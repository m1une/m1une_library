#ifndef M1UNE_GRAPH_SCC_HPP
#define M1UNE_GRAPH_SCC_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct SccResult {
    int count;
    std::vector<int> comp;
    std::vector<std::vector<int>> groups;

    bool same(int u, int v) const {
        assert(0 <= u && u < int(comp.size()));
        assert(0 <= v && v < int(comp.size()));
        return comp[u] == comp[v];
    }

    template <class T>
    Graph<int> dag(const Graph<T>& g) const {
        std::vector<std::pair<int, int>> edges;
        for (int v = 0; v < g.size(); v++) {
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                int a = comp[e.from], b = comp[e.to];
                if (a != b) edges.emplace_back(a, b);
            }
        }
        std::sort(edges.begin(), edges.end());
        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());

        Graph<int> result(count);
        for (auto [a, b] : edges) result.add_directed_edge(a, b);
        return result;
    }
};

template <class T>
SccResult strongly_connected_components(const Graph<T>& g) {
    const int n = g.size();
    std::vector<std::vector<int>> reverse_graph(n);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const auto& edge : g[vertex]) {
            if (edge.alive) reverse_graph[edge.to].push_back(vertex);
        }
    }

    std::vector<char> seen(n, false);
    std::vector<int> order;
    order.reserve(n);
    std::vector<std::pair<int, std::size_t>> dfs_stack;
    for (int start = 0; start < n; start++) {
        if (seen[start]) continue;
        seen[start] = true;
        dfs_stack.emplace_back(start, 0);
        while (!dfs_stack.empty()) {
            int vertex = dfs_stack.back().first;
            std::size_t& edge_index = dfs_stack.back().second;
            while (edge_index < g[vertex].size() &&
                   !g[vertex][edge_index].alive) {
                edge_index++;
            }
            if (edge_index == g[vertex].size()) {
                order.push_back(vertex);
                dfs_stack.pop_back();
                continue;
            }
            const int to = g[vertex][edge_index++].to;
            if (!seen[to]) {
                seen[to] = true;
                dfs_stack.emplace_back(to, 0);
            }
        }
    }

    std::vector<int> comp(n, -1);
    std::vector<std::vector<int>> groups;
    std::vector<int> stack;
    for (auto iterator = order.rbegin(); iterator != order.rend(); ++iterator) {
        const int start = *iterator;
        if (comp[start] != -1) continue;
        const int component = int(groups.size());
        groups.emplace_back();
        comp[start] = component;
        stack.push_back(start);
        while (!stack.empty()) {
            const int vertex = stack.back();
            stack.pop_back();
            groups.back().push_back(vertex);
            for (int to : reverse_graph[vertex]) {
                if (comp[to] != -1) continue;
                comp[to] = component;
                stack.push_back(to);
            }
        }
    }

    return SccResult{int(groups.size()), std::move(comp), std::move(groups)};
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_SCC_HPP
