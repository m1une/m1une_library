---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':question:'
    path: math/fps/internal/ntt998_fast.hpp
    title: math/fps/internal/ntt998_fast.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 17: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_FPS_ALL_HPP

    #define M1UNE_FPS_ALL_HPP 1


    #include "convolution.hpp"

    #include "convolution_ll.hpp"

    #include "floating_point_convolution.hpp"

    #include "formal_power_series.hpp"

    #include "half_gcd.hpp"

    #include "lagrange_inversion.hpp"

    #include "linear_recurrence.hpp"

    #include "multipoint_evaluation.hpp"


    #endif  // M1UNE_FPS_ALL_HPP

    '
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_fast.hpp
  - math/modint.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  isVerificationFile: false
  path: math/fps/all.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/all.hpp
layout: document
title: Formal Power Series All
---

## Overview

`math/fps/all.hpp` includes every formal power series header in this directory.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/fps/convolution.hpp` | Naive, NTT, and CRT-based convolution. |
| `math/fps/convolution_ll.hpp` | Exact signed 64-bit convolution using three NTT primes. |
| `math/fps/floating_point_convolution.hpp` | FFT convolution for real, complex, and rounded integral coefficients. |
| `math/fps/formal_power_series.hpp` | Formal power series operations and polynomial utilities. |
| `math/fps/half_gcd.hpp` | Fast half-GCD, polynomial GCD, extended GCD, and modular inverse. |
| `math/fps/lagrange_inversion.hpp` | Coefficients from the Lagrange inversion and Lagrange-Bürmann formulas. |
| `math/fps/linear_recurrence.hpp` | Berlekamp-Massey and linear-recurrence term evaluation. |
| `math/fps/multipoint_evaluation.hpp` | Multipoint evaluation and polynomial interpolation. |
