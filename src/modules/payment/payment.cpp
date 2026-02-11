// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file payment.cpp

#include "faker/payment.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <format>
#include <mutex>
#include <optional>
#include <random>
#include <span>
#include <string>
#include <string_view>

#include "faker/types/enums.h"
#include "payment_data.h"
#include "permutation_generator.h"
#include "random_engine.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::payment {

namespace {

constexpr std::size_t card_number_format_count = kAmericanExpressCardNumberFormat.size() +
                                                 kJCBCardNumberFormat.size() +
                                                 kMasterCardNumberFormat.size() +
                                                 kUnionPayCardNumberFormat.size() +
                                                 kVisaCardNumberFormat.size();

std::array<PermutationGenerator, card_number_format_count> card_number_pg_vector;
std::array<uint64_t, card_number_format_count>             card_number_capacity{};
std::array<uint8_t, card_number_format_count>              card_number_wildcards{};
std::array<std::mutex, card_number_format_count>           card_number_mutexes{};

int parse_month_index(
    const std::string_view      value,
    const std::source_location& location = std::source_location::current()
) {
    if (value.size() != 5 || value[2] != '/' || !std::isdigit(static_cast<unsigned char>(value[0])) ||
        !std::isdigit(static_cast<unsigned char>(value[1])) || !std::isdigit(static_cast<unsigned char>(value[3])) ||
        !std::isdigit(static_cast<unsigned char>(value[4]))) {
        throw_exception<std::invalid_argument>(
            "Invalid format: '" + std::string(value) + "' (expected %m/%y).",
            location
        );
    }

    const int month = (value[0] - '0') * 10 + (value[1] - '0');
    const int year  = (value[3] - '0') * 10 + (value[4] - '0');
    if (month < 1 || month > 12) {
        throw_exception<std::invalid_argument>(
            "Invalid date: Month must be between 1 and 12. (Current: " + std::to_string(month) + ")",
            location
        );
    }
    return year * 12 + (month - 1);
}

std::string format_month_index(const int month_index) {
    const int month = month_index % 12 + 1;
    const int year  = month_index / 12;
    return std::format("{:02d}/{:02d}", month, year);
}

std::string get_card_date(
    const std::string_view      start_date,
    const std::string_view      end_date,
    const std::source_location& location = std::source_location::current()
) {
    const int start = parse_month_index(start_date, location);
    const int end   = parse_month_index(end_date, location);
    CHECK_RANGE_EX(std::invalid_argument, start, end, location);

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(start, end);
    const int                     random_month_index = distribution(random_engine);

    return format_month_index(random_month_index);
}

}  // namespace

std::string payment_method(std::optional<std::span<const std::string_view>> payment_methods) {
    if (payment_methods.has_value()) {
        check_empty<std::invalid_argument>(payment_methods.value(), "payment_methods");
        if (std::ranges::any_of(payment_methods.value(), [](const std::string_view v) { return v.empty(); })) {
            throw_exception<std::invalid_argument>(
                "Invalid string: 'payment_methods' must not contain empty items.",
                std::source_location::current()
            );
        }
        return std::string(pick_one(payment_methods.value()));
    }
    return std::string(pick_one(kPaymentMethodsDefault));
}

std::string card_type(const Languages languages, const CardTypes card_types) {
    const auto selected_language  = pick_language(languages);
    const auto selected_card_type = pick_card_type(card_types);
    return std::string(kCardTypes.at(selected_language).at(selected_card_type));
}

std::string card_number(const CardTypes card_types, const bool unique) {
    const auto selected_card_type = pick_card_type(card_types);

    std::size_t      index;
    std::size_t      seq_index = 0;
    std::string_view pattern;

    switch (selected_card_type) {
    case CardTypes::AmericanExpress:
        index     = pick_index(kAmericanExpressCardNumberFormat);
        seq_index = index;
        pattern   = kAmericanExpressCardNumberFormat[index];
        break;
    case CardTypes::JCB:
        index     = pick_index(kJCBCardNumberFormat);
        seq_index = index + kAmericanExpressCardNumberFormat.size();
        pattern   = kJCBCardNumberFormat[index];
        break;
    case CardTypes::MasterCard:
        index     = pick_index(kMasterCardNumberFormat);
        seq_index = index + kAmericanExpressCardNumberFormat.size() + kJCBCardNumberFormat.size();
        pattern   = kMasterCardNumberFormat[index];
        break;
    case CardTypes::UnionPay:
        index     = pick_index(kUnionPayCardNumberFormat);
        seq_index = index +
                    kAmericanExpressCardNumberFormat.size() +
                    kJCBCardNumberFormat.size() +
                    kMasterCardNumberFormat.size();
        pattern = kUnionPayCardNumberFormat[index];
        break;
    case CardTypes::Visa:
        index     = pick_index(kVisaCardNumberFormat);
        seq_index = index +
                    kAmericanExpressCardNumberFormat.size() +
                    kJCBCardNumberFormat.size() +
                    kMasterCardNumberFormat.size() +
                    kUnionPayCardNumberFormat.size();
        pattern = kVisaCardNumberFormat[index];
        break;
    }

    std::string card_number;

    if (unique) {
        std::lock_guard<std::mutex> guard(card_number_mutexes[seq_index]);
        if (card_number_capacity[seq_index] == 0) {
            const uint64_t wildcard_count = std::count(pattern.begin(), pattern.end(), '#');
            uint64_t       capacity       = 1;
            for (size_t i = 0; i < wildcard_count; ++i) { capacity *= 10; }
            card_number_capacity[seq_index]  = capacity;
            card_number_wildcards[seq_index] = static_cast<uint8_t>(wildcard_count);
        }
        const uint64_t capacity       = card_number_capacity[seq_index];
        const uint64_t wildcard_count = card_number_wildcards[seq_index];
        if (!card_number_pg_vector[seq_index].is_initialized()) {
            card_number_pg_vector[seq_index].initialize(0, capacity - 1);
        }
        const uint64_t    seq     = card_number_pg_vector[seq_index].next_uint64();
        const std::string seq_str = std::format("{:0{}}", seq, wildcard_count);
        card_number               = replace_wildcard_with_sequence(pattern, '#', seq_str);
    } else {
        card_number = replace_wildcard_with_digit(pattern);
    }

    return card_number;
}

std::string card_date(const std::string_view start_month, const std::string_view end_month) {
    CHECK_EMPTY(std::invalid_argument, start_month);
    CHECK_EMPTY(std::invalid_argument, end_month);
    return get_card_date(start_month, end_month);
}

Card::Card(
    const Languages        languages,
    const CardTypes        card_types,
    const std::string_view start_month,
    const std::string_view end_month,
    const bool             unique
) :
    languages_(languages),
    card_types_(card_types),
    start_month_(start_month),
    end_month_(end_month),
    unique_(unique) {
    roll();
}

void Card::reroll() {
    roll();
}

Card::~Card() = default;

std::string Card::type() const {
    return type_;
}

std::string Card::number() const {
    return number_;
}

std::string Card::date() const {
    return date_;
}

std::string Card::payment_method() const {
    return payment_method_;
}

void Card::roll() {
    language_       = pick_language(languages_);
    card_type_      = pick_card_type(card_types_);
    type_           = std::string(kCardTypes.at(language_).at(card_type_));
    number_         = card_number(card_types_, unique_);
    date_           = get_card_date(start_month_, end_month_, location);
    payment_method_ = "Credit Card";
}

}  // namespace faker::payment
