#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle_union_area.hpp"

#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <numbers>
#include <vector>

namespace {

using m1une::geometry::Circle;
using m1une::geometry::Point;
using m1une::geometry::circle_circle_intersection_area;
using m1une::geometry::circle_union_area;

bool close(long double first, long double second, long double eps = 1e-10L) {
    return std::fabs(first - second) <=
        eps * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

void test_edge_cases() {
    const long double pi = std::numbers::pi_v<long double>;
    std::vector<Circle<long double>> circles;
    assert(circle_union_area(circles) == 0.0L);

    circles.push_back(Circle<long double>{Point<long double>(3, -4), 0});
    assert(circle_union_area(circles) == 0.0L);

    circles.push_back(Circle<long double>{Point<long double>(0, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(1, 0), 1});
    assert(close(circle_union_area(circles), 9.0L * pi));

    circles.clear();
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 2});
    circles.push_back(Circle<long double>{Point<long double>(4, 0), 2});
    circles.push_back(Circle<long double>{Point<long double>(0, 7), 1});
    assert(close(circle_union_area(circles), 9.0L * pi));
}

void test_two_circles_randomized() {
    std::uint64_t state = 2718281828ULL;
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
        long double expected =
            m1une::geometry::circle_area(first) +
            m1une::geometry::circle_area(second) -
            circle_circle_intersection_area(first, second);
        assert(close(circle_union_area(circles), expected, 1e-9L));
    }
}

void test_translation_invariance() {
    std::vector<Circle<long double>> circles;
    circles.push_back(Circle<long double>{Point<long double>(0, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(3, 0), 3});
    circles.push_back(Circle<long double>{Point<long double>(1, 4), 2});
    long double expected = circle_union_area(circles);
    for (Circle<long double>& circle : circles) {
        circle.center.x += 1.0e8L;
        circle.center.y -= 2.0e8L;
    }
    assert(close(circle_union_area(circles), expected, 1e-8L));
}

void test_multiple_covered_arcs() {
    const long double side = 1.9L;
    const long double height = side * std::sqrt(3.0L) / 2.0L;
    std::vector<Circle<long double>> circles(3);
    circles[0] = Circle<long double>{Point<long double>(0, 0), 1};
    circles[1] = Circle<long double>{Point<long double>(side, 0), 1};
    circles[2] = Circle<long double>{
        Point<long double>(side / 2.0L, height),
        1
    };
    long double pair_intersection =
        circle_circle_intersection_area(circles[0], circles[1]);
    long double expected =
        3.0L * std::numbers::pi_v<long double> -
        3.0L * pair_intersection;
    assert(close(circle_union_area(circles), expected));
}

}  // namespace

int main() {
    test_edge_cases();
    test_two_circles_randomized();
    test_translation_invariance();
    test_multiple_covered_arcs();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first = 0, second = 0;
    input.read(first, second);
    output.println(first + second);
}
