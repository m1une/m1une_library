#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "../../../algo/dp/knapsack.hpp"

std::vector<char> naive_subset_sum(const std::vector<int>& weights, int limit) {
    std::vector<char> reachable(limit + 1, 0);
    reachable[0] = 1;
    for (int weight : weights) {
        for (int sum = limit; weight <= sum; --sum) {
            if (reachable[sum - weight]) reachable[sum] = 1;
        }
    }
    return reachable;
}

std::vector<long long> naive_zero_one_max_value(
    const std::vector<int>& weights,
    const std::vector<long long>& values,
    int capacity
) {
    std::vector<long long> result(capacity + 1, 0);
    const int n = int(weights.size());
    for (int mask = 0; mask < (1 << n); ++mask) {
        int weight = 0;
        long long value = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                weight += weights[i];
                value += values[i];
            }
        }
        if (weight <= capacity) {
            for (int current = weight; current <= capacity; ++current) {
                result[current] = std::max(result[current], value);
            }
        }
    }
    return result;
}

std::vector<long long> naive_bounded_max_value(
    const std::vector<int>& weights,
    const std::vector<long long>& values,
    const std::vector<int>& counts,
    int capacity
) {
    std::vector<long long> result(capacity + 1, 0);
    const int n = int(weights.size());

    auto dfs = [&](auto& self, int item, int weight, long long value) -> void {
        if (item == n) {
            if (weight <= capacity) {
                for (int current = weight; current <= capacity; ++current) {
                    result[current] = std::max(result[current], value);
                }
            }
            return;
        }
        for (int take = 0; take <= counts[item]; ++take) {
            self(self, item + 1, weight + weights[item] * take, value + values[item] * take);
        }
    };
    dfs(dfs, 0, 0, 0);
    return result;
}

std::vector<long long> naive_min_weight_for_value(
    const std::vector<long long>& weights,
    const std::vector<int>& values,
    int value_limit
) {
    const long long inf = std::numeric_limits<long long>::max() / 4;
    std::vector<long long> result(value_limit + 1, inf);
    const int n = int(weights.size());
    for (int mask = 0; mask < (1 << n); ++mask) {
        long long weight = 0;
        int value = 0;
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                weight += weights[i];
                value += values[i];
            }
        }
        if (value <= value_limit) {
            result[value] = std::min(result[value], weight);
        }
    }
    return result;
}

void test_subset_sum() {
    for (int n = 0; n <= 8; ++n) {
        std::vector<int> weights(n);
        for (int seed = 0; seed < 60; ++seed) {
            for (int i = 0; i < n; ++i) {
                weights[i] = (seed * 13 + i * 7) % 10;
            }
            assert(m1une::algo::subset_sum_reachable(weights, 30) == naive_subset_sum(weights, 30));
        }
    }
}

void test_zero_one_knapsack() {
    std::vector<int> weights = {2, 3, 4, 5};
    std::vector<long long> values = {4, 5, 7, 8};
    assert(
        m1une::algo::zero_one_knapsack_max_value(weights, values, 10)
        == naive_zero_one_max_value(weights, values, 10)
    );
}

void test_bounded_knapsack() {
    std::vector<int> weights = {0, 2, 3};
    std::vector<long long> values = {5, 3, 4};
    std::vector<int> counts = {2, 3, 2};
    assert(
        m1une::algo::bounded_knapsack_max_value(weights, values, counts, 10)
        == naive_bounded_max_value(weights, values, counts, 10)
    );
}

void test_min_weight_for_value() {
    std::vector<long long> weights = {3, 2, 5, 7};
    std::vector<int> values = {4, 3, 6, 8};
    assert(
        m1une::algo::zero_one_knapsack_min_weight_for_value(weights, values, 20)
        == naive_min_weight_for_value(weights, values, 20)
    );
}

int main() {
    test_subset_sum();
    test_zero_one_knapsack();
    test_bounded_knapsack();
    test_min_weight_for_value();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
