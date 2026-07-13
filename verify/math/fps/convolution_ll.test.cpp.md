---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../math/fps/convolution_ll.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <limits>\n#include <random>\n#include <vector>\n\
    \n#ifndef NDEBUG\nnamespace {\n\nstd::vector<long long> naive(const std::vector<long\
    \ long>& first,\n                             const std::vector<long long>& second)\
    \ {\n    if (first.empty() || second.empty()) return {};\n    std::vector<__int128>\
    \ wide(first.size() + second.size() - 1);\n    for (int i = 0; i < int(first.size());\
    \ i++) {\n        for (int j = 0; j < int(second.size()); j++) {\n           \
    \ wide[i + j] += static_cast<__int128>(first[i]) * second[j];\n        }\n   \
    \ }\n    std::vector<long long> result(wide.size());\n    for (int i = 0; i <\
    \ int(wide.size()); i++) {\n        assert(std::numeric_limits<long long>::min()\
    \ <= wide[i]);\n        assert(wide[i] <= std::numeric_limits<long long>::max());\n\
    \        result[i] = static_cast<long long>(wide[i]);\n    }\n    return result;\n\
    }\n\nvoid fixed_tests() {\n    using m1une::fps::convolution_ll;\n    assert(convolution_ll({},\
    \ std::vector<long long>{1}).empty());\n    assert(convolution_ll(std::vector<long\
    \ long>{1, -2, 3},\n                          std::vector<long long>{4, 5}) ==\n\
    \           std::vector<long long>({4, -3, 2, 15}));\n    assert(convolution_ll(std::vector<long\
    \ long>{std::numeric_limits<long long>::max()},\n                          std::vector<long\
    \ long>{1}) ==\n           std::vector<long long>({std::numeric_limits<long long>::max()}));\n\
    \    assert(convolution_ll(std::vector<long long>{std::numeric_limits<long long>::min()},\n\
    \                          std::vector<long long>{1}) ==\n           std::vector<long\
    \ long>({std::numeric_limits<long long>::min()}));\n    assert(convolution_ll(\n\
    \               std::vector<long long>{std::numeric_limits<long long>::max(),\n\
    \                                      std::numeric_limits<long long>::max()},\n\
    \               std::vector<long long>{1, -1}) ==\n           std::vector<long\
    \ long>({std::numeric_limits<long long>::max(), 0,\n                         \
    \          -std::numeric_limits<long long>::max()}));\n}\n\nvoid randomized_tests()\
    \ {\n    std::mt19937_64 random(123456789);\n    for (int trial = 0; trial < 3000;\
    \ trial++) {\n        int first_size = int(random() % 100);\n        int second_size\
    \ = int(random() % 100);\n        std::vector<long long> first(first_size);\n\
    \        std::vector<long long> second(second_size);\n        for (long long&\
    \ value : first) value = int(random() % 2000001) - 1000000;\n        for (long\
    \ long& value : second) value = int(random() % 2000001) - 1000000;\n        assert(m1une::fps::convolution_ll(first,\
    \ second) == naive(first, second));\n    }\n}\n\n}  // namespace\n#endif\n\nint\
    \ main() {\n#ifndef NDEBUG\n    fixed_tests();\n    randomized_tests();\n#endif\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/fps/convolution_ll.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/convolution_ll.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 23:10:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/convolution_ll.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/convolution_ll.test.cpp
- /verify/verify/math/fps/convolution_ll.test.cpp.html
title: verify/math/fps/convolution_ll.test.cpp
---
