---
title: Structured Min-Plus and Max-Plus Convolution
documentation_of: ../../monge/min_plus_convolution.hpp
---

## Overview

For arrays `a` and `b`, min-plus convolution is

$$
c[k] = \min_{i+j=k}(a[i] + b[j]).
$$

When `b` is a discrete convex sequence, the minimizing index in `a` is
nondecreasing with `k`. `min_plus_convolution_convex` applies SMAWK to this
implicit Monge matrix and computes every minimum in linear time. Only the second
sequence must be convex; the first may be arbitrary.

The header also provides the symmetric `max_plus_convolution_concave`. Only its
second sequence must be concave, meaning that its adjacent differences are
nonincreasing.

When both inputs are structured,
`min_plus_convolution_convex_convex` and
`max_plus_convolution_concave_concave` merge their adjacent differences
directly. These specializations have the same linear asymptotic complexity but
smaller constants than the SMAWK-based one-sided functions.

## Functions

```cpp
template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex
);

template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex,
    const T& infinity
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second,
    const T& infinity
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave,
    const T& negative_infinity
);

template <class T>
std::vector<T> max_plus_convolution_concave_concave(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> max_plus_convolution_concave_concave(
    const std::vector<T>& first,
    const std::vector<T>& second,
    const T& negative_infinity
);
```

For `min_plus_convolution_convex`, the first sequence is arbitrary and the
second must have nondecreasing adjacent differences. For
`max_plus_convolution_concave`, the first sequence is arbitrary and the second
must have nonincreasing adjacent differences. Both inputs to the specialized
functions must have the corresponding structure.

The three-argument overloads treat the last argument as an absorbing extended
value. For min-plus, `infinity + x` is `infinity`; for max-plus,
`negative_infinity + x` is `negative_infinity`. The finite entries of each
structured input must form one contiguous convex or concave interval. Infinity
may occur before or after that interval, so `{0, 1, infinity, infinity}` is a
valid extended convex sequence. The arbitrary input may contain the sentinel at
any indices. Values are recognized as infinite by equality with the supplied
sentinel, so no finite input or finite sum may equal that value. The sentinel
does not need to be the numeric maximum or minimum of `T`.

The two-argument overloads continue to treat every value as an ordinary element
of `T`.

If either sequence is empty, the result is empty. Otherwise its length is
the sum of the input lengths minus one.

The precondition helpers are:

```cpp
template <class T>
bool is_convex_sequence(const std::vector<T>& sequence);

template <class T>
bool is_convex_sequence(
    const std::vector<T>& sequence,
    const T& infinity
);

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence);

template <class T>
bool is_concave_sequence(
    const std::vector<T>& sequence,
    const T& negative_infinity
);
```

The sentinel-aware helpers check that the finite domain is contiguous in
addition to checking its adjacent differences. An all-infinity sequence is
accepted. The convolution functions do not run these checks automatically.

## Complexity

For input lengths `N` and `M`:

| Function | Time | Memory, including the result |
| --- | --- | --- |
| `min_plus_convolution_convex` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex(..., infinity)` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex` | $O(N + M)$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex(..., infinity)` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave(..., negative_infinity)` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave_concave` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave_concave(..., negative_infinity)` | $O(N + M)$ | $O(N + M)$ |
| `is_convex_sequence` | $O(N)$ | $O(1)$ |
| `is_concave_sequence` | $O(N)$ | $O(1)$ |

The convolution element type must support addition and comparison. The
sentinel-aware overloads additionally require equality comparison. The
precondition helpers and two-structured specializations require subtraction.
Finite intermediate sums and adjacent differences must fit in the type.

## Example

```cpp
#include "monge/min_plus_convolution.hpp"
#include <vector>

int main() {
    std::vector<long long> first = {4, -3, 8, 1};
    std::vector<long long> second = {1, 2, 5, 10};

    auto result = m1une::monge::min_plus_convolution_convex(first, second);

    std::vector<long long> another_convex = {0, 3, 8, 15};
    auto structured = m1une::monge::min_plus_convolution_convex_convex(
        another_convex, second);

    constexpr long long infinity = 2'000'000'000'000'000'000LL;
    std::vector<long long> extended_convex = {0, 1, infinity, infinity};
    auto extended = m1une::monge::min_plus_convolution_convex(
        first, extended_convex, infinity);

    std::vector<long long> first_max = {2, 9, -1, 5};
    std::vector<long long> second_concave = {-1, -2, -5, -10};
    auto maximum =
        m1une::monge::max_plus_convolution_concave(first_max, second_concave);
}
```
