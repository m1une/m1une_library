---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/base_n.hpp
    title: Base-N Numbers
  - icon: ':heavy_check_mark:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  - icon: ':heavy_check_mark:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/cyclotomic_polynomial.hpp
    title: Cyclotomic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':heavy_check_mark:'
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
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/generalized_floor_sum.hpp
    title: Generalized Floor Sum
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Square Root and Power
  - icon: ':heavy_check_mark:'
    path: math/lucas.hpp
    title: Lucas's Theorem
  - icon: ':heavy_check_mark:'
    path: math/matrix/all.hpp
    title: Matrix Bundle
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  - icon: ':heavy_check_mark:'
    path: math/partition_function.hpp
    title: Partition Function
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':heavy_check_mark:'
    path: math/prime_sieve.hpp
    title: Prime Sieve
  - icon: ':heavy_check_mark:'
    path: math/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':heavy_check_mark:'
    path: math/repunit.hpp
    title: Repunit
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  - icon: ':heavy_check_mark:'
    path: math/tetration.hpp
    title: Tetration
  - icon: ':heavy_check_mark:'
    path: math/totient_sum.hpp
    title: Totient Sum
  - icon: ':heavy_check_mark:'
    path: math/two_square_sum.hpp
    title: Sum of Two Squares
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_MATH_ALL_HPP

    #define M1UNE_MATH_ALL_HPP 1


    #include "base_n.hpp"

    #include "bernoulli.hpp"

    #include "bitwise_convolution.hpp"

    #include "bit_ceil.hpp"

    #include "combinatorics.hpp"

    #include "combinatorial_sequences.hpp"

    #include "cyclotomic_polynomial.hpp"

    #include "generalized_floor_sum.hpp"

    #include "integer_arithmetic.hpp"

    #include "lucas.hpp"

    #include "fps/all.hpp"

    #include "matrix/all.hpp"

    #include "modint.hpp"

    #include "modular_square_root.hpp"

    #include "number_theory.hpp"

    #include "partition_function.hpp"

    #include "prime_factorization.hpp"

    #include "primitive_root.hpp"

    #include "prime_sieve.hpp"

    #include "rational.hpp"

    #include "repunit.hpp"

    #include "stern_brocot_tree.hpp"

    #include "tetration.hpp"

    #include "totient_sum.hpp"

    #include "two_square_sum.hpp"

    #include "zeta_mobius_transform.hpp"


    #endif  // M1UNE_MATH_ALL_HPP

    '
  dependsOn:
  - math/base_n.hpp
  - math/bernoulli.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  - math/bitwise_convolution.hpp
  - math/zeta_mobius_transform.hpp
  - math/bit_ceil.hpp
  - math/combinatorial_sequences.hpp
  - math/partition_function.hpp
  - math/cyclotomic_polynomial.hpp
  - math/prime_factorization.hpp
  - math/generalized_floor_sum.hpp
  - math/integer_arithmetic.hpp
  - math/lucas.hpp
  - math/fps/all.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/matrix/all.hpp
  - math/matrix/linear_algebra.hpp
  - math/matrix/matrix.hpp
  - math/modint.hpp
  - math/modular_square_root.hpp
  - math/number_theory.hpp
  - math/primitive_root.hpp
  - math/prime_sieve.hpp
  - math/rational.hpp
  - math/repunit.hpp
  - math/stern_brocot_tree.hpp
  - math/tetration.hpp
  - math/totient_sum.hpp
  - math/two_square_sum.hpp
  isVerificationFile: false
  path: math/all.hpp
  requiredBy: []
  timestamp: '2026-07-11 19:26:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
documentation_of: math/all.hpp
layout: document
title: Math All
---

## Overview

`math/all.hpp` includes every general math header in this directory, including
the FPS/polynomial and dense-matrix subcategories.

Public namespaces stay flat and short: general math helpers use `m1une::math`,
FPS helpers use `m1une::fps`, and dense matrix helpers use `m1une::matrix`.

## Choosing a Header

You usually do not need to include this entire bundle:

* Use `modint.hpp` for arithmetic modulo a fixed number such as `998244353`.
* Use `modular_square_root.hpp` to solve `x * x = value (mod prime)`.
* Use `base_n.hpp` to convert nonnegative integers to and from arbitrary-base
  digit sequences.
* Use `bitwise_convolution.hpp` for OR, AND, or XOR convolution over mask
  indices.
* Use `generalized_floor_sum.hpp` for polynomial moments of
  `floor((a * i + b) / mod)`.
* Use `zeta_mobius_transform.hpp` for subset, superset, divisor, and multiple
  transforms.
