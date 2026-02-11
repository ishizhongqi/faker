// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string.cpp

#include "faker/string.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <random>
#include <span>
#include <string>
#include <string_view>

#include "random_engine.h"
#include "random_helper.h"
#include "string_data.h"
#include "validation.h"

namespace faker::string {

namespace {

constexpr std::array kHexDigits{
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
};

void write_hex_byte(std::string& output, const uint8_t value) {
    output.push_back(kHexDigits[(value >> 4) & 0x0F]);
    output.push_back(kHexDigits[value & 0x0F]);
}

}  // namespace

std::string enum_item(const std::span<const std::string_view> enums) {
    if (enums.empty()) { return ""; }
    return std::string(pick_one<std::string_view>(enums));
}

std::string text(const unsigned int number_of_chars_start, const unsigned int number_of_chars_end) {
    CHECK_RANGE(std::invalid_argument, number_of_chars_start, number_of_chars_end);
    if (kEnglishTexts.empty()) {
        throw_exception<std::invalid_argument>(
            "Text source is empty.",
            std::source_location::current()
        );
    }

    std::mt19937_64& random_engine = get_random_engine();
    std::uniform_int_distribution<unsigned int> length_distribution(number_of_chars_start, number_of_chars_end);
    const unsigned int target_length = length_distribution(random_engine);
    if (target_length == 0) { return {}; }

    std::uniform_int_distribution<std::size_t> source_distribution(0, kEnglishTexts.size() - 1);
    std::string output;
    output.reserve(target_length);

    while (output.size() < target_length) {
        const std::string_view fragment = kEnglishTexts[source_distribution(random_engine)];
        if (fragment.empty()) {
            throw_exception<std::invalid_argument>(
                "Text source contains an empty fragment.",
                std::source_location::current()
            );
        }

        const std::size_t remaining = target_length - output.size();
        const std::size_t to_copy   = std::min(fragment.size(), remaining);
        output.append(fragment.data(), to_copy);
    }

    return output;
}

std::string uuid(const bool include_hyphens) {
    std::mt19937_64&                       engine = get_random_engine();
    std::uniform_int_distribution<uint8_t> byte_distribution(0, 0xFF);

    std::array<uint8_t, 16> bytes{};
    for (auto& byte : bytes) { byte = byte_distribution(engine); }

    // RFC 4122 version 4 and variant 1.
    bytes[6] = static_cast<uint8_t>((bytes[6] & 0x0F) | 0x40);
    bytes[8] = static_cast<uint8_t>((bytes[8] & 0x3F) | 0x80);

    std::string output;
    output.reserve(include_hyphens ? 36 : 32);
    for (std::size_t i = 0; i < bytes.size(); ++i) {
        if (include_hyphens && (i == 4 || i == 6 || i == 8 || i == 10)) { output.push_back('-'); }
        write_hex_byte(output, bytes[i]);
    }
    return output;
}

}  // namespace faker::string
