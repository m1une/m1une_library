#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <functional>
#include "../../utilities/fast_io.hpp"
#include <limits>
#include <queue>
#include <random>
#include <utility>
#include <vector>

#include "../../graph/replacement_paths.hpp"

namespace {

using m1une::graph::Graph;
using m1une::graph::GraphPath;

template <class T>
T brute_distance(const Graph<T>& g, int s, int t, int removed_edge, int removed_vertex, T inf) {
    if (s == removed_vertex || t == removed_vertex) return inf;
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
            if (!e.alive || e.id == removed_edge || e.to == removed_vertex) continue;
            T nd = d + e.cost;
            if (nd >= inf || dist[e.to] <= nd) continue;
            dist[e.to] = nd;
            que.emplace(nd, e.to);
        }
    }
    return dist[t];
}

template <class T>
void compare_with_brute(const Graph<T>& g, const GraphPath& path) {
    auto edge_result = m1une::graph::edge_replacement_paths(g, path);
    auto vertex_result = m1une::graph::vertex_replacement_paths(g, path);
    assert(edge_result.path.vertices == path.vertices);
    assert(edge_result.path.edges == path.edges);
    assert(vertex_result.path.vertices == path.vertices);
    assert(vertex_result.path.edges == path.edges);
    assert(edge_result.replacement_dist.size() == path.edges.size());
    assert(vertex_result.replacement_dist.size() == path.vertices.size());
    for (int i = 0; i < int(path.edges.size()); i++) {
        T expected = brute_distance(
            g, path.vertices.front(), path.vertices.back(), path.edges[i], -1, edge_result.inf
        );
        assert(edge_result.replacement_dist[i] == expected);
        assert(edge_result.reachable(i) == (expected != edge_result.inf));
    }
    for (int i = 0; i < int(path.vertices.size()); i++) {
        T expected = brute_distance(
            g, path.vertices.front(), path.vertices.back(), -1, path.vertices[i], vertex_result.inf
        );
        assert(vertex_result.replacement_dist[i] == expected);
        assert(vertex_result.reachable(i) == (expected != vertex_result.inf));
    }
}

template <class T>
void compare_automatic_with_brute(const Graph<T>& g, int s, int t) {
    auto edge_result = m1une::graph::edge_replacement_paths(g, s, t);
    auto vertex_result = m1une::graph::vertex_replacement_paths(g, s, t);
    assert(edge_result.path.vertices == vertex_result.path.vertices);
    assert(edge_result.path.edges == vertex_result.path.edges);
    compare_with_brute(g, edge_result.path);
    assert(edge_result.replacement_dist ==
           m1une::graph::edge_replacement_paths(g, edge_result.path).replacement_dist);
    assert(vertex_result.replacement_dist ==
           m1une::graph::vertex_replacement_paths(g, vertex_result.path).replacement_dist);
}

void test_only_path_and_trivial() {
    Graph<int> g(4);
    int e0 = g.add_edge(0, 1, 2);
    int e1 = g.add_edge(1, 2, 3);
    int e2 = g.add_edge(2, 3, 4);
    GraphPath path;
    path.vertices = {0, 1, 2, 3};
    path.edges = {e0, e1, e2};
    auto edges = m1une::graph::edge_replacement_paths(g, path);
    auto vertices = m1une::graph::vertex_replacement_paths(g, path);
    assert(std::all_of(edges.replacement_dist.begin(), edges.replacement_dist.end(),
                       [&](int x) { return x == edges.inf; }));
    assert(std::all_of(vertices.replacement_dist.begin(), vertices.replacement_dist.end(),
                       [&](int x) { return x == vertices.inf; }));
    compare_with_brute(g, path);

    auto trivial_edges = m1une::graph::edge_replacement_paths(g, 2, 2);
    auto trivial_vertices = m1une::graph::vertex_replacement_paths(g, 2, 2);
    assert((trivial_edges.path.vertices == std::vector<int>{2}));
    assert(trivial_edges.path.edges.empty());
    assert(trivial_edges.replacement_dist.empty());
    assert((trivial_vertices.replacement_dist == std::vector<int>{trivial_vertices.inf}));
}

void test_parallel_edges_and_inactive_edges() {
    Graph<long long> g(4);
    int fixed = g.add_edge(0, 1, 2);
    int equal_parallel = g.add_edge(0, 1, 2);
    int longer_parallel = g.add_edge(0, 1, 5);
    int e12 = g.add_edge(1, 2, 2);
    int e23 = g.add_edge(2, 3, 2);
    int inactive = g.add_edge(0, 3, 1);
    g.erase_edge(inactive);
    GraphPath path;
    path.vertices = {0, 1, 2, 3};
    path.edges = {fixed, e12, e23};
    auto result = m1une::graph::edge_replacement_paths(g, path);
    assert(result.replacement_dist[0] == 6);
    assert(equal_parallel != fixed && longer_parallel != fixed);
    compare_with_brute(g, path);
}

