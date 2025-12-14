// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file payment_data.h

#ifndef FAKER_PAYMENT_DATA_H
#define FAKER_PAYMENT_DATA_H

#include <array>
#include <string_view>
#include <unordered_map>

#include "faker/types/enums.h"

namespace faker::payment {

const std::unordered_map<Languages, std::unordered_map<CardTypes, std::string_view>> kCardTypes = {
    {Languages::English,
     {
         {CardTypes::AmericanExpress, "American Express"},
         {CardTypes::JCB, "JCB"},
         {CardTypes::MasterCard, "MasterCard"},
         {CardTypes::UnionPay, "UnionPay"},
         {CardTypes::Visa, "Visa"},
     }},
    {Languages::SimplifiedChinese,
     {
         {CardTypes::AmericanExpress, "美国运通"},
         {CardTypes::JCB, "JCB"},
         {CardTypes::MasterCard, "万事达卡"},
         {CardTypes::UnionPay, "银联"},
         {CardTypes::Visa, "Visa"},
     }},
    {Languages::TraditionalChinese,
     {
         {CardTypes::AmericanExpress, "美國運通"},
         {CardTypes::JCB, "JCB"},
         {CardTypes::MasterCard, "萬事達卡"},
         {CardTypes::UnionPay, "銀聯"},
         {CardTypes::Visa, "Visa"},
     }},
    {Languages::Japanese,
     {
         {CardTypes::AmericanExpress, "AMEXカード"},
         {CardTypes::JCB, "JCB"},
         {CardTypes::MasterCard, "マスターカード"},
         {CardTypes::UnionPay, "銀聯"},
         {CardTypes::Visa, "Visa"},
     }},
};

constexpr auto kAmericanExpressCardNumberFormat =
    std::to_array<std::string_view>({"34#############", "37#############"});

constexpr auto kJCBCardNumberFormat = std::to_array<std::string_view>(
    {"3528############",
     "3529############",
     "353#############",
     "354#############",
     "355#############",
     "356#############",
     "357#############",
     "358#############"}
);

constexpr auto kMasterCardNumberFormat = std::to_array<std::string_view>(
    {"51##############", "52##############", "53##############", "54##############", "55##############"}
);

constexpr auto kUnionPayCardNumberFormat = std::to_array<std::string_view>(
    {"622202#############",
     "622230#############",
     "621661#############",
     "621700#############",
     "622280#############",
     "622848#############",
     "621282#############",
     "621661#############",
     "621660#############",
     "621663#############",
     "621483##########",
     "622246##########",
     "625956##########",
     "625955##########",
     "622848##########",
     "621282##########",
     "621660##########",
     "621661##########",
     "622576##########"}
);

constexpr auto kVisaCardNumberFormat = std::to_array<std::string_view>({"4###############"});

}  // namespace faker::payment

#endif  // FAKER_PAYMENT_DATA_H
