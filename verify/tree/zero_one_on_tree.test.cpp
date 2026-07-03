#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "../../graph/graph.hpp"
#include "../../tree/zero_one_on_tree.hpp"

long long brute_force(const std::vector<int>& parent, const std::vector<int>& value) {
    const int n = int(parent.size());
    const int size = 1 << n;
    const long long infinity = std::numeric_limits<long long>::max() / 4;
    std::vector<long long> dp(size, infinity);
    dp[0] = 0;
    for (int mask = 0; mask < size; mask++) {
        if (dp[mask] == infinity) continue;
        int previous_ones = 0;
        for (int v = 0; v < n; v++) {
            if (mask >> v & 1) previous_ones += value[v];
        }
        for (int v = 0; v < n; v++) {
            if (mask >> v & 1) continue;
            if (parent[v] != -1 && !(mask >> parent[v] & 1)) continue;
            const int next = mask | (1 << v);
            dp[next] = std::min(dp[next], dp[mask] + (value[v] == 0 ? previous_ones : 0));
        }
    }
    return dp.back();
}

void randomized_test() {
    std::mt19937 random(712367);
    for (int iteration = 0; iteration < 500; iteration++) {
        const int n = 1 + int(random() % 9);
        std::vector<int> permutation(n);
        for (int v = 0; v < n; v++) permutation[v] = v;
        std::shuffle(permutation.begin(), permutation.end(), random);

        std::vector<int> parent(n, -2);
        const int root = permutation[0];
        parent[root] = -1;
        m1une::graph::Graph<int> graph(n);
        for (int i = 1; i < n; i++) {
            const int v = permutation[i];
            const int p = permutation[random() % i];
            parent[v] = p;
            graph.add_edge(p, v);
        }

        std::vector<int> value(n);
        for (int& x : value) x = int(random() & 1);
        const long long expected = brute_force(parent, value);
        assert(m1une::tree::zero_one_on_tree(parent, value) == expected);
        assert(m1une::tree::zero_one_on_tree(graph, value, root) == expected);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    randomized_test();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
