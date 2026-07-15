#ifndef M1UNE_FLOW_MIN_COST_FLOW_HPP
#define M1UNE_FLOW_MIN_COST_FLOW_HPP 1

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <cstddef>
#include <functional>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "bounded_min_cost_flow.hpp"
#include "max_flow.hpp"

namespace m1une {
namespace flow {

template <class Cap, class Cost>
struct MinCostFlow {
    struct Edge {
        int from;
        int to;
        Cap cap;
        Cap flow;
        Cost cost;
    };

   private:
    struct InternalEdge {
        int to;
        int rev;
        Cap cap;
        Cost cost;
    };

    int _n;
    std::vector<std::pair<int, int>> _pos;
    std::vector<std::vector<InternalEdge>> _g;
    bool _has_negative_cost;
    bool _has_flow;

    template <class Key>
    struct RadixHeap {
        using Unsigned = std::make_unsigned_t<Key>;
        static constexpr int bits = std::numeric_limits<Unsigned>::digits;

        std::array<std::vector<std::pair<Unsigned, int>>, bits + 1> bucket;
        Unsigned last = 0;
        std::size_t count = 0;

        static int index(Unsigned first, Unsigned second) {
            return int(std::bit_width(first ^ second));
        }

        void clear() {
            for (auto& values : bucket) values.clear();
            last = 0;
            count = 0;
        }

        bool empty() const {
            return count == 0;
        }

        void push(Key key, int vertex) {
            Unsigned value = static_cast<Unsigned>(key);
            assert(last <= value);
            bucket[index(value, last)].emplace_back(value, vertex);
            count++;
        }

        std::pair<Key, int> pop() {
            if (bucket[0].empty()) {
                int i = 1;
                while (bucket[i].empty()) i++;
                last = bucket[i][0].first;
                for (const auto& value : bucket[i]) {
                    last = std::min(last, value.first);
                }
                for (const auto& value : bucket[i]) {
                    bucket[index(value.first, last)].push_back(value);
                }
                bucket[i].clear();
            }
            auto [key, vertex] = bucket[0].back();
            bucket[0].pop_back();
            count--;
            return {static_cast<Key>(key), vertex};
        }
    };

    template <class Key>
    struct BinaryHeap {
        using Value = std::pair<Key, int>;
        std::vector<Value> heap;

        void clear() {
            heap.clear();
        }

        bool empty() const {
            return heap.empty();
        }

        void push(Key key, int vertex) {
            heap.emplace_back(key, vertex);
            std::push_heap(heap.begin(), heap.end(), std::greater<Value>());
        }

        Value pop() {
            std::pop_heap(heap.begin(), heap.end(), std::greater<Value>());
            Value result = heap.back();
            heap.pop_back();
            return result;
        }
    };

    template <
        class Key,
        bool UseRadix =
            std::numeric_limits<Key>::is_integer && sizeof(Key) <= 8
    >
    struct HeapSelector {
        using Type = BinaryHeap<Key>;
    };

    template <class Key>
    struct HeapSelector<Key, true> {
        using Type = RadixHeap<Key>;
    };

    bool use_network_simplex(int s, int t, Cap flow_limit) const {
        if (_has_negative_cost) return false;
        if (_pos.size() < 64) return false;
        auto add_saturated = [](Cap first, Cap second) {
            const Cap maximum = std::numeric_limits<Cap>::max();
            return maximum - first < second ? maximum : first + second;
        };
        struct TerminalCapacity {
            Cap total = Cap(0);
            std::array<Cap, 7> largest{};
        };
        auto add_capacity = [&](TerminalCapacity& terminal, Cap cap) {
            terminal.total = add_saturated(terminal.total, cap);
            for (Cap& current : terminal.largest) {
                if (cap <= current) break;
                std::swap(cap, current);
            }
        };
        TerminalCapacity source;
        for (const auto& e : _g[s]) {
            if (e.to == s) continue;
            add_capacity(source, e.cap);
        }
        TerminalCapacity sink;
        for (const auto& e : _g[t]) {
            if (e.to == t) continue;
            Cap cap = _g[e.to][e.rev].cap;
            add_capacity(sink, cap);
        }
        Cap target = std::min(
            flow_limit,
            std::min(source.total, sink.total)
        );
        if (target == Cap(0)) return false;
        auto requires_eight_arcs = [&](const TerminalCapacity& terminal) {
            Cap sum = Cap(0);
            for (Cap cap : terminal.largest) {
                sum = add_saturated(sum, cap);
            }
            return sum < target;
        };
        return requires_eight_arcs(source) && requires_eight_arcs(sink);
    }

