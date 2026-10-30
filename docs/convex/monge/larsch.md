---
title: LARSCH Online Matrix Minima
documentation_of: ../../../convex/monge/larsch.hpp
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
