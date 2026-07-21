#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../../graph/graph.hpp"
#include "../../../graph/tree/heavy_light_decomposition.hpp"
#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int vertex_count, query_count;
    fast_input >> vertex_count >> query_count;
    m1une::graph::Graph<int> tree(vertex_count);
    for (int edge = 1; edge < vertex_count; edge++) {
        int first, second;
        fast_input >> first >> second;
        tree.add_edge(first, second);
    }

    m1une::tree::HeavyLightDecomposition<int> decomposition(tree);
    while (query_count--) {
        int from, to, distance;
        fast_input >> from >> to >> distance;
        fast_output << decomposition.jump(from, to, distance) << '\n';
    }
}
