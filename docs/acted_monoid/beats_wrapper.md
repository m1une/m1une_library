---
title: Beats Acted Monoid Wrapper
documentation_of: ../../acted_monoid/beats_wrapper.hpp
---

## Overview

`m1une::acted_monoid::BeatsWrapper` defines a Beats acted monoid from callables
supplied as C++20 non-type template arguments (NTTPs). It is useful when the
operations are short enough that declaring a named acted-monoid `struct` would
add ceremony during a contest.

The template arguments themselves must be valid constant template arguments.
The operations do not have to be callable in a constant expression:
`IsBeatsActedMonoid` checks their signatures and return types only. Named lambda
objects in the example are declared `constexpr` solely so their values can be
used as template arguments.

A Beats action differs from an ordinary acted-monoid action because an update
cannot necessarily be calculated from one aggregate. `can_apply(f, x)` tells
the data structure whether `mapping(f, x)` can update the whole node `x`
without inspecting its children. If it returns `false`, `SegtreeBeats`
descends, applies the update to smaller nodes, and rebuilds the aggregate.

Use `acted_monoid::Wrapper` with `LazySegtree` when every update is directly
applicable. Use `BeatsWrapper` with `SegtreeBeats` when applicability depends on
the aggregate.

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

## Required callables

| Parameter | Required behavior |
| --- | --- |
| `T` | Value aggregate type exposed as `value_type`. |
| `F` | Update type exposed as `operator_type`. |
| `Op` | `T(const T&, const T&)`; associative value operation. |
| `Id` | `T()`; identity of `Op`. |
| `OpComp` | `F(const F&, const F&)`; `OpComp(f, g)` represents applying `g` first and then `f`. |
| `OpId` | `F()`; identity of `OpComp`. |
| `Mapping` | `T(const F&, const T&)`; updates an aggregate when application is allowed. |
| `CanApply` | `bool(const F&, const T&)`; reports whether `Mapping` can update the aggregate directly. |

The functions must satisfy the monoid and action laws required by
`IsActedMonoid`. In addition, `CanApply` has the following contract:

* When it returns `true`, `Mapping(f, x)` must be the exact aggregate after
  applying `f` to every element represented by `x`.
* When it returns `false`, `Mapping(f, x)` is not called. The tree descends
  instead.
* Every valid update must become applicable at every real leaf.
* `OpId()` must always be applicable and must leave every value unchanged.

Returning `false` is always correct when descent is safe, but unnecessary
failures make operations slower. A useful predicate therefore recognizes as
many constant-time aggregate updates as the stored information permits.

## Optional callables

The last five template arguments expose hooks used by `SegtreeBeats` when they
are present.

| Parameter | Exposed method | Purpose |
| --- | --- | --- |
| `Make` | `make(value)` | Converts an input element into a leaf aggregate. |
| `MakeAt` | `make(value, index)` | Converts an input element using its zero-based index. |
| `MappingAt` | `mapping(f, x, ordinal)` | Applies an update using an ordinal relative to the update's origin. |
| `CanApplyAt` | `can_apply(f, x, ordinal)` | Index-aware applicability test. |
| `OpShift` | `op_shift(f, offset)` | Shifts a position-dependent update by `offset`. |

Pass the optional callables in this exact order. Omitted trailing arguments
default to `nullptr`, and their corresponding methods are not made available.
The ordinary `Mapping` and `CanApply` arguments remain required even when the
index-aware overloads are supplied.

When constructing `SegtreeBeats` from `std::vector<U>`, the tree prefers
`make(value)`, then `make(value, index)`, then conversion to `T`. Usually only
one of `Make` and `MakeAt` should be supplied.

## Interface and complexity

