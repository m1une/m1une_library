---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/sparse_determinant.hpp
    title: Sparse Determinant
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
    PROBLEM: https://judge.yosupo.jp/problem/sparse_matrix_det
    links:
    - https://judge.yosupo.jp/problem/sparse_matrix_det
  bundledCode: "#line 1 \"verify/math/matrix/sparse_determinant.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n#line 1 \"\
    math/matrix/linear_algebra.hpp\"\n\n\n\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <cstdint>\n#include <utility>\n#line 9 \"math/matrix/matrix.hpp\"\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/linear_algebra.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nconstexpr T default_epsilon()\
    \ {\n    if constexpr (std::is_floating_point_v<T>) {\n        return T(1e-10);\n\
    \    } else {\n        return T();\n    }\n}\n\nnamespace detail {\n\ntemplate\
    \ <class T>\nT matrix_abs(T value) {\n    return value < T() ? T() - value : value;\n\
    }\n\ntemplate <class T>\nbool is_zero(const T& value, const T& eps) {\n    if\
    \ constexpr (std::is_floating_point_v<T>) {\n        return matrix_abs(value)\
    \ <= eps;\n    } else {\n        (void)eps;\n        return value == T();\n  \
    \  }\n}\n\ntemplate <class T>\nint choose_pivot(const Matrix<T>& matrix, int first_row,\
    \ int col, const T& eps) {\n    int pivot = -1;\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (int row = first_row; row < matrix.rows(); row++) {\n       \
    \     if (is_zero(matrix[row][col], eps)) continue;\n            if (pivot ==\
    \ -1 || matrix_abs(matrix[pivot][col]) < matrix_abs(matrix[row][col])) {\n   \
    \             pivot = row;\n            }\n        }\n    } else {\n        for\
    \ (int row = first_row; row < matrix.rows(); row++) {\n            if (!is_zero(matrix[row][col],\
    \ eps)) {\n                pivot = row;\n                break;\n            }\n\
    \        }\n    }\n    return pivot;\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ row_reduce(Matrix<T>& matrix, int pivot_col_limit, const T& eps,\n         \
    \                   bool reduced) {\n    std::vector<int> pivot_columns;\n   \
    \ int pivot_row = 0;\n    for (int col = 0; col < pivot_col_limit && pivot_row\
    \ < matrix.rows(); col++) {\n        int pivot = choose_pivot(matrix, pivot_row,\
    \ col, eps);\n        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row,\
    \ pivot);\n\n        const T pivot_value = matrix[pivot_row][col];\n        if\
    \ (reduced) {\n            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j]\
    \ /= pivot_value;\n        }\n\n        const int first_row = reduced ? 0 : pivot_row\
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
    #line 1 \"math/matrix/sparse_determinant.hpp\"\n\n\n\n#line 8 \"math/matrix/sparse_determinant.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nstruct SparseMatrixEntry\
    \ {\n    int row;\n    int col;\n    T value;\n};\n\nnamespace internal {\n\n\
    struct SparseDeterminantRandom {\n    std::uint64_t state;\n\n    explicit SparseDeterminantRandom(std::uint64_t\
    \ seed) : state(seed) {}\n\n    std::uint64_t operator()() {\n        std::uint64_t\
    \ value = (state += 0x9e3779b97f4a7c15ULL);\n        value = (value ^ (value >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return value ^ (value >> 31);\n    }\n};\n\ntemplate <class T>\nstd::vector<T>\
    \ berlekamp_massey(const std::vector<T>& sequence) {\n    std::vector<T> recurrence(1,\
    \ T(1));\n    std::vector<T> previous(1, T(1));\n    int degree = 0;\n    int\
    \ shift = 1;\n    T previous_discrepancy = T(1);\n\n    for (int index = 0; index\
    \ < int(sequence.size()); index++) {\n        T discrepancy = sequence[index];\n\
    \        for (int i = 1; i <= degree; i++) {\n            discrepancy += recurrence[i]\
    \ * sequence[index - i];\n        }\n        if (discrepancy == T()) {\n     \
    \       shift++;\n            continue;\n        }\n\n        const T factor =\
    \ discrepancy / previous_discrepancy;\n        std::vector<T> old_recurrence =\
    \ recurrence;\n        if (int(recurrence.size()) < int(previous.size()) + shift)\
    \ {\n            recurrence.resize(previous.size() + std::size_t(shift), T());\n\
    \        }\n        for (int i = 0; i < int(previous.size()); i++) {\n       \
    \     recurrence[i + shift] -= factor * previous[i];\n        }\n\n        if\
    \ (2 * degree <= index) {\n            degree = index + 1 - degree;\n        \
    \    previous = std::move(old_recurrence);\n            previous_discrepancy =\
    \ discrepancy;\n            shift = 1;\n        } else {\n            shift++;\n\
    \        }\n    }\n    recurrence.resize(std::size_t(degree + 1));\n    return\
    \ recurrence;\n}\n\n}  // namespace internal\n\n// Randomized black-box determinant\
    \ over a finite field. random_nonzero must\n// return independent nonzero field\
    \ elements.\ntemplate <class T, class RandomValue>\nT sparse_determinant_with_randomizer(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    RandomValue\
    \ random_nonzero\n) {\n    assert(size >= 0);\n    for (const SparseMatrixEntry<T>&\
    \ entry : entries) {\n        assert(0 <= entry.row && entry.row < size);\n  \
    \      assert(0 <= entry.col && entry.col < size);\n    }\n    if (size == 0)\
    \ return T(1);\n\n    auto random_vector = [&]() {\n        std::vector<T> result(size);\n\
    \        for (T& value : result) {\n            value = random_nonzero();\n  \
    \          assert(value != T());\n        }\n        return result;\n    };\n\n\
    \    while (true) {\n        std::vector<T> diagonal = random_vector();\n    \
    \    std::vector<T> left = random_vector();\n        std::vector<T> state = random_vector();\n\
    \        std::vector<T> sequence(std::size_t(2 * size));\n\n        for (int step\
    \ = 0; step < 2 * size; step++) {\n            for (int i = 0; i < size; i++)\
    \ sequence[step] += left[i] * state[i];\n            for (int i = 0; i < size;\
    \ i++) state[i] *= diagonal[i];\n\n            std::vector<T> next(size);\n  \
    \          for (const SparseMatrixEntry<T>& entry : entries) {\n             \
    \   next[entry.row] += entry.value * state[entry.col];\n            }\n      \
    \      state = std::move(next);\n        }\n\n        std::vector<T> recurrence\
    \ = internal::berlekamp_massey(sequence);\n        if (recurrence.back() == T())\
    \ return T();\n        if (int(recurrence.size()) != size + 1) continue;\n\n \
    \       T determinant = recurrence.back();\n        if (size % 2 == 1) determinant\
    \ = T() - determinant;\n        for (const T& value : diagonal) determinant /=\
    \ value;\n        return determinant;\n    }\n}\n\ntemplate <class T>\nT sparse_determinant(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    std::uint64_t\
    \ seed = 0x243f6a8885a308d3ULL\n) {\n    const std::uint64_t modulus = T::mod();\n\
    \    assert(modulus > 1);\n    internal::SparseDeterminantRandom random(seed);\n\
    \    auto random_nonzero = [&]() {\n        return T(1 + random() % (modulus -\
    \ 1));\n    };\n    return sparse_determinant_with_randomizer<T>(size, entries,\
    \ random_nonzero);\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
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
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 6 \"verify/math/matrix/sparse_determinant.test.cpp\"\n\n#line 11 \"\
    verify/math/matrix/sparse_determinant.test.cpp\"\n\nnamespace {\n\nusing mint\
    \ = m1une::math::modint998244353;\nusing Entry = m1une::matrix::SparseMatrixEntry<mint>;\n\
    using Matrix = m1une::matrix::Matrix<mint>;\n\nmint dense_determinant(int size,\
    \ const std::vector<Entry>& entries) {\n    Matrix matrix(size, size);\n    for\
    \ (const Entry& entry : entries) matrix[entry.row][entry.col] += entry.value;\n\
    \    return m1une::matrix::determinant(std::move(matrix));\n}\n\nvoid validate(int\
    \ size, const std::vector<Entry>& entries, std::uint64_t seed) {\n    mint expected\
    \ = dense_determinant(size, entries);\n    mint actual = m1une::matrix::sparse_determinant(size,\
    \ entries, seed);\n    assert(actual == expected);\n}\n\nvoid test_edge_cases()\
    \ {\n    validate(0, {}, 1);\n    validate(4, {}, 2);\n\n    std::vector<Entry>\
    \ identity;\n    for (int i = 0; i < 7; i++) identity.push_back(Entry{i, i, mint(1)});\n\
    \    validate(7, identity, 3);\n\n    std::vector<Entry> singular;\n    singular.push_back(Entry{0,\
    \ 0, mint(2)});\n    singular.push_back(Entry{0, 1, mint(3)});\n    singular.push_back(Entry{1,\
    \ 0, mint(2)});\n    singular.push_back(Entry{1, 1, mint(3)});\n    validate(2,\
    \ singular, 4);\n\n    std::vector<Entry> permutation;\n    permutation.push_back(Entry{0,\
    \ 1, mint(1)});\n    permutation.push_back(Entry{1, 2, mint(1)});\n    permutation.push_back(Entry{2,\
    \ 0, mint(1)});\n    validate(3, permutation, 5);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x94d049bb133111ebULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        int\
    \ size = int(random() % 9);\n        std::vector<Entry> entries;\n        for\
    \ (int row = 0; row < size; row++) {\n            for (int col = 0; col < size;\
    \ col++) {\n                if (random() % 3 == 0) continue;\n               \
    \ entries.push_back(Entry{row, col, mint(int(random() % 17) - 8)});\n        \
    \        if (random() % 7 == 0) {\n                    entries.push_back(Entry{row,\
    \ col, mint(int(random() % 11) - 5)});\n                }\n            }\n   \
    \     }\n        validate(size, entries, random());\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_edge_cases();\n    test_randomized();\n\n    int size,\
    \ entry_count;\n    std::cin >> size >> entry_count;\n    std::vector<Entry> entries;\n\
    \    entries.reserve(entry_count);\n    while (entry_count--) {\n        int row,\
    \ col;\n        mint value;\n        std::cin >> row >> col >> value;\n      \
    \  entries.push_back(Entry{row, col, value});\n    }\n    std::cout << m1une::matrix::sparse_determinant(size,\
    \ entries) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sparse_matrix_det\"\n\n\
    #include \"../../../math/matrix/linear_algebra.hpp\"\n#include \"../../../math/matrix/sparse_determinant.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <vector>\n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\n\
    using Entry = m1une::matrix::SparseMatrixEntry<mint>;\nusing Matrix = m1une::matrix::Matrix<mint>;\n\
    \nmint dense_determinant(int size, const std::vector<Entry>& entries) {\n    Matrix\
    \ matrix(size, size);\n    for (const Entry& entry : entries) matrix[entry.row][entry.col]\
    \ += entry.value;\n    return m1une::matrix::determinant(std::move(matrix));\n\
    }\n\nvoid validate(int size, const std::vector<Entry>& entries, std::uint64_t\
    \ seed) {\n    mint expected = dense_determinant(size, entries);\n    mint actual\
    \ = m1une::matrix::sparse_determinant(size, entries, seed);\n    assert(actual\
    \ == expected);\n}\n\nvoid test_edge_cases() {\n    validate(0, {}, 1);\n    validate(4,\
    \ {}, 2);\n\n    std::vector<Entry> identity;\n    for (int i = 0; i < 7; i++)\
    \ identity.push_back(Entry{i, i, mint(1)});\n    validate(7, identity, 3);\n\n\
    \    std::vector<Entry> singular;\n    singular.push_back(Entry{0, 0, mint(2)});\n\
    \    singular.push_back(Entry{0, 1, mint(3)});\n    singular.push_back(Entry{1,\
    \ 0, mint(2)});\n    singular.push_back(Entry{1, 1, mint(3)});\n    validate(2,\
    \ singular, 4);\n\n    std::vector<Entry> permutation;\n    permutation.push_back(Entry{0,\
    \ 1, mint(1)});\n    permutation.push_back(Entry{1, 2, mint(1)});\n    permutation.push_back(Entry{2,\
    \ 0, mint(1)});\n    validate(3, permutation, 5);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x94d049bb133111ebULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        int\
    \ size = int(random() % 9);\n        std::vector<Entry> entries;\n        for\
    \ (int row = 0; row < size; row++) {\n            for (int col = 0; col < size;\
    \ col++) {\n                if (random() % 3 == 0) continue;\n               \
    \ entries.push_back(Entry{row, col, mint(int(random() % 17) - 8)});\n        \
    \        if (random() % 7 == 0) {\n                    entries.push_back(Entry{row,\
    \ col, mint(int(random() % 11) - 5)});\n                }\n            }\n   \
    \     }\n        validate(size, entries, random());\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_edge_cases();\n    test_randomized();\n\n    int size,\
    \ entry_count;\n    std::cin >> size >> entry_count;\n    std::vector<Entry> entries;\n\
    \    entries.reserve(entry_count);\n    while (entry_count--) {\n        int row,\
    \ col;\n        mint value;\n        std::cin >> row >> col >> value;\n      \
    \  entries.push_back(Entry{row, col, value});\n    }\n    std::cout << m1une::matrix::sparse_determinant(size,\
    \ entries) << '\\n';\n}\n"
  dependsOn:
  - math/matrix/linear_algebra.hpp
  - math/matrix/matrix.hpp
  - math/matrix/sparse_determinant.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/matrix/sparse_determinant.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:42:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/sparse_determinant.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/sparse_determinant.test.cpp
- /verify/verify/math/matrix/sparse_determinant.test.cpp.html
title: verify/math/matrix/sparse_determinant.test.cpp
---
