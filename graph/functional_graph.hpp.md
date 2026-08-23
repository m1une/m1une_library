---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/functional_graph.test.cpp
    title: verify/graph/functional_graph.test.cpp
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
  bundledCode: "#line 1 \"graph/functional_graph.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <queue>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace graph {\n\nstruct FunctionalGraph\
    \ {\n    int component_count;\n    std::vector<int> successor;\n    std::vector<std::vector<int>>\
    \ predecessors;\n    std::vector<std::vector<int>> cycles;\n    std::vector<int>\
    \ component;\n    std::vector<int> component_size;\n    std::vector<int> cycle_entry;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> distance_to_cycle;\n\
    \n   private:\n    std::vector<std::vector<int>> _up;\n\n    void check_vertex(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < size());\n    }\n\n\
    \    int advance_before_cycle(int vertex, int steps) const {\n        assert(0\
    \ <= steps && steps <= distance_to_cycle[vertex]);\n        int bit = 0;\n   \
    \     while (steps > 0) {\n            if (steps & 1) vertex = _up[bit][vertex];\n\
    \            steps >>= 1;\n            bit++;\n        }\n        return vertex;\n\
    \    }\n\n   public:\n    FunctionalGraph() : component_count(0) {}\n\n    explicit\
    \ FunctionalGraph(const std::vector<int>& successor_) {\n        build(successor_);\n\
    \    }\n\n    void build(const std::vector<int>& successor_) {\n        successor\
    \ = successor_;\n        const int n = size();\n        for (int to : successor)\
    \ assert(0 <= to && to < n);\n\n        component_count = 0;\n        predecessors.assign(n,\
    \ {});\n        cycles.clear();\n        component.assign(n, -1);\n        cycle_entry.assign(n,\
    \ -1);\n        cycle_position.assign(n, -1);\n        distance_to_cycle.assign(n,\
    \ -1);\n\n        std::vector<int> indegree(n, 0);\n        for (int vertex =\
    \ 0; vertex < n; vertex++) {\n            predecessors[successor[vertex]].push_back(vertex);\n\
    \            indegree[successor[vertex]]++;\n        }\n\n        std::queue<int>\
    \ queue;\n        std::vector<char> removed(n, false);\n        for (int vertex\
    \ = 0; vertex < n; vertex++) {\n            if (indegree[vertex] == 0) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            removed[vertex] = true;\n            const\
    \ int to = successor[vertex];\n            indegree[to]--;\n            if (indegree[to]\
    \ == 0) queue.push(to);\n        }\n\n        for (int start = 0; start < n; start++)\
    \ {\n            if (removed[start] || component[start] != -1) continue;\n   \
    \         const int component_id = int(cycles.size());\n            std::vector<int>\
    \ cycle;\n            int vertex = start;\n            do {\n                const\
    \ int position = int(cycle.size());\n                cycle.push_back(vertex);\n\
    \                component[vertex] = component_id;\n                cycle_entry[vertex]\
    \ = vertex;\n                cycle_position[vertex] = position;\n            \
    \    distance_to_cycle[vertex] = 0;\n                vertex = successor[vertex];\n\
    \            } while (vertex != start);\n            cycles.push_back(std::move(cycle));\n\
    \        }\n        component_count = int(cycles.size());\n\n        for (const\
    \ std::vector<int>& cycle : cycles) {\n            for (int vertex : cycle) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int from : predecessors[vertex]) {\n\
    \                if (component[from] != -1) continue;\n                component[from]\
    \ = component[vertex];\n                cycle_entry[from] = cycle_entry[vertex];\n\
    \                cycle_position[from] = cycle_position[vertex];\n            \
    \    distance_to_cycle[from] = distance_to_cycle[vertex] + 1;\n              \
    \  queue.push(from);\n            }\n        }\n\n        component_size.assign(component_count,\
    \ 0);\n        for (int component_id : component) component_size[component_id]++;\n\
    \n        int log = 1;\n        while ((std::uint64_t(1) << log) <= std::uint64_t(n))\
    \ log++;\n        _up.assign(log, successor);\n        for (int bit = 1; bit <\
    \ log; bit++) {\n            for (int vertex = 0; vertex < n; vertex++) {\n  \
    \              _up[bit][vertex] = _up[bit - 1][_up[bit - 1][vertex]];\n      \
    \      }\n        }\n    }\n\n    int size() const {\n        return int(successor.size());\n\
    \    }\n\n    bool empty() const {\n        return successor.empty();\n    }\n\
    \n    bool same_component(int first, int second) const {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return component[first] == component[second];\n\
    \    }\n\n    bool on_cycle(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] == 0;\n    }\n\n    int cycle_size(int\
    \ vertex) const {\n        check_vertex(vertex);\n        return int(cycles[component[vertex]].size());\n\
    \    }\n\n    int orbit_size(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] + cycle_size(vertex);\n    }\n\n   \
    \ int jump(int vertex, std::uint64_t steps) const {\n        check_vertex(vertex);\n\
    \        const int tail_length = distance_to_cycle[vertex];\n        if (steps\
    \ < std::uint64_t(tail_length)) {\n            return advance_before_cycle(vertex,\
    \ int(steps));\n        }\n\n        steps -= std::uint64_t(tail_length);\n  \
    \      const int entry = cycle_entry[vertex];\n        const int length = cycle_size(entry);\n\
    \        const int offset = int(steps % std::uint64_t(length));\n        const\
    \ int position = (cycle_position[entry] + offset) % length;\n        return cycles[component[vertex]][position];\n\
    \    }\n\n    long long distance(int from, int to) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        if (!same_component(from, to)) return -1;\n\
    \n        if (!on_cycle(to)) {\n            if (distance_to_cycle[from] < distance_to_cycle[to])\
    \ return -1;\n            const int difference = distance_to_cycle[from] - distance_to_cycle[to];\n\
    \            return advance_before_cycle(from, difference) == to ? difference\
    \ : -1;\n        }\n\n        const int entry = cycle_entry[from];\n        const\
    \ int length = cycle_size(from);\n        int cycle_distance = cycle_position[to]\
    \ - cycle_position[entry];\n        if (cycle_distance < 0) cycle_distance +=\
    \ length;\n        return static_cast<long long>(distance_to_cycle[from]) + cycle_distance;\n\
    \    }\n\n    bool reachable(int from, int to) const {\n        return distance(from,\
    \ to) != -1;\n    }\n\n    std::vector<int> path(int from, int to) const {\n \
    \       const long long path_length = distance(from, to);\n        if (path_length\
    \ == -1) return {};\n\n        std::vector<int> result;\n        result.reserve(path_length\
    \ + 1);\n        for (long long step = 0; step <= path_length; step++) {\n   \
    \         result.push_back(from);\n            from = successor[from];\n     \
    \   }\n        return result;\n    }\n\n    std::vector<int> orbit(int vertex)\
    \ const {\n        check_vertex(vertex);\n        const int length = orbit_size(vertex);\n\
    \        std::vector<int> result;\n        result.reserve(length);\n        for\
    \ (int step = 0; step < length; step++) {\n            result.push_back(vertex);\n\
    \            vertex = successor[vertex];\n        }\n        return result;\n\
    \    }\n\n    std::uint64_t visit_count(\n        int from,\n        int to,\n\
    \        std::uint64_t step_count\n    ) const {\n        const long long first_visit\
    \ = distance(from, to);\n        if (first_visit == -1 ||\n            std::uint64_t(first_visit)\
    \ >= step_count) {\n            return 0;\n        }\n        if (!on_cycle(to))\
    \ return 1;\n\n        const std::uint64_t remaining =\n            step_count\
    \ - 1 - std::uint64_t(first_visit);\n        return 1 + remaining / std::uint64_t(cycle_size(to));\n\
    \    }\n\n    long long first_meeting_time(int first, int second) const {\n  \
    \      check_vertex(first);\n        check_vertex(second);\n        if (!same_component(first,\
    \ second)) return -1;\n        if (first == second) return 0;\n\n        const\
    \ int first_depth = distance_to_cycle[first];\n        const int second_depth\
    \ = distance_to_cycle[second];\n        if (first_depth == second_depth &&\n \
    \           cycle_entry[first] == cycle_entry[second]) {\n            int elapsed\
    \ = 0;\n            for (int bit = int(_up.size()) - 1; bit >= 0; bit--) {\n \
    \               const int steps = 1 << bit;\n                if (first_depth -\
    \ elapsed < steps) continue;\n                const int next_first = _up[bit][first];\n\
    \                const int next_second = _up[bit][second];\n                if\
    \ (next_first == next_second) continue;\n                first = next_first;\n\
    \                second = next_second;\n                elapsed += steps;\n  \
    \          }\n            return elapsed + 1;\n        }\n\n        const int\
    \ length = cycle_size(first);\n        int first_phase =\n            cycle_position[first]\
    \ - first_depth % length;\n        int second_phase =\n            cycle_position[second]\
    \ - second_depth % length;\n        if (first_phase < 0) first_phase += length;\n\
    \        if (second_phase < 0) second_phase += length;\n        if (first_phase\
    \ != second_phase) return -1;\n        return std::max(first_depth, second_depth);\n\
    \    }\n\n    int first_meeting_vertex(int first, int second) const {\n      \
    \  const long long time = first_meeting_time(first, second);\n        if (time\
    \ == -1) return -1;\n        return jump(first, std::uint64_t(time));\n    }\n\
    };\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP\n#define M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct FunctionalGraph {\n    int component_count;\n    std::vector<int>\
    \ successor;\n    std::vector<std::vector<int>> predecessors;\n    std::vector<std::vector<int>>\
    \ cycles;\n    std::vector<int> component;\n    std::vector<int> component_size;\n\
    \    std::vector<int> cycle_entry;\n    std::vector<int> cycle_position;\n   \
    \ std::vector<int> distance_to_cycle;\n\n   private:\n    std::vector<std::vector<int>>\
    \ _up;\n\n    void check_vertex(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < size());\n    }\n\n    int advance_before_cycle(int vertex, int\
    \ steps) const {\n        assert(0 <= steps && steps <= distance_to_cycle[vertex]);\n\
    \        int bit = 0;\n        while (steps > 0) {\n            if (steps & 1)\
    \ vertex = _up[bit][vertex];\n            steps >>= 1;\n            bit++;\n \
    \       }\n        return vertex;\n    }\n\n   public:\n    FunctionalGraph()\
    \ : component_count(0) {}\n\n    explicit FunctionalGraph(const std::vector<int>&\
    \ successor_) {\n        build(successor_);\n    }\n\n    void build(const std::vector<int>&\
    \ successor_) {\n        successor = successor_;\n        const int n = size();\n\
    \        for (int to : successor) assert(0 <= to && to < n);\n\n        component_count\
    \ = 0;\n        predecessors.assign(n, {});\n        cycles.clear();\n       \
    \ component.assign(n, -1);\n        cycle_entry.assign(n, -1);\n        cycle_position.assign(n,\
    \ -1);\n        distance_to_cycle.assign(n, -1);\n\n        std::vector<int> indegree(n,\
    \ 0);\n        for (int vertex = 0; vertex < n; vertex++) {\n            predecessors[successor[vertex]].push_back(vertex);\n\
    \            indegree[successor[vertex]]++;\n        }\n\n        std::queue<int>\
    \ queue;\n        std::vector<char> removed(n, false);\n        for (int vertex\
    \ = 0; vertex < n; vertex++) {\n            if (indegree[vertex] == 0) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            removed[vertex] = true;\n            const\
    \ int to = successor[vertex];\n            indegree[to]--;\n            if (indegree[to]\
    \ == 0) queue.push(to);\n        }\n\n        for (int start = 0; start < n; start++)\
    \ {\n            if (removed[start] || component[start] != -1) continue;\n   \
    \         const int component_id = int(cycles.size());\n            std::vector<int>\
    \ cycle;\n            int vertex = start;\n            do {\n                const\
    \ int position = int(cycle.size());\n                cycle.push_back(vertex);\n\
    \                component[vertex] = component_id;\n                cycle_entry[vertex]\
    \ = vertex;\n                cycle_position[vertex] = position;\n            \
    \    distance_to_cycle[vertex] = 0;\n                vertex = successor[vertex];\n\
    \            } while (vertex != start);\n            cycles.push_back(std::move(cycle));\n\
    \        }\n        component_count = int(cycles.size());\n\n        for (const\
    \ std::vector<int>& cycle : cycles) {\n            for (int vertex : cycle) queue.push(vertex);\n\
    \        }\n        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int from : predecessors[vertex]) {\n\
    \                if (component[from] != -1) continue;\n                component[from]\
    \ = component[vertex];\n                cycle_entry[from] = cycle_entry[vertex];\n\
    \                cycle_position[from] = cycle_position[vertex];\n            \
    \    distance_to_cycle[from] = distance_to_cycle[vertex] + 1;\n              \
    \  queue.push(from);\n            }\n        }\n\n        component_size.assign(component_count,\
    \ 0);\n        for (int component_id : component) component_size[component_id]++;\n\
    \n        int log = 1;\n        while ((std::uint64_t(1) << log) <= std::uint64_t(n))\
    \ log++;\n        _up.assign(log, successor);\n        for (int bit = 1; bit <\
    \ log; bit++) {\n            for (int vertex = 0; vertex < n; vertex++) {\n  \
    \              _up[bit][vertex] = _up[bit - 1][_up[bit - 1][vertex]];\n      \
    \      }\n        }\n    }\n\n    int size() const {\n        return int(successor.size());\n\
    \    }\n\n    bool empty() const {\n        return successor.empty();\n    }\n\
    \n    bool same_component(int first, int second) const {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return component[first] == component[second];\n\
    \    }\n\n    bool on_cycle(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] == 0;\n    }\n\n    int cycle_size(int\
    \ vertex) const {\n        check_vertex(vertex);\n        return int(cycles[component[vertex]].size());\n\
    \    }\n\n    int orbit_size(int vertex) const {\n        check_vertex(vertex);\n\
    \        return distance_to_cycle[vertex] + cycle_size(vertex);\n    }\n\n   \
    \ int jump(int vertex, std::uint64_t steps) const {\n        check_vertex(vertex);\n\
    \        const int tail_length = distance_to_cycle[vertex];\n        if (steps\
    \ < std::uint64_t(tail_length)) {\n            return advance_before_cycle(vertex,\
    \ int(steps));\n        }\n\n        steps -= std::uint64_t(tail_length);\n  \
    \      const int entry = cycle_entry[vertex];\n        const int length = cycle_size(entry);\n\
    \        const int offset = int(steps % std::uint64_t(length));\n        const\
    \ int position = (cycle_position[entry] + offset) % length;\n        return cycles[component[vertex]][position];\n\
    \    }\n\n    long long distance(int from, int to) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        if (!same_component(from, to)) return -1;\n\
    \n        if (!on_cycle(to)) {\n            if (distance_to_cycle[from] < distance_to_cycle[to])\
    \ return -1;\n            const int difference = distance_to_cycle[from] - distance_to_cycle[to];\n\
    \            return advance_before_cycle(from, difference) == to ? difference\
    \ : -1;\n        }\n\n        const int entry = cycle_entry[from];\n        const\
    \ int length = cycle_size(from);\n        int cycle_distance = cycle_position[to]\
    \ - cycle_position[entry];\n        if (cycle_distance < 0) cycle_distance +=\
    \ length;\n        return static_cast<long long>(distance_to_cycle[from]) + cycle_distance;\n\
    \    }\n\n    bool reachable(int from, int to) const {\n        return distance(from,\
    \ to) != -1;\n    }\n\n    std::vector<int> path(int from, int to) const {\n \
    \       const long long path_length = distance(from, to);\n        if (path_length\
    \ == -1) return {};\n\n        std::vector<int> result;\n        result.reserve(path_length\
    \ + 1);\n        for (long long step = 0; step <= path_length; step++) {\n   \
    \         result.push_back(from);\n            from = successor[from];\n     \
    \   }\n        return result;\n    }\n\n    std::vector<int> orbit(int vertex)\
    \ const {\n        check_vertex(vertex);\n        const int length = orbit_size(vertex);\n\
    \        std::vector<int> result;\n        result.reserve(length);\n        for\
    \ (int step = 0; step < length; step++) {\n            result.push_back(vertex);\n\
    \            vertex = successor[vertex];\n        }\n        return result;\n\
    \    }\n\n    std::uint64_t visit_count(\n        int from,\n        int to,\n\
    \        std::uint64_t step_count\n    ) const {\n        const long long first_visit\
    \ = distance(from, to);\n        if (first_visit == -1 ||\n            std::uint64_t(first_visit)\
    \ >= step_count) {\n            return 0;\n        }\n        if (!on_cycle(to))\
    \ return 1;\n\n        const std::uint64_t remaining =\n            step_count\
    \ - 1 - std::uint64_t(first_visit);\n        return 1 + remaining / std::uint64_t(cycle_size(to));\n\
    \    }\n\n    long long first_meeting_time(int first, int second) const {\n  \
    \      check_vertex(first);\n        check_vertex(second);\n        if (!same_component(first,\
    \ second)) return -1;\n        if (first == second) return 0;\n\n        const\
    \ int first_depth = distance_to_cycle[first];\n        const int second_depth\
    \ = distance_to_cycle[second];\n        if (first_depth == second_depth &&\n \
    \           cycle_entry[first] == cycle_entry[second]) {\n            int elapsed\
    \ = 0;\n            for (int bit = int(_up.size()) - 1; bit >= 0; bit--) {\n \
    \               const int steps = 1 << bit;\n                if (first_depth -\
    \ elapsed < steps) continue;\n                const int next_first = _up[bit][first];\n\
    \                const int next_second = _up[bit][second];\n                if\
    \ (next_first == next_second) continue;\n                first = next_first;\n\
    \                second = next_second;\n                elapsed += steps;\n  \
    \          }\n            return elapsed + 1;\n        }\n\n        const int\
    \ length = cycle_size(first);\n        int first_phase =\n            cycle_position[first]\
    \ - first_depth % length;\n        int second_phase =\n            cycle_position[second]\
    \ - second_depth % length;\n        if (first_phase < 0) first_phase += length;\n\
    \        if (second_phase < 0) second_phase += length;\n        if (first_phase\
    \ != second_phase) return -1;\n        return std::max(first_depth, second_depth);\n\
    \    }\n\n    int first_meeting_vertex(int first, int second) const {\n      \
    \  const long long time = first_meeting_time(first, second);\n        if (time\
    \ == -1) return -1;\n        return jump(first, std::uint64_t(time));\n    }\n\
    };\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_FUNCTIONAL_GRAPH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/functional_graph.hpp
  requiredBy:
  - graph/all.hpp
  - graph/directed.hpp
  timestamp: '2026-08-24 02:34:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/functional_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/functional_graph.hpp
