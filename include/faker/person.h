// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file person.h

#ifndef FAKER_PERSON_H
#define FAKER_PERSON_H

#include <string>

#include "faker/internal/macros.h"
#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

namespace faker::person {

/// @brief Generates a random first name.
/// @param languages The languages of the first name. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param genders The genders. Defaults to Genders::M | Genders::F.
///                If multiple genders are specified, bitwise(bitwise_or |) operator can be used.
/// @return A first name.
/// @note You need to use class @code faker::Bilingual@endcode to get first name.
/// @code
/// faker::person::first_name();  // "Virginia"
/// faker::person::first_name(faker::Languages::SimplifiedChinese |
///                          faker::Languages::TraditionalChinese |
///                          faker::Languages::Japanese);  // "慕安"
/// faker::person::first_name(faker::Languages::SimplifiedChinese, faker::Genders::F).Translate();  // "Qiaoyun"
/// @endcode
FAKER_EXPORT Bilingual first_name(Languages languages = Languages::English, Genders genders = Genders::M | Genders::F);

/// @brief Generates a random last name.
/// @param languages The languages of the last name. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A last name.
/// @note You need to use class @code faker::Bilingual@endcode to get last name.
/// @code
/// faker::person::last_name();  // "Chambers"
/// faker::person::last_name(faker::Languages::SimplifiedChinese |
///                         faker::Languages::TraditionalChinese |
///                         faker::Languages::Japanese);  // "张"
/// @endcode
FAKER_EXPORT Bilingual last_name(Languages languages = Languages::English);

/// @brief Generates a full name.
/// @param languages The languages of the full name. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param genders The genders. Defaults to Genders::M | Genders::F.
///                If multiple genders are specified, bitwise(bitwise_or |) operator can be used.
/// @return A full name.
/// @note You need to use class @code faker::Bilingual@endcode to get full name.
/// @code
/// faker::person::full_name();  // "Lucas Perry"
/// faker::person::full_name(faker::Languages::SimplifiedChinese |
///                         faker::Languages::TraditionalChinese |
///                         faker::Languages::Japanese);  // "寺西聖良"
/// faker::person::full_name(faker::Languages::SimplifiedChinese, faker::Genders::F).Translate();  // "Zhang Qiaoyun"
/// @endcode
FAKER_EXPORT Bilingual full_name(Languages languages = Languages::English, Genders genders = Genders::M | Genders::F);

/// @brief Generates a random gender.
/// @param languages The languages of the gender. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A gender.
/// @code
/// faker::person::gender();  // "Female"
/// faker::person::gender(faker::Languages::SimplifiedChinese | faker::Languages::TraditionalChinese);  // "男"
/// @endcode
FAKER_EXPORT std::string gender(Languages languages = Languages::English);

/// @brief Generates a random title.
/// @param languages The languages of the title. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param genders The genders. Defaults to Genders::M | Genders::F.
///                If multiple genders are specified, bitwise(bitwise_or |) operator can be used.
/// @return A title.
/// @code
/// faker::person::title();  // "Prof."
/// faker::person::title(faker::Languages::SimplifiedChinese |
///                      faker::Languages::TraditionalChinese |
///                      faker::Languages::Japanese);  // "教授"
/// faker::person::title(faker::Languages::SimplifiedChinese |
///                      faker::Languages::TraditionalChinese |
///                      faker::Languages::Japanese,
///                      faker::Genders::F);  // "小姐"
/// @endcode
FAKER_EXPORT std::string title(Languages languages = Languages::English, Genders genders = Genders::M | Genders::F);

/// @brief Generates a random marital status.
/// @param languages The languages of the marital status. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return Marital status.
/// @code
/// faker::person::marital_status();  // "Single"
/// faker::person::marital_status(faker::Languages::TraditionalChinese | faker::Languages::Japanese);  // "既婚"
/// @endcode
FAKER_EXPORT std::string marital_status(Languages languages = Languages::English);

/// @brief Generates a random phone number.
/// @param is_international Whether the phone number format is international. Defaults to false.
/// @param include_delimiters Whether to include delimiters such as '-' or spaces. Defaults to true.
/// @param regions Regions. Defaults to Regions::UnitedStates.
///                If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
/// @return A phone number string.
/// @code
/// faker::person::phone_number();  // "319-248-9499"
/// faker::person::phone_number(false, false, faker::Regions::UnitedStates | faker::Regions::China);  // "14581499058"
/// faker::person::phone_number(true, true, faker::Regions::UnitedStates);  // "+1 216-712-4643"
/// @endcode
FAKER_EXPORT std::string phone_number(
    bool is_international   = false,
    bool include_delimiters = true,
    Regions regions         = Regions::UnitedStates
);

/// @brief Generates a random email.
/// @param languages The languages of the email. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param domains The list of domains. Defaults to "gmail.com,hotmail.com".
///                If empty, throw error.
/// @param delimiter Delimiter of domains.
/// @return An email.
/// @code
/// faker::person::email();  // "CannonDean7011@gmail.com"
/// faker::person::email(faker::Languages::SimplifiedChinese | faker::Languages::TraditionalChinese,
///                      "163.com, qq.com", ',');  // "LengYiyi987@163.com"
/// @endcode
FAKER_EXPORT std::string email(
    Languages languages      = Languages::English,
    std::string_view domains = "gmail.com,hotmail.com",
    char delimiter           = ','
);

/// @brief Generates a random job title.
/// @param languages The languages of the job title. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A job title.
/// @code
/// faker::person::job_title();  // "Electrical Engineer"
/// faker::person::job_title(faker::Languages::SimplifiedChinese | faker::Languages::TraditionalChinese);  // "写真家"
/// @endcode
FAKER_EXPORT std::string job_title(Languages languages = Languages::English);

/// @brief Generates a random social network ID.
/// @param languages The languages of the social network ID. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A social network ID.
/// @code
/// faker::person::social_network_id();  // "Cyanelle479"
/// faker::person::social_network_id(faker::Languages::SimplifiedChinese |
///                                faker::Languages::TraditionalChinese);  // "天星回憶_official"
/// @endcode
FAKER_EXPORT Bilingual social_network_id(Languages languages = Languages::English);

/// @brief Represents a person entity with a generated first name, last name, full name,
///        gender, title, marital status, phone number, email, job title and social network ID.
/// @code
/// faker::person::Person p1;
/// p1.first_name();  // "Spencer"
/// p1.last_name();  // "Henson"
/// p1.full_name();  // "Spencer Henson"
/// p1.gender();  // "Male"
/// p1.title();  // "Dr."
/// p1.marital_status();  // "Separated"
/// p1.phone_number();  // "229-652-3995"
/// p1.email();  // "SpencerHenson_live@gmail.com"
/// p1.job_title();  // "Dentist"
/// p1.social_network_id();  // "DynaraKing"
/// faker::person::Person
/// p2(faker::Genders::F, faker::Languages::TraditionalChinese, faker::Regions::China, "qq.com,163.com", ',');
/// p2.first_name();  // "左詩晴"
/// p2.last_name();  // "詩晴"
/// p2.full_name();  // "左"
/// p2.gender();  // "女"
/// p2.title();  // "女士"
/// p2.marital_status();  // "已婚"
/// p2.phone_number();  // "130 9088 1583"
/// p2.email();  // "TsoSzeching.live@qq.com"
/// p2.job_title();  // "心理諮商師"
/// p2.social_network_id();  // "獅子山下呀"
/// @endcode
class FAKER_EXPORT Person {
public:
    /// @brief Constructs a person entity.
    /// @param genders The genders. Defaults to Genders::M | Genders::F.
    ///                If multiple genders are specified, bitwise(bitwise_or |) operator can be used.
    /// @param languages The languages. Defaults to Languages::English.
    ///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
    /// @param regions Regions. Defaults to Regions::UnitedStates.
    ///                             If multiple regions are specified, bitwise(bitwise_or |) operator can be used.
    /// @param email_domains The list of domains. Defaults to "gmail.com,hotmail.com".
    ///                      If empty, throw error.
    /// @param email_domains_delimiter Delimiter of domains.
    explicit Person(
        Genders genders                = Genders::M | Genders::F,
        Languages languages            = Languages::English,
        Regions regions                = Regions::UnitedStates,
        std::string_view email_domains = "gmail.com,hotmail.com",
        char email_domains_delimiter   = ','
    );

