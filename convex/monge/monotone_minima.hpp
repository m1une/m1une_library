#ifndef M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP
#define M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP 1

#include <cassert>
#include <functional>
#include <span>
#include <vector>

namespace m1une {
namespace convex {

namespace monotone_minima_detail {

template <class Value, class Compare>
void solve(int row_left, int row_right, int column_left, int column_right,
           const Value& value, const Compare& compare, std::vector<int>& answer) {
    if (row_left == row_right) return;
    int row = (row_left + row_right) / 2;
    int best = column_left;
    for (int column = column_left + 1; column < column_right; column++) {
        if (compare(value(row, column), value(row, best))) best = column;
    }
    answer[row] = best;
    solve(row_left, row, column_left, best + 1, value, compare, answer);
    solve(row + 1, row_right, best, column_right, value, compare, answer);
}

}  // namespace monotone_minima_detail

// Fixed rectangular matrix; leftmost optimal columns must be nondecreasing.
// Returns column indices, or -1 when there are no columns. Not an online DP.
// O(H + W log(H+1)) time, O(H + log(H+1)) memory.
template <class Value, class Compare = std::less<>>
std::vector<int> monotone_row_optima(int row_count, int column_count, Value value,
                                     Compare compare = Compare()) {
    assert(row_count >= 0);
    assert(column_count >= 0);
    std::vector<int> answer(row_count, -1);
    if (row_count == 0 || column_count == 0) return answer;
    monotone_minima_detail::solve(0, row_count, 0, column_count, value, compare, answer);
    return answer;
}

template <class Value>
std::vector<int> monotone_row_argmin(int row_count, int column_count, Value value) {
    return monotone_row_optima(row_count, column_count, value, std::less<>());
}

template <class Value>
std::vector<int> monotone_row_argmax(int row_count, int column_count, Value value) {
    return monotone_row_optima(row_count, column_count, value, std::greater<>());
}

// Ordered matrix value(rows[r], columns[c]); return original column IDs in
// row list order. Leftmost means first in columns. IDs are distinct/nonnegative.
template <class Value, class Compare = std::less<>>
std::vector<int> monotone_row_optima(std::span<const int> rows,
                                     std::span<const int> columns, Value value,
                                     Compare compare = Compare()) {
    auto answer = monotone_row_optima(int(rows.size()), int(columns.size()),
        [&](int row, int column) -> decltype(auto) {
            return value(rows[row], columns[column]);
        }, compare);
    for (int& column : answer) if (column != -1) column = columns[column];
    return answer;
}

template <class Value>
std::vector<int> monotone_row_argmin(std::span<const int> rows,
                                     std::span<const int> columns, Value value) {
    return monotone_row_optima(rows, columns, value, std::less<>());
}

template <class Value>
std::vector<int> monotone_row_argmax(std::span<const int> rows,
                                     std::span<const int> columns, Value value) {
    return monotone_row_optima(rows, columns, value, std::greater<>());
}

template <class T>
std::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return monotone_row_argmin(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

template <class T>
std::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>& matrix) {
    int row_count = int(matrix.size());
    int column_count = row_count == 0 ? 0 : int(matrix[0].size());
    for (const auto& row : matrix) assert(int(row.size()) == column_count);
    return monotone_row_argmax(
        row_count, column_count,
        [&](int row, int column) -> const T& { return matrix[row][column]; });
}

}  // namespace convex
}  // namespace m1une

#endif  // M1UNE_CONVEX_MONGE_MONOTONE_MINIMA_HPP
