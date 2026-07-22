#define PROBLEM "https://judge.yosupo.jp/problem/euclidean_mst"

#include "../../geometry/convex_hull.hpp"
#include "../../geometry/delaunay_triangulation.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "../../ds/dsu/dsu.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using Point = m1une::geometry::Point<long long>;
using Wide = __int128_t;

bool inside_circumcircle(
    const Point& first,
    const Point& second,
    const Point& third,
    const Point& point
) {
    Wide ax = Wide(first.x) - Wide(point.x);
    Wide ay = Wide(first.y) - Wide(point.y);
    Wide bx = Wide(second.x) - Wide(point.x);
    Wide by = Wide(second.y) - Wide(point.y);
    Wide cx = Wide(third.x) - Wide(point.x);
    Wide cy = Wide(third.y) - Wide(point.y);
    Wide first_norm = ax * ax + ay * ay;
    Wide second_norm = bx * bx + by * by;
    Wide third_norm = cx * cx + cy * cy;
    Wide determinant =
        (bx * cy - by * cx) * first_norm +
        (cx * ay - cy * ax) * second_norm +
        (ax * by - ay * bx) * third_norm;
    return determinant > 0;
}

void check(const std::vector<Point>& points) {
    auto triangulation = m1une::geometry::delaunay_triangulation(points);
    assert(std::is_sorted(
        triangulation.edges.begin(),
        triangulation.edges.end()
    ));
    assert(std::adjacent_find(
        triangulation.edges.begin(),
        triangulation.edges.end()
    ) == triangulation.edges.end());
    assert(std::is_sorted(
        triangulation.triangles.begin(),
        triangulation.triangles.end()
    ));
    assert(std::adjacent_find(
        triangulation.triangles.begin(),
        triangulation.triangles.end()
    ) == triangulation.triangles.end());

    std::set<std::pair<int, int>> edge_set;
    for (auto [first, second] : triangulation.edges) {
        assert(0 <= first && first < int(points.size()));
        assert(0 <= second && second < int(points.size()));
        assert(first < second);
        edge_set.emplace(first, second);
    }

    std::vector<int> incidence(triangulation.edges.size(), 0);
    Wide triangle_area_twice = 0;
    for (const auto& triangle : triangulation.triangles) {
        int first = triangle[0];
        int second = triangle[1];
        int third = triangle[2];
        assert(first < second && first < third);
        Wide area = m1une::geometry::cross(
            points[first],
            points[second],
            points[third]
        );
        assert(area > 0);
        triangle_area_twice += area;

        for (int side = 0; side < 3; ++side) {
            int from = triangle[side];
            int to = triangle[(side + 1) % 3];
            if (from > to) std::swap(from, to);
            auto iterator = edge_set.find(std::pair(from, to));
            assert(iterator != edge_set.end());
            auto sorted_iterator = std::lower_bound(
                triangulation.edges.begin(),
                triangulation.edges.end(),
                *iterator
            );
            ++incidence[sorted_iterator - triangulation.edges.begin()];
        }
        for (const Point& point : points) {
            assert(!inside_circumcircle(
                points[first],
                points[second],
                points[third],
                point
            ));
        }
    }

    std::vector<Point> hull = m1une::geometry::convex_hull(points, true);
    bool non_collinear = false;
    for (int index = 2; index < int(points.size()); ++index) {
        if (m1une::geometry::orientation(
                points[0],
                points[1],
                points[index]
            ) != 0) {
            non_collinear = true;
        }
    }
    if (!non_collinear) {
        assert(triangulation.triangles.empty());
        assert(triangulation.edges.size() ==
               (points.empty() ? 0 : points.size() - 1));
        return;
    }

    int size = int(points.size());
    int hull_size = int(hull.size());
    assert(int(triangulation.edges.size()) == 3 * size - 3 - hull_size);
    assert(int(triangulation.triangles.size()) == 2 * size - 2 - hull_size);
    for (int count : incidence) assert(count == 1 || count == 2);

    Wide hull_area_twice = 0;
    for (int index = 0; index < hull_size; ++index) {
        hull_area_twice += m1une::geometry::cross(
            hull[index],
            hull[(index + 1) % hull_size]
        );
    }
    assert(triangle_area_twice == hull_area_twice);
}

