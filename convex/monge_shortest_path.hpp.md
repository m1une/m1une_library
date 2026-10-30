---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH Online Matrix Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/anti_monge_shortest_path.test.cpp
    title: verify/convex/monge/anti_monge_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_shortest_path.test.cpp
    title: verify/convex/monge/monge_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge_shortest_path.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <numeric>\n#include <vector>\n\n#line 1 \"convex/monge/larsch.hpp\"\
    \n\n\n\n#line 5 \"convex/monge/larsch.hpp\"\n#include <utility>\n#line 7 \"convex/monge/larsch.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\n// Online minima of a lower-triangular\
    \ totally monotone matrix (column <= row).\n// Leftmost ties. Before answering\
    \ row r, only columns <= r are accessed, even\n// when evaluating future rows.\
    \ Finalize column r+1 after receiving answer r.\n// O(N) total time/evaluations/memory;\
    \ an individual next_argmin can take O(N).\n// Value is stored directly, with\
    \ no type-erased callable. Use CTAD: Larsch q(n,f).\ntemplate <class Value>\n\
    class Larsch {\n    struct Level {\n        int size;\n        int row = 0;\n\
    \        int column_row = 0;\n        int boundary = 0;\n        std::vector<int>\
    \ columns;\n        explicit Level(int n) : size(n) {}\n    };\n\n    int _size;\n\
    \    Value _value;\n    std::vector<Level> _levels;\n\n    auto entry(int depth,\
    \ int row, int column) {\n        for (int d = depth; d > 0; --d) {\n        \
    \    row = row * 2 + 1;\n            column = _levels[d].columns[column];\n  \
    \      }\n        return _value(row, column);\n    }\n\n    int next_column(int\
    \ depth) {\n        auto& level = _levels[depth];\n        int row = level.column_row++;\n\
    \        int first = row == 0 ? 0 : row * 2 - 1;\n        for (int column = first;\
    \ column <= row * 2; ++column) {\n            while (int(level.columns.size())\
    \ != row &&\n                   entry(depth - 1, int(level.columns.size()) * 2\
    \ - 1,\n                         level.columns.back()) >\n                   entry(depth\
    \ - 1, int(level.columns.size()) * 2 - 1, column)) {\n                level.columns.pop_back();\n\
    \            }\n            if (int(level.columns.size()) != level.size) {\n \
    \               level.columns.push_back(column);\n            }\n        }\n \
    \       return level.columns[next_row(depth)];\n    }\n\n    int next_row(int\
    \ depth) {\n        auto& level = _levels[depth];\n        int row = level.row++;\n\
    \        if (row % 2 != 0) {\n            return entry(depth, row, level.boundary)\
    \ <= entry(depth, row, row)\n                       ? level.boundary : row;\n\
    \        }\n        int previous = level.boundary;\n        int next = row + 1\
    \ == level.size ? level.size - 1\n                                        : next_column(depth\
    \ + 1);\n        level.boundary = next;\n        int best = previous;\n      \
    \  for (int column = previous + 1; column <= next; ++column) {\n            if\
    \ (entry(depth, row, column) < entry(depth, row, best)) best = column;\n     \
    \   }\n        return best;\n    }\n\n   public:\n    explicit Larsch(int size,\
    \ Value value) : _size(size), _value(std::move(value)) {\n        assert(size\
    \ >= 0);\n        for (int n = size; n > 0; n /= 2) {\n            _levels.emplace_back(n);\n\
    \            if (_levels.size() > 1) _levels.back().columns.reserve(n);\n    \
    \    }\n    }\n    int size() const { return _size; }\n    int processed_rows()\
    \ const { return _size == 0 ? 0 : _levels[0].row; }\n    bool finished() const\
    \ { return processed_rows() == _size; }\n    int next_argmin() {\n        assert(!finished());\n\
    \        return next_row(0);\n    }\n};\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/smawk.hpp\"\n\n\n\n#line 5 \"convex/monge/smawk.hpp\"\
    \n#include <functional>\n#line 7 \"convex/monge/smawk.hpp\"\n#include <span>\n\
    #line 9 \"convex/monge/smawk.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\n\
    namespace smawk_detail {\n\ntemplate <class Select>\nvoid solve(const std::vector<int>&\
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
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 11 \"convex/monge_shortest_path.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct MongeShortestPathResult\
    \ {\n    std::vector<T> distance;\n    std::vector<int> parent;\n};\n\n// Same-array\
    \ forward recurrence: dp[j] = min(dp[i] + cost(i,j)), j-i >= D.\n// Finite Monge\
    \ costs on every fully valid rectangle. Smallest parent on ties.\n// O(N) time/evaluations/memory,\
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
    \ convex\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP\n#define M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <vector>\n\n#include \"monge/larsch.hpp\"\n#include \"monge/smawk.hpp\"\n\n\
    namespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct MongeShortestPathResult\
    \ {\n    std::vector<T> distance;\n    std::vector<int> parent;\n};\n\n// Same-array\
    \ forward recurrence: dp[j] = min(dp[i] + cost(i,j)), j-i >= D.\n// Finite Monge\
    \ costs on every fully valid rectangle. Smallest parent on ties.\n// O(N) time/evaluations/memory,\
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
    \ convex\n}  // namespace m1une\n\n#endif  // M1UNE_CONVEX_MONGE_SHORTEST_PATH_HPP\n"
  dependsOn:
  - convex/monge/larsch.hpp
  - convex/monge/smawk.hpp
  isVerificationFile: false
  path: convex/monge_shortest_path.hpp
  requiredBy:
  - convex/all.hpp
  timestamp: '2026-10-30 16:04:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/anti_monge_shortest_path.test.cpp
  - verify/convex/monge/monge_shortest_path.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge_shortest_path.hpp
