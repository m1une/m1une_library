#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../math/bernoulli.hpp"
#include "../../math/modint.hpp"

using Mint = m1une::math::modint998244353;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n;
    fast_input >> n;
    const std::vector<Mint> values = m1une::math::bernoulli_numbers<Mint>(n);
    for (int i = 0; i <= n; i++) {
        if (i) fast_output << ' ';
        fast_output << values[i];
    }
    fast_output << '\n';
}
