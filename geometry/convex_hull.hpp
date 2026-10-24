#ifndef M1UNE_GEOMETRY_CONVEX_HULL_HPP
#define M1UNE_GEOMETRY_CONVEX_HULL_HPP 1

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

// Returns the convex hull counterclockwise from its lexicographically smallest
// point. The first point is not repeated at the end. Equal coordinates retain
// the first input record, independently of metadata.
template <PointRecord P>
std::vector<P> convex_hull(
    std::vector<P> points,
    bool include_collinear = false
) {
    using T = typename P::coordinate_type;
    auto less = [](const Point<T>& a, const Point<T>& b) { return a < b; };
    if constexpr (std::same_as<P, Point<T>>) {
        std::sort(points.begin(), points.end(), less);
    } else {
        std::stable_sort(points.begin(), points.end(), less);
    }
    points.erase(
        std::unique(points.begin(), points.end(),
            [](const Point<T>& a, const Point<T>& b) { return a == b; }),
        points.end()
    );
    std::size_t size = points.size();
    if (size <= 1) return points;

    std::vector<P> hull;
    hull.reserve(2 * size);
    auto should_pop = [include_collinear](
        const Point<T>& first,
        const Point<T>& second,
        const Point<T>& third
    ) {
        int turn = orientation(first, second, third);
        return include_collinear ? turn < 0 : turn <= 0;
    };

    for (const P& point : points) {
        while (
            hull.size() >= 2 &&
            should_pop(hull[hull.size() - 2], hull.back(), point)
        ) {
            hull.pop_back();
        }
        hull.push_back(point);
    }

    std::size_t lower_size = hull.size();
    for (std::size_t index = size - 1; index-- > 0;) {
        const P& point = points[index];
        while (
            hull.size() > lower_size &&
            should_pop(hull[hull.size() - 2], hull.back(), point)
        ) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    hull.pop_back();

    if (include_collinear && hull.size() == 2 * points.size() - 2) {
        hull = std::move(points);
    }
    return hull;
}

template <Coordinate T>
std::vector<Point<T>> convex_hull(
    std::vector<Point<T>> points,
    bool include_collinear = false
) {
    return convex_hull<Point<T>>(std::move(points), include_collinear);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CONVEX_HULL_HPP
