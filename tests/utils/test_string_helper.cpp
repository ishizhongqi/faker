// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file test_string_helper.cpp

#include <gtest/gtest.h>

#include <regex>
#include <string>
#include <string_view>

#include "string_helper.h"

using namespace ::faker;

TEST(CapitalizeTest, MixedCase) {
    ASSERT_EQ("Hello", capitalize("hELLo"));
}

TEST(CapitalizeTest, EmptyString) {
    ASSERT_EQ("", capitalize(""));
}

TEST(RemoveCharactersTest, CharactersNeedToRemove) {
    ASSERT_EQ("HelloWorld", remove_characters("Hello World!", " !"));
}

TEST(RemoveCharactersTest, NoCharactersNeedToRemove) {
    ASSERT_EQ("Hello World!", remove_characters("Hello World!", ",@"));
}

TEST(ReplacePlaceholderTest, OneReplacement) {
    ASSERT_EQ("Hello, World!", replace_placeholder("Hello, {}!", "World"));
}

TEST(ReplacePlaceholderTest, NoPlaceholders) {
    ASSERT_EQ("Hello, World!", replace_placeholder("Hello, World!", "World"));
}

TEST(ReplaceWildcardWithSequenceTest, ShouldReplaceAllWildcards) {
    ASSERT_EQ("AB12CD34", replace_wildcard_with_sequence("AB##CD##", '#', "1234"));
}

TEST(ReplaceWildcardWithSequenceTest, ShouldThrowWhenReplacementSizeMismatch) {
    ASSERT_THROW(
        [[maybe_unused]] const auto value = replace_wildcard_with_sequence("A##", '#', "1"),
        std::invalid_argument
    );
}

TEST(ReplaceWildcardToCharacterTest, MoreThanOneWildcard) {
    const std::string replacement = replace_wildcard_with_character("Hello??", "ABC", '?');
    ASSERT_TRUE(
        replacement ==
        "HelloAA" ||
        replacement ==
        "HelloBA" ||
        replacement ==
        "HelloCA" ||
        replacement ==
        "HelloAB" ||
        replacement ==
        "HelloBB" ||
        replacement ==
        "HelloCB" ||
        replacement ==
        "HelloAC" ||
        replacement ==
        "HelloBC" ||
        replacement == "HelloCC"
    );
}

TEST(ReplaceWildcardToCharacterTest, OneWildcard) {
    const std::string replacement = replace_wildcard_with_character("Hello?", "ABC", '?');
    ASSERT_TRUE(replacement == "HelloA" || replacement == "HelloB" || replacement == "HelloC");
}

TEST(ReplaceWildcardToCharacterTest, NoWildcard) {
    const std::string replacement = replace_wildcard_with_character("Hello", "ABC", '?');
    ASSERT_EQ("Hello", replacement);
}

TEST(ReplaceWildcardToCharacterTest, ShouldThrowWhenCharsEmptyAndWildcardExists) {
    ASSERT_THROW(
        [[maybe_unused]] const auto value = replace_wildcard_with_character("Hello?", "", '?'),
        std::invalid_argument
    );
}

TEST(ReplaceWildcardsWithSameCharactersTest, MoreThanOneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_characters("Hello??", "World??", "ABC", '?');
    ASSERT_TRUE(
        (fst == "HelloAA" && snd == "WorldAA") ||
        (fst == "HelloBA" && snd == "WorldBA") ||
        (fst == "HelloCA" && snd == "WorldCA") ||
        (fst == "HelloAB" && snd == "WorldAB") ||
        (fst == "HelloBB" && snd == "WorldBB") ||
        (fst == "HelloCB" && snd == "WorldCB") ||
        (fst == "HelloAC" && snd == "WorldAC") ||
        (fst == "HelloBC" && snd == "WorldBC") ||
        (fst == "HelloCC" && snd == "WorldCC")
    );
}

TEST(ReplaceWildcardsWithSameCharactersTest, OneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_characters("Hello?", "World?", "ABC", '?');
    ASSERT_TRUE(
        (fst == "HelloA" && snd == "WorldA") ||
        (fst == "HelloB" && snd == "WorldB") ||
        (fst == "HelloC" && snd == "WorldC")
    );
}

TEST(ReplaceWildcardsWithSameCharactersTest, NoWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_characters("Hello", "World", "ABC", '?');
    ASSERT_EQ("Hello", fst);
    ASSERT_EQ("World", snd);
}

TEST(ReplaceWildcardToDigitTest, MoreThanOneWildcard) {
    const std::string replacement = replace_wildcard_with_digit("Hello##");
    const std::regex  re("Hello\\d\\d");
    ASSERT_TRUE(std::regex_match(replacement, re));
}

TEST(ReplaceWildcardToDigitTest, OneWildcard) {
    const std::string replacement = replace_wildcard_with_digit("Hello#");
    const std::regex  re("Hello\\d");
    ASSERT_TRUE(std::regex_match(replacement, re));
}

TEST(ReplaceWildcardToDigitTest, NoWildcard) {
    const std::string replacement = replace_wildcard_with_digit("Hello");
    ASSERT_EQ("Hello", replacement);
}

TEST(ReplaceWildcardsWithSameDigitsTest, MoreThanOneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_digits("Hello##", "World##");
    const std::regex re("Hello\\d\\d");
    ASSERT_TRUE(std::regex_match(fst, re));
    ASSERT_EQ(fst.substr(5, 2), snd.substr(5, 2));
}

TEST(ReplaceWildcardsWithSameDigitsTest, OneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_digits("Hello#", "World#");
    const std::regex re("Hello\\d");
    ASSERT_TRUE(std::regex_match(fst, re));
    ASSERT_EQ(fst.substr(5, 1), snd.substr(5, 1));
}

TEST(ReplaceWildcardsWithSameDigitsTest, NoWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_digits("Hello", "World");
    ASSERT_EQ("Hello", fst);
    ASSERT_EQ("World", snd);
}

TEST(ReplaceWildcardToLetterTest, MoreThanOneWildcard) {
    const std::string replacement = replace_wildcard_with_letter("Hello@@");
    const std::regex  re("Hello[a-zA-Z]{2}");
    ASSERT_TRUE(std::regex_match(replacement, re));
}

TEST(ReplaceWildcardToLetterTest, OneWildcard) {
    const std::string replacement = replace_wildcard_with_letter("Hello@");
    const std::regex  re("Hello[a-zA-Z]");
    ASSERT_TRUE(std::regex_match(replacement, re));
}

TEST(ReplaceWildcardToLetterTest, NoWildcard) {
    const std::string replacement = replace_wildcard_with_letter("Hello");
    ASSERT_EQ("Hello", replacement);
}

TEST(ReplaceWildcardsWithSameLettersTest, MoreThanOneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_letters("Hello@@", "World@@");
    const std::regex re("Hello[a-zA-Z]{2}");
    ASSERT_TRUE(std::regex_match(fst, re));
    ASSERT_EQ(fst.substr(5, 2), snd.substr(5, 2));
}

TEST(ReplaceWildcardsWithSameLettersTest, OneWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_letters("Hello@", "World@");
    const std::regex re("Hello[a-zA-Z]");
    ASSERT_TRUE(std::regex_match(fst, re));
    ASSERT_EQ(fst.substr(5, 1), snd.substr(5, 1));
}

TEST(ReplaceWildcardsWithSameLettersTest, NoWildcard) {
    const auto [fst, snd] = replace_wildcards_with_same_letters("Hello", "World");
    ASSERT_EQ("Hello", fst);
    ASSERT_EQ("World", snd);
}
