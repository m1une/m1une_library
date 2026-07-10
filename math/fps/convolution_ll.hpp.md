---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/convolution_ll.test.cpp
    title: verify/math/fps/convolution_ll.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_CONVOLUTION_LL_HPP\n#define M1UNE_FPS_CONVOLUTION_LL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <vector>\n\
    \n#include \"convolution.hpp\"\n#include \"../modint.hpp\"\n\nnamespace m1une\
    \ {\nnamespace fps {\n\n// Exact convolution of signed 64-bit coefficients.\n\
    // Every result coefficient must fit in long long.\ninline std::vector<long long>\
    \ convolution_ll(\n    const std::vector<long long>& first,\n    const std::vector<long\
    \ long>& second\n) {\n    if (first.empty() || second.empty()) return {};\n  \
    \  std::size_t result_size = first.size() + second.size() - 1;\n    assert(result_size\
    \ <= (std::size_t(1) << 24));\n\n    using Mint1 = math::ModInt<167772161>;\n\
    \    using Mint2 = math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n\
    \n    auto convolve = [&]<class Mint>() {\n        std::vector<Mint> converted_first(first.size());\n\
    \        std::vector<Mint> converted_second(second.size());\n        for (int\
    \ index = 0; index < int(first.size()); index++) {\n            converted_first[index]\
    \ = Mint(first[index]);\n        }\n        for (int index = 0; index < int(second.size());\
    \ index++) {\n            converted_second[index] = Mint(second[index]);\n   \
    \     }\n        return convolution(converted_first, converted_second);\n    };\n\
    \n    std::vector<Mint1> result1 = convolve.template operator()<Mint1>();\n  \
    \  std::vector<Mint2> result2 = convolve.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ result3 = convolve.template operator()<Mint3>();\n\n    static const std::uint64_t\
    \ inverse_mod1_mod2 =\n        Mint2(Mint1::mod()).inv().val();\n    static const\
    \ std::uint64_t mod1_mod2 =\n        std::uint64_t(Mint1::mod()) * Mint2::mod();\n\
    \    static const std::uint64_t inverse_mod1_mod2_mod3 =\n        Mint3(mod1_mod2\
    \ % Mint3::mod()).inv().val();\n    static const unsigned __int128 crt_modulus\
    \ =\n        static_cast<unsigned __int128>(mod1_mod2) * Mint3::mod();\n\n   \
    \ std::vector<long long> result(result_size);\n    for (int index = 0; index <\
    \ int(result_size); index++) {\n        std::uint64_t residue1 = result1[index].val();\n\
    \        std::uint64_t residue2 = result2[index].val();\n        std::uint64_t\
    \ residue3 = result3[index].val();\n\n        std::uint64_t second_digit =\n \
    \           (residue2 + Mint2::mod() - residue1 % Mint2::mod()) %\n          \
    \  Mint2::mod();\n        second_digit = second_digit * inverse_mod1_mod2 % Mint2::mod();\n\
    \        std::uint64_t first_two =\n            residue1 + std::uint64_t(Mint1::mod())\
    \ * second_digit;\n\n        std::uint64_t third_digit =\n            (residue3\
    \ + Mint3::mod() - first_two % Mint3::mod()) %\n            Mint3::mod();\n  \
    \      third_digit =\n            third_digit * inverse_mod1_mod2_mod3 % Mint3::mod();\n\
    \n        unsigned __int128 reconstructed =\n            first_two + static_cast<unsigned\
    \ __int128>(mod1_mod2) * third_digit;\n        __int128 centered = reconstructed\
    \ <= crt_modulus / 2\n                                ? static_cast<__int128>(reconstructed)\n\
    \                                : -static_cast<__int128>(crt_modulus - reconstructed);\n\
    \        assert(std::numeric_limits<long long>::min() <= centered);\n        assert(centered\
    \ <= std::numeric_limits<long long>::max());\n        result[index] = static_cast<long\
    \ long>(centered);\n    }\n    return result;\n}\n\n}  // namespace fps\n}  //\
    \ namespace m1une\n\n#endif  // M1UNE_FPS_CONVOLUTION_LL_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/convolution_ll.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/convolution_ll.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/convolution_ll.hpp
layout: document
title: Long Long Convolution
---

## Overview

`convolution_ll` computes an exact polynomial convolution whose inputs and
outputs use signed `long long` coefficients.

It performs convolution modulo three NTT-friendly primes and reconstructs each
signed coefficient with the Chinese remainder theorem. Unlike FFT followed by
rounding, the result has no floating-point error.

## Function

```cpp
std::vector<long long> convolution_ll(
    const std::vector<long long>& first,
    const std::vector<long long>& second);
```

The coefficient at index `k` is

$$
\sum_{i+j=k} \text{first}[i]\,\text{second}[j].
$$

If either input is empty, the result is empty. Otherwise, the result has
`first.size() + second.size() - 1` coefficients.

Every exact result coefficient must fit in signed `long long`. Individual
products and intermediate mathematical sums may exceed 64 bits. The required
NTT length must not exceed $2^{24}$.

| Function | Complexity |
| --- | --- |
| `convolution_ll(first, second)` | $O(L\log L)$ time and $O(L)$ memory. |

Here $L$ is the output length rounded up to a power of two. Small inputs use
the modular convolution implementation's quadratic cutoff.

## Example

```cpp
#include "math/fps/convolution_ll.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> first = {1, -2, 3};
    std::vector<long long> second = {4, 5};
    auto result = m1une::fps::convolution_ll(first, second);

    for (long long value : result) std::cout << value << " ";
    std::cout << "\n"; // 4 -3 2 15
}
```
