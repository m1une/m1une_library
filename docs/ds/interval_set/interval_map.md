---
title: Interval Map
documentation_of: ../../../ds/interval_set/interval_map.hpp
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
