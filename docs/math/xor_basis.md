---
title: XOR Basis
documentation_of: ../../math/xor_basis.hpp
---

## Overview

`XorBasis` maintains a linearly independent basis of unsigned integers, viewed
as vectors over $\mathbb{F}_2$. It represents exactly the values obtainable by
XORing a subset of the inserted values.

```cpp
#include "math/xor_basis.hpp"
```

The class is in `m1une::math`.

## Template Requirements

```cpp
template <std::unsigned_integral UInt = unsigned long long>
class XorBasis;
```

`UInt` must be an unsigned integer type other than `bool`. The default basis
handles all bits of `unsigned long long`. Memory usage is $O(B)$, where
$B = std::numeric_limits<UInt>::digits$.

## Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `XorBasis()` | Constructs an empty basis. | $O(B)$ |
| `XorBasis(first, last)` | Inserts every value in the iterator range. | $O(NB)$ |
| `XorBasis(values)` | Inserts an initializer list. | $O(NB)$ |
| `bool insert(UInt value)` | Inserts `value`; returns whether the rank increased. | $O(B)$ |
| `bool contains(UInt value) const` | Tests whether `value` is representable. | $O(B)$ |
| `int rank() const` | Returns the number of independent vectors. | $O(1)$ |
| `bool empty() const` | Tests whether the rank is zero. | $O(1)$ |
| `void clear()` | Removes all vectors. | $O(B)$ |
| `int merge(const XorBasis& other)` | Inserts another basis and returns the rank increase. | $O(B^2)$ |
| `UInt min_xor(UInt value = 0) const` | Minimizes `value ^ x` over representable `x`. | $O(B)$ |
| `UInt max_xor(UInt value = 0) const` | Maximizes `value ^ x` over representable `x`. | $O(B)$ |
| `UInt kth_smallest(UInt index) const` | Returns the zero-based `index`-th smallest representable value. | $O(B)$ |
| `std::vector<UInt> vectors() const` | Returns independent vectors in increasing pivot-bit order. | $O(B)$ |

`insert`, `merge`, and `clear` mutate the basis. All query methods are `const`.
Duplicate or dependent insertions leave the basis unchanged. Zero is always
representable and does not increase the rank.

There are exactly $2^{\text{rank}}$ distinct representable values.
`kth_smallest(index)` asserts that `index` is in this range when the count fits
in `UInt`. At full rank, every `UInt` value is representable, so every possible
`UInt` index is valid.

## Example

```cpp
#include "math/xor_basis.hpp"

#include <cassert>

int main() {
    m1une::math::XorBasis<unsigned> basis{3, 5, 6};

    assert(basis.rank() == 2);
    assert(basis.contains(6));
    assert(!basis.contains(1));
    assert(basis.max_xor() == 6);
    assert(basis.kth_smallest(2) == 5);
}
```
