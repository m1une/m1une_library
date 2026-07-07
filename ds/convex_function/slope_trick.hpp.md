---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: ds/convex_function/all.hpp
    title: Convex Function All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/convex_function/slope_trick.test.cpp
    title: verify/ds/convex_function/slope_trick.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/convex_function/slope_trick.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <optional>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <class T>\nstruct SlopeTrickArgmin {\n    std::optional<T> left;\n  \
    \  std::optional<T> right;\n};\n\ntemplate <class T>\nclass SlopeTrick {\n   \
    \ static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\n    T _minimum\
    \ = T();\n    T _left_offset = T();\n    T _right_offset = T();\n    std::priority_queue<T>\
    \ _left;\n    std::priority_queue<T, std::vector<T>, std::greater<T>> _right;\n\
    \n    T left_top() const {\n        return _left.top() + _left_offset;\n    }\n\
    \n    T right_top() const {\n        return _right.top() + _right_offset;\n  \
    \  }\n\n    void push_left(T value) {\n        _left.push(value - _left_offset);\n\
    \    }\n\n    void push_right(T value) {\n        _right.push(value - _right_offset);\n\
    \    }\n\n   public:\n    SlopeTrick() = default;\n\n    T minimum() const {\n\
    \        return _minimum;\n    }\n\n    int breakpoint_count() const {\n     \
    \   return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_CONVEX_FUNCTION_SLOPE_TRICK_HPP\n#define M1UNE_DS_CONVEX_FUNCTION_SLOPE_TRICK_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <optional>\n#include\
    \ <queue>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n \
    \   std::optional<T> left;\n    std::optional<T> right;\n};\n\ntemplate <class\
    \ T>\nclass SlopeTrick {\n    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\
    \n    T _minimum = T();\n    T _left_offset = T();\n    T _right_offset = T();\n\
    \    std::priority_queue<T> _left;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> _right;\n\n    T left_top() const {\n        return _left.top()\
    \ + _left_offset;\n    }\n\n    T right_top() const {\n        return _right.top()\
    \ + _right_offset;\n    }\n\n    void push_left(T value) {\n        _left.push(value\
    \ - _left_offset);\n    }\n\n    void push_right(T value) {\n        _right.push(value\
    \ - _right_offset);\n    }\n\n   public:\n    SlopeTrick() = default;\n\n    T\
    \ minimum() const {\n        return _minimum;\n    }\n\n    int breakpoint_count()\
    \ const {\n        return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif \
    \ // M1UNE_DS_CONVEX_FUNCTION_SLOPE_TRICK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/convex_function/slope_trick.hpp
  requiredBy:
  - ds/convex_function/all.hpp
  timestamp: '2026-07-07 17:18:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/convex_function/slope_trick.test.cpp
documentation_of: ds/convex_function/slope_trick.hpp
layout: document
title: Slope Trick
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
