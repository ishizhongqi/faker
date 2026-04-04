// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file person.cpp

#include "faker/person.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <format>
#include <mutex>
#include <optional>
#include <random>
#include <span>
#include <string>
#include <string_view>

#include "faker/types/bilingual.h"
#include "faker/types/enums.h"
#include "permutation_generator.h"
#include "person_data.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::person {

namespace {

// unique
constexpr std::size_t phone_number_format_count = kUnitedStatesPhoneNumberFormat.size() +
                                                  kUnitedKingdomPhoneNumberFormat.size() +
                                                  kChinaPhoneNumberFormat.size() +
                                                  kJapanPhoneNumberFormat.size();

std::array<PermutationGenerator, phone_number_format_count> phone_number_pg_vector;
std::array<uint64_t, phone_number_format_count>             phone_number_capacity{};
std::array<uint8_t, phone_number_format_count>              phone_number_wildcards{};
std::array<std::mutex, phone_number_format_count>           phone_number_mutexes{};

PermutationGenerator email_pg(0, 2176782336 - 1, PermutationGenerator::BaseN::Base36);              // 36^6 - 1

PermutationGenerator social_network_id_pg(0, 2176782336 - 1, PermutationGenerator::BaseN::Base36);  // 36^6 - 1
std::mutex           email_pg_mutex;
std::mutex           social_network_id_pg_mutex;

                                                                                                    // Format full name
Bilingual format_full_name(const Languages language, const Bilingual& first_name, const Bilingual& last_name) {
    std::string full_name_original;
    std::string full_name_translation;

    switch (language) {
    case Languages::SimplifiedChinese:
    case Languages::TraditionalChinese:
    case Languages::Japanese:
        full_name_original    = std::format("{0}{1}", last_name.original(), first_name.original());
        full_name_translation = std::format("{0} {1}", last_name.translation(), first_name.translation());
        break;
    case Languages::English:
        full_name_original    = std::format("{0} {1}", first_name.original(), last_name.original());
        full_name_translation = std::format("{0} {1}", first_name.translation(), last_name.translation());
        break;
    }

    auto full_name = Bilingual(full_name_original, full_name_translation);
    return full_name;
}

}  // namespace

Bilingual first_name(const Languages languages, const Genders genders) {
    const auto selected_language = pick_language(languages);
    const auto selected_gender   = pick_gender(genders);

    BilingualView view{"", ""};
    if (selected_gender == Genders::M) {
        switch (selected_language) {
        case Languages::English           : view = pick_one(kEnglishMaleFirstNames); break;
        case Languages::SimplifiedChinese : view = pick_one(kSimplifiedChineseMaleFirstNames); break;
        case Languages::TraditionalChinese: view = pick_one(kTraditionalChineseMaleFirstNames); break;
        case Languages::Japanese          : view = pick_one(kJapaneseMaleFirstNames); break;
        }
    } else if (selected_gender == Genders::F) {
        switch (selected_language) {
        case Languages::English           : view = pick_one(kEnglishFemaleFirstNames); break;
        case Languages::SimplifiedChinese : view = pick_one(kSimplifiedChineseFemaleFirstNames); break;
        case Languages::TraditionalChinese: view = pick_one(kTraditionalChineseFemaleFirstNames); break;
        case Languages::Japanese          : view = pick_one(kJapaneseFemaleFirstNames); break;
        }
    }

    auto bilingual = Bilingual(view.original, view.translation);
    return bilingual;
}

Bilingual last_name(const Languages languages) {
    const auto selected_name_language = pick_language(languages);

    BilingualView view{"", ""};
    switch (selected_name_language) {
    case Languages::English           : view = pick_one(kEnglishLastNames); break;
    case Languages::SimplifiedChinese : view = pick_one(kSimplifiedChineseLastNames); break;
    case Languages::TraditionalChinese: view = pick_one(kTraditionalChineseLastNames); break;
    case Languages::Japanese          : view = pick_one(kJapaneseLastNames); break;
    }

    auto bilingual = Bilingual(view.original, view.translation);
    return bilingual;
}

