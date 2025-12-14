// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string_helper.cc

#include "string_helper.h"

#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "random_engine.h"

namespace faker {

std::string capitalize(const std::string_view word) {
    std::string out(word);
    if (out.empty()) return out;

    std::ranges::transform(out, out.begin(), [](const char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    });

    out[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(out[0])));
    return out;
}

std::string remove_characters(const std::string_view source_string, const std::string_view chars_to_remove) {
    std::string new_string;
    new_string.reserve(source_string.size());  // Optional: reserve capacity to avoid multiple reallocations
    for (const char c : source_string) {
        if (chars_to_remove.find(c) == std::string_view::npos) { new_string += c; }
    }
    return new_string;
}

std::string remove_extra_spaces(const std::string_view source_string) {
    std::string new_string;
    new_string.reserve(source_string.size());

    for (const char c : source_string) {
        if (c == ' ') {
            if (new_string.empty() || new_string.back() != ' ') { new_string += c; }
        } else {
            new_string += c;
        }
    }

    return new_string;
}

std::string replace_placeholder(std::string_view pattern, const std::string_view replacement) {
    std::string       result;
    const std::size_t pos = pattern.find("{}");
    if (pos == std::string_view::npos) {
        return std::string(pattern);  // No placeholder found, return as is.
    }

    result.reserve(pattern.size() - 2 + replacement.size());
    result.append(pattern.substr(0, pos));
    result.append(replacement);
    result.append(pattern.substr(pos + 2));
    return result;
}

std::string& trim(std::string& s) {
    if (s.empty()) { return s; }
    s.erase(0, s.find_first_not_of(" \t\r\n"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

std::vector<std::string> split(const std::string_view source_string, const char delimiter) {
    std::vector<std::string> tokens;
    const std::string        source(source_string);
    std::stringstream        stream(source);
    std::string              token;
    while (std::getline(stream, token, delimiter)) {
        if (!token.empty()) { tokens.push_back(token); }
    }

    return tokens;
}

std::vector<std::string> split_and_trim(const std::string_view source_string, const char delimiter) {
    std::vector<std::string> tokens;
    const std::string        source(source_string);
    std::stringstream        stream(source);
    std::string              token;
    while (std::getline(stream, token, delimiter)) {
        if (!token.empty()) {
            trim(token);
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::string
    replace_wildcard_to_character(const std::string_view pattern, const std::string_view chars, const char wildcard) {
    std::string out;
    out.reserve(pattern.size());

    std::mt19937_64&                      random_engine = get_random_engine();
    std::uniform_int_distribution<size_t> digits_distribution(0, chars.size() - 1);

    for (const char c : pattern) { c == wildcard ? out += chars[digits_distribution(random_engine)] : out += c; }

    return out;
}

std::pair<std::string, std::string> replace_wildcards_with_same_characters(
    const std::string_view pattern1,
    const std::string_view pattern2,
    const std::string_view chars,
    const char             wildcard
) {
    std::vector<char> random_chars;
    if (chars.empty()) return {std::string(pattern1), std::string(pattern2)};

    // Count the total number of wildcards in both patterns
    const size_t count1 = std::ranges::count(pattern1, wildcard);
    const size_t count2 = std::ranges::count(pattern2, wildcard);
    if (count1 != count2) { return {std::string(pattern1), std::string(pattern2)}; }

    std::mt19937_64&                      random_engine = get_random_engine();
    std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    random_chars.reserve(count1);
    for (size_t i = 0; i < count1; ++i) { random_chars.push_back(chars[dist(random_engine)]); }

    auto replace = [&](const std::string_view pattern) -> std::string {
        size_t      index = 0;
        std::string result;
        result.reserve(pattern.size());
        for (char c : pattern) { result += c == wildcard ? random_chars[index++] : c; }
        return result;
    };

    return {replace(pattern1), replace(pattern2)};
}

std::string
    replace_wildcard_to_digit(const std::string_view pattern, const std::string_view digits, const char wildcard) {
    return replace_wildcard_to_character(pattern, digits, wildcard);
}

std::pair<std::string, std::string> replace_wildcards_with_same_digits(
    const std::string_view pattern1,
    const std::string_view pattern2,
    const std::string_view digits,
    const char             wildcard
) {
    return replace_wildcards_with_same_characters(pattern1, pattern2, digits, wildcard);
}

std::string
    replace_wildcard_to_letter(const std::string_view pattern, const std::string_view letters, const char wildcard) {
    return replace_wildcard_to_character(pattern, letters, wildcard);
}

std::pair<std::string, std::string> replace_wildcards_with_same_letters(
    const std::string_view pattern1,
    const std::string_view pattern2,
    const std::string_view letters,
    const char             wildcard
) {
    return replace_wildcards_with_same_characters(pattern1, pattern2, letters, wildcard);
}

}  // namespace faker
