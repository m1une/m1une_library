#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../../utilities/fast_io.hpp"
#include <vector>

#include "../../../math/fps/multipoint_evaluation.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, m;
    fast_input >> n >> m;
    Fps polynomial(n);
    std::vector<mint> points(m);
    for (mint& value : polynomial) fast_input >> value;
    for (mint& point : points) fast_input >> point;
    std::vector<mint> result = m1une::fps::multipoint_evaluate(polynomial, points);
    for (int i = 0; i < m; i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
