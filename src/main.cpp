#include <iostream>
#include <memory>

#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>

#include "common/prompt_mod.h"
#include "models/tokenizer.h"
// #include "models/generator.h"

#define TOKENIZER_PATH "/home/alex/.huggingface/hub/models--JosephusCheung--LL7M/snapshots/9b31bbf38a43d41eaf166fb3573f706b23cb1c13/tokenizer.model"

#define GENERATOR_PATH "models/ct2-ll7m"

int main() {
    std::ios::sync_with_stdio(false);

    ctranslate2::Tokenizer sp(TOKENIZER_PATH);

    ctranslate2::ReplicaPoolConfig config {
        .num_threads_per_replica = 1,
        .max_queued_batches = 1,
    };

    printf("Loading model...");
    ctranslate2::models::ModelLoader model_loader(GENERATOR_PATH);
    printf("Done!\n");

    // ctranslate2::GeneratorModel generator_model(model_loader, config);

    printf("Loading generator...");
    ctranslate2::Generator generator_model(model_loader, config);
    printf("Done!\n");

    auto batch = CreateBatch("Hello world !");

    printf("Generating...");
    auto results = generator_model.generate_batch_async(batch);
    printf("Done!\n");

    for (const auto& token : results.at(0).get().sequences)
        std::cout << token.at(0) << ' ';
    std::cout << std::endl;

    std::string prompt = "Hey, Remi!";

    std::vector<std::string> tokens = sp.EncodeAsPieces(prompt);
    std::vector<int> ids = sp.EncodeAsIds(prompt);

    std::cout << "Regular prompt: " << prompt << std::endl;

    std::cout << "IDs: ";
    for (auto& id : ids)
        std::cout << id << ' ';

    std::cout << std::endl << "Tokens: ";
    for (auto& token : tokens)
        std::cout << token << ' ';

    std::cout << std::endl << "Decoded: " << sp.Decode(ids) << std::endl;

    return 0;
}
