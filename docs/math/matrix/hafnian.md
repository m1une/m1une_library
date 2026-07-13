---
title: Hafnian
documentation_of: ../../../math/matrix/hafnian.hpp
---

## Overview

The hafnian of a symmetric $N\times N$ matrix is the sum, over every perfect
pairing of the indices, of the product of the paired matrix entries. It is the
weighted perfect-matching analogue of the permanent.

`hafnian` uses a polynomial-space Björklund recurrence and is intended for
small even dimensions, including the Library Checker limit $N=38$.

## Requirements

`matrix` must be square with even size, zero diagonal, and
`matrix[i][j] == matrix[j][i]`.

`T` must be a commutative ring type supporting construction from `0` and `1`,
equality, addition, subtraction, and multiplication. Division is not required.

## API

```cpp
template <class T>
T hafnian(const Matrix<T>& matrix);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `hafnian(matrix)` | Returns the hafnian without modifying `matrix`. | $O(N^4 2^{N/2})$ time and $O(N^4)$ memory |

The bounds conservatively account for naive truncated-polynomial products and
the matrices retained along the recursion. The hafnian of the empty matrix is
`T(1)`.

## Example

```cpp
#include "math/matrix/hafnian.hpp"
#include "math/matrix/matrix.hpp"

#include <iostream>

int main() {
    m1une::matrix::Matrix<long long> matrix(2, 2);
    matrix[0][1] = matrix[1][0] = 12;
    std::cout << m1une::matrix::hafnian(matrix) << "\n";  // 12
}
```
