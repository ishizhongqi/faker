// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file datetime.cpp

#include "faker/datetime.h"

#include <chrono>
#include <iomanip>
#include <locale>
#include <random>
#include <regex>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>

#include "faker/types/enums.h"
#include "random_engine.h"
#include "validation.h"

namespace faker::datetime {

static std::string g_date_format = "%Y-%m-%d";
static std::string g_time_format = "%H:%M:%S";

enum class DateTimeFlag { Date, Time };

static std::tm now() {
    const std::time_t now = std::time(nullptr);
    return *std::localtime(&now);
}

// Parse date string to tm
static std::tm parse_time(
    const std::string&          dt,
    const DateTimeFlag          dt_flag,
    const std::source_location& location = std::source_location::current()
) {
    std::tm tm{};
    tm          = now();
    tm.tm_isdst = -1;

    std::string_view format = g_time_format;

    if (dt_flag == DateTimeFlag::Date) {
        tm.tm_year = 0;
        tm.tm_mon  = 0;
        tm.tm_mday = 0;
        format     = g_date_format;
    }

    std::istringstream iss{dt};
    iss.imbue(std::locale::classic());
    iss >> std::get_time(&tm, std::string(format).c_str());
    if (iss.fail()) {
        throw_exception<std::invalid_argument>(
            "Invalid format: '" + dt + "' (expected " + std::string(format) + ").",
            location
        );
    }
    iss >> std::ws;
    if (!iss.eof()) { throw_exception<std::invalid_argument>("Trailing characters in `" + dt + "`.", location); }

    CHECK_TIME_EX(std::invalid_argument, tm, location);

    return tm;
}

// Check if the given tm is in the allowed weekday
static bool is_allowed_weekday(const std::tm& tm, const DaysOfWeek allowed) {
    static constexpr DaysOfWeek mapping[] = {
        DaysOfWeek::Sunday,
        DaysOfWeek::Monday,
        DaysOfWeek::Tuesday,
        DaysOfWeek::Wednesday,
        DaysOfWeek::Thursday,
        DaysOfWeek::Friday,
        DaysOfWeek::Saturday,
    };
    return (allowed & mapping[tm.tm_wday]) != static_cast<DaysOfWeek>(0);
}

// Format date tm to string
static std::string format_time(const std::tm& tm, const DateTimeFlag dt_flag) {
    std::ostringstream     stream;
    const std::string_view format = dt_flag == DateTimeFlag::Date ? g_date_format : g_time_format;
    stream << std::put_time(&tm, std::string(format).c_str());
    return stream.str();
}

static std::string get_date(
    const std::string_view      start,
    const std::string_view      end,
    const DaysOfWeek            days_of_week,
    const std::source_location& location = std::source_location::current()
) {
    auto start_tm = parse_time(std::string(start), DateTimeFlag::Date, location);
    auto end_tm   = parse_time(std::string(end), DateTimeFlag::Date, location);

    const auto start_date = std::mktime(&start_tm);
    const auto end_date   = std::mktime(&end_tm);

    CHECK_RANGE_EX(std::invalid_argument, start_date, end_date, location);

    constexpr std::time_t seconds_per_day = 24 * 3600;
    const auto            span_days       = static_cast<int>((end_date - start_date) / seconds_per_day) + 1;

    std::mt19937_64& random_engine = get_random_engine();

    // If span_days < 7, we can use a simple loop to find a valid date
    if (span_days < 7) {
        std::vector<std::time_t> candidates;
        candidates.reserve(span_days);

        for (int i = 0; i < span_days; ++i) {
            std::time_t tt = start_date + i * seconds_per_day;
            if (std::tm tm = *std::localtime(&tt); is_allowed_weekday(tm, days_of_week)) { candidates.push_back(tt); }
        }

        if (candidates.empty()) {
            throw_exception<std::invalid_argument>(
                "No matching weekday in range '" + std::string(start) + "' to '" + std::string(end) + "'.",
                location
            );
        }

        std::uniform_int_distribution<size_t> distribution(0, candidates.size() - 1);
        const std::tm                         random_tm = *std::localtime(&candidates[distribution(random_engine)]);
        return format_time(random_tm, DateTimeFlag::Date);
    }

    // If span_days >= 7
    std::uniform_int_distribution distribution(start_date, end_date);
    const auto                    random_time = distribution(random_engine);
    const std::tm                 random_tm   = *std::localtime(&random_time);
    if (is_allowed_weekday(random_tm, days_of_week)) { return format_time(random_tm, DateTimeFlag::Date); }
    for (int offset = 1; offset < span_days; ++offset) {
        // try forward
        std::time_t forward = random_time + offset * seconds_per_day;
        if (forward <= end_date) {
            std::tm tm_forward = *std::localtime(&forward);
            if (is_allowed_weekday(tm_forward, days_of_week)) { return format_time(tm_forward, DateTimeFlag::Date); }
        }
        // try backward
        std::time_t backward = random_time - offset * seconds_per_day;
        if (backward >= start_date) {
            std::tm tm_backward = *std::localtime(&backward);
            if (is_allowed_weekday(tm_backward, days_of_week)) { return format_time(tm_backward, DateTimeFlag::Date); }
        }
    }

    throw_exception<std::runtime_error>("Unable to find a valid weekday in the expanded search.", location);
}

std::string get_time(
    const std::string_view      start,
    const std::string_view      end,
    const std::source_location& location = std::source_location::current()
) {
    auto start_tm = parse_time(std::string(start), DateTimeFlag::Time, location);
    auto end_tm   = parse_time(std::string(end), DateTimeFlag::Time, location);

    const auto start_time = std::mktime(&start_tm);
    const auto end_time   = std::mktime(&end_tm);

    CHECK_RANGE_EX(std::invalid_argument, start_time, end_time, location);

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(start_time, end_time);
    const auto                    random_time = distribution(random_engine);
    const std::tm                 random_tm   = *std::localtime(&random_time);

    return format_time(random_tm, DateTimeFlag::Time);
}

std::string date(const std::string_view start_date, const std::string_view end_date, const DaysOfWeek days_of_week) {
    CHECK_EMPTY(std::invalid_argument, start_date);
    CHECK_EMPTY(std::invalid_argument, end_date);

    return get_date(start_date, end_date, days_of_week);
}

std::string time(const std::string_view start_time, const std::string_view end_time) {
    CHECK_EMPTY(std::invalid_argument, start_time);
    CHECK_EMPTY(std::invalid_argument, end_time);
    return get_time(start_time, end_time);
}

std::string datetime(
    const std::string_view start_date,
    const std::string_view end_date,
    const std::string_view start_time,
    const std::string_view end_time,
    const DaysOfWeek       days_of_week
) {
    CHECK_EMPTY(std::invalid_argument, start_date);
    CHECK_EMPTY(std::invalid_argument, end_date);
    CHECK_EMPTY(std::invalid_argument, start_time);
    CHECK_EMPTY(std::invalid_argument, end_time);

    return get_date(start_date, end_date, days_of_week) + " " + get_time(start_time, end_time);
}

}  // namespace faker::datetime
