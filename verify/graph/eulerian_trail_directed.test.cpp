#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#include <cassert>
#include <iostream>
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include "../../graph/eulerian_trail.hpp"

namespace {

#ifndef NDEBUG
bool brute_directed_dfs(
    int vertex,
    const std::vector<std::pair<int, int>>& edges,
    int used_mask
) {
    if (used_mask == (1 << int(edges.size())) - 1) return true;
    for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
        if (used_mask >> edge_id & 1) continue;
        if (edges[edge_id].first != vertex) continue;
        if (brute_directed_dfs(
                edges[edge_id].second, edges, used_mask | (1 << edge_id))) {
            return true;
        }
    }
    return false;
}

bool brute_directed(int vertex_count, const std::vector<std::pair<int, int>>& edges) {
    if (edges.empty()) return true;
    for (int start = 0; start < vertex_count; start++) {
        if (brute_directed_dfs(start, edges, 0)) return true;
    }
    return false;
}

void validate_directed(
    const m1une::graph::EulerianTrail& trail,
    const std::vector<std::pair<int, int>>& edges
) {
    assert(trail.edge_ids.size() == edges.size());
    assert(trail.vertices.size() == edges.size() + 1);
    std::vector<char> used(edges.size(), false);
    for (int index = 0; index < int(edges.size()); index++) {
        int edge_id = trail.edge_ids[index];
        assert(0 <= edge_id && edge_id < int(edges.size()));
        assert(!used[edge_id]);
        used[edge_id] = true;
        assert(edges[edge_id].first == trail.vertices[index]);
        assert(edges[edge_id].second == trail.vertices[index + 1]);
    }
}

void randomized_test() {
    std::mt19937 random(712367);
    for (int test = 0; test < 350; test++) {
        int vertex_count = 1 + int(random() % 5);
        int edge_count = int(random() % 9);
        m1une::graph::Graph<> graph(vertex_count);
        std::vector<std::pair<int, int>> edges;
        for (int edge = 0; edge < edge_count; edge++) {
            int from = int(random() % vertex_count);
            int to = int(random() % vertex_count);
            graph.add_directed_edge(from, to);
            edges.emplace_back(from, to);
        }
        auto trail = m1une::graph::directed_eulerian_trail(graph);
        assert(trail.has_value() == brute_directed(vertex_count, edges));
        if (trail.has_value() && !edges.empty()) validate_directed(*trail, edges);
    }

    m1une::graph::Graph<> open(3);
    open.add_directed_edge(0, 1);
    open.add_directed_edge(1, 2);
    assert(m1une::graph::directed_eulerian_trail(open, 0).has_value());
    assert(!m1une::graph::directed_eulerian_trail(open, 1).has_value());
    open.erase_edge(1);
    auto active_only = m1une::graph::directed_eulerian_trail(open);
    assert(active_only.has_value() && active_only->edge_ids == std::vector<int>(1, 0));
}
#endif

void print(const std::optional<m1une::graph::EulerianTrail>& trail) {
    if (!trail.has_value()) {
        std::cout << "No\n";
        return;
    }
    std::cout << "Yes\n";
    for (int index = 0; index < int(trail->vertices.size()); index++) {
        if (index) std::cout << ' ';
        std::cout << trail->vertices[index];
    }
    std::cout << '\n';
    for (int index = 0; index < int(trail->edge_ids.size()); index++) {
        if (index) std::cout << ' ';
        std::cout << trail->edge_ids[index];
    }
    std::cout << '\n';
}

}  // namespace

int main() {
#ifndef NDEBUG
    randomized_test();
#endif
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_count;
    std::cin >> test_count;
    while (test_count--) {
        int vertex_count, edge_count;
        std::cin >> vertex_count >> edge_count;
        m1une::graph::Graph<> graph(vertex_count);
        for (int edge = 0; edge < edge_count; edge++) {
            int from, to;
            std::cin >> from >> to;
            graph.add_directed_edge(from, to);
        }
        print(m1une::graph::directed_eulerian_trail(graph));
    }
}
