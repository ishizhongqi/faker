// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file product.h

#ifndef FAKER_PRODUCT_H
#define FAKER_PRODUCT_H

#include <string>

#include "faker/internal/macros.h"
#include "faker/types/enums.h"

namespace faker::product {

/// @brief Generates a random product name.
/// @param languages The languages of prefixes or suffixes. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param keywords The list of product keywords.
///                 Defaults to "Cherry,Orange,Pluots,Grape,Kiwi,Mango,Raspberry,Strawberry".
///                 If empty, throw error.
/// @param delimiter Delimiter of keywords.
/// @return A product name.
/// @code
/// faker::product::product_name();  // "Mango Ultra"
/// faker::product::product_name(faker::Languages::SimplifiedChinese, "苹果,橘猫,爱新", ',');  // "橘猫 旗舰版"
/// @endcode
FAKER_EXPORT std::string product_name(
    Languages languages       = Languages::English,
    std::string_view keywords = "Cherry,Orange,Pluots,Grape,Kiwi,Mango,Raspberry,Strawberry",
    char delimiter            = ','
);

/// @brief Generates a random product category.
/// @param languages The languages of product category. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A product category.
/// @code
/// faker::product::product_category();  // "Health & Baby Care"
/// faker::product::product_category(faker::Languages::SimplifiedChinese |
///                                 faker::Languages::TraditionalChinese |
///                                 faker::Languages::Japanese);  // "映画およびテレビ用品"
/// @endcode
FAKER_EXPORT std::string product_category(Languages languages = Languages::English);

/// @brief Generates a random color string.
/// @param languages The languages of product category. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A color string.
/// @code
/// faker::product::color();  // "Sepia"
/// faker::product::color(faker::Languages::SimplifiedChinese |
///                       faker::Languages::TraditionalChinese |
///                       faker::Languages::Japanese);  // "青銅色"
/// @endcode
FAKER_EXPORT std::string color(Languages languages = Languages::English);

/// @brief Generates a random size string.
/// @return A size string.
/// @code
/// faker::product::size();  // "XL"
/// @endcode
FAKER_EXPORT std::string size();

/// @brief Generates a random barcode string.
/// @param barcode_types The types of barcode. Defaults to BarcodeTypes::EAN13.
/// @return A barcode string.
/// @code
/// faker::product::barcode();  // "1347237267997"
/// faker::product::barcode(faker::BarcodeTypes::EAN8 |
///                         faker::BarcodeTypes::UPCA |
///                         faker::BarcodeTypes::UPCE |
///                         faker::BarcodeTypes::ISBN);  // "9798471761315"
/// @endcode
FAKER_EXPORT std::string barcode(BarcodeTypes barcode_types = BarcodeTypes::EAN13);

}  // namespace faker::product

#endif  // FAKER_PRODUCT_H
