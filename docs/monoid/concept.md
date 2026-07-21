---
title: Monoid Concept
documentation_of: ../../monoid/concept.hpp
---

## Overview

`m1une::monoid::IsMonoid` is the C++20 concept used by generic data structures
such as `Segtree`. It checks that a type exposes the interface needed by the
library: a value type, an identity element, and a binary operation.

The concept checks the shape of the interface. The mathematical laws are still
the user's responsibility:

* `op` should be associative.
* `id()` should be a left and right identity for `op`.

## Concept Requirements

To satisfy `m1une::monoid::IsMonoid`, a type `M` must implement:

* `using value_type = T;`
  The type stored by the monoid.

* `static T id();`
  Returns the identity element.

* `static T op(const T& a, const T& b);`
  Combines two values.

Built-in monoids also expose `static constexpr bool commutative`. Generic data
structures may use it to select a faster representation. This member is
deliberately optional and is not part of `IsMonoid`, so a contest-local monoid
may omit it. An omitted flag is treated conservatively by data structures that
inspect it.

## Group

`m1une::monoid::IsGroup` extends `IsMonoid` with an inverse:

* `static T inv(const T& x);`
  Returns the inverse of `x` with respect to `op`.

The concept checks only that `inv` exists. The type must satisfy the group
laws, but `op` does not need to be commutative.

`m1une::monoid::IsCommutativeGroup` extends `IsGroup`. It has the same
compile-time interface check because C++ concepts cannot prove commutativity;
types used through it must additionally guarantee that `op(a, b) == op(b, a)`.

## Example

```cpp
#include "monoid/concept.hpp"
#include <algorithm>

struct MinMonoid {
    using value_type = int;
    static constexpr int id() { return 1e9; }
    static constexpr int op(const int& a, const int& b) { return std::min(a, b); }
};

static_assert(m1une::monoid::IsMonoid<MinMonoid>);
```

## Complexity

These concepts are compile-time interface checks and have no runtime cost.
