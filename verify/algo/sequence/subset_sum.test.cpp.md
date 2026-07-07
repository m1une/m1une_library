---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/subset_sum.hpp
    title: Meet-in-the-Middle Subset Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A
  bundledCode: "#line 1 \"verify/algo/sequence/subset_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A\"\n\n\
    #include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#line 1 \"algo/sequence/subset_sum.hpp\"\n\n\n\n#line 5 \"\
    algo/sequence/subset_sum.hpp\"\n#include <cstddef>\n#include <utility>\n#line\
    \ 8 \"algo/sequence/subset_sum.hpp\"\n\nnamespace m1une {\nnamespace sequence\
    \ {\n\nnamespace internal {\n\ntemplate <typename T>\nstd::vector<T> enumerate_sorted_subset_sums(\n\
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
    \ sequence\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/sequence/subset_sum.test.cpp\"\
    \n\nstd::vector<long long> naive_subset_sums(const std::vector<long long>& values)\
    \ {\n    std::vector<long long> sums(1, 0);\n    for (long long value : values)\
    \ {\n        const std::size_t size = sums.size();\n        for (std::size_t mask\
    \ = 0; mask < size; ++mask) {\n            sums.push_back(sums[mask] + value);\n\
    \        }\n    }\n    return sums;\n}\n\nlong long naive_maximum_subset_sum(\n\
    \    const std::vector<long long>& values,\n    long long limit\n) {\n    long\
    \ long answer = 0;\n    for (long long sum : naive_subset_sums(values)) {\n  \
    \      if (sum <= limit) answer = std::max(answer, sum);\n    }\n    return answer;\n\
    }\n\nvoid basic_test() {\n    const std::vector<long long> empty;\n    auto [empty_left,\
    \ empty_right] =\n        m1une::sequence::enumerate_half_subset_sums(empty);\n\
    \    assert(empty_left == std::vector<long long>{0});\n    assert(empty_right\
    \ == std::vector<long long>{0});\n    assert(m1une::sequence::maximum_subset_sum(empty,\
    \ 10LL) == 0);\n\n    const std::vector<long long> values = {3, -1, 3};\n    auto\
    \ [left_sums, right_sums] =\n        m1une::sequence::enumerate_half_subset_sums(values);\n\
    \    assert(left_sums == std::vector<long long>({0, 3}));\n    assert(right_sums\
    \ == std::vector<long long>({-1, 0, 2, 3}));\n    assert(m1une::sequence::maximum_subset_sum(values,\
    \ 4LL) == 3);\n}\n\nvoid randomized_test() {\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 200; ++test) {\n        const int n = int(random()\
    \ % 16);\n        std::vector<long long> values(n);\n        for (long long& value\
    \ : values) {\n            value = int(random() % 21) - 10;\n        }\n     \
    \   const long long limit = random() % 101;\n\n        auto [left_sums, right_sums]\
    \ =\n            m1une::sequence::enumerate_half_subset_sums(values);\n      \
    \  assert(std::is_sorted(left_sums.begin(), left_sums.end()));\n        assert(std::is_sorted(right_sums.begin(),\
    \ right_sums.end()));\n        assert(left_sums.size() == (std::size_t(1) << (n\
    \ / 2)));\n        assert(right_sums.size() == (std::size_t(1) << (n - n / 2)));\n\
    \n        std::vector<long long> actual;\n        actual.reserve(left_sums.size()\
    \ * right_sums.size());\n        for (long long left : left_sums) {\n        \
    \    for (long long right : right_sums) {\n                actual.push_back(left\
    \ + right);\n            }\n        }\n        std::vector<long long> expected\
    \ = naive_subset_sums(values);\n        std::sort(actual.begin(), actual.end());\n\
    \        std::sort(expected.begin(), expected.end());\n        assert(actual ==\
    \ expected);\n\n        assert(\n            m1une::sequence::maximum_subset_sum(values,\
    \ limit) ==\n            naive_maximum_subset_sum(values, limit)\n        );\n\
    \    }\n}\n\nint main() {\n    basic_test();\n    randomized_test();\n\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<long long> values(n);\n    for (long\
    \ long& value : values) std::cin >> value;\n\n    int query_count;\n    std::cin\
    \ >> query_count;\n    while (query_count--) {\n        long long target;\n  \
    \      std::cin >> target;\n        const bool found =\n            m1une::sequence::maximum_subset_sum(values,\
    \ target) == target;\n        std::cout << (found ? \"yes\" : \"no\") << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_A\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#include \"../../../algo/sequence/subset_sum.hpp\"\n\nstd::vector<long\
    \ long> naive_subset_sums(const std::vector<long long>& values) {\n    std::vector<long\
    \ long> sums(1, 0);\n    for (long long value : values) {\n        const std::size_t\
    \ size = sums.size();\n        for (std::size_t mask = 0; mask < size; ++mask)\
    \ {\n            sums.push_back(sums[mask] + value);\n        }\n    }\n    return\
    \ sums;\n}\n\nlong long naive_maximum_subset_sum(\n    const std::vector<long\
    \ long>& values,\n    long long limit\n) {\n    long long answer = 0;\n    for\
    \ (long long sum : naive_subset_sums(values)) {\n        if (sum <= limit) answer\
    \ = std::max(answer, sum);\n    }\n    return answer;\n}\n\nvoid basic_test()\
    \ {\n    const std::vector<long long> empty;\n    auto [empty_left, empty_right]\
    \ =\n        m1une::sequence::enumerate_half_subset_sums(empty);\n    assert(empty_left\
    \ == std::vector<long long>{0});\n    assert(empty_right == std::vector<long long>{0});\n\
    \    assert(m1une::sequence::maximum_subset_sum(empty, 10LL) == 0);\n\n    const\
    \ std::vector<long long> values = {3, -1, 3};\n    auto [left_sums, right_sums]\
    \ =\n        m1une::sequence::enumerate_half_subset_sums(values);\n    assert(left_sums\
    \ == std::vector<long long>({0, 3}));\n    assert(right_sums == std::vector<long\
    \ long>({-1, 0, 2, 3}));\n    assert(m1une::sequence::maximum_subset_sum(values,\
    \ 4LL) == 3);\n}\n\nvoid randomized_test() {\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 200; ++test) {\n        const int n = int(random()\
    \ % 16);\n        std::vector<long long> values(n);\n        for (long long& value\
    \ : values) {\n            value = int(random() % 21) - 10;\n        }\n     \
    \   const long long limit = random() % 101;\n\n        auto [left_sums, right_sums]\
    \ =\n            m1une::sequence::enumerate_half_subset_sums(values);\n      \
    \  assert(std::is_sorted(left_sums.begin(), left_sums.end()));\n        assert(std::is_sorted(right_sums.begin(),\
    \ right_sums.end()));\n        assert(left_sums.size() == (std::size_t(1) << (n\
    \ / 2)));\n        assert(right_sums.size() == (std::size_t(1) << (n - n / 2)));\n\
    \n        std::vector<long long> actual;\n        actual.reserve(left_sums.size()\
    \ * right_sums.size());\n        for (long long left : left_sums) {\n        \
    \    for (long long right : right_sums) {\n                actual.push_back(left\
    \ + right);\n            }\n        }\n        std::vector<long long> expected\
    \ = naive_subset_sums(values);\n        std::sort(actual.begin(), actual.end());\n\
    \        std::sort(expected.begin(), expected.end());\n        assert(actual ==\
    \ expected);\n\n        assert(\n            m1une::sequence::maximum_subset_sum(values,\
    \ limit) ==\n            naive_maximum_subset_sum(values, limit)\n        );\n\
    \    }\n}\n\nint main() {\n    basic_test();\n    randomized_test();\n\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<long long> values(n);\n    for (long\
    \ long& value : values) std::cin >> value;\n\n    int query_count;\n    std::cin\
    \ >> query_count;\n    while (query_count--) {\n        long long target;\n  \
    \      std::cin >> target;\n        const bool found =\n            m1une::sequence::maximum_subset_sum(values,\
    \ target) == target;\n        std::cout << (found ? \"yes\" : \"no\") << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - algo/sequence/subset_sum.hpp
  isVerificationFile: true
  path: verify/algo/sequence/subset_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 14:26:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/sequence/subset_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/sequence/subset_sum.test.cpp
- /verify/verify/algo/sequence/subset_sum.test.cpp.html
title: verify/algo/sequence/subset_sum.test.cpp
---
