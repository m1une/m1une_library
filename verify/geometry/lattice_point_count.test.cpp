#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/lattice_point_count.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <limits>
#include <vector>

using Inequality = m1une::geometry::LinearInequality<long long>;

__int128 count(const std::vector<Inequality>& inequalities) {
    return m1une::geometry::count_lattice_points(inequalities);
}

void test_examples_and_degenerate_regions() {
    std::vector<Inequality> triangle;
    triangle.push_back(Inequality{-1, 0, 0});
    triangle.push_back(Inequality{0, -1, 0});
    triangle.push_back(Inequality{1, 1, 2});
    assert(count(triangle) == 6);

    std::vector<Inequality> point;
    point.push_back(Inequality{1, 0, 1});
    point.push_back(Inequality{-1, 0, -1});
    point.push_back(Inequality{0, 1, 2});
    point.push_back(Inequality{0, -1, -2});
    assert(count(point) == 1);

    std::vector<Inequality> diagonal_segment;
    diagonal_segment.push_back(Inequality{-1, 0, 0});
    diagonal_segment.push_back(Inequality{1, 0, 2});
    diagonal_segment.push_back(Inequality{-1, 2, 0});
    diagonal_segment.push_back(Inequality{1, -2, 0});
    assert(count(diagonal_segment) == 2);

    std::vector<Inequality> fractional_vertical_segment;
    fractional_vertical_segment.push_back(Inequality{2, 0, 1});
    fractional_vertical_segment.push_back(Inequality{-2, 0, -1});
    fractional_vertical_segment.push_back(Inequality{0, 1, 10});
    fractional_vertical_segment.push_back(Inequality{0, -1, 10});
    assert(count(fractional_vertical_segment) == 0);

    std::vector<Inequality> empty;
    empty.push_back(Inequality{1, 0, 0});
    empty.push_back(Inequality{-1, 0, -1});
    empty.push_back(Inequality{0, 1, 2});
    empty.push_back(Inequality{0, -1, 2});
    assert(count(empty) == 0);

    std::vector<Inequality> contradiction = triangle;
    contradiction.push_back(Inequality{0, 0, -1});
    assert(count(contradiction) == 0);
}

void test_large_coordinates_and_floor_sum() {
    constexpr long long size = 1000000000000LL;
    std::vector<Inequality> square;
    square.push_back(Inequality{-1, 0, 0});
    square.push_back(Inequality{1, 0, size - 1});
    square.push_back(Inequality{0, -1, 0});
    square.push_back(Inequality{0, 1, size - 1});
    assert(count(square) == __int128(size) * size);

    constexpr long long maximum = std::numeric_limits<long long>::max();
    std::vector<Inequality> long_segment;
    long_segment.push_back(Inequality{1, 0, maximum});
    long_segment.push_back(Inequality{-1, 0, maximum});
    long_segment.push_back(Inequality{0, maximum, 0});
    long_segment.push_back(Inequality{0, -maximum, 0});
    assert(count(long_segment) == __int128(2) * maximum + 1);

    std::vector<Inequality> rational_triangle;
    rational_triangle.push_back(Inequality{-1, 0, 0});
    rational_triangle.push_back(Inequality{1, 0, size});
    rational_triangle.push_back(Inequality{0, -1, 0});
    rational_triangle.push_back(Inequality{2, 3, 3 * size});

    __int128 expected = 0;
    for (long long x = 0; x <= 1000; ++x) {
        expected += (3 * 1000 - 2 * x) / 3 + 1;
    }
    std::vector<Inequality> small_triangle;
    small_triangle.push_back(Inequality{-1, 0, 0});
    small_triangle.push_back(Inequality{1, 0, 1000});
    small_triangle.push_back(Inequality{0, -1, 0});
    small_triangle.push_back(Inequality{2, 3, 3000});
    assert(count(small_triangle) == expected);
    assert(count(rational_triangle) > 0);
}

bool satisfies(const Inequality& inequality, long long x, long long y) {
    return __int128(inequality.a) * x + __int128(inequality.b) * y <=
           inequality.c;
}

void test_randomized_against_naive() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int test = 0; test < 4000; ++test) {
        long long bound = 1 + static_cast<long long>(random() % 8);
        std::vector<Inequality> inequalities;
        inequalities.push_back(Inequality{1, 0, bound});
        inequalities.push_back(Inequality{-1, 0, bound});
        inequalities.push_back(Inequality{0, 1, bound});
        inequalities.push_back(Inequality{0, -1, bound});

        int extra = static_cast<int>(random() % 15);
        for (int index = 0; index < extra; ++index) {
            long long a = static_cast<long long>(random() % 11) - 5;
            long long b = static_cast<long long>(random() % 11) - 5;
            long long c = static_cast<long long>(random() % 31) - 15;
            inequalities.push_back(Inequality{a, b, c});
        }

        long long expected = 0;
        for (long long x = -bound; x <= bound; ++x) {
            for (long long y = -bound; y <= bound; ++y) {
                bool valid = true;
                for (const Inequality& inequality : inequalities) {
                    if (!satisfies(inequality, x, y)) {
                        valid = false;
                        break;
                    }
                }
                expected += valid;
            }
        }
        assert(count(inequalities) == expected);
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_examples_and_degenerate_regions();
    test_large_coordinates_and_floor_sum();
    test_randomized_against_naive();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
