#ifndef M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP
#define M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP 1

#include <cassert>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct TwoEdgeConnectedBridge {
    int from;
    int to;
    int edge_id;
};

struct TwoEdgeConnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<int> component_of_vertex;
    std::vector<int> bridge_ids;
    std::vector<char> bridge;
    std::vector<TwoEdgeConnectedBridge> bridge_forest_edges;
    std::vector<int> ord;
    std::vector<int> low;

    int component_count() const {
        return int(components.size());
    }

    bool same(int first, int second) const {
        assert(0 <= first && first < int(component_of_vertex.size()));
        assert(0 <= second && second < int(component_of_vertex.size()));
        return component_of_vertex[first] == component_of_vertex[second];
    }

    bool is_bridge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(bridge.size()));
        return bridge[edge_id];
    }
};

// Removes every active bridge and returns the remaining connected components.
// The first lowlink traversal and the component traversal are both iterative.
template <class T>
TwoEdgeConnectedComponentsResult two_edge_connected_components(
    const Graph<T>& graph
) {
    const int n = graph.size();
    const int edge_count = graph.edge_count();

    TwoEdgeConnectedComponentsResult result;
    result.component_of_vertex.assign(n, -1);
    result.bridge.assign(edge_count, false);
    result.ord.assign(n, -1);
    result.low.assign(n, -1);

    std::vector<int> edge_from(edge_count, -1);
    std::vector<int> edge_to(edge_count, -1);
    std::vector<int> incidence_count(edge_count, 0);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < edge_count);
            if (incidence_count[edge.id] == 0) {
                edge_from[edge.id] = edge.from;
                edge_to[edge.id] = edge.to;
            }
            incidence_count[edge.id]++;
        }
    }
#ifndef NDEBUG
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        if (incidence_count[edge_id] != 0) assert(incidence_count[edge_id] == 2);
    }
#endif

    std::vector<int> parent(n, -1);
    std::vector<int> parent_edge(n, -1);
    std::vector<int> next_edge(n, 0);
    std::vector<int> stack;
    int timer = 0;

    for (int root = 0; root < n; root++) {
        if (result.ord[root] != -1) continue;
        result.ord[root] = result.low[root] = timer++;
        stack.push_back(root);
        while (!stack.empty()) {
            const int vertex = stack.back();
            if (next_edge[vertex] < int(graph[vertex].size())) {
                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];
                if (!edge.alive || edge.id == parent_edge[vertex]) continue;
                const int to = edge.to;
                if (result.ord[to] == -1) {
                    parent[to] = vertex;
                    parent_edge[to] = edge.id;
                    result.ord[to] = result.low[to] = timer++;
                    stack.push_back(to);
                } else if (result.ord[to] < result.low[vertex]) {
                    result.low[vertex] = result.ord[to];
                }
                continue;
            }

            stack.pop_back();
            const int parent_vertex = parent[vertex];
            if (parent_vertex == -1) continue;
            if (result.low[vertex] < result.low[parent_vertex]) {
                result.low[parent_vertex] = result.low[vertex];
            }
            if (result.ord[parent_vertex] < result.low[vertex]) {
                result.bridge[parent_edge[vertex]] = true;
            }
        }
    }

    for (int root = 0; root < n; root++) {
        if (result.component_of_vertex[root] != -1) continue;
        const int component = result.component_count();
        result.components.emplace_back();
        result.component_of_vertex[root] = component;
        stack.push_back(root);
        while (!stack.empty()) {
            const int vertex = stack.back();
            stack.pop_back();
            result.components.back().push_back(vertex);
            for (const Edge<T>& edge : graph[vertex]) {
                if (!edge.alive || result.bridge[edge.id]) continue;
                if (result.component_of_vertex[edge.to] != -1) continue;
                result.component_of_vertex[edge.to] = component;
                stack.push_back(edge.to);
            }
        }
    }

    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        if (!result.bridge[edge_id]) continue;
        result.bridge_ids.push_back(edge_id);
        const int first_component = result.component_of_vertex[edge_from[edge_id]];
        const int second_component = result.component_of_vertex[edge_to[edge_id]];
        assert(first_component != second_component);
        result.bridge_forest_edges.push_back(
            TwoEdgeConnectedBridge{first_component, second_component, edge_id});
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_TWO_EDGE_CONNECTED_COMPONENTS_HPP
