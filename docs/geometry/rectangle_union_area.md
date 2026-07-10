---
title: Area of Union of Rectangles
documentation_of: ../../geometry/rectangle_union_area.hpp
---

## Overview

`rectangle_union_area` returns the area covered by at least one axis-aligned
rectangle. Overlaps are counted once. Coordinates may be negative, rectangles
may touch, and zero-width or zero-height rectangles contribute no area.

The implementation sweeps rectangle edges from left to right. A segment tree
over compressed y-coordinates maintains the total y-length currently covered.
Between consecutive x-events, that length is multiplied by the x-distance.

## Interface

```cpp
template <Coordinate T>
struct AxisAlignedRectangle {
    T left;
    T bottom;
    T right;
    T top;
};

template <Coordinate T>
wide_type<T> rectangle_union_area(
    const std::vector<AxisAlignedRectangle<T>>& rectangles
);
```

| Member / Function | Complexity | Description |
| --- | --- | --- |
| `AxisAlignedRectangle<T>()` | $O(1)$ | Constructs a zero-area rectangle at the origin. |
| `AxisAlignedRectangle<T>(left, bottom, right, top)` | $O(1)$ | Constructs `[left, right]` by `[bottom, top]`. |
| `rectangle_union_area(rectangles)` | $O(N\log N)$ time and $O(N)$ memory | Returns the union area without modifying the input. |

The constructor coordinates must satisfy `left <= right` and `bottom <= top`.
This is checked when the area is calculated. Boundary inclusion does not affect
area; the implementation treats rectangles as half-open during the sweep.

For integral `T`, `wide_type<T>` is signed `__int128_t`, preventing overflow
in coordinate subtraction and multiplication. For floating-point `T`, the
return type is `long double`.

## Example

```cpp
#include "geometry/rectangle_union_area.hpp"

#include <iostream>
#include <vector>

int main() {
    using Rectangle = m1une::geometry::AxisAlignedRectangle<long long>;
    std::vector<Rectangle> rectangles;
    rectangles.emplace_back(0, 0, 4, 3);
    rectangles.emplace_back(2, 1, 6, 5);

    long long area = static_cast<long long>(
        m1une::geometry::rectangle_union_area(rectangles)
    );
    std::cout << area << "\n"; // 24
}
```