layout: document
title: Monge and Anti-Monge Forward DAG Shortest Paths
---

Compute a **same-array recurrence**, starting at vertex `0`:

$$
dp[0]=0,\qquad dp[j]=\min_{0\le i\le j-D}(dp[i]+cost(i,j)),
\qquad D=minimum\_step\ge1.
$$

Vertices are natural indices in `[0,vertex_count)`; **every** edge with
`to-from >= D` exists and has finite cost. Negative costs are allowed in this
forward DAG. `cost(from,to)` returns only the edge cost. Distances are finalized
by the solver, unlike an [offline layer transition](https://m1une.github.io/m1une_library/convex/monge_transition.hpp).
For prefix partitioning, use `vertex_count = sequence_length+1`.

## Interface

Both functions use `m1une::convex` and return the same result type.

| Signature | Time | Memory |
| --- | --- | --- |
| `template<class T, class Cost> MongeShortestPathResult<T> monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | $O(N)$ for every $D$ | $O(N)$ |
| `template<class T, class Cost> MongeShortestPathResult<T> anti_monge_shortest_path(int vertex_count, Cost cost, T infinity, int minimum_step = 1)` | $O(N\log(N+1)+ND)$ | $O(N)$ |

For anti-Monge, $D=1$ or $D=2$ gives $O(N\log(N+1))$. If $D\ge N$,
both routines return after $O(N)$ initialization. Counts and minimum steps
are asserted nonnegative and positive respectively. Arithmetic and cost
evaluation are assumed constant time. Inputs are not modified.

`MongeShortestPathResult<T>` contains `std::vector<T> distance` and
`std::vector<int> parent`. `distance[0]=T()` and `parent[0]=-1`.
Unreachable vertices have `distance=infinity` and `parent=-1`. Among optimal
parents, Monge chooses the **smallest** source ID; anti-Monge chooses the
**largest**. Empty graphs return empty vectors. Vertices `1..D-1` are
unreachable; every vertex `>=D` in the graph is reachable directly from `0`.

`T()` must represent zero. `T` supports addition and comparisons, and cost
values are convertible to `T`. Choose `infinity > T()` strictly larger than
every finite path value and transition sum encountered. All such sums must
fit in `T`. Neither algorithm adds infinity or calls the cost for an
unreachable source or invalid edge. Other missing edges, infinite edge costs,
and maximum-step restrictions are unsupported.

## Monge assumptions

For `a<b`, `c<d`, and `b+D<=c`, require

$$
cost(a,c)+cost(b,d)\le cost(a,d)+cost(b,c).
$$

For anti-Monge reverse the inequality. These conditions apply to **all fully
valid rectangles**, not just adjacent entries of a triangularly masked table.
The cost is fixed across calls; evaluations can occur in arbitrary order on
legal pairs. Properties are not checked. Adding source or target fees preserves
either inequality.

## Why Monge supports arbitrary minimum steps in linear time

Use [LARSCH](https://m1une.github.io/m1une_library/convex/monge/larsch.hpp) with
`N-D` rows. Row `r` targets vertex `r+D`. Its legal reachable sources are `0`
and `D..r`. Map virtual column `c` to `0` when `c<D`, otherwise to `c`.
The columns are now a **nondecreasing** list with duplicates of `0` replacing
permanently unreachable vertices. The lower triangle `c<=r` represents exactly
the needed candidates, including harmless duplicates. Every queried edge is
legal. Duplicating an ordered source preserves Monge; adding its finalized
distance as a column constant preserves Monge too.

Before answering row `r`, LARSCH accesses only virtual columns `<=r`, though it
may query future rows. Their sources are at most `r`, whose distances are already
finalized since the destination is `r+D`. Leftmost virtual ties map to the
smallest original parent. The construction and all row searches take $O(N)$
time and memory, independently of `D`; no numeric padding is used.

The early return for `D>=N` precedes construction of LARSCH or evaluation of
`r+D`. Otherwise `0<=r<N-D`, hence `r+D<=N-1`; the addition fits in `int`.
This also covers `minimum_step=INT_MAX`, which always takes the early return
for an `int` vertex count. In every case, existing vertices in `[1,min(D,N))`
retain `distance=infinity` and `parent=-1`, and their costs are never queried.

## Anti-Monge CDQ and boundary handling

For `[l,r)`, split at `m`, **solve the left half**, relax all legal left-to-right
edges, then **solve the right half**. All source distances in a cross rectangle
are finalized. Put targets in increasing row order and reachable sources in
**decreasing column order**. This transforms the anti-Monge rectangle to Monge;
SMAWK with source-distance constants computes its minima. Leftmost in this
virtual order is the largest original parent. Transposition alone would not
change anti-Monge to Monge.

Let `p=max(l,m-D+1)` and `q=min(r,m+D-1)`. Partition cross edges into complete
rectangles `[l,m) -> [q,r)` and `[l,p) -> [m,q)`, and scan legal pairs in the
small corner `[p,m) -> [m,q)` directly. Stop recursion at blocks of size `<=D`.
Rectangle work totals $O(N\log(N+1))$. There are $O(N/D)$ larger blocks and
$O(D^2)$ corner pairs per block, hence $O(ND)$ boundary work. For `D=1,2`,
the corner contains no legal pairs. Arbitrary reordering is safe **inside a
complete rectangle**, where every source-target pair exists; it cannot be
applied blindly to the online triangle.

## Example and parent reconstruction

```cpp
#include "convex/monge_shortest_path.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

int main() {
    std::vector<long long> x = {0, 2, 5, 9};
    constexpr long long inf = 1LL << 60;
    auto result = m1une::convex::monge_shortest_path(4, [&](int i, int j) {
        long long gap = x[j]-x[i];
        return gap*gap+3;
    }, inf);
    assert(result.distance == std::vector<long long>({0, 7, 19, 38}));
    std::vector<int> path;
    if (result.distance[3] != inf) {
        for (int v = 3; v != -1; v = result.parent[v]) path.push_back(v);
        std::reverse(path.begin(), path.end());
    }
    assert(path == std::vector<int>({0, 1, 2, 3}));

    auto anti = m1une::convex::anti_monge_shortest_path(4, [&](int i, int j) {
        long long gap = x[j]-x[i];
        return -gap*gap-20;
    }, inf, 2);
    assert(anti.distance == std::vector<long long>({0, inf, -45, -101}));
    assert(anti.parent == std::vector<int>({-1, -1, 0, 0}));
}
```

Known permutations belong to the offline matrix/transition APIs. These graph
solvers intentionally retain the natural topological order and index-step
constraint. A permutation that makes the cost matrix Monge does not by itself
preserve online source availability (`i<j`), or the edge-legality constraint
`j-i>=D`. A reordered column can require a distance that is still unfinished,
or describe a forbidden edge. General source availability after arbitrary
permutations is a different problem, and is not silently inferred from matrix
ordering.
