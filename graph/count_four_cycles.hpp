#ifndef M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP
#define M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP 1

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

namespace four_cycle_detail {

// Counts C4s containing one particular copy of each edge in a simple graph
// whose edge weights represent parallel-edge multiplicities.
inline std::vector<long long> count_simple_per_edge(
    int vertex_count,
    std::vector<int> first,
    std::vector<int> second,
    const std::vector<long long>& multiplicity
) {
    const int edge_count = int(first.size());
    assert(second.size() == first.size());
    assert(multiplicity.size() == first.size());

    std::vector<int> degree(vertex_count, 0);
    for (int edge = 0; edge < edge_count; edge++) {
        degree[first[edge]]++;
        degree[second[edge]]++;
    }

    int maximum_degree = 0;
    for (int value : degree) maximum_degree = std::max(maximum_degree, value);
    std::vector<int> degree_start(maximum_degree + 2, 0);
    for (int value : degree) degree_start[value + 1]++;
    for (int value = 0; value <= maximum_degree; value++) {
        degree_start[value + 1] += degree_start[value];
    }
    std::vector<int> cursor = degree_start;
    std::vector<int> order(vertex_count);
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        order[cursor[degree[vertex]]++] = vertex;
    }
    std::vector<int> rank(vertex_count);
    for (int i = 0; i < vertex_count; i++) rank[order[i]] = i;
    for (int edge = 0; edge < edge_count; edge++) {
        first[edge] = rank[first[edge]];
        second[edge] = rank[second[edge]];
        if (first[edge] < second[edge]) {
            std::swap(first[edge], second[edge]);
        }
    }

    std::vector<int> start(vertex_count + 1, 0);
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        start[vertex + 1] = start[vertex] + degree[order[vertex]];
    }
    std::vector<int> end = start;
    std::vector<int> edge_at(2 * edge_count);
    std::vector<int> to(2 * edge_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int position = end[first[edge]]++;
        edge_at[position] = edge;
        to[position] = second[edge];
    }

    std::vector<int> downward_end = end;
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        for (int i = start[vertex]; i < downward_end[vertex]; i++) {
            int edge = edge_at[i];
            int neighbor = to[i];
            int position = end[neighbor]++;
            edge_at[position] = edge;
            to[position] = vertex;
        }
    }

    std::vector<long long> path_count(vertex_count, 0);
    std::vector<long long> result(edge_count, 0);
    for (int vertex = vertex_count - 1; vertex >= 0; vertex--) {
        for (int i = start[vertex]; i < end[vertex]; i++) {
            int first_edge = edge_at[i];
            int middle = to[i];
            end[middle]--;
            for (int j = start[middle]; j < end[middle]; j++) {
                int second_edge = edge_at[j];
                int opposite = to[j];
                path_count[opposite] +=
                    multiplicity[first_edge] * multiplicity[second_edge];
            }
        }

        for (int i = start[vertex]; i < end[vertex]; i++) {
            int first_edge = edge_at[i];
            int middle = to[i];
            for (int j = start[middle]; j < end[middle]; j++) {
                int second_edge = edge_at[j];
                int opposite = to[j];
                long long other_paths =
                    path_count[opposite] -
                    multiplicity[first_edge] * multiplicity[second_edge];
                result[first_edge] +=
                    other_paths * multiplicity[second_edge];
                result[second_edge] +=
                    other_paths * multiplicity[first_edge];
            }
        }

        for (int i = start[vertex]; i < end[vertex]; i++) {
            int middle = to[i];
            for (int j = start[middle]; j < end[middle]; j++) {
                path_count[to[j]] = 0;
            }
        }
    }
    return result;
}

}  // namespace four_cycle_detail

// Returns, for every graph edge id, the number of C4 subgraphs containing it.
// Parallel active edges are distinct choices; inactive edges receive zero.
template <class T>
std::vector<long long> count_four_cycles_per_edge(const Graph<T>& graph) {
    struct ActiveEdge {
        int first;
        int second;
        int id;
    };

    std::vector<ActiveEdge> active_edges;
    active_edges.reserve(graph.edge_count());
    for (const Edge<T>& edge : graph.edges()) {
        assert(edge.from != edge.to);
        assert(0 <= edge.id && edge.id < graph.edge_count());
        if (edge.from == edge.to) continue;
        active_edges.push_back(ActiveEdge{
            std::min(edge.from, edge.to),
            std::max(edge.from, edge.to),
            edge.id
        });
    }
    std::sort(
        active_edges.begin(),
        active_edges.end(),
        [](const ActiveEdge& left, const ActiveEdge& right) {
            return std::tie(left.first, left.second) <
                   std::tie(right.first, right.second);
        }
    );

    std::vector<int> first;
    std::vector<int> second;
    std::vector<long long> multiplicity;
    std::vector<int> group_of_edge(graph.edge_count(), -1);
    first.reserve(active_edges.size());
    second.reserve(active_edges.size());
    multiplicity.reserve(active_edges.size());
    for (const ActiveEdge& edge : active_edges) {
        if (first.empty() || first.back() != edge.first ||
            second.back() != edge.second) {
            first.push_back(edge.first);
            second.push_back(edge.second);
            multiplicity.push_back(0);
        }
        multiplicity.back()++;
        group_of_edge[edge.id] = int(first.size()) - 1;
    }

    std::vector<long long> simple_result =
        four_cycle_detail::count_simple_per_edge(
            graph.size(),
            std::move(first),
            std::move(second),
            multiplicity
        );
    std::vector<long long> result(graph.edge_count(), 0);
    for (const ActiveEdge& edge : active_edges) {
        result[edge.id] = simple_result[group_of_edge[edge.id]];
    }
    return result;
}

template <class T>
long long count_four_cycles(const Graph<T>& graph) {
    std::vector<long long> per_edge = count_four_cycles_per_edge(graph);
    long long incidence_count = 0;
    for (long long count : per_edge) incidence_count += count;
    assert(incidence_count % 4 == 0);
    return incidence_count / 4;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_COUNT_FOUR_CYCLES_HPP
