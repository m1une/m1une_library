#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

// Include geometry first to check that support does not depend on include order.
#include "../../geometry/all.hpp"
#include "../../math/rational.hpp"
#include "../../math/matrix/linear_algebra.hpp"
#include "../../utilities/bigint.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {

using namespace m1une::geometry;
using Fraction = m1une::math::Rational<>;
using BigInt = m1une::utilities::BigInt;
using BigFraction = m1une::math::Rational<BigInt>;

static_assert(Coordinate<Fraction> && ExactCoordinate<Fraction>);
static_assert(Coordinate<BigFraction> && ExactCoordinate<BigFraction>);
static_assert(!Coordinate<bool> && !Coordinate<std::string>);
static_assert(!ExactCoordinate<double>);
static_assert(std::same_as<wide_type<Fraction>, Fraction>);
static_assert(std::same_as<wide_type<BigFraction>, BigFraction>);
static_assert(std::same_as<wide_type<long long>, __int128_t>);
static_assert(std::same_as<wide_type<float>, long double>);
static_assert(std::same_as<std::common_type_t<Fraction, int>, Fraction>);
static_assert(std::same_as<std::common_type_t<Fraction, double>, long double>);
static_assert(std::same_as<std::common_type_t<float, BigFraction>, long double>);
static_assert(!std::convertible_to<Fraction, double>);
static_assert(static_cast<float>(Fraction(1, 2)) == 0.5F);
static_assert(static_cast<double>(Fraction(1, 2)) == 0.5);
static_assert(orientation(Point<Fraction>(0, 0), Point<Fraction>(1, 0),
                          Point<Fraction>(0, Fraction(1, 1000000000000000LL))) == 1);

