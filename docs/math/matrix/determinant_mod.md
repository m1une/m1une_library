---
title: Determinant Modulo a Composite Modulus
documentation_of: ../../../math/matrix/determinant_mod.hpp
---

## Overview

`determinant_mod` computes the determinant of an integral square matrix modulo
an arbitrary positive modulus. Unlike field Gaussian elimination, it never
divides by a matrix entry, so the modulus may be composite and pivot values do
not need to be invertible.

Pairs of rows are reduced with the extended Euclidean algorithm. Every row
transformation is unimodular, which preserves the determinant up to a tracked
sign.

## Requirements

The matrix entry type must be an integral type no wider than 64 bits. Entries
may be signed or unsigned and are normalized modulo `modulus`. The modulus must
be positive; `modulus == 1` is supported.

## Public Interface

```cpp
template <class Integer>
std::uint64_t determinant_mod(
    const Matrix<Integer>& matrix,
    std::uint64_t modulus
);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `determinant_mod(matrix, modulus)` | Returns `det(matrix)` in `[0, modulus)`. The matrix must be square and is not mutated. | $O(N^3 + N^2 \log M)$ time and $O(N^2)$ memory |

Here $N$ is the matrix size and $M$ is the modulus. The determinant of the
empty matrix is `1 % modulus`.

## Example

```cpp
#include "math/matrix/determinant_mod.hpp"

#include <cstdint>

int main() {
    m1une::matrix::Matrix<long long> matrix(2, 2);
    matrix[0][0] = 2;
    matrix[0][1] = 3;
    matrix[1][0] = 4;
    matrix[1][1] = 5;
    std::uint64_t determinant = m1une::matrix::determinant_mod(matrix, 12);
    return determinant == 10 ? 0 : 1;
}
```
