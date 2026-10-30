---
title: Monotone Matrix Minima
documentation_of: ../../../convex/monge/monotone_minima.hpp
---

Search a fixed complete rectangle whose **leftmost optimum positions are
nondecreasing with row position**. Only this whole-matrix property is needed;
total monotonicity and Monge are stronger sufficient conditions. The callback
must return fixed entries; this routine does not compute an online recurrence.

Use `m1une::convex`. `compare(a,b)` is strict: `a` is better than `b`.
For minima use `<`, for maxima use `>`. Ties select the first column in the
search order. Ordered calls search `value(rows[r],columns[c])` and return
original column IDs compactly in row list order. Lists contain distinct
nonnegative IDs. Empty columns yield `-1` for each row; empty rows yield no
answers. Dense matrix overloads assert rectangular shape. Dimensions must be
nonnegative. The matrix and lists are not changed.

## Interface

| Signature | Time | Memory including answers |
| --- | --- | --- |
| `template<class V, class C = std::less<>> std::vector<int> monotone_row_optima(int row_count, int column_count, V value, C compare = C())` | $O(H+W\log(H+1))$ | $O(H+\log(H+1))$ |
| `template<class V, class C = std::less<>> std::vector<int> monotone_row_optima(std::span<const int> rows, std::span<const int> columns, V value, C compare = C())` | same | same |
| `template<class V> std::vector<int> monotone_row_argmin(int row_count, int column_count, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmin(std::span<const int> rows, std::span<const int> columns, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmax(int row_count, int column_count, V value)` | same | same |
| `template<class V> std::vector<int> monotone_row_argmax(std::span<const int> rows, std::span<const int> columns, V value)` | same | same |
| `template<class T> std::vector<int> monotone_row_argmin(const std::vector<std::vector<T>>& matrix)` | same | same |
| `template<class T> std::vector<int> monotone_row_argmax(const std::vector<std::vector<T>>& matrix)` | same | same |

Bounds assume constant-time entry evaluation and comparison. A middle row is
scanned, then the rows above/below search only the feasible column ranges.
For totally monotone matrices, [SMAWK](https://m1une.github.io/m1une_library/convex/monge/smawk.hpp) gives a linear bound.

```cpp
#include "convex/monge/monotone_minima.hpp"
#include <cassert>
#include <vector>

int main() {
    auto answer = m1une::convex::monotone_row_argmin(4, 5, [](int r, int c) {
        return (r-c)*(r-c);
    });
    assert(answer == std::vector<int>({0, 1, 2, 3}));
}
```

The finalized-layer wrapper is named
[`monotone_transition`](https://m1une.github.io/m1une_library/convex/monge_transition.hpp)
after its actual precondition; the divide-and-conquer implementation is internal.
