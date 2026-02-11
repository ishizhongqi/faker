// Copyright (c) 2026 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file permutation_generator.cpp

#include "permutation_generator.h"

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <limits>
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
    if (end == std::numeric_limits<uint64_t>::max() && start == 0) {
        throw_exception<std::invalid_argument>(
            "Range [0, UINT64_MAX] is not supported.",
            location
        );
    }

    start_  = start;
    end_    = end;
    base_n_ = base_n;
    range_size_ = end_ - start_ + 1;
    current_.store(0, std::memory_order_relaxed);
    initialized_ = true;

    modulus_    = range_size_;
    multiplier_ = pick_coprime_multiplier(modulus_);
    increment_  = std::uniform_int_distribution<uint64_t>(0, modulus_ - 1)(get_random_engine());
}

bool PermutationGenerator::is_initialized() const {
    return initialized_;
}

uint64_t PermutationGenerator::next_uint64(const std::source_location& location) {
    if (!initialized_) { throw_exception<std::runtime_error>("Illegal permutation detected.", location); }
    const uint64_t value = current_.fetch_add(1, std::memory_order_relaxed);
    if (value >= range_size_) { throw_exception<std::overflow_error>("No valid permutation available.", location); }

    const uint64_t scrambled_index = scramble(value);

    return scrambled_index;
}

std::string PermutationGenerator::next(const std::source_location& location) {
    const uint64_t value = next_uint64(location);

    if (base_n_ == BaseN::Base36) { return to_base36(value); }

    return std::to_string(value);
}

uint64_t PermutationGenerator::scramble(const uint64_t value) const {
    return start_ + ((mul_mod(value, multiplier_, modulus_) + increment_) % modulus_);
}

uint64_t PermutationGenerator::gcd(uint64_t lhs, uint64_t rhs) {
    while (rhs != 0) {
        const uint64_t t = lhs % rhs;
        lhs              = rhs;
        rhs              = t;
    }
    return lhs;
}

uint64_t PermutationGenerator::pick_coprime_multiplier(const uint64_t modulus) {
    if (modulus <= 1) { return 1; }

    uint64_t candidate = kMultiplier % modulus;
    if (candidate == 0) { candidate = 1; }

    while (gcd(candidate, modulus) != 1) {
        ++candidate;
        if (candidate >= modulus) { candidate = 1; }
    }

    return candidate;
}

uint64_t PermutationGenerator::add_mod(const uint64_t lhs, const uint64_t rhs, const uint64_t modulus) {
    if (lhs >= modulus - rhs) { return lhs - (modulus - rhs); }
    return lhs + rhs;
}

uint64_t PermutationGenerator::mul_mod(uint64_t lhs, uint64_t rhs, const uint64_t modulus) {
    if (modulus == 1) { return 0; }
#if defined(__SIZEOF_INT128__)
    const auto product = static_cast<unsigned __int128>(lhs) * static_cast<unsigned __int128>(rhs);
    return static_cast<uint64_t>(product % modulus);
#else
    lhs %= modulus;
    rhs %= modulus;
    uint64_t result = 0;
    while (rhs != 0) {
        if ((rhs & 1U) != 0U) { result = add_mod(result, lhs, modulus); }
        rhs >>= 1U;
        if (rhs != 0U) { lhs = add_mod(lhs, lhs, modulus); }
    }
    return result;
#endif
}

std::string PermutationGenerator::to_base36(uint64_t value) {
    if (value == 0) return "0";

    std::string result;
    result.reserve(13);

    while (value > 0) {
        result.push_back(kBase36Chars[value % 36]);
        value /= 36;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace faker
