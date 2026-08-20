#ifndef M1UNE_GEOMETRY_LINE_HPP
#define M1UNE_GEOMETRY_LINE_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <optional>

#include "point.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct Line {
    Point<T> a;
    Point<T> b;
};

template <Coordinate T>
struct Segment {
    Point<T> a;
    Point<T> b;
};

enum class SegmentIntersectionKind {
    Empty,
    Point,
    Overlap,
};

struct SegmentIntersection {
    SegmentIntersectionKind kind;
    Point<long double> first;
    Point<long double> second;
};

template <Coordinate T>
constexpr Point<long double> centroid(const Segment<T>& segment) {
    return Point<long double>(
        (
            static_cast<long double>(segment.a.x) +
            static_cast<long double>(segment.b.x)
        ) / 2,
        (
            static_cast<long double>(segment.a.y) +
            static_cast<long double>(segment.b.y)
        ) / 2
    );
}

template <Coordinate T>
bool on_line(
    const Line<T>& line,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    assert(line.a != line.b);
    return orientation(line.a, line.b, point, eps) == 0;
}

template <Coordinate T>
bool parallel(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {
    using W = wide_type<T>;
    W first_x = W(first.b.x) - W(first.a.x);
    W first_y = W(first.b.y) - W(first.a.y);
    W second_x = W(second.b.x) - W(second.a.x);
    W second_y = W(second.b.y) - W(second.a.y);
    return predicate_detail::determinant_sign<std::integral<T>>(
        first_x,
        first_y,
        second_x,
        second_y,
        eps
    ) == 0;
}

template <Coordinate T>
bool orthogonal(const Line<T>& first, const Line<T>& second, long double eps = 1e-12L) {
    using W = wide_type<T>;
    W first_x = W(first.b.x) - W(first.a.x);
    W first_y = W(first.b.y) - W(first.a.y);
    W second_x = W(second.b.x) - W(second.a.x);
    W second_y = W(second.b.y) - W(second.a.y);
    return predicate_detail::dot_sign<std::integral<T>>(
        first_x,
        first_y,
        second_x,
        second_y,
        eps
    ) == 0;
}

template <Coordinate T>
Point<long double> projection(const Line<T>& line, const Point<T>& point) {
    assert(line.a != line.b);
    Point<long double> a(line.a);
    Point<long double> direction(
        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)
    );
    Point<long double> offset(
        static_cast<long double>(point.x) - a.x,
        static_cast<long double>(point.y) - a.y
    );
    long double ratio = dot(offset, direction) / dot(direction, direction);
    return a + direction * ratio;
}

