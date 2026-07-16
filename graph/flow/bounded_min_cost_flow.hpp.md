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
  - icon: ':heavy_check_mark:'
    path: graph/flow/min_cost_flow.hpp
    title: Min Cost Flow
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
    path: verify/graph/flow/min_cost_flow.test.cpp
    title: verify/graph/flow/min_cost_flow.test.cpp
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
    #include <cassert>\n#include <cstddef>\n#include <cmath>\n#include <functional>\n\
    #include <limits>\n#include <optional>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate <\n    class\
    \ Cap,\n    class Cost,\n    class TotalCost = Cost,\n    std::size_t PivotLimitFactor\
    \ = 8\n>\nstruct BoundedMinCostFlow {\n    static_assert(std::numeric_limits<Cap>::is_integer);\n\
    \    static_assert(std::numeric_limits<Cap>::is_signed);\n    static_assert(std::numeric_limits<Cost>::is_specialized);\n\
    \    static_assert(std::numeric_limits<Cost>::is_signed);\n\n    struct Edge {\n\
    \        int from;\n        int to;\n        Cap lower;\n        Cap upper;\n\
    \        Cost cost;\n    };\n\n    struct ResultEdge {\n        int from;\n  \
    \      int to;\n        Cap lower;\n        Cap upper;\n        Cap flow;\n  \
    \      Cost cost;\n    };\n\n    struct Result {\n        std::vector<ResultEdge>\
    \ edges;\n        std::vector<Cap> balance;\n        std::vector<Cost> potential;\n\
    \        TotalCost cost;\n\n        ResultEdge get_edge(int i) const {\n     \
    \       assert(0 <= i && i < int(edges.size()));\n            return edges[i];\n\
    \        }\n\n        Cap flow(int i) const {\n            assert(0 <= i && i\
    \ < int(edges.size()));\n            return edges[i].flow;\n        }\n    };\n\
    \n   private:\n    struct NetworkEdge {\n        int to;\n        Cap cap;\n \
    \       Cost cost;\n    };\n\n    struct NetworkSimplexSolver {\n        enum\
    \ class Status {\n            optimal,\n            infeasible,\n            pivot_limit_reached,\n\
    \        };\n\n        struct Parent {\n            int vertex;\n            int\
    \ edge;\n            Cap up;\n            Cap down;\n        };\n\n        int\
    \ n;\n        std::vector<NetworkEdge> edges;\n        std::vector<Cap> excess;\n\
    \        std::vector<Cost> potential;\n        std::size_t pivot_count = 0;\n\n\
    \        NetworkSimplexSolver(int vertex_count, const std::vector<Cap>& balance)\n\
    \            : n(vertex_count), excess(balance) {}\n\n        void reserve_edges(int\
    \ edge_count) {\n            edges.reserve(2 * (edge_count + n));\n        }\n\
    \n        int add_edge(int from, int to, Cap lower, Cap upper, Cost cost) {\n\
    \            int id = int(edges.size()) / 2;\n            edges.push_back(NetworkEdge{to,\
    \ upper - lower, cost});\n            edges.push_back(NetworkEdge{from, Cap(0),\
    \ -cost});\n            excess[from] -= lower;\n            excess[to] += lower;\n\
    \            return id;\n        }\n\n        Status solve(std::size_t pivot_limit)\
    \ {\n            pivot_count = 0;\n            const int original_edge_count =\
    \ int(edges.size());\n            potential.assign(n + 1, Cost(0));\n\n      \
    \      Cost artificial_cost = Cost(1);\n            for (int edge = 0; edge <\
    \ original_edge_count; edge += 2) {\n                artificial_cost += edges[edge].cost\
    \ < Cost(0)\n                    ? -edges[edge].cost : edges[edge].cost;\n   \
    \         }\n\n            std::vector<Parent> parent(n);\n            edges.reserve(original_edge_count\
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
    \ flow\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\n#define M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cmath>\n#include <functional>\n#include <limits>\n#include <optional>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
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
    \ flow\n}  // namespace m1une\n\n#endif  // M1UNE_FLOW_BOUNDED_MIN_COST_FLOW_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/flow/bounded_min_cost_flow.hpp
  requiredBy:
  - graph/all.hpp
  - graph/flow/flow.hpp
  - graph/flow/min_cost_flow.hpp
  timestamp: '2026-07-15 13:35:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/flow/min_cost_b_flow.test.cpp
  - verify/graph/flow/flow_algorithms.test.cpp
  - verify/graph/flow/min_cost_flow.test.cpp
documentation_of: graph/flow/bounded_min_cost_flow.hpp
layout: document
title: Bounded Min Cost Flow
---

## Overview

`BoundedMinCostFlow<Cap, Cost, TotalCost = Cost, PivotLimitFactor = 8>` finds
a minimum-cost feasible flow with lower and upper bounds on each edge. It is
the costed version of `BoundedFlow<Cap>`. `BMinCostFlow` is an alias of the
same type.

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

The solver first uses the network simplex method with an artificial-root
initial basis. It repeatedly pivots a negative reduced-cost residual edge into
the spanning-tree basis and removes a saturated tree edge. A candidate-list
pivot rule reuses promising edges for several minor iterations before scanning
the residual edges again. This approach has very small constants and is
especially fast on the sparse and medium-sized flow networks common in
contests.

Network simplex alone has no polynomial pivot bound. Therefore, after
`PivotLimitFactor * (N + M + 1)` pivots, `min_cost_flow` discards the partial
basis and restarts from the original instance with a polynomial capacity-scaling
solver. The default factor is `8`. Because the pivot budget is linear in the
input graph size, the hybrid algorithm retains a polynomial worst-case bound.

`min_cost_flow_polynomial` skips network simplex and directly uses capacity
scaling. It is useful for inputs known to be adversarial to simplex. Setting
`PivotLimitFactor` to `0` also makes the hybrid fall back as soon as its first
pivot would be required.

On the simplex path, the artificial edges determine feasibility and the tree
potentials provide the returned dual certificate. On the capacity-scaling path,
the certificate is reconstructed from the final residual graph.

The returned `Result::cost` is the total cost on the original edges:

```cpp
sum(edge.flow * edge.cost)
```

If the balance constraints cannot be satisfied, the solver returns
`std::nullopt`.

`Cap` must be a signed integer type. `Cost` must support signed exact
arithmetic, ordering, and `std::numeric_limits<Cost>::max()`. `TotalCost` is
the accumulator type for the final
`sum(flow * cost)` and defaults to `Cost`. All capacities must fit `Cap`;
intermediate potential values and the artificial cost
`1 + sum(abs(edge.cost))`, as well as reduced-cost arithmetic, must fit `Cost`;
the total must fit `TotalCost`.

When only the total may overflow the unit-cost type, use a wider third template
argument. For example, `BoundedMinCostFlow<long long, long long, __int128_t>`
keeps the network-simplex hot path in 64-bit arithmetic and accumulates the
answer in 128 bits.

## How to Use It

Use `add_edge(from, to, lower, upper, cost)` to add bounded directed edges.

Use these balance helpers for `b`-flow:

* `add_supply(v, x)` adds `x` to `balance[v]`;
* `add_demand(v, x)` subtracts `x` from `balance[v]`;
* `set_balance(v, b)` sets the balance directly;
* `add_balance(v, b)` adds signed balance directly.

Then call `min_cost_flow()`. It returns `std::nullopt` if no feasible flow
exists.

Call `min_cost_flow_polynomial()` instead to bypass the simplex fast path.

For an exact `s-t` flow of value `F`, call `min_cost_st_flow(s, t, F)`. This
adds temporary balances `balance[s] += F` and `balance[t] -= F`, then minimizes
the total cost among feasible flows with that exact value. The direct
capacity-scaling version is `min_cost_st_flow_polynomial(s, t, F)`.

The result contains these members:

| Member | Type / Signature | Meaning |
| --- | --- | --- |
| `edges` | `std::vector<ResultEdge>` | Original edges with selected minimum-cost flow. |
| `balance` | `std::vector<Cap>` | Vertex balances used for this solve. |
| `potential` | `std::vector<Cost>` | A dual potential certificate for the selected flow. |
| `cost` | `TotalCost` | Total cost `sum(flow * cost)` of the selected flow. |
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
| `reserve_edges` | `void reserve_edges(int edge_count)` | Reserves storage when the number of edges is known in advance. | $O(M)$ when reallocation occurs |
| `add_edge` | `int add_edge(int from, int to, Cap lower, Cap upper, Cost cost)` | Adds an edge with bounds and cost, then returns its id. | Amortized $O(1)$ |
| `get_edge` | `Edge get_edge(int i) const` | Returns original edge `i`. | $O(1)$ |
| `edges` | `std::vector<Edge> edges() const` | Returns all original edges. | $O(M)$ |
| `set_balance` | `void set_balance(int v, Cap b)` | Sets `balance[v] = b`. | $O(1)$ |
| `add_balance` | `void add_balance(int v, Cap b)` | Adds signed balance to vertex `v`. | $O(1)$ |
| `add_supply` | `void add_supply(int v, Cap supply)` | Adds non-negative supply to vertex `v`. | $O(1)$ |
| `add_demand` | `void add_demand(int v, Cap demand)` | Adds non-negative demand to vertex `v`. | $O(1)$ |
| `balance` | `Cap balance(int v) const` | Returns `balance[v]`. | $O(1)$ |
| `balances` | `const std::vector<Cap>& balances() const` | Returns all balances. | $O(1)$ |
| `min_cost_flow` | `std::optional<Result> min_cost_flow() const` | Solves stored balances with simplex and polynomial fallback. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_flow` | `std::optional<Result> min_cost_flow(const std::vector<Cap>& balance) const` | Solves explicit balances with simplex and polynomial fallback. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_flow_polynomial` | `std::optional<Result> min_cost_flow_polynomial() const` | Solves stored balances directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |
| `min_cost_flow_polynomial` | `std::optional<Result> min_cost_flow_polynomial(const std::vector<Cap>& balance) const` | Solves explicit balances directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |
| `min_cost_st_flow` | `std::optional<Result> min_cost_st_flow(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow with value `flow_value`. | $O((N + M)^2 + M \log U (M + N \log N))$ worst case |
| `min_cost_st_flow_polynomial` | `std::optional<Result> min_cost_st_flow_polynomial(int s, int t, Cap flow_value) const` | Solves exact `s-t` flow directly with capacity scaling. | $O(M \log U (M + N \log N) + NM)$ |

Here, `P <= PivotLimitFactor * (N + M + 1)` is the number of network-simplex
pivots completed before termination or fallback. `U` is the maximum absolute
capacity or balance, with a minimum value of two. Without fallback, the actual
time is $O(N + M + P(N + M))$. Thus the default hybrid keeps the simplex fast
path while having the polynomial worst-case bounds shown above.

Average-case complexity depends on the input distribution. Let $\bar P$ be the
expected number of simplex pivots and let $q$ be the probability that the pivot
limit is reached. The expected time is

$$
O\left(
N + M + \bar P(N + M)
+ q\left(M \log U (M + N \log N) + NM\right)
\right).
$$

For typical contest inputs the fallback is rare, so the practical average is
$O(N + M + \bar P(N + M))$.

As empirical intuition, with the current candidate-list rule on the 54 official
Library Checker `min_cost_b_flow` cases, the pivot count had median `16.5`, mean
`627`, and maximum `2104`. On the ten 1000-edge `large_random` cases the mean
was `1924` pivots, while the ten 1000-edge `goto` cases averaged `968`. Thus a
useful practical estimate on the larger cases is $\bar P \approx M$ to $2M$,
giving the coarse average bound $O(M(N + M))$. For comparison, the default
budget is `8808` pivots when `N = 100` and `M = 1000`.

The observed running time is usually better than that coarse bound suggests:
candidate lists avoid a full edge scan before every pivot, and a pivot normally
touches only a short tree path and a small rerooted subtree. The theoretical
$O(N + M)$ work per pivot is therefore rarely fully realized. These figures are
measurements, not a distribution-independent guarantee on $\bar P$.

## Alias

| Alias | Type |
| --- | --- |
| `BMinCostFlow<Cap, Cost, TotalCost, PivotLimitFactor>` | `BoundedMinCostFlow<Cap, Cost, TotalCost, PivotLimitFactor>` |

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
