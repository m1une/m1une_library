---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
    title: verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/dsu/potentialized_dsu.test.cpp
    title: verify/ds/dsu/potentialized_dsu.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/xor.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate <typename T>\nstruct Xor\
    \ {\n    using value_type = T;\n    static constexpr bool commutative = true;\n\
    \n    // Returns the identity element for bitwise XOR, which is 0.\n    static\
    \ constexpr T id() {\n        return T(0);\n    }\n\n    // Returns the bitwise\
    \ XOR of a and b.\n    static constexpr T op(const T& a, const T& b) {\n     \
    \   return a ^ b;\n    }\n\n    static constexpr T inv(const T& x) {\n       \
    \ return x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_XOR_HPP\n#define M1UNE_MONOID_XOR_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for bitwise XOR (Range XOR).\ntemplate\
    \ <typename T>\nstruct Xor {\n    using value_type = T;\n    static constexpr\
    \ bool commutative = true;\n\n    // Returns the identity element for bitwise\
    \ XOR, which is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\
    \n    // Returns the bitwise XOR of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a ^ b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_XOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/xor.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/dsu/persistent_potentialized_dsu.test.cpp
  - verify/ds/dsu/potentialized_dsu.test.cpp
  - verify/monoid/commutative_flags.test.cpp
  - verify/graph/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - verify/graph/tree/vertex_get_range_contour_add_on_tree.test.cpp
documentation_of: monoid/xor.hpp
layout: document
title: Bitwise XOR Monoid
---

## Overview

A monoid representing the bitwise XOR operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise XOR ($a \ \text{\textasciicircum} \ b$)
* **Identity Element**: $0$

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns zero. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the bitwise XOR. | $O(1)$ |
| `static constexpr T inv(const T& x)` | Returns the group inverse of `x`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/xor.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Xor<unsigned int>;
    assert(M::op(6, 3) == 5);
    assert(M::inv(6) == 6);
}
```
