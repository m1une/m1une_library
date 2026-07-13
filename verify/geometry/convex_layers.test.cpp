#define PROBLEM "https://judge.yosupo.jp/problem/convex_layers"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "../../geometry/convex_hull.hpp"
#include "../../geometry/convex_layers.hpp"
#include "../../geometry/point.hpp"

namespace {

using Point = m1une::geometry::Point<long long>;

std::vector<int> naive_convex_layers(const std::vector<Point>& points) {
    const int n = int(points.size());
    std::vector<int> result(n, 0);
    int remaining = n;
    for (int layer = 1; remaining > 0; layer++) {
        std::vector<Point> active;
        for (int index = 0; index < n; index++) {
            if (result[index] == 0) active.push_back(points[index]);
        }
        std::vector<Point> hull = m1une::geometry::convex_hull(active, true);
        for (int index = 0; index < n; index++) {
            if (result[index] != 0) continue;
            if (std::find(hull.begin(), hull.end(), points[index]) == hull.end()) {
                continue;
            }
            result[index] = layer;
            remaining--;
        }
    }
    return result;
}

void test_randomized() {
    assert(m1une::geometry::convex_layers(std::vector<Point>()).empty());

    std::uint64_t state = 0x3141592653589793ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int test = 0; test < 500; test++) {
        const int n = int(random() % 45);
        std::vector<Point> points;
        points.reserve(n);
        for (int index = 0; index < n; index++) {
            points.emplace_back(
                static_cast<long long>(random() % 17) - 8,
                static_cast<long long>(random() % 17) - 8
            );
        }
        assert(
            m1une::geometry::convex_layers(points) ==
            naive_convex_layers(points)
        );
    }
}

void test_coordinate_types() {
    std::vector<m1une::geometry::Point<long double>> floating;
    floating.emplace_back(0.5L, 0.5L);
    floating.emplace_back(4.5L, 0.5L);
    floating.emplace_back(4.5L, 4.5L);
    floating.emplace_back(0.5L, 4.5L);
    floating.emplace_back(2.5L, 2.5L);
    std::vector<int> expected_floating = {1, 1, 1, 1, 2};
    assert(m1une::geometry::convex_layers(floating) == expected_floating);

    const long long base = std::numeric_limits<long long>::lowest();
    std::vector<Point> extreme;
    extreme.emplace_back(base, base);
    extreme.emplace_back(base + 4, base);
    extreme.emplace_back(base + 4, base + 4);
    extreme.emplace_back(base, base + 4);
    extreme.emplace_back(base + 2, base + 2);
    std::vector<int> expected_extreme = {1, 1, 1, 1, 2};
    assert(m1une::geometry::convex_layers(extreme) == expected_extreme);
}

}  // namespace

int main() {
    test_coordinate_types();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int point_count;
    std::cin >> point_count;
    std::vector<Point> points(point_count);
    for (Point& point : points) std::cin >> point.x >> point.y;

    for (int layer : m1une::geometry::convex_layers(points)) {
        std::cout << layer << '\n';
    }
}
