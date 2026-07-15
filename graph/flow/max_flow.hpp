#ifndef M1UNE_FLOW_MAX_FLOW_HPP
#define M1UNE_FLOW_MAX_FLOW_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

namespace m1une {
namespace flow {

template <class Cap>
struct MaxFlow {
    struct Edge {
        int from;
        int to;
        Cap cap;
        Cap flow;
    };

   private:
    struct InternalEdge {
        int to;
        int rev;
        Cap cap;
    };

    struct Position {
        int from;
        int edge;
    };

    int _n;
    std::vector<Position> _pos;
    std::vector<std::vector<InternalEdge>> _g;

    Cap push_relabel(int s, int t) {
        const std::size_t edge_count = _pos.size();
        const std::size_t source_degree = _g[s].size();
        const std::size_t sink_degree = _g[t].size();
        const std::size_t terminal_degree =
            std::min(source_degree, sink_degree);
        const bool dense = edge_count >= 5 * std::size_t(_n);
        const std::size_t wide_threshold =
            4 * (edge_count / std::size_t(_n) + 1);
        // Reverse input order defeats several ordering-sensitive hard cases,
        // while forward order is substantially better on ordinary random
        // graphs with medium-width terminals.
        const bool reverse_scan =
            terminal_degree > wide_threshold ||
            (terminal_degree <= 4 &&
             (dense ||
              (source_degree == 2 && sink_degree == 2) ||
              (terminal_degree == 1 &&
               edge_count >= 2 * std::size_t(_n))));
        const int dead = 2 * _n;
        const int unreachable = _n + 1;
        std::vector<Cap> excess(_n, Cap(0));
        std::vector<int> state(8 * std::size_t(_n) + 2);
        int* height = state.data();
        int* height_count = height + _n;
        int* current = height_count + dead + 1;
        int* queue = current + _n;
        int* next = queue + _n;
        int* bucket_head = next + _n;
        std::vector<char> active(_n, false);
        int highest = -1;
        long long work = 0;
        const long long arc_count =
            2LL * static_cast<long long>(_pos.size());
        const long long work_limit = std::max(
            1LL,
            (reverse_scan ? 3 : 4) * arc_count + _n
        );

        auto activate = [&](int v) {
            if (v == s || v == t || active[v] || excess[v] == Cap(0) ||
                height[v] >= dead) {
                return;
            }
            active[v] = true;
            next[v] = bucket_head[height[v]];
            bucket_head[height[v]] = v;
            highest = std::max(highest, height[v]);
        };

        auto rebuild_buckets = [&]() {
            std::fill(bucket_head, bucket_head + dead + 1, -1);
            std::fill(active.begin(), active.end(), false);
            highest = -1;
            for (int v = 0; v < _n; v++) activate(v);
        };

        auto global_relabel = [&]() {
            std::fill(height, height + _n, unreachable);
            std::fill(height_count, height_count + dead + 1, 0);
            for (int v = 0; v < _n; v++) {
                current[v] = reverse_scan ? int(_g[v].size()) - 1 : 0;
            }
            int head = 0;
            int tail = 0;
            height[t] = 0;
            height[s] = _n;
            queue[tail++] = t;
            while (head != tail) {
                int v = queue[head++];
                for (const auto& e : _g[v]) {
                    if (e.to == s || height[e.to] != unreachable) continue;
                    const auto& reverse = _g[e.to][e.rev];
                    if (reverse.cap == Cap(0)) continue;
                    height[e.to] = height[v] + 1;
                    queue[tail++] = e.to;
                }
            }
            for (int v = 0; v < _n; v++) height_count[height[v]]++;
            rebuild_buckets();
            work = 0;
        };

        auto gap = [&](int empty_height) {
            for (int v = 0; v < _n; v++) {
                if (v == s || v == t || height[v] <= empty_height ||
                    height[v] >= _n) {
                    continue;
                }
                height_count[height[v]]--;
                height[v] = unreachable;
                height_count[height[v]]++;
                current[v] = reverse_scan ? int(_g[v].size()) - 1 : 0;
            }
            rebuild_buckets();
        };

        auto relabel = [&](int v) -> bool {
            int old_height = height[v];
            int new_height = dead;
            work += int(_g[v].size());
            for (const auto& e : _g[v]) {
                if (e.cap != Cap(0)) {
                    new_height = std::min(new_height, height[e.to] + 1);
                }
            }
            height_count[old_height]--;
            height[v] = std::min(new_height, dead);
            height_count[height[v]]++;
            current[v] = reverse_scan ? int(_g[v].size()) - 1 : 0;
            if (old_height < _n && height_count[old_height] == 0) {
                gap(old_height);
                return true;
            }
            return false;
        };

        auto push = [&](int v, InternalEdge& e) {
            Cap sent = std::min(excess[v], e.cap);
            bool was_zero = excess[e.to] == Cap(0);
            e.cap -= sent;
            _g[e.to][e.rev].cap += sent;
            excess[v] -= sent;
            excess[e.to] += sent;
            if (was_zero) activate(e.to);
        };

        auto discharge = [&]<bool Reverse>(int v) {
            while (excess[v] != Cap(0) && height[v] < dead) {
                bool exhausted_edges;
                if constexpr (Reverse) {
                    exhausted_edges = current[v] < 0;
                } else {
                    exhausted_edges = current[v] == int(_g[v].size());
                }
                if (exhausted_edges) {
                    if (relabel(v)) return;
                    continue;
                }
                auto& e = _g[v][current[v]];
                work++;
                if (e.cap != Cap(0) && height[v] == height[e.to] + 1) {
                    push(v, e);
                } else {
                    if constexpr (Reverse) {
                        current[v]--;
                    } else {
                        current[v]++;
                    }
                }
            }
            activate(v);
        };

        for (auto& e : _g[s]) {
            if (e.to == s || e.cap == Cap(0)) continue;
            Cap sent = e.cap;
            e.cap = Cap(0);
            _g[e.to][e.rev].cap += sent;
            excess[e.to] += sent;
        }
        global_relabel();

        while (highest >= 0) {
            if (bucket_head[highest] == -1) {
                highest--;
                continue;
            }
            int v = bucket_head[highest];
            bucket_head[highest] = next[v];
            if (!active[v] || height[v] != highest) continue;
            active[v] = false;
            if (reverse_scan) {
                discharge.template operator()<true>(v);
            } else {
                discharge.template operator()<false>(v);
            }
            if (work >= work_limit) global_relabel();
        }
        return excess[t];
    }

