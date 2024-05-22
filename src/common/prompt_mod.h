#ifndef PROMPT_MOD_H
#define PROMPT_MOD_H

#include "macros.h"

namespace remi {

template <typename T> BatchSlices CreateBatch(T);
template <typename T> std::vector<BatchIDs> CreateBatch(T);

} // namespace remi

#endif