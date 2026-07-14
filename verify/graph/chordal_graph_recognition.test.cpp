#define PROBLEM "https://judge.yosupo.jp/problem/chordal_graph_recognition"

#include "../../graph/chordal_graph_recognition.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

using Graph = m1une::graph::Graph<>;
using Result = m1une::graph::ChordalGraphResult;

std::vector<std::vector<char>> adjacency_matrix(const Graph& graph) {
    const int size = graph.size();
    std::vector<std::vector<char>> adjacent(size, std::vector<char>(size, false));
    for (const auto& edge : graph.edges()) {
        if (edge.from == edge.to) continue;
        adjacent[edge.from][edge.to] = true;
        adjacent[edge.to][edge.from] = true;
    }
    return adjacent;
}

void validate(const Graph& graph) {
    const int size = graph.size();
    const auto adjacent = adjacency_matrix(graph);
    Result result = m1une::graph::chordal_graph_recognition(graph);
    assert(m1une::graph::is_chordal(graph) == result.is_chordal);

    if (result.is_chordal) {
        assert(result.induced_cycle.empty());
        assert(int(result.perfect_elimination_order.size()) == size);
        std::vector<int> position(size, -1);
        for (int index = 0; index < size; index++) {
            int vertex = result.perfect_elimination_order[index];
            assert(0 <= vertex && vertex < size);
            assert(position[vertex] == -1);
            position[vertex] = index;
        }
        for (int vertex = 0; vertex < size; vertex++) {
            std::vector<int> later_neighbors;
            for (int to = 0; to < size; to++) {
                if (adjacent[vertex][to] && position[vertex] < position[to]) {
                    later_neighbors.push_back(to);
                }
            }
            for (int first : later_neighbors) {
                for (int second : later_neighbors) {
                    if (first != second) assert(adjacent[first][second]);
                }
            }
        }
        return;
    }

    assert(result.perfect_elimination_order.empty());
    const int cycle_size = int(result.induced_cycle.size());
    assert(cycle_size >= 4);
    std::vector<char> used(size, false);
    for (int index = 0; index < cycle_size; index++) {
        const int vertex = result.induced_cycle[index];
        assert(0 <= vertex && vertex < size);
        assert(!used[vertex]);
        used[vertex] = true;
        for (int other = index + 1; other < cycle_size; other++) {
            const int distance = other - index;
            const bool consecutive = distance == 1 || distance == cycle_size - 1;
            assert(bool(adjacent[vertex][result.induced_cycle[other]]) == consecutive);
        }
    }
}

void test_fixed() {
    validate(Graph());
    validate(Graph(1));

    Graph tree(8);
    for (int vertex = 1; vertex < 8; vertex++) tree.add_edge(vertex / 2, vertex);
    validate(tree);
    assert(m1une::graph::is_chordal(tree));

    Graph complete(9);
    for (int first = 0; first < 9; first++) {
        for (int second = first + 1; second < 9; second++) {
            complete.add_edge(first, second);
        }
    }
    validate(complete);

    for (int size = 4; size <= 12; size++) {
        Graph cycle(size);
        for (int vertex = 0; vertex < size; vertex++) {
            cycle.add_edge(vertex, (vertex + 1) % size);
        }
        validate(cycle);
        assert(!m1une::graph::is_chordal(cycle));
    }

    Graph parallel(4);
    parallel.add_edge(0, 1);
    parallel.add_edge(0, 1);
    parallel.add_directed_edge(1, 2);
    int inactive = parallel.add_edge(0, 2);
    parallel.erase_edge(inactive);
    parallel.add_edge(2, 3);
    validate(parallel);
}

void test_randomized() {
    std::uint64_t state = 0xd1b54a32d192ed03ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        const int size = int(random() % 11);
        Graph graph(size);
        for (int first = 0; first < size; first++) {
            for (int second = first + 1; second < size; second++) {
                if (random() % 3 == 0) continue;
                if (random() & 1) {
                    graph.add_edge(first, second);
                } else {
                    graph.add_directed_edge(first, second);
                }
                if (random() % 13 == 0) graph.add_edge(first, second);
            }
        }
        validate(graph);
    }
}

void test_deep_graph() {
    const int size = 50000;
    Graph graph(size);
    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1, vertex);
    Result result = m1une::graph::chordal_graph_recognition(graph);
    assert(result.is_chordal);
    assert(int(result.perfect_elimination_order.size()) == size);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    test_deep_graph();
    int size, edge_count;
    fast_input >> size >> edge_count;
    Graph graph(size);
    while (edge_count--) {
        int first, second;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    Result result = m1une::graph::chordal_graph_recognition(graph);
    if (result.is_chordal) {
        fast_output << "YES\n";
        for (int index = 0; index < size; index++) {
            if (index != 0) fast_output << ' ';
            fast_output << result.perfect_elimination_order[index];
        }
        fast_output << '\n';
    } else {
        fast_output << "NO\n" << result.induced_cycle.size() << '\n';
        for (int index = 0; index < int(result.induced_cycle.size()); index++) {
            if (index != 0) fast_output << ' ';
            fast_output << result.induced_cycle[index];
        }
        fast_output << '\n';
    }
}
