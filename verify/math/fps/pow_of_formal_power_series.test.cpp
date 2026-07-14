#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include <cstdint>
#include "../../../utilities/fast_io.hpp"

#include "../../../math/fps/formal_power_series.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n;
    long long exponent;
    fast_input >> n >> exponent;
    Fps a(n);
    for (mint& value : a) fast_input >> value;
    Fps result = a.pow(exponent);
    for (int i = 0; i < n; i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
