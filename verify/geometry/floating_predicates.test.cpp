#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C"

#include "../../geometry/ray.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using IntegerPoint = Point<long long>;
using FloatingPoint = Point<long double>;

FloatingPoint scaled(const IntegerPoint& point, long double scale) {
    return FloatingPoint(point.x * scale, point.y * scale);
}

template <class Object>
Object make_object(
    const IntegerPoint& first,
    const IntegerPoint& second
) {
    Object result;
    result.a = first;
    result.b = second;
    return result;
}

template <class Object>
Object make_directed_object(
    const IntegerPoint& first,
    const IntegerPoint& second
) {
    Object result;
    result.origin = first;
    result.through = second;
    return result;
}

Line<long double> scaled(
    const Line<long long>& line,
    long double scale
) {
    Line<long double> result;
    result.a = scaled(line.a, scale);
    result.b = scaled(line.b, scale);
    return result;
}

Segment<long double> scaled(
    const Segment<long long>& segment,
    long double scale
) {
    Segment<long double> result;
    result.a = scaled(segment.a, scale);
    result.b = scaled(segment.b, scale);
    return result;
}

Ray<long double> scaled(const Ray<long long>& ray, long double scale) {
    Ray<long double> result;
    result.origin = scaled(ray.origin, scale);
    result.through = scaled(ray.through, scale);
    return result;
}

void test_small_triangle() {
    const FloatingPoint origin(0, 0);
    assert(
        orientation(
            origin,
            FloatingPoint(1e-30L, 0),
            FloatingPoint(0, 1e-30L)
        ) == 1
    );
    assert(
        orientation(
            origin,
            FloatingPoint(1e30L, 0),
            FloatingPoint(0, 1e30L)
        ) == 1
    );

    Segment<long double> segment;
    segment.a = FloatingPoint(9, 10);
    segment.b = FloatingPoint(21, 9);
    const FloatingPoint rounded_endpoint(9, 10 - 2e-15L);
    assert(orientation(segment.a, segment.b, rounded_endpoint) == 0);
    assert(on_segment(segment, rounded_endpoint));
}

void test_scale_invariance() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    auto random_point = [&]() {
        return IntegerPoint(
            static_cast<long long>(random() % 21) - 10,
            static_cast<long long>(random() % 21) - 10
        );
    };

    for (int trial = 0; trial < 10000; ++trial) {
        IntegerPoint first = random_point();
        IntegerPoint second;
        do {
            second = random_point();
        } while (second == first);
        IntegerPoint third = random_point();
        IntegerPoint fourth;
        do {
            fourth = random_point();
        } while (fourth == third);
        IntegerPoint query = random_point();

        Line<long long> first_line =
            make_object<Line<long long>>(first, second);
        Line<long long> second_line =
            make_object<Line<long long>>(third, fourth);
        Segment<long long> first_segment =
            make_object<Segment<long long>>(first, second);
        Segment<long long> second_segment =
            make_object<Segment<long long>>(third, fourth);
        Ray<long long> first_ray =
            make_directed_object<Ray<long long>>(first, second);
        Ray<long long> second_ray =
            make_directed_object<Ray<long long>>(third, fourth);

        const int exponent = int(random() % 161) - 80;
        const long double scale = std::ldexp(1.0L, exponent);
        const FloatingPoint floating_first = scaled(first, scale);
        const FloatingPoint floating_second = scaled(second, scale);
        const FloatingPoint floating_query = scaled(query, scale);
        const Line<long double> floating_first_line =
            scaled(first_line, scale);
        const Line<long double> floating_second_line =
            scaled(second_line, scale);
        const Segment<long double> floating_first_segment =
            scaled(first_segment, scale);
        const Segment<long double> floating_second_segment =
            scaled(second_segment, scale);
        const Ray<long double> floating_first_ray =
            scaled(first_ray, scale);
        const Ray<long double> floating_second_ray =
            scaled(second_ray, scale);

        assert(
            orientation(first, second, query) ==
            orientation(floating_first, floating_second, floating_query)
        );
        assert(
            on_line(first_line, query) ==
            on_line(floating_first_line, floating_query)
        );
        assert(
            on_segment(first_segment, query) ==
            on_segment(floating_first_segment, floating_query)
        );
        assert(
            on_ray(first_ray, query) ==
            on_ray(floating_first_ray, floating_query)
        );
        assert(
            parallel(first_line, second_line) ==
            parallel(floating_first_line, floating_second_line)
        );
        assert(
            orthogonal(first_line, second_line) ==
            orthogonal(floating_first_line, floating_second_line)
        );
        assert(
            intersects(first_segment, second_segment) ==
            intersects(floating_first_segment, floating_second_segment)
        );
        assert(
            intersects(first_ray, second_segment) ==
            intersects(floating_first_ray, floating_second_segment)
        );
        assert(
            intersects(first_ray, second_line) ==
            intersects(floating_first_ray, floating_second_line)
        );
        assert(
            intersects(first_ray, second_ray) ==
            intersects(floating_first_ray, floating_second_ray)
        );
        assert(
            segment_intersection(first_segment, second_segment).kind ==
            segment_intersection(
                floating_first_segment,
                floating_second_segment
            ).kind
        );
    }
}

}  // namespace

int main() {
    test_small_triangle();
    test_scale_invariance();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    Point<long double> first;
    Point<long double> second;
    fast_input >> first.x >> first.y >> second.x >> second.y;
    Line<long double> line;
    line.a = first;
    line.b = second;
    Segment<long double> segment;
    segment.a = first;
    segment.b = second;
    Ray<long double> ray;
    ray.origin = first;
    ray.through = second;

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        Point<long double> point;
        fast_input >> point.x >> point.y;
        const int turn = orientation(first, second, point);
        if (turn > 0) {
            fast_output << "COUNTER_CLOCKWISE\n";
        } else if (turn < 0) {
            fast_output << "CLOCKWISE\n";
        } else if (on_segment(segment, point)) {
            fast_output << "ON_SEGMENT\n";
        } else if (on_ray(ray, point)) {
            fast_output << "ONLINE_FRONT\n";
        } else {
            fast_output << "ONLINE_BACK\n";
        }
    }
}
