#ifndef M1UNE_MATRIX_BIT_MATRIX_HPP
#define M1UNE_MATRIX_BIT_MATRIX_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace m1une {
namespace matrix {

class BitMatrix {
   private:
    int _rows;
    int _cols;
    int _blocks;
    std::vector<std::uint64_t> _data;

    static int block_count(int cols) {
        assert(cols >= 0);
        return (cols + 63) / 64;
    }

    static std::size_t storage_size(int rows, int blocks) {
        assert(rows >= 0);
        return std::size_t(rows) * std::size_t(blocks);
    }

    std::size_t word_index(int row, int col) const {
        assert(0 <= row && row < _rows);
        assert(0 <= col && col < _cols);
        return std::size_t(row) * std::size_t(_blocks) +
               std::size_t(col / 64);
    }

    std::uint64_t trailing_mask() const {
        if ((_cols & 63) == 0) return ~std::uint64_t(0);
        return (std::uint64_t(1) << (_cols & 63)) - 1;
    }

   public:
    class BitReference {
       private:
        std::uint64_t* word;
        std::uint64_t mask;

       public:
        BitReference(std::uint64_t& word_value, std::uint64_t mask_value)
            : word(&word_value), mask(mask_value) {}

        operator bool() const {
            return (*word & mask) != 0;
        }

        BitReference& operator=(bool value) {
            if (value) {
                *word |= mask;
            } else {
                *word &= ~mask;
            }
            return *this;
        }

        BitReference& operator=(const BitReference& other) {
            return *this = bool(other);
        }

        void flip() {
            *word ^= mask;
        }
    };

    class RowReference {
       private:
        BitMatrix* matrix;
        int row;

       public:
        RowReference(BitMatrix& matrix_value, int row_value)
            : matrix(&matrix_value), row(row_value) {}

        BitReference operator[](int col) const {
            return (*matrix)(row, col);
        }
    };

    class ConstRowReference {
       private:
        const BitMatrix* matrix;
        int row;

       public:
        ConstRowReference(const BitMatrix& matrix_value, int row_value)
            : matrix(&matrix_value), row(row_value) {}

        bool operator[](int col) const {
            return (*matrix)(row, col);
        }
    };

    BitMatrix() : _rows(0), _cols(0), _blocks(0) {}

    BitMatrix(int rows, int cols, bool value = false)
        : _rows(rows),
          _cols(cols),
          _blocks(block_count(cols)),
          _data(
              storage_size(rows, _blocks),
              value ? ~std::uint64_t(0) : std::uint64_t(0)
          ) {
        assert(rows >= 0);
        if (value && _blocks > 0) {
            const std::uint64_t mask = trailing_mask();
            for (int row = 0; row < _rows; row++) {
                _data[
                    std::size_t(row + 1) * std::size_t(_blocks) - 1
                ] &= mask;
            }
        }
    }

    int rows() const {
        return _rows;
    }

    int cols() const {
        return _cols;
    }

    int blocks_per_row() const {
        return _blocks;
    }

    bool empty() const {
        return _rows == 0 || _cols == 0;
    }

    RowReference operator[](int row) {
        assert(0 <= row && row < _rows);
        return RowReference(*this, row);
    }

    ConstRowReference operator[](int row) const {
        assert(0 <= row && row < _rows);
        return ConstRowReference(*this, row);
    }

    BitReference operator()(int row, int col) {
        const std::size_t index = word_index(row, col);
        return BitReference(_data[index], std::uint64_t(1) << (col & 63));
    }

    bool operator()(int row, int col) const {
        const std::size_t index = word_index(row, col);
        return (_data[index] >> (col & 63)) & 1;
    }

    bool get(int row, int col) const {
        return (*this)(row, col);
    }

    void set(int row, int col, bool value = true) {
        (*this)(row, col) = value;
    }

    void reset(int row, int col) {
        set(row, col, false);
    }

    void flip(int row, int col) {
        (*this)(row, col).flip();
    }

    void clear() {
        std::fill(_data.begin(), _data.end(), std::uint64_t(0));
    }

    void set_row(int row, std::string_view bits) {
        assert(0 <= row && row < _rows);
        assert(int(bits.size()) == _cols);
        const std::size_t offset =
            std::size_t(row) * std::size_t(_blocks);
        std::fill(
            _data.begin() + std::ptrdiff_t(offset),
            _data.begin() + std::ptrdiff_t(offset + std::size_t(_blocks)),
            std::uint64_t(0)
        );
        for (int col = 0; col < _cols; col++) {
            assert(bits[std::size_t(col)] == '0' || bits[std::size_t(col)] == '1');
            if (bits[std::size_t(col)] == '1') set(row, col);
        }
    }

    std::string row_string(int row) const {
        assert(0 <= row && row < _rows);
        std::string result(std::size_t(_cols), '0');
        for (int col = 0; col < _cols; col++) {
            if (get(row, col)) result[std::size_t(col)] = '1';
        }
        return result;
    }

