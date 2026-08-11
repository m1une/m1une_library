---
title: Persistent Dual Segment Tree
documentation_of: ../../../ds/segtree/persistent_dual_segtree.hpp
---

## Overview

A persistent dual segment tree for any monoid satisfying
`m1une::monoid::IsMonoid`. Range updates and point assignments return new
versions while older versions remain available.
Nodes are reference counted across versions and recycled after their final
parent or version handle is released.

Use it when you need versioned range updates and point queries. If you also need
range products on each version, use `PersistentLazySegtree`.

`apply(l, r, x)` updates each point value `v` in `[l, r)` to
`Monoid::op(x, v)`.

The `_inplace` updates use copy-on-write. They mutate only this handle, clone
nodes that are still shared with another version, and reuse unique nodes.
Ordinary `set` and `apply` keep their fully persistent, return-a-version
semantics.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentDualSegtree(int n)` | Initializes `n` elements with the monoid identity. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<T>& v)` | Builds the tree from monoid values. | $O(N)$ |
| `PersistentDualSegtree(const std::vector<U>& v)` | Builds from another value type when `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)` is available. | $O(N)$ |
| `int size()` | Returns the number of elements. | $O(1)$ |
| `bool empty()` | Returns whether the tree is empty. | $O(1)$ |
| `void release()` | Releases this version and makes this handle empty. | $O(F)$ |
| `size_t node_count()` | Returns live nodes in the shared version family. | $O(1)$ |
| `PersistentDualSegtree set(int p, T x)` | Returns a new version where index `p` is assigned `x`. | $O(\log N)$ |
| `void set_inplace(int p, T x)` | Assigns `x` in this version using copy-on-write. | $O(\log N)$ |
| `T get(int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int p, T x)` | Returns a new version where `x` is applied to index `p`. | $O(\log N)$ |
| `PersistentDualSegtree apply(int l, int r, T x)` | Returns a new version where `x` is applied to every element in `[l, r)`. | $O(\log N)$ |
| `void apply_inplace(int p, const T& x)` | Applies `x` at `p` in this version using copy-on-write. | $O(\log N)$ |
| `void apply_inplace(int l, int r, const T& x)` | Applies `x` over `[l, r)` in this version using copy-on-write. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O(\log N + r - l)$ |

Here $F$ is the number of nodes that become unreachable. Destruction and
assignment release versions automatically; `release()` is useful when a handle
must stay in scope. Released slots are reused.

## Example

```cpp
#include "ds/segtree/persistent_dual_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    using Seg = m1une::ds::PersistentDualSegtree<Add>;

    Seg seg(std::vector<long long>{1, 2, 3, 4});
    Seg next = seg.apply(1, 3, 10);

    std::cout << seg.get(2) << "\n";   // 3
    std::cout << next.get(2) << "\n";  // 13
}
```
