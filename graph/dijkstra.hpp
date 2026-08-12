#ifndef M1UNE_GRAPH_DIJKSTRA_HPP
#define M1UNE_GRAPH_DIJKSTRA_HPP 1

#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct DijkstraResult {
    std::vector<T> dist;
    std::vector<char> reached;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    T inf = T();

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return reached[v];
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

namespace internal {

template <class T>
struct DijkstraQueueNode {
    T dist;
    int vertex;
};

template <class T>
struct DijkstraQueueCompare {
    bool operator()(const DijkstraQueueNode<T>& first,
                    const DijkstraQueueNode<T>& second) const {
        return second.dist < first.dist;
    }
};

}  // namespace internal

template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& g,
                           const std::vector<int>& sources) {
    int n = g.size();
    DijkstraResult<T> result;
    result.dist.resize(n);
    result.reached.assign(n, false);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);

    using Node = internal::DijkstraQueueNode<T>;
    using Compare = internal::DijkstraQueueCompare<T>;
    std::priority_queue<Node, std::vector<Node>, Compare> que;
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.reached[s]) continue;
        result.reached[s] = true;
        result.dist[s] = T();
        que.push(Node{T(), s});
    }

    while (!que.empty()) {
        Node current = que.top();
        que.pop();
        if (result.dist[current.vertex] < current.dist) continue;
        for (const auto& e : g[current.vertex]) {
            if (!e.alive) continue;
            T nd = current.dist + e.cost;
            if (result.reached[e.to] && !(nd < result.dist[e.to])) continue;
            result.reached[e.to] = true;
            result.dist[e.to] = nd;
            result.parent[e.to] = current.vertex;
            result.parent_edge[e.to] = e.id;
            que.push(Node{std::move(nd), e.to});
        }
    }

    return result;
}

template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& g, int s) {
    return dijkstra(g, std::vector<int>{s});
}

// Compatibility overload: unreachable distances are replaced by inf after the
// search. Reachability itself never depends on this sentinel.
template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& g,
                           const std::vector<int>& sources, const T& inf) {
    DijkstraResult<T> result = dijkstra(g, sources);
    result.inf = inf;
    for (int v = 0; v < int(result.dist.size()); v++) {
        if (!result.reachable(v)) result.dist[v] = inf;
    }
    return result;
}

template <class T>
DijkstraResult<T> dijkstra(const Graph<T>& g, int s, const T& inf) {
    return dijkstra(g, std::vector<int>{s}, inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DIJKSTRA_HPP
