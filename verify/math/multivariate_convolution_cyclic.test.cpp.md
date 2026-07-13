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
    path: math/modint.hpp
    title: ModInt
  - icon: ':x:'
    path: math/multivariate_convolution.hpp
    title: Multidimensional Convolution
  - icon: ':question:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':x:'
    path: math/primitive_root.hpp
    title: Primitive Root
  - icon: ':question:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/multivariate_convolution_cyclic
    links:
    - https://judge.yosupo.jp/problem/multivariate_convolution_cyclic
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/multivariate_convolution_cyclic\"\
    \n\n#pragma GCC optimize(\"O3\")\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <vector>\n\n#include \"../../math/modint.hpp\"\n#include \"../../math/multivariate_convolution.hpp\"\
    \n#include \"../../utilities/fast_io.hpp\"\n\nnamespace {\n\nusing mint = m1une::math::DynamicModInt<0>;\n\
    \nstd::vector<mint> naive(\n    const std::vector<int>& dimensions,\n    const\
    \ std::vector<mint>& first,\n    const std::vector<mint>& second\n) {\n    const\
    \ int size = int(first.size());\n    std::vector<mint> result(size);\n    for\
    \ (int left = 0; left < size; left++) {\n        for (int right = 0; right < size;\
    \ right++) {\n            int left_index = left;\n            int right_index\
    \ = right;\n            int target = 0;\n            int stride = 1;\n       \
    \     for (int dimension : dimensions) {\n                const int coordinate\
    \ =\n                    (left_index % dimension + right_index % dimension) %\
    \ dimension;\n                target += stride * coordinate;\n               \
    \ stride *= dimension;\n                left_index /= dimension;\n           \
    \     right_index /= dimension;\n            }\n            result[target] +=\
    \ first[left] * second[right];\n        }\n    }\n    return result;\n}\n\nvoid\
    \ test_randomized() {\n    mint::set_mod(97);\n    uint64_t state = 0xfedcba987654321ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n    const int divisors[] = {1, 2,\
    \ 3, 4, 6, 8};\n\n    for (int trial = 0; trial < 300; trial++) {\n        const\
    \ int variable_count = int(random() % 4);\n        std::vector<int> dimensions(variable_count);\n\
    \        int size = 1;\n        for (int& dimension : dimensions) {\n        \
    \    dimension = divisors[random() % 6];\n            size *= dimension;\n   \
    \     }\n        std::vector<mint> first(size), second(size);\n        for (mint&\
    \ value : first) value = random() % mint::mod();\n        for (mint& value : second)\
    \ value = random() % mint::mod();\n        assert(\n            m1une::math::multivariate_convolution_cyclic(\n\
    \                dimensions, first, second\n            ) == naive(dimensions,\
    \ first, second)\n        );\n    }\n\n    std::vector<int> dimensions = {96};\n\
    \    std::vector<mint> first(96), second(96);\n    for (mint& value : first) value\
    \ = random() % mint::mod();\n    for (mint& value : second) value = random() %\
    \ mint::mod();\n    assert(\n        m1une::math::multivariate_convolution_cyclic(\n\
    \            dimensions, first, second\n        ) == naive(dimensions, first,\
    \ second)\n    );\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \    uint32_t modulus = 1;\n    int variable_count = 0;\n    input.read(modulus,\
    \ variable_count);\n    mint::set_mod(modulus);\n    std::vector<int> dimensions(variable_count);\n\
    \    input.read(dimensions);\n    int size = 1;\n    for (int dimension : dimensions)\
    \ size *= dimension;\n    std::vector<mint> first(size), second(size);\n    input.read(first);\n\
    \    input.read(second);\n    output.println(\n        m1une::math::multivariate_convolution_cyclic(\n\
    \            dimensions, first, second\n        )\n    );\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/multivariate_convolution.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/primitive_root.hpp
  - math/prime_factorization.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/multivariate_convolution_cyclic.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/math/multivariate_convolution_cyclic.test.cpp
layout: document
redirect_from:
- /verify/verify/math/multivariate_convolution_cyclic.test.cpp
- /verify/verify/math/multivariate_convolution_cyclic.test.cpp.html
title: verify/math/multivariate_convolution_cyclic.test.cpp
---
