#ifndef M1UNE_GEOMETRY_CONVEX_POLYGON_HPP
#define M1UNE_GEOMETRY_CONVEX_POLYGON_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <deque>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

#include "convex_hull.hpp"
#include "half_plane_intersection.hpp"
#include "polygon.hpp"

namespace m1une {
namespace geometry {

namespace convex_polygon_detail {

inline std::vector<Point<long double>> clean_polygon(
    std::vector<Point<long double>> polygon,
    long double eps
) {
    if (polygon.empty()) return polygon;

    std::vector<Point<long double>> deduplicated;
    for (const Point<long double>& point : polygon) {
        if (
            deduplicated.empty() ||
            !polygon_detail::close(deduplicated.back(), point, eps)
        ) {
            deduplicated.push_back(point);
        }
    }
    if (
        deduplicated.size() >= 2 &&
        polygon_detail::close(
            deduplicated.front(),
            deduplicated.back(),
            eps
        )
    ) {
        deduplicated.pop_back();
    }
    if (deduplicated.size() <= 2) return deduplicated;
    std::vector<Point<long double>> cleaned;
    const std::size_t size = deduplicated.size();
    cleaned.reserve(size);
    for (std::size_t index = 0; index < size; ++index) {
        const Point<long double>& previous =
            deduplicated[(index + size - 1) % size];
        const Point<long double>& current = deduplicated[index];
        const Point<long double>& next =
            deduplicated[(index + 1) % size];
        if (
            orientation(previous, current, next, eps) != 0 ||
            dot(current - previous, next - current) < -eps
        ) {
            cleaned.push_back(current);
        }
    }
    return cleaned;
}

template <Coordinate T>
std::vector<Point<T>> without_closing_point(std::vector<Point<T>> polygon) {
    if (
        polygon.size() >= 2 &&
        polygon.front() == polygon.back()
    ) {
        polygon.pop_back();
    }
    return polygon;
}

}  // namespace convex_polygon_detail

template <Coordinate T>
bool is_convex_polygon(
    const std::vector<Point<T>>& polygon,
    bool strict = false,
    long double eps = 1e-12L
) {
    std::size_t size = polygon.size();
    if (size >= 2 && polygon.front() == polygon.back()) size--;
    if (size < 3) return false;

    int direction = 0;
    for (std::size_t index = 0; index < size; ++index) {
        const Point<T>& current = polygon[index];
        const Point<T>& next = polygon[(index + 1) % size];
        const Point<T>& after = polygon[(index + 2) % size];
        if (current == next) return false;
        const int turn = orientation(current, next, after, eps);
        if (turn == 0) {
            if (strict) return false;
            continue;
        }
        if (direction != 0 && direction != turn) return false;
        direction = turn;
    }
    return !strict || direction != 0;
}

template <Coordinate T>
std::vector<Point<T>> normalize_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon = convex_polygon_detail::without_closing_point(
        std::move(polygon)
    );
    polygon.erase(
        std::unique(polygon.begin(), polygon.end()),
        polygon.end()
    );
    if (
        polygon.size() >= 2 &&
        polygon.front() == polygon.back()
    ) {
        polygon.pop_back();
    }
    if (polygon.size() <= 1) return polygon;
    if (
        polygon.size() >= 3 &&
        sign<T>(polygon_area2(polygon), eps) < 0
    ) {
        std::reverse(polygon.begin(), polygon.end());
    }

