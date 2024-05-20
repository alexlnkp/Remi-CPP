#ifndef GENERATOR_H
#define GENERATOR_H

#include "common/macros.h"

namespace std {

template <typename T, typename D>
class unique_ptr;


template <typename T, typename D>
class vector;

} // namespace std


namespace ctranslate2 {

namespace models { class ModelLoader;}

class Generator;
class GenerationResult;

class ReplicaPoolConfig;


class GeneratorModel {
public:
    NON_NULL(1)
    GeneratorModel(models::ModelLoader& model_loader, ReplicaPoolConfig& config);

    ~GeneratorModel();

    NON_NULL(1)
    BATCH generate(const BATCH &encoded_prompt) const;

private:
    models::ModelLoader *_model_loader;
    ReplicaPoolConfig *_config;
    Generator *_generator;
};


} // namespace ctranslate2

#endif