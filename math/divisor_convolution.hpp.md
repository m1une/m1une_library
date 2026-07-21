---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/divisor_convolution.test.cpp
    title: verify/math/divisor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/lcm_convolution.test.cpp
    title: verify/math/lcm_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/divisor_convolution.hpp\"\n\n\n\n#include <cstddef>\n\
    #include <vector>\n\n#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 7 \"math/zeta_mobius_transform.hpp\"\n\nnamespace m1une {\n\
    namespace math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline bool is_power_of_two(std::size_t\
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
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 8 \"math/divisor_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n\
    template <typename T>\nstd::vector<T> gcd_convolution(\n    std::vector<T> first,\n\
    \    std::vector<T> second\n) {\n    if (first.empty() || second.empty()) return\
    \ {};\n    const std::size_t size = first.size() > second.size()\n        ? first.size()\n\
    \        : second.size();\n    first.resize(size);\n    second.resize(size);\n\
    \    first[0] = T{};\n    second[0] = T{};\n\n    multiple_zeta_transform(first);\n\
    \    multiple_zeta_transform(second);\n    for (std::size_t index = 1; index <\
    \ size; ++index) {\n        first[index] *= second[index];\n    }\n    multiple_mobius_transform(first);\n\
    \    return first;\n}\n\ntemplate <typename T>\nstd::vector<T> lcm_convolution(\n\
    \    std::vector<T> first,\n    std::vector<T> second\n) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    const std::size_t size = first.size() > second.size()\n\
    \        ? first.size()\n        : second.size();\n    first.resize(size);\n \
    \   second.resize(size);\n    first[0] = T{};\n    second[0] = T{};\n\n    divisor_zeta_transform(first);\n\
    \    divisor_zeta_transform(second);\n    for (std::size_t index = 1; index <\
    \ size; ++index) {\n        first[index] *= second[index];\n    }\n    divisor_mobius_transform(first);\n\
    \    return first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_DIVISOR_CONVOLUTION_HPP\n#define M1UNE_MATH_DIVISOR_CONVOLUTION_HPP\
    \ 1\n\n#include <cstddef>\n#include <vector>\n\n#include \"zeta_mobius_transform.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nstd::vector<T>\
    \ gcd_convolution(\n    std::vector<T> first,\n    std::vector<T> second\n) {\n\
    \    if (first.empty() || second.empty()) return {};\n    const std::size_t size\
    \ = first.size() > second.size()\n        ? first.size()\n        : second.size();\n\
    \    first.resize(size);\n    second.resize(size);\n    first[0] = T{};\n    second[0]\
    \ = T{};\n\n    multiple_zeta_transform(first);\n    multiple_zeta_transform(second);\n\
    \    for (std::size_t index = 1; index < size; ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    multiple_mobius_transform(first);\n    return\
    \ first;\n}\n\ntemplate <typename T>\nstd::vector<T> lcm_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    const std::size_t size = first.size() > second.size()\n    \
    \    ? first.size()\n        : second.size();\n    first.resize(size);\n    second.resize(size);\n\
    \    first[0] = T{};\n    second[0] = T{};\n\n    divisor_zeta_transform(first);\n\
    \    divisor_zeta_transform(second);\n    for (std::size_t index = 1; index <\
    \ size; ++index) {\n        first[index] *= second[index];\n    }\n    divisor_mobius_transform(first);\n\
    \    return first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_MATH_DIVISOR_CONVOLUTION_HPP\n"
  dependsOn:
  - math/zeta_mobius_transform.hpp
  isVerificationFile: false
  path: math/divisor_convolution.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-21 23:59:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/lcm_convolution.test.cpp
  - verify/math/divisor_convolution.test.cpp
documentation_of: math/divisor_convolution.hpp
layout: document
title: Divisor Convolution
---

## Overview

`gcd_convolution` and `lcm_convolution` combine sequences indexed by positive
integers. For two sequences $a$ and $b$, they compute

$$
c_k = \sum_{\gcd(i,j)=k} a_i b_j
$$

or

$$
c_k = \sum_{\mathop{\rm lcm}(i,j)=k} a_i b_j,
$$

respectively.

Both operations use zeta and Mobius transforms on the divisibility poset. They
are useful when a direct quadratic loop over every pair of indices is too slow.

## Interface

All functions are in `m1une::math`.

| Function | Description | Complexity |
| --- | --- | --- |
| `template <typename T> std::vector<T> gcd_convolution(std::vector<T> first, std::vector<T> second)` | Returns the GCD convolution. | $O(N \log\log N)$ |
| `template <typename T> std::vector<T> lcm_convolution(std::vector<T> first, std::vector<T> second)` | Returns the LCM convolution. | $O(N \log\log N)$ |

Here, $N$ is one less than the larger input size. Both functions use $O(N)$
additional memory.

## Requirements and Behavior

* Index `0` is unused. The returned value at index `0` is value-initialized.
* If the input sizes differ, the shorter sequence is padded with zeros and the
  result has the larger size.
* If either input is empty, the result is empty.
* For LCM convolution, contributions whose LCM is outside the returned index
  range are discarded.
* `T` must be default-constructible and support `+=`, `-=`, and `*=`.

## Algorithm

GCD convolution applies the multiple zeta transform to both inputs, multiplies
the transformed values pointwise, and applies the multiple Mobius transform.
LCM convolution uses the divisor zeta and divisor Mobius transforms instead.

## Example

```cpp
#include "math/divisor_convolution.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> first(7);
    std::vector<long long> second(7);
    first[1] = 1;
    first[2] = 2;
    first[3] = 3;
    second[1] = 4;
    second[2] = 5;
    second[3] = 6;

    auto gcd_result = m1une::math::gcd_convolution(first, second);
    auto lcm_result = m1une::math::lcm_convolution(first, second);

    std::cout << gcd_result[1] << ' ' << gcd_result[2] << ' '
              << gcd_result[3] << '\n';
    std::cout << lcm_result[1] << ' ' << lcm_result[2] << ' '
              << lcm_result[3] << ' ' << lcm_result[6] << '\n';
}
```

Output:

```text
62 10 18
4 23 36 27
```
