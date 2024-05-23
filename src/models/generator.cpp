
#include <ctranslate2/models/model.h>
#include <ctranslate2/generator.h>
#include <memory>

#include "common/json_handler.h"
#include "generator.h"

namespace remi {


namespace models {

GeneratorModel::GeneratorModel(ctranslate2::models::ModelLoader& model_loader, ctranslate2::ReplicaPoolConfig& config) {
    _model_loader = std::make_unique<ctranslate2::models::ModelLoader>(model_loader);
    _config = std::make_unique<ctranslate2::ReplicaPoolConfig>(config);
    _generator = std::make_unique<ctranslate2::Generator>(*_model_loader, *_config);
    _generation_options = std::make_unique<ctranslate2::GenerationOptions>(ctranslate2::GenerationOptions());
}

GeneratorModel::~GeneratorModel() {
    _generator.release();
    _model_loader.release();
    _config.release();
    _generation_options.release();
}

void GeneratorModel::set_options(const ctranslate2::GenerationOptions& options) {
    *_generation_options = options;
}

BatchSlices GeneratorModel::generate(const BatchSlices &prompt_slices) const {
    return _generator->generate_batch_async(prompt_slices, *_generation_options, max_batch_size, ctranslate2::BatchType::Tokens).at(0).get().sequences;
}

// BatchSlices GeneratorModel::generate(const BatchIDs &prompt_ids) const {
//     return _generator->forward_batch_async(prompt_ids, false).get();
// }

} // namespace models

namespace generation {

ctranslate2::GenerationOptions parse_options(remi::UserConfig &user_config) {
    return ctranslate2::GenerationOptions {
        .beam_size = user_config.BeamSize,
        .repetition_penalty = user_config.RepetitionPenalty,
        .max_length = user_config.MaxSequenceLength,
        .sampling_topk = user_config.TopK,
        .sampling_topp = user_config.TopP,
        .include_prompt_in_result = true,
    };
}

} // namespace generation


} // namespace remi

