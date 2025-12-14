// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file string_helper.h

#ifndef FAKER_STRING_HELPER_H
#define FAKER_STRING_HELPER_H

#include <string>
#include <string_view>
#include <vector>

namespace faker {

/// @brief Capitalize a word.
/// @param word The word to capitalize.
/// @return The capitalized word.
std::string capitalize(std::string_view word);

/// @brief Remove all characters from `source_string` that are present in `chars_to_remove`.
/// @param source_string The source string to strip.
/// @param chars_to_remove Characters to be removed from `source_string`.
/// @return A new string with specified characters removed.
std::string remove_characters(std::string_view source_string, std::string_view chars_to_remove);

/// @brief Remove extra spaces from `source_string`.
/// @param source_string The source string to strip.
/// @return A new string with extra spaces removed.
std::string remove_extra_spaces(std::string_view source_string);

/// @brief Replace the first "{}" placeholder in the template string with the given text.
/// @param pattern The pattern to replace.
/// @param replacement The replacement string.
/// @return A new string with the placeholder replaced.
std::string replace_placeholder(std::string_view pattern, std::string_view replacement);

/// @brief Remove the space characters (space, tab, cr, lf) at both ends of the string.
/// @param s The string to trim.
/// @return A new string with space characters removed.
std::string& trim(std::string& s);

/// @brief Split `source_string` with `delimiter`.
/// @param source_string The source string to split.
/// @param delimiter The delimiter to split `source_string` with.
/// @return A vector of string.
std::vector<std::string> split(std::string_view source_string, char delimiter);

/// @brief Splitting `source_string` with `delimiter`
///        and remove the space characters (space, tab, cr, lf) at both ends of the string.
/// @param source_string The source string to split.
/// @param delimiter The delimiter to split `source_string` with.
/// @return A vector of string.
std::vector<std::string> split_and_trim(std::string_view source_string, char delimiter);

/// @brief Replace each wildcard in the pattern with a random character.
/// @param pattern The template string.
/// @param chars Chars list.
/// @param wildcard Wildcard character.
/// @return A string where each wildcard is replaced with a random character.
std::string replace_wildcard_to_character(std::string_view pattern, std::string_view chars, char wildcard);

/// @brief Replace each wildcard in two patterns using the same random characters.
/// @param pattern1 The first string with wildcards.
/// @param pattern2 The second string with wildcards.
/// @param chars Chars list.
/// @param wildcard Wildcard character.
/// @return A pair of strings with wildcards replaced using the same random characters.
std::pair<std::string, std::string> replace_wildcards_with_same_characters(
    std::string_view pattern1,
    std::string_view pattern2,
    std::string_view chars,
    char             wildcard
);

/// @brief Replace each wildcard in the pattern with a random digit.
/// @param pattern The template string.
/// @param digits Digits list, e.g. "123456789"
/// @param wildcard Wildcard character, e.g. '#'
/// @return A string where each wildcard is replaced with a random digit.
std::string
    replace_wildcard_to_digit(std::string_view pattern, std::string_view digits = "0123456789", char wildcard = '#');

/// @brief Replace each wildcard in two patterns using the same random characters.
/// @param pattern1 The first string with wildcards.
/// @param pattern2 The second string with wildcards.
/// @param digits Digits list, e.g. "123456789"
/// @param wildcard Wildcard character, e.g. '#'
/// @return A pair of strings with wildcards replaced using the same random characters.
std::pair<std::string, std::string> replace_wildcards_with_same_digits(
    std::string_view pattern1,
    std::string_view pattern2,
    std::string_view digits = "0123456789",
    char wildcard           = '#'
);

/// @brief Replace each wildcard in the pattern with a random letter.
/// @param pattern The template string.
/// @param letters Letters list, e.g. "abcde"
/// @param wildcard Wildcard character, e.g. '@'
/// @return A string where each wildcard is replaced with a random letter.
std::string replace_wildcard_to_letter(
    std::string_view pattern,
    std::string_view letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    char wildcard            = '@'
);

/// @brief Replace each wildcard in two patterns using the same random characters.
/// @param pattern1 The first string with wildcards.
/// @param pattern2 The second string with wildcards.
/// @param letters Letters list, e.g. "abcde"
/// @param wildcard Wildcard character, e.g. '@'
/// @return A pair of strings with wildcards replaced using the same random characters.
std::pair<std::string, std::string> replace_wildcards_with_same_letters(
    std::string_view pattern1,
    std::string_view pattern2,
    std::string_view letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
    char wildcard            = '@'
);

}  // namespace faker

#endif  // FAKER_STRING_HELPER_H
