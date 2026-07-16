---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/subset_convolution.hpp
    title: Subset Convolution
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/set_power_series_exp.test.cpp
    title: verify/math/set_power_series_exp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/set_power_series_log.test.cpp
    title: verify/math/set_power_series_log.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/set_power_series.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <bit>\n#include <cassert>\n#include <cstddef>\n#include <iterator>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"math/subset_convolution.hpp\"\
    \n\n\n\n#line 10 \"math/subset_convolution.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <typename T>\nstd::vector<T> subset_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    assert(first.size() == second.size());\n\
    \    if (first.empty()) return {};\n    assert((first.size() & (first.size() -\
    \ 1)) == 0);\n\n    const std::size_t size = first.size();\n    std::size_t bit_count\
    \ = 0;\n    while ((std::size_t(1) << bit_count) < size) ++bit_count;\n    const\
    \ std::size_t rank_count = bit_count + 1;\n\n    std::vector<T> first_ranked(size\
    \ * rank_count);\n    std::vector<T> second_ranked(size * rank_count);\n    for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n        const std::size_t rank\
    \ = std::popcount(mask);\n        first_ranked[mask * rank_count + rank] = std::move(first[mask]);\n\
    \        second_ranked[mask * rank_count + rank] = std::move(second[mask]);\n\
    \    }\n\n    for (std::size_t bit = 1; bit < size; bit <<= 1) {\n        for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n            if ((mask & bit)\
    \ == 0) continue;\n            const std::size_t destination = mask * rank_count;\n\
    \            const std::size_t source = (mask ^ bit) * rank_count;\n         \
    \   for (std::size_t rank = 0; rank < rank_count; ++rank) {\n                first_ranked[destination\
    \ + rank] +=\n                    first_ranked[source + rank];\n             \
    \   second_ranked[destination + rank] +=\n                    second_ranked[source\
    \ + rank];\n            }\n        }\n    }\n\n    std::vector<T> product(rank_count);\n\
    \    for (std::size_t mask = 0; mask < size; ++mask) {\n        for (T& value\
    \ : product) value = T{};\n        const std::size_t offset = mask * rank_count;\n\
    \        const std::size_t rank_limit = std::popcount(mask);\n        for (std::size_t\
    \ left = 0; left <= rank_limit; ++left) {\n            const std::size_t right_limit\
    \ =\n                std::min(rank_limit, bit_count - left);\n            for\
    \ (std::size_t right = 0; right <= right_limit; ++right) {\n                product[left\
    \ + right] +=\n                    first_ranked[offset + left] *\n           \
    \         second_ranked[offset + right];\n            }\n        }\n        for\
    \ (std::size_t rank = 0; rank < rank_count; ++rank) {\n            first_ranked[offset\
    \ + rank] = std::move(product[rank]);\n        }\n    }\n\n    for (std::size_t\
    \ bit = 1; bit < size; bit <<= 1) {\n        for (std::size_t mask = 0; mask <\
    \ size; ++mask) {\n            if ((mask & bit) == 0) continue;\n            const\
    \ std::size_t destination = mask * rank_count;\n            const std::size_t\
    \ source = (mask ^ bit) * rank_count;\n            for (std::size_t rank = 0;\
    \ rank < rank_count; ++rank) {\n                first_ranked[destination + rank]\
    \ -=\n                    first_ranked[source + rank];\n            }\n      \
    \  }\n    }\n\n    std::vector<T> result(size);\n    for (std::size_t mask = 0;\
    \ mask < size; ++mask) {\n        result[mask] = std::move(\n            first_ranked[mask\
    \ * rank_count + std::popcount(mask)]\n        );\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 13 \"math/set_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace set_power_series_detail {\n\
    \ninline bool is_power_of_two(std::size_t size) {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ntemplate <class T>\nstd::vector<T> divide(\n    const\
    \ std::vector<T>& numerator,\n    const std::vector<T>& denominator\n) {\n   \
    \ assert(numerator.size() == denominator.size());\n    assert(is_power_of_two(numerator.size()));\n\
    \    assert(denominator[0] != T{});\n\n    const std::size_t size = numerator.size();\n\
    \    const int bit_count = std::countr_zero(size);\n    const std::size_t rank_count\
    \ = std::size_t(bit_count) + 1;\n    std::vector<T> denominator_ranked(size *\
    \ rank_count);\n    std::vector<T> quotient_ranked(size * rank_count);\n\n   \
    \ for (std::size_t mask = 0; mask < size; mask++) {\n        std::size_t rank\
    \ = std::popcount(mask);\n        denominator_ranked[mask * rank_count + rank]\
    \ = denominator[mask];\n    }\n    for (std::size_t bit = 1; bit < size; bit <<=\
    \ 1) {\n        for (std::size_t mask = 0; mask < size; mask++) {\n          \
    \  if ((mask & bit) == 0) continue;\n            std::size_t source_mask = mask\
    \ ^ bit;\n            std::size_t source = source_mask * rank_count;\n       \
    \     std::size_t destination = mask * rank_count;\n            std::size_t rank_limit\
    \ = std::popcount(source_mask);\n            for (std::size_t rank = 0; rank <=\
    \ rank_limit; rank++) {\n                denominator_ranked[destination + rank]\
    \ +=\n                    denominator_ranked[source + rank];\n            }\n\
    \        }\n    }\n\n    const T inverse_constant = T(1) / denominator[0];\n \
    \   std::vector<T> transformed_product(size);\n    std::vector<T> quotient(size);\n\
    \    for (int rank = 0; rank <= bit_count; rank++) {\n        std::fill(\n   \
    \         transformed_product.begin(),\n            transformed_product.end(),\n\
    \            T{}\n        );\n        for (std::size_t mask = 0; mask < size;\
    \ mask++) {\n            std::size_t offset = mask * rank_count;\n           \
    \ for (int left_rank = 0; left_rank <= rank; left_rank++) {\n                transformed_product[mask]\
    \ +=\n                    denominator_ranked[offset + left_rank] *\n         \
    \           quotient_ranked[offset + rank - left_rank];\n            }\n     \
    \   }\n\n        for (std::size_t bit = 1; bit < size; bit <<= 1) {\n        \
    \    for (std::size_t mask = 0; mask < size; mask++) {\n                if (mask\
    \ & bit) {\n                    transformed_product[mask] -=\n               \
    \         transformed_product[mask ^ bit];\n                }\n            }\n\
    \        }\n\n        for (std::size_t mask = 0; mask < size; mask++) {\n    \
    \        if (int(std::popcount(mask)) != rank) continue;\n            quotient[mask]\
    \ =\n                (numerator[mask] - transformed_product[mask]) *\n       \
    \         inverse_constant;\n            quotient_ranked[mask * rank_count + rank]\
    \ = quotient[mask];\n        }\n\n        for (std::size_t bit = 1; bit < size;\
    \ bit <<= 1) {\n            for (std::size_t mask = 0; mask < size; mask++) {\n\
    \                if (mask & bit) {\n                    quotient_ranked[mask *\
    \ rank_count + rank] +=\n                        quotient_ranked[(mask ^ bit)\
    \ * rank_count + rank];\n                }\n            }\n        }\n    }\n\
    \    return quotient;\n}\n\ntemplate <class T>\nstd::vector<T> normalized_power(std::vector<T>\
    \ series, T exponent) {\n    assert(is_power_of_two(series.size()));\n    assert(series[0]\
    \ == T(1));\n    std::vector<T> logarithm(series.size());\n    logarithm[0] =\
    \ T{};\n    for (std::size_t half = 1; half < series.size(); half <<= 1) {\n \
    \       std::vector<T> low(series.begin(), series.begin() + half);\n        std::vector<T>\
    \ high(\n            series.begin() + half,\n            series.begin() + 2 *\
    \ half\n        );\n        std::vector<T> next = divide(high, low);\n       \
    \ std::move(next.begin(), next.end(), logarithm.begin() + half);\n    }\n    for\
    \ (T& value : logarithm) value *= exponent;\n\n    std::vector<T> result(1, T(1));\n\
    \    result.reserve(series.size());\n    for (std::size_t half = 1; half < series.size();\
    \ half <<= 1) {\n        std::vector<T> high(\n            logarithm.begin() +\
    \ half,\n            logarithm.begin() + 2 * half\n        );\n        std::vector<T>\
    \ next = subset_convolution(std::move(high), result);\n        result.insert(\n\
    \            result.end(),\n            std::make_move_iterator(next.begin()),\n\
    \            std::make_move_iterator(next.end())\n        );\n    }\n    return\
    \ result;\n}\n\n}  // namespace set_power_series_detail\n\n// Returns numerator\
    \ / denominator under subset convolution.\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_divide(\n    const std::vector<T>& numerator,\n    const std::vector<T>&\
    \ denominator\n) {\n    return set_power_series_detail::divide(numerator, denominator);\n\
    }\n\ntemplate <class T>\nstd::vector<T> set_power_series_inverse(const std::vector<T>&\
    \ series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    std::vector<T> identity(series.size());\n    identity[0] = T(1);\n    return\
    \ set_power_series_divide(identity, series);\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_exp(const std::vector<T>& series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    assert(series[0] == T{});\n    std::vector<T> result(1, T(1));\n    result.reserve(series.size());\n\
    \    for (std::size_t half = 1; half < series.size(); half <<= 1) {\n        std::vector<T>\
    \ high(\n            series.begin() + half,\n            series.begin() + 2 *\
    \ half\n        );\n        std::vector<T> next = subset_convolution(std::move(high),\
    \ result);\n        result.insert(\n            result.end(),\n            std::make_move_iterator(next.begin()),\n\
    \            std::make_move_iterator(next.end())\n        );\n    }\n    return\
    \ result;\n}\n\ntemplate <class T>\nstd::vector<T> set_power_series_log(const\
    \ std::vector<T>& series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    assert(series[0] == T(1));\n    std::vector<T> result(series.size());\n \
    \   for (std::size_t half = 1; half < series.size(); half <<= 1) {\n        std::vector<T>\
    \ low(series.begin(), series.begin() + half);\n        std::vector<T> high(\n\
    \            series.begin() + half,\n            series.begin() + 2 * half\n \
    \       );\n        std::vector<T> next = set_power_series_divide(high, low);\n\
    \        std::move(next.begin(), next.end(), result.begin() + half);\n    }\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<T> set_power_series_pow(\n\
    \    const std::vector<T>& series,\n    long long exponent\n) {\n    return set_power_series_detail::normalized_power(\n\
    \        series,\n        T(exponent)\n    );\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_sqrt(const std::vector<T>& series) {\n    return set_power_series_detail::normalized_power(\n\
    \        series,\n        T(1) / T(2)\n    );\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_SET_POWER_SERIES_HPP\n#define M1UNE_MATH_SET_POWER_SERIES_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <iterator>\n#include <utility>\n#include <vector>\n\n#include \"subset_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace set_power_series_detail {\n\
    \ninline bool is_power_of_two(std::size_t size) {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ntemplate <class T>\nstd::vector<T> divide(\n    const\
    \ std::vector<T>& numerator,\n    const std::vector<T>& denominator\n) {\n   \
    \ assert(numerator.size() == denominator.size());\n    assert(is_power_of_two(numerator.size()));\n\
    \    assert(denominator[0] != T{});\n\n    const std::size_t size = numerator.size();\n\
    \    const int bit_count = std::countr_zero(size);\n    const std::size_t rank_count\
    \ = std::size_t(bit_count) + 1;\n    std::vector<T> denominator_ranked(size *\
    \ rank_count);\n    std::vector<T> quotient_ranked(size * rank_count);\n\n   \
    \ for (std::size_t mask = 0; mask < size; mask++) {\n        std::size_t rank\
    \ = std::popcount(mask);\n        denominator_ranked[mask * rank_count + rank]\
    \ = denominator[mask];\n    }\n    for (std::size_t bit = 1; bit < size; bit <<=\
    \ 1) {\n        for (std::size_t mask = 0; mask < size; mask++) {\n          \
    \  if ((mask & bit) == 0) continue;\n            std::size_t source_mask = mask\
    \ ^ bit;\n            std::size_t source = source_mask * rank_count;\n       \
    \     std::size_t destination = mask * rank_count;\n            std::size_t rank_limit\
    \ = std::popcount(source_mask);\n            for (std::size_t rank = 0; rank <=\
    \ rank_limit; rank++) {\n                denominator_ranked[destination + rank]\
    \ +=\n                    denominator_ranked[source + rank];\n            }\n\
    \        }\n    }\n\n    const T inverse_constant = T(1) / denominator[0];\n \
    \   std::vector<T> transformed_product(size);\n    std::vector<T> quotient(size);\n\
    \    for (int rank = 0; rank <= bit_count; rank++) {\n        std::fill(\n   \
    \         transformed_product.begin(),\n            transformed_product.end(),\n\
    \            T{}\n        );\n        for (std::size_t mask = 0; mask < size;\
    \ mask++) {\n            std::size_t offset = mask * rank_count;\n           \
    \ for (int left_rank = 0; left_rank <= rank; left_rank++) {\n                transformed_product[mask]\
    \ +=\n                    denominator_ranked[offset + left_rank] *\n         \
    \           quotient_ranked[offset + rank - left_rank];\n            }\n     \
    \   }\n\n        for (std::size_t bit = 1; bit < size; bit <<= 1) {\n        \
    \    for (std::size_t mask = 0; mask < size; mask++) {\n                if (mask\
    \ & bit) {\n                    transformed_product[mask] -=\n               \
    \         transformed_product[mask ^ bit];\n                }\n            }\n\
    \        }\n\n        for (std::size_t mask = 0; mask < size; mask++) {\n    \
    \        if (int(std::popcount(mask)) != rank) continue;\n            quotient[mask]\
    \ =\n                (numerator[mask] - transformed_product[mask]) *\n       \
    \         inverse_constant;\n            quotient_ranked[mask * rank_count + rank]\
    \ = quotient[mask];\n        }\n\n        for (std::size_t bit = 1; bit < size;\
    \ bit <<= 1) {\n            for (std::size_t mask = 0; mask < size; mask++) {\n\
    \                if (mask & bit) {\n                    quotient_ranked[mask *\
    \ rank_count + rank] +=\n                        quotient_ranked[(mask ^ bit)\
    \ * rank_count + rank];\n                }\n            }\n        }\n    }\n\
    \    return quotient;\n}\n\ntemplate <class T>\nstd::vector<T> normalized_power(std::vector<T>\
    \ series, T exponent) {\n    assert(is_power_of_two(series.size()));\n    assert(series[0]\
    \ == T(1));\n    std::vector<T> logarithm(series.size());\n    logarithm[0] =\
    \ T{};\n    for (std::size_t half = 1; half < series.size(); half <<= 1) {\n \
    \       std::vector<T> low(series.begin(), series.begin() + half);\n        std::vector<T>\
    \ high(\n            series.begin() + half,\n            series.begin() + 2 *\
    \ half\n        );\n        std::vector<T> next = divide(high, low);\n       \
    \ std::move(next.begin(), next.end(), logarithm.begin() + half);\n    }\n    for\
    \ (T& value : logarithm) value *= exponent;\n\n    std::vector<T> result(1, T(1));\n\
    \    result.reserve(series.size());\n    for (std::size_t half = 1; half < series.size();\
    \ half <<= 1) {\n        std::vector<T> high(\n            logarithm.begin() +\
    \ half,\n            logarithm.begin() + 2 * half\n        );\n        std::vector<T>\
    \ next = subset_convolution(std::move(high), result);\n        result.insert(\n\
    \            result.end(),\n            std::make_move_iterator(next.begin()),\n\
    \            std::make_move_iterator(next.end())\n        );\n    }\n    return\
    \ result;\n}\n\n}  // namespace set_power_series_detail\n\n// Returns numerator\
    \ / denominator under subset convolution.\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_divide(\n    const std::vector<T>& numerator,\n    const std::vector<T>&\
    \ denominator\n) {\n    return set_power_series_detail::divide(numerator, denominator);\n\
    }\n\ntemplate <class T>\nstd::vector<T> set_power_series_inverse(const std::vector<T>&\
    \ series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    std::vector<T> identity(series.size());\n    identity[0] = T(1);\n    return\
    \ set_power_series_divide(identity, series);\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_exp(const std::vector<T>& series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    assert(series[0] == T{});\n    std::vector<T> result(1, T(1));\n    result.reserve(series.size());\n\
    \    for (std::size_t half = 1; half < series.size(); half <<= 1) {\n        std::vector<T>\
    \ high(\n            series.begin() + half,\n            series.begin() + 2 *\
    \ half\n        );\n        std::vector<T> next = subset_convolution(std::move(high),\
    \ result);\n        result.insert(\n            result.end(),\n            std::make_move_iterator(next.begin()),\n\
    \            std::make_move_iterator(next.end())\n        );\n    }\n    return\
    \ result;\n}\n\ntemplate <class T>\nstd::vector<T> set_power_series_log(const\
    \ std::vector<T>& series) {\n    assert(set_power_series_detail::is_power_of_two(series.size()));\n\
    \    assert(series[0] == T(1));\n    std::vector<T> result(series.size());\n \
    \   for (std::size_t half = 1; half < series.size(); half <<= 1) {\n        std::vector<T>\
    \ low(series.begin(), series.begin() + half);\n        std::vector<T> high(\n\
    \            series.begin() + half,\n            series.begin() + 2 * half\n \
    \       );\n        std::vector<T> next = set_power_series_divide(high, low);\n\
    \        std::move(next.begin(), next.end(), result.begin() + half);\n    }\n\
    \    return result;\n}\n\ntemplate <class T>\nstd::vector<T> set_power_series_pow(\n\
    \    const std::vector<T>& series,\n    long long exponent\n) {\n    return set_power_series_detail::normalized_power(\n\
    \        series,\n        T(exponent)\n    );\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ set_power_series_sqrt(const std::vector<T>& series) {\n    return set_power_series_detail::normalized_power(\n\
    \        series,\n        T(1) / T(2)\n    );\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_MATH_SET_POWER_SERIES_HPP\n"
  dependsOn:
  - math/subset_convolution.hpp
  isVerificationFile: false
  path: math/set_power_series.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-16 17:56:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/set_power_series_log.test.cpp
  - verify/math/set_power_series_exp.test.cpp
documentation_of: math/set_power_series.hpp
layout: document
title: Set Power Series
---

## Overview

A set power series stores one coefficient for every subset of an `n`-element
ground set. Subsets are represented by masks, so a series has exactly `2^n`
coefficients. Multiplication is subset convolution:

$$
(fg)[S] = \sum_{T \subseteq S} f[T]g[S \setminus T].
$$

This header provides division, inverse, exponential, logarithm, integer power,
and normalized square root under that multiplication. The exponential and
logarithm are mutually inverse on series with constant coefficients zero and
one, respectively.

## Requirements and Behavior

Every input vector must be nonempty and have power-of-two size. Invalid sizes
assert.

`T` must provide ordinary construction, equality, addition, subtraction, and
multiplication. Division and inverse additionally require division in `T` and a
nonzero denominator constant. `set_power_series_sqrt` requires that `2` be
invertible.

The normalized operations have these constant-term requirements:

* `set_power_series_exp(f)` requires `f[0] == 0`.
* `set_power_series_log(f)`, `set_power_series_pow(f, k)`, and
  `set_power_series_sqrt(f)` require `f[0] == 1`.

`set_power_series_sqrt` returns the square root whose constant coefficient is
one. `set_power_series_pow` accepts negative exponents because a series with
constant coefficient one is invertible.

## Interface

| Function | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Division | `template <class T> std::vector<T> set_power_series_divide(const std::vector<T>& numerator, const std::vector<T>& denominator)` | Returns `numerator / denominator` under subset convolution. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Inverse | `template <class T> std::vector<T> set_power_series_inverse(const std::vector<T>& series)` | Returns the subset-convolution inverse. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Exponential | `template <class T> std::vector<T> set_power_series_exp(const std::vector<T>& series)` | Returns the normalized set-series exponential. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Logarithm | `template <class T> std::vector<T> set_power_series_log(const std::vector<T>& series)` | Returns the normalized set-series logarithm. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Integer power | `template <class T> std::vector<T> set_power_series_pow(const std::vector<T>& series, long long exponent)` | Returns the integer power under subset convolution. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |
| Square root | `template <class T> std::vector<T> set_power_series_sqrt(const std::vector<T>& series)` | Returns the normalized square root. | $O(n^2 2^n)$ time, $O(n2^n)$ memory |

The implementation uses ranked subset-zeta transforms for division. The
exponential builds one variable at a time, and the logarithm solves the inverse
subset-convolution problem at each level. Geometrically increasing levels keep
the total bound at $O(n^2 2^n)$.

## Example

```cpp
#include "math/modint.hpp"
#include "math/set_power_series.hpp"

#include <cassert>
#include <vector>

int main() {
    using Mint = m1une::math::modint998244353;

    std::vector<Mint> logarithm(8);
    logarithm[1] = 2;
    logarithm[2] = 3;
    logarithm[4] = 5;

    auto series = m1une::math::set_power_series_exp(logarithm);
    auto restored = m1une::math::set_power_series_log(series);
    assert(restored == logarithm);
}
```
