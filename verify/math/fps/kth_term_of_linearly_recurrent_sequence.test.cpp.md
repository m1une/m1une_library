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
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\n#include \"\
    ../../../utilities/fast_io.hpp\"\n#include \"../../../math/fps/linear_recurrence.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nint main() {\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int order;\n    uint64_t index;\n    input.read(order, index);\n\
    \    std::vector<mint> initial(order), recurrence(order);\n    input.read(initial);\n\
    \    input.read(recurrence);\n    output.println(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index));\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
- /verify/verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp.html
title: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
---
