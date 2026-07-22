#ifndef M1UNE_GEOMETRY_CIRCLE_HPP
#define M1UNE_GEOMETRY_CIRCLE_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <numbers>
#include <optional>
#include <type_traits>
#include <vector>

#include "ray.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct Circle {
    Point<T> center;
    T radius;
};

enum class PointInCircle {
    Outside = 0,
    Boundary = 1,
    Inside = 2,
};

enum class CircleRelation {
    Separate,
    ExternallyTangent,
    Intersecting,
    InternallyTangent,
    Contained,
    Coincident,
};

namespace circle_detail {

inline int compare(long double first, long double second, long double eps) {
    if (first < second - eps) return -1;
    if (first > second + eps) return 1;
    return 0;
}

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

inline bool same_line(
    const Line<long double>& first,
    const Line<long double>& second,
    long double eps
) {
    Point<long double> first_direction = first.b - first.a;
    Point<long double> second_direction = second.b - second.a;
    if (std::fabs(cross(first_direction, second_direction)) > eps) {
        return false;
    }
    return std::fabs(cross(first_direction, second.a - first.a)) <= eps;
}

inline Line<long double> tangent_line(
    const Point<long double>& contact,
    Point<long double> normal,
    long double eps
) {
    Point<long double> direction(-normal.y, normal.x);
    if (
        direction.x < -eps ||
        (std::fabs(direction.x) <= eps && direction.y < 0)
    ) {
        direction = -direction;
    }
    return Line<long double>{contact, contact + direction};
}

inline long double circular_segment_angle_term(
    long double angle,
    long double sine,
    long double cosine
) {
    if (angle >= 0.01L) return angle - sine * cosine;
    long double squared = angle * angle;
    return angle * squared * (
        2.0L / 3.0L +
        squared * (
            -2.0L / 15.0L +
            squared * (4.0L / 315.0L - squared * 2.0L / 2835.0L)
        )
    );
}

inline long double segment_disk_signed_area(
    const Point<long double>& first,
    const Point<long double>& second,
    long double radius,
    long double eps
) {
    Point<long double> direction = second - first;
    long double quadratic = dot(direction, direction);
    if (quadratic == 0.0L || radius == 0.0L) return 0.0L;

    std::vector<long double> cuts = {0.0L, 1.0L};
    long double linear = 2.0L * dot(first, direction);
    long double constant = dot(first, first) - radius * radius;
    long double discriminant =
        linear * linear - 4.0L * quadratic * constant;
    long double tolerance = eps * std::max({
        1.0L,
        std::fabs(linear * linear),
        std::fabs(4.0L * quadratic * constant)
    });
    if (discriminant >= -tolerance) {
        long double root = std::sqrt(std::max(0.0L, discriminant));
        long double first_ratio =
            (-linear - root) / (2.0L * quadratic);
        long double second_ratio =
            (-linear + root) / (2.0L * quadratic);
        if (eps < first_ratio && first_ratio < 1.0L - eps) {
            cuts.push_back(first_ratio);
        }
        if (eps < second_ratio && second_ratio < 1.0L - eps) {
            cuts.push_back(second_ratio);
        }
    }
    std::sort(cuts.begin(), cuts.end());
    cuts.erase(
        std::unique(
            cuts.begin(),
            cuts.end(),
            [eps](long double left, long double right) {
                return std::fabs(left - right) <= eps;
            }
        ),
        cuts.end()
    );

    long double result = 0.0L;
    for (std::size_t index = 1; index < cuts.size(); ++index) {
        long double left = cuts[index - 1];
        long double right = cuts[index];
        Point<long double> a = first + direction * left;
        Point<long double> b = first + direction * right;
        Point<long double> middle =
            first + direction * ((left + right) / 2.0L);
        if (norm(middle) <= radius + eps) {
            result += cross(a, b) / 2.0L;
        } else {
            result +=
                radius * radius * std::atan2(cross(a, b), dot(a, b)) /
                2.0L;
        }
    }
    return result;
}

}  // namespace circle_detail

