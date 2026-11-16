---
title: Rolling Hash Monoid
documentation_of: ../../monoid/rolling_hash.hpp
---

## Overview

A monoid for maintaining a dynamic rolling hash of a string on a Segment Tree. This allows you to update characters in $O(\log N)$ and query the hash of any substring in $O(\log N)$.

The defaults are $Base = 10007$ and $Mod = 2^{61}-1$.
Different strings can have equal hashes. Hash equality is a probabilistic
comparison, and the fixed default base gives no protection against inputs
chosen to cause collisions. Compare lengths as well as hash values.

## Data Structure

* `using value_type = std::pair<long long, long long>;`
  The state maintained in each node of the Segment Tree.
  * `first`: The hash value of the string segment.
  * `second`: The base power, calculated as $Base^{\text{length of the segment}} \pmod{Mod}$.

## Initialization & Element Creation

When initializing the Segment Tree or updating a single point, you must convert a single character into the `value_type` pair.
**Always use the `make(c)` helper method** to automatically generate the correct element.

### `static constexpr value_type make(long long c)`

Generates a valid monoid element for a single character.

* **Parameters:** `c` is the character code (or integer) for one element.
* **Returns:** A `value_type` pair initialized as `{c % Mod, Base % Mod}`.

## Interface and Complexity

```cpp
using value_type = std::pair<long long, long long>;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `static constexpr value_type id()` | Returns the identity aggregate representing no elements. | $O(1)$ |
| `static constexpr value_type op(const value_type& a, const value_type& b)` | Combines the two aggregates in left-to-right order. | $O(1)$ |
| `static constexpr value_type make(long long c)` | Creates a one-element aggregate. | $O(1)$ |

Bounds count operations on the stored scalar type as $O(1)$; account for its cost when using a larger numeric type.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/rolling_hash.hpp"
#include <iostream>
#include <string>
#include <vector>

// Use the default Base and Mod by providing empty angle brackets <>
using RHMonoid = m1une::monoid::RollingHash<>;

int main() {
    std::string S = "abracadabra";
    int N = S.length();

    // 1. Convert characters into leaf aggregates using `make`
    std::vector<RHMonoid::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        // Pass the character S[i] to `make`
        init_data[i] = RHMonoid::make(S[i]);
    }

    // 2. Build the Segment Tree
    m1une::ds::Segtree<RHMonoid> seg(init_data);

    // 3. Point Update: Change S[1] ('b') to 'x' using `make`
    seg.set(1, RHMonoid::make('x'));

    // 4. Query Range: Get the hash of S[0..4] (indices [0, 5))
    // The returned value is a pair. Extract `.first` to get the actual hash.
    long long hash_val = seg.prod(0, 5).first;
    std::cout << hash_val << "\n";

    return 0;
}
```
