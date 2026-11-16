---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_arg_max.hpp\"\n\n\n\n#include\
    \ <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long size;\n\
    \    long long ord;\n};\n\n// Acted Monoid for Range Addition and Range Maximum\
    \ Value & Index queries.\ntemplate <typename T>\nstruct RangeAddRangeArgMax {\n\
    \    using value_type = RangeAddRangeArgMaxNode<T>;\n    using operator_type =\
    \ T;\n    static constexpr bool commutative = false;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    static constexpr value_type id() {\n   \
    \     return {std::numeric_limits<T>::lowest(), 0, -1};\n    }\n\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.size\
    \ == 0) return b;\n        if (b.size == 0) return a;\n        long long size\
    \ = a.size + b.size;\n        if (a.max_val >= b.max_val) return {a.max_val, size,\
    \ a.ord};\n        return {b.max_val, size, b.ord + a.size};\n    }\n\n    static\
    \ constexpr operator_type op_id() {\n        return T(0);\n    }\n\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.size == 0) return x;\n\
    \        return {x.max_val + f, x.size, x.ord};\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1, 0};\n    }\n};\n\n\
    }  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\
    \ 1\n\n#include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeArgMaxNode {\n    T max_val;\n    long long\
    \ size;\n    long long ord;\n};\n\n// Acted Monoid for Range Addition and Range\
    \ Maximum Value & Index queries.\ntemplate <typename T>\nstruct RangeAddRangeArgMax\
    \ {\n    using value_type = RangeAddRangeArgMaxNode<T>;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = false;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    static constexpr value_type id() {\n   \
    \     return {std::numeric_limits<T>::lowest(), 0, -1};\n    }\n\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        if (a.size\
    \ == 0) return b;\n        if (b.size == 0) return a;\n        long long size\
    \ = a.size + b.size;\n        if (a.max_val >= b.max_val) return {a.max_val, size,\
    \ a.ord};\n        return {b.max_val, size, b.ord + a.size};\n    }\n\n    static\
    \ constexpr operator_type op_id() {\n        return T(0);\n    }\n\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (x.size == 0) return x;\n\
    \        return {x.max_val + f, x.size, x.ord};\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1, 0};\n    }\n};\n\n\
    }  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_ARG_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_arg_max.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_add_range_arg_max.hpp
layout: document
title: Range Add Range ArgMax
---

## Overview

An acted monoid for range addition and range maximum queries with the position
of the selected maximum.

### Tie-breaking

If there are multiple maximum values in the queried range, the `op` function returns the earliest order.

## Requirements and Behavior

`value_type` stores `max_val`, `size`, and `ord`. `ord` is the zero-based
position within the aggregate, so `prod(l, r)` reports array index `l + ord`.
Ties choose the earliest position. An empty result has `ord == -1`.

## Interface and Complexity

```cpp
using value_type = RangeAddRangeArgMaxNode<T>;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "acted_monoid/range_add_range_arg_max.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeArgMax<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 5, 3, 5});
    seg.apply(1, 3, 2);
    auto result = seg.prod(1, 4);
    assert(result.max_val == 7);
    assert(1 + result.ord == 1);  // Convert query-relative order to array index.
}
```
