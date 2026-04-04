// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file payment.h

#ifndef FAKER_PAYMENT_H
#define FAKER_PAYMENT_H

#include <optional>
#include <source_location>
#include <span>
#include <string>
#include <string_view>

#include "faker/internal/export.h"
#include "faker/types/enums.h"

namespace faker::payment {

/// @brief Generates a random payment method.
/// @param payment_methods The list of payment methods.
///                        Defaults to std::nullopt, equivalent to {"Credit Card", "PayPal", "Apple Pay"}.
///                        If empty, throws an error.
/// @return A payment method.
/// @code
/// faker::payment::payment_method();  // "PayPal"
/// faker::payment::payment_method(std::to_array<std::string_view>({"WeChat Pay", "Alipay"}));  // "Alipay"
/// @endcode
FAKER_EXPORT std::string payment_method(
    std::optional<std::span<const std::string_view>> payment_methods = std::nullopt
);

/// @brief Generates a random card type.
/// @param languages The languages of card type. Defaults to Languages::English.
///                  If multiple languages are specified, the bitwise OR (`|`) operator can be used.
/// @param card_types The selected card types.
///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
///                   If multiple card types are specified, the bitwise OR (`|`) operator can be used.
/// @return A card type string.
/// @code
/// faker::payment::card_type();  // "American Express"
/// faker::payment::card_type(faker::Languages::SimplifiedChinese,
///                          faker::CardTypes::MasterCard |
///                          faker::CardTypes::UnionPay |
///                          faker::CardTypes::Visa);  // "万事达卡"
/// @endcode
FAKER_EXPORT std::string card_type(
    Languages languages = Languages::English,
    CardTypes card_types =
        CardTypes::AmericanExpress | CardTypes::JCB | CardTypes::MasterCard | CardTypes::UnionPay | CardTypes::Visa
);

/// @brief Generates a random card number.
/// @param card_types The selected card types.
///                   If multiple card types are specified, the bitwise OR (`|`) operator can be used.
///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
/// @param unique Whether to generate a unique card number. Defaults to false.
/// @return A card number.
/// @code
/// faker::payment::card_number();  // "371608770166525"
/// faker::payment::card_number(faker::CardTypes::UnionPay);  // "6212826123992956"
/// @endcode
/// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
FAKER_EXPORT std::string card_number(
    CardTypes card_types =
        CardTypes::AmericanExpress | CardTypes::JCB | CardTypes::MasterCard | CardTypes::UnionPay | CardTypes::Visa,
    bool unique = false
);

/// @brief Generates a random issue or valid through date of a card.
/// @param start_month The start month in the format of "mm/YY". Defaults to "01/00".
/// @param end_month The end month in the format of "mm/YY". Defaults to "12/50".
/// @return A card date in the format of "mm/YY".
/// @code
/// faker::payment::card_date();  // "07/25"
/// faker::payment::card_date("03/11", "04/12");  // "03/12"
/// @endcode
FAKER_EXPORT std::string card_date(
    std::string_view start_month = "01/00",
    std::string_view end_month   = "12/50"
);

/// @brief Represents a card entity with a generated type, number and date
///        that are strongly correlated and contextually appropriate.
/// @code
/// faker::payment::Card c1();
/// c1.type();  // "JCB"
/// c1.number();  // "3529397175057255"
/// c1.date();  // "5/22"
/// faker::payment::Card c2(faker::Languages::SimplifiedChinese, faker::CardTypes::UnionPay | faker::CardTypes::Visa,
///                         "4/10", "8/30");
/// c2.type();  // "银联"
/// c2.number();  // "6222308709432476257"
/// c2.date();  // "6/28"
/// @endcode
class FAKER_EXPORT Card {
public:
    /// @brief Constructs a card entity.
    /// @param languages The language of card type. Defaults to Languages::English.
    ///                  If multiple languages are specified, the bitwise OR (`|`) operator can be used.
    /// @param card_types The selected card types.
    ///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
    ///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
    ///                   If multiple card types are specified, the bitwise OR (`|`) operator can be used.
    /// @param start_month The start month in the format of "mm/YY". Defaults to "01/00".
    /// @param end_month The end month in the format of "mm/YY". Defaults to "12/50".
    /// @param unique Whether to generate a unique card number.
    ///               Supported data: card_number.
    ///               Defaults to false.
    /// @note The unique option has a runtime generation limit. Exceeding it may cause errors.
    explicit Card(
        Languages languages = Languages::English,
        CardTypes card_types =
            CardTypes::AmericanExpress | CardTypes::JCB | CardTypes::MasterCard | CardTypes::UnionPay | CardTypes::Visa,
        std::string_view start_month = "01/00",
        std::string_view end_month   = "12/50",
        bool             unique = false
    );

    /// @brief Destroys the card entity.
    ~Card();

    /// @brief Regenerates card data.
    void reroll();

    /// @brief Gets the type of the card.
    [[nodiscard]] std::string type() const;

    /// @brief Gets the number of the card.
    [[nodiscard]] std::string number() const;

    /// @brief Gets the issue date or "valid through" date of the card.
    [[nodiscard]] std::string date() const;

    /// @brief Gets the payment method of the card.
    /// @return Payment method string, always "Credit Card".
    [[nodiscard]] std::string payment_method() const;

private:
    // Location
    std::source_location location = std::source_location::current();

    // Constructor parameters
    Languages   languages_;
    CardTypes   card_types_;
    std::string start_month_;
    std::string end_month_;
    bool        unique_;

    // Selection
    Languages language_  = Languages::English;
    CardTypes card_type_ = CardTypes::AmericanExpress;

    // Generated data
    std::string type_;
    std::string number_;
    std::string date_;
    std::string payment_method_;

    // Generates card data
    void roll();
};

}  // namespace faker::payment

#endif  // FAKER_PAYMENT_H
