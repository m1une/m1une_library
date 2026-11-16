---
title: Bitwise AND Monoid
documentation_of: ../../monoid/and.hpp
---

## Overview

A monoid representing the bitwise AND operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise AND ($a \ \& \ b$)
* **Identity Element**: `~T(0)` (All bits set to 1)

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `~T(0)` (all bits set). | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the bitwise AND. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/and.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::And<unsigned int>;
    assert(M::op(6, 3) == 2);
}
```
