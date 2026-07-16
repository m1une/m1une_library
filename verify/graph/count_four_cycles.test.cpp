#define PROBLEM "https://judge.yosupo.jp/problem/counting_c4"

#include "../../graph/count_four_cycles.hpp"
#include "../../graph/graph.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace {

template <class T>
std::vector<long long> brute_force(const m1une::graph::Graph<T>& graph) {
    std::vector<m1une::graph::Edge<T>> edges = graph.edges();
    std::vector<long long> result(graph.edge_count(), 0);
    int edge_count = int(edges.size());
    for (int first = 0; first < edge_count; first++) {
        for (int second = first + 1; second < edge_count; second++) {
            for (int third = second + 1; third < edge_count; third++) {
                for (int fourth = third + 1; fourth < edge_count; fourth++) {
                    std::array<int, 4> selected;
                    selected[0] = first;
                    selected[1] = second;
                    selected[2] = third;
                    selected[3] = fourth;

                    std::vector<int> degree(graph.size(), 0);
                    std::array<std::pair<int, int>, 4> endpoint;
                    bool valid = true;
                    for (int i = 0; i < 4; i++) {
                        const auto& edge = edges[selected[i]];
                        int from = std::min(edge.from, edge.to);
                        int to = std::max(edge.from, edge.to);
                        endpoint[i] = std::make_pair(from, to);
                        degree[from]++;
                        degree[to]++;
                        for (int j = 0; j < i; j++) {
                            if (endpoint[j] == endpoint[i]) valid = false;
                        }
                    }

                    int used_vertices = 0;
                    for (int value : degree) {
                        if (value != 0) {
                            used_vertices++;
                            valid &= value == 2;
                        }
                    }
                    valid &= used_vertices == 4;
                    if (!valid) continue;
                    for (int index : selected) result[edges[index].id]++;
                }
            }
        }
    }
    return result;
}

void test_randomized() {
    std::uint64_t state = 0xa4093822299f31d0ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int vertex_count = 2 + int(random() % 7);
        int edge_count = 1 + int(random() % 16);
        m1une::graph::Graph<> graph(vertex_count);
        for (int edge = 0; edge < edge_count; edge++) {
            int first = int(random() % vertex_count);
            int second = int(random() % (vertex_count - 1));
            if (first <= second) second++;
            int edge_id;
            if (random() % 2 == 0) {
                edge_id = graph.add_edge(first, second);
            } else {
                edge_id = graph.add_directed_edge(first, second);
            }
            if (random() % 7 == 0) graph.erase_edge(edge_id);
        }

        std::vector<long long> expected = brute_force(graph);
        std::vector<long long> actual =
            m1une::graph::count_four_cycles_per_edge(graph);
        assert(actual == expected);
        long long incidence_count = 0;
        for (long long count : expected) incidence_count += count;
        assert(incidence_count % 4 == 0);
        assert(
            m1une::graph::count_four_cycles(graph) == incidence_count / 4
        );
    }

    m1une::graph::Graph<> complete(4);
    for (int first = 0; first < 4; first++) {
        for (int second = first + 1; second < 4; second++) {
            complete.add_edge(first, second);
        }
    }
    assert(m1une::graph::count_four_cycles(complete) == 3);
    for (long long count :
         m1une::graph::count_four_cycles_per_edge(complete)) {
        assert(count == 2);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int vertex_count = 0;
    int edge_count = 0;
    fast_input >> vertex_count >> edge_count;
    m1une::graph::Graph<> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int first = 0;
        int second = 0;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }
    std::vector<long long> result =
        m1une::graph::count_four_cycles_per_edge(graph);
    for (int edge = 0; edge < edge_count; edge++) {
        if (edge != 0) fast_output << ' ';
        fast_output << result[edge];
    }
    fast_output << '\n';
}
