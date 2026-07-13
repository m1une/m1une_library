---
title: Pfaffian
documentation_of: ../../../math/matrix/pfaffian.hpp
---

## Overview

`pfaffian` computes the Pfaffian of an even-dimensional alternating matrix.
For such a matrix $A$, the result satisfies
$\operatorname{pf}(A)^2=\det(A)$.

The implementation uses skew-symmetric Gaussian elimination.

## Requirements

`matrix` must be square with even size, zero diagonal, and
`matrix[i][j] == -matrix[j][i]`.

`T` must be a field type supporting construction from `0` and `1`, equality,
addition, subtraction, multiplication, and division by a nonzero value.

## API

```cpp
template <class T>
T pfaffian(Matrix<T> matrix);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `pfaffian(matrix)` | Returns the Pfaffian. The argument is copied and the caller's matrix is unchanged. | $O(N^3)$ time and $O(N^2)$ memory |

The Pfaffian of the empty matrix is `T(1)`.

## Example

```cpp
#include "math/matrix/matrix.hpp"
#include "math/matrix/pfaffian.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    m1une::matrix::Matrix<mint> matrix(2, 2);
    matrix[0][1] = 7;
    matrix[1][0] = mint(0) - matrix[0][1];
    std::cout << m1une::matrix::pfaffian(matrix) << "\n";  // 7
}
```
