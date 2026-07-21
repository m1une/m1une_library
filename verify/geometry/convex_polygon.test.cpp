#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"

#include "../../geometry/convex_polygon.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

using namespace m1une::geometry;
using PointType = Point<long long>;
using Wide = wide_type<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-9L;
}

Wide naive_chain_area2(
    const std::vector<PointType>& polygon,
    int first,
    int last
) {
    Wide result = 0;
    int index = first;
    while (index != last) {
        const int next = (index + 1) % int(polygon.size());
        result += cross(polygon[index], polygon[next]);
        index = next;
    }
    result += cross(polygon[last], polygon[first]);
    return result;
}

bool is_tangent(
    const std::vector<PointType>& polygon,
    const PointType& point,
    int index
) {
    int side = 0;
    for (const PointType& vertex : polygon) {
        const int current = orientation(point, polygon[index], vertex);
        if (current == 0) continue;
        if (side != 0 && side != current) return false;
        side = current;
    }
    return side != 0;
}

void test_fixed() {
    std::vector<PointType> square;
    square.emplace_back(0, 0);
    square.emplace_back(4, 0);
    square.emplace_back(4, 4);
    square.emplace_back(0, 4);
    assert(is_convex_polygon(square));
    assert(is_convex_polygon(square, true));

    std::vector<PointType> weak;
    weak.emplace_back(0, 0);
    weak.emplace_back(2, 0);
    weak.emplace_back(4, 0);
    weak.emplace_back(4, 4);
    weak.emplace_back(0, 4);
    assert(is_convex_polygon(weak));
    assert(!is_convex_polygon(weak, true));
    std::reverse(weak.begin(), weak.end());

    ConvexPolygon<long long> polygon(weak);
    assert(polygon.size() == 4);
    assert(polygon.area2() == 32);
    assert(polygon.contains(PointType(2, 2)) == PointInPolygon::Inside);
    assert(polygon.contains(PointType(0, 2)) == PointInPolygon::Boundary);
    assert(polygon.contains(PointType(5, 2)) == PointInPolygon::Outside);
    assert(polygon.max_dot(PointType(1, 0)).first == 4);
    assert(polygon.min_dot(PointType(1, 0)).first == 0);

    std::vector<PointType> diagonal_segment;
    diagonal_segment.emplace_back(0, 3);
    diagonal_segment.emplace_back(2, 1);
    const auto normalized_segment =
        normalize_convex_polygon(diagonal_segment);
    assert(normalized_segment[0] == PointType(2, 1));

    const auto tangents = polygon.tangent_vertices(PointType(7, 2));
    assert(is_tangent(polygon.vertices(), PointType(7, 2), tangents.first));
    assert(is_tangent(polygon.vertices(), PointType(7, 2), tangents.second));
    assert(tangents.first != tangents.second);

    const PointType edge_extension(7, 0);
    const auto collinear_tangents =
        polygon.tangent_vertices(edge_extension);
    assert(is_tangent(
        polygon.vertices(),
        edge_extension,
        collinear_tangents.first
    ));
    assert(is_tangent(
        polygon.vertices(),
        edge_extension,
        collinear_tangents.second
    ));

    Line<long long> vertical{PointType(2, -1), PointType(2, 5)};
    const auto left = convex_cut(square, vertical);
    assert(close(polygon_area(left), 8));

    std::vector<PointType> redundant_square;
    redundant_square.emplace_back(0, 0);
    redundant_square.emplace_back(2, 0);
    redundant_square.emplace_back(4, 0);
    redundant_square.emplace_back(4, 4);
    redundant_square.emplace_back(0, 4);
    redundant_square.emplace_back(0, 0);
    const auto self_intersection =
        convex_polygon_intersection(redundant_square, square);
    assert(close(polygon_area(self_intersection), 16));

    std::vector<PointType> concave;
    concave.emplace_back(0, 0);
    concave.emplace_back(4, 0);
    concave.emplace_back(2, 1);
    concave.emplace_back(4, 4);
    concave.emplace_back(0, 4);
    assert(!is_convex_polygon(concave));

    std::vector<PointType> collinear;
    collinear.emplace_back(0, 0);
    collinear.emplace_back(4, 0);
    collinear.emplace_back(2, 0);
    assert(is_convex_polygon(collinear));
    assert(!is_convex_polygon(collinear, true));
}

