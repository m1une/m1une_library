#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C"
#define ERROR "1e-8"

#include "../../geometry/linear.hpp"

#include <cassert>
#include <cmath>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using m1une::geometry::Point;
using m1une::geometry::Segment;
using m1une::geometry::LinearIntersection;
using m1une::geometry::LinearIntersectionKind;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-12L;
}

bool close(
    const Point<long double>& first,
    const Point<long double>& second
) {
    return close(first.x, second.x) && close(first.y, second.y);
}

template <class T>
Segment<T> make_segment(T ax, T ay, T bx, T by) {
    Segment<T> result;
    result.a = Point<T>(ax, ay);
    result.b = Point<T>(bx, by);
    return result;
}

void test_examples() {
    using namespace m1une::geometry;

    Segment<long long> first = make_segment(0LL, 0LL, 4LL, 4LL);
    Segment<long long> second = make_segment(0LL, 4LL, 4LL, 0LL);
    LinearIntersection result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Point);
    assert(close(result.first, Point<long double>(2, 2)));
    assert(close(result.first, result.second));

    first = make_segment(4LL, 0LL, 0LL, 0LL);
    second = make_segment(1LL, 0LL, 3LL, 0LL);
    result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Segment);
    assert(close(result.first, Point<long double>(3, 0)));
    assert(close(result.second, Point<long double>(1, 0)));

    first = make_segment(0LL, 0LL, 2LL, 0LL);
    second = make_segment(2LL, 0LL, 5LL, 0LL);
    result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Point);
    assert(close(result.first, Point<long double>(2, 0)));

    second = make_segment(3LL, 0LL, 5LL, 0LL);
    result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Empty);

    first = make_segment(1LL, 1LL, 1LL, 1LL);
    second = make_segment(0LL, 0LL, 2LL, 2LL);
    result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Point);
    assert(close(result.first, Point<long double>(1, 1)));

    first = make_segment(0LL, 0LL, 3LL, 3LL);
    second = make_segment(0LL, 3LL, 3LL, 0LL);
    result = linear_intersection(first, second);
    assert(result.kind == LinearIntersectionKind::Point);
    assert(close(result.first, Point<long double>(1.5L, 1.5L)));
}

void test_exhaustive_small_integer_segments() {
    using namespace m1une::geometry;
    std::vector<Segment<long long>> segments;
    for (long long ax = -1; ax <= 1; ++ax) {
        for (long long ay = -1; ay <= 1; ++ay) {
            for (long long bx = -1; bx <= 1; ++bx) {
                for (long long by = -1; by <= 1; ++by) {
                    segments.push_back(make_segment(ax, ay, bx, by));
                }
            }
        }
    }

    for (const Segment<long long>& first : segments) {
        for (const Segment<long long>& second : segments) {
            const LinearIntersection result =
                linear_intersection(first, second);
            assert(
                (result.kind != LinearIntersectionKind::Empty) ==
                intersects(first, second)
            );
            if (result.kind == LinearIntersectionKind::Empty) continue;

            Segment<long double> first_floating;
            first_floating.a = Point<long double>(first.a);
            first_floating.b = Point<long double>(first.b);
            Segment<long double> second_floating;
            second_floating.a = Point<long double>(second.a);
            second_floating.b = Point<long double>(second.b);
            assert(on_segment(first_floating, result.first));
            assert(on_segment(second_floating, result.first));
            assert(on_segment(first_floating, result.second));
            assert(on_segment(second_floating, result.second));

            if (result.kind == LinearIntersectionKind::Point) {
                assert(close(result.first, result.second));
            } else {
                assert(result.kind == LinearIntersectionKind::Segment);
                assert(!close(result.first, result.second));
                const Point<long double> middle =
                    (result.first + result.second) / 2.0L;
                assert(on_segment(first_floating, middle));
                assert(on_segment(second_floating, middle));
            }
        }
    }
}

}  // namespace

int main() {
    test_examples();
    test_exhaustive_small_integer_segments();

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
        const LinearIntersection result =
            m1une::geometry::linear_intersection(first, second);
        assert(result.kind == LinearIntersectionKind::Point);
        fast_output << result.first.x << ' ' << result.first.y << '\n';
    }
}
