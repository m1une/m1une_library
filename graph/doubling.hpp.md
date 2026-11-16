---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/doubling.test.cpp
    title: verify/graph/doubling.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/doubling_jump_on_tree.test.cpp
    title: verify/graph/doubling_jump_on_tree.test.cpp
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
  bundledCode: "#line 1 \"graph/doubling.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <bit>\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include\
    \ <limits>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include\
    \ <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if\
    \ a type satisfies the requirements of a Monoid.\n// A Monoid must have a `value_type`,\
    \ an identity element `id()`, and an associative binary operation `op()`.\ntemplate\
    \ <typename M>\nconcept IsMonoid = requires(typename M::value_type a, typename\
    \ M::value_type b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\
    \n    // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 13 \"graph/doubling.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\n// Static binary lifting with ordered aggregates. A step\
    \ collects values[v]\n// before moving to successor[v]. State -1 stays at -1 and\
    \ contributes id().\ntemplate <m1une::monoid::IsMonoid Monoid>\nclass Doubling\
    \ {\n   public:\n    using value_type = typename Monoid::value_type;\n\n    struct\
    \ Result {\n        int vertex;\n        value_type product;\n    };\n\n   private:\n\
    \    int _n = 0;\n    int _levels = 0;\n    std::uint64_t _max_steps = 0;\n  \
    \  // Level-major flat tables: the entry at (bit, v) describes 2^bit steps.\n\
    \    std::vector<int> _next;\n    std::vector<value_type> _products;\n\n    void\
    \ check_query(int vertex, std::uint64_t steps) const {\n        assert(-1 <= vertex\
    \ && vertex < _n);\n        assert(steps <= _max_steps);\n        (void)vertex;\n\
    \        (void)steps;\n    }\n\n   public:\n    Doubling() = default;\n\n    Doubling(const\
    \ std::vector<int>& successor, const std::vector<value_type>& values,\n      \
    \       std::uint64_t max_steps) {\n        build(successor, values, max_steps);\n\
    \    }\n\n    void build(const std::vector<int>& successor, const std::vector<value_type>&\
    \ values,\n               std::uint64_t max_steps) {\n        assert(successor.size()\
    \ == values.size());\n        assert(successor.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(successor.size());\n        for (int to : successor)\
    \ {\n            assert(-1 <= to && to < n);\n            (void)to;\n        }\n\
    \        _n = n;\n        _levels = std::bit_width(max_steps);\n        _max_steps\
    \ = max_steps;\n        assert(_levels == 0 || std::size_t(n) <=\n           \
    \        std::numeric_limits<std::size_t>::max() / std::size_t(_levels));\n  \
    \      const std::size_t total = std::size_t(n) * std::size_t(_levels);\n    \
    \    _next = std::vector<int>(total, -1);\n        _products = std::vector<value_type>(total,\
    \ Monoid::id());\n        if (_levels == 0) return;\n\n        std::copy(successor.begin(),\
    \ successor.end(), _next.begin());\n        std::copy(values.begin(), values.end(),\
    \ _products.begin());\n        for (int bit = 1; bit < _levels; ++bit) {\n   \
    \         const std::size_t previous = std::size_t(bit - 1) * std::size_t(n);\n\
    \            const std::size_t current = previous + std::size_t(n);\n        \
    \    for (int vertex = 0; vertex < n; ++vertex) {\n                const int middle\
    \ = _next[previous + vertex];\n                if (middle == -1) {\n         \
    \           _products[current + vertex] = _products[previous + vertex];\n    \
    \            } else {\n                    _next[current + vertex] = _next[previous\
    \ + middle];\n                    _products[current + vertex] = Monoid::op(\n\
    \                        _products[previous + vertex], _products[previous + middle]);\n\
    \                }\n            }\n        }\n    }\n\n    int size() const {\
    \ return _n; }\n\n    bool empty() const { return _n == 0; }\n\n    int levels()\
    \ const { return _levels; }\n\n    std::uint64_t max_steps() const { return _max_steps;\
    \ }\n\n    int jump(int vertex, std::uint64_t steps) const {\n        check_query(vertex,\
    \ steps);\n        while (steps != 0 && vertex != -1) {\n            const int\
    \ bit = std::countr_zero(steps);\n            vertex = _next[std::size_t(bit)\
    \ * std::size_t(_n) + vertex];\n            steps &= steps - 1;\n        }\n \
    \       return vertex;\n    }\n\n    Result walk(int vertex, std::uint64_t steps)\
    \ const {\n        check_query(vertex, steps);\n        Result result{vertex,\
    \ Monoid::id()};\n        while (steps != 0 && result.vertex != -1) {\n      \
    \      const int bit = std::countr_zero(steps);\n            const std::size_t\
    \ index = std::size_t(bit) * std::size_t(_n) + result.vertex;\n            result.product\
    \ = Monoid::op(result.product, _products[index]);\n            result.vertex =\
    \ _next[index];\n            steps &= steps - 1;\n        }\n        return result;\n\
    \    }\n\n    value_type prod(int vertex, std::uint64_t steps) const {\n     \
    \   return walk(vertex, steps).product;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_DOUBLING_HPP\n#define M1UNE_GRAPH_DOUBLING_HPP 1\n\n\
    #include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <limits>\n#include <vector>\n\n#include \"../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\n// Static binary lifting with ordered\
    \ aggregates. A step collects values[v]\n// before moving to successor[v]. State\
    \ -1 stays at -1 and contributes id().\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    class Doubling {\n   public:\n    using value_type = typename Monoid::value_type;\n\
    \n    struct Result {\n        int vertex;\n        value_type product;\n    };\n\
    \n   private:\n    int _n = 0;\n    int _levels = 0;\n    std::uint64_t _max_steps\
    \ = 0;\n    // Level-major flat tables: the entry at (bit, v) describes 2^bit\
    \ steps.\n    std::vector<int> _next;\n    std::vector<value_type> _products;\n\
    \n    void check_query(int vertex, std::uint64_t steps) const {\n        assert(-1\
    \ <= vertex && vertex < _n);\n        assert(steps <= _max_steps);\n        (void)vertex;\n\
    \        (void)steps;\n    }\n\n   public:\n    Doubling() = default;\n\n    Doubling(const\
    \ std::vector<int>& successor, const std::vector<value_type>& values,\n      \
    \       std::uint64_t max_steps) {\n        build(successor, values, max_steps);\n\
    \    }\n\n    void build(const std::vector<int>& successor, const std::vector<value_type>&\
    \ values,\n               std::uint64_t max_steps) {\n        assert(successor.size()\
    \ == values.size());\n        assert(successor.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(successor.size());\n        for (int to : successor)\
    \ {\n            assert(-1 <= to && to < n);\n            (void)to;\n        }\n\
    \        _n = n;\n        _levels = std::bit_width(max_steps);\n        _max_steps\
    \ = max_steps;\n        assert(_levels == 0 || std::size_t(n) <=\n           \
    \        std::numeric_limits<std::size_t>::max() / std::size_t(_levels));\n  \
    \      const std::size_t total = std::size_t(n) * std::size_t(_levels);\n    \
    \    _next = std::vector<int>(total, -1);\n        _products = std::vector<value_type>(total,\
    \ Monoid::id());\n        if (_levels == 0) return;\n\n        std::copy(successor.begin(),\
    \ successor.end(), _next.begin());\n        std::copy(values.begin(), values.end(),\
    \ _products.begin());\n        for (int bit = 1; bit < _levels; ++bit) {\n   \
    \         const std::size_t previous = std::size_t(bit - 1) * std::size_t(n);\n\
    \            const std::size_t current = previous + std::size_t(n);\n        \
    \    for (int vertex = 0; vertex < n; ++vertex) {\n                const int middle\
    \ = _next[previous + vertex];\n                if (middle == -1) {\n         \
    \           _products[current + vertex] = _products[previous + vertex];\n    \
    \            } else {\n                    _next[current + vertex] = _next[previous\
    \ + middle];\n                    _products[current + vertex] = Monoid::op(\n\
    \                        _products[previous + vertex], _products[previous + middle]);\n\
    \                }\n            }\n        }\n    }\n\n    int size() const {\
    \ return _n; }\n\n    bool empty() const { return _n == 0; }\n\n    int levels()\
    \ const { return _levels; }\n\n    std::uint64_t max_steps() const { return _max_steps;\
    \ }\n\n    int jump(int vertex, std::uint64_t steps) const {\n        check_query(vertex,\
    \ steps);\n        while (steps != 0 && vertex != -1) {\n            const int\
    \ bit = std::countr_zero(steps);\n            vertex = _next[std::size_t(bit)\
    \ * std::size_t(_n) + vertex];\n            steps &= steps - 1;\n        }\n \
    \       return vertex;\n    }\n\n    Result walk(int vertex, std::uint64_t steps)\
    \ const {\n        check_query(vertex, steps);\n        Result result{vertex,\
    \ Monoid::id()};\n        while (steps != 0 && result.vertex != -1) {\n      \
    \      const int bit = std::countr_zero(steps);\n            const std::size_t\
    \ index = std::size_t(bit) * std::size_t(_n) + result.vertex;\n            result.product\
    \ = Monoid::op(result.product, _products[index]);\n            result.vertex =\
    \ _next[index];\n            steps &= steps - 1;\n        }\n        return result;\n\
    \    }\n\n    value_type prod(int vertex, std::uint64_t steps) const {\n     \
    \   return walk(vertex, steps).product;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n#endif  // M1UNE_GRAPH_DOUBLING_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: graph/doubling.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-11-17 03:42:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/doubling.test.cpp
  - verify/graph/graph_algorithms.test.cpp
  - verify/graph/doubling_jump_on_tree.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
