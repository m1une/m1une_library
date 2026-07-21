#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"

#include "../../geometry/all.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-10L;
}

void test_fixed() {
    const Point<long double> point_center = centroid(P(3, -5));
    assert(close(point_center.x, 3));
    assert(close(point_center.y, -5));

    const Segment<long long> segment{P(0, 2), P(6, 8)};
    const Point<long double> segment_center = centroid(segment);
    assert(close(segment_center.x, 3));
    assert(close(segment_center.y, 5));
    const Segment<long long> degenerate{P(4, 7), P(4, 7)};
    assert(centroid(degenerate) == Point<long double>(4, 7));

    std::array<P, 3> triangle;
    triangle[0] = P(0, 0);
    triangle[1] = P(6, 0);
    triangle[2] = P(0, 3);
    const Point<long double> triangle_center = centroid(triangle);
    assert(close(triangle_center.x, 2));
    assert(close(triangle_center.y, 1));

    const Circle<long long> circle{P(-3, 9), 5};
    assert(centroid(circle) == Point<long double>(-3, 9));

    std::vector<P> concave;
    concave.emplace_back(0, 0);
    concave.emplace_back(5, 0);
    concave.emplace_back(5, 1);
    concave.emplace_back(1, 1);
    concave.emplace_back(1, 5);
    concave.emplace_back(0, 5);
    const auto concave_center = centroid(concave);
    assert(concave_center.has_value());
    assert(close(concave_center->x, 14.5L / 9));
    assert(close(concave_center->y, 14.5L / 9));
    std::reverse(concave.begin(), concave.end());
    const auto clockwise_center = centroid(concave);
    assert(clockwise_center.has_value());
    assert(close(clockwise_center->x, concave_center->x));
    assert(close(clockwise_center->y, concave_center->y));

    std::vector<P> square;
    square.emplace_back(0, 0);
    square.emplace_back(4, 0);
    square.emplace_back(4, 2);
    square.emplace_back(0, 2);
    const ConvexPolygon<long long> convex(square);
    const auto convex_center = centroid(convex);
    assert(convex_center.has_value());
    assert(close(convex_center->x, 2));
    assert(close(convex_center->y, 1));

    std::vector<P> collinear;
    collinear.emplace_back(0, 0);
    collinear.emplace_back(2, 0);
    collinear.emplace_back(7, 0);
    assert(!centroid(collinear).has_value());
}

void test_randomized_concave_polygons() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        const long long width = 2 + static_cast<long long>(random() % 100);
        const long long height = 2 + static_cast<long long>(random() % 100);
        const long long inner_x =
            1 + static_cast<long long>(random() % (width - 1));
        const long long inner_y =
            1 + static_cast<long long>(random() % (height - 1));
        const long long translate_x =
            static_cast<long long>(random() % 201) - 100;
        const long long translate_y =
            static_cast<long long>(random() % 201) - 100;

        std::vector<P> polygon;
        polygon.emplace_back(translate_x, translate_y);
        polygon.emplace_back(translate_x + width, translate_y);
        polygon.emplace_back(
            translate_x + width,
            translate_y + inner_y
        );
        polygon.emplace_back(
            translate_x + inner_x,
            translate_y + inner_y
        );
        polygon.emplace_back(
            translate_x + inner_x,
            translate_y + height
        );
        polygon.emplace_back(translate_x, translate_y + height);
        if (random() % 2 != 0) std::reverse(polygon.begin(), polygon.end());

        const long double w = static_cast<long double>(width);
        const long double h = static_cast<long double>(height);
        const long double x = static_cast<long double>(inner_x);
        const long double y = static_cast<long double>(inner_y);
        const long double tx = static_cast<long double>(translate_x);
        const long double ty = static_cast<long double>(translate_y);
        const long double full_area = w * h;
        const long double removed_area = (w - x) * (h - y);
        const long double area = full_area - removed_area;
        const long double expected_x = tx +
            (
                full_area * w / 2 -
                removed_area * (x + w) / 2
            ) / area;
        const long double expected_y = ty +
            (
                full_area * h / 2 -
                removed_area * (y + h) / 2
            ) / area;

        const auto result = centroid(polygon);
        assert(result.has_value());
        assert(close(result->x, expected_x));
        assert(close(result->y, expected_y));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized_concave_polygons();

    int size;
    fast_input >> size;
    std::vector<P> polygon(size);
    for (P& point : polygon) fast_input >> point.x >> point.y;
    fast_output.set_fixed(1);
    fast_output << polygon_area(polygon) << '\n';
}
