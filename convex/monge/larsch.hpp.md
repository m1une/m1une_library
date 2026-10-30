---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/all.hpp
    title: Convex All
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge Matrix Primitives and Algorithm Guide
  - icon: ':heavy_check_mark:'
    path: convex/monge_shortest_path.hpp
    title: Monge and Anti-Monge Forward DAG Shortest Paths
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/anti_monge_shortest_path.test.cpp
    title: verify/convex/monge/anti_monge_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_algorithms.test.cpp
    title: verify/convex/monge/monge_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_dp_optimization.test.cpp
    title: verify/convex/monge/monge_dp_optimization.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/monge_shortest_path.test.cpp
    title: verify/convex/monge/monge_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/convex/monge/ordered_matrix.test.cpp
    title: verify/convex/monge/ordered_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"convex/monge/larsch.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace convex {\n\n//\
    \ Online minima of a lower-triangular totally monotone matrix (column <= row).\n\
    // Leftmost ties. Before answering row r, only columns <= r are accessed, even\n\
    // when evaluating future rows. Finalize column r+1 after receiving answer r.\n\
    // O(N) total time/evaluations/memory; an individual next_argmin can take O(N).\n\
    // Value is stored directly, with no type-erased callable. Use CTAD: Larsch q(n,f).\n\
    template <class Value>\nclass Larsch {\n    struct Level {\n        int size;\n\
    \        int row = 0;\n        int column_row = 0;\n        int boundary = 0;\n\
    \        std::vector<int> columns;\n        explicit Level(int n) : size(n) {}\n\
    \    };\n\n    int _size;\n    Value _value;\n    std::vector<Level> _levels;\n\
    \n    auto entry(int depth, int row, int column) {\n        for (int d = depth;\
    \ d > 0; --d) {\n            row = row * 2 + 1;\n            column = _levels[d].columns[column];\n\
    \        }\n        return _value(row, column);\n    }\n\n    int next_column(int\
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
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_CONVEX_MONGE_LARSCH_HPP\n#define M1UNE_CONVEX_MONGE_LARSCH_HPP\
    \ 1\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace convex {\n\n// Online minima of a lower-triangular totally\
    \ monotone matrix (column <= row).\n// Leftmost ties. Before answering row r,\
    \ only columns <= r are accessed, even\n// when evaluating future rows. Finalize\
    \ column r+1 after receiving answer r.\n// O(N) total time/evaluations/memory;\
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
    \ m1une\n\n#endif  // M1UNE_CONVEX_MONGE_LARSCH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: convex/monge/larsch.hpp
  requiredBy:
  - convex/monge_shortest_path.hpp
  - convex/monge/all.hpp
  - convex/all.hpp
  - convex/all.hpp
  timestamp: '2026-10-30 15:56:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_dp_optimization.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/monge_algorithms.test.cpp
  - verify/convex/monge/anti_monge_shortest_path.test.cpp
  - verify/convex/monge/monge_shortest_path.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
  - verify/convex/monge/ordered_matrix.test.cpp
documentation_of: convex/monge/larsch.hpp
layout: document
title: LARSCH Online Matrix Minima
---

`m1une::convex::Larsch<Value>` finds leftmost row minima in a lower triangle:
row `r` admits columns `0..r`. The triangular matrix must be totally monotone
for leftmost minima: leftmost optimal positions in every completely defined
submatrix are nondecreasing. Monge inequalities on fully defined rectangles
are sufficient. No infinity padding or property check is performed.

Rows are answered sequentially. During the call answering row `r`, callbacks
can examine **future rows** but only columns `0..r`. After answer `r`, finalize
values associated with column `r+1` before requesting the next answer. Values
of ready columns must remain fixed at every row; future entries must already
be evaluable for these columns. This is the guarantee that permits dependent
DP, unlike ordinary offline SMAWK.

## Interface

Use class template argument deduction, e.g. `Larsch search(n, value)`.
`Value` is stored directly and may be move-only. Values support `<`, `>`, `<=`.
The primitive is movable; a moved-from object is only destructible/assignable.
It cannot be copied when the callback cannot be copied. Each result is a
natural column index, with the smallest index winning ties.

| Signature | Meaning | Time |
| --- | --- | --- |
| `explicit Larsch(int size, Value value)` | Construct with nonnegative row count. | $O(N)$ allocated capacity, $O(\log(N+1))$ control work |
| `int size() const` | Number of rows. | $O(1)$ |
| `int processed_rows() const` | Answers already returned. | $O(1)$ |
| `bool finished() const` | All rows answered (also true for zero rows). | $O(1)$ |
| `int next_argmin()` | Advance one row, return its leftmost minimum. Asserts not finished. | $O(N)$ worst case per call; $O(N)$ total over all $N$ calls |

Memory and callback evaluations total $O(N)$, with constant-time arithmetic
and entry evaluation. Reduction levels have geometrically decreasing sizes;
queries map through their column stacks without runtime type erasure. The
weighted sum of mapping depths is also linear. No `const` method advances state.

```cpp
#include "convex/monge/larsch.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<long long> dp(5);
    m1une::convex::Larsch search(4, [&](int row, int column) {
        long long gap = row+1-column;
        return dp[column] + gap*gap;
    });
    for (int to = 1; to < 5; ++to) {
        int from = search.next_argmin();
        long long gap = to-from;
        dp[to] = dp[from] + gap*gap;
    }
    assert(dp == std::vector<long long>({0, 1, 2, 3, 4}));
}
```

For this complete forward-DAG recurrence, prefer the public
[`monge_shortest_path`](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp),
which also supports a minimum index step. Arbitrary row/column permutations
are deliberately confined to offline primitives: an order must respect column
availability to be valid online.
