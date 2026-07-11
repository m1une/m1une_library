#ifndef M1UNE_GEOMETRY_CLOSEST_PAIR_HPP
#define M1UNE_GEOMETRY_CLOSEST_PAIR_HPP 1

#include <algorithm>
#include <optional>
#include <utility>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

template <Coordinate T>
struct ClosestPair {
    int first;
    int second;
    wide_type<T> distance_squared;
};

// Returns two distinct original indices with minimum Euclidean distance.
template <Coordinate T>
std::optional<ClosestPair<T>> closest_pair(
    const std::vector<Point<T>>& points
) {
    const int n = int(points.size());
    if (n < 2) return std::nullopt;

    struct IndexedPoint {
        Point<T> point;
        int index;
    };

    std::vector<IndexedPoint> ordered;
    ordered.reserve(n);
    for (int index = 0; index < n; index++) {
        ordered.push_back(IndexedPoint{points[index], index});
    }
    std::sort(
        ordered.begin(),
        ordered.end(),
        [](const IndexedPoint& first, const IndexedPoint& second) {
            if (first.point < second.point) return true;
            if (second.point < first.point) return false;
            return first.index < second.index;
        }
    );

    std::optional<ClosestPair<T>> duplicate_result;
    for (int first = 0; first < n;) {
        int last = first + 1;
        while (last < n && ordered[last].point == ordered[first].point) last++;
        if (last - first >= 2) {
            int first_index = ordered[first].index;
            int second_index = ordered[first + 1].index;
            std::pair<int, int> candidate(first_index, second_index);
            if (
                !duplicate_result ||
                candidate < std::pair(
                    duplicate_result->first,
                    duplicate_result->second
                )
            ) {
                duplicate_result = ClosestPair<T>{
                    first_index,
                    second_index,
                    wide_type<T>(0)
                };
            }
        }
        first = last;
    }
    if (duplicate_result) return duplicate_result;

    std::optional<ClosestPair<T>> result;
    auto consider = [&result, &points](int first, int second) {
        if (second < first) std::swap(first, second);
        wide_type<T> squared = distance2(points[first], points[second]);
        std::pair<int, int> candidate(first, second);
        if (
            !result ||
            squared < result->distance_squared ||
            (
                squared == result->distance_squared &&
                candidate < std::pair(result->first, result->second)
            )
        ) {
            result = ClosestPair<T>{first, second, squared};
        }
    };
    consider(ordered[0].index, ordered[1].index);

    auto by_y = [](const IndexedPoint& first, const IndexedPoint& second) {
        if (first.point.y != second.point.y) {
            return first.point.y < second.point.y;
        }
        if (first.point.x != second.point.x) {
            return first.point.x < second.point.x;
        }
        return first.index < second.index;
    };

    std::vector<IndexedPoint> buffer(n);
    auto solve = [&](auto&& self, int left, int right) -> void {
        if (right - left <= 3) {
            for (int first = left; first < right; first++) {
                for (int second = first + 1; second < right; second++) {
                    consider(ordered[first].index, ordered[second].index);
                }
            }
            std::sort(ordered.begin() + left, ordered.begin() + right, by_y);
            return;
        }

        int middle = (left + right) / 2;
        T middle_x = ordered[middle].point.x;
        self(self, left, middle);
        self(self, middle, right);
        std::merge(
            ordered.begin() + left,
            ordered.begin() + middle,
            ordered.begin() + middle,
            ordered.begin() + right,
            buffer.begin() + left,
            by_y
        );
        std::copy(
            buffer.begin() + left,
            buffer.begin() + right,
            ordered.begin() + left
        );

        int strip_size = 0;
        for (int index = left; index < right; index++) {
            using W = wide_type<T>;
            W dx = W(ordered[index].point.x) - W(middle_x);
            if (result->distance_squared < dx * dx) continue;

            for (int previous = strip_size - 1; previous >= 0; previous--) {
                W dy = W(ordered[index].point.y) - W(buffer[previous].point.y);
                if (result->distance_squared < dy * dy) break;
                consider(ordered[index].index, buffer[previous].index);
            }
            buffer[strip_size++] = ordered[index];
        }
    };
    solve(solve, 0, n);
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CLOSEST_PAIR_HPP
