#ifndef M1UNE_GRAPH_REPLACEMENT_PATHS_HPP
#define M1UNE_GRAPH_REPLACEMENT_PATHS_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "dijkstra.hpp"
#include "graph.hpp"

namespace m1une {
namespace graph {

struct GraphPath {
    std::vector<int> vertices;
    std::vector<int> edges;
};

template <class T>
struct EdgeReplacementPathsResult {
    GraphPath path;
    std::vector<T> replacement_dist;
    T inf;

    bool reachable(int path_edge_index) const {
        assert(0 <= path_edge_index && path_edge_index < int(replacement_dist.size()));
        return replacement_dist[path_edge_index] != inf;
    }
};

template <class T>
struct VertexReplacementPathsResult {
    GraphPath path;
    std::vector<T> replacement_dist;
    T inf;

    bool reachable(int path_vertex_index) const {
        assert(0 <= path_vertex_index && path_vertex_index < int(replacement_dist.size()));
        return replacement_dist[path_vertex_index] != inf;
    }
};

namespace internal {

template <class T>
T replacement_paths_safe_add(T a, T b, T inf) {
    if (a >= inf || b >= inf) return inf;
    if (a > inf - b) return inf;
    return a + b;
}

template <class T>
DijkstraResult<T> replacement_paths_dijkstra(const Graph<T>& g, int s, T inf) {
    int n = g.size();
    assert(0 <= s && s < n);
    DijkstraResult<T> result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.inf = inf;

    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    result.dist[s] = T(0);
    que.emplace(T(0), s);
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (result.dist[v] != d) continue;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            T nd = replacement_paths_safe_add(d, e.cost, inf);
            if (result.dist[e.to] <= nd) continue;
            result.dist[e.to] = nd;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            que.emplace(nd, e.to);
        }
    }
    return result;
}

template <class T>
std::vector<Edge<T>> replacement_paths_validate_graph(const Graph<T>& g, T inf) {
    assert(T(0) < inf);
    std::vector<int> occurrence(g.edge_count(), 0);
    std::vector<Edge<T>> edge_by_id(g.edge_count());
    for (int v = 0; v < g.size(); v++) {
        for (const auto& e : g[v]) {
            assert(e.from == v);
            assert(0 <= e.to && e.to < g.size());
            assert(0 <= e.id && e.id < g.edge_count());
            if (e.alive) assert(T(0) < e.cost);
            if (occurrence[e.id] == 0) {
                edge_by_id[e.id] = e;
            } else {
                assert(occurrence[e.id] == 1);
                const auto& other = edge_by_id[e.id];
                assert(e.from == other.to && e.to == other.from);
                assert(e.cost == other.cost && e.alive == other.alive);
            }
            occurrence[e.id]++;
        }
    }

    for (int id = 0; id < g.edge_count(); id++) {
        // add_edge creates exactly two mutually reversed arcs with one logical id.
        assert(occurrence[id] == 2);
    }
    return edge_by_id;
}

template <class T>
void replacement_paths_validate_path(const Graph<T>& g, const GraphPath& path,
                                     const std::vector<Edge<T>>& edge_by_id,
                                     const DijkstraResult<T>& from_s) {
    assert(!path.vertices.empty());
    assert(path.edges.size() + 1 == path.vertices.size());
    std::vector<char> used_vertex(g.size(), false);
    for (int v : path.vertices) {
        assert(0 <= v && v < g.size());
        assert(!used_vertex[v]);
        used_vertex[v] = true;
    }

    T path_cost = T(0);
    for (int i = 0; i < int(path.edges.size()); i++) {
        int id = path.edges[i];
        assert(0 <= id && id < g.edge_count());
        assert(g.is_edge_alive(id));
        const auto& e = edge_by_id[id];
        int u = path.vertices[i];
        int v = path.vertices[i + 1];
        assert((e.from == u && e.to == v) || (e.from == v && e.to == u));
        assert(T(0) < e.cost);
        path_cost = replacement_paths_safe_add(path_cost, e.cost, from_s.inf);
    }
    assert(from_s.reachable(path.vertices.back()));
    assert(path_cost == from_s.dist[path.vertices.back()]);
}

template <class T>
GraphPath replacement_paths_restore_path(const DijkstraResult<T>& result, int s, int t) {
    assert(result.reachable(t));
    GraphPath path;
    for (int v = t; v != s; v = result.parent[v]) {
        assert(v != -1 && result.parent[v] != -1 && result.parent_edge[v] != -1);
        path.vertices.push_back(v);
        path.edges.push_back(result.parent_edge[v]);
    }
    path.vertices.push_back(s);
    std::reverse(path.vertices.begin(), path.vertices.end());
    std::reverse(path.edges.begin(), path.edges.end());
    return path;
}

template <class T>
struct ReplacementPathsData {
    GraphPath path;
    std::vector<T> dist_s;
    std::vector<T> dist_t;
    std::vector<int> block;
    std::vector<char> is_path_edge;
    std::vector<Edge<T>> edge_by_id;
    T inf;
};

template <class T>
ReplacementPathsData<T> replacement_paths_prepare(const Graph<T>& g, const GraphPath& path,
                                                   T inf, const DijkstraResult<T>* known_from_s) {
    auto edge_by_id = replacement_paths_validate_graph(g, inf);
    int s = path.vertices.front();
    int t = path.vertices.back();
    auto computed_from_s = known_from_s == nullptr
                               ? replacement_paths_dijkstra(g, s, inf)
                               : DijkstraResult<T>();
    const auto& from_s = known_from_s == nullptr ? computed_from_s : *known_from_s;
    replacement_paths_validate_path(g, path, edge_by_id, from_s);
    auto from_t = replacement_paths_dijkstra(g, t, inf);

    int n = g.size();
    std::vector<int> path_position(n, -1);
    std::vector<char> is_path_edge(g.edge_count(), false);
    for (int i = 0; i < int(path.vertices.size()); i++) path_position[path.vertices[i]] = i;
    for (int id : path.edges) is_path_edge[id] = true;

    std::vector<int> parent(n, -1);
    for (int i = 0; i < int(path.edges.size()); i++) {
        int v = path.vertices[i + 1];
        parent[v] = path.vertices[i];
        const auto& e = edge_by_id[path.edges[i]];
        assert(replacement_paths_safe_add(from_s.dist[parent[v]], e.cost, inf) == from_s.dist[v]);
    }
    for (int v = 0; v < n; v++) {
        if (!from_s.reachable(v) || v == s || path_position[v] != -1) continue;
        for (const auto& e : g[v]) {
            if (!e.alive || !from_s.reachable(e.to)) continue;
            if (replacement_paths_safe_add(from_s.dist[e.to], e.cost, inf) != from_s.dist[v]) {
                continue;
            }
            parent[v] = e.to;
            break;
        }
        assert(parent[v] != -1);
        assert(from_s.dist[parent[v]] < from_s.dist[v]);
    }

    std::vector<std::vector<int>> children(n);
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) children[parent[v]].push_back(v);
    }
    std::vector<int> block(n, -1);
    block[s] = 0;
    std::vector<int> stack = {s};
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        for (int to : children[v]) {
            block[to] = path_position[to] == -1 ? block[v] : path_position[to];
            stack.push_back(to);
        }
    }
    for (int v = 0; v < n; v++) assert(!from_s.reachable(v) || block[v] != -1);

    return {path, from_s.dist, from_t.dist, block, is_path_edge, edge_by_id, inf};
}

