#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include "../../graph/cycle_detection.hpp"
#include "../../graph/graph.hpp"

#include <iostream>

int main() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int first, second;
        std::cin >> first >> second;
        graph.add_edge(first, second);
    }

    m1une::graph::Cycle cycle = m1une::graph::find_undirected_cycle(graph);
    if (cycle.empty()) {
        std::cout << -1 << '\n';
        return 0;
    }

    const int length = int(cycle.edge_ids.size());
    std::cout << length << '\n';
    for (int i = 0; i < length; i++) {
        if (i != 0) std::cout << ' ';
        std::cout << cycle.vertices[i];
    }
    std::cout << '\n';
    for (int i = 0; i < length; i++) {
        if (i != 0) std::cout << ' ';
        std::cout << cycle.edge_ids[i];
    }
    std::cout << '\n';
}
