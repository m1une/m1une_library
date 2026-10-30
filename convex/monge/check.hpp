#ifndef M1UNE_CONVEX_MONGE_CHECK_HPP
#define M1UNE_CONVEX_MONGE_CHECK_HPP 1

#include <cassert>
#include <span>
#include <vector>

namespace m1une {
namespace convex {

template <class Value>
bool is_monge(int row_count, int column_count, Value value) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    if (row_count < 2 || column_count < 2) return true;
    for (int row = 0; row + 1 < row_count; row++) {
        for (int column = 0; column + 1 < column_count; column++) {
            if (value(row, column) + value(row + 1, column + 1) >
                value(row, column + 1) + value(row + 1, column)) {
                return false;
            }
        }
    }
    return true;
}

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value) {
    return is_monge(row_count, column_count,
        [&](int row, int column) -> decltype(auto) {
            return value(row, column_count - 1 - column);
        });
}

// Check adjacent 2x2 inequalities in the supplied orders, O(HW) time,
// O(1) extra memory. Distinct nonnegative IDs; arithmetic must not overflow.
template <class Value>
bool is_monge(std::span<const int> rows, std::span<const int> columns, Value value) {
    return is_monge(int(rows.size()), int(columns.size()),
        [&](int row, int column) -> decltype(auto) {
            return value(rows[row], columns[column]);
        });
}

template <class Value>
bool is_anti_monge(std::span<const int> rows, std::span<const int> columns,
                   Value value) {
    return is_anti_monge(int(rows.size()), int(columns.size()),
        [&](int row, int column) -> decltype(auto) {
            return value(rows[row], columns[column]);
        });
}

template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return is_monge(row_count, column_count,
                    [&](int row, int column) -> const T& { return matrix[row][column]; });
}

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return is_anti_monge(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

}  // namespace convex
}  // namespace m1une

#endif  // M1UNE_CONVEX_MONGE_CHECK_HPP
