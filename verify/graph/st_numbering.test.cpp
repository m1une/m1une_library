#define PROBLEM "https://judge.yosupo.jp/problem/st_numbering"

#include "../../graph/st_numbering.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using Graph = m1une::graph::Graph<>;

bool valid_numbering(
    const Graph& graph,
    int source,
    int sink,
    const std::vector<int>& rank
) {
    const int n = graph.size();
    if (int(rank.size()) != n) return false;
    std::vector<int> order(n, -1);
    for (int vertex = 0; vertex < n; vertex++) {
        if (rank[vertex] < 0 || rank[vertex] >= n) return false;
        if (order[rank[vertex]] != -1) return false;
        order[rank[vertex]] = vertex;
    }
    if (rank[source] != 0 || rank[sink] != n - 1) return false;

    for (int index = 0; index < n; index++) {
        bool smaller = index == 0;
        bool larger = index + 1 == n;
        for (const auto& edge : graph[order[index]]) {
            if (!edge.alive || edge.to == order[index]) continue;
            smaller = smaller || rank[edge.to] < index;
            larger = larger || index < rank[edge.to];
        }
        if (!smaller || !larger) return false;
    }
    return true;
}

bool brute_exists(const Graph& graph, int source, int sink) {
    const int n = graph.size();
    std::vector<int> middle;
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex != source && vertex != sink) middle.push_back(vertex);
    }
    do {
        std::vector<int> rank(n, -1);
        rank[source] = 0;
        for (int index = 0; index < int(middle.size()); index++) {
            rank[middle[index]] = index + 1;
        }
        rank[sink] = n - 1;
        if (valid_numbering(graph, source, sink, rank)) return true;
    } while (std::next_permutation(middle.begin(), middle.end()));
    return false;
}

void validate(const Graph& graph, int source, int sink) {
    const std::vector<int> rank =
        m1une::graph::st_numbering(graph, source, sink);
    assert(rank.empty() == !brute_exists(graph, source, sink));
    if (!rank.empty()) assert(valid_numbering(graph, source, sink, rank));
}

void test_fixed() {
    Graph edge(2);
    edge.add_edge(0, 1);
    validate(edge, 0, 1);

    Graph path(5);
    for (int vertex = 1; vertex < 5; vertex++) {
        path.add_edge(vertex - 1, vertex);
    }
    validate(path, 0, 4);
    validate(path, 1, 4);

    Graph cycle(6);
    for (int vertex = 0; vertex < 6; vertex++) {
        cycle.add_edge(vertex, (vertex + 1) % 6);
    }
    validate(cycle, 1, 4);

    Graph parallel(3);
    parallel.add_edge(0, 1);
    parallel.add_edge(0, 1);
    parallel.add_edge(1, 2);
    int shortcut = parallel.add_edge(0, 2);
    validate(parallel, 0, 2);
    parallel.erase_edge(shortcut);
    validate(parallel, 0, 2);
}

void test_randomized() {
    std::uint64_t state = 20260717;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; trial++) {
        const int n = 2 + int(random() % 6);
        Graph graph(n);
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                if (random() % 3 == 0) graph.add_edge(first, second);
            }
        }
        const int source = int(random() % n);
        int sink = int(random() % (n - 1));
        if (sink >= source) sink++;
        validate(graph, source, sink);
    }
}

void test_deep_path() {
    const int n = 50000;
    Graph graph(n);
    for (int vertex = 1; vertex < n; vertex++) {
        graph.add_edge(vertex - 1, vertex);
    }
    const std::vector<int> rank = m1une::graph::st_numbering(graph, 0, n - 1);
    assert(int(rank.size()) == n);
    for (int vertex = 0; vertex < n; vertex++) assert(rank[vertex] == vertex);
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();
    test_deep_path();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        int vertex_count, edge_count, source, sink;
        fast_input >> vertex_count >> edge_count >> source >> sink;
        Graph graph(vertex_count);
        while (edge_count--) {
            int first, second;
            fast_input >> first >> second;
            graph.add_edge(first, second);
        }

        const std::vector<int> rank =
            m1une::graph::st_numbering(graph, source, sink);
        if (rank.empty()) {
            fast_output << "No\n";
        } else {
            fast_output << "Yes\n";
            for (int vertex = 0; vertex < vertex_count; vertex++) {
                if (vertex) fast_output << ' ';
                fast_output << rank[vertex];
            }
            fast_output << '\n';
        }
    }
}
