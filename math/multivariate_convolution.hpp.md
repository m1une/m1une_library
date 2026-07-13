---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':x:'
    path: math/primitive_root.hpp
    title: Primitive Root
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':x:'
    path: verify/math/multivariate_convolution_cyclic.test.cpp
    title: verify/math/multivariate_convolution_cyclic.test.cpp
  - icon: ':x:'
    path: verify/math/multivariate_convolution_truncated.test.cpp
    title: verify/math/multivariate_convolution_truncated.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP\n#define M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include\
    \ <limits>\n#include <vector>\n\n#include \"fps/convolution.hpp\"\n#include \"\
    primitive_root.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal\
    \ {\n\ninline int multivariate_coefficient_count(const std::vector<int>& dimensions)\
    \ {\n    int64_t count = 1;\n    for (int dimension : dimensions) {\n        assert(dimension\
    \ > 0);\n        count *= dimension;\n        assert(count <= std::numeric_limits<int>::max());\n\
    \    }\n    return int(count);\n}\n\ninline std::vector<int> multivariate_colors(const\
    \ std::vector<int>& dimensions) {\n    const int variable_count = int(dimensions.size());\n\
    \    const int coefficient_count = multivariate_coefficient_count(dimensions);\n\
    \    std::vector<int> color(coefficient_count);\n    if (variable_count == 0)\
    \ return color;\n\n    for (int index = 0; index < coefficient_count; index++)\
    \ {\n        int sum = 0;\n        int stride = 1;\n        for (int variable\
    \ = 0; variable + 1 < variable_count; variable++) {\n            stride *= dimensions[variable];\n\
    \            sum += index / stride;\n        }\n        color[index] = sum % variable_count;\n\
    \    }\n    return color;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> geometric_evaluation(\n\
    \    const std::vector<Mint>& polynomial, Mint ratio\n) {\n    const int size\
    \ = int(polynomial.size());\n    if (size <= 64) {\n        std::vector<Mint>\
    \ result(size);\n        Mint point = 1;\n        for (int i = 0; i < size; i++)\
    \ {\n            Mint power = 1;\n            for (const Mint& coefficient : polynomial)\
    \ {\n                result[i] += coefficient * power;\n                power\
    \ *= point;\n            }\n            point *= ratio;\n        }\n        return\
    \ result;\n    }\n\n    auto triangular_powers = [](Mint base, int length) {\n\
    \        std::vector<Mint> result(length);\n        if (length == 0) return result;\n\
    \        result[0] = 1;\n        Mint power = 1;\n        for (int i = 0; i +\
    \ 1 < length; i++) {\n            result[i + 1] = result[i] * power;\n       \
    \     power *= base;\n        }\n        return result;\n    };\n\n    std::vector<Mint>\
    \ positive = triangular_powers(ratio, 2 * size - 1);\n    std::vector<Mint> negative\
    \ = triangular_powers(ratio.inv(), size);\n    std::vector<Mint> scaled(polynomial);\n\
    \    for (int i = 0; i < size; i++) scaled[i] *= negative[i];\n    std::reverse(scaled.begin(),\
    \ scaled.end());\n    std::vector<Mint> product = fps::convolution(scaled, positive);\n\
    \n    std::vector<Mint> result(size);\n    for (int i = 0; i < size; i++) result[i]\
    \ = product[size - 1 + i] * negative[i];\n    return result;\n}\n\n}  // namespace\
    \ internal\n\ntemplate <class Mint>\nstd::vector<Mint> multivariate_convolution_truncated(\n\
    \    const std::vector<int>& dimensions,\n    const std::vector<Mint>& first,\n\
    \    const std::vector<Mint>& second\n) {\n    static_assert(\n        fps::internal::has_static_modulus<Mint>::value,\n\
    \        \"truncated multivariate convolution requires a static-modulus type\"\
    \n    );\n    const int variable_count = int(dimensions.size());\n    const int\
    \ coefficient_count = internal::multivariate_coefficient_count(dimensions);\n\
    \    assert(int(first.size()) == coefficient_count);\n    assert(int(second.size())\
    \ == coefficient_count);\n    if (variable_count == 0) return {first[0] * second[0]};\n\
    \n    int64_t transform_size_64 = 1;\n    while (transform_size_64 < 2LL * coefficient_count\
    \ - 1) transform_size_64 <<= 1;\n    assert(transform_size_64 <= std::numeric_limits<int>::max());\n\
    \    const int transform_size = int(transform_size_64);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(transform_size) == 0);\n\n    const std::vector<int> color =\
    \ internal::multivariate_colors(dimensions);\n    std::vector<std::vector<Mint>>\
    \ transformed_first(\n        variable_count, std::vector<Mint>(transform_size)\n\
    \    );\n    std::vector<std::vector<Mint>> transformed_second(\n        variable_count,\
    \ std::vector<Mint>(transform_size)\n    );\n    for (int i = 0; i < coefficient_count;\
    \ i++) {\n        transformed_first[color[i]][i] = first[i];\n        transformed_second[color[i]][i]\
    \ = second[i];\n    }\n    for (int group = 0; group < variable_count; group++)\
    \ {\n        fps::internal::ntt(transformed_first[group], false);\n        fps::internal::ntt(transformed_second[group],\
    \ false);\n    }\n\n    std::vector<std::vector<Mint>> transformed_result(\n \
    \       variable_count, std::vector<Mint>(transform_size)\n    );\n    for (int\
    \ left = 0; left < variable_count; left++) {\n        for (int right = 0; right\
    \ < variable_count; right++) {\n            std::vector<Mint>& destination =\n\
    \                transformed_result[(left + right) % variable_count];\n      \
    \      const std::vector<Mint>& left_values = transformed_first[left];\n     \
    \       const std::vector<Mint>& right_values = transformed_second[right];\n \
    \           for (int i = 0; i < transform_size; i++) {\n                destination[i]\
    \ += left_values[i] * right_values[i];\n            }\n        }\n    }\n    for\
    \ (int group = 0; group < variable_count; group++) {\n        fps::internal::ntt(transformed_result[group],\
    \ true);\n    }\n\n    std::vector<Mint> result(coefficient_count);\n    for (int\
    \ i = 0; i < coefficient_count; i++) {\n        result[i] = transformed_result[color[i]][i];\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> multivariate_convolution_cyclic(\n\
    \    const std::vector<int>& dimensions,\n    const std::vector<Mint>& first,\n\
    \    const std::vector<Mint>& second\n) {\n    const int coefficient_count = internal::multivariate_coefficient_count(dimensions);\n\
    \    assert(int(first.size()) == coefficient_count);\n    assert(int(second.size())\
    \ == coefficient_count);\n    if (dimensions.empty()) return {first[0] * second[0]};\n\
    \n    const uint32_t modulus = Mint::mod();\n    const uint64_t generator = primitive_root(modulus);\n\
    \    assert(generator != 0);\n\n    std::vector<Mint> transformed_first(first);\n\
    \    std::vector<Mint> transformed_second(second);\n    int stride = 1;\n    for\
    \ (int dimension : dimensions) {\n        assert((modulus - 1) % uint32_t(dimension)\
    \ == 0);\n        const Mint root = Mint(generator).pow((modulus - 1) / dimension);\n\
    \        for (int block = 0; block < coefficient_count; block += stride * dimension)\
    \ {\n            for (int offset = 0; offset < stride; offset++) {\n         \
    \       std::vector<Mint> first_line(dimension);\n                std::vector<Mint>\
    \ second_line(dimension);\n                for (int i = 0; i < dimension; i++)\
    \ {\n                    first_line[i] = transformed_first[block + offset + stride\
    \ * i];\n                    second_line[i] = transformed_second[block + offset\
    \ + stride * i];\n                }\n                first_line = internal::geometric_evaluation(first_line,\
    \ root);\n                second_line = internal::geometric_evaluation(second_line,\
    \ root);\n                for (int i = 0; i < dimension; i++) {\n            \
    \        transformed_first[block + offset + stride * i] = first_line[i];\n   \
    \                 transformed_second[block + offset + stride * i] = second_line[i];\n\
    \                }\n            }\n        }\n        stride *= dimension;\n \
    \   }\n\n    for (int i = 0; i < coefficient_count; i++) {\n        transformed_first[i]\
    \ *= transformed_second[i];\n    }\n\n    stride = 1;\n    for (int dimension\
    \ : dimensions) {\n        const Mint inverse_root =\n            Mint(generator).pow((modulus\
    \ - 1) / dimension).inv();\n        for (int block = 0; block < coefficient_count;\
    \ block += stride * dimension) {\n            for (int offset = 0; offset < stride;\
    \ offset++) {\n                std::vector<Mint> line(dimension);\n          \
    \      for (int i = 0; i < dimension; i++) {\n                    line[i] = transformed_first[block\
    \ + offset + stride * i];\n                }\n                line = internal::geometric_evaluation(line,\
    \ inverse_root);\n                for (int i = 0; i < dimension; i++) {\n    \
    \                transformed_first[block + offset + stride * i] = line[i];\n \
    \               }\n            }\n        }\n        stride *= dimension;\n  \
    \  }\n\n    const Mint inverse_size = Mint(coefficient_count).inv();\n    for\
    \ (Mint& value : transformed_first) value *= inverse_size;\n    return transformed_first;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_MULTIVARIATE_CONVOLUTION_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/primitive_root.hpp
  - math/prime_factorization.hpp
  isVerificationFile: false
  path: math/multivariate_convolution.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - verify/math/multivariate_convolution_cyclic.test.cpp
  - verify/math/multivariate_convolution_truncated.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/multivariate_convolution.hpp
layout: document
title: Multidimensional Convolution
---

## Overview

Fast convolution of flattened multidimensional arrays. The first dimension is
contiguous: for dimensions `n`, coordinates `(i[0], ..., i[k - 1])` are stored
at

`i[0] + i[1] * n[0] + ... + i[k - 1] * n[0] * ... * n[k - 2]`.

Two products are available:

* truncated convolution discards every term whose exponent reaches the bound
  in any variable, corresponding to reduction modulo
  $(x_0^{n_0}, \ldots, x_{k-1}^{n_{k-1}})$;
* cyclic convolution wraps every exponent in each variable, corresponding to
  reduction modulo
  $(1-x_0^{n_0}, \ldots, 1-x_{k-1}^{n_{k-1}})$.

## API

| Function | Description | Complexity |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> multivariate_convolution_truncated(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the truncated product. | $O(kN\log N+k^2N)$ time and $O(kN)$ memory. |
| `template <class Mint> std::vector<Mint> multivariate_convolution_cyclic(const std::vector<int>& dimensions, const std::vector<Mint>& first, const std::vector<Mint>& second)` | Returns the cyclic product. | $O(N\sum_i \log n_i + P(M))$ time and $O(N+\max_i n_i)$ memory. |

Here, `k = dimensions.size()`, $n_i$ is the size of dimension `i`, and
$N=\prod_i n_i$, $M$ is the modulus, and $P(M)$ is the cost of one
`primitive_root(M)` call. Both input arrays and the returned array have length
$N$.

## Requirements and Behavior

Every dimension must be positive. An empty dimension vector represents a
zero-variable polynomial, so both arrays must contain one scalar.

`multivariate_convolution_truncated` requires a static-modulus `Mint`. If `S`
is the smallest power of two with $S \geq 2N-1$, then `S` must divide
`Mint::mod() - 1`. In particular, `m1une::math::modint998244353` supports all
sizes up to the usual $2^{22}$ coefficient limit for this routine.

`multivariate_convolution_cyclic` accepts either `ModInt<mod>` or
`DynamicModInt<id>`. Its modulus must admit a primitive root, and every $n_i$
must divide `Mint::mod() - 1`. Library Checker's circular version supplies a
prime modulus, which satisfies the first condition. For a dynamic modint, call
`set_mod` before constructing or reading coefficients.

Neither function modifies its arguments.

## Example

```cpp
#include "math/modint.hpp"
#include "math/multivariate_convolution.hpp"

#include <vector>

using mint = m1une::math::modint998244353;

int main() {
    // Shape 2 by 2. Indices are (0,0), (1,0), (0,1), (1,1).
    std::vector<int> dimensions = {2, 2};
    std::vector<mint> first = {1, 2, 3, 4};
    std::vector<mint> second = {5, 6, 7, 8};

    std::vector<mint> truncated =
        m1une::math::multivariate_convolution_truncated(
            dimensions, first, second
        );
    std::vector<mint> cyclic =
        m1une::math::multivariate_convolution_cyclic(
            dimensions, first, second
        );
    // truncated is 5, 16, 22, 60.
    // cyclic is 70, 68, 62, 60.
}
```
