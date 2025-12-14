// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file macros.h

#ifndef FAKER_MACROS_H
#define FAKER_MACROS_H

#if defined(_WIN32) || defined(_WIN64)
#define FAKER_PLATFORM_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
#define FAKER_PLATFORM_MACOS 1
#elif defined(__linux__)
#define FAKER_PLATFORM_LINUX 1
#else
#error "Unsupported platform"
#endif

#if defined(_MSC_VER)
#define FAKER_COMPILER_MSVC 1
#elif defined(__clang__)
#define FAKER_COMPILER_CLANG 1
#elif defined(__GNUC__)
#define FAKER_COMPILER_GCC 1
#else
#error "Unsupported compiler"
#endif

#if defined(FAKER_PLATFORM_WINDOWS)
#if defined(FAKER_BUILD_SHARED)
#define FAKER_EXPORT __declspec(dllexport)
#elif defined(FAKER_USE_SHARED)
#define FAKER_EXPORT __declspec(dllimport)
#else
#define FAKER_EXPORT
#endif
#else
#if __GNUC__ >= 4
#define FAKER_EXPORT __attribute__((visibility("default")))
#else
#define FAKER_EXPORT
#endif
#endif

#endif  // FAKER_MACROS_H
