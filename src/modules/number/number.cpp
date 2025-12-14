// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file number.cpp

#include "faker/number.h"

#include <concepts>
#include <iomanip>
#include <random>
#include <sstream>

#include "random_engine.h"
#include "validation.h"

namespace faker::number {

// Generate a random decimal string.
static std::string GetDecimalString(
    const double                start,
    const double                end,
    const int                   decimal_places,
    const std::source_location& location = std::source_location::current()
) {
    std::mt19937_64& rng = get_random_engine();

    const double factor       = std::pow(10, decimal_places);
    const auto   scaled_start = static_cast<int64_t>(std::ceil(start * factor));
    const auto   scaled_end   = static_cast<int64_t>(std::floor(end * factor));

    if (scaled_start > scaled_end) {
        throw_exception<std::invalid_argument>(
            "No possible value in range with the specified decimal_places.",
            location
        );
    }

    std::uniform_int_distribution dist(scaled_start, scaled_end);
    const int64_t                 raw_value = dist(rng);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimal_places) << static_cast<double>(raw_value) / factor;
    return oss.str();
}

template <std::integral T>
    requires(std::is_signed_v<T>)
T integer(T start, T end) {
    CHECK_RANGE_T(std::invalid_argument, T, start, end);

    std::mt19937_64&                 random_engine = get_random_engine();
    std::uniform_int_distribution<T> distribution(start, end);

    return distribution(random_engine);
}
template int8_t  number::integer<int8_t>(int8_t, int8_t);
template int16_t number::integer<int16_t>(int16_t, int16_t);
template int32_t number::integer<int32_t>(int32_t, int32_t);
template int64_t number::integer<int64_t>(int64_t, int64_t);

template <std::integral T>
    requires(std::is_unsigned_v<T>)
T unsigned_integer(T start, T end) {
    CHECK_RANGE_T(std::invalid_argument, T, start, end);

    std::mt19937_64&                 random_engine = get_random_engine();
    std::uniform_int_distribution<T> distribution(start, end);

    return static_cast<T>(distribution(random_engine));
}
template uint8_t  number::unsigned_integer<uint8_t>(uint8_t, uint8_t);
template uint16_t number::unsigned_integer<uint16_t>(uint16_t, uint16_t);
template uint32_t number::unsigned_integer<uint32_t>(uint32_t, uint32_t);
template uint64_t number::unsigned_integer<uint64_t>(uint64_t, uint64_t);

template <std::floating_point T>
T decimal(T start, T end, const int decimal_places) {
    CHECK_RANGE_T(std::invalid_argument, T, start, end);
    CHECK_RANGE(std::invalid_argument, 0, decimal_places);

    return static_cast<T>(std::stod(GetDecimalString(start, end, decimal_places)));
}
template float       number::decimal<float>(float, float, int);
template double      number::decimal<double>(double, double, int);
template long double number::decimal<long double>(long double, long double, int);

template <std::floating_point T>
std::string decimal_string(T start, T end, const int decimal_places) {
    CHECK_RANGE_T(std::invalid_argument, T, start, end);
    CHECK_RANGE(std::invalid_argument, 0, decimal_places);

    return GetDecimalString(start, end, decimal_places);
}
template std::string number::decimal_string<float>(float, float, int);
template std::string number::decimal_string<double>(double, double, int);
template std::string number::decimal_string<long double>(long double, long double, int);

}  // namespace faker::number
