---
title: Runs
documentation_of: ../../string/runs.hpp
---

## Overview

A run is a maximal periodic substring whose length is at least twice its
minimum period. This header enumerates every run of an indexable sequence.
It uses zero-based indices and represents substrings as half-open intervals.

The sequence elements only need to support equality comparison. Strings and
vectors of integers can be passed directly.

## Interface

| Interface | Description | Complexity |
| --- | --- | --- |
| `Run` | A result with fields `int period`, `int left`, and `int right`. | -- |
| `vector<Run> enumerate_runs(const Sequence& sequence)` | Returns all runs in lexicographic `(period, left, right)` order. | $O(N \log N)$ time and $O(N \log N)$ memory |

For each returned run, `[left, right)` has minimum period `period`, its length
is at least `2 * period`, and it cannot be extended one position to either side
while preserving that period. The empty sequence has no runs.

## Example

```cpp
#include "string/runs.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "mississippi";
    for (const auto& run : m1une::string::enumerate_runs(text)) {
        std::cout << run.period << ' ' << run.left << ' ' << run.right << '\n';
    }
}
```
