---
title: Bit Matrix
documentation_of: ../../../math/matrix/bit_matrix.hpp
---

## Overview

`BitMatrix` is a dynamically sized matrix over the field $\mathrm{GF}(2)$.
Every row is packed into 64-bit blocks, so row addition and Gaussian elimination
process 64 entries at once.

Use it for binary linear systems, XOR constraints, parity transitions, binary
matrix multiplication, ranks, determinants, and inverses.

## Construction and Access

| Interface | Description | Complexity |
| --- | --- | --- |
| `BitMatrix()` | Constructs a `0 x 0` matrix. | $O(1)$ |
| `BitMatrix(rows, cols, value)` | Constructs a matrix filled with `value`; the default is `false`. | $O(rows\lceil cols/64\rceil)$ |
| `rows()`, `cols()`, `blocks_per_row()`, `empty()` | Returns shape or storage information. | $O(1)$ |
| `matrix[row][col]`, `matrix(row, col)`, `get(row, col)` | Reads one entry. Non-const indexed access returns an assignable bit proxy. | $O(1)$ |
| `set(row, col, value)`, `reset(row, col)`, `flip(row, col)` | Changes one entry. | $O(1)$ |
| `clear()` | Sets every entry to zero. | $O(rows\lceil cols/64\rceil)$ |
| `set_row(row, bits)` | Replaces a row from a `0`/`1` string of length `cols`. | $O(cols)$ |
| `row_string(row)` | Returns one row as a `0`/`1` string. | $O(cols)$ |

Dimensions and indices are checked with `assert`.

## Matrix Operations

All arithmetic is over $\mathrm{GF}(2)$, so addition, subtraction, and XOR are
the same operation.

| Interface | Description | Complexity |
| --- | --- | --- |
| `BitMatrix::identity(size)` | Returns the identity matrix. | $O(size\lceil size/64\rceil)$ |
| `transposed()` | Returns the transpose. | $O(rows\cdot cols)$ |
| `swap_rows(first, second)` | Exchanges two rows. | $O(\lceil cols/64\rceil)$ |
| `xor_rows(target, source, first_col)` | XORs the source row into the target on `[first_col, cols)`; `first_col` defaults to `0`. | $O(\lceil (cols-first_col)/64\rceil)$ |
| `+`, `-`, `^`, `+=`, `-=`, `^=` | Entrywise GF(2) addition. Shapes must match. | $O(rows\lceil cols/64\rceil)$ |
| `lhs * rhs`, `lhs *= rhs` | GF(2) matrix multiplication. | $O(lhs.rows\cdot lhs.cols\cdot\lceil rhs.cols/64\rceil)$ worst case |
| `==`, `!=` | Compares shapes and packed entries. | $O(rows\lceil cols/64\rceil)$ |
| `pow(exponent)` | Raises a square matrix to a nonnegative power. | Matrix-multiplication complexity times $O(\log exponent)$ |

## Linear Algebra

| Function | Signature | Description | Complexity |
| --- | --- | --- | --- |
| `reduced_row_echelon_form` | `BitRowReduction reduced_row_echelon_form(BitMatrix matrix)` | Returns the reduced matrix and pivot columns. | $O(rows\min(rows,cols)\lceil cols/64\rceil)$ |
| `matrix_rank` | `int matrix_rank(BitMatrix matrix)` | Returns the GF(2) rank. It transposes tall matrices first. | $O(\min(rows,cols)^2\lceil\max(rows,cols)/64\rceil + rows\cdot cols)$ |
| `determinant` | `bool determinant(const BitMatrix& matrix)` | Returns the determinant of a square matrix. | $O(n^3/64)$ |
| `inverse` | `std::optional<BitMatrix> inverse(const BitMatrix& matrix)` | Returns the inverse, or `std::nullopt` if singular. | $O(n^3/64)$ |
| `solve_linear_system` | `BitLinearSystemResult solve_linear_system(const BitMatrix& coefficients, const std::vector<bool>& constants)` | Solves `coefficients * x = constants`, returning one solution and a nullspace basis. | $O(rows\min(rows,cols)\lceil cols/64\rceil + cols^2)$ including basis output |

`BitRowReduction` contains `matrix`, `pivot_columns`, and `rank()`.

`BitLinearSystemResult` contains `consistent`, `particular_solution`,
`nullspace_basis`, and `pivot_columns`. It also provides `rank()`, `nullity()`,
and `has_unique_solution()`.

## Example

```cpp
#include "math/matrix/bit_matrix.hpp"

#include <iostream>

int main() {
    m1une::matrix::BitMatrix matrix(3, 3);
    matrix.set_row(0, "110");
    matrix.set_row(1, "011");
    matrix.set_row(2, "101");

    std::cout << m1une::matrix::matrix_rank(matrix) << "\n";  // 2
    auto inverse = m1une::matrix::inverse(matrix);
    std::cout << inverse.has_value() << "\n";  // 0
}
```
