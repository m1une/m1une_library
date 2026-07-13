#ifndef M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP
#define M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP 1

#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct ThreeEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;

    int component_count() const {
        return int(components.size());
    }

    bool same(int first, int second) const {
        assert(0 <= first && first < int(component_of_vertex.size()));
        assert(0 <= second && second < int(component_of_vertex.size()));
        return component_of_vertex[first] == component_of_vertex[second];
    }
};

namespace internal {

// Maintains every component as a circular linked list. Swapping two successors
// concatenates two different lists in O(1) time.
struct ThreeEdgeComponentCycles {
    std::vector<int> next;

    explicit ThreeEdgeComponentCycles(int n) : next(n) {
        std::iota(next.begin(), next.end(), 0);
    }

    void unite(int first, int second) {
        std::swap(next[first], next[second]);
    }

    ThreeEdgeConnectedComponentsResult build_result() const {
        const int n = int(next.size());
        ThreeEdgeConnectedComponentsResult result;
        result.component_of_vertex.assign(n, -1);
        for (int first = 0; first < n; first++) {
            if (result.component_of_vertex[first] != -1) continue;
            const int component = result.component_count();
            result.components.emplace_back();
            int vertex = first;
            do {
                result.component_of_vertex[vertex] = component;
                result.components.back().push_back(vertex);
                vertex = next[vertex];
            } while (vertex != first);
        }
        return result;
    }
};

}  // namespace internal

// Decomposes an undirected multigraph into maximal vertex sets joined by at
// least three edge-disjoint paths. This is an iterative form of Tsin's
// one-pass contraction algorithm.
template <class T>
ThreeEdgeConnectedComponentsResult three_edge_connected_components(
    const Graph<T>& graph
) {
    const int n = graph.size();
    const int edge_count = graph.edge_count();

#ifndef NDEBUG
    std::vector<int> incidence_count(edge_count, 0);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(edge.from == vertex);
            assert(0 <= edge.to && edge.to < n);
            assert(0 <= edge.id && edge.id < edge_count);
            incidence_count[edge.id]++;
        }
    }
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id] == 2);
    }
#endif

    const int none = n;
    std::vector<int> enter(n, -1);
    std::vector<int> leave(n, 0);
    std::vector<int> low(n, none);
    std::vector<int> degree(n, 0);
    std::vector<int> path(n, none);
    std::vector<int> parent(n, -1);
    std::vector<int> parent_edge(n, -1);
    std::vector<int> next_edge(n, 0);
    std::vector<int> dfs_stack;
    internal::ThreeEdgeComponentCycles component_cycles(n);
    int timer = 0;

    auto absorb = [&](int vertex, int other) {
        component_cycles.unite(vertex, other);
        degree[vertex] += degree[other];
    };

    auto process_visited_edge = [&](int vertex, int to) {
        if (enter[to] < enter[vertex]) {
            degree[vertex]++;
            low[vertex] = std::min(low[vertex], enter[to]);
            return;
        }

        degree[vertex]--;
        int current = path[vertex];
        while (current != none && enter[current] <= enter[to] && enter[to] < leave[current]) {
            absorb(vertex, current);
            current = path[current];
        }
        path[vertex] = current;
    };

    auto process_child = [&](int vertex, int child) {
        if (path[child] == none && degree[child] <= 1) {
            degree[vertex] += degree[child];
            low[vertex] = std::min(low[vertex], low[child]);
            return;
        }

        int current = child;
        if (degree[child] == 0) current = path[child];
        assert(current != none);
        if (low[current] < low[vertex]) {
            low[vertex] = low[current];
            std::swap(current, path[vertex]);
        }
        while (current != none) {
            absorb(vertex, current);
            current = path[current];
        }
    };

    for (int root = 0; root < n; root++) {
        if (enter[root] != -1) continue;
        enter[root] = timer++;
        dfs_stack.push_back(root);

        while (!dfs_stack.empty()) {
            const int vertex = dfs_stack.back();
            if (next_edge[vertex] < int(graph[vertex].size())) {
                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];
                if (!edge.alive || edge.from == edge.to || edge.id == parent_edge[vertex]) continue;
                const int to = edge.to;
                if (enter[to] == -1) {
                    parent[to] = vertex;
                    parent_edge[to] = edge.id;
                    enter[to] = timer++;
                    dfs_stack.push_back(to);
                } else {
                    process_visited_edge(vertex, to);
                }
                continue;
            }

            leave[vertex] = timer;
            dfs_stack.pop_back();
            if (parent[vertex] != -1) process_child(parent[vertex], vertex);
        }
    }

    return component_cycles.build_result();
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_THREE_EDGE_CONNECTED_COMPONENTS_HPP
