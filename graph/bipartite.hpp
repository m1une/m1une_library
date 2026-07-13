#ifndef M1UNE_GRAPH_BIPARTITE_HPP
#define M1UNE_GRAPH_BIPARTITE_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct BipartiteResult {
    bool is_bipartite;
    std::vector<int> color;
    std::vector<int> left_vertices;
    std::vector<int> right_vertices;
    std::vector<int> left_id;
    std::vector<int> right_id;
};

template <class T>
BipartiteResult bipartite(const Graph<T>& g) {
    int n = g.size();
    BipartiteResult result;
    result.is_bipartite = true;
    result.color.assign(n, -1);
    result.left_id.assign(n, -1);
    result.right_id.assign(n, -1);

    std::vector<std::vector<int>> adjacency(n);
    for (const auto& e : g.edges()) {
        adjacency[e.from].push_back(e.to);
        adjacency[e.to].push_back(e.from);
    }

    std::queue<int> que;
    for (int s = 0; s < n; s++) {
        if (result.color[s] != -1) continue;
        result.color[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int to : adjacency[v]) {
                if (result.color[to] == -1) {
                    result.color[to] = result.color[v] ^ 1;
                    que.push(to);
                } else if (result.color[to] == result.color[v]) {
                    result.is_bipartite = false;
                    return result;
                }
            }
        }
    }

    for (int v = 0; v < n; v++) {
        if (result.color[v] == 0) {
            result.left_id[v] = int(result.left_vertices.size());
            result.left_vertices.push_back(v);
        } else {
            result.right_id[v] = int(result.right_vertices.size());
            result.right_vertices.push_back(v);
        }
    }

    return result;
}

template <class T>
bool is_bipartite(const Graph<T>& g) {
    return bipartite(g).is_bipartite;
}

struct BipartiteVertexSet {
    std::vector<int> left;
    std::vector<int> right;

    int size() const {
        return int(left.size() + right.size());
    }
};

struct BipartiteMatching {
    struct Edge {
        int left;
        int right;
        int id;
        bool alive;
    };

    struct Pair {
        int left;
        int right;
        int edge_id;
    };

   private:
    int _left_size;
    int _right_size;
    std::vector<Edge> _edges;
    std::vector<std::vector<int>> _adj;
    std::vector<std::vector<int>> _radj;
    std::vector<int> _left_match;
    std::vector<int> _right_match;
    std::vector<int> _left_match_edge;
    std::vector<int> _right_match_edge;
    bool _calculated;

    void invalidate() {
        _calculated = false;
    }

    void ensure_matching() {
        if (!_calculated) max_matching();
    }

   public:
    BipartiteMatching() : BipartiteMatching(0, 0) {}

    BipartiteMatching(int left_size, int right_size)
        : _left_size(left_size),
          _right_size(right_size),
          _adj(left_size),
          _radj(right_size),
          _left_match(left_size, -1),
          _right_match(right_size, -1),
          _left_match_edge(left_size, -1),
          _right_match_edge(right_size, -1),
          _calculated(false) {
        assert(0 <= left_size);
        assert(0 <= right_size);
    }

    int left_size() const {
        return _left_size;
    }

