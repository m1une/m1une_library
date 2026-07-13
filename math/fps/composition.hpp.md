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
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/composition.test.cpp
    title: verify/math/fps/composition.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_COMPOSITION_HPP\n#define M1UNE_FPS_COMPOSITION_HPP 1\n\n\
    #include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n\
    #include <utility>\n#include <vector>\n\n#include \"formal_power_series.hpp\"\n\
    \nnamespace m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nusing CompositionMatrix = std::vector<std::vector<Mint>>;\n\ntemplate\
    \ <class Mint>\nCompositionMatrix<Mint> composition_convolution_2d(const CompositionMatrix<Mint>&\
    \ lhs,\n                                                   const CompositionMatrix<Mint>&\
    \ rhs) {\n    const int lhs_height = int(lhs.size());\n    const int rhs_height\
    \ = int(rhs.size());\n    const int lhs_width = int(lhs[0].size());\n    const\
    \ int rhs_width = int(rhs[0].size());\n    const int height = lhs_height + rhs_height\
    \ - 1;\n    const int width = lhs_width + rhs_width - 1;\n\n    std::vector<Mint>\
    \ flattened_lhs(std::size_t(lhs_height) * width);\n    std::vector<Mint> flattened_rhs(std::size_t(rhs_height)\
    \ * width);\n    for (int i = 0; i < lhs_height; i++) {\n        std::copy(lhs[i].begin(),\
    \ lhs[i].end(),\n                  flattened_lhs.begin() + std::size_t(i) * width);\n\
    \    }\n    for (int i = 0; i < rhs_height; i++) {\n        std::copy(rhs[i].begin(),\
    \ rhs[i].end(),\n                  flattened_rhs.begin() + std::size_t(i) * width);\n\
    \    }\n\n    std::vector<Mint> flattened_result = convolution(flattened_lhs,\
    \ flattened_rhs);\n    CompositionMatrix<Mint> result(height, std::vector<Mint>(width));\n\
    \    for (int i = 0; i < height; i++) {\n        std::copy_n(flattened_result.begin()\
    \ + std::size_t(i) * width, width,\n                    result[i].begin());\n\
    \    }\n    return result;\n}\n\n// result[i] = sum_j kernel[j] * values[i + j]\n\
    template <class Mint>\nstd::vector<Mint> composition_middle_product(const std::vector<Mint>&\
    \ values,\n                                             const std::vector<Mint>&\
    \ kernel) {\n    assert(values.size() >= kernel.size() && !kernel.empty());\n\
    \    const int kernel_size = int(kernel.size());\n    const int result_size =\
    \ int(values.size()) - kernel_size + 1;\n    if (std::min(kernel_size, result_size)\
    \ <= 32) {\n        std::vector<Mint> result(result_size);\n        for (int i\
    \ = 0; i < result_size; i++) {\n            for (int j = 0; j < kernel_size; j++)\
    \ result[i] += kernel[j] * values[i + j];\n        }\n        return result;\n\
    \    }\n\n    int transform_size = 1;\n    while ((transform_size << 1) <= int(values.size())\
    \ * 2 - 1) transform_size <<= 1;\n    if ((Mint::mod() - 1) % uint32_t(transform_size)\
    \ == 0) {\n        std::vector<Mint> transformed_values(transform_size);\n   \
    \     std::vector<Mint> transformed_kernel(transform_size);\n        std::copy(values.begin(),\
    \ values.end(), transformed_values.begin());\n        std::reverse_copy(kernel.begin(),\
    \ kernel.end(), transformed_kernel.begin());\n        ntt(transformed_values,\
    \ false);\n        ntt(transformed_kernel, false);\n        for (int i = 0; i\
    \ < transform_size; i++) transformed_values[i] *= transformed_kernel[i];\n   \
    \     ntt(transformed_values, true);\n        return std::vector<Mint>(transformed_values.begin()\
    \ + kernel_size - 1,\n                                 transformed_values.begin()\
    \ + int(values.size()));\n    }\n\n    std::vector<Mint> reversed_kernel(kernel.rbegin(),\
    \ kernel.rend());\n    std::vector<Mint> product = convolution(values, reversed_kernel);\n\
    \    return std::vector<Mint>(product.begin() + kernel_size - 1,\n           \
    \                  product.begin() + int(values.size()));\n}\n\n}  // namespace\
    \ internal\n\n// Returns outer(inner(x)) modulo x^degree. Formal composition requires\
    \ inner(0) = 0.\ntemplate <class Mint>\nFormalPowerSeries<Mint> compose(const\
    \ FormalPowerSeries<Mint>& outer,\n                                const FormalPowerSeries<Mint>&\
    \ inner, int degree = -1) {\n    using Matrix = internal::CompositionMatrix<Mint>;\n\
    \    if (degree < 0) degree = int(outer.size());\n    assert(degree >= 0);\n \
    \   if (degree == 0) return {};\n    assert(inner.empty() || inner[0] == Mint(0));\n\
    \n    FormalPowerSeries<Mint> coefficients = outer.pre(degree);\n    FormalPowerSeries<Mint>\
    \ argument = inner.pre(degree);\n\n    auto transpose_power_projection = [&](auto&&\
    \ self, Matrix denominator) -> Matrix {\n        const int x_degree = int(denominator.size())\
    \ - 1;\n        const int y_degree = int(denominator[0].size()) - 1;\n       \
    \ if (x_degree == 0) {\n            Matrix result(1, std::vector<Mint>(y_degree\
    \ + 1));\n            std::copy(coefficients.begin(), coefficients.end(), result[0].begin());\n\
    \            return result;\n        }\n\n        Matrix conjugate = denominator;\n\
    \        for (int i = 1; i <= x_degree; i += 2) {\n            for (Mint& value\
    \ : conjugate[i]) value = Mint(0) - value;\n        }\n        Matrix reduced\
    \ = internal::composition_convolution_2d(denominator, conjugate);\n        for\
    \ (int i = 1; i <= x_degree / 2; i++) reduced[i] = std::move(reduced[i << 1]);\n\
    \        reduced.resize(x_degree / 2 + 1);\n        Matrix().swap(denominator);\n\
    \n        Matrix projected = self(self, std::move(reduced));\n        const int\
    \ block_width = 2 * y_degree + 1;\n        std::vector<Mint> expanded(std::size_t(2)\
    \ * (x_degree + 1) * block_width - 1);\n        for (int i = 0; i < int(projected.size());\
    \ i++) {\n            for (int j = 0; j < int(projected[i].size()); j++) {\n \
    \               const int row = 2 * i + (x_degree & 1);\n                expanded[std::size_t(row)\
    \ * block_width + j] = projected[i][j];\n            }\n        }\n\n        std::vector<Mint>\
    \ flattened_conjugate(std::size_t(x_degree + 1) * block_width);\n        for (int\
    \ i = 0; i <= x_degree; i++) {\n            std::copy(conjugate[i].begin(), conjugate[i].end(),\n\
    \                      flattened_conjugate.begin() + std::size_t(i) * block_width);\n\
    \        }\n        std::vector<Mint> middle =\n            internal::composition_middle_product(expanded,\
    \ flattened_conjugate);\n\n        Matrix result(x_degree + 1, std::vector<Mint>(y_degree\
    \ + 1));\n        for (int i = 0; i <= x_degree; i++) {\n            std::copy_n(middle.begin()\
    \ + std::size_t(i) * block_width, y_degree + 1,\n                        result[i].begin());\n\
    \        }\n        return result;\n    };\n\n    Matrix denominator(degree, std::vector<Mint>(2));\n\
    \    denominator[0][0] = Mint(1);\n    for (int i = 0; i < degree; i++) denominator[i][1]\
    \ = Mint(0) - argument[i];\n    Matrix transposed =\n        transpose_power_projection(transpose_power_projection,\
    \ std::move(denominator));\n\n    FormalPowerSeries<Mint> result(degree);\n  \
    \  for (int i = 0; i < degree; i++) result[i] = transposed[i][0];\n    std::reverse(result.begin(),\
    \ result.end());\n    return result;\n}\n\n}  // namespace fps\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_FPS_COMPOSITION_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/composition.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/composition.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/composition.hpp
