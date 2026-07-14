#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include <cstdint>
#include "../../utilities/fast_io.hpp"

#include "../../math/prime_factorization.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        uint64_t value;
        fast_input >> value;
        fast_output << (m1une::math::is_prime(value) ? "Yes" : "No") << '\n';
    }
}