    int right_size() const {
        return _right_size;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    int add_edge(int left, int right) {
        assert(0 <= left && left < _left_size);
        assert(0 <= right && right < _right_size);
        int id = int(_edges.size());
        _edges.push_back(Edge{left, right, id, true});
        _adj[left].push_back(id);
        _radj[right].push_back(id);
        invalidate();
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_edges.size()));
        return _edges[i];
    }

    std::vector<Edge> edges(bool include_inactive = false) const {
        std::vector<Edge> result;
        result.reserve(_edges.size());
        for (const auto& e : _edges) {
            if (include_inactive || e.alive) result.push_back(e);
        }
        return result;
    }

    void set_edge_alive(int id, bool alive) {
        assert(0 <= id && id < int(_edges.size()));
        _edges[id].alive = alive;
        invalidate();
    }

    void erase_edge(int id) {
        set_edge_alive(id, false);
    }

    void revive_edge(int id) {
        set_edge_alive(id, true);
    }

    bool is_edge_alive(int id) const {
        assert(0 <= id && id < int(_edges.size()));
        return _edges[id].alive;
    }

    int max_matching() {
        _left_match.assign(_left_size, -1);
        _right_match.assign(_right_size, -1);
        _left_match_edge.assign(_left_size, -1);
        _right_match_edge.assign(_right_size, -1);

        std::vector<int> dist(_left_size);
        auto bfs = [&]() -> bool {
            std::queue<int> que;
            bool found = false;
            for (int l = 0; l < _left_size; l++) {
                if (_left_match[l] == -1) {
                    dist[l] = 0;
                    que.push(l);
                } else {
                    dist[l] = -1;
                }
            }

            while (!que.empty()) {
                int l = que.front();
                que.pop();
                for (int id : _adj[l]) {
                    const auto& e = _edges[id];
                    if (!e.alive) continue;
                    int next_left = _right_match[e.right];
                    if (next_left == -1) {
                        found = true;
                    } else if (dist[next_left] == -1) {
                        dist[next_left] = dist[l] + 1;
                        que.push(next_left);
                    }
                }
            }
            return found;
        };

        auto dfs = [&](auto self, int l) -> bool {
            for (int id : _adj[l]) {
                const auto& e = _edges[id];
                if (!e.alive) continue;
                int next_left = _right_match[e.right];
                if (next_left != -1 && (dist[next_left] != dist[l] + 1 || !self(self, next_left))) {
                    continue;
                }
                _left_match[l] = e.right;
                _right_match[e.right] = l;
                _left_match_edge[l] = id;
                _right_match_edge[e.right] = id;
                return true;
            }
            dist[l] = -1;
            return false;
        };

        int result = 0;
        while (bfs()) {
            for (int l = 0; l < _left_size; l++) {
                if (_left_match[l] == -1 && dfs(dfs, l)) result++;
            }
        }

        _calculated = true;
        return result;
    }

    int matching_size() {
        ensure_matching();
        int result = 0;
        for (int right : _left_match) {
            if (right != -1) result++;
        }
        return result;
    }

    std::vector<int> left_match() {
        ensure_matching();
        return _left_match;
    }

    std::vector<int> right_match() {
        ensure_matching();
        return _right_match;
    }

    std::vector<Pair> matching() {
        ensure_matching();
        std::vector<Pair> result;
        for (int l = 0; l < _left_size; l++) {
            if (_left_match[l] != -1) result.push_back(Pair{l, _left_match[l], _left_match_edge[l]});
        }
        return result;
    }

    BipartiteVertexSet minimum_vertex_cover() {
        ensure_matching();

        std::vector<char> visited_left(_left_size, false), visited_right(_right_size, false);
        std::queue<int> que;
        for (int l = 0; l < _left_size; l++) {
            if (_left_match[l] == -1) {
                visited_left[l] = true;
                que.push(l);
            }
        }

        while (!que.empty()) {
            int l = que.front();
            que.pop();
            for (int id : _adj[l]) {
                const auto& e = _edges[id];
                if (!e.alive || _left_match_edge[l] == id || visited_right[e.right]) continue;
                visited_right[e.right] = true;
                int next_left = _right_match[e.right];
                if (next_left != -1 && !visited_left[next_left]) {
                    visited_left[next_left] = true;
                    que.push(next_left);
                }
            }
        }

        BipartiteVertexSet result;
        for (int l = 0; l < _left_size; l++) {
            if (!visited_left[l]) result.left.push_back(l);
        }
        for (int r = 0; r < _right_size; r++) {
            if (visited_right[r]) result.right.push_back(r);
        }
        return result;
    }

    BipartiteVertexSet maximum_independent_set() {
        auto cover = minimum_vertex_cover();
        std::vector<char> in_left_cover(_left_size, false), in_right_cover(_right_size, false);
        for (int l : cover.left) in_left_cover[l] = true;
        for (int r : cover.right) in_right_cover[r] = true;

        BipartiteVertexSet result;
        for (int l = 0; l < _left_size; l++) {
            if (!in_left_cover[l]) result.left.push_back(l);
        }
        for (int r = 0; r < _right_size; r++) {
            if (!in_right_cover[r]) result.right.push_back(r);
        }
        return result;
    }

    std::optional<std::vector<int>> minimum_edge_cover() {
        ensure_matching();

        std::vector<int> result;
        std::vector<char> covered_left(_left_size, false), covered_right(_right_size, false);
        std::vector<char> used_edge(_edges.size(), false);

        auto use_edge = [&](int id) {
            if (used_edge[id]) return;
            used_edge[id] = true;
            result.push_back(id);
            covered_left[_edges[id].left] = true;
            covered_right[_edges[id].right] = true;
        };

        for (int l = 0; l < _left_size; l++) {
            if (_left_match_edge[l] != -1) use_edge(_left_match_edge[l]);
        }

        for (int l = 0; l < _left_size; l++) {
            if (covered_left[l]) continue;
            int id = -1;
            for (int edge_id : _adj[l]) {
                if (_edges[edge_id].alive) {
                    id = edge_id;
                    break;
                }
            }
            if (id == -1) return std::nullopt;
            use_edge(id);
        }

        for (int r = 0; r < _right_size; r++) {
            if (covered_right[r]) continue;
            int id = -1;
            for (int edge_id : _radj[r]) {
                if (_edges[edge_id].alive) {
                    id = edge_id;
                    break;
                }
            }
            if (id == -1) return std::nullopt;
            use_edge(id);
        }

        return result;
    }
};

