// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_number.cpp

#include <gtest/gtest.h>

#include <regex>
#include <string>

#include "faker/number.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::number;

struct IntegerParam {
    int64_t     start;
    int64_t     end;
    std::string name;
};

struct UnsignedIntegerParam {
    uint64_t    start;
    uint64_t    end;
    std::string name;
};

struct DecimalParam {
    double      start;
    double      end;
    int         decimal_places;
    std::string name;
};

class IntegerTest : public TestWithParam<IntegerParam> {};

TEST_P(IntegerTest, ShouldGenerateIntegerInRange) {
    const auto [start, end, name] = GetParam();

    // Test with int32_t
    const auto int32_value = integer<int32_t>(static_cast<int32_t>(start), static_cast<int32_t>(end));
    ASSERT_GE(int32_value, static_cast<int32_t>(start));
    ASSERT_LE(int32_value, static_cast<int32_t>(end));

    // Test with int64_t
    const auto int64_value = integer<int64_t>(start, end);
    ASSERT_GE(int64_value, start);
    ASSERT_LE(int64_value, end);

    // Test with default int
    const int int_value = integer(static_cast<int>(start), static_cast<int>(end));
    ASSERT_GE(int_value, static_cast<int>(start));
    ASSERT_LE(int_value, static_cast<int>(end));
}

INSTANTIATE_TEST_SUITE_P(
    IntegerTests,
    IntegerTest,
    Values(
        IntegerParam{-1000, -10, "NegativeRange"},
        IntegerParam{10, 1000, "PositiveRange"},
        IntegerParam{0, 0, "ZeroRange"},
        IntegerParam{-1, 1, "SmallRange"},
        IntegerParam{-2147483647, 2147483647, "LargeRange"}
    ),
    [](const TestParamInfo<IntegerParam>& param_info) { return param_info.param.name; }
);

class UnsignedIntegerTest : public TestWithParam<UnsignedIntegerParam> {};

TEST_P(UnsignedIntegerTest, ShouldGenerateUnsignedIntegerInRange) {
    const auto [start, end, name] = GetParam();

    // Test with uint32_t
    const auto uint32_value = unsigned_integer<uint32_t>(static_cast<uint32_t>(start), static_cast<uint32_t>(end));
    ASSERT_GE(uint32_value, static_cast<uint32_t>(start));
    ASSERT_LE(uint32_value, static_cast<uint32_t>(end));

    // Test with uint64_t
    const auto uint64_value = unsigned_integer<uint64_t>(start, end);
    ASSERT_GE(uint64_value, start);
    ASSERT_LE(uint64_value, end);

    // Test with default unsigned int
    const unsigned int uint_value = unsigned_integer(static_cast<unsigned int>(start), static_cast<unsigned int>(end));
    ASSERT_GE(uint_value, static_cast<unsigned int>(start));
    ASSERT_LE(uint_value, static_cast<unsigned int>(end));
}

INSTANTIATE_TEST_SUITE_P(
    UnsignedIntegerTests,
    UnsignedIntegerTest,
    Values(
        UnsignedIntegerParam{0, 1000, "ZeroToThousand"},
        UnsignedIntegerParam{1000000, 2000000, "LargePositiveRange"},
        UnsignedIntegerParam{0, 0, "ZeroOnly"},
        UnsignedIntegerParam{1, 1, "OneOnly"},
        UnsignedIntegerParam{4294967295ULL - 1000, 4294967295ULL, "NearMaxUint32"}
    ),
    [](const TestParamInfo<UnsignedIntegerParam>& param_info) { return param_info.param.name; }
);

class DecimalTest : public TestWithParam<DecimalParam> {};

