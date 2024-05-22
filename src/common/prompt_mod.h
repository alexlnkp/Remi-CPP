#ifndef PROMPT_MOD_H
#define PROMPT_MOD_H

#include "macros.h"

namespace remi {

typedef std::vector<std::vector<std::string>> BatchSlices;
typedef std::vector<int> BatchIDs;

template <typename T> BatchSlices CreateBatch(T);
template <typename T> std::vector<BatchIDs> CreateBatch(T);

} // namespace remi

#endif