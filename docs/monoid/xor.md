---
title: Bitwise XOR Monoid
documentation_of: ../../monoid/xor.hpp
---

## Overview

A monoid representing the bitwise XOR operation.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: Bitwise XOR ($a \ \text{\textasciicircum} \ b$)
* **Identity Element**: $0$

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns zero. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns the bitwise XOR. | $O(1)$ |
| `static constexpr T inv(const T& x)` | Returns the group inverse of `x`. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/xor.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Xor<unsigned int>;
    assert(M::op(6, 3) == 5);
    assert(M::inv(6) == 6);
}
```
