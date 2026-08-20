#ifndef M1UNE_GEOMETRY_LINEAR_HPP
#define M1UNE_GEOMETRY_LINEAR_HPP 1

#include <algorithm>
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

struct ClosestPoints {
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
bool intersects(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    return !parallel(first, second, eps) || on_line(first, second.a, eps);
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
Point<long double> projection(
    const Segment<T>& segment,
    const Point<T>& point
) {
    const Point<long double> first(segment.a);
    const Point<long double> direction =
        Point<long double>(segment.b) - first;
    const long double length_squared = dot(direction, direction);
    if (length_squared == 0) return first;
    const long double ratio = std::clamp(
        dot(Point<long double>(point) - first, direction) / length_squared,
        0.0L,
        1.0L
    );
    return first + direction * ratio;
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

namespace linear_parameter_detail {

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

}  // namespace linear_parameter_detail

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
    linear_parameter_detail::Parameters<T> values =
        linear_parameter_detail::parameters(
        ray.origin,
        ray.through,
        line.a,
        line.b
    );
    if (linear_parameter_detail::denominator_sign(values, eps) == 0) {
        return on_line(line, ray.origin, eps);
    }
    return linear_parameter_detail::ratio_nonnegative<T>(
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
bool intersects(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    assert(ray.origin != ray.through);
    if (segment.a == segment.b) return on_ray(ray, segment.a, eps);

    linear_parameter_detail::Parameters<T> values =
        linear_parameter_detail::parameters(
        ray.origin,
        ray.through,
        segment.a,
        segment.b
    );
    if (linear_parameter_detail::denominator_sign(values, eps) == 0) {
        if (orientation(ray.origin, ray.through, segment.a, eps) != 0) {
            return false;
        }
        return on_ray(ray, segment.a, eps) ||
               on_ray(ray, segment.b, eps) ||
               on_segment(segment, ray.origin, eps);
    }
    return linear_parameter_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           linear_parameter_detail::ratio_in_unit_interval<T>(
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
bool intersects(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    assert(first.origin != first.through);
    assert(second.origin != second.through);
    linear_parameter_detail::Parameters<T> values =
        linear_parameter_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (linear_parameter_detail::denominator_sign(values, eps) == 0) {
        if (orientation(first.origin, first.through, second.origin, eps) != 0) {
            return false;
        }
        return on_ray(first, second.origin, eps) ||
               on_ray(second, first.origin, eps);
    }
    return linear_parameter_detail::ratio_nonnegative<T>(
               values.first_numerator,
               values.denominator,
               eps
           ) &&
           linear_parameter_detail::ratio_nonnegative<T>(
               values.second_numerator,
               values.denominator,
               eps
           );
}

namespace linear_intersection_detail {

enum class Domain {
    Line,
    Segment,
    Ray,
};

template <Coordinate T>
struct ParametricObject {
    Point<T> origin;
    Point<T> through;
    Domain domain;
};

template <Coordinate T>
ParametricObject<T> parametric_object(const Line<T>& line) {
    assert(line.a != line.b);
    return ParametricObject<T>{line.a, line.b, Domain::Line};
}

template <Coordinate T>
ParametricObject<T> parametric_object(const Segment<T>& segment) {
    return ParametricObject<T>{segment.a, segment.b, Domain::Segment};
}

template <Coordinate T>
ParametricObject<T> parametric_object(const Ray<T>& ray) {
    assert(ray.origin != ray.through);
    return ParametricObject<T>{ray.origin, ray.through, Domain::Ray};
}

template <Coordinate T>
bool contains(
    const ParametricObject<T>& object,
    const Point<T>& point,
    long double eps
) {
    if (object.domain == Domain::Line) {
        return on_line(Line<T>{object.origin, object.through}, point, eps);
    }
    if (object.domain == Domain::Segment) {
        return on_segment(
            Segment<T>{object.origin, object.through},
            point,
            eps
        );
    }
    return on_ray(Ray<T>{object.origin, object.through}, point, eps);
}

template <Coordinate T>
bool accepts_parameter(
    Domain domain,
    wide_type<T> numerator,
    wide_type<T> denominator,
    long double eps
) {
    if (domain == Domain::Line) return true;
    if (domain == Domain::Ray) {
        return linear_parameter_detail::ratio_nonnegative<T>(
            numerator,
            denominator,
            eps
        );
    }
    return linear_parameter_detail::ratio_in_unit_interval<T>(
        numerator,
        denominator,
        eps
    );
}

template <Coordinate T>
Point<long double> point_at_ratio(
    const ParametricObject<T>& object,
    wide_type<T> numerator,
    wide_type<T> denominator
) {
    const long double ratio =
        static_cast<long double>(numerator) /
        static_cast<long double>(denominator);
    const Point<long double> origin(object.origin);
    const Point<long double> direction =
        Point<long double>(object.through) - origin;
    return origin + direction * ratio;
}

template <Coordinate T>
struct AxisProjection {
    bool use_x;
    bool negate;

    wide_type<T> operator()(const Point<T>& point) const {
        const wide_type<T> value = use_x
            ? wide_type<T>(point.x)
            : wide_type<T>(point.y);
        return negate ? -value : value;
    }
};

template <Coordinate T>
AxisProjection<T> axis_projection(const ParametricObject<T>& object) {
    using W = wide_type<T>;
    const W direction_x = W(object.through.x) - W(object.origin.x);
    const W direction_y = W(object.through.y) - W(object.origin.y);
    const bool use_x =
        predicate_detail::absolute(direction_x) >=
        predicate_detail::absolute(direction_y);
    const W component = use_x ? direction_x : direction_y;
    assert(component != W(0));
    return AxisProjection<T>{use_x, component < W(0)};
}

template <Coordinate T>
struct ParameterInterval {
    bool has_lower;
    bool has_upper;
    wide_type<T> lower;
    wide_type<T> upper;
};

template <Coordinate T>
ParameterInterval<T> parameter_interval(
    const ParametricObject<T>& object,
    const AxisProjection<T>& projection
) {
    using W = wide_type<T>;
    const W origin = projection(object.origin);
    const W through = projection(object.through);
    if (object.domain == Domain::Line) {
        return ParameterInterval<T>{false, false, W(0), W(0)};
    }
    if (object.domain == Domain::Segment) {
        return ParameterInterval<T>{
            true,
            true,
            std::min(origin, through),
            std::max(origin, through),
        };
    }
    if (origin < through) {
        return ParameterInterval<T>{true, false, origin, W(0)};
    }
    return ParameterInterval<T>{false, true, W(0), origin};
}

template <Coordinate T>
ParameterInterval<T> intersect_intervals(
    ParameterInterval<T> first,
    const ParameterInterval<T>& second
) {
    if (
        second.has_lower &&
        (!first.has_lower || first.lower < second.lower)
    ) {
        first.has_lower = true;
        first.lower = second.lower;
    }
    if (
        second.has_upper &&
        (!first.has_upper || second.upper < first.upper)
    ) {
        first.has_upper = true;
        first.upper = second.upper;
    }
    return first;
}

template <Coordinate T>
Point<long double> point_at_projection(
    const ParametricObject<T>& object,
    const AxisProjection<T>& projection,
    long double target
) {
    const long double origin =
        static_cast<long double>(projection(object.origin));
    const long double through =
        static_cast<long double>(projection(object.through));
    const long double ratio = (target - origin) / (through - origin);
    const Point<long double> point(object.origin);
    const Point<long double> direction =
        Point<long double>(object.through) - point;
    return point + direction * ratio;
}

template <Coordinate T>
LinearIntersection collinear_intersection(
    const ParametricObject<T>& first,
    const ParametricObject<T>& second,
    long double eps
) {
    using W = wide_type<T>;
    const AxisProjection<T> projection = axis_projection(first);
    const ParameterInterval<T> first_interval =
        parameter_interval(first, projection);
    const ParameterInterval<T> second_interval =
        parameter_interval(second, projection);
    const ParameterInterval<T> common =
        intersect_intervals(first_interval, second_interval);

    W scale = predicate_detail::absolute(
        projection(first.through) - projection(first.origin)
    );
    scale = std::max(
        scale,
        predicate_detail::absolute(
            projection(second.through) - projection(second.origin)
        )
    );

    if (common.has_lower && common.has_upper) {
        const int order = predicate_detail::scaled_sign<std::integral<T>>(
            common.lower - common.upper,
            scale,
            eps
        );
        if (order > 0) return make_empty();
        if (order == 0) {
            const long double coordinate =
                (
                    static_cast<long double>(common.lower) +
                    static_cast<long double>(common.upper)
                ) / 2.0L;
            return make_point(
                point_at_projection(first, projection, coordinate)
            );
        }
        return make_object(
            LinearIntersectionKind::Segment,
            point_at_projection(
                first,
                projection,
                static_cast<long double>(common.lower)
            ),
            point_at_projection(
                first,
                projection,
                static_cast<long double>(common.upper)
            )
        );
    }

    const Point<long double> direction =
        Point<long double>(first.through) -
        Point<long double>(first.origin);
    if (common.has_lower) {
        const Point<long double> origin = point_at_projection(
            first,
            projection,
            static_cast<long double>(common.lower)
        );
        return make_object(
            LinearIntersectionKind::Ray,
            origin,
            origin + direction
        );
    }
    if (common.has_upper) {
        const Point<long double> origin = point_at_projection(
            first,
            projection,
            static_cast<long double>(common.upper)
        );
        return make_object(
            LinearIntersectionKind::Ray,
            origin,
            origin - direction
        );
    }
    return make_object(
        LinearIntersectionKind::Line,
        first.origin,
        first.through
    );
}

template <Coordinate T>
LinearIntersection intersect(
    const ParametricObject<T>& first,
    const ParametricObject<T>& second,
    long double eps
) {
    const bool first_degenerate = first.origin == first.through;
    const bool second_degenerate = second.origin == second.through;
    if (first_degenerate) {
        assert(first.domain == Domain::Segment);
        if (contains(second, first.origin, eps)) {
            return make_point(first.origin);
        }
        return make_empty();
    }
    if (second_degenerate) {
        assert(second.domain == Domain::Segment);
        if (contains(first, second.origin, eps)) {
            return make_point(second.origin);
        }
        return make_empty();
    }

    const linear_parameter_detail::Parameters<T> values =
        linear_parameter_detail::parameters(
        first.origin,
        first.through,
        second.origin,
        second.through
    );
    if (linear_parameter_detail::denominator_sign(values, eps) != 0) {
        if (
            !accepts_parameter<T>(
                first.domain,
                values.first_numerator,
                values.denominator,
                eps
            ) ||
            !accepts_parameter<T>(
                second.domain,
                values.second_numerator,
                values.denominator,
                eps
            )
        ) {
            return make_empty();
        }
        return make_point(
            point_at_ratio(
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
        return make_empty();
    }
    return collinear_intersection(first, second, eps);
}

}  // namespace linear_intersection_detail

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(first),
        linear_intersection_detail::parametric_object(second),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(line),
        linear_intersection_detail::parametric_object(segment),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(segment),
        linear_intersection_detail::parametric_object(line),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(first),
        linear_intersection_detail::parametric_object(second),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(ray),
        linear_intersection_detail::parametric_object(line),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(line),
        linear_intersection_detail::parametric_object(ray),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(ray),
        linear_intersection_detail::parametric_object(segment),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(segment),
        linear_intersection_detail::parametric_object(ray),
        eps
    );
}

template <Coordinate T>
LinearIntersection linear_intersection(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    return linear_intersection_detail::intersect(
        linear_intersection_detail::parametric_object(first),
        linear_intersection_detail::parametric_object(second),
        eps
    );
}

namespace closest_points_detail {

inline ClosestPoints reversed(const ClosestPoints& result) {
    return ClosestPoints{result.second, result.first};
}

inline bool point_less(
    const Point<long double>& first,
    const Point<long double>& second
) {
    if (first.x != second.x) return first.x < second.x;
    return first.y < second.y;
}

inline ClosestPoints common_point(const LinearIntersection& intersection) {
    assert(intersection.kind != LinearIntersectionKind::Empty);
    Point<long double> point = intersection.first;
    if (intersection.kind == LinearIntersectionKind::Segment) {
        if (point_less(intersection.second, point)) {
            point = intersection.second;
        }
    } else if (intersection.kind == LinearIntersectionKind::Line) {
        const Line<long double> line{
            intersection.first,
            intersection.second
        };
        point = projection(line, Point<long double>(0, 0));
    }
    return ClosestPoints{point, point};
}

inline long double separation2(const ClosestPoints& result) {
    return distance2(result.first, result.second);
}

inline bool canonical_less(
    const ClosestPoints& first,
    const ClosestPoints& second
) {
    Point<long double> first_start = first.first;
    Point<long double> first_finish = first.second;
    if (point_less(first_finish, first_start)) {
        std::swap(first_start, first_finish);
    }
    Point<long double> second_start = second.first;
    Point<long double> second_finish = second.second;
    if (point_less(second_finish, second_start)) {
        std::swap(second_start, second_finish);
    }
    if (point_less(first_start, second_start)) return true;
    if (point_less(second_start, first_start)) return false;
    return point_less(first_finish, second_finish);
}

inline void consider(ClosestPoints& best, const ClosestPoints& candidate) {
    const long double best_distance = separation2(best);
    const long double candidate_distance = separation2(candidate);
    if (
        candidate_distance < best_distance ||
        (
            candidate_distance == best_distance &&
            canonical_less(candidate, best)
        )
    ) {
        best = candidate;
    }
}

}  // namespace closest_points_detail

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& first,
    const Point<T>& second
) {
    return ClosestPoints{
        Point<long double>(first),
        Point<long double>(second),
    };
}

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& line,
    const Point<T>& point
) {
    return ClosestPoints{
        projection(line, point),
        Point<long double>(point),
    };
}

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& point,
    const Line<T>& line
) {
    return closest_points_detail::reversed(closest_points(line, point));
}

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Point<T>& point
) {
    return ClosestPoints{
        projection(segment, point),
        Point<long double>(point),
    };
}

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& point,
    const Segment<T>& segment
) {
    return closest_points_detail::reversed(closest_points(segment, point));
}

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& ray,
    const Point<T>& point
) {
    return ClosestPoints{
        projection(ray, point),
        Point<long double>(point),
    };
}

