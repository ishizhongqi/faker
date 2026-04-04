// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_string.cpp

#include <faker/string.h>
#include <gtest/gtest.h>

#include <array>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "random_engine.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::string;

TEST(StringTest, ShouldGenerateEnumItem) {
    const std::string result = enum_item(std::to_array<std::string_view>({"a", "b", "c"}));
    ASSERT_TRUE(result == "a" || result == "b" || result == "c");
}

TEST(StringTest, ShouldGenerateEmptyWhenEnumsIsEmpty) {
    const std::string result = enum_item({});
    ASSERT_TRUE(result.empty());
}

TEST(StringTest, ShouldGenerateText) {
    const std::string result = text(10, 20);
    ASSERT_TRUE(result.size() >= 10 && result.size() <= 20);
}

TEST(StringTest, ShouldGenerateEmptyTextWhenRangeIsZero) { ASSERT_TRUE(text(0, 0).empty()); }

TEST(StringTest, ShouldThrowExceptionWhenNumberOfCharsStartIsGreaterThanNumberOfCharsEnd) {
    EXPECT_THROW(text(20, 10), std::invalid_argument);
}

TEST(StringTest, ShouldGenerateUuidWithHyphens) {
    const std::string result = uuid(true);
    ASSERT_TRUE(result.size() == 36);

    const std::regex pattern("^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
    ASSERT_TRUE(std::regex_match(result, pattern));
}

TEST(StringTest, ShouldGenerateUuidWithoutHyphens) {
    const std::string result = uuid(false);
    ASSERT_TRUE(result.size() == 32);

    const std::regex pattern("^[0-9a-f]{12}4[0-9a-f]{3}[89ab][0-9a-f]{15}$");
    ASSERT_TRUE(std::regex_match(result, pattern));
}

TEST(StringTest, ShouldGenerateDeterministicUuidWhenSeeded) {
    seed_random_engine(20260211ULL);
    const std::string first = uuid(true);
    seed_random_engine(20260211ULL);
    const std::string second = uuid(true);
    ASSERT_EQ(first, second);
}

TEST(StringTest, ShouldGenerateTextConcurrentlyWithinRange) {
    std::array<std::string, 2> results;
    std::thread                t1([&results]() { results[0] = text(32, 48); });
    std::thread                t2([&results]() { results[1] = text(32, 48); });
    t1.join();
    t2.join();

    ASSERT_GE(results[0].size(), 32);
    ASSERT_LE(results[0].size(), 48);
    ASSERT_GE(results[1].size(), 32);
    ASSERT_LE(results[1].size(), 48);
}
