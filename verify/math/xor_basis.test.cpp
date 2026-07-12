#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/xor_basis.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

namespace {

using Basis = m1une::math::XorBasis<uint64_t>;

std::vector<uint64_t> enumerate(const std::vector<uint64_t>& values) {
    std::vector<uint64_t> result;
    result.reserve(std::size_t(1) << values.size());
    for (uint64_t mask = 0; mask < (uint64_t(1) << values.size()); mask++) {
        uint64_t value = 0;
        for (int i = 0; i < int(values.size()); i++) {
            if (((mask >> i) & 1) != 0) value ^= values[i];
        }
        result.push_back(value);
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

void test_basic() {
    Basis basis{3, 5, 6, 0};
    assert(basis.rank() == 2);
    assert(!basis.empty());
    assert(basis.contains(0));
    assert(basis.contains(3));
    assert(basis.contains(5));
    assert(basis.contains(6));
    assert(!basis.contains(1));
    assert(!basis.insert(6));
    assert(basis.min_xor(4) == 1);
    assert(basis.max_xor() == 6);
    assert(basis.max_xor(8) == 14);

    const std::vector<uint64_t> expected{0, 3, 5, 6};
    for (uint64_t i = 0; i < expected.size(); i++) {
        assert(basis.kth_smallest(i) == expected[i]);
    }

    Basis other{1, 8, 9};
    assert(basis.merge(other) == 2);
    assert(basis.rank() == 4);
    assert(basis.contains(15));
    basis.clear();
    assert(basis.empty());
    assert(basis.vectors().empty());
}

void test_randomized() {
    std::mt19937_64 random(123456789);
    for (int trial = 0; trial < 2000; trial++) {
        const int size = int(random() % 11);
        std::vector<uint64_t> values(size);
        for (uint64_t& value : values) value = random() & 1023;

        Basis basis(values.begin(), values.end());
        const std::vector<uint64_t> span = enumerate(values);
        assert(span.size() == (std::size_t(1) << basis.rank()));
        assert(int(basis.vectors().size()) == basis.rank());

        for (uint64_t value = 0; value < 1024; value++) {
            const bool expected = std::binary_search(span.begin(), span.end(), value);
            assert(basis.contains(value) == expected);
        }
        for (std::size_t i = 0; i < span.size(); i++) {
            assert(basis.kth_smallest(i) == span[i]);
        }

        for (int query = 0; query < 20; query++) {
            const uint64_t seed = random() & 2047;
            uint64_t expected_min = ~uint64_t(0);
            uint64_t expected_max = 0;
            for (uint64_t value : span) {
                expected_min = std::min(expected_min, seed ^ value);
                expected_max = std::max(expected_max, seed ^ value);
            }
            assert(basis.min_xor(seed) == expected_min);
            assert(basis.max_xor(seed) == expected_max);
        }
    }
}

void test_full_rank() {
    m1une::math::XorBasis<uint8_t> basis;
    for (int bit = 0; bit < 8; bit++) basis.insert(uint8_t(1U << bit));
    assert(basis.rank() == 8);
    for (int value = 0; value < 256; value++) {
        assert(basis.kth_smallest(uint8_t(value)) == uint8_t(value));
    }
}

}  // namespace

int main() {
    test_basic();
    test_randomized();
    test_full_rank();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
