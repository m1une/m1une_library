#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "../../../utilities/fast_io.hpp"

#include "../../../graph/graph.hpp"
#include "../../../graph/tree/diameter.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count;
    fast_input >> vertex_count;
    m1une::graph::Graph<long long> graph(vertex_count);
    for (int i = 0; i + 1 < vertex_count; i++) {
        int first, second;
        long long cost;
        fast_input >> first >> second >> cost;
        graph.add_edge(first, second, cost);
    }

    m1une::tree::TreeDiameter<long long> diameter =
        m1une::tree::tree_diameter(graph);
    fast_output << diameter.cost << ' ' << diameter.vertices.size() << '\n';
    for (int i = 0; i < int(diameter.vertices.size()); i++) {
        if (i > 0) fast_output << ' ';
        fast_output << diameter.vertices[i];
    }
    fast_output << '\n';
}
