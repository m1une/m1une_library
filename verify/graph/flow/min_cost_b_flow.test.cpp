#define PROBLEM "https://judge.yosupo.jp/problem/min_cost_b_flow"

#include "../../../graph/flow/bounded_min_cost_flow.hpp"
#include "../../../utilities/int128.hpp"

#include <cassert>
#include <iostream>

int main() {
    using Flow = long long;
    using Cost = __int128_t;
    using Solver = m1une::flow::BoundedMinCostFlow<Flow, Cost>;

    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Solver solver(vertex_count);
    for (int vertex = 0; vertex < vertex_count; vertex++) {
        Flow balance;
        std::cin >> balance;
        solver.set_balance(vertex, balance);
    }
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        Flow lower, upper;
        long long cost;
        std::cin >> from >> to >> lower >> upper >> cost;
        solver.add_edge(from, to, lower, upper, Cost(cost));
    }

    auto result = solver.min_cost_flow();
    if (!result.has_value()) {
        std::cout << "infeasible\n";
        return 0;
    }

    assert(int(result->potential.size()) == vertex_count);
    for (const auto& edge : result->edges) {
        Cost reduced_cost =
            edge.cost + result->potential[edge.from] - result->potential[edge.to];
        if (edge.flow < edge.upper) assert(Cost(0) <= reduced_cost);
        if (edge.lower < edge.flow) assert(reduced_cost <= Cost(0));
    }

    std::cout << result->cost << '\n';
    for (Cost potential : result->potential) std::cout << potential << '\n';
    for (const auto& edge : result->edges) std::cout << edge.flow << '\n';
}