template <Coordinate T>
ClosestPoints closest_points(
    const Point<T>& point,
    const Ray<T>& ray
) {
    return closest_points_detail::reversed(closest_points(ray, point));
}

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& first,
    const Line<T>& second,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(first, second, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    ClosestPoints result = closest_points(first, second.a);
    closest_points_detail::consider(
        result,
        closest_points(first.a, second)
    );
    return result;
}

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& line,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(line, segment, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    ClosestPoints result = closest_points(line, segment.a);
    closest_points_detail::consider(
        result,
        closest_points(line, segment.b)
    );
    return result;
}

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(line, segment, eps)
    );
}

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& first,
    const Segment<T>& second,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(first, second, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    ClosestPoints result = closest_points(first, second.a);
    closest_points_detail::consider(
        result,
        closest_points(first, second.b)
    );
    closest_points_detail::consider(
        result,
        closest_points(first.a, second)
    );
    closest_points_detail::consider(
        result,
        closest_points(first.b, second)
    );
    return result;
}

template <Coordinate T>
ClosestPoints closest_points(
    const Line<T>& line,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(line, ray, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    return closest_points(line, ray.origin);
}

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& ray,
    const Line<T>& line,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(closest_points(line, ray, eps));
}

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& ray,
    const Segment<T>& segment,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(ray, segment, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    ClosestPoints result = closest_points(ray, segment.a);
    closest_points_detail::consider(
        result,
        closest_points(ray, segment.b)
    );
    closest_points_detail::consider(
        result,
        closest_points(ray.origin, segment)
    );
    return result;
}

