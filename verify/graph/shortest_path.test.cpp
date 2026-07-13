#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <iostream>
#include <vector>

#include "../../graph/dijkstra.hpp"
#include "../../graph/graph.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_count, edge_count, source, target;
    std::cin >> vertex_count >> edge_count >> source >> target;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        long long cost;
        std::cin >> from >> to >> cost;
        graph.add_directed_edge(from, to, cost);
    }

    m1une::graph::DijkstraResult<long long> result =
        m1une::graph::dijkstra(graph, source);
    if (!result.reachable(target)) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::vector<int> path = result.path(target);
    std::cout << result.dist[target] << ' ' << path.size() - 1 << '\n';
    for (int i = 1; i < int(path.size()); i++) {
        std::cout << path[i - 1] << ' ' << path[i] << '\n';
    }
}
