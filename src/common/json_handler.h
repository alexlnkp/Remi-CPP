#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <nlohmann/json_fwd.hpp>

namespace remi {

struct UserConfig {
    std::string TokenizerPath;
    std::string GeneratorPath;

    std::string UsrReqDevice;

    size_t BeamSize;

    size_t TopK;
    float TopP;

    size_t BatchSize;

    size_t MaxSequenceLength;

    float RepetitionPenalty;

    float Temperature;
};

// A wrapper for an overload of ParseUserConfig because NLohmann decided it would be a good idea to make std::string a friend of nlohmann::json_abi_v3_11_2::json.
struct JsonFilePath {
    std::string path;
};

namespace json {

    template <typename T> nlohmann::json parse_json_file(T);

    UserConfig ParseUserConfig(const nlohmann::json &config_json);
    UserConfig ParseUserConfig(const JsonFilePath &config_path);

} // namespace json


} // namespace remi

#endif