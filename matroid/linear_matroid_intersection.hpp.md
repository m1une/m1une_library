---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/linear_matroid_intersection.test.cpp
    title: verify/matroid/linear_matroid_intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/linear_matroid_intersection.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <chrono>\n#include <cstdint>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace matroid {\n\nnamespace internal {\n\
    \ninline std::uint64_t linear_matroid_intersection_random() {\n    static std::uint64_t\
    \ state = std::uint64_t(\n        std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    state += 0x9e3779b97f4a7c15ULL;\n    std::uint64_t value = state;\n    value\
    \ = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n    value = (value ^ (value\
    \ >> 27)) * 0x94d049bb133111ebULL;\n    return value ^ (value >> 31);\n}\n\ntemplate\
    \ <class Field>\nint linear_matroid_intersection_matrix_rank(\n    std::vector<std::vector<Field>>\
    \ matrix) {\n    const int row_count = int(matrix.size());\n    const int column_count\
    \ = row_count == 0 ? 0 : int(matrix[0].size());\n    int rank = 0;\n    for (int\
    \ column = 0; column < column_count && rank < row_count; column++) {\n       \
    \ int pivot = rank;\n        while (pivot < row_count && matrix[pivot][column]\
    \ == Field(0)) pivot++;\n        if (pivot == row_count) continue;\n        std::swap(matrix[rank],\
    \ matrix[pivot]);\n\n        Field inverse = Field(1) / matrix[rank][column];\n\
    \        for (int j = column; j < column_count; j++) matrix[rank][j] *= inverse;\n\
    \        for (int row = rank + 1; row < row_count; row++) {\n            if (matrix[row][column]\
    \ == Field(0)) continue;\n            Field factor = matrix[row][column];\n  \
    \          for (int j = column; j < column_count; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[rank][j];\n            }\n        }\n        rank++;\n  \
    \  }\n    return rank;\n}\n\n}  // namespace internal\n\ntemplate <class Field>\n\
    int linear_matroid_intersection_size_with_weights(\n    const std::vector<std::vector<Field>>&\
    \ first_vectors,\n    const std::vector<std::vector<Field>>& second_vectors,\n\
    \    const std::vector<Field>& weights) {\n    const int ground_size = int(first_vectors.size());\n\
    \    assert(int(second_vectors.size()) == ground_size);\n    assert(int(weights.size())\
    \ == ground_size);\n    if (ground_size == 0) return 0;\n\n    const int first_dimension\
    \ = int(first_vectors[0].size());\n    const int second_dimension = int(second_vectors[0].size());\n\
    #ifndef NDEBUG\n    for (const auto& vector : first_vectors) {\n        assert(int(vector.size())\
    \ == first_dimension);\n    }\n    for (const auto& vector : second_vectors) {\n\
    \        assert(int(vector.size()) == second_dimension);\n    }\n#endif\n\n  \
    \  const bool transpose = second_dimension < first_dimension;\n    const int row_count\
    \ = transpose ? second_dimension : first_dimension;\n    const int column_count\
    \ = transpose ? first_dimension : second_dimension;\n    std::vector<std::vector<Field>>\
    \ matrix(\n        row_count, std::vector<Field>(column_count, Field(0)));\n\n\
    \    for (int element = 0; element < ground_size; element++) {\n        const\
    \ auto& row_vector =\n            transpose ? second_vectors[element] : first_vectors[element];\n\
    \        const auto& column_vector =\n            transpose ? first_vectors[element]\
    \ : second_vectors[element];\n        for (int row = 0; row < row_count; row++)\
    \ {\n            Field coefficient = weights[element] * row_vector[row];\n   \
    \         if (coefficient == Field(0)) continue;\n            for (int column\
    \ = 0; column < column_count; column++) {\n                matrix[row][column]\
    \ += coefficient * column_vector[column];\n            }\n        }\n    }\n \
    \   return internal::linear_matroid_intersection_matrix_rank(std::move(matrix));\n\
    }\n\ntemplate <class Field, class RandomNumberGenerator>\nint linear_matroid_intersection_size(\n\
    \    const std::vector<std::vector<Field>>& first_vectors,\n    const std::vector<std::vector<Field>>&\
    \ second_vectors,\n    RandomNumberGenerator& random) {\n    assert(first_vectors.size()\
    \ == second_vectors.size());\n    std::vector<Field> weights(first_vectors.size());\n\
    \    for (Field& weight : weights) weight = Field(random());\n    return linear_matroid_intersection_size_with_weights(\n\
    \        first_vectors, second_vectors, weights);\n}\n\ntemplate <class Field>\n\
    int linear_matroid_intersection_size(\n    const std::vector<std::vector<Field>>&\
    \ first_vectors,\n    const std::vector<std::vector<Field>>& second_vectors) {\n\
    \    assert(first_vectors.size() == second_vectors.size());\n    std::vector<Field>\
    \ weights(first_vectors.size());\n    for (Field& weight : weights) {\n      \
    \  weight = Field(internal::linear_matroid_intersection_random());\n    }\n  \
    \  return linear_matroid_intersection_size_with_weights(\n        first_vectors,\
    \ second_vectors, weights);\n}\n\n}  // namespace matroid\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP\n#define M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace matroid {\n\nnamespace internal\
    \ {\n\ninline std::uint64_t linear_matroid_intersection_random() {\n    static\
    \ std::uint64_t state = std::uint64_t(\n        std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    state += 0x9e3779b97f4a7c15ULL;\n    std::uint64_t value = state;\n    value\
    \ = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n    value = (value ^ (value\
    \ >> 27)) * 0x94d049bb133111ebULL;\n    return value ^ (value >> 31);\n}\n\ntemplate\
    \ <class Field>\nint linear_matroid_intersection_matrix_rank(\n    std::vector<std::vector<Field>>\
    \ matrix) {\n    const int row_count = int(matrix.size());\n    const int column_count\
    \ = row_count == 0 ? 0 : int(matrix[0].size());\n    int rank = 0;\n    for (int\
    \ column = 0; column < column_count && rank < row_count; column++) {\n       \
    \ int pivot = rank;\n        while (pivot < row_count && matrix[pivot][column]\
    \ == Field(0)) pivot++;\n        if (pivot == row_count) continue;\n        std::swap(matrix[rank],\
    \ matrix[pivot]);\n\n        Field inverse = Field(1) / matrix[rank][column];\n\
    \        for (int j = column; j < column_count; j++) matrix[rank][j] *= inverse;\n\
    \        for (int row = rank + 1; row < row_count; row++) {\n            if (matrix[row][column]\
    \ == Field(0)) continue;\n            Field factor = matrix[row][column];\n  \
    \          for (int j = column; j < column_count; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[rank][j];\n            }\n        }\n        rank++;\n  \
    \  }\n    return rank;\n}\n\n}  // namespace internal\n\ntemplate <class Field>\n\
    int linear_matroid_intersection_size_with_weights(\n    const std::vector<std::vector<Field>>&\
    \ first_vectors,\n    const std::vector<std::vector<Field>>& second_vectors,\n\
    \    const std::vector<Field>& weights) {\n    const int ground_size = int(first_vectors.size());\n\
    \    assert(int(second_vectors.size()) == ground_size);\n    assert(int(weights.size())\
    \ == ground_size);\n    if (ground_size == 0) return 0;\n\n    const int first_dimension\
    \ = int(first_vectors[0].size());\n    const int second_dimension = int(second_vectors[0].size());\n\
    #ifndef NDEBUG\n    for (const auto& vector : first_vectors) {\n        assert(int(vector.size())\
    \ == first_dimension);\n    }\n    for (const auto& vector : second_vectors) {\n\
    \        assert(int(vector.size()) == second_dimension);\n    }\n#endif\n\n  \
    \  const bool transpose = second_dimension < first_dimension;\n    const int row_count\
    \ = transpose ? second_dimension : first_dimension;\n    const int column_count\
    \ = transpose ? first_dimension : second_dimension;\n    std::vector<std::vector<Field>>\
    \ matrix(\n        row_count, std::vector<Field>(column_count, Field(0)));\n\n\
    \    for (int element = 0; element < ground_size; element++) {\n        const\
    \ auto& row_vector =\n            transpose ? second_vectors[element] : first_vectors[element];\n\
    \        const auto& column_vector =\n            transpose ? first_vectors[element]\
    \ : second_vectors[element];\n        for (int row = 0; row < row_count; row++)\
    \ {\n            Field coefficient = weights[element] * row_vector[row];\n   \
    \         if (coefficient == Field(0)) continue;\n            for (int column\
    \ = 0; column < column_count; column++) {\n                matrix[row][column]\
    \ += coefficient * column_vector[column];\n            }\n        }\n    }\n \
    \   return internal::linear_matroid_intersection_matrix_rank(std::move(matrix));\n\
    }\n\ntemplate <class Field, class RandomNumberGenerator>\nint linear_matroid_intersection_size(\n\
    \    const std::vector<std::vector<Field>>& first_vectors,\n    const std::vector<std::vector<Field>>&\
    \ second_vectors,\n    RandomNumberGenerator& random) {\n    assert(first_vectors.size()\
    \ == second_vectors.size());\n    std::vector<Field> weights(first_vectors.size());\n\
    \    for (Field& weight : weights) weight = Field(random());\n    return linear_matroid_intersection_size_with_weights(\n\
    \        first_vectors, second_vectors, weights);\n}\n\ntemplate <class Field>\n\
    int linear_matroid_intersection_size(\n    const std::vector<std::vector<Field>>&\
    \ first_vectors,\n    const std::vector<std::vector<Field>>& second_vectors) {\n\
    \    assert(first_vectors.size() == second_vectors.size());\n    std::vector<Field>\
    \ weights(first_vectors.size());\n    for (Field& weight : weights) {\n      \
    \  weight = Field(internal::linear_matroid_intersection_random());\n    }\n  \
    \  return linear_matroid_intersection_size_with_weights(\n        first_vectors,\
    \ second_vectors, weights);\n}\n\n}  // namespace matroid\n}  // namespace m1une\n\
    \n#endif  // M1UNE_MATROID_LINEAR_MATROID_INTERSECTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/linear_matroid_intersection.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-29 16:26:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/linear_matroid_intersection.test.cpp
  - verify/matroid/matroids.test.cpp
