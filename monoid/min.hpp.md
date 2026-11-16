---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sparse_table.test.cpp
    title: verify/ds/range_query/sparse_table.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/min.hpp\"\n\n\n\n#include <algorithm>\n#include <limits>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Monoid for minimum (Range Minimum).\n\
    // The identity element defaults to the maximum possible value of type T, but\
    \ can be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct Min {\n    using value_type = T;\n    static constexpr bool commutative\
    \ = true;\n\n    // Returns the identity element for minimum.\n    static constexpr\
    \ T id() {\n        return Id;\n    }\n\n    // Returns the minimum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return std::min(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_HPP\n#define M1UNE_MONOID_MIN_HPP 1\n\n#include\
    \ <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for minimum (Range Minimum).\n// The identity element defaults to the\
    \ maximum possible value of type T, but can be overridden.\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max()>\nstruct Min {\n    using value_type\
    \ = T;\n    static constexpr bool commutative = true;\n\n    // Returns the identity\
    \ element for minimum.\n    static constexpr T id() {\n        return Id;\n  \
    \  }\n\n    // Returns the minimum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return std::min(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sparse_table.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/min.hpp
layout: document
title: Min Monoid
---

## Overview

A monoid representing the Minimum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Minimum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::max()`.

## Properties

* **Operation**: `std::min(a, b)`
* **Identity Element**: `Id`

## Requirements

`T` must support ordered comparison. A custom `Id` must be at least as large as
every valid value. Floating-point values must have a consistent ordering;
exclude NaNs.

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `Id` (the largest representable `T` by default). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the smaller value. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/min.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Min<int>;
    assert(M::op(3, 4) == 3);
}
```
