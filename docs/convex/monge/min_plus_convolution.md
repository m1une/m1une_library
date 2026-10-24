---
title: Structured Min-Plus and Max-Plus Convolution
documentation_of: ../../../convex/monge/min_plus_convolution.hpp
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

## Worked example: split a total quantity between two suppliers

Supplier A charges `a[i]` for exactly `i` units; supplier B charges `b[j]`
for exactly `j` units. Given `a={0,5,1}` and `b={0,2,6}`, find the cheapest
cost for **every** total quantity `k=i+j`.

| Total `k` | Costs of valid splits | Minimum |
| --- | --- | --- |
| 0 | `a[0]+b[0]=0` | 0 |
| 1 | `a[0]+b[1]=2`, `a[1]+b[0]=5` | 2 |
| 2 | `a[0]+b[2]=6`, `a[1]+b[1]=7`, `a[2]+b[0]=1` | 1 |
| 3 | `a[1]+b[2]=11`, `a[2]+b[1]=3` | 3 |
| 4 | `a[2]+b[2]=7` | 7 |

The straightforward implementation checks every pair:

```cpp
std::vector<long long> answer(a.size() + b.size() - 1, infinity);
for (int i = 0; i < int(a.size()); ++i) {
    for (int j = 0; j < int(b.size()); ++j) {
        answer[i+j] = std::min(answer[i+j], a[i] + b[j]);
    }
}
```

Here B's adjacent price differences are `2,4`, which are nondecreasing.
That makes `b` convex, so use:

```cpp
#include "convex/monge/min_plus_convolution.hpp"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a = {0, 5, 1};  // May have arbitrary differences.
    std::vector<long long> b = {0, 2, 6};  // Differences 2,4: convex.
    assert(m1une::convex::is_convex_sequence(b));
    auto answer = m1une::convex::min_plus_convolution_convex(a, b);
    assert(answer == std::vector<long long>({0, 2, 1, 3, 7}));
    for (int k = 0; k < int(answer.size()); ++k) {
        std::cout << k << ' ' << answer[k] << '\n';
    }
}
```

Output (total quantity, minimum cost):

```text
0 0
1 2
2 1
3 3
4 7
```

The arguments are the **two cost arrays**, with the convex one second; there
is no callback. The result contains minimum **values**, not split indices.
Its length is `a.size()+b.size()-1`, because possible totals run from `0` to
`(a.size()-1)+(b.size()-1)`. Work drops from $O(NM)$ to $O(N+M)$.

For your own inputs, check the second array's adjacent differences. If both
arrays are convex, use `min_plus_convolution_convex_convex` for smaller
constants. To maximize instead, use `max_plus_convolution_concave` with a
concave second array (nonincreasing adjacent differences).

If quantities are unavailable, use the sentinel-aware overload. For example,
`b={0,2,6,INF}` says quantity 3 from B is unavailable. Pass `INF` as the third
argument, and check output entries for `INF` before using them. The exact
finite-domain restrictions are specified below.

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
any indices; those candidates are omitted from SMAWK, and result indices with no
finite decomposition remain infinite. Values are recognized as infinite by
equality with the supplied sentinel, so no finite input or finite sum may equal
that value. The sentinel does not need to be the numeric maximum or minimum of
`T`.

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
