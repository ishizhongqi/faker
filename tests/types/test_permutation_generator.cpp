// Copyright (c) 2026 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <mutex>
#include <regex>
#include <thread>
#include <unordered_set>
#include <vector>

#include "permutation_generator.h"
#include "random_engine.h"

namespace faker {

TEST(PermutationGeneratorTest, ThrowsWhenNotInitialized) {
    PermutationGenerator pg;
    ASSERT_THROW([[maybe_unused]] const auto value = pg.next_uint64(), std::runtime_error);
}

TEST(PermutationGeneratorTest, SingleValueRangeIsReturnedThenExhausted) {
    PermutationGenerator pg(42, 42);
    ASSERT_EQ(pg.next_uint64(), 42U);
    ASSERT_THROW([[maybe_unused]] const auto value = pg.next_uint64(), std::overflow_error);
}

TEST(PermutationGeneratorTest, CoversRangeUniquelyWithoutOutOfRangeValues) {
    seed_random_engine(20260211ULL);
    constexpr uint64_t kStart = 10;
    constexpr uint64_t kEnd   = 19;
    PermutationGenerator pg(kStart, kEnd);

    std::unordered_set<uint64_t> values;
    values.reserve(static_cast<std::size_t>(kEnd - kStart + 1));

    for (uint64_t i = kStart; i <= kEnd; ++i) {
        const auto value = pg.next_uint64();
        ASSERT_GE(value, kStart);
        ASSERT_LE(value, kEnd);
        values.insert(value);
    }

    ASSERT_EQ(values.size(), static_cast<std::size_t>(kEnd - kStart + 1));
    ASSERT_THROW([[maybe_unused]] const auto value = pg.next_uint64(), std::overflow_error);
}

TEST(PermutationGeneratorTest, Base36OutputIsAlnumAndUnique) {
    seed_random_engine(99ULL);
    PermutationGenerator pg(0, 35, PermutationGenerator::BaseN::Base36);

    std::unordered_set<std::string> values;
    values.reserve(36);
    const std::regex pattern("^[0-9a-z]+$");

    for (int i = 0; i < 36; ++i) {
        const auto value = pg.next();
        ASSERT_TRUE(std::regex_match(value, pattern));
        values.insert(value);
    }

    ASSERT_EQ(values.size(), 36U);
}

TEST(PermutationGeneratorTest, DecimalOutputUsesNumericStringPath) {
    seed_random_engine(20260211ULL);
    PermutationGenerator pg(100, 105, PermutationGenerator::BaseN::Decimal);

    const std::string first = pg.next();
    ASSERT_TRUE(std::regex_match(first, std::regex(R"(^\d+$)")));
}

TEST(PermutationGeneratorTest, ThrowsForUnsupportedFullUint64Range) {
    PermutationGenerator pg;
    ASSERT_THROW(
        pg.initialize(0, std::numeric_limits<uint64_t>::max(), PermutationGenerator::BaseN::Decimal),
        std::invalid_argument
    );
}

TEST(PermutationGeneratorTest, HandlesMultiplierModuloZeroInitializationPath) {
    // range_size = 48271 -> candidate = kMultiplier % modulus = 0
    PermutationGenerator pg(0, 48270, PermutationGenerator::BaseN::Decimal);
    const uint64_t value = pg.next_uint64();
    ASSERT_LE(value, 48270U);
}

TEST(PermutationGeneratorTest, DeterministicSequenceWhenSeeded) {
    seed_random_engine(123456ULL);
    PermutationGenerator first(1000, 1100);

    std::array<uint64_t, 16> seq1{};
    for (auto& value : seq1) { value = first.next_uint64(); }

    seed_random_engine(123456ULL);
    PermutationGenerator second(1000, 1100);

    std::array<uint64_t, 16> seq2{};
    for (auto& value : seq2) { value = second.next_uint64(); }

    ASSERT_EQ(seq1, seq2);
}

TEST(PermutationGeneratorTest, ConcurrentNextReturnsUniqueValues) {
    seed_random_engine(7ULL);
    constexpr uint64_t kStart = 100;
    constexpr uint64_t kEnd   = 1099;
    PermutationGenerator pg(kStart, kEnd);

    std::vector<uint64_t> values;
    values.reserve(1000);
    std::mutex values_mutex;

    auto worker = [&pg, &values, &values_mutex]() {
        for (int i = 0; i < 250; ++i) {
            const uint64_t value = pg.next_uint64();
            std::lock_guard<std::mutex> lock(values_mutex);
            values.push_back(value);
        }
    };

    std::thread t1(worker);
    std::thread t2(worker);
    std::thread t3(worker);
    std::thread t4(worker);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ASSERT_EQ(values.size(), 1000U);
    std::unordered_set<uint64_t> unique_values(values.begin(), values.end());
    ASSERT_EQ(unique_values.size(), values.size());

    for (const uint64_t value : values) {
        ASSERT_GE(value, kStart);
        ASSERT_LE(value, kEnd);
    }
}

}  // namespace faker
