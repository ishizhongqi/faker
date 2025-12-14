// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file datetime.h

#ifndef FAKER_DATETIME_H
#define FAKER_DATETIME_H

#include <string>

#include "faker/internal/macros.h"
#include "faker/types/enums.h"

namespace faker::datetime {

/// @brief Generates a random date string between start_date and end_date, filtering by specified days of the week.
/// @param start_date The start date string in the format of "%Y-%m-%d". Defaults to "1970-01-01".
///                   If empty, throw error.
/// @param end_date The end date string in the format of "%Y-%m-%d". Defaults to "2050-12-31".
///                 If empty, throw error.
/// @param days_of_week Days of the week. Defaults to DaysOfWeek::Sunday through DaysOfWeek::Saturday.
///                     If multiple days are specified, bitwise(bitwise_or |) operator can be used.
/// @return A date string in the format of "%Y-%m-%d".
/// @code
/// faker::datetime::date();  // "2011-08-23"
/// faker::datetime::date("2023-01-01", "2023-12-31");  // "2023-02-09"
/// faker::datetime::date("2023-01-01", "2023-12-31", faker::DaysOfWeek::Monday);  // "2023-07-26"
/// @endcode
FAKER_EXPORT std::string date(
    std::string_view start_date = "1970-01-01",
    std::string_view end_date   = "2050-12-31",
    DaysOfWeek days_of_week     = DaysOfWeek::Sunday |
                              DaysOfWeek::Monday |
                              DaysOfWeek::Tuesday |
                              DaysOfWeek::Wednesday |
                              DaysOfWeek::Thursday |
                              DaysOfWeek::Friday |
                              DaysOfWeek::Saturday
);

/// @brief Generates a random time string between start_time and end_time.
/// @param start_time The start time string in the format of "%H:%M:%S". Defaults to "00:00:00".
///                   If empty, throw error.
/// @param end_time The end time string in the format of "%H:%M:%S". Defaults to "23:59:59".
///                 If empty, throw error.
/// @return A time string in the format of "%H:%M:%S".
/// @code
/// faker::datetime::time();  // "16:59:12"
/// faker::datetime::time("08:00:00", "17:00:00");  // "12:19:28"
/// @endcode
FAKER_EXPORT std::string time(std::string_view start_time = "00:00:00", std::string_view end_time = "23:59:59");

/// @brief Generates a random datetime string between start_date and end_date,
///        filtering by specified days of the week and between start_time and end_time.
/// @param start_date The start date string in the format of "%Y-%m-%d".
///                   If empty, throw error.
/// @param end_date The end date string in the format of "%Y-%m-%d".
///                 If empty, throw error.
/// @param start_time The start time string in the format of "%H:%M:%S".
///                   If empty, throw error.
/// @param end_time The end time string in the format of "%H:%M:%S".
///                 If empty, throw error.
/// @param days_of_week Days of the week. Defaults to DaysOfWeek::Sunday through DaysOfWeek::Saturday.
///                     If multiple days are specified, bitwise(bitwise_or |) operator can be used.
/// @return A datetime string in the format of "%Y-%m-%d %H:%M:%S".
/// @code
/// faker::datetime::datetime();  // "2012-04-12 17:04:23"
/// faker::datetime::datetime("2023-01-01", "2023-12-31", "08:00:00", "17:00:00");  // "2023-04-18 09:45:12"
/// faker::datetime::datetime("2023-01-01", "2023-12-31", "08:00:00", "17:00:00",  faker::DaysOfWeek::Monday);
/// // "2023-10-02 15:00:35"
/// @endcode
FAKER_EXPORT std::string datetime(
    std::string_view start_date = "1970-01-01",
    std::string_view end_date   = "2050-12-31",
    std::string_view start_time = "00:00:00",
    std::string_view end_time   = "23:59:59",
    DaysOfWeek days_of_week     = DaysOfWeek::Sunday |
                              DaysOfWeek::Monday |
                              DaysOfWeek::Tuesday |
                              DaysOfWeek::Wednesday |
                              DaysOfWeek::Thursday |
                              DaysOfWeek::Friday |
                              DaysOfWeek::Saturday
);

}  // namespace faker::datetime

#endif  // FAKER_DATETIME_H
