#ifndef M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP
#define M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

namespace count_points_in_triangle_detail {

class FenwickTree {
   private:
    std::vector<int> values;

   public:
    explicit FenwickTree(std::size_t size) : values(size, 0) {}

    void add(std::size_t position) {
        for (
            ++position;
            position <= values.size();
            position += position & -position
        ) {
            values[position - 1]++;
        }
    }

    int prefix_sum(std::size_t right) const {
        int result = 0;
        for (; right > 0; right -= right & -right) {
            result += values[right - 1];
        }
        return result;
    }
};

template <std::integral T>
struct SweepItem {
    using Wide = wide_type<T>;

    Wide x;
    Wide y;
    int index;
    int kind;
};

}  // namespace count_points_in_triangle_detail

template <std::integral T>
class CountPointsInTriangle {
   private:
    using Wide = wide_type<T>;
    using SweepItem = count_points_in_triangle_detail::SweepItem<T>;

    static constexpr int before_counted_points = 0;
    static constexpr int counted_point = 1;
    static constexpr int after_counted_points = 2;

    std::vector<Point<T>> vertices;
    std::vector<int> horizontal_left;
    std::vector<int> horizontal_equal;
    std::vector<std::vector<int>> edge_left;
    std::vector<std::vector<int>> edge_equal;

    static bool yx_less(const Point<T>& first, const Point<T>& second) {
        if (first.y != second.y) return first.y < second.y;
        return first.x < second.x;
    }

    SweepItem make_item(
        const Point<T>& origin,
        const Point<T>& point,
        int index,
        int kind
    ) const {
        return SweepItem{
            Wide(point.x) - Wide(origin.x),
            Wide(point.y) - Wide(origin.y),
            index,
            kind
        };
    }

    void build(const std::vector<Point<T>>& counted_points) {
        const int vertex_count = int(vertices.size());
        const int counted_point_count = int(counted_points.size());
        for (int anchor = 0; anchor < vertex_count; ++anchor) {
            for (const Point<T>& point : counted_points) {
                if (point.y != vertices[anchor].y) continue;
                if (point.x < vertices[anchor].x) {
                    horizontal_left[anchor]++;
                } else if (point.x == vertices[anchor].x) {
                    horizontal_equal[anchor]++;
                }
            }

            std::vector<SweepItem> items;
            items.reserve(2 * vertices.size() + counted_points.size());
            for (int index = 0; index < vertex_count; ++index) {
                if (vertices[anchor].y < vertices[index].y) {
                    items.push_back(make_item(
                        vertices[anchor],
                        vertices[index],
                        index,
                        before_counted_points
                    ));
                }
            }
            for (int index = 0; index < counted_point_count; ++index) {
                if (vertices[anchor].y < counted_points[index].y) {
                    items.push_back(make_item(
                        vertices[anchor],
                        counted_points[index],
                        index,
                        counted_point
                    ));
                }
            }
            for (int index = 0; index < vertex_count; ++index) {
                if (vertices[anchor].y < vertices[index].y) {
                    items.push_back(make_item(
                        vertices[anchor],
                        vertices[index],
                        index,
                        after_counted_points
                    ));
                }
            }

            std::sort(
                items.begin(),
                items.end(),
                [](const SweepItem& first, const SweepItem& second) {
                    const Wide determinant =
                        first.x * second.y - first.y * second.x;
                    if (determinant != 0) return determinant < 0;
                    return first.kind < second.kind;
                }
            );

            std::vector<std::size_t> height_order(items.size());
            std::iota(height_order.begin(), height_order.end(), 0);
            std::sort(
                height_order.begin(),
                height_order.end(),
                [&items](std::size_t first, std::size_t second) {
                    if (items[first].y != items[second].y) {
                        return items[first].y < items[second].y;
                    }
                    return items[first].kind % 2 < items[second].kind % 2;
                }
            );

            count_points_in_triangle_detail::FenwickTree fenwick(items.size());
            for (std::size_t position : height_order) {
                const SweepItem& item = items[position];
                if (item.kind == before_counted_points) {
                    edge_left[anchor][item.index] =
                        fenwick.prefix_sum(position + 1);
                } else if (item.kind == counted_point) {
                    fenwick.add(position);
                } else {
                    edge_equal[anchor][item.index] =
                        fenwick.prefix_sum(position + 1);
                }
            }
            for (int index = 0; index < vertex_count; ++index) {
                edge_equal[anchor][index] -= edge_left[anchor][index];
            }
        }
    }

   public:
    CountPointsInTriangle(
        const std::vector<Point<T>>& triangle_vertices,
        const std::vector<Point<T>>& counted_points
    )
        : vertices(triangle_vertices),
          horizontal_left(vertices.size(), 0),
          horizontal_equal(vertices.size(), 0),
          edge_left(vertices.size(), std::vector<int>(vertices.size(), 0)),
          edge_equal(vertices.size(), std::vector<int>(vertices.size(), 0)) {
        assert(
            vertices.size() <=
            static_cast<std::size_t>(std::numeric_limits<int>::max())
        );
        assert(
            counted_points.size() <=
            static_cast<std::size_t>(std::numeric_limits<int>::max())
        );
        build(counted_points);
    }

    int query(int first, int second, int third) const {
        const int size = int(vertices.size());
        assert(0 <= first && first < size);
        assert(0 <= second && second < size);
        assert(0 <= third && third < size);

        if (yx_less(vertices[second], vertices[first])) {
            std::swap(first, second);
        }
        if (yx_less(vertices[third], vertices[second])) {
            std::swap(second, third);
        }
        if (yx_less(vertices[second], vertices[first])) {
            std::swap(first, second);
        }

        const Wide determinant = cross(
            vertices[first],
            vertices[second],
            vertices[third]
        );
        if (determinant == 0) return 0;

        long long result;
        if (vertices[first].y == vertices[second].y) {
            result =
                static_cast<long long>(edge_left[second][third]) -
                edge_left[first][third] -
                edge_equal[first][third];
        } else if (vertices[second].y == vertices[third].y) {
            result =
                static_cast<long long>(edge_left[first][third]) -
                edge_left[first][second] -
                edge_equal[first][second];
        } else if (determinant < 0) {
            result =
                static_cast<long long>(edge_left[first][third]) -
                edge_left[second][third] -
                edge_equal[second][third] -
                edge_left[first][second] -
                edge_equal[first][second] -
                horizontal_left[second] -
                horizontal_equal[second];
        } else {
            result =
                static_cast<long long>(edge_left[first][second]) +
                edge_left[second][third] +
                horizontal_left[second] -
                edge_left[first][third] -
                edge_equal[first][third];
        }
        assert(
            0 <= result &&
            result <= std::numeric_limits<int>::max()
        );
        return int(result);
    }
};

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_COUNT_POINTS_IN_TRIANGLE_HPP
