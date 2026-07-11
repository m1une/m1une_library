#ifndef M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP
#define M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <optional>
#include <type_traits>
#include <vector>

#include "circle.hpp"

namespace m1une {
namespace geometry {

struct MinimumEnclosingCircle {
    Circle<long double> circle;
    std::vector<int> support;
};

namespace internal {

struct MinimumEnclosingCircleSupport {
    int size = 0;
    std::array<int, 3> index = {-1, -1, -1};
};

template <Coordinate T>
Circle<long double> circle_from_support(
    const std::vector<Point<T>>& points,
    const MinimumEnclosingCircleSupport& support
) {
    assert(1 <= support.size && support.size <= 3);
    Point<long double> first(points[support.index[0]]);
    if (support.size == 1) return Circle<long double>{first, 0.0L};

    Point<long double> second(points[support.index[1]]);
    if (support.size == 2) {
        Point<long double> center = (first + second) / 2.0L;
        return Circle<long double>{center, distance(first, second) / 2.0L};
    }

    Point<long double> third(points[support.index[2]]);
    long double denominator = 2.0L * cross(first, second, third);
    assert(denominator != 0.0L);
    long double first_norm = norm2(first);
    long double second_norm = norm2(second);
    long double third_norm = norm2(third);
    Point<long double> center(
        (
            first_norm * (second.y - third.y) +
            second_norm * (third.y - first.y) +
            third_norm * (first.y - second.y)
        ) / denominator,
        (
            first_norm * (third.x - second.x) +
            second_norm * (first.x - third.x) +
            third_norm * (second.x - first.x)
        ) / denominator
    );
    return Circle<long double>{center, distance(center, first)};
}

template <Coordinate T>
void reduce_collinear_support(
    const std::vector<Point<T>>& points,
    MinimumEnclosingCircleSupport& support
) {
    if (support.size != 3) return;
    const Point<T>& first = points[support.index[0]];
    const Point<T>& second = points[support.index[1]];
    const Point<T>& third = points[support.index[2]];
    if (cross(first, second, third) != 0) return;

    wide_type<T> first_second = distance2(first, second);
    wide_type<T> second_third = distance2(second, third);
    wide_type<T> first_third = distance2(first, third);
    if (first_second >= second_third && first_second >= first_third) {
        support.size = 2;
    } else if (second_third >= first_second && second_third >= first_third) {
        support.size = 2;
        support.index[0] = support.index[1];
        support.index[1] = support.index[2];
    } else {
        support.size = 2;
        support.index[1] = support.index[2];
    }
}

template <Coordinate T>
bool support_contains(
    const std::vector<Point<T>>& points,
    const MinimumEnclosingCircleSupport& support,
    int point_index,
    long double eps
) {
    if (support.size == 0) return false;
    const Point<T>& point = points[point_index];
    const Point<T>& first = points[support.index[0]];
    if (support.size == 1) return point == first;

    if constexpr (std::integral<T>) {
        using W = wide_type<T>;
        const Point<T>& second = points[support.index[1]];
        if (support.size == 2) {
            W ux = W(2) * W(point.x) - W(first.x) - W(second.x);
            W uy = W(2) * W(point.y) - W(first.y) - W(second.y);
            W dx = W(first.x) - W(second.x);
            W dy = W(first.y) - W(second.y);
            return ux * ux + uy * uy <= dx * dx + dy * dy;
        }

        const Point<T>& third = points[support.index[2]];
        W ax = W(first.x) - W(point.x);
        W ay = W(first.y) - W(point.y);
        W bx = W(second.x) - W(point.x);
        W by = W(second.y) - W(point.y);
        W cx = W(third.x) - W(point.x);
        W cy = W(third.y) - W(point.y);
        W a_norm = ax * ax + ay * ay;
        W b_norm = bx * bx + by * by;
        W c_norm = cx * cx + cy * cy;
        W determinant =
            ax * (by * c_norm - cy * b_norm) -
            ay * (bx * c_norm - cx * b_norm) +
            a_norm * (bx * cy - by * cx);
        W direction = cross(first, second, third);
        return direction > 0 ? determinant >= 0 : determinant <= 0;
    } else {
        Circle<long double> circle = circle_from_support(points, support);
        long double squared = distance2(Point<long double>(point), circle.center);
        long double radius_squared = circle.radius * circle.radius;
        long double tolerance = eps * std::max(1.0L, radius_squared);
        return squared <= radius_squared + tolerance;
    }
}

inline std::uint64_t minimum_enclosing_circle_random(std::uint64_t& state) {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

}  // namespace internal

// Returns the unique minimum circle containing every input point.
template <Coordinate T>
std::optional<MinimumEnclosingCircle> minimum_enclosing_circle(
    const std::vector<Point<T>>& points,
    long double eps = 1e-12L
) {
    if (points.empty()) return std::nullopt;
    assert(eps >= 0.0L);

    const int n = int(points.size());
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::uint64_t state = 0x9e3779b97f4a7c15ULL;
    for (int index = n - 1; index >= 1; index--) {
        int other = int(
            internal::minimum_enclosing_circle_random(state) %
            std::uint64_t(index + 1)
        );
        std::swap(order[index], order[other]);
    }

    internal::MinimumEnclosingCircleSupport support;
    for (int first = 0; first < n; first++) {
        if (internal::support_contains(points, support, order[first], eps)) {
            continue;
        }
        support.size = 1;
        support.index[0] = order[first];
        for (int second = 0; second < first; second++) {
            if (internal::support_contains(points, support, order[second], eps)) {
                continue;
            }
            support.size = 2;
            support.index[0] = order[first];
            support.index[1] = order[second];
            for (int third = 0; third < second; third++) {
                if (internal::support_contains(
                        points,
                        support,
                        order[third],
                        eps
                    )) {
                    continue;
                }
                support.size = 3;
                support.index[0] = order[first];
                support.index[1] = order[second];
                support.index[2] = order[third];
                internal::reduce_collinear_support(points, support);
            }
        }
    }

    MinimumEnclosingCircle result;
    result.circle = internal::circle_from_support(points, support);
    result.support.assign(
        support.index.begin(),
        support.index.begin() + support.size
    );
    std::sort(result.support.begin(), result.support.end());
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_MINIMUM_ENCLOSING_CIRCLE_HPP
