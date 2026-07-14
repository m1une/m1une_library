#define PROBLEM "https://judge.yosupo.jp/problem/euclidean_mst"

#include "../../geometry/euclidean_mst.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../ds/dsu/dsu.hpp"

namespace {

using Point = m1une::geometry::Point<long long>;
using Wide = __int128_t;

Wide squared_distance(const Point& a, const Point& b) {
    return m1une::geometry::distance2(a, b);
}

std::vector<Wide> brute_force_weights(const std::vector<Point>& points) {
    struct Edge {
        int from;
        int to;
        Wide squared_distance;
    };

    std::vector<Edge> edges;
    for (int i = 0; i < int(points.size()); i++) {
        for (int j = 0; j < i; j++) {
            edges.push_back(Edge{i, j, squared_distance(points[i], points[j])});
        }
    }
    std::sort(edges.begin(), edges.end(), [](const Edge& left, const Edge& right) {
        return left.squared_distance < right.squared_distance;
    });

    m1une::ds::Dsu dsu(int(points.size()));
    std::vector<Wide> result;
    for (const auto& edge : edges) {
        if (dsu.same(edge.from, edge.to)) continue;
        dsu.merge(edge.from, edge.to);
        result.push_back(edge.squared_distance);
    }
    std::sort(result.begin(), result.end());
    return result;
}

void check(const std::vector<Point>& points) {
    auto candidates = m1une::geometry::euclidean_mst_edges(points);
    assert(candidates.size() <= 4 * points.size());
    for (const auto& edge : candidates) {
        assert(0 <= edge.from && edge.from < int(points.size()));
        assert(0 <= edge.to && edge.to < int(points.size()));
        assert(edge.from != edge.to);
        assert(edge.squared_distance == squared_distance(points[edge.from], points[edge.to]));
    }

    auto mst = m1une::geometry::euclidean_mst(points);
    assert(mst.edges.size() == (points.empty() ? 0 : points.size() - 1));
    m1une::ds::Dsu dsu(int(points.size()));
    std::vector<Wide> weights;
    long double cost = 0;
    for (const auto& edge : mst.edges) {
        assert(!dsu.same(edge.from, edge.to));
        dsu.merge(edge.from, edge.to);
        weights.push_back(edge.squared_distance);
        cost += std::sqrt(static_cast<long double>(edge.squared_distance));
    }
    std::sort(weights.begin(), weights.end());
    assert(weights == brute_force_weights(points));
    assert(std::abs(mst.cost - cost) <= 1e-12L * (1 + cost));
}

void test_fixed() {
    check({});
    check({Point(2, -3)});
    check({Point(0, 0), Point(0, 0), Point(0, 0)});
    check({Point(-5, 0), Point(-2, 0), Point(1, 0), Point(7, 0)});
    check({Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)});
    check({
        Point(0, 0),
        Point(2, 0),
        Point(2, 2),
        Point(0, 2),
        Point(1, 1),
        Point(1, 1),
    });
}

void test_randomized() {
    std::uint64_t state = 20260714;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int size = int(random() % 15);
        std::vector<Point> points;
        points.reserve(size);
        for (int i = 0; i < size; i++) {
            points.emplace_back(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
        }
        check(points);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    int n;
    fast_input >> n;
    std::vector<Point> points;
    points.reserve(n);
    for (int i = 0; i < n; i++) {
        long long x, y;
        fast_input >> x >> y;
        points.emplace_back(x, y);
    }

    auto mst = m1une::geometry::euclidean_mst(points);
    for (const auto& edge : mst.edges) {
        fast_output << edge.from << ' ' << edge.to << '\n';
    }
}
