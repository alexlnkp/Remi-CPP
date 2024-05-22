#include <sentencepiece_processor.h>
#include "tokenizer.h"

namespace remi {

namespace models {

#pragma region Public methods

Tokenizer::Tokenizer(const char *model_path) {
    _load(model_path);
}

Tokenizer::~Tokenizer() {
    _sp.release();
}


std::vector<std::string> Tokenizer::EncodeAsPieces(const std::string& text) const {
    return _encode(text);
}

std::vector<int> Tokenizer::EncodeAsIds(const std::string& text) const {
    return _encode_ids(text);
}


std::string Tokenizer::Decode(const std::vector<std::string> &slices) const {
    return _decode(slices);
}


BatchSlices Tokenizer::GeneratePrompt(std::vector<std::string> tokens) const {
    tokens.insert(tokens.begin(), "<s>");
    tokens.push_back("</s>");
    return {tokens};
}

#pragma endregion

#pragma region Private methods

void Tokenizer::_load(const char *model_path) {
    _sp = std::make_unique<sentencepiece::SentencePieceProcessor>();
    _sp->Load(model_path);
}


std::vector<std::string> Tokenizer::_encode(const std::string& text) const {
    return _sp->EncodeAsPieces(text);
}

std::vector<int> Tokenizer::_encode_ids(const std::string &text) const {
    return _sp->EncodeAsIds(text);
}


std::string Tokenizer::_decode(const std::vector<std::string> &pieces) const {
    return _sp->DecodePieces(pieces);
}

#pragma endregion

} // namespace models


} // namespace remi
