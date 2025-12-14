// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file location.h

#ifndef FAKER_LOCATION_H
#define FAKER_LOCATION_H

#include "faker/internal/macros.h"
#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

namespace faker::location {

/// @brief Generates random address line 1.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return Address line 1.
/// @note You need to use class @code faker::Bilingual@endcode to get address line 1.
/// @code
/// faker::location::address_line1();  // "998 W Main St"
/// faker::location::address_line1(faker::Regions::China | faker::Regions::Japan);  // "中南路81号" or "神宮前6-46-66"
/// @endcode
FAKER_EXPORT Bilingual address_line1(Regions regions = Regions::UnitedStates);

/// @brief Generates random address line 2.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return Address line 2, it might be empty.
/// @note You need to use class @code faker::Bilingual@endcode to get address line 2.
/// @code
/// faker::location::address_line2();  // "Unit 518"
/// faker::location::address_line2(faker::Regions::China | faker::Regions::Japan);  // "6栋501室" or "渋谷17ビル"
/// @endcode
FAKER_EXPORT Bilingual address_line2(Regions regions = Regions::UnitedStates);

/// @brief Generates a random postal code or zip code or postcode.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return A postal code or zip code or postcode.
/// @code
/// faker::location::postcode();  // "42101-3057"
/// faker::location::postcode(faker::Regions::UnitedKingdom | faker::Regions::China);  // "EC1A 1BB" or "211100"
/// @endcode
FAKER_EXPORT std::string postcode(Regions regions = Regions::UnitedStates);

/// @brief Generates random full address.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return Full address.
/// @note You need to use class @code faker::Bilingual@endcode to get full address.
///       If International format address is needed, @code Translate()@endcode can be used.
/// @code
/// faker::Bilingual addr = faker::location::full_address();  //  "238 Mulberry St, Macon, GA 31201-7534"
/// addr.translation();  // "238 Mulberry St, Macon, GA 31201-7534, United States"
/// faker::location::full_address(faker::Regions::China | faker::Regions::Japan);
/// //  "广东省深圳市罗湖区东门街道东门中路76号" or "東京都渋谷区神宮前9-59-43"
/// @endcode
FAKER_EXPORT Bilingual full_address(Regions regions = Regions::UnitedStates);

/// @brief Generates a random city.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return A city.
/// @note You need to use class @code faker::Bilingual@endcode to get city.
/// @code
/// faker::location::city();  // "Chicago"
/// faker::location::city(faker::Regions::China | faker::Regions::Japan);  // "广州市" or "北海道"
/// @endcode
FAKER_EXPORT Bilingual city(Regions regions = Regions::UnitedStates);

/// @brief Generates a random region.
/// @param country_codes_standard Country codes standard. Defaults to CountryCodesStandard::None.
/// @param languages The languages of the region. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A region.
/// @code
/// faker::location::region();  // "United States"
/// faker::location::region(
///     faker::CountryCodesStandard::None,
///     faker::Languages::SimplifiedChinese);  // "英国"
/// @endcode
FAKER_EXPORT std::string region(
    CountryCodesStandard country_codes_standard = CountryCodesStandard::None,
    Languages languages                         = Languages::English
);

/// @brief Represents a location entity with a generated
///        address line 1, address line 2, postal code, full address and city
///        that are strongly correlated and contextually appropriate.
/// @code
/// faker::location::Location l1();
/// l1.address_line1();  // "574 Ocean Dr"
/// l1.address_line2();  // ""
/// l1.postcode();  // "33139-0091"
/// l1.full_address();  // "574 Ocean Dr, Miami Beach, FL 33139-0091"
/// l1.city();  // "Miami beach"
/// faker::location::Location l2(faker::Regions::China);
/// l2.address_line1();  // "青年大街28号"
/// l2.address_line2();  // "5座5层"
/// l2.postcode();  // "110015"
/// l2.full_address();  // "辽宁省沈阳市沈河区五里河街道青年大街28号5座5层"
/// l2.city();  // "沈阳市"
/// @endcode
class FAKER_EXPORT Location {
public:
    /// @brief Constructs a location entity.
    /// @param regions The regions of the location. Defaults to Regions::UnitedStates.
    explicit Location(Regions regions = Regions::UnitedStates);

    /// @brief Destroys the location entity.
    ~Location();

    /// @brief Regenerates location data.
    void reroll();

    /// @brief Get address line 1.
    /// @return Address line 1.
    /// @note You need to use class @code faker::Bilingual@endcode to get address line 1.
    [[nodiscard]] Bilingual address_line1() const;

    /// @brief Get address line 2.
    /// @return Address line 2.
    /// @note You need to use class @code faker::Bilingual@endcode to get address line 2.
    [[nodiscard]] Bilingual address_line2() const;

    /// @brief Get the postal code.
    /// @return Postal code.
    [[nodiscard]] std::string postcode() const;

    /// @brief Get full address.
    /// @return Full address.
    /// @note You need to use class @code faker::Bilingual@endcode to get full address.
    [[nodiscard]] Bilingual full_address() const;

    /// @brief Get the city.
    /// @return City.
    /// @note You need to use class @code faker::Bilingual@endcode to get city.
    [[nodiscard]] Bilingual city() const;

    /// @brief Get the region.
    /// @param country_codes_standard Country codes standard. Defaults to CountryCodesStandard::None.
    /// @param languages The languages of the region. Defaults to Languages::English.
    /// @return Region.
    [[nodiscard]] std::string region(
        CountryCodesStandard country_codes_standard = CountryCodesStandard::None,
        Languages languages                         = Languages::English
    ) const;

private:
    // Constructor parameters.
    Regions regions_;

    // Selection.
    Regions selected_region_ = Regions::UnitedStates;

    // Generated data.
    Bilingual   address_line1_;
    Bilingual   address_line2_;
    std::string postcode_;
    Bilingual   full_address_;
    Bilingual   city_;

    // Generates location data.
    void roll();
};

}  // namespace faker::location

#endif  // FAKER_LOCATION_H
