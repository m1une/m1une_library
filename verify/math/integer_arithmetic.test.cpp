#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../../math/integer_arithmetic.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

namespace {

template <class T>
void test_square_roots() {
    using U = std::make_unsigned_t<T>;
    U limit = std::min<U>(std::numeric_limits<T>::max(), U(100000));
    for (U value = 0;; ++value) {
        T input = static_cast<T>(value);
        [[maybe_unused]] T floor = m1une::math::isqrt(input);
        [[maybe_unused]] T ceiling = m1une::math::ceil_sqrt(input);
        assert(floor <= input / (floor == 0 ? 1 : floor));
        assert(floor == 0 || floor + 1 > input / (floor + 1));
        assert(ceiling == floor || ceiling == floor + 1);
        assert(
            ceiling == floor
            ? floor * floor == input
            : floor * floor < input
        );
        if (value == limit) break;
    }
}

void test_boundaries() {
    constexpr std::uint64_t maximum =
        std::numeric_limits<std::uint64_t>::max();
    constexpr std::uint64_t root = 4294967295ULL;
    static_assert(m1une::math::isqrt(maximum) == root);
    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);
    static_assert(m1une::math::isqrt(root * root) == root);

    constexpr long long signed_maximum =
        std::numeric_limits<long long>::max();
    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);
    static_assert(m1une::math::ceil_sqrt(signed_maximum) == 3037000500LL);
}

void test_kth_roots() {
    using m1une::math::checked_ipow;
    using m1une::math::floor_kth_root;
    constexpr std::uint64_t maximum =
        std::numeric_limits<std::uint64_t>::max();

    static_assert(floor_kth_root(0ULL, 1) == 0);
    static_assert(floor_kth_root(1ULL, 64) == 1);
    static_assert(floor_kth_root(7ULL, 3) == 1);
    static_assert(floor_kth_root(8ULL, 3) == 2);
    static_assert(floor_kth_root(80ULL, 4) == 2);
    static_assert(floor_kth_root(81ULL, 4) == 3);
    static_assert(floor_kth_root(maximum, 1) == maximum);
    static_assert(floor_kth_root(maximum, 2) == 4294967295ULL);
    static_assert(floor_kth_root(maximum, 3) == 2642245ULL);
    static_assert(floor_kth_root(maximum, 64) == 1);
    static_assert(
        floor_kth_root(std::numeric_limits<long long>::max(), 3U)
        == 2097151LL
    );

    for (std::uint64_t value = 0; value <= 10000; value++) {
        for (unsigned degree = 1; degree <= 16; degree++) {
            std::uint64_t root = floor_kth_root(value, degree);
            std::optional<std::uint64_t> power = checked_ipow(root, degree);
            assert(power.has_value() && *power <= value);

            std::optional<std::uint64_t> next_power =
                checked_ipow(root + 1, degree);
            assert(!next_power.has_value() || value < *next_power);
        }
    }
}

void test_powers() {
    using m1une::math::checked_ipow;
    using m1une::math::ipow;

    static_assert(ipow(0LL, 0U) == 1);
    static_assert(ipow(2LL, 10U) == 1024);
    static_assert(ipow(-3LL, 3U) == -27);
    static_assert(ipow(-3LL, 4U) == 81);
    static_assert(
        ipow(-2LL, 63U) == std::numeric_limits<long long>::min()
    );
    static_assert(!checked_ipow(2LL, 63U).has_value());
    static_assert(!checked_ipow(-2LL, 64U).has_value());
    static_assert(!checked_ipow(10ULL, 20U).has_value());
    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));
    static_assert(
        checked_ipow(std::numeric_limits<long long>::min(), 1U)
        == std::optional(std::numeric_limits<long long>::min())
    );
    static_assert(
        !checked_ipow(std::numeric_limits<long long>::min(), 2U).has_value()
    );

    for (long long base = -20; base <= 20; ++base) {
        [[maybe_unused]] long long expected = 1;
        for (unsigned exponent = 0; exponent <= 8; ++exponent) {
            assert(ipow(base, exponent) == expected);
            expected *= base;
        }
    }
}

}  // namespace

int main() {
    test_square_roots<signed char>();
    test_square_roots<unsigned char>();
    test_square_roots<short>();
    test_square_roots<unsigned short>();
    test_square_roots<int>();
    test_square_roots<unsigned int>();
    test_square_roots<long long>();
    test_square_roots<unsigned long long>();
    test_boundaries();
    test_kth_roots();
    test_powers();

    int test_count;
    std::cin >> test_count;
    while (test_count--) {
        std::uint64_t value;
        int degree;
        std::cin >> value >> degree;
        std::cout << m1une::math::floor_kth_root(value, degree) << '\n';
    }
}
