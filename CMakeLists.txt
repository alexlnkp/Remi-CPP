cmake_minimum_required(VERSION 3.29)

project(
  RemiCPP
  LANGUAGES CXX
  VERSION 0.0.14
  DESCRIPTION "Remi C++"
  HOMEPAGE_URL "https://github.com/alexlnkp/Remi-CPP")

set(CMAKE_CXX_FLAGS_INIT "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "${CMAKE_CXX_FLAGS_INIT} -g -O0")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${CMAKE_CXX_FLAGS_INIT} -O3")

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests
    OFF
    CACHE INTERNAL "")

set(INCLUDE_DIRECTORIES src lib)

# file globbing ##############################################################

file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE sources_common src/common/*.cpp src/common/*.h)
file(GLOB_RECURSE models src/models/*.cpp src/models/*.h)

# target definitions #########################################################

add_executable(${PROJECT_NAME} ${sources} ${sources_common} ${models})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++20)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

find_package(nlohmann_json REQUIRED)
find_package(ctranslate2 REQUIRED)

# linking ####################################################################

target_link_libraries(${PROJECT_NAME} CTranslate2::ctranslate2)
target_link_libraries(${PROJECT_NAME} sentencepiece)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

# post build steps ###########################################################

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND mv ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/output/${PROJECT_NAME})