Bilingual full_name(const Languages languages, const Genders genders) {
    const auto selected_language = pick_language(languages);
    const auto selected_gender   = pick_gender(genders);

    return format_full_name(
        selected_language,
        first_name(selected_language, selected_gender),
        last_name(selected_language)
    );
}

std::string gender(const Languages languages) {
    const auto        selected_language = pick_language(languages);
    constexpr Genders genders           = Genders::M | Genders::F;
    const auto        selected_gender   = pick_gender(genders);
    return std::string(kGenders.at(selected_language).at(selected_gender));
}

std::string title(const Languages languages, const Genders genders) {
    const auto selected_language = pick_language(languages);
    const auto selected_gender   = pick_gender(genders);

    std::string_view title;
    if (selected_gender == Genders::M) {
        switch (selected_language) {
        case Languages::English           : title = pick_one(kEnglishMaleTitle); break;
        case Languages::SimplifiedChinese : title = pick_one(kSimplifiedChineseMaleTitle); break;
        case Languages::TraditionalChinese: title = pick_one(kTraditionalChineseMaleTitle); break;
        case Languages::Japanese          : title = pick_one(kJapaneseMaleTitle); break;
        }
    } else if (selected_gender == Genders::F) {
        switch (selected_language) {
        case Languages::English           : title = pick_one(kEnglishFemaleTitle); break;
        case Languages::SimplifiedChinese : title = pick_one(kSimplifiedChineseFemaleTitle); break;
        case Languages::TraditionalChinese: title = pick_one(kTraditionalChineseFemaleTitle); break;
        case Languages::Japanese          : title = pick_one(kJapaneseFemaleTitle); break;
        }
    }

    return std::string(title);
}

std::string marital_status(const Languages languages) {
    const auto selected_language = pick_language(languages);

    std::string_view marital_status;
    if (selected_language == Languages::English) {
        marital_status = pick_one(kEnglishMaritalStatus);
    } else if (selected_language == Languages::SimplifiedChinese) {
        marital_status = pick_one(kSimplifiedChineseMaritalStatus);
    } else if (selected_language == Languages::TraditionalChinese) {
        marital_status = pick_one(kTraditionalChineseMaritalStatus);
    } else if (selected_language == Languages::Japanese) {
        marital_status = pick_one(kJapaneseMaritalStatus);
    }

    return std::string(marital_status);
}

std::string
    phone_number(const bool is_international, const bool include_delimiters, const Regions regions, const bool unique) {
    const auto selected_region = pick_region(regions);

    std::size_t      index;
    std::size_t      seq_index = 0;
    std::string_view pattern;

    switch (selected_region) {
    case Regions::UnitedStates:
        index     = pick_index(kUnitedStatesPhoneNumberFormat);
        seq_index = index;
        pattern   = kUnitedStatesPhoneNumberFormat[index];
        break;
    case Regions::UnitedKingdom:
        index     = pick_index(kUnitedKingdomPhoneNumberFormat);
        seq_index = index + kUnitedStatesPhoneNumberFormat.size();
        pattern   = kUnitedKingdomPhoneNumberFormat[index];
        break;
    case Regions::China:
        index     = pick_index(kChinaPhoneNumberFormat);
        seq_index = index + kUnitedStatesPhoneNumberFormat.size() + kUnitedKingdomPhoneNumberFormat.size();
        pattern   = kChinaPhoneNumberFormat[index];
        break;
    case Regions::Japan:
        index     = pick_index(kJapanPhoneNumberFormat);
        seq_index = index +
                    kUnitedStatesPhoneNumberFormat.size() +
                    kUnitedKingdomPhoneNumberFormat.size() +
                    kChinaPhoneNumberFormat.size();
        pattern = kJapanPhoneNumberFormat[index];
        break;
    }
    std::string phone_number;

    // Generate a unique phone number if requested
    if (unique) {
        std::lock_guard<std::mutex> guard(phone_number_mutexes[seq_index]);
        if (phone_number_capacity[seq_index] == 0) {
            const uint64_t wildcard_count = std::count(pattern.begin(), pattern.end(), '#');
            uint64_t       capacity       = 1;
            for (size_t i = 0; i < wildcard_count; ++i) { capacity *= 10; }
            phone_number_capacity[seq_index]  = capacity;
            phone_number_wildcards[seq_index] = static_cast<uint8_t>(wildcard_count);
        }
        const uint64_t capacity       = phone_number_capacity[seq_index];
        const uint64_t wildcard_count = phone_number_wildcards[seq_index];
        if (!phone_number_pg_vector[seq_index].is_initialized()) {
            phone_number_pg_vector[seq_index].initialize(0, capacity - 1);
        }
        const uint64_t    seq     = phone_number_pg_vector[seq_index].next_uint64();
        const std::string seq_str = std::format("{:0{}}", seq, wildcard_count);
        phone_number              = replace_wildcard_with_sequence(pattern, '#', seq_str);
    } else {
        phone_number = replace_wildcard_with_digit(pattern);
    }
    const auto code = kRegionCodes.at(selected_region);

    if (!is_international) {
        // Add a leading zero for the United Kingdom and Japan
        if (selected_region == Regions::UnitedKingdom || selected_region == Regions::Japan) {
            const auto first_digit = std::find_if(phone_number.begin(), phone_number.end(), [](const unsigned char c) {
                return std::isdigit(c);
            });
            if (first_digit != phone_number.end()) {
                if (first_digit[0] != '0') { phone_number.insert(first_digit, '0'); }
            }
        }
    } else {
        phone_number = std::format("+{0} {1}", code, phone_number);
    }

    if (!include_delimiters) { phone_number = remove_characters(phone_number, " -()"); }

    return phone_number;
}

