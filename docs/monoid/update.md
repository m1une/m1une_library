---
title: Update Monoid
documentation_of: ../../monoid/update.hpp
---

## Overview

A monoid for range updates/assignments. It uses `std::optional<T>` to safely represent whether an assignment operation exists or not (the identity element is `std::nullopt`).

When two operations are composed, the newer operation (on the left, when applied) completely overwrites the older operation (on the right), unless the newer operation is empty.

## Template Parameters

* `T`: The underlying data type being assigned.

## Interface and Complexity

```cpp
using value_type = std::optional<T>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns `std::nullopt`. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Returns `a` if present, otherwise `b`; the left assignment wins. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "monoid/update.hpp"
#include <cassert>

int main() {
    using M = m1une::monoid::Update<int>;
    assert(M::op(7, 3).value() == 7);
    assert(M::op(M::id(), 3).value() == 3);
}
```
