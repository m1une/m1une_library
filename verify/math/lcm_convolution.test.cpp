#define PROBLEM "https://judge.yosupo.jp/problem/lcm_convolution"

#include "../../math/divisor_convolution.hpp"
#include "../../math/modint.hpp"

#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

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
        m1une::math::lcm_convolution(first, second);
    for (int index = 1; index <= n; ++index) {
        if (index != 1) fast_output << ' ';
        fast_output << result[index].val();
    }
    fast_output << '\n';
}