void test_fixed() {
    check({});
    check({Point(3, -2)});
    check({Point(0, 0), Point(7, 1)});
    check({
        Point(-5, 0),
        Point(-2, 0),
        Point(1, 0),
        Point(7, 0),
    });
    check({Point(0, 0), Point(4, 0), Point(1, 3)});
    check({
        Point(0, 0),
        Point(2, 0),
        Point(2, 2),
        Point(0, 2),
    });
    check({
        Point(5, 0),
        Point(3, 4),
        Point(0, 5),
        Point(-3, 4),
        Point(-5, 0),
        Point(-3, -4),
        Point(0, -5),
        Point(3, -4),
    });
    check({
        Point(0, 0),
        Point(2, 0),
        Point(4, 0),
        Point(4, 3),
        Point(0, 3),
        Point(2, 1),
    });
    check({
        Point(0, 0),
        Point(4, 0),
        Point(5, 3),
        Point(2, 6),
        Point(-1, 3),
        Point(2, 3),
    });
}

void test_randomized() {
    std::uint64_t state = 0xd31a'2026'0722ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        int size = int(random() % 15);
        std::set<std::pair<long long, long long>> coordinates;
        while (int(coordinates.size()) < size) {
            coordinates.emplace(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
        }
        std::vector<Point> points;
        for (auto [x, y] : coordinates) points.emplace_back(x, y);
        std::shuffle(
            points.begin(),
            points.end(),
            std::mt19937_64(random())
        );
        check(points);
    }
}

std::vector<std::pair<int, int>> delaunay_mst(
    const std::vector<Point>& points
) {
    struct Edge {
        int from;
        int to;
        Wide squared_distance;
    };

    std::vector<int> order(points.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int first, int second) {
        return points[first] < points[second];
    });

    std::vector<Point> unique_points;
    std::vector<int> representatives;
    std::vector<Edge> candidates;
    unique_points.reserve(points.size());
    representatives.reserve(points.size());
    candidates.reserve(3 * points.size());
    for (int index : order) {
        if (unique_points.empty() || unique_points.back() != points[index]) {
            unique_points.push_back(points[index]);
            representatives.push_back(index);
        } else {
            candidates.push_back(Edge{index, representatives.back(), 0});
        }
    }

    auto triangulation =
        m1une::geometry::delaunay_triangulation(unique_points);
    for (auto [first, second] : triangulation.edges) {
        int from = representatives[first];
        int to = representatives[second];
        candidates.push_back(Edge{
            from,
            to,
            m1une::geometry::distance2(points[from], points[to]),
        });
    }
    std::sort(
        candidates.begin(),
        candidates.end(),
        [](const Edge& left, const Edge& right) {
            if (left.squared_distance != right.squared_distance) {
                return left.squared_distance < right.squared_distance;
            }
            if (left.from != right.from) return left.from < right.from;
            return left.to < right.to;
        }
    );

    m1une::ds::Dsu dsu(int(points.size()));
    std::vector<std::pair<int, int>> result;
    for (const Edge& edge : candidates) {
        if (dsu.same(edge.from, edge.to)) continue;
        dsu.merge(edge.from, edge.to);
        result.emplace_back(edge.from, edge.to);
    }
    assert(points.empty() || result.size() + 1 == points.size());
    return result;
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    int size;
    fast_input >> size;
    std::vector<Point> points(size);
    for (Point& point : points) fast_input >> point.x >> point.y;
    for (auto [from, to] : delaunay_mst(points)) {
        fast_output << from << ' ' << to << '\n';
    }
}
