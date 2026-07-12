---
title: Sliding Window Aggregation Deque
documentation_of: ../../../ds/range_query/sliding_window_aggregation_deque.hpp
---

## Overview

`SlidingWindowAggregationDeque<Monoid>` maintains a deque and the monoid product
of all its elements. It is the double-ended version of sliding window
aggregation (SWAG): elements can be inserted or removed at either end.

The deque is stored in two aggregate stacks. When one stack is empty, the
elements are split approximately in half between the stacks. This gives
amortized constant-time updates while keeping the total product available in
constant time.

`SwagDeque<Monoid>` is a shorter alias.

## Template Requirements

`Monoid` must satisfy `m1une::monoid::IsMonoid`. Its `value_type` must be
copy-constructible, and `Monoid::op(a, b)` must be associative with identity
`Monoid::id()`.

The product follows deque order:

$$
a_0 \mathbin{\mathrm{op}} a_1 \mathbin{\mathrm{op}} \cdots
\mathbin{\mathrm{op}} a_{n-1}.
$$

The monoid does not need to be commutative.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `SlidingWindowAggregationDeque()` | Constructs an empty deque. | $O(1)$ |
| `SlidingWindowAggregationDeque(const std::vector<T>& values)` | Constructs a deque containing `values` in order. | $O(N)$ |
| `SlidingWindowAggregationDeque(std::vector<T>&& values)` | Constructs a deque containing `values` in order, moving the values. | $O(N)$ |
| `void push_front(T value)` | Inserts `value` at the front. | Amortized $O(1)$ |
| `void push_back(T value)` | Inserts `value` at the back. | Amortized $O(1)$ |
| `void pop_front()` | Removes the front element. | Amortized $O(1)$ |
| `void pop_back()` | Removes the back element. | Amortized $O(1)$ |
| `const T& front()` | Returns the front element. | Amortized $O(1)$ |
| `const T& back()` | Returns the back element. | Amortized $O(1)$ |
| `T prod() const`, `T all_prod() const` | Returns the ordered product, or the identity when empty. | $O(1)$ |
| `std::size_t size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the deque is empty. | $O(1)$ |
| `void clear()` | Removes every element. | $O(N)$ |
| `void reserve(std::size_t capacity)` | Reserves both internal stacks. | $O(N)$ |

`pop_front`, `pop_back`, `front`, and `back` require a nonempty deque.

## Example

This maintains a string under updates at both ends:

```cpp
#include "ds/range_query/sliding_window_aggregation_deque.hpp"

#include <iostream>
#include <string>

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& left, const value_type& right) {
        return left + right;
    }
};

int main() {
    m1une::ds::SwagDeque<Concat> deque;
    deque.push_back("b");
    deque.push_front("a");
    deque.push_back("c");
    std::cout << deque.prod() << "\n";  // abc

    deque.pop_front();
    std::cout << deque.prod() << "\n";  // bc
}
```
