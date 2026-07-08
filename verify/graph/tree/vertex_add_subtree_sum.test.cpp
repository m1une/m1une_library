#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#include "../../../ds/range_query/fenwick_tree.hpp"
#include "../../../graph/graph.hpp"
#include "../../../graph/tree/euler_tour.hpp"
#include "../../../utilities/fast_io.hpp"

using m1une::graph::Graph;

void test_euler_tour() {
    Graph<int> empty_graph;
    m1une::tree::EulerTour<int> empty(empty_graph);
    assert(empty.empty());
    assert(empty.root == -1);
    assert(empty.visited_size() == 0);

    Graph<long long> sample(7);
    sample.add_edge(0, 1, 3);
    sample.add_edge(0, 2, 2);
    sample.add_edge(1, 3, 4);
    sample.add_edge(1, 4, 1);
    sample.add_edge(2, 5, 6);
    sample.add_edge(5, 6, 2);

    m1une::tree::EulerTour<long long> tour(sample, 0);
    std::vector<int> expected_order = {0, 1, 3, 4, 2, 5, 6};
    std::vector<int> expected_children_zero = {1, 2};
    std::vector<int> expected_subtree = {1, 3, 4};
    assert(tour.size() == 7);
    assert(tour.visited_size() == 7);
    assert(tour.root == 0);
    assert(tour.order == expected_order);
    assert(tour.children[0] == expected_children_zero);
    assert(tour.parent[6] == 5);
    assert(tour.parent_edge[6] == 5);
    assert(tour.depth[6] == 3);
    assert(tour.dist[6] == 10);
    assert(tour.subtree_size[0] == 7);
    assert(tour.subtree_size[1] == 3);
    assert(tour.is_ancestor(1, 4));
    assert(!tour.is_ancestor(2, 4));
    assert(tour.in_subtree(4, 1));
    assert(tour.subtree_range(1).first == 1);
    assert(tour.subtree_range(1).second == 4);
    assert(tour.subtree_range(1, true).first == 2);
    assert(tour.subtree_range(1, true).second == 4);
    assert(tour.subtree_vertices(1) == expected_subtree);

    int subtree_sum = 0;
    tour.for_each_subtree(1, [&](int vertex) {
        subtree_sum += vertex;
    });
    assert(subtree_sum == 8);

    std::mt19937 random(123456789);
    for (int test = 0; test < 50; ++test) {
        int n = 1 + int(random() % 40);
        Graph<int> graph(n);
        std::vector<int> parent(n, -1);
        for (int v = 1; v < n; ++v) {
            parent[v] = int(random() % v);
            graph.add_edge(parent[v], v);
        }

        m1une::tree::EulerTour<int> random_tour(graph, 0);
        assert(random_tour.size() == n);
        assert(random_tour.visited_size() == n);

        std::vector<int> expected_size(n, 1);
        for (int v = n - 1; v >= 1; --v) expected_size[parent[v]] += expected_size[v];
        assert(random_tour.subtree_size == expected_size);

        for (int i = 0; i < n; ++i) {
            int vertex = random_tour.order[i];
            assert(random_tour.tin[vertex] == i);
            assert(random_tour.tout[vertex] - random_tour.tin[vertex] == random_tour.subtree_size[vertex]);
        }

        auto naive_ancestor = [&](int ancestor, int vertex) {
            while (vertex != -1) {
                if (vertex == ancestor) return true;
                vertex = parent[vertex];
            }
            return false;
        };

        for (int u = 0; u < n; ++u) {
            std::vector<int> expected_vertices;
            for (int v = 0; v < n; ++v) {
                assert(random_tour.is_ancestor(u, v) == naive_ancestor(u, v));
                if (naive_ancestor(u, v)) expected_vertices.push_back(v);
            }
            std::vector<int> actual_vertices = random_tour.subtree_vertices(u);
            std::sort(actual_vertices.begin(), actual_vertices.end());
            assert(actual_vertices == expected_vertices);
        }
    }
}

int main() {
    test_euler_tour();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0, q = 0;
    if (!input.read(n)) return 0;
    input.read(q);

    std::vector<long long> values(n);
    for (long long& value : values) input.read(value);

    Graph<int> graph(n);
    for (int v = 1; v < n; ++v) {
        int p = 0;
        input.read(p);
        graph.add_edge(p, v);
    }

    m1une::tree::EulerTour<int> tour(graph, 0);
    std::vector<long long> base(n);
    for (int v = 0; v < n; ++v) base[tour.tin[v]] = values[v];
    m1une::ds::FenwickTree<long long> fenwick(base);

    for (int query = 0; query < q; ++query) {
        int type = 0;
        input.read(type);
        if (type == 0) {
            int u = 0;
            long long x = 0;
            input.read(u);
            input.read(x);
            fenwick.add(tour.tin[u], x);
        } else {
            int u = 0;
            input.read(u);
            auto [l, r] = tour.subtree_range(u);
            output.println(fenwick.sum(l, r));
        }
    }
}
