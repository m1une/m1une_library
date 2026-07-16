#ifndef M1UNE_GRAPH_DFS_HPP
#define M1UNE_GRAPH_DFS_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct DfsResult {
    std::vector<int> depth;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> root;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> preorder;
    std::vector<int> postorder;
    std::vector<int> roots;

    bool reachable(int vertex) const {
        assert(0 <= vertex && vertex < int(depth.size()));
        return depth[vertex] != -1;
    }

    int component_count() const {
        return int(roots.size());
    }

    std::vector<int> path(int target) const {
        assert(reachable(target));
        std::vector<int> result;
        for (int vertex = target; vertex != -1; vertex = parent[vertex]) {
            result.push_back(vertex);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    bool is_ancestor(int ancestor, int vertex) const {
        assert(0 <= ancestor && ancestor < int(depth.size()));
        assert(0 <= vertex && vertex < int(depth.size()));
        if (!reachable(ancestor) || !reachable(vertex)) return false;
        return tin[ancestor] <= tin[vertex] && tout[vertex] <= tout[ancestor];
    }
};

namespace dfs_detail {

template <class Callback>
concept DfsCallback =
    std::invocable<Callback&, int, int> ||
    std::invocable<Callback&, int>;

template <DfsCallback Callback>
void invoke_callback(Callback& callback, int vertex, int parent) {
    if constexpr (std::invocable<Callback&, int, int>) {
        std::invoke(callback, vertex, parent);
    } else {
        std::invoke(callback, vertex);
    }
}

template <class T, class Callback>
DfsResult run_dfs(
    const Graph<T>& graph,
    const std::vector<int>& sources,
    bool complete_forest,
    Callback& callback
) {
    const int n = graph.size();
    DfsResult result;
    result.depth.assign(n, -1);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.root.assign(n, -1);
    result.tin.assign(n, -1);
    result.tout.assign(n, -1);
    result.preorder.reserve(n);
    result.postorder.reserve(n);
    result.roots.reserve(n);

    struct Frame {
        int vertex;
        int next_edge;
    };
    std::vector<Frame> stack;
    stack.reserve(n);
    int timer = 0;

    auto traverse = [&](int source) {
        assert(0 <= source && source < n);
        if (result.reachable(source)) return;

        result.depth[source] = 0;
        result.root[source] = source;
        result.tin[source] = ++timer;
        result.preorder.push_back(source);
        result.roots.push_back(source);
        invoke_callback(callback, source, -1);
        stack.push_back(Frame{source, 0});

        while (!stack.empty()) {
            Frame& frame = stack.back();
            int vertex = frame.vertex;
            if (frame.next_edge == int(graph[vertex].size())) {
                result.tout[vertex] = ++timer;
                result.postorder.push_back(vertex);
                stack.pop_back();
                continue;
            }

            const Edge<T>& edge = graph[vertex][frame.next_edge++];
            if (!edge.alive || result.reachable(edge.to)) continue;
            result.depth[edge.to] = result.depth[vertex] + 1;
            result.parent[edge.to] = vertex;
            result.parent_edge[edge.to] = edge.id;
            result.root[edge.to] = result.root[vertex];
            result.tin[edge.to] = ++timer;
            result.preorder.push_back(edge.to);
            invoke_callback(callback, edge.to, vertex);
            stack.push_back(Frame{edge.to, 0});
        }
    };

    for (int source : sources) traverse(source);
    if (complete_forest) {
        for (int vertex = 0; vertex < n; vertex++) traverse(vertex);
    }
    return result;
}

}  // namespace dfs_detail

template <class T>
DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources) {
    auto callback = [](int) {};
    return dfs_detail::run_dfs(graph, sources, false, callback);
}

template <class T>
DfsResult dfs(const Graph<T>& graph, int source) {
    return dfs(graph, std::vector<int>{source});
}

template <class T>
DfsResult dfs(const Graph<T>& graph) {
    auto callback = [](int) {};
    return dfs_detail::run_dfs(
        graph,
        std::vector<int>(),
        true,
        callback
    );
}

template <class T, class Callback>
requires dfs_detail::DfsCallback<Callback>
DfsResult dfs(
    const Graph<T>& graph,
    const std::vector<int>& sources,
    Callback&& callback
) {
    return dfs_detail::run_dfs(graph, sources, false, callback);
}

template <class T, class Callback>
requires dfs_detail::DfsCallback<Callback>
DfsResult dfs(const Graph<T>& graph, int source, Callback&& callback) {
    return dfs(
        graph,
        std::vector<int>{source},
        std::forward<Callback>(callback)
    );
}

template <class T, class Callback>
requires dfs_detail::DfsCallback<Callback>
DfsResult dfs(const Graph<T>& graph, Callback&& callback) {
    return dfs_detail::run_dfs(
        graph,
        std::vector<int>(),
        true,
        callback
    );
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DFS_HPP
