---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dual_segtree.test.cpp
    title: verify/ds/segtree/dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/dynamic_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/affine.hpp\"\n\n\n\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for affine transformations f(x) = ax\
    \ + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct Affine\
    \ {\n    using value_type = std::pair<T, T>;\n    static constexpr bool commutative\
    \ = false;\n\n    // The identity transformation is f(x) = 1*x + 0.\n    static\
    \ constexpr value_type id() {\n        return {T(1), T(0)};\n    }\n\n    // Composes\
    \ two affine transformations.\n    // f(g(x)) where f = a, g = b.\n    // a.first\
    \ * (b.first * x + b.second) + a.second\n    // = (a.first * b.first) * x + (a.first\
    \ * b.second + a.second)\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.first * b.first, a.first * b.second\
    \ + a.second};\n    }\n\n    // Helpers to create common affine transformations\n\
    \    static constexpr value_type make_add(const T& b) {\n        return {T(1),\
    \ b};\n    }\n    static constexpr value_type make_mul(const T& a) {\n       \
    \ return {a, T(0)};\n    }\n    static constexpr value_type make_assign(const\
    \ T& b) {\n        return {T(0), b};\n    }\n};\n\n}  // namespace monoid\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_AFFINE_HPP\n#define M1UNE_MONOID_AFFINE_HPP 1\n\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for affine transformations\
    \ f(x) = ax + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct\
    \ Affine {\n    using value_type = std::pair<T, T>;\n    static constexpr bool\
    \ commutative = false;\n\n    // The identity transformation is f(x) = 1*x + 0.\n\
    \    static constexpr value_type id() {\n        return {T(1), T(0)};\n    }\n\
    \n    // Composes two affine transformations.\n    // f(g(x)) where f = a, g =\
    \ b.\n    // a.first * (b.first * x + b.second) + a.second\n    // = (a.first\
    \ * b.first) * x + (a.first * b.second + a.second)\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.first * b.first,\
    \ a.first * b.second + a.second};\n    }\n\n    // Helpers to create common affine\
    \ transformations\n    static constexpr value_type make_add(const T& b) {\n  \
    \      return {T(1), b};\n    }\n    static constexpr value_type make_mul(const\
    \ T& a) {\n        return {a, T(0)};\n    }\n    static constexpr value_type make_assign(const\
    \ T& b) {\n        return {T(0), b};\n    }\n};\n\n}  // namespace monoid\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_MONOID_AFFINE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/affine.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/dynamic_dual_segtree.test.cpp
  - verify/ds/segtree/dual_segtree.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/affine.hpp
layout: document
title: Affine Monoid
---

## Overview

A monoid for composing affine transformations, expressed as $f(x) = ax + b$.
The underlying `value_type` is `std::pair<T, T>`, where `first` represents $a$ (the multiplier) and `second` represents $b$ (the addend).

`op(f, g)` returns $f \circ g$: apply `g` first, then `f`.
Consequently, a segment-tree product over maps `f[l], ..., f[r - 1]`
applies `f[r - 1]` first and `f[l]` last. This order is significant because
composition is not commutative. `T` must support zero, one, addition, and
multiplication with the usual distributive laws.

## Initialization

You can create operations directly using pairs, or use the provided helper functions for clarity:

* **Add $C$:** `make_add(C)` -> `{1, C}`
* **Multiply by $C$:** `make_mul(C)` -> `{C, 0}`
* **Assign $C$:** `make_assign(C)` -> `{0, C}`

## Interface and Complexity

```cpp
using value_type = std::pair<T, T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns `{1, 0}`, the identity function. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Returns `a(b(x))`; `b` is applied first. | $O(1)$ |
| `static constexpr value_type make_add(const T& b)` | Returns the affine map `x + b`. | $O(1)$ |
| `static constexpr value_type make_mul(const T& a)` | Returns the affine map `a * x`. | $O(1)$ |
| `static constexpr value_type make_assign(const T& b)` | Returns the constant affine map `b`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/affine.hpp"
#include <iostream>

using AffineM = m1une::monoid::Affine<long long>;

int main() {
    // Operations:
    // 0: f(x) = 2x + 3
    // 1: f(x) = 1x + 5 (Add 5)
    // 2: f(x) = 3x + 0 (Multiply by 3)

    std::vector<AffineM::value_type> ops = {
        {2, 3},
        AffineM::make_add(5),
        AffineM::make_mul(3)
    };

    m1une::ds::Segtree<AffineM> seg(ops);

    // Get the composite function for the range [0, 2)
    // f(x) = 2 * (x + 5) + 3 = 2x + 13
    auto [a, b] = seg.prod(0, 2);
    std::cout << "f(x) = " << a << "x + " << b << "\n"; // Output: 2x + 13

    return 0;
}
```
