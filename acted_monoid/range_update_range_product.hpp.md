---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/power.hpp
    title: Monoid Power
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/range_update_range_product.test.cpp
    title: verify/ds/segtree/range_update_range_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/range_update_range_product.hpp\"\n\n\n\n#include\
    \ <optional>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\n\
    namespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 1 \"monoid/power.hpp\"\n\n\n\n#line 5 \"monoid/power.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Computes a^n (a * a * ... * a,\
    \ n times) for an element 'a' in Monoid 'M'.\n// Uses binary exponentiation to\
    \ achieve O(log n) time complexity.\n// The template parameter 'M' is constrained\
    \ by the 'IsMonoid' concept.\ntemplate <IsMonoid M>\nconstexpr typename M::value_type\
    \ power(typename M::value_type a, long long n) {\n    typename M::value_type res\
    \ = M::id();\n    while (n > 0) {\n        if (n & 1) {\n            res = M::op(res,\
    \ a);\n        }\n        a = M::op(a, a);\n        n >>= 1;\n    }\n    return\
    \ res;\n}\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 8 \"acted_monoid/range_update_range_product.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct RangeUpdateRangeProductNode {\n    using base_type = typename\
    \ Monoid::value_type;\n\n    base_type product;\n    long long size;\n};\n\n//\
    \ Range assignment and range product for an arbitrary, possibly\n// noncommutative,\
    \ monoid.\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct RangeUpdateRangeProduct\
    \ {\n    using base_type = typename Monoid::value_type;\n    using value_type\
    \ = RangeUpdateRangeProductNode<Monoid>;\n    using operator_type = std::optional<base_type>;\n\
    \n    static constexpr value_type id() {\n        return {Monoid::id(), 0};\n\
    \    }\n\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {Monoid::op(a.product, b.product), a.size + b.size};\n\
    \    }\n\n    static constexpr operator_type op_id() {\n        return std::nullopt;\n\
    \    }\n\n    static constexpr operator_type op_comp(const operator_type& f, const\
    \ operator_type& g) {\n        return f.has_value() ? f : g;\n    }\n\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        if (!f.has_value() || x.size == 0) return x;\n        return {m1une::monoid::power<Monoid>(f.value(),\
    \ x.size), x.size};\n    }\n\n    static constexpr value_type make(const base_type&\
    \ value) {\n        return {value, 1};\n    }\n};\n\n}  // namespace acted_monoid\n\
    }  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP\n#define M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP\
    \ 1\n\n#include <optional>\n\n#include \"../monoid/concept.hpp\"\n#include \"\
    ../monoid/power.hpp\"\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate\
    \ <m1une::monoid::IsMonoid Monoid>\nstruct RangeUpdateRangeProductNode {\n   \
    \ using base_type = typename Monoid::value_type;\n\n    base_type product;\n \
    \   long long size;\n};\n\n// Range assignment and range product for an arbitrary,\
    \ possibly\n// noncommutative, monoid.\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct RangeUpdateRangeProduct {\n    using base_type = typename Monoid::value_type;\n\
    \    using value_type = RangeUpdateRangeProductNode<Monoid>;\n    using operator_type\
    \ = std::optional<base_type>;\n\n    static constexpr value_type id() {\n    \
    \    return {Monoid::id(), 0};\n    }\n\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {Monoid::op(a.product,\
    \ b.product), a.size + b.size};\n    }\n\n    static constexpr operator_type op_id()\
    \ {\n        return std::nullopt;\n    }\n\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f.has_value()\
    \ ? f : g;\n    }\n\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        if (!f.has_value() || x.size == 0) return\
    \ x;\n        return {m1une::monoid::power<Monoid>(f.value(), x.size), x.size};\n\
    \    }\n\n    static constexpr value_type make(const base_type& value) {\n   \
    \     return {value, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_ACTED_MONOID_RANGE_UPDATE_RANGE_PRODUCT_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - monoid/power.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: acted_monoid/range_update_range_product.hpp
  requiredBy: []
  timestamp: '2026-07-16 20:57:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/segtree/range_update_range_product.test.cpp
documentation_of: acted_monoid/range_update_range_product.hpp
layout: document
title: Range Update Range Product
---

## Overview

`m1une::acted_monoid::RangeUpdateRangeProduct<Monoid>` adapts any monoid for
range assignment and range product queries. It works for noncommutative monoids:
the product keeps the original left-to-right order defined by `Monoid::op`.

Assigning `value` to a segment of length $k$ changes its aggregate to
$value^k$. The adapter computes this power with binary exponentiation.

## Requirements and behavior

`Monoid` must satisfy `m1une::monoid::IsMonoid`. In particular, it provides:

* `using value_type = ...;`
* `static value_type id();`
* `static value_type op(const value_type&, const value_type&);`

The operator type is `std::optional<Monoid::value_type>`. `std::nullopt` means
no assignment, and a present value overwrites every element of the segment.
When lazy assignments are composed, the newer present assignment wins.

The aggregate node stores both `product` and `size`. Initialize a lazy segment
tree from `std::vector<Monoid::value_type>` so that its adapting constructor
calls `make(value)`, or call `make(value)` yourself. The size-only
`LazySegtree<AM>(n)` constructor creates identity nodes of length zero and is not
suitable until every leaf has been replaced with a node returned by `make`.

## Interface

For `using AM = m1une::acted_monoid::RangeUpdateRangeProduct<Monoid>;`:

| Member | Signature | Meaning | Complexity |
| --- | --- | --- | --- |
| Base value | `using base_type = typename Monoid::value_type;` | One array element. | -- |
| Aggregate | `using value_type = RangeUpdateRangeProductNode<Monoid>;` | Stores `base_type product` and `long long size`. | -- |
| Lazy operator | `using operator_type = std::optional<base_type>;` | A range assignment, or no operation. | -- |
| Identity | `static constexpr value_type id();` | Empty product with size zero. | One `Monoid::id()` call. |
| Product | `static constexpr value_type op(const value_type& a, const value_type& b);` | Concatenates `a` followed by `b`. | One `Monoid::op()` call. |
| Operator identity | `static constexpr operator_type op_id();` | Returns `std::nullopt`. | $O(1)$ |
| Operator composition | `static constexpr operator_type op_comp(const operator_type& f, const operator_type& g);` | Returns `f` when present, otherwise `g`; `f` is newer. | $O(1)$ plus copying one operator. |
| Apply assignment | `static constexpr value_type mapping(const operator_type& f, const value_type& x);` | Replaces `x.product` by the assigned value to the power `x.size`. | $O(\log x.size)$ monoid operations for an assignment; otherwise one node copy. |
| Make leaf | `static constexpr value_type make(const base_type& value);` | Returns `{value, 1}`. | One value copy. |

With `m1une::ds::LazySegtree<AM>` on $N$ elements, construction and range
product take $O(N)$ and $O(\log N)$ monoid operations respectively. A range
assignment takes $O(\log^2 N)$ monoid operations in the worst case because up
to $O(\log N)$ segment-tree nodes each compute a power. Memory use is $O(N)$.

## Example

```cpp
#include "acted_monoid/range_update_range_product.hpp"
#include "ds/segtree/lazy_segtree.hpp"

#include <iostream>
#include <string>
#include <vector>

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
    using AM = m1une::acted_monoid::RangeUpdateRangeProduct<Concat>;

    std::vector<std::string> values = {"a", "b", "c", "d"};
    m1une::ds::LazySegtree<AM> seg(values);

    seg.apply(1, 3, std::string("x"));
    std::cout << seg.prod(0, 4).product << '\n';  // axxd
}
```
