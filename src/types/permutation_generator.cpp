// Copyright (c) 2026 Shizhongqi
// Licensed under the Apache License 2.0.
// See the LICENSE file in the project root for more information.

/// @file permutation_generator.cpp

#include "permutation_generator.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <source_location>
#include <stdexcept>

#include "random_engine.h"
#include "validation.h"

namespace faker {

static constexpr std::string_view kBase36Chars = "0123456789abcdefghijklmnopqrstuvwxyz";

PermutationGenerator::PermutationGenerator() = default;

PermutationGenerator::PermutationGenerator(
    const uint64_t              start,
    const uint64_t              end,
    const BaseN                 base_n,
    const std::source_location& location
) {
    initialize(start, end, base_n, location);
}

void PermutationGenerator::initialize(
    const uint64_t              start,
    const uint64_t              end,
    const BaseN                 base_n,
    const std::source_location& location
) {
    CHECK_RANGE_EX(std::invalid_argument, start, end, location);
    start_  = start;
    end_    = end;
    base_n_ = base_n;
    current_.store(start_, std::memory_order_relaxed);
    initialized_ = true;

    modulus_   = end_ + 1;
    increment_ = std::uniform_int_distribution(start_, end_)(get_random_engine());
}

bool PermutationGenerator::is_initialized() const {
    return initialized_;
}

uint64_t PermutationGenerator::next_uint64(const std::source_location& location) {
    if (!initialized_) { throw_exception<std::runtime_error>("Illegal permutation detected.", location); }
    const uint64_t value = current_.fetch_add(1, std::memory_order_relaxed);
    if (value >= end_) { throw_exception<std::overflow_error>("No valid permutation available.", location); }

    const uint64_t scrambled_index = scramble(value);

    return scrambled_index;
}

std::string PermutationGenerator::next(const std::source_location& location) {
    const uint64_t value = next_uint64(location);

    if (base_n_ == BaseN::Base36) { return to_base36(value); }

    return std::to_string(value);
}

uint64_t PermutationGenerator::scramble(const uint64_t value) const {
    return (value * kMultiplier + increment_) % modulus_;
}

std::string PermutationGenerator::to_base36(uint64_t value) {
    if (value == 0) return "0";

    std::string result;

    while (value > 0) {
        result.push_back(kBase36Chars[value % 36]);
        value /= 36;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace faker
