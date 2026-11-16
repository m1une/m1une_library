---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/binary_inversion.hpp
    title: Binary Inversion Monoid
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
  bundledCode: "#line 1 \"acted_monoid/range_flip_range_binary_inversion.hpp\"\n\n\
    \n\n#line 1 \"monoid/binary_inversion.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\ntemplate <typename T = long long>\nstruct BinaryInversionNode {\n\
    \    long long zeros;\n    long long ones;\n    T inversions;\n};\n\n// Monoid\
    \ for counting zeros, ones, and inversions (1s before 0s) in a binary array.\n\
    template <typename T = long long>\nstruct BinaryInversion {\n    using value_type\
    \ = BinaryInversionNode<T>;\n    static constexpr bool commutative = false;\n\n\
    \    // The identity element has 0 zeros, 0 ones, and 0 inversions.\n    static\
    \ constexpr value_type id() {\n        return {0, 0, 0};\n    }\n\n    // Merges\
    \ two segments and calculates the new inversions.\n    // New inversions = left\
    \ inversions + right inversions + (ones in left * zeros in right)\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.zeros + b.zeros, a.ones + b.ones, a.inversions + b.inversions + a.ones\
    \ * b.zeros};\n    }\n\n    // Helper to securely create a leaf node from a value\
    \ (0 or 1).\n    static constexpr value_type make(int val) {\n        if (val\
    \ == 0) return {1, 0, 0};\n        return {0, 1, 0};\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n#line 5 \"acted_monoid/range_flip_range_binary_inversion.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T = long\
    \ long>\nstruct RangeFlipRangeBinaryInversion {\n    using value_type = m1une::monoid::BinaryInversionNode<T>;\n\
    \    using operator_type = bool;\n    static constexpr bool commutative = false;\n\
    \    static constexpr bool operator_commutative = true;\n\n    static constexpr\
    \ value_type id() {\n        return {0, 0, 0};\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.zeros + b.zeros,\
    \ a.ones + b.ones, a.inversions + b.inversions + a.ones * b.zeros};\n    }\n\n\
    \    static constexpr operator_type op_id() {\n        return false;\n    }\n\
    \    static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f ^ g;\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (!f) return x;\n      \
    \  return {x.ones, x.zeros, x.zeros * x.ones - x.inversions};\n    }\n\n    static\
    \ constexpr value_type make(int val) {\n        if (val == 0) return {1, 0, 0};\n\
    \        return {0, 1, 0};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP\n#define\
    \ M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP 1\n\n#include \"../monoid/binary_inversion.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T = long\
    \ long>\nstruct RangeFlipRangeBinaryInversion {\n    using value_type = m1une::monoid::BinaryInversionNode<T>;\n\
    \    using operator_type = bool;\n    static constexpr bool commutative = false;\n\
    \    static constexpr bool operator_commutative = true;\n\n    static constexpr\
    \ value_type id() {\n        return {0, 0, 0};\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.zeros + b.zeros,\
    \ a.ones + b.ones, a.inversions + b.inversions + a.ones * b.zeros};\n    }\n\n\
    \    static constexpr operator_type op_id() {\n        return false;\n    }\n\
    \    static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f ^ g;\n    }\n\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        if (!f) return x;\n      \
    \  return {x.ones, x.zeros, x.zeros * x.ones - x.inversions};\n    }\n\n    static\
    \ constexpr value_type make(int val) {\n        if (val == 0) return {1, 0, 0};\n\
    \        return {0, 1, 0};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_FLIP_RANGE_BINARY_INVERSION_HPP\n"
  dependsOn:
  - monoid/binary_inversion.hpp
  isVerificationFile: false
  path: acted_monoid/range_flip_range_binary_inversion.hpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_flip_range_binary_inversion.hpp
layout: document
title: Range Flip Range Binary Inversion
---

## Overview

An Acted Monoid designed for binary arrays (01-strings) to support range bit-flipping operations (inverting $0 \leftrightarrow 1$) and range binary inversion queries (the number of pairs $(i, j)$ such that $i < j$ and $A[i] = 1, A[j] = 0$).

This acted monoid leverages the structure of `m1une::monoid::BinaryInversionNode`. When a range is flipped, the counts of zeros and ones are swapped. Concurrently, the new number of inversions is computed as the total number of possible pairs minus the old number of inversions:
$$\text{new\_inversions} = (\text{zeros} \times \text{ones}) - \text{old\_inversions}$$

## Template Parameters

* `T`: The underlying scalar integer type used to store counts and inversion numbers (e.g., `long long`).

## Data Structure

* `using value_type = m1une::monoid::BinaryInversionNode<T>;`
  The state tracked in each segment tree node:
  * `zeros`: The number of `0`s in the segment.
  * `ones`: The number of `1`s in the segment.
  * `inversions`: The number of pairs where `1` appears before `0`.
* `using operator_type = bool;`
  A boolean flag representing whether the segment needs to be flipped (`true`) or not (`false`).

## Element Creation

When initializing the lazy segment tree, you must transform the raw binary values (`0` or `1`) into valid monoid nodes.
Use `make(val)` to build a leaf with the correct zero/one counts.

### `static constexpr value_type make(int val)`

* **Parameters:**
  * `val`: The binary element value (`0` or `1`).
* **Returns:** A `BinaryInversionNode` properly initialized for a single element.

## Interface and Complexity

```cpp
using value_type = m1une::monoid::BinaryInversionNode<T>;
using operator_type = bool;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Composes updates: apply `g` first, then `f`. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Returns the aggregate after applying `f`; does not modify `x`. | $O(1)$ |
| `static constexpr value_type make(int val)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/lazy_segtree.hpp"
#include "acted_monoid/range_flip_range_binary_inversion.hpp"
#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeFlipRangeBinaryInversion<long long>;

int main() {
    // Initial binary array: [1, 0, 1, 0, 0]
    std::vector<int> A = {1, 0, 1, 0, 0};
    int N = A.size();

    std::vector<AM::value_type> init_nodes(N);
    for (int i = 0; i < N; ++i) {
        init_nodes[i] = AM::make(A[i]);
    }

    m1une::ds::LazySegtree<AM> seg(init_nodes);

    // 1. Query entire array inversion count
    // Initial inversions: 5 (index pairs: (0,1), (0,3), (0,4), (2,3), (2,4))
    std::cout << "Initial Inversions: " << seg.all_prod().inversions << "\n"; // Output: 5

    // 2. Range Flip: Invert bits in range [1, 4) -> indices 1, 2, 3
    // A becomes: [1, 1, 0, 1, 0]
    seg.apply(1, 4, true);

    // 3. Query after inversion
    // New inversions: 5 (index pairs: (0,2), (0,4), (1,2), (1,4), (3,4))
    auto res = seg.prod(0, N);
    std::cout << "Zeros: " << res.zeros << ", Ones: " << res.ones << "\n"; // Output: Zeros: 2, Ones: 3
    std::cout << "Updated Inversions: " << res.inversions << "\n";         // Output: 5

    return 0;
}
```
