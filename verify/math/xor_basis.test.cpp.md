---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/xor_basis.hpp
    title: XOR Basis
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
  bundledCode: "#line 1 \"verify/math/xor_basis.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/xor_basis.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <concepts>\n#include <initializer_list>\n#include <iterator>\n#include\
    \ <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <std::unsigned_integral UInt = unsigned long long>\nclass XorBasis {\n    static_assert(!std::same_as<UInt,\
    \ bool>);\n\npublic:\n    static constexpr int bit_width = std::numeric_limits<UInt>::digits;\n\
    \n    XorBasis() = default;\n\n    template <std::input_iterator Iterator, std::sentinel_for<Iterator>\
    \ Sentinel>\n        requires std::convertible_to<std::iter_reference_t<Iterator>,\
    \ UInt>\n    XorBasis(Iterator first, Sentinel last) {\n        for (; first !=\
    \ last; ++first) insert(UInt(*first));\n    }\n\n    XorBasis(std::initializer_list<UInt>\
    \ values)\n        : XorBasis(values.begin(), values.end()) {}\n\n    bool insert(UInt\
    \ value) {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n       \
    \     if (((value >> bit) & UInt(1)) == 0) continue;\n            if (basis_[bit]\
    \ != 0) {\n                value ^= basis_[bit];\n                continue;\n\
    \            }\n\n            for (int lower = bit - 1; lower >= 0; lower--) {\n\
    \                if (((value >> lower) & UInt(1)) != 0) value ^= basis_[lower];\n\
    \            }\n            basis_[bit] = value;\n            rank_++;\n     \
    \       for (int higher = bit + 1; higher < bit_width; higher++) {\n         \
    \       if (((basis_[higher] >> bit) & UInt(1)) != 0) {\n                    basis_[higher]\
    \ ^= value;\n                }\n            }\n            return true;\n    \
    \    }\n        return false;\n    }\n\n    bool contains(UInt value) const {\n\
    \        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if (((value\
    \ >> bit) & UInt(1)) != 0) value ^= basis_[bit];\n        }\n        return value\
    \ == 0;\n    }\n\n    int rank() const {\n        return rank_;\n    }\n\n   \
    \ bool empty() const {\n        return rank_ == 0;\n    }\n\n    void clear()\
    \ {\n        basis_.fill(UInt(0));\n        rank_ = 0;\n    }\n\n    int merge(const\
    \ XorBasis& other) {\n        const int old_rank = rank_;\n        for (UInt value\
    \ : other.basis_) {\n            if (value != 0) insert(value);\n        }\n \
    \       return rank_ - old_rank;\n    }\n\n    UInt min_xor(UInt value = 0) const\
    \ {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if\
    \ ((value ^ basis_[bit]) < value) value ^= basis_[bit];\n        }\n        return\
    \ value;\n    }\n\n    UInt max_xor(UInt value = 0) const {\n        for (int\
    \ bit = bit_width - 1; bit >= 0; bit--) {\n            if (value < (value ^ basis_[bit]))\
    \ value ^= basis_[bit];\n        }\n        return value;\n    }\n\n    UInt kth_smallest(UInt\
    \ index) const {\n        if (rank_ < bit_width) assert(index < (UInt(1) << rank_));\n\
    \        UInt result = 0;\n        int coefficient = 0;\n        for (int bit\
    \ = 0; bit < bit_width; bit++) {\n            if (basis_[bit] == 0) continue;\n\
    \            if (((index >> coefficient) & UInt(1)) != 0) result ^= basis_[bit];\n\
    \            coefficient++;\n        }\n        return result;\n    }\n\n    std::vector<UInt>\
    \ vectors() const {\n        std::vector<UInt> result;\n        result.reserve(rank_);\n\
    \        for (UInt value : basis_) {\n            if (value != 0) result.push_back(value);\n\
    \        }\n        return result;\n    }\n\nprivate:\n    std::array<UInt, bit_width>\
    \ basis_{};\n    int rank_ = 0;\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/math/xor_basis.test.cpp\"\n\n#include <algorithm>\n#line\
    \ 7 \"verify/math/xor_basis.test.cpp\"\n#include <cstdint>\n#include <iostream>\n\
    #include <random>\n#line 11 \"verify/math/xor_basis.test.cpp\"\n\nnamespace {\n\
    \nusing Basis = m1une::math::XorBasis<uint64_t>;\n\nstd::vector<uint64_t> enumerate(const\
    \ std::vector<uint64_t>& values) {\n    std::vector<uint64_t> result;\n    result.reserve(std::size_t(1)\
    \ << values.size());\n    for (uint64_t mask = 0; mask < (uint64_t(1) << values.size());\
    \ mask++) {\n        uint64_t value = 0;\n        for (int i = 0; i < int(values.size());\
    \ i++) {\n            if (((mask >> i) & 1) != 0) value ^= values[i];\n      \
    \  }\n        result.push_back(value);\n    }\n    std::sort(result.begin(), result.end());\n\
    \    result.erase(std::unique(result.begin(), result.end()), result.end());\n\
    \    return result;\n}\n\nvoid test_basic() {\n    Basis basis{3, 5, 6, 0};\n\
    \    assert(basis.rank() == 2);\n    assert(!basis.empty());\n    assert(basis.contains(0));\n\
    \    assert(basis.contains(3));\n    assert(basis.contains(5));\n    assert(basis.contains(6));\n\
    \    assert(!basis.contains(1));\n    assert(!basis.insert(6));\n    assert(basis.min_xor(4)\
    \ == 1);\n    assert(basis.max_xor() == 6);\n    assert(basis.max_xor(8) == 14);\n\
    \n    const std::vector<uint64_t> expected{0, 3, 5, 6};\n    for (uint64_t i =\
    \ 0; i < expected.size(); i++) {\n        assert(basis.kth_smallest(i) == expected[i]);\n\
    \    }\n\n    Basis other{1, 8, 9};\n    assert(basis.merge(other) == 2);\n  \
    \  assert(basis.rank() == 4);\n    assert(basis.contains(15));\n    basis.clear();\n\
    \    assert(basis.empty());\n    assert(basis.vectors().empty());\n}\n\nvoid test_randomized()\
    \ {\n    std::mt19937_64 random(123456789);\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        const int size = int(random() % 11);\n        std::vector<uint64_t>\
    \ values(size);\n        for (uint64_t& value : values) value = random() & 1023;\n\
    \n        Basis basis(values.begin(), values.end());\n        const std::vector<uint64_t>\
    \ span = enumerate(values);\n        assert(span.size() == (std::size_t(1) <<\
    \ basis.rank()));\n        assert(int(basis.vectors().size()) == basis.rank());\n\
    \n        for (uint64_t value = 0; value < 1024; value++) {\n            const\
    \ bool expected = std::binary_search(span.begin(), span.end(), value);\n     \
    \       assert(basis.contains(value) == expected);\n        }\n        for (std::size_t\
    \ i = 0; i < span.size(); i++) {\n            assert(basis.kth_smallest(i) ==\
    \ span[i]);\n        }\n\n        for (int query = 0; query < 20; query++) {\n\
    \            const uint64_t seed = random() & 2047;\n            uint64_t expected_min\
    \ = ~uint64_t(0);\n            uint64_t expected_max = 0;\n            for (uint64_t\
    \ value : span) {\n                expected_min = std::min(expected_min, seed\
    \ ^ value);\n                expected_max = std::max(expected_max, seed ^ value);\n\
    \            }\n            assert(basis.min_xor(seed) == expected_min);\n   \
    \         assert(basis.max_xor(seed) == expected_max);\n        }\n    }\n}\n\n\
    void test_full_rank() {\n    m1une::math::XorBasis<uint8_t> basis;\n    for (int\
    \ bit = 0; bit < 8; bit++) basis.insert(uint8_t(1U << bit));\n    assert(basis.rank()\
    \ == 8);\n    for (int value = 0; value < 256; value++) {\n        assert(basis.kth_smallest(uint8_t(value))\
    \ == uint8_t(value));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_basic();\n\
    \    test_randomized();\n    test_full_rank();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/xor_basis.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <random>\n#include <vector>\n\nnamespace\
    \ {\n\nusing Basis = m1une::math::XorBasis<uint64_t>;\n\nstd::vector<uint64_t>\
    \ enumerate(const std::vector<uint64_t>& values) {\n    std::vector<uint64_t>\
    \ result;\n    result.reserve(std::size_t(1) << values.size());\n    for (uint64_t\
    \ mask = 0; mask < (uint64_t(1) << values.size()); mask++) {\n        uint64_t\
    \ value = 0;\n        for (int i = 0; i < int(values.size()); i++) {\n       \
    \     if (((mask >> i) & 1) != 0) value ^= values[i];\n        }\n        result.push_back(value);\n\
    \    }\n    std::sort(result.begin(), result.end());\n    result.erase(std::unique(result.begin(),\
    \ result.end()), result.end());\n    return result;\n}\n\nvoid test_basic() {\n\
    \    Basis basis{3, 5, 6, 0};\n    assert(basis.rank() == 2);\n    assert(!basis.empty());\n\
    \    assert(basis.contains(0));\n    assert(basis.contains(3));\n    assert(basis.contains(5));\n\
    \    assert(basis.contains(6));\n    assert(!basis.contains(1));\n    assert(!basis.insert(6));\n\
    \    assert(basis.min_xor(4) == 1);\n    assert(basis.max_xor() == 6);\n    assert(basis.max_xor(8)\
    \ == 14);\n\n    const std::vector<uint64_t> expected{0, 3, 5, 6};\n    for (uint64_t\
    \ i = 0; i < expected.size(); i++) {\n        assert(basis.kth_smallest(i) ==\
    \ expected[i]);\n    }\n\n    Basis other{1, 8, 9};\n    assert(basis.merge(other)\
    \ == 2);\n    assert(basis.rank() == 4);\n    assert(basis.contains(15));\n  \
    \  basis.clear();\n    assert(basis.empty());\n    assert(basis.vectors().empty());\n\
    }\n\nvoid test_randomized() {\n    std::mt19937_64 random(123456789);\n    for\
    \ (int trial = 0; trial < 2000; trial++) {\n        const int size = int(random()\
    \ % 11);\n        std::vector<uint64_t> values(size);\n        for (uint64_t&\
    \ value : values) value = random() & 1023;\n\n        Basis basis(values.begin(),\
    \ values.end());\n        const std::vector<uint64_t> span = enumerate(values);\n\
    \        assert(span.size() == (std::size_t(1) << basis.rank()));\n        assert(int(basis.vectors().size())\
    \ == basis.rank());\n\n        for (uint64_t value = 0; value < 1024; value++)\
    \ {\n            const bool expected = std::binary_search(span.begin(), span.end(),\
    \ value);\n            assert(basis.contains(value) == expected);\n        }\n\
    \        for (std::size_t i = 0; i < span.size(); i++) {\n            assert(basis.kth_smallest(i)\
    \ == span[i]);\n        }\n\n        for (int query = 0; query < 20; query++)\
    \ {\n            const uint64_t seed = random() & 2047;\n            uint64_t\
    \ expected_min = ~uint64_t(0);\n            uint64_t expected_max = 0;\n     \
    \       for (uint64_t value : span) {\n                expected_min = std::min(expected_min,\
    \ seed ^ value);\n                expected_max = std::max(expected_max, seed ^\
    \ value);\n            }\n            assert(basis.min_xor(seed) == expected_min);\n\
    \            assert(basis.max_xor(seed) == expected_max);\n        }\n    }\n\
    }\n\nvoid test_full_rank() {\n    m1une::math::XorBasis<uint8_t> basis;\n    for\
    \ (int bit = 0; bit < 8; bit++) basis.insert(uint8_t(1U << bit));\n    assert(basis.rank()\
    \ == 8);\n    for (int value = 0; value < 256; value++) {\n        assert(basis.kth_smallest(uint8_t(value))\
    \ == uint8_t(value));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_basic();\n\
    \    test_randomized();\n    test_full_rank();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/xor_basis.hpp
  isVerificationFile: true
  path: verify/math/xor_basis.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 05:12:04+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/xor_basis.test.cpp
layout: document
redirect_from:
- /verify/verify/math/xor_basis.test.cpp
- /verify/verify/math/xor_basis.test.cpp.html
title: verify/math/xor_basis.test.cpp
---
