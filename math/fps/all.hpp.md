---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/composition.hpp
    title: Formal Power Series Composition
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':question:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  - icon: ':question:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':question:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':question:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':question:'
    path: math/fps/polynomial_factorization.hpp
    title: Polynomial Factorization
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_FPS_ALL_HPP

    #define M1UNE_FPS_ALL_HPP 1


    #include "composition.hpp"

    #include "convolution.hpp"

    #include "convolution_ll.hpp"

    #include "floating_point_convolution.hpp"

    #include "formal_power_series.hpp"

    #include "half_gcd.hpp"

    #include "lagrange_inversion.hpp"

    #include "linear_recurrence.hpp"

    #include "multipoint_evaluation.hpp"

    #include "polynomial_factorization.hpp"


    #endif  // M1UNE_FPS_ALL_HPP

    '
  dependsOn:
  - math/fps/composition.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/fps/polynomial_factorization.hpp
  isVerificationFile: false
  path: math/fps/all.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
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
| `math/fps/composition.hpp` | Fast truncated formal power series composition. |
| `math/fps/convolution.hpp` | Naive, NTT, and CRT-based convolution. |
| `math/fps/convolution_ll.hpp` | Exact signed 64-bit convolution using three NTT primes. |
| `math/fps/floating_point_convolution.hpp` | FFT convolution for real, complex, and rounded integral coefficients. |
| `math/fps/formal_power_series.hpp` | Formal power series operations and polynomial utilities. |
| `math/fps/half_gcd.hpp` | Fast half-GCD, polynomial GCD, extended GCD, and modular inverse. |
| `math/fps/lagrange_inversion.hpp` | Coefficients from the Lagrange inversion and Lagrange-Bürmann formulas. |
| `math/fps/linear_recurrence.hpp` | Berlekamp-Massey and linear-recurrence term evaluation. |
| `math/fps/multipoint_evaluation.hpp` | Multipoint evaluation and polynomial interpolation. |
| `math/fps/polynomial_factorization.hpp` | Factorization into monic irreducible polynomials over a prime field. |
