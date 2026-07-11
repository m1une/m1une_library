#ifndef M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP
#define M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
struct PolynomialFactor {
    FormalPowerSeries<Mint> polynomial;
    int multiplicity;
};

template <class Mint>
struct PolynomialFactorization {
    Mint leading_coefficient;
    std::vector<PolynomialFactor<Mint>> factors;
};

namespace internal {

template <class Mint>
FormalPowerSeries<Mint> factorization_monic(FormalPowerSeries<Mint> polynomial) {
    polynomial.shrink();
    if (polynomial.empty()) return polynomial;
    polynomial /= polynomial.back();
    return polynomial;
}

template <class Mint>
FormalPowerSeries<Mint> factorization_multiply(
    const FormalPowerSeries<Mint>& first,
    const FormalPowerSeries<Mint>& second
) {
    if (first.empty() || second.empty()) return {};
    FormalPowerSeries<Mint> result(first.size() + second.size() - 1);
    for (int i = 0; i < int(first.size()); i++) {
        for (int j = 0; j < int(second.size()); j++) {
            result[i + j] += first[i] * second[j];
        }
    }
    result.shrink();
    return result;
}

template <class Mint>
std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>> factorization_divmod(
    FormalPowerSeries<Mint> dividend,
    FormalPowerSeries<Mint> divisor
) {
    dividend.shrink();
    divisor.shrink();
    assert(!divisor.empty());
    if (dividend.size() < divisor.size()) return std::make_pair(FormalPowerSeries<Mint>(), dividend);

    FormalPowerSeries<Mint> quotient(dividend.size() - divisor.size() + 1);
    const Mint inverse_leading = divisor.back().inv();
    for (int i = int(dividend.size()) - 1; i >= int(divisor.size()) - 1; i--) {
        const Mint coefficient = dividend[i] * inverse_leading;
        const int shift = i - int(divisor.size()) + 1;
        quotient[shift] = coefficient;
        if (coefficient == Mint(0)) continue;
        for (int j = 0; j < int(divisor.size()); j++) {
            dividend[shift + j] -= coefficient * divisor[j];
        }
    }
    quotient.shrink();
    dividend.resize(divisor.size() - 1);
    dividend.shrink();
    return std::make_pair(std::move(quotient), std::move(dividend));
}

template <class Mint>
FormalPowerSeries<Mint> factorization_gcd(
    FormalPowerSeries<Mint> first,
    FormalPowerSeries<Mint> second
) {
    first.shrink();
    second.shrink();
    while (!second.empty()) {
        FormalPowerSeries<Mint> remainder =
            factorization_divmod(std::move(first), second).second;
        first = std::move(second);
        second = std::move(remainder);
    }
    return factorization_monic(std::move(first));
}

template <class Mint>
FormalPowerSeries<Mint> factorization_multiply_mod(
    const FormalPowerSeries<Mint>& first,
    const FormalPowerSeries<Mint>& second,
    const FormalPowerSeries<Mint>& modulus
) {
    return factorization_divmod(factorization_multiply(first, second), modulus).second;
}

template <class Mint>
FormalPowerSeries<Mint> factorization_power_mod(
    FormalPowerSeries<Mint> base,
    uint64_t exponent,
    const FormalPowerSeries<Mint>& modulus
) {
    FormalPowerSeries<Mint> result(1, Mint(1));
    result = factorization_divmod(std::move(result), modulus).second;
    base = factorization_divmod(std::move(base), modulus).second;
    while (exponent > 0) {
        if (exponent & 1) result = factorization_multiply_mod(result, base, modulus);
        exponent >>= 1;
        if (exponent > 0) base = factorization_multiply_mod(base, base, modulus);
    }
    return result;
}

struct PolynomialFactorizationRandom {
    uint64_t state;

    uint64_t operator()() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    }
};

