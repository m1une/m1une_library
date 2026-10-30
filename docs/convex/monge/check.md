---
title: Monge and Anti-Monge Checks
documentation_of: ../../../convex/monge/check.hpp
---

Check adjacent $2\times2$ inequalities of a complete rectangle. Monge means
$A(r,c)+A(r+1,c+1)\le A(r,c+1)+A(r+1,c)$; anti-Monge uses $\ge$.
For finite ordered arithmetic these local conditions imply all rectangle
inequalities by summation. Neither function checks total monotonicity alone.

All APIs use `m1une::convex`. `V` receives `(row,column)` and returns a finite
value supporting addition and comparison. Sums must fit in the value type;
NaNs and arithmetic with infinity are not supported. These are offline
checks and do not mutate their inputs. No optimum is returned, so ties are
irrelevant and equality satisfies both properties.

## Interface

| Signature | Time | Extra memory |
| --- | --- | --- |
| `template<class V> bool is_monge(int row_count, int column_count, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_anti_monge(int row_count, int column_count, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_monge(std::span<const int> rows, std::span<const int> columns, V value)` | $O(HW)$ | $O(1)$ |
| `template<class V> bool is_anti_monge(std::span<const int> rows, std::span<const int> columns, V value)` | $O(HW)$ | $O(1)$ |
| `template<class T> bool is_monge(const std::vector<std::vector<T>>& matrix)` | $O(H+HW)$ | $O(1)$ |
| `template<class T> bool is_anti_monge(const std::vector<std::vector<T>>& matrix)` | $O(H+HW)$ | $O(1)$ |

Dimensions must be nonnegative; dense overloads assert rectangular shape.
A dimension below two makes the inequality vacuous and returns `true`.
The ordered forms check `value(rows[r],columns[c])`, with distinct nonnegative
IDs in each list. Anti-Monge is implemented through reversed virtual column
order and is directly callable without building a reverse permutation.

```cpp
#include "convex/monge/check.hpp"
#include <cassert>

int main() {
    auto squared_gap = [](int r, int c) { return (r-c)*(r-c); };
    assert(m1une::convex::is_monge(4, 6, squared_gap));
    assert(m1une::convex::is_anti_monge(4, 6,
        [&](int r, int c) { return -squared_gap(r,c); }));
}
```
