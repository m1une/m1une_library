#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numbers>
#include <vector>
#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;

bool close(long double first, long double second, long double eps = 1e-9L) {
    long double scale = std::max({1.0L, std::fabs(first), std::fabs(second)});
    return std::fabs(first - second) <= eps * scale;
}

void test_basic_queries() {
    Circle<long long> circle;
    circle.center = Point<long long>(2, -1);
    circle.radius = 5;
    assert(point_in_circle(circle, Point<int>(2, -1)) == PointInCircle::Inside);
    assert(point_in_circle(circle, Point<int>(5, 3)) == PointInCircle::Boundary);
    assert(point_in_circle(circle, Point<int>(8, -1)) == PointInCircle::Outside);
    assert(contains(circle, Point<int>(5, 3)));
    assert(on_circle(circle, Point<int>(5, 3)));
    assert(close(circle_area(circle), 25.0L * std::numbers::pi_v<long double>));
    assert(close(
        circle_circumference(circle),
        10.0L * std::numbers::pi_v<long double>
    ));

    Circle<int> first;
    first.center = Point<int>(0, 0);
    first.radius = 5;
    Circle<long long> second;
    second.center = Point<long long>(9, 0);
    second.radius = 4;
    assert(circle_relation(first, second) == CircleRelation::ExternallyTangent);
    assert(intersects(first, second));
    second.center.x = 1;
    second.radius = 2;
    assert(circle_relation(first, second) == CircleRelation::Contained);
    assert(!intersects(first, second));
}

void test_constructions() {
    auto diameter = circle_from_diameter(
        Point<int>(-2, 3),
        Point<long long>(4, -5)
    );
    assert(close(diameter.center.x, 1));
    assert(close(diameter.center.y, -1));
    assert(close(diameter.radius, 5));

    Point<long long> first(0, 0);
    Point<long long> second(6, 0);
    Point<long long> third(0, 8);
    auto inner = incircle(first, second, third);
    assert(inner.has_value());
    assert(close(inner->center.x, 2));
    assert(close(inner->center.y, 2));
    assert(close(inner->radius, 2));

    auto outer = circumcircle(first, second, third);
    assert(outer.has_value());
    assert(close(outer->center.x, 3));
    assert(close(outer->center.y, 4));
    assert(close(outer->radius, 5));
    assert(!incircle(first, second, Point<long long>(12, 0)).has_value());
    assert(!circumcircle(first, second, Point<long long>(12, 0)).has_value());
}

void test_linear_intersections() {
    Circle<int> circle;
    circle.center = Point<int>(0, 0);
    circle.radius = 5;

    Line<long double> line;
    line.a = Point<long double>(-10, 0);
    line.b = Point<long double>(10, 0);
    auto points = circle_line_intersections(line, circle);
    assert(points.size() == 2);
    assert(close(points[0].x, -5));
    assert(close(points[1].x, 5));
    assert(intersects(line, circle));

    Segment<long long> crossing;
    crossing.a = Point<long long>(10, 0);
    crossing.b = Point<long long>(-2, 0);
    points = circle_segment_intersections(circle, crossing);
    assert(points.size() == 1);
    assert(close(points[0].x, 5));

    Segment<long long> chord;
    chord.a = Point<long long>(10, 0);
    chord.b = Point<long long>(-10, 0);
    points = circle_segment_intersections(chord, circle);
    assert(points.size() == 2);
    assert(close(points[0].x, 5));
    assert(close(points[1].x, -5));

    Segment<long long> point_segment;
    point_segment.a = Point<long long>(0, 5);
    point_segment.b = point_segment.a;
    assert(circle_segment_intersections(circle, point_segment).size() == 1);
    point_segment.a = Point<long long>(0, 0);
    point_segment.b = point_segment.a;
    assert(circle_segment_intersections(circle, point_segment).empty());
}

void test_tangents() {
    Circle<long long> circle;
    circle.center = Point<long long>(0, 0);
    circle.radius = 5;
    Point<long long> external(13, 0);
    auto points = tangent_points(circle, external);
    assert(points.size() == 2);
    for (const Point<long double>& point : points) {
        Point<long double> radius = point - Point<long double>(circle.center);
        Point<long double> tangent = Point<long double>(external) - point;
        assert(close(
            norm(radius),
            static_cast<long double>(circle.radius)
        ));
        assert(close(dot(radius, tangent), 0));
    }
    assert(tangent_points(circle, Point<long long>(0, 0)).empty());
    assert(tangent_points(circle, Point<long long>(5, 0)).size() == 1);

    Circle<long long> point_circle;
    point_circle.center = Point<long long>(7, 4);
    point_circle.radius = 0;
    points = tangent_points(point_circle, Point<long long>(1, 2));
    assert(points.size() == 1);
    assert(close(points[0].x, 7));
    assert(close(points[0].y, 4));
}

