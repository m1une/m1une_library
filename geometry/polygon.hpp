#ifndef M1UNE_GEOMETRY_POLYGON_HPP
#define M1UNE_GEOMETRY_POLYGON_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <vector>

#include "ray.hpp"

namespace m1une {
namespace geometry {

enum class PointInPolygon {
    Outside = 0,
    Boundary = 1,
    Inside = 2,
};

namespace polygon_detail {

inline bool close(
    const Point<long double>& first,
    const Point<long double>& second,
    long double eps
) {
    return geometry::distance(first, second) <= eps;
}

inline void push_unique(
    std::vector<Point<long double>>& points,
    const Point<long double>& point,
    long double eps
) {
    for (const Point<long double>& existing : points) {
        if (close(existing, point, eps)) return;
    }
    points.push_back(point);
}

template <Coordinate T>
std::vector<Point<T>> clean_polygon_vertices(
    std::vector<Point<T>> polygon,
    long double eps
) {
    if (
        polygon.size() >= 2 &&
        polygon.front() == polygon.back()
    ) {
        polygon.pop_back();
    }

    std::vector<Point<T>> deduplicated;
    for (const Point<T>& point : polygon) {
        if (deduplicated.empty() || deduplicated.back() != point) {
            deduplicated.push_back(point);
        }
    }
    if (
        deduplicated.size() >= 2 &&
        deduplicated.front() == deduplicated.back()
    ) {
        deduplicated.pop_back();
    }

    bool changed = true;
    while (changed && deduplicated.size() >= 3) {
        changed = false;
        std::vector<Point<T>> cleaned;
        std::size_t size = deduplicated.size();
        for (std::size_t index = 0; index < size; ++index) {
            const Point<T>& previous =
                deduplicated[(index + size - 1) % size];
            const Point<T>& current = deduplicated[index];
            const Point<T>& next =
                deduplicated[(index + 1) % size];
            if (
                orientation(previous, current, next, eps) == 0 &&
                sign<T>(dot(current - previous, next - current), eps) >= 0
            ) {
                changed = true;
            } else {
                cleaned.push_back(current);
            }
        }
        deduplicated = std::move(cleaned);
    }
    return deduplicated;
}

template <Coordinate T>
bool in_ccw_triangle(
    const Point<T>& point,
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps
) {
    return
        orientation(first, second, point, eps) >= 0 &&
        orientation(second, third, point, eps) >= 0 &&
        orientation(third, first, point, eps) >= 0;
}

}  // namespace polygon_detail

template <Coordinate T>
wide_type<T> polygon_area2(const std::vector<Point<T>>& polygon) {
    wide_type<T> result = 0;
    std::size_t n = polygon.size();
    for (std::size_t i = 0; i < n; i++) {
        result += cross(polygon[i], polygon[(i + 1) % n]);
    }
    return result;
}

template <Coordinate T>
long double polygon_area(const std::vector<Point<T>>& polygon) {
    return std::fabs(static_cast<long double>(polygon_area2(polygon))) / 2;
}

template <Coordinate T>
std::optional<Point<long double>> polygon_centroid(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    if (polygon.size() < 3) return std::nullopt;

    wide_type<T> signed_area2 = polygon_area2(polygon);
    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;

    long double x_numerator = 0;
    long double y_numerator = 0;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        long double weight = static_cast<long double>(cross(current, next));
        x_numerator +=
            (static_cast<long double>(current.x) +
             static_cast<long double>(next.x)) *
            weight;
        y_numerator +=
            (static_cast<long double>(current.y) +
             static_cast<long double>(next.y)) *
            weight;
    }
    long double denominator =
        3.0L * static_cast<long double>(signed_area2);
    return Point<long double>(
        x_numerator / denominator,
        y_numerator / denominator
    );
}

template <Coordinate T>
std::optional<Point<long double>> polygon_center_of_gravity(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    return polygon_centroid(polygon, eps);
}

template <Coordinate T>
bool is_simple_polygon(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    if (polygon.size() < 3) return false;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& previous = polygon[(index + size - 1) % size];
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        if (current == next) return false;
        if (
            orientation(previous, current, next, eps) == 0 &&
            sign<T>(dot(current - previous, next - current), eps) < 0
        ) {
            return false;
        }
    }
    for (std::size_t first_index = 0; first_index < size; ++first_index) {
        Segment<T> first{
            polygon[first_index],
            polygon[(first_index + 1) % size]
        };
        for (
            std::size_t second_index = first_index + 1;
            second_index < size;
            ++second_index
        ) {
            bool adjacent =
                second_index == first_index + 1 ||
                (first_index == 0 && second_index + 1 == size);
            if (adjacent) continue;

            Segment<T> second{
                polygon[second_index],
                polygon[(second_index + 1) % size]
            };
            if (intersects(first, second, eps)) return false;
        }
    }
    return true;
}

