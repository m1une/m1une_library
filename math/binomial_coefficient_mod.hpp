#ifndef M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP
#define M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP 1

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "number_theory.hpp"

namespace m1une {
namespace math {

// Binomial coefficients modulo a fixed, not necessarily prime, modulus.
class BinomialCoefficientMod {
   private:
    struct PrimePower {
        uint32_t prime;
        int exponent;
        uint32_t modulus;
        uint32_t crt_multiplier;
        std::vector<uint32_t> unit_factorial_prefix;

        uint32_t multiply(uint32_t lhs, uint32_t rhs) const {
            return uint32_t(uint64_t(lhs) * rhs % modulus);
        }

        uint32_t power(uint32_t base, uint64_t exponent_) const {
            uint32_t result = 1 % modulus;
            while (exponent_ > 0) {
                if (exponent_ & 1) result = multiply(result, base);
                base = multiply(base, base);
                exponent_ >>= 1;
            }
            return result;
        }

        uint64_t factorial_valuation(uint64_t n) const {
            uint64_t result = 0;
            while (n > 0) {
                n /= prime;
                result += n;
            }
            return result;
        }

        uint32_t unit_factorial(uint64_t n) const {
            if (n == 0) return 1 % modulus;
            const uint32_t block_product = unit_factorial_prefix.back();
            uint32_t result = power(block_product, n / modulus);
            result = multiply(result, unit_factorial_prefix[std::size_t(n % modulus)]);
            return multiply(result, unit_factorial(n / prime));
        }

        uint32_t binom(uint64_t n, uint64_t k) const {
            if (k > n) return 0;
            const uint64_t valuation = factorial_valuation(n) - factorial_valuation(k) -
                                       factorial_valuation(n - k);
            if (valuation >= uint64_t(exponent)) return 0;

            const uint32_t numerator = unit_factorial(n);
            const uint32_t denominator =
                multiply(unit_factorial(k), unit_factorial(n - k));
            const uint32_t inverse_denominator =
                uint32_t(inv_mod(denominator, modulus));
            uint32_t result = multiply(numerator, inverse_denominator);
            result = multiply(result, power(prime, valuation));
            return result;
        }
    };

    uint32_t _modulus;
    std::vector<PrimePower> _prime_powers;

   public:
    explicit BinomialCoefficientMod(uint32_t modulus) : _modulus(modulus) {
        assert(modulus >= 1);
        uint32_t remaining = modulus;
        for (uint32_t prime = 2; uint64_t(prime) * prime <= remaining; prime++) {
            if (remaining % prime != 0) continue;
            int exponent = 0;
            uint32_t prime_power = 1;
            do {
                remaining /= prime;
                prime_power *= prime;
                exponent++;
            } while (remaining % prime == 0);
            _prime_powers.push_back(
                PrimePower{prime, exponent, prime_power, 0, {}});
        }
        if (remaining > 1) {
            _prime_powers.push_back(PrimePower{remaining, 1, remaining, 0, {}});
        }

        for (PrimePower& component : _prime_powers) {
            component.unit_factorial_prefix.resize(std::size_t(component.modulus));
            component.unit_factorial_prefix[0] = 1;
            for (uint32_t value = 1; value < component.modulus; value++) {
                component.unit_factorial_prefix[value] =
                    component.unit_factorial_prefix[value - 1];
                if (value % component.prime != 0) {
                    component.unit_factorial_prefix[value] = component.multiply(
                        component.unit_factorial_prefix[value], value);
                }
            }

            const uint32_t other = modulus / component.modulus;
            const uint32_t inverse =
                uint32_t(inv_mod(other, component.modulus));
            component.crt_multiplier =
                uint32_t(uint64_t(other) * inverse % modulus);
        }
    }

    uint32_t modulus() const {
        return _modulus;
    }

    uint32_t binom(uint64_t n, uint64_t k) const {
        if (k > n || _modulus == 1) return 0;
        uint64_t result = 0;
        for (const PrimePower& component : _prime_powers) {
            const uint32_t residue = component.binom(n, k);
            result += uint64_t(residue) * component.crt_multiplier % _modulus;
            result %= _modulus;
        }
        return uint32_t(result);
    }

    uint32_t operator()(uint64_t n, uint64_t k) const {
        return binom(n, k);
    }
};

using ArbitraryModBinomialCoefficient = BinomialCoefficientMod;

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_BINOMIAL_COEFFICIENT_MOD_HPP
