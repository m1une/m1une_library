#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

#include "../../graph/all.hpp"
#include "../../utilities/fast_io.hpp"

using CowGame = m1une::graph::CowGame<long long>;

void test_basic_constraints() {
    CowGame game(4);
    int first = game.add_upper_bound(1, 0, 5);
    game.add_lower_bound(1, 0, 2);
    game.add_bounds(2, 1, -1, 4);
    game.add_equality(3, 2, 3);

    assert(game.size() == 4);
    assert(game.constraint_count() == 6);
    assert(game.get_constraint(first).a == 1);
    assert(game.get_constraint(first).b == 0);
    assert(game.get_constraint(first).upper_bound == 5);

    auto solution = game.solve();
    assert(solution.is_feasible());
    assert(solution.value.size() == 4);
    for (const auto& constraint : game.constraints()) {
        assert(solution.value[constraint.a] - solution.value[constraint.b] <=
               constraint.upper_bound);
    }

    auto bounds = game.difference_bounds(3, 0);
    assert(bounds.is_feasible());
    assert(bounds.bounded_below());
    assert(bounds.bounded_above());
    assert(*bounds.lower_bound == 4);
    assert(*bounds.upper_bound == 12);

    auto all = game.tightest_upper_bounds(0);
    assert(all.is_feasible());
    assert(all.bounded(0));
    assert(all.bounded(3));
    assert(all.upper_bound[0] == 0);
    assert(all.upper_bound[3] == 12);
}

void test_infeasible() {
    CowGame game(2);
    game.add_lower_bound(1, 0, 5);
    assert(game.is_feasible());
    assert(game.solve().is_feasible());

    game.add_upper_bound(1, 0, 3);

    assert(!game.is_feasible());
    assert(!game.solve().is_feasible());
    assert(!game.tightest_upper_bounds(0).is_feasible());
    assert(!game.difference_bounds(1, 0).is_feasible());
}

void test_unbounded() {
    CowGame game(4);
    game.add_upper_bound(1, 0, 7);
    game.add_upper_bound(3, 2, 2);

    auto one_way = game.difference_bounds(1, 0);
    assert(one_way.is_feasible());
    assert(!one_way.bounded_below());
    assert(one_way.bounded_above());
    assert(*one_way.upper_bound == 7);

    auto disconnected = game.difference_bounds(3, 0);
    assert(disconnected.is_feasible());
    assert(!disconnected.bounded_below());
    assert(!disconnected.bounded_above());

    auto all = game.tightest_upper_bounds(0);
    assert(all.bounded(0));
    assert(all.bounded(1));
    assert(!all.bounded(2));
    assert(!all.bounded(3));
}

void test_dijkstra_and_reweighting() {
    CowGame game(5);
    game.add_constraint(1, 0, 7);
    game.add_constraint(2, 0, 2);
    game.add_constraint(1, 2, 3);
    game.add_constraint(3, 1, 4);

    auto nonnegative_solution = game.solve();
    assert(nonnegative_solution.is_feasible());
    assert(std::all_of(nonnegative_solution.value.begin(),
                       nonnegative_solution.value.end(),
                       [](long long value) { return value == 0; }));

    auto nonnegative = game.tightest_upper_bounds(0);
    assert(nonnegative.upper_bound[1] == 5);
    assert(nonnegative.upper_bound[3] == 9);

    game.add_constraint(4, 3, -2);
    auto reweighted_solution = game.solve();
    assert(reweighted_solution.is_feasible());
    auto reweighted = game.difference_bounds(4, 0);
    assert(reweighted.bounded_above());
    assert(!reweighted.bounded_below());
    assert(*reweighted.upper_bound == 7);
}

void test_alias_and_empty() {
    m1une::graph::DifferenceConstraints<long long> constraints(0);
    auto solution = constraints.solve();
    assert(solution.is_feasible());
    assert(solution.value.empty());
}

