---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/predecessor_set.test.cpp
    title: verify/ds/bst/predecessor_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/predecessor_set.hpp\"\n\n\n\n#include <bit>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <limits>\n#include <string_view>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Fixed-universe integer set\
    \ with predecessor and successor queries.\nstruct PredecessorSet {\n   private:\n\
    \    static constexpr int word_bits = 64;\n\n    int _universe_size;\n    int\
    \ _size;\n    std::vector<std::vector<std::uint64_t>> _levels;\n\n    static int\
    \ checked_size(std::string_view membership) {\n        assert(\n            membership.size()\n\
    \            <= static_cast<std::size_t>(std::numeric_limits<int>::max())\n  \
    \      );\n        return int(membership.size());\n    }\n\n    int next_index(int\
    \ index) const {\n        if (index >= _universe_size) return _universe_size;\n\
    \        for (int level = 0; level < int(_levels.size()); level++) {\n       \
    \     if (index / word_bits >= int(_levels[level].size())) break;\n          \
    \  std::uint64_t word =\n                _levels[level][index / word_bits] >>\
    \ (index % word_bits);\n            if (word == 0) {\n                index =\
    \ index / word_bits + 1;\n                continue;\n            }\n         \
    \   index += int(std::countr_zero(word));\n            for (int lower = level\
    \ - 1; lower >= 0; lower--) {\n                index *= word_bits;\n         \
    \       std::uint64_t lower_word =\n                    _levels[lower][index /\
    \ word_bits];\n                index += int(std::countr_zero(lower_word));\n \
    \           }\n            return index;\n        }\n        return _universe_size;\n\
    \    }\n\n    int previous_index(int index) const {\n        if (_universe_size\
    \ == 0 || index < 0) return -1;\n        if (index >= _universe_size) index =\
    \ _universe_size - 1;\n        for (int level = 0; level < int(_levels.size());\
    \ level++) {\n            int offset = index % word_bits;\n            std::uint64_t\
    \ word = _levels[level][index / word_bits];\n            if (offset != word_bits\
    \ - 1) {\n                word &= (std::uint64_t(1) << (offset + 1)) - 1;\n  \
    \          }\n            if (word == 0) {\n                index = index / word_bits\
    \ - 1;\n                if (index < 0) break;\n                continue;\n   \
    \         }\n            index += word_bits - 1 - int(std::countl_zero(word))\
    \ - offset;\n            for (int lower = level - 1; lower >= 0; lower--) {\n\
    \                index *= word_bits;\n                std::uint64_t lower_word\
    \ =\n                    _levels[lower][index / word_bits];\n                index\
    \ += word_bits - 1 - int(std::countl_zero(lower_word));\n            }\n     \
    \       return index;\n        }\n        return -1;\n    }\n\n    static int\
    \ not_found_if_end(int index, int universe_size) {\n        return index == universe_size\
    \ ? -1 : index;\n    }\n\n   public:\n    PredecessorSet() : PredecessorSet(0)\
    \ {}\n\n    explicit PredecessorSet(int universe_size)\n        : _universe_size(universe_size),\
    \ _size(0) {\n        assert(universe_size >= 0);\n        int length = universe_size\
    \ == 0 ? 1 : universe_size;\n        do {\n            int words = int((std::int64_t(length)\
    \ + word_bits - 1) / word_bits);\n            _levels.emplace_back(words, 0);\n\
    \            length = words;\n        } while (length > 1);\n    }\n\n    explicit\
    \ PredecessorSet(std::string_view membership)\n        : PredecessorSet(checked_size(membership))\
    \ {\n        for (int index = 0; index < _universe_size; index++) {\n        \
    \    assert(membership[index] == '0' || membership[index] == '1');\n         \
    \   if (membership[index] == '1') {\n                _levels[0][index / word_bits]\n\
    \                    |= std::uint64_t(1) << (index % word_bits);\n           \
    \     _size++;\n            }\n        }\n        for (int level = 1; level <\
    \ int(_levels.size()); level++) {\n            for (int index = 0; index < int(_levels[level\
    \ - 1].size()); index++) {\n                if (_levels[level - 1][index] != 0)\
    \ {\n                    _levels[level][index / word_bits]\n                 \
    \       |= std::uint64_t(1) << (index % word_bits);\n                }\n     \
    \       }\n        }\n    }\n\n    int universe_size() const {\n        return\
    \ _universe_size;\n    }\n\n    int size() const {\n        return _size;\n  \
    \  }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    bool\
    \ contains(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return ((_levels[0][key / word_bits] >> (key % word_bits)) & 1U) != 0;\n\
    \    }\n\n    bool insert(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (contains(key)) return false;\n        int index = key;\n        for\
    \ (auto& level : _levels) {\n            std::uint64_t& word = level[index / word_bits];\n\
    \            bool was_empty = word == 0;\n            word |= std::uint64_t(1)\
    \ << (index % word_bits);\n            if (!was_empty) break;\n            index\
    \ /= word_bits;\n        }\n        _size++;\n        return true;\n    }\n\n\
    \    bool erase(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (!contains(key)) return false;\n        int index = key;\n       \
    \ for (auto& level : _levels) {\n            std::uint64_t& word = level[index\
    \ / word_bits];\n            word &= ~(std::uint64_t(1) << (index % word_bits));\n\
    \            if (word != 0) break;\n            index /= word_bits;\n        }\n\
    \        _size--;\n        return true;\n    }\n\n    // Returns the smallest\
    \ key greater than or equal to key, or -1.\n    int successor(int key) const {\n\
    \        assert(0 <= key && key < _universe_size);\n        return not_found_if_end(next_index(key),\
    \ _universe_size);\n    }\n\n    // Returns the largest key less than or equal\
    \ to key, or -1.\n    int predecessor(int key) const {\n        assert(0 <= key\
    \ && key < _universe_size);\n        return previous_index(key);\n    }\n\n  \
    \  int min_ge(int key) const {\n        return successor(key);\n    }\n\n    int\
    \ min_gt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return not_found_if_end(next_index(key + 1), _universe_size);\n    }\n\
    \n    int max_le(int key) const {\n        return predecessor(key);\n    }\n\n\
    \    int max_lt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return previous_index(key - 1);\n    }\n\n    int min() const {\n   \
    \     return not_found_if_end(next_index(0), _universe_size);\n    }\n\n    int\
    \ max() const {\n        return previous_index(_universe_size - 1);\n    }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_BST_PREDECESSOR_SET_HPP\n#define M1UNE_DS_BST_PREDECESSOR_SET_HPP\
    \ 1\n\n#include <bit>\n#include <cassert>\n#include <cstdint>\n#include <limits>\n\
    #include <string_view>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\
    \n// Fixed-universe integer set with predecessor and successor queries.\nstruct\
    \ PredecessorSet {\n   private:\n    static constexpr int word_bits = 64;\n\n\
    \    int _universe_size;\n    int _size;\n    std::vector<std::vector<std::uint64_t>>\
    \ _levels;\n\n    static int checked_size(std::string_view membership) {\n   \
    \     assert(\n            membership.size()\n            <= static_cast<std::size_t>(std::numeric_limits<int>::max())\n\
    \        );\n        return int(membership.size());\n    }\n\n    int next_index(int\
    \ index) const {\n        if (index >= _universe_size) return _universe_size;\n\
    \        for (int level = 0; level < int(_levels.size()); level++) {\n       \
    \     if (index / word_bits >= int(_levels[level].size())) break;\n          \
    \  std::uint64_t word =\n                _levels[level][index / word_bits] >>\
    \ (index % word_bits);\n            if (word == 0) {\n                index =\
    \ index / word_bits + 1;\n                continue;\n            }\n         \
    \   index += int(std::countr_zero(word));\n            for (int lower = level\
    \ - 1; lower >= 0; lower--) {\n                index *= word_bits;\n         \
    \       std::uint64_t lower_word =\n                    _levels[lower][index /\
    \ word_bits];\n                index += int(std::countr_zero(lower_word));\n \
    \           }\n            return index;\n        }\n        return _universe_size;\n\
    \    }\n\n    int previous_index(int index) const {\n        if (_universe_size\
    \ == 0 || index < 0) return -1;\n        if (index >= _universe_size) index =\
    \ _universe_size - 1;\n        for (int level = 0; level < int(_levels.size());\
    \ level++) {\n            int offset = index % word_bits;\n            std::uint64_t\
    \ word = _levels[level][index / word_bits];\n            if (offset != word_bits\
    \ - 1) {\n                word &= (std::uint64_t(1) << (offset + 1)) - 1;\n  \
    \          }\n            if (word == 0) {\n                index = index / word_bits\
    \ - 1;\n                if (index < 0) break;\n                continue;\n   \
    \         }\n            index += word_bits - 1 - int(std::countl_zero(word))\
    \ - offset;\n            for (int lower = level - 1; lower >= 0; lower--) {\n\
    \                index *= word_bits;\n                std::uint64_t lower_word\
    \ =\n                    _levels[lower][index / word_bits];\n                index\
    \ += word_bits - 1 - int(std::countl_zero(lower_word));\n            }\n     \
    \       return index;\n        }\n        return -1;\n    }\n\n    static int\
    \ not_found_if_end(int index, int universe_size) {\n        return index == universe_size\
    \ ? -1 : index;\n    }\n\n   public:\n    PredecessorSet() : PredecessorSet(0)\
    \ {}\n\n    explicit PredecessorSet(int universe_size)\n        : _universe_size(universe_size),\
    \ _size(0) {\n        assert(universe_size >= 0);\n        int length = universe_size\
    \ == 0 ? 1 : universe_size;\n        do {\n            int words = int((std::int64_t(length)\
    \ + word_bits - 1) / word_bits);\n            _levels.emplace_back(words, 0);\n\
    \            length = words;\n        } while (length > 1);\n    }\n\n    explicit\
    \ PredecessorSet(std::string_view membership)\n        : PredecessorSet(checked_size(membership))\
    \ {\n        for (int index = 0; index < _universe_size; index++) {\n        \
    \    assert(membership[index] == '0' || membership[index] == '1');\n         \
    \   if (membership[index] == '1') {\n                _levels[0][index / word_bits]\n\
    \                    |= std::uint64_t(1) << (index % word_bits);\n           \
    \     _size++;\n            }\n        }\n        for (int level = 1; level <\
    \ int(_levels.size()); level++) {\n            for (int index = 0; index < int(_levels[level\
    \ - 1].size()); index++) {\n                if (_levels[level - 1][index] != 0)\
    \ {\n                    _levels[level][index / word_bits]\n                 \
    \       |= std::uint64_t(1) << (index % word_bits);\n                }\n     \
    \       }\n        }\n    }\n\n    int universe_size() const {\n        return\
    \ _universe_size;\n    }\n\n    int size() const {\n        return _size;\n  \
    \  }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    bool\
    \ contains(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return ((_levels[0][key / word_bits] >> (key % word_bits)) & 1U) != 0;\n\
    \    }\n\n    bool insert(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (contains(key)) return false;\n        int index = key;\n        for\
    \ (auto& level : _levels) {\n            std::uint64_t& word = level[index / word_bits];\n\
    \            bool was_empty = word == 0;\n            word |= std::uint64_t(1)\
    \ << (index % word_bits);\n            if (!was_empty) break;\n            index\
    \ /= word_bits;\n        }\n        _size++;\n        return true;\n    }\n\n\
    \    bool erase(int key) {\n        assert(0 <= key && key < _universe_size);\n\
    \        if (!contains(key)) return false;\n        int index = key;\n       \
    \ for (auto& level : _levels) {\n            std::uint64_t& word = level[index\
    \ / word_bits];\n            word &= ~(std::uint64_t(1) << (index % word_bits));\n\
    \            if (word != 0) break;\n            index /= word_bits;\n        }\n\
    \        _size--;\n        return true;\n    }\n\n    // Returns the smallest\
    \ key greater than or equal to key, or -1.\n    int successor(int key) const {\n\
    \        assert(0 <= key && key < _universe_size);\n        return not_found_if_end(next_index(key),\
    \ _universe_size);\n    }\n\n    // Returns the largest key less than or equal\
    \ to key, or -1.\n    int predecessor(int key) const {\n        assert(0 <= key\
    \ && key < _universe_size);\n        return previous_index(key);\n    }\n\n  \
    \  int min_ge(int key) const {\n        return successor(key);\n    }\n\n    int\
    \ min_gt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return not_found_if_end(next_index(key + 1), _universe_size);\n    }\n\
    \n    int max_le(int key) const {\n        return predecessor(key);\n    }\n\n\
    \    int max_lt(int key) const {\n        assert(0 <= key && key < _universe_size);\n\
    \        return previous_index(key - 1);\n    }\n\n    int min() const {\n   \
    \     return not_found_if_end(next_index(0), _universe_size);\n    }\n\n    int\
    \ max() const {\n        return previous_index(_universe_size - 1);\n    }\n};\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_BST_PREDECESSOR_SET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/bst/predecessor_set.hpp
  requiredBy: []
  timestamp: '2026-07-15 01:33:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/predecessor_set.test.cpp
