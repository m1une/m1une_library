---
title: Linear Matroid Intersection
documentation_of: ../../matroid/linear_matroid_intersection.hpp
---

## Overview

`linear_matroid_intersection_size` returns the maximum size of a set that is
linearly independent in each of two vector families on the same ground set.
Unlike general matroid intersection, it computes only the cardinality, not a
maximizing set.

For vectors $a_e$ and $b_e$, the answer is the symbolic rank of

$$
\sum_e x_e a_e b_e^T.
$$

The algorithm substitutes random field values for $x_e$ and applies Gaussian
elimination. It never returns more than the correct answer, and can return less
with small probability. Over a field of size $q$, the failure probability of
one evaluation is at most $R/q$, where $R$ is the answer. Use a large prime
field such as `modint998244353`; small fields such as $\mathbb F_2$ are not
suitable.

Each outer vector is one ground-set element. Thus both arguments have size $N$,
while their inner vector dimensions may differ.

## Requirements

`Field` must be a field type supporting construction from integers, equality,
addition, subtraction, multiplication, and division. Every vector within one
family must have the same dimension.

For the generator overload, `random()` must return a value from which `Field`
can be constructed. Independent uniform field values give the stated error
bound.

## Interface

```cpp
template <class Field>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors);

template <class Field, class RandomNumberGenerator>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    RandomNumberGenerator& random);

template <class Field>
int linear_matroid_intersection_size_with_weights(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    const std::vector<Field>& weights);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `linear_matroid_intersection_size(first, second)` | Returns the maximum common independent-set size using an internally seeded random evaluation. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |
| `linear_matroid_intersection_size(first, second, random)` | Uses the supplied random-number generator. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |
| `linear_matroid_intersection_size_with_weights(first, second, weights)` | Uses the explicit values `weights[e]` for $x_e$. This is deterministic, but adversarial values need not preserve the symbolic rank. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |

Here $N$ is the ground-set size and $D_1,D_2$ are the two vector dimensions.
The randomized overloads use $O(N+D_1D_2)$ auxiliary memory, and the explicit
weight overload uses $O(D_1D_2)$. Inputs are not modified. `weights` must have
size $N$.

## Example

```cpp
#include "math/modint.hpp"
#include "matroid/linear_matroid_intersection.hpp"
#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<std::vector<mint>> first(3), second(3);
    first[0] = {1, 0};
    first[1] = {0, 1};
    first[2] = {1, 1};
    second[0] = {1, 0};
    second[1] = {1, 0};
    second[2] = {0, 1};

    int size =
        m1une::matroid::linear_matroid_intersection_size(first, second);
    // size == 2
}
```