struct BipartiteMatchingGraph {
    BipartiteResult parts;
    BipartiteMatching matching;
    std::vector<int> original_edge_id;

    int left_vertex(int left) const {
        assert(0 <= left && left < int(parts.left_vertices.size()));
        return parts.left_vertices[left];
    }

    int right_vertex(int right) const {
        assert(0 <= right && right < int(parts.right_vertices.size()));
        return parts.right_vertices[right];
    }

    int original_edge(int edge_id) const {
        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));
        return original_edge_id[edge_id];
    }
};

template <class T>
std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>& g) {
    auto parts = bipartite(g);
    if (!parts.is_bipartite) return std::nullopt;

    BipartiteMatchingGraph result;
    result.parts = parts;
    result.matching = BipartiteMatching(int(parts.left_vertices.size()), int(parts.right_vertices.size()));

    for (const auto& e : g.edges()) {
        int left, right;
        if (parts.color[e.from] == 0) {
            left = parts.left_id[e.from];
            right = parts.right_id[e.to];
        } else {
            left = parts.left_id[e.to];
            right = parts.right_id[e.from];
        }
        int id = result.matching.add_edge(left, right);
        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id + 1);
        result.original_edge_id[id] = e.id;
    }

    return result;
}

struct BipartiteEdgeColoringResult {
    int color_count;
    std::vector<int> color;
};

namespace detail {

struct BipartiteEdgeColoringGroups {
    int count;
    std::vector<int> group;
};

inline BipartiteEdgeColoringGroups group_vertices(
    const std::vector<int>& degree,
    int maximum_degree
) {
    BipartiteEdgeColoringGroups result;
    result.count = 0;
    result.group.assign(degree.size(), -1);
    int current_degree = 0;
    for (int vertex = 0; vertex < int(degree.size()); vertex++) {
        if (degree[vertex] == 0) continue;
        if (result.count == 0 || current_degree + degree[vertex] > maximum_degree) {
            result.count++;
            current_degree = 0;
        }
        result.group[vertex] = result.count - 1;
        current_degree += degree[vertex];
    }
    return result;
}

class BipartiteEdgeColoringSolver {
   private:
    int _side_size;
    int _original_edge_count;
    std::vector<int> _left;
    std::vector<int> _right;
    std::vector<int> _color;
    std::vector<int> _used_stamp;
    int _stamp;

    int other_endpoint(int vertex, int edge) const {
        if (vertex < _side_size) return _side_size + _right[edge];
        return _left[edge];
    }

