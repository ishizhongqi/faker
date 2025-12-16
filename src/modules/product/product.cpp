// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file product.cpp

#include "faker/product.h"

#include <stdexcept>
#include <string>
#include <string_view>

#include "faker/types/enums.h"
#include "product_data.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::product {

std::string product_name(const Languages languages, const std::string_view keywords, const char delimiter) {
    CHECK_EMPTY(std::invalid_argument, keywords);

    const auto selected_language = pick_language(languages);

    const auto keywords_vector = split_and_trim(keywords, delimiter);
    const auto keyword         = pick_one<std::string>(keywords_vector);

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

std::string barcode(const BarcodeTypes barcode_types) {
    const auto selected_barcode = pick_barcode_type(barcode_types);

    std::string_view barcode_format;
    switch (selected_barcode) {
    case BarcodeTypes::EAN13: barcode_format = pick_one(kBarcodeEAN13Formats); break;
    case BarcodeTypes::EAN8 : barcode_format = pick_one(kBarcodeEAN8Formats); break;
    case BarcodeTypes::UPCA : barcode_format = pick_one(kBarcodeUPCAFormats); break;
    case BarcodeTypes::UPCE : barcode_format = pick_one(kBarcodeUPCEFormats); break;
    case BarcodeTypes::ISBN : barcode_format = pick_one(kBarcodeISBNFormats); break;
    }
    return replace_wildcard_to_digit(barcode_format);
}

}  // namespace faker::product
