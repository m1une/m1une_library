#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/modint.hpp"
#include "../../math/repunit.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <numeric>
#include <optional>
#include <random>
#include <utility>

namespace {

template <class T>
T naive_repunit(std::uint64_t length, T base) {
    T result = T(0);
    for (std::uint64_t i = 0; i < length; i++) {
        result = result * base + T(1);
    }
    return result;
}

template <class T>
T power(T base, std::uint64_t exponent) {
    T result = T(1);
    while (exponent > 0) {
        if (exponent & 1) result = result * base;
        base = base * base;
        exponent >>= 1;
    }
    return result;
}

std::uint64_t naive_repunit_mod(
    std::uint64_t length,
    std::uint64_t base,
    std::uint64_t mod
) {
    std::uint64_t result = 0;
    for (std::uint64_t i = 0; i < length; i++) {
        result = (
            static_cast<unsigned __int128>(result) * base + 1
        ) % mod;
    }
    return result;
}

std::uint64_t naive_power_mod(
    std::uint64_t base,
    std::uint64_t exponent,
    std::uint64_t mod
) {
    std::uint64_t result = 1 % mod;
    for (std::uint64_t i = 0; i < exponent; i++) {
        result = static_cast<unsigned __int128>(result) * base % mod;
    }
    return result;
}

void fixed_tests() {
    using m1une::math::repunit;

    static_assert(repunit<unsigned long long>(0) == 0);
    static_assert(repunit<unsigned long long>(1) == 1);
    static_assert(repunit<unsigned long long>(3) == 111);
    static_assert(repunit<unsigned long long>(4, 2) == 15);
    static_assert(repunit<unsigned long long>(5, 1) == 5);
    static_assert(repunit<unsigned long long>(5, 0) == 1);
    static_assert(
        m1une::math::repdigit<unsigned long long>(3, 7) == 777
    );
    static_assert(
        m1une::math::concatenate_digits(12ULL, 34ULL, 2) == 1234
    );

    constexpr std::pair<unsigned long long, unsigned long long> block =
        m1une::math::repunit_and_power<unsigned long long>(3);
    static_assert(block.first == 111);
    static_assert(block.second == 1000);

    using CompositeMint = m1une::math::ModInt<1000>;
    assert(repunit<CompositeMint>(3).val() == 111);
    assert(repunit<CompositeMint>(30).val() == 111);

    using Mint = m1une::math::modint1000000007;
    constexpr std::uint64_t large_length = 1000000000000000000ULL;
    Mint left = repunit<Mint>(large_length);
    Mint half = repunit<Mint>(large_length / 2);
    Mint expected = half * power(Mint(10), large_length / 2) + half;
    assert(left == expected);

    assert(m1une::math::repunit_mod(30, 10, 1000) == 111);
    assert((
        m1une::math::repunit_and_power_mod(3, 10, 1000) ==
        std::pair<std::uint64_t, std::uint64_t>(111, 0)
    ));
    assert(m1une::math::repdigit_mod(3, 7, 10, 1000) == 777);
    assert(m1une::math::concatenate_digits_mod(12, 34, 2, 10, 1000) == 234);

    assert(m1une::math::minimum_repunit_length(1) == 1);
    assert(!m1une::math::minimum_repunit_length(2).has_value());
    assert(m1une::math::minimum_repunit_length(3) == 3);
    assert(m1une::math::minimum_repunit_length(7) == 6);
    assert(m1une::math::minimum_repunit_length(13) == 6);
    assert(m1une::math::minimum_repunit_length(27) == 27);
    assert(m1une::math::minimum_repunit_length(7, 2) == 3);
}

void exhaustive_tests() {
    using Mint = m1une::math::ModInt<1009>;
    for (int base = 0; base <= 50; base++) {
        for (int length = 0; length <= 500; length++) {
            assert(
                m1une::math::repunit<Mint>(length, Mint(base)) ==
                naive_repunit<Mint>(length, Mint(base))
            );
        }
    }
}

void runtime_modulus_tests() {
    std::mt19937_64 random(0x13198a2e03707344ULL);
    for (int trial = 0; trial < 30000; trial++) {
        const std::uint64_t mod = random() | 1;
        const std::uint64_t base = random();
        const std::uint64_t digit = random();
        const std::uint64_t length = random() % 200;
        const std::uint64_t expected = naive_repunit_mod(length, base, mod);
        assert(m1une::math::repunit_mod(length, base, mod) == expected);
        assert(
            m1une::math::repdigit_mod(length, digit, base, mod) ==
            static_cast<unsigned __int128>(digit % mod) * expected % mod
        );

        const std::uint64_t right_length = random() % 100;
        const std::uint64_t left = random();
        const std::uint64_t right = random();
        const std::uint64_t base_power =
            naive_power_mod(base, right_length, mod);
        const std::uint64_t concatenated = (
            static_cast<unsigned __int128>(left % mod) * base_power + right % mod
        ) % mod;
        assert(
            m1une::math::concatenate_digits_mod(
                left,
                right,
                right_length,
                base,
                mod
            ) == concatenated
        );
    }
}

void minimum_length_tests() {
    for (std::uint64_t base = 2; base <= 20; base++) {
        for (std::uint64_t divisor = 1; divisor <= 500; divisor++) {
            const std::optional<std::uint64_t> actual =
                m1une::math::minimum_repunit_length(divisor, base);
            if (std::gcd(base, divisor) != 1) {
                assert(!actual.has_value());
                continue;
            }

            assert(actual.has_value());
            assert(*actual <= divisor);
            assert(naive_repunit_mod(*actual, base, divisor) == 0);
            for (std::uint64_t length = 1; length < *actual; length++) {
                assert(naive_repunit_mod(length, base, divisor) != 0);
            }
        }
    }
}

void randomized_tests() {
    using Mint = m1une::math::modint998244353;
    std::mt19937_64 random(0x243f6a8885a308d3ULL);

    for (int trial = 0; trial < 100000; trial++) {
        const std::uint64_t first_length = random() % 1000000000000ULL;
        const std::uint64_t second_length = random() % 1000000000000ULL;
        const Mint base = Mint(random());

        const Mint first = m1une::math::repunit<Mint>(first_length, base);
        const Mint second = m1une::math::repunit<Mint>(second_length, base);
        const Mint combined = m1une::math::repunit<Mint>(
            first_length + second_length,
            base
        );
        assert(combined == first * power(base, second_length) + second);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    fixed_tests();
    exhaustive_tests();
    randomized_tests();
    runtime_modulus_tests();
    minimum_length_tests();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
