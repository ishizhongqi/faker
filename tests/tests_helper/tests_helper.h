// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file tests_helper.h

#ifndef FAKER_TESTS_HELPER_H
#define FAKER_TESTS_HELPER_H

#include <gtest/gtest.h>

#include "faker/types/bilingual.h"
#include "faker/types/enums.h"

using namespace ::faker;

inline std::string to_string(const Languages language) {
    std::unordered_map<Languages, std::string> map = {
        {Languages::English, "English"},
        {Languages::SimplifiedChinese, "SimplifiedChinese"},
        {Languages::TraditionalChinese, "TraditionalChinese"},
        {Languages::Japanese, "Japanese"},
    };
    return map[language];
}

inline std::string to_string(const OperatingSystems operatingSystem) {
    std::unordered_map<OperatingSystems, std::string> map = {
        {OperatingSystems::Windows, "Windows"},
        {OperatingSystems::macOS, "macOS"},
        {OperatingSystems::Linux, "Linux"},
    };
    return map[operatingSystem];
}

inline std::string to_string(const Regions region) {
    std::unordered_map<Regions, std::string> map = {
        {Regions::UnitedStates, "UnitedStates"},
        {Regions::UnitedKingdom, "UnitedKingdom"},
        {Regions::China, "China"},
        {Regions::Japan, "Japan"},
    };
    return map[region];
}

inline std::string to_string(const CardTypes cardTypes) {
    std::unordered_map<CardTypes, std::string> map = {
        {CardTypes::AmericanExpress, "AmericanExpress"},
        {CardTypes::JCB, "JCB"},
        {CardTypes::MasterCard, "MasterCard"},
        {CardTypes::UnionPay, "UnionPay"},
        {CardTypes::Visa, "Visa"},
    };
    return map[cardTypes];
}

inline std::string to_string(const BarcodeTypes barcodeTypes) {
    std::unordered_map<BarcodeTypes, std::string> map = {
        {BarcodeTypes::EAN8, "EAN8"},
        {BarcodeTypes::EAN13, "EAN13"},
        {BarcodeTypes::UPCA, "UPCA"},
        {BarcodeTypes::UPCE, "UPCE"},
        {BarcodeTypes::ISBN, "ISBN"},
    };
    return map[barcodeTypes];
}

inline std::string to_string(const Genders gender) {
    std::unordered_map<Genders, std::string> map = {
        {Genders::M, "M"},
        {Genders::F, "F"},
    };
    return map[gender];
}

#endif  // FAKER_TESTS_HELPER_H
