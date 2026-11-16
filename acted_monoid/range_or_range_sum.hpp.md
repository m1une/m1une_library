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
  bundledCode: "#line 1 \"acted_monoid/range_or_range_sum.hpp\"\n\n\n\n#include <array>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T, int BITS\
    \ = 30>\nstruct RangeOrRangeSumNode {\n    T sum;\n    std::array<int, BITS> bit_count;\n\
    \    long long size;\n};\n\n// Acted Monoid for Range OR updates and Range Sum\
    \ queries.\ntemplate <typename T, int BITS = 30>\nstruct RangeOrRangeSum {\n \
    \   using value_type = RangeOrRangeSumNode<T, BITS>;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = true;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    static constexpr value_type id() {\n   \
    \     value_type res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n\
    \        res.size = 0;\n        return res;\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res;\n  \
    \      res.sum = a.sum + b.sum;\n        res.size = a.size + b.size;\n       \
    \ for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i]\
    \ + b.bit_count[i];\n        }\n        return res;\n    }\n\n    static constexpr\
    \ operator_type op_id() {\n        return T(0);\n    }\n\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f | g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (f == T(0) || x.size == 0) return x;\n\
    \        value_type res = x;\n        res.sum = T(0);\n        for (int i = 0;\
    \ i < BITS; ++i) {\n            if ((f >> i) & 1) {\n                res.bit_count[i]\
    \ = x.size;  // OR forces the bit to be 1 for all elements\n            }\n  \
    \          res.sum += static_cast<T>(res.bit_count[i]) * (T(1) << i);\n      \
    \  }\n        return res;\n    }\n\n    static constexpr value_type make(const\
    \ T& val) {\n        value_type res;\n        res.sum = val;\n        res.size\
    \ = 1;\n        for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i]\
    \ = ((val >> i) & 1) ? 1 : 0;\n        }\n        return res;\n    }\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_OR_RANGE_SUM_HPP\n#define M1UNE_ACTED_MONOID_RANGE_OR_RANGE_SUM_HPP\
    \ 1\n\n#include <array>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <typename T, int BITS = 30>\nstruct RangeOrRangeSumNode {\n    T sum;\n    std::array<int,\
    \ BITS> bit_count;\n    long long size;\n};\n\n// Acted Monoid for Range OR updates\
    \ and Range Sum queries.\ntemplate <typename T, int BITS = 30>\nstruct RangeOrRangeSum\
    \ {\n    using value_type = RangeOrRangeSumNode<T, BITS>;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = true;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    static constexpr value_type id() {\n   \
    \     value_type res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n\
    \        res.size = 0;\n        return res;\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        value_type res;\n  \
    \      res.sum = a.sum + b.sum;\n        res.size = a.size + b.size;\n       \
    \ for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i]\
    \ + b.bit_count[i];\n        }\n        return res;\n    }\n\n    static constexpr\
    \ operator_type op_id() {\n        return T(0);\n    }\n\n    static constexpr\
    \ operator_type op_comp(const operator_type& f, const operator_type& g) {\n  \
    \      return f | g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (f == T(0) || x.size == 0) return x;\n\
    \        value_type res = x;\n        res.sum = T(0);\n        for (int i = 0;\
    \ i < BITS; ++i) {\n            if ((f >> i) & 1) {\n                res.bit_count[i]\
    \ = x.size;  // OR forces the bit to be 1 for all elements\n            }\n  \
    \          res.sum += static_cast<T>(res.bit_count[i]) * (T(1) << i);\n      \
    \  }\n        return res;\n    }\n\n    static constexpr value_type make(const\
    \ T& val) {\n        value_type res;\n        res.sum = val;\n        res.size\
    \ = 1;\n        for (int i = 0; i < BITS; ++i) {\n            res.bit_count[i]\
    \ = ((val >> i) & 1) ? 1 : 0;\n        }\n        return res;\n    }\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_OR_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_or_range_sum.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_or_range_sum.hpp
layout: document
title: Range OR Range Sum
---

## Overview

An Acted Monoid representing Range Bitwise OR operations and Range Sum queries.

### Mathematical Mechanism

Because Bitwise OR does not distribute directly over addition, the node must track how many times each individual bit is set within its range. When a Range OR is applied with a value $f$, any bit set to `1` in $f$ forces that specific bit to become `1` for *every* element in the segment. Its bit count immediately becomes equal to `size`.

## Template Parameters

* `T`: The underlying numerical type.
* `BITS`: Max bit length (default 30). Set to 60 for `long long` bounds.

## Requirements and Behavior

The node stores `T sum`, `std::array<int, BITS> bit_count`, and
`long long size`. Read the range sum from `.sum`; `.bit_count[i]` is the number
of elements with bit `i` set. `op_id()` is zero and composition is bitwise OR.

## Interface and Complexity

```cpp
using value_type = RangeOrRangeSumNode<T, BITS>;
using operator_type = T;
```

Let $B = \mathtt{BITS}$. Values and masks must be nonnegative and fit in the lowest `BITS` bits. Choose `T` wide enough for the segment sum and keep segment lengths within `int` for the per-bit counts.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(B)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(B)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(B)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(B)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.
With `LazySegtree`, construction uses $O(NB)$ time and space, and range updates and queries take $O(B \log N)$ time.

## Example

```cpp
#include "acted_monoid/range_or_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeOrRangeSum<long long, 4>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{1, 2, 3});
    seg.apply(0, 2, 4);  // Values become 5, 6, 3.
    assert(seg.prod(0, 3).sum == 14);
}
```
