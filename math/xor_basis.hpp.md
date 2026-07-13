---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/xor_basis.test.cpp
    title: verify/math/xor_basis.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/xor_basis.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <concepts>\n#include <initializer_list>\n#include <iterator>\n#include\
    \ <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <std::unsigned_integral UInt = unsigned long long>\nclass XorBasis {\n    static_assert(!std::same_as<UInt,\
    \ bool>);\n\npublic:\n    static constexpr int bit_width = std::numeric_limits<UInt>::digits;\n\
    \n    XorBasis() = default;\n\n    template <std::input_iterator Iterator, std::sentinel_for<Iterator>\
    \ Sentinel>\n        requires std::convertible_to<std::iter_reference_t<Iterator>,\
    \ UInt>\n    XorBasis(Iterator first, Sentinel last) {\n        for (; first !=\
    \ last; ++first) insert(UInt(*first));\n    }\n\n    XorBasis(std::initializer_list<UInt>\
    \ values)\n        : XorBasis(values.begin(), values.end()) {}\n\n    bool insert(UInt\
    \ value) {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n       \
    \     if (((value >> bit) & UInt(1)) == 0) continue;\n            if (basis_[bit]\
    \ != 0) {\n                value ^= basis_[bit];\n                continue;\n\
    \            }\n\n            for (int lower = bit - 1; lower >= 0; lower--) {\n\
    \                if (((value >> lower) & UInt(1)) != 0) value ^= basis_[lower];\n\
    \            }\n            basis_[bit] = value;\n            rank_++;\n     \
    \       for (int higher = bit + 1; higher < bit_width; higher++) {\n         \
    \       if (((basis_[higher] >> bit) & UInt(1)) != 0) {\n                    basis_[higher]\
    \ ^= value;\n                }\n            }\n            return true;\n    \
    \    }\n        return false;\n    }\n\n    bool contains(UInt value) const {\n\
    \        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if (((value\
    \ >> bit) & UInt(1)) != 0) value ^= basis_[bit];\n        }\n        return value\
    \ == 0;\n    }\n\n    int rank() const {\n        return rank_;\n    }\n\n   \
    \ bool empty() const {\n        return rank_ == 0;\n    }\n\n    void clear()\
    \ {\n        basis_.fill(UInt(0));\n        rank_ = 0;\n    }\n\n    int merge(const\
    \ XorBasis& other) {\n        const int old_rank = rank_;\n        for (UInt value\
    \ : other.basis_) {\n            if (value != 0) insert(value);\n        }\n \
    \       return rank_ - old_rank;\n    }\n\n    UInt min_xor(UInt value = 0) const\
    \ {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if\
    \ ((value ^ basis_[bit]) < value) value ^= basis_[bit];\n        }\n        return\
    \ value;\n    }\n\n    UInt max_xor(UInt value = 0) const {\n        for (int\
    \ bit = bit_width - 1; bit >= 0; bit--) {\n            if (value < (value ^ basis_[bit]))\
    \ value ^= basis_[bit];\n        }\n        return value;\n    }\n\n    UInt kth_smallest(UInt\
    \ index) const {\n        if (rank_ < bit_width) assert(index < (UInt(1) << rank_));\n\
    \        UInt result = 0;\n        int coefficient = 0;\n        for (int bit\
    \ = 0; bit < bit_width; bit++) {\n            if (basis_[bit] == 0) continue;\n\
    \            if (((index >> coefficient) & UInt(1)) != 0) result ^= basis_[bit];\n\
    \            coefficient++;\n        }\n        return result;\n    }\n\n    std::vector<UInt>\
    \ vectors() const {\n        std::vector<UInt> result;\n        result.reserve(rank_);\n\
    \        for (UInt value : basis_) {\n            if (value != 0) result.push_back(value);\n\
    \        }\n        return result;\n    }\n\nprivate:\n    std::array<UInt, bit_width>\
    \ basis_{};\n    int rank_ = 0;\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MATH_XOR_BASIS_HPP\n#define M1UNE_MATH_XOR_BASIS_HPP 1\n\n\
    #include <array>\n#include <cassert>\n#include <concepts>\n#include <initializer_list>\n\
    #include <iterator>\n#include <limits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <std::unsigned_integral UInt = unsigned long long>\n\
    class XorBasis {\n    static_assert(!std::same_as<UInt, bool>);\n\npublic:\n \
    \   static constexpr int bit_width = std::numeric_limits<UInt>::digits;\n\n  \
    \  XorBasis() = default;\n\n    template <std::input_iterator Iterator, std::sentinel_for<Iterator>\
    \ Sentinel>\n        requires std::convertible_to<std::iter_reference_t<Iterator>,\
    \ UInt>\n    XorBasis(Iterator first, Sentinel last) {\n        for (; first !=\
    \ last; ++first) insert(UInt(*first));\n    }\n\n    XorBasis(std::initializer_list<UInt>\
    \ values)\n        : XorBasis(values.begin(), values.end()) {}\n\n    bool insert(UInt\
    \ value) {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n       \
    \     if (((value >> bit) & UInt(1)) == 0) continue;\n            if (basis_[bit]\
    \ != 0) {\n                value ^= basis_[bit];\n                continue;\n\
    \            }\n\n            for (int lower = bit - 1; lower >= 0; lower--) {\n\
    \                if (((value >> lower) & UInt(1)) != 0) value ^= basis_[lower];\n\
    \            }\n            basis_[bit] = value;\n            rank_++;\n     \
    \       for (int higher = bit + 1; higher < bit_width; higher++) {\n         \
    \       if (((basis_[higher] >> bit) & UInt(1)) != 0) {\n                    basis_[higher]\
    \ ^= value;\n                }\n            }\n            return true;\n    \
    \    }\n        return false;\n    }\n\n    bool contains(UInt value) const {\n\
    \        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if (((value\
    \ >> bit) & UInt(1)) != 0) value ^= basis_[bit];\n        }\n        return value\
    \ == 0;\n    }\n\n    int rank() const {\n        return rank_;\n    }\n\n   \
    \ bool empty() const {\n        return rank_ == 0;\n    }\n\n    void clear()\
    \ {\n        basis_.fill(UInt(0));\n        rank_ = 0;\n    }\n\n    int merge(const\
    \ XorBasis& other) {\n        const int old_rank = rank_;\n        for (UInt value\
    \ : other.basis_) {\n            if (value != 0) insert(value);\n        }\n \
    \       return rank_ - old_rank;\n    }\n\n    UInt min_xor(UInt value = 0) const\
    \ {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if\
    \ ((value ^ basis_[bit]) < value) value ^= basis_[bit];\n        }\n        return\
    \ value;\n    }\n\n    UInt max_xor(UInt value = 0) const {\n        for (int\
    \ bit = bit_width - 1; bit >= 0; bit--) {\n            if (value < (value ^ basis_[bit]))\
    \ value ^= basis_[bit];\n        }\n        return value;\n    }\n\n    UInt kth_smallest(UInt\
    \ index) const {\n        if (rank_ < bit_width) assert(index < (UInt(1) << rank_));\n\
    \        UInt result = 0;\n        int coefficient = 0;\n        for (int bit\
    \ = 0; bit < bit_width; bit++) {\n            if (basis_[bit] == 0) continue;\n\
    \            if (((index >> coefficient) & UInt(1)) != 0) result ^= basis_[bit];\n\
    \            coefficient++;\n        }\n        return result;\n    }\n\n    std::vector<UInt>\
    \ vectors() const {\n        std::vector<UInt> result;\n        result.reserve(rank_);\n\
    \        for (UInt value : basis_) {\n            if (value != 0) result.push_back(value);\n\
    \        }\n        return result;\n    }\n\nprivate:\n    std::array<UInt, bit_width>\
    \ basis_{};\n    int rank_ = 0;\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MATH_XOR_BASIS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/xor_basis.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 05:12:04+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/xor_basis.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/xor_basis.hpp