documentation_of: matroid/linear_matroid_intersection.hpp
layout: document
title: Linear Matroid Intersection
---

## Overview

`linear_matroid_intersection_size` returns the maximum size of a set that is
linearly independent in each of two vector families on the same ground set.
Unlike general matroid intersection, it computes only the cardinality, not a
maximizing set.

For vectors $a_e$ and $b_e$, the answer is the symbolic rank of

$$
\sum_e x_e a_e b_e^T.
$$

The algorithm substitutes random field values for $x_e$ and applies Gaussian
elimination. It never returns more than the correct answer, and can return less
with small probability. Over a field of size $q$, the failure probability of
one evaluation is at most $R/q$, where $R$ is the answer. Use a large prime
field such as `modint998244353`; small fields such as $\mathbb F_2$ are not
suitable.

Each outer vector is one ground-set element. Thus both arguments have size $N$,
while their inner vector dimensions may differ.

## Requirements

`Field` must be a field type supporting construction from integers, equality,
addition, subtraction, multiplication, and division. Every vector within one
family must have the same dimension.

For the generator overload, `random()` must return a value from which `Field`
can be constructed. Independent uniform field values give the stated error
bound.

## Interface

```cpp
template <class Field>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors);

template <class Field, class RandomNumberGenerator>
int linear_matroid_intersection_size(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    RandomNumberGenerator& random);

template <class Field>
int linear_matroid_intersection_size_with_weights(
    const std::vector<std::vector<Field>>& first_vectors,
    const std::vector<std::vector<Field>>& second_vectors,
    const std::vector<Field>& weights);
```

| Function | Description | Complexity |
| --- | --- | --- |
| `linear_matroid_intersection_size(first, second)` | Returns the maximum common independent-set size using an internally seeded random evaluation. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |
| `linear_matroid_intersection_size(first, second, random)` | Uses the supplied random-number generator. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |
| `linear_matroid_intersection_size_with_weights(first, second, weights)` | Uses the explicit values `weights[e]` for $x_e$. This is deterministic, but adversarial values need not preserve the symbolic rank. | $O(N(1+D_1D_2)+D_1D_2\min(D_1,D_2))$ |

Here $N$ is the ground-set size and $D_1,D_2$ are the two vector dimensions.
The randomized overloads use $O(N+D_1D_2)$ auxiliary memory, and the explicit
weight overload uses $O(D_1D_2)$. Inputs are not modified. `weights` must have
size $N$.

## Example

```cpp
#include "math/modint.hpp"
#include "matroid/linear_matroid_intersection.hpp"
#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<std::vector<mint>> first(3), second(3);
    first[0] = {1, 0};
    first[1] = {0, 1};
    first[2] = {1, 1};
    second[0] = {1, 0};
    second[1] = {1, 0};
    second[2] = {0, 1};

    int size =
        m1une::matroid::linear_matroid_intersection_size(first, second);
    // size == 2
}
```
