---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/project_selection.test.cpp
    title: verify/optimization/project_selection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/simplex.test.cpp
    title: verify/optimization/simplex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"optimization/project_selection.hpp\"\n\n\n\n#include <cassert>\n\
    #include <limits>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"graph/flow/max_flow.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"\
    graph/flow/max_flow.hpp\"\n#include <cstddef>\n#line 9 \"graph/flow/max_flow.hpp\"\
    \n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow\
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
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 11 \"optimization/project_selection.hpp\"\
    \n\nnamespace m1une {\nnamespace opt {\n\ntemplate <class T>\nstruct ProjectSelectionResult\
    \ {\n    bool feasible;\n    T max_gain;\n    std::vector<bool> selected;\n\n\
    \    bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nclass ProjectSelection {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct Arc {\n        int from;\n        int\
    \ to;\n        T cap;\n    };\n\n    static constexpr int source = -1;\n    static\
    \ constexpr int sink = -2;\n\n    int _project_count;\n    int _vertex_count;\n\
    \    T _offset = T();\n    T _finite_cap_sum = T();\n    std::vector<Arc> _arcs;\n\
    \    std::vector<std::pair<int, int>> _hard_arcs;\n\n    void assert_project(int\
    \ project) const {\n        (void)project;\n        assert(0 <= project && project\
    \ < _project_count);\n    }\n\n    void assert_vertex(int vertex) const {\n  \
    \      (void)vertex;\n        assert(0 <= vertex && vertex < _vertex_count);\n\
    \    }\n\n    void add_offset(T value) {\n        if (value > T()) {\n       \
    \     assert(_offset <= std::numeric_limits<T>::max() - value);\n        } else\
    \ if (value < T()) {\n            assert(_offset >= std::numeric_limits<T>::lowest()\
    \ - value);\n        }\n        _offset += value;\n    }\n\n    T nonnegative_difference(T\
    \ large, T small) const {\n        assert(small <= large);\n        if (small\
    \ < T()) {\n            assert(large <= std::numeric_limits<T>::max() + small);\n\
    \        }\n        return large - small;\n    }\n\n    void add_arc(int from,\
    \ int to, T cap) {\n        assert(cap >= T());\n        if (from == to) return;\n\
    \        assert(cap <= std::numeric_limits<T>::max() - _finite_cap_sum);\n   \
    \     _finite_cap_sum += cap;\n        _arcs.push_back(Arc{from, to, cap});\n\
    \    }\n\n    void add_hard_arc(int from, int to) {\n        if (from == to) return;\n\
    \        _hard_arcs.emplace_back(from, to);\n    }\n\n    void add_vertex_gain(int\
    \ vertex, T gain_if_selected, T gain_if_unselected) {\n        assert_vertex(vertex);\n\
    \        if (gain_if_selected >= gain_if_unselected) {\n            add_offset(gain_if_selected);\n\
    \            add_arc(source, vertex,\n                    nonnegative_difference(gain_if_selected,\
    \ gain_if_unselected));\n        } else {\n            add_offset(gain_if_unselected);\n\
    \            add_arc(vertex, sink,\n                    nonnegative_difference(gain_if_unselected,\
    \ gain_if_selected));\n        }\n    }\n\n    int add_auxiliary_vertex() {\n\
    \        return _vertex_count++;\n    }\n\n   public:\n    ProjectSelection()\
    \ : ProjectSelection(0) {}\n\n    explicit ProjectSelection(int project_count)\n\
    \        : _project_count(project_count), _vertex_count(project_count) {\n   \
    \     assert(project_count >= 0);\n    }\n\n    int size() const {\n        return\
    \ _project_count;\n    }\n\n    void add_gain(int project, T gain_if_selected)\
    \ {\n        add_gain(project, gain_if_selected, T());\n    }\n\n    void add_gain(int\
    \ project, T gain_if_selected, T gain_if_unselected) {\n        assert_project(project);\n\
    \        add_vertex_gain(project, gain_if_selected, gain_if_unselected);\n   \
    \ }\n\n    void add_penalty(int selected_project, int unselected_project, T penalty)\
    \ {\n        assert_project(selected_project);\n        assert_project(unselected_project);\n\
    \        add_arc(selected_project, unselected_project, penalty);\n    }\n\n  \
    \  void add_penalty_if_different(int project_a, int project_b, T penalty) {\n\
    \        assert_project(project_a);\n        assert_project(project_b);\n    \
    \    add_arc(project_a, project_b, penalty);\n        add_arc(project_b, project_a,\
    \ penalty);\n    }\n\n    void add_gain_if_same(int project_a, int project_b,\
    \ T gain) {\n        assert(gain >= T());\n        add_offset(gain);\n       \
    \ add_penalty_if_different(project_a, project_b, gain);\n    }\n\n    void add_hard_implication(int\
    \ selected_project, int required_project) {\n        assert_project(selected_project);\n\
    \        assert_project(required_project);\n        add_hard_arc(selected_project,\
    \ required_project);\n    }\n\n    void force_selected(int project) {\n      \
    \  assert_project(project);\n        add_hard_arc(source, project);\n    }\n\n\
    \    void force_unselected(int project) {\n        assert_project(project);\n\
    \        add_hard_arc(project, sink);\n    }\n\n    void add_gain_if_all_selected(const\
    \ std::vector<int>& projects, T gain) {\n        assert(gain >= T());\n      \
    \  for (int project : projects) assert_project(project);\n        if (projects.empty())\
    \ {\n            add_offset(gain);\n            return;\n        }\n        if\
    \ (projects.size() == 1) {\n            add_vertex_gain(projects[0], gain, T());\n\
    \            return;\n        }\n        if (projects.size() == 2) {\n       \
    \     add_vertex_gain(projects[0], gain, T());\n            add_arc(projects[0],\
    \ projects[1], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, gain, T());\n\
    \        for (int project : projects) add_hard_arc(auxiliary, project);\n    }\n\
    \n    void add_gain_if_all_unselected(const std::vector<int>& projects, T gain)\
    \ {\n        assert(gain >= T());\n        for (int project : projects) assert_project(project);\n\
    \        if (projects.empty()) {\n            add_offset(gain);\n            return;\n\
    \        }\n        if (projects.size() == 1) {\n            add_vertex_gain(projects[0],\
    \ T(), gain);\n            return;\n        }\n        if (projects.size() ==\
    \ 2) {\n            add_vertex_gain(projects[0], T(), gain);\n            add_arc(projects[1],\
    \ projects[0], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, T(), gain);\n\
    \        for (int project : projects) add_hard_arc(project, auxiliary);\n    }\n\
    \n    ProjectSelectionResult<T> solve() const {\n        int s = _vertex_count;\n\
    \        int t = s + 1;\n        flow::MaxFlow<T> max_flow(_vertex_count + 2);\n\
    \n        auto vertex_id = [&](int vertex) {\n            if (vertex == source)\
    \ return s;\n            if (vertex == sink) return t;\n            return vertex;\n\
    \        };\n\n        for (const auto& arc : _arcs) {\n            max_flow.add_edge(vertex_id(arc.from),\
    \ vertex_id(arc.to), arc.cap);\n        }\n\n        T hard_cap = T();\n     \
    \   if (!_hard_arcs.empty()) {\n            assert(_finite_cap_sum < std::numeric_limits<T>::max());\n\
    \            hard_cap = _finite_cap_sum + T(1);\n            for (auto [from,\
    \ to] : _hard_arcs) {\n                max_flow.add_edge(vertex_id(from), vertex_id(to),\
    \ hard_cap);\n            }\n        }\n\n        T cut_cost =\n            _hard_arcs.empty()\
    \ ? max_flow.max_flow(s, t) : max_flow.max_flow(s, t, hard_cap);\n        ProjectSelectionResult<T>\
    \ result;\n        result.feasible = _hard_arcs.empty() || cut_cost < hard_cap;\n\
    \        result.max_gain = T();\n        result.selected.assign(_project_count,\
    \ false);\n        if (!result.feasible) return result;\n\n        assert(_offset\
    \ >= std::numeric_limits<T>::lowest() + cut_cost);\n        result.max_gain =\
    \ _offset - cut_cost;\n        auto source_side = max_flow.min_cut(s);\n     \
    \   for (int project = 0; project < _project_count; project++) {\n           \
    \ result.selected[project] = source_side[project];\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP\n#define M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP\
    \ 1\n\n#include <cassert>\n#include <limits>\n#include <type_traits>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../graph/flow/max_flow.hpp\"\n\n\
    namespace m1une {\nnamespace opt {\n\ntemplate <class T>\nstruct ProjectSelectionResult\
    \ {\n    bool feasible;\n    T max_gain;\n    std::vector<bool> selected;\n\n\
    \    bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nclass ProjectSelection {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct Arc {\n        int from;\n        int\
    \ to;\n        T cap;\n    };\n\n    static constexpr int source = -1;\n    static\
    \ constexpr int sink = -2;\n\n    int _project_count;\n    int _vertex_count;\n\
    \    T _offset = T();\n    T _finite_cap_sum = T();\n    std::vector<Arc> _arcs;\n\
    \    std::vector<std::pair<int, int>> _hard_arcs;\n\n    void assert_project(int\
    \ project) const {\n        (void)project;\n        assert(0 <= project && project\
    \ < _project_count);\n    }\n\n    void assert_vertex(int vertex) const {\n  \
    \      (void)vertex;\n        assert(0 <= vertex && vertex < _vertex_count);\n\
    \    }\n\n    void add_offset(T value) {\n        if (value > T()) {\n       \
    \     assert(_offset <= std::numeric_limits<T>::max() - value);\n        } else\
    \ if (value < T()) {\n            assert(_offset >= std::numeric_limits<T>::lowest()\
    \ - value);\n        }\n        _offset += value;\n    }\n\n    T nonnegative_difference(T\
    \ large, T small) const {\n        assert(small <= large);\n        if (small\
    \ < T()) {\n            assert(large <= std::numeric_limits<T>::max() + small);\n\
    \        }\n        return large - small;\n    }\n\n    void add_arc(int from,\
    \ int to, T cap) {\n        assert(cap >= T());\n        if (from == to) return;\n\
    \        assert(cap <= std::numeric_limits<T>::max() - _finite_cap_sum);\n   \
    \     _finite_cap_sum += cap;\n        _arcs.push_back(Arc{from, to, cap});\n\
    \    }\n\n    void add_hard_arc(int from, int to) {\n        if (from == to) return;\n\
    \        _hard_arcs.emplace_back(from, to);\n    }\n\n    void add_vertex_gain(int\
    \ vertex, T gain_if_selected, T gain_if_unselected) {\n        assert_vertex(vertex);\n\
    \        if (gain_if_selected >= gain_if_unselected) {\n            add_offset(gain_if_selected);\n\
    \            add_arc(source, vertex,\n                    nonnegative_difference(gain_if_selected,\
    \ gain_if_unselected));\n        } else {\n            add_offset(gain_if_unselected);\n\
    \            add_arc(vertex, sink,\n                    nonnegative_difference(gain_if_unselected,\
    \ gain_if_selected));\n        }\n    }\n\n    int add_auxiliary_vertex() {\n\
    \        return _vertex_count++;\n    }\n\n   public:\n    ProjectSelection()\
    \ : ProjectSelection(0) {}\n\n    explicit ProjectSelection(int project_count)\n\
    \        : _project_count(project_count), _vertex_count(project_count) {\n   \
    \     assert(project_count >= 0);\n    }\n\n    int size() const {\n        return\
    \ _project_count;\n    }\n\n    void add_gain(int project, T gain_if_selected)\
    \ {\n        add_gain(project, gain_if_selected, T());\n    }\n\n    void add_gain(int\
    \ project, T gain_if_selected, T gain_if_unselected) {\n        assert_project(project);\n\
    \        add_vertex_gain(project, gain_if_selected, gain_if_unselected);\n   \
    \ }\n\n    void add_penalty(int selected_project, int unselected_project, T penalty)\
    \ {\n        assert_project(selected_project);\n        assert_project(unselected_project);\n\
    \        add_arc(selected_project, unselected_project, penalty);\n    }\n\n  \
    \  void add_penalty_if_different(int project_a, int project_b, T penalty) {\n\
    \        assert_project(project_a);\n        assert_project(project_b);\n    \
    \    add_arc(project_a, project_b, penalty);\n        add_arc(project_b, project_a,\
    \ penalty);\n    }\n\n    void add_gain_if_same(int project_a, int project_b,\
    \ T gain) {\n        assert(gain >= T());\n        add_offset(gain);\n       \
    \ add_penalty_if_different(project_a, project_b, gain);\n    }\n\n    void add_hard_implication(int\
    \ selected_project, int required_project) {\n        assert_project(selected_project);\n\
    \        assert_project(required_project);\n        add_hard_arc(selected_project,\
    \ required_project);\n    }\n\n    void force_selected(int project) {\n      \
    \  assert_project(project);\n        add_hard_arc(source, project);\n    }\n\n\
    \    void force_unselected(int project) {\n        assert_project(project);\n\
    \        add_hard_arc(project, sink);\n    }\n\n    void add_gain_if_all_selected(const\
    \ std::vector<int>& projects, T gain) {\n        assert(gain >= T());\n      \
    \  for (int project : projects) assert_project(project);\n        if (projects.empty())\
    \ {\n            add_offset(gain);\n            return;\n        }\n        if\
    \ (projects.size() == 1) {\n            add_vertex_gain(projects[0], gain, T());\n\
    \            return;\n        }\n        if (projects.size() == 2) {\n       \
    \     add_vertex_gain(projects[0], gain, T());\n            add_arc(projects[0],\
    \ projects[1], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, gain, T());\n\
    \        for (int project : projects) add_hard_arc(auxiliary, project);\n    }\n\
    \n    void add_gain_if_all_unselected(const std::vector<int>& projects, T gain)\
    \ {\n        assert(gain >= T());\n        for (int project : projects) assert_project(project);\n\
    \        if (projects.empty()) {\n            add_offset(gain);\n            return;\n\
    \        }\n        if (projects.size() == 1) {\n            add_vertex_gain(projects[0],\
    \ T(), gain);\n            return;\n        }\n        if (projects.size() ==\
    \ 2) {\n            add_vertex_gain(projects[0], T(), gain);\n            add_arc(projects[1],\
    \ projects[0], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, T(), gain);\n\
    \        for (int project : projects) add_hard_arc(project, auxiliary);\n    }\n\
    \n    ProjectSelectionResult<T> solve() const {\n        int s = _vertex_count;\n\
    \        int t = s + 1;\n        flow::MaxFlow<T> max_flow(_vertex_count + 2);\n\
    \n        auto vertex_id = [&](int vertex) {\n            if (vertex == source)\
    \ return s;\n            if (vertex == sink) return t;\n            return vertex;\n\
    \        };\n\n        for (const auto& arc : _arcs) {\n            max_flow.add_edge(vertex_id(arc.from),\
    \ vertex_id(arc.to), arc.cap);\n        }\n\n        T hard_cap = T();\n     \
    \   if (!_hard_arcs.empty()) {\n            assert(_finite_cap_sum < std::numeric_limits<T>::max());\n\
    \            hard_cap = _finite_cap_sum + T(1);\n            for (auto [from,\
    \ to] : _hard_arcs) {\n                max_flow.add_edge(vertex_id(from), vertex_id(to),\
    \ hard_cap);\n            }\n        }\n\n        T cut_cost =\n            _hard_arcs.empty()\
    \ ? max_flow.max_flow(s, t) : max_flow.max_flow(s, t, hard_cap);\n        ProjectSelectionResult<T>\
    \ result;\n        result.feasible = _hard_arcs.empty() || cut_cost < hard_cap;\n\
    \        result.max_gain = T();\n        result.selected.assign(_project_count,\
    \ false);\n        if (!result.feasible) return result;\n\n        assert(_offset\
    \ >= std::numeric_limits<T>::lowest() + cut_cost);\n        result.max_gain =\
    \ _offset - cut_cost;\n        auto source_side = max_flow.min_cut(s);\n     \
    \   for (int project = 0; project < _project_count; project++) {\n           \
    \ result.selected[project] = source_side[project];\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP\n"
  dependsOn:
  - graph/flow/max_flow.hpp
  isVerificationFile: false
  path: optimization/project_selection.hpp
  requiredBy:
  - optimization/all.hpp
  timestamp: '2026-07-15 23:21:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/simplex.test.cpp
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
documentation_of: optimization/project_selection.hpp
layout: document
title: Project Selection
---

