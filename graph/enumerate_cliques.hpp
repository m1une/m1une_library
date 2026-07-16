#ifndef M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP
#define M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

// Invokes callback once for every nonempty clique. The callback receives a
// const reference to a temporary vector that is reused after it returns.
template <class T, class Callback>
void enumerate_cliques(const Graph<T>& graph, Callback&& callback) {
    const int n = graph.size();
    std::vector<std::vector<int>> adjacency(n);
    for (const Edge<T>& edge : graph.edges()) {
        assert(edge.from != edge.to);
        if (edge.from == edge.to) continue;
        adjacency[edge.from].push_back(edge.to);
        adjacency[edge.to].push_back(edge.from);
    }

    for (std::vector<int>& neighbors : adjacency) {
        std::sort(neighbors.begin(), neighbors.end());
#ifndef NDEBUG
        for (int i = 1; i < int(neighbors.size()); i++) {
            assert(neighbors[i - 1] != neighbors[i]);
        }
#endif
        neighbors.erase(
            std::unique(neighbors.begin(), neighbors.end()),
            neighbors.end()
        );
    }

    int maximum_degree = 0;
    std::vector<int> degree(n);
    for (int vertex = 0; vertex < n; vertex++) {
        degree[vertex] = int(adjacency[vertex].size());
        maximum_degree = std::max(maximum_degree, degree[vertex]);
    }

    // Compute a degeneracy ordering in linear time. A clique is assigned to
    // its first vertex in this ordering, and all its other vertices are among
    // that vertex's forward neighbors.
    std::vector<std::vector<int>> bucket(maximum_degree + 1);
    for (int vertex = 0; vertex < n; vertex++) {
        bucket[degree[vertex]].push_back(vertex);
    }
    std::vector<char> active(n, true);
    std::vector<std::vector<int>> forward(n);
    int minimum_degree = 0;
    int degeneracy = 0;
    for (int removed = 0; removed < n; removed++) {
        while (true) {
            while (bucket[minimum_degree].empty()) minimum_degree++;
            int vertex = bucket[minimum_degree].back();
            if (active[vertex] && degree[vertex] == minimum_degree) break;
            bucket[minimum_degree].pop_back();
        }

        int vertex = bucket[minimum_degree].back();
        bucket[minimum_degree].pop_back();
        active[vertex] = false;
        degeneracy = std::max(degeneracy, minimum_degree);
        forward[vertex].reserve(minimum_degree);
        for (int to : adjacency[vertex]) {
            if (!active[to]) continue;
            forward[vertex].push_back(to);
            degree[to]--;
            bucket[degree[to]].push_back(to);
            minimum_degree = std::min(minimum_degree, degree[to]);
        }
    }

    std::vector<int> clique;
    clique.reserve(degeneracy + 1);
    std::vector<std::vector<int>> candidates(degeneracy + 1);
    for (int vertex = 0; vertex < n; vertex++) {
        const std::vector<int>& neighbors = forward[vertex];
        const int neighbor_count = int(neighbors.size());

        clique.clear();
        clique.push_back(vertex);
        callback(std::as_const(clique));
        if (neighbor_count == 0) continue;

        std::vector<char> connected(
            std::size_t(neighbor_count) * neighbor_count,
            false
        );
        for (int first = 0; first < neighbor_count; first++) {
            for (int second = first + 1; second < neighbor_count; second++) {
                bool adjacent = std::binary_search(
                    adjacency[neighbors[first]].begin(),
                    adjacency[neighbors[first]].end(),
                    neighbors[second]
                );
                connected[std::size_t(first) * neighbor_count + second] =
                    adjacent;
                connected[std::size_t(second) * neighbor_count + first] =
                    adjacent;
            }
        }

        candidates[0].resize(neighbor_count);
        for (int i = 0; i < neighbor_count; i++) candidates[0][i] = i;
        auto enumerate = [&](auto&& self, int depth) -> void {
            const std::vector<int>& current = candidates[depth];
            for (int position = 0; position < int(current.size()); position++) {
                int chosen = current[position];
                clique.push_back(neighbors[chosen]);
                callback(std::as_const(clique));

                std::vector<int>& next = candidates[depth + 1];
                next.clear();
                for (int next_position = position + 1;
                     next_position < int(current.size());
                     next_position++) {
                    int candidate = current[next_position];
                    if (connected[
                            std::size_t(chosen) * neighbor_count + candidate
                        ]) {
                        next.push_back(candidate);
                    }
                }
                if (!next.empty()) self(self, depth + 1);
                clique.pop_back();
            }
        };
        enumerate(enumerate, 0);
    }
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_ENUMERATE_CLIQUES_HPP
