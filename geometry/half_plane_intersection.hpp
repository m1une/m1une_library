#ifndef M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP
#define M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <limits>
#include <numbers>
#include <optional>
#include <random>
#include <utility>
#include <vector>

#include "line.hpp"

namespace m1une {
namespace geometry {

enum class HalfPlaneIntersectionStatus {
    Empty,
    Unbounded,
    Degenerate,
    Bounded,
};

struct HalfPlaneIntersectionResult {
    HalfPlaneIntersectionStatus status;
    std::vector<Point<long double>> polygon;
};

namespace half_plane_intersection_detail {

struct HalfPlane {
    Point<long double> point;
    Point<long double> direction;
};

inline int direction_half(const Point<long double>& direction) {
    return direction.y > 0 || (direction.y == 0 && direction.x >= 0) ? 0 : 1;
}

inline bool direction_less(const HalfPlane& first, const HalfPlane& second) {
    int first_half = direction_half(first.direction);
    int second_half = direction_half(second.direction);
    if (first_half != second_half) return first_half < second_half;
    return cross(first.direction, second.direction) > 0;
}

inline bool parallel(
    const HalfPlane& first,
    const HalfPlane& second,
    long double eps
) {
    return std::fabs(cross(first.direction, second.direction)) <= eps;
}

inline bool same_direction(
    const HalfPlane& first,
    const HalfPlane& second,
    long double eps
) {
    return parallel(first, second, eps) &&
           dot(first.direction, second.direction) > 0;
}

inline bool outside(
    const HalfPlane& half_plane,
    const Point<long double>& point,
    long double eps
) {
    return cross(half_plane.direction, point - half_plane.point) < -eps;
}

inline bool more_restrictive(
    const HalfPlane& candidate,
    const HalfPlane& current,
    long double eps
) {
    return cross(
        current.direction,
        candidate.point - current.point
    ) > eps;
}

inline std::optional<Point<long double>> intersection(
    const HalfPlane& first,
    const HalfPlane& second,
    long double eps
) {
    long double denominator = cross(first.direction, second.direction);
    if (std::fabs(denominator) <= eps) return std::nullopt;
    long double ratio = cross(
        second.point - first.point,
        second.direction
    ) / denominator;
    return first.point + first.direction * ratio;
}

inline void merge_same_direction(
    std::vector<HalfPlane>& half_planes,
    const HalfPlane& half_plane,
    long double eps
) {
    if (
        half_planes.empty() ||
        !same_direction(half_planes.back(), half_plane, eps)
    ) {
        half_planes.push_back(half_plane);
        return;
    }
    if (more_restrictive(half_plane, half_planes.back(), eps)) {
        half_planes.back() = half_plane;
    }
}

inline void merge_cyclic_ends(
    std::vector<HalfPlane>& half_planes,
    long double eps
) {
    if (
        half_planes.size() < 2 ||
        !same_direction(half_planes.front(), half_planes.back(), eps)
    ) {
        return;
    }
    if (more_restrictive(half_planes.back(), half_planes.front(), eps)) {
        half_planes.front() = half_planes.back();
    }
    half_planes.pop_back();
}

inline bool has_feasible_point(
    std::vector<HalfPlane> half_planes,
    long double eps
) {
    std::mt19937_64 generator(0x6a09e667f3bcc909ULL);
    std::shuffle(half_planes.begin(), half_planes.end(), generator);

    Point<long double> feasible(0, 0);
    for (std::size_t index = 0; index < half_planes.size(); ++index) {
        const HalfPlane& current = half_planes[index];
        if (!outside(current, feasible, eps)) continue;

        Point<long double> normal(
            -current.direction.y,
            current.direction.x
        );
        Point<long double> base = normal * dot(normal, current.point);
        long double lower = -std::numeric_limits<long double>::infinity();
        long double upper = std::numeric_limits<long double>::infinity();
        for (std::size_t previous_index = 0;
             previous_index < index;
             ++previous_index) {
            const HalfPlane& previous = half_planes[previous_index];
            long double coefficient = cross(
                previous.direction,
                current.direction
            );
            long double constant = cross(
                previous.direction,
                base - previous.point
            );
            if (std::fabs(coefficient) <= eps) {
                if (constant < -eps) return false;
                continue;
            }

            long double bound = (-eps - constant) / coefficient;
            if (coefficient > 0) {
                lower = std::max(lower, bound);
            } else {
                upper = std::min(upper, bound);
            }
            if (lower > upper) return false;
        }

        long double parameter = 0;
        if (parameter < lower) parameter = lower;
        if (parameter > upper) parameter = upper;
        feasible = base + current.direction * parameter;
    }
    return true;
}

inline bool has_bounded_recession_cone(
    const std::vector<HalfPlane>& half_planes,
    long double eps
) {
    if (half_planes.empty()) return false;

    constexpr long double pi = std::numbers::pi_v<long double>;
    std::vector<long double> angles;
    angles.reserve(half_planes.size());
    for (const HalfPlane& half_plane : half_planes) {
        long double angle = std::atan2(
            half_plane.direction.y,
            half_plane.direction.x
        );
        if (angle < 0) angle += 2 * pi;
        angles.push_back(angle);
    }

    long double maximum_gap = angles.front() + 2 * pi - angles.back();
    for (std::size_t index = 1; index < angles.size(); ++index) {
        maximum_gap = std::max(
            maximum_gap,
            angles[index] - angles[index - 1]
        );
    }
    return maximum_gap < pi - eps;
}

}  // namespace half_plane_intersection_detail

// Each directed line keeps its closed left half-plane. Returns the vertices of
// a bounded intersection with positive area in counterclockwise order. Empty,
// unbounded, and bounded zero-area intersections have distinct statuses.
template <Coordinate T>
HalfPlaneIntersectionResult half_plane_intersection(
    const std::vector<Line<T>>& half_planes,
    long double eps = 1e-12L
) {
    using half_plane_intersection_detail::HalfPlane;
    namespace detail = half_plane_intersection_detail;

    assert(eps >= 0);
    std::vector<HalfPlane> sorted;
    sorted.reserve(half_planes.size());
    for (const Line<T>& line : half_planes) {
        assert(line.a != line.b);
        Point<long double> point(line.a);
        Point<long double> direction = Point<long double>(line.b) - point;
        long double length = norm(direction);
        direction = direction / length;
        sorted.push_back(HalfPlane{point, direction});
    }
    if (!detail::has_feasible_point(sorted, eps)) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Empty,
            {},
        };
    }
    std::sort(sorted.begin(), sorted.end(), detail::direction_less);
    if (!detail::has_bounded_recession_cone(sorted, eps)) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Unbounded,
            {},
        };
    }
    if (sorted.size() < 3) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Degenerate,
            {},
        };
    }

    std::vector<HalfPlane> unique;
    unique.reserve(sorted.size());
    for (const HalfPlane& half_plane : sorted) {
        detail::merge_same_direction(unique, half_plane, eps);
    }
    detail::merge_cyclic_ends(unique, eps);
    if (unique.size() < 3) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Degenerate,
            {},
        };
    }

    std::deque<HalfPlane> deque;
    for (const HalfPlane& half_plane : unique) {
        while (deque.size() >= 2) {
            auto point = detail::intersection(
                deque[deque.size() - 2],
                deque.back(),
                eps
            );
            if (!point.has_value()) {
                return HalfPlaneIntersectionResult{
                    HalfPlaneIntersectionStatus::Degenerate,
                    {},
                };
            }
            if (!detail::outside(half_plane, *point, eps)) break;
            deque.pop_back();
        }
        while (deque.size() >= 2) {
            auto point = detail::intersection(deque[0], deque[1], eps);
            if (!point.has_value()) {
                return HalfPlaneIntersectionResult{
                    HalfPlaneIntersectionStatus::Degenerate,
                    {},
                };
            }
            if (!detail::outside(half_plane, *point, eps)) break;
            deque.pop_front();
        }
        deque.push_back(half_plane);
    }

    while (deque.size() >= 3) {
        auto point = detail::intersection(
            deque[deque.size() - 2],
            deque.back(),
            eps
        );
        if (!point.has_value()) {
            return HalfPlaneIntersectionResult{
                HalfPlaneIntersectionStatus::Degenerate,
                {},
            };
        }
        if (!detail::outside(deque.front(), *point, eps)) break;
        deque.pop_back();
    }
    while (deque.size() >= 3) {
        auto point = detail::intersection(deque[0], deque[1], eps);
        if (!point.has_value()) {
            return HalfPlaneIntersectionResult{
                HalfPlaneIntersectionStatus::Degenerate,
                {},
            };
        }
        if (!detail::outside(deque.back(), *point, eps)) break;
        deque.pop_front();
    }
    if (deque.size() < 3) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Degenerate,
            {},
        };
    }

    std::vector<Point<long double>> polygon;
    polygon.reserve(deque.size());
    for (std::size_t index = 0; index < deque.size(); ++index) {
        auto point = detail::intersection(
            deque[index],
            deque[(index + 1) % deque.size()],
            eps
        );
        if (!point.has_value()) {
            return HalfPlaneIntersectionResult{
                HalfPlaneIntersectionStatus::Degenerate,
                {},
            };
        }
        if (
            polygon.empty() ||
            distance(polygon.back(), *point) > eps
        ) {
            polygon.push_back(*point);
        }
    }
    if (
        polygon.size() >= 2 &&
        distance(polygon.front(), polygon.back()) <= eps
    ) {
        polygon.pop_back();
    }
    if (polygon.size() < 3) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Degenerate,
            {},
        };
    }

    long double signed_area2 = 0;
    Point<long double> origin = polygon.front();
    for (std::size_t index = 1; index + 1 < polygon.size(); ++index) {
        signed_area2 += cross(
            polygon[index] - origin,
            polygon[index + 1] - origin
        );
    }
    if (signed_area2 <= eps) {
        return HalfPlaneIntersectionResult{
            HalfPlaneIntersectionStatus::Degenerate,
            {},
        };
    }

    auto first = std::min_element(polygon.begin(), polygon.end());
    std::rotate(polygon.begin(), first, polygon.end());
    return HalfPlaneIntersectionResult{
        HalfPlaneIntersectionStatus::Bounded,
        std::move(polygon),
    };
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_HALF_PLANE_INTERSECTION_HPP
