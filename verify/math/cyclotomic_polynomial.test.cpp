#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/cyclotomic_polynomial.hpp"
#include "../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

template <class T>
std::vector<T> multiply(
    const std::vector<T>& left,
    const std::vector<T>& right
) {
    std::vector<T> result(left.size() + right.size() - 1, T(0));
    for (int i = 0; i < int(left.size()); i++) {
        for (int j = 0; j < int(right.size()); j++) {
            result[i + j] += left[i] * right[j];
        }
    }
    return result;
}

void fixed_tests() {
    using m1une::math::cyclotomic_polynomial;

    assert(cyclotomic_polynomial(1) == std::vector<long long>({-1, 1}));
    assert(cyclotomic_polynomial(2) == std::vector<long long>({1, 1}));
    assert(cyclotomic_polynomial(3) == std::vector<long long>({1, 1, 1}));
    assert(cyclotomic_polynomial(4) == std::vector<long long>({1, 0, 1}));
    assert(cyclotomic_polynomial(6) == std::vector<long long>({1, -1, 1}));
    assert(
        cyclotomic_polynomial(12) ==
        std::vector<long long>({1, 0, -1, 0, 1})
    );
}

void product_identity_tests() {
    for (std::uint64_t index = 1; index <= 300; index++) {
        const std::vector<long long> polynomial =
            m1une::math::cyclotomic_polynomial(index);
        assert(polynomial.size() == m1une::math::euler_phi(index) + 1);
        assert(polynomial.back() == 1);
        if (index > 1) {
            assert(polynomial.front() == 1);
            for (int i = 0; i < int(polynomial.size()); i++) {
                assert(polynomial[i] == polynomial[polynomial.size() - 1 - i]);
            }
        }

        std::vector<long long> product(1, 1);
        for (std::uint64_t divisor : m1une::math::divisors(index)) {
            product = multiply(
                product,
                m1une::math::cyclotomic_polynomial(divisor)
            );
        }
        std::vector<long long> expected(index + 1, 0);
        expected[0] = -1;
        expected[index] = 1;
        assert(product == expected);
    }
}

void generic_coefficient_tests() {
    using Mint = m1une::math::modint998244353;
    for (std::uint64_t index = 1; index <= 200; index++) {
        const std::vector<long long> integer =
            m1une::math::cyclotomic_polynomial(index);
        const std::vector<Mint> modular =
            m1une::math::cyclotomic_polynomial<Mint>(index);
        assert(integer.size() == modular.size());
        for (int i = 0; i < int(integer.size()); i++) {
            assert(modular[i] == Mint(integer[i]));
        }
    }
}

}  // namespace

int main() {
    fixed_tests();
    product_identity_tests();
    generic_coefficient_tests();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
