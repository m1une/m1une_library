#ifndef M1UNE_GRAPH_DAG_PATH_COUNT_HPP
#define M1UNE_GRAPH_DAG_PATH_COUNT_HPP 1

#include <cassert>
#include <optional>
#include <vector>

#include "graph.hpp"
#include "topological_sort.hpp"

namespace m1une {
namespace graph {

template <class Count = long long, class T>
std::optional<std::vector<Count>> dag_path_count(
    const Graph<T>& g,
    const std::vector<int>& sources
) {
    const int n = g.size();
    auto order = topological_sort(g);
    if (!order) return std::nullopt;

    std::vector<Count> ways(n, Count(0));
    std::vector<char> used_source(n, false);
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (used_source[s]) continue;
        used_source[s] = true;
        ways[s] += Count(1);
    }

    for (int v : *order) {
        for (const auto& e : g[v]) {
            if (e.alive) ways[e.to] += ways[v];
        }
    }
    return ways;
}

template <class Count = long long, class T>
std::optional<std::vector<Count>> dag_path_count(const Graph<T>& g, int s) {
    return dag_path_count<Count>(g, std::vector<int>{s});
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DAG_PATH_COUNT_HPP