documentation_of: graph/doubling.hpp
layout: document
title: Doubling with Monoid Aggregates
---

## Overview

`m1une::graph::Doubling<Monoid>` preprocesses a fixed transition from each state.
It answers where you arrive after `k` steps and the monoid product collected
along the way, using only the set bits of `k`.

Use it for repeated transitions with sums, minima, matrices, or ordered
function products. If you need cycle decomposition, reachability, or meeting
queries without aggregates, see
[FunctionalGraph](https://m1une.github.io/m1une_library/graph/functional_graph.hpp).

## Step and Product Convention

The constructor takes equally sized vectors `successor` and `values`.
States have indices `[0, N)`. One step from state `v`:

1. Collects `values[v]`.
2. Moves to `successor[v]`.

Thus `walk(v, 0)` returns `v` and the identity, while `walk(v, 1)` returns
`successor[v]` and `values[v]`. The arrival state's value is excluded until
another step is taken.

The special state `-1` is absorbing: it stays at `-1` and contributes the
identity. A transition to `-1` still collects its source state's value.
For `0 -> 1 -> -1` with values `4, 7`, the products for zero, one, two, and
three steps from `0` are `id()`, `4`, `op(4, 7)`, and `op(4, 7)`.
Starting a query at `-1` is also allowed. If a root or terminal state should
not contribute a value, give that state `Monoid::id()`.

Products combine values in traversal order:

```cpp
product = Monoid::op(product, values[current]);
current = successor[current];
```

Commutativity is not required. This is the same ordered-product convention as
[Segtree](https://m1une.github.io/m1une_library/ds/segtree/segtree.hpp).
The supplied
[Affine monoid](https://m1une.github.io/m1une_library/monoid/affine.hpp) defines
`op(f, g) = f(g(x))`, so its rightmost function acts first. To apply functions
in traversal order to an argument, use a monoid with `op(f, g) = g(f(x))`.

## How Doubling Works

Level `b` stores the destination and product for exactly `2^b` steps from
every state. Level zero comes directly from the input. Each higher level joins
two consecutive blocks of half that length:

```text
middle = next[b - 1][v]
next[b][v] = next[b - 1][middle]
product[b][v] = op(product[b - 1][v], product[b - 1][middle])
```

An absorbing middle state contributes an identity second block. To answer six
steps, the query takes a two-step block, then a four-step block starting at the
new state. Their products are appended in that order. The tables are flat,
contiguous arrays arranged by level.

## Requirements

`Monoid` must satisfy
[`m1une::monoid::IsMonoid`](https://m1une.github.io/m1une_library/monoid/concept.hpp).
It supplies `value_type`, associative `op`, and a two-sided identity `id()`.
The value type must be copyable; default construction, comparison, and
inverses are not required.

`max_steps` is an explicit inclusive upper bound on every query's step count.
It determines the table height, rather than silently allocating 64 levels.
All `std::uint64_t` bounds are supported, including `UINT64_MAX`. A bound of
zero allocates no table entries and supports only zero-step queries.

The input sizes must match and fit in `int`. Every successor must be `-1` or
an index in `[0, N)`. Query starts must be in `[-1, N)` and step counts must
not exceed `max_steps()`. These requirements are asserted, including for
zero-step queries. Empty input is supported; only start state `-1` is valid.

All precomputed and queried products must be representable by the value type.
For variable-sized values such as strings, account for their actual lengths
when estimating time and memory.

## Interface and Complexity

The public types are:

```cpp
using value_type = typename Monoid::value_type;

struct Result {
    int vertex;
    value_type product;
};
```

Let `N = size()`, `B = bit_width(max_steps())` (`0 <= B <= 64`), and `S_old`
be the previous table-entry count when rebuilding. Let `P = popcount(steps)`.
Bounds count each monoid operation, value copy, and value destruction as
constant time. The tables store `N * B` integers and `N * B` aggregate values.

| Method | Description | Complexity |
| --- | --- | --- |
| `Doubling()` | Creates an empty object with maximum step count zero. | $O(1)$ |
| `Doubling(const std::vector<int>& successor, const std::vector<value_type>& values, std::uint64_t max_steps)` | Validates the input and constructs the tables. | $O(1 + N + NB)$ time, $O(NB)$ table space |
| `void build(const std::vector<int>& successor, const std::vector<value_type>& values, std::uint64_t max_steps)` | Replaces all transitions, values, and the query bound; releases the old tables. | $O(1 + S_{old} + N + NB)$ time |
| `int size() const` | Returns the number of ordinary states, excluding `-1`. | $O(1)$ |
| `bool empty() const` | Returns whether there are no ordinary states. | $O(1)$ |
| `int levels() const` | Returns `B`, the table height. | $O(1)$ |
| `std::uint64_t max_steps() const` | Returns the inclusive query bound. | $O(1)$ |
| `int jump(int vertex, std::uint64_t steps) const` | Returns the destination only; performs no monoid operations. | $O(1 + P)$ |
| `Result walk(int vertex, std::uint64_t steps) const` | Returns both destination and ordered product. | $O(1 + P)$ |
| `value_type prod(int vertex, std::uint64_t steps) const` | Returns only the ordered product. | $O(1 + P)$ |

Queries stop early after reaching `-1`. They are `const`, allocate no table
entries, and never change the object. The monoid itself may allocate memory
for its values. Transitions and values are static between calls to `build`.

Copying an object copies its tables in $O(1 + NB)$ time and space. Moving it
transfers vector storage in $O(1)$; do not query a moved-from object until it
has been rebuilt or assigned. Assignment and destruction also account for
releasing the destination's previous aggregate values. During a rebuild, old
and new table storage can temporarily coexist.

## Example

```cpp
#include "graph/doubling.hpp"
#include "monoid/add.hpp"
#include <cassert>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    std::vector<int> successor = {1, 2, 0};
    std::vector<long long> values = {10, 20, 30};
    m1une::graph::Doubling<Sum> doubling(successor, values, 1000000000000ULL);

    auto result = doubling.walk(0, 5);  // Collect at 0, 1, 2, 0, 1; arrive at 2.
    assert(result.vertex == 2);
    assert(result.product == 90);
    assert(doubling.jump(1, 0) == 1);
    assert(doubling.prod(1, 0) == 0);

    successor = {1, -1};
    values = {4, 7};
    doubling.build(successor, values, 10);
    auto stopped = doubling.walk(0, 10);
    assert(stopped.vertex == -1 && stopped.product == 11);
}
```

## Verification

Library Checker's
[Static Range Sum](https://github.com/yosupo06/library-checker-problems/tree/master/data_structure/static_range_sum)
checks aggregates along a linear successor sequence, and
[Jump on Tree](https://github.com/yosupo06/library-checker-problems/tree/master/tree/jump_on_tree)
checks ancestor jumps and path lengths. Randomized tests compare sums,
noncommutative affine products, and string concatenation against direct
simulation. Focused cases cover stopping states, zero steps, rebuilds, empty
inputs, values without default constructors, and full-width 64-bit queries.