    auto start = std::min_element(
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

template <Coordinate T>
PointInPolygon point_in_convex_polygon(
    const std::vector<Point<T>>& polygon,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    const std::size_t size = polygon.size();
    if (size == 0) return PointInPolygon::Outside;
    if (size == 1) {
        return distance(polygon[0], point) <= eps
            ? PointInPolygon::Boundary
            : PointInPolygon::Outside;
    }
    if (size == 2) {
        return on_segment(Segment<T>{polygon[0], polygon[1]}, point, eps)
            ? PointInPolygon::Boundary
            : PointInPolygon::Outside;
    }

    const int order = orientation(
        polygon[0],
        polygon[1],
        polygon[size - 1],
        eps
    );
    if (order == 0) return point_in_polygon(polygon, point, eps);
    auto vertex = [&](std::size_t index) -> const Point<T>& {
        if (order > 0 || index == 0) return polygon[index];
        return polygon[size - index];
    };

    const int first_side = orientation(vertex(0), vertex(1), point, eps);
    const int last_side =
        orientation(vertex(0), vertex(size - 1), point, eps);
    if (first_side < 0 || last_side > 0) {
        return PointInPolygon::Outside;
    }
    if (first_side == 0) {
        return on_segment(Segment<T>{vertex(0), vertex(1)}, point, eps)
            ? PointInPolygon::Boundary
            : PointInPolygon::Outside;
    }
    if (last_side == 0) {
        return on_segment(
            Segment<T>{vertex(0), vertex(size - 1)},
            point,
            eps
        )
            ? PointInPolygon::Boundary
            : PointInPolygon::Outside;
    }

    std::size_t left = 1;
    std::size_t right = size - 1;
    while (right - left >= 2) {
        const std::size_t middle = (left + right) / 2;
        if (orientation(vertex(0), vertex(middle), point, eps) >= 0) {
            left = middle;
        } else {
            right = middle;
        }
    }
    const int triangle_side =
        orientation(vertex(left), vertex(right), point, eps);
    if (triangle_side < 0) return PointInPolygon::Outside;
    if (triangle_side == 0) return PointInPolygon::Boundary;
    return PointInPolygon::Inside;
}

template <Coordinate T>
class ConvexPolygon {
   public:
    using Wide = wide_type<T>;

   private:
    std::vector<Point<T>> points;
    std::vector<Wide> area_prefix;
    long double epsilon;

    template <class Compare>
    int periodic_best(Compare better) const {
        const int size = int(points.size());
        int left = 0;
        int middle = size;
        int right = 2 * size;
        while (right - left > 2) {
            const int left_middle = (left + middle) / 2;
            const int right_middle = (middle + right + 1) / 2;
            if (better(left_middle % size, middle % size)) {
                right = middle;
                middle = left_middle;
            } else if (better(right_middle % size, middle % size)) {
                left = middle;
                middle = right_middle;
            } else {
                left = left_middle;
                right = right_middle;
            }
        }
        return middle % size;
    }

    int previous(int index) const {
        return index == 0 ? int(points.size()) - 1 : index - 1;
    }

    int next(int index) const {
        return index + 1 == int(points.size()) ? 0 : index + 1;
    }

   public:
    explicit ConvexPolygon(
        std::vector<Point<T>> polygon,
        long double eps = 1e-12L
    )
        : points(normalize_convex_polygon(std::move(polygon), eps)),
          epsilon(eps) {
        assert(
            points.size() <=
            static_cast<std::size_t>(
                std::numeric_limits<int>::max() / 2
            )
        );
        assert(
            points.size() < 3 ||
            is_convex_polygon(points, true, epsilon)
        );
        area_prefix.resize(2 * points.size() + 1, Wide(0));
        for (std::size_t index = 0; index < 2 * points.size(); ++index) {
            area_prefix[index + 1] =
                area_prefix[index] +
                cross(
                    points[index % points.size()],
                    points[(index + 1) % points.size()]
                );
        }
    }

    int size() const noexcept {
        return int(points.size());
    }

    bool empty() const noexcept {
        return points.empty();
    }

    const std::vector<Point<T>>& vertices() const noexcept {
        return points;
    }

    const Point<T>& operator[](int index) const {
        assert(0 <= index && index < size());
        return points[index];
    }

    Wide area2() const {
        if (points.empty()) return Wide(0);
        return area_prefix[points.size()];
    }

    Wide chain_area2(int first, int last) const {
        assert(0 <= first && first < size());
        assert(0 <= last && last < size());
        int extended_last = last;
        if (extended_last < first) extended_last += size();
        return
            area_prefix[extended_last] - area_prefix[first] +
            cross(points[last], points[first]);
    }

    PointInPolygon contains(const Point<T>& point) const {
        return point_in_convex_polygon(points, point, epsilon);
    }

    std::pair<Wide, int> min_dot(const Point<T>& direction) const {
        assert(!points.empty());
        const int index = periodic_best([&](int first, int second) {
            return dot(points[first], direction) <
                   dot(points[second], direction);
        });
        return std::pair<Wide, int>(dot(points[index], direction), index);
    }

    std::pair<Wide, int> max_dot(const Point<T>& direction) const {
        assert(!points.empty());
        const int index = periodic_best([&](int first, int second) {
            return dot(points[first], direction) >
                   dot(points[second], direction);
        });
        return std::pair<Wide, int>(dot(points[index], direction), index);
    }

    std::pair<int, int> tangent_vertices(const Point<T>& point) const {
        assert(points.size() >= 3);
        assert(contains(point) == PointInPolygon::Outside);
        int first = periodic_best([&](int left, int right) {
            return orientation(point, points[left], points[right], epsilon) < 0;
        });
        int second = periodic_best([&](int left, int right) {
            return orientation(point, points[left], points[right], epsilon) > 0;
        });
        if (
            orientation(
                point,
                points[first],
                points[previous(first)],
                epsilon
            ) == 0
        ) {
            first = previous(first);
        }
        if (
            orientation(
                point,
                points[second],
                points[next(second)],
                epsilon
            ) == 0
        ) {
            second = next(second);
        }
        return std::pair<int, int>(first, second);
    }
};

template <Coordinate T>
std::vector<std::array<Point<T>, 3>> triangulate_convex_polygon(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon = normalize_convex_polygon(std::move(polygon), eps);
    if (polygon.size() < 3) return {};

    std::vector<std::array<Point<T>, 3>> result;
    result.reserve(polygon.size() - 2);
    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {
        std::array<Point<T>, 3> triangle;
        triangle[0] = polygon[0];
        triangle[1] = polygon[index];
        triangle[2] = polygon[index + 1];
        result.push_back(std::move(triangle));
    }
    return result;
}

template <Coordinate T>
wide_type<T> convex_diameter2(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    polygon = normalize_convex_polygon(std::move(polygon), eps);
    const std::size_t size = polygon.size();
    if (size <= 1) return 0;
    if (size == 2) return distance2(polygon[1], polygon[0]);

    wide_type<T> result = 0;
    std::size_t opposite = 1;
    for (std::size_t index = 0; index < size; ++index) {
        const std::size_t next = (index + 1) % size;
        while (true) {
            const std::size_t candidate = (opposite + 1) % size;
            const auto current_area =
                cross(polygon[index], polygon[next], polygon[opposite]);
            const auto candidate_area =
                cross(polygon[index], polygon[next], polygon[candidate]);
            if (candidate_area <= current_area) break;
            opposite = candidate;
        }
        result = std::max(
            result,
            distance2(polygon[index], polygon[opposite])
        );
        result = std::max(
            result,
            distance2(polygon[next], polygon[opposite])
        );
    }
    return result;
}

template <Coordinate T>
std::vector<Point<long double>> convex_cut(
    const std::vector<Point<T>>& polygon,
    const Line<T>& boundary,
    long double eps = 1e-12L
) {
    assert(boundary.a != boundary.b);
    std::vector<Point<long double>> input;
    input.reserve(polygon.size());
    for (const Point<T>& point : polygon) input.emplace_back(point);
    if (input.empty()) return input;

    const Point<long double> line_start(boundary.a);
    const Point<long double> line_end(boundary.b);
    const Line<long double> line{line_start, line_end};
    std::vector<Point<long double>> result;
    Point<long double> previous = input.back();
    int previous_side = orientation(line_start, line_end, previous, eps);
    for (const Point<long double>& current : input) {
        const int current_side =
            orientation(line_start, line_end, current, eps);
        const bool previous_inside = previous_side >= 0;
        const bool current_inside = current_side >= 0;
        if (previous_inside != current_inside) {
            const Line<long double> crossing{previous, current};
            const std::optional<Point<long double>> intersection =
                line_intersection(line, crossing, eps);
            if (intersection.has_value()) result.push_back(*intersection);
        }
        if (current_inside) result.push_back(current);
        previous = current;
        previous_side = current_side;
    }
    return convex_polygon_detail::clean_polygon(std::move(result), eps);
}

template <Coordinate T>
std::vector<Point<T>> minkowski_sum(
    std::vector<Point<T>> first,
    std::vector<Point<T>> second,
    long double eps = 1e-12L
) {
    assert(!first.empty());
    assert(!second.empty());
    first = normalize_convex_polygon(std::move(first), eps);
    second = normalize_convex_polygon(std::move(second), eps);

    if (first.size() == 1 || second.size() == 1) {
        if (second.size() == 1) std::swap(first, second);
        for (Point<T>& point : second) {
            point += first[0];
        }
        return normalize_convex_polygon(std::move(second), eps);
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
                step =
                    first_edges[first_index++] +
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
    return normalize_convex_polygon(std::move(result), eps);
}

template <Coordinate T>
bool convex_polygons_intersect(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    assert(!first.empty());
    assert(!second.empty());
    std::vector<Point<T>> negated;
    negated.reserve(second.size());
    for (const Point<T>& point : second) negated.push_back(-point);
    const std::vector<Point<T>> difference =
        minkowski_sum(first, std::move(negated), eps);
    return
        point_in_convex_polygon(difference, Point<T>(), eps) !=
        PointInPolygon::Outside;
}

template <Coordinate T>
std::vector<Point<long double>> convex_polygon_intersection(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    using HalfPlane = half_plane_intersection_detail::HalfPlane;
    namespace detail = half_plane_intersection_detail;

    const std::vector<Point<T>> normalized_first =
        normalize_convex_polygon(first, eps);
    const std::vector<Point<T>> normalized_second =
        normalize_convex_polygon(second, eps);
    assert(normalized_first.size() >= 3);
    assert(normalized_second.size() >= 3);
    assert(is_convex_polygon(normalized_first, true, eps));
    assert(is_convex_polygon(normalized_second, true, eps));
    if (!convex_polygons_intersect(
            normalized_first,
            normalized_second,
            eps
        )) {
        return {};
    }

    auto boundaries = [](const std::vector<Point<T>>& polygon) {
        std::vector<HalfPlane> result;
        result.reserve(polygon.size());
        for (std::size_t index = 0; index < polygon.size(); ++index) {
            const Point<long double> point(polygon[index]);
            Point<long double> direction =
                Point<long double>(polygon[(index + 1) % polygon.size()]) -
                point;
            direction = direction / norm(direction);
            result.push_back(HalfPlane{point, direction});
        }
        return result;
    };
    const std::vector<HalfPlane> first_boundaries =
        boundaries(normalized_first);
    const std::vector<HalfPlane> second_boundaries =
        boundaries(normalized_second);

    std::vector<HalfPlane> merged;
    merged.reserve(first_boundaries.size() + second_boundaries.size());
    std::size_t first_index = 0;
    std::size_t second_index = 0;
    while (
        first_index < first_boundaries.size() ||
        second_index < second_boundaries.size()
    ) {
        const bool take_first =
            second_index == second_boundaries.size() ||
            (
                first_index < first_boundaries.size() &&
                detail::direction_less(
                    first_boundaries[first_index],
                    second_boundaries[second_index]
                )
            );
        if (take_first) {
            detail::merge_same_direction(
                merged,
                first_boundaries[first_index++],
                eps
            );
        } else {
            detail::merge_same_direction(
                merged,
                second_boundaries[second_index++],
                eps
            );
        }
    }
    detail::merge_cyclic_ends(merged, eps);

    std::deque<HalfPlane> active;
    for (const HalfPlane& half_plane : merged) {
        while (active.size() >= 2) {
            const std::optional<Point<long double>> point =
                detail::intersection(
                    active[active.size() - 2],
                    active.back(),
                    eps
                );
            if (
                !point.has_value() ||
                !detail::outside(half_plane, *point, eps)
            ) {
                break;
            }
            active.pop_back();
        }
        while (active.size() >= 2) {
            const std::optional<Point<long double>> point =
                detail::intersection(active[0], active[1], eps);
            if (
                !point.has_value() ||
                !detail::outside(half_plane, *point, eps)
            ) {
                break;
            }
            active.pop_front();
        }
        active.push_back(half_plane);
    }
    while (active.size() >= 3) {
        const std::optional<Point<long double>> point =
            detail::intersection(
                active[active.size() - 2],
                active.back(),
                eps
            );
        if (
            !point.has_value() ||
            !detail::outside(active.front(), *point, eps)
        ) {
            break;
        }
        active.pop_back();
    }
    while (active.size() >= 3) {
        const std::optional<Point<long double>> point =
            detail::intersection(active[0], active[1], eps);
        if (
            !point.has_value() ||
            !detail::outside(active.back(), *point, eps)
        ) {
            break;
        }
        active.pop_front();
    }

    std::vector<Point<long double>> result;
    result.reserve(active.size());
    for (std::size_t index = 0; index < active.size(); ++index) {
        const std::optional<Point<long double>> point =
            detail::intersection(
                active[index],
                active[(index + 1) % active.size()],
                eps
            );
        if (point.has_value()) result.push_back(*point);
    }
    return convex_polygon_detail::clean_polygon(std::move(result), eps);
}

template <Coordinate T>
long double convex_polygons_distance(
    const std::vector<Point<T>>& first,
    const std::vector<Point<T>>& second,
    long double eps = 1e-12L
) {
    assert(!first.empty());
    assert(!second.empty());
    std::vector<Point<T>> negated;
    negated.reserve(second.size());
    for (const Point<T>& point : second) negated.push_back(-point);
    const std::vector<Point<T>> difference =
        minkowski_sum(first, std::move(negated), eps);
    const Point<T> origin;
    if (
        point_in_convex_polygon(difference, origin, eps) !=
        PointInPolygon::Outside
    ) {
        return 0;
    }
    if (difference.size() == 1) return distance(difference[0], origin);

    long double result = std::numeric_limits<long double>::infinity();
    for (std::size_t index = 0; index < difference.size(); ++index) {
        if (difference.size() == 2 && index == 1) break;
        result = std::min(
            result,
            distance(
                Segment<T>{
                    difference[index],
                    difference[(index + 1) % difference.size()]
                },
                origin
            )
        );
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CONVEX_POLYGON_HPP
