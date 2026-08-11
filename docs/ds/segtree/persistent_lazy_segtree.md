---
title: Persistent Lazy Segment Tree
documentation_of: ../../../ds/segtree/persistent_lazy_segtree.hpp
---

## Overview

A persistent lazy segment tree for any acted monoid satisfying
`m1une::acted_monoid::IsActedMonoid`. Point assignments and range updates return
new versions while older versions remain available.
Unreferenced path nodes are recycled automatically when versions are destroyed
or overwritten, and `release()` can drop a version early.

The ordinary `set` and `apply` methods always return new versions. Their
`_inplace` counterparts mutate this handle with copy-on-write. A shared node is
cloned immediately before a write, including writes caused by lazy propagation;
an already unique node is updated directly. Every other live version stays
unchanged. This is intended for repeatedly updating a working copy of a base.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentLazySegtree(int n)` | Initializes `n` elements with the value monoid identity. | $O(N)$ |
| `PersistentLazySegtree(const std::vector<T>& v)` | Builds the tree from `v`. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `void release()` | Releases this version and makes this handle empty. | $O(F)$ |
| `size_t node_count()` | Returns live nodes in the shared version family. | $O(1)$ |
| `PersistentLazySegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `void set_inplace(int p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the acted-monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod()` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r - l)$ |
| `PersistentLazySegtree apply(int p, F f)` | Returns a new version where `f` is applied to index `p`. | $O(\log N)$ |
| `PersistentLazySegtree apply(int l, int r, F f)` | Returns a new version where `f` is applied to every element in `[l, r)`. | $O(\log N)$ |
| `void apply_inplace(int p, const F& f)` | Applies `f` at `p` in this version using copy-on-write. | $O(\log N)$ |
| `void apply_inplace(int l, int r, const F& f)` | Applies `f` over `[l, r)` in this version using copy-on-write. | $O(\log N)$ |
| `PersistentLazySegtree copy_range_from(const PersistentLazySegtree& source, int l, int r)` | Returns a new version whose `[l, r)` is copied from `source`. | $O(\log N)$ |
| `int max_right<G>(int l, G g)` | Returns the largest `r` such that `g(prod(l, r))` is `true`. | $O(\log N)$ |
| `int min_left<G>(int r, G g)` | Returns the smallest `l` such that `g(prod(l, r))` is `true`. | $O(\log N)$ |

Here $F$ is the number of nodes whose last reference is removed. Copying a
version is $O(1)$, and released slots are reused by later updates.

`copy_range_from` requires both versions to have the same size and to descend
from the same initial tree, so that they share a node pool. Neither input
version is mutated. The returned version uses the receiver outside `[l, r)`
and `source` inside `[l, r)`.

## Example

```cpp
#include "ds/segtree/persistent_lazy_segtree.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

int main() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentLazySegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4});
    Seg next = seg.apply(1, 3, 10);
    Seg mixed = seg.copy_range_from(next, 2, 4);
    Seg working = seg;
    working.apply_inplace(0, 4, 1);

    std::cout << seg.prod(0, 4).sum << "\n";   // 10
    std::cout << next.prod(0, 4).sum << "\n";  // 30
    std::cout << mixed.prod(0, 4).sum << "\n"; // 20
    std::cout << working.prod(0, 4).sum << "\n"; // 14; seg is still 10
    next.release();                            // mixed keeps shared nodes alive
}
```
