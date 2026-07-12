---
title: Minimum Rotation
documentation_of: ../../string/minimum_rotation.hpp
---

## Overview

`minimum_cyclic_shift` finds where the lexicographically smallest rotation of a
sequence begins. If several starting positions produce the same minimum
rotation, it returns the smallest index.

```cpp
#include "string/minimum_rotation.hpp"
```

The function is in `m1une::string` and uses the same Duval-style linear scan as
the previous implementation in `lyndon_factorization.hpp`.

## Interface

```cpp
template <class Sequence>
int minimum_cyclic_shift(const Sequence& sequence);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `minimum_cyclic_shift(sequence)` | Returns the earliest starting index of a lexicographically minimum cyclic shift. | $O(N)$ time and $O(1)$ additional memory |

`Sequence` must provide `size()` and random access through `operator[]`. Its
elements are compared using `operator<`. Strings, vectors, and arrays are
supported.

The empty sequence returns `0`. The function does not construct or modify a
rotation; it only returns its starting index.

`lyndon_factorization.hpp` includes this header, preserving the old include
behavior. New code that only needs minimum rotation can include this smaller
header directly.

## Example

```cpp
#include "string/minimum_rotation.hpp"

#include <iostream>
#include <string>

int main() {
    std::string text = "banana";
    int start = m1une::string::minimum_cyclic_shift(text);
    std::string rotation = text.substr(start) + text.substr(0, start);

    std::cout << start << '\n';     // 5
    std::cout << rotation << '\n';  // abanan
}
```
