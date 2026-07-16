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
    path: verify/math/matrix/hafnian.test.cpp
    title: verify/math/matrix/hafnian.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/hafnian.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line\
    \ 5 \"math/matrix/matrix.hpp\"\n#include <cstddef>\n#include <cstdint>\n#line\
    \ 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\ntemplate\
    \ <class T>\nclass Matrix {\n   private:\n    int _rows;\n    int _cols;\n   \
    \ std::vector<T> _data;\n\n    static std::size_t storage_size(int rows, int cols)\
    \ {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        return std::size_t(rows)\
    \ * std::size_t(cols);\n    }\n\n   public:\n    using value_type = T;\n\n   \
    \ Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int rows, int cols, const T&\
    \ value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows, cols),\
    \ value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n       \
    \ : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/hafnian.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass HafnianSolver {\n    using Polynomial = std::vector<T>;\n    using\
    \ PolynomialMatrix = std::vector<std::vector<Polynomial>>;\n\n    int _degree;\n\
    \n    void add_shifted_product(Polynomial& result, const Polynomial& first,\n\
    \                             const Polynomial& second) const {\n        for (int\
    \ first_degree = 0; first_degree < _degree; first_degree++) {\n            for\
    \ (int second_degree = 0;\n                 first_degree + second_degree + 1 <\
    \ _degree;\n                 second_degree++) {\n                result[first_degree\
    \ + second_degree + 1] +=\n                    first[first_degree] * second[second_degree];\n\
    \            }\n        }\n    }\n\n    Polynomial solve(PolynomialMatrix matrix)\
    \ const {\n        if (matrix.empty()) {\n            Polynomial result(_degree);\n\
    \            result[0] = T(1);\n            return result;\n        }\n\n    \
    \    std::vector<Polynomial> first = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        std::vector<Polynomial> second = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        const int remaining = int(matrix.size());\n        Polynomial first_to_pair\
    \ = std::move(first[remaining]);\n\n        Polynomial result = solve(matrix);\n\
    \        for (T& coefficient : result) coefficient = T() - coefficient;\n\n  \
    \      for (int row = 0; row < remaining; row++) {\n            for (int col =\
    \ 0; col < row; col++) {\n                add_shifted_product(matrix[row][col],\
    \ first[row], second[col]);\n                add_shifted_product(matrix[row][col],\
    \ second[row], first[col]);\n            }\n        }\n\n        Polynomial with_connections\
    \ = solve(std::move(matrix));\n        add_shifted_product(result, first_to_pair,\
    \ with_connections);\n        for (int degree = 0; degree < _degree; degree++)\
    \ {\n            result[degree] += with_connections[degree];\n        }\n    \
    \    return result;\n    }\n\n   public:\n    explicit HafnianSolver(int size)\
    \ : _degree(size / 2 + 1) {}\n\n    T operator()(const Matrix<T>& matrix) const\
    \ {\n        const int size = matrix.rows();\n        PolynomialMatrix polynomial_matrix(size);\n\
    \        for (int row = 0; row < size; row++) {\n            polynomial_matrix[row].assign(row,\
    \ Polynomial(_degree));\n            for (int col = 0; col < row; col++) {\n \
    \               polynomial_matrix[row][col][0] = matrix[row][col];\n         \
    \   }\n        }\n        return solve(std::move(polynomial_matrix)).back();\n\
    \    }\n};\n\n}  // namespace internal\n\n// Returns the hafnian of an even-dimensional\
    \ symmetric zero-diagonal matrix.\ntemplate <class T>\nT hafnian(const Matrix<T>&\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    assert(size % 2 == 0);\n\n#ifndef NDEBUG\n    for (int row\
    \ = 0; row < size; row++) {\n        assert(matrix[row][row] == T());\n      \
    \  for (int col = row + 1; col < size; col++) {\n            assert(matrix[row][col]\
    \ == matrix[col][row]);\n        }\n    }\n#endif\n\n    return internal::HafnianSolver<T>(size)(matrix);\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_HAFNIAN_HPP\n#define M1UNE_MATRIX_HAFNIAN_HPP 1\n\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n#include \"matrix.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass HafnianSolver {\n    using Polynomial = std::vector<T>;\n    using\
    \ PolynomialMatrix = std::vector<std::vector<Polynomial>>;\n\n    int _degree;\n\
    \n    void add_shifted_product(Polynomial& result, const Polynomial& first,\n\
    \                             const Polynomial& second) const {\n        for (int\
    \ first_degree = 0; first_degree < _degree; first_degree++) {\n            for\
    \ (int second_degree = 0;\n                 first_degree + second_degree + 1 <\
    \ _degree;\n                 second_degree++) {\n                result[first_degree\
    \ + second_degree + 1] +=\n                    first[first_degree] * second[second_degree];\n\
    \            }\n        }\n    }\n\n    Polynomial solve(PolynomialMatrix matrix)\
    \ const {\n        if (matrix.empty()) {\n            Polynomial result(_degree);\n\
    \            result[0] = T(1);\n            return result;\n        }\n\n    \
    \    std::vector<Polynomial> first = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        std::vector<Polynomial> second = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        const int remaining = int(matrix.size());\n        Polynomial first_to_pair\
    \ = std::move(first[remaining]);\n\n        Polynomial result = solve(matrix);\n\
    \        for (T& coefficient : result) coefficient = T() - coefficient;\n\n  \
    \      for (int row = 0; row < remaining; row++) {\n            for (int col =\
    \ 0; col < row; col++) {\n                add_shifted_product(matrix[row][col],\
    \ first[row], second[col]);\n                add_shifted_product(matrix[row][col],\
    \ second[row], first[col]);\n            }\n        }\n\n        Polynomial with_connections\
    \ = solve(std::move(matrix));\n        add_shifted_product(result, first_to_pair,\
    \ with_connections);\n        for (int degree = 0; degree < _degree; degree++)\
    \ {\n            result[degree] += with_connections[degree];\n        }\n    \
    \    return result;\n    }\n\n   public:\n    explicit HafnianSolver(int size)\
    \ : _degree(size / 2 + 1) {}\n\n    T operator()(const Matrix<T>& matrix) const\
    \ {\n        const int size = matrix.rows();\n        PolynomialMatrix polynomial_matrix(size);\n\
    \        for (int row = 0; row < size; row++) {\n            polynomial_matrix[row].assign(row,\
    \ Polynomial(_degree));\n            for (int col = 0; col < row; col++) {\n \
    \               polynomial_matrix[row][col][0] = matrix[row][col];\n         \
    \   }\n        }\n        return solve(std::move(polynomial_matrix)).back();\n\
    \    }\n};\n\n}  // namespace internal\n\n// Returns the hafnian of an even-dimensional\
    \ symmetric zero-diagonal matrix.\ntemplate <class T>\nT hafnian(const Matrix<T>&\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    assert(size % 2 == 0);\n\n#ifndef NDEBUG\n    for (int row\
    \ = 0; row < size; row++) {\n        assert(matrix[row][row] == T());\n      \
    \  for (int col = row + 1; col < size; col++) {\n            assert(matrix[row][col]\
    \ == matrix[col][row]);\n        }\n    }\n#endif\n\n    return internal::HafnianSolver<T>(size)(matrix);\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n#endif  // M1UNE_MATRIX_HAFNIAN_HPP\n"
  dependsOn:
  - math/matrix/matrix.hpp
  isVerificationFile: false
  path: math/matrix/hafnian.hpp
  requiredBy:
  - math/all.hpp
  - math/matrix/all.hpp
  timestamp: '2026-07-14 02:42:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/hafnian.test.cpp
  - verify/math/matrix/matrix.test.cpp
documentation_of: math/matrix/hafnian.hpp
layout: document
title: Hafnian
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
