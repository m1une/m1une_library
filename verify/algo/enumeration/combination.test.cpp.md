---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/enumeration/combination.hpp
    title: Combination Masks
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
  bundledCode: "#line 1 \"verify/algo/enumeration/combination.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <vector>\n\n#line 1 \"algo/enumeration/combination.hpp\"\
    \n\n\n\n#line 5 \"algo/enumeration/combination.hpp\"\n#include <concepts>\n#line\
    \ 7 \"algo/enumeration/combination.hpp\"\n#include <limits>\n#include <type_traits>\n\
    \nnamespace m1une {\nnamespace algo {\n\nnamespace internal {\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nUInt combination_low_bits(int\
    \ bit_count) {\n    constexpr int digits = std::numeric_limits<UInt>::digits;\n\
    \    assert(0 <= bit_count && bit_count <= digits);\n    if (bit_count == digits)\
    \ return ~UInt(0);\n    return (UInt(1) << bit_count) - UInt(1);\n}\n\n}  // namespace\
    \ internal\n\ntemplate <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nUInt first_combination_mask(int bit_count, int choose) {\n    constexpr\
    \ int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <= choose && choose\
    \ <= bit_count && bit_count <= digits);\n    if (choose == 0) return UInt(0);\n\
    \    if (choose == bit_count) return internal::combination_low_bits<UInt>(bit_count);\n\
    \    return (UInt(1) << choose) - UInt(1);\n}\n\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nbool next_combination_mask(UInt&\
    \ mask, int bit_count) {\n    const UInt universe = internal::combination_low_bits<UInt>(bit_count);\n\
    \    assert((mask & ~universe) == 0);\n    if (mask == 0) return false;\n\n  \
    \  const UInt lowest = mask & (~mask + UInt(1));\n    const UInt ripple = mask\
    \ + lowest;\n    if (ripple == 0 || (ripple & ~universe) != 0) return false;\n\
    \n    const UInt next = (((ripple ^ mask) >> 2) / lowest) | ripple;\n    if ((next\
    \ & ~universe) != 0) return false;\n    mask = next;\n    return true;\n}\n\n\
    template <std::unsigned_integral UInt = std::uint64_t, class F>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nvoid for_each_combination_mask(int bit_count, int choose, F f) {\n \
    \   constexpr int digits = std::numeric_limits<UInt>::digits;\n    assert(0 <=\
    \ choose && choose <= bit_count && bit_count <= digits);\n    UInt mask = first_combination_mask<UInt>(bit_count,\
    \ choose);\n    while (true) {\n        f(mask);\n        if (!next_combination_mask(mask,\
    \ bit_count)) break;\n    }\n}\n\n}  // namespace algo\n}  // namespace m1une\n\
    \n\n#line 9 \"verify/algo/enumeration/combination.test.cpp\"\n\nvoid test_combination_masks()\
    \ {\n    assert(m1une::algo::first_combination_mask<std::uint64_t>(5, 3) == 0b00111ULL);\n\
    \n    std::uint64_t mask = 0b00111ULL;\n    assert(m1une::algo::next_combination_mask(mask,\
    \ 5));\n    assert(mask == 0b01011ULL);\n\n    std::vector<std::uint64_t> masks;\n\
    \    m1une::algo::for_each_combination_mask(5, 3, [&](std::uint64_t current) {\n\
    \        masks.push_back(current);\n    });\n    std::vector<std::uint64_t> expected\
    \ = {\n        0b00111ULL, 0b01011ULL, 0b01101ULL, 0b01110ULL, 0b10011ULL,\n \
    \       0b10101ULL, 0b10110ULL, 0b11001ULL, 0b11010ULL, 0b11100ULL\n    };\n \
    \   assert(masks == expected);\n\n    masks.clear();\n    m1une::algo::for_each_combination_mask(4,\
    \ 0, [&](std::uint64_t current) {\n        masks.push_back(current);\n    });\n\
    \    assert(masks == std::vector<std::uint64_t>{0});\n\n    masks.clear();\n \
    \   m1une::algo::for_each_combination_mask(4, 4, [&](std::uint64_t current) {\n\
    \        masks.push_back(current);\n    });\n    assert(masks == std::vector<std::uint64_t>{0b1111ULL});\n\
    }\n\nint main() {\n    test_combination_masks();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\n#include \"../../../algo/enumeration/combination.hpp\"\
    \n\nvoid test_combination_masks() {\n    assert(m1une::algo::first_combination_mask<std::uint64_t>(5,\
    \ 3) == 0b00111ULL);\n\n    std::uint64_t mask = 0b00111ULL;\n    assert(m1une::algo::next_combination_mask(mask,\
    \ 5));\n    assert(mask == 0b01011ULL);\n\n    std::vector<std::uint64_t> masks;\n\
    \    m1une::algo::for_each_combination_mask(5, 3, [&](std::uint64_t current) {\n\
    \        masks.push_back(current);\n    });\n    std::vector<std::uint64_t> expected\
    \ = {\n        0b00111ULL, 0b01011ULL, 0b01101ULL, 0b01110ULL, 0b10011ULL,\n \
    \       0b10101ULL, 0b10110ULL, 0b11001ULL, 0b11010ULL, 0b11100ULL\n    };\n \
    \   assert(masks == expected);\n\n    masks.clear();\n    m1une::algo::for_each_combination_mask(4,\
    \ 0, [&](std::uint64_t current) {\n        masks.push_back(current);\n    });\n\
    \    assert(masks == std::vector<std::uint64_t>{0});\n\n    masks.clear();\n \
    \   m1une::algo::for_each_combination_mask(4, 4, [&](std::uint64_t current) {\n\
    \        masks.push_back(current);\n    });\n    assert(masks == std::vector<std::uint64_t>{0b1111ULL});\n\
    }\n\nint main() {\n    test_combination_masks();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - algo/enumeration/combination.hpp
  isVerificationFile: true
  path: verify/algo/enumeration/combination.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 22:10:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/enumeration/combination.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/enumeration/combination.test.cpp
- /verify/verify/algo/enumeration/combination.test.cpp.html
title: verify/algo/enumeration/combination.test.cpp
---
