---
title: Slope Trick
documentation_of: ../../../ds/convex_function/slope_trick.hpp
---

## Overview

`SlopeTrick<T>` maintains a convex piecewise-linear function whose slopes
change by integer units. It supports adding hinge and absolute-value functions,
translations, sliding-window minima, evaluation, function addition, and
min-plus convolution of two slope-trick functions.

The structure stores the breakpoints in two heaps. Most updates take logarithmic
time without explicitly constructing the function over its whole domain.

Typical applications include scheduling, sequence adjustment, median costs,
and dynamic programs with convex piecewise-linear states.

## Complexity Notation

* `N` is the number of breakpoints stored in the current object.
* `M` is the number of breakpoints stored in another object passed to `merge`
  or `min_plus_convolve`.

## Represented Function

A new object represents `f(x) = 0` for every `x`.

The template parameter must be a signed arithmetic type. `long long` is
recommended for integer problems. All values, breakpoint translations, and
intermediate sums must fit in `T`.

## Adding Functions

| Method | Effect |
| --- | --- |
| `void add_constant(T c)` | Adds the constant `c`. |
| `void add_x_minus_a(T a)` | Adds `max(x - a, 0)`. |
| `void add_a_minus_x(T a)` | Adds `max(a - x, 0)`. |
| `void add_abs(T a)` | Adds `abs(x - a)`. |

Each hinge insertion takes amortized $O(\log N)$ time, where `N` is the current
number of stored breakpoints. `add_abs` inserts two hinges.

## Minimum and Argmin

| Method | Meaning |
| --- | --- |
| `T minimum() const` | Minimum function value. |
| `SlopeTrickArgmin<T> argmin() const` | Closed interval on which the minimum is attained. |
| `int breakpoint_count() const` | Number of stored unit-slope breakpoints. |

`argmin()` returns `SlopeTrickArgmin<T>` with optional `left` and `right`
endpoints. An empty left endpoint means the interval is unbounded below; an
empty right endpoint means it is unbounded above.

For the initial constant function, both endpoints are empty.

## Translation and Sliding Minimum

`shift(delta)` replaces the function by

$$
g(x) = f(x-\mathrm{delta}).
$$

`shift(left_delta, right_delta)` requires
`left_delta <= right_delta` and computes

$$
g(x) = \min_{x-b \le y \le x-a} f(y).
$$

This operation shifts the left and right breakpoint heaps independently and
takes $O(1)$ time.

The one-sided variants are:

| Method | Effect |
| --- | --- |
| `void shift(T delta)` | Replaces `f(x)` by `f(x - delta)`. |
| `void shift(T left_delta, T right_delta)` | Replaces `f(x)` by a sliding-window minimum. |
| `void prefix_minimum()` / `void clear_right()` | Replaces `f(x)` by `min` over `y <= x` of `f(y)`. |
| `void suffix_minimum()` / `void clear_left()` | Replaces `f(x)` by `min` over `y >= x` of `f(y)`. |

Clearing one side takes linear time in the number of discarded breakpoints.

## Evaluation, Merge, and Convolution

`T evaluate(T x) const` returns `f(x)` in $O(N)$ time without changing the structure.
This is intended mainly for final answers and debugging; slope trick is useful
because updates and minimum queries avoid evaluating arbitrary points.

`void merge(SlopeTrick other)` adds the function represented by `other` to this function.
`other` is passed by value, so passing an rvalue avoids an extra copy. The
operation takes $O((N+M)\log(N+M))$ time in the worst case.

`void min_plus_convolve(SlopeTrick other)` replaces the represented function by

$$
h(x) = \min_y f(y) + g(x-y),
$$

where `g` is the function represented by `other`. The minimum value becomes
`f.minimum() + g.minimum()`, and the argmin interval is the Minkowski sum of
the two argmin intervals. If either side is unbounded on the left or right, the
corresponding result side is also unbounded.

`SlopeTrick<T> min_plus_convolution(SlopeTrick<T> first, SlopeTrick<T> second)`
returns the same convolution as a free function. Both APIs take their
arguments by value, so moving temporary slope tricks avoids extra copies.

The convolution keeps only slope levels that appear in both functions. Its
worst-case running time is $O((N+M)\log(N+M))$.

## Example

```cpp
#include "ds/convex_function/slope_trick.hpp"
#include <iostream>

int main() {
    m1une::ds::SlopeTrick<long long> slope;
    slope.add_abs(3);
    slope.add_x_minus_a(0);
    slope.shift(-1, 2);

    m1une::ds::SlopeTrick<long long> other;
    other.add_abs(5);
    auto convolved = m1une::ds::min_plus_convolution(slope, other);

    std::cout << convolved.minimum() << "\n";
    auto range = convolved.argmin();
    if (range.left) std::cout << *range.left << "\n";
}
```
