---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: optimization/project_selection.hpp
    title: Project Selection
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/optimization/integer_lp.test.cpp
    title: verify/optimization/integer_lp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/optimization/k_project_selection.test.cpp
    title: verify/optimization/k_project_selection.test.cpp
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
  bundledCode: "#line 1 \"optimization/k_project_selection.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"optimization/project_selection.hpp\"\n\n\n\n#line\
    \ 9 \"optimization/project_selection.hpp\"\n\n#line 1 \"graph/flow/max_flow.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 9 \"graph/flow/max_flow.hpp\"\n\nnamespace\
    \ m1une {\nnamespace flow {\n\ntemplate <class Cap>\nstruct MaxFlow {\n    struct\
    \ Edge {\n        int from;\n        int to;\n        Cap cap;\n        Cap flow;\n\
    \    };\n\n   private:\n    struct InternalEdge {\n        int to;\n        int\
    \ rev;\n        Cap cap;\n    };\n\n    struct Position {\n        int from;\n\
    \        int edge;\n    };\n\n    int _n;\n    std::vector<Position> _pos;\n \
    \   std::vector<std::vector<InternalEdge>> _g;\n\n    Cap highest_label_preflow_push(int\
    \ s, int t) {\n        const int dead = 2 * _n;\n        const int unreachable\
    \ = _n + 1;\n        std::vector<Cap> excess(_n, Cap(0));\n        std::vector<int>\
    \ state(8 * std::size_t(_n) + 2);\n        int* height = state.data();\n     \
    \   int* height_count = height + _n;\n        int* current = height_count + dead\
    \ + 1;\n        int* queue = current + _n;\n        int* next = queue + _n;\n\
    \        int* bucket_head = next + _n;\n        std::vector<char> active(_n, false);\n\
    \        int highest = -1;\n        long long work = 0;\n        const long long\
    \ arc_count =\n            2LL * static_cast<long long>(_pos.size());\n      \
    \  const long long work_limit = std::max(1LL, 4 * arc_count + _n);\n\n       \
    \ auto activate = [&](int v) {\n            if (v == s || v == t || active[v]\
    \ || excess[v] == Cap(0) ||\n                height[v] >= dead) {\n          \
    \      return;\n            }\n            active[v] = true;\n            next[v]\
    \ = bucket_head[height[v]];\n            bucket_head[height[v]] = v;\n       \
    \     highest = std::max(highest, height[v]);\n        };\n\n        auto rebuild_buckets\
    \ = [&]() {\n            std::fill(bucket_head, bucket_head + dead + 1, -1);\n\
    \            std::fill(active.begin(), active.end(), false);\n            highest\
    \ = -1;\n            for (int v = 0; v < _n; v++) activate(v);\n        };\n\n\
    \        auto global_relabel = [&]() {\n            std::fill(height, height +\
    \ _n, unreachable);\n            std::fill(height_count, height_count + dead +\
    \ 1, 0);\n            std::fill(current, current + _n, 0);\n            int head\
    \ = 0;\n            int tail = 0;\n            height[t] = 0;\n            height[s]\
    \ = _n;\n            queue[tail++] = t;\n            while (head != tail) {\n\
    \                int v = queue[head++];\n                for (const auto& e :\
    \ _g[v]) {\n                    if (e.to == s || height[e.to] != unreachable)\
    \ continue;\n                    const auto& reverse = _g[e.to][e.rev];\n    \
    \                if (reverse.cap == Cap(0)) continue;\n                    height[e.to]\
    \ = height[v] + 1;\n                    queue[tail++] = e.to;\n              \
    \  }\n            }\n            for (int v = 0; v < _n; v++) height_count[height[v]]++;\n\
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
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP\n#define M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <limits>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#include \"project_selection.hpp\"\n\n\
    namespace m1une {\nnamespace opt {\n\ntemplate <class T>\nstruct KProjectSelectionResult\
    \ {\n    bool feasible;\n    T max_gain;\n    std::vector<int> values;\n\n   \
    \ bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nclass KProjectSelection {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n    static_assert(sizeof(T) <= sizeof(long long));\n\
    \n    using Wide = __int128_t;\n\n    std::vector<int> _value_counts;\n    std::vector<int>\
    \ _first_threshold;\n    ProjectSelection<T> _binary;\n    T _constant = T();\n\
    \n    static int threshold_count(const std::vector<int>& value_counts) {\n   \
    \     assert(value_counts.size() <=\n               std::size_t(std::numeric_limits<int>::max()));\n\
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
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP\n"
  dependsOn:
  - optimization/project_selection.hpp
  - graph/flow/max_flow.hpp
  isVerificationFile: false
  path: optimization/k_project_selection.hpp
  requiredBy:
  - optimization/all.hpp
  timestamp: '2026-08-24 01:51:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/optimization/project_selection.test.cpp
  - verify/optimization/k_project_selection.test.cpp
  - verify/optimization/integer_lp.test.cpp
  - verify/optimization/simplex.test.cpp
documentation_of: optimization/k_project_selection.hpp
layout: document
title: K-Value Project Selection
---

## Overview

`KProjectSelection<T>` assigns one ordered value to every project and maximizes
the sum of unary gains and graph-cut-representable pairwise gains. Project `i`
has values `0, 1, ..., value_count(i) - 1`; different projects may have
different numbers of values.

This is the ordered, k-valued generalization of binary project selection. It is
useful for labeling and discrete optimization problems whose pairwise terms
prefer coordinated increases. The model is reduced to one minimum `s-t` cut.

## Objective Terms

All calls are additive: calling `add_gain` several times adds every supplied
term to the same objective.

| Method | Contribution |
| --- | --- |
| `void add_gain(int i, const std::vector<T>& gains)` | Adds `gains[x]` when project `i` takes value `x`. The vector must have `value_count(i)` entries. |
| `void add_gain(int i, int j, const std::vector<std::vector<T>>& gains)` | Adds `gains[x][y]` when distinct projects `i` and `j` take values `x` and `y`. The matrix must have shape `value_count(i)` by `value_count(j)`. |

## Domain of Gains

Every entry in a unary gain vector or pairwise gain matrix may be **negative,
zero, or positive**, as long as it is representable by `T`. A negative entry
represents a cost for the corresponding value or pair of values. Consequently,
the optimal `result.max_gain` may also be negative.

Unary gain vectors have no further algebraic restriction. Pairwise matrix
entries do not need to be non-negative, but their discrete mixed differences
must be non-negative. Equivalently, a pairwise gain matrix `g` must be
**supermodular** on the ordered values:

$$
g(x,y) + g(x+1,y+1) \ge g(x+1,y) + g(x,y+1)
$$

for every adjacent pair of rows and columns. The implementation checks this
condition with assertions. Each mixed difference, every accumulated value, and
the final answer must also fit the numeric requirements stated below.

Equivalently, if the problem is written using costs `c = -g`, every pairwise
cost matrix must be Monge. An arbitrary pairwise table cannot generally be
optimized by one minimum cut.

To minimize costs, negate every cost table before adding it, maximize the
resulting gain, and negate `result.max_gain`.

## Construction and Bounds

| Method | Signature / Meaning |
| --- | --- |
| Default constructor | Creates a model with no projects. |
| Heterogeneous constructor | `explicit KProjectSelection(std::vector<int> value_counts)` creates one project for every entry. Every count must be positive. |
| Uniform constructor | `KProjectSelection(int project_count, int value_count)` gives every project the same positive number of values. |
| `size` | `int size() const` returns the number of projects. |
| `value_count` | `int value_count(int i) const` returns the number of values of project `i`. |
| `force_value` | `void force_value(int i, int x)` requires value `x`. |
| `force_value_at_least` | `void force_value_at_least(int i, int lower_bound)` requires the value to be at least the bound. |
| `force_value_at_most` | `void force_value_at_most(int i, int upper_bound)` requires the value to be at most the bound. |

Bounds are inclusive. Contradictory bounds make the model infeasible rather
than silently choosing a value.

## Result

`KProjectSelectionResult<T>` contains:

| Member / Method | Type / Signature | Meaning |
| --- | --- | --- |
| `feasible` | `bool` | Whether all forced-value constraints can be satisfied. |
| `max_gain` | `T` | Maximum total gain; meaningful only when feasible. |
| `values` | `std::vector<int>` | One optimal value for each project. |
| `is_feasible` | `bool is_feasible() const` | Returns `feasible`. |

`solve()` has signature `KProjectSelectionResult<T> solve() const`. It does not
mutate the model, and it may return any optimum when several assignments tie.

## Reduction and Complexity

For every project value boundary `d`, the reduction creates a Boolean threshold
vertex representing `value >= d`. Hard implications ensure that the selected
thresholds form a prefix. Unary tables become gains on these thresholds.

For a pairwise table, each non-negative discrete mixed difference becomes a
reward for selecting two threshold vertices. Supermodularity is exactly the
condition that makes all such rewards graph-cut-representable.

Let

- `S` be the sum of `value_count(i) - 1` over all projects,
- `P` be the sum of `value_count(i) * value_count(j)` over all added pairwise
  terms, and
- `M = O(S + P)` be the number of generated flow edges.

| Method | Time | Extra stored memory |
| --- | --- | --- |
| Heterogeneous or uniform constructor | $O(N + S)$ | $O(N + S)$ |
| `size`, `value_count` | $O(1)$ | $O(1)$ |
| Unary `add_gain` | $O(K_i)$ | $O(K_i)$ |
| Pairwise `add_gain` | $O(K_i K_j)$ | $O(K_i K_j)$ in the worst case |
| Forced-value or bound method | $O(1)$ | $O(1)$ |
| `solve` | General-case $O((S+2)^2 M)$ | $O(S + M)$ |

The solve bound follows the underlying `MaxFlow<T>` implementation. Threshold
reconstruction takes an additional $O(S)$ time.

## Numeric Requirements

`T` must be a signed integral type no wider than 64 bits; `long long` is
recommended. Every adjacent gain difference, discrete mixed difference, sum of
finite cut capacities, accumulated constant, and final answer must fit in `T`.
The implementation uses a wider intermediate for checking individual table
differences and assertions for the remaining range requirements.

## Example

The following model has three values for project `0` and two for project `1`.
Its pairwise table is supermodular.

```cpp
#include "optimization/k_project_selection.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::opt::KProjectSelection<long long> solver(
        std::vector<int>{3, 2}
    );
    solver.add_gain(0, std::vector<long long>{1, 4, 2});
    solver.add_gain(1, std::vector<long long>{-2, 3});

    std::vector<std::vector<long long>> together(
        3,
        std::vector<long long>(2)
    );
    together[0] = std::vector<long long>{0, 1};
    together[1] = std::vector<long long>{-1, 3};
    together[2] = std::vector<long long>{1, 7};
    solver.add_gain(0, 1, together);

    auto result = solver.solve();
    if (!result.is_feasible()) return 0;
    std::cout << result.max_gain << '\n';  // 12
    std::cout << result.values[0] << ' ' << result.values[1] << '\n';  // 2 1
}
```
