---
title: Monoid Wrapper
documentation_of: ../../monoid/wrapper.hpp
---

## Overview

Defines a monoid from callables supplied as C++20 non-type template parameters.
Use it for a short custom operation without declaring a separate struct.

## Template Parameters

* `T`: The underlying data type of the monoid.
* `Op`: A callable object (function pointer or stateless lambda) that takes two arguments of type `T` and returns a value of type `T`.
* `Id`: A callable object (function pointer or stateless lambda) that takes no arguments and returns the identity element of type `T`.
* `Commutative`: Whether `Op` is commutative. Defaults to `false`.

## Interface and Complexity

```cpp
using value_type = T;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns `Id()`. | Cost of `Id()` |
| `static constexpr T op(const T& a, const T& b)` | Returns `Op(a, b)`. | Cost of `Op(a, b)` |

## Example

In C++20, you can pass lambdas directly in the template arguments. This allows you to define a monoid completely inline.

```cpp
#include "monoid/wrapper.hpp"

// Define a Monoid for XOR sum inline
using XorMonoid = m1une::monoid::Wrapper<int, [](int a, int b) { return a ^ b; }, []() { return 0; }, true>;

// Now `XorMonoid` can be passed to data structures like Segtree
// Segtree<XorMonoid> seg(n);
```

You can also define the lambdas separately if the operations are complex:

```cpp
constexpr auto custom_op = [](long long a, long long b) { return a + b; };
constexpr auto custom_id = []() { return 0LL; };
using CustomMonoid = m1une::monoid::Wrapper<long long, custom_op, custom_id>;
```