    Cap dinic_phases(
        int s,
        int t,
        Cap flow_limit,
        int phase_limit,
        bool& exhausted
    ) {
        std::vector<int> work(3 * std::size_t(_n));
        int* level = work.data();
        int* iter = level + _n;
        int* queue = iter + _n;
        auto bfs = [&]() -> bool {
            std::fill(level, level + _n, -1);
            int head = 0;
            int tail = 0;
            level[s] = 0;
            queue[tail++] = s;
            while (head != tail) {
                int v = queue[head++];
                const auto& edges = _g[v];
                for (const auto& e : edges) {
                    if (level[e.to] != -1 || e.cap == Cap(0)) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return true;
                    queue[tail++] = e.to;
                }
            }
            return false;
        };

        auto dfs = [&](auto&& self, int v, Cap up) -> Cap {
            if (v == s) return up;
            Cap result = Cap(0);
            const int current_level = level[v];
            auto& edges = _g[v];
            const int edge_count = int(edges.size());
            for (int& i = iter[v]; i < edge_count; i++) {
                auto& e = edges[i];
                if (level[e.to] + 1 != current_level) continue;
                auto& reverse = _g[e.to][e.rev];
                if (reverse.cap == Cap(0)) continue;
                Cap d = self(
                    self,
                    e.to,
                    std::min(up - result, reverse.cap)
                );
                if (d == Cap(0)) continue;
                e.cap += d;
                reverse.cap -= d;
                result += d;
                if (result == up) return result;
            }
            level[v] = _n;
            return result;
        };

        Cap flow = Cap(0);
        int phases = 0;
        exhausted = false;
        while (flow < flow_limit && phases < phase_limit) {
            if (!bfs()) {
                exhausted = true;
                break;
            }
            std::fill(iter, iter + _n, 0);
            flow += dfs(dfs, t, flow_limit - flow);
            phases++;
        }
        if (flow == flow_limit) exhausted = true;
        return flow;
    }

   public:
    MaxFlow() : MaxFlow(0) {}

    explicit MaxFlow(int n) : _n(n), _g(n) {
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

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(Cap(0) <= cap);
        int id = int(_pos.size());
        int from_id = int(_g[from].size());
        int to_id = int(_g[to].size());
        if (from == to) to_id++;
        _pos.push_back(Position{from, from_id});
        _g[from].push_back(InternalEdge{to, to_id, cap});
        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});
        return id;
    }

    int add_undirected_edge(int first, int second, Cap cap) {
        static_assert(std::numeric_limits<Cap>::is_signed);
        assert(0 <= first && first < _n);
        assert(0 <= second && second < _n);
        assert(Cap(0) <= cap);
        assert(cap <= std::numeric_limits<Cap>::max() / Cap(2));
        int id = int(_pos.size());
        int first_id = int(_g[first].size());
        int second_id = int(_g[second].size());
        if (first == second) second_id++;
        _pos.push_back(Position{first, ~first_id});
        _g[first].push_back(InternalEdge{second, second_id, cap});
        _g[second].push_back(InternalEdge{first, first_id, cap});
        return id;
    }

