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
  bundledCode: "#line 1 \"monoid/max.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Monoid for maximum (Range Maximum).\n\
    // The identity element defaults to the lowest possible value of type T, but can\
    \ be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::lowest()>\n\
    struct Max {\n    using value_type = T;\n    static constexpr bool commutative\
    \ = true;\n\n    // Returns the identity element for maximum.\n    static constexpr\
    \ T id() {\n        return Id;\n    }\n\n    // Returns the maximum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return std::max(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MAX_HPP\n#define M1UNE_MONOID_MAX_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for maximum (Range Maximum).\n// The identity element defaults to the\
    \ lowest possible value of type T, but can be overridden.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::lowest()>\nstruct Max {\n    using value_type\
    \ = T;\n    static constexpr bool commutative = true;\n\n    // Returns the identity\
    \ element for maximum.\n    static constexpr T id() {\n        return Id;\n  \
    \  }\n\n    // Returns the maximum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return std::max(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/max.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/max.hpp
layout: document
title: Max Monoid
---

## Overview

A monoid representing the Maximum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Maximum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::lowest()`.

## Properties

* **Operation**: `std::max(a, b)`
* **Identity Element**: `Id`

## Requirements

`T` must support ordered comparison. A custom `Id` must be at most as small as
every valid value. Floating-point values must have a consistent ordering;
exclude NaNs.

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `Id` (the lowest representable `T` by default). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the larger value. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/max.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Max<int>;
    assert(M::op(3, 4) == 4);
}
```
