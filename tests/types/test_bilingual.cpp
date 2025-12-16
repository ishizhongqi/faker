// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_bilingual.cpp

#include <gtest/gtest.h>

#include "faker/types/bilingual.h"
using namespace ::faker;

TEST(BilingualTest, Constructor) {
    Bilingual bilingual("测试", "Test");
    EXPECT_EQ(bilingual.original(), "测试");
    EXPECT_EQ(bilingual.translation(), "Test");
    bilingual.set_original("测试2");
    EXPECT_EQ(bilingual.original(), "测试2");
    EXPECT_EQ(bilingual.translation(), "Test");
    bilingual.set_translation("Test2");
    EXPECT_EQ(bilingual.original(), "测试2");
    EXPECT_EQ(bilingual.translation(), "Test2");
    bilingual.swap();
    EXPECT_EQ(bilingual.original(), "Test2");
    EXPECT_EQ(bilingual.translation(), "测试2");
    EXPECT_FALSE(bilingual.empty());
    bilingual.set_original("");
    bilingual.set_translation("");
    EXPECT_EQ(bilingual.original(), "");
    EXPECT_EQ(bilingual.translation(), "");
    EXPECT_TRUE(bilingual.empty());
}
