---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/minimum_steiner_tree.test.cpp
    title: verify/graph/minimum_steiner_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/minimum_steiner_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <cstddef>\n#include <functional>\n\
    #include <limits>\n#include <optional>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line\
    \ 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class\
    \ T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int\
    \ to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1),\
    \ cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1),\
    \ int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
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
    \ m1une\n\n\n#line 17 \"graph/minimum_steiner_tree.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeResult {\n\
    \    Cost cost;\n    std::vector<int> edge_ids;\n    std::vector<int> vertices;\n\
    };\n\nnamespace internal {\n\ninline std::vector<int> steiner_terminals(int n,\
    \ std::vector<int> terminals) {\n    for (int v : terminals) assert(0 <= v &&\
    \ v < n);\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    assert(terminals.size() < std::numeric_limits<std::size_t>::digits);\n\
    \    return terminals;\n}\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeDp\
    \ {\n    Cost cost;\n    Cost inf;\n    std::size_t states;\n    std::size_t width;\n\
    \    std::vector<Cost> dp;\n    std::vector<int> terminals;\n};\n\ntemplate <class\
    \ Cost, class GraphCost, class EdgeCost>\nstd::optional<MinimumSteinerTreeDp<Cost>>\
    \ minimum_steiner_tree_dp(\n    const Graph<GraphCost>& g,\n    std::vector<int>\
    \ terminals,\n    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost,\n\
    \    Cost inf\n) {\n    const int n = g.size();\n    assert(vertex_cost.size()\
    \ == std::size_t(n));\n    for (Cost cost : vertex_cost) assert(Cost(0) <= cost);\n\
    \    terminals = steiner_terminals(n, std::move(terminals));\n    const int k\
    \ = int(terminals.size());\n    if (k == 0) return MinimumSteinerTreeDp<Cost>{Cost(0),\
    \ inf, 1, std::size_t(n), {}, {}};\n\n    assert(Cost(0) < inf);\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& edge : g[v]) {\n            if\
    \ (edge.alive) assert(Cost(0) <= edge_cost(edge));\n        }\n    }\n\n    const\
    \ std::size_t states = std::size_t(1) << k;\n    const std::size_t width = std::size_t(n);\n\
    \    assert(width <= std::numeric_limits<std::size_t>::max() / states);\n    std::vector<Cost>\
    \ dp(states * width, inf);\n    for (int i = 0; i < k; i++) {\n        const int\
    \ terminal = terminals[i];\n        if (vertex_cost[terminal] < inf) {\n     \
    \       dp[(std::size_t(1) << i) * width + std::size_t(terminal)] = vertex_cost[terminal];\n\
    \        }\n    }\n\n    using QueueEntry = std::pair<Cost, int>;\n    for (std::size_t\
    \ mask = 1; mask < states; mask++) {\n        const std::size_t mask_offset =\
    \ mask * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub\
    \ = (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n \
    \           if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const Cost left = dp[sub_offset +\
    \ vertex];\n                const Cost right = dp[other_offset + vertex];\n  \
    \              if (left == inf || right == inf) continue;\n                assert(vertex_cost[v]\
    \ <= right);\n                const Cost extra = right - vertex_cost[v];\n   \
    \             if (left > inf - extra) continue;\n                const Cost candidate\
    \ = left + extra;\n                Cost& current = dp[mask_offset + vertex];\n\
    \                if (candidate < current) current = candidate;\n            }\n\
    \        }\n\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>,\
    \ std::greater<QueueEntry>> queue;\n        for (int v = 0; v < n; v++) {\n  \
    \          const Cost distance = dp[mask_offset + std::size_t(v)];\n         \
    \   if (distance != inf) queue.emplace(distance, v);\n        }\n        while\
    \ (!queue.empty()) {\n            auto [distance, v] = queue.top();\n        \
    \    queue.pop();\n            if (distance != dp[mask_offset + std::size_t(v)])\
    \ continue;\n            for (const auto& edge : g[v]) {\n                if (!edge.alive)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= inf || vertex_cost[edge.to] > inf - cost) continue;\n       \
    \         const Cost extra = cost + vertex_cost[edge.to];\n                if\
    \ (distance > inf - extra) continue;\n                const Cost candidate = distance\
    \ + extra;\n                Cost& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                if (current <= candidate) continue;\n                current\
    \ = candidate;\n                queue.emplace(candidate, edge.to);\n         \
    \   }\n        }\n    }\n\n    const auto answer_begin = dp.begin() + (states\
    \ - 1) * width;\n    const Cost answer = *std::min_element(answer_begin, dp.end());\n\
    \    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<Cost>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeDp<int>>\
    \ minimum_steiner_tree_unweighted_dp(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    const int n = g.size();\n    terminals = steiner_terminals(n,\
    \ std::move(terminals));\n    const int k = int(terminals.size());\n    if (k\
    \ == 0) return MinimumSteinerTreeDp<int>{0, n, 1, std::size_t(n), {}, {}};\n\n\
    \    const std::size_t states = std::size_t(1) << k;\n    const std::size_t width\
    \ = std::size_t(n);\n    assert(width <= std::numeric_limits<std::size_t>::max()\
    \ / states);\n    const int inf = n;\n    std::vector<int> dp(states * width,\
    \ inf);\n    for (int i = 0; i < k; i++) {\n        dp[(std::size_t(1) << i) *\
    \ width + std::size_t(terminals[i])] = 0;\n    }\n\n    for (std::size_t mask\
    \ = 1; mask < states; mask++) {\n        const std::size_t mask_offset = mask\
    \ * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub =\
    \ (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n   \
    \         if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const int candidate = dp[sub_offset\
    \ + vertex] + dp[other_offset + vertex];\n                int& current = dp[mask_offset\
    \ + vertex];\n                if (candidate < current) current = candidate;\n\
    \            }\n        }\n\n        std::vector<int> bucket_head(n, -1);\n  \
    \      std::vector<int> entry_vertex;\n        std::vector<int> entry_next;\n\
    \        entry_vertex.reserve(2 * width);\n        entry_next.reserve(2 * width);\n\
    \        auto push = [&](int distance, int v) {\n            entry_vertex.push_back(v);\n\
    \            entry_next.push_back(bucket_head[distance]);\n            bucket_head[distance]\
    \ = int(entry_vertex.size()) - 1;\n        };\n        for (int v = 0; v < n;\
    \ v++) {\n            const int distance = dp[mask_offset + std::size_t(v)];\n\
    \            if (distance != inf) push(distance, v);\n        }\n        for (int\
    \ distance = 0; distance < n; distance++) {\n            for (int entry = bucket_head[distance];\
    \ entry != -1; entry = entry_next[entry]) {\n                const int v = entry_vertex[entry];\n\
    \                if (dp[mask_offset + std::size_t(v)] != distance) continue;\n\
    \                for (const auto& edge : g[v]) {\n                    if (!edge.alive)\
    \ continue;\n                    int& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                    if (distance + 1 >= current) continue;\n                \
    \    current = distance + 1;\n                    push(current, edge.to);\n  \
    \              }\n            }\n        }\n    }\n\n    const auto answer_begin\
    \ = dp.begin() + (states - 1) * width;\n    const int answer = *std::min_element(answer_begin,\
    \ dp.end());\n    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<int>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nMinimumSteinerTreeResult<Cost> restore_minimum_steiner_tree(\n\
    \    const Graph<GraphCost>& g,\n    const MinimumSteinerTreeDp<Cost>& data,\n\
    \    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost\n) {\n    MinimumSteinerTreeResult<Cost>\
    \ result;\n    result.cost = data.cost;\n    if (data.terminals.empty()) return\
    \ result;\n\n    const int n = g.size();\n    const std::size_t cells = data.states\
    \ * data.width;\n    std::vector<char> state(cells, 0);\n    std::vector<char>\
    \ selected_edge(g.edge_count(), false);\n\n    std::function<bool(std::size_t,\
    \ int)> restore = [&](std::size_t mask, int start) {\n        const std::size_t\
    \ position = mask * data.width + std::size_t(start);\n        if (state[position]\
    \ == 2) return true;\n        if (state[position] == 1) return false;\n      \
    \  state[position] = 1;\n\n        std::vector<int> search_parent(n, -2), search_edge(n,\
    \ -1), stack;\n        search_parent[start] = -1;\n        stack.push_back(start);\n\
    \        int seed = -1;\n        std::size_t seed_split = 0;\n\n        while\
    \ (!stack.empty() && seed == -1) {\n            const int v = stack.back();\n\
    \            stack.pop_back();\n            const std::size_t vertex_position\
    \ = mask * data.width + std::size_t(v);\n            const Cost current = data.dp[vertex_position];\n\
    \n            if (v != start && state[vertex_position] == 2) {\n             \
    \   seed = v;\n                break;\n            }\n            if ((mask &\
    \ (mask - 1)) == 0) {\n                const int terminal_index = int(std::countr_zero(mask));\n\
    \                if (v == data.terminals[terminal_index] && current == vertex_cost[v])\
    \ {\n                    seed = v;\n                    break;\n             \
    \   }\n            }\n            for (std::size_t sub = (mask - 1) & mask; sub\
    \ != 0; sub = (sub - 1) & mask) {\n                const std::size_t other = mask\
    \ ^ sub;\n                if (sub > other) continue;\n                const Cost\
    \ left = data.dp[sub * data.width + std::size_t(v)];\n                const Cost\
    \ right = data.dp[other * data.width + std::size_t(v)];\n                if (left\
    \ == data.inf || right == data.inf || right < vertex_cost[v]) continue;\n    \
    \            const Cost extra = right - vertex_cost[v];\n                if (left\
    \ > data.inf - extra || left + extra != current) continue;\n                seed\
    \ = v;\n                seed_split = sub;\n                break;\n          \
    \  }\n            if (seed != -1) break;\n\n            for (const auto& edge\
    \ : g[v]) {\n                if (!edge.alive || search_parent[edge.to] != -2)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= data.inf || vertex_cost[v] > data.inf - cost) continue;\n   \
    \             const Cost extra = cost + vertex_cost[v];\n                const\
    \ Cost previous = data.dp[mask * data.width + std::size_t(edge.to)];\n       \
    \         if (previous == data.inf || previous > data.inf - extra) continue;\n\
    \                if (previous + extra != current) continue;\n                search_parent[edge.to]\
    \ = v;\n                search_edge[edge.to] = edge.id;\n                stack.push_back(edge.to);\n\
    \            }\n        }\n\n        if (seed == -1) {\n            state[position]\
    \ = 0;\n            return false;\n        }\n        if (seed_split != 0) {\n\
    \            const bool restored_left = restore(seed_split, seed);\n         \
    \   const bool restored_right = restore(mask ^ seed_split, seed);\n          \
    \  assert(restored_left && restored_right);\n            if (!restored_left ||\
    \ !restored_right) {\n                state[position] = 0;\n                return\
    \ false;\n            }\n        }\n\n        for (int v = seed; v != -1; v =\
    \ search_parent[v]) {\n            state[mask * data.width + std::size_t(v)] =\
    \ 2;\n            if (search_parent[v] == -1) continue;\n            const int\
    \ id = search_edge[v];\n            assert(0 <= id && id < g.edge_count());\n\
    \            selected_edge[id] = true;\n        }\n        return true;\n    };\n\
    \n    int root = -1;\n    const std::size_t full_mask = data.states - 1;\n   \
    \ for (int v = 0; v < n; v++) {\n        if (data.dp[full_mask * data.width +\
    \ std::size_t(v)] == data.cost) {\n            root = v;\n            break;\n\
    \        }\n    }\n    assert(root != -1);\n    const bool restored = restore(full_mask,\
    \ root);\n    assert(restored);\n    (void)restored;\n\n    std::vector<Edge<GraphCost>>\
    \ edge_by_id(g.edge_count());\n    std::vector<char> has_edge(g.edge_count(),\
    \ false);\n    for (const auto& edge : g.edges()) {\n        edge_by_id[edge.id]\
    \ = edge;\n        has_edge[edge.id] = true;\n    }\n\n    std::vector<int> parent(n),\
    \ component_size(n, 1);\n    for (int v = 0; v < n; v++) parent[v] = v;\n    auto\
    \ leader = [&](auto&& self, int v) -> int {\n        if (parent[v] == v) return\
    \ v;\n        return parent[v] = self(self, parent[v]);\n    };\n\n    std::vector<char>\
    \ tree_edge(g.edge_count(), false);\n    for (int id = 0; id < g.edge_count();\
    \ id++) {\n        if (!selected_edge[id]) continue;\n        assert(has_edge[id]);\n\
    \        const auto& edge = edge_by_id[id];\n        int u = leader(leader, edge.from);\n\
    \        int v = leader(leader, edge.to);\n        if (u == v) continue;\n   \
    \     if (component_size[u] < component_size[v]) std::swap(u, v);\n        parent[v]\
    \ = u;\n        component_size[u] += component_size[v];\n        tree_edge[id]\
    \ = true;\n    }\n\n    std::vector<std::vector<std::pair<int, int>>> tree(n);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<char> in_tree(n, false),\
    \ is_terminal(n, false);\n    for (int terminal : data.terminals) {\n        in_tree[terminal]\
    \ = true;\n        is_terminal[terminal] = true;\n    }\n    for (int id = 0;\
    \ id < g.edge_count(); id++) {\n        if (!tree_edge[id]) continue;\n      \
    \  const auto& edge = edge_by_id[id];\n        tree[edge.from].emplace_back(edge.to,\
    \ id);\n        tree[edge.to].emplace_back(edge.from, id);\n        degree[edge.from]++;\n\
    \        degree[edge.to]++;\n        in_tree[edge.from] = true;\n        in_tree[edge.to]\
    \ = true;\n    }\n\n    std::queue<int> leaves;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (in_tree[v] && !is_terminal[v] && degree[v] <= 1) leaves.push(v);\n\
    \    }\n    std::vector<char> removed_vertex(n, false), removed_edge(g.edge_count(),\
    \ false);\n    while (!leaves.empty()) {\n        const int v = leaves.front();\n\
    \        leaves.pop();\n        if (removed_vertex[v] || is_terminal[v] || degree[v]\
    \ > 1) continue;\n        removed_vertex[v] = true;\n        for (auto [to, id]\
    \ : tree[v]) {\n            if (removed_edge[id]) continue;\n            removed_edge[id]\
    \ = true;\n            degree[v]--;\n            degree[to]--;\n            if\
    \ (!is_terminal[to] && degree[to] <= 1) leaves.push(to);\n            break;\n\
    \        }\n    }\n\n    Cost restored_cost = Cost(0);\n    for (int id = 0; id\
    \ < g.edge_count(); id++) {\n        if (!tree_edge[id] || removed_edge[id]) continue;\n\
    \        result.edge_ids.push_back(id);\n        restored_cost += edge_cost(edge_by_id[id]);\n\
    \    }\n    for (int v = 0; v < n; v++) {\n        if (!in_tree[v] || removed_vertex[v])\
    \ continue;\n        result.vertices.push_back(v);\n        restored_cost += vertex_cost[v];\n\
    \    }\n    if constexpr (std::is_integral_v<Cost>) assert(restored_cost == result.cost);\n\
    \    result.cost = restored_cost;\n    return result;\n}\n\n}  // namespace internal\n\
    \ntemplate <class T>\nstd::optional<T> minimum_steiner_tree(\n    const Graph<T>&\
    \ g,\n    std::vector<int> terminals,\n    const std::vector<T>& vertex_cost,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto result = internal::minimum_steiner_tree_dp(\n\
    \        g,\n        std::move(terminals),\n        vertex_cost,\n        [](const\
    \ Edge<T>& edge) { return edge.cost; },\n        inf\n    );\n    if (!result)\
    \ return std::nullopt;\n    return result->cost;\n}\n\ntemplate <class T>\nstd::optional<T>\
    \ minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    return minimum_steiner_tree(g,\
    \ std::move(terminals), std::vector<T>(g.size(), T(0)), inf);\n}\n\ntemplate <class\
    \ GraphCost, class Cost>\nstd::optional<Cost> minimum_steiner_tree_unweighted(\n\
    \    const Graph<GraphCost>& g,\n    std::vector<int> terminals,\n    const std::vector<Cost>&\
    \ vertex_cost,\n    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n\
    \    auto result = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!result) return std::nullopt;\n    return result->cost;\n\
    }\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals,\n    const std::vector<T>&\
    \ vertex_cost,\n    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto\
    \ data = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<T>& edge) { return edge.cost; },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>& edge)\
    \ { return edge.cost; }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>>\
    \ build_minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    std::vector<T> vertex_cost(g.size(),\
    \ T(0));\n    return build_minimum_steiner_tree(g, std::move(terminals), vertex_cost,\
    \ inf);\n}\n\ntemplate <class GraphCost, class Cost>\nstd::optional<MinimumSteinerTreeResult<Cost>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<GraphCost>& g,\n   \
    \ std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n   \
    \ Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n    auto data =\
    \ internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<GraphCost>&)\
    \ { return Cost(1); }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<int>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    auto data = internal::minimum_steiner_tree_unweighted_dp(g,\
    \ std::move(terminals));\n    if (!data) return std::nullopt;\n    std::vector<int>\
    \ vertex_cost(g.size(), 0);\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>&)\
    \ { return 1; }\n    );\n}\n\ntemplate <class T>\nstd::optional<int> minimum_steiner_tree_unweighted(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals\n) {\n    auto result\
    \ = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));\n \
    \   if (!result) return std::nullopt;\n    return result->cost;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP\n#define M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <functional>\n#include <limits>\n#include <optional>\n#include <queue>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n#include \"graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeResult\
    \ {\n    Cost cost;\n    std::vector<int> edge_ids;\n    std::vector<int> vertices;\n\
    };\n\nnamespace internal {\n\ninline std::vector<int> steiner_terminals(int n,\
    \ std::vector<int> terminals) {\n    for (int v : terminals) assert(0 <= v &&\
    \ v < n);\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    assert(terminals.size() < std::numeric_limits<std::size_t>::digits);\n\
    \    return terminals;\n}\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeDp\
    \ {\n    Cost cost;\n    Cost inf;\n    std::size_t states;\n    std::size_t width;\n\
    \    std::vector<Cost> dp;\n    std::vector<int> terminals;\n};\n\ntemplate <class\
    \ Cost, class GraphCost, class EdgeCost>\nstd::optional<MinimumSteinerTreeDp<Cost>>\
    \ minimum_steiner_tree_dp(\n    const Graph<GraphCost>& g,\n    std::vector<int>\
    \ terminals,\n    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost,\n\
    \    Cost inf\n) {\n    const int n = g.size();\n    assert(vertex_cost.size()\
    \ == std::size_t(n));\n    for (Cost cost : vertex_cost) assert(Cost(0) <= cost);\n\
    \    terminals = steiner_terminals(n, std::move(terminals));\n    const int k\
    \ = int(terminals.size());\n    if (k == 0) return MinimumSteinerTreeDp<Cost>{Cost(0),\
    \ inf, 1, std::size_t(n), {}, {}};\n\n    assert(Cost(0) < inf);\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& edge : g[v]) {\n            if\
    \ (edge.alive) assert(Cost(0) <= edge_cost(edge));\n        }\n    }\n\n    const\
    \ std::size_t states = std::size_t(1) << k;\n    const std::size_t width = std::size_t(n);\n\
    \    assert(width <= std::numeric_limits<std::size_t>::max() / states);\n    std::vector<Cost>\
    \ dp(states * width, inf);\n    for (int i = 0; i < k; i++) {\n        const int\
    \ terminal = terminals[i];\n        if (vertex_cost[terminal] < inf) {\n     \
    \       dp[(std::size_t(1) << i) * width + std::size_t(terminal)] = vertex_cost[terminal];\n\
    \        }\n    }\n\n    using QueueEntry = std::pair<Cost, int>;\n    for (std::size_t\
    \ mask = 1; mask < states; mask++) {\n        const std::size_t mask_offset =\
    \ mask * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub\
    \ = (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n \
    \           if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const Cost left = dp[sub_offset +\
    \ vertex];\n                const Cost right = dp[other_offset + vertex];\n  \
    \              if (left == inf || right == inf) continue;\n                assert(vertex_cost[v]\
    \ <= right);\n                const Cost extra = right - vertex_cost[v];\n   \
    \             if (left > inf - extra) continue;\n                const Cost candidate\
    \ = left + extra;\n                Cost& current = dp[mask_offset + vertex];\n\
    \                if (candidate < current) current = candidate;\n            }\n\
    \        }\n\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>,\
    \ std::greater<QueueEntry>> queue;\n        for (int v = 0; v < n; v++) {\n  \
    \          const Cost distance = dp[mask_offset + std::size_t(v)];\n         \
    \   if (distance != inf) queue.emplace(distance, v);\n        }\n        while\
    \ (!queue.empty()) {\n            auto [distance, v] = queue.top();\n        \
    \    queue.pop();\n            if (distance != dp[mask_offset + std::size_t(v)])\
    \ continue;\n            for (const auto& edge : g[v]) {\n                if (!edge.alive)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= inf || vertex_cost[edge.to] > inf - cost) continue;\n       \
    \         const Cost extra = cost + vertex_cost[edge.to];\n                if\
    \ (distance > inf - extra) continue;\n                const Cost candidate = distance\
    \ + extra;\n                Cost& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                if (current <= candidate) continue;\n                current\
    \ = candidate;\n                queue.emplace(candidate, edge.to);\n         \
    \   }\n        }\n    }\n\n    const auto answer_begin = dp.begin() + (states\
    \ - 1) * width;\n    const Cost answer = *std::min_element(answer_begin, dp.end());\n\
    \    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<Cost>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeDp<int>>\
    \ minimum_steiner_tree_unweighted_dp(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    const int n = g.size();\n    terminals = steiner_terminals(n,\
    \ std::move(terminals));\n    const int k = int(terminals.size());\n    if (k\
    \ == 0) return MinimumSteinerTreeDp<int>{0, n, 1, std::size_t(n), {}, {}};\n\n\
    \    const std::size_t states = std::size_t(1) << k;\n    const std::size_t width\
    \ = std::size_t(n);\n    assert(width <= std::numeric_limits<std::size_t>::max()\
    \ / states);\n    const int inf = n;\n    std::vector<int> dp(states * width,\
    \ inf);\n    for (int i = 0; i < k; i++) {\n        dp[(std::size_t(1) << i) *\
    \ width + std::size_t(terminals[i])] = 0;\n    }\n\n    for (std::size_t mask\
    \ = 1; mask < states; mask++) {\n        const std::size_t mask_offset = mask\
    \ * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub =\
    \ (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n   \
    \         if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const int candidate = dp[sub_offset\
    \ + vertex] + dp[other_offset + vertex];\n                int& current = dp[mask_offset\
    \ + vertex];\n                if (candidate < current) current = candidate;\n\
    \            }\n        }\n\n        std::vector<int> bucket_head(n, -1);\n  \
    \      std::vector<int> entry_vertex;\n        std::vector<int> entry_next;\n\
    \        entry_vertex.reserve(2 * width);\n        entry_next.reserve(2 * width);\n\
    \        auto push = [&](int distance, int v) {\n            entry_vertex.push_back(v);\n\
    \            entry_next.push_back(bucket_head[distance]);\n            bucket_head[distance]\
    \ = int(entry_vertex.size()) - 1;\n        };\n        for (int v = 0; v < n;\
    \ v++) {\n            const int distance = dp[mask_offset + std::size_t(v)];\n\
    \            if (distance != inf) push(distance, v);\n        }\n        for (int\
    \ distance = 0; distance < n; distance++) {\n            for (int entry = bucket_head[distance];\
    \ entry != -1; entry = entry_next[entry]) {\n                const int v = entry_vertex[entry];\n\
    \                if (dp[mask_offset + std::size_t(v)] != distance) continue;\n\
    \                for (const auto& edge : g[v]) {\n                    if (!edge.alive)\
    \ continue;\n                    int& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                    if (distance + 1 >= current) continue;\n                \
    \    current = distance + 1;\n                    push(current, edge.to);\n  \
    \              }\n            }\n        }\n    }\n\n    const auto answer_begin\
    \ = dp.begin() + (states - 1) * width;\n    const int answer = *std::min_element(answer_begin,\
    \ dp.end());\n    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<int>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nMinimumSteinerTreeResult<Cost> restore_minimum_steiner_tree(\n\
    \    const Graph<GraphCost>& g,\n    const MinimumSteinerTreeDp<Cost>& data,\n\
    \    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost\n) {\n    MinimumSteinerTreeResult<Cost>\
    \ result;\n    result.cost = data.cost;\n    if (data.terminals.empty()) return\
    \ result;\n\n    const int n = g.size();\n    const std::size_t cells = data.states\
    \ * data.width;\n    std::vector<char> state(cells, 0);\n    std::vector<char>\
    \ selected_edge(g.edge_count(), false);\n\n    std::function<bool(std::size_t,\
    \ int)> restore = [&](std::size_t mask, int start) {\n        const std::size_t\
    \ position = mask * data.width + std::size_t(start);\n        if (state[position]\
    \ == 2) return true;\n        if (state[position] == 1) return false;\n      \
    \  state[position] = 1;\n\n        std::vector<int> search_parent(n, -2), search_edge(n,\
    \ -1), stack;\n        search_parent[start] = -1;\n        stack.push_back(start);\n\
    \        int seed = -1;\n        std::size_t seed_split = 0;\n\n        while\
    \ (!stack.empty() && seed == -1) {\n            const int v = stack.back();\n\
    \            stack.pop_back();\n            const std::size_t vertex_position\
    \ = mask * data.width + std::size_t(v);\n            const Cost current = data.dp[vertex_position];\n\
    \n            if (v != start && state[vertex_position] == 2) {\n             \
    \   seed = v;\n                break;\n            }\n            if ((mask &\
    \ (mask - 1)) == 0) {\n                const int terminal_index = int(std::countr_zero(mask));\n\
    \                if (v == data.terminals[terminal_index] && current == vertex_cost[v])\
    \ {\n                    seed = v;\n                    break;\n             \
    \   }\n            }\n            for (std::size_t sub = (mask - 1) & mask; sub\
    \ != 0; sub = (sub - 1) & mask) {\n                const std::size_t other = mask\
    \ ^ sub;\n                if (sub > other) continue;\n                const Cost\
    \ left = data.dp[sub * data.width + std::size_t(v)];\n                const Cost\
    \ right = data.dp[other * data.width + std::size_t(v)];\n                if (left\
    \ == data.inf || right == data.inf || right < vertex_cost[v]) continue;\n    \
    \            const Cost extra = right - vertex_cost[v];\n                if (left\
    \ > data.inf - extra || left + extra != current) continue;\n                seed\
    \ = v;\n                seed_split = sub;\n                break;\n          \
    \  }\n            if (seed != -1) break;\n\n            for (const auto& edge\
    \ : g[v]) {\n                if (!edge.alive || search_parent[edge.to] != -2)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= data.inf || vertex_cost[v] > data.inf - cost) continue;\n   \
    \             const Cost extra = cost + vertex_cost[v];\n                const\
    \ Cost previous = data.dp[mask * data.width + std::size_t(edge.to)];\n       \
    \         if (previous == data.inf || previous > data.inf - extra) continue;\n\
    \                if (previous + extra != current) continue;\n                search_parent[edge.to]\
    \ = v;\n                search_edge[edge.to] = edge.id;\n                stack.push_back(edge.to);\n\
    \            }\n        }\n\n        if (seed == -1) {\n            state[position]\
    \ = 0;\n            return false;\n        }\n        if (seed_split != 0) {\n\
    \            const bool restored_left = restore(seed_split, seed);\n         \
    \   const bool restored_right = restore(mask ^ seed_split, seed);\n          \
    \  assert(restored_left && restored_right);\n            if (!restored_left ||\
    \ !restored_right) {\n                state[position] = 0;\n                return\
    \ false;\n            }\n        }\n\n        for (int v = seed; v != -1; v =\
    \ search_parent[v]) {\n            state[mask * data.width + std::size_t(v)] =\
    \ 2;\n            if (search_parent[v] == -1) continue;\n            const int\
    \ id = search_edge[v];\n            assert(0 <= id && id < g.edge_count());\n\
    \            selected_edge[id] = true;\n        }\n        return true;\n    };\n\
    \n    int root = -1;\n    const std::size_t full_mask = data.states - 1;\n   \
    \ for (int v = 0; v < n; v++) {\n        if (data.dp[full_mask * data.width +\
    \ std::size_t(v)] == data.cost) {\n            root = v;\n            break;\n\
    \        }\n    }\n    assert(root != -1);\n    const bool restored = restore(full_mask,\
    \ root);\n    assert(restored);\n    (void)restored;\n\n    std::vector<Edge<GraphCost>>\
    \ edge_by_id(g.edge_count());\n    std::vector<char> has_edge(g.edge_count(),\
    \ false);\n    for (const auto& edge : g.edges()) {\n        edge_by_id[edge.id]\
    \ = edge;\n        has_edge[edge.id] = true;\n    }\n\n    std::vector<int> parent(n),\
    \ component_size(n, 1);\n    for (int v = 0; v < n; v++) parent[v] = v;\n    auto\
    \ leader = [&](auto&& self, int v) -> int {\n        if (parent[v] == v) return\
    \ v;\n        return parent[v] = self(self, parent[v]);\n    };\n\n    std::vector<char>\
    \ tree_edge(g.edge_count(), false);\n    for (int id = 0; id < g.edge_count();\
    \ id++) {\n        if (!selected_edge[id]) continue;\n        assert(has_edge[id]);\n\
    \        const auto& edge = edge_by_id[id];\n        int u = leader(leader, edge.from);\n\
    \        int v = leader(leader, edge.to);\n        if (u == v) continue;\n   \
    \     if (component_size[u] < component_size[v]) std::swap(u, v);\n        parent[v]\
    \ = u;\n        component_size[u] += component_size[v];\n        tree_edge[id]\
    \ = true;\n    }\n\n    std::vector<std::vector<std::pair<int, int>>> tree(n);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<char> in_tree(n, false),\
    \ is_terminal(n, false);\n    for (int terminal : data.terminals) {\n        in_tree[terminal]\
    \ = true;\n        is_terminal[terminal] = true;\n    }\n    for (int id = 0;\
    \ id < g.edge_count(); id++) {\n        if (!tree_edge[id]) continue;\n      \
    \  const auto& edge = edge_by_id[id];\n        tree[edge.from].emplace_back(edge.to,\
    \ id);\n        tree[edge.to].emplace_back(edge.from, id);\n        degree[edge.from]++;\n\
    \        degree[edge.to]++;\n        in_tree[edge.from] = true;\n        in_tree[edge.to]\
    \ = true;\n    }\n\n    std::queue<int> leaves;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (in_tree[v] && !is_terminal[v] && degree[v] <= 1) leaves.push(v);\n\
    \    }\n    std::vector<char> removed_vertex(n, false), removed_edge(g.edge_count(),\
    \ false);\n    while (!leaves.empty()) {\n        const int v = leaves.front();\n\
    \        leaves.pop();\n        if (removed_vertex[v] || is_terminal[v] || degree[v]\
    \ > 1) continue;\n        removed_vertex[v] = true;\n        for (auto [to, id]\
    \ : tree[v]) {\n            if (removed_edge[id]) continue;\n            removed_edge[id]\
    \ = true;\n            degree[v]--;\n            degree[to]--;\n            if\
    \ (!is_terminal[to] && degree[to] <= 1) leaves.push(to);\n            break;\n\
    \        }\n    }\n\n    Cost restored_cost = Cost(0);\n    for (int id = 0; id\
    \ < g.edge_count(); id++) {\n        if (!tree_edge[id] || removed_edge[id]) continue;\n\
    \        result.edge_ids.push_back(id);\n        restored_cost += edge_cost(edge_by_id[id]);\n\
    \    }\n    for (int v = 0; v < n; v++) {\n        if (!in_tree[v] || removed_vertex[v])\
    \ continue;\n        result.vertices.push_back(v);\n        restored_cost += vertex_cost[v];\n\
    \    }\n    if constexpr (std::is_integral_v<Cost>) assert(restored_cost == result.cost);\n\
    \    result.cost = restored_cost;\n    return result;\n}\n\n}  // namespace internal\n\
    \ntemplate <class T>\nstd::optional<T> minimum_steiner_tree(\n    const Graph<T>&\
    \ g,\n    std::vector<int> terminals,\n    const std::vector<T>& vertex_cost,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto result = internal::minimum_steiner_tree_dp(\n\
    \        g,\n        std::move(terminals),\n        vertex_cost,\n        [](const\
    \ Edge<T>& edge) { return edge.cost; },\n        inf\n    );\n    if (!result)\
    \ return std::nullopt;\n    return result->cost;\n}\n\ntemplate <class T>\nstd::optional<T>\
    \ minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    return minimum_steiner_tree(g,\
    \ std::move(terminals), std::vector<T>(g.size(), T(0)), inf);\n}\n\ntemplate <class\
    \ GraphCost, class Cost>\nstd::optional<Cost> minimum_steiner_tree_unweighted(\n\
    \    const Graph<GraphCost>& g,\n    std::vector<int> terminals,\n    const std::vector<Cost>&\
    \ vertex_cost,\n    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n\
    \    auto result = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!result) return std::nullopt;\n    return result->cost;\n\
    }\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals,\n    const std::vector<T>&\
    \ vertex_cost,\n    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto\
    \ data = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<T>& edge) { return edge.cost; },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>& edge)\
    \ { return edge.cost; }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>>\
    \ build_minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    std::vector<T> vertex_cost(g.size(),\
    \ T(0));\n    return build_minimum_steiner_tree(g, std::move(terminals), vertex_cost,\
    \ inf);\n}\n\ntemplate <class GraphCost, class Cost>\nstd::optional<MinimumSteinerTreeResult<Cost>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<GraphCost>& g,\n   \
    \ std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n   \
    \ Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n    auto data =\
    \ internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<GraphCost>&)\
    \ { return Cost(1); }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<int>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    auto data = internal::minimum_steiner_tree_unweighted_dp(g,\
    \ std::move(terminals));\n    if (!data) return std::nullopt;\n    std::vector<int>\
    \ vertex_cost(g.size(), 0);\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>&)\
    \ { return 1; }\n    );\n}\n\ntemplate <class T>\nstd::optional<int> minimum_steiner_tree_unweighted(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals\n) {\n    auto result\
    \ = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));\n \
    \   if (!result) return std::nullopt;\n    return result->cost;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: graph/minimum_steiner_tree.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/minimum_steiner_tree.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/minimum_steiner_tree.hpp
