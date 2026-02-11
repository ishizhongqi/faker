// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_product.cpp

#include <array>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include "faker/product.h"
#include "gtest/gtest.h"
#include "random_engine.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::product;

class ProductTest : public TestWithParam<Languages> {};

TEST_P(ProductTest, ShouldGenerateProductName) {
    const auto        languages = GetParam();
    const std::string generated_product_name =
        product_name(languages, std::to_array<std::string_view>({"Apple", "Orange"}));

    ASSERT_FALSE(generated_product_name.empty());

    const auto contains_keyword = generated_product_name.find("Apple") !=
                                  std::string::npos ||
                                  generated_product_name.find("Orange") != std::string::npos;

    ASSERT_TRUE(contains_keyword);
}

TEST_P(ProductTest, ShouldGenerateWhenNullOptional) {
    const auto        languages              = GetParam();
    const std::string generated_product_name = product_name(languages);

    ASSERT_FALSE(generated_product_name.empty());
}

TEST_P(ProductTest, ShouldThrowExceptionWhenKeywordsIsEmpty) {
    const auto                    languages      = GetParam();
    std::vector<std::string_view> empty_keywords = {};
    ASSERT_THROW({ product_name(languages, empty_keywords); }, std::invalid_argument);
}

TEST_P(ProductTest, ShouldThrowExceptionWhenKeywordsContainEmptyItem) {
    const auto languages = GetParam();
    ASSERT_THROW(product_name(languages, std::to_array<std::string_view>({"Phone", ""})), std::invalid_argument);
}

TEST_P(ProductTest, ShouldGenerateProductCategory) {
    const auto        languages                  = GetParam();
    const std::string generated_product_category = product_category(languages);
    ASSERT_FALSE(generated_product_category.empty());
}

TEST_P(ProductTest, ShouldGenerateColor) {
    const auto        languages       = GetParam();
    const std::string generated_color = color(languages);
    ASSERT_FALSE(generated_color.empty());
}

INSTANTIATE_TEST_SUITE_P(
    ProductTests,
    ProductTest,
    ValuesIn(
        std::vector<Languages>{
            Languages::English,
            Languages::SimplifiedChinese,
            Languages::TraditionalChinese,
            Languages::Japanese
        }
    ),
    [](const TestParamInfo<Languages>& param_info) { return to_string(param_info.param); }
);

TEST(ProductTest, ShouldGenerateSize) {
    const std::string result = size();
    EXPECT_FALSE(result.empty());
}

TEST(ProductTest, ShouldGenerateDeterministicProductNameWhenSeeded) {
    seed_random_engine(20260211ULL);
    const std::string first = product_name(Languages::English, std::to_array<std::string_view>({"Phone"}));
    seed_random_engine(20260211ULL);
    const std::string second = product_name(Languages::English, std::to_array<std::string_view>({"Phone"}));
    ASSERT_EQ(first, second);
}

class BarcodeTest : public TestWithParam<BarcodeTypes> {};

TEST_P(BarcodeTest, ShouldGenerateBarcode) {
    const auto        barcode_type      = GetParam();
    const std::string generated_barcode = barcode(barcode_type);
    ASSERT_FALSE(generated_barcode.empty());
}

TEST_P(BarcodeTest, ShouldGenerateUniqueBarcode) {
    const auto        barcode_type      = GetParam();
    const std::string generated_barcode = barcode(barcode_type, true);
    ASSERT_FALSE(generated_barcode.empty());
}

TEST(BarcodeTest, ShouldGenerateUniqueBarcodeAcrossThreads) {
    std::vector<std::string> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const std::string value = barcode(BarcodeTypes::EAN13, true);
            std::lock_guard<std::mutex> lock(generated_mutex);
            generated.push_back(value);
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);
    std::thread t4(worker);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::unordered_set<std::string> unique_values(generated.begin(), generated.end());
    ASSERT_EQ(unique_values.size(), generated.size());
}

INSTANTIATE_TEST_SUITE_P(
    BarcodeTests,
    BarcodeTest,
    ValuesIn(
        std::vector<BarcodeTypes>{
            BarcodeTypes::EAN8,
            BarcodeTypes::EAN13,
            BarcodeTypes::UPCA,
            BarcodeTypes::UPCE,
            BarcodeTypes::ISBN,
        }
    ),
    [](const TestParamInfo<BarcodeTypes>& param_info) { return to_string(param_info.param); }
);
