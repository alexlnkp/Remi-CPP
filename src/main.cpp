#include <iostream>
#include <memory>

#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>

#include "tokenizer.h"

#define TOKENIZER_PATH "/home/alex/.huggingface/hub/models--JosephusCheung--LL7M/snapshots/9b31bbf38a43d41eaf166fb3573f706b23cb1c13/tokenizer.model"

#define GENERATOR_PATH "models/ct2-ll7m"

int main() {
    std::ios::sync_with_stdio(false);

    auto sp = ctranslate2::Tokenizer(TOKENIZER_PATH);

    ctranslate2::ReplicaPoolConfig config {
        .num_threads_per_replica = 1,
        .max_queued_batches = 1,
    };


    ctranslate2::models::ModelLoader model_loader(GENERATOR_PATH);

    ctranslate2::Generator generator(model_loader, config);

    std::string prompt = "Hey, Remi!";

    std::vector<std::string> tokens = sp.EncodeAsPieces(prompt);
    std::vector<int> ids = sp.EncodeAsIds(prompt);

    std::cout << "Regular prompt: " << prompt << std::endl;

    std::cout << "IDs: ";
    for (auto& id : ids) { std::cout << id << ' '; }

    std::cout << std::endl << "Tokens: ";
    for (auto& token : tokens) { std::cout << token << ' '; }

    std::cout << std::endl << "Decoded: " << sp.Decode(ids) << std::endl;

    return 0;
}
