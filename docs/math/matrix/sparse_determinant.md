---
title: Sparse Determinant
documentation_of: ../../../math/matrix/sparse_determinant.hpp
---

## Overview

`sparse_determinant` computes the determinant of a sparse square matrix over a
large finite field without materializing a dense matrix. It combines random
diagonal preconditioning, a scalar Wiedemann sequence, and Berlekamp--Massey.

The algorithm is Las Vegas: the returned value is exact, while the number of
preconditioning attempts is random and has constant expectation over a large
field.

## Requirements

`T` must be a field type supporting construction from integers, equality,
addition, subtraction, multiplication, and division.

The convenience overload also requires `T::mod()` and assumes the nonzero
residues modulo `T::mod()` are suitable random field elements. This includes
the repository's static and dynamic modular integer types when their modulus
is prime.

Entries use zero-based row and column indices. Duplicate positions are allowed
and their values are added. Explicit zero entries are allowed.

## API

```cpp
template <class T>
struct SparseMatrixEntry {
    int row;
    int col;
    T value;
};

template <class T, class RandomValue>
T sparse_determinant_with_randomizer(
    int size,
    const std::vector<SparseMatrixEntry<T>>& entries,
    RandomValue random_nonzero
);

template <class T>
T sparse_determinant(
    int size,
    const std::vector<SparseMatrixEntry<T>>& entries,
    std::uint64_t seed = 0x243f6a8885a308d3ULL
);
```

`random_nonzero()` must return independent nonzero values of `T`. The default
overload uses a deterministic SplitMix64 stream; supplying the same seed makes
the sequence of attempts reproducible.

| Function | Description | Complexity |
| --- | --- | --- |
| `sparse_determinant_with_randomizer(size, entries, random_nonzero)` | Computes the determinant using the supplied field sampler. | Expected $O(N(M+N))$ time, $O(N+M)$ memory |
| `sparse_determinant(size, entries, seed)` | Uses the built-in deterministic pseudorandom stream. | Expected $O(N(M+N))$ time, $O(N+M)$ memory |

Here $M$ is `entries.size()`. The determinant of the empty matrix is `T(1)`.
The functions do not mutate `entries`.

## Example

```cpp
#include "math/matrix/sparse_determinant.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using mint = m1une::math::modint998244353;
    using Entry = m1une::matrix::SparseMatrixEntry<mint>;
    std::vector<Entry> entries;
    entries.push_back(Entry{0, 0, mint(2)});
    entries.push_back(Entry{1, 1, mint(3)});
    std::cout << m1une::matrix::sparse_determinant(2, entries) << "\n";  // 6
}
```
