#ifndef M1UNE_GRAPH_MATRIX_TREE_THEOREM_HPP
#define M1UNE_GRAPH_MATRIX_TREE_THEOREM_HPP 1

#include <cassert>
#include <utility>
#include <vector>

#include "../math/matrix/linear_algebra.hpp"
#include "graph.hpp"

namespace m1une {
namespace graph {

namespace matrix_tree_detail {

inline int minor_index(int vertex, int removed) {
    assert(vertex != removed);
    return vertex < removed ? vertex : vertex - 1;
}

template <class Weight>
void assert_edge_incidence(const Graph<Weight>& graph, int expected) {
#ifndef NDEBUG
    std::vector<int> incidence(graph.edge_count(), 0);
    for (int vertex = 0; vertex < graph.size(); vertex++) {
        for (const Edge<Weight>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < graph.edge_count());
            incidence[edge.id]++;
        }
    }
    for (int count : incidence) {
        if (count != 0) assert(count == expected);
    }
#else
    (void)graph;
    (void)expected;
#endif
}

template <class Field, class Weight>
Field count_arborescences(
    const Graph<Weight>& graph,
    int root,
    bool outward
) {
    const int n = graph.size();
    assert(0 <= root && root < n);
    assert_edge_incidence(graph, 1);

    matrix::Matrix<Field> minor(n - 1, n - 1);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<Weight>& edge : graph[vertex]) {
            if (!edge.alive || edge.from == edge.to) continue;
            const int row = outward ? edge.to : edge.from;
            const int col = outward ? edge.from : edge.to;
            if (row == root) continue;

            const Field weight(edge.cost);
            const int reduced_row = minor_index(row, root);
            minor[reduced_row][reduced_row] += weight;
            if (col != root) {
                minor[reduced_row][minor_index(col, root)] -= weight;
            }
        }
    }
    return matrix::determinant(std::move(minor));
}

}  // namespace matrix_tree_detail

// Returns the total weight of all undirected spanning trees. The weight of a
// tree is the product of its edge costs.
template <class Field, class Weight>
Field count_spanning_trees(const Graph<Weight>& graph) {
    const int n = graph.size();
    assert(n > 0);
    matrix_tree_detail::assert_edge_incidence(graph, 2);

    const int removed = n - 1;
    matrix::Matrix<Field> minor(n - 1, n - 1);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<Weight>& edge : graph[vertex]) {
            if (!edge.alive || edge.from >= edge.to) continue;
            const int from = edge.from;
            const int to = edge.to;
            const Field weight(edge.cost);

            if (from != removed) {
                const int reduced_from = matrix_tree_detail::minor_index(from, removed);
                minor[reduced_from][reduced_from] += weight;
            }
            if (to != removed) {
                const int reduced_to = matrix_tree_detail::minor_index(to, removed);
                minor[reduced_to][reduced_to] += weight;
            }
            if (from != removed && to != removed) {
                const int reduced_from = matrix_tree_detail::minor_index(from, removed);
                const int reduced_to = matrix_tree_detail::minor_index(to, removed);
                minor[reduced_from][reduced_to] -= weight;
                minor[reduced_to][reduced_from] -= weight;
            }
        }
    }
    return matrix::determinant(std::move(minor));
}

// Counts directed spanning trees whose edges point away from root, so every
// vertex is reachable from root.
template <class Field, class Weight>
Field count_out_arborescences(const Graph<Weight>& graph, int root) {
    return matrix_tree_detail::count_arborescences<Field>(graph, root, true);
}

// Counts directed spanning trees whose edges point toward root, so root is
// reachable from every vertex.
template <class Field, class Weight>
Field count_in_arborescences(const Graph<Weight>& graph, int root) {
    return matrix_tree_detail::count_arborescences<Field>(graph, root, false);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_MATRIX_TREE_THEOREM_HPP
