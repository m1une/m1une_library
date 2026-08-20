#ifndef M1UNE_GEOMETRY_POLYGON_HPP
#define M1UNE_GEOMETRY_POLYGON_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <optional>
#include <type_traits>
#include <vector>

#include "circle.hpp"

namespace m1une {
namespace geometry {

enum class PointInPolygon {
    Outside = 0,
    Boundary = 1,
    Inside = 2,
};

template <Coordinate T>
struct Polygon {
    std::vector<Point<T>> vertices;
    bool filled = true;
};

template <Coordinate T>
constexpr Point<long double> centroid(
    const std::array<Point<T>, 3>& triangle
) {
    return Point<long double>(
        (
            static_cast<long double>(triangle[0].x) +
            static_cast<long double>(triangle[1].x) +
            static_cast<long double>(triangle[2].x)
        ) / 3,
        (
            static_cast<long double>(triangle[0].y) +
            static_cast<long double>(triangle[1].y) +
            static_cast<long double>(triangle[2].y)
        ) / 3
    );
}

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
std::optional<Point<long double>> centroid(
    const std::vector<Point<T>>& polygon,
    long double eps = 1e-12L
) {
    return polygon_centroid(polygon, eps);
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

template <Coordinate T, Coordinate P>
PointInPolygon point_in_polygon(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    assert(polygon.vertices.size() >= 3);
    if constexpr (std::is_same_v<T, P>) {
        return point_in_polygon(polygon.vertices, point, eps);
    } else {
        std::vector<Point<long double>> vertices;
        vertices.reserve(polygon.vertices.size());
        for (const Point<T>& vertex : polygon.vertices) {
            vertices.emplace_back(vertex);
        }
        return point_in_polygon(vertices, Point<long double>(point), eps);
    }
}

template <Coordinate T, Coordinate P>
bool contains(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    const PointInPolygon relation = point_in_polygon(polygon, point, eps);
    return polygon.filled
        ? relation != PointInPolygon::Outside
        : relation == PointInPolygon::Boundary;
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
        const LinearIntersection intersection =
            linear_intersection(ray, edge, eps);
        if (intersection.kind == LinearIntersectionKind::Point) {
            polygon_detail::push_unique(result, intersection.first, eps);
        } else if (intersection.kind == LinearIntersectionKind::Segment) {
            polygon_detail::push_unique(result, intersection.first, eps);
            polygon_detail::push_unique(result, intersection.second, eps);
        } else {
            assert(intersection.kind == LinearIntersectionKind::Empty);
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

template <Coordinate T>
wide_type<T> polygon_area2(const Polygon<T>& polygon) {
    return polygon_area2(polygon.vertices);
}

template <Coordinate T>
long double polygon_area(const Polygon<T>& polygon) {
    return polygon_area(polygon.vertices);
}

template <Coordinate T>
std::optional<Point<long double>> polygon_centroid(
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return polygon_centroid(polygon.vertices, eps);
}

template <Coordinate T>
std::optional<Point<long double>> centroid(
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return polygon_centroid(polygon.vertices, eps);
}

namespace polygon_detail {

template <Coordinate T>
Segment<long double> edge(const Polygon<T>& polygon, std::size_t index) {
    return Segment<long double>{
        Point<long double>(polygon.vertices[index]),
        Point<long double>(
            polygon.vertices[(index + 1) % polygon.vertices.size()]
        )
    };
}

template <Coordinate T>
ClosestPoints closest_boundary_point(
    const Polygon<T>& polygon,
    const Point<long double>& point
) {
    assert(polygon.vertices.size() >= 3);
    ClosestPoints result = closest_points(edge(polygon, 0), point);
    for (std::size_t index = 1; index < polygon.vertices.size(); ++index) {
        closest_points_detail::consider(
            result,
            closest_points(edge(polygon, index), point)
        );
    }
    return result;
}

template <Coordinate T, class Object>
ClosestPoints closest_boundary_object(
    const Polygon<T>& polygon,
    const Object& object
) {
    assert(polygon.vertices.size() >= 3);
    ClosestPoints result = closest_points(edge(polygon, 0), object);
    for (std::size_t index = 1; index < polygon.vertices.size(); ++index) {
        closest_points_detail::consider(
            result,
            closest_points(edge(polygon, index), object)
        );
    }
    return result;
}

template <Coordinate A, Coordinate B>
ClosestPoints closest_boundaries(
    const Polygon<A>& first,
    const Polygon<B>& second
) {
    assert(first.vertices.size() >= 3);
    assert(second.vertices.size() >= 3);
    ClosestPoints result = closest_points(edge(first, 0), edge(second, 0));
    for (
        std::size_t first_index = 0;
        first_index < first.vertices.size();
        ++first_index
    ) {
        for (
            std::size_t second_index = 0;
            second_index < second.vertices.size();
            ++second_index
        ) {
            closest_points_detail::consider(
                result,
                closest_points(
                    edge(first, first_index),
                    edge(second, second_index)
                )
            );
        }
    }
    return result;
}

}  // namespace polygon_detail

template <Coordinate T, Coordinate P>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    assert(polygon.vertices.size() >= 3);
    const Point<long double> converted(point);
    if (polygon.filled && contains(polygon, point, eps)) {
        return ClosestPoints{converted, converted};
    }
    return polygon_detail::closest_boundary_point(polygon, converted);
}

template <Coordinate P, Coordinate T>
ClosestPoints closest_points(
    const Point<P>& point,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(polygon, point, eps)
    );
}

template <Coordinate T, Coordinate S>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Segment<S>& segment,
    long double eps = 1e-12L
) {
    assert(polygon.vertices.size() >= 3);
    const Segment<long double> converted{
        Point<long double>(segment.a),
        Point<long double>(segment.b)
    };
    if (polygon.filled) {
        if (contains(polygon, segment.a, eps)) {
            const Point<long double> point(segment.a);
            return ClosestPoints{point, point};
        }
        if (contains(polygon, segment.b, eps)) {
            const Point<long double> point(segment.b);
            return ClosestPoints{point, point};
        }
    }
    return polygon_detail::closest_boundary_object(polygon, converted);
}

template <Coordinate S, Coordinate T>
ClosestPoints closest_points(
    const Segment<S>& segment,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(polygon, segment, eps)
    );
}

template <Coordinate T, Coordinate R>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Ray<R>& ray,
    long double eps = 1e-12L
) {
    assert(polygon.vertices.size() >= 3);
    const Ray<long double> converted{
        Point<long double>(ray.origin),
        Point<long double>(ray.through)
    };
    if (polygon.filled && contains(polygon, ray.origin, eps)) {
        const Point<long double> point(ray.origin);
        return ClosestPoints{point, point};
    }
    return polygon_detail::closest_boundary_object(polygon, converted);
}

