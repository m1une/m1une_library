---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  - icon: ':heavy_check_mark:'
    path: math/divisor_convolution.hpp
    title: Divisor Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bitwise_and_convolution.test.cpp
    title: verify/math/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bitwise_convolution.test.cpp
    title: verify/math/bitwise_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/divisor_convolution.test.cpp
    title: verify/math/divisor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/lcm_convolution.test.cpp
    title: verify/math/lcm_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/zeta_mobius_transform.test.cpp
    title: verify/math/zeta_mobius_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace zeta_mobius_transform_detail {\n\ninline bool is_power_of_two(std::size_t\
    \ size) noexcept {\n    return size != 0 && (size & (size - 1)) == 0;\n}\n\ninline\
    \ std::vector<std::size_t> primes_up_to(std::size_t limit) {\n    std::vector<std::size_t>\
    \ primes;\n    std::vector<bool> is_prime(limit + 1, true);\n    if (!is_prime.empty())\
    \ is_prime[0] = false;\n    if (limit >= 1) is_prime[1] = false;\n    for (std::size_t\
    \ value = 2; value <= limit; ++value) {\n        if (!is_prime[value]) continue;\n\
    \        primes.emplace_back(value);\n        if (value > limit / value) continue;\n\
    \        for (\n            std::size_t multiple = value * value;\n          \
    \  multiple <= limit;\n            multiple += value\n        ) {\n          \
    \  is_prime[multiple] = false;\n        }\n    }\n    return primes;\n}\n\n} \
    \ // namespace zeta_mobius_transform_detail\n\ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>&\
    \ values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ += values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\n#define M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline\
    \ bool is_power_of_two(std::size_t size) noexcept {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MATH_ZETA_MOBIUS_TRANSFORM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/zeta_mobius_transform.hpp
  requiredBy:
  - math/bitwise_convolution.hpp
  - math/divisor_convolution.hpp
  - math/all.hpp
  timestamp: '2026-06-22 22:56:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/divisor_convolution.test.cpp
  - verify/math/zeta_mobius_transform.test.cpp
  - verify/math/lcm_convolution.test.cpp
  - verify/math/bitwise_and_convolution.test.cpp
  - verify/math/bitwise_convolution.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/zeta_mobius_transform.hpp
layout: document
title: Zeta and Mobius Transform
---

## Overview

This header provides zeta transforms and their Mobius inverses for subsets,
supersets, divisors, and multiples.

```cpp
#include "math/zeta_mobius_transform.hpp"
```

All functions operate in place.

The functions are templates over the array's element type:

```cpp
template <typename T>
void subset_zeta_transform(std::vector<T>& values);

template <typename T>
void subset_mobius_transform(std::vector<T>& values);

template <typename T>
void superset_zeta_transform(std::vector<T>& values);

template <typename T>
void superset_mobius_transform(std::vector<T>& values);

template <typename T>
void divisor_zeta_transform(std::vector<T>& values);

template <typename T>
void divisor_mobius_transform(std::vector<T>& values);

template <typename T>
void multiple_zeta_transform(std::vector<T>& values);

template <typename T>
void multiple_mobius_transform(std::vector<T>& values);
```

`T` may be an integer, floating-point type, modular integer, or another
user-defined type. Zeta transforms require `T` to support `operator+=`, while
Mobius transforms require `operator-=`. No multiplication or division is
performed. The vector is modified directly and no value is returned.

## Subset and Superset Transforms

Let the array length be $N = 2^n$. Index $S$ is interpreted as a subset of an
$n$-element set: element $i$ belongs to $S$ exactly when bit $i$ of the index is
set. For example, when $n = 3$, index `5 = 0b101` represents the subset
$\{0, 2\}$. The array length must be a nonzero power of two.

Suppose that `values[S]` initially stores $f(S)$. The subset zeta transform
replaces it with

$$
F(S) = \sum_{T \subseteq S} f(T),
$$

so the new value at `S` includes the old value at `S` and the old values at all
of its submasks. The subset Mobius transform performs the inverse operation: if
the input stores $F$, it recovers

$$
f(S) = \sum_{T \subseteq S} (-1)^{|S \setminus T|} F(T).
$$

In the other direction, the superset zeta transform replaces `values[S]` with

$$
G(S) = \sum_{T \supseteq S} f(T),
$$

which includes the old values at `S` and all of its supermasks. The superset
Mobius transform recovers $f$ from $G$:

$$
f(S) = \sum_{T \supseteq S} (-1)^{|T \setminus S|} G(T).
$$

| Function | Input at mask `S` | Output at mask `S` | Time |
| --- | --- | --- | --- |
| `subset_zeta_transform(values)` | $f(S)$ | $\sum_{T \subseteq S} f(T)$ | $O(N \log N)$ |
| `subset_mobius_transform(values)` | $F(S)$ | $\sum_{T \subseteq S} (-1)^{|S \setminus T|} F(T)$ | $O(N \log N)$ |
| `superset_zeta_transform(values)` | $f(S)$ | $\sum_{T \supseteq S} f(T)$ | $O(N \log N)$ |
| `superset_mobius_transform(values)` | $G(S)$ | $\sum_{T \supseteq S} (-1)^{|T \setminus S|} G(T)$ | $O(N \log N)$ |

For example, let the masks `0`, `1`, `2`, and `3` represent $\varnothing$,
$\{0\}$, $\{1\}$, and $\{0, 1\}$, respectively. Starting with
`values = [1, 2, 4, 8]`:

- the subset zeta transform produces `[1, 3, 5, 15]`;
- the superset zeta transform produces `[15, 10, 12, 8]`.

Applying the matching Mobius transform to either result restores
`[1, 2, 4, 8]`. Each transform uses $O(1)$ additional memory.

## Divisor and Multiple Transforms

An array of length `N + 1` represents values for the integers from `1` through
`N`; element `0` is left unchanged.

| Function | Result at index `x` |
| --- | --- |
| `divisor_zeta_transform(values)` | Sum of the original values at all divisors of `x`. |
| `divisor_mobius_transform(values)` | Inverse of the divisor zeta transform. |
| `multiple_zeta_transform(values)` | Sum of the original values at all multiples of `x` through `N`. |
| `multiple_mobius_transform(values)` | Inverse of the multiple zeta transform. |

More precisely, the divisor zeta transform computes

$$
F(x) = \sum_{d \mid x} f(d),
$$

and the multiple zeta transform computes

$$
F(x) = \sum_{\substack{m \leq N \\ x \mid m}} f(m).
$$

The corresponding Mobius transform recovers `f` from `F`. The element type
must support addition and subtraction.

### Complexity

Each transform first enumerates all primes through `N` with the sieve of
Eratosthenes, which takes $O(N \log \log N)$ time and $O(N)$ temporary memory.

For every prime $p$, the transform visits $\lfloor N/p \rfloor$ indices.
Therefore the number of additions or subtractions is

$$
\sum_{p \leq N} \left\lfloor \frac{N}{p} \right\rfloor
= O\left(N \sum_{p \leq N}\frac{1}{p}\right)
= O(N \log \log N).
$$

Thus each zeta or Mobius transform takes $O(N \log \log N)$ total time and
$O(N)$ temporary memory. In particular, this is not the
$O(N \log N)$ loop that visits every divisor or multiple directly; processing
only prime transitions is sufficient to represent the divisibility relation.

Empty arrays and arrays containing only indices `0` or `0, 1` are accepted and
remain unchanged.

## Example

```cpp
#include "math/zeta_mobius_transform.hpp"

#include <vector>

int main() {
    std::vector<long long> values{0, 1, 2, 3, 4, 5, 6};
    m1une::math::divisor_zeta_transform(values);
    // values[6] is now 1 + 2 + 3 + 6 = 12.

    m1une::math::divisor_mobius_transform(values);
    // values is restored to its original contents.
}
```
