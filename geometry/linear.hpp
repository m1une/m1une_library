#ifndef M1UNE_GEOMETRY_LINEAR_HPP
#define M1UNE_GEOMETRY_LINEAR_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>

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

template <Coordinate T>
struct Ray {
    Point<T> origin;
    Point<T> through;
};

enum class LinearIntersectionKind {
    Empty,
    Point,
    Segment,
    Ray,
    Line,
};

struct LinearIntersection {
    LinearIntersectionKind kind;
    Point<long double> first;
    Point<long double> second;
};

namespace linear_intersection_detail {

inline LinearIntersection make_empty() {
    const Point<long double> zero;
    return LinearIntersection{
        LinearIntersectionKind::Empty,
        zero,
        zero,
    };
}

template <Coordinate T>
LinearIntersection make_point(const Point<T>& point) {
    const Point<long double> converted(point);
    return LinearIntersection{
        LinearIntersectionKind::Point,
        converted,
        converted,
    };
}

template <Coordinate T>
LinearIntersection make_object(
    LinearIntersectionKind kind,
    const Point<T>& first,
    const Point<T>& second
) {
    return LinearIntersection{
        kind,
        Point<long double>(first),
        Point<long double>(second),
    };
}

template <Coordinate T>
Point<long double> crossing_point(
    const Line<T>& first,
    const Line<T>& second
) {
    using W = wide_type<T>;
    const W first_x = W(first.b.x) - W(first.a.x);
    const W first_y = W(first.b.y) - W(first.a.y);
    const W second_x = W(second.b.x) - W(second.a.x);
    const W second_y = W(second.b.y) - W(second.a.y);
    const W offset_x = W(second.a.x) - W(first.a.x);
    const W offset_y = W(second.a.y) - W(first.a.y);
    const W denominator =
        first_x * second_y - first_y * second_x;
    assert(denominator != W(0));
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

}  // namespace linear_intersection_detail

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
LinearIntersection linear_intersection(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    assert(first.a != first.b);
    assert(second.a != second.b);
    if (parallel(first, second, eps)) {
        if (on_line(first, second.a, eps)) {
            return linear_intersection_detail::make_object(
                LinearIntersectionKind::Line,
                first.a,
                first.b
            );
        }
        return linear_intersection_detail::make_empty();
    }
    return linear_intersection_detail::make_point(
        linear_intersection_detail::crossing_point(first, second)
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(line.a != line.b);
    if (!intersects(line, segment, eps)) {
        return linear_intersection_detail::make_empty();
    }
    if (segment.a == segment.b) {
        return linear_intersection_detail::make_point(segment.a);
    }

    const int first_side =
        orientation(line.a, line.b, segment.a, eps);
    const int second_side =
        orientation(line.a, line.b, segment.b, eps);
    if (first_side == 0 && second_side == 0) {
        return linear_intersection_detail::make_object(
            LinearIntersectionKind::Segment,
            segment.a,
            segment.b
        );
    }
    if (first_side == 0) {
        return linear_intersection_detail::make_point(segment.a);
    }
    if (second_side == 0) {
        return linear_intersection_detail::make_point(segment.b);
    }

    return linear_intersection_detail::make_point(
        linear_intersection_detail::crossing_point(
            line,
            Line<T>{segment.a, segment.b}
        )
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return linear_intersection(line, segment, eps);
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    if (!intersects(first, second, eps)) {
        return linear_intersection_detail::make_empty();
    }
    if (first.a == first.b) {
        return linear_intersection_detail::make_point(first.a);
    }
    if (second.a == second.b) {
        return linear_intersection_detail::make_point(second.a);
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
        if (first_a_side == 0 && on_segment(second, first.a, eps)) {
            return linear_intersection_detail::make_point(first.a);
        }
        if (first_b_side == 0 && on_segment(second, first.b, eps)) {
            return linear_intersection_detail::make_point(first.b);
        }
        if (second_a_side == 0 && on_segment(first, second.a, eps)) {
            return linear_intersection_detail::make_point(second.a);
        }
        if (second_b_side == 0 && on_segment(first, second.b, eps)) {
            return linear_intersection_detail::make_point(second.b);
        }
        return linear_intersection_detail::make_point(
            linear_intersection_detail::crossing_point(
                Line<T>{first.a, first.b},
                Line<T>{second.a, second.b}
            )
        );
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

    if (same_point(common[start_index], common[finish_index])) {
        return linear_intersection_detail::make_point(common[start_index]);
    }
    return linear_intersection_detail::make_object(
        LinearIntersectionKind::Segment,
        common[start_index],
        common[finish_index]
    );
}

namespace ray_detail {

template <Coordinate T>
struct Parameters {
    wide_type<T> denominator;
    wide_type<T> denominator_scale;
    wide_type<T> first_numerator;
    wide_type<T> second_numerator;
};

template <Coordinate T>
Parameters<T> parameters(
    const Point<T>& first_origin,
    const Point<T>& first_through,
    const Point<T>& second_origin,
    const Point<T>& second_through
) {
    using W = wide_type<T>;
    W first_x = W(first_through.x) - W(first_origin.x);
    W first_y = W(first_through.y) - W(first_origin.y);
    W second_x = W(second_through.x) - W(second_origin.x);
    W second_y = W(second_through.y) - W(second_origin.y);
    W offset_x = W(second_origin.x) - W(first_origin.x);
    W offset_y = W(second_origin.y) - W(first_origin.y);
    return Parameters<T>{
        first_x * second_y - first_y * second_x,
        predicate_detail::determinant_scale<std::integral<T>>(
            first_x,
            first_y,
            second_x,
            second_y
        ),
        offset_x * second_y - offset_y * second_x,
        offset_x * first_y - offset_y * first_x
    };
}

template <Coordinate T>
int denominator_sign(const Parameters<T>& values, long double eps) {
    return predicate_detail::scaled_sign<std::integral<T>>(
        values.denominator,
        values.denominator_scale,
        eps
    );
}

template <Coordinate T>
bool ratio_nonnegative(
    wide_type<T> numerator,
    wide_type<T> denominator,
    long double eps
) {
    const int numerator_sign =
        predicate_detail::scaled_sign<std::integral<T>>(
            numerator,
            predicate_detail::absolute(denominator),
            eps
        );
    const int denominator_direction =
        (denominator > 0) - (denominator < 0);
    return
        numerator_sign == 0 ||
        numerator_sign == denominator_direction;
}

template <Coordinate T>
bool ratio_in_unit_interval(
    wide_type<T> numerator,
    wide_type<T> denominator,
    long double eps
) {
    const auto scale = predicate_detail::absolute(denominator);
    const int start_sign =
        predicate_detail::scaled_sign<std::integral<T>>(
            numerator,
            scale,
            eps
        );
    const int finish_sign =
        predicate_detail::scaled_sign<std::integral<T>>(
            numerator - denominator,
            scale,
            eps
        );
    if (denominator > 0) {
        return start_sign >= 0 && finish_sign <= 0;
    }
    return start_sign <= 0 && finish_sign >= 0;
}

template <Coordinate T>
Point<long double> point_at(
    const Ray<T>& ray,
    wide_type<T> numerator,
    wide_type<T> denominator
) {
    long double ratio =
        static_cast<long double>(numerator) /
        static_cast<long double>(denominator);
    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    return origin + direction * ratio;
}

}  // namespace ray_detail

template <Coordinate T>
bool on_ray(
    const Ray<T>& ray,
    const Point<T>& point,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (orientation(ray.origin, ray.through, point, eps) != 0) return false;
    using W = wide_type<T>;
    W direction_x = W(ray.through.x) - W(ray.origin.x);
    W direction_y = W(ray.through.y) - W(ray.origin.y);
    W offset_x = W(point.x) - W(ray.origin.x);
    W offset_y = W(point.y) - W(ray.origin.y);
    const W projection =
        direction_x * offset_x + direction_y * offset_y;
    const W length_squared =
        direction_x * direction_x + direction_y * direction_y;
    return predicate_detail::scaled_sign<std::integral<T>>(
        projection,
        length_squared,
        eps
    ) >= 0;
}

template <Coordinate T>
Point<long double> projection(const Ray<T>& ray, const Point<T>& point) {
    assert(ray.origin != ray.through);
    Point<long double> origin(ray.origin);
    Point<long double> direction =
        Point<long double>(ray.through) - origin;
    Point<long double> offset = Point<long double>(point) - origin;
    long double ratio = dot(offset, direction) / dot(direction, direction);
    if (ratio < 0) ratio = 0;
    return origin + direction * ratio;
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Point<T>& point) {
    return geometry::distance(projection(ray, point), Point<long double>(point));
}

template <Coordinate T>
long double distance(const Point<T>& point, const Ray<T>& ray) {
    return distance(ray, point);
}

template <Coordinate T>
Ray<long double> reflection(const Line<T>& line, const Ray<T>& ray) {
    assert(ray.origin != ray.through);
    return Ray<long double>{
        reflection(line, ray.origin),
        reflection(line, ray.through)
    };
}

template <Coordinate T>
Ray<long double> reflected_ray(
    const Ray<T>& incoming,
    const Point<T>& hit,
    const Line<T>& mirror,
    long double eps = 1e-12L
) {
    assert(incoming.origin != incoming.through);
    assert(on_line(mirror, hit, eps));
    Point<T> translated = hit + (incoming.through - incoming.origin);
    return Ray<long double>{
        Point<long double>(hit),
        reflection(mirror, translated)
    };
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(line.a != line.b);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        line.a,
        line.b
    );
    if (ray_detail::denominator_sign(values, eps) == 0) {
        return on_line(line, ray.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
        values.first_numerator,
        values.denominator,
        eps
    );
}

template <Coordinate T>
bool intersects(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, line, eps);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Line<T>& line) {
    return intersects(ray, line) ? 0 : distance(line, ray.origin);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Ray<T>& ray) {
    return distance(ray, line);
}

template <Coordinate T>
bool intersects(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (segment.a == segment.b) return on_ray(ray, segment.a, eps);

    ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        segment.a,
        segment.b
    );
    if (ray_detail::denominator_sign(values, eps) == 0) {
        if (orientation(ray.origin, ray.through, segment.a, eps) != 0) {
            return false;
        }
        return on_ray(ray, segment.a, eps) ||
               on_ray(ray, segment.b, eps) ||
               on_segment(segment, ray.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           ray_detail::ratio_in_unit_interval<T>(
               values.second_numerator,
               values.denominator,
               eps
           );
}

template <Coordinate T>
bool intersects(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return intersects(ray, segment, eps);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Segment<T>& segment) {
    if (intersects(ray, segment)) return 0;
    return std::min({
        distance(ray, segment.a),
        distance(ray, segment.b),
        distance(segment, ray.origin)
    });
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Ray<T>& ray) {
    return distance(ray, segment);
}

template <Coordinate T>
bool intersects(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    assert(first.origin != first.through);
    assert(second.origin != second.through);
    ray_detail::Parameters<T> values = ray_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (ray_detail::denominator_sign(values, eps) == 0) {
        if (orientation(first.origin, first.through, second.origin, eps) != 0) {
            return false;
        }
        return on_ray(first, second.origin, eps) ||
               on_ray(second, first.origin, eps);
    }
    return ray_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           ray_detail::ratio_nonnegative<T>(
               values.second_numerator,
               values.denominator,
               eps
           );
}

template <Coordinate T>
long double distance(const Ray<T>& first, const Ray<T>& second) {
    if (intersects(first, second)) return 0;
    return std::min(
        distance(first, second.origin),
        distance(second, first.origin)
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    assert(line.a != line.b);
    const ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        line.a,
        line.b
    );
    if (ray_detail::denominator_sign(values, eps) == 0) {
        if (on_line(line, ray.origin, eps)) {
            return linear_intersection_detail::make_object(
                LinearIntersectionKind::Ray,
                ray.origin,
                ray.through
            );
        }
        return linear_intersection_detail::make_empty();
    }
    if (
        !ray_detail::ratio_nonnegative<T>(
            values.first_numerator,
            values.denominator,
            eps
        )
    ) {
        return linear_intersection_detail::make_empty();
    }
    return linear_intersection_detail::make_point(
        ray_detail::point_at(
            ray,
            values.first_numerator,
            values.denominator
        )
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return linear_intersection(ray, line, eps);
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (segment.a == segment.b) {
        if (on_ray(ray, segment.a, eps)) {
            return linear_intersection_detail::make_point(segment.a);
        }
        return linear_intersection_detail::make_empty();
    }

    const ray_detail::Parameters<T> values = ray_detail::parameters(
        ray.origin,
        ray.through,
        segment.a,
        segment.b
    );
    if (ray_detail::denominator_sign(values, eps) != 0) {
        if (
            !ray_detail::ratio_nonnegative<T>(
                values.first_numerator,
                values.denominator,
                eps
            ) ||
            !ray_detail::ratio_in_unit_interval<T>(
                values.second_numerator,
                values.denominator,
                eps
            )
        ) {
            return linear_intersection_detail::make_empty();
        }
        return linear_intersection_detail::make_point(
            ray_detail::point_at(
                ray,
                values.first_numerator,
                values.denominator
            )
        );
    }
    if (orientation(ray.origin, ray.through, segment.a, eps) != 0) {
        return linear_intersection_detail::make_empty();
    }

    std::array<Point<T>, 3> candidates{
        ray.origin,
        segment.a,
        segment.b,
    };
    std::array<Point<T>, 3> common;
    int common_size = 0;
    long double object_scale = 0.0L;
    if constexpr (!std::integral<T>) {
        object_scale = std::max(
            geometry::distance(ray.origin, ray.through),
            geometry::distance(segment.a, segment.b)
        );
    }
    auto same_point = [eps, object_scale](
        const Point<T>& first,
        const Point<T>& second
    ) {
        if constexpr (std::integral<T>) {
            return first == second;
        } else {
            return
                geometry::distance(first, second) <= eps * object_scale;
        }
    };
    for (const Point<T>& candidate : candidates) {
        if (
            !on_ray(ray, candidate, eps) ||
            !on_segment(segment, candidate, eps)
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
    if (common_size == 0) {
        return linear_intersection_detail::make_empty();
    }

    using W = wide_type<T>;
    const W direction_x = W(ray.through.x) - W(ray.origin.x);
    const W direction_y = W(ray.through.y) - W(ray.origin.y);
    const W absolute_x = predicate_detail::absolute(direction_x);
    const W absolute_y = predicate_detail::absolute(direction_y);
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
    if (same_point(common[start_index], common[finish_index])) {
        return linear_intersection_detail::make_point(common[start_index]);
    }
    return linear_intersection_detail::make_object(
        LinearIntersectionKind::Segment,
        common[start_index],
        common[finish_index]
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return linear_intersection(ray, segment, eps);
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    assert(first.origin != first.through);
    assert(second.origin != second.through);
    const ray_detail::Parameters<T> values = ray_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (ray_detail::denominator_sign(values, eps) != 0) {
        if (
            !ray_detail::ratio_nonnegative<T>(
                values.first_numerator,
                values.denominator,
                eps
            ) ||
            !ray_detail::ratio_nonnegative<T>(
                values.second_numerator,
                values.denominator,
                eps
            )
        ) {
            return linear_intersection_detail::make_empty();
        }
        return linear_intersection_detail::make_point(
            ray_detail::point_at(
                first,
                values.first_numerator,
                values.denominator
            )
        );
    }
    if (
        orientation(
            first.origin,
            first.through,
            second.origin,
            eps
        ) != 0
    ) {
        return linear_intersection_detail::make_empty();
    }

    using W = wide_type<T>;
    const W first_x = W(first.through.x) - W(first.origin.x);
    const W first_y = W(first.through.y) - W(first.origin.y);
    const W second_x = W(second.through.x) - W(second.origin.x);
    const W second_y = W(second.through.y) - W(second.origin.y);
    const int direction_relation =
        predicate_detail::dot_sign<std::integral<T>>(
            first_x,
            first_y,
            second_x,
            second_y,
            eps
        );

    bool same_origin;
    if constexpr (std::integral<T>) {
        same_origin = first.origin == second.origin;
    } else {
        const long double object_scale = std::max(
            geometry::distance(first.origin, first.through),
            geometry::distance(second.origin, second.through)
        );
        same_origin =
            geometry::distance(first.origin, second.origin) <=
            eps * object_scale;
    }
    if (same_origin) {
        if (direction_relation < 0) {
            return linear_intersection_detail::make_point(first.origin);
        }
        return linear_intersection_detail::make_object(
            LinearIntersectionKind::Ray,
            first.origin,
            first.through
        );
    }

    const bool first_contains_second =
        on_ray(first, second.origin, eps);
    const bool second_contains_first =
        on_ray(second, first.origin, eps);
    if (direction_relation >= 0) {
        if (first_contains_second) {
            return linear_intersection_detail::make_object(
                LinearIntersectionKind::Ray,
                second.origin,
                second.through
            );
        }
        if (second_contains_first) {
            return linear_intersection_detail::make_object(
                LinearIntersectionKind::Ray,
                first.origin,
                first.through
            );
        }
        return linear_intersection_detail::make_empty();
    }
    if (first_contains_second && second_contains_first) {
        return linear_intersection_detail::make_object(
            LinearIntersectionKind::Segment,
            first.origin,
            second.origin
        );
    }
    return linear_intersection_detail::make_empty();
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_LINEAR_HPP
