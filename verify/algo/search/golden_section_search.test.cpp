#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "../../../algo/search/golden_section_search.hpp"

template <class F>
int naive_argmin(int left, int right, F f) {
    int best = left;
    auto best_value = f(best);
    for (int x = left + 1; x < right; ++x) {
        auto value = f(x);
        if (value < best_value) {
            best = x;
            best_value = value;
        }
    }
    return best;
}

template <class F>
int naive_argmax(int left, int right, F f) {
    int best = left;
    auto best_value = f(best);
    for (int x = left + 1; x < right; ++x) {
        auto value = f(x);
        if (best_value < value) {
            best = x;
            best_value = value;
        }
    }
    return best;
}

void test_integer_argmin() {
    auto convex = [](long long x) {
        return (x - 7) * (x - 7) + 3;
    };
    assert(m1une::algo::golden_section_search_argmin<long long>(-100, 101, convex) == 7);

    auto plateau = [](int x) {
        if (x < 3) return 3 - x;
        if (5 < x) return x - 5;
        return 0;
    };
    assert(m1une::algo::golden_section_search_argmin<int>(-10, 10, plateau) == 3);

    auto increasing = [](int x) {
        return x;
    };
    assert(m1une::algo::golden_section_search_argmin<int>(-7, 9, increasing) == -7);
}

void test_integer_argmax() {
    auto concave = [](int x) {
        return -(x + 2) * (x + 2) + 10;
    };
    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, concave) == -2);

    auto plateau = [](int x) {
        if (x < -4) return x + 4;
        if (1 < x) return 1 - x;
        return 0;
    };
    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, plateau) == -4);

    auto increasing = [](int x) {
        return x;
    };
    assert(m1une::algo::golden_section_search_argmax<int>(-7, 9, increasing) == 8);
}

void test_random_integer_arrays() {
    std::mt19937_64 rng(20260709);
    for (int tc = 0; tc < 1000; ++tc) {
        int n = static_cast<int>(rng() % 200) + 1;
        int low = static_cast<int>(rng() % n);
        int high = low + static_cast<int>(rng() % (n - low));

        std::vector<long long> min_values(n);
        long long value = 0;
        for (int i = low - 1; i >= 0; --i) {
            value += static_cast<long long>(rng() % 7) + 1;
            min_values[i] = value;
        }
        value = 0;
        for (int i = high + 1; i < n; ++i) {
            value += static_cast<long long>(rng() % 7) + 1;
            min_values[i] = value;
        }

        int base = static_cast<int>(rng() % 1000) - 500;
        auto min_f = [&](int x) {
            return min_values[x - base];
        };
        int xmin = m1une::algo::golden_section_search_argmin<int>(base, base + n, min_f);
        assert(xmin == naive_argmin(base, base + n, min_f));

        std::vector<long long> max_values(n);
        for (int i = 0; i < n; ++i) max_values[i] = -min_values[i];
        auto max_f = [&](int x) {
            return max_values[x - base];
        };
        int xmax = m1une::algo::golden_section_search_argmax<int>(base, base + n, max_f);
        assert(xmax == naive_argmax(base, base + n, max_f));
    }
}

void test_integer_evaluation_reuse() {
    for (int n = 1; n <= 300; ++n) {
        int base = -n / 2;
        int center = base + n / 3;
        auto value_at = [center](int x) {
            return x < center ? center - x : x - center;
        };

        std::vector<int> count(n);
        auto f = [&](int x) {
            int index = x - base;
            assert(count[index] == 0);
            ++count[index];
            return value_at(x);
        };

        int xmin = m1une::algo::golden_section_search_argmin<int>(base, base + n, f);
        assert(xmin == naive_argmin(base, base + n, value_at));

        std::fill(count.begin(), count.end(), 0);
        auto g = [&](int x) {
            int index = x - base;
            assert(count[index] == 0);
            ++count[index];
            return -value_at(x);
        };
        auto max_value_at = [&](int x) {
            return -value_at(x);
        };

        int xmax = m1une::algo::golden_section_search_argmax<int>(base, base + n, g);
        assert(xmax == naive_argmax(base, base + n, max_value_at));
    }
}

void test_real_argmin() {
    auto convex = [](double x) {
        return (x - 2.75) * (x - 2.75);
    };
    double x = m1une::algo::golden_section_search_argmin(-100.0, 100.0, convex);
    assert(std::abs(x - 2.75) < 1e-9);

    auto increasing = [](double x) {
        return x;
    };
    double left = m1une::algo::golden_section_search_argmin(-3.0, 8.0, increasing);
    assert(std::abs(left + 3.0) < 1e-9);
}

void test_real_argmax() {
    auto concave = [](double x) {
        return -(x + 0.5) * (x + 0.5);
    };
    double x = m1une::algo::golden_section_search_argmax(-100.0, 100.0, concave);
    assert(std::abs(x + 0.5) < 1e-9);

    auto increasing = [](double x) {
        return x;
    };
    double right = m1une::algo::golden_section_search_argmax(-3.0, 8.0, increasing);
    assert(std::abs(right - 8.0) < 1e-9);
}

void test_evaluation_count() {
    int zero_iteration_calls = 0;
    auto f0 = [&](double x) {
        ++zero_iteration_calls;
        return x * x;
    };
    double midpoint = m1une::algo::golden_section_search_argmin(-2.0, 4.0, f0, 0);
    assert(midpoint == 1.0);
    assert(zero_iteration_calls == 0);

    int calls = 0;
    auto f = [&](double x) {
        ++calls;
        return (x - 1.0) * (x - 1.0);
    };
    m1une::algo::golden_section_search_argmin(-5.0, 5.0, f, 37);
    assert(calls == 38);
}

void test_random_quadratics() {
    std::mt19937_64 rng(20260708);
    std::uniform_real_distribution<double> center_dist(-1000.0, 1000.0);
    std::uniform_real_distribution<double> width_dist(0.1, 1000.0);
    std::uniform_real_distribution<double> coef_dist(0.1, 10.0);

    for (int tc = 0; tc < 1000; ++tc) {
        double center = center_dist(rng);
        double left_width = width_dist(rng);
        double right_width = width_dist(rng);
        double coef = coef_dist(rng);
        double left = center - left_width;
        double right = center + right_width;

        auto convex = [=](double x) {
            double dx = x - center;
            return coef * dx * dx;
        };
        double expected_min = center;
        double xmin = m1une::algo::golden_section_search_argmin(left, right, convex, 120);
        assert(std::abs(xmin - expected_min) < 1e-8);

        auto concave = [=](double x) {
            double dx = x - center;
            return -coef * dx * dx;
        };
        double expected_max = center;
        double xmax = m1une::algo::golden_section_search_argmax(left, right, concave, 120);
        assert(std::abs(xmax - expected_max) < 1e-8);
    }
}

int main() {
    test_integer_argmin();
    test_integer_argmax();
    test_random_integer_arrays();
    test_integer_evaluation_reuse();
    test_real_argmin();
    test_real_argmax();
    test_evaluation_count();
    test_random_quadratics();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
