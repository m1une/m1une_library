#define PROBLEM "https://judge.yosupo.jp/problem/three_edge_connected_components"

#include "../../graph/three_edge_connected_components.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <queue>
#include <vector>

namespace {

using Graph = m1une::graph::Graph<>;
using Result = m1une::graph::ThreeEdgeConnectedComponentsResult;

int naive_edge_connectivity(const Graph& graph, int source, int sink) {
    const int n = graph.size();
    std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));
    for (const auto& edge : graph.edges()) {
        if (edge.from == edge.to) continue;
        capacity[edge.from][edge.to]++;
        capacity[edge.to][edge.from]++;
    }

    int flow = 0;
    while (flow < 3) {
        std::vector<int> parent(n, -1);
        std::queue<int> queue;
        parent[source] = source;
        queue.push(source);
        while (!queue.empty() && parent[sink] == -1) {
            int vertex = queue.front();
            queue.pop();
            for (int to = 0; to < n; to++) {
                if (capacity[vertex][to] == 0 || parent[to] != -1) continue;
                parent[to] = vertex;
                queue.push(to);
            }
        }
        if (parent[sink] == -1) break;
        for (int vertex = sink; vertex != source; vertex = parent[vertex]) {
            capacity[parent[vertex]][vertex]--;
            capacity[vertex][parent[vertex]]++;
        }
        flow++;
    }
    return flow;
}

void validate(const Graph& graph) {
    Result result = m1une::graph::three_edge_connected_components(graph);
    assert(result.component_of_vertex.size() == std::size_t(graph.size()));

    std::vector<int> occurrence(graph.size(), 0);
    for (int component = 0; component < result.component_count(); component++) {
        assert(!result.components[component].empty());
        for (int vertex : result.components[component]) {
            assert(0 <= vertex && vertex < graph.size());
            assert(result.component_of_vertex[vertex] == component);
            occurrence[vertex]++;
        }
    }
    for (int count : occurrence) assert(count == 1);

    for (int first = 0; first < graph.size(); first++) {
        for (int second = 0; second < graph.size(); second++) {
            bool expected = first == second || naive_edge_connectivity(graph, first, second) >= 3;
            assert(result.same(first, second) == expected);
        }
    }
}

void test_fixed() {
    validate(Graph());
    validate(Graph(1));

    Graph parallel(2);
    parallel.add_edge(0, 1);
    parallel.add_edge(0, 1);
    int third = parallel.add_edge(0, 1);
    validate(parallel);
    assert(m1une::graph::three_edge_connected_components(parallel).same(0, 1));
    parallel.erase_edge(third);
    validate(parallel);
    assert(!m1une::graph::three_edge_connected_components(parallel).same(0, 1));
    parallel.revive_edge(third);
    validate(parallel);

    Graph complete(4);
    for (int from = 0; from < 4; from++) {
        for (int to = from + 1; to < 4; to++) complete.add_edge(from, to);
    }
    complete.add_edge(0, 0);
    validate(complete);
    assert(m1une::graph::three_edge_connected_components(complete).component_count() == 1);

    Graph joined(8);
    for (int offset : {0, 4}) {
        for (int from = offset; from < offset + 4; from++) {
            for (int to = from + 1; to < offset + 4; to++) joined.add_edge(from, to);
        }
    }
    joined.add_edge(0, 4);
    joined.add_edge(1, 5);
    validate(joined);
    auto joined_result = m1une::graph::three_edge_connected_components(joined);
    assert(joined_result.component_count() == 2);
    assert(joined_result.same(0, 3));
    assert(joined_result.same(4, 7));
    assert(!joined_result.same(0, 4));
}

void test_randomized() {
    std::uint64_t state = 123456789;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 9);
        Graph graph(n);
        int edge_count = int(random() % 26);
        for (int i = 0; i < edge_count && n > 0; i++) {
            int id = graph.add_edge(int(random() % n), int(random() % n));
            if (random() % 7 == 0) graph.erase_edge(id);
        }
        validate(graph);
    }
}

void test_deep_graph() {
    const int n = 50000;
    Graph graph(n);
    for (int vertex = 1; vertex < n; vertex++) graph.add_edge(vertex - 1, vertex);
    Result result = m1une::graph::three_edge_connected_components(graph);
    assert(result.component_count() == n);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    test_deep_graph();
    int n, edge_count;
    fast_input >> n >> edge_count;
    Graph graph(n);
    while (edge_count--) {
        int from, to;
        fast_input >> from >> to;
        graph.add_edge(from, to);
    }

    Result result = m1une::graph::three_edge_connected_components(graph);
    fast_output << result.component_count() << '\n';
    for (const auto& component : result.components) {
        fast_output << component.size();
        for (int vertex : component) fast_output << ' ' << vertex;
        fast_output << '\n';
    }
}
