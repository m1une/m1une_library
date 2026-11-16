---
title: Persistent Segment Tree
documentation_of: ../../../ds/segtree/persistent_segtree.hpp
---

## Overview

A persistent segment tree for any monoid satisfying `m1une::monoid::IsMonoid`.
Point updates return a new tree while keeping older versions available.
Versions use reference-counted path nodes. Destroying, overwriting, or explicitly
releasing a version recursively recycles every node that has no remaining parent.

`set` always returns a new persistent version. `set_inplace` instead mutates the
current handle with copy-on-write: nodes shared with another live version are
cloned before modification, while already unique path nodes are reused. Other
versions remain unchanged. This is useful for a mutable working copy derived
from a persistent base.

## Requirements and Behavior

Let `N = size()`. Point indices must satisfy `0 <= p < N`, and ranges must
satisfy `0 <= l <= r <= N`. An empty product is the identity. Products combine
elements from left to right; commutativity is not required.

The stated bounds assume constant-time algebra operations and value copies.
`T` denotes `typename Monoid::value_type`.

For `max_right` and `min_left`, the predicate must return `true` on the identity
and must be monotone as the range grows: once it becomes `false`, it must stay
false. It must return the same result each time for the same value. For
example, `sum <= limit` works with nonnegative array values and `limit >= 0`;
negative elements can violate this requirement. Searches return `N` or `0`
when the whole available range satisfies the predicate.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentSegtree()` | Creates an empty version. | $O(1)$ |
| `explicit PersistentSegtree(int n)` | Initializes `n` elements with the monoid identity. | $O(N)$ |
| `explicit PersistentSegtree(const std::vector<T>& v)` | Builds the tree from `v`. | $O(N)$ |
| `explicit PersistentSegtree(std::vector<T>&& v)` | Builds from moved values. | $O(N)$ |
| `template <typename U> explicit PersistentSegtree(const std::vector<U>& v)` | Builds using `Monoid::make(value)`, then `make(value, index)`, then conversion to `T`, in that priority order. | $O(N)$ |
| `PersistentSegtree(const PersistentSegtree& other)` | Shares the old version's nodes. | $O(1)$ |
| `PersistentSegtree(PersistentSegtree&& other) noexcept` | Transfers the version handle and empties `other`. | $O(1)$ |
| `PersistentSegtree& operator=(const PersistentSegtree& other)` | Releases this handle and shares `other`'s version. | $O(F + 1)$ |
| `PersistentSegtree& operator=(PersistentSegtree&& other) noexcept` | Releases this handle, transfers the version, and empties `other`. | $O(F + 1)$ |
| `~PersistentSegtree()` | Releases this handle's nodes. | $O(F + 1)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the tree is empty. | $O(1)$ |
| `void release()` | Releases this version and makes this handle empty. | $O(F + 1)$ |
| `std::size_t node_count() const` | Returns the number of live nodes in the shared version family. | $O(1)$ |
| `PersistentSegtree set(int p, T x) const` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `void set_inplace(int p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log N)$ |
| `T get(int p) const` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p) const` | Returns the value at index `p`. | $O(\log N)$ |
| `T prod(int l, int r) const` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod() const` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector() const` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Returns the elements in `[l, r)`. | $O(\log N + r - l)$ |
| `template <class F> int max_right(int l, F f) const` | Returns the largest `r` such that `f(prod(l, r))` is `true`. | $O(\log N)$ |
| `template <class F> int min_left(int r, F f) const` | Returns the smallest `l` such that `f(prod(l, r))` is `true`. | $O(\log N)$ |

Here $F$ is the number of nodes that become unreachable when releasing the old
handle. It is unrelated to the predicate template parameter `F`. Copying a version is
$O(1)$. Released node slots are reused by later updates in the same family.

## Example

```cpp
#include "ds/segtree/persistent_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Seg = m1une::ds::PersistentSegtree<m1une::monoid::Add<long long>>;

    Seg seg(std::vector<long long>{1, 2, 3});
    Seg next = seg.set(1, 10);

    std::cout << seg.prod(0, 3) << "\n";   // 6
    std::cout << next.prod(0, 3) << "\n";  // 14
    next.release();                         // unique path nodes are recycled
}
```
