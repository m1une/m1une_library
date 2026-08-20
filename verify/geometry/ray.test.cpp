#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/linear.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;
using IntegerRay = Ray<long long>;
using IntegerLine = Line<long long>;
using IntegerSegment = Segment<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-10L;
}

IntegerSegment long_segment(const IntegerRay& ray) {
    P direction = ray.through - ray.origin;
    IntegerSegment result;
    result.a = ray.origin;
    result.b = ray.origin + direction * 1000;
    return result;
}

void test_line_segment() {
    IntegerLine horizontal;
    horizontal.a = P(0, 0);
    horizontal.b = P(1, 0);

    IntegerSegment crossing;
    crossing.a = P(2, -3);
    crossing.b = P(2, 4);
    assert(intersects(horizontal, crossing));
    assert(intersects(crossing, horizontal));
    assert(close(distance(horizontal, crossing), 0));
    LinearIntersection point = linear_intersection(horizontal, crossing);
    assert(point.kind == LinearIntersectionKind::Point);
    assert(close(point.first.x, 2));
    assert(close(point.first.y, 0));

    IntegerSegment above;
    above.a = P(-1, 3);
    above.b = P(4, 3);
    assert(!intersects(horizontal, above));
    assert(close(distance(horizontal, above), 3));
    assert(close(distance(above, horizontal), 3));
    assert(
        linear_intersection(horizontal, above).kind ==
        LinearIntersectionKind::Empty
    );

    IntegerSegment overlapping;
    overlapping.a = P(2, 0);
    overlapping.b = P(5, 0);
    assert(intersects(horizontal, overlapping));
    assert(close(distance(horizontal, overlapping), 0));
    assert(
        linear_intersection(horizontal, overlapping).kind ==
        LinearIntersectionKind::Segment
    );

    IntegerSegment point_segment;
    point_segment.a = P(7, 0);
    point_segment.b = point_segment.a;
    const LinearIntersection degenerate =
        linear_intersection(horizontal, point_segment);
    assert(degenerate.kind == LinearIntersectionKind::Point);
    assert(close(degenerate.first.x, 7));
}

void test_ray_point_and_line() {
    IntegerRay ray;
    ray.origin = P(0, 0);
    ray.through = P(2, 0);

    assert(on_ray(ray, P(0, 0)));
    assert(on_ray(ray, P(5, 0)));
    assert(!on_ray(ray, P(-1, 0)));
    assert(!on_ray(ray, P(1, 1)));
    assert(close(distance(ray, P(-3, 4)), 5));
    assert(close(distance(P(-3, 4), ray), 5));

    Point<long double> projected = projection(ray, P(-3, 4));
    assert(close(projected.x, 0));
    assert(close(projected.y, 0));

    IntegerLine ahead;
    ahead.a = P(3, -2);
    ahead.b = P(3, 2);
    assert(intersects(ray, ahead));
    assert(close(distance(ray, ahead), 0));
    LinearIntersection hit = linear_intersection(ray, ahead);
    assert(hit.kind == LinearIntersectionKind::Point);
    assert(close(hit.first.x, 3));
    assert(close(hit.first.y, 0));

    IntegerLine behind;
    behind.a = P(-3, -2);
    behind.b = P(-3, 2);
    assert(!intersects(ray, behind));
    assert(close(distance(ray, behind), 3));
    assert(
        linear_intersection(ray, behind).kind ==
        LinearIntersectionKind::Empty
    );

    IntegerLine parallel_line;
    parallel_line.a = P(0, 4);
    parallel_line.b = P(1, 4);
    assert(!intersects(ray, parallel_line));
    assert(close(distance(ray, parallel_line), 4));

    IntegerLine supporting;
    supporting.a = P(-10, 0);
    supporting.b = P(10, 0);
    assert(intersects(ray, supporting));
    assert(
        linear_intersection(ray, supporting).kind ==
        LinearIntersectionKind::Ray
    );
}

