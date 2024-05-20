#ifndef MACROS_H
#   define MACROS_H
#   include "hedley/hedley.h"
#   define NON_NULL(...) HEDLEY_NON_NULL(__VA_ARGS__)
#   define NON_EMPTY(...) HEDLEY_NON_EMPTY(__VA_ARGS__)
#   define U_PTR(...) std::unique_ptr<__VA_ARGS__>
#   define BATCH std::vector<std::vector<std::string>>
#endif