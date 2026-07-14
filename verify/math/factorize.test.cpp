#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../math/prime_factorization.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        uint64_t value;
        fast_input >> value;
        std::vector<uint64_t> factors = m1une::math::prime_factors(value);
        fast_output << factors.size();
        for (uint64_t factor : factors) fast_output << ' ' << factor;
        fast_output << '\n';
    }
}
