---
title: Multiplicative Function Prefix Sum
documentation_of: ../../math/multiplicative_function_prefix_sum.hpp
---

## Overview

`MultiplicativeFunctionPrefixSum` uses a Min_25 sieve to compute

$$
F(x) = \sum_{k=1}^{x} f(k)
$$

for a multiplicative function `f`. It computes `F(n)` and, when useful, all
`F(floor(n / i))` in one run without enumerating every integer through `n`.

The caller supplies two descriptions of the function:

* `prime_power(p, e)` returns `f(p^e)` for a prime `p` and positive `e`.
* `prime_prefix[index(x)]` equals the sum of `f(p)` over primes `p <= x`.

The second part depends on the problem. The header provides tables for prime
counts and prime sums, which cover common formulas such as `f(p) = a + b * p`.
More general functions may build the required prime-prefix table separately.

## Requirements

`f` must be multiplicative and satisfy `f(1) = 1`.

The value type `T` must be constructible from the used integer types and support
default construction, addition, subtraction, and multiplication. In typical
use, `T` is a modular integer type. `PrimePower` must be callable as
`T(uint64_t prime, int exponent)`.

The argument `n` and all intermediate prime powers must fit in `uint64_t`.
The table has about `2 * sqrt(n)` entries and its size must fit in `int`.

## API

```cpp
template <class T, class PrimePower>
struct MultiplicativeFunctionPrefixSum {
    explicit MultiplicativeFunctionPrefixSum(
        uint64_t n,
        PrimePower prime_power
    );

    uint64_t n() const;
    uint64_t sqrt_n() const;
    const std::vector<int>& primes() const;
    int table_size() const;
    int index(uint64_t x) const;

    std::vector<uint64_t> quotient_values() const;
    std::vector<T> prime_count_table() const;
    std::vector<T> prime_sum_table() const;
    std::vector<T> prefix_sum_table(
        const std::vector<T>& prime_prefix
    ) const;
    T prefix_sum(const std::vector<T>& prime_prefix) const;
};
```

### Table layout

`quotient_values()` contains every distinct value `floor(n / i)`, together
with a dummy element at index zero. For each represented positive `x`,
`index(x)` is its table position. Every table accepted or returned by the class
uses this same layout.

`prime_count_table()` stores `pi(x)`, the number of primes at most `x`.
`prime_sum_table()` stores the sum of primes at most `x`.

`prefix_sum_table(prime_prefix)` returns `F(x)` at all represented `x`.
`prefix_sum(prime_prefix)` returns only `F(n)`. Neither method mutates the
solver or its input table. When `n = 0`, tables are empty and `prefix_sum`
returns `T{}`.

## Complexity

Let `N = n`.

| Method | Time | Extra returned memory |
| --- | --- | --- |
| Constructor | $O(\sqrt N)$ | $O(\sqrt N)$ in the object |
| `n`, `sqrt_n`, `primes`, `table_size`, `index` | $O(1)$ | $O(1)$ |
| `quotient_values` | $O(\sqrt N)$ | $O(\sqrt N)$ |
| `prime_count_table`, `prime_sum_table` | $O(N^{3/4} / \log N)$ | $O(\sqrt N)$ |
| `prefix_sum_table`, `prefix_sum` | $O(N^{3/4} / \log N)$ calls and ring operations | $O(\sqrt N)$ |

The bounds for the sieve methods are the standard Min_25 bounds; small values
have the expected lower practical cost.

## Example

This computes the Library Checker function defined by
`f(p^e) = a * e + b * p`.

```cpp
#include "math/modint.hpp"
#include "math/multiplicative_function_prefix_sum.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

using Mint = m1une::math::ModInt<469762049>;

int main() {
    uint64_t n = 1000000;
    Mint a = 2;
    Mint b = 3;

    auto prime_power = [a, b](uint64_t p, int e) {
        return a * Mint(e) + b * Mint(p);
    };
    using Solver = m1une::math::MultiplicativeFunctionPrefixSum<
        Mint,
        decltype(prime_power)
    >;
    Solver solver(n, prime_power);

    std::vector<Mint> prime_prefix = solver.prime_count_table();
    std::vector<Mint> prime_sum = solver.prime_sum_table();
    for (int i = 0; i < solver.table_size(); i++) {
        prime_prefix[i] = a * prime_prefix[i] + b * prime_sum[i];
    }

    std::cout << solver.prefix_sum(prime_prefix) << '\n';
}
```
