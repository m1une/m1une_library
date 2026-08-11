---
title: Persistent Segment Tree Beats
documentation_of: ../../../ds/segtree/persistent_segtree_beats.hpp
---

## Overview

`m1une::ds::PersistentSegtreeBeats<ActedMonoid>` is a persistent version of the
generic Segment Tree Beats. A range action is applied to an aggregate when
`can_apply(f, x)` succeeds; otherwise the operation descends until it reaches
segments where the action can be evaluated directly. Every assignment, range
action, and range copy returns a new version, leaving all input versions
unchanged.

Versions in the same family share a reference-counted node pool. Destroyed or
explicitly released versions return unreferenced nodes to the pool, and later
updates reuse those slots. Read-only methods never push into or otherwise
mutate the tree. When a pending action cannot directly produce a queried
subaggregate, a query evaluates the necessary descendants virtually.

Use `PersistentLazySegtree<ActedMonoid>` when every valid action always applies
to an aggregate. Use nonpersistent `SegtreeBeats<ActedMonoid>` when old versions
are unnecessary.

## Beats acted monoid requirements

`ActedMonoid` must satisfy
`m1une::beats_acted_monoid::IsBeatsActedMonoid` and provide:

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

`op_comp(f, g)` means applying `g` first and then `f`. The applicability
contract is:

* If `can_apply(f, x)` is true, `mapping(f, x)` must return the complete updated
  aggregate without inspecting children.
* If it is false, `mapping` is not called at that node. The tree materializes
  older pending actions as necessary, applies `f` recursively, and rebuilds the
  aggregate with `op`.
* Every valid operator must be directly applicable at every real leaf.
* `op_id()` must always be applicable and must map every value to itself.

The following index-aware overloads are optional and detected automatically:

```cpp
static T mapping(const F& f, const T& x, long long ordinal);
static bool can_apply(const F& f, const T& x, long long ordinal);
static F op_shift(const F& f, long long offset);
```

An operator given to `apply(l, r, f)` is relative to `l`. A covered segment
starting at `p` receives `op_shift(f, p - l)`. Construction from
`std::vector<U>` uses `ActedMonoid::make(value)`, then
`ActedMonoid::make(value, index)`, then conversion to `T`, choosing the first
available operation.

## Public interface

All indices are zero-based and ranges are half-open. `T` is `value_type` and
`F` is `operator_type`.

| Method | Description | Complexity |
| --- | --- | --- |
| `PersistentSegtreeBeats()` | Constructs an empty version family. | $O(1)$ |
| `explicit PersistentSegtreeBeats(int n)` | Constructs `n` identity values. | $O(N)$ |
| `explicit PersistentSegtreeBeats(const std::vector<T>& v)` | Copies and builds from acted-monoid values. | $O(N)$ |
| `explicit PersistentSegtreeBeats(std::vector<T>&& v)` | Moves and builds from acted-monoid values. | $O(N)$ |
| `template<class U> explicit PersistentSegtreeBeats(const std::vector<U>& v)` | Converts elements with `make` or conversion and builds. | $O(N)$ |
| `PersistentSegtreeBeats(const PersistentSegtreeBeats& other)` | Copies a version handle. | $O(1)$ |
| `PersistentSegtreeBeats(PersistentSegtreeBeats&& other) noexcept` | Moves a version handle. | $O(1)$ |
| `PersistentSegtreeBeats& operator=(const PersistentSegtreeBeats& other)` | Replaces this handle with a shared copy of `other`. | $O(R)$ |
| `PersistentSegtreeBeats& operator=(PersistentSegtreeBeats&& other) noexcept` | Replaces this handle by moving `other`. | $O(R)$ |
| `~PersistentSegtreeBeats()` | Releases this handle's root. | $O(R)$ |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the handle has no elements. | $O(1)$ |
| `void release()` | Releases this version early and makes the handle empty. | $O(R)$ |
| `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `PersistentSegtreeBeats set(int p, T x) const` | Returns a version with element `p` assigned to `x`. | $O(\log N+D)$ |
| `T get(int p) const` | Returns element `p`. | $O(\log N+D)$ |
| `T operator[](int p) const` | Returns element `p`. | $O(\log N+D)$ |
| `T prod(int l, int r) const` | Returns the monoid product of `[l, r)`. | $O(\log N+D)$ |
| `T all_prod() const` | Returns the whole-array product. | $O(1)$ |
| `PersistentSegtreeBeats apply(int p, const F& f) const` | Returns a version with `f` applied at `p`. | $O(\log N+D)$ |
| `PersistentSegtreeBeats apply(int l, int r, const F& f) const` | Returns a version with `f` applied to `[l, r)`. | $O(\log N+D)$ |
| `PersistentSegtreeBeats copy_range_from(const PersistentSegtreeBeats& source, int l, int r) const` | Returns a version using `source` on `[l, r)` and this version elsewhere. | $O(\log N+D)$ |
| `std::vector<T> to_vector() const` | Materializes every element. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Materializes `[l, r)`. | $O(\log N+r-l)$ |
| `template<class Predicate> int max_right(int l, Predicate g) const` | Finds the largest `r` for which `g(prod(l, r))` is true. | $O(\log N+D)$ |
| `template<class Predicate> int min_left(int r, Predicate g) const` | Finds the smallest `l` for which `g(prod(l, r))` is true. | $O(\log N+D)$ |

Here, $D$ is the number of extra nodes visited because a new or pending action
cannot be evaluated directly. An update allocates $O(\log N+D)$ new nodes.
There is no universal logarithmic Beats bound: the acted monoid needs its own
potential or transition-count argument. Persistence also permits branching
from the same old potential state, so bounds amortized across one linear update
sequence do not automatically amortize across every branch.

$R$ in the handle-management rows is the number of nodes whose last reference
is removed. Empty products return `id()`. Boundary-search predicates must
accept `id()`.

`copy_range_from` requires equal sizes and a shared node pool, which means both
versions must descend from the same initial tree. Neither version is mutated.

## Example

This compact example uses an always-applicable action; a fallible Beats action
uses the same version workflow.

```cpp
#include "ds/segtree/persistent_segtree_beats.hpp"
#include "acted_monoid/range_add_range_sum.hpp"
#include <iostream>
#include <vector>

struct RangeAddRangeSumBeats
    : m1une::acted_monoid::RangeAddRangeSum<long long> {
    static bool can_apply(
        const operator_type&,
        const value_type&
    ) {
        return true;
    }
};

int main() {
    using AM = RangeAddRangeSumBeats;
    using Seg = m1une::ds::PersistentSegtreeBeats<AM>;

    Seg initial(std::vector<long long>{1, 2, 3, 4});
    Seg added = initial.apply(1, 4, 10);
    Seg changed = added.set(1, AM::make(100));
    Seg mixed = initial.copy_range_from(changed, 1, 3);

    std::cout << initial.prod(0, 4).sum << "\n";  // 10
    std::cout << added.prod(0, 4).sum << "\n";    // 40
    std::cout << changed.prod(0, 4).sum << "\n";  // 128
    std::cout << mixed.prod(0, 4).sum << "\n";    // 118
}
```
