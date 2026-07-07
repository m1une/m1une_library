#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../algo/enumeration/gray_code.hpp"

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

namespace {

template <class UInt>
constexpr UInt naive_gray_decode(UInt code) {
    UInt value = 0;
    for (; code != 0; code >>= 1) value ^= code;
    return value;
}

void fixed_tests() {
    using m1une::algo::gray_decode;
    using m1une::algo::gray_encode;

    static_assert(gray_encode(std::uint32_t(0)) == 0);
    static_assert(gray_encode(std::uint32_t(1)) == 1);
    static_assert(gray_encode(std::uint32_t(2)) == 3);
    static_assert(gray_encode(std::uint32_t(7)) == 4);
    static_assert(gray_decode(std::uint32_t(0)) == 0);
    static_assert(gray_decode(std::uint32_t(4)) == 7);
    static_assert(gray_decode(gray_encode(
        std::numeric_limits<std::uint64_t>::max()
    )) == std::numeric_limits<std::uint64_t>::max());

    const std::vector<std::uint64_t> expected = {0, 1, 3, 2, 6, 7, 5, 4};
    assert(m1une::algo::gray_code_sequence(3) == expected);
    assert(m1une::algo::gray_code_sequence(0) ==
           std::vector<std::uint64_t>({0}));

    const std::vector<std::uint8_t> byte_codes =
        m1une::algo::gray_code_sequence<std::uint8_t>(8);
    assert(byte_codes.size() == 256);
    for (int value = 0; value < 256; ++value) {
        assert(gray_decode(byte_codes[value]) == value);
    }
}

void exhaustive_tests() {
    using m1une::algo::gray_decode;
    using m1une::algo::gray_encode;

    for (std::uint32_t value = 0; value < (std::uint32_t(1) << 16); ++value) {
        const std::uint32_t code = gray_encode(value);
        assert(gray_decode(code) == value);
        assert(gray_decode(code) == naive_gray_decode(code));
    }

    for (int bit_count = 0; bit_count <= 16; ++bit_count) {
        std::vector<std::uint32_t> codes =
            m1une::algo::gray_code_sequence<std::uint32_t>(bit_count);
        assert(codes.size() == (std::size_t(1) << bit_count));
        for (std::size_t index = 0; index < codes.size(); ++index) {
            assert(
                codes[index] ==
                gray_encode(static_cast<std::uint32_t>(index))
            );
            if (index != 0) {
                assert(std::has_single_bit(codes[index] ^ codes[index - 1]));
            }
        }
        if (bit_count != 0) {
            assert(std::has_single_bit(codes.front() ^ codes.back()));
        }

        std::sort(codes.begin(), codes.end());
        for (std::size_t index = 0; index < codes.size(); ++index) {
            assert(codes[index] == index);
        }
    }
}

void randomized_tests() {
    std::mt19937_64 random(0x6a09e667f3bcc909ULL);
    for (int trial = 0; trial < 100000; ++trial) {
        const std::uint64_t value = random();
        const std::uint64_t code = m1une::algo::gray_encode(value);
        assert(m1une::algo::gray_decode(code) == value);
        assert(m1une::algo::gray_decode(code) == naive_gray_decode(code));
    }
}

}  // namespace

int main() {
    fixed_tests();
    exhaustive_tests();
    randomized_tests();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
