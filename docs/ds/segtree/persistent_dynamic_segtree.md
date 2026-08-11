---
title: Persistent Dynamic Segment Tree
documentation_of: ../../../ds/segtree/persistent_dynamic_segtree.hpp
---

## Overview

`m1une::ds::PersistentDynamicSegtree` is a persistent sparse segment tree over
a fixed integer coordinate domain. Point assignments return new versions while
older versions remain available. It supports monoid range products and boundary
searches without building the entire domain.

Every coordinate starts with the same `initial_value`. Products of untouched
segments are derived from that leaf value, so a large uniform array can remain
implicit. The default initial value is `Monoid::id()`, which gives the usual
sparse-map behavior.

All related versions share immutable domain metadata and one contiguous node
pool. Read-only queries do not allocate nodes. Products preserve coordinate
order, so non-commutative monoids are supported. Nodes whose last parent or
version reference disappears are recycled.

`set_inplace` mutates the current handle with copy-on-write. Shared nodes are
cloned before modification and unique nodes are reused; all other live versions
remain unchanged. `set` continues to return a distinct persistent version.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.
* `Index`: A non-`bool` integral coordinate type. The default is `long long`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

## Construction

* `PersistentDynamicSegtree()`: creates an empty domain `[0, 0)`.
* `PersistentDynamicSegtree(Index n)`: creates `[0, n)` with identity values.
* `PersistentDynamicSegtree(Index left, Index right)`: creates
  `[left, right)` with identity values.
* `PersistentDynamicSegtree(Index left, Index right, T initial_value)`: creates
  a domain with the specified uniform initial leaf.

Construction caches the possible untouched segment products at each depth. It
uses $O(\log U)$ memory and $O(\log^2 U)$ monoid operations, where $U$ is the
domain length. No tree node is allocated initially.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `size_type size()` | Returns the unsigned domain length. | $O(1)$ |
| `bool empty()` | Returns whether the domain is empty. | $O(1)$ |
| `Index left_bound()` | Returns the left endpoint. | $O(1)$ |
| `Index right_bound()` | Returns the right endpoint. | $O(1)$ |
| `const T& initial_value()` | Returns the uniform initial leaf value. | $O(1)$ |
| `void reserve(size_t n)` | Reserves shared-pool space for `n` nodes. | $O(K)$ |
| `size_t node_count()` | Returns live nodes in the shared version family. | $O(1)$ |
| `void release()` | Releases this root and resets the handle to the uniform initial version. | $O(F)$ |
| `PersistentDynamicSegtree set(Index p, T x)` | Returns a version assigning `x` at `p`. | $O(\log U)$ |
| `void set_inplace(Index p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log U)$ |
| `T get(Index p)` | Returns the value at `p`. | $O(\log U)$ |
| `T operator[](Index p)` | Equivalent to `get(p)`. | $O(\log U)$ |
| `T prod(Index l, Index r)` | Returns the monoid product over `[l, r)`. | $O(\log U)$ |
| `T all_prod()` | Returns the product over the entire domain. | $O(1)$ |
| `Index max_right(Index l, F f)` | Finds the largest `r` for which `f(prod(l, r))` is true. | $O(\log U)$ |
| `Index min_left(Index r, F f)` | Finds the smallest `l` for which `f(prod(l, r))` is true. | $O(\log U)$ |

Here $K$ is the number of live nodes and $F$ is the number freed by a release.
Each assignment allocates $O(\log U)$ nodes in the worst case. Copying a version
is $O(1)$. Destruction and assignment release roots automatically; freed slots
are reused.

For `max_right` and `min_left`, the identity must satisfy the predicate and the
predicate must be monotone along searched products.

## Example

```cpp
#include "ds/segtree/persistent_dynamic_segtree.hpp"
#include "monoid/add.hpp"

#include <iostream>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDynamicSegtree<Sum>;

    Seg base(-1'000'000'000LL, 1'000'000'001LL, 0);
    Seg first = base.set(-500'000'000LL, 7);
    Seg second = first.set(900'000'000LL, 11);

    std::cout << base.all_prod() << "\n";    // 0
    std::cout << first.all_prod() << "\n";   // 7
    std::cout << second.all_prod() << "\n";  // 18
    first.release();                         // second keeps shared nodes alive
}
```