## Overview

`ProjectSelection<T>` chooses a subset of binary projects that maximizes total
gain. Besides a gain or cost for each individual choice, it supports implication
penalties, hard implications, forced choices, and several common group rewards.

The problem is reduced to a minimum `s-t` cut and solved with Dinic's algorithm.
This is substantially faster and more predictable than a general integer
programming solver for objectives that fit the supported forms.

Project `i` is **selected** when `result.selected[i]` is true. Gains increase the
objective and penalties decrease it. A cost of `c` for selecting project `i`
can therefore be written as `add_gain(i, -c)`.

## Supported Objective Terms

All gains and penalties are additive.

| Call | Contribution to the objective |
| --- | --- |
| `add_gain(i, selected_gain)` | Adds `selected_gain` if `i` is selected. |
| `add_gain(i, selected_gain, unselected_gain)` | Adds the gain corresponding to the choice for `i`. |
| `add_penalty(i, j, penalty)` | Subtracts `penalty` exactly when `i` is selected and `j` is unselected. |
| `add_penalty_if_different(i, j, penalty)` | Subtracts `penalty` when exactly one of `i` and `j` is selected. |
| `add_gain_if_same(i, j, gain)` | Adds `gain` when `i` and `j` make the same choice. |
| `add_gain_if_all_selected(projects, gain)` | Adds `gain` when every listed project is selected. |
| `add_gain_if_all_unselected(projects, gain)` | Adds `gain` when every listed project is unselected. |

