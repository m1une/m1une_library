---
title: GCD Monoid
documentation_of: ../../monoid/gcd.hpp
---

## Overview

A monoid representing the Greatest Common Divisor (GCD) operation. This is an idempotent monoid, meaning it can be safely used with a Sparse Table for range GCD queries using one GCD operation. The GCD operation itself takes $O(\log(V + 1))$ time for values of magnitude at most $V$.

## Template Parameters

* `T`: The underlying integer data type.

## Properties

* **Operation**: `std::gcd(a, b)`
* **Identity Element**: $0$ (Since $\gcd(x, 0) = x$)

## Interface and Complexity

```cpp
using value_type = T;
```

Let $V$ bound the absolute input values. Their absolute values must be representable by `T`, as required by `std::gcd`.

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns zero. | $O(1)$ |
| `static constexpr T op(const T& a, const T& b)` | Returns `std::gcd(a, b)`. | $O(\log(V + 1))$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/gcd.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Gcd<int>;
    assert(M::op(12, 18) == 6);
}
```
