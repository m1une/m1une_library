---
title: K-d Tree
documentation_of: ../../../ds/range_query/kd_tree.hpp
---

## Overview

`KdTree<T, K>` stores a static set of `K`-dimensional points. It supports
orthogonal half-open range reporting and counting, nearest-neighbor queries,
and k-nearest-neighbor queries while preserving every point's original input
index.

Construction recursively selects the widest coordinate axis, places its median
at the current node, and stores a bounding box for each subtree. Duplicate
points are kept as separate entries. The structure is effective for small,
fixed dimensions; like other k-d trees, its pruning becomes less effective as
the dimension grows.

## Requirements

`K` must be positive. `T` must be an arithmetic type other than `bool`.
Floating-point coordinates and queries must be finite.

For integral `T`, squared distances use signed 128-bit arithmetic. For
floating-point `T`, they use `long double`. Every squared distance and
intermediate sum must fit in `distance_type`.

## Public Interface

```cpp
template <class T, std::size_t K>
class KdTree {
public:
    using coordinate_type = T;
    using point_type = std::array<T, K>;
    using distance_type = /* __int128_t or long double */;
    static constexpr std::size_t dimension = K;

    struct Neighbor {
        int index;
        distance_type distance_squared;

        friend bool operator==(const Neighbor&, const Neighbor&) = default;
    };
};
```

All boxes are the Cartesian product of half-open ranges
`[lower[axis], upper[axis])`. Each lower bound must not exceed its upper bound.

| Method | Description | Complexity |
| --- | --- | --- |
| `bool operator==(const Neighbor& first, const Neighbor& second)` | Compares both neighbor fields. | $O(1)$ |
| `KdTree()` | Constructs an empty tree. | $O(1)$ |
| `explicit KdTree(const std::vector<point_type>& points)` | Copies the points and builds the tree. | $O(KN\log N)$ average time, $O(KN)$ memory |
| `void build(const std::vector<point_type>& points)` | Replaces all stored points and rebuilds the tree. | $O(KN\log N)$ average time, $O(KN)$ memory |
| `int size() const` | Returns the number of stored points, including duplicates. | $O(1)$ |
| `bool empty() const` | Returns whether no points are stored. | $O(1)$ |
| `const point_type& get(int index) const` | Returns the point at its original input index. | $O(1)$ |
| `const point_type& operator[](int index) const` | Equivalent to `get(index)`. | $O(1)$ |
| `std::vector<int> range_search(const point_type& lower, const point_type& upper) const` | Returns the original indices inside the half-open box. | Typically $O(KN^{1-1/K}+A)$; $O(KN)$ worst case |
| `int count(const point_type& lower, const point_type& upper) const` | Counts points inside the half-open box. Fully covered subtrees are counted at once. | Typically $O(KN^{1-1/K})$; $O(KN)$ worst case |
| `std::optional<Neighbor> nearest(const point_type& query) const` | Returns the nearest point, or `nullopt` for an empty tree. | Typically $O(K\log N)$; $O(KN)$ worst case |
| `std::vector<Neighbor> k_nearest(const point_type& query, int k) const` | Returns the `k` nearest points for `0 <= k <= size()`. | $O(1)$ for `k = 0`; otherwise typically $O((K+\log k)(\log N+k))$ and $O(N(K+\log k))$ worst case |

Here, `A` is the number of reported points. Typical query bounds assume a
low-dimensional, reasonably distributed point set. Adversarial layouts can
force a query to visit every node.

`range_search` does not sort its result. `nearest` breaks equal-distance ties by
the smaller original index. `k_nearest` returns neighbors in ascending
`(distance_squared, index)` order. Query methods do not mutate the tree.

## Example

```cpp
#include "ds/range_query/kd_tree.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

int main() {
    using Tree = m1une::ds::KdTree<long long, 2>;
    using Point = Tree::point_type;

    std::vector<Point> points;
    Point first = {0, 0};
    Point second = {3, 1};
    Point third = {2, 4};
    points.push_back(first);
    points.push_back(second);
    points.push_back(third);

    Tree tree(points);

    Point lower = {0, 0};
    Point upper = {3, 3};
    std::vector<int> found = tree.range_search(lower, upper);
    std::sort(found.begin(), found.end());
    assert(found.size() == 1 && found[0] == 0);

    Point query = {2, 0};
    auto nearest = tree.nearest(query);
    assert(nearest.has_value());
    assert(nearest->index == 1);
    assert(nearest->distance_squared == 2);
}
```
