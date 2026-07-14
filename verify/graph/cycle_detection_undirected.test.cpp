#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

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
        int first, second;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    m1une::graph::Cycle cycle = m1une::graph::find_undirected_cycle(graph);
    if (cycle.empty()) {
        fast_output << -1 << '\n';
        return 0;
    }

    const int length = int(cycle.edge_ids.size());
    fast_output << length << '\n';
    for (int i = 0; i < length; i++) {
        if (i != 0) fast_output << ' ';
        fast_output << cycle.vertices[i];
    }
    fast_output << '\n';
    for (int i = 0; i < length; i++) {
        if (i != 0) fast_output << ' ';
        fast_output << cycle.edge_ids[i];
    }
    fast_output << '\n';
}