    std::pair<Cap, Cost> network_simplex_flow(
        int s,
        int t,
        Cap flow_limit
    ) {
        struct ResidualArc {
            int edge;
            bool reverse;
        };

        using Solver = BoundedMinCostFlow<Cap, Cost, Cost>;
        std::vector<ResidualArc> arcs;
        arcs.reserve(2 * _pos.size());
        for (int i = 0; i < int(_pos.size()); i++) {
            auto [from, idx] = _pos[i];
            const auto& e = _g[from][idx];
            const auto& reverse = _g[e.to][e.rev];
            if (e.cap != Cap(0)) {
                arcs.push_back(ResidualArc{i, false});
            }
            if (reverse.cap != Cap(0)) {
                arcs.push_back(ResidualArc{i, true});
            }
        }

        auto add_saturated = [](Cap first, Cap second, bool& exact) {
            const Cap maximum = std::numeric_limits<Cap>::max();
            if (maximum - first < second) {
                exact = false;
                return maximum;
            }
            return first + second;
        };
        bool source_capacity_exact = true;
        Cap source_capacity = Cap(0);
        for (const auto& e : _g[s]) {
            if (e.to == s) continue;
            source_capacity = add_saturated(
                source_capacity,
                e.cap,
                source_capacity_exact
            );
        }
        bool sink_capacity_exact = true;
        Cap sink_capacity = Cap(0);
        for (const auto& e : _g[t]) {
            if (e.to == t) continue;
            sink_capacity = add_saturated(
                sink_capacity,
                _g[e.to][e.rev].cap,
                sink_capacity_exact
            );
        }
        Cap target = std::min(
            flow_limit,
            std::min(source_capacity, sink_capacity)
        );
        if (target == Cap(0)) return {Cap(0), Cost(0)};

        struct ArcData {
            int from;
            int to;
            Cap cap;
            Cost cost;
        };
        auto arc_data = [&](const ResidualArc& arc) {
            auto [from, idx] = _pos[arc.edge];
            const auto& e = _g[from][idx];
            const auto& reverse = _g[e.to][e.rev];
            return arc.reverse
                ? ArcData{e.to, from, reverse.cap, reverse.cost}
                : ArcData{from, e.to, e.cap, e.cost};
        };
        auto apply_flow = [&](const ResidualArc& arc, Cap amount) {
            auto [from, idx] = _pos[arc.edge];
            auto& e = _g[from][idx];
            auto& reverse = _g[e.to][e.rev];
            if (arc.reverse) {
                reverse.cap -= amount;
                e.cap += amount;
            } else {
                e.cap -= amount;
                reverse.cap += amount;
            }
        };

        bool target_infeasible = false;
        if (
            source_capacity_exact && sink_capacity_exact &&
            target == source_capacity && target == sink_capacity
        ) {
            Solver terminal_solver(_n);
            terminal_solver.reserve_edges(int(arcs.size()));
            std::vector<Cap> balance(_n, Cap(0));
            std::vector<int> internal_arcs;
            std::vector<int> fixed_arcs;
            internal_arcs.reserve(arcs.size());
            fixed_arcs.reserve(_g[s].size() + _g[t].size());
            Cost fixed_cost = Cost(0);
            for (int i = 0; i < int(arcs.size()); i++) {
                ArcData data = arc_data(arcs[i]);
                if (data.from == s) {
                    if (data.to == s) continue;
                    fixed_arcs.push_back(i);
                    fixed_cost += Cost(data.cap) * data.cost;
                    if (data.to != t) balance[data.to] += data.cap;
                } else if (data.to == t) {
                    if (data.from == t) continue;
                    fixed_arcs.push_back(i);
                    fixed_cost += Cost(data.cap) * data.cost;
                    balance[data.from] -= data.cap;
                } else if (data.to != s && data.from != t) {
                    terminal_solver.add_edge(
                        data.from,
                        data.to,
                        Cap(0),
                        data.cap,
                        data.cost
                    );
                    internal_arcs.push_back(i);
                }
            }
            auto terminal_result = terminal_solver.min_cost_flow(balance);
            if (terminal_result) {
                for (int i : fixed_arcs) {
                    apply_flow(arcs[i], arc_data(arcs[i]).cap);
                }
                for (int i = 0; i < int(internal_arcs.size()); i++) {
                    apply_flow(
                        arcs[internal_arcs[i]],
                        terminal_result->flow(i)
                    );
                }
                _has_flow = true;
                return {target, fixed_cost + terminal_result->cost};
            }
            target_infeasible = true;
        }

        Solver solver(_n);
        solver.reserve_edges(int(arcs.size()));
        for (const auto& arc : arcs) {
            ArcData data = arc_data(arc);
            solver.add_edge(
                data.from,
                data.to,
                Cap(0),
                data.cap,
                data.cost
            );
        }
        Cap sent = target;
        std::optional<typename Solver::Result> result;
        if (
            !target_infeasible &&
            target != std::numeric_limits<Cap>::max()
        ) {
            result = solver.min_cost_st_flow(s, t, target);
        }
        if (!result) {
            MaxFlow<Cap> feasible(_n);
            feasible.reserve_edges(int(arcs.size()));
            for (const auto& arc : arcs) {
                auto [from, idx] = _pos[arc.edge];
                const auto& e = _g[from][idx];
                const auto& reverse = _g[e.to][e.rev];
                if (arc.reverse) {
                    feasible.add_edge(e.to, from, reverse.cap);
                } else {
                    feasible.add_edge(from, e.to, e.cap);
                }
            }
            sent = feasible.max_flow(s, t, target);
            if (sent == Cap(0)) return {Cap(0), Cost(0)};
            result = solver.min_cost_st_flow(s, t, sent);
        }
        assert(result.has_value());
        for (int i = 0; i < int(arcs.size()); i++) {
            auto [from, idx] = _pos[arcs[i].edge];
            auto& e = _g[from][idx];
            auto& reverse = _g[e.to][e.rev];
            Cap amount = result->flow(i);
            if (arcs[i].reverse) {
                reverse.cap -= amount;
                e.cap += amount;
            } else {
                e.cap -= amount;
                reverse.cap += amount;
            }
        }
        _has_flow = true;
        return {sent, result->cost};
    }

