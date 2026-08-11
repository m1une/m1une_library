#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../math/fps/solve_fps_equation.hpp"
#include "../../math/modint.hpp"
#include "../../math/newton_method.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <random>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

namespace {

void test_floating_point() {
    auto function = [](double value) {
        return value * value - 2.0;
    };
    auto derivative = [](double value) {
        return 2.0 * value;
    };
    double root = m1une::math::newton_method(
        1.0, function, derivative, 8
    );
    assert(std::abs(root - std::sqrt(2.0)) < 1e-12);

    assert(m1une::math::newton_method(
        3.0, function, derivative, 0
    ) == 3.0);
}

void test_custom_quotient() {
    int quotient_calls = 0;
    auto function = [](double value) {
        return value - 5.0;
    };
    auto derivative = [](double) {
        return 1.0;
    };
    auto quotient = [&](double numerator, double denominator) {
        quotient_calls++;
        return numerator / denominator;
    };
    double root = m1une::math::newton_method(
        0.0, function, derivative, 4, quotient
    );
    assert(root == 5.0);
    assert(quotient_calls == 4);
}

void test_formal_power_series() {
    std::mt19937 random(123456789);
    for (int degree = 1; degree <= 64; degree++) {
        Fps expected(degree);
        expected[0] = 1;
        for (int i = 1; i < degree; i++) expected[i] = mint(random());
        Fps target = (expected * expected).pre(degree);

        auto function = [&](const Fps& value, int precision) {
            return (value * value).pre(precision) - target.pre(precision);
        };
        auto derivative = [](const Fps& value, int precision) {
            return (value * mint(2)).pre(precision);
        };

        Fps actual;
        if (degree % 2 == 0) {
            const int known = std::min(degree, 3);
            actual = m1une::fps::solve_fps_equation(
                expected.pre(known), degree, function, derivative
            );
        } else {
            actual = m1une::fps::solve_fps_equation(
                degree, mint(1), function, derivative
            );
        }
        assert(actual == expected);
    }
}

void solve_library_checker() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size;
    fast_input >> size;
    Fps series(size);
    for (mint& coefficient : series) fast_input >> coefficient;

    int first = 0;
    while (first < size && series[first] == mint(0)) first++;
    if (first == size) {
        for (int i = 0; i < size; i++) {
            if (i != 0) fast_output << ' ';
            fast_output << 0;
        }
        fast_output << '\n';
        return;
    }
    if (first & 1) {
        fast_output << -1 << '\n';
        return;
    }

    auto leading_root = m1une::math::modular_square_root(series[first]);
    if (!leading_root.has_value()) {
        fast_output << -1 << '\n';
        return;
    }

    Fps target = series >> first;
    const int degree = int(target.size());
    auto function = [&](const Fps& value, int precision) {
        Fps truncated = value.pre(precision);
        return (truncated * truncated).pre(precision) - target.pre(precision);
    };
    auto derivative = [](const Fps& value, int precision) {
        return value.pre(precision) * mint(2);
    };
    Fps result = m1une::fps::solve_fps_equation(
        degree, *leading_root, function, derivative
    );
    result <<= first / 2;
    result.resize(size);

    for (int i = 0; i < size; i++) {
        if (i != 0) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}

}  // namespace

int main() {
    test_floating_point();
    test_custom_quotient();
    test_formal_power_series();
    solve_library_checker();
}