template <class T>
class ReplacementPathsRangeChmin {
   private:
    int _size;
    std::vector<T> _lazy;

   public:
    ReplacementPathsRangeChmin(int n, T inf) : _size(1) {
        while (_size < n) _size <<= 1;
        _lazy.assign(2 * _size, inf);
    }

    void apply(int l, int r, T value) {
        assert(0 <= l && l <= r && r <= _size);
        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                _lazy[l] = std::min(_lazy[l], value);
                l++;
            }
            if (r & 1) {
                --r;
                _lazy[r] = std::min(_lazy[r], value);
            }
        }
    }

    std::vector<T> values(int n) {
        for (int v = 1; v < _size; v++) {
            _lazy[2 * v] = std::min(_lazy[2 * v], _lazy[v]);
            _lazy[2 * v + 1] = std::min(_lazy[2 * v + 1], _lazy[v]);
        }
        return std::vector<T>(_lazy.begin() + _size, _lazy.begin() + _size + n);
    }
};

template <class T>
std::vector<T> replacement_paths_solve_edges(const ReplacementPathsData<T>& data) {
    int answer_size = int(data.path.edges.size());
    ReplacementPathsRangeChmin<T> range_chmin(answer_size, data.inf);
    for (const auto& e : data.edge_by_id) {
        if (!e.alive || data.is_path_edge[e.id]) continue;
        int u = e.from;
        int v = e.to;
        if (data.block[u] == -1 || data.block[v] == -1 || data.block[u] == data.block[v]) continue;
        if (data.block[u] > data.block[v]) std::swap(u, v);
        int a = data.block[u];
        int b = data.block[v];
        T candidate = replacement_paths_safe_add(data.dist_s[u], e.cost, data.inf);
        candidate = replacement_paths_safe_add(candidate, data.dist_t[v], data.inf);
        if (candidate == data.inf) continue;
        range_chmin.apply(a, b, candidate);
    }
    return range_chmin.values(answer_size);
}

