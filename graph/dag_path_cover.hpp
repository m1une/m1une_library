#ifndef M1UNE_GRAPH_DAG_PATH_COVER_HPP
#define M1UNE_GRAPH_DAG_PATH_COVER_HPP 1

#include <cassert>
#include <optional>
#include <vector>

#include "bipartite.hpp"
#include "graph.hpp"
#include "topological_sort.hpp"

namespace m1une {
namespace graph {

struct DagPathCoverResult {
    std::vector<std::vector<int>> paths;
    std::vector<std::vector<int>> path_edge_ids;
    std::vector<int> predecessor;
    std::vector<int> successor;
    std::vector<int> predecessor_edge;
    std::vector<int> successor_edge;

    int size() const {
        return int(paths.size());
    }
};

template <class T>
std::optional<DagPathCoverResult> minimum_dag_path_cover(const Graph<T>& g) {
    const int n = g.size();
    if (!topological_sort(g)) return std::nullopt;

    BipartiteMatching matching(n, n);
    std::vector<int> original_edge_id;
    for (int v = 0; v < n; v++) {
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            matching.add_edge(v, e.to);
            original_edge_id.push_back(e.id);
        }
    }

    DagPathCoverResult result;
    result.predecessor.assign(n, -1);
    result.successor.assign(n, -1);
    result.predecessor_edge.assign(n, -1);
    result.successor_edge.assign(n, -1);
    for (const auto& pair : matching.matching()) {
        const int edge_id = original_edge_id[pair.edge_id];
        result.successor[pair.left] = pair.right;
        result.successor_edge[pair.left] = edge_id;
        result.predecessor[pair.right] = pair.left;
        result.predecessor_edge[pair.right] = edge_id;
    }

    int covered = 0;
    for (int s = 0; s < n; s++) {
        if (result.predecessor[s] != -1) continue;
        result.paths.emplace_back();
        result.path_edge_ids.emplace_back();
        for (int v = s; v != -1; v = result.successor[v]) {
            result.paths.back().push_back(v);
            covered++;
            if (result.successor_edge[v] != -1) {
                result.path_edge_ids.back().push_back(result.successor_edge[v]);
            }
        }
    }
    assert(covered == n);
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DAG_PATH_COVER_HPP
