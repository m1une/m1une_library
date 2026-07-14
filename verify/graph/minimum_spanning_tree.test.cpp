#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include "../../utilities/fast_io.hpp"

#include "../../graph/graph.hpp"
#include "../../graph/kruskal.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int first, second;
        long long cost;
        fast_input >> first >> second >> cost;
        graph.add_edge(first, second, cost);
    }

    m1une::graph::MinimumSpanningForest<long long> result =
        m1une::graph::kruskal(graph);
    fast_output << result.cost << '\n';
    for (int i = 0; i < int(result.edges.size()); i++) {
        if (i > 0) fast_output << ' ';
        fast_output << result.edges[i].id;
    }
    fast_output << '\n';
}
