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
  bundledCode: "#line 1 \"monoid/and.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for bitwise AND (Range AND).\n// ~T(0) sets all bits to 1, acting\
    \ as the identity for bitwise AND.\ntemplate <typename T>\nstruct And {\n    using\
    \ value_type = T;\n    static constexpr bool commutative = true;\n\n    // The\
    \ identity element for bitwise AND is all bits set to 1.\n    static constexpr\
    \ T id() { return ~T(0); }\n\n    // Returns the bitwise AND of a and b.\n   \
    \ static constexpr T op(const T& a, const T& b) { return a & b; }\n};\n\n}  //\
    \ namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_AND_HPP\n#define M1UNE_MONOID_AND_HPP 1\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for bitwise AND (Range AND).\n// ~T(0)\
    \ sets all bits to 1, acting as the identity for bitwise AND.\ntemplate <typename\
    \ T>\nstruct And {\n    using value_type = T;\n    static constexpr bool commutative\
    \ = true;\n\n    // The identity element for bitwise AND is all bits set to 1.\n\
    \    static constexpr T id() { return ~T(0); }\n\n    // Returns the bitwise AND\
    \ of a and b.\n    static constexpr T op(const T& a, const T& b) { return a &\
    \ b; }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_AND_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/and.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/and.hpp
layout: document
title: Bitwise AND Monoid
---

## Overview

A monoid representing the bitwise AND operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise AND ($a \ \& \ b$)
* **Identity Element**: `~T(0)` (All bits set to 1)

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `~T(0)` (all bits set). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the bitwise AND. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/and.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::And<unsigned int>;
    assert(M::op(6, 3) == 2);
}
```
