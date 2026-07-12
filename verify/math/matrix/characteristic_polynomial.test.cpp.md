---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/characteristic_polynomial.hpp
    title: Characteristic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/characteristic_polynomial
    links:
    - https://judge.yosupo.jp/problem/characteristic_polynomial
  bundledCode: "#line 1 \"verify/math/matrix/characteristic_polynomial.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\n\
    \n#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <utility>\n#include <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\
    \n\n\n\n#line 6 \"math/matrix/matrix.hpp\"\n#include <cstdint>\n#line 9 \"math/matrix/matrix.hpp\"\
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
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\
    \n\n\n\n#include <optional>\n#include <type_traits>\n#line 7 \"math/matrix/linear_algebra.hpp\"\
    \n\n#line 9 \"math/matrix/linear_algebra.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matrix {\n\ntemplate <class T>\nconstexpr T default_epsilon() {\n    if constexpr\
    \ (std::is_floating_point_v<T>) {\n        return T(1e-10);\n    } else {\n  \
    \      return T();\n    }\n}\n\nnamespace detail {\n\ntemplate <class T>\nT matrix_abs(T\
    \ value) {\n    return value < T() ? T() - value : value;\n}\n\ntemplate <class\
    \ T>\nbool is_zero(const T& value, const T& eps) {\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        return matrix_abs(value) <= eps;\n    } else {\n        (void)eps;\n\
    \        return value == T();\n    }\n}\n\ntemplate <class T>\nint choose_pivot(const\
    \ Matrix<T>& matrix, int first_row, int col, const T& eps) {\n    int pivot =\
    \ -1;\n    if constexpr (std::is_floating_point_v<T>) {\n        for (int row\
    \ = first_row; row < matrix.rows(); row++) {\n            if (is_zero(matrix[row][col],\
    \ eps)) continue;\n            if (pivot == -1 || matrix_abs(matrix[pivot][col])\
    \ < matrix_abs(matrix[row][col])) {\n                pivot = row;\n          \
    \  }\n        }\n    } else {\n        for (int row = first_row; row < matrix.rows();\
    \ row++) {\n            if (!is_zero(matrix[row][col], eps)) {\n             \
    \   pivot = row;\n                break;\n            }\n        }\n    }\n  \
    \  return pivot;\n}\n\ntemplate <class T>\nstd::vector<int> row_reduce(Matrix<T>&\
    \ matrix, int pivot_col_limit, const T& eps,\n                            bool\
    \ reduced) {\n    std::vector<int> pivot_columns;\n    int pivot_row = 0;\n  \
    \  for (int col = 0; col < pivot_col_limit && pivot_row < matrix.rows(); col++)\
    \ {\n        int pivot = choose_pivot(matrix, pivot_row, col, eps);\n        if\
    \ (pivot == -1) continue;\n        matrix.swap_rows(pivot_row, pivot);\n\n   \
    \     const T pivot_value = matrix[pivot_row][col];\n        if (reduced) {\n\
    \            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j] /=\
    \ pivot_value;\n        }\n\n        const int first_row = reduced ? 0 : pivot_row\
    \ + 1;\n        for (int row = first_row; row < matrix.rows(); row++) {\n    \
    \        if (row == pivot_row || is_zero(matrix[row][col], eps)) continue;\n \
    \           T factor = matrix[row][col];\n            if (!reduced) factor /=\
    \ pivot_value;\n            matrix[row][col] = T();\n            for (int j =\
    \ col + 1; j < matrix.cols(); j++) {\n                matrix[row][j] -= factor\
    \ * matrix[pivot_row][j];\n            }\n        }\n\n        pivot_columns.push_back(col);\n\
    \        pivot_row++;\n    }\n\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (T& value : matrix.data()) {\n            if (is_zero(value,\
    \ eps)) value = T();\n        }\n    }\n    return pivot_columns;\n}\n\n}  //\
    \ namespace detail\n\ntemplate <class T>\nstruct RowReduction {\n    Matrix<T>\
    \ matrix;\n    std::vector<int> pivot_columns;\n\n    int rank() const {\n   \
    \     return int(pivot_columns.size());\n    }\n};\n\ntemplate <class T>\nRowReduction<T>\
    \ reduced_row_echelon_form(Matrix<T> matrix,\n                               \
    \          T eps = default_epsilon<T>()) {\n    RowReduction<T> result;\n    result.pivot_columns\
    \ = detail::row_reduce(matrix, matrix.cols(), eps, true);\n    result.matrix =\
    \ std::move(matrix);\n    return result;\n}\n\ntemplate <class T>\nint matrix_rank(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    return int(detail::row_reduce(matrix,\
    \ matrix.cols(), eps, false).size());\n}\n\ntemplate <class T>\nT determinant(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    assert(matrix.rows() == matrix.cols());\n\
    \    const int size = matrix.rows();\n    T result = T(1);\n    bool negate =\
    \ false;\n\n    for (int col = 0; col < size; col++) {\n        int pivot = detail::choose_pivot(matrix,\
    \ col, col, eps);\n        if (pivot == -1) return T();\n        if (pivot !=\
    \ col) {\n            matrix.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        const T pivot_value = matrix[col][col];\n        result\
    \ *= pivot_value;\n        for (int row = col + 1; row < size; row++) {\n    \
    \        if (detail::is_zero(matrix[row][col], eps)) continue;\n            const\
    \ T factor = matrix[row][col] / pivot_value;\n            matrix[row][col] = T();\n\
    \            for (int j = col + 1; j < size; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[col][j];\n            }\n        }\n    }\n    return negate\
    \ ? T() - result : result;\n}\n\ntemplate <class T>\nstd::optional<Matrix<T>>\
    \ inverse(const Matrix<T>& matrix,\n                                 T eps = default_epsilon<T>())\
    \ {\n    assert(matrix.rows() == matrix.cols());\n    const int size = matrix.rows();\n\
    \    Matrix<T> augmented(size, size * 2);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) {\n            augmented[row][col]\
    \ = matrix[row][col];\n        }\n        augmented[row][size + row] = T(1);\n\
    \    }\n\n    const std::vector<int> pivots = detail::row_reduce(augmented, size,\
    \ eps, true);\n    if (int(pivots.size()) != size) return std::nullopt;\n\n  \
    \  Matrix<T> result(size, size);\n    for (int row = 0; row < size; row++) {\n\
    \        for (int col = 0; col < size; col++) {\n            result[row][col]\
    \ = augmented[row][size + col];\n        }\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nstruct LinearSystemResult {\n    bool consistent = false;\n    std::vector<T>\
    \ particular_solution;\n    std::vector<std::vector<T>> nullspace_basis;\n   \
    \ std::vector<int> pivot_columns;\n\n    int rank() const {\n        return int(pivot_columns.size());\n\
    \    }\n\n    int nullity() const {\n        return consistent ? int(nullspace_basis.size())\
    \ : 0;\n    }\n\n    bool has_unique_solution() const {\n        return consistent\
    \ && nullspace_basis.empty();\n    }\n};\n\ntemplate <class T>\nLinearSystemResult<T>\
    \ solve_linear_system(const Matrix<T>& coefficients,\n                       \
    \                   const std::vector<T>& constants,\n                       \
    \                   T eps = default_epsilon<T>()) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    Matrix<T> augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            augmented[row][col]\
    \ = coefficients[row][col];\n        }\n        augmented[row][variable_count]\
    \ = constants[std::size_t(row)];\n    }\n\n    LinearSystemResult<T> result;\n\
    \    result.pivot_columns =\n        detail::row_reduce(augmented, variable_count,\
    \ eps, true);\n\n    for (int row = result.rank(); row < equation_count; row++)\
    \ {\n        bool zero_left = true;\n        for (int col = 0; col < variable_count;\
    \ col++) {\n            if (!detail::is_zero(augmented[row][col], eps)) {\n  \
    \              zero_left = false;\n                break;\n            }\n   \
    \     }\n        if (zero_left && !detail::is_zero(augmented[row][variable_count],\
    \ eps)) {\n            return result;\n        }\n    }\n\n    result.consistent\
    \ = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ T());\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] = augmented[row][variable_count];\n\
    \    }\n\n    for (int free_col = 0; free_col < variable_count; free_col++) {\n\
    \        if (is_pivot[std::size_t(free_col)]) continue;\n        std::vector<T>\
    \ direction(static_cast<std::size_t>(variable_count));\n        direction[std::size_t(free_col)]\
    \ = T(1);\n        for (int row = 0; row < result.rank(); row++) {\n         \
    \   const int pivot_col = result.pivot_columns[std::size_t(row)];\n          \
    \  direction[std::size_t(pivot_col)] = T() - augmented[row][free_col];\n     \
    \   }\n        result.nullspace_basis.push_back(std::move(direction));\n    }\n\
    \    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n\
    #line 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 6 \"verify/math/matrix/characteristic_polynomial.test.cpp\"\
    \n\n#line 12 \"verify/math/matrix/characteristic_polynomial.test.cpp\"\n\nnamespace\
    \ {\n\nusing mint = m1une::math::modint998244353;\nusing Matrix = m1une::matrix::Matrix<mint>;\n\
    \nmint evaluate(const std::vector<mint>& polynomial, mint point) {\n    mint result\
    \ = 0;\n    for (auto iterator = polynomial.rbegin(); iterator != polynomial.rend();\
    \ ++iterator) {\n        result = result * point + *iterator;\n    }\n    return\
    \ result;\n}\n\nvoid check_by_evaluation(const Matrix& matrix, const std::vector<mint>&\
    \ polynomial) {\n    assert(polynomial.size() == std::size_t(matrix.rows() + 1));\n\
    \    assert(polynomial.back() == mint(1));\n    for (int value = -3; value <=\
    \ 3; value++) {\n        Matrix shifted = Matrix::identity(matrix.rows()) * mint(value)\
    \ - matrix;\n        assert(\n            evaluate(polynomial, mint(value)) ==\n\
    \            m1une::matrix::determinant(shifted)\n        );\n    }\n}\n\nvoid\
    \ test_edge_cases() {\n    Matrix empty(0, 0);\n    std::vector<mint> one{mint(1)};\n\
    \    assert(m1une::matrix::characteristic_polynomial(empty) == one);\n\n    Matrix\
    \ single(1, 1);\n    single[0][0] = 7;\n    std::vector<mint> expected{mint(-7),\
    \ mint(1)};\n    assert(m1une::matrix::characteristic_polynomial(single) == expected);\n\
    \n    Matrix zero(5, 5);\n    std::vector<mint> zero_polynomial(6);\n    zero_polynomial[5]\
    \ = 1;\n    assert(\n        m1une::matrix::characteristic_polynomial(zero) ==\
    \ zero_polynomial\n    );\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 0xb4ca731d9e6205f8ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 1000; trial++) {\n        const int size = int(random()\
    \ % 7);\n        Matrix matrix(size, size);\n        for (mint& value : matrix.data())\
    \ {\n            value = int(random() % 15) - 7;\n        }\n        const std::vector<mint>\
    \ polynomial =\n            m1une::matrix::characteristic_polynomial(matrix);\n\
    \        check_by_evaluation(matrix, polynomial);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_edge_cases();\n    test_randomized();\n\n    int size;\n\
    \    std::cin >> size;\n    Matrix matrix(size, size);\n    for (int row = 0;\
    \ row < size; row++) {\n        for (int col = 0; col < size; col++) {\n     \
    \       std::cin >> matrix[row][col];\n        }\n    }\n\n    const std::vector<mint>\
    \ polynomial =\n        m1une::matrix::characteristic_polynomial(std::move(matrix));\n\
    \    for (int degree = 0; degree <= size; degree++) {\n        if (degree != 0)\
    \ std::cout << ' ';\n        std::cout << polynomial[std::size_t(degree)];\n \
    \   }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n\n#include \"../../../math/matrix/characteristic_polynomial.hpp\"\n#include\
    \ \"../../../math/matrix/linear_algebra.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\n\
    using Matrix = m1une::matrix::Matrix<mint>;\n\nmint evaluate(const std::vector<mint>&\
    \ polynomial, mint point) {\n    mint result = 0;\n    for (auto iterator = polynomial.rbegin();\
    \ iterator != polynomial.rend(); ++iterator) {\n        result = result * point\
    \ + *iterator;\n    }\n    return result;\n}\n\nvoid check_by_evaluation(const\
    \ Matrix& matrix, const std::vector<mint>& polynomial) {\n    assert(polynomial.size()\
    \ == std::size_t(matrix.rows() + 1));\n    assert(polynomial.back() == mint(1));\n\
    \    for (int value = -3; value <= 3; value++) {\n        Matrix shifted = Matrix::identity(matrix.rows())\
    \ * mint(value) - matrix;\n        assert(\n            evaluate(polynomial, mint(value))\
    \ ==\n            m1une::matrix::determinant(shifted)\n        );\n    }\n}\n\n\
    void test_edge_cases() {\n    Matrix empty(0, 0);\n    std::vector<mint> one{mint(1)};\n\
    \    assert(m1une::matrix::characteristic_polynomial(empty) == one);\n\n    Matrix\
    \ single(1, 1);\n    single[0][0] = 7;\n    std::vector<mint> expected{mint(-7),\
    \ mint(1)};\n    assert(m1une::matrix::characteristic_polynomial(single) == expected);\n\
    \n    Matrix zero(5, 5);\n    std::vector<mint> zero_polynomial(6);\n    zero_polynomial[5]\
    \ = 1;\n    assert(\n        m1une::matrix::characteristic_polynomial(zero) ==\
    \ zero_polynomial\n    );\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 0xb4ca731d9e6205f8ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 1000; trial++) {\n        const int size = int(random()\
    \ % 7);\n        Matrix matrix(size, size);\n        for (mint& value : matrix.data())\
    \ {\n            value = int(random() % 15) - 7;\n        }\n        const std::vector<mint>\
    \ polynomial =\n            m1une::matrix::characteristic_polynomial(matrix);\n\
    \        check_by_evaluation(matrix, polynomial);\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_edge_cases();\n    test_randomized();\n\n    int size;\n\
    \    std::cin >> size;\n    Matrix matrix(size, size);\n    for (int row = 0;\
    \ row < size; row++) {\n        for (int col = 0; col < size; col++) {\n     \
    \       std::cin >> matrix[row][col];\n        }\n    }\n\n    const std::vector<mint>\
    \ polynomial =\n        m1une::matrix::characteristic_polynomial(std::move(matrix));\n\
    \    for (int degree = 0; degree <= size; degree++) {\n        if (degree != 0)\
    \ std::cout << ' ';\n        std::cout << polynomial[std::size_t(degree)];\n \
    \   }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - math/matrix/characteristic_polynomial.hpp
  - math/matrix/matrix.hpp
  - math/matrix/linear_algebra.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/matrix/characteristic_polynomial.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:25:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/characteristic_polynomial.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/characteristic_polynomial.test.cpp
- /verify/verify/math/matrix/characteristic_polynomial.test.cpp.html
title: verify/math/matrix/characteristic_polynomial.test.cpp
---
