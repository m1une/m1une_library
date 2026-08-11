---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"beats_acted_monoid/range_bitwise_and_or_range_sum.hpp\"\n\
    \n\n\n#include <cassert>\n#include <limits>\n#include <type_traits>\n\nnamespace\
    \ m1une {\nnamespace beats_acted_monoid {\n\ntemplate <typename T>\nstruct RangeBitwiseAndOrRangeSumNode\
    \ {\n    T sum;\n    T bitwise_and;\n    T bitwise_or;\n    long long length;\n\
    };\n\n// Beats acted monoid for range bitwise AND/OR updates and range sum queries.\n\
    template <typename T, int BITS = 30>\nstruct RangeBitwiseAndOrRangeSum {\n   \
    \ static_assert(\n        std::is_integral_v<T> &&\n        !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n    );\n    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);\n\
    \n    using value_type = RangeBitwiseAndOrRangeSumNode<T>;\n\n    // Represents\
    \ f(x) = (x & and_mask) | or_mask.\n    struct operator_type {\n        T and_mask;\n\
    \        T or_mask;\n    };\n\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = false;\n\n    static constexpr\
    \ T bit_mask() {\n        if constexpr (\n            std::is_unsigned_v<T> &&\n\
    \            BITS == std::numeric_limits<T>::digits\n        ) {\n           \
    \ return ~T(0);\n        } else {\n            return\n                (T(1) <<\
    \ (BITS - 1)) |\n                ((T(1) << (BITS - 1)) - 1);\n        }\n    }\n\
    \n    static constexpr value_type id() {\n        return {T(0), bit_mask(), T(0),\
    \ 0};\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        return {\n        \
    \    left.sum + right.sum,\n            left.bitwise_and & right.bitwise_and,\n\
    \            left.bitwise_or | right.bitwise_or,\n            left.length + right.length\n\
    \        };\n    }\n\n    static constexpr operator_type op_id() {\n        return\
    \ {bit_mask(), T(0)};\n    }\n\n    // Returns f(g(x)).\n    static constexpr\
    \ operator_type op_comp(\n        const operator_type& f,\n        const operator_type&\
    \ g\n    ) {\n        return {\n            (f.and_mask & g.and_mask) & bit_mask(),\n\
    \            ((g.or_mask & f.and_mask) | f.or_mask) & bit_mask()\n        };\n\
    \    }\n\n    static constexpr bool can_apply(\n        const operator_type& f,\n\
    \        const value_type& value\n    ) {\n        if (value.length == 0) return\
    \ true;\n        T changed = ((~f.and_mask) | f.or_mask) & bit_mask();\n     \
    \   T mixed = value.bitwise_and ^ value.bitwise_or;\n        return (changed &\
    \ mixed) == T(0);\n    }\n\n    static constexpr value_type mapping(\n       \
    \ const operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        T changed =\
    \ ((~f.and_mask) | f.or_mask) & bit_mask();\n        T old_uniform = value.bitwise_and\
    \ & changed;\n        T new_uniform =\n            ((old_uniform & f.and_mask)\
    \ | f.or_mask) & changed;\n\n        value_type result = value;\n        result.sum\
    \ +=\n            (new_uniform - old_uniform) * T(value.length);\n        result.bitwise_and\
    \ =\n            ((value.bitwise_and & f.and_mask) | f.or_mask) & bit_mask();\n\
    \        result.bitwise_or =\n            ((value.bitwise_or & f.and_mask) | f.or_mask)\
    \ & bit_mask();\n        return result;\n    }\n\n    static constexpr value_type\
    \ make(const T& value) {\n        assert((value & ~bit_mask()) == T(0));\n   \
    \     return {value, value, value, 1};\n    }\n\n    static constexpr operator_type\
    \ make_and(const T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\
    \n    static constexpr operator_type make_or(const T& mask) {\n        return\
    \ {bit_mask(), mask & bit_mask()};\n    }\n};\n\n}  // namespace beats_acted_monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP\n#define\
    \ M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP 1\n\n#include <cassert>\n\
    #include <limits>\n#include <type_traits>\n\nnamespace m1une {\nnamespace beats_acted_monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeBitwiseAndOrRangeSumNode {\n    T sum;\n\
    \    T bitwise_and;\n    T bitwise_or;\n    long long length;\n};\n\n// Beats\
    \ acted monoid for range bitwise AND/OR updates and range sum queries.\ntemplate\
    \ <typename T, int BITS = 30>\nstruct RangeBitwiseAndOrRangeSum {\n    static_assert(\n\
    \        std::is_integral_v<T> &&\n        !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n    );\n    static_assert(0 < BITS && BITS <= std::numeric_limits<T>::digits);\n\
    \n    using value_type = RangeBitwiseAndOrRangeSumNode<T>;\n\n    // Represents\
    \ f(x) = (x & and_mask) | or_mask.\n    struct operator_type {\n        T and_mask;\n\
    \        T or_mask;\n    };\n\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = false;\n\n    static constexpr\
    \ T bit_mask() {\n        if constexpr (\n            std::is_unsigned_v<T> &&\n\
    \            BITS == std::numeric_limits<T>::digits\n        ) {\n           \
    \ return ~T(0);\n        } else {\n            return\n                (T(1) <<\
    \ (BITS - 1)) |\n                ((T(1) << (BITS - 1)) - 1);\n        }\n    }\n\
    \n    static constexpr value_type id() {\n        return {T(0), bit_mask(), T(0),\
    \ 0};\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        return {\n        \
    \    left.sum + right.sum,\n            left.bitwise_and & right.bitwise_and,\n\
    \            left.bitwise_or | right.bitwise_or,\n            left.length + right.length\n\
    \        };\n    }\n\n    static constexpr operator_type op_id() {\n        return\
    \ {bit_mask(), T(0)};\n    }\n\n    // Returns f(g(x)).\n    static constexpr\
    \ operator_type op_comp(\n        const operator_type& f,\n        const operator_type&\
    \ g\n    ) {\n        return {\n            (f.and_mask & g.and_mask) & bit_mask(),\n\
    \            ((g.or_mask & f.and_mask) | f.or_mask) & bit_mask()\n        };\n\
    \    }\n\n    static constexpr bool can_apply(\n        const operator_type& f,\n\
    \        const value_type& value\n    ) {\n        if (value.length == 0) return\
    \ true;\n        T changed = ((~f.and_mask) | f.or_mask) & bit_mask();\n     \
    \   T mixed = value.bitwise_and ^ value.bitwise_or;\n        return (changed &\
    \ mixed) == T(0);\n    }\n\n    static constexpr value_type mapping(\n       \
    \ const operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        T changed =\
    \ ((~f.and_mask) | f.or_mask) & bit_mask();\n        T old_uniform = value.bitwise_and\
    \ & changed;\n        T new_uniform =\n            ((old_uniform & f.and_mask)\
    \ | f.or_mask) & changed;\n\n        value_type result = value;\n        result.sum\
    \ +=\n            (new_uniform - old_uniform) * T(value.length);\n        result.bitwise_and\
    \ =\n            ((value.bitwise_and & f.and_mask) | f.or_mask) & bit_mask();\n\
    \        result.bitwise_or =\n            ((value.bitwise_or & f.and_mask) | f.or_mask)\
    \ & bit_mask();\n        return result;\n    }\n\n    static constexpr value_type\
    \ make(const T& value) {\n        assert((value & ~bit_mask()) == T(0));\n   \
    \     return {value, value, value, 1};\n    }\n\n    static constexpr operator_type\
    \ make_and(const T& mask) {\n        return {mask & bit_mask(), T(0)};\n    }\n\
    \n    static constexpr operator_type make_or(const T& mask) {\n        return\
    \ {bit_mask(), mask & bit_mask()};\n    }\n};\n\n}  // namespace beats_acted_monoid\n\
    }  // namespace m1une\n\n#endif  // M1UNE_BEATS_ACTED_MONOID_RANGE_BITWISE_AND_OR_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: beats_acted_monoid/range_bitwise_and_or_range_sum.hpp
  requiredBy: []
  timestamp: '2026-08-12 01:20:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
