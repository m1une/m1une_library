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
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix_det_arbitrary_mod.test.cpp
    title: verify/math/matrix/matrix_det_arbitrary_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/determinant_mod.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <type_traits>\n\n#line 1 \"math/matrix/matrix.hpp\"\
    \n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\n#include <cstddef>\n#line 7 \"math/matrix/matrix.hpp\"\
    \n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace matrix\
    \ {\n\ntemplate <class T>\nclass Matrix {\n   private:\n    int _rows;\n    int\
    \ _cols;\n    std::vector<T> _data;\n\n    static std::size_t storage_size(int\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/determinant_mod.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\nnamespace detail {\n\ninline std::uint64_t\
    \ determinant_multiply_mod(std::uint64_t lhs,\n                              \
    \                std::uint64_t rhs,\n                                        \
    \      std::uint64_t modulus) {\n    return std::uint64_t(static_cast<unsigned\
    \ __int128>(lhs) * rhs % modulus);\n}\n\ninline std::uint64_t determinant_subtract_product_mod(\n\
    \    std::uint64_t value, std::uint64_t lhs, std::uint64_t rhs,\n    std::uint64_t\
    \ modulus) {\n    const std::uint64_t product = determinant_multiply_mod(lhs,\
    \ rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(value)\
    \ + modulus - product) %\n                         modulus);\n}\n\ninline std::uint64_t\
    \ determinant_add_products_mod(\n    std::uint64_t first_lhs, std::uint64_t first_rhs,\n\
    \    std::uint64_t second_lhs, std::uint64_t second_rhs,\n    std::uint64_t modulus)\
    \ {\n    const std::uint64_t first =\n        determinant_multiply_mod(first_lhs,\
    \ first_rhs, modulus);\n    const std::uint64_t second =\n        determinant_multiply_mod(second_lhs,\
    \ second_rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(first)\
    \ + second) % modulus);\n}\n\ntemplate <class Integer>\nstd::uint64_t determinant_normalize(Integer\
    \ value, std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    static_assert(sizeof(Integer) <= sizeof(std::uint64_t));\n    if constexpr\
    \ (std::is_signed_v<Integer>) {\n        __int128 residue = static_cast<__int128>(value)\
    \ % static_cast<__int128>(modulus);\n        if (residue < 0) residue += modulus;\n\
    \        return std::uint64_t(residue);\n    } else {\n        return std::uint64_t(static_cast<unsigned\
    \ __int128>(value) % modulus);\n    }\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class Integer>\nstd::uint64_t determinant_mod(const Matrix<Integer>& matrix,\n\
    \                              std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    assert(matrix.rows() == matrix.cols());\n    assert(modulus > 0);\n    const\
    \ int size = matrix.rows();\n    if (size == 0) return std::uint64_t(1) % modulus;\n\
    \n    Matrix<std::uint64_t> reduced(size, size);\n    for (int row = 0; row <\
    \ size; row++) {\n        for (int col = 0; col < size; col++) {\n           \
    \ reduced[row][col] =\n                detail::determinant_normalize(matrix[row][col],\
    \ modulus);\n        }\n    }\n\n    std::uint64_t result = std::uint64_t(1) %\
    \ modulus;\n    bool negate = false;\n    for (int col = 0; col < size; col++)\
    \ {\n        int pivot = col;\n        while (pivot < size && reduced[pivot][col]\
    \ == 0) pivot++;\n        if (pivot == size) return 0;\n        if (pivot != col)\
    \ {\n            reduced.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        for (int row = col + 1; row < size; row++) {\n         \
    \   std::uint64_t upper = reduced[col][col];\n            std::uint64_t lower\
    \ = reduced[row][col];\n            if (lower == 0) continue;\n\n            std::uint64_t\
    \ upper_upper = 1 % modulus;\n            std::uint64_t upper_lower = 0;\n   \
    \         std::uint64_t lower_upper = 0;\n            std::uint64_t lower_lower\
    \ = 1 % modulus;\n            while (upper != 0 && lower != 0) {\n           \
    \     if (upper < lower) {\n                    const std::uint64_t quotient =\
    \ lower / upper;\n                    lower -= quotient * upper;\n           \
    \         lower_upper = detail::determinant_subtract_product_mod(\n          \
    \              lower_upper, quotient, upper_upper, modulus);\n               \
    \     lower_lower = detail::determinant_subtract_product_mod(\n              \
    \          lower_lower, quotient, upper_lower, modulus);\n                } else\
    \ {\n                    const std::uint64_t quotient = upper / lower;\n     \
    \               upper -= quotient * lower;\n                    upper_upper =\
    \ detail::determinant_subtract_product_mod(\n                        upper_upper,\
    \ quotient, lower_upper, modulus);\n                    upper_lower = detail::determinant_subtract_product_mod(\n\
    \                        upper_lower, quotient, lower_lower, modulus);\n     \
    \           }\n            }\n\n            for (int index = col; index < size;\
    \ index++) {\n                const std::uint64_t old_upper = reduced[col][index];\n\
    \                const std::uint64_t old_lower = reduced[row][index];\n      \
    \          reduced[col][index] = detail::determinant_add_products_mod(\n     \
    \               upper_upper, old_upper, upper_lower, old_lower, modulus);\n  \
    \              reduced[row][index] = detail::determinant_add_products_mod(\n \
    \                   lower_upper, old_upper, lower_lower, old_lower, modulus);\n\
    \            }\n            if (upper == 0) {\n                reduced.swap_rows(col,\
    \ row);\n                negate = !negate;\n            }\n        }\n\n     \
    \   result = detail::determinant_multiply_mod(\n            result, reduced[col][col],\
    \ modulus);\n        if (result == 0) return 0;\n    }\n    return negate ? modulus\
    \ - result : result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_DETERMINANT_MOD_HPP\n#define M1UNE_MATRIX_DETERMINANT_MOD_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\n#include\
    \ \"matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\nnamespace detail\
    \ {\n\ninline std::uint64_t determinant_multiply_mod(std::uint64_t lhs,\n    \
    \                                          std::uint64_t rhs,\n              \
    \                                std::uint64_t modulus) {\n    return std::uint64_t(static_cast<unsigned\
    \ __int128>(lhs) * rhs % modulus);\n}\n\ninline std::uint64_t determinant_subtract_product_mod(\n\
    \    std::uint64_t value, std::uint64_t lhs, std::uint64_t rhs,\n    std::uint64_t\
    \ modulus) {\n    const std::uint64_t product = determinant_multiply_mod(lhs,\
    \ rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(value)\
    \ + modulus - product) %\n                         modulus);\n}\n\ninline std::uint64_t\
    \ determinant_add_products_mod(\n    std::uint64_t first_lhs, std::uint64_t first_rhs,\n\
    \    std::uint64_t second_lhs, std::uint64_t second_rhs,\n    std::uint64_t modulus)\
    \ {\n    const std::uint64_t first =\n        determinant_multiply_mod(first_lhs,\
    \ first_rhs, modulus);\n    const std::uint64_t second =\n        determinant_multiply_mod(second_lhs,\
    \ second_rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(first)\
    \ + second) % modulus);\n}\n\ntemplate <class Integer>\nstd::uint64_t determinant_normalize(Integer\
    \ value, std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    static_assert(sizeof(Integer) <= sizeof(std::uint64_t));\n    if constexpr\
    \ (std::is_signed_v<Integer>) {\n        __int128 residue = static_cast<__int128>(value)\
    \ % static_cast<__int128>(modulus);\n        if (residue < 0) residue += modulus;\n\
    \        return std::uint64_t(residue);\n    } else {\n        return std::uint64_t(static_cast<unsigned\
    \ __int128>(value) % modulus);\n    }\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class Integer>\nstd::uint64_t determinant_mod(const Matrix<Integer>& matrix,\n\
    \                              std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    assert(matrix.rows() == matrix.cols());\n    assert(modulus > 0);\n    const\
    \ int size = matrix.rows();\n    if (size == 0) return std::uint64_t(1) % modulus;\n\
    \n    Matrix<std::uint64_t> reduced(size, size);\n    for (int row = 0; row <\
    \ size; row++) {\n        for (int col = 0; col < size; col++) {\n           \
    \ reduced[row][col] =\n                detail::determinant_normalize(matrix[row][col],\
    \ modulus);\n        }\n    }\n\n    std::uint64_t result = std::uint64_t(1) %\
    \ modulus;\n    bool negate = false;\n    for (int col = 0; col < size; col++)\
    \ {\n        int pivot = col;\n        while (pivot < size && reduced[pivot][col]\
    \ == 0) pivot++;\n        if (pivot == size) return 0;\n        if (pivot != col)\
    \ {\n            reduced.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        for (int row = col + 1; row < size; row++) {\n         \
    \   std::uint64_t upper = reduced[col][col];\n            std::uint64_t lower\
    \ = reduced[row][col];\n            if (lower == 0) continue;\n\n            std::uint64_t\
    \ upper_upper = 1 % modulus;\n            std::uint64_t upper_lower = 0;\n   \
    \         std::uint64_t lower_upper = 0;\n            std::uint64_t lower_lower\
    \ = 1 % modulus;\n            while (upper != 0 && lower != 0) {\n           \
    \     if (upper < lower) {\n                    const std::uint64_t quotient =\
    \ lower / upper;\n                    lower -= quotient * upper;\n           \
    \         lower_upper = detail::determinant_subtract_product_mod(\n          \
    \              lower_upper, quotient, upper_upper, modulus);\n               \
    \     lower_lower = detail::determinant_subtract_product_mod(\n              \
    \          lower_lower, quotient, upper_lower, modulus);\n                } else\
    \ {\n                    const std::uint64_t quotient = upper / lower;\n     \
    \               upper -= quotient * lower;\n                    upper_upper =\
    \ detail::determinant_subtract_product_mod(\n                        upper_upper,\
    \ quotient, lower_upper, modulus);\n                    upper_lower = detail::determinant_subtract_product_mod(\n\
    \                        upper_lower, quotient, lower_lower, modulus);\n     \
    \           }\n            }\n\n            for (int index = col; index < size;\
    \ index++) {\n                const std::uint64_t old_upper = reduced[col][index];\n\
    \                const std::uint64_t old_lower = reduced[row][index];\n      \
    \          reduced[col][index] = detail::determinant_add_products_mod(\n     \
    \               upper_upper, old_upper, upper_lower, old_lower, modulus);\n  \
    \              reduced[row][index] = detail::determinant_add_products_mod(\n \
    \                   lower_upper, old_upper, lower_lower, old_lower, modulus);\n\
    \            }\n            if (upper == 0) {\n                reduced.swap_rows(col,\
    \ row);\n                negate = !negate;\n            }\n        }\n\n     \
    \   result = detail::determinant_multiply_mod(\n            result, reduced[col][col],\
    \ modulus);\n        if (result == 0) return 0;\n    }\n    return negate ? modulus\
    \ - result : result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MATRIX_DETERMINANT_MOD_HPP\n"
  dependsOn:
  - math/matrix/matrix.hpp
  isVerificationFile: false
  path: math/matrix/determinant_mod.hpp
  requiredBy:
  - math/matrix/all.hpp
  - math/all.hpp
  timestamp: '2026-07-18 19:05:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/matrix.test.cpp
  - verify/math/matrix/matrix_det_arbitrary_mod.test.cpp
documentation_of: math/matrix/determinant_mod.hpp
layout: document
title: Determinant Modulo a Composite Modulus
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
