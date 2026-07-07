#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/grid_transform.hpp"
#include "../../utilities/random.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace {

using m1une::utilities::dihedral_transforms;
using m1une::utilities::flip_horizontal;
using m1une::utilities::flip_vertical;
using m1une::utilities::height;
using m1une::utilities::is_rectangular;
using m1une::utilities::rotate;
using m1une::utilities::rotate180;
using m1une::utilities::rotate270;
using m1une::utilities::rotate90;
using m1une::utilities::rotate_clockwise;
using m1une::utilities::rotate_counterclockwise;
using m1une::utilities::rotations;
using m1une::utilities::transpose;
using m1une::utilities::Vector2D;
using m1une::utilities::width;

void assert_shape(const Vector2D<int>& grid, int h, int w) {
    assert(static_cast<int>(grid.size()) == h);
    for (const std::vector<int>& row : grid) {
        assert(static_cast<int>(row.size()) == w);
    }
}

void check_coordinate_mappings(const Vector2D<int>& grid) {
    assert(is_rectangular(grid));
    const int h = static_cast<int>(grid.size());
    const int w = h == 0 ? 0 : static_cast<int>(grid[0].size());
    assert(static_cast<int>(height(grid)) == h);
    assert(static_cast<int>(width(grid)) == w);

    const Vector2D<int> transposed = transpose(grid);
    assert_shape(transposed, w, h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(transposed[x][y] == grid[y][x]);
        }
    }

    const Vector2D<int> horizontal = flip_horizontal(grid);
    assert_shape(horizontal, h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(horizontal[y][w - 1 - x] == grid[y][x]);
        }
    }

    const Vector2D<int> vertical = flip_vertical(grid);
    assert_shape(vertical, h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(vertical[h - 1 - y][x] == grid[y][x]);
        }
    }

    const Vector2D<int> clockwise = rotate90(grid);
    assert_shape(clockwise, w, h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(clockwise[x][h - 1 - y] == grid[y][x]);
        }
    }
    assert(rotate_clockwise(grid) == clockwise);

    const Vector2D<int> half_turn = rotate180(grid);
    assert_shape(half_turn, h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(half_turn[h - 1 - y][w - 1 - x] == grid[y][x]);
        }
    }

    const Vector2D<int> counterclockwise = rotate270(grid);
    assert_shape(counterclockwise, w, h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            assert(counterclockwise[w - 1 - x][y] == grid[y][x]);
        }
    }
    assert(rotate_counterclockwise(grid) == counterclockwise);

    assert(rotate(grid, 0) == grid);
    assert(rotate(grid, 1) == clockwise);
    assert(rotate(grid, 2) == half_turn);
    assert(rotate(grid, 3) == counterclockwise);
    assert(rotate(grid, 4) == grid);
    assert(rotate(grid, -1) == counterclockwise);
    assert(rotate(grid, -2) == half_turn);
    assert(rotate(grid, 5) == clockwise);

    const auto all_rotations = rotations(grid);
    assert(all_rotations[0] == grid);
    assert(all_rotations[1] == clockwise);
    assert(all_rotations[2] == half_turn);
    assert(all_rotations[3] == counterclockwise);

    const auto all_dihedral = dihedral_transforms(grid);
    assert(all_dihedral[0] == grid);
    assert(all_dihedral[1] == clockwise);
    assert(all_dihedral[2] == half_turn);
    assert(all_dihedral[3] == counterclockwise);
    assert(all_dihedral[4] == horizontal);
    assert(all_dihedral[5] == rotate90(horizontal));
    assert(all_dihedral[6] == rotate180(horizontal));
    assert(all_dihedral[7] == rotate270(horizontal));
}

void test_fixed_vector_grids() {
    Vector2D<int> grid;
    grid.emplace_back(std::vector<int>{1, 2, 3});
    grid.emplace_back(std::vector<int>{4, 5, 6});
    check_coordinate_mappings(grid);

    Vector2D<int> empty;
    check_coordinate_mappings(empty);

    Vector2D<int> zero_width(3);
    check_coordinate_mappings(zero_width);

    std::vector<std::vector<int>> ragged;
    ragged.emplace_back(std::vector<int>{1, 2});
    ragged.emplace_back(std::vector<int>{3});
    assert(!is_rectangular(ragged));
}

void test_string_grids() {
    std::vector<std::string> grid;
    grid.emplace_back("abc");
    grid.emplace_back("def");

    std::vector<std::string> expected_transpose;
    expected_transpose.emplace_back("ad");
    expected_transpose.emplace_back("be");
    expected_transpose.emplace_back("cf");
    assert(transpose(grid) == expected_transpose);

    std::vector<std::string> expected_clockwise;
    expected_clockwise.emplace_back("da");
    expected_clockwise.emplace_back("eb");
    expected_clockwise.emplace_back("fc");
    assert(rotate90(grid) == expected_clockwise);

    std::vector<std::string> expected_half_turn;
    expected_half_turn.emplace_back("fed");
    expected_half_turn.emplace_back("cba");
    assert(rotate180(grid) == expected_half_turn);

    std::vector<std::string> expected_counterclockwise;
    expected_counterclockwise.emplace_back("cf");
    expected_counterclockwise.emplace_back("be");
    expected_counterclockwise.emplace_back("ad");
    assert(rotate270(grid) == expected_counterclockwise);

    std::vector<std::string> expected_horizontal;
    expected_horizontal.emplace_back("cba");
    expected_horizontal.emplace_back("fed");
    assert(flip_horizontal(grid) == expected_horizontal);

    std::vector<std::string> expected_vertical;
    expected_vertical.emplace_back("def");
    expected_vertical.emplace_back("abc");
    assert(flip_vertical(grid) == expected_vertical);
}

void test_random_grids() {
    m1une::utilities::Random random(0x7a5a2d11ULL);
    for (int trial = 0; trial < 1000; trial++) {
        const int h = static_cast<int>(random.uniform(0, 8));
        const int w = static_cast<int>(random.uniform(0, 8));
        Vector2D<int> grid(h, std::vector<int>(w));
        for (std::vector<int>& row : grid) {
            for (int& value : row) {
                value = static_cast<int>(random.uniform(-1000, 1000));
            }
        }
        check_coordinate_mappings(grid);
    }
}

}  // namespace

int main() {
    test_fixed_vector_grids();
    test_string_grids();
    test_random_grids();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