template <Coordinate R, Coordinate T>
ClosestPoints closest_points(
    const Ray<R>& ray,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(polygon, ray, eps)
    );
}

template <Coordinate A, Coordinate B>
ClosestPoints closest_points(
    const Polygon<A>& first,
    const Polygon<B>& second,
    long double eps = 1e-12L
) {
    assert(first.vertices.size() >= 3);
    assert(second.vertices.size() >= 3);
    ClosestPoints result = polygon_detail::closest_boundaries(first, second);
    if (geometry::distance(result.first, result.second) <= eps) return result;

    if (first.filled) {
        for (const Point<B>& vertex : second.vertices) {
            if (contains(first, vertex, eps)) {
                const Point<long double> point(vertex);
                return ClosestPoints{point, point};
            }
        }
    }
    if (second.filled) {
        for (const Point<A>& vertex : first.vertices) {
            if (contains(second, vertex, eps)) {
                const Point<long double> point(vertex);
                return ClosestPoints{point, point};
            }
        }
    }
    return result;
}

template <Coordinate C, Coordinate T>
ClosestPoints closest_points(
    const Circle<C>& circle,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    assert(polygon.vertices.size() >= 3);
    ClosestPoints result = closest_points(
        circle,
        polygon_detail::edge(polygon, 0),
        eps
    );
    for (std::size_t index = 1; index < polygon.vertices.size(); ++index) {
        closest_points_detail::consider(
            result,
            closest_points(circle, polygon_detail::edge(polygon, index), eps)
        );
    }
    if (geometry::distance(result.first, result.second) <= eps) return result;

    if (polygon.filled) {
        Point<long double> member(circle.center);
        if (!circle.filled) {
            member = circle_detail::point_toward(circle, member);
        }
        if (contains(polygon, member, eps)) {
            return ClosestPoints{member, member};
        }
    }
    return result;
}

