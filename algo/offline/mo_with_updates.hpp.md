---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algo/all.hpp
    title: Algorithms All
  - icon: ':warning:'
    path: algo/offline/all.hpp
    title: Offline Algorithms All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/offline/mo_with_updates.test.cpp
    title: verify/algo/offline/mo_with_updates.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"algo/offline/mo_with_updates.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <cstddef>\n#include <limits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Offline Mo ordering\
    \ in (left, right, update time). Array values and the\n// before/after values\
    \ of each point update are owned by the caller.\nstruct MoWithUpdates {\n    struct\
    \ Query {\n        int left;\n        int right;\n        int time;\n        int\
    \ id;\n    };\n\n   private:\n    int _n;\n    int _update_count = 0;\n    std::vector<Query>\
    \ _queries;\n\n   public:\n    MoWithUpdates() : _n(0) {}\n\n    explicit MoWithUpdates(int\
    \ n) : _n(n) { assert(0 <= n); }\n\n    int size() const { return _n; }\n\n  \
    \  int query_count() const { return int(_queries.size()); }\n\n    int update_count()\
    \ const { return _update_count; }\n\n    bool empty() const { return _queries.empty();\
    \ }\n\n    const std::vector<Query>& queries() const { return _queries; }\n\n\
    \    void reserve(int query_capacity) {\n        assert(0 <= query_capacity);\n\
    \        _queries.reserve(query_capacity);\n    }\n\n    void clear() {\n    \
    \    _queries.clear();\n        _update_count = 0;\n    }\n\n    // Registers\
    \ one update and returns its zero-based ID. Time t means that\n    // updates\
    \ [0, t) have been applied, including any no-op assignments.\n    int add_update()\
    \ {\n        assert(_update_count < std::numeric_limits<int>::max());\n      \
    \  return _update_count++;\n    }\n\n    int add_query(int left, int right) {\
    \ return add_query(left, right, _update_count); }\n\n    // Historical times are\
    \ allowed, but the updates must already be registered.\n    int add_query(int\
    \ left, int right, int time) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        assert(0 <= time && time <= _update_count);\n        assert(_queries.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{left, right, time, id});\n        return id;\n\
    \    }\n\n    std::vector<int> order(int block_size = 0) const {\n        const\
    \ int q = query_count();\n        if (q == 0) return {};\n        auto times =\
    \ std::minmax_element(_queries.begin(), _queries.end(),\n            [](const\
    \ Query& a, const Query& b) { return a.time < b.time; });\n        const int time_span\
    \ = times.second->time - times.first->time;\n        if (block_size <= 0) {\n\
    \            const double n = _n;\n            const double static_size = n /\
    \ std::sqrt(double(q));\n            const double dynamic_size = std::cbrt(n *\
    \ n * double(time_span) / double(q));\n            const double estimate = std::max(static_size,\
    \ dynamic_size);\n            block_size = int(std::clamp(estimate, 1.0, double(std::max(1,\
    \ _n))));\n        }\n\n        struct Entry {\n            int left_block;\n\
    \            int right_block;\n            int time;\n            int id;\n  \
    \      };\n        std::vector<Entry> entries;\n        entries.reserve(q);\n\
    \        for (const Query& query : _queries) {\n            entries.push_back(Entry{\n\
    \                query.left / block_size, query.right / block_size, query.time,\
    \ query.id});\n        }\n        std::sort(entries.begin(), entries.end(), [&](const\
    \ Entry& a, const Entry& b) {\n            if (a.left_block != b.left_block) return\
    \ a.left_block < b.left_block;\n            const bool reverse_right = (a.left_block\
    \ & 1) != 0;\n            if (time_span != 0) {\n                if (a.right_block\
    \ != b.right_block) {\n                    return reverse_right ? a.right_block\
    \ > b.right_block : a.right_block < b.right_block;\n                }\n      \
    \          if (a.time != b.time) {\n                    return ((a.left_block\
    \ ^ a.right_block) & 1) ? a.time > b.time : a.time < b.time;\n               \
    \ }\n            }\n            const int a_right = _queries[a.id].right;\n  \
    \          const int b_right = _queries[b.id].right;\n            if (a_right\
    \ != b_right) return reverse_right ? a_right > b_right : a_right < b_right;\n\
    \            return a.id < b.id;\n        });\n        std::vector<int> result;\n\
    \        result.reserve(q);\n        for (const Entry& entry : entries) result.push_back(entry.id);\n\
    \        return result;\n    }\n\n    // apply(id, left, right) moves time id\
    \ -> id + 1; undo(id, left, right)\n    // reverses that update. Both must update\
    \ the array even outside the active\n    // range, and must repair the maintained\
    \ answer when necessary inside it.\n    template <class AddLeft, class AddRight,\
    \ class RemoveLeft, class RemoveRight,\n              class Apply, class Undo,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right,\n             Apply apply, Undo undo,\
    \ Answer answer, int block_size = 0) const {\n        int left = 0;\n        int\
    \ right = 0;\n        int time = 0;\n        for (int query_index : order(block_size))\
    \ {\n            const Query& query = _queries[query_index];\n            while\
    \ (time < query.time) {\n                apply(time, left, right);\n         \
    \       ++time;\n            }\n            while (query.time < time) {\n    \
    \            --time;\n                undo(time, left, right);\n            }\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    template <class Add, class Remove, class Apply, class\
    \ Undo, class Answer>\n    void run(Add add, Remove remove, Apply apply, Undo\
    \ undo, Answer answer,\n             int block_size = 0) const {\n        run(add,\
    \ add, remove, remove, apply, undo, answer, block_size);\n    }\n};\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP\n#define M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <cstddef>\n\
    #include <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n\
    // Offline Mo ordering in (left, right, update time). Array values and the\n//\
    \ before/after values of each point update are owned by the caller.\nstruct MoWithUpdates\
    \ {\n    struct Query {\n        int left;\n        int right;\n        int time;\n\
    \        int id;\n    };\n\n   private:\n    int _n;\n    int _update_count =\
    \ 0;\n    std::vector<Query> _queries;\n\n   public:\n    MoWithUpdates() : _n(0)\
    \ {}\n\n    explicit MoWithUpdates(int n) : _n(n) { assert(0 <= n); }\n\n    int\
    \ size() const { return _n; }\n\n    int query_count() const { return int(_queries.size());\
    \ }\n\n    int update_count() const { return _update_count; }\n\n    bool empty()\
    \ const { return _queries.empty(); }\n\n    const std::vector<Query>& queries()\
    \ const { return _queries; }\n\n    void reserve(int query_capacity) {\n     \
    \   assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \    }\n\n    void clear() {\n        _queries.clear();\n        _update_count\
    \ = 0;\n    }\n\n    // Registers one update and returns its zero-based ID. Time\
    \ t means that\n    // updates [0, t) have been applied, including any no-op assignments.\n\
    \    int add_update() {\n        assert(_update_count < std::numeric_limits<int>::max());\n\
    \        return _update_count++;\n    }\n\n    int add_query(int left, int right)\
    \ { return add_query(left, right, _update_count); }\n\n    // Historical times\
    \ are allowed, but the updates must already be registered.\n    int add_query(int\
    \ left, int right, int time) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        assert(0 <= time && time <= _update_count);\n        assert(_queries.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{left, right, time, id});\n        return id;\n\
    \    }\n\n    std::vector<int> order(int block_size = 0) const {\n        const\
    \ int q = query_count();\n        if (q == 0) return {};\n        auto times =\
    \ std::minmax_element(_queries.begin(), _queries.end(),\n            [](const\
    \ Query& a, const Query& b) { return a.time < b.time; });\n        const int time_span\
    \ = times.second->time - times.first->time;\n        if (block_size <= 0) {\n\
    \            const double n = _n;\n            const double static_size = n /\
    \ std::sqrt(double(q));\n            const double dynamic_size = std::cbrt(n *\
    \ n * double(time_span) / double(q));\n            const double estimate = std::max(static_size,\
    \ dynamic_size);\n            block_size = int(std::clamp(estimate, 1.0, double(std::max(1,\
    \ _n))));\n        }\n\n        struct Entry {\n            int left_block;\n\
    \            int right_block;\n            int time;\n            int id;\n  \
    \      };\n        std::vector<Entry> entries;\n        entries.reserve(q);\n\
    \        for (const Query& query : _queries) {\n            entries.push_back(Entry{\n\
    \                query.left / block_size, query.right / block_size, query.time,\
    \ query.id});\n        }\n        std::sort(entries.begin(), entries.end(), [&](const\
    \ Entry& a, const Entry& b) {\n            if (a.left_block != b.left_block) return\
    \ a.left_block < b.left_block;\n            const bool reverse_right = (a.left_block\
    \ & 1) != 0;\n            if (time_span != 0) {\n                if (a.right_block\
    \ != b.right_block) {\n                    return reverse_right ? a.right_block\
    \ > b.right_block : a.right_block < b.right_block;\n                }\n      \
    \          if (a.time != b.time) {\n                    return ((a.left_block\
    \ ^ a.right_block) & 1) ? a.time > b.time : a.time < b.time;\n               \
    \ }\n            }\n            const int a_right = _queries[a.id].right;\n  \
    \          const int b_right = _queries[b.id].right;\n            if (a_right\
    \ != b_right) return reverse_right ? a_right > b_right : a_right < b_right;\n\
    \            return a.id < b.id;\n        });\n        std::vector<int> result;\n\
    \        result.reserve(q);\n        for (const Entry& entry : entries) result.push_back(entry.id);\n\
    \        return result;\n    }\n\n    // apply(id, left, right) moves time id\
    \ -> id + 1; undo(id, left, right)\n    // reverses that update. Both must update\
    \ the array even outside the active\n    // range, and must repair the maintained\
    \ answer when necessary inside it.\n    template <class AddLeft, class AddRight,\
    \ class RemoveLeft, class RemoveRight,\n              class Apply, class Undo,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right,\n             Apply apply, Undo undo,\
    \ Answer answer, int block_size = 0) const {\n        int left = 0;\n        int\
    \ right = 0;\n        int time = 0;\n        for (int query_index : order(block_size))\
    \ {\n            const Query& query = _queries[query_index];\n            while\
    \ (time < query.time) {\n                apply(time, left, right);\n         \
    \       ++time;\n            }\n            while (query.time < time) {\n    \
    \            --time;\n                undo(time, left, right);\n            }\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    template <class Add, class Remove, class Apply, class\
    \ Undo, class Answer>\n    void run(Add add, Remove remove, Apply apply, Undo\
    \ undo, Answer answer,\n             int block_size = 0) const {\n        run(add,\
    \ add, remove, remove, apply, undo, answer, block_size);\n    }\n};\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n#endif  // M1UNE_ALGO_OFFLINE_MO_WITH_UPDATES_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: algo/offline/mo_with_updates.hpp
  requiredBy:
  - algo/all.hpp
  - algo/offline/all.hpp
  timestamp: '2026-11-17 04:04:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/algo/offline/mo_with_updates.test.cpp
