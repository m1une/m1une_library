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
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_polynomials
    links:
    - https://judge.yosupo.jp/problem/inv_of_polynomials
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_polynomials\"\n\n\
    #include <cassert>\n#include <iostream>\n#include <optional>\n#include <random>\n\
    \n#include \"../../../math/fps/half_gcd.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing Fps = m1une::fps::FormalPowerSeries<mint>;\n\
    \nFps naive_gcd(Fps first, Fps second) {\n    first.shrink();\n    second.shrink();\n\
    \    while (!second.empty()) {\n        while (first.size() >= second.size())\
    \ {\n            const int shift = int(first.size() - second.size());\n      \
    \      const mint factor = first.back() / second.back();\n            for (int\
    \ i = 0; i < int(second.size()); i++) {\n                first[i + shift] -= factor\
    \ * second[i];\n            }\n            first.shrink();\n        }\n      \
    \  std::swap(first, second);\n    }\n    if (!first.empty()) first /= first.back();\n\
    \    return first;\n}\n\nvoid test_randomized() {\n    std::mt19937 rng(712367);\n\
    \    for (int iteration = 0; iteration < 200; iteration++) {\n        const int\
    \ first_size = 1 + int(rng() % 35);\n        const int second_size = 1 + int(rng()\
    \ % first_size);\n        Fps first(first_size), second(second_size);\n      \
    \  for (mint& value : first) value = mint(rng());\n        for (mint& value :\
    \ second) value = mint(rng());\n        first.back() = mint(1 + rng() % (mint::mod()\
    \ - 1));\n        second.back() = mint(1 + rng() % (mint::mod() - 1));\n\n   \
    \     auto matrix = m1une::fps::half_gcd(first, second);\n        auto reduced\
    \ = matrix.apply(first, second);\n        if (int(second.size()) > (first_size\
    \ + 1) / 2) {\n            assert(reduced.second.size() < second.size());\n  \
    \      }\n        Fps determinant = matrix.a00 * matrix.a11 - matrix.a01 * matrix.a10;\n\
    \        determinant.shrink();\n        assert(determinant.size() == 1);\n   \
    \     assert(determinant[0] == mint(1) || determinant[0] == mint(0) - mint(1));\n\
    \        assert(naive_gcd(reduced.first, reduced.second) == naive_gcd(first, second));\n\
    \n        auto extended = m1une::fps::polynomial_extended_gcd(first, second);\n\
    \        Fps bezout = first * extended.x + second * extended.y;\n        bezout.shrink();\n\
    \        assert(bezout == extended.gcd);\n        assert(extended.gcd == naive_gcd(first,\
    \ second));\n\n        auto swapped_extended = m1une::fps::polynomial_extended_gcd(second,\
    \ first);\n        Fps swapped_bezout = second * swapped_extended.x + first *\
    \ swapped_extended.y;\n        swapped_bezout.shrink();\n        assert(swapped_bezout\
    \ == swapped_extended.gcd);\n        assert(swapped_extended.gcd == extended.gcd);\n\
    \n        if (extended.gcd.size() == 1) {\n            std::optional<Fps> inverse\
    \ = m1une::fps::polynomial_inv_mod(first, second);\n            assert(inverse.has_value());\n\
    \            assert((first * *inverse) % second == Fps(1, mint(1)) % second);\n\
    \        }\n    }\n\n    Fps zero;\n    Fps polynomial = {2, 3, 1};\n    assert(m1une::fps::polynomial_gcd(zero,\
    \ zero).empty());\n    assert(m1une::fps::polynomial_gcd(zero, polynomial) ==\
    \ polynomial / polynomial.back());\n\n    Fps factor = {1, 1};\n    std::optional<Fps>\
    \ no_inverse =\n        m1une::fps::polynomial_inv_mod(factor, factor * Fps{2,\
    \ 1});\n    assert(!no_inverse.has_value());\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_randomized();\n\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    Fps polynomial(n), modulus(m);\n    for (mint& value : polynomial)\
    \ std::cin >> value;\n    for (mint& value : modulus) std::cin >> value;\n\n \
    \   std::optional<Fps> inverse = m1une::fps::polynomial_inv_mod(polynomial, modulus);\n\
    \    if (!inverse.has_value()) {\n        std::cout << -1 << '\\n';\n        return\
    \ 0;\n    }\n\n    std::cout << inverse->size() << '\\n';\n    if (inverse->empty())\
    \ return 0;\n    for (int i = 0; i < int(inverse->size()); i++) {\n        if\
    \ (i) std::cout << ' ';\n        std::cout << (*inverse)[i];\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - math/fps/half_gcd.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/half_gcd.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/half_gcd.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/half_gcd.test.cpp
- /verify/verify/math/fps/half_gcd.test.cpp.html
title: verify/math/fps/half_gcd.test.cpp
---
