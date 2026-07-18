#ifndef M1UNE_FPS_POLYNOMIAL_ROOTS_HPP
#define M1UNE_FPS_POLYNOMIAL_ROOTS_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "half_gcd.hpp"

namespace m1une {
namespace fps {

namespace internal {

struct PolynomialRootsRandom {
    uint64_t state;

    uint64_t operator()() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    }
};

template <class Mint>
FormalPowerSeries<Mint> polynomial_roots_power_mod(
    FormalPowerSeries<Mint> base, uint64_t exponent,
    const FormalPowerSeries<Mint>& modulus) {
    using Fps = FormalPowerSeries<Mint>;
    Fps result(1, Mint(1));
    result %= modulus;
    base %= modulus;
    while (exponent > 0) {
        if (exponent & 1) result = (result * base) % modulus;
        exponent >>= 1;
        if (exponent > 0) base = (base * base) % modulus;
    }
    return result;
}

}  // namespace internal

template <class Mint>
std::vector<Mint> polynomial_roots(
    FormalPowerSeries<Mint> polynomial,
    uint64_t seed = 88172645463325252ULL) {
    using Fps = FormalPowerSeries<Mint>;
    polynomial.shrink();
    assert(!polynomial.empty());
    if (polynomial.size() == 1) return {};

    const uint64_t modulus = Mint::mod();
    if (modulus == 2) {
        std::vector<Mint> result;
        if (polynomial.evaluate(Mint(0)) == Mint(0)) result.push_back(Mint(0));
        if (polynomial.evaluate(Mint(1)) == Mint(0)) result.push_back(Mint(1));
        return result;
    }
    assert(modulus & 1);

    Fps x(2);
    x[1] = Mint(1);
    Fps frobenius = internal::polynomial_roots_power_mod(x, modulus, polynomial);
    frobenius -= x;
    frobenius.shrink();
    Fps linear_part = polynomial_gcd(polynomial, frobenius);
    if (linear_part.size() <= 1) return {};

    if (seed == 0) seed = 88172645463325252ULL;
    internal::PolynomialRootsRandom random{seed};
    std::vector<Mint> result;
    auto split = [&](auto&& self, Fps current) -> void {
        current.shrink();
        if (current.size() <= 1) return;
        if (current.size() == 2) {
            result.push_back((Mint(0) - current[0]) / current[1]);
            return;
        }

        Fps divisor;
        do {
            Fps shifted_x(2);
            shifted_x[0] = Mint(random() % modulus);
            shifted_x[1] = Mint(1);
            Fps separator = internal::polynomial_roots_power_mod(
                std::move(shifted_x), (modulus - 1) / 2, current);
            if (separator.empty()) separator.resize(1);
            separator[0] -= Mint(1);
            separator.shrink();
            divisor = polynomial_gcd(current, separator);
        } while (divisor.size() <= 1 || divisor.size() == current.size());

        auto division = current.divmod(divisor);
        assert(division.second.empty());
        self(self, std::move(divisor));
        self(self, std::move(division.first));
    };
    split(split, std::move(linear_part));

    std::sort(result.begin(), result.end(), [](Mint lhs, Mint rhs) {
        return lhs.val() < rhs.val();
    });
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_POLYNOMIAL_ROOTS_HPP
