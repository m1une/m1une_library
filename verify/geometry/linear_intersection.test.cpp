#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
#define ERROR "1e-8"

#include "../../geometry/linear.hpp"

#include <cassert>
#include <cmath>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using IntegerLine = Line<long long>;
using IntegerRay = Ray<long long>;
using IntegerSegment = Segment<long long>;
using P = Point<long long>;
using FloatingPoint = Point<long double>;

bool close(const FloatingPoint& first, const FloatingPoint& second) {
    return distance(first, second) <= 1e-9L;
}

Line<long double> floating(const IntegerLine& line) {
    Line<long double> result;
    result.a = FloatingPoint(line.a);
    result.b = FloatingPoint(line.b);
    return result;
}

Segment<long double> floating(const IntegerSegment& segment) {
    Segment<long double> result;
    result.a = FloatingPoint(segment.a);
    result.b = FloatingPoint(segment.b);
    return result;
}

Ray<long double> floating(const IntegerRay& ray) {
    Ray<long double> result;
    result.origin = FloatingPoint(ray.origin);
    result.through = FloatingPoint(ray.through);
    return result;
}

bool contains(const Line<long double>& line, const FloatingPoint& point) {
    return on_line(line, point, 1e-9L);
}

bool contains(
    const Segment<long double>& segment,
    const FloatingPoint& point
) {
    return on_segment(segment, point, 1e-9L);
}

bool contains(const Ray<long double>& ray, const FloatingPoint& point) {
    return on_ray(ray, point, 1e-9L);
}

template <class First, class Second>
void verify_result(const First& first, const Second& second) {
    const LinearIntersection result = linear_intersection(first, second);
    const LinearIntersection reversed = linear_intersection(second, first);
    assert(result.kind == reversed.kind);
    assert(
        (result.kind != LinearIntersectionKind::Empty) ==
        intersects(first, second)
    );

    if (result.kind == LinearIntersectionKind::Empty) return;
    const auto floating_first = floating(first);
    const auto floating_second = floating(second);
    assert(contains(floating_first, result.first));
    assert(contains(floating_second, result.first));
    assert(contains(floating_first, result.second));
    assert(contains(floating_second, result.second));

    if (result.kind == LinearIntersectionKind::Point) {
        assert(close(result.first, result.second));
        return;
    }

    assert(!close(result.first, result.second));
    const FloatingPoint direction = result.second - result.first;
    if (result.kind == LinearIntersectionKind::Segment) {
        const FloatingPoint middle =
            (result.first + result.second) / 2.0L;
        assert(contains(floating_first, middle));
        assert(contains(floating_second, middle));
        return;
    }
    if (result.kind == LinearIntersectionKind::Ray) {
        const FloatingPoint forward = result.second + direction;
        assert(contains(floating_first, forward));
        assert(contains(floating_second, forward));
        return;
    }
    assert(result.kind == LinearIntersectionKind::Line);
    const FloatingPoint before = result.first - direction;
    const FloatingPoint after = result.second + direction;
    assert(contains(floating_first, before));
    assert(contains(floating_second, before));
    assert(contains(floating_first, after));
    assert(contains(floating_second, after));
}

IntegerLine make_line(long long ax, long long ay, long long bx, long long by) {
    IntegerLine result;
    result.a = P(ax, ay);
    result.b = P(bx, by);
    return result;
}

IntegerSegment make_segment(
    long long ax,
    long long ay,
    long long bx,
    long long by
) {
    IntegerSegment result;
    result.a = P(ax, ay);
    result.b = P(bx, by);
    return result;
}

IntegerRay make_ray(long long ox, long long oy, long long tx, long long ty) {
    IntegerRay result;
    result.origin = P(ox, oy);
    result.through = P(tx, ty);
    return result;
}

