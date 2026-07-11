---
title: Static Rectangle Sum
documentation_of: ../../../ds/range_query/static_rectangle_sum.hpp
---

## Overview

`StaticRectangleSum<X, Y, Sum>` stores an immutable set of weighted points and
returns the total weight inside axis-aligned half-open rectangles:

$$
[x_l,x_r)\times[y_l,y_r).
$$

Points are sorted by their x-coordinate. Y-coordinates are compressed and
queried with a weighted wavelet matrix. Multiple input points may have identical
coordinates; every weight is included independently.

## Requirements

`X` and `Y` must provide a strict weak ordering through `<`. `Sum{}` must be the
additive identity, and `Sum` must support addition and subtraction. All weight
sums must fit in `Sum`.

## Interface

```cpp
template <class X, class Y = X, class Sum = long long>
class StaticRectangleSum {
public:
    using x_type = X;
    using y_type = Y;
    using sum_type = Sum;
    using weighted_point_type = std::tuple<X, Y, Sum>;

    StaticRectangleSum();

    explicit StaticRectangleSum(
        const std::vector<weighted_point_type>& points
    );

    StaticRectangleSum(
        const std::vector<X>& x_coordinates,
        const std::vector<Y>& y_coordinates,
        const std::vector<Sum>& weights
    );

    void build(std::vector<weighted_point_type> points);

    void build(
        const std::vector<X>& x_coordinates,
        const std::vector<Y>& y_coordinates,
        const std::vector<Sum>& weights
    );

    int size() const;
    bool empty() const;

    Sum sum(
        const X& left,
        const X& right,
        const Y& lower,
        const Y& upper
    ) const;
};
```

## Operations

| Method | Description | Complexity |
| --- | --- | --- |
| `StaticRectangleSum()` | Constructs an empty structure. | $O(1)$ |
| `explicit StaticRectangleSum(const std::vector<weighted_point_type>& points)` | Builds from `(x, y, weight)` tuples. | $O(N\log N + NB)$ |
| `StaticRectangleSum(const std::vector<X>& xs, const std::vector<Y>& ys, const std::vector<Sum>& weights)` | Builds from parallel coordinate and weight vectors. | $O(N\log N + NB)$ |
| `void build(std::vector<weighted_point_type> points)` | Replaces the stored points. | $O(N\log N + NB)$ |
| `void build(const std::vector<X>& xs, const std::vector<Y>& ys, const std::vector<Sum>& weights)` | Replaces the stored points from parallel vectors. | $O(N\log N + NB)$ |
| `int size() const` | Returns the number of input points, including duplicates. | $O(1)$ |
| `bool empty() const` | Returns whether no points are stored. | $O(1)$ |
| `Sum sum(const X& left, const X& right, const Y& lower, const Y& upper) const` | Returns the weight sum in `[left,right) x [lower,upper)`. | $O(\log N+B)$ |

Here `B = 32`, the bit width of the compressed y-rank type. Construction uses
$O(NB)$ memory. Calls to `sum` do not mutate the structure. Empty rectangles
and rectangles outside all stored coordinates return `Sum{}`.

## Example

```cpp
#include "ds/range_query/static_rectangle_sum.hpp"

#include <cassert>
#include <tuple>
#include <vector>

int main() {
    using Query = m1une::ds::StaticRectangleSum<int, int, long long>;
    std::vector<Query::weighted_point_type> points;
    points.emplace_back(1, 2, 5);
    points.emplace_back(3, 4, 7);
    points.emplace_back(1, 2, 11);

    Query query(points);
    assert(query.sum(1, 2, 2, 3) == 16);
    assert(query.sum(0, 4, 0, 5) == 23);
}
```
