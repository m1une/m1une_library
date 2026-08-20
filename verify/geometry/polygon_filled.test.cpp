#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/polygon.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <=
        1e-9L * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

Polygon<long long> square(long long radius, bool filled = true) {
    Polygon<long long> result;
    result.vertices.emplace_back(-radius, -radius);
    result.vertices.emplace_back(radius, -radius);
    result.vertices.emplace_back(radius, radius);
    result.vertices.emplace_back(-radius, radius);
    result.filled = filled;
    return result;
}

void test_point_and_segment() {
    const Polygon<long long> region = square(2);
    const Polygon<long long> boundary = square(2, false);
    const P center(0, 0);
    const P edge(2, 0);
    const Segment<long long> inside{P(-1, 0), P(1, 0)};

    assert(contains(region, center));
    assert(!contains(boundary, center));
    assert(contains(region, edge));
    assert(contains(boundary, edge));
    assert(intersects(region, center));
    assert(!intersects(boundary, center));
    assert(close(distance(region, center), 0));
    assert(close(distance(boundary, center), 2));
    assert(intersects(region, inside));
    assert(!intersects(boundary, inside));
    assert(close(distance(region, inside), 0));
    assert(close(distance(boundary, inside), 1));

    const ClosestPoints result = closest_points(boundary, center);
    assert(close(distance(result.first, result.second), 2));
    assert(contains(boundary, result.first));
}

void test_polygon_pairs() {
    const Polygon<long long> outer_region = square(3);
    const Polygon<long long> outer_boundary = square(3, false);
    const Polygon<long long> inner_region = square(1);
    const Polygon<long long> inner_boundary = square(1, false);

    assert(intersects(outer_region, inner_region));
    assert(intersects(outer_region, inner_boundary));
    assert(!intersects(outer_boundary, inner_region));
    assert(!intersects(outer_boundary, inner_boundary));
    assert(close(distance(outer_region, inner_boundary), 0));
    assert(close(distance(outer_boundary, inner_region), 2));
    assert(close(distance(outer_boundary, inner_boundary), 2));

    Polygon<long long> shifted = square(1);
    for (P& vertex : shifted.vertices) vertex.x += 5;
    assert(!intersects(inner_region, shifted));
    assert(close(distance(inner_region, shifted), 3));
    const ClosestPoints apart = closest_points(inner_region, shifted);
    const ClosestPoints reversed = closest_points(shifted, inner_region);
    assert(apart.first == reversed.second);
    assert(apart.second == reversed.first);
}

void test_circle_polygon_pairs() {
    const Polygon<long long> region = square(3);
    const Polygon<long long> boundary = square(3, false);
    const Circle<long long> inner_boundary{P(0, 0), 1, false};
    const Circle<long long> inner_region{P(0, 0), 1};
    const Circle<long long> outer_region{P(0, 0), 5};

    assert(intersects(region, inner_boundary));
    assert(intersects(inner_region, region));
    assert(!intersects(boundary, inner_boundary));
    assert(!intersects(inner_region, boundary));
    assert(intersects(outer_region, boundary));
    assert(close(distance(region, inner_boundary), 0));
    assert(close(distance(boundary, inner_boundary), 2));
    assert(close(distance(inner_region, boundary), 2));
    assert(close(distance(outer_region, boundary), 0));
}

void test_random_point_queries() {
    std::uint64_t state = 0x9e3779b97f4a7c15ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 20000; ++trial) {
        const long long center_x =
            static_cast<long long>(random() % 41) - 20;
        const long long center_y =
            static_cast<long long>(random() % 41) - 20;
        const long long radius =
            static_cast<long long>(random() % 10) + 1;
        Polygon<long long> region = square(radius);
        for (P& vertex : region.vertices) {
            vertex.x += center_x;
            vertex.y += center_y;
        }
        Polygon<long long> boundary = region;
        boundary.filled = false;
        const P point(
            static_cast<long long>(random() % 81) - 40,
            static_cast<long long>(random() % 81) - 40
        );

        const long long dx = std::llabs(point.x - center_x);
        const long long dy = std::llabs(point.y - center_y);
        const bool in_region = dx <= radius && dy <= radius;
        const bool on_boundary =
            in_region && (dx == radius || dy == radius);
        const long double outside_x = std::max(0LL, dx - radius);
        const long double outside_y = std::max(0LL, dy - radius);
        const long double region_distance =
            std::hypot(outside_x, outside_y);
        const long double boundary_distance = in_region
            ? static_cast<long double>(
                std::min(radius - dx, radius - dy)
            )
            : region_distance;

        assert(contains(region, point) == in_region);
        assert(contains(boundary, point) == on_boundary);
        assert(intersects(region, point) == in_region);
        assert(intersects(boundary, point) == on_boundary);
        assert(close(distance(region, point), region_distance));
        assert(close(distance(boundary, point), boundary_distance));
        assert(close(distance(point, region), region_distance));
        assert(close(distance(point, boundary), boundary_distance));
    }
}

}  // namespace

int main() {
    test_point_and_segment();
    test_polygon_pairs();
    test_circle_polygon_pairs();
    test_random_point_queries();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first, second;
    input >> first >> second;
    output << first + second << '\n';
}
