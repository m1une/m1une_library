#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../graph/dijkstra.hpp"
#include "../../graph/graph.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count, edge_count, source, target;
    fast_input >> vertex_count >> edge_count >> source >> target;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        long long cost;
        fast_input >> from >> to >> cost;
        graph.add_directed_edge(from, to, cost);
    }

    m1une::graph::DijkstraResult<long long> result =
        m1une::graph::dijkstra(graph, source);
    if (!result.reachable(target)) {
        fast_output << -1 << '\n';
        return 0;
    }

    std::vector<int> path = result.path(target);
    fast_output << result.dist[target] << ' ' << path.size() - 1 << '\n';
    for (int i = 1; i < int(path.size()); i++) {
        fast_output << path[i - 1] << ' ' << path[i] << '\n';
    }
}
