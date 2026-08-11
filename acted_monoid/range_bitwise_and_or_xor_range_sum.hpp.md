---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
    title: verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_bitwise_and_or_xor_range_sum.hpp\"\n\n\
    \n\n#include <array>\n#include <limits>\n#include <type_traits>\n\nnamespace m1une\
    \ {\nnamespace acted_monoid {\n\ntemplate <typename T, int BITS>\nstruct RangeBitwiseAndOrXorRangeSumNode\
    \ {\n    T sum;\n    std::array<long long, BITS> bit_count;\n    long long size;\n\
    };\n\n// Acted monoid for range bitwise AND, OR, and XOR updates and range sum\
    \ queries.\ntemplate <typename T, int BITS = 30>\nstruct RangeBitwiseAndOrXorRangeSum\
    \ {\n    static_assert(std::is_integral_v<T> && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>);\n    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);\n\
    \n    using value_type = RangeBitwiseAndOrXorRangeSumNode<T, BITS>;\n\n    //\
    \ Represents f(x) = (x & and_mask) ^ xor_mask on the lowest BITS bits.\n    struct\
    \ operator_type {\n        T and_mask;\n        T xor_mask;\n    };\n\n    static\
    \ constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = false;\n\n    static constexpr T bit_mask() {\n        if constexpr (std::is_unsigned_v<T>\
    \ && BITS == std::numeric_limits<T>::digits) {\n            return ~T(0);\n  \
    \      } else {\n            return (T(1) << (BITS - 1)) | ((T(1) << (BITS - 1))\
    \ - 1);\n        }\n    }\n\n    static constexpr value_type id() {\n        value_type\
    \ res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n        res.size\
    \ = 0;\n        return res;\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        value_type res;\n        res.sum\
    \ = a.sum + b.sum;\n        res.size = a.size + b.size;\n        for (int i =\
    \ 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i] + b.bit_count[i];\n\
    \        }\n        return res;\n    }\n\n    static constexpr operator_type op_id()\
    \ {\n        return {bit_mask(), T(0)};\n    }\n\n    // Returns f(g(x)).\n  \
    \  static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return {f.and_mask & g.and_mask, (g.xor_mask & f.and_mask) ^ f.xor_mask};\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x) {\n        value_type res = x;\n        res.sum = T(0);\n   \
    \     for (int i = 0; i < BITS; ++i) {\n            long long count = ((f.and_mask\
    \ >> i) & T(1)) ? x.bit_count[i] : 0;\n            if ((f.xor_mask >> i) & T(1))\
    \ count = x.size - count;\n            res.bit_count[i] = count;\n           \
    \ res.sum += static_cast<T>(count) * (T(1) << i);\n        }\n        return res;\n\
    \    }\n\n    static constexpr value_type make(const T& value) {\n        value_type\
    \ res;\n        res.sum = value;\n        res.size = 1;\n        for (int i =\
    \ 0; i < BITS; ++i) {\n            res.bit_count[i] = (value >> i) & T(1);\n \
    \       }\n        return res;\n    }\n\n    static constexpr operator_type make_and(const\
    \ T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\n    static constexpr\
    \ operator_type make_or(const T& mask) {\n        T normalized = mask & bit_mask();\n\
    \        return {bit_mask() ^ normalized, normalized};\n    }\n\n    static constexpr\
    \ operator_type make_xor(const T& mask) {\n        return {bit_mask(), mask &\
    \ bit_mask()};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP\n#define\
    \ M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP 1\n\n#include <array>\n\
    #include <limits>\n#include <type_traits>\n\nnamespace m1une {\nnamespace acted_monoid\
    \ {\n\ntemplate <typename T, int BITS>\nstruct RangeBitwiseAndOrXorRangeSumNode\
    \ {\n    T sum;\n    std::array<long long, BITS> bit_count;\n    long long size;\n\
    };\n\n// Acted monoid for range bitwise AND, OR, and XOR updates and range sum\
    \ queries.\ntemplate <typename T, int BITS = 30>\nstruct RangeBitwiseAndOrXorRangeSum\
    \ {\n    static_assert(std::is_integral_v<T> && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>);\n    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);\n\
    \n    using value_type = RangeBitwiseAndOrXorRangeSumNode<T, BITS>;\n\n    //\
    \ Represents f(x) = (x & and_mask) ^ xor_mask on the lowest BITS bits.\n    struct\
    \ operator_type {\n        T and_mask;\n        T xor_mask;\n    };\n\n    static\
    \ constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = false;\n\n    static constexpr T bit_mask() {\n        if constexpr (std::is_unsigned_v<T>\
    \ && BITS == std::numeric_limits<T>::digits) {\n            return ~T(0);\n  \
    \      } else {\n            return (T(1) << (BITS - 1)) | ((T(1) << (BITS - 1))\
    \ - 1);\n        }\n    }\n\n    static constexpr value_type id() {\n        value_type\
    \ res;\n        res.sum = T(0);\n        res.bit_count.fill(0);\n        res.size\
    \ = 0;\n        return res;\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        value_type res;\n        res.sum\
    \ = a.sum + b.sum;\n        res.size = a.size + b.size;\n        for (int i =\
    \ 0; i < BITS; ++i) {\n            res.bit_count[i] = a.bit_count[i] + b.bit_count[i];\n\
    \        }\n        return res;\n    }\n\n    static constexpr operator_type op_id()\
    \ {\n        return {bit_mask(), T(0)};\n    }\n\n    // Returns f(g(x)).\n  \
    \  static constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return {f.and_mask & g.and_mask, (g.xor_mask & f.and_mask) ^ f.xor_mask};\n\
    \    }\n\n    static constexpr value_type mapping(const operator_type& f, const\
    \ value_type& x) {\n        value_type res = x;\n        res.sum = T(0);\n   \
    \     for (int i = 0; i < BITS; ++i) {\n            long long count = ((f.and_mask\
    \ >> i) & T(1)) ? x.bit_count[i] : 0;\n            if ((f.xor_mask >> i) & T(1))\
    \ count = x.size - count;\n            res.bit_count[i] = count;\n           \
    \ res.sum += static_cast<T>(count) * (T(1) << i);\n        }\n        return res;\n\
    \    }\n\n    static constexpr value_type make(const T& value) {\n        value_type\
    \ res;\n        res.sum = value;\n        res.size = 1;\n        for (int i =\
    \ 0; i < BITS; ++i) {\n            res.bit_count[i] = (value >> i) & T(1);\n \
    \       }\n        return res;\n    }\n\n    static constexpr operator_type make_and(const\
    \ T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\n    static constexpr\
    \ operator_type make_or(const T& mask) {\n        T normalized = mask & bit_mask();\n\
    \        return {bit_mask() ^ normalized, normalized};\n    }\n\n    static constexpr\
    \ operator_type make_xor(const T& mask) {\n        return {bit_mask(), mask &\
    \ bit_mask()};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n#endif  // M1UNE_ACTED_MONOID_RANGE_BITWISE_AND_OR_XOR_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
  requiredBy: []
  timestamp: '2026-08-12 00:05:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/acted_monoid/range_bitwise_and_or_xor_range_sum.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: acted_monoid/range_bitwise_and_or_xor_range_sum.hpp
