---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/alien_trick.hpp
    title: Alien Trick
  - icon: ':warning:'
    path: algo/dp_optimization/all.hpp
    title: DP Optimization All
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/all.hpp
    title: Monge All
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/check.hpp
    title: Monge Checks
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/knuth_optimization.hpp
    title: Knuth Optimization
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/larsch.hpp
    title: LARSCH
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/monotone_minima.hpp
    title: Monotone Minima
  - icon: ':heavy_check_mark:'
    path: algo/dp_optimization/monge/smawk.hpp
    title: SMAWK
  - icon: ':warning:'
    path: algo/sequence/all.hpp
    title: Sequence Algorithms All
  - icon: ':heavy_check_mark:'
    path: algo/sequence/inversion_count.hpp
    title: Inversion Count
  - icon: ':heavy_check_mark:'
    path: algo/sequence/lis.hpp
    title: Longest Increasing Subsequence (LIS)
  - icon: ':heavy_check_mark:'
    path: algo/sequence/subset_sum.hpp
    title: Meet-in-the-Middle Subset Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/all.hpp\"\n\n\n\n#line 1 \"algo/dp_optimization/all.hpp\"\
    \n\n\n\n#line 1 \"algo/dp_optimization/alien_trick.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <numeric>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace dp {\n\nnamespace detail {\n\ntemplate <std::integral\
    \ Penalty, std::integral Count, class Oracle>\nPenalty alien_trick_penalty(Penalty\
    \ lower, Penalty upper, Count target_count, Oracle& oracle) {\n    assert(lower\
    \ <= upper);\n    assert(oracle(lower).second >= target_count);\n    assert(oracle(upper).second\
    \ <= target_count);\n\n    while (lower < upper) {\n        Penalty middle = std::midpoint(lower,\
    \ upper);\n        if (middle == lower) ++middle;\n        if (oracle(middle).second\
    \ >= target_count) {\n            lower = middle;\n        } else {\n        \
    \    upper = middle - 1;\n        }\n    }\n    return lower;\n}\n\n}  // namespace\
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
    }\n\n}  // namespace dp\n}  // namespace m1une\n\n\n#line 1 \"algo/dp_optimization/monge/all.hpp\"\
    \n\n\n\n#line 1 \"algo/dp_optimization/monge/check.hpp\"\n\n\n\n#line 5 \"algo/dp_optimization/monge/check.hpp\"\
    \n#include <vector>\n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class\
    \ Value>\nbool is_monge(int row_count, int column_count, Value value) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    for (int row = 0; row + 1 < row_count;\
    \ row++) {\n        for (int column = 0; column + 1 < column_count; column++)\
    \ {\n            if (value(row, column) + value(row + 1, column + 1) >\n     \
    \           value(row, column + 1) + value(row + 1, column)) {\n             \
    \   return false;\n            }\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class Value>\nbool is_anti_monge(int row_count, int column_count, Value value)\
    \ {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int\
    \ row = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column\
    \ + 1 < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) <\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class T>\nbool is_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 1 \"algo/dp_optimization/monge/divide_and_conquer_optimization.hpp\"\
    \n\n\n\n#line 7 \"algo/dp_optimization/monge/divide_and_conquer_optimization.hpp\"\
    \n\n#line 1 \"algo/dp_optimization/monge/monotone_minima.hpp\"\n\n\n\n#line 5\
    \ \"algo/dp_optimization/monge/monotone_minima.hpp\"\n#include <functional>\n\
    #line 7 \"algo/dp_optimization/monge/monotone_minima.hpp\"\n\nnamespace m1une\
    \ {\nnamespace monge {\n\nnamespace monotone_minima_detail {\n\ntemplate <class\
    \ Value, class Compare>\nvoid solve(int row_left, int row_right, int column_left,\
    \ int column_right,\n           const Value& value, const Compare& compare, std::vector<int>&\
    \ answer) {\n    if (row_left == row_right) return;\n    int row = (row_left +\
    \ row_right) / 2;\n    int best = column_left;\n    for (int column = column_left\
    \ + 1; column < column_right; column++) {\n        if (compare(value(row, column),\
    \ value(row, best))) best = column;\n    }\n    answer[row] = best;\n    solve(row_left,\
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
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 9 \"algo/dp_optimization/monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
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
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/dp_optimization/monge/knuth_optimization.hpp\"\n\n\
    \n\n#include <algorithm>\n#line 8 \"algo/dp_optimization/monge/knuth_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\ntemplate <class T>\nstruct KnuthOptimizationResult\
    \ {\n    std::vector<std::vector<T>> value;\n    std::vector<std::vector<int>>\
    \ split;\n\n    T optimum() const {\n        return value[0].back();\n    }\n\
    };\n\ntemplate <class IntervalCost>\nauto knuth_optimization(int element_count,\
    \ IntervalCost interval_cost)\n    -> KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
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
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 1 \"algo/dp_optimization/monge/larsch.hpp\"\
    \n\n\n\n#line 6 \"algo/dp_optimization/monge/larsch.hpp\"\n#include <memory>\n\
    #line 10 \"algo/dp_optimization/monge/larsch.hpp\"\n\nnamespace m1une {\nnamespace\
    \ monge {\n\ntemplate <class T>\nclass Larsch {\n    struct ReduceColumn;\n\n\
    \    struct ReduceRow {\n        int size;\n        std::function<T(int, int)>\
    \ value;\n        int current_row = 0;\n        int boundary = 0;\n        std::unique_ptr<ReduceColumn>\
    \ recursive;\n\n        explicit ReduceRow(int size_) : size(size_) {\n      \
    \      if (size / 2 != 0) recursive = std::make_unique<ReduceColumn>(size / 2);\n\
    \        }\n\n        void set_value(std::function<T(int, int)> value_) {\n  \
    \          value = std::move(value_);\n            if (recursive) {\n        \
    \        recursive->set_value(\n                    [&](int row, int column) {\
    \ return value(row * 2 + 1, column); });\n            }\n        }\n\n       \
    \ int next_argmin() {\n            int row = current_row++;\n            if (row\
    \ % 2 == 0) {\n                int previous = boundary;\n                int next\
    \ = row + 1 == size ? size - 1 : recursive->next_argmin();\n                boundary\
    \ = next;\n                int best = previous;\n                for (int column\
    \ = previous + 1; column <= next; column++) {\n                    if (value(row,\
    \ column) < value(row, best)) best = column;\n                }\n            \
    \    return best;\n            }\n            return value(row, boundary) <= value(row,\
    \ row) ? boundary : row;\n        }\n    };\n\n    struct ReduceColumn {\n   \
    \     int size;\n        std::function<T(int, int)> value;\n        int current_row\
    \ = 0;\n        std::vector<int> columns;\n        ReduceRow recursive;\n\n  \
    \      explicit ReduceColumn(int size_) : size(size_), recursive(size_) {}\n\n\
    \        void set_value(std::function<T(int, int)> value_) {\n            value\
    \ = std::move(value_);\n            recursive.set_value(\n                [&](int\
    \ row, int column) { return value(row, columns[column]); });\n        }\n\n  \
    \      int next_argmin() {\n            int row = current_row++;\n           \
    \ int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row * 2;\n \
    \           for (int column = first; column <= last; column++) {\n           \
    \     while (int(columns.size()) != row &&\n                       value(int(columns.size())\
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
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace monge\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/dp_optimization/monge/min_plus_convolution.hpp\"\n\
    \n\n\n#line 7 \"algo/dp_optimization/monge/min_plus_convolution.hpp\"\n\n#line\
    \ 1 \"algo/dp_optimization/monge/smawk.hpp\"\n\n\n\n#line 8 \"algo/dp_optimization/monge/smawk.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\nnamespace smawk_detail {\n\ntemplate\
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
    }\n\n}  // namespace monge\n}  // namespace m1une\n\n\n#line 9 \"algo/dp_optimization/monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace monge {\n\nnamespace convolution_detail {\n\n\
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
    \ monge\n}  // namespace m1une\n\n\n#line 11 \"algo/dp_optimization/monge/all.hpp\"\
    \n\n\n#line 6 \"algo/dp_optimization/all.hpp\"\n\n\n#line 1 \"algo/sequence/all.hpp\"\
    \n\n\n\n#line 1 \"algo/sequence/inversion_count.hpp\"\n\n\n\n#line 5 \"algo/sequence/inversion_count.hpp\"\
    \n\nnamespace m1une {\nnamespace sequence {\n\n// Returns the number of pairs\
    \ (i, j) with i < j and a[i] > a[j].\n// The vector is taken by value because\
    \ merge sort rearranges it.\ntemplate <typename T>\nlong long inversion_count(std::vector<T>\
    \ a) {\n    const int n = int(a.size());\n    std::vector<T> temp = a;\n\n   \
    \ auto merge_sort = [&](auto& self, int l, int r) -> long long {\n        if (r\
    \ - l <= 1) return 0;\n\n        const int m = l + (r - l) / 2;\n        long\
    \ long inv = self(self, l, m) + self(self, m, r);\n\n        int i = l;\n    \
    \    int j = m;\n        int k = l;\n        while (i < m && j < r) {\n      \
    \      if (!(a[j] < a[i])) {\n                temp[k++] = a[i++];\n          \
    \  } else {\n                temp[k++] = a[j++];\n                inv += m - i;\n\
    \            }\n        }\n\n        while (i < m) temp[k++] = a[i++];\n     \
    \   while (j < r) temp[k++] = a[j++];\n\n        for (int p = l; p < r; ++p) {\n\
    \            a[p] = temp[p];\n        }\n\n        return inv;\n    };\n\n   \
    \ return merge_sort(merge_sort, 0, n);\n}\n\n}  // namespace sequence\n}  // namespace\
    \ m1une\n\n\n#line 1 \"algo/sequence/lis.hpp\"\n\n\n\n#line 5 \"algo/sequence/lis.hpp\"\
    \n#include <iterator>\n#line 7 \"algo/sequence/lis.hpp\"\n\nnamespace m1une {\n\
    namespace sequence {\n\n// Returns the zero-based indices of a longest increasing\
    \ subsequence.\n// If `strict` is false, equal adjacent values are also allowed.\n\
    template <typename T>\nstd::vector<int> lis(const std::vector<T>& a, bool strict\
    \ = true) {\n    const int n = int(a.size());\n    std::vector<T> tails;\n   \
    \ std::vector<int> tail_positions;\n    std::vector<int> predecessor(n, -1);\n\
    \    tails.reserve(n);\n    tail_positions.reserve(n);\n\n    for (int i = 0;\
    \ i < n; ++i) {\n        auto it = strict ? std::lower_bound(tails.begin(), tails.end(),\
    \ a[i])\n                         : std::upper_bound(tails.begin(), tails.end(),\
    \ a[i]);\n        const int length = int(std::distance(tails.begin(), it));\n\n\
    \        if (it == tails.end()) {\n            tails.push_back(a[i]);\n      \
    \      tail_positions.push_back(i);\n        } else {\n            *it = a[i];\n\
    \            tail_positions[length] = i;\n        }\n\n        if (length > 0)\
    \ {\n            predecessor[i] = tail_positions[length - 1];\n        }\n   \
    \ }\n\n    if (tail_positions.empty()) return {};\n\n    std::vector<int> result;\n\
    \    result.reserve(tail_positions.size());\n    int current = tail_positions.back();\n\
    \    while (current != -1) {\n        result.push_back(current);\n        current\
    \ = predecessor[current];\n    }\n    std::reverse(result.begin(), result.end());\n\
    \    return result;\n}\n\n}  // namespace sequence\n}  // namespace m1une\n\n\n\
    #line 1 \"algo/sequence/subset_sum.hpp\"\n\n\n\n#line 5 \"algo/sequence/subset_sum.hpp\"\
    \n#include <cstddef>\n#line 8 \"algo/sequence/subset_sum.hpp\"\n\nnamespace m1une\
    \ {\nnamespace sequence {\n\nnamespace internal {\n\ntemplate <typename T>\nstd::vector<T>\
    \ enumerate_sorted_subset_sums(\n    const std::vector<T>& values,\n    int left,\n\
    \    int right\n) {\n    std::vector<T> sums(1, T{});\n    std::vector<T> merged;\n\
    \n    for (int i = left; i < right; ++i) {\n        const std::size_t size = sums.size();\n\
    \        merged.clear();\n        merged.reserve(size * 2);\n\n        std::size_t\
    \ without = 0;\n        std::size_t with = 0;\n        while (without < size &&\
    \ with < size) {\n            const T with_current = sums[with] + values[i];\n\
    \            if (with_current < sums[without]) {\n                merged.push_back(with_current);\n\
    \                ++with;\n            } else {\n                merged.push_back(sums[without]);\n\
    \                ++without;\n            }\n        }\n        while (without\
    \ < size) {\n            merged.push_back(sums[without]);\n            ++without;\n\
    \        }\n        while (with < size) {\n            merged.push_back(sums[with]\
    \ + values[i]);\n            ++with;\n        }\n        sums.swap(merged);\n\
    \    }\n\n    return sums;\n}\n\n}  // namespace internal\n\n// Returns the sorted\
    \ subset sums of values[0, n / 2) and values[n / 2, n).\ntemplate <typename T>\n\
    std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(\n    const\
    \ std::vector<T>& values\n) {\n    const int n = int(values.size());\n    const\
    \ int middle = n / 2;\n    return {\n        internal::enumerate_sorted_subset_sums(values,\
    \ 0, middle),\n        internal::enumerate_sorted_subset_sums(values, middle,\
    \ n)\n    };\n}\n\n// Returns the maximum subset sum not exceeding limit.\ntemplate\
    \ <typename T>\nT maximum_subset_sum(const std::vector<T>& values, const T& limit)\
    \ {\n    assert(!(limit < T{}));\n    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);\n\
    \n    T answer{};\n    std::size_t right_count = right_sums.size();\n    for (const\
    \ T& left : left_sums) {\n        while (\n            right_count > 0 &&\n  \
    \          limit < left + right_sums[right_count - 1]\n        ) {\n         \
    \   --right_count;\n        }\n        if (right_count == 0) break;\n\n      \
    \  const T candidate = left + right_sums[right_count - 1];\n        if (answer\
    \ < candidate) answer = candidate;\n    }\n    return answer;\n}\n\n}  // namespace\
    \ sequence\n}  // namespace m1une\n\n\n#line 7 \"algo/sequence/all.hpp\"\n\n\n\
    #line 6 \"algo/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_ALGO_ALL_HPP

    #define M1UNE_ALGO_ALL_HPP 1


    #include "dp_optimization/all.hpp"

    #include "sequence/all.hpp"


    #endif  // M1UNE_ALGO_ALL_HPP

    '
  dependsOn:
  - algo/dp_optimization/all.hpp
  - algo/dp_optimization/alien_trick.hpp
  - algo/dp_optimization/monge/all.hpp
  - algo/dp_optimization/monge/check.hpp
  - algo/dp_optimization/monge/divide_and_conquer_optimization.hpp
  - algo/dp_optimization/monge/monotone_minima.hpp
  - algo/dp_optimization/monge/knuth_optimization.hpp
  - algo/dp_optimization/monge/larsch.hpp
  - algo/dp_optimization/monge/min_plus_convolution.hpp
  - algo/dp_optimization/monge/smawk.hpp
  - algo/sequence/all.hpp
  - algo/sequence/inversion_count.hpp
  - algo/sequence/lis.hpp
  - algo/sequence/subset_sum.hpp
  isVerificationFile: false
  path: algo/all.hpp
  requiredBy: []
  timestamp: '2026-07-07 14:26:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algo/all.hpp
layout: document
title: Algorithms All
---

## Overview

`algo/all.hpp` includes one-shot sequence algorithms and DP optimization
helpers. Stateful query/update structures live under `ds/`.

## Included Headers

| Header | Contents |
| --- | --- |
| `algo/sequence/all.hpp` | Sequence and array algorithms such as LIS, inversion count, and subset sum. |
| `algo/dp_optimization/all.hpp` | Alien Trick and Monge-family DP optimization helpers. |