* Use `combinatorics.hpp` for many factorial, combination, or permutation
  queries under a prime modulus.
* Use `lucas.hpp` for binomial coefficients with huge arguments modulo a small
  prime.
* Use `bernoulli.hpp` for Bernoulli numbers, Bernoulli polynomials, Faulhaber
  sums, and polynomial discrete integration.
* Use `combinatorial_sequences.hpp` for Catalan, Bell, Stirling, partition, or
  derangement numbers.
* Use `partition_function.hpp` when only integer partition numbers are needed.
* Use `cyclotomic_polynomial.hpp` to construct the polynomial of primitive
  roots of unity of a given order.
* Use `prime_sieve.hpp` when all queried integers are at most a manageable
  limit, usually a few million or tens of millions.
* Use `prime_factorization.hpp` for isolated 64-bit integers that are too large
  for a sieve.
* Use `primitive_root.hpp` to find a generator of the multiplicative group
  modulo an integer when one exists.
* Use `two_square_sum.hpp` to enumerate non-negative pairs `(a, b)` satisfying
  `n = a * a + b * b`.
* Use `number_theory.hpp` for extended GCD, modular inverses, simultaneous
  remainder constraints, and sums involving floor division.
* Use `integer_arithmetic.hpp` for exact integer square roots and powers.
* Use `repunit.hpp` for a repeated-one numeral or geometric sum in an
  arbitrary base.
* Use `tetration.hpp` for modular tetration and arbitrary power towers.
* Use `totient_sum.hpp` for summatory Euler totient queries.
* Use `rational.hpp` for normalized exact fractions.
* Use `stern_brocot_tree.hpp` for positive rational tree paths, ancestors, and
  LCA operations.
* Use `fps/` for formal power series, convolution, multipoint evaluation,
  interpolation, and linear recurrences.
* Use `matrix/` for dense matrices and linear algebra.

`math/all.hpp` is convenient during a contest when compile time and including a
few unused headers do not matter.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/base_n.hpp` | Checked conversion between integers and arbitrary-base digits. |
| `math/bernoulli.hpp` | Bernoulli numbers and polynomials, power sums, and polynomial discrete integration. |
| `math/bitwise_convolution.hpp` | OR, AND, XOR convolutions and the Walsh-Hadamard transform. |
| `math/bit_ceil.hpp` | Smallest power of two at least a given value. |
| `math/integer_arithmetic.hpp` | Exact integer square roots and overflow-aware powers. |
| `math/lucas.hpp` | Lucas's theorem for huge binomial arguments modulo a small prime. |
| `math/modint.hpp` | Static modular integer type. |
| `math/modular_square_root.hpp` | Modular square roots for prime moduli using Tonelli-Shanks. |
| `math/fps/all.hpp` | Convolution, formal power series, polynomial algorithms, and linear recurrences. |
| `math/matrix/all.hpp` | Dense matrices, powers, Gaussian elimination, determinant, inverse, and linear systems. |
| `math/combinatorics.hpp` | Factorials, binomial coefficients, permutations, and multiset counts. |
| `math/combinatorial_sequences.hpp` | Fast standard counting sequences and special numbers. |
| `math/cyclotomic_polynomial.hpp` | Integer coefficients of cyclotomic polynomials. |
| `math/generalized_floor_sum.hpp` | Polynomial moments of a linear floor sequence using monoid floor sum. |
| `math/number_theory.hpp` | Extended GCD, modular power and inverse, CRT, and floor sum. |
| `math/partition_function.hpp` | Integer partition numbers via Euler's pentagonal theorem and FPS inversion. |
| `math/prime_sieve.hpp` | Linear sieve with smallest prime factors. |
| `math/prime_factorization.hpp` | Deterministic 64-bit primality test and Pollard-Rho factorization. |
| `math/primitive_root.hpp` | Smallest primitive root modulo an integer, when one exists. |
| `math/repunit.hpp` | Repunits, repdigits, digit-block concatenation, and divisibility lengths. |
| `math/two_square_sum.hpp` | Enumerates representations as a sum of two non-negative squares. |
| `math/tetration.hpp` | Modular tetration, arbitrary power towers, and bounded tower comparison. |
| `math/totient_sum.hpp` | Summatory Euler totient function. |
| `math/rational.hpp` | Exact normalized rational arithmetic over signed integers. |
| `math/stern_brocot_tree.hpp` | Compressed Stern-Brocot paths and tree navigation. |
| `math/zeta_mobius_transform.hpp` | Subset, superset, divisor, and multiple zeta/Mobius transforms. |
