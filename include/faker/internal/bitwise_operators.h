// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file bitwise_operators.h

#ifndef FAKER_BITWISE_OPERATORS_H
#define FAKER_BITWISE_OPERATORS_H

#include <type_traits>

namespace faker {

/// @brief Trait to enable bitwise operators.
///        By default, all enums are disabled.
template <typename E>
struct enable_bitwise_operators : std::false_type {};

/// @brief Helper variable template for easier use.
template <typename E>
constexpr bool enable_bitwise_operators_v = enable_bitwise_operators<E>::value;

/// @brief operator| overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E> operator|(E lhs, E rhs) {
    using T = std::underlying_type_t<E>;
    return static_cast<E>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

/// @brief operator& overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E> operator&(E lhs, E rhs) {
    using T = std::underlying_type_t<E>;
    return static_cast<E>(static_cast<T>(lhs) & static_cast<T>(rhs));
}

/// @brief operator^ overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E> operator^(E lhs, E rhs) {
    using T = std::underlying_type_t<E>;
    return static_cast<E>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
}

/// @brief operator~ overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E> operator~(E e) {
    using T = std::underlying_type_t<E>;
    return static_cast<E>(~static_cast<T>(e));
}

/// @brief operator|= overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E&> operator|=(E& lhs, E rhs) {
    lhs = lhs | rhs;
    return lhs;
}

/// @brief operator&= overload.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, E&> operator&=(E& lhs, E rhs) {
    lhs = lhs & rhs;
    return lhs;
}

/// @brief Check whether a specific flag is set in a bitwise.
template <typename E>
constexpr std::enable_if_t<enable_bitwise_operators_v<E>, bool> has_flag(E value, E flag) {
    using T = std::underlying_type_t<E>;
    return (static_cast<T>(value) & static_cast<T>(flag)) != 0;
}

}  // namespace faker

#endif  // FAKER_BITWISE_OPERATORS_H
