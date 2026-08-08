#ifndef M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP
#define M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "detail/convex_polygon_normalize.hpp"

namespace m1une {
namespace geometry {

// Returns the normalized boundary of the Minkowski sum of two nonempty
// ordered convex polygons.
template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
) {
    assert(!first.empty());
    assert(!second.empty());
    first = convex_polygon_detail::normalize_convex_boundary(
        std::move(first),
        eps
    );
    second = convex_polygon_detail::normalize_convex_boundary(
        std::move(second),
        eps
    );

    if (first.size() == 1 || second.size() == 1) {
        if (second.size() == 1) std::swap(first, second);
        for (Point<T>& point : second) point += first[0];
        return convex_polygon_detail::normalize_convex_boundary(
            std::move(second),
            eps
        );
    }

    std::vector<Point<T>> first_edges;
    std::vector<Point<T>> second_edges;
    first_edges.reserve(first.size());
    second_edges.reserve(second.size());
    for (std::size_t index = 0; index < first.size(); ++index) {
        first_edges.push_back(
            first[(index + 1) % first.size()] - first[index]
        );
    }
    for (std::size_t index = 0; index < second.size(); ++index) {
        second_edges.push_back(
            second[(index + 1) % second.size()] - second[index]
        );
    }

    Point<T> current = first.front() + second.front();
    std::vector<Point<T>> result;
    result.reserve(first.size() + second.size());
    result.push_back(current);
    std::size_t first_index = 0;
    std::size_t second_index = 0;
    while (
        first_index < first_edges.size() ||
        second_index < second_edges.size()
    ) {
        Point<T> step;
        if (first_index == first_edges.size()) {
            step = second_edges[second_index++];
        } else if (second_index == second_edges.size()) {
            step = first_edges[first_index++];
        } else {
            const auto turn = cross(
                first_edges[first_index],
                second_edges[second_index]
            );
            if (turn > 0) {
                step = first_edges[first_index++];
            } else if (turn < 0) {
                step = second_edges[second_index++];
            } else {
                step = first_edges[first_index++] +
                       second_edges[second_index++];
            }
        }
        current += step;
        if (
            first_index < first_edges.size() ||
            second_index < second_edges.size()
        ) {
            result.push_back(current);
        }
    }
    return convex_polygon_detail::normalize_convex_boundary(
        std::move(result),
        eps
    );
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_MINKOWSKI_SUM_HPP
