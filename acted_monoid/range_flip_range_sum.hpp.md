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
  bundledCode: "#line 1 \"acted_monoid/range_flip_range_sum.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeFlipRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\n// Acted Monoid for binary arrays\
    \ (0s and 1s).\n// Supports range bit inversion (flip) and range sum queries.\n\
    template <typename T = long long>\nstruct RangeFlipRangeSum {\n    using value_type\
    \ = RangeFlipRangeSumNode<T>;\n    using operator_type = bool;  // 'true' means\
    \ flip the bits in the range\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = true;\n\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0};\n    }\n\n    static constexpr\
    \ value_type op(const value_type& a, const value_type& b) {\n        return {a.sum\
    \ + b.sum, a.size + b.size};\n    }\n\n    static constexpr operator_type op_id()\
    \ {\n        return false;\n    }\n\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f ^ g;\n    }\n\n\
    \    static constexpr value_type mapping(const operator_type& f, const value_type&\
    \ x) {\n        if (!f || x.size == 0) return x;\n        // If flipped, the new\
    \ number of 1s is exactly (Total Elements - Old number of 1s)\n        return\
    \ {static_cast<T>(x.size) - x.sum, x.size};\n    }\n\n    // Initialize with a\
    \ 0 or 1\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP\
    \ 1\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeFlipRangeSumNode {\n    T sum;\n    long long size;\n};\n\n// Acted\
    \ Monoid for binary arrays (0s and 1s).\n// Supports range bit inversion (flip)\
    \ and range sum queries.\ntemplate <typename T = long long>\nstruct RangeFlipRangeSum\
    \ {\n    using value_type = RangeFlipRangeSumNode<T>;\n    using operator_type\
    \ = bool;  // 'true' means flip the bits in the range\n    static constexpr bool\
    \ commutative = true;\n    static constexpr bool operator_commutative = true;\n\
    \n    static constexpr value_type id() {\n        return {T(0), 0};\n    }\n\n\
    \    static constexpr value_type op(const value_type& a, const value_type& b)\
    \ {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n\n    static constexpr\
    \ operator_type op_id() {\n        return false;\n    }\n\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f ^ g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f || x.size == 0) return x;\n      \
    \  // If flipped, the new number of 1s is exactly (Total Elements - Old number\
    \ of 1s)\n        return {static_cast<T>(x.size) - x.sum, x.size};\n    }\n\n\
    \    // Initialize with a 0 or 1\n    static constexpr value_type make(const T&\
    \ val) {\n        return {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_flip_range_sum.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_flip_range_sum.hpp
layout: document
title: Range Flip Range Sum
---

## Overview

An Acted Monoid designed specifically for binary arrays ($0$s and $1$s). It supports Range Bit Inversion (flipping $0 \leftrightarrow 1$) operations and Range Sum queries (which effectively counts the number of $1$s in the range).

### Important Usage Note

This is a highly optimized structure. When a range is flipped, the new sum (number of $1$s) becomes exactly `size - old_sum`. Therefore, the `value_type` tracks both the `sum` and the `size`.

The `operator_type` is a boolean, where `true` indicates that the range should be flipped, and `false` is the identity operation (no-op).

## Interface and Complexity

```cpp
using value_type = RangeFlipRangeSumNode<T>;
using operator_type = bool;
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
#include "acted_monoid/range_flip_range_sum.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeFlipRangeSum<long long>;

int main() {
    std::vector<long long> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // Sum of [0, 5) is 2 (two 1s)
    std::cout << "Initial 1s: " << seg.prod(0, 5).sum << "\n";

    // Flip bits in range [1, 4) -> Indices 1, 2, 3
    // Array becomes: {1, 1, 0, 1, 0}
    seg.apply(1, 4, true);

    // Sum of [0, 5) is now 3
    std::cout << "Updated 1s: " << seg.prod(0, 5).sum << "\n";

    return 0;
}
```