void test_randomized() {
    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        std::vector<PointType> first_points;
        std::vector<PointType> second_points;
        const int first_count = 3 + int(random() % 18);
        const int second_count = 3 + int(random() % 18);
        for (int index = 0; index < first_count; ++index) {
            first_points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        for (int index = 0; index < second_count; ++index) {
            second_points.emplace_back(
                static_cast<long long>(random() % 31) - 15,
                static_cast<long long>(random() % 31) - 15
            );
        }
        std::vector<PointType> first = convex_hull(first_points);
        std::vector<PointType> second = convex_hull(second_points);
        if (first.size() < 3 || second.size() < 3) continue;

        std::vector<PointType> input = first;
        if (random() % 2 != 0) std::reverse(input.begin(), input.end());
        ConvexPolygon<long long> polygon(input);
        assert(
            polygon.vertices() ==
            normalize_convex_polygon(first)
        );
        assert(polygon.area2() == polygon_area2(first));
        assert(is_convex_polygon(polygon.vertices(), true));

        for (int query = 0; query < 40; ++query) {
            const PointType point(
                static_cast<long long>(random() % 61) - 30,
                static_cast<long long>(random() % 61) - 30
            );
            assert(
                polygon.contains(point) ==
                point_in_polygon(first, point)
            );

            const PointType direction(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
            Wide minimum = dot(first[0], direction);
            Wide maximum = minimum;
            for (const PointType& vertex : first) {
                minimum = std::min(minimum, dot(vertex, direction));
                maximum = std::max(maximum, dot(vertex, direction));
            }
            assert(polygon.min_dot(direction).first == minimum);
            assert(polygon.max_dot(direction).first == maximum);
        }

        for (int first_index = 0; first_index < polygon.size(); ++first_index) {
            for (int last_index = 0; last_index < polygon.size(); ++last_index) {
                assert(
                    polygon.chain_area2(first_index, last_index) ==
                    naive_chain_area2(
                        polygon.vertices(),
                        first_index,
                        last_index
                    )
                );
            }
        }

        for (int query = 0; query < 4; ++query) {
            const long long outside_x =
                query % 2 == 0 ? -100 - int(random() % 20)
                               : 100 + int(random() % 20);
            const long long outside_y =
                query / 2 == 0 ? -100 - int(random() % 20)
                               : 100 + int(random() % 20);
            const PointType outside(outside_x, outside_y);
            const auto tangents = polygon.tangent_vertices(outside);
            assert(is_tangent(
                polygon.vertices(),
                outside,
                tangents.first
            ));
            assert(is_tangent(
                polygon.vertices(),
                outside,
                tangents.second
            ));
        }

        assert(
            convex_polygons_intersect(first, second) ==
            intersects(first, second)
        );
        assert(close(
            convex_polygons_distance(first, second),
            distance(first, second)
        ));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    int size;
    fast_input >> size;
    using FloatingPoint = Point<long double>;
    std::vector<FloatingPoint> polygon(size);
    for (FloatingPoint& point : polygon) fast_input >> point.x >> point.y;

    int query_count;
    fast_input >> query_count;
    fast_output.set_fixed(8);
    while (query_count--) {
        Line<long double> boundary;
        fast_input >> boundary.a.x >> boundary.a.y;
        fast_input >> boundary.b.x >> boundary.b.y;
        fast_output << polygon_area(convex_cut(polygon, boundary)) << '\n';
    }
}