void test_detour_intervals_and_disconnections() {
    Graph<long long> g(9);
    int e0 = g.add_edge(0, 1, 1);
    int e1 = g.add_edge(1, 2, 1);
    int e2 = g.add_edge(2, 3, 1);
    int e3 = g.add_edge(3, 4, 1);
    g.add_edge(1, 5, 2);
    g.add_edge(5, 2, 2);
    g.add_edge(5, 3, 2);
    g.add_edge(0, 6, 4);
    g.add_edge(6, 3, 4);
    g.add_edge(1, 7, 3);
    g.add_edge(7, 4, 3);
    g.add_edge(0, 8, 20);
    g.add_edge(8, 4, 20);
    GraphPath path;
    path.vertices = {0, 1, 2, 3, 4};
    path.edges = {e0, e1, e2, e3};
    compare_with_brute(g, path);

    Graph<int> bridge(5);
    int b0 = bridge.add_edge(0, 1);
    int b1 = bridge.add_edge(1, 2);
    int b2 = bridge.add_edge(2, 3);
    int b3 = bridge.add_edge(3, 4);
    GraphPath bridge_path;
    bridge_path.vertices = {0, 1, 2, 3, 4};
    bridge_path.edges = {b0, b1, b2, b3};
    compare_with_brute(bridge, bridge_path);
}

void test_multiple_and_external_shortest_paths() {
    Graph<int> g(4);
    int e02 = g.add_edge(0, 2, 1);
    int e23 = g.add_edge(2, 3, 1);
    int e01 = g.add_edge(0, 1, 1);
    int e13 = g.add_edge(1, 3, 1);
    GraphPath through_two;
    through_two.vertices = {0, 2, 3};
    through_two.edges = {e02, e23};
    GraphPath through_one;
    through_one.vertices = {0, 1, 3};
    through_one.edges = {e01, e13};
    compare_with_brute(g, through_two);
    compare_with_brute(g, through_one);
    compare_automatic_with_brute(g, 0, 3);
    auto result = m1une::graph::edge_replacement_paths(g, through_two);
    assert(result.replacement_dist == std::vector<int>(2, 2));
}

template <class T>
std::vector<GraphPath> enumerate_shortest_paths(const Graph<T>& g, int s, int t, int limit) {
    auto from_s = m1une::graph::dijkstra(g, s);
    std::vector<GraphPath> paths;
    GraphPath current;
    current.vertices.push_back(s);
    std::vector<char> used(g.size(), false);
    used[s] = true;
    auto dfs = [&](auto&& self, int v) -> void {
        if (int(paths.size()) == limit) return;
        if (v == t) {
            paths.push_back(current);
            return;
        }
        for (const auto& e : g[v]) {
            if (!e.alive || used[e.to]) continue;
            if (from_s.dist[v] + e.cost != from_s.dist[e.to]) continue;
            used[e.to] = true;
            current.vertices.push_back(e.to);
            current.edges.push_back(e.id);
            self(self, e.to);
            current.edges.pop_back();
            current.vertices.pop_back();
            used[e.to] = false;
        }
    };
    dfs(dfs, s);
    return paths;
}

void test_randomized() {
    std::mt19937 rng(712367821);
    for (int iteration = 0; iteration < 1500; iteration++) {
        int n = 2 + int(rng() % 7);
        Graph<long long> g(n);
        int attempts = int(rng() % 22);
        for (int i = 0; i < attempts; i++) {
            int u = int(rng() % n);
            int v = int(rng() % n);
            if (u == v) continue;
            int id = g.add_edge(u, v, 1 + int(rng() % 10));
            if (rng() % 13 == 0) g.erase_edge(id);
        }
        int s = int(rng() % n);
        int t = int(rng() % n);
        if (s == t) t = (t + 1) % n;
        auto shortest = m1une::graph::dijkstra(g, s);
        if (!shortest.reachable(t)) continue;
        compare_automatic_with_brute(g, s, t);
        auto paths = enumerate_shortest_paths(g, s, t, 5);
        assert(!paths.empty());
        for (const auto& path : paths) compare_with_brute(g, path);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_only_path_and_trivial();
    test_parallel_edges_and_inactive_edges();
    test_detour_intervals_and_disconnections();
    test_multiple_and_external_shortest_paths();
    test_randomized();

    int a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
