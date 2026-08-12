#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/rational.hpp"
#include "../../utilities/bigint.hpp"

#include <cassert>
#include <compare>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <limits>
#include <sstream>

namespace {

using Fraction = m1une::math::Rational<long long>;
using BigInt = m1une::utilities::BigInt;
using BigFraction = m1une::math::Rational<BigInt>;

void test_fixed() {
    constexpr Fraction zero;
    constexpr Fraction half(2, 4);
    constexpr Fraction negative(3, -6);
    static_assert(zero.numerator() == 0);
    static_assert(zero.denominator() == 1);
    static_assert(half == Fraction(1, 2));
    static_assert(negative == Fraction(-1, 2));
    static_assert(half + negative == 0);
    static_assert(Fraction(2, 3) + Fraction(5, 6) == Fraction(3, 2));
    static_assert(Fraction(2, 3) * Fraction(9, 4) == Fraction(3, 2));
    static_assert(Fraction(2, 3) / Fraction(4, 9) == Fraction(3, 2));
    static_assert(Fraction(-7, 3).floor() == -3);
    static_assert(Fraction(-7, 3).ceil() == -2);
    static_assert(Fraction(-7, 3).trunc() == -2);
    static_assert(Fraction(1, 3) < Fraction(1, 2));
    static_assert(m1une::math::abs(Fraction(-3, 4)) == Fraction(3, 4));

    [[maybe_unused]] Fraction large(
        std::numeric_limits<long long>::max(),
        std::numeric_limits<long long>::max() - 1
    );
    assert(large > 1);

    std::stringstream stream;
    stream << Fraction(-6, 8) << ' ' << Fraction(5);
    assert(stream.str() == "-3/4 5");
    Fraction first;
    Fraction second;
    stream.seekg(0);
    stream >> first >> second;
    assert(first == Fraction(-3, 4));
    assert(second == 5);
}

void test_randomized() {
    std::uint64_t state = 1301;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 100000; ++trial) {
        long long a = static_cast<long long>(random() % 2001) - 1000;
        long long b = 1 + static_cast<long long>(random() % 1000);
        long long c = static_cast<long long>(random() % 2001) - 1000;
        long long d = 1 + static_cast<long long>(random() % 1000);
        Fraction first(a, b);
        Fraction second(c, d);

        [[maybe_unused]] __int128_t left = __int128_t(a) * d;
        [[maybe_unused]] __int128_t right = __int128_t(c) * b;
        assert((first <=> second) == (left <=> right));

        [[maybe_unused]] Fraction sum = first + second;
        assert(
            __int128_t(sum.numerator()) * b * d
            == (__int128_t(a) * d + __int128_t(c) * b)
                * sum.denominator()
        );

        [[maybe_unused]] Fraction product = first * second;
        assert(
            __int128_t(product.numerator()) * b * d
            == __int128_t(a) * c * product.denominator()
        );

        if (c != 0) {
            [[maybe_unused]] Fraction quotient = first / second;
            assert(
                __int128_t(quotient.numerator()) * b * c
                == __int128_t(a) * d * quotient.denominator()
            );
        }
    }
}

void test_bigint() {
    BigInt power = 1;
    for (int i = 0; i < 100; ++i) power *= 10;

    BigFraction reduced(power * 6, power * 8);
    assert(reduced == BigFraction(3, 4));
    assert(reduced.numerator() == 3);
    assert(reduced.denominator() == 4);

    BigFraction large(power, 3);
    BigFraction inverse(3, power);
    assert(large * inverse == 1);
    assert(large > inverse);
    assert(large + BigFraction(1, 3) == BigFraction(power + 1, 3));
    assert(large / large == 1);

    BigFraction negative(-(power + 1), power);
    assert(negative.floor() == -2);
    assert(negative.ceil() == -1);
    assert(negative.trunc() == -1);
    assert(negative.sign() == -1);
    assert(abs(negative) == -negative);

    BigFraction integer = 5;
    assert(integer + 1 == 6);
    assert(BigFraction(1, 2).to_long_double() == 0.5L);
    long double near_two_thirds =
        BigFraction(power * 2 + 1, power * 3 + 1).to_long_double();
    assert(0.66L < near_two_thirds && near_two_thirds < 0.67L);

    std::stringstream stream;
    stream << large;
    BigFraction parsed;
    stream >> parsed;
    assert(parsed == large);

    std::uint64_t state = 2309;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto assert_same = [](const BigFraction& big, const Fraction& small) {
        assert(big.numerator().to_string() == std::to_string(small.numerator()));
        assert(big.denominator().to_string() == std::to_string(small.denominator()));
    };
    for (int trial = 0; trial < 10000; ++trial) {
        long long a = static_cast<long long>(random() % 2001) - 1000;
        long long b = 1 + static_cast<long long>(random() % 1000);
        long long c = static_cast<long long>(random() % 2001) - 1000;
        long long d = 1 + static_cast<long long>(random() % 1000);
        BigFraction big_first = BigFraction(BigInt(a), BigInt(b));
        BigFraction big_second = BigFraction(BigInt(c), BigInt(d));
        Fraction small_first(a, b);
        Fraction small_second(c, d);
        assert_same(big_first + big_second, small_first + small_second);
        assert_same(big_first - big_second, small_first - small_second);
        assert_same(big_first * big_second, small_first * small_second);
        assert((big_first <=> big_second) == (small_first <=> small_second));
        if (c != 0) {
            assert_same(big_first / big_second, small_first / small_second);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    test_bigint();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
