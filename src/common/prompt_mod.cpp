#include <string>
#include <vector>

#include "prompt_mod.h"

template BATCH CreateBatch<const char*>(const char*);
template BATCH CreateBatch<std::string>(std::string);

template <typename T>
BATCH CreateBatch(T prompt) {
    return {{prompt}};
}

