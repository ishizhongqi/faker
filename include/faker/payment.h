// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file payment.h

#ifndef FAKER_PAYMENT_H
#define FAKER_PAYMENT_H

#include <source_location>
#include <string>

#include "faker/internal/macros.h"
#include "faker/types/enums.h"

namespace faker::payment {

/// @brief Generates a random payment method.
/// @param payment_methods The list of payment methods. Defaults to "Credit Card, PayPal, Apple Pay".
///                        If empty, throw error.
/// @param delimiter Delimiter of payment methods.
/// @return A payment method.
/// @code
/// faker::payment::payment_method();  // "PayPal"
/// faker::payment::payment_method("WeChat Pay | Alipay", '|');  // "Alipay"
/// @endcode
FAKER_EXPORT std::string
          payment_method(std::string_view payment_methods = "Credit Card, PayPal, Apple Pay", char delimiter = ',');

/// @brief Generates a random card type.
/// @param languages The languages of card type. Defaults to Languages::English.
///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
/// @param card_types The selected card types.
///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
///                   If multiple card types are specified, bitwise(bitwise_or |) operator can be used.
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
///                   If multiple card types are specified, bitwise(bitwise_or |) operator can be used.
///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
/// @return A card number.
/// @code
/// faker::payment::card_number();  // "371608770166525"
/// faker::payment::card_number(faker::CardTypes::UnionPay);  // "6212826123992956"
/// @endcode
FAKER_EXPORT std::string card_number(
    CardTypes card_types =
        CardTypes::AmericanExpress | CardTypes::JCB | CardTypes::MasterCard | CardTypes::UnionPay | CardTypes::Visa
);

/// @brief Generates a random issue or valid through date of a card.
/// @param start The start month in the format of "mm/YY". Defaults to "01/00".
/// @param end The end month in the format of "mm/YY". Defaults to "12/50".
/// @return A card date in the format of "mm/YY".
/// @code
/// faker::payment::card_date();  // "07/25"
/// faker::payment::card_date("03/11", "04/12");  // "03/12"
/// @endcode
FAKER_EXPORT std::string card_date(std::string_view start = "01/00", std::string_view end = "12/50");

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
    /// @brief Construct a card entity.
    /// @param languages The language of card type. Defaults to Languages::English.
    ///                  If multiple languages are specified, bitwise(bitwise_or |) operator can be used.
    /// @param card_types The selected card types.
    ///                   Defaults to CardTypes::AmericanExpress, CardTypes::JCB,
    ///                   CardTypes::MasterCard, CardTypes::UnionPay and CardTypes::Visa.
    ///                   If multiple card types are specified, bitwise(bitwise_or |) operator can be used.
    /// @param start The start month in the format of "mm/YY". Defaults to "01/00".
    /// @param end The end month in the format of "mm/YY". Defaults to "12/50".
    explicit Card(
        Languages languages = Languages::English,
        CardTypes card_types =
            CardTypes::AmericanExpress | CardTypes::JCB | CardTypes::MasterCard | CardTypes::UnionPay | CardTypes::Visa,
        std::string_view start = "01/00",
        std::string_view end   = "12/50"
    );

    /// @brief Destroys the card entity.
    ~Card();

    /// @brief Regenerates card data.
    void reroll();

    /// @brief Get the type of the card.
    [[nodiscard]] std::string type() const;

    /// @brief Get the number of the card.
    [[nodiscard]] std::string number() const;

    /// @brief Get the issue or valid through date of the card.
    [[nodiscard]] std::string date() const;

private:
    // Location
    std::source_location location = std::source_location::current();

    // Constructor parameters
    Languages   languages_;
    CardTypes   card_types_;
    std::string start_;
    std::string end_;

    // Selection
    Languages language_  = Languages::English;
    CardTypes card_type_ = CardTypes::AmericanExpress;

    // Generated data
    std::string type_;
    std::string number_;
    std::string date_;

    // Generates card data
    void roll();
};

}  // namespace faker::payment

#endif  // FAKER_PAYMENT_H