void test_ray_segment() {
    IntegerRay ray;
    ray.origin = P(0, 0);
    ray.through = P(1, 0);

    IntegerSegment crossing;
    crossing.a = P(3, -2);
    crossing.b = P(3, 2);
    assert(intersects(ray, crossing));
    assert(intersects(crossing, ray));
    LinearIntersection hit = linear_intersection(ray, crossing);
    assert(hit.kind == LinearIntersectionKind::Point);
    assert(close(hit.first.x, 3));
    assert(close(hit.first.y, 0));

    IntegerSegment behind;
    behind.a = P(-4, -2);
    behind.b = P(-4, 2);
    assert(!intersects(ray, behind));
    assert(close(distance(ray, behind), 4));

    IntegerSegment overlap;
    overlap.a = P(-2, 0);
    overlap.b = P(5, 0);
    assert(intersects(ray, overlap));
    assert(
        linear_intersection(ray, overlap).kind ==
        LinearIntersectionKind::Segment
    );

    IntegerSegment touching_origin;
    touching_origin.a = P(-2, 0);
    touching_origin.b = P(0, 0);
    const LinearIntersection endpoint_hit =
        linear_intersection(ray, touching_origin);
    assert(endpoint_hit.kind == LinearIntersectionKind::Point);
    assert(close(endpoint_hit.first.x, 0));
    assert(close(endpoint_hit.first.y, 0));

    IntegerSegment separated;
    separated.a = P(-3, 4);
    separated.b = P(-1, 4);
    assert(!intersects(ray, separated));
    assert(close(distance(ray, separated), std::sqrt(17.0L)));
    assert(close(distance(separated, ray), std::sqrt(17.0L)));
}

void test_ray_ray() {
    IntegerRay horizontal;
    horizontal.origin = P(0, 0);
    horizontal.through = P(1, 0);

    IntegerRay vertical;
    vertical.origin = P(3, -2);
    vertical.through = P(3, -1);
    assert(intersects(horizontal, vertical));
    LinearIntersection crossing = linear_intersection(horizontal, vertical);
    assert(crossing.kind == LinearIntersectionKind::Point);
    assert(close(crossing.first.x, 3));
    assert(close(crossing.first.y, 0));

    IntegerRay diverging;
    diverging.origin = P(-2, 0);
    diverging.through = P(-3, 0);
    assert(!intersects(horizontal, diverging));
    assert(close(distance(horizontal, diverging), 2));
    assert(
        linear_intersection(horizontal, diverging).kind ==
        LinearIntersectionKind::Empty
    );

    IntegerRay facing;
    facing.origin = P(4, 0);
    facing.through = P(3, 0);
    assert(intersects(horizontal, facing));
    assert(close(distance(horizontal, facing), 0));
    assert(
        linear_intersection(horizontal, facing).kind ==
        LinearIntersectionKind::Segment
    );

    IntegerRay opposite_at_origin;
    opposite_at_origin.origin = P(0, 0);
    opposite_at_origin.through = P(-1, 0);
    const LinearIntersection origin_hit =
        linear_intersection(horizontal, opposite_at_origin);
    assert(origin_hit.kind == LinearIntersectionKind::Point);
    assert(close(origin_hit.first.x, 0));
    assert(close(origin_hit.first.y, 0));

    IntegerRay offset;
    offset.origin = P(-2, 3);
    offset.through = P(-3, 3);
    assert(!intersects(horizontal, offset));
    assert(close(distance(horizontal, offset), std::sqrt(13.0L)));
}

void test_randomized_against_long_segments() {
    std::uint64_t state = 0x18273645abcdefULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto random_point = [&]() {
        return P(
            static_cast<long long>(random() % 11) - 5,
            static_cast<long long>(random() % 11) - 5
        );
    };

    for (int trial = 0; trial < 20000; ++trial) {
        IntegerRay first;
        first.origin = random_point();
        do {
            first.through = random_point();
        } while (first.origin == first.through);

        IntegerRay second;
        second.origin = random_point();
        do {
            second.through = random_point();
        } while (second.origin == second.through);

        IntegerSegment segment;
        segment.a = random_point();
        segment.b = random_point();

        IntegerLine line;
        line.a = random_point();
        do {
            line.b = random_point();
        } while (line.a == line.b);

        IntegerSegment first_long = long_segment(first);
        IntegerSegment second_long = long_segment(second);

        assert(intersects(first, segment) == intersects(first_long, segment));
        assert(intersects(first, second) == intersects(first_long, second_long));
        assert(intersects(first, line) == intersects(line, first_long));

        assert(close(distance(first, segment), distance(first_long, segment)));
        assert(close(distance(first, second), distance(first_long, second_long)));
        assert(close(distance(first, line), distance(line, first_long)));

        assert(intersects(first, segment) == intersects(segment, first));
        assert(close(distance(first, segment), distance(segment, first)));
        assert(close(distance(first, line), distance(line, first)));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_line_segment();
    test_ray_point_and_line();
    test_ray_segment();
    test_ray_ray();
    test_randomized_against_long_segments();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
