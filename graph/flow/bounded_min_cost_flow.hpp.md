---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/flow/flow.hpp
    title: Flow
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/flow/flow_algorithms.test.cpp
    title: verify/graph/flow/flow_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/flow/min_cost_b_flow.test.cpp
    title: verify/graph/flow/min_cost_b_flow.test.cpp
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
  bundledCode: "#line 1 \"graph/flow/bounded_min_cost_flow.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <limits>\n#include <optional>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace flow {\n\ntemplate <class Cap, class Cost>\nstruct BoundedMinCostFlow\
    \ {\n    static_assert(std::numeric_limits<Cap>::is_integer);\n    static_assert(std::numeric_limits<Cap>::is_signed);\n\
    \n    struct Edge {\n        int from;\n        int to;\n        Cap lower;\n\
    \        Cap upper;\n        Cost cost;\n    };\n\n    struct ResultEdge {\n \
    \       int from;\n        int to;\n        Cap lower;\n        Cap upper;\n \
    \       Cap flow;\n        Cost cost;\n    };\n\n    struct Result {\n       \
    \ std::vector<ResultEdge> edges;\n        std::vector<Cap> balance;\n        std::vector<Cost>\
    \ potential;\n        Cost cost;\n\n        ResultEdge get_edge(int i) const {\n\
    \            assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n\
    \        }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i\
    \ < int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\
    \n   private:\n    struct ScalingEdge {\n        int to;\n        int rev;\n \
    \       Cap cap;\n        Cap flow;\n        Cost cost;\n    };\n\n    struct\
    \ ScalingSolver {\n        int n;\n        std::vector<std::vector<ScalingEdge>>\
    \ graph;\n        std::vector<std::pair<int, int>> positions;\n        std::vector<Cap>\
    \ excess;\n        std::vector<Cost> potential;\n        std::vector<Cost> dist;\n\
    \        std::vector<int> parent_vertex;\n        std::vector<int> parent_edge;\n\
    \        std::vector<int> excess_vertices;\n        std::vector<int> deficit_vertices;\n\
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
    \ // namespace flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\n#define M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
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
    \ // namespace flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/flow/bounded_min_cost_flow.hpp
  requiredBy:
  - graph/all.hpp
  - graph/flow/flow.hpp
  timestamp: '2026-07-14 03:22:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/flow/min_cost_b_flow.test.cpp
  - verify/graph/flow/flow_algorithms.test.cpp
documentation_of: graph/flow/bounded_min_cost_flow.hpp
layout: document
title: Bounded Min Cost Flow
---

## Overview

`BoundedMinCostFlow<Cap, Cost>` finds a minimum-cost feasible flow with lower
and upper bounds on each edge. It is the costed version of `BoundedFlow<Cap>`.
`BMinCostFlow<Cap, Cost>` is an alias of
`BoundedMinCostFlow<Cap, Cost>`.

For this library, vertex balance means:

```cpp
outgoing_flow(v) - incoming_flow(v) = balance[v]
```

Positive balance is supply. Negative balance is demand.

Each edge may have any interval `lower <= flow <= upper`. The lower bound may
be negative, so an edge can allow negative flow. For example, an edge
`u -> v` with bounds `[-3, 5]` may carry `-2`, which behaves like sending `2`
units from `v` to `u`. The cost is still `flow * cost`, so a negative flow can
contribute a negative or positive value depending on `cost`.

## Graph Orientation

Directed flow network. An edge added by
`add_edge(from, to, lower, upper, cost)` has the signed direction
`from -> to`.

## How It Works

The solver uses capacity scaling. At scale `delta`, it saturates negative
reduced-cost residual edges in multiples of `delta`, then repeatedly runs a
multi-source shortest-path search from vertices with excess balance and pushes
flow to deficit vertices. Halving `delta` gradually restores exact feasibility;
the final `delta = 1` phase also establishes optimal residual reduced costs.
Unlike a plain successive-shortest-path implementation, the number of phases
depends logarithmically on capacity magnitudes, so exponentially many small
augmentations are avoided.

The returned `Result::cost` is the total cost on the original edges:

```cpp
sum(edge.flow * edge.cost)
```

If the balance constraints cannot be satisfied, the solver returns
`std::nullopt`.

`Cap` must be a signed integer type. `Cost` must support signed exact
arithmetic, ordering, and `std::numeric_limits`. All capacities, intermediate
potential values, and products `flow * cost` must fit their respective types.

## How to Use It

Use `add_edge(from, to, lower, upper, cost)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `min_cost_flow()`. It returns `std::nullopt` if no feasible flow
exists.

For an exact `s-t` flow of value `F`, call `min_cost_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`, then minimizes
the total cost among feasible flows with that exact value.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected minimum-cost flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `potential` | `std::vector<Cost>` | A dual potential certificate for the selected flow. |
| `cost` | `Cost` | Total cost `sum(flow * cost)` of the selected flow. |
| `get_edge` | `ResultEdge get_edge(int i) const` | Returns result edge `i`. |
| `flow` | `Cap flow(int i) const` | Returns selected flow on edge `i`. |

For every returned edge `e`, `potential` satisfies the residual reduced-cost
conditions:

* if `e.flow < e.upper`, then
  `e.cost + potential[e.from] - potential[e.to] >= 0`;
* if `e.lower < e.flow`, then
  `e.cost + potential[e.from] - potential[e.to] <= 0`.

Together with feasibility, these inequalities certify that the returned flow
has minimum cost.

## Edge Fields

| Field | Type | Meaning |
| --- | --- | --- |
| `from` | `int` | Edge source. |
| `to` | `int` | Edge destination. |
| `lower` | `Cap` | Lower bound on flow. |
| `upper` | `Cap` | Upper bound on flow. |
| `flow` | `Cap` | Present only in `ResultEdge`; selected minimum-cost flow. |
| `cost` | `Cost` | Cost per unit of flow. |

## Methods

| Method | Signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `BoundedMinCostFlow()` | Creates an empty bounded min-cost-flow graph. | $O(1)$ |
| Constructor | `explicit BoundedMinCostFlow(int n)` | Creates a graph with `n` vertices. | $O(N)$ |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `edge_count` | `int edge_count() const` | Returns the number of edges. | $O(1)$ |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper, Cost cost)` | Adds an edge with bounds and cost, then returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow() const` | Solves using stored balances. | $O(M \log U \cdot (M + N \log N))$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const` | Solves using explicit balances. | $O(M \log U \cdot (M + N \log N))$ |
| `min_cost_st_flow` | `std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | $O(M \log U \cdot (M + N \log N))$ |

Here, `U` is the maximum absolute edge bound or vertex balance, with
`U >= 1`.

## Alias

| Alias | Type |
| --- | --- |
| `BMinCostFlow<Cap, Cost>` | `BoundedMinCostFlow<Cap, Cost>` |

## Example

```cpp
#include "graph/flow/bounded_min_cost_flow.hpp"
#include <iostream>

int main() {
    m1une::flow::BoundedMinCostFlow<long long, long long> mcf(3);
    int e0 = mcf.add_edge(0, 1, 1, 3, 2);
    int e1 = mcf.add_edge(1, 2, 1, 3, 1);
    int e2 = mcf.add_edge(0, 2, 0, 3, 10);

    auto res = mcf.min_cost_st_flow(0, 2, 3);
    if (!res) return 0;

    std::cout << res->cost << "\n";     // 9
    std::cout << res->flow(e0) << "\n"; // 3
    std::cout << res->flow(e1) << "\n"; // 3
    std::cout << res->flow(e2) << "\n"; // 0
}
```