Every `penalty` argument must be non-negative. The `gain` passed to
`add_gain_if_same` and the two group methods must also be non-negative. The
group methods treat an empty list as vacuously satisfying the condition, so
their gain is always added.

`add_penalty(i, j, penalty)` is the low-level finite implication primitive. It
is useful for statements such as “choosing `i` without choosing `j` loses 20.”
It does not forbid that combination; use `add_hard_implication` when it must be
impossible.

Not every Boolean objective can be represented by one minimum cut. In
particular, a positive reward for “at least one is selected” or a penalty for
“both are selected” is not generally supported without reformulating the
problem. The methods above are exactly the forms provided by this interface.

## Reduction to Minimum Cut

The source side of the cut represents selected projects, and the sink side
represents unselected projects.

- A directed edge from `i` to `j` crosses the cut exactly when `i` is selected
  and `j` is unselected, so its capacity is the corresponding penalty.
- A unary gain is converted into a constant offset and one edge incident to
  the source or sink. Cutting that edge loses the difference between the two
  possible gains.
- Group rewards of three or more entries use one auxiliary vertex and hard
  implication edges. Smaller groups have a direct encoding.

Thus every cut has cost equal to a constant minus the modeled gain. A minimum
cut therefore gives a maximum-gain selection. If several selections have the
same maximum gain, `solve()` may return any one of them.

