#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include <nlohmann/json_fwd.hpp>

namespace remi {


namespace json {

    template <typename T> nlohmann::json parse_json_file(T);

} // namespace json


} // namespace remi

#endif