// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_business.cpp

#include <gtest/gtest.h>

#include "business_data.h"
#include "faker/business.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::business;

class BusinessTest : public TestWithParam<Languages> {};

TEST_P(BusinessTest, CompanyNameWithSpecificLanguages) {
    const auto language               = GetParam();
    const auto generated_company_name = company_name(language);
    ASSERT_FALSE(generated_company_name.original().empty() && generated_company_name.translation().empty());
}

TEST_P(BusinessTest, DepartmentWithSpecificLanguages) {
    const auto language             = GetParam();
    const auto generated_department = department(language);
    ASSERT_FALSE(generated_department.empty());
}

TEST_P(BusinessTest, IndustryWithSpecificLanguages) {
    const auto language           = GetParam();
    const auto generated_industry = industry(language);
    ASSERT_FALSE(generated_industry.empty());
}

TEST_P(BusinessTest, ClassCompanyWithSpecificLanguages) {
    const auto language          = GetParam();
    auto       generated_company = Company(language);
    ASSERT_FALSE(generated_company.name().original().empty() && generated_company.name().translation().empty());
    ASSERT_FALSE(generated_company.industry().empty());

    generated_company.reroll();
    ASSERT_FALSE(generated_company.name().original().empty() && generated_company.name().translation().empty());
    ASSERT_FALSE(generated_company.industry().empty());
}

INSTANTIATE_TEST_SUITE_P(
    TestBusinessWithLanguages,
    BusinessTest,
    ValuesIn(
        std::vector<Languages>(
            {Languages::English, Languages::SimplifiedChinese, Languages::TraditionalChinese, Languages::Japanese}
        )
    ),
    [](const TestParamInfo<Languages>& paramInfo) { return to_string(paramInfo.param); }
);
