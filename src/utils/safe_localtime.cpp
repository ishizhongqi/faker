// Copyright (c) 2026 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file safe_localtime.cpp

#include "safe_localtime.h"

#include <ctime>
#include <mutex>

namespace faker {

// Cross-platform thread-safe localtime wrapper.
// - MSVC: localtime_s
// - POSIX: localtime_r
// - Fallback: guard std::localtime with a mutex and copy
std::tm get_safe_localtime(std::time_t t) noexcept {
    std::tm tm{};
#if defined(_WIN32)
    // localtime_s returns non-zero on error
    (void)localtime_s(&tm, &t);
#elif defined(_POSIX_VERSION)
    // localtime_r returns nullptr on error
    if (localtime_r(&t, &tm) == nullptr) {
        // leave tm zero-initialized on failure
    }
#else
    std::mutex                  s_localtime_mutex;
    std::lock_guard<std::mutex> lk(s_localtime_mutex);
    if (std::tm* p = std::localtime(&t)) { tm = *p; }
#endif
    return tm;
}

}  // namespace faker