layout: document
title: Formal Power Series Composition
---

## Overview

`compose` computes the truncated composition $f(g(x))$. It uses a transposed
power-projection algorithm, reducing composition to a logarithmic number of
one-dimensional convolutions.

## Interface

```cpp
template <class Mint>
FormalPowerSeries<Mint> compose(
    const FormalPowerSeries<Mint>& outer,
    const FormalPowerSeries<Mint>& inner,
    int degree = -1);
```

`Mint` must satisfy the static modular-integer interface required by
`convolution`; the modular integer types in `math/modint.hpp` do so. Let `Fps`
denote `FormalPowerSeries<Mint>`.

| Function | Result | Complexity |
| --- | --- | --- |
| `compose(f, g, n)` | $f(g(x)) \bmod x^n$ as exactly `n` coefficients. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |
| `compose(f, g)` | The same result with `n = f.size()`. | $O(M(n) \log n)$ time and $O(n \log n)$ memory |

Here $M(n)$ is the cost of multiplying degree-$n$ polynomials, so the time is
$O(n \log^2 n)$ when NTT convolution is available.

Formal power series composition requires `g.empty()` or `g[0] == 0`; the
function asserts this condition. Missing coefficients in either input are
treated as zero. The function does not modify either input.

## Example

```cpp
#include "math/fps/composition.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};
    Fps g = {0, 1, 1};
    Fps h = m1une::fps::compose(f, g, 5);

    for (mint coefficient : h) std::cout << coefficient << ' ';
    std::cout << '\n';
}
```

The result is the first five coefficients of $1 + 2g(x) + 3g(x)^2$.

## Algorithm

The map taking the coefficients of $f$ to those of $f(g(x))$ is linear.
Transposing it turns composition into power projection: extracting one fixed
coefficient from successive powers of $g$. A bivariate Bostan--Mori reduction
halves the $x$-degree at each level. Reversing those reductions evaluates the
transposed map with 2D convolutions and middle products, both encoded as 1D
convolutions. There are $O(\log n)$ levels and $O(M(n))$ work per level.
