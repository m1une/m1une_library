---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/anti_monge_shortest_path.hpp
    title: Anti-Monge DAG Shortest Paths
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
  _extendedRequiredBy:
  - icon: ':warning:'
    path: convex/all.hpp
    title: Convex All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/all.hpp\"\n\n\n\n#line 1 \"convex/monge/anti_monge_shortest_path.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n#line 1\
    \ \"convex/monge/smawk.hpp\"\n\n\n\n#line 5 \"convex/monge/smawk.hpp\"\n#include\
    \ <functional>\n#include <numeric>\n#line 8 \"convex/monge/smawk.hpp\"\n\nnamespace\
    \ m1une {\nnamespace convex {\n\nnamespace smawk_detail {\n\ntemplate <class Select>\n\
    void solve(const std::vector<int>& rows, const std::vector<int>& columns,\n  \
    \         const Select& select, std::vector<int>& answer) {\n    if (rows.empty())\
    \ return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
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
    \ // namespace smawk_detail\n\n// Search a fixed H x W rectangle, returning column\
    \ indices (leftmost on ties).\n// Requires total monotonicity under Compare; Monge\
    \ suffices for minima.\n// For anti-Monge minima, reverse columns in value and\
    \ map indices back.\n// O(H + W) evaluations; callbacks may be queried out of\
    \ row order.\ntemplate <class Value, class Compare = std::less<>>\nstd::vector<int>\
    \ smawk_row_optima(int row_count, int column_count, Value value,\n           \
    \                       Compare compare = Compare()) {\n    assert(row_count >=\
    \ 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/anti_monge_shortest_path.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct AntiMongeShortestPathResult\
    \ {\n    std::vector<T> distance;\n    std::vector<int> parent;\n};\n\n// dist[j]\
    \ = min(dist[i] + cost(i, j)), where j - i >= minimum_step.\n// cost must be finite\
    \ and anti-Monge on valid rectangles; see the docs.\n// O(N log N + N * minimum_step)\
    \ time for O(1) cost evaluations.\n// In particular, minimum_step = 1 or 2 gives\
    \ O(N log N) time.\ntemplate <class T, class Cost>\nAntiMongeShortestPathResult<T>\
    \ anti_monge_shortest_path(\n    int vertex_count, Cost cost, T infinity, int\
    \ minimum_step = 1) {\n    assert(vertex_count >= 0);\n    assert(minimum_step\
    \ >= 1);\n    assert(T() < infinity);\n\n    AntiMongeShortestPathResult<T> result;\n\
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
    \ to++) relax(sources[0], to);\n            return;\n        }\n        auto argmin\
    \ = smawk_row_argmin(\n            bottom - top, int(sources.size()), [&](int\
    \ row, int column) -> T {\n                int from = sources[column];\n     \
    \           return result.distance[from] + cost(from, top + row);\n          \
    \  });\n        for (int row = 0; row < bottom - top; row++) {\n            relax(sources[argmin[row]],\
    \ top + row);\n        }\n    };\n\n    auto solve = [&](auto& self, int left,\
    \ int right) -> void {\n        // Such a block contains no valid internal edge.\n\
    \        if (right - left <= minimum_step) return;\n        int middle = left\
    \ + (right - left) / 2;\n        self(self, left, middle);\n\n        // Two valid\
    \ rectangles and a small corner partition the cross edges.\n        int source_end\
    \ = std::max(left, middle - (minimum_step - 1));\n        int target_begin = middle\
    \ + std::min(right - middle, minimum_step - 1);\n        rectangle(left, middle,\
    \ target_begin, right);\n        rectangle(left, source_end, middle, target_begin);\n\
    \        for (int from = source_end; from < middle; from++) {\n            //\
    \ Subtraction avoids overflow when minimum_step is large.\n            if (minimum_step\
    \ >= target_begin - from) continue;\n            for (int to = std::max(middle,\
    \ from + minimum_step);\n                 to < target_begin; to++) {\n       \
    \         relax(from, to);\n            }\n        }\n\n        // Incoming transitions\
    \ must be applied BEFORE solving the right half.\n        self(self, middle, right);\n\
    \    };\n    solve(solve, 0, vertex_count);\n    return result;\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/check.hpp\"\n\n\n\n\
    #line 6 \"convex/monge/check.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\n\
    template <class Value>\nbool is_monge(int row_count, int column_count, Value value)\
    \ {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int\
    \ row = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column\
    \ + 1 < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) >\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class Value>\nbool is_anti_monge(int row_count,\
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
    \n#include <type_traits>\n#include <utility>\n#line 7 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\n#line 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#line 7 \"convex/monge/monotone_minima.hpp\"\
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
    \ there are no columns. Not an online DP.\n// Anti-Monge minima require reversing\
    \ one axis before using this routine.\ntemplate <class Value, class Compare =\
    \ std::less<>>\nstd::vector<int> monotone_row_optima(int row_count, int column_count,\
    \ Value value,\n                                     Compare compare = Compare())\
    \ {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n    monotone_minima_detail::solve(0, row_count, 0, column_count, value,\
    \ compare, answer);\n    return answer;\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ monotone_row_argmin(int row_count, int column_count, Value value) {\n    return\
    \ monotone_row_optima(row_count, column_count, value, std::less<>());\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmax(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmin(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return monotone_row_argmin(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmax(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmax(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\ntemplate <class\
    \ Value>\nauto divide_and_conquer_dp(int state_count, int candidate_count, Value\
    \ value)\n    -> DivideAndConquerDpResult<\n        std::decay_t<std::invoke_result_t<Value,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;\n\
    \    DivideAndConquerDpResult<T> result;\n    result.argmin = monotone_row_argmin(state_count,\
    \ candidate_count, value);\n    result.value.resize(state_count);\n    for (int\
    \ state = 0; state < state_count; state++) {\n        if (result.argmin[state]\
    \ != -1) {\n            result.value[state] = value(state, result.argmin[state]);\n\
    \        }\n    }\n    return result;\n}\n\n// One transition from a finalized\
    \ previous layer. This does not compute a\n// same-array recurrence dp[j] = min_i(dp[i]\
    \ + cost(i,j)).\n// Leftmost minimizing candidates must be nondecreasing with\
    \ the state index.\ntemplate <class T, class Cost>\nauto divide_and_conquer_transition(const\
    \ std::vector<T>& previous, int state_count,\n                               \
    \    Cost cost)\n    -> DivideAndConquerDpResult<\n        std::decay_t<decltype(std::declval<T>()\
    \ + cost(0, 0))>> {\n    using Result = std::decay_t<decltype(std::declval<T>()\
    \ + cost(0, 0))>;\n    return divide_and_conquer_dp(\n        state_count, int(previous.size()),\n\
    \        [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/knuth_optimization.hpp\"\n\n\n\n#line 8 \"\
    convex/monge/knuth_optimization.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\
    \ntemplate <class T>\nstruct KnuthOptimizationResult {\n    std::vector<std::vector<T>>\
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
    \ \"convex/monge/min_plus_convolution.hpp\"\n\n#line 9 \"convex/monge/min_plus_convolution.hpp\"\
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
    \ convex\n}  // namespace m1une\n\n\n#line 12 \"convex/monge/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_CONVEX_MONGE_ALL_HPP

    #define M1UNE_CONVEX_MONGE_ALL_HPP 1


    #include "anti_monge_shortest_path.hpp"

    #include "check.hpp"

    #include "divide_and_conquer_optimization.hpp"

    #include "knuth_optimization.hpp"

    #include "larsch.hpp"

    #include "min_plus_convolution.hpp"

    #include "monotone_minima.hpp"

    #include "smawk.hpp"


    #endif  // M1UNE_CONVEX_MONGE_ALL_HPP

    '
  dependsOn:
  - convex/monge/anti_monge_shortest_path.hpp
  - convex/monge/smawk.hpp
  - convex/monge/check.hpp
  - convex/monge/divide_and_conquer_optimization.hpp
  - convex/monge/monotone_minima.hpp
  - convex/monge/knuth_optimization.hpp
  - convex/monge/larsch.hpp
  - convex/monge/min_plus_convolution.hpp
  isVerificationFile: false
  path: convex/monge/all.hpp
  requiredBy:
  - convex/all.hpp
  timestamp: '2026-10-24 20:27:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
documentation_of: convex/monge/all.hpp
layout: document
title: Monge Optimization Guide
---

## What these algorithms solve

Monge optimization avoids checking every candidate for every state when the
cost matrix has an ordered structure. You provide a callback for a matrix
entry or edge cost; the library evaluates only selected entries. You do not
need to construct the full matrix.

All APIs use `m1une::convex`, zero-based indices, and half-open intervals.
Start with the recurrence and its dependency order, then prove the required
matrix property. The word "Monge" alone does not determine which API to use.

## Start here: what does a library call replace?

Suppose each row is a request and each column is one possible choice. You
want the cheapest choice for each request:

| Request | Choice 0 | Choice 1 | Choice 2 | Choice 3 |
| --- | --- | --- | --- | --- |
| 0 | 5 | 9 | 21 | 41 |
| 1 | 6 | 2 | 6 | 18 |
| 2 | 23 | 11 | 7 | 11 |

Normally, you scan all four choices for each of the three requests. SMAWK
performs that search with fewer cost evaluations when its matrix condition
holds. Here is the complete input-to-answer workflow:

```cpp
#include "convex/monge/smawk.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {5, 9, 21, 41},
        {6, 2, 6, 18},
        {23, 11, 7, 11}
    };
    // Explicit-table overload: returns the best column index for each row.
    auto best = m1une::convex::smawk_row_argmin(cost);
    assert(best == std::vector<int>({0, 1, 2}));
    long long minimum_for_request_1 = cost[1][best[1]];
    assert(minimum_for_request_1 == 2);

    // Callback overload: same table, supplied one entry at a time.
    auto same = m1une::convex::smawk_row_argmin(3, 4,
        [&](int request, int choice) { return cost[request][choice]; });
    assert(same == best);
}
```

The callback is just a way to look up **one candidate's cost**. It does not
search for the best choice. The library performs that search and returns an
index; you use the index to read the minimum value. To avoid storing a large
table, replace the lookup with your formula or range query.

This example is Monge: its entries equal `base[row] + 4*(row-column)^2`,
with `base={5,2,7}`. Your own cost needs the documented ordering property
before you use this optimization. The [SMAWK worked example](smawk.md)
shows the original nested loop, exact output, and argument meanings.

For other recurrences, start with the corresponding worked example:

| What your straightforward code does | Worked example |
| --- | --- |
| Scans all choices independently for each answer | [SMAWK](smawk.md) or [monotone minima](monotone_minima.md). |
| Builds a new cost array from a known previous array | [One more move from known costs](divide_and_conquer_optimization.md). |
| Computes later DP values from earlier values in the same array | [Forward jumps with Monge costs](larsch.md) or [anti-Monge costs](anti_monge_shortest_path.md). |
| Tries every split of an interval | [Merging adjacent piles](knuth_optimization.md). |
| Tries every pair of quantities whose sum is a requested total | [Two-supplier convolution](min_plus_convolution.md). |

Each page starts with a small task and its straightforward implementation,
then a complete library-based program, expected answers, and the condition
that permits the optimization. The reference tables below help adapt those
examples once the basic call is clear.

## Choose by recurrence and dependencies

| Task | API | Required structure | Work, for constant-time callbacks |
| --- | --- | --- | --- |
| `answer[r] = min_c M(r,c)`, all entries fixed | [smawk_row_argmin](smawk.md) | Total monotonicity for leftmost minima; Monge suffices. | $O(H+W)$ |
| Same, but only the full matrix's argmins are known to be nondecreasing | [monotone_row_argmin](monotone_minima.md) | Nondecreasing leftmost argmins. | $O((H+W)\log(H+1))$ |
| `next[j] = min_i(previous[i] + cost(i,j))` | [divide_and_conquer_transition](divide_and_conquer_optimization.md) | Previous layer fixed; nondecreasing minimizing candidates. | $O((H+W)\log(H+1))$ per layer |
| `dp[j] = min_{i<j}(dp[i] + cost(i,j))`, Monge costs | [larsch_shortest_path](larsch.md) | Triangular total monotonicity for minima. | $O(V)$ |
| Same forward DP, anti-Monge costs, optionally `j-i >= D` | [anti_monge_shortest_path](anti_monge_shortest_path.md) | Anti-Monge on valid rectangles. | $O(V\log V+VD)$; $O(V\log V)$ for fixed `D`. |
| `dp[l][r] = cost(l,r) + min_k(dp[l][k]+dp[k][r])` | [knuth_optimization](knuth_optimization.md) | Knuth's split monotonicity. | $O(N^2)$ |
| `answer[k] = min_{i+j=k}(a[i]+b[j])`, or the maximum analogue | [structured convolution](min_plus_convolution.md) | Convex or concave input sequences as documented. | $O(N+M)$ |

`divide_and_conquer_dp` is a value-and-choice wrapper around monotone minima;
it does not imply that the recurrence has a segment-count dimension.
If a fixed transition matrix is Monge, you can also use SMAWK directly to
compute one previous-layer transition in $O(H+W)$ work.

For maxima, the matrix-search APIs have `row_argmax` variants and strict
comparator overloads. The shortest-path helpers minimize; their documented
cost direction still applies.

## Map the recurrence to rows and columns

For a minimization over candidates, use **one row per answer/state** and
**one column per candidate**. For a previous-layer recurrence, the matrix is

$$
M(j,i)=previous[i]+cost(i,j).
$$

The callback and return values depend on the interface:

| API | Callback receives | Callback returns | Result |
| --- | --- | --- | --- |
| `smawk_row_argmin(H,W,value)` | `(state, candidate)` | Entire matrix entry, including `previous[candidate]` if needed. | Column index for each state. |
| `divide_and_conquer_dp(H,W,value)` | `(state, candidate)` | Entire matrix entry. | `.value[state]` and `.argmin[state]`. |
| `divide_and_conquer_transition(previous,H,cost)` | `(candidate, state)` | Edge/transition cost only; the helper adds the previous value. | `.value[state]` and `.argmin[state]`. |
| `larsch_shortest_path(V,cost)` | `(from, to)` | Edge cost only; the helper adds the source distance. | `.distance[to]` and `.parent[to]`. |
| `anti_monge_shortest_path(V,cost,INF,D)` | `(from, to)` | Edge cost only. | `.distance[to]` and `.parent[to]`. |

The dimensions are counts, not largest indices. `H` states use indices
`0..H-1`; a sequence-prefix DP over lengths `0..N` needs `N+1` vertices.
Matrix-search results are column positions in the order you supplied. If
columns index a filtered or reordered candidate list, map positions through
that list before using them as original indices.

## Establish the inequality and its direction

For row indices `a < b` and column indices `c < d`, Monge means

$$
M(a,c)+M(b,d)\le M(a,d)+M(b,c).
$$

Anti-Monge reverses the inequality. Some sources use different naming
conventions; compare their inequality with this one.

A useful general model is squared distance between sorted coordinates:
`M(r,c) = (x[r]-y[c])^2`. Its quadrangle difference is
`-2*(x[b]-x[a])*(y[d]-y[c]) <= 0`, so it is Monge. Negated squared distance
is anti-Monge. More generally, convex functions of coordinate differences
give Monge costs, while concave functions give anti-Monge costs.

These transformations are useful when adapting a recurrence:

| Transformation | Effect |
| --- | --- |
| Add an arbitrary constant to each row or column | Preserves Monge / anti-Monge, since constants cancel in the inequality. |
| Keep a subset of rows or columns in their original order | Preserves the property. |
| Transpose | Preserves the inequality's direction. |
| Reverse columns, or reverse rows | Exchanges Monge and anti-Monge. |
| Negate entries | Exchanges Monge and anti-Monge, and exchanges minima with maxima. |

In particular, adding known `previous[i]` values as column constants preserves
Monge. This does **not** hold for arbitrary column constants if all you know
is total monotonicity; check the resulting transition matrix in that case.

Both search algorithms expect optimal column indices to be nondecreasing in
the supplied row order. For Monge matrices this holds for minima; for
anti-Monge matrices it holds for maxima. Use this orientation table:

| Matrix | Row minima | Row maxima |
| --- | --- | --- |
| Monge | Original column order. | Reverse columns first. |
| Anti-Monge | Reverse columns first. | Original column order. |

Reversing columns preserves the values being optimized. Map the result back:

```cpp
auto argmin = m1une::convex::smawk_row_argmin(H, W,
    [&](int row, int column) { return value(row, W - 1 - column); });
for (int row = 0; row < H; ++row) {
    if (argmin[row] != -1) argmin[row] = W - 1 - argmin[row];
}
```

Matrix-search APIs break ties toward the leftmost supplied column. Reversal
therefore chooses the rightmost original optimum. For `W=0`, every answer is
`-1`; for `H=0`, the result is empty. Never index a candidate array with `-1`.

## Applying the examples to your own recurrence

First write the candidate-search loop without optimization. Identify which
array entries are already known, what one candidate's transition value is,
and whether the output is a value or an index. Then match that loop to the
callback table above.

For a previous-layer recurrence, follow the
[known-costs example](divide_and_conquer_optimization.md): provide the previous
array and a transition-cost callback, then read `.value` and `.argmin`.
For multiple layers, finish each layer before replacing `previous`. Layer
count multiplies the work; the library does not decide whether your problem
needs an exact number of transitions or an unrestricted optimal path.

## Forward DP requires a different evaluation order

In `dp[j] = min_{i<j}(dp[i]+cost(i,j))`, predecessor values belong to the same
array you are computing. Fixed-matrix search may query rows out of order;
a callback reading unfinished `dp[i]` values does not define a fixed matrix.

Use `larsch_shortest_path` for the documented Monge case, or
`anti_monge_shortest_path` for the anti-Monge case. Both accept **edge costs**;
they manage source distances and dependency order internally. Their pages
contain standalone examples and exact graph restrictions.

For a custom divide-and-conquer forward DP, the dependency order is:

1. Solve the left block so its source distances are final.
2. Relax all valid transitions from the left block to the right block.
3. Solve the right block with those incoming distances.

At the cross step, distances on the left are fixed column constants, so
matrix search is valid on a fully defined rectangle of cross transitions.
Each edge is handled at the unique recursive split that separates its
endpoints. A generic recursion that solves both halves before invoking the
cross callback does not provide this dependency order.

## Invalid candidates, infinity, and checking your model

The public matrix-search routines search **full rectangles**. A restriction
such as `i < j`, a minimum interval length, or a maximum interval length is a
separate condition; Monge on valid cells alone does not justify searching a
padded rectangle.

For example, after reversing a triangular candidate set, a zero-cost matrix
may become:

| | Column 0 | Column 1 |
| --- | --- | --- |
| Row 0 | INF | 0 |
| Row 1 | 0 | 0 |

The leftmost minima are `1,0`, violating the required monotonicity. This can
happen even when the original finite cost is both Monge and anti-Monge.

For state-independent exclusions, filter out invalid candidates and retain
the index mapping. For state-dependent exclusions, use a helper that explicitly
supports the restriction, split transitions into valid rectangles, or prove
that your particular padding preserves the algorithm's precondition.
`anti_monge_shortest_path` supports a minimum index step `D`; it does not
support arbitrary forbidden edges or a maximum step.

For a previous-layer matrix, avoid adding edge costs to an unreachable-value
sentinel. Remove unreachable candidate columns before searching. Choose a
numeric type and sentinel that can represent all finite transition sums;
see each helper's numeric contract.

During development, compare optimized answers with exhaustive candidate
search on small instances, including ties and empty candidate sets.
`is_monge` and `is_anti_monge` check a finite rectangle in $O(HW)$ time;
they are useful diagnostics, but checking a few instances is not a proof for
all inputs. Test the **actual callback matrix**, including previous-layer
costs and any reordering or validity mask.

## Included Headers

| Header | Contents |
| --- | --- |
| `convex/monge/smawk.hpp` | Linear-time row optima for implicit totally monotone matrices. |
| `convex/monge/monotone_minima.hpp` | Divide-and-conquer row optima under monotone argmins. |
| `convex/monge/divide_and_conquer_optimization.hpp` | DP-facing matrix search returning values and choices. |
| `convex/monge/knuth_optimization.hpp` | Quadratic Knuth optimization for interval DP. |
| `convex/monge/larsch.hpp` | Linear-time online minima and Monge DAG shortest paths. |
| `convex/monge/anti_monge_shortest_path.hpp` | Anti-Monge forward DP with a minimum index step. |
| `convex/monge/check.hpp` | Monge and anti-Monge inequality checks. |
| `convex/monge/min_plus_convolution.hpp` | Structured min-plus/max-plus convolution. |
