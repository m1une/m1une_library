---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/merge_sort_tree.test.cpp
    title: verify/ds/range_query/merge_sort_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/merge_sort_tree_sum.test.cpp
    title: verify/ds/range_query/merge_sort_tree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/merge_sort_tree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <cstddef>\n#include <iterator>\n\
    #include <limits>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\n\
    template <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 15 \"ds/range_query/merge_sort_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Static range counting, sums, and order\
    \ statistics for arbitrary ordered values.\ntemplate <class T, class Sum = T>\n\
    class MergeSortTree {\n   private:\n    struct Node {\n        std::vector<T>\
    \ values;\n        std::vector<Sum> prefix_sum;\n    };\n\n    static constexpr\
    \ bool supports_sum = requires(Sum left, Sum right, const T& value) {\n      \
    \  Sum{};\n        static_cast<Sum>(value);\n        { left + right } -> std::convertible_to<Sum>;\n\
    \        { left - right } -> std::convertible_to<Sum>;\n    };\n\n    int _n;\n\
    \    int _size;\n    std::vector<T> _values;\n    std::vector<T> _sorted_values;\n\
    \    std::vector<Node> _tree;\n    std::vector<Sum> _original_prefix_sum;\n\n\
    \    template <class Callback>\n    void visit(int left, int right, Callback&&\
    \ callback) const {\n        left += _size;\n        right += _size;\n       \
    \ while (left < right) {\n            if (left & 1) callback(_tree[left++]);\n\
    \            if (right & 1) callback(_tree[--right]);\n            left >>= 1;\n\
    \            right >>= 1;\n        }\n    }\n\n    static bool equivalent(const\
    \ T& left, const T& right) {\n        return !(left < right) && !(right < left);\n\
    \    }\n\n   public:\n    MergeSortTree()\n        : _n(0),\n          _size(1),\n\
    \          _tree(2) {\n        if constexpr (supports_sum) _original_prefix_sum.push_back(Sum{});\n\
    \    }\n\n    explicit MergeSortTree(const std::vector<T>& values)\n        :\
    \ _n(0),\n          _size(1) {\n        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        _n = int(values.size());\n        _size = m1une::math::bit_ceil(std::max(1,\
    \ _n));\n        _values = values;\n        _sorted_values = values;\n       \
    \ std::sort(_sorted_values.begin(), _sorted_values.end());\n        _sorted_values.erase(\n\
    \            std::unique(\n                _sorted_values.begin(),\n         \
    \       _sorted_values.end(),\n                [](const T& left, const T& right)\
    \ {\n                    return equivalent(left, right);\n                }\n\
    \            ),\n            _sorted_values.end()\n        );\n\n        _tree.resize(2\
    \ * _size);\n        for (int index = 0; index < _n; index++) {\n            _tree[_size\
    \ + index].values.push_back(values[index]);\n        }\n        for (int node\
    \ = _size - 1; node >= 1; node--) {\n            const auto& left = _tree[2 *\
    \ node].values;\n            const auto& right = _tree[2 * node + 1].values;\n\
    \            _tree[node].values.reserve(left.size() + right.size());\n       \
    \     std::merge(\n                left.begin(),\n                left.end(),\n\
    \                right.begin(),\n                right.end(),\n              \
    \  std::back_inserter(_tree[node].values)\n            );\n        }\n\n     \
    \   if constexpr (supports_sum) {\n            _original_prefix_sum.reserve(_n\
    \ + 1);\n            _original_prefix_sum.push_back(Sum{});\n            for (const\
    \ T& value : values) {\n                _original_prefix_sum.push_back(\n    \
    \                _original_prefix_sum.back() + static_cast<Sum>(value)\n     \
    \           );\n            }\n            for (Node& node : _tree) {\n      \
    \          if (node.values.empty()) continue;\n                node.prefix_sum.reserve(node.values.size()\
    \ + 1);\n                node.prefix_sum.push_back(Sum{});\n                for\
    \ (const T& value : node.values) {\n                    node.prefix_sum.push_back(\n\
    \                        node.prefix_sum.back() + static_cast<Sum>(value)\n  \
    \                  );\n                }\n            }\n        }\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    const T& get(int position) const {\n  \
    \      assert(0 <= position && position < _n);\n        return _values[position];\n\
    \    }\n\n    const T& operator[](int position) const {\n        return get(position);\n\
    \    }\n\n    int count_less(int left, int right, const T& upper) const {\n  \
    \      assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::lower_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count_less_equal(int left, int right, const T& upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::upper_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count(int left, int right, const T& value) const {\n       \
    \ assert(0 <= left && left <= right && right <= _n);\n        int result = 0;\n\
    \        visit(left, right, [&](const Node& node) {\n            const auto& values\
    \ = node.values;\n            auto range = std::equal_range(values.begin(), values.end(),\
    \ value);\n            result += int(range.second - range.first);\n        });\n\
    \        return result;\n    }\n\n    int count(int left, int right, const T&\
    \ lower, const T& upper) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        if (!(lower < upper)) return 0;\n        int result =\
    \ 0;\n        visit(left, right, [&](const Node& node) {\n            const auto&\
    \ values = node.values;\n            auto first = std::lower_bound(values.begin(),\
    \ values.end(), lower);\n            auto last = std::lower_bound(values.begin(),\
    \ values.end(), upper);\n            result += int(last - first);\n        });\n\
    \        return result;\n    }\n\n    Sum range_sum(int left, int right) const\
    \ requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        return _original_prefix_sum[right] - _original_prefix_sum[left];\n\
    \    }\n\n    Sum sum_less(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum_less_equal(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::upper_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum(int left, int right, const T& value) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto range =\
    \ std::equal_range(node.values.begin(), node.values.end(), value);\n         \
    \   int first = int(range.first - node.values.begin());\n            int last\
    \ = int(range.second - node.values.begin());\n            result = result + node.prefix_sum[last]\
    \ - node.prefix_sum[first];\n        });\n        return result;\n    }\n\n  \
    \  Sum sum(int left, int right, const T& lower, const T& upper) const\n      \
    \  requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (!(lower < upper)) return Sum{};\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto first_iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), lower);\n       \
    \     auto last_iterator = std::lower_bound(node.values.begin(), node.values.end(),\
    \ upper);\n            int first = int(first_iterator - node.values.begin());\n\
    \            int last = int(last_iterator - node.values.begin());\n          \
    \  result = result + node.prefix_sum[last] - node.prefix_sum[first];\n       \
    \ });\n        return result;\n    }\n\n    T kth_smallest(int left, int right,\
    \ int k) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        assert(0 <= k && k < right - left);\n        int low = 0;\n        int\
    \ high = int(_sorted_values.size()) - 1;\n        while (low < high) {\n     \
    \       int middle = (low + high) / 2;\n            if (count_less_equal(left,\
    \ right, _sorted_values[middle]) > k) {\n                high = middle;\n    \
    \        } else {\n                low = middle + 1;\n            }\n        }\n\
    \        return _sorted_values[low];\n    }\n\n    T kth_largest(int left, int\
    \ right, int k) const {\n        assert(0 <= left && left <= right && right <=\
    \ _n);\n        assert(0 <= k && k < right - left);\n        return kth_smallest(left,\
    \ right, right - left - 1 - k);\n    }\n\n    std::optional<T> prev_value(int\
    \ left, int right, const T& upper) const {\n        assert(0 <= left && left <=\
    \ right && right <= _n);\n        std::optional<T> result;\n        visit(left,\
    \ right, [&](const Node& node) {\n            const auto& values = node.values;\n\
    \            auto iterator = std::lower_bound(values.begin(), values.end(), upper);\n\
    \            if (iterator == values.begin()) return;\n            --iterator;\n\
    \            if (!result || *result < *iterator) result = *iterator;\n       \
    \ });\n        return result;\n    }\n\n    std::optional<T> next_value(int left,\
    \ int right, const T& lower) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::optional<T> result;\n        visit(left, right,\
    \ [&](const Node& node) {\n            const auto& values = node.values;\n   \
    \         auto iterator = std::lower_bound(values.begin(), values.end(), lower);\n\
    \            if (iterator == values.end()) return;\n            if (!result ||\
    \ *iterator < *result) result = *iterator;\n        });\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP\n#define M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstddef>\n#include <iterator>\n#include <limits>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#include \"../../math/bit_ceil.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\n// Static range counting, sums, and order statistics\
    \ for arbitrary ordered values.\ntemplate <class T, class Sum = T>\nclass MergeSortTree\
    \ {\n   private:\n    struct Node {\n        std::vector<T> values;\n        std::vector<Sum>\
    \ prefix_sum;\n    };\n\n    static constexpr bool supports_sum = requires(Sum\
    \ left, Sum right, const T& value) {\n        Sum{};\n        static_cast<Sum>(value);\n\
    \        { left + right } -> std::convertible_to<Sum>;\n        { left - right\
    \ } -> std::convertible_to<Sum>;\n    };\n\n    int _n;\n    int _size;\n    std::vector<T>\
    \ _values;\n    std::vector<T> _sorted_values;\n    std::vector<Node> _tree;\n\
    \    std::vector<Sum> _original_prefix_sum;\n\n    template <class Callback>\n\
    \    void visit(int left, int right, Callback&& callback) const {\n        left\
    \ += _size;\n        right += _size;\n        while (left < right) {\n       \
    \     if (left & 1) callback(_tree[left++]);\n            if (right & 1) callback(_tree[--right]);\n\
    \            left >>= 1;\n            right >>= 1;\n        }\n    }\n\n    static\
    \ bool equivalent(const T& left, const T& right) {\n        return !(left < right)\
    \ && !(right < left);\n    }\n\n   public:\n    MergeSortTree()\n        : _n(0),\n\
    \          _size(1),\n          _tree(2) {\n        if constexpr (supports_sum)\
    \ _original_prefix_sum.push_back(Sum{});\n    }\n\n    explicit MergeSortTree(const\
    \ std::vector<T>& values)\n        : _n(0),\n          _size(1) {\n        assert(values.size()\
    \ <= std::size_t(std::numeric_limits<int>::max()));\n        _n = int(values.size());\n\
    \        _size = m1une::math::bit_ceil(std::max(1, _n));\n        _values = values;\n\
    \        _sorted_values = values;\n        std::sort(_sorted_values.begin(), _sorted_values.end());\n\
    \        _sorted_values.erase(\n            std::unique(\n                _sorted_values.begin(),\n\
    \                _sorted_values.end(),\n                [](const T& left, const\
    \ T& right) {\n                    return equivalent(left, right);\n         \
    \       }\n            ),\n            _sorted_values.end()\n        );\n\n  \
    \      _tree.resize(2 * _size);\n        for (int index = 0; index < _n; index++)\
    \ {\n            _tree[_size + index].values.push_back(values[index]);\n     \
    \   }\n        for (int node = _size - 1; node >= 1; node--) {\n            const\
    \ auto& left = _tree[2 * node].values;\n            const auto& right = _tree[2\
    \ * node + 1].values;\n            _tree[node].values.reserve(left.size() + right.size());\n\
    \            std::merge(\n                left.begin(),\n                left.end(),\n\
    \                right.begin(),\n                right.end(),\n              \
    \  std::back_inserter(_tree[node].values)\n            );\n        }\n\n     \
    \   if constexpr (supports_sum) {\n            _original_prefix_sum.reserve(_n\
    \ + 1);\n            _original_prefix_sum.push_back(Sum{});\n            for (const\
    \ T& value : values) {\n                _original_prefix_sum.push_back(\n    \
    \                _original_prefix_sum.back() + static_cast<Sum>(value)\n     \
    \           );\n            }\n            for (Node& node : _tree) {\n      \
    \          if (node.values.empty()) continue;\n                node.prefix_sum.reserve(node.values.size()\
    \ + 1);\n                node.prefix_sum.push_back(Sum{});\n                for\
    \ (const T& value : node.values) {\n                    node.prefix_sum.push_back(\n\
    \                        node.prefix_sum.back() + static_cast<Sum>(value)\n  \
    \                  );\n                }\n            }\n        }\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    const T& get(int position) const {\n  \
    \      assert(0 <= position && position < _n);\n        return _values[position];\n\
    \    }\n\n    const T& operator[](int position) const {\n        return get(position);\n\
    \    }\n\n    int count_less(int left, int right, const T& upper) const {\n  \
    \      assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::lower_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count_less_equal(int left, int right, const T& upper) const\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        int result\
    \ = 0;\n        visit(left, right, [&](const Node& node) {\n            const\
    \ auto& values = node.values;\n            result += int(std::upper_bound(values.begin(),\
    \ values.end(), upper) - values.begin());\n        });\n        return result;\n\
    \    }\n\n    int count(int left, int right, const T& value) const {\n       \
    \ assert(0 <= left && left <= right && right <= _n);\n        int result = 0;\n\
    \        visit(left, right, [&](const Node& node) {\n            const auto& values\
    \ = node.values;\n            auto range = std::equal_range(values.begin(), values.end(),\
    \ value);\n            result += int(range.second - range.first);\n        });\n\
    \        return result;\n    }\n\n    int count(int left, int right, const T&\
    \ lower, const T& upper) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        if (!(lower < upper)) return 0;\n        int result =\
    \ 0;\n        visit(left, right, [&](const Node& node) {\n            const auto&\
    \ values = node.values;\n            auto first = std::lower_bound(values.begin(),\
    \ values.end(), lower);\n            auto last = std::lower_bound(values.begin(),\
    \ values.end(), upper);\n            result += int(last - first);\n        });\n\
    \        return result;\n    }\n\n    Sum range_sum(int left, int right) const\
    \ requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        return _original_prefix_sum[right] - _original_prefix_sum[left];\n\
    \    }\n\n    Sum sum_less(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum_less_equal(int left, int right, const T& upper) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto iterator\
    \ = std::upper_bound(node.values.begin(), node.values.end(), upper);\n       \
    \     int position = int(iterator - node.values.begin());\n            result\
    \ = result + node.prefix_sum[position];\n        });\n        return result;\n\
    \    }\n\n    Sum sum(int left, int right, const T& value) const requires(supports_sum)\
    \ {\n        assert(0 <= left && left <= right && right <= _n);\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto range =\
    \ std::equal_range(node.values.begin(), node.values.end(), value);\n         \
    \   int first = int(range.first - node.values.begin());\n            int last\
    \ = int(range.second - node.values.begin());\n            result = result + node.prefix_sum[last]\
    \ - node.prefix_sum[first];\n        });\n        return result;\n    }\n\n  \
    \  Sum sum(int left, int right, const T& lower, const T& upper) const\n      \
    \  requires(supports_sum) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (!(lower < upper)) return Sum{};\n        Sum result{};\n\
    \        visit(left, right, [&](const Node& node) {\n            auto first_iterator\
    \ = std::lower_bound(node.values.begin(), node.values.end(), lower);\n       \
    \     auto last_iterator = std::lower_bound(node.values.begin(), node.values.end(),\
    \ upper);\n            int first = int(first_iterator - node.values.begin());\n\
    \            int last = int(last_iterator - node.values.begin());\n          \
    \  result = result + node.prefix_sum[last] - node.prefix_sum[first];\n       \
    \ });\n        return result;\n    }\n\n    T kth_smallest(int left, int right,\
    \ int k) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        assert(0 <= k && k < right - left);\n        int low = 0;\n        int\
    \ high = int(_sorted_values.size()) - 1;\n        while (low < high) {\n     \
    \       int middle = (low + high) / 2;\n            if (count_less_equal(left,\
    \ right, _sorted_values[middle]) > k) {\n                high = middle;\n    \
    \        } else {\n                low = middle + 1;\n            }\n        }\n\
    \        return _sorted_values[low];\n    }\n\n    T kth_largest(int left, int\
    \ right, int k) const {\n        assert(0 <= left && left <= right && right <=\
    \ _n);\n        assert(0 <= k && k < right - left);\n        return kth_smallest(left,\
    \ right, right - left - 1 - k);\n    }\n\n    std::optional<T> prev_value(int\
    \ left, int right, const T& upper) const {\n        assert(0 <= left && left <=\
    \ right && right <= _n);\n        std::optional<T> result;\n        visit(left,\
    \ right, [&](const Node& node) {\n            const auto& values = node.values;\n\
    \            auto iterator = std::lower_bound(values.begin(), values.end(), upper);\n\
    \            if (iterator == values.begin()) return;\n            --iterator;\n\
    \            if (!result || *result < *iterator) result = *iterator;\n       \
    \ });\n        return result;\n    }\n\n    std::optional<T> next_value(int left,\
    \ int right, const T& lower) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::optional<T> result;\n        visit(left, right,\
    \ [&](const Node& node) {\n            const auto& values = node.values;\n   \
    \         auto iterator = std::lower_bound(values.begin(), values.end(), lower);\n\
    \            if (iterator == values.end()) return;\n            if (!result ||\
    \ *iterator < *result) result = *iterator;\n        });\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP\n"
  dependsOn:
  - math/bit_ceil.hpp
  isVerificationFile: false
  path: ds/range_query/merge_sort_tree.hpp
  requiredBy: []
  timestamp: '2026-07-14 01:36:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/merge_sort_tree.test.cpp
  - verify/ds/range_query/merge_sort_tree_sum.test.cpp
