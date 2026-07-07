---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/alien_trick.hpp
    title: Alien Trick
  - icon: ':heavy_check_mark:'
    path: convex/convex_hull_trick.hpp
    title: Convex Hull Trick
  - icon: ':heavy_check_mark:'
    path: convex/li_chao_tree.hpp
    title: Li Chao Tree
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge All
  - icon: ':heavy_check_mark:'
    path: convex/monge/check.hpp
    title: Monge Checks
  - icon: ':heavy_check_mark:'
    path: convex/monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
  - icon: ':heavy_check_mark:'
    path: convex/monge/knuth_optimization.hpp
    title: Knuth Optimization
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH
  - icon: ':heavy_check_mark:'
    path: convex/monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  - icon: ':heavy_check_mark:'
    path: convex/slope_trick.hpp
    title: Slope Trick
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/all.hpp\"\n\n\n\n#line 1 \"convex/alien_trick.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <numeric>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace convex {\n\
    \nnamespace detail {\n\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nPenalty alien_trick_penalty(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle& oracle) {\n    assert(lower <= upper);\n    assert(oracle(lower).second\
    \ >= target_count);\n    assert(oracle(upper).second <= target_count);\n\n   \
    \ while (lower < upper) {\n        Penalty middle = std::midpoint(lower, upper);\n\
    \        if (middle == lower) ++middle;\n        if (oracle(middle).second >=\
    \ target_count) {\n            lower = middle;\n        } else {\n           \
    \ upper = middle - 1;\n        }\n    }\n    return lower;\n}\n\n}  // namespace\
    \ detail\n\n// Recovers the minimum value among solutions using exactly `target_count`\n\
    // items. The oracle minimizes value + penalty * count and breaks ties in favor\n\
    // of the larger count.\ntemplate <std::integral Penalty, std::integral Count,\
    \ class Oracle>\nauto alien_trick_minimize(Penalty lower, Penalty upper, Count\
    \ target_count, Oracle oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower,\
    \ upper, target_count, oracle);\n    auto result = oracle(penalty);\n    using\
    \ Value = std::remove_cvref_t<decltype(result.first)>;\n    return result.first\
    \ - static_cast<Value>(penalty) * static_cast<Value>(target_count);\n}\n\n// Recovers\
    \ the maximum value among solutions using exactly `target_count`\n// items. The\
    \ oracle maximizes value - penalty * count and breaks ties in favor\n// of the\
    \ larger count.\ntemplate <std::integral Penalty, std::integral Count, class Oracle>\n\
    auto alien_trick_maximize(Penalty lower, Penalty upper, Count target_count, Oracle\
    \ oracle) {\n    Penalty penalty = detail::alien_trick_penalty(lower, upper, target_count,\
    \ oracle);\n    auto result = oracle(penalty);\n    using Value = std::remove_cvref_t<decltype(result.first)>;\n\
    \    return result.first + static_cast<Value>(penalty) * static_cast<Value>(target_count);\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/convex_hull_trick.hpp\"\
    \n\n\n\n#line 6 \"convex/convex_hull_trick.hpp\"\n#include <cstddef>\n#include\
    \ <optional>\n#line 9 \"convex/convex_hull_trick.hpp\"\n#include <vector>\n\n\
    namespace m1une {\nnamespace convex {\n\nenum class LineOptimization {\n    Minimize,\n\
    \    Maximize,\n};\n\ntemplate <std::signed_integral T>\nusing line_wide_type\
    \ = __int128_t;\n\ntemplate <std::signed_integral T>\nstruct LinearFunction {\n\
    \    using value_type = line_wide_type<T>;\n\n    value_type slope;\n    value_type\
    \ intercept;\n\n    constexpr LinearFunction() : slope(0), intercept(0) {}\n\n\
    \    constexpr LinearFunction(T slope_value, T intercept_value) : slope(slope_value),\
    \ intercept(intercept_value) {}\n\n    constexpr value_type operator()(T x) const\
    \ {\n        return slope * value_type(x) + intercept;\n    }\n};\n\n// Convex\
    \ hull trick for lines inserted in nondecreasing slope order.\ntemplate <std::signed_integral\
    \ T, LineOptimization Objective = LineOptimization::Minimize>\nstruct ConvexHullTrick\
    \ {\n    using Line = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\
    \n   private:\n    std::vector<Line> _lines;\n\n    static bool better(value_type\
    \ first, value_type second) {\n        if constexpr (Objective == LineOptimization::Minimize)\
    \ {\n            return first < second;\n        } else {\n            return\
    \ second < first;\n        }\n    }\n\n    static bool redundant(const Line& first,\
    \ const Line& middle, const Line& last) {\n        value_type left = (first.intercept\
    \ - middle.intercept) * (last.slope - middle.slope);\n        value_type right\
    \ = (middle.intercept - last.intercept) * (middle.slope - first.slope);\n    \
    \    if constexpr (Objective == LineOptimization::Minimize) {\n            return\
    \ left <= right;\n        } else {\n            return right <= left;\n      \
    \  }\n    }\n\n   public:\n    ConvexHullTrick() = default;\n\n    int size()\
    \ const {\n        return int(_lines.size());\n    }\n\n    bool empty() const\
    \ {\n        return _lines.empty();\n    }\n\n    const std::vector<Line>& lines()\
    \ const {\n        return _lines;\n    }\n\n    void reserve(std::size_t line_capacity)\
    \ {\n        _lines.reserve(line_capacity);\n    }\n\n    void clear() {\n   \
    \     _lines.clear();\n    }\n\n    // Slopes must be inserted in nondecreasing\
    \ order.\n    void add_line(T slope, T intercept) {\n        Line line(slope,\
    \ intercept);\n        if (!_lines.empty()) {\n            assert(_lines.back().slope\
    \ <= line.slope);\n        }\n\n        if (!_lines.empty() && _lines.back().slope\
    \ == line.slope) {\n            if (!better(line.intercept, _lines.back().intercept))\
    \ return;\n            _lines.pop_back();\n        }\n\n        while (_lines.size()\
    \ >= 2 && redundant(_lines[_lines.size() - 2], _lines.back(), line)) {\n     \
    \       _lines.pop_back();\n        }\n        _lines.push_back(line);\n    }\n\
    \n    std::optional<value_type> try_query(T x) const {\n        if (_lines.empty())\
    \ return std::nullopt;\n        int low = 0;\n        int high = int(_lines.size())\
    \ - 1;\n        while (low < high) {\n            int middle = low + (high - low)\
    \ / 2;\n            value_type first = _lines[middle](x);\n            value_type\
    \ second = _lines[middle + 1](x);\n            if (better(first, second) || first\
    \ == second) {\n                high = middle;\n            } else {\n       \
    \         low = middle + 1;\n            }\n        }\n        return _lines[low](x);\n\
    \    }\n\n    value_type query(T x) const {\n        assert(!empty());\n     \
    \   return *try_query(x);\n    }\n};\n\ntemplate <std::signed_integral T>\nusing\
    \ MinConvexHullTrick = ConvexHullTrick<T, LineOptimization::Minimize>;\n\ntemplate\
    \ <std::signed_integral T>\nusing MaxConvexHullTrick = ConvexHullTrick<T, LineOptimization::Maximize>;\n\
    \n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/li_chao_tree.hpp\"\
    \n\n\n\n#line 7 \"convex/li_chao_tree.hpp\"\n#include <limits>\n#line 13 \"convex/li_chao_tree.hpp\"\
    \n\n#line 15 \"convex/li_chao_tree.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\n// Dynamic Li Chao tree over an integral half-open coordinate domain.\n\
    template <std::signed_integral T, LineOptimization Objective = LineOptimization::Minimize>\n\
    struct LiChaoTree {\n    using Line = LinearFunction<T>;\n    using value_type\
    \ = typename Line::value_type;\n\n   private:\n    struct Node {\n        Line\
    \ line;\n        bool has_line;\n        int left;\n        int right;\n\n   \
    \     Node() : has_line(false), left(-1), right(-1) {}\n\n        explicit Node(Line\
    \ value) : line(std::move(value)), has_line(true), left(-1), right(-1) {}\n  \
    \  };\n\n    T _left;\n    T _right;\n    int _root;\n    std::vector<Node> _nodes;\n\
    \n    static bool better(value_type first, value_type second) {\n        if constexpr\
    \ (Objective == LineOptimization::Minimize) {\n            return first < second;\n\
    \        } else {\n            return second < first;\n        }\n    }\n\n  \
    \  int new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    int new_node(Line line) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(std::move(line));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    int add_line_node(int node, T left, T right, Line line) {\n\
    \        if (node == -1) return new_node(std::move(line));\n        if (!_nodes[node].has_line)\
    \ {\n            _nodes[node].line = std::move(line);\n            _nodes[node].has_line\
    \ = true;\n            return node;\n        }\n\n        T middle = std::midpoint(left,\
    \ right);\n        bool left_better = better(line(left), _nodes[node].line(left));\n\
    \        bool middle_better = better(line(middle), _nodes[node].line(middle));\n\
    \        if (middle_better) std::swap(line, _nodes[node].line);\n        if (middle\
    \ == left) return node;\n\n        if (left_better != middle_better) {\n     \
    \       int child = add_line_node(_nodes[node].left, left, middle, std::move(line));\n\
    \            _nodes[node].left = child;\n        } else {\n            int child\
    \ = add_line_node(_nodes[node].right, middle, right, std::move(line));\n     \
    \       _nodes[node].right = child;\n        }\n        return node;\n    }\n\n\
    \    int add_segment_node(int node, T left, T right, T query_left, T query_right,\
    \ const Line& line) {\n        if (query_right <= left || right <= query_left)\
    \ return node;\n        if (query_left <= left && right <= query_right) {\n  \
    \          return add_line_node(node, left, right, line);\n        }\n       \
    \ if (node == -1) node = new_node();\n\n        T middle = std::midpoint(left,\
    \ right);\n        if (middle == left) return add_line_node(node, left, right,\
    \ line);\n        int left_child = add_segment_node(_nodes[node].left, left, middle,\
    \ query_left, query_right, line);\n        int right_child = add_segment_node(_nodes[node].right,\
    \ middle, right, query_left, query_right, line);\n        _nodes[node].left =\
    \ left_child;\n        _nodes[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    LiChaoTree() : _left(0), _right(0), _root(-1) {}\n\n\
    \    LiChaoTree(T left, T right) : _left(left), _right(right), _root(-1) {\n \
    \       assert(left <= right);\n    }\n\n    T left_bound() const {\n        return\
    \ _left;\n    }\n\n    T right_bound() const {\n        return _right;\n    }\n\
    \n    bool empty() const {\n        return _root == -1;\n    }\n\n    std::size_t\
    \ node_count() const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _root = -1;\n        _nodes.clear();\n    }\n\n    void add_line(T\
    \ slope, T intercept) {\n        assert(_left < _right);\n        _root = add_line_node(_root,\
    \ _left, _right, Line(slope, intercept));\n    }\n\n    void add_segment(T segment_left,\
    \ T segment_right, T slope, T intercept) {\n        assert(_left <= segment_left\
    \ && segment_left <= segment_right && segment_right <= _right);\n        if (segment_left\
    \ == segment_right) return;\n        _root = add_segment_node(_root, _left, _right,\
    \ segment_left, segment_right, Line(slope, intercept));\n    }\n\n    // Returns\
    \ nullopt when no inserted line covers x.\n    std::optional<value_type> query(T\
    \ x) const {\n        assert(_left <= x && x < _right);\n        std::optional<value_type>\
    \ result;\n        int node = _root;\n        T left = _left;\n        T right\
    \ = _right;\n        while (node != -1) {\n            if (_nodes[node].has_line)\
    \ {\n                value_type candidate = _nodes[node].line(x);\n          \
    \      if (!result || better(candidate, *result)) {\n                    result\
    \ = candidate;\n                }\n            }\n\n            T middle = std::midpoint(left,\
    \ right);\n            if (middle == left) break;\n            if (x < middle)\
    \ {\n                node = _nodes[node].left;\n                right = middle;\n\
    \            } else {\n                node = _nodes[node].right;\n          \
    \      left = middle;\n            }\n        }\n        return result;\n    }\n\
    \n    value_type get(T x) const {\n        std::optional<value_type> result =\
    \ query(x);\n        assert(result.has_value());\n        return result.value_or(value_type());\n\
    \    }\n};\n\ntemplate <std::signed_integral T>\nusing MinLiChaoTree = LiChaoTree<T,\
    \ LineOptimization::Minimize>;\n\ntemplate <std::signed_integral T>\nusing MaxLiChaoTree\
    \ = LiChaoTree<T, LineOptimization::Maximize>;\n\n}  // namespace convex\n}  //\
    \ namespace m1une\n\n\n#line 1 \"convex/monge/all.hpp\"\n\n\n\n#line 1 \"convex/monge/check.hpp\"\
    \n\n\n\n#line 6 \"convex/monge/check.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\ntemplate <class Value>\nbool is_monge(int row_count, int column_count,\
    \ Value value) {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n\
    \    for (int row = 0; row + 1 < row_count; row++) {\n        for (int column\
    \ = 0; column + 1 < column_count; column++) {\n            if (value(row, column)\
    \ + value(row + 1, column + 1) >\n                value(row, column + 1) + value(row\
    \ + 1, column)) {\n                return false;\n            }\n        }\n \
    \   }\n    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
    \ int column_count, Value value) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    for (int row = 0; row + 1 < row_count; row++) {\n        for (int\
    \ column = 0; column + 1 < column_count; column++) {\n            if (value(row,\
    \ column) + value(row + 1, column + 1) <\n                value(row, column +\
    \ 1) + value(row + 1, column)) {\n                return false;\n            }\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_monge(row_count,\
    \ column_count,\n                    [&](int row, int column) -> const T& { return\
    \ matrix[row][column]; });\n}\n\ntemplate <class T>\nbool is_anti_monge(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return is_anti_monge(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/divide_and_conquer_optimization.hpp\"\n\n\n\
    \n#line 7 \"convex/monge/divide_and_conquer_optimization.hpp\"\n\n#line 1 \"convex/monge/monotone_minima.hpp\"\
    \n\n\n\n#line 5 \"convex/monge/monotone_minima.hpp\"\n#include <functional>\n\
    #line 7 \"convex/monge/monotone_minima.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\nnamespace monotone_minima_detail {\n\ntemplate <class Value, class Compare>\n\
    void solve(int row_left, int row_right, int column_left, int column_right,\n \
    \          const Value& value, const Compare& compare, std::vector<int>& answer)\
    \ {\n    if (row_left == row_right) return;\n    int row = (row_left + row_right)\
    \ / 2;\n    int best = column_left;\n    for (int column = column_left + 1; column\
    \ < column_right; column++) {\n        if (compare(value(row, column), value(row,\
    \ best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
    \ row, column_left, best + 1, value, compare, answer);\n    solve(row + 1, row_right,\
    \ best, column_right, value, compare, answer);\n}\n\n}  // namespace monotone_minima_detail\n\
    \ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \     Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    std::vector<int> answer(row_count, -1);\n    if (row_count == 0\
    \ || column_count == 0) return answer;\n    monotone_minima_detail::solve(0, row_count,\
    \ 0, column_count, value, compare, answer);\n    return answer;\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmin(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int> monotone_row_argmax(int\
    \ row_count, int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmin(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmin(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\ntemplate <class\
    \ Value>\nauto divide_and_conquer_dp(int state_count, int candidate_count, Value\
    \ value)\n    -> DivideAndConquerDpResult<\n        std::decay_t<std::invoke_result_t<Value,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;\n\
    \    DivideAndConquerDpResult<T> result;\n    result.argmin = monotone_row_argmin(state_count,\
    \ candidate_count, value);\n    result.value.resize(state_count);\n    for (int\
    \ state = 0; state < state_count; state++) {\n        if (result.argmin[state]\
    \ != -1) {\n            result.value[state] = value(state, result.argmin[state]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class T, class Cost>\nauto\
    \ divide_and_conquer_transition(const std::vector<T>& previous, int state_count,\n\
    \                                   Cost cost)\n    -> DivideAndConquerDpResult<\n\
    \        std::decay_t<decltype(std::declval<T>() + cost(0, 0))>> {\n    using\
    \ Result = std::decay_t<decltype(std::declval<T>() + cost(0, 0))>;\n    return\
    \ divide_and_conquer_dp(\n        state_count, int(previous.size()),\n       \
    \ [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/knuth_optimization.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 8 \"convex/monge/knuth_optimization.hpp\"\n\nnamespace m1une {\nnamespace\
    \ convex {\n\ntemplate <class T>\nstruct KnuthOptimizationResult {\n    std::vector<std::vector<T>>\
    \ value;\n    std::vector<std::vector<int>> split;\n\n    T optimum() const {\n\
    \        return value[0].back();\n    }\n};\n\ntemplate <class IntervalCost>\n\
    auto knuth_optimization(int element_count, IntervalCost interval_cost)\n    ->\
    \ KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/larsch.hpp\"\
    \n\n\n\n#line 6 \"convex/monge/larsch.hpp\"\n#include <memory>\n#line 10 \"convex/monge/larsch.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nclass Larsch\
    \ {\n    struct ReduceColumn;\n\n    struct ReduceRow {\n        int size;\n \
    \       std::function<T(int, int)> value;\n        int current_row = 0;\n    \
    \    int boundary = 0;\n        std::unique_ptr<ReduceColumn> recursive;\n\n \
    \       explicit ReduceRow(int size_) : size(size_) {\n            if (size /\
    \ 2 != 0) recursive = std::make_unique<ReduceColumn>(size / 2);\n        }\n\n\
    \        void set_value(std::function<T(int, int)> value_) {\n            value\
    \ = std::move(value_);\n            if (recursive) {\n                recursive->set_value(\n\
    \                    [&](int row, int column) { return value(row * 2 + 1, column);\
    \ });\n            }\n        }\n\n        int next_argmin() {\n            int\
    \ row = current_row++;\n            if (row % 2 == 0) {\n                int previous\
    \ = boundary;\n                int next = row + 1 == size ? size - 1 : recursive->next_argmin();\n\
    \                boundary = next;\n                int best = previous;\n    \
    \            for (int column = previous + 1; column <= next; column++) {\n   \
    \                 if (value(row, column) < value(row, best)) best = column;\n\
    \                }\n                return best;\n            }\n            return\
    \ value(row, boundary) <= value(row, row) ? boundary : row;\n        }\n    };\n\
    \n    struct ReduceColumn {\n        int size;\n        std::function<T(int, int)>\
    \ value;\n        int current_row = 0;\n        std::vector<int> columns;\n  \
    \      ReduceRow recursive;\n\n        explicit ReduceColumn(int size_) : size(size_),\
    \ recursive(size_) {}\n\n        void set_value(std::function<T(int, int)> value_)\
    \ {\n            value = std::move(value_);\n            recursive.set_value(\n\
    \                [&](int row, int column) { return value(row, columns[column]);\
    \ });\n        }\n\n        int next_argmin() {\n            int row = current_row++;\n\
    \            int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row\
    \ * 2;\n            for (int column = first; column <= last; column++) {\n   \
    \             while (int(columns.size()) != row &&\n                       value(int(columns.size())\
    \ - 1, columns.back()) >\n                           value(int(columns.size())\
    \ - 1, column)) {\n                    columns.pop_back();\n                }\n\
    \                if (int(columns.size()) != size) columns.push_back(column);\n\
    \            }\n            return columns[recursive.next_argmin()];\n       \
    \ }\n    };\n\n    int _size;\n    int _processed = 0;\n    std::unique_ptr<ReduceRow>\
    \ _base;\n\n   public:\n    template <class Value>\n    explicit Larsch(int size,\
    \ Value value)\n        : _size(size), _base(std::make_unique<ReduceRow>(size))\
    \ {\n        assert(size >= 0);\n        _base->set_value(std::function<T(int,\
    \ int)>(std::move(value)));\n    }\n\n    int size() const {\n        return _size;\n\
    \    }\n\n    int processed_rows() const {\n        return _processed;\n    }\n\
    \n    bool finished() const {\n        return _processed == _size;\n    }\n\n\
    \    int next_argmin() {\n        assert(!finished());\n        _processed++;\n\
    \        return _base->next_argmin();\n    }\n};\n\ntemplate <class T>\nstruct\
    \ LarschShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\ntemplate <class Cost>\nauto larsch_shortest_path(int vertex_count,\
    \ Cost cost)\n    -> LarschShortestPathResult<\n        std::decay_t<std::invoke_result_t<Cost,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;\n\
    \    assert(vertex_count >= 0);\n\n    LarschShortestPathResult<T> result;\n \
    \   result.distance.assign(vertex_count, T());\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count <= 1) return result;\n\n    Larsch<T> optimizer(vertex_count\
    \ - 1, [&](int row, int column) {\n        return result.distance[column] + cost(column,\
    \ row + 1);\n    });\n    for (int vertex = 1; vertex < vertex_count; vertex++)\
    \ {\n        int parent = optimizer.next_argmin();\n        result.parent[vertex]\
    \ = parent;\n        result.distance[vertex] = result.distance[parent] + cost(parent,\
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/min_plus_convolution.hpp\"\n\n\n\n#line 7\
    \ \"convex/monge/min_plus_convolution.hpp\"\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 8 \"convex/monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\nnamespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>&\
    \ rows, const std::vector<int>& columns,\n           const Select& select, std::vector<int>&\
    \ answer) {\n    if (rows.empty()) return;\n\n    std::vector<int> reduced;\n\
    \    reduced.reserve(columns.size());\n    for (int column : columns) {\n    \
    \    while (!reduced.empty()) {\n            int row = rows[int(reduced.size())\
    \ - 1];\n            if (!select(row, reduced.back(), column)) break;\n      \
    \      reduced.pop_back();\n        }\n        if (reduced.size() < rows.size())\
    \ reduced.push_back(column);\n    }\n\n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size()\
    \ / 2);\n    for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace convolution_detail {\n\n\
    template <class T, class Compare, class Add>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare, Add add)\
    \ {\n    if (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size\
    \ = int(arbitrary.size());\n    int second_size = int(structured.size());\n  \
    \  int result_size = first_size + second_size - 1;\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= second_size) return true;\n        T\
    \ current_value = add(arbitrary[current], structured[index - current]);\n    \
    \    T candidate_value = add(arbitrary[candidate], structured[index - candidate]);\n\
    \        return !compare(current_value, candidate_value);\n    };\n\n    std::vector<int>\
    \ optima =\n        smawk_detail::row_optima(result_size, first_size, select);\n\
    \    std::vector<T> result;\n    result.reserve(result_size);\n    for (int index\
    \ = 0; index < result_size; index++) {\n        int first_index = optima[index];\n\
    \        result.emplace_back(add(arbitrary[first_index],\n                   \
    \             structured[index - first_index]));\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstd::pair<int, int> finite_interval(const std::vector<T>&\
    \ sequence,\n                                    const T& infinity) {\n    int\
    \ left = 0;\n    while (left < int(sequence.size()) && sequence[left] == infinity)\
    \ left++;\n    int right = int(sequence.size());\n    while (right > left && sequence[right\
    \ - 1] == infinity) right--;\n    return {left, right};\n}\n\ntemplate <class\
    \ T, class Compare>\nstd::vector<T> structured_convolution_with_infinity(\n  \
    \  const std::vector<T>& arbitrary, const std::vector<T>& structured,\n    const\
    \ T& infinity, Compare compare) {\n    if (arbitrary.empty() || structured.empty())\
    \ return {};\n\n    auto [left, right] = finite_interval(structured, infinity);\n\
    \    int result_size = int(arbitrary.size() + structured.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (left == right) return result;\n\n  \
    \  std::vector<int> columns;\n    columns.reserve(arbitrary.size());\n    for\
    \ (int i = 0; i < int(arbitrary.size()); i++) {\n        if (arbitrary[i] != infinity)\
    \ columns.push_back(i);\n    }\n    if (columns.empty()) return result;\n\n  \
    \  int finite_size = right - left;\n    int middle_size = int(arbitrary.size())\
    \ + finite_size - 1;\n    std::vector<int> rows;\n    rows.reserve(middle_size);\n\
    \    int active = 0;\n    for (int row = 0; row < middle_size; row++) {\n    \
    \    if (row < int(arbitrary.size()) && arbitrary[row] != infinity) active++;\n\
    \        if (row >= finite_size && arbitrary[row - finite_size] != infinity) active--;\n\
    \        if (active > 0) rows.push_back(row);\n    }\n\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= finite_size) return true;\n        T\
    \ current_value =\n            arbitrary[current] + structured[left + index -\
    \ current];\n        T candidate_value =\n            arbitrary[candidate] + structured[left\
    \ + index - candidate];\n        return !compare(current_value, candidate_value);\n\
    \    };\n    std::vector<int> optima(middle_size, -1);\n    smawk_detail::solve(rows,\
    \ columns, select, optima);\n    for (int row : rows) {\n        int first_index\
    \ = optima[row];\n        result[left + row] =\n            arbitrary[first_index]\
    \ + structured[left + row - first_index];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T, class Compare>\nstd::vector<T> linear_structured_convolution(const\
    \ std::vector<T>& first,\n                                             const std::vector<T>&\
    \ second,\n                                             Compare compare) {\n \
    \   if (first.empty() || second.empty()) return {};\n\n    int first_size = int(first.size());\n\
    \    int second_size = int(second.size());\n    std::vector<T> result(first_size\
    \ + second_size - 1);\n    result[0] = first[0] + second[0];\n\n    int first_index\
    \ = 1;\n    int second_index = 1;\n    int result_index = 1;\n    while (first_index\
    \ < first_size && second_index < second_size) {\n        T first_difference =\
    \ first[first_index] - first[first_index - 1];\n        T second_difference =\
    \ second[second_index] - second[second_index - 1];\n        if (compare(second_difference,\
    \ first_difference)) {\n            result[result_index] = result[result_index\
    \ - 1] + second_difference;\n            second_index++;\n        } else {\n \
    \           result[result_index] = result[result_index - 1] + first_difference;\n\
    \            first_index++;\n        }\n        result_index++;\n    }\n    while\
    \ (first_index < first_size) {\n        T difference = first[first_index] - first[first_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        first_index++;\n        result_index++;\n    }\n    while (second_index\
    \ < second_size) {\n        T difference = second[second_index] - second[second_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        second_index++;\n        result_index++;\n    }\n    return result;\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> linear_structured_convolution_with_infinity(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity, Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n\n    auto [first_left, first_right] = finite_interval(first, infinity);\n\
    \    auto [second_left, second_right] = finite_interval(second, infinity);\n \
    \   int result_size = int(first.size() + second.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (first_left == first_right || second_left\
    \ == second_right) return result;\n\n    int offset = first_left + second_left;\n\
    \    result[offset] = first[first_left] + second[second_left];\n\n    int first_index\
    \ = first_left + 1;\n    int second_index = second_left + 1;\n    int result_index\
    \ = offset + 1;\n    while (first_index < first_right && second_index < second_right)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (compare(second_difference, first_difference)) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_right) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_right) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T, class Compare>\nbool is_structured_sequence_with_infinity(const\
    \ std::vector<T>& sequence,\n                                          const T&\
    \ infinity, Compare violation) {\n    auto [left, right] = finite_interval(sequence,\
    \ infinity);\n    for (int i = left; i < right; i++) {\n        if (sequence[i]\
    \ == infinity) return false;\n    }\n    for (int i = left + 1; i + 1 < right;\
    \ i++) {\n        T first_difference = sequence[i] - sequence[i - 1];\n      \
    \  T second_difference = sequence[i + 1] - sequence[i];\n        if (violation(first_difference,\
    \ second_difference)) return false;\n    }\n    return true;\n}\n\n}  // namespace\
    \ convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const std::vector<T>&\
    \ sequence) {\n    for (int i = 1; i + 1 < int(sequence.size()); i++) {\n    \
    \    if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {\n  \
    \          return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ T>\nbool is_convex_sequence(const std::vector<T>& sequence, const T& infinity)\
    \ {\n    return convolution_detail::is_structured_sequence_with_infinity(\n  \
    \      sequence, infinity, std::greater<>());\n}\n\ntemplate <class T>\nbool is_concave_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence,\n      \
    \                   const T& negative_infinity) {\n    return convolution_detail::is_structured_sequence_with_infinity(\n\
    \        sequence, negative_infinity, std::less<>());\n}\n\ntemplate <class T>\n\
    std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,\n\
    \                                           const std::vector<T>& convex) {\n\
    \    auto add = [](const T& first, const T& second) { return first + second; };\n\
    \    return convolution_detail::structured_convolution(arbitrary, convex,\n  \
    \                                                    std::less<>(), add);\n}\n\
    \ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const std::vector<T>&\
    \ arbitrary,\n                                           const std::vector<T>&\
    \ convex,\n                                           const T& infinity) {\n \
    \   return convolution_detail::structured_convolution_with_infinity(\n       \
    \ arbitrary, convex, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ min_plus_convolution_convex_convex(const std::vector<T>& first,\n          \
    \                                        const std::vector<T>& second) {\n   \
    \ return convolution_detail::linear_structured_convolution(first, second, std::less<>());\n\
    }\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex_convex(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ max_plus_convolution_concave(const std::vector<T>& arbitrary,\n            \
    \                                const std::vector<T>& concave) {\n    auto add\
    \ = [](const T& first, const T& second) { return first + second; };\n    return\
    \ convolution_detail::structured_convolution(arbitrary, concave,\n           \
    \                                           std::greater<>(), add);\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave(const std::vector<T>&\
    \ arbitrary,\n                                            const std::vector<T>&\
    \ concave,\n                                            const T& negative_infinity)\
    \ {\n    return convolution_detail::structured_convolution_with_infinity(\n  \
    \      arbitrary, concave, negative_infinity, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave_concave(const std::vector<T>&\
    \ first,\n                                                    const std::vector<T>&\
    \ second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave_concave(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ negative_infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, negative_infinity, std::greater<>());\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 11 \"convex/monge/all.hpp\"\n\n\n#line\
    \ 1 \"convex/slope_trick.hpp\"\n\n\n\n#line 7 \"convex/slope_trick.hpp\"\n#include\
    \ <queue>\n#line 11 \"convex/slope_trick.hpp\"\n\nnamespace m1une {\nnamespace\
    \ convex {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n    std::optional<T>\
    \ left;\n    std::optional<T> right;\n};\n\ntemplate <class T>\nclass SlopeTrick\
    \ {\n    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\n  \
    \  T _minimum = T();\n    T _left_offset = T();\n    T _right_offset = T();\n\
    \    std::priority_queue<T> _left;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> _right;\n\n    T left_top() const {\n        return _left.top()\
    \ + _left_offset;\n    }\n\n    T right_top() const {\n        return _right.top()\
    \ + _right_offset;\n    }\n\n    void push_left(T value) {\n        _left.push(value\
    \ - _left_offset);\n    }\n\n    void push_right(T value) {\n        _right.push(value\
    \ - _right_offset);\n    }\n\n   public:\n    SlopeTrick() = default;\n\n    T\
    \ minimum() const {\n        return _minimum;\n    }\n\n    int breakpoint_count()\
    \ const {\n        return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line\
    \ 9 \"convex/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_CONVEX_ALL_HPP

    #define M1UNE_CONVEX_ALL_HPP 1


    #include "alien_trick.hpp"

    #include "convex_hull_trick.hpp"

    #include "li_chao_tree.hpp"

    #include "monge/all.hpp"

    #include "slope_trick.hpp"


    #endif  // M1UNE_CONVEX_ALL_HPP

    '
  dependsOn:
  - convex/alien_trick.hpp
  - convex/convex_hull_trick.hpp
  - convex/li_chao_tree.hpp
  - convex/monge/all.hpp
  - convex/monge/check.hpp
  - convex/monge/divide_and_conquer_optimization.hpp
  - convex/monge/monotone_minima.hpp
  - convex/monge/knuth_optimization.hpp
  - convex/monge/larsch.hpp
  - convex/monge/min_plus_convolution.hpp
  - convex/monge/smawk.hpp
  - convex/slope_trick.hpp
  isVerificationFile: false
  path: convex/all.hpp
  requiredBy: []
  timestamp: '2026-07-07 18:38:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convex/all.hpp
layout: document
title: Convex All
---

## Overview

`convex/all.hpp` includes convex data structures and convex optimization
helpers. The public namespace is `m1une::convex`.

## Included Headers

| Header | Contents |
| --- | --- |
| `convex/alien_trick.hpp` | Exact-count optimization through Lagrangian relaxation. |
| `convex/convex_hull_trick.hpp` | Monotone-slope CHT for minimum or maximum line queries. |
| `convex/li_chao_tree.hpp` | Dynamic Li Chao tree for arbitrary line and line-segment insertion. |
| `convex/monge/all.hpp` | SMAWK, monotone minima, Knuth/D&C DP optimization, LARSCH, Monge checks, and structured min-plus/max-plus convolution. |
| `convex/slope_trick.hpp` | Heap-based slope trick for convex piecewise-linear functions. |
