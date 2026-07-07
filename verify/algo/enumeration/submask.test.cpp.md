---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/submask.hpp
    title: Submask Enumeration
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
  bundledCode: "#line 1 \"verify/algo/enumeration/submask.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\n#line\
    \ 1 \"algo/enumeration/submask.hpp\"\n\n\n\n#line 5 \"algo/enumeration/submask.hpp\"\
    \n#include <concepts>\n#include <limits>\n#include <type_traits>\n\nnamespace\
    \ m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt submask_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_submask(UInt mask, F f) {\n    UInt submask = mask;\n\
    \    while (true) {\n        f(submask);\n        if (submask == 0) break;\n \
    \       submask = (submask - 1) & mask;\n    }\n}\n\ntemplate <std::unsigned_integral\
    \ UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nvoid\
    \ for_each_nonzero_submask(UInt mask, F f) {\n    for (UInt submask = mask; submask\
    \ != 0; submask = (submask - 1) & mask) {\n        f(submask);\n    }\n}\n\ntemplate\
    \ <std::unsigned_integral UInt, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_supermask(UInt mask, int bit_count, F f) {\n    const\
    \ UInt universe = internal::submask_low_bits<UInt>(bit_count);\n    assert((mask\
    \ & ~universe) == 0);\n    const UInt free_bits = universe ^ mask;\n    for_each_submask(free_bits,\
    \ [&](UInt added_bits) {\n        f(mask | added_bits);\n    });\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/enumeration/submask.test.cpp\"\
    \n\nvoid test_submasks() {\n    std::vector<std::uint32_t> submasks;\n    m1une::algo::for_each_submask(std::uint32_t(0b1011),\
    \ [&](std::uint32_t mask) {\n        submasks.push_back(mask);\n    });\n    std::vector<std::uint32_t>\
    \ expected = {\n        0b1011, 0b1010, 0b1001, 0b1000, 0b0011, 0b0010, 0b0001,\
    \ 0b0000\n    };\n    assert(submasks == expected);\n\n    int nonzero_count =\
    \ 0;\n    m1une::algo::for_each_nonzero_submask(std::uint32_t(0b1011), [&](std::uint32_t)\
    \ {\n        ++nonzero_count;\n    });\n    assert(nonzero_count == 7);\n}\n\n\
    void test_supermasks() {\n    std::vector<std::uint32_t> supermasks;\n    m1une::algo::for_each_supermask(std::uint32_t(0b001),\
    \ 3, [&](std::uint32_t mask) {\n        supermasks.push_back(mask);\n    });\n\
    \    std::sort(supermasks.begin(), supermasks.end());\n    std::vector<std::uint32_t>\
    \ expected = {0b001, 0b011, 0b101, 0b111};\n    assert(supermasks == expected);\n\
    }\n\nint main() {\n    test_submasks();\n    test_supermasks();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \n#include \"../../../algo/enumeration/submask.hpp\"\n\nvoid test_submasks() {\n\
    \    std::vector<std::uint32_t> submasks;\n    m1une::algo::for_each_submask(std::uint32_t(0b1011),\
    \ [&](std::uint32_t mask) {\n        submasks.push_back(mask);\n    });\n    std::vector<std::uint32_t>\
    \ expected = {\n        0b1011, 0b1010, 0b1001, 0b1000, 0b0011, 0b0010, 0b0001,\
    \ 0b0000\n    };\n    assert(submasks == expected);\n\n    int nonzero_count =\
    \ 0;\n    m1une::algo::for_each_nonzero_submask(std::uint32_t(0b1011), [&](std::uint32_t)\
    \ {\n        ++nonzero_count;\n    });\n    assert(nonzero_count == 7);\n}\n\n\
    void test_supermasks() {\n    std::vector<std::uint32_t> supermasks;\n    m1une::algo::for_each_supermask(std::uint32_t(0b001),\
    \ 3, [&](std::uint32_t mask) {\n        supermasks.push_back(mask);\n    });\n\
    \    std::sort(supermasks.begin(), supermasks.end());\n    std::vector<std::uint32_t>\
    \ expected = {0b001, 0b011, 0b101, 0b111};\n    assert(supermasks == expected);\n\
    }\n\nint main() {\n    test_submasks();\n    test_supermasks();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/enumeration/submask.hpp
  isVerificationFile: true
  path: verify/algo/enumeration/submask.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/enumeration/submask.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/enumeration/submask.test.cpp
- /verify/verify/algo/enumeration/submask.test.cpp.html
title: verify/algo/enumeration/submask.test.cpp
---