template <Coordinate T>
Point<long double> reflection(const Line<T>& line, const Point<T>& point) {
    Point<long double> projected = projection(line, point);
    return projected * 2.0L - Point<long double>(point);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Point<T>& point) {
    assert(line.a != line.b);
    Point<long double> direction(
        static_cast<long double>(line.b.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(line.b.y) - static_cast<long double>(line.a.y)
    );
    Point<long double> offset(
        static_cast<long double>(point.x) - static_cast<long double>(line.a.x),
        static_cast<long double>(point.y) - static_cast<long double>(line.a.y)
    );
    return std::fabs(cross(direction, offset)) / norm(direction);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Line<T>& line) {
    return distance(line, point);
}

template <Coordinate T>
bool intersects(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    return !parallel(first, second, eps) || on_line(first, second.a, eps);
}

template <Coordinate T>
long double distance(const Line<T>& first, const Line<T>& second) {
    return intersects(first, second) ? 0 : distance(first, second.a);
}

template <Coordinate T>
bool on_segment(
    const Segment<T>& segment,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    if (orientation(segment.a, segment.b, point, eps) != 0) return false;
    using W = wide_type<T>;
    const W direction_x = W(segment.b.x) - W(segment.a.x);
    const W direction_y = W(segment.b.y) - W(segment.a.y);
    if (direction_x == W(0) && direction_y == W(0)) {
        if constexpr (std::integral<T>) {
            return point == segment.a;
        } else {
            return
                predicate_detail::absolute(W(point.x) - W(segment.a.x)) <= eps &&
                predicate_detail::absolute(W(point.y) - W(segment.a.y)) <= eps;
        }
    }
    const W offset_x = W(point.x) - W(segment.a.x);
    const W offset_y = W(point.y) - W(segment.a.y);
    const W projection =
        offset_x * direction_x + offset_y * direction_y;
    const W length_squared =
        direction_x * direction_x + direction_y * direction_y;
    return
        predicate_detail::scaled_sign<std::integral<T>>(
            projection,
            length_squared,
            eps
        ) >= 0 &&
        predicate_detail::scaled_sign<std::integral<T>>(
            projection - length_squared,
            length_squared,
            eps
        ) <= 0;
}

template <Coordinate T>
bool intersects(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    int abc = orientation(first.a, first.b, second.a, eps);
    int abd = orientation(first.a, first.b, second.b, eps);
    int cda = orientation(second.a, second.b, first.a, eps);
    int cdb = orientation(second.a, second.b, first.b, eps);

    if (abc == 0 && on_segment(first, second.a, eps)) return true;
    if (abd == 0 && on_segment(first, second.b, eps)) return true;
    if (cda == 0 && on_segment(second, first.a, eps)) return true;
    if (cdb == 0 && on_segment(second, first.b, eps)) return true;
    return abc * abd < 0 && cda * cdb < 0;
}

template <Coordinate T>
bool intersects(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    int first_side = orientation(line.a, line.b, segment.a, eps);
    int second_side = orientation(line.a, line.b, segment.b, eps);
    return first_side == 0 || second_side == 0 || first_side != second_side;
}

template <Coordinate T>
bool intersects(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return intersects(line, segment, eps);
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Point<T>& point) {
    Point<long double> a(segment.a);
    Point<long double> b(segment.b);
    Point<long double> p(point);
    Point<long double> direction = b - a;
    long double length_squared = dot(direction, direction);
    if (length_squared == 0) return geometry::distance(segment.a, point);
    long double ratio = dot(p - a, direction) / length_squared;
    ratio = std::clamp(ratio, 0.0L, 1.0L);
    Point<long double> closest = a + direction * ratio;
    return geometry::distance(closest, p);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Segment<T>& segment) {
    return distance(segment, point);
}

template <Coordinate T>
long double distance(const Segment<T>& first, const Segment<T>& second) {
    if (intersects(first, second)) return 0;
    return std::min({
        distance(first, second.a),
        distance(first, second.b),
        distance(second, first.a),
        distance(second, first.b),
    });
}

template <Coordinate T>
long double distance(const Line<T>& line, const Segment<T>& segment) {
    if (intersects(line, segment)) return 0;
    return std::min(distance(line, segment.a), distance(line, segment.b));
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Line<T>& line) {
    return distance(line, segment);
}

template <Coordinate T>
std::optional<Point<long double>> line_intersection(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    assert(first.a != first.b);
    assert(second.a != second.b);
    using W = wide_type<T>;
    const W first_x = W(first.b.x) - W(first.a.x);
    const W first_y = W(first.b.y) - W(first.a.y);
    const W second_x = W(second.b.x) - W(second.a.x);
    const W second_y = W(second.b.y) - W(second.a.y);
    const W offset_x = W(second.a.x) - W(first.a.x);
    const W offset_y = W(second.a.y) - W(first.a.y);
    const W denominator =
        first_x * second_y - first_y * second_x;
    if (
        predicate_detail::determinant_sign<std::integral<T>>(
            first_x,
            first_y,
            second_x,
            second_y,
            eps
        ) == 0
    ) {
        return std::nullopt;
    }
    const W numerator = offset_x * second_y - offset_y * second_x;
    const long double ratio =
        static_cast<long double>(numerator) /
        static_cast<long double>(denominator);
    return Point<long double>(
        static_cast<long double>(first.a.x) +
            static_cast<long double>(first_x) * ratio,
        static_cast<long double>(first.a.y) +
            static_cast<long double>(first_y) * ratio
    );
}

template <Coordinate T>
SegmentIntersection segment_intersection(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    const Point<long double> zero;
    if (!intersects(first, second, eps)) {
        return SegmentIntersection{
            SegmentIntersectionKind::Empty,
            zero,
            zero,
        };
    }
    if (first.a == first.b) {
        const Point<long double> point(first.a);
        return SegmentIntersection{
            SegmentIntersectionKind::Point,
            point,
            point,
        };
    }
    if (second.a == second.b) {
        const Point<long double> point(second.a);
        return SegmentIntersection{
            SegmentIntersectionKind::Point,
            point,
            point,
        };
    }

    const int first_a_side =
        orientation(second.a, second.b, first.a, eps);
    const int first_b_side =
        orientation(second.a, second.b, first.b, eps);
    const int second_a_side =
        orientation(first.a, first.b, second.a, eps);
    const int second_b_side =
        orientation(first.a, first.b, second.b, eps);
    const bool collinear_intersection =
        first_a_side == 0 && first_b_side == 0 &&
        second_a_side == 0 && second_b_side == 0;

    if (!collinear_intersection) {
        const auto point = line_intersection(
            Line<T>{first.a, first.b},
            Line<T>{second.a, second.b},
            0.0L
        );
        assert(point.has_value());
        return SegmentIntersection{
            SegmentIntersectionKind::Point,
            *point,
            *point,
        };
    }

    std::array<Point<T>, 4> candidates{
        first.a,
        first.b,
        second.a,
        second.b,
    };
    std::array<Point<T>, 4> common;
    int common_size = 0;
    long double overlap_scale = 0.0L;
    if constexpr (!std::integral<T>) {
        overlap_scale = std::max(
            geometry::distance(first.a, first.b),
            geometry::distance(second.a, second.b)
        );
    }
    auto same_point = [eps, overlap_scale](
        const Point<T>& left,
        const Point<T>& right
    ) {
        if constexpr (std::integral<T>) {
            return left == right;
        } else {
            return geometry::distance(left, right) <= eps * overlap_scale;
        }
    };
    for (const Point<T>& candidate : candidates) {
        if (
            !on_segment(first, candidate, eps) ||
            !on_segment(second, candidate, eps)
        ) {
            continue;
        }
        bool duplicate = false;
        for (int index = 0; index < common_size; ++index) {
            if (same_point(common[index], candidate)) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) common[common_size++] = candidate;
    }
    assert(common_size >= 1);

    using W = wide_type<T>;
    const W direction_x = W(first.b.x) - W(first.a.x);
    const W direction_y = W(first.b.y) - W(first.a.y);
    const W absolute_x = direction_x >= 0 ? direction_x : -direction_x;
    const W absolute_y = direction_y >= 0 ? direction_y : -direction_y;
    const bool use_x = absolute_x >= absolute_y;
    auto parameter = [&](const Point<T>& point) {
        if (use_x) {
            return direction_x >= 0 ? W(point.x) : -W(point.x);
        }
        return direction_y >= 0 ? W(point.y) : -W(point.y);
    };
    int start_index = 0;
    int finish_index = 0;
    for (int index = 1; index < common_size; ++index) {
        if (parameter(common[index]) < parameter(common[start_index])) {
            start_index = index;
        }
        if (parameter(common[finish_index]) < parameter(common[index])) {
            finish_index = index;
        }
    }

    const Point<long double> start(common[start_index]);
    const Point<long double> finish(common[finish_index]);
    if (same_point(common[start_index], common[finish_index])) {
        return SegmentIntersection{
            SegmentIntersectionKind::Point,
            start,
            start,
        };
    }
    return SegmentIntersection{
        SegmentIntersectionKind::Overlap,
        start,
        finish,
    };
}

template <Coordinate T>
std::optional<Point<long double>> line_segment_intersection(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(line.a != line.b);
    if (segment.a == segment.b) {
        if (on_line(line, segment.a, eps)) {
            return Point<long double>(segment.a);
        }
        return std::nullopt;
    }
    if (!intersects(line, segment, eps)) return std::nullopt;
    Line<T> supporting_line{segment.a, segment.b};
    return line_intersection(line, supporting_line, eps);
}

template <Coordinate T>
std::optional<Point<long double>> line_segment_intersection(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return line_segment_intersection(line, segment, eps);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_LINE_HPP
