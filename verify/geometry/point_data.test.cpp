#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include "../../geometry/all.hpp"
#include "../../math/rational.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

namespace {
using namespace m1une::geometry;
using P = Point<long long>;

struct Data {
    int index;
    std::string color;
    Data() = delete;
    Data(int index, std::string color) : index(index), color(std::move(color)) {}
};
using Record = PointWithData<long long, Data>;

// Deliberately order and compare metadata: geometric algorithms must ignore it.
struct Vertex : P {
    int index;
    explicit Vertex(long long x, long long y, int index)
        : P(x, y), index(index) {}
    bool operator==(const Vertex&) const = default;
    bool operator<(const Vertex& other) const { return index < other.index; }
};

static_assert(PointRecord<P> && PointRecord<Record> && PointRecord<Vertex>);
static_assert(!PointRecord<int>);
static_assert(!std::default_initializable<Record>);
static_assert(std::same_as<decltype(Record(1, 2, Data(0, "red")) * 2), P>);

void test_records() {
    std::vector<Record> points;
    points.emplace_back(0, 0, Data(7, "red"));
    points.emplace_back(2, 0, Data(3, "green"));
    points.emplace_back(0, 2, Data(5, "blue"));
    points.emplace_back(0, 0, Data(1, "yellow"));
    const auto hull = convex_hull(points);
    static_assert(std::same_as<std::remove_cv_t<decltype(hull)>, std::vector<Record>>);
    assert(hull.size() == 3);
    assert(hull[0].data.index == 7 && hull[0].data.color == "red");
    assert(hull[1].data.index == 3 && hull[2].data.index == 5);
    assert(points[3].data.color == "yellow");
    assert(points[0] == points[3]);
    assert(orientation(points[0], points[1], points[2]) == 1);
    assert(distance2(points[1], points[2]) == 8);
    assert(Point<long double>(points[1]) == Point<long double>(2, 0));
    const auto closest = closest_pair(points);
    assert(closest && closest->first == 0 && closest->second == 3);
    assert(polygon_area2(hull) == 4);
    assert(is_simple_polygon(hull));
    assert(is_convex_polygon(hull));
    assert(convex_diameter2(hull) == 8);
    assert(point_in_polygon(hull, P(1, 0)) == PointInPolygon::Boundary);
    assert(point_in_convex_polygon(hull, points[0]) == PointInPolygon::Boundary);
    const auto center = centroid(hull);
    assert(center && std::fabs(center->x - 2.0L / 3) < 1e-12L);
    assert(polygon_center_of_gravity(hull) == center);
    assert(polygon_area(hull) == 2);
    const auto normalized = normalize_convex_polygon(hull);
    assert(normalized[0].data.index == 7);
    std::vector<Vertex> custom_triangle;
    custom_triangle.emplace_back(0, 0, 8);
    custom_triangle.emplace_back(2, 0, 2);
    custom_triangle.emplace_back(0, 2, 5);
    assert(delaunay_triangulation(custom_triangle).triangles.size() == 1);
    const auto triangulation = delaunay_triangulation(hull);
    assert(triangulation.triangles.size() == 1);
    // Other object-building APIs can explicitly discard metadata.
    assert(triangulate_polygon(to_points(hull))->size() == 1);
    assert(convex_hull<long long>(to_points(hull)).size() == 3);
    assert(closest_pair<long long>(to_points(hull))->distance_squared == 4);
    assert(minimum_enclosing_circle<long long>(to_points(hull)));

    PointWithData<long long, int> zero;
    assert(zero.x == 0 && zero.y == 0 && zero.data == 0);
    PointWithData<long long, int> positioned(3, 4);
    assert(positioned.data == 0);
    PointWithData<long long, int> from_point(P(3, 4), 12);
    from_point += P(1, 2);
    assert(from_point.x == 4 && from_point.y == 6 && from_point.data == 12);

    // Index-producing queries do not require copying or defaulting payloads.
    std::vector<PointWithData<long long, std::unique_ptr<int>>> owning;
    owning.emplace_back(0, 0, std::make_unique<int>(4));
    owning.emplace_back(2, 0, std::make_unique<int>(9));
    assert(closest_pair(owning)->distance_squared == 4);
    assert(farthest_pair(owning)->distance_squared == 4);
    assert(convex_layers(owning) == std::vector<int>(2, 1));
    assert(manhattan_mst(owning).cost == 2);
    assert(euclidean_mst(owning).cost == 2);
    assert(minimum_enclosing_circle(owning)->circle.radius == 1);
    assert(*owning[0].data == 4 && *owning[1].data == 9);

    using Fraction = m1une::math::Rational<>;
    std::vector<PointWithData<Fraction, int>> rational;
    rational.emplace_back(0, 0, 10);
    rational.emplace_back(Fraction(1, 2), 0, 20);
    rational.emplace_back(0, Fraction(1, 3), 30);
    const auto rational_hull = convex_hull(rational);
    assert(rational_hull[1].data == 20);
    assert(polygon_area2(rational_hull) == Fraction(1, 6));
    assert(closest_pair(rational)->distance_squared == Fraction(1, 9));

    std::vector<PointWithData<double, int>> floating;
    floating.emplace_back(0, 0, 1);
    floating.emplace_back(2, 0, 2);
    assert(minimum_enclosing_circle(floating)->circle.radius == 1);
    assert(convex_layers(floating) == std::vector<int>(2, 1));
}

void test_random() {
    std::mt19937 random(712367);
    for (int trial = 0; trial < 250; ++trial) {
        std::vector<Vertex> records;
        const int n = int(random() % 25);
        for (int i = 0; i < n; ++i) {
            records.emplace_back(int(random() % 13) - 6, int(random() % 13) - 6, i);
        }
        const auto plain = to_points(records);
        for (bool collinear : {false, true}) {
            const auto hull = convex_hull(records, collinear);
            assert(to_points(hull) == convex_hull(plain, collinear));
            for (const auto& point : hull) {
                auto first = std::find(plain.begin(), plain.end(), static_cast<const P&>(point));
                assert(point.index == first - plain.begin());
            }
            assert(convex_diameter2(hull) == convex_diameter2(to_points(hull)));
            assert(to_points(normalize_convex_polygon(hull)) ==
                normalize_convex_polygon(to_points(hull)));
        }
        assert(convex_layers(records) == convex_layers(plain));
        const auto sorted = angle_sorted(records, P(1, 2));
        assert(to_points(sorted) == angle_sorted(plain, P(1, 2)));
        for (const auto& point : sorted) {
            assert(static_cast<const P&>(point) == plain[point.index]);
        }
        const auto near = closest_pair(records);
        const auto far = farthest_pair(records);
        assert(bool(near) == (n >= 2) && bool(far) == (n >= 2));
        if (n >= 2) {
            __int128_t minimum = distance2(plain[0], plain[1]);
            __int128_t maximum = minimum;
            std::pair<int, int> nearest(0, 1), farthest(0, 1);
            for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
                auto squared = distance2(plain[i], plain[j]);
                if (squared < minimum) { minimum = squared; nearest = {i, j}; }
                if (maximum < squared) { maximum = squared; farthest = {i, j}; }
            }
            assert(near->distance_squared == minimum);
            assert(std::pair(near->first, near->second) == nearest);
            assert(far->distance_squared == maximum);
            assert(std::pair(far->first, far->second) == farthest);
            assert(furthest_pair(records)->distance_squared == maximum);
        }
        assert(manhattan_mst(records).cost == manhattan_mst(plain).cost);
        assert(euclidean_mst(records).cost == euclidean_mst(plain).cost);
        const auto circle = minimum_enclosing_circle(records);
        const auto reference = minimum_enclosing_circle(plain);
        assert(bool(circle) == bool(reference));
        if (circle) {
            assert(circle->circle.center == reference->circle.center);
            assert(circle->circle.radius == reference->circle.radius);
            assert(circle->support == reference->support);
        }
    }
}
}  // namespace

int main() {
    test_records();
    test_random();
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int test_count;
    input >> test_count;
    while (test_count--) {
        int n;
        input >> n;
        std::vector<Record> points;
        for (int i = 0; i < n; ++i) {
            long long x, y;
            input >> x >> y;
            points.emplace_back(x, y, Data(i, "red"));
        }
        const auto hull = convex_hull(std::move(points));
        output << hull.size() << '\n';
        for (const auto& point : hull) output << point.x << ' ' << point.y << '\n';
    }
}
