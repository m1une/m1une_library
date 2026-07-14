#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include <algorithm>
#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <random>
#include <utility>
#include <vector>

#include "../../graph/two_edge_connected_components.hpp"

namespace {

#ifndef NDEBUG
int connected_component_count(
    int vertex_count,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<char>& alive,
    int skipped_edge
) {
    std::vector<std::vector<int>> adjacency(vertex_count);
    for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
        if (!alive[edge_id] || edge_id == skipped_edge) continue;
        auto [first, second] = edges[edge_id];
        adjacency[first].push_back(second);
        adjacency[second].push_back(first);
    }

    int count = 0;
    std::vector<char> visited(vertex_count, false);
    std::vector<int> stack;
    for (int root = 0; root < vertex_count; root++) {
        if (visited[root]) continue;
        count++;
        visited[root] = true;
        stack.push_back(root);
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            for (int to : adjacency[vertex]) {
                if (visited[to]) continue;
                visited[to] = true;
                stack.push_back(to);
            }
        }
    }
    return count;
}

std::vector<std::vector<int>> brute_components(
    int vertex_count,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<char>& alive,
    std::vector<char>& bridge
) {
    const int base_count = connected_component_count(vertex_count, edges, alive, -1);
    bridge.assign(edges.size(), false);
    for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
        if (!alive[edge_id]) continue;
        bridge[edge_id] =
            connected_component_count(vertex_count, edges, alive, edge_id) > base_count;
    }

    std::vector<std::vector<int>> adjacency(vertex_count);
    for (int edge_id = 0; edge_id < int(edges.size()); edge_id++) {
        if (!alive[edge_id] || bridge[edge_id]) continue;
        auto [first, second] = edges[edge_id];
        adjacency[first].push_back(second);
        adjacency[second].push_back(first);
    }

    std::vector<std::vector<int>> result;
    std::vector<char> visited(vertex_count, false);
    std::vector<int> stack;
    for (int root = 0; root < vertex_count; root++) {
        if (visited[root]) continue;
        result.emplace_back();
        visited[root] = true;
        stack.push_back(root);
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            result.back().push_back(vertex);
            for (int to : adjacency[vertex]) {
                if (visited[to]) continue;
                visited[to] = true;
                stack.push_back(to);
            }
        }
        std::sort(result.back().begin(), result.back().end());
    }
    std::sort(result.begin(), result.end());
    return result;
}

void randomized_test() {
    std::mt19937 random(712367);
    for (int iteration = 0; iteration < 500; iteration++) {
        const int vertex_count = 1 + int(random() % 7);
        const int edge_count = int(random() % 13);
        m1une::graph::Graph<> graph(vertex_count);
        std::vector<std::pair<int, int>> edges;
        std::vector<char> alive;
        for (int edge_id = 0; edge_id < edge_count; edge_id++) {
            int first = int(random() % vertex_count);
            int second = int(random() % vertex_count);
            graph.add_edge(first, second);
            edges.emplace_back(first, second);
            alive.push_back(true);
            if (random() % 7 == 0) {
                graph.erase_edge(edge_id);
                alive.back() = false;
            }
        }

        auto actual = m1une::graph::two_edge_connected_components(graph);
        std::vector<char> expected_bridge;
        auto expected = brute_components(vertex_count, edges, alive, expected_bridge);
        auto actual_components = actual.components;
        for (std::vector<int>& component : actual_components) {
            std::sort(component.begin(), component.end());
        }
        std::sort(actual_components.begin(), actual_components.end());
        assert(actual_components == expected);
        assert(actual.bridge == expected_bridge);

        assert(actual.bridge_ids.size() == actual.bridge_forest_edges.size());
        for (const auto& edge : actual.bridge_forest_edges) {
            assert(actual.is_bridge(edge.edge_id));
            assert(edge.from != edge.to);
        }
    }
}

void self_loop_edge_state_test() {
    m1une::graph::Graph<> graph(1);
    int loop = graph.add_edge(0, 0);
    assert(graph[0].size() == 2);
    assert(graph.edges().size() == 1);

    graph.erase_edge(loop);
    assert(!graph.is_edge_alive(loop));
    assert(graph.edges().empty());
    auto erased = m1une::graph::two_edge_connected_components(graph);
    assert(erased.component_count() == 1);
    assert(!erased.is_bridge(loop));

    graph.revive_edge(loop);
    assert(graph.is_edge_alive(loop));
    assert(graph.edges().size() == 1);
    auto active = m1une::graph::two_edge_connected_components(graph);
    assert(active.component_count() == 1);
    assert(!active.is_bridge(loop));
}
#endif

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    randomized_test();
    self_loop_edge_state_test();
#endif
    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int first, second;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    auto result = m1une::graph::two_edge_connected_components(graph);
    fast_output << result.component_count() << '\n';
    for (const std::vector<int>& component : result.components) {
        fast_output << component.size();
        for (int vertex : component) fast_output << ' ' << vertex;
        fast_output << '\n';
    }
}
