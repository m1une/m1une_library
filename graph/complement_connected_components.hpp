#ifndef M1UNE_GRAPH_COMPLEMENT_CONNECTED_COMPONENTS_HPP
#define M1UNE_GRAPH_COMPLEMENT_CONNECTED_COMPONENTS_HPP 1

#include <queue>
#include <vector>

#include "connected_components.hpp"

namespace m1une {
namespace graph {

// Computes connected components after complementing the underlying simple
// undirected graph, without constructing the complement graph.
template <class T>
ConnectedComponents complement_connected_components(const Graph<T>& graph) {
    const int size = graph.size();
    std::vector<std::vector<int>> adjacency(size);
    for (const Edge<T>& edge : graph.edges()) {
        if (edge.from == edge.to) continue;
        adjacency[edge.from].push_back(edge.to);
        adjacency[edge.to].push_back(edge.from);
    }

    const int sentinel = size;
    std::vector<int> next(size + 1);
    std::vector<int> previous(size + 1);
    if (size == 0) {
        next[sentinel] = previous[sentinel] = sentinel;
    } else {
        next[sentinel] = 0;
        previous[sentinel] = size - 1;
        for (int vertex = 0; vertex < size; vertex++) {
            next[vertex] = (vertex + 1 == size ? sentinel : vertex + 1);
            previous[vertex] = (vertex == 0 ? sentinel : vertex - 1);
        }
    }

    auto erase = [&](int vertex) {
        next[previous[vertex]] = next[vertex];
        previous[next[vertex]] = previous[vertex];
    };

    ConnectedComponents result;
    result.comp.assign(size, -1);
    std::vector<int> neighbor_stamp(size, -1);
    std::queue<int> queue;

    while (next[sentinel] != sentinel) {
        const int root = next[sentinel];
        erase(root);
        const int component = int(result.groups.size());
        result.groups.emplace_back();
        result.groups.back().push_back(root);
        result.comp[root] = component;
        queue.push(root);

        while (!queue.empty()) {
            const int vertex = queue.front();
            queue.pop();
            for (int to : adjacency[vertex]) neighbor_stamp[to] = vertex;

            int candidate = next[sentinel];
            while (candidate != sentinel) {
                const int following = next[candidate];
                if (neighbor_stamp[candidate] != vertex) {
                    erase(candidate);
                    result.comp[candidate] = component;
                    result.groups.back().push_back(candidate);
                    queue.push(candidate);
                }
                candidate = following;
            }
        }
    }
    result.count = int(result.groups.size());
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_COMPLEMENT_CONNECTED_COMPONENTS_HPP
