---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/arg_min.hpp
    title: ArgMin Monoid
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
  bundledCode: "#line 1 \"monoid/arg_max.hpp\"\n\n\n\n#include <functional>\n#include\
    \ <limits>\n\n#line 1 \"monoid/arg_min.hpp\"\n\n\n\n#line 6 \"monoid/arg_min.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\ntemplate <typename T>\nstruct ArgMinNode\
    \ {\n    T value;\n    long long size;\n    long long ord;\n};\n\n// Monoid for\
    \ finding the optimal value (minimum by default) and its relative order.\n// Ties\
    \ are broken by choosing the earlier element.\ntemplate <typename T, T Id = std::numeric_limits<T>::max(),\
    \ typename Compare = std::less<T>>\nstruct ArgMin {\n    using value_type = ArgMinNode<T>;\n\
    \    static constexpr bool commutative = false;\n\n    static constexpr value_type\
    \ id() {\n        return {Id, 0, -1};\n    }\n\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        if (a.size == 0) return\
    \ b;\n        if (b.size == 0) return a;\n        long long size = a.size + b.size;\n\
    \        if (Compare()(a.value, b.value)) return {a.value, size, a.ord};\n   \
    \     if (Compare()(b.value, a.value)) return {b.value, size, b.ord + a.size};\n\
    \        return {a.value, size, a.ord};\n    }\n\n    static constexpr value_type\
    \ make(const T& val) {\n        return {val, 1, 0};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n#line 8 \"monoid/arg_max.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for finding the maximum value and its\
    \ corresponding index.\n// Defined as a type alias of ArgMin using std::greater.\n\
    template <typename T, T Id = std::numeric_limits<T>::lowest()>\nusing ArgMax =\
    \ ArgMin<T, Id, std::greater<T>>;\n\n}  // namespace monoid\n}  // namespace m1une\n\
    \n\n"
  code: '#ifndef M1UNE_MONOID_ARG_MAX_HPP

    #define M1UNE_MONOID_ARG_MAX_HPP 1


    #include <functional>

    #include <limits>


    #include "arg_min.hpp"


    namespace m1une {

    namespace monoid {


    // Monoid for finding the maximum value and its corresponding index.

    // Defined as a type alias of ArgMin using std::greater.

    template <typename T, T Id = std::numeric_limits<T>::lowest()>

    using ArgMax = ArgMin<T, Id, std::greater<T>>;


    }  // namespace monoid

    }  // namespace m1une


    #endif  // M1UNE_MONOID_ARG_MAX_HPP

    '
  dependsOn:
  - monoid/arg_min.hpp
  isVerificationFile: false
  path: monoid/arg_max.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/arg_max.hpp
layout: document
title: ArgMax Monoid
---

## Overview

A monoid for finding both the maximum value and its relative order in a range. If there are multiple maximum values, it returns the earliest one.

This is defined as a type alias of `ArgMin` using `std::greater`. For the minimum counterpart, see `monoid/arg_min.hpp`.

## Requirements and Behavior

`value_type` is `ArgMinNode<T>` with fields `value`, `size`, and `ord`
(the field is named `value` even for maxima). `ord` is relative to the queried
range; add its left endpoint to obtain the array index. Ties choose the earliest
position. The empty identity has `size == 0` and `ord == -1`.

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
#include "monoid/arg_max.hpp"
#include <iostream>
#include <vector>

using ArgMaxM = m1une::monoid::ArgMax<long long>;

int main() {
    std::vector<long long> A = {4, 8, 5, 8, 2};
    m1une::ds::Segtree<ArgMaxM> seg(A);

    auto res = seg.prod(0, A.size());

    std::cout << "Max Value: " << res.value << "\n"; // Output: 8
    std::cout << "Order: " << res.ord << "\n";       // Output: 1 (Order 1 is chosen over order 3)

    return 0;
}
```
