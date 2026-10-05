---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/predecessor_set.hpp
    title: Predecessor Set
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/mex_multiset.test.cpp
    title: verify/ds/bst/mex_multiset.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/mex_multiset.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <limits>\n#include <string>\n#include <type_traits>\n#include\
    \ <vector>\n\n#line 1 \"ds/bst/predecessor_set.hpp\"\n\n\n\n#include <bit>\n#line\
    \ 8 \"ds/bst/predecessor_set.hpp\"\n#include <string_view>\n#line 10 \"ds/bst/predecessor_set.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Fixed-universe integer set with predecessor\
    \ and successor queries.\nstruct PredecessorSet {\n   private:\n    static constexpr\
    \ int word_bits = 64;\n\n    int _universe_size;\n    int _size;\n    std::vector<std::vector<std::uint64_t>>\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/bst/mex_multiset.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Tracks multiplicities in [0, U) and\
    \ returns min(actual mex, U).\nstruct MexMultiset {\n   private:\n    std::vector<int>\
    \ _count;\n    PredecessorSet _missing;\n    int _mex;\n\n    static int checked_universe_size(int\
    \ universe_size) {\n        assert(universe_size >= 0);\n        return universe_size;\n\
    \    }\n\n    static int checked_size(std::size_t size) {\n        assert(size\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        return\
    \ int(size);\n    }\n\n   public:\n    MexMultiset() : MexMultiset(0) {}\n\n \
    \   explicit MexMultiset(int universe_size)\n        : _count(checked_universe_size(universe_size),\
    \ 0),\n          _missing(std::string(universe_size, '1')), _mex(0) {}\n\n   \
    \ template <class T>\n    explicit MexMultiset(const std::vector<T>& values)\n\
    \        : _count(checked_size(values.size()), 0), _missing(0), _mex(0) {\n  \
    \      static_assert(\n            std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),\n\
    \            \"MexMultiset requires standard integral values\"\n        );\n \
    \       const int n = universe_size();\n        for (T value : values) {\n   \
    \         if constexpr (std::is_signed_v<T>) {\n                if (value < 0)\
    \ continue;\n            }\n            if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n                ++_count[int(value)];\n\
    \            }\n        }\n        std::string membership(n, '1');\n        for\
    \ (int value = 0; value < n; ++value) {\n            if (_count[value] != 0) membership[value]\
    \ = '0';\n        }\n        _missing = PredecessorSet(membership);\n        const\
    \ int first = _missing.min();\n        _mex = first == -1 ? n : first;\n    }\n\
    \n    int universe_size() const {\n        return int(_count.size());\n    }\n\
    \n    int count(long long value) const {\n        if (value < 0 || value >= universe_size())\
    \ return 0;\n        return _count[int(value)];\n    }\n\n    void insert(long\
    \ long value) {\n        if (value < 0 || value >= universe_size()) return;\n\
    \        const int key = int(value);\n        assert(_count[key] < std::numeric_limits<int>::max());\n\
    \        if (_count[key]++ != 0) return;\n        _missing.erase(key);\n     \
    \   if (key == _mex) {\n            const int first = _missing.min();\n      \
    \      _mex = first == -1 ? universe_size() : first;\n        }\n    }\n\n   \
    \ // Removes one occurrence; returns false for absent or untracked values.\n \
    \   bool erase(long long value) {\n        if (value < 0 || value >= universe_size())\
    \ return false;\n        const int key = int(value);\n        if (_count[key]\
    \ == 0) return false;\n        if (--_count[key] == 0) {\n            _missing.insert(key);\n\
    \            if (key < _mex) _mex = key;\n        }\n        return true;\n  \
    \  }\n\n    int mex() const {\n        return _mex;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_BST_MEX_MULTISET_HPP\n#define M1UNE_DS_BST_MEX_MULTISET_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <string>\n\
    #include <type_traits>\n#include <vector>\n\n#include \"predecessor_set.hpp\"\n\
    \nnamespace m1une {\nnamespace ds {\n\n// Tracks multiplicities in [0, U) and\
    \ returns min(actual mex, U).\nstruct MexMultiset {\n   private:\n    std::vector<int>\
    \ _count;\n    PredecessorSet _missing;\n    int _mex;\n\n    static int checked_universe_size(int\
    \ universe_size) {\n        assert(universe_size >= 0);\n        return universe_size;\n\
    \    }\n\n    static int checked_size(std::size_t size) {\n        assert(size\
    \ <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n        return\
    \ int(size);\n    }\n\n   public:\n    MexMultiset() : MexMultiset(0) {}\n\n \
    \   explicit MexMultiset(int universe_size)\n        : _count(checked_universe_size(universe_size),\
    \ 0),\n          _missing(std::string(universe_size, '1')), _mex(0) {}\n\n   \
    \ template <class T>\n    explicit MexMultiset(const std::vector<T>& values)\n\
    \        : _count(checked_size(values.size()), 0), _missing(0), _mex(0) {\n  \
    \      static_assert(\n            std::is_integral_v<T> && sizeof(T) <= sizeof(std::uintmax_t),\n\
    \            \"MexMultiset requires standard integral values\"\n        );\n \
    \       const int n = universe_size();\n        for (T value : values) {\n   \
    \         if constexpr (std::is_signed_v<T>) {\n                if (value < 0)\
    \ continue;\n            }\n            if (static_cast<std::uintmax_t>(value)\
    \ < static_cast<std::uintmax_t>(n)) {\n                ++_count[int(value)];\n\
    \            }\n        }\n        std::string membership(n, '1');\n        for\
    \ (int value = 0; value < n; ++value) {\n            if (_count[value] != 0) membership[value]\
    \ = '0';\n        }\n        _missing = PredecessorSet(membership);\n        const\
    \ int first = _missing.min();\n        _mex = first == -1 ? n : first;\n    }\n\
    \n    int universe_size() const {\n        return int(_count.size());\n    }\n\
    \n    int count(long long value) const {\n        if (value < 0 || value >= universe_size())\
    \ return 0;\n        return _count[int(value)];\n    }\n\n    void insert(long\
    \ long value) {\n        if (value < 0 || value >= universe_size()) return;\n\
    \        const int key = int(value);\n        assert(_count[key] < std::numeric_limits<int>::max());\n\
    \        if (_count[key]++ != 0) return;\n        _missing.erase(key);\n     \
    \   if (key == _mex) {\n            const int first = _missing.min();\n      \
    \      _mex = first == -1 ? universe_size() : first;\n        }\n    }\n\n   \
    \ // Removes one occurrence; returns false for absent or untracked values.\n \
    \   bool erase(long long value) {\n        if (value < 0 || value >= universe_size())\
    \ return false;\n        const int key = int(value);\n        if (_count[key]\
    \ == 0) return false;\n        if (--_count[key] == 0) {\n            _missing.insert(key);\n\
    \            if (key < _mex) _mex = key;\n        }\n        return true;\n  \
    \  }\n\n    int mex() const {\n        return _mex;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_BST_MEX_MULTISET_HPP\n"
  dependsOn:
  - ds/bst/predecessor_set.hpp
  isVerificationFile: false
  path: ds/bst/mex_multiset.hpp
  requiredBy: []
  timestamp: '2026-10-06 02:15:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/mex_multiset.test.cpp
