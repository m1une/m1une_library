---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/dp/all.hpp
    title: DP Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/dp/knapsack.test.cpp
    title: verify/algo/dp/knapsack.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/dp/knapsack.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <deque>\n#include <limits>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace algo {\n\ninline std::vector<char>\
    \ subset_sum_reachable(const std::vector<int>& weights, int limit) {\n    assert(0\
    \ <= limit);\n    using Word = unsigned long long;\n    constexpr int word_bits\
    \ = std::numeric_limits<Word>::digits;\n\n    const std::size_t bit_count = std::size_t(limit)\
    \ + 1;\n    std::vector<Word> bits((bit_count + word_bits - 1) / word_bits, Word(0));\n\
    \    bits[0] = Word(1);\n\n    auto trim = [&]() {\n        const int extra =\
    \ int(bit_count % word_bits);\n        if (extra != 0) {\n            bits.back()\
    \ &= (Word(1) << extra) - Word(1);\n        }\n    };\n\n    for (int weight :\
    \ weights) {\n        assert(0 <= weight);\n        if (weight == 0 || limit <\
    \ weight) continue;\n\n        const std::size_t word_shift = std::size_t(weight\
    \ / word_bits);\n        const int bit_shift = weight % word_bits;\n        for\
    \ (std::size_t i = bits.size() - word_shift; i-- > 0;) {\n            const Word\
    \ source = bits[i];\n            if (source == Word(0)) continue;\n          \
    \  const std::size_t target = i + word_shift;\n            bits[target] |= source\
    \ << bit_shift;\n            if (bit_shift != 0 && target + 1 < bits.size()) {\n\
    \                bits[target + 1] |= source >> (word_bits - bit_shift);\n    \
    \        }\n        }\n        trim();\n    }\n\n    std::vector<char> reachable(std::size_t(limit)\
    \ + 1, 0);\n    for (int sum = 0; sum <= limit; ++sum) {\n        reachable[sum]\
    \ = char((bits[std::size_t(sum / word_bits)] >> (sum % word_bits)) & Word(1));\n\
    \    }\n    return reachable;\n}\n\ntemplate <typename Value = long long>\nstd::vector<Value>\
    \ zero_one_knapsack_max_value(\n    const std::vector<int>& weights,\n    const\
    \ std::vector<Value>& values,\n    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest()\
    \ / Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(0\
    \ <= capacity);\n\n    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);\n\
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
    \    }\n    return dp;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_DP_KNAPSACK_HPP\n#define M1UNE_ALGO_DP_KNAPSACK_HPP 1\n\
    \n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include <deque>\n\
    #include <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n\
    inline std::vector<char> subset_sum_reachable(const std::vector<int>& weights,\
    \ int limit) {\n    assert(0 <= limit);\n    using Word = unsigned long long;\n\
    \    constexpr int word_bits = std::numeric_limits<Word>::digits;\n\n    const\
    \ std::size_t bit_count = std::size_t(limit) + 1;\n    std::vector<Word> bits((bit_count\
    \ + word_bits - 1) / word_bits, Word(0));\n    bits[0] = Word(1);\n\n    auto\
    \ trim = [&]() {\n        const int extra = int(bit_count % word_bits);\n    \
    \    if (extra != 0) {\n            bits.back() &= (Word(1) << extra) - Word(1);\n\
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
    \    }\n    return dp;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_ALGO_DP_KNAPSACK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/dp/knapsack.hpp
  requiredBy:
  - algo/all.hpp
  - algo/dp/all.hpp
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/dp/knapsack.test.cpp
documentation_of: algo/dp/knapsack.hpp
layout: document
title: Knapsack Helpers
---

## Overview

This header provides small, explicit helpers for common subset-sum and knapsack
DP patterns. The public namespace is `m1une::algo`.

Weights and capacities are nonnegative. Ranges are indexed by exact sum,
capacity, or value depending on the function.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_sum_reachable(weights, limit)` | Returns a `vector<char>` where `result[s]` says whether sum `s` is reachable. | $O(NL / W)$ time, $O(L / W)$ working memory |
| `zero_one_knapsack_max_value(weights, values, capacity, neg_inf)` | Returns max value for each capacity at most `c`. | $O(NC)$ time, $O(C)$ memory |
| `bounded_knapsack_max_value(weights, values, counts, capacity, neg_inf)` | Returns max value for each capacity at most `c` with item limits. | $O(NC)$ time, $O(C)$ memory |
| `zero_one_knapsack_min_weight_for_value(weights, values, value_limit, inf)` | Returns minimum exact weight for each total value. | $O(NV)$ time, $O(V)$ memory |

Here `L` is `limit`, `C` is `capacity`, `V` is `value_limit`, and `W` is the
number of bits in an unsigned machine word.

The max-value functions return arrays of length `capacity + 1`; entry `c` is
the best value using total weight at most `c`. The min-weight function returns
exact-value costs, so unreachable values contain `inf`.

## Example

```cpp
#include "algo/dp/knapsack.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> weights = {2, 3, 4};
    std::vector<long long> values = {4, 5, 7};

    std::vector<long long> best =
        m1une::algo::zero_one_knapsack_max_value(weights, values, 5);
    std::cout << best[5] << '\n';
}
```
