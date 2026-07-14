#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cmath>
#include "../../../utilities/fast_io.hpp"

#include "../../../algo/search/ternary_search.hpp"

void test_integer_ternary_search() {
    auto convex = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    assert(m1une::algo::ternary_search_argmin<long long>(-100, 101, convex) == 7);

    auto plateau = [](int x) {
        if (x < 3) return 3 - x;
        if (5 < x) return x - 5;
        return 0;
    };
    assert(m1une::algo::ternary_search_argmin<int>(-10, 10, plateau) == 3);

    auto concave = [](int x) {
        return -(x + 2) * (x + 2) + 10;
    };
    assert(m1une::algo::ternary_search_argmax<int>(-20, 20, concave) == -2);
}

void test_real_ternary_search() {
    auto convex = [](double x) {
        return (x - 1.5) * (x - 1.5);
    };
    double xmin = m1une::algo::real_ternary_search_argmin(-10.0, 10.0, convex);
    assert(std::abs(xmin - 1.5) < 1e-9);

    auto concave = [](double x) {
        return -(x + 0.25) * (x + 0.25);
    };
    double xmax = m1une::algo::real_ternary_search_argmax(-10.0, 10.0, concave);
    assert(std::abs(xmax + 0.25) < 1e-9);
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_integer_ternary_search();
    test_real_ternary_search();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
