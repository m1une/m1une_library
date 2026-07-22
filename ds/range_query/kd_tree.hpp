#ifndef M1UNE_DS_RANGE_QUERY_KD_TREE_HPP
#define M1UNE_DS_RANGE_QUERY_KD_TREE_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Static orthogonal range and nearest-neighbor queries in K dimensions.
template <class T, std::size_t K>
class KdTree {
    static_assert(K > 0);
    static_assert(std::is_arithmetic_v<T>);
    static_assert(!std::is_same_v<std::remove_cv_t<T>, bool>);

   public:
    using coordinate_type = T;
    using point_type = std::array<T, K>;
    using distance_type =
        std::conditional_t<std::is_integral_v<T>, __int128_t, long double>;
    static constexpr std::size_t dimension = K;

    struct Neighbor {
        int index;
        distance_type distance_squared;

        friend bool operator==(const Neighbor&, const Neighbor&) = default;
    };

   private:
    struct Node {
        point_type minimum;
        point_type maximum;
        int point_index = -1;
        int left = -1;
        int right = -1;
        int subtree_size = 1;
    };

    std::vector<point_type> _points;
    std::vector<Node> _nodes;
    int _root = -1;
    int _node_count = 0;

    static distance_type squared_distance(
        const point_type& first,
        const point_type& second
    ) {
        distance_type result = 0;
        for (std::size_t axis = 0; axis < K; axis++) {
            distance_type difference =
                distance_type(first[axis]) - distance_type(second[axis]);
            result += difference * difference;
        }
        return result;
    }

    distance_type box_distance(int node, const point_type& point) const {
        distance_type result = 0;
        for (std::size_t axis = 0; axis < K; axis++) {
            distance_type difference = 0;
            if (point[axis] < _nodes[node].minimum[axis]) {
                difference = distance_type(_nodes[node].minimum[axis])
                    - distance_type(point[axis]);
            } else if (_nodes[node].maximum[axis] < point[axis]) {
                difference = distance_type(point[axis])
                    - distance_type(_nodes[node].maximum[axis]);
            }
            result += difference * difference;
        }
        return result;
    }

    int build_node(
        std::vector<int>& order,
        int left,
        int right
    ) {
        if (left == right) return -1;

        point_type minimum = _points[order[left]];
        point_type maximum = minimum;
        for (int position = left + 1; position < right; position++) {
            const point_type& point = _points[order[position]];
            for (std::size_t axis = 0; axis < K; axis++) {
                if (point[axis] < minimum[axis]) minimum[axis] = point[axis];
                if (maximum[axis] < point[axis]) maximum[axis] = point[axis];
            }
        }

        std::size_t split_axis = 0;
        distance_type maximum_extent =
            distance_type(maximum[0]) - distance_type(minimum[0]);
        for (std::size_t axis = 1; axis < K; axis++) {
            distance_type extent =
                distance_type(maximum[axis]) - distance_type(minimum[axis]);
            if (maximum_extent < extent) {
                maximum_extent = extent;
                split_axis = axis;
            }
        }

        int middle = (left + right) / 2;
        std::nth_element(
            order.begin() + left,
            order.begin() + middle,
            order.begin() + right,
            [&](int first, int second) {
                if (_points[first][split_axis]
                    < _points[second][split_axis]) return true;
                if (_points[second][split_axis]
                    < _points[first][split_axis]) return false;
                return first < second;
            }
        );

        int node = _node_count++;
        _nodes[node].point_index = order[middle];
        _nodes[node].minimum = minimum;
        _nodes[node].maximum = maximum;
        _nodes[node].left = build_node(order, left, middle);
        _nodes[node].right = build_node(order, middle + 1, right);
        _nodes[node].subtree_size = 1;
        if (_nodes[node].left != -1) {
            _nodes[node].subtree_size +=
                _nodes[_nodes[node].left].subtree_size;
        }
        if (_nodes[node].right != -1) {
            _nodes[node].subtree_size +=
                _nodes[_nodes[node].right].subtree_size;
        }
        return node;
    }

    static bool contains(
        const point_type& point,
        const point_type& lower,
        const point_type& upper
    ) {
        for (std::size_t axis = 0; axis < K; axis++) {
            if (point[axis] < lower[axis] || !(point[axis] < upper[axis])) {
                return false;
            }
        }
        return true;
    }

    bool disjoint(
        int node,
        const point_type& lower,
        const point_type& upper
    ) const {
        for (std::size_t axis = 0; axis < K; axis++) {
            if (_nodes[node].maximum[axis] < lower[axis]
                || !(_nodes[node].minimum[axis] < upper[axis])) {
                return true;
            }
        }
        return false;
    }

    bool covered(
        int node,
        const point_type& lower,
        const point_type& upper
    ) const {
        for (std::size_t axis = 0; axis < K; axis++) {
            if (_nodes[node].minimum[axis] < lower[axis]
                || !(_nodes[node].maximum[axis] < upper[axis])) {
                return false;
            }
        }
        return true;
    }

