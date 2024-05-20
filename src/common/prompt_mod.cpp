#include <string>
#include <vector>

#include "prompt_mod.h"

template BATCH_SLICES CreateBatch<const char*>(const char*);
template BATCH_SLICES CreateBatch<std::string>(std::string);
template std::vector<BATCH_IDS> CreateBatch<BATCH_IDS>(BATCH_IDS);

template <typename T>
BATCH_SLICES CreateBatch(T prompt) {
    return {{prompt}};
}

template <typename T>
std::vector<BATCH_IDS> CreateBatch(T prompt) {
    return {prompt};
}