## Hard Constraints

| Call | Constraint |
| --- | --- |
| `add_hard_implication(i, j)` | If `i` is selected, `j` must also be selected. |
| `force_selected(i)` | Project `i` must be selected. |
| `force_unselected(i)` | Project `i` must be unselected. |

Hard constraints use a capacity larger than the sum of every finite capacity.
This value is computed only inside `solve()`, so constraints remain truly hard
even if more gains or penalties are added later.

Contradictory hard constraints make the result infeasible. Check
`result.is_feasible()` before reading `max_gain` or interpreting `selected`.

## Result

`ProjectSelectionResult<T>` contains:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether all hard constraints can be satisfied. |
| `max_gain` | `T` | Maximum total gain. It is meaningful only when feasible. |
| `selected` | `std::vector<bool>` | One optimal choice for the original projects. Auxiliary vertices are not included. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |

Calling `solve()` does not mutate the model, so it may be called repeatedly.

## Methods and Complexity

Let `N` be the number of original projects plus internally created auxiliary
vertices, and let `M` be the number of generated flow edges.

| Method | Complexity |
| --- | --- |
| Constructor, `size` | $O(1)$ |
| `add_gain`, `add_penalty`, `add_penalty_if_different`, `add_gain_if_same`, hard single-project methods | Amortized $O(1)$ |
| `add_gain_if_all_selected`, `add_gain_if_all_unselected` | $O(K)$ for a group of size `K` |
| `solve` | General-case $O(N^2 M)$ time and $O(N + M)$ memory |

A group-reward call creates one auxiliary vertex when its group has at least
three entries. `solve()` uses the repository's `MaxFlow<T>` implementation.

## Numeric Requirements

`T` must be a signed integral type; `long long` is recommended. Every
intermediate gain difference, the sum of finite capacities, the hard capacity,
and the final answer must fit in `T`. These range requirements are checked with
assertions where practical.

## Example

Suppose each selected project earns its listed gain, project `0` requires
project `1`, and completing projects `1` and `2` together earns a bonus.

```cpp
#include "optimization/project_selection.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::opt::ProjectSelection<long long> solver(3);
    solver.add_gain(0, 10);
    solver.add_gain(1, -3);  // Selecting project 1 costs 3.
    solver.add_gain(2, 4);
    solver.add_hard_implication(0, 1);
    solver.add_gain_if_all_selected(std::vector<int>{1, 2}, 5);

    auto result = solver.solve();
    if (!result.is_feasible()) return 0;

    std::cout << result.max_gain << "\n";  // 16
    for (int i = 0; i < solver.size(); i++) {
        if (result.selected[i]) std::cout << i << "\n";
    }
}
```
