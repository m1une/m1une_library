---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <limits>\n\nnamespace m1une {\nnamespace beats_acted_monoid {\n\ntemplate <std::signed_integral\
    \ T>\nstruct RangeChminChmaxAddRangeSumNode {\n    T sum;\n    T maximum;\n  \
    \  T second_maximum;\n    T minimum;\n    T second_minimum;\n    int maximum_count;\n\
    \    int minimum_count;\n    int length;\n};\n\n// Beats acted monoid for range\
    \ chmin/chmax/add updates and range sum queries.\ntemplate <std::signed_integral\
    \ T = long long>\nstruct RangeChminChmaxAddRangeSum {\n    using value_type =\
    \ RangeChminChmaxAddRangeSumNode<T>;\n\n    // Represents f(x) = clamp(x + add,\
    \ lower, upper).\n    struct operator_type {\n        T add;\n        T lower;\n\
    \        T upper;\n    };\n\n    static constexpr bool commutative = true;\n \
    \   static constexpr bool operator_commutative = false;\n    static constexpr\
    \ T negative_infinity = std::numeric_limits<T>::lowest();\n    static constexpr\
    \ T positive_infinity = std::numeric_limits<T>::max();\n\n   private:\n    static\
    \ constexpr T shift_lower_bound(T bound, T add) {\n        return bound == negative_infinity\
    \ ? bound : bound + add;\n    }\n\n    static constexpr T shift_upper_bound(T\
    \ bound, T add) {\n        return bound == positive_infinity ? bound : bound +\
    \ add;\n    }\n\n    static constexpr void apply_add(value_type& value, T add)\
    \ {\n        if (value.length == 0 || add == T(0)) return;\n        value.sum\
    \ += add * T(value.length);\n        value.maximum += add;\n        value.minimum\
    \ += add;\n        if (value.maximum_count != value.length) {\n            value.second_maximum\
    \ += add;\n        }\n        if (value.minimum_count != value.length) {\n   \
    \         value.second_minimum += add;\n        }\n    }\n\n    static constexpr\
    \ bool can_apply_chmin(\n        const value_type& value,\n        T upper\n \
    \   ) {\n        return value.maximum <= upper ||\n            value.maximum_count\
    \ == value.length ||\n            value.second_maximum < upper;\n    }\n\n   \
    \ static constexpr void apply_chmin(value_type& value, T upper) {\n        if\
    \ (value.maximum <= upper) return;\n        assert(can_apply_chmin(value, upper));\n\
    \        value.sum +=\n            (upper - value.maximum) * T(value.maximum_count);\n\
    \        if (value.minimum == value.maximum) {\n            value.minimum = upper;\n\
    \        } else if (value.second_minimum == value.maximum) {\n            value.second_minimum\
    \ = upper;\n        }\n        value.maximum = upper;\n    }\n\n    static constexpr\
    \ bool can_apply_chmax(\n        const value_type& value,\n        T lower\n \
    \   ) {\n        return lower <= value.minimum ||\n            value.minimum_count\
    \ == value.length ||\n            lower < value.second_minimum;\n    }\n\n   \
    \ static constexpr void apply_chmax(value_type& value, T lower) {\n        if\
    \ (lower <= value.minimum) return;\n        assert(can_apply_chmax(value, lower));\n\
    \        value.sum +=\n            (lower - value.minimum) * T(value.minimum_count);\n\
    \        if (value.maximum == value.minimum) {\n            value.maximum = lower;\n\
    \        } else if (value.second_maximum == value.minimum) {\n            value.second_maximum\
    \ = lower;\n        }\n        value.minimum = lower;\n    }\n\n    static constexpr\
    \ value_type constant_value(T value, int length) {\n        return {\n       \
    \     value * T(length),\n            value,\n            negative_infinity,\n\
    \            value,\n            positive_infinity,\n            length,\n   \
    \         length,\n            length\n        };\n    }\n\n   public:\n    static\
    \ constexpr value_type id() {\n        return {\n            T(0),\n         \
    \   negative_infinity,\n            negative_infinity,\n            positive_infinity,\n\
    \            positive_infinity,\n            0,\n            0,\n            0\n\
    \        };\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        if (left.length ==\
    \ 0) return right;\n        if (right.length == 0) return left;\n\n        value_type\
    \ result;\n        result.sum = left.sum + right.sum;\n        result.length =\
    \ left.length + right.length;\n\n        result.maximum = std::max(left.maximum,\
    \ right.maximum);\n        result.maximum_count = 0;\n        result.second_maximum\
    \ = negative_infinity;\n        if (left.maximum == result.maximum) {\n      \
    \      result.maximum_count += left.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                left.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                left.maximum\n      \
    \      );\n        }\n        if (right.maximum == result.maximum) {\n       \
    \     result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                right.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                right.maximum\n     \
    \       );\n        }\n\n        result.minimum = std::min(left.minimum, right.minimum);\n\
    \        result.minimum_count = 0;\n        result.second_minimum = positive_infinity;\n\
    \        if (left.minimum == result.minimum) {\n            result.minimum_count\
    \ += left.minimum_count;\n            result.second_minimum = std::min(\n    \
    \            result.second_minimum,\n                left.second_minimum\n   \
    \         );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                left.minimum\n      \
    \      );\n        }\n        if (right.minimum == result.minimum) {\n       \
    \     result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ = std::min(\n                result.second_minimum,\n                right.second_minimum\n\
    \            );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                right.minimum\n     \
    \       );\n        }\n        return result;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), negative_infinity, positive_infinity};\n  \
    \  }\n\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(\n\
    \        const operator_type& f,\n        const operator_type& g\n    ) {\n  \
    \      T lower = shift_lower_bound(g.lower, f.add);\n        T upper = shift_upper_bound(g.upper,\
    \ f.add);\n        return {\n            g.add + f.add,\n            std::clamp(lower,\
    \ f.lower, f.upper),\n            std::clamp(upper, f.lower, f.upper)\n      \
    \  };\n    }\n\n    static constexpr bool can_apply(\n        const operator_type&\
    \ f,\n        const value_type& value\n    ) {\n        if (value.length == 0\
    \ || f.lower == f.upper) return true;\n        value_type mapped = value;\n  \
    \      apply_add(mapped, f.add);\n        if (\n            mapped.maximum <=\
    \ f.lower ||\n            f.upper <= mapped.minimum\n        ) {\n           \
    \ return true;\n        }\n        if (!can_apply_chmax(mapped, f.lower)) return\
    \ false;\n        apply_chmax(mapped, f.lower);\n        return can_apply_chmin(mapped,\
    \ f.upper);\n    }\n\n    static constexpr value_type mapping(\n        const\
    \ operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        if (f.lower\
    \ == f.upper) {\n            return constant_value(f.lower, value.length);\n \
    \       }\n        value_type result = value;\n        apply_add(result, f.add);\n\
    \        if (result.maximum <= f.lower) {\n            return constant_value(f.lower,\
    \ result.length);\n        }\n        if (f.upper <= result.minimum) {\n     \
    \       return constant_value(f.upper, result.length);\n        }\n        apply_chmax(result,\
    \ f.lower);\n        apply_chmin(result, f.upper);\n        return result;\n \
    \   }\n\n    static constexpr value_type make(const T& value) {\n        return\
    \ constant_value(value, 1);\n    }\n\n    static constexpr operator_type make_chmin(const\
    \ T& upper) {\n        return {T(0), negative_infinity, upper};\n    }\n\n   \
    \ static constexpr operator_type make_chmax(const T& lower) {\n        return\
    \ {T(0), lower, positive_infinity};\n    }\n\n    static constexpr operator_type\
    \ make_add(const T& add) {\n        return {add, negative_infinity, positive_infinity};\n\
    \    }\n};\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP\n#define\
    \ M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP 1\n\n#include <algorithm>\n\
    #include <cassert>\n#include <concepts>\n#include <limits>\n\nnamespace m1une\
    \ {\nnamespace beats_acted_monoid {\n\ntemplate <std::signed_integral T>\nstruct\
    \ RangeChminChmaxAddRangeSumNode {\n    T sum;\n    T maximum;\n    T second_maximum;\n\
    \    T minimum;\n    T second_minimum;\n    int maximum_count;\n    int minimum_count;\n\
    \    int length;\n};\n\n// Beats acted monoid for range chmin/chmax/add updates\
    \ and range sum queries.\ntemplate <std::signed_integral T = long long>\nstruct\
    \ RangeChminChmaxAddRangeSum {\n    using value_type = RangeChminChmaxAddRangeSumNode<T>;\n\
    \n    // Represents f(x) = clamp(x + add, lower, upper).\n    struct operator_type\
    \ {\n        T add;\n        T lower;\n        T upper;\n    };\n\n    static\
    \ constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = false;\n    static constexpr T negative_infinity = std::numeric_limits<T>::lowest();\n\
    \    static constexpr T positive_infinity = std::numeric_limits<T>::max();\n\n\
    \   private:\n    static constexpr T shift_lower_bound(T bound, T add) {\n   \
    \     return bound == negative_infinity ? bound : bound + add;\n    }\n\n    static\
    \ constexpr T shift_upper_bound(T bound, T add) {\n        return bound == positive_infinity\
    \ ? bound : bound + add;\n    }\n\n    static constexpr void apply_add(value_type&\
    \ value, T add) {\n        if (value.length == 0 || add == T(0)) return;\n   \
    \     value.sum += add * T(value.length);\n        value.maximum += add;\n   \
    \     value.minimum += add;\n        if (value.maximum_count != value.length)\
    \ {\n            value.second_maximum += add;\n        }\n        if (value.minimum_count\
    \ != value.length) {\n            value.second_minimum += add;\n        }\n  \
    \  }\n\n    static constexpr bool can_apply_chmin(\n        const value_type&\
    \ value,\n        T upper\n    ) {\n        return value.maximum <= upper ||\n\
    \            value.maximum_count == value.length ||\n            value.second_maximum\
    \ < upper;\n    }\n\n    static constexpr void apply_chmin(value_type& value,\
    \ T upper) {\n        if (value.maximum <= upper) return;\n        assert(can_apply_chmin(value,\
    \ upper));\n        value.sum +=\n            (upper - value.maximum) * T(value.maximum_count);\n\
    \        if (value.minimum == value.maximum) {\n            value.minimum = upper;\n\
    \        } else if (value.second_minimum == value.maximum) {\n            value.second_minimum\
    \ = upper;\n        }\n        value.maximum = upper;\n    }\n\n    static constexpr\
    \ bool can_apply_chmax(\n        const value_type& value,\n        T lower\n \
    \   ) {\n        return lower <= value.minimum ||\n            value.minimum_count\
    \ == value.length ||\n            lower < value.second_minimum;\n    }\n\n   \
    \ static constexpr void apply_chmax(value_type& value, T lower) {\n        if\
    \ (lower <= value.minimum) return;\n        assert(can_apply_chmax(value, lower));\n\
    \        value.sum +=\n            (lower - value.minimum) * T(value.minimum_count);\n\
    \        if (value.maximum == value.minimum) {\n            value.maximum = lower;\n\
    \        } else if (value.second_maximum == value.minimum) {\n            value.second_maximum\
    \ = lower;\n        }\n        value.minimum = lower;\n    }\n\n    static constexpr\
    \ value_type constant_value(T value, int length) {\n        return {\n       \
    \     value * T(length),\n            value,\n            negative_infinity,\n\
    \            value,\n            positive_infinity,\n            length,\n   \
    \         length,\n            length\n        };\n    }\n\n   public:\n    static\
    \ constexpr value_type id() {\n        return {\n            T(0),\n         \
    \   negative_infinity,\n            negative_infinity,\n            positive_infinity,\n\
    \            positive_infinity,\n            0,\n            0,\n            0\n\
    \        };\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        if (left.length ==\
    \ 0) return right;\n        if (right.length == 0) return left;\n\n        value_type\
    \ result;\n        result.sum = left.sum + right.sum;\n        result.length =\
    \ left.length + right.length;\n\n        result.maximum = std::max(left.maximum,\
    \ right.maximum);\n        result.maximum_count = 0;\n        result.second_maximum\
    \ = negative_infinity;\n        if (left.maximum == result.maximum) {\n      \
    \      result.maximum_count += left.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                left.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                left.maximum\n      \
    \      );\n        }\n        if (right.maximum == result.maximum) {\n       \
    \     result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                right.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                right.maximum\n     \
    \       );\n        }\n\n        result.minimum = std::min(left.minimum, right.minimum);\n\
    \        result.minimum_count = 0;\n        result.second_minimum = positive_infinity;\n\
    \        if (left.minimum == result.minimum) {\n            result.minimum_count\
    \ += left.minimum_count;\n            result.second_minimum = std::min(\n    \
    \            result.second_minimum,\n                left.second_minimum\n   \
    \         );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                left.minimum\n      \
    \      );\n        }\n        if (right.minimum == result.minimum) {\n       \
    \     result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ = std::min(\n                result.second_minimum,\n                right.second_minimum\n\
    \            );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                right.minimum\n     \
    \       );\n        }\n        return result;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), negative_infinity, positive_infinity};\n  \
    \  }\n\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(\n\
    \        const operator_type& f,\n        const operator_type& g\n    ) {\n  \
    \      T lower = shift_lower_bound(g.lower, f.add);\n        T upper = shift_upper_bound(g.upper,\
    \ f.add);\n        return {\n            g.add + f.add,\n            std::clamp(lower,\
    \ f.lower, f.upper),\n            std::clamp(upper, f.lower, f.upper)\n      \
    \  };\n    }\n\n    static constexpr bool can_apply(\n        const operator_type&\
    \ f,\n        const value_type& value\n    ) {\n        if (value.length == 0\
    \ || f.lower == f.upper) return true;\n        value_type mapped = value;\n  \
    \      apply_add(mapped, f.add);\n        if (\n            mapped.maximum <=\
    \ f.lower ||\n            f.upper <= mapped.minimum\n        ) {\n           \
    \ return true;\n        }\n        if (!can_apply_chmax(mapped, f.lower)) return\
    \ false;\n        apply_chmax(mapped, f.lower);\n        return can_apply_chmin(mapped,\
    \ f.upper);\n    }\n\n    static constexpr value_type mapping(\n        const\
    \ operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        if (f.lower\
    \ == f.upper) {\n            return constant_value(f.lower, value.length);\n \
    \       }\n        value_type result = value;\n        apply_add(result, f.add);\n\
    \        if (result.maximum <= f.lower) {\n            return constant_value(f.lower,\
    \ result.length);\n        }\n        if (f.upper <= result.minimum) {\n     \
    \       return constant_value(f.upper, result.length);\n        }\n        apply_chmax(result,\
    \ f.lower);\n        apply_chmin(result, f.upper);\n        return result;\n \
    \   }\n\n    static constexpr value_type make(const T& value) {\n        return\
    \ constant_value(value, 1);\n    }\n\n    static constexpr operator_type make_chmin(const\
    \ T& upper) {\n        return {T(0), negative_infinity, upper};\n    }\n\n   \
    \ static constexpr operator_type make_chmax(const T& lower) {\n        return\
    \ {T(0), lower, positive_infinity};\n    }\n\n    static constexpr operator_type\
    \ make_add(const T& add) {\n        return {add, negative_infinity, positive_infinity};\n\
    \    }\n};\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_BEATS_ACTED_MONOID_RANGE_CHMIN_CHMAX_ADD_RANGE_SUM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
  requiredBy: []
  timestamp: '2026-08-12 01:20:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
  - verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
