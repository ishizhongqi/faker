// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_engine.cpp

#include "random_engine.h"

#include <array>
#include <atomic>
#include <chrono>
#include <limits>
#include <random>

namespace faker {

namespace {

std::atomic<bool>     g_deterministic_mode{false};
std::atomic<uint64_t> g_seed_epoch{1};
std::atomic<uint64_t> g_base_seed{0};
std::atomic<uint64_t> g_thread_counter{0};

// SplitMix64 for stable seed diffusion and cheap deterministic stream partitioning.
uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

uint64_t make_non_deterministic_seed() {
    // NOLINTNEXTLINE(cert-msc51-cpp)  // random_device seeding is intentional
    std::random_device rd;
    const uint64_t     t = static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    const uint64_t     r1 = static_cast<uint64_t>(rd());
    const uint64_t     r2 = static_cast<uint64_t>(rd());
    const uint64_t     r3 = static_cast<uint64_t>(rd());

    std::seed_seq seq{
        static_cast<std::uint32_t>(r1),
        static_cast<std::uint32_t>(r1 >> 32),
        static_cast<std::uint32_t>(r2),
        static_cast<std::uint32_t>(r2 >> 32),
        static_cast<std::uint32_t>(r3),
        static_cast<std::uint32_t>(r3 >> 32),
        static_cast<std::uint32_t>(t),
        static_cast<std::uint32_t>(t >> 32),
    };
    std::array<std::uint32_t, 2> state{};
    seq.generate(state.begin(), state.end());
    return (static_cast<uint64_t>(state[0]) << 32) | static_cast<uint64_t>(state[1]);
}

thread_local std::mt19937_64 engine;
thread_local uint64_t        local_seed_epoch = std::numeric_limits<uint64_t>::max();

void reseed_if_needed() {
    const uint64_t epoch = g_seed_epoch.load(std::memory_order_acquire);
    if (local_seed_epoch == epoch) { return; }

    const bool deterministic = g_deterministic_mode.load(std::memory_order_acquire);
    if (deterministic) {
        const uint64_t base_seed    = g_base_seed.load(std::memory_order_relaxed);
        const uint64_t thread_index = g_thread_counter.fetch_add(1, std::memory_order_relaxed);
        engine.seed(splitmix64(base_seed + thread_index));
    } else {
        engine.seed(make_non_deterministic_seed());
    }
    local_seed_epoch = epoch;
}

}  // namespace

std::mt19937_64& get_random_engine() {
    reseed_if_needed();
    return engine;
}

void seed_random_engine(const std::uint64_t seed) {
    g_base_seed.store(seed, std::memory_order_release);
    g_deterministic_mode.store(true, std::memory_order_release);
    g_thread_counter.store(0, std::memory_order_release);
    g_seed_epoch.fetch_add(1, std::memory_order_acq_rel);
}

void use_non_deterministic_seed() {
    g_deterministic_mode.store(false, std::memory_order_release);
    g_thread_counter.store(0, std::memory_order_release);
    g_seed_epoch.fetch_add(1, std::memory_order_acq_rel);
}

}  // namespace faker
