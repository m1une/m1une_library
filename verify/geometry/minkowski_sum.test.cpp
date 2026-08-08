#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/convex_hull.hpp"
#include "../../geometry/minkowski_sum.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

namespace {

using m1une::geometry::Point;
using PointType = Point<long long>;

std::vector<PointType> brute_sum(
    const std::vector<PointType>& first,
    const std::vector<PointType>& second
) {
    std::vector<PointType> sums;
    sums.reserve(first.size() * second.size());
    for (const PointType& left : first) {
        for (const PointType& right : second) {
            sums.push_back(left + right);
        }
    }
    return m1une::geometry::convex_hull(std::move(sums));
}

void test_fixed() {
    std::vector<PointType> square;
    square.emplace_back(0, 0);
    square.emplace_back(2, 0);
    square.emplace_back(2, 2);
    square.emplace_back(0, 2);

    std::vector<PointType> triangle;
    triangle.emplace_back(0, 0);
    triangle.emplace_back(3, 0);
    triangle.emplace_back(0, 1);
    assert(
        m1une::geometry::minkowski_sum(square, triangle) ==
        brute_sum(square, triangle)
    );

    std::reverse(square.begin(), square.end());
    triangle.push_back(triangle.front());
    assert(
        m1une::geometry::minkowski_sum(square, triangle) ==
        brute_sum(square, triangle)
    );

    std::vector<PointType> segment;
    segment.emplace_back(3, 0);
    segment.emplace_back(0, 0);
    std::vector<PointType> point;
    point.emplace_back(2, 4);
    std::vector<PointType> expected;
    expected.emplace_back(2, 4);
    expected.emplace_back(5, 4);
    assert(m1une::geometry::minkowski_sum(segment, point) == expected);

    std::vector<PointType> redundant;
    redundant.emplace_back(0, 0);
    redundant.emplace_back(1, 0);
    redundant.emplace_back(2, 0);
    redundant.emplace_back(2, 2);
    redundant.emplace_back(0, 2);
    redundant.emplace_back(0, 0);
    assert(
        m1une::geometry::minkowski_sum(redundant, point) ==
        brute_sum(redundant, point)
    );
}

void test_randomized() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        std::vector<PointType> first_points;
        std::vector<PointType> second_points;
        const int first_size = 1 + int(random() % 12);
        const int second_size = 1 + int(random() % 12);
        for (int index = 0; index < first_size; ++index) {
            first_points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        for (int index = 0; index < second_size; ++index) {
            second_points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        std::vector<PointType> first =
            m1une::geometry::convex_hull(first_points);
        std::vector<PointType> second =
            m1une::geometry::convex_hull(second_points);
        if (random() & 1) std::reverse(first.begin(), first.end());
        if (random() & 1) std::reverse(second.begin(), second.end());

        const std::vector<PointType> expected = brute_sum(first, second);
        const std::vector<PointType> actual =
            m1une::geometry::minkowski_sum(first, second);
        assert(m1une::geometry::convex_hull(actual) == expected);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    long long first;
    long long second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
