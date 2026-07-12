#define PROBLEM "https://judge.yosupo.jp/problem/k_shortest_walk"

#include "../../graph/k_shortest_walk.hpp"

#include <cassert>
#include <functional>
#include <iostream>
#include <queue>
#include <random>
#include <utility>
#include <vector>

namespace {

std::vector<long long> naive_k_shortest_walk(
    const m1une::graph::Graph<long long>& graph,
    int source,
    int target,
    int k
) {
    using Entry = std::pair<long long, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> queue;
    std::vector<int> popped(graph.size(), 0);
    std::vector<long long> result;
    queue.emplace(0, source);
    while (!queue.empty() && int(result.size()) < k) {
        auto [cost, vertex] = queue.top();
        queue.pop();
        if (popped[vertex] == k) continue;
        popped[vertex]++;
        if (vertex == target) result.push_back(cost);
        for (const auto& edge : graph[vertex]) {
            if (edge.alive) queue.emplace(cost + edge.cost, edge.to);
        }
    }
    return result;
}

void deterministic_test() {
    m1une::graph::Graph<long long> graph(3);
    graph.add_directed_edge(0, 1, 2);
    graph.add_directed_edge(1, 2, 3);
    graph.add_directed_edge(0, 2, 8);
    graph.add_directed_edge(1, 1, 1);
    std::vector<long long> expected{5, 6, 7, 8, 8, 9};
    assert(m1une::graph::k_shortest_walk(graph, 0, 2, 6) == expected);

    m1une::graph::Graph<long long> loop(1);
    loop.add_directed_edge(0, 0, 0);
    assert(m1une::graph::k_shortest_walk(loop, 0, 0, 20) == std::vector<long long>(20, 0));

    m1une::graph::Graph<long long> unreachable(2);
    assert(m1une::graph::k_shortest_walk(unreachable, 0, 1, 10).empty());
    assert(m1une::graph::k_shortest_walk(unreachable, 0, 0, 0).empty());
}

void randomized_test() {
    std::mt19937 random(20260713);
    for (int test = 0; test < 2000; test++) {
        int n = std::uniform_int_distribution<int>(1, 7)(random);
        int m = std::uniform_int_distribution<int>(0, 18)(random);
        int source = std::uniform_int_distribution<int>(0, n - 1)(random);
        int target = std::uniform_int_distribution<int>(0, n - 1)(random);
        int k = std::uniform_int_distribution<int>(0, 20)(random);
        m1une::graph::Graph<long long> graph(n);
        for (int edge = 0; edge < m; edge++) {
            int from = std::uniform_int_distribution<int>(0, n - 1)(random);
            int to = std::uniform_int_distribution<int>(0, n - 1)(random);
            int cost = std::uniform_int_distribution<int>(0, 8)(random);
            int id = graph.add_directed_edge(from, to, cost);
            if (std::uniform_int_distribution<int>(0, 7)(random) == 0) graph.erase_edge(id);
        }
        auto expected = naive_k_shortest_walk(graph, source, target, k);
        auto actual = m1une::graph::k_shortest_walk(graph, source, target, k);
        assert(actual == expected);
    }
}

}  // namespace

int main() {
    deterministic_test();
    randomized_test();

    int n, m, source, target, k;
    std::cin >> n >> m >> source >> target >> k;
    m1une::graph::Graph<long long> graph(n);
    for (int edge = 0; edge < m; edge++) {
        int from, to;
        long long cost;
        std::cin >> from >> to >> cost;
        graph.add_directed_edge(from, to, cost);
    }
    auto answer = m1une::graph::k_shortest_walk(graph, source, target, k);
    answer.resize(k, -1);
    for (long long value : answer) std::cout << value << "\n";
}
