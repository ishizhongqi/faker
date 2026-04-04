// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

#include <gtest/gtest.h>

#include <array>
#include <thread>

#include "random_engine.h"

namespace faker {

class RandomEngineTest : public ::testing::Test {
protected:
    void SetUp() override { use_non_deterministic_seed(); }

    void TearDown() override { use_non_deterministic_seed(); }
};

TEST_F(RandomEngineTest, ReturnsSameEngineReferenceInSameThread) {
    auto* const engine1 = &get_random_engine();
    auto* const engine2 = &get_random_engine();

    ASSERT_EQ(engine1, engine2);
}

TEST_F(RandomEngineTest, DeterministicSeedReproducesSequence) {
    seed_random_engine(123456789ULL);
    auto& engine1 = get_random_engine();

    const auto v1 = std::array{
        engine1(),
        engine1(),
        engine1(),
        engine1(),
        engine1(),
    };

    seed_random_engine(123456789ULL);
    auto& engine2 = get_random_engine();

    const auto v2 = std::array{
        engine2(),
        engine2(),
        engine2(),
        engine2(),
        engine2(),
    };

    ASSERT_EQ(v1, v2);
}

TEST_F(RandomEngineTest, DifferentDeterministicSeedChangesSequence) {
    seed_random_engine(100ULL);
    auto& engine1 = get_random_engine();
    const auto first = engine1();

    seed_random_engine(101ULL);
    auto& engine2 = get_random_engine();
    const auto second = engine2();

    ASSERT_NE(first, second);
}

TEST_F(RandomEngineTest, DeterministicSeedGivesDistinctThreadStreams) {
    seed_random_engine(42ULL);

    std::array<std::uint64_t, 2> first_values{};

    std::thread t1([&first_values]() {
        auto& engine = get_random_engine();
        first_values[0] = engine();
    });
    std::thread t2([&first_values]() {
        auto& engine = get_random_engine();
        first_values[1] = engine();
    });

    t1.join();
    t2.join();

    ASSERT_NE(first_values[0], first_values[1]);
}

}  // namespace faker
