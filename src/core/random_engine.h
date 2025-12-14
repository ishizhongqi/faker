// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file random_engine.h

#ifndef FAKER_RANDOM_ENGINE_H
#define FAKER_RANDOM_ENGINE_H

#include <random>

namespace faker {

/// @brief Provides a shared random engine instance for faker modules.
/// @return Reference to a global std::mt19937_64 engine.
std::mt19937_64& get_random_engine();

}  // namespace faker

#endif  // FAKER_RANDOM_ENGINE_H
