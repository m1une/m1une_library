#ifndef M1UNE_GEOMETRY_CONVEX_LAYERS_HPP
#define M1UNE_GEOMETRY_CONVEX_LAYERS_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

#include "point.hpp"

namespace m1une {
namespace geometry {

namespace convex_layers_detail {

template <Coordinate T>
struct LayerPoint {
    wide_type<T> x;
    wide_type<T> y;
};

template <Coordinate T>
wide_type<T> layer_cross(
    const LayerPoint<T>& first,
    const LayerPoint<T>& second,
    const LayerPoint<T>& third
) {
    return
        (second.x - first.x) * (third.y - first.y) -
        (second.y - first.y) * (third.x - first.x);
}

template <Coordinate T>
class DecrementalHull {
   private:
    struct Node {
        int left_bound;
        int right_bound;
        int bridge_left;
        int bridge_right;
        int left_child;
        int right_child;
    };

    std::vector<LayerPoint<T>> points;
    std::vector<Node> nodes;
    int root;

    bool is_leaf(int node) const {
        return nodes[node].left_child == -1 && nodes[node].right_child == -1;
    }

    void pull(int node) {
        int left = nodes[node].left_child;
        int right = nodes[node].right_child;
        assert(left != -1 && right != -1);
        using Wide = wide_type<T>;
        const Wide split_y = points[nodes[right].left_bound].y;

        while (!is_leaf(left) || !is_leaf(right)) {
            const int a = nodes[left].bridge_left;
            const int b = nodes[left].bridge_right;
            const int c = nodes[right].bridge_left;
            const int d = nodes[right].bridge_right;

            if (
                a != b &&
                sign<T>(layer_cross<T>(points[a], points[b], points[c])) > 0
            ) {
                left = nodes[left].left_child;
            } else if (
                c != d &&
                sign<T>(layer_cross<T>(points[b], points[c], points[d])) > 0
            ) {
                right = nodes[right].right_child;
            } else if (a == b) {
                right = nodes[right].left_child;
            } else if (c == d) {
                left = nodes[left].right_child;
            } else {
                const Wide first =
                    layer_cross<T>(points[a], points[b], points[c]);
                const Wide second =
                    layer_cross<T>(points[b], points[a], points[d]);
                const Wide sum = first + second;
                assert(sign<T>(sum) >= 0);
                const Wide comparison =
                    first * points[d].y + second * points[c].y - split_y * sum;
                if (sign<T>(sum) == 0 || sign<T>(comparison) < 0) {
                    left = nodes[left].right_child;
                } else {
                    right = nodes[right].left_child;
                }
            }
        }
        nodes[node].bridge_left = nodes[left].left_bound;
        nodes[node].bridge_right = nodes[right].left_bound;
    }

    void build(int node, int left, int right) {
        nodes[node].left_bound = left;
        nodes[node].right_bound = right;
        if (right - left == 1) {
            nodes[node].bridge_left = left;
            nodes[node].bridge_right = left;
            nodes[node].left_child = -1;
            nodes[node].right_child = -1;
            return;
        }

        const int middle = (left + right) / 2;
        nodes[node].left_child = node + 1;
        nodes[node].right_child = node + 2 * (middle - left);
        build(nodes[node].left_child, left, middle);
        build(nodes[node].right_child, middle, right);
        pull(node);
    }

    int erase(int node, int position) {
        if (
            position < nodes[node].left_bound ||
            nodes[node].right_bound <= position
        ) {
            return node;
        }
        if (nodes[node].right_bound - nodes[node].left_bound == 1) return -1;

        nodes[node].left_child = erase(nodes[node].left_child, position);
        nodes[node].right_child = erase(nodes[node].right_child, position);
        if (nodes[node].left_child == -1) return nodes[node].right_child;
        if (nodes[node].right_child == -1) return nodes[node].left_child;
        pull(node);
        return node;
    }

