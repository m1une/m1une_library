---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/internal/ntt998_fast.hpp
    title: math/fps/internal/ntt998_fast.hpp
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
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
    \ math/fps/convolution.hpp: line 17: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#pragma\
    \ GCC optimize(\"O3\")\n\n#include <iostream>\n#include <vector>\n\n#include \"\
    ../../../math/fps/convolution.hpp\"\n#include \"../../../math/modint.hpp\"\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nint main() {\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int n, m;\n    input.read(n, m);\n    std::vector<mint> a(n),\
    \ b(m);\n    input.read(a);\n    input.read(b);\n    std::vector<mint> result\
    \ = m1une::fps::convolution(a, b);\n    output.println(result);\n}\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_fast.hpp
  - math/modint.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/fps/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/math/fps/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/convolution_mod.test.cpp
- /verify/verify/math/fps/convolution_mod.test.cpp.html
title: verify/math/fps/convolution_mod.test.cpp
---
