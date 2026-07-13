---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/matrix/bit_matrix.hpp
    title: Bit Matrix
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inverse_matrix_mod_2
    links:
    - https://judge.yosupo.jp/problem/inverse_matrix_mod_2
  bundledCode: "#line 1 \"verify/math/matrix/bit_matrix_inverse.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/inverse_matrix_mod_2\"\n\n#include\
    \ <iostream>\n#include <optional>\n#include <string>\n\n#line 1 \"math/matrix/bit_matrix.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#line 11 \"math/matrix/bit_matrix.hpp\"\n#include <string_view>\n\
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
    \n\n#line 8 \"verify/math/matrix/bit_matrix_inverse.test.cpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ size;\n    std::cin >> size;\n    m1une::matrix::BitMatrix matrix(size, size);\n\
    \    std::string bits;\n    for (int row = 0; row < size; row++) {\n        std::cin\
    \ >> bits;\n        matrix.set_row(row, bits);\n    }\n\n    std::optional<m1une::matrix::BitMatrix>\
    \ result =\n        m1une::matrix::inverse(matrix);\n    if (!result) {\n    \
    \    std::cout << -1 << '\\n';\n        return 0;\n    }\n    for (int row = 0;\
    \ row < size; row++) {\n        std::cout << result->row_string(row) << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inverse_matrix_mod_2\"\n\
    \n#include <iostream>\n#include <optional>\n#include <string>\n\n#include \"../../../math/matrix/bit_matrix.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int size;\n    std::cin >> size;\n    m1une::matrix::BitMatrix matrix(size,\
    \ size);\n    std::string bits;\n    for (int row = 0; row < size; row++) {\n\
    \        std::cin >> bits;\n        matrix.set_row(row, bits);\n    }\n\n    std::optional<m1une::matrix::BitMatrix>\
    \ result =\n        m1une::matrix::inverse(matrix);\n    if (!result) {\n    \
    \    std::cout << -1 << '\\n';\n        return 0;\n    }\n    for (int row = 0;\
    \ row < size; row++) {\n        std::cout << result->row_string(row) << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - math/matrix/bit_matrix.hpp
  isVerificationFile: true
  path: verify/math/matrix/bit_matrix_inverse.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 20:43:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/bit_matrix_inverse.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/bit_matrix_inverse.test.cpp
- /verify/verify/math/matrix/bit_matrix_inverse.test.cpp.html
title: verify/math/matrix/bit_matrix_inverse.test.cpp
---
