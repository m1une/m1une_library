#ifndef M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP
#define M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP 1

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

#include "../point.hpp"

namespace m1une {
namespace geometry {
namespace convex_polygon_detail {

template <Coordinate T>
wide_type<T> boundary_area2(const std::vector<Point<T>>& polygon) {
    wide_type<T> result = 0;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        result += cross(
            polygon[index],
            polygon[(index + 1) % polygon.size()]
        );
    }
    return result;
}

template <Coordinate T>
std::vector<Point<T>> normalize_convex_boundary(
    std::vector<Point<T>> polygon,
    long double eps
) {
    if (polygon.size() >= 2 && polygon.front() == polygon.back()) {
        polygon.pop_back();
    }
    polygon.erase(
        std::unique(polygon.begin(), polygon.end()),
        polygon.end()
    );
    if (polygon.size() >= 2 && polygon.front() == polygon.back()) {
        polygon.pop_back();
    }
    if (polygon.size() <= 1) return polygon;
    if (
        polygon.size() >= 3 &&
        sign<T>(boundary_area2(polygon), eps) < 0
    ) {
        std::reverse(polygon.begin(), polygon.end());
    }

    const auto start = std::min_element(
        polygon.begin(),
        polygon.end(),
        [](const Point<T>& first, const Point<T>& second) {
            if (first.y != second.y) return first.y < second.y;
            return first.x < second.x;
        }
    );
    std::rotate(polygon.begin(), start, polygon.end());

    if (polygon.size() >= 3) {
        std::vector<Point<T>> cleaned;
        const std::size_t size = polygon.size();
        cleaned.reserve(size);
        for (std::size_t index = 0; index < size; ++index) {
            const Point<T>& previous = polygon[(index + size - 1) % size];
            const Point<T>& current = polygon[index];
            const Point<T>& next = polygon[(index + 1) % size];
            if (
                orientation(previous, current, next, eps) != 0 ||
                sign<T>(dot(current - previous, next - current), eps) < 0
            ) {
                cleaned.push_back(current);
            }
        }
        polygon = std::move(cleaned);
    }
    return polygon;
}

}  // namespace convex_polygon_detail
}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_DETAIL_CONVEX_POLYGON_NORMALIZE_HPP