    static BitMatrix identity(int size) {
        assert(size >= 0);
        BitMatrix result(size, size);
        for (int index = 0; index < size; index++) result.set(index, index);
        return result;
    }

    BitMatrix transposed() const {
        BitMatrix result(_cols, _rows);
        for (int row = 0; row < _rows; row++) {
            for (int col = 0; col < _cols; col++) {
                if (get(row, col)) result.set(col, row);
            }
        }
        return result;
    }

    void swap_rows(int first, int second) {
        assert(0 <= first && first < _rows);
        assert(0 <= second && second < _rows);
        if (first == second) return;
        const std::size_t first_offset =
            std::size_t(first) * std::size_t(_blocks);
        const std::size_t second_offset =
            std::size_t(second) * std::size_t(_blocks);
        for (int block = 0; block < _blocks; block++) {
            std::swap(
                _data[first_offset + std::size_t(block)],
                _data[second_offset + std::size_t(block)]
            );
        }
    }

    void xor_rows(int target, int source, int first_col = 0) {
        assert(0 <= target && target < _rows);
        assert(0 <= source && source < _rows);
        assert(0 <= first_col && first_col <= _cols);
        if (first_col == _cols) return;
        const std::size_t target_offset =
            std::size_t(target) * std::size_t(_blocks);
        const std::size_t source_offset =
            std::size_t(source) * std::size_t(_blocks);
        const int first_block = first_col / 64;
        const int first_bit = first_col & 63;
        if (first_bit != 0) {
            const std::uint64_t mask = ~std::uint64_t(0) << first_bit;
            _data[target_offset + std::size_t(first_block)] ^=
                _data[source_offset + std::size_t(first_block)] & mask;
        } else {
            _data[target_offset + std::size_t(first_block)] ^=
                _data[source_offset + std::size_t(first_block)];
        }
        for (int block = first_block + 1; block < _blocks; block++) {
            _data[target_offset + std::size_t(block)] ^=
                _data[source_offset + std::size_t(block)];
        }
    }

    BitMatrix& operator^=(const BitMatrix& rhs) {
        assert(_rows == rhs._rows && _cols == rhs._cols);
        for (std::size_t index = 0; index < _data.size(); index++) {
            _data[index] ^= rhs._data[index];
        }
        return *this;
    }

    BitMatrix& operator+=(const BitMatrix& rhs) {
        return *this ^= rhs;
    }

    BitMatrix& operator-=(const BitMatrix& rhs) {
        return *this ^= rhs;
    }

    BitMatrix& operator*=(const BitMatrix& rhs) {
        return *this = *this * rhs;
    }

    friend BitMatrix operator^(BitMatrix lhs, const BitMatrix& rhs) {
        return lhs ^= rhs;
    }

    friend BitMatrix operator+(BitMatrix lhs, const BitMatrix& rhs) {
        return lhs += rhs;
    }

    friend BitMatrix operator-(BitMatrix lhs, const BitMatrix& rhs) {
        return lhs -= rhs;
    }

    friend BitMatrix operator*(const BitMatrix& lhs, const BitMatrix& rhs) {
        assert(lhs._cols == rhs._rows);
        BitMatrix result(lhs._rows, rhs._cols);
        for (int row = 0; row < lhs._rows; row++) {
            const std::size_t lhs_offset =
                std::size_t(row) * std::size_t(lhs._blocks);
            const std::size_t result_offset =
                std::size_t(row) * std::size_t(result._blocks);
            for (int lhs_block = 0; lhs_block < lhs._blocks; lhs_block++) {
                std::uint64_t word =
                    lhs._data[lhs_offset + std::size_t(lhs_block)];
                while (word != 0) {
                    const int bit = std::countr_zero(word);
                    const int middle = lhs_block * 64 + bit;
                    const std::size_t rhs_offset =
                        std::size_t(middle) * std::size_t(rhs._blocks);
                    for (int block = 0; block < rhs._blocks; block++) {
                        result._data[result_offset + std::size_t(block)] ^=
                            rhs._data[rhs_offset + std::size_t(block)];
                    }
                    word &= word - 1;
                }
            }
        }
        return result;
    }

    bool operator==(const BitMatrix& rhs) const {
        return
            _rows == rhs._rows && _cols == rhs._cols && _data == rhs._data;
    }

    bool operator!=(const BitMatrix& rhs) const {
        return !(*this == rhs);
    }

