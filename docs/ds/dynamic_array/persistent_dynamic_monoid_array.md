---
title: Persistent Dynamic Monoid Array
documentation_of: ../../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp
---

## Overview

`PersistentDynamicMonoidArray` is a path-copying implicit treap for dynamic sequences with range product queries. Updates return a new sequence and leave older versions available.

Nodes live in a shared stable-slot pool and store integer child indices. Intrusive reference counts reclaim nodes after their final dependent version or parent is released, and later updates reuse their slots.

Each node stores both forward and reversed products, so range reversal works for non-commutative monoids.

`set_inplace` is a copy-on-write point assignment for a mutable working
version. It preserves other versions, clones shared search-path nodes, and
updates unique nodes directly. Other update methods retain their
persistent-returning semantics.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const`, `bool empty() const` | Returns the sequence size or whether it is empty. | $O(1)$ |
| `void release()` | Releases this version immediately and makes this handle empty. | $O(F)$ |
| `std::size_t node_count() const` | Returns live nodes in the shared version family. | $O(1)$ |
| `insert`, `push_back`, `push_front`, `append` | Return a version with values inserted. Another version sharing the pool reuses its nodes; an independently constructed array is copied into this pool. | Expected $O(\log N)$ for one value or a shared-pool version; $O(M + \log N)$ for a vector or independent array |
| `erase`, `pop_back`, `pop_front` | Return a version with values removed. | Expected $O(\log N)$ |
| `set` | Returns a version with one value replaced. | Expected $O(\log N)$ |
| `set_inplace(int pos, T value)` | Replaces one value in this version using copy-on-write. | Expected $O(\log N)$ |
| `reverse`, `rotate` | Return versions with sequence order changed. | Expected $O(\log N)$; whole-sequence `reverse()` is $O(1)$ |
| `prod`, `all_prod` | Return monoid products over a range or the whole sequence. | Expected $O(\log N)$ for `prod`; $O(1)$ for `all_prod` |
| `split`, `split_off` | Return persistent split versions. | Expected $O(\log N)$ |
| `to_vector` | Dumps a range or the whole sequence. | $O(K + \log N)$ for a range; $O(N)$ for all values |

Here $F$ is the number of nodes that become unreachable. Destruction and
assignment release roots automatically.

## Notes

Order-aware monoids should store relative order information such as `size` and `ord`, not immutable global indices. For example, `monoid::ArgMin` returns `ord` relative to the queried range, so it remains valid after insertions, deletions, and reversals.

## Example

```cpp
#include "ds/dynamic_array/persistent_dynamic_monoid_array.hpp"
#include "monoid/add.hpp"
#include <iostream>

using Monoid = m1une::monoid::Add<long long>;
using Array = m1une::ds::PersistentDynamicMonoidArray<Monoid>;

int main() {
    Array a = {1, 2, 3, 4, 5};
    auto b = a.reverse(1, 5);
    auto c = b.set(2, 10);

    // a is still {1, 2, 3, 4, 5}
    // c is {1, 5, 10, 3, 2}
    long long sum = c.prod(0, 4);
    std::cout << sum << "\n";
}
```
