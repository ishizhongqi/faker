// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file enums.h

#ifndef FAKER_ENUMS_H
#define FAKER_ENUMS_H

#include "faker/internal/bitwise_operators.h"

namespace faker {

/// @brief Days of the week.
///  If you want to use multiple days, you can use bitwise(bitwise_or |) operators.
enum class DaysOfWeek {
    Sunday    = 1 << 0,  // Sunday
    Monday    = 1 << 1,  // Monday
    Tuesday   = 1 << 2,  // Tuesday
    Wednesday = 1 << 3,  // Wednesday
    Thursday  = 1 << 4,  // Thursday
    Friday    = 1 << 5,  // Friday
    Saturday  = 1 << 6,  // Saturday
};
template <>
struct enable_bitwise_operators<DaysOfWeek> : std::true_type {};

/// @brief Languages.
///  If you want to use multiple languages, you can use bitwise(bitwise_or |) operators.
enum class Languages {
    English            = 1 << 0,  // English
    SimplifiedChinese  = 1 << 1,  // Simplified Chinese
    TraditionalChinese = 1 << 2,  // Traditional Chinese
    Japanese           = 1 << 3,  // Japanese
};
template <>
struct enable_bitwise_operators<Languages> : std::true_type {};

/// @brief Regions
///  If you want to use multiple regions, you can use bitwise(bitwise_or |) operators.
enum class Regions {
    UnitedStates  = 1 << 0,  // United States
    UnitedKingdom = 1 << 1,  // United Kingdom
    China         = 1 << 2,  // China
    Japan         = 1 << 3,  // Japan
};
template <>
struct enable_bitwise_operators<Regions> : std::true_type {};

/// @brief Country Codes Standard
enum class CountryCodesStandard {
    None,                // None, output as name
    ISO_3166_1_alpha_2,  // ISO 3166-1 alpha-2 codes
    ISO_3166_1_alpha_3,  // ISO 3166-1 alpha-3 codes
};

/// @brief Gender
///  If you want to use multiple genders, you can use bitwise(bitwise_or |) operators.
enum class Genders { M = 1 << 0, F = 1 << 1 };
template <>
struct enable_bitwise_operators<Genders> : std::true_type {};

/// @brief Credit card types
///  If you want to use multiple card types, you can use bitwise(bitwise_or |) operators.
enum class CardTypes {
    AmericanExpress = 1 << 0,  // American Express
    JCB             = 1 << 1,  // JCB
    MasterCard      = 1 << 2,  // MasterCard
    UnionPay        = 1 << 3,  // UnionPay
    Visa            = 1 << 4,  // Visa
};
template <>
struct enable_bitwise_operators<CardTypes> : std::true_type {};

/// @brief Barcode types
///  If you want to use multiple barcode types, you can use bitwise(bitwise_or |) operators.
enum class BarcodeTypes {
    EAN8  = 1 << 0,  // EAN-8
    EAN13 = 1 << 1,  // EAN-13
    UPCA  = 1 << 2,  // UPC-A
    UPCE  = 1 << 3,  // UPC-E
    ISBN  = 1 << 4,  // ISBN
};
template <>
struct enable_bitwise_operators<BarcodeTypes> : std::true_type {};

/// @brief IP address types
enum class IpAddressType {
    IPv4,  // IPv4
    IPv6,  // IPv6
};

/// @brief Operating systems
///  If you want to use multiple operating systems, you can use bitwise(bitwise_or |) operators.
enum class OperatingSystems {
    Windows = 1 << 0,  // Windows
    macOS   = 1 << 1,  // macOS
    Linux   = 1 << 2,  // Linux
};
template <>
struct enable_bitwise_operators<OperatingSystems> : std::true_type {};

}  // namespace faker

#endif  // FAKER_ENUMS_H
