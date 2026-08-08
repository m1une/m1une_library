#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle_coverage_areas.hpp"
#include "../../geometry/circle_union_area.hpp"

#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numbers>
#include <numeric>
#include <vector>

namespace {

using m1une::geometry::Circle;
using m1une::geometry::Point;
using m1une::geometry::circle_area;
using m1une::geometry::circle_circle_intersection_area;
using m1une::geometry::circle_coverage_areas;
using m1une::geometry::circle_union_area;

bool close(long double first, long double second, long double eps = 1e-9L) {
    return std::fabs(first - second) <=
        eps * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

void test_edge_cases() {
    const long double pi = std::numbers::pi_v<long double>;
    std::vector<Circle<long double>> circles;
    assert(circle_coverage_areas(circles) == std::vector<long double>(1, 0));

    circles.push_back(Circle<long double>{Point<long double>(0, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(1, 0), 1});
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 0});
    std::vector<long double> area = circle_coverage_areas(circles);
    assert(area.size() == 5);
    assert(close(area[1], 0));
    assert(close(area[2], 8.0L * pi));
    assert(close(area[3], pi));
    assert(close(area[4], 0));

    circles.clear();
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 2});
    circles.push_back(Circle<long double>{Point<long double>(4, 0), 2});
    area = circle_coverage_areas(circles);
    assert(close(area[1], 8.0L * pi));
    assert(close(area[2], 0));
}

void test_two_circles_randomized() {
    std::uint64_t state = 1618033988ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; ++trial) {
        Circle<long double> first;
        Circle<long double> second;
        first.center = Point<long double>(
            static_cast<long double>(int(random() % 41) - 20) / 4.0L,
            static_cast<long double>(int(random() % 41) - 20) / 4.0L
        );
        second.center = Point<long double>(
            static_cast<long double>(int(random() % 41) - 20) / 4.0L,
            static_cast<long double>(int(random() % 41) - 20) / 4.0L
        );
        first.radius = static_cast<long double>(random() % 20 + 1) / 4.0L;
        second.radius = static_cast<long double>(random() % 20 + 1) / 4.0L;
        std::vector<Circle<long double>> circles = {first, second};
        std::vector<long double> area = circle_coverage_areas(circles);
        long double intersection =
            circle_circle_intersection_area(first, second);
        assert(close(area[2], intersection));
        assert(close(
            area[1],
            circle_area(first) + circle_area(second) - 2.0L * intersection
        ));
    }
}

void test_randomized_invariants() {
    std::uint64_t state = 5772156649ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; ++trial) {
        int count = int(random() % 9);
        std::vector<Circle<long double>> circles(count);
        long double area_with_multiplicity = 0.0L;
        for (Circle<long double>& circle : circles) {
            circle.center = Point<long double>(
                static_cast<long double>(int(random() % 25) - 12) / 3.0L,
                static_cast<long double>(int(random() % 25) - 12) / 3.0L
            );
            circle.radius =
                static_cast<long double>(random() % 13) / 3.0L;
            area_with_multiplicity += circle_area(circle);
        }
        std::vector<long double> area = circle_coverage_areas(circles);
        long double union_area =
            std::accumulate(area.begin() + 1, area.end(), 0.0L);
        long double weighted_area = 0.0L;
        for (int coverage = 1; coverage <= count; ++coverage) {
            weighted_area += coverage * area[coverage];
        }
        assert(close(union_area, circle_union_area(circles), 1e-8L));
        assert(close(weighted_area, area_with_multiplicity, 1e-8L));
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_two_circles_randomized();
    test_randomized_invariants();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first = 0, second = 0;
    input.read(first, second);
    output.println(first + second);
}
