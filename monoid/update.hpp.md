---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
    title: verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/update.hpp\"\n\n\n\n#include <optional>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for range updates/assignments.\n//\
    \ Uses std::optional to represent the presence of an assignment.\ntemplate <typename\
    \ T>\nstruct Update {\n    using value_type = std::optional<T>;\n    static constexpr\
    \ bool commutative = false;\n\n    // The identity element represents \"no operation\"\
    .\n    static constexpr value_type id() {\n        return std::nullopt;\n    }\n\
    \n    // Composes two updates. The newer operation 'a' overwrites the older 'b'.\n\
    \    // If 'a' does not exist, it falls back to 'b'.\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return a.has_value()\
    \ ? a : b;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_UPDATE_HPP\n#define M1UNE_MONOID_UPDATE_HPP 1\n\n#include\
    \ <optional>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for range updates/assignments.\n\
    // Uses std::optional to represent the presence of an assignment.\ntemplate <typename\
    \ T>\nstruct Update {\n    using value_type = std::optional<T>;\n    static constexpr\
    \ bool commutative = false;\n\n    // The identity element represents \"no operation\"\
    .\n    static constexpr value_type id() {\n        return std::nullopt;\n    }\n\
    \n    // Composes two updates. The newer operation 'a' overwrites the older 'b'.\n\
    \    // If 'a' does not exist, it falls back to 'b'.\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return a.has_value()\
    \ ? a : b;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MONOID_UPDATE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/update.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/persistent_dynamic_dual_segtree.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/update.hpp
layout: document
title: Update Monoid
---

## Overview

A monoid for range updates/assignments. It uses `std::optional<T>` to safely represent whether an assignment operation exists or not (the identity element is `std::nullopt`).

When two operations are composed, the newer operation (on the left, when applied) completely overwrites the older operation (on the right), unless the newer operation is empty.

## Template Parameters

* `T`: The underlying data type being assigned.

## Interface and Complexity

```cpp
using value_type = std::optional<T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns `std::nullopt`. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Returns `a` if present, otherwise `b`; the left assignment wins. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/update.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Update<int>;
    assert(M::op(7, 3).value() == 7);
    assert(M::op(M::id(), 3).value() == 3);
}
```
