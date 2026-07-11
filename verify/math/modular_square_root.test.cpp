#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <cassert>
#include <cstdint>
#include <iostream>

#include "../../math/modint.hpp"
#include "../../math/modular_square_root.hpp"

namespace {

#ifndef NDEBUG
bool is_prime(uint64_t value) {
    if (value < 2) return false;
    for (uint64_t divisor = 2; divisor * divisor <= value; divisor++) {
        if (value % divisor == 0) return false;
    }
    return true;
}

void exhaustive_test() {
    for (uint64_t prime = 2; prime < 200; prime++) {
        if (!is_prime(prime)) continue;
        for (uint64_t value = 0; value < prime; value++) {
            bool exists = false;
            for (uint64_t root = 0; root < prime; root++) {
                if (root * root % prime == value) exists = true;
            }
            auto answer = m1une::math::modular_square_root(value, prime);
            assert(answer.has_value() == exists);
            if (answer.has_value()) assert(*answer * *answer % prime == value);
        }
    }

    using Mint = m1une::math::ModInt<17>;
    auto root = m1une::math::modular_square_root(Mint(13));
    assert(root.has_value());
    assert(*root * *root == Mint(13));
    assert(!m1une::math::modular_square_root(Mint(3)).has_value());
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
        uint64_t value, prime;
        std::cin >> value >> prime;
        auto root = m1une::math::modular_square_root(value, prime);
        if (root.has_value()) {
            std::cout << *root << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
}
