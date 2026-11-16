---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_arg_min.hpp
    title: Range Add Range ArgMin
  - icon: ':heavy_check_mark:'
    path: monoid/arg_max.hpp
    title: ArgMax Monoid
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/arg_min.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <limits>\n\nnamespace m1une {\nnamespace monoid {\n\ntemplate <typename T>\n\
    struct ArgMinNode {\n    T value;\n    long long size;\n    long long ord;\n};\n\
    \n// Monoid for finding the optimal value (minimum by default) and its relative\
    \ order.\n// Ties are broken by choosing the earlier element.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max(), typename Compare = std::less<T>>\n\
    struct ArgMin {\n    using value_type = ArgMinNode<T>;\n    static constexpr bool\
    \ commutative = false;\n\n    static constexpr value_type id() {\n        return\
    \ {Id, 0, -1};\n    }\n\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        if (a.size == 0) return b;\n        if (b.size\
    \ == 0) return a;\n        long long size = a.size + b.size;\n        if (Compare()(a.value,\
    \ b.value)) return {a.value, size, a.ord};\n        if (Compare()(b.value, a.value))\
    \ return {b.value, size, b.ord + a.size};\n        return {a.value, size, a.ord};\n\
    \    }\n\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1, 0};\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_MONOID_ARG_MIN_HPP\n#define M1UNE_MONOID_ARG_MIN_HPP 1\n\n\
    #include <functional>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\ntemplate <typename T>\nstruct ArgMinNode {\n    T value;\n    long long\
    \ size;\n    long long ord;\n};\n\n// Monoid for finding the optimal value (minimum\
    \ by default) and its relative order.\n// Ties are broken by choosing the earlier\
    \ element.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(), typename\
    \ Compare = std::less<T>>\nstruct ArgMin {\n    using value_type = ArgMinNode<T>;\n\
    \    static constexpr bool commutative = false;\n\n    static constexpr value_type\
    \ id() {\n        return {Id, 0, -1};\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        if (a.size == 0) return\
    \ b;\n        if (b.size == 0) return a;\n        long long size = a.size + b.size;\n\
    \        if (Compare()(a.value, b.value)) return {a.value, size, a.ord};\n   \
    \     if (Compare()(b.value, a.value)) return {b.value, size, b.ord + a.size};\n\
    \        return {a.value, size, a.ord};\n    }\n\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val, 1, 0};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_ARG_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/arg_min.hpp
  requiredBy:
  - acted_monoid/range_add_range_arg_min.hpp
  - monoid/arg_max.hpp
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
  - verify/monoid/commutative_flags.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/arg_min.hpp
layout: document
title: ArgMin Monoid
---

## Overview

A monoid for finding both the minimum value and its relative order in a range. If there are multiple minimum values, it returns the earliest one.

For the maximum counterpart, see `monoid/arg_max.hpp`.

## Requirements and Behavior

`value_type` stores `T value`, `long long size`, and `long long ord`.
`ord` is relative to the aggregate: for `prod(l, r)`, the array position is
`l + ord`. Ties choose the earliest position; the empty identity has `size == 0`
and `ord == -1`. `Compare` must be a strict weak ordering.

## Interface and Complexity

```cpp
using value_type = ArgMinNode<T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(const T& val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/arg_min.hpp"
#include <iostream>
#include <vector>

using ArgMinM = m1une::monoid::ArgMin<long long>;

int main() {
    std::vector<long long> A = {4, 2, 5, 2, 8};
    m1une::ds::Segtree<ArgMinM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Min Value: " << res.value << "\n"; // Output: 2
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
