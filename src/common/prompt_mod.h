#ifndef PROMPT_MOD_H
#define PROMPT_MOD_H

#include "macros.h"

template <typename T>
BATCH_SLICES CreateBatch(T);

template <typename T>
std::vector<BATCH_IDS> CreateBatch(T);

#endif