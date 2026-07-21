#define PROBLEM "https://judge.yosupo.jp/problem/count_points_in_triangle"

#include "../../geometry/count_points_in_triangle.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;

int naive_count(
    const std::vector<Point>& vertices,
    const std::vector<Point>& points,
    int first,
    int second,
    int third
) {
    const auto determinant = m1une::geometry::cross(
        vertices[first],
        vertices[second],
        vertices[third]
    );
    if (determinant == 0) return 0;

    int result = 0;
    for (const Point& point : points) {
        const auto first_side = m1une::geometry::cross(
            vertices[first],
            vertices[second],
            point
        );
        const auto second_side = m1une::geometry::cross(
            vertices[second],
            vertices[third],
            point
        );
        const auto third_side = m1une::geometry::cross(
            vertices[third],
            vertices[first],
            point
        );
        if (determinant > 0) {
            result += first_side > 0 && second_side > 0 && third_side > 0;
        } else {
            result += first_side < 0 && second_side < 0 && third_side < 0;
        }
    }
    return result;
}

void check_all_queries(
    const std::vector<Point>& vertices,
    const std::vector<Point>& points
) {
    m1une::geometry::CountPointsInTriangle<long long> counter(
        vertices,
        points
    );
    for (int first = 0; first < int(vertices.size()); ++first) {
        for (int second = 0; second < int(vertices.size()); ++second) {
            for (int third = 0; third < int(vertices.size()); ++third) {
                assert(
                    counter.query(first, second, third) ==
                    naive_count(
                        vertices,
                        points,
                        first,
                        second,
                        third
                    )
                );
            }
        }
    }
}

void test_fixed() {
    std::vector<Point> vertices;
    vertices.emplace_back(0, 0);
    vertices.emplace_back(4, 0);
    vertices.emplace_back(0, 4);
    vertices.emplace_back(4, 4);
    vertices.emplace_back(0, 0);
    vertices.emplace_back(2, 0);

    std::vector<Point> points;
    points.emplace_back(1, 1);
    points.emplace_back(2, 1);
    points.emplace_back(0, 1);
    points.emplace_back(2, 2);
    points.emplace_back(4, 4);
    points.emplace_back(1, 1);
    points.emplace_back(-1, -1);
    check_all_queries(vertices, points);

    std::vector<Point> extreme_vertices;
    extreme_vertices.emplace_back(-1000000000LL, -1000000000LL);
    extreme_vertices.emplace_back(1000000000LL, -1000000000LL);
    extreme_vertices.emplace_back(0, 1000000000LL);
    std::vector<Point> extreme_points;
    extreme_points.emplace_back(0, 0);
    extreme_points.emplace_back(0, -1000000000LL);
    extreme_points.emplace_back(1000000000LL, 1000000000LL);
    check_all_queries(extreme_vertices, extreme_points);

    std::vector<Point> no_points;
    check_all_queries(vertices, no_points);
}

void test_randomized() {
    std::uint64_t state = 0x9e3779b97f4a7c15ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; ++trial) {
        const int vertex_count = 1 + int(random() % 11);
        const int point_count = int(random() % 18);
        std::vector<Point> vertices;
        std::vector<Point> points;
        vertices.reserve(vertex_count);
        points.reserve(point_count);
        for (int index = 0; index < vertex_count; ++index) {
            vertices.emplace_back(
                static_cast<long long>(random() % 11) - 5,
                static_cast<long long>(random() % 11) - 5
            );
        }
        for (int index = 0; index < point_count; ++index) {
            points.emplace_back(
                static_cast<long long>(random() % 11) - 5,
                static_cast<long long>(random() % 11) - 5
            );
        }
        check_all_queries(vertices, points);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    int vertex_count;
    fast_input >> vertex_count;
    std::vector<Point> vertices(vertex_count);
    for (Point& point : vertices) fast_input >> point.x >> point.y;

    int point_count;
    fast_input >> point_count;
    std::vector<Point> points(point_count);
    for (Point& point : points) fast_input >> point.x >> point.y;

    m1une::geometry::CountPointsInTriangle<long long> counter(
        vertices,
        points
    );
    int query_count;
    fast_input >> query_count;
    for (int query = 0; query < query_count; ++query) {
        int first, second, third;
        fast_input >> first >> second >> third;
        fast_output << counter.query(first, second, third) << '\n';
    }
}
