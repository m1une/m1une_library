#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../graph/graph.hpp"
#include "../../graph/scc.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<int> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int from, to;
        fast_input >> from >> to;
        graph.add_directed_edge(from, to);
    }

    m1une::graph::SccResult result =
        m1une::graph::strongly_connected_components(graph);
    fast_output << result.count << '\n';
    for (const std::vector<int>& group : result.groups) {
        fast_output << group.size();
        for (int vertex : group) fast_output << ' ' << vertex;
        fast_output << '\n';
    }
}
