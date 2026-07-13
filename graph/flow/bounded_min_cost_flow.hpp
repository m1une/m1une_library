#ifndef M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
#define M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap, class Cost>
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
        Cost cost;

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
    struct ScalingEdge {
        int to;
        int rev;
        Cap cap;
        Cap flow;
        Cost cost;
    };

    struct ScalingSolver {
        int n;
        std::vector<std::vector<ScalingEdge>> graph;
        std::vector<std::pair<int, int>> positions;
        std::vector<Cap> excess;
        std::vector<Cost> potential;
        std::vector<Cost> dist;
        std::vector<int> parent_vertex;
        std::vector<int> parent_edge;
        std::vector<int> excess_vertices;
        std::vector<int> deficit_vertices;
        Cost farthest = Cost(0);

        ScalingSolver(int vertex_count, const std::vector<Cap>& balance)
            : n(vertex_count), graph(vertex_count), excess(balance),
              potential(vertex_count, Cost(0)) {}

        int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {
            int id = int(positions.size());
            int from_id = int(graph[from].size());
            int to_id = int(graph[to].size());
            if (from == to) to_id++;
            positions.emplace_back(from, from_id);
            graph[from].push_back(ScalingEdge{to, to_id, upper, Cap(0), cost});
            graph[to].push_back(ScalingEdge{from, from_id, -lower, Cap(0), -cost});
            return id;
        }

        Cap residual_capacity(int from, int edge_id) const {
            const auto& edge = graph[from][edge_id];
            return edge.cap - edge.flow;
        }

        Cost residual_cost(int from, const ScalingEdge& edge) const {
            return edge.cost + potential[from] - potential[edge.to];
        }

        void push(int from, int edge_id, Cap amount) {
            auto& edge = graph[from][edge_id];
            edge.flow += amount;
            graph[edge.to][edge.rev].flow -= amount;
        }

        void saturate_negative(Cap delta) {
            excess_vertices.clear();
            deficit_vertices.clear();
            for (int from = 0; from < n; from++) {
                for (int edge_id = 0; edge_id < int(graph[from].size()); edge_id++) {
                    const auto& edge = graph[from][edge_id];
                    Cap residual = edge.cap - edge.flow;
                    residual -= residual % delta;
                    if (residual_cost(from, edge) < Cost(0) || residual < Cap(0)) {
                        int to = edge.to;
                        push(from, edge_id, residual);
                        excess[from] -= residual;
                        excess[to] += residual;
                    }
                }
            }
            for (int vertex = 0; vertex < n; vertex++) {
                if (excess[vertex] > Cap(0)) {
                    excess_vertices.push_back(vertex);
                } else if (excess[vertex] < Cap(0)) {
                    deficit_vertices.push_back(vertex);
                }
            }
        }

        bool dual(Cap delta) {
            excess_vertices.erase(
                std::remove_if(
                    excess_vertices.begin(), excess_vertices.end(),
                    [&](int vertex) { return excess[vertex] < delta; }
                ),
                excess_vertices.end()
            );
            deficit_vertices.erase(
                std::remove_if(
                    deficit_vertices.begin(), deficit_vertices.end(),
                    [&](int vertex) { return excess[vertex] > -delta; }
                ),
                deficit_vertices.end()
            );

            const Cost unreachable = std::numeric_limits<Cost>::max();
            dist.assign(n, unreachable);
            parent_vertex.assign(n, -1);
            parent_edge.assign(n, -1);
            using QueueEntry = std::pair<Cost, int>;
            std::priority_queue<
                QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>
            > queue;
            for (int vertex : excess_vertices) {
                dist[vertex] = Cost(0);
                queue.emplace(Cost(0), vertex);
            }

            farthest = Cost(0);
            int reached_deficits = 0;
            while (!queue.empty()) {
                auto [distance, from] = queue.top();
                queue.pop();
                if (dist[from] != distance) continue;
                farthest = distance;
                if (excess[from] <= -delta) reached_deficits++;
                if (reached_deficits >= int(deficit_vertices.size())) break;

                for (int edge_id = 0; edge_id < int(graph[from].size()); edge_id++) {
                    const auto& edge = graph[from][edge_id];
                    if (edge.cap - edge.flow < delta) continue;
                    Cost next_distance = distance + residual_cost(from, edge);
                    if (next_distance >= dist[edge.to]) continue;
                    dist[edge.to] = next_distance;
                    parent_vertex[edge.to] = from;
                    parent_edge[edge.to] = edge_id;
                    queue.emplace(next_distance, edge.to);
                }
            }

            for (int vertex = 0; vertex < n; vertex++) {
                potential[vertex] += std::min(dist[vertex], farthest);
            }
            return reached_deficits > 0;
        }

        void primal(Cap delta) {
            for (int sink : deficit_vertices) {
                if (dist[sink] > farthest) continue;
                Cap amount = -excess[sink];
                int root = sink;
                while (parent_edge[root] != -1) {
                    int from = parent_vertex[root];
                    amount = std::min(amount, residual_capacity(from, parent_edge[root]));
                    root = from;
                }
                amount = std::min(amount, excess[root]);
                amount -= amount % delta;
                if (amount <= Cap(0)) continue;

                int vertex = sink;
                while (parent_edge[vertex] != -1) {
                    int from = parent_vertex[vertex];
                    int edge_id = parent_edge[vertex];
                    push(from, edge_id, amount);
                    if (residual_capacity(from, edge_id) == Cap(0)) {
                        parent_edge[vertex] = -1;
                    }
                    vertex = from;
                }
                excess[sink] += amount;
                excess[root] -= amount;
            }
        }

        bool solve() {
            Cap scale_bound = Cap(1);
            for (Cap value : excess) {
                scale_bound = std::max(scale_bound, value);
                scale_bound = std::max(scale_bound, -value);
            }
            for (const auto& edges : graph) {
                for (const auto& edge : edges) {
                    Cap residual = edge.cap - edge.flow;
                    scale_bound = std::max(scale_bound, residual);
                    scale_bound = std::max(scale_bound, -residual);
                }
            }

            Cap delta = Cap(1);
            while (delta <= scale_bound / Cap(2)) delta *= Cap(2);
            while (true) {
                saturate_negative(delta);
                while (dual(delta)) primal(delta);
                if (delta == Cap(1)) break;
                delta /= Cap(2);
            }
            return excess_vertices.empty() && deficit_vertices.empty();
        }

        Cap edge_flow(int edge_id) const {
            auto [from, index] = positions[edge_id];
            return graph[from][index].flow;
        }
    };

    int _n;
    std::vector<Edge> _edges;
    std::vector<Cap> _balance;

    std::vector<Cost> residual_potential(
        const std::vector<ResultEdge>& edges
    ) const {
        std::vector<Cost> potential(_n, Cost(0));
        bool updated = false;
        for (int iteration = 0; iteration < _n; iteration++) {
            updated = false;
            for (const ResultEdge& edge : edges) {
                if (
                    edge.flow < edge.upper &&
                    potential[edge.to] > potential[edge.from] + edge.cost
                ) {
                    potential[edge.to] = potential[edge.from] + edge.cost;
                    updated = true;
                }
                if (
                    edge.lower < edge.flow &&
                    potential[edge.from] > potential[edge.to] - edge.cost
                ) {
                    potential[edge.from] = potential[edge.to] - edge.cost;
                    updated = true;
                }
            }
            if (!updated) break;
        }
        assert(!updated);
        return potential;
    }

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

        ScalingSolver solver(_n, balance);
        for (const auto& edge : _edges) {
            solver.add_edge(edge.from, edge.to, edge.lower, edge.upper, edge.cost);
        }
        if (!solver.solve()) return std::nullopt;

        Result result;
        result.balance = balance;
        result.cost = Cost(0);
        result.edges.reserve(_edges.size());
        for (int i = 0; i < int(_edges.size()); i++) {
            const auto& e = _edges[i];
            Cap flow = solver.edge_flow(i);
            result.cost += Cost(flow) * e.cost;
            result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper, flow, e.cost});
        }
        result.potential = residual_potential(result.edges);
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

template <class Cap, class Cost>
using BMinCostFlow = BoundedMinCostFlow<Cap, Cost>;

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP
