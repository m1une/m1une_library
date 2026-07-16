---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/matrix/all.hpp
    title: Matrix Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/matrix.test.cpp
    title: verify/math/matrix/matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/matrix/sparse_determinant.test.cpp
    title: verify/math/matrix/sparse_determinant.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/matrix/sparse_determinant.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace matrix {\n\ntemplate <class T>\nstruct SparseMatrixEntry {\n    int\
    \ row;\n    int col;\n    T value;\n};\n\nnamespace internal {\n\nstruct SparseDeterminantRandom\
    \ {\n    std::uint64_t state;\n\n    explicit SparseDeterminantRandom(std::uint64_t\
    \ seed) : state(seed) {}\n\n    std::uint64_t operator()() {\n        std::uint64_t\
    \ value = (state += 0x9e3779b97f4a7c15ULL);\n        value = (value ^ (value >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return value ^ (value >> 31);\n    }\n};\n\ntemplate <class T>\nstd::vector<T>\
    \ berlekamp_massey(const std::vector<T>& sequence) {\n    std::vector<T> recurrence(1,\
    \ T(1));\n    std::vector<T> previous(1, T(1));\n    int degree = 0;\n    int\
    \ shift = 1;\n    T previous_discrepancy = T(1);\n\n    for (int index = 0; index\
    \ < int(sequence.size()); index++) {\n        T discrepancy = sequence[index];\n\
    \        for (int i = 1; i <= degree; i++) {\n            discrepancy += recurrence[i]\
    \ * sequence[index - i];\n        }\n        if (discrepancy == T()) {\n     \
    \       shift++;\n            continue;\n        }\n\n        const T factor =\
    \ discrepancy / previous_discrepancy;\n        std::vector<T> old_recurrence =\
    \ recurrence;\n        if (int(recurrence.size()) < int(previous.size()) + shift)\
    \ {\n            recurrence.resize(previous.size() + std::size_t(shift), T());\n\
    \        }\n        for (int i = 0; i < int(previous.size()); i++) {\n       \
    \     recurrence[i + shift] -= factor * previous[i];\n        }\n\n        if\
    \ (2 * degree <= index) {\n            degree = index + 1 - degree;\n        \
    \    previous = std::move(old_recurrence);\n            previous_discrepancy =\
    \ discrepancy;\n            shift = 1;\n        } else {\n            shift++;\n\
    \        }\n    }\n    recurrence.resize(std::size_t(degree + 1));\n    return\
    \ recurrence;\n}\n\n}  // namespace internal\n\n// Randomized black-box determinant\
    \ over a finite field. random_nonzero must\n// return independent nonzero field\
    \ elements.\ntemplate <class T, class RandomValue>\nT sparse_determinant_with_randomizer(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    RandomValue\
    \ random_nonzero\n) {\n    assert(size >= 0);\n    for (const SparseMatrixEntry<T>&\
    \ entry : entries) {\n        assert(0 <= entry.row && entry.row < size);\n  \
    \      assert(0 <= entry.col && entry.col < size);\n    }\n    if (size == 0)\
    \ return T(1);\n\n    auto random_vector = [&]() {\n        std::vector<T> result(size);\n\
    \        for (T& value : result) {\n            value = random_nonzero();\n  \
    \          assert(value != T());\n        }\n        return result;\n    };\n\n\
    \    while (true) {\n        std::vector<T> diagonal = random_vector();\n    \
    \    std::vector<T> left = random_vector();\n        std::vector<T> state = random_vector();\n\
    \        std::vector<T> sequence(std::size_t(2 * size));\n\n        for (int step\
    \ = 0; step < 2 * size; step++) {\n            for (int i = 0; i < size; i++)\
    \ sequence[step] += left[i] * state[i];\n            for (int i = 0; i < size;\
    \ i++) state[i] *= diagonal[i];\n\n            std::vector<T> next(size);\n  \
    \          for (const SparseMatrixEntry<T>& entry : entries) {\n             \
    \   next[entry.row] += entry.value * state[entry.col];\n            }\n      \
    \      state = std::move(next);\n        }\n\n        std::vector<T> recurrence\
    \ = internal::berlekamp_massey(sequence);\n        if (recurrence.back() == T())\
    \ return T();\n        if (int(recurrence.size()) != size + 1) continue;\n\n \
    \       T determinant = recurrence.back();\n        if (size % 2 == 1) determinant\
    \ = T() - determinant;\n        for (const T& value : diagonal) determinant /=\
    \ value;\n        return determinant;\n    }\n}\n\ntemplate <class T>\nT sparse_determinant(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    std::uint64_t\
    \ seed = 0x243f6a8885a308d3ULL\n) {\n    const std::uint64_t modulus = T::mod();\n\
    \    assert(modulus > 1);\n    internal::SparseDeterminantRandom random(seed);\n\
    \    auto random_nonzero = [&]() {\n        return T(1 + random() % (modulus -\
    \ 1));\n    };\n    return sparse_determinant_with_randomizer<T>(size, entries,\
    \ random_nonzero);\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATRIX_SPARSE_DETERMINANT_HPP\n#define M1UNE_MATRIX_SPARSE_DETERMINANT_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nstruct SparseMatrixEntry\
    \ {\n    int row;\n    int col;\n    T value;\n};\n\nnamespace internal {\n\n\
    struct SparseDeterminantRandom {\n    std::uint64_t state;\n\n    explicit SparseDeterminantRandom(std::uint64_t\
    \ seed) : state(seed) {}\n\n    std::uint64_t operator()() {\n        std::uint64_t\
    \ value = (state += 0x9e3779b97f4a7c15ULL);\n        value = (value ^ (value >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return value ^ (value >> 31);\n    }\n};\n\ntemplate <class T>\nstd::vector<T>\
    \ berlekamp_massey(const std::vector<T>& sequence) {\n    std::vector<T> recurrence(1,\
    \ T(1));\n    std::vector<T> previous(1, T(1));\n    int degree = 0;\n    int\
    \ shift = 1;\n    T previous_discrepancy = T(1);\n\n    for (int index = 0; index\
    \ < int(sequence.size()); index++) {\n        T discrepancy = sequence[index];\n\
    \        for (int i = 1; i <= degree; i++) {\n            discrepancy += recurrence[i]\
    \ * sequence[index - i];\n        }\n        if (discrepancy == T()) {\n     \
    \       shift++;\n            continue;\n        }\n\n        const T factor =\
    \ discrepancy / previous_discrepancy;\n        std::vector<T> old_recurrence =\
    \ recurrence;\n        if (int(recurrence.size()) < int(previous.size()) + shift)\
    \ {\n            recurrence.resize(previous.size() + std::size_t(shift), T());\n\
    \        }\n        for (int i = 0; i < int(previous.size()); i++) {\n       \
    \     recurrence[i + shift] -= factor * previous[i];\n        }\n\n        if\
    \ (2 * degree <= index) {\n            degree = index + 1 - degree;\n        \
    \    previous = std::move(old_recurrence);\n            previous_discrepancy =\
    \ discrepancy;\n            shift = 1;\n        } else {\n            shift++;\n\
    \        }\n    }\n    recurrence.resize(std::size_t(degree + 1));\n    return\
    \ recurrence;\n}\n\n}  // namespace internal\n\n// Randomized black-box determinant\
    \ over a finite field. random_nonzero must\n// return independent nonzero field\
    \ elements.\ntemplate <class T, class RandomValue>\nT sparse_determinant_with_randomizer(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    RandomValue\
    \ random_nonzero\n) {\n    assert(size >= 0);\n    for (const SparseMatrixEntry<T>&\
    \ entry : entries) {\n        assert(0 <= entry.row && entry.row < size);\n  \
    \      assert(0 <= entry.col && entry.col < size);\n    }\n    if (size == 0)\
    \ return T(1);\n\n    auto random_vector = [&]() {\n        std::vector<T> result(size);\n\
    \        for (T& value : result) {\n            value = random_nonzero();\n  \
    \          assert(value != T());\n        }\n        return result;\n    };\n\n\
    \    while (true) {\n        std::vector<T> diagonal = random_vector();\n    \
    \    std::vector<T> left = random_vector();\n        std::vector<T> state = random_vector();\n\
    \        std::vector<T> sequence(std::size_t(2 * size));\n\n        for (int step\
    \ = 0; step < 2 * size; step++) {\n            for (int i = 0; i < size; i++)\
    \ sequence[step] += left[i] * state[i];\n            for (int i = 0; i < size;\
    \ i++) state[i] *= diagonal[i];\n\n            std::vector<T> next(size);\n  \
    \          for (const SparseMatrixEntry<T>& entry : entries) {\n             \
    \   next[entry.row] += entry.value * state[entry.col];\n            }\n      \
    \      state = std::move(next);\n        }\n\n        std::vector<T> recurrence\
    \ = internal::berlekamp_massey(sequence);\n        if (recurrence.back() == T())\
    \ return T();\n        if (int(recurrence.size()) != size + 1) continue;\n\n \
    \       T determinant = recurrence.back();\n        if (size % 2 == 1) determinant\
    \ = T() - determinant;\n        for (const T& value : diagonal) determinant /=\
    \ value;\n        return determinant;\n    }\n}\n\ntemplate <class T>\nT sparse_determinant(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    std::uint64_t\
    \ seed = 0x243f6a8885a308d3ULL\n) {\n    const std::uint64_t modulus = T::mod();\n\
    \    assert(modulus > 1);\n    internal::SparseDeterminantRandom random(seed);\n\
    \    auto random_nonzero = [&]() {\n        return T(1 + random() % (modulus -\
    \ 1));\n    };\n    return sparse_determinant_with_randomizer<T>(size, entries,\
    \ random_nonzero);\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MATRIX_SPARSE_DETERMINANT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/matrix/sparse_determinant.hpp
  requiredBy:
  - math/matrix/all.hpp
  - math/all.hpp
  timestamp: '2026-07-14 02:42:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/matrix/matrix.test.cpp
  - verify/math/matrix/sparse_determinant.test.cpp
documentation_of: math/matrix/sparse_determinant.hpp
layout: document
title: Sparse Determinant
---

## Overview

`sparse_determinant` computes the determinant of a sparse square matrix over a
large finite field without materializing a dense matrix. It combines random
diagonal preconditioning, a scalar Wiedemann sequence, and Berlekamp--Massey.

The algorithm is Las Vegas: the returned value is exact, while the number of
preconditioning attempts is random and has constant expectation over a large
field.

## Requirements

`T` must be a field type supporting construction from integers, equality,
addition, subtraction, multiplication, and division.

The convenience overload also requires `T::mod()` and assumes the nonzero
residues modulo `T::mod()` are suitable random field elements. This includes
the repository's static and dynamic modular integer types when their modulus
is prime.

Entries use zero-based row and column indices. Duplicate positions are allowed
and their values are added. Explicit zero entries are allowed.

## API

```cpp
template <class T>
struct SparseMatrixEntry {
    int row;
    int col;
    T value;
};

template <class T, class RandomValue>
T sparse_determinant_with_randomizer(
    int size,
    const std::vector<SparseMatrixEntry<T>>& entries,
    RandomValue random_nonzero
);

template <class T>
T sparse_determinant(
    int size,
    const std::vector<SparseMatrixEntry<T>>& entries,
    std::uint64_t seed = 0x243f6a8885a308d3ULL
);
```

`random_nonzero()` must return independent nonzero values of `T`. The default
overload uses a deterministic SplitMix64 stream; supplying the same seed makes
the sequence of attempts reproducible.

| Function | Description | Complexity |
| --- | --- | --- |
| `sparse_determinant_with_randomizer(size, entries, random_nonzero)` | Computes the determinant using the supplied field sampler. | Expected $O(N(M+N))$ time, $O(N+M)$ memory |
| `sparse_determinant(size, entries, seed)` | Uses the built-in deterministic pseudorandom stream. | Expected $O(N(M+N))$ time, $O(N+M)$ memory |

Here $M$ is `entries.size()`. The determinant of the empty matrix is `T(1)`.
The functions do not mutate `entries`.

## Example

```cpp
#include "math/matrix/sparse_determinant.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

int main() {
    using mint = m1une::math::modint998244353;
    using Entry = m1une::matrix::SparseMatrixEntry<mint>;
    std::vector<Entry> entries;
    entries.push_back(Entry{0, 0, mint(2)});
    entries.push_back(Entry{1, 1, mint(3)});
    std::cout << m1une::matrix::sparse_determinant(2, entries) << "\n";  // 6
}
```
