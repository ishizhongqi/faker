// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_business.cpp

#include <gtest/gtest.h>

#include <array>
#include <mutex>
#include <thread>
#include <vector>

#include "business_data.h"
#include "faker/business.h"
#include "random_engine.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::business;

class BusinessTest : public TestWithParam<Languages> {};

TEST_P(BusinessTest, ShouldGenerateCompanyName) {
    const auto language               = GetParam();
    const auto generated_company_name = company_name(language);
    ASSERT_FALSE(generated_company_name.original().empty() && generated_company_name.translation().empty());
}

TEST_P(BusinessTest, ShouldGenerateDepartment) {
    const auto language             = GetParam();
    const auto generated_department = department(language);
    ASSERT_FALSE(generated_department.empty());
}

TEST_P(BusinessTest, ShouldGenerateIndustry) {
    const auto language           = GetParam();
    const auto generated_industry = industry(language);
    ASSERT_FALSE(generated_industry.empty());
}

TEST_P(BusinessTest, ShouldGenerateCompany) {
    const auto language          = GetParam();
    auto       generated_company = Company(language);
    ASSERT_FALSE(generated_company.name().original().empty() && generated_company.name().translation().empty());
    ASSERT_FALSE(generated_company.industry().empty());

    generated_company.reroll();
    ASSERT_FALSE(generated_company.name().original().empty() && generated_company.name().translation().empty());
    ASSERT_FALSE(generated_company.industry().empty());
}

INSTANTIATE_TEST_SUITE_P(
    BusinessTests,
    BusinessTest,
    ValuesIn(
        std::vector<Languages>(
            {Languages::English, Languages::SimplifiedChinese, Languages::TraditionalChinese, Languages::Japanese}
        )
    ),
    [](const TestParamInfo<Languages>& param_info) { return to_string(param_info.param); }
);

TEST(BusinessTest, ShouldHaveCompleteIndustryMappingsForAllLanguages) {
    constexpr std::array all_industries = {
        Industries::Catering,
        Industries::Consulting,
        Industries::Electronics,
        Industries::Engineering,
        Industries::FinancialServices,
        Industries::Industrial,
        Industries::InformationTechnology,
        Industries::LandedProperty,
        Industries::Logistic,
        Industries::Manufacturing,
        Industries::Pharmaceutical,
        Industries::Telecommunication,
        Industries::Trading,
    };
    constexpr std::array all_languages = {
        Languages::English,
        Languages::SimplifiedChinese,
        Languages::TraditionalChinese,
        Languages::Japanese,
    };

    for (const auto language : all_languages) {
        const auto industries_it = kIndustries.find(language);
        ASSERT_NE(industries_it, kIndustries.end());
        const auto words_it = kBusinessWords.find(language);
        ASSERT_NE(words_it, kBusinessWords.end());

        for (const auto industry : all_industries) {
            ASSERT_NE(industries_it->second.find(industry), industries_it->second.end());
            const auto industry_words_it = words_it->second.find(industry);
            ASSERT_NE(industry_words_it, words_it->second.end());
            ASSERT_FALSE(industry_words_it->second.empty());
        }
    }
}

TEST(BusinessTest, ShouldGenerateDeterministicCompanyNameWhenSeeded) {
    seed_random_engine(20260211ULL);
    const Bilingual first = company_name(Languages::English);
    seed_random_engine(20260211ULL);
    const Bilingual second = company_name(Languages::English);
    ASSERT_EQ(first.original(), second.original());
    ASSERT_EQ(first.translation(), second.translation());
}

TEST(BusinessTest, ShouldGenerateCompanyConcurrently) {
    std::vector<Company> companies;
    companies.reserve(400);
    std::mutex companies_mutex;

    auto worker = [&companies, &companies_mutex]() {
        for (int i = 0; i < 100; ++i) {
            Company company(Languages::English);
            std::lock_guard<std::mutex> lock(companies_mutex);
            companies.push_back(company);
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

    ASSERT_EQ(companies.size(), 400U);
    for (const auto& company : companies) {
        ASSERT_FALSE(company.name().original().empty());
        ASSERT_FALSE(company.name().translation().empty());
        ASSERT_FALSE(company.industry().empty());
    }
}
