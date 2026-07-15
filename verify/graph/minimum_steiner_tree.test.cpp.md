---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/minimum_steiner_tree.hpp
    title: Minimum Steiner Tree
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040
  bundledCode: "#line 1 \"verify/graph/minimum_steiner_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040\"\n\n#line\
    \ 1 \"graph/minimum_steiner_tree.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <cstddef>\n#include <functional>\n#include <limits>\n\
    #include <optional>\n#include <queue>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     _g[u].push_back(edge_type(u, v, cost, id));\n        int v_idx = int(_g[v].size());\n\
    \        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/minimum_steiner_tree.test.cpp\"\
    \n\n#line 7 \"verify/graph/minimum_steiner_tree.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/graph/minimum_steiner_tree.test.cpp\"\
    \n#include <numeric>\n#line 14 \"verify/graph/minimum_steiner_tree.test.cpp\"\n\
    \nnamespace {\n\nstruct NaiveDsu {\n    std::vector<int> parent;\n\n    explicit\
    \ NaiveDsu(int n) : parent(n) {\n        std::iota(parent.begin(), parent.end(),\
    \ 0);\n    }\n\n    int leader(int v) {\n        if (parent[v] == v) return v;\n\
    \        return parent[v] = leader(parent[v]);\n    }\n\n    void merge(int u,\
    \ int v) {\n        u = leader(u);\n        v = leader(v);\n        if (u != v)\
    \ parent[u] = v;\n    }\n};\n\ntemplate <class T>\nstd::pair<std::optional<T>,\
    \ std::optional<int>> naive(\n    const m1une::graph::Graph<T>& graph,\n    std::vector<int>\
    \ terminals\n) {\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    if (terminals.empty()) return {T(0),\
    \ 0};\n\n    const auto edges = graph.edges();\n    assert(edges.size() < std::numeric_limits<std::uint64_t>::digits);\n\
    \    std::optional<T> weighted;\n    std::optional<int> unweighted;\n    for (std::uint64_t\
    \ mask = 0; mask < (std::uint64_t(1) << edges.size()); mask++) {\n        NaiveDsu\
    \ dsu(graph.size());\n        T cost = T(0);\n        int count = 0;\n       \
    \ for (int i = 0; i < int(edges.size()); i++) {\n            if ((mask >> i &\
    \ 1) == 0) continue;\n            dsu.merge(edges[i].from, edges[i].to);\n   \
    \         cost += edges[i].cost;\n            count++;\n        }\n\n        bool\
    \ connected = true;\n        for (int v : terminals) {\n            if (dsu.leader(v)\
    \ != dsu.leader(terminals[0])) connected = false;\n        }\n        if (!connected)\
    \ continue;\n        if (!weighted || cost < *weighted) weighted = cost;\n   \
    \     if (!unweighted || count < *unweighted) unweighted = count;\n    }\n   \
    \ return {weighted, unweighted};\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nstd::optional<Cost> naive_with_vertex_cost(\n    const m1une::graph::Graph<GraphCost>&\
    \ graph,\n    std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n\
    \    EdgeCost edge_cost\n) {\n    std::sort(terminals.begin(), terminals.end());\n\
    \    terminals.erase(std::unique(terminals.begin(), terminals.end()), terminals.end());\n\
    \    if (terminals.empty()) return Cost(0);\n\n    const auto edges = graph.edges();\n\
    \    std::optional<Cost> answer;\n    for (std::uint64_t mask = 0; mask < (std::uint64_t(1)\
    \ << edges.size()); mask++) {\n        NaiveDsu dsu(graph.size());\n        std::vector<char>\
    \ used(graph.size(), false);\n        for (int terminal : terminals) used[terminal]\
    \ = true;\n        Cost cost = Cost(0);\n        for (int i = 0; i < int(edges.size());\
    \ i++) {\n            if ((mask >> i & 1) == 0) continue;\n            dsu.merge(edges[i].from,\
    \ edges[i].to);\n            used[edges[i].from] = true;\n            used[edges[i].to]\
    \ = true;\n            cost += edge_cost(edges[i]);\n        }\n        for (int\
    \ v = 0; v < graph.size(); v++) {\n            if (used[v]) cost += vertex_cost[v];\n\
    \        }\n\n        bool connected = true;\n        for (int v : terminals)\
    \ {\n            if (dsu.leader(v) != dsu.leader(terminals[0])) connected = false;\n\
    \        }\n        if (connected && (!answer || cost < *answer)) answer = cost;\n\
    \    }\n    return answer;\n}\n\ntemplate <class Cost, class GraphCost, class\
    \ EdgeCost>\nvoid validate_built_tree(\n    const m1une::graph::Graph<GraphCost>&\
    \ graph,\n    const m1une::graph::MinimumSteinerTreeResult<Cost>& result,\n  \
    \  const std::vector<int>& terminals,\n    const std::vector<Cost>& vertex_cost,\n\
    \    EdgeCost edge_cost\n) {\n    assert(std::is_sorted(result.edge_ids.begin(),\
    \ result.edge_ids.end()));\n    assert(std::adjacent_find(result.edge_ids.begin(),\
    \ result.edge_ids.end()) == result.edge_ids.end());\n    assert(std::is_sorted(result.vertices.begin(),\
    \ result.vertices.end()));\n    assert(std::adjacent_find(result.vertices.begin(),\
    \ result.vertices.end()) == result.vertices.end());\n\n    std::vector<m1une::graph::Edge<GraphCost>>\
    \ edge_by_id(graph.edge_count());\n    for (const auto& edge : graph.edges())\
    \ edge_by_id[edge.id] = edge;\n    NaiveDsu dsu(graph.size());\n    Cost cost\
    \ = Cost(0);\n    for (int id : result.edge_ids) {\n        assert(0 <= id &&\
    \ id < graph.edge_count());\n        assert(graph.is_edge_alive(id));\n      \
    \  const auto& edge = edge_by_id[id];\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), edge.from));\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), edge.to));\n        assert(dsu.leader(edge.from) != dsu.leader(edge.to));\n\
    \        dsu.merge(edge.from, edge.to);\n        cost += edge_cost(edge);\n  \
    \  }\n    for (int v : result.vertices) cost += vertex_cost[v];\n    for (int\
    \ terminal : terminals) {\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), terminal));\n    }\n    if (result.vertices.empty())\
    \ {\n        assert(terminals.empty() && result.edge_ids.empty());\n    } else\
    \ {\n        assert(result.edge_ids.size() + 1 == result.vertices.size());\n \
    \       for (int v : result.vertices) assert(dsu.leader(v) == dsu.leader(result.vertices[0]));\n\
    \    }\n    assert(cost == result.cost);\n}\n\nvoid test_examples_and_failures()\
    \ {\n    m1une::graph::Graph<long long> graph(6);\n    graph.add_edge(0, 1, 4);\n\
    \    graph.add_edge(1, 2, 1);\n    graph.add_edge(1, 3, 2);\n    graph.add_edge(3,\
    \ 4, 3);\n    graph.add_edge(0, 4, 20);\n\n    auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{0, 2, 4});\n    auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4}\n    );\n    assert(weighted\
    \ && *weighted == 10);\n    assert(unweighted && *unweighted == 3);\n    assert(!m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{0, 5}));\n    assert(!m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ std::vector<int>{0, 5}));\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{2, 2}) == 0);\n    assert(*m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ std::vector<int>()) == 0);\n\n    const std::vector<long long> vertex_cost =\
    \ {2, 3, 7, 5, 11, 13};\n    auto vertex_weighted = m1une::graph::minimum_steiner_tree(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    auto vertex_weighted_unit_edges = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    assert(vertex_weighted && *vertex_weighted == 38);\n    assert(vertex_weighted_unit_edges\
    \ && *vertex_weighted_unit_edges == 26);\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{2}, vertex_cost) == 7);\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>(), vertex_cost) == 0);\n\n    m1une::graph::Graph<int> unit_graph(2);\n\
    \    unit_graph.add_edge(0, 1, 100);\n    const std::vector<long long> large_vertex_cost\
    \ = {3'000'000'000LL, 4'000'000'000LL};\n    auto independent_cost_type = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        unit_graph,\n        std::vector<int>{0, 1},\n        large_vertex_cost\n\
    \    );\n    assert(independent_cost_type && *independent_cost_type == 7'000'000'001LL);\n\
    \n    auto built = m1une::graph::build_minimum_steiner_tree(\n        graph,\n\
    \        std::vector<int>{0, 2, 4},\n        vertex_cost\n    );\n    assert(built\
    \ && built->cost == 38);\n    validate_built_tree(\n        graph,\n        *built,\n\
    \        std::vector<int>{0, 2, 4},\n        vertex_cost,\n        [](const auto&\
    \ edge) { return edge.cost; }\n    );\n    auto built_unit = m1une::graph::build_minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    assert(built_unit && built_unit->cost == 26);\n    validate_built_tree(\n\
    \        graph,\n        *built_unit,\n        std::vector<int>{0, 2, 4},\n  \
    \      vertex_cost,\n        [](const auto&) { return 1LL; }\n    );\n\n    m1une::graph::Graph<long\
    \ long> zero_cycle(3);\n    zero_cycle.add_edge(0, 1, 0);\n    zero_cycle.add_edge(1,\
    \ 2, 0);\n    zero_cycle.add_edge(2, 0, 0);\n    auto zero_cycle_tree = m1une::graph::build_minimum_steiner_tree(\n\
    \        zero_cycle,\n        std::vector<int>{0, 1, 2}\n    );\n    assert(zero_cycle_tree\
    \ && zero_cycle_tree->cost == 0);\n    assert(zero_cycle_tree->edge_ids.size()\
    \ == 2);\n    validate_built_tree(\n        zero_cycle,\n        *zero_cycle_tree,\n\
    \        std::vector<int>{0, 1, 2},\n        std::vector<long long>(3, 0),\n \
    \       [](const auto& edge) { return edge.cost; }\n    );\n\n    auto single_vertex_tree\
    \ = m1une::graph::build_minimum_steiner_tree(\n        graph,\n        std::vector<int>{2},\n\
    \        vertex_cost\n    );\n    assert(single_vertex_tree && single_vertex_tree->vertices\
    \ == std::vector<int>{2});\n    assert(single_vertex_tree->edge_ids.empty() &&\
    \ single_vertex_tree->cost == 7);\n    auto empty_tree = m1une::graph::build_minimum_steiner_tree(\n\
    \        graph,\n        std::vector<int>(),\n        vertex_cost\n    );\n  \
    \  assert(empty_tree && empty_tree->vertices.empty() && empty_tree->edge_ids.empty());\n\
    \n    int removed = graph.add_edge(4, 5, 1);\n    graph.erase_edge(removed);\n\
    \    assert(!m1une::graph::minimum_steiner_tree(graph, std::vector<int>{0, 5}));\n\
    \    assert(!m1une::graph::build_minimum_steiner_tree(graph, std::vector<int>{0,\
    \ 5}));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x243f6a8885a308d3ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 100; trial++) {\n        const int n = 1 + int(random() % 7);\n        std::vector<std::pair<int,\
    \ int>> pairs;\n        for (int u = 0; u < n; u++) {\n            for (int v\
    \ = u + 1; v < n; v++) pairs.emplace_back(u, v);\n        }\n        for (int\
    \ i = int(pairs.size()) - 1; i > 0; i--) {\n            std::swap(pairs[i], pairs[random()\
    \ % (i + 1)]);\n        }\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        const int m = int(random() % (std::min<int>(10, pairs.size()) + 1));\n\
    \        for (int i = 0; i < m; i++) {\n            graph.add_edge(pairs[i].first,\
    \ pairs[i].second, random() % 10);\n        }\n        if (m > 0 && trial % 7\
    \ == 0) graph.erase_edge(int(random() % m));\n\n        std::vector<int> terminals;\n\
    \        for (int v = 0; v < n; v++) {\n            if (random() % 3 == 0) terminals.push_back(v);\n\
    \        }\n        if (!terminals.empty() && trial % 5 == 0) terminals.push_back(terminals.back());\n\
    \n        std::vector<long long> vertex_cost(n);\n        for (long long& cost\
    \ : vertex_cost) cost = random() % 8;\n\n        auto expected = naive(graph,\
    \ terminals);\n        auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ terminals);\n        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ terminals);\n        assert(weighted == expected.first);\n        assert(unweighted\
    \ == expected.second);\n\n        auto expected_vertex_weighted = naive_with_vertex_cost<long\
    \ long>(\n            graph,\n            terminals,\n            vertex_cost,\n\
    \            [](const auto& edge) { return edge.cost; }\n        );\n        auto\
    \ expected_vertex_weighted_unit_edges = naive_with_vertex_cost<long long>(\n \
    \           graph,\n            terminals,\n            vertex_cost,\n       \
    \     [](const auto&) { return 1LL; }\n        );\n        auto vertex_weighted\
    \ = m1une::graph::minimum_steiner_tree(\n            graph,\n            terminals,\n\
    \            vertex_cost\n        );\n        auto vertex_weighted_unit_edges\
    \ = m1une::graph::minimum_steiner_tree_unweighted(\n            graph,\n     \
    \       terminals,\n            vertex_cost\n        );\n        assert(vertex_weighted\
    \ == expected_vertex_weighted);\n        assert(vertex_weighted_unit_edges ==\
    \ expected_vertex_weighted_unit_edges);\n\n        const std::vector<long long>\
    \ zero_vertex_cost(n, 0);\n        auto built_weighted = m1une::graph::build_minimum_steiner_tree(graph,\
    \ terminals);\n        auto built_unweighted = m1une::graph::build_minimum_steiner_tree_unweighted(\n\
    \            graph,\n            terminals\n        );\n        auto built_vertex_weighted\
    \ = m1une::graph::build_minimum_steiner_tree(\n            graph,\n          \
    \  terminals,\n            vertex_cost\n        );\n        auto built_vertex_weighted_unit_edges\
    \ =\n            m1une::graph::build_minimum_steiner_tree_unweighted(graph, terminals,\
    \ vertex_cost);\n        assert(bool(built_weighted) == bool(expected.first));\n\
    \        assert(bool(built_unweighted) == bool(expected.second));\n        assert(bool(built_vertex_weighted)\
    \ == bool(expected_vertex_weighted));\n        assert(\n            bool(built_vertex_weighted_unit_edges)\
    \ == bool(expected_vertex_weighted_unit_edges)\n        );\n        if (built_weighted)\
    \ {\n            assert(built_weighted->cost == *expected.first);\n          \
    \  validate_built_tree(\n                graph,\n                *built_weighted,\n\
    \                terminals,\n                zero_vertex_cost,\n             \
    \   [](const auto& edge) { return edge.cost; }\n            );\n        }\n  \
    \      if (built_unweighted) {\n            assert(built_unweighted->cost == *expected.second);\n\
    \            validate_built_tree(\n                graph,\n                *built_unweighted,\n\
    \                terminals,\n                std::vector<int>(n, 0),\n       \
    \         [](const auto&) { return 1; }\n            );\n        }\n        if\
    \ (built_vertex_weighted) {\n            assert(built_vertex_weighted->cost ==\
    \ *expected_vertex_weighted);\n            validate_built_tree(\n            \
    \    graph,\n                *built_vertex_weighted,\n                terminals,\n\
    \                vertex_cost,\n                [](const auto& edge) { return edge.cost;\
    \ }\n            );\n        }\n        if (built_vertex_weighted_unit_edges)\
    \ {\n            assert(built_vertex_weighted_unit_edges->cost == *expected_vertex_weighted_unit_edges);\n\
    \            validate_built_tree(\n                graph,\n                *built_vertex_weighted_unit_edges,\n\
    \                terminals,\n                vertex_cost,\n                [](const\
    \ auto&) { return 1LL; }\n            );\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_examples_and_failures();\n    test_randomized();\n\n\
    \    int height, width;\n    while (fast_input >> height >> width, height != 0)\
    \ {\n        m1une::graph::Graph<int> graph(height * width);\n        std::vector<int>\
    \ terminals;\n        for (int row = 0; row < height; row++) {\n            for\
    \ (int column = 0; column < width; column++) {\n                int required;\n\
    \                fast_input >> required;\n                const int vertex = row\
    \ * width + column;\n                if (row > 0) graph.add_edge(vertex, vertex\
    \ - width);\n                if (column > 0) graph.add_edge(vertex, vertex - 1);\n\
    \                if (required == 1) terminals.push_back(vertex);\n           \
    \ }\n        }\n\n        auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ terminals);\n        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ terminals);\n        assert(weighted && unweighted && *weighted == *unweighted);\n\
    \        fast_output << height * width - *unweighted - 1 << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040\"\
    \n\n#include \"../../graph/minimum_steiner_tree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <limits>\n#include <numeric>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nstruct NaiveDsu {\n    std::vector<int> parent;\n\
    \n    explicit NaiveDsu(int n) : parent(n) {\n        std::iota(parent.begin(),\
    \ parent.end(), 0);\n    }\n\n    int leader(int v) {\n        if (parent[v] ==\
    \ v) return v;\n        return parent[v] = leader(parent[v]);\n    }\n\n    void\
    \ merge(int u, int v) {\n        u = leader(u);\n        v = leader(v);\n    \
    \    if (u != v) parent[u] = v;\n    }\n};\n\ntemplate <class T>\nstd::pair<std::optional<T>,\
    \ std::optional<int>> naive(\n    const m1une::graph::Graph<T>& graph,\n    std::vector<int>\
    \ terminals\n) {\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    if (terminals.empty()) return {T(0),\
    \ 0};\n\n    const auto edges = graph.edges();\n    assert(edges.size() < std::numeric_limits<std::uint64_t>::digits);\n\
    \    std::optional<T> weighted;\n    std::optional<int> unweighted;\n    for (std::uint64_t\
    \ mask = 0; mask < (std::uint64_t(1) << edges.size()); mask++) {\n        NaiveDsu\
    \ dsu(graph.size());\n        T cost = T(0);\n        int count = 0;\n       \
    \ for (int i = 0; i < int(edges.size()); i++) {\n            if ((mask >> i &\
    \ 1) == 0) continue;\n            dsu.merge(edges[i].from, edges[i].to);\n   \
    \         cost += edges[i].cost;\n            count++;\n        }\n\n        bool\
    \ connected = true;\n        for (int v : terminals) {\n            if (dsu.leader(v)\
    \ != dsu.leader(terminals[0])) connected = false;\n        }\n        if (!connected)\
    \ continue;\n        if (!weighted || cost < *weighted) weighted = cost;\n   \
    \     if (!unweighted || count < *unweighted) unweighted = count;\n    }\n   \
    \ return {weighted, unweighted};\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nstd::optional<Cost> naive_with_vertex_cost(\n    const m1une::graph::Graph<GraphCost>&\
    \ graph,\n    std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n\
    \    EdgeCost edge_cost\n) {\n    std::sort(terminals.begin(), terminals.end());\n\
    \    terminals.erase(std::unique(terminals.begin(), terminals.end()), terminals.end());\n\
    \    if (terminals.empty()) return Cost(0);\n\n    const auto edges = graph.edges();\n\
    \    std::optional<Cost> answer;\n    for (std::uint64_t mask = 0; mask < (std::uint64_t(1)\
    \ << edges.size()); mask++) {\n        NaiveDsu dsu(graph.size());\n        std::vector<char>\
    \ used(graph.size(), false);\n        for (int terminal : terminals) used[terminal]\
    \ = true;\n        Cost cost = Cost(0);\n        for (int i = 0; i < int(edges.size());\
    \ i++) {\n            if ((mask >> i & 1) == 0) continue;\n            dsu.merge(edges[i].from,\
    \ edges[i].to);\n            used[edges[i].from] = true;\n            used[edges[i].to]\
    \ = true;\n            cost += edge_cost(edges[i]);\n        }\n        for (int\
    \ v = 0; v < graph.size(); v++) {\n            if (used[v]) cost += vertex_cost[v];\n\
    \        }\n\n        bool connected = true;\n        for (int v : terminals)\
    \ {\n            if (dsu.leader(v) != dsu.leader(terminals[0])) connected = false;\n\
    \        }\n        if (connected && (!answer || cost < *answer)) answer = cost;\n\
    \    }\n    return answer;\n}\n\ntemplate <class Cost, class GraphCost, class\
    \ EdgeCost>\nvoid validate_built_tree(\n    const m1une::graph::Graph<GraphCost>&\
    \ graph,\n    const m1une::graph::MinimumSteinerTreeResult<Cost>& result,\n  \
    \  const std::vector<int>& terminals,\n    const std::vector<Cost>& vertex_cost,\n\
    \    EdgeCost edge_cost\n) {\n    assert(std::is_sorted(result.edge_ids.begin(),\
    \ result.edge_ids.end()));\n    assert(std::adjacent_find(result.edge_ids.begin(),\
    \ result.edge_ids.end()) == result.edge_ids.end());\n    assert(std::is_sorted(result.vertices.begin(),\
    \ result.vertices.end()));\n    assert(std::adjacent_find(result.vertices.begin(),\
    \ result.vertices.end()) == result.vertices.end());\n\n    std::vector<m1une::graph::Edge<GraphCost>>\
    \ edge_by_id(graph.edge_count());\n    for (const auto& edge : graph.edges())\
    \ edge_by_id[edge.id] = edge;\n    NaiveDsu dsu(graph.size());\n    Cost cost\
    \ = Cost(0);\n    for (int id : result.edge_ids) {\n        assert(0 <= id &&\
    \ id < graph.edge_count());\n        assert(graph.is_edge_alive(id));\n      \
    \  const auto& edge = edge_by_id[id];\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), edge.from));\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), edge.to));\n        assert(dsu.leader(edge.from) != dsu.leader(edge.to));\n\
    \        dsu.merge(edge.from, edge.to);\n        cost += edge_cost(edge);\n  \
    \  }\n    for (int v : result.vertices) cost += vertex_cost[v];\n    for (int\
    \ terminal : terminals) {\n        assert(std::binary_search(result.vertices.begin(),\
    \ result.vertices.end(), terminal));\n    }\n    if (result.vertices.empty())\
    \ {\n        assert(terminals.empty() && result.edge_ids.empty());\n    } else\
    \ {\n        assert(result.edge_ids.size() + 1 == result.vertices.size());\n \
    \       for (int v : result.vertices) assert(dsu.leader(v) == dsu.leader(result.vertices[0]));\n\
    \    }\n    assert(cost == result.cost);\n}\n\nvoid test_examples_and_failures()\
    \ {\n    m1une::graph::Graph<long long> graph(6);\n    graph.add_edge(0, 1, 4);\n\
    \    graph.add_edge(1, 2, 1);\n    graph.add_edge(1, 3, 2);\n    graph.add_edge(3,\
    \ 4, 3);\n    graph.add_edge(0, 4, 20);\n\n    auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{0, 2, 4});\n    auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4}\n    );\n    assert(weighted\
    \ && *weighted == 10);\n    assert(unweighted && *unweighted == 3);\n    assert(!m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{0, 5}));\n    assert(!m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ std::vector<int>{0, 5}));\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{2, 2}) == 0);\n    assert(*m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ std::vector<int>()) == 0);\n\n    const std::vector<long long> vertex_cost =\
    \ {2, 3, 7, 5, 11, 13};\n    auto vertex_weighted = m1une::graph::minimum_steiner_tree(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    auto vertex_weighted_unit_edges = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    assert(vertex_weighted && *vertex_weighted == 38);\n    assert(vertex_weighted_unit_edges\
    \ && *vertex_weighted_unit_edges == 26);\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>{2}, vertex_cost) == 7);\n    assert(*m1une::graph::minimum_steiner_tree(graph,\
    \ std::vector<int>(), vertex_cost) == 0);\n\n    m1une::graph::Graph<int> unit_graph(2);\n\
    \    unit_graph.add_edge(0, 1, 100);\n    const std::vector<long long> large_vertex_cost\
    \ = {3'000'000'000LL, 4'000'000'000LL};\n    auto independent_cost_type = m1une::graph::minimum_steiner_tree_unweighted(\n\
    \        unit_graph,\n        std::vector<int>{0, 1},\n        large_vertex_cost\n\
    \    );\n    assert(independent_cost_type && *independent_cost_type == 7'000'000'001LL);\n\
    \n    auto built = m1une::graph::build_minimum_steiner_tree(\n        graph,\n\
    \        std::vector<int>{0, 2, 4},\n        vertex_cost\n    );\n    assert(built\
    \ && built->cost == 38);\n    validate_built_tree(\n        graph,\n        *built,\n\
    \        std::vector<int>{0, 2, 4},\n        vertex_cost,\n        [](const auto&\
    \ edge) { return edge.cost; }\n    );\n    auto built_unit = m1une::graph::build_minimum_steiner_tree_unweighted(\n\
    \        graph,\n        std::vector<int>{0, 2, 4},\n        vertex_cost\n   \
    \ );\n    assert(built_unit && built_unit->cost == 26);\n    validate_built_tree(\n\
    \        graph,\n        *built_unit,\n        std::vector<int>{0, 2, 4},\n  \
    \      vertex_cost,\n        [](const auto&) { return 1LL; }\n    );\n\n    m1une::graph::Graph<long\
    \ long> zero_cycle(3);\n    zero_cycle.add_edge(0, 1, 0);\n    zero_cycle.add_edge(1,\
    \ 2, 0);\n    zero_cycle.add_edge(2, 0, 0);\n    auto zero_cycle_tree = m1une::graph::build_minimum_steiner_tree(\n\
    \        zero_cycle,\n        std::vector<int>{0, 1, 2}\n    );\n    assert(zero_cycle_tree\
    \ && zero_cycle_tree->cost == 0);\n    assert(zero_cycle_tree->edge_ids.size()\
    \ == 2);\n    validate_built_tree(\n        zero_cycle,\n        *zero_cycle_tree,\n\
    \        std::vector<int>{0, 1, 2},\n        std::vector<long long>(3, 0),\n \
    \       [](const auto& edge) { return edge.cost; }\n    );\n\n    auto single_vertex_tree\
    \ = m1une::graph::build_minimum_steiner_tree(\n        graph,\n        std::vector<int>{2},\n\
    \        vertex_cost\n    );\n    assert(single_vertex_tree && single_vertex_tree->vertices\
    \ == std::vector<int>{2});\n    assert(single_vertex_tree->edge_ids.empty() &&\
    \ single_vertex_tree->cost == 7);\n    auto empty_tree = m1une::graph::build_minimum_steiner_tree(\n\
    \        graph,\n        std::vector<int>(),\n        vertex_cost\n    );\n  \
    \  assert(empty_tree && empty_tree->vertices.empty() && empty_tree->edge_ids.empty());\n\
    \n    int removed = graph.add_edge(4, 5, 1);\n    graph.erase_edge(removed);\n\
    \    assert(!m1une::graph::minimum_steiner_tree(graph, std::vector<int>{0, 5}));\n\
    \    assert(!m1une::graph::build_minimum_steiner_tree(graph, std::vector<int>{0,\
    \ 5}));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x243f6a8885a308d3ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 100; trial++) {\n        const int n = 1 + int(random() % 7);\n        std::vector<std::pair<int,\
    \ int>> pairs;\n        for (int u = 0; u < n; u++) {\n            for (int v\
    \ = u + 1; v < n; v++) pairs.emplace_back(u, v);\n        }\n        for (int\
    \ i = int(pairs.size()) - 1; i > 0; i--) {\n            std::swap(pairs[i], pairs[random()\
    \ % (i + 1)]);\n        }\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        const int m = int(random() % (std::min<int>(10, pairs.size()) + 1));\n\
    \        for (int i = 0; i < m; i++) {\n            graph.add_edge(pairs[i].first,\
    \ pairs[i].second, random() % 10);\n        }\n        if (m > 0 && trial % 7\
    \ == 0) graph.erase_edge(int(random() % m));\n\n        std::vector<int> terminals;\n\
    \        for (int v = 0; v < n; v++) {\n            if (random() % 3 == 0) terminals.push_back(v);\n\
    \        }\n        if (!terminals.empty() && trial % 5 == 0) terminals.push_back(terminals.back());\n\
    \n        std::vector<long long> vertex_cost(n);\n        for (long long& cost\
    \ : vertex_cost) cost = random() % 8;\n\n        auto expected = naive(graph,\
    \ terminals);\n        auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ terminals);\n        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ terminals);\n        assert(weighted == expected.first);\n        assert(unweighted\
    \ == expected.second);\n\n        auto expected_vertex_weighted = naive_with_vertex_cost<long\
    \ long>(\n            graph,\n            terminals,\n            vertex_cost,\n\
    \            [](const auto& edge) { return edge.cost; }\n        );\n        auto\
    \ expected_vertex_weighted_unit_edges = naive_with_vertex_cost<long long>(\n \
    \           graph,\n            terminals,\n            vertex_cost,\n       \
    \     [](const auto&) { return 1LL; }\n        );\n        auto vertex_weighted\
    \ = m1une::graph::minimum_steiner_tree(\n            graph,\n            terminals,\n\
    \            vertex_cost\n        );\n        auto vertex_weighted_unit_edges\
    \ = m1une::graph::minimum_steiner_tree_unweighted(\n            graph,\n     \
    \       terminals,\n            vertex_cost\n        );\n        assert(vertex_weighted\
    \ == expected_vertex_weighted);\n        assert(vertex_weighted_unit_edges ==\
    \ expected_vertex_weighted_unit_edges);\n\n        const std::vector<long long>\
    \ zero_vertex_cost(n, 0);\n        auto built_weighted = m1une::graph::build_minimum_steiner_tree(graph,\
    \ terminals);\n        auto built_unweighted = m1une::graph::build_minimum_steiner_tree_unweighted(\n\
    \            graph,\n            terminals\n        );\n        auto built_vertex_weighted\
    \ = m1une::graph::build_minimum_steiner_tree(\n            graph,\n          \
    \  terminals,\n            vertex_cost\n        );\n        auto built_vertex_weighted_unit_edges\
    \ =\n            m1une::graph::build_minimum_steiner_tree_unweighted(graph, terminals,\
    \ vertex_cost);\n        assert(bool(built_weighted) == bool(expected.first));\n\
    \        assert(bool(built_unweighted) == bool(expected.second));\n        assert(bool(built_vertex_weighted)\
    \ == bool(expected_vertex_weighted));\n        assert(\n            bool(built_vertex_weighted_unit_edges)\
    \ == bool(expected_vertex_weighted_unit_edges)\n        );\n        if (built_weighted)\
    \ {\n            assert(built_weighted->cost == *expected.first);\n          \
    \  validate_built_tree(\n                graph,\n                *built_weighted,\n\
    \                terminals,\n                zero_vertex_cost,\n             \
    \   [](const auto& edge) { return edge.cost; }\n            );\n        }\n  \
    \      if (built_unweighted) {\n            assert(built_unweighted->cost == *expected.second);\n\
    \            validate_built_tree(\n                graph,\n                *built_unweighted,\n\
    \                terminals,\n                std::vector<int>(n, 0),\n       \
    \         [](const auto&) { return 1; }\n            );\n        }\n        if\
    \ (built_vertex_weighted) {\n            assert(built_vertex_weighted->cost ==\
    \ *expected_vertex_weighted);\n            validate_built_tree(\n            \
    \    graph,\n                *built_vertex_weighted,\n                terminals,\n\
    \                vertex_cost,\n                [](const auto& edge) { return edge.cost;\
    \ }\n            );\n        }\n        if (built_vertex_weighted_unit_edges)\
    \ {\n            assert(built_vertex_weighted_unit_edges->cost == *expected_vertex_weighted_unit_edges);\n\
    \            validate_built_tree(\n                graph,\n                *built_vertex_weighted_unit_edges,\n\
    \                terminals,\n                vertex_cost,\n                [](const\
    \ auto&) { return 1LL; }\n            );\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_examples_and_failures();\n    test_randomized();\n\n\
    \    int height, width;\n    while (fast_input >> height >> width, height != 0)\
    \ {\n        m1une::graph::Graph<int> graph(height * width);\n        std::vector<int>\
    \ terminals;\n        for (int row = 0; row < height; row++) {\n            for\
    \ (int column = 0; column < width; column++) {\n                int required;\n\
    \                fast_input >> required;\n                const int vertex = row\
    \ * width + column;\n                if (row > 0) graph.add_edge(vertex, vertex\
    \ - width);\n                if (column > 0) graph.add_edge(vertex, vertex - 1);\n\
    \                if (required == 1) terminals.push_back(vertex);\n           \
    \ }\n        }\n\n        auto weighted = m1une::graph::minimum_steiner_tree(graph,\
    \ terminals);\n        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph,\
    \ terminals);\n        assert(weighted && unweighted && *weighted == *unweighted);\n\
    \        fast_output << height * width - *unweighted - 1 << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/minimum_steiner_tree.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/minimum_steiner_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/minimum_steiner_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/minimum_steiner_tree.test.cpp
- /verify/verify/graph/minimum_steiner_tree.test.cpp.html
title: verify/graph/minimum_steiner_tree.test.cpp
---
