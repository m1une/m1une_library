---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/gray_code.hpp
    title: Gray Code
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
  bundledCode: "#line 1 \"verify/math/gray_code.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/gray_code.hpp\"\n\n\n\n#include <cassert>\n#include <concepts>\n\
    #include <cstddef>\n#include <cstdint>\n#include <limits>\n#include <type_traits>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace math {\n\n// Converts a binary\
    \ value to its binary-reflected Gray code.\ntemplate <std::unsigned_integral UInt>\n\
    requires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nconstexpr UInt gray_encode(UInt\
    \ value) noexcept {\n    return value ^ (value >> 1);\n}\n\n// Converts a binary-reflected\
    \ Gray code to the corresponding binary value.\ntemplate <std::unsigned_integral\
    \ UInt>\nrequires(!std::same_as<std::remove_cv_t<UInt>, bool>)\nconstexpr UInt\
    \ gray_decode(UInt code) noexcept {\n    for (int shift = 1; shift < std::numeric_limits<UInt>::digits;\n\
    \         shift <<= 1) {\n        code ^= code >> shift;\n    }\n    return code;\n\
    }\n\n// Returns all bit_count-bit binary-reflected Gray codes in traversal order.\n\
    template <std::unsigned_integral UInt = std::uint64_t>\nrequires(!std::same_as<std::remove_cv_t<UInt>,\
    \ bool>)\nstd::vector<UInt> gray_code_sequence(int bit_count) {\n    constexpr\
    \ int uint_digits = std::numeric_limits<UInt>::digits;\n    constexpr int size_digits\
    \ = std::numeric_limits<std::size_t>::digits;\n    assert(0 <= bit_count);\n \
    \   assert(bit_count <= uint_digits);\n    assert(bit_count < size_digits);\n\
    \    if (bit_count < 0 || uint_digits < bit_count || size_digits <= bit_count)\
    \ {\n        return {};\n    }\n\n    const std::size_t size = std::size_t(1)\
    \ << bit_count;\n    std::vector<UInt> result(size);\n    for (std::size_t index\
    \ = 0; index < size; ++index) {\n        result[index] = gray_encode(static_cast<UInt>(index));\n\
    \    }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/math/gray_code.test.cpp\"\n\n#include <algorithm>\n#include\
    \ <bit>\n#line 9 \"verify/math/gray_code.test.cpp\"\n#include <iostream>\n#line\
    \ 11 \"verify/math/gray_code.test.cpp\"\n#include <random>\n#line 13 \"verify/math/gray_code.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class UInt>\nconstexpr UInt naive_gray_decode(UInt\
    \ code) {\n    UInt value = 0;\n    for (; code != 0; code >>= 1) value ^= code;\n\
    \    return value;\n}\n\nvoid fixed_tests() {\n    using m1une::math::gray_decode;\n\
    \    using m1une::math::gray_encode;\n\n    static_assert(gray_encode(std::uint32_t(0))\
    \ == 0);\n    static_assert(gray_encode(std::uint32_t(1)) == 1);\n    static_assert(gray_encode(std::uint32_t(2))\
    \ == 3);\n    static_assert(gray_encode(std::uint32_t(7)) == 4);\n    static_assert(gray_decode(std::uint32_t(0))\
    \ == 0);\n    static_assert(gray_decode(std::uint32_t(4)) == 7);\n    static_assert(gray_decode(gray_encode(\n\
    \        std::numeric_limits<std::uint64_t>::max()\n    )) == std::numeric_limits<std::uint64_t>::max());\n\
    \n    const std::vector<std::uint64_t> expected = {0, 1, 3, 2, 6, 7, 5, 4};\n\
    \    assert(m1une::math::gray_code_sequence(3) == expected);\n    assert(m1une::math::gray_code_sequence(0)\
    \ ==\n           std::vector<std::uint64_t>({0}));\n\n    const std::vector<std::uint8_t>\
    \ byte_codes =\n        m1une::math::gray_code_sequence<std::uint8_t>(8);\n  \
    \  assert(byte_codes.size() == 256);\n    for (int value = 0; value < 256; ++value)\
    \ {\n        assert(gray_decode(byte_codes[value]) == value);\n    }\n}\n\nvoid\
    \ exhaustive_tests() {\n    using m1une::math::gray_decode;\n    using m1une::math::gray_encode;\n\
    \n    for (std::uint32_t value = 0; value < (std::uint32_t(1) << 16); ++value)\
    \ {\n        const std::uint32_t code = gray_encode(value);\n        assert(gray_decode(code)\
    \ == value);\n        assert(gray_decode(code) == naive_gray_decode(code));\n\
    \    }\n\n    for (int bit_count = 0; bit_count <= 16; ++bit_count) {\n      \
    \  std::vector<std::uint32_t> codes =\n            m1une::math::gray_code_sequence<std::uint32_t>(bit_count);\n\
    \        assert(codes.size() == (std::size_t(1) << bit_count));\n        for (std::size_t\
    \ index = 0; index < codes.size(); ++index) {\n            assert(\n         \
    \       codes[index] ==\n                gray_encode(static_cast<std::uint32_t>(index))\n\
    \            );\n            if (index != 0) {\n                assert(std::has_single_bit(codes[index]\
    \ ^ codes[index - 1]));\n            }\n        }\n        if (bit_count != 0)\
    \ {\n            assert(std::has_single_bit(codes.front() ^ codes.back()));\n\
    \        }\n\n        std::sort(codes.begin(), codes.end());\n        for (std::size_t\
    \ index = 0; index < codes.size(); ++index) {\n            assert(codes[index]\
    \ == index);\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::mt19937_64\
    \ random(0x6a09e667f3bcc909ULL);\n    for (int trial = 0; trial < 100000; ++trial)\
    \ {\n        const std::uint64_t value = random();\n        const std::uint64_t\
    \ code = m1une::math::gray_encode(value);\n        assert(m1une::math::gray_decode(code)\
    \ == value);\n        assert(m1une::math::gray_decode(code) == naive_gray_decode(code));\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n    exhaustive_tests();\n\
    \    randomized_tests();\n\n    long long a, b;\n    std::cin >> a >> b;\n   \
    \ std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/gray_code.hpp\"\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <limits>\n#include <random>\n\
    #include <vector>\n\nnamespace {\n\ntemplate <class UInt>\nconstexpr UInt naive_gray_decode(UInt\
    \ code) {\n    UInt value = 0;\n    for (; code != 0; code >>= 1) value ^= code;\n\
    \    return value;\n}\n\nvoid fixed_tests() {\n    using m1une::math::gray_decode;\n\
    \    using m1une::math::gray_encode;\n\n    static_assert(gray_encode(std::uint32_t(0))\
    \ == 0);\n    static_assert(gray_encode(std::uint32_t(1)) == 1);\n    static_assert(gray_encode(std::uint32_t(2))\
    \ == 3);\n    static_assert(gray_encode(std::uint32_t(7)) == 4);\n    static_assert(gray_decode(std::uint32_t(0))\
    \ == 0);\n    static_assert(gray_decode(std::uint32_t(4)) == 7);\n    static_assert(gray_decode(gray_encode(\n\
    \        std::numeric_limits<std::uint64_t>::max()\n    )) == std::numeric_limits<std::uint64_t>::max());\n\
    \n    const std::vector<std::uint64_t> expected = {0, 1, 3, 2, 6, 7, 5, 4};\n\
    \    assert(m1une::math::gray_code_sequence(3) == expected);\n    assert(m1une::math::gray_code_sequence(0)\
    \ ==\n           std::vector<std::uint64_t>({0}));\n\n    const std::vector<std::uint8_t>\
    \ byte_codes =\n        m1une::math::gray_code_sequence<std::uint8_t>(8);\n  \
    \  assert(byte_codes.size() == 256);\n    for (int value = 0; value < 256; ++value)\
    \ {\n        assert(gray_decode(byte_codes[value]) == value);\n    }\n}\n\nvoid\
    \ exhaustive_tests() {\n    using m1une::math::gray_decode;\n    using m1une::math::gray_encode;\n\
    \n    for (std::uint32_t value = 0; value < (std::uint32_t(1) << 16); ++value)\
    \ {\n        const std::uint32_t code = gray_encode(value);\n        assert(gray_decode(code)\
    \ == value);\n        assert(gray_decode(code) == naive_gray_decode(code));\n\
    \    }\n\n    for (int bit_count = 0; bit_count <= 16; ++bit_count) {\n      \
    \  std::vector<std::uint32_t> codes =\n            m1une::math::gray_code_sequence<std::uint32_t>(bit_count);\n\
    \        assert(codes.size() == (std::size_t(1) << bit_count));\n        for (std::size_t\
    \ index = 0; index < codes.size(); ++index) {\n            assert(\n         \
    \       codes[index] ==\n                gray_encode(static_cast<std::uint32_t>(index))\n\
    \            );\n            if (index != 0) {\n                assert(std::has_single_bit(codes[index]\
    \ ^ codes[index - 1]));\n            }\n        }\n        if (bit_count != 0)\
    \ {\n            assert(std::has_single_bit(codes.front() ^ codes.back()));\n\
    \        }\n\n        std::sort(codes.begin(), codes.end());\n        for (std::size_t\
    \ index = 0; index < codes.size(); ++index) {\n            assert(codes[index]\
    \ == index);\n        }\n    }\n}\n\nvoid randomized_tests() {\n    std::mt19937_64\
    \ random(0x6a09e667f3bcc909ULL);\n    for (int trial = 0; trial < 100000; ++trial)\
    \ {\n        const std::uint64_t value = random();\n        const std::uint64_t\
    \ code = m1une::math::gray_encode(value);\n        assert(m1une::math::gray_decode(code)\
    \ == value);\n        assert(m1une::math::gray_decode(code) == naive_gray_decode(code));\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n    exhaustive_tests();\n\
    \    randomized_tests();\n\n    long long a, b;\n    std::cin >> a >> b;\n   \
    \ std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/gray_code.hpp
  isVerificationFile: true
  path: verify/math/gray_code.test.cpp
  requiredBy: []
  timestamp: '2026-07-03 14:55:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/gray_code.test.cpp
layout: document
redirect_from:
- /verify/verify/math/gray_code.test.cpp
- /verify/verify/math/gray_code.test.cpp.html
title: verify/math/gray_code.test.cpp
---
