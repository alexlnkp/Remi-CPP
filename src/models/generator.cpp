
#include <ctranslate2/models/model.h>
#include <ctranslate2/generator.h>
#include "generator.h"

namespace ctranslate2 {

GeneratorModel::GeneratorModel(models::ModelLoader& model_loader, ReplicaPoolConfig& config) {
    _model_loader = &model_loader;
    _config = &config;
    _generator = new Generator(*_model_loader, *_config);
}

GeneratorModel::~GeneratorModel() {
    delete _generator;
}

BATCH_SLICES GeneratorModel::generate(const BATCH_SLICES &encoded_prompt) const {
    return _generator->generate_batch_async(encoded_prompt).at(0).get().sequences;
}

} // namespace ctranslate2