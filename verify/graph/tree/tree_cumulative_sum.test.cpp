#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include <cassert>
#include <cstdint>
#include <random>
#include <vector>

#include "../../../graph/graph.hpp"
#include "../../../graph/tree/cumulative_sum.hpp"
#include "../../../graph/tree/rooted_tree.hpp"
#include "../../../utilities/fast_io.hpp"

struct XorGroup {
    using value_type = std::uint64_t;

    static value_type id() {
        return 0;
    }

    static value_type op(value_type first, value_type second) {
        return first ^ second;
    }

    static value_type inv(value_type value) {
        return value;
    }
};

void test_random() {
    std::mt19937_64 random(123456789);
    for (int test = 0; test < 100; test++) {
        int n = 1 + int(random() % 50);
        m1une::graph::Graph<int> graph(n);
        std::vector<long long> edge_value;
        edge_value.reserve(n - 1);
        for (int vertex = 1; vertex < n; vertex++) {
            int parent = int(random() % vertex);
            int edge = graph.add_edge(parent, vertex);
            assert(edge == int(edge_value.size()));
            edge_value.push_back(static_cast<long long>(random() % 201) - 100);
        }

        std::vector<long long> vertex_value(n);
        std::vector<std::uint64_t> xor_value(n);
        for (int vertex = 0; vertex < n; vertex++) {
            vertex_value[vertex] =
                static_cast<long long>(random() % 201) - 100;
            xor_value[vertex] = random();
        }

        int root = int(random() % n);
        m1une::tree::RootedTree<int> rooted(graph, root);
        m1une::tree::TreeCumulativeSum<long long> vertex_sum(
            graph,
            vertex_value,
            root
        );
        m1une::tree::TreeEdgeCumulativeSum<long long> edge_sum(
            graph,
            edge_value,
            root
        );
        m1une::tree::TreeCumulativeProduct<XorGroup> vertex_xor(
            graph,
            xor_value,
            root
        );

        assert(vertex_sum.size() == n);
        assert(vertex_sum.root() == root);
        for (int vertex = 0; vertex < n; vertex++) {
            long long expected_vertex_sum = 0;
            long long expected_edge_sum = 0;
            std::uint64_t expected_xor = 0;
            for (
                int current = vertex;
                current != -1;
                current = rooted.parent[current]
            ) {
                expected_vertex_sum += vertex_value[current];
                expected_xor ^= xor_value[current];
                if (rooted.parent[current] != -1) {
                    expected_edge_sum +=
                        edge_value[rooted.parent_edge[current]];
                }
            }
            assert(vertex_sum.sum(vertex) == expected_vertex_sum);
            assert(edge_sum.sum(vertex) == expected_edge_sum);
            assert(vertex_xor.prod(vertex) == expected_xor);
        }

        for (int query = 0; query < 200; query++) {
            int first = int(random() % n);
            int second = int(random() % n);
            std::vector<int> path = rooted.path(first, second);
            std::vector<int> path_edges = rooted.path_edges(first, second);

            long long expected_vertex_sum = 0;
            std::uint64_t expected_xor = 0;
            for (int vertex : path) {
                expected_vertex_sum += vertex_value[vertex];
                expected_xor ^= xor_value[vertex];
            }
            long long expected_edge_sum = 0;
            for (int edge : path_edges) expected_edge_sum += edge_value[edge];

            assert(
                vertex_sum.lca(first, second) == rooted.lca(first, second)
            );
            assert(vertex_sum.sum(first, second) == expected_vertex_sum);
            assert(edge_sum.sum(first, second) == expected_edge_sum);
            assert(vertex_xor.prod(first, second) == expected_xor);
        }
    }

    m1une::graph::Graph<int> graph;
    std::vector<long long> values;
    m1une::tree::TreeCumulativeSum<long long> empty(graph, values);
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.root() == -1);
}

int main() {
    test_random();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n;
    input >> n;
    m1une::graph::Graph<long long> graph(n);
    std::vector<long long> edge_value(n - 1);
    for (int edge = 0; edge < n - 1; edge++) {
        int first, second;
        long long weight;
        input >> first >> second >> weight;
        int id = graph.add_edge(first, second, weight);
        edge_value[id] = weight;
    }

    m1une::tree::TreeEdgeCumulativeSum<long long> from_zero(
        graph,
        edge_value,
        0
    );
    int first = 0;
    for (int vertex = 1; vertex < n; vertex++) {
        if (from_zero.sum(first) < from_zero.sum(vertex)) first = vertex;
    }

    m1une::tree::TreeEdgeCumulativeSum<long long> from_first(
        graph,
        edge_value,
        first
    );
    int second = first;
    for (int vertex = 0; vertex < n; vertex++) {
        if (from_first.sum(second) < from_first.sum(vertex)) second = vertex;
    }

    m1une::tree::RootedTree<long long> rooted(graph, first);
    std::vector<int> path = rooted.path(first, second);
    output << from_first.sum(first, second) << ' ' << path.size() << '\n';
    for (int index = 0; index < int(path.size()); index++) {
        if (index != 0) output << ' ';
        output << path[index];
    }
    output << '\n';
}
