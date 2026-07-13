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
  - icon: ':x:'
    path: verify/math/subset_convolution.test.cpp
    title: verify/math/subset_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/subset_convolution.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nstd::vector<T>\
    \ subset_convolution(\n    std::vector<T> first,\n    std::vector<T> second\n\
    ) {\n    assert(first.size() == second.size());\n    if (first.empty()) return\
    \ {};\n    assert((first.size() & (first.size() - 1)) == 0);\n\n    const std::size_t\
    \ size = first.size();\n    std::size_t bit_count = 0;\n    while ((std::size_t(1)\
    \ << bit_count) < size) ++bit_count;\n    const std::size_t rank_count = bit_count\
    \ + 1;\n\n    std::vector<T> first_ranked(size * rank_count);\n    std::vector<T>\
    \ second_ranked(size * rank_count);\n    for (std::size_t mask = 0; mask < size;\
    \ ++mask) {\n        const std::size_t rank = std::popcount(mask);\n        first_ranked[mask\
    \ * rank_count + rank] = std::move(first[mask]);\n        second_ranked[mask *\
    \ rank_count + rank] = std::move(second[mask]);\n    }\n\n    for (std::size_t\
    \ bit = 1; bit < size; bit <<= 1) {\n        for (std::size_t mask = 0; mask <\
    \ size; ++mask) {\n            if ((mask & bit) == 0) continue;\n            const\
    \ std::size_t destination = mask * rank_count;\n            const std::size_t\
    \ source = (mask ^ bit) * rank_count;\n            for (std::size_t rank = 0;\
    \ rank < rank_count; ++rank) {\n                first_ranked[destination + rank]\
    \ +=\n                    first_ranked[source + rank];\n                second_ranked[destination\
    \ + rank] +=\n                    second_ranked[source + rank];\n            }\n\
    \        }\n    }\n\n    std::vector<T> product(rank_count);\n    for (std::size_t\
    \ mask = 0; mask < size; ++mask) {\n        for (T& value : product) value = T{};\n\
    \        const std::size_t offset = mask * rank_count;\n        const std::size_t\
    \ rank_limit = std::popcount(mask);\n        for (std::size_t left = 0; left <=\
    \ rank_limit; ++left) {\n            const std::size_t right_limit =\n       \
    \         std::min(rank_limit, bit_count - left);\n            for (std::size_t\
    \ right = 0; right <= right_limit; ++right) {\n                product[left +\
    \ right] +=\n                    first_ranked[offset + left] *\n             \
    \       second_ranked[offset + right];\n            }\n        }\n        for\
    \ (std::size_t rank = 0; rank < rank_count; ++rank) {\n            first_ranked[offset\
    \ + rank] = std::move(product[rank]);\n        }\n    }\n\n    for (std::size_t\
    \ bit = 1; bit < size; bit <<= 1) {\n        for (std::size_t mask = 0; mask <\
    \ size; ++mask) {\n            if ((mask & bit) == 0) continue;\n            const\
    \ std::size_t destination = mask * rank_count;\n            const std::size_t\
    \ source = (mask ^ bit) * rank_count;\n            for (std::size_t rank = 0;\
    \ rank < rank_count; ++rank) {\n                first_ranked[destination + rank]\
    \ -=\n                    first_ranked[source + rank];\n            }\n      \
    \  }\n    }\n\n    std::vector<T> result(size);\n    for (std::size_t mask = 0;\
    \ mask < size; ++mask) {\n        result[mask] = std::move(\n            first_ranked[mask\
    \ * rank_count + std::popcount(mask)]\n        );\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_SUBSET_CONVOLUTION_HPP\n#define M1UNE_MATH_SUBSET_CONVOLUTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nstd::vector<T> subset_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    assert(first.size() == second.size());\n\
    \    if (first.empty()) return {};\n    assert((first.size() & (first.size() -\
    \ 1)) == 0);\n\n    const std::size_t size = first.size();\n    std::size_t bit_count\
    \ = 0;\n    while ((std::size_t(1) << bit_count) < size) ++bit_count;\n    const\
    \ std::size_t rank_count = bit_count + 1;\n\n    std::vector<T> first_ranked(size\
    \ * rank_count);\n    std::vector<T> second_ranked(size * rank_count);\n    for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n        const std::size_t rank\
    \ = std::popcount(mask);\n        first_ranked[mask * rank_count + rank] = std::move(first[mask]);\n\
    \        second_ranked[mask * rank_count + rank] = std::move(second[mask]);\n\
    \    }\n\n    for (std::size_t bit = 1; bit < size; bit <<= 1) {\n        for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n            if ((mask & bit)\
    \ == 0) continue;\n            const std::size_t destination = mask * rank_count;\n\
    \            const std::size_t source = (mask ^ bit) * rank_count;\n         \
    \   for (std::size_t rank = 0; rank < rank_count; ++rank) {\n                first_ranked[destination\
    \ + rank] +=\n                    first_ranked[source + rank];\n             \
    \   second_ranked[destination + rank] +=\n                    second_ranked[source\
    \ + rank];\n            }\n        }\n    }\n\n    std::vector<T> product(rank_count);\n\
    \    for (std::size_t mask = 0; mask < size; ++mask) {\n        for (T& value\
    \ : product) value = T{};\n        const std::size_t offset = mask * rank_count;\n\
    \        const std::size_t rank_limit = std::popcount(mask);\n        for (std::size_t\
    \ left = 0; left <= rank_limit; ++left) {\n            const std::size_t right_limit\
    \ =\n                std::min(rank_limit, bit_count - left);\n            for\
    \ (std::size_t right = 0; right <= right_limit; ++right) {\n                product[left\
    \ + right] +=\n                    first_ranked[offset + left] *\n           \
    \         second_ranked[offset + right];\n            }\n        }\n        for\
    \ (std::size_t rank = 0; rank < rank_count; ++rank) {\n            first_ranked[offset\
    \ + rank] = std::move(product[rank]);\n        }\n    }\n\n    for (std::size_t\
    \ bit = 1; bit < size; bit <<= 1) {\n        for (std::size_t mask = 0; mask <\
    \ size; ++mask) {\n            if ((mask & bit) == 0) continue;\n            const\
    \ std::size_t destination = mask * rank_count;\n            const std::size_t\
    \ source = (mask ^ bit) * rank_count;\n            for (std::size_t rank = 0;\
    \ rank < rank_count; ++rank) {\n                first_ranked[destination + rank]\
    \ -=\n                    first_ranked[source + rank];\n            }\n      \
    \  }\n    }\n\n    std::vector<T> result(size);\n    for (std::size_t mask = 0;\
    \ mask < size; ++mask) {\n        result[mask] = std::move(\n            first_ranked[mask\
    \ * rank_count + std::popcount(mask)]\n        );\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_SUBSET_CONVOLUTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/subset_convolution.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 05:19:17+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/math/subset_convolution.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/subset_convolution.hpp
layout: document
title: Subset Convolution
---

## Overview

Subset convolution combines two arrays indexed by bit masks. For every mask
$S$, it computes

$$
c_S = \sum_{T \subseteq S} a_T b_{S \setminus T}.
$$

Equivalently, every term partitions `S` into two disjoint masks. This operation
appears in subset dynamic programming when two independently solved parts must
cover the current set exactly.

```cpp
#include "math/subset_convolution.hpp"
```

The function is in `m1une::math`.

## Interface

```cpp
template <typename T>
std::vector<T> subset_convolution(
    std::vector<T> first,
    std::vector<T> second
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_convolution(first, second)` | Returns the subset convolution of two equally sized mask arrays. | $O(K^2 2^K)$ time and $O(K 2^K)$ additional memory |

Both input vectors must have the same size. Their size must be zero or a power
of two; a nonempty vector of size $2^K$ represents masks on `K` bits. Empty
inputs produce an empty result. The result has the same size as each input.

The arguments are passed by value and used as workspace, so the caller's
vectors are unchanged unless explicitly moved into the function. The element
type `T` must be default-constructible and support multiplication, `operator+=`,
and `operator-=`. Modular integers and ordinary integer types satisfy these
requirements.

The implementation separates coefficients by mask popcount, applies ranked
subset-zeta transforms, multiplies the rank polynomials pointwise, and applies
the ranked Mobius transform. It uses two flat ranked work buffers rather than
allocating a separate vector for every mask.

## Example

```cpp
#include "math/subset_convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a{1, 2, 3, 4};
    std::vector<long long> b{5, 6, 7, 8};

    std::vector<long long> c =
        m1une::math::subset_convolution(a, b);

    // c[3] = a[0] * b[3] + a[1] * b[2]
    //      + a[2] * b[1] + a[3] * b[0] = 60.
    std::cout << c[3] << '\n';
}
```
