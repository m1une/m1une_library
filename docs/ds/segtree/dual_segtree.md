---
title: Dual Segment Tree
documentation_of: ../../../ds/segtree/dual_segtree.hpp
---

## Overview

`m1une::ds::DualSegtree` is a generic dual segment tree for range
updates and point queries. Both updates and stored point values are elements of
the same monoid.

Use it when you only need point queries after range updates. If you also need
range queries, use `LazySegtree` instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

`apply(l, r, x)` updates each point value `v` in `[l, r)` to
`Monoid::op(x, v)`.

## Construction

* `DualSegtree()`: creates an empty tree.
* `explicit DualSegtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `explicit DualSegtree(const std::vector<T>& v)`: builds from monoid values.
* `explicit DualSegtree(std::vector<T>&& v)`: builds from moved monoid values.
* `template <typename U> explicit DualSegtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or
  `static_cast<T>(value)` is available.

`DualSegtree()` takes $O(1)$ time. The other constructors take $O(N)$
time and store $O(N)$ values, assuming constant-time monoid operations and copies.

## Requirements and Behavior

Let `N = size()`. Point indices must satisfy `0 <= p < N`, and ranges must
satisfy `0 <= l <= r <= N`. Empty range updates do nothing. Commutativity is not required.

The stated bounds assume constant-time algebra operations and value copies.
`T` denotes `typename Monoid::value_type`. An update replaces each
point value `v` with `Monoid::op(update, v)`: the newer update is the left
argument. Queries push pending updates and are not `const`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Pushes pending updates on the path and assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p)` | Pushes pending updates on the path and returns the value at index `p`. | $O(\log N)$ |
| `T operator[](int p)` | Returns the value at index `p`. | $O(\log N)$ |
| `void apply(int p, T x)` | Applies `x` to index `p`. | $O(\log N)$ |
| `void apply(int l, int r, T x)` | Applies `x` to every element in `[l, r)`. | $O(\log N)$ |
| `std::vector<T> to_vector()` | Pushes all pending updates and returns all elements. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r)` | Returns the elements in `[l, r)`. | $O((r - l) \log N)$ |

## Example

```cpp
#include "ds/segtree/dual_segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Add = m1une::monoid::Add<long long>;
    m1une::ds::DualSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});

    seg.apply(1, 4, 10);

    std::cout << seg.get(0) << "\n";  // 1
    std::cout << seg.get(2) << "\n";  // 13

    return 0;
}
```
