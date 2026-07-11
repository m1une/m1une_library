---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/fps/polynomial_factorization.hpp
    title: Polynomial Factorization
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <random>\n#include <vector>\n\
    \n#include \"../../../math/fps/all.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing mint1e9 = m1une::math::modint1000000007;\n\
    using Fps = m1une::fps::FormalPowerSeries<mint>;\n\ntemplate <class Mint>\nvoid\
    \ assert_equal(const std::vector<Mint>& lhs, const std::vector<Mint>& rhs) {\n\
    \    assert(lhs.size() == rhs.size());\n    for (int i = 0; i < int(lhs.size());\
    \ i++) assert(lhs[i] == rhs[i]);\n}\n\nvoid test_convolution() {\n    std::mt19937\
    \ rng(712367);\n    for (int iteration = 0; iteration < 30; iteration++) {\n \
    \       int n = 33 + int(rng() % 70);\n        int m = 33 + int(rng() % 70);\n\
    \        std::vector<mint> a(n), b(m);\n        for (mint& value : a) value =\
    \ mint(static_cast<uint32_t>(rng()));\n        for (mint& value : b) value = mint(static_cast<uint32_t>(rng()));\n\
    \        assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a,\
    \ b));\n    }\n\n    std::vector<mint1e9> a(70), b(65);\n    for (mint1e9& value\
    \ : a) value = mint1e9(static_cast<uint32_t>(rng()));\n    for (mint1e9& value\
    \ : b) value = mint1e9(static_cast<uint32_t>(rng()));\n    assert_equal(m1une::fps::convolution(a,\
    \ b), m1une::fps::convolution_naive(a, b));\n}\n\nvoid test_series_functions()\
    \ {\n    Fps f(96);\n    f[0] = 1;\n    for (int i = 1; i < int(f.size()); i++)\
    \ f[i] = mint(i * i + 7);\n\n    Fps inverse = f.inv();\n    Fps identity = (f\
    \ * inverse).pre(int(f.size()));\n    assert(identity[0] == mint(1));\n    for\
    \ (int i = 1; i < int(identity.size()); i++) assert(identity[i] == mint(0));\n\
    \n    Fps logarithm = f.log();\n    assert_equal(logarithm.exp(), f);\n    assert_equal(f.derivative().integral().pre(int(f.size()))\
    \ + Fps(1, f[0]), f);\n\n    Fps cube = f.pow(3);\n    assert_equal(cube, ((f\
    \ * f) * f).pre(int(f.size())));\n\n    Fps shifted(40);\n    shifted[4] = 9;\n\
    \    for (int i = 5; i < int(shifted.size()); i++) shifted[i] = mint(i + 11);\n\
    \    auto root = (shifted * shifted).pre(70).sqrt(70);\n    assert(root.has_value());\n\
    \    assert_equal(((*root) * (*root)).pre(70), (shifted * shifted).pre(70));\n\
    \n    Fps beyond_precision(8);\n    beyond_precision[5] = 1;\n    auto zero_root\
    \ = beyond_precision.sqrt(5);\n    assert(zero_root.has_value());\n    assert_equal(*zero_root,\
    \ Fps(5));\n\n    Fps odd_leading(8);\n    odd_leading[3] = 1;\n    assert(!odd_leading.sqrt(8).has_value());\n\
    \n    Fps zero(20);\n    Fps one(20);\n    one[0] = 1;\n    assert_equal(zero.pow(0),\
    \ one);\n    assert_equal(zero.pow(7), zero);\n}\n\nvoid test_polynomial_operations()\
    \ {\n    Fps dividend(80), divisor(35);\n    for (int i = 0; i < int(dividend.size());\
    \ i++) dividend[i] = mint(i * 17 + 3);\n    for (int i = 0; i < int(divisor.size());\
    \ i++) divisor[i] = mint(i * 5 + 1);\n    auto division = dividend.divmod(divisor);\n\
    \    Fps restored = division.first * divisor + division.second;\n    restored.resize(dividend.size());\n\
    \    assert_equal(restored, dividend);\n    assert(division.second.size() < divisor.size());\n\
    \n    mint shift = 12345;\n    Fps translated = dividend.taylor_shift(shift);\n\
    \    for (int x = 0; x < 10; x++) {\n        assert(translated.evaluate(mint(x))\
    \ == dividend.evaluate(mint(x) + shift));\n    }\n}\n\nvoid test_multipoint_and_recurrence()\
    \ {\n    Fps polynomial(70);\n    for (int i = 0; i < int(polynomial.size());\
    \ i++) polynomial[i] = mint(i * i * 13 + 5);\n    std::vector<mint> points(70);\n\
    \    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);\n\
    \n    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);\n\
    \    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));\n\
    \    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);\n\
    \    assert_equal(interpolated, polynomial);\n    std::vector<mint> one_point(1,\
    \ mint(42));\n    std::vector<mint> one_value(1, mint(314));\n    assert_equal(m1une::fps::polynomial_interpolate(one_point,\
    \ one_value), Fps(1, mint(314)));\n    assert(m1une::fps::multipoint_evaluate(Fps(),\
    \ std::vector<mint>()).empty());\n\n    std::vector<mint> initial(2);\n    std::vector<mint>\
    \ recurrence(2);\n    initial[0] = 0;\n    initial[1] = 1;\n    recurrence[0]\
    \ = 1;\n    recurrence[1] = 1;\n    mint previous = 0;\n    mint current = 1;\n\
    \    for (uint64_t index = 0; index < 200; index++) {\n        mint expected =\
    \ index == 0 ? previous : current;\n        assert(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index) == expected);\n        if (index > 0) {\n            mint\
    \ next = previous + current;\n            previous = current;\n            current\
    \ = next;\n        }\n    }\n}\n\nint main() {\n    test_convolution();\n    test_series_functions();\n\
    \    test_polynomial_operations();\n    test_multipoint_and_recurrence();\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - math/fps/all.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/fps/polynomial_factorization.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/fps_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:34:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/fps_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/fps_algorithms.test.cpp
- /verify/verify/math/fps/fps_algorithms.test.cpp.html
title: verify/math/fps/fps_algorithms.test.cpp
---