template <class Mint>
FormalPowerSeries<Mint> factorization_random_polynomial(
    int coefficient_count,
    PolynomialFactorizationRandom& random
) {
    FormalPowerSeries<Mint> result(coefficient_count);
    const uint64_t mod = Mint::mod();
    for (Mint& coefficient : result) coefficient = Mint(random() % mod);
    result.shrink();
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> equal_degree_separator_odd(
    const FormalPowerSeries<Mint>& random_polynomial,
    int factor_degree,
    const FormalPowerSeries<Mint>& modulus
) {
    FormalPowerSeries<Mint> power = factorization_power_mod(
        random_polynomial, (uint64_t(Mint::mod()) - 1) / 2, modulus);
    FormalPowerSeries<Mint> result(1, Mint(1));
    for (int i = 0; i < factor_degree; i++) {
        result = factorization_multiply_mod(result, power, modulus);
        if (i + 1 < factor_degree) {
            power = factorization_power_mod(power, Mint::mod(), modulus);
        }
    }
    if (result.empty()) result.resize(1);
    result[0] -= Mint(1);
    result.shrink();
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> equal_degree_separator_two(
    const FormalPowerSeries<Mint>& random_polynomial,
    int factor_degree,
    const FormalPowerSeries<Mint>& modulus
) {
    FormalPowerSeries<Mint> power =
        factorization_divmod(random_polynomial, modulus).second;
    FormalPowerSeries<Mint> result;
    for (int i = 0; i < factor_degree; i++) {
        result += power;
        result.shrink();
        if (i + 1 < factor_degree) {
            power = factorization_multiply_mod(power, power, modulus);
        }
    }
    return result;
}

template <class Mint>
std::vector<FormalPowerSeries<Mint>> equal_degree_factorization(
    FormalPowerSeries<Mint> polynomial,
    int factor_degree,
    PolynomialFactorizationRandom& random
) {
    using Fps = FormalPowerSeries<Mint>;
    polynomial = factorization_monic(std::move(polynomial));
    std::vector<Fps> queue(1, std::move(polynomial));
    std::vector<Fps> result;
    for (int head = 0; head < int(queue.size()); head++) {
        Fps current = factorization_monic(std::move(queue[head]));
        const int degree = int(current.size()) - 1;
        if (degree == factor_degree) {
            result.push_back(std::move(current));
            continue;
        }

        Fps divisor;
        do {
            Fps random_polynomial =
                factorization_random_polynomial<Mint>(degree, random);
            Fps separator = Mint::mod() == 2
                ? equal_degree_separator_two(random_polynomial, factor_degree, current)
                : equal_degree_separator_odd(random_polynomial, factor_degree, current);
            divisor = factorization_gcd(current, std::move(separator));
        } while (divisor.size() <= 1 || divisor.size() == current.size());

        Fps quotient = factorization_divmod(current, divisor).first;
        queue.push_back(std::move(divisor));
        queue.push_back(std::move(quotient));
    }
    return result;
}

}  // namespace internal

template <class Mint>
PolynomialFactorization<Mint> polynomial_factorize(
    FormalPowerSeries<Mint> polynomial,
    uint64_t seed = 88172645463325252ULL
) {
    using Fps = FormalPowerSeries<Mint>;
    polynomial.shrink();
    assert(!polynomial.empty());

    const Mint leading_coefficient = polynomial.back();
    polynomial /= leading_coefficient;
    std::vector<PolynomialFactor<Mint>> factors;
    if (polynomial.size() == 1) return {leading_coefficient, std::move(factors)};

    if (seed == 0) seed = 88172645463325252ULL;
    internal::PolynomialFactorizationRandom random{seed};
    const Fps x = Fps({Mint(0), Mint(1)});
    Fps frobenius = x;
    for (int degree = 1;
         polynomial.size() > 1 && 2 * degree <= int(polynomial.size()) - 1;
         degree++) {
        frobenius = internal::factorization_power_mod(
            std::move(frobenius), Mint::mod(), polynomial);
        Fps difference = frobenius - x;
        difference.shrink();
        Fps product = internal::factorization_gcd(polynomial, std::move(difference));
        if (product.size() <= 1) continue;

        std::vector<Fps> distinct = internal::equal_degree_factorization(
            std::move(product), degree, random);
        for (Fps& factor : distinct) {
            int multiplicity = 0;
            while (factor.size() <= polynomial.size()) {
                auto division = internal::factorization_divmod(polynomial, factor);
                if (!division.second.empty()) break;
                polynomial = std::move(division.first);
                multiplicity++;
            }
            assert(multiplicity > 0);
            factors.push_back({std::move(factor), multiplicity});
        }
    }
    if (polynomial.size() > 1) {
        factors.push_back({internal::factorization_monic(std::move(polynomial)), 1});
    }

    auto less = [](const PolynomialFactor<Mint>& first,
                   const PolynomialFactor<Mint>& second) {
        if (first.polynomial.size() != second.polynomial.size()) {
            return first.polynomial.size() < second.polynomial.size();
        }
        for (int i = int(first.polynomial.size()) - 1; i >= 0; i--) {
            if (first.polynomial[i].val() != second.polynomial[i].val()) {
                return first.polynomial[i].val() < second.polynomial[i].val();
            }
        }
        return false;
    };
    std::sort(factors.begin(), factors.end(), less);

    std::vector<PolynomialFactor<Mint>> merged;
    for (PolynomialFactor<Mint>& factor : factors) {
        if (!merged.empty() && merged.back().polynomial == factor.polynomial) {
            merged.back().multiplicity += factor.multiplicity;
        } else {
            merged.push_back(std::move(factor));
        }
    }
    return {leading_coefficient, std::move(merged)};
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_POLYNOMIAL_FACTORIZATION_HPP
