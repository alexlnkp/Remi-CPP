#include <string>
#include <vector>

#include "prompt_mod.h"

namespace remi {

template BatchSlices CreateBatch<const char*>(const char*);
template BatchSlices CreateBatch<std::string>(std::string);
template std::vector<BatchIDs> CreateBatch<BatchIDs>(BatchIDs);

template <typename T> BatchSlices CreateBatch(T prompt) {
    return {{prompt}};
}

template <typename T> std::vector<BatchIDs> CreateBatch(T prompt) {
    return {prompt};
}

} // namespace remi
