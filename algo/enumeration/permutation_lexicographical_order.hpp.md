---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/enumeration/all.hpp
    title: Enumeration Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/enumeration/permutation_lexicographical_order.test.cpp
    title: verify/algo/enumeration/permutation_lexicographical_order.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/enumeration/permutation_lexicographical_order.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal\
    \ {\n\nstruct PermutationOrderFenwick {\n    std::vector<int> data;\n\n    explicit\
    \ PermutationOrderFenwick(int size) : data(size + 1) {}\n\n    void add(int index,\
    \ int value) {\n        for (index++; index < int(data.size()); index += index\
    \ & -index) {\n            data[index] += value;\n        }\n    }\n\n    int\
    \ prefix_sum(int right) const {\n        int result = 0;\n        for (; 0 < right;\
    \ right -= right & -right) result += data[right];\n        return result;\n  \
    \  }\n\n    int kth(int order) const {\n        int index = 0;\n        int accumulated\
    \ = 0;\n        int step = 1;\n        while (step < int(data.size())) step <<=\
    \ 1;\n        for (; 0 < step; step >>= 1) {\n            const int next = index\
    \ + step;\n            if (next < int(data.size()) &&\n                accumulated\
    \ + data[next] <= order) {\n                index = next;\n                accumulated\
    \ += data[next];\n            }\n        }\n        return index;\n    }\n};\n\
    \n}  // namespace internal\n\n// Returns the zero-based lexicographical rank of\
    \ a permutation of [0, n).\n// Returns nullopt when the sequence is invalid or\
    \ the rank does not fit in UInt.\ntemplate <\n    std::unsigned_integral UInt\
    \ = std::uint64_t,\n    class Permutation\n>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::optional<UInt> checked_permutation_lexicographical_rank(\n    const\
    \ Permutation& permutation\n) {\n    const int size = int(permutation.size());\n\
    \    internal::PermutationOrderFenwick fenwick(size);\n    for (int value = 0;\
    \ value < size; value++) fenwick.add(value, 1);\n\n    UInt rank = 0;\n    constexpr\
    \ UInt limit = std::numeric_limits<UInt>::max();\n    for (int index = 0; index\
    \ < size; index++) {\n        const auto& value_reference = permutation[index];\n\
    \        using Value = std::remove_cvref_t<decltype(value_reference)>;\n     \
    \   static_assert(std::integral<Value>);\n        static_assert(!std::same_as<Value,\
    \ bool>);\n\n        if (std::cmp_less(value_reference, 0) ||\n            std::cmp_greater_equal(value_reference,\
    \ size)) {\n            return std::nullopt;\n        }\n        const int value\
    \ = int(value_reference);\n        if (fenwick.prefix_sum(value + 1) == fenwick.prefix_sum(value))\
    \ {\n            return std::nullopt;\n        }\n\n        const std::uintmax_t\
    \ smaller = fenwick.prefix_sum(value);\n        const std::uintmax_t remaining\
    \ = size - index;\n        if (smaller > std::uintmax_t(limit) ||\n          \
    \  std::uintmax_t(rank) >\n                (std::uintmax_t(limit) - smaller) /\
    \ remaining) {\n            return std::nullopt;\n        }\n        rank = UInt(std::uintmax_t(rank)\
    \ * remaining + smaller);\n        fenwick.add(value, -1);\n    }\n    return\
    \ rank;\n}\n\n// Every value must occur exactly once in [0, n), and the rank must\
    \ fit in UInt.\ntemplate <\n    std::unsigned_integral UInt = std::uint64_t,\n\
    \    class Permutation\n>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    UInt permutation_lexicographical_rank(const Permutation& permutation) {\n    const\
    \ std::optional<UInt> result =\n        checked_permutation_lexicographical_rank<UInt>(permutation);\n\
    \    assert(result.has_value());\n    return result.value_or(UInt(0));\n}\n\n\
    // Returns the permutation of [0, size) with the given zero-based rank.\n// Returns\
    \ nullopt when size is negative or rank is at least size factorial.\ntemplate\
    \ <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::optional<std::vector<int>> checked_kth_lexicographical_permutation(\n\
    \    int size,\n    UInt rank\n) {\n    if (size < 0) return std::nullopt;\n\n\
    \    std::vector<int> lehmer_code(size);\n    UInt remaining_rank = rank;\n  \
    \  for (int base = 1; base <= size && remaining_rank != 0; base++) {\n       \
    \ lehmer_code[size - base] = int(remaining_rank % UInt(base));\n        remaining_rank\
    \ /= UInt(base);\n    }\n    if (remaining_rank != 0) return std::nullopt;\n\n\
    \    internal::PermutationOrderFenwick fenwick(size);\n    for (int value = 0;\
    \ value < size; value++) fenwick.add(value, 1);\n\n    std::vector<int> permutation(size);\n\
    \    for (int index = 0; index < size; index++) {\n        const int value = fenwick.kth(lehmer_code[index]);\n\
    \        permutation[index] = value;\n        fenwick.add(value, -1);\n    }\n\
    \    return permutation;\n}\n\n// Rank must be less than size factorial.\ntemplate\
    \ <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::vector<int> kth_lexicographical_permutation(int size, UInt rank)\
    \ {\n    std::optional<std::vector<int>> result =\n        checked_kth_lexicographical_permutation(size,\
    \ rank);\n    assert(result.has_value());\n    return result.value_or(std::vector<int>());\n\
    }\n\n}  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP\n#define\
    \ M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP 1\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace algo {\n\nnamespace internal {\n\nstruct PermutationOrderFenwick\
    \ {\n    std::vector<int> data;\n\n    explicit PermutationOrderFenwick(int size)\
    \ : data(size + 1) {}\n\n    void add(int index, int value) {\n        for (index++;\
    \ index < int(data.size()); index += index & -index) {\n            data[index]\
    \ += value;\n        }\n    }\n\n    int prefix_sum(int right) const {\n     \
    \   int result = 0;\n        for (; 0 < right; right -= right & -right) result\
    \ += data[right];\n        return result;\n    }\n\n    int kth(int order) const\
    \ {\n        int index = 0;\n        int accumulated = 0;\n        int step =\
    \ 1;\n        while (step < int(data.size())) step <<= 1;\n        for (; 0 <\
    \ step; step >>= 1) {\n            const int next = index + step;\n          \
    \  if (next < int(data.size()) &&\n                accumulated + data[next] <=\
    \ order) {\n                index = next;\n                accumulated += data[next];\n\
    \            }\n        }\n        return index;\n    }\n};\n\n}  // namespace\
    \ internal\n\n// Returns the zero-based lexicographical rank of a permutation\
    \ of [0, n).\n// Returns nullopt when the sequence is invalid or the rank does\
    \ not fit in UInt.\ntemplate <\n    std::unsigned_integral UInt = std::uint64_t,\n\
    \    class Permutation\n>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    std::optional<UInt> checked_permutation_lexicographical_rank(\n    const Permutation&\
    \ permutation\n) {\n    const int size = int(permutation.size());\n    internal::PermutationOrderFenwick\
    \ fenwick(size);\n    for (int value = 0; value < size; value++) fenwick.add(value,\
    \ 1);\n\n    UInt rank = 0;\n    constexpr UInt limit = std::numeric_limits<UInt>::max();\n\
    \    for (int index = 0; index < size; index++) {\n        const auto& value_reference\
    \ = permutation[index];\n        using Value = std::remove_cvref_t<decltype(value_reference)>;\n\
    \        static_assert(std::integral<Value>);\n        static_assert(!std::same_as<Value,\
    \ bool>);\n\n        if (std::cmp_less(value_reference, 0) ||\n            std::cmp_greater_equal(value_reference,\
    \ size)) {\n            return std::nullopt;\n        }\n        const int value\
    \ = int(value_reference);\n        if (fenwick.prefix_sum(value + 1) == fenwick.prefix_sum(value))\
    \ {\n            return std::nullopt;\n        }\n\n        const std::uintmax_t\
    \ smaller = fenwick.prefix_sum(value);\n        const std::uintmax_t remaining\
    \ = size - index;\n        if (smaller > std::uintmax_t(limit) ||\n          \
    \  std::uintmax_t(rank) >\n                (std::uintmax_t(limit) - smaller) /\
    \ remaining) {\n            return std::nullopt;\n        }\n        rank = UInt(std::uintmax_t(rank)\
    \ * remaining + smaller);\n        fenwick.add(value, -1);\n    }\n    return\
    \ rank;\n}\n\n// Every value must occur exactly once in [0, n), and the rank must\
    \ fit in UInt.\ntemplate <\n    std::unsigned_integral UInt = std::uint64_t,\n\
    \    class Permutation\n>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    UInt permutation_lexicographical_rank(const Permutation& permutation) {\n    const\
    \ std::optional<UInt> result =\n        checked_permutation_lexicographical_rank<UInt>(permutation);\n\
    \    assert(result.has_value());\n    return result.value_or(UInt(0));\n}\n\n\
    // Returns the permutation of [0, size) with the given zero-based rank.\n// Returns\
    \ nullopt when size is negative or rank is at least size factorial.\ntemplate\
    \ <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::optional<std::vector<int>> checked_kth_lexicographical_permutation(\n\
    \    int size,\n    UInt rank\n) {\n    if (size < 0) return std::nullopt;\n\n\
    \    std::vector<int> lehmer_code(size);\n    UInt remaining_rank = rank;\n  \
    \  for (int base = 1; base <= size && remaining_rank != 0; base++) {\n       \
    \ lehmer_code[size - base] = int(remaining_rank % UInt(base));\n        remaining_rank\
    \ /= UInt(base);\n    }\n    if (remaining_rank != 0) return std::nullopt;\n\n\
    \    internal::PermutationOrderFenwick fenwick(size);\n    for (int value = 0;\
    \ value < size; value++) fenwick.add(value, 1);\n\n    std::vector<int> permutation(size);\n\
    \    for (int index = 0; index < size; index++) {\n        const int value = fenwick.kth(lehmer_code[index]);\n\
    \        permutation[index] = value;\n        fenwick.add(value, -1);\n    }\n\
    \    return permutation;\n}\n\n// Rank must be less than size factorial.\ntemplate\
    \ <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::vector<int> kth_lexicographical_permutation(int size, UInt rank)\
    \ {\n    std::optional<std::vector<int>> result =\n        checked_kth_lexicographical_permutation(size,\
    \ rank);\n    assert(result.has_value());\n    return result.value_or(std::vector<int>());\n\
    }\n\n}  // namespace algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_ENUMERATION_PERMUTATION_LEXICOGRAPHICAL_ORDER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/enumeration/permutation_lexicographical_order.hpp
  requiredBy:
  - algo/enumeration/all.hpp
  - algo/all.hpp
  timestamp: '2026-07-25 23:25:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/enumeration/permutation_lexicographical_order.test.cpp
