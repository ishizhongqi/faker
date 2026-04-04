// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_datetime.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <ctime>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <thread>

#include "faker/datetime.h"
#include "faker/types/enums.h"
#include "random_engine.h"
#include "string_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::datetime;

struct DateTimeParams {
    std::string start_date;
    std::string end_date;
    std::string start_time;
    std::string end_time;
    DaysOfWeek  days_of_week;
};

class DateTimeTest : public TestWithParam<DateTimeParams> {};

TEST_P(DateTimeTest, ShouldGenerateDate) {
    const auto [start_date, end_date, start_time, end_time, days_of_week] = GetParam();
    const std::string generated_date                                      = date(start_date, end_date, days_of_week);

    const std::regex date_pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    ASSERT_TRUE(std::regex_match(generated_date, date_pattern));

    ASSERT_TRUE(generated_date >= start_date);
    ASSERT_TRUE(generated_date <= end_date);
}

TEST_P(DateTimeTest, ShouldGenerateTime) {
    const auto [start_date, end_date, start_time, end_time, days_of_week] = GetParam();
    const std::string generated_time                                      = time(start_time, end_time);

    const std::regex time_pattern(R"(^\d{2}:\d{2}:\d{2}$)");
    ASSERT_TRUE(std::regex_match(generated_time, time_pattern));

    ASSERT_TRUE(generated_time >= start_time);
    ASSERT_TRUE(generated_time <= end_time);
}

