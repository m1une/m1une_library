---
title: Adjugate Matrix
documentation_of: ../../../math/matrix/adjugate.hpp
---

## Overview

For a square matrix $A$, `adjugate` returns the transpose of its cofactor
matrix. The result satisfies

$$
A\operatorname{adj}(A)=\operatorname{adj}(A)A=\det(A)I.
$$

The implementation performs one rank-revealing Gauss--Jordan elimination. It
uses the inverse formula at full rank, returns zero below rank $N-1$, and
reconstructs the rank-one adjugate from left and right null vectors at rank
$N-1$. It is deterministic and does not compute individual minors.

## Requirements

`T` must be a field type supporting construction from `0` and `1`, equality,
addition, subtraction, multiplication, and division by nonzero values. The
input matrix must be square.

## Public Interface

```cpp
template <class T>
Matrix<T> adjugate(Matrix<T> matrix);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `adjugate(matrix)` | Returns the adjugate. The argument is copied and the caller's matrix is unchanged. | $O(N^3)$ time and $O(N^2)$ memory |

The empty matrix produces an empty matrix. The adjugate of every `1 x 1`
matrix, including the zero matrix, is the matrix whose only entry is `1`.

## Example

```cpp
#include "math/matrix/adjugate.hpp"
#include "math/modint.hpp"

int main() {
    using Mint = m1une::math::modint998244353;
    m1une::matrix::Matrix<Mint> matrix(2, 2);
    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[1][0] = 3;
    matrix[1][1] = 4;
    auto result = m1une::matrix::adjugate(matrix);
    return result[0][0] == Mint(4) && result[0][1] == Mint(0) - Mint(2) &&
                   result[1][0] == Mint(0) - Mint(3) && result[1][1] == Mint(1)
               ? 0
               : 1;
}
```