    BitMatrix pow(std::uint64_t exponent) const {
        assert(_rows == _cols);
        BitMatrix result = identity(_rows);
        BitMatrix base = *this;
        while (exponent > 0) {
            if (exponent & 1) result *= base;
            exponent >>= 1;
            if (exponent > 0) base *= base;
        }
        return result;
    }
};

namespace bit_matrix_detail {

inline std::vector<int> row_reduce(
    BitMatrix& matrix,
    int pivot_col_limit,
    bool reduced
) {
    assert(0 <= pivot_col_limit && pivot_col_limit <= matrix.cols());
    std::vector<int> pivot_columns;
    int pivot_row = 0;
    for (
        int col = 0;
        col < pivot_col_limit && pivot_row < matrix.rows();
        col++
    ) {
        int pivot = -1;
        for (int row = pivot_row; row < matrix.rows(); row++) {
            if (matrix.get(row, col)) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        matrix.swap_rows(pivot_row, pivot);

        const int first_row = reduced ? 0 : pivot_row + 1;
        for (int row = first_row; row < matrix.rows(); row++) {
            if (row != pivot_row && matrix.get(row, col)) {
                matrix.xor_rows(row, pivot_row, col);
            }
        }
        pivot_columns.push_back(col);
        pivot_row++;
    }
    return pivot_columns;
}

}  // namespace bit_matrix_detail

struct BitRowReduction {
    BitMatrix matrix;
    std::vector<int> pivot_columns;

    int rank() const {
        return int(pivot_columns.size());
    }
};

inline BitRowReduction reduced_row_echelon_form(BitMatrix matrix) {
    BitRowReduction result;
    result.pivot_columns = bit_matrix_detail::row_reduce(
        matrix,
        matrix.cols(),
        true
    );
    result.matrix = std::move(matrix);
    return result;
}

inline int matrix_rank(BitMatrix matrix) {
    if (matrix.rows() > matrix.cols()) matrix = matrix.transposed();
    return int(bit_matrix_detail::row_reduce(
        matrix,
        matrix.cols(),
        false
    ).size());
}

inline bool determinant(const BitMatrix& matrix) {
    assert(matrix.rows() == matrix.cols());
    return matrix_rank(matrix) == matrix.rows();
}

inline std::optional<BitMatrix> inverse(const BitMatrix& matrix) {
    assert(matrix.rows() == matrix.cols());
    const int size = matrix.rows();
    BitMatrix augmented(size, 2 * size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (matrix.get(row, col)) augmented.set(row, col);
        }
        augmented.set(row, size + row);
    }

    const std::vector<int> pivots = bit_matrix_detail::row_reduce(
        augmented,
        size,
        true
    );
    if (int(pivots.size()) != size) return std::nullopt;

    BitMatrix result(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (augmented.get(row, size + col)) result.set(row, col);
        }
    }
    return result;
}

struct BitLinearSystemResult {
    bool consistent = false;
    std::vector<bool> particular_solution;
    std::vector<std::vector<bool>> nullspace_basis;
    std::vector<int> pivot_columns;

    int rank() const {
        return int(pivot_columns.size());
    }

    int nullity() const {
        return consistent ? int(nullspace_basis.size()) : 0;
    }

    bool has_unique_solution() const {
        return consistent && nullspace_basis.empty();
    }
};

inline BitLinearSystemResult solve_linear_system(
    const BitMatrix& coefficients,
    const std::vector<bool>& constants
) {
    assert(coefficients.rows() == int(constants.size()));
    const int equation_count = coefficients.rows();
    const int variable_count = coefficients.cols();
    BitMatrix augmented(equation_count, variable_count + 1);
    for (int row = 0; row < equation_count; row++) {
        for (int col = 0; col < variable_count; col++) {
            if (coefficients.get(row, col)) augmented.set(row, col);
        }
        if (constants[std::size_t(row)]) augmented.set(row, variable_count);
    }

    BitLinearSystemResult result;
    result.pivot_columns = bit_matrix_detail::row_reduce(
        augmented,
        variable_count,
        true
    );
    for (int row = result.rank(); row < equation_count; row++) {
        if (augmented.get(row, variable_count)) return result;
    }

    result.consistent = true;
    result.particular_solution.assign(std::size_t(variable_count), false);
    std::vector<bool> is_pivot(std::size_t(variable_count), false);
    for (int row = 0; row < result.rank(); row++) {
        const int col = result.pivot_columns[std::size_t(row)];
        is_pivot[std::size_t(col)] = true;
        result.particular_solution[std::size_t(col)] =
            augmented.get(row, variable_count);
    }

    for (int free_col = 0; free_col < variable_count; free_col++) {
        if (is_pivot[std::size_t(free_col)]) continue;
        std::vector<bool> direction(std::size_t(variable_count), false);
        direction[std::size_t(free_col)] = true;
        for (int row = 0; row < result.rank(); row++) {
            const int pivot_col = result.pivot_columns[std::size_t(row)];
            direction[std::size_t(pivot_col)] = augmented.get(row, free_col);
        }
        result.nullspace_basis.push_back(std::move(direction));
    }
    return result;
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_BIT_MATRIX_HPP
