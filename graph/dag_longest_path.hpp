#ifndef M1UNE_GRAPH_DAG_LONGEST_PATH_HPP
#define M1UNE_GRAPH_DAG_LONGEST_PATH_HPP 1

#include <algorithm>
#include <cassert>
#include <limits>
#include <optional>
#include <vector>

#include "graph.hpp"
#include "topological_sort.hpp"

namespace m1une {
namespace graph {

template <class T>
struct DagLongestPathResult {
    std::vector<T> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> topological_order;
    T neg_inf;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != neg_inf;
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

template <class T>
std::optional<DagLongestPathResult<T>> dag_longest_path(
    const Graph<T>& g,
    const std::vector<int>& sources,
    T neg_inf = std::numeric_limits<T>::lowest() / T(4)
) {
    const int n = g.size();
    auto order = topological_sort(g);
    if (!order) return std::nullopt;

    DagLongestPathResult<T> result;
    result.dist.assign(n, neg_inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.topological_order = *order;
    result.neg_inf = neg_inf;

    for (int s : sources) {
        assert(0 <= s && s < n);
        result.dist[s] = T(0);
    }

    for (int v : *order) {
        if (result.dist[v] == neg_inf) continue;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            T nd = result.dist[v] + e.cost;
            if (result.dist[e.to] >= nd) continue;
            result.dist[e.to] = nd;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
        }
    }

    return result;
}

template <class T>
std::optional<DagLongestPathResult<T>> dag_longest_path(
    const Graph<T>& g,
    int s,
    T neg_inf = std::numeric_limits<T>::lowest() / T(4)
) {
    return dag_longest_path(g, std::vector<int>{s}, neg_inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DAG_LONGEST_PATH_HPP
