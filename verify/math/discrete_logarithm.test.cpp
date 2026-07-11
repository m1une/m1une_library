#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

#include "../../math/discrete_logarithm.hpp"

namespace {

#ifndef NDEBUG
std::optional<uint64_t> brute_discrete_logarithm(
    uint64_t base,
    uint64_t target,
    uint64_t mod
) {
    if (mod == 1) return uint64_t(0);
    base %= mod;
    target %= mod;
    uint64_t value = 1 % mod;
    std::vector<char> visited(mod, false);
    for (uint64_t exponent = 0; !visited[value]; exponent++) {
        if (value == target) return exponent;
        visited[value] = true;
        value = value * base % mod;
    }
    return std::nullopt;
}

void exhaustive_test() {
    for (uint64_t mod = 1; mod <= 180; mod++) {
        for (uint64_t base = 0; base < mod; base++) {
            for (uint64_t target = 0; target < mod; target++) {
                auto expected = brute_discrete_logarithm(base, target, mod);
                auto actual = m1une::math::discrete_logarithm(base, target, mod);
                assert(actual == expected);
            }
        }
    }

    assert(m1une::math::discrete_logarithm(2, 8, 13) == uint64_t(3));
    assert(m1une::math::discrete_logarithm(0, 1, 17) == uint64_t(0));
    assert(m1une::math::discrete_logarithm(0, 0, 17) == uint64_t(1));
    assert(m1une::math::discrete_logarithm(4, 2, 14) == uint64_t(2));
    assert(!m1une::math::discrete_logarithm(4, 3, 14).has_value());
    assert(m1une::math::discrete_logarithm(6, 0, 72) == uint64_t(3));
}
#endif

}  // namespace

int main() {
#ifndef NDEBUG
    exhaustive_test();
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int query_count;
    std::cin >> query_count;
    while (query_count--) {
        uint64_t base, target, mod;
        std::cin >> base >> target >> mod;
        auto answer = m1une::math::discrete_logarithm(base, target, mod);
        if (answer.has_value()) {
            std::cout << *answer << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
}
