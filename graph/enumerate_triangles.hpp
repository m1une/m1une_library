#ifndef M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP
#define M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP 1

#include <cassert>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T, class Callback>
void enumerate_triangles(const Graph<T>& graph, Callback&& callback) {
    const int n = graph.size();
    const std::vector<Edge<T>> edges = graph.edges();

    std::vector<int> degree(n, 0);
    for (const Edge<T>& edge : edges) {
        assert(edge.from != edge.to);
        degree[edge.from]++;
        degree[edge.to]++;
    }

    std::vector<std::vector<int>> oriented(n);
    for (const Edge<T>& edge : edges) {
        int from = edge.from;
        int to = edge.to;
        if (degree[from] > degree[to] ||
            (degree[from] == degree[to] && from > to)) {
            std::swap(from, to);
        }
        oriented[from].push_back(to);
    }

    std::vector<int> marked(n, -1);
    for (int vertex = 0; vertex < n; vertex++) {
        for (int to : oriented[vertex]) marked[to] = vertex;
        for (int middle : oriented[vertex]) {
            for (int to : oriented[middle]) {
                if (marked[to] != vertex) continue;
                int first = vertex;
                int second = middle;
                int third = to;
                if (first > second) std::swap(first, second);
                if (second > third) std::swap(second, third);
                if (first > second) std::swap(first, second);
                callback(first, second, third);
            }
        }
    }
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_ENUMERATE_TRIANGLES_HPP
