#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#include "../../utilities/fast_io.hpp"

#include "../../math/number_theory.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        long long n, mod, a, b;
        fast_input >> n >> mod >> a >> b;
        fast_output << m1une::math::floor_sum(n, mod, a, b) << '\n';
    }
}
