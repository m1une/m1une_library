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
            (2 * std::size_t(edge_count) + std::size_t(_n) - 1)
            / std::size_t(_n);
        for (auto& edges : _g) edges.reserve(average_degree);
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
        return max_flow(s, t, std::numeric_limits<Cap>::max());
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
                    if (e.cap == Cap(0) || level[e.to] != -1) continue;
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
            for (int& i = iter[v]; i < int(_g[v].size()); i++) {
                auto& e = _g[v][i];
                if (current_level <= level[e.to]) continue;
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
