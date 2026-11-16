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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_sum.hpp\"\n\n\n\n#include\
    \ <optional>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T>\nstruct RangeUpdateRangeSumNode {\n    T sum;\n    long long size;\n};\n\n\
    template <typename T>\nstruct RangeUpdateRangeSum {\n    using value_type = RangeUpdateRangeSumNode<T>;\n\
    \    using operator_type = std::optional<T>;\n    static constexpr bool commutative\
    \ = true;\n    static constexpr bool operator_commutative = false;\n\n    static\
    \ constexpr value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size};\n    }\n\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f.has_value() ?\
    \ f : g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x.size == 0) return\
    \ x;\n        return {f.value() * static_cast<T>(x.size), x.size};\n    }\n\n\
    \    static constexpr value_type make(const T& val) {\n        return {val, 1};\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP\
    \ 1\n\n#include <optional>\n\nnamespace m1une {\nnamespace acted_monoid {\n\n\
    template <typename T>\nstruct RangeUpdateRangeSumNode {\n    T sum;\n    long\
    \ long size;\n};\n\ntemplate <typename T>\nstruct RangeUpdateRangeSum {\n    using\
    \ value_type = RangeUpdateRangeSumNode<T>;\n    using operator_type = std::optional<T>;\n\
    \    static constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = false;\n\n    static constexpr value_type id() {\n        return {T(0), 0};\n\
    \    }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n\n    static\
    \ constexpr operator_type op_id() {\n        return std::nullopt;\n    }\n   \
    \ static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f.has_value() ? f : g;\n    }\n\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        if (!f.has_value()\
    \ || x.size == 0) return x;\n        return {f.value() * static_cast<T>(x.size),\
    \ x.size};\n    }\n\n    static constexpr value_type make(const T& val) {\n  \
    \      return {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_sum.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_update_range_sum.hpp
layout: document
title: Range Update Range Sum
---

## Overview

An acted monoid that supports range update (overwrite) operations and range sum queries.

### Important Usage Note

Since the sum of a range updated to a single value $f$ becomes $f \times \text{size}$, the `value_type` must maintain the size of the segment. When initializing leaf nodes, use the provided helper function `make(val)` to correctly set the size to 1. The `operator_type` uses `std::optional<T>` to safely represent the state of "no operation".

## Requirements and Behavior

The node stores `T sum` and `long long size`. A present optional update
assigns its value to every element; `std::nullopt` leaves the segment unchanged.
A newer present assignment overrides an older one, including an assignment of zero.

## Interface and Complexity

```cpp
using value_type = RangeUpdateRangeSumNode<T>;
using operator_type = std::optional<T>;
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
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_update_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeUpdateRangeSum<long long>;

int main() {
    std::vector<long long> A = {1, 2, 3, 4, 5};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Update the range [1, 4) to 10
    seg.apply(1, 4, std::optional<long long>(10));

    // Get the sum of the range [0, 5)
    std::cout << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
