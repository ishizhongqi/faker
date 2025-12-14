// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string.cpp

#include "faker/string.h"

#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "random_engine.h"
#include "random_helper.h"
#include "string_data.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::string {

std::string enum_item(const std::string_view enums, const char delimiter) {
    if (enums.empty()) { return ""; }
    auto domains_vector = split_and_trim(enums, delimiter);
    return pick_one<std::string>(domains_vector);
}

std::string text(const unsigned int number_of_chars_start, const unsigned int number_of_chars_end) {
    CHECK_RANGE(std::invalid_argument, number_of_chars_start, number_of_chars_end);

    std::mt19937_64&                      random_engine = get_random_engine();
    std::uniform_int_distribution<size_t> source_distribution(0, kEnglishTexts.size() - 1);
    auto                                  selected = std::string(kEnglishTexts[source_distribution(random_engine)]);

    while (static_cast<int>(selected.size()) < number_of_chars_start) { selected += selected; }

    const unsigned int max_length = std::min(static_cast<unsigned int>(selected.size()), number_of_chars_end);
    std::uniform_int_distribution length_distribution(number_of_chars_start, max_length);
    const unsigned int            target_length = length_distribution(random_engine);

    return selected.substr(0, target_length);
}

std::string uuid(const bool include_hyphens) {
    std::mt19937_64&                        engine = get_random_engine();
    std::uniform_int_distribution<uint32_t> distribution(0, 0xFFFFFFFF);

    const uint32_t data1 = distribution(engine);
    const auto     data2 = static_cast<uint16_t>(distribution(engine));
    auto           data3 = static_cast<uint16_t>(distribution(engine));

    // Set version to 4 ---- 0100xxxx
    data3 = data3 & 0x0FFF | 0x4000;

    auto data4 = static_cast<uint16_t>(distribution(engine));

    // Set variant bits to 10xxxxxx
    data4 = data4 & 0x3FFF | 0x8000;

    const uint64_t data5 = static_cast<uint64_t>(distribution(engine)) << 32 | distribution(engine);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    if (include_hyphens) {
        oss << std::setw(8) << data1 << "-" << std::setw(4) << data2 << "-" << std::setw(4) << data3 << "-" << std::setw(4) << data4 << "-" << std::setw(12) << (data5 & 0xFFFFFFFFFFFF);
    } else {
        oss << std::setw(8) << data1 << std::setw(4) << data2 << std::setw(4) << data3 << std::setw(4) << data4 << std::setw(12) << (data5 & 0xFFFFFFFFFFFF);
    }

    return oss.str();
}

}  // namespace faker::string
