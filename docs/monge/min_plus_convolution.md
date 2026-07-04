---
title: Structured Min-Plus Convolution
documentation_of: ../../monge/min_plus_convolution.hpp
---

## Overview

For arrays `a` and `b`, min-plus convolution is

$$
c[k] = \min_{i+j=k}(a[i] + b[j]).
$$

When `b` is a discrete convex sequence, the minimizing index in `a` is
nondecreasing with `k`. `min_plus_convolution_convex` uses this Monge structure
to avoid the naive quadratic algorithm. When both sequences are convex,
`min_plus_convolution_convex_convex` merges their nondecreasing adjacent
differences and runs in linear time.

The header also provides the symmetric max-plus operation when the second
sequence is concave.

## Functions

```cpp
template <class T>
std::vector<T> min_plus_convolution_convex(
    const std::vector<T>& arbitrary,
    const std::vector<T>& convex
);

template <class T>
std::vector<T> min_plus_convolution_convex_convex(
    const std::vector<T>& first,
    const std::vector<T>& second
);

template <class T>
std::vector<T> max_plus_convolution_concave(
    const std::vector<T>& arbitrary,
    const std::vector<T>& concave
);
```

For `min_plus_convolution_convex`, the first sequence is arbitrary and the
second must have nondecreasing adjacent differences. Both arguments to
`min_plus_convolution_convex_convex` must have nondecreasing adjacent
differences. For max-plus, the first sequence is arbitrary and the second must
have nonincreasing adjacent differences.

If either sequence is empty, the result is empty. Otherwise its length is
the sum of the input lengths minus one.

The precondition helpers are:

```cpp
template <class T>
bool is_convex_sequence(const std::vector<T>& sequence);

template <class T>
bool is_concave_sequence(const std::vector<T>& sequence);
```

Sequences of length at most two satisfy both properties. The convolution
functions do not run these checks automatically.

## Complexity

For input lengths `N` and `M`:

| Function | Time | Memory, including the result |
| --- | --- | --- |
| `min_plus_convolution_convex` | $O((N + M)\log(N + M))$ | $O(N + M)$ |
| `min_plus_convolution_convex_convex` | $O(N + M)$ | $O(N + M)$ |
| `max_plus_convolution_concave` | $O((N + M)\log(N + M))$ | $O(N + M)$ |
| `is_convex_sequence` | $O(N)$ | $O(1)$ |
| `is_concave_sequence` | $O(N)$ | $O(1)$ |

The element type must support addition, subtraction, and comparison.
Intermediate values and adjacent differences must fit in the type.

## Example

```cpp
#include "monge/min_plus_convolution.hpp"
#include <vector>

int main() {
    std::vector<long long> first = {0, 2, 7, 15};
    std::vector<long long> second = {1, 2, 5, 10};

    auto result = m1une::monge::min_plus_convolution_convex_convex(first,
                                                                   second);
}
```
