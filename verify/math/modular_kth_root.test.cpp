#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_mod"

#include "../../math/modular_kth_root.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

#include "../../math/modint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t mod) {
    uint64_t result = 1 % mod;
    while (exponent != 0) {
        if (exponent & 1) {
            result = static_cast<uint64_t>(
                static_cast<__uint128_t>(result) * base % mod
            );
        }
        base = static_cast<uint64_t>(
            static_cast<__uint128_t>(base) * base % mod
        );
        exponent >>= 1;
    }
    return result;
}

bool is_prime(uint64_t value) {
    if (value < 2) return false;
    for (uint64_t divisor = 2; divisor <= value / divisor; divisor++) {
        if (value % divisor == 0) return false;
    }
    return true;
}

void test_exhaustive() {
    for (uint64_t prime = 2; prime <= 47; prime++) {
        if (!is_prime(prime)) continue;
        for (uint64_t degree = 0; degree <= 2 * prime; degree++) {
            std::vector<bool> exists(prime, false);
            for (uint64_t root = 0; root < prime; root++) {
                exists[power_mod(root, degree, prime)] = true;
            }
            for (uint64_t value = 0; value < prime; value++) {
                auto root = m1une::math::modular_kth_root(
                    value, degree, prime
                );
                assert(root.has_value() == exists[value]);
                if (root.has_value()) {
                    assert(*root < prime);
                    assert(power_mod(*root, degree, prime) == value);
                }
            }
        }
    }

    using Mint = m1une::math::ModInt<13>;
    auto root = m1une::math::modular_kth_root(Mint(8), 3);
    assert(root.has_value());
    assert(root->pow(3) == Mint(8));
    assert(!m1une::math::modular_kth_root(Mint(2), 4).has_value());
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_exhaustive();

    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        uint64_t degree, value, prime;
        fast_input >> degree >> value >> prime;
        auto root = m1une::math::modular_kth_root(value, degree, prime);
        if (root.has_value()) {
            fast_output << *root << '\n';
        } else {
            fast_output << -1 << '\n';
        }
    }
}
