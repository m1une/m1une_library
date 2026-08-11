#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../graph/tree/mo_on_tree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

namespace {

struct Path {
    std::vector<int> vertices;
    std::vector<int> edges;
};

Path naive_path(
    const std::vector<std::vector<std::pair<int, int>>>& adjacency,
    int from,
    int to
) {
    int n = int(adjacency.size());
    std::vector<int> previous(n, -1);
    std::vector<int> previous_edge(n, -1);
    std::queue<int> queue;
    previous[from] = from;
    queue.push(from);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        for (auto [next, edge_id] : adjacency[vertex]) {
            if (previous[next] != -1) continue;
            previous[next] = vertex;
            previous_edge[next] = edge_id;
            queue.push(next);
        }
    }

    Path result;
    for (int vertex = to; vertex != from; vertex = previous[vertex]) {
        result.vertices.push_back(vertex);
        result.edges.push_back(previous_edge[vertex]);
    }
    result.vertices.push_back(from);
    std::reverse(result.vertices.begin(), result.vertices.end());
    std::reverse(result.edges.begin(), result.edges.end());
    return result;
}

void test_empty_tree() {
    m1une::graph::Graph<int> graph;
    m1une::tree::MoOnTree<int> mo;
    mo.build(graph);
    assert(mo.empty());
    assert(mo.size() == 0);
    assert(mo.query_count() == 0);
    assert(mo.order().empty());
    mo.run(
        [](int) { assert(false); },
        [](int) { assert(false); },
        [](int) { assert(false); }
    );
}

void test_deep_path() {
    constexpr int n = 200000;
    m1une::graph::Graph<int> graph(n);
    for (int vertex = 1; vertex < n; ++vertex) {
        graph.add_edge(vertex - 1, vertex);
    }

    m1une::tree::MoOnTree<int> mo(graph, n - 1);
    mo.add_query(0, n - 1);
    mo.add_query(12345, 67890);
    mo.add_query(77777, 77777);
    std::vector<int> answer(3);
    int count = 0;
    mo.run(
        [&](int) { count++; },
        [&](int) { count--; },
        [&](int query) { answer[query] = count; }
    );
    assert(answer[0] == n);
    assert(answer[1] == 67890 - 12345 + 1);
    assert(answer[2] == 1);
}

void test_randomized() {
    std::uint64_t state = 0x3141592653589793ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; ++trial) {
        int n = 1 + int(random() % 55);
        int query_count = int(random() % 85);
        m1une::graph::Graph<int> graph(n);
        std::vector<std::vector<std::pair<int, int>>> adjacency(n);
        std::vector<long long> edge_weight(std::max(0, n - 1));
        for (int vertex = 1; vertex < n; ++vertex) {
            int parent = int(random() % vertex);
            int edge_id = graph.add_edge(parent, vertex);
            adjacency[parent].push_back({vertex, edge_id});
            adjacency[vertex].push_back({parent, edge_id});
            edge_weight[edge_id] = int(random() % 101) - 50;
        }

        std::vector<int> color(n);
        std::vector<long long> weight(n);
        for (int vertex = 0; vertex < n; ++vertex) {
            color[vertex] = int(random() % 13);
            weight[vertex] = int(random() % 101) - 50;
        }

        int root = int(random() % n);
        m1une::tree::MoOnTree<int> vertex_mo(graph, root);
        assert(vertex_mo.size() == n);
        assert(vertex_mo.root == root);
        assert(int(vertex_mo.tour.size()) == 2 * n);
        std::vector<int> occurrence(n);
        for (int vertex : vertex_mo.tour) occurrence[vertex]++;
        for (int vertex = 0; vertex < n; ++vertex) {
            assert(occurrence[vertex] == 2);
            assert(vertex_mo.tour[vertex_mo.entry[vertex]] == vertex);
            assert(vertex_mo.tour[vertex_mo.exit[vertex]] == vertex);
            assert(vertex_mo.entry[vertex] < vertex_mo.exit[vertex]);
        }

        vertex_mo.reserve(query_count);
        std::vector<Path> paths;
        paths.reserve(query_count);
        for (int query = 0; query < query_count; ++query) {
            int from = int(random() % n);
            int to = int(random() % n);
            assert(vertex_mo.add_query(from, to) == query);
            paths.push_back(naive_path(adjacency, from, to));
            const auto& stored = vertex_mo.queries().back();
            assert(stored.id == query);
            assert(stored.from == from && stored.to == to);
            assert(!stored.edge);
        }

        std::vector<int> order = vertex_mo.order();
        std::sort(order.begin(), order.end());
        for (int query = 0; query < query_count; ++query) {
            assert(order[query] == query);
        }

        std::vector<int> frequency(13);
        std::vector<long long> answer_sum(query_count);
        std::vector<int> answer_distinct(query_count);
        long long sum = 0;
        int distinct = 0;
        vertex_mo.run(
            [&](int vertex) {
                sum += weight[vertex];
                if (frequency[color[vertex]]++ == 0) distinct++;
            },
            [&](int vertex) {
                sum -= weight[vertex];
                if (--frequency[color[vertex]] == 0) distinct--;
            },
            [&](int query) {
                answer_sum[query] = sum;
                answer_distinct[query] = distinct;
            },
            trial % 3 == 0 ? 1 + int(random() % (2 * n)) : 0
        );

        for (int query = 0; query < query_count; ++query) {
            long long expected_sum = 0;
            std::vector<char> seen(13, false);
            int expected_distinct = 0;
            for (int vertex : paths[query].vertices) {
                expected_sum += weight[vertex];
                if (!seen[color[vertex]]) {
                    seen[color[vertex]] = true;
                    expected_distinct++;
                }
            }
            assert(answer_sum[query] == expected_sum);
            assert(answer_distinct[query] == expected_distinct);
        }

        m1une::tree::MoOnTree<int> edge_mo(graph, root);
        edge_mo.reserve(query_count);
        for (int query = 0; query < query_count; ++query) {
            int from = paths[query].vertices.front();
            int to = paths[query].vertices.back();
            assert(edge_mo.add_edge_query(from, to) == query);
            assert(edge_mo.queries().back().edge);
        }

        std::vector<long long> edge_answer(query_count);
        long long edge_sum = 0;
        edge_mo.run(
            [&](int child) {
                int edge_id = edge_mo.parent_edge(child);
                assert(edge_id != -1);
                edge_sum += edge_weight[edge_id];
            },
            [&](int child) {
                int edge_id = edge_mo.parent_edge(child);
                assert(edge_id != -1);
                edge_sum -= edge_weight[edge_id];
            },
            [&](int query) { edge_answer[query] = edge_sum; }
        );
        for (int query = 0; query < query_count; ++query) {
            long long expected = 0;
            for (int edge_id : paths[query].edges) {
                expected += edge_weight[edge_id];
            }
            assert(edge_answer[query] == expected);
        }

        vertex_mo.clear();
        assert(vertex_mo.query_count() == 0);
        assert(vertex_mo.order().empty());
    }
}

}  // namespace

int main() {
    test_empty_tree();
    test_deep_path();
    test_randomized();

    long long first, second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
