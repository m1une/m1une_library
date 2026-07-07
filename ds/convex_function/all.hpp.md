---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/convex_function/slope_trick.hpp
    title: Slope Trick
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/convex_function/all.hpp\"\n\n\n\n#line 1 \"ds/convex_function/slope_trick.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <optional>\n#include\
    \ <queue>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n \
    \   std::optional<T> left;\n    std::optional<T> right;\n};\n\ntemplate <class\
    \ T>\nclass SlopeTrick {\n    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\
    \n    T _minimum = T();\n    T _left_offset = T();\n    T _right_offset = T();\n\
    \    std::priority_queue<T> _left;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> _right;\n\n    T left_top() const {\n        return _left.top()\
    \ + _left_offset;\n    }\n\n    T right_top() const {\n        return _right.top()\
    \ + _right_offset;\n    }\n\n    void push_left(T value) {\n        _left.push(value\
    \ - _left_offset);\n    }\n\n    void push_right(T value) {\n        _right.push(value\
    \ - _right_offset);\n    }\n\n   public:\n    SlopeTrick() = default;\n\n    T\
    \ minimum() const {\n        return _minimum;\n    }\n\n    int breakpoint_count()\
    \ const {\n        return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 5 \"ds/convex_function/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_DS_CONVEX_FUNCTION_ALL_HPP

    #define M1UNE_DS_CONVEX_FUNCTION_ALL_HPP 1


    #include "slope_trick.hpp"


    #endif  // M1UNE_DS_CONVEX_FUNCTION_ALL_HPP

    '
  dependsOn:
  - ds/convex_function/slope_trick.hpp
  isVerificationFile: false
  path: ds/convex_function/all.hpp
  requiredBy: []
  timestamp: '2026-07-07 17:18:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: ds/convex_function/all.hpp
layout: document
title: Convex Function All
---

## Overview

`ds/convex_function/all.hpp` includes data structures that maintain convex
piecewise-linear functions.
The public namespace is `m1une::ds`.

## Included Headers

| Header | Contents |
| --- | --- |
| `ds/convex_function/slope_trick.hpp` | Heap-based slope-trick representation of a convex piecewise-linear function. |
