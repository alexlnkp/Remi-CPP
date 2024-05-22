
#include <ctranslate2/models/model.h>
#include <ctranslate2/generator.h>
#include "generator.h"

namespace remi {


namespace models {

GeneratorModel::GeneratorModel(ctranslate2::models::ModelLoader& model_loader, ctranslate2::ReplicaPoolConfig& config) {
    _model_loader = &model_loader;
    _config = &config;
    _generator = new ctranslate2::Generator(*_model_loader, *_config);
}

GeneratorModel::~GeneratorModel() {
    delete _generator;
}

BatchSlices GeneratorModel::generate(const BatchSlices &encoded_prompt) const {
    return _generator->generate_batch_async(encoded_prompt).at(0).get().sequences;
}

} // namespace models


} // namespace remi