template <Coordinate T>
constexpr Point<long double> centroid(const Circle<T>& circle) {
    assert(circle.radius >= 0);
    return Point<long double>(circle.center);
}

template <Coordinate T>
constexpr long double circle_area(const Circle<T>& circle) {
    assert(circle.radius >= 0);
    long double radius = static_cast<long double>(circle.radius);
    return std::numbers::pi_v<long double> * radius * radius;
}

template <Coordinate T>
constexpr long double circle_circumference(const Circle<T>& circle) {
    assert(circle.radius >= 0);
    return
        2.0L * std::numbers::pi_v<long double> *
        static_cast<long double>(circle.radius);
}

template <Coordinate C, Coordinate P>
PointInCircle point_in_circle(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(eps >= 0.0L);
    if constexpr (std::integral<C> && std::integral<P>) {
        using W = __int128_t;
        W dx = W(point.x) - W(circle.center.x);
        W dy = W(point.y) - W(circle.center.y);
        W radius = W(circle.radius);
        W squared_distance = dx * dx + dy * dy;
        W squared_radius = radius * radius;
        if (squared_distance < squared_radius) return PointInCircle::Inside;
        if (squared_distance > squared_radius) return PointInCircle::Outside;
        return PointInCircle::Boundary;
    } else {
        long double value = geometry::distance(
            Point<long double>(circle.center),
            Point<long double>(point)
        );
        int relation = circle_detail::compare(
            value,
            static_cast<long double>(circle.radius),
            eps
        );
        if (relation < 0) return PointInCircle::Inside;
        if (relation > 0) return PointInCircle::Outside;
        return PointInCircle::Boundary;
    }
}

template <Coordinate C, Coordinate P>
bool on_circle(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    return point_in_circle(circle, point, eps) == PointInCircle::Boundary;
}

template <Coordinate C, Coordinate P>
bool contains(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    return point_in_circle(circle, point, eps) != PointInCircle::Outside;
}

template <Coordinate A, Coordinate B>
Circle<long double> circle_from_diameter(
    const Point<A>& first,
    const Point<B>& second
) {
    Point<long double> a(first);
    Point<long double> b(second);
    Point<long double> center = (a + b) / 2.0L;
    return Circle<long double>{center, geometry::distance(a, b) / 2.0L};
}

template <Coordinate T>
std::optional<Circle<long double>> incircle(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps = 1e-12L
) {
    assert(eps >= 0.0L);
    if (orientation(first, second, third, eps) == 0) return std::nullopt;

    long double opposite_first = geometry::distance(second, third);
    long double opposite_second = geometry::distance(third, first);
    long double opposite_third = geometry::distance(first, second);
    long double perimeter =
        opposite_first + opposite_second + opposite_third;
    Point<long double> center =
        (Point<long double>(first) * opposite_first +
         Point<long double>(second) * opposite_second +
         Point<long double>(third) * opposite_third) /
        perimeter;
    long double doubled_area = std::fabs(
        static_cast<long double>(cross(first, second, third))
    );
    return Circle<long double>{center, doubled_area / perimeter};
}

template <Coordinate T>
std::optional<Circle<long double>> circumcircle(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    long double eps = 1e-12L
) {
    assert(eps >= 0.0L);
    if (orientation(first, second, third, eps) == 0) return std::nullopt;

    Point<long double> origin(first);
    Point<long double> u = Point<long double>(second) - origin;
    Point<long double> v = Point<long double>(third) - origin;
    long double denominator = 2.0L * cross(u, v);
    long double u_norm = norm2(u);
    long double v_norm = norm2(v);
    Point<long double> offset(
        (u_norm * v.y - v_norm * u.y) / denominator,
        (u.x * v_norm - v.x * u_norm) / denominator
    );
    Point<long double> center = origin + offset;
    return Circle<long double>{center, norm(offset)};
}

