// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_engine.h

#ifndef FAKER_RANDOM_ENGINE_H
#define FAKER_RANDOM_ENGINE_H

#include <cstdint>
#include <random>

#include "faker/internal/export.h"

namespace faker {

/// @brief Provides a shared random engine instance for faker modules.
/// @return Reference to a global std::mt19937_64 engine.
FAKER_EXPORT std::mt19937_64& get_random_engine();

/// @brief Reseed random engine(s) with deterministic behavior.
/// @param seed Base seed.
/// @note This affects the current and future threads that use faker RNG.
FAKER_EXPORT void seed_random_engine(std::uint64_t seed);

/// @brief Switch random engine seeding back to non-deterministic mode.
/// @note This affects the current and future threads that use faker RNG.
FAKER_EXPORT void use_non_deterministic_seed();

}  // namespace faker

#endif  // FAKER_RANDOM_ENGINE_H
