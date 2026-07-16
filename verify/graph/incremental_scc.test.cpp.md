---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/incremental_scc.hpp
    title: Incremental Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/incremental_scc
    links:
    - https://judge.yosupo.jp/problem/incremental_scc
  bundledCode: "#line 1 \"verify/graph/incremental_scc.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/incremental_scc\"\n\n#line 1 \"graph/incremental_scc.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()),\
    \ id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_\
    \ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_),\
    \ alive(alive_) {}\n\n    int other(int v) const {\n        assert(v == from ||\
    \ v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\n\
    struct Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n \
    \  private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 11 \"graph/incremental_scc.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace incremental_scc_detail {\n\nstruct EdgeEvent {\n    int\
    \ id;\n    int from;\n    int to;\n};\n\ninline std::vector<int> component_ids(\n\
    \    int vertex_count,\n    const std::vector<EdgeEvent>& edges,\n    int time\n\
    ) {\n    std::vector<int> begin(vertex_count + 1, 0);\n    std::vector<int> reverse_begin(vertex_count\
    \ + 1, 0);\n    int edge_count = 0;\n    for (const EdgeEvent& edge : edges) {\n\
    \        if (edge.id >= time) continue;\n        begin[edge.from + 1]++;\n   \
    \     reverse_begin[edge.to + 1]++;\n        edge_count++;\n    }\n    for (int\
    \ vertex = 0; vertex < vertex_count; vertex++) {\n        begin[vertex + 1] +=\
    \ begin[vertex];\n        reverse_begin[vertex + 1] += reverse_begin[vertex];\n\
    \    }\n\n    std::vector<int> adjacency(edge_count);\n    std::vector<int> reverse_adjacency(edge_count);\n\
    \    std::vector<int> cursor = begin;\n    std::vector<int> reverse_cursor = reverse_begin;\n\
    \    for (const EdgeEvent& edge : edges) {\n        if (edge.id >= time) continue;\n\
    \        adjacency[cursor[edge.from]++] = edge.to;\n        reverse_adjacency[reverse_cursor[edge.to]++]\
    \ = edge.from;\n    }\n    std::vector<int>().swap(cursor);\n    std::vector<int>().swap(reverse_cursor);\n\
    \n    std::vector<char> visited(vertex_count, false);\n    std::vector<int> next_position(begin.begin(),\
    \ begin.end() - 1);\n    std::vector<int> order;\n    order.reserve(vertex_count);\n\
    \    std::vector<int> stack;\n    for (int start = 0; start < vertex_count; start++)\
    \ {\n        if (visited[start]) continue;\n        visited[start] = true;\n \
    \       stack.push_back(start);\n        while (!stack.empty()) {\n          \
    \  const int vertex = stack.back();\n            int& position = next_position[vertex];\n\
    \            if (position < begin[vertex + 1]) {\n                const int to\
    \ = adjacency[position++];\n                if (!visited[to]) {\n            \
    \        visited[to] = true;\n                    stack.push_back(to);\n     \
    \           }\n            } else {\n                order.push_back(vertex);\n\
    \                stack.pop_back();\n            }\n        }\n    }\n\n    std::vector<int>\
    \ component(vertex_count, -1);\n    int component_count = 0;\n    for (auto iterator\
    \ = order.rbegin(); iterator != order.rend(); ++iterator) {\n        const int\
    \ start = *iterator;\n        if (component[start] != -1) continue;\n        component[start]\
    \ = component_count;\n        stack.push_back(start);\n        while (!stack.empty())\
    \ {\n            const int vertex = stack.back();\n            stack.pop_back();\n\
    \            for (int position = reverse_begin[vertex];\n                 position\
    \ < reverse_begin[vertex + 1]; position++) {\n                const int to = reverse_adjacency[position];\n\
    \                if (component[to] != -1) continue;\n                component[to]\
    \ = component_count;\n                stack.push_back(to);\n            }\n  \
    \      }\n        component_count++;\n    }\n    return component;\n}\n\n}  //\
    \ namespace incremental_scc_detail\n\n// For every directed edge e, returns the\
    \ first time t after e is inserted such\n// that its endpoints are in the same\
    \ SCC. At time t, edges with IDs less than\n// t have been inserted. edge_count()\
    \ + 1 means this never happens.\ntemplate <class T>\nstd::vector<int> incremental_scc(const\
    \ Graph<T>& graph) {\n    using incremental_scc_detail::EdgeEvent;\n    using\
    \ incremental_scc_detail::component_ids;\n\n    const int vertex_count = graph.size();\n\
    \    const int edge_count = graph.edge_count();\n    const int never = edge_count\
    \ + 1;\n    std::vector<int> merge_time(edge_count, never);\n    if (edge_count\
    \ == 0) return merge_time;\n\n    std::vector<EdgeEvent> edges_by_id(edge_count);\n\
    \    std::vector<char> initialized(edge_count, false);\n    for (int vertex =\
    \ 0; vertex < vertex_count; vertex++) {\n        for (const Edge<T>& edge : graph[vertex])\
    \ {\n            assert(0 <= edge.id && edge.id < edge_count);\n            assert(!initialized[edge.id]);\n\
    \            if (initialized[edge.id]) continue;\n            initialized[edge.id]\
    \ = true;\n            edges_by_id[edge.id] = EdgeEvent{edge.id, edge.from, edge.to};\n\
    \        }\n    }\n\n    std::vector<EdgeEvent> events;\n    events.reserve(edge_count);\n\
    \    for (int edge_id = 0; edge_id < edge_count; edge_id++) {\n        assert(initialized[edge_id]);\n\
    \        if (graph.is_edge_alive(edge_id)) {\n            events.push_back(edges_by_id[edge_id]);\n\
    \        }\n    }\n    std::vector<EdgeEvent>().swap(edges_by_id);\n    std::vector<char>().swap(initialized);\n\
    \n    std::vector<int> new_index(vertex_count, -1);\n    auto divide = [&](\n\
    \        auto&& self,\n        std::vector<EdgeEvent> current,\n        int left,\n\
    \        int right\n    ) -> void {\n        if (current.empty() || right == left\
    \ + 1) return;\n        const int middle = left + (right - left) / 2;\n\n    \
    \    std::vector<int> touched;\n        touched.reserve(std::min(\n          \
    \  std::size_t(vertex_count),\n            current.size() * 2\n        ));\n \
    \       int compressed_count = 0;\n        for (const EdgeEvent& edge : current)\
    \ {\n            if (new_index[edge.from] == -1) {\n                new_index[edge.from]\
    \ = compressed_count++;\n                touched.push_back(edge.from);\n     \
    \       }\n            if (new_index[edge.to] == -1) {\n                new_index[edge.to]\
    \ = compressed_count++;\n                touched.push_back(edge.to);\n       \
    \     }\n        }\n        for (EdgeEvent& edge : current) {\n            edge.from\
    \ = new_index[edge.from];\n            edge.to = new_index[edge.to];\n       \
    \ }\n        for (int vertex : touched) new_index[vertex] = -1;\n\n        std::vector<EdgeEvent>\
    \ earlier;\n        std::vector<EdgeEvent> later;\n        earlier.reserve(current.size()\
    \ / 2);\n        later.reserve(current.size() / 2);\n        {\n            std::vector<int>\
    \ component =\n                component_ids(compressed_count, current, middle);\n\
    \            for (const EdgeEvent& edge : current) {\n                const int\
    \ from_component = component[edge.from];\n                const int to_component\
    \ = component[edge.to];\n                if (edge.id < middle &&\n           \
    \         from_component == to_component) {\n                    merge_time[edge.id]\
    \ =\n                        std::min(merge_time[edge.id], middle);\n        \
    \            earlier.push_back(edge);\n                } else {\n            \
    \        later.push_back(EdgeEvent{\n                        edge.id,\n      \
    \                  from_component,\n                        to_component\n   \
    \                 });\n                }\n            }\n        }\n\n       \
    \ std::vector<EdgeEvent>().swap(current);\n        self(self, std::move(earlier),\
    \ left, middle);\n        self(self, std::move(later), middle, right);\n    };\n\
    \    divide(divide, std::move(events), 0, edge_count + 1);\n    return merge_time;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/incremental_scc.test.cpp\"\
    \n\n#line 6 \"verify/graph/incremental_scc.test.cpp\"\n#include <cstdint>\n#line\
    \ 9 \"verify/graph/incremental_scc.test.cpp\"\n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\
    \n\n#line 5 \"ds/dsu/dsu.hpp\"\n#include <numeric>\n#line 8 \"ds/dsu/dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n   private:\n    int _n;\n\
    \    // parent_or_size[i] is the parent of i if it's >= 0.\n    // If it's < 0,\
    \ then i is a root and -parent_or_size[i] is the size of the group.\n    std::vector<int>\
    \ parent_or_size;\n\n    // Returns {new leader, absorbed leader}. The absorbed\
    \ leader is -1 when\n    // both vertices already belong to the same component.\n\
    \    std::pair<int, int> merge_leaders(int a, int b) {\n        int x = leader(a),\
    \ y = leader(b);\n        if (x == y) return {x, -1};\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) std::swap(x, y);\n        parent_or_size[x] += parent_or_size[y];\n\
    \        parent_or_size[y] = x;\n        return {x, y};\n    }\n\n   public:\n\
    \    Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1)\
    \ {}\n\n    // Merges the group containing 'a' with the group containing 'b'.\n\
    \    // Returns the leader of the merged group.\n    int merge(int a, int b) {\n\
    \        return merge_leaders(a, b).first;\n    }\n\n    // Invokes callback(new_leader,\
    \ absorbed_leader) after an actual merge.\n    // Returns the leader of the merged\
    \ group.\n    template <class Callback>\n    int merge(int a, int b, Callback&&\
    \ callback) {\n        std::pair<int, int> merged = merge_leaders(a, b);\n   \
    \     if (merged.second != -1) callback(merged.first, merged.second);\n      \
    \  return merged.first;\n    }\n\n    // Returns true if 'a' and 'b' belong to\
    \ the same group.\n    bool same(int a, int b) {\n        return leader(a) ==\
    \ leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"graph/scc.hpp\"\n\n\n\n#line 9 \"graph/scc.hpp\"\
    \n\n#line 11 \"graph/scc.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ SccResult {\n    int count;\n    std::vector<int> comp;\n    std::vector<std::vector<int>>\
    \ groups;\n\n    bool same(int u, int v) const {\n        assert(0 <= u && u <\
    \ int(comp.size()));\n        assert(0 <= v && v < int(comp.size()));\n      \
    \  return comp[u] == comp[v];\n    }\n\n    template <class T>\n    Graph<int>\
    \ dag(const Graph<T>& g) const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int v = 0; v < g.size(); v++) {\n            for (const auto& e\
    \ : g[v]) {\n                if (!e.alive) continue;\n                int a =\
    \ comp[e.from], b = comp[e.to];\n                if (a != b) edges.emplace_back(a,\
    \ b);\n            }\n        }\n        std::sort(edges.begin(), edges.end());\n\
    \        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());\n\n\
    \        Graph<int> result(count);\n        for (auto [a, b] : edges) result.add_directed_edge(a,\
    \ b);\n        return result;\n    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    const int n = g.size();\n    std::vector<std::vector<int>>\
    \ reverse_graph(n);\n    for (int vertex = 0; vertex < n; vertex++) {\n      \
    \  for (const auto& edge : g[vertex]) {\n            if (edge.alive) reverse_graph[edge.to].push_back(vertex);\n\
    \        }\n    }\n\n    std::vector<char> seen(n, false);\n    std::vector<int>\
    \ order;\n    order.reserve(n);\n    std::vector<std::pair<int, std::size_t>>\
    \ dfs_stack;\n    for (int start = 0; start < n; start++) {\n        if (seen[start])\
    \ continue;\n        seen[start] = true;\n        dfs_stack.emplace_back(start,\
    \ 0);\n        while (!dfs_stack.empty()) {\n            int vertex = dfs_stack.back().first;\n\
    \            std::size_t& edge_index = dfs_stack.back().second;\n            while\
    \ (edge_index < g[vertex].size() &&\n                   !g[vertex][edge_index].alive)\
    \ {\n                edge_index++;\n            }\n            if (edge_index\
    \ == g[vertex].size()) {\n                order.push_back(vertex);\n         \
    \       dfs_stack.pop_back();\n                continue;\n            }\n    \
    \        const int to = g[vertex][edge_index++].to;\n            if (!seen[to])\
    \ {\n                seen[to] = true;\n                dfs_stack.emplace_back(to,\
    \ 0);\n            }\n        }\n    }\n\n    std::vector<int> comp(n, -1);\n\
    \    std::vector<std::vector<int>> groups;\n    std::vector<int> stack;\n    for\
    \ (auto iterator = order.rbegin(); iterator != order.rend(); ++iterator) {\n \
    \       const int start = *iterator;\n        if (comp[start] != -1) continue;\n\
    \        const int component = int(groups.size());\n        groups.emplace_back();\n\
    \        comp[start] = component;\n        stack.push_back(start);\n        while\
    \ (!stack.empty()) {\n            const int vertex = stack.back();\n         \
    \   stack.pop_back();\n            groups.back().push_back(vertex);\n        \
    \    for (int to : reverse_graph[vertex]) {\n                if (comp[to] != -1)\
    \ continue;\n                comp[to] = component;\n                stack.push_back(to);\n\
    \            }\n        }\n    }\n\n    return SccResult{int(groups.size()), std::move(comp),\
    \ std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #include <type_traits>\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0\
    \ < Modulus, \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\
    \n   public:\n    static constexpr uint32_t mod() {\n        return Modulus;\n\
    \    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt\
    \ x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept\
    \ : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
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
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 14 \"verify/graph/incremental_scc.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\n\nvoid validate(const\
    \ Graph& graph, const std::vector<std::pair<int, int>>& edges) {\n    const int\
    \ n = graph.size();\n    const int m = graph.edge_count();\n    assert(int(edges.size())\
    \ == m);\n    const std::vector<int> actual = m1une::graph::incremental_scc(graph);\n\
    \    assert(int(actual.size()) == m);\n\n    std::vector<int> expected(m, m +\
    \ 1);\n    m1une::ds::Dsu replay(n);\n    for (int time = 1; time <= m; time++)\
    \ {\n        Graph prefix(n);\n        for (int edge_id = 0; edge_id < time; edge_id++)\
    \ {\n            if (!graph.is_edge_alive(edge_id)) continue;\n            prefix.add_directed_edge(\n\
    \                edges[edge_id].first,\n                edges[edge_id].second\n\
    \            );\n        }\n        const auto components =\n            m1une::graph::strongly_connected_components(prefix);\n\
    \        for (int edge_id = 0; edge_id < m; edge_id++) {\n            if (edge_id\
    \ >= time || !graph.is_edge_alive(edge_id)) continue;\n            if (expected[edge_id]\
    \ == m + 1 && components.same(\n                    edges[edge_id].first,\n  \
    \                  edges[edge_id].second\n                )) {\n             \
    \   expected[edge_id] = time;\n            }\n            if (actual[edge_id]\
    \ == time) {\n                replay.merge(edges[edge_id].first, edges[edge_id].second);\n\
    \            }\n        }\n        for (int first = 0; first < n; first++) {\n\
    \            for (int second = 0; second < n; second++) {\n                assert(replay.same(first,\
    \ second) ==\n                       components.same(first, second));\n      \
    \      }\n        }\n    }\n    assert(actual == expected);\n}\n\nvoid test_fixed()\
    \ {\n    Graph empty(3);\n    validate(empty, std::vector<std::pair<int, int>>());\n\
    \n    Graph graph(4);\n    std::vector<std::pair<int, int>> edges;\n    edges.emplace_back(0,\
    \ 1);\n    graph.add_directed_edge(0, 1);\n    edges.emplace_back(1, 2);\n   \
    \ graph.add_directed_edge(1, 2);\n    edges.emplace_back(2, 0);\n    graph.add_directed_edge(2,\
    \ 0);\n    edges.emplace_back(2, 3);\n    graph.add_directed_edge(2, 3);\n   \
    \ edges.emplace_back(3, 3);\n    graph.add_directed_edge(3, 3);\n    validate(graph,\
    \ edges);\n    const std::vector<int> time = m1une::graph::incremental_scc(graph);\n\
    \    assert(time[0] == 3);\n    assert(time[1] == 3);\n    assert(time[2] == 3);\n\
    \    assert(time[3] == 6);\n    assert(time[4] == 5);\n\n    graph.erase_edge(2);\n\
    \    validate(graph, edges);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 20260718;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 500; trial++) {\n        const int n = 1 + int(random() %\
    \ 8);\n        const int m = int(random() % 17);\n        Graph graph(n);\n  \
    \      std::vector<std::pair<int, int>> edges;\n        edges.reserve(m);\n  \
    \      for (int edge_id = 0; edge_id < m; edge_id++) {\n            const int\
    \ from = int(random() % n);\n            const int to = int(random() % n);\n \
    \           edges.emplace_back(from, to);\n            const int id = graph.add_directed_edge(from,\
    \ to);\n            if (random() % 7 == 0) graph.erase_edge(id);\n        }\n\
    \        validate(graph, edges);\n    }\n}\n\n}  // namespace\n\nint main() {\n\
    \    test_fixed();\n    test_randomized();\n\n    using Mint = m1une::math::modint998244353;\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    int vertex_count, edge_count;\n    fast_input >> vertex_count\
    \ >> edge_count;\n\n    std::vector<Mint> weight(vertex_count);\n    for (Mint&\
    \ value : weight) {\n        int input;\n        fast_input >> input;\n      \
    \  value = Mint(input);\n    }\n\n    Graph graph(vertex_count);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    edges.reserve(edge_count);\n    for (int edge_id = 0; edge_id\
    \ < edge_count; edge_id++) {\n        int from, to;\n        fast_input >> from\
    \ >> to;\n        edges.emplace_back(from, to);\n        graph.add_directed_edge(from,\
    \ to);\n    }\n\n    const std::vector<int> merge_time =\n        m1une::graph::incremental_scc(graph);\n\
    \    std::vector<std::vector<int>> edges_by_time(edge_count + 1);\n    for (int\
    \ edge_id = 0; edge_id < edge_count; edge_id++) {\n        if (merge_time[edge_id]\
    \ <= edge_count) {\n            edges_by_time[merge_time[edge_id]].push_back(edge_id);\n\
    \        }\n    }\n\n    m1une::ds::Dsu components(vertex_count);\n    Mint answer\
    \ = 0;\n    for (int time = 1; time <= edge_count; time++) {\n        for (int\
    \ edge_id : edges_by_time[time]) {\n            const int first = components.leader(edges[edge_id].first);\n\
    \            const int second = components.leader(edges[edge_id].second);\n  \
    \          if (first == second) continue;\n            answer += weight[first]\
    \ * weight[second];\n            components.merge(first, second, [&](int leader,\
    \ int absorbed) {\n                weight[leader] += weight[absorbed];\n     \
    \       });\n        }\n        fast_output << answer.val() << '\\n';\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/incremental_scc\"\n\n#include\
    \ \"../../graph/incremental_scc.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../ds/dsu/dsu.hpp\"\n#include\
    \ \"../../graph/scc.hpp\"\n#include \"../../math/modint.hpp\"\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\n\nvoid validate(const\
    \ Graph& graph, const std::vector<std::pair<int, int>>& edges) {\n    const int\
    \ n = graph.size();\n    const int m = graph.edge_count();\n    assert(int(edges.size())\
    \ == m);\n    const std::vector<int> actual = m1une::graph::incremental_scc(graph);\n\
    \    assert(int(actual.size()) == m);\n\n    std::vector<int> expected(m, m +\
    \ 1);\n    m1une::ds::Dsu replay(n);\n    for (int time = 1; time <= m; time++)\
    \ {\n        Graph prefix(n);\n        for (int edge_id = 0; edge_id < time; edge_id++)\
    \ {\n            if (!graph.is_edge_alive(edge_id)) continue;\n            prefix.add_directed_edge(\n\
    \                edges[edge_id].first,\n                edges[edge_id].second\n\
    \            );\n        }\n        const auto components =\n            m1une::graph::strongly_connected_components(prefix);\n\
    \        for (int edge_id = 0; edge_id < m; edge_id++) {\n            if (edge_id\
    \ >= time || !graph.is_edge_alive(edge_id)) continue;\n            if (expected[edge_id]\
    \ == m + 1 && components.same(\n                    edges[edge_id].first,\n  \
    \                  edges[edge_id].second\n                )) {\n             \
    \   expected[edge_id] = time;\n            }\n            if (actual[edge_id]\
    \ == time) {\n                replay.merge(edges[edge_id].first, edges[edge_id].second);\n\
    \            }\n        }\n        for (int first = 0; first < n; first++) {\n\
    \            for (int second = 0; second < n; second++) {\n                assert(replay.same(first,\
    \ second) ==\n                       components.same(first, second));\n      \
    \      }\n        }\n    }\n    assert(actual == expected);\n}\n\nvoid test_fixed()\
    \ {\n    Graph empty(3);\n    validate(empty, std::vector<std::pair<int, int>>());\n\
    \n    Graph graph(4);\n    std::vector<std::pair<int, int>> edges;\n    edges.emplace_back(0,\
    \ 1);\n    graph.add_directed_edge(0, 1);\n    edges.emplace_back(1, 2);\n   \
    \ graph.add_directed_edge(1, 2);\n    edges.emplace_back(2, 0);\n    graph.add_directed_edge(2,\
    \ 0);\n    edges.emplace_back(2, 3);\n    graph.add_directed_edge(2, 3);\n   \
    \ edges.emplace_back(3, 3);\n    graph.add_directed_edge(3, 3);\n    validate(graph,\
    \ edges);\n    const std::vector<int> time = m1une::graph::incremental_scc(graph);\n\
    \    assert(time[0] == 3);\n    assert(time[1] == 3);\n    assert(time[2] == 3);\n\
    \    assert(time[3] == 6);\n    assert(time[4] == 5);\n\n    graph.erase_edge(2);\n\
    \    validate(graph, edges);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 20260718;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 500; trial++) {\n        const int n = 1 + int(random() %\
    \ 8);\n        const int m = int(random() % 17);\n        Graph graph(n);\n  \
    \      std::vector<std::pair<int, int>> edges;\n        edges.reserve(m);\n  \
    \      for (int edge_id = 0; edge_id < m; edge_id++) {\n            const int\
    \ from = int(random() % n);\n            const int to = int(random() % n);\n \
    \           edges.emplace_back(from, to);\n            const int id = graph.add_directed_edge(from,\
    \ to);\n            if (random() % 7 == 0) graph.erase_edge(id);\n        }\n\
    \        validate(graph, edges);\n    }\n}\n\n}  // namespace\n\nint main() {\n\
    \    test_fixed();\n    test_randomized();\n\n    using Mint = m1une::math::modint998244353;\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    int vertex_count, edge_count;\n    fast_input >> vertex_count\
    \ >> edge_count;\n\n    std::vector<Mint> weight(vertex_count);\n    for (Mint&\
    \ value : weight) {\n        int input;\n        fast_input >> input;\n      \
    \  value = Mint(input);\n    }\n\n    Graph graph(vertex_count);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    edges.reserve(edge_count);\n    for (int edge_id = 0; edge_id\
    \ < edge_count; edge_id++) {\n        int from, to;\n        fast_input >> from\
    \ >> to;\n        edges.emplace_back(from, to);\n        graph.add_directed_edge(from,\
    \ to);\n    }\n\n    const std::vector<int> merge_time =\n        m1une::graph::incremental_scc(graph);\n\
    \    std::vector<std::vector<int>> edges_by_time(edge_count + 1);\n    for (int\
    \ edge_id = 0; edge_id < edge_count; edge_id++) {\n        if (merge_time[edge_id]\
    \ <= edge_count) {\n            edges_by_time[merge_time[edge_id]].push_back(edge_id);\n\
    \        }\n    }\n\n    m1une::ds::Dsu components(vertex_count);\n    Mint answer\
    \ = 0;\n    for (int time = 1; time <= edge_count; time++) {\n        for (int\
    \ edge_id : edges_by_time[time]) {\n            const int first = components.leader(edges[edge_id].first);\n\
    \            const int second = components.leader(edges[edge_id].second);\n  \
    \          if (first == second) continue;\n            answer += weight[first]\
    \ * weight[second];\n            components.merge(first, second, [&](int leader,\
    \ int absorbed) {\n                weight[leader] += weight[absorbed];\n     \
    \       });\n        }\n        fast_output << answer.val() << '\\n';\n    }\n\
    }\n"
  dependsOn:
  - graph/incremental_scc.hpp
  - graph/graph.hpp
  - ds/dsu/dsu.hpp
  - graph/scc.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/incremental_scc.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 23:38:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/incremental_scc.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/incremental_scc.test.cpp
- /verify/verify/graph/incremental_scc.test.cpp.html
title: verify/graph/incremental_scc.test.cpp
---
