---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/segtree_range.hpp
    title: Segment Tree Range Split
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"verify/algo/enumeration/segtree_range.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n#line 1 \"algo/enumeration/segtree_range.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\
    \n// Splits [left, right) into maximal segment-tree ranges from left to right.\n\
    template <std::integral Int>\nrequires(!std::same_as<std::remove_cv_t<Int>, bool>)\n\
    std::vector<std::pair<Int, Int>> split_segtree_range(Int left, Int right) {\n\
    \    if constexpr (std::signed_integral<Int>) assert(Int(0) <= left);\n    assert(left\
    \ <= right);\n    if constexpr (std::signed_integral<Int>) {\n        if (left\
    \ < 0) return {};\n    }\n    if (right < left) return {};\n\n    using UInt =\
    \ std::make_unsigned_t<Int>;\n    UInt position = static_cast<UInt>(left);\n \
    \   const UInt end = static_cast<UInt>(right);\n    std::vector<std::pair<Int,\
    \ Int>> result;\n    if (position == end) return result;\n    result.reserve(2\
    \ * std::bit_width(end - position));\n\n    while (position < end) {\n       \
    \ UInt length = std::bit_floor(end - position);\n        if (position != 0) {\n\
    \            const UInt alignment = position & (~position + UInt(1));\n      \
    \      if (alignment < length) length = alignment;\n        }\n        const UInt\
    \ next = position + length;\n        result.emplace_back(\n            static_cast<Int>(position),\
    \ static_cast<Int>(next)\n        );\n        position = next;\n    }\n    return\
    \ result;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n#line 4 \"verify/algo/enumeration/segtree_range.test.cpp\"\
    \n\n#line 7 \"verify/algo/enumeration/segtree_range.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <limits>\n#include <random>\n#line 13 \"verify/algo/enumeration/segtree_range.test.cpp\"\
    \n\nnamespace {\n\nvoid naive_split_impl(\n    int query_left, int query_right,\
    \ int left, int right,\n    std::vector<std::pair<int, int>>& result\n) {\n  \
    \  if (query_right <= left || right <= query_left) return;\n    if (query_left\
    \ <= left && right <= query_right) {\n        result.emplace_back(left, right);\n\
    \        return;\n    }\n    const int middle = (left + right) / 2;\n    naive_split_impl(query_left,\
    \ query_right, left, middle, result);\n    naive_split_impl(query_left, query_right,\
    \ middle, right, result);\n}\n\nstd::vector<std::pair<int, int>> naive_split(int\
    \ left, int right) {\n    std::vector<std::pair<int, int>> result;\n    if (left\
    \ == right) return result;\n    int size = 1;\n    while (size < right) size *=\
    \ 2;\n    naive_split_impl(left, right, 0, size, result);\n    return result;\n\
    }\n\nvoid check_range(int left, int right) {\n    const auto ranges = m1une::algo::split_segtree_range(left,\
    \ right);\n    int position = left;\n    for (auto [range_left, range_right] :\
    \ ranges) {\n        assert(range_left == position);\n        assert(range_left\
    \ < range_right);\n        const unsigned length = unsigned(range_right - range_left);\n\
    \        assert(std::has_single_bit(length));\n        assert(range_left % int(length)\
    \ == 0);\n\n        const int parent_length = 2 * int(length);\n        const\
    \ int parent_left = range_left / parent_length * parent_length;\n        assert(!(left\
    \ <= parent_left &&\n                 parent_left + parent_length <= right));\n\
    \        position = range_right;\n    }\n    assert(position == right);\n    assert(ranges\
    \ == naive_split(left, right));\n}\n\nvoid fixed_tests() {\n    std::vector<std::pair<int,\
    \ int>> expected;\n    expected.emplace_back(3, 4);\n    expected.emplace_back(4,\
    \ 8);\n    expected.emplace_back(8, 12);\n    expected.emplace_back(12, 13);\n\
    \    assert(m1une::algo::split_segtree_range(3, 13) == expected);\n    assert(m1une::algo::split_segtree_range(5,\
    \ 5).empty());\n\n    const auto whole = m1une::algo::split_segtree_range(0, 16);\n\
    \    assert(whole.size() == 1);\n    assert(whole.front().first == 0);\n    assert(whole.front().second\
    \ == 16);\n\n    const auto wide = m1une::algo::split_segtree_range(\n       \
    \ std::uint64_t(0), std::numeric_limits<std::uint64_t>::max()\n    );\n    assert(wide.size()\
    \ == 64);\n    assert(wide.front().first == 0);\n    assert(wide.front().second\
    \ == (std::uint64_t(1) << 63));\n    assert(wide.back().first ==\n           std::numeric_limits<std::uint64_t>::max()\
    \ - 1);\n    assert(wide.back().second == std::numeric_limits<std::uint64_t>::max());\n\
    }\n\nvoid exhaustive_tests() {\n    for (int right = 0; right <= 256; ++right)\
    \ {\n        for (int left = 0; left <= right; ++left) {\n            check_range(left,\
    \ right);\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::mt19937\
    \ random(0x243f6a88U);\n    for (int trial = 0; trial < 20000; ++trial) {\n  \
    \      int left = int(random() % (1U << 20));\n        int right = int(random()\
    \ % (1U << 20));\n        if (left > right) std::swap(left, right);\n        check_range(left,\
    \ right);\n    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n \
    \   exhaustive_tests();\n    randomized_tests();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, query_count;\n    if (!(std::cin >>\
    \ n >> query_count)) return 0;\n    std::vector<long long> prefix_sum(n + 1);\n\
    \    for (int i = 0; i < n; ++i) {\n        long long value;\n        std::cin\
    \ >> value;\n        prefix_sum[i + 1] = prefix_sum[i] + value;\n    }\n\n   \
    \ while (query_count--) {\n        int left, right;\n        std::cin >> left\
    \ >> right;\n        long long answer = 0;\n        for (auto [range_left, range_right]\
    \ :\n             m1une::algo::split_segtree_range(left, right)) {\n         \
    \   answer += prefix_sum[range_right] - prefix_sum[range_left];\n        }\n \
    \       std::cout << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"../../../algo/enumeration/segtree_range.hpp\"\n\n#include <bit>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <limits>\n#include\
    \ <random>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nvoid naive_split_impl(\n\
    \    int query_left, int query_right, int left, int right,\n    std::vector<std::pair<int,\
    \ int>>& result\n) {\n    if (query_right <= left || right <= query_left) return;\n\
    \    if (query_left <= left && right <= query_right) {\n        result.emplace_back(left,\
    \ right);\n        return;\n    }\n    const int middle = (left + right) / 2;\n\
    \    naive_split_impl(query_left, query_right, left, middle, result);\n    naive_split_impl(query_left,\
    \ query_right, middle, right, result);\n}\n\nstd::vector<std::pair<int, int>>\
    \ naive_split(int left, int right) {\n    std::vector<std::pair<int, int>> result;\n\
    \    if (left == right) return result;\n    int size = 1;\n    while (size < right)\
    \ size *= 2;\n    naive_split_impl(left, right, 0, size, result);\n    return\
    \ result;\n}\n\nvoid check_range(int left, int right) {\n    const auto ranges\
    \ = m1une::algo::split_segtree_range(left, right);\n    int position = left;\n\
    \    for (auto [range_left, range_right] : ranges) {\n        assert(range_left\
    \ == position);\n        assert(range_left < range_right);\n        const unsigned\
    \ length = unsigned(range_right - range_left);\n        assert(std::has_single_bit(length));\n\
    \        assert(range_left % int(length) == 0);\n\n        const int parent_length\
    \ = 2 * int(length);\n        const int parent_left = range_left / parent_length\
    \ * parent_length;\n        assert(!(left <= parent_left &&\n                \
    \ parent_left + parent_length <= right));\n        position = range_right;\n \
    \   }\n    assert(position == right);\n    assert(ranges == naive_split(left,\
    \ right));\n}\n\nvoid fixed_tests() {\n    std::vector<std::pair<int, int>> expected;\n\
    \    expected.emplace_back(3, 4);\n    expected.emplace_back(4, 8);\n    expected.emplace_back(8,\
    \ 12);\n    expected.emplace_back(12, 13);\n    assert(m1une::algo::split_segtree_range(3,\
    \ 13) == expected);\n    assert(m1une::algo::split_segtree_range(5, 5).empty());\n\
    \n    const auto whole = m1une::algo::split_segtree_range(0, 16);\n    assert(whole.size()\
    \ == 1);\n    assert(whole.front().first == 0);\n    assert(whole.front().second\
    \ == 16);\n\n    const auto wide = m1une::algo::split_segtree_range(\n       \
    \ std::uint64_t(0), std::numeric_limits<std::uint64_t>::max()\n    );\n    assert(wide.size()\
    \ == 64);\n    assert(wide.front().first == 0);\n    assert(wide.front().second\
    \ == (std::uint64_t(1) << 63));\n    assert(wide.back().first ==\n           std::numeric_limits<std::uint64_t>::max()\
    \ - 1);\n    assert(wide.back().second == std::numeric_limits<std::uint64_t>::max());\n\
    }\n\nvoid exhaustive_tests() {\n    for (int right = 0; right <= 256; ++right)\
    \ {\n        for (int left = 0; left <= right; ++left) {\n            check_range(left,\
    \ right);\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::mt19937\
    \ random(0x243f6a88U);\n    for (int trial = 0; trial < 20000; ++trial) {\n  \
    \      int left = int(random() % (1U << 20));\n        int right = int(random()\
    \ % (1U << 20));\n        if (left > right) std::swap(left, right);\n        check_range(left,\
    \ right);\n    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n \
    \   exhaustive_tests();\n    randomized_tests();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n, query_count;\n    if (!(std::cin >>\
    \ n >> query_count)) return 0;\n    std::vector<long long> prefix_sum(n + 1);\n\
    \    for (int i = 0; i < n; ++i) {\n        long long value;\n        std::cin\
    \ >> value;\n        prefix_sum[i + 1] = prefix_sum[i] + value;\n    }\n\n   \
    \ while (query_count--) {\n        int left, right;\n        std::cin >> left\
    \ >> right;\n        long long answer = 0;\n        for (auto [range_left, range_right]\
    \ :\n             m1une::algo::split_segtree_range(left, right)) {\n         \
    \   answer += prefix_sum[range_right] - prefix_sum[range_left];\n        }\n \
    \       std::cout << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - algo/enumeration/segtree_range.hpp
  isVerificationFile: true
  path: verify/algo/enumeration/segtree_range.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 01:43:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/enumeration/segtree_range.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/enumeration/segtree_range.test.cpp
- /verify/verify/algo/enumeration/segtree_range.test.cpp.html
title: verify/algo/enumeration/segtree_range.test.cpp
---
