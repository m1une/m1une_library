#ifndef M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP
#define M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP 1

#include "point.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace geometry {

template <Coordinate T>
struct AxisAlignedRectangle {
    T left;
    T bottom;
    T right;
    T top;

    constexpr AxisAlignedRectangle()
        : left(0), bottom(0), right(0), top(0) {}

    constexpr AxisAlignedRectangle(
        T left_value,
        T bottom_value,
        T right_value,
        T top_value
    )
        : left(left_value),
          bottom(bottom_value),
          right(right_value),
          top(top_value) {}

    friend constexpr bool operator==(
        const AxisAlignedRectangle&,
        const AxisAlignedRectangle&
    ) = default;
};

namespace rectangle_union_area_detail {

template <Coordinate T>
struct Event {
    T x;
    T bottom;
    T top;
    int delta;

    Event(T x_value, T bottom_value, T top_value, int delta_value)
        : x(x_value),
          bottom(bottom_value),
          top(top_value),
          delta(delta_value) {}
};

template <Coordinate T>
struct CoveredLengthTree {
    using Wide = wide_type<T>;

    int interval_count;
    const std::vector<T>& coordinates;
    std::vector<int> cover;
    std::vector<Wide> covered;

    explicit CoveredLengthTree(const std::vector<T>& values)
        : interval_count(std::max(0, int(values.size()) - 1)),
          coordinates(values),
          cover(std::max(1, 4 * interval_count), 0),
          covered(std::max(1, 4 * interval_count), Wide(0)) {}

    void pull(int node, int left, int right) {
        if (cover[node] > 0) {
            covered[node] =
                Wide(coordinates[right]) - Wide(coordinates[left]);
        } else if (right - left == 1) {
            covered[node] = 0;
        } else {
            covered[node] = covered[2 * node] + covered[2 * node + 1];
        }
    }

    void add(
        int query_left,
        int query_right,
        int delta,
        int node,
        int left,
        int right
    ) {
        if (query_right <= left || right <= query_left) return;
        if (query_left <= left && right <= query_right) {
            cover[node] += delta;
            assert(cover[node] >= 0);
            pull(node, left, right);
            return;
        }
        int middle = (left + right) / 2;
        add(query_left, query_right, delta, 2 * node, left, middle);
        add(
            query_left,
            query_right,
            delta,
            2 * node + 1,
            middle,
            right
        );
        pull(node, left, right);
    }

    void add(int left, int right, int delta) {
        if (left >= right) return;
        assert(0 <= left && left < right && right <= interval_count);
        add(left, right, delta, 1, 0, interval_count);
    }

    Wide length() const {
        return interval_count == 0 ? Wide(0) : covered[1];
    }
};

}  // namespace rectangle_union_area_detail

template <Coordinate T>
wide_type<T> rectangle_union_area(
    const std::vector<AxisAlignedRectangle<T>>& rectangles
) {
    using Wide = wide_type<T>;
    using Event = rectangle_union_area_detail::Event<T>;

    std::vector<Event> events;
    std::vector<T> y_coordinates;
    events.reserve(2 * rectangles.size());
    y_coordinates.reserve(2 * rectangles.size());
    for (const AxisAlignedRectangle<T>& rectangle : rectangles) {
        assert(rectangle.left <= rectangle.right);
        assert(rectangle.bottom <= rectangle.top);
        if (
            rectangle.left == rectangle.right ||
            rectangle.bottom == rectangle.top
        ) {
            continue;
        }
        events.emplace_back(
            rectangle.left,
            rectangle.bottom,
            rectangle.top,
            1
        );
        events.emplace_back(
            rectangle.right,
            rectangle.bottom,
            rectangle.top,
            -1
        );
        y_coordinates.push_back(rectangle.bottom);
        y_coordinates.push_back(rectangle.top);
    }
    if (events.empty()) return Wide(0);

    std::sort(y_coordinates.begin(), y_coordinates.end());
    y_coordinates.erase(
        std::unique(y_coordinates.begin(), y_coordinates.end()),
        y_coordinates.end()
    );
    std::sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        return a.x < b.x;
    });

    rectangle_union_area_detail::CoveredLengthTree<T> tree(y_coordinates);
    Wide area = 0;
    T previous_x = events.front().x;
    int event_index = 0;
    while (event_index < int(events.size())) {
        T x = events[event_index].x;
        area += tree.length() * (Wide(x) - Wide(previous_x));

        int next = event_index;
        while (next < int(events.size()) && events[next].x == x) {
            int bottom = int(
                std::lower_bound(
                    y_coordinates.begin(),
                    y_coordinates.end(),
                    events[next].bottom
                ) - y_coordinates.begin()
            );
            int top = int(
                std::lower_bound(
                    y_coordinates.begin(),
                    y_coordinates.end(),
                    events[next].top
                ) - y_coordinates.begin()
            );
            tree.add(bottom, top, events[next].delta);
            next++;
        }
        previous_x = x;
        event_index = next;
    }
    return area;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_RECTANGLE_UNION_AREA_HPP
