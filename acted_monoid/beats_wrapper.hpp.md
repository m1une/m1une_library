---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tests/ds/segtree/segtree_beats_test.cpp
    title: tests/ds/segtree/segtree_beats_test.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"acted_monoid/beats_wrapper.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\n// Wrapper for defining a Beats\
    \ acted monoid with functions or constexpr lambdas.\ntemplate <\n    typename\
    \ T,\n    typename E,\n    auto Op,\n    auto Id,\n    auto OpComp,\n    auto\
    \ OpId,\n    auto Mapping,\n    auto CanApply,\n    auto Make = nullptr,\n   \
    \ auto MakeAt = nullptr,\n    auto MappingAt = nullptr,\n    auto CanApplyAt =\
    \ nullptr,\n    auto OpShift = nullptr\n>\nstruct BeatsWrapper {\n    using value_type\
    \ = T;\n    using operator_type = E;\n\n    static constexpr T id() {\n      \
    \  return Id();\n    }\n\n    static constexpr T op(const T& lhs, const T& rhs)\
    \ {\n        return Op(lhs, rhs);\n    }\n\n    static constexpr E op_id() {\n\
    \        return OpId();\n    }\n\n    static constexpr E op_comp(const E& f, const\
    \ E& g) {\n        return OpComp(f, g);\n    }\n\n    static constexpr T mapping(const\
    \ E& f, const T& x) {\n        return Mapping(f, x);\n    }\n\n    static constexpr\
    \ bool can_apply(const E& f, const T& x) {\n        return CanApply(f, x);\n \
    \   }\n\n    template <typename U>\n    requires requires(const U& value) {\n\
    \        { Make(value) } -> std::convertible_to<T>;\n    }\n    static constexpr\
    \ T make(const U& value) {\n        return Make(value);\n    }\n\n    template\
    \ <typename U>\n    requires requires(const U& value, int index) {\n        {\
    \ MakeAt(value, index) } -> std::convertible_to<T>;\n    }\n    static constexpr\
    \ T make(const U& value, int index) {\n        return MakeAt(value, index);\n\
    \    }\n\n    static constexpr T mapping(const E& f, const T& x, long long ordinal)\n\
    \    requires requires {\n        { MappingAt(f, x, ordinal) } -> std::convertible_to<T>;\n\
    \    }\n    {\n        return MappingAt(f, x, ordinal);\n    }\n\n    static constexpr\
    \ bool can_apply(\n        const E& f,\n        const T& x,\n        long long\
    \ ordinal\n    )\n    requires requires {\n        { CanApplyAt(f, x, ordinal)\
    \ } -> std::convertible_to<bool>;\n    }\n    {\n        return CanApplyAt(f,\
    \ x, ordinal);\n    }\n\n    static constexpr E op_shift(const E& f, long long\
    \ ordinal)\n    requires requires {\n        { OpShift(f, ordinal) } -> std::convertible_to<E>;\n\
    \    }\n    {\n        return OpShift(f, ordinal);\n    }\n};\n\n}  // namespace\
    \ acted_monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP\n#define M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP\
    \ 1\n\n#include <concepts>\n\nnamespace m1une {\nnamespace acted_monoid {\n\n\
    // Wrapper for defining a Beats acted monoid with functions or constexpr lambdas.\n\
    template <\n    typename T,\n    typename E,\n    auto Op,\n    auto Id,\n   \
    \ auto OpComp,\n    auto OpId,\n    auto Mapping,\n    auto CanApply,\n    auto\
    \ Make = nullptr,\n    auto MakeAt = nullptr,\n    auto MappingAt = nullptr,\n\
    \    auto CanApplyAt = nullptr,\n    auto OpShift = nullptr\n>\nstruct BeatsWrapper\
    \ {\n    using value_type = T;\n    using operator_type = E;\n\n    static constexpr\
    \ T id() {\n        return Id();\n    }\n\n    static constexpr T op(const T&\
    \ lhs, const T& rhs) {\n        return Op(lhs, rhs);\n    }\n\n    static constexpr\
    \ E op_id() {\n        return OpId();\n    }\n\n    static constexpr E op_comp(const\
    \ E& f, const E& g) {\n        return OpComp(f, g);\n    }\n\n    static constexpr\
    \ T mapping(const E& f, const T& x) {\n        return Mapping(f, x);\n    }\n\n\
    \    static constexpr bool can_apply(const E& f, const T& x) {\n        return\
    \ CanApply(f, x);\n    }\n\n    template <typename U>\n    requires requires(const\
    \ U& value) {\n        { Make(value) } -> std::convertible_to<T>;\n    }\n   \
    \ static constexpr T make(const U& value) {\n        return Make(value);\n   \
    \ }\n\n    template <typename U>\n    requires requires(const U& value, int index)\
    \ {\n        { MakeAt(value, index) } -> std::convertible_to<T>;\n    }\n    static\
    \ constexpr T make(const U& value, int index) {\n        return MakeAt(value,\
    \ index);\n    }\n\n    static constexpr T mapping(const E& f, const T& x, long\
    \ long ordinal)\n    requires requires {\n        { MappingAt(f, x, ordinal) }\
    \ -> std::convertible_to<T>;\n    }\n    {\n        return MappingAt(f, x, ordinal);\n\
    \    }\n\n    static constexpr bool can_apply(\n        const E& f,\n        const\
    \ T& x,\n        long long ordinal\n    )\n    requires requires {\n        {\
    \ CanApplyAt(f, x, ordinal) } -> std::convertible_to<bool>;\n    }\n    {\n  \
    \      return CanApplyAt(f, x, ordinal);\n    }\n\n    static constexpr E op_shift(const\
    \ E& f, long long ordinal)\n    requires requires {\n        { OpShift(f, ordinal)\
    \ } -> std::convertible_to<E>;\n    }\n    {\n        return OpShift(f, ordinal);\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_ACTED_MONOID_BEATS_WRAPPER_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: acted_monoid/beats_wrapper.hpp
  requiredBy:
  - tests/ds/segtree/segtree_beats_test.cpp
  timestamp: '2026-07-02 21:23:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: acted_monoid/beats_wrapper.hpp
layout: document
title: Beats Acted Monoid Wrapper
---

## Overview

`m1une::acted_monoid::BeatsWrapper` builds a Beats acted monoid from functions,
function objects, or captureless `constexpr` lambdas supplied as non-type
template arguments.

```cpp
template <
    class T, class F,
    auto Op, auto Id,
    auto OpComp, auto OpId,
    auto Mapping, auto CanApply,
    auto Make = nullptr,
    auto MakeAt = nullptr,
    auto MappingAt = nullptr,
    auto CanApplyAt = nullptr,
    auto OpShift = nullptr
>
struct BeatsWrapper;
```

The first eight function arguments define the required value monoid, operator
monoid, mapping, and applicability predicate. Optional arguments forward
`make(value)`, `make(value, index)`, index-aware `mapping`, index-aware
`can_apply`, and `op_shift` in that order.

All wrapper methods are constant-time apart from the user-supplied functions.
`op_comp(f, g)` must represent applying `g` before `f`, and `CanApply` must obey
the failure contract documented for `IsBeatsActedMonoid`.
