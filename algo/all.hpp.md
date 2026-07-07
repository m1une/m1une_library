---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: algo/enumeration/all.hpp
    title: Enumeration Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/gray_code.hpp
    title: Gray Code
  - icon: ':warning:'
    path: algo/offline/all.hpp
    title: Offline Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/offline/mo.hpp
    title: Mo's Algorithm
  - icon: ':warning:'
    path: algo/search/all.hpp
    title: Search Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/search/bisect.hpp
    title: Bisect
  - icon: ':warning:'
    path: algo/sequence/all.hpp
    title: Sequence Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/sequence/inversion_count.hpp
    title: Inversion Count
  - icon: ':heavy_check_mark:'
    path: algo/sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  - icon: ':heavy_check_mark:'
    path: algo/sequence/run_length_encoding.hpp
    title: Run Length Encoding
  - icon: ':heavy_check_mark:'
    path: algo/sequence/subset_sum.hpp
    title: Meet-in-the-Middle Subset Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/all.hpp\"\n\n\n\n#line 1 \"algo/enumeration/all.hpp\"\
    \n\n\n\n#line 1 \"algo/enumeration/gray_code.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n\
    #include <type_traits>\n#include <vector>\n\nnamespace m1une {\nnamespace algo\
    \ {\n\n// Converts a binary value to its binary-reflected Gray code.\ntemplate\
    \ <std::unsigned_integral UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
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
    \n\n#line 5 \"algo/enumeration/all.hpp\"\n\n\n#line 1 \"algo/offline/all.hpp\"\
    \n\n\n\n#line 1 \"algo/offline/mo.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"\
    algo/offline/mo.hpp\"\n#include <cmath>\n#include <numeric>\n#line 9 \"algo/offline/mo.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\n// Offline Mo's algorithm for half-open\
    \ array ranges.\nstruct Mo {\n    struct Query {\n        int left;\n        int\
    \ right;\n        int id;\n    };\n\n   private:\n    int _n;\n    std::vector<Query>\
    \ _queries;\n\n   public:\n    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n)\
    \ {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    bool empty() const {\n        return _queries.empty();\n    }\n\n\
    \    const std::vector<Query>& queries() const {\n        return _queries;\n \
    \   }\n\n    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n    }\n\n    // Adds [left, right) and returns its insertion-order\
    \ ID.\n    int add_query(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        int id = query_count();\n        _queries.push_back(Query{left,\
    \ right, id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order.\
    \ A non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 5 \"algo/offline/all.hpp\"\
    \n\n\n#line 1 \"algo/search/all.hpp\"\n\n\n\n#line 1 \"algo/search/bisect.hpp\"\
    \n\n\n\n#line 5 \"algo/search/bisect.hpp\"\n\nnamespace m1une {\nnamespace algo\
    \ {\n\ntemplate <typename F>\nlong long first_true(long long ng, long long ok,\
    \ F pred) {\n    auto distance = [](long long a, long long b) {\n        return\
    \ a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b) - a;\n \
    \   };\n    while (distance(ng, ok) > 1) {\n        long long mid = std::midpoint(ng,\
    \ ok);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\nlong long last_true(long long ok, long long ng, F pred) {\n    auto distance\
    \ = [](long long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a)\
    \ - b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ok, ng) >\
    \ 1) {\n        long long mid = std::midpoint(ok, ng);\n        if (pred(mid))\
    \ {\n            ok = mid;\n        } else {\n            ng = mid;\n        }\n\
    \    }\n    return ok;\n}\n\ntemplate <typename F>\ndouble real_first_true(double\
    \ ng, double ok, F pred, int iterations = 80) {\n    for (int i = 0; i < iterations;\
    \ ++i) {\n        double mid = (ng + ok) / 2.0;\n        if (pred(mid)) {\n  \
    \          ok = mid;\n        } else {\n            ng = mid;\n        }\n   \
    \ }\n    return ok;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 5 \"algo/search/all.hpp\"\n\n\n#line 1 \"algo/sequence/all.hpp\"\n\n\n\n#line\
    \ 1 \"algo/sequence/inversion_count.hpp\"\n\n\n\n#line 5 \"algo/sequence/inversion_count.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\n// Returns the number of pairs (i,\
    \ j) with i < j and a[i] > a[j].\n// The vector is taken by value because merge\
    \ sort rearranges it.\ntemplate <typename T>\nlong long inversion_count(std::vector<T>\
    \ a) {\n    const int n = int(a.size());\n    std::vector<T> temp = a;\n\n   \
    \ auto merge_sort = [&](auto& self, int l, int r) -> long long {\n        if (r\
    \ - l <= 1) return 0;\n\n        const int m = l + (r - l) / 2;\n        long\
    \ long inv = self(self, l, m) + self(self, m, r);\n\n        int i = l;\n    \
    \    int j = m;\n        int k = l;\n        while (i < m && j < r) {\n      \
    \      if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n          \
    \  } else {\n                temp[k++] = a[j++];\n                inv += m - i;\n\
    \            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n     \
    \   while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p) {\n\
    \            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n   \
    \ return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace algo\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/sequence/lis.hpp\"\n\n\n\n#line 5 \"algo/sequence/lis.hpp\"\
    \n#include <iterator>\n#line 7 \"algo/sequence/lis.hpp\"\n\nnamespace m1une {\n\
    namespace algo {\n\n// Returns the zero-based indices of a longest increasing\
    \ subsequence.\n// If `strict` is false, equal adjacent values are also allowed.\n\
    template <typename T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict\
    \ = true) {\n    const int n = int(a.size());\n    std::vector<T> tails;\n   \
    \ std::vector<int> tail_positions;\n    std::vector<int> predecessor(n, -1);\n\
    \    tails.reserve(n);\n    tail_positions.reserve(n);\n\n    for (int i = 0;\
    \ i < n; ++i) {\n        auto it = strict ? std::lower_bound(tails.begin(), tails.end(),\
    \ a[i])\n                         : std::upper_bound(tails.begin(), tails.end(),\
    \ a[i]);\n        const int length = int(std::distance(tails.begin(), it));\n\n\
    \        if (it == tails.end()) {\n            tails.push_back(a[i]);\n      \
    \      tail_positions.push_back(i);\n        } else {\n            *it = a[i];\n\
    \            tail_positions[length] = i;\n        }\n\n        if (length > 0)\
    \ {\n            predecessor[i] = tail_positions[length - 1];\n        }\n   \
    \ }\n\n    if (tail_positions.empty()) return {};\n\n    std::vector<int> result;\n\
    \    result.reserve(tail_positions.size());\n    int current = tail_positions.back();\n\
    \    while (current != -1) {\n        result.push_back(current);\n        current\
    \ = predecessor[current];\n    }\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line\
    \ 1 \"algo/sequence/run_length_encoding.hpp\"\n\n\n\n#line 5 \"algo/sequence/run_length_encoding.hpp\"\
    \n#include <utility>\n#line 7 \"algo/sequence/run_length_encoding.hpp\"\n\nnamespace\
    \ m1une {\nnamespace algo {\n\ntemplate <typename Container>\nauto run_length_encoding(const\
    \ Container& values) {\n    using T = typename Container::value_type;\n    std::vector<std::pair<T,\
    \ long long>> result;\n\n    auto it = std::begin(values);\n    auto last = std::end(values);\n\
    \    if (it == last) {\n        return result;\n    }\n\n    T current = *it;\n\
    \    long long count = 0;\n    for (; it != last; ++it) {\n        if (*it ==\
    \ current) {\n            ++count;\n        } else {\n            result.emplace_back(current,\
    \ count);\n            current = *it;\n            count = 1;\n        }\n   \
    \ }\n    result.emplace_back(current, count);\n    return result;\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 1 \"algo/sequence/subset_sum.hpp\"\
    \n\n\n\n#line 8 \"algo/sequence/subset_sum.hpp\"\n\nnamespace m1une {\nnamespace\
    \ algo {\n\nnamespace internal {\n\ntemplate <typename T>\nstd::vector<T> enumerate_sorted_subset_sums(\n\
    \    const std::vector<T>& values,\n    int left,\n    int right\n) {\n    std::vector<T>\
    \ sums(1, T{});\n    std::vector<T> merged;\n\n    for (int i = left; i < right;\
    \ ++i) {\n        const std::size_t size = sums.size();\n        merged.clear();\n\
    \        merged.reserve(size * 2);\n\n        std::size_t without = 0;\n     \
    \   std::size_t with = 0;\n        while (without < size && with < size) {\n \
    \           const T with_current = sums[with] + values[i];\n            if (with_current\
    \ < sums[without]) {\n                merged.push_back(with_current);\n      \
    \          ++with;\n            } else {\n                merged.push_back(sums[without]);\n\
    \                ++without;\n            }\n        }\n        while (without\
    \ < size) {\n            merged.push_back(sums[without]);\n            ++without;\n\
    \        }\n        while (with < size) {\n            merged.push_back(sums[with]\
    \ + values[i]);\n            ++with;\n        }\n        sums.swap(merged);\n\
    \    }\n\n    return sums;\n}\n\n}  // namespace internal\n\n// Returns the sorted\
    \ subset sums of values[0, n / 2) and values[n / 2, n).\ntemplate <typename T>\n\
    std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(\n    const\
    \ std::vector<T>& values\n) {\n    const int n = int(values.size());\n    const\
    \ int middle = n / 2;\n    return {\n        internal::enumerate_sorted_subset_sums(values,\
    \ 0, middle),\n        internal::enumerate_sorted_subset_sums(values, middle,\
    \ n)\n    };\n}\n\n// Returns the maximum subset sum not exceeding limit.\ntemplate\
    \ <typename T>\nT maximum_subset_sum(const std::vector<T>& values, const T& limit)\
    \ {\n    assert(!(limit < T{}));\n    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);\n\
    \n    T answer{};\n    std::size_t right_count = right_sums.size();\n    for (const\
    \ T& left : left_sums) {\n        while (\n            right_count > 0 &&\n  \
    \          limit < left + right_sums[right_count - 1]\n        ) {\n         \
    \   --right_count;\n        }\n        if (right_count == 0) break;\n\n      \
    \  const T candidate = left + right_sums[right_count - 1];\n        if (answer\
    \ < candidate) answer = candidate;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 8 \"algo/sequence/all.hpp\"\n\n\n#line\
    \ 8 \"algo/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ALL_HPP

    #define M1UNE_ALGO_ALL_HPP 1


    #include "enumeration/all.hpp"

    #include "offline/all.hpp"

    #include "search/all.hpp"

    #include "sequence/all.hpp"


    #endif  // M1UNE_ALGO_ALL_HPP

    '
  dependsOn:
  - algo/enumeration/all.hpp
  - algo/enumeration/gray_code.hpp
  - algo/offline/all.hpp
  - algo/offline/mo.hpp
  - algo/search/all.hpp
  - algo/search/bisect.hpp
  - algo/sequence/all.hpp
  - algo/sequence/inversion_count.hpp
  - algo/sequence/lis.hpp
  - algo/sequence/run_length_encoding.hpp
  - algo/sequence/subset_sum.hpp
  isVerificationFile: false
  path: algo/all.hpp
  requiredBy: []
  timestamp: '2026-07-07 21:49:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/all.hpp
layout: document
title: Algorithms All
---

## Overview

`algo/all.hpp` includes one-shot, domain-neutral algorithms. The public
namespace is `m1une::algo`; subdirectories are only browsing categories.

Convex optimization helpers live under `convex/`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/sequence/all.hpp` | Sequence and array algorithms such as LIS, inversion count, run-length encoding, and subset sum. |
| `algo/search/all.hpp` | Search-over-answer helpers such as integer and floating-point binary search. |
| `algo/offline/all.hpp` | Offline query processing such as Mo's algorithm. |
| `algo/enumeration/all.hpp` | Combinatorial traversal helpers such as Gray-code enumeration. |
