// Copyright (c) 2026 Shizhongqi
// Licensed under the MIT License.
// See the LICENSE file in the project root for more information.

/// @file permutation_generator.h

#ifndef FAKER_PERMUTATION_GENERATOR_H
#define FAKER_PERMUTATION_GENERATOR_H

#include <atomic>
#include <cstdint>
#include <source_location>
#include <string>

namespace faker {

class PermutationGenerator {
public:
    enum class BaseN {
        Decimal,
        Base36,
    };

    PermutationGenerator();

    explicit PermutationGenerator(
        uint64_t                    start,
        uint64_t                    end,
        BaseN                       base_n   = BaseN::Decimal,
        const std::source_location& location = std::source_location::current()
    );

    PermutationGenerator(const PermutationGenerator&)            = delete;
    PermutationGenerator& operator=(const PermutationGenerator&) = delete;

    void initialize(
        uint64_t                    start,
        uint64_t                    end,
        BaseN                       base_n   = BaseN::Decimal,
        const std::source_location& location = std::source_location::current()
    );

    [[nodiscard]] bool is_initialized() const;

    uint64_t next_uint64(const std::source_location& location = std::source_location::current());

    std::string next(const std::source_location& location = std::source_location::current());

private:
    uint64_t              start_{0};
    uint64_t              end_{0};
    uint64_t              range_size_{0};
    BaseN                 base_n_{BaseN::Decimal};
    std::atomic<uint64_t> current_{0};
    bool                  initialized_{false};

    uint64_t modulus_{0};
    uint64_t increment_{0};
    uint64_t multiplier_{1};

    static constexpr uint64_t kMultiplier = 48271;

    [[nodiscard]] uint64_t scramble(uint64_t value) const;
    [[nodiscard]] static uint64_t gcd(uint64_t lhs, uint64_t rhs);
    [[nodiscard]] static uint64_t pick_coprime_multiplier(uint64_t modulus);
    [[nodiscard]] static uint64_t add_mod(uint64_t lhs, uint64_t rhs, uint64_t modulus);
    [[nodiscard]] static uint64_t mul_mod(uint64_t lhs, uint64_t rhs, uint64_t modulus);
    static std::string     to_base36(uint64_t value);
};

}  // namespace faker

#endif  // FAKER_PERMUTATION_GENERATOR_H
