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
    \ pch.hpp: line 18: unable to process #include in #if / #ifdef / #ifndef other\
    \ than include guards\n"
  code: "#include \"pch.hpp\"\n\nauto& fastin = m1une::template_io::input();\nauto&\
    \ fastout = m1une::template_io::output();\n\nvoid solve() {\n\n}\n\nint main()\
    \ {\n    CPP_DUMP_SET_OPTION(max_line_width, 80);\n    CPP_DUMP_SET_OPTION(log_label_func,\
    \ cpp_dump::log_label::filename());\n    CPP_DUMP_SET_OPTION(enable_asterisk,\
    \ true);\n    int T = 1;\n    // cin >> T;\n    while (T--) solve();\n    return\
    \ 0;\n}\n"
  dependsOn:
  - pch.hpp
  - template.hpp
  - utilities/fast_io.hpp
  isVerificationFile: false
  path: main.cpp
  requiredBy: []
  timestamp: '2026-07-16 05:31:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: main.cpp
layout: document
redirect_from:
- /library/main.cpp
- /library/main.cpp.html
title: main.cpp
---
