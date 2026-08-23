#ifndef M1UNE_GRAPH_DAG_REACHABILITY_HPP
#define M1UNE_GRAPH_DAG_REACHABILITY_HPP 1

#include <algorithm>
#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "../utilities/dynamic_bitset.hpp"
#include "graph.hpp"
#include "topological_sort.hpp"

namespace m1une {
namespace graph {

struct DagReachability {
    std::vector<utilities::DynamicBitset> reachable_vertices;
    std::vector<int> topological_order;

    int size() const {
        return int(reachable_vertices.size());
    }

    bool reachable(int from, int to) const {
        assert(0 <= from && from < size());
        assert(0 <= to && to < size());
        return reachable_vertices[from].test(to);
    }
};

template <class T>
std::optional<DagReachability> dag_reachability(const Graph<T>& g) {
    const int n = g.size();
    auto order = topological_sort(g);
    if (!order) return std::nullopt;

    DagReachability result;
    result.reachable_vertices.assign(n, utilities::DynamicBitset(n));
    result.topological_order = *order;
    for (int i = n - 1; i >= 0; i--) {
        int v = (*order)[i];
        result.reachable_vertices[v].set(v);
        for (const auto& e : g[v]) {
            if (e.alive) result.reachable_vertices[v] |= result.reachable_vertices[e.to];
        }
    }
    return result;
}

template <class T>
struct DagTransitiveReductionResult {
    Graph<T> graph;
    std::vector<int> original_edge_ids;
};

template <class T>
std::optional<DagTransitiveReductionResult<T>> dag_transitive_reduction(const Graph<T>& g) {
    auto reachability = dag_reachability(g);
    if (!reachability) return std::nullopt;

    const int n = g.size();
    std::vector<int> position(n);
    for (int i = 0; i < n; i++) position[reachability->topological_order[i]] = i;

    std::vector<char> kept(g.edge_count(), false);
    for (int v = 0; v < n; v++) {
        std::vector<const Edge<T>*> outgoing;
        outgoing.reserve(g[v].size());
        for (const auto& e : g[v]) {
            if (e.alive) outgoing.push_back(&e);
        }
        std::stable_sort(outgoing.begin(), outgoing.end(), [&](const auto* lhs, const auto* rhs) {
            return position[lhs->to] < position[rhs->to];
        });

        utilities::DynamicBitset covered(n);
        for (const auto* e : outgoing) {
            if (covered.test(e->to)) continue;
            kept[e->id] = true;
            covered |= reachability->reachable_vertices[e->to];
        }
    }

    DagTransitiveReductionResult<T> result;
    result.graph = Graph<T>(n);
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (!e.alive || !kept[e.id]) continue;
            result.graph.add_directed_edge(e.from, e.to, e.cost);
            result.original_edge_ids.push_back(e.id);
        }
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DAG_REACHABILITY_HPP
