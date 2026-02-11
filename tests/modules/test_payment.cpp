// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_payment.cpp

#include <gtest/gtest.h>

#include <array>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include "faker/payment.h"
#include "faker/types/enums.h"
#include "random_engine.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::payment;

struct CardTypeParam {
    Languages   languages;
    CardTypes   card_types;
    std::string name;
};

struct CardNumberParam {
    CardTypes   card_types;
    std::string name;
};

struct CardDateParam {
    std::string_view start_month;
    std::string_view end_month;
    std::string      name;
};

struct CardParam {
    Languages        languages;
    CardTypes        card_types;
    std::string_view start_month;
    std::string_view end_month;
    std::string      name;
};

TEST(PaymentTest, ShouldGeneratePaymentMethod) {
    const std::string generated_payment_method =
        payment_method(std::to_array<std::string_view>({"Credit Card", "PayPal", "Apple Pay"}));
    ASSERT_FALSE(generated_payment_method.empty());
}

TEST(PaymentTest, ShouldGeneratePaymentMethodWhenNullOptional) {
    const std::string generated_payment_method = payment_method();
    ASSERT_FALSE(generated_payment_method.empty());
}

TEST(PaymentTest, ShouldThrowExceptionWhenPaymentMethodsIsEmpty) {
    std::vector<std::string_view> empty_payment_methods = {};
    ASSERT_THROW(payment_method(empty_payment_methods), std::invalid_argument);
}

TEST(PaymentTest, ShouldThrowExceptionWhenPaymentMethodsContainsEmptyItem) {
    ASSERT_THROW(
        payment_method(std::to_array<std::string_view>({"Credit Card", ""})),
        std::invalid_argument
    );
}

class CardTypeLanguagesTest : public TestWithParam<Languages> {};

TEST_P(CardTypeLanguagesTest, ShouldGenerateCardType) {
    const auto        languages           = GetParam();
    const std::string generated_card_type = card_type(languages);
    ASSERT_FALSE(generated_card_type.empty());
}

TEST_P(CardTypeLanguagesTest, ShouldGenerateCard) {
    const auto languages = GetParam();
    Card       card(languages);
    ASSERT_FALSE(card.type().empty());
    ASSERT_FALSE(card.number().empty());
    ASSERT_FALSE(card.date().empty());
    ASSERT_EQ(card.payment_method(), "Credit Card");
    card.reroll();
    ASSERT_FALSE(card.type().empty());
    ASSERT_FALSE(card.number().empty());
    ASSERT_FALSE(card.date().empty());
    ASSERT_EQ(card.payment_method(), "Credit Card");
}

INSTANTIATE_TEST_SUITE_P(
    CardTypeLanguagesTests,
    CardTypeLanguagesTest,
    ValuesIn(
        std::vector<Languages>(
            {Languages::English, Languages::SimplifiedChinese, Languages::TraditionalChinese, Languages::Japanese}
        )
    ),
    [](const TestParamInfo<Languages>& param_info) { return to_string(param_info.param); }
);

class CardTypesTest : public TestWithParam<CardTypes> {};

TEST_P(CardTypesTest, ShouldGenerateCardType) {
    const auto        card_types          = GetParam();
    const std::string generated_card_type = card_type(Languages::English, card_types);
    ASSERT_FALSE(generated_card_type.empty());
}

TEST_P(CardTypesTest, ShouldGenerateCardNumber) {
    const auto        card_types            = GetParam();
    const std::string generated_card_number = card_number(card_types);

    ASSERT_FALSE(generated_card_number.empty());

    for (const char c : generated_card_number) { ASSERT_TRUE(std::isdigit(c)); }
}

TEST_P(CardTypesTest, ShouldGenerateUniqueCardNumber) {
    const auto        card_types            = GetParam();
    const std::string generated_card_number = card_number(card_types, true);
    ASSERT_FALSE(generated_card_number.empty());
    for (const char c : generated_card_number) { ASSERT_TRUE(std::isdigit(c)); }
}

TEST_P(CardTypesTest, ShouldGenerateCard) {
    const auto card_types = GetParam();
    const Card card(Languages::English, card_types);
    ASSERT_FALSE(card.type().empty());
    ASSERT_FALSE(card.number().empty());
    ASSERT_FALSE(card.date().empty());
}

INSTANTIATE_TEST_SUITE_P(
    CardTypesTests,
    CardTypesTest,
    ValuesIn(
        std::vector<CardTypes>(
            {CardTypes::AmericanExpress, CardTypes::JCB, CardTypes::MasterCard, CardTypes::UnionPay, CardTypes::Visa}
        )
    ),
    [](const TestParamInfo<CardTypes>& param_info) { return to_string(param_info.param); }
);

TEST(CardTest, ShouldGenerateCardDate) {
    const std::string generated_card_date = card_date("01/01", "12/10");
    ASSERT_FALSE(generated_card_date.empty());
    ASSERT_TRUE(std::regex_match(generated_card_date, std::regex(R"(^(0[1-9]|1[0-2])/[0-9]{2}$)")));
}

TEST(CardTest, ShouldThrowExceptionWhenDateIsEmpty) {
    ASSERT_THROW(card_date("", "12/10"), std::invalid_argument);
    ASSERT_THROW(card_date("01/01", ""), std::invalid_argument);
}

TEST(CardTest, ShouldThrowExceptionWhenDateIsInvalid) {
    ASSERT_THROW(card_date("invalid", "12/10"), std::invalid_argument);
    ASSERT_THROW(card_date("01/01", "invalid"), std::invalid_argument);
    ASSERT_THROW(card_date("13/01", "12/10"), std::invalid_argument);
    ASSERT_THROW(card_date("00/01", "12/10"), std::invalid_argument);
}

TEST(CardTest, ShouldThrowExceptionWhenStartDateIsAfterEndDate) {
    ASSERT_THROW(card_date("12/10", "01/01"), std::invalid_argument);
}

TEST(CardTest, ShouldGenerateExactCardDateWhenRangeCollapsed) {
    ASSERT_EQ(card_date("02/24", "02/24"), "02/24");
}

TEST(CardTest, ShouldGenerateDeterministicCardDateWhenSeeded) {
    seed_random_engine(20260211ULL);
    const std::string first = card_date("01/00", "12/50");
    seed_random_engine(20260211ULL);
    const std::string second = card_date("01/00", "12/50");
    ASSERT_EQ(first, second);
}

TEST(CardTest, ShouldGenerateUniqueCardNumberAcrossThreads) {
    std::vector<std::string> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const std::string value = card_number(CardTypes::MasterCard, true);
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
