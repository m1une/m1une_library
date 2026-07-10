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
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/partition_function.hpp
    title: Partition Function
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/partition_function
    links:
    - https://judge.yosupo.jp/problem/partition_function
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
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/partition_function\"\n\n\
    #include <cassert>\n#include <iostream>\n#include <vector>\n\n#include \"../../math/modint.hpp\"\
    \n#include \"../../math/partition_function.hpp\"\n\nusing Mint = m1une::math::modint998244353;\n\
    \nvoid test_against_naive() {\n    for (int maximum = 0; maximum <= 100; maximum++)\
    \ {\n        std::vector<Mint> expected(maximum + 1);\n        expected[0] = 1;\n\
    \        for (int part = 1; part <= maximum; part++) {\n            for (int sum\
    \ = part; sum <= maximum; sum++) {\n                expected[sum] += expected[sum\
    \ - part];\n            }\n        }\n        assert(\n            m1une::math::partition_function<Mint>(maximum)\
    \ == expected\n        );\n        assert(m1une::math::partition_numbers<Mint>(maximum)\
    \ == expected);\n    }\n}\n\nint main() {\n    test_against_naive();\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int n;\n    std::cin >> n;\n    const std::vector<Mint>\
    \ values =\n        m1une::math::partition_function<Mint>(n);\n    for (int i\
    \ = 0; i <= n; i++) {\n        if (i) std::cout << ' ';\n        std::cout <<\
    \ values[i];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/partition_function.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/partition_function.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/partition_function.test.cpp
layout: document
redirect_from:
- /verify/verify/math/partition_function.test.cpp
- /verify/verify/math/partition_function.test.cpp.html
title: verify/math/partition_function.test.cpp
---
