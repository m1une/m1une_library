#ifndef M1UNE_MATH_BERNOULLI_HPP
#define M1UNE_MATH_BERNOULLI_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

#include "../fps/formal_power_series.hpp"
#include "combinatorics.hpp"

namespace m1une {
namespace math {

namespace bernoulli_detail {

template <class Mint>
std::vector<Mint> numbers(
    int maximum,
    const Combinatorics<Mint>& combinations
) {
    using Fps = fps::FormalPowerSeries<Mint>;
    Fps denominator(maximum + 1);
    for (int index = 0; index <= maximum; ++index) {
        denominator[index] = combinations.inverse_factorial(index + 1);
    }

    Fps generating_function = denominator.inv(maximum + 1);
    std::vector<Mint> result(maximum + 1);
    for (int index = 0; index <= maximum; ++index) {
        result[index] =
            generating_function[index] * combinations.factorial(index);
    }
    return result;
}

template <class Mint>
Mint evaluate_polynomial(const std::vector<Mint>& coefficients, Mint x) {
    Mint result = 0;
    for (int index = int(coefficients.size()) - 1; index >= 0; --index) {
        result = result * x + coefficients[index];
    }
    return result;
}

}  // namespace bernoulli_detail

// Uses x / (exp(x) - 1), so B_1 = -1/2.
template <class Mint>
std::vector<Mint> bernoulli_numbers(int maximum) {
    assert(maximum >= 0);
    assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());
    Combinatorics<Mint> combinations(maximum + 1);
    return bernoulli_detail::numbers(maximum, combinations);
}

template <class Mint>
class Bernoulli {
   public:
    explicit Bernoulli(int maximum)
        : combinations_(checked_maximum(maximum) + 1),
          numbers_(bernoulli_detail::numbers(maximum, combinations_)) {}

    int maximum() const {
        return int(numbers_.size()) - 1;
    }

    const std::vector<Mint>& numbers() const {
        return numbers_;
    }

    Mint number(int degree) const {
        assert(0 <= degree && degree <= maximum());
        return numbers_[degree];
    }

    // Coefficients of B_degree(x), in increasing order of powers of x.
    std::vector<Mint> polynomial_coefficients(int degree) const {
        assert(0 <= degree && degree <= maximum());
        std::vector<Mint> result(degree + 1);
        for (int power = 0; power <= degree; ++power) {
            result[power] =
                combinations_.binom(degree, power) *
                numbers_[degree - power];
        }
        return result;
    }

    Mint polynomial(int degree, Mint x) const {
        assert(0 <= degree && degree <= maximum());
        std::vector<Mint> powers(degree + 1, Mint(1));
        for (int power = 0; power < degree; ++power) {
            powers[power + 1] = powers[power] * x;
        }

        Mint result = 0;
        for (int index = 0; index <= degree; ++index) {
            result += combinations_.binom(degree, index) * numbers_[index] *
                      powers[degree - index];
        }
        return result;
    }

    // Returns sum_{i=0}^{n-1} i^degree, evaluated as a polynomial in n.
    Mint power_sum(Mint n, int degree) const {
        assert(0 <= degree && degree <= maximum());
        std::vector<Mint> powers(degree + 2, Mint(1));
        for (int power = 0; power <= degree; ++power) {
            powers[power + 1] = powers[power] * n;
        }

        Mint result = 0;
        for (int index = 0; index <= degree; ++index) {
            result += combinations_.binom(degree + 1, index) *
                      numbers_[index] * powers[degree + 1 - index];
        }
        return result * combinations_.inverse(degree + 1);
    }

    // Returns sum_{i=left}^{right-1} i^degree.
    Mint power_sum(Mint left, Mint right, int degree) const {
        return power_sum(right, degree) - power_sum(left, degree);
    }

    // Coefficients of sum_{i=0}^{n-1} i^degree as a polynomial in n.
    std::vector<Mint> power_sum_polynomial(int degree) const {
        assert(0 <= degree && degree <= maximum());
        std::vector<Mint> result(degree + 2);
        Mint inverse = combinations_.inverse(degree + 1);
        for (int index = 0; index <= degree; ++index) {
            result[degree + 1 - index] +=
                combinations_.binom(degree + 1, index) * numbers_[index] *
                inverse;
        }
        return result;
    }

    // If P is given by coefficients, returns coefficients of the unique Q
    // with Q(0) = 0 and Q(n) = sum_{i=0}^{n-1} P(i).
    std::vector<Mint> polynomial_prefix_sum(
        const std::vector<Mint>& coefficients
    ) const {
        if (coefficients.empty()) return std::vector<Mint>{Mint(0)};
        int degree = int(coefficients.size()) - 1;
        assert(degree <= maximum());

        std::vector<Mint> result(degree + 2);
        for (int source_degree = 0;
             source_degree <= degree;
             ++source_degree) {
            Mint inverse = combinations_.inverse(source_degree + 1);
            for (int index = 0; index <= source_degree; ++index) {
                result[source_degree + 1 - index] +=
                    coefficients[source_degree] *
                    combinations_.binom(source_degree + 1, index) *
                    numbers_[index] * inverse;
            }
        }
        return result;
    }

    // Returns sum_{i=left}^{right-1} P(i).
    Mint polynomial_sum(
        const std::vector<Mint>& coefficients,
        Mint left,
        Mint right
    ) const {
        std::vector<Mint> prefix = polynomial_prefix_sum(coefficients);
        return bernoulli_detail::evaluate_polynomial(prefix, right) -
               bernoulli_detail::evaluate_polynomial(prefix, left);
    }

    // Returns sum_{i=0}^{count-1} (start + step*i)^degree.
    Mint arithmetic_progression_power_sum(
        Mint start,
        Mint step,
        Mint count,
        int degree
    ) const {
        assert(0 <= degree && degree <= maximum());
        std::vector<Mint> start_powers(degree + 1, Mint(1));
        std::vector<Mint> step_powers(degree + 1, Mint(1));
        for (int power = 0; power < degree; ++power) {
            start_powers[power + 1] = start_powers[power] * start;
            step_powers[power + 1] = step_powers[power] * step;
        }

        Mint result = 0;
        for (int power = 0; power <= degree; ++power) {
            result += combinations_.binom(degree, power) *
                      start_powers[degree - power] * step_powers[power] *
                      power_sum(count, power);
        }
        return result;
    }

   private:
    static int checked_maximum(int maximum) {
        assert(maximum >= 0);
        assert(static_cast<uint64_t>(maximum) + 1 < Mint::mod());
        return maximum;
    }

    Combinatorics<Mint> combinations_;
    std::vector<Mint> numbers_;
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_BERNOULLI_HPP