layout: document
title: XOR Basis
---

## Overview

`XorBasis` maintains a linearly independent basis of unsigned integers, viewed
as vectors over $\mathbb{F}_2$. It represents exactly the values obtainable by
XORing a subset of the inserted values.

```cpp
#include "math/xor_basis.hpp"
```

The class is in `m1une::math`.

## Template Requirements

```cpp
template <std::unsigned_integral UInt = unsigned long long>
class XorBasis;
```

`UInt` must be an unsigned integer type other than `bool`. The default basis
handles all bits of `unsigned long long`. Memory usage is $O(B)$, where
$B = std::numeric_limits<UInt>::digits$.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `XorBasis()` | Constructs an empty basis. | $O(B)$ |
| `XorBasis(first, last)` | Inserts every value in the iterator range. | $O(NB)$ |
| `XorBasis(values)` | Inserts an initializer list. | $O(NB)$ |
| `bool insert(UInt value)` | Inserts `value`; returns whether the rank increased. | $O(B)$ |
| `bool contains(UInt value) const` | Tests whether `value` is representable. | $O(B)$ |
| `int rank() const` | Returns the number of independent vectors. | $O(1)$ |
| `bool empty() const` | Tests whether the rank is zero. | $O(1)$ |
| `void clear()` | Removes all vectors. | $O(B)$ |
| `int merge(const XorBasis& other)` | Inserts another basis and returns the rank increase. | $O(B^2)$ |
| `UInt min_xor(UInt value = 0) const` | Minimizes `value ^ x` over representable `x`. | $O(B)$ |
| `UInt max_xor(UInt value = 0) const` | Maximizes `value ^ x` over representable `x`. | $O(B)$ |
| `UInt kth_smallest(UInt index) const` | Returns the zero-based `index`-th smallest representable value. | $O(B)$ |
| `std::vector<UInt> vectors() const` | Returns independent vectors in increasing pivot-bit order. | $O(B)$ |

`insert`, `merge`, and `clear` mutate the basis. All query methods are `const`.
Duplicate or dependent insertions leave the basis unchanged. Zero is always
representable and does not increase the rank.

There are exactly $2^{\text{rank}}$ distinct representable values.
`kth_smallest(index)` asserts that `index` is in this range when the count fits
in `UInt`. At full rank, every `UInt` value is representable, so every possible
`UInt` index is valid.

## Example

```cpp
#include "math/xor_basis.hpp"

#include <cassert>

int main() {
    m1une::math::XorBasis<unsigned> basis{3, 5, 6};

    assert(basis.rank() == 2);
    assert(basis.contains(6));
    assert(!basis.contains(1));
    assert(basis.max_xor() == 6);
    assert(basis.kth_smallest(2) == 5);
}
```
