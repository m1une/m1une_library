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

## Commutative Acted Group

`m1une::acted_monoid::IsCommutativeActedGroup` extends `IsActedMonoid` with an
inverse for the value monoid:

* `static value_type inv(const value_type& x)`
  Returns the inverse of `x` with respect to the value operation `op`.

The concept checks only the interface. The value operation should satisfy the
commutative group laws, and `mapping` should still distribute over `op`.

## Complexity

These concepts are compile-time interface checks and have no runtime cost.
