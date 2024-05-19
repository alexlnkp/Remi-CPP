#include <iostream>
#include <ctranslate2/translator.h>
#include <ctranslate2/generator.h>
#include <ctranslate2/models/model.h>
#include <sentencepiece_processor.h>

int main() {
    sentencepiece::SentencePieceProcessor sp;
    sp.Load("/home/alex/.huggingface/hub/models--JosephusCheung--LL7M/blobs/ffc415e485fbcba6d207670fd14e00b99b6edf5e74bf967e3a370ae969ff550a");

    ctranslate2::ReplicaPoolConfig config;
    config.num_threads_per_replica = 1;
    config.max_queued_batches = 1;

    ctranslate2::models::ModelLoader model_loader("../models/ct2-ll7m");

    ctranslate2::Generator generator(model_loader, config);
    ctranslate2::Translator translator(model_loader, config);

    ctranslate2::TranslationOptions options;
    options.max_decoding_length = 10;
    options.beam_size = 5;

    std::string prompt = "Hey, Remi!";

    std::vector<std::string> tokens = sp.EncodeAsPieces(prompt);
    std::vector<int> ids = sp.EncodeAsIds(prompt);
    std::cout << prompt << std::endl;
    for (auto& id : ids) {
        std::cout << id << std::endl;
    }
    for (auto& token : tokens) {
        std::cout << token << std::endl;
    }

    // std::cout << translator.translate_batch_async("Hello, world!") << std::endl;
}
