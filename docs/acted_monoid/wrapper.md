---
title: Acted Monoid Wrapper
documentation_of: ../../acted_monoid/wrapper.hpp
---

## Overview

`Wrapper` provides a convenient way to define an Acted Monoid inline without writing a separate `struct`. This is particularly useful during contests when you need to combine custom mapping logic quickly.

It uses C++20 non-type template parameters (NTTPs), allowing functions,
structural function objects, and captureless lambda values to be passed as
template arguments. The template arguments must be valid constant template
arguments, but `IsActedMonoid` does not require the operations themselves to be
callable in a constant expression.

## Template Parameters

- `typename T`: The type of the value element (`value_type`).
- `typename E`: The type of the operator element (`operator_type`).
- `auto Op`: A function or lambda for the value monoid operation (`T op(T, T)`).
- `auto Id`: A function or lambda returning the value identity (`T id()`).
- `auto OpComp`: A function or lambda for operator composition (`E op_comp(E, E)`).
- `auto OpId`: A function or lambda returning the operator identity (`E op_id()`).
- `auto Mapping`: A function or lambda for mapping the operator onto the value (`T mapping(E, T)`).
- `bool Commutative`: Whether the value operation `Op` is commutative. Defaults
  to `false`.
- `bool OperatorCommutative`: Whether the operator operation `OpComp` is
  commutative. Defaults to `false`.

## Interface and Complexity

```cpp
using value_type = T;
using operator_type = E;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr T id()` | Returns the empty value-monoid identity. | Cost of `Id()` |
| `static constexpr T op(const T& a, const T& b)` | Combines the two aggregates in left-to-right order. | Cost of `Op(a, b)` |
| `static constexpr E op_id()` | Returns the identity update. | Cost of `OpId()` |
| `static constexpr E op_comp(const E& f, const E& g)` | Composes updates: apply `g` first, then `f`. | Cost of `OpComp(f, g)` |
| `static constexpr T mapping(const E& f, const T& x)` | Returns the aggregate after applying `f`; does not modify `x`. | Cost of `Mapping(f, x)` |

## Example

```cpp
#include "acted_monoid/wrapper.hpp"
#include <algorithm>
#include <limits>

// Definition of Range Add Range Min using Wrapper
constexpr long long INF = std::numeric_limits<long long>::max();
using RangeAddRangeMin = m1une::acted_monoid::Wrapper<
    long long,
    long long,
    [](long long a, long long b) { return std::min(a, b); },
    []() { return INF; },
    [](long long f, long long g) { return f + g; },
    []() { return 0LL; },
    [](long long f, long long x) { return x == INF ? INF : x + f; },
    true,
    true
>;
```
