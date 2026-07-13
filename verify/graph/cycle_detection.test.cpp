#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include "../../graph/cycle_detection.hpp"
#include "../../graph/graph.hpp"

#include <iostream>

int main() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        std::cin >> from >> to;
        graph.add_directed_edge(from, to);
    }

    m1une::graph::Cycle cycle = m1une::graph::find_directed_cycle(graph);
    if (cycle.empty()) {
        std::cout << -1 << '\n';
        return 0;
    }
    std::cout << cycle.edge_ids.size() << '\n';
    for (int edge : cycle.edge_ids) std::cout << edge << '\n';
}
