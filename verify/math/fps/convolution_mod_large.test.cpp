#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_large"

#pragma GCC optimize("O3")

#include <vector>

#include "../../../math/fps/convolution.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

using mint = m1une::math::modint998244353;

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0, m = 0;
    input.read(n, m);
    std::vector<mint> a(n), b(m);
    input.read(a);
    input.read(b);
    std::vector<mint> result = m1une::fps::convolution(a, b);
    output.println(result);
}
