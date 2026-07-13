#ifndef M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP
#define M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP 1

#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct ChordalGraphResult {
    bool is_chordal;
    std::vector<int> perfect_elimination_order;
    std::vector<int> induced_cycle;
};

namespace internal {

class MaximumCardinalitySearch {
    std::vector<int> _head;
    std::vector<int> _next;
    std::vector<int> _previous;
    std::vector<int> _weight;

    void erase(int vertex) {
        const int weight = _weight[vertex];
        if (_previous[vertex] == -1) {
            _head[weight] = _next[vertex];
        } else {
            _next[_previous[vertex]] = _next[vertex];
        }
        if (_next[vertex] != -1) _previous[_next[vertex]] = _previous[vertex];
    }

    void insert(int vertex) {
        const int weight = _weight[vertex];
        _previous[vertex] = -1;
        _next[vertex] = _head[weight];
        if (_head[weight] != -1) _previous[_head[weight]] = vertex;
        _head[weight] = vertex;
    }

   public:
    explicit MaximumCardinalitySearch(int size)
        : _head(size + 1, -1),
          _next(size, -1),
          _previous(size, -1),
          _weight(size, 0) {
        for (int vertex = 0; vertex < size; vertex++) insert(vertex);
    }

    std::vector<int> run(const std::vector<std::vector<int>>& adjacency) {
        const int size = int(adjacency.size());
        std::vector<int> order;
        order.reserve(size);
        std::vector<char> selected(size, false);
        std::vector<int> seen_neighbor(size, -1);
        int maximum_weight = 0;

        while (int(order.size()) < size) {
            while (_head[maximum_weight] == -1) maximum_weight--;
            const int vertex = _head[maximum_weight];
            erase(vertex);
            selected[vertex] = true;
            order.push_back(vertex);

            for (int to : adjacency[vertex]) {
                if (to == vertex || selected[to] || seen_neighbor[to] == vertex) continue;
                seen_neighbor[to] = vertex;
                erase(to);
                _weight[to]++;
                insert(to);
                maximum_weight = std::max(maximum_weight, _weight[to]);
            }
        }
        return order;
    }
};

inline std::vector<int> chordless_cycle(
    const std::vector<std::vector<int>>& adjacency, int vertex, int first,
    int second
) {
    const int size = int(adjacency.size());
    std::vector<char> forbidden(size, false);
    for (int to : adjacency[vertex]) forbidden[to] = true;
    forbidden[vertex] = true;
    forbidden[first] = false;
    forbidden[second] = false;

    std::vector<int> parent(size, -1);
    std::queue<int> queue;
    parent[first] = first;
    queue.push(first);
    while (!queue.empty() && parent[second] == -1) {
        const int current = queue.front();
        queue.pop();
        for (int to : adjacency[current]) {
            if (forbidden[to] || parent[to] != -1) continue;
            parent[to] = current;
            queue.push(to);
        }
    }
    assert(parent[second] != -1);

    std::vector<int> path;
    for (int current = second; current != first; current = parent[current]) {
        path.push_back(current);
    }
    path.push_back(first);
    std::reverse(path.begin(), path.end());

    std::vector<int> cycle;
    cycle.reserve(path.size() + 1);
    cycle.push_back(vertex);
    cycle.insert(cycle.end(), path.begin(), path.end());
    return cycle;
}

}  // namespace internal

// Recognizes a chordal graph. On success, returns a perfect elimination
// ordering; on failure, returns an induced cycle of length at least four.
template <class T>
ChordalGraphResult chordal_graph_recognition(const Graph<T>& graph) {
    const int size = graph.size();
    std::vector<std::vector<int>> adjacency(size);
    for (const Edge<T>& edge : graph.edges()) {
        if (edge.from == edge.to) continue;
        adjacency[edge.from].push_back(edge.to);
        adjacency[edge.to].push_back(edge.from);
    }

    std::vector<int> order = internal::MaximumCardinalitySearch(size).run(adjacency);
    std::vector<int> position(size);
    for (int index = 0; index < size; index++) position[order[index]] = index;

    std::vector<int> parent(size, -1);
    std::vector<std::vector<int>> children(size);
    for (int vertex = 0; vertex < size; vertex++) {
        for (int to : adjacency[vertex]) {
            if (position[to] < position[vertex] &&
                (parent[vertex] == -1 || position[parent[vertex]] < position[to])) {
                parent[vertex] = to;
            }
        }
        if (parent[vertex] != -1) children[parent[vertex]].push_back(vertex);
    }

    std::vector<int> adjacent_stamp(size, -1);
    for (int center = 0; center < size; center++) {
        for (int to : adjacency[center]) adjacent_stamp[to] = center;
        for (int vertex : children[center]) {
            for (int to : adjacency[vertex]) {
                if (position[to] >= position[center] || adjacent_stamp[to] == center) continue;
                return ChordalGraphResult{
                    false,
                    {},
                    internal::chordless_cycle(adjacency, vertex, to, center),
                };
            }
        }
    }

    std::reverse(order.begin(), order.end());
    return ChordalGraphResult{true, std::move(order), {}};
}

template <class T>
bool is_chordal(const Graph<T>& graph) {
    return chordal_graph_recognition(graph).is_chordal;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_CHORDAL_GRAPH_RECOGNITION_HPP
