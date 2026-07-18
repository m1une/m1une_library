---
title: Offline-Registered Point-Update Range Order Statistics with Sums
documentation_of: ../../../ds/range_query/offline_point_update_range_order_statistics_sum.hpp
---

## Overview

`OfflinePointUpdateRangeOrderStatisticsSum<T, Sum>` maintains a fixed-length
sequence of `(key, weight)` pairs. It supports point replacement, range
frequencies and order statistics, sums selected by key order, and direct
minimum-count threshold searches.

The structure is intended for problems in which every key that may be assigned
to each position is known before processing begins. Initial keys are registered
automatically; future `(position, key)` states are passed to the constructor.
Weights need not be known in advance. Query and update processing is still
sequential: only the possible update states are collected offline.

This is not a fully dynamic wavelet matrix. The sequence length never changes,
and there is no insertion or erasure API. In exchange, precomputed update
handles and flat Fenwick storage make point updates substantially cheaper than
rerouting elements through mutable sequence trees.

## Requirements

`T` must be copyable, sortable by `operator<`, and equality comparable under
the induced ordering. Values `a` and `b` are equivalent when neither `a < b`
nor `b < a` holds.

`Sum{}` must be the additive identity. `Sum` must support copying, addition,
and subtraction. The key-only constructor and `set(position, key)` additionally
require `T` to be convertible to `Sum`. Arithmetic overflow is unchecked.

Every key assigned to a position must have been registered for that position.
Initial keys are always registered. Duplicate candidate pairs and arbitrary
candidate order are accepted and deduplicated. Candidate positions and
unregistered updates are asserted in debug builds; an unregistered update is
an invalid operation.

## Public Interface

All positions are zero-based and all index and key ranges are half-open.

```cpp
template <class T, class Sum = T>
class OfflinePointUpdateRangeOrderStatisticsSum;
```

Let `N` be the fixed sequence length, `V` the number of distinct registered
keys, `H = ceil(log2(V))`, and `M` the number of distinct registered
`(position, key)` states.

### Construction and access

| Method | Description | Complexity |
| --- | --- | --- |
| `OfflinePointUpdateRangeOrderStatisticsSum(const vector<T>& initial_values, const vector<pair<int, T>>& update_candidates)` | Registers candidates and uses every initial key as its weight. | $O(MH\log N)$ time, $O(MH)$ memory |
| `OfflinePointUpdateRangeOrderStatisticsSum(const vector<T>& initial_keys, const vector<Sum>& initial_weights, const vector<pair<int, T>>& update_candidates)` | Registers candidates and builds separate initial weights. | $O(MH\log N)$ time, $O(MH)$ memory |
| `int size() const` | Returns the fixed sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `T access(int position) const` | Returns the active key. | $O(1)$ |
| `T operator[](int position) const` | Equivalent to `access(position)`. | $O(1)$ |
| `Sum weight(int position) const` | Returns the active weight. | $O(1)$ |
| `pair<T, Sum> get(int position) const` | Returns the active key and weight. | $O(1)$ |

Candidate sorting and key compression also cost
`O((N + candidates) log(N + candidates))`; the displayed construction bound
covers the root-to-leaf registrations, handle lookup, and activation work.

### Point updates

| Method | Description | Complexity |
| --- | --- | --- |
| `void set(int position, T key)` | Replaces both key and weight with `key`. | $O(H\log N)$ |
| `void set(int position, T key, const Sum& weight)` | Replaces both key and weight. | $O(H\log N)$ |
| `void set_value(int position, T key)` | Replaces the key and preserves the weight. | $O(H\log N)$ |
| `void set_weight(int position, const Sum& weight)` | Replaces the weight and preserves the key. | $O(H\log N)$ |
| `void add_weight(int position, const Sum& delta)` | Adds to the weight and preserves the key. | $O(H\log N)$ |

The hot path performs one candidate-list binary search, then follows
precomputed Fenwick-local handles. It performs no per-level `lower_bound` and
does not allocate.

### Order-statistic queries

