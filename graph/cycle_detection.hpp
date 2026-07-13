#ifndef M1UNE_GRAPH_CYCLE_DETECTION_HPP
#define M1UNE_GRAPH_CYCLE_DETECTION_HPP 1

#include <algorithm>
#include <cstddef>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct Cycle {
    std::vector<int> vertices;
    std::vector<int> edge_ids;

    bool empty() const {
        return vertices.empty();
    }
};

inline Cycle restore_cycle(int from, int to, int closing_edge, const std::vector<int>& parent,
                           const std::vector<int>& parent_edge) {
    Cycle result;
    result.vertices.push_back(to);

    std::vector<int> middle_vertices;
    std::vector<int> middle_edges;
    for (int v = from; v != to; v = parent[v]) {
        middle_vertices.push_back(v);
        middle_edges.push_back(parent_edge[v]);
    }
    std::reverse(middle_vertices.begin(), middle_vertices.end());
    std::reverse(middle_edges.begin(), middle_edges.end());

    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());
    result.vertices.push_back(to);
    result.edge_ids.insert(result.edge_ids.end(), middle_edges.begin(), middle_edges.end());
    result.edge_ids.push_back(closing_edge);
    return result;
}

template <class T>
Cycle find_directed_cycle(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);
    struct Frame {
        int vertex;
        std::size_t next_edge;
    };

    std::vector<Frame> stack;
    stack.reserve(n);
    for (int start = 0; start < n; start++) {
        if (color[start] != 0) continue;
        color[start] = 1;
        stack.push_back(Frame{start, 0});
        while (!stack.empty()) {
            Frame& frame = stack.back();
            const int vertex = frame.vertex;
            const auto& adjacency = g[vertex];
            while (
                frame.next_edge < adjacency.size() &&
                !adjacency[frame.next_edge].alive
            ) {
                frame.next_edge++;
            }
            if (frame.next_edge == adjacency.size()) {
                color[vertex] = 2;
                stack.pop_back();
                continue;
            }

            const auto& edge = adjacency[frame.next_edge++];
            const int to = edge.to;
            const int edge_id = edge.id;
            if (color[to] == 0) {
                parent[to] = vertex;
                parent_edge[to] = edge_id;
                color[to] = 1;
                stack.push_back(Frame{to, 0});
            } else if (color[to] == 1) {
                return restore_cycle(vertex, to, edge_id, parent, parent_edge);
            }
        }
    }
    return Cycle();
}

template <class T>
Cycle find_undirected_cycle(const Graph<T>& g) {
    int n = g.size();
    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);
    struct Frame {
        int vertex;
        std::size_t next_edge;
    };

    std::vector<Frame> stack;
    stack.reserve(n);
    for (int start = 0; start < n; start++) {
        if (color[start] != 0) continue;
        color[start] = 1;
        stack.push_back(Frame{start, 0});
        while (!stack.empty()) {
            Frame& frame = stack.back();
            const int vertex = frame.vertex;
            const auto& adjacency = g[vertex];
            while (
                frame.next_edge < adjacency.size() &&
                (
                    !adjacency[frame.next_edge].alive ||
                    adjacency[frame.next_edge].id == parent_edge[vertex]
                )
            ) {
                frame.next_edge++;
            }
            if (frame.next_edge == adjacency.size()) {
                color[vertex] = 2;
                stack.pop_back();
                continue;
            }

            const auto& edge = adjacency[frame.next_edge++];
            const int to = edge.to;
            const int edge_id = edge.id;
            if (color[to] == 0) {
                parent[to] = vertex;
                parent_edge[to] = edge_id;
                color[to] = 1;
                stack.push_back(Frame{to, 0});
            } else if (color[to] == 1) {
                return restore_cycle(vertex, to, edge_id, parent, parent_edge);
            }
        }
    }
    return Cycle();
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_CYCLE_DETECTION_HPP
