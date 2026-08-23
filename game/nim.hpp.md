---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: game/all.hpp
    title: Game Library
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/game/game_algorithms.test.cpp
    title: verify/game/game_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"game/nim.hpp\"\n\n\n\n#include <iterator>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace game\
    \ {\n\ntemplate <typename T>\nstruct NimMove {\n    int heap;\n    T new_size;\n\
    };\n\ntemplate <typename Iterator>\nauto nim_sum(Iterator first, Iterator last)\
    \ {\n    using T = typename std::iterator_traits<Iterator>::value_type;\n    T\
    \ result{};\n    while (first != last) {\n        result ^= *first;\n        ++first;\n\
    \    }\n    return result;\n}\n\ntemplate <typename Range>\nauto nim_sum(const\
    \ Range& heaps) {\n    using std::begin;\n    using std::end;\n    return nim_sum(begin(heaps),\
    \ end(heaps));\n}\n\ntemplate <typename Range>\nbool nim_first_player_wins(const\
    \ Range& heaps) {\n    return nim_sum(heaps) != 0;\n}\n\ntemplate <typename Range>\n\
    auto nim_winning_move(const Range& heaps) {\n    using std::begin;\n    using\
    \ std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\n    const\
    \ T sum = nim_sum(heaps);\n    if (sum == 0) return std::optional<NimMove<T>>{};\n\
    \    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n      \
    \  iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\ntemplate <typename\
    \ Range>\nbool misere_nim_first_player_wins(const Range& heaps) {\n    using std::begin;\n\
    \    using std::end;\n\n    auto first = begin(heaps);\n    const auto last =\
    \ end(heaps);\n    bool odd_nonzero_heaps = false;\n    bool has_large_heap =\
    \ false;\n    using T = typename std::iterator_traits<decltype(first)>::value_type;\n\
    \    T sum{};\n    for (; first != last; ++first) {\n        sum ^= *first;\n\
    \        if (*first != 0) {\n            odd_nonzero_heaps = !odd_nonzero_heaps;\n\
    \        }\n        if (*first > 1) has_large_heap = true;\n    }\n    return\
    \ has_large_heap ? sum != 0 : !odd_nonzero_heaps;\n}\n\ntemplate <typename Range>\n\
    auto misere_nim_winning_move(const Range& heaps) {\n    using std::begin;\n  \
    \  using std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\n \
    \   T sum{};\n    int ones = 0;\n    int large_heaps = 0;\n    int only_large_heap\
    \ = -1;\n    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n\
    \        iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n     \
    \   sum ^= *iterator;\n        if (*iterator == 1) ones++;\n        if (*iterator\
    \ > 1) {\n            large_heaps++;\n            only_large_heap = index;\n \
    \       }\n    }\n\n    if (large_heaps == 0) {\n        if (ones == 0 || ones\
    \ % 2 == 1) return std::optional<NimMove<T>>{};\n        index = 0;\n        for\
    \ (\n            auto iterator = begin(heaps);\n            iterator != end(heaps);\n\
    \            ++iterator, ++index\n        ) {\n            if (*iterator == 1)\
    \ return std::optional(NimMove<T>{index, T(0)});\n        }\n    }\n    if (large_heaps\
    \ == 1) {\n        const T new_size = ones % 2 == 0 ? T(1) : T(0);\n        return\
    \ std::optional(NimMove<T>{only_large_heap, new_size});\n    }\n    if (sum ==\
    \ 0) return std::optional<NimMove<T>>{};\n\n    index = 0;\n    for (auto iterator\
    \ = begin(heaps); iterator != end(heaps); ++iterator, ++index) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GAME_NIM_HPP\n#define M1UNE_GAME_NIM_HPP 1\n\n#include <iterator>\n\
    #include <optional>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une\
    \ {\nnamespace game {\n\ntemplate <typename T>\nstruct NimMove {\n    int heap;\n\
    \    T new_size;\n};\n\ntemplate <typename Iterator>\nauto nim_sum(Iterator first,\
    \ Iterator last) {\n    using T = typename std::iterator_traits<Iterator>::value_type;\n\
    \    T result{};\n    while (first != last) {\n        result ^= *first;\n   \
    \     ++first;\n    }\n    return result;\n}\n\ntemplate <typename Range>\nauto\
    \ nim_sum(const Range& heaps) {\n    using std::begin;\n    using std::end;\n\
    \    return nim_sum(begin(heaps), end(heaps));\n}\n\ntemplate <typename Range>\n\
    bool nim_first_player_wins(const Range& heaps) {\n    return nim_sum(heaps) !=\
    \ 0;\n}\n\ntemplate <typename Range>\nauto nim_winning_move(const Range& heaps)\
    \ {\n    using std::begin;\n    using std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\
    \n    const T sum = nim_sum(heaps);\n    if (sum == 0) return std::optional<NimMove<T>>{};\n\
    \    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n      \
    \  iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\ntemplate <typename\
    \ Range>\nbool misere_nim_first_player_wins(const Range& heaps) {\n    using std::begin;\n\
    \    using std::end;\n\n    auto first = begin(heaps);\n    const auto last =\
    \ end(heaps);\n    bool odd_nonzero_heaps = false;\n    bool has_large_heap =\
    \ false;\n    using T = typename std::iterator_traits<decltype(first)>::value_type;\n\
    \    T sum{};\n    for (; first != last; ++first) {\n        sum ^= *first;\n\
    \        if (*first != 0) {\n            odd_nonzero_heaps = !odd_nonzero_heaps;\n\
    \        }\n        if (*first > 1) has_large_heap = true;\n    }\n    return\
    \ has_large_heap ? sum != 0 : !odd_nonzero_heaps;\n}\n\ntemplate <typename Range>\n\
    auto misere_nim_winning_move(const Range& heaps) {\n    using std::begin;\n  \
    \  using std::end;\n    using T = std::decay_t<decltype(*begin(heaps))>;\n\n \
    \   T sum{};\n    int ones = 0;\n    int large_heaps = 0;\n    int only_large_heap\
    \ = -1;\n    int index = 0;\n    for (\n        auto iterator = begin(heaps);\n\
    \        iterator != end(heaps);\n        ++iterator, ++index\n    ) {\n     \
    \   sum ^= *iterator;\n        if (*iterator == 1) ones++;\n        if (*iterator\
    \ > 1) {\n            large_heaps++;\n            only_large_heap = index;\n \
    \       }\n    }\n\n    if (large_heaps == 0) {\n        if (ones == 0 || ones\
    \ % 2 == 1) return std::optional<NimMove<T>>{};\n        index = 0;\n        for\
    \ (\n            auto iterator = begin(heaps);\n            iterator != end(heaps);\n\
    \            ++iterator, ++index\n        ) {\n            if (*iterator == 1)\
    \ return std::optional(NimMove<T>{index, T(0)});\n        }\n    }\n    if (large_heaps\
    \ == 1) {\n        const T new_size = ones % 2 == 0 ? T(1) : T(0);\n        return\
    \ std::optional(NimMove<T>{only_large_heap, new_size});\n    }\n    if (sum ==\
    \ 0) return std::optional<NimMove<T>>{};\n\n    index = 0;\n    for (auto iterator\
    \ = begin(heaps); iterator != end(heaps); ++iterator, ++index) {\n        const\
    \ T new_size = *iterator ^ sum;\n        if (new_size < *iterator) return std::optional(NimMove<T>{index,\
    \ new_size});\n    }\n    return std::optional<NimMove<T>>{};\n}\n\n}  // namespace\
    \ game\n}  // namespace m1une\n\n#endif  // M1UNE_GAME_NIM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: game/nim.hpp
  requiredBy:
  - game/all.hpp
  timestamp: '2026-08-24 02:07:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/game/game_algorithms.test.cpp
