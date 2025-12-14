// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file number.h

#ifndef FAKER_NUMBER_H
#define FAKER_NUMBER_H

#include <concepts>
#include <string>

#include "faker/internal/macros.h"

namespace faker::number {

/// @brief Generate a random integer between start and end.
///
/// This function supports all signed integer types.
///
/// If start and end are of different types, the type of end needs to be specified.
///     E.g., @code Integer<long>(0, 9999999999999)@endcode.
///
/// If an unsigned integer needs to be generated, use @code UnsignedInteger()@endcode.
///
/// @tparam T Integer type (e.g., int32_t, int64_t).
/// @param start Minimum value.
/// @param end Maximum value.
/// @return An integer.
/// @code
/// faker::number::integer(-1000, -10);  // -64
/// faker::number::integer(10, 1000);  // 698
/// faker::number::integer<int64_t>(-21474836471, 91474836471);  // 23868252086
/// @endcode
template <std::integral T>
    requires(std::is_signed_v<T>)
FAKER_EXPORT T integer(T start, T end);

/// @brief Generate a random integer between start and end.
///
/// This function supports all unsigned integer types.
///
/// If start and end are of different types, the type of end needs to be specified.
///     E.g., @code UnsignedInteger<long>(0, 9999999999999)@endcode.
///
/// @tparam T Unsigned integer type (e.g., uint32_t, uint64_t).
/// @param start Minimum value.
/// @param end Maximum value.
/// @return An unsigned integer.
/// @code
/// faker::number::unsigned_integer<uint16_t>(1000, 32000);  // 13327
/// faker::number::unsigned_integer(100000000U, 2147483647U);  // 1842120397
/// @endcode
template <std::integral T>
    requires(std::is_unsigned_v<T>)
FAKER_EXPORT T unsigned_integer(T start, T end);

/// @brief Generate a random decimal number between start and end.
///
/// @code Decimal()@endcode may not generate numbers with exactly decimal_places digits
///     after the decimal point due to floating-point precision limits.
/// If exact decimal places are required, please use @code DecimalString()@endcode instead.
///
/// @tparam T Floating point type (e.g., float, double).
/// @param start Minimum value.
/// @param end Maximum value.
/// @param decimal_places Number of decimal places.
/// @return A decimal number.
/// @code
/// faker::number::decimal(-50.0, 50.0);  // -10.03
/// faker::number::decimal(-50.0, 50.0, 3);  // 43.707
/// @endcode
template <std::floating_point T>
FAKER_EXPORT T decimal(T start, T end, int decimal_places = 2);

/// @brief Generate a random decimal number string between start and end.
///
/// @tparam T Floating point type (e.g., float, double).
/// @param start Minimum value.
/// @param end Maximum value.
/// @param decimal_places Number of decimal places.
/// @return A decimal number string
/// @code
/// faker::number::decimal_string(-100.0, 100.0, 10);  // "32.7797482557"
/// @endcode
template <std::floating_point T>
FAKER_EXPORT std::string decimal_string(T start, T end, int decimal_places = 2);
}  // namespace faker::number

#endif  // FAKER_NUMBER_H
