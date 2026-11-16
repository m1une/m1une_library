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
  bundledCode: "#line 1 \"acted_monoid/range_update_range_max_subarray.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <optional>\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeUpdateRangeMaxSubarrayNode {\n    T\
    \ sum, pref, suff, max_sub;\n    long long size;\n};\n\n// Acted Monoid for Range\
    \ Assignment (Update) and Max Contiguous Subarray Sum.\n// Note: This implementation\
    \ assumes empty subarrays are allowed (max sum is at least 0).\ntemplate <typename\
    \ T>\nstruct RangeUpdateRangeMaxSubarray {\n    using value_type = RangeUpdateRangeMaxSubarrayNode<T>;\n\
    \    using operator_type = std::optional<T>;\n    static constexpr bool commutative\
    \ = false;\n    static constexpr bool operator_commutative = false;\n\n    static\
    \ constexpr value_type id() {\n        return {T(0), T(0), T(0), T(0), 0};\n \
    \   }\n\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        if (a.size == 0) return b;\n        if (b.size == 0) return a;\n\
    \        value_type res;\n        res.sum = a.sum + b.sum;\n        res.pref =\
    \ std::max(a.pref, a.sum + b.pref);\n        res.suff = std::max(b.suff, b.sum\
    \ + a.suff);\n        res.max_sub = std::max({a.max_sub, b.max_sub, a.suff + b.pref});\n\
    \        res.size = a.size + b.size;\n        return res;\n    }\n\n    static\
    \ constexpr operator_type op_id() {\n        return std::nullopt;\n    }\n\n \
    \   static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f ? f : g;  // left-biased because new updates override\
    \ old ones\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f || x.size == 0) return x;\n      \
    \  value_type res;\n        res.sum = (*f) * x.size;\n        T max_val = std::max(T(0),\
    \ res.sum);\n        // If empty subarrays are NOT allowed, change to: T max_val\
    \ = (*f) > 0 ? res.sum : (*f);\n        res.pref = res.suff = res.max_sub = max_val;\n\
    \        res.size = x.size;\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        T max_val = std::max(T(0), val);\n\
    \        return {val, max_val, max_val, max_val, 1};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\
    \ 1\n\n#include <algorithm>\n#include <optional>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T>\nstruct RangeUpdateRangeMaxSubarrayNode\
    \ {\n    T sum, pref, suff, max_sub;\n    long long size;\n};\n\n// Acted Monoid\
    \ for Range Assignment (Update) and Max Contiguous Subarray Sum.\n// Note: This\
    \ implementation assumes empty subarrays are allowed (max sum is at least 0).\n\
    template <typename T>\nstruct RangeUpdateRangeMaxSubarray {\n    using value_type\
    \ = RangeUpdateRangeMaxSubarrayNode<T>;\n    using operator_type = std::optional<T>;\n\
    \    static constexpr bool commutative = false;\n    static constexpr bool operator_commutative\
    \ = false;\n\n    static constexpr value_type id() {\n        return {T(0), T(0),\
    \ T(0), T(0), 0};\n    }\n\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (a.size == 0) return b;\n        if (b.size\
    \ == 0) return a;\n        value_type res;\n        res.sum = a.sum + b.sum;\n\
    \        res.pref = std::max(a.pref, a.sum + b.pref);\n        res.suff = std::max(b.suff,\
    \ b.sum + a.suff);\n        res.max_sub = std::max({a.max_sub, b.max_sub, a.suff\
    \ + b.pref});\n        res.size = a.size + b.size;\n        return res;\n    }\n\
    \n    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f ? f : g;  // left-biased because new updates\
    \ override old ones\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f || x.size == 0) return x;\n      \
    \  value_type res;\n        res.sum = (*f) * x.size;\n        T max_val = std::max(T(0),\
    \ res.sum);\n        // If empty subarrays are NOT allowed, change to: T max_val\
    \ = (*f) > 0 ? res.sum : (*f);\n        res.pref = res.suff = res.max_sub = max_val;\n\
    \        res.size = x.size;\n        return res;\n    }\n\n    static constexpr\
    \ value_type make(const T& val) {\n        T max_val = std::max(T(0), val);\n\
    \        return {val, max_val, max_val, max_val, 1};\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_MAX_SUBARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_update_range_max_subarray.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_update_range_max_subarray.hpp
layout: document
title: Range Update Range Max Subarray
---

## Overview

An acted monoid for range assignment and maximum contiguous subarray sums.

Each aggregate stores the whole-segment sum, best prefix and suffix sums, and
best subarray sum. Combining adjacent segments also considers a subarray that
crosses their boundary.

### Usage Notes

* `operator_type` uses `std::optional<T>`, where `std::nullopt` represents no operation.
* It always allows an empty subarray, so the answer is at least zero.

## Requirements and Behavior

The node stores `sum`, `pref`, `suff`, `max_sub`, and `size`. Empty
subarrays are allowed, so `max_sub` is at least zero even when every element is
negative. A present optional update assigns a constant; `std::nullopt` is a no-op.

## Interface and Complexity

```cpp
using value_type = RangeUpdateRangeMaxSubarrayNode<T>;
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
#include "acted_monoid/range_update_range_max_subarray.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeUpdateRangeMaxSubarray<long long>;
    m1une::ds::LazySegtree<AM> seg(std::vector<long long>{-2, 3, -1, 4});
    assert(seg.prod(0, 4).max_sub == 6);
    seg.apply(1, 3, -5);  // Values become -2, -5, -5, 4.
    assert(seg.prod(0, 4).max_sub == 4);
    assert(seg.prod(0, 3).max_sub == 0);  // Choose the empty subarray.
}
```
