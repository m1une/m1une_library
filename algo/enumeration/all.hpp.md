---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/combination.hpp
    title: Combination Masks
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/gray_code.hpp
    title: Gray Code
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/permutation_lexicographical_order.hpp
    title: Permutation Lexicographical Order
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/segtree_range.hpp
    title: Segment Tree Range Split
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/submask.hpp
    title: Submask Enumeration
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/enumeration/all.hpp\"\n\n\n\n#line 1 \"algo/enumeration/combination.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <limits>\n#include <type_traits>\n\nnamespace m1une {\nnamespace algo {\n\n\
    namespace internal {\n\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt combination_low_bits(int bit_count) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= bit_count && bit_count\
    \ <= digits);\n    if (bit_count == digits) return ~UInt(0);\n    return (UInt(1)\
    \ << bit_count) - UInt(1);\n}\n\n}  // namespace internal\n\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    UInt first_combination_mask(int bit_count, int choose) {\n    constexpr int digits\
    \ = std::numeric_limits<UInt>::digits;\n    assert(0 <= choose && choose <= bit_count\
    \ && bit_count <= digits);\n    if (choose == 0) return UInt(0);\n    if (choose\
    \ == bit_count) return internal::combination_low_bits<UInt>(bit_count);\n    return\
    \ (UInt(1) << choose) - UInt(1);\n}\n\ntemplate <std::unsigned_integral UInt>\n\
    requires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nbool next_combination_mask(UInt&\
    \ mask, int bit_count) {\n    const UInt universe = internal::combination_low_bits<UInt>(bit_count);\n\
    \    assert((mask & ~universe) == 0);\n    if (mask == 0) return false;\n\n  \
    \  const UInt lowest = mask & (~mask + UInt(1));\n    const UInt ripple = mask\
    \ + lowest;\n    if (ripple == 0 || (ripple & ~universe) != 0) return false;\n\
    \n    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;\n    if ((next\
    \ & ~universe) != 0) return false;\n    mask = next;\n    return true;\n}\n\n\
    template <std::unsigned_integral UInt = std::uint64_t, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_combination_mask(int bit_count, int choose, F f) {\n \
    \   constexpr int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <=\
    \ choose && choose <= bit_count && bit_count <= digits);\n    UInt mask = first_combination_mask<UInt>(bit_count,\
    \ choose);\n    while (true) {\n        f(mask);\n        if (!next_combination_mask(mask,\
    \ bit_count)) break;\n    }\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"algo/enumeration/gray_code.hpp\"\n\n\n\n#line 6 \"algo/enumeration/gray_code.hpp\"\
    \n#include <cstddef>\n#line 10 \"algo/enumeration/gray_code.hpp\"\n#include <vector>\n\
    \nnamespace m1une {\nnamespace algo {\n\n// Converts a binary value to its binary-reflected\
    \ Gray code.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_encode(UInt value) noexcept {\n    return value\
    \ ^ (value >> 1);\n}\n\n// Converts a binary-reflected Gray code to the corresponding\
    \ binary value.\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nconstexpr UInt gray_decode(UInt code) noexcept {\n    for (int shift\
    \ = 1; shift < std::numeric_limits<UInt>::digits;\n         shift <<= 1) {\n \
    \       code ^= code >> shift;\n    }\n    return code;\n}\n\n// Returns all bit_count-bit\
    \ binary-reflected Gray codes in traversal order.\ntemplate <std::unsigned_integral\
    \ UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\n\
    std::vector<UInt> gray_code_sequence(int bit_count) {\n    constexpr int uint_digits\
    \ = std::numeric_limits<UInt>::digits;\n    constexpr int size_digits = std::numeric_limits<std::size_t>::digits;\n\
    \    assert(0 <= bit_count);\n    assert(bit_count <= uint_digits);\n    assert(bit_count\
    \ < size_digits);\n    if (bit_count < 0 || uint_digits < bit_count || size_digits\
    \ <= bit_count) {\n        return {};\n    }\n\n    const std::size_t size = std::size_t(1)\
    \ << bit_count;\n    std::vector<UInt> result(size);\n    for (std::size_t index\
    \ = 0; index < size; ++index) {\n        result[index] = gray_encode(static_cast<UInt>(index));\n\
    \    }\n    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 1 \"algo/enumeration/permutation_lexicographical_order.hpp\"\n\n\n\n\
    #line 8 \"algo/enumeration/permutation_lexicographical_order.hpp\"\n#include <optional>\n\
    #line 10 \"algo/enumeration/permutation_lexicographical_order.hpp\"\n#include\
    \ <utility>\n#line 12 \"algo/enumeration/permutation_lexicographical_order.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\nstruct PermutationOrderFenwick\
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
    }\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/enumeration/segtree_range.hpp\"\
    \n\n\n\n#include <bit>\n#line 10 \"algo/enumeration/segtree_range.hpp\"\n\nnamespace\
    \ m1une {\nnamespace algo {\n\n// Splits [left, right) into maximal segment-tree\
    \ ranges from left to right.\ntemplate <std::integral Int>\nrequires(!std::same_as<std::remove_cv_t<Int>,\
    \ bool>)\nstd::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right)\
    \ {\n    if constexpr (std::signed_integral<Int>) assert(Int(0) <= left);\n  \
    \  assert(left <= right);\n    if constexpr (std::signed_integral<Int>) {\n  \
    \      if (left < 0) return {};\n    }\n    if (right < left) return {};\n\n \
    \   using UInt = std::make_unsigned_t<Int>;\n    UInt position = static_cast<UInt>(left);\n\
    \    const UInt end = static_cast<UInt>(right);\n    std::vector<std::pair<Int,\
    \ Int>> result;\n    if (position == end) return result;\n    result.reserve(2\
    \ * std::bit_width(end - position));\n\n    while (position < end) {\n       \
    \ UInt length = std::bit_floor(end - position);\n        if (position != 0) {\n\
    \            const UInt alignment = position & (~position + UInt(1));\n      \
    \      if (alignment < length) length = alignment;\n        }\n        const UInt\
    \ next = position + length;\n        result.emplace_back(\n            static_cast<Int>(position),\
    \ static_cast<Int>(next)\n        );\n        position = next;\n    }\n    return\
    \ result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/enumeration/submask.hpp\"\
    \n\n\n\n#line 8 \"algo/enumeration/submask.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt submask_low_bits(int bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_submask(UInt mask, F f) {\n    UInt submask = mask;\n\
    \    while (true) {\n        f(submask);\n        if (submask == 0) break;\n \
    \       submask = (submask - 1) & mask;\n    }\n}\n\ntemplate <std::unsigned_integral\
    \ UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nvoid\
    \ for_each_nonzero_submask(UInt mask, F f) {\n    for (UInt submask = mask; submask\
    \ != 0; submask = (submask - 1) & mask) {\n        f(submask);\n    }\n}\n\ntemplate\
    \ <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_supermask(UInt mask, int bit_count, F f) {\n    const\
    \ UInt universe = internal::submask_low_bits<UInt>(bit_count);\n    assert((mask\
    \ & ~universe) == 0);\n    const UInt free_bits = universe ^ mask;\n    for_each_submask(free_bits,\
    \ [&](UInt added_bits) {\n        f(mask | added_bits);\n    });\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 9 \"algo/enumeration/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ENUMERATION_ALL_HPP

    #define M1UNE_ALGO_ENUMERATION_ALL_HPP 1


    #include "combination.hpp"

    #include "gray_code.hpp"

    #include "permutation_lexicographical_order.hpp"

    #include "segtree_range.hpp"

    #include "submask.hpp"


    #endif  // M1UNE_ALGO_ENUMERATION_ALL_HPP

    '
  dependsOn:
  - algo/enumeration/combination.hpp
  - algo/enumeration/gray_code.hpp
  - algo/enumeration/permutation_lexicographical_order.hpp
  - algo/enumeration/segtree_range.hpp
  - algo/enumeration/submask.hpp
  isVerificationFile: false
  path: algo/enumeration/all.hpp
  requiredBy:
  - algo/all.hpp
  timestamp: '2026-07-25 23:25:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/enumeration/all.hpp
layout: document
title: Enumeration Algorithms All
---

## Overview

`algo/enumeration/all.hpp` includes helpers for traversing combinatorial state
spaces. The public namespace is `m1une::algo`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/enumeration/gray_code.hpp` | Binary-reflected Gray-code encoding, decoding, and enumeration. |
| `algo/enumeration/segtree_range.hpp` | Decomposition into maximal aligned segment-tree ranges. |
| `algo/enumeration/submask.hpp` | Submask and supermask enumeration helpers. |
| `algo/enumeration/combination.hpp` | Fixed-size subset mask generation helpers. |
| `algo/enumeration/permutation_lexicographical_order.hpp` | Rank and select permutations in lexicographical order. |