documentation_of: beats_acted_monoid/range_bitwise_and_or_range_sum.hpp
layout: document
title: Range Bitwise AND/OR Range Sum
---

## Overview

`m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<T, BITS>` is a Beats
acted monoid for range bitwise AND and OR updates with range-sum queries.

Unlike the ordinary acted monoid that stores a count for every bit, this Beats
version stores only the sum, aggregate bitwise AND, aggregate bitwise OR, and
segment length. An update applies directly when every bit it changes is uniform
throughout the node. If a changed bit is mixed, `can_apply` returns `false` and
the Beats tree descends.

The lazy `operator_type` represents

```cpp
f(x) = (x & and_mask) | or_mask;
```

Use `make_and` and `make_or` instead of constructing an operator directly.

## Template requirements

* `T` must be a non-boolean integral type. Values are nonnegative, occupy only
  the lowest `BITS` bits, and have range sums representable by `T`.
* `BITS` defaults to `30` and must be between `1` and
  `std::numeric_limits<T>::digits`, inclusive.

`value_type` is `RangeBitwiseAndOrRangeSumNode<T>` and has these public members:

```cpp
T sum;
T bitwise_and;
T bitwise_or;
long long length;
```

`operator_type` has public members `T and_mask` and `T or_mask`.

## Interface and complexity

Every acted-monoid operation takes $O(1)$ time, independently of `BITS`.

| Member | Description | Complexity |
| --- | --- | --- |
| `static T bit_mask()` | Returns a mask with its lowest `BITS` bits set. | $O(1)$ |
| `static value_type id()` | Returns the empty aggregate. | $O(1)$ |
| `static value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(1)$ |
| `static operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns $f \circ g$. | $O(1)$ |
| `static bool can_apply(const operator_type& f, const value_type& x)` | Reports whether every changed bit is uniform in `x`. | $O(1)$ |
| `static value_type mapping(const operator_type& f, const value_type& x)` | Applies an update after `can_apply` succeeds. | $O(1)$ |
| `static value_type make(const T& value)` | Constructs a one-element aggregate. | $O(1)$ |
| `static operator_type make_and(const T& mask)` | Constructs `x = x & mask`. | $O(1)$ |
| `static operator_type make_or(const T& mask)` | Constructs `x = x | mask`. | $O(1)$ |

With `SegtreeBeats`, an operation takes $O(\log N+D)$, where $D$ is the number
of extra nodes visited because a changed bit is mixed. Read a query result from
the returned node's `sum` member.

## Example

```cpp
#include "beats_acted_monoid/range_bitwise_and_or_range_sum.hpp"
#include "ds/segtree/segtree_beats.hpp"

#include <iostream>
#include <vector>

using AM =
    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long long, 30>;

int main() {
    std::vector<long long> values = {1, 2, 3, 4};
    m1une::ds::SegtreeBeats<AM> seg(values);

    seg.apply(0, 3, AM::make_or(4));
    seg.apply(1, 4, AM::make_and(6));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
