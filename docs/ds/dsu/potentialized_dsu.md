---
title: Potentialized DSU
documentation_of: ../../../ds/dsu/potentialized_dsu.hpp
---

## Overview

`PotentializedDsu` is a weighted Union-Find over a possibly noncommutative
group. It stores relative potentials inside each connected component and can
answer potential differences between two vertices.

The template parameter is a type satisfying
`m1une::monoid::IsGroup`, so the same data structure works with addition, xor,
matrix multiplication, permutation composition, and other group operations.

The main operation is `merge(a, b, w)`, which adds the constraint
`diff(a, b) == w`. Here `diff(a, b)` is defined as
`Group::op(Group::inv(potential(a)), potential(b))`.

The order of these operations is significant. If `P(v) = potential(v)`, then
`merge(a, b, w)` imposes

```text
inv(P(a)) * P(b) = w
```

or equivalently `P(b) = P(a) * w`, where `*` denotes `Group::op`. Reversing
the arguments of `merge` therefore requires both swapping the vertices and
inverting `w`.

For `m1une::monoid::Add<long long>`, this means:

```cpp
potential(b) - potential(a) == w
```

Equivalently, `diff(a, b)` is `b - a` for addition.

For `m1une::monoid::Xor<int>`, this means:

```cpp
potential(a) ^ potential(b) == w
```

Absolute values returned by `potential(v)` are root-relative and may shift when
components are merged. Use `diff(a, b)` for stable values.

## Template Parameters

* `Group`: A type satisfying `m1une::monoid::IsGroup`.

The group must provide:

* `using value_type = T`
* `static T id()`
* `static T op(const T& a, const T& b)`
* `static T inv(const T& x)`

`T` must be equality comparable so repeated constraints can be checked for
consistency.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `PotentializedDsu()` | Creates an empty DSU. | $O(1)$ |
| `explicit PotentializedDsu(int n)` | Creates `n` singleton sets with identity potentials. | $O(N)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the DSU has no elements. | $O(1)$ |
| `bool merge(int a, int b, const T& w)` | Adds the constraint `diff(a, b) == w`. Returns `false` only when `a` and `b` were already connected and the constraint contradicts the stored potentials. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b)` | Returns whether `a` and `b` are in the same set and applies path compression. | Amortized $O(\alpha(N))$ |
| `bool same(int a, int b) const` | Returns whether `a` and `b` are in the same set without mutation. | $O(\log N)$ |
| `int leader(int a)` | Returns the representative and applies path compression. | Amortized $O(\alpha(N))$ |
| `int leader(int a) const` | Returns the representative without mutation. | $O(\log N)$ |
| `int group_size(int a)`, `int size(int a)` | Returns the component size and applies path compression. | Amortized $O(\alpha(N))$ |
| `int group_size(int a) const`, `int size(int a) const` | Returns the component size without mutation. | $O(\log N)$ |
| `T potential(int a)` | Returns the root-relative potential and applies path compression. | Amortized $O(\alpha(N))$ |
| `T potential(int a) const` | Returns the root-relative potential without mutation. | $O(\log N)$ |
| `T diff(int a, int b)` | Returns the potential difference from `a` to `b` and applies path compression. Requires `same(a, b)`. | Amortized $O(\alpha(N))$ |
| `T diff(int a, int b) const` | Returns the potential difference without mutation. Requires `same(a, b)`. | $O(\log N)$ |
| `std::vector<std::vector<int>> groups()` | Returns all components and applies path compression. | $O(N \alpha(N))$ |
| `std::vector<std::vector<int>> groups() const` | Returns all components without mutation. | $O(N \log N)$ |

## Example

```cpp
#include "ds/dsu/potentialized_dsu.hpp"
#include <array>

#include <iostream>

struct Permutation3 {
    using value_type = std::array<int, 3>;

    static value_type id() {
        return {0, 1, 2};
    }

    static value_type op(const value_type& first, const value_type& second) {
        value_type result;
        for (int i = 0; i < 3; i++) result[i] = second[first[i]];
        return result;
    }

    static value_type inv(const value_type& value) {
        value_type result;
        for (int i = 0; i < 3; i++) result[value[i]] = i;
        return result;
    }
};

int main() {
    using P = Permutation3::value_type;
    m1une::ds::PotentializedDsu<Permutation3> dsu(3);

    P rotate = {1, 2, 0};
    P swap_last = {0, 2, 1};
    dsu.merge(0, 1, rotate);
    dsu.merge(1, 2, swap_last);

    P composed = dsu.diff(0, 2);
    for (int image : composed) std::cout << image << ' ';
    std::cout << '\n';
}
```
