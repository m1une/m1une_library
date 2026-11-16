---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/range_add_range_min.test.cpp
    title: verify/ds/segtree/range_add_range_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_add_range_min.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename\
    \ T, T Id = std::numeric_limits<T>::max()>\nstruct RangeAddRangeMin {\n    using\
    \ value_type = T;\n    using operator_type = T;\n    static constexpr bool commutative\
    \ = true;\n    static constexpr bool operator_commutative = true;\n\n    // Value\
    \ Monoid (Min)\n    static constexpr value_type id() {\n        return Id;\n \
    \   }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return std::min(a, b);\n    }\n\n    // Operator Monoid (Add)\n\
    \    static constexpr operator_type op_id() {\n        return 0;\n    }\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    // Mapping\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        if (x == id())\
    \ return x;  // Do not apply the operator to the identity element\n        return\
    \ x + f;\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\n#define M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\
    \ 1\n\n#include <algorithm>\n#include <limits>\n\nnamespace m1une {\nnamespace\
    \ acted_monoid {\n\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct RangeAddRangeMin {\n    using value_type = T;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = true;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    // Value Monoid (Min)\n    static constexpr\
    \ value_type id() {\n        return Id;\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return std::min(a, b);\n\
    \    }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return 0;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (x == id()) return x;  // Do not apply\
    \ the operator to the identity element\n        return x + f;\n    }\n};\n\n}\
    \  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_ADD_RANGE_MIN_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_add_range_min.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/range_add_range_min.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_add_range_min.hpp
layout: document
title: Range Add Range Min
---

## Overview

An Acted Monoid representing Range Addition operations and Range Minimum queries. It safely handles the identity element to prevent wrapping or incorrect modifications on uninitialized values.

## Template Parameters

* `T`: The underlying scalar data type (e.g., `long long`, `int`).
* `Id`: The identity element for the value monoid. Defaults to `std::numeric_limits<T>::max()`.

## Requirements and Behavior

`Id` is reserved for empty or uninitialized values: `mapping` leaves it
unchanged. Do not use it as a real element value, and ensure updates do not
produce it. All arithmetic must remain representable by `T`.

## Interface and Complexity

```cpp
using value_type = T;
using operator_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_add_range_min.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeAddRangeMin<long long>;

int main() {
    std::vector<long long> A = {10, 20, 30, 40, 50};
    m1une::ds::LazySegtree<AM> seg(A);

    // Add -15 to all elements in range [1, 4) -> {10, 5, 15, 25, 50}
    seg.apply(1, 4, -15);

    // Get the minimum in range [0, 3) -> min(10, 5, 15) = 5
    std::cout << seg.prod(0, 3) << "\n";

    return 0;
}
```
