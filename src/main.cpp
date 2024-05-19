#include <iostream>
#include <ctranslate2/translator.h>
#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>
#include <sentencepiece_processor.h>

int main() {
    sentencepiece::SentencePieceProcessor sp;
    sp.Load("/home/alex/.huggingface/hub/models--JosephusCheung--LL7M/snapshots/9b31bbf38a43d41eaf166fb3573f706b23cb1c13/tokenizer.model");


    ctranslate2::ReplicaPoolConfig config;
    config.num_threads_per_replica = 1;
    config.max_queued_batches = 1;

    ctranslate2::models::ModelLoader model_loader("models/ct2-ll7m");

    ctranslate2::Generator generator(model_loader, config);

    std::string prompt = "Hey, Remi!";

    std::vector<std::string> tokens = sp.EncodeAsPieces(prompt);
    std::vector<int> ids = sp.EncodeAsIds(prompt);
    std::cout << prompt << std::endl;

    for (auto& id : ids) {
        std::cout << id << ' ';
    }

    std::cout << std::endl;

    for (auto& token : tokens) {
        std::cout << token << ' ';
    }

    // std::cout << translator.translate_batch_async("Hello, world!") << std::endl;
}
