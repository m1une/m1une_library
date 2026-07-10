---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_fast.hpp
    title: math/fps/internal/ntt998_fast.hpp
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/bernoulli.hpp\"\n#include \"../../math/modint.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nusing Mint = m1une::math::modint998244353;\n\
    \nMint evaluate(const std::vector<Mint>& coefficients, Mint x) {\n    Mint result\
    \ = 0;\n    for (int index = int(coefficients.size()) - 1; index >= 0; --index)\
    \ {\n        result = result * x + coefficients[index];\n    }\n    return result;\n\
    }\n\nMint power(Mint base, int exponent) {\n    Mint result = 1;\n    while (exponent--)\
    \ result *= base;\n    return result;\n}\n\nvoid test_numbers_and_polynomials()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(30);\n    assert(bernoulli.number(0)\
    \ == Mint(1));\n    assert(bernoulli.number(1) * Mint(2) == Mint(-1));\n    assert(bernoulli.number(2)\
    \ * Mint(6) == Mint(1));\n    assert(bernoulli.number(4) * Mint(30) == Mint(-1));\n\
    \    for (int degree = 3; degree <= 29; degree += 2) {\n        assert(bernoulli.number(degree)\
    \ == Mint(0));\n    }\n\n    for (int degree = 0; degree <= 20; ++degree) {\n\
    \        auto coefficients = bernoulli.polynomial_coefficients(degree);\n    \
    \    for (int value = -5; value <= 5; ++value) {\n            Mint x = value;\n\
    \            assert(evaluate(coefficients, x) == bernoulli.polynomial(degree,\
    \ x));\n            if (degree > 0) {\n                assert(\n             \
    \       bernoulli.polynomial(degree, x + Mint(1)) -\n                        bernoulli.polynomial(degree,\
    \ x) ==\n                    Mint(degree) * power(x, degree - 1)\n           \
    \     );\n            }\n        }\n    }\n}\n\nvoid test_power_sums() {\n   \
    \ m1une::math::Bernoulli<Mint> bernoulli(20);\n    for (int degree = 0; degree\
    \ <= 20; ++degree) {\n        auto coefficients = bernoulli.power_sum_polynomial(degree);\n\
    \        Mint expected = 0;\n        for (int n = 0; n <= 40; ++n) {\n       \
    \     assert(bernoulli.power_sum(Mint(n), degree) == expected);\n            assert(evaluate(coefficients,\
    \ Mint(n)) == expected);\n            expected += power(Mint(n), degree);\n  \
    \      }\n    }\n\n    for (int degree = 0; degree <= 12; ++degree) {\n      \
    \  for (int left = -10; left <= 10; ++left) {\n            Mint expected = 0;\n\
    \            for (int right = left; right <= 12; ++right) {\n                assert(\n\
    \                    bernoulli.power_sum(Mint(left), Mint(right), degree) ==\n\
    \                    expected\n                );\n                expected +=\
    \ power(Mint(right), degree);\n            }\n        }\n    }\n}\n\nvoid test_polynomial_sums_randomized()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    std::uint64_t state\
    \ = 0xbb67ae8584caa73bULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int test = 0; test < 2000; ++test) {\n        int degree = static_cast<int>(random()\
    \ % 13);\n        std::vector<Mint> coefficients(degree + 1);\n        for (Mint&\
    \ coefficient : coefficients) {\n            coefficient = static_cast<long long>(random()\
    \ % 101) - 50;\n        }\n\n        auto prefix = bernoulli.polynomial_prefix_sum(coefficients);\n\
    \        for (int x = -10; x <= 10; ++x) {\n            assert(\n            \
    \    evaluate(prefix, Mint(x + 1)) - evaluate(prefix, Mint(x)) ==\n          \
    \      evaluate(coefficients, Mint(x))\n            );\n        }\n\n        int\
    \ left = static_cast<int>(random() % 21) - 10;\n        int length = static_cast<int>(random()\
    \ % 21);\n        int right = left + length;\n        Mint expected = 0;\n   \
    \     for (int x = left; x < right; ++x) {\n            expected += evaluate(coefficients,\
    \ Mint(x));\n        }\n        assert(\n            bernoulli.polynomial_sum(\n\
    \                coefficients,\n                Mint(left),\n                Mint(right)\n\
    \            ) == expected\n        );\n    }\n}\n\nvoid test_arithmetic_progressions()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    for (int degree = 0;\
    \ degree <= 12; ++degree) {\n        for (int start = -3; start <= 3; ++start)\
    \ {\n            for (int step = -2; step <= 2; ++step) {\n                Mint\
    \ expected = 0;\n                for (int count = 0; count <= 15; ++count) {\n\
    \                    assert(\n                        bernoulli.arithmetic_progression_power_sum(\n\
    \                            Mint(start),\n                            Mint(step),\n\
    \                            Mint(count),\n                            degree\n\
    \                        ) == expected\n                    );\n             \
    \       expected += power(Mint(start + step * count), degree);\n             \
    \   }\n            }\n        }\n    }\n}\n\nint main() {\n    test_numbers_and_polynomials();\n\
    \    test_power_sums();\n    test_polynomial_sums_randomized();\n    test_arithmetic_progressions();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/bernoulli.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_fast.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/bernoulli_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/bernoulli_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/math/bernoulli_utilities.test.cpp
- /verify/verify/math/bernoulli_utilities.test.cpp.html
title: verify/math/bernoulli_utilities.test.cpp
---
