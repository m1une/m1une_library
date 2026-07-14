#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"

#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include "../../graph/eulerian_trail.hpp"

namespace {

#ifndef NDEBUG
bool brute_undirected_dfs(
    int vertex,
    const std::vector<std::pair<int, int>>& edges,
    int used_mask
) {
    if (used_mask == (1 << int(edges.size())) - 1) return true;
    for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
        if (used_mask >> edge_id & 1) continue;
        auto [first, second] = edges[edge_id];
        if (first == vertex &&
            brute_undirected_dfs(second, edges, used_mask | (1 << edge_id))) {
            return true;
        }
        if (second == vertex && second != first &&
            brute_undirected_dfs(first, edges, used_mask | (1 << edge_id))) {
            return true;
        }
    }
    return false;
}

bool brute_undirected(int vertex_count, const std::vector<std::pair<int, int>>& edges) {
    if (edges.empty()) return true;
    for (int start = 0; start < vertex_count; start++) {
        if (brute_undirected_dfs(start, edges, 0)) return true;
    }
    return false;
}

void validate_undirected(
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
        auto [first, second] = edges[edge_id];
        int from = trail.vertices[index];
        int to = trail.vertices[index + 1];
        assert((first == from && second == to) || (first == to && second == from));
    }
}

void randomized_test() {
    std::mt19937 random(891011);
    for (int test = 0; test < 350; test++) {
        int vertex_count = 1 + int(random() % 5);
        int edge_count = int(random() % 9);
        m1une::graph::Graph<> graph(vertex_count);
        std::vector<std::pair<int, int>> edges;
        for (int edge = 0; edge < edge_count; edge++) {
            int first = int(random() % vertex_count);
            int second = int(random() % vertex_count);
            graph.add_edge(first, second);
            edges.emplace_back(first, second);
        }
        auto trail = m1une::graph::undirected_eulerian_trail(graph);
        assert(trail.has_value() == brute_undirected(vertex_count, edges));
        if (trail.has_value() && !edges.empty()) validate_undirected(*trail, edges);
    }

    m1une::graph::Graph<> loops(2);
    int first = loops.add_edge(0, 0);
    int erased = loops.add_edge(0, 1);
    loops.erase_edge(erased);
    auto active_only = m1une::graph::undirected_eulerian_trail(loops);
    assert(active_only.has_value() && active_only->edge_ids == std::vector<int>(1, first));
    assert(active_only->is_circuit());
}
#endif

void print(
    const std::optional<m1une::graph::EulerianTrail>& trail,
    m1une::utilities::FastOutput& fast_output
) {
    if (!trail.has_value()) {
        fast_output << "No\n";
        return;
    }
    fast_output << "Yes\n";
    for (int index = 0; index < int(trail->vertices.size()); index++) {
        if (index) fast_output << ' ';
        fast_output << trail->vertices[index];
    }
    fast_output << '\n';
    for (int index = 0; index < int(trail->edge_ids.size()); index++) {
        if (index) fast_output << ' ';
        fast_output << trail->edge_ids[index];
    }
    fast_output << '\n';
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    randomized_test();
#endif
    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        int vertex_count, edge_count;
        fast_input >> vertex_count >> edge_count;
        m1une::graph::Graph<> graph(vertex_count);
        for (int edge = 0; edge < edge_count; edge++) {
            int first, second;
            fast_input >> first >> second;
            graph.add_edge(first, second);
        }
        print(m1une::graph::undirected_eulerian_trail(graph), fast_output);
    }
}
