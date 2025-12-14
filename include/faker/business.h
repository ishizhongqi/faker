// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file business.h

#ifndef FAKER_BUSINESS_H
#define FAKER_BUSINESS_H

#include <string>

#include "faker/internal/macros.h"
#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

namespace faker::business {

/// @brief Generates a random company name.
/// @param languages The languages of the company name. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A company name.
/// @note You need to use class @code faker::Bilingual@endcode to get company name.
/// @code
/// faker::business::company_name();  // "Meza Brothers Equipment Inc."
/// faker::business::company_name(faker::Languages::SimplifiedChinese); // "戎氏兄弟房地产股份有限公司"
/// faker::business::company_name(faker::Languages::SimplifiedChinese | faker::Languages::Japanese);
/// // "戎氏兄弟房地产股份有限公司" or "根岸商店ネットワーク株式会社"
/// @endcode
FAKER_EXPORT Bilingual company_name(Languages languages = Languages::English);

/// @brief Generates a random department.
/// @param languages The languages of the department. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return A department.
/// @code
/// faker::business::department();  // "Public Relations"
/// faker::business::department(faker::Languages::Japanese);  // "マーケティング部"
/// faker::business::department(faker::Languages::SimplifiedChinese | faker::Languages::Japanese);
/// // "会计及金融部" or "マーケティング部"
/// @endcode
FAKER_EXPORT std::string department(Languages languages = Languages::English);

/// @brief Generates a random industry.
/// @param languages The languages of the industry. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @return An industry.
/// @code
/// faker::business::industry();  // "Consulting industry"
/// faker::business::industry(faker::Languages::Japanese);  // "金融サービス業界"
/// faker::business::industry(faker::Languages::SimplifiedChinese | faker::Languages::Japanese);
/// // "金融服务业 " or "金融サービス業界"
/// @endcode
FAKER_EXPORT std::string industry(Languages languages = Languages::English);

/// @brief Represents a company entity with a generated name and industry
///        that are strongly correlated and contextually appropriate.
/// @code
/// faker::business::Company c1();
/// c1.name();  // "Lewis Logistic Inc."
/// c1.industry();  // "Logistic industry"
/// faker::business::Company c2(faker::NameLanguages::SimplifiedChinese, faker::Languages::SimplifiedChinese);
/// c2.name();  // "易氏制药有限责任公司"
/// c2.industry();  // "制药业"
/// @endcode
class FAKER_EXPORT Company {
public:
    /// @brief Constructs a company entity.
    /// @param languages The languages of the industry. Defaults to Languages::English.
    ///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
    explicit Company(Languages languages = Languages::English);

    /// @brief Destroys the company entity.
    ~Company();

    /// @brief Regenerates company data.
    void reroll();

    /// @brief Gets the company name.
    /// @return Company name.
    /// @note You need to use class @code faker::Bilingual@endcode to get company name.
    [[nodiscard]] Bilingual name() const;

    /// @brief Gets the industry.
    /// @return Industry.
    [[nodiscard]] std::string industry() const;

private:
    // Constructor parameters.
    Languages languages_;

    // Selection.
    Languages selected_language_ = Languages::English;

    // Generated data.
    Bilingual   name_;
    std::string industry_;

    // Generates company data.
    void roll();
};

}  // namespace faker::business

#endif  // FAKER_BUSINESS_H
