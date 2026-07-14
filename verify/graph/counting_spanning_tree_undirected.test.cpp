#define PROBLEM "https://judge.yosupo.jp/problem/counting_spanning_tree_undirected"

#include "../../graph/matrix_tree_theorem.hpp"
#include "../../math/modint.hpp"

#include <bit>
#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <numeric>
#include <random>
#include <vector>

using mint = m1une::math::modint998244353;

struct Dsu {
    std::vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int leader(int vertex) {
        while (parent[vertex] != vertex) {
            parent[vertex] = parent[parent[vertex]];
            vertex = parent[vertex];
        }
        return vertex;
    }

    bool merge(int first, int second) {
        first = leader(first);
        second = leader(second);
        if (first == second) return false;
        parent[second] = first;
        return true;
    }
};

mint naive_count(const m1une::graph::Graph<int>& graph) {
    const int n = graph.size();
    const std::vector<m1une::graph::Edge<int>> edges = graph.edges();
    mint answer = 0;
    for (unsigned mask = 0; mask < (1U << edges.size()); mask++) {
        if (std::popcount(mask) != n - 1) continue;
        Dsu dsu(n);
        mint weight = 1;
        bool acyclic = true;
        for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
            if (((mask >> edge_id) & 1U) == 0) continue;
            const auto& edge = edges[edge_id];
            if (!dsu.merge(edge.from, edge.to)) {
                acyclic = false;
                break;
            }
            weight *= mint(edge.cost);
        }
        if (!acyclic) continue;
        bool connected = true;
        for (int vertex = 1; vertex < n; vertex++) {
            connected = connected && dsu.leader(vertex) == dsu.leader(0);
        }
        if (connected) answer += weight;
    }
    return answer;
}

void run_focused_tests() {
    std::mt19937 random(123456789);
    for (int test = 0; test < 200; test++) {
        int n = 1 + int(random() % 6);
        int edge_count = int(random() % 9);
        m1une::graph::Graph<int> graph(n);
        for (int edge = 0; edge < edge_count; edge++) {
            int from = int(random() % unsigned(n));
            int to = int(random() % unsigned(n));
            int weight = int(random() % 5);
            graph.add_edge(from, to, weight);
        }
        assert(m1une::graph::count_spanning_trees<mint>(graph) == naive_count(graph));
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    run_focused_tests();

    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<int> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        fast_input >> from >> to;
        graph.add_edge(from, to);
    }
    fast_output << m1une::graph::count_spanning_trees<mint>(graph) << '\n';
}
