---
title: Static Range Mode Query
documentation_of: ../../../ds/range_query/static_range_mode_query.hpp
---

## Overview

`StaticRangeModeQuery<T>` preprocesses a static array and finds a mode of any
nonempty subarray `[left, right)`. A query returns the mode and its frequency.
If several values have maximum frequency, any one of them may be returned.

The array is divided into square-root-sized blocks. Modes of all complete-block
ranges and value frequencies at every block boundary are precomputed. Only the
two partial boundary blocks must be inspected during a query.

## Requirements

`T` must support `<` and equality consistently. The values are coordinate
compressed during construction. The input array is not modified.

## Complexity

| Operation | Time | Memory |
| --- | --- | --- |
| Construction | $O(N\sqrt N + N\log N)$ | $O(N\sqrt N)$ |
| Query | $O(\sqrt N)$ | $O(\sqrt N)$ temporary memory |

## Methods

| Method | Complexity | Description |
| --- | --- | --- |
| `StaticRangeModeQuery()` | $O(1)$ | Constructs an empty structure. |
| `explicit StaticRangeModeQuery(const std::vector<T>& values)` | $O(N\sqrt N + N\log N)$ | Builds the static structure. |
| `result_type query(int left, int right)` | $O(\sqrt N)$ | Returns `{mode, frequency}` for nonempty `[left, right)`. |
| `result_type mode(int left, int right)` | $O(\sqrt N)$ | Alias of `query`. |
| `int size() const` | $O(1)$ | Returns the array size. |
| `bool empty() const` | $O(1)$ | Returns whether the array is empty. |
| `int block_size() const` | $O(1)$ | Returns the selected block size. |

`result_type` is `std::pair<T, int>`. Queries reuse internal frequency
workspace, so `query` and `mode` are intentionally non-`const`. They do not
change the represented array or any future answer.

## Example

```cpp
#include "ds/range_query/static_range_mode_query.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {1, 2, 2, 3, 3, 3};
    m1une::ds::StaticRangeModeQuery<int> modes(values);

    auto answer = modes.query(1, 6);
    std::cout << answer.first << " " << answer.second << "\n"; // 3 3
}
```