layout: document
title: Functional Graph
---

## Overview

`FunctionalGraph` represents a directed graph in which every vertex has exactly
one outgoing edge. It decomposes the graph into directed cycles and the trees
that feed into them. Besides large successor jumps and directed reachability
distances, it can enumerate orbits and paths, count visits during a bounded
walk, and find the first meeting of two synchronized walkers.

Construct it directly from a successor array: `successor[v]` is the vertex
reached after one step from `v`. Self-loops and disconnected components are
supported. The object is static; call `build` again to replace the graph.

## Public Fields

| Field | Meaning |
| --- | --- |
| `component_count` | Number of weakly connected components, equivalently the number of directed cycles. |
| `successor[v]` | Vertex reached from `v` after one step. |
| `predecessors[v]` | Vertices whose successor is `v`, including the preceding cycle vertex when `v` is on a cycle. |
| `cycles[c]` | Vertices of component `c`'s cycle in successor order. |
| `component[v]` | Component and cycle id containing `v`. |
| `component_size[c]` | Number of vertices in component `c`, including its cycle and all attached trees. |
| `cycle_entry[v]` | First cycle vertex reached from `v`. A cycle vertex is its own entry. |
| `cycle_position[v]` | Position of `cycle_entry[v]` in `cycles[component[v]]`. |
| `distance_to_cycle[v]` | Number of steps from `v` to `cycle_entry[v]`. |

