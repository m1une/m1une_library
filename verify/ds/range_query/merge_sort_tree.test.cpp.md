---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/merge_sort_tree.hpp
    title: Merge Sort Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"verify/ds/range_query/merge_sort_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\n#line\
    \ 1 \"ds/range_query/merge_sort_tree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <concepts>\n#include <cstddef>\n#include <iterator>\n#include\
    \ <limits>\n#include <optional>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n#line 15 \"ds/range_query/merge_sort_tree.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\n// Static range counting, sums, and order\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/merge_sort_tree.test.cpp\"\
    \n\n#line 7 \"verify/ds/range_query/merge_sort_tree.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 10 \"verify/ds/range_query/merge_sort_tree.test.cpp\"\
    \n#include <string>\n#line 12 \"verify/ds/range_query/merge_sort_tree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_fixed() {\n    m1une::ds::MergeSortTree<int> empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.count(0,\
    \ 0, 7) == 0);\n    assert(empty.count_less(0, 0, 7) == 0);\n    assert(empty.range_sum(0,\
    \ 0) == 0);\n    assert(empty.sum_less_equal(0, 0, 7) == 0);\n    assert(!empty.prev_value(0,\
    \ 0, 7));\n    assert(!empty.next_value(0, 0, 7));\n\n    std::vector<std::string>\
    \ words = {\"pear\", \"apple\", \"pear\", \"plum\"};\n    m1une::ds::MergeSortTree<std::string>\
    \ strings(words);\n    assert(strings.count(0, 4, std::string(\"pear\")) == 2);\n\
    \    assert(strings.count(0, 4, std::string(\"a\"), std::string(\"q\")) == 4);\n\
    \    assert(strings.kth_smallest(0, 4, 0) == \"apple\");\n    assert(strings.prev_value(0,\
    \ 4, std::string(\"pear\")).value() == \"apple\");\n    assert(strings.next_value(0,\
    \ 4, std::string(\"pebble\")).value() == \"plum\");\n\n    std::vector<int> large\
    \ = {1'000'000'000, 1'000'000'000, -1'000'000'000};\n    m1une::ds::MergeSortTree<int,\
    \ long long> wide(large);\n    assert(wide.range_sum(0, 3) == 1'000'000'000LL);\n\
    \    assert(wide.sum_less_equal(0, 3, 1'000'000'000) == 1'000'000'000LL);\n}\n\
    \nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 500; trial++)\
    \ {\n        int size = int(random() % 60);\n        std::vector<int> values(size);\n\
    \        for (int& value : values) value = int(random() % 41) - 20;\n        m1une::ds::MergeSortTree<int>\
    \ tree(values);\n        assert(tree.size() == size);\n        assert(tree.empty()\
    \ == values.empty());\n        for (int i = 0; i < size; i++) assert(tree[i] ==\
    \ values[i]);\n\n        for (int query = 0; query < 300; query++) {\n       \
    \     int left = int(random() % (size + 1));\n            int right = int(random()\
    \ % (size + 1));\n            if (left > right) std::swap(left, right);\n    \
    \        int lower = int(random() % 51) - 25;\n            int upper = int(random()\
    \ % 51) - 25;\n            if (lower > upper) std::swap(lower, upper);\n\n   \
    \         int less = 0;\n            int less_equal = 0;\n            int equal\
    \ = 0;\n            int between = 0;\n            int total_sum = 0;\n       \
    \     int less_sum = 0;\n            int less_equal_sum = 0;\n            int\
    \ equal_sum = 0;\n            int between_sum = 0;\n            std::optional<int>\
    \ previous;\n            std::optional<int> next;\n            std::vector<int>\
    \ sorted;\n            for (int i = left; i < right; i++) {\n                sorted.push_back(values[i]);\n\
    \                less += values[i] < lower;\n                less_equal += values[i]\
    \ <= lower;\n                equal += values[i] == lower;\n                between\
    \ += lower <= values[i] && values[i] < upper;\n                total_sum += values[i];\n\
    \                if (values[i] < lower) less_sum += values[i];\n             \
    \   if (values[i] <= lower) less_equal_sum += values[i];\n                if (values[i]\
    \ == lower) equal_sum += values[i];\n                if (lower <= values[i] &&\
    \ values[i] < upper) between_sum += values[i];\n                if (values[i]\
    \ < lower && (!previous || *previous < values[i])) {\n                    previous\
    \ = values[i];\n                }\n                if (lower <= values[i] && (!next\
    \ || values[i] < *next)) {\n                    next = values[i];\n          \
    \      }\n            }\n            std::sort(sorted.begin(), sorted.end());\n\
    \n            assert(tree.count_less(left, right, lower) == less);\n         \
    \   assert(tree.count_less_equal(left, right, lower) == less_equal);\n       \
    \     assert(tree.count(left, right, lower) == equal);\n            assert(tree.count(left,\
    \ right, lower, upper) == between);\n            assert(tree.range_sum(left, right)\
    \ == total_sum);\n            assert(tree.sum_less(left, right, lower) == less_sum);\n\
    \            assert(tree.sum_less_equal(left, right, lower) == less_equal_sum);\n\
    \            assert(tree.sum(left, right, lower) == equal_sum);\n            assert(tree.sum(left,\
    \ right, lower, upper) == between_sum);\n            assert(tree.prev_value(left,\
    \ right, lower) == previous);\n            assert(tree.next_value(left, right,\
    \ lower) == next);\n            if (!sorted.empty()) {\n                int k\
    \ = int(random() % sorted.size());\n                assert(tree.kth_smallest(left,\
    \ right, k) == sorted[k]);\n                assert(tree.kth_largest(left, right,\
    \ k) == sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, query_count;\n    std::cin >> n >> query_count;\n    std::vector<int> values(n);\n\
    \    for (int& value : values) std::cin >> value;\n\n    m1une::ds::MergeSortTree<int>\
    \ tree(values);\n    while (query_count--) {\n        int left, right, value;\n\
    \        std::cin >> left >> right >> value;\n        std::cout << tree.count(left,\
    \ right, value) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n\n#include \"../../../ds/range_query/merge_sort_tree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <optional>\n\
    #include <string>\n#include <vector>\n\nnamespace {\n\nvoid test_fixed() {\n \
    \   m1une::ds::MergeSortTree<int> empty;\n    assert(empty.empty());\n    assert(empty.size()\
    \ == 0);\n    assert(empty.count(0, 0, 7) == 0);\n    assert(empty.count_less(0,\
    \ 0, 7) == 0);\n    assert(empty.range_sum(0, 0) == 0);\n    assert(empty.sum_less_equal(0,\
    \ 0, 7) == 0);\n    assert(!empty.prev_value(0, 0, 7));\n    assert(!empty.next_value(0,\
    \ 0, 7));\n\n    std::vector<std::string> words = {\"pear\", \"apple\", \"pear\"\
    , \"plum\"};\n    m1une::ds::MergeSortTree<std::string> strings(words);\n    assert(strings.count(0,\
    \ 4, std::string(\"pear\")) == 2);\n    assert(strings.count(0, 4, std::string(\"\
    a\"), std::string(\"q\")) == 4);\n    assert(strings.kth_smallest(0, 4, 0) ==\
    \ \"apple\");\n    assert(strings.prev_value(0, 4, std::string(\"pear\")).value()\
    \ == \"apple\");\n    assert(strings.next_value(0, 4, std::string(\"pebble\")).value()\
    \ == \"plum\");\n\n    std::vector<int> large = {1'000'000'000, 1'000'000'000,\
    \ -1'000'000'000};\n    m1une::ds::MergeSortTree<int, long long> wide(large);\n\
    \    assert(wide.range_sum(0, 3) == 1'000'000'000LL);\n    assert(wide.sum_less_equal(0,\
    \ 3, 1'000'000'000) == 1'000'000'000LL);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 123456789;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 500; trial++) {\n        int size = int(random() % 60);\n\
    \        std::vector<int> values(size);\n        for (int& value : values) value\
    \ = int(random() % 41) - 20;\n        m1une::ds::MergeSortTree<int> tree(values);\n\
    \        assert(tree.size() == size);\n        assert(tree.empty() == values.empty());\n\
    \        for (int i = 0; i < size; i++) assert(tree[i] == values[i]);\n\n    \
    \    for (int query = 0; query < 300; query++) {\n            int left = int(random()\
    \ % (size + 1));\n            int right = int(random() % (size + 1));\n      \
    \      if (left > right) std::swap(left, right);\n            int lower = int(random()\
    \ % 51) - 25;\n            int upper = int(random() % 51) - 25;\n            if\
    \ (lower > upper) std::swap(lower, upper);\n\n            int less = 0;\n    \
    \        int less_equal = 0;\n            int equal = 0;\n            int between\
    \ = 0;\n            int total_sum = 0;\n            int less_sum = 0;\n      \
    \      int less_equal_sum = 0;\n            int equal_sum = 0;\n            int\
    \ between_sum = 0;\n            std::optional<int> previous;\n            std::optional<int>\
    \ next;\n            std::vector<int> sorted;\n            for (int i = left;\
    \ i < right; i++) {\n                sorted.push_back(values[i]);\n          \
    \      less += values[i] < lower;\n                less_equal += values[i] <=\
    \ lower;\n                equal += values[i] == lower;\n                between\
    \ += lower <= values[i] && values[i] < upper;\n                total_sum += values[i];\n\
    \                if (values[i] < lower) less_sum += values[i];\n             \
    \   if (values[i] <= lower) less_equal_sum += values[i];\n                if (values[i]\
    \ == lower) equal_sum += values[i];\n                if (lower <= values[i] &&\
    \ values[i] < upper) between_sum += values[i];\n                if (values[i]\
    \ < lower && (!previous || *previous < values[i])) {\n                    previous\
    \ = values[i];\n                }\n                if (lower <= values[i] && (!next\
    \ || values[i] < *next)) {\n                    next = values[i];\n          \
    \      }\n            }\n            std::sort(sorted.begin(), sorted.end());\n\
    \n            assert(tree.count_less(left, right, lower) == less);\n         \
    \   assert(tree.count_less_equal(left, right, lower) == less_equal);\n       \
    \     assert(tree.count(left, right, lower) == equal);\n            assert(tree.count(left,\
    \ right, lower, upper) == between);\n            assert(tree.range_sum(left, right)\
    \ == total_sum);\n            assert(tree.sum_less(left, right, lower) == less_sum);\n\
    \            assert(tree.sum_less_equal(left, right, lower) == less_equal_sum);\n\
    \            assert(tree.sum(left, right, lower) == equal_sum);\n            assert(tree.sum(left,\
    \ right, lower, upper) == between_sum);\n            assert(tree.prev_value(left,\
    \ right, lower) == previous);\n            assert(tree.next_value(left, right,\
    \ lower) == next);\n            if (!sorted.empty()) {\n                int k\
    \ = int(random() % sorted.size());\n                assert(tree.kth_smallest(left,\
    \ right, k) == sorted[k]);\n                assert(tree.kth_largest(left, right,\
    \ k) == sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int\
    \ n, query_count;\n    std::cin >> n >> query_count;\n    std::vector<int> values(n);\n\
    \    for (int& value : values) std::cin >> value;\n\n    m1une::ds::MergeSortTree<int>\
    \ tree(values);\n    while (query_count--) {\n        int left, right, value;\n\
    \        std::cin >> left >> right >> value;\n        std::cout << tree.count(left,\
    \ right, value) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/merge_sort_tree.hpp
  - math/bit_ceil.hpp
  isVerificationFile: true
  path: verify/ds/range_query/merge_sort_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 01:36:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/merge_sort_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/merge_sort_tree.test.cpp
- /verify/verify/ds/range_query/merge_sort_tree.test.cpp.html
title: verify/ds/range_query/merge_sort_tree.test.cpp
---
