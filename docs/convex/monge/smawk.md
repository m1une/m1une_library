---
title: SMAWK
documentation_of: ../../../convex/monge/smawk.hpp
---

Find row optima of a **fixed complete rectangle**. The matrix must be totally
monotone for the requested comparison and tie rule; Monge suffices for minima,
anti-Monge suffices for maxima. Every submatrix's selected optimum positions
must be nondecreasing in row order, using the same comparison and tie rule.
The property is assumed, not checked.

## Interface

The value-based APIs choose the first column in search order on ties; the
comparison-oracle API lets `prefer` decide. Dimensions mean
natural indices; list overloads mean `value(rows[r], columns[c])` and return
original column IDs in row list order. Lists contain distinct nonnegative IDs;
caller-owned IDs need not be dense. Vectors and arrays convert to spans.

In the signatures below, `V` is a callable and `C` is a strict comparator.
Every function returns `std::vector<int>`.

| Signature | Time / additional memory |
| --- | --- |
| `template<class V, class C = std::less<>> std::vector<int> smawk_row_optima(int row_count, int column_count, V value, C compare = C())` | $O(H+W)$ / $O(H+W)$ |
| `template<class V, class C = std::less<>> std::vector<int> smawk_row_optima(std::span<const int> rows, std::span<const int> columns, V value, C compare = C())` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmin(int row_count, int column_count, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmin(std::span<const int> rows, std::span<const int> columns, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmax(int row_count, int column_count, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class V> std::vector<int> smawk_row_argmax(std::span<const int> rows, std::span<const int> columns, V value)` | $O(H+W)$ / $O(H+W)$ |
| `template<class T> std::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>& matrix)` | $O(H+W)$ / $O(H+W)$ |
| `template<class T> std::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>& matrix)` | $O(H+W)$ / $O(H+W)$ |
| `template<class P> std::vector<int> smawk_row_select(int row_count, int column_count, P prefer)` | $O(H+W)$ / $O(H+W)$ |
| `template<class P> std::vector<int> smawk_row_select(std::span<const int> rows, std::span<const int> columns, P prefer)` | $O(H+W)$ / $O(H+W)$ |

`compare(a,b)` means `a` is strictly better. `prefer(row,current,candidate)`
means replace `current` by `candidate`, including any desired tie decision.
This lower-level comparison oracle supports symbolic invalid entries without
numeric infinity. Its comparisons must describe consistent ordered optima,
and total monotonicity must hold **including the tie rule**. It does not make
arbitrary validity masks safe. For example, strict `<` selects the first
minimum, while `<=` selects the last, under their respective preconditions.

The oracle is independently useful when two entries can be compared directly
without constructing their values: for example, by cancelling common terms in
an implicit cost expression, or comparing valid and symbolic invalid entries
without evaluating an undefined cost. It is a public algorithmic primitive;
convolution is one user, not its defining purpose. Recursive row reduction and
scratch storage remain private in `smawk_detail`.

Only pairs with `current` earlier than `candidate` in the supplied column
order are queried (their original numeric IDs may be reversed). The oracle
must describe a fixed, consistent ordering for each row, with its tie rule
included. In particular, for ordered rows `r < s` and column positions `a < b`,
if the later column is preferred in row `r`, it must remain preferred in row
`s`. This requirement is on positions in the supplied lists, not numeric IDs.

`row_count` and `column_count` must be nonnegative. Matrix overloads assert
rectangular shape. With no columns return `H` copies of `-1`; with no rows
return an empty vector. Callback values may be references and need only the
selected comparison. Inputs are not modified. Complexity counts callback
calls, assuming constant-time comparison and evaluation.

## Ordered example

```cpp
#include "convex/monge/smawk.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<int> rows = {2, 0, 1};
    std::vector<int> columns = {1, 2, 0};
    std::vector<int> row_rank = {1, 2, 0};
    std::vector<int> column_rank = {2, 0, 1};
    auto value = [&](int row, int column) {
        int gap = row_rank[row] - column_rank[column];
        return gap * gap;
    };
    auto answer = m1une::convex::smawk_row_argmin(rows, columns, value);
    assert(answer == std::vector<int>({1, 2, 0}));
}
```

The callback may be evaluated out of row order and all entries must already be
fixed. For a previous layer use [transitions](https://m1une.github.io/m1une_library/convex/monge_transition.hpp);
for a same-array recurrence use [shortest paths](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp).
Direct anti-Monge minimization is available through `anti_monge_transition`;
when using explicit orders, the first column in a reversed list is the
rightmost natural column. See the [guide](https://m1une.github.io/m1une_library/convex/monge/all.hpp).
