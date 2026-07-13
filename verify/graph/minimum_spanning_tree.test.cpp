#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include <iostream>

#include "../../graph/graph.hpp"
#include "../../graph/kruskal.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int first, second;
        long long cost;
        std::cin >> first >> second >> cost;
        graph.add_edge(first, second, cost);
    }

    m1une::graph::MinimumSpanningForest<long long> result =
        m1une::graph::kruskal(graph);
    std::cout << result.cost << '\n';
    for (int i = 0; i < int(result.edges.size()); i++) {
        if (i > 0) std::cout << ' ';
        std::cout << result.edges[i].id;
    }
    std::cout << '\n';
}