template <class R>
void fixed_test() {
    using P = Point<R>;
    const P origin;
    const P half(R(1, 2), R(1, 2));
    assert(dot(half, half) == R(1, 2));
    assert(cross(P(R(1, 2), 0), P(0, R(1, 3))) == R(1, 6));
    assert(distance2(origin, half) == R(1, 2));
    assert(half * 2 == P(1, 1));
    assert(2 * half == P(1, 1));
    assert(half / 2 == P(R(1, 4), R(1, 4)));
    assert(half * R(2, 3) == P(R(1, 3), R(1, 3)));
    assert(R(2, 3) * half == P(R(1, 3), R(1, 3)));
    assert(half / R(2, 3) == P(R(3, 4), R(3, 4)));
    assert((half * 0.5L == Point<long double>(0.25L, 0.25L)));
    assert((Point<int>(1, 2) * R(1, 2) == P(R(1, 2), 1)));
    assert((Point<float>(half) == Point<float>(0.5F, 0.5F)));
    assert((Point<double>(half) == Point<double>(0.5, 0.5)));
    assert((internal_division_point(origin, P(1, 1), R(1, 2), R(1, 2)) ==
            Point<long double>(0.5L, 0.5L)));
    assert((external_division_point(origin, P(1, 1), R(1, 2), R(1, 4)) ==
            Point<long double>(2, 2)));

    const Segment<R> singleton{half, half};
    assert(on_segment(singleton, half));
    assert(!on_segment(singleton, half + P(R(1, 1000000), 0), 1));
    const Segment<R> diagonal{origin, P(1, 1)};
    const Segment<R> other{P(0, 1), P(1, 0)};
    assert(intersects(diagonal, other));
    assert(linear_intersection(diagonal, other).kind == LinearIntersectionKind::Point);
    const Ray<R> ray{origin, half};
    assert(on_ray(ray, P(1, 1)) && !on_ray(ray, P(-1, -1)));
    assert(intersects(ray, other));
    const Line<R> horizontal{origin, P(1, 0)};
    const Line<R> vertical{origin, P(0, 1)};
    assert(orthogonal(horizontal, vertical));
    assert(parallel(horizontal, Line<R>{P(0, 1), P(1, 1)}));
    const Line<R> bisector = perpendicular_bisector(origin, P(1, 0));
    assert(on_line(bisector, P(R(1, 2), 0)));
    assert(on_line(bisector, half));

    const std::vector<P> square{origin, P(1, 0), P(1, 1), P(0, 1)};
    const std::vector<P> points{origin, P(1, 0), P(1, 1), P(0, 1), half};
    assert(convex_hull(points) == square);
    assert(polygon_area2(square) == 2);
    assert(point_in_polygon(square, half) == PointInPolygon::Inside);
    const ConvexPolygon<R> polygon(square);
    assert(polygon.contains(half) == PointInPolygon::Inside);
    assert(convex_layers(points) == std::vector<int>({1, 1, 1, 1, 2}));
    assert(minkowski_sum(square, square).size() == 4);
    assert(convex_decomposition(square)->size() == 1);
    assert(steiner_convex_decomposition(square)->size() == 1);
    const std::vector<P> concave{
        origin, P(1, 0), P(1, R(1, 2)), P(R(1, 2), R(1, 2)),
        P(R(1, 2), 1), P(0, 1)
    };
    const auto minimum_decomposition = minimum_convex_decomposition(concave);
    assert(minimum_decomposition.has_value() && minimum_decomposition->size() == 2);
    R total_area = 0;
    for (const auto& piece : *minimum_decomposition) {
        assert(is_convex_polygon(piece));
        total_area += polygon_area2(piece);
    }
    assert(total_area == polygon_area2(concave));
    const CountPointsInTriangle<R> counter(square, std::vector<P>{P(R(3, 4), R(1, 4))});
    assert(counter.query(0, 1, 2) == 1);
    assert(manhattan_mst(square).cost == 3);
    assert(euclidean_mst(square).cost == 3);
    assert(delaunay_triangulation(square).triangles.size() == 2);
    assert(voronoi_diagram(square).edges.size() > 0);
    assert(minimum_enclosing_circle(square)->support.size() == 2);
    std::vector<P> fractional_square = square;
    for (P& point : fractional_square) point = point / R(3);
    assert(manhattan_mst(fractional_square).cost == 1);
    assert(std::fabs(euclidean_mst(fractional_square).cost - 1) < 1e-12L);
    assert(delaunay_triangulation(fractional_square).triangles.size() == 2);
    assert(!voronoi_diagram(fractional_square).edges.empty());

    const std::vector<Segment<R>> segments{
        Segment<R>{P(R(1, 2), 0), P(R(1, 2), 1)},
        Segment<R>{P(0, R(1, 2)), P(1, R(1, 2))}
    };
    assert(manhattan_segment_intersections(segments) == 1);
    assert(manhattan_segment_intersection_points(segments) == std::vector<P>{half});
    const std::vector<AxisAlignedRectangle<R>> rectangles{
        AxisAlignedRectangle<R>(0, R(1, 2), 0, 1),
        AxisAlignedRectangle<R>(R(1, 4), 1, 0, 1)
    };
    assert(rectangle_union_area(rectangles) == 1);

    const Circle<R> circle{origin, R(1, 2)};
    assert(point_in_circle(circle, P(R(1, 2), 0)) == PointInCircle::Boundary);
    assert(point_in_circle(circle, P(R(1, 2) + R(1, 1000000), 0), 1) ==
           PointInCircle::Outside);
    assert(on_circle(circle, P(R(1, 2), 0)));
    assert(on_circle(circle, Point<int>(0, 0)) == false);
    assert(circle_relation(circle, Circle<R>{P(1, 0), R(1, 2)}) ==
           CircleRelation::ExternallyTangent);
    assert(intersects(circle, circle));

    m1une::matrix::Matrix<R> matrix(2, 2);
    matrix[0][0] = R(1, 2); matrix[0][1] = R(1, 3);
    matrix[1][0] = 1; matrix[1][1] = -1;
    const auto inverse = m1une::matrix::inverse(matrix);
    assert(inverse.has_value());
    assert(matrix * *inverse == m1une::matrix::Matrix<R>::identity(2));
}

// Gift wrapping is an independent quadratic hull oracle on scaled integers.
std::vector<Point<long long>> naive_hull(std::vector<Point<long long>> points) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    if (points.size() < 2) return points;
    std::vector<Point<long long>> hull;
    int current = 0;
    do {
        hull.push_back(points[current]);
        int next = (current + 1) % int(points.size());
        for (int i = 0; i < int(points.size()); ++i) {
            const auto turn = cross(points[current], points[next], points[i]);
            if (turn < 0 || (turn == 0 && distance2(points[current], points[next]) <
                                        distance2(points[current], points[i]))) next = i;
        }
        current = next;
    } while (current != 0);
    return hull;
}

