#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "json_handler.h"
#include "remio.h"

namespace remi {


namespace json {

template nlohmann::json parse_json_file<const char*>(const char*);
template nlohmann::json parse_json_file<std::string>(std::string);

template <typename T>
nlohmann::json parse_json_file(T path) {
    if (!file_exists(path)) {
        std::cerr << "File not found: " << path << std::endl;
        return nlohmann::json();
    }
    std::ifstream i(path);
    nlohmann::json j;
    i >> j;

    return j;
}

} // namespace json


} // namespace remi
