#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "../../graph/dag.hpp"

using m1une::graph::Graph;

std::vector<std::vector<char>> naive_reachability(const Graph<int>& g) {
    const int n = g.size();
    std::vector<std::vector<char>> reach(n, std::vector<char>(n, false));
    for (int v = 0; v < n; v++) reach[v][v] = true;
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (e.alive) reach[v][e.to] = true;
        }
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }
    return reach;
}

int naive_maximum_matching(const Graph<int>& g) {
    const int n = g.size();
    std::vector<std::vector<int>> adjacency(n);
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (e.alive && std::find(adjacency[v].begin(), adjacency[v].end(), e.to) == adjacency[v].end()) {
                adjacency[v].push_back(e.to);
            }
        }
    }

    std::vector<int> dp(1 << n, -1);
    dp[0] = 0;
    for (int left = 0; left < n; left++) {
        std::vector<int> next = dp;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] < 0) continue;
            for (int right : adjacency[left]) {
                if ((mask >> right) & 1) continue;
                int next_mask = mask | (1 << right);
                next[next_mask] = std::max(next[next_mask], dp[mask] + 1);
            }
        }
        dp.swap(next);
    }
    return *std::max_element(dp.begin(), dp.end());
}

void test_randomized() {
    std::mt19937 rng(123456789);
    for (int iteration = 0; iteration < 1000; iteration++) {
        const int n = int(rng() % 8);
        std::vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;
        std::shuffle(order.begin(), order.end(), rng);

        Graph<int> g(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (rng() % 3 != 0) continue;
                g.add_directed_edge(order[i], order[j], int(rng() % 11) - 5);
                if (rng() % 8 == 0) {
                    int id = g.add_directed_edge(order[i], order[j], int(rng() % 11) - 5);
                    if (rng() % 3 == 0) g.erase_edge(id);
                }
            }
        }

        std::vector<int> sources;
        for (int v = 0; v < n; v++) {
            if (rng() % 3 == 0) sources.push_back(v);
        }
        if (n > 0 && sources.empty()) sources.push_back(int(rng() % n));

        const int neg_inf = std::numeric_limits<int>::lowest() / 4;
        std::vector<int> longest(n, neg_inf);
        std::vector<long long> path_count(n, 0);
        std::function<void(int, int)> enumerate = [&](int v, int distance) {
            longest[v] = std::max(longest[v], distance);
            path_count[v]++;
            for (const auto& e : g[v]) {
                if (e.alive) enumerate(e.to, distance + e.cost);
            }
        };
        for (int s : sources) enumerate(s, 0);

        auto longest_result = m1une::graph::dag_longest_path(g, sources);
        assert(longest_result.has_value());
        assert(longest_result->dist == longest);
        for (int v = 0; v < n; v++) {
            if (!longest_result->reachable(v)) continue;
            std::vector<int> path = longest_result->path(v);
            assert(!path.empty() && path.back() == v);
            assert(std::find(sources.begin(), sources.end(), path.front()) != sources.end());
        }

        auto count_result = m1une::graph::dag_path_count<long long>(g, sources);
        assert(count_result.has_value());
        assert(*count_result == path_count);

        auto reachability = m1une::graph::dag_reachability(g);
        assert(reachability.has_value());
        auto expected_reachability = naive_reachability(g);
        for (int from = 0; from < n; from++) {
            for (int to = 0; to < n; to++) {
                assert(reachability->reachable(from, to) == bool(expected_reachability[from][to]));
            }
        }

        auto reduction = m1une::graph::dag_transitive_reduction(g);
        assert(reduction.has_value());
        assert(naive_reachability(reduction->graph) == expected_reachability);
        assert(reduction->graph.edge_count() == int(reduction->original_edge_ids.size()));
        std::vector<m1une::graph::Edge<int>> reduced_edges = reduction->graph.edges();
        for (int removed = 0; removed < reduction->graph.edge_count(); removed++) {
            Graph<int> without_edge(n);
            for (const auto& e : reduced_edges) {
                if (e.id != removed) without_edge.add_directed_edge(e.from, e.to, e.cost);
            }
            const auto& edge = reduced_edges[removed];
            assert(!naive_reachability(without_edge)[edge.from][edge.to]);
        }

        auto cover = m1une::graph::minimum_dag_path_cover(g);
        assert(cover.has_value());
        assert(cover->size() == n - naive_maximum_matching(g));
        std::vector<int> occurrence(n, 0);
        for (int i = 0; i < cover->size(); i++) {
            assert(cover->path_edge_ids[i].size() + 1 == cover->paths[i].size());
            for (int v : cover->paths[i]) occurrence[v]++;
            for (int j = 0; j + 1 < int(cover->paths[i].size()); j++) {
                int from = cover->paths[i][j];
                int to = cover->paths[i][j + 1];
                int edge_id = cover->path_edge_ids[i][j];
                bool found = false;
                for (const auto& e : g[from]) {
                    if (e.alive && e.to == to && e.id == edge_id) found = true;
                }
                assert(found);
            }
        }
        for (int count : occurrence) assert(count == 1);
    }
}

void test_cycle_rejection() {
    Graph<int> g(3);
    g.add_directed_edge(0, 1);
    g.add_directed_edge(1, 2);
    g.add_directed_edge(2, 0);
    assert(!m1une::graph::dag_longest_path(g, 0));
    assert(!m1une::graph::dag_path_count(g, 0));
    assert(!m1une::graph::dag_reachability(g));
    assert(!m1une::graph::dag_transitive_reduction(g));
    assert(!m1une::graph::minimum_dag_path_cover(g));
}

int main() {
    test_randomized();
    test_cycle_rejection();

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Graph<int> g(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        std::cin >> from >> to;
        g.add_directed_edge(from, to);
    }
    std::cout << !m1une::graph::is_dag(g) << '\n';
}
