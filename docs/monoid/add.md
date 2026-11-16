---
title: Add Monoid
documentation_of: ../../monoid/add.hpp
---

## Overview

A monoid representing the addition operation. It is commonly used with Segment Trees or Lazy Segment Trees for Range Sum Queries.

## Template Parameters

* `T`: The underlying numeric data type (e.g., `long long`, `int`, or `Modint`).

## Properties

* **Operation**: Addition ($a + b$)
* **Identity Element**: $0$

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns zero. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns `a + b`. | $O(1)$ |
| `static constexpr T inv(const T& x)` | Returns the group inverse of `x`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/add.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Add<long long>;
    assert(M::op(3, 4) == 7);
    assert(M::inv(3) == -3);
}
```