template <Coordinate T>
ClosestPoints closest_points(
    const Segment<T>& segment,
    const Ray<T>& ray,
    long double eps = 1e-12L
) {
    return closest_points_detail::reversed(
        closest_points(ray, segment, eps)
    );
}

template <Coordinate T>
ClosestPoints closest_points(
    const Ray<T>& first,
    const Ray<T>& second,
    long double eps = 1e-12L
) {
    const LinearIntersection intersection =
        linear_intersection(first, second, eps);
    if (intersection.kind != LinearIntersectionKind::Empty) {
        return closest_points_detail::common_point(intersection);
    }
    ClosestPoints result = closest_points(first, second.origin);
    closest_points_detail::consider(
        result,
        closest_points(first.origin, second)
    );
    return result;
}

template <Coordinate T>
long double distance(const Line<T>& line, const Point<T>& point) {
    const ClosestPoints result = closest_points(line, point);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Line<T>& line) {
    return distance(line, point);
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Point<T>& point) {
    const ClosestPoints result = closest_points(segment, point);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Segment<T>& segment) {
    return distance(segment, point);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Point<T>& point) {
    const ClosestPoints result = closest_points(ray, point);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Point<T>& point, const Ray<T>& ray) {
    return distance(ray, point);
}

template <Coordinate T>
long double distance(const Line<T>& first, const Line<T>& second) {
    const ClosestPoints result = closest_points(first, second);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Segment<T>& segment) {
    const ClosestPoints result = closest_points(line, segment);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Line<T>& line) {
    return distance(line, segment);
}

template <Coordinate T>
long double distance(const Segment<T>& first, const Segment<T>& second) {
    const ClosestPoints result = closest_points(first, second);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Line<T>& line, const Ray<T>& ray) {
    const ClosestPoints result = closest_points(line, ray);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Line<T>& line) {
    return distance(line, ray);
}

template <Coordinate T>
long double distance(const Ray<T>& ray, const Segment<T>& segment) {
    const ClosestPoints result = closest_points(ray, segment);
    return geometry::distance(result.first, result.second);
}

template <Coordinate T>
long double distance(const Segment<T>& segment, const Ray<T>& ray) {
    return distance(ray, segment);
}

template <Coordinate T>
long double distance(const Ray<T>& first, const Ray<T>& second) {
    const ClosestPoints result = closest_points(first, second);
    return geometry::distance(result.first, result.second);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_LINEAR_HPP
