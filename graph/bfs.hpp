#ifndef M1UNE_GRAPH_BFS_HPP
#define M1UNE_GRAPH_BFS_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct BfsResult {
    std::vector<int> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != -1;
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

namespace bfs_detail {

template <class Callback>
concept BfsCallback =
    std::invocable<Callback&, int, int> ||
    std::invocable<Callback&, int>;

template <BfsCallback Callback>
void invoke_callback(Callback& callback, int vertex, int parent) {
    if constexpr (std::invocable<Callback&, int, int>) {
        std::invoke(callback, vertex, parent);
    } else {
        std::invoke(callback, vertex);
    }
}

template <class T, class Callback>
BfsResult run_bfs(
    const Graph<T>& g,
    const std::vector<int>& sources,
    Callback& callback
) {
    int n = g.size();
    BfsResult result;
    result.dist.assign(n, -1);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);

    std::queue<int> que;
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.dist[s] != -1) continue;
        result.dist[s] = 0;
        invoke_callback(callback, s, -1);
        que.push(s);
    }

    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (result.dist[e.to] != -1) continue;
            result.dist[e.to] = result.dist[v] + 1;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            invoke_callback(callback, e.to, v);
            que.push(e.to);
        }
    }

    return result;
}

}  // namespace bfs_detail

template <class T>
BfsResult bfs(const Graph<T>& g, const std::vector<int>& sources) {
    auto callback = [](int) {};
    return bfs_detail::run_bfs(g, sources, callback);
}

template <class T>
BfsResult bfs(const Graph<T>& g, int s) {
    return bfs(g, std::vector<int>{s});
}

template <class T, class Callback>
requires bfs_detail::BfsCallback<Callback>
BfsResult bfs(
    const Graph<T>& g,
    const std::vector<int>& sources,
    Callback&& callback
) {
    return bfs_detail::run_bfs(g, sources, callback);
}

template <class T, class Callback>
requires bfs_detail::BfsCallback<Callback>
BfsResult bfs(const Graph<T>& g, int source, Callback&& callback) {
    return bfs(
        g,
        std::vector<int>{source},
        std::forward<Callback>(callback)
    );
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BFS_HPP
