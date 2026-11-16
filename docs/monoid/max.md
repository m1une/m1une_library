---
title: Max Monoid
documentation_of: ../../monoid/max.hpp
---

## Overview

A monoid representing the Maximum operation. It is an idempotent monoid, meaning it is compatible with Sparse Tables for $O(1)$ Range Maximum Queries (RMQ).

## Template Parameters

* `T`: The underlying data type.
* `Id`: The identity element. Defaults to `std::numeric_limits<T>::lowest()`.

## Properties

* **Operation**: `std::max(a, b)`
* **Identity Element**: `Id`

## Requirements

`T` must support ordered comparison. A custom `Id` must be at most as small as
every valid value. Floating-point values must have a consistent ordering;
exclude NaNs.

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `Id` (the lowest representable `T` by default). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the larger value. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/max.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Max<int>;
    assert(M::op(3, 4) == 4);
}
```
