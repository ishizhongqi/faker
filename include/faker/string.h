// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string.h

#ifndef FAKER_STRING_H
#define FAKER_STRING_H

#include <string>

#include "faker/internal/macros.h"

namespace faker::string {

/// @brief Selects one item from a string of enumerated values.
/// @param enums The list of string item.
///              If empty, return empty.
/// @param delimiter The delimiter of enums.
/// @return An item of enums.
/// @code
/// faker::string::enum_item("First, Second, Third", ',');  // "First"
/// @endcode
FAKER_EXPORT std::string enum_item(std::string_view enums, char delimiter);

/// @brief Generates a random text.
/// @param number_of_chars_start Minimum number of characters. Defaults to 100.
/// @param number_of_chars_end Maximum number of characters. Defaults to 10,000.
/// @return A random text.
/// @code
/// faker::string::text();  //  The text is too long to display.
/// faker::string::text(1000, 2000);  //  The text is too long to display.
/// @endcode
FAKER_EXPORT std::string text(unsigned int number_of_chars_start = 100, unsigned int number_of_chars_end = 10000);

/// @brief Generates a UUID string.
/// @param include_hyphens Whether the UUID should include hyphens (-). Defaults to true.
/// @return A UUID v4 string.
/// @code
/// faker::string::uuid();  // "d6c86f3d-3221-4b6a-b120-ec9b9fb66ac2"
/// faker::string::uuid(false);  // "c8c303b7229349489d96ab804e3d80dd"
/// @endcode
FAKER_EXPORT std::string uuid(bool include_hyphens = true);

}  // namespace faker::string

#endif  // FAKER_STRING_H
