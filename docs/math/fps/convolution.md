---
title: Convolution
documentation_of: ../../../math/fps/convolution.hpp
---

## Overview

Fast polynomial convolution for static modular integer types such as
`m1une::math::modint998244353`.

For exact signed `long long` coefficients rather than modular coefficients,
use [`convolution_ll`](convolution_ll.md).

The implementation automatically chooses between:

* a quadratic loop for small inputs;
* one NTT convolution when the modulus supports the required transform length;
* block NTT convolution under `998244353` when the result is longer than
  $2^{23}$ coefficients;
* three NTT convolutions plus CRT reconstruction for moduli such as
  `1000000007`.

## API

```cpp
template <class Mint>
std::vector<Mint> convolution(
    const std::vector<Mint>& a,
    const std::vector<Mint>& b);

template <class Mint>
std::vector<Mint> convolution_naive(
    const std::vector<Mint>& a,
    const std::vector<Mint>& b);

template <class Mint>
std::vector<Mint> convolution_ntt(
    const std::vector<Mint>& a,
    const std::vector<Mint>& b);
```

`convolution(a, b)[k]` is the sum of `a[i] * b[j]` over all `i + j = k`.
If either input is empty, the result is empty.

`convolution_ntt` directly selects the single-NTT implementation. Both inputs
must be nonempty, and the smallest power of two at least
`a.size() + b.size() - 1` must divide `Mint::mod() - 1`. Prefer `convolution`
unless this precondition is already known.

## Complexity

Let $A$ and $B$ be the input sizes, $R=A+B-1$, and $L$ be the smallest power of
two with $L\ge R$.

| Function | Time | Memory including result |
|---|---:|---:|
| `convolution_naive` | $O(AB)$ | $O(R)$ for the returned vector |
| `convolution_ntt` | $O(L\log L)$ | $O(L)$ |
| `convolution` (one NTT or CRT) | $O(L\log L)$ | $O(L)$ |

All functions return a new vector and do not modify either input. Their
additional memory usage is linear in the processed coefficient count. For
`998244353`, inputs as large as the Library Checker `convolution_mod_large`
limit ($2^{24}$ coefficients each) are split into blocks and processed with
$T=2^{23}$-point NTTs. If $P=\lceil 2A/T\rceil$ and
$Q=\lceil 2B/T\rceil$ are the block counts, this path takes
$O((P+Q)T\log T+PQT)$ time and $O((P+Q)T+R)$ memory including the returned
vector. Under the stated Library Checker bounds, $P,Q\le4$.

For an NTT-friendly modulus, the transform length must divide
`Mint::mod() - 1`. The CRT fallback supports transform lengths up to
$2^{24}$ and requires the exact integer coefficient bound to fit in the
product of its three internal primes. These conditions cover ordinary
competitive-programming use with modulus `1000000007`.

## Example

```cpp
#include "math/fps/convolution.hpp"
#include "math/modint.hpp"

#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<mint> a = {1, 2, 3};
    std::vector<mint> b = {4, 5};
    std::vector<mint> c = m1une::fps::convolution(a, b);
    // c is 4, 13, 22, 15.
}
```
