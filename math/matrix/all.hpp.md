---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/bit_matrix.hpp
    title: Bit Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/characteristic_polynomial.hpp
    title: Characteristic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/matrix/hafnian.hpp
    title: Hafnian
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/pfaffian.hpp
    title: Pfaffian
  - icon: ':heavy_check_mark:'
    path: math/matrix/sparse_determinant.hpp
    title: Sparse Determinant
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/all.hpp\"\n\n\n\n#line 1 \"math/matrix/bit_matrix.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <optional>\n#include <string>\n#include <string_view>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace matrix {\n\
    \nclass BitMatrix {\n   private:\n    int _rows;\n    int _cols;\n    int _blocks;\n\
    \    std::vector<std::uint64_t> _data;\n\n    static int block_count(int cols)\
    \ {\n        assert(cols >= 0);\n        return (cols + 63) / 64;\n    }\n\n \
    \   static std::size_t storage_size(int rows, int blocks) {\n        assert(rows\
    \ >= 0);\n        return std::size_t(rows) * std::size_t(blocks);\n    }\n\n \
    \   std::size_t word_index(int row, int col) const {\n        assert(0 <= row\
    \ && row < _rows);\n        assert(0 <= col && col < _cols);\n        return std::size_t(row)\
    \ * std::size_t(_blocks) +\n               std::size_t(col / 64);\n    }\n\n \
    \   std::uint64_t trailing_mask() const {\n        if ((_cols & 63) == 0) return\
    \ ~std::uint64_t(0);\n        return (std::uint64_t(1) << (_cols & 63)) - 1;\n\
    \    }\n\n   public:\n    class BitReference {\n       private:\n        std::uint64_t*\
    \ word;\n        std::uint64_t mask;\n\n       public:\n        BitReference(std::uint64_t&\
    \ word_value, std::uint64_t mask_value)\n            : word(&word_value), mask(mask_value)\
    \ {}\n\n        operator bool() const {\n            return (*word & mask) !=\
    \ 0;\n        }\n\n        BitReference& operator=(bool value) {\n           \
    \ if (value) {\n                *word |= mask;\n            } else {\n       \
    \         *word &= ~mask;\n            }\n            return *this;\n        }\n\
    \n        BitReference& operator=(const BitReference& other) {\n            return\
    \ *this = bool(other);\n        }\n\n        void flip() {\n            *word\
    \ ^= mask;\n        }\n    };\n\n    class RowReference {\n       private:\n \
    \       BitMatrix* matrix;\n        int row;\n\n       public:\n        RowReference(BitMatrix&\
    \ matrix_value, int row_value)\n            : matrix(&matrix_value), row(row_value)\
    \ {}\n\n        BitReference operator[](int col) const {\n            return (*matrix)(row,\
    \ col);\n        }\n    };\n\n    class ConstRowReference {\n       private:\n\
    \        const BitMatrix* matrix;\n        int row;\n\n       public:\n      \
    \  ConstRowReference(const BitMatrix& matrix_value, int row_value)\n         \
    \   : matrix(&matrix_value), row(row_value) {}\n\n        bool operator[](int\
    \ col) const {\n            return (*matrix)(row, col);\n        }\n    };\n\n\
    \    BitMatrix() : _rows(0), _cols(0), _blocks(0) {}\n\n    BitMatrix(int rows,\
    \ int cols, bool value = false)\n        : _rows(rows),\n          _cols(cols),\n\
    \          _blocks(block_count(cols)),\n          _data(\n              storage_size(rows,\
    \ _blocks),\n              value ? ~std::uint64_t(0) : std::uint64_t(0)\n    \
    \      ) {\n        assert(rows >= 0);\n        if (value && _blocks > 0) {\n\
    \            const std::uint64_t mask = trailing_mask();\n            for (int\
    \ row = 0; row < _rows; row++) {\n                _data[\n                   \
    \ std::size_t(row + 1) * std::size_t(_blocks) - 1\n                ] &= mask;\n\
    \            }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n\
    \    }\n\n    int cols() const {\n        return _cols;\n    }\n\n    int blocks_per_row()\
    \ const {\n        return _blocks;\n    }\n\n    bool empty() const {\n      \
    \  return _rows == 0 || _cols == 0;\n    }\n\n    RowReference operator[](int\
    \ row) {\n        assert(0 <= row && row < _rows);\n        return RowReference(*this,\
    \ row);\n    }\n\n    ConstRowReference operator[](int row) const {\n        assert(0\
    \ <= row && row < _rows);\n        return ConstRowReference(*this, row);\n   \
    \ }\n\n    BitReference operator()(int row, int col) {\n        const std::size_t\
    \ index = word_index(row, col);\n        return BitReference(_data[index], std::uint64_t(1)\
    \ << (col & 63));\n    }\n\n    bool operator()(int row, int col) const {\n  \
    \      const std::size_t index = word_index(row, col);\n        return (_data[index]\
    \ >> (col & 63)) & 1;\n    }\n\n    bool get(int row, int col) const {\n     \
    \   return (*this)(row, col);\n    }\n\n    void set(int row, int col, bool value\
    \ = true) {\n        (*this)(row, col) = value;\n    }\n\n    void reset(int row,\
    \ int col) {\n        set(row, col, false);\n    }\n\n    void flip(int row, int\
    \ col) {\n        (*this)(row, col).flip();\n    }\n\n    void clear() {\n   \
    \     std::fill(_data.begin(), _data.end(), std::uint64_t(0));\n    }\n\n    void\
    \ set_row(int row, std::string_view bits) {\n        assert(0 <= row && row <\
    \ _rows);\n        assert(int(bits.size()) == _cols);\n        const std::size_t\
    \ offset =\n            std::size_t(row) * std::size_t(_blocks);\n        std::fill(\n\
    \            _data.begin() + std::ptrdiff_t(offset),\n            _data.begin()\
    \ + std::ptrdiff_t(offset + std::size_t(_blocks)),\n            std::uint64_t(0)\n\
    \        );\n        for (int col = 0; col < _cols; col++) {\n            assert(bits[std::size_t(col)]\
    \ == '0' || bits[std::size_t(col)] == '1');\n            if (bits[std::size_t(col)]\
    \ == '1') set(row, col);\n        }\n    }\n\n    std::string row_string(int row)\
    \ const {\n        assert(0 <= row && row < _rows);\n        std::string result(std::size_t(_cols),\
    \ '0');\n        for (int col = 0; col < _cols; col++) {\n            if (get(row,\
    \ col)) result[std::size_t(col)] = '1';\n        }\n        return result;\n \
    \   }\n\n    static BitMatrix identity(int size) {\n        assert(size >= 0);\n\
    \        BitMatrix result(size, size);\n        for (int index = 0; index < size;\
    \ index++) result.set(index, index);\n        return result;\n    }\n\n    BitMatrix\
    \ transposed() const {\n        BitMatrix result(_cols, _rows);\n        for (int\
    \ row = 0; row < _rows; row++) {\n            for (int col = 0; col < _cols; col++)\
    \ {\n                if (get(row, col)) result.set(col, row);\n            }\n\
    \        }\n        return result;\n    }\n\n    void swap_rows(int first, int\
    \ second) {\n        assert(0 <= first && first < _rows);\n        assert(0 <=\
    \ second && second < _rows);\n        if (first == second) return;\n        const\
    \ std::size_t first_offset =\n            std::size_t(first) * std::size_t(_blocks);\n\
    \        const std::size_t second_offset =\n            std::size_t(second) *\
    \ std::size_t(_blocks);\n        for (int block = 0; block < _blocks; block++)\
    \ {\n            std::swap(\n                _data[first_offset + std::size_t(block)],\n\
    \                _data[second_offset + std::size_t(block)]\n            );\n \
    \       }\n    }\n\n    void xor_rows(int target, int source, int first_col =\
    \ 0) {\n        assert(0 <= target && target < _rows);\n        assert(0 <= source\
    \ && source < _rows);\n        assert(0 <= first_col && first_col <= _cols);\n\
    \        if (first_col == _cols) return;\n        const std::size_t target_offset\
    \ =\n            std::size_t(target) * std::size_t(_blocks);\n        const std::size_t\
    \ source_offset =\n            std::size_t(source) * std::size_t(_blocks);\n \
    \       const int first_block = first_col / 64;\n        const int first_bit =\
    \ first_col & 63;\n        if (first_bit != 0) {\n            const std::uint64_t\
    \ mask = ~std::uint64_t(0) << first_bit;\n            _data[target_offset + std::size_t(first_block)]\
    \ ^=\n                _data[source_offset + std::size_t(first_block)] & mask;\n\
    \        } else {\n            _data[target_offset + std::size_t(first_block)]\
    \ ^=\n                _data[source_offset + std::size_t(first_block)];\n     \
    \   }\n        for (int block = first_block + 1; block < _blocks; block++) {\n\
    \            _data[target_offset + std::size_t(block)] ^=\n                _data[source_offset\
    \ + std::size_t(block)];\n        }\n    }\n\n    BitMatrix& operator^=(const\
    \ BitMatrix& rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n\
    \        for (std::size_t index = 0; index < _data.size(); index++) {\n      \
    \      _data[index] ^= rhs._data[index];\n        }\n        return *this;\n \
    \   }\n\n    BitMatrix& operator+=(const BitMatrix& rhs) {\n        return *this\
    \ ^= rhs;\n    }\n\n    BitMatrix& operator-=(const BitMatrix& rhs) {\n      \
    \  return *this ^= rhs;\n    }\n\n    BitMatrix& operator*=(const BitMatrix& rhs)\
    \ {\n        return *this = *this * rhs;\n    }\n\n    friend BitMatrix operator^(BitMatrix\
    \ lhs, const BitMatrix& rhs) {\n        return lhs ^= rhs;\n    }\n\n    friend\
    \ BitMatrix operator+(BitMatrix lhs, const BitMatrix& rhs) {\n        return lhs\
    \ += rhs;\n    }\n\n    friend BitMatrix operator-(BitMatrix lhs, const BitMatrix&\
    \ rhs) {\n        return lhs -= rhs;\n    }\n\n    friend BitMatrix operator*(const\
    \ BitMatrix& lhs, const BitMatrix& rhs) {\n        assert(lhs._cols == rhs._rows);\n\
    \        BitMatrix result(lhs._rows, rhs._cols);\n        for (int row = 0; row\
    \ < lhs._rows; row++) {\n            const std::size_t lhs_offset =\n        \
    \        std::size_t(row) * std::size_t(lhs._blocks);\n            const std::size_t\
    \ result_offset =\n                std::size_t(row) * std::size_t(result._blocks);\n\
    \            for (int lhs_block = 0; lhs_block < lhs._blocks; lhs_block++) {\n\
    \                std::uint64_t word =\n                    lhs._data[lhs_offset\
    \ + std::size_t(lhs_block)];\n                while (word != 0) {\n          \
    \          const int bit = std::countr_zero(word);\n                    const\
    \ int middle = lhs_block * 64 + bit;\n                    const std::size_t rhs_offset\
    \ =\n                        std::size_t(middle) * std::size_t(rhs._blocks);\n\
    \                    for (int block = 0; block < rhs._blocks; block++) {\n   \
    \                     result._data[result_offset + std::size_t(block)] ^=\n  \
    \                          rhs._data[rhs_offset + std::size_t(block)];\n     \
    \               }\n                    word &= word - 1;\n                }\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ BitMatrix& rhs) const {\n        return\n            _rows == rhs._rows && _cols\
    \ == rhs._cols && _data == rhs._data;\n    }\n\n    bool operator!=(const BitMatrix&\
    \ rhs) const {\n        return !(*this == rhs);\n    }\n\n    BitMatrix pow(std::uint64_t\
    \ exponent) const {\n        assert(_rows == _cols);\n        BitMatrix result\
    \ = identity(_rows);\n        BitMatrix base = *this;\n        while (exponent\
    \ > 0) {\n            if (exponent & 1) result *= base;\n            exponent\
    \ >>= 1;\n            if (exponent > 0) base *= base;\n        }\n        return\
    \ result;\n    }\n};\n\nnamespace bit_matrix_detail {\n\ninline std::vector<int>\
    \ row_reduce(\n    BitMatrix& matrix,\n    int pivot_col_limit,\n    bool reduced\n\
    ) {\n    assert(0 <= pivot_col_limit && pivot_col_limit <= matrix.cols());\n \
    \   std::vector<int> pivot_columns;\n    int pivot_row = 0;\n    for (\n     \
    \   int col = 0;\n        col < pivot_col_limit && pivot_row < matrix.rows();\n\
    \        col++\n    ) {\n        int pivot = -1;\n        for (int row = pivot_row;\
    \ row < matrix.rows(); row++) {\n            if (matrix.get(row, col)) {\n   \
    \             pivot = row;\n                break;\n            }\n        }\n\
    \        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row, pivot);\n\
    \n        const int first_row = reduced ? 0 : pivot_row + 1;\n        for (int\
    \ row = first_row; row < matrix.rows(); row++) {\n            if (row != pivot_row\
    \ && matrix.get(row, col)) {\n                matrix.xor_rows(row, pivot_row,\
    \ col);\n            }\n        }\n        pivot_columns.push_back(col);\n   \
    \     pivot_row++;\n    }\n    return pivot_columns;\n}\n\n}  // namespace bit_matrix_detail\n\
    \nstruct BitRowReduction {\n    BitMatrix matrix;\n    std::vector<int> pivot_columns;\n\
    \n    int rank() const {\n        return int(pivot_columns.size());\n    }\n};\n\
    \ninline BitRowReduction reduced_row_echelon_form(BitMatrix matrix) {\n    BitRowReduction\
    \ result;\n    result.pivot_columns = bit_matrix_detail::row_reduce(\n       \
    \ matrix,\n        matrix.cols(),\n        true\n    );\n    result.matrix = std::move(matrix);\n\
    \    return result;\n}\n\ninline int matrix_rank(BitMatrix matrix) {\n    if (matrix.rows()\
    \ > matrix.cols()) matrix = matrix.transposed();\n    return int(bit_matrix_detail::row_reduce(\n\
    \        matrix,\n        matrix.cols(),\n        false\n    ).size());\n}\n\n\
    inline bool determinant(const BitMatrix& matrix) {\n    assert(matrix.rows() ==\
    \ matrix.cols());\n    return matrix_rank(matrix) == matrix.rows();\n}\n\ninline\
    \ std::optional<BitMatrix> inverse(const BitMatrix& matrix) {\n    assert(matrix.rows()\
    \ == matrix.cols());\n    const int size = matrix.rows();\n    BitMatrix augmented(size,\
    \ 2 * size);\n    for (int row = 0; row < size; row++) {\n        for (int col\
    \ = 0; col < size; col++) {\n            if (matrix.get(row, col)) augmented.set(row,\
    \ col);\n        }\n        augmented.set(row, size + row);\n    }\n\n    const\
    \ std::vector<int> pivots = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        size,\n        true\n    );\n    if (int(pivots.size()) != size) return\
    \ std::nullopt;\n\n    BitMatrix result(size, size);\n    for (int row = 0; row\
    \ < size; row++) {\n        for (int col = 0; col < size; col++) {\n         \
    \   if (augmented.get(row, size + col)) result.set(row, col);\n        }\n   \
    \ }\n    return result;\n}\n\nstruct BitLinearSystemResult {\n    bool consistent\
    \ = false;\n    std::vector<bool> particular_solution;\n    std::vector<std::vector<bool>>\
    \ nullspace_basis;\n    std::vector<int> pivot_columns;\n\n    int rank() const\
    \ {\n        return int(pivot_columns.size());\n    }\n\n    int nullity() const\
    \ {\n        return consistent ? int(nullspace_basis.size()) : 0;\n    }\n\n \
    \   bool has_unique_solution() const {\n        return consistent && nullspace_basis.empty();\n\
    \    }\n};\n\ninline BitLinearSystemResult solve_linear_system(\n    const BitMatrix&\
    \ coefficients,\n    const std::vector<bool>& constants\n) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    BitMatrix augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            if (coefficients.get(row,\
    \ col)) augmented.set(row, col);\n        }\n        if (constants[std::size_t(row)])\
    \ augmented.set(row, variable_count);\n    }\n\n    BitLinearSystemResult result;\n\
    \    result.pivot_columns = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        variable_count,\n        true\n    );\n    for (int row = result.rank();\
    \ row < equation_count; row++) {\n        if (augmented.get(row, variable_count))\
    \ return result;\n    }\n\n    result.consistent = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ false);\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] =\n          \
    \  augmented.get(row, variable_count);\n    }\n\n    for (int free_col = 0; free_col\
    \ < variable_count; free_col++) {\n        if (is_pivot[std::size_t(free_col)])\
    \ continue;\n        std::vector<bool> direction(std::size_t(variable_count),\
    \ false);\n        direction[std::size_t(free_col)] = true;\n        for (int\
    \ row = 0; row < result.rank(); row++) {\n            const int pivot_col = result.pivot_columns[std::size_t(row)];\n\
    \            direction[std::size_t(pivot_col)] = augmented.get(row, free_col);\n\
    \        }\n        result.nullspace_basis.push_back(std::move(direction));\n\
    \    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\
    \n\n#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\n#line 8 \"math/matrix/characteristic_polynomial.hpp\"\
    \n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 9 \"math/matrix/matrix.hpp\"\
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
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/hafnian.hpp\"\
    \n\n\n\n#line 7 \"math/matrix/hafnian.hpp\"\n\n#line 9 \"math/matrix/hafnian.hpp\"\
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
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\
    \n\n\n\n#line 5 \"math/matrix/linear_algebra.hpp\"\n#include <type_traits>\n#line\
    \ 7 \"math/matrix/linear_algebra.hpp\"\n\n#line 9 \"math/matrix/linear_algebra.hpp\"\
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
    #line 1 \"math/matrix/pfaffian.hpp\"\n\n\n\n#line 6 \"math/matrix/pfaffian.hpp\"\
    \n\n#line 8 \"math/matrix/pfaffian.hpp\"\n\nnamespace m1une {\nnamespace matrix\
    \ {\n\n// Returns the Pfaffian of an even-dimensional alternating matrix over\
    \ a field.\ntemplate <class T>\nT pfaffian(Matrix<T> matrix) {\n    assert(matrix.rows()\
    \ == matrix.cols());\n    const int size = matrix.rows();\n    assert(size % 2\
    \ == 0);\n\n#ifndef NDEBUG\n    for (int row = 0; row < size; row++) {\n     \
    \   assert(matrix[row][row] == T());\n        for (int col = row + 1; col < size;\
    \ col++) {\n            assert(matrix[row][col] == T() - matrix[col][row]);\n\
    \        }\n    }\n#endif\n\n    T result = T(1);\n    for (int first = 0; first\
    \ < size; first += 2) {\n        int pivot = first + 1;\n        while (pivot\
    \ < size && matrix[first][pivot] == T()) pivot++;\n        if (pivot == size)\
    \ return T();\n\n        if (pivot != first + 1) {\n            matrix.swap_rows(pivot,\
    \ first + 1);\n            for (int row = 0; row < size; row++) {\n          \
    \      std::swap(matrix[row][pivot], matrix[row][first + 1]);\n            }\n\
    \            result = T() - result;\n        }\n\n        const int second = first\
    \ + 1;\n        const T pivot_value = matrix[first][second];\n        result *=\
    \ pivot_value;\n        const T inverse_pivot = T(1) / pivot_value;\n\n      \
    \  for (int row = second + 1; row < size; row++) {\n            for (int col =\
    \ row + 1; col < size; col++) {\n                matrix[row][col] +=\n       \
    \             (matrix[second][row] * matrix[first][col] -\n                  \
    \   matrix[first][row] * matrix[second][col]) *\n                    inverse_pivot;\n\
    \                matrix[col][row] = T() - matrix[row][col];\n            }\n \
    \       }\n    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/matrix/sparse_determinant.hpp\"\n\n\n\n#line 8 \"\
    math/matrix/sparse_determinant.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\
    \ntemplate <class T>\nstruct SparseMatrixEntry {\n    int row;\n    int col;\n\
    \    T value;\n};\n\nnamespace internal {\n\nstruct SparseDeterminantRandom {\n\
    \    std::uint64_t state;\n\n    explicit SparseDeterminantRandom(std::uint64_t\
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
    \ 11 \"math/matrix/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_MATRIX_ALL_HPP

    #define M1UNE_MATRIX_ALL_HPP 1


    #include "bit_matrix.hpp"

    #include "characteristic_polynomial.hpp"

    #include "hafnian.hpp"

    #include "linear_algebra.hpp"

    #include "matrix.hpp"

    #include "pfaffian.hpp"

    #include "sparse_determinant.hpp"


    #endif  // M1UNE_MATRIX_ALL_HPP

    '
  dependsOn:
  - math/matrix/bit_matrix.hpp
  - math/matrix/characteristic_polynomial.hpp
  - math/matrix/matrix.hpp
  - math/matrix/hafnian.hpp
  - math/matrix/linear_algebra.hpp
  - math/matrix/pfaffian.hpp
  - math/matrix/sparse_determinant.hpp
  isVerificationFile: false
  path: math/matrix/all.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-14 02:42:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/matrix.test.cpp
documentation_of: math/matrix/all.hpp
layout: document
title: Matrix Bundle
---

## Overview

`math/matrix/all.hpp` includes the complete dense and packed GF(2) matrix
module.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/matrix/bit_matrix.hpp` | Packed GF(2) matrices, arithmetic, multiplication, elimination, rank, inverse, and linear systems. |
| `math/matrix/characteristic_polynomial.hpp` | Characteristic polynomial of a square matrix over a field. |
| `math/matrix/pfaffian.hpp` | Cubic-time Pfaffian of an alternating matrix. |
| `math/matrix/hafnian.hpp` | Exact hafnian of a small symmetric matrix. |
| `math/matrix/sparse_determinant.hpp` | Randomized black-box determinant of a sparse matrix over a finite field. |
| `math/matrix/matrix.hpp` | Row-major dense matrices, arithmetic, multiplication, transposition, matrix-vector products, and powers. |
| `math/matrix/linear_algebra.hpp` | Gaussian elimination, rank, determinant, inverse, and linear systems. |
