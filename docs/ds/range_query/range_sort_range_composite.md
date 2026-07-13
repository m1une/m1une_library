---
title: Range Sort Range Composite
documentation_of: ../../../ds/range_query/range_sort_range_composite.hpp
---

## Overview

`RangeSortRangeComposite<Monoid>` maintains a fixed-length sequence of distinct
integer keys and monoid values. It supports point replacement, range products,
and sorting any half-open range by key in ascending or descending order.

Internally, each currently sorted run is represented by a dynamic key segment
tree that stores both forward and reverse products. A boundary set and an outer
segment tree combine the runs. This is commonly called a sortable segment tree.

## Template and Key Requirements

`Monoid` must satisfy `m1une::monoid::IsMonoid`:

```cpp
using value_type = T;
static T id();
static T op(const T& left, const T& right);
```

The supplied keys must be distinct integers in `[0, key_count)`. Every `set`
must preserve this property. Coordinate-compress all initial and future keys
before construction when the original key values are arbitrary.

`Monoid::op` need not be commutative. Products preserve the current left-to-right
sequence order.

## Public Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `RangeSortRangeComposite()` | Constructs an empty sequence with no key domain. | $O(1)$ |
| `RangeSortRangeComposite(int key_count, const std::vector<int>& keys, const std::vector<T>& values)` | Constructs the sequence. `keys.size()` must equal `values.size()`. | $O(N\log K)$ time and memory |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `int key_count() const` | Returns the compressed key-domain size. | $O(1)$ |
| `std::pair<int, T> get(int position)` | Returns the key and value at `position`. | Amortized $O(\log K\log N)$ |
| `void set(int position, int key, T value)` | Replaces one key-value pair. | Amortized $O(\log K\log N)$ |
| `T prod(int left, int right)` | Returns the ordered monoid product over `[left, right)`. | Amortized $O(\log K\log N)$ |
| `T all_prod() const` | Returns the product of the complete sequence. | $O(1)$ |
| `void sort_ascending(int left, int right)` | Sorts `[left, right)` by increasing key. | Amortized $O((B+1)(\log K+\log N))$ |
| `void sort_descending(int left, int right)` | Sorts `[left, right)` by decreasing key. | Amortized $O((B+1)(\log K+\log N))$ |

Here, $N$ is the sequence length, $K$ is `key_count`, and $B$ is the number of
stored run boundaries removed by a sort. Across operations, a boundary must be
created before it can be removed, so the boundary-dependent work amortizes.
The implementation periodically rebuilds its internal node pool without
changing the logical sequence.

`get`, `set`, `prod`, and sorting may refine or merge the internal run
partition, so they are mutating member functions. `all_prod` does not mutate
the representation.

## Example

This example stores affine functions. The monoid operation composes the right
function after the left function, matching left-to-right sequence application.

```cpp
#include "ds/range_query/range_sort_range_composite.hpp"

#include <iostream>
#include <utility>
#include <vector>

struct Affine {
    using value_type = std::pair<long long, long long>;

    static value_type id() {
        return {1, 0};
    }

    static value_type op(const value_type& left, const value_type& right) {
        return {
            right.first * left.first,
            right.first * left.second + right.second
        };
    }
};

int main() {
    std::vector<int> keys = {2, 0, 1};
    std::vector<Affine::value_type> functions;
    functions.emplace_back(2, 1);
    functions.emplace_back(1, 3);
    functions.emplace_back(3, 0);

    m1une::ds::RangeSortRangeComposite<Affine> data(3, keys, functions);
    data.sort_ascending(0, 3);

    auto composed = data.prod(0, 3);
    long long x = 4;
    std::cout << composed.first * x + composed.second << "\n";
}
```
