#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../../graph/biconnected_components.hpp"

namespace {

#ifndef NDEBUG
bool connected_after_removal(
    const std::vector<std::vector<int>>& adjacent,
    int mask,
    int removed
) {
    mask &= ~(1 << removed);
    if (mask == 0) return true;
    const int start = __builtin_ctz(unsigned(mask));
    int reached = 0;
    std::vector<int> stack(1, start);
    reached |= 1 << start;
    while (!stack.empty()) {
        int vertex = stack.back();
        stack.pop_back();
        for (int to = 0; to < int(adjacent.size()); to++) {
            if (!adjacent[vertex][to] || !(mask >> to & 1) || (reached >> to & 1)) continue;
            reached |= 1 << to;
            stack.push_back(to);
        }
    }
    return reached == mask;
}

std::vector<int> brute_components(const std::vector<std::vector<int>>& adjacent) {
    const int n = int(adjacent.size());
    std::vector<int> candidate;
    for (int mask = 1; mask < (1 << n); mask++) {
        if (!connected_after_removal(adjacent, mask, n)) continue;
        bool biconnected = true;
        for (int vertex = 0; vertex < n; vertex++) {
            if ((mask >> vertex & 1) && !connected_after_removal(adjacent, mask, vertex)) {
                biconnected = false;
            }
        }
        if (biconnected) candidate.push_back(mask);
    }

    std::vector<int> maximal;
    for (int mask : candidate) {
        bool contained = false;
        for (int other : candidate) {
            if (mask != other && (mask & other) == mask) contained = true;
        }
        if (!contained) maximal.push_back(mask);
    }
    std::sort(maximal.begin(), maximal.end());
    return maximal;
}

void randomized_test() {
    std::mt19937 random(712367);
    for (int iteration = 0; iteration < 300; iteration++) {
        const int n = 1 + int(random() % 7);
        m1une::graph::Graph<> graph(n);
        std::vector<std::vector<int>> adjacent(n, std::vector<int>(n, 0));
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                if (random() % 3 == 0) {
                    graph.add_edge(first, second);
                    adjacent[first][second] = adjacent[second][first] = 1;
                }
            }
        }

        auto result = m1une::graph::biconnected_components(graph);
        std::vector<int> actual;
        for (const std::vector<int>& component : result.components) {
            int mask = 0;
            for (int vertex : component) mask |= 1 << vertex;
            actual.push_back(mask);
        }
        std::sort(actual.begin(), actual.end());
        assert(actual == brute_components(adjacent));

        std::vector<int> edge_seen(graph.edge_count(), 0);
        for (int component = 0; component < result.component_count(); component++) {
            for (int edge_id : result.edge_components[component]) {
                assert(result.component_of_edge[edge_id] == component);
                edge_seen[edge_id]++;
            }
        }
        for (int count : edge_seen) assert(count == 1);
    }
}

void parallel_and_inactive_test() {
    m1une::graph::Graph<> graph(4);
    int first = graph.add_edge(0, 1);
    int second = graph.add_edge(0, 1);
    int erased = graph.add_edge(1, 2);
    graph.erase_edge(erased);

    auto result = m1une::graph::biconnected_components(graph);
    assert(result.component_count() == 3);
    assert(result.component_of_edge[first] == result.component_of_edge[second]);
    assert(result.component_of_edge[erased] == -1);
    assert(!result.is_articulation(0));
    assert(!result.is_articulation(1));
    assert(result.vertex_components[2].size() == 1);
    assert(result.vertex_components[3].size() == 1);
}
#endif

}  // namespace

int main() {
#ifndef NDEBUG
    randomized_test();
    parallel_and_inactive_test();
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

    auto result = m1une::graph::biconnected_components(graph);
    std::cout << result.component_count() << '\n';
    for (const std::vector<int>& component : result.components) {
        std::cout << component.size();
        for (int vertex : component) std::cout << ' ' << vertex;
        std::cout << '\n';
    }
}