layout: document
title: Minimum Steiner Tree
---

## Overview

Finds the minimum cost of a connected subgraph containing every specified
terminal. Non-terminal vertices may be used as Steiner vertices. The objective
can include edge costs alone or both edge and vertex costs. Each selected edge
and each selected vertex is charged exactly once.

Use `minimum_steiner_tree` when only the optimum cost is needed. Use
`build_minimum_steiner_tree` to also obtain the vertices and logical edge ids of
one optimum tree. The corresponding `_unweighted` functions ignore stored edge
costs and charge one per selected edge.

All overloads use the Dreyfus--Wagner subset DP. Stored edge weights or vertex
weights require a multi-source Dijkstra step for each terminal subset. When all
edges have unit cost and no vertex weights are supplied, a bucketed
multi-source BFS removes the logarithmic factor.

## Requirements and Behavior

The graph must be undirected and should be built with `add_edge`.

* Weighted edge and vertex costs must be non-negative.
* A supplied `vertex_cost` vector must have exactly $N$ elements. Its value for
  every terminal and every selected Steiner vertex is included once.
* `minimum_steiner_tree_unweighted` treats every active edge as having cost one.
* Inactive edges are ignored.
* Duplicate terminals are removed internally.
* An empty terminal set has cost zero. A one-vertex terminal set costs that
  vertex's weight when `vertex_cost` is supplied, and zero otherwise.
