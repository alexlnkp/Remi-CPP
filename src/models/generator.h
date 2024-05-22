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

typedef std::vector<std::vector<std::string>> BatchSlices;


namespace models {

class GeneratorModel {
public:
    NON_NULL(1) GeneratorModel(ctranslate2::models::ModelLoader& model_loader, ctranslate2::ReplicaPoolConfig& config);

    ~GeneratorModel();

    NON_NULL(1) BatchSlices generate(const BatchSlices &encoded_prompt) const;

private:
    ctranslate2::models::ModelLoader *_model_loader;
    ctranslate2::ReplicaPoolConfig *_config;
    ctranslate2::Generator *_generator;
};

} // namespace models


} // namespace remi

#endif