documentation_of: algo/offline/mo_with_updates.hpp
layout: document
title: Mo's Algorithm with Updates
---

## Overview

`m1une::algo::MoWithUpdates` answers offline range queries with point updates.
Use it when all operations are known beforehand and your answer can be adjusted
when an endpoint moves or an active element changes.

The workflow is:

1. Record queries and updates in their original order.
2. Provide callbacks that maintain your array and the current answer.
3. Call `run` once to compute all query answers.

The class reorders the work to reuse the current interval and array state.
It stores the schedule; your callbacks own the array, update values, and answers.
For an unchanged array, use
[Mo](https://m1une.github.io/m1une_library/algo/offline/mo.hpp).

## Complexity

Let `N` be the array length, `Q` the number of queries, and `U` the number of
point updates. Set `M = max(1, N, Q, U)`.

**With the automatic block size and constant-time callbacks, the total time is
$O(M^{5/3})$ for the entire batch.** This includes sorting and processing all
queries and updates; it is not a cost charged separately to each query.

For example, if `N`, `Q`, and `U` are all about `n`, use **$O(n^{5/3})$ total**
when estimating the work. If each callback costs $O(\log n)$, use
**$O(n^{5/3}\log n)$ total** instead. More generally, if every callback takes
at most $O(F)$ time, with `F >= 1`, the bound is $O(M^{5/3}F)$.

The scheduler needs $O(Q)$ memory. Keeping the working array, update records,
and answers usually makes the total memory **$O(N + Q + U)$**. Reserved query
capacity is retained until the scheduler is destroyed or replaced.

The extra work comes from moving through update history as well as moving the
range endpoints. The same recorded update can be applied and undone many times.
When the three input sizes are similar, blocks of about $n^{2/3}$ balance these
movements and give the $n^{5/3}$ total bound. Sorting is already included.

## Registering Queries and Updates

```cpp
m1une::algo::MoWithUpdates mo(n);
int first_query = mo.add_query(l, r);  // Time zero.
int update_id = mo.add_update();      // Register update zero; time becomes one.
int second_query = mo.add_query(l, r);
```

Time `t` means updates with IDs `[0, t)` have been applied. `add_update()`
returns the next update ID and advances the registered time by one, even for
an assignment that leaves a value unchanged. Save that update's position and
its before/after values under the returned ID. Registering it does not execute it.

`add_query(l, r)` captures the current registered time and returns an
insertion-order query ID. `add_query(l, r, time)` can instead query a historical
state; all updates up to that time must already have been registered.

The public query record is:

```cpp
struct Query {
    int left;
    int right;
    int time;
    int id;
};
```

Ranges are zero-based and half-open. `0 <= left <= right <= size()` and
`0 <= time <= update_count()` are asserted. Empty ranges and arrays are
supported. Point positions in the caller's update records must be valid array
indices. The number of registered updates and queries must each fit in `int`.

## Callbacks

For statistics such as sums, frequencies, or distinct counts:

```cpp
mo.run(add, remove, apply, undo, answer);
```

| Callback | What it does |
| --- | --- |
| `add(int index)` | Adds the current value at `index` to your answer state. |
| `remove(int index)` | Removes the current value at `index` from your answer state. |
| `apply(int id, int left, int right)` | Executes update `id` and adjusts the answer if its position is in `[left, right)`. |
| `undo(int id, int left, int right)` | Restores the value immediately before update `id` and adjusts the answer if its position is in `[left, right)`. |
| `answer(int id)` | Saves the current answer for query `id`. |

For `apply` and `undo`, always change the working array, including when the
position is outside the active range. For a position inside the range, a common
pattern is: remove its old contribution, replace its value, then add its new
contribution. The scheduler does not do those three steps for you.

Updates are applied in increasing ID order and undone in decreasing ID order.
The supplied bounds describe the current active interval. Time changes happen
before the endpoints move toward the next query. The example below shows the
complete callback implementation.

If adding or removing on the left differs from doing so on the right, use:

```cpp
mo.run(add_left, add_right, remove_left, remove_right, apply, undo, answer);
```

Each endpoint callback receives one array index. `apply` and `undo` keep the
same three arguments and must also handle changes in the interval's interior.

Before `run`, the working array must be at time zero and the answer state must
represent an empty interval. Afterward, external state is left at the last
processed query. Reset it before another run. Save answers by query ID because
processing order differs from input order. With no queries, no callback runs.
Callbacks must not modify the scheduler while it is running.

## Interface

`Add`, `Remove`, `AddLeft`, `AddRight`, `RemoveLeft`, `RemoveRight`, `Apply`,
`Undo`, and `Answer` below are deduced callable template parameters with the
contracts above.

| Method | Description | Complexity |
| --- | --- | --- |
| `MoWithUpdates()` | Creates a scheduler for an empty array. | $O(1)$ |
| `explicit MoWithUpdates(int n)` | Creates a scheduler for array length `n`; requires `n >= 0`. | $O(1)$ |
| `int size() const` | Returns the fixed array length. | $O(1)$ |
| `int query_count() const` | Returns the number of registered queries. | $O(1)$ |
| `int update_count() const` | Returns the number of registered updates, also the current registration time. | $O(1)$ |
| `bool empty() const` | Returns whether there are no queries, even if updates are registered. | $O(1)$ |
| `const std::vector<Query>& queries() const` | Returns query records in insertion order. | $O(1)$ |
| `void reserve(int query_capacity)` | Reserves query storage; requires nonnegative capacity. | $O(Q)$ if reallocation occurs; otherwise $O(1)$ |
| `void clear()` | Removes queries and resets update IDs/time to zero; retains array length and query capacity. No callback is invoked. | $O(Q)$ |
| `int add_update()` | Registers one update and returns its zero-based ID. | $O(1)$ |
| `int add_query(int left, int right)` | Registers a query at the current time and returns its ID. | Amortized $O(1)$ |
| `int add_query(int left, int right, int time)` | Registers a query at an already registered time and returns its ID. | Amortized $O(1)$ |
| `std::vector<int> order(int block_size = 0) const` | Returns query IDs in processing order. | $O(Q\log(Q + 1))$ time, $O(Q)$ space |
| `void run(Add add, Remove remove, Apply apply, Undo undo, Answer answer, int block_size = 0) const` | Processes queries with symmetric endpoint callbacks. | Automatic blocks: $O(M^{5/3}F)$ total; custom blocks: see Complexity |
| `void run(AddLeft add_left, AddRight add_right, RemoveLeft remove_left, RemoveRight remove_right, Apply apply, Undo undo, Answer answer, int block_size = 0) const` | Processes queries with directional endpoint callbacks. | Automatic blocks: $O(M^{5/3}F)$ total; custom blocks: see Complexity |

`order` and `run` leave the stored schedule unchanged. `clear` resets only the
scheduler; reset your own array, update records, and answer state when starting
a new batch. Query storage may retain explicitly reserved capacity.

## Example

This answers distinct-value queries before and after two assignments to the
same position. The working array stays at its initial state while operations
are registered.

```cpp
#include "algo/offline/mo_with_updates.hpp"
#include <cassert>
#include <vector>

struct Change {
    int position;
    int before;
    int after;
};

int main() {
    std::vector<int> values = {1, 2, 1, 3};
    m1une::algo::MoWithUpdates mo(int(values.size()));
    std::vector<Change> changes;

    mo.add_query(0, 4);                    // Time 0: three distinct values.
    changes.push_back(Change{1, 2, 1});
    mo.add_update();                       // Update 0: values[1] = 1.
    mo.add_query(0, 3);                    // Time 1: one distinct value.
    changes.push_back(Change{1, 1, 3});     // The previous value is now 1, not 2.
    mo.add_update();                       // Update 1: values[1] = 3.
    mo.add_query(1, 4);                    // Time 2: two distinct values.

    std::vector<int> frequency(4, 0), result(mo.query_count());
    int distinct = 0;
    auto add = [&](int index) {
        if (frequency[values[index]]++ == 0) ++distinct;
    };
    auto remove = [&](int index) {
        if (--frequency[values[index]] == 0) --distinct;
    };
    auto replace = [&](int id, int left, int right, int value) {
        const int position = changes[id].position;
        const bool inside = left <= position && position < right;
        if (inside) remove(position);
        values[position] = value;
        if (inside) add(position);
    };
    mo.run(add, remove,
        [&](int id, int left, int right) {
            replace(id, left, right, changes[id].after);
        },
        [&](int id, int left, int right) {
            replace(id, left, right, changes[id].before);
        },
        [&](int id) { result[id] = distinct; });

    const std::vector<int> expected = {3, 1, 2};
    assert(result == expected);
}
```

## Advanced: Custom Block Size

Normally, leave `block_size = 0`; the implementation chooses it automatically.
A positive value overrides that choice, so the bound then depends on your
chosen block size `B`:

$$
O\left(
Q\log(Q+1) + F\left[
QB + N\left(1+\frac{N}{B}\right)
+ U\left(1+\frac{N}{B}\right)^2
\right]
\right).
$$

The three terms inside the brackets account for endpoint movements within
blocks, endpoint sweeps between blocks, and applying/undoing updates. This
more detailed bound is useful for tuning; the automatic-block bound above is
the simpler estimate for ordinary use.

## Verification

The verification target solves Library Checker's
[Point Set Range Frequency](https://github.com/yosupo06/library-checker-problems/tree/master/data_structure/point_set_range_frequency).
Randomized tests compare against saved naive array states for several block
sizes, repeated runs, no-op and repeated-position updates, historical queries,
and empty ranges/arrays. Directional callbacks maintain an ordered string and
check its contents and active bounds after forward and backward time changes.