std::string
    email(const Languages languages, std::optional<std::span<const std::string_view>> domains, const bool unique) {
    std::string_view selected_domain;
    if (domains.has_value()) {
        check_empty<std::invalid_argument>(domains.value(), "domains");
        if (std::ranges::any_of(domains.value(), [](const std::string_view domain) { return domain.empty(); })) {
            throw_exception<std::invalid_argument>(
                "Invalid string: 'domains' must not contain empty items.",
                std::source_location::current()
            );
        }
        selected_domain = pick_one(domains.value());
    } else {
        selected_domain = pick_one(kEmailDefaultDomains);
    }

    const auto selected_language = pick_language(languages);

    constexpr Genders genders = Genders::M | Genders::F;

    const Bilingual bilingual = full_name(selected_language, genders);

    std::string user_name = remove_characters(bilingual.translation(), " -");

    if (unique) {
        std::string seq;
        {
            std::lock_guard<std::mutex> lock(email_pg_mutex);
            seq = email_pg.next();
        }
        user_name             += std::format("_{0}", seq);
    }

    std::string email = std::format("{0}@{1}", user_name, selected_domain);

    return email;
}

std::string job_title(const Languages languages) {
    const auto selected_language = pick_language(languages);

    std::string_view job_title;
    if (selected_language == Languages::English) {
        job_title = pick_one(kEnglishJobTitle);
    } else if (selected_language == Languages::SimplifiedChinese) {
        job_title = pick_one(kSimplifiedChineseJobTitle);
    } else if (selected_language == Languages::TraditionalChinese) {
        job_title = pick_one(kTraditionalChineseJobTitle);
    } else if (selected_language == Languages::Japanese) {
        job_title = pick_one(kJapaneseJobTitle);
    }

    return std::string(job_title);
}

Bilingual social_network_id(const Languages languages, const bool unique) {
    const auto selected_name_language = pick_language(languages);

    BilingualView social_network_id_view;

    switch (selected_name_language) {
    case Languages::English           : social_network_id_view = pick_one(kEnglishSocialNetworkId); break;
    case Languages::SimplifiedChinese : social_network_id_view = pick_one(kSimplifiedChineseSocialNetworkId); break;
    case Languages::TraditionalChinese: social_network_id_view = pick_one(kTraditionalChineseSocialNetworkId); break;
    case Languages::Japanese          : social_network_id_view = pick_one(kJapaneseSocialNetworkId); break;
    }

    std::string social_network_id_original(social_network_id_view.original);
    std::string social_network_id_translation(social_network_id_view.translation);

    if (unique) {
        std::string seq;
        {
            std::lock_guard<std::mutex> lock(social_network_id_pg_mutex);
            seq = social_network_id_pg.next();
        }
        social_network_id_original    += std::format("_{0}", seq);
        social_network_id_translation += std::format("_{0}", seq);
    }

    return {social_network_id_original, social_network_id_translation};
}

