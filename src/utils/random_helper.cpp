// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_helper.cpp

#include "random_helper.h"

#include <random>
#include <vector>

#include "faker/types/enums.h"
#include "random_engine.h"

namespace faker {
Languages pick_language(const Languages languages) {
    std::vector<Languages> candidates;
    if ((languages & Languages::English) == Languages::English) { candidates.push_back(Languages::English); }
    if ((languages & Languages::SimplifiedChinese) == Languages::SimplifiedChinese) {
        candidates.push_back(Languages::SimplifiedChinese);
    }
    if ((languages & Languages::TraditionalChinese) == Languages::TraditionalChinese) {
        candidates.push_back(Languages::TraditionalChinese);
    }
    if ((languages & Languages::Japanese) == Languages::Japanese) { candidates.push_back(Languages::Japanese); }

    if (candidates.empty()) { return Languages::English; }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(candidates.size()) - 1);
    const Languages               random_language = candidates[distribution(random_engine)];
    return random_language;
}

Regions pick_region(const Regions regions) {
    std::vector<Regions> candidates;
    if ((regions & Regions::UnitedStates) == Regions::UnitedStates) { candidates.push_back(Regions::UnitedStates); }
    if ((regions & Regions::UnitedKingdom) == Regions::UnitedKingdom) { candidates.push_back(Regions::UnitedKingdom); }
    if ((regions & Regions::China) == Regions::China) { candidates.push_back(Regions::China); }
    if ((regions & Regions::Japan) == Regions::Japan) { candidates.push_back(Regions::Japan); }

    if (candidates.empty()) { return Regions::UnitedStates; }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(candidates.size()) - 1);
    const Regions                 random_region = candidates[distribution(random_engine)];
    return random_region;
}

Genders pick_gender(const Genders genders) {
    if ((genders & (Genders::M | Genders::F)) == (Genders::M | Genders::F)) {
        std::mt19937_64&              random_engine = get_random_engine();
        std::uniform_int_distribution distribution(0, 1);
        const Genders                 random_gender = distribution(random_engine) == 0 ? Genders::M : Genders::F;
        return random_gender;
    }

    if ((genders & Genders::M) != Genders::M && (genders & Genders::F) != Genders::F) { return Genders::M; }

    return genders;
}

CardTypes pick_card_type(const CardTypes card_types) {
    std::vector<CardTypes> candidates;
    if ((card_types & CardTypes::AmericanExpress) == CardTypes::AmericanExpress) {
        candidates.push_back(CardTypes::AmericanExpress);
    }
    if ((card_types & CardTypes::JCB) == CardTypes::JCB) { candidates.push_back(CardTypes::JCB); }
    if ((card_types & CardTypes::MasterCard) == CardTypes::MasterCard) { candidates.push_back(CardTypes::MasterCard); }
    if ((card_types & CardTypes::UnionPay) == CardTypes::UnionPay) { candidates.push_back(CardTypes::UnionPay); }
    if ((card_types & CardTypes::Visa) == CardTypes::Visa) { candidates.push_back(CardTypes::Visa); }

    if (candidates.empty()) { return CardTypes::Visa; }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(candidates.size()) - 1);
    const CardTypes               random_card_type = candidates[distribution(random_engine)];
    return random_card_type;
}

BarcodeTypes pick_barcode_type(BarcodeTypes barcode_types) {
    std::vector<BarcodeTypes> candidates;
    if ((barcode_types & BarcodeTypes::EAN13) == BarcodeTypes::EAN13) { candidates.push_back(BarcodeTypes::EAN13); }
    if ((barcode_types & BarcodeTypes::EAN8) == BarcodeTypes::EAN8) { candidates.push_back(BarcodeTypes::EAN8); }
    if ((barcode_types & BarcodeTypes::UPCA) == BarcodeTypes::UPCA) { candidates.push_back(BarcodeTypes::UPCA); }
    if ((barcode_types & BarcodeTypes::UPCE) == BarcodeTypes::UPCE) { candidates.push_back(BarcodeTypes::UPCE); }
    if ((barcode_types & BarcodeTypes::ISBN) == BarcodeTypes::ISBN) { candidates.push_back(BarcodeTypes::ISBN); }

    if (candidates.empty()) { return BarcodeTypes::EAN13; }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(candidates.size()) - 1);
    const BarcodeTypes            random_barcode_type = candidates[distribution(random_engine)];
    return random_barcode_type;
}

OperatingSystems pick_operating_system(OperatingSystems operating_systems) {
    std::vector<OperatingSystems> candidates;
    if ((operating_systems & OperatingSystems::Windows) == OperatingSystems::Windows) {
        candidates.push_back(OperatingSystems::Windows);
    }
    if ((operating_systems & OperatingSystems::macOS) == OperatingSystems::macOS) {
        candidates.push_back(OperatingSystems::macOS);
    }
    if ((operating_systems & OperatingSystems::Linux) == OperatingSystems::Linux) {
        candidates.push_back(OperatingSystems::Linux);
    }

    if (candidates.empty()) { return OperatingSystems::Windows; }

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(candidates.size()) - 1);
    const OperatingSystems        random_operating_system = candidates[distribution(random_engine)];
    return random_operating_system;
}

}  // namespace faker
