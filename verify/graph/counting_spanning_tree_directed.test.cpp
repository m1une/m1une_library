#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_directed"

#include "../../graph/matrix_tree_theorem.hpp"
#include "../../math/modint.hpp"

#include <bit>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

using mint = m1une::math::modint998244353;

bool all_reachable(
    int n,
    int root,
    const std::vector<std::vector<int>>& adjacency
) {
    std::vector<char> visited(n, false);
    std::vector<int> stack;
    stack.push_back(root);
    visited[root] = true;
    while (!stack.empty()) {
        int vertex = stack.back();
        stack.pop_back();
        for (int to : adjacency[vertex]) {
            if (visited[to]) continue;
            visited[to] = true;
            stack.push_back(to);
        }
    }
    for (char value : visited) {
        if (!value) return false;
    }
    return true;
}

mint naive_count(
    const m1une::graph::Graph<int>& graph,
    int root,
    bool outward
) {
    const int n = graph.size();
    const std::vector<m1une::graph::Edge<int>> edges = graph.edges();
    mint answer = 0;
    for (unsigned mask = 0; mask < (1U << edges.size()); mask++) {
        if (std::popcount(mask) != n - 1) continue;
        std::vector<int> constrained_degree(n, 0);
        std::vector<std::vector<int>> adjacency(n);
        mint weight = 1;
        for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
            if (((mask >> edge_id) & 1U) == 0) continue;
            const auto& edge = edges[edge_id];
            constrained_degree[outward ? edge.to : edge.from]++;
            int from = outward ? edge.from : edge.to;
            int to = outward ? edge.to : edge.from;
            adjacency[from].push_back(to);
            weight *= mint(edge.cost);
        }

        bool valid_degree = constrained_degree[root] == 0;
        for (int vertex = 0; vertex < n; vertex++) {
            if (vertex != root) valid_degree = valid_degree && constrained_degree[vertex] == 1;
        }
        if (valid_degree && all_reachable(n, root, adjacency)) answer += weight;
    }
    return answer;
}

void run_focused_tests() {
    std::mt19937 random(987654321);
    for (int test = 0; test < 200; test++) {
        int n = 1 + int(random() % 5);
        int edge_count = int(random() % 9);
        int root = int(random() % unsigned(n));
        m1une::graph::Graph<int> graph(n);
        for (int edge = 0; edge < edge_count; edge++) {
            int from = int(random() % unsigned(n));
            int to = int(random() % unsigned(n));
            int weight = int(random() % 5);
            graph.add_directed_edge(from, to, weight);
        }
        assert(
            m1une::graph::count_out_arborescences<mint>(graph, root) ==
            naive_count(graph, root, true)
        );
        assert(
            m1une::graph::count_in_arborescences<mint>(graph, root) ==
            naive_count(graph, root, false)
        );
    }
}

int main() {
    run_focused_tests();

    int vertex_count, edge_count, root;
    std::cin >> vertex_count >> edge_count >> root;
    m1une::graph::Graph<int> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        std::cin >> from >> to;
        graph.add_directed_edge(from, to);
    }
    std::cout << m1une::graph::count_out_arborescences<mint>(graph, root) << '\n';
}
