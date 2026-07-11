---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"verify/math/modular_square_root.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6\
    \ \"math/modint.hpp\"\n#include <type_traits>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n\
    \    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
    \    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod() {\n     \
    \   return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept\
    \ {\n        ModInt x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr\
    \ ModInt() noexcept : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
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
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/modular_square_root.hpp\"\n\n\n\n#line 6 \"math/modular_square_root.hpp\"\
    \n#include <optional>\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal\
    \ {\n\ninline uint64_t modular_square_root_multiply(uint64_t lhs, uint64_t rhs,\
    \ uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(lhs)\
    \ * rhs % mod);\n}\n\ninline uint64_t modular_square_root_power(uint64_t base,\
    \ uint64_t exponent, uint64_t mod) {\n    uint64_t result = 1 % mod;\n    while\
    \ (exponent > 0) {\n        if (exponent & 1) result = modular_square_root_multiply(result,\
    \ base, mod);\n        base = modular_square_root_multiply(base, base, mod);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\n}  // namespace internal\n\
    \n// Returns x such that x * x = value (mod prime), or nullopt when no such x\
    \ exists.\n// The modulus must be prime.\ninline std::optional<uint64_t> modular_square_root(uint64_t\
    \ value, uint64_t prime) {\n    assert(prime >= 2);\n    value %= prime;\n   \
    \ if (value == 0 || prime == 2) return value;\n\n    if (internal::modular_square_root_power(value,\
    \ (prime - 1) / 2, prime) != 1) {\n        return std::nullopt;\n    }\n    if\
    \ (prime % 4 == 3) {\n        return internal::modular_square_root_power(value,\
    \ prime / 4 + 1, prime);\n    }\n\n    uint64_t odd_part = prime - 1;\n    int\
    \ power_of_two = 0;\n    while ((odd_part & 1) == 0) {\n        odd_part >>= 1;\n\
    \        power_of_two++;\n    }\n\n    uint64_t non_residue = 2;\n    while (internal::modular_square_root_power(non_residue,\
    \ (prime - 1) / 2, prime) == 1) {\n        non_residue++;\n    }\n\n    uint64_t\
    \ c = internal::modular_square_root_power(non_residue, odd_part, prime);\n   \
    \ uint64_t root = internal::modular_square_root_power(value, odd_part / 2 + 1,\
    \ prime);\n    uint64_t remainder = internal::modular_square_root_power(value,\
    \ odd_part, prime);\n    int remaining_power = power_of_two;\n\n    while (remainder\
    \ != 1) {\n        int exponent = 1;\n        uint64_t squared = internal::modular_square_root_multiply(remainder,\
    \ remainder, prime);\n        while (squared != 1) {\n            squared = internal::modular_square_root_multiply(squared,\
    \ squared, prime);\n            exponent++;\n        }\n\n        uint64_t correction\
    \ = c;\n        for (int i = 0; i < remaining_power - exponent - 1; i++) {\n \
    \           correction = internal::modular_square_root_multiply(correction, correction,\
    \ prime);\n        }\n        root = internal::modular_square_root_multiply(root,\
    \ correction, prime);\n        c = internal::modular_square_root_multiply(correction,\
    \ correction, prime);\n        remainder = internal::modular_square_root_multiply(remainder,\
    \ c, prime);\n        remaining_power = exponent;\n    }\n    return root;\n}\n\
    \ntemplate <class Mint>\nstd::optional<Mint> modular_square_root(Mint value) {\n\
    \    auto root = modular_square_root(static_cast<uint64_t>(value.val()),\n   \
    \                                 static_cast<uint64_t>(Mint::mod()));\n    if\
    \ (!root.has_value()) return std::nullopt;\n    return Mint(*root);\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 9 \"verify/math/modular_square_root.test.cpp\"\
    \n\nnamespace {\n\n#ifndef NDEBUG\nbool is_prime(uint64_t value) {\n    if (value\
    \ < 2) return false;\n    for (uint64_t divisor = 2; divisor * divisor <= value;\
    \ divisor++) {\n        if (value % divisor == 0) return false;\n    }\n    return\
    \ true;\n}\n\nvoid exhaustive_test() {\n    for (uint64_t prime = 2; prime < 200;\
    \ prime++) {\n        if (!is_prime(prime)) continue;\n        for (uint64_t value\
    \ = 0; value < prime; value++) {\n            bool exists = false;\n         \
    \   for (uint64_t root = 0; root < prime; root++) {\n                if (root\
    \ * root % prime == value) exists = true;\n            }\n            auto answer\
    \ = m1une::math::modular_square_root(value, prime);\n            assert(answer.has_value()\
    \ == exists);\n            if (answer.has_value()) assert(*answer * *answer %\
    \ prime == value);\n        }\n    }\n\n    using Mint = m1une::math::ModInt<17>;\n\
    \    auto root = m1une::math::modular_square_root(Mint(13));\n    assert(root.has_value());\n\
    \    assert(*root * *root == Mint(13));\n    assert(!m1une::math::modular_square_root(Mint(3)).has_value());\n\
    }\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    exhaustive_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    while (query_count--)\
    \ {\n        uint64_t value, prime;\n        std::cin >> value >> prime;\n   \
    \     auto root = m1une::math::modular_square_root(value, prime);\n        if\
    \ (root.has_value()) {\n            std::cout << *root << '\\n';\n        } else\
    \ {\n            std::cout << -1 << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n\n#include \"../../math/modint.hpp\"\
    \n#include \"../../math/modular_square_root.hpp\"\n\nnamespace {\n\n#ifndef NDEBUG\n\
    bool is_prime(uint64_t value) {\n    if (value < 2) return false;\n    for (uint64_t\
    \ divisor = 2; divisor * divisor <= value; divisor++) {\n        if (value % divisor\
    \ == 0) return false;\n    }\n    return true;\n}\n\nvoid exhaustive_test() {\n\
    \    for (uint64_t prime = 2; prime < 200; prime++) {\n        if (!is_prime(prime))\
    \ continue;\n        for (uint64_t value = 0; value < prime; value++) {\n    \
    \        bool exists = false;\n            for (uint64_t root = 0; root < prime;\
    \ root++) {\n                if (root * root % prime == value) exists = true;\n\
    \            }\n            auto answer = m1une::math::modular_square_root(value,\
    \ prime);\n            assert(answer.has_value() == exists);\n            if (answer.has_value())\
    \ assert(*answer * *answer % prime == value);\n        }\n    }\n\n    using Mint\
    \ = m1une::math::ModInt<17>;\n    auto root = m1une::math::modular_square_root(Mint(13));\n\
    \    assert(root.has_value());\n    assert(*root * *root == Mint(13));\n    assert(!m1une::math::modular_square_root(Mint(3)).has_value());\n\
    }\n#endif\n\n}  // namespace\n\nint main() {\n#ifndef NDEBUG\n    exhaustive_test();\n\
    #endif\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    while (query_count--)\
    \ {\n        uint64_t value, prime;\n        std::cin >> value >> prime;\n   \
    \     auto root = m1une::math::modular_square_root(value, prime);\n        if\
    \ (root.has_value()) {\n            std::cout << *root << '\\n';\n        } else\
    \ {\n            std::cout << -1 << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/modular_square_root.hpp
  isVerificationFile: true
  path: verify/math/modular_square_root.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:26:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/modular_square_root.test.cpp
layout: document
redirect_from:
- /verify/verify/math/modular_square_root.test.cpp
- /verify/verify/math/modular_square_root.test.cpp.html
title: verify/math/modular_square_root.test.cpp
---