template <class T>
T replacement_paths_without_vertex(const Graph<T>& g, int s, int t, int removed, T inf) {
    if (s == removed || t == removed) return inf;
    std::vector<T> dist(g.size(), inf);
    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    dist[s] = T(0);
    que.emplace(T(0), s);
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dist[v] != d) continue;
        for (const auto& e : g[v]) {
            if (!e.alive || e.to == removed) continue;
            T nd = replacement_paths_safe_add(d, e.cost, inf);
            if (dist[e.to] <= nd) continue;
            dist[e.to] = nd;
            que.emplace(nd, e.to);
        }
    }
    return dist[t];
}

template <class T>
std::vector<T> replacement_paths_solve_vertices(const Graph<T>& g,
                                                const ReplacementPathsData<T>& data) {
    // One edge can cross an edge cut, but a vertex-avoiding path may enter and
    // leave the failed vertex's tree block through two different detour edges.
    int path_size = int(data.path.vertices.size());
    std::vector<T> answer(path_size, data.inf);
    int s = data.path.vertices.front();
    int t = data.path.vertices.back();
    for (int i = 1; i + 1 < path_size; i++) {
        answer[i] = replacement_paths_without_vertex(g, s, t, data.path.vertices[i], data.inf);
    }
    return answer;
}

}  // namespace internal

template <class T>
EdgeReplacementPathsResult<T> edge_replacement_paths(
    const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4)) {
    assert(!path.vertices.empty());
    auto data = internal::replacement_paths_prepare(
        g, path, inf, static_cast<const DijkstraResult<T>*>(nullptr));
    auto replacement_dist = internal::replacement_paths_solve_edges(data);
    return {path, replacement_dist, inf};
}

template <class T>
EdgeReplacementPathsResult<T> edge_replacement_paths(
    const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4)) {
    assert(0 <= s && s < g.size());
    assert(0 <= t && t < g.size());
    auto from_s = internal::replacement_paths_dijkstra(g, s, inf);
    assert(from_s.reachable(t));
    auto path = internal::replacement_paths_restore_path(from_s, s, t);
    auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);
    auto replacement_dist = internal::replacement_paths_solve_edges(data);
    return {path, replacement_dist, inf};
}

template <class T>
VertexReplacementPathsResult<T> vertex_replacement_paths(
    const Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() / T(4)) {
    assert(!path.vertices.empty());
    auto data = internal::replacement_paths_prepare(
        g, path, inf, static_cast<const DijkstraResult<T>*>(nullptr));
    auto replacement_dist = internal::replacement_paths_solve_vertices(g, data);
    return {path, replacement_dist, inf};
}

template <class T>
VertexReplacementPathsResult<T> vertex_replacement_paths(
    const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4)) {
    assert(0 <= s && s < g.size());
    assert(0 <= t && t < g.size());
    auto from_s = internal::replacement_paths_dijkstra(g, s, inf);
    assert(from_s.reachable(t));
    auto path = internal::replacement_paths_restore_path(from_s, s, t);
    auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);
    auto replacement_dist = internal::replacement_paths_solve_vertices(g, data);
    return {path, replacement_dist, inf};
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_REPLACEMENT_PATHS_HPP
