// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file business.cpp

#include "faker/business.h"

#include <format>
#include <random>

#include "business_data.h"
#include "faker/types/bilingual.h"
#include "faker/types/enums.h"
#include "person_data.h"
#include "random_engine.h"
#include "random_helper.h"

namespace faker::business {

// Get a random industry
static Industries pick_industry() {
    constexpr std::array industries = {
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
    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(0, static_cast<int>(industries.size()) - 1);
    const Industries              random_industry = industries[distribution(random_engine)];
    return random_industry;
}

// Get a company name
static Bilingual get_company_name(const Languages language, const Industries industry) {
    BilingualView business_words_view;
    const auto    selected_language_it = kBusinessWords.find(language);
    if (selected_language_it != kBusinessWords.end()) {
        const auto& industries_map = selected_language_it->second;
        const auto  industries_it  = industries_map.find(industry);
        if (industries_it != industries_map.end() && !industries_it->second.empty()) {
            business_words_view = pick_one(industries_it->second);
        } else {
            business_words_view = pick_one(industries_map.at(Industries::Trading));
        }
    }

    BilingualView company_suffixes_view;
    BilingualView last_name_suffixes_view;
    BilingualView last_name_view;
    switch (language) {
    case Languages::English:
        company_suffixes_view   = pick_one(kEnglishCompanySuffixes);
        last_name_suffixes_view = pick_one(kEnglishLastNameSuffixes);
        last_name_view          = pick_one(person::kEnglishLastNames);
        break;
    case Languages::SimplifiedChinese:
        company_suffixes_view   = pick_one(kSimplifiedChineseCompanySuffixes);
        last_name_suffixes_view = pick_one(kSimplifiedChineseLastNameSuffixes);
        last_name_view          = pick_one(person::kSimplifiedChineseLastNames);
        break;
    case Languages::TraditionalChinese:
        company_suffixes_view   = pick_one(kTraditionalChineseCompanySuffixes);
        last_name_suffixes_view = pick_one(kTraditionalChineseLastNameSuffixes);
        last_name_view          = pick_one(person::kTraditionalChineseLastNames);
        break;
    case Languages::Japanese:
        company_suffixes_view   = pick_one(kJapaneseCompanySuffixes);
        last_name_suffixes_view = pick_one(kJapaneseLastNameSuffixes);
        last_name_view          = pick_one(person::kJapaneseLastNames);
        break;
    }

    std::string original;
    if (language ==
        Languages::SimplifiedChinese ||
        language ==
        Languages::TraditionalChinese ||
        language == Languages::Japanese) {
        original = std::format(
            "{}{}{}{}",
            last_name_view.original,
            last_name_suffixes_view.original,
            business_words_view.original,
            company_suffixes_view.original
        );
    } else {
        original = std::format(
            "{}{} {} {}",
            last_name_view.original,
            last_name_suffixes_view.original,
            business_words_view.original,
            company_suffixes_view.original
        );
    }

    std::string translation = std::format(
        "{}{} {} {}",
        last_name_view.translation,
        last_name_suffixes_view.translation,
        business_words_view.translation,
        company_suffixes_view.translation
    );

    auto bilingual = Bilingual(original, translation);

    return bilingual;
}

static std::string get_industry(const Languages languages, const Industries industry) {
    std::string_view industry_string;
    const auto       selected_language_it = kIndustries.find(languages);
    if (selected_language_it != kIndustries.end()) {
        const auto& industries_map = selected_language_it->second;
        const auto  industries_it  = industries_map.find(industry);
        if (industries_it != industries_map.end() && !industries_it->second.empty()) {
            industry_string = industries_it->second;
        } else {
            industry_string = industries_map.at(Industries::Trading);
        }
    }
    return std::string(industry_string);
}

Bilingual company_name(const Languages languages) {
    const auto selected_language = pick_language(languages);
    const auto selected_industry = pick_industry();

    return get_company_name(selected_language, selected_industry);
}

std::string department(const Languages languages) {
    const auto       selected_language = pick_language(languages);
    std::string_view department;
    switch (selected_language) {
    case Languages::English           : department = pick_one(kEnglishDepartments); break;
    case Languages::SimplifiedChinese : department = pick_one(kSimplifiedChineseDepartments); break;
    case Languages::TraditionalChinese: department = pick_one(kTraditionalChineseDepartments); break;
    case Languages::Japanese          : department = pick_one(kJapaneseDepartments); break;
    }

    return std::string(department);
}

std::string industry(const Languages languages) {
    const auto selected_language = pick_language(languages);
    const auto selected_industry = pick_industry();

    return get_industry(selected_language, selected_industry);
}

Company::Company(const Languages languages) : languages_(languages) {
    roll();
}

Company::~Company() = default;

void Company::reroll() {
    roll();
}

Bilingual Company::name() const {
    return name_;
}

std::string Company::industry() const {
    return industry_;
}

void Company::roll() {
    selected_language_ = pick_language(languages_);

    const auto selected_industry = pick_industry();

    name_     = get_company_name(selected_language_, selected_industry);
    industry_ = get_industry(selected_language_, selected_industry);
}

}  // namespace faker::business
