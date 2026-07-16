---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/matrix/all.hpp
    title: Matrix Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/characteristic_polynomial.test.cpp
    title: verify/math/matrix/characteristic_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 6 \"math/matrix/matrix.hpp\"\n#include\
    \ <cstdint>\n#line 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matrix {\n\ntemplate <class T>\nclass Matrix {\n   private:\n    int _rows;\n\
    \    int _cols;\n    std::vector<T> _data;\n\n    static std::size_t storage_size(int\
    \ rows, int cols) {\n        assert(rows >= 0);\n        assert(cols >= 0);\n\
    \        return std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n\
    \    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int\
    \ rows, int cols, const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
    \ cols), value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n\
    \        : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        assert(_data.size() == std::size_t(rows)\
    \ * std::size_t(cols));\n    }\n\n    explicit Matrix(const std::vector<std::vector<T>>&\
    \ values)\n        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),\n\
    \          _data(storage_size(_rows, _cols)) {\n        for (int row = 0; row\
    \ < _rows; row++) {\n            assert(int(values[std::size_t(row)].size()) ==\
    \ _cols);\n            for (int col = 0; col < _cols; col++) {\n             \
    \   (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n        \
    \    }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n  \
    \  }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 10 \"math/matrix/characteristic_polynomial.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nstd::vector<T>\
    \ characteristic_polynomial(Matrix<T> matrix) {\n    assert(matrix.rows() == matrix.cols());\n\
    \    const int size = matrix.rows();\n\n    for (int col = 0; col + 2 < size;\
    \ col++) {\n        int pivot = col + 1;\n        while (pivot < size && matrix[pivot][col]\
    \ == T()) pivot++;\n        if (pivot == size) continue;\n\n        if (pivot\
    \ != col + 1) {\n            matrix.swap_rows(pivot, col + 1);\n            for\
    \ (int row = 0; row < size; row++) {\n                std::swap(matrix[row][pivot],\
    \ matrix[row][col + 1]);\n            }\n        }\n\n        const T inverse_pivot\
    \ = T(1) / matrix[col + 1][col];\n        for (int row = col + 2; row < size;\
    \ row++) {\n            if (matrix[row][col] == T()) continue;\n            const\
    \ T factor = matrix[row][col] * inverse_pivot;\n            for (int j = col;\
    \ j < size; j++) {\n                matrix[row][j] -= factor * matrix[col + 1][j];\n\
    \            }\n            for (int i = 0; i < size; i++) {\n               \
    \ matrix[i][col + 1] += factor * matrix[i][row];\n            }\n        }\n \
    \   }\n\n    std::vector<std::vector<T>> polynomial(std::size_t(size + 1));\n\
    \    polynomial[0].assign(1, T(1));\n    for (int leading_size = 1; leading_size\
    \ <= size; leading_size++) {\n        const int last = leading_size - 1;\n   \
    \     polynomial[std::size_t(leading_size)].assign(\n            std::size_t(leading_size\
    \ + 1),\n            T()\n        );\n        const std::vector<T>& previous =\n\
    \            polynomial[std::size_t(leading_size - 1)];\n        std::vector<T>&\
    \ current = polynomial[std::size_t(leading_size)];\n\n        for (int degree\
    \ = 0; degree < leading_size; degree++) {\n            current[std::size_t(degree)]\
    \ -=\n                previous[std::size_t(degree)] * matrix[last][last];\n  \
    \          current[std::size_t(degree + 1)] +=\n                previous[std::size_t(degree)];\n\
    \        }\n\n        T subdiagonal_product = T(1);\n        for (int row = last\
    \ - 1; row >= 0; row--) {\n            subdiagonal_product *= matrix[row + 1][row];\n\
    \            const T factor = subdiagonal_product * matrix[row][last];\n     \
    \       if (factor == T()) continue;\n            for (int degree = 0; degree\
    \ <= row; degree++) {\n                current[std::size_t(degree)] -=\n     \
    \               factor * polynomial[std::size_t(row)][std::size_t(degree)];\n\
    \            }\n        }\n    }\n    return polynomial[std::size_t(size)];\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP\n#define M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#include \"matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\ntemplate\
    \ <class T>\nstd::vector<T> characteristic_polynomial(Matrix<T> matrix) {\n  \
    \  assert(matrix.rows() == matrix.cols());\n    const int size = matrix.rows();\n\
    \n    for (int col = 0; col + 2 < size; col++) {\n        int pivot = col + 1;\n\
    \        while (pivot < size && matrix[pivot][col] == T()) pivot++;\n        if\
    \ (pivot == size) continue;\n\n        if (pivot != col + 1) {\n            matrix.swap_rows(pivot,\
    \ col + 1);\n            for (int row = 0; row < size; row++) {\n            \
    \    std::swap(matrix[row][pivot], matrix[row][col + 1]);\n            }\n   \
    \     }\n\n        const T inverse_pivot = T(1) / matrix[col + 1][col];\n    \
    \    for (int row = col + 2; row < size; row++) {\n            if (matrix[row][col]\
    \ == T()) continue;\n            const T factor = matrix[row][col] * inverse_pivot;\n\
    \            for (int j = col; j < size; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[col + 1][j];\n            }\n            for (int i = 0;\
    \ i < size; i++) {\n                matrix[i][col + 1] += factor * matrix[i][row];\n\
    \            }\n        }\n    }\n\n    std::vector<std::vector<T>> polynomial(std::size_t(size\
    \ + 1));\n    polynomial[0].assign(1, T(1));\n    for (int leading_size = 1; leading_size\
    \ <= size; leading_size++) {\n        const int last = leading_size - 1;\n   \
    \     polynomial[std::size_t(leading_size)].assign(\n            std::size_t(leading_size\
    \ + 1),\n            T()\n        );\n        const std::vector<T>& previous =\n\
    \            polynomial[std::size_t(leading_size - 1)];\n        std::vector<T>&\
    \ current = polynomial[std::size_t(leading_size)];\n\n        for (int degree\
    \ = 0; degree < leading_size; degree++) {\n            current[std::size_t(degree)]\
    \ -=\n                previous[std::size_t(degree)] * matrix[last][last];\n  \
    \          current[std::size_t(degree + 1)] +=\n                previous[std::size_t(degree)];\n\
    \        }\n\n        T subdiagonal_product = T(1);\n        for (int row = last\
    \ - 1; row >= 0; row--) {\n            subdiagonal_product *= matrix[row + 1][row];\n\
    \            const T factor = subdiagonal_product * matrix[row][last];\n     \
    \       if (factor == T()) continue;\n            for (int degree = 0; degree\
    \ <= row; degree++) {\n                current[std::size_t(degree)] -=\n     \
    \               factor * polynomial[std::size_t(row)][std::size_t(degree)];\n\
    \            }\n        }\n    }\n    return polynomial[std::size_t(size)];\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n#endif  // M1UNE_MATRIX_CHARACTERISTIC_POLYNOMIAL_HPP\n"
  dependsOn:
  - math/matrix/matrix.hpp
  isVerificationFile: false
  path: math/matrix/characteristic_polynomial.hpp
  requiredBy:
  - math/matrix/all.hpp
  - math/all.hpp
  timestamp: '2026-07-13 05:25:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/matrix.test.cpp
  - verify/math/matrix/characteristic_polynomial.test.cpp
documentation_of: math/matrix/characteristic_polynomial.hpp
layout: document
title: Characteristic Polynomial
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
