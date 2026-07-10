---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    IGNORE: ''
    IGNORE_IF_GCC: ''
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ verify/math/partition_number_hrr.test.cpp: line 5: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define IGNORE\n\n#if __has_include(<flint/partitions.h>)\n\n#include \"\
    ../../math/modint.hpp\"\n#include \"../../math/partition_function.hpp\"\n#include\
    \ \"../../math/partition_number_hrr.hpp\"\n\n#include <cassert>\n#include <string>\n\
    #include <vector>\n\nint main() {\n    using Mint = m1une::math::ModInt<1'000'000'007>;\n\
    \n    assert(m1une::math::partition_number_hrr(0).to_string() == \"1\");\n   \
    \ assert(m1une::math::partition_number_hrr(5).to_string() == \"7\");\n    assert(\n\
    \        m1une::math::partition_number_hrr(100).to_string()\n        == \"190569292\"\
    \n    );\n    assert(\n        m1une::math::partition_number_hrr(1000).to_string()\n\
    \        == \"24061467864032622473692149727991\"\n    );\n\n    std::vector<Mint>\
    \ modulo = m1une::math::partition_function<Mint>(5000);\n    for (int n = 0; n\
    \ <= 5000; n++) {\n        m1une::utilities::BigInt value =\n            m1une::math::partition_number_hrr(n);\n\
    \        m1une::utilities::BigInt remainder =\n            value % m1une::utilities::BigInt(Mint::mod());\n\
    \        assert(remainder.to_string() == std::to_string(modulo[n].val()));\n \
    \   }\n\n    m1une::utilities::BigInt large =\n        m1une::math::partition_number_hrr(1'000'000);\n\
    \    assert(large.to_string().size() == 1108);\n}\n\n#else\n\nint main() {}\n\n\
    #endif\n"
  dependsOn: []
  isVerificationFile: true
  path: verify/math/partition_number_hrr.test.cpp
  requiredBy: []
  timestamp: '2026-07-10 19:00:10+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/math/partition_number_hrr.test.cpp
layout: document
redirect_from:
- /verify/verify/math/partition_number_hrr.test.cpp
- /verify/verify/math/partition_number_hrr.test.cpp.html
title: verify/math/partition_number_hrr.test.cpp
---
