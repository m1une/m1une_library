#ifndef M1UNE_MATH_DISCRETE_LOGARITHM_HPP
#define M1UNE_MATH_DISCRETE_LOGARITHM_HPP 1

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <optional>
#include <unordered_map>

namespace m1une {
namespace math {

namespace internal {

inline uint64_t discrete_logarithm_multiply(
    uint64_t first,
    uint64_t second,
    uint64_t mod
) {
    return static_cast<uint64_t>(static_cast<unsigned __int128>(first) * second % mod);
}

inline uint64_t discrete_logarithm_power(
    uint64_t base,
    uint64_t exponent,
    uint64_t mod
) {
    uint64_t result = 1 % mod;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) result = discrete_logarithm_multiply(result, base, mod);
        base = discrete_logarithm_multiply(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

inline uint64_t discrete_logarithm_ceil_sqrt(uint64_t value) {
    uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long double>(value)));
    while (static_cast<unsigned __int128>(result) * result < value) result++;
    while (result > 0 &&
           static_cast<unsigned __int128>(result - 1) * (result - 1) >= value) {
        result--;
    }
    return result;
}

struct DiscreteLogarithmHash {
    std::size_t operator()(uint64_t value) const {
        value += 0x9e3779b97f4a7c15ULL;
        value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
        value ^= value >> 31;
        return static_cast<std::size_t>(value);
    }
};

// Solves coefficient * base^exponent = target (mod mod) for a positive
// exponent. Both coefficient and base must be invertible modulo mod.
inline std::optional<uint64_t> discrete_logarithm_coprime(
    uint64_t coefficient,
    uint64_t base,
    uint64_t target,
    uint64_t mod
) {
    const uint64_t step = discrete_logarithm_ceil_sqrt(mod);
    std::unordered_map<uint64_t, uint64_t, DiscreteLogarithmHash> baby;
    baby.max_load_factor(0.7F);
    baby.reserve(static_cast<std::size_t>(step));

    uint64_t value = target;
    for (uint64_t exponent = 0; exponent < step; exponent++) {
        baby[value] = exponent;
        value = discrete_logarithm_multiply(value, base, mod);
    }

    const uint64_t giant_factor = discrete_logarithm_power(base, step, mod);
    uint64_t giant = coefficient;
    for (uint64_t block = 1; block <= step; block++) {
        giant = discrete_logarithm_multiply(giant, giant_factor, mod);
        auto it = baby.find(giant);
        if (it == baby.end()) continue;
        const unsigned __int128 candidate =
            static_cast<unsigned __int128>(block) * step - it->second;
        if (candidate <= UINT64_MAX) return static_cast<uint64_t>(candidate);
    }
    return std::nullopt;
}

}  // namespace internal

// Returns the smallest nonnegative exponent x satisfying base^x = target
// modulo mod, or nullopt when no such exponent exists. Defines 0^0 as 1.
inline std::optional<uint64_t> discrete_logarithm(
    uint64_t base,
    uint64_t target,
    uint64_t mod
) {
    assert(mod >= 1);
    if (mod == 1) return uint64_t(0);
    base %= mod;
    target %= mod;

    uint64_t coefficient = 1;
    uint64_t offset = 0;
    while (true) {
        if (coefficient == target) return offset;
        const uint64_t divisor = std::gcd(base, mod);
        if (divisor == 1) break;
        if (target % divisor != 0) return std::nullopt;
        target /= divisor;
        mod /= divisor;
        coefficient = internal::discrete_logarithm_multiply(
            coefficient % mod, (base / divisor) % mod, mod);
        offset++;
    }

    auto remaining = internal::discrete_logarithm_coprime(
        coefficient, base % mod, target, mod);
    if (!remaining.has_value()) return std::nullopt;
    return offset + *remaining;
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_DISCRETE_LOGARITHM_HPP
