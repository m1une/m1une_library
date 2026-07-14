#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse"

#include "../../../utilities/fast_io.hpp"

#include "../../../math/fps/sparse_formal_power_series.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Sparse = m1une::fps::SparseFormalPowerSeries<mint>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, k;
    fast_input >> n >> k;
    Sparse f(k);
    for (auto& [degree, coefficient] : f) fast_input >> degree >> coefficient;
    auto result = m1une::fps::sparse_fps_log(f, n);
    for (int i = 0; i < n; i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