    void init_potential(int s, std::vector<Cost>& potential, Cost cost_inf) const {
        if (!_has_negative_cost && !_has_flow) {
            potential.assign(_n, Cost(0));
            return;
        }
        potential.assign(_n, cost_inf);
        potential[s] = Cost(0);
        for (int iter = 0; iter < _n - 1; iter++) {
            bool updated = false;
            for (int v = 0; v < _n; v++) {
                if (potential[v] == cost_inf) continue;
                for (const auto& e : _g[v]) {
                    if (e.cap == Cap(0)) continue;
                    Cost nd = potential[v] + e.cost;
                    if (nd < potential[e.to]) {
                        potential[e.to] = nd;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
        for (int v = 0; v < _n; v++) {
            if (potential[v] == cost_inf) potential[v] = Cost(0);
        }
    }

   public:
    MinCostFlow() : MinCostFlow(0) {}

    explicit MinCostFlow(int n)
        : _n(n), _g(n), _has_negative_cost(false), _has_flow(false) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    int edge_count() const {
        return int(_pos.size());
    }

    void reserve_edges(int edge_count) {
        assert(0 <= edge_count);
        _pos.reserve(edge_count);
        if (_n == 0 || edge_count == 0 ||
            2 * std::size_t(edge_count) < std::size_t(_n)) {
            return;
        }
        const std::size_t average_degree =
            (3 * std::size_t(edge_count) + std::size_t(_n) - 1)
            / std::size_t(_n);
        for (auto& edges : _g) edges.reserve(average_degree);
    }

    void reserve_edges(int edge_count, const std::vector<int>& degrees) {
        assert(0 <= edge_count);
        assert(int(degrees.size()) == _n);
        _pos.reserve(edge_count);
        for (int v = 0; v < _n; v++) {
            assert(0 <= degrees[v]);
            _g[v].reserve(degrees[v]);
        }
    }

    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(Cap(0) <= cap);
        _has_negative_cost = _has_negative_cost || cost < Cost(0);
        int id = int(_pos.size());
        int from_id = int(_g[from].size());
        int to_id = int(_g[to].size());
        if (from == to) to_id++;
        _pos.emplace_back(from, from_id);
        _g[from].push_back(InternalEdge{to, to_id, cap, cost});
        _g[to].push_back(InternalEdge{from, from_id, Cap(0), -cost});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_pos.size()));
        auto [from, idx] = _pos[i];
        const auto& e = _g[from][idx];
        const auto& re = _g[e.to][e.rev];
        return Edge{from, e.to, e.cap + re.cap, re.cap, e.cost};
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        result.reserve(_pos.size());
        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));
        return result;
    }

