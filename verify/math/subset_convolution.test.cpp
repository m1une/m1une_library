#define PROBLEM "https://judge.yosupo.jp/problem/subset_convolution"

#include "../../math/modint.hpp"
#include "../../math/subset_convolution.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

template <typename T>
std::vector<T> naive_subset_convolution(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    assert(first.size() == second.size());
    std::vector<T> result(first.size());
    for (std::size_t mask = 0; mask < first.size(); ++mask) {
        std::size_t submask = mask;
        while (true) {
            result[mask] += first[submask] * second[mask ^ submask];
            if (submask == 0) break;
            submask = (submask - 1) & mask;
        }
    }
    return result;
}

void test_edge_cases() {
    std::vector<long long> empty;
    assert(m1une::math::subset_convolution(empty, empty).empty());

    std::vector<long long> first{7};
    std::vector<long long> second{-3};
    std::vector<long long> expected{-21};
    assert(m1une::math::subset_convolution(first, second) == expected);
}

void test_randomized() {
    std::uint64_t state = 0x72ad4f19c6e3b805ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; ++trial) {
        int bit_count = int(random() % 8);
        std::size_t size = std::size_t(1) << bit_count;
        std::vector<long long> first(size), second(size);
        for (long long& value : first) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        for (long long& value : second) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        assert(
            m1une::math::subset_convolution(first, second) ==
            naive_subset_convolution(first, second)
        );
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();

    int bit_count;
    fast_input >> bit_count;
    int size = 1 << bit_count;
    using mint = m1une::math::modint998244353;
    std::vector<mint> first(size), second(size);
    for (mint& value : first) {
        long long input;
        fast_input >> input;
        value = input;
    }
    for (mint& value : second) {
        long long input;
        fast_input >> input;
        value = input;
    }

    std::vector<mint> result =
        m1une::math::subset_convolution(first, second);
    for (int mask = 0; mask < size; ++mask) {
        if (mask != 0) fast_output << ' ';
        fast_output << result[mask].val();
    }
    fast_output << '\n';
}
