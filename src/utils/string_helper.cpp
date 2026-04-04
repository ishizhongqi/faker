// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string_helper.cpp

#include "string_helper.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <string>
#include <string_view>
#include <stdexcept>
#include <vector>

#include "random_engine.h"

namespace faker {

std::string capitalize(const std::string_view word) {
    std::string out(word);
    if (out.empty()) return out;

    std::transform(out.begin(), out.end(), out.begin(), [](const char c) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    });

    out[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(out[0])));
    return out;
}

std::string remove_characters(const std::string_view source_string, const std::string_view chars_to_remove) {
    std::array<bool, 256> should_remove{};
    for (const char c : chars_to_remove) { should_remove[static_cast<unsigned char>(c)] = true; }

    std::string out;
    out.reserve(source_string.size());
    for (const char c : source_string) {
        if (!should_remove[static_cast<unsigned char>(c)]) { out.push_back(c); }
    }
    return out;
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

std::string replace_wildcard_with_sequence(
    const std::string_view pattern,
    const char             wildcard,
    const std::string_view replacement
) {
    const std::size_t wildcard_count = static_cast<std::size_t>(std::count(pattern.begin(), pattern.end(), wildcard));
    if (wildcard_count != replacement.size()) {
        throw std::invalid_argument("Replacement size must match wildcard count.");
    }

    std::string out;
    out.reserve(pattern.size());

    std::size_t i = 0;
    for (const char c : pattern) {
        if (c == wildcard) {
            out.push_back(replacement[i]);
            ++i;
        } else {
            out.push_back(c);
        }
    }

    return out;
}

std::string
    replace_wildcard_with_character(const std::string_view pattern, const std::string_view chars, const char wildcard) {
    if (chars.empty() && std::find(pattern.begin(), pattern.end(), wildcard) != pattern.end()) {
        throw std::invalid_argument("chars must not be empty when wildcard exists in pattern.");
    }

    std::string out;
    out.reserve(pattern.size());

    std::mt19937_64&                      random_engine = get_random_engine();
    std::uniform_int_distribution<size_t> digits_distribution(0, chars.size() - 1);

    for (const char c : pattern) {
        if (c == wildcard) {
            out.push_back(chars[digits_distribution(random_engine)]);
        } else {
            out.push_back(c);
        }
    }

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
    const size_t count1 = std::count(pattern1.begin(), pattern1.end(), wildcard);
    const size_t count2 = std::count(pattern2.begin(), pattern2.end(), wildcard);
    if (count1 != count2) { return {std::string(pattern1), std::string(pattern2)}; }

    std::mt19937_64&                      random_engine = get_random_engine();
    std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    random_chars.reserve(count1);
    for (size_t i = 0; i < count1; ++i) { random_chars.push_back(chars[dist(random_engine)]); }

    auto replace = [&](const std::string_view pattern) -> std::string {
        size_t      index = 0;
        std::string result;
        result.reserve(pattern.size());
        for (const char c : pattern) {
            if (c == wildcard) {
                result.push_back(random_chars[index]);
                ++index;
            } else {
                result.push_back(c);
            }
        }
        return result;
    };

    return {replace(pattern1), replace(pattern2)};
}

std::string
    replace_wildcard_with_digit(const std::string_view pattern, const std::string_view digits, const char wildcard) {
    return replace_wildcard_with_character(pattern, digits, wildcard);
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
    replace_wildcard_with_letter(const std::string_view pattern, const std::string_view letters, const char wildcard) {
    return replace_wildcard_with_character(pattern, letters, wildcard);
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
