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
    i.close();
    return j;
}

UserConfig ParseUserConfig(const nlohmann::json &config_json) {
    return UserConfig {
        .TokenizerPath = config_json["tokenizer_info"]["tokenizer_path"].get<std::string>(),
        .GeneratorPath = config_json["model_info"]["model_path"].get<std::string>(),
        .UsrReqDevice = config_json["device"].get<std::string>(),
        .BeamSize = config_json["beam_size"].get<size_t>(),
        .TopK = config_json["top_k"].get<size_t>(),
        .TopP = config_json["top_p"].get<float>(),
        .BatchSize = config_json["batch_size"].get<size_t>(),
        .MaxSequenceLength = config_json["max_seq_len"].get<size_t>(),
        .RepetitionPenalty = config_json["repetition_penalty"].get<float>(),
        .Temperature = config_json["temperature"].get<float>()
    };
}

UserConfig ParseUserConfig(const JsonFilePath &config_path) {
    nlohmann::json config_json = parse_json_file(config_path.path);
    return ParseUserConfig(config_json);
}

} // namespace json


} // namespace remi
