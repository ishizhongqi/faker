// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file validation.cpp

#include "validation.h"

#include <string>
#include <string_view>

namespace faker {

std::string get_function_name(std::string_view function_name) {
    // const size_t paren_pos = function_name.rfind('(');
    // if (paren_pos != std::string_view::npos) { function_name = function_name.substr(0, paren_pos); }
    //
    // size_t template_pos = function_name.rfind(']');
    // if (template_pos != std::string_view::npos) {
    //     const size_t start_template_pos = function_name.rfind('[', template_pos);
    //     if (start_template_pos != std::string_view::npos) {
    //         if (start_template_pos > 0 && function_name[start_template_pos - 1] == ' ') {
    //             function_name = function_name.substr(0, start_template_pos - 1);
    //         } else {
    //             function_name = function_name.substr(0, start_template_pos);
    //         }
    //     }
    // }
    //
    // template_pos = function_name.rfind('>');
    // if (template_pos != std::string_view::npos) {
    //     const size_t start_template_pos = function_name.rfind('<', template_pos);
    //     if (start_template_pos != std::string_view::npos) {
    //         function_name = function_name.substr(0, start_template_pos);
    //     }
    // }
    //
    // const size_t scope_pos = function_name.rfind("::");
    // if (scope_pos != std::string_view::npos) {
    //     size_t space_pos = function_name.rfind(' ', scope_pos);
    //     if (space_pos != std::string_view::npos) { function_name = function_name.substr(space_pos + 1); }
    // } else {
    //     const size_t space_pos = function_name.rfind(' ');
    //     if (space_pos != std::string_view::npos) { function_name = function_name.substr(space_pos + 1); }
    // }
    //
    // const size_t last_char = function_name.find_last_not_of(" \t\n\r");
    // if (last_char != std::string_view::npos) { function_name.remove_suffix(function_name.length() - last_char - 1); }
    //
    // return std::string(function_name);

    const size_t end_pos = function_name.find_first_of("(<[");
    if (end_pos != std::string_view::npos) { function_name = function_name.substr(0, end_pos); }

    if (const auto last_char_pos = function_name.find_last_not_of(" \t"); last_char_pos != std::string_view::npos) {
        function_name = function_name.substr(0, last_char_pos + 1);
    } else {
        return {};
    }

    const size_t start_pos = function_name.rfind(' ');
    if (start_pos != std::string_view::npos) { function_name = function_name.substr(start_pos + 1); }

    return std::string(function_name);
}

}  // namespace faker
