---
title: Monge Checks
documentation_of: ../../../convex/monge/check.hpp
---

## Overview

This header checks the Monge or anti-Monge quadrangle inequality.

An `H` by `W` matrix `A` is Monge when

$$
A[i][j] + A[k][l] \le A[i][l] + A[k][j]
$$

for every `i < k` and `j < l`. It is enough to test adjacent rows and columns,
which gives an $O(HW)$ checker.

Anti-Monge reverses the inequality. It supports row maxima directly, or row
minima after reversing one axis; see [SMAWK](smawk.md). Transposition alone
does not reverse the inequality. These checks require a full rectangle:
restrict an interval-cost callback to valid ranges rather than querying
undefined intervals. See the [Monge guide](all.md).

## Worked example: check the matrix you intend to search

Use this checker on small instances while deriving a cost model. For example,
the following table is the same three-request, four-choice table used in the
[SMAWK example](smawk.md):

```cpp
#include "convex/monge/check.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<std::vector<long long>> cost = {
        {5, 9, 21, 41},
        {6, 2, 6, 18},
        {23, 11, 7, 11}
    };
    assert(m1une::convex::is_monge(cost));
    assert(!m1une::convex::is_anti_monge(cost));

    // Negating every entry reverses the inequality.
    for (auto& row : cost) {
        for (auto& entry : row) entry = -entry;
    }
    assert(m1une::convex::is_anti_monge(cost));

    // For an implicit matrix, pass its dimensions and one-entry callback.
    auto value = [](int row, int column) {
        long long gap = row - column;
        return gap * gap;
    };
    assert(m1une::convex::is_monge(3, 4, value));
}
```

Both overloads return a boolean. For example, the first adjacent check is
`5+2 <= 9+6`, and the remaining adjacent checks must also pass.
A successful check justifies the property for this finite table. To use an
optimization for arbitrary problem inputs, prove the inequality for the cost
rule too. These functions do not check the weaker condition of monotone
argmins, and they do not compute any minima.

## Interface

Implicit matrices:

```cpp
template <class Value>
bool is_monge(int row_count, int column_count, Value value);

template <class Value>
bool is_anti_monge(int row_count, int column_count, Value value);
```

Explicit rectangular matrices:

```cpp
template <class T>
bool is_monge(const std::vector<std::vector<T>>& matrix);

template <class T>
bool is_anti_monge(const std::vector<std::vector<T>>& matrix);
```

Empty matrices and matrices with fewer than two rows or columns satisfy both
properties vacuously.

The element type must support addition and comparison. Intermediate sums must
fit in the element type.

## Complexity

$O(HW)$ time and $O(1)$ additional memory.