void test_common_tangents_randomized() {
    std::uint64_t state = 0x319642b2d24d8ec3ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 10000; ++trial) {
        Circle<long long> first;
        Circle<long long> second;
        first.center = Point<long long>(
            static_cast<long long>(random() % 41) - 20,
            static_cast<long long>(random() % 41) - 20
        );
        second.center = Point<long long>(
            static_cast<long long>(random() % 41) - 20,
            static_cast<long long>(random() % 41) - 20
        );
        first.radius = static_cast<long long>(random() % 10) + 1;
        second.radius = static_cast<long long>(random() % 10) + 1;
        if (first.center == second.center && first.radius == second.radius) {
            continue;
        }

        CircleRelation relation = circle_relation(first, second);
        int expected = 0;
        if (relation == CircleRelation::Separate) expected = 4;
        if (relation == CircleRelation::ExternallyTangent) expected = 3;
        if (relation == CircleRelation::Intersecting) expected = 2;
        if (relation == CircleRelation::InternallyTangent) expected = 1;
        auto tangents = common_tangents(first, second);
        assert(int(tangents.size()) == expected);
        assert(common_tangent_points(first, second).size() == tangents.size());
        for (const Line<long double>& tangent : tangents) {
            assert(close(
                distance(tangent, Point<long double>(first.center)),
                static_cast<long double>(first.radius)
            ));
            assert(close(
                distance(tangent, Point<long double>(second.center)),
                static_cast<long double>(second.radius)
            ));
            assert(on_circle(first, tangent.a, 1e-9L));
        }
    }
}

void test_triangle_circles_randomized() {
    std::uint64_t state = 0x94d049bb133111ebULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 5000; ++trial) {
        Point<long long> first(
            static_cast<long long>(random() % 31) - 15,
            static_cast<long long>(random() % 31) - 15
        );
        Point<long long> second(
            static_cast<long long>(random() % 31) - 15,
            static_cast<long long>(random() % 31) - 15
        );
        Point<long long> third(
            static_cast<long long>(random() % 31) - 15,
            static_cast<long long>(random() % 31) - 15
        );
        if (orientation(first, second, third) == 0) continue;

        auto outer = circumcircle(first, second, third);
        assert(outer.has_value());
        assert(close(
            distance(outer->center, Point<long double>(first)),
            outer->radius
        ));
        assert(close(
            distance(outer->center, Point<long double>(second)),
            outer->radius
        ));
        assert(close(
            distance(outer->center, Point<long double>(third)),
            outer->radius
        ));

        auto inner = incircle(first, second, third);
        assert(inner.has_value());
        Line<long double> first_side;
        first_side.a = Point<long double>(first);
        first_side.b = Point<long double>(second);
        Line<long double> second_side;
        second_side.a = Point<long double>(second);
        second_side.b = Point<long double>(third);
        Line<long double> third_side;
        third_side.a = Point<long double>(third);
        third_side.b = Point<long double>(first);
        assert(close(distance(first_side, inner->center), inner->radius));
        assert(close(distance(second_side, inner->center), inner->radius));
        assert(close(distance(third_side, inner->center), inner->radius));
    }
}

void test_intersection_areas() {
    Circle<long double> first;
    first.center = Point<long double>(0, 0);
    first.radius = 1;
    Circle<long double> second = first;
    assert(close(
        circle_circle_intersection_area(first, second),
        std::numbers::pi_v<long double>
    ));
    second.center.x = 1;
    long double expected =
        2.0L * std::numbers::pi_v<long double> / 3.0L -
        std::sqrt(3.0L) / 2.0L;
    assert(close(circle_circle_intersection_area(first, second), expected));
    assert(close(circle_circle_intersection_area(second, first), expected));
    second.center.x = 3;
    assert(close(circle_circle_intersection_area(first, second), 0));
    second.center.x = 0;
    second.radius = 2;
    assert(close(
        circle_circle_intersection_area(first, second),
        std::numbers::pi_v<long double>
    ));

    std::vector<Point<long double>> square;
    square.emplace_back(-2, -2);
    square.emplace_back(2, -2);
    square.emplace_back(2, 2);
    square.emplace_back(-2, 2);
    assert(close(
        circle_polygon_intersection_area(first, square),
        std::numbers::pi_v<long double>
    ));
    std::reverse(square.begin(), square.end());
    assert(close(
        circle_polygon_intersection_area(first, square),
        std::numbers::pi_v<long double>
    ));

    std::vector<Point<long double>> half_disk_box;
    half_disk_box.emplace_back(0, -2);
    half_disk_box.emplace_back(2, -2);
    half_disk_box.emplace_back(2, 2);
    half_disk_box.emplace_back(0, 2);
    assert(close(
        circle_polygon_intersection_area(first, half_disk_box),
        std::numbers::pi_v<long double> / 2.0L
    ));

    std::vector<Point<long double>> small_square;
    small_square.emplace_back(-0.25L, -0.25L);
    small_square.emplace_back(0.25L, -0.25L);
    small_square.emplace_back(0.25L, 0.25L);
    small_square.emplace_back(-0.25L, 0.25L);
    assert(close(circle_polygon_intersection_area(first, small_square), 0.25L));
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_basic_queries();
    test_constructions();
    test_linear_intersections();
    test_tangents();
    test_common_tangents_randomized();
    test_triangle_circles_randomized();
    test_intersection_areas();

    long long first, second;
    fast_input >> first >> second;
    fast_output << first + second << '\n';
}