    void collect(
        int node,
        int left,
        int right,
        std::vector<int>& result
    ) const {
        if (is_leaf(node)) {
            result.push_back(nodes[node].left_bound);
        } else if (right <= nodes[node].bridge_left) {
            collect(nodes[node].left_child, left, right, result);
        } else if (nodes[node].bridge_right <= left) {
            collect(nodes[node].right_child, left, right, result);
        } else {
            assert(
                left <= nodes[node].bridge_left &&
                nodes[node].bridge_right <= right
            );
            collect(
                nodes[node].left_child,
                left,
                nodes[node].bridge_left,
                result
            );
            collect(
                nodes[node].right_child,
                nodes[node].bridge_right,
                right,
                result
            );
        }
    }

   public:
    explicit DecrementalHull(std::vector<LayerPoint<T>> ordered_points)
        : points(std::move(ordered_points)),
          nodes(2 * points.size()),
          root(points.empty() ? -1 : 0) {
        if (!points.empty()) build(0, 0, int(points.size()));
    }

    std::vector<int> hull() const {
        std::vector<int> result;
        if (root != -1) collect(root, 0, int(points.size()) - 1, result);
        return result;
    }

    void erase(int position) {
        assert(root != -1);
        assert(0 <= position && position < int(points.size()));
        root = erase(root, position);
    }
};

}  // namespace convex_layers_detail

template <Coordinate T>
std::vector<int> convex_layers(const std::vector<Point<T>>& points) {
    const int n = int(points.size());
    if (n == 0) return {};

    struct IndexedPoint {
        Point<T> point;
        int original_index;
    };
    std::vector<IndexedPoint> indexed;
    indexed.reserve(n);
    for (int index = 0; index < n; index++) {
        indexed.push_back(IndexedPoint{points[index], index});
    }
    std::sort(
        indexed.begin(),
        indexed.end(),
        [](const IndexedPoint& first, const IndexedPoint& second) {
            if (first.point.y != second.point.y) {
                return first.point.y < second.point.y;
            }
            if (first.point.x != second.point.x) {
                return first.point.x < second.point.x;
            }
            return first.original_index < second.original_index;
        }
    );

    std::vector<Point<T>> ordered;
    std::vector<int> position(n);
    ordered.reserve(n);
    for (const IndexedPoint& item : indexed) {
        if (ordered.empty() || !(ordered.back() == item.point)) {
            ordered.push_back(item.point);
        }
        position[item.original_index] = int(ordered.size()) - 1;
    }

    using LayerPoint = convex_layers_detail::LayerPoint<T>;
    using Wide = wide_type<T>;
    std::vector<LayerPoint> left_points;
    left_points.reserve(ordered.size());
    for (const Point<T>& point : ordered) {
        left_points.push_back(LayerPoint{Wide(point.x), Wide(point.y)});
    }
    convex_layers_detail::DecrementalHull<T> left_hull(
        std::move(left_points)
    );

    std::vector<LayerPoint> reversed;
    reversed.reserve(ordered.size());
    for (auto iterator = ordered.rbegin(); iterator != ordered.rend(); ++iterator) {
        reversed.push_back(LayerPoint{-Wide(iterator->x), -Wide(iterator->y)});
    }
    convex_layers_detail::DecrementalHull<T> right_hull(std::move(reversed));

    const int distinct_count = int(ordered.size());
    std::vector<int> layer_by_position(distinct_count, 0);
    std::vector<int> selected_in_layer(distinct_count, 0);
    int remaining = distinct_count;
    for (int layer = 1; remaining > 0; layer++) {
        std::vector<int> boundary;
        auto add_boundary = [&](int ordered_position) {
            if (selected_in_layer[ordered_position] == layer) return;
            selected_in_layer[ordered_position] = layer;
            boundary.push_back(ordered_position);
        };
        for (int ordered_position : left_hull.hull()) {
            add_boundary(ordered_position);
        }
        for (int reversed_position : right_hull.hull()) {
            add_boundary(distinct_count - 1 - reversed_position);
        }

        assert(!boundary.empty());
        for (int ordered_position : boundary) {
            layer_by_position[ordered_position] = layer;
            left_hull.erase(ordered_position);
            right_hull.erase(distinct_count - 1 - ordered_position);
            remaining--;
        }
    }

    std::vector<int> result(n);
    for (int index = 0; index < n; index++) {
        result[index] = layer_by_position[position[index]];
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CONVEX_LAYERS_HPP
