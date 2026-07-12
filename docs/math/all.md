---
title: Math All
documentation_of: ../../math/all.hpp
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
* Use `discrete_logarithm.hpp` to solve `base^x = target (mod mod)` for the
  smallest nonnegative exponent.
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
* Use `prefix_sum_of_binom.hpp` for online or offline queries of
  $\sum_{k=0}^{m-1}\binom{n}{k}$.
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
| `math/discrete_logarithm.hpp` | Extended baby-step--giant-step for discrete logarithms modulo any positive integer. |
| `math/generalized_floor_sum.hpp` | Polynomial moments of a linear floor sequence using monoid floor sum. |
| `math/number_theory.hpp` | Extended GCD, modular power and inverse, CRT, and floor sum. |
| `math/partition_function.hpp` | Integer partition numbers via Euler's pentagonal theorem and FPS inversion. |
| `math/prefix_sum_of_binom.hpp` | Online and offline prefix sums of binomial coefficients. |
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
