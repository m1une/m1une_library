---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: optimization/k_project_selection.hpp
    title: K-Value Project Selection
  - icon: ':heavy_check_mark:'
    path: optimization/project_selection.hpp
    title: Project Selection
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
  bundledCode: "#line 1 \"verify/optimization/k_project_selection.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <limits>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"optimization/k_project_selection.hpp\"\
    \n\n\n\n#line 5 \"optimization/k_project_selection.hpp\"\n#include <cstddef>\n\
    #line 7 \"optimization/k_project_selection.hpp\"\n#include <type_traits>\n#line\
    \ 10 \"optimization/k_project_selection.hpp\"\n\n#line 1 \"optimization/project_selection.hpp\"\
    \n\n\n\n#line 9 \"optimization/project_selection.hpp\"\n\n#line 1 \"graph/flow/max_flow.hpp\"\
    \n\n\n\n#line 9 \"graph/flow/max_flow.hpp\"\n\nnamespace m1une {\nnamespace flow\
    \ {\n\ntemplate <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int\
    \ from;\n        int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n\
    \    struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \    };\n\n    struct Position {\n        int from;\n        int edge;\n    };\n\
    \n    int _n;\n    std::vector<Position> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n    Cap highest_label_preflow_push(int s, int t) {\n        const int\
    \ dead = 2 * _n;\n        const int unreachable = _n + 1;\n        std::vector<Cap>\
    \ excess(_n, Cap(0));\n        std::vector<int> state(8 * std::size_t(_n) + 2);\n\
    \        int* height = state.data();\n        int* height_count = height + _n;\n\
    \        int* current = height_count + dead + 1;\n        int* queue = current\
    \ + _n;\n        int* next = queue + _n;\n        int* bucket_head = next + _n;\n\
    \        std::vector<char> active(_n, false);\n        int highest = -1;\n   \
    \     long long work = 0;\n        const long long arc_count =\n            2LL\
    \ * static_cast<long long>(_pos.size());\n        const long long work_limit =\
    \ std::max(1LL, 4 * arc_count + _n);\n\n        auto activate = [&](int v) {\n\
    \            if (v == s || v == t || active[v] || excess[v] == Cap(0) ||\n   \
    \             height[v] >= dead) {\n                return;\n            }\n \
    \           active[v] = true;\n            next[v] = bucket_head[height[v]];\n\
    \            bucket_head[height[v]] = v;\n            highest = std::max(highest,\
    \ height[v]);\n        };\n\n        auto rebuild_buckets = [&]() {\n        \
    \    std::fill(bucket_head, bucket_head + dead + 1, -1);\n            std::fill(active.begin(),\
    \ active.end(), false);\n            highest = -1;\n            for (int v = 0;\
    \ v < _n; v++) activate(v);\n        };\n\n        auto global_relabel = [&]()\
    \ {\n            std::fill(height, height + _n, unreachable);\n            std::fill(height_count,\
    \ height_count + dead + 1, 0);\n            std::fill(current, current + _n, 0);\n\
    \            int head = 0;\n            int tail = 0;\n            height[t] =\
    \ 0;\n            height[s] = _n;\n            queue[tail++] = t;\n          \
    \  while (head != tail) {\n                int v = queue[head++];\n          \
    \      for (const auto& e : _g[v]) {\n                    if (e.to == s || height[e.to]\
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
    \ current[v] = 0;\n            }\n            rebuild_buckets();\n        };\n\
    \n        auto relabel = [&](int v) -> bool {\n            int old_height = height[v];\n\
    \            int new_height = dead;\n            work += int(_g[v].size());\n\
    \            for (const auto& e : _g[v]) {\n                if (e.cap != Cap(0))\
    \ {\n                    new_height = std::min(new_height, height[e.to] + 1);\n\
    \                }\n            }\n            height_count[old_height]--;\n \
    \           height[v] = std::min(new_height, dead);\n            height_count[height[v]]++;\n\
    \            current[v] = 0;\n            if (old_height < _n && height_count[old_height]\
    \ == 0) {\n                gap(old_height);\n                return true;\n  \
    \          }\n            return false;\n        };\n\n        auto push = [&](int\
    \ v, InternalEdge& e) {\n            Cap sent = std::min(excess[v], e.cap);\n\
    \            bool was_zero = excess[e.to] == Cap(0);\n            e.cap -= sent;\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[v] -= sent;\n  \
    \          excess[e.to] += sent;\n            if (was_zero) activate(e.to);\n\
    \        };\n\n        auto discharge = [&](int v) {\n            while (excess[v]\
    \ != Cap(0) && height[v] < dead) {\n                if (current[v] == int(_g[v].size()))\
    \ {\n                    if (relabel(v)) return;\n                    continue;\n\
    \                }\n                auto& e = _g[v][current[v]];\n           \
    \     work++;\n                if (e.cap != Cap(0) && height[v] == height[e.to]\
    \ + 1) {\n                    push(v, e);\n                } else {\n        \
    \            current[v]++;\n                }\n            }\n            activate(v);\n\
    \        };\n\n        for (auto& e : _g[s]) {\n            if (e.to == s || e.cap\
    \ == Cap(0)) continue;\n            Cap sent = e.cap;\n            e.cap = Cap(0);\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[e.to] += sent;\n\
    \        }\n        global_relabel();\n\n        while (highest >= 0) {\n    \
    \        if (bucket_head[highest] == -1) {\n                highest--;\n     \
    \           continue;\n            }\n            int v = bucket_head[highest];\n\
    \            bucket_head[highest] = next[v];\n            if (!active[v] || height[v]\
    \ != highest) continue;\n            active[v] = false;\n            discharge(v);\n\
    \            if (work >= work_limit) global_relabel();\n        }\n        return\
    \ excess[t];\n    }\n\n   public:\n    MaxFlow() : MaxFlow(0) {}\n\n    explicit\
    \ MaxFlow(int n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_pos.size());\n    }\n\n    void reserve_edges(int edge_count) {\n\
    \        assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n       \
    \ if (_n == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count) <\
    \ std::size_t(_n)) {\n            return;\n        }\n        const std::size_t\
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
    \        assert(s != t);\n        return highest_label_preflow_push(s, t);\n \
    \   }\n\n    Cap max_flow_push_relabel(int s, int t) {\n        assert(0 <= s\
    \ && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n  \
    \      return highest_label_preflow_push(s, t);\n    }\n\n    Cap max_flow_dinic(int\
    \ s, int t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n\n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n\
    \        std::vector<int> work(3 * std::size_t(_n));\n        int* level = work.data();\n\
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
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n\n#line\
    \ 12 \"optimization/k_project_selection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ opt {\n\ntemplate <class T>\nstruct KProjectSelectionResult {\n    bool feasible;\n\
    \    T max_gain;\n    std::vector<int> values;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n};\n\ntemplate <class T>\nclass KProjectSelection\
    \ {\n    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);\n    static_assert(sizeof(T)\
    \ <= sizeof(long long));\n\n    using Wide = __int128_t;\n\n    std::vector<int>\
    \ _value_counts;\n    std::vector<int> _first_threshold;\n    ProjectSelection<T>\
    \ _binary;\n    T _constant = T();\n\n    static int threshold_count(const std::vector<int>&\
    \ value_counts) {\n        assert(value_counts.size() <=\n               std::size_t(std::numeric_limits<int>::max()));\n\
    \        long long count = 0;\n        for (int value_count : value_counts) {\n\
    \            assert(value_count >= 1);\n            count += value_count - 1;\n\
    \            assert(count <= std::numeric_limits<int>::max());\n        }\n  \
    \      return int(count);\n    }\n\n    static std::vector<int> repeated_value_counts(\n\
    \        int project_count,\n        int value_count\n    ) {\n        assert(project_count\
    \ >= 0);\n        assert(value_count >= 1);\n        return std::vector<int>(project_count,\
    \ value_count);\n    }\n\n    void assert_project(int project) const {\n     \
    \   (void)project;\n        assert(0 <= project && project < size());\n    }\n\
    \n    int threshold(int project, int value) const {\n        assert_project(project);\n\
    \        (void)value;\n        assert(1 <= value && value < _value_counts[project]);\n\
    \        return _first_threshold[project] + value - 1;\n    }\n\n    static T\
    \ narrow(Wide value) {\n        assert(Wide(std::numeric_limits<T>::lowest())\
    \ <= value);\n        assert(value <= Wide(std::numeric_limits<T>::max()));\n\
    \        return T(value);\n    }\n\n    void add_constant(T gain) {\n        _constant\
    \ = narrow(Wide(_constant) + gain);\n    }\n\n    void add_threshold_gain(int\
    \ project, int value, Wide gain) {\n        if (gain == 0) return;\n        _binary.add_gain(threshold(project,\
    \ value), narrow(gain));\n    }\n\n   public:\n    KProjectSelection() : KProjectSelection(std::vector<int>())\
    \ {}\n\n    explicit KProjectSelection(std::vector<int> value_counts)\n      \
    \  : _value_counts(std::move(value_counts)),\n          _first_threshold(_value_counts.size()),\n\
    \          _binary(threshold_count(_value_counts)) {\n        int first = 0;\n\
    \        for (int project = 0; project < size(); project++) {\n            _first_threshold[project]\
    \ = first;\n            first += _value_counts[project] - 1;\n        }\n\n  \
    \      for (int project = 0; project < size(); project++) {\n            for (int\
    \ value = 2; value < _value_counts[project]; value++) {\n                _binary.add_hard_implication(\n\
    \                    threshold(project, value),\n                    threshold(project,\
    \ value - 1)\n                );\n            }\n        }\n    }\n\n    KProjectSelection(int\
    \ project_count, int value_count)\n        : KProjectSelection(repeated_value_counts(project_count,\
    \ value_count)) {}\n\n    int size() const {\n        return int(_value_counts.size());\n\
    \    }\n\n    int value_count(int project) const {\n        assert_project(project);\n\
    \        return _value_counts[project];\n    }\n\n    void add_gain(int project,\
    \ const std::vector<T>& gains) {\n        assert_project(project);\n        assert(int(gains.size())\
    \ == _value_counts[project]);\n        add_constant(gains[0]);\n        for (int\
    \ value = 1; value < _value_counts[project]; value++) {\n            add_threshold_gain(\n\
    \                project,\n                value,\n                Wide(gains[value])\
    \ - gains[value - 1]\n            );\n        }\n    }\n\n    void add_gain(\n\
    \        int project_a,\n        int project_b,\n        const std::vector<std::vector<T>>&\
    \ gains\n    ) {\n        assert_project(project_a);\n        assert_project(project_b);\n\
    \        assert(project_a != project_b);\n        const int count_a = _value_counts[project_a];\n\
    \        const int count_b = _value_counts[project_b];\n        assert(int(gains.size())\
    \ == count_a);\n        for (const auto& row : gains) assert(int(row.size()) ==\
    \ count_b);\n\n        add_constant(gains[0][0]);\n        for (int value_a =\
    \ 1; value_a < count_a; value_a++) {\n            add_threshold_gain(\n      \
    \          project_a,\n                value_a,\n                Wide(gains[value_a][0])\
    \ - gains[value_a - 1][0]\n            );\n        }\n        for (int value_b\
    \ = 1; value_b < count_b; value_b++) {\n            add_threshold_gain(\n    \
    \            project_b,\n                value_b,\n                Wide(gains[0][value_b])\
    \ - gains[0][value_b - 1]\n            );\n        }\n\n        for (int value_a\
    \ = 1; value_a < count_a; value_a++) {\n            for (int value_b = 1; value_b\
    \ < count_b; value_b++) {\n                Wide mixed =\n                    Wide(gains[value_a][value_b])\n\
    \                    - gains[value_a - 1][value_b]\n                    - gains[value_a][value_b\
    \ - 1]\n                    + gains[value_a - 1][value_b - 1];\n             \
    \   assert(mixed >= 0);\n                T gain = narrow(mixed);\n           \
    \     if (gain == T()) continue;\n                int threshold_a = threshold(project_a,\
    \ value_a);\n                int threshold_b = threshold(project_b, value_b);\n\
    \                _binary.add_gain(threshold_a, gain);\n                _binary.add_penalty(threshold_a,\
    \ threshold_b, gain);\n            }\n        }\n    }\n\n    void force_value(int\
    \ project, int value) {\n        assert_project(project);\n        assert(0 <=\
    \ value && value < _value_counts[project]);\n        force_value_at_least(project,\
    \ value);\n        force_value_at_most(project, value);\n    }\n\n    void force_value_at_least(int\
    \ project, int lower_bound) {\n        assert_project(project);\n        assert(0\
    \ <= lower_bound && lower_bound < _value_counts[project]);\n        if (lower_bound\
    \ > 0) {\n            _binary.force_selected(threshold(project, lower_bound));\n\
    \        }\n    }\n\n    void force_value_at_most(int project, int upper_bound)\
    \ {\n        assert_project(project);\n        assert(0 <= upper_bound && upper_bound\
    \ < _value_counts[project]);\n        if (upper_bound + 1 < _value_counts[project])\
    \ {\n            _binary.force_unselected(threshold(project, upper_bound + 1));\n\
    \        }\n    }\n\n    KProjectSelectionResult<T> solve() const {\n        auto\
    \ binary_result = _binary.solve();\n        KProjectSelectionResult<T> result;\n\
    \        result.feasible = binary_result.feasible;\n        result.max_gain =\
    \ T();\n        result.values.assign(size(), 0);\n        if (!result.feasible)\
    \ return result;\n\n        result.max_gain = narrow(Wide(_constant) + binary_result.max_gain);\n\
    \        for (int project = 0; project < size(); project++) {\n            for\
    \ (int value = 1; value < _value_counts[project]; value++) {\n               \
    \ if (!binary_result.selected[threshold(project, value)]) break;\n           \
    \     result.values[project] = value;\n            }\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
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
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 13 \"verify/optimization/k_project_selection.test.cpp\"\
    \n\nusing Solver = m1une::opt::KProjectSelection<long long>;\n\nstruct PairGain\
    \ {\n    int a;\n    int b;\n    std::vector<std::vector<long long>> gain;\n};\n\
    \nvoid test_basic() {\n    Solver solver(std::vector<int>{3, 2});\n    solver.add_gain(0,\
    \ std::vector<long long>{1, 4, 2});\n    solver.add_gain(1, std::vector<long long>{-2,\
    \ 3});\n\n    std::vector<std::vector<long long>> pair_gain(3, std::vector<long\
    \ long>(2));\n    pair_gain[0] = std::vector<long long>{0, 1};\n    pair_gain[1]\
    \ = std::vector<long long>{-1, 3};\n    pair_gain[2] = std::vector<long long>{1,\
    \ 7};\n    solver.add_gain(0, 1, pair_gain);\n\n    auto result = solver.solve();\n\
    \    assert(result.is_feasible());\n    assert(result.max_gain == 12);\n    assert(result.values\
    \ == std::vector<int>({2, 1}));\n\n    auto repeated = solver.solve();\n    assert(repeated.max_gain\
    \ == result.max_gain);\n    assert(repeated.values == result.values);\n}\n\nvoid\
    \ test_bounds_and_infeasibility() {\n    Solver solver(std::vector<int>{4, 1});\n\
    \    solver.add_gain(0, std::vector<long long>{0, 5, 9, 20});\n    solver.add_gain(1,\
    \ std::vector<long long>{7});\n    solver.force_value_at_least(0, 1);\n    solver.force_value_at_most(0,\
    \ 2);\n    auto result = solver.solve();\n    assert(result.is_feasible());\n\
    \    assert(result.max_gain == 16);\n    assert(result.values == std::vector<int>({2,\
    \ 0}));\n\n    Solver impossible(1, 3);\n    impossible.force_value(0, 0);\n \
    \   impossible.force_value(0, 2);\n    assert(!impossible.solve().is_feasible());\n\
    \n    Solver empty;\n    auto empty_result = empty.solve();\n    assert(empty_result.is_feasible());\n\
    \    assert(empty_result.max_gain == 0);\n    assert(empty_result.values.empty());\n\
    }\n\nstd::vector<std::vector<long long>> make_supermodular_gain(\n    int rows,\n\
    \    int columns,\n    std::mt19937& rng\n) {\n    auto random_value = [&](int\
    \ low, int high) {\n        return static_cast<long long>(\n            low +\
    \ int(rng() % unsigned(high - low + 1))\n        );\n    };\n\n    std::vector<std::vector<long\
    \ long>> gain(\n        rows,\n        std::vector<long long>(columns)\n    );\n\
    \    gain[0][0] = random_value(-5, 5);\n    for (int row = 1; row < rows; row++)\
    \ {\n        gain[row][0] = gain[row - 1][0] + random_value(-4, 4);\n    }\n \
    \   for (int column = 1; column < columns; column++) {\n        gain[0][column]\
    \ = gain[0][column - 1] + random_value(-4, 4);\n    }\n    for (int row = 1; row\
    \ < rows; row++) {\n        for (int column = 1; column < columns; column++) {\n\
    \            long long mixed = random_value(0, 5);\n            gain[row][column]\
    \ =\n                gain[row - 1][column]\n                + gain[row][column\
    \ - 1]\n                - gain[row - 1][column - 1]\n                + mixed;\n\
    \        }\n    }\n    return gain;\n}\n\nvoid test_random_against_bruteforce()\
    \ {\n    std::mt19937 rng(712367821);\n    for (int test = 0; test < 240; test++)\
    \ {\n        int n = 1 + int(rng() % 4);\n        std::vector<int> counts(n);\n\
    \        for (int& count : counts) count = 1 + int(rng() % 4);\n        Solver\
    \ solver(counts);\n\n        std::vector<std::vector<long long>> unary(n);\n \
    \       for (int project = 0; project < n; project++) {\n            unary[project].resize(counts[project]);\n\
    \            for (long long& gain : unary[project]) {\n                gain =\
    \ int(rng() % 17) - 8;\n            }\n            solver.add_gain(project, unary[project]);\n\
    \        }\n\n        std::vector<PairGain> pairs;\n        for (int a = 0; a\
    \ < n; a++) {\n            for (int b = a + 1; b < n; b++) {\n               \
    \ if (rng() % 3 == 0) continue;\n                PairGain term;\n            \
    \    term.a = a;\n                term.b = b;\n                term.gain = make_supermodular_gain(counts[a],\
    \ counts[b], rng);\n                solver.add_gain(a, b, term.gain);\n      \
    \          pairs.push_back(std::move(term));\n            }\n        }\n\n   \
    \     std::vector<int> lower(n, 0);\n        std::vector<int> upper = counts;\n\
    \        for (int& value : upper) value--;\n        for (int project = 0; project\
    \ < n; project++) {\n            if (rng() % 5 == 0) {\n                lower[project]\
    \ = int(rng() % unsigned(counts[project]));\n                solver.force_value_at_least(project,\
    \ lower[project]);\n            }\n            if (rng() % 5 == 0) {\n       \
    \         upper[project] = int(rng() % unsigned(counts[project]));\n         \
    \       solver.force_value_at_most(project, upper[project]);\n            }\n\
    \        }\n\n        bool found = false;\n        long long expected = std::numeric_limits<long\
    \ long>::lowest();\n        std::vector<int> values(n);\n        std::function<void(int)>\
    \ enumerate = [&](int project) {\n            if (project != n) {\n          \
    \      for (values[project] = 0;\n                     values[project] < counts[project];\n\
    \                     values[project]++) {\n                    enumerate(project\
    \ + 1);\n                }\n                return;\n            }\n\n       \
    \     for (int i = 0; i < n; i++) {\n                if (values[i] < lower[i]\
    \ || upper[i] < values[i]) return;\n            }\n            long long total\
    \ = 0;\n            for (int i = 0; i < n; i++) total += unary[i][values[i]];\n\
    \            for (const auto& term : pairs) {\n                total += term.gain[values[term.a]][values[term.b]];\n\
    \            }\n            found = true;\n            expected = std::max(expected,\
    \ total);\n        };\n        enumerate(0);\n\n        auto result = solver.solve();\n\
    \        assert(result.is_feasible() == found);\n        if (!found) continue;\n\
    \        assert(result.max_gain == expected);\n\n        long long returned_gain\
    \ = 0;\n        for (int project = 0; project < n; project++) {\n            assert(lower[project]\
    \ <= result.values[project]);\n            assert(result.values[project] <= upper[project]);\n\
    \            returned_gain += unary[project][result.values[project]];\n      \
    \  }\n        for (const auto& term : pairs) {\n            returned_gain +=\n\
    \                term.gain[result.values[term.a]][result.values[term.b]];\n  \
    \      }\n        assert(returned_gain == expected);\n    }\n}\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_bounds_and_infeasibility();\n  \
    \  test_random_against_bruteforce();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <limits>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../optimization/k_project_selection.hpp\"\
    \n#include \"../../utilities/fast_io.hpp\"\n\nusing Solver = m1une::opt::KProjectSelection<long\
    \ long>;\n\nstruct PairGain {\n    int a;\n    int b;\n    std::vector<std::vector<long\
    \ long>> gain;\n};\n\nvoid test_basic() {\n    Solver solver(std::vector<int>{3,\
    \ 2});\n    solver.add_gain(0, std::vector<long long>{1, 4, 2});\n    solver.add_gain(1,\
    \ std::vector<long long>{-2, 3});\n\n    std::vector<std::vector<long long>> pair_gain(3,\
    \ std::vector<long long>(2));\n    pair_gain[0] = std::vector<long long>{0, 1};\n\
    \    pair_gain[1] = std::vector<long long>{-1, 3};\n    pair_gain[2] = std::vector<long\
    \ long>{1, 7};\n    solver.add_gain(0, 1, pair_gain);\n\n    auto result = solver.solve();\n\
    \    assert(result.is_feasible());\n    assert(result.max_gain == 12);\n    assert(result.values\
    \ == std::vector<int>({2, 1}));\n\n    auto repeated = solver.solve();\n    assert(repeated.max_gain\
    \ == result.max_gain);\n    assert(repeated.values == result.values);\n}\n\nvoid\
    \ test_bounds_and_infeasibility() {\n    Solver solver(std::vector<int>{4, 1});\n\
    \    solver.add_gain(0, std::vector<long long>{0, 5, 9, 20});\n    solver.add_gain(1,\
    \ std::vector<long long>{7});\n    solver.force_value_at_least(0, 1);\n    solver.force_value_at_most(0,\
    \ 2);\n    auto result = solver.solve();\n    assert(result.is_feasible());\n\
    \    assert(result.max_gain == 16);\n    assert(result.values == std::vector<int>({2,\
    \ 0}));\n\n    Solver impossible(1, 3);\n    impossible.force_value(0, 0);\n \
    \   impossible.force_value(0, 2);\n    assert(!impossible.solve().is_feasible());\n\
    \n    Solver empty;\n    auto empty_result = empty.solve();\n    assert(empty_result.is_feasible());\n\
    \    assert(empty_result.max_gain == 0);\n    assert(empty_result.values.empty());\n\
    }\n\nstd::vector<std::vector<long long>> make_supermodular_gain(\n    int rows,\n\
    \    int columns,\n    std::mt19937& rng\n) {\n    auto random_value = [&](int\
    \ low, int high) {\n        return static_cast<long long>(\n            low +\
    \ int(rng() % unsigned(high - low + 1))\n        );\n    };\n\n    std::vector<std::vector<long\
    \ long>> gain(\n        rows,\n        std::vector<long long>(columns)\n    );\n\
    \    gain[0][0] = random_value(-5, 5);\n    for (int row = 1; row < rows; row++)\
    \ {\n        gain[row][0] = gain[row - 1][0] + random_value(-4, 4);\n    }\n \
    \   for (int column = 1; column < columns; column++) {\n        gain[0][column]\
    \ = gain[0][column - 1] + random_value(-4, 4);\n    }\n    for (int row = 1; row\
    \ < rows; row++) {\n        for (int column = 1; column < columns; column++) {\n\
    \            long long mixed = random_value(0, 5);\n            gain[row][column]\
    \ =\n                gain[row - 1][column]\n                + gain[row][column\
    \ - 1]\n                - gain[row - 1][column - 1]\n                + mixed;\n\
    \        }\n    }\n    return gain;\n}\n\nvoid test_random_against_bruteforce()\
    \ {\n    std::mt19937 rng(712367821);\n    for (int test = 0; test < 240; test++)\
    \ {\n        int n = 1 + int(rng() % 4);\n        std::vector<int> counts(n);\n\
    \        for (int& count : counts) count = 1 + int(rng() % 4);\n        Solver\
    \ solver(counts);\n\n        std::vector<std::vector<long long>> unary(n);\n \
    \       for (int project = 0; project < n; project++) {\n            unary[project].resize(counts[project]);\n\
    \            for (long long& gain : unary[project]) {\n                gain =\
    \ int(rng() % 17) - 8;\n            }\n            solver.add_gain(project, unary[project]);\n\
    \        }\n\n        std::vector<PairGain> pairs;\n        for (int a = 0; a\
    \ < n; a++) {\n            for (int b = a + 1; b < n; b++) {\n               \
    \ if (rng() % 3 == 0) continue;\n                PairGain term;\n            \
    \    term.a = a;\n                term.b = b;\n                term.gain = make_supermodular_gain(counts[a],\
    \ counts[b], rng);\n                solver.add_gain(a, b, term.gain);\n      \
    \          pairs.push_back(std::move(term));\n            }\n        }\n\n   \
    \     std::vector<int> lower(n, 0);\n        std::vector<int> upper = counts;\n\
    \        for (int& value : upper) value--;\n        for (int project = 0; project\
    \ < n; project++) {\n            if (rng() % 5 == 0) {\n                lower[project]\
    \ = int(rng() % unsigned(counts[project]));\n                solver.force_value_at_least(project,\
    \ lower[project]);\n            }\n            if (rng() % 5 == 0) {\n       \
    \         upper[project] = int(rng() % unsigned(counts[project]));\n         \
    \       solver.force_value_at_most(project, upper[project]);\n            }\n\
    \        }\n\n        bool found = false;\n        long long expected = std::numeric_limits<long\
    \ long>::lowest();\n        std::vector<int> values(n);\n        std::function<void(int)>\
    \ enumerate = [&](int project) {\n            if (project != n) {\n          \
    \      for (values[project] = 0;\n                     values[project] < counts[project];\n\
    \                     values[project]++) {\n                    enumerate(project\
    \ + 1);\n                }\n                return;\n            }\n\n       \
    \     for (int i = 0; i < n; i++) {\n                if (values[i] < lower[i]\
    \ || upper[i] < values[i]) return;\n            }\n            long long total\
    \ = 0;\n            for (int i = 0; i < n; i++) total += unary[i][values[i]];\n\
    \            for (const auto& term : pairs) {\n                total += term.gain[values[term.a]][values[term.b]];\n\
    \            }\n            found = true;\n            expected = std::max(expected,\
    \ total);\n        };\n        enumerate(0);\n\n        auto result = solver.solve();\n\
    \        assert(result.is_feasible() == found);\n        if (!found) continue;\n\
    \        assert(result.max_gain == expected);\n\n        long long returned_gain\
    \ = 0;\n        for (int project = 0; project < n; project++) {\n            assert(lower[project]\
    \ <= result.values[project]);\n            assert(result.values[project] <= upper[project]);\n\
    \            returned_gain += unary[project][result.values[project]];\n      \
    \  }\n        for (const auto& term : pairs) {\n            returned_gain +=\n\
    \                term.gain[result.values[term.a]][result.values[term.b]];\n  \
    \      }\n        assert(returned_gain == expected);\n    }\n}\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_bounds_and_infeasibility();\n  \
    \  test_random_against_bruteforce();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - optimization/k_project_selection.hpp
  - optimization/project_selection.hpp
  - graph/flow/max_flow.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/optimization/k_project_selection.test.cpp
  requiredBy: []
  timestamp: '2026-08-24 01:51:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/k_project_selection.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/k_project_selection.test.cpp
- /verify/verify/optimization/k_project_selection.test.cpp.html
title: verify/optimization/k_project_selection.test.cpp
---
