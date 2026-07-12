---
title: Double-Ended Priority Queue
documentation_of: ../../../ds/heap/double_ended_priority_queue.hpp
---

## Overview

`DoubleEndedPriorityQueue<T, Compare>` is a min-max heap stored in one
contiguous array. It inserts values and removes either extreme in logarithmic
time, while reading both extremes takes constant time.

Unlike an implementation made from two lazily synchronized heaps, this
structure stores each element once and never accumulates stale entries. It uses
$O(N)$ memory even if insertions and removals are interleaved for a long time.

`MinMaxHeap<T, Compare>` is an alias for the same type.

## Ordering

`Compare` defines the ordering and defaults to `std::less<T>`:

* `min()` returns the first element in the `Compare` ordering.
* `max()` returns the last element in the `Compare` ordering.
* Equal values are stored separately, so the structure behaves as a multiset.

With the default comparator these are the usual numeric minimum and maximum.
With `std::greater<T>`, their roles are reversed.

## Interface

```cpp
template <class T, class Compare = std::less<T>>
class DoubleEndedPriorityQueue {
public:
    DoubleEndedPriorityQueue();
    explicit DoubleEndedPriorityQueue(Compare compare);
    DoubleEndedPriorityQueue(
        std::initializer_list<T> values,
        Compare compare = Compare()
    );

    template <class Iterator>
    DoubleEndedPriorityQueue(
        Iterator first,
        Iterator last,
        Compare compare = Compare()
    );

    std::size_t size() const;
    bool empty() const;
    const T& min() const;
    const T& max() const;

    void clear();

    template <class... Args>
    void emplace(Args&&... args);

    void push(const T& value);
    void push(T&& value);
    void pop_min();
    void pop_max();

    const Compare& comparator() const;
};

template <class T, class Compare = std::less<T>>
using MinMaxHeap = DoubleEndedPriorityQueue<T, Compare>;
```

## Complexity

| Method | Description | Complexity |
| --- | --- | --- |
| Default/comparator constructor | Creates an empty queue. | $O(1)$ |
| Initializer-list/range constructor | Inserts all $N$ supplied values. | $O(N\log N)$ |
| `push(value)` | Inserts one value. | $O(\log N)$ |
| `emplace(args...)` | Constructs and inserts one value. | $O(\log N)$ |
| `min()` | Returns the minimum without removing it. | $O(1)$ |
| `max()` | Returns the maximum without removing it. | $O(1)$ |
| `pop_min()` | Removes one minimum value. | $O(\log N)$ |
| `pop_max()` | Removes one maximum value. | $O(\log N)$ |
| `size()` | Returns the number of stored values. | $O(1)$ |
| `empty()` | Returns whether the queue is empty. | $O(1)$ |
| `clear()` | Removes every value. | $O(N)$ |
| `comparator()` | Returns the comparator. | $O(1)$ |

The data structure uses $O(N)$ memory. `min`, `max`, `pop_min`, and `pop_max`
require a nonempty queue. Queries do not mutate the structure; both removal
methods do.

## Example

```cpp
#include "ds/heap/double_ended_priority_queue.hpp"

#include <iostream>

int main() {
    m1une::ds::DoubleEndedPriorityQueue<int> queue = {5, 2, 8, 2};

    std::cout << queue.min() << '\n';  // 2
    queue.pop_min();
    std::cout << queue.max() << '\n';  // 8
    queue.pop_max();

    queue.push(10);
    std::cout << queue.max() << '\n';  // 10
}
```
