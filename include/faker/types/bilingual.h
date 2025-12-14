// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file bilingual.h

#ifndef FAKER_BILINGUAL_H
#define FAKER_BILINGUAL_H

#include <string>
#include <string_view>

#include "faker/internal/macros.h"

namespace faker {

/// @brief View for storing bilingual content.
struct FAKER_EXPORT BilingualView {
    std::string_view original;
    std::string_view translation;
};

/// @brief Used for storing strings containing bilingual content.
///        If you need to use the object as a string, you must perform an explicit conversion.
class FAKER_EXPORT Bilingual {
public:
    /// @brief Bilingual constructor.
    Bilingual();

    /// @brief Bilingual constructor.
    ///        If you need to use the object as a string, you must perform an explicit conversion.
    /// @param original Original language.
    /// @param translation The translation of the original language.
    Bilingual(std::string_view original, std::string_view translation);

    /// @brief Bilingual constructor.
    /// @param bilingual_view Bilingual view.
    explicit Bilingual(const BilingualView &bilingual_view);

    /// @brief Bilingual destructor.
    ~Bilingual();

    /// @brief Overload. Get the original as string.
    explicit operator std::string() const;

    /// @brief Overload. Get original as string_view.
    explicit operator std::string_view() const;

    /// @brief Set the original.
    void set_original(std::string_view original);

    /// @brief Set the translation.
    void set_translation(std::string_view translation);

    /// @brief Get the original.
    /// @return The original.
    [[nodiscard]] std::string original() const;

    /// @brief Get the translation.
    /// @return The translation of the original language
    [[nodiscard]] std::string translation() const;

    /// @brief Swap the original and translation.
    void swap();

    /// @brief Check Bilingual if is empty.
    [[nodiscard]] bool empty() const;

private:
    std::string original_;
    std::string translation_;
};

}  // namespace faker

#endif  // FAKER_BILINGUAL_H
