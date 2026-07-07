#ifndef M1UNE_GRID_TRANSFORM_HPP
#define M1UNE_GRID_TRANSFORM_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

namespace m1une {
namespace utilities {

template <class T>
using Vector2D = std::vector<std::vector<T>>;

namespace grid_transform_detail {

template <class Row>
void reserve_if_possible(Row& row, std::size_t size) {
    if constexpr (requires { row.reserve(size); }) {
        row.reserve(size);
    }
}

template <class Row>
std::vector<Row> make_rows(std::size_t row_count, std::size_t row_size) {
    std::vector<Row> result(row_count);
    for (Row& row : result) reserve_if_possible(row, row_size);
    return result;
}

}  // namespace grid_transform_detail

template <class Row>
bool is_rectangular(const std::vector<Row>& grid) {
    if (grid.empty()) return true;
    const std::size_t row_size = grid[0].size();
    for (const Row& row : grid) {
        if (row.size() != row_size) return false;
    }
    return true;
}

template <class Row>
std::size_t height(const std::vector<Row>& grid) {
    return grid.size();
}

template <class Row>
std::size_t width(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    return grid.empty() ? 0 : grid[0].size();
}

template <class Row>
std::vector<Row> transpose(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    const std::size_t h = height(grid);
    const std::size_t w = width(grid);

    std::vector<Row> result =
        grid_transform_detail::make_rows<Row>(w, h);
    for (std::size_t y = 0; y < h; y++) {
        for (std::size_t x = 0; x < w; x++) {
            result[x].push_back(grid[y][x]);
        }
    }
    return result;
}

template <class Row>
std::vector<Row> flip_horizontal(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    std::vector<Row> result = grid;
    for (Row& row : result) {
        std::reverse(row.begin(), row.end());
    }
    return result;
}

template <class Row>
std::vector<Row> flip_vertical(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    std::vector<Row> result = grid;
    std::reverse(result.begin(), result.end());
    return result;
}

template <class Row>
std::vector<Row> rotate90(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    const std::size_t h = height(grid);
    const std::size_t w = width(grid);

    std::vector<Row> result =
        grid_transform_detail::make_rows<Row>(w, h);
    for (std::size_t x = 0; x < w; x++) {
        for (std::size_t y = h; y > 0; y--) {
            result[x].push_back(grid[y - 1][x]);
        }
    }
    return result;
}

template <class Row>
std::vector<Row> rotate180(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    std::vector<Row> result = flip_vertical(grid);
    for (Row& row : result) {
        std::reverse(row.begin(), row.end());
    }
    return result;
}

template <class Row>
std::vector<Row> rotate270(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    const std::size_t h = height(grid);
    const std::size_t w = width(grid);

    std::vector<Row> result =
        grid_transform_detail::make_rows<Row>(w, h);
    for (std::size_t x = 0; x < w; x++) {
        for (std::size_t y = 0; y < h; y++) {
            result[w - 1 - x].push_back(grid[y][x]);
        }
    }
    return result;
}

template <class Row>
std::vector<Row> rotate_clockwise(const std::vector<Row>& grid) {
    return rotate90(grid);
}

template <class Row>
std::vector<Row> rotate_counterclockwise(const std::vector<Row>& grid) {
    return rotate270(grid);
}

template <class Row>
std::vector<Row> rotate(const std::vector<Row>& grid, int clockwise_quarter_turns) {
    assert(is_rectangular(grid));
    int turns = clockwise_quarter_turns % 4;
    if (turns < 0) turns += 4;
    if (turns == 0) return grid;
    if (turns == 1) return rotate90(grid);
    if (turns == 2) return rotate180(grid);
    return rotate270(grid);
}

template <class Row>
std::array<std::vector<Row>, 4> rotations(const std::vector<Row>& grid) {
    assert(is_rectangular(grid));
    return std::array<std::vector<Row>, 4>{
        grid,
        rotate90(grid),
        rotate180(grid),
        rotate270(grid)
    };
}

template <class Row>
std::array<std::vector<Row>, 8> dihedral_transforms(
    const std::vector<Row>& grid
) {
    assert(is_rectangular(grid));
    const std::vector<Row> mirrored = flip_horizontal(grid);
    return std::array<std::vector<Row>, 8>{
        grid,
        rotate90(grid),
        rotate180(grid),
        rotate270(grid),
        mirrored,
        rotate90(mirrored),
        rotate180(mirrored),
        rotate270(mirrored)
    };
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_GRID_TRANSFORM_HPP