documentation_of: ds/bst/mex_multiset.hpp
layout: document
title: Mex Multiset
---

## Overview

`MexMultiset` maintains multiplicities of integers in a fixed universe `[0, U)`
and answers mex queries in constant time. It stores counts and uses a
[`PredecessorSet`](predecessor_set.md) to find the first missing value after
updates, with deterministic bounds and $O(U)$ space.

## Behavior

The returned answer is the smallest missing integer in `[0, U)`, or `U` if all
tracked values are present. It equals the actual mex whenever the actual mex is
at most `U`. In particular, choosing `U` at least the maximum number of elements
in the maintained collection always suffices. There is no automatic resizing.

Negative values and values at least `U` are ignored: insertion has no effect,
`erase` returns `false`, and `count` returns `0`. They are not stored. Repeated
insertions increment multiplicity; erasure removes one occurrence. The mex can
decrease only when the last occurrence of a tracked value is removed.

The vector constructor chooses `U = values.size()`. `T` must be a standard
integral type, signed or unsigned, and the vector length must fit in `int`.
The integer constructor asserts `U >= 0`. Each tracked multiplicity must fit
in `int`; insertion asserts before overflowing it. Updates mutate the object;
const queries do not mutate it.

## Interface

Let $L = 1 + \lceil\log_{64}(U + 1)\rceil$.

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `MexMultiset()` | Constructs an empty universe (`U = 0`). | $O(1)$ |
| Constructor | `explicit MexMultiset(int universe_size)` | Constructs an empty multiset over `[0, U)`. | $O(U + 1)$ |
| Constructor | `template <class T> explicit MexMultiset(const std::vector<T>& values)` | Constructs from `values`, with `U = values.size()`. | $O(U + 1)$ |
| `universe_size` | `int universe_size() const` | Returns `U`. | $O(1)$ |
| `count` | `int count(long long value) const` | Returns the tracked multiplicity, or `0` outside `[0, U)`. | $O(1)$ |
| `insert` | `void insert(long long value)` | Adds one occurrence, or ignores an untracked value. | $O(L)$ worst case; $O(1)$ for duplicates or untracked values |
| `erase` | `bool erase(long long value)` | Removes one occurrence and returns whether removal succeeded. | $O(L)$ worst case; $O(1)$ unless the last occurrence is removed |
| `mex` | `int mex() const` | Returns the smallest missing value, capped at `U`. | $O(1)$ |

## Example

```cpp
#include "ds/bst/mex_multiset.hpp"

#include <iostream>

int main() {
    m1une::ds::MexMultiset values(5);
    values.insert(0);
    values.insert(1);
    values.insert(1);
    values.insert(3);
    std::cout << values.mex() << '\n';  // 2

    values.erase(1);
    std::cout << values.mex() << '\n';  // 2: one copy of 1 remains
    values.erase(1);
    std::cout << values.mex() << '\n';  // 1
    values.insert(1);
    values.insert(2);
    std::cout << values.mex() << '\n';  // 4
}
```