layout: document
title: Range Bitwise AND/OR/XOR Range Sum
---

## Overview

`RangeBitwiseAndOrXorRangeSum<T, BITS>` is an acted monoid for range bitwise
AND, OR, and XOR updates and range sum queries. It is intended for lazy data
structures such as `LazySegtree`.

Each value node stores the segment sum, size, and set-bit count at every tracked
bit. A lazy operator represents

$$
f(x) = (x \mathbin{\&} a) \mathbin{\hat{}} b.
$$

This form represents AND, OR, XOR, and every composition of those operations.
The order of lazy operators matters.

`value_type` has members `T sum`, `std::array<long long, BITS> bit_count`, and
`long long size`. `operator_type` has members `T and_mask` and `T xor_mask`.
Prefer the three update factories below instead of constructing an operator
directly.

## Template Parameters

* `T`: A non-boolean integral type used for values, masks, and sums. Values must
  be nonnegative and fit in the lowest `BITS` bits. The sum must fit in `T`.
* `BITS`: Number of low bits to track. It defaults to `30` and must not exceed
  `std::numeric_limits<T>::digits`. For values below $2^{60}$, use
  `RangeBitwiseAndOrXorRangeSum<long long, 60>`.

## Interface and Complexity

Let $B = \mathtt{BITS}$.

| Member | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the empty value-monoid identity. | $O(B)$ |
| `static constexpr value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(B)$ |
| `static constexpr T bit_mask()` | Returns a mask whose lowest `BITS` bits are set. | $O(1)$ |
| `static constexpr operator_type op_id()` | Returns the identity lazy operator. | $O(1)$ |
| `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns the composition $f \circ g$. | $O(1)$ |
| `static constexpr value_type mapping(const operator_type& f, const value_type& x)` | Applies `f` to an aggregate. | $O(B)$ |
| `static constexpr value_type make(const T& value)` | Constructs a one-element aggregate. | $O(B)$ |
| `static constexpr operator_type make_and(const T& mask)` | Constructs the update $x \gets x \mathbin{\&} \mathtt{mask}$. | $O(1)$ |
| `static constexpr operator_type make_or(const T& mask)` | Constructs the update $x \gets x \mathbin{|} \mathtt{mask}$. | $O(1)$ |
| `static constexpr operator_type make_xor(const T& mask)` | Constructs the update $x \gets x \mathbin{\hat{}} \mathtt{mask}$. | $O(1)$ |

With `LazySegtree`, construction takes $O(NB)$, a range update takes
$O(B \log N)$, and a range-sum query takes $O(B \log N)$. Read the answer from
the returned node's `sum` member.

## Example

```cpp
#include "acted_monoid/range_bitwise_and_or_xor_range_sum.hpp"
#include "ds/segtree/lazy_segtree.hpp"

#include <iostream>
#include <vector>

using AM = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long long, 30>;

int main() {
    std::vector<long long> values = {1, 2, 3, 4};
    m1une::ds::LazySegtree<AM> seg(values);

    seg.apply(0, 3, AM::make_or(4));
    seg.apply(1, 4, AM::make_xor(1));
    seg.apply(0, 2, AM::make_and(6));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
