---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
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
  - icon: ':question:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/bell_number.test.cpp
    title: verify/math/bell_number.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/partition_function.test.cpp
    title: verify/math/partition_function.test.cpp
  - icon: ':x:'
    path: verify/math/stirling_number_of_the_second_kind.test.cpp
    title: verify/math/stirling_number_of_the_second_kind.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_MATH_PARTITION_FUNCTION_HPP\n#define M1UNE_MATH_PARTITION_FUNCTION_HPP\
    \ 1\n\n#include \"fps/formal_power_series.hpp\"\n\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace math {\n\n// Returns p(0), p(1), ...,\
    \ p(maximum), where p(n) is the number of integer\n// partitions of n.\ntemplate\
    \ <class Mint>\nstd::vector<Mint> partition_function(int maximum) {\n    assert(maximum\
    \ >= 0);\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n    Fps denominator(maximum\
    \ + 1);\n    denominator[0] = 1;\n    for (long long k = 1;; k++) {\n        long\
    \ long first = k * (3 * k - 1) / 2;\n        long long second = k * (3 * k + 1)\
    \ / 2;\n        if (first > maximum) break;\n\n        Mint sign = (k & 1) ? Mint(-1)\
    \ : Mint(1);\n        denominator[int(first)] += sign;\n        if (second <=\
    \ maximum) denominator[int(second)] += sign;\n    }\n    return denominator.inv(maximum\
    \ + 1);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> partition_numbers(int maximum)\
    \ {\n    return partition_function<Mint>(maximum);\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MATH_PARTITION_FUNCTION_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/partition_function.hpp
  requiredBy:
  - math/combinatorial_sequences.hpp
  - math/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/bell_number.test.cpp
  - verify/math/partition_function.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/stirling_number_of_the_second_kind.test.cpp
documentation_of: math/partition_function.hpp
layout: document
title: Partition Function
---

## Overview

The partition function $p(n)$ counts the ways to write the nonnegative integer
$n$ as a sum of positive integers when order does not matter. By convention,
$p(0)=1$.

For example, $p(5)=7$:

```text
5
4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

Its generating function is

$$
\sum_{n=0}^{\infty}p(n)x^n
=
\prod_{k=1}^{\infty}\frac{1}{1-x^k}.
$$

Euler's pentagonal number theorem makes the denominator sparse. The
implementation constructs that denominator through degree `maximum`, then
inverts it as a formal power series.

## Requirements

`Mint` must satisfy the requirements of `FormalPowerSeries`, including modular
addition, multiplication, and inversion. The usual choice is
`m1une::math::modint998244353`.

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `std::vector<Mint> partition_function<Mint>(int maximum)` | $O(N\log N)$ time and $O(N)$ memory | Returns `p(0)` through `p(maximum)`. |
| `std::vector<Mint> partition_numbers<Mint>(int maximum)` | $O(N\log N)$ time and $O(N)$ memory | Compatibility alias of `partition_function`. |

`maximum` must be nonnegative. The returned vector has size `maximum + 1`.

## Example

```cpp
#include "math/modint.hpp"
#include "math/partition_function.hpp"

#include <iostream>

int main() {
    using Mint = m1une::math::modint998244353;
    std::vector<Mint> values =
        m1une::math::partition_function<Mint>(10);

    std::cout << values[5] << "\n"; // 7
}
```
