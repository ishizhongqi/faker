// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file validation.h

#ifndef FAKER_VALIDATION_H
#define FAKER_VALIDATION_H

#include <ctime>
#include <source_location>
#include <stdexcept>
#include <string>
#include <string_view>

namespace faker {

std::string get_function_name(std::string_view function_name);

template <typename E>
[[noreturn]] void throw_exception(
    const std::string&          message,
    const std::source_location& location = std::source_location::current()
) {
    const std::string function_name = location.function_name();
    throw E(get_function_name(function_name) + ": " + message);
}

template <typename E>
void check_empty(
    const std::string_view      value,
    const std::string_view      name,
    const std::source_location& location = std::source_location::current()
) {
    if (value.empty()) {
        throw_exception<E>("Invalid string: '" + std::string(name) + "' must not be empty.", location);
    }
}

#define CHECK_EMPTY_EX(exception_type, argument, location) check_empty<exception_type>(argument, #argument, location)
#define CHECK_EMPTY(exception_type, argument)              CHECK_EMPTY_EX(exception_type, argument, std::source_location::current())

template <typename E, typename T = int32_t>
void check_range(
    const T                     range_start,
    const std::string_view      range_start_name,
    const T                     range_end,
    const std::string_view      range_end_name,
    const std::source_location& location = std::source_location::current()
) {
    if (range_start == 0 && range_start_name == "0" && range_end < range_start) {
        throw_exception<E>(
            "Invalid range: '" +
                std::string(range_end_name) +
                "' must be greater than 0."
                " (Current: " +
                std::to_string(range_start) +
                ")",
            location
        );
    }

    if (range_start > range_end) {
        throw_exception<E>(
            "Invalid range: '" +
                std::string(range_end_name) +
                "' must be greater than '" +
                std::string(range_start_name) +
                "'."
                " (Current: " +
                std::to_string(range_start) +
                ", " +
                std::to_string(range_end) +
                ")",
            location
        );
    }
}

#define CHECK_RANGE_EX(exception_type, range_start, range_end, location) \
    check_range<exception_type>(range_start, #range_start, range_end, #range_end, location)
#define CHECK_RANGE(exception_type, range_start, range_end) \
    CHECK_RANGE_EX(exception_type, range_start, range_end, std::source_location::current())
#define CHECK_RANGE_T_EX(exception_type, T, range_start, range_end, location) \
    check_range<exception_type, T>(range_start, #range_start, range_end, #range_end, location)
#define CHECK_RANGE_T(exception_type, T, range_start, range_end) \
    CHECK_RANGE_EX(exception_type, range_start, range_end, std::source_location::current())

template <typename E>
void check_time(const tm& time, const std::source_location& location = std::source_location::current()) {
    const int year   = time.tm_year + 1900;
    const int month  = time.tm_mon + 1;
    const int day    = time.tm_mday;
    const int hour   = time.tm_hour;
    const int minute = time.tm_min;
    const int second = time.tm_sec;

    if (month < 1 || month > 12) {
        throw_exception<E>(
            "Invalid date: Month must be between 1 and 12."
            " (Current: " +
                std::to_string(month) +
                ")",
            location
        );
    }

    constexpr int days_in_month[] = {
        31,  // Jan
        28,  // Feb
        31,  // Mar
        30,  // Apr
        31,  // May
        30,  // Jun
        31,  // Jul
        31,  // Aug
        30,  // Sep
        31,  // Oct
        30,  // Nov
        31   // Dec
    };
    const bool is_leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    const int  max_day = days_in_month[month - 1] + (month == 2 && is_leap ? 1 : 0);
    if (day < 1 || day > max_day) {
        throw_exception<E>(
            "Invalid date: Day in month(" +
                std::to_string(month) +
                ") must be between 1 and " +
                std::to_string(max_day) +
                "."
                " (Current: " +
                std::to_string(day) +
                ")",
            location
        );
    }

    if (hour < 0 || hour > 23) {
        throw_exception<E>(
            "Invalid time: Hour must be between 0 and 23."
            " (Current: " +
                std::to_string(hour) +
                ")",
            location
        );
    }

    if (minute < 0 || minute > 59) {
        throw_exception<E>(
            "Invalid time: Minute must be between 0 and 59."
            " (Current: " +
                std::to_string(minute) +
                ")",
            location
        );
    }

    if (second < 0 || second > 59) {
        throw_exception<E>(
            "Invalid time: Second must be between 0 and 59."
            " (Current: " +
                std::to_string(second) +
                ")",
            location
        );
    }
}

#define CHECK_TIME_EX(exception_type, tm, location) check_time<exception_type>(tm, location)
#define CHECK_TIME(exception_type, tm)              CHECK_TIME_EX(exception_type, tm, std::source_location::current())

}  // namespace faker

#endif  // FAKER_VALIDATION_H
