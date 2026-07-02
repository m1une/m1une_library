#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include <cassert>
#include <iostream>
#include <optional>
#include <random>

#include "../../fps/half_gcd.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

Fps naive_gcd(Fps first, Fps second) {
    first.shrink();
    second.shrink();
    while (!second.empty()) {
        while (first.size() >= second.size()) {
            const int shift = int(first.size() - second.size());
            const mint factor = first.back() / second.back();
            for (int i = 0; i < int(second.size()); i++) {
                first[i + shift] -= factor * second[i];
            }
            first.shrink();
        }
        std::swap(first, second);
    }
    if (!first.empty()) first /= first.back();
    return first;
}

void test_randomized() {
    std::mt19937 rng(712367);
    for (int iteration = 0; iteration < 200; iteration++) {
        const int first_size = 1 + int(rng() % 35);
        const int second_size = 1 + int(rng() % first_size);
        Fps first(first_size), second(second_size);
        for (mint& value : first) value = mint(rng());
        for (mint& value : second) value = mint(rng());
        first.back() = mint(1 + rng() % (mint::mod() - 1));
        second.back() = mint(1 + rng() % (mint::mod() - 1));

        auto matrix = m1une::fps::half_gcd(first, second);
        auto reduced = matrix.apply(first, second);
        if (int(second.size()) > (first_size + 1) / 2) {
            assert(reduced.second.size() < second.size());
        }
        Fps determinant = matrix.a00 * matrix.a11 - matrix.a01 * matrix.a10;
        determinant.shrink();
        assert(determinant.size() == 1);
        assert(determinant[0] == mint(1) || determinant[0] == mint(0) - mint(1));
        assert(naive_gcd(reduced.first, reduced.second) == naive_gcd(first, second));

        auto extended = m1une::fps::polynomial_extended_gcd(first, second);
        Fps bezout = first * extended.x + second * extended.y;
        bezout.shrink();
        assert(bezout == extended.gcd);
        assert(extended.gcd == naive_gcd(first, second));

        auto swapped_extended = m1une::fps::polynomial_extended_gcd(second, first);
        Fps swapped_bezout = second * swapped_extended.x + first * swapped_extended.y;
        swapped_bezout.shrink();
        assert(swapped_bezout == swapped_extended.gcd);
        assert(swapped_extended.gcd == extended.gcd);

        if (extended.gcd.size() == 1) {
            std::optional<Fps> inverse = m1une::fps::polynomial_inv_mod(first, second);
            assert(inverse.has_value());
            assert((first * *inverse) % second == Fps(1, mint(1)) % second);
        }
    }

    Fps zero;
    Fps polynomial = {2, 3, 1};
    assert(m1une::fps::polynomial_gcd(zero, zero).empty());
    assert(m1une::fps::polynomial_gcd(zero, polynomial) == polynomial / polynomial.back());

    Fps factor = {1, 1};
    std::optional<Fps> no_inverse =
        m1une::fps::polynomial_inv_mod(factor, factor * Fps{2, 1});
    assert(!no_inverse.has_value());
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_randomized();

    int n, m;
    std::cin >> n >> m;
    Fps polynomial(n), modulus(m);
    for (mint& value : polynomial) std::cin >> value;
    for (mint& value : modulus) std::cin >> value;

    std::optional<Fps> inverse = m1une::fps::polynomial_inv_mod(polynomial, modulus);
    if (!inverse.has_value()) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::cout << inverse->size() << '\n';
    if (inverse->empty()) return 0;
    for (int i = 0; i < int(inverse->size()); i++) {
        if (i) std::cout << ' ';
        std::cout << (*inverse)[i];
    }
    std::cout << '\n';
}
