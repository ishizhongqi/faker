// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file product.cpp

#include "faker/product.h"

#include <algorithm>
#include <format>
#include <optional>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "faker/types/enums.h"
#include "permutation_generator.h"
#include "product_data.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::product {

static constexpr std::size_t barcode_format_count = kBarcodeEAN13Formats.size() +
                                                    kBarcodeEAN8Formats.size() +
                                                    kBarcodeUPCAFormats.size() +
                                                    kBarcodeUPCEFormats.size() +
                                                    kBarcodeISBNFormats.size();

static std::vector<PermutationGenerator> barcode_pg_vector(barcode_format_count);
static std::vector<uint64_t> barcode_capacity(barcode_format_count);
static std::vector<uint8_t>  barcode_wildcards(barcode_format_count);

std::string product_name(const Languages languages, const std::optional<std::span<const std::string_view>> keywords) {
    std::string_view keyword;
    if (keywords.has_value()) {
        check_empty<std::invalid_argument>(keywords.value(), "keywords");
        keyword = pick_one(keywords.value());
    } else {
        keyword = pick_one(kProductNameDefaultKeywords);
    }

    const auto selected_language = pick_language(languages);

    std::string_view prefix_or_suffix;
    switch (selected_language) {
    case Languages::English: prefix_or_suffix = pick_one(kEnglishProductNamePrefixesAndSuffixes); break;
    case Languages::SimplifiedChinese:
        prefix_or_suffix = pick_one(kSimplifiedChineseProductNamePrefixesAndSuffixes);
        break;
    case Languages::TraditionalChinese:
        prefix_or_suffix = pick_one(kTraditionalChineseProductNamePrefixesAndSuffixes);
        break;
    case Languages::Japanese: prefix_or_suffix = pick_one(kJapaneseProductNamePrefixesAndSuffixes); break;
    }

    return replace_placeholder(prefix_or_suffix, keyword);
}

std::string product_category(const Languages languages) {
    const auto selected_language = pick_language(languages);

    std::string_view category;
    switch (selected_language) {
    case Languages::English           : category = pick_one(kEnglishProductCategories); break;
    case Languages::SimplifiedChinese : category = pick_one(kSimplifiedChineseProductCategories); break;
    case Languages::TraditionalChinese: category = pick_one(kTraditionalChineseProductCategories); break;
    case Languages::Japanese          : category = pick_one(kJapaneseProductCategories); break;
    }

    return std::string(category);
}

std::string color(const Languages languages) {
    const auto       selected_language = pick_language(languages);
    std::string_view color;
    switch (selected_language) {
    case Languages::English           : color = pick_one(kEnglishColors); break;
    case Languages::SimplifiedChinese : color = pick_one(kSimplifiedChineseColors); break;
    case Languages::TraditionalChinese: color = pick_one(kTraditionalChineseColors); break;
    case Languages::Japanese          : color = pick_one(kJapaneseColors); break;
    }
    return std::string(color);
}

std::string size() {
    return std::string(pick_one(kProductSizes));
}

std::string barcode(const BarcodeTypes barcode_types, const bool unique) {
    const auto selected_barcode = pick_barcode_type(barcode_types);

    std::size_t      index;
    std::size_t      seq_index = 0;
    std::string_view pattern;

    switch (selected_barcode) {
    case BarcodeTypes::EAN13:
        index     = pick_index(kBarcodeEAN13Formats);
        seq_index = index;
        pattern   = kBarcodeEAN13Formats[index];
        break;
    case BarcodeTypes::EAN8:
        index     = pick_index(kBarcodeEAN8Formats);
        seq_index = index + kBarcodeEAN13Formats.size();
        pattern   = kBarcodeEAN8Formats[index];
        break;
    case BarcodeTypes::UPCA:
        index     = pick_index(kBarcodeUPCAFormats);
        seq_index = index + kBarcodeEAN13Formats.size() + kBarcodeEAN8Formats.size();
        pattern   = kBarcodeUPCAFormats[index];
        break;
    case BarcodeTypes::UPCE:
        index     = pick_index(kBarcodeUPCEFormats);
        seq_index = index + kBarcodeEAN13Formats.size() + kBarcodeEAN8Formats.size() + kBarcodeUPCAFormats.size();
        pattern   = kBarcodeUPCEFormats[index];
        break;
    case BarcodeTypes::ISBN:
        index     = pick_index(kBarcodeISBNFormats);
        seq_index = index +
                    kBarcodeEAN13Formats.size() +
                    kBarcodeEAN8Formats.size() +
                    kBarcodeUPCAFormats.size() +
                    kBarcodeUPCEFormats.size();
        pattern = kBarcodeISBNFormats[index];
        break;
    }

    std::string barcode;

    if (unique) {
        if (barcode_capacity[seq_index] == 0) {
            const uint64_t wildcard_count = std::count(pattern.begin(), pattern.end(), '#');
            uint64_t       capacity       = 1;
            for (size_t i = 0; i < wildcard_count; ++i) { capacity *= 10; }
            barcode_capacity[seq_index] = capacity;
            barcode_wildcards[seq_index] = static_cast<uint8_t>(wildcard_count);
        }
        const uint64_t capacity = barcode_capacity[seq_index];
        const uint64_t wildcard_count = barcode_wildcards[seq_index];
        if (!barcode_pg_vector[seq_index].is_initialized()) {
            barcode_pg_vector[seq_index].initialize(0, capacity - 1);
        }
        const uint64_t    seq     = barcode_pg_vector[seq_index].next_uint64();
        const std::string seq_str = std::format("{:0{}}", seq, wildcard_count);
        barcode                   = replace_wildcard_with_sequence(pattern, '#', seq_str);
    } else {
        barcode = replace_wildcard_with_digit(pattern);
    }

    return barcode;
}

}  // namespace faker::product
