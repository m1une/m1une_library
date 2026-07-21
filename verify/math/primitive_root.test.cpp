#define PROBLEM "https://judge.yosupo.jp/problem/primitive_root"

#include "../../math/primitive_root.hpp"
#include "../../utilities/fast_io.hpp"

#include <cstdint>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        std::uint64_t prime;
        fast_input >> prime;
        fast_output << m1une::math::primitive_root(prime) << '\n';
    }
}
