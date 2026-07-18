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
    path: verify/math/matrix/adjugate.test.cpp
    title: verify/math/matrix/adjugate.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/adjugate.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\
    \n#include <cstddef>\n#include <cstdint>\n#include <utility>\n#line 9 \"math/matrix/matrix.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nclass Matrix\
    \ {\n   private:\n    int _rows;\n    int _cols;\n    std::vector<T> _data;\n\n\
    \    static std::size_t storage_size(int rows, int cols) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n\
    \    }\n\n   public:\n    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0)\
    \ {}\n\n    Matrix(int rows, int cols, const T& value = T())\n        : _rows(rows),\
    \ _cols(cols), _data(storage_size(rows, cols), value) {}\n\n    Matrix(int rows,\
    \ int cols, std::vector<T> values)\n        : _rows(rows), _cols(cols), _data(std::move(values))\
    \ {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        assert(_data.size()\
    \ == std::size_t(rows) * std::size_t(cols));\n    }\n\n    explicit Matrix(const\
    \ std::vector<std::vector<T>>& values)\n        : _rows(int(values.size())), _cols(values.empty()\
    \ ? 0 : int(values[0].size())),\n          _data(storage_size(_rows, _cols)) {\n\
    \        for (int row = 0; row < _rows; row++) {\n            assert(int(values[std::size_t(row)].size())\
    \ == _cols);\n            for (int col = 0; col < _cols; col++) {\n          \
    \      (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n     \
    \       }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n\
    \    }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 8 \"math/matrix/adjugate.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nMatrix<T> adjugate(Matrix<T>\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    Matrix<T> augmented(size, size * 2);\n    for (int row =\
    \ 0; row < size; row++) {\n        for (int col = 0; col < size; col++) {\n  \
    \          augmented[row][col] = matrix[row][col];\n        }\n        augmented[row][size\
    \ + row] = T(1);\n    }\n\n    std::vector<int> pivot_columns;\n    T pivot_product\
    \ = T(1);\n    bool negate = false;\n    for (int col = 0; col < size && int(pivot_columns.size())\
    \ < size; col++) {\n        const int pivot_row = int(pivot_columns.size());\n\
    \        int pivot = pivot_row;\n        while (pivot < size && augmented[pivot][col]\
    \ == T()) pivot++;\n        if (pivot == size) continue;\n        if (pivot !=\
    \ pivot_row) {\n            augmented.swap_rows(pivot, pivot_row);\n         \
    \   negate = !negate;\n        }\n\n        const T pivot_value = augmented[pivot_row][col];\n\
    \        pivot_product *= pivot_value;\n        const T inverse_pivot = T(1) /\
    \ pivot_value;\n        for (int index = col; index < size; index++) {\n     \
    \       augmented[pivot_row][index] *= inverse_pivot;\n        }\n        for\
    \ (int index = size; index < size * 2; index++) {\n            augmented[pivot_row][index]\
    \ *= inverse_pivot;\n        }\n\n        for (int row = 0; row < size; row++)\
    \ {\n            if (row == pivot_row || augmented[row][col] == T()) continue;\n\
    \            const T factor = augmented[row][col];\n            augmented[row][col]\
    \ = T();\n            for (int index = col + 1; index < size; index++) {\n   \
    \             augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n            for (int index = size; index < size * 2; index++)\
    \ {\n                augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n        }\n        pivot_columns.push_back(col);\n    }\n\n  \
    \  const int rank = int(pivot_columns.size());\n    Matrix<T> result(size, size);\n\
    \    if (rank + 1 < size) return result;\n\n    if (rank == size) {\n        const\
    \ T determinant = negate ? T() - pivot_product : pivot_product;\n        for (int\
    \ row = 0; row < size; row++) {\n            for (int col = 0; col < size; col++)\
    \ {\n                result[row][col] = determinant * augmented[row][size + col];\n\
    \            }\n        }\n        return result;\n    }\n\n    int free_column\
    \ = 0;\n    while (free_column < rank && pivot_columns[free_column] == free_column)\
    \ {\n        free_column++;\n    }\n    std::vector<T> right_null(size);\n   \
    \ right_null[free_column] = T(1);\n    for (int row = 0; row < rank; row++) {\n\
    \        right_null[pivot_columns[row]] = T() - augmented[row][free_column];\n\
    \    }\n\n    T scale = pivot_product;\n    if (negate != bool((size - 1 + free_column)\
    \ & 1)) scale = T() - scale;\n    for (int row = 0; row < size; row++) {\n   \
    \     for (int col = 0; col < size; col++) {\n            result[row][col] =\n\
    \                scale * right_null[row] * augmented[size - 1][size + col];\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_ADJUGATE_HPP\n#define M1UNE_MATRIX_ADJUGATE_HPP 1\n\n\
    #include <cassert>\n#include <vector>\n\n#include \"matrix.hpp\"\n\nnamespace\
    \ m1une {\nnamespace matrix {\n\ntemplate <class T>\nMatrix<T> adjugate(Matrix<T>\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    Matrix<T> augmented(size, size * 2);\n    for (int row =\
    \ 0; row < size; row++) {\n        for (int col = 0; col < size; col++) {\n  \
    \          augmented[row][col] = matrix[row][col];\n        }\n        augmented[row][size\
    \ + row] = T(1);\n    }\n\n    std::vector<int> pivot_columns;\n    T pivot_product\
    \ = T(1);\n    bool negate = false;\n    for (int col = 0; col < size && int(pivot_columns.size())\
    \ < size; col++) {\n        const int pivot_row = int(pivot_columns.size());\n\
    \        int pivot = pivot_row;\n        while (pivot < size && augmented[pivot][col]\
    \ == T()) pivot++;\n        if (pivot == size) continue;\n        if (pivot !=\
    \ pivot_row) {\n            augmented.swap_rows(pivot, pivot_row);\n         \
    \   negate = !negate;\n        }\n\n        const T pivot_value = augmented[pivot_row][col];\n\
    \        pivot_product *= pivot_value;\n        const T inverse_pivot = T(1) /\
    \ pivot_value;\n        for (int index = col; index < size; index++) {\n     \
    \       augmented[pivot_row][index] *= inverse_pivot;\n        }\n        for\
    \ (int index = size; index < size * 2; index++) {\n            augmented[pivot_row][index]\
    \ *= inverse_pivot;\n        }\n\n        for (int row = 0; row < size; row++)\
    \ {\n            if (row == pivot_row || augmented[row][col] == T()) continue;\n\
    \            const T factor = augmented[row][col];\n            augmented[row][col]\
    \ = T();\n            for (int index = col + 1; index < size; index++) {\n   \
    \             augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n            for (int index = size; index < size * 2; index++)\
    \ {\n                augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n        }\n        pivot_columns.push_back(col);\n    }\n\n  \
    \  const int rank = int(pivot_columns.size());\n    Matrix<T> result(size, size);\n\
    \    if (rank + 1 < size) return result;\n\n    if (rank == size) {\n        const\
    \ T determinant = negate ? T() - pivot_product : pivot_product;\n        for (int\
    \ row = 0; row < size; row++) {\n            for (int col = 0; col < size; col++)\
    \ {\n                result[row][col] = determinant * augmented[row][size + col];\n\
    \            }\n        }\n        return result;\n    }\n\n    int free_column\
    \ = 0;\n    while (free_column < rank && pivot_columns[free_column] == free_column)\
    \ {\n        free_column++;\n    }\n    std::vector<T> right_null(size);\n   \
    \ right_null[free_column] = T(1);\n    for (int row = 0; row < rank; row++) {\n\
    \        right_null[pivot_columns[row]] = T() - augmented[row][free_column];\n\
    \    }\n\n    T scale = pivot_product;\n    if (negate != bool((size - 1 + free_column)\
    \ & 1)) scale = T() - scale;\n    for (int row = 0; row < size; row++) {\n   \
    \     for (int col = 0; col < size; col++) {\n            result[row][col] =\n\
    \                scale * right_null[row] * augmented[size - 1][size + col];\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_MATRIX_ADJUGATE_HPP\n"
  dependsOn:
  - math/matrix/matrix.hpp
  isVerificationFile: false
  path: math/matrix/adjugate.hpp
  requiredBy:
  - math/matrix/all.hpp
  - math/all.hpp
  timestamp: '2026-07-18 19:05:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/matrix.test.cpp
  - verify/math/matrix/adjugate.test.cpp
documentation_of: math/matrix/adjugate.hpp
layout: document
title: Adjugate Matrix
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
