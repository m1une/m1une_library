#ifndef M1UNE_GRAPH_INCREMENTAL_SCC_HPP
#define M1UNE_GRAPH_INCREMENTAL_SCC_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

namespace incremental_scc_detail {

struct EdgeEvent {
    int id;
    int from;
    int to;
};

inline std::vector<int> component_ids(
    int vertex_count,
    const std::vector<EdgeEvent>& edges,
    int time
) {
    std::vector<int> begin(vertex_count + 1, 0);
    std::vector<int> reverse_begin(vertex_count + 1, 0);
    int edge_count = 0;
    for (const EdgeEvent& edge : edges) {
        if (edge.id >= time) continue;
        begin[edge.from + 1]++;
        reverse_begin[edge.to + 1]++;
        edge_count++;
    }
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        begin[vertex + 1] += begin[vertex];
        reverse_begin[vertex + 1] += reverse_begin[vertex];
    }

    std::vector<int> adjacency(edge_count);
    std::vector<int> reverse_adjacency(edge_count);
    std::vector<int> cursor = begin;
    std::vector<int> reverse_cursor = reverse_begin;
    for (const EdgeEvent& edge : edges) {
        if (edge.id >= time) continue;
        adjacency[cursor[edge.from]++] = edge.to;
        reverse_adjacency[reverse_cursor[edge.to]++] = edge.from;
    }
    std::vector<int>().swap(cursor);
    std::vector<int>().swap(reverse_cursor);

    std::vector<char> visited(vertex_count, false);
    std::vector<int> next_position(begin.begin(), begin.end() - 1);
    std::vector<int> order;
    order.reserve(vertex_count);
    std::vector<int> stack;
    for (int start = 0; start < vertex_count; start++) {
        if (visited[start]) continue;
        visited[start] = true;
        stack.push_back(start);
        while (!stack.empty()) {
            const int vertex = stack.back();
            int& position = next_position[vertex];
            if (position < begin[vertex + 1]) {
                const int to = adjacency[position++];
                if (!visited[to]) {
                    visited[to] = true;
                    stack.push_back(to);
                }
            } else {
                order.push_back(vertex);
                stack.pop_back();
            }
        }
    }

    std::vector<int> component(vertex_count, -1);
    int component_count = 0;
    for (auto iterator = order.rbegin(); iterator != order.rend(); ++iterator) {
        const int start = *iterator;
        if (component[start] != -1) continue;
        component[start] = component_count;
        stack.push_back(start);
        while (!stack.empty()) {
            const int vertex = stack.back();
            stack.pop_back();
            for (int position = reverse_begin[vertex];
                 position < reverse_begin[vertex + 1]; position++) {
                const int to = reverse_adjacency[position];
                if (component[to] != -1) continue;
                component[to] = component_count;
                stack.push_back(to);
            }
        }
        component_count++;
    }
    return component;
}

}  // namespace incremental_scc_detail

// For every directed edge e, returns the first time t after e is inserted such
// that its endpoints are in the same SCC. At time t, edges with IDs less than
// t have been inserted. edge_count() + 1 means this never happens.
template <class T>
std::vector<int> incremental_scc(const Graph<T>& graph) {
    using incremental_scc_detail::EdgeEvent;
    using incremental_scc_detail::component_ids;

    const int vertex_count = graph.size();
    const int edge_count = graph.edge_count();
    const int never = edge_count + 1;
    std::vector<int> merge_time(edge_count, never);
    if (edge_count == 0) return merge_time;

    std::vector<EdgeEvent> edges_by_id(edge_count);
    std::vector<char> initialized(edge_count, false);
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            assert(0 <= edge.id && edge.id < edge_count);
            assert(!initialized[edge.id]);
            if (initialized[edge.id]) continue;
            initialized[edge.id] = true;
            edges_by_id[edge.id] = EdgeEvent{edge.id, edge.from, edge.to};
        }
    }

    std::vector<EdgeEvent> events;
    events.reserve(edge_count);
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        assert(initialized[edge_id]);
        if (graph.is_edge_alive(edge_id)) {
            events.push_back(edges_by_id[edge_id]);
        }
    }
    std::vector<EdgeEvent>().swap(edges_by_id);
    std::vector<char>().swap(initialized);

    std::vector<int> new_index(vertex_count, -1);
    auto divide = [&](
        auto&& self,
        std::vector<EdgeEvent> current,
        int left,
        int right
    ) -> void {
        if (current.empty() || right == left + 1) return;
        const int middle = left + (right - left) / 2;

        std::vector<int> touched;
        touched.reserve(std::min(
            std::size_t(vertex_count),
            current.size() * 2
        ));
        int compressed_count = 0;
        for (const EdgeEvent& edge : current) {
            if (new_index[edge.from] == -1) {
                new_index[edge.from] = compressed_count++;
                touched.push_back(edge.from);
            }
            if (new_index[edge.to] == -1) {
                new_index[edge.to] = compressed_count++;
                touched.push_back(edge.to);
            }
        }
        for (EdgeEvent& edge : current) {
            edge.from = new_index[edge.from];
            edge.to = new_index[edge.to];
        }
        for (int vertex : touched) new_index[vertex] = -1;

        std::vector<EdgeEvent> earlier;
        std::vector<EdgeEvent> later;
        earlier.reserve(current.size() / 2);
        later.reserve(current.size() / 2);
        {
            std::vector<int> component =
                component_ids(compressed_count, current, middle);
            for (const EdgeEvent& edge : current) {
                const int from_component = component[edge.from];
                const int to_component = component[edge.to];
                if (edge.id < middle &&
                    from_component == to_component) {
                    merge_time[edge.id] =
                        std::min(merge_time[edge.id], middle);
                    earlier.push_back(edge);
                } else {
                    later.push_back(EdgeEvent{
                        edge.id,
                        from_component,
                        to_component
                    });
                }
            }
        }

        std::vector<EdgeEvent>().swap(current);
        self(self, std::move(earlier), left, middle);
        self(self, std::move(later), middle, right);
    };
    divide(divide, std::move(events), 0, edge_count + 1);
    return merge_time;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_INCREMENTAL_SCC_HPP
