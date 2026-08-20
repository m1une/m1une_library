---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/persistent_segtree_beats.hpp
    title: ds/segtree/persistent_segtree_beats.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_segtree_beats.hpp
    title: Rollback Segment Tree Beats
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_beats.hpp
    title: Generic Segment Tree Beats!
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
    title: verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/persistent_cow.test.cpp
    title: verify/ds/persistent_cow.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/persistent_segtree_beats.test.cpp
    title: verify/ds/segtree/persistent_segtree_beats.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/segtree/segtree_beats.test.cpp
    title: verify/ds/segtree/segtree_beats.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/monoid/commutative_flags.test.cpp
    title: verify/monoid/commutative_flags.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"beats_acted_monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 7 \"beats_acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ beats_acted_monoid {\n\n// An acted monoid whose action may require descent\
    \ before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP\n#define M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP\
    \ 1\n\n#include <concepts>\n\n#include \"../acted_monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace beats_acted_monoid {\n\n// An acted monoid whose action may\
    \ require descent before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_BEATS_ACTED_MONOID_CONCEPT_HPP\n"
  dependsOn:
  - acted_monoid/concept.hpp
  isVerificationFile: false
  path: beats_acted_monoid/concept.hpp
  requiredBy:
  - ds/segtree/persistent_segtree_beats.hpp
  - ds/segtree/segtree_beats.hpp
  - ds/segtree/rollback_segtree_beats.hpp
  timestamp: '2026-08-12 01:20:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/persistent_cow.test.cpp
  - verify/ds/rollback_counterparts.test.cpp
  - verify/ds/segtree/segtree_beats.test.cpp
  - verify/ds/segtree/persistent_segtree_beats.test.cpp
  - verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  - verify/beats_acted_monoid/range_chmin_chmax_add_range_sum.test.cpp
  - verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  - verify/beats_acted_monoid/range_bitwise_and_or_range_sum.test.cpp
  - verify/monoid/commutative_flags.test.cpp
documentation_of: beats_acted_monoid/concept.hpp
layout: document
title: Beats Acted Monoid Concept
---

## Overview

`m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>` extends
`m1une::acted_monoid::IsActedMonoid<AM>` with:

```cpp
static bool can_apply(
    const operator_type& f,
    const value_type& x
);
```

It is used by `ds::SegtreeBeats`. A true result promises that `mapping(f, x)`
can update the whole represented segment. A false result requires descent and
forbids both calling `mapping` at that node and composing `f` into its lazy
tag. Every valid update must eventually be applicable at every real leaf. The
identity operator must always be applicable and leave values unchanged.

`op_comp(f, g)` means applying `g` first, then `f`.

Optional three-argument `can_apply` and `mapping` overloads and optional
`op_shift` are recognized by `SegtreeBeats`; they are not additional concept
requirements.
