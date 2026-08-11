---
title: Range Chmin/Chmax/Add Range Sum
documentation_of: ../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
---

## Overview

`m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<T>` is a Beats acted
monoid for these range updates:

* `a[i] = min(a[i], upper)`
* `a[i] = max(a[i], lower)`
* `a[i] += add`

It aggregates range sums and is intended for `SegtreeBeats` or
`PersistentSegtreeBeats`. Each node stores the sum, minimum, second minimum,
maximum, second maximum, their occurrence counts, and the segment length.

The lazy `operator_type` represents

```cpp
f(x) = clamp(x + add, lower, upper);
```

Use `make_chmin`, `make_chmax`, and `make_add` instead of constructing that
operator directly.

## Template requirements

`T` must satisfy `std::signed_integral` and defaults to `long long`. All values,
sums, differences, products by segment lengths, accumulated additions, and
finite shifted bounds must remain representable by `T`.

`value_type` is
`RangeChminChmaxAddRangeSumNode<T>` and has these public members:

```cpp
T sum;
T maximum;
T second_maximum;
T minimum;
T second_minimum;
int maximum_count;
int minimum_count;
int length;
```

For a constant nonempty segment, `second_maximum` is
`std::numeric_limits<T>::lowest()` and `second_minimum` is
`std::numeric_limits<T>::max()`.

## Interface and complexity

Every acted-monoid operation below takes $O(1)$ time.

| Member | Description | Complexity |
| --- | --- | --- |
| `static value_type id()` | Returns the empty aggregate. | $O(1)$ |
| `static value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(1)$ |
| `static operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns $f \circ g$. | $O(1)$ |
| `static bool can_apply(const operator_type& f, const value_type& x)` | Reports whether `mapping(f, x)` can update this node without descending. | $O(1)$ |
| `static value_type mapping(const operator_type& f, const value_type& x)` | Applies an update after `can_apply` succeeds. | $O(1)$ |
| `static value_type make(const T& value)` | Constructs a one-element aggregate. | $O(1)$ |
| `static operator_type make_chmin(const T& upper)` | Constructs a range-`chmin` update. | $O(1)$ |
| `static operator_type make_chmax(const T& lower)` | Constructs a range-`chmax` update. | $O(1)$ |
| `static operator_type make_add(const T& add)` | Constructs a range-add update. | $O(1)$ |

`can_apply` succeeds when each clamp is a no-op, changes only the known extreme,
or makes the segment constant. Otherwise the Beats tree descends. With
`SegtreeBeats`, an operation takes $O(\log N+D)$, where $D$ is the number of
extra nodes visited after failed applications.

## Example

```cpp
#include "beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "ds/segtree/segtree_beats.hpp"

#include <iostream>
#include <vector>

using AM =
    m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;

int main() {
    std::vector<long long> values = {8, 3, 6, 7};
    m1une::ds::SegtreeBeats<AM> seg(values);

    seg.apply(0, 4, AM::make_chmin(6));
    seg.apply(1, 3, AM::make_chmax(5));
    seg.apply(0, 2, AM::make_add(2));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
