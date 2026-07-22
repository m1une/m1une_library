#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../../geometry/convex_polygon.hpp"
#include "../../geometry/steiner_convex_decomposition.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>
#include <random>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long double>;

int reflex_count(const std::vector<P>& polygon) {
    int result = 0;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                polygon[(index + polygon.size() - 1) % polygon.size()],
                polygon[index],
                polygon[(index + 1) % polygon.size()]
            ) < 0
        ) {
            ++result;
        }
    }
    return result;
}

void assert_valid(const std::vector<P>& polygon) {
    const auto decomposition = steiner_convex_decomposition(polygon);
    assert(decomposition.has_value());
    assert(
        decomposition->size() ==
        static_cast<std::size_t>(reflex_count(polygon) + 1)
    );

    long double area_sum = 0;
    for (const std::vector<P>& part : *decomposition) {
        assert(part.size() >= 3);
        assert(polygon_area2(part) > 0);
        assert(is_convex_polygon(part));
        area_sum += polygon_area(part);
        for (const P& point : part) {
            assert(
                point_in_polygon(polygon, point, 1e-9L) !=
                PointInPolygon::Outside
            );
        }
        for (std::size_t index = 0; index < part.size(); ++index) {
            const P midpoint =
                (part[index] + part[(index + 1) % part.size()]) / 2;
            assert(
                point_in_polygon(polygon, midpoint, 1e-9L) !=
                PointInPolygon::Outside
            );
        }
    }
    const long double expected = polygon_area(polygon);
    assert(
        std::fabs(area_sum - expected) <=
        1e-8L * std::max(1.0L, expected)
    );
}

void test_fixed() {
    std::vector<P> convex;
    convex.emplace_back(0, 0);
    convex.emplace_back(6, 0);
    convex.emplace_back(6, 4);
    convex.emplace_back(0, 4);
    assert_valid(convex);

    std::vector<P> l_shape;
    l_shape.emplace_back(0, 0);
    l_shape.emplace_back(5, 0);
    l_shape.emplace_back(5, 2);
    l_shape.emplace_back(2, 2);
    l_shape.emplace_back(2, 5);
    l_shape.emplace_back(0, 5);
    assert_valid(l_shape);

    std::vector<P> u_shape;
    u_shape.emplace_back(0, 0);
    u_shape.emplace_back(6, 0);
    u_shape.emplace_back(6, 6);
    u_shape.emplace_back(4, 6);
    u_shape.emplace_back(4, 2);
    u_shape.emplace_back(2, 2);
    u_shape.emplace_back(2, 6);
    u_shape.emplace_back(0, 6);
    assert_valid(u_shape);

    std::vector<P> crossing_cuts;
    crossing_cuts.emplace_back(0, 0);
    crossing_cuts.emplace_back(6, 0);
    crossing_cuts.emplace_back(6, 2);
    crossing_cuts.emplace_back(4, 2);
    crossing_cuts.emplace_back(4, 4);
    crossing_cuts.emplace_back(6, 4);
    crossing_cuts.emplace_back(6, 6);
    crossing_cuts.emplace_back(0, 6);
    crossing_cuts.emplace_back(0, 4);
    crossing_cuts.emplace_back(2, 4);
    crossing_cuts.emplace_back(2, 2);
    crossing_cuts.emplace_back(0, 2);
    assert_valid(crossing_cuts);

    std::vector<P> few_reflex;
    few_reflex.emplace_back(10, 0);
    few_reflex.emplace_back(8, 6);
    few_reflex.emplace_back(3, 10);
    few_reflex.emplace_back(0, 0);
    few_reflex.emplace_back(-8, 6);
    few_reflex.emplace_back(-10, 0);
    few_reflex.emplace_back(-8, -6);
    few_reflex.emplace_back(-3, -10);
    few_reflex.emplace_back(3, -10);
    few_reflex.emplace_back(8, -6);
    assert(reflex_count(few_reflex) == 1);
    assert_valid(few_reflex);

    std::vector<P> one_reflex_many_vertices;
    constexpr int many_size = 256;
    one_reflex_many_vertices.reserve(many_size);
    for (int index = 0; index < many_size; ++index) {
        const long double angle =
            2 * std::numbers::pi_v<long double> * index / many_size;
        const long double radius = index == 0 ? 1.0L : 10.0L;
        one_reflex_many_vertices.emplace_back(
            radius * std::cos(angle), radius * std::sin(angle)
        );
    }
    assert(reflex_count(one_reflex_many_vertices) == 1);
    assert_valid(one_reflex_many_vertices);

    std::reverse(l_shape.begin(), l_shape.end());
    const auto clockwise = steiner_convex_decomposition(l_shape);
    assert(clockwise.has_value() && clockwise->size() == 2);

    std::vector<P> redundant;
    redundant.emplace_back(0, 0);
    redundant.emplace_back(3, 0);
    redundant.emplace_back(6, 0);
    redundant.emplace_back(6, 2);
    redundant.emplace_back(2, 2);
    redundant.emplace_back(2, 6);
    redundant.emplace_back(0, 6);
    redundant.emplace_back(0, 0);
    const auto cleaned = steiner_convex_decomposition(redundant);
    assert(cleaned.has_value() && cleaned->size() == 2);

    std::vector<P> degenerate;
    degenerate.emplace_back(0, 0);
    degenerate.emplace_back(1, 0);
    degenerate.emplace_back(2, 0);
    assert(!steiner_convex_decomposition(degenerate).has_value());
}

void test_random_radial_polygons() {
    std::mt19937_64 generator(0x57e1deULL);
    std::uniform_real_distribution<long double> jitter(-0.08L, 0.08L);
    std::uniform_real_distribution<long double> radius(3.0L, 12.0L);
    for (int iteration = 0; iteration < 300; ++iteration) {
        const int size = 5 + static_cast<int>(generator() % 20);
        std::vector<P> polygon;
        polygon.reserve(size);
        for (int index = 0; index < size; ++index) {
            const long double angle =
                2 * std::numbers::pi_v<long double> * index / size +
                jitter(generator) / size;
            const long double length = radius(generator);
            polygon.emplace_back(
                length * std::cos(angle), length * std::sin(angle)
            );
        }
        if (!is_simple_polygon(polygon)) {
            --iteration;
            continue;
        }
        assert_valid(polygon);
    }
}

void test_random_monotone_polygons() {
    std::mt19937_64 generator(0xc0ffee57ULL);
    std::uniform_real_distribution<long double> height(1.0L, 20.0L);
    for (int iteration = 0; iteration < 300; ++iteration) {
        const int half = 3 + static_cast<int>(generator() % 15);
        std::vector<P> polygon;
        polygon.reserve(2 * half);
        for (int index = 0; index < half; ++index) {
            polygon.emplace_back(index, -height(generator));
        }
        for (int index = half - 1; index >= 0; --index) {
            polygon.emplace_back(index, height(generator));
        }
        assert(is_simple_polygon(polygon));
        assert(polygon_area2(polygon) > 0);
        assert_valid(polygon);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_random_radial_polygons();
    test_random_monotone_polygons();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int size;
    fast_input >> size;
    std::vector<Point<long long>> polygon(size);
    for (auto& point : polygon) fast_input >> point.x >> point.y;
    fast_output << (is_convex_polygon(polygon) ? 1 : 0) << '\n';
}
