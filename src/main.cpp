#include <iostream>
#include <memory>
#include <cassert>

#include <nlohmann/json.hpp>

#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>

#include "common/json_handler.h"
#include "common/prompt_mod.h"

#include "models/tokenizer.h"
#include "models/generator.h"


int main() {
    std::ios::sync_with_stdio(false);

    nlohmann::json config_json = remi::json::parse_json_file("config.json");

    auto tokenizer_path = config_json["tokenizer_info"]["tokenizer_path"].get<std::string>();
    auto generator_path = config_json["model_info"]["model_path"].get<std::string>();

    auto usr_req_device = config_json["device"].get<std::string>();
    auto top_k = config_json["top_k"].get<size_t>();
    auto top_p = config_json["top_p"].get<float>();
    auto batch_size = config_json["batch_size"].get<size_t>();
    auto max_seq_len = config_json["max_seq_len"].get<size_t>();
    auto repetition_penalty = config_json["repetition_penalty"].get<float>();
    auto temperature = config_json["temperature"].get<float>();

    ctranslate2::GenerationOptions generation_options {
        .beam_size = 1,
        .repetition_penalty = repetition_penalty,
        .max_length = max_seq_len,
        .sampling_topk = top_k,
        .sampling_topp = top_p,
        .include_prompt_in_result = true,
    };

    // User wants to use cuda but no gpu is detected by CTranslate2.
    // This is usually because the user compiled CTranslate2 without CUDA support.
    if (usr_req_device == "cuda" && ctranslate2::get_gpu_count() == 0) {
        std::cerr << "User requested CUDA but No GPU is detected by CTranslate2." << '\n'
                  << "Please compile CTranslate2 with CUDA support" << std::endl;
        return -1;
    }

    ctranslate2::Device device(ctranslate2::str_to_device(usr_req_device));

    remi::models::Tokenizer sp(tokenizer_path.c_str());

    ctranslate2::ReplicaPoolConfig config {
        .num_threads_per_replica = 0,
        .max_queued_batches = 0,
    };

    ctranslate2::models::ModelLoader model_loader(generator_path.c_str());
    model_loader.device = device;

    remi::models::GeneratorModel generator_model(model_loader, config);
    generator_model.set_options(generation_options);
    generator_model.max_batch_size = batch_size;

    std::string prompt = "## History:" "\n"
                        "User: Hey!" "\n"
                        "Assistant: Why, hello there! How are you doing?" "\n"
                        "User: Pretty good, thank you." "\n"
                        "Assistant: What do you want to chat about?" "\n"
                        "## Input:" "\n"
                        "System: You are an AI assistant. Carefully listen to user prompt and answer them in as much detail as possible." "\n"
                        "User: Hey! How are you doing?" "\n"
                        "## Response:" "\n"
                        "Assistant: ";

    auto results = generator_model.generate({sp.EncodeAsPieces(prompt)});

    for (auto& result : results) {
        printf(sp.Decode(result).c_str());
    }

    return 0;
}
