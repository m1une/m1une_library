---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/alien_trick.hpp
    title: Alien Trick
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/convex_hull_trick.hpp
    title: Convex Hull Trick
  - icon: ':heavy_check_mark:'
    path: convex/li_chao_tree.hpp
    title: Li Chao Tree
  - icon: ':heavy_check_mark:'
    path: convex/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Matrix Primitives and Algorithm Guide
  - icon: ':heavy_check_mark:'
    path: convex/monge/check.hpp
    title: Monge and Anti-Monge Checks
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH Online Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH Online Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  - icon: ':heavy_check_mark:'
    path: convex/monge_shortest_path.hpp
    title: Monge and Anti-Monge Forward DAG Shortest Paths
  - icon: ':heavy_check_mark:'
    path: convex/monge_transition.hpp
    title: Finalized-Layer Matrix Transitions
  - icon: ':heavy_check_mark:'
    path: convex/slope_trick.hpp
    title: Slope Trick
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/convex/monge/ordered_matrix.test.cpp\"\n// No direct\
    \ judge target for explicit matrix-order lists or online LARSCH.\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <numeric>\n#include <random>\n#include <vector>\n#line 1\
    \ \"convex/all.hpp\"\n\n\n\n#line 1 \"convex/alien_trick.hpp\"\n\n\n\n#line 5\
    \ \"convex/alien_trick.hpp\"\n#include <concepts>\n#line 7 \"convex/alien_trick.hpp\"\
    \n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace convex\
    \ {\n\nnamespace detail {\n\ntemplate <std::integral Penalty, std::integral Count,\
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
    \ <optional>\n#line 10 \"convex/convex_hull_trick.hpp\"\n\nnamespace m1une {\n\
    namespace convex {\n\nenum class LineOptimization {\n    Minimize,\n    Maximize,\n\
    };\n\ntemplate <std::signed_integral T>\nusing line_wide_type = __int128_t;\n\n\
    template <std::signed_integral T>\nstruct LinearFunction {\n    using value_type\
    \ = line_wide_type<T>;\n\n    value_type slope;\n    value_type intercept;\n\n\
    \    constexpr LinearFunction() : slope(0), intercept(0) {}\n\n    constexpr LinearFunction(T\
    \ slope_value, T intercept_value) : slope(slope_value), intercept(intercept_value)\
    \ {}\n\n    constexpr value_type operator()(T x) const {\n        return slope\
    \ * value_type(x) + intercept;\n    }\n};\n\n// Convex hull trick for lines inserted\
    \ in nondecreasing slope order.\ntemplate <std::signed_integral T, LineOptimization\
    \ Objective = LineOptimization::Minimize>\nstruct ConvexHullTrick {\n    using\
    \ Line = LinearFunction<T>;\n    using value_type = typename Line::value_type;\n\
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
    \ namespace m1une\n\n\n#line 1 \"convex/min_plus_convolution.hpp\"\n\n\n\n#include\
    \ <functional>\n#line 7 \"convex/min_plus_convolution.hpp\"\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 7 \"convex/monge/smawk.hpp\"\n#include <span>\n#line 9 \"convex/monge/smawk.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace smawk_detail {\n\ntemplate\
    \ <class Select>\nvoid solve(const std::vector<int>& rows, const std::vector<int>&\
    \ columns,\n           const Select& select, std::vector<int>& answer) {\n   \
    \ if (rows.empty()) return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
    \    for (int column : columns) {\n        while (!reduced.empty()) {\n      \
    \      int row = rows[int(reduced.size()) - 1];\n            if (!select(row,\
    \ reduced.back(), column)) break;\n            reduced.pop_back();\n        }\n\
    \        if (reduced.size() < rows.size()) reduced.push_back(column);\n    }\n\
    \n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size() / 2);\n   \
    \ for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
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
    \ // namespace smawk_detail\n\n// Comparison-oracle SMAWK. prefer(row, current,\
    \ candidate) says whether to\n// replace current. The induced ordered matrix must\
    \ be totally monotone with\n// this tie rule. This also permits symbolic invalid\
    \ entries without sentinels.\n// O(H + W) oracle calls and memory. Entries must\
    \ be fixed (offline search).\ntemplate <class Prefer>\nstd::vector<int> smawk_row_select(int\
    \ row_count, int column_count, Prefer prefer) {\n    assert(row_count >= 0);\n\
    \    assert(column_count >= 0);\n    return smawk_detail::row_optima(row_count,\
    \ column_count, prefer);\n}\n\n// Search value(rows[r], columns[c]); answers are\
    \ original column IDs, in row\n// list order. Lists contain distinct nonnegative\
    \ IDs; prefer defines the tie\n// rule with respect to the supplied order.\ntemplate\
    \ <class Prefer>\nstd::vector<int> smawk_row_select(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Prefer prefer)\
    \ {\n    auto answer = smawk_row_select(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int current, int candidate) {\n            return prefer(rows[row],\
    \ columns[current], columns[candidate]);\n        });\n    for (int& column :\
    \ answer) if (column != -1) column = columns[column];\n    return answer;\n}\n\
    \n// Fixed rectangle, leftmost on ties. Requires total monotonicity for leftmost\n\
    // optima under Compare (Monge suffices for minima). O(H + W) time and memory.\n\
    // Callback evaluations may be out of row order; this is not an online DP.\ntemplate\
    \ <class Value, class Compare = std::less<>>\nstd::vector<int> smawk_row_optima(int\
    \ row_count, int column_count, Value value,\n                                \
    \  Compare compare = Compare()) {\n    assert(row_count >= 0);\n    assert(column_count\
    \ >= 0);\n    return smawk_row_select(\n        row_count, column_count,\n   \
    \     [&](int row, int current, int candidate) {\n            return compare(value(row,\
    \ candidate), value(row, current));\n        });\n}\n\ntemplate <class Value>\n\
    std::vector<int> smawk_row_argmin(int row_count, int column_count, Value value)\
    \ {\n    return smawk_row_optima(row_count, column_count, value, std::less<>());\n\
    }\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmax(int row_count,\
    \ int column_count, Value value) {\n    return smawk_row_optima(row_count, column_count,\
    \ value, std::greater<>());\n}\n\n// Ordered variants use supplied positions for\
    \ total monotonicity and ties.\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(std::span<const int> rows,\n               \
    \                   std::span<const int> columns, Value value,\n             \
    \                     Compare compare = Compare()) {\n    return smawk_row_select(rows,\
    \ columns,\n        [&](int row, int current, int candidate) {\n            return\
    \ compare(value(row, candidate), value(row, current));\n        });\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> smawk_row_argmin(std::span<const int> rows,\n\
    \                                  std::span<const int> columns, Value value)\
    \ {\n    return smawk_row_optima(rows, columns, value, std::less<>());\n}\n\n\
    template <class Value>\nstd::vector<int> smawk_row_argmax(std::span<const int>\
    \ rows,\n                                  std::span<const int> columns, Value\
    \ value) {\n    return smawk_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/min_plus_convolution.hpp\"\
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
    \ optima =\n        smawk_row_select(result_size, first_size, select);\n    std::vector<T>\
    \ result;\n    result.reserve(result_size);\n    for (int index = 0; index < result_size;\
    \ index++) {\n        int first_index = optima[index];\n        result.emplace_back(add(arbitrary[first_index],\n\
    \                                structured[index - first_index]));\n    }\n \
    \   return result;\n}\n\ntemplate <class T>\nstd::pair<int, int> finite_interval(const\
    \ std::vector<T>& sequence,\n                                    const T& infinity)\
    \ {\n    int left = 0;\n    while (left < int(sequence.size()) && sequence[left]\
    \ == infinity) left++;\n    int right = int(sequence.size());\n    while (right\
    \ > left && sequence[right - 1] == infinity) right--;\n    return {left, right};\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> structured_convolution_with_infinity(\n\
    \    const std::vector<T>& arbitrary, const std::vector<T>& structured,\n    const\
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
    \    };\n    auto optima = smawk_row_select(rows, columns, select);\n    for (int\
    \ i = 0; i < int(rows.size()); i++) {\n        int row = rows[i];\n        int\
    \ first_index = optima[i];\n        result[left + row] =\n            arbitrary[first_index]\
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
    \ convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/all.hpp\"\n\n\n\n\
    #line 1 \"convex/monge/check.hpp\"\n\n\n\n#line 7 \"convex/monge/check.hpp\"\n\
    \nnamespace m1une {\nnamespace convex {\n\ntemplate <class Value>\nbool is_monge(int\
    \ row_count, int column_count, Value value) {\n    assert(row_count >= 0);\n \
    \   assert(column_count >= 0);\n    if (row_count < 2 || column_count < 2) return\
    \ true;\n    for (int row = 0; row + 1 < row_count; row++) {\n        for (int\
    \ column = 0; column + 1 < column_count; column++) {\n            if (value(row,\
    \ column) + value(row + 1, column + 1) >\n                value(row, column +\
    \ 1) + value(row + 1, column)) {\n                return false;\n            }\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int\
    \ row_count, int column_count, Value value) {\n    return is_monge(row_count,\
    \ column_count,\n        [&](int row, int column) -> decltype(auto) {\n      \
    \      return value(row, column_count - 1 - column);\n        });\n}\n\n// Check\
    \ adjacent 2x2 inequalities in the supplied orders, O(HW) time,\n// O(1) extra\
    \ memory. Distinct nonnegative IDs; arithmetic must not overflow.\ntemplate <class\
    \ Value>\nbool is_monge(std::span<const int> rows, std::span<const int> columns,\
    \ Value value) {\n    return is_monge(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int column) -> decltype(auto) {\n            return value(rows[row],\
    \ columns[column]);\n        });\n}\n\ntemplate <class Value>\nbool is_anti_monge(std::span<const\
    \ int> rows, std::span<const int> columns,\n                   Value value) {\n\
    \    return is_anti_monge(int(rows.size()), int(columns.size()),\n        [&](int\
    \ row, int column) -> decltype(auto) {\n            return value(rows[row], columns[column]);\n\
    \        });\n}\n\ntemplate <class T>\nbool is_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/larsch.hpp\"\
    \n\n\n\n#line 7 \"convex/monge/larsch.hpp\"\n\nnamespace m1une {\nnamespace convex\
    \ {\n\n// Online minima of a lower-triangular totally monotone matrix (column\
    \ <= row).\n// Leftmost ties. Before answering row r, only columns <= r are accessed,\
    \ even\n// when evaluating future rows. Finalize column r+1 after receiving answer\
    \ r.\n// O(N) total time/evaluations/memory; an individual next_argmin can take\
    \ O(N).\n// Value is stored directly, with no type-erased callable. Use CTAD:\
    \ Larsch q(n,f).\ntemplate <class Value>\nclass Larsch {\n    struct Level {\n\
    \        int size;\n        int row = 0;\n        int column_row = 0;\n      \
    \  int boundary = 0;\n        std::vector<int> columns;\n        explicit Level(int\
    \ n) : size(n) {}\n    };\n\n    int _size;\n    Value _value;\n    std::vector<Level>\
    \ _levels;\n\n    auto entry(int depth, int row, int column) {\n        for (int\
    \ d = depth; d > 0; --d) {\n            row = row * 2 + 1;\n            column\
    \ = _levels[d].columns[column];\n        }\n        return _value(row, column);\n\
    \    }\n\n    int next_column(int depth) {\n        auto& level = _levels[depth];\n\
    \        int row = level.column_row++;\n        int first = row == 0 ? 0 : row\
    \ * 2 - 1;\n        for (int column = first; column <= row * 2; ++column) {\n\
    \            while (int(level.columns.size()) != row &&\n                   entry(depth\
    \ - 1, int(level.columns.size()) * 2 - 1,\n                         level.columns.back())\
    \ >\n                   entry(depth - 1, int(level.columns.size()) * 2 - 1, column))\
    \ {\n                level.columns.pop_back();\n            }\n            if\
    \ (int(level.columns.size()) != level.size) {\n                level.columns.push_back(column);\n\
    \            }\n        }\n        return level.columns[next_row(depth)];\n  \
    \  }\n\n    int next_row(int depth) {\n        auto& level = _levels[depth];\n\
    \        int row = level.row++;\n        if (row % 2 != 0) {\n            return\
    \ entry(depth, row, level.boundary) <= entry(depth, row, row)\n              \
    \         ? level.boundary : row;\n        }\n        int previous = level.boundary;\n\
    \        int next = row + 1 == level.size ? level.size - 1\n                 \
    \                       : next_column(depth + 1);\n        level.boundary = next;\n\
    \        int best = previous;\n        for (int column = previous + 1; column\
    \ <= next; ++column) {\n            if (entry(depth, row, column) < entry(depth,\
    \ row, best)) best = column;\n        }\n        return best;\n    }\n\n   public:\n\
    \    explicit Larsch(int size, Value value) : _size(size), _value(std::move(value))\
    \ {\n        assert(size >= 0);\n        for (int n = size; n > 0; n /= 2) {\n\
    \            _levels.emplace_back(n);\n            if (_levels.size() > 1) _levels.back().columns.reserve(n);\n\
    \        }\n    }\n    int size() const { return _size; }\n    int processed_rows()\
    \ const { return _size == 0 ? 0 : _levels[0].row; }\n    bool finished() const\
    \ { return processed_rows() == _size; }\n    int next_argmin() {\n        assert(!finished());\n\
    \        return next_row(0);\n    }\n};\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#line 8 \"convex/monge/monotone_minima.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace monotone_minima_detail\
    \ {\n\ntemplate <class Value, class Compare>\nvoid solve(int row_left, int row_right,\
    \ int column_left, int column_right,\n           const Value& value, const Compare&\
    \ compare, std::vector<int>& answer) {\n    if (row_left == row_right) return;\n\
    \    int row = (row_left + row_right) / 2;\n    int best = column_left;\n    for\
    \ (int column = column_left + 1; column < column_right; column++) {\n        if\
    \ (compare(value(row, column), value(row, best))) best = column;\n    }\n    answer[row]\
    \ = best;\n    solve(row_left, row, column_left, best + 1, value, compare, answer);\n\
    \    solve(row + 1, row_right, best, column_right, value, compare, answer);\n\
    }\n\n}  // namespace monotone_minima_detail\n\n// Fixed rectangular matrix; leftmost\
    \ optimal columns must be nondecreasing.\n// Returns column indices, or -1 when\
    \ there are no columns. Not an online DP.\n// O(H + W log(H+1)) time, O(H + log(H+1))\
    \ memory.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ monotone_row_optima(int row_count, int column_count, Value value,\n        \
    \                             Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    std::vector<int> answer(row_count,\
    \ -1);\n    if (row_count == 0 || column_count == 0) return answer;\n    monotone_minima_detail::solve(0,\
    \ row_count, 0, column_count, value, compare, answer);\n    return answer;\n}\n\
    \ntemplate <class Value>\nstd::vector<int> monotone_row_argmin(int row_count,\
    \ int column_count, Value value) {\n    return monotone_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ monotone_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ monotone_row_optima(row_count, column_count, value, std::greater<>());\n}\n\n\
    // Ordered matrix value(rows[r], columns[c]); return original column IDs in\n\
    // row list order. Leftmost means first in columns. IDs are distinct/nonnegative.\n\
    template <class Value, class Compare = std::less<>>\nstd::vector<int> monotone_row_optima(std::span<const\
    \ int> rows,\n                                     std::span<const int> columns,\
    \ Value value,\n                                     Compare compare = Compare())\
    \ {\n    auto answer = monotone_row_optima(int(rows.size()), int(columns.size()),\n\
    \        [&](int row, int column) -> decltype(auto) {\n            return value(rows[row],\
    \ columns[column]);\n        }, compare);\n    for (int& column : answer) if (column\
    \ != -1) column = columns[column];\n    return answer;\n}\n\ntemplate <class Value>\n\
    std::vector<int> monotone_row_argmin(std::span<const int> rows,\n            \
    \                         std::span<const int> columns, Value value) {\n    return\
    \ monotone_row_optima(rows, columns, value, std::less<>());\n}\n\ntemplate <class\
    \ Value>\nstd::vector<int> monotone_row_argmax(std::span<const int> rows,\n  \
    \                                   std::span<const int> columns, Value value)\
    \ {\n    return monotone_row_optima(rows, columns, value, std::greater<>());\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return monotone_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 8 \"convex/monge/all.hpp\"\
    \n\n\n#line 1 \"convex/monge_shortest_path.hpp\"\n\n\n\n#line 8 \"convex/monge_shortest_path.hpp\"\
    \n\n#line 11 \"convex/monge_shortest_path.hpp\"\n\nnamespace m1une {\nnamespace\
    \ convex {\n\ntemplate <class T>\nstruct MongeShortestPathResult {\n    std::vector<T>\
    \ distance;\n    std::vector<int> parent;\n};\n\n// Same-array forward recurrence:\
    \ dp[j] = min(dp[i] + cost(i,j)), j-i >= D.\n// Finite Monge costs on every fully\
    \ valid rectangle. Smallest parent on ties.\n// O(N) time/evaluations/memory,\
    \ for any D >= 1. Never evaluates invalid edges\n// or adds infinity. Vertices\
    \ 1..D-1 are unreachable; all vertices >=D are reachable.\ntemplate <class T,\
    \ class Cost>\nMongeShortestPathResult<T> monge_shortest_path(\n    int vertex_count,\
    \ Cost cost, T infinity, int minimum_step = 1) {\n    assert(vertex_count >= 0);\n\
    \    assert(minimum_step >= 1);\n    assert(T() < infinity);\n    MongeShortestPathResult<T>\
    \ result;\n    result.distance.assign(vertex_count, infinity);\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count == 0) return result;\n    result.distance[0] = T();\n\
    \    if (minimum_step >= vertex_count) return result;\n\n    // D=minimum_step\
    \ < vertex_count here. Row r targets r+D, with\n    // 0 <= r < vertex_count-D,\
    \ so r+D <= vertex_count-1 cannot overflow.\n    // The source map 0,...,0,D,D+1,...\
    \ is nondecreasing: early columns\n    // duplicate source 0 instead of unreachable\
    \ sources 1..D-1.\n    // LARSCH queries c <= r; source(c) <= c makes every edge\
    \ satisfy the step.\n    // While answering row q it uses only c <= q, whose mapped\
    \ sources are\n    // already finalized before target q+D. Duplicating ordered\
    \ columns and\n    // adding their finalized distance constants both preserve\
    \ Monge.\n    auto source = [&](int column) { return column < minimum_step ? 0\
    \ : column; };\n    Larsch optimizer(vertex_count - minimum_step, [&](int row,\
    \ int column) -> T {\n        int from = source(column);\n        return result.distance[from]\
    \ + cost(from, row + minimum_step);\n    });\n    for (int to = minimum_step;\
    \ to < vertex_count; ++to) {\n        int from = source(optimizer.next_argmin());\n\
    \        result.parent[to] = from;\n        result.distance[to] = result.distance[from]\
    \ + cost(from, to);\n    }\n    return result;\n}\n\n// dist[j] = min(dist[i]\
    \ + cost(i, j)), where j - i >= minimum_step.\n// Same-array recurrence. Finite\
    \ anti-Monge costs on every valid rectangle.\n// Largest parent on ties; O(N)\
    \ memory. See docs for the numeric contract.\n// O(N log N + N * minimum_step)\
    \ time for O(1) cost evaluations.\n// In particular, minimum_step = 1 or 2 gives\
    \ O(N log N) time.\ntemplate <class T, class Cost>\nMongeShortestPathResult<T>\
    \ anti_monge_shortest_path(\n    int vertex_count, Cost cost, T infinity, int\
    \ minimum_step = 1) {\n    assert(vertex_count >= 0);\n    assert(minimum_step\
    \ >= 1);\n    assert(T() < infinity);\n\n    MongeShortestPathResult<T> result;\n\
    \    result.distance.assign(vertex_count, infinity);\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count == 0) return result;\n    result.distance[0] = T();\n\
    \    if (minimum_step >= vertex_count) return result;\n\n    auto relax = [&](int\
    \ from, int to) {\n        if (result.distance[from] == infinity) return;\n  \
    \      T candidate = result.distance[from] + cost(from, to);\n        if (candidate\
    \ < result.distance[to] ||\n            (candidate == result.distance[to] && from\
    \ > result.parent[to])) {\n            result.distance[to] = candidate;\n    \
    \        result.parent[to] = from;\n        }\n    };\n\n    // All pairs in this\
    \ rectangle are valid. Remove unreachable columns,\n    // then reverse the remaining\
    \ columns to turn anti-Monge into Monge.\n    auto rectangle = [&](int first,\
    \ int last, int top, int bottom) {\n        if (first == last || top == bottom)\
    \ return;\n        std::vector<int> sources;\n        for (int from = last; from\
    \ > first;) {\n            --from;\n            if (result.distance[from] != infinity)\
    \ sources.push_back(from);\n        }\n        if (sources.empty()) return;\n\
    \        if (sources.size() == 1) {\n            for (int to = top; to < bottom;\
    \ to++) relax(sources[0], to);\n            return;\n        }\n        std::vector<int>\
    \ targets(bottom - top);\n        std::iota(targets.begin(), targets.end(), top);\n\
    \        auto argmin = smawk_row_argmin(targets, sources, [&](int to, int from)\
    \ -> T {\n            return result.distance[from] + cost(from, to);\n       \
    \ });\n        for (int row = 0; row < bottom - top; row++) relax(argmin[row],\
    \ top + row);\n    };\n\n    auto solve = [&](auto& self, int left, int right)\
    \ -> void {\n        // Such a block contains no valid internal edge.\n      \
    \  if (right - left <= minimum_step) return;\n        int middle = left + (right\
    \ - left) / 2;\n        self(self, left, middle);\n\n        // Two valid rectangles\
    \ and a small corner partition the cross edges.\n        int source_end = std::max(left,\
    \ middle - (minimum_step - 1));\n        int target_begin = middle + std::min(right\
    \ - middle, minimum_step - 1);\n        rectangle(left, middle, target_begin,\
    \ right);\n        rectangle(left, source_end, middle, target_begin);\n      \
    \  for (int from = source_end; from < middle; from++) {\n            // Subtraction\
    \ avoids overflow when minimum_step is large.\n            if (minimum_step >=\
    \ target_begin - from) continue;\n            for (int to = std::max(middle, from\
    \ + minimum_step);\n                 to < target_begin; to++) {\n            \
    \    relax(from, to);\n            }\n        }\n\n        // Incoming transitions\
    \ must be applied BEFORE solving the right half.\n        self(self, middle, right);\n\
    \    };\n    solve(solve, 0, vertex_count);\n    return result;\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge_transition.hpp\"\n\
    \n\n\n#line 9 \"convex/monge_transition.hpp\"\n\n#line 12 \"convex/monge_transition.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct MatrixTransitionResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\nnamespace\
    \ monge_transition_detail {\n\ntemplate <class T, class Cost, class Source, class\
    \ Target, class Search>\nauto solve(const std::vector<T>& previous, int targets,\
    \ int sources, Cost cost,\n           Source source, Target target, Search search)\
    \ {\n    using R = std::decay_t<decltype(previous[0] + cost(0, 0))>;\n    auto\
    \ value = [&](int row, int column) -> R {\n        return previous[source(column)]\
    \ + cost(source(column), target(row));\n    };\n    MatrixTransitionResult<R>\
    \ result;\n    result.argmin = search(targets, sources, value);\n    result.value.resize(targets);\n\
    \    for (int row = 0; row < targets; ++row) {\n        int& column = result.argmin[row];\n\
    \        if (column == -1) continue;\n        result.value[row] = value(row, column);\n\
    \        column = source(column);\n    }\n    return result;\n}\n\n}  // namespace\
    \ monge_transition_detail\n\n// Offline layer: g[j] = min_i(previous[i] + cost(i,j));\
    \ previous is finalized.\n// Leftmost minimizing sources must be nondecreasing\
    \ with target index. This is\n// weaker than total monotonicity. O(H + W log(H+1))\
    \ time, O(H) result memory.\n// Ties select smallest source. Empty sources give\
    \ argmin=-1, value=R().\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous, int state_count, Cost cost) {\n    auto identity =\
    \ [](int i) { return i; };\n    return monge_transition_detail::solve(previous,\
    \ state_count, int(previous.size()),\n        cost, identity, identity, [](int\
    \ h, int w, auto value) {\n            return monotone_row_argmin(h, w, value);\n\
    \        });\n}\n\n// Same offline recurrence, with finite Monge cost(source,target).\
    \ Adding source\n// constants preserves Monge. O(H+W) time/memory; smallest source\
    \ on ties.\ntemplate <class T, class Cost>\nauto monge_transition(const std::vector<T>&\
    \ previous, int state_count, Cost cost) {\n    auto identity = [](int i) { return\
    \ i; };\n    return monge_transition_detail::solve(previous, state_count, int(previous.size()),\n\
    \        cost, identity, identity, [](int h, int w, auto value) {\n          \
    \  return smawk_row_argmin(h, w, value);\n        });\n}\n\n// Anti-Monge specialization:\
    \ reverse source order internally. Largest source\n// on ties; O(H+W) time/memory.\
    \ All source-target pairs must be legal and finite.\ntemplate <class T, class\
    \ Cost>\nauto anti_monge_transition(const std::vector<T>& previous, int state_count,\
    \ Cost cost) {\n    int width = int(previous.size());\n    return monge_transition_detail::solve(previous,\
    \ state_count, width, cost,\n        [=](int i) { return width - 1 - i; }, [](int\
    \ i) { return i; },\n        [](int h, int w, auto value) { return smawk_row_argmin(h,\
    \ w, value); });\n}\n\n// Ordered variants: the virtual matrix is previous[sources[c]]\
    \ +\n// cost(sources[c], targets[r]). Return original source IDs, in target list\
    \ order.\n// IDs must be distinct/nonnegative; sources must index previous. Ties\
    \ choose the\n// first source in the supplied order. No same-array recurrence\
    \ is computed.\ntemplate <class T, class Cost>\nauto monotone_transition(const\
    \ std::vector<T>& previous,\n                         std::span<const int> targets,\
    \ std::span<const int> sources,\n                         Cost cost) {\n    for\
    \ (int i : sources) { assert(0 <= i && i < int(previous.size())); (void)i; }\n\
    \    for (int j : targets) { assert(j >= 0); (void)j; }\n    return monge_transition_detail::solve(previous,\
    \ int(targets.size()),\n        int(sources.size()), cost, [&](int i) { return\
    \ sources[i]; },\n        [&](int i) { return targets[i]; },\n        [](int h,\
    \ int w, auto value) { return monotone_row_argmin(h, w, value); });\n}\n\ntemplate\
    \ <class T, class Cost>\nauto monge_transition(const std::vector<T>& previous,\n\
    \                      std::span<const int> targets, std::span<const int> sources,\n\
    \                      Cost cost) {\n    for (int i : sources) { assert(0 <= i\
    \ && i < int(previous.size())); (void)i; }\n    for (int j : targets) { assert(j\
    \ >= 0); (void)j; }\n    return monge_transition_detail::solve(previous, int(targets.size()),\n\
    \        int(sources.size()), cost, [&](int i) { return sources[i]; },\n     \
    \   [&](int i) { return targets[i]; },\n        [](int h, int w, auto value) {\
    \ return smawk_row_argmin(h, w, value); });\n}\n\n}  // namespace convex\n}  //\
    \ namespace m1une\n\n\n#line 1 \"convex/slope_trick.hpp\"\n\n\n\n#line 7 \"convex/slope_trick.hpp\"\
    \n#include <queue>\n#line 11 \"convex/slope_trick.hpp\"\n\nnamespace m1une {\n\
    namespace convex {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n    std::optional<T>\
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
    \ 12 \"convex/all.hpp\"\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5\
    \ \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#include\
    \ <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n#include\
    \ <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n#line\
    \ 20 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\n\
    struct FastOutput;\n\nnamespace internal {\n\n// Shared with the convenience helpers\
    \ in template.hpp.\ninline FastOutput* standard_output_instance = nullptr;\n\n\
    // Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n    std::string* _capture = nullptr;\n\n    template\
    \ <class T>\n    std::string format_cell(const T& value) {\n        std::string\
    \ result;\n        struct CaptureGuard {\n            std::string*& target;\n\
    \            std::string* previous;\n            ~CaptureGuard() { target = previous;\
    \ }\n        } guard{_capture, _capture};\n        _capture = &result;\n     \
    \   write(value);\n        return result;\n    }\n\n    template <class Matrix>\n\
    \    void write_aligned_matrix(const Matrix& matrix) {\n        std::vector<std::vector<std::string>>\
    \ rows;\n        std::vector<std::size_t> widths;\n        for (const auto& row\
    \ : matrix) {\n            auto& cells = rows.emplace_back();\n            std::size_t\
    \ column = 0;\n            for (const auto& value : row) {\n                cells.push_back(format_cell(value));\n\
    \                if (column == widths.size()) widths.push_back(0);\n         \
    \       widths[column] = std::max(widths[column], cells.back().size());\n    \
    \            ++column;\n            }\n        }\n        bool first = true;\n\
    \        for (const auto& row : rows) {\n            if (!first) write_char('\\\
    n');\n            first = false;\n            for (std::size_t column = 0; column\
    \ < row.size(); ++column) {\n                if (column != 0) write_char(_range_separator);\n\
    \                for (std::size_t padding = row[column].size();\n            \
    \         padding < widths[column]; ++padding) {\n                    write_char('\
    \ ');\n                }\n                write(row[column]);\n            }\n\
    \        }\n    }\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream),\n          _position(0),\n          _precision(6),\n\
    \          _float_format(std::chars_format::general),\n          _range_separator('\
    \ ') {\n        if (_stream == stdout\n            && internal::standard_output_instance\
    \ == nullptr) {\n            internal::standard_output_instance = this;\n    \
    \    }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \        if (internal::standard_output_instance == this) {\n            internal::standard_output_instance\
    \ = nullptr;\n        }\n    }\n\n    void flush() {\n        if (_position !=\
    \ 0) {\n            std::fwrite(_buffer, 1, _position, _stream);\n           \
    \ _position = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void\
    \ write_char(char c) {\n        if (_capture != nullptr) {\n            _capture->push_back(c);\n\
    \            return;\n        }\n        if (_position == buffer_size) flush();\n\
    \        _buffer[_position++] = c;\n    }\n\n    void write(const char* s) {\n\
    \        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        if (_capture != nullptr) {\n            _capture->append(s);\n\
    \            return;\n        }\n        std::size_t position = 0;\n        while\
    \ (position < s.size()) {\n            if (_position == buffer_size) flush();\n\
    \            const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_capture\
    \ == nullptr && _position > buffer_size - 64) flush();\n        char captured[64];\n\
    \        char* const begin = _capture != nullptr ? captured : _buffer + _position;\n\
    \        char* destination = begin;\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) *destination++ = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(destination, digits, 4);\n            destination +=\
    \ 4;\n        }\n        if (_capture != nullptr) {\n            _capture->append(begin,\
    \ destination - begin);\n        } else {\n            _position += int(destination\
    \ - begin);\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class Matrix>\n   \
    \ void write_aligned(const Matrix& matrix) {\n        using Row = internal::range_stored_value_t<const\
    \ Matrix>;\n        using Cell = internal::range_stored_value_t<const Row>;\n\
    \        static_assert(internal::is_range_v<Row> && !internal::is_string_like_v<Row>,\n\
    \                      \"write_aligned requires a two-dimensional range\");\n\
    \        static_assert(!internal::is_range_v<Cell> || internal::is_string_like_v<Cell>,\n\
    \                      \"write_aligned requires scalar cells\");\n        write_aligned_matrix(matrix);\n\
    \    }\n\n    template <class Matrix>\n    void println_aligned(const Matrix&\
    \ matrix) {\n        write_aligned(matrix);\n        write_char('\\n');\n    }\n\
    \n    template <class... Args>\n    void println(const Args&... args) {\n    \
    \    print(args...);\n        write_char('\\n');\n    }\n\n    template <class\
    \ T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n  \
    \      return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 11 \"verify/convex/monge/ordered_matrix.test.cpp\"\n\nvoid\
    \ test_orders() {\n    std::mt19937 rng(712367);\n    for (int h = 0; h <= 30;\
    \ ++h) for (int w = 0; w <= 30; ++w) {\n        // Sparse IDs in independently\
    \ shuffled orders: answers must be compact\n        // in row order, contain original\
    \ IDs, and never query unlisted cells.\n        std::vector<int> rows(h), cols(w),\
    \ row_rank(3*h+1, -1), col_rank(4*w+1, -1);\n        for (int r = 0; r < h; ++r)\
    \ rows[r] = 3*r+1;\n        for (int c = 0; c < w; ++c) cols[c] = 4*c+2;\n   \
    \     std::shuffle(rows.begin(), rows.end(), rng);\n        std::shuffle(cols.begin(),\
    \ cols.end(), rng);\n        for (int r = 0; r < h; ++r) row_rank[rows[r]] = r;\n\
    \        for (int c = 0; c < w; ++c) col_rank[cols[c]] = c;\n        std::vector<std::vector<long\
    \ long>> matrix(h, std::vector<long long>(w));\n        if (h && w) {\n      \
    \      for (int r = 0; r < h; ++r) matrix[r][0] = int(rng()%31)-15;\n        \
    \    for (int c = 0; c < w; ++c) matrix[0][c] = int(rng()%31)-15;\n          \
    \  for (int r = 1; r < h; ++r) for (int c = 1; c < w; ++c)\n                matrix[r][c]\
    \ = matrix[r-1][c]+matrix[r][c-1]-matrix[r-1][c-1]-int(rng()%4);\n        }\n\
    \        auto value = [&](int r, int c) {\n            assert(row_rank[r] >= 0\
    \ && col_rank[c] >= 0);\n            return matrix[row_rank[r]][col_rank[c]];\n\
    \        };\n        std::vector<int> expected(h, -1);\n        for (int r = 0;\
    \ r < h; ++r) for (int c : cols) {\n            if (expected[r] == -1 || value(rows[r],\
    \ c) < value(rows[r], expected[r]))\n                expected[r] = c;\n      \
    \  }\n        assert(m1une::convex::is_monge(rows, cols, value));\n        assert(m1une::convex::smawk_row_argmin(rows,\
    \ cols, value) == expected);\n        assert(m1une::convex::monotone_row_argmin(rows,\
    \ cols, value) == expected);\n        auto negative = [&](int r, int c) { return\
    \ -value(r,c); };\n        assert(m1une::convex::is_anti_monge(rows, cols, negative));\n\
    \        assert(m1une::convex::smawk_row_argmax(rows, cols, negative) == expected);\n\
    \        assert(m1une::convex::monotone_row_argmax(rows, cols, negative) == expected);\n\
    \        auto oracle = [&](int r, int a, int b) { return value(r,b) < value(r,a);\
    \ };\n        assert(m1une::convex::smawk_row_select(rows, cols, oracle) == expected);\n\
    \n        std::vector<long long> previous(4*w+1);\n        for (int c : cols)\
    \ previous[c] = int(rng()%81) - 40;\n        auto cost = [&](int source, int target)\
    \ { return value(target, source); };\n        auto result = m1une::convex::monge_transition(previous,\
    \ rows, cols, cost);\n        auto monotone = m1une::convex::monotone_transition(previous,\
    \ rows, cols, cost);\n        assert(result.value == monotone.value && result.argmin\
    \ == monotone.argmin);\n        for (int r = 0; r < h; ++r) {\n            int\
    \ best = -1;\n            for (int c : cols) {\n                if (best == -1\
    \ || previous[c]+cost(c,rows[r]) < previous[best]+cost(best,rows[r])) best = c;\n\
    \            }\n            assert(result.argmin[r] == best);\n            if\
    \ (best != -1) assert(result.value[r] == previous[best]+cost(best,rows[r]));\n\
    \            else assert(result.value[r] == 0);\n        }\n        auto ties\
    \ = [](int, int) { return 0; };\n        assert(m1une::convex::smawk_row_argmin(rows,\
    \ cols, ties) ==\n               std::vector<int>(h, w ? cols[0] : -1));\n   \
    \     std::fill(previous.begin(), previous.end(), 0);\n        auto tied = m1une::convex::monge_transition(previous,\
    \ rows, cols, ties);\n        assert(tied.argmin == std::vector<int>(h, w ? cols[0]\
    \ : -1));\n    }\n}\n\nvoid test_direct_anti_monge() {\n    std::mt19937 rng(981234);\n\
    \    for (int h = 0; h <= 40; ++h) for (int w = 0; w <= 40; ++w) {\n        std::vector<long\
    \ long> previous(w);\n        for (auto& v : previous) v = int(rng()%51)-25;\n\
    \        auto cost = [](int i, int j) { return -(i-j)*1LL*(i-j); };\n        auto\
    \ result = m1une::convex::anti_monge_transition(previous, h, cost);\n        for\
    \ (int j = 0; j < h; ++j) {\n            int best = -1;\n            for (int\
    \ i = 0; i < w; ++i) {\n                if (best == -1 || previous[i]+cost(i,j)\
    \ <= previous[best]+cost(best,j)) best = i;\n            }\n            assert(result.argmin[j]\
    \ == best);\n            if (best != -1) assert(result.value[j] == previous[best]+cost(best,j));\n\
    \        }\n        auto ties = m1une::convex::anti_monge_transition(std::vector<int>(w),\
    \ h,\n            [](int, int) { return 0; });\n        assert(ties.argmin ==\
    \ std::vector<int>(h, w-1));\n    }\n}\n\nint main() {\n    test_orders();\n \
    \   test_direct_anti_monge();\n    m1une::utilities::FastInput in;\n    m1une::utilities::FastOutput\
    \ out;\n    long long a, b;\n    in >> a >> b;\n    out << a+b << '\\n';\n}\n"
  code: "// No direct judge target for explicit matrix-order lists or online LARSCH.\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <random>\n#include <vector>\n\
    #include \"../../../convex/all.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nvoid test_orders() {\n    std::mt19937 rng(712367);\n    for (int h = 0; h\
    \ <= 30; ++h) for (int w = 0; w <= 30; ++w) {\n        // Sparse IDs in independently\
    \ shuffled orders: answers must be compact\n        // in row order, contain original\
    \ IDs, and never query unlisted cells.\n        std::vector<int> rows(h), cols(w),\
    \ row_rank(3*h+1, -1), col_rank(4*w+1, -1);\n        for (int r = 0; r < h; ++r)\
    \ rows[r] = 3*r+1;\n        for (int c = 0; c < w; ++c) cols[c] = 4*c+2;\n   \
    \     std::shuffle(rows.begin(), rows.end(), rng);\n        std::shuffle(cols.begin(),\
    \ cols.end(), rng);\n        for (int r = 0; r < h; ++r) row_rank[rows[r]] = r;\n\
    \        for (int c = 0; c < w; ++c) col_rank[cols[c]] = c;\n        std::vector<std::vector<long\
    \ long>> matrix(h, std::vector<long long>(w));\n        if (h && w) {\n      \
    \      for (int r = 0; r < h; ++r) matrix[r][0] = int(rng()%31)-15;\n        \
    \    for (int c = 0; c < w; ++c) matrix[0][c] = int(rng()%31)-15;\n          \
    \  for (int r = 1; r < h; ++r) for (int c = 1; c < w; ++c)\n                matrix[r][c]\
    \ = matrix[r-1][c]+matrix[r][c-1]-matrix[r-1][c-1]-int(rng()%4);\n        }\n\
    \        auto value = [&](int r, int c) {\n            assert(row_rank[r] >= 0\
    \ && col_rank[c] >= 0);\n            return matrix[row_rank[r]][col_rank[c]];\n\
    \        };\n        std::vector<int> expected(h, -1);\n        for (int r = 0;\
    \ r < h; ++r) for (int c : cols) {\n            if (expected[r] == -1 || value(rows[r],\
    \ c) < value(rows[r], expected[r]))\n                expected[r] = c;\n      \
    \  }\n        assert(m1une::convex::is_monge(rows, cols, value));\n        assert(m1une::convex::smawk_row_argmin(rows,\
    \ cols, value) == expected);\n        assert(m1une::convex::monotone_row_argmin(rows,\
    \ cols, value) == expected);\n        auto negative = [&](int r, int c) { return\
    \ -value(r,c); };\n        assert(m1une::convex::is_anti_monge(rows, cols, negative));\n\
    \        assert(m1une::convex::smawk_row_argmax(rows, cols, negative) == expected);\n\
    \        assert(m1une::convex::monotone_row_argmax(rows, cols, negative) == expected);\n\
    \        auto oracle = [&](int r, int a, int b) { return value(r,b) < value(r,a);\
    \ };\n        assert(m1une::convex::smawk_row_select(rows, cols, oracle) == expected);\n\
    \n        std::vector<long long> previous(4*w+1);\n        for (int c : cols)\
    \ previous[c] = int(rng()%81) - 40;\n        auto cost = [&](int source, int target)\
    \ { return value(target, source); };\n        auto result = m1une::convex::monge_transition(previous,\
    \ rows, cols, cost);\n        auto monotone = m1une::convex::monotone_transition(previous,\
    \ rows, cols, cost);\n        assert(result.value == monotone.value && result.argmin\
    \ == monotone.argmin);\n        for (int r = 0; r < h; ++r) {\n            int\
    \ best = -1;\n            for (int c : cols) {\n                if (best == -1\
    \ || previous[c]+cost(c,rows[r]) < previous[best]+cost(best,rows[r])) best = c;\n\
    \            }\n            assert(result.argmin[r] == best);\n            if\
    \ (best != -1) assert(result.value[r] == previous[best]+cost(best,rows[r]));\n\
    \            else assert(result.value[r] == 0);\n        }\n        auto ties\
    \ = [](int, int) { return 0; };\n        assert(m1une::convex::smawk_row_argmin(rows,\
    \ cols, ties) ==\n               std::vector<int>(h, w ? cols[0] : -1));\n   \
    \     std::fill(previous.begin(), previous.end(), 0);\n        auto tied = m1une::convex::monge_transition(previous,\
    \ rows, cols, ties);\n        assert(tied.argmin == std::vector<int>(h, w ? cols[0]\
    \ : -1));\n    }\n}\n\nvoid test_direct_anti_monge() {\n    std::mt19937 rng(981234);\n\
    \    for (int h = 0; h <= 40; ++h) for (int w = 0; w <= 40; ++w) {\n        std::vector<long\
    \ long> previous(w);\n        for (auto& v : previous) v = int(rng()%51)-25;\n\
    \        auto cost = [](int i, int j) { return -(i-j)*1LL*(i-j); };\n        auto\
    \ result = m1une::convex::anti_monge_transition(previous, h, cost);\n        for\
    \ (int j = 0; j < h; ++j) {\n            int best = -1;\n            for (int\
    \ i = 0; i < w; ++i) {\n                if (best == -1 || previous[i]+cost(i,j)\
    \ <= previous[best]+cost(best,j)) best = i;\n            }\n            assert(result.argmin[j]\
    \ == best);\n            if (best != -1) assert(result.value[j] == previous[best]+cost(best,j));\n\
    \        }\n        auto ties = m1une::convex::anti_monge_transition(std::vector<int>(w),\
    \ h,\n            [](int, int) { return 0; });\n        assert(ties.argmin ==\
    \ std::vector<int>(h, w-1));\n    }\n}\n\nint main() {\n    test_orders();\n \
    \   test_direct_anti_monge();\n    m1une::utilities::FastInput in;\n    m1une::utilities::FastOutput\
    \ out;\n    long long a, b;\n    in >> a >> b;\n    out << a+b << '\\n';\n}\n"
  dependsOn:
  - convex/all.hpp
  - convex/alien_trick.hpp
  - convex/convex_hull_trick.hpp
  - convex/li_chao_tree.hpp
  - convex/min_plus_convolution.hpp
  - convex/monge/smawk.hpp
  - convex/monge/all.hpp
  - convex/monge/check.hpp
  - convex/monge/larsch.hpp
  - convex/monge/monotone_minima.hpp
  - convex/monge/smawk.hpp
  - convex/monge_shortest_path.hpp
  - convex/monge/larsch.hpp
  - convex/monge_transition.hpp
  - convex/monge/monotone_minima.hpp
  - convex/slope_trick.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/convex/monge/ordered_matrix.test.cpp
  requiredBy: []
  timestamp: '2026-10-30 16:04:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/convex/monge/ordered_matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/convex/monge/ordered_matrix.test.cpp
- /verify/verify/convex/monge/ordered_matrix.test.cpp.html
title: verify/convex/monge/ordered_matrix.test.cpp
---
