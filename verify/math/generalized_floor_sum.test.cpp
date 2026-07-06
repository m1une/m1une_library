#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/generalized_floor_sum.hpp"
#include "../../math/modint.hpp"
#include "../../math/number_theory.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>

using Mint = m1une::math::modint998244353;

long long floor_div(long long numerator, long long denominator) {
    long long quotient = numerator / denominator;
    if (numerator % denominator < 0) --quotient;
    return quotient;
}

template <class T, int MaxPower, int MaxFloorPower>
auto naive(long long n, long long mod, long long a, long long b) {
    m1une::math::GeneralizedFloorSumTable<
        T,
        MaxPower,
        MaxFloorPower
    > result{};
    for (long long x = 0; x < n; ++x) {
        long long y = floor_div(a * x + b, mod);
        T x_power = T(1);
        for (int p = 0; p <= MaxPower; ++p) {
            T y_power = T(1);
            for (int q = 0; q <= MaxFloorPower; ++q) {
                result[p][q] += x_power * y_power;
                y_power *= T(y);
            }
            x_power *= T(x);
        }
    }
    return result;
}

void test_fixed_cases() {
    auto count_only =
        m1une::math::generalized_floor_sum_table<Mint, 0, 0>(12, 1, -5, -8);
    assert(count_only[0][0] == Mint(12));

    auto empty =
        m1une::math::generalized_floor_sum_table<Mint, 3, 3>(0, 7, 2, 3);
    for (const auto& row : empty) {
        for (Mint value : row) assert(value == Mint(0));
    }

    auto actual =
        m1une::math::generalized_floor_sum_table<Mint, 4, 4>(20, 11, -7, -9);
    auto expected = naive<Mint, 4, 4>(20, 11, -7, -9);
    assert(actual == expected);

    Mint moment =
        m1une::math::generalized_floor_sum<Mint, 3, 2>(20, 11, -7, -9);
    assert(moment == expected[3][2]);

    auto unsigned_actual =
        m1une::math::generalized_floor_sum_table<std::uint64_t, 3, 3>(
            30,
            17,
            23,
            -41
        );
    auto unsigned_expected = naive<std::uint64_t, 3, 3>(30, 17, 23, -41);
    assert(unsigned_actual == unsigned_expected);

    long long ordinary = m1une::math::floor_sum(1000000, 998244353, 123456, -789);
    Mint generalized =
        m1une::math::generalized_floor_sum<Mint, 0, 1>(
            1000000,
            998244353,
            123456,
            -789
        );
    assert(generalized == Mint(ordinary));
}

void test_randomized_against_naive() {
    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int test = 0; test < 5000; ++test) {
        long long n = static_cast<long long>(random() % 25);
        long long mod = 1 + static_cast<long long>(random() % 20);
        long long a = static_cast<long long>(random() % 101) - 50;
        long long b = static_cast<long long>(random() % 101) - 50;

        auto actual =
            m1une::math::generalized_floor_sum_table<Mint, 4, 4>(
                n,
                mod,
                a,
                b
            );
        auto expected = naive<Mint, 4, 4>(n, mod, a, b);
        assert(actual == expected);
    }
}

int main() {
    test_fixed_cases();
    test_randomized_against_naive();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