    std::vector<int> perfect_matching(const std::vector<int>& edge_ids) const {
        std::vector<std::vector<int>> adjacency(_side_size);
        for (int edge : edge_ids) adjacency[_left[edge]].push_back(edge);

        std::vector<int> right_match(_side_size, -1);
        std::vector<int> left_match_edge(_side_size, -1);
        int matching_size = 0;
        for (int left = 0; left < _side_size; left++) {
            for (int edge : adjacency[left]) {
                int right = _right[edge];
                if (right_match[right] != -1) continue;
                right_match[right] = left;
                left_match_edge[left] = edge;
                matching_size++;
                break;
            }
        }

        std::vector<int> distance(_side_size);
        std::vector<int> next_edge(_side_size);
        std::vector<int> left_stack;
        std::vector<int> path_edges;
        left_stack.reserve(_side_size);
        path_edges.reserve(_side_size);

        while (matching_size < _side_size) {
            std::queue<int> queue;
            std::fill(distance.begin(), distance.end(), -1);
            for (int left = 0; left < _side_size; left++) {
                if (left_match_edge[left] != -1) continue;
                distance[left] = 0;
                queue.push(left);
            }

            bool reachable_free_right = false;
            while (!queue.empty()) {
                int left = queue.front();
                queue.pop();
                for (int edge : adjacency[left]) {
                    int next_left = right_match[_right[edge]];
                    if (next_left == -1) {
                        reachable_free_right = true;
                    } else if (distance[next_left] == -1) {
                        distance[next_left] = distance[left] + 1;
                        queue.push(next_left);
                    }
                }
            }
            assert(reachable_free_right);

            std::fill(next_edge.begin(), next_edge.end(), 0);
            int augmented = 0;
            for (int root = 0; root < _side_size; root++) {
                if (left_match_edge[root] != -1 || distance[root] == -1) continue;
                left_stack.clear();
                path_edges.clear();
                left_stack.push_back(root);
                bool found = false;

                while (!left_stack.empty() && !found) {
                    int left = left_stack.back();
                    bool advanced = false;
                    while (next_edge[left] < int(adjacency[left].size())) {
                        int edge = adjacency[left][next_edge[left]++];
                        int right = _right[edge];
                        int next_left = right_match[right];
                        if (next_left == -1) {
                            left_match_edge[left] = edge;
                            right_match[right] = left;
                            for (int index = int(path_edges.size()) - 1; index >= 0; index--) {
                                int path_edge = path_edges[index];
                                int path_left = left_stack[index];
                                left_match_edge[path_left] = path_edge;
                                right_match[_right[path_edge]] = path_left;
                            }
                            found = true;
                            break;
                        }
                        if (distance[next_left] != distance[left] + 1) continue;
                        path_edges.push_back(edge);
                        left_stack.push_back(next_left);
                        advanced = true;
                        break;
                    }
                    if (found || advanced) continue;
                    distance[left] = -1;
                    left_stack.pop_back();
                    if (path_edges.size() == left_stack.size() && !path_edges.empty()) {
                        path_edges.pop_back();
                    }
                }
                if (found) augmented++;
            }
            assert(augmented > 0);
            matching_size += augmented;
        }

        return left_match_edge;
    }

    std::pair<std::vector<int>, std::vector<int>> split_even(
        const std::vector<int>& edge_ids
    ) {
        std::vector<std::vector<int>> incidence(std::size_t(2) * _side_size);
        for (int edge : edge_ids) {
            incidence[_left[edge]].push_back(edge);
            incidence[_side_size + _right[edge]].push_back(edge);
        }

        _stamp++;
        assert(_stamp > 0);
        std::vector<int> next_edge(std::size_t(2) * _side_size, 0);
        std::vector<int> first;
        std::vector<int> second;
        first.reserve(edge_ids.size() / 2);
        second.reserve(edge_ids.size() / 2);

        for (int start = 0; start < 2 * _side_size; start++) {
            while (true) {
                while (next_edge[start] < int(incidence[start].size()) &&
                       _used_stamp[incidence[start][next_edge[start]]] == _stamp) {
                    next_edge[start]++;
                }
                if (next_edge[start] == int(incidence[start].size())) break;

                int vertex = start;
                bool parity = false;
                do {
                    while (next_edge[vertex] < int(incidence[vertex].size()) &&
                           _used_stamp[incidence[vertex][next_edge[vertex]]] == _stamp) {
                        next_edge[vertex]++;
                    }
                    assert(next_edge[vertex] < int(incidence[vertex].size()));
                    int edge = incidence[vertex][next_edge[vertex]++];
                    _used_stamp[edge] = _stamp;
                    if (!parity) {
                        first.push_back(edge);
                    } else {
                        second.push_back(edge);
                    }
                    parity = !parity;
                    vertex = other_endpoint(vertex, edge);
                } while (vertex != start);
                assert(!parity);
            }
        }
        assert(first.size() == second.size());
        return {std::move(first), std::move(second)};
    }

