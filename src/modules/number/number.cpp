// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file number.cpp

#include "faker/number.h"

#include <cmath>
#include <concepts>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>

#include "random_engine.h"
#include "validation.h"

namespace faker::number {

namespace {

constexpr int kMaxSupportedDecimalPlaces = 18;

template <typename T>
void check_range_typed(
    const T                     start,
    const T                     end,
    const std::source_location& location = std::source_location::current()
) {
    if (start > end) {
        throw_exception<std::invalid_argument>(
            "Invalid range: 'end' must be greater than 'start'.",
            location
        );
    }
}

struct DecimalSample {
    int64_t     raw_value;
    long double factor;
};

template <std::floating_point T>
DecimalSample sample_decimal_scaled(
    const T                     start,
    const T                     end,
    const int                   decimal_places,
    const std::source_location& location = std::source_location::current()
) {
    check_range_typed(start, end, location);
    if (decimal_places < 0) {
        throw_exception<std::invalid_argument>(
            "Invalid range: 'decimal_places' must be greater than 0.",
            location
        );
    }
    if (decimal_places > kMaxSupportedDecimalPlaces) {
        throw_exception<std::invalid_argument>(
            "decimal_places exceeds supported precision for this generator.",
            location
        );
    }
    if (!std::isfinite(static_cast<long double>(start)) || !std::isfinite(static_cast<long double>(end))) {
        throw_exception<std::invalid_argument>(
            "start and end must be finite numbers.",
            location
        );
    }

    const long double factor = std::pow(10.0L, decimal_places);
    if (!std::isfinite(factor) || factor <= 0.0L) {
        throw_exception<std::invalid_argument>(
            "Unable to compute a finite scaling factor for decimal_places.",
            location
        );
    }

    const long double scaled_start_ld = std::ceil(static_cast<long double>(start) * factor);
    const long double scaled_end_ld   = std::floor(static_cast<long double>(end) * factor);

    if (!std::isfinite(scaled_start_ld) || !std::isfinite(scaled_end_ld)) {
        throw_exception<std::invalid_argument>(
            "No possible value in range with the specified decimal_places.",
            location
        );
    }

    constexpr long double kInt64Min = static_cast<long double>(std::numeric_limits<int64_t>::min());
    constexpr long double kInt64Max = static_cast<long double>(std::numeric_limits<int64_t>::max());
    if (scaled_start_ld < kInt64Min || scaled_end_ld > kInt64Max) {
        throw_exception<std::invalid_argument>(
            "No possible value in range with the specified decimal_places.",
            location
        );
    }

    const auto scaled_start = static_cast<int64_t>(scaled_start_ld);
    const auto scaled_end   = static_cast<int64_t>(scaled_end_ld);

    if (scaled_start > scaled_end) {
        throw_exception<std::invalid_argument>(
            "No possible value in range with the specified decimal_places.",
            location
        );
    }

    std::mt19937_64& rng = get_random_engine();
    std::uniform_int_distribution<int64_t> dist(scaled_start, scaled_end);
    return {
        .raw_value = dist(rng),
        .factor    = factor,
    };
}

template <std::floating_point T>
std::string to_decimal_string(const DecimalSample sample, const int decimal_places) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimal_places) << static_cast<T>(sample.raw_value / sample.factor);
    return oss.str();
}

}  // namespace

template <std::integral T>
    requires(std::is_signed_v<T>)
T integer(T start, T end) {
    check_range_typed(start, end);

    std::mt19937_64&                 random_engine = get_random_engine();
    std::uniform_int_distribution<T> distribution(start, end);

    return distribution(random_engine);
}
// unsigned char and signed char are not supported
// template int8_t  number::integer<int8_t>(int8_t, int8_t);
template FAKER_EXPORT int16_t number::integer<int16_t>(int16_t, int16_t);
template FAKER_EXPORT int32_t number::integer<int32_t>(int32_t, int32_t);
template FAKER_EXPORT int64_t number::integer<int64_t>(int64_t, int64_t);

template <std::integral T>
    requires(std::is_unsigned_v<T>)
T unsigned_integer(T start, T end) {
    check_range_typed(start, end);

    std::mt19937_64&                 random_engine = get_random_engine();
    std::uniform_int_distribution<T> distribution(start, end);

    return static_cast<T>(distribution(random_engine));
}
// unsigned char and signed char are not supported
// template uint8_t  number::unsigned_integer<uint8_t>(uint8_t, uint8_t);
template FAKER_EXPORT uint16_t number::unsigned_integer<uint16_t>(uint16_t, uint16_t);
template FAKER_EXPORT uint32_t number::unsigned_integer<uint32_t>(uint32_t, uint32_t);
template FAKER_EXPORT uint64_t number::unsigned_integer<uint64_t>(uint64_t, uint64_t);

template <std::floating_point T>
T decimal(T start, T end, const int decimal_places) {
    const DecimalSample sample = sample_decimal_scaled(start, end, decimal_places);
    return static_cast<T>(sample.raw_value / sample.factor);
}
template FAKER_EXPORT float       number::decimal<float>(float, float, int);
template FAKER_EXPORT double      number::decimal<double>(double, double, int);
template FAKER_EXPORT long double number::decimal<long double>(long double, long double, int);

template <std::floating_point T>
std::string decimal_string(T start, T end, const int decimal_places) {
    const DecimalSample sample = sample_decimal_scaled(start, end, decimal_places);
    return to_decimal_string<T>(sample, decimal_places);
}
template FAKER_EXPORT std::string number::decimal_string<float>(float, float, int);
template FAKER_EXPORT std::string number::decimal_string<double>(double, double, int);
template FAKER_EXPORT std::string number::decimal_string<long double>(long double, long double, int);

}  // namespace faker::number
