// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_helper.cpp

#include "random_helper.h"

#include <array>
#include <random>

#include "faker/types/enums.h"
#include "random_engine.h"

namespace faker {

namespace {

template <typename Enum, std::size_t N>
Enum pick_flag_from_candidates(const Enum flags, const std::array<Enum, N>& available, const Enum default_value) {
    std::array<Enum, N> candidates{};
    std::size_t         count = 0;
    for (const Enum value : available) {
        if ((flags & value) == value) { candidates[count++] = value; }
    }

    if (count == 0) { return default_value; }

    const std::size_t index = std::uniform_int_distribution<std::size_t>(0, count - 1)(get_random_engine());
    return candidates[index];
}

}  // namespace

Languages pick_language(const Languages languages) {
    constexpr std::array kCandidates{
        Languages::English,
        Languages::SimplifiedChinese,
        Languages::TraditionalChinese,
        Languages::Japanese,
    };
    return pick_flag_from_candidates(languages, kCandidates, Languages::English);
}

Regions pick_region(const Regions regions) {
    constexpr std::array kCandidates{
        Regions::UnitedStates,
        Regions::UnitedKingdom,
        Regions::China,
        Regions::Japan,
    };
    return pick_flag_from_candidates(regions, kCandidates, Regions::UnitedStates);
}

Genders pick_gender(const Genders genders) {
    const bool has_male   = (genders & Genders::M) == Genders::M;
    const bool has_female = (genders & Genders::F) == Genders::F;
    if (has_male && has_female) {
        const bool pick_male = std::uniform_int_distribution<int>(0, 1)(get_random_engine()) == 0;
        return pick_male ? Genders::M : Genders::F;
    }
    if (has_male) { return Genders::M; }
    if (has_female) { return Genders::F; }
    return Genders::M;
}

CardTypes pick_card_type(const CardTypes card_types) {
    constexpr std::array kCandidates{
        CardTypes::AmericanExpress,
        CardTypes::JCB,
        CardTypes::MasterCard,
        CardTypes::UnionPay,
        CardTypes::Visa,
    };
    return pick_flag_from_candidates(card_types, kCandidates, CardTypes::Visa);
}

BarcodeTypes pick_barcode_type(BarcodeTypes barcode_types) {
    constexpr std::array kCandidates{
        BarcodeTypes::EAN13,
        BarcodeTypes::EAN8,
        BarcodeTypes::UPCA,
        BarcodeTypes::UPCE,
        BarcodeTypes::ISBN,
    };
    return pick_flag_from_candidates(barcode_types, kCandidates, BarcodeTypes::EAN13);
}

OperatingSystems pick_operating_system(OperatingSystems operating_systems) {
    constexpr std::array kCandidates{
        OperatingSystems::Windows,
        OperatingSystems::macOS,
        OperatingSystems::Linux,
    };
    return pick_flag_from_candidates(operating_systems, kCandidates, OperatingSystems::Windows);
}

}  // namespace faker
