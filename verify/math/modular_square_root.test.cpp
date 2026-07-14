#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"

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
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    exhaustive_test();
#endif
    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        uint64_t value, prime;
        fast_input >> value >> prime;
        auto root = m1une::math::modular_square_root(value, prime);
        if (root.has_value()) {
            fast_output << *root << '\n';
        } else {
            fast_output << -1 << '\n';
        }
    }
}
