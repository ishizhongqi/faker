// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_person.cpp

#include <gtest/gtest.h>

#include <array>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

#include "faker/person.h"
#include "faker/types/enums.h"
#include "random_engine.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace ::faker::person;

class PersonLanguagesTest : public TestWithParam<Languages> {};

TEST_P(PersonLanguagesTest, ShouldGenerateMaleFirstName) {
    const auto      languages            = GetParam();
    const Bilingual generated_first_name = first_name(languages, Genders::M);
    ASSERT_FALSE(generated_first_name.original().empty());
    ASSERT_FALSE(generated_first_name.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateFemaleFirstName) {
    const auto      languages            = GetParam();
    const Bilingual generated_first_name = first_name(languages, Genders::F);
    ASSERT_FALSE(generated_first_name.original().empty());
    ASSERT_FALSE(generated_first_name.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateLastName) {
    const auto      languages           = GetParam();
    const Bilingual generated_last_name = last_name(languages);
    ASSERT_FALSE(generated_last_name.original().empty());
    ASSERT_FALSE(generated_last_name.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateFullName) {
    const auto      languages           = GetParam();
    const Bilingual generated_full_name = full_name(languages);
    ASSERT_FALSE(generated_full_name.original().empty());
    ASSERT_FALSE(generated_full_name.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateGender) {
    const auto        languages        = GetParam();
    const std::string generated_gender = gender(languages);
    ASSERT_FALSE(generated_gender.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateMaleTitle) {
    const auto        languages       = GetParam();
    const std::string generated_title = title(languages, Genders::M);
    ASSERT_FALSE(generated_title.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateFemaleTitle) {
    const auto        languages       = GetParam();
    const std::string generated_title = title(languages, Genders::F);
    ASSERT_FALSE(generated_title.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateMaritalStatus) {
    const auto        languages                = GetParam();
    const std::string generated_marital_status = marital_status(languages);
    ASSERT_FALSE(generated_marital_status.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateEmail) {
    const auto        languages = GetParam();
    const std::string generated_email =
        email(languages, std::to_array<std::string_view>({"163.com", "outlook.com", "qq.com"}));
    ASSERT_FALSE(generated_email.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateEmailWhenNullOptional) {
    const auto        languages       = GetParam();
    const std::string generated_email = email(languages);
    ASSERT_FALSE(generated_email.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateUniqueEmail) {
    const auto        languages = GetParam();
    const std::string generated_email =
        email(languages, std::to_array<std::string_view>({"163.com", "outlook.com", "qq.com"}), true);
    ASSERT_FALSE(generated_email.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateJobTitle) {
    const auto        languages           = GetParam();
    const std::string generated_job_title = job_title(languages);
    ASSERT_FALSE(generated_job_title.empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateSocialNetworkId) {
    const auto      languages                   = GetParam();
    const Bilingual generated_social_network_id = social_network_id(languages);
    ASSERT_FALSE(generated_social_network_id.original().empty());
    ASSERT_FALSE(generated_social_network_id.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGenerateUniqueSocialNetworkId) {
    const auto      languages                   = GetParam();
    const Bilingual generated_social_network_id = social_network_id(languages, true);
    ASSERT_FALSE(generated_social_network_id.original().empty());
    ASSERT_FALSE(generated_social_network_id.translation().empty());
}

TEST_P(PersonLanguagesTest, ShouldGeneratePerson) {
    const auto languages = GetParam();
    Person     generated_person(Genders::M, languages);
    ASSERT_FALSE(generated_person.first_name().original().empty());
    ASSERT_FALSE(generated_person.first_name().translation().empty());
    ASSERT_FALSE(generated_person.last_name().original().empty());
    ASSERT_FALSE(generated_person.last_name().translation().empty());
    ASSERT_FALSE(generated_person.full_name().original().empty());
    ASSERT_FALSE(generated_person.full_name().translation().empty());
    ASSERT_FALSE(generated_person.gender().empty());
    ASSERT_FALSE(generated_person.title().empty());
    ASSERT_FALSE(generated_person.marital_status().empty());
    ASSERT_FALSE(generated_person.email().empty());
    ASSERT_FALSE(generated_person.job_title().empty());
    ASSERT_FALSE(generated_person.social_network_id().original().empty());
    ASSERT_FALSE(generated_person.social_network_id().translation().empty());
    generated_person.reroll();
    ASSERT_FALSE(generated_person.first_name().original().empty());
    ASSERT_FALSE(generated_person.first_name().translation().empty());
    ASSERT_FALSE(generated_person.last_name().original().empty());
    ASSERT_FALSE(generated_person.last_name().translation().empty());
    ASSERT_FALSE(generated_person.full_name().original().empty());
    ASSERT_FALSE(generated_person.full_name().translation().empty());
    ASSERT_FALSE(generated_person.gender().empty());
    ASSERT_FALSE(generated_person.title().empty());
    ASSERT_FALSE(generated_person.marital_status().empty());
    ASSERT_FALSE(generated_person.email().empty());
    ASSERT_FALSE(generated_person.job_title().empty());
    ASSERT_FALSE(generated_person.social_network_id().original().empty());
    ASSERT_FALSE(generated_person.social_network_id().translation().empty());
}

INSTANTIATE_TEST_SUITE_P(
    PersonLanguagesTests,
    PersonLanguagesTest,
    ValuesIn(
        std::vector<Languages>(
            {Languages::English, Languages::SimplifiedChinese, Languages::TraditionalChinese, Languages::Japanese}
        )
    ),
    [](const TestParamInfo<Languages>& param_info) { return to_string(param_info.param); }
);

class PersonGendersTest : public TestWithParam<Genders> {};

TEST_P(PersonGendersTest, ShouldGenerateFirstName) {
    const auto      genders              = GetParam();
    const Bilingual generated_first_name = first_name(Languages::English, genders);
    ASSERT_FALSE(generated_first_name.original().empty());
    ASSERT_FALSE(generated_first_name.translation().empty());
}

TEST_P(PersonGendersTest, ShouldGenerateFullName) {
    const auto      genders             = GetParam();
    const Bilingual generated_full_name = full_name(Languages::English, genders);
    ASSERT_FALSE(generated_full_name.original().empty());
    ASSERT_FALSE(generated_full_name.translation().empty());
}

TEST_P(PersonGendersTest, ShouldGenerateTitle) {
    const auto        genders         = GetParam();
    const std::string generated_title = title(Languages::English, genders);
    ASSERT_FALSE(generated_title.empty());
}

TEST_P(PersonGendersTest, ShouldGeneratePerson) {
    const auto   genders = GetParam();
    const Person generated_person(genders);
    ASSERT_FALSE(generated_person.first_name().original().empty());
    ASSERT_FALSE(generated_person.first_name().translation().empty());
    ASSERT_FALSE(generated_person.last_name().original().empty());
    ASSERT_FALSE(generated_person.last_name().translation().empty());
    ASSERT_FALSE(generated_person.full_name().original().empty());
    ASSERT_FALSE(generated_person.full_name().translation().empty());
    ASSERT_FALSE(generated_person.gender().empty());
    ASSERT_FALSE(generated_person.title().empty());
    ASSERT_FALSE(generated_person.marital_status().empty());
    ASSERT_FALSE(generated_person.phone_number(true, true).empty());
    ASSERT_FALSE(generated_person.email().empty());
    ASSERT_FALSE(generated_person.job_title().empty());
    ASSERT_FALSE(generated_person.social_network_id().original().empty());
    ASSERT_FALSE(generated_person.social_network_id().translation().empty());
}

INSTANTIATE_TEST_SUITE_P(
    PersonGendersTests,
    PersonGendersTest,
    ValuesIn(std::vector<Genders>({Genders::M, Genders::F})),
    [](const TestParamInfo<Genders>& param_info) { return to_string(param_info.param); }
);

class PersonRegionsTest : public TestWithParam<Regions> {};

TEST_P(PersonRegionsTest, ShouldGeneratePhoneNumberWithDelimiters) {
    const auto        regions                = GetParam();
    const std::string generated_phone_number = phone_number(false, true, regions);
    ASSERT_FALSE(generated_phone_number.empty());
}

TEST_P(PersonRegionsTest, ShouldGeneratePhoneNumberWithoutDelimiters) {
    const auto        regions                = GetParam();
    const std::string generated_phone_number = phone_number(false, false, regions);
    ASSERT_FALSE(generated_phone_number.empty());
    ASSERT_TRUE(generated_phone_number.find("()-") == std::string::npos);
}

TEST_P(PersonRegionsTest, ShouldGenerateInternationalPhoneNumberWithDelimiters) {
    const auto        regions                = GetParam();
    const std::string generated_phone_number = phone_number(true, true, regions);
    ASSERT_FALSE(generated_phone_number.empty());
    ASSERT_TRUE(generated_phone_number.find_first_of('+') != std::string::npos);
}

TEST_P(PersonRegionsTest, ShouldGenerateUniquePhoneNumber) {
    const auto        regions                = GetParam();
    const std::string generated_phone_number = phone_number(true, true, regions, true);
    ASSERT_FALSE(generated_phone_number.empty());
    ASSERT_TRUE(generated_phone_number.find_first_of('+') != std::string::npos);
}

TEST_P(PersonRegionsTest, ShouldGeneratePerson) {
    const auto   regions = GetParam();
    const Person generated_person(
        Genders::M,
        Languages::English,
        regions,
        std::to_array<std::string_view>({"gmail.com", "yahoo.com"})
    );
    ASSERT_FALSE(generated_person.first_name().original().empty());
    ASSERT_FALSE(generated_person.first_name().translation().empty());
    ASSERT_FALSE(generated_person.last_name().original().empty());
    ASSERT_FALSE(generated_person.last_name().translation().empty());
    ASSERT_FALSE(generated_person.full_name().original().empty());
    ASSERT_FALSE(generated_person.full_name().translation().empty());
    ASSERT_FALSE(generated_person.gender().empty());
    ASSERT_FALSE(generated_person.title().empty());
    ASSERT_FALSE(generated_person.marital_status().empty());
    ASSERT_FALSE(generated_person.phone_number(true, true).empty());
    ASSERT_FALSE(generated_person.email().empty());
    ASSERT_FALSE(generated_person.job_title().empty());
    ASSERT_FALSE(generated_person.social_network_id().original().empty());
    ASSERT_FALSE(generated_person.social_network_id().translation().empty());
}

INSTANTIATE_TEST_SUITE_P(
    PersonRegionsTests,
    PersonRegionsTest,
    ValuesIn(std::vector<Regions>({Regions::UnitedKingdom, Regions::UnitedStates, Regions::China, Regions::Japan})),
    [](const TestParamInfo<Regions>& param_info) { return to_string(param_info.param); }
);

TEST(PersonTest, ShouldGeneratePersonPhoneNumberWithDelimiters) {
    const Person      generated_person{};
    const std::string generated_phone_number = generated_person.phone_number(false, true);
    ASSERT_FALSE(generated_phone_number.empty());
}

TEST(PersonTest, ShouldGeneratePersonPhoneNumberWithoutDelimiters) {
    const Person      generated_person{};
    const std::string generated_phone_number = generated_person.phone_number(false, false);
    ASSERT_FALSE(generated_phone_number.empty());
    ASSERT_TRUE(generated_phone_number.find("()-") == std::string::npos);
}

TEST(PersonTest, ShouldGeneratePersonInternationalPhoneNumberWithDelimiters) {
    const Person      generated_person{};
    const std::string generated_phone_number = generated_person.phone_number(true, true);
    ASSERT_FALSE(generated_phone_number.empty());
    ASSERT_TRUE(generated_phone_number.find_first_of('+') != std::string::npos);
}

TEST(PersonTest, ShouldGenerateUniquePerson) {
    const Person generated_person{
        Genders::F,
        Languages::English,
        Regions::UnitedStates,
        std::to_array<std::string_view>({"gmail.com", "yahoo.com"}),
        true
    };
    ASSERT_FALSE(generated_person.first_name().empty());
    ASSERT_FALSE(generated_person.first_name().original().empty());
    ASSERT_FALSE(generated_person.first_name().translation().empty());
    ASSERT_FALSE(generated_person.last_name().original().empty());
    ASSERT_FALSE(generated_person.last_name().translation().empty());
    ASSERT_FALSE(generated_person.full_name().original().empty());
    ASSERT_FALSE(generated_person.full_name().translation().empty());
    ASSERT_FALSE(generated_person.gender().empty());
    ASSERT_FALSE(generated_person.title().empty());
    ASSERT_FALSE(generated_person.marital_status().empty());
    ASSERT_FALSE(generated_person.phone_number(true, true).empty());
    ASSERT_FALSE(generated_person.email().empty());
    ASSERT_FALSE(generated_person.job_title().empty());
    ASSERT_FALSE(generated_person.social_network_id().original().empty());
    ASSERT_FALSE(generated_person.social_network_id().translation().empty());
}

TEST(PersonTest, ShouldThrowExceptionWhenEmailDomainsIsEmpty) {
    std::vector<std::string_view> empty_email_domains = {};
    ASSERT_THROW(email(Languages::English, empty_email_domains), std::invalid_argument);
}

TEST(PersonTest, ShouldThrowExceptionWhenEmailDomainsContainEmptyItem) {
    ASSERT_THROW(email(Languages::English, std::to_array<std::string_view>({"gmail.com", ""})), std::invalid_argument);
}

TEST(PersonTest, ShouldThrowExceptionWhenPersonEmailDomainsIsEmpty) {
    std::vector<std::string_view> empty_email_domains = {};
    ASSERT_THROW(
        Person generated_person(Genders::M, Languages::English, Regions::UnitedStates, empty_email_domains),
        std::invalid_argument
    );
}

TEST(PersonTest, ShouldThrowExceptionWhenPersonEmailDomainsContainEmptyItem) {
    ASSERT_THROW(
        Person generated_person(
            Genders::M,
            Languages::English,
            Regions::UnitedStates,
            std::to_array<std::string_view>({"gmail.com", ""})
        ),
        std::invalid_argument
    );
}

TEST(PersonTest, ShouldGenerateDeterministicEmailWhenSeeded) {
    seed_random_engine(20260211ULL);
    const std::string first = email(Languages::English, std::to_array<std::string_view>({"example.com"}), false);
    seed_random_engine(20260211ULL);
    const std::string second = email(Languages::English, std::to_array<std::string_view>({"example.com"}), false);
    ASSERT_EQ(first, second);
}

TEST(PersonTest, ShouldGenerateUniqueEmailAcrossThreads) {
    std::vector<std::string> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const std::string value =
                email(Languages::English, std::to_array<std::string_view>({"example.com"}), true);
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

TEST(PersonTest, ShouldGenerateUniquePhoneNumberAcrossThreads) {
    std::vector<std::string> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const std::string value = phone_number(true, true, Regions::UnitedStates, true);
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

TEST(PersonTest, ShouldGenerateUniqueSocialNetworkIdAcrossThreads) {
    std::vector<std::string> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const Bilingual value = social_network_id(Languages::English, true);
            std::lock_guard<std::mutex> lock(generated_mutex);
            generated.push_back(value.original());
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
