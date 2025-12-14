// Copyright (c) 2025 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file bilingual.cpp

#include "faker/types/bilingual.h"

#include <string>
#include <string_view>

namespace faker {

Bilingual::Bilingual() = default;

Bilingual::Bilingual(const std::string_view original, const std::string_view translation) :
    original_(original), translation_(translation) {}

Bilingual::Bilingual(const BilingualView &bilingual_view) :
    original_(bilingual_view.original), translation_(bilingual_view.translation) {}

Bilingual::~Bilingual() = default;

Bilingual::operator std::string() const {
    return original_;
}

Bilingual::operator std::string_view() const {
    return original_;
}

void Bilingual::set_original(const std::string_view original) {
    original_ = original;
}

void Bilingual::set_translation(const std::string_view translation) {
    translation_ = translation;
}

std::string Bilingual::original() const {
    return original_;
}

std::string Bilingual::translation() const {
    return translation_;
}

void Bilingual::swap() {
    std::swap(original_, translation_);
}

bool Bilingual::empty() const {
    return original_.empty();
}

}  // namespace faker
