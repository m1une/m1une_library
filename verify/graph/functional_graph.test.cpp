#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../graph/functional_graph.hpp"
#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

namespace {

int naive_jump(
    const std::vector<int>& successor,
    int vertex,
    std::uint64_t steps
) {
    const int n = int(successor.size());
    std::vector<long long> first_visit(n, -1);
    std::vector<int> path;
    while (first_visit[vertex] == -1) {
        first_visit[vertex] = int(path.size());
        path.push_back(vertex);
        vertex = successor[vertex];
    }

    if (steps < path.size()) return path[steps];
    const std::uint64_t cycle_start = std::uint64_t(first_visit[vertex]);
    const std::uint64_t cycle_length = path.size() - cycle_start;
    const std::uint64_t position =
        cycle_start + (steps - cycle_start) % cycle_length;
    return path[position];
}

long long naive_distance(
    const std::vector<int>& successor,
    int from,
    int to
) {
    const int n = int(successor.size());
    std::vector<char> visited(n, false);
    for (int distance = 0; !visited[from]; distance++) {
        if (from == to) return distance;
        visited[from] = true;
        from = successor[from];
    }
    return -1;
}

std::vector<int> naive_orbit(
    const std::vector<int>& successor,
    int vertex
) {
    std::vector<char> visited(successor.size(), false);
    std::vector<int> result;
    while (!visited[vertex]) {
        visited[vertex] = true;
        result.push_back(vertex);
        vertex = successor[vertex];
    }
    return result;
}

std::uint64_t naive_visit_count(
    const std::vector<int>& successor,
    int from,
    int to,
    std::uint64_t step_count
) {
    std::uint64_t result = 0;
    for (std::uint64_t step = 0; step < step_count; step++) {
        if (from == to) result++;
        from = successor[from];
    }
    return result;
}

long long naive_first_meeting_time(
    const std::vector<int>& successor,
    int first,
    int second
) {
    const int n = int(successor.size());
    std::vector<char> visited(n * n, false);
    for (int time = 0; !visited[first * n + second]; time++) {
        if (first == second) return time;
        visited[first * n + second] = true;
        first = successor[first];
        second = successor[second];
    }
    return -1;
}

void test_focused_cases() {
    const std::vector<int> successor = {1, 2, 0, 2, 3, 6, 5, 6, 3};
    m1une::graph::FunctionalGraph graph(successor);

    assert(graph.size() == 9);
    assert(!graph.empty());
    assert(graph.component_count == 2);
    assert(graph.same_component(0, 4));
    assert(!graph.same_component(0, 5));
    assert(graph.on_cycle(0));
    assert(graph.on_cycle(5));
    assert(!graph.on_cycle(4));
    assert(graph.cycle_entry[4] == 2);
    assert(graph.distance_to_cycle[4] == 2);
    assert(graph.cycle_size(4) == 3);
    assert(graph.cycle_size(7) == 2);
    assert(graph.component_size[graph.component[4]] == 6);
    assert(graph.component_size[graph.component[7]] == 3);
    assert((graph.predecessors[3] == std::vector<int>{4, 8}));
    assert(graph.orbit_size(4) == 5);
    assert((graph.orbit(4) == std::vector<int>{4, 3, 2, 0, 1}));

    assert(graph.jump(4, 0) == 4);
    assert(graph.jump(4, 1) == 3);
    assert(graph.jump(4, 2) == 2);
    assert(graph.jump(4, 4) == 1);
    assert(graph.jump(7, 3) == 6);
    assert(graph.jump(4, UINT64_C(1000000000000000000)) ==
           naive_jump(successor, 4, UINT64_C(1000000000000000000)));

    assert(graph.distance(4, 4) == 0);
    assert(graph.distance(4, 3) == 1);
    assert(graph.distance(4, 2) == 2);
    assert(graph.distance(4, 1) == 4);
    assert(graph.distance(1, 4) == -1);
    assert(graph.distance(3, 4) == -1);
    assert(graph.distance(4, 5) == -1);
    assert(graph.distance(7, 5) == 2);
    assert(graph.reachable(4, 1));
    assert(!graph.reachable(1, 4));
    assert((graph.path(4, 1) == std::vector<int>{4, 3, 2, 0, 1}));
    assert(graph.path(1, 4).empty());

    assert(graph.visit_count(4, 2, 0) == 0);
    assert(graph.visit_count(4, 2, 3) == 1);
    assert(graph.visit_count(4, 2, 5) == 1);
    assert(graph.visit_count(4, 2, 6) == 2);
    assert(graph.visit_count(4, 3, UINT64_MAX) == 1);
    assert(graph.visit_count(4, 5, UINT64_MAX) == 0);

    assert(graph.first_meeting_time(4, 8) == 1);
    assert(graph.first_meeting_vertex(4, 8) == 3);
    assert(graph.first_meeting_time(4, 0) == 2);
    assert(graph.first_meeting_vertex(4, 0) == 2);
    assert(graph.first_meeting_time(4, 1) == -1);
    assert(graph.first_meeting_vertex(4, 1) == -1);
    assert(graph.first_meeting_time(7, 5) == 1);
    assert(graph.first_meeting_vertex(7, 5) == 6);
    assert(graph.first_meeting_time(4, 5) == -1);
    assert(graph.first_meeting_time(2, 2) == 0);

    graph.build(std::vector<int>{0});
    assert(graph.size() == 1);
    assert(graph.component_count == 1);
    assert(graph.on_cycle(0));
    assert(graph.jump(0, UINT64_MAX) == 0);
    assert(graph.distance(0, 0) == 0);
    assert(graph.orbit_size(0) == 1);
    assert(graph.visit_count(0, 0, UINT64_MAX) == UINT64_MAX);
    assert(graph.first_meeting_time(0, 0) == 0);

    graph.build(std::vector<int>());
    assert(graph.empty());
    assert(graph.component_count == 0);
    assert(graph.cycles.empty());
}

void test_randomized() {
    std::uint64_t state = UINT64_C(0x5f3759df12345678);
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        const int n = 1 + int(random() % 60);
        std::vector<int> successor(n);
        for (int& to : successor) to = int(random() % n);
        m1une::graph::FunctionalGraph graph(successor);

        assert(graph.size() == n);
        assert(1 <= graph.component_count && graph.component_count <= n);
        std::vector<int> expected_component_size(graph.component_count, 0);
        for (int component : graph.component) expected_component_size[component]++;
        assert(graph.component_size == expected_component_size);
        int cycle_vertex_count = 0;
        for (int component = 0; component < graph.component_count; component++) {
            const std::vector<int>& cycle = graph.cycles[component];
            assert(!cycle.empty());
            cycle_vertex_count += int(cycle.size());
            for (int position = 0; position < int(cycle.size()); position++) {
                const int vertex = cycle[position];
                const int next = cycle[(position + 1) % cycle.size()];
                assert(successor[vertex] == next);
                assert(graph.component[vertex] == component);
                assert(graph.cycle_entry[vertex] == vertex);
                assert(graph.cycle_position[vertex] == position);
                assert(graph.distance_to_cycle[vertex] == 0);
            }
        }

        int counted_cycle_vertices = 0;
        for (int vertex = 0; vertex < n; vertex++) {
            assert(0 <= graph.component[vertex]);
            assert(graph.component[vertex] < graph.component_count);
            assert(0 <= graph.cycle_position[vertex]);
            assert(graph.cycle_position[vertex] < graph.cycle_size(vertex));
            assert(graph.cycles[graph.component[vertex]][graph.cycle_position[vertex]] ==
                   graph.cycle_entry[vertex]);
            assert(graph.jump(vertex, graph.distance_to_cycle[vertex]) ==
                   graph.cycle_entry[vertex]);
            assert(graph.orbit(vertex) == naive_orbit(successor, vertex));
            assert(graph.orbit_size(vertex) == int(graph.orbit(vertex).size()));
            if (graph.on_cycle(vertex)) counted_cycle_vertices++;

            int predecessor_count = 0;
            for (int from = 0; from < n; from++) {
                if (successor[from] == vertex) predecessor_count++;
            }
            assert(int(graph.predecessors[vertex].size()) == predecessor_count);
            for (int from : graph.predecessors[vertex]) {
                assert(successor[from] == vertex);
            }

            for (int query = 0; query < 12; query++) {
                const std::uint64_t steps =
                    query == 0 ? random() : random() % std::uint64_t(4 * n + 1);
                assert(graph.jump(vertex, steps) == naive_jump(successor, vertex, steps));
            }
            for (int query = 0; query < 8; query++) {
                const int to = int(random() % n);
                const std::uint64_t step_count = random() % std::uint64_t(4 * n + 1);
                assert(graph.visit_count(vertex, to, step_count) ==
                       naive_visit_count(successor, vertex, to, step_count));
            }
        }
        assert(counted_cycle_vertices == cycle_vertex_count);

        for (int from = 0; from < n; from++) {
            for (int to = 0; to < n; to++) {
                const long long expected_distance = naive_distance(successor, from, to);
                assert(graph.distance(from, to) == expected_distance);
                assert(graph.reachable(from, to) == (expected_distance != -1));
                const std::vector<int> path = graph.path(from, to);
                if (expected_distance == -1) {
                    assert(path.empty());
                } else {
                    assert(int(path.size()) == expected_distance + 1);
                    int vertex = from;
                    for (int value : path) {
                        assert(value == vertex);
                        vertex = successor[vertex];
                    }
                    assert(path.back() == to);
                }
            }
        }

        for (int query = 0; query < 40; query++) {
            const int first = int(random() % n);
            const int second = int(random() % n);
            const long long expected =
                naive_first_meeting_time(successor, first, second);
            assert(graph.first_meeting_time(first, second) == expected);
            assert(graph.first_meeting_time(second, first) == expected);
            const int meeting_vertex = graph.first_meeting_vertex(first, second);
            assert(meeting_vertex ==
                   (expected == -1 ? -1 : naive_jump(successor, first, expected)));
        }
    }
}

}  // namespace

int main() {
    test_focused_cases();
    test_randomized();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    long long first, second;
    fast_input >> first >> second;
    fast_output << first + second << '\n';
}
