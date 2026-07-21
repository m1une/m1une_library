#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "../../math/divisor_convolution.hpp"
#include "../../math/modint.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

template <typename T>
std::vector<T> naive_gcd_convolution(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    if (first.empty() || second.empty()) return {};
    const std::size_t size = first.size() > second.size()
        ? first.size()
        : second.size();
    std::vector<T> result(size);
    for (std::size_t i = 1; i < first.size(); ++i) {
        for (std::size_t j = 1; j < second.size(); ++j) {
            result[std::gcd(i, j)] += first[i] * second[j];
        }
    }
    return result;
}

template <typename T>
std::vector<T> naive_lcm_convolution(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    if (first.empty() || second.empty()) return {};
    const std::size_t size = first.size() > second.size()
        ? first.size()
        : second.size();
    std::vector<T> result(size);
    for (std::size_t i = 1; i < first.size(); ++i) {
        for (std::size_t j = 1; j < second.size(); ++j) {
            const std::size_t index = std::lcm(i, j);
            if (index < size) result[index] += first[i] * second[j];
        }
    }
    return result;
}

template <typename T>
void check(
    const std::vector<T>& first,
    const std::vector<T>& second
) {
    assert(
        m1une::math::gcd_convolution(first, second) ==
        naive_gcd_convolution(first, second)
    );
    assert(
        m1une::math::lcm_convolution(first, second) ==
        naive_lcm_convolution(first, second)
    );
}

void test_edge_cases() {
    check(std::vector<long long>(), std::vector<long long>());
    check(std::vector<long long>(), std::vector<long long>{7, 3});
    check(std::vector<long long>{5}, std::vector<long long>{-2});
    check(
        std::vector<long long>{99, 1, 2, 3},
        std::vector<long long>{-99, 4, 5}
    );
}

void test_randomized() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        const std::size_t first_size = random() % 20;
        const std::size_t second_size = random() % 20;
        std::vector<long long> first(first_size);
        std::vector<long long> second(second_size);
        for (long long& value : first) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        for (long long& value : second) {
            value = static_cast<long long>(random() % 21) - 10;
        }
        check(first, second);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();

    int n;
    fast_input >> n;
    using mint = m1une::math::modint998244353;
    std::vector<mint> first(n + 1), second(n + 1);
    for (int index = 1; index <= n; ++index) {
        long long value;
        fast_input >> value;
        first[index] = value;
    }
    for (int index = 1; index <= n; ++index) {
        long long value;
        fast_input >> value;
        second[index] = value;
    }

    std::vector<mint> result =
        m1une::math::gcd_convolution(first, second);
    for (int index = 1; index <= n; ++index) {
        if (index != 1) fast_output << ' ';
        fast_output << result[index].val();
    }
    fast_output << '\n';
}
