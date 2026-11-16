---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/interval_set/interval_map.test.cpp
    title: verify/ds/interval_set/interval_map.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/interval_set/interval_map.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <iterator>\n#include <limits>\n\
    #include <memory>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// A sparse piecewise-constant map. Adjacent intervals\
    \ with equal values merge.\ntemplate <class Key, class T>\nclass IntervalMap {\n\
    \   public:\n    using key_type = Key;\n    using value_type = T;\n\n    struct\
    \ interval_type {\n        Key l;\n        Key r;\n        T value;\n    };\n\n\
    \   private:\n    struct Compare {\n        using is_transparent = void;\n\n \
    \       bool operator()(const interval_type& a, const interval_type& b) const\
    \ {\n            return a.l < b.l;\n        }\n        bool operator()(const interval_type&\
    \ a, const Key& b) const { return a.l < b; }\n        bool operator()(const Key&\
    \ a, const interval_type& b) const { return a < b.l; }\n    };\n\n    using Set\
    \ = std::set<interval_type, Compare>;\n    using iterator = typename Set::iterator;\n\
    \    Set _intervals;\n\n    static bool equal_key(const Key& a, const Key& b)\
    \ {\n        return !(a < b) && !(b < a);\n    }\n\n    // Creates a boundary\
    \ at x if x is strictly inside a stored interval.\n    // The extracted left node\
    \ is reused; only the right node is allocated.\n    iterator split(Key x) {\n\
    \        auto right = _intervals.lower_bound(x);\n        if (right != _intervals.end()\
    \ && equal_key(right->l, x)) return right;\n        if (right == _intervals.begin())\
    \ return right;\n        auto left = std::prev(right);\n        if (!(x < left->r))\
    \ return right;\n\n        right = _intervals.emplace_hint(right, interval_type{x,\
    \ left->r, left->value});\n        auto node = _intervals.extract(left);\n   \
    \     node.value().r = std::move(x);\n        _intervals.insert(right, std::move(node));\n\
    \        return right;\n    }\n\n    template <class Callback>\n    iterator erase_range(Key\
    \ l, Key r, Callback& on_erase) {\n        auto last = split(r);\n        auto\
    \ first = split(l);\n        for (auto it = first; it != last; ++it) on_erase(it->l,\
    \ it->r, it->value);\n        return _intervals.erase(first, last);\n    }\n\n\
    \   public:\n    using const_iterator = typename Set::const_iterator;\n\n    IntervalMap()\
    \ = default;\n\n    IntervalMap(Key l, Key r, T value) { assign(l, r, std::move(value));\
    \ }\n\n    // Input intervals must be nonempty, sorted, and nonoverlapping.\n\
    \    explicit IntervalMap(const std::vector<interval_type>& intervals) {\n   \
    \     for (const auto& interval : intervals) {\n            assert(interval.l\
    \ < interval.r);\n            if (!_intervals.empty()) {\n                auto\
    \ previous = std::prev(_intervals.end());\n                assert(!(interval.l\
    \ < previous->r));\n                if (equal_key(previous->r, interval.l) &&\
    \ previous->value == interval.value) {\n                    auto node = _intervals.extract(previous);\n\
    \                    node.value().r = interval.r;\n                    _intervals.insert(_intervals.end(),\
    \ std::move(node));\n                    continue;\n                }\n      \
    \      }\n            _intervals.insert(_intervals.end(), interval);\n       \
    \ }\n    }\n\n    // Dense array convenience constructor: values[i] is assigned\
    \ to [i, i + 1).\n    explicit IntervalMap(const std::vector<T>& values) requires\
    \ std::same_as<Key, int> {\n        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(values.size());\n        for (int l = 0; l < n;) {\n\
    \            int r = l + 1;\n            while (r < n && values[l] == values[r])\
    \ ++r;\n            _intervals.emplace_hint(_intervals.end(), interval_type{l,\
    \ r, values[l]});\n            l = r;\n        }\n    }\n\n    int size() const\
    \ { return int(_intervals.size()); }\n\n    bool empty() const { return _intervals.empty();\
    \ }\n\n    void clear() { _intervals.clear(); }\n\n    // Returns the interval\
    \ containing x, rather than requiring x to be a boundary.\n    const_iterator\
    \ find(Key x) const {\n        auto it = _intervals.upper_bound(x);\n        if\
    \ (it == _intervals.begin()) return _intervals.end();\n        --it;\n       \
    \ return x < it->r ? it : _intervals.end();\n    }\n\n    bool contains(Key x)\
    \ const { return find(x) != end(); }\n\n    const T& get(Key x) const {\n    \
    \    auto it = find(x);\n        assert(it != end());\n        return it->value;\n\
    \    }\n\n    const T* get_if(Key x) const {\n        auto it = find(x);\n   \
    \     return it == end() ? nullptr : std::addressof(it->value);\n    }\n\n   \
    \ void assign(Key l, Key r, T value) {\n        assign(l, r, std::move(value),\
    \ [](Key, Key, const T&) {});\n    }\n\n    // Calls on_erase(a, b, old_value)\
    \ for covered parts of [l, r), even when\n    // old_value == value. Gaps do not\
    \ generate callbacks. The value is owned\n    // before any erasure, so assign(l,\
    \ r, get(x)) is safe.\n    template <class Callback>\n    void assign(Key l, Key\
    \ r, T value, Callback&& on_erase) {\n        assert(!(r < l));\n        if (!(l\
    \ < r)) return;\n        auto right = erase_range(l, r, on_erase);\n\n       \
    \ if (right != _intervals.begin()) {\n            auto left = std::prev(right);\n\
    \            if (equal_key(left->r, l) && left->value == value) {\n          \
    \      l = left->l;\n                _intervals.erase(left);\n            }\n\
    \        }\n        if (right != _intervals.end() && equal_key(r, right->l) &&\
    \ right->value == value) {\n            r = right->r;\n            right = _intervals.erase(right);\n\
    \        }\n        _intervals.emplace_hint(right, interval_type{std::move(l),\
    \ std::move(r), std::move(value)});\n    }\n\n    void erase(Key l, Key r) { erase(l,\
    \ r, [](Key, Key, const T&) {}); }\n\n    template <class Callback>\n    void\
    \ erase(Key l, Key r, Callback&& on_erase) {\n        assert(!(r < l));\n    \
    \    if (l < r) erase_range(l, r, on_erase);\n    }\n\n    // Visits the covered\
    \ parts of [l, r), clipped to the query and in order.\n    // No callback may\
    \ modify this map while traversal or an update is active.\n    template <class\
    \ Callback>\n    void for_each(Key l, Key r, Callback&& callback) const {\n  \
    \      assert(!(r < l));\n        if (!(l < r)) return;\n        auto it = _intervals.lower_bound(l);\n\
    \        if (it != _intervals.begin()) {\n            auto previous = std::prev(it);\n\
    \            if (l < previous->r) it = previous;\n        }\n        for (; it\
    \ != _intervals.end() && it->l < r; ++it) {\n            callback(std::max(l,\
    \ it->l), std::min(r, it->r), it->value);\n        }\n    }\n\n    std::vector<interval_type>\
    \ to_vector() const {\n        return std::vector<interval_type>(begin(), end());\n\
    \    }\n\n    const_iterator begin() const { return _intervals.begin(); }\n\n\
    \    const_iterator end() const { return _intervals.end(); }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_INTERVAL_MAP_HPP\n#define M1UNE_DS_INTERVAL_MAP_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <concepts>\n#include <iterator>\n\
    #include <limits>\n#include <memory>\n#include <set>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// A sparse piecewise-constant\
    \ map. Adjacent intervals with equal values merge.\ntemplate <class Key, class\
    \ T>\nclass IntervalMap {\n   public:\n    using key_type = Key;\n    using value_type\
    \ = T;\n\n    struct interval_type {\n        Key l;\n        Key r;\n       \
    \ T value;\n    };\n\n   private:\n    struct Compare {\n        using is_transparent\
    \ = void;\n\n        bool operator()(const interval_type& a, const interval_type&\
    \ b) const {\n            return a.l < b.l;\n        }\n        bool operator()(const\
    \ interval_type& a, const Key& b) const { return a.l < b; }\n        bool operator()(const\
    \ Key& a, const interval_type& b) const { return a < b.l; }\n    };\n\n    using\
    \ Set = std::set<interval_type, Compare>;\n    using iterator = typename Set::iterator;\n\
    \    Set _intervals;\n\n    static bool equal_key(const Key& a, const Key& b)\
    \ {\n        return !(a < b) && !(b < a);\n    }\n\n    // Creates a boundary\
    \ at x if x is strictly inside a stored interval.\n    // The extracted left node\
    \ is reused; only the right node is allocated.\n    iterator split(Key x) {\n\
    \        auto right = _intervals.lower_bound(x);\n        if (right != _intervals.end()\
    \ && equal_key(right->l, x)) return right;\n        if (right == _intervals.begin())\
    \ return right;\n        auto left = std::prev(right);\n        if (!(x < left->r))\
    \ return right;\n\n        right = _intervals.emplace_hint(right, interval_type{x,\
    \ left->r, left->value});\n        auto node = _intervals.extract(left);\n   \
    \     node.value().r = std::move(x);\n        _intervals.insert(right, std::move(node));\n\
    \        return right;\n    }\n\n    template <class Callback>\n    iterator erase_range(Key\
    \ l, Key r, Callback& on_erase) {\n        auto last = split(r);\n        auto\
    \ first = split(l);\n        for (auto it = first; it != last; ++it) on_erase(it->l,\
    \ it->r, it->value);\n        return _intervals.erase(first, last);\n    }\n\n\
    \   public:\n    using const_iterator = typename Set::const_iterator;\n\n    IntervalMap()\
    \ = default;\n\n    IntervalMap(Key l, Key r, T value) { assign(l, r, std::move(value));\
    \ }\n\n    // Input intervals must be nonempty, sorted, and nonoverlapping.\n\
    \    explicit IntervalMap(const std::vector<interval_type>& intervals) {\n   \
    \     for (const auto& interval : intervals) {\n            assert(interval.l\
    \ < interval.r);\n            if (!_intervals.empty()) {\n                auto\
    \ previous = std::prev(_intervals.end());\n                assert(!(interval.l\
    \ < previous->r));\n                if (equal_key(previous->r, interval.l) &&\
    \ previous->value == interval.value) {\n                    auto node = _intervals.extract(previous);\n\
    \                    node.value().r = interval.r;\n                    _intervals.insert(_intervals.end(),\
    \ std::move(node));\n                    continue;\n                }\n      \
    \      }\n            _intervals.insert(_intervals.end(), interval);\n       \
    \ }\n    }\n\n    // Dense array convenience constructor: values[i] is assigned\
    \ to [i, i + 1).\n    explicit IntervalMap(const std::vector<T>& values) requires\
    \ std::same_as<Key, int> {\n        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(values.size());\n        for (int l = 0; l < n;) {\n\
    \            int r = l + 1;\n            while (r < n && values[l] == values[r])\
    \ ++r;\n            _intervals.emplace_hint(_intervals.end(), interval_type{l,\
    \ r, values[l]});\n            l = r;\n        }\n    }\n\n    int size() const\
    \ { return int(_intervals.size()); }\n\n    bool empty() const { return _intervals.empty();\
    \ }\n\n    void clear() { _intervals.clear(); }\n\n    // Returns the interval\
    \ containing x, rather than requiring x to be a boundary.\n    const_iterator\
    \ find(Key x) const {\n        auto it = _intervals.upper_bound(x);\n        if\
    \ (it == _intervals.begin()) return _intervals.end();\n        --it;\n       \
    \ return x < it->r ? it : _intervals.end();\n    }\n\n    bool contains(Key x)\
    \ const { return find(x) != end(); }\n\n    const T& get(Key x) const {\n    \
    \    auto it = find(x);\n        assert(it != end());\n        return it->value;\n\
    \    }\n\n    const T* get_if(Key x) const {\n        auto it = find(x);\n   \
    \     return it == end() ? nullptr : std::addressof(it->value);\n    }\n\n   \
    \ void assign(Key l, Key r, T value) {\n        assign(l, r, std::move(value),\
    \ [](Key, Key, const T&) {});\n    }\n\n    // Calls on_erase(a, b, old_value)\
    \ for covered parts of [l, r), even when\n    // old_value == value. Gaps do not\
    \ generate callbacks. The value is owned\n    // before any erasure, so assign(l,\
    \ r, get(x)) is safe.\n    template <class Callback>\n    void assign(Key l, Key\
    \ r, T value, Callback&& on_erase) {\n        assert(!(r < l));\n        if (!(l\
    \ < r)) return;\n        auto right = erase_range(l, r, on_erase);\n\n       \
    \ if (right != _intervals.begin()) {\n            auto left = std::prev(right);\n\
    \            if (equal_key(left->r, l) && left->value == value) {\n          \
    \      l = left->l;\n                _intervals.erase(left);\n            }\n\
    \        }\n        if (right != _intervals.end() && equal_key(r, right->l) &&\
    \ right->value == value) {\n            r = right->r;\n            right = _intervals.erase(right);\n\
    \        }\n        _intervals.emplace_hint(right, interval_type{std::move(l),\
    \ std::move(r), std::move(value)});\n    }\n\n    void erase(Key l, Key r) { erase(l,\
    \ r, [](Key, Key, const T&) {}); }\n\n    template <class Callback>\n    void\
    \ erase(Key l, Key r, Callback&& on_erase) {\n        assert(!(r < l));\n    \
    \    if (l < r) erase_range(l, r, on_erase);\n    }\n\n    // Visits the covered\
    \ parts of [l, r), clipped to the query and in order.\n    // No callback may\
    \ modify this map while traversal or an update is active.\n    template <class\
    \ Callback>\n    void for_each(Key l, Key r, Callback&& callback) const {\n  \
    \      assert(!(r < l));\n        if (!(l < r)) return;\n        auto it = _intervals.lower_bound(l);\n\
    \        if (it != _intervals.begin()) {\n            auto previous = std::prev(it);\n\
    \            if (l < previous->r) it = previous;\n        }\n        for (; it\
    \ != _intervals.end() && it->l < r; ++it) {\n            callback(std::max(l,\
    \ it->l), std::min(r, it->r), it->value);\n        }\n    }\n\n    std::vector<interval_type>\
    \ to_vector() const {\n        return std::vector<interval_type>(begin(), end());\n\
    \    }\n\n    const_iterator begin() const { return _intervals.begin(); }\n\n\
    \    const_iterator end() const { return _intervals.end(); }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_INTERVAL_MAP_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/interval_set/interval_map.hpp
  requiredBy: []
  timestamp: '2026-11-17 03:01:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/interval_set/interval_map.test.cpp
