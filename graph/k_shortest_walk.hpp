#ifndef M1UNE_GRAPH_K_SHORTEST_WALK_HPP
#define M1UNE_GRAPH_K_SHORTEST_WALK_HPP 1

#include <cassert>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

namespace internal {

template <class T>
class KShortestWalkHeap {
    struct Node {
        T key;
        int to;
        int left;
        int right;
        int rank;
    };

    std::vector<Node> _nodes;

    int rank(int root) const {
        return root == -1 ? 0 : _nodes[root].rank;
    }

   public:
    int make_node(T key, int to) {
        int result = int(_nodes.size());
        _nodes.push_back(Node{key, to, -1, -1, 1});
        return result;
    }

    int meld_mutable(int first, int second) {
        if (first == -1) return second;
        if (second == -1) return first;
        if (_nodes[second].key < _nodes[first].key) std::swap(first, second);
        _nodes[first].right = meld_mutable(_nodes[first].right, second);
        if (rank(_nodes[first].left) < rank(_nodes[first].right)) {
            std::swap(_nodes[first].left, _nodes[first].right);
        }
        _nodes[first].rank = rank(_nodes[first].right) + 1;
        return first;
    }

    int meld_persistent(int first, int second) {
        if (first == -1) return second;
        if (second == -1) return first;
        if (_nodes[second].key < _nodes[first].key) std::swap(first, second);
        int result = int(_nodes.size());
        _nodes.push_back(_nodes[first]);
        _nodes[result].right = meld_persistent(_nodes[result].right, second);
        if (rank(_nodes[result].left) < rank(_nodes[result].right)) {
            std::swap(_nodes[result].left, _nodes[result].right);
        }
        _nodes[result].rank = rank(_nodes[result].right) + 1;
        return result;
    }

    const Node& operator[](int index) const {
        return _nodes[index];
    }
};

}  // namespace internal

template <class T>
std::vector<T> k_shortest_walk(
    const Graph<T>& g,
    int s,
    int t,
    int k,
    T inf = std::numeric_limits<T>::max() / T(4)
) {
    int n = g.size();
    assert(0 <= s && s < n);
    assert(0 <= t && t < n);
    assert(0 <= k);
    if (k == 0) return {};

    struct ReverseEdge {
        int from;
        int index;
        T cost;
    };
    std::vector<std::vector<ReverseEdge>> reverse_graph(n);
    for (int from = 0; from < n; from++) {
        for (int index = 0; index < int(g[from].size()); index++) {
            const auto& edge = g[from][index];
            if (!edge.alive) continue;
            assert(T(0) <= edge.cost);
            reverse_graph[edge.to].push_back(ReverseEdge{from, index, edge.cost});
        }
    }

    std::vector<T> dist(n, inf);
    std::vector<int> tree_edge(n, -1);
    std::vector<int> order;
    order.reserve(n);
    using QueueEntry = std::pair<T, int>;
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> queue;
    dist[t] = T(0);
    queue.emplace(T(0), t);
    while (!queue.empty()) {
        auto [current_dist, vertex] = queue.top();
        queue.pop();
        if (dist[vertex] != current_dist) continue;
        order.push_back(vertex);
        for (const auto& edge : reverse_graph[vertex]) {
            T next_dist = current_dist + edge.cost;
            if (dist[edge.from] <= next_dist) continue;
            dist[edge.from] = next_dist;
            tree_edge[edge.from] = edge.index;
            queue.emplace(next_dist, edge.from);
        }
    }
    if (dist[s] == inf) return {};

    internal::KShortestWalkHeap<T> heap_pool;
    std::vector<int> local_heap(n, -1);
    for (int vertex : order) {
        for (int index = 0; index < int(g[vertex].size()); index++) {
            const auto& edge = g[vertex][index];
            if (!edge.alive || dist[edge.to] == inf || index == tree_edge[vertex]) continue;
            T extra = edge.cost + dist[edge.to] - dist[vertex];
            assert(T(0) <= extra);
            int node = heap_pool.make_node(extra, edge.to);
            local_heap[vertex] = heap_pool.meld_mutable(local_heap[vertex], node);
        }
    }

    std::vector<int> path_heap(n, -1);
    for (int vertex : order) {
        int inherited = -1;
        if (tree_edge[vertex] != -1) inherited = path_heap[g[vertex][tree_edge[vertex]].to];
        path_heap[vertex] = heap_pool.meld_persistent(inherited, local_heap[vertex]);
    }

    std::vector<T> result;
    result.reserve(k);
    result.push_back(dist[s]);
    std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> candidates;
    if (path_heap[s] != -1) {
        candidates.emplace(dist[s] + heap_pool[path_heap[s]].key, path_heap[s]);
    }
    while (int(result.size()) < k && !candidates.empty()) {
        auto [cost, node_index] = candidates.top();
        candidates.pop();
        result.push_back(cost);
        const auto& node = heap_pool[node_index];
        if (node.left != -1) {
            candidates.emplace(cost - node.key + heap_pool[node.left].key, node.left);
        }
        if (node.right != -1) {
            candidates.emplace(cost - node.key + heap_pool[node.right].key, node.right);
        }
        int next_heap = path_heap[node.to];
        if (next_heap != -1) {
            candidates.emplace(cost + heap_pool[next_heap].key, next_heap);
        }
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_K_SHORTEST_WALK_HPP
