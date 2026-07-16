---
title: Offline Rectangle Add Rectangle Sum
documentation_of: ../../../ds/range_query/offline_rectangle_add_rectangle_sum.hpp
---

## Overview

`m1une::ds::OfflineRectangleAddRectangleSum<T, X, Y>` records additions to
axis-aligned rectangles and rectangle-sum queries, then evaluates the complete
batch with an offline sweep.

Every rectangle is half-open:

$$
[x_l,x_r)\times[y_l,y_r).
$$

An update adds `value` to every unit cell in its rectangle. A query returns the
sum of all cells in its rectangle. Equivalently, the structure computes the
area-weighted integral of the piecewise-constant rectangle additions. Integer
coordinates therefore match the usual grid interpretation exactly.

All recorded updates affect every recorded query. Insertion order is not a time
axis. Query IDs and returned answers use query insertion order, and repeated
calls to `calculate()` do not mutate the batch.

## Requirements

```cpp
template <class T, class X = long long, class Y = X>
class OfflineRectangleAddRectangleSum;
```

* `X` and `Y` must be strictly ordered by `<`.
* `T{}` must be zero. `T` must support copying, `+=`, `-=`, addition,
  subtraction, and multiplication.
* Coordinates must be explicitly constructible as `T`. Coordinate products are
  performed after conversion to `T`, which is useful for modular arithmetic.
* Exact arithmetic results must fit in `T`, unless `T` intentionally implements
  modular arithmetic.

## Interface

```cpp
using value_type = T;
using x_type = X;
using y_type = Y;

int update_count() const;
int query_count() const;
bool empty() const;

void reserve_updates(int capacity);
void reserve_queries(int capacity);
void clear();

int add_rectangle(
    const X& x_lower,
    const X& x_upper,
    const Y& y_lower,
    const Y& y_upper,
    const T& value
);

int add_query(
    const X& x_lower,
    const X& x_upper,
    const Y& y_lower,
    const Y& y_upper
);

std::vector<T> calculate() const;
```

## Operations

| Method | Description | Complexity |
| --- | --- | --- |
| Default construction | Creates an empty batch. | $O(1)$ |
| `update_count()` | Returns the number of recorded rectangle additions. | $O(1)$ |
| `query_count()` | Returns the number of recorded sum queries. | $O(1)$ |
| `empty()` | Returns whether both logs are empty. | $O(1)$ |
| `reserve_updates(capacity)` | Reserves update storage. | $O(N)$ worst case |
| `reserve_queries(capacity)` | Reserves query storage. | $O(Q)$ worst case |
| `clear()` | Removes every update and query while preserving allocated capacity. | $O(N+Q)$ |
| `add_rectangle(xl, xr, yl, yr, value)` | Records an addition and returns its insertion-order update ID. Empty rectangles are allowed. | Amortized $O(1)$ |
| `add_query(xl, xr, yl, yr)` | Records a sum query and returns its insertion-order query ID. Empty rectangles are allowed. | Amortized $O(1)$ |
| `calculate()` | Returns all answers in query insertion order without mutating the object. | $O((N+Q)\log(N+Q))$ time and $O(N+Q)$ memory |

Here $N$ is the number of updates and $Q$ is the number of queries. Invalid
rectangles with a lower boundary greater than the corresponding upper boundary
trigger an assertion.

The implementation converts every rectangle addition into four weighted corner
events. A sweep over x and a Fenwick tree over compressed y-coordinates evaluate
the two-dimensional prefix sums used by inclusion-exclusion.

## Example

```cpp
#include "ds/range_query/offline_rectangle_add_rectangle_sum.hpp"

#include <cassert>

int main() {
    m1une::ds::OfflineRectangleAddRectangleSum<long long> offline;

    offline.add_rectangle(0, 3, 0, 2, 5);
    int query_id = offline.add_query(1, 4, 1, 3);

    const auto answers = offline.calculate();
    assert(answers[query_id] == 10);
}
```
