#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/bernoulli.hpp"
#include "../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

using Mint = m1une::math::modint998244353;

Mint evaluate(const std::vector<Mint>& coefficients, Mint x) {
    Mint result = 0;
    for (int index = int(coefficients.size()) - 1; index >= 0; --index) {
        result = result * x + coefficients[index];
    }
    return result;
}

Mint power(Mint base, int exponent) {
    Mint result = 1;
    while (exponent--) result *= base;
    return result;
}

void test_numbers_and_polynomials() {
    m1une::math::Bernoulli<Mint> bernoulli(30);
    assert(bernoulli.number(0) == Mint(1));
    assert(bernoulli.number(1) * Mint(2) == Mint(-1));
    assert(bernoulli.number(2) * Mint(6) == Mint(1));
    assert(bernoulli.number(4) * Mint(30) == Mint(-1));
    for (int degree = 3; degree <= 29; degree += 2) {
        assert(bernoulli.number(degree) == Mint(0));
    }

    for (int degree = 0; degree <= 20; ++degree) {
        auto coefficients = bernoulli.polynomial_coefficients(degree);
        for (int value = -5; value <= 5; ++value) {
            Mint x = value;
            assert(evaluate(coefficients, x) == bernoulli.polynomial(degree, x));
            if (degree > 0) {
                assert(
                    bernoulli.polynomial(degree, x + Mint(1)) -
                        bernoulli.polynomial(degree, x) ==
                    Mint(degree) * power(x, degree - 1)
                );
            }
        }
    }
}

void test_power_sums() {
    m1une::math::Bernoulli<Mint> bernoulli(20);
    for (int degree = 0; degree <= 20; ++degree) {
        auto coefficients = bernoulli.power_sum_polynomial(degree);
        Mint expected = 0;
        for (int n = 0; n <= 40; ++n) {
            assert(bernoulli.power_sum(Mint(n), degree) == expected);
            assert(evaluate(coefficients, Mint(n)) == expected);
            expected += power(Mint(n), degree);
        }
    }

    for (int degree = 0; degree <= 12; ++degree) {
        for (int left = -10; left <= 10; ++left) {
            Mint expected = 0;
            for (int right = left; right <= 12; ++right) {
                assert(
                    bernoulli.power_sum(Mint(left), Mint(right), degree) ==
                    expected
                );
                expected += power(Mint(right), degree);
            }
        }
    }
}

void test_polynomial_sums_randomized() {
    m1une::math::Bernoulli<Mint> bernoulli(12);
    std::uint64_t state = 0xbb67ae8584caa73bULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int test = 0; test < 2000; ++test) {
        int degree = static_cast<int>(random() % 13);
        std::vector<Mint> coefficients(degree + 1);
        for (Mint& coefficient : coefficients) {
            coefficient = static_cast<long long>(random() % 101) - 50;
        }

        auto prefix = bernoulli.polynomial_prefix_sum(coefficients);
        for (int x = -10; x <= 10; ++x) {
            assert(
                evaluate(prefix, Mint(x + 1)) - evaluate(prefix, Mint(x)) ==
                evaluate(coefficients, Mint(x))
            );
        }

        int left = static_cast<int>(random() % 21) - 10;
        int length = static_cast<int>(random() % 21);
        int right = left + length;
        Mint expected = 0;
        for (int x = left; x < right; ++x) {
            expected += evaluate(coefficients, Mint(x));
        }
        assert(
            bernoulli.polynomial_sum(
                coefficients,
                Mint(left),
                Mint(right)
            ) == expected
        );
    }
}

void test_arithmetic_progressions() {
    m1une::math::Bernoulli<Mint> bernoulli(12);
    for (int degree = 0; degree <= 12; ++degree) {
        for (int start = -3; start <= 3; ++start) {
            for (int step = -2; step <= 2; ++step) {
                Mint expected = 0;
                for (int count = 0; count <= 15; ++count) {
                    assert(
                        bernoulli.arithmetic_progression_power_sum(
                            Mint(start),
                            Mint(step),
                            Mint(count),
                            degree
                        ) == expected
                    );
                    expected += power(Mint(start + step * count), degree);
                }
            }
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_numbers_and_polynomials();
    test_power_sums();
    test_polynomial_sums_randomized();
    test_arithmetic_progressions();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
