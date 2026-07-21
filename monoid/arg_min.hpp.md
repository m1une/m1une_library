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
  - monoid/arg_max.hpp
  - acted_monoid/range_add_range_arg_min.hpp
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

## Interface and Complexity

This is a stateless algebra tag. Generic data structures use its public
`value_type`, `id()`, and `op(a, b)` members. If the type also provides helpers
such as `make(...)` or `inv(x)`, they are described above or in the documented
properties.

Each static operation runs in the cost of the underlying operation shown in the
properties. Scalar monoids are $O(1)$; monoids whose `value_type` stores several
items, permutations, or matrices scale with that stored size.
