// Copyright (c) 2026 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file safe_localtime.h

#ifndef FAKER_SAFE_LOCALTIME_H
#define FAKER_SAFE_LOCALTIME_H

#include <mutex>

namespace faker {

std::tm get_safe_localtime(std::time_t t) noexcept;

}  // namespace faker

#endif  // FAKER_SAFE_LOCALTIME_H
