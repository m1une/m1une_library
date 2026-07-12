#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../../graph/block_cut_tree.hpp"

namespace {

#ifndef NDEBUG
void verify_block_cut_tree(const m1une::graph::BiconnectedComponentsResult& bcc) {
    const auto actual = m1une::graph::block_cut_tree(bcc);
    const int n = int(bcc.vertex_components.size());
    const int block_count = bcc.component_count();
    assert(actual.block_count() == block_count);
    assert(actual.node_count() == block_count + int(bcc.articulation.size()));

    std::vector<std::vector<int>> expected_forest(actual.node_count());
    int incidence_count = 0;
    for (int vertex = 0; vertex < n; vertex++) {
        if (!bcc.is_articulation(vertex)) continue;
        const int node = actual.node_of_articulation[vertex];
        for (int block : bcc.vertex_components[vertex]) {
            expected_forest[node].push_back(block);
            expected_forest[block].push_back(node);
            incidence_count++;
        }
    }
    assert(actual.forest == expected_forest);

    int degree_sum = 0;
    for (int node = 0; node < actual.node_count(); node++) {
        assert(actual.is_block_node(node) != actual.is_articulation_node(node));
        degree_sum += int(actual.forest[node].size());
        for (int to : actual.forest[node]) {
            assert(0 <= to && to < actual.node_count());
            assert(actual.is_block_node(node) != actual.is_block_node(to));
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        const bool articulation = bcc.is_articulation(vertex);
        const int node = actual.node_of_vertex[vertex];
        assert(0 <= node && node < actual.node_count());
        if (articulation) {
            assert(actual.node_of_articulation[vertex] == node);
            assert(actual.articulation_of_node[node] == vertex);
            assert(actual.forest[node].size() == bcc.vertex_components[vertex].size());
        } else {
            assert(actual.node_of_articulation[vertex] == -1);
            assert(bcc.vertex_components[vertex].size() == 1);
            assert(node == actual.node_of_block[bcc.vertex_components[vertex][0]]);
        }
    }
    assert(degree_sum == 2 * incidence_count);

    std::vector<int> parent(actual.node_count(), -1);
    std::vector<int> stack;
    for (int root = 0; root < actual.node_count(); root++) {
        if (parent[root] != -1) continue;
        parent[root] = root;
        stack.push_back(root);
        while (!stack.empty()) {
            const int node = stack.back();
            stack.pop_back();
            for (int to : actual.forest[node]) {
                if (to == parent[node]) continue;
                assert(parent[to] == -1);
                parent[to] = node;
                stack.push_back(to);
            }
        }
    }
}

void randomized_test() {
    m1une::graph::Graph<> empty_graph(0);
    verify_block_cut_tree(m1une::graph::biconnected_components(empty_graph));

    m1une::graph::Graph<> inactive_graph(3);
    int erased = inactive_graph.add_edge(0, 1);
    inactive_graph.erase_edge(erased);
    verify_block_cut_tree(m1une::graph::biconnected_components(inactive_graph));

    std::mt19937 random(294631);
    for (int iteration = 0; iteration < 500; iteration++) {
        const int n = 1 + int(random() % 20);
        m1une::graph::Graph<> graph(n);
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                if (random() % 6 == 0) graph.add_edge(first, second);
            }
        }
        if (n >= 2 && random() % 2 == 0) {
            graph.add_edge(0, 1);
            graph.add_edge(0, 1);
        }
        auto bcc = m1une::graph::biconnected_components(graph);
        verify_block_cut_tree(bcc);
        const auto from_graph = m1une::graph::block_cut_tree(graph);
        const auto from_bcc = m1une::graph::block_cut_tree(bcc);
        assert(from_graph.forest == from_bcc.forest);
        assert(from_graph.node_of_vertex == from_bcc.node_of_vertex);
    }
}
#endif

}  // namespace

int main() {
#ifndef NDEBUG
    randomized_test();
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int first, second;
        std::cin >> first >> second;
        graph.add_edge(first, second);
    }

    auto bcc = m1une::graph::biconnected_components(graph);
#ifndef NDEBUG
    verify_block_cut_tree(bcc);
#endif
    std::cout << bcc.component_count() << '\n';
    for (const std::vector<int>& component : bcc.components) {
        std::cout << component.size();
        for (int vertex : component) std::cout << ' ' << vertex;
        std::cout << '\n';
    }
}