template <Coordinate T, Coordinate C>
ClosestPoints closest_points(
    const Polygon<T>& polygon,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(circle, polygon, eps)
    );
}

template <Coordinate T, Coordinate P>
bool intersects(
    const Polygon<T>& polygon,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    return contains(polygon, point, eps);
}

template <Coordinate P, Coordinate T>
bool intersects(
    const Point<P>& point,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return intersects(polygon, point, eps);
}

template <Coordinate T, Coordinate S>
bool intersects(
    const Polygon<T>& polygon,
    const Segment<S>& segment,
    long double eps = 1e-12L
) {
    const ClosestPoints result = closest_points(polygon, segment, eps);
    return geometry::distance(result.first, result.second) <= eps;
}

template <Coordinate S, Coordinate T>
bool intersects(
    const Segment<S>& segment,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return intersects(polygon, segment, eps);
}

template <Coordinate T, Coordinate R>
bool intersects(
    const Polygon<T>& polygon,
    const Ray<R>& ray,
    long double eps = 1e-12L
) {
    const ClosestPoints result = closest_points(polygon, ray, eps);
    return geometry::distance(result.first, result.second) <= eps;
}

template <Coordinate R, Coordinate T>
bool intersects(
    const Ray<R>& ray,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return intersects(polygon, ray, eps);
}

template <Coordinate A, Coordinate B>
bool intersects(
    const Polygon<A>& first,
    const Polygon<B>& second,
    long double eps = 1e-12L
) {
    const ClosestPoints result = closest_points(first, second, eps);
    return geometry::distance(result.first, result.second) <= eps;
}

template <Coordinate C, Coordinate T>
bool intersects(
    const Circle<C>& circle,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    const ClosestPoints result = closest_points(circle, polygon, eps);
    return geometry::distance(result.first, result.second) <= eps;
}

template <Coordinate T, Coordinate C>
bool intersects(
    const Polygon<T>& polygon,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return intersects(circle, polygon, eps);
}

template <Coordinate A, Coordinate B>
long double distance(
    const Polygon<A>& first,
    const Polygon<B>& second
) {
    const ClosestPoints result = closest_points(first, second);
    return geometry::distance(result.first, result.second);
}

template <Coordinate C, Coordinate T>
long double distance(
    const Circle<C>& circle,
    const Polygon<T>& polygon
) {
    const ClosestPoints result = closest_points(circle, polygon);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T, Coordinate C>
long double distance(
    const Polygon<T>& polygon,
    const Circle<C>& circle
) {
    return distance(circle, polygon);
}

template <Coordinate C, Coordinate T>
long double circle_polygon_intersection_area(
    const Circle<C>& circle,
    const Polygon<T>& polygon,
    long double eps = 1e-12L
) {
    return circle_polygon_intersection_area(circle, polygon.vertices, eps);
}

template <Coordinate T, Coordinate P>
long double distance(
    const Polygon<T>& polygon,
    const Point<P>& point
) {
    const ClosestPoints result = closest_points(polygon, point);
    return geometry::distance(result.first, result.second);
}

template <Coordinate P, Coordinate T>
long double distance(
    const Point<P>& point,
    const Polygon<T>& polygon
) {
    return distance(polygon, point);
}

template <Coordinate T, Coordinate S>
long double distance(
    const Polygon<T>& polygon,
    const Segment<S>& segment
) {
    const ClosestPoints result = closest_points(polygon, segment);
    return geometry::distance(result.first, result.second);
}

template <Coordinate S, Coordinate T>
long double distance(
    const Segment<S>& segment,
    const Polygon<T>& polygon
) {
    return distance(polygon, segment);
}

template <Coordinate T, Coordinate R>
long double distance(
    const Polygon<T>& polygon,
    const Ray<R>& ray
) {
    const ClosestPoints result = closest_points(polygon, ray);
    return geometry::distance(result.first, result.second);
}

template <Coordinate R, Coordinate T>
long double distance(
    const Ray<R>& ray,
    const Polygon<T>& polygon
) {
    return distance(polygon, ray);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_POLYGON_HPP
