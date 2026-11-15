---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: pch.hpp
    title: pch.hpp
  - icon: ':heavy_check_mark:'
    path: template.hpp
    title: template.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ pch.hpp: line 18: unable to process #include in #if / #ifdef / #ifndef other\
    \ than include guards\n"
  code: "#include \"pch.hpp\"\n\nauto& fastin = m1une::template_io::input();\nauto&\
    \ fastout = m1une::template_io::output();\n\nvoid solve() {\n    int n;\n    scan(n);\n\
    \    vi a(n);\n    scan(a);\n    ll answer = 0;\n    FOR(i, n) FOR(j, i + 1, n)\
    \ answer += a[i] > a[j];\n    print(answer);\n}\n\nint main() {\n    int T = 1;\n\
    \    // scan(T);\n    while (T--) solve();\n    return 0;\n}\n"
  dependsOn:
  - pch.hpp
  - template.hpp
  - utilities/fast_io.hpp
  isVerificationFile: false
  path: examples/stress/brute.cpp
  requiredBy: []
  timestamp: '2026-11-16 02:40:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: examples/stress/brute.cpp
layout: document
redirect_from:
- /library/examples/stress/brute.cpp
- /library/examples/stress/brute.cpp.html
title: examples/stress/brute.cpp
---