documentation_of: algo/enumeration/permutation_lexicographical_order.hpp
layout: document
title: Permutation Lexicographical Order
---

## Overview

This header converts in both directions between a permutation of `[0, N)` and
its zero-based position among all such permutations in lexicographical order.
It uses a Fenwick tree and a Lehmer code, without enumerating earlier
permutations.

```cpp
#include "algo/enumeration/permutation_lexicographical_order.hpp"
```

## Template Requirements

`UInt` must be an unsigned integral type other than `bool`. The default is
`std::uint64_t`.

The rank functions accept a random-access sequence whose `size()` fits in
`int` and whose elements are integral values other than `bool`.

## Functions

Let `N` be the permutation size.

| Function | Description | Complexity |
| --- | --- | --- |
| `optional<UInt> checked_permutation_lexicographical_rank<UInt>(permutation)` | Returns its zero-based rank, or `nullopt` if the input is not a permutation of `[0, N)` or the rank does not fit in `UInt`. | $O(N \log N)$ time and $O(N)$ memory |
| `UInt permutation_lexicographical_rank<UInt>(permutation)` | Returns its zero-based rank. The input and result must be valid. | $O(N \log N)$ time and $O(N)$ memory |
| `optional<vector<int>> checked_kth_lexicographical_permutation(size, rank)` | Returns the permutation at `rank`, or `nullopt` if `size` is negative or `rank` is at least $N!$. | $O(N \log N)$ time and $O(N)$ memory |
| `vector<int> kth_lexicographical_permutation(size, rank)` | Returns the permutation at `rank`. The rank must be less than $N!$. | $O(N \log N)$ time and $O(N)$ memory |

The unchecked functions assert their preconditions. The checked functions do
not rely on computing $N!$, so they remain usable when $N!$ does not fit in
`UInt`. In particular, a small rank of a large permutation can still be ranked
and selected exactly.

The only permutation of size zero is the empty permutation, with rank zero.

## Example

```cpp
#include "algo/enumeration/permutation_lexicographical_order.hpp"

#include <cstdint>
#include <vector>

int main() {
    std::vector<int> permutation = {2, 0, 3, 1};
    std::uint64_t rank =
        m1une::algo::permutation_lexicographical_rank(permutation);

    std::vector<int> restored =
        m1une::algo::kth_lexicographical_permutation(4, rank);
}
```