TEST_P(DecimalTest, ShouldGenerateDecimalInRange) {
    const auto [start, end, decimal_places, name] = GetParam();

    // Test with float
    const auto float_value = decimal<float>(static_cast<float>(start), static_cast<float>(end), decimal_places);
    const auto float_start = static_cast<float>(start);
    const auto float_end   = static_cast<float>(end);
    ASSERT_GE(float_value, float_start - 0.0001f);  // Allow for floating point precision
    ASSERT_LE(float_value, float_end + 0.0001f);

    // Test with double
    const auto double_value = decimal<double>(start, end, decimal_places);
    ASSERT_GE(double_value, start - 0.000000001);  // Allow for floating point precision
    ASSERT_LE(double_value, end + 0.000000001);

    // Test with default double
    const double default_double_value = decimal(start, end, decimal_places);
    ASSERT_GE(default_double_value, start - 0.000000001);
    ASSERT_LE(default_double_value, end + 0.000000001);
}

TEST_P(DecimalTest, ShouldGenerateValidDecimalString) {
    const auto [start, end, decimal_places, name] = GetParam();

    // Test with float
    const std::string float_string =
        decimal_string<float>(static_cast<float>(start), static_cast<float>(end), decimal_places);
    ASSERT_FALSE(float_string.empty());

    // Test with double
    const std::string double_string = decimal_string<double>(start, end, decimal_places);
    ASSERT_FALSE(double_string.empty());

    // Test with default double
    const std::string default_double_string = decimal_string(start, end, decimal_places);
    ASSERT_FALSE(default_double_string.empty());

    // Check decimal places format
    if (decimal_places > 0) {
        std::regex decimal_pattern(R"(^-?\d+\.\d{)" + std::to_string(decimal_places) + R"(}$)");
        ASSERT_TRUE(std::regex_match(default_double_string, decimal_pattern));
    } else {
        std::regex integer_pattern(R"(^-?\d+$)");
        ASSERT_TRUE(std::regex_match(default_double_string, integer_pattern));
    }

    // Check if value is within range
    const double parsed_value = std::stod(default_double_string);
    ASSERT_GE(parsed_value, start);
    ASSERT_LE(parsed_value, end);
}

INSTANTIATE_TEST_SUITE_P(
    DecimalTests,
    DecimalTest,
    Values(
        DecimalParam{-50.0, 50.0, 2, "DefaultDecimalPlaces"},
        DecimalParam{-100.0, 100.0, 5, "MoreDecimalPlaces"},
        DecimalParam{0.0, 0.0, 2, "ZeroDecimal"},
        DecimalParam{-1.0, 1.0, 10, "SmallRangeManyDecimals"},
        DecimalParam{1000.0, 2000.0, 0, "NoDecimalPlaces"}
    ),
    [](const TestParamInfo<DecimalParam>& param_info) { return param_info.param.name; }
);

TEST(NumberTest, ShouldHandleEdgeCases) {
    // Test with very large numbers
    const auto large_int = integer<int64_t>(91474836471LL - 10000, 91474836471LL);
    ASSERT_GE(large_int, 91474836471LL - 10000);
    ASSERT_LE(large_int, 91474836471LL);

    // Test with very small negative numbers
    const auto small_negative = integer<int64_t>(-21474836471LL, -21474836471LL + 10000);
    ASSERT_GE(small_negative, -21474836471LL);
    ASSERT_LE(small_negative, -21474836471LL + 10000);

    // Test decimal with zero range
    const double zero_decimal = decimal(0.0, 0.0, 5);
    ASSERT_NEAR(zero_decimal, 0.0, 0.00001);

    // Test decimal string with zero range
    const std::string zero_decimal_str = decimal_string(0.0, 0.0, 3);
    ASSERT_EQ(zero_decimal_str, "0.000");
}

TEST(NumberTest, ShouldThrowExceptionWhenStartGreaterThanEnd) {
    ASSERT_THROW(integer<int>(200, -100), std::invalid_argument);
    ASSERT_THROW(unsigned_integer<unsigned int>(200, 100), std::invalid_argument);
    ASSERT_THROW(decimal(10.0, 5.0, 2), std::invalid_argument);
    ASSERT_THROW(decimal_string(10.0, 5.0, 2), std::invalid_argument);
}

TEST(NumberTest, ShouldThrowExceptionWhenNoPossibleValue) {
    ASSERT_THROW(decimal_string(1.2, 1.3, 0), std::invalid_argument);
}