template <Coordinate A, Coordinate B>
CircleRelation circle_relation(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    assert(eps >= 0.0L);
    if constexpr (std::integral<A> && std::integral<B>) {
        using W = __int128_t;
        W dx = W(second.center.x) - W(first.center.x);
        W dy = W(second.center.y) - W(first.center.y);
        W squared_distance = dx * dx + dy * dy;
        W first_radius = W(first.radius);
        W second_radius = W(second.radius);
        W sum = first_radius + second_radius;
        W difference = first_radius - second_radius;
        if (difference < 0) difference = -difference;
        if (squared_distance == 0 && difference == 0) {
            return CircleRelation::Coincident;
        }
        if (squared_distance > sum * sum) return CircleRelation::Separate;
        if (squared_distance == sum * sum) {
            return CircleRelation::ExternallyTangent;
        }
        if (squared_distance < difference * difference) {
            return CircleRelation::Contained;
        }
        if (squared_distance == difference * difference) {
            return CircleRelation::InternallyTangent;
        }
        return CircleRelation::Intersecting;
    } else {
        long double center_distance = geometry::distance(
            Point<long double>(first.center),
            Point<long double>(second.center)
        );
        long double first_radius = static_cast<long double>(first.radius);
        long double second_radius = static_cast<long double>(second.radius);
        long double sum = first_radius + second_radius;
        long double difference = std::fabs(first_radius - second_radius);
        if (
            center_distance <= eps &&
            difference <= eps
        ) {
            return CircleRelation::Coincident;
        }
        int outer = circle_detail::compare(center_distance, sum, eps);
        if (outer > 0) return CircleRelation::Separate;
        if (outer == 0) return CircleRelation::ExternallyTangent;
        int inner = circle_detail::compare(center_distance, difference, eps);
        if (inner < 0) return CircleRelation::Contained;
        if (inner == 0) return CircleRelation::InternallyTangent;
        return CircleRelation::Intersecting;
    }
}

template <Coordinate C, Coordinate L>
std::vector<Point<long double>> circle_line_intersections(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(line.a != line.b);
    assert(eps >= 0.0L);

    Point<long double> center(circle.center);
    Point<long double> a(line.a);
    Point<long double> direction = Point<long double>(line.b) - a;
    long double length = norm(direction);
    Point<long double> unit = direction / length;
    Point<long double> foot =
        a + direction * (dot(center - a, direction) / dot(direction, direction));
    long double distance_to_line = geometry::distance(center, foot);
    long double radius = static_cast<long double>(circle.radius);
    int relation = circle_detail::compare(distance_to_line, radius, eps);
    if (relation > 0) return {};
    if (relation == 0) return {foot};

    long double offset = std::sqrt(std::max(
        0.0L,
        radius * radius - distance_to_line * distance_to_line
    ));
    Point<long double> first = foot - unit * offset;
    Point<long double> second = foot + unit * offset;
    if (second < first) std::swap(first, second);
    return {first, second};
}

template <Coordinate C, Coordinate L>
std::vector<Point<long double>> circle_line_intersections(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return circle_line_intersections(circle, line, eps);
}

template <Coordinate C, Coordinate R>
std::vector<Point<long double>> circle_ray_intersections(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(ray.origin != ray.through);
    assert(eps >= 0.0L);

    Point<long double> origin(ray.origin);
    Point<long double> direction = Point<long double>(ray.through) - origin;
    Point<long double> unit = direction / norm(direction);
    Line<R> line{ray.origin, ray.through};
    std::vector<Point<long double>> line_points =
        circle_line_intersections(circle, line, eps);
    std::vector<Point<long double>> result;
    for (Point<long double> point : line_points) {
        long double along = dot(point - origin, unit);
        if (along < -eps) continue;
        if (std::fabs(along) <= eps) point = origin;
        circle_detail::push_unique(result, point, eps);
    }
    std::sort(
        result.begin(),
        result.end(),
        [&](const Point<long double>& first, const Point<long double>& second) {
            return dot(first - origin, unit) < dot(second - origin, unit);
        }
    );
    return result;
}

template <Coordinate C, Coordinate R>
std::vector<Point<long double>> circle_ray_intersections(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return circle_ray_intersections(circle, ray, eps);
}

