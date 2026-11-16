---
title: Multiply Monoid
documentation_of: ../../monoid/mul.hpp
---

## Overview

A monoid representing the multiplication operation. Useful for Range Product queries. Commonly used alongside modular arithmetic types (`Modint`) to prevent overflow.

## Template Parameters

* `T`: The underlying numeric data type.

## Properties

* **Operation**: Multiplication ($a \times b$)
* **Identity Element**: $1$

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns one. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns `a * b`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/mul.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Mul<long long>;
    assert(M::op(3, 4) == 12);
}
```