    void collect_subtree(int node, std::vector<int>& result) const {
        if (node == -1) return;
        result.push_back(_nodes[node].point_index);
        collect_subtree(_nodes[node].left, result);
        collect_subtree(_nodes[node].right, result);
    }

    void range_search_node(
        int node,
        const point_type& lower,
        const point_type& upper,
        std::vector<int>& result
    ) const {
        if (node == -1 || disjoint(node, lower, upper)) return;
        if (covered(node, lower, upper)) {
            collect_subtree(node, result);
            return;
        }
        int point_index = _nodes[node].point_index;
        if (contains(_points[point_index], lower, upper)) {
            result.push_back(point_index);
        }
        range_search_node(_nodes[node].left, lower, upper, result);
        range_search_node(_nodes[node].right, lower, upper, result);
    }

    int count_node(
        int node,
        const point_type& lower,
        const point_type& upper
    ) const {
        if (node == -1 || disjoint(node, lower, upper)) return 0;
        if (covered(node, lower, upper)) return _nodes[node].subtree_size;
        int result = int(contains(
            _points[_nodes[node].point_index],
            lower,
            upper
        ));
        result += count_node(_nodes[node].left, lower, upper);
        result += count_node(_nodes[node].right, lower, upper);
        return result;
    }

    static bool better(const Neighbor& first, const Neighbor& second) {
        if (first.distance_squared != second.distance_squared) {
            return first.distance_squared < second.distance_squared;
        }
        return first.index < second.index;
    }

    void nearest_node(
        int node,
        const point_type& query,
        std::optional<Neighbor>& best
    ) const {
        if (node == -1) return;
        distance_type bound = box_distance(node, query);
        if (best && best->distance_squared < bound) return;

        int point_index = _nodes[node].point_index;
        Neighbor candidate{
            point_index,
            squared_distance(_points[point_index], query)
        };
        if (!best || better(candidate, *best)) best = candidate;

        int first = _nodes[node].left;
        int second = _nodes[node].right;
        if (first != -1 && second != -1
            && box_distance(second, query) < box_distance(first, query)) {
            std::swap(first, second);
        }
        nearest_node(first, query, best);
        nearest_node(second, query, best);
    }

    using HeapEntry = std::pair<distance_type, int>;

    void k_nearest_node(
        int node,
        const point_type& query,
        int k,
        std::priority_queue<HeapEntry>& heap
    ) const {
        if (node == -1) return;
        distance_type bound = box_distance(node, query);
        if (int(heap.size()) == k && heap.top().first < bound) return;

        int point_index = _nodes[node].point_index;
        HeapEntry candidate = {
            squared_distance(_points[point_index], query),
            point_index
        };
        if (int(heap.size()) < k) {
            heap.push(candidate);
        } else if (candidate < heap.top()) {
            heap.pop();
            heap.push(candidate);
        }

        int first = _nodes[node].left;
        int second = _nodes[node].right;
        if (first != -1 && second != -1
            && box_distance(second, query) < box_distance(first, query)) {
            std::swap(first, second);
        }
        k_nearest_node(first, query, k, heap);
        k_nearest_node(second, query, k, heap);
    }

    static void assert_valid_box(
        const point_type& lower,
        const point_type& upper
    ) {
        for (std::size_t axis = 0; axis < K; axis++) {
            assert(!(upper[axis] < lower[axis]));
        }
    }

   public:
    KdTree() = default;

    explicit KdTree(const std::vector<point_type>& points) {
        build(points);
    }

    void build(const std::vector<point_type>& points) {
        assert(points.size()
            <= std::size_t(std::numeric_limits<int>::max()));
        _points = points;
        _nodes.clear();
        _nodes.resize(points.size());
        _root = -1;
        _node_count = 0;
        std::vector<int> order(points.size());
        for (int index = 0; index < int(points.size()); index++) {
            order[index] = index;
        }
        _root = build_node(order, 0, int(order.size()));
    }

    int size() const {
        return int(_points.size());
    }

    bool empty() const {
        return _points.empty();
    }

    const point_type& get(int index) const {
        assert(0 <= index && index < size());
        return _points[index];
    }

    const point_type& operator[](int index) const {
        return get(index);
    }

    std::vector<int> range_search(
        const point_type& lower,
        const point_type& upper
    ) const {
        assert_valid_box(lower, upper);
        std::vector<int> result;
        range_search_node(_root, lower, upper, result);
        return result;
    }

    int count(
        const point_type& lower,
        const point_type& upper
    ) const {
        assert_valid_box(lower, upper);
        return count_node(_root, lower, upper);
    }

    std::optional<Neighbor> nearest(const point_type& query) const {
        std::optional<Neighbor> result;
        nearest_node(_root, query, result);
        return result;
    }

    std::vector<Neighbor> k_nearest(
        const point_type& query,
        int k
    ) const {
        assert(0 <= k && k <= size());
        if (k == 0) return {};
        std::priority_queue<HeapEntry> heap;
        k_nearest_node(_root, query, k, heap);
        std::vector<Neighbor> result;
        result.reserve(k);
        while (!heap.empty()) {
            result.push_back(Neighbor{heap.top().second, heap.top().first});
            heap.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_KD_TREE_HPP
