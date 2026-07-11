#ifndef M1UNE_MATH_MODULAR_SQUARE_ROOT_HPP
#define M1UNE_MATH_MODULAR_SQUARE_ROOT_HPP 1

#include <cassert>
#include <cstdint>
#include <optional>

namespace m1une {
namespace math {

namespace internal {

inline uint64_t modular_square_root_multiply(uint64_t lhs, uint64_t rhs, uint64_t mod) {
    return static_cast<uint64_t>(static_cast<unsigned __int128>(lhs) * rhs % mod);
}

inline uint64_t modular_square_root_power(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1) result = modular_square_root_multiply(result, base, mod);
        base = modular_square_root_multiply(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

}  // namespace internal

// Returns x such that x * x = value (mod prime), or nullopt when no such x exists.
// The modulus must be prime.
inline std::optional<uint64_t> modular_square_root(uint64_t value, uint64_t prime) {
    assert(prime >= 2);
    value %= prime;
    if (value == 0 || prime == 2) return value;

    if (internal::modular_square_root_power(value, (prime - 1) / 2, prime) != 1) {
        return std::nullopt;
    }
    if (prime % 4 == 3) {
        return internal::modular_square_root_power(value, prime / 4 + 1, prime);
    }

    uint64_t odd_part = prime - 1;
    int power_of_two = 0;
    while ((odd_part & 1) == 0) {
        odd_part >>= 1;
        power_of_two++;
    }

    uint64_t non_residue = 2;
    while (internal::modular_square_root_power(non_residue, (prime - 1) / 2, prime) == 1) {
        non_residue++;
    }

    uint64_t c = internal::modular_square_root_power(non_residue, odd_part, prime);
    uint64_t root = internal::modular_square_root_power(value, odd_part / 2 + 1, prime);
    uint64_t remainder = internal::modular_square_root_power(value, odd_part, prime);
    int remaining_power = power_of_two;

    while (remainder != 1) {
        int exponent = 1;
        uint64_t squared = internal::modular_square_root_multiply(remainder, remainder, prime);
        while (squared != 1) {
            squared = internal::modular_square_root_multiply(squared, squared, prime);
            exponent++;
        }

        uint64_t correction = c;
        for (int i = 0; i < remaining_power - exponent - 1; i++) {
            correction = internal::modular_square_root_multiply(correction, correction, prime);
        }
        root = internal::modular_square_root_multiply(root, correction, prime);
        c = internal::modular_square_root_multiply(correction, correction, prime);
        remainder = internal::modular_square_root_multiply(remainder, c, prime);
        remaining_power = exponent;
    }
    return root;
}

template <class Mint>
std::optional<Mint> modular_square_root(Mint value) {
    auto root = modular_square_root(static_cast<uint64_t>(value.val()),
                                    static_cast<uint64_t>(Mint::mod()));
    if (!root.has_value()) return std::nullopt;
    return Mint(*root);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MODULAR_SQUARE_ROOT_HPP