All vertex indices and component indices are zero-based.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Default constructor | `FunctionalGraph()` | Constructs an empty graph. | $O(1)$ |
| Constructor | `explicit FunctionalGraph(const std::vector<int>& successor)` | Builds from a successor array. | $O(N\log N)$ time and memory |
| `build` | `void build(const std::vector<int>& successor)` | Replaces the graph and rebuilds all metadata. | $O(N\log N)$ time and memory |
| `size` | `int size() const` | Returns the number of vertices. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether there are no vertices. | $O(1)$ |
| `same_component` | `bool same_component(int first, int second) const` | Tests whether two vertices belong to the same weakly connected component. | $O(1)$ |
| `on_cycle` | `bool on_cycle(int vertex) const` | Tests whether a vertex lies on a directed cycle. | $O(1)$ |
| `cycle_size` | `int cycle_size(int vertex) const` | Returns the length of the cycle eventually reached from a vertex. | $O(1)$ |
| `orbit_size` | `int orbit_size(int vertex) const` | Returns the number of distinct vertices visited before the walk first repeats. | $O(1)$ |
| `jump` | `int jump(int vertex, std::uint64_t steps) const` | Returns the vertex reached after exactly `steps` successor edges. | $O(\log N)$ |
| `distance` | `long long distance(int from, int to) const` | Returns the minimum number of successor edges from `from` to `to`, or `-1` if `to` is unreachable. | $O(\log N)$ |
| `reachable` | `bool reachable(int from, int to) const` | Tests directed reachability along successor edges. | $O(\log N)$ |
| `path` | `std::vector<int> path(int from, int to) const` | Returns the minimum directed path including both endpoints, or an empty vector if unreachable. | $O(D + \log N)$ time and $O(D)$ output memory, where $D$ is the returned distance |
| `orbit` | `std::vector<int> orbit(int vertex) const` | Returns the distinct vertices of the walk in order, stopping immediately before the first repetition. | $O(K)$ time and output memory, where $K$ is `orbit_size(vertex)` |
| `visit_count` | `std::uint64_t visit_count(int from, int to, std::uint64_t step_count) const` | Counts times `t` in `[0, step_count)` for which the walk from `from` is at `to`. | $O(\log N)$ |
| `first_meeting_time` | `long long first_meeting_time(int first, int second) const` | Returns the minimum `t` such that both synchronized walks occupy the same vertex after `t` steps, or `-1` if they never meet. | $O(\log N)$ |
| `first_meeting_vertex` | `int first_meeting_vertex(int first, int second) const` | Returns the vertex at the first synchronized meeting, or `-1` if none exists. | $O(\log N)$ |