| Method | Description | Complexity |
| --- | --- | --- |
| `int rank(T key, int right) const` | Counts `key` in `[0, right)`. | $O(\log N)$ |
| `int rank(T key, int left, int right) const` | Counts `key` in the index range. | $O(\log N)$ |
| `int range_freq(int left, int right, T upper) const` | Counts keys less than `upper`. | $O(H\log N)$ |
| `int range_freq(int left, int right, T lower, T upper) const` | Counts keys in `[lower, upper)`. | $O(H\log N)$ |
| `T kth_smallest(int left, int right, int k) const` | Returns the zero-based `k`-th smallest key. | $O(H\log N)$ |
| `T kth_largest(int left, int right, int k) const` | Returns the zero-based `k`-th largest key. | $O(H\log N)$ |
| `optional<T> prev_value(int left, int right, T upper) const` | Returns the greatest key below `upper`, or `nullopt`. | $O(H\log N)$ |
| `optional<T> next_value(int left, int right, T lower) const` | Returns the smallest key at least `lower`, or `nullopt`. | $O(H\log N)$ |

The `k`-th methods require `0 <= k < right - left`.

### Sum and threshold queries

| Method | Description | Complexity |
| --- | --- | --- |
| `Sum range_sum(int left, int right) const` | Sums every active weight in the index range. | $O(\log N)$ |
| `Sum range_sum(int left, int right, T upper) const` | Sums weights whose keys are less than `upper`. | $O(H\log N)$ |
| `Sum range_sum(int left, int right, T lower, T upper) const` | Sums weights whose keys are in `[lower, upper)`. | $O(H\log N)$ |
| `Sum sum_k_smallest(int left, int right, int k) const` | Sums the first `k` elements in ascending key order. | $O(H\log N)$ |
| `Sum sum_k_largest(int left, int right, int k) const` | Sums the first `k` elements in descending key order. | $O(H\log N)$ |
| `optional<int> min_count_smallest_sum_at_least(int left, int right, const Sum& target) const` | Returns the minimum ascending-order count whose sum reaches `target`. | $O(H\log N)$ |
| `optional<int> min_count_largest_sum_at_least(int left, int right, const Sum& target) const` | Returns the minimum descending-order count whose sum reaches `target`. | $O(H\log N)$ |

Sum methods allow `0 <= k <= right - left`. Equal keys use increasing current
sequence index for `smallest` and decreasing current sequence index for
`largest`.

The threshold methods require `Sum{} < target` and all active weights in the
structure to be nonnegative while either threshold method is used. They return
`nullopt` when the index-range sum is below `target`. Zero weights are selected
and counted when they occur before the element that reaches the threshold.
Threshold traversal descends the value tree once and uses Fenwick prefix-sum
selection at the final equal-key leaf; it does not binary-search an answer or
call a `sum_k` query repeatedly.

## Implementation

Keys are coordinate-compressed and form the leaves of a value segment tree.
Every registered state contributes its original position to each node on its
root-to-leaf value path. Construction deduplicates those positions and flattens
all node coordinates and Fenwick arrays into CSR-like global vectors.

Each active position contributes count one and its current weight along one
value path. A candidate state stores precomputed `(node, local_position)`
handles, so replacement removes the old path and activates the new path without
searching node coordinate arrays. Ordinary updates and queries allocate no
memory.

## ABC467 G-style example

```cpp
#include "ds/range_query/offline_point_update_range_order_statistics_sum.hpp"

#include <optional>
#include <utility>
#include <vector>

struct Query {
    int position;
    int value;
    int left;
    int right;
    long long target;
};

int main() {
    int n = read_int();
    int q = read_int();
    std::vector<int> initial_values(n);
    read(initial_values);

    std::vector<Query> queries(q);
    std::vector<std::pair<int, int>> candidates;
    candidates.reserve(q);
    for (Query& query : queries) {
        read(
            query.position,
            query.value,
            query.left,
            query.right,
            query.target
        );
        query.position--;
        query.left--;
        candidates.emplace_back(query.position, query.value);
    }

    using Matrix =
        m1une::ds::OfflinePointUpdateRangeOrderStatisticsSum<int, long long>;
    Matrix matrix(initial_values, candidates);
    for (const Query& query : queries) {
        matrix.set(query.position, query.value);
        std::optional<int> answer =
            matrix.min_count_largest_sum_at_least(
                query.left,
                query.right,
                query.target
            );
        print(answer.has_value() ? answer.value() : -1);
    }
}
```

A complete compilable example is under `examples/ds/range_query/`. It is not an
`oj-verify` target.

## Limitations

The sequence length and candidate states are fixed after construction. Memory
is proportional to every distinct registered state times its value-tree path,
so registering many keys for every position can be expensive. Construction is
also heavier than a dynamic wavelet matrix built only from the initial state.
Use the fully dynamic structure when insertion, erasure, or previously unknown
keys are required.
