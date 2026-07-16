#define PROBLEM "https://judge.yosupo.jp/problem/incremental_scc"

#include "../../graph/incremental_scc.hpp"

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "../../ds/dsu/dsu.hpp"
#include "../../graph/scc.hpp"
#include "../../math/modint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using Graph = m1une::graph::Graph<>;

void validate(const Graph& graph, const std::vector<std::pair<int, int>>& edges) {
    const int n = graph.size();
    const int m = graph.edge_count();
    assert(int(edges.size()) == m);
    const std::vector<int> actual = m1une::graph::incremental_scc(graph);
    assert(int(actual.size()) == m);

    std::vector<int> expected(m, m + 1);
    m1une::ds::Dsu replay(n);
    for (int time = 1; time <= m; time++) {
        Graph prefix(n);
        for (int edge_id = 0; edge_id < time; edge_id++) {
            if (!graph.is_edge_alive(edge_id)) continue;
            prefix.add_directed_edge(
                edges[edge_id].first,
                edges[edge_id].second
            );
        }
        const auto components =
            m1une::graph::strongly_connected_components(prefix);
        for (int edge_id = 0; edge_id < m; edge_id++) {
            if (edge_id >= time || !graph.is_edge_alive(edge_id)) continue;
            if (expected[edge_id] == m + 1 && components.same(
                    edges[edge_id].first,
                    edges[edge_id].second
                )) {
                expected[edge_id] = time;
            }
            if (actual[edge_id] == time) {
                replay.merge(edges[edge_id].first, edges[edge_id].second);
            }
        }
        for (int first = 0; first < n; first++) {
            for (int second = 0; second < n; second++) {
                assert(replay.same(first, second) ==
                       components.same(first, second));
            }
        }
    }
    assert(actual == expected);
}

void test_fixed() {
    Graph empty(3);
    validate(empty, std::vector<std::pair<int, int>>());

    Graph graph(4);
    std::vector<std::pair<int, int>> edges;
    edges.emplace_back(0, 1);
    graph.add_directed_edge(0, 1);
    edges.emplace_back(1, 2);
    graph.add_directed_edge(1, 2);
    edges.emplace_back(2, 0);
    graph.add_directed_edge(2, 0);
    edges.emplace_back(2, 3);
    graph.add_directed_edge(2, 3);
    edges.emplace_back(3, 3);
    graph.add_directed_edge(3, 3);
    validate(graph, edges);
    const std::vector<int> time = m1une::graph::incremental_scc(graph);
    assert(time[0] == 3);
    assert(time[1] == 3);
    assert(time[2] == 3);
    assert(time[3] == 6);
    assert(time[4] == 5);

    graph.erase_edge(2);
    validate(graph, edges);
}

void test_randomized() {
    std::uint64_t state = 20260718;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        const int n = 1 + int(random() % 8);
        const int m = int(random() % 17);
        Graph graph(n);
        std::vector<std::pair<int, int>> edges;
        edges.reserve(m);
        for (int edge_id = 0; edge_id < m; edge_id++) {
            const int from = int(random() % n);
            const int to = int(random() % n);
            edges.emplace_back(from, to);
            const int id = graph.add_directed_edge(from, to);
            if (random() % 7 == 0) graph.erase_edge(id);
        }
        validate(graph, edges);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    using Mint = m1une::math::modint998244353;
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;

    std::vector<Mint> weight(vertex_count);
    for (Mint& value : weight) {
        int input;
        fast_input >> input;
        value = Mint(input);
    }

    Graph graph(vertex_count);
    std::vector<std::pair<int, int>> edges;
    edges.reserve(edge_count);
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        int from, to;
        fast_input >> from >> to;
        edges.emplace_back(from, to);
        graph.add_directed_edge(from, to);
    }

    const std::vector<int> merge_time =
        m1une::graph::incremental_scc(graph);
    std::vector<std::vector<int>> edges_by_time(edge_count + 1);
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        if (merge_time[edge_id] <= edge_count) {
            edges_by_time[merge_time[edge_id]].push_back(edge_id);
        }
    }

    m1une::ds::Dsu components(vertex_count);
    Mint answer = 0;
    for (int time = 1; time <= edge_count; time++) {
        for (int edge_id : edges_by_time[time]) {
            const int first = components.leader(edges[edge_id].first);
            const int second = components.leader(edges[edge_id].second);
            if (first == second) continue;
            answer += weight[first] * weight[second];
            components.merge(first, second, [&](int leader, int absorbed) {
                weight[leader] += weight[absorbed];
            });
        }
        fast_output << answer.val() << '\n';
    }
}
