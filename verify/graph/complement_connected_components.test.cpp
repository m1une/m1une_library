#define PROBLEM "https://judge.yosupo.jp/problem/connected_components_of_complement_graph"

#include "../../graph/complement_connected_components.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <queue>
#include <vector>

namespace {

using Graph = m1une::graph::Graph<>;
using Result = m1une::graph::ConnectedComponents;

std::vector<int> naive_components(const Graph& graph) {
    const int size = graph.size();
    std::vector<std::vector<char>> adjacent(size, std::vector<char>(size, false));
    for (const auto& edge : graph.edges()) {
        if (edge.from == edge.to) continue;
        adjacent[edge.from][edge.to] = true;
        adjacent[edge.to][edge.from] = true;
    }

    std::vector<int> component(size, -1);
    std::queue<int> queue;
    int component_count = 0;
    for (int root = 0; root < size; root++) {
        if (component[root] != -1) continue;
        component[root] = component_count;
        queue.push(root);
        while (!queue.empty()) {
            const int vertex = queue.front();
            queue.pop();
            for (int to = 0; to < size; to++) {
                if (to == vertex || adjacent[vertex][to] || component[to] != -1) continue;
                component[to] = component_count;
                queue.push(to);
            }
        }
        component_count++;
    }
    return component;
}

void validate(const Graph& graph) {
    Result result = m1une::graph::complement_connected_components(graph);
    std::vector<int> expected = naive_components(graph);
    assert(int(result.comp.size()) == graph.size());
    assert(result.count == int(result.groups.size()));

    std::vector<int> occurrence(graph.size(), 0);
    for (int component = 0; component < result.count; component++) {
        assert(!result.groups[component].empty());
        for (int vertex : result.groups[component]) {
            assert(0 <= vertex && vertex < graph.size());
            assert(result.comp[vertex] == component);
            occurrence[vertex]++;
        }
    }
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        assert(occurrence[vertex] == 1);
        for (int other = 0; other < graph.size(); other++) {
            assert(result.same(vertex, other) == (expected[vertex] == expected[other]));
        }
    }
}

void test_fixed() {
    validate(Graph());
    validate(Graph(1));

    Graph no_edges(10);
    validate(no_edges);
    assert(m1une::graph::complement_connected_components(no_edges).count == 1);

    Graph complete(9);
    for (int first = 0; first < 9; first++) {
        for (int second = first + 1; second < 9; second++) {
            complete.add_edge(first, second);
        }
    }
    validate(complete);
    assert(m1une::graph::complement_connected_components(complete).count == 9);

    Graph star(8);
    for (int vertex = 1; vertex < 8; vertex++) star.add_edge(0, vertex);
    validate(star);
    assert(m1une::graph::complement_connected_components(star).count == 2);

    Graph mixed(5);
    mixed.add_directed_edge(0, 1);
    mixed.add_edge(0, 1);
    int inactive = mixed.add_edge(1, 2);
    mixed.erase_edge(inactive);
    mixed.add_edge(3, 3);
    validate(mixed);
}

void test_randomized() {
    std::uint64_t state = 0x8cb92baa3f3d8dd7ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        const int size = int(random() % 13);
        Graph graph(size);
        for (int first = 0; first < size; first++) {
            for (int second = first + 1; second < size; second++) {
                if (random() % 2 == 0) continue;
                if (random() & 1) {
                    graph.add_edge(first, second);
                } else {
                    graph.add_directed_edge(first, second);
                }
                if (random() % 11 == 0) graph.add_edge(first, second);
            }
        }
        validate(graph);
    }
}

void test_large_sparse_graph() {
    const int size = 100000;
    Graph graph(size);
    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1, vertex);
    Result result = m1une::graph::complement_connected_components(graph);
    assert(result.count == 1);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    test_large_sparse_graph();
    int size, edge_count;
    fast_input >> size >> edge_count;
    Graph graph(size);
    while (edge_count--) {
        int first, second;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    Result result = m1une::graph::complement_connected_components(graph);
    fast_output << result.count << '\n';
    for (const auto& component : result.groups) {
        fast_output << component.size();
        for (int vertex : component) fast_output << ' ' << vertex;
        fast_output << '\n';
    }
}
