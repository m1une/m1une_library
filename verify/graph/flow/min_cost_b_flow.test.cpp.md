---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/bounded_min_cost_flow.hpp
    title: Bounded Min Cost Flow
  - icon: ':heavy_check_mark:'
    path: utilities/int128.hpp
    title: Int128
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_cost_b_flow
    links:
    - https://judge.yosupo.jp/problem/min_cost_b_flow
  bundledCode: "#line 1 \"verify/graph/flow/min_cost_b_flow.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n\n#line 1 \"graph/flow/bounded_min_cost_flow.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <limits>\n#include <optional>\n#include <queue>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <class Cap, class\
    \ Cost>\nstruct BoundedMinCostFlow {\n    static_assert(std::numeric_limits<Cap>::is_integer);\n\
    \    static_assert(std::numeric_limits<Cap>::is_signed);\n\n    struct Edge {\n\
    \        int from;\n        int to;\n        Cap lower;\n        Cap upper;\n\
    \        Cost cost;\n    };\n\n    struct ResultEdge {\n        int from;\n  \
    \      int to;\n        Cap lower;\n        Cap upper;\n        Cap flow;\n  \
    \      Cost cost;\n    };\n\n    struct Result {\n        std::vector<ResultEdge>\
    \ edges;\n        std::vector<Cap> balance;\n        std::vector<Cost> potential;\n\
    \        Cost cost;\n\n        ResultEdge get_edge(int i) const {\n          \
    \  assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n  \
    \      }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i <\
    \ int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\n\
    \   private:\n    struct ScalingEdge {\n        int to;\n        int rev;\n  \
    \      Cap cap;\n        Cap flow;\n        Cost cost;\n    };\n\n    struct ScalingSolver\
    \ {\n        int n;\n        std::vector<std::vector<ScalingEdge>> graph;\n  \
    \      std::vector<std::pair<int, int>> positions;\n        std::vector<Cap> excess;\n\
    \        std::vector<Cost> potential;\n        std::vector<Cost> dist;\n     \
    \   std::vector<int> parent_vertex;\n        std::vector<int> parent_edge;\n \
    \       std::vector<int> excess_vertices;\n        std::vector<int> deficit_vertices;\n\
    \        Cost farthest = Cost(0);\n\n        ScalingSolver(int vertex_count, const\
    \ std::vector<Cap>& balance)\n            : n(vertex_count), graph(vertex_count),\
    \ excess(balance),\n              potential(vertex_count, Cost(0)) {}\n\n    \
    \    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n     \
    \       int id = int(positions.size());\n            int from_id = int(graph[from].size());\n\
    \            int to_id = int(graph[to].size());\n            if (from == to) to_id++;\n\
    \            positions.emplace_back(from, from_id);\n            graph[from].push_back(ScalingEdge{to,\
    \ to_id, upper, Cap(0), cost});\n            graph[to].push_back(ScalingEdge{from,\
    \ from_id, -lower, Cap(0), -cost});\n            return id;\n        }\n\n   \
    \     Cap residual_capacity(int from, int edge_id) const {\n            const\
    \ auto& edge = graph[from][edge_id];\n            return edge.cap - edge.flow;\n\
    \        }\n\n        Cost residual_cost(int from, const ScalingEdge& edge) const\
    \ {\n            return edge.cost + potential[from] - potential[edge.to];\n  \
    \      }\n\n        void push(int from, int edge_id, Cap amount) {\n         \
    \   auto& edge = graph[from][edge_id];\n            edge.flow += amount;\n   \
    \         graph[edge.to][edge.rev].flow -= amount;\n        }\n\n        void\
    \ saturate_negative(Cap delta) {\n            excess_vertices.clear();\n     \
    \       deficit_vertices.clear();\n            for (int from = 0; from < n; from++)\
    \ {\n                for (int edge_id = 0; edge_id < int(graph[from].size());\
    \ edge_id++) {\n                    const auto& edge = graph[from][edge_id];\n\
    \                    Cap residual = edge.cap - edge.flow;\n                  \
    \  residual -= residual % delta;\n                    if (residual_cost(from,\
    \ edge) < Cost(0) || residual < Cap(0)) {\n                        int to = edge.to;\n\
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
    \            dist.assign(n, unreachable);\n            parent_vertex.assign(n,\
    \ -1);\n            parent_edge.assign(n, -1);\n            using QueueEntry =\
    \ std::pair<Cost, int>;\n            std::priority_queue<\n                QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>\n            > queue;\n  \
    \          for (int vertex : excess_vertices) {\n                dist[vertex]\
    \ = Cost(0);\n                queue.emplace(Cost(0), vertex);\n            }\n\
    \n            farthest = Cost(0);\n            int reached_deficits = 0;\n   \
    \         while (!queue.empty()) {\n                auto [distance, from] = queue.top();\n\
    \                queue.pop();\n                if (dist[from] != distance) continue;\n\
    \                farthest = distance;\n                if (excess[from] <= -delta)\
    \ reached_deficits++;\n                if (reached_deficits >= int(deficit_vertices.size()))\
    \ break;\n\n                for (int edge_id = 0; edge_id < int(graph[from].size());\
    \ edge_id++) {\n                    const auto& edge = graph[from][edge_id];\n\
    \                    if (edge.cap - edge.flow < delta) continue;\n           \
    \         Cost next_distance = distance + residual_cost(from, edge);\n       \
    \             if (next_distance >= dist[edge.to]) continue;\n                \
    \    dist[edge.to] = next_distance;\n                    parent_vertex[edge.to]\
    \ = from;\n                    parent_edge[edge.to] = edge_id;\n             \
    \       queue.emplace(next_distance, edge.to);\n                }\n          \
    \  }\n\n            for (int vertex = 0; vertex < n; vertex++) {\n           \
    \     potential[vertex] += std::min(dist[vertex], farthest);\n            }\n\
    \            return reached_deficits > 0;\n        }\n\n        void primal(Cap\
    \ delta) {\n            for (int sink : deficit_vertices) {\n                if\
    \ (dist[sink] > farthest) continue;\n                Cap amount = -excess[sink];\n\
    \                int root = sink;\n                while (parent_edge[root] !=\
    \ -1) {\n                    int from = parent_vertex[root];\n               \
    \     amount = std::min(amount, residual_capacity(from, parent_edge[root]));\n\
    \                    root = from;\n                }\n                amount =\
    \ std::min(amount, excess[root]);\n                amount -= amount % delta;\n\
    \                if (amount <= Cap(0)) continue;\n\n                int vertex\
    \ = sink;\n                while (parent_edge[vertex] != -1) {\n             \
    \       int from = parent_vertex[vertex];\n                    int edge_id = parent_edge[vertex];\n\
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
    \ && deficit_vertices.empty();\n        }\n\n        Cap edge_flow(int edge_id)\
    \ const {\n            auto [from, index] = positions[edge_id];\n            return\
    \ graph[from][index].flow;\n        }\n    };\n\n    int _n;\n    std::vector<Edge>\
    \ _edges;\n    std::vector<Cap> _balance;\n\n    std::vector<Cost> residual_potential(\n\
    \        const std::vector<ResultEdge>& edges\n    ) const {\n        std::vector<Cost>\
    \ potential(_n, Cost(0));\n        bool updated = false;\n        for (int iteration\
    \ = 0; iteration < _n; iteration++) {\n            updated = false;\n        \
    \    for (const ResultEdge& edge : edges) {\n                if (\n          \
    \          edge.flow < edge.upper &&\n                    potential[edge.to] >\
    \ potential[edge.from] + edge.cost\n                ) {\n                    potential[edge.to]\
    \ = potential[edge.from] + edge.cost;\n                    updated = true;\n \
    \               }\n                if (\n                    edge.lower < edge.flow\
    \ &&\n                    potential[edge.from] > potential[edge.to] - edge.cost\n\
    \                ) {\n                    potential[edge.from] = potential[edge.to]\
    \ - edge.cost;\n                    updated = true;\n                }\n     \
    \       }\n            if (!updated) break;\n        }\n        assert(!updated);\n\
    \        return potential;\n    }\n\n   public:\n    BoundedMinCostFlow() : BoundedMinCostFlow(0)\
    \ {}\n\n    explicit BoundedMinCostFlow(int n) : _n(n), _balance(n, Cap(0)) {\n\
    \        assert(0 <= n);\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    int edge_count() const {\n        return int(_edges.size());\n \
    \   }\n\n    int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(lower <= upper);\n        int id = int(_edges.size());\n     \
    \   _edges.push_back(Edge{from, to, lower, upper, cost});\n        return id;\n\
    \    }\n\n    Edge get_edge(int i) const {\n        assert(0 <= i && i < int(_edges.size()));\n\
    \        return _edges[i];\n    }\n\n    std::vector<Edge> edges() const {\n \
    \       return _edges;\n    }\n\n    void set_balance(int v, Cap b) {\n      \
    \  assert(0 <= v && v < _n);\n        _balance[v] = b;\n    }\n\n    void add_balance(int\
    \ v, Cap b) {\n        assert(0 <= v && v < _n);\n        _balance[v] += b;\n\
    \    }\n\n    void add_supply(int v, Cap supply) {\n        assert(Cap(0) <= supply);\n\
    \        add_balance(v, supply);\n    }\n\n    void add_demand(int v, Cap demand)\
    \ {\n        assert(Cap(0) <= demand);\n        add_balance(v, -demand);\n   \
    \ }\n\n    Cap balance(int v) const {\n        assert(0 <= v && v < _n);\n   \
    \     return _balance[v];\n    }\n\n    const std::vector<Cap>& balances() const\
    \ {\n        return _balance;\n    }\n\n    std::optional<Result> min_cost_flow()\
    \ const {\n        return min_cost_flow(_balance);\n    }\n\n    std::optional<Result>\
    \ min_cost_flow(const std::vector<Cap>& balance) const {\n        assert(int(balance.size())\
    \ == _n);\n        Cap balance_sum = Cap(0);\n        for (Cap value : balance)\
    \ balance_sum += value;\n        if (balance_sum != Cap(0)) return std::nullopt;\n\
    \n        ScalingSolver solver(_n, balance);\n        for (const auto& edge :\
    \ _edges) {\n            solver.add_edge(edge.from, edge.to, edge.lower, edge.upper,\
    \ edge.cost);\n        }\n        if (!solver.solve()) return std::nullopt;\n\n\
    \        Result result;\n        result.balance = balance;\n        result.cost\
    \ = Cost(0);\n        result.edges.reserve(_edges.size());\n        for (int i\
    \ = 0; i < int(_edges.size()); i++) {\n            const auto& e = _edges[i];\n\
    \            Cap flow = solver.edge_flow(i);\n            result.cost += Cost(flow)\
    \ * e.cost;\n            result.edges.push_back(ResultEdge{e.from, e.to, e.lower,\
    \ e.upper, flow, e.cost});\n        }\n        result.potential = residual_potential(result.edges);\n\
    \        return result;\n    }\n\n    std::optional<Result> min_cost_st_flow(int\
    \ s, int t, Cap flow_value) const {\n        assert(0 <= s && s < _n);\n     \
    \   assert(0 <= t && t < _n);\n        assert(s != t);\n        std::vector<Cap>\
    \ balance = _balance;\n        balance[s] += flow_value;\n        balance[t] -=\
    \ flow_value;\n        return min_cost_flow(balance);\n    }\n};\n\ntemplate <class\
    \ Cap, class Cost>\nusing BMinCostFlow = BoundedMinCostFlow<Cap, Cost>;\n\n} \
    \ // namespace flow\n}  // namespace m1une\n\n\n#line 1 \"utilities/int128.hpp\"\
    \n\n\n\n#line 5 \"utilities/int128.hpp\"\n#include <cctype>\n#include <istream>\n\
    #include <ostream>\n#include <stdexcept>\n#include <string>\n\nnamespace m1une\
    \ {\nnamespace utilities {\n\nusing i128 = __int128_t;\nusing u128 = __uint128_t;\n\
    \ninline std::string to_string(u128 x) {\n    if (x == 0) {\n        return \"\
    0\";\n    }\n    std::string s;\n    while (x > 0) {\n        s.push_back(static_cast<char>('0'\
    \ + x % 10));\n        x /= 10;\n    }\n    std::reverse(s.begin(), s.end());\n\
    \    return s;\n}\n\ninline std::string to_string(i128 x) {\n    if (x < 0) {\n\
    \        u128 magnitude = static_cast<u128>(-(x + 1)) + 1;\n        return \"\
    -\" + to_string(magnitude);\n    }\n    return to_string(static_cast<u128>(x));\n\
    }\n\ninline u128 parse_uint128(const std::string& s) {\n    if (s.empty()) {\n\
    \        throw std::invalid_argument(\"empty string\");\n    }\n    u128 value\
    \ = 0;\n    for (char c : s) {\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid unsigned __int128\
    \ literal\");\n        }\n        value = value * 10 + static_cast<unsigned>(c\
    \ - '0');\n    }\n    return value;\n}\n\ninline i128 parse_int128(const std::string&\
    \ s) {\n    if (s.empty()) {\n        throw std::invalid_argument(\"empty string\"\
    );\n    }\n    bool negative = s[0] == '-';\n    std::size_t pos = (s[0] == '-'\
    \ || s[0] == '+') ? 1 : 0;\n    if (pos == s.size()) {\n        throw std::invalid_argument(\"\
    invalid __int128 literal\");\n    }\n\n    i128 value = 0;\n    for (; pos < s.size();\
    \ ++pos) {\n        char c = s[pos];\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid __int128 literal\"\
    );\n        }\n        int digit = c - '0';\n        value = value * 10 + (negative\
    \ ? -digit : digit);\n    }\n    return value;\n}\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\ninline std::ostream& operator<<(std::ostream& os, __uint128_t\
    \ x) {\n    return os << m1une::utilities::to_string(x);\n}\n\ninline std::ostream&\
    \ operator<<(std::ostream& os, __int128_t x) {\n    return os << m1une::utilities::to_string(x);\n\
    }\n\ninline std::istream& operator>>(std::istream& is, __uint128_t& x) {\n   \
    \ std::string s;\n    is >> s;\n    if (is) {\n        x = m1une::utilities::parse_uint128(s);\n\
    \    }\n    return is;\n}\n\ninline std::istream& operator>>(std::istream& is,\
    \ __int128_t& x) {\n    std::string s;\n    is >> s;\n    if (is) {\n        x\
    \ = m1une::utilities::parse_int128(s);\n    }\n    return is;\n}\n\n\n#line 5\
    \ \"verify/graph/flow/min_cost_b_flow.test.cpp\"\n\n#line 7 \"verify/graph/flow/min_cost_b_flow.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n    using Flow = long long;\n    using\
    \ Cost = __int128_t;\n    using Solver = m1une::flow::BoundedMinCostFlow<Flow,\
    \ Cost>;\n\n    int vertex_count, edge_count;\n    std::cin >> vertex_count >>\
    \ edge_count;\n    Solver solver(vertex_count);\n    for (int vertex = 0; vertex\
    \ < vertex_count; vertex++) {\n        Flow balance;\n        std::cin >> balance;\n\
    \        solver.set_balance(vertex, balance);\n    }\n    for (int edge = 0; edge\
    \ < edge_count; edge++) {\n        int from, to;\n        Flow lower, upper;\n\
    \        long long cost;\n        std::cin >> from >> to >> lower >> upper >>\
    \ cost;\n        solver.add_edge(from, to, lower, upper, Cost(cost));\n    }\n\
    \n    auto result = solver.min_cost_flow();\n    if (!result.has_value()) {\n\
    \        std::cout << \"infeasible\\n\";\n        return 0;\n    }\n\n    assert(int(result->potential.size())\
    \ == vertex_count);\n    for (const auto& edge : result->edges) {\n        Cost\
    \ reduced_cost =\n            edge.cost + result->potential[edge.from] - result->potential[edge.to];\n\
    \        if (edge.flow < edge.upper) assert(Cost(0) <= reduced_cost);\n      \
    \  if (edge.lower < edge.flow) assert(reduced_cost <= Cost(0));\n    }\n\n   \
    \ std::cout << result->cost << '\\n';\n    for (Cost potential : result->potential)\
    \ std::cout << potential << '\\n';\n    for (const auto& edge : result->edges)\
    \ std::cout << edge.flow << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_cost_b_flow\"\n\n#include\
    \ \"../../../graph/flow/bounded_min_cost_flow.hpp\"\n#include \"../../../utilities/int128.hpp\"\
    \n\n#include <cassert>\n#include <iostream>\n\nint main() {\n    using Flow =\
    \ long long;\n    using Cost = __int128_t;\n    using Solver = m1une::flow::BoundedMinCostFlow<Flow,\
    \ Cost>;\n\n    int vertex_count, edge_count;\n    std::cin >> vertex_count >>\
    \ edge_count;\n    Solver solver(vertex_count);\n    for (int vertex = 0; vertex\
    \ < vertex_count; vertex++) {\n        Flow balance;\n        std::cin >> balance;\n\
    \        solver.set_balance(vertex, balance);\n    }\n    for (int edge = 0; edge\
    \ < edge_count; edge++) {\n        int from, to;\n        Flow lower, upper;\n\
    \        long long cost;\n        std::cin >> from >> to >> lower >> upper >>\
    \ cost;\n        solver.add_edge(from, to, lower, upper, Cost(cost));\n    }\n\
    \n    auto result = solver.min_cost_flow();\n    if (!result.has_value()) {\n\
    \        std::cout << \"infeasible\\n\";\n        return 0;\n    }\n\n    assert(int(result->potential.size())\
    \ == vertex_count);\n    for (const auto& edge : result->edges) {\n        Cost\
    \ reduced_cost =\n            edge.cost + result->potential[edge.from] - result->potential[edge.to];\n\
    \        if (edge.flow < edge.upper) assert(Cost(0) <= reduced_cost);\n      \
    \  if (edge.lower < edge.flow) assert(reduced_cost <= Cost(0));\n    }\n\n   \
    \ std::cout << result->cost << '\\n';\n    for (Cost potential : result->potential)\
    \ std::cout << potential << '\\n';\n    for (const auto& edge : result->edges)\
    \ std::cout << edge.flow << '\\n';\n}\n"
  dependsOn:
  - graph/flow/bounded_min_cost_flow.hpp
  - utilities/int128.hpp
  isVerificationFile: true
  path: verify/graph/flow/min_cost_b_flow.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/flow/min_cost_b_flow.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/flow/min_cost_b_flow.test.cpp
- /verify/verify/graph/flow/min_cost_b_flow.test.cpp.html
title: verify/graph/flow/min_cost_b_flow.test.cpp
---