TEST_P(DateTimeTest, ShouldGenerateDateTime) {
    const auto [start_date, end_date, start_time, end_time, days_of_week] = GetParam();
    const std::string generated_datetime = datetime::datetime(start_date, end_date, start_time, end_time, days_of_week);

    // Check datetime format: YYYY-MM-DD HH:MM:SS
    const std::regex datetime_pattern(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
    EXPECT_TRUE(std::regex_match(generated_datetime, datetime_pattern));

    // Extract date and time parts
    const std::string generated_date      = generated_datetime.substr(0, 10);
    const std::string generated_time_part = generated_datetime.substr(11, 8);

    // Check if the date is within the specified range
    EXPECT_TRUE(generated_date >= start_date);
    EXPECT_TRUE(generated_date <= end_date);

    // Check if the time is within the specified range
    EXPECT_TRUE(generated_time_part >= start_time);
    EXPECT_TRUE(generated_time_part <= end_time);
}

INSTANTIATE_TEST_SUITE_P(
    DateTimeTests,
    DateTimeTest,
    Values(
        DateTimeParams{
            "2020-01-01",
            "2020-12-31",
            "08:00:00",
            "17:00:00",
            DaysOfWeek::Monday | DaysOfWeek::Tuesday | DaysOfWeek::Wednesday | DaysOfWeek::Thursday | DaysOfWeek::Friday
        },
        DateTimeParams{"2020-01-01", "2020-12-31", "18:00:00", "23:59:59", DaysOfWeek::Saturday | DaysOfWeek::Sunday},
        DateTimeParams{"2020-01-01", "2020-01-07", "12:00:00", "12:00:00", DaysOfWeek::Monday},
        DateTimeParams{"2023-03-12", "2023-03-15", "00:00:00", "23:59:59", DaysOfWeek::Monday},
        DateTimeParams{"2023-03-15", "2023-03-15", "00:00:00", "23:59:59", DaysOfWeek::Wednesday}
    ),
    [](const TestParamInfo<DateTimeTest::ParamType>& param_info) {
        const auto& param = param_info.param;

        std::string name = remove_characters(
            "Between" + param.start_date + param.start_time + "And" + param.end_date + param.end_time,
            "-: "
        );

        if ((param.days_of_week & DaysOfWeek::Monday) != static_cast<DaysOfWeek>(0)) name += "Monday";
        if ((param.days_of_week & DaysOfWeek::Tuesday) != static_cast<DaysOfWeek>(0)) name += "Tuesday";
        if ((param.days_of_week & DaysOfWeek::Wednesday) != static_cast<DaysOfWeek>(0)) name += "Wednesday";
        if ((param.days_of_week & DaysOfWeek::Thursday) != static_cast<DaysOfWeek>(0)) name += "Thursday";
        if ((param.days_of_week & DaysOfWeek::Friday) != static_cast<DaysOfWeek>(0)) name += "Friday";
        if ((param.days_of_week & DaysOfWeek::Saturday) != static_cast<DaysOfWeek>(0)) name += "Saturday";
        if ((param.days_of_week & DaysOfWeek::Sunday) != static_cast<DaysOfWeek>(0)) name += "Sunday";

        return name;
    }
);

TEST(DateTimeTest, ShouldThrowExceptionForEmptyDates) {
    EXPECT_THROW(date("", "2020-01-01"), std::invalid_argument);
    EXPECT_THROW(date("2020-01-01", ""), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForInvalidDateFormat) {
    EXPECT_THROW(date("invalid-date", "2020-01-01"), std::invalid_argument);
    EXPECT_THROW(date("2020-01-01", "invalid-date"), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForUnknownWeekday) {
    EXPECT_THROW(date("2020-01-01", "2020-02-01", static_cast<DaysOfWeek>(0)), std::runtime_error);
}

TEST(DateTimeTest, ShouldThrowExceptionForEmptyTimes) {
    EXPECT_THROW(time("", "12:00:00"), std::invalid_argument);
    EXPECT_THROW(time("12:00:00", ""), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForInvalidTimeFormat) {
    EXPECT_THROW(time("invalid-time", "12:00:00"), std::invalid_argument);
    EXPECT_THROW(time("12:00:00", "invalid-time"), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForInvalidDateRange) {
    EXPECT_THROW(date("2020-12-31", "2020-01-01"), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForInvalidTimeRange) {
    EXPECT_THROW(time("12:00:00", "11:00:00"), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForNoMatchingWeekdays) {
    // January 1-3, 2020: Wednesday, Thursday, Friday
    EXPECT_THROW(date("2020-01-01", "2020-01-03", DaysOfWeek::Monday), std::invalid_argument);
}

TEST(DateTimeTest, ShouldThrowExceptionForEmptyDatesAndTimes) {
    EXPECT_THROW(
        datetime::datetime("", "2020-01-01", "08:00:00", "17:00:00", DaysOfWeek::Monday),
        std::invalid_argument
    );
    EXPECT_THROW(
        datetime::datetime("2020-01-01", "", "08:00:00", "17:00:00", DaysOfWeek::Monday),
        std::invalid_argument
    );
    EXPECT_THROW(
        datetime::datetime("2020-01-01", "2020-01-01", "", "17:00:00", DaysOfWeek::Monday),
        std::invalid_argument
    );
    EXPECT_THROW(
        datetime::datetime("2020-01-01", "2020-01-01", "08:00:00", "", DaysOfWeek::Monday),
        std::invalid_argument
    );
}

TEST(DateTimeTest, ShouldRespectSpecificWeekdayFilter) {
    const std::string generated_date = date("2024-01-01", "2024-01-31", DaysOfWeek::Monday);

    std::tm tm{};
    std::istringstream iss(generated_date);
    iss >> std::get_time(&tm, "%Y-%m-%d");
    ASSERT_FALSE(iss.fail());
    tm.tm_isdst = -1;
    ASSERT_NE(std::mktime(&tm), -1);
    ASSERT_EQ(tm.tm_wday, 1);
}

TEST(DateTimeTest, ShouldGenerateDeterministicDatetimeWhenSeeded) {
    seed_random_engine(20260211ULL);
    const std::string first = datetime::datetime("2020-01-01", "2020-12-31", "08:00:00", "17:00:00");
    seed_random_engine(20260211ULL);
    const std::string second = datetime::datetime("2020-01-01", "2020-12-31", "08:00:00", "17:00:00");
    ASSERT_EQ(first, second);
}

TEST(DateTimeTest, ShouldGenerateDateConcurrentlyWithinRange) {
    std::array<std::string, 2> results;
    std::thread                t1(
        [&results]() { results[0] = date("2020-01-01", "2020-12-31", DaysOfWeek::Monday | DaysOfWeek::Friday); }
    );
    std::thread                t2(
        [&results]() { results[1] = date("2020-01-01", "2020-12-31", DaysOfWeek::Monday | DaysOfWeek::Friday); }
    );
    t1.join();
    t2.join();

    ASSERT_GE(results[0], "2020-01-01");
    ASSERT_LE(results[0], "2020-12-31");
    ASSERT_GE(results[1], "2020-01-01");
    ASSERT_LE(results[1], "2020-12-31");
}