void test_each_topology() {
    const IntegerLine horizontal = make_line(0, 0, 1, 0);
    const IntegerLine same_line = make_line(-2, 0, 3, 0);
    const IntegerLine parallel_line = make_line(0, 1, 1, 1);
    const IntegerLine vertical = make_line(0, -1, 0, 1);
    assert(
        linear_intersection(horizontal, same_line).kind ==
        LinearIntersectionKind::Line
    );
    assert(
        linear_intersection(horizontal, parallel_line).kind ==
        LinearIntersectionKind::Empty
    );
    assert(
        linear_intersection(horizontal, vertical).kind ==
        LinearIntersectionKind::Point
    );

    const IntegerSegment overlap = make_segment(-1, 0, 2, 0);
    const IntegerSegment crossing = make_segment(0, -2, 0, 2);
    assert(
        linear_intersection(horizontal, overlap).kind ==
        LinearIntersectionKind::Segment
    );
    assert(
        linear_intersection(overlap, crossing).kind ==
        LinearIntersectionKind::Point
    );

    const IntegerRay right = make_ray(0, 0, 1, 0);
    const IntegerRay later_right = make_ray(2, 0, 3, 0);
    const IntegerRay facing = make_ray(4, 0, 3, 0);
    const IntegerRay left_from_origin = make_ray(0, 0, -1, 0);
    const IntegerRay diverging = make_ray(-2, 0, -3, 0);
    assert(
        linear_intersection(horizontal, right).kind ==
        LinearIntersectionKind::Ray
    );
    assert(
        linear_intersection(right, later_right).kind ==
        LinearIntersectionKind::Ray
    );
    assert(
        linear_intersection(right, facing).kind ==
        LinearIntersectionKind::Segment
    );
    assert(
        linear_intersection(right, left_from_origin).kind ==
        LinearIntersectionKind::Point
    );
    assert(
        linear_intersection(right, diverging).kind ==
        LinearIntersectionKind::Empty
    );
}

void test_exhaustive_small_integer_objects() {
    std::vector<P> points;
    for (long long x = -1; x <= 1; ++x) {
        for (long long y = -1; y <= 1; ++y) {
            points.emplace_back(x, y);
        }
    }

    std::vector<IntegerLine> lines;
    std::vector<IntegerSegment> segments;
    std::vector<IntegerRay> rays;
    for (const P& first : points) {
        for (const P& second : points) {
            IntegerSegment segment;
            segment.a = first;
            segment.b = second;
            segments.push_back(segment);
            if (first == second) continue;

            IntegerLine line;
            line.a = first;
            line.b = second;
            lines.push_back(line);

            IntegerRay ray;
            ray.origin = first;
            ray.through = second;
            rays.push_back(ray);
        }
    }

    for (const IntegerLine& first : lines) {
        for (const IntegerLine& second : lines) {
            verify_result(first, second);
        }
        for (const IntegerSegment& segment : segments) {
            verify_result(first, segment);
        }
        for (const IntegerRay& ray : rays) {
            verify_result(first, ray);
        }
    }
    for (const IntegerSegment& first : segments) {
        for (const IntegerSegment& second : segments) {
            verify_result(first, second);
        }
        for (const IntegerRay& ray : rays) {
            verify_result(first, ray);
        }
    }
    for (const IntegerRay& first : rays) {
        for (const IntegerRay& second : rays) {
            verify_result(first, second);
        }
    }
}

}  // namespace

int main() {
    test_each_topology();
    test_exhaustive_small_integer_objects();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    fast_output.set_fixed(15);

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        Segment<long double> first;
        Segment<long double> second;
        fast_input >> first.a.x >> first.a.y >> first.b.x >> first.b.y;
        fast_input >> second.a.x >> second.a.y >> second.b.x >> second.b.y;
        const LinearIntersection result = linear_intersection(first, second);
        assert(result.kind == LinearIntersectionKind::Point);
        fast_output << result.first.x << ' ' << result.first.y << '\n';
    }
}
