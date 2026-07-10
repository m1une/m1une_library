---
title: Isolated Partition Number (HRR)
documentation_of: ../../math/partition_number_hrr.hpp
---

## Overview

`partition_number_hrr(n)` computes one exact integer partition number $p(n)$.
It is intended for an isolated, potentially very large index. This differs
from `partition_function<Mint>(maximum)`, which efficiently computes every
coefficient from `p(0)` through `p(maximum)` modulo `Mint::mod()`.

The function uses FLINT's implementation of the
Hardy-Ramanujan-Rademacher formula. FLINT evaluates $O(\sqrt n)$ terms using
factored exponential sums and Arb variable-precision ball arithmetic. A
Rademacher remainder bound is added to the numerical enclosure, and the result
is accepted only when the ball contains one unique integer.

For small indices, FLINT uses lookup and Euler-recurrence shortcuts. Its HRR
path is used for sufficiently large indices.

## Dependency

This optional header requires FLINT 3 and links against FLINT, GMP, and MPFR.
It is deliberately not included by `math/all.hpp`, so the rest of the library
remains dependency-free and header-only.

On common systems, install FLINT with one of:

```sh
brew install flint
sudo apt-get install libflint-dev
```

Use `pkg-config` when compiling:

```sh
g++ -std=c++20 -O2 -I. program.cpp $(pkg-config --cflags --libs flint)
```

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `utilities::BigInt partition_number_hrr(unsigned long n)` | $O(n^{1/2+o(1)})$ bit operations plus output conversion | Returns the exact integer $p(n)$. |

The returned value has $\Theta(\sqrt n)$ bits, so merely writing it requires
$\Omega(\sqrt n)$ work and memory. The index must fit `unsigned long`.

## Example

```cpp
#include "math/partition_number_hrr.hpp"

#include <iostream>

int main() {
    m1une::utilities::BigInt answer =
        m1une::math::partition_number_hrr(1000);
    std::cout << answer << "\n";
}
```

## Verification

The external-dependency test is intentionally ignored by
`online-judge-verify-helper`. Run it manually with:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -I. \
    verify/math/partition_number_hrr.test.cpp \
    $(pkg-config --cflags --libs flint) \
    -o partition_number_hrr.test
./partition_number_hrr.test
```

The test checks known exact values, compares every result through 5000 with
the independent FPS implementation modulo $10^9+7$, and exercises the HRR
path at $n=10^6$.

## References

* Fredrik Johansson, [Efficient implementation of the
  Hardy-Ramanujan-Rademacher formula](https://arxiv.org/abs/1205.5991).
* [FLINT partition-function interface](https://flintlib.org/doc/partitions.html).