* The result is `std::nullopt` when no connected subgraph contains every
  terminal.
* Build functions return an actual acyclic tree. Their `edge_ids` and `vertices`
  are sorted and contain no duplicates.
* Build functions remove redundant zero-cost cycles and non-terminal leaves
  without changing the optimum cost.

The default `inf` for weighted overloads is
`std::numeric_limits<Cost>::max() / Cost(4)`. Pass a larger safe value when a
valid answer can reach that sentinel.

## Result Type

`MinimumSteinerTreeResult<Cost>` contains:

| Member | Type | Description |
| --- | --- | --- |
| `cost` | `Cost` | Total cost of the returned tree. |
| `edge_ids` | `std::vector<int>` | Sorted logical edge ids in the tree. |
| `vertices` | `std::vector<int>` | Sorted vertices in the tree, including every terminal. |

## Functions

Let $N$ be the number of vertices, $M$ the number of undirected edges, and $K$
the number of distinct terminals.

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `minimum_steiner_tree` | `template <class T> std::optional<T> minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, T inf = std::numeric_limits<T>::max() / T(4))` | Returns the minimum total stored edge cost. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree` | `template <class T> std::optional<T> minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, const std::vector<T>& vertex_cost, T inf = std::numeric_limits<T>::max() / T(4))` | Returns the minimum total stored edge cost plus selected vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree_unweighted` | `template <class T> std::optional<int> minimum_steiner_tree_unweighted(const Graph<T>& g, std::vector<int> terminals)` | Returns the minimum number of edges, ignoring stored costs. | $O(3^K N + 2^K (N+M))$ time, $O(2^K N + N + M)$ memory. |
| `minimum_steiner_tree_unweighted` | `template <class GraphCost, class Cost> std::optional<Cost> minimum_steiner_tree_unweighted(const Graph<GraphCost>& g, std::vector<int> terminals, const std::vector<Cost>& vertex_cost, Cost inf = std::numeric_limits<Cost>::max() / Cost(4))` | Returns the number of selected edges plus selected vertex costs, ignoring stored edge costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree` | `template <class T> std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, T inf = std::numeric_limits<T>::max() / T(4))` | Returns one optimum tree using stored edge costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree` | `template <class T> std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(const Graph<T>& g, std::vector<int> terminals, const std::vector<T>& vertex_cost, T inf = std::numeric_limits<T>::max() / T(4))` | Returns one optimum tree using stored edge and vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree_unweighted` | `template <class T> std::optional<MinimumSteinerTreeResult<int>> build_minimum_steiner_tree_unweighted(const Graph<T>& g, std::vector<int> terminals)` | Returns one optimum unit-edge tree. | $O(3^K N + 2^K (N+M))$ time, $O(2^K N + N + M)$ memory. |
| `build_minimum_steiner_tree_unweighted` | `template <class GraphCost, class Cost> std::optional<MinimumSteinerTreeResult<Cost>> build_minimum_steiner_tree_unweighted(const Graph<GraphCost>& g, std::vector<int> terminals, const std::vector<Cost>& vertex_cost, Cost inf = std::numeric_limits<Cost>::max() / Cost(4))` | Returns one optimum tree using unit edge costs and supplied vertex costs. | $O(3^K N + 2^K (N+M) \log N)$ time, $O(2^K N + N + M)$ memory. |

The problem is NP-hard in general, so these functions are intended for small
$K$ (often around 15 terminals, depending on $N$ and the time limit).

## Example

```cpp
#include "graph/minimum_steiner_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::graph::Graph<long long> g(5);
    g.add_edge(0, 1, 4);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 2);
    g.add_edge(3, 4, 3);
    g.add_edge(0, 4, 20);

    std::vector<int> terminals = {0, 2, 4};
    std::vector<long long> vertex_cost = {2, 3, 7, 5, 11};
    auto answer = m1une::graph::build_minimum_steiner_tree(g, terminals, vertex_cost);
    if (answer) {
        std::cout << answer->cost << "\n";  // 38
        for (int edge_id : answer->edge_ids) std::cout << edge_id << " ";
        std::cout << "\n";
    }
}
```
