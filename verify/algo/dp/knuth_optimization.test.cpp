#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_10_D"
#define ERROR 1e-7

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#include "../../../algo/dp/knuth_optimization.hpp"

void test_knuth_optimization() {
    for (int n = 0; n <= 45; n++) {
        for (int test = 0; test < 20; test++) {
            std::vector<long long> weight(n);
            for (int i = 0; i < n; i++) weight[i] = (test * 7 + i * 11 + n) % 13;
            std::vector<long long> prefix(n + 1);
            for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + weight[i];
            auto interval_cost = [&](int left, int right) {
                return prefix[right] - prefix[left];
            };

            auto result = m1une::algo::knuth_optimization(n, interval_cost);
            std::vector<std::vector<long long>> expected(
                n + 1, std::vector<long long>(n + 1));
            for (int length = 2; length <= n; length++) {
                for (int left = 0; left + length <= n; left++) {
                    int right = left + length;
                    expected[left][right] = std::numeric_limits<long long>::max();
                    for (int split = left + 1; split < right; split++) {
                        expected[left][right] =
                            std::min(expected[left][right],
                                     expected[left][split] + expected[split][right] +
                                         interval_cost(left, right));
                    }
                }
            }
            assert(result.value == expected);
            assert(result.optimum() == expected[0][n]);

            for (int length = 2; length <= n; length++) {
                for (int left = 0; left + length <= n; left++) {
                    int right = left + length;
                    int split = result.split[left][right];
                    assert(result.split[left][right - 1] <= split);
                    assert(split <= result.split[left + 1][right]);
                    assert(result.value[left][right] ==
                           result.value[left][split] + result.value[split][right] +
                               interval_cost(left, right));
                }
            }
        }
    }
}

int main() {
    test_knuth_optimization();
    int n;
    std::cin >> n;
    std::vector<double> p(n + 1), q(n + 2);
    for (int i = 0; i < n; ++i) std::cin >> p[i + 1];
    for (int i = 0; i <= n; ++i) std::cin >> q[i + 1];
    for (int i = 0; i < n; ++i) p[i + 1] += p[i];
    for (int i = 0; i <= n; ++i) q[i + 1] += q[i];
    // Leaves are the n+1 unsuccessful-search gaps; a split selects a key.
    auto result = m1une::algo::knuth_optimization(n + 1, [&](int l, int r) {
        return q[r] - q[l] + p[r - 1] - p[l];
    });
    std::cout << std::fixed << std::setprecision(12) << result.optimum() + q[n + 1] << '\n';
}
