#ifndef M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
#define M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap, class Cost, class TotalCost = Cost>
struct BoundedMinCostFlow {
    static_assert(std::numeric_limits<Cap>::is_integer);
    static_assert(std::numeric_limits<Cap>::is_signed);

    struct Edge {
        int from;
        int to;
        Cap lower;
        Cap upper;
        Cost cost;
    };

    struct ResultEdge {
        int from;
        int to;
        Cap lower;
        Cap upper;
        Cap flow;
        Cost cost;
    };

    struct Result {
        std::vector<ResultEdge> edges;
        std::vector<Cap> balance;
        std::vector<Cost> potential;
        TotalCost cost;

        ResultEdge get_edge(int i) const {
            assert(0 <= i && i < int(edges.size()));
            return edges[i];
        }

        Cap flow(int i) const {
            assert(0 <= i && i < int(edges.size()));
            return edges[i].flow;
        }
    };

   private:
    struct NetworkEdge {
        int to;
        Cap cap;
        Cost cost;
    };

    struct NetworkSimplexSolver {
        struct Parent {
            int vertex;
            int edge;
            Cap up;
            Cap down;
        };

        int n;
        std::vector<NetworkEdge> edges;
        std::vector<Cap> excess;
        std::vector<Cost> potential;

        NetworkSimplexSolver(int vertex_count, const std::vector<Cap>& balance)
            : n(vertex_count), excess(balance) {}

        void reserve_edges(int edge_count) {
            edges.reserve(2 * (edge_count + n));
        }

        int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {
            int id = int(edges.size()) / 2;
            edges.push_back(NetworkEdge{to, upper - lower, cost});
            edges.push_back(NetworkEdge{from, Cap(0), -cost});
            excess[from] -= lower;
            excess[to] += lower;
            return id;
        }

