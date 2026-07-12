---
title: Prefix Sum of Binomial Coefficients
documentation_of: ../../math/prefix_sum_of_binom.hpp
---

## Overview

`PrefixSumOfBinom<Mint>` and `OfflinePrefixSumOfBinom<Mint>` compute

$$
\sum_{k=0}^{m-1} \binom{n}{k}.
$$

The online structure is useful when queries must be answered immediately. It
precomputes binomial-prefix values at square-root-spaced endpoints. The offline
structure stores all queries and moves between them in Mo order, using Pascal's
identity to update the current answer.

`Mint` must provide the static-modulus interface used by `ModInt`. The modulus
must be prime, odd for the offline structure, and larger than every queried
`n`.

## API

```cpp
template <class Mint>
struct PrefixSumOfBinom {
    explicit PrefixSumOfBinom(int maximum);
    int maximum() const;
    Mint query(int n, int m) const;
};

template <class Mint>
struct OfflinePrefixSumOfBinom {
    int query_count() const;
    bool empty() const;
    void reserve(int query_capacity);
    void clear();
    int add_query(int n, int m);
    std::vector<Mint> calculate() const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `PrefixSumOfBinom(maximum)` | Precomputes data for every `0 <= n <= maximum`. | $O(N\sqrt N)$ time and memory |
| `maximum()` | Returns the largest supported `n`. | $O(1)$ |
| `query(n, m)` | Returns the half-open prefix through `m - 1`. | $O(\sqrt N)$ |
| `query_count()` | Returns the number of stored offline queries. | $O(1)$ |
| `empty()` | Tests whether the offline batch is empty. | $O(1)$ |
| `reserve(query_capacity)` | Reserves storage for offline queries. | $O(Q)$ in the worst case |
| `clear()` | Removes all offline queries. | $O(Q)$ |
| `add_query(n, m)` | Stores a query and returns its insertion-order ID. | Amortized $O(1)$ |
| `calculate()` | Returns answers in insertion order. | $O((N+Q)\sqrt Q)$ time and $O(N+Q)$ memory |

Here $N$ is the largest queried or constructed `n`, and $Q$ is the number of
offline queries.

## Behavioral Notes

* The range in `k` is half-open: `query(n, m)` sums `0 <= k < m`.
* `m == 0` returns zero.
* Values `m > n + 1` are clamped to `n + 1`, so the result is `2^n`.
* The online constructor asserts that `maximum` is nonnegative and smaller than
  the modulus. Each query asserts `0 <= n <= maximum` and `m >= 0`.
* `calculate()` does not clear or mutate the offline query batch. Query IDs and
  returned positions use insertion order.
* The online version has relatively high memory use. Prefer the offline version
  when all queries are known beforehand.

## Example

```cpp
#include "math/modint.hpp"
#include "math/prefix_sum_of_binom.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::modint998244353;
    m1une::math::PrefixSumOfBinom<Mint> prefix(1000);

    // 1 + 5 + 10 = 16
    std::cout << prefix.query(5, 3) << '\n';

    m1une::math::OfflinePrefixSumOfBinom<Mint> offline;
    offline.add_query(5, 3);
    offline.add_query(4, 5);
    const auto answers = offline.calculate();
    std::cout << answers[0] << ' ' << answers[1] << '\n';
}
```
