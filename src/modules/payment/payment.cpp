// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file payment.cpp

#include "faker/payment.h"

#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "faker/types/enums.h"
#include "payment_data.h"
#include "random_engine.h"
#include "random_helper.h"
#include "string_helper.h"
#include "validation.h"

namespace faker::payment {

static std::string g_card_date_format = "%m/%y";

static std::tm now() {
    const std::time_t now = std::time(nullptr);
    return *std::localtime(&now);
}

static std::tm
    parse_time(const std::string& dt, const std::source_location& location = std::source_location::current()) {
    std::tm tm{};
    tm          = now();
    tm.tm_isdst = -1;

    const std::string_view format = g_card_date_format;

    std::istringstream iss{dt};
    iss.imbue(std::locale::classic());
    iss >> std::get_time(&tm, std::string(format).c_str());
    if (iss.fail()) {
        throw_exception<std::invalid_argument>(
            "Invalid format: '" + dt + "' (expected " + std::string(format) + ").",
            location
        );
    }
    iss >> std::ws;
    if (!iss.eof()) { throw_exception<std::invalid_argument>("Trailing characters in `" + dt + "`.", location); }

    CHECK_TIME_EX(std::invalid_argument, tm, location);

    return tm;
}

static std::string format_time(const std::tm& tm) {
    std::ostringstream     stream;
    const std::string_view format = g_card_date_format;
    stream << std::put_time(&tm, std::string(format).c_str());
    return stream.str();
}

static std::string get_card_date(
    const std::string_view      start_date,
    const std::string_view      end_date,
    const std::source_location& location = std::source_location::current()
) {
    auto start_tm = parse_time(std::string(start_date));
    auto end_tm   = parse_time(std::string(end_date));

    const auto start = std::mktime(&start_tm);
    const auto end   = std::mktime(&end_tm);

    CHECK_RANGE_EX(std::invalid_argument, start, end, location);

    std::mt19937_64&              random_engine = get_random_engine();
    std::uniform_int_distribution distribution(start, end);
    const auto                    random_time = distribution(random_engine);
    const std::tm                 random_tm   = *std::localtime(&random_time);

    return format_time(random_tm);
}

std::string payment_method(const std::string_view payment_methods, const char delimiter) {
    CHECK_EMPTY(std::invalid_argument, payment_methods);
    auto payment_method_vector = split_and_trim(payment_methods, delimiter);
    return pick_one<std::string>(payment_method_vector);
}

std::string card_type(const Languages languages, const CardTypes card_types) {
    const auto selected_language  = pick_language(languages);
    const auto selected_card_type = pick_card_type(card_types);
    return std::string(kCardTypes.at(selected_language).at(selected_card_type));
}

std::string card_number(const CardTypes card_types) {
    const auto selected_card_type = pick_card_type(card_types);

    std::string_view pattern;
    switch (selected_card_type) {
    case CardTypes::AmericanExpress: pattern = pick_one(kAmericanExpressCardNumberFormat); break;
    case CardTypes::JCB            : pattern = pick_one(kJCBCardNumberFormat); break;
    case CardTypes::MasterCard     : pattern = pick_one(kMasterCardNumberFormat); break;
    case CardTypes::UnionPay       : pattern = pick_one(kUnionPayCardNumberFormat); break;
    case CardTypes::Visa           : pattern = pick_one(kVisaCardNumberFormat); break;
    }

    return replace_wildcard_to_digit(pattern);
}

std::string card_date(const std::string_view start, const std::string_view end) {
    CHECK_EMPTY(std::invalid_argument, start);
    CHECK_EMPTY(std::invalid_argument, end);
    return get_card_date(start, end);
}

Card::Card(
    const Languages        languages,
    const CardTypes        card_types,
    const std::string_view start,
    const std::string_view end
) :
    languages_(languages), card_types_(card_types), start_(start), end_(end) {
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

void Card::roll() {
    language_  = pick_language(languages_);
    card_type_ = pick_card_type(card_types_);
    type_      = std::string(kCardTypes.at(language_).at(card_type_));
    number_    = card_number(card_types_);
    date_      = get_card_date(start_, end_, location);
}

}  // namespace faker::payment
