---
title: Min Monoid
documentation_of: ../../monoid/min.hpp
---

## Overview

A monoid representing the Minimum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Minimum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::max()`.

## Properties

* **Operation**: `std::min(a, b)`
* **Identity Element**: `Id`

## Requirements

`T` must support ordered comparison. A custom `Id` must be at least as large as
every valid value. Floating-point values must have a consistent ordering;
exclude NaNs.

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `Id` (the largest representable `T` by default). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the smaller value. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/min.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Min<int>;
    assert(M::op(3, 4) == 3);
}
```
