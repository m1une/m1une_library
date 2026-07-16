---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
    title: verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/offline_rectangle_add_rectangle_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#line 6 \"ds/range_query/fenwick_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T> _data;\n\
    \n    static int max_power_leq(int n) {\n        int result = 1;\n        while\
    \ (result <= n / 2) result <<= 1;\n        return result;\n    }\n\n    T prefix_sum(int\
    \ r) const {\n        T result{};\n        const T* data = _data.data();\n   \
    \     while (r > 0) {\n            result += data[r];\n            r -= r & -r;\n\
    \        }\n        return result;\n    }\n\n   public:\n    FenwickTree() : _n(0),\
    \ _max_power(0) {}\n\n    explicit FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n\
    \ > 0 ? n : 1)), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>&\
    \ a)\n        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0\
    \ ? _n : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i\
    \ <= _n; ++i) {\n            _data[i] += a[i - 1];\n            const int p =\
    \ i + (i & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 10 \"ds/range_query/offline_rectangle_add_rectangle_sum.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Records rectangle additions and rectangle-sum\
    \ queries, then evaluates the\n// complete static batch with an offline sweep.\n\
    template <class T, class X = long long, class Y = X>\nclass OfflineRectangleAddRectangleSum\
    \ {\n   public:\n    using value_type = T;\n    using x_type = X;\n    using y_type\
    \ = Y;\n\n   private:\n    struct Update {\n        X x_lower;\n        X x_upper;\n\
    \        Y y_lower;\n        Y y_upper;\n        T value;\n    };\n\n    struct\
    \ Query {\n        X x_lower;\n        X x_upper;\n        Y y_lower;\n      \
    \  Y y_upper;\n    };\n\n    struct Coefficient {\n        T xy{};\n        T\
    \ x{};\n        T y{};\n        T constant{};\n\n        Coefficient& operator+=(const\
    \ Coefficient& other) {\n            xy += other.xy;\n            x += other.x;\n\
    \            y += other.y;\n            constant += other.constant;\n        \
    \    return *this;\n        }\n    };\n\n    struct PointEvent {\n        X x;\n\
    \        Y y;\n        Coefficient coefficient;\n    };\n\n    struct PrefixEvent\
    \ {\n        X x;\n        Y y;\n        int query_id;\n        bool subtract;\n\
    \    };\n\n    std::vector<Update> _updates;\n    std::vector<Query> _queries;\n\
    \n    template <class Coordinate>\n    static bool equivalent(const Coordinate&\
    \ first, const Coordinate& second) {\n        return !(first < second) && !(second\
    \ < first);\n    }\n\n    static Coefficient make_coefficient(\n        const\
    \ X& x,\n        const Y& y,\n        const T& signed_value\n    ) {\n       \
    \ const T converted_x(x);\n        const T converted_y(y);\n        return {\n\
    \            signed_value,\n            T{} - signed_value * converted_y,\n  \
    \          T{} - signed_value * converted_x,\n            signed_value * converted_x\
    \ * converted_y\n        };\n    }\n\n    static T evaluate(\n        const Coefficient&\
    \ coefficient,\n        const X& x,\n        const Y& y\n    ) {\n        const\
    \ T converted_x(x);\n        const T converted_y(y);\n        return coefficient.xy\
    \ * converted_x * converted_y +\n               coefficient.x * converted_x +\n\
    \               coefficient.y * converted_y +\n               coefficient.constant;\n\
    \    }\n\n   public:\n    int update_count() const {\n        return int(_updates.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    bool empty() const {\n        return _updates.empty() && _queries.empty();\n\
    \    }\n\n    void reserve_updates(int capacity) {\n        assert(0 <= capacity);\n\
    \        _updates.reserve(capacity);\n    }\n\n    void reserve_queries(int capacity)\
    \ {\n        assert(0 <= capacity);\n        _queries.reserve(capacity);\n   \
    \ }\n\n    void clear() {\n        _updates.clear();\n        _queries.clear();\n\
    \    }\n\n    int add_rectangle(\n        const X& x_lower,\n        const X&\
    \ x_upper,\n        const Y& y_lower,\n        const Y& y_upper,\n        const\
    \ T& value\n    ) {\n        assert(!(x_upper < x_lower));\n        assert(!(y_upper\
    \ < y_lower));\n        const int id = update_count();\n        _updates.push_back(Update{x_lower,\
    \ x_upper, y_lower, y_upper, value});\n        return id;\n    }\n\n    int add_query(\n\
    \        const X& x_lower,\n        const X& x_upper,\n        const Y& y_lower,\n\
    \        const Y& y_upper\n    ) {\n        assert(!(x_upper < x_lower));\n  \
    \      assert(!(y_upper < y_lower));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{x_lower, x_upper, y_lower, y_upper});\n    \
    \    return id;\n    }\n\n    std::vector<T> calculate() const {\n        std::vector<T>\
    \ answers(_queries.size(), T{});\n        if (_queries.empty() || _updates.empty())\
    \ return answers;\n\n        std::vector<PointEvent> point_events;\n        point_events.reserve(4\
    \ * _updates.size());\n        std::vector<Y> y_coordinates;\n        y_coordinates.reserve(2\
    \ * _updates.size());\n        for (const Update& update : _updates) {\n     \
    \       if (equivalent(update.x_lower, update.x_upper) ||\n                equivalent(update.y_lower,\
    \ update.y_upper)) {\n                continue;\n            }\n            const\
    \ T negative_value = T{} - update.value;\n            point_events.push_back(PointEvent{\n\
    \                update.x_lower,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_lower, update.y_lower, update.value)\n      \
    \      });\n            point_events.push_back(PointEvent{\n                update.x_lower,\n\
    \                update.y_upper,\n                make_coefficient(update.x_lower,\
    \ update.y_upper, negative_value)\n            });\n            point_events.push_back(PointEvent{\n\
    \                update.x_upper,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_upper, update.y_lower, negative_value)\n    \
    \        });\n            point_events.push_back(PointEvent{\n               \
    \ update.x_upper,\n                update.y_upper,\n                make_coefficient(update.x_upper,\
    \ update.y_upper, update.value)\n            });\n            y_coordinates.push_back(update.y_lower);\n\
    \            y_coordinates.push_back(update.y_upper);\n        }\n        if (point_events.empty())\
    \ return answers;\n\n        std::sort(y_coordinates.begin(), y_coordinates.end());\n\
    \        y_coordinates.erase(\n            std::unique(\n                y_coordinates.begin(),\n\
    \                y_coordinates.end(),\n                [](const Y& first, const\
    \ Y& second) {\n                    return equivalent(first, second);\n      \
    \          }\n            ),\n            y_coordinates.end()\n        );\n  \
    \      std::sort(\n            point_events.begin(),\n            point_events.end(),\n\
    \            [](const PointEvent& first, const PointEvent& second) {\n       \
    \         return first.x < second.x;\n            }\n        );\n\n        std::vector<PrefixEvent>\
    \ prefix_events;\n        prefix_events.reserve(4 * _queries.size());\n      \
    \  for (int query_id = 0; query_id < query_count(); query_id++) {\n          \
    \  const Query& query = _queries[query_id];\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_upper, query_id, false\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_upper, query_id, true\n            });\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_lower, query_id, true\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_lower, query_id, false\n            });\n        }\n        std::sort(\n\
    \            prefix_events.begin(),\n            prefix_events.end(),\n      \
    \      [](const PrefixEvent& first, const PrefixEvent& second) {\n           \
    \     return first.x < second.x;\n            }\n        );\n\n        FenwickTree<Coefficient>\
    \ fenwick(int(y_coordinates.size()));\n        int point_index = 0;\n        for\
    \ (const PrefixEvent& event : prefix_events) {\n            while (\n        \
    \        point_index < int(point_events.size()) &&\n                point_events[point_index].x\
    \ < event.x\n            ) {\n                const PointEvent& point = point_events[point_index];\n\
    \                const int y_index = int(\n                    std::lower_bound(\n\
    \                        y_coordinates.begin(), y_coordinates.end(), point.y\n\
    \                    ) - y_coordinates.begin()\n                );\n         \
    \       fenwick.add(y_index, point.coefficient);\n                point_index++;\n\
    \            }\n            const int y_count = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(), y_coordinates.end(), event.y\n   \
    \             ) - y_coordinates.begin()\n            );\n            const T value\
    \ = evaluate(fenwick.sum(y_count), event.x, event.y);\n            if (event.subtract)\
    \ {\n                answers[event.query_id] -= value;\n            } else {\n\
    \                answers[event.query_id] += value;\n            }\n        }\n\
    \        return answers;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP\n#define M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\n#include \"fenwick_tree.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\n// Records rectangle additions and rectangle-sum queries, then evaluates\
    \ the\n// complete static batch with an offline sweep.\ntemplate <class T, class\
    \ X = long long, class Y = X>\nclass OfflineRectangleAddRectangleSum {\n   public:\n\
    \    using value_type = T;\n    using x_type = X;\n    using y_type = Y;\n\n \
    \  private:\n    struct Update {\n        X x_lower;\n        X x_upper;\n   \
    \     Y y_lower;\n        Y y_upper;\n        T value;\n    };\n\n    struct Query\
    \ {\n        X x_lower;\n        X x_upper;\n        Y y_lower;\n        Y y_upper;\n\
    \    };\n\n    struct Coefficient {\n        T xy{};\n        T x{};\n       \
    \ T y{};\n        T constant{};\n\n        Coefficient& operator+=(const Coefficient&\
    \ other) {\n            xy += other.xy;\n            x += other.x;\n         \
    \   y += other.y;\n            constant += other.constant;\n            return\
    \ *this;\n        }\n    };\n\n    struct PointEvent {\n        X x;\n       \
    \ Y y;\n        Coefficient coefficient;\n    };\n\n    struct PrefixEvent {\n\
    \        X x;\n        Y y;\n        int query_id;\n        bool subtract;\n \
    \   };\n\n    std::vector<Update> _updates;\n    std::vector<Query> _queries;\n\
    \n    template <class Coordinate>\n    static bool equivalent(const Coordinate&\
    \ first, const Coordinate& second) {\n        return !(first < second) && !(second\
    \ < first);\n    }\n\n    static Coefficient make_coefficient(\n        const\
    \ X& x,\n        const Y& y,\n        const T& signed_value\n    ) {\n       \
    \ const T converted_x(x);\n        const T converted_y(y);\n        return {\n\
    \            signed_value,\n            T{} - signed_value * converted_y,\n  \
    \          T{} - signed_value * converted_x,\n            signed_value * converted_x\
    \ * converted_y\n        };\n    }\n\n    static T evaluate(\n        const Coefficient&\
    \ coefficient,\n        const X& x,\n        const Y& y\n    ) {\n        const\
    \ T converted_x(x);\n        const T converted_y(y);\n        return coefficient.xy\
    \ * converted_x * converted_y +\n               coefficient.x * converted_x +\n\
    \               coefficient.y * converted_y +\n               coefficient.constant;\n\
    \    }\n\n   public:\n    int update_count() const {\n        return int(_updates.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    bool empty() const {\n        return _updates.empty() && _queries.empty();\n\
    \    }\n\n    void reserve_updates(int capacity) {\n        assert(0 <= capacity);\n\
    \        _updates.reserve(capacity);\n    }\n\n    void reserve_queries(int capacity)\
    \ {\n        assert(0 <= capacity);\n        _queries.reserve(capacity);\n   \
    \ }\n\n    void clear() {\n        _updates.clear();\n        _queries.clear();\n\
    \    }\n\n    int add_rectangle(\n        const X& x_lower,\n        const X&\
    \ x_upper,\n        const Y& y_lower,\n        const Y& y_upper,\n        const\
    \ T& value\n    ) {\n        assert(!(x_upper < x_lower));\n        assert(!(y_upper\
    \ < y_lower));\n        const int id = update_count();\n        _updates.push_back(Update{x_lower,\
    \ x_upper, y_lower, y_upper, value});\n        return id;\n    }\n\n    int add_query(\n\
    \        const X& x_lower,\n        const X& x_upper,\n        const Y& y_lower,\n\
    \        const Y& y_upper\n    ) {\n        assert(!(x_upper < x_lower));\n  \
    \      assert(!(y_upper < y_lower));\n        const int id = query_count();\n\
    \        _queries.push_back(Query{x_lower, x_upper, y_lower, y_upper});\n    \
    \    return id;\n    }\n\n    std::vector<T> calculate() const {\n        std::vector<T>\
    \ answers(_queries.size(), T{});\n        if (_queries.empty() || _updates.empty())\
    \ return answers;\n\n        std::vector<PointEvent> point_events;\n        point_events.reserve(4\
    \ * _updates.size());\n        std::vector<Y> y_coordinates;\n        y_coordinates.reserve(2\
    \ * _updates.size());\n        for (const Update& update : _updates) {\n     \
    \       if (equivalent(update.x_lower, update.x_upper) ||\n                equivalent(update.y_lower,\
    \ update.y_upper)) {\n                continue;\n            }\n            const\
    \ T negative_value = T{} - update.value;\n            point_events.push_back(PointEvent{\n\
    \                update.x_lower,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_lower, update.y_lower, update.value)\n      \
    \      });\n            point_events.push_back(PointEvent{\n                update.x_lower,\n\
    \                update.y_upper,\n                make_coefficient(update.x_lower,\
    \ update.y_upper, negative_value)\n            });\n            point_events.push_back(PointEvent{\n\
    \                update.x_upper,\n                update.y_lower,\n          \
    \      make_coefficient(update.x_upper, update.y_lower, negative_value)\n    \
    \        });\n            point_events.push_back(PointEvent{\n               \
    \ update.x_upper,\n                update.y_upper,\n                make_coefficient(update.x_upper,\
    \ update.y_upper, update.value)\n            });\n            y_coordinates.push_back(update.y_lower);\n\
    \            y_coordinates.push_back(update.y_upper);\n        }\n        if (point_events.empty())\
    \ return answers;\n\n        std::sort(y_coordinates.begin(), y_coordinates.end());\n\
    \        y_coordinates.erase(\n            std::unique(\n                y_coordinates.begin(),\n\
    \                y_coordinates.end(),\n                [](const Y& first, const\
    \ Y& second) {\n                    return equivalent(first, second);\n      \
    \          }\n            ),\n            y_coordinates.end()\n        );\n  \
    \      std::sort(\n            point_events.begin(),\n            point_events.end(),\n\
    \            [](const PointEvent& first, const PointEvent& second) {\n       \
    \         return first.x < second.x;\n            }\n        );\n\n        std::vector<PrefixEvent>\
    \ prefix_events;\n        prefix_events.reserve(4 * _queries.size());\n      \
    \  for (int query_id = 0; query_id < query_count(); query_id++) {\n          \
    \  const Query& query = _queries[query_id];\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_upper, query_id, false\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_upper, query_id, true\n            });\n            prefix_events.push_back(PrefixEvent{\n\
    \                query.x_upper, query.y_lower, query_id, true\n            });\n\
    \            prefix_events.push_back(PrefixEvent{\n                query.x_lower,\
    \ query.y_lower, query_id, false\n            });\n        }\n        std::sort(\n\
    \            prefix_events.begin(),\n            prefix_events.end(),\n      \
    \      [](const PrefixEvent& first, const PrefixEvent& second) {\n           \
    \     return first.x < second.x;\n            }\n        );\n\n        FenwickTree<Coefficient>\
    \ fenwick(int(y_coordinates.size()));\n        int point_index = 0;\n        for\
    \ (const PrefixEvent& event : prefix_events) {\n            while (\n        \
    \        point_index < int(point_events.size()) &&\n                point_events[point_index].x\
    \ < event.x\n            ) {\n                const PointEvent& point = point_events[point_index];\n\
    \                const int y_index = int(\n                    std::lower_bound(\n\
    \                        y_coordinates.begin(), y_coordinates.end(), point.y\n\
    \                    ) - y_coordinates.begin()\n                );\n         \
    \       fenwick.add(y_index, point.coefficient);\n                point_index++;\n\
    \            }\n            const int y_count = int(\n                std::lower_bound(\n\
    \                    y_coordinates.begin(), y_coordinates.end(), event.y\n   \
    \             ) - y_coordinates.begin()\n            );\n            const T value\
    \ = evaluate(fenwick.sum(y_count), event.x, event.y);\n            if (event.subtract)\
    \ {\n                answers[event.query_id] -= value;\n            } else {\n\
    \                answers[event.query_id] += value;\n            }\n        }\n\
    \        return answers;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n#endif  // M1UNE_OFFLINE_RECTANGLE_ADD_RECTANGLE_SUM_HPP\n"
  dependsOn:
  - ds/range_query/fenwick_tree.hpp
  isVerificationFile: false
  path: ds/range_query/offline_rectangle_add_rectangle_sum.hpp
  requiredBy: []
  timestamp: '2026-07-16 21:06:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/offline_rectangle_add_rectangle_sum.test.cpp
documentation_of: ds/range_query/offline_rectangle_add_rectangle_sum.hpp
layout: document
title: Offline Rectangle Add Rectangle Sum
---

## Overview

`m1une::ds::OfflineRectangleAddRectangleSum<T, X, Y>` records additions to
axis-aligned rectangles and rectangle-sum queries, then evaluates the complete
batch with an offline sweep.

Every rectangle is half-open:

$$
[x_l,x_r)\times[y_l,y_r).
$$

An update adds `value` to every unit cell in its rectangle. A query returns the
sum of all cells in its rectangle. Equivalently, the structure computes the
area-weighted integral of the piecewise-constant rectangle additions. Integer
coordinates therefore match the usual grid interpretation exactly.

All recorded updates affect every recorded query. Insertion order is not a time
axis. Query IDs and returned answers use query insertion order, and repeated
calls to `calculate()` do not mutate the batch.

## Requirements

```cpp
template <class T, class X = long long, class Y = X>
class OfflineRectangleAddRectangleSum;
```

* `X` and `Y` must be strictly ordered by `<`.
* `T{}` must be zero. `T` must support copying, `+=`, `-=`, addition,
  subtraction, and multiplication.
* Coordinates must be explicitly constructible as `T`. Coordinate products are
  performed after conversion to `T`, which is useful for modular arithmetic.
* Exact arithmetic results must fit in `T`, unless `T` intentionally implements
  modular arithmetic.

## Interface

```cpp
using value_type = T;
using x_type = X;
using y_type = Y;

int update_count() const;
int query_count() const;
bool empty() const;

void reserve_updates(int capacity);
void reserve_queries(int capacity);
void clear();

int add_rectangle(
    const X& x_lower,
    const X& x_upper,
    const Y& y_lower,
    const Y& y_upper,
    const T& value
);

int add_query(
    const X& x_lower,
    const X& x_upper,
    const Y& y_lower,
    const Y& y_upper
);

std::vector<T> calculate() const;
```

## Operations

| Method | Description | Complexity |
| --- | --- | --- |
| Default construction | Creates an empty batch. | $O(1)$ |
| `update_count()` | Returns the number of recorded rectangle additions. | $O(1)$ |
| `query_count()` | Returns the number of recorded sum queries. | $O(1)$ |
| `empty()` | Returns whether both logs are empty. | $O(1)$ |
| `reserve_updates(capacity)` | Reserves update storage. | $O(N)$ worst case |
| `reserve_queries(capacity)` | Reserves query storage. | $O(Q)$ worst case |
| `clear()` | Removes every update and query while preserving allocated capacity. | $O(N+Q)$ |
| `add_rectangle(xl, xr, yl, yr, value)` | Records an addition and returns its insertion-order update ID. Empty rectangles are allowed. | Amortized $O(1)$ |
| `add_query(xl, xr, yl, yr)` | Records a sum query and returns its insertion-order query ID. Empty rectangles are allowed. | Amortized $O(1)$ |
| `calculate()` | Returns all answers in query insertion order without mutating the object. | $O((N+Q)\log(N+Q))$ time and $O(N+Q)$ memory |

Here $N$ is the number of updates and $Q$ is the number of queries. Invalid
rectangles with a lower boundary greater than the corresponding upper boundary
trigger an assertion.

The implementation converts every rectangle addition into four weighted corner
events. A sweep over x and a Fenwick tree over compressed y-coordinates evaluate
the two-dimensional prefix sums used by inclusion-exclusion.

## Example

```cpp
#include "ds/range_query/offline_rectangle_add_rectangle_sum.hpp"

#include <cassert>

int main() {
    m1une::ds::OfflineRectangleAddRectangleSum<long long> offline;

    offline.add_rectangle(0, 3, 0, 2, 5);
    int query_id = offline.add_query(1, 4, 1, 3);

    const auto answers = offline.calculate();
    assert(answers[query_id] == 10);
}
```
