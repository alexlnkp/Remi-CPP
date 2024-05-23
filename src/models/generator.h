#ifndef GENERATOR_H
#define GENERATOR_H

#include "common/macros.h"

namespace std {
    template <typename T, typename D> class unique_ptr;
    template <typename T, typename D> class vector;
} // namespace std


namespace ctranslate2 {
    namespace models { class ModelLoader; }

    class Generator;
    class GenerationResult;

    class ReplicaPoolConfig;
} // namespace ctranslate2


namespace remi {

// typedef std::vector<std::vector<size_t>> BatchIDs;

namespace models {

class GeneratorModel {
public:
    NON_NULL(1) GeneratorModel(ctranslate2::models::ModelLoader& model_loader, ctranslate2::ReplicaPoolConfig& config);

    ~GeneratorModel();

    void set_options(const ctranslate2::GenerationOptions& options);

    NON_NULL(1) BatchSlices generate(const BatchSlices &encoded_prompt) const;
    // BatchSlices generate(const BatchIDs &prompt_ids) const;

    size_t max_batch_size = 0U;

private:
    U_PTR(ctranslate2::GenerationOptions) _generation_options;
    U_PTR(ctranslate2::models::ModelLoader) _model_loader;
    U_PTR(ctranslate2::ReplicaPoolConfig) _config;
    U_PTR(ctranslate2::Generator) _generator;
};

} // namespace models

namespace generation {

ctranslate2::GenerationOptions parse_options(remi::UserConfig &user_config);

}

} // namespace remi

#endif