        bool solve() {
            const int original_edge_count = int(edges.size());
            potential.assign(n + 1, Cost(0));

            Cost artificial_cost = Cost(1);
            for (int edge = 0; edge < original_edge_count; edge += 2) {
                artificial_cost += edges[edge].cost < Cost(0)
                    ? -edges[edge].cost : edges[edge].cost;
            }

            std::vector<Parent> parent(n);
            edges.reserve(original_edge_count + 2 * n);
            for (int vertex = 0; vertex < n; vertex++) {
                if (excess[vertex] >= Cap(0)) {
                    edges.push_back(NetworkEdge{n, Cap(0), artificial_cost});
                    edges.push_back(NetworkEdge{vertex, excess[vertex], -artificial_cost});
                    potential[vertex] = -artificial_cost;
                } else {
                    edges.push_back(NetworkEdge{n, -excess[vertex], -artificial_cost});
                    edges.push_back(NetworkEdge{vertex, Cap(0), artificial_cost});
                    potential[vertex] = artificial_cost;
                }
                int edge = int(edges.size()) - 2;
                parent[vertex] = Parent{
                    n, edge, edges[edge].cap, edges[edge ^ 1].cap
                };
            }

            std::vector<int> depth(n + 1, 1);
            depth[n] = 0;
            std::vector<int> next(2 * (n + 1));
            std::vector<int> previous(2 * (n + 1));
            auto connect = [&](int first, int second) {
                next[first] = second;
                previous[second] = first;
            };
            for (int vertex = 0; vertex <= n; vertex++) {
                connect(2 * vertex, 2 * vertex + 1);
            }
            for (int vertex = 0; vertex < n; vertex++) {
                connect(2 * vertex + 1, next[2 * n]);
                connect(2 * n, 2 * vertex);
            }

            auto push_flow = [&](int entering_edge) {
                const int first = edges[entering_edge ^ 1].to;
                const int second = edges[entering_edge].to;
                const Cost cycle_cost =
                    edges[entering_edge].cost
                    + potential[first] - potential[second];

                Cap amount = edges[entering_edge].cap;
                bool leave_first_side = true;
                int leaving_vertex = second;

                int first_ancestor = first;
                int second_ancestor = second;
                auto move_first_up = [&] {
                    if (parent[first_ancestor].down < amount) {
                        amount = parent[first_ancestor].down;
                        leaving_vertex = first_ancestor;
                        leave_first_side = true;
                    }
                    first_ancestor = parent[first_ancestor].vertex;
                };
                auto move_second_up = [&] {
                    if (parent[second_ancestor].up <= amount) {
                        amount = parent[second_ancestor].up;
                        leaving_vertex = second_ancestor;
                        leave_first_side = false;
                    }
                    second_ancestor = parent[second_ancestor].vertex;
                };
                if (depth[first_ancestor] >= depth[second_ancestor]) {
                    int difference = depth[first_ancestor] - depth[second_ancestor];
                    for (int i = 0; i < difference; i++) move_first_up();
                } else {
                    int difference = depth[second_ancestor] - depth[first_ancestor];
                    for (int i = 0; i < difference; i++) move_second_up();
                }
                while (first_ancestor != second_ancestor) {
                    move_first_up();
                    move_second_up();
                }
                const int ancestor = first_ancestor;

                if (amount != Cap(0)) {
                    int vertex = first;
                    while (vertex != ancestor) {
                        parent[vertex].up += amount;
                        parent[vertex].down -= amount;
                        vertex = parent[vertex].vertex;
                    }
                    vertex = second;
                    while (vertex != ancestor) {
                        parent[vertex].up -= amount;
                        parent[vertex].down += amount;
                        vertex = parent[vertex].vertex;
                    }
                }

                int vertex = first;
                int new_parent = second;
                std::pair<Cap, Cap> parent_capacities{
                    edges[entering_edge].cap - amount,
                    edges[entering_edge ^ 1].cap + amount
                };
                Cost potential_difference = -cycle_cost;
                if (!leave_first_side) {
                    std::swap(vertex, new_parent);
                    std::swap(parent_capacities.first, parent_capacities.second);
                    potential_difference = -potential_difference;
                }
                int parent_edge = entering_edge ^ (leave_first_side ? 0 : 1);

                while (new_parent != leaving_vertex) {
                    int new_depth = depth[new_parent];
                    int tour_index = 2 * vertex;
                    while (tour_index != 2 * vertex + 1) {
                        if ((tour_index & 1) == 0) {
                            new_depth++;
                            potential[tour_index / 2] += potential_difference;
                            depth[tour_index / 2] = new_depth;
                        } else {
                            new_depth--;
                        }
                        tour_index = next[tour_index];
                    }

                    connect(previous[2 * vertex], next[2 * vertex + 1]);
                    connect(2 * vertex + 1, next[2 * new_parent]);
                    connect(2 * new_parent, 2 * vertex);

                    std::swap(parent[vertex].edge, parent_edge);
                    parent_edge ^= 1;
                    std::swap(parent[vertex].up, parent_capacities.first);
                    std::swap(parent[vertex].down, parent_capacities.second);
                    std::swap(parent_capacities.first, parent_capacities.second);

                    int old_parent = parent[vertex].vertex;
                    parent[vertex].vertex = new_parent;
                    new_parent = vertex;
                    vertex = old_parent;
                }
                edges[parent_edge].cap = parent_capacities.first;
                edges[parent_edge ^ 1].cap = parent_capacities.second;
            };

            const int candidate_limit = std::max(
                int(0.2 * std::sqrt(double(original_edge_count))), 10
            );
            const int minor_limit = std::max(candidate_limit / 10, 3);
            std::vector<int> candidates;
            candidates.reserve(candidate_limit);

            auto minor_pivot = [&] {
                Cost best_cost = Cost(0);
                int best_edge = -1;
                int index = 0;
                while (index < int(candidates.size())) {
                    int edge = candidates[index];
                    if (edges[edge].cap == Cap(0)) {
                        candidates[index] = candidates.back();
                        candidates.pop_back();
                        continue;
                    }
                    Cost reduced_cost =
                        edges[edge].cost
                        + potential[edges[edge ^ 1].to]
                        - potential[edges[edge].to];
                    if (reduced_cost >= Cost(0)) {
                        candidates[index] = candidates.back();
                        candidates.pop_back();
                        continue;
                    }
                    if (reduced_cost < best_cost) {
                        best_cost = reduced_cost;
                        best_edge = edge;
                    }
                    index++;
                }
                if (best_edge == -1) return false;
                push_flow(best_edge);
                return true;
            };

            int edge = 0;
            while (true) {
                for (int iteration = 0; iteration < minor_limit; iteration++) {
                    if (!minor_pivot()) break;
                }

                Cost best_cost = Cost(0);
                int best_edge = -1;
                candidates.clear();
                for (int scanned = 0; scanned < int(edges.size()); scanned++) {
                    if (edges[edge].cap != Cap(0)) {
                        Cost reduced_cost =
                            edges[edge].cost
                            + potential[edges[edge ^ 1].to]
                            - potential[edges[edge].to];
                        if (reduced_cost < Cost(0)) {
                            if (reduced_cost < best_cost) {
                                best_cost = reduced_cost;
                                best_edge = edge;
                            }
                            candidates.push_back(edge);
                            if (int(candidates.size()) == candidate_limit) break;
                        }
                    }
                    edge++;
                    if (edge == int(edges.size())) edge = 0;
                }
                if (candidates.empty()) break;
                push_flow(best_edge);
            }

            for (int vertex = 0; vertex < n; vertex++) {
                edges[parent[vertex].edge].cap = parent[vertex].up;
                edges[parent[vertex].edge ^ 1].cap = parent[vertex].down;
            }

            bool feasible = true;
            for (int vertex = 0; vertex < n; vertex++) {
                int artificial_edge = original_edge_count + 2 * vertex;
                if (
                    (excess[vertex] >= Cap(0)
                        && edges[artificial_edge ^ 1].cap != Cap(0))
                    || (excess[vertex] < Cap(0)
                        && edges[artificial_edge].cap != Cap(0))
                ) {
                    feasible = false;
                    break;
                }
            }
            potential.pop_back();
            return feasible;
        }

        Cap edge_flow(int edge_id, Cap lower) const {
            return lower + edges[2 * edge_id + 1].cap;
        }
    };

    int _n;
    std::vector<Edge> _edges;
    std::vector<Cap> _balance;

   public:
    BoundedMinCostFlow() : BoundedMinCostFlow(0) {}

    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_edges.size());
    }

    void reserve_edges(int edge_count) {
        assert(0 <= edge_count);
        _edges.reserve(edge_count);
    }

    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(lower <= upper);
        int id = int(_edges.size());
        _edges.push_back(Edge{from, to, lower, upper, cost});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_edges.size()));
        return _edges[i];
    }

    std::vector<Edge> edges() const {
        return _edges;
    }

    void set_balance(int v, Cap b) {
        assert(0 <= v && v < _n);
        _balance[v] = b;
    }

    void add_balance(int v, Cap b) {
        assert(0 <= v && v < _n);
        _balance[v] += b;
    }

    void add_supply(int v, Cap supply) {
        assert(Cap(0) <= supply);
        add_balance(v, supply);
    }

    void add_demand(int v, Cap demand) {
        assert(Cap(0) <= demand);
        add_balance(v, -demand);
    }

    Cap balance(int v) const {
        assert(0 <= v && v < _n);
        return _balance[v];
    }

    const std::vector<Cap>& balances() const {
        return _balance;
    }

    std::optional<Result> min_cost_flow() const {
        return min_cost_flow(_balance);
    }

    std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const {
        assert(int(balance.size()) == _n);
        Cap balance_sum = Cap(0);
        for (Cap value : balance) balance_sum += value;
        if (balance_sum != Cap(0)) return std::nullopt;

        NetworkSimplexSolver solver(_n, balance);
        solver.reserve_edges(int(_edges.size()));
        for (const auto& edge : _edges) {
            solver.add_edge(edge.from, edge.to, edge.lower, edge.upper, edge.cost);
        }
        if (!solver.solve()) return std::nullopt;

        Result result;
        result.balance = balance;
        result.cost = TotalCost(0);
        result.edges.reserve(_edges.size());
        for (int i = 0; i < int(_edges.size()); i++) {
            const auto& e = _edges[i];
            Cap flow = solver.edge_flow(i, e.lower);
            result.cost += TotalCost(flow) * TotalCost(e.cost);
            result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, flow, e.cost});
        }
        result.potential = std::move(solver.potential);
        return result;
    }

    std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        std::vector<Cap> balance = _balance;
        balance[s] += flow_value;
        balance[t] -= flow_value;
        return min_cost_flow(balance);
    }
};

template <class Cap, class Cost, class TotalCost = Cost>
using BMinCostFlow = BoundedMinCostFlow<Cap, Cost, TotalCost>;

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
