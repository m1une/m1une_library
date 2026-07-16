#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_C"

#include "../../graph/bfs.hpp"
#include "../../graph/graph.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace {

void test_randomized() {
    std::uint64_t state = 0x13198a2e03707344ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 400; trial++) {
        int size = 1 + int(random() % 50);
        m1une::graph::Graph<> graph(size);
        for (int from = 0; from < size; from++) {
            for (int to = 0; to < size; to++) {
                if (from == to || random() % 17 != 0) continue;
                int edge = graph.add_directed_edge(from, to);
                if (random() % 11 == 0) graph.erase_edge(edge);
            }
        }

        int source_count = 1 + int(random() % size);
        std::vector<int> sources;
        for (int i = 0; i < source_count; i++) {
            sources.push_back(int(random() % size));
        }

        std::vector<std::pair<int, int>> callback_visits;
        auto callback_result = m1une::graph::bfs(
            graph,
            sources,
            [&](int vertex, int parent) {
                callback_visits.emplace_back(vertex, parent);
            }
        );
        auto ordinary_result = m1une::graph::bfs(graph, sources);
        assert(callback_result.dist == ordinary_result.dist);
        assert(callback_result.parent == ordinary_result.parent);
        assert(callback_result.parent_edge == ordinary_result.parent_edge);

        std::vector<char> seen(size, false);
        int previous_distance = -1;
        for (auto [vertex, parent] : callback_visits) {
            assert(!seen[vertex]);
            seen[vertex] = true;
            assert(callback_result.reachable(vertex));
            assert(parent == callback_result.parent[vertex]);
            assert(previous_distance <= callback_result.dist[vertex]);
            previous_distance = callback_result.dist[vertex];
        }
        for (int vertex = 0; vertex < size; vertex++) {
            assert(seen[vertex] == callback_result.reachable(vertex));
        }

        int source = int(random() % size);
        std::vector<int> single_order;
        auto single = m1une::graph::bfs(
            graph,
            source,
            [&](int vertex) { single_order.push_back(vertex); }
        );
        assert(single.dist == m1une::graph::bfs(graph, source).dist);
        assert(!single_order.empty() && single_order.front() == source);
    }
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

    std::vector<int> callback_order;
    auto result = m1une::graph::bfs(
        graph,
        0,
        [&](int vertex) { callback_order.push_back(vertex); }
    );
    assert(int(callback_order.size()) ==
           int(std::count_if(
               result.dist.begin(),
               result.dist.end(),
               [](int distance) { return distance != -1; }
           )));
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        fast_output << vertex + 1 << ' ' << result.dist[vertex] << '\n';
    }
}
