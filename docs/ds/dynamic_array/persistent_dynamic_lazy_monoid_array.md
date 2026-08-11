---
title: Persistent Dynamic Lazy Monoid Array
documentation_of: ../../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
---

## Overview

`PersistentDynamicLazyMonoidArray` is a path-copying implicit treap for dynamic sequences with lazy range actions and range product queries. Updates return a new sequence and keep previous versions unchanged.

Nodes live in a shared stable-slot pool and store integer child indices. Intrusive reference counts reclaim nodes after their final dependent version or parent is released, and later updates reuse their slots.

It supports insertion, deletion, reversal, rotation, point assignment, range application, range products, splitting, and concatenation.

`set_inplace` and `apply_inplace` mutate a working version with copy-on-write.
They clone shared path nodes before writes, including propagation of pending
reversal and action tags, while unique nodes are reused. Other live versions
remain unchanged. Structural treap operations keep their persistent-returning
interface.

## Template Parameters

* `ActedMonoid`: An acted monoid satisfying `m1une::acted_monoid::IsActedMonoid`.

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
| `apply` | Returns a version with an operator applied to one value or a half-open range. | Expected $O(\log N)$ |
| `apply_inplace(int pos, const F& f)` | Applies an operator to one value in this version using copy-on-write. | Expected $O(\log N)$ |
| `apply_inplace(int l, int r, const F& f)` | Applies an operator to `[l, r)` in this version using copy-on-write. | Expected $O(\log N)$ |
| `reverse`, `rotate` | Return versions with sequence order changed. | Expected $O(\log N)$; whole-sequence `reverse()` is $O(1)$ |
| `prod`, `all_prod` | Return acted-monoid products over a range or the whole sequence. | Expected $O(\log N)$ for `prod`; $O(1)$ for `all_prod` |
| `split`, `split_off` | Return persistent split versions. | Expected $O(\log N)$ |
| `to_vector` | Dumps a range or the whole sequence without mutating the version. | $O(K + \log N)$ for a range; $O(N)$ for all values |

Here $F$ is the number of nodes that become unreachable. Destruction and
assignment release roots automatically.

## Notes

Order-aware acted monoids should store relative order information such as `size`, `ord`, or `ord_sum`, not immutable global indices. Arithmetic-progression acted monoids use range-local order; to apply a global formula on `[l, r)`, shift the constant term by `a * l`.

## Example

```cpp
#include "acted_monoid/range_add_range_sum.hpp"
#include "ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp"
#include <iostream>

using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
using Array = m1une::ds::PersistentDynamicLazyMonoidArray<AM>;

int main() {
    Array a(std::vector<long long>{1, 2, 3, 4, 5});
    auto b = a.apply(1, 4, 10);
    auto c = b.reverse(1, 5);

    // a is still {1, 2, 3, 4, 5}
    // c is {1, 5, 14, 13, 12}
    long long sum = c.prod(0, 5).sum;
    std::cout << sum << "\n";
}
```
