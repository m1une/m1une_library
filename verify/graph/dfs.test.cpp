#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_B"

#include "../../graph/dfs.hpp"
#include "../../graph/graph.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace {

template <class T>
m1une::graph::DfsResult recursive_dfs(
    const m1une::graph::Graph<T>& graph,
    const std::vector<int>& sources,
    bool complete_forest
) {
    int size = graph.size();
    m1une::graph::DfsResult result;
    result.depth.assign(size, -1);
    result.parent.assign(size, -1);
    result.parent_edge.assign(size, -1);
    result.root.assign(size, -1);
    result.tin.assign(size, -1);
    result.tout.assign(size, -1);
    int timer = 0;

    auto visit = [&](auto&& self, int vertex) -> void {
        result.tin[vertex] = ++timer;
        result.preorder.push_back(vertex);
        for (const auto& edge : graph[vertex]) {
            if (!edge.alive || result.depth[edge.to] != -1) continue;
            result.depth[edge.to] = result.depth[vertex] + 1;
            result.parent[edge.to] = vertex;
            result.parent_edge[edge.to] = edge.id;
            result.root[edge.to] = result.root[vertex];
            self(self, edge.to);
        }
        result.tout[vertex] = ++timer;
        result.postorder.push_back(vertex);
    };
    auto start = [&](int source) {
        if (result.depth[source] != -1) return;
        result.depth[source] = 0;
        result.root[source] = source;
        result.roots.push_back(source);
        visit(visit, source);
    };
    for (int source : sources) start(source);
    if (complete_forest) {
        for (int vertex = 0; vertex < size; vertex++) start(vertex);
    }
    return result;
}

void assert_equal(
    const m1une::graph::DfsResult& actual,
    const m1une::graph::DfsResult& expected
) {
    assert(actual.depth == expected.depth);
    assert(actual.parent == expected.parent);
    assert(actual.parent_edge == expected.parent_edge);
    assert(actual.root == expected.root);
    assert(actual.tin == expected.tin);
    assert(actual.tout == expected.tout);
    assert(actual.preorder == expected.preorder);
    assert(actual.postorder == expected.postorder);
    assert(actual.roots == expected.roots);
    assert(actual.component_count() == int(actual.roots.size()));

    int size = int(actual.depth.size());
    for (int vertex = 0; vertex < size; vertex++) {
        assert(actual.reachable(vertex) == (actual.depth[vertex] != -1));
        if (!actual.reachable(vertex)) continue;
        std::vector<int> path = actual.path(vertex);
        assert(path.front() == actual.root[vertex]);
        assert(path.back() == vertex);
        assert(int(path.size()) == actual.depth[vertex] + 1);
    }
    for (int ancestor = 0; ancestor < size; ancestor++) {
        for (int vertex = 0; vertex < size; vertex++) {
            bool expected_ancestor = false;
            if (actual.reachable(vertex)) {
                for (int current = vertex; current != -1;
                     current = actual.parent[current]) {
                    expected_ancestor |= current == ancestor;
                }
            }
            assert(
                actual.is_ancestor(ancestor, vertex) == expected_ancestor
            );
        }
    }
}

void assert_callback_visits(
    const std::vector<std::pair<int, int>>& visits,
    const m1une::graph::DfsResult& result
) {
    assert(visits.size() == result.preorder.size());
    for (int i = 0; i < int(visits.size()); i++) {
        int vertex = visits[i].first;
        assert(vertex == result.preorder[i]);
        assert(visits[i].second == result.parent[vertex]);
    }
}

void test_randomized() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; trial++) {
        int size = int(random() % 25);
        m1une::graph::Graph<> graph(size);
        for (int from = 0; from < size; from++) {
            for (int to = 0; to < size; to++) {
                if (from == to || random() % 11 != 0) continue;
                int edge = graph.add_directed_edge(from, to);
                if (random() % 9 == 0) graph.erase_edge(edge);
            }
        }
        if (size == 0) {
            assert_equal(
                m1une::graph::dfs(graph),
                recursive_dfs(graph, std::vector<int>(), true)
            );
            continue;
        }

        int source = int(random() % size);
        std::vector<int> single_source(1, source);
        assert_equal(
            m1une::graph::dfs(graph, source),
            recursive_dfs(graph, single_source, false)
        );
        std::vector<std::pair<int, int>> single_callback_visits;
        auto single_callback_result = m1une::graph::dfs(
            graph,
            source,
            [&](int vertex, int parent) {
                single_callback_visits.emplace_back(vertex, parent);
            }
        );
        assert_callback_visits(
            single_callback_visits,
            single_callback_result
        );
        assert_equal(
            single_callback_result,
            recursive_dfs(graph, single_source, false)
        );

        std::vector<int> sources;
        int source_count = int(random() % (size + 1));
        for (int i = 0; i < source_count; i++) {
            sources.push_back(int(random() % size));
        }
        assert_equal(
            m1une::graph::dfs(graph, sources),
            recursive_dfs(graph, sources, false)
        );
        std::vector<std::pair<int, int>> multi_callback_visits;
        auto multi_callback_result = m1une::graph::dfs(
            graph,
            sources,
            [&](int vertex, int parent) {
                multi_callback_visits.emplace_back(vertex, parent);
            }
        );
        assert_callback_visits(
            multi_callback_visits,
            multi_callback_result
        );
        assert_equal(
            multi_callback_result,
            recursive_dfs(graph, sources, false)
        );
        assert_equal(
            m1une::graph::dfs(graph),
            recursive_dfs(graph, std::vector<int>(), true)
        );
        std::vector<std::pair<int, int>> forest_callback_visits;
        auto forest_callback_result = m1une::graph::dfs(
            graph,
            [&](int vertex, int parent) {
                forest_callback_visits.emplace_back(vertex, parent);
            }
        );
        assert_callback_visits(
            forest_callback_visits,
            forest_callback_result
        );
        assert_equal(
            forest_callback_result,
            recursive_dfs(graph, std::vector<int>(), true)
        );
    }

    constexpr int deep_size = 100'000;
    m1une::graph::Graph<> chain(deep_size);
    for (int vertex = 1; vertex < deep_size; vertex++) {
        chain.add_directed_edge(vertex - 1, vertex);
    }
    int callback_count = 0;
    auto deep = m1une::graph::dfs(
        chain,
        0,
        [&](int) { callback_count++; }
    );
    assert(callback_count == deep_size);
    assert(deep.depth.back() == deep_size - 1);
    assert(deep.is_ancestor(0, deep_size - 1));
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int vertex_count = 0;
    fast_input >> vertex_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int i = 0; i < vertex_count; i++) {
        int vertex = 0;
        int degree = 0;
        fast_input >> vertex >> degree;
        vertex--;
        while (degree--) {
            int to = 0;
            fast_input >> to;
            graph.add_directed_edge(vertex, to - 1);
        }
    }

    m1une::graph::DfsResult result = m1une::graph::dfs(graph);
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        fast_output << vertex + 1 << ' ' << result.tin[vertex] << ' '
                    << result.tout[vertex] << '\n';
    }
}