documentation_of: game/nim.hpp
layout: document
title: Nim
---

## Overview

Helpers for ordinary Nim and misere Nim. A position is given as a range of
nonnegative heap sizes. An empty or all-zero position is losing in ordinary Nim
and winning under the misere convention, where the player with no move wins.

In ordinary Nim, the first player wins exactly when the xor of all heap sizes is
nonzero. In misere Nim, the same rule applies while some heap has size at least
two; if every nonempty heap has size one, the first player wins exactly when
their count is even.

## Functions

All functions are in namespace `m1une::game`. Heap values must support default
construction, `^=`, comparison with zero, and, for misere Nim, comparison with
one.

`NimMove<T>` stores the zero-based `heap` index and its strictly smaller
`new_size`. Winning-move functions return `std::nullopt` for losing positions.
For the empty misere position they also return `std::nullopt`: the position is
winning because the player already has no move, so no move can be constructed.

| Function signature | Description | Complexity |
| --- | --- | --- |
| `template<class Iterator>`<br>`auto nim_sum(Iterator first, Iterator last)` | Returns the xor of the heap sizes in `[first, last)`. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`auto nim_sum(const Range& heaps)` | Range overload of `nim_sum`. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`bool nim_first_player_wins(const Range& heaps)` | Whether the first player wins ordinary Nim under normal play. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`std::optional<NimMove<T>> nim_winning_move(const Range& heaps)` | Returns a move to an ordinary-Nim losing position when one exists. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`bool misere_nim_first_player_wins(const Range& heaps)` | Whether the first player wins Nim when taking the last object loses. | `O(N)` time, `O(1)` space |
| `template<class Range>`<br>`std::optional<NimMove<T>> misere_nim_winning_move(const Range& heaps)` | Returns a move to a misere-Nim losing position when one exists. | `O(N)` time, `O(1)` space |

## Example

```cpp
#include "game/nim.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> heaps = {1, 4, 5};
    std::cout << m1une::game::nim_sum(heaps) << '\n';
    std::cout << m1une::game::nim_first_player_wins(heaps) << '\n';
    auto move = m1une::game::nim_winning_move(heaps);
    if (move) heaps[move->heap] = move->new_size;

    std::vector<int> misere_heaps = {1, 1};
    std::cout << m1une::game::misere_nim_first_player_wins(misere_heaps) << '\n';
}
```
