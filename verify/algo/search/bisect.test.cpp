#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cmath>
#include "../../../utilities/fast_io.hpp"

#include "../../../algo/search/bisect.hpp"

void test_bisect() {
    long long n = 100;
    long long first = m1une::algo::first_true(0, n + 1, [&](long long x) {
        return x * x >= n;
    });
    assert(first == 10);

    long long last = m1une::algo::last_true(n + 1, 0, [&](long long x) {
        return x * x >= n;
    });
    assert(last == 10);

    double root = m1une::algo::real_first_true(0.0, 2.0, [](double x) {
        return x * x >= 2.0;
    });
    assert(std::abs(root * root - 2.0) < 1e-12);
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_bisect();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
