#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include "../../../utilities/fast_io.hpp"
#include <vector>

#include "../../../math/fps/multipoint_evaluation.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n;
    fast_input >> n;
    std::vector<mint> points(n), values(n);
    for (mint& point : points) fast_input >> point;
    for (mint& value : values) fast_input >> value;
    Fps result = m1une::fps::polynomial_interpolate(points, values);
    for (int i = 0; i < n; i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
