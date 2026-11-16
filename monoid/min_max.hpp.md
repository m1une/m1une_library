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
  bundledCode: "#line 1 \"monoid/min_max.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <limits>\n#include <utility>\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Monoid for finding both the minimum and maximum values in a range simultaneously.\n\
    template <typename T, T MinId = std::numeric_limits<T>::max(), T MaxId = std::numeric_limits<T>::lowest()>\n\
    struct MinMax {\n    using value_type = std::pair<T, T>;\n    static constexpr\
    \ bool commutative = true;\n\n    // The identity element contains the bounds\
    \ for min and max.\n    static constexpr value_type id() {\n        return {MinId,\
    \ MaxId};\n    }\n\n    // Merges two elements, extracting the overall min and\
    \ max.\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {std::min(a.first, b.first), std::max(a.second, b.second)};\n\
    \    }\n\n    // Helper to securely create a leaf node from a single value.\n\
    \    static constexpr value_type make(const T& val) {\n        return {val, val};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_MIN_MAX_HPP\n#define M1UNE_MONOID_MIN_MAX_HPP 1\n\n\
    #include <algorithm>\n#include <limits>\n#include <utility>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for finding both the minimum and maximum\
    \ values in a range simultaneously.\ntemplate <typename T, T MinId = std::numeric_limits<T>::max(),\
    \ T MaxId = std::numeric_limits<T>::lowest()>\nstruct MinMax {\n    using value_type\
    \ = std::pair<T, T>;\n    static constexpr bool commutative = true;\n\n    //\
    \ The identity element contains the bounds for min and max.\n    static constexpr\
    \ value_type id() {\n        return {MinId, MaxId};\n    }\n\n    // Merges two\
    \ elements, extracting the overall min and max.\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {std::min(a.first,\
    \ b.first), std::max(a.second, b.second)};\n    }\n\n    // Helper to securely\
    \ create a leaf node from a single value.\n    static constexpr value_type make(const\
    \ T& val) {\n        return {val, val};\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MONOID_MIN_MAX_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/min_max.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: monoid/min_max.hpp
layout: document
title: MinMax Monoid
---

## Overview

A monoid for retrieving both the minimum and maximum values of a contiguous subarray in a single query. The underlying `value_type` is `std::pair<T, T>`, where `first` is the minimum value and `second` is the maximum value.

## Initialization

Use the `make(val)` method to construct a leaf node from a single scalar value.

## Requirements

`T` must support ordered comparison. `MinId` must be at least as large as
all valid values and `MaxId` at most as small. The result pair contains the
minimum in `.first` and maximum in `.second`; `make(v)` returns `{v, v}`.

## Interface and Complexity

```cpp
using value_type = std::pair<T, T>;
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
#include "monoid/min_max.hpp"
#include <iostream>
#include <vector>

using MinMaxM = m1une::monoid::MinMax<long long>;

int main() {
    std::vector<long long> A = {8, 2, 5, 3, 9, 1};
    int N = A.size();

    std::vector<MinMaxM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = MinMaxM::make(A[i]);
    }

    m1une::ds::Segtree<MinMaxM> seg(init_data);

    // Query the range [1, 4) -> {2, 5, 3}
    auto [min_val, max_val] = seg.prod(1, 4);

    std::cout << "Min: " << min_val << ", Max: " << max_val << "\n"; // Output: Min: 2, Max: 5

    return 0;
}
```
