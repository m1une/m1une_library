#ifndef M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP
#define M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace graph {

struct FunctionalGraph {
    int component_count;
    std::vector<int> successor;
    std::vector<std::vector<int>> predecessors;
    std::vector<std::vector<int>> cycles;
    std::vector<int> component;
    std::vector<int> component_size;
    std::vector<int> cycle_entry;
    std::vector<int> cycle_position;
    std::vector<int> distance_to_cycle;

   private:
    std::vector<std::vector<int>> _up;

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < size());
    }

    int advance_before_cycle(int vertex, int steps) const {
        assert(0 <= steps && steps <= distance_to_cycle[vertex]);
        int bit = 0;
        while (steps > 0) {
            if (steps & 1) vertex = _up[bit][vertex];
            steps >>= 1;
            bit++;
        }
        return vertex;
    }

   public:
    FunctionalGraph() : component_count(0) {}

    explicit FunctionalGraph(const std::vector<int>& successor_) {
        build(successor_);
    }

    void build(const std::vector<int>& successor_) {
        successor = successor_;
        const int n = size();
        for (int to : successor) assert(0 <= to && to < n);

        component_count = 0;
        predecessors.assign(n, {});
        cycles.clear();
        component.assign(n, -1);
        cycle_entry.assign(n, -1);
        cycle_position.assign(n, -1);
        distance_to_cycle.assign(n, -1);

        std::vector<int> indegree(n, 0);
        for (int vertex = 0; vertex < n; vertex++) {
            predecessors[successor[vertex]].push_back(vertex);
            indegree[successor[vertex]]++;
        }

        std::queue<int> queue;
        std::vector<char> removed(n, false);
        for (int vertex = 0; vertex < n; vertex++) {
            if (indegree[vertex] == 0) queue.push(vertex);
        }
        while (!queue.empty()) {
            const int vertex = queue.front();
            queue.pop();
            removed[vertex] = true;
            const int to = successor[vertex];
            indegree[to]--;
            if (indegree[to] == 0) queue.push(to);
        }

        for (int start = 0; start < n; start++) {
            if (removed[start] || component[start] != -1) continue;
            const int component_id = int(cycles.size());
            std::vector<int> cycle;
            int vertex = start;
            do {
                const int position = int(cycle.size());
                cycle.push_back(vertex);
                component[vertex] = component_id;
                cycle_entry[vertex] = vertex;
                cycle_position[vertex] = position;
                distance_to_cycle[vertex] = 0;
                vertex = successor[vertex];
            } while (vertex != start);
            cycles.push_back(std::move(cycle));
        }
        component_count = int(cycles.size());

        for (const std::vector<int>& cycle : cycles) {
            for (int vertex : cycle) queue.push(vertex);
        }
        while (!queue.empty()) {
            const int vertex = queue.front();
            queue.pop();
            for (int from : predecessors[vertex]) {
                if (component[from] != -1) continue;
                component[from] = component[vertex];
                cycle_entry[from] = cycle_entry[vertex];
                cycle_position[from] = cycle_position[vertex];
                distance_to_cycle[from] = distance_to_cycle[vertex] + 1;
                queue.push(from);
            }
        }

        component_size.assign(component_count, 0);
        for (int component_id : component) component_size[component_id]++;

        int log = 1;
        while ((std::uint64_t(1) << log) <= std::uint64_t(n)) log++;
        _up.assign(log, successor);
        for (int bit = 1; bit < log; bit++) {
            for (int vertex = 0; vertex < n; vertex++) {
                _up[bit][vertex] = _up[bit - 1][_up[bit - 1][vertex]];
            }
        }
    }

    int size() const {
        return int(successor.size());
    }

    bool empty() const {
        return successor.empty();
    }

    bool same_component(int first, int second) const {
        check_vertex(first);
        check_vertex(second);
        return component[first] == component[second];
    }

    bool on_cycle(int vertex) const {
        check_vertex(vertex);
        return distance_to_cycle[vertex] == 0;
    }

    int cycle_size(int vertex) const {
        check_vertex(vertex);
        return int(cycles[component[vertex]].size());
    }

    int orbit_size(int vertex) const {
        check_vertex(vertex);
        return distance_to_cycle[vertex] + cycle_size(vertex);
    }

    int jump(int vertex, std::uint64_t steps) const {
        check_vertex(vertex);
        const int tail_length = distance_to_cycle[vertex];
        if (steps < std::uint64_t(tail_length)) {
            return advance_before_cycle(vertex, int(steps));
        }

        steps -= std::uint64_t(tail_length);
        const int entry = cycle_entry[vertex];
        const int length = cycle_size(entry);
        const int offset = int(steps % std::uint64_t(length));
        const int position = (cycle_position[entry] + offset) % length;
        return cycles[component[vertex]][position];
    }

    long long distance(int from, int to) const {
        check_vertex(from);
        check_vertex(to);
        if (!same_component(from, to)) return -1;

        if (!on_cycle(to)) {
            if (distance_to_cycle[from] < distance_to_cycle[to]) return -1;
            const int difference = distance_to_cycle[from] - distance_to_cycle[to];
            return advance_before_cycle(from, difference) == to ? difference : -1;
        }

        const int entry = cycle_entry[from];
        const int length = cycle_size(from);
        int cycle_distance = cycle_position[to] - cycle_position[entry];
        if (cycle_distance < 0) cycle_distance += length;
        return static_cast<long long>(distance_to_cycle[from]) + cycle_distance;
    }

    bool reachable(int from, int to) const {
        return distance(from, to) != -1;
    }

    std::vector<int> path(int from, int to) const {
        const long long path_length = distance(from, to);
        if (path_length == -1) return {};

        std::vector<int> result;
        result.reserve(path_length + 1);
        for (long long step = 0; step <= path_length; step++) {
            result.push_back(from);
            from = successor[from];
        }
        return result;
    }

    std::vector<int> orbit(int vertex) const {
        check_vertex(vertex);
        const int length = orbit_size(vertex);
        std::vector<int> result;
        result.reserve(length);
        for (int step = 0; step < length; step++) {
            result.push_back(vertex);
            vertex = successor[vertex];
        }
        return result;
    }

    std::uint64_t visit_count(
        int from,
        int to,
        std::uint64_t step_count
    ) const {
        const long long first_visit = distance(from, to);
        if (first_visit == -1 ||
            std::uint64_t(first_visit) >= step_count) {
            return 0;
        }
        if (!on_cycle(to)) return 1;

        const std::uint64_t remaining =
            step_count - 1 - std::uint64_t(first_visit);
        return 1 + remaining / std::uint64_t(cycle_size(to));
    }

    long long first_meeting_time(int first, int second) const {
        check_vertex(first);
        check_vertex(second);
        if (!same_component(first, second)) return -1;
        if (first == second) return 0;

        const int first_depth = distance_to_cycle[first];
        const int second_depth = distance_to_cycle[second];
        if (first_depth == second_depth &&
            cycle_entry[first] == cycle_entry[second]) {
            int elapsed = 0;
            for (int bit = int(_up.size()) - 1; bit >= 0; bit--) {
                const int steps = 1 << bit;
                if (first_depth - elapsed < steps) continue;
                const int next_first = _up[bit][first];
                const int next_second = _up[bit][second];
                if (next_first == next_second) continue;
                first = next_first;
                second = next_second;
                elapsed += steps;
            }
            return elapsed + 1;
        }

        const int length = cycle_size(first);
        int first_phase =
            cycle_position[first] - first_depth % length;
        int second_phase =
            cycle_position[second] - second_depth % length;
        if (first_phase < 0) first_phase += length;
        if (second_phase < 0) second_phase += length;
        if (first_phase != second_phase) return -1;
        return std::max(first_depth, second_depth);
    }

    int first_meeting_vertex(int first, int second) const {
        const long long time = first_meeting_time(first, second);
        if (time == -1) return -1;
        return jump(first, std::uint64_t(time));
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP
