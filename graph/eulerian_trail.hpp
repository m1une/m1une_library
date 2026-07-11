#ifndef M1UNE_GRAPH_EULERIAN_TRAIL_HPP
#define M1UNE_GRAPH_EULERIAN_TRAIL_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct EulerianTrail {
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    int edge_count() const {
        return int(edge_ids.size());
    }

    bool is_circuit() const {
        return vertices.empty() || vertices.front() == vertices.back();
    }
};

namespace internal {

template <class T>
std::optional<EulerianTrail> hierholzer(
    const Graph<T>& graph,
    int start,
    int active_edge_count
) {
    EulerianTrail result;
    if (active_edge_count == 0) {
        if (start != -1) result.vertices.push_back(start);
        return result;
    }

    assert(0 <= start && start < graph.size());
    std::vector<char> used(graph.edge_count(), false);
    std::vector<int> cursor(graph.size(), 0);
    std::vector<int> vertex_stack(1, start);
    std::vector<int> incoming_edge_stack(1, -1);
    std::vector<int> reversed_vertices;
    std::vector<int> reversed_edges;
    reversed_vertices.reserve(active_edge_count + 1);
    reversed_edges.reserve(active_edge_count);

    while (!vertex_stack.empty()) {
        const int vertex = vertex_stack.back();
        while (cursor[vertex] < int(graph[vertex].size())) {
            const Edge<T>& edge = graph[vertex][cursor[vertex]];
            if (edge.alive && !used[edge.id]) break;
            cursor[vertex]++;
        }

        if (cursor[vertex] < int(graph[vertex].size())) {
            const Edge<T>& edge = graph[vertex][cursor[vertex]++];
            used[edge.id] = true;
            vertex_stack.push_back(edge.to);
            incoming_edge_stack.push_back(edge.id);
            continue;
        }

        reversed_vertices.push_back(vertex);
        const int incoming_edge = incoming_edge_stack.back();
        if (incoming_edge != -1) reversed_edges.push_back(incoming_edge);
        vertex_stack.pop_back();
        incoming_edge_stack.pop_back();
    }

    if (int(reversed_edges.size()) != active_edge_count) return std::nullopt;
    std::reverse(reversed_vertices.begin(), reversed_vertices.end());
    std::reverse(reversed_edges.begin(), reversed_edges.end());
    result.vertices = std::move(reversed_vertices);
    result.edge_ids = std::move(reversed_edges);
    return result;
}

template <class T>
std::vector<int> edge_incidence_count(const Graph<T>& graph) {
    std::vector<int> count(graph.edge_count(), 0);
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < graph.edge_count());
            count[edge.id]++;
        }
    }
    return count;
}

}  // namespace internal

template <class T>
std::optional<EulerianTrail> directed_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
) {
    assert(start == -1 || (0 <= start && start < graph.size()));
    const int n = graph.size();
    std::vector<int> incidence = internal::edge_incidence_count(graph);
    std::vector<int> in_degree(n, 0);
    std::vector<int> out_degree(n, 0);
    int active_edge_count = 0;
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            out_degree[vertex]++;
            in_degree[edge.to]++;
        }
    }
    for (int count : incidence) {
        if (count == 0) continue;
        assert(count == 1);
        active_edge_count++;
    }

    int required_start = -1;
    int required_end = -1;
    for (int vertex = 0; vertex < n; vertex++) {
        const int difference = out_degree[vertex] - in_degree[vertex];
        if (difference == 1) {
            if (required_start != -1) return std::nullopt;
            required_start = vertex;
        } else if (difference == -1) {
            if (required_end != -1) return std::nullopt;
            required_end = vertex;
        } else if (difference != 0) {
            return std::nullopt;
        }
    }
    if ((required_start == -1) != (required_end == -1)) return std::nullopt;

    int chosen_start = start;
    if (active_edge_count == 0) {
        if (chosen_start == -1 && n > 0) chosen_start = 0;
        return internal::hierholzer(graph, chosen_start, 0);
    }
    if (required_start != -1) {
        if (chosen_start != -1 && chosen_start != required_start) return std::nullopt;
        chosen_start = required_start;
    } else if (chosen_start == -1) {
        for (int vertex = 0; vertex < n; vertex++) {
            if (out_degree[vertex] > 0) {
                chosen_start = vertex;
                break;
            }
        }
    } else if (out_degree[chosen_start] == 0) {
        return std::nullopt;
    }
    return internal::hierholzer(graph, chosen_start, active_edge_count);
}

template <class T>
std::optional<EulerianTrail> undirected_eulerian_trail(
    const Graph<T>& graph,
    int start = -1
) {
    assert(start == -1 || (0 <= start && start < graph.size()));
    const int n = graph.size();
    std::vector<int> incidence = internal::edge_incidence_count(graph);
    std::vector<int> degree(n, 0);
    int active_edge_count = 0;
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (edge.alive) degree[vertex]++;
        }
    }
    for (int count : incidence) {
        if (count == 0) continue;
        assert(count == 2);
        active_edge_count++;
    }

    std::vector<int> odd;
    for (int vertex = 0; vertex < n; vertex++) {
        if (degree[vertex] & 1) odd.push_back(vertex);
    }
    if (!odd.empty() && odd.size() != 2) return std::nullopt;

    int chosen_start = start;
    if (active_edge_count == 0) {
        if (chosen_start == -1 && n > 0) chosen_start = 0;
        return internal::hierholzer(graph, chosen_start, 0);
    }
    if (odd.size() == 2) {
        if (chosen_start != -1 && chosen_start != odd[0] && chosen_start != odd[1]) {
            return std::nullopt;
        }
        if (chosen_start == -1) chosen_start = odd[0];
    } else if (chosen_start == -1) {
        for (int vertex = 0; vertex < n; vertex++) {
            if (degree[vertex] > 0) {
                chosen_start = vertex;
                break;
            }
        }
    } else if (degree[chosen_start] == 0) {
        return std::nullopt;
    }
    return internal::hierholzer(graph, chosen_start, active_edge_count);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_EULERIAN_TRAIL_HPP
