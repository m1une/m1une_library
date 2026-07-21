#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../../math/fps/formal_power_series.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    using Fps = m1une::fps::FormalPowerSeries<mint>;

    int size;
    fast_input >> size;
    Fps series(size);
    for (mint& coefficient : series) fast_input >> coefficient;
    auto result = series.sqrt();
    if (!result.has_value()) {
        fast_output << -1 << '\n';
        return 0;
    }
    for (int index = 0; index < size; index++) {
        if (index != 0) fast_output << ' ';
        fast_output << (*result)[index];
    }
    fast_output << '\n';
}
