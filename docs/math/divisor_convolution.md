---
title: Divisor Convolution
documentation_of: ../../math/divisor_convolution.hpp
---

## Overview

`gcd_convolution` and `lcm_convolution` combine sequences indexed by positive
integers. For two sequences $a$ and $b$, they compute

$$
c_k = \sum_{\gcd(i,j)=k} a_i b_j
$$

or

$$
c_k = \sum_{\mathop{\rm lcm}(i,j)=k} a_i b_j,
$$

respectively.

Both operations use zeta and Mobius transforms on the divisibility poset. They
are useful when a direct quadratic loop over every pair of indices is too slow.

## Interface

All functions are in `m1une::math`.

| Function | Description | Complexity |
| --- | --- | --- |
| `template <typename T> std::vector<T> gcd_convolution(std::vector<T> first, std::vector<T> second)` | Returns the GCD convolution. | $O(N \log\log N)$ |
| `template <typename T> std::vector<T> lcm_convolution(std::vector<T> first, std::vector<T> second)` | Returns the LCM convolution. | $O(N \log\log N)$ |

Here, $N$ is one less than the larger input size. Both functions use $O(N)$
additional memory.

## Requirements and Behavior

* Index `0` is unused. The returned value at index `0` is value-initialized.
* If the input sizes differ, the shorter sequence is padded with zeros and the
  result has the larger size.
* If either input is empty, the result is empty.
* For LCM convolution, contributions whose LCM is outside the returned index
  range are discarded.
* `T` must be default-constructible and support `+=`, `-=`, and `*=`.

## Algorithm

GCD convolution applies the multiple zeta transform to both inputs, multiplies
the transformed values pointwise, and applies the multiple Mobius transform.
LCM convolution uses the divisor zeta and divisor Mobius transforms instead.

## Example

```cpp
#include "math/divisor_convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> first(7);
    std::vector<long long> second(7);
    first[1] = 1;
    first[2] = 2;
    first[3] = 3;
    second[1] = 4;
    second[2] = 5;
    second[3] = 6;

    auto gcd_result = m1une::math::gcd_convolution(first, second);
    auto lcm_result = m1une::math::lcm_convolution(first, second);

    std::cout << gcd_result[1] << ' ' << gcd_result[2] << ' '
              << gcd_result[3] << '\n';
    std::cout << lcm_result[1] << ' ' << lcm_result[2] << ' '
              << lcm_result[3] << ' ' << lcm_result[6] << '\n';
}
```

Output:

```text
62 10 18
4 23 36 27
```