template <class R>
void randomized_test(int trials) {
    using P = Point<R>;
    std::uint64_t state = 1307;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < trials; ++trial) {
        std::vector<P> points;
        std::vector<Point<long long>> scaled;
        const int size = int(random() % 20);
        for (int i = 0; i < size; ++i) {
            const long long x = static_cast<long long>(random() % 41) - 20;
            const long long y = static_cast<long long>(random() % 41) - 20;
            const int dx = 1 + int(random() % 5), dy = 1 + int(random() % 5);
            points.emplace_back(R(x, dx), R(y, dy));
            scaled.emplace_back(x * (60 / dx), y * (60 / dy));
        }
        const auto expected_hull = naive_hull(scaled);
        const auto hull = convex_hull(points);
        assert(hull.size() == expected_hull.size());
        for (std::size_t i = 0; i < hull.size(); ++i) {
            assert(hull[i].x * 60 == expected_hull[i].x);
            assert(hull[i].y * 60 == expected_hull[i].y);
        }
        const auto nearest = closest_pair(points);
        const auto farthest = farthest_pair(points);
        assert(nearest.has_value() == (size >= 2));
        assert(farthest.has_value() == (size >= 2));
        if (size >= 2) {
            auto minimum = distance2(scaled[0], scaled[1]);
            auto maximum = minimum;
            std::pair<int, int> nearest_indices(0, 1);
            for (int i = 0; i < size; ++i) {
                for (int j = i + 1; j < size; ++j) {
                    const auto squared = distance2(scaled[i], scaled[j]);
                    if (squared < minimum) {
                        minimum = squared;
                        nearest_indices = std::pair(i, j);
                    }
                    maximum = std::max(maximum, squared);
                }
            }
            assert(nearest->distance_squared * 3600 == static_cast<long long>(minimum));
            assert(std::pair(nearest->first, nearest->second) == nearest_indices);
            assert(farthest->distance_squared * 3600 == static_cast<long long>(maximum));
        }
        if (size >= 3) {
            assert(orientation(points[0], points[1], points[2], 1) ==
                   orientation(scaled[0], scaled[1], scaled[2]));
        }
    }
}

void bigint_precision_test() {
    const BigInt power("1000000000000000000000000000000000000000000000000000000000000");
    const BigFraction base(power);
    const BigFraction tiny(1, power);
    using P = Point<BigFraction>;
    const P a(base, base), b(base + 1, base), c(base, base + tiny);
    assert(cross(a, b, c) == tiny);
    assert(orientation(a, b, c) == 1);
    assert(convex_hull(std::vector<P>{a, b, c}).size() == 3);
    assert(sign<BigFraction>(tiny, 1) == 1);
    const Segment<BigFraction> singleton{a, a};
    assert(!on_segment(singleton, c));
    const Circle<BigFraction> circle{P(), 1};
    assert(!on_circle(circle, P(1 + tiny, 0)));
    assert(point_in_circle(circle, P(1 + tiny, 0)) == PointInCircle::Outside);
    assert(static_cast<float>(BigFraction(1, 2)) == 0.5F);
    assert(static_cast<double>(BigFraction(1, 2)) == 0.5);
}

}  // namespace

int main() {
    fixed_test<Fraction>();
    fixed_test<BigFraction>();
    randomized_test<Fraction>(1000);
    randomized_test<BigFraction>(100);
    bigint_precision_test();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int test_count;
    input >> test_count;
    while (test_count--) {
        int size;
        input >> size;
        std::vector<Point<Fraction>> points;
        points.reserve(size);
        for (int i = 0; i < size; ++i) {
            long long x, y;
            input >> x >> y;
            points.emplace_back(Fraction(x, 2), Fraction(y, 2));
        }
        const auto hull = convex_hull(std::move(points));
        output << hull.size() << '\n';
        for (const auto& point : hull) {
            output << (point.x * 2).numerator() << ' ' << (point.y * 2).numerator() << '\n';
        }
    }
}
