// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_random_helper.cpp

#include <gtest/gtest.h>

#include <array>
#include <ranges>
#include <span>
#include <thread>
#include <vector>

#include "faker/types/enums.h"
#include "random_helper.h"

using namespace ::faker;

TEST(PickOneTest, Array) {
    const auto candidates = std::to_array<std::string>({
        {"a"},
        {"b"},
        {"c"},
    });

    const auto picked = pick_one(candidates);
    ASSERT_TRUE(std::ranges::find(candidates.begin(), candidates.end(), picked) != candidates.end());
}

TEST(PickOneTest, EmptySpanThrows) {
    const std::span<const int> empty_values{};
    ASSERT_THROW([[maybe_unused]] const auto& value = pick_one(empty_values), std::invalid_argument);
}

TEST(PickIndexTest, EmptySpanThrows) {
    const std::span<const int> empty_values{};
    ASSERT_THROW([[maybe_unused]] const auto index = pick_index(empty_values), std::invalid_argument);
}

TEST(PickLanguageTest, CombinationOfAllLanguages) {
    std::vector<Languages> combination;
    for (int mask = 1; mask < (1 << 4); ++mask) { combination.push_back(static_cast<Languages>(mask)); }
    for (const auto& languages : combination) {
        const auto language = pick_language(languages);
        ASSERT_TRUE((language & languages) == language);
    }

    ASSERT_EQ(pick_language(static_cast<Languages>(0)), Languages::English);
}

TEST(PickLanguageTest, DeterministicSeedProducesRepeatableSequence) {
    constexpr auto all_languages =
        Languages::English | Languages::SimplifiedChinese | Languages::TraditionalChinese | Languages::Japanese;

    seed_random_engine(20260211ULL);
    std::array<Languages, 12> first_sequence{};
    for (auto& value : first_sequence) { value = pick_language(all_languages); }

    seed_random_engine(20260211ULL);
    std::array<Languages, 12> second_sequence{};
    for (auto& value : second_sequence) { value = pick_language(all_languages); }

    ASSERT_EQ(first_sequence, second_sequence);
}

TEST(PickLanguageTest, MultiThreadedCallsStayWithinProvidedMask) {
    constexpr auto language_mask = Languages::English | Languages::Japanese;
    std::array<Languages, 2> results{};

    std::thread t1([&results]() { results[0] = pick_language(language_mask); });
    std::thread t2([&results]() { results[1] = pick_language(language_mask); });
    t1.join();
    t2.join();

    ASSERT_TRUE((results[0] & language_mask) == results[0]);
    ASSERT_TRUE((results[1] & language_mask) == results[1]);
}

TEST(PickRegionTest, CombinationOfAllRegions) {
    std::vector<Regions> combination;
    for (int mask = 1; mask < (1 << 4); ++mask) { combination.push_back(static_cast<Regions>(mask)); }
    for (const auto& regions : combination) {
        const auto region = pick_region(regions);
        ASSERT_TRUE((region & regions) == region);
    }

    ASSERT_EQ(pick_region(static_cast<Regions>(0)), Regions::UnitedStates);
}

TEST(PickGenderTest, CombinationOfAllGenders) {
    std::vector<Genders> combination;
    for (int mask = 1; mask < (1 << 2); ++mask) { combination.push_back(static_cast<Genders>(mask)); }
    for (const auto& genders : combination) {
        const auto gender = pick_gender(genders);
        ASSERT_TRUE((gender & genders) == gender);
    }

    ASSERT_EQ(pick_gender(static_cast<Genders>(0)), Genders::M);
}

TEST(PickCardTypeTest, CombinationOfAllCardTypes) {
    std::vector<CardTypes> combination;
    for (int mask = 1; mask < (1 << 5); ++mask) { combination.push_back(static_cast<CardTypes>(mask)); }
    for (const auto& card_types : combination) {
        const auto card_type = pick_card_type(card_types);
        ASSERT_TRUE((card_type & card_types) == card_type);
    }
    ASSERT_EQ(pick_card_type(static_cast<CardTypes>(0)), CardTypes::Visa);
}

TEST(PickBarcodeTypeTest, CombinationOfAllBarcodeTypes) {
    std::vector<BarcodeTypes> combination;
    for (int mask = 1; mask < (1 << 5); ++mask) { combination.push_back(static_cast<BarcodeTypes>(mask)); }
    for (const auto& barcode_types : combination) {
        const auto barcode_type = pick_barcode_type(barcode_types);
        ASSERT_TRUE((barcode_type & barcode_types) == barcode_type);
    }
    ASSERT_EQ(pick_barcode_type(static_cast<BarcodeTypes>(0)), BarcodeTypes::EAN13);
}

TEST(PickOperatingSystemTest, CombinationOfAllOperatingSystems) {
    std::vector<OperatingSystems> combination;
    for (int mask = 1; mask < (1 << 3); ++mask) { combination.push_back(static_cast<OperatingSystems>(mask)); }
    for (const auto& operating_systems : combination) {
        const auto operating_system = pick_operating_system(operating_systems);
        ASSERT_TRUE((operating_system & operating_systems) == operating_system);
    }
    ASSERT_EQ(pick_operating_system(static_cast<OperatingSystems>(0)), OperatingSystems::Windows);
}