template <Coordinate C, Coordinate S>
std::vector<Point<long double>> circle_segment_intersections(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(eps >= 0.0L);
    if (segment.a == segment.b) {
        if (on_circle(circle, segment.a, eps)) {
            return {Point<long double>(segment.a)};
        }
        return {};
    }

    Point<long double> first_endpoint(segment.a);
    Point<long double> direction =
        Point<long double>(segment.b) - first_endpoint;
    long double length = norm(direction);
    Point<long double> unit = direction / length;
    Line<S> line{segment.a, segment.b};
    std::vector<Point<long double>> line_points =
        circle_line_intersections(circle, line, eps);
    std::vector<Point<long double>> result;
    for (Point<long double> point : line_points) {
        long double along = dot(point - first_endpoint, unit);
        if (along < -eps || along > length + eps) continue;
        if (std::fabs(along) <= eps) point = first_endpoint;
        if (std::fabs(along - length) <= eps) {
            point = Point<long double>(segment.b);
        }
        circle_detail::push_unique(result, point, eps);
    }
    std::sort(
        result.begin(),
        result.end(),
        [&](const Point<long double>& first, const Point<long double>& second) {
            return dot(first - first_endpoint, unit) <
                   dot(second - first_endpoint, unit);
        }
    );
    return result;
}

template <Coordinate C, Coordinate S>
std::vector<Point<long double>> circle_segment_intersections(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return circle_segment_intersections(circle, segment, eps);
}

template <Coordinate A, Coordinate B>
std::vector<Point<long double>> circle_intersections(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    assert(eps >= 0.0L);
    CircleRelation relation = circle_relation(first, second, eps);
    if (
        relation == CircleRelation::Separate ||
        relation == CircleRelation::Contained ||
        relation == CircleRelation::Coincident
    ) {
        return {};
    }

    Point<long double> first_center(first.center);
    Point<long double> second_center(second.center);
    Point<long double> direction = second_center - first_center;
    long double center_distance = norm(direction);
    long double first_radius = static_cast<long double>(first.radius);
    long double second_radius = static_cast<long double>(second.radius);
    long double along =
        (first_radius * first_radius - second_radius * second_radius +
         center_distance * center_distance) /
        (2.0L * center_distance);
    Point<long double> unit = direction / center_distance;
    Point<long double> base = first_center + unit * along;
    if (
        relation == CircleRelation::ExternallyTangent ||
        relation == CircleRelation::InternallyTangent
    ) {
        return {base};
    }

    long double height = std::sqrt(std::max(
        0.0L,
        first_radius * first_radius - along * along
    ));
    Point<long double> perpendicular(-unit.y, unit.x);
    Point<long double> a = base - perpendicular * height;
    Point<long double> b = base + perpendicular * height;
    if (b < a) std::swap(a, b);
    return {a, b};
}

template <Coordinate C, Coordinate R>
std::optional<Point<long double>> first_circle_ray_intersection(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
) {
    std::vector<Point<long double>> points =
        circle_ray_intersections(circle, ray, eps);
    if (points.empty()) return std::nullopt;
    return points.front();
}

template <Coordinate C, Coordinate L>
bool intersects(
    const Circle<C>& circle,
    const Line<L>& line,
    long double eps = 1e-12L
) {
    return !circle_line_intersections(circle, line, eps).empty();
}

template <Coordinate C, Coordinate L>
bool intersects(
    const Line<L>& line,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return intersects(circle, line, eps);
}

template <Coordinate C, Coordinate R>
bool intersects(
    const Circle<C>& circle,
    const Ray<R>& ray,
    long double eps = 1e-12L
) {
    return !circle_ray_intersections(circle, ray, eps).empty();
}

template <Coordinate C, Coordinate R>
bool intersects(
    const Ray<R>& ray,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return intersects(circle, ray, eps);
}

template <Coordinate C, Coordinate S>
bool intersects(
    const Circle<C>& circle,
    const Segment<S>& segment,
    long double eps = 1e-12L
) {
    return !circle_segment_intersections(circle, segment, eps).empty();
}

