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
    path: graph/flow/gomory_hu.hpp
    title: Gomory-Hu Tree
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: graph/flow/min_cost_flow.hpp
    title: Min Cost Flow
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/flow/flow_algorithms.test.cpp
    title: verify/graph/flow/flow_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/flow/flow.hpp\"\n\n\n\n#line 1 \"graph/flow/bounded_flow.hpp\"\
    \n\n\n\n#include <cassert>\n#include <optional>\n#include <vector>\n\n#line 1\
    \ \"graph/flow/max_flow.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"graph/flow/max_flow.hpp\"\
    \n#include <cstddef>\n#include <limits>\n#line 9 \"graph/flow/max_flow.hpp\"\n\
    \nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow\
    \ {\n    struct Edge {\n        int from;\n        int to;\n        Cap cap;\n\
    \        Cap flow;\n    };\n\n   private:\n    struct InternalEdge {\n       \
    \ int to;\n        int rev;\n        Cap cap;\n    };\n\n    struct Position {\n\
    \        int from;\n        int edge;\n    };\n\n    int _n;\n    std::vector<Position>\
    \ _pos;\n    std::vector<std::vector<InternalEdge>> _g;\n\n    Cap push_relabel(int\
    \ s, int t) {\n        const std::size_t edge_count = _pos.size();\n        const\
    \ std::size_t source_degree = _g[s].size();\n        const std::size_t sink_degree\
    \ = _g[t].size();\n        const std::size_t terminal_degree =\n            std::min(source_degree,\
    \ sink_degree);\n        const bool dense = edge_count >= 5 * std::size_t(_n);\n\
    \        const std::size_t wide_threshold =\n            4 * (edge_count / std::size_t(_n)\
    \ + 1);\n        // Reverse input order defeats several ordering-sensitive hard\
    \ cases,\n        // while forward order is substantially better on ordinary random\n\
    \        // graphs with medium-width terminals.\n        const bool reverse_scan\
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
    #include <utility>\n#line 14 \"graph/flow/bounded_min_cost_flow.hpp\"\n\nnamespace\
    \ m1une {\nnamespace flow {\n\ntemplate <\n    class Cap,\n    class Cost,\n \
    \   class TotalCost = Cost,\n    std::size_t PivotLimitFactor = 8\n>\nstruct BoundedMinCostFlow\
    \ {\n    static_assert(std::numeric_limits<Cap>::is_integer);\n    static_assert(std::numeric_limits<Cap>::is_signed);\n\
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
    \n\n\n"
  code: '#ifndef M1UNE_FLOW_FLOW_HPP

    #define M1UNE_FLOW_FLOW_HPP 1


    #include "bounded_flow.hpp"

    #include "bounded_min_cost_flow.hpp"

    #include "gomory_hu.hpp"

    #include "max_flow.hpp"

    #include "min_cost_flow.hpp"


    #endif  // M1UNE_FLOW_FLOW_HPP

    '
  dependsOn:
  - graph/flow/bounded_flow.hpp
  - graph/flow/max_flow.hpp
  - graph/flow/bounded_min_cost_flow.hpp
  - graph/flow/gomory_hu.hpp
  - graph/flow/min_cost_flow.hpp
  isVerificationFile: false
  path: graph/flow/flow.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-16 02:08:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/flow/flow_algorithms.test.cpp
documentation_of: graph/flow/flow.hpp
layout: document
title: Flow
---

## Overview

`graph/flow/flow.hpp` includes flow-network algorithms. Flow networks are
directed: an edge `u -> v` only sends flow from `u` to `v`.

For an undirected capacity between `u` and `v`, `MaxFlow` provides
`add_undirected_edge(u, v, cap)`, which stores one shared-capacity residual
pair. Other directed-flow classes represent it with two directed edges.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/flow/bounded_flow.hpp` | Directed flow network | Feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/flow/bounded_min_cost_flow.hpp` | Directed flow network | Minimum-cost feasible flow with lower/upper bounds, balances, and negative flow intervals. |
| `graph/flow/gomory_hu.hpp` | Undirected capacitated graph | Gomory-Hu cut tree and pairwise minimum-cut queries. |
| `graph/flow/max_flow.hpp` | Directed or shared-capacity undirected network | Optimized Dinic and highest-label push-relabel maximum flow, plus minimum cut. |
| `graph/flow/min_cost_flow.hpp` | Directed flow network | Minimum-cost flow with potentials. |

## Complexity

This header is an include bundle and provides no runtime operation by itself.
See the included algorithm pages for public interfaces and complexities.
