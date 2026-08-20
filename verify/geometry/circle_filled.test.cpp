#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <=
        1e-9L * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

bool close(
    const Point<long double>& first,
    const Point<long double>& second
) {
    return close(distance(first, second), 0.0L);
}

void test_modes() {
    const Circle<long long> region{P(0, 0), 5};
    const Circle<long long> boundary{P(0, 0), 5, false};
    const Segment<long long> inside{P(-1, 0), P(1, 0)};

    assert(region.filled);
    assert(!boundary.filled);
    assert(point_in_circle(region, P(0, 0)) == PointInCircle::Inside);
    assert(contains(region, P(0, 0)));
    assert(!contains(boundary, P(0, 0)));
    assert(contains(boundary, P(5, 0)));
    assert(intersects(region, inside));
    assert(!intersects(boundary, inside));
    assert(close(distance(region, inside), 0));
    assert(close(distance(boundary, inside), 4));

    const ClosestPoints common = closest_points(region, inside);
    assert(close(common.first, common.second));
    const ClosestPoints apart = closest_points(boundary, inside);
    assert(on_circle(boundary, apart.first));
    assert(close(distance(apart.first, apart.second), 4));
}

void test_circle_pairs() {
    const Circle<long long> outer_boundary{P(0, 0), 5, false};
    const Circle<long long> inner_boundary{P(1, 0), 2, false};
    const Circle<long long> inner_region{P(1, 0), 2};
    const Circle<long long> covering_region{P(0, 0), 6};

    assert(!intersects(outer_boundary, inner_boundary));
    assert(close(distance(outer_boundary, inner_boundary), 2));
    assert(!intersects(outer_boundary, inner_region));
    assert(close(distance(outer_boundary, inner_region), 2));
    assert(intersects(outer_boundary, covering_region));
    assert(close(distance(outer_boundary, covering_region), 0));

    const Circle<long long> first{P(0, 0), 3};
    const Circle<long long> overlapping{P(4, 0), 2};
    const Circle<long long> separated{P(10, 0), 2};
    assert(intersects(first, overlapping));
    assert(!intersects(first, separated));
    assert(close(distance(first, separated), 5));
    const ClosestPoints apart = closest_points(first, separated);
    assert(close(apart.first, Point<long double>(3, 0)));
    assert(close(apart.second, Point<long double>(8, 0)));
}

void test_random_point_queries() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 20000; ++trial) {
        const Circle<long long> circle{
            P(
                static_cast<long long>(random() % 41) - 20,
                static_cast<long long>(random() % 41) - 20
            ),
            static_cast<long long>(random() % 11)
        };
        const P point(
            static_cast<long long>(random() % 61) - 30,
            static_cast<long long>(random() % 61) - 30
        );
        const long double expected = std::max(
            0.0L,
            distance(circle.center, point) -
                static_cast<long double>(circle.radius)
        );
        const ClosestPoints result = closest_points(circle, point);
        assert(contains(circle, result.first));
        assert(close(result.second, Point<long double>(point)));
        assert(close(distance(result.first, result.second), expected));
        assert(close(distance(circle, point), expected));
    }
}

}  // namespace

int main() {
    test_modes();
    test_circle_pairs();
    test_random_point_queries();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first, second;
    input >> first >> second;
    output << first + second << '\n';
}
