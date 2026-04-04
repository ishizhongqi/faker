// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_location.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "faker/location.h"
#include "faker/types/bilingual.h"
#include "faker/types/enums.h"
#include "location_data.h"
#include "random_engine.h"
#include "tests_helper.h"

using namespace ::testing;
using namespace ::faker;
using namespace faker::location;

struct LocationClassParam {
    Regions regions;
};

class LocationTest : public TestWithParam<Regions> {};

TEST_P(LocationTest, ShouldGenerateAddressLine1) {
    const auto      param             = GetParam();
    const Bilingual generated_address = address_line1(param);

    ASSERT_FALSE(generated_address.original().empty());
    ASSERT_FALSE(generated_address.translation().empty());
}

TEST_P(LocationTest, ShouldGenerateAddressLine2) {
    const auto      param             = GetParam();
    const Bilingual generated_address = address_line2(param);

    ASSERT_EQ(generated_address.original().empty(), generated_address.translation().empty());
}

TEST_P(LocationTest, ShouldGeneratePostcode) {
    const auto        param              = GetParam();
    const std::string generated_postcode = postcode(param);

    ASSERT_FALSE(generated_postcode.empty());
}

TEST_P(LocationTest, ShouldGenerateFullAddress) {
    const auto      param             = GetParam();
    const Bilingual generated_address = full_address(param);

    ASSERT_FALSE(generated_address.original().empty());
    ASSERT_FALSE(generated_address.translation().empty());
}

TEST_P(LocationTest, ShouldGenerateCity) {
    const auto      param          = GetParam();
    const Bilingual generated_city = city(param);

    ASSERT_FALSE(generated_city.original().empty());
    ASSERT_FALSE(generated_city.translation().empty());
}

TEST_P(LocationTest, ShouldGenerateLocation) {
    const auto param = GetParam();
    Location   location(param);

    ASSERT_FALSE(location.address_line1().original().empty());
    ASSERT_FALSE(location.address_line1().translation().empty());
    ASSERT_EQ(location.address_line2().original().empty(), location.address_line2().translation().empty());
    ASSERT_FALSE(location.postcode().empty());
    ASSERT_FALSE(location.full_address().original().empty());
    ASSERT_FALSE(location.full_address().translation().empty());
    ASSERT_FALSE(location.city().original().empty());
    ASSERT_FALSE(location.city().translation().empty());
    ASSERT_FALSE(location.region().empty());

    location.reroll();

    ASSERT_FALSE(location.address_line1().original().empty());
    ASSERT_FALSE(location.address_line1().translation().empty());
    ASSERT_EQ(location.address_line2().original().empty(), location.address_line2().translation().empty());
    ASSERT_FALSE(location.postcode().empty());
    ASSERT_FALSE(location.full_address().original().empty());
    ASSERT_FALSE(location.full_address().translation().empty());
    ASSERT_FALSE(location.city().original().empty());
    ASSERT_FALSE(location.city().translation().empty());
    ASSERT_FALSE(location.region().empty());
}

INSTANTIATE_TEST_SUITE_P(
    LocationTests,
    LocationTest,
    ValuesIn(std::vector<Regions>({Regions::UnitedStates, Regions::UnitedKingdom, Regions::China, Regions::Japan})),
    [](const TestParamInfo<Regions>& param_info) { return to_string(param_info.param); }
);

TEST(LocationTest, ShouldHaveValidCityLevelInAddressData) {
    const auto validate_city_level = [](const auto& components, const std::size_t city_level) {
        for (const auto& component : components) {
            ASSERT_FALSE(component.admin_levels.empty());
            ASSERT_LT(city_level, component.admin_levels.size());
            ASSERT_FALSE(component.admin_levels[city_level].original.empty());
            ASSERT_FALSE(component.admin_levels[city_level].translation.empty());
        }
    };

    validate_city_level(kUnitedStatesAddressComponents, static_cast<std::size_t>(KUnitedStatesCityLevel));
    validate_city_level(kUnitedKingdomAddressComponents, static_cast<std::size_t>(KUnitedKingdomCityLevel));
    validate_city_level(kChinaAddressComponents, static_cast<std::size_t>(KChinaCityLevel));
    validate_city_level(kJapanAddressComponents, static_cast<std::size_t>(KJapanCityLevel));
}

TEST(LocationTest, ShouldGenerateDeterministicCityWhenSeeded) {
    seed_random_engine(20260211ULL);
    const Bilingual first = city(Regions::UnitedStates);
    seed_random_engine(20260211ULL);
    const Bilingual second = city(Regions::UnitedStates);
    ASSERT_EQ(first.original(), second.original());
    ASSERT_EQ(first.translation(), second.translation());
}

TEST(LocationTest, ShouldGenerateFullAddressConcurrently) {
    std::vector<Bilingual> generated;
    generated.reserve(400);
    std::mutex generated_mutex;

    auto worker = [&generated, &generated_mutex]() {
        for (int i = 0; i < 100; ++i) {
            const Bilingual value = full_address(Regions::UnitedStates);
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

    ASSERT_EQ(generated.size(), 400U);
    for (const auto& value : generated) {
        ASSERT_FALSE(value.original().empty());
        ASSERT_FALSE(value.translation().empty());
    }
}

struct RegionParam {
    CountryCodesStandard country_codes_standard;
    Languages            languages;
};

const auto all_country_standards = Values(
    CountryCodesStandard::None,
    CountryCodesStandard::ISO_3166_1_alpha_2,
    CountryCodesStandard::ISO_3166_1_alpha_3
);

const auto all_languages =
    Values(Languages::English, Languages::SimplifiedChinese, Languages::TraditionalChinese, Languages::Japanese);

class RegionTest : public TestWithParam<std::tuple<CountryCodesStandard, Languages>> {};

TEST_P(RegionTest, ShouldGenerateRegion) {
    const auto& [country_codes_standard, languages] = GetParam();
    const std::string generated_region              = region(country_codes_standard, languages);

    ASSERT_FALSE(generated_region.empty());
}

TEST_P(RegionTest, ShouldGenerateLocationRegion) {
    const auto [country_codes_standard, languages] = GetParam();
    const Location location{};
    const auto     generated_region = location.region(country_codes_standard, languages);

    ASSERT_FALSE(generated_region.empty());
}

INSTANTIATE_TEST_SUITE_P(
    RegionTests,
    RegionTest,
    ::testing::Combine(all_country_standards, all_languages),
    [](const TestParamInfo<std::tuple<CountryCodesStandard, Languages>>& param_info) {
        std::string name;
        const auto  country_std = std::get<0>(param_info.param);
        const auto  lang        = std::get<1>(param_info.param);
        switch (country_std) {
        case CountryCodesStandard::None              : name += "None"; break;
        case CountryCodesStandard::ISO_3166_1_alpha_2: name += "ISO_3166_1_alpha_2"; break;
        case CountryCodesStandard::ISO_3166_1_alpha_3: name += "ISO_3166_1_alpha_3"; break;
        }
        name += "_";
        name += to_string(lang);
        return name;
    }
);
