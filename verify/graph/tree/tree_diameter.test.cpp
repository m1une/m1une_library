#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include <iostream>

#include "../../../graph/graph.hpp"
#include "../../../graph/tree/diameter.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_count;
    std::cin >> vertex_count;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i + 1 < vertex_count; i++) {
        int first, second;
        long long cost;
        std::cin >> first >> second >> cost;
        graph.add_edge(first, second, cost);
    }

    m1une::tree::TreeDiameter<long long> diameter =
        m1une::tree::tree_diameter(graph);
    std::cout << diameter.cost << ' ' << diameter.vertices.size() << '\n';
    for (int i = 0; i < int(diameter.vertices.size()); i++) {
        if (i > 0) std::cout << ' ';
        std::cout << diameter.vertices[i];
    }
    std::cout << '\n';
}
