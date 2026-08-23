---
title: Functional Graph
documentation_of: ../../graph/functional_graph.hpp
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
