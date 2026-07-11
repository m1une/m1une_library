#ifndef M1UNE_GRAPH_BICONNECTED_COMPONENTS_HPP
#define M1UNE_GRAPH_BICONNECTED_COMPONENTS_HPP 1

#include <cassert>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct BiconnectedComponentsResult {
    std::vector<std::vector<int>> components;
    std::vector<std::vector<int>> edge_components;
    std::vector<int> component_of_edge;
    std::vector<std::vector<int>> vertex_components;
    std::vector<int> articulation;
    std::vector<int> ord;
    std::vector<int> low;

    int component_count() const {
        return int(components.size());
    }

    bool is_articulation(int vertex) const {
        assert(0 <= vertex && vertex < int(vertex_components.size()));
        return vertex_components[vertex].size() >= 2;
    }
};

// Decomposes an undirected graph into maximal vertex-biconnected blocks.
// Every active edge belongs to exactly one block. Isolated vertices form
// singleton blocks, and articulation vertices occur in multiple blocks.
template <class T>
BiconnectedComponentsResult biconnected_components(const Graph<T>& graph) {
    const int n = graph.size();
    const int edge_count = graph.edge_count();

    BiconnectedComponentsResult result;
    result.component_of_edge.assign(edge_count, -1);
    result.vertex_components.assign(n, {});
    result.ord.assign(n, -1);
    result.low.assign(n, -1);

    std::vector<int> edge_from(edge_count, -1);
    std::vector<int> edge_to(edge_count, -1);
    std::vector<int> incidence_count(edge_count, 0);
    std::vector<int> alive_degree(n, 0);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < edge_count);
            alive_degree[vertex]++;
            if (incidence_count[edge.id] == 0) {
                edge_from[edge.id] = edge.from;
                edge_to[edge.id] = edge.to;
            }
            incidence_count[edge.id]++;
        }
    }
#ifndef NDEBUG
    for (int edge_id = 0; edge_id < edge_count; edge_id++) {
        if (incidence_count[edge_id] == 0) continue;
        assert(incidence_count[edge_id] == 2);
        assert(edge_from[edge_id] != edge_to[edge_id]);
    }
#endif

    std::vector<int> parent(n, -1);
    std::vector<int> parent_edge(n, -1);
    std::vector<int> next_edge(n, 0);
    std::vector<int> dfs_stack;
    std::vector<int> edge_stack;
    std::vector<int> vertex_mark(n, -1);
    int timer = 0;

    auto add_singleton = [&](int vertex) {
        const int component = result.component_count();
        result.components.push_back(std::vector<int>(1, vertex));
        result.edge_components.emplace_back();
        result.vertex_components[vertex].push_back(component);
    };

    auto extract_component = [&](int stopping_edge) {
        const int component = result.component_count();
        result.components.emplace_back();
        result.edge_components.emplace_back();
        std::vector<int>& vertices = result.components.back();
        std::vector<int>& edges = result.edge_components.back();

        while (true) {
            assert(!edge_stack.empty());
            const int edge_id = edge_stack.back();
            edge_stack.pop_back();
            edges.push_back(edge_id);
            result.component_of_edge[edge_id] = component;

            const int endpoints[2] = {edge_from[edge_id], edge_to[edge_id]};
            for (int vertex : endpoints) {
                if (vertex_mark[vertex] == component) continue;
                vertex_mark[vertex] = component;
                vertices.push_back(vertex);
            }
            if (edge_id == stopping_edge) break;
        }
        for (int vertex : vertices) {
            result.vertex_components[vertex].push_back(component);
        }
    };

    for (int root = 0; root < n; root++) {
        if (result.ord[root] != -1) continue;
        if (alive_degree[root] == 0) {
            result.ord[root] = result.low[root] = timer++;
            add_singleton(root);
            continue;
        }

        result.ord[root] = result.low[root] = timer++;
        dfs_stack.push_back(root);
        while (!dfs_stack.empty()) {
            const int vertex = dfs_stack.back();
            if (next_edge[vertex] < int(graph[vertex].size())) {
                const Edge<T>& edge = graph[vertex][next_edge[vertex]++];
                if (!edge.alive || edge.id == parent_edge[vertex]) continue;
                const int to = edge.to;
                if (result.ord[to] == -1) {
                    parent[to] = vertex;
                    parent_edge[to] = edge.id;
                    edge_stack.push_back(edge.id);
                    result.ord[to] = result.low[to] = timer++;
                    dfs_stack.push_back(to);
                } else if (result.ord[to] < result.ord[vertex]) {
                    edge_stack.push_back(edge.id);
                    if (result.ord[to] < result.low[vertex]) {
                        result.low[vertex] = result.ord[to];
                    }
                }
                continue;
            }

            dfs_stack.pop_back();
            const int parent_vertex = parent[vertex];
            if (parent_vertex == -1) {
                assert(edge_stack.empty());
                continue;
            }
            if (result.low[vertex] < result.low[parent_vertex]) {
                result.low[parent_vertex] = result.low[vertex];
            }
            if (result.ord[parent_vertex] <= result.low[vertex]) {
                extract_component(parent_edge[vertex]);
            }
        }
    }

    for (int vertex = 0; vertex < n; vertex++) {
        if (result.is_articulation(vertex)) result.articulation.push_back(vertex);
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BICONNECTED_COMPONENTS_HPP
