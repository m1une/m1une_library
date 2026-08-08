#ifndef M1UNE_GEOMETRY_CIRCLE_COVERAGE_AREAS_HPP
#define M1UNE_GEOMETRY_CIRCLE_COVERAGE_AREAS_HPP 1

#include "circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numbers>
#include <utility>
#include <vector>

namespace m1une {
namespace geometry {

namespace circle_coverage_areas_detail {

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

}  // namespace circle_coverage_areas_detail

template <Coordinate T>
std::vector<long double> circle_coverage_areas(
    const std::vector<Circle<T>>& circles,
    long double eps = 1e-12L
) {
    assert(eps >= 0.0L);
    const int count = int(circles.size());
    const long double full_angle =
        2.0L * std::numbers::pi_v<long double>;
    std::vector<long double> at_least(count + 2, 0.0L);

    for (int index = 0; index < count; ++index) {
        const Circle<T>& circle = circles[index];
        assert(circle.radius >= 0);
        long double radius = static_cast<long double>(circle.radius);
        if (radius == 0.0L) continue;

        long double center_x = static_cast<long double>(circle.center.x);
        long double center_y = static_cast<long double>(circle.center.y);
        int coverage = 0;
        int multiplicity = 1;
        bool duplicate = false;
        std::vector<std::pair<long double, int>> events;
        events.reserve(2 * circles.size());

        for (int other_index = 0; other_index < count; ++other_index) {
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
                if (other_index < index) duplicate = true;
                multiplicity++;
                continue;
            }
            if (
                radius <= other_radius &&
                center_distance + radius <= other_radius + tolerance
            ) {
                coverage++;
                continue;
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
            long double right = std::fmod(
                direction + half_width,
                full_angle
            );
            if (right < 0.0L) right += full_angle;
            if (left <= right) {
                events.emplace_back(left, 1);
                events.emplace_back(right, -1);
            } else {
                coverage++;
                events.emplace_back(right, -1);
                events.emplace_back(left, 1);
            }
        }
        if (duplicate) continue;

        std::sort(events.begin(), events.end());
        long double previous_angle = 0.0L;
        auto add_arc = [&](long double first_angle, long double second_angle) {
            long double integral =
                circle_coverage_areas_detail::arc_integral(
                    center_x,
                    center_y,
                    radius,
                    first_angle,
                    second_angle
                );
            for (int offset = 1; offset <= multiplicity; ++offset) {
                at_least[coverage + offset] += integral;
            }
        };
        int event_index = 0;
        while (event_index < int(events.size())) {
            long double angle = events[event_index].first;
            add_arc(previous_angle, angle);
            int next = event_index;
            while (
                next < int(events.size()) &&
                events[next].first == angle
            ) {
                coverage += events[next].second;
                next++;
            }
            previous_angle = angle;
            event_index = next;
        }
        add_arc(previous_angle, full_angle);
    }

    std::vector<long double> exact(count + 1, 0.0L);
    for (int coverage = 1; coverage <= count; ++coverage) {
        exact[coverage] = std::max(
            0.0L,
            at_least[coverage] - at_least[coverage + 1]
        );
    }
    return exact;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CIRCLE_COVERAGE_AREAS_HPP
