cmake_minimum_required(VERSION 3.29)

project(RemiCPP)


set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Werror -O3")

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources      src/*.cpp src/*.h)

###############################################################################
## target definitions #########################################################
###############################################################################

add_subdirectory(lib/sentencepiece)

add_executable(${PROJECT_NAME} ${sources} ${data})

target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall -Werror)

find_package(ctranslate2)

target_link_libraries(${PROJECT_NAME} CTranslate2::ctranslate2)

target_link_libraries(${PROJECT_NAME} libsentencepiece.so)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND mv ${PROJECT_NAME} ../output/${PROJECT_NAME}
)