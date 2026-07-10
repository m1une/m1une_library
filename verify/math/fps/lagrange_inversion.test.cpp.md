---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_fast.hpp
    title: math/fps/internal/ntt998_fast.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
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
    \ math/fps/convolution.hpp: line 17: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    \n#include \"../../../math/fps/lagrange_inversion.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing Fps = m1une::fps::FormalPowerSeries<mint>;\n\
    \nFps naive_multiply(const Fps& a, const Fps& b, int degree) {\n    Fps result(degree);\n\
    \    for (int i = 0; i < int(a.size()) && i < degree; i++) {\n        for (int\
    \ j = 0; j < int(b.size()) && i + j < degree; j++) {\n            result[i + j]\
    \ += a[i] * b[j];\n        }\n    }\n    return result;\n}\n\nFps naive_compose(const\
    \ Fps& outer, const Fps& inner, int degree) {\n    Fps result(degree);\n    Fps\
    \ power(degree);\n    if (degree != 0) power[0] = 1;\n    for (int i = 0; i <\
    \ int(outer.size()) && i < degree; i++) {\n        for (int j = 0; j < degree;\
    \ j++) result[j] += outer[i] * power[j];\n        power = naive_multiply(power,\
    \ inner, degree);\n    }\n    return result;\n}\n\nFps naive_implicit_series(const\
    \ Fps& phi, int degree) {\n    Fps w(degree);\n    for (int iteration = 0; iteration\
    \ < degree; iteration++) {\n        Fps composed = naive_compose(phi, w, degree\
    \ - 1);\n        Fps next(degree);\n        for (int i = 1; i < degree; i++) next[i]\
    \ = composed[i - 1];\n        w = std::move(next);\n    }\n    return w;\n}\n\n\
    void test_lagrange_inversion() {\n    Fps catalan_phi = {1, 2, 1};\n    mint catalan[]\
    \ = {1, 1, 2, 5, 14, 42, 132};\n    for (int n = 1; n <= 6; n++) {\n        assert(m1une::fps::lagrange_inversion_coefficient(catalan_phi,\
    \ n) == catalan[n]);\n    }\n    const int large_n = 128;\n    mint central_binomial\
    \ = 1;\n    for (int i = 1; i <= large_n; i++) {\n        central_binomial *=\
    \ mint(large_n + i) / mint(i);\n    }\n    mint large_catalan = central_binomial\
    \ / mint(large_n + 1);\n    assert(m1une::fps::lagrange_inversion_coefficient(catalan_phi,\
    \ large_n) == large_catalan);\n\n    std::mt19937 random(123456789);\n    for\
    \ (int test = 0; test < 100; test++) {\n        const int degree = 12;\n     \
    \   Fps phi(degree);\n        phi[0] = 1 + random() % 100;\n        for (int i\
    \ = 1; i < degree; i++) phi[i] = random() % 100;\n        Fps w = naive_implicit_series(phi,\
    \ degree);\n\n        Fps outer(degree);\n        for (mint& value : outer) value\
    \ = random() % 100;\n        Fps composed = naive_compose(outer, w, degree);\n\
    \n        for (int n = 1; n < degree; n++) {\n            assert(m1une::fps::lagrange_inversion_coefficient(phi,\
    \ n) == w[n]);\n            assert(m1une::fps::lagrange_burmann_coefficient(phi,\
    \ outer, n) == composed[n]);\n        }\n        assert(m1une::fps::lagrange_burmann_coefficient(phi,\
    \ outer, 0) == outer[0]);\n\n        Fps f = phi.inv(degree) << 1;\n        f.resize(degree);\n\
    \        for (int n = 0; n < degree; n++) {\n            assert(m1une::fps::compositional_inverse_coefficient(f,\
    \ n) == w[n]);\n        }\n    }\n}\n\nint main() {\n    test_lagrange_inversion();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/fps/lagrange_inversion.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_fast.hpp
  - math/modint.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/lagrange_inversion.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/lagrange_inversion.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/lagrange_inversion.test.cpp
- /verify/verify/math/fps/lagrange_inversion.test.cpp.html
title: verify/math/fps/lagrange_inversion.test.cpp
---
