---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/composition.hpp
    title: Formal Power Series Composition
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
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
    links:
    - https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/composition_of_formal_power_series_large\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <random>\n\n#include \"\
    ../../../math/fps/composition.hpp\"\n#include \"../../../math/modint.hpp\"\n\n\
    using mint = m1une::math::modint998244353;\nusing mint1e9 = m1une::math::modint1000000007;\n\
    using Fps = m1une::fps::FormalPowerSeries<mint>;\n\ntemplate <class Mint>\nm1une::fps::FormalPowerSeries<Mint>\
    \ naive_compose(\n    const m1une::fps::FormalPowerSeries<Mint>& outer,\n    const\
    \ m1une::fps::FormalPowerSeries<Mint>& inner, int degree) {\n    using Series\
    \ = m1une::fps::FormalPowerSeries<Mint>;\n    Series result(degree);\n    Series\
    \ power(degree);\n    if (degree > 0) power[0] = 1;\n    for (int i = 0; i < int(outer.size())\
    \ && i < degree; i++) {\n        for (int j = 0; j < degree; j++) result[j] +=\
    \ outer[i] * power[j];\n        power = (power * inner).pre(degree);\n    }\n\
    \    return result;\n}\n\nvoid randomized_test() {\n    std::mt19937 rng(918273645);\n\
    \    assert(m1une::fps::compose(Fps(), Fps()).empty());\n    for (int iteration\
    \ = 0; iteration < 100; iteration++) {\n        const int degree = int(rng() %\
    \ 24) + 1;\n        Fps outer(rng() % (degree + 1));\n        Fps inner(rng()\
    \ % (degree + 1));\n        for (mint& value : outer) value = mint(rng());\n \
    \       for (mint& value : inner) value = mint(rng());\n        if (!inner.empty())\
    \ inner[0] = 0;\n        assert(m1une::fps::compose(outer, inner, degree) ==\n\
    \               naive_compose(outer, inner, degree));\n    }\n\n    using Fps1e9\
    \ = m1une::fps::FormalPowerSeries<mint1e9>;\n    Fps1e9 outer(48), inner(48);\n\
    \    for (mint1e9& value : outer) value = mint1e9(rng());\n    for (mint1e9& value\
    \ : inner) value = mint1e9(rng());\n    inner[0] = 0;\n    assert(m1une::fps::compose(outer,\
    \ inner) == naive_compose(outer, inner, 48));\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    randomized_test();\n\n    int n;\n    std::cin\
    \ >> n;\n    Fps f(n), g(n);\n    for (mint& value : f) std::cin >> value;\n \
    \   for (mint& value : g) std::cin >> value;\n\n    Fps result = m1une::fps::compose(f,\
    \ g, n);\n    for (int i = 0; i < n; i++) {\n        if (i) std::cout << ' ';\n\
    \        std::cout << result[i];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - math/fps/composition.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/composition.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/composition.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/composition.test.cpp
- /verify/verify/math/fps/composition.test.cpp.html
title: verify/math/fps/composition.test.cpp
---
