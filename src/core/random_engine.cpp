// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_engine.cpp

#include "random_engine.h"

#include <random>

namespace faker {

thread_local bool is_seeded = false;

// NOLINTNEXTLINE(cert-msc51-cpp)  // random_device seeding is intentional
thread_local std::mt19937_64 engine;

std::mt19937_64& get_random_engine() {
    if (!is_seeded) {
        engine.seed(std::random_device{}());
        is_seeded = true;
    }

    return engine;
}

}  // namespace faker