    std::pair<Cap, Cost> flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }

    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        assert(Cap(0) <= flow_limit);
        if (flow_limit == Cap(0)) return {Cap(0), Cost(0)};
        if constexpr (
            std::numeric_limits<Cap>::is_integer &&
            std::numeric_limits<Cap>::is_signed &&
            std::numeric_limits<Cost>::is_signed
        ) {
            if (use_network_simplex(s, t, flow_limit)) {
                return network_simplex_flow(s, t, flow_limit);
            }
        }
        auto result = slope(s, t, flow_limit);
        return result.back();
    }

    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {
        return slope(s, t, std::numeric_limits<Cap>::max());
    }

    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        assert(Cap(0) <= flow_limit);

        const Cost cost_inf = std::numeric_limits<Cost>::max() / Cost(4);
        std::vector<Cost> potential, dist(_n);
        std::vector<int> prev_v(_n), prev_e(_n);
        std::vector<int> settled;
        settled.reserve(_n);
        typename HeapSelector<Cost>::Type que;
        init_potential(s, potential, cost_inf);

        std::vector<std::pair<Cap, Cost>> result;
        result.emplace_back(Cap(0), Cost(0));
        Cap flow = 0;
        Cost cost = 0;

        while (flow < flow_limit) {
            std::fill(dist.begin(), dist.end(), cost_inf);
            dist[s] = Cost(0);
            settled.clear();
            que.clear();
            que.push(Cost(0), s);

            while (!que.empty()) {
                auto [d, v] = que.pop();
                if (dist[v] != d) continue;
                settled.push_back(v);
                if (v == t) break;
                for (int i = 0; i < int(_g[v].size()); i++) {
                    const auto& e = _g[v][i];
                    if (e.cap == Cap(0)) continue;
                    Cost nd = d + e.cost + potential[v] - potential[e.to];
                    if (nd >= dist[e.to]) continue;
                    dist[e.to] = nd;
                    prev_v[e.to] = v;
                    prev_e[e.to] = i;
                    que.push(nd, e.to);
                }
            }

            if (dist[t] == cost_inf) break;
            for (int v : settled) {
                potential[v] += dist[v] - dist[t];
            }

            Cap add = flow_limit - flow;
            for (int v = t; v != s; v = prev_v[v]) {
                add = std::min(add, _g[prev_v[v]][prev_e[v]].cap);
            }
            Cost path_cost = potential[t] - potential[s];
            for (int v = t; v != s; v = prev_v[v]) {
                auto& e = _g[prev_v[v]][prev_e[v]];
                e.cap -= add;
                _g[e.to][e.rev].cap += add;
            }

            flow += add;
            cost += Cost(add) * path_cost;
            result.emplace_back(flow, cost);
        }

        _has_flow = _has_flow || flow != Cap(0);
        return result;
    }
};

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_MIN_COST_FLOW_HPP