| Method | Description | Complexity |
| --- | --- | --- |
| `static T id()` | Calls `Id()`. | Cost of `Id` |
| `static T op(const T& lhs, const T& rhs)` | Calls `Op(lhs, rhs)`. | Cost of `Op` |
| `static F op_id()` | Calls `OpId()`. | Cost of `OpId` |
| `static F op_comp(const F& f, const F& g)` | Calls `OpComp(f, g)`. | Cost of `OpComp` |
| `static T mapping(const F& f, const T& x)` | Calls `Mapping(f, x)`. | Cost of `Mapping` |
| `static bool can_apply(const F& f, const T& x)` | Calls `CanApply(f, x)`. | Cost of `CanApply` |
| `static T make(const U& value)` | Calls `Make(value)`, when supplied. | Cost of `Make` |
| `static T make(const U& value, int index)` | Calls `MakeAt(value, index)`, when supplied. | Cost of `MakeAt` |
| `static T mapping(const F& f, const T& x, long long ordinal)` | Calls `MappingAt`, when supplied. | Cost of `MappingAt` |
| `static bool can_apply(const F& f, const T& x, long long ordinal)` | Calls `CanApplyAt`, when supplied. | Cost of `CanApplyAt` |
| `static F op_shift(const F& f, long long offset)` | Calls `OpShift`, when supplied. | Cost of `OpShift` |

The wrapper itself adds no asymptotic overhead. The complexity of a
`SegtreeBeats` operation also depends on how often `CanApply` fails; see the
`SegtreeBeats` documentation for that bound.

## Example: range chmin and range sum

For a range-`chmin` update, a node stores its largest value, second-largest
value, number of occurrences of the largest value, and sum. Capping by `f` is
directly applicable in either of these cases:

* `f` is at least the maximum, so nothing changes.
* `f` is strictly greater than the second maximum, so only the known maximum
  elements change.

If `f` is at most the second maximum, the aggregate does not contain enough
information to update the sum, so `can_apply` returns `false` and the tree
descends.

```cpp
#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

#include "acted_monoid/beats_wrapper.hpp"
#include "ds/segtree/segtree_beats.hpp"

struct Node {
    long long max_value;
    long long second_max;
    long long sum;
    int max_count;
    int length;
};

constexpr long long NEG_INF =
    std::numeric_limits<long long>::lowest() / 4;
constexpr long long INF =
    std::numeric_limits<long long>::max() / 4;

constexpr auto op = [](const Node& a, const Node& b) {
    if (a.length == 0) return b;
    if (b.length == 0) return a;
    Node result;
    result.sum = a.sum + b.sum;
    result.length = a.length + b.length;
    if (a.max_value == b.max_value) {
        result.max_value = a.max_value;
        result.second_max = std::max(a.second_max, b.second_max);
        result.max_count = a.max_count + b.max_count;
    } else if (a.max_value > b.max_value) {
        result.max_value = a.max_value;
        result.second_max = std::max(a.second_max, b.max_value);
        result.max_count = a.max_count;
    } else {
        result.max_value = b.max_value;
        result.second_max = std::max(a.max_value, b.second_max);
        result.max_count = b.max_count;
    }
    return result;
};

constexpr auto id = [] { return Node{NEG_INF, NEG_INF, 0, 0, 0}; };
constexpr auto compose = [](long long f, long long g) {
    return std::min(f, g);
};
constexpr auto op_id = [] { return INF; };
constexpr auto can_apply = [](long long f, const Node& x) {
    return x.length == 0 || x.length == 1 || x.max_value <= f ||
        x.second_max < f;
};
constexpr auto mapping = [](long long f, Node x) {
    assert(can_apply(f, x));
    if (x.length == 0 || x.max_value <= f) return x;
    x.sum -= (x.max_value - f) * x.max_count;
    x.max_value = f;
    return x;
};
constexpr auto make = [](long long value) {
    return Node{value, NEG_INF, value, 1, 1};
};

using RangeChminRangeSum = m1une::acted_monoid::BeatsWrapper<
    Node,
    long long,
    op,
    id,
    compose,
    op_id,
    mapping,
    can_apply,
    make
>;

int main() {
    std::vector<long long> values{8, 3, 6, 7};
    m1une::ds::SegtreeBeats<RangeChminRangeSum> seg(values);

    seg.apply(0, 4, 5LL);
    std::cout << seg.prod(0, 4).sum << '\n';  // 18
    std::cout << seg.all_prod().max_value << '\n';  // 5
}
```

The example assumes all input values, caps, sums, and intermediate differences
fit in `long long`, and that real values stay strictly above `NEG_INF`.