    void color_regular(const std::vector<int>& edge_ids, int degree, int offset) {
        assert(std::size_t(_side_size) * std::size_t(degree) == edge_ids.size());
        if (degree == 0) return;
        if (degree == 1) {
            for (int edge : edge_ids) {
                if (edge < _original_edge_count) _color[edge] = offset;
            }
            return;
        }

        if (degree % 2 == 1) {
            std::vector<int> matching = perfect_matching(edge_ids);
            _stamp++;
            assert(_stamp > 0);
            for (int edge : matching) {
                _used_stamp[edge] = _stamp;
                if (edge < _original_edge_count) _color[edge] = offset;
            }
            std::vector<int> remaining;
            remaining.reserve(edge_ids.size() - matching.size());
            for (int edge : edge_ids) {
                if (_used_stamp[edge] != _stamp) remaining.push_back(edge);
            }
            color_regular(remaining, degree - 1, offset + 1);
            return;
        }

        auto [first, second] = split_even(edge_ids);
        color_regular(first, degree / 2, offset);
        color_regular(second, degree / 2, offset + degree / 2);
    }

   public:
    BipartiteEdgeColoringSolver(
        int side_size,
        int original_edge_count,
        std::vector<int> left,
        std::vector<int> right
    )
        : _side_size(side_size),
          _original_edge_count(original_edge_count),
          _left(std::move(left)),
          _right(std::move(right)),
          _color(original_edge_count, -1),
          _used_stamp(_left.size(), 0),
          _stamp(0) {}

    std::vector<int> solve(int degree) {
        std::vector<int> edge_ids(_left.size());
        for (int edge = 0; edge < int(edge_ids.size()); edge++) edge_ids[edge] = edge;
        color_regular(edge_ids, degree, 0);
        for (int color : _color) assert(0 <= color && color < degree);
        return _color;
    }
};

}  // namespace detail

// Returns an optimal edge coloring of a bipartite multigraph.
inline BipartiteEdgeColoringResult bipartite_edge_coloring(
    int left_size,
    int right_size,
    const std::vector<std::pair<int, int>>& edges
) {
    assert(left_size >= 0);
    assert(right_size >= 0);
    assert(edges.size() <= std::size_t(std::numeric_limits<int>::max()));

    std::vector<int> left_degree(left_size, 0);
    std::vector<int> right_degree(right_size, 0);
    int maximum_degree = 0;
    for (auto [left, right] : edges) {
        assert(0 <= left && left < left_size);
        assert(0 <= right && right < right_size);
        left_degree[left]++;
        right_degree[right]++;
        maximum_degree = std::max(maximum_degree, left_degree[left]);
        maximum_degree = std::max(maximum_degree, right_degree[right]);
    }

    BipartiteEdgeColoringResult result;
    result.color_count = maximum_degree;
    if (edges.empty()) return result;

    detail::BipartiteEdgeColoringGroups left_groups =
        detail::group_vertices(left_degree, maximum_degree);
    detail::BipartiteEdgeColoringGroups right_groups =
        detail::group_vertices(right_degree, maximum_degree);
    int side_size = std::max(left_groups.count, right_groups.count);

    std::vector<int> contracted_left;
    std::vector<int> contracted_right;
    contracted_left.reserve(std::size_t(3) * edges.size());
    contracted_right.reserve(std::size_t(3) * edges.size());
    std::vector<int> contracted_left_degree(side_size, 0);
    std::vector<int> contracted_right_degree(side_size, 0);
    for (auto [left, right] : edges) {
        int contracted_left_vertex = left_groups.group[left];
        int contracted_right_vertex = right_groups.group[right];
        contracted_left.push_back(contracted_left_vertex);
        contracted_right.push_back(contracted_right_vertex);
        contracted_left_degree[contracted_left_vertex]++;
        contracted_right_degree[contracted_right_vertex]++;
    }

    int left = 0;
    int right = 0;
    while (true) {
        while (left < side_size && contracted_left_degree[left] == maximum_degree) left++;
        while (right < side_size && contracted_right_degree[right] == maximum_degree) right++;
        if (left == side_size || right == side_size) break;
        contracted_left.push_back(left);
        contracted_right.push_back(right);
        contracted_left_degree[left]++;
        contracted_right_degree[right]++;
    }
    assert(left == side_size && right == side_size);
    assert(contracted_left.size() == std::size_t(side_size) * std::size_t(maximum_degree));

    detail::BipartiteEdgeColoringSolver solver(
        side_size,
        int(edges.size()),
        std::move(contracted_left),
        std::move(contracted_right)
    );
    result.color = solver.solve(maximum_degree);
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BIPARTITE_HPP
