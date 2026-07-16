#ifndef M1UNE_MATH_MODULAR_KTH_ROOT_HPP
#define M1UNE_MATH_MODULAR_KTH_ROOT_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

#include "integer_arithmetic.hpp"

namespace m1une {
namespace math {

namespace modular_kth_root_detail {

inline uint64_t multiply(uint64_t first, uint64_t second, uint64_t mod) {
    return static_cast<uint64_t>(static_cast<__uint128_t>(first) * second % mod);
}

inline uint64_t power(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1 % mod;
    while (exponent != 0) {
        if (exponent & 1) result = multiply(result, base, mod);
        base = multiply(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

inline uint64_t integer_power(uint64_t base, int exponent) {
    uint64_t result = 1;
    for (int i = 0; i < exponent; i++) result *= base;
    return result;
}

inline uint64_t inverse(uint64_t value, uint64_t mod) {
    if (mod == 1) return 0;
    value %= mod;
    uint64_t old_remainder = mod;
    uint64_t remainder = value;
    __int128_t old_coefficient = 0;
    __int128_t coefficient = 1;
    while (remainder != 0) {
        const uint64_t quotient = old_remainder / remainder;
        const uint64_t next_remainder =
            old_remainder - quotient * remainder;
        old_remainder = remainder;
        remainder = next_remainder;

        const __int128_t next_coefficient =
            old_coefficient - static_cast<__int128_t>(quotient) * coefficient;
        old_coefficient = coefficient;
        coefficient = next_coefficient;
    }
    assert(old_remainder == 1);
    old_coefficient %= static_cast<__int128_t>(mod);
    if (old_coefficient < 0) old_coefficient += mod;
    return static_cast<uint64_t>(old_coefficient);
}

inline uint64_t extract_prime_power_root(
    uint64_t value,
    uint64_t root_prime,
    int exponent,
    uint64_t prime
) {
    uint64_t coprime_part = prime - 1;
    int available_exponent = 0;
    while (coprime_part % root_prime == 0) {
        coprime_part /= root_prime;
        available_exponent++;
    }
    assert(exponent <= available_exponent);

    const uint64_t root_prime_power = integer_power(root_prime, exponent);
    const uint64_t inverse_coprime_part = inverse(
        coprime_part, root_prime_power
    );
    const uint64_t residue = static_cast<uint64_t>(
        static_cast<__uint128_t>(root_prime_power - 1) *
        inverse_coprime_part % root_prime_power
    );
    const uint64_t root_exponent = static_cast<uint64_t>(
        (static_cast<__uint128_t>(residue) * coprime_part + 1) /
        root_prime_power
    );
    uint64_t root = power(value, root_exponent, prime);
    if (exponent == available_exponent) return root;

    uint64_t non_residue = 2;
    while (power(non_residue, (prime - 1) / root_prime, prime) == 1) {
        non_residue++;
    }
    const uint64_t generator = power(non_residue, coprime_part, prime);
    const uint64_t digit_generator = power(
        generator,
        integer_power(root_prime, available_exponent - 1),
        prime
    );

    const uint64_t step = isqrt(
        static_cast<uint64_t>(available_exponent - exponent) * root_prime
    ) + 1;
    const uint64_t giant_factor = power(digit_generator, step, prime);
    std::vector<std::pair<uint64_t, uint64_t>> baby_steps;
    baby_steps.reserve(step + 1);
    uint64_t current = 1;
    for (uint64_t index = 0; index <= step; index++) {
        baby_steps.emplace_back(current, index);
        current = multiply(current, giant_factor, prime);
    }
    std::sort(baby_steps.begin(), baby_steps.end());

    const uint64_t inverse_digit_generator = power(
        digit_generator, prime - 2, prime
    );
    for (int level = exponent; level < available_exponent; level++) {
        const uint64_t root_power = power(root, root_prime_power, prime);
        const uint64_t error = multiply(
            power(root_power, prime - 2, prime), value, prime
        );
        uint64_t target = power(
            error,
            integer_power(root_prime, available_exponent - 1 - level),
            prime
        );

        bool found = false;
        uint64_t logarithm = 0;
        for (uint64_t remainder = 0; remainder <= step; remainder++) {
            auto iterator = std::upper_bound(
                baby_steps.begin(),
                baby_steps.end(),
                target,
                [](uint64_t key, const std::pair<uint64_t, uint64_t>& entry) {
                    return key < entry.first;
                }
            );
            if (iterator != baby_steps.begin()) {
                --iterator;
                if (iterator->first == target) {
                    logarithm = remainder + step * iterator->second;
                    found = true;
                    break;
                }
            }
            target = multiply(target, inverse_digit_generator, prime);
        }
        assert(found);
        if (!found) return 0;

        const uint64_t correction_exponent =
            logarithm * integer_power(root_prime, level - exponent);
        root = multiply(
            root,
            power(generator, correction_exponent, prime),
            prime
        );
    }
    return root;
}

}  // namespace modular_kth_root_detail

// Returns x such that x^degree = value (mod prime), or nullopt when no root
// exists. The modulus must be prime.
inline std::optional<uint64_t> modular_kth_root(
    uint64_t value,
    uint64_t degree,
    uint64_t prime
) {
    assert(prime >= 2);
    value %= prime;
    if (degree == 0) {
        if (value == 1) return uint64_t(0);
        return std::nullopt;
    }
    if (value == 0) return uint64_t(0);
    if (prime == 2) return uint64_t(1);

    const uint64_t group_order = prime - 1;
    degree %= group_order;
    const uint64_t common_divisor = std::gcd(degree, group_order);
    if (
        modular_kth_root_detail::power(
            value, group_order / common_divisor, prime
        ) != 1
    ) {
        return std::nullopt;
    }

    const uint64_t reduced_order = group_order / common_divisor;
    uint64_t transformed = 1;
    if (reduced_order != 1) {
        const uint64_t inverse_degree = modular_kth_root_detail::inverse(
            degree / common_divisor, reduced_order
        );
        transformed = modular_kth_root_detail::power(
            value, inverse_degree, prime
        );
    }

    uint64_t remaining = common_divisor;
    int exponent = 0;
    while ((remaining & 1) == 0) {
        remaining >>= 1;
        exponent++;
    }
    if (exponent != 0) {
        transformed = modular_kth_root_detail::extract_prime_power_root(
            transformed, 2, exponent, prime
        );
    }
    for (uint64_t divisor = 3; divisor <= remaining / divisor; divisor += 2) {
        exponent = 0;
        while (remaining % divisor == 0) {
            remaining /= divisor;
            exponent++;
        }
        if (exponent != 0) {
            transformed = modular_kth_root_detail::extract_prime_power_root(
                transformed, divisor, exponent, prime
            );
        }
    }
    if (remaining != 1) {
        transformed = modular_kth_root_detail::extract_prime_power_root(
            transformed, remaining, 1, prime
        );
    }
    return transformed;
}

template <class Mint>
std::optional<Mint> modular_kth_root(Mint value, uint64_t degree) {
    auto root = modular_kth_root(
        static_cast<uint64_t>(value.val()),
        degree,
        static_cast<uint64_t>(Mint::mod())
    );
    if (!root.has_value()) return std::nullopt;
    return Mint(*root);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MODULAR_KTH_ROOT_HPP
