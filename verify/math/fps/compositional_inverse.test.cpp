#define PROBLEM "https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series_large"

#include <cassert>
#include "../../../utilities/fast_io.hpp"
#include <random>

#include "../../../math/fps/compositional_inverse.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using mint1e9 = m1une::math::modint1000000007;
using Fps = m1une::fps::FormalPowerSeries<mint>;

template <class Mint>
m1une::fps::FormalPowerSeries<Mint> naive_compose(
    const m1une::fps::FormalPowerSeries<Mint>& outer,
    const m1une::fps::FormalPowerSeries<Mint>& inner, int degree) {
    using Series = m1une::fps::FormalPowerSeries<Mint>;
    Series result(degree);
    Series power(degree);
    if (degree > 0) power[0] = 1;
    for (int i = 0; i < int(outer.size()) && i < degree; i++) {
        for (int j = 0; j < degree; j++) result[j] += outer[i] * power[j];
        power = m1une::fps::convolution_naive<Mint>(power, inner);
        power.resize(degree);
    }
    return result;
}

template <class Mint>
m1une::fps::FormalPowerSeries<Mint> naive_compositional_inverse(
    const m1une::fps::FormalPowerSeries<Mint>& f, int degree) {
    using Series = m1une::fps::FormalPowerSeries<Mint>;
    Series result(degree);
    if (degree <= 1) return result;
    result[1] = f[1].inv();
    for (int i = 2; i < degree; i++) {
        result[i] = Mint(0);
        Series composed = naive_compose(f.pre(i + 1), result, i + 1);
        result[i] = (Mint(0) - composed[i]) / f[1];
    }
    return result;
}

template <class Mint>
void assert_identity(const m1une::fps::FormalPowerSeries<Mint>& f,
                     const m1une::fps::FormalPowerSeries<Mint>& inverse, int degree) {
    using Series = m1une::fps::FormalPowerSeries<Mint>;
    Series identity(degree);
    if (degree > 1) identity[1] = 1;
    assert(naive_compose(f, inverse, degree) == identity);
    assert(naive_compose(inverse, f, degree) == identity);
}

void randomized_test() {
    std::mt19937 rng(314159265);
    for (int iteration = 0; iteration < 80; iteration++) {
        const int degree = int(rng() % 28) + 2;
        Fps f(degree);
        f[0] = 0;
        do {
            f[1] = mint(rng());
        } while (f[1] == mint(0));
        for (int i = 2; i < degree; i++) f[i] = mint(rng());

        Fps inverse = m1une::fps::compositional_inverse(f);
        assert(inverse == naive_compositional_inverse(f, degree));
        assert_identity(f, inverse, degree);
    }

    using Fps1e9 = m1une::fps::FormalPowerSeries<mint1e9>;
    Fps1e9 f(48);
    f[1] = 7;
    for (int i = 2; i < int(f.size()); i++) f[i] = mint1e9(rng());
    Fps1e9 inverse = m1une::fps::compositional_inverse(f);
    assert(inverse == naive_compositional_inverse(f, int(f.size())));
    assert_identity(f, inverse, int(f.size()));
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    randomized_test();

    int n;
    fast_input >> n;
    Fps f(n);
    for (mint& value : f) fast_input >> value;

    Fps result = m1une::fps::compositional_inverse(f);
    for (int i = 0; i < n; i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
