---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: game/grundy.hpp
    title: Grundy Numbers
  - icon: ':heavy_check_mark:'
    path: game/nim.hpp
    title: Nim
  - icon: ':heavy_check_mark:'
    path: game/nim_product.hpp
    title: Nim Product
  - icon: ':heavy_check_mark:'
    path: game/retrograde_analysis.hpp
    title: Game Retrograde Analysis
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/all.hpp\"\n\n\n\n#line 1 \"game/grundy.hpp\"\n\n\n\n\
    #include <cassert>\n#include <queue>\n#include <vector>\n\nnamespace m1une {\n\
    namespace game {\n\n// graph[v] contains the states reachable from v in one move.\n\
    // The graph must be a DAG.\ntemplate <typename Graph>\nstd::vector<int> grundy_numbers(const\
    \ Graph& graph) {\n    const int size = int(graph.size());\n    std::vector<int>\
    \ indegree(size);\n    for (int vertex = 0; vertex < size; ++vertex) {\n     \
    \   for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            indegree[next]++;\n        }\n    }\n\n    std::queue<int> queue;\n\
    \    for (int vertex = 0; vertex < size; ++vertex) {\n        if (indegree[vertex]\
    \ == 0) queue.push(vertex);\n    }\n    std::vector<int> order;\n    order.reserve(size);\n\
    \    while (!queue.empty()) {\n        const int vertex = queue.front();\n   \
    \     queue.pop();\n        order.push_back(vertex);\n        for (int next :\
    \ graph[vertex]) {\n            if (--indegree[next] == 0) queue.push(next);\n\
    \        }\n    }\n    assert(int(order.size()) == size);\n\n    std::vector<int>\
    \ grundy(size);\n    std::vector<int> seen(size + 1, -1);\n    for (int position\
    \ = size - 1; position >= 0; --position) {\n        const int vertex = order[position];\n\
    \        for (int next : graph[vertex]) {\n            const int value = grundy[next];\n\
    \            if (value <= size) seen[value] = vertex;\n        }\n        while\
    \ (grundy[vertex] <= size && seen[grundy[vertex]] == vertex) {\n            grundy[vertex]++;\n\
    \        }\n    }\n    return grundy;\n}\n\n}  // namespace game\n}  // namespace\
    \ m1une\n\n\n#line 1 \"game/nim.hpp\"\n\n\n\n#include <iterator>\n\nnamespace\
    \ m1une {\nnamespace game {\n\ntemplate <typename Iterator>\nauto nim_sum(Iterator\
    \ first, Iterator last) {\n    using T = typename std::iterator_traits<Iterator>::value_type;\n\
    \    T result{};\n    while (first != last) {\n        result ^= *first;\n   \
    \     ++first;\n    }\n    return result;\n}\n\ntemplate <typename Range>\nauto\
    \ nim_sum(const Range& heaps) {\n    using std::begin;\n    using std::end;\n\
    \    return nim_sum(begin(heaps), end(heaps));\n}\n\ntemplate <typename Range>\n\
    bool nim_first_player_wins(const Range& heaps) {\n    return nim_sum(heaps) !=\
    \ 0;\n}\n\ntemplate <typename Range>\nbool misere_nim_first_player_wins(const\
    \ Range& heaps) {\n    using std::begin;\n    using std::end;\n\n    auto first\
    \ = begin(heaps);\n    const auto last = end(heaps);\n    bool odd_nonzero_heaps\
    \ = false;\n    bool has_large_heap = false;\n    using T = typename std::iterator_traits<decltype(first)>::value_type;\n\
    \    T sum{};\n    for (; first != last; ++first) {\n        sum ^= *first;\n\
    \        if (*first != 0) {\n            odd_nonzero_heaps = !odd_nonzero_heaps;\n\
    \        }\n        if (*first > 1) has_large_heap = true;\n    }\n    return\
    \ has_large_heap ? sum != 0 : !odd_nonzero_heaps;\n}\n\n}  // namespace game\n\
    }  // namespace m1une\n\n\n#line 1 \"game/nim_product.hpp\"\n\n\n\n#include <array>\n\
    #line 6 \"game/nim_product.hpp\"\n#include <cstdint>\n#include <limits>\n\nnamespace\
    \ m1une {\nnamespace game {\nnamespace internal {\n\ninline uint64_t nim_product_small(uint64_t\
    \ x, uint64_t y) {\n    if (x < 2 || y < 2) return x * y;\n\n    int shift = 1;\n\
    \    const uint64_t largest = x | y;\n    while ((uint64_t(1) << (shift * 2))\
    \ <= largest) shift *= 2;\n    const uint64_t mask = (uint64_t(1) << shift) -\
    \ 1;\n    const uint64_t x_high = x >> shift;\n    const uint64_t x_low = x &\
    \ mask;\n    const uint64_t y_high = y >> shift;\n    const uint64_t y_low = y\
    \ & mask;\n\n    const uint64_t high_product = nim_product_small(x_high, y_high);\n\
    \    const uint64_t low_product = nim_product_small(x_low, y_low);\n    const\
    \ uint64_t mixed_product =\n        nim_product_small(x_high ^ x_low, y_high ^\
    \ y_low);\n    return ((mixed_product ^ low_product) << shift) ^ low_product\n\
    \           ^ nim_product_small(high_product, uint64_t(1) << (shift - 1));\n}\n\
    \ninline const std::array<uint8_t, 1 << 16>& nim_product_8_table() {\n    static\
    \ const auto table = [] {\n        std::array<uint8_t, 1 << 16> result{};\n  \
    \      for (int x = 0; x < 256; ++x) {\n            for (int y = 0; y < 256; ++y)\
    \ {\n                result[(x << 8) | y] = uint8_t(nim_product_small(x, y));\n\
    \            }\n        }\n        return result;\n    }();\n    return table;\n\
    }\n\ninline uint64_t nim_product_8(uint64_t x, uint64_t y) {\n    return nim_product_8_table()[(x\
    \ << 8) | y];\n}\n\ntemplate <int Bits>\ninline uint64_t nim_product_fixed(uint64_t\
    \ x, uint64_t y) {\n    if constexpr (Bits == 8) {\n        return nim_product_8(x,\
    \ y);\n    } else {\n        constexpr int shift = Bits / 2;\n        constexpr\
    \ uint64_t mask = (uint64_t(1) << shift) - 1;\n        const uint64_t x_high =\
    \ x >> shift;\n        const uint64_t x_low = x & mask;\n        const uint64_t\
    \ y_high = y >> shift;\n        const uint64_t y_low = y & mask;\n\n        const\
    \ uint64_t high_product =\n            nim_product_fixed<shift>(x_high, y_high);\n\
    \        const uint64_t low_product = nim_product_fixed<shift>(x_low, y_low);\n\
    \        const uint64_t mixed_product = nim_product_fixed<shift>(\n          \
    \  x_high ^ x_low,\n            y_high ^ y_low\n        );\n        return ((mixed_product\
    \ ^ low_product) << shift) ^ low_product\n               ^ nim_product_fixed<shift>(\n\
    \                   high_product,\n                   uint64_t(1) << (shift -\
    \ 1)\n               );\n    }\n}\n\n}  // namespace internal\n\ninline uint64_t\
    \ nim_product(uint64_t x, uint64_t y) {\n    return internal::nim_product_fixed<64>(x,\
    \ y);\n}\n\ninline uint64_t nim_power(uint64_t base, uint64_t exponent) {\n  \
    \  uint64_t result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ result = nim_product(result, base);\n        base = nim_product(base, base);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t nim_inverse(uint64_t\
    \ value) {\n    assert(value != 0);\n    return nim_power(value, std::numeric_limits<uint64_t>::max()\
    \ - 1);\n}\n\ninline uint64_t nim_quotient(uint64_t numerator, uint64_t denominator)\
    \ {\n    assert(denominator != 0);\n    return nim_product(numerator, nim_inverse(denominator));\n\
    }\n\n}  // namespace game\n}  // namespace m1une\n\n\n#line 1 \"game/retrograde_analysis.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"game/retrograde_analysis.hpp\"\n#include\
    \ <utility>\n#line 9 \"game/retrograde_analysis.hpp\"\n\nnamespace m1une {\nnamespace\
    \ game {\n\nenum class GameOutcome { Win, Lose, Draw };\n\nstruct RetrogradeResult\
    \ {\n    std::vector<GameOutcome> outcome;\n    std::vector<int> distance;\n};\n\
    \n// graph[v] contains the states reachable from v in one move.\ninline RetrogradeResult\
    \ retrograde_analysis(\n    const std::vector<std::vector<int>>& graph\n) {\n\
    \    const int size = int(graph.size());\n    std::vector<std::vector<int>> reverse_graph(size);\n\
    \    std::vector<int> remaining(size);\n    for (int vertex = 0; vertex < size;\
    \ ++vertex) {\n        remaining[vertex] = int(graph[vertex].size());\n      \
    \  for (int next : graph[vertex]) {\n            assert(0 <= next && next < size);\n\
    \            reverse_graph[next].push_back(vertex);\n        }\n    }\n\n    std::vector<GameOutcome>\
    \ outcome(size, GameOutcome::Draw);\n    std::vector<int> distance(size, -1);\n\
    \    std::vector<int> longest_win_successor(size);\n    std::vector<bool> decided(size);\n\
    \    std::queue<int> queue;\n    for (int vertex = 0; vertex < size; ++vertex)\
    \ {\n        if (remaining[vertex] == 0) {\n            outcome[vertex] = GameOutcome::Lose;\n\
    \            distance[vertex] = 0;\n            decided[vertex] = true;\n    \
    \        queue.push(vertex);\n        }\n    }\n\n    while (!queue.empty()) {\n\
    \        const int vertex = queue.front();\n        queue.pop();\n        for\
    \ (int previous : reverse_graph[vertex]) {\n            if (decided[previous])\
    \ continue;\n            if (outcome[vertex] == GameOutcome::Lose) {\n       \
    \         outcome[previous] = GameOutcome::Win;\n                distance[previous]\
    \ = distance[vertex] + 1;\n                decided[previous] = true;\n       \
    \         queue.push(previous);\n            } else {\n                longest_win_successor[previous]\
    \ = std::max(\n                    longest_win_successor[previous],\n        \
    \            distance[vertex]\n                );\n                if (--remaining[previous]\
    \ == 0) {\n                    outcome[previous] = GameOutcome::Lose;\n      \
    \              distance[previous] = longest_win_successor[previous] + 1;\n   \
    \                 decided[previous] = true;\n                    queue.push(previous);\n\
    \                }\n            }\n        }\n    }\n    return {std::move(outcome),\
    \ std::move(distance)};\n}\n\n}  // namespace game\n}  // namespace m1une\n\n\n\
    #line 8 \"game/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_GAME_ALL_HPP

    #define M1UNE_GAME_ALL_HPP 1


    #include "grundy.hpp"

    #include "nim.hpp"

    #include "nim_product.hpp"

    #include "retrograde_analysis.hpp"


    #endif  // M1UNE_GAME_ALL_HPP

    '
  dependsOn:
  - game/grundy.hpp
  - game/nim.hpp
  - game/nim_product.hpp
  - game/retrograde_analysis.hpp
  isVerificationFile: false
  path: game/all.hpp
  requiredBy: []
  timestamp: '2026-08-24 02:00:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
documentation_of: game/all.hpp
layout: document
title: Game Library
---

## Overview

`game/all.hpp` includes the game-theory library. Public APIs use the
`m1une::game` namespace.

## Included Headers

| Header | Contents |
| --- | --- |
| `game/nim.hpp` | Ordinary and misere Nim helpers. |
| `game/nim_product.hpp` | 64-bit nimber multiplication, powers, inverses, and quotients. |
| `game/grundy.hpp` | Linear-time Sprague-Grundy numbers for finite DAG games. |
| `game/retrograde_analysis.hpp` | Win/lose/draw classification for finite directed games, including cycles. |
