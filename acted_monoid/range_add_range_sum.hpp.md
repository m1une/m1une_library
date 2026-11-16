---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
    title: verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
    title: verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dynamic_tree/lazy_path_link_cut_tree.test.cpp
    title: verify/ds/dynamic_tree/lazy_path_link_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_release.test.cpp
    title: verify/ds/persistent_release.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_lazy_segtree.test.cpp
    title: verify/ds/segtree/persistent_lazy_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = true;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    // Value Monoid (Sum)\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.sum + b.sum,\
    \ a.size + b.size};\n    }\n    static constexpr value_type inv(const value_type&\
    \ x) {\n        return {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n\
    \    static constexpr operator_type op_id() {\n        return 0;\n    }\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    // Mapping (sum + f * size)\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return {x.sum + f * x.size, x.size};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeAddRangeSumNode {\n    T sum;\n    long long size;\n};\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeSum {\n    using value_type = RangeAddRangeSumNode<T>;\n\
    \    using operator_type = T;\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = true;\n\n    // Value Monoid\
    \ (Sum)\n    static constexpr value_type id() {\n        return {T(0), 0};\n \
    \   }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n    static constexpr\
    \ value_type inv(const value_type& x) {\n        return {-x.sum, -x.size};\n \
    \   }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return 0;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping (sum + f * size)\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return {x.sum + f * x.size,\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_sum.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_release.test.cpp
  - verify/ds/dynamic_tree/lazy_path_link_cut_tree.test.cpp
  - verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
  - verify/ds/segtree/persistent_dynamic_lazy_segtree.test.cpp
  - verify/ds/segtree/persistent_lazy_segtree.test.cpp
  - verify/ds/segtree/dynamic_lazy_segtree.test.cpp
  - verify/ds/dynamic_array/persistent_dynamic_lazy_monoid_array.test.cpp
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_add_range_sum.hpp
layout: document
title: Range Add Range Sum
---

## Overview

An acted monoid for adding a constant to every element in a range and querying
the range sum.

### Important Usage Note

When adding a value $f$ to a range of sum $x$, the total sum increases by $f \times (\text{length of the range})$. Therefore, the `value_type` cannot just be an integer; it must keep track of the **size** of the range it currently represents.

The `value_type` is defined as `RangeAddRangeSumNode<T>`, which holds both the `sum` and the `size`.

Initialize from a vector of raw values, which `LazySegtree` converts with
`make(val)`, or construct the leaf aggregates explicitly. Avoid the size-only
constructor for an ordinary array: its identity leaves have size zero.

## Requirements and Behavior

The node stores `T sum` and `long long size`; `make(v)` represents one
element, while `id()` has size zero. The operator is the amount to add.

## Interface and Complexity

```cpp
using value_type = RangeAddRangeSumNode<T>;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type inv(const value_type& x)` | Returns the group inverse of `x`. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
    seg.apply(1, 3, 4);  // Values become 1, 6, 7.
    assert(seg.prod(0, 3).sum == 14);
    seg.set(0, AM::make(10));
    assert(seg.all_prod().sum == 23);
}
```
