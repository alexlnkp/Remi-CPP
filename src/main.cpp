#include <iostream>
#include <memory>

#include <nlohmann/json.hpp>

#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>

#include "common/json_handler.h"

#include "common/prompt_mod.h"
#include "models/tokenizer.h"
// #include "models/generator.h"


int main() {
    std::ios::sync_with_stdio(false);

    nlohmann::json config_json = remi::json::parse_json_file("config.json");

    auto tokenizer_path = config_json["tokenizer_info"]["tokenizer_path"].get<std::string>();
    auto generator_path = config_json["model_info"]["model_path"].get<std::string>();

    ctranslate2::Tokenizer sp(tokenizer_path.c_str());

    ctranslate2::ReplicaPoolConfig config {
        .num_threads_per_replica = 1,
        .max_queued_batches = 1,
    };

    ctranslate2::models::ModelLoader model_loader(generator_path.c_str());

    // ctranslate2::GeneratorModel generator_model(model_loader, config);
    ctranslate2::Generator generator_model(model_loader, config);

    std::string prompt = "Hey, Remi!";

    std::vector<std::string> tokens = sp.EncodeAsPieces(prompt);
    std::vector<int> ids = sp.EncodeAsIds(prompt);
    // std::vector<BATCH_IDS> batch = CreateBatch(ids);

    std::cout << "Regular prompt: " << prompt << std::endl;

    std::cout << "IDs: ";
    for (auto& id : ids)
        std::cout << id << ' ';

    std::cout << std::endl << "Tokens: ";
    for (auto& token : tokens)
        std::cout << token << ' ';

    std::cout << std::endl << "Decoded: " << sp.Decode(ids) << std::endl;

    // auto results = generator_model.generate_batch_async(ids, ctranslate2::GenerationOptions(), 0L, ctranslate2::BatchType::Tokens);

    // for (const auto& token : results.at(0).get().sequences)
    //     std::cout << token.at(0) << ' ';
    // std::cout << std::endl;

    return 0;
}
