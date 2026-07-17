---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: template.hpp
    title: template.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy:
  - icon: ':warning:'
    path: main.cpp
    title: main.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://zenn.dev/sassan/articles/19db660e4da0a4
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ pch.hpp: line 18: unable to process #include in #if / #ifdef / #ifndef other\
    \ than include guards\n"
  code: '#ifndef M1UNE_PCH_HPP

    #define M1UNE_PCH_HPP 1


    #ifdef LOCAL

    #define _GLIBCXX_DEBUG

    #if defined(__GNUC__) && !defined(__clang__)

    #pragma GCC optimize("O0")

    #endif

    #else

    #if defined(__GNUC__) && !defined(__clang__)

    #pragma GCC optimize("O3")

    #pragma GCC optimize("unroll-loops")

    #endif

    #endif


    #ifdef LOCAL

    // https://zenn.dev/sassan/articles/19db660e4da0a4

    #include "cpp-dump/cpp-dump.hpp"

    #define dump(...) cpp_dump(__VA_ARGS__)

    #else

    #define dump(...)

    #define CPP_DUMP_SET_OPTION(...)

    #define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)

    #define CPP_DUMP_DEFINE_EXPORT_ENUM(...)

    #define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)

    #endif


    #include "template.hpp"


    #endif  // M1UNE_PCH_HPP

    '
  dependsOn:
  - template.hpp
  - utilities/fast_io.hpp
  isVerificationFile: false
  path: pch.hpp
  requiredBy:
  - main.cpp
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: pch.hpp
layout: document
redirect_from:
- /library/pch.hpp
- /library/pch.hpp.html
title: pch.hpp
---
