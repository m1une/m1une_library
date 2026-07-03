#ifndef M1UNE_MATH_REPUNIT_HPP
#define M1UNE_MATH_REPUNIT_HPP 1

#include <cassert>
#include <cstdint>
#include <numeric>
#include <optional>
#include <utility>

namespace m1une {
namespace math {

template <class T>
constexpr std::pair<T, T> repunit_and_power(
    std::uint64_t length,
    T base = T(10)
) {
    T result = T(0);
    T result_power = T(1);
    T block = T(1);
    T block_power = base;

    while (length > 0) {
        if (length & 1) {
            result = result * block_power + block;
            result_power = result_power * block_power;
        }
        block = block * block_power + block;
        block_power = block_power * block_power;
        length >>= 1;
    }
    return std::make_pair(result, result_power);
}

// Returns 1 + base + ... + base^(length - 1).
// The arithmetic, including any modular reduction, is performed by T.
template <class T>
constexpr T repunit(std::uint64_t length, T base = T(10)) {
    return repunit_and_power<T>(length, base).first;
}

template <class T>
constexpr T repdigit(std::uint64_t length, T digit, T base = T(10)) {
    return digit * repunit<T>(length, base);
}

template <class T>
constexpr T concatenate_digits(
    T left,
    T right,
    std::uint64_t right_length,
    T base = T(10)
) {
    return left * repunit_and_power<T>(right_length, base).second + right;
}

namespace repunit_detail {

inline std::uint64_t multiply_mod(
    std::uint64_t left,
    std::uint64_t right,
    std::uint64_t mod
) {
    return static_cast<std::uint64_t>(
        static_cast<unsigned __int128>(left) * right % mod
    );
}

inline std::pair<std::uint64_t, std::uint64_t> repunit_and_power_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod
) {
    if (mod == 1) return std::make_pair(0, 0);

    std::uint64_t result = 0;
    std::uint64_t result_power = 1;
    std::uint64_t block = 1;
    std::uint64_t block_power = base % mod;
    while (length > 0) {
        if (length & 1) {
            result = (
                static_cast<unsigned __int128>(result) * block_power + block
            ) % mod;
            result_power = multiply_mod(result_power, block_power, mod);
        }
        block = (
            static_cast<unsigned __int128>(block) * block_power + block
        ) % mod;
        block_power = multiply_mod(block_power, block_power, mod);
        length >>= 1;
    }
    return std::make_pair(result, result_power);
}

}  // namespace repunit_detail

inline std::pair<std::uint64_t, std::uint64_t> repunit_and_power_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod
) {
    assert(mod >= 1);
    return repunit_detail::repunit_and_power_mod(length, base, mod);
}

inline std::uint64_t repunit_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod
) {
    return repunit_and_power_mod(length, base, mod).first;
}

inline std::uint64_t repdigit_mod(
    std::uint64_t length,
    std::uint64_t digit,
    std::uint64_t base,
    std::uint64_t mod
) {
    assert(mod >= 1);
    if (mod == 1) return 0;
    return repunit_detail::multiply_mod(
        digit % mod,
        repunit_mod(length, base, mod),
        mod
    );
}

inline std::uint64_t concatenate_digits_mod(
    std::uint64_t left,
    std::uint64_t right,
    std::uint64_t right_length,
    std::uint64_t base,
    std::uint64_t mod
) {
    assert(mod >= 1);
    if (mod == 1) return 0;
    const std::uint64_t power =
        repunit_and_power_mod(right_length, base, mod).second;
    return (
        static_cast<unsigned __int128>(left % mod) * power + right % mod
    ) % mod;
}

inline std::optional<std::uint64_t> minimum_repunit_length(
    std::uint64_t divisor,
    std::uint64_t base = 10
) {
    assert(divisor >= 1);
    assert(base >= 2);
    if (std::gcd(divisor, base) != 1) return std::nullopt;

    std::uint64_t remainder = 0;
    for (std::uint64_t length = 1; length <= divisor; length++) {
        remainder = (
            static_cast<unsigned __int128>(remainder) * base + 1
        ) % divisor;
        if (remainder == 0) return length;
    }
    return std::nullopt;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_REPUNIT_HPP
