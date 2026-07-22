#ifndef M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP
#define M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP 1

#include "../ds/range_query/fenwick_tree.hpp"
#include "line.hpp"

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <set>
#include <vector>

namespace m1une {
namespace geometry {

namespace manhattan_segment_intersections_detail {

enum class EventKind {
    add,
    query,
    remove,
};

template <std::integral T>
struct Event {
    T y;
    T left;
    T right;
    EventKind kind;

    Event(T y_value, T left_value, T right_value, EventKind kind_value)
        : y(y_value),
          left(left_value),
          right(right_value),
          kind(kind_value) {}
};

template <std::integral T>
std::vector<Event<T>> make_events(
    const std::vector<Segment<T>>& segments,
    std::vector<T>* vertical_x_coordinates = nullptr
) {
    assert(segments.size() <= std::size_t(std::numeric_limits<int>::max()));

    std::vector<Event<T>> events;
    events.reserve(2 * segments.size());
    if (vertical_x_coordinates != nullptr) {
        vertical_x_coordinates->reserve(segments.size());
    }

    for (const Segment<T>& segment : segments) {
        assert(segment.a != segment.b);
        assert(segment.a.x == segment.b.x || segment.a.y == segment.b.y);

        if (segment.a.x == segment.b.x) {
            T bottom = std::min(segment.a.y, segment.b.y);
            T top = std::max(segment.a.y, segment.b.y);
            events.emplace_back(
                bottom,
                segment.a.x,
                segment.a.x,
                EventKind::add
            );
            events.emplace_back(
                top,
                segment.a.x,
                segment.a.x,
                EventKind::remove
            );
            if (vertical_x_coordinates != nullptr) {
                vertical_x_coordinates->push_back(segment.a.x);
            }
        } else {
            T left = std::min(segment.a.x, segment.b.x);
            T right = std::max(segment.a.x, segment.b.x);
            events.emplace_back(
                segment.a.y,
                left,
                right,
                EventKind::query
            );
        }
    }

    std::sort(
        events.begin(),
        events.end(),
        [](const Event<T>& a, const Event<T>& b) {
            if (a.y != b.y) return a.y < b.y;
            if (a.kind != b.kind) return a.kind < b.kind;
            if (a.left != b.left) return a.left < b.left;
            return a.right < b.right;
        }
    );
    return events;
}

}  // namespace manhattan_segment_intersections_detail

// Counts intersecting horizontal-vertical pairs of closed segments.
template <std::integral T>
long long manhattan_segment_intersections(
    const std::vector<Segment<T>>& segments
) {
    using Event = manhattan_segment_intersections_detail::Event<T>;
    using EventKind =
        manhattan_segment_intersections_detail::EventKind;

    std::vector<T> vertical_x_coordinates;
    std::vector<Event> events =
        manhattan_segment_intersections_detail::make_events(
            segments,
            &vertical_x_coordinates
        );

    std::sort(
        vertical_x_coordinates.begin(),
        vertical_x_coordinates.end()
    );
    vertical_x_coordinates.erase(
        std::unique(
            vertical_x_coordinates.begin(),
            vertical_x_coordinates.end()
        ),
        vertical_x_coordinates.end()
    );
    m1une::ds::FenwickTree<long long> active(
        int(vertical_x_coordinates.size())
    );
    long long result = 0;
    for (const Event& event : events) {
        if (event.kind == EventKind::query) {
            int left = int(
                std::lower_bound(
                    vertical_x_coordinates.begin(),
                    vertical_x_coordinates.end(),
                    event.left
                ) - vertical_x_coordinates.begin()
            );
            int right = int(
                std::upper_bound(
                    vertical_x_coordinates.begin(),
                    vertical_x_coordinates.end(),
                    event.right
                ) - vertical_x_coordinates.begin()
            );
            result += active.sum(left, right);
            continue;
        }

        int x = int(
            std::lower_bound(
                vertical_x_coordinates.begin(),
                vertical_x_coordinates.end(),
                event.left
            ) - vertical_x_coordinates.begin()
        );
        active.add(x, event.kind == EventKind::add ? 1 : -1);
    }
    return result;
}

// Returns one point per intersecting horizontal-vertical pair.
template <std::integral T>
std::vector<Point<T>> manhattan_segment_intersection_points(
    const std::vector<Segment<T>>& segments
) {
    using Event = manhattan_segment_intersections_detail::Event<T>;
    using EventKind =
        manhattan_segment_intersections_detail::EventKind;

    std::vector<Event> events =
        manhattan_segment_intersections_detail::make_events(segments);
    std::multiset<T> active;
    std::vector<Point<T>> result;

    for (const Event& event : events) {
        if (event.kind == EventKind::add) {
            active.insert(event.left);
        } else if (event.kind == EventKind::remove) {
            auto iterator = active.find(event.left);
            assert(iterator != active.end());
            active.erase(iterator);
        } else {
            auto iterator = active.lower_bound(event.left);
            while (iterator != active.end() && *iterator <= event.right) {
                result.emplace_back(*iterator, event.y);
                ++iterator;
            }
        }
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_MANHATTAN_SEGMENT_INTERSECTIONS_HPP
