---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/segtree/rollback_segtree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 12 \"ds/segtree/rollback_segtree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ RollbackSegtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    struct Entry {\n        int pos;\n        T value;\n    };\n    struct Checkpoint\
    \ {\n        std::size_t change_size;\n        std::uint64_t epoch;\n    };\n\n\
    \    int _n = 0;\n    int _size = 1;\n    std::vector<T> _data = std::vector<T>(2,\
    \ Monoid::id());\n    std::vector<Entry> _history;\n    std::vector<Checkpoint>\
    \ _checkpoints;\n    std::vector<std::uint64_t> _saved_epoch;\n    std::uint64_t\
    \ _next_epoch = 1;\n\n    std::uint64_t new_epoch() {\n        if (_next_epoch\
    \ == 0) {\n            std::fill(_saved_epoch.begin(), _saved_epoch.end(), 0);\n\
    \            _next_epoch = 1;\n        }\n        return _next_epoch++;\n    }\n\
    \n    template <class U>\n    static T make_value(const U& value, int index) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else if constexpr (requires(U x, int i) { Monoid::make(x,\
    \ i); }) {\n            return Monoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    void assign(int\
    \ pos, T value) {\n        int node = pos + _size;\n        _data[node] = std::move(value);\n\
    \        while (node >>= 1) {\n            _data[node] = Monoid::op(_data[node\
    \ << 1], _data[node << 1 | 1]);\n        }\n    }\n\n    template <class U>\n\
    \    void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = 1;\n        while (_size < _n) _size <<= 1;\n        _data.assign(2\
    \ * _size, Monoid::id());\n        _saved_epoch.assign(_n, 0);\n        for (int\
    \ index = 0; index < _n; ++index) {\n            _data[_size + index] = make_value(values[index],\
    \ index);\n        }\n        for (int node = _size - 1; node > 0; --node) {\n\
    \            _data[node] = Monoid::op(_data[node << 1], _data[node << 1 | 1]);\n\
    \        }\n    }\n\n   public:\n    RollbackSegtree() = default;\n    explicit\
    \ RollbackSegtree(int n) { assert(0 <= n); build(std::vector<T>(n, Monoid::id()));\
    \ }\n    explicit RollbackSegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackSegtree(std::vector<T>&& values) { build(values); }\n\
    \n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackSegtree(const std::vector<U>& values) { build(values); }\n\n    int\
    \ size() const { return _n; }\n    bool empty() const { return _n == 0; }\n  \
    \  std::size_t node_count() const { return _data.size(); }\n\n    void set(int\
    \ pos, T value) {\n        assert(0 <= pos && pos < _n);\n        if (!_checkpoints.empty()\
    \ && _saved_epoch[pos] != _checkpoints.back().epoch) {\n            _saved_epoch[pos]\
    \ = _checkpoints.back().epoch;\n            _history.push_back(Entry{pos, get(pos)});\n\
    \        }\n        assign(pos, std::move(value));\n    }\n\n    void set_inplace(int\
    \ pos, T value) { set(pos, std::move(value)); }\n\n    T get(int pos) const {\n\
    \        assert(0 <= pos && pos < _n);\n        return _data[_size + pos];\n \
    \   }\n\n    T operator[](int pos) const { return get(pos); }\n\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        T left_product = Monoid::id();\n        T right_product = Monoid::id();\n\
    \        for (left += _size, right += _size; left < right; left >>= 1, right >>=\
    \ 1) {\n            if (left & 1) left_product = Monoid::op(left_product, _data[left++]);\n\
    \            if (right & 1) right_product = Monoid::op(_data[--right], right_product);\n\
    \        }\n        return Monoid::op(left_product, right_product);\n    }\n\n\
    \    T all_prod() const { return _data[1]; }\n\n    std::vector<T> to_vector()\
    \ const { return to_vector(0, _n); }\n    std::vector<T> to_vector(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        return std::vector<T>(_data.begin() + _size + left, _data.begin() + _size\
    \ + right);\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) const {\n        assert(0 <= left && left <= _n);\n   \
    \     assert(predicate(Monoid::id()));\n        if (left == _n) return _n;\n \
    \       int node = left + _size;\n        T product = Monoid::id();\n        do\
    \ {\n            while ((node & 1) == 0) node >>= 1;\n            T next = Monoid::op(product,\
    \ _data[node]);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node <<= 1;\n                    next = Monoid::op(product,\
    \ _data[node]);\n                    if (predicate(next)) {\n                \
    \        product = std::move(next);\n                        ++node;\n       \
    \             }\n                }\n                return std::min(_n, node -\
    \ _size);\n            }\n            product = std::move(next);\n           \
    \ ++node;\n        } while ((node & -node) != node);\n        return _n;\n   \
    \ }\n\n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ const {\n        assert(0 <= right && right <= _n);\n        assert(predicate(Monoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  T product = Monoid::id();\n        do {\n            --node;\n            while\
    \ (node > 1 && (node & 1)) node >>= 1;\n            T next = Monoid::op(_data[node],\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node = node << 1 | 1;\n                    next\
    \ = Monoid::op(_data[node], product);\n                    if (predicate(next))\
    \ {\n                        product = std::move(next);\n                    \
    \    --node;\n                    }\n                }\n                return\
    \ std::max(0, node + 1 - _size);\n            }\n            product = std::move(next);\n\
    \        } while ((node & -node) != node);\n        return 0;\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(Checkpoint{_history.size(), new_epoch()});\n\
    \        return int(_checkpoints.size());\n    }\n    int snapshot_count() const\
    \ { return int(_checkpoints.size()); }\n    void reserve_snapshots(int count)\
    \ { assert(0 <= count); _checkpoints.reserve(count); }\n\n    void rollback(int\
    \ state) {\n        assert(1 <= state && state <= snapshot_count());\n       \
    \ while (_history.size() > _checkpoints[state - 1].change_size) {\n          \
    \  Entry entry = std::move(_history.back());\n            _history.pop_back();\n\
    \            assign(entry.pos, std::move(entry.value));\n        }\n        _checkpoints.resize(state);\n\
    \        _checkpoints.back().epoch = new_epoch();\n    }\n    void clear_history()\
    \ {\n        _history.clear();\n        _checkpoints.clear();\n        std::fill(_saved_epoch.begin(),\
    \ _saved_epoch.end(), 0);\n    }\n    void release() {\n        _n = 0;\n    \
    \    _size = 1;\n        _data.assign(2, Monoid::id());\n        _history.clear();\n\
    \        _checkpoints.clear();\n        _saved_epoch.clear();\n        _next_epoch\
    \ = 1;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\n#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstdint>\n#include <utility>\n#include <vector>\n\n#include \"../../monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct RollbackSegtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    struct Entry {\n        int pos;\n        T value;\n    };\n    struct Checkpoint\
    \ {\n        std::size_t change_size;\n        std::uint64_t epoch;\n    };\n\n\
    \    int _n = 0;\n    int _size = 1;\n    std::vector<T> _data = std::vector<T>(2,\
    \ Monoid::id());\n    std::vector<Entry> _history;\n    std::vector<Checkpoint>\
    \ _checkpoints;\n    std::vector<std::uint64_t> _saved_epoch;\n    std::uint64_t\
    \ _next_epoch = 1;\n\n    std::uint64_t new_epoch() {\n        if (_next_epoch\
    \ == 0) {\n            std::fill(_saved_epoch.begin(), _saved_epoch.end(), 0);\n\
    \            _next_epoch = 1;\n        }\n        return _next_epoch++;\n    }\n\
    \n    template <class U>\n    static T make_value(const U& value, int index) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else if constexpr (requires(U x, int i) { Monoid::make(x,\
    \ i); }) {\n            return Monoid::make(value, index);\n        } else {\n\
    \            return static_cast<T>(value);\n        }\n    }\n\n    void assign(int\
    \ pos, T value) {\n        int node = pos + _size;\n        _data[node] = std::move(value);\n\
    \        while (node >>= 1) {\n            _data[node] = Monoid::op(_data[node\
    \ << 1], _data[node << 1 | 1]);\n        }\n    }\n\n    template <class U>\n\
    \    void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = 1;\n        while (_size < _n) _size <<= 1;\n        _data.assign(2\
    \ * _size, Monoid::id());\n        _saved_epoch.assign(_n, 0);\n        for (int\
    \ index = 0; index < _n; ++index) {\n            _data[_size + index] = make_value(values[index],\
    \ index);\n        }\n        for (int node = _size - 1; node > 0; --node) {\n\
    \            _data[node] = Monoid::op(_data[node << 1], _data[node << 1 | 1]);\n\
    \        }\n    }\n\n   public:\n    RollbackSegtree() = default;\n    explicit\
    \ RollbackSegtree(int n) { assert(0 <= n); build(std::vector<T>(n, Monoid::id()));\
    \ }\n    explicit RollbackSegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackSegtree(std::vector<T>&& values) { build(values); }\n\
    \n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackSegtree(const std::vector<U>& values) { build(values); }\n\n    int\
    \ size() const { return _n; }\n    bool empty() const { return _n == 0; }\n  \
    \  std::size_t node_count() const { return _data.size(); }\n\n    void set(int\
    \ pos, T value) {\n        assert(0 <= pos && pos < _n);\n        if (!_checkpoints.empty()\
    \ && _saved_epoch[pos] != _checkpoints.back().epoch) {\n            _saved_epoch[pos]\
    \ = _checkpoints.back().epoch;\n            _history.push_back(Entry{pos, get(pos)});\n\
    \        }\n        assign(pos, std::move(value));\n    }\n\n    void set_inplace(int\
    \ pos, T value) { set(pos, std::move(value)); }\n\n    T get(int pos) const {\n\
    \        assert(0 <= pos && pos < _n);\n        return _data[_size + pos];\n \
    \   }\n\n    T operator[](int pos) const { return get(pos); }\n\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        T left_product = Monoid::id();\n        T right_product = Monoid::id();\n\
    \        for (left += _size, right += _size; left < right; left >>= 1, right >>=\
    \ 1) {\n            if (left & 1) left_product = Monoid::op(left_product, _data[left++]);\n\
    \            if (right & 1) right_product = Monoid::op(_data[--right], right_product);\n\
    \        }\n        return Monoid::op(left_product, right_product);\n    }\n\n\
    \    T all_prod() const { return _data[1]; }\n\n    std::vector<T> to_vector()\
    \ const { return to_vector(0, _n); }\n    std::vector<T> to_vector(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        return std::vector<T>(_data.begin() + _size + left, _data.begin() + _size\
    \ + right);\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) const {\n        assert(0 <= left && left <= _n);\n   \
    \     assert(predicate(Monoid::id()));\n        if (left == _n) return _n;\n \
    \       int node = left + _size;\n        T product = Monoid::id();\n        do\
    \ {\n            while ((node & 1) == 0) node >>= 1;\n            T next = Monoid::op(product,\
    \ _data[node]);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node <<= 1;\n                    next = Monoid::op(product,\
    \ _data[node]);\n                    if (predicate(next)) {\n                \
    \        product = std::move(next);\n                        ++node;\n       \
    \             }\n                }\n                return std::min(_n, node -\
    \ _size);\n            }\n            product = std::move(next);\n           \
    \ ++node;\n        } while ((node & -node) != node);\n        return _n;\n   \
    \ }\n\n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ const {\n        assert(0 <= right && right <= _n);\n        assert(predicate(Monoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  T product = Monoid::id();\n        do {\n            --node;\n            while\
    \ (node > 1 && (node & 1)) node >>= 1;\n            T next = Monoid::op(_data[node],\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node = node << 1 | 1;\n                    next\
    \ = Monoid::op(_data[node], product);\n                    if (predicate(next))\
    \ {\n                        product = std::move(next);\n                    \
    \    --node;\n                    }\n                }\n                return\
    \ std::max(0, node + 1 - _size);\n            }\n            product = std::move(next);\n\
    \        } while ((node & -node) != node);\n        return 0;\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(Checkpoint{_history.size(), new_epoch()});\n\
    \        return int(_checkpoints.size());\n    }\n    int snapshot_count() const\
    \ { return int(_checkpoints.size()); }\n    void reserve_snapshots(int count)\
    \ { assert(0 <= count); _checkpoints.reserve(count); }\n\n    void rollback(int\
    \ state) {\n        assert(1 <= state && state <= snapshot_count());\n       \
    \ while (_history.size() > _checkpoints[state - 1].change_size) {\n          \
    \  Entry entry = std::move(_history.back());\n            _history.pop_back();\n\
    \            assign(entry.pos, std::move(entry.value));\n        }\n        _checkpoints.resize(state);\n\
    \        _checkpoints.back().epoch = new_epoch();\n    }\n    void clear_history()\
    \ {\n        _history.clear();\n        _checkpoints.clear();\n        std::fill(_saved_epoch.begin(),\
    \ _saved_epoch.end(), 0);\n    }\n    void release() {\n        _n = 0;\n    \
    \    _size = 1;\n        _data.assign(2, Monoid::id());\n        _history.clear();\n\
    \        _checkpoints.clear();\n        _saved_epoch.clear();\n        _next_epoch\
    \ = 1;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/segtree/rollback_segtree.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/segtree/rollback_segtree.hpp
layout: document
title: Rollback Segment Tree
---

## Overview

`RollbackSegtree<Monoid>` is a mutable segment tree with point assignment,
range products, and registered-snapshot rollback. `Monoid` must satisfy
`m1une::monoid::IsMonoid`. The tree uses one contiguous mutable segment-tree array.

## Methods

Constructors and read-only methods follow `Segtree<Monoid>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int pos, T value)`, `void set_inplace(int pos, T value)` | Assigns one point. | $O(\log N)$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Restores a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |

$F = O(\log N)$ per undone assignment and counts nodes released.

## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

Within one snapshot interval, each assigned position saves its old value only once.

## Example

```cpp
#include "ds/segtree/rollback_segtree.hpp"
#include "monoid/add.hpp"

#include <vector>

using Add = m1une::monoid::Add<long long>;
m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3});
int state = seg.snapshot();
seg.set(1, 8);
seg.rollback(state);
assert(seg.all_prod() == 6);
```
