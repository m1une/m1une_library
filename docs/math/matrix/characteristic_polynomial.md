---
title: Characteristic Polynomial
documentation_of: ../../../math/matrix/characteristic_polynomial.hpp
---

## Overview

`characteristic_polynomial` computes the monic characteristic polynomial of a
square matrix:

$$
p(x) = \det(xI - A).
$$

```cpp
#include "math/matrix/characteristic_polynomial.hpp"
```

The function and `Matrix` are in `m1une::matrix`.

## Interface

```cpp
template <class T>
std::vector<T> characteristic_polynomial(Matrix<T> matrix);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `characteristic_polynomial(matrix)` | Returns the coefficients of $\det(xI-A)$ in ascending degree order. | $O(N^3)$ time and $O(N^2)$ additional memory |

The input must be square. For an `N` by `N` matrix, the returned vector has
`N + 1` elements and satisfies

$$
p(x) = p_0 + p_1x + \dots + p_Nx^N.
$$

In particular, `result[N]` is one and `result[0]` is
$(-1)^N\det(A)$. The characteristic polynomial of the empty `0` by `0` matrix
is the constant polynomial `{1}`.

The matrix is passed by value and reduced internally, so the caller's matrix is
not modified unless it is explicitly moved into the function.

`T` must represent a field: it must support construction from zero and one,
equality, addition, subtraction, multiplication, and division by a nonzero
value. Fixed-prime modular integers are the main intended type. The algorithm
uses exact zero comparisons, so floating-point types are not recommended.

## Algorithm

Similarity transformations first reduce the matrix to upper Hessenberg form.
These transformations preserve the characteristic polynomial. The
characteristic polynomials of all leading principal submatrices are then built
using the Hessenberg recurrence.

## Example

```cpp
#include "math/matrix/characteristic_polynomial.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using mint = m1une::math::modint998244353;
    std::vector<mint> values{1, 2, 3, 4};
    m1une::matrix::Matrix<mint> matrix(2, 2, values);

    // det(xI - matrix) = x^2 - 5x - 2.
    std::vector<mint> polynomial =
        m1une::matrix::characteristic_polynomial(matrix);
    for (mint coefficient : polynomial) {
        std::cout << coefficient << ' ';
    }
}
```