template <Coordinate T>
std::optional<std::vector<std::array<Point<T>, 3>>> triangulate_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon =
        polygon_detail::clean_polygon_vertices(std::move(polygon), eps);
    if (polygon.size() < 3) return std::nullopt;

    wide_type<T> signed_area2 = polygon_area2(polygon);
    if (sign<T>(signed_area2, eps) == 0) return std::nullopt;
    if (!is_simple_polygon(polygon, eps)) return std::nullopt;
    if (sign<T>(signed_area2, eps) < 0) {
        std::reverse(polygon.begin(), polygon.end());
    }

    std::vector<std::size_t> remaining(polygon.size());
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        remaining[index] = index;
    }

    std::vector<std::array<Point<T>, 3>> result;
    result.reserve(polygon.size() - 2);
    while (remaining.size() > 3) {
        bool found_ear = false;
        std::size_t size = remaining.size();
        for (std::size_t position = 0; position < size; ++position) {
            std::size_t previous_index =
                remaining[(position + size - 1) % size];
            std::size_t current_index = remaining[position];
            std::size_t next_index =
                remaining[(position + 1) % size];
            const Point<T>& previous = polygon[previous_index];
            const Point<T>& current = polygon[current_index];
            const Point<T>& next = polygon[next_index];
            if (orientation(previous, current, next, eps) <= 0) continue;

            bool contains_vertex = false;
            for (std::size_t other_index : remaining) {
                if (
                    other_index == previous_index ||
                    other_index == current_index ||
                    other_index == next_index
                ) {
                    continue;
                }
                if (
                    polygon_detail::in_ccw_triangle(
                        polygon[other_index],
                        previous,
                        current,
                        next,
                        eps
                    )
                ) {
                    contains_vertex = true;
                    break;
                }
            }
            if (contains_vertex) continue;

            std::array<Point<T>, 3> triangle;
            triangle[0] = previous;
            triangle[1] = current;
            triangle[2] = next;
            result.push_back(std::move(triangle));
            remaining.erase(
                remaining.begin() +
                static_cast<std::ptrdiff_t>(position)
            );
            found_ear = true;
            break;
        }
        if (!found_ear) return std::nullopt;
    }

    std::array<Point<T>, 3> triangle;
    triangle[0] = polygon[remaining[0]];
    triangle[1] = polygon[remaining[1]];
    triangle[2] = polygon[remaining[2]];
    if (orientation(triangle[0], triangle[1], triangle[2], eps) <= 0) {
        return std::nullopt;
    }
    result.push_back(std::move(triangle));
    return result;
}

template <Coordinate T>
PointInPolygon point_in_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    bool inside = false;
    std::size_t n = polygon.size();
    for (std::size_t i = 0; i < n; i++) {
        const Point<T>& a = polygon[i];
        const Point<T>& b = polygon[(i + 1) % n];
        if (on_segment(Segment<T>{a, b}, point, eps)) {
            return PointInPolygon::Boundary;
        }

        if (a.y <= point.y) {
            if (point.y < b.y && orientation(a, b, point, eps) > 0) {
                inside = !inside;
            }
        } else if (b.y <= point.y && orientation(a, b, point, eps) < 0) {
            inside = !inside;
        }
    }
    return inside ? PointInPolygon::Inside : PointInPolygon::Outside;
}

