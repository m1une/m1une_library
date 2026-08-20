#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D"
#define ERROR "1e-8"

#include "../../geometry/linear.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using IntegerLine = Line<long long>;
using IntegerRay = Ray<long long>;
using IntegerSegment = Segment<long long>;
using P = Point<long long>;
using FloatingPoint = Point<long double>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-9L;
}

bool close(const FloatingPoint& first, const FloatingPoint& second) {
    return distance(first, second) <= 1e-9L;
}

FloatingPoint floating(const P& point) {
    return FloatingPoint(point);
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

bool contains(const FloatingPoint& object, const FloatingPoint& point) {
    return close(object, point);
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
void verify_closest(const First& first, const Second& second) {
    const ClosestPoints result = closest_points(first, second);
    const ClosestPoints reversed = closest_points(second, first);
    const auto floating_first = floating(first);
    const auto floating_second = floating(second);

    assert(contains(floating_first, result.first));
    assert(contains(floating_second, result.second));
    assert(contains(floating_first, reversed.second));
    assert(contains(floating_second, reversed.first));
    assert(close(result.first, reversed.second));
    assert(close(result.second, reversed.first));

    const long double witness_distance =
        m1une::geometry::distance(result.first, result.second);
    assert(close(witness_distance, distance(first, second)));

    if constexpr (requires { linear_intersection(first, second); }) {
        const bool has_intersection =
            linear_intersection(first, second).kind !=
            LinearIntersectionKind::Empty;
        assert((witness_distance <= 1e-9L) == has_intersection);
    }
}

void test_examples() {
    IntegerSegment segment;
    segment.a = P(0, 0);
    segment.b = P(2, 0);
    IntegerRay ray;
    ray.origin = P(5, 3);
    ray.through = P(6, 3);
    const ClosestPoints separated = closest_points(segment, ray);
    assert(close(separated.first, FloatingPoint(2, 0)));
    assert(close(separated.second, FloatingPoint(5, 3)));

    IntegerLine horizontal;
    horizontal.a = P(0, 0);
    horizontal.b = P(1, 0);
    IntegerLine vertical;
    vertical.a = P(3, -1);
    vertical.b = P(3, 1);
    const ClosestPoints crossing = closest_points(horizontal, vertical);
    assert(close(crossing.first, FloatingPoint(3, 0)));
    assert(close(crossing.first, crossing.second));

    IntegerSegment first_overlap;
    first_overlap.a = P(4, 0);
    first_overlap.b = P(1, 0);
    IntegerSegment second_overlap;
    second_overlap.a = P(2, 0);
    second_overlap.b = P(6, 0);
    const ClosestPoints overlap =
        closest_points(first_overlap, second_overlap);
    assert(close(overlap.first, FloatingPoint(2, 0)));
    assert(close(overlap.first, overlap.second));
}

void test_scale_invariance() {
    const long double scales[] = {1e-20L, 1.0L, 1e20L};
    for (const long double scale : scales) {
        Segment<long double> segment;
        segment.a = FloatingPoint(0, 0);
        segment.b = FloatingPoint(2 * scale, 0);
        Ray<long double> ray;
        ray.origin = FloatingPoint(5 * scale, 3 * scale);
        ray.through = FloatingPoint(6 * scale, 3 * scale);

        const ClosestPoints result = closest_points(segment, ray);
        const long double tolerance = 1e-9L * scale;
        assert(
            distance(result.first, FloatingPoint(2 * scale, 0)) <=
            tolerance
        );
        assert(
            distance(result.second, FloatingPoint(5 * scale, 3 * scale)) <=
            tolerance
        );
        assert(
            std::fabs(distance(segment, ray) - std::sqrt(18.0L) * scale) <=
            tolerance
        );
    }
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

    for (const P& first : points) {
        for (const P& second : points) verify_closest(first, second);
        for (const IntegerLine& line : lines) verify_closest(first, line);
        for (const IntegerSegment& segment : segments) {
            verify_closest(first, segment);
        }
        for (const IntegerRay& ray : rays) verify_closest(first, ray);
    }
    for (const IntegerLine& first : lines) {
        for (const IntegerLine& second : lines) {
            verify_closest(first, second);
        }
        for (const IntegerSegment& segment : segments) {
            verify_closest(first, segment);
        }
        for (const IntegerRay& ray : rays) verify_closest(first, ray);
    }
    for (const IntegerSegment& first : segments) {
        for (const IntegerSegment& second : segments) {
            verify_closest(first, second);
        }
        for (const IntegerRay& ray : rays) verify_closest(first, ray);
    }
    for (const IntegerRay& first : rays) {
        for (const IntegerRay& second : rays) {
            verify_closest(first, second);
        }
    }
}

void test_random_integer_objects() {
    std::uint64_t state = 0xa7d36c219e45bfULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto random_point = [&]() {
        return P(
            static_cast<long long>(random() % 41) - 20,
            static_cast<long long>(random() % 41) - 20
        );
    };

    for (int trial = 0; trial < 5000; ++trial) {
        P point = random_point();
        IntegerLine line;
        line.a = random_point();
        do {
            line.b = random_point();
        } while (line.a == line.b);
        IntegerSegment first_segment;
        first_segment.a = random_point();
        first_segment.b = random_point();
        IntegerSegment second_segment;
        second_segment.a = random_point();
        second_segment.b = random_point();
        IntegerRay first_ray;
        first_ray.origin = random_point();
        do {
            first_ray.through = random_point();
        } while (first_ray.origin == first_ray.through);
        IntegerRay second_ray;
        second_ray.origin = random_point();
        do {
            second_ray.through = random_point();
        } while (second_ray.origin == second_ray.through);

        verify_closest(point, line);
        verify_closest(point, first_segment);
        verify_closest(point, first_ray);
        verify_closest(line, first_segment);
        verify_closest(line, first_ray);
        verify_closest(first_segment, second_segment);
        verify_closest(first_segment, first_ray);
        verify_closest(first_ray, second_ray);
    }
}

}  // namespace

int main() {
    test_examples();
    test_scale_invariance();
    test_exhaustive_small_integer_objects();
    test_random_integer_objects();

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
        const ClosestPoints result = closest_points(first, second);
        fast_output << distance(result.first, result.second) << '\n';
    }
}
