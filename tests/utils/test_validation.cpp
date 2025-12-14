// Copyright (c) 2025 Shizhongqi
// Licensed under the Apache License 2.0.
// See the LICENSE file in the project root for more information.

/// @file test_validation.cpp

#include <gtest/gtest.h>

#include "validation.h"

using namespace ::faker;

TEST(GetFunctionNameTest, DifferentSignatures) {
    ASSERT_EQ("MyNs::MyClass::get_name", get_function_name("const std::string& MyNs::MyClass::get_name() const"));
    ASSERT_EQ("N::C::calculate", get_function_name("unsigned long long N::C::calculate<T>() [with T=int]"));
    ASSERT_EQ("MyNs::MyClass::MyClass", get_function_name("MyNs::MyClass::MyClass(int)"));
    ASSERT_EQ("MyNs::MyClass::~MyClass", get_function_name("MyNs::MyClass::~MyClass()"));
    ASSERT_EQ("::free_function", get_function_name("void ::free_function()"));
}

template <typename T>
class ThrowExceptionTest : public ::testing::Test {};
using ExceptionTypes = ::testing::Types<std::runtime_error, std::invalid_argument, std::logic_error>;
TYPED_TEST_SUITE(ThrowExceptionTest, ExceptionTypes);

TYPED_TEST(ThrowExceptionTest, ThrowsWithCorrectTypeAndMessage) {
    using ExceptionT = TypeParam;
    ASSERT_THROW(throw_exception<ExceptionT>("test message"), ExceptionT);
}

TYPED_TEST(ThrowExceptionTest, CheckEmpty) {
    using ExceptionT = TypeParam;
    ASSERT_NO_THROW(check_empty<ExceptionT>("not empty", "value is not empty"));
    ASSERT_THROW(check_empty<ExceptionT>("", "value is empty"), ExceptionT);
}

TYPED_TEST(ThrowExceptionTest, CheckRangeIfRangeStartIsZero) {
    using ExceptionT = TypeParam;
    ASSERT_NO_THROW(check_range<ExceptionT>(0, "0", 1, "range_end"));
    ASSERT_THROW(check_range<ExceptionT>(0, "0", -1, "range_end"), ExceptionT);
}

TYPED_TEST(ThrowExceptionTest, CheckRange) {
    using ExceptionT = TypeParam;
    ASSERT_NO_THROW(check_range<ExceptionT>(3, "range_start", 10, "range_end"));
    ASSERT_THROW(check_range<ExceptionT>(10, "range_start", 3, "range_end"), ExceptionT);
}

TYPED_TEST(ThrowExceptionTest, CheckTimeIfMonthValid) {
    using ExceptionT = TypeParam;
    tm tm{};
    tm.tm_year = 2025 - 1900;
    tm.tm_mday = 1;
    tm.tm_mon  = 0 - 1;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon = 13 - 1;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon = 11 - 1;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));
}

TYPED_TEST(ThrowExceptionTest, CheckTimeIfDayValid) {
    using ExceptionT = TypeParam;
    tm tm{};
    tm.tm_year = 2025 - 1900;
    tm.tm_mon  = 0;
    tm.tm_mday = 0;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);

    // January has 31 days
    tm.tm_mon  = 0;
    tm.tm_mday = 32;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon  = 0;
    tm.tm_mday = 31;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));

    // April has 30 days
    tm.tm_mon  = 3;
    tm.tm_mday = 31;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon  = 3;
    tm.tm_mday = 30;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));

    // February has 28 days in non-leap year
    tm.tm_mon  = 1;
    tm.tm_mday = 29;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon  = 1;
    tm.tm_mday = 28;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));

    // February has 29 days in leap year
    tm.tm_year = 2024 - 1900;
    tm.tm_mon  = 1;
    tm.tm_mday = 30;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_mon  = 1;
    tm.tm_mday = 29;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));
}

TYPED_TEST(ThrowExceptionTest, CheckTimeIfTimeValid) {
    using ExceptionT = TypeParam;
    tm tm{};
    tm.tm_year = 2025 - 1900;
    tm.tm_mon  = 0;
    tm.tm_mday = 1;

    tm.tm_hour = -1;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_hour = 24;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_hour = 23;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));

    tm.tm_min = -1;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_min = 60;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_min = 59;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));

    tm.tm_sec = -1;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_sec = 60;
    ASSERT_THROW(check_time<ExceptionT>(tm), ExceptionT);
    tm.tm_sec = 59;
    ASSERT_NO_THROW(check_time<ExceptionT>(tm));
}
