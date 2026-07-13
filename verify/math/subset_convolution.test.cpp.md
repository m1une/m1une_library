---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':x:'
    path: math/subset_convolution.hpp
    title: Subset Convolution
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/subset_convolution
    links:
    - https://judge.yosupo.jp/problem/subset_convolution
  bundledCode: "#line 1 \"verify/math/subset_convolution.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math {\n\n\
    template <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"\
    Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 1 \"math/subset_convolution.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <bit>\n#line 7 \"math/subset_convolution.hpp\"\n#include <cstddef>\n#line 9\
    \ \"math/subset_convolution.hpp\"\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <typename T>\nstd::vector<T> subset_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    assert(first.size() == second.size());\n\
    \    if (first.empty()) return {};\n    assert((first.size() & (first.size() -\
    \ 1)) == 0);\n\n    const std::size_t size = first.size();\n    std::size_t bit_count\
    \ = 0;\n    while ((std::size_t(1) << bit_count) < size) ++bit_count;\n    const\
    \ std::size_t rank_count = bit_count + 1;\n\n    std::vector<T> first_ranked(size\
    \ * rank_count);\n    std::vector<T> second_ranked(size * rank_count);\n    for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n        const std::size_t rank\
    \ = std::popcount(mask);\n        first_ranked[mask * rank_count + rank] = std::move(first[mask]);\n\
    \        second_ranked[mask * rank_count + rank] = std::move(second[mask]);\n\
    \    }\n\n    for (std::size_t bit = 1; bit < size; bit <<= 1) {\n        for\
    \ (std::size_t mask = 0; mask < size; ++mask) {\n            if ((mask & bit)\
    \ == 0) continue;\n            const std::size_t destination = mask * rank_count;\n\
    \            const std::size_t source = (mask ^ bit) * rank_count;\n         \
    \   for (std::size_t rank = 0; rank < rank_count; ++rank) {\n                first_ranked[destination\
    \ + rank] +=\n                    first_ranked[source + rank];\n             \
    \   second_ranked[destination + rank] +=\n                    second_ranked[source\
    \ + rank];\n            }\n        }\n    }\n\n    std::vector<T> product(rank_count);\n\
    \    for (std::size_t mask = 0; mask < size; ++mask) {\n        for (T& value\
    \ : product) value = T{};\n        const std::size_t offset = mask * rank_count;\n\
    \        const std::size_t rank_limit = std::popcount(mask);\n        for (std::size_t\
    \ left = 0; left <= rank_limit; ++left) {\n            const std::size_t right_limit\
    \ =\n                std::min(rank_limit, bit_count - left);\n            for\
    \ (std::size_t right = 0; right <= right_limit; ++right) {\n                product[left\
    \ + right] +=\n                    first_ranked[offset + left] *\n           \
    \         second_ranked[offset + right];\n            }\n        }\n        for\
    \ (std::size_t rank = 0; rank < rank_count; ++rank) {\n            first_ranked[offset\
    \ + rank] = std::move(product[rank]);\n        }\n    }\n\n    for (std::size_t\
    \ bit = 1; bit < size; bit <<= 1) {\n        for (std::size_t mask = 0; mask <\
    \ size; ++mask) {\n            if ((mask & bit) == 0) continue;\n            const\
    \ std::size_t destination = mask * rank_count;\n            const std::size_t\
    \ source = (mask ^ bit) * rank_count;\n            for (std::size_t rank = 0;\
    \ rank < rank_count; ++rank) {\n                first_ranked[destination + rank]\
    \ -=\n                    first_ranked[source + rank];\n            }\n      \
    \  }\n    }\n\n    std::vector<T> result(size);\n    for (std::size_t mask = 0;\
    \ mask < size; ++mask) {\n        result[mask] = std::move(\n            first_ranked[mask\
    \ * rank_count + std::popcount(mask)]\n        );\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 5 \"verify/math/subset_convolution.test.cpp\"\
    \n\n#line 10 \"verify/math/subset_convolution.test.cpp\"\n\nnamespace {\n\ntemplate\
    \ <typename T>\nstd::vector<T> naive_subset_convolution(\n    const std::vector<T>&\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    std::vector<T> result(first.size());\n    for (std::size_t mask = 0; mask\
    \ < first.size(); ++mask) {\n        std::size_t submask = mask;\n        while\
    \ (true) {\n            result[mask] += first[submask] * second[mask ^ submask];\n\
    \            if (submask == 0) break;\n            submask = (submask - 1) & mask;\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::vector<long\
    \ long> empty;\n    assert(m1une::math::subset_convolution(empty, empty).empty());\n\
    \n    std::vector<long long> first{7};\n    std::vector<long long> second{-3};\n\
    \    std::vector<long long> expected{-21};\n    assert(m1une::math::subset_convolution(first,\
    \ second) == expected);\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 0x72ad4f19c6e3b805ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 1000; ++trial) {\n        int bit_count = int(random()\
    \ % 8);\n        std::size_t size = std::size_t(1) << bit_count;\n        std::vector<long\
    \ long> first(size), second(size);\n        for (long long& value : first) {\n\
    \            value = static_cast<long long>(random() % 21) - 10;\n        }\n\
    \        for (long long& value : second) {\n            value = static_cast<long\
    \ long>(random() % 21) - 10;\n        }\n        assert(\n            m1une::math::subset_convolution(first,\
    \ second) ==\n            naive_subset_convolution(first, second)\n        );\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\
    \n    int bit_count;\n    std::cin >> bit_count;\n    int size = 1 << bit_count;\n\
    \    using mint = m1une::math::modint998244353;\n    std::vector<mint> first(size),\
    \ second(size);\n    for (mint& value : first) {\n        long long input;\n \
    \       std::cin >> input;\n        value = input;\n    }\n    for (mint& value\
    \ : second) {\n        long long input;\n        std::cin >> input;\n        value\
    \ = input;\n    }\n\n    std::vector<mint> result =\n        m1une::math::subset_convolution(first,\
    \ second);\n    for (int mask = 0; mask < size; ++mask) {\n        if (mask !=\
    \ 0) std::cout << ' ';\n        std::cout << result[mask].val();\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/subset_convolution\"\n\n\
    #include \"../../math/modint.hpp\"\n#include \"../../math/subset_convolution.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \nnamespace {\n\ntemplate <typename T>\nstd::vector<T> naive_subset_convolution(\n\
    \    const std::vector<T>& first,\n    const std::vector<T>& second\n) {\n   \
    \ assert(first.size() == second.size());\n    std::vector<T> result(first.size());\n\
    \    for (std::size_t mask = 0; mask < first.size(); ++mask) {\n        std::size_t\
    \ submask = mask;\n        while (true) {\n            result[mask] += first[submask]\
    \ * second[mask ^ submask];\n            if (submask == 0) break;\n          \
    \  submask = (submask - 1) & mask;\n        }\n    }\n    return result;\n}\n\n\
    void test_edge_cases() {\n    std::vector<long long> empty;\n    assert(m1une::math::subset_convolution(empty,\
    \ empty).empty());\n\n    std::vector<long long> first{7};\n    std::vector<long\
    \ long> second{-3};\n    std::vector<long long> expected{-21};\n    assert(m1une::math::subset_convolution(first,\
    \ second) == expected);\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 0x72ad4f19c6e3b805ULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int trial = 0; trial < 1000; ++trial) {\n        int bit_count = int(random()\
    \ % 8);\n        std::size_t size = std::size_t(1) << bit_count;\n        std::vector<long\
    \ long> first(size), second(size);\n        for (long long& value : first) {\n\
    \            value = static_cast<long long>(random() % 21) - 10;\n        }\n\
    \        for (long long& value : second) {\n            value = static_cast<long\
    \ long>(random() % 21) - 10;\n        }\n        assert(\n            m1une::math::subset_convolution(first,\
    \ second) ==\n            naive_subset_convolution(first, second)\n        );\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    test_edge_cases();\n    test_randomized();\n\
    \n    int bit_count;\n    std::cin >> bit_count;\n    int size = 1 << bit_count;\n\
    \    using mint = m1une::math::modint998244353;\n    std::vector<mint> first(size),\
    \ second(size);\n    for (mint& value : first) {\n        long long input;\n \
    \       std::cin >> input;\n        value = input;\n    }\n    for (mint& value\
    \ : second) {\n        long long input;\n        std::cin >> input;\n        value\
    \ = input;\n    }\n\n    std::vector<mint> result =\n        m1une::math::subset_convolution(first,\
    \ second);\n    for (int mask = 0; mask < size; ++mask) {\n        if (mask !=\
    \ 0) std::cout << ' ';\n        std::cout << result[mask].val();\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/subset_convolution.hpp
  isVerificationFile: true
  path: verify/math/subset_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/math/subset_convolution.test.cpp
layout: document
redirect_from:
- /verify/verify/math/subset_convolution.test.cpp
- /verify/verify/math/subset_convolution.test.cpp.html
title: verify/math/subset_convolution.test.cpp
---
