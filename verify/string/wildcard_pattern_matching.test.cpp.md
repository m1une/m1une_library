---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: string/wildcard_pattern_matching.hpp
    title: Wildcard Pattern Matching
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/wildcard_pattern_matching
    links:
    - https://judge.yosupo.jp/problem/wildcard_pattern_matching
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
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/wildcard_pattern_matching\"\
    \n\n#include \"../../string/wildcard_pattern_matching.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <string>\n#include <vector>\n\
    \nnamespace {\n\nstd::vector<bool> naive_matching(\n    const std::string& text,\n\
    \    const std::string& pattern,\n    char wildcard = '*'\n) {\n    int n = int(text.size());\n\
    \    int m = int(pattern.size());\n    if (n < m) return {};\n    std::vector<bool>\
    \ result(n - m + 1, true);\n    for (int start = 0; start <= n - m; start++) {\n\
    \        for (int i = 0; i < m; i++) {\n            if (\n                text[start\
    \ + i] != wildcard &&\n                pattern[i] != wildcard &&\n           \
    \     text[start + i] != pattern[i]\n            ) {\n                result[start]\
    \ = false;\n                break;\n            }\n        }\n    }\n    return\
    \ result;\n}\n\nvoid test_edge_cases() {\n    assert(\n        m1une::string::wildcard_pattern_matching(std::string(),\
    \ std::string()) ==\n        std::vector<bool>(1, true)\n    );\n    assert(\n\
    \        m1une::string::wildcard_pattern_matching(std::string(\"abc\"), std::string())\
    \ ==\n        std::vector<bool>(4, true)\n    );\n    assert(\n        m1une::string::wildcard_pattern_matching(std::string(\"\
    ab\"), std::string(\"abc\")).empty()\n    );\n    assert(\n        m1une::string::wildcard_pattern_matching(std::string(\"\
    abc\"), std::string(\"***\")) ==\n        std::vector<bool>(1, true)\n    );\n\
    \    assert(\n        m1une::string::wildcard_pattern_matching(std::string(\"\
    ***\"), std::string(\"abc\")) ==\n        std::vector<bool>(1, true)\n    );\n\
    \    assert(\n        m1une::string::wildcard_pattern_matching(\n            std::string(\"\
    abcxabc\"),\n            std::string(\"a?c\"),\n            '?'\n        ) ==\
    \ std::vector<bool>({true, false, false, false, true})\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260713;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; trial++) {\n        int n = int(random()\
    \ % 80);\n        int m = int(random() % 90);\n        std::string text(n, 'a');\n\
    \        std::string pattern(m, 'a');\n        for (char& character : text) {\n\
    \            int value = int(random() % 6);\n            character = value ==\
    \ 5 ? '*' : char('a' + value);\n        }\n        for (char& character : pattern)\
    \ {\n            int value = int(random() % 6);\n            character = value\
    \ == 5 ? '*' : char('a' + value);\n        }\n        assert(\n            m1une::string::wildcard_pattern_matching(text,\
    \ pattern) ==\n            naive_matching(text, pattern)\n        );\n    }\n\
    }\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\
    \n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    std::string\
    \ text, pattern;\n    std::cin >> text >> pattern;\n    std::vector<bool> matches\
    \ =\n        m1une::string::wildcard_pattern_matching(text, pattern);\n    for\
    \ (bool matches_here : matches) std::cout << int(matches_here);\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - string/wildcard_pattern_matching.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/string/wildcard_pattern_matching.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 04:21:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/wildcard_pattern_matching.test.cpp
layout: document
redirect_from:
- /verify/verify/string/wildcard_pattern_matching.test.cpp
- /verify/verify/string/wildcard_pattern_matching.test.cpp.html
title: verify/string/wildcard_pattern_matching.test.cpp
---
