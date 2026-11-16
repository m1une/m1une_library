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
  bundledCode: "#line 1 \"monoid/gcd.hpp\"\n\n\n\n#include <numeric>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for Greatest Common Divisor (Range\
    \ GCD).\ntemplate <typename T>\nstruct Gcd {\n    using value_type = T;\n    static\
    \ constexpr bool commutative = true;\n\n    // The identity element for GCD is\
    \ 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    // Returns\
    \ the greatest common divisor of a and b.\n    static constexpr T op(const T&\
    \ a, const T& b) {\n        return std::gcd(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_GCD_HPP\n#define M1UNE_MONOID_GCD_HPP 1\n\n#include\
    \ <numeric>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for Greatest\
    \ Common Divisor (Range GCD).\ntemplate <typename T>\nstruct Gcd {\n    using\
    \ value_type = T;\n    static constexpr bool commutative = true;\n\n    // The\
    \ identity element for GCD is 0.\n    static constexpr T id() {\n        return\
    \ T(0);\n    }\n\n    // Returns the greatest common divisor of a and b.\n   \
    \ static constexpr T op(const T& a, const T& b) {\n        return std::gcd(a,\
    \ b);\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_MONOID_GCD_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/gcd.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/gcd.hpp
layout: document
title: GCD Monoid
---

## Overview

A monoid representing the Greatest Common Divisor (GCD) operation. This is an idempotent monoid, meaning it can be safely used with a Sparse Table for range GCD queries using one GCD operation. The GCD operation itself takes $O(\log(V + 1))$ time for values of magnitude at most $V$.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: `std::gcd(a, b)`
* **Identity Element**: $0$ (Since $\gcd(x, 0) = x$)

## Interface and Complexity

```cpp
using value_type = T;
```

Let $V$ bound the absolute input values. Their absolute values must be representable by `T`, as required by `std::gcd`.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns zero. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns `std::gcd(a, b)`. | $O(\log(V + 1))$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/gcd.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Gcd<int>;
    assert(M::op(12, 18) == 6);
}
```
