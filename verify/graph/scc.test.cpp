#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <iostream>
#include <vector>

#include "../../graph/graph.hpp"
#include "../../graph/scc.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    m1une::graph::Graph<int> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        std::cin >> from >> to;
        graph.add_directed_edge(from, to);
    }

    m1une::graph::SccResult result =
        m1une::graph::strongly_connected_components(graph);
    std::cout << result.count << '\n';
    for (const std::vector<int>& group : result.groups) {
        std::cout << group.size();
        for (int vertex : group) std::cout << ' ' << vertex;
        std::cout << '\n';
    }
}
