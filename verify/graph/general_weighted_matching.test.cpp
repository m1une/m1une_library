#define PROBLEM "https://judge.yosupo.jp/problem/general_weighted_matching"

#include "../../graph/general_weighted_matching.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

namespace {

using Matching = m1une::graph::GeneralWeightedMatching<int, long long>;

long long naive(const Matching& graph) {
    int n = graph.size();
    std::vector<long long> dp(1 << n, std::numeric_limits<long long>::min());
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == std::numeric_limits<long long>::min()) continue;
        int from = 0;
        while (from < n && (mask >> from & 1)) from++;
        if (from == n) continue;
        dp[mask | (1 << from)] = std::max(dp[mask | (1 << from)], dp[mask]);
        for (const auto& edge : graph.edges()) {
            if (edge.cost <= 0) continue;
            int to = -1;
            if (edge.from == from) to = edge.to;
            if (edge.to == from) to = edge.from;
            if (to == -1 || (mask >> to & 1)) continue;
            int next = mask | (1 << from) | (1 << to);
            dp[next] = std::max(dp[next], dp[mask] + edge.cost);
        }
    }
    return *std::max_element(dp.begin(), dp.end());
}

void validate(Matching& graph) {
    long long expected = naive(graph);
    assert(graph.max_weight_matching() == expected);
    assert(graph.matching_weight() == expected);

    std::vector<char> used(graph.size(), false);
    long long actual = 0;
    for (const auto& pair : graph.matching()) {
        assert(!used[pair.from] && !used[pair.to]);
        used[pair.from] = used[pair.to] = true;
        auto edge = graph.get_edge(pair.edge_id);
        assert(edge.alive);
        assert(edge.cost == pair.cost);
        assert((edge.from == pair.from && edge.to == pair.to) ||
               (edge.from == pair.to && edge.to == pair.from));
        actual += pair.cost;
    }
    assert(actual == expected);

    auto mate = graph.mate();
    auto mate_edge = graph.mate_edge();
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        if (mate[vertex] == -1) {
            assert(mate_edge[vertex] == -1);
        } else {
            assert(mate[mate[vertex]] == vertex);
            assert(mate_edge[mate[vertex]] == mate_edge[vertex]);
        }
    }
}

void test_fixed() {
    Matching empty;
    validate(empty);

    Matching graph(6);
    int edge_01 = graph.add_edge(0, 1, 8);
    graph.add_edge(1, 2, 9);
    graph.add_edge(2, 0, 10);
    graph.add_edge(2, 3, 7);
    graph.add_edge(3, 4, 6);
    graph.add_edge(4, 5, 5);
    graph.add_edge(5, 3, 4);
    graph.add_edge(0, 1, 11);
    graph.add_edge(0, 5, -100);
    validate(graph);

    graph.erase_edge(edge_01);
    assert(!graph.is_edge_alive(edge_01));
    validate(graph);
    graph.revive_edge(edge_01);
    validate(graph);

    m1une::graph::Graph<int> source(3);
    int original_01 = source.add_edge(0, 1, 4);
    source.add_edge(1, 2, 7);
    int inactive = source.add_edge(0, 2, 100);
    source.erase_edge(inactive);
    auto built = m1une::graph::make_general_weighted_matching(source);
    assert(built.matching.edge_count() == 2);
    assert(built.matching.max_weight_matching() == 7);
    assert(built.original_edge(0) == original_01);
}

void test_randomized() {
    std::uint64_t state = 123456789;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        int n = int(random() % 10);
        Matching graph(n);
        int edge_count = int(random() % 35);
        for (int i = 0; i < edge_count && n >= 2; i++) {
            int from = int(random() % n);
            int to = int(random() % n);
            if (from == to) continue;
            int cost = int(random() % 31) - 10;
            int id = graph.add_edge(from, to, cost);
            if (random() % 7 == 0) graph.erase_edge(id);
        }
        validate(graph);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, edge_count;
    std::cin >> n >> edge_count;
    Matching graph(n);
    while (edge_count--) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        graph.add_edge(from, to, cost);
    }

    long long weight = graph.max_weight_matching();
    auto matching = graph.matching();
    std::cout << matching.size() << ' ' << weight << '\n';
    for (const auto& pair : matching) {
        std::cout << pair.from << ' ' << pair.to << '\n';
    }
}