    Edge get_edge(int i) const {
        assert(0 <= i && i < int(_pos.size()));
        const auto& position = _pos[i];
        int from = position.from;
        bool undirected = position.edge < 0;
        int idx = undirected ? ~position.edge : position.edge;
        const auto& e = _g[from][idx];
        const auto& re = _g[e.to][e.rev];
        if (undirected) {
            return Edge{
                from,
                e.to,
                (e.cap + re.cap) / Cap(2),
                (re.cap - e.cap) / Cap(2)
            };
        }
        return Edge{from, e.to, e.cap + re.cap, re.cap};
    }

    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        result.reserve(_pos.size());
        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));
        return result;
    }

    void change_edge(int i, Cap new_cap, Cap new_flow) {
        assert(0 <= i && i < int(_pos.size()));
        assert(Cap(0) <= new_cap);
        auto& position = _pos[i];
        int from = position.from;
        bool undirected = position.edge < 0;
        int idx = undirected ? ~position.edge : position.edge;
        auto& e = _g[from][idx];
        auto& re = _g[e.to][e.rev];
        if (undirected) {
            assert(new_cap <= std::numeric_limits<Cap>::max() / Cap(2));
            assert(-new_cap <= new_flow && new_flow <= new_cap);
            e.cap = new_cap - new_flow;
            re.cap = new_cap + new_flow;
        } else {
            assert(Cap(0) <= new_flow && new_flow <= new_cap);
            e.cap = new_cap - new_flow;
            re.cap = new_flow;
        }
    }

    Cap max_flow(int s, int t) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        bool exhausted;
        const std::size_t edge_count = _pos.size();
        const std::size_t terminal_degree =
            std::min(_g[s].size(), _g[t].size());
        const bool dense = edge_count >= 5 * std::size_t(_n);
        const bool sparse_narrow_terminals =
            edge_count >= std::size_t(_n) &&
            2 <= _g[s].size() && _g[s].size() <= 4 &&
            2 <= _g[t].size() && _g[t].size() <= 4;
        // Only pay for a possible push-relabel handoff on graph shapes where
        // many Dinic phases are a realistic risk.
        const bool use_hybrid =
            (dense || sparse_narrow_terminals) &&
            terminal_degree <= 4 * (edge_count / std::size_t(_n) + 1);
        if (!use_hybrid) {
            return max_flow(s, t, std::numeric_limits<Cap>::max());
        }
        int phase_limit = dense ? 4 : 8;
        bool small_terminal_capacities = true;
        const int terminals[2] = {s, t};
        for (int v : terminals) {
            for (const auto& e : _g[v]) {
                if (Cap(2) < e.cap ||
                    Cap(2) < _g[e.to][e.rev].cap) {
                    small_terminal_capacities = false;
                    break;
                }
            }
            if (!small_terminal_capacities) break;
        }
        if (small_terminal_capacities) {
            return max_flow(s, t, std::numeric_limits<Cap>::max());
        }
        Cap flow = dinic_phases(
            s,
            t,
            std::numeric_limits<Cap>::max(),
            phase_limit,
            exhausted
        );
        if (!exhausted) flow += push_relabel(s, t);
        return flow;
    }

    Cap max_flow_push_relabel(int s, int t) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);
        return push_relabel(s, t);
    }

    Cap max_flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> work(3 * std::size_t(_n));
        int* level = work.data();
        int* iter = level + _n;
        int* queue = iter + _n;
        auto bfs = [&]() -> bool {
            std::fill(level, level + _n, -1);
            int head = 0;
            int tail = 0;
            level[s] = 0;
            queue[tail++] = s;
            while (head != tail) {
                int v = queue[head++];
                for (const auto& e : _g[v]) {
                    if (level[e.to] != -1 || e.cap == Cap(0)) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return true;
                    queue[tail++] = e.to;
                }
            }
            return level[t] != -1;
        };

        auto dfs = [&](auto&& self, int v, Cap up) -> Cap {
            if (v == s) return up;
            Cap result = Cap(0);
            const int current_level = level[v];
            auto& edges = _g[v];
            const int edge_count = int(edges.size());
            for (int& i = iter[v]; i < edge_count; i++) {
                auto& e = edges[i];
                if (level[e.to] + 1 != current_level) continue;
                auto& reverse = _g[e.to][e.rev];
                if (reverse.cap == Cap(0)) continue;
                Cap d = self(
                    self,
                    e.to,
                    std::min(up - result, reverse.cap)
                );
                if (d == Cap(0)) continue;
                e.cap += d;
                reverse.cap -= d;
                result += d;
                if (result == up) return result;
            }
            level[v] = _n;
            return result;
        };

        Cap flow = 0;
        while (flow < flow_limit && bfs()) {
            std::fill(iter, iter + _n, 0);
            flow += dfs(dfs, t, flow_limit - flow);
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) const {
        assert(0 <= s && s < _n);
        std::vector<bool> visited(_n, false);
        std::vector<int> queue(_n);
        int head = 0;
        int tail = 0;
        visited[s] = true;
        queue[tail++] = s;
        while (head != tail) {
            int v = queue[head++];
            for (const auto& e : _g[v]) {
                if (e.cap == Cap(0) || visited[e.to]) continue;
                visited[e.to] = true;
                queue[tail++] = e.to;
            }
        }
        return visited;
    }
};

}  // namespace flow
}  // namespace m1une

#endif  // M1UNE_FLOW_MAX_FLOW_HPP
