#ifndef M1UNE_GRAPH_ST_NUMBERING_HPP
#define M1UNE_GRAPH_ST_NUMBERING_HPP 1

#include <cassert>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

// Returns ranks p with p[source] = 0 and p[sink] = n - 1 such that every
// other vertex has neighbors of both smaller and larger rank. Returns an empty
// vector when no such numbering exists.
template <class T>
std::vector<int> st_numbering(
    const Graph<T>& graph,
    int source,
    int sink
) {
    const int n = graph.size();
    assert(0 < n);
    assert(0 <= source && source < n);
    assert(0 <= sink && sink < n);
    assert(source != sink);

#ifndef NDEBUG
    std::vector<int> incidence_count(graph.edge_count(), 0);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < graph.edge_count());
            incidence_count[edge.id]++;
        }
    }
    for (int edge_id = 0; edge_id < graph.edge_count(); edge_id++) {
        if (graph.is_edge_alive(edge_id)) {
            assert(incidence_count[edge_id] == 2);
        }
    }
#endif

    std::vector<int> parent(n, -1);
    std::vector<int> preorder(n, -1);
    std::vector<int> low_vertex(n, -1);
    std::vector<int> next_edge(n, 0);
    std::vector<int> traversal;
    traversal.reserve(n);

    preorder[source] = 0;
    low_vertex[source] = source;
    traversal.push_back(source);
    preorder[sink] = 1;
    low_vertex[sink] = sink;
    traversal.push_back(sink);

    std::vector<int> stack(1, sink);
    while (!stack.empty()) {
        const int vertex = stack.back();
        if (next_edge[vertex] < int(graph[vertex].size())) {
            const Edge<T>& edge = graph[vertex][next_edge[vertex]++];
            if (!edge.alive || edge.to == vertex) continue;
            const int to = edge.to;
            if (preorder[to] == -1) {
                parent[to] = vertex;
                preorder[to] = int(traversal.size());
                low_vertex[to] = to;
                traversal.push_back(to);
                stack.push_back(to);
            } else if (preorder[to] < preorder[low_vertex[vertex]]) {
                low_vertex[vertex] = to;
            }
            continue;
        }

        stack.pop_back();
        const int parent_vertex = parent[vertex];
        if (parent_vertex != -1 &&
            preorder[low_vertex[vertex]] <
                preorder[low_vertex[parent_vertex]]) {
            low_vertex[parent_vertex] = low_vertex[vertex];
        }
    }
    if (int(traversal.size()) != n) return {};

    std::vector<int> next(n, -1);
    std::vector<int> previous(n, -1);
    std::vector<int> sign(n, 0);
    next[source] = sink;
    previous[sink] = source;
    sign[source] = -1;

    for (int index = 2; index < n; index++) {
        const int vertex = traversal[index];
        const int parent_vertex = parent[vertex];
        assert(parent_vertex != -1);
        if (sign[low_vertex[vertex]] == -1) {
            const int before = previous[parent_vertex];
            if (before == -1) return {};
            next[before] = vertex;
            next[vertex] = parent_vertex;
            previous[vertex] = before;
            previous[parent_vertex] = vertex;
            sign[parent_vertex] = 1;
        } else {
            const int after = next[parent_vertex];
            if (after == -1) return {};
            next[parent_vertex] = vertex;
            next[vertex] = after;
            previous[vertex] = parent_vertex;
            previous[after] = vertex;
            sign[parent_vertex] = -1;
        }
    }

    std::vector<int> order;
    order.reserve(n);
    int vertex = source;
    while (vertex != -1 && int(order.size()) <= n) {
        order.push_back(vertex);
        if (vertex == sink) break;
        vertex = next[vertex];
    }
    if (int(order.size()) != n || order.back() != sink) return {};

    std::vector<int> rank(n, -1);
    for (int index = 0; index < n; index++) rank[order[index]] = index;

    for (int index = 0; index < n; index++) {
        const int current = order[index];
        bool has_smaller = false;
        bool has_larger = false;
        for (const Edge<T>& edge : graph[current]) {
            if (!edge.alive || edge.to == current) continue;
            has_smaller = has_smaller || rank[edge.to] < index;
            has_larger = has_larger || index < rank[edge.to];
        }
        if (index > 0 && !has_smaller) return {};
        if (index + 1 < n && !has_larger) return {};
    }
    return rank;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_ST_NUMBERING_HPP