    /// @brief Destroys the person entity.
    ~Person();

    /// @brief Regenerates person data
    void reroll();

    /// @brief Gets the full name.
    /// @note You need to use class @code faker::Bilingual@endcode to get full name.
    [[nodiscard]] Bilingual full_name() const;

    /// @brief Gets the first name.
    /// @note You need to use class @code faker::Bilingual@endcode to get first name.
    [[nodiscard]] Bilingual first_name() const;

    /// @brief Gets the last name.
    /// @note You need to use class @code faker::Bilingual@endcode to get last name.
    [[nodiscard]] Bilingual last_name() const;

    /// @brief Gets the gender.
    [[nodiscard]] std::string gender() const;

    /// @brief Gets the title.
    [[nodiscard]] std::string title() const;

    /// @brief Gets the marital status.
    [[nodiscard]] std::string marital_status() const;

    /// @brief Gets the phone number string.
    [[nodiscard]] std::string phone_number(bool is_international = false, bool include_delimiters = true) const;

    /// @brief Gets the email.
    [[nodiscard]] std::string email() const;

    /// @brief Gets the job title.
    [[nodiscard]] std::string job_title() const;

    /// @brief Gets the social network ID.
    [[nodiscard]] Bilingual social_network_id() const;

private:
    // Constructor parameters
    Genders     genders_;
    Languages   languages_;
    Regions     regions_;
    std::string email_domains_;
    char        email_domains_delimiter_;

    // Selection
    Genders   selected_gender_   = Genders::M;
    Languages selected_language_ = Languages::English;
    Regions   selected_region_   = Regions::UnitedStates;

    // Generated the person data
    Bilingual   first_name_;
    Bilingual   last_name_;
    Bilingual   full_name_;
    std::string gender_;
    std::string title_;
    std::string marital_status_;
    std::string phone_number_;
    std::string email_;
    std::string job_title_;
    Bilingual   social_network_id_;

    // Generates person data
    void roll();
};

}  // namespace faker::person

#endif  // FAKER_PERSON_H