documentation_of: ds/range_query/merge_sort_tree.hpp
layout: document
title: Merge Sort Tree
---

## Overview

`MergeSortTree<T, Sum>` preprocesses a static sequence by storing sorted values
at every segment-tree node. For summable types, it also stores prefix sums. It
supports range frequency and sum queries, order statistics, and
predecessor/successor searches.

Use a merge sort tree when values are arbitrary ordered objects or when a
simple static range-counting structure is convenient. For integral values and
many order-statistic queries, `WaveletMatrix` uses less memory and has faster
queries.

## Requirements

`T` must be copyable and provide a strict weak ordering through `operator<`.
Values equivalent under that ordering are treated as equal. The input sequence
is copied and never modified.

`Sum` defaults to `T`. Sum methods are available when `T` is explicitly
convertible to `Sum`, `Sum{}` is the additive identity, and addition and
subtraction produce values convertible to `Sum`. Choose a sufficiently wide
type, such as `MergeSortTree<int, long long>`, because arithmetic uses `Sum`
and does not check for overflow. Ordered nonnumeric types can still use every
nonsum method.

## Public Interface

All index ranges are zero-based and half-open.

```cpp
template <class T, class Sum = T>
class MergeSortTree;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `MergeSortTree()` | Constructs an empty tree. | $O(1)$ |
| `explicit MergeSortTree(const std::vector<T>& values)` | Builds the tree. | $O(N\log N)$ time and memory |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `const T& get(int position) const` | Returns the original value at `position`. | $O(1)$ |
| `const T& operator[](int position) const` | Equivalent to `get(position)`. | $O(1)$ |
| `int count_less(int left, int right, const T& upper) const` | Counts values less than `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `int count_less_equal(int left, int right, const T& upper) const` | Counts values at most `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `int count(int left, int right, const T& value) const` | Counts values equivalent to `value` in `[left, right)`. | $O(\log^2 N)$ |
| `int count(int left, int right, const T& lower, const T& upper) const` | Counts values in `[lower, upper)` within `[left, right)`. | $O(\log^2 N)$ |
| `Sum range_sum(int left, int right) const` | Returns the sum of all values in `[left, right)`. | $O(1)$ |
| `Sum sum_less(int left, int right, const T& upper) const` | Sums values less than `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum_less_equal(int left, int right, const T& upper) const` | Sums values at most `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum(int left, int right, const T& value) const` | Sums values equivalent to `value` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum(int left, int right, const T& lower, const T& upper) const` | Sums values in `[lower, upper)` within `[left, right)`. | $O(\log^2 N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest value. | $O(\log U\log^2 N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest value. | $O(\log U\log^2 N)$ |
| `std::optional<T> prev_value(int left, int right, const T& upper) const` | Returns the greatest value less than `upper`, or `nullopt`. | $O(\log^2 N)$ |
| `std::optional<T> next_value(int left, int right, const T& lower) const` | Returns the smallest value at least `lower`, or `nullopt`. | $O(\log^2 N)$ |

Here, $U$ is the number of distinct values stored in the complete sequence.
The order-statistic methods require `0 <= k < right - left`. Empty ranges are
valid for every count, sum, and predecessor/successor query. All sum methods
sum the stored values themselves; the bounds only filter which values are
included.

## Example

```cpp
#include "ds/range_query/merge_sort_tree.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {5, 1, 4, 1, 3};
    m1une::ds::MergeSortTree<int, long long> tree(values);

    std::cout << tree.count(0, 5, 1) << "\n";          // 2
    std::cout << tree.sum_less_equal(0, 5, 3) << "\n"; // 5
    std::cout << tree.sum(1, 5, 2, 5) << "\n";         // 7
    std::cout << tree.kth_smallest(0, 5, 2) << "\n";   // 3
}
```
