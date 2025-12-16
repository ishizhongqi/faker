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

#endif  // FAKER_TESTS_HELPER_H
