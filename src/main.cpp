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

    remi::UserConfig user_conf = remi::json::ParseUserConfig(
        remi::JsonFilePath{"config.json"}
    );

    ctranslate2::GenerationOptions generation_options = remi::generation::parse_options(user_conf);

    // User wants to use cuda but no gpu is detected by CTranslate2.
    // This is usually because the user compiled CTranslate2 without CUDA support.
    if (user_conf.UsrReqDevice == "cuda" && ctranslate2::get_gpu_count() == 0) {
        std::cerr << "User requested CUDA but No GPU is detected by CTranslate2." << '\n'
                  << "Please compile CTranslate2 with CUDA support" << '\n' << std::endl;
        
        // Fun fact: I could've used a local var for exit code and just goto; for going straight to the end...
        // BUT! G++ didn't like that i skipped initialization of the automatically managed objects.
        // So, in other words, even if an object is never initialized properly,
        // G++ would still want to remove them at the end of scope... For some reason.
        return -1;
    }

    ctranslate2::Device device(ctranslate2::str_to_device(user_conf.UsrReqDevice));

    remi::models::Tokenizer sp(user_conf.TokenizerPath.c_str());

    ctranslate2::ReplicaPoolConfig config {
        .num_threads_per_replica = 0,
        .max_queued_batches = 0,
    };

    ctranslate2::models::ModelLoader model_loader(user_conf.GeneratorPath.c_str());
    model_loader.device = device;

    remi::models::GeneratorModel generator_model(model_loader, config);
    generator_model.set_options(generation_options);
    generator_model.max_batch_size = user_conf.BatchSize;

    std::string prompt = "## History:" "\n"
                        "User: Hey!" "\n"
                        "Assistant: Why, hello there! How are you doing?" "\n"
                        "User: Pretty good, thank you." "\n"
                        "Assistant: What do you want to chat about?" "\n"
                        "## Input:" "\n"
                        "System: You are an AI assistant. Carefully listen to user prompt and answer them in as much detail as possible." "\n"
                        "User: Hey! How are you doing?" "\n"
                        "## Response:" "\n";

    auto results = generator_model.generate({sp.EncodeAsPieces(prompt)});

    for (auto& result : results) {
        printf(sp.Decode(result).c_str());
    }

    return 0;
}