template <Coordinate C, Coordinate S>
bool intersects(
    const Segment<S>& segment,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    return intersects(circle, segment, eps);
}

template <Coordinate A, Coordinate B>
bool intersects(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    CircleRelation relation = circle_relation(first, second, eps);
    return
        relation == CircleRelation::ExternallyTangent ||
        relation == CircleRelation::Intersecting ||
        relation == CircleRelation::InternallyTangent ||
        relation == CircleRelation::Coincident;
}

template <Coordinate R, Coordinate H, Coordinate C>
Ray<long double> reflected_ray(
    const Ray<R>& incoming,
    const Point<H>& hit,
    const Circle<C>& circle,
    long double eps = 1e-12L
) {
    assert(incoming.origin != incoming.through);
    assert(eps >= 0.0L);
    assert(static_cast<long double>(circle.radius) > eps);
    assert(
        std::fabs(
            geometry::distance(
                Point<long double>(hit),
                Point<long double>(circle.center)
            ) -
            static_cast<long double>(circle.radius)
        ) <= eps
    );

    Point<long double> hit_point(hit);
    Point<long double> normal = normalized(
        hit_point - Point<long double>(circle.center)
    );
    Point<long double> incoming_direction =
        Point<long double>(incoming.through) -
        Point<long double>(incoming.origin);
    Point<long double> outgoing_direction =
        incoming_direction - normal * (2.0L * dot(incoming_direction, normal));
    return Ray<long double>{hit_point, hit_point + outgoing_direction};
}

template <Coordinate C, Coordinate P>
std::vector<Point<long double>> tangent_points(
    const Circle<C>& circle,
    const Point<P>& point,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(eps >= 0.0L);
    Point<long double> center(circle.center);
    Point<long double> external(point);
    Point<long double> direction = external - center;
    long double squared_distance = dot(direction, direction);
    long double radius = static_cast<long double>(circle.radius);
    if (radius == 0.0L) return {center};

    long double center_distance = std::sqrt(squared_distance);
    int relation = circle_detail::compare(center_distance, radius, eps);
    if (relation < 0) return {};
    if (relation == 0) {
        return {center + direction * (radius / center_distance)};
    }

    Point<long double> base =
        center + direction * (radius * radius / squared_distance);
    long double scale =
        radius * std::sqrt(std::max(
            0.0L,
            squared_distance - radius * radius
        )) /
        squared_distance;
    Point<long double> perpendicular(-direction.y, direction.x);
    Point<long double> first = base - perpendicular * scale;
    Point<long double> second = base + perpendicular * scale;
    if (second < first) std::swap(first, second);
    return {first, second};
}