documentation_of: beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
layout: document
title: Range Chmin/Chmax/Add Range Sum
---

## Overview

`m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<T>` is a Beats acted
monoid for these range updates:

* `a[i] = min(a[i], upper)`
* `a[i] = max(a[i], lower)`
* `a[i] += add`

It aggregates range sums and is intended for `SegtreeBeats` or
`PersistentSegtreeBeats`. Each node stores the sum, minimum, second minimum,
maximum, second maximum, their occurrence counts, and the segment length.

The lazy `operator_type` represents

```cpp
f(x) = clamp(x + add, lower, upper);
```

Use `make_chmin`, `make_chmax`, and `make_add` instead of constructing that
operator directly.

## Template requirements

`T` must satisfy `std::signed_integral` and defaults to `long long`. All values,
sums, differences, products by segment lengths, accumulated additions, and
finite shifted bounds must remain representable by `T`.

`value_type` is
`RangeChminChmaxAddRangeSumNode<T>` and has these public members:

```cpp
T sum;
T maximum;
T second_maximum;
T minimum;
T second_minimum;
int maximum_count;
int minimum_count;
int length;
```

For a constant nonempty segment, `second_maximum` is
`std::numeric_limits<T>::lowest()` and `second_minimum` is
`std::numeric_limits<T>::max()`.