documentation_of: ds/bst/predecessor_set.hpp
layout: document
title: Predecessor Set
---

## Overview

`PredecessorSet` maintains a set of integers in a fixed universe `[0, U)`.
Besides insertion, erasure, and membership tests, it finds the closest stored
key on either side of a query key.

The structure stores the universe in 64-bit words and recursively records which
words are nonempty. A search skips empty groups one level at a time, giving
small constants and deterministic worst-case bounds. It is most useful when the
universe is dense enough that a tree node per stored key would be wasteful.

## Behavior

Keys passed to membership, update, predecessor, and successor methods must
satisfy `0 <= key < universe_size()`. Invalid keys trigger an assertion.

Every predecessor or successor method returns `-1` when no matching key exists.
The string constructor expects one character per universe key: key `i` is
initially present exactly when `membership[i]` is `'1'`.

The structure uses $O(U / 64)$ machine words. Its query and update bounds are
$O(\log_{64} U)$, which is at most four levels for common contest constraints.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `PredecessorSet()` | Constructs a set with an empty universe. | $O(1)$ |
| Constructor | `explicit PredecessorSet(int universe_size)` | Constructs an empty set over `[0, universe_size)`. | $O(U / 64)$ |
| Constructor | `explicit PredecessorSet(std::string_view membership)` | Constructs the set from a binary membership string. | $O(U)$ |
| `universe_size` | `int universe_size() const` | Returns `U`. | $O(1)$ |
| `size` | `int size() const` | Returns the number of stored keys. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the set has no keys. | $O(1)$ |
| `contains` | `bool contains(int key) const` | Returns whether `key` is stored. | $O(1)$ |
| `insert` | `bool insert(int key)` | Inserts `key` and returns whether the set changed. | $O(\log_{64} U)$ |
| `erase` | `bool erase(int key)` | Erases `key` and returns whether the set changed. | $O(\log_{64} U)$ |
| `successor`, `min_ge` | `int successor(int key) const`, `int min_ge(int key) const` | Returns the smallest stored key greater than or equal to `key`, or `-1`. | $O(\log_{64} U)$ |
| `min_gt` | `int min_gt(int key) const` | Returns the smallest stored key strictly greater than `key`, or `-1`. | $O(\log_{64} U)$ |
| `predecessor`, `max_le` | `int predecessor(int key) const`, `int max_le(int key) const` | Returns the largest stored key less than or equal to `key`, or `-1`. | $O(\log_{64} U)$ |
| `max_lt` | `int max_lt(int key) const` | Returns the largest stored key strictly less than `key`, or `-1`. | $O(\log_{64} U)$ |
| `min` | `int min() const` | Returns the minimum stored key, or `-1`. | $O(\log_{64} U)$ |
| `max` | `int max() const` | Returns the maximum stored key, or `-1`. | $O(\log_{64} U)$ |

## Example

```cpp
#include "ds/bst/predecessor_set.hpp"

#include <iostream>

int main() {
    m1une::ds::PredecessorSet set(10);
    set.insert(2);
    set.insert(7);

    std::cout << set.predecessor(5) << '\n';  // 2
    std::cout << set.successor(5) << '\n';    // 7

    set.erase(2);
    std::cout << set.max_le(5) << '\n';       // -1
}
```