template <Coordinate A, Coordinate B>
std::vector<Line<long double>> common_tangents(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    assert(eps >= 0.0L);
    Point<long double> first_center(first.center);
    Point<long double> second_center(second.center);
    Point<long double> direction = second_center - first_center;
    long double squared_distance = dot(direction, direction);
    long double center_distance = std::sqrt(squared_distance);
    if (center_distance <= eps) return {};

    long double first_radius = static_cast<long double>(first.radius);
    long double second_radius = static_cast<long double>(second.radius);
    std::vector<Line<long double>> result;
    for (int second_side : {1, -1}) {
        long double difference =
            first_radius - second_side * second_radius;
        int relation = circle_detail::compare(
            std::fabs(difference),
            center_distance,
            eps
        );
        if (relation > 0) continue;
        long double perpendicular_length = relation == 0 ? 0.0L : std::sqrt(
            std::max(0.0L, squared_distance - difference * difference)
        );
        int choices = perpendicular_length <= eps ? 1 : 2;
        for (int choice = 0; choice < choices; ++choice) {
            long double side = choice == 0 ? -1.0L : 1.0L;
            Point<long double> normal =
                direction * (difference / squared_distance) +
                Point<long double>(-direction.y, direction.x) *
                    (side * perpendicular_length / squared_distance);
            normal = normalized(normal);
            Point<long double> contact =
                first_center + normal * first_radius;
            Line<long double> tangent =
                circle_detail::tangent_line(contact, normal, eps);
            bool duplicate = false;
            for (const Line<long double>& existing : result) {
                if (circle_detail::same_line(existing, tangent, eps)) {
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) result.push_back(tangent);
        }
    }
    std::sort(
        result.begin(),
        result.end(),
        [](const Line<long double>& left, const Line<long double>& right) {
            if (left.a != right.a) return left.a < right.a;
            return left.b < right.b;
        }
    );
    return result;
}

template <Coordinate A, Coordinate B>
std::vector<Point<long double>> common_tangent_points(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    std::vector<Point<long double>> result;
    for (const Line<long double>& line : common_tangents(first, second, eps)) {
        circle_detail::push_unique(result, line.a, eps);
    }
    std::sort(result.begin(), result.end());
    return result;
}

template <Coordinate A, Coordinate B>
long double circle_circle_intersection_area(
    const Circle<A>& first,
    const Circle<B>& second,
    long double eps = 1e-12L
) {
    assert(first.radius >= 0);
    assert(second.radius >= 0);
    assert(eps >= 0.0L);
    long double first_radius = static_cast<long double>(first.radius);
    long double second_radius = static_cast<long double>(second.radius);
    CircleRelation relation = circle_relation(first, second, eps);
    if (
        relation == CircleRelation::Separate ||
        relation == CircleRelation::ExternallyTangent
    ) {
        return 0.0L;
    }
    if (
        relation == CircleRelation::Contained ||
        relation == CircleRelation::InternallyTangent ||
        relation == CircleRelation::Coincident
    ) {
        long double radius = std::min(first_radius, second_radius);
        return std::numbers::pi_v<long double> * radius * radius;
    }

    long double center_distance = geometry::distance(
        Point<long double>(first.center),
        Point<long double>(second.center)
    );
    long double first_cosine = std::clamp(
        (
            (center_distance - second_radius) *
                (center_distance + second_radius) +
            first_radius * first_radius
        ) /
            (2.0L * center_distance * first_radius),
        -1.0L,
        1.0L
    );
    long double second_cosine = std::clamp(
        (
            (center_distance - first_radius) *
                (center_distance + first_radius) +
            second_radius * second_radius
        ) /
            (2.0L * center_distance * second_radius),
        -1.0L,
        1.0L
    );
    long double radicand =
        (-center_distance + first_radius + second_radius) *
        (center_distance + first_radius - second_radius) *
        (center_distance - first_radius + second_radius) *
        (center_distance + first_radius + second_radius);
    long double height =
        std::sqrt(std::max(0.0L, radicand)) /
        (2.0L * center_distance);
    long double first_sine = std::clamp(
        height / first_radius,
        0.0L,
        1.0L
    );
    long double second_sine = std::clamp(
        height / second_radius,
        0.0L,
        1.0L
    );
    long double first_angle = std::atan2(first_sine, first_cosine);
    long double second_angle = std::atan2(second_sine, second_cosine);
    return
        first_radius * first_radius *
            circle_detail::circular_segment_angle_term(
                first_angle,
                first_sine,
                first_cosine
            ) +
        second_radius * second_radius *
            circle_detail::circular_segment_angle_term(
                second_angle,
                second_sine,
                second_cosine
            );
}

template <Coordinate C, Coordinate P>
long double circle_polygon_intersection_area(
    const Circle<C>& circle,
    const std::vector<Point<P>>& polygon,
    long double eps = 1e-12L
) {
    assert(circle.radius >= 0);
    assert(eps >= 0.0L);
    if (polygon.empty() || circle.radius == 0) return 0.0L;

    Point<long double> center(circle.center);
    long double radius = static_cast<long double>(circle.radius);
    long double result = 0.0L;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        Point<long double> first =
            Point<long double>(polygon[index]) - center;
        Point<long double> second =
            Point<long double>(polygon[(index + 1) % polygon.size()]) - center;
        result += circle_detail::segment_disk_signed_area(
            first,
            second,
            radius,
            eps
        );
    }
    return std::fabs(result);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CIRCLE_HPP
