#ifndef M1UNE_GEOMETRY_DELAUNAY_TRIANGULATION_HPP
#define M1UNE_GEOMETRY_DELAUNAY_TRIANGULATION_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "euclidean_mst.hpp"

namespace m1une {
namespace geometry {

struct DelaunayTriangulation {
    std::vector<std::pair<int, int>> edges;
    std::vector<std::array<int, 3>> triangles;
};

namespace delaunay_triangulation_detail {

template <std::integral T>
int direction_half(
    const Point<T>& origin,
    const Point<T>& destination
) {
    using W = wide_type<T>;
    W x = W(destination.x) - W(origin.x);
    W y = W(destination.y) - W(origin.y);
    return y > 0 || (y == 0 && x >= 0) ? 0 : 1;
}

template <std::integral T>
bool direction_less(
    const std::vector<Point<T>>& points,
    int origin,
    int first,
    int second
) {
    int first_half = direction_half(points[origin], points[first]);
    int second_half = direction_half(points[origin], points[second]);
    if (first_half != second_half) return first_half < second_half;

    using W = wide_type<T>;
    W first_x = W(points[first].x) - W(points[origin].x);
    W first_y = W(points[first].y) - W(points[origin].y);
    W second_x = W(points[second].x) - W(points[origin].x);
    W second_y = W(points[second].y) - W(points[origin].y);
    W product = first_x * second_y - first_y * second_x;
    if (product != 0) return product > 0;

    W first_norm = first_x * first_x + first_y * first_y;
    W second_norm = second_x * second_x + second_y * second_y;
    if (first_norm != second_norm) return first_norm < second_norm;
    return first < second;
}

inline void rotate_minimum_first(std::array<int, 3>& triangle) {
    int minimum = int(std::min_element(triangle.begin(), triangle.end()) -
                      triangle.begin());
    std::rotate(
        triangle.begin(),
        triangle.begin() + minimum,
        triangle.end()
    );
}

}  // namespace delaunay_triangulation_detail

// Constructs one Delaunay triangulation of distinct integral points.
template <std::integral T>
DelaunayTriangulation delaunay_triangulation(
    const std::vector<Point<T>>& points
) {
    namespace detail = delaunay_triangulation_detail;

    DelaunayTriangulation result;
    geometry::detail::EuclideanDelaunay<T> builder(points);
    assert(!builder.has_duplicates());
    result.edges = builder.get_edges();
    for (auto& [first, second] : result.edges) {
        if (first > second) std::swap(first, second);
    }
    std::sort(result.edges.begin(), result.edges.end());
    result.edges.erase(
        std::unique(result.edges.begin(), result.edges.end()),
        result.edges.end()
    );

    std::vector<std::vector<int>> neighbors(points.size());
    for (auto [first, second] : result.edges) {
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
    }
    for (int point = 0; point < int(points.size()); ++point) {
        std::sort(
            neighbors[point].begin(),
            neighbors[point].end(),
            [&](int first, int second) {
                return detail::direction_less(points, point, first, second);
            }
        );
    }

    auto has_edge = [&](int first, int second) {
        if (first > second) std::swap(first, second);
        return std::binary_search(
            result.edges.begin(),
            result.edges.end(),
            std::pair(first, second)
        );
    };
    result.triangles.reserve(result.edges.size());
    for (int point = 0; point < int(points.size()); ++point) {
        int degree = int(neighbors[point].size());
        for (int index = 0; index < degree; ++index) {
            int first = neighbors[point][index];
            int second = neighbors[point][(index + 1) % degree];
            if (orientation(points[point], points[first], points[second]) <= 0) {
                continue;
            }
            if (!has_edge(first, second)) continue;
            std::array<int, 3> triangle{point, first, second};
            detail::rotate_minimum_first(triangle);
            result.triangles.push_back(triangle);
        }
    }
    std::sort(result.triangles.begin(), result.triangles.end());
    result.triangles.erase(
        std::unique(result.triangles.begin(), result.triangles.end()),
        result.triangles.end()
    );
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_DELAUNAY_TRIANGULATION_HPP
