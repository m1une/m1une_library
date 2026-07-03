#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/half_plane_intersection.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

namespace {

using m1une::geometry::Line;
using m1une::geometry::Point;
using PointType = Point<long double>;

std::vector<PointType> clip(
    const std::vector<PointType>& polygon,
    const Line<long double>& half_plane
) {
    std::vector<PointType> result;
    PointType direction = half_plane.b - half_plane.a;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        PointType first = polygon[index];
        PointType second = polygon[(index + 1) % polygon.size()];
        long double first_side = cross(direction, first - half_plane.a);
        long double second_side = cross(direction, second - half_plane.a);
        bool first_inside = first_side >= -1e-12L;
        bool second_inside = second_side >= -1e-12L;
        if (first_inside) result.push_back(first);
        if (first_inside != second_inside) {
            long double ratio = first_side / (first_side - second_side);
            result.push_back(first + (second - first) * ratio);
        }
    }
    return result;
}

long double area(const std::vector<PointType>& polygon) {
    long double result = 0;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        result += cross(
            polygon[index],
            polygon[(index + 1) % polygon.size()]
        );
    }
    return std::fabs(result) / 2;
}

void add_bounding_square(std::vector<Line<long double>>& half_planes) {
    PointType lower_left(-50, -50);
    PointType lower_right(50, -50);
    PointType upper_right(50, 50);
    PointType upper_left(-50, 50);
    half_planes.push_back(Line<long double>{lower_left, lower_right});
    half_planes.push_back(Line<long double>{lower_right, upper_right});
    half_planes.push_back(Line<long double>{upper_right, upper_left});
    half_planes.push_back(Line<long double>{upper_left, lower_left});
}

void test_special_cases() {
    using IntegerPoint = Point<long long>;
    std::vector<Line<long long>> integer_square;
    integer_square.push_back(Line<long long>{IntegerPoint(0, 0), IntegerPoint(2, 0)});
    integer_square.push_back(Line<long long>{IntegerPoint(2, 0), IntegerPoint(2, 2)});
    integer_square.push_back(Line<long long>{IntegerPoint(2, 2), IntegerPoint(0, 2)});
    integer_square.push_back(Line<long long>{IntegerPoint(0, 2), IntegerPoint(0, 0)});
    auto integer_polygon =
        m1une::geometry::half_plane_intersection(integer_square);
    assert(integer_polygon.size() == 4);
    assert(std::fabs(area(integer_polygon) - 4) <= 1e-12L);

    std::vector<Line<long double>> square;
    add_bounding_square(square);
    square.push_back(Line<long double>{PointType(-4, -5), PointType(4, -5)});
    square.push_back(Line<long double>{PointType(-4, -3), PointType(4, -3)});
    auto polygon = m1une::geometry::half_plane_intersection(square);
    assert(polygon.size() == 4);
    assert(std::fabs(area(polygon) - 5300) <= 1e-8L);

    std::vector<Line<long double>> impossible;
    impossible.push_back(Line<long double>{PointType(1, 1), PointType(1, 0)});
    impossible.push_back(Line<long double>{PointType(0, 0), PointType(0, 1)});
    impossible.push_back(Line<long double>{PointType(0, 0), PointType(1, 0)});
    impossible.push_back(Line<long double>{PointType(1, 1), PointType(0, 1)});
    assert(m1une::geometry::half_plane_intersection(impossible).empty());

    std::vector<Line<long double>> unbounded;
    unbounded.push_back(Line<long double>{PointType(0, 0), PointType(1, 0)});
    unbounded.push_back(Line<long double>{PointType(0, 0), PointType(0, -1)});
    unbounded.push_back(Line<long double>{PointType(0, 1), PointType(1, 0)});
    assert(m1une::geometry::half_plane_intersection(unbounded).empty());
}

void test_randomized() {
    std::uint64_t state = 0x5f3759dfULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        std::vector<Line<long double>> half_planes;
        add_bounding_square(half_planes);
        int count = 1 + int(random() % 30);
        for (int index = 0; index < count; ++index) {
            long long dx;
            long long dy;
            do {
                dx = static_cast<long long>(random() % 21) - 10;
                dy = static_cast<long long>(random() % 21) - 10;
            } while (dx == 0 && dy == 0);
            long long offset = 1 + static_cast<long long>(random() % 8);
            PointType first(dy * offset, -dx * offset);
            PointType second(first.x + dx, first.y + dy);
            half_planes.push_back(Line<long double>{first, second});
        }

        std::vector<PointType> expected;
        expected.emplace_back(-50, -50);
        expected.emplace_back(50, -50);
        expected.emplace_back(50, 50);
        expected.emplace_back(-50, 50);
        for (const auto& half_plane : half_planes) {
            expected = clip(expected, half_plane);
        }

        std::shuffle(
            half_planes.begin(),
            half_planes.end(),
            std::mt19937_64(random())
        );
        auto actual = m1une::geometry::half_plane_intersection(half_planes);
        assert(!actual.empty());
        long double expected_area = area(expected);
        long double actual_area = area(actual);
        assert(
            std::fabs(expected_area - actual_area) <=
            1e-8L * std::max(1.0L, expected_area)
        );
        for (const PointType& point : actual) {
            for (const auto& half_plane : half_planes) {
                assert(cross(
                    half_plane.b - half_plane.a,
                    point - half_plane.a
                ) >= -1e-8L);
            }
        }
    }

    for (int trial = 0; trial < 3000; ++trial) {
        std::vector<Line<long double>> half_planes;
        add_bounding_square(half_planes);
        int count = 1 + int(random() % 20);
        for (int index = 0; index < count; ++index) {
            long long dx;
            long long dy;
            do {
                dx = static_cast<long long>(random() % 21) - 10;
                dy = static_cast<long long>(random() % 21) - 10;
            } while (dx == 0 && dy == 0);
            PointType first(
                static_cast<long long>(random() % 121) - 60,
                static_cast<long long>(random() % 121) - 60
            );
            PointType second(first.x + dx, first.y + dy);
            half_planes.push_back(Line<long double>{first, second});
        }

        std::vector<PointType> expected;
        expected.emplace_back(-50, -50);
        expected.emplace_back(50, -50);
        expected.emplace_back(50, 50);
        expected.emplace_back(-50, 50);
        for (const auto& half_plane : half_planes) {
            expected = clip(expected, half_plane);
        }
        std::shuffle(
            half_planes.begin(),
            half_planes.end(),
            std::mt19937_64(random())
        );
        auto actual = m1une::geometry::half_plane_intersection(half_planes);
        long double expected_area = area(expected);
        if (expected_area <= 1e-10L) {
            assert(actual.empty());
        } else {
            assert(!actual.empty());
            assert(
                std::fabs(expected_area - area(actual)) <=
                1e-8L * std::max(1.0L, expected_area)
            );
        }
    }
}

}  // namespace

int main() {
    test_special_cases();
    test_randomized();

    long long a;
    long long b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
