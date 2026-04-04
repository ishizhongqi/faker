// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file datetime.cpp

#include "faker/datetime.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <locale>
#include <random>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "faker/types/enums.h"
#include "random_engine.h"
#include "validation.h"

namespace faker::datetime {

namespace {

constexpr std::string_view kDateFormat = "%Y-%m-%d";
constexpr std::string_view kTimeFormat = "%H:%M:%S";

enum class DateTimeFlag { Date, Time };

std::tm parse_time(
    const std::string&          dt,
    const DateTimeFlag          dt_flag,
    const std::source_location& location = std::source_location::current()
) {
    std::tm tm{};
    tm.tm_isdst = -1;

    if (dt_flag == DateTimeFlag::Date) {
        tm.tm_hour = 0;
        tm.tm_min  = 0;
        tm.tm_sec  = 0;
    } else {
        // Use a stable valid date to avoid dependence on current local date.
        tm.tm_year = 100;  // 2000
        tm.tm_mon  = 0;    // January
        tm.tm_mday = 1;
    }
    const std::string_view format = dt_flag == DateTimeFlag::Date ? kDateFormat : kTimeFormat;

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

bool is_allowed_weekday(const int weekday, const DaysOfWeek allowed) {
    if (weekday < 0 || weekday > 6) { return false; }

    static constexpr DaysOfWeek mapping[] = {
        DaysOfWeek::Sunday,
        DaysOfWeek::Monday,
        DaysOfWeek::Tuesday,
        DaysOfWeek::Wednesday,
        DaysOfWeek::Thursday,
        DaysOfWeek::Friday,
        DaysOfWeek::Saturday,
    };
    return (allowed & mapping[weekday]) != static_cast<DaysOfWeek>(0);
}

std::chrono::sys_days parse_sys_days(const std::string_view date_sv, const std::source_location& location) {
    const std::tm date_tm = parse_time(std::string(date_sv), DateTimeFlag::Date, location);
    const auto ymd = std::chrono::year{date_tm.tm_year + 1900} / std::chrono::month{static_cast<unsigned>(date_tm.tm_mon + 1)} /
                     std::chrono::day{static_cast<unsigned>(date_tm.tm_mday)};
    if (!ymd.ok()) { throw_exception<std::invalid_argument>("Invalid calendar date.", location); }
    return std::chrono::sys_days{ymd};
}

std::string format_date(const std::chrono::sys_days day) {
    const auto ymd = std::chrono::year_month_day{day};
    std::ostringstream stream;
    stream << std::setw(4) << std::setfill('0') << static_cast<int>(ymd.year()) << "-"
           << std::setw(2) << static_cast<unsigned>(ymd.month()) << "-"
           << std::setw(2) << static_cast<unsigned>(ymd.day());
    return stream.str();
}

int to_seconds_of_day(const std::tm& tm) {
    return tm.tm_hour * 3600 + tm.tm_min * 60 + tm.tm_sec;
}

std::string format_seconds_of_day(const int seconds_of_day) {
    const int hour   = seconds_of_day / 3600;
    const int minute = (seconds_of_day % 3600) / 60;
    const int second = seconds_of_day % 60;

    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << minute << ":" << std::setw(2)
           << second;
    return stream.str();
}

std::string get_date(
    const std::string_view      start,
    const std::string_view      end,
    const DaysOfWeek            days_of_week,
    const std::source_location& location = std::source_location::current()
) {
    const auto start_day = parse_sys_days(start, location);
    const auto end_day   = parse_sys_days(end, location);

    if (start_day > end_day) {
        throw_exception<std::invalid_argument>(
            "Invalid range: 'end' must be greater than 'start'.",
            location
        );
    }

    const auto span_days = static_cast<int>((end_day - start_day).count()) + 1;
    if (span_days <= 0) {
        throw_exception<std::invalid_argument>(
            "Invalid date range.",
            location
        );
    }

    std::vector<int> allowed_weekdays;
    allowed_weekdays.reserve(7);
    for (int weekday = 0; weekday < 7; ++weekday) {
        if (is_allowed_weekday(weekday, days_of_week)) { allowed_weekdays.push_back(weekday); }
    }
    if (allowed_weekdays.empty()) {
        throw_exception<std::runtime_error>(
            "No matching weekday in range '" + std::string(start) + "' to '" + std::string(end) + "'.",
            location
        );
    }

    std::mt19937_64& random_engine = get_random_engine();
    const int        start_weekday = static_cast<int>(std::chrono::weekday{start_day}.c_encoding());

    std::vector<std::pair<int, int>> weekday_offsets;
    weekday_offsets.reserve(allowed_weekdays.size());
    int total_candidates = 0;
    for (const int weekday : allowed_weekdays) {
        const int first_offset = (weekday - start_weekday + 7) % 7;
        if (first_offset >= span_days) { continue; }
        const int count = ((span_days - 1 - first_offset) / 7) + 1;
        weekday_offsets.emplace_back(first_offset, count);
        total_candidates += count;
    }

    if (total_candidates <= 0) {
        throw_exception<std::invalid_argument>(
            "No matching weekday in range '" + std::string(start) + "' to '" + std::string(end) + "'.",
            location
        );
    }

    std::uniform_int_distribution<int> pick_distribution(0, total_candidates - 1);
    int                                pick = pick_distribution(random_engine);

    int chosen_offset = 0;
    for (const auto [first_offset, count] : weekday_offsets) {
        if (pick < count) {
            chosen_offset = first_offset + pick * 7;
            break;
        }
        pick -= count;
    }

    return format_date(start_day + std::chrono::days(chosen_offset));
}

std::string get_time(
    const std::string_view      start,
    const std::string_view      end,
    const std::source_location& location = std::source_location::current()
) {
    const std::tm start_tm = parse_time(std::string(start), DateTimeFlag::Time, location);
    const std::tm end_tm   = parse_time(std::string(end), DateTimeFlag::Time, location);

    const int start_time = to_seconds_of_day(start_tm);
    const int end_time   = to_seconds_of_day(end_tm);
    if (start_time > end_time) {
        throw_exception<std::invalid_argument>(
            "Invalid range: 'end' must be greater than 'start'.",
            location
        );
    }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(start_time, end_time);
    const int                     random_time = distribution(random_engine);

    return format_seconds_of_day(random_time);
}

}  // namespace

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
