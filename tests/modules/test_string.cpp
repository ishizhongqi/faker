// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_string.cpp

#include <faker/string.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <array>

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

TEST(StringTest, ShouldThrowExceptionWhenNumberOfCharsStartIsGreaterThanNumberOfCharsEnd) {
    EXPECT_THROW(text(20, 10), std::invalid_argument);
}

TEST(StringTest, ShouldGenerateUuidWithHyphens) {
    const std::string result = uuid(true);
    ASSERT_TRUE(result.size() == 36);
}

TEST(StringTest, ShouldGenerateUuidWithoutHyphens) {
    const std::string result = uuid(false);
    ASSERT_TRUE(result.size() == 32);
}