Construction asserts that every successor is a valid vertex. Query methods
assert that their vertex arguments are valid. No query mutates the object.

## Algorithm

Vertices with indegree zero are repeatedly removed. The vertices left behind
are exactly the directed cycles. A traversal over reverse edges then assigns
each removed vertex to its cycle entry and records its distance from the cycle.

Binary lifting handles the acyclic prefix of a walk. Once a walk reaches its
cycle, `jump` reduces the remaining 64-bit step count modulo the cycle length.
This avoids storing 64 ancestors per vertex while still accepting every
`std::uint64_t` step count.

For a target outside a cycle, a walk can visit it at most once. For a target on
a cycle, subsequent visits are separated by the cycle length; `visit_count`
uses this fact after finding the first visit.

Two synchronized walks can merge before reaching a cycle only when they have
the same distance to that cycle and feed into the same cycle entry. Binary
lifting finds their first common tail vertex. Otherwise, their eventual cycle
positions are compared after adjusting for their different entry times.
Matching cycle phases meet as soon as both walkers have reached the cycle;
different phases never meet.

## Example

```cpp
#include "graph/functional_graph.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    // 0 -> 1 -> 2 -> 0, and 4 -> 3 -> 2.
    m1une::graph::FunctionalGraph graph(std::vector<int>{1, 2, 0, 2, 3});

    std::cout << graph.jump(4, 4) << '\n';       // 1
    std::cout << graph.distance(4, 1) << '\n';  // 4
    std::cout << graph.cycle_entry[4] << '\n';  // 2
    std::cout << graph.cycle_size(4) << '\n';   // 3
    std::cout << graph.orbit_size(4) << '\n';   // 5
    std::cout << graph.visit_count(4, 2, 6) << '\n';  // 2
}
```
