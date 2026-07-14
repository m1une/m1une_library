#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include "../../graph/cycle_detection.hpp"
#include "../../graph/graph.hpp"

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        fast_input >> from >> to;
        graph.add_directed_edge(from, to);
    }

    m1une::graph::Cycle cycle = m1une::graph::find_directed_cycle(graph);
    if (cycle.empty()) {
        fast_output << -1 << '\n';
        return 0;
    }
    fast_output << cycle.edge_ids.size() << '\n';
    for (int edge : cycle.edge_ids) fast_output << edge << '\n';
}
