// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_helper.h

#ifndef FAKER_RANDOM_HELPER_H
#define FAKER_RANDOM_HELPER_H

#include <array>
#include <random>
#include <span>
#include <vector>

#include "faker/types/enums.h"
#include "random_engine.h"

namespace faker {

/// @brief Get a random element from an array.
/// @param data The array to get a random element from.
/// @return A random element.
template <typename T>
const T& pick_one(std::span<const T> data) {
    return data[std::uniform_int_distribution<std::size_t>(0, data.size() - 1)(get_random_engine())];
}

/// @brief Get a random element from an array.
/// @param data_array The array to get a random element from.
/// @return A random element.
template <typename T, size_t N>
const T& pick_one(const std::array<T, N>& data_array) {
    return pick_one(std::span<const T>(data_array));
}

/// @brief Get a random language from the given languages
/// @param languages Languages
/// @return A random language
Languages pick_language(Languages languages);

/// @brief Get a random region from the given regions
/// @param regions Regions
/// @return A random region
Regions pick_region(Regions regions);

/// @brief Get a random gender from the given genders
/// @param genders Genders
/// @return A random gender
Genders pick_gender(Genders genders);

/// @brief Get a random card type from the given card types
/// @param card_types CardTypes
/// @return A random card type
CardTypes pick_card_type(CardTypes card_types);

/// @brief Get a random barcode type from the given barcode types
/// @param barcode_types BarcodeTypes
/// @return A random barcode type
BarcodeTypes pick_barcode_type(BarcodeTypes barcode_types);

/// @brief Get a random operating system from the given operating systems
/// @param operating_systems OperatingSystems
/// @return A random operating system
OperatingSystems pick_operating_system(OperatingSystems operating_systems);

}  // namespace faker

#endif  // FAKER_RANDOM_HELPER_H