Person::Person(
    const Genders                                          genders,
    const Languages                                        languages,
    const Regions                                          regions,
    const std::optional<std::span<const std::string_view>> email_domains,
    const bool                                             unique
) :
    genders_(genders), languages_(languages), regions_(regions), unique_(unique) {
    if (email_domains.has_value()) {
        check_empty<std::invalid_argument>(email_domains.value(), "email_domains");
        if (std::ranges::any_of(email_domains.value(), [](const std::string_view domain) { return domain.empty(); })) {
            throw_exception<std::invalid_argument>(
                "Invalid string: 'email_domains' must not contain empty items.",
                std::source_location::current()
            );
        }
        email_domains_.assign(email_domains.value().begin(), email_domains.value().end());
    } else {
        email_domains_.assign(kEmailDefaultDomains.begin(), kEmailDefaultDomains.end());
    }

    roll();
}

Person::~Person() = default;

void Person::reroll() {
    roll();
}

Bilingual Person::full_name() const {
    return full_name_;
}

Bilingual Person::first_name() const {
    return first_name_;
}

Bilingual Person::last_name() const {
    return last_name_;
}

std::string Person::gender() const {
    return gender_;
}

std::string Person::title() const {
    return title_;
}

std::string Person::marital_status() const {
    return marital_status_;
}

std::string Person::phone_number(const bool is_international, const bool include_delimiters) const {
    std::string      phone_number = phone_number_;
    std::string_view region_code  = kRegionCodes.at(selected_region_);
    if (is_international) { phone_number = std::format("+{0} {1}", region_code, phone_number_); }

    if (!include_delimiters) { phone_number = remove_characters(phone_number, " -()"); }
    return phone_number;
}

std::string Person::email() const {
    return email_;
}

std::string Person::job_title() const {
    return job_title_;
}

Bilingual Person::social_network_id() const {
    return social_network_id_;
}

void Person::roll() {
    selected_gender_   = pick_gender(genders_);
    selected_language_ = pick_language(languages_);
    selected_region_   = pick_region(regions_);

    first_name_     = person::first_name(selected_language_, selected_gender_);
    last_name_      = person::last_name(selected_language_);
    full_name_      = format_full_name(selected_language_, first_name_, last_name_);
    gender_         = std::string(kGenders.at(selected_language_).at(selected_gender_));
    marital_status_ = person::marital_status(selected_language_);

    title_ = person::title(selected_language_, selected_gender_);
    if (selected_gender_ == Genders::F) {
        switch (selected_language_) {
        case Languages::English:
            if (marital_status_ == "single") {
                title_ = pick_one(kEnglishSingleFemaleTitle);
            } else {
                title_ = pick_one(kEnglishMarriedFemaleTitle);
            }
            break;
        case Languages::SimplifiedChinese:
            if (marital_status_ == "单身") {
                title_ = pick_one(kSimplifiedChineseSingleFemaleTitle);
            } else {
                title_ = pick_one(kSimplifiedChineseMarriedFemaleTitle);
            }
            break;
        case Languages::TraditionalChinese:
            if (marital_status_ == "單身") {
                title_ = pick_one(kTraditionalChineseSingleFemaleTitle);
            } else {
                title_ = pick_one(kTraditionalChineseMarriedFemaleTitle);
            }
            break;
        case Languages::Japanese: break;
        }
    }

    phone_number_ = person::phone_number(false, true, selected_region_, unique_);

    auto selected_domain = pick_one<std::string>(email_domains_);

    const auto  full_name_eng = full_name_.translation();
    std::string user_name     = remove_characters(full_name_eng, " -");
    if (unique_) {
        std::string seq;
        {
            std::lock_guard<std::mutex> lock(email_pg_mutex);
            seq = email_pg.next();
        }
        user_name             += std::format("_{0}", seq);
    }
    email_ = std::format("{0}@{1}", user_name, selected_domain);

    job_title_         = person::job_title(selected_language_);
    social_network_id_ = person::social_network_id(selected_language_, unique_);
}

}  // namespace faker::person
