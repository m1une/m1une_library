---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/acted_monoid/range_add_range_gcd.test.cpp
    title: verify/acted_monoid/range_add_range_gcd.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_gcd.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <numeric>\n#include <type_traits>\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeAddRangeGcdNode {\n    T min;\n    T\
    \ diff_gcd;\n    bool empty;\n};\n\n// Range addition preserves the GCD of differences\
    \ from the minimum.\ntemplate <typename T>\nstruct RangeAddRangeGcd {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    using value_type = RangeAddRangeGcdNode<T>;\n\
    \    using operator_type = T;\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = true;\n\n    static constexpr\
    \ value_type id() {\n        return {T(0), T(0), true};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.empty)\
    \ return b;\n        if (b.empty) return a;\n        return {std::min(a.min, b.min),\n\
    \                std::gcd(std::gcd(a.diff_gcd, b.diff_gcd), T(a.min - b.min)),\
    \ false};\n    }\n\n    static constexpr operator_type op_id() {\n        return\
    \ T(0);\n    }\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (x.empty) return x;\n        return {T(x.min + f), x.diff_gcd,\
    \ false};\n    }\n\n    static constexpr value_type make(const T& val) {\n   \
    \     return {val, T(0), false};\n    }\n    // Returns a nonnegative GCD, or\
    \ zero for an empty range.\n    static constexpr T gcd(const value_type& x) {\n\
    \        return std::gcd(x.min, x.diff_gcd);\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP\
    \ 1\n\n#include <algorithm>\n#include <numeric>\n#include <type_traits>\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeGcdNode\
    \ {\n    T min;\n    T diff_gcd;\n    bool empty;\n};\n\n// Range addition preserves\
    \ the GCD of differences from the minimum.\ntemplate <typename T>\nstruct RangeAddRangeGcd\
    \ {\n    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);\n\n    using\
    \ value_type = RangeAddRangeGcdNode<T>;\n    using operator_type = T;\n    static\
    \ constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = true;\n\n    static constexpr value_type id() {\n        return {T(0), T(0),\
    \ true};\n    }\n    static constexpr value_type op(const value_type& a, const\
    \ value_type& b) {\n        if (a.empty) return b;\n        if (b.empty) return\
    \ a;\n        return {std::min(a.min, b.min),\n                std::gcd(std::gcd(a.diff_gcd,\
    \ b.diff_gcd), T(a.min - b.min)), false};\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return T(0);\n    }\n    // Returns f(g(x)).\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.empty) return x;\n \
    \       return {T(x.min + f), x.diff_gcd, false};\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, T(0), false};\n    }\n\
    \    // Returns a nonnegative GCD, or zero for an empty range.\n    static constexpr\
    \ T gcd(const value_type& x) {\n        return std::gcd(x.min, x.diff_gcd);\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_GCD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_gcd.hpp
  requiredBy: []
  timestamp: '2026-11-17 02:00:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/acted_monoid/range_add_range_gcd.test.cpp
documentation_of: acted_monoid/range_add_range_gcd.hpp
layout: document
title: Range Add Range GCD
---

## Overview

`m1une::acted_monoid::RangeAddRangeGcd<T>` supports adding a constant to a
range and querying its nonnegative greatest common divisor with
[LazySegtree](https://m1une.github.io/m1une_library/ds/segtree/lazy_segtree.hpp).
All ranges are zero-based and half-open.

A nonempty node stores its minimum `min` and
`diff_gcd = gcd(a[i] - min)` over the represented elements. Its answer is
`gcd(min, diff_gcd)`. Uniform addition shifts only the minimum. Merging two
nodes takes the smaller minimum and the GCD of both `diff_gcd` values and
the difference between their minima. This representation is associative and
commutative, and supports negative values and negative additions.

## Types and Requirements

* `T` must be a signed integral type supported by `std::gcd`, such as `int`
  or `long long`.
* All element values, additions, composed lazy tags, and intermediate sums must
  fit in `T`. Absolute values of element values and pairwise differences must
  also fit in `T`; in particular, do not use the minimum representable value.
  Arithmetic is neither widened nor checked for overflow.
* `value_type` is `RangeAddRangeGcdNode<T>`, an aggregate with fields `T min`,
  `T diff_gcd`, and `bool empty`. Construct leaves with `make(value)` and empty
  nodes with `id()`. An empty node has both numeric fields zero. A singleton
  has `diff_gcd == 0`; a zero-valued singleton is distinct from an empty node.
* `operator_type` is `T`, representing addition by that amount.
* `commutative` and `operator_commutative` are both `true`.

## Interface and Complexity

All methods below are `static constexpr`, return new values, and do not mutate
their arguments. Let $V$ bound the absolute values and differences supplied to
GCD operations. Complexities count fixed-width arithmetic operations.

| Signature | Behavior | Time |
| --- | --- | --- |
| `value_type id()` | Empty-range identity. | $O(1)$ |
| `value_type op(const value_type& a, const value_type& b)` | Merges two nodes; an empty node is ignored. | $O(\log(V+2))$ |
| `operator_type op_id()` | Returns zero, the identity addition. | $O(1)$ |
| `operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns `f + g`, applying `g` then `f`. | $O(1)$ |
| `value_type mapping(const operator_type& f, const value_type& x)` | Adds `f` to the represented elements; preserves an empty node. | $O(1)$ |
| `value_type make(const T& val)` | Makes a singleton node. | $O(1)$ |
| `T gcd(const value_type& x)` | Returns the nonnegative range GCD; returns zero for an empty range or all-zero range. | $O(\log(V+2))$ |

The tag has no state or explicit constructors. Every node uses $O(1)$ space.
With `LazySegtree`, building from $n$ scalar values costs
$O(n\log(V+2))$ time and $O(n)$ space. Range additions, point assignments,
and range GCD queries cost $O(\log(n+2)\log(V+2))$ time in the worst case.
Build from a vector of scalar values (or `make` nodes): the size-only tree
constructor initializes empty identities, rather than zero-valued leaves.

## Example

```cpp
#include <cassert>
#include <vector>

#include "acted_monoid/range_add_range_gcd.hpp"
#include "ds/segtree/lazy_segtree.hpp"

using AM = m1une::acted_monoid::RangeAddRangeGcd<long long>;

int main() {
    std::vector<long long> values = {6, 10, 14};
    m1une::ds::LazySegtree<AM> seg(values);
    assert(AM::gcd(seg.prod(0, 3)) == 2);

    seg.apply(0, 3, 2);  // {8, 12, 16}
    assert(AM::gcd(seg.all_prod()) == 4);
    seg.apply(1, 3, -4);  // {8, 8, 12}
    assert(AM::gcd(seg.prod(0, 2)) == 8);

    seg.set(0, AM::make(-6));
    assert(AM::gcd(seg.prod(0, 1)) == 6);
    assert(AM::gcd(seg.prod(1, 1)) == 0);
}
```

## Verification

[yukicoder No.1036: Make One With GCD 2](https://yukicoder.me/problems/no/1036)
checks range GCD aggregation and segment-tree boundary searches. The same
verification source includes deterministic algebra checks and randomized
range additions, point assignments, and GCD queries against a naive array.
