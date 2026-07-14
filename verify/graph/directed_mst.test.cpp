#define PROBLEM "https://judge.yosupo.jp/problem/directedmst"

#include "../../graph/directed_mst.hpp"

#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <optional>
#include <queue>
#include <random>
#include <vector>

namespace {

struct TestEdge {
    int from;
    int to;
    long long cost;
    bool alive;
};

std::optional<long long> brute_directed_mst(
    int n,
    int root,
    const std::vector<TestEdge>& edges
) {
    std::vector<std::vector<int>> incoming(n);
    for (int index = 0; index < int(edges.size()); index++) {
        if (edges[index].alive && edges[index].from != edges[index].to) {
            incoming[edges[index].to].push_back(index);
        }
    }
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex != root && incoming[vertex].empty()) return std::nullopt;
    }

    std::vector<int> vertices;
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex != root) vertices.push_back(vertex);
    }

    std::optional<long long> answer;
    std::vector<int> chosen(n, -1);
    auto search = [&](auto&& self, int index, long long cost) -> void {
        if (index == int(vertices.size())) {
            std::vector<std::vector<int>> tree(n);
            for (int vertex : vertices) {
                tree[edges[chosen[vertex]].from].push_back(vertex);
            }
            std::vector<char> reached(n, false);
            std::queue<int> queue;
            reached[root] = true;
            queue.push(root);
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                for (int to : tree[vertex]) {
                    if (reached[to]) continue;
                    reached[to] = true;
                    queue.push(to);
                }
            }
            for (char value : reached) {
                if (!value) return;
            }
            if (!answer || cost < *answer) answer = cost;
            return;
        }

        int vertex = vertices[index];
        for (int edge_index : incoming[vertex]) {
            chosen[vertex] = edge_index;
            self(self, index + 1, cost + edges[edge_index].cost);
        }
    };
    search(search, 0, 0);
    return answer;
}

std::optional<long long> brute_rootless_directed_mst(
    int n,
    const std::vector<TestEdge>& edges
) {
    std::optional<long long> answer;
    for (int root = 0; root < n; root++) {
        auto candidate = brute_directed_mst(n, root, edges);
        if (candidate && (!answer || *candidate < *answer)) answer = candidate;
    }
    return answer;
}

void validate_result(
    const m1une::graph::DirectedMinimumSpanningTree<long long>& result,
    int n,
    int root,
    const std::vector<TestEdge>& edges
) {
    assert(result.root == root);
    assert(int(result.parent.size()) == n);
    assert(int(result.parent_edge.size()) == n);
    assert(int(result.edges.size()) == n - 1);
    assert(result.parent[root] == root);
    assert(result.parent_edge[root] == -1);

    long long total = 0;
    std::vector<std::vector<int>> tree(n);
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex == root) continue;
        int edge_id = result.parent_edge[vertex];
        assert(0 <= edge_id && edge_id < int(edges.size()));
        const auto& edge = edges[edge_id];
        assert(edge.alive);
        assert(edge.to == vertex);
        assert(edge.from == result.parent[vertex]);
        total += edge.cost;
        tree[edge.from].push_back(vertex);
    }
    assert(total == result.cost);

    std::vector<char> reached(n, false);
    std::queue<int> queue;
    reached[root] = true;
    queue.push(root);
    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        for (int to : tree[vertex]) {
            assert(!reached[to]);
            reached[to] = true;
            queue.push(to);
        }
    }
    for (char value : reached) assert(value);
}

void randomized_test() {
    std::mt19937 random(20260711);
    for (int test = 0; test < 500; test++) {
        int n = std::uniform_int_distribution<int>(1, 5)(random);
        int root = std::uniform_int_distribution<int>(0, n - 1)(random);
        int m = std::uniform_int_distribution<int>(0, 10)(random);

        m1une::graph::Graph<long long> graph(n);
        std::vector<TestEdge> edges;
        for (int index = 0; index < m; index++) {
            int from = std::uniform_int_distribution<int>(0, n - 1)(random);
            int to = std::uniform_int_distribution<int>(0, n - 1)(random);
            long long cost = std::uniform_int_distribution<int>(-5, 10)(random);
            int id = graph.add_directed_edge(from, to, cost);
            bool alive = std::uniform_int_distribution<int>(0, 8)(random) != 0;
            graph.set_edge_alive(id, alive);
            edges.push_back(TestEdge{from, to, cost, alive});
        }

        auto expected = brute_directed_mst(n, root, edges);
        auto actual = m1une::graph::directed_mst(graph, root);
        assert(expected.has_value() == actual.has_value());
        if (actual) {
            assert(actual->cost == *expected);
            validate_result(*actual, n, root, edges);
        }

        auto rootless_expected = brute_rootless_directed_mst(n, edges);
        auto rootless_actual = m1une::graph::directed_mst(graph);
        assert(rootless_expected.has_value() == rootless_actual.has_value());
        if (rootless_actual) {
            assert(rootless_actual->cost == *rootless_expected);
            validate_result(
                *rootless_actual,
                n,
                rootless_actual->root,
                edges
            );
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    randomized_test();
    int n, m, root;
    fast_input >> n >> m >> root;
    m1une::graph::Graph<long long> graph(n);
    for (int index = 0; index < m; index++) {
        int from, to;
        long long cost;
        fast_input >> from >> to >> cost;
        graph.add_directed_edge(from, to, cost);
    }

    auto answer = m1une::graph::directed_mst(graph, root);
    assert(answer.has_value());
    fast_output << answer->cost << '\n';
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex) fast_output << ' ';
        fast_output << answer->parent[vertex];
    }
    fast_output << '\n';
}
