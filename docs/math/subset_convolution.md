---
title: Subset Convolution
documentation_of: ../../math/subset_convolution.hpp
---

## Overview

Subset convolution combines two arrays indexed by bit masks. For every mask
$S$, it computes

$$
c_S = \sum_{T \subseteq S} a_T b_{S \setminus T}.
$$

Equivalently, every term partitions `S` into two disjoint masks. This operation
appears in subset dynamic programming when two independently solved parts must
cover the current set exactly.

```cpp
#include "math/subset_convolution.hpp"
```

The function is in `m1une::math`.

## Interface

```cpp
template <typename T>
std::vector<T> subset_convolution(
    std::vector<T> first,
    std::vector<T> second
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `subset_convolution(first, second)` | Returns the subset convolution of two equally sized mask arrays. | $O(K^2 2^K)$ time and $O(K 2^K)$ additional memory |

Both input vectors must have the same size. Their size must be zero or a power
of two; a nonempty vector of size $2^K$ represents masks on `K` bits. Empty
inputs produce an empty result. The result has the same size as each input.

The arguments are passed by value and used as workspace, so the caller's
vectors are unchanged unless explicitly moved into the function. The element
type `T` must be default-constructible and support multiplication, `operator+=`,
and `operator-=`. Modular integers and ordinary integer types satisfy these
requirements.

The implementation separates coefficients by mask popcount, applies ranked
subset-zeta transforms, multiplies the rank polynomials pointwise, and applies
the ranked Mobius transform. It uses two flat ranked work buffers rather than
allocating a separate vector for every mask.

## Example

```cpp
#include "math/subset_convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> a{1, 2, 3, 4};
    std::vector<long long> b{5, 6, 7, 8};

    std::vector<long long> c =
        m1une::math::subset_convolution(a, b);

    // c[3] = a[0] * b[3] + a[1] * b[2]
    //      + a[2] * b[1] + a[3] * b[0] = 60.
    std::cout << c[3] << '\n';
}
```
