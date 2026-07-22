---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/kd_tree.test.cpp
    title: verify/ds/range_query/kd_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/kd_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <optional>\n#include <queue>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Static orthogonal\
    \ range and nearest-neighbor queries in K dimensions.\ntemplate <class T, std::size_t\
    \ K>\nclass KdTree {\n    static_assert(K > 0);\n    static_assert(std::is_arithmetic_v<T>);\n\
    \    static_assert(!std::is_same_v<std::remove_cv_t<T>, bool>);\n\n   public:\n\
    \    using coordinate_type = T;\n    using point_type = std::array<T, K>;\n  \
    \  using distance_type =\n        std::conditional_t<std::is_integral_v<T>, __int128_t,\
    \ long double>;\n    static constexpr std::size_t dimension = K;\n\n    struct\
    \ Neighbor {\n        int index;\n        distance_type distance_squared;\n\n\
    \        friend bool operator==(const Neighbor&, const Neighbor&) = default;\n\
    \    };\n\n   private:\n    struct Node {\n        point_type minimum;\n     \
    \   point_type maximum;\n        int point_index = -1;\n        int left = -1;\n\
    \        int right = -1;\n        int subtree_size = 1;\n    };\n\n    std::vector<point_type>\
    \ _points;\n    std::vector<Node> _nodes;\n    int _root = -1;\n    int _node_count\
    \ = 0;\n\n    static distance_type squared_distance(\n        const point_type&\
    \ first,\n        const point_type& second\n    ) {\n        distance_type result\
    \ = 0;\n        for (std::size_t axis = 0; axis < K; axis++) {\n            distance_type\
    \ difference =\n                distance_type(first[axis]) - distance_type(second[axis]);\n\
    \            result += difference * difference;\n        }\n        return result;\n\
    \    }\n\n    distance_type box_distance(int node, const point_type& point) const\
    \ {\n        distance_type result = 0;\n        for (std::size_t axis = 0; axis\
    \ < K; axis++) {\n            distance_type difference = 0;\n            if (point[axis]\
    \ < _nodes[node].minimum[axis]) {\n                difference = distance_type(_nodes[node].minimum[axis])\n\
    \                    - distance_type(point[axis]);\n            } else if (_nodes[node].maximum[axis]\
    \ < point[axis]) {\n                difference = distance_type(point[axis])\n\
    \                    - distance_type(_nodes[node].maximum[axis]);\n          \
    \  }\n            result += difference * difference;\n        }\n        return\
    \ result;\n    }\n\n    int build_node(\n        std::vector<int>& order,\n  \
    \      int left,\n        int right\n    ) {\n        if (left == right) return\
    \ -1;\n\n        point_type minimum = _points[order[left]];\n        point_type\
    \ maximum = minimum;\n        for (int position = left + 1; position < right;\
    \ position++) {\n            const point_type& point = _points[order[position]];\n\
    \            for (std::size_t axis = 0; axis < K; axis++) {\n                if\
    \ (point[axis] < minimum[axis]) minimum[axis] = point[axis];\n               \
    \ if (maximum[axis] < point[axis]) maximum[axis] = point[axis];\n            }\n\
    \        }\n\n        std::size_t split_axis = 0;\n        distance_type maximum_extent\
    \ =\n            distance_type(maximum[0]) - distance_type(minimum[0]);\n    \
    \    for (std::size_t axis = 1; axis < K; axis++) {\n            distance_type\
    \ extent =\n                distance_type(maximum[axis]) - distance_type(minimum[axis]);\n\
    \            if (maximum_extent < extent) {\n                maximum_extent =\
    \ extent;\n                split_axis = axis;\n            }\n        }\n\n  \
    \      int middle = (left + right) / 2;\n        std::nth_element(\n         \
    \   order.begin() + left,\n            order.begin() + middle,\n            order.begin()\
    \ + right,\n            [&](int first, int second) {\n                if (_points[first][split_axis]\n\
    \                    < _points[second][split_axis]) return true;\n           \
    \     if (_points[second][split_axis]\n                    < _points[first][split_axis])\
    \ return false;\n                return first < second;\n            }\n     \
    \   );\n\n        int node = _node_count++;\n        _nodes[node].point_index\
    \ = order[middle];\n        _nodes[node].minimum = minimum;\n        _nodes[node].maximum\
    \ = maximum;\n        _nodes[node].left = build_node(order, left, middle);\n \
    \       _nodes[node].right = build_node(order, middle + 1, right);\n        _nodes[node].subtree_size\
    \ = 1;\n        if (_nodes[node].left != -1) {\n            _nodes[node].subtree_size\
    \ +=\n                _nodes[_nodes[node].left].subtree_size;\n        }\n   \
    \     if (_nodes[node].right != -1) {\n            _nodes[node].subtree_size +=\n\
    \                _nodes[_nodes[node].right].subtree_size;\n        }\n       \
    \ return node;\n    }\n\n    static bool contains(\n        const point_type&\
    \ point,\n        const point_type& lower,\n        const point_type& upper\n\
    \    ) {\n        for (std::size_t axis = 0; axis < K; axis++) {\n           \
    \ if (point[axis] < lower[axis] || !(point[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    bool disjoint(\n        int node,\n        const point_type& lower,\n  \
    \      const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].maximum[axis] < lower[axis]\n\
    \                || !(_nodes[node].minimum[axis] < upper[axis])) {\n         \
    \       return true;\n            }\n        }\n        return false;\n    }\n\
    \n    bool covered(\n        int node,\n        const point_type& lower,\n   \
    \     const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].minimum[axis] < lower[axis]\n\
    \                || !(_nodes[node].maximum[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    void collect_subtree(int node, std::vector<int>& result) const {\n     \
    \   if (node == -1) return;\n        result.push_back(_nodes[node].point_index);\n\
    \        collect_subtree(_nodes[node].left, result);\n        collect_subtree(_nodes[node].right,\
    \ result);\n    }\n\n    void range_search_node(\n        int node,\n        const\
    \ point_type& lower,\n        const point_type& upper,\n        std::vector<int>&\
    \ result\n    ) const {\n        if (node == -1 || disjoint(node, lower, upper))\
    \ return;\n        if (covered(node, lower, upper)) {\n            collect_subtree(node,\
    \ result);\n            return;\n        }\n        int point_index = _nodes[node].point_index;\n\
    \        if (contains(_points[point_index], lower, upper)) {\n            result.push_back(point_index);\n\
    \        }\n        range_search_node(_nodes[node].left, lower, upper, result);\n\
    \        range_search_node(_nodes[node].right, lower, upper, result);\n    }\n\
    \n    int count_node(\n        int node,\n        const point_type& lower,\n \
    \       const point_type& upper\n    ) const {\n        if (node == -1 || disjoint(node,\
    \ lower, upper)) return 0;\n        if (covered(node, lower, upper)) return _nodes[node].subtree_size;\n\
    \        int result = int(contains(\n            _points[_nodes[node].point_index],\n\
    \            lower,\n            upper\n        ));\n        result += count_node(_nodes[node].left,\
    \ lower, upper);\n        result += count_node(_nodes[node].right, lower, upper);\n\
    \        return result;\n    }\n\n    static bool better(const Neighbor& first,\
    \ const Neighbor& second) {\n        if (first.distance_squared != second.distance_squared)\
    \ {\n            return first.distance_squared < second.distance_squared;\n  \
    \      }\n        return first.index < second.index;\n    }\n\n    void nearest_node(\n\
    \        int node,\n        const point_type& query,\n        std::optional<Neighbor>&\
    \ best\n    ) const {\n        if (node == -1) return;\n        distance_type\
    \ bound = box_distance(node, query);\n        if (best && best->distance_squared\
    \ < bound) return;\n\n        int point_index = _nodes[node].point_index;\n  \
    \      Neighbor candidate{\n            point_index,\n            squared_distance(_points[point_index],\
    \ query)\n        };\n        if (!best || better(candidate, *best)) best = candidate;\n\
    \n        int first = _nodes[node].left;\n        int second = _nodes[node].right;\n\
    \        if (first != -1 && second != -1\n            && box_distance(second,\
    \ query) < box_distance(first, query)) {\n            std::swap(first, second);\n\
    \        }\n        nearest_node(first, query, best);\n        nearest_node(second,\
    \ query, best);\n    }\n\n    using HeapEntry = std::pair<distance_type, int>;\n\
    \n    void k_nearest_node(\n        int node,\n        const point_type& query,\n\
    \        int k,\n        std::priority_queue<HeapEntry>& heap\n    ) const {\n\
    \        if (node == -1) return;\n        distance_type bound = box_distance(node,\
    \ query);\n        if (int(heap.size()) == k && heap.top().first < bound) return;\n\
    \n        int point_index = _nodes[node].point_index;\n        HeapEntry candidate\
    \ = {\n            squared_distance(_points[point_index], query),\n          \
    \  point_index\n        };\n        if (int(heap.size()) < k) {\n            heap.push(candidate);\n\
    \        } else if (candidate < heap.top()) {\n            heap.pop();\n     \
    \       heap.push(candidate);\n        }\n\n        int first = _nodes[node].left;\n\
    \        int second = _nodes[node].right;\n        if (first != -1 && second !=\
    \ -1\n            && box_distance(second, query) < box_distance(first, query))\
    \ {\n            std::swap(first, second);\n        }\n        k_nearest_node(first,\
    \ query, k, heap);\n        k_nearest_node(second, query, k, heap);\n    }\n\n\
    \    static void assert_valid_box(\n        const point_type& lower,\n       \
    \ const point_type& upper\n    ) {\n        for (std::size_t axis = 0; axis <\
    \ K; axis++) {\n            assert(!(upper[axis] < lower[axis]));\n        }\n\
    \    }\n\n   public:\n    KdTree() = default;\n\n    explicit KdTree(const std::vector<point_type>&\
    \ points) {\n        build(points);\n    }\n\n    void build(const std::vector<point_type>&\
    \ points) {\n        assert(points.size()\n            <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        _points = points;\n        _nodes.clear();\n        _nodes.resize(points.size());\n\
    \        _root = -1;\n        _node_count = 0;\n        std::vector<int> order(points.size());\n\
    \        for (int index = 0; index < int(points.size()); index++) {\n        \
    \    order[index] = index;\n        }\n        _root = build_node(order, 0, int(order.size()));\n\
    \    }\n\n    int size() const {\n        return int(_points.size());\n    }\n\
    \n    bool empty() const {\n        return _points.empty();\n    }\n\n    const\
    \ point_type& get(int index) const {\n        assert(0 <= index && index < size());\n\
    \        return _points[index];\n    }\n\n    const point_type& operator[](int\
    \ index) const {\n        return get(index);\n    }\n\n    std::vector<int> range_search(\n\
    \        const point_type& lower,\n        const point_type& upper\n    ) const\
    \ {\n        assert_valid_box(lower, upper);\n        std::vector<int> result;\n\
    \        range_search_node(_root, lower, upper, result);\n        return result;\n\
    \    }\n\n    int count(\n        const point_type& lower,\n        const point_type&\
    \ upper\n    ) const {\n        assert_valid_box(lower, upper);\n        return\
    \ count_node(_root, lower, upper);\n    }\n\n    std::optional<Neighbor> nearest(const\
    \ point_type& query) const {\n        std::optional<Neighbor> result;\n      \
    \  nearest_node(_root, query, result);\n        return result;\n    }\n\n    std::vector<Neighbor>\
    \ k_nearest(\n        const point_type& query,\n        int k\n    ) const {\n\
    \        assert(0 <= k && k <= size());\n        if (k == 0) return {};\n    \
    \    std::priority_queue<HeapEntry> heap;\n        k_nearest_node(_root, query,\
    \ k, heap);\n        std::vector<Neighbor> result;\n        result.reserve(k);\n\
    \        while (!heap.empty()) {\n            result.push_back(Neighbor{heap.top().second,\
    \ heap.top().first});\n            heap.pop();\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_KD_TREE_HPP\n#define M1UNE_DS_RANGE_QUERY_KD_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <optional>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    // Static orthogonal range and nearest-neighbor queries in K dimensions.\ntemplate\
    \ <class T, std::size_t K>\nclass KdTree {\n    static_assert(K > 0);\n    static_assert(std::is_arithmetic_v<T>);\n\
    \    static_assert(!std::is_same_v<std::remove_cv_t<T>, bool>);\n\n   public:\n\
    \    using coordinate_type = T;\n    using point_type = std::array<T, K>;\n  \
    \  using distance_type =\n        std::conditional_t<std::is_integral_v<T>, __int128_t,\
    \ long double>;\n    static constexpr std::size_t dimension = K;\n\n    struct\
    \ Neighbor {\n        int index;\n        distance_type distance_squared;\n\n\
    \        friend bool operator==(const Neighbor&, const Neighbor&) = default;\n\
    \    };\n\n   private:\n    struct Node {\n        point_type minimum;\n     \
    \   point_type maximum;\n        int point_index = -1;\n        int left = -1;\n\
    \        int right = -1;\n        int subtree_size = 1;\n    };\n\n    std::vector<point_type>\
    \ _points;\n    std::vector<Node> _nodes;\n    int _root = -1;\n    int _node_count\
    \ = 0;\n\n    static distance_type squared_distance(\n        const point_type&\
    \ first,\n        const point_type& second\n    ) {\n        distance_type result\
    \ = 0;\n        for (std::size_t axis = 0; axis < K; axis++) {\n            distance_type\
    \ difference =\n                distance_type(first[axis]) - distance_type(second[axis]);\n\
    \            result += difference * difference;\n        }\n        return result;\n\
    \    }\n\n    distance_type box_distance(int node, const point_type& point) const\
    \ {\n        distance_type result = 0;\n        for (std::size_t axis = 0; axis\
    \ < K; axis++) {\n            distance_type difference = 0;\n            if (point[axis]\
    \ < _nodes[node].minimum[axis]) {\n                difference = distance_type(_nodes[node].minimum[axis])\n\
    \                    - distance_type(point[axis]);\n            } else if (_nodes[node].maximum[axis]\
    \ < point[axis]) {\n                difference = distance_type(point[axis])\n\
    \                    - distance_type(_nodes[node].maximum[axis]);\n          \
    \  }\n            result += difference * difference;\n        }\n        return\
    \ result;\n    }\n\n    int build_node(\n        std::vector<int>& order,\n  \
    \      int left,\n        int right\n    ) {\n        if (left == right) return\
    \ -1;\n\n        point_type minimum = _points[order[left]];\n        point_type\
    \ maximum = minimum;\n        for (int position = left + 1; position < right;\
    \ position++) {\n            const point_type& point = _points[order[position]];\n\
    \            for (std::size_t axis = 0; axis < K; axis++) {\n                if\
    \ (point[axis] < minimum[axis]) minimum[axis] = point[axis];\n               \
    \ if (maximum[axis] < point[axis]) maximum[axis] = point[axis];\n            }\n\
    \        }\n\n        std::size_t split_axis = 0;\n        distance_type maximum_extent\
    \ =\n            distance_type(maximum[0]) - distance_type(minimum[0]);\n    \
    \    for (std::size_t axis = 1; axis < K; axis++) {\n            distance_type\
    \ extent =\n                distance_type(maximum[axis]) - distance_type(minimum[axis]);\n\
    \            if (maximum_extent < extent) {\n                maximum_extent =\
    \ extent;\n                split_axis = axis;\n            }\n        }\n\n  \
    \      int middle = (left + right) / 2;\n        std::nth_element(\n         \
    \   order.begin() + left,\n            order.begin() + middle,\n            order.begin()\
    \ + right,\n            [&](int first, int second) {\n                if (_points[first][split_axis]\n\
    \                    < _points[second][split_axis]) return true;\n           \
    \     if (_points[second][split_axis]\n                    < _points[first][split_axis])\
    \ return false;\n                return first < second;\n            }\n     \
    \   );\n\n        int node = _node_count++;\n        _nodes[node].point_index\
    \ = order[middle];\n        _nodes[node].minimum = minimum;\n        _nodes[node].maximum\
    \ = maximum;\n        _nodes[node].left = build_node(order, left, middle);\n \
    \       _nodes[node].right = build_node(order, middle + 1, right);\n        _nodes[node].subtree_size\
    \ = 1;\n        if (_nodes[node].left != -1) {\n            _nodes[node].subtree_size\
    \ +=\n                _nodes[_nodes[node].left].subtree_size;\n        }\n   \
    \     if (_nodes[node].right != -1) {\n            _nodes[node].subtree_size +=\n\
    \                _nodes[_nodes[node].right].subtree_size;\n        }\n       \
    \ return node;\n    }\n\n    static bool contains(\n        const point_type&\
    \ point,\n        const point_type& lower,\n        const point_type& upper\n\
    \    ) {\n        for (std::size_t axis = 0; axis < K; axis++) {\n           \
    \ if (point[axis] < lower[axis] || !(point[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    bool disjoint(\n        int node,\n        const point_type& lower,\n  \
    \      const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].maximum[axis] < lower[axis]\n\
    \                || !(_nodes[node].minimum[axis] < upper[axis])) {\n         \
    \       return true;\n            }\n        }\n        return false;\n    }\n\
    \n    bool covered(\n        int node,\n        const point_type& lower,\n   \
    \     const point_type& upper\n    ) const {\n        for (std::size_t axis =\
    \ 0; axis < K; axis++) {\n            if (_nodes[node].minimum[axis] < lower[axis]\n\
    \                || !(_nodes[node].maximum[axis] < upper[axis])) {\n         \
    \       return false;\n            }\n        }\n        return true;\n    }\n\
    \n    void collect_subtree(int node, std::vector<int>& result) const {\n     \
    \   if (node == -1) return;\n        result.push_back(_nodes[node].point_index);\n\
    \        collect_subtree(_nodes[node].left, result);\n        collect_subtree(_nodes[node].right,\
    \ result);\n    }\n\n    void range_search_node(\n        int node,\n        const\
    \ point_type& lower,\n        const point_type& upper,\n        std::vector<int>&\
    \ result\n    ) const {\n        if (node == -1 || disjoint(node, lower, upper))\
    \ return;\n        if (covered(node, lower, upper)) {\n            collect_subtree(node,\
    \ result);\n            return;\n        }\n        int point_index = _nodes[node].point_index;\n\
    \        if (contains(_points[point_index], lower, upper)) {\n            result.push_back(point_index);\n\
    \        }\n        range_search_node(_nodes[node].left, lower, upper, result);\n\
    \        range_search_node(_nodes[node].right, lower, upper, result);\n    }\n\
    \n    int count_node(\n        int node,\n        const point_type& lower,\n \
    \       const point_type& upper\n    ) const {\n        if (node == -1 || disjoint(node,\
    \ lower, upper)) return 0;\n        if (covered(node, lower, upper)) return _nodes[node].subtree_size;\n\
    \        int result = int(contains(\n            _points[_nodes[node].point_index],\n\
    \            lower,\n            upper\n        ));\n        result += count_node(_nodes[node].left,\
    \ lower, upper);\n        result += count_node(_nodes[node].right, lower, upper);\n\
    \        return result;\n    }\n\n    static bool better(const Neighbor& first,\
    \ const Neighbor& second) {\n        if (first.distance_squared != second.distance_squared)\
    \ {\n            return first.distance_squared < second.distance_squared;\n  \
    \      }\n        return first.index < second.index;\n    }\n\n    void nearest_node(\n\
    \        int node,\n        const point_type& query,\n        std::optional<Neighbor>&\
    \ best\n    ) const {\n        if (node == -1) return;\n        distance_type\
    \ bound = box_distance(node, query);\n        if (best && best->distance_squared\
    \ < bound) return;\n\n        int point_index = _nodes[node].point_index;\n  \
    \      Neighbor candidate{\n            point_index,\n            squared_distance(_points[point_index],\
    \ query)\n        };\n        if (!best || better(candidate, *best)) best = candidate;\n\
    \n        int first = _nodes[node].left;\n        int second = _nodes[node].right;\n\
    \        if (first != -1 && second != -1\n            && box_distance(second,\
    \ query) < box_distance(first, query)) {\n            std::swap(first, second);\n\
    \        }\n        nearest_node(first, query, best);\n        nearest_node(second,\
    \ query, best);\n    }\n\n    using HeapEntry = std::pair<distance_type, int>;\n\
    \n    void k_nearest_node(\n        int node,\n        const point_type& query,\n\
    \        int k,\n        std::priority_queue<HeapEntry>& heap\n    ) const {\n\
    \        if (node == -1) return;\n        distance_type bound = box_distance(node,\
    \ query);\n        if (int(heap.size()) == k && heap.top().first < bound) return;\n\
    \n        int point_index = _nodes[node].point_index;\n        HeapEntry candidate\
    \ = {\n            squared_distance(_points[point_index], query),\n          \
    \  point_index\n        };\n        if (int(heap.size()) < k) {\n            heap.push(candidate);\n\
    \        } else if (candidate < heap.top()) {\n            heap.pop();\n     \
    \       heap.push(candidate);\n        }\n\n        int first = _nodes[node].left;\n\
    \        int second = _nodes[node].right;\n        if (first != -1 && second !=\
    \ -1\n            && box_distance(second, query) < box_distance(first, query))\
    \ {\n            std::swap(first, second);\n        }\n        k_nearest_node(first,\
    \ query, k, heap);\n        k_nearest_node(second, query, k, heap);\n    }\n\n\
    \    static void assert_valid_box(\n        const point_type& lower,\n       \
    \ const point_type& upper\n    ) {\n        for (std::size_t axis = 0; axis <\
    \ K; axis++) {\n            assert(!(upper[axis] < lower[axis]));\n        }\n\
    \    }\n\n   public:\n    KdTree() = default;\n\n    explicit KdTree(const std::vector<point_type>&\
    \ points) {\n        build(points);\n    }\n\n    void build(const std::vector<point_type>&\
    \ points) {\n        assert(points.size()\n            <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        _points = points;\n        _nodes.clear();\n        _nodes.resize(points.size());\n\
    \        _root = -1;\n        _node_count = 0;\n        std::vector<int> order(points.size());\n\
    \        for (int index = 0; index < int(points.size()); index++) {\n        \
    \    order[index] = index;\n        }\n        _root = build_node(order, 0, int(order.size()));\n\
    \    }\n\n    int size() const {\n        return int(_points.size());\n    }\n\
    \n    bool empty() const {\n        return _points.empty();\n    }\n\n    const\
    \ point_type& get(int index) const {\n        assert(0 <= index && index < size());\n\
    \        return _points[index];\n    }\n\n    const point_type& operator[](int\
    \ index) const {\n        return get(index);\n    }\n\n    std::vector<int> range_search(\n\
    \        const point_type& lower,\n        const point_type& upper\n    ) const\
    \ {\n        assert_valid_box(lower, upper);\n        std::vector<int> result;\n\
    \        range_search_node(_root, lower, upper, result);\n        return result;\n\
    \    }\n\n    int count(\n        const point_type& lower,\n        const point_type&\
    \ upper\n    ) const {\n        assert_valid_box(lower, upper);\n        return\
    \ count_node(_root, lower, upper);\n    }\n\n    std::optional<Neighbor> nearest(const\
    \ point_type& query) const {\n        std::optional<Neighbor> result;\n      \
    \  nearest_node(_root, query, result);\n        return result;\n    }\n\n    std::vector<Neighbor>\
    \ k_nearest(\n        const point_type& query,\n        int k\n    ) const {\n\
    \        assert(0 <= k && k <= size());\n        if (k == 0) return {};\n    \
    \    std::priority_queue<HeapEntry> heap;\n        k_nearest_node(_root, query,\
    \ k, heap);\n        std::vector<Neighbor> result;\n        result.reserve(k);\n\
    \        while (!heap.empty()) {\n            result.push_back(Neighbor{heap.top().second,\
    \ heap.top().first});\n            heap.pop();\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_KD_TREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/range_query/kd_tree.hpp
  requiredBy: []
  timestamp: '2026-07-22 14:00:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/kd_tree.test.cpp
documentation_of: ds/range_query/kd_tree.hpp
layout: document
title: K-d Tree
---

## Overview

`KdTree<T, K>` stores a static set of `K`-dimensional points. It supports
orthogonal half-open range reporting and counting, nearest-neighbor queries,
and k-nearest-neighbor queries while preserving every point's original input
index.

Construction recursively selects the widest coordinate axis, places its median
at the current node, and stores a bounding box for each subtree. Duplicate
points are kept as separate entries. The structure is effective for small,
fixed dimensions; like other k-d trees, its pruning becomes less effective as
the dimension grows.

## Requirements

`K` must be positive. `T` must be an arithmetic type other than `bool`.
Floating-point coordinates and queries must be finite.

For integral `T`, squared distances use signed 128-bit arithmetic. For
floating-point `T`, they use `long double`. Every squared distance and
intermediate sum must fit in `distance_type`.

## Public Interface

```cpp
template <class T, std::size_t K>
class KdTree {
public:
    using coordinate_type = T;
    using point_type = std::array<T, K>;
    using distance_type = /* __int128_t or long double */;
    static constexpr std::size_t dimension = K;

    struct Neighbor {
        int index;
        distance_type distance_squared;

        friend bool operator==(const Neighbor&, const Neighbor&) = default;
    };
};
```

All boxes are the Cartesian product of half-open ranges
`[lower[axis], upper[axis])`. Each lower bound must not exceed its upper bound.

| Method | Description | Complexity |
| --- | --- | --- |
| `bool operator==(const Neighbor& first, const Neighbor& second)` | Compares both neighbor fields. | $O(1)$ |
| `KdTree()` | Constructs an empty tree. | $O(1)$ |
| `explicit KdTree(const std::vector<point_type>& points)` | Copies the points and builds the tree. | $O(KN\log N)$ average time, $O(KN)$ memory |
| `void build(const std::vector<point_type>& points)` | Replaces all stored points and rebuilds the tree. | $O(KN\log N)$ average time, $O(KN)$ memory |
| `int size() const` | Returns the number of stored points, including duplicates. | $O(1)$ |
| `bool empty() const` | Returns whether no points are stored. | $O(1)$ |
| `const point_type& get(int index) const` | Returns the point at its original input index. | $O(1)$ |
| `const point_type& operator[](int index) const` | Equivalent to `get(index)`. | $O(1)$ |
| `std::vector<int> range_search(const point_type& lower, const point_type& upper) const` | Returns the original indices inside the half-open box. | Typically $O(KN^{1-1/K}+A)$; $O(KN)$ worst case |
| `int count(const point_type& lower, const point_type& upper) const` | Counts points inside the half-open box. Fully covered subtrees are counted at once. | Typically $O(KN^{1-1/K})$; $O(KN)$ worst case |
| `std::optional<Neighbor> nearest(const point_type& query) const` | Returns the nearest point, or `nullopt` for an empty tree. | Typically $O(K\log N)$; $O(KN)$ worst case |
| `std::vector<Neighbor> k_nearest(const point_type& query, int k) const` | Returns the `k` nearest points for `0 <= k <= size()`. | $O(1)$ for `k = 0`; otherwise typically $O((K+\log k)(\log N+k))$ and $O(N(K+\log k))$ worst case |

Here, `A` is the number of reported points. Typical query bounds assume a
low-dimensional, reasonably distributed point set. Adversarial layouts can
force a query to visit every node.

`range_search` does not sort its result. `nearest` breaks equal-distance ties by
the smaller original index. `k_nearest` returns neighbors in ascending
`(distance_squared, index)` order. Query methods do not mutate the tree.

## Example

```cpp
#include "ds/range_query/kd_tree.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

int main() {
    using Tree = m1une::ds::KdTree<long long, 2>;
    using Point = Tree::point_type;

    std::vector<Point> points;
    Point first = {0, 0};
    Point second = {3, 1};
    Point third = {2, 4};
    points.push_back(first);
    points.push_back(second);
    points.push_back(third);

    Tree tree(points);

    Point lower = {0, 0};
    Point upper = {3, 3};
    std::vector<int> found = tree.range_search(lower, upper);
    std::sort(found.begin(), found.end());
    assert(found.size() == 1 && found[0] == 0);

    Point query = {2, 0};
    auto nearest = tree.nearest(query);
    assert(nearest.has_value());
    assert(nearest->index == 1);
    assert(nearest->distance_squared == 2);
}
```
