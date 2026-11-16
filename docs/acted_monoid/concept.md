---
title: Acted Monoid Concept
documentation_of: ../../acted_monoid/concept.hpp
---

## Overview

`m1une::acted_monoid::IsActedMonoid` is the C++20 concept used by lazy
propagation data structures such as `LazySegtree`.

An acted monoid has three parts:

1. A value monoid, which combines segment values for queries.
2. An operator monoid, which combines lazy update operations.
3. A mapping function, which applies one operator to one value.

For example, in range-add range-sum:

* the value stores `(sum, size)`,
* the lazy operator stores the amount to add,
* `mapping(add, value)` increases the sum by `add * size`.

## Requirements

The concept requires the type to implement these members:

* `using value_type`
  The type stored for each segment.

* `using operator_type`
  The type stored for each lazy operation.

* `static value_type id()`
  Returns the identity element of the value monoid.

* `static value_type op(const value_type& a, const value_type& b)`
  Combines two segment values.

* `static operator_type op_id()`
  Returns the identity operation.

* `static operator_type op_comp(const operator_type& f, const operator_type& g)`
  Composes two operators. The order is `f(g(x))`: apply `g` first, then `f`.

* `static value_type mapping(const operator_type& f, const value_type& x)`
  Applies operator `f` to value `x`.

The concept checks that these expressions are valid and return the exact stated
types. It does not require any operation to be `constexpr`. Associativity,
identity laws, and the interaction between `mapping` and `op` must be satisfied
by the implementation.

Built-in acted monoids also expose two metadata flags:

* `static constexpr bool commutative` describes the value operation `op`.
* `static constexpr bool operator_commutative` describes the operator operation
  `op_comp`.

Generic data structures may use these flags to select faster representations or
algorithms. Both members are deliberately optional and are not part of
`IsActedMonoid`, so a contest-local acted monoid may omit them. An omitted flag
is treated conservatively by data structures that inspect it.

## Algebraic Laws

In addition to the value-monoid laws, update composition must be associative
with identity `op_id()`. For valid values and operators:

* `mapping(op_id(), x) == x`.
* `mapping(op_comp(f, g), x) == mapping(f, mapping(g, x))`.
* `mapping(f, op(a, b)) == op(mapping(f, a), mapping(f, b))`.

These equations describe ordinary, position-independent actions. Some supplied
arithmetic-progression actions use `mapping(f, x, offset)` and `op_shift`;
when splitting a segment, its right child's update must be shifted by the
left child's length. Use a data structure supporting those hooks, as shown on
the action's page.

An aggregate's `size` describes the elements it represents. `id()` has size
zero, while `make(v)` creates one element; filling leaves with `id()` does not
create ordinary zero-valued elements. See the
[initialization guide](https://m1une.github.io/m1une_library/guide.html#monoids-and-updates).

## Commutative Acted Group

`m1une::acted_monoid::IsCommutativeActedGroup` extends `IsActedMonoid` with an
inverse for the value monoid:

* `static value_type inv(const value_type& x)`
  Returns the inverse of `x` with respect to the value operation `op`.

The concept checks only the interface. The value operation should satisfy the
commutative group laws, and `mapping` should still distribute over `op`.

## Example

This custom action stores a sum and a segment length, and adds a constant to
all elements in a range:

```cpp
#include "acted_monoid/concept.hpp"
#include "ds/segtree/lazy_segtree.hpp"
#include <cassert>
#include <vector>

struct RangeAddSum {
    struct value_type {
        long long sum;
        long long size;
    };
    using operator_type = long long;

    static value_type id() { return {0, 0}; }
    static value_type op(const value_type& a, const value_type& b) {
        return {a.sum + b.sum, a.size + b.size};
    }
    static operator_type op_id() { return 0; }
    static operator_type op_comp(const operator_type& f, const operator_type& g) {
        return f + g;
    }
    static value_type mapping(const operator_type& f, const value_type& x) {
        return {x.sum + f * x.size, x.size};
    }
    static value_type make(long long value) { return {value, 1}; }
};

static_assert(m1une::acted_monoid::IsActedMonoid<RangeAddSum>);

int main() {
    m1une::ds::LazySegtree<RangeAddSum> seg(std::vector<long long>{1, 2, 3});
    seg.apply(0, 2, 5);
    assert(seg.prod(0, 3).sum == 16);
}
```

## Complexity

These concepts are compile-time interface checks and have no runtime cost.
