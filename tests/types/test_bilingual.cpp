// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_bilingual.cpp

#include <gtest/gtest.h>

#include "faker/types/bilingual.h"
using namespace ::faker;

TEST(BilingualTest, StringParam) {
    Bilingual bilingual("测试", "Test");
    ASSERT_EQ(bilingual.original(), "测试");
    ASSERT_EQ(bilingual.translation(), "Test");

    auto str = std::string(bilingual);
    ASSERT_EQ(str, "测试");

    bilingual.set_original("测试2");
    ASSERT_EQ(bilingual.original(), "测试2");
    ASSERT_EQ(bilingual.translation(), "Test");

    auto str2 = std::string_view(bilingual);
    ASSERT_EQ(str2, "测试2");

    bilingual.set_translation("Test2");
    ASSERT_EQ(bilingual.original(), "测试2");
    ASSERT_EQ(bilingual.translation(), "Test2");

    bilingual.swap();
    ASSERT_EQ(bilingual.original(), "Test2");
    ASSERT_EQ(bilingual.translation(), "测试2");
    ASSERT_FALSE(bilingual.empty());

    bilingual.set_original("");
    bilingual.set_translation("");
    ASSERT_EQ(bilingual.original(), "");
    ASSERT_EQ(bilingual.translation(), "");
    ASSERT_TRUE(bilingual.empty());
}

TEST(BilingualTest, StructureParam) {
    constexpr BilingualView bv("测试", "Test");
    const Bilingual         bilingual(bv);
    ASSERT_EQ(bilingual.original(), "测试");
    ASSERT_EQ(bilingual.translation(), "Test");
}
