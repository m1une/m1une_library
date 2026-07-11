---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_LINEAR_RECURRENCE_HPP\n#define M1UNE_FPS_LINEAR_RECURRENCE_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include \"\
    formal_power_series.hpp\"\n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class\
    \ Mint>\nMint coefficient_of_rational(FormalPowerSeries<Mint> numerator,\n   \
    \                          FormalPowerSeries<Mint> denominator, uint64_t index)\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n    assert(!denominator.empty()\
    \ && denominator[0] != Mint(0));\n\n    while (index > 0) {\n        Fps denominator_negative\
    \ = denominator;\n        for (int i = 1; i < int(denominator_negative.size());\
    \ i += 2) {\n            denominator_negative[i] = Mint(0) - denominator_negative[i];\n\
    \        }\n\n        Fps numerator_product = numerator * denominator_negative;\n\
    \        Fps denominator_product = denominator * denominator_negative;\n     \
    \   Fps next_numerator;\n        Fps next_denominator;\n        next_numerator.reserve((numerator_product.size()\
    \ + 1) / 2);\n        next_denominator.reserve((denominator_product.size() + 1)\
    \ / 2);\n        for (int i = int(index & 1); i < int(numerator_product.size());\
    \ i += 2) {\n            next_numerator.emplace_back(numerator_product[i]);\n\
    \        }\n        for (int i = 0; i < int(denominator_product.size()); i +=\
    \ 2) {\n            next_denominator.emplace_back(denominator_product[i]);\n \
    \       }\n        numerator = std::move(next_numerator);\n        denominator\
    \ = std::move(next_denominator);\n        index >>= 1;\n    }\n    return numerator.empty()\
    \ ? Mint(0) : numerator[0] / denominator[0];\n}\n\ntemplate <class Mint>\nMint\
    \ linear_recurrence_kth(const std::vector<Mint>& initial,\n                  \
    \         const std::vector<Mint>& recurrence, uint64_t index) {\n    using Fps\
    \ = FormalPowerSeries<Mint>;\n    assert(!initial.empty() && initial.size() ==\
    \ recurrence.size());\n    if (index < initial.size()) return initial[index];\n\
    \n    const int order = int(recurrence.size());\n    Fps denominator(order + 1);\n\
    \    denominator[0] = 1;\n    for (int i = 0; i < order; i++) denominator[i +\
    \ 1] = Mint(0) - recurrence[i];\n    Fps numerator = (Fps(initial) * denominator).pre(order);\n\
    \    return coefficient_of_rational(std::move(numerator), std::move(denominator),\
    \ index);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_LINEAR_RECURRENCE_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/linear_recurrence.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-11 19:26:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/linear_recurrence.hpp
layout: document
title: Linear Recurrence and Bostan-Mori
---

## Overview

Computes a distant coefficient of a rational generating function with the
Bostan-Mori algorithm. A convenience wrapper finds a term of a linear
recurrence without constructing all preceding terms.

## API

```cpp
template <class Mint>
Mint coefficient_of_rational(
    FormalPowerSeries<Mint> numerator,
    FormalPowerSeries<Mint> denominator,
    uint64_t index);
```

Returns the coefficient of $x^\mathrm{index}$ in
`numerator / denominator`. The denominator's constant term must be nonzero.

```cpp
template <class Mint>
Mint linear_recurrence_kth(
    const std::vector<Mint>& initial,
    const std::vector<Mint>& recurrence,
    uint64_t index);
```

For recurrence order `d`, the convention is:

```text
a[n] = recurrence[0] * a[n - 1]
     + recurrence[1] * a[n - 2]
     + ...
     + recurrence[d - 1] * a[n - d]
```

`initial` contains `a[0]` through `a[d - 1]`.

## Complexity

For recurrence order `d`, the running time is
$O(d \log d \log \mathrm{index})$ and the working memory is
$O(d)$ apart from convolution buffers.

## Example

```cpp
#include "math/fps/linear_recurrence.hpp"
#include "math/modint.hpp"

#include <iostream>
#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    std::vector<mint> initial = {0, 1};
    std::vector<mint> recurrence = {1, 1};
    mint fibonacci_100 = m1une::fps::linear_recurrence_kth(
        initial, recurrence, 100);
    std::cout << fibonacci_100 << "\n";
}
```