void test_against_warshall_floyd() {
    constexpr long long inf = std::numeric_limits<long long>::max() / 4;
    for (int n = 1; n <= 7; n++) {
        for (int test = 0; test < 80; test++) {
            CowGame game(n);
            std::vector<std::vector<long long>> dist(
                n, std::vector<long long>(n, inf));
            for (int i = 0; i < n; i++) dist[i][i] = 0;

            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if ((test * 5 + a * 7 + b * 11) % 6 != 0) continue;
                    long long upper_bound = (test * 3 + a * 5 + b * 2) % 13 - 6;
                    game.add_constraint(a, b, upper_bound);
                    dist[b][a] = std::min(dist[b][a], upper_bound);
                }
            }

            dist = m1une::graph::warshall_floyd(std::move(dist), inf);
            bool feasible = !m1une::graph::has_negative_cycle(dist);
            assert(game.is_feasible() == feasible);

            auto solution = game.solve();
            assert(solution.is_feasible() == feasible);
            if (!feasible) continue;
            for (const auto& constraint : game.constraints()) {
                assert(solution.value[constraint.a] - solution.value[constraint.b] <=
                       constraint.upper_bound);
            }

            for (int source = 0; source < n; source++) {
                auto upper = game.tightest_upper_bounds(source);
                assert(upper.is_feasible());
                for (int target = 0; target < n; target++) {
                    assert(upper.bounded(target) == (dist[source][target] != inf));
                    if (upper.bounded(target)) {
                        assert(upper.upper_bound[target] == dist[source][target]);
                    }

                    auto bounds = game.difference_bounds(target, source);
                    assert(bounds.is_feasible());
                    assert(bounds.bounded_above() == (dist[source][target] != inf));
                    assert(bounds.bounded_below() == (dist[target][source] != inf));
                    if (bounds.bounded_above()) {
                        assert(*bounds.upper_bound == dist[source][target]);
                    }
                    if (bounds.bounded_below()) {
                        assert(*bounds.lower_bound == -dist[target][source]);
                    }
                }
            }
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_basic_constraints();
    test_infeasible();
    test_unbounded();
    test_dijkstra_and_reweighting();
    test_alias_and_empty();
    test_against_warshall_floyd();

    int vertex_count, edge_count, source, target;
    fast_input >> vertex_count >> edge_count >> source >> target;
    CowGame game(vertex_count);
    std::vector<int> from(edge_count), to(edge_count);
    std::vector<long long> cost(edge_count);
    std::vector<std::vector<int>> outgoing(vertex_count);
    for (int id = 0; id < edge_count; id++) {
        fast_input >> from[id] >> to[id] >> cost[id];
        game.add_constraint(to[id], from[id], cost[id]);
        outgoing[from[id]].push_back(id);
    }

    auto bounds = game.tightest_upper_bounds(source);
    if (!bounds.bounded(target)) {
        fast_output << -1 << '\n';
        return 0;
    }

    std::vector<int> parent_edge(vertex_count, -1);
    std::queue<int> queue;
    parent_edge[source] = edge_count;
    queue.push(source);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int id : outgoing[v]) {
            if (parent_edge[to[id]] != -1) continue;
            if (!bounds.bounded(to[id])) continue;
            if (bounds.upper_bound[v] + cost[id] != bounds.upper_bound[to[id]]) {
                continue;
            }
            parent_edge[to[id]] = id;
            queue.push(to[id]);
        }
    }

    assert(parent_edge[target] != -1);
    std::vector<std::pair<int, int>> path;
    for (int v = target; v != source; v = from[parent_edge[v]]) {
        int id = parent_edge[v];
        path.emplace_back(from[id], to[id]);
    }
    std::reverse(path.begin(), path.end());

    fast_output << bounds.upper_bound[target] << ' ' << path.size() << '\n';
    for (auto [a, b] : path) fast_output << a << ' ' << b << '\n';
}
