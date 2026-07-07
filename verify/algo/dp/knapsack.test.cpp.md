---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/dp/knapsack.hpp
    title: Knapsack Helpers
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/algo/dp/knapsack.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"algo/dp/knapsack.hpp\"\n\n\n\n#line 6 \"algo/dp/knapsack.hpp\"\
    \n#include <cstddef>\n#include <deque>\n#line 10 \"algo/dp/knapsack.hpp\"\n\n\
    namespace m1une {\nnamespace algo {\n\ninline std::vector<char> subset_sum_reachable(const\
    \ std::vector<int>& weights, int limit) {\n    assert(0 <= limit);\n    using\
    \ Word = unsigned long long;\n    constexpr int word_bits = std::numeric_limits<Word>::digits;\n\
    \n    const std::size_t bit_count = std::size_t(limit) + 1;\n    std::vector<Word>\
    \ bits((bit_count + word_bits - 1) / word_bits, Word(0));\n    bits[0] = Word(1);\n\
    \n    auto trim = [&]() {\n        const int extra = int(bit_count % word_bits);\n\
    \        if (extra != 0) {\n            bits.back() &= (Word(1) << extra) - Word(1);\n\
    \        }\n    };\n\n    for (int weight : weights) {\n        assert(0 <= weight);\n\
    \        if (weight == 0 || limit < weight) continue;\n\n        const std::size_t\
    \ word_shift = std::size_t(weight / word_bits);\n        const int bit_shift =\
    \ weight % word_bits;\n        for (std::size_t i = bits.size() - word_shift;\
    \ i-- > 0;) {\n            const Word source = bits[i];\n            if (source\
    \ == Word(0)) continue;\n            const std::size_t target = i + word_shift;\n\
    \            bits[target] |= source << bit_shift;\n            if (bit_shift !=\
    \ 0 && target + 1 < bits.size()) {\n                bits[target + 1] |= source\
    \ >> (word_bits - bit_shift);\n            }\n        }\n        trim();\n   \
    \ }\n\n    std::vector<char> reachable(std::size_t(limit) + 1, 0);\n    for (int\
    \ sum = 0; sum <= limit; ++sum) {\n        reachable[sum] = char((bits[std::size_t(sum\
    \ / word_bits)] >> (sum % word_bits)) & Word(1));\n    }\n    return reachable;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> zero_one_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest() /\
    \ Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(0 <=\
    \ capacity);\n\n    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);\n\
    \    dp[0] = Value{};\n    for (std::size_t item = 0; item < weights.size(); ++item)\
    \ {\n        const int weight = weights[item];\n        assert(0 <= weight);\n\
    \        for (int current = capacity; weight <= current; --current) {\n      \
    \      if (dp[current - weight] == neg_inf) continue;\n            dp[current]\
    \ = std::max(dp[current], dp[current - weight] + values[item]);\n        }\n \
    \   }\n\n    for (int current = 1; current <= capacity; ++current) {\n       \
    \ dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> bounded_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest()\
    \ / Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(weights.size()\
    \ == counts.size());\n    assert(0 <= capacity);\n\n    std::vector<Value> dp(std::size_t(capacity)\
    \ + 1, neg_inf);\n    dp[0] = Value{};\n\n    for (std::size_t item = 0; item\
    \ < weights.size(); ++item) {\n        const int weight = weights[item];\n   \
    \     const Value value = values[item];\n        const int count = counts[item];\n\
    \        assert(0 <= weight);\n        assert(0 <= count);\n        if (count\
    \ == 0) continue;\n\n        if (weight == 0) {\n            if (Value{} < value)\
    \ {\n                const Value gain = value * Value(count);\n              \
    \  for (Value& current : dp) {\n                    if (current != neg_inf) current\
    \ += gain;\n                }\n            }\n            continue;\n        }\n\
    \n        std::vector<Value> next = dp;\n        for (int residue = 0; residue\
    \ < weight && residue <= capacity; ++residue) {\n            std::deque<int> indices;\n\
    \            std::deque<Value> bases;\n            int k = 0;\n            for\
    \ (int current = residue; current <= capacity; current += weight, ++k) {\n   \
    \             if (dp[current] != neg_inf) {\n                    const Value base\
    \ = dp[current] - Value(k) * value;\n                    while (!bases.empty()\
    \ && bases.back() <= base) {\n                        bases.pop_back();\n    \
    \                    indices.pop_back();\n                    }\n            \
    \        bases.push_back(base);\n                    indices.push_back(k);\n \
    \               }\n\n                while (!indices.empty() && indices.front()\
    \ < k - count) {\n                    indices.pop_front();\n                 \
    \   bases.pop_front();\n                }\n                if (!bases.empty())\
    \ {\n                    next[current] = std::max(next[current], bases.front()\
    \ + Value(k) * value);\n                }\n            }\n        }\n        dp.swap(next);\n\
    \    }\n\n    for (int current = 1; current <= capacity; ++current) {\n      \
    \  dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Weight = long long>\nstd::vector<Weight> zero_one_knapsack_min_weight_for_value(\n\
    \    const std::vector<Weight>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit,\n    Weight inf = std::numeric_limits<Weight>::max() / Weight(4)\n\
    ) {\n    assert(weights.size() == values.size());\n    assert(0 <= value_limit);\n\
    \n    std::vector<Weight> dp(std::size_t(value_limit) + 1, inf);\n    dp[0] =\
    \ Weight{};\n    for (std::size_t item = 0; item < weights.size(); ++item) {\n\
    \        assert(Weight{} <= weights[item]);\n        assert(0 <= values[item]);\n\
    \        for (int value = value_limit; values[item] <= value; --value) {\n   \
    \         if (dp[value - values[item]] == inf) continue;\n            dp[value]\
    \ = std::min(dp[value], dp[value - values[item]] + weights[item]);\n        }\n\
    \    }\n    return dp;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n\
    #line 10 \"verify/algo/dp/knapsack.test.cpp\"\n\nstd::vector<char> naive_subset_sum(const\
    \ std::vector<int>& weights, int limit) {\n    std::vector<char> reachable(limit\
    \ + 1, 0);\n    reachable[0] = 1;\n    for (int weight : weights) {\n        for\
    \ (int sum = limit; weight <= sum; --sum) {\n            if (reachable[sum - weight])\
    \ reachable[sum] = 1;\n        }\n    }\n    return reachable;\n}\n\nstd::vector<long\
    \ long> naive_zero_one_max_value(\n    const std::vector<int>& weights,\n    const\
    \ std::vector<long long>& values,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n   \
    \ for (int mask = 0; mask < (1 << n); ++mask) {\n        int weight = 0;\n   \
    \     long long value = 0;\n        for (int i = 0; i < n; ++i) {\n          \
    \  if ((mask >> i) & 1) {\n                weight += weights[i];\n           \
    \     value += values[i];\n            }\n        }\n        if (weight <= capacity)\
    \ {\n            for (int current = weight; current <= capacity; ++current) {\n\
    \                result[current] = std::max(result[current], value);\n       \
    \     }\n        }\n    }\n    return result;\n}\n\nstd::vector<long long> naive_bounded_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<long long>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n\n \
    \   auto dfs = [&](auto& self, int item, int weight, long long value) -> void\
    \ {\n        if (item == n) {\n            if (weight <= capacity) {\n       \
    \         for (int current = weight; current <= capacity; ++current) {\n     \
    \               result[current] = std::max(result[current], value);\n        \
    \        }\n            }\n            return;\n        }\n        for (int take\
    \ = 0; take <= counts[item]; ++take) {\n            self(self, item + 1, weight\
    \ + weights[item] * take, value + values[item] * take);\n        }\n    };\n \
    \   dfs(dfs, 0, 0, 0);\n    return result;\n}\n\nstd::vector<long long> naive_min_weight_for_value(\n\
    \    const std::vector<long long>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit\n) {\n    const long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n    std::vector<long long> result(value_limit + 1, inf);\n\
    \    const int n = int(weights.size());\n    for (int mask = 0; mask < (1 << n);\
    \ ++mask) {\n        long long weight = 0;\n        int value = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) {\n            \
    \    weight += weights[i];\n                value += values[i];\n            }\n\
    \        }\n        if (value <= value_limit) {\n            result[value] = std::min(result[value],\
    \ weight);\n        }\n    }\n    return result;\n}\n\nvoid test_subset_sum()\
    \ {\n    for (int n = 0; n <= 8; ++n) {\n        std::vector<int> weights(n);\n\
    \        for (int seed = 0; seed < 60; ++seed) {\n            for (int i = 0;\
    \ i < n; ++i) {\n                weights[i] = (seed * 13 + i * 7) % 10;\n    \
    \        }\n            assert(m1une::algo::subset_sum_reachable(weights, 30)\
    \ == naive_subset_sum(weights, 30));\n        }\n    }\n}\n\nvoid test_zero_one_knapsack()\
    \ {\n    std::vector<int> weights = {2, 3, 4, 5};\n    std::vector<long long>\
    \ values = {4, 5, 7, 8};\n    assert(\n        m1une::algo::zero_one_knapsack_max_value(weights,\
    \ values, 10)\n        == naive_zero_one_max_value(weights, values, 10)\n    );\n\
    }\n\nvoid test_bounded_knapsack() {\n    std::vector<int> weights = {0, 2, 3};\n\
    \    std::vector<long long> values = {5, 3, 4};\n    std::vector<int> counts =\
    \ {2, 3, 2};\n    assert(\n        m1une::algo::bounded_knapsack_max_value(weights,\
    \ values, counts, 10)\n        == naive_bounded_max_value(weights, values, counts,\
    \ 10)\n    );\n}\n\nvoid test_min_weight_for_value() {\n    std::vector<long long>\
    \ weights = {3, 2, 5, 7};\n    std::vector<int> values = {4, 3, 6, 8};\n    assert(\n\
    \        m1une::algo::zero_one_knapsack_min_weight_for_value(weights, values,\
    \ 20)\n        == naive_min_weight_for_value(weights, values, 20)\n    );\n}\n\
    \nint main() {\n    test_subset_sum();\n    test_zero_one_knapsack();\n    test_bounded_knapsack();\n\
    \    test_min_weight_for_value();\n\n    long long a, b;\n    std::cin >> a >>\
    \ b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <limits>\n#include <vector>\n\
    \n#include \"../../../algo/dp/knapsack.hpp\"\n\nstd::vector<char> naive_subset_sum(const\
    \ std::vector<int>& weights, int limit) {\n    std::vector<char> reachable(limit\
    \ + 1, 0);\n    reachable[0] = 1;\n    for (int weight : weights) {\n        for\
    \ (int sum = limit; weight <= sum; --sum) {\n            if (reachable[sum - weight])\
    \ reachable[sum] = 1;\n        }\n    }\n    return reachable;\n}\n\nstd::vector<long\
    \ long> naive_zero_one_max_value(\n    const std::vector<int>& weights,\n    const\
    \ std::vector<long long>& values,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n   \
    \ for (int mask = 0; mask < (1 << n); ++mask) {\n        int weight = 0;\n   \
    \     long long value = 0;\n        for (int i = 0; i < n; ++i) {\n          \
    \  if ((mask >> i) & 1) {\n                weight += weights[i];\n           \
    \     value += values[i];\n            }\n        }\n        if (weight <= capacity)\
    \ {\n            for (int current = weight; current <= capacity; ++current) {\n\
    \                result[current] = std::max(result[current], value);\n       \
    \     }\n        }\n    }\n    return result;\n}\n\nstd::vector<long long> naive_bounded_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<long long>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n\n \
    \   auto dfs = [&](auto& self, int item, int weight, long long value) -> void\
    \ {\n        if (item == n) {\n            if (weight <= capacity) {\n       \
    \         for (int current = weight; current <= capacity; ++current) {\n     \
    \               result[current] = std::max(result[current], value);\n        \
    \        }\n            }\n            return;\n        }\n        for (int take\
    \ = 0; take <= counts[item]; ++take) {\n            self(self, item + 1, weight\
    \ + weights[item] * take, value + values[item] * take);\n        }\n    };\n \
    \   dfs(dfs, 0, 0, 0);\n    return result;\n}\n\nstd::vector<long long> naive_min_weight_for_value(\n\
    \    const std::vector<long long>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit\n) {\n    const long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n    std::vector<long long> result(value_limit + 1, inf);\n\
    \    const int n = int(weights.size());\n    for (int mask = 0; mask < (1 << n);\
    \ ++mask) {\n        long long weight = 0;\n        int value = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) {\n            \
    \    weight += weights[i];\n                value += values[i];\n            }\n\
    \        }\n        if (value <= value_limit) {\n            result[value] = std::min(result[value],\
    \ weight);\n        }\n    }\n    return result;\n}\n\nvoid test_subset_sum()\
    \ {\n    for (int n = 0; n <= 8; ++n) {\n        std::vector<int> weights(n);\n\
    \        for (int seed = 0; seed < 60; ++seed) {\n            for (int i = 0;\
    \ i < n; ++i) {\n                weights[i] = (seed * 13 + i * 7) % 10;\n    \
    \        }\n            assert(m1une::algo::subset_sum_reachable(weights, 30)\
    \ == naive_subset_sum(weights, 30));\n        }\n    }\n}\n\nvoid test_zero_one_knapsack()\
    \ {\n    std::vector<int> weights = {2, 3, 4, 5};\n    std::vector<long long>\
    \ values = {4, 5, 7, 8};\n    assert(\n        m1une::algo::zero_one_knapsack_max_value(weights,\
    \ values, 10)\n        == naive_zero_one_max_value(weights, values, 10)\n    );\n\
    }\n\nvoid test_bounded_knapsack() {\n    std::vector<int> weights = {0, 2, 3};\n\
    \    std::vector<long long> values = {5, 3, 4};\n    std::vector<int> counts =\
    \ {2, 3, 2};\n    assert(\n        m1une::algo::bounded_knapsack_max_value(weights,\
    \ values, counts, 10)\n        == naive_bounded_max_value(weights, values, counts,\
    \ 10)\n    );\n}\n\nvoid test_min_weight_for_value() {\n    std::vector<long long>\
    \ weights = {3, 2, 5, 7};\n    std::vector<int> values = {4, 3, 6, 8};\n    assert(\n\
    \        m1une::algo::zero_one_knapsack_min_weight_for_value(weights, values,\
    \ 20)\n        == naive_min_weight_for_value(weights, values, 20)\n    );\n}\n\
    \nint main() {\n    test_subset_sum();\n    test_zero_one_knapsack();\n    test_bounded_knapsack();\n\
    \    test_min_weight_for_value();\n\n    long long a, b;\n    std::cin >> a >>\
    \ b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/dp/knapsack.hpp
  isVerificationFile: true
  path: verify/algo/dp/knapsack.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/dp/knapsack.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/dp/knapsack.test.cpp
- /verify/verify/algo/dp/knapsack.test.cpp.html
title: verify/algo/dp/knapsack.test.cpp
---
