---
title: Merge Sort Tree
documentation_of: ../../../ds/range_query/merge_sort_tree.hpp
---

## Overview

`MergeSortTree<T, Sum>` preprocesses a static sequence by storing sorted values
at every segment-tree node. For summable types, it also stores prefix sums. It
supports range frequency and sum queries, order statistics, and
predecessor/successor searches.

Use a merge sort tree when values are arbitrary ordered objects or when a
simple static range-counting structure is convenient. For integral values and
many order-statistic queries, `WaveletMatrix` uses less memory and has faster
queries.

## Requirements

`T` must be copyable and provide a strict weak ordering through `operator<`.
Values equivalent under that ordering are treated as equal. The input sequence
is copied and never modified.

`Sum` defaults to `T`. Sum methods are available when `T` is explicitly
convertible to `Sum`, `Sum{}` is the additive identity, and addition and
subtraction produce values convertible to `Sum`. Choose a sufficiently wide
type, such as `MergeSortTree<int, long long>`, because arithmetic uses `Sum`
and does not check for overflow. Ordered nonnumeric types can still use every
nonsum method.

## Public Interface

All index ranges are zero-based and half-open.

```cpp
template <class T, class Sum = T>
class MergeSortTree;
```

| Method | Description | Complexity |
| --- | --- | --- |
| `MergeSortTree()` | Constructs an empty tree. | $O(1)$ |
| `explicit MergeSortTree(const std::vector<T>& values)` | Builds the tree. | $O(N\log N)$ time and memory |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `const T& get(int position) const` | Returns the original value at `position`. | $O(1)$ |
| `const T& operator[](int position) const` | Equivalent to `get(position)`. | $O(1)$ |
| `int count_less(int left, int right, const T& upper) const` | Counts values less than `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `int count_less_equal(int left, int right, const T& upper) const` | Counts values at most `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `int count(int left, int right, const T& value) const` | Counts values equivalent to `value` in `[left, right)`. | $O(\log^2 N)$ |
| `int count(int left, int right, const T& lower, const T& upper) const` | Counts values in `[lower, upper)` within `[left, right)`. | $O(\log^2 N)$ |
| `Sum range_sum(int left, int right) const` | Returns the sum of all values in `[left, right)`. | $O(1)$ |
| `Sum sum_less(int left, int right, const T& upper) const` | Sums values less than `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum_less_equal(int left, int right, const T& upper) const` | Sums values at most `upper` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum(int left, int right, const T& value) const` | Sums values equivalent to `value` in `[left, right)`. | $O(\log^2 N)$ |
| `Sum sum(int left, int right, const T& lower, const T& upper) const` | Sums values in `[lower, upper)` within `[left, right)`. | $O(\log^2 N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest value. | $O(\log U\log^2 N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest value. | $O(\log U\log^2 N)$ |
| `std::optional<T> prev_value(int left, int right, const T& upper) const` | Returns the greatest value less than `upper`, or `nullopt`. | $O(\log^2 N)$ |
| `std::optional<T> next_value(int left, int right, const T& lower) const` | Returns the smallest value at least `lower`, or `nullopt`. | $O(\log^2 N)$ |

Here, $U$ is the number of distinct values stored in the complete sequence.
The order-statistic methods require `0 <= k < right - left`. Empty ranges are
valid for every count, sum, and predecessor/successor query. All sum methods
sum the stored values themselves; the bounds only filter which values are
included.

## Example

```cpp
#include "ds/range_query/merge_sort_tree.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {5, 1, 4, 1, 3};
    m1une::ds::MergeSortTree<int, long long> tree(values);

    std::cout << tree.count(0, 5, 1) << "\n";          // 2
    std::cout << tree.sum_less_equal(0, 5, 3) << "\n"; // 5
    std::cout << tree.sum(1, 5, 2, 5) << "\n";         // 7
    std::cout << tree.kth_smallest(0, 5, 2) << "\n";   // 3
}
```