documentation_of: ds/interval_set/interval_map.hpp
layout: document
title: Interval Map
---

## Overview

`m1une::ds::IntervalMap<Key, T>` stores a piecewise-constant function as
disjoint half-open intervals `[l, r)` with associated values. Assigning a range
splits its boundary intervals, replaces the covered values, and merges adjacent
intervals whose values are equal. Erasing a range leaves an uncovered gap.

Use it for range recoloring, sparse assignments on large coordinates, and
maintaining statistics with callbacks for the old values. It stores only the
current runs, rather than one entry per coordinate. For coverage without
associated values, use
[IntervalSet](https://m1une.github.io/m1une_library/ds/interval_set/interval_set.hpp).

## Template Parameters

* `Key`: A copyable coordinate type with a strict total ordering through `<`.
  Arithmetic, a default constructor, and `==` are not required. Floating-point
  coordinates must exclude NaNs.
* `T`: A copyable value type with `==` defining an equivalence relation.
  Neither ordering, arithmetic, nor a default constructor is required.

The public types are:

```cpp
using key_type = Key;
using value_type = T;

struct interval_type {
    Key l;
    Key r;
    T value;
};
```

`const_iterator` iterates over these records in increasing order of `l`.
Stored intervals are nonempty and nonoverlapping. Adjacent intervals with equal
values are always merged after construction or an update. Equal-valued
intervals separated by a gap remain separate.

## Interface and Complexity

Let `I` be the number of stored intervals, `N` the number of constructor input
records or array elements, and `K` the number of stored intervals intersecting
the requested range. Bounds assume constant-time coordinate comparisons, value
copies, and value equality tests. Add the cost of each callback invocation.
Memory usage is $O(I)$, with one balanced-tree node per stored interval.

| Method | Description | Complexity |
| --- | --- | --- |
| `IntervalMap()` | Creates an empty map with no covered points. | $O(1)$ |
| `IntervalMap(Key l, Key r, T value)` | Assigns `value` to `[l, r)` in an initially empty map. | $O(1)$ |
| `explicit IntervalMap(const std::vector<interval_type>& intervals)` | Builds from nonempty, sorted, nonoverlapping intervals; equal adjacent runs are merged. | $O(N)$ amortized |
| `explicit IntervalMap(const std::vector<T>& values) requires std::same_as<Key, int>` | Builds the array with `values[i]` on `[i, i + 1)`. Requires `values.size() <= INT_MAX`. | $O(N)$ amortized |
| `int size() const` | Returns the number of stored intervals, not the covered length. | $O(1)$ |
| `bool empty() const` | Returns whether no point is covered. | $O(1)$ |
| `void clear()` | Removes all intervals without invoking callbacks. | $O(I)$ |
| `const_iterator find(Key x) const` | Returns the interval containing `x`, or `end()` when uncovered. `x` need not be a boundary. | $O(\log(I + 1))$ |
| `bool contains(Key x) const` | Returns whether `x` is covered. | $O(\log(I + 1))$ |
| `const T& get(Key x) const` | Returns the value at a covered point. Asserts if `x` is uncovered. | $O(\log(I + 1))$ |
| `const T* get_if(Key x) const` | Returns a pointer to the value at `x`, or `nullptr` when uncovered. | $O(\log(I + 1))$ |
| `void assign(Key l, Key r, T value)` | Overwrites `[l, r)`, filling gaps and coalescing equal neighbors. | Amortized $O(\log(I + 1) + K)$ |
| `template <class Callback> void assign(Key l, Key r, T value, Callback&& on_erase)` | Reports the old covered portions, then performs the assignment. | Amortized $O(\log(I + 1) + K)$ |
| `void erase(Key l, Key r)` | Removes coverage on `[l, r)` and preserves the parts outside it. | Amortized $O(\log(I + 1) + K)$ |
| `template <class Callback> void erase(Key l, Key r, Callback&& on_erase)` | Reports the removed covered portions, then erases them. | Amortized $O(\log(I + 1) + K)$ |
| `template <class Callback> void for_each(Key l, Key r, Callback&& callback) const` | Visits the covered portions of `[l, r)` without changing the map. | $O(\log(I + 1) + K)$ |
| `std::vector<interval_type> to_vector() const` | Copies all interval records in coordinate order. | $O(I)$ time and returned space |
| `const_iterator begin() const` | Returns the first stored interval. | $O(1)$ |
| `const_iterator end() const` | Returns the past-the-end iterator. | $O(1)$ |

Copy construction takes $O(I)$ time and space. Move construction is $O(1)$.
Assignment and destruction also account for releasing the destination's old
nodes. These are ordinary value semantics; copies can be updated independently.

## Range and Callback Semantics

Every range must satisfy `!(r < l)`; invalid endpoint order asserts. Empty
ranges do nothing and invoke no callbacks. The map has no fixed universe:
assignments may extend beyond the range initialized by a constructor. No
infinite sentinels or endpoint increments are used internally.

All callbacks have the call form `callback(Key a, Key b, const T& old_value)`.
They run in increasing coordinate order, once per intersecting old interval,
with `[a, b)` clipped to the requested range. Uncovered gaps are skipped.
Assignment reports old portions even when their values equal the new value.
Coalescing a neighbor outside the assigned range produces no extra callback.

An assignment's new value is passed by value before any erasure, so
`map.assign(l, r, map.get(x))` is valid. To maintain a sum, subtract the old
contribution in `on_erase` and add `(r - l) * new_value` once for the assigned
range, including any newly covered gaps.

Callbacks must not modify the same map and must return normally. References
passed to an update callback must not be retained after the update. Splitting,
erasing, or merging intervals may invalidate their iterators and value
references; intervals outside the affected runs remain valid. Public iteration
is read-only so values cannot be changed without restoring the run invariant.

One update can visit every stored interval. Over a sequence of assignments and
erasures, however, each update creates at most a constant number of new runs.
Starting with `I0` runs, `Q` updates therefore take
$O((I0 + Q)\log(I0 + Q + 1))$ amortized time, excluding callback costs.
Repeated `for_each` queries still pay for every run they visit.

## Example

```cpp
#include "ds/interval_set/interval_map.hpp"
#include <cassert>

int main() {
    m1une::ds::IntervalMap<int, long long> map(0, 8, 2);
    long long total = 16;

    map.assign(2, 6, 5, [&](int l, int r, const long long& old_value) {
        total -= (r - l) * old_value;
    });
    total += (6 - 2) * 5;
    assert(total == 28);
    assert(map.size() == 3);  // [0, 2): 2, [2, 6): 5, [6, 8): 2.
    assert(map.get(3) == 5);

    map.assign(6, 8, 5);     // The two neighboring runs with value 5 merge.
    auto run = map.find(7);
    assert(run->l == 2 && run->r == 8 && run->value == 5);

    map.erase(3, 4);         // Leaves an uncovered gap.
    assert(map.get_if(3) == nullptr);

    long long covered_length = 0;
    map.for_each(1, 7, [&](int l, int r, const long long&) {
        covered_length += r - l;
    });
    assert(covered_length == 5);
}
```

## Verification

The verification target solves Library Checker's
[Range Set Range Composite](https://github.com/yosupo06/library-checker-problems/tree/master/data_structure/range_set_range_composite)
using the interval map to maintain constant-function runs and a segment tree
to combine their products. It also checks sparse assignments and erasures,
callback clipping and ordering, coalescing, const queries, extreme coordinates,
and generic types against focused assertions and a randomized naive model.
