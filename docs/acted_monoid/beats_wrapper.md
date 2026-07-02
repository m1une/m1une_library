---
title: Beats Acted Monoid Wrapper
documentation_of: ../../acted_monoid/beats_wrapper.hpp
---

## Overview

`m1une::acted_monoid::BeatsWrapper` builds a Beats acted monoid from functions,
function objects, or captureless `constexpr` lambdas supplied as non-type
template arguments.

```cpp
template <
    class T, class F,
    auto Op, auto Id,
    auto OpComp, auto OpId,
    auto Mapping, auto CanApply,
    auto Make = nullptr,
    auto MakeAt = nullptr,
    auto MappingAt = nullptr,
    auto CanApplyAt = nullptr,
    auto OpShift = nullptr
>
struct BeatsWrapper;
```

The first eight function arguments define the required value monoid, operator
monoid, mapping, and applicability predicate. Optional arguments forward
`make(value)`, `make(value, index)`, index-aware `mapping`, index-aware
`can_apply`, and `op_shift` in that order.

All wrapper methods are constant-time apart from the user-supplied functions.
`op_comp(f, g)` must represent applying `g` before `f`, and `CanApply` must obey
the failure contract documented for `IsBeatsActedMonoid`.