template <Coordinate T>
std::vector<Point<long double>> ray_polygon_intersections(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(polygon.size() >= 3);
    std::vector<Point<long double>> result;
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        Segment<T> edge{
            polygon[index],
            polygon[(index + 1) % size]
        };
        std::optional<Point<long double>> point =
            ray_segment_intersection(ray, edge, eps);
        if (point.has_value()) {
            polygon_detail::push_unique(result, *point, eps);
            continue;
        }
        if (
            orientation(ray.origin, ray.through, edge.a, eps) == 0 &&
            orientation(ray.origin, ray.through, edge.b, eps) == 0
        ) {
            if (on_ray(ray, edge.a, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(edge.a),
                    eps
                );
            }
            if (on_ray(ray, edge.b, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(edge.b),
                    eps
                );
            }
            if (on_segment(edge, ray.origin, eps)) {
                polygon_detail::push_unique(
                    result,
                    Point<long double>(ray.origin),
                    eps
                );
            }
        }
    }

    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    std::sort(
        result.begin(),
        result.end(),
        [&](const Point<long double>& first, const Point<long double>& second) {
            return dot(first - origin, direction) <
                   dot(second - origin, direction);
        }
    );
    return result;
}

template <Coordinate T>
std::optional<Point<long double>> first_ray_polygon_intersection(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    std::vector<Point<long double>> points =
        ray_polygon_intersections(ray, polygon, eps);
    if (points.empty()) return std::nullopt;
    return points.front();
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    assert(polygon.size() >= 3);
    if (point_in_polygon(polygon, ray.origin, eps) != PointInPolygon::Outside) {
        return true;
    }
    return !ray_polygon_intersections(ray, polygon, eps).empty();
}

template <Coordinate T>
bool intersects(
    const std::vector<Point<T>>& polygon,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, polygon, eps);
}

template <Coordinate T>
long double distance(
    const Ray<T>& ray,
    const std::vector<Point<T>>& polygon
) {
    assert(polygon.size() >= 3);
    if (intersects(ray, polygon)) return 0;
    long double result = std::numeric_limits<long double>::infinity();
    std::size_t size = polygon.size();
    for (std::size_t index = 0; index < size; ++index) {
        result = std::min(
            result,
            distance(
                ray,
                Segment<T>{
                    polygon[index],
                    polygon[(index + 1) % size]
                }
            )
        );
    }
    return result;
}

template <Coordinate T>
long double distance(
    const std::vector<Point<T>>& polygon,
    const Ray<T>& ray
) {
    return distance(ray, polygon);
}

template <Coordinate T>
bool intersects(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    assert(first.size() >= 3);
    assert(second.size() >= 3);
    std::size_t first_size = first.size();
    std::size_t second_size = second.size();
    for (
        std::size_t first_index = 0;
        first_index < first_size;
        ++first_index
    ) {
        Segment<T> first_edge{
            first[first_index],
            first[(first_index + 1) % first_size]
        };
        for (
            std::size_t second_index = 0;
            second_index < second_size;
            ++second_index
        ) {
            Segment<T> second_edge{
                second[second_index],
                second[(second_index + 1) % second_size]
            };
            if (intersects(first_edge, second_edge, eps)) return true;
        }
    }
    return
        point_in_polygon(first, second.front(), eps) !=
            PointInPolygon::Outside ||
        point_in_polygon(second, first.front(), eps) !=
            PointInPolygon::Outside;
}

template <Coordinate T>
long double distance(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second
) {
    assert(first.size() >= 3);
    assert(second.size() >= 3);
    if (intersects(first, second)) return 0;

    long double result = std::numeric_limits<long double>::infinity();
    std::size_t first_size = first.size();
    std::size_t second_size = second.size();
    for (
        std::size_t first_index = 0;
        first_index < first_size;
        ++first_index
    ) {
        Segment<T> first_edge{
            first[first_index],
            first[(first_index + 1) % first_size]
        };
        for (
            std::size_t second_index = 0;
            second_index < second_size;
            ++second_index
        ) {
            Segment<T> second_edge{
                second[second_index],
                second[(second_index + 1) % second_size]
            };
            result = std::min(result, distance(first_edge, second_edge));
        }
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_POLYGON_HPP
