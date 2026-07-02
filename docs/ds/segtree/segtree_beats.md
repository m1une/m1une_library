---
title: Generic Segment Tree Beats
documentation_of: ../../../ds/segtree/segtree_beats.hpp
---

## Overview

`m1une::ds::SegtreeBeats<ActedMonoid>` is a generic lazy segment tree for
actions that cannot always be applied to an aggregated node. When
`can_apply(f, x)` is false, the tree pushes any older lazy operator, descends to
the children, applies `f` there, and rebuilds the node.

This is the library's generic meaning of Segment Tree Beats. It is not tied to
`chmin` or `chmax`. For the ready-made numeric structure supporting range
`chmin`, range `chmax`, range addition, and sum/min/max queries, use
`ChminChmaxAddSegtree<T>`.

Use `LazySegtree<ActedMonoid>` when every valid action always maps an aggregate
directly. Its simpler contract gives the usual $O(\log N)$ update bound.

## Beats acted monoid

`ActedMonoid` must satisfy `m1une::acted_monoid::IsBeatsActedMonoid` and provide:

```cpp
using value_type = T;
using operator_type = F;

static T id();
static T op(const T& lhs, const T& rhs);

static F op_id();
static F op_comp(const F& f, const F& g);

static T mapping(const F& f, const T& x);
static bool can_apply(const F& f, const T& x);
```

`op_comp(f, g)` represents applying `g` first and then `f`.

The exact applicability contract is:

* If `can_apply(f, x)` is true, `mapping(f, x)` must return the correct updated
  aggregate without inspecting children.
* If it is false, `mapping` is not called and `f` is not composed into that
  node's lazy tag.
* A failed internal application pushes the node's existing lazy tag first,
  recursively applies `f` to both children, and rebuilds the aggregate with
  `op`.
* Pushing a stored operator uses the same fallible procedure. It may itself
  descend multiple levels before propagation finishes.
* Every valid operator must be applicable at every real leaf. Reaching a real
  leaf for which `can_apply` is false triggers an assertion.
* `op_id()` must always be applicable and `mapping(op_id(), x)` must equal `x`.

Padded leaves are excluded by the data structure and do not impose an
application-specific `can_apply` requirement.

## Optional index-aware operations

The following overloads are detected automatically:

```cpp
static T mapping(const F& f, const T& x, long long ordinal);
static bool can_apply(const F& f, const T& x, long long ordinal);
static F op_shift(const F& f, long long offset);
```

An operator passed to `apply(l, r, f)` is relative to index `l`. A covered node
starting at `p` receives `op_shift(f, p - l)`. On descent, the left child keeps
offset zero relative to its parent and the right child receives the operator
shifted by the left child's interval length. The index-aware mapping and
applicability overloads receive the ordinal relative to the already shifted
operator; the current implementation calls them with zero at a node.

Construction from `std::vector<U>` uses `ActedMonoid::make(value)` when
available, then `ActedMonoid::make(value, index)`, then conversion to
`value_type`.

`acted_monoid/beats_wrapper.hpp` provides `BeatsWrapper` for assembling the
required functions from `constexpr` lambdas or function objects. It can also
forward optional `make`, index-aware mapping/applicability, and shifting
functions.

## Public interface

All indices are zero-based and all ranges are half-open.

| Method | Description | Complexity |
| --- | --- | --- |
| `SegtreeBeats()` | Constructs an empty tree. | $O(1)$ |
| `SegtreeBeats(int n)` | Constructs `n` identity values. | $O(N)$ |
| `SegtreeBeats(const std::vector<T>& v)` | Copies and builds from acted-monoid values. | $O(N)$ |
| `SegtreeBeats(std::vector<T>&& v)` | Moves and builds from acted-monoid values. | $O(N)$ |
| `SegtreeBeats(const std::vector<U>& v)` | Converts with `make` or conversion and builds. | $O(N)$ |
| `int size() const` | Returns the number of real elements. | $O(1)$ |
| `bool empty() const` | Returns whether there are no elements. | $O(1)$ |
| `void set(int p, T x)` | Assigns element `p`. | $O(\log N + D)$ |
| `T get(int p)` | Returns element `p`. | $O(\log N + D)$ |
| `T operator[](int p)` | Returns element `p`. | $O(\log N + D)$ |
| `T prod(int l, int r)` | Returns the monoid product of `[l, r)`. | $O(\log N + D)$ |
| `T all_prod() const` | Returns the whole-array product. | $O(1)$ |
| `void apply(int p, F f)` | Applies `f` to element `p`. | $O(\log N + D)$ |
| `void apply(int l, int r, F f)` | Applies `f` to `[l, r)`. | $O(\log N + D)$ |
| `std::vector<T> to_vector()` | Materializes every element. | $O(N + D)$ |
| `std::vector<T> to_vector(int l, int r)` | Materializes `[l, r)`. | $O((r-l)+\log N+D)$ |
| `int max_right(int l, Predicate g)` | Finds the largest `r` for which `g(prod(l, r))` is true. | $O(\log N + D)$ |
| `int min_left(int r, Predicate g)` | Finds the smallest `l` for which `g(prod(l, r))` is true. | $O(\log N + D)$ |

Here, $D$ is the number of additional nodes visited because direct application
of a new or stored operator fails. Empty products return `id()`. Boundary-search
predicates must accept `id()`.

A generic update is therefore $O(\log N + D)$, not automatically amortized
$O(\log N)$. A stronger bound must be proved for the particular acted monoid,
usually with a potential argument or a bound on exceptional state transitions.
Because queries may push stored operators, their $D$ can also be nonzero.

## Non-chmin/chmax example

Consider reactors with a pressure threshold. A value stores the minimum
remaining pressure before any active reactor vents, the total number of vents,
and the number and length of terminal reactors. An update stores both the added
pressure and one operation count.

The update is directly applicable when all reactors are terminal, no active
reactor reaches its threshold, or the node is a leaf. Otherwise
`can_apply(update, node)` returns false. The generic tree descends only through
segments containing exceptional transitions; a leaf that vents can halve its
threshold and reset its pressure. This is a Beats action even though it uses no
`chmin` or `chmax` operation.
