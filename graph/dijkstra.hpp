#ifndef M1UNE_GRAPH_DIJKSTRA_HPP
#define M1UNE_GRAPH_DIJKSTRA_HPP 1

#include <algorithm>
#include <cassert>
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
class DijkstraHeap {
   private:
    const std::vector<T>& dist_;
    std::vector<int> heap_;
    std::vector<int> position_;

    bool less(int first, int second) const {
        return dist_[heap_[first]] < dist_[heap_[second]];
    }

    void swap_nodes(int first, int second) {
        std::swap(heap_[first], heap_[second]);
        position_[heap_[first]] = first;
        position_[heap_[second]] = second;
    }

    void sift_up(int index) {
        while (index != 0) {
            const int parent = (index - 1) / 2;
            if (!less(index, parent)) break;
            swap_nodes(index, parent);
            index = parent;
        }
    }

    void sift_down(int index) {
        while (2 * index + 1 < int(heap_.size())) {
            int child = 2 * index + 1;
            if (child + 1 < int(heap_.size()) && less(child + 1, child)) {
                ++child;
            }
            if (!less(child, index)) break;
            swap_nodes(index, child);
            index = child;
        }
    }

   public:
    DijkstraHeap(const std::vector<T>& dist, int size)
        : dist_(dist), position_(size, -1) {
        heap_.reserve(size);
    }

    bool empty() const {
        return heap_.empty();
    }

    void push_or_decrease(int vertex) {
        int& position = position_[vertex];
        if (position == -1) {
            position = int(heap_.size());
            heap_.push_back(vertex);
        }
        sift_up(position);
    }

    int pop_min() {
        const int result = heap_.front();
        position_[result] = -1;
        if (heap_.size() == 1) {
            heap_.pop_back();
            return result;
        }
        heap_.front() = heap_.back();
        position_[heap_.front()] = 0;
        heap_.pop_back();
        sift_down(0);
        return result;
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

    internal::DijkstraHeap<T> que(result.dist, n);
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.reached[s]) continue;
        result.reached[s] = true;
        result.dist[s] = T();
        que.push_or_decrease(s);
    }

    while (!que.empty()) {
        const int current = que.pop_min();
        for (const auto& e : g[current]) {
            if (!e.alive) continue;
            T nd = result.dist[current] + e.cost;
            if (result.reached[e.to] && !(nd < result.dist[e.to])) continue;
            result.reached[e.to] = true;
            result.dist[e.to] = std::move(nd);
            result.parent[e.to] = current;
            result.parent_edge[e.to] = e.id;
            que.push_or_decrease(e.to);
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