## Interface and complexity

Every acted-monoid operation below takes $O(1)$ time.

| Member | Description | Complexity |
| --- | --- | --- |
| `static value_type id()` | Returns the empty aggregate. | $O(1)$ |
| `static value_type op(const value_type& x, const value_type& y)` | Concatenates two aggregates. | $O(1)$ |
| `static operator_type op_id()` | Returns the identity update. | $O(1)$ |
| `static operator_type op_comp(const operator_type& f, const operator_type& g)` | Returns $f \circ g$. | $O(1)$ |
| `static bool can_apply(const operator_type& f, const value_type& x)` | Reports whether `mapping(f, x)` can update this node without descending. | $O(1)$ |
| `static value_type mapping(const operator_type& f, const value_type& x)` | Applies an update after `can_apply` succeeds. | $O(1)$ |
| `static value_type make(const T& value)` | Constructs a one-element aggregate. | $O(1)$ |
| `static operator_type make_chmin(const T& upper)` | Constructs a range-`chmin` update. | $O(1)$ |
| `static operator_type make_chmax(const T& lower)` | Constructs a range-`chmax` update. | $O(1)$ |
| `static operator_type make_add(const T& add)` | Constructs a range-add update. | $O(1)$ |

`can_apply` succeeds when each clamp is a no-op, changes only the known extreme,
or makes the segment constant. Otherwise the Beats tree descends. With
`SegtreeBeats`, an operation takes $O(\log N+D)$, where $D$ is the number of
extra nodes visited after failed applications.

## Example

```cpp
#include "beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "ds/segtree/segtree_beats.hpp"

#include <iostream>
#include <vector>

using AM =
    m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;

int main() {
    std::vector<long long> values = {8, 3, 6, 7};
    m1une::ds::SegtreeBeats<AM> seg(values);

    seg.apply(0, 4, AM::make_chmin(6));
    seg.apply(1, 3, AM::make_chmax(5));
    seg.apply(0, 2, AM::make_add(2));

    std::cout << seg.prod(0, 4).sum << '\n';
}
```
