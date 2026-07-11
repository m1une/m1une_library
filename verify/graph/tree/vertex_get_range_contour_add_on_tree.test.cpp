#define PROBLEM "https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree"

#include "../../../graph/tree/range_contour_query.hpp"
#include "../../../monoid/xor.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

namespace {

std::vector<std::vector<int>> distances(
    const m1une::graph::Graph<>& graph
) {
    const int n = graph.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, -1));
    for (int start = 0; start < n; start++) {
        std::queue<int> queue;
        result[start][start] = 0;
        queue.push(start);
        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();
            for (const auto& edge : graph[vertex]) {
                if (result[start][edge.to] != -1) continue;
                result[start][edge.to] = result[start][vertex] + 1;
                queue.push(edge.to);
            }
        }
    }
    return result;
}

void randomized_test() {
    std::uint64_t state = 457;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 250; trial++) {
        int n = int(random() % 20) + 1;
        m1une::graph::Graph<> graph(n);
        for (int vertex = 1; vertex < n; vertex++) {
            graph.add_edge(vertex, int(random() % std::uint64_t(vertex)));
        }
        auto distance = distances(graph);
        std::vector<long long> value(n);
        for (long long& element : value) {
            element = static_cast<long long>(random() % 21) - 10;
        }

        m1une::tree::VertexGetRangeContourAdd<long long> contour(graph, value);
        assert(contour.size() == n);
        assert(!contour.empty());
        for (int query = 0; query < 250; query++) {
            int vertex = int(random() % std::uint64_t(n));
            int type = int(random() % 4);
            if (type == 0) {
                int left = int(random() % std::uint64_t(n + 3));
                int right = int(random() % std::uint64_t(n + 3));
                if (right < left) std::swap(left, right);
                long long delta = static_cast<long long>(random() % 21) - 10;
                contour.apply(vertex, left, right, delta);
                for (int other = 0; other < n; other++) {
                    if (left <= distance[vertex][other] &&
                        distance[vertex][other] < right) {
                        value[other] += delta;
                    }
                }
            } else if (type == 1) {
                long long delta = static_cast<long long>(random() % 21) - 10;
                contour.add(vertex, delta);
                value[vertex] += delta;
            } else if (type == 2) {
                long long replacement =
                    static_cast<long long>(random() % 21) - 10;
                contour.set(vertex, replacement);
                value[vertex] = replacement;
            } else {
                assert(contour.get(vertex) == value[vertex]);
            }
        }
        for (int vertex = 0; vertex < n; vertex++) {
            assert(contour.get(vertex) == value[vertex]);
        }
    }

    m1une::graph::Graph<> empty_graph;
    m1une::tree::VertexGetRangeContourAdd<long long> empty(empty_graph);
    assert(empty.empty());
}

void xor_group_test() {
    std::uint64_t state = 811;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    using Group = m1une::monoid::Xor<std::uint64_t>;
    for (int trial = 0; trial < 120; trial++) {
        int n = int(random() % 20) + 1;
        m1une::graph::Graph<> graph(n);
        for (int vertex = 1; vertex < n; vertex++) {
            graph.add_edge(vertex, int(random() % std::uint64_t(vertex)));
        }
        auto distance = distances(graph);
        std::vector<std::uint64_t> value(n);
        for (auto& element : value) element = random();

        m1une::tree::VertexGetRangeContourApply<Group> contour(graph, value);
        for (int query = 0; query < 150; query++) {
            int vertex = int(random() % std::uint64_t(n));
            if (random() & 1) {
                int left = int(random() % std::uint64_t(n + 3));
                int right = int(random() % std::uint64_t(n + 3));
                if (right < left) std::swap(left, right);
                std::uint64_t update = random();
                contour.apply(vertex, left, right, update);
                for (int other = 0; other < n; other++) {
                    if (left <= distance[vertex][other] &&
                        distance[vertex][other] < right) {
                        value[other] ^= update;
                    }
                }
            } else {
                assert(contour.get(vertex) == value[vertex]);
            }
        }
        for (int vertex = 0; vertex < n; vertex++) {
            assert(contour.get(vertex) == value[vertex]);
        }
    }
}

}  // namespace

int main() {
    randomized_test();
    xor_group_test();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, query_count;
    std::cin >> n >> query_count;
    std::vector<long long> initial(n);
    for (long long& value : initial) std::cin >> value;

    m1une::graph::Graph<> graph(n);
    for (int index = 0; index + 1 < n; index++) {
        int first, second;
        std::cin >> first >> second;
        graph.add_edge(first, second);
    }
    m1une::tree::VertexGetRangeContourAdd<long long> contour(graph, initial);

    while (query_count--) {
        int type, vertex;
        std::cin >> type >> vertex;
        if (type == 0) {
            int left, right;
            long long delta;
            std::cin >> left >> right >> delta;
            contour.apply(vertex, left, right, delta);
        } else {
            std::cout << contour.get(vertex) << '\n';
        }
    }
}
