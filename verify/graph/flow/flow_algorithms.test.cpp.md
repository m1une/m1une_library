---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/bounded_flow.hpp
    title: Bounded Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/bounded_min_cost_flow.hpp
    title: Bounded Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/flow.hpp
    title: Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/gomory_hu.hpp
    title: Gomory-Hu Tree
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/min_cost_flow.hpp
    title: Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/graph/flow/flow_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <limits>\n\
    #include <random>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/flow/flow.hpp\"\
    \n\n\n\n#line 1 \"graph/flow/bounded_flow.hpp\"\n\n\n\n#line 5 \"graph/flow/bounded_flow.hpp\"\
    \n#include <optional>\n#line 7 \"graph/flow/bounded_flow.hpp\"\n\n#line 1 \"graph/flow/max_flow.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 6 \"graph/flow/max_flow.hpp\"\n#include <cstddef>\n\
    #line 9 \"graph/flow/max_flow.hpp\"\n\nnamespace m1une {\nnamespace flow {\n\n\
    template <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int from;\n\
    \        int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n\
    \    struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \    };\n\n    struct Position {\n        int from;\n        int edge;\n    };\n\
    \n    int _n;\n    std::vector<Position> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n    Cap push_relabel(int s, int t) {\n        const std::size_t edge_count\
    \ = _pos.size();\n        const std::size_t source_degree = _g[s].size();\n  \
    \      const std::size_t sink_degree = _g[t].size();\n        const std::size_t\
    \ terminal_degree =\n            std::min(source_degree, sink_degree);\n     \
    \   const bool dense = edge_count >= 5 * std::size_t(_n);\n        const std::size_t\
    \ wide_threshold =\n            4 * (edge_count / std::size_t(_n) + 1);\n    \
    \    // Reverse input order defeats several ordering-sensitive hard cases,\n \
    \       // while forward order is substantially better on ordinary random\n  \
    \      // graphs with medium-width terminals.\n        const bool reverse_scan\
    \ =\n            terminal_degree > wide_threshold ||\n            (terminal_degree\
    \ <= 4 &&\n             (dense ||\n              (source_degree == 2 && sink_degree\
    \ == 2) ||\n              (terminal_degree == 1 &&\n               edge_count\
    \ >= 2 * std::size_t(_n))));\n        const int dead = 2 * _n;\n        const\
    \ int unreachable = _n + 1;\n        std::vector<Cap> excess(_n, Cap(0));\n  \
    \      std::vector<int> state(8 * std::size_t(_n) + 2);\n        int* height =\
    \ state.data();\n        int* height_count = height + _n;\n        int* current\
    \ = height_count + dead + 1;\n        int* queue = current + _n;\n        int*\
    \ next = queue + _n;\n        int* bucket_head = next + _n;\n        std::vector<char>\
    \ active(_n, false);\n        int highest = -1;\n        long long work = 0;\n\
    \        const long long arc_count =\n            2LL * static_cast<long long>(_pos.size());\n\
    \        const long long work_limit = std::max(\n            1LL,\n          \
    \  (reverse_scan ? 3 : 4) * arc_count + _n\n        );\n\n        auto activate\
    \ = [&](int v) {\n            if (v == s || v == t || active[v] || excess[v] ==\
    \ Cap(0) ||\n                height[v] >= dead) {\n                return;\n \
    \           }\n            active[v] = true;\n            next[v] = bucket_head[height[v]];\n\
    \            bucket_head[height[v]] = v;\n            highest = std::max(highest,\
    \ height[v]);\n        };\n\n        auto rebuild_buckets = [&]() {\n        \
    \    std::fill(bucket_head, bucket_head + dead + 1, -1);\n            std::fill(active.begin(),\
    \ active.end(), false);\n            highest = -1;\n            for (int v = 0;\
    \ v < _n; v++) activate(v);\n        };\n\n        auto global_relabel = [&]()\
    \ {\n            std::fill(height, height + _n, unreachable);\n            std::fill(height_count,\
    \ height_count + dead + 1, 0);\n            for (int v = 0; v < _n; v++) {\n \
    \               current[v] = reverse_scan ? int(_g[v].size()) - 1 : 0;\n     \
    \       }\n            int head = 0;\n            int tail = 0;\n            height[t]\
    \ = 0;\n            height[s] = _n;\n            queue[tail++] = t;\n        \
    \    while (head != tail) {\n                int v = queue[head++];\n        \
    \        for (const auto& e : _g[v]) {\n                    if (e.to == s || height[e.to]\
    \ != unreachable) continue;\n                    const auto& reverse = _g[e.to][e.rev];\n\
    \                    if (reverse.cap == Cap(0)) continue;\n                  \
    \  height[e.to] = height[v] + 1;\n                    queue[tail++] = e.to;\n\
    \                }\n            }\n            for (int v = 0; v < _n; v++) height_count[height[v]]++;\n\
    \            rebuild_buckets();\n            work = 0;\n        };\n\n       \
    \ auto gap = [&](int empty_height) {\n            for (int v = 0; v < _n; v++)\
    \ {\n                if (v == s || v == t || height[v] <= empty_height ||\n  \
    \                  height[v] >= _n) {\n                    continue;\n       \
    \         }\n                height_count[height[v]]--;\n                height[v]\
    \ = unreachable;\n                height_count[height[v]]++;\n               \
    \ current[v] = reverse_scan ? int(_g[v].size()) - 1 : 0;\n            }\n    \
    \        rebuild_buckets();\n        };\n\n        auto relabel = [&](int v) ->\
    \ bool {\n            int old_height = height[v];\n            int new_height\
    \ = dead;\n            work += int(_g[v].size());\n            for (const auto&\
    \ e : _g[v]) {\n                if (e.cap != Cap(0)) {\n                    new_height\
    \ = std::min(new_height, height[e.to] + 1);\n                }\n            }\n\
    \            height_count[old_height]--;\n            height[v] = std::min(new_height,\
    \ dead);\n            height_count[height[v]]++;\n            current[v] = reverse_scan\
    \ ? int(_g[v].size()) - 1 : 0;\n            if (old_height < _n && height_count[old_height]\
    \ == 0) {\n                gap(old_height);\n                return true;\n  \
    \          }\n            return false;\n        };\n\n        auto push = [&](int\
    \ v, InternalEdge& e) {\n            Cap sent = std::min(excess[v], e.cap);\n\
    \            bool was_zero = excess[e.to] == Cap(0);\n            e.cap -= sent;\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[v] -= sent;\n  \
    \          excess[e.to] += sent;\n            if (was_zero) activate(e.to);\n\
    \        };\n\n        auto discharge = [&]<bool Reverse>(int v) {\n         \
    \   while (excess[v] != Cap(0) && height[v] < dead) {\n                bool exhausted_edges;\n\
    \                if constexpr (Reverse) {\n                    exhausted_edges\
    \ = current[v] < 0;\n                } else {\n                    exhausted_edges\
    \ = current[v] == int(_g[v].size());\n                }\n                if (exhausted_edges)\
    \ {\n                    if (relabel(v)) return;\n                    continue;\n\
    \                }\n                auto& e = _g[v][current[v]];\n           \
    \     work++;\n                if (e.cap != Cap(0) && height[v] == height[e.to]\
    \ + 1) {\n                    push(v, e);\n                } else {\n        \
    \            if constexpr (Reverse) {\n                        current[v]--;\n\
    \                    } else {\n                        current[v]++;\n       \
    \             }\n                }\n            }\n            activate(v);\n\
    \        };\n\n        for (auto& e : _g[s]) {\n            if (e.to == s || e.cap\
    \ == Cap(0)) continue;\n            Cap sent = e.cap;\n            e.cap = Cap(0);\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[e.to] += sent;\n\
    \        }\n        global_relabel();\n\n        while (highest >= 0) {\n    \
    \        if (bucket_head[highest] == -1) {\n                highest--;\n     \
    \           continue;\n            }\n            int v = bucket_head[highest];\n\
    \            bucket_head[highest] = next[v];\n            if (!active[v] || height[v]\
    \ != highest) continue;\n            active[v] = false;\n            if (reverse_scan)\
    \ {\n                discharge.template operator()<true>(v);\n            } else\
    \ {\n                discharge.template operator()<false>(v);\n            }\n\
    \            if (work >= work_limit) global_relabel();\n        }\n        return\
    \ excess[t];\n    }\n\n    Cap dinic_phases(\n        int s,\n        int t,\n\
    \        Cap flow_limit,\n        int phase_limit,\n        bool& exhausted\n\
    \    ) {\n        std::vector<int> work(3 * std::size_t(_n));\n        int* level\
    \ = work.data();\n        int* iter = level + _n;\n        int* queue = iter +\
    \ _n;\n        auto bfs = [&]() -> bool {\n            std::fill(level, level\
    \ + _n, -1);\n            int head = 0;\n            int tail = 0;\n         \
    \   level[s] = 0;\n            queue[tail++] = s;\n            while (head !=\
    \ tail) {\n                int v = queue[head++];\n                const auto&\
    \ edges = _g[v];\n                for (const auto& e : edges) {\n            \
    \        if (level[e.to] != -1 || e.cap == Cap(0)) continue;\n               \
    \     level[e.to] = level[v] + 1;\n                    if (e.to == t) return true;\n\
    \                    queue[tail++] = e.to;\n                }\n            }\n\
    \            return false;\n        };\n\n        auto dfs = [&](auto&& self,\
    \ int v, Cap up) -> Cap {\n            if (v == s) return up;\n            Cap\
    \ result = Cap(0);\n            const int current_level = level[v];\n        \
    \    auto& edges = _g[v];\n            const int edge_count = int(edges.size());\n\
    \            for (int& i = iter[v]; i < edge_count; i++) {\n                auto&\
    \ e = edges[i];\n                if (level[e.to] + 1 != current_level) continue;\n\
    \                auto& reverse = _g[e.to][e.rev];\n                if (reverse.cap\
    \ == Cap(0)) continue;\n                Cap d = self(\n                    self,\n\
    \                    e.to,\n                    std::min(up - result, reverse.cap)\n\
    \                );\n                if (d == Cap(0)) continue;\n            \
    \    e.cap += d;\n                reverse.cap -= d;\n                result +=\
    \ d;\n                if (result == up) return result;\n            }\n      \
    \      level[v] = _n;\n            return result;\n        };\n\n        Cap flow\
    \ = Cap(0);\n        int phases = 0;\n        exhausted = false;\n        while\
    \ (flow < flow_limit && phases < phase_limit) {\n            if (!bfs()) {\n \
    \               exhausted = true;\n                break;\n            }\n   \
    \         std::fill(iter, iter + _n, 0);\n            flow += dfs(dfs, t, flow_limit\
    \ - flow);\n            phases++;\n        }\n        if (flow == flow_limit)\
    \ exhausted = true;\n        return flow;\n    }\n\n   public:\n    MaxFlow()\
    \ : MaxFlow(0) {}\n\n    explicit MaxFlow(int n) : _n(n), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int\
    \ edge_count() const {\n        return int(_pos.size());\n    }\n\n    void reserve_edges(int\
    \ edge_count) {\n        assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n\
    \        if (_n == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count)\
    \ < std::size_t(_n)) {\n            return;\n        }\n        const std::size_t\
    \ average_degree =\n            (3 * std::size_t(edge_count) + std::size_t(_n)\
    \ - 1)\n            / std::size_t(_n);\n        for (auto& edges : _g) edges.reserve(average_degree);\n\
    \    }\n\n    void reserve_edges(int edge_count, const std::vector<int>& degrees)\
    \ {\n        assert(0 <= edge_count);\n        assert(int(degrees.size()) == _n);\n\
    \        _pos.reserve(edge_count);\n        for (int v = 0; v < _n; v++) {\n \
    \           assert(0 <= degrees[v]);\n            _g[v].reserve(degrees[v]);\n\
    \        }\n    }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0\
    \ <= from && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0)\
    \ <= cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.push_back(Position{from, from_id});\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    int add_undirected_edge(int first, int second,\
    \ Cap cap) {\n        static_assert(std::numeric_limits<Cap>::is_signed);\n  \
    \      assert(0 <= first && first < _n);\n        assert(0 <= second && second\
    \ < _n);\n        assert(Cap(0) <= cap);\n        assert(cap <= std::numeric_limits<Cap>::max()\
    \ / Cap(2));\n        int id = int(_pos.size());\n        int first_id = int(_g[first].size());\n\
    \        int second_id = int(_g[second].size());\n        if (first == second)\
    \ second_id++;\n        _pos.push_back(Position{first, ~first_id});\n        _g[first].push_back(InternalEdge{second,\
    \ second_id, cap});\n        _g[second].push_back(InternalEdge{first, first_id,\
    \ cap});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n    \
    \    assert(0 <= i && i < int(_pos.size()));\n        const auto& position = _pos[i];\n\
    \        int from = position.from;\n        bool undirected = position.edge <\
    \ 0;\n        int idx = undirected ? ~position.edge : position.edge;\n       \
    \ const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        if (undirected) {\n            return Edge{\n                from,\n\
    \                e.to,\n                (e.cap + re.cap) / Cap(2),\n         \
    \       (re.cap - e.cap) / Cap(2)\n            };\n        }\n        return Edge{from,\
    \ e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge> edges() const\
    \ {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_cap);\n        auto& position = _pos[i];\n        int from = position.from;\n\
    \        bool undirected = position.edge < 0;\n        int idx = undirected ?\
    \ ~position.edge : position.edge;\n        auto& e = _g[from][idx];\n        auto&\
    \ re = _g[e.to][e.rev];\n        if (undirected) {\n            assert(new_cap\
    \ <= std::numeric_limits<Cap>::max() / Cap(2));\n            assert(-new_cap <=\
    \ new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_cap + new_flow;\n        } else {\n            assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_flow;\n        }\n    }\n\n    Cap max_flow(int s, int\
    \ t) {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n\
    \        assert(s != t);\n        bool exhausted;\n        const std::size_t edge_count\
    \ = _pos.size();\n        const std::size_t terminal_degree =\n            std::min(_g[s].size(),\
    \ _g[t].size());\n        const bool dense = edge_count >= 5 * std::size_t(_n);\n\
    \        const bool sparse_narrow_terminals =\n            edge_count >= std::size_t(_n)\
    \ &&\n            2 <= _g[s].size() && _g[s].size() <= 4 &&\n            2 <=\
    \ _g[t].size() && _g[t].size() <= 4;\n        // Only pay for a possible push-relabel\
    \ handoff on graph shapes where\n        // many Dinic phases are a realistic\
    \ risk.\n        const bool use_hybrid =\n            (dense || sparse_narrow_terminals)\
    \ &&\n            terminal_degree <= 4 * (edge_count / std::size_t(_n) + 1);\n\
    \        if (!use_hybrid) {\n            return max_flow(s, t, std::numeric_limits<Cap>::max());\n\
    \        }\n        int phase_limit = dense ? 4 : 8;\n        bool small_terminal_capacities\
    \ = true;\n        const int terminals[2] = {s, t};\n        for (int v : terminals)\
    \ {\n            for (const auto& e : _g[v]) {\n                if (Cap(2) < e.cap\
    \ ||\n                    Cap(2) < _g[e.to][e.rev].cap) {\n                  \
    \  small_terminal_capacities = false;\n                    break;\n          \
    \      }\n            }\n            if (!small_terminal_capacities) break;\n\
    \        }\n        if (small_terminal_capacities) {\n            return max_flow(s,\
    \ t, std::numeric_limits<Cap>::max());\n        }\n        Cap flow = dinic_phases(\n\
    \            s,\n            t,\n            std::numeric_limits<Cap>::max(),\n\
    \            phase_limit,\n            exhausted\n        );\n        if (!exhausted)\
    \ flow += push_relabel(s, t);\n        return flow;\n    }\n\n    Cap max_flow_push_relabel(int\
    \ s, int t) {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t <\
    \ _n);\n        assert(s != t);\n        return push_relabel(s, t);\n    }\n\n\
    \    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   std::vector<int> work(3 * std::size_t(_n));\n        int* level = work.data();\n\
    \        int* iter = level + _n;\n        int* queue = iter + _n;\n        auto\
    \ bfs = [&]() -> bool {\n            std::fill(level, level + _n, -1);\n     \
    \       int head = 0;\n            int tail = 0;\n            level[s] = 0;\n\
    \            queue[tail++] = s;\n            while (head != tail) {\n        \
    \        int v = queue[head++];\n                for (const auto& e : _g[v]) {\n\
    \                    if (level[e.to] != -1 || e.cap == Cap(0)) continue;\n   \
    \                 level[e.to] = level[v] + 1;\n                    if (e.to ==\
    \ t) return true;\n                    queue[tail++] = e.to;\n               \
    \ }\n            }\n            return level[t] != -1;\n        };\n\n       \
    \ auto dfs = [&](auto&& self, int v, Cap up) -> Cap {\n            if (v == s)\
    \ return up;\n            Cap result = Cap(0);\n            const int current_level\
    \ = level[v];\n            auto& edges = _g[v];\n            const int edge_count\
    \ = int(edges.size());\n            for (int& i = iter[v]; i < edge_count; i++)\
    \ {\n                auto& e = edges[i];\n                if (level[e.to] + 1\
    \ != current_level) continue;\n                auto& reverse = _g[e.to][e.rev];\n\
    \                if (reverse.cap == Cap(0)) continue;\n                Cap d =\
    \ self(\n                    self,\n                    e.to,\n              \
    \      std::min(up - result, reverse.cap)\n                );\n              \
    \  if (d == Cap(0)) continue;\n                e.cap += d;\n                reverse.cap\
    \ -= d;\n                result += d;\n                if (result == up) return\
    \ result;\n            }\n            level[v] = _n;\n            return result;\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter, iter + _n, 0);\n            flow += dfs(dfs,\
    \ t, flow_limit - flow);\n        }\n        return flow;\n    }\n\n    std::vector<bool>\
    \ min_cut(int s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool>\
    \ visited(_n, false);\n        std::vector<int> queue(_n);\n        int head =\
    \ 0;\n        int tail = 0;\n        visited[s] = true;\n        queue[tail++]\
    \ = s;\n        while (head != tail) {\n            int v = queue[head++];\n \
    \           for (const auto& e : _g[v]) {\n                if (e.cap == Cap(0)\
    \ || visited[e.to]) continue;\n                visited[e.to] = true;\n       \
    \         queue[tail++] = e.to;\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 9 \"graph/flow/bounded_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct BoundedFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap lower;\n\
    \        Cap upper;\n    };\n\n    struct ResultEdge {\n        int from;\n  \
    \      int to;\n        Cap lower;\n        Cap upper;\n        Cap flow;\n  \
    \  };\n\n    struct Result {\n        std::vector<ResultEdge> edges;\n       \
    \ std::vector<Cap> balance;\n\n        ResultEdge get_edge(int i) const {\n  \
    \          assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n\
    \        }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i\
    \ < int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\
    \n   private:\n    int _n;\n    std::vector<Edge> _edges;\n    std::vector<Cap>\
    \ _balance;\n\n   public:\n    BoundedFlow() : BoundedFlow(0) {}\n\n    explicit\
    \ BoundedFlow(int n) : _n(n), _balance(n, Cap(0)) {\n        assert(0 <= n);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    int edge_count()\
    \ const {\n        return int(_edges.size());\n    }\n\n    int add_edge(int from,\
    \ int to, Cap lower, Cap upper) {\n        assert(0 <= from && from < _n);\n \
    \       assert(0 <= to && to < _n);\n        assert(lower <= upper);\n       \
    \ int id = int(_edges.size());\n        _edges.push_back(Edge{from, to, lower,\
    \ upper});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n  \
    \      assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        return _edges;\n    }\n\
    \n    void set_balance(int v, Cap b) {\n        assert(0 <= v && v < _n);\n  \
    \      _balance[v] = b;\n    }\n\n    void add_balance(int v, Cap b) {\n     \
    \   assert(0 <= v && v < _n);\n        _balance[v] += b;\n    }\n\n    void add_supply(int\
    \ v, Cap supply) {\n        assert(Cap(0) <= supply);\n        add_balance(v,\
    \ supply);\n    }\n\n    void add_demand(int v, Cap demand) {\n        assert(Cap(0)\
    \ <= demand);\n        add_balance(v, -demand);\n    }\n\n    Cap balance(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _balance[v];\n\
    \    }\n\n    const std::vector<Cap>& balances() const {\n        return _balance;\n\
    \    }\n\n    std::optional<Result> feasible_flow() const {\n        return feasible_flow(_balance);\n\
    \    }\n\n    std::optional<Result> feasible_flow(const std::vector<Cap>& balance)\
    \ const {\n        assert(int(balance.size()) == _n);\n        int ss = _n, tt\
    \ = _n + 1;\n        MaxFlow<Cap> mf(_n + 2);\n        std::vector<int> edge_ids;\n\
    \        edge_ids.reserve(_edges.size());\n\n        std::vector<Cap> need = balance;\n\
    \        for (const auto& e : _edges) {\n            edge_ids.push_back(mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower));\n            need[e.from] -= e.lower;\n         \
    \   need[e.to] += e.lower;\n        }\n\n        Cap positive_sum = Cap(0), negative_sum\
    \ = Cap(0);\n        for (int v = 0; v < _n; v++) {\n            if (need[v] >\
    \ Cap(0)) {\n                positive_sum += need[v];\n                mf.add_edge(ss,\
    \ v, need[v]);\n            } else if (need[v] < Cap(0)) {\n                negative_sum\
    \ += -need[v];\n                mf.add_edge(v, tt, -need[v]);\n            }\n\
    \        }\n        if (positive_sum != negative_sum) return std::nullopt;\n \
    \       if (mf.max_flow(ss, tt) != positive_sum) return std::nullopt;\n\n    \
    \    Result result;\n        result.balance = balance;\n        result.edges.reserve(_edges.size());\n\
    \        for (int i = 0; i < int(_edges.size()); i++) {\n            auto used\
    \ = mf.get_edge(edge_ids[i]).flow;\n            const auto& e = _edges[i];\n \
    \           result.edges.push_back(ResultEdge{e.from, e.to, e.lower, e.upper,\
    \ e.lower + used});\n        }\n        return result;\n    }\n\n    std::optional<Result>\
    \ feasible_st_flow(int s, int t, Cap flow_value) const {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\
    \        std::vector<Cap> balance = _balance;\n        balance[s] += flow_value;\n\
    \        balance[t] -= flow_value;\n        return feasible_flow(balance);\n \
    \   }\n};\n\ntemplate <class Cap>\nusing BFlow = BoundedFlow<Cap>;\n\n}  // namespace\
    \ flow\n}  // namespace m1une\n\n\n#line 1 \"graph/flow/bounded_min_cost_flow.hpp\"\
    \n\n\n\n#line 7 \"graph/flow/bounded_min_cost_flow.hpp\"\n#include <cmath>\n#include\
    \ <functional>\n#line 11 \"graph/flow/bounded_min_cost_flow.hpp\"\n#include <queue>\n\
    #line 14 \"graph/flow/bounded_min_cost_flow.hpp\"\n\nnamespace m1une {\nnamespace\
    \ flow {\n\ntemplate <\n    class Cap,\n    class Cost,\n    class TotalCost =\
    \ Cost,\n    std::size_t PivotLimitFactor = 8\n>\nstruct BoundedMinCostFlow {\n\
    \    static_assert(std::numeric_limits<Cap>::is_integer);\n    static_assert(std::numeric_limits<Cap>::is_signed);\n\
    \    static_assert(std::numeric_limits<Cost>::is_specialized);\n    static_assert(std::numeric_limits<Cost>::is_signed);\n\
    \n    struct Edge {\n        int from;\n        int to;\n        Cap lower;\n\
    \        Cap upper;\n        Cost cost;\n    };\n\n    struct ResultEdge {\n \
    \       int from;\n        int to;\n        Cap lower;\n        Cap upper;\n \
    \       Cap flow;\n        Cost cost;\n    };\n\n    struct Result {\n       \
    \ std::vector<ResultEdge> edges;\n        std::vector<Cap> balance;\n        std::vector<Cost>\
    \ potential;\n        TotalCost cost;\n\n        ResultEdge get_edge(int i) const\
    \ {\n            assert(0 <= i && i < int(edges.size()));\n            return\
    \ edges[i];\n        }\n\n        Cap flow(int i) const {\n            assert(0\
    \ <= i && i < int(edges.size()));\n            return edges[i].flow;\n       \
    \ }\n    };\n\n   private:\n    struct NetworkEdge {\n        int to;\n      \
    \  Cap cap;\n        Cost cost;\n    };\n\n    struct NetworkSimplexSolver {\n\
    \        enum class Status {\n            optimal,\n            infeasible,\n\
    \            pivot_limit_reached,\n        };\n\n        struct Parent {\n   \
    \         int vertex;\n            int edge;\n            Cap up;\n          \
    \  Cap down;\n        };\n\n        int n;\n        std::vector<NetworkEdge> edges;\n\
    \        std::vector<Cap> excess;\n        std::vector<Cost> potential;\n    \
    \    std::size_t pivot_count = 0;\n\n        NetworkSimplexSolver(int vertex_count,\
    \ const std::vector<Cap>& balance)\n            : n(vertex_count), excess(balance)\
    \ {}\n\n        void reserve_edges(int edge_count) {\n            edges.reserve(2\
    \ * (edge_count + n));\n        }\n\n        int add_edge(int from, int to, Cap\
    \ lower, Cap upper, Cost cost) {\n            int id = int(edges.size()) / 2;\n\
    \            edges.push_back(NetworkEdge{to, upper - lower, cost});\n        \
    \    edges.push_back(NetworkEdge{from, Cap(0), -cost});\n            excess[from]\
    \ -= lower;\n            excess[to] += lower;\n            return id;\n      \
    \  }\n\n        Status solve(std::size_t pivot_limit) {\n            pivot_count\
    \ = 0;\n            const int original_edge_count = int(edges.size());\n     \
    \       potential.assign(n + 1, Cost(0));\n\n            Cost artificial_cost\
    \ = Cost(1);\n            for (int edge = 0; edge < original_edge_count; edge\
    \ += 2) {\n                artificial_cost += edges[edge].cost < Cost(0)\n   \
    \                 ? -edges[edge].cost : edges[edge].cost;\n            }\n\n \
    \           std::vector<Parent> parent(n);\n            edges.reserve(original_edge_count\
    \ + 2 * n);\n            for (int vertex = 0; vertex < n; vertex++) {\n      \
    \          if (excess[vertex] >= Cap(0)) {\n                    edges.push_back(NetworkEdge{n,\
    \ Cap(0), artificial_cost});\n                    edges.push_back(NetworkEdge{vertex,\
    \ excess[vertex], -artificial_cost});\n                    potential[vertex] =\
    \ -artificial_cost;\n                } else {\n                    edges.push_back(NetworkEdge{n,\
    \ -excess[vertex], -artificial_cost});\n                    edges.push_back(NetworkEdge{vertex,\
    \ Cap(0), artificial_cost});\n                    potential[vertex] = artificial_cost;\n\
    \                }\n                int edge = int(edges.size()) - 2;\n      \
    \          parent[vertex] = Parent{\n                    n, edge, edges[edge].cap,\
    \ edges[edge ^ 1].cap\n                };\n            }\n\n            std::vector<int>\
    \ depth(n + 1, 1);\n            depth[n] = 0;\n            std::vector<int> next(2\
    \ * (n + 1));\n            std::vector<int> previous(2 * (n + 1));\n         \
    \   auto connect = [&](int first, int second) {\n                next[first] =\
    \ second;\n                previous[second] = first;\n            };\n       \
    \     for (int vertex = 0; vertex <= n; vertex++) {\n                connect(2\
    \ * vertex, 2 * vertex + 1);\n            }\n            for (int vertex = 0;\
    \ vertex < n; vertex++) {\n                connect(2 * vertex + 1, next[2 * n]);\n\
    \                connect(2 * n, 2 * vertex);\n            }\n\n            auto\
    \ push_flow = [&](int entering_edge) {\n                const int first = edges[entering_edge\
    \ ^ 1].to;\n                const int second = edges[entering_edge].to;\n    \
    \            const Cost cycle_cost =\n                    edges[entering_edge].cost\n\
    \                    + potential[first] - potential[second];\n\n             \
    \   Cap amount = edges[entering_edge].cap;\n                bool leave_first_side\
    \ = true;\n                int leaving_vertex = second;\n\n                int\
    \ first_ancestor = first;\n                int second_ancestor = second;\n   \
    \             auto move_first_up = [&] {\n                    if (parent[first_ancestor].down\
    \ < amount) {\n                        amount = parent[first_ancestor].down;\n\
    \                        leaving_vertex = first_ancestor;\n                  \
    \      leave_first_side = true;\n                    }\n                    first_ancestor\
    \ = parent[first_ancestor].vertex;\n                };\n                auto move_second_up\
    \ = [&] {\n                    if (parent[second_ancestor].up <= amount) {\n \
    \                       amount = parent[second_ancestor].up;\n               \
    \         leaving_vertex = second_ancestor;\n                        leave_first_side\
    \ = false;\n                    }\n                    second_ancestor = parent[second_ancestor].vertex;\n\
    \                };\n                if (depth[first_ancestor] >= depth[second_ancestor])\
    \ {\n                    int difference = depth[first_ancestor] - depth[second_ancestor];\n\
    \                    for (int i = 0; i < difference; i++) move_first_up();\n \
    \               } else {\n                    int difference = depth[second_ancestor]\
    \ - depth[first_ancestor];\n                    for (int i = 0; i < difference;\
    \ i++) move_second_up();\n                }\n                while (first_ancestor\
    \ != second_ancestor) {\n                    move_first_up();\n              \
    \      move_second_up();\n                }\n                const int ancestor\
    \ = first_ancestor;\n\n                if (amount != Cap(0)) {\n             \
    \       int vertex = first;\n                    while (vertex != ancestor) {\n\
    \                        parent[vertex].up += amount;\n                      \
    \  parent[vertex].down -= amount;\n                        vertex = parent[vertex].vertex;\n\
    \                    }\n                    vertex = second;\n               \
    \     while (vertex != ancestor) {\n                        parent[vertex].up\
    \ -= amount;\n                        parent[vertex].down += amount;\n       \
    \                 vertex = parent[vertex].vertex;\n                    }\n   \
    \             }\n\n                int vertex = first;\n                int new_parent\
    \ = second;\n                std::pair<Cap, Cap> parent_capacities{\n        \
    \            edges[entering_edge].cap - amount,\n                    edges[entering_edge\
    \ ^ 1].cap + amount\n                };\n                Cost potential_difference\
    \ = -cycle_cost;\n                if (!leave_first_side) {\n                 \
    \   std::swap(vertex, new_parent);\n                    std::swap(parent_capacities.first,\
    \ parent_capacities.second);\n                    potential_difference = -potential_difference;\n\
    \                }\n                int parent_edge = entering_edge ^ (leave_first_side\
    \ ? 0 : 1);\n\n                while (new_parent != leaving_vertex) {\n      \
    \              int new_depth = depth[new_parent];\n                    int tour_index\
    \ = 2 * vertex;\n                    while (tour_index != 2 * vertex + 1) {\n\
    \                        if ((tour_index & 1) == 0) {\n                      \
    \      new_depth++;\n                            potential[tour_index / 2] +=\
    \ potential_difference;\n                            depth[tour_index / 2] = new_depth;\n\
    \                        } else {\n                            new_depth--;\n\
    \                        }\n                        tour_index = next[tour_index];\n\
    \                    }\n\n                    connect(previous[2 * vertex], next[2\
    \ * vertex + 1]);\n                    connect(2 * vertex + 1, next[2 * new_parent]);\n\
    \                    connect(2 * new_parent, 2 * vertex);\n\n                \
    \    std::swap(parent[vertex].edge, parent_edge);\n                    parent_edge\
    \ ^= 1;\n                    std::swap(parent[vertex].up, parent_capacities.first);\n\
    \                    std::swap(parent[vertex].down, parent_capacities.second);\n\
    \                    std::swap(parent_capacities.first, parent_capacities.second);\n\
    \n                    int old_parent = parent[vertex].vertex;\n              \
    \      parent[vertex].vertex = new_parent;\n                    new_parent = vertex;\n\
    \                    vertex = old_parent;\n                }\n               \
    \ edges[parent_edge].cap = parent_capacities.first;\n                edges[parent_edge\
    \ ^ 1].cap = parent_capacities.second;\n            };\n\n            bool pivot_limit_reached\
    \ = false;\n            auto pivot = [&](int entering_edge) {\n              \
    \  if (pivot_count == pivot_limit) {\n                    pivot_limit_reached\
    \ = true;\n                    return false;\n                }\n            \
    \    push_flow(entering_edge);\n                pivot_count++;\n             \
    \   return true;\n            };\n\n            const int candidate_limit = std::max(\n\
    \                int(0.2 * std::sqrt(double(original_edge_count))), 10\n     \
    \       );\n            const int minor_limit = std::max(candidate_limit / 10,\
    \ 3);\n            std::vector<int> candidates;\n            candidates.reserve(candidate_limit);\n\
    \n            auto minor_pivot = [&] {\n                Cost best_cost = Cost(0);\n\
    \                int best_edge = -1;\n                int index = 0;\n       \
    \         while (index < int(candidates.size())) {\n                    int edge\
    \ = candidates[index];\n                    if (edges[edge].cap == Cap(0)) {\n\
    \                        candidates[index] = candidates.back();\n            \
    \            candidates.pop_back();\n                        continue;\n     \
    \               }\n                    Cost reduced_cost =\n                 \
    \       edges[edge].cost\n                        + potential[edges[edge ^ 1].to]\n\
    \                        - potential[edges[edge].to];\n                    if\
    \ (reduced_cost >= Cost(0)) {\n                        candidates[index] = candidates.back();\n\
    \                        candidates.pop_back();\n                        continue;\n\
    \                    }\n                    if (reduced_cost < best_cost) {\n\
    \                        best_cost = reduced_cost;\n                        best_edge\
    \ = edge;\n                    }\n                    index++;\n             \
    \   }\n                if (best_edge == -1) return false;\n                return\
    \ pivot(best_edge);\n            };\n\n            int edge = 0;\n           \
    \ while (true) {\n                for (int iteration = 0; iteration < minor_limit;\
    \ iteration++) {\n                    if (!minor_pivot()) break;\n           \
    \     }\n                if (pivot_limit_reached) return Status::pivot_limit_reached;\n\
    \n                Cost best_cost = Cost(0);\n                int best_edge = -1;\n\
    \                candidates.clear();\n                for (int scanned = 0; scanned\
    \ < int(edges.size()); scanned++) {\n                    if (edges[edge].cap !=\
    \ Cap(0)) {\n                        Cost reduced_cost =\n                   \
    \         edges[edge].cost\n                            + potential[edges[edge\
    \ ^ 1].to]\n                            - potential[edges[edge].to];\n       \
    \                 if (reduced_cost < Cost(0)) {\n                            if\
    \ (reduced_cost < best_cost) {\n                                best_cost = reduced_cost;\n\
    \                                best_edge = edge;\n                         \
    \   }\n                            candidates.push_back(edge);\n             \
    \               if (int(candidates.size()) == candidate_limit) break;\n      \
    \                  }\n                    }\n                    edge++;\n   \
    \                 if (edge == int(edges.size())) edge = 0;\n                }\n\
    \                if (candidates.empty()) break;\n                if (!pivot(best_edge))\
    \ return Status::pivot_limit_reached;\n            }\n\n            for (int vertex\
    \ = 0; vertex < n; vertex++) {\n                edges[parent[vertex].edge].cap\
    \ = parent[vertex].up;\n                edges[parent[vertex].edge ^ 1].cap = parent[vertex].down;\n\
    \            }\n\n            bool feasible = true;\n            for (int vertex\
    \ = 0; vertex < n; vertex++) {\n                int artificial_edge = original_edge_count\
    \ + 2 * vertex;\n                if (\n                    (excess[vertex] >=\
    \ Cap(0)\n                        && edges[artificial_edge ^ 1].cap != Cap(0))\n\
    \                    || (excess[vertex] < Cap(0)\n                        && edges[artificial_edge].cap\
    \ != Cap(0))\n                ) {\n                    feasible = false;\n   \
    \                 break;\n                }\n            }\n            potential.pop_back();\n\
    \            return feasible ? Status::optimal : Status::infeasible;\n       \
    \ }\n\n        Cap edge_flow(int edge_id, Cap lower) const {\n            return\
    \ lower + edges[2 * edge_id + 1].cap;\n        }\n    };\n\n    struct ScalingEdge\
    \ {\n        int to;\n        int reverse;\n        Cap cap;\n        Cap flow;\n\
    \        Cost cost;\n    };\n\n    struct ScalingSolver {\n        int n;\n  \
    \      std::vector<std::vector<ScalingEdge>> graph;\n        std::vector<std::pair<int,\
    \ int>> positions;\n        std::vector<Cap> excess;\n        std::vector<Cost>\
    \ potential;\n        std::vector<Cost> distance;\n        std::vector<int> parent_vertex;\n\
    \        std::vector<int> parent_edge;\n        std::vector<int> excess_vertices;\n\
    \        std::vector<int> deficit_vertices;\n        Cost farthest = Cost(0);\n\
    \n        ScalingSolver(int vertex_count, const std::vector<Cap>& balance)\n \
    \           : n(vertex_count), graph(vertex_count), excess(balance),\n       \
    \       potential(vertex_count, Cost(0)) {}\n\n        void reserve_edges(int\
    \ edge_count) {\n            positions.reserve(edge_count);\n        }\n\n   \
    \     int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n    \
    \        int id = int(positions.size());\n            int from_edge = int(graph[from].size());\n\
    \            int to_edge = int(graph[to].size());\n            if (from == to)\
    \ to_edge++;\n            positions.emplace_back(from, from_edge);\n         \
    \   graph[from].push_back(ScalingEdge{\n                to, to_edge, upper, Cap(0),\
    \ cost\n            });\n            graph[to].push_back(ScalingEdge{\n      \
    \          from, from_edge, -lower, Cap(0), -cost\n            });\n         \
    \   return id;\n        }\n\n        Cap residual_capacity(int from, int edge_id)\
    \ const {\n            const auto& edge = graph[from][edge_id];\n            return\
    \ edge.cap - edge.flow;\n        }\n\n        Cost residual_cost(int from, const\
    \ ScalingEdge& edge) const {\n            return edge.cost + potential[from] -\
    \ potential[edge.to];\n        }\n\n        void push(int from, int edge_id, Cap\
    \ amount) {\n            auto& edge = graph[from][edge_id];\n            edge.flow\
    \ += amount;\n            graph[edge.to][edge.reverse].flow -= amount;\n     \
    \   }\n\n        void saturate_negative(Cap delta) {\n            excess_vertices.clear();\n\
    \            deficit_vertices.clear();\n            for (int from = 0; from <\
    \ n; from++) {\n                for (\n                    int edge_id = 0;\n\
    \                    edge_id < int(graph[from].size());\n                    edge_id++\n\
    \                ) {\n                    const auto& edge = graph[from][edge_id];\n\
    \                    Cap residual = edge.cap - edge.flow;\n                  \
    \  residual -= residual % delta;\n                    if (\n                 \
    \       residual_cost(from, edge) < Cost(0)\n                        || residual\
    \ < Cap(0)\n                    ) {\n                        int to = edge.to;\n\
    \                        push(from, edge_id, residual);\n                    \
    \    excess[from] -= residual;\n                        excess[to] += residual;\n\
    \                    }\n                }\n            }\n            for (int\
    \ vertex = 0; vertex < n; vertex++) {\n                if (excess[vertex] > Cap(0))\
    \ {\n                    excess_vertices.push_back(vertex);\n                }\
    \ else if (excess[vertex] < Cap(0)) {\n                    deficit_vertices.push_back(vertex);\n\
    \                }\n            }\n        }\n\n        bool dual(Cap delta) {\n\
    \            excess_vertices.erase(\n                std::remove_if(\n       \
    \             excess_vertices.begin(), excess_vertices.end(),\n              \
    \      [&](int vertex) { return excess[vertex] < delta; }\n                ),\n\
    \                excess_vertices.end()\n            );\n            deficit_vertices.erase(\n\
    \                std::remove_if(\n                    deficit_vertices.begin(),\
    \ deficit_vertices.end(),\n                    [&](int vertex) { return excess[vertex]\
    \ > -delta; }\n                ),\n                deficit_vertices.end()\n  \
    \          );\n\n            const Cost unreachable = std::numeric_limits<Cost>::max();\n\
    \            distance.assign(n, unreachable);\n            parent_vertex.assign(n,\
    \ -1);\n            parent_edge.assign(n, -1);\n            using QueueEntry =\
    \ std::pair<Cost, int>;\n            std::priority_queue<\n                QueueEntry,\n\
    \                std::vector<QueueEntry>,\n                std::greater<QueueEntry>\n\
    \            > queue;\n            for (int vertex : excess_vertices) {\n    \
    \            distance[vertex] = Cost(0);\n                queue.emplace(Cost(0),\
    \ vertex);\n            }\n\n            farthest = Cost(0);\n            int\
    \ reached_deficits = 0;\n            while (!queue.empty()) {\n              \
    \  auto [current_distance, from] = queue.top();\n                queue.pop();\n\
    \                if (distance[from] != current_distance) continue;\n         \
    \       farthest = current_distance;\n                if (excess[from] <= -delta)\
    \ reached_deficits++;\n                if (reached_deficits >= int(deficit_vertices.size()))\
    \ break;\n\n                for (\n                    int edge_id = 0;\n    \
    \                edge_id < int(graph[from].size());\n                    edge_id++\n\
    \                ) {\n                    const auto& edge = graph[from][edge_id];\n\
    \                    if (edge.cap - edge.flow < delta) continue;\n           \
    \         Cost next_distance =\n                        current_distance + residual_cost(from,\
    \ edge);\n                    if (next_distance >= distance[edge.to]) continue;\n\
    \                    distance[edge.to] = next_distance;\n                    parent_vertex[edge.to]\
    \ = from;\n                    parent_edge[edge.to] = edge_id;\n             \
    \       queue.emplace(next_distance, edge.to);\n                }\n          \
    \  }\n\n            for (int vertex = 0; vertex < n; vertex++) {\n           \
    \     potential[vertex] += std::min(distance[vertex], farthest);\n           \
    \ }\n            return reached_deficits > 0;\n        }\n\n        void primal(Cap\
    \ delta) {\n            for (int sink : deficit_vertices) {\n                if\
    \ (distance[sink] > farthest) continue;\n                Cap amount = -excess[sink];\n\
    \                int root = sink;\n                while (parent_edge[root] !=\
    \ -1) {\n                    int from = parent_vertex[root];\n               \
    \     amount = std::min(\n                        amount,\n                  \
    \      residual_capacity(from, parent_edge[root])\n                    );\n  \
    \                  root = from;\n                }\n                amount = std::min(amount,\
    \ excess[root]);\n                amount -= amount % delta;\n                if\
    \ (amount <= Cap(0)) continue;\n\n                int vertex = sink;\n       \
    \         while (parent_edge[vertex] != -1) {\n                    int from =\
    \ parent_vertex[vertex];\n                    int edge_id = parent_edge[vertex];\n\
    \                    push(from, edge_id, amount);\n                    if (residual_capacity(from,\
    \ edge_id) == Cap(0)) {\n                        parent_edge[vertex] = -1;\n \
    \                   }\n                    vertex = from;\n                }\n\
    \                excess[sink] += amount;\n                excess[root] -= amount;\n\
    \            }\n        }\n\n        bool solve() {\n            Cap scale_bound\
    \ = Cap(1);\n            for (Cap value : excess) {\n                scale_bound\
    \ = std::max(scale_bound, value);\n                scale_bound = std::max(scale_bound,\
    \ -value);\n            }\n            for (const auto& edges : graph) {\n   \
    \             for (const auto& edge : edges) {\n                    Cap residual\
    \ = edge.cap - edge.flow;\n                    scale_bound = std::max(scale_bound,\
    \ residual);\n                    scale_bound = std::max(scale_bound, -residual);\n\
    \                }\n            }\n\n            Cap delta = Cap(1);\n       \
    \     while (delta <= scale_bound / Cap(2)) delta *= Cap(2);\n            while\
    \ (true) {\n                saturate_negative(delta);\n                while (dual(delta))\
    \ primal(delta);\n                if (delta == Cap(1)) break;\n              \
    \  delta /= Cap(2);\n            }\n            return excess_vertices.empty()\
    \ && deficit_vertices.empty();\n        }\n\n        Cap edge_flow(int edge_id,\
    \ Cap) const {\n            auto [from, index] = positions[edge_id];\n       \
    \     return graph[from][index].flow;\n        }\n    };\n\n    int _n;\n    std::vector<Edge>\
    \ _edges;\n    std::vector<Cap> _balance;\n\n    template <class Solver>\n   \
    \ Result make_result(\n        const std::vector<Cap>& balance,\n        const\
    \ Solver& solver,\n        std::vector<Cost> potential\n    ) const {\n      \
    \  Result result;\n        result.balance = balance;\n        result.cost = TotalCost(0);\n\
    \        result.edges.reserve(_edges.size());\n        for (int i = 0; i < int(_edges.size());\
    \ i++) {\n            const auto& edge = _edges[i];\n            Cap flow = solver.edge_flow(i,\
    \ edge.lower);\n            result.cost += TotalCost(flow) * TotalCost(edge.cost);\n\
    \            result.edges.push_back(ResultEdge{\n                edge.from,\n\
    \                edge.to,\n                edge.lower,\n                edge.upper,\n\
    \                flow,\n                edge.cost\n            });\n        }\n\
    \        result.potential = std::move(potential);\n        return result;\n  \
    \  }\n\n    std::vector<Cost> residual_potential(\n        const std::vector<ResultEdge>&\
    \ edges\n    ) const {\n        std::vector<Cost> potential(_n, Cost(0));\n  \
    \      bool updated = false;\n        for (int iteration = 0; iteration < _n;\
    \ iteration++) {\n            updated = false;\n            for (const ResultEdge&\
    \ edge : edges) {\n                if (\n                    edge.flow < edge.upper\n\
    \                    && potential[edge.to] > potential[edge.from] + edge.cost\n\
    \                ) {\n                    potential[edge.to] = potential[edge.from]\
    \ + edge.cost;\n                    updated = true;\n                }\n     \
    \           if (\n                    edge.lower < edge.flow\n               \
    \     && potential[edge.from] > potential[edge.to] - edge.cost\n             \
    \   ) {\n                    potential[edge.from] = potential[edge.to] - edge.cost;\n\
    \                    updated = true;\n                }\n            }\n     \
    \       if (!updated) break;\n        }\n        assert(!updated);\n        return\
    \ potential;\n    }\n\n    std::optional<Result> polynomial_min_cost_flow_impl(\n\
    \        const std::vector<Cap>& balance\n    ) const {\n        ScalingSolver\
    \ solver(_n, balance);\n        solver.reserve_edges(int(_edges.size()));\n  \
    \      for (const auto& edge : _edges) {\n            solver.add_edge(\n     \
    \           edge.from,\n                edge.to,\n                edge.lower,\n\
    \                edge.upper,\n                edge.cost\n            );\n    \
    \    }\n        if (!solver.solve()) return std::nullopt;\n\n        Result result\
    \ = make_result(balance, solver, {});\n        result.potential = residual_potential(result.edges);\n\
    \        return result;\n    }\n\n   public:\n    BoundedMinCostFlow() : BoundedMinCostFlow(0)\
    \ {}\n\n    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {\n\
    \        assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    int edge_count() const {\n        return int(_edges.size());\n \
    \   }\n\n    void reserve_edges(int edge_count) {\n        assert(0 <= edge_count);\n\
    \        _edges.reserve(edge_count);\n    }\n\n    int add_edge(int from, int\
    \ to, Cap lower, Cap upper, Cost cost) {\n        assert(0 <= from && from < _n);\n\
    \        assert(0 <= to && to < _n);\n        assert(lower <= upper);\n      \
    \  int id = int(_edges.size());\n        _edges.push_back(Edge{from, to, lower,\
    \ upper, cost});\n        return id;\n    }\n\n    Edge get_edge(int i) const\
    \ {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges() const {\n        return _edges;\n    }\n\
    \n    void set_balance(int v, Cap b) {\n        assert(0 <= v && v < _n);\n  \
    \      _balance[v] = b;\n    }\n\n    void add_balance(int v, Cap b) {\n     \
    \   assert(0 <= v && v < _n);\n        _balance[v] += b;\n    }\n\n    void add_supply(int\
    \ v, Cap supply) {\n        assert(Cap(0) <= supply);\n        add_balance(v,\
    \ supply);\n    }\n\n    void add_demand(int v, Cap demand) {\n        assert(Cap(0)\
    \ <= demand);\n        add_balance(v, -demand);\n    }\n\n    Cap balance(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _balance[v];\n\
    \    }\n\n    const std::vector<Cap>& balances() const {\n        return _balance;\n\
    \    }\n\n    std::optional<Result> min_cost_flow() const {\n        return min_cost_flow(_balance);\n\
    \    }\n\n    std::optional<Result> min_cost_flow(const std::vector<Cap>& balance)\
    \ const {\n        assert(int(balance.size()) == _n);\n        Cap balance_sum\
    \ = Cap(0);\n        for (Cap value : balance) balance_sum += value;\n       \
    \ if (balance_sum != Cap(0)) return std::nullopt;\n\n        NetworkSimplexSolver\
    \ solver(_n, balance);\n        solver.reserve_edges(int(_edges.size()));\n  \
    \      for (const auto& edge : _edges) {\n            solver.add_edge(edge.from,\
    \ edge.to, edge.lower, edge.upper, edge.cost);\n        }\n        const std::size_t\
    \ graph_size =\n            std::size_t(_n) + _edges.size() + 1;\n        std::size_t\
    \ pivot_limit = 0;\n        if constexpr (PivotLimitFactor != 0) {\n         \
    \   const std::size_t maximum =\n                std::numeric_limits<std::size_t>::max();\n\
    \            pivot_limit = graph_size > maximum / PivotLimitFactor\n         \
    \       ? maximum : PivotLimitFactor * graph_size;\n        }\n        auto status\
    \ = solver.solve(pivot_limit);\n        if (status == NetworkSimplexSolver::Status::infeasible)\
    \ {\n            return std::nullopt;\n        }\n        if (status == NetworkSimplexSolver::Status::pivot_limit_reached)\
    \ {\n            return polynomial_min_cost_flow_impl(balance);\n        }\n \
    \       return make_result(balance, solver, std::move(solver.potential));\n  \
    \  }\n\n    std::optional<Result> min_cost_flow_polynomial() const {\n       \
    \ return min_cost_flow_polynomial(_balance);\n    }\n\n    std::optional<Result>\
    \ min_cost_flow_polynomial(\n        const std::vector<Cap>& balance\n    ) const\
    \ {\n        assert(int(balance.size()) == _n);\n        Cap balance_sum = Cap(0);\n\
    \        for (Cap value : balance) balance_sum += value;\n        if (balance_sum\
    \ != Cap(0)) return std::nullopt;\n        return polynomial_min_cost_flow_impl(balance);\n\
    \    }\n\n    std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value)\
    \ const {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n\
    \        assert(s != t);\n        std::vector<Cap> balance = _balance;\n     \
    \   balance[s] += flow_value;\n        balance[t] -= flow_value;\n        return\
    \ min_cost_flow(balance);\n    }\n\n    std::optional<Result> min_cost_st_flow_polynomial(\n\
    \        int s,\n        int t,\n        Cap flow_value\n    ) const {\n     \
    \   assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s\
    \ != t);\n        std::vector<Cap> balance = _balance;\n        balance[s] +=\
    \ flow_value;\n        balance[t] -= flow_value;\n        return min_cost_flow_polynomial(balance);\n\
    \    }\n};\n\ntemplate <\n    class Cap,\n    class Cost,\n    class TotalCost\
    \ = Cost,\n    std::size_t PivotLimitFactor = 8\n>\nusing BMinCostFlow = BoundedMinCostFlow<\n\
    \    Cap,\n    Cost,\n    TotalCost,\n    PivotLimitFactor\n>;\n\n}  // namespace\
    \ flow\n}  // namespace m1une\n\n\n#line 1 \"graph/flow/gomory_hu.hpp\"\n\n\n\n\
    #line 9 \"graph/flow/gomory_hu.hpp\"\n\nnamespace m1une {\nnamespace flow {\n\n\
    template <class Cap>\nstruct GomoryHu {\n    struct Edge {\n        int u;\n \
    \       int v;\n        Cap cap;\n    };\n\n   private:\n    struct FlowEdge {\n\
    \        int to;\n        int rev;\n        Cap cap;\n        Cap initial_cap;\n\
    \    };\n\n    int _n;\n    bool _built = false;\n    std::vector<Edge> _edges;\n\
    \    std::vector<Edge> _tree_edges;\n    std::vector<int> _parent;\n    std::vector<Cap>\
    \ _cut_value;\n    std::vector<std::vector<std::pair<int, Cap>>> _tree;\n    std::vector<std::vector<int>>\
    \ _up;\n    std::vector<std::vector<Cap>> _minimum;\n    std::vector<int> _depth;\n\
    \n    std::vector<std::vector<FlowEdge>> _graph;\n    std::vector<Cap> _excess;\n\
    \    std::vector<int> _height;\n    std::vector<int> _height_count;\n    std::vector<int>\
    \ _current;\n    std::vector<bool> _active;\n    std::vector<std::vector<int>>\
    \ _buckets;\n    std::vector<int> _queue;\n    int _highest;\n    long long _work;\n\
    \    long long _work_limit;\n\n    void add_flow_edge(int u, int v, Cap cap) {\n\
    \        if (u == v || cap == Cap(0)) return;\n        int ui = int(_graph[u].size());\n\
    \        int vi = int(_graph[v].size());\n        _graph[u].push_back(FlowEdge{v,\
    \ vi, cap, cap});\n        _graph[v].push_back(FlowEdge{u, ui, cap, cap});\n \
    \   }\n\n    void reset_flow() {\n        for (auto& edges : _graph) {\n     \
    \       for (auto& edge : edges) edge.cap = edge.initial_cap;\n        }\n   \
    \ }\n\n    void activate(int v, int s, int t) {\n        int dead = 2 * _n;\n\
    \        if (v == s || v == t || _active[v] || _excess[v] == Cap(0) || _height[v]\
    \ >= dead) return;\n        _active[v] = true;\n        _buckets[_height[v]].push_back(v);\n\
    \        _highest = std::max(_highest, _height[v]);\n    }\n\n    void rebuild_buckets(int\
    \ s, int t) {\n        for (auto& bucket : _buckets) bucket.clear();\n       \
    \ std::fill(_active.begin(), _active.end(), false);\n        _highest = -1;\n\
    \        for (int v = 0; v < _n; v++) activate(v, s, t);\n    }\n\n    void global_relabel(int\
    \ s, int t) {\n        int dead = 2 * _n;\n        int unreachable = _n + 1;\n\
    \        std::fill(_height.begin(), _height.end(), unreachable);\n        std::fill(_height_count.begin(),\
    \ _height_count.end(), 0);\n        std::fill(_current.begin(), _current.end(),\
    \ 0);\n\n        int head = 0;\n        int tail = 0;\n        _height[t] = 0;\n\
    \        _height[s] = _n;\n        _queue[tail++] = t;\n        while (head <\
    \ tail) {\n            int v = _queue[head++];\n            for (const auto& edge\
    \ : _graph[v]) {\n                const FlowEdge& reverse = _graph[edge.to][edge.rev];\n\
    \                if (reverse.cap == Cap(0) || _height[edge.to] != unreachable)\
    \ continue;\n                _height[edge.to] = _height[v] + 1;\n            \
    \    _queue[tail++] = edge.to;\n            }\n        }\n        for (int v =\
    \ 0; v < _n; v++) {\n            _height[v] = std::min(_height[v], dead);\n  \
    \          _height_count[_height[v]]++;\n        }\n        rebuild_buckets(s,\
    \ t);\n        _work = 0;\n    }\n\n    void push(int v, FlowEdge& edge, int s,\
    \ int t) {\n        if (edge.cap == Cap(0) || _height[v] != _height[edge.to] +\
    \ 1) return;\n        Cap sent = std::min(_excess[v], edge.cap);\n        if (sent\
    \ == Cap(0)) return;\n        bool was_zero = _excess[edge.to] == Cap(0);\n  \
    \      edge.cap -= sent;\n        _graph[edge.to][edge.rev].cap += sent;\n   \
    \     _excess[v] -= sent;\n        _excess[edge.to] += sent;\n        if (was_zero)\
    \ activate(edge.to, s, t);\n    }\n\n    void gap(int height, int s, int t) {\n\
    \        int unreachable = _n + 1;\n        for (int v = 0; v < _n; v++) {\n \
    \           if (v == s || v == t || _height[v] <= height || _height[v] >= _n)\
    \ continue;\n            _height_count[_height[v]]--;\n            _height[v]\
    \ = unreachable;\n            _height_count[_height[v]]++;\n            _current[v]\
    \ = 0;\n        }\n        rebuild_buckets(s, t);\n    }\n\n    bool relabel(int\
    \ v, int s, int t) {\n        int dead = 2 * _n;\n        int old_height = _height[v];\n\
    \        int new_height = dead;\n        _work += int(_graph[v].size());\n   \
    \     for (const auto& edge : _graph[v]) {\n            if (edge.cap != Cap(0))\
    \ new_height = std::min(new_height, _height[edge.to] + 1);\n        }\n      \
    \  _height_count[old_height]--;\n        _height[v] = std::min(new_height, dead);\n\
    \        _height_count[_height[v]]++;\n        _current[v] = 0;\n        if (old_height\
    \ < _n && _height_count[old_height] == 0) {\n            gap(old_height, s, t);\n\
    \            return true;\n        }\n        return false;\n    }\n\n    void\
    \ discharge(int v, int s, int t) {\n        while (_excess[v] != Cap(0) && _height[v]\
    \ < 2 * _n) {\n            if (_current[v] == int(_graph[v].size())) {\n     \
    \           if (relabel(v, s, t)) return;\n                continue;\n       \
    \     }\n            FlowEdge& edge = _graph[v][_current[v]];\n            _work++;\n\
    \            if (edge.cap != Cap(0) && _height[v] == _height[edge.to] + 1) {\n\
    \                push(v, edge, s, t);\n            } else {\n                _current[v]++;\n\
    \            }\n        }\n        activate(v, s, t);\n    }\n\n    Cap max_flow(int\
    \ s, int t) {\n        reset_flow();\n        std::fill(_excess.begin(), _excess.end(),\
    \ Cap(0));\n        for (auto& edge : _graph[s]) {\n            Cap sent = edge.cap;\n\
    \            if (sent == Cap(0)) continue;\n            edge.cap = Cap(0);\n \
    \           _graph[edge.to][edge.rev].cap += sent;\n            _excess[edge.to]\
    \ += sent;\n        }\n        global_relabel(s, t);\n\n        while (_highest\
    \ >= 0) {\n            if (_buckets[_highest].empty()) {\n                _highest--;\n\
    \                continue;\n            }\n            int v = _buckets[_highest].back();\n\
    \            _buckets[_highest].pop_back();\n            if (!_active[v] || _height[v]\
    \ != _highest) continue;\n            _active[v] = false;\n            discharge(v,\
    \ s, t);\n            if (_work >= _work_limit) global_relabel(s, t);\n      \
    \  }\n        return _excess[t];\n    }\n\n    std::vector<bool> source_side(int\
    \ s) {\n        std::vector<bool> visited(_n, false);\n        int head = 0;\n\
    \        int tail = 0;\n        visited[s] = true;\n        _queue[tail++] = s;\n\
    \        while (head < tail) {\n            int v = _queue[head++];\n        \
    \    for (const auto& edge : _graph[v]) {\n                if (edge.cap == Cap(0)\
    \ || visited[edge.to]) continue;\n                visited[edge.to] = true;\n \
    \               _queue[tail++] = edge.to;\n            }\n        }\n        return\
    \ visited;\n    }\n\n    void build_query_table() {\n        int log = 1;\n  \
    \      while ((1LL << log) <= std::max(1, _n)) log++;\n        const Cap infinity\
    \ = std::numeric_limits<Cap>::max();\n        _up.assign(log, std::vector<int>(_n,\
    \ 0));\n        _minimum.assign(log, std::vector<Cap>(_n, infinity));\n      \
    \  _depth.assign(_n, 0);\n        if (_n == 0) return;\n\n        std::vector<int>\
    \ order;\n        order.reserve(_n);\n        order.push_back(0);\n        for\
    \ (int i = 0; i < int(order.size()); i++) {\n            int v = order[i];\n \
    \           for (auto [to, cap] : _tree[v]) {\n                if (to == _up[0][v]\
    \ && v != 0) continue;\n                _up[0][to] = v;\n                _minimum[0][to]\
    \ = cap;\n                _depth[to] = _depth[v] + 1;\n                order.push_back(to);\n\
    \            }\n        }\n        for (int k = 1; k < log; k++) {\n         \
    \   for (int v = 0; v < _n; v++) {\n                int middle = _up[k - 1][v];\n\
    \                _up[k][v] = _up[k - 1][middle];\n                _minimum[k][v]\
    \ = std::min(_minimum[k - 1][v], _minimum[k - 1][middle]);\n            }\n  \
    \      }\n    }\n\n   public:\n    GomoryHu() : GomoryHu(0) {}\n\n    explicit\
    \ GomoryHu(int n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int u, int v, Cap cap)\
    \ {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n  \
    \      assert(Cap(0) <= cap);\n        _built = false;\n        int id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, cap});\n        return id;\n    }\n\n   \
    \ void build() {\n        std::vector<Edge> flow_edges;\n        flow_edges.reserve(_edges.size());\n\
    \        for (auto edge : _edges) {\n            if (edge.u == edge.v || edge.cap\
    \ == Cap(0)) continue;\n            if (edge.u > edge.v) std::swap(edge.u, edge.v);\n\
    \            flow_edges.push_back(edge);\n        }\n        std::sort(flow_edges.begin(),\
    \ flow_edges.end(), [](const Edge& lhs, const Edge& rhs) {\n            return\
    \ std::pair<int, int>(lhs.u, lhs.v) < std::pair<int, int>(rhs.u, rhs.v);\n   \
    \     });\n        int unique_edges = 0;\n        for (const auto& edge : flow_edges)\
    \ {\n            if (unique_edges > 0 && flow_edges[unique_edges - 1].u == edge.u\
    \ &&\n                flow_edges[unique_edges - 1].v == edge.v) {\n          \
    \      flow_edges[unique_edges - 1].cap += edge.cap;\n            } else {\n \
    \               flow_edges[unique_edges++] = edge;\n            }\n        }\n\
    \        flow_edges.resize(unique_edges);\n\n        _graph.assign(_n, {});\n\
    \        std::vector<int> degree(_n, 0);\n        for (const auto& edge : flow_edges)\
    \ {\n            degree[edge.u]++;\n            degree[edge.v]++;\n        }\n\
    \        for (int v = 0; v < _n; v++) _graph[v].reserve(degree[v]);\n        for\
    \ (const auto& edge : flow_edges) add_flow_edge(edge.u, edge.v, edge.cap);\n \
    \       _excess.resize(_n);\n        _height.resize(_n);\n        _height_count.resize(2\
    \ * _n + 1);\n        _current.resize(_n);\n        _active.resize(_n);\n    \
    \    _buckets.resize(2 * _n + 1);\n        _queue.resize(_n);\n        long long\
    \ arc_count = 0;\n        for (const auto& edges : _graph) arc_count += int(edges.size());\n\
    \        _work_limit = std::max(1LL, 4 * arc_count + _n);\n\n        _parent.assign(_n,\
    \ 0);\n        _cut_value.assign(_n, std::numeric_limits<Cap>::max());\n     \
    \   for (int s = 1; s < _n; s++) {\n            int t = _parent[s];\n        \
    \    Cap flow = max_flow(s, t);\n            std::vector<bool> cut = source_side(s);\n\
    \            for (int v = s + 1; v < _n; v++) {\n                if (_parent[v]\
    \ == t && cut[v]) _parent[v] = s;\n            }\n            if (cut[_parent[t]])\
    \ {\n                _parent[s] = _parent[t];\n                _parent[t] = s;\n\
    \                _cut_value[s] = _cut_value[t];\n                _cut_value[t]\
    \ = flow;\n            } else {\n                _cut_value[s] = flow;\n     \
    \       }\n        }\n\n        _tree.assign(_n, {});\n        _tree_edges.clear();\n\
    \        if (_n > 0) _tree_edges.reserve(_n - 1);\n        for (int v = 1; v <\
    \ _n; v++) {\n            int p = _parent[v];\n            Cap cap = _cut_value[v];\n\
    \            _tree_edges.push_back(Edge{v, p, cap});\n            _tree[v].emplace_back(p,\
    \ cap);\n            _tree[p].emplace_back(v, cap);\n        }\n        build_query_table();\n\
    \        _built = true;\n    }\n\n    const std::vector<Edge>& tree_edges() const\
    \ {\n        assert(_built);\n        return _tree_edges;\n    }\n\n    const\
    \ std::vector<int>& parent() const {\n        assert(_built);\n        return\
    \ _parent;\n    }\n\n    const std::vector<Cap>& cut_values() const {\n      \
    \  assert(_built);\n        return _cut_value;\n    }\n\n    Cap min_cut(int u,\
    \ int v) const {\n        assert(_built);\n        assert(0 <= u && u < _n);\n\
    \        assert(0 <= v && v < _n);\n        assert(u != v);\n        Cap result\
    \ = std::numeric_limits<Cap>::max();\n        if (_depth[u] < _depth[v]) std::swap(u,\
    \ v);\n        int difference = _depth[u] - _depth[v];\n        for (int k = 0;\
    \ difference > 0; k++, difference >>= 1) {\n            if ((difference & 1) ==\
    \ 0) continue;\n            result = std::min(result, _minimum[k][u]);\n     \
    \       u = _up[k][u];\n        }\n        if (u == v) return result;\n      \
    \  for (int k = int(_up.size()) - 1; k >= 0; k--) {\n            if (_up[k][u]\
    \ == _up[k][v]) continue;\n            result = std::min(result, _minimum[k][u]);\n\
    \            result = std::min(result, _minimum[k][v]);\n            u = _up[k][u];\n\
    \            v = _up[k][v];\n        }\n        result = std::min(result, _minimum[0][u]);\n\
    \        result = std::min(result, _minimum[0][v]);\n        return result;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 1 \"graph/flow/min_cost_flow.hpp\"\
    \n\n\n\n#line 5 \"graph/flow/min_cost_flow.hpp\"\n#include <array>\n#include <bit>\n\
    #line 12 \"graph/flow/min_cost_flow.hpp\"\n#include <type_traits>\n#line 15 \"\
    graph/flow/min_cost_flow.hpp\"\n\n#line 18 \"graph/flow/min_cost_flow.hpp\"\n\n\
    namespace m1une {\nnamespace flow {\n\ntemplate <class Cap, class Cost>\nstruct\
    \ MinCostFlow {\n    struct Edge {\n        int from;\n        int to;\n     \
    \   Cap cap;\n        Cap flow;\n        Cost cost;\n    };\n\n   private:\n \
    \   struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \        Cost cost;\n    };\n\n    int _n;\n    std::vector<std::pair<int, int>>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n    bool _has_negative_cost;\n\
    \    bool _has_flow;\n\n    template <class Key>\n    struct RadixHeap {\n   \
    \     using Unsigned = std::make_unsigned_t<Key>;\n        static constexpr int\
    \ bits = std::numeric_limits<Unsigned>::digits;\n\n        std::array<std::vector<std::pair<Unsigned,\
    \ int>>, bits + 1> bucket;\n        Unsigned last = 0;\n        std::size_t count\
    \ = 0;\n\n        static int index(Unsigned first, Unsigned second) {\n      \
    \      return int(std::bit_width(first ^ second));\n        }\n\n        void\
    \ clear() {\n            for (auto& values : bucket) values.clear();\n       \
    \     last = 0;\n            count = 0;\n        }\n\n        bool empty() const\
    \ {\n            return count == 0;\n        }\n\n        void push(Key key, int\
    \ vertex) {\n            Unsigned value = static_cast<Unsigned>(key);\n      \
    \      assert(last <= value);\n            bucket[index(value, last)].emplace_back(value,\
    \ vertex);\n            count++;\n        }\n\n        std::pair<Key, int> pop()\
    \ {\n            if (bucket[0].empty()) {\n                int i = 1;\n      \
    \          while (bucket[i].empty()) i++;\n                last = bucket[i][0].first;\n\
    \                for (const auto& value : bucket[i]) {\n                    last\
    \ = std::min(last, value.first);\n                }\n                for (const\
    \ auto& value : bucket[i]) {\n                    bucket[index(value.first, last)].push_back(value);\n\
    \                }\n                bucket[i].clear();\n            }\n      \
    \      auto [key, vertex] = bucket[0].back();\n            bucket[0].pop_back();\n\
    \            count--;\n            return {static_cast<Key>(key), vertex};\n \
    \       }\n    };\n\n    template <class Key>\n    struct BinaryHeap {\n     \
    \   using Value = std::pair<Key, int>;\n        std::vector<Value> heap;\n\n \
    \       void clear() {\n            heap.clear();\n        }\n\n        bool empty()\
    \ const {\n            return heap.empty();\n        }\n\n        void push(Key\
    \ key, int vertex) {\n            heap.emplace_back(key, vertex);\n          \
    \  std::push_heap(heap.begin(), heap.end(), std::greater<Value>());\n        }\n\
    \n        Value pop() {\n            std::pop_heap(heap.begin(), heap.end(), std::greater<Value>());\n\
    \            Value result = heap.back();\n            heap.pop_back();\n     \
    \       return result;\n        }\n    };\n\n    template <\n        class Key,\n\
    \        bool UseRadix =\n            std::numeric_limits<Key>::is_integer &&\
    \ sizeof(Key) <= 8\n    >\n    struct HeapSelector {\n        using Type = BinaryHeap<Key>;\n\
    \    };\n\n    template <class Key>\n    struct HeapSelector<Key, true> {\n  \
    \      using Type = RadixHeap<Key>;\n    };\n\n    bool use_network_simplex(int\
    \ s, int t, Cap flow_limit) const {\n        if (_has_negative_cost) return false;\n\
    \        if (_pos.size() < 64) return false;\n        auto add_saturated = [](Cap\
    \ first, Cap second) {\n            const Cap maximum = std::numeric_limits<Cap>::max();\n\
    \            return maximum - first < second ? maximum : first + second;\n   \
    \     };\n        struct TerminalCapacity {\n            Cap total = Cap(0);\n\
    \            std::array<Cap, 7> largest{};\n        };\n        auto add_capacity\
    \ = [&](TerminalCapacity& terminal, Cap cap) {\n            terminal.total = add_saturated(terminal.total,\
    \ cap);\n            for (Cap& current : terminal.largest) {\n               \
    \ if (cap <= current) break;\n                std::swap(cap, current);\n     \
    \       }\n        };\n        TerminalCapacity source;\n        for (const auto&\
    \ e : _g[s]) {\n            if (e.to == s) continue;\n            add_capacity(source,\
    \ e.cap);\n        }\n        TerminalCapacity sink;\n        for (const auto&\
    \ e : _g[t]) {\n            if (e.to == t) continue;\n            Cap cap = _g[e.to][e.rev].cap;\n\
    \            add_capacity(sink, cap);\n        }\n        Cap target = std::min(\n\
    \            flow_limit,\n            std::min(source.total, sink.total)\n   \
    \     );\n        if (target == Cap(0)) return false;\n        auto requires_eight_arcs\
    \ = [&](const TerminalCapacity& terminal) {\n            Cap sum = Cap(0);\n \
    \           for (Cap cap : terminal.largest) {\n                sum = add_saturated(sum,\
    \ cap);\n            }\n            return sum < target;\n        };\n       \
    \ return requires_eight_arcs(source) && requires_eight_arcs(sink);\n    }\n\n\
    \    std::pair<Cap, Cost> network_simplex_flow(\n        int s,\n        int t,\n\
    \        Cap flow_limit\n    ) {\n        struct ResidualArc {\n            int\
    \ edge;\n            bool reverse;\n        };\n\n        using Solver = BoundedMinCostFlow<Cap,\
    \ Cost, Cost>;\n        std::vector<ResidualArc> arcs;\n        arcs.reserve(2\
    \ * _pos.size());\n        for (int i = 0; i < int(_pos.size()); i++) {\n    \
    \        auto [from, idx] = _pos[i];\n            const auto& e = _g[from][idx];\n\
    \            const auto& reverse = _g[e.to][e.rev];\n            if (e.cap !=\
    \ Cap(0)) {\n                arcs.push_back(ResidualArc{i, false});\n        \
    \    }\n            if (reverse.cap != Cap(0)) {\n                arcs.push_back(ResidualArc{i,\
    \ true});\n            }\n        }\n\n        auto add_saturated = [](Cap first,\
    \ Cap second, bool& exact) {\n            const Cap maximum = std::numeric_limits<Cap>::max();\n\
    \            if (maximum - first < second) {\n                exact = false;\n\
    \                return maximum;\n            }\n            return first + second;\n\
    \        };\n        bool source_capacity_exact = true;\n        Cap source_capacity\
    \ = Cap(0);\n        for (const auto& e : _g[s]) {\n            if (e.to == s)\
    \ continue;\n            source_capacity = add_saturated(\n                source_capacity,\n\
    \                e.cap,\n                source_capacity_exact\n            );\n\
    \        }\n        bool sink_capacity_exact = true;\n        Cap sink_capacity\
    \ = Cap(0);\n        for (const auto& e : _g[t]) {\n            if (e.to == t)\
    \ continue;\n            sink_capacity = add_saturated(\n                sink_capacity,\n\
    \                _g[e.to][e.rev].cap,\n                sink_capacity_exact\n \
    \           );\n        }\n        Cap target = std::min(\n            flow_limit,\n\
    \            std::min(source_capacity, sink_capacity)\n        );\n        if\
    \ (target == Cap(0)) return {Cap(0), Cost(0)};\n\n        struct ArcData {\n \
    \           int from;\n            int to;\n            Cap cap;\n           \
    \ Cost cost;\n        };\n        auto arc_data = [&](const ResidualArc& arc)\
    \ {\n            auto [from, idx] = _pos[arc.edge];\n            const auto& e\
    \ = _g[from][idx];\n            const auto& reverse = _g[e.to][e.rev];\n     \
    \       return arc.reverse\n                ? ArcData{e.to, from, reverse.cap,\
    \ reverse.cost}\n                : ArcData{from, e.to, e.cap, e.cost};\n     \
    \   };\n        auto apply_flow = [&](const ResidualArc& arc, Cap amount) {\n\
    \            auto [from, idx] = _pos[arc.edge];\n            auto& e = _g[from][idx];\n\
    \            auto& reverse = _g[e.to][e.rev];\n            if (arc.reverse) {\n\
    \                reverse.cap -= amount;\n                e.cap += amount;\n  \
    \          } else {\n                e.cap -= amount;\n                reverse.cap\
    \ += amount;\n            }\n        };\n\n        bool target_infeasible = false;\n\
    \        if (\n            source_capacity_exact && sink_capacity_exact &&\n \
    \           target == source_capacity && target == sink_capacity\n        ) {\n\
    \            Solver terminal_solver(_n);\n            terminal_solver.reserve_edges(int(arcs.size()));\n\
    \            std::vector<Cap> balance(_n, Cap(0));\n            std::vector<int>\
    \ internal_arcs;\n            std::vector<int> fixed_arcs;\n            internal_arcs.reserve(arcs.size());\n\
    \            fixed_arcs.reserve(_g[s].size() + _g[t].size());\n            Cost\
    \ fixed_cost = Cost(0);\n            for (int i = 0; i < int(arcs.size()); i++)\
    \ {\n                ArcData data = arc_data(arcs[i]);\n                if (data.from\
    \ == s) {\n                    if (data.to == s) continue;\n                 \
    \   fixed_arcs.push_back(i);\n                    fixed_cost += Cost(data.cap)\
    \ * data.cost;\n                    if (data.to != t) balance[data.to] += data.cap;\n\
    \                } else if (data.to == t) {\n                    if (data.from\
    \ == t) continue;\n                    fixed_arcs.push_back(i);\n            \
    \        fixed_cost += Cost(data.cap) * data.cost;\n                    balance[data.from]\
    \ -= data.cap;\n                } else if (data.to != s && data.from != t) {\n\
    \                    terminal_solver.add_edge(\n                        data.from,\n\
    \                        data.to,\n                        Cap(0),\n         \
    \               data.cap,\n                        data.cost\n               \
    \     );\n                    internal_arcs.push_back(i);\n                }\n\
    \            }\n            auto terminal_result = terminal_solver.min_cost_flow(balance);\n\
    \            if (terminal_result) {\n                for (int i : fixed_arcs)\
    \ {\n                    apply_flow(arcs[i], arc_data(arcs[i]).cap);\n       \
    \         }\n                for (int i = 0; i < int(internal_arcs.size()); i++)\
    \ {\n                    apply_flow(\n                        arcs[internal_arcs[i]],\n\
    \                        terminal_result->flow(i)\n                    );\n  \
    \              }\n                _has_flow = true;\n                return {target,\
    \ fixed_cost + terminal_result->cost};\n            }\n            target_infeasible\
    \ = true;\n        }\n\n        Solver solver(_n);\n        solver.reserve_edges(int(arcs.size()));\n\
    \        for (const auto& arc : arcs) {\n            ArcData data = arc_data(arc);\n\
    \            solver.add_edge(\n                data.from,\n                data.to,\n\
    \                Cap(0),\n                data.cap,\n                data.cost\n\
    \            );\n        }\n        Cap sent = target;\n        std::optional<typename\
    \ Solver::Result> result;\n        if (\n            !target_infeasible &&\n \
    \           target != std::numeric_limits<Cap>::max()\n        ) {\n         \
    \   result = solver.min_cost_st_flow(s, t, target);\n        }\n        if (!result)\
    \ {\n            MaxFlow<Cap> feasible(_n);\n            feasible.reserve_edges(int(arcs.size()));\n\
    \            for (const auto& arc : arcs) {\n                auto [from, idx]\
    \ = _pos[arc.edge];\n                const auto& e = _g[from][idx];\n        \
    \        const auto& reverse = _g[e.to][e.rev];\n                if (arc.reverse)\
    \ {\n                    feasible.add_edge(e.to, from, reverse.cap);\n       \
    \         } else {\n                    feasible.add_edge(from, e.to, e.cap);\n\
    \                }\n            }\n            sent = feasible.max_flow(s, t,\
    \ target);\n            if (sent == Cap(0)) return {Cap(0), Cost(0)};\n      \
    \      result = solver.min_cost_st_flow(s, t, sent);\n        }\n        assert(result.has_value());\n\
    \        for (int i = 0; i < int(arcs.size()); i++) {\n            auto [from,\
    \ idx] = _pos[arcs[i].edge];\n            auto& e = _g[from][idx];\n         \
    \   auto& reverse = _g[e.to][e.rev];\n            Cap amount = result->flow(i);\n\
    \            if (arcs[i].reverse) {\n                reverse.cap -= amount;\n\
    \                e.cap += amount;\n            } else {\n                e.cap\
    \ -= amount;\n                reverse.cap += amount;\n            }\n        }\n\
    \        _has_flow = true;\n        return {sent, result->cost};\n    }\n\n  \
    \  void init_potential(int s, std::vector<Cost>& potential, Cost cost_inf) const\
    \ {\n        if (!_has_negative_cost && !_has_flow) {\n            potential.assign(_n,\
    \ Cost(0));\n            return;\n        }\n        potential.assign(_n, cost_inf);\n\
    \        potential[s] = Cost(0);\n        for (int iter = 0; iter < _n - 1; iter++)\
    \ {\n            bool updated = false;\n            for (int v = 0; v < _n; v++)\
    \ {\n                if (potential[v] == cost_inf) continue;\n               \
    \ for (const auto& e : _g[v]) {\n                    if (e.cap == Cap(0)) continue;\n\
    \                    Cost nd = potential[v] + e.cost;\n                    if\
    \ (nd < potential[e.to]) {\n                        potential[e.to] = nd;\n  \
    \                      updated = true;\n                    }\n              \
    \  }\n            }\n            if (!updated) break;\n        }\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (potential[v] == cost_inf) potential[v]\
    \ = Cost(0);\n        }\n    }\n\n   public:\n    MinCostFlow() : MinCostFlow(0)\
    \ {}\n\n    explicit MinCostFlow(int n)\n        : _n(n), _g(n), _has_negative_cost(false),\
    \ _has_flow(false) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    int edge_count() const {\n        return int(_pos.size());\n\
    \    }\n\n    void reserve_edges(int edge_count) {\n        assert(0 <= edge_count);\n\
    \        _pos.reserve(edge_count);\n        if (_n == 0 || edge_count == 0 ||\n\
    \            2 * std::size_t(edge_count) < std::size_t(_n)) {\n            return;\n\
    \        }\n        const std::size_t average_degree =\n            (3 * std::size_t(edge_count)\
    \ + std::size_t(_n) - 1)\n            / std::size_t(_n);\n        for (auto& edges\
    \ : _g) edges.reserve(average_degree);\n    }\n\n    void reserve_edges(int edge_count,\
    \ const std::vector<int>& degrees) {\n        assert(0 <= edge_count);\n     \
    \   assert(int(degrees.size()) == _n);\n        _pos.reserve(edge_count);\n  \
    \      for (int v = 0; v < _n; v++) {\n            assert(0 <= degrees[v]);\n\
    \            _g[v].reserve(degrees[v]);\n        }\n    }\n\n    int add_edge(int\
    \ from, int to, Cap cap, Cost cost) {\n        assert(0 <= from && from < _n);\n\
    \        assert(0 <= to && to < _n);\n        assert(Cap(0) <= cap);\n       \
    \ _has_negative_cost = _has_negative_cost || cost < Cost(0);\n        int id =\
    \ int(_pos.size());\n        int from_id = int(_g[from].size());\n        int\
    \ to_id = int(_g[to].size());\n        if (from == to) to_id++;\n        _pos.emplace_back(from,\
    \ from_id);\n        _g[from].push_back(InternalEdge{to, to_id, cap, cost});\n\
    \        _g[to].push_back(InternalEdge{from, from_id, Cap(0), -cost});\n     \
    \   return id;\n    }\n\n    Edge get_edge(int i) const {\n        assert(0 <=\
    \ i && i < int(_pos.size()));\n        auto [from, idx] = _pos[i];\n        const\
    \ auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n      \
    \  return Edge{from, e.to, e.cap + re.cap, re.cap, e.cost};\n    }\n\n    std::vector<Edge>\
    \ edges() const {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    std::pair<Cap, Cost> flow(int s, int t)\
    \ {\n        return flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\n  \
    \  std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {\n        assert(0\
    \ <= s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\
    \        assert(Cap(0) <= flow_limit);\n        if (flow_limit == Cap(0)) return\
    \ {Cap(0), Cost(0)};\n        if constexpr (\n            std::numeric_limits<Cap>::is_integer\
    \ &&\n            std::numeric_limits<Cap>::is_signed &&\n            std::numeric_limits<Cost>::is_signed\n\
    \        ) {\n            if (use_network_simplex(s, t, flow_limit)) {\n     \
    \           return network_simplex_flow(s, t, flow_limit);\n            }\n  \
    \      }\n        auto result = slope(s, t, flow_limit);\n        return result.back();\n\
    \    }\n\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\n      \
    \  return slope(s, t, std::numeric_limits<Cap>::max());\n    }\n\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s < _n);\n\
    \        assert(0 <= t && t < _n);\n        assert(s != t);\n        assert(Cap(0)\
    \ <= flow_limit);\n\n        const Cost cost_inf = std::numeric_limits<Cost>::max()\
    \ / Cost(4);\n        std::vector<Cost> potential, dist(_n);\n        std::vector<int>\
    \ prev_v(_n), prev_e(_n);\n        std::vector<int> settled;\n        settled.reserve(_n);\n\
    \        typename HeapSelector<Cost>::Type que;\n        init_potential(s, potential,\
    \ cost_inf);\n\n        std::vector<std::pair<Cap, Cost>> result;\n        result.emplace_back(Cap(0),\
    \ Cost(0));\n        Cap flow = 0;\n        Cost cost = 0;\n\n        while (flow\
    \ < flow_limit) {\n            std::fill(dist.begin(), dist.end(), cost_inf);\n\
    \            dist[s] = Cost(0);\n            settled.clear();\n            que.clear();\n\
    \            que.push(Cost(0), s);\n\n            while (!que.empty()) {\n   \
    \             auto [d, v] = que.pop();\n                if (dist[v] != d) continue;\n\
    \                settled.push_back(v);\n                if (v == t) break;\n \
    \               for (int i = 0; i < int(_g[v].size()); i++) {\n              \
    \      const auto& e = _g[v][i];\n                    if (e.cap == Cap(0)) continue;\n\
    \                    Cost nd = d + e.cost + potential[v] - potential[e.to];\n\
    \                    if (nd >= dist[e.to]) continue;\n                    dist[e.to]\
    \ = nd;\n                    prev_v[e.to] = v;\n                    prev_e[e.to]\
    \ = i;\n                    que.push(nd, e.to);\n                }\n         \
    \   }\n\n            if (dist[t] == cost_inf) break;\n            for (int v :\
    \ settled) {\n                potential[v] += dist[v] - dist[t];\n           \
    \ }\n\n            Cap add = flow_limit - flow;\n            for (int v = t; v\
    \ != s; v = prev_v[v]) {\n                add = std::min(add, _g[prev_v[v]][prev_e[v]].cap);\n\
    \            }\n            Cost path_cost = potential[t] - potential[s];\n  \
    \          for (int v = t; v != s; v = prev_v[v]) {\n                auto& e =\
    \ _g[prev_v[v]][prev_e[v]];\n                e.cap -= add;\n                _g[e.to][e.rev].cap\
    \ += add;\n            }\n\n            flow += add;\n            cost += Cost(add)\
    \ * path_cost;\n            result.emplace_back(flow, cost);\n        }\n\n  \
    \      _has_flow = _has_flow || flow != Cap(0);\n        return result;\n    }\n\
    };\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 9 \"graph/flow/flow.hpp\"\
    \n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n\
    #include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 17 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/graph/flow/flow_algorithms.test.cpp\"\
    \n\nvoid test_max_flow() {\n    m1une::flow::MaxFlow<long long> mf(4);\n    int\
    \ e0 = mf.add_edge(0, 1, 2);\n    int e1 = mf.add_edge(0, 2, 1);\n    int e2 =\
    \ mf.add_edge(1, 2, 1);\n    int e3 = mf.add_edge(1, 3, 1);\n    int e4 = mf.add_edge(2,\
    \ 3, 2);\n    (void)e1;\n    (void)e2;\n    (void)e3;\n    (void)e4;\n\n    assert(mf.size()\
    \ == 4);\n    assert(mf.edge_count() == 5);\n    assert(mf.max_flow(0, 3) == 3);\n\
    \    auto edges = mf.edges();\n    long long outgoing = 0;\n    for (const auto&\
    \ e : edges) {\n        if (e.from == 0) outgoing += e.flow;\n        assert(0\
    \ <= e.flow && e.flow <= e.cap);\n    }\n    assert(outgoing == 3);\n    assert(mf.get_edge(e0).cap\
    \ == 2);\n\n    auto cut = mf.min_cut(0);\n    assert(cut[0]);\n    assert(!cut[3]);\n\
    \n    mf.change_edge(e0, 3, 1);\n    auto changed = mf.get_edge(e0);\n    assert(changed.cap\
    \ == 3);\n    assert(changed.flow == 1);\n\n    m1une::flow::MaxFlow<long long>\
    \ undirected(2);\n    undirected.reserve_edges(1, std::vector<int>{1, 1});\n \
    \   int undirected_id = undirected.add_undirected_edge(0, 1, 7);\n    undirected.change_edge(undirected_id,\
    \ 7, -3);\n    auto initial_undirected = undirected.get_edge(undirected_id);\n\
    \    assert(initial_undirected.cap == 7);\n    assert(initial_undirected.flow\
    \ == -3);\n    assert(undirected.max_flow(0, 1) == 10);\n    assert(undirected.get_edge(undirected_id).flow\
    \ == 7);\n\n    m1une::flow::MaxFlow<long long> limited(2);\n    int limited_id\
    \ = limited.add_edge(0, 1, 10);\n    assert(limited.max_flow(0, 1, 4) == 4);\n\
    \    assert(limited.get_edge(limited_id).flow == 4);\n    assert(limited.max_flow(0,\
    \ 1) == 6);\n    assert(limited.get_edge(limited_id).flow == 10);\n\n    // Five\
    \ different path lengths force the unlimited overload past its\n    // initial\
    \ Dinic phases and exercise the push-relabel handoff.\n    m1une::flow::MaxFlow<long\
    \ long> hybrid(17);\n    int next_vertex = 1;\n    for (int length = 2; length\
    \ <= 6; length++) {\n        int from = 0;\n        for (int edge = 0; edge <\
    \ length; edge++) {\n            int to = edge + 1 == length ? 16 : next_vertex++;\n\
    \            hybrid.add_edge(from, to, 3);\n            from = to;\n        }\n\
    \    }\n    assert(next_vertex == 16);\n    while (hybrid.edge_count() < 85) {\n\
    \        int v = 1 + hybrid.edge_count() % 15;\n        hybrid.add_edge(v, v,\
    \ 0);\n    }\n    assert(hybrid.max_flow(0, 16) == 15);\n    assert(hybrid.max_flow(0,\
    \ 16) == 0);\n\n    struct InputEdge {\n        int from;\n        int to;\n \
    \       long long cap;\n        bool undirected;\n    };\n    std::mt19937 random(19260817);\n\
    \    for (int iteration = 0; iteration < 500; iteration++) {\n        int n =\
    \ 2 + int(random() % 6);\n        int m = int(random() % 13);\n        std::vector<InputEdge>\
    \ input_edges;\n        m1une::flow::MaxFlow<long long> flow(n);\n        m1une::flow::MaxFlow<long\
    \ long> push_relabel_flow(n);\n        flow.reserve_edges(m);\n        push_relabel_flow.reserve_edges(m);\n\
    \        for (int edge = 0; edge < m; edge++) {\n            InputEdge input{\n\
    \                int(random() % n),\n                int(random() % n),\n    \
    \            1 + static_cast<long long>(random() % 10),\n                bool(random()\
    \ & 1)\n            };\n            input_edges.push_back(input);\n          \
    \  if (input.undirected) {\n                flow.add_undirected_edge(input.from,\
    \ input.to, input.cap);\n                push_relabel_flow.add_undirected_edge(input.from,\
    \ input.to, input.cap);\n            } else {\n                flow.add_edge(input.from,\
    \ input.to, input.cap);\n                push_relabel_flow.add_edge(input.from,\
    \ input.to, input.cap);\n            }\n        }\n\n        long long expected\
    \ = std::numeric_limits<long long>::max();\n        for (int mask = 0; mask <\
    \ (1 << n); mask++) {\n            if ((mask & 1) == 0 || (mask >> (n - 1) & 1)\
    \ != 0) continue;\n            long long capacity = 0;\n            for (const\
    \ auto& edge : input_edges) {\n                bool from_side = mask >> edge.from\
    \ & 1;\n                bool to_side = mask >> edge.to & 1;\n                if\
    \ (from_side && !to_side) capacity += edge.cap;\n                if (edge.undirected\
    \ && !from_side && to_side) {\n                    capacity += edge.cap;\n   \
    \             }\n            }\n            expected = std::min(expected, capacity);\n\
    \        }\n\n        long long result = flow.max_flow(0, n - 1);\n        assert(result\
    \ == expected);\n        long long push_relabel_result =\n            push_relabel_flow.max_flow_push_relabel(0,\
    \ n - 1);\n        assert(push_relabel_result == expected);\n\n        auto validate\
    \ = [&](const auto& solved_flow, long long solved_value) {\n            std::vector<long\
    \ long> net_flow(n, 0);\n            for (int edge = 0; edge < m; edge++) {\n\
    \                auto result_edge = solved_flow.get_edge(edge);\n            \
    \    assert(result_edge.cap == input_edges[edge].cap);\n                if (input_edges[edge].undirected)\
    \ {\n                    assert(-result_edge.cap <= result_edge.flow);\n     \
    \           } else {\n                    assert(0 <= result_edge.flow);\n   \
    \             }\n                assert(result_edge.flow <= result_edge.cap);\n\
    \                net_flow[result_edge.from] += result_edge.flow;\n           \
    \     net_flow[result_edge.to] -= result_edge.flow;\n            }\n         \
    \   assert(net_flow[0] == solved_value);\n            assert(net_flow[n - 1] ==\
    \ -solved_value);\n            for (int vertex = 1; vertex + 1 < n; vertex++)\
    \ {\n                assert(net_flow[vertex] == 0);\n            }\n        };\n\
    \        validate(flow, result);\n        validate(push_relabel_flow, push_relabel_result);\n\
    \        assert(flow.max_flow_push_relabel(0, n - 1) == 0);\n        assert(push_relabel_flow.max_flow_push_relabel(0,\
    \ n - 1) == 0);\n        assert(push_relabel_flow.max_flow(0, n - 1) == 0);\n\
    \    }\n}\n\nvoid test_gomory_hu() {\n    m1une::flow::GomoryHu<long long> gh(4);\n\
    \    gh.add_edge(0, 1, 3);\n    gh.add_edge(1, 2, 2);\n    gh.add_edge(0, 2, 1);\n\
    \    gh.add_edge(2, 3, 4);\n    gh.build();\n    assert(gh.size() == 4);\n   \
    \ assert(gh.edge_count() == 4);\n    assert(gh.tree_edges().size() == 3);\n  \
    \  assert(gh.min_cut(0, 1) == 4);\n    assert(gh.min_cut(0, 2) == 3);\n    assert(gh.min_cut(0,\
    \ 3) == 3);\n    assert(gh.min_cut(2, 3) == 4);\n\n    m1une::flow::GomoryHu<long\
    \ long> disconnected(3);\n    disconnected.add_edge(0, 1, 5);\n    disconnected.build();\n\
    \    assert(disconnected.min_cut(0, 1) == 5);\n    assert(disconnected.min_cut(0,\
    \ 2) == 0);\n\n    m1une::flow::GomoryHu<long long> rebuilt(2);\n    rebuilt.build();\n\
    \    assert(rebuilt.min_cut(0, 1) == 0);\n    rebuilt.add_edge(0, 1, 7);\n   \
    \ rebuilt.add_edge(0, 0, 100);\n    rebuilt.build();\n    assert(rebuilt.min_cut(0,\
    \ 1) == 7);\n\n    m1une::flow::GomoryHu<long long> singleton(1);\n    singleton.build();\n\
    \    assert(singleton.tree_edges().empty());\n\n    std::mt19937 random(123456789);\n\
    \    for (int iteration = 0; iteration < 200; iteration++) {\n        int n =\
    \ 2 + int(random() % 8);\n        struct InputEdge {\n            int u;\n   \
    \         int v;\n            long long cap;\n        };\n        std::vector<InputEdge>\
    \ edges;\n        m1une::flow::GomoryHu<long long> tree(n);\n        int m = random()\
    \ % (2 * n * n + 1);\n        for (int i = 0; i < m; i++) {\n            int u\
    \ = random() % n;\n            int v = random() % n;\n            long long cap\
    \ = random() % 1000001;\n            edges.push_back(InputEdge{u, v, cap});\n\
    \            tree.add_edge(u, v, cap);\n        }\n        tree.build();\n   \
    \     for (int s = 0; s < n; s++) {\n            for (int t = s + 1; t < n; t++)\
    \ {\n                m1une::flow::MaxFlow<long long> mf(n);\n                for\
    \ (const auto& edge : edges) {\n                    mf.add_edge(edge.u, edge.v,\
    \ edge.cap);\n                    mf.add_edge(edge.v, edge.u, edge.cap);\n   \
    \             }\n                assert(tree.min_cut(s, t) == mf.max_flow(s, t));\n\
    \            }\n        }\n    }\n}\n\nvoid test_bounded_flow() {\n    m1une::flow::BoundedFlow<long\
    \ long> st(4);\n    int a = st.add_edge(0, 1, 1, 3);\n    int b = st.add_edge(0,\
    \ 2, 0, 2);\n    int c = st.add_edge(1, 3, 1, 2);\n    int d = st.add_edge(2,\
    \ 3, 0, 2);\n    int e = st.add_edge(1, 2, 0, 1);\n    (void)a;\n    (void)b;\n\
    \    (void)c;\n    (void)d;\n    (void)e;\n\n    auto exact = st.feasible_st_flow(0,\
    \ 3, 3);\n    assert(exact.has_value());\n    std::vector<long long> balance(4,\
    \ 0);\n    for (const auto& edge : exact->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        balance[edge.from] += edge.flow;\n\
    \        balance[edge.to] -= edge.flow;\n    }\n    assert((balance == std::vector<long\
    \ long>{3, 0, 0, -3}));\n\n    auto too_much = st.feasible_st_flow(0, 3, 6);\n\
    \    assert(!too_much.has_value());\n\n    m1une::flow::BoundedFlow<long long>\
    \ bf(3);\n    int f01 = bf.add_edge(0, 1, 1, 3);\n    int f02 = bf.add_edge(0,\
    \ 2, 0, 4);\n    bf.add_edge(1, 2, 0, 2);\n    bf.add_supply(0, 4);\n    bf.add_demand(1,\
    \ 1);\n    bf.add_demand(2, 3);\n    assert(bf.balance(0) == 4);\n    auto bflow\
    \ = bf.feasible_flow();\n    assert(bflow.has_value());\n    assert(bflow->get_edge(f01).flow\
    \ >= 1);\n    assert(bflow->get_edge(f02).flow >= 0);\n    std::vector<long long>\
    \ b_balance(3, 0);\n    for (const auto& edge : bflow->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        b_balance[edge.from] += edge.flow;\n\
    \        b_balance[edge.to] -= edge.flow;\n    }\n    assert((b_balance == std::vector<long\
    \ long>{4, -1, -3}));\n\n    m1une::flow::BoundedFlow<long long> negative(2);\n\
    \    int neg = negative.add_edge(0, 1, -5, 5);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.feasible_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n\n    m1une::flow::BoundedFlow<long long> impossible(2);\n    impossible.add_edge(0,\
    \ 1, 0, 1);\n    impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n\
    \    assert(!impossible.feasible_flow().has_value());\n\n    m1une::flow::BFlow<long\
    \ long> alias(1);\n    assert(alias.size() == 1);\n}\n\nvoid test_bounded_min_cost_flow()\
    \ {\n    m1une::flow::BoundedMinCostFlow<long long, long long> st(3);\n    st.reserve_edges(3);\n\
    \    int e01 = st.add_edge(0, 1, 1, 3, 2);\n    int e12 = st.add_edge(1, 2, 1,\
    \ 3, 1);\n    int e02 = st.add_edge(0, 2, 0, 3, 10);\n\n    auto exact = st.min_cost_st_flow(0,\
    \ 2, 3);\n    assert(exact.has_value());\n    assert(exact->cost == 9);\n    assert(exact->flow(e01)\
    \ == 3);\n    assert(exact->flow(e12) == 3);\n    assert(exact->flow(e02) == 0);\n\
    \    auto exact_polynomial = st.min_cost_st_flow_polynomial(0, 2, 3);\n    assert(exact_polynomial.has_value());\n\
    \    assert(exact_polynomial->cost == 9);\n    std::vector<long long> balance(3,\
    \ 0);\n    for (const auto& edge : exact->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        balance[edge.from] += edge.flow;\n\
    \        balance[edge.to] -= edge.flow;\n    }\n    assert((balance == std::vector<long\
    \ long>{3, 0, -3}));\n\n    m1une::flow::BoundedMinCostFlow<long long, long long>\
    \ bf(3);\n    int p01 = bf.add_edge(0, 1, 0, 2, 1);\n    int p12 = bf.add_edge(1,\
    \ 2, 0, 2, 1);\n    int p02 = bf.add_edge(0, 2, 0, 2, 5);\n    bf.add_supply(0,\
    \ 2);\n    bf.add_demand(2, 2);\n    auto bflow = bf.min_cost_flow();\n    assert(bflow.has_value());\n\
    \    assert(bflow->cost == 4);\n    assert(bflow->flow(p01) == 2);\n    assert(bflow->flow(p12)\
    \ == 2);\n    assert(bflow->flow(p02) == 0);\n\n    m1une::flow::BoundedMinCostFlow<long\
    \ long, long long> negative(2);\n    int neg = negative.add_edge(0, 1, -5, 5,\
    \ 2);\n    negative.add_demand(0, 3);\n    negative.add_supply(1, 3);\n    auto\
    \ negative_flow = negative.min_cost_flow();\n    assert(negative_flow.has_value());\n\
    \    assert(negative_flow->flow(neg) == -3);\n    assert(negative_flow->cost ==\
    \ -6);\n\n    m1une::flow::BoundedMinCostFlow<long long, long long> cycle(2);\n\
    \    int c01 = cycle.add_edge(0, 1, 0, 1, -5);\n    int c10 = cycle.add_edge(1,\
    \ 0, 0, 1, 3);\n    auto circulation = cycle.min_cost_flow();\n    assert(circulation.has_value());\n\
    \    assert(circulation->flow(c01) == 1);\n    assert(circulation->flow(c10) ==\
    \ 1);\n    assert(circulation->cost == -2);\n    auto polynomial_circulation =\
    \ cycle.min_cost_flow_polynomial();\n    assert(polynomial_circulation.has_value());\n\
    \    assert(polynomial_circulation->cost == -2);\n\n    using ImmediateFallback\
    \ = m1une::flow::BoundedMinCostFlow<\n        long long, long long, long long,\
    \ 0\n    >;\n    ImmediateFallback fallback_cycle(2);\n    fallback_cycle.add_edge(0,\
    \ 1, 0, 1, -5);\n    fallback_cycle.add_edge(1, 0, 0, 1, 3);\n    auto fallback_circulation\
    \ = fallback_cycle.min_cost_flow();\n    assert(fallback_circulation.has_value());\n\
    \    assert(fallback_circulation->cost == -2);\n\n    m1une::flow::BoundedMinCostFlow<long\
    \ long, long long> impossible(2);\n    impossible.add_edge(0, 1, 0, 1, 0);\n \
    \   impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n    assert(!impossible.min_cost_flow().has_value());\n\
    \n    using WideCostFlow = m1une::flow::BoundedMinCostFlow<\n        long long,\
    \ long long, __int128_t\n    >;\n    WideCostFlow wide_cost(1);\n    wide_cost.reserve_edges(1);\n\
    \    constexpr long long trillion = 1000000000000LL;\n    wide_cost.add_edge(0,\
    \ 0, trillion, trillion, trillion);\n    auto wide_result = wide_cost.min_cost_flow();\n\
    \    assert(wide_result.has_value());\n    assert(wide_result->cost == __int128_t(trillion)\
    \ * trillion);\n\n    std::mt19937 random(987654321);\n    for (int iteration\
    \ = 0; iteration < 500; iteration++) {\n        int n = 1 + int(random() % 4);\n\
    \        int m = int(random() % 7);\n        struct SmallEdge {\n            int\
    \ from;\n            int to;\n            long long lower;\n            long long\
    \ upper;\n            long long cost;\n        };\n        std::vector<SmallEdge>\
    \ edges;\n        m1une::flow::BoundedMinCostFlow<long long, long long> solver(n);\n\
    \        for (int i = 0; i < m; i++) {\n            int from = int(random() %\
    \ n);\n            int to = int(random() % n);\n            long long lower =\
    \ static_cast<long long>(random() % 5) - 2;\n            long long upper = lower\
    \ + static_cast<long long>(random() % 4);\n            long long cost = static_cast<long\
    \ long>(random() % 9) - 4;\n            edges.push_back(SmallEdge{from, to, lower,\
    \ upper, cost});\n            solver.add_edge(from, to, lower, upper, cost);\n\
    \        }\n\n        std::vector<long long> required_balance(n, 0);\n       \
    \ long long balance_sum = 0;\n        for (int vertex = 0; vertex + 1 < n; vertex++)\
    \ {\n            required_balance[vertex] =\n                static_cast<long\
    \ long>(random() % 7) - 3;\n            balance_sum += required_balance[vertex];\n\
    \        }\n        required_balance.back() = -balance_sum;\n\n        bool feasible\
    \ = false;\n        long long best_cost = 0;\n        std::vector<long long> flow(m);\n\
    \        auto enumerate = [&](auto&& self, int edge_id) -> void {\n          \
    \  if (edge_id != m) {\n                for (\n                    flow[edge_id]\
    \ = edges[edge_id].lower;\n                    flow[edge_id] <= edges[edge_id].upper;\n\
    \                    flow[edge_id]++\n                ) {\n                  \
    \  self(self, edge_id + 1);\n                }\n                return;\n    \
    \        }\n\n            std::vector<long long> actual_balance(n, 0);\n     \
    \       long long cost = 0;\n            for (int i = 0; i < m; i++) {\n     \
    \           actual_balance[edges[i].from] += flow[i];\n                actual_balance[edges[i].to]\
    \ -= flow[i];\n                cost += flow[i] * edges[i].cost;\n            }\n\
    \            if (actual_balance != required_balance) return;\n            if (!feasible\
    \ || cost < best_cost) best_cost = cost;\n            feasible = true;\n     \
    \   };\n        enumerate(enumerate, 0);\n\n        auto validate_result = [&](const\
    \ auto& result) {\n            assert(result.has_value() == feasible);\n     \
    \       if (!result.has_value()) return;\n            assert(result->cost == best_cost);\n\
    \n            std::vector<long long> actual_balance(n, 0);\n            for (const\
    \ auto& edge : result->edges) {\n                assert(edge.lower <= edge.flow\
    \ && edge.flow <= edge.upper);\n                actual_balance[edge.from] += edge.flow;\n\
    \                actual_balance[edge.to] -= edge.flow;\n                long long\
    \ reduced_cost =\n                    edge.cost\n                    + result->potential[edge.from]\n\
    \                    - result->potential[edge.to];\n                if (edge.flow\
    \ < edge.upper) assert(0 <= reduced_cost);\n                if (edge.lower < edge.flow)\
    \ assert(reduced_cost <= 0);\n            }\n            assert(actual_balance\
    \ == required_balance);\n        };\n\n        validate_result(solver.min_cost_flow(required_balance));\n\
    \        validate_result(solver.min_cost_flow_polynomial(required_balance));\n\
    \    }\n\n    m1une::flow::BMinCostFlow<long long, long long> alias(1);\n    assert(alias.size()\
    \ == 1);\n    m1une::flow::BMinCostFlow<long long, long long, __int128_t> wide_alias(1);\n\
    \    assert(wide_alias.size() == 1);\n    m1une::flow::BMinCostFlow<long long,\
    \ long long, long long, 0>\n        fallback_alias(1);\n    assert(fallback_alias.size()\
    \ == 1);\n}\n\nvoid test_min_cost_flow() {\n    m1une::flow::MinCostFlow<long\
    \ long, long long> mcf(4);\n    mcf.add_edge(0, 1, 2, 1);\n    mcf.add_edge(0,\
    \ 2, 1, 2);\n    mcf.add_edge(1, 2, 1, 0);\n    mcf.add_edge(1, 3, 1, 3);\n  \
    \  mcf.add_edge(2, 3, 2, 1);\n\n    auto result = mcf.flow(0, 3, 2);\n    assert(result.first\
    \ == 2);\n    assert(result.second == 5);\n    auto edges = mcf.edges();\n   \
    \ long long total_source_flow = 0;\n    for (const auto& e : edges) {\n      \
    \  if (e.from == 0) total_source_flow += e.flow;\n        assert(0 <= e.flow &&\
    \ e.flow <= e.cap);\n    }\n    assert(total_source_flow == 2);\n\n    m1une::flow::MinCostFlow<long\
    \ long, long long> negative(3);\n    negative.add_edge(0, 1, 1, -5);\n    negative.add_edge(1,\
    \ 2, 1, 2);\n    negative.add_edge(0, 2, 1, 10);\n    auto slope = negative.slope(0,\
    \ 2, 2);\n    std::vector<std::pair<long long, long long>> expected_slope = {\n\
    \        std::pair<long long, long long>{0, 0},\n        std::pair<long long,\
    \ long long>{1, -3},\n        std::pair<long long, long long>{2, 7},\n    };\n\
    \    assert(slope == expected_slope);\n\n    std::mt19937 random(31415926);\n\
    \    for (int iteration = 0; iteration < 200; iteration++) {\n        int n =\
    \ 2 + int(random() % 7);\n        int m = int(random() % 30);\n        long long\
    \ flow_limit = random() % 16;\n        m1une::flow::MinCostFlow<long long, long\
    \ long> tested(n);\n        m1une::flow::BoundedMinCostFlow<long long, long long>\
    \ expected(n);\n        m1une::flow::MaxFlow<long long> maximum(n);\n        tested.reserve_edges(m);\n\
    \        expected.reserve_edges(m);\n        maximum.reserve_edges(m);\n     \
    \   for (int edge = 0; edge < m; edge++) {\n            int from = int(random()\
    \ % (n - 1));\n            int to = from + 1 + int(random() % (n - from - 1));\n\
    \            long long cap = random() % 6;\n            long long cost = int(random()\
    \ % 21) - 10;\n            tested.add_edge(from, to, cap, cost);\n           \
    \ expected.add_edge(from, to, 0, cap, cost);\n            maximum.add_edge(from,\
    \ to, cap);\n        }\n        long long sent = maximum.max_flow(0, n - 1, flow_limit);\n\
    \        auto expected_result = expected.min_cost_st_flow(0, n - 1, sent);\n \
    \       assert(expected_result.has_value());\n        auto tested_result = tested.flow(0,\
    \ n - 1, flow_limit);\n        assert(tested_result.first == sent);\n        assert(tested_result.second\
    \ == expected_result->cost);\n    }\n\n    // At least eight terminal arcs are\
    \ required, exercising the guarded\n    // one-shot network-simplex path rather\
    \ than successive shortest paths.\n    m1une::flow::MinCostFlow<long long, long\
    \ long> fast(10);\n    m1une::flow::MinCostFlow<long long, long long> reference(10);\n\
    \    fast.reserve_edges(64);\n    reference.reserve_edges(64);\n    for (int v\
    \ = 1; v <= 8; v++) {\n        fast.add_edge(0, v, 1, v);\n        fast.add_edge(v,\
    \ 9, 1, 10 - v);\n        reference.add_edge(0, v, 1, v);\n        reference.add_edge(v,\
    \ 9, 1, 10 - v);\n    }\n    while (fast.edge_count() < 64) {\n        int from\
    \ = 1 + fast.edge_count() % 8;\n        int to = 1 + (fast.edge_count() * 3 +\
    \ 1) % 8;\n        if (from == to) to = to == 8 ? 1 : to + 1;\n        fast.add_edge(from,\
    \ to, 1, 100);\n        reference.add_edge(from, to, 1, 100);\n    }\n    auto\
    \ fast_result = fast.flow(0, 9, 10);\n    auto reference_result = reference.slope(0,\
    \ 9, 10).back();\n    assert(fast_result == reference_result);\n    std::pair<long\
    \ long, long long> expected_fast_result(8, 80);\n    assert(fast_result == expected_fast_result);\n\
    \    assert(fast.flow(0, 9).first == 0);\n\n    // After one shortest-path augmentation,\
    \ a limit below both remaining\n    // terminal capacities exercises the exact\
    \ residual s-t solve without\n    // terminal contraction, including negative-cost\
    \ reverse arcs.\n    m1une::flow::MinCostFlow<long long, long long> partial(12);\n\
    \    m1une::flow::MinCostFlow<long long, long long> partial_reference(12);\n \
    \   for (int v = 1; v <= 10; v++) {\n        partial.add_edge(0, v, 1, v);\n \
    \       partial.add_edge(v, 11, 1, 0);\n        partial_reference.add_edge(0,\
    \ v, 1, v);\n        partial_reference.add_edge(v, 11, 1, 0);\n    }\n    while\
    \ (partial.edge_count() < 64) {\n        int from = 1 + partial.edge_count() %\
    \ 10;\n        int to = 1 + (partial.edge_count() * 7 + 1) % 10;\n        if (from\
    \ == to) to = to == 10 ? 1 : to + 1;\n        partial.add_edge(from, to, 1, 100);\n\
    \        partial_reference.add_edge(from, to, 1, 100);\n    }\n    assert(\n \
    \       partial.flow(0, 11, 1) ==\n        partial_reference.slope(0, 11, 1).back()\n\
    \    );\n    assert(\n        partial.flow(0, 11, 8) ==\n        partial_reference.slope(0,\
    \ 11, 8).back()\n    );\n    assert(partial.flow(0, 11) == partial_reference.slope(0,\
    \ 11).back());\n\n    // The terminal cut permits eight units but an internal\
    \ bottleneck permits\n    // only four, exercising the max-flow fallback before\
    \ the exact-cost solve.\n    m1une::flow::MinCostFlow<long long, long long> bottleneck(20);\n\
    \    for (int v = 1; v <= 8; v++) {\n        bottleneck.add_edge(0, v, 1, 0);\n\
    \        bottleneck.add_edge(v, 9, 1, 0);\n        bottleneck.add_edge(10, v +\
    \ 10, 1, 0);\n        bottleneck.add_edge(v + 10, 19, 1, 0);\n    }\n    bottleneck.add_edge(9,\
    \ 10, 4, 1);\n    while (bottleneck.edge_count() < 64) {\n        int from = 1\
    \ + bottleneck.edge_count() % 8;\n        int to = 1 + (bottleneck.edge_count()\
    \ * 5 + 1) % 8;\n        if (from == to) to = to == 8 ? 1 : to + 1;\n        bottleneck.add_edge(from,\
    \ to, 1, 100);\n    }\n    std::pair<long long, long long> expected_bottleneck(4,\
    \ 4);\n    assert(bottleneck.flow(0, 19, 8) == expected_bottleneck);\n\n    //\
    \ Randomized comparisons cover the terminal-contraction optimization on\n    //\
    \ feasible non-negative-cost instances.\n    for (int iteration = 0; iteration\
    \ < 100; iteration++) {\n        constexpr int n = 18;\n        m1une::flow::MinCostFlow<long\
    \ long, long long> adaptive(n);\n        m1une::flow::MinCostFlow<long long, long\
    \ long> shortest_paths(n);\n        adaptive.reserve_edges(80);\n        shortest_paths.reserve_edges(80);\n\
    \        for (int v = 1; v <= 8; v++) {\n            long long first_cost = random()\
    \ % 11;\n            long long middle_cost = random() % 11;\n            long\
    \ long last_cost = random() % 11;\n            adaptive.add_edge(0, v, 1, first_cost);\n\
    \            adaptive.add_edge(v, v + 8, 1, middle_cost);\n            adaptive.add_edge(v\
    \ + 8, 17, 1, last_cost);\n            shortest_paths.add_edge(0, v, 1, first_cost);\n\
    \            shortest_paths.add_edge(v, v + 8, 1, middle_cost);\n            shortest_paths.add_edge(v\
    \ + 8, 17, 1, last_cost);\n        }\n        while (adaptive.edge_count() < 80)\
    \ {\n            int from = 1 + int(random() % 16);\n            int to = 1 +\
    \ int(random() % 16);\n            if (from == to) to = to == 16 ? 1 : to + 1;\n\
    \            long long cap = 1 + random() % 3;\n            long long cost = random()\
    \ % 21;\n            adaptive.add_edge(from, to, cap, cost);\n            shortest_paths.add_edge(from,\
    \ to, cap, cost);\n        }\n        assert(\n            adaptive.flow(0, 17,\
    \ 8) ==\n            shortest_paths.slope(0, 17, 8).back()\n        );\n    }\n\
    }\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_max_flow();\n    test_gomory_hu();\n    test_bounded_flow();\n\
    \    test_bounded_min_cost_flow();\n    test_min_cost_flow();\n\n    long long\
    \ a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <limits>\n#include <random>\n#include <utility>\n#include <vector>\n\n\
    #include \"../../../graph/flow/flow.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nvoid test_max_flow() {\n    m1une::flow::MaxFlow<long long> mf(4);\n    int\
    \ e0 = mf.add_edge(0, 1, 2);\n    int e1 = mf.add_edge(0, 2, 1);\n    int e2 =\
    \ mf.add_edge(1, 2, 1);\n    int e3 = mf.add_edge(1, 3, 1);\n    int e4 = mf.add_edge(2,\
    \ 3, 2);\n    (void)e1;\n    (void)e2;\n    (void)e3;\n    (void)e4;\n\n    assert(mf.size()\
    \ == 4);\n    assert(mf.edge_count() == 5);\n    assert(mf.max_flow(0, 3) == 3);\n\
    \    auto edges = mf.edges();\n    long long outgoing = 0;\n    for (const auto&\
    \ e : edges) {\n        if (e.from == 0) outgoing += e.flow;\n        assert(0\
    \ <= e.flow && e.flow <= e.cap);\n    }\n    assert(outgoing == 3);\n    assert(mf.get_edge(e0).cap\
    \ == 2);\n\n    auto cut = mf.min_cut(0);\n    assert(cut[0]);\n    assert(!cut[3]);\n\
    \n    mf.change_edge(e0, 3, 1);\n    auto changed = mf.get_edge(e0);\n    assert(changed.cap\
    \ == 3);\n    assert(changed.flow == 1);\n\n    m1une::flow::MaxFlow<long long>\
    \ undirected(2);\n    undirected.reserve_edges(1, std::vector<int>{1, 1});\n \
    \   int undirected_id = undirected.add_undirected_edge(0, 1, 7);\n    undirected.change_edge(undirected_id,\
    \ 7, -3);\n    auto initial_undirected = undirected.get_edge(undirected_id);\n\
    \    assert(initial_undirected.cap == 7);\n    assert(initial_undirected.flow\
    \ == -3);\n    assert(undirected.max_flow(0, 1) == 10);\n    assert(undirected.get_edge(undirected_id).flow\
    \ == 7);\n\n    m1une::flow::MaxFlow<long long> limited(2);\n    int limited_id\
    \ = limited.add_edge(0, 1, 10);\n    assert(limited.max_flow(0, 1, 4) == 4);\n\
    \    assert(limited.get_edge(limited_id).flow == 4);\n    assert(limited.max_flow(0,\
    \ 1) == 6);\n    assert(limited.get_edge(limited_id).flow == 10);\n\n    // Five\
    \ different path lengths force the unlimited overload past its\n    // initial\
    \ Dinic phases and exercise the push-relabel handoff.\n    m1une::flow::MaxFlow<long\
    \ long> hybrid(17);\n    int next_vertex = 1;\n    for (int length = 2; length\
    \ <= 6; length++) {\n        int from = 0;\n        for (int edge = 0; edge <\
    \ length; edge++) {\n            int to = edge + 1 == length ? 16 : next_vertex++;\n\
    \            hybrid.add_edge(from, to, 3);\n            from = to;\n        }\n\
    \    }\n    assert(next_vertex == 16);\n    while (hybrid.edge_count() < 85) {\n\
    \        int v = 1 + hybrid.edge_count() % 15;\n        hybrid.add_edge(v, v,\
    \ 0);\n    }\n    assert(hybrid.max_flow(0, 16) == 15);\n    assert(hybrid.max_flow(0,\
    \ 16) == 0);\n\n    struct InputEdge {\n        int from;\n        int to;\n \
    \       long long cap;\n        bool undirected;\n    };\n    std::mt19937 random(19260817);\n\
    \    for (int iteration = 0; iteration < 500; iteration++) {\n        int n =\
    \ 2 + int(random() % 6);\n        int m = int(random() % 13);\n        std::vector<InputEdge>\
    \ input_edges;\n        m1une::flow::MaxFlow<long long> flow(n);\n        m1une::flow::MaxFlow<long\
    \ long> push_relabel_flow(n);\n        flow.reserve_edges(m);\n        push_relabel_flow.reserve_edges(m);\n\
    \        for (int edge = 0; edge < m; edge++) {\n            InputEdge input{\n\
    \                int(random() % n),\n                int(random() % n),\n    \
    \            1 + static_cast<long long>(random() % 10),\n                bool(random()\
    \ & 1)\n            };\n            input_edges.push_back(input);\n          \
    \  if (input.undirected) {\n                flow.add_undirected_edge(input.from,\
    \ input.to, input.cap);\n                push_relabel_flow.add_undirected_edge(input.from,\
    \ input.to, input.cap);\n            } else {\n                flow.add_edge(input.from,\
    \ input.to, input.cap);\n                push_relabel_flow.add_edge(input.from,\
    \ input.to, input.cap);\n            }\n        }\n\n        long long expected\
    \ = std::numeric_limits<long long>::max();\n        for (int mask = 0; mask <\
    \ (1 << n); mask++) {\n            if ((mask & 1) == 0 || (mask >> (n - 1) & 1)\
    \ != 0) continue;\n            long long capacity = 0;\n            for (const\
    \ auto& edge : input_edges) {\n                bool from_side = mask >> edge.from\
    \ & 1;\n                bool to_side = mask >> edge.to & 1;\n                if\
    \ (from_side && !to_side) capacity += edge.cap;\n                if (edge.undirected\
    \ && !from_side && to_side) {\n                    capacity += edge.cap;\n   \
    \             }\n            }\n            expected = std::min(expected, capacity);\n\
    \        }\n\n        long long result = flow.max_flow(0, n - 1);\n        assert(result\
    \ == expected);\n        long long push_relabel_result =\n            push_relabel_flow.max_flow_push_relabel(0,\
    \ n - 1);\n        assert(push_relabel_result == expected);\n\n        auto validate\
    \ = [&](const auto& solved_flow, long long solved_value) {\n            std::vector<long\
    \ long> net_flow(n, 0);\n            for (int edge = 0; edge < m; edge++) {\n\
    \                auto result_edge = solved_flow.get_edge(edge);\n            \
    \    assert(result_edge.cap == input_edges[edge].cap);\n                if (input_edges[edge].undirected)\
    \ {\n                    assert(-result_edge.cap <= result_edge.flow);\n     \
    \           } else {\n                    assert(0 <= result_edge.flow);\n   \
    \             }\n                assert(result_edge.flow <= result_edge.cap);\n\
    \                net_flow[result_edge.from] += result_edge.flow;\n           \
    \     net_flow[result_edge.to] -= result_edge.flow;\n            }\n         \
    \   assert(net_flow[0] == solved_value);\n            assert(net_flow[n - 1] ==\
    \ -solved_value);\n            for (int vertex = 1; vertex + 1 < n; vertex++)\
    \ {\n                assert(net_flow[vertex] == 0);\n            }\n        };\n\
    \        validate(flow, result);\n        validate(push_relabel_flow, push_relabel_result);\n\
    \        assert(flow.max_flow_push_relabel(0, n - 1) == 0);\n        assert(push_relabel_flow.max_flow_push_relabel(0,\
    \ n - 1) == 0);\n        assert(push_relabel_flow.max_flow(0, n - 1) == 0);\n\
    \    }\n}\n\nvoid test_gomory_hu() {\n    m1une::flow::GomoryHu<long long> gh(4);\n\
    \    gh.add_edge(0, 1, 3);\n    gh.add_edge(1, 2, 2);\n    gh.add_edge(0, 2, 1);\n\
    \    gh.add_edge(2, 3, 4);\n    gh.build();\n    assert(gh.size() == 4);\n   \
    \ assert(gh.edge_count() == 4);\n    assert(gh.tree_edges().size() == 3);\n  \
    \  assert(gh.min_cut(0, 1) == 4);\n    assert(gh.min_cut(0, 2) == 3);\n    assert(gh.min_cut(0,\
    \ 3) == 3);\n    assert(gh.min_cut(2, 3) == 4);\n\n    m1une::flow::GomoryHu<long\
    \ long> disconnected(3);\n    disconnected.add_edge(0, 1, 5);\n    disconnected.build();\n\
    \    assert(disconnected.min_cut(0, 1) == 5);\n    assert(disconnected.min_cut(0,\
    \ 2) == 0);\n\n    m1une::flow::GomoryHu<long long> rebuilt(2);\n    rebuilt.build();\n\
    \    assert(rebuilt.min_cut(0, 1) == 0);\n    rebuilt.add_edge(0, 1, 7);\n   \
    \ rebuilt.add_edge(0, 0, 100);\n    rebuilt.build();\n    assert(rebuilt.min_cut(0,\
    \ 1) == 7);\n\n    m1une::flow::GomoryHu<long long> singleton(1);\n    singleton.build();\n\
    \    assert(singleton.tree_edges().empty());\n\n    std::mt19937 random(123456789);\n\
    \    for (int iteration = 0; iteration < 200; iteration++) {\n        int n =\
    \ 2 + int(random() % 8);\n        struct InputEdge {\n            int u;\n   \
    \         int v;\n            long long cap;\n        };\n        std::vector<InputEdge>\
    \ edges;\n        m1une::flow::GomoryHu<long long> tree(n);\n        int m = random()\
    \ % (2 * n * n + 1);\n        for (int i = 0; i < m; i++) {\n            int u\
    \ = random() % n;\n            int v = random() % n;\n            long long cap\
    \ = random() % 1000001;\n            edges.push_back(InputEdge{u, v, cap});\n\
    \            tree.add_edge(u, v, cap);\n        }\n        tree.build();\n   \
    \     for (int s = 0; s < n; s++) {\n            for (int t = s + 1; t < n; t++)\
    \ {\n                m1une::flow::MaxFlow<long long> mf(n);\n                for\
    \ (const auto& edge : edges) {\n                    mf.add_edge(edge.u, edge.v,\
    \ edge.cap);\n                    mf.add_edge(edge.v, edge.u, edge.cap);\n   \
    \             }\n                assert(tree.min_cut(s, t) == mf.max_flow(s, t));\n\
    \            }\n        }\n    }\n}\n\nvoid test_bounded_flow() {\n    m1une::flow::BoundedFlow<long\
    \ long> st(4);\n    int a = st.add_edge(0, 1, 1, 3);\n    int b = st.add_edge(0,\
    \ 2, 0, 2);\n    int c = st.add_edge(1, 3, 1, 2);\n    int d = st.add_edge(2,\
    \ 3, 0, 2);\n    int e = st.add_edge(1, 2, 0, 1);\n    (void)a;\n    (void)b;\n\
    \    (void)c;\n    (void)d;\n    (void)e;\n\n    auto exact = st.feasible_st_flow(0,\
    \ 3, 3);\n    assert(exact.has_value());\n    std::vector<long long> balance(4,\
    \ 0);\n    for (const auto& edge : exact->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        balance[edge.from] += edge.flow;\n\
    \        balance[edge.to] -= edge.flow;\n    }\n    assert((balance == std::vector<long\
    \ long>{3, 0, 0, -3}));\n\n    auto too_much = st.feasible_st_flow(0, 3, 6);\n\
    \    assert(!too_much.has_value());\n\n    m1une::flow::BoundedFlow<long long>\
    \ bf(3);\n    int f01 = bf.add_edge(0, 1, 1, 3);\n    int f02 = bf.add_edge(0,\
    \ 2, 0, 4);\n    bf.add_edge(1, 2, 0, 2);\n    bf.add_supply(0, 4);\n    bf.add_demand(1,\
    \ 1);\n    bf.add_demand(2, 3);\n    assert(bf.balance(0) == 4);\n    auto bflow\
    \ = bf.feasible_flow();\n    assert(bflow.has_value());\n    assert(bflow->get_edge(f01).flow\
    \ >= 1);\n    assert(bflow->get_edge(f02).flow >= 0);\n    std::vector<long long>\
    \ b_balance(3, 0);\n    for (const auto& edge : bflow->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        b_balance[edge.from] += edge.flow;\n\
    \        b_balance[edge.to] -= edge.flow;\n    }\n    assert((b_balance == std::vector<long\
    \ long>{4, -1, -3}));\n\n    m1une::flow::BoundedFlow<long long> negative(2);\n\
    \    int neg = negative.add_edge(0, 1, -5, 5);\n    negative.add_demand(0, 3);\n\
    \    negative.add_supply(1, 3);\n    auto negative_flow = negative.feasible_flow();\n\
    \    assert(negative_flow.has_value());\n    assert(negative_flow->flow(neg) ==\
    \ -3);\n\n    m1une::flow::BoundedFlow<long long> impossible(2);\n    impossible.add_edge(0,\
    \ 1, 0, 1);\n    impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n\
    \    assert(!impossible.feasible_flow().has_value());\n\n    m1une::flow::BFlow<long\
    \ long> alias(1);\n    assert(alias.size() == 1);\n}\n\nvoid test_bounded_min_cost_flow()\
    \ {\n    m1une::flow::BoundedMinCostFlow<long long, long long> st(3);\n    st.reserve_edges(3);\n\
    \    int e01 = st.add_edge(0, 1, 1, 3, 2);\n    int e12 = st.add_edge(1, 2, 1,\
    \ 3, 1);\n    int e02 = st.add_edge(0, 2, 0, 3, 10);\n\n    auto exact = st.min_cost_st_flow(0,\
    \ 2, 3);\n    assert(exact.has_value());\n    assert(exact->cost == 9);\n    assert(exact->flow(e01)\
    \ == 3);\n    assert(exact->flow(e12) == 3);\n    assert(exact->flow(e02) == 0);\n\
    \    auto exact_polynomial = st.min_cost_st_flow_polynomial(0, 2, 3);\n    assert(exact_polynomial.has_value());\n\
    \    assert(exact_polynomial->cost == 9);\n    std::vector<long long> balance(3,\
    \ 0);\n    for (const auto& edge : exact->edges) {\n        assert(edge.lower\
    \ <= edge.flow && edge.flow <= edge.upper);\n        balance[edge.from] += edge.flow;\n\
    \        balance[edge.to] -= edge.flow;\n    }\n    assert((balance == std::vector<long\
    \ long>{3, 0, -3}));\n\n    m1une::flow::BoundedMinCostFlow<long long, long long>\
    \ bf(3);\n    int p01 = bf.add_edge(0, 1, 0, 2, 1);\n    int p12 = bf.add_edge(1,\
    \ 2, 0, 2, 1);\n    int p02 = bf.add_edge(0, 2, 0, 2, 5);\n    bf.add_supply(0,\
    \ 2);\n    bf.add_demand(2, 2);\n    auto bflow = bf.min_cost_flow();\n    assert(bflow.has_value());\n\
    \    assert(bflow->cost == 4);\n    assert(bflow->flow(p01) == 2);\n    assert(bflow->flow(p12)\
    \ == 2);\n    assert(bflow->flow(p02) == 0);\n\n    m1une::flow::BoundedMinCostFlow<long\
    \ long, long long> negative(2);\n    int neg = negative.add_edge(0, 1, -5, 5,\
    \ 2);\n    negative.add_demand(0, 3);\n    negative.add_supply(1, 3);\n    auto\
    \ negative_flow = negative.min_cost_flow();\n    assert(negative_flow.has_value());\n\
    \    assert(negative_flow->flow(neg) == -3);\n    assert(negative_flow->cost ==\
    \ -6);\n\n    m1une::flow::BoundedMinCostFlow<long long, long long> cycle(2);\n\
    \    int c01 = cycle.add_edge(0, 1, 0, 1, -5);\n    int c10 = cycle.add_edge(1,\
    \ 0, 0, 1, 3);\n    auto circulation = cycle.min_cost_flow();\n    assert(circulation.has_value());\n\
    \    assert(circulation->flow(c01) == 1);\n    assert(circulation->flow(c10) ==\
    \ 1);\n    assert(circulation->cost == -2);\n    auto polynomial_circulation =\
    \ cycle.min_cost_flow_polynomial();\n    assert(polynomial_circulation.has_value());\n\
    \    assert(polynomial_circulation->cost == -2);\n\n    using ImmediateFallback\
    \ = m1une::flow::BoundedMinCostFlow<\n        long long, long long, long long,\
    \ 0\n    >;\n    ImmediateFallback fallback_cycle(2);\n    fallback_cycle.add_edge(0,\
    \ 1, 0, 1, -5);\n    fallback_cycle.add_edge(1, 0, 0, 1, 3);\n    auto fallback_circulation\
    \ = fallback_cycle.min_cost_flow();\n    assert(fallback_circulation.has_value());\n\
    \    assert(fallback_circulation->cost == -2);\n\n    m1une::flow::BoundedMinCostFlow<long\
    \ long, long long> impossible(2);\n    impossible.add_edge(0, 1, 0, 1, 0);\n \
    \   impossible.add_supply(0, 2);\n    impossible.add_demand(1, 2);\n    assert(!impossible.min_cost_flow().has_value());\n\
    \n    using WideCostFlow = m1une::flow::BoundedMinCostFlow<\n        long long,\
    \ long long, __int128_t\n    >;\n    WideCostFlow wide_cost(1);\n    wide_cost.reserve_edges(1);\n\
    \    constexpr long long trillion = 1000000000000LL;\n    wide_cost.add_edge(0,\
    \ 0, trillion, trillion, trillion);\n    auto wide_result = wide_cost.min_cost_flow();\n\
    \    assert(wide_result.has_value());\n    assert(wide_result->cost == __int128_t(trillion)\
    \ * trillion);\n\n    std::mt19937 random(987654321);\n    for (int iteration\
    \ = 0; iteration < 500; iteration++) {\n        int n = 1 + int(random() % 4);\n\
    \        int m = int(random() % 7);\n        struct SmallEdge {\n            int\
    \ from;\n            int to;\n            long long lower;\n            long long\
    \ upper;\n            long long cost;\n        };\n        std::vector<SmallEdge>\
    \ edges;\n        m1une::flow::BoundedMinCostFlow<long long, long long> solver(n);\n\
    \        for (int i = 0; i < m; i++) {\n            int from = int(random() %\
    \ n);\n            int to = int(random() % n);\n            long long lower =\
    \ static_cast<long long>(random() % 5) - 2;\n            long long upper = lower\
    \ + static_cast<long long>(random() % 4);\n            long long cost = static_cast<long\
    \ long>(random() % 9) - 4;\n            edges.push_back(SmallEdge{from, to, lower,\
    \ upper, cost});\n            solver.add_edge(from, to, lower, upper, cost);\n\
    \        }\n\n        std::vector<long long> required_balance(n, 0);\n       \
    \ long long balance_sum = 0;\n        for (int vertex = 0; vertex + 1 < n; vertex++)\
    \ {\n            required_balance[vertex] =\n                static_cast<long\
    \ long>(random() % 7) - 3;\n            balance_sum += required_balance[vertex];\n\
    \        }\n        required_balance.back() = -balance_sum;\n\n        bool feasible\
    \ = false;\n        long long best_cost = 0;\n        std::vector<long long> flow(m);\n\
    \        auto enumerate = [&](auto&& self, int edge_id) -> void {\n          \
    \  if (edge_id != m) {\n                for (\n                    flow[edge_id]\
    \ = edges[edge_id].lower;\n                    flow[edge_id] <= edges[edge_id].upper;\n\
    \                    flow[edge_id]++\n                ) {\n                  \
    \  self(self, edge_id + 1);\n                }\n                return;\n    \
    \        }\n\n            std::vector<long long> actual_balance(n, 0);\n     \
    \       long long cost = 0;\n            for (int i = 0; i < m; i++) {\n     \
    \           actual_balance[edges[i].from] += flow[i];\n                actual_balance[edges[i].to]\
    \ -= flow[i];\n                cost += flow[i] * edges[i].cost;\n            }\n\
    \            if (actual_balance != required_balance) return;\n            if (!feasible\
    \ || cost < best_cost) best_cost = cost;\n            feasible = true;\n     \
    \   };\n        enumerate(enumerate, 0);\n\n        auto validate_result = [&](const\
    \ auto& result) {\n            assert(result.has_value() == feasible);\n     \
    \       if (!result.has_value()) return;\n            assert(result->cost == best_cost);\n\
    \n            std::vector<long long> actual_balance(n, 0);\n            for (const\
    \ auto& edge : result->edges) {\n                assert(edge.lower <= edge.flow\
    \ && edge.flow <= edge.upper);\n                actual_balance[edge.from] += edge.flow;\n\
    \                actual_balance[edge.to] -= edge.flow;\n                long long\
    \ reduced_cost =\n                    edge.cost\n                    + result->potential[edge.from]\n\
    \                    - result->potential[edge.to];\n                if (edge.flow\
    \ < edge.upper) assert(0 <= reduced_cost);\n                if (edge.lower < edge.flow)\
    \ assert(reduced_cost <= 0);\n            }\n            assert(actual_balance\
    \ == required_balance);\n        };\n\n        validate_result(solver.min_cost_flow(required_balance));\n\
    \        validate_result(solver.min_cost_flow_polynomial(required_balance));\n\
    \    }\n\n    m1une::flow::BMinCostFlow<long long, long long> alias(1);\n    assert(alias.size()\
    \ == 1);\n    m1une::flow::BMinCostFlow<long long, long long, __int128_t> wide_alias(1);\n\
    \    assert(wide_alias.size() == 1);\n    m1une::flow::BMinCostFlow<long long,\
    \ long long, long long, 0>\n        fallback_alias(1);\n    assert(fallback_alias.size()\
    \ == 1);\n}\n\nvoid test_min_cost_flow() {\n    m1une::flow::MinCostFlow<long\
    \ long, long long> mcf(4);\n    mcf.add_edge(0, 1, 2, 1);\n    mcf.add_edge(0,\
    \ 2, 1, 2);\n    mcf.add_edge(1, 2, 1, 0);\n    mcf.add_edge(1, 3, 1, 3);\n  \
    \  mcf.add_edge(2, 3, 2, 1);\n\n    auto result = mcf.flow(0, 3, 2);\n    assert(result.first\
    \ == 2);\n    assert(result.second == 5);\n    auto edges = mcf.edges();\n   \
    \ long long total_source_flow = 0;\n    for (const auto& e : edges) {\n      \
    \  if (e.from == 0) total_source_flow += e.flow;\n        assert(0 <= e.flow &&\
    \ e.flow <= e.cap);\n    }\n    assert(total_source_flow == 2);\n\n    m1une::flow::MinCostFlow<long\
    \ long, long long> negative(3);\n    negative.add_edge(0, 1, 1, -5);\n    negative.add_edge(1,\
    \ 2, 1, 2);\n    negative.add_edge(0, 2, 1, 10);\n    auto slope = negative.slope(0,\
    \ 2, 2);\n    std::vector<std::pair<long long, long long>> expected_slope = {\n\
    \        std::pair<long long, long long>{0, 0},\n        std::pair<long long,\
    \ long long>{1, -3},\n        std::pair<long long, long long>{2, 7},\n    };\n\
    \    assert(slope == expected_slope);\n\n    std::mt19937 random(31415926);\n\
    \    for (int iteration = 0; iteration < 200; iteration++) {\n        int n =\
    \ 2 + int(random() % 7);\n        int m = int(random() % 30);\n        long long\
    \ flow_limit = random() % 16;\n        m1une::flow::MinCostFlow<long long, long\
    \ long> tested(n);\n        m1une::flow::BoundedMinCostFlow<long long, long long>\
    \ expected(n);\n        m1une::flow::MaxFlow<long long> maximum(n);\n        tested.reserve_edges(m);\n\
    \        expected.reserve_edges(m);\n        maximum.reserve_edges(m);\n     \
    \   for (int edge = 0; edge < m; edge++) {\n            int from = int(random()\
    \ % (n - 1));\n            int to = from + 1 + int(random() % (n - from - 1));\n\
    \            long long cap = random() % 6;\n            long long cost = int(random()\
    \ % 21) - 10;\n            tested.add_edge(from, to, cap, cost);\n           \
    \ expected.add_edge(from, to, 0, cap, cost);\n            maximum.add_edge(from,\
    \ to, cap);\n        }\n        long long sent = maximum.max_flow(0, n - 1, flow_limit);\n\
    \        auto expected_result = expected.min_cost_st_flow(0, n - 1, sent);\n \
    \       assert(expected_result.has_value());\n        auto tested_result = tested.flow(0,\
    \ n - 1, flow_limit);\n        assert(tested_result.first == sent);\n        assert(tested_result.second\
    \ == expected_result->cost);\n    }\n\n    // At least eight terminal arcs are\
    \ required, exercising the guarded\n    // one-shot network-simplex path rather\
    \ than successive shortest paths.\n    m1une::flow::MinCostFlow<long long, long\
    \ long> fast(10);\n    m1une::flow::MinCostFlow<long long, long long> reference(10);\n\
    \    fast.reserve_edges(64);\n    reference.reserve_edges(64);\n    for (int v\
    \ = 1; v <= 8; v++) {\n        fast.add_edge(0, v, 1, v);\n        fast.add_edge(v,\
    \ 9, 1, 10 - v);\n        reference.add_edge(0, v, 1, v);\n        reference.add_edge(v,\
    \ 9, 1, 10 - v);\n    }\n    while (fast.edge_count() < 64) {\n        int from\
    \ = 1 + fast.edge_count() % 8;\n        int to = 1 + (fast.edge_count() * 3 +\
    \ 1) % 8;\n        if (from == to) to = to == 8 ? 1 : to + 1;\n        fast.add_edge(from,\
    \ to, 1, 100);\n        reference.add_edge(from, to, 1, 100);\n    }\n    auto\
    \ fast_result = fast.flow(0, 9, 10);\n    auto reference_result = reference.slope(0,\
    \ 9, 10).back();\n    assert(fast_result == reference_result);\n    std::pair<long\
    \ long, long long> expected_fast_result(8, 80);\n    assert(fast_result == expected_fast_result);\n\
    \    assert(fast.flow(0, 9).first == 0);\n\n    // After one shortest-path augmentation,\
    \ a limit below both remaining\n    // terminal capacities exercises the exact\
    \ residual s-t solve without\n    // terminal contraction, including negative-cost\
    \ reverse arcs.\n    m1une::flow::MinCostFlow<long long, long long> partial(12);\n\
    \    m1une::flow::MinCostFlow<long long, long long> partial_reference(12);\n \
    \   for (int v = 1; v <= 10; v++) {\n        partial.add_edge(0, v, 1, v);\n \
    \       partial.add_edge(v, 11, 1, 0);\n        partial_reference.add_edge(0,\
    \ v, 1, v);\n        partial_reference.add_edge(v, 11, 1, 0);\n    }\n    while\
    \ (partial.edge_count() < 64) {\n        int from = 1 + partial.edge_count() %\
    \ 10;\n        int to = 1 + (partial.edge_count() * 7 + 1) % 10;\n        if (from\
    \ == to) to = to == 10 ? 1 : to + 1;\n        partial.add_edge(from, to, 1, 100);\n\
    \        partial_reference.add_edge(from, to, 1, 100);\n    }\n    assert(\n \
    \       partial.flow(0, 11, 1) ==\n        partial_reference.slope(0, 11, 1).back()\n\
    \    );\n    assert(\n        partial.flow(0, 11, 8) ==\n        partial_reference.slope(0,\
    \ 11, 8).back()\n    );\n    assert(partial.flow(0, 11) == partial_reference.slope(0,\
    \ 11).back());\n\n    // The terminal cut permits eight units but an internal\
    \ bottleneck permits\n    // only four, exercising the max-flow fallback before\
    \ the exact-cost solve.\n    m1une::flow::MinCostFlow<long long, long long> bottleneck(20);\n\
    \    for (int v = 1; v <= 8; v++) {\n        bottleneck.add_edge(0, v, 1, 0);\n\
    \        bottleneck.add_edge(v, 9, 1, 0);\n        bottleneck.add_edge(10, v +\
    \ 10, 1, 0);\n        bottleneck.add_edge(v + 10, 19, 1, 0);\n    }\n    bottleneck.add_edge(9,\
    \ 10, 4, 1);\n    while (bottleneck.edge_count() < 64) {\n        int from = 1\
    \ + bottleneck.edge_count() % 8;\n        int to = 1 + (bottleneck.edge_count()\
    \ * 5 + 1) % 8;\n        if (from == to) to = to == 8 ? 1 : to + 1;\n        bottleneck.add_edge(from,\
    \ to, 1, 100);\n    }\n    std::pair<long long, long long> expected_bottleneck(4,\
    \ 4);\n    assert(bottleneck.flow(0, 19, 8) == expected_bottleneck);\n\n    //\
    \ Randomized comparisons cover the terminal-contraction optimization on\n    //\
    \ feasible non-negative-cost instances.\n    for (int iteration = 0; iteration\
    \ < 100; iteration++) {\n        constexpr int n = 18;\n        m1une::flow::MinCostFlow<long\
    \ long, long long> adaptive(n);\n        m1une::flow::MinCostFlow<long long, long\
    \ long> shortest_paths(n);\n        adaptive.reserve_edges(80);\n        shortest_paths.reserve_edges(80);\n\
    \        for (int v = 1; v <= 8; v++) {\n            long long first_cost = random()\
    \ % 11;\n            long long middle_cost = random() % 11;\n            long\
    \ long last_cost = random() % 11;\n            adaptive.add_edge(0, v, 1, first_cost);\n\
    \            adaptive.add_edge(v, v + 8, 1, middle_cost);\n            adaptive.add_edge(v\
    \ + 8, 17, 1, last_cost);\n            shortest_paths.add_edge(0, v, 1, first_cost);\n\
    \            shortest_paths.add_edge(v, v + 8, 1, middle_cost);\n            shortest_paths.add_edge(v\
    \ + 8, 17, 1, last_cost);\n        }\n        while (adaptive.edge_count() < 80)\
    \ {\n            int from = 1 + int(random() % 16);\n            int to = 1 +\
    \ int(random() % 16);\n            if (from == to) to = to == 16 ? 1 : to + 1;\n\
    \            long long cap = 1 + random() % 3;\n            long long cost = random()\
    \ % 21;\n            adaptive.add_edge(from, to, cap, cost);\n            shortest_paths.add_edge(from,\
    \ to, cap, cost);\n        }\n        assert(\n            adaptive.flow(0, 17,\
    \ 8) ==\n            shortest_paths.slope(0, 17, 8).back()\n        );\n    }\n\
    }\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_max_flow();\n    test_gomory_hu();\n    test_bounded_flow();\n\
    \    test_bounded_min_cost_flow();\n    test_min_cost_flow();\n\n    long long\
    \ a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - graph/flow/flow.hpp
  - graph/flow/bounded_flow.hpp
  - graph/flow/max_flow.hpp
  - graph/flow/bounded_min_cost_flow.hpp
  - graph/flow/gomory_hu.hpp
  - graph/flow/min_cost_flow.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/flow/flow_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/flow/flow_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/flow/flow_algorithms.test.cpp
- /verify/verify/graph/flow/flow_algorithms.test.cpp.html
title: verify/graph/flow/flow_algorithms.test.cpp
---
