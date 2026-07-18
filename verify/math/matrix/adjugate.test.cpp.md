---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/adjugate.hpp
    title: Adjugate Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/adjugate_matrix
    links:
    - https://judge.yosupo.jp/problem/adjugate_matrix
  bundledCode: "#line 1 \"verify/math/matrix/adjugate.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/adjugate_matrix\"\n\n#include <cassert>\n\
    #include <cstdint>\n\n#line 1 \"math/matrix/adjugate.hpp\"\n\n\n\n#line 5 \"math/matrix/adjugate.hpp\"\
    \n#include <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\
    \n#include <cstddef>\n#line 7 \"math/matrix/matrix.hpp\"\n#include <utility>\n\
    #line 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\n\
    template <class T>\nclass Matrix {\n   private:\n    int _rows;\n    int _cols;\n\
    \    std::vector<T> _data;\n\n    static std::size_t storage_size(int rows, int\
    \ cols) {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        return\
    \ std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n    using value_type\
    \ = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int rows, int cols,\
    \ const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
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
    \ m1une\n\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\n\n\n\n#include <optional>\n\
    #include <type_traits>\n#line 7 \"math/matrix/linear_algebra.hpp\"\n\n#line 9\
    \ \"math/matrix/linear_algebra.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\
    \ntemplate <class T>\nconstexpr T default_epsilon() {\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        return T(1e-10);\n    } else {\n        return T();\n    }\n}\n\n\
    namespace detail {\n\ntemplate <class T>\nT matrix_abs(T value) {\n    return\
    \ value < T() ? T() - value : value;\n}\n\ntemplate <class T>\nbool is_zero(const\
    \ T& value, const T& eps) {\n    if constexpr (std::is_floating_point_v<T>) {\n\
    \        return matrix_abs(value) <= eps;\n    } else {\n        (void)eps;\n\
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
    #line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
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
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cerrno>\n#include <charconv>\n#line\
    \ 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line 12\
    \ \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include\
    \ <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\
    \n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/math/matrix/adjugate.test.cpp\"\
    \n\nnamespace {\n\nusing Mint = m1une::math::modint998244353;\nusing Matrix =\
    \ m1une::matrix::Matrix<Mint>;\n\nMatrix naive_adjugate(const Matrix& matrix)\
    \ {\n    const int size = matrix.rows();\n    Matrix result(size, size);\n   \
    \ for (int row = 0; row < size; row++) {\n        for (int col = 0; col < size;\
    \ col++) {\n            Matrix minor(size - 1, size - 1);\n            int minor_row\
    \ = 0;\n            for (int source_row = 0; source_row < size; source_row++)\
    \ {\n                if (source_row == col) continue;\n                int minor_col\
    \ = 0;\n                for (int source_col = 0; source_col < size; source_col++)\
    \ {\n                    if (source_col == row) continue;\n                  \
    \  minor[minor_row][minor_col++] = matrix[source_row][source_col];\n         \
    \       }\n                minor_row++;\n            }\n            result[row][col]\
    \ = m1une::matrix::determinant(std::move(minor));\n            if ((row + col)\
    \ & 1) result[row][col] = Mint(0) - result[row][col];\n        }\n    }\n    return\
    \ result;\n}\n\nstd::uint64_t next_random(std::uint64_t& state) {\n    state ^=\
    \ state << 7;\n    state ^= state >> 9;\n    return state;\n}\n\nvoid check(const\
    \ Matrix& matrix) {\n    const Matrix actual = m1une::matrix::adjugate(matrix);\n\
    \    assert(actual == naive_adjugate(matrix));\n    const Mint determinant = m1une::matrix::determinant(matrix);\n\
    \    const Matrix expected = Matrix::identity(matrix.rows()) * determinant;\n\
    \    assert(matrix * actual == expected);\n    assert(actual * matrix == expected);\n\
    }\n\nvoid focused_tests() {\n    check(Matrix(0, 0));\n    check(Matrix(1, 1));\n\
    \    Matrix scalar(1, 1);\n    scalar[0][0] = 17;\n    check(scalar);\n\n    Matrix\
    \ rank_one(5, 5);\n    for (int row = 0; row < 5; row++) {\n        for (int col\
    \ = 0; col < 5; col++) rank_one[row][col] = (row + 1) * (col + 3);\n    }\n  \
    \  check(rank_one);\n\n    std::uint64_t random = 0x4c38d91bea75260fULL;\n   \
    \ for (int iteration = 0; iteration < 250; iteration++) {\n        const int size\
    \ = int(next_random(random) % 8);\n        Matrix matrix(size, size);\n      \
    \  for (Mint& value : matrix.data()) {\n            value = int(next_random(random)\
    \ % 21) - 10;\n        }\n        check(matrix);\n    }\n\n    for (int size =\
    \ 2; size <= 7; size++) {\n        for (int iteration = 0; iteration < 30; iteration++)\
    \ {\n            Matrix matrix = Matrix::identity(size);\n            matrix[size\
    \ - 1][size - 1] = Mint(0);\n            for (int operation = 0; operation < size\
    \ * 4; operation++) {\n                int first = int(next_random(random) % size);\n\
    \                int second = int(next_random(random) % size);\n             \
    \   if (first == second) second = (second + 1) % size;\n                const\
    \ Mint factor = Mint(1 + next_random(random) % 20);\n                for (int\
    \ col = 0; col < size; col++) {\n                    matrix[first][col] += factor\
    \ * matrix[second][col];\n                }\n\n                first = int(next_random(random)\
    \ % size);\n                second = int(next_random(random) % size);\n      \
    \          if (first == second) second = (second + 1) % size;\n              \
    \  for (int row = 0; row < size; row++) {\n                    matrix[row][first]\
    \ += factor * matrix[row][second];\n                }\n            }\n       \
    \     check(matrix);\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    focused_tests();\n\n    int size;\n    input >> size;\n    Matrix matrix(size,\
    \ size);\n    for (Mint& value : matrix.data()) input >> value;\n    const Matrix\
    \ result = m1une::matrix::adjugate(std::move(matrix));\n    for (int row = 0;\
    \ row < size; row++) {\n        for (int col = 0; col < size; col++) {\n     \
    \       if (col != 0) output << ' ';\n            output << result[row][col];\n\
    \        }\n        output << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/adjugate_matrix\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n\n#include \"../../../math/matrix/adjugate.hpp\"\
    \n#include \"../../../math/matrix/linear_algebra.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\nnamespace {\n\nusing Mint = m1une::math::modint998244353;\n\
    using Matrix = m1une::matrix::Matrix<Mint>;\n\nMatrix naive_adjugate(const Matrix&\
    \ matrix) {\n    const int size = matrix.rows();\n    Matrix result(size, size);\n\
    \    for (int row = 0; row < size; row++) {\n        for (int col = 0; col < size;\
    \ col++) {\n            Matrix minor(size - 1, size - 1);\n            int minor_row\
    \ = 0;\n            for (int source_row = 0; source_row < size; source_row++)\
    \ {\n                if (source_row == col) continue;\n                int minor_col\
    \ = 0;\n                for (int source_col = 0; source_col < size; source_col++)\
    \ {\n                    if (source_col == row) continue;\n                  \
    \  minor[minor_row][minor_col++] = matrix[source_row][source_col];\n         \
    \       }\n                minor_row++;\n            }\n            result[row][col]\
    \ = m1une::matrix::determinant(std::move(minor));\n            if ((row + col)\
    \ & 1) result[row][col] = Mint(0) - result[row][col];\n        }\n    }\n    return\
    \ result;\n}\n\nstd::uint64_t next_random(std::uint64_t& state) {\n    state ^=\
    \ state << 7;\n    state ^= state >> 9;\n    return state;\n}\n\nvoid check(const\
    \ Matrix& matrix) {\n    const Matrix actual = m1une::matrix::adjugate(matrix);\n\
    \    assert(actual == naive_adjugate(matrix));\n    const Mint determinant = m1une::matrix::determinant(matrix);\n\
    \    const Matrix expected = Matrix::identity(matrix.rows()) * determinant;\n\
    \    assert(matrix * actual == expected);\n    assert(actual * matrix == expected);\n\
    }\n\nvoid focused_tests() {\n    check(Matrix(0, 0));\n    check(Matrix(1, 1));\n\
    \    Matrix scalar(1, 1);\n    scalar[0][0] = 17;\n    check(scalar);\n\n    Matrix\
    \ rank_one(5, 5);\n    for (int row = 0; row < 5; row++) {\n        for (int col\
    \ = 0; col < 5; col++) rank_one[row][col] = (row + 1) * (col + 3);\n    }\n  \
    \  check(rank_one);\n\n    std::uint64_t random = 0x4c38d91bea75260fULL;\n   \
    \ for (int iteration = 0; iteration < 250; iteration++) {\n        const int size\
    \ = int(next_random(random) % 8);\n        Matrix matrix(size, size);\n      \
    \  for (Mint& value : matrix.data()) {\n            value = int(next_random(random)\
    \ % 21) - 10;\n        }\n        check(matrix);\n    }\n\n    for (int size =\
    \ 2; size <= 7; size++) {\n        for (int iteration = 0; iteration < 30; iteration++)\
    \ {\n            Matrix matrix = Matrix::identity(size);\n            matrix[size\
    \ - 1][size - 1] = Mint(0);\n            for (int operation = 0; operation < size\
    \ * 4; operation++) {\n                int first = int(next_random(random) % size);\n\
    \                int second = int(next_random(random) % size);\n             \
    \   if (first == second) second = (second + 1) % size;\n                const\
    \ Mint factor = Mint(1 + next_random(random) % 20);\n                for (int\
    \ col = 0; col < size; col++) {\n                    matrix[first][col] += factor\
    \ * matrix[second][col];\n                }\n\n                first = int(next_random(random)\
    \ % size);\n                second = int(next_random(random) % size);\n      \
    \          if (first == second) second = (second + 1) % size;\n              \
    \  for (int row = 0; row < size; row++) {\n                    matrix[row][first]\
    \ += factor * matrix[row][second];\n                }\n            }\n       \
    \     check(matrix);\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    focused_tests();\n\n    int size;\n    input >> size;\n    Matrix matrix(size,\
    \ size);\n    for (Mint& value : matrix.data()) input >> value;\n    const Matrix\
    \ result = m1une::matrix::adjugate(std::move(matrix));\n    for (int row = 0;\
    \ row < size; row++) {\n        for (int col = 0; col < size; col++) {\n     \
    \       if (col != 0) output << ' ';\n            output << result[row][col];\n\
    \        }\n        output << '\\n';\n    }\n}\n"
  dependsOn:
  - math/matrix/adjugate.hpp
  - math/matrix/matrix.hpp
  - math/matrix/linear_algebra.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/matrix/adjugate.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/adjugate.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/adjugate.test.cpp
- /verify/verify/math/matrix/adjugate.test.cpp.html
title: verify/math/matrix/adjugate.test.cpp
---
