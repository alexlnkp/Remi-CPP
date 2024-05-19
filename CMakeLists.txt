cmake_minimum_required(VERSION 3.29)

project(RemiCPP)


set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Werror -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Werror -O3")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB_RECURSE sources      src/*.cpp src/*.h)

###############################################################################
## target definitions #########################################################
###############################################################################

add_subdirectory(lib/sentencepiece)

add_executable(${PROJECT_NAME} ${sources})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20)

find_package(ctranslate2 REQUIRED)

target_link_libraries(${PROJECT_NAME} CTranslate2::ctranslate2)
target_link_libraries(${PROJECT_NAME} libsentencepiece.so)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND mv ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/output/${PROJECT_NAME}
)
