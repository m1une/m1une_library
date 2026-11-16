---
title: Segment Tree
documentation_of: ../../../ds/segtree/segtree.hpp
---

## Overview

`m1une::ds::Segtree` is a generic segment tree for point updates and
range queries. The query operation is supplied by a monoid, so the same data
structure can handle sums, minimums, maximums, gcd, affine composition, and other
associative operations.

Use it when updates affect one position at a time. For range updates, use
`LazySegtree` with an acted monoid instead.

## Template Parameters

* `Monoid`: A type satisfying `m1une::monoid::IsMonoid`.

The monoid must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`

Ready-made monoids are available in `monoid/`.

## Construction

* `Segtree()`: creates an empty tree.
* `explicit Segtree(int n)`: creates `n` elements initialized with `Monoid::id()`.
* `explicit Segtree(const std::vector<T>& v)`: builds from monoid values.
* `explicit Segtree(std::vector<T>&& v)`: builds from moved monoid values.
* `template <typename U> explicit Segtree(const std::vector<U>& v)`: builds from another value type when
  `Monoid::make(value)`, `Monoid::make(value, index)`, or `static_cast<T>(value)`
  is available.

`Segtree()` takes $O(1)$ time. The other constructors take $O(N)$
time and store $O(N)$ values, assuming constant-time algebra operations and copies.

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
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the tree has no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns `x` to index `p`. | $O(\log N)$ |
| `T get(int p) const` | Returns the value at index `p`. | $O(1)$ |
| `T operator[](int p) const` | Returns the value at index `p`. | $O(1)$ |
| `T prod(int l, int r) const` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod() const` | Returns the product of the entire array. | $O(1)$ |
| `std::vector<T> to_vector() const` | Returns all elements as a vector. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Returns the elements in `[l, r)`. | $O(r - l)$ |
| `template <class F> int max_right(int l, F f) const` | Returns the largest `r` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |
| `template <class F> int min_left(int r, F f) const` | Returns the smallest `l` such that `f(prod(l, r))` is `true`. Requires `f(Monoid::id())`. | $O(\log N)$ |

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/add.hpp"
#include <iostream>
#include <vector>

int main() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::ds::Segtree<Sum> seg(std::vector<long long>{0, 0, 0, 0, 0});

    seg.set(0, 10);
    seg.set(2, 20);

    std::cout << seg.prod(0, 3) << "\n";  // 30

    return 0;
}
```
