// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file location.cpp

#include "faker/location.h"

#include <format>
#include <string>
#include <tuple>

#include "faker/types/bilingual.h"
#include "faker/types/enums.h"
#include "location_data.h"
#include "random_helper.h"
#include "string_helper.h"

namespace faker::location {

static AddressComponents pick_address_component(const Regions region) {
    AddressComponents address_components;
    switch (region) {
    case Regions::UnitedStates : address_components = pick_one(kUnitedStatesAddressComponents); break;
    case Regions::UnitedKingdom: address_components = pick_one(kUnitedKingdomAddressComponents); break;
    case Regions::China        : address_components = pick_one(kChinaAddressComponents); break;
    case Regions::Japan        : address_components = pick_one(kJapanAddressComponents); break;
    }
    return address_components;
}

static BilingualView get_city(const Regions region, const AddressComponents& address_components) {
    int city_level = 1;
    switch (region) {
    case Regions::UnitedStates : city_level = KUnitedStatesCityLevel; break;
    case Regions::UnitedKingdom: city_level = KUnitedKingdomCityLevel; break;
    case Regions::China        : city_level = KChinaCityLevel; break;
    case Regions::Japan        : city_level = KJapanCityLevel; break;
    }

    if (city_level > address_components.admin_levels.size()) { city_level = 0; }

    return address_components.admin_levels[city_level];
}

static std::tuple<std::string, Bilingual, Bilingual, Bilingual>
    format_address(const Regions region, const AddressComponents& address_components) {
    std::string postcode = replace_wildcard_to_letter(
        replace_wildcard_to_digit(address_components.postcode),
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    );

    auto [street_original_tmp, street_translation_tmp] = replace_wildcards_with_same_digits(
        address_components.street.original,
        address_components.street.translation,
        "123456789"
    );
    auto [street_original, street_translation] =
        replace_wildcards_with_same_letters(street_original_tmp, street_translation_tmp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    auto [building_original_tmp, building_translation_tmp] = replace_wildcards_with_same_digits(
        address_components.building.original,
        address_components.building.translation,
        "123456789"
    );
    auto [building_original, building_translation] = replace_wildcards_with_same_letters(
        building_original_tmp,
        building_translation_tmp,
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    );

    std::string admin_levels_original;
    std::string admin_levels_translation;
    std::string address_line_original;
    std::string address_line_translation;
    std::string full_address_original;
    std::string full_address_translation;
    switch (region) {
    case Regions::UnitedStates:
        // House number and street name + Apartment/Suite/Room number, City, State, Zip code
        for (size_t i = address_components.admin_levels.size(); i-- > 0;) {
            if (address_components.admin_levels[i].original.empty()) { continue; }
            admin_levels_original    += address_components.admin_levels[i].original;
            admin_levels_translation += address_components.admin_levels[i].translation;
            if (i > 0 && !address_components.admin_levels[i - 1].original.empty()) {
                admin_levels_original    += ", ";
                admin_levels_translation += ", ";
            }
        }

        if (!building_original.empty()) {
            address_line_original    = std::format("{0} {1}", street_original, building_original);
            address_line_translation = std::format("{0} {1}", street_translation, building_translation);
        } else {
            address_line_original    = street_original;
            address_line_translation = street_translation;
        }

        full_address_original    = std::format("{0}, {1} {2}", address_line_original, admin_levels_original, postcode);
        full_address_translation = std::format(
            "{0}, {1}, {2}, {3}",
            address_line_translation,
            admin_levels_translation,
            postcode,
            std::string_view(kRegions.at(Languages::English).at(Regions::UnitedStates))
        );
        break;
    case Regions::UnitedKingdom:
        // Number supplement and street name, Locality(only if required), POST TOWN, POST CODE
        for (size_t i = address_components.admin_levels.size(); i-- > 0;) {
            if (address_components.admin_levels[i].original.empty()) { continue; }
            admin_levels_original    += address_components.admin_levels[i].original;
            admin_levels_translation += address_components.admin_levels[i].translation;
            if (i > 0 && !address_components.admin_levels[i - 1].original.empty()) {
                admin_levels_original    += ", ";
                admin_levels_translation += ", ";
            }
        }

        if (!building_original.empty()) {
            address_line_original    = std::format("{0}, {1}", building_original, street_original);
            address_line_translation = std::format("{0}, {1}", building_translation, street_translation);
        } else {
            address_line_original    = street_original;
            address_line_translation = street_translation;
        }

        full_address_original    = std::format("{0}, {1} {2}", address_line_original, admin_levels_original, postcode);
        full_address_translation = std::format(
            "{0}, {1}, {2}, {3}",
            address_line_translation,
            admin_levels_translation,
            postcode,
            std::string_view(kRegions.at(Languages::English).at(Regions::UnitedKingdom))
        );
        break;
    case Regions::China:
        // Province, Prefecture-level city, County, Town, Road Name, Road Number
        for (const auto& [original, translation] : address_components.admin_levels) {
            if (original.empty()) { continue; }
            admin_levels_original += original;
        }
        for (size_t i = address_components.admin_levels.size(); i-- > 0;) {
            if (address_components.admin_levels[i].original.empty()) { continue; }
            admin_levels_translation += address_components.admin_levels[i].translation;
            if (i > 0 && !address_components.admin_levels[i - 1].original.empty()) { admin_levels_translation += ", "; }
        }

        if (!building_original.empty()) {
            address_line_original    = std::format("{0}{1}", street_original, building_original);
            address_line_translation = std::format("{0}, {1}", building_translation, street_translation);
        } else {
            address_line_original    = street_original;
            address_line_translation = street_translation;
        }

        full_address_original    = std::format("{0}{1}", admin_levels_original, address_line_original);
        full_address_translation = std::format(
            "{0}, {1}, {2}",
            address_line_translation,
            admin_levels_translation,
            std::string_view(kRegions.at(Languages::English).at(Regions::China))
        );
        break;
    case Regions::Japan:
        // Province, Prefecture-level city, County, Town, Road Name, Road Number
        for (const auto& [original, translation] : address_components.admin_levels) {
            if (original.empty()) { continue; }
            admin_levels_original += original;
        }
        for (size_t i = address_components.admin_levels.size(); i-- > 0;) {
            if (address_components.admin_levels[i].original.empty()) { continue; }
            admin_levels_translation += address_components.admin_levels[i].translation;
            if (i > 0 && !address_components.admin_levels[i - 1].original.empty()) { admin_levels_translation += ", "; }
        }

        if (!building_original.empty()) {
            address_line_original    = std::format("{0}{1}", street_original, building_original);
            address_line_translation = std::format("{0}, {1}", building_translation, street_translation);
        } else {
            address_line_original    = street_original;
            address_line_translation = street_translation;
        }

        full_address_original    = std::format("{0}{1}", admin_levels_original, address_line_original);
        full_address_translation = std::format(
            "{0}, {1}, {2}",
            address_line_translation,
            admin_levels_translation,
            std::string_view(kRegions.at(Languages::English).at(Regions::Japan))
        );
        break;
    }

    Bilingual address_line1{street_original, street_translation};
    Bilingual address_line2{building_original, building_translation};
    Bilingual full_address{full_address_original, full_address_translation};

    return std::make_tuple(postcode, address_line1, address_line2, full_address);
}

Bilingual address_line1(const Regions regions) {
    const auto selected_region   = pick_region(regions);
    const auto address_component = pick_address_component(selected_region);
    const std::tuple<std::string, Bilingual, Bilingual, Bilingual> address_tuple =
        format_address(selected_region, address_component);
    return std::get<1>(address_tuple);
}

Bilingual address_line2(const Regions regions) {
    const auto selected_region   = pick_region(regions);
    const auto address_component = pick_address_component(selected_region);
    const std::tuple<std::string, Bilingual, Bilingual, Bilingual> address_tuple =
        format_address(selected_region, address_component);
    return std::get<2>(address_tuple);
}

std::string postcode(const Regions regions) {
    const auto selected_region   = pick_region(regions);
    const auto address_component = pick_address_component(selected_region);
    const std::tuple<std::string, Bilingual, Bilingual, Bilingual> address_tuple =
        format_address(selected_region, address_component);
    return std::get<0>(address_tuple);
}

Bilingual full_address(const Regions regions) {
    const auto selected_region   = pick_region(regions);
    const auto address_component = pick_address_component(selected_region);
    const std::tuple<std::string, Bilingual, Bilingual, Bilingual> address_tuple =
        format_address(selected_region, address_component);
    return std::get<3>(address_tuple);
}

Bilingual city(const Regions regions) {
    const auto selected_region   = pick_region(regions);
    const auto address_component = pick_address_component(selected_region);
    auto [original, translation] = get_city(selected_region, address_component);
    return {capitalize(original), capitalize(translation)};
}

std::string region(const CountryCodesStandard country_codes_standard, const Languages languages) {
    const auto selected_language = pick_language(languages);
    const auto selected_region =
        pick_region(Regions::UnitedStates | Regions::UnitedKingdom | Regions::China | Regions::Japan);
    if (country_codes_standard == CountryCodesStandard::None) {
        return std::string(kRegions.at(selected_language).at(selected_region));
    }
    return std::string(kRegionsByCountryCodesStandards.at(country_codes_standard).at(selected_region));
}

Location::Location(const Regions regions) : regions_(regions) {
    roll();
}

Location::~Location() = default;

void Location::reroll() {
    roll();
}

Bilingual Location::address_line1() const {
    return address_line1_;
}

Bilingual Location::address_line2() const {
    return address_line2_;
}

std::string Location::postcode() const {
    return postcode_;
}

Bilingual Location::full_address() const {
    return full_address_;
}

Bilingual Location::city() const {
    return city_;
}

std::string Location::region(const CountryCodesStandard country_codes_standard, const Languages languages) const {
    const auto selected_language = pick_language(languages);
    if (country_codes_standard == CountryCodesStandard::None) {
        return std::string(kRegions.at(selected_language).at(selected_region_));
    }
    return std::string(kRegionsByCountryCodesStandards.at(country_codes_standard).at(selected_region_));
}

void Location::roll() {
    selected_region_ = pick_region(regions_);

    const auto address_component                 = pick_address_component(selected_region_);
    const auto [city_original, city_translation] = get_city(selected_region_, address_component);
    const std::tuple<std::string, Bilingual, Bilingual, Bilingual> address_tuple =
        format_address(selected_region_, address_component);

    address_line1_ = std::get<1>(address_tuple);
    address_line2_ = std::get<2>(address_tuple);
    postcode_      = std::get<0>(address_tuple);
    full_address_  = std::get<3>(address_tuple);
    city_          = Bilingual(capitalize(city_original), capitalize(city_translation));
}

}  // namespace faker::location
