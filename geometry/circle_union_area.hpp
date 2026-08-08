#ifndef M1UNE_GEOMETRY_CIRCLE_UNION_AREA_HPP
#define M1UNE_GEOMETRY_CIRCLE_UNION_AREA_HPP 1

#include "circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>
#include <utility>
#include <vector>

namespace m1une {
namespace geometry {

namespace circle_union_area_detail {

inline long double arc_integral(
    long double center_x,
    long double center_y,
    long double radius,
    long double first_angle,
    long double second_angle
) {
    return (
        radius * center_x *
            (std::sin(second_angle) - std::sin(first_angle)) -
        radius * center_y *
            (std::cos(second_angle) - std::cos(first_angle)) +
        radius * radius * (second_angle - first_angle)
    ) / 2.0L;
}

}  // namespace circle_union_area_detail

template <Coordinate T>
long double circle_union_area(
    const std::vector<Circle<T>>& circles,
    long double eps = 1e-12L
) {
    assert(eps >= 0.0L);
    const long double pi = std::numbers::pi_v<long double>;
    const long double full_angle = 2.0L * pi;
    long double area = 0.0L;

    for (int index = 0; index < int(circles.size()); ++index) {
        const Circle<T>& circle = circles[index];
        assert(circle.radius >= 0);
        long double radius = static_cast<long double>(circle.radius);
        if (radius == 0.0L) continue;

        long double center_x = static_cast<long double>(circle.center.x);
        long double center_y = static_cast<long double>(circle.center.y);
        bool covered = false;
        std::vector<std::pair<long double, long double>> intervals;
        intervals.reserve(2 * circles.size());

        for (int other_index = 0;
             other_index < int(circles.size());
             ++other_index) {
            if (other_index == index) continue;
            const Circle<T>& other = circles[other_index];
            assert(other.radius >= 0);
            long double other_radius =
                static_cast<long double>(other.radius);
            if (other_radius == 0.0L) continue;

            long double difference_x =
                static_cast<long double>(other.center.x) - center_x;
            long double difference_y =
                static_cast<long double>(other.center.y) - center_y;
            long double center_distance =
                std::hypot(difference_x, difference_y);
            long double tolerance = eps * std::max({
                1.0L,
                center_distance,
                radius,
                other_radius
            });

            if (
                center_distance <= tolerance &&
                std::fabs(radius - other_radius) <= tolerance
            ) {
                if (other_index < index) covered = true;
                continue;
            }
            if (
                radius <= other_radius &&
                center_distance + radius <= other_radius + tolerance
            ) {
                covered = true;
                break;
            }
            if (
                center_distance >= radius + other_radius - tolerance ||
                center_distance <=
                    std::fabs(radius - other_radius) + tolerance
            ) {
                continue;
            }

            long double direction =
                std::atan2(difference_y, difference_x);
            long double cosine = std::clamp(
                (
                    center_distance * center_distance + radius * radius -
                    other_radius * other_radius
                ) / (2.0L * center_distance * radius),
                -1.0L,
                1.0L
            );
            long double half_width = std::acos(cosine);
            long double left = std::fmod(
                direction - half_width,
                full_angle
            );
            if (left < 0.0L) left += full_angle;
            long double right = left + 2.0L * half_width;
            if (right <= full_angle) {
                intervals.emplace_back(left, right);
            } else {
                intervals.emplace_back(left, full_angle);
                intervals.emplace_back(0.0L, right - full_angle);
            }
        }
        if (covered) continue;

        std::sort(intervals.begin(), intervals.end());
        long double exposed_begin = 0.0L;
        for (const auto& [left, right] : intervals) {
            if (exposed_begin < left) {
                area += circle_union_area_detail::arc_integral(
                    center_x,
                    center_y,
                    radius,
                    exposed_begin,
                    left
                );
            }
            exposed_begin = std::max(exposed_begin, right);
        }
        if (exposed_begin < full_angle) {
            area += circle_union_area_detail::arc_integral(
                center_x,
                center_y,
                radius,
                exposed_begin,
                full_angle
            );
        }
    }
    return std::max(0.0L, area);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CIRCLE_UNION_AREA_HPP
