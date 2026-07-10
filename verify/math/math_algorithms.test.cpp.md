---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/base_n.hpp
    title: Base-N Numbers
  - icon: ':heavy_check_mark:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/bitwise_convolution.hpp
    title: Bitwise Convolution
  - icon: ':heavy_check_mark:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/cyclotomic_polynomial.hpp
    title: Cyclotomic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/generalized_floor_sum.hpp
    title: Generalized Floor Sum
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Square Root and Power
  - icon: ':heavy_check_mark:'
    path: math/lucas.hpp
    title: Lucas's Theorem
  - icon: ':heavy_check_mark:'
    path: math/matrix/all.hpp
    title: Matrix Bundle
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  - icon: ':heavy_check_mark:'
    path: math/partition_function.hpp
    title: Partition Function
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
  - icon: ':heavy_check_mark:'
    path: math/prime_sieve.hpp
    title: Prime Sieve
  - icon: ':heavy_check_mark:'
    path: math/primitive_root.hpp
    title: Primitive Root
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':heavy_check_mark:'
    path: math/repunit.hpp
    title: Repunit
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
  - icon: ':heavy_check_mark:'
    path: math/tetration.hpp
    title: Tetration
  - icon: ':heavy_check_mark:'
    path: math/totient_sum.hpp
    title: Totient Sum
  - icon: ':heavy_check_mark:'
    path: math/two_square_sum.hpp
    title: Sum of Two Squares
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
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
  bundledCode: "#line 1 \"verify/math/math_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"math/all.hpp\"\n\n\n\n#line 1 \"math/base_n.hpp\"\
    \n\n\n\n#line 6 \"math/base_n.hpp\"\n#include <concepts>\n#include <limits>\n\
    #include <optional>\n#include <type_traits>\n#line 11 \"math/base_n.hpp\"\n\n\
    namespace m1une {\nnamespace math {\n\n// Returns the canonical most-significant-first\
    \ base-n digits of a\n// nonnegative integer. Zero is represented by one zero\
    \ digit.\ntemplate <std::integral Integer>\nrequires(!std::same_as<std::remove_cv_t<Integer>,\
    \ bool>)\nstd::vector<int> to_base_n(Integer value, int base) {\n    assert(2\
    \ <= base);\n    if (base < 2) return {};\n    if constexpr (std::signed_integral<Integer>)\
    \ {\n        assert(0 <= value);\n        if (value < 0) return {};\n    }\n\n\
    \    using Unsigned = std::make_unsigned_t<Integer>;\n    Unsigned remaining =\
    \ static_cast<Unsigned>(value);\n    if (remaining == 0) return {0};\n\n    std::vector<int>\
    \ digits;\n    const unsigned long long unsigned_base = static_cast<unsigned int>(base);\n\
    \    while (remaining != 0) {\n        digits.push_back(int(remaining % unsigned_base));\n\
    \        remaining = Unsigned(remaining / unsigned_base);\n    }\n    std::reverse(digits.begin(),\
    \ digits.end());\n    return digits;\n}\n\n// Converts most-significant-first\
    \ base-n digits to an integer.\n// Returns nullopt for an invalid digit or when\
    \ the result does not fit.\ntemplate <std::integral Integer, class DigitSequence>\n\
    requires(!std::same_as<std::remove_cv_t<Integer>, bool>)\nstd::optional<Integer>\
    \ checked_from_base_n(const DigitSequence& digits,\n                         \
    \                  int base) {\n    assert(2 <= base);\n    if (base < 2) return\
    \ std::nullopt;\n\n    using Unsigned = std::make_unsigned_t<Integer>;\n    constexpr\
    \ Unsigned integer_limit = [] {\n        if constexpr (std::signed_integral<Integer>)\
    \ {\n            return Unsigned(std::numeric_limits<Integer>::max());\n     \
    \   } else {\n            return std::numeric_limits<Integer>::max();\n      \
    \  }\n    }();\n    const unsigned __int128 limit = integer_limit;\n    const\
    \ unsigned __int128 unsigned_base = static_cast<unsigned int>(base);\n\n    unsigned\
    \ __int128 value = 0;\n    for (const auto& digit_reference : digits) {\n    \
    \    using Digit = std::remove_cvref_t<decltype(digit_reference)>;\n        static_assert(std::integral<Digit>);\n\
    \        static_assert(!std::same_as<Digit, bool>);\n        Digit digit = digit_reference;\n\
    \        if constexpr (std::signed_integral<Digit>) {\n            if (digit <\
    \ 0) return std::nullopt;\n        }\n        using UnsignedDigit = std::make_unsigned_t<Digit>;\n\
    \        UnsignedDigit unsigned_digit = static_cast<UnsignedDigit>(digit);\n \
    \       unsigned __int128 converted_digit = unsigned_digit;\n        if (converted_digit\
    \ >= unsigned_base) {\n            return std::nullopt;\n        }\n\n       \
    \ if (converted_digit > limit ||\n            value > (limit - converted_digit)\
    \ / unsigned_base) {\n            return std::nullopt;\n        }\n        value\
    \ = value * unsigned_base + converted_digit;\n    }\n    return static_cast<Integer>(static_cast<Unsigned>(value));\n\
    }\n\n// Converts most-significant-first base-n digits to an integer.\n// Every\
    \ digit must be valid and the result must fit in Integer.\ntemplate <std::integral\
    \ Integer, class DigitSequence>\nrequires(!std::same_as<std::remove_cv_t<Integer>,\
    \ bool>)\nInteger from_base_n(const DigitSequence& digits, int base) {\n    std::optional<Integer>\
    \ result = checked_from_base_n<Integer>(digits, base);\n    assert(result.has_value());\n\
    \    return result.value_or(Integer(0));\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/bernoulli.hpp\"\n\n\n\n#line 7 \"math/bernoulli.hpp\"\
    \n\n#line 1 \"math/fps/formal_power_series.hpp\"\n\n\n\n#line 10 \"math/fps/formal_power_series.hpp\"\
    \n\n#line 1 \"math/fps/convolution.hpp\"\n\n\n\n#line 5 \"math/fps/convolution.hpp\"\
    \n#include <array>\n#line 10 \"math/fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n\
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
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 12 \"math/fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\nnamespace internal {\n\nconstexpr uint32_t primitive_root_constexpr(uint32_t\
    \ mod) {\n    if (mod == 2) return 1;\n    if (mod == 167772161) return 3;\n \
    \   if (mod == 469762049) return 3;\n    if (mod == 754974721) return 11;\n  \
    \  if (mod == 998244353) return 3;\n    if (mod == 1224736769) return 3;\n\n \
    \   uint32_t divisors[32] = {};\n    int count = 0;\n    uint32_t x = mod - 1;\n\
    \    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {\n        if (x % p != 0)\
    \ continue;\n        divisors[count++] = p;\n        while (x % p == 0) x /= p;\n\
    \    }\n    if (x > 1) divisors[count++] = x;\n\n    for (uint32_t g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < count; i++) {\n    \
    \        uint64_t value = 1;\n            uint64_t base = g;\n            uint32_t\
    \ exponent = (mod - 1) / divisors[i];\n            while (exponent > 0) {\n  \
    \              if (exponent & 1) value = value * base % mod;\n               \
    \ base = base * base % mod;\n                exponent >>= 1;\n            }\n\
    \            if (value == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\nconstexpr int\
    \ two_adic_order(uint32_t x) {\n    int result = 0;\n    while ((x & 1) == 0)\
    \ {\n        x >>= 1;\n        result++;\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstruct NttRoots {\n    static constexpr int max_base = two_adic_order(Mint::mod()\
    \ - 1);\n    std::array<Mint, max_base + 1> root;\n    std::array<Mint, max_base\
    \ + 1> inverse_root;\n    std::array<Mint, max_base> rate;\n    std::array<Mint,\
    \ max_base> inverse_rate;\n    std::array<Mint, max_base> rate_radix4;\n    std::array<Mint,\
    \ max_base> inverse_rate_radix4;\n\n    NttRoots() {\n        constexpr uint32_t\
    \ primitive_root = primitive_root_constexpr(Mint::mod());\n        for (int level\
    \ = 1; level <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n        Mint product = 1;\n        Mint inverse_product = 1;\n       \
    \ for (int i = 0; i + 1 < max_base; i++) {\n            rate[i] = root[i + 2]\
    \ * product;\n            inverse_rate[i] = inverse_root[i + 2] * inverse_product;\n\
    \            product *= inverse_root[i + 2];\n            inverse_product *= root[i\
    \ + 2];\n        }\n        product = 1;\n        inverse_product = 1;\n     \
    \   for (int i = 0; i + 2 < max_base; i++) {\n            rate_radix4[i] = root[i\
    \ + 3] * product;\n            inverse_rate_radix4[i] = inverse_root[i + 3] *\
    \ inverse_product;\n            product *= inverse_root[i + 3];\n            inverse_product\
    \ *= root[i + 3];\n        }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>&\
    \ ntt_roots() {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\
    \ntemplate <class Mint>\n#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__)\
    \ || defined(__i386__))\n__attribute__((target(\"avx2,bmi,bmi2,lzcnt\"), optimize(\"\
    O3,unroll-loops\"), hot, flatten))\n#endif\nvoid ntt(std::vector<Mint>& a, bool\
    \ inverse, bool normalize = true) {\n    const int n = int(a.size());\n    assert(n\
    \ > 0 && (n & (n - 1)) == 0);\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\
    \n    const auto& roots = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\
    \    if (!inverse) {\n        int phase = 0;\n        while (phase < height) {\n\
    \            if (height - phase == 1) {\n                const int width = 1 <<\
    \ (height - phase - 1);\n                Mint twiddle = 1;\n                for\
    \ (int block = 0; block < (1 << phase); block++) {\n                    const\
    \ int offset = block << (height - phase);\n                    for (int i = 0;\
    \ i < width; i++) {\n                        const Mint left = a[offset + i];\n\
    \                        const Mint right = a[offset + i + width] * twiddle;\n\
    \                        a[offset + i] = left + right;\n                     \
    \   a[offset + i + width] = left - right;\n                    }\n           \
    \         if (block + 1 != (1 << phase))\n                        twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase++;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase - 2);\n     \
    \       Mint twiddle = 1;\n            const Mint imaginary = roots.root[2];\n\
    \            for (int block = 0; block < (1 << phase); block++) {\n          \
    \      const Mint twiddle2 = twiddle * twiddle;\n                const Mint twiddle3\
    \ = twiddle2 * twiddle;\n                const int offset = block << (height -\
    \ phase);\n                for (int i = 0; i < width; i++) {\n               \
    \     const uint64_t mod2 = uint64_t(Mint::mod()) * Mint::mod();\n           \
    \         const uint64_t a0 = a[offset + i].val();\n                    const\
    \ uint64_t a1 = uint64_t(a[offset + i + width].val()) * twiddle.val();\n     \
    \               const uint64_t a2 =\n                        uint64_t(a[offset\
    \ + i + 2 * width].val()) * twiddle2.val();\n                    const uint64_t\
    \ a3 =\n                        uint64_t(a[offset + i + 3 * width].val()) * twiddle3.val();\n\
    \                    const uint64_t a1na3i =\n                        uint64_t(Mint(a1\
    \ + mod2 - a3).val()) * imaginary.val();\n                    const uint64_t negative_a2\
    \ = mod2 - a2;\n                    a[offset + i] = Mint(a0 + a2 + a1 + a3);\n\
    \                    a[offset + i + width] = Mint(a0 + a2 + 2 * mod2 - a1 - a3);\n\
    \                    a[offset + i + 2 * width] = Mint(a0 + negative_a2 + a1na3i);\n\
    \                    a[offset + i + 3 * width] = Mint(a0 + negative_a2 + mod2\
    \ - a1na3i);\n                }\n                if (block + 1 != (1 << phase))\n\
    \                    twiddle *= roots.rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase += 2;\n        }\n    } else {\n        int\
    \ phase = height;\n        while (phase > 0) {\n            if (phase == 1) {\n\
    \                const int width = 1 << (height - phase);\n                Mint\
    \ twiddle = 1;\n                for (int block = 0; block < (1 << (phase - 1));\
    \ block++) {\n                    const int offset = block << (height - phase\
    \ + 1);\n                    for (int i = 0; i < width; i++) {\n             \
    \           const Mint left = a[offset + i];\n                        const Mint\
    \ right = a[offset + i + width];\n                        a[offset + i] = left\
    \ + right;\n                        a[offset + i + width] = (left - right) * twiddle;\n\
    \                    }\n                    if (block + 1 != (1 << (phase - 1)))\n\
    \                        twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase--;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase);\n         \
    \   Mint twiddle = 1;\n            const Mint inverse_imaginary = roots.inverse_root[2];\n\
    \            for (int block = 0; block < (1 << (phase - 2)); block++) {\n    \
    \            const Mint twiddle2 = twiddle * twiddle;\n                const Mint\
    \ twiddle3 = twiddle2 * twiddle;\n                const int offset = block <<\
    \ (height - phase + 2);\n                for (int i = 0; i < width; i++) {\n \
    \                   const uint64_t a0 = a[offset + i].val();\n               \
    \     const uint64_t a1 = a[offset + i + width].val();\n                    const\
    \ uint64_t a2 = a[offset + i + 2 * width].val();\n                    const uint64_t\
    \ a3 = a[offset + i + 3 * width].val();\n                    const uint64_t a2na3i\
    \ =\n                        uint64_t(Mint((Mint::mod() + a2 - a3) * inverse_imaginary.val()).val());\n\
    \                    a[offset + i] = Mint(a0 + a1 + a2 + a3);\n              \
    \      a[offset + i + width] =\n                        Mint((a0 + Mint::mod()\
    \ - a1 + a2na3i) * twiddle.val());\n                    a[offset + i + 2 * width]\
    \ = Mint(\n                        (a0 + a1 + 2ULL * Mint::mod() - a2 - a3) *\
    \ twiddle2.val());\n                    a[offset + i + 3 * width] = Mint(\n  \
    \                      (a0 + Mint::mod() - a1 + Mint::mod() - a2na3i) * twiddle3.val());\n\
    \                }\n                if (block + 1 != (1 << (phase - 2)))\n   \
    \                 twiddle *= roots.inverse_rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase -= 2;\n        }\n        if (normalize) {\n\
    \            const Mint inverse_n = Mint(n).inv();\n            for (Mint& value\
    \ : a) value *= inverse_n;\n        }\n    }\n}\n\n}  // namespace internal\n\n\
    template <class Mint>\nstd::vector<Mint> convolution_naive(const std::vector<Mint>&\
    \ a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size() < b.size())\
    \ {\n        for (int i = 0; i < int(a.size()); i++) {\n            for (int j\
    \ = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n        }\n    }\
    \ else {\n        for (int j = 0; j < int(b.size()); j++) {\n            for (int\
    \ i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n        }\n  \
    \  }\n    return result;\n}\n\ntemplate <class Mint>\n#if defined(__GNUC__) &&\
    \ !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))\n__attribute__((target(\"\
    avx2,bmi,bmi2,lzcnt\"), optimize(\"O3,unroll-loops\"), hot, flatten))\n#endif\n\
    std::vector<Mint> convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    const int result_size = int(a.size() + b.size() - 1);\n    int n =\
    \ 1;\n    while (n < result_size) n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n)\
    \ == 0);\n\n    // Allocate the padded buffers directly.  Constructing from the\
    \ inputs and\n    // then resizing used to allocate and copy both large operands\
    \ twice.\n    std::vector<Mint> fa(n);\n    std::vector<Mint> fb(n);\n    std::copy(a.begin(),\
    \ a.end(), fa.begin());\n    std::copy(b.begin(), b.end(), fb.begin());\n    internal::ntt(fa,\
    \ false);\n    internal::ntt(fb, false);\n    const Mint inverse_n = Mint(n).inv();\n\
    \    for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;\n    internal::ntt(fa,\
    \ true, false);\n    fa.resize(result_size);\n    return fa;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    if (a.empty() || b.empty()) return {};\n    if (std::min(a.size(),\
    \ b.size()) <= 32) return convolution_naive(a, b);\n\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a,\
    \ b);\n\n    using Mint1 = math::ModInt<167772161>;\n    using Mint2 = math::ModInt<469762049>;\n\
    \    using Mint3 = math::ModInt<754974721>;\n    assert(n <= (1 << 24));\n\n \
    \   [[maybe_unused]] const unsigned __int128 coefficient_bound =\n        static_cast<unsigned\
    \ __int128>(std::min(a.size(), b.size())) * (Mint::mod() - 1) *\n        (Mint::mod()\
    \ - 1);\n    [[maybe_unused]] const unsigned __int128 crt_modulus =\n        static_cast<unsigned\
    \ __int128>(Mint1::mod()) * Mint2::mod() * Mint3::mod();\n    assert(coefficient_bound\
    \ < crt_modulus);\n\n    auto converted_convolution = [&]<class OtherMint>() {\n\
    \        std::vector<OtherMint> converted_a(a.size());\n        std::vector<OtherMint>\
    \ converted_b(b.size());\n        for (int i = 0; i < int(a.size()); i++) converted_a[i]\
    \ = OtherMint(a[i].val());\n        for (int i = 0; i < int(b.size()); i++) converted_b[i]\
    \ = OtherMint(b[i].val());\n        return convolution_ntt(converted_a, converted_b);\n\
    \    };\n    std::vector<Mint1> c1 = converted_convolution.template operator()<Mint1>();\n\
    \    std::vector<Mint2> c2 = converted_convolution.template operator()<Mint2>();\n\
    \    std::vector<Mint3> c3 = converted_convolution.template operator()<Mint3>();\n\
    \    static const uint64_t inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n\
    \    static const uint64_t mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static\
    \ const uint64_t mod1_mod2_mod3 =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod())\
    \ % Mint3::mod();\n    static const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
    \n    const uint64_t target_mod = Mint::mod();\n    const uint64_t mod1_target\
    \ = Mint1::mod() % target_mod;\n    const uint64_t mod1_mod2_target = mod1_target\
    \ * (Mint2::mod() % target_mod) % target_mod;\n    std::vector<Mint> result(result_size);\n\
    \    for (int i = 0; i < result_size; i++) {\n        const uint64_t r1 = c1[i].val();\n\
    \        const uint64_t r2 = c2[i].val();\n        const uint64_t r3 = c3[i].val();\n\
    \        const uint64_t first =\n            (r2 + Mint2::mod() - r1 % Mint2::mod())\
    \ % Mint2::mod() * inverse_mod1_mod2 %\n            Mint2::mod();\n        const\
    \ uint64_t combined_mod3 =\n            (r1 % Mint3::mod() + mod1_mod3 * (first\
    \ % Mint3::mod())) % Mint3::mod();\n        const uint64_t second =\n        \
    \    (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3\
    \ %\n            Mint3::mod();\n\n        uint64_t value = r1 % target_mod;\n\
    \        value = (value + mod1_target * (first % target_mod)) % target_mod;\n\
    \        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;\n\
    \        result[i] = Mint::raw(uint32_t(value));\n    }\n    return result;\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 12 \"math/fps/formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nstd::optional<Mint> modular_square_root(Mint value) {\n    const uint32_t\
    \ mod = Mint::mod();\n    if (value == Mint(0)) return Mint(0);\n    if (mod ==\
    \ 2) return value;\n    if (value.pow((mod - 1) / 2) != Mint(1)) return std::nullopt;\n\
    \    if (mod % 4 == 3) return value.pow((mod + 1) / 4);\n\n    uint32_t q = mod\
    \ - 1;\n    int s = 0;\n    while ((q & 1) == 0) {\n        q >>= 1;\n       \
    \ s++;\n    }\n\n    Mint z = 2;\n    while (z.pow((mod - 1) / 2) == Mint(1))\
    \ ++z;\n    Mint c = z.pow(q);\n    Mint x = value.pow((q + 1) / 2);\n    Mint\
    \ t = value.pow(q);\n    int m = s;\n    while (t != Mint(1)) {\n        int i\
    \ = 1;\n        Mint squared = t * t;\n        while (squared != Mint(1)) {\n\
    \            squared *= squared;\n            i++;\n        }\n        Mint b\
    \ = c.pow(uint64_t(1) << (m - i - 1));\n        x *= b;\n        c = b * b;\n\
    \        t *= c;\n        m = i;\n    }\n    return x;\n}\n\n}  // namespace internal\n\
    \ntemplate <class Mint>\nstruct FormalPowerSeries : std::vector<Mint> {\n    using\
    \ std::vector<Mint>::vector;\n    using Fps = FormalPowerSeries;\n\n    FormalPowerSeries()\
    \ = default;\n    FormalPowerSeries(const std::vector<Mint>& values) : std::vector<Mint>(values)\
    \ {}\n    FormalPowerSeries(std::vector<Mint>&& values) : std::vector<Mint>(std::move(values))\
    \ {}\n\n    Fps& shrink() {\n        while (!this->empty() && this->back() ==\
    \ Mint(0)) this->pop_back();\n        return *this;\n    }\n\n    Fps pre(int\
    \ degree) const {\n        assert(degree >= 0);\n        Fps result(this->begin(),\
    \ this->begin() + std::min<int>(degree, this->size()));\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    Fps reversed(int size = -1) const {\n  \
    \      Fps result = *this;\n        if (size >= 0) result.resize(size);\n    \
    \    std::reverse(result.begin(), result.end());\n        return result;\n   \
    \ }\n\n    Fps& operator+=(const Fps& rhs) {\n        if (this->size() < rhs.size())\
    \ this->resize(rhs.size());\n        for (int i = 0; i < int(rhs.size()); i++)\
    \ (*this)[i] += rhs[i];\n        return *this;\n    }\n\n    Fps& operator-=(const\
    \ Fps& rhs) {\n        if (this->size() < rhs.size()) this->resize(rhs.size());\n\
    \        for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];\n   \
    \     return *this;\n    }\n\n    Fps& operator*=(const Fps& rhs) {\n        std::vector<Mint>\
    \ lhs(this->begin(), this->end());\n        *this = convolution(lhs, rhs);\n \
    \       return *this;\n    }\n\n    Fps& operator*=(Mint rhs) {\n        for (Mint&\
    \ value : *this) value *= rhs;\n        return *this;\n    }\n\n    Fps& operator/=(Mint\
    \ rhs) {\n        return *this *= rhs.inv();\n    }\n\n    Fps& operator<<=(int\
    \ shift) {\n        assert(shift >= 0);\n        this->insert(this->begin(), shift,\
    \ Mint(0));\n        return *this;\n    }\n\n    Fps& operator>>=(int shift) {\n\
    \        assert(shift >= 0);\n        if (shift >= int(this->size())) {\n    \
    \        this->clear();\n        } else {\n            this->erase(this->begin(),\
    \ this->begin() + shift);\n        }\n        return *this;\n    }\n\n    Fps\
    \ operator+() const {\n        return *this;\n    }\n\n    Fps operator-() const\
    \ {\n        Fps result = *this;\n        for (Mint& value : result) value = Mint(0)\
    \ - value;\n        return result;\n    }\n\n    friend Fps operator+(Fps lhs,\
    \ const Fps& rhs) {\n        return lhs += rhs;\n    }\n\n    friend Fps operator-(Fps\
    \ lhs, const Fps& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Fps\
    \ operator*(Fps lhs, const Fps& rhs) {\n        return lhs *= rhs;\n    }\n\n\
    \    friend Fps operator*(Fps lhs, Mint rhs) {\n        return lhs *= rhs;\n \
    \   }\n\n    friend Fps operator*(Mint lhs, Fps rhs) {\n        return rhs *=\
    \ lhs;\n    }\n\n    friend Fps operator/(Fps lhs, Mint rhs) {\n        return\
    \ lhs /= rhs;\n    }\n\n    friend Fps operator<<(Fps lhs, int shift) {\n    \
    \    return lhs <<= shift;\n    }\n\n    friend Fps operator>>(Fps lhs, int shift)\
    \ {\n        return lhs >>= shift;\n    }\n\n    Fps derivative() const {\n  \
    \      if (this->empty()) return {};\n        Fps result(this->size() - 1);\n\
    \        for (int i = 1; i < int(this->size()); i++) result[i - 1] = (*this)[i]\
    \ * Mint(i);\n        return result;\n    }\n\n    Fps integral() const {\n  \
    \      Fps result(this->size() + 1);\n        if (this->empty()) return result;\n\
    \        assert(this->size() < Mint::mod());\n\n        std::vector<Mint> inverse(this->size()\
    \ + 1);\n        inverse[1] = 1;\n        for (int i = 2; i <= int(this->size());\
    \ i++) {\n            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) *\
    \ inverse[Mint::mod() % uint32_t(i)];\n        }\n        for (int i = 0; i <\
    \ int(this->size()); i++) result[i + 1] = (*this)[i] * inverse[i + 1];\n     \
    \   return result;\n    }\n\n    Mint evaluate(Mint x) const {\n        Mint result\
    \ = 0;\n        for (auto it = this->rbegin(); it != this->rend(); ++it) result\
    \ = result * x + *it;\n        return result;\n    }\n\n    Fps inv(int degree\
    \ = -1) const {\n        if (degree < 0) degree = int(this->size());\n       \
    \ assert(degree >= 0);\n        if (degree == 0) return {};\n        assert(!this->empty()\
    \ && (*this)[0] != Mint(0));\n\n        Fps result(1, (*this)[0].inv());\n   \
    \     for (int size = 1; size < degree; size <<= 1) {\n            const int next_size\
    \ = std::min(size << 1, degree);\n            const int transform_size = size\
    \ << 1;\n            if (size >= 32 && (Mint::mod() - 1) % uint32_t(transform_size)\
    \ == 0) {\n                // Newton's g <- g(2-fg), restricted to the newly determined\n\
    \                // half.  Keeping g in the frequency domain avoids two general\n\
    \                // convolutions and their 2x larger padding.\n              \
    \  std::vector<Mint> transformed_f(transform_size);\n                std::copy_n(this->begin(),\
    \ std::min<int>(this->size(), next_size),\n                            transformed_f.begin());\n\
    \                std::vector<Mint> transformed_g(transform_size);\n          \
    \      std::copy(result.begin(), result.end(), transformed_g.begin());\n     \
    \           internal::ntt(transformed_f, false);\n                internal::ntt(transformed_g,\
    \ false);\n\n                std::vector<Mint> error(transform_size);\n      \
    \          for (int i = 0; i < transform_size; i++)\n                    error[i]\
    \ = transformed_f[i] * transformed_g[i];\n                internal::ntt(error,\
    \ true);\n                std::fill(error.begin(), error.begin() + size, Mint(0));\n\
    \                internal::ntt(error, false);\n                for (int i = 0;\
    \ i < transform_size; i++) error[i] *= transformed_g[i];\n                internal::ntt(error,\
    \ true);\n\n                result.resize(next_size);\n                for (int\
    \ i = size; i < next_size; i++) result[i] = Mint(0) - error[i];\n            \
    \    continue;\n            }\n            Fps product = this->pre(next_size)\
    \ * result;\n            product.resize(next_size);\n            for (Mint& value\
    \ : product) value = Mint(0) - value;\n            product[0] += Mint(2);\n  \
    \          result = (result * product).pre(next_size);\n        }\n        return\
    \ result.pre(degree);\n    }\n\n    Fps log(int degree = -1) const {\n       \
    \ if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ == Mint(1));\n        return (derivative() * inv(degree)).pre(degree - 1).integral();\n\
    \    }\n\n    Fps exp(int degree = -1) const {\n        if (degree < 0) degree\
    \ = int(this->size());\n        assert(degree >= 0);\n        if (degree == 0)\
    \ return {};\n        assert(this->empty() || (*this)[0] == Mint(0));\n\n    \
    \    Fps result(1, Mint(1));\n        for (int size = 1; size < degree; size <<=\
    \ 1) {\n            const int next_size = std::min(size << 1, degree);\n     \
    \       Fps correction = this->pre(next_size) - result.log(next_size);\n     \
    \       correction[0] += Mint(1);\n            result = (result * correction).pre(next_size);\n\
    \        }\n        return result.pre(degree);\n    }\n\n    Fps pow(long long\
    \ exponent, int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(exponent >= 0 && degree >= 0);\n        if (degree == 0) return\
    \ {};\n        if (exponent == 0) {\n            Fps result(degree);\n       \
    \     result[0] = 1;\n            return result;\n        }\n\n        int first\
    \ = 0;\n        while (first < int(this->size()) && (*this)[first] == Mint(0))\
    \ first++;\n        if (first == int(this->size()) || first > (degree - 1) / exponent)\
    \ return Fps(degree);\n\n        const int shift = int(first * exponent);\n  \
    \      const Mint leading = (*this)[first];\n        Fps normalized = (*this >>\
    \ first) / leading;\n        Fps result = (normalized.log(degree - shift) * Mint(exponent)).exp(degree\
    \ - shift);\n        result *= leading.pow(exponent);\n        result <<= shift;\n\
    \        result.resize(degree);\n        return result;\n    }\n\n    std::optional<Fps>\
    \ sqrt(int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(degree >= 0);\n        if (degree == 0) return Fps();\n\n    \
    \    int first = 0;\n        while (first < int(this->size()) && (*this)[first]\
    \ == Mint(0)) first++;\n        if (first == int(this->size())) return Fps(degree);\n\
    \        if (first >= degree) return Fps(degree);\n        if (first & 1) return\
    \ std::nullopt;\n\n        const int shift = first / 2;\n        auto leading_root\
    \ = internal::modular_square_root((*this)[first]);\n        if (!leading_root.has_value())\
    \ return std::nullopt;\n\n        const int result_degree = degree - shift;\n\
    \        Fps normalized = (*this >> first) / (*this)[first];\n        Fps result\
    \ = (normalized.log(result_degree) / Mint(2)).exp(result_degree);\n        result\
    \ *= *leading_root;\n        result <<= shift;\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    std::pair<Fps, Fps> divmod(const Fps& divisor)\
    \ const {\n        Fps dividend = *this;\n        Fps normalized_divisor = divisor;\n\
    \        dividend.shrink();\n        normalized_divisor.shrink();\n        assert(!normalized_divisor.empty());\n\
    \n        if (dividend.size() < normalized_divisor.size()) return std::make_pair(Fps(),\
    \ dividend);\n        const int quotient_size = int(dividend.size() - normalized_divisor.size()\
    \ + 1);\n        Fps quotient =\n            (dividend.reversed().pre(quotient_size)\
    \ * normalized_divisor.reversed().inv(quotient_size))\n                .pre(quotient_size)\n\
    \                .reversed();\n        quotient.shrink();\n        Fps remainder\
    \ = dividend - normalized_divisor * quotient;\n        remainder.resize(normalized_divisor.size()\
    \ - 1);\n        remainder.shrink();\n        return std::make_pair(std::move(quotient),\
    \ std::move(remainder));\n    }\n\n    Fps& operator/=(const Fps& rhs) {\n   \
    \     *this = divmod(rhs).first;\n        return *this;\n    }\n\n    Fps& operator%=(const\
    \ Fps& rhs) {\n        *this = divmod(rhs).second;\n        return *this;\n  \
    \  }\n\n    friend Fps operator/(Fps lhs, const Fps& rhs) {\n        return lhs\
    \ /= rhs;\n    }\n\n    friend Fps operator%(Fps lhs, const Fps& rhs) {\n    \
    \    return lhs %= rhs;\n    }\n\n    Fps taylor_shift(Mint shift) const {\n \
    \       const int n = int(this->size());\n        if (n == 0) return {};\n   \
    \     assert(uint32_t(n) < Mint::mod());\n\n        std::vector<Mint> factorial(n,\
    \ Mint(1));\n        std::vector<Mint> inverse_factorial(n, Mint(1));\n      \
    \  for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * Mint(i);\n  \
    \      inverse_factorial[n - 1] = factorial[n - 1].inv();\n        for (int i\
    \ = n - 1; i > 0; i--) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);\n\
    \n        Fps left(n);\n        Fps right(n);\n        Mint power = 1;\n     \
    \   for (int i = 0; i < n; i++) {\n            left[n - 1 - i] = (*this)[i] *\
    \ factorial[i];\n            right[i] = power * inverse_factorial[i];\n      \
    \      power *= shift;\n        }\n        Fps product = left * right;\n     \
    \   Fps result(n);\n        for (int i = 0; i < n; i++) result[i] = product[n\
    \ - 1 - i] * inverse_factorial[i];\n        return result;\n    }\n};\n\n}  //\
    \ namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/combinatorics.hpp\"\
    \n\n\n\n#line 7 \"math/combinatorics.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <class Mint>\nstruct Combinatorics {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n   public:\n    explicit\
    \ Combinatorics(int maximum = 0) : _factorial(1, Mint(1)), _inverse_factorial(1,\
    \ Mint(1)) {\n        ensure(maximum);\n    }\n\n    int maximum() const {\n \
    \       return int(_factorial.size()) - 1;\n    }\n\n    void ensure(int maximum)\
    \ {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n        if (maximum <= this->maximum()) return;\n\n       \
    \ const int old_maximum = this->maximum();\n        _factorial.resize(maximum\
    \ + 1);\n        _inverse_factorial.resize(maximum + 1);\n        for (int i =\
    \ old_maximum + 1; i <= maximum; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum] = _factorial[maximum].inv();\n\
    \        for (int i = maximum; i > old_maximum; i--) {\n            _inverse_factorial[i\
    \ - 1] = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    Mint factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _factorial[n];\n\
    \    }\n\n    Mint inverse_factorial(int n) const {\n        assert(0 <= n &&\
    \ n <= maximum());\n        return _inverse_factorial[n];\n    }\n\n    Mint inverse(int\
    \ n) const {\n        assert(1 <= n && n <= maximum());\n        return _factorial[n\
    \ - 1] * _inverse_factorial[n];\n    }\n\n    Mint binom(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n -\
    \ k];\n    }\n\n    Mint perm(int n, int k) const {\n        if (k < 0 || k >\
    \ n) return Mint(0);\n        assert(n <= maximum());\n        return _factorial[n]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint multiset(int types, int count)\
    \ const {\n        if (types < 0 || count < 0) return Mint(0);\n        if (types\
    \ == 0) return Mint(count == 0);\n        const long long total = static_cast<long\
    \ long>(types) + count - 1;\n        assert(total <= maximum());\n        return\
    \ binom(static_cast<int>(total), count);\n    }\n\n    Mint catalan(int n) const\
    \ {\n        assert(n >= 0);\n        const long long doubled = 2LL * n;\n   \
    \     assert(doubled <= maximum());\n        return binom(int(doubled), n) - binom(int(doubled),\
    \ n + 1);\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/bernoulli.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nnamespace\
    \ bernoulli_detail {\n\ntemplate <class Mint>\nstd::vector<Mint> numbers(\n  \
    \  int maximum,\n    const Combinatorics<Mint>& combinations\n) {\n    using Fps\
    \ = fps::FormalPowerSeries<Mint>;\n    Fps denominator(maximum + 1);\n    for\
    \ (int index = 0; index <= maximum; ++index) {\n        denominator[index] = combinations.inverse_factorial(index\
    \ + 1);\n    }\n\n    Fps generating_function = denominator.inv(maximum + 1);\n\
    \    std::vector<Mint> result(maximum + 1);\n    for (int index = 0; index <=\
    \ maximum; ++index) {\n        result[index] =\n            generating_function[index]\
    \ * combinations.factorial(index);\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nMint evaluate_polynomial(const std::vector<Mint>& coefficients, Mint\
    \ x) {\n    Mint result = 0;\n    for (int index = int(coefficients.size()) -\
    \ 1; index >= 0; --index) {\n        result = result * x + coefficients[index];\n\
    \    }\n    return result;\n}\n\n}  // namespace bernoulli_detail\n\n// Uses x\
    \ / (exp(x) - 1), so B_1 = -1/2.\ntemplate <class Mint>\nstd::vector<Mint> bernoulli_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n    Combinatorics<Mint> combinations(maximum + 1);\n  \
    \  return bernoulli_detail::numbers(maximum, combinations);\n}\n\ntemplate <class\
    \ Mint>\nclass Bernoulli {\n   public:\n    explicit Bernoulli(int maximum)\n\
    \        : combinations_(checked_maximum(maximum) + 1),\n          numbers_(bernoulli_detail::numbers(maximum,\
    \ combinations_)) {}\n\n    int maximum() const {\n        return int(numbers_.size())\
    \ - 1;\n    }\n\n    const std::vector<Mint>& numbers() const {\n        return\
    \ numbers_;\n    }\n\n    Mint number(int degree) const {\n        assert(0 <=\
    \ degree && degree <= maximum());\n        return numbers_[degree];\n    }\n\n\
    \    // Coefficients of B_degree(x), in increasing order of powers of x.\n   \
    \ std::vector<Mint> polynomial_coefficients(int degree) const {\n        assert(0\
    \ <= degree && degree <= maximum());\n        std::vector<Mint> result(degree\
    \ + 1);\n        for (int power = 0; power <= degree; ++power) {\n           \
    \ result[power] =\n                combinations_.binom(degree, power) *\n    \
    \            numbers_[degree - power];\n        }\n        return result;\n  \
    \  }\n\n    Mint polynomial(int degree, Mint x) const {\n        assert(0 <= degree\
    \ && degree <= maximum());\n        std::vector<Mint> powers(degree + 1, Mint(1));\n\
    \        for (int power = 0; power < degree; ++power) {\n            powers[power\
    \ + 1] = powers[power] * x;\n        }\n\n        Mint result = 0;\n        for\
    \ (int index = 0; index <= degree; ++index) {\n            result += combinations_.binom(degree,\
    \ index) * numbers_[index] *\n                      powers[degree - index];\n\
    \        }\n        return result;\n    }\n\n    // Returns sum_{i=0}^{n-1} i^degree,\
    \ evaluated as a polynomial in n.\n    Mint power_sum(Mint n, int degree) const\
    \ {\n        assert(0 <= degree && degree <= maximum());\n        std::vector<Mint>\
    \ powers(degree + 2, Mint(1));\n        for (int power = 0; power <= degree; ++power)\
    \ {\n            powers[power + 1] = powers[power] * n;\n        }\n\n       \
    \ Mint result = 0;\n        for (int index = 0; index <= degree; ++index) {\n\
    \            result += combinations_.binom(degree + 1, index) *\n            \
    \          numbers_[index] * powers[degree + 1 - index];\n        }\n        return\
    \ result * combinations_.inverse(degree + 1);\n    }\n\n    // Returns sum_{i=left}^{right-1}\
    \ i^degree.\n    Mint power_sum(Mint left, Mint right, int degree) const {\n \
    \       return power_sum(right, degree) - power_sum(left, degree);\n    }\n\n\
    \    // Coefficients of sum_{i=0}^{n-1} i^degree as a polynomial in n.\n    std::vector<Mint>\
    \ power_sum_polynomial(int degree) const {\n        assert(0 <= degree && degree\
    \ <= maximum());\n        std::vector<Mint> result(degree + 2);\n        Mint\
    \ inverse = combinations_.inverse(degree + 1);\n        for (int index = 0; index\
    \ <= degree; ++index) {\n            result[degree + 1 - index] +=\n         \
    \       combinations_.binom(degree + 1, index) * numbers_[index] *\n         \
    \       inverse;\n        }\n        return result;\n    }\n\n    // If P is given\
    \ by coefficients, returns coefficients of the unique Q\n    // with Q(0) = 0\
    \ and Q(n) = sum_{i=0}^{n-1} P(i).\n    std::vector<Mint> polynomial_prefix_sum(\n\
    \        const std::vector<Mint>& coefficients\n    ) const {\n        if (coefficients.empty())\
    \ return std::vector<Mint>{Mint(0)};\n        int degree = int(coefficients.size())\
    \ - 1;\n        assert(degree <= maximum());\n\n        std::vector<Mint> result(degree\
    \ + 2);\n        for (int source_degree = 0;\n             source_degree <= degree;\n\
    \             ++source_degree) {\n            Mint inverse = combinations_.inverse(source_degree\
    \ + 1);\n            for (int index = 0; index <= source_degree; ++index) {\n\
    \                result[source_degree + 1 - index] +=\n                    coefficients[source_degree]\
    \ *\n                    combinations_.binom(source_degree + 1, index) *\n   \
    \                 numbers_[index] * inverse;\n            }\n        }\n     \
    \   return result;\n    }\n\n    // Returns sum_{i=left}^{right-1} P(i).\n   \
    \ Mint polynomial_sum(\n        const std::vector<Mint>& coefficients,\n     \
    \   Mint left,\n        Mint right\n    ) const {\n        std::vector<Mint> prefix\
    \ = polynomial_prefix_sum(coefficients);\n        return bernoulli_detail::evaluate_polynomial(prefix,\
    \ right) -\n               bernoulli_detail::evaluate_polynomial(prefix, left);\n\
    \    }\n\n    // Returns sum_{i=0}^{count-1} (start + step*i)^degree.\n    Mint\
    \ arithmetic_progression_power_sum(\n        Mint start,\n        Mint step,\n\
    \        Mint count,\n        int degree\n    ) const {\n        assert(0 <= degree\
    \ && degree <= maximum());\n        std::vector<Mint> start_powers(degree + 1,\
    \ Mint(1));\n        std::vector<Mint> step_powers(degree + 1, Mint(1));\n   \
    \     for (int power = 0; power < degree; ++power) {\n            start_powers[power\
    \ + 1] = start_powers[power] * start;\n            step_powers[power + 1] = step_powers[power]\
    \ * step;\n        }\n\n        Mint result = 0;\n        for (int power = 0;\
    \ power <= degree; ++power) {\n            result += combinations_.binom(degree,\
    \ power) *\n                      start_powers[degree - power] * step_powers[power]\
    \ *\n                      power_sum(count, power);\n        }\n        return\
    \ result;\n    }\n\n   private:\n    static int checked_maximum(int maximum) {\n\
    \        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n        return maximum;\n    }\n\n    Combinatorics<Mint>\
    \ combinations_;\n    std::vector<Mint> numbers_;\n};\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n#line 1 \"math/bitwise_convolution.hpp\"\n\n\n\n#line\
    \ 5 \"math/bitwise_convolution.hpp\"\n#include <cstddef>\n#line 8 \"math/bitwise_convolution.hpp\"\
    \n\n#line 1 \"math/zeta_mobius_transform.hpp\"\n\n\n\n#line 7 \"math/zeta_mobius_transform.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail\
    \ {\n\ninline bool is_power_of_two(std::size_t size) noexcept {\n    return size\
    \ != 0 && (size & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
    \ limit) {\n    std::vector<std::size_t> primes;\n    std::vector<bool> is_prime(limit\
    \ + 1, true);\n    if (!is_prime.empty()) is_prime[0] = false;\n    if (limit\
    \ >= 1) is_prime[1] = false;\n    for (std::size_t value = 2; value <= limit;\
    \ ++value) {\n        if (!is_prime[value]) continue;\n        primes.emplace_back(value);\n\
    \        if (value > limit / value) continue;\n        for (\n            std::size_t\
    \ multiple = value * value;\n            multiple <= limit;\n            multiple\
    \ += value\n        ) {\n            is_prime[multiple] = false;\n        }\n\
    \    }\n    return primes;\n}\n\n}  // namespace zeta_mobius_transform_detail\n\
    \ntemplate <typename T>\nvoid subset_zeta_transform(std::vector<T>& values) {\n\
    \    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n \
    \   for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for (\n\
    \            std::size_t block = 0;\n            block < values.size();\n    \
    \        block += bit << 1\n        ) {\n            for (std::size_t offset =\
    \ 0; offset < bit; ++offset) {\n                values[block + bit + offset] +=\
    \ values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid subset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + bit + offset]\
    \ -= values[block + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename\
    \ T>\nvoid superset_zeta_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] += values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void superset_mobius_transform(std::vector<T>& values) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t bit = 1; bit < values.size(); bit <<= 1) {\n        for\
    \ (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += bit << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < bit; ++offset) {\n                values[block + offset] -= values[block\
    \ + bit + offset];\n            }\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void divisor_zeta_transform(std::vector<T>& values) {\n    if (values.size() <=\
    \ 2) return;\n    const std::size_t limit = values.size() - 1;\n    const std::vector<std::size_t>\
    \ primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n    for\
    \ (std::size_t prime : primes) {\n        for (std::size_t value = 1; value <=\
    \ limit / prime; ++value) {\n            values[value * prime] += values[value];\n\
    \        }\n    }\n}\n\ntemplate <typename T>\nvoid divisor_mobius_transform(std::vector<T>&\
    \ values) {\n    if (values.size() <= 2) return;\n    const std::size_t limit\
    \ = values.size() - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value * prime] -= values[value];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_zeta_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (\n            std::size_t\
    \ value = limit / prime;\n            value >= 1;\n            --value\n     \
    \   ) {\n            values[value] += values[value * prime];\n        }\n    }\n\
    }\n\ntemplate <typename T>\nvoid multiple_mobius_transform(std::vector<T>& values)\
    \ {\n    if (values.size() <= 2) return;\n    const std::size_t limit = values.size()\
    \ - 1;\n    const std::vector<std::size_t> primes =\n        zeta_mobius_transform_detail::primes_up_to(limit);\n\
    \    for (std::size_t prime : primes) {\n        for (std::size_t value = 1; value\
    \ <= limit / prime; ++value) {\n            values[value] -= values[value * prime];\n\
    \        }\n    }\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 10 \"math/bitwise_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \nnamespace bitwise_convolution_detail {\n\ninline std::size_t common_size(\n\
    \    std::size_t first_size,\n    std::size_t second_size\n) {\n    std::size_t\
    \ required = first_size > second_size\n        ? first_size\n        : second_size;\n\
    \    std::size_t size = 1;\n    while (size < required) size <<= 1;\n    return\
    \ size;\n}\n\ntemplate <typename T>\nstd::vector<T> pointwise_product(\n    std::vector<T>\
    \ first,\n    const std::vector<T>& second\n) {\n    assert(first.size() == second.size());\n\
    \    for (std::size_t index = 0; index < first.size(); ++index) {\n        first[index]\
    \ *= second[index];\n    }\n    return first;\n}\n\n}  // namespace bitwise_convolution_detail\n\
    \ntemplate <typename T>\nvoid walsh_hadamard_transform(\n    std::vector<T>& values,\n\
    \    bool inverse = false\n) {\n    assert(zeta_mobius_transform_detail::is_power_of_two(values.size()));\n\
    \    for (std::size_t length = 1; length < values.size(); length <<= 1) {\n  \
    \      for (\n            std::size_t block = 0;\n            block < values.size();\n\
    \            block += length << 1\n        ) {\n            for (std::size_t offset\
    \ = 0; offset < length; ++offset) {\n                T first = values[block +\
    \ offset];\n                T second = values[block + offset + length];\n    \
    \            values[block + offset] = first + second;\n                values[block\
    \ + offset + length] = first - second;\n            }\n        }\n    }\n    if\
    \ (inverse) {\n        T size = T(static_cast<long long>(values.size()));\n  \
    \      for (T& value : values) value /= size;\n    }\n}\n\ntemplate <typename\
    \ T>\nstd::vector<T> bitwise_or_convolution(\n    std::vector<T> first,\n    std::vector<T>\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ size = bitwise_convolution_detail::common_size(\n        first.size(),\n   \
    \     second.size()\n    );\n    first.resize(size);\n    second.resize(size);\n\
    \    subset_zeta_transform(first);\n    subset_zeta_transform(second);\n    first\
    \ = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    subset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_and_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    superset_zeta_transform(first);\n    superset_zeta_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    superset_mobius_transform(first);\n    return first;\n\
    }\n\ntemplate <typename T>\nstd::vector<T> bitwise_xor_convolution(\n    std::vector<T>\
    \ first,\n    std::vector<T> second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::size_t size = bitwise_convolution_detail::common_size(\n\
    \        first.size(),\n        second.size()\n    );\n    first.resize(size);\n\
    \    second.resize(size);\n    walsh_hadamard_transform(first);\n    walsh_hadamard_transform(second);\n\
    \    first = bitwise_convolution_detail::pointwise_product(\n        std::move(first),\n\
    \        second\n    );\n    walsh_hadamard_transform(first, true);\n    return\
    \ first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 1 \"math/combinatorial_sequences.hpp\"\n\n\n\n#line 7 \"math/combinatorial_sequences.hpp\"\
    \n\n#line 1 \"math/partition_function.hpp\"\n\n\n\n#line 5 \"math/partition_function.hpp\"\
    \n\n#line 8 \"math/partition_function.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\n// Returns p(0), p(1), ..., p(maximum), where p(n) is the number of integer\n\
    // partitions of n.\ntemplate <class Mint>\nstd::vector<Mint> partition_function(int\
    \ maximum) {\n    assert(maximum >= 0);\n\n    using Fps = fps::FormalPowerSeries<Mint>;\n\
    \    Fps denominator(maximum + 1);\n    denominator[0] = 1;\n    for (long long\
    \ k = 1;; k++) {\n        long long first = k * (3 * k - 1) / 2;\n        long\
    \ long second = k * (3 * k + 1) / 2;\n        if (first > maximum) break;\n\n\
    \        Mint sign = (k & 1) ? Mint(-1) : Mint(1);\n        denominator[int(first)]\
    \ += sign;\n        if (second <= maximum) denominator[int(second)] += sign;\n\
    \    }\n    return denominator.inv(maximum + 1);\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> partition_numbers(int maximum) {\n    return partition_function<Mint>(maximum);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 12 \"math/combinatorial_sequences.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ catalan_numbers(int maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ + 1 < Mint::mod());\n\n    std::vector<Mint> inverse(maximum + 2);\n    inverse[1]\
    \ = 1;\n    for (int i = 2; i <= maximum + 1; i++) {\n        inverse[i] = Mint(0)\
    \ - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod() % uint32_t(i)];\n  \
    \  }\n\n    std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    for\
    \ (int n = 0; n < maximum; n++) {\n        result[n + 1] = result[n] * Mint(2)\
    \ * Mint(2LL * n + 1) * inverse[n + 2];\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> bell_numbers(int maximum) {\n    assert(maximum\
    \ >= 0);\n    assert(static_cast<uint64_t>(maximum) < Mint::mod());\n\n    using\
    \ Fps = fps::FormalPowerSeries<Mint>;\n    Combinatorics<Mint> combinations(maximum);\n\
    \    Fps exponent(maximum + 1);\n    for (int i = 1; i <= maximum; i++) {\n  \
    \      exponent[i] = combinations.inverse_factorial(i);\n    }\n\n    Fps generating_function\
    \ = exponent.exp(maximum + 1);\n    std::vector<Mint> result(maximum + 1);\n \
    \   for (int i = 0; i <= maximum; i++) {\n        result[i] = generating_function[i]\
    \ * combinations.factorial(i);\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> stirling_numbers_second_kind(int n) {\n    assert(n\
    \ >= 0);\n    assert(static_cast<uint64_t>(n) < Mint::mod());\n\n    Combinatorics<Mint>\
    \ combinations(n);\n    std::vector<Mint> powers(n + 1);\n    std::vector<Mint>\
    \ signs(n + 1);\n    for (int i = 0; i <= n; i++) {\n        powers[i] = Mint(i).pow(n)\
    \ * combinations.inverse_factorial(i);\n        signs[i] = combinations.inverse_factorial(i);\n\
    \        if (i & 1) signs[i] = Mint(0) - signs[i];\n    }\n\n    std::vector<Mint>\
    \ result = fps::convolution(powers, signs);\n    result.resize(n + 1);\n    return\
    \ result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> derangement_numbers(int\
    \ maximum) {\n    assert(maximum >= 0);\n\n    std::vector<Mint> result(maximum\
    \ + 1);\n    result[0] = 1;\n    if (maximum >= 1) result[1] = 0;\n    for (int\
    \ n = 2; n <= maximum; n++) {\n        result[n] = Mint(n - 1) * (result[n - 1]\
    \ + result[n - 2]);\n    }\n    return result;\n}\n\n}  // namespace math\n} \
    \ // namespace m1une\n\n\n#line 1 \"math/cyclotomic_polynomial.hpp\"\n\n\n\n#line\
    \ 9 \"math/cyclotomic_polynomial.hpp\"\n\n#line 1 \"math/prime_factorization.hpp\"\
    \n\n\n\n#line 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t a, uint64_t\
    \ b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned __int128>(a)\
    \ * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t exponent,\
    \ uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0) {\n    \
    \    if (exponent & 1) result = multiply_mod(result, base, mod);\n        base\
    \ = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n    return\
    \ result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t state\
    \ = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
    \ value = state;\n    value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \    value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n    return value\
    \ ^ (value >> 31);\n}\n\n}  // namespace internal\n\ninline bool is_prime(uint64_t\
    \ value) {\n    if (value < 2) return false;\n    for (uint64_t prime : {2ULL,\
    \ 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {\n\
    \        if (value % prime == 0) return value == prime;\n    }\n\n    uint64_t\
    \ odd_part = value - 1;\n    int power_of_two = 0;\n    while ((odd_part & 1)\
    \ == 0) {\n        odd_part >>= 1;\n        power_of_two++;\n    }\n\n    for\
    \ (uint64_t base : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL})\
    \ {\n        if (base % value == 0) continue;\n        uint64_t x = internal::power_mod(base\
    \ % value, odd_part, value);\n        if (x == 1 || x == value - 1) continue;\n\
    \n        bool composite = true;\n        for (int i = 1; i < power_of_two; i++)\
    \ {\n            x = internal::multiply_mod(x, x, value);\n            if (x ==\
    \ value - 1) {\n                composite = false;\n                break;\n \
    \           }\n        }\n        if (composite) return false;\n    }\n    return\
    \ true;\n}\n\nnamespace internal {\n\ninline uint64_t pollard_rho(uint64_t value)\
    \ {\n    for (uint64_t prime : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,\
    \ 23ULL, 29ULL, 31ULL, 37ULL}) {\n        if (value % prime == 0) return prime;\n\
    \    }\n\n    while (true) {\n        const uint64_t constant = pollard_random()\
    \ % (value - 1) + 1;\n        uint64_t y = pollard_random() % (value - 1) + 1;\n\
    \        uint64_t x = 0;\n        uint64_t saved_y = 0;\n        uint64_t gcd\
    \ = 1;\n        uint64_t segment_length = 1;\n\n        auto advance = [&](uint64_t\
    \ current) {\n            return static_cast<uint64_t>(\n                (static_cast<unsigned\
    \ __int128>(multiply_mod(current, current, value)) + constant) % value);\n   \
    \     };\n\n        while (gcd == 1) {\n            x = y;\n            for (uint64_t\
    \ i = 0; i < segment_length; i++) y = advance(y);\n\n            for (uint64_t\
    \ offset = 0; offset < segment_length && gcd == 1; offset += 128) {\n        \
    \        saved_y = y;\n                uint64_t product = 1;\n               \
    \ const uint64_t block = std::min<uint64_t>(128, segment_length - offset);\n \
    \               for (uint64_t i = 0; i < block; i++) {\n                    y\
    \ = advance(y);\n                    const uint64_t difference = x > y ? x - y\
    \ : y - x;\n                    product = multiply_mod(product, difference, value);\n\
    \                }\n                gcd = std::gcd(product, value);\n        \
    \    }\n            segment_length <<= 1;\n        }\n\n        if (gcd == value)\
    \ {\n            do {\n                saved_y = advance(saved_y);\n         \
    \       const uint64_t difference = x > saved_y ? x - saved_y : saved_y - x;\n\
    \                gcd = std::gcd(difference, value);\n            } while (gcd\
    \ == 1);\n        }\n        if (gcd != value) return gcd;\n    }\n}\n\ninline\
    \ void factor_recursively(uint64_t value, std::vector<uint64_t>& factors) {\n\
    \    if (value == 1) return;\n    if (is_prime(value)) {\n        factors.push_back(value);\n\
    \        return;\n    }\n    const uint64_t divisor = pollard_rho(value);\n  \
    \  factor_recursively(divisor, factors);\n    factor_recursively(value / divisor,\
    \ factors);\n}\n\n}  // namespace internal\n\ninline std::vector<uint64_t> prime_factors(uint64_t\
    \ value) {\n    assert(value >= 1);\n    std::vector<uint64_t> result;\n    internal::factor_recursively(value,\
    \ result);\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline std::vector<std::pair<uint64_t, int>> prime_factorize(uint64_t value)\
    \ {\n    std::vector<uint64_t> factors = prime_factors(value);\n    std::vector<std::pair<uint64_t,\
    \ int>> result;\n    for (uint64_t prime : factors) {\n        if (result.empty()\
    \ || result.back().first != prime) {\n            result.emplace_back(prime, 1);\n\
    \        } else {\n            result.back().second++;\n        }\n    }\n   \
    \ return result;\n}\n\ninline std::vector<uint64_t> divisors(uint64_t value) {\n\
    \    std::vector<uint64_t> result = {1};\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        const int current_size = int(result.size());\n        uint64_t power\
    \ = 1;\n        for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n            power *= factor.first;\n            for (int i = 0; i < current_size;\
    \ i++) {\n                result.push_back(result[i] * power);\n            }\n\
    \        }\n    }\n    std::sort(result.begin(), result.end());\n    return result;\n\
    }\n\ninline uint64_t euler_phi(uint64_t value) {\n    assert(value >= 1);\n  \
    \  uint64_t result = value;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        result = result / factor.first * (factor.first - 1);\n    }\n   \
    \ return result;\n}\n\ninline int mobius(uint64_t value) {\n    assert(value >=\
    \ 1);\n    int result = 1;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.second >= 2) return 0;\n        result = -result;\n  \
    \  }\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 11 \"math/cyclotomic_polynomial.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class T = long long>\nstd::vector<T> cyclotomic_polynomial(std::uint64_t\
    \ index) {\n    assert(index >= 1);\n    if (index == 1) return {T(-1), T(1)};\n\
    \n    const std::vector<std::pair<std::uint64_t, int>> factors =\n        prime_factorize(index);\n\
    \    std::uint64_t degree = index;\n    for (const auto& factor : factors) {\n\
    \        degree = degree / factor.first * (factor.first - 1);\n    }\n    assert(degree\
    \ < std::numeric_limits<std::size_t>::max());\n\n    std::vector<T> result(static_cast<std::size_t>(degree)\
    \ + 1, T(0));\n    result[0] = T(1);\n\n    const std::size_t subset_count = std::size_t(1)\
    \ << factors.size();\n    for (std::size_t mask = 0; mask < subset_count; mask++)\
    \ {\n        std::uint64_t exponent = index;\n        bool negative_mobius = false;\n\
    \        for (std::size_t i = 0; i < factors.size(); i++) {\n            if ((mask\
    \ >> i) & 1) {\n                exponent /= factors[i].first;\n              \
    \  negative_mobius = !negative_mobius;\n            }\n        }\n        if (exponent\
    \ > degree) continue;\n\n        const std::size_t shift = static_cast<std::size_t>(exponent);\n\
    \        if (negative_mobius) {\n            // Divide by 1 - x^shift as a truncated\
    \ formal power series.\n            for (std::size_t i = shift; i <= degree; i++)\
    \ {\n                result[i] += result[i - shift];\n            }\n        }\
    \ else {\n            // Multiply by 1 - x^shift.\n            for (std::size_t\
    \ i = static_cast<std::size_t>(degree);\n                 i >= shift;\n      \
    \           i--) {\n                result[i] -= result[i - shift];\n        \
    \        if (i == shift) break;\n            }\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/generalized_floor_sum.hpp\"\
    \n\n\n\n#line 9 \"math/generalized_floor_sum.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\nusing GeneralizedFloorSumTable\
    \ =\n    std::array<std::array<T, MaxFloorPower + 1>, MaxPower + 1>;\n\nnamespace\
    \ generalized_floor_sum_detail {\n\nusing SignedWide = __int128_t;\nusing UnsignedWide\
    \ = __uint128_t;\n\ntemplate <class T>\nT from_wide(SignedWide value) {\n    bool\
    \ negative = value < 0;\n    UnsignedWide magnitude;\n    if (negative) {\n  \
    \      magnitude = static_cast<UnsignedWide>(-(value + 1));\n        ++magnitude;\n\
    \    } else {\n        magnitude = static_cast<UnsignedWide>(value);\n    }\n\n\
    \    T result = T();\n    T binary_place = T(1);\n    while (magnitude > 0) {\n\
    \        if ((magnitude & 1) != 0) result += binary_place;\n        magnitude\
    \ >>= 1;\n        if (magnitude > 0) binary_place += binary_place;\n    }\n  \
    \  return negative ? T() - result : result;\n}\n\ninline SignedWide floor_div(SignedWide\
    \ numerator, SignedWide denominator) {\n    assert(denominator > 0);\n    SignedWide\
    \ quotient = numerator / denominator;\n    if (numerator % denominator < 0) --quotient;\n\
    \    return quotient;\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\n\
    class MomentMonoid {\n   public:\n    using Table = GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>;\n\n    struct Data {\n        Table sums{};\n    \
    \    T delta_x = T();\n        T delta_y = T();\n    };\n\n    static constexpr\
    \ int MaximumDegree =\n        MaxPower > MaxFloorPower ? MaxPower : MaxFloorPower;\n\
    \n    MomentMonoid() {\n        binomial_[0][0] = T(1);\n        for (int degree\
    \ = 0; degree < MaximumDegree; ++degree) {\n            for (int index = 0; index\
    \ <= degree; ++index) {\n                binomial_[degree + 1][index] += binomial_[degree][index];\n\
    \                binomial_[degree + 1][index + 1] +=\n                    binomial_[degree][index];\n\
    \            }\n        }\n    }\n\n    const T& binomial(int n, int k) const\
    \ {\n        assert(0 <= k && k <= n && n <= MaximumDegree);\n        return binomial_[n][k];\n\
    \    }\n\n    Data unit() const {\n        return Data();\n    }\n\n    Data x_step()\
    \ const {\n        Data result;\n        result.sums[0][0] = T(1);\n        result.delta_x\
    \ = T(1);\n        return result;\n    }\n\n    Data y_step() const {\n      \
    \  Data result;\n        result.delta_y = T(1);\n        return result;\n    }\n\
    \n    Data concatenate(Data left, Data right) const {\n        std::array<T, MaxPower\
    \ + 1> x_powers{};\n        std::array<T, MaxFloorPower + 1> y_powers{};\n   \
    \     x_powers[0] = T(1);\n        y_powers[0] = T(1);\n        for (int power\
    \ = 0; power < MaxPower; ++power) {\n            x_powers[power + 1] = x_powers[power]\
    \ * left.delta_x;\n        }\n        for (int power = 0; power < MaxFloorPower;\
    \ ++power) {\n            y_powers[power + 1] = y_powers[power] * left.delta_y;\n\
    \        }\n\n        // Shift the y-coordinate of every sampled x-step in the\
    \ right path.\n        for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n\
    \            for (int old_power = MaxFloorPower; old_power >= 0; --old_power)\
    \ {\n                T source = right.sums[x_power][old_power];\n            \
    \    for (int new_power = old_power + 1;\n                     new_power <= MaxFloorPower;\n\
    \                     ++new_power) {\n                    right.sums[x_power][new_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            y_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        // Shift x, then append all samples from the\
    \ right path.\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int old_power = 0; old_power <= MaxPower; ++old_power) {\n\
    \                T source = right.sums[old_power][y_power];\n                for\
    \ (int new_power = old_power;\n                     new_power <= MaxPower;\n \
    \                    ++new_power) {\n                    left.sums[new_power][y_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            x_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        left.delta_x += right.delta_x;\n        left.delta_y\
    \ += right.delta_y;\n        return left;\n    }\n\n   private:\n    std::array<std::array<T,\
    \ MaximumDegree + 1>, MaximumDegree + 1>\n        binomial_{};\n};\n\ntemplate\
    \ <class Monoid>\ntypename Monoid::Data monoid_power(\n    const Monoid& monoid,\n\
    \    typename Monoid::Data base,\n    UnsignedWide exponent\n) {\n    typename\
    \ Monoid::Data result = monoid.unit();\n    while (exponent > 0) {\n        if\
    \ ((exponent & 1) != 0) {\n            result = monoid.concatenate(std::move(result),\
    \ base);\n        }\n        exponent >>= 1;\n        if (exponent > 0) {\n  \
    \          base = monoid.concatenate(base, base);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Monoid>\ntypename Monoid::Data floor_path_product(\n\
    \    const Monoid& monoid,\n    UnsignedWide n,\n    UnsignedWide a,\n    UnsignedWide\
    \ b,\n    UnsignedWide modulus\n) {\n    assert(modulus > 0);\n    UnsignedWide\
    \ height = (a * n + b) / modulus;\n    typename Monoid::Data x = monoid.x_step();\n\
    \    typename Monoid::Data y = monoid.y_step();\n    typename Monoid::Data prefix\
    \ = monoid.unit();\n    typename Monoid::Data suffix = monoid.unit();\n\n    while\
    \ (true) {\n        UnsignedWide slope_quotient = a / modulus;\n        UnsignedWide\
    \ intercept_quotient = b / modulus;\n        a %= modulus;\n        b %= modulus;\n\
    \n        x = monoid.concatenate(\n            std::move(x),\n            monoid_power(monoid,\
    \ y, slope_quotient)\n        );\n        prefix = monoid.concatenate(\n     \
    \       std::move(prefix),\n            monoid_power(monoid, y, intercept_quotient)\n\
    \        );\n        height -= slope_quotient * n + intercept_quotient;\n    \
    \    if (height == 0) break;\n\n        assert(a > 0);\n        UnsignedWide boundary\
    \ =\n            (modulus * height - b - 1) / a + 1;\n        suffix = monoid.concatenate(\n\
    \            y,\n            monoid.concatenate(\n                monoid_power(monoid,\
    \ x, n - boundary),\n                std::move(suffix)\n            )\n      \
    \  );\n        b = modulus - b - 1 + a;\n        n = height - 1;\n        height\
    \ = boundary;\n        std::swap(modulus, a);\n        std::swap(x, y);\n    }\n\
    \n    x = monoid_power(monoid, x, n);\n    return monoid.concatenate(\n      \
    \  monoid.concatenate(std::move(prefix), std::move(x)),\n        std::move(suffix)\n\
    \    );\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\nGeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>\nnonnegative_slope_table(\n    const MomentMonoid<T,\
    \ MaxPower, MaxFloorPower>& monoid,\n    SignedWide n,\n    SignedWide modulus,\n\
    \    SignedWide a,\n    SignedWide b\n) {\n    assert(n >= 0 && modulus > 0 &&\
    \ a >= 0);\n    SignedWide y_offset = floor_div(b, modulus);\n    SignedWide normalized_b\
    \ = b - y_offset * modulus;\n\n    auto path = floor_path_product(\n        monoid,\n\
    \        static_cast<UnsignedWide>(n),\n        static_cast<UnsignedWide>(a),\n\
    \        static_cast<UnsignedWide>(normalized_b),\n        static_cast<UnsignedWide>(modulus)\n\
    \    );\n\n    std::array<T, MaxFloorPower + 1> offset_powers{};\n    offset_powers[0]\
    \ = T(1);\n    T offset = from_wide<T>(y_offset);\n    for (int power = 0; power\
    \ < MaxFloorPower; ++power) {\n        offset_powers[power + 1] = offset_powers[power]\
    \ * offset;\n    }\n\n    GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\
    \ result{};\n    for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n   \
    \     for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {\n         \
    \   for (int inner_power = 0;\n                 inner_power <= y_power;\n    \
    \             ++inner_power) {\n                result[x_power][y_power] +=\n\
    \                    monoid.binomial(y_power, inner_power) *\n               \
    \     offset_powers[y_power - inner_power] *\n                    path.sums[x_power][inner_power];\n\
    \            }\n        }\n    }\n    return result;\n}\n\n}  // namespace generalized_floor_sum_detail\n\
    \n// Returns every sum of x^p * floor((a*x+b)/mod)^q for 0 <= x < n,\n// 0 <=\
    \ p <= MaxPower, and 0 <= q <= MaxFloorPower.\ntemplate <class T, int MaxPower,\
    \ int MaxFloorPower, class I>\nGeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\n\
    generalized_floor_sum_table(I n, I mod, I a, I b) {\n    static_assert(MaxPower\
    \ >= 0 && MaxFloorPower >= 0);\n    static_assert(\n        std::is_integral_v<I>\
    \ && std::is_signed_v<I> && sizeof(I) <= 8,\n        \"generalized_floor_sum_table\
    \ requires signed integer arguments\"\n    );\n    assert(n >= 0);\n    assert(mod\
    \ > 0);\n\n    namespace detail = generalized_floor_sum_detail;\n    using Monoid\
    \ = detail::MomentMonoid<T, MaxPower, MaxFloorPower>;\n    static const Monoid\
    \ monoid;\n\n    detail::SignedWide wide_n = n;\n    detail::SignedWide wide_mod\
    \ = mod;\n    detail::SignedWide wide_a = a;\n    detail::SignedWide wide_b =\
    \ b;\n    if (wide_n == 0) {\n        return GeneralizedFloorSumTable<T, MaxPower,\
    \ MaxFloorPower>();\n    }\n    if (wide_a >= 0) {\n        return detail::nonnegative_slope_table(\n\
    \            monoid,\n            wide_n,\n            wide_mod,\n           \
    \ wide_a,\n            wide_b\n        );\n    }\n\n    // Substitute x = n -\
    \ 1 - t to make the slope nonnegative.\n    auto reflected = detail::nonnegative_slope_table(\n\
    \        monoid,\n        wide_n,\n        wide_mod,\n        -wide_a,\n     \
    \   wide_a * (wide_n - 1) + wide_b\n    );\n    std::array<T, MaxPower + 1> offset_powers{};\n\
    \    offset_powers[0] = T(1);\n    T offset = detail::from_wide<T>(wide_n - 1);\n\
    \    for (int power = 0; power < MaxPower; ++power) {\n        offset_powers[power\
    \ + 1] = offset_powers[power] * offset;\n    }\n\n    GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower> result{};\n    for (int x_power = 0; x_power <= MaxPower;\
    \ ++x_power) {\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int inner_power = 0;\n                 inner_power <= x_power;\n\
    \                 ++inner_power) {\n                T coefficient =\n        \
    \            monoid.binomial(x_power, inner_power) *\n                    offset_powers[x_power\
    \ - inner_power];\n                if ((inner_power & 1) != 0) coefficient = T()\
    \ - coefficient;\n                result[x_power][y_power] +=\n              \
    \      coefficient * reflected[inner_power][y_power];\n            }\n       \
    \ }\n    }\n    return result;\n}\n\ntemplate <class T, int Power, int FloorPower,\
    \ class I>\nT generalized_floor_sum(I n, I mod, I a, I b) {\n    return generalized_floor_sum_table<T,\
    \ Power, FloorPower>(n, mod, a, b)\n        [Power][FloorPower];\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/integer_arithmetic.hpp\"\n\n\
    \n\n#line 9 \"math/integer_arithmetic.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nnamespace integer_arithmetic_detail {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr std::optional<T> checked_multiply(T first, T second) {\n \
    \   constexpr T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum\
    \ = std::numeric_limits<T>::max();\n\n    if constexpr (std::unsigned_integral<T>)\
    \ {\n        if (second != 0 && maximum / second < first) return std::nullopt;\n\
    \    } else {\n        if (0 < first) {\n            if (0 < second) {\n     \
    \           if (maximum / second < first) return std::nullopt;\n            }\
    \ else if (second < minimum / first) {\n                return std::nullopt;\n\
    \            }\n        } else if (first < 0) {\n            if (0 < second) {\n\
    \                if (first < minimum / second) return std::nullopt;\n        \
    \    } else if (second < maximum / first) {\n                return std::nullopt;\n\
    \            }\n        }\n    }\n    return T(first * second);\n}\n\n}  // namespace\
    \ integer_arithmetic_detail\n\n// Returns floor(sqrt(value)) exactly, without\
    \ floating-point arithmetic.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ assert(0 <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n \
    \   T high = value / 2 + 1;\n    while (low < high) {\n        T middle = low\
    \ + (high - low + 1) / 2;\n        if (middle <= value / middle) {\n         \
    \   low = middle;\n        } else {\n            high = middle - 1;\n        }\n\
    \    }\n    return low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T floor_sqrt(T value) {\n    return isqrt(value);\n}\n\n//\
    \ Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nconstexpr\
    \ T ceil_sqrt(T value) {\n    T result = isqrt(value);\n    if (result == 0) return\
    \ 0;\n    if (result != 0 && value / result == result && value % result == 0)\
    \ {\n        return result;\n    }\n    return result + 1;\n}\n\n// Returns base^exponent,\
    \ or nullopt when the result does not fit in T.\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr std::optional<T> checked_ipow(T base, Exponent exponent)\
    \ {\n    T result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ {\n            auto product =\n                integer_arithmetic_detail::checked_multiply(result,\
    \ base);\n            if (!product.has_value()) return std::nullopt;\n       \
    \     result = *product;\n        }\n        exponent >>= 1;\n        if (exponent\
    \ != 0) {\n            auto square =\n                integer_arithmetic_detail::checked_multiply(base,\
    \ base);\n            if (!square.has_value()) return std::nullopt;\n        \
    \    base = *square;\n        }\n    }\n    return result;\n}\n\ntemplate <std::integral\
    \ T, std::unsigned_integral Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Exponent>, bool>\n)\nconstexpr\
    \ std::optional<T> checked_integer_pow(T base, Exponent exponent) {\n    return\
    \ checked_ipow(base, exponent);\n}\n\n// Returns base^exponent. The result must\
    \ be representable by T.\ntemplate <std::integral T, std::unsigned_integral Exponent>\n\
    requires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T ipow(T base, Exponent exponent) {\n    std::optional<T>\
    \ result = checked_ipow(base, exponent);\n    assert(result.has_value());\n  \
    \  return result.value_or(T());\n}\n\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T integer_pow(T base, Exponent exponent) {\n    return ipow(base,\
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"\
    math/lucas.hpp\"\n\n\n\n#line 7 \"math/lucas.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <class Mint>\nstruct Lucas {\n   private:\n    std::vector<Mint>\
    \ _factorial;\n    std::vector<Mint> _inverse_factorial;\n\n    Mint small_binom(uint32_t\
    \ n, uint32_t k) const {\n        if (k > n) return Mint(0);\n        return _factorial[n]\
    \ * _inverse_factorial[k] * _inverse_factorial[n - k];\n    }\n\n   public:\n\
    \    Lucas() {\n        const uint32_t prime = Mint::mod();\n        assert(2\
    \ <= prime);\n        _factorial.resize(prime);\n        _inverse_factorial.resize(prime);\n\
    \        _factorial[0] = Mint(1);\n        for (uint32_t i = 1; i < prime; i++)\
    \ {\n            _factorial[i] = _factorial[i - 1] * Mint(i);\n        }\n   \
    \     _inverse_factorial[prime - 1] = _factorial[prime - 1].inv();\n        for\
    \ (uint32_t i = prime - 1; i > 0; i--) {\n            _inverse_factorial[i - 1]\
    \ = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    uint32_t prime()\
    \ const {\n        return Mint::mod();\n    }\n\n    Mint binom(uint64_t n, uint64_t\
    \ k) const {\n        if (k > n) return Mint(0);\n        const uint64_t modulus\
    \ = Mint::mod();\n        Mint result = Mint(1);\n        while (n > 0 || k >\
    \ 0) {\n            uint32_t n_digit = uint32_t(n % modulus);\n            uint32_t\
    \ k_digit = uint32_t(k % modulus);\n            if (k_digit > n_digit) return\
    \ Mint(0);\n            result *= small_binom(n_digit, k_digit);\n           \
    \ n /= modulus;\n            k /= modulus;\n        }\n        return result;\n\
    \    }\n\n    Mint operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\ntemplate <class Mint>\nusing LucasTheorem = Lucas<Mint>;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/fps/all.hpp\"\
    \n\n\n\n#line 1 \"math/fps/convolution_ll.hpp\"\n\n\n\n#line 8 \"math/fps/convolution_ll.hpp\"\
    \n\n#line 11 \"math/fps/convolution_ll.hpp\"\n\nnamespace m1une {\nnamespace fps\
    \ {\n\n// Exact convolution of signed 64-bit coefficients.\n// Every result coefficient\
    \ must fit in long long.\ninline std::vector<long long> convolution_ll(\n    const\
    \ std::vector<long long>& first,\n    const std::vector<long long>& second\n)\
    \ {\n    if (first.empty() || second.empty()) return {};\n    std::size_t result_size\
    \ = first.size() + second.size() - 1;\n    assert(result_size <= (std::size_t(1)\
    \ << 24));\n\n    using Mint1 = math::ModInt<167772161>;\n    using Mint2 = math::ModInt<469762049>;\n\
    \    using Mint3 = math::ModInt<754974721>;\n\n    auto convolve = [&]<class Mint>()\
    \ {\n        std::vector<Mint> converted_first(first.size());\n        std::vector<Mint>\
    \ converted_second(second.size());\n        for (int index = 0; index < int(first.size());\
    \ index++) {\n            converted_first[index] = Mint(first[index]);\n     \
    \   }\n        for (int index = 0; index < int(second.size()); index++) {\n  \
    \          converted_second[index] = Mint(second[index]);\n        }\n       \
    \ return convolution(converted_first, converted_second);\n    };\n\n    std::vector<Mint1>\
    \ result1 = convolve.template operator()<Mint1>();\n    std::vector<Mint2> result2\
    \ = convolve.template operator()<Mint2>();\n    std::vector<Mint3> result3 = convolve.template\
    \ operator()<Mint3>();\n\n    static const std::uint64_t inverse_mod1_mod2 =\n\
    \        Mint2(Mint1::mod()).inv().val();\n    static const std::uint64_t mod1_mod2\
    \ =\n        std::uint64_t(Mint1::mod()) * Mint2::mod();\n    static const std::uint64_t\
    \ inverse_mod1_mod2_mod3 =\n        Mint3(mod1_mod2 % Mint3::mod()).inv().val();\n\
    \    static const unsigned __int128 crt_modulus =\n        static_cast<unsigned\
    \ __int128>(mod1_mod2) * Mint3::mod();\n\n    std::vector<long long> result(result_size);\n\
    \    for (int index = 0; index < int(result_size); index++) {\n        std::uint64_t\
    \ residue1 = result1[index].val();\n        std::uint64_t residue2 = result2[index].val();\n\
    \        std::uint64_t residue3 = result3[index].val();\n\n        std::uint64_t\
    \ second_digit =\n            (residue2 + Mint2::mod() - residue1 % Mint2::mod())\
    \ %\n            Mint2::mod();\n        second_digit = second_digit * inverse_mod1_mod2\
    \ % Mint2::mod();\n        std::uint64_t first_two =\n            residue1 + std::uint64_t(Mint1::mod())\
    \ * second_digit;\n\n        std::uint64_t third_digit =\n            (residue3\
    \ + Mint3::mod() - first_two % Mint3::mod()) %\n            Mint3::mod();\n  \
    \      third_digit =\n            third_digit * inverse_mod1_mod2_mod3 % Mint3::mod();\n\
    \n        unsigned __int128 reconstructed =\n            first_two + static_cast<unsigned\
    \ __int128>(mod1_mod2) * third_digit;\n        __int128 centered = reconstructed\
    \ <= crt_modulus / 2\n                                ? static_cast<__int128>(reconstructed)\n\
    \                                : -static_cast<__int128>(crt_modulus - reconstructed);\n\
    \        assert(std::numeric_limits<long long>::min() <= centered);\n        assert(centered\
    \ <= std::numeric_limits<long long>::max());\n        result[index] = static_cast<long\
    \ long>(centered);\n    }\n    return result;\n}\n\n}  // namespace fps\n}  //\
    \ namespace m1une\n\n\n#line 1 \"math/fps/floating_point_convolution.hpp\"\n\n\
    \n\n#line 5 \"math/fps/floating_point_convolution.hpp\"\n#include <bit>\n#include\
    \ <cmath>\n#include <complex>\n#line 9 \"math/fps/floating_point_convolution.hpp\"\
    \n#include <numbers>\n#line 12 \"math/fps/floating_point_convolution.hpp\"\n\n\
    namespace m1une {\nnamespace fps {\n\nnamespace floating_point_convolution_detail\
    \ {\n\ntemplate <std::floating_point Real>\nvoid fft(std::vector<std::complex<Real>>&\
    \ values, bool inverse) {\n    int size = int(values.size());\n    for (int index\
    \ = 1, reversed = 0; index < size; ++index) {\n        int bit = size >> 1;\n\
    \        while (reversed & bit) {\n            reversed ^= bit;\n            bit\
    \ >>= 1;\n        }\n        reversed ^= bit;\n        if (index < reversed) std::swap(values[index],\
    \ values[reversed]);\n    }\n\n    for (int length = 2; length <= size; length\
    \ <<= 1) {\n        Real angle = Real(2) * std::numbers::pi_v<Real> / Real(length);\n\
    \        if (inverse) angle = -angle;\n        std::complex<Real> step(std::cos(angle),\
    \ std::sin(angle));\n        int half = length >> 1;\n        for (int offset\
    \ = 0; offset < size; offset += length) {\n            std::complex<Real> root(1,\
    \ 0);\n            for (int index = 0; index < half; ++index) {\n            \
    \    std::complex<Real> even = values[offset + index];\n                std::complex<Real>\
    \ odd = values[offset + index + half] * root;\n                values[offset +\
    \ index] = even + odd;\n                values[offset + index + half] = even -\
    \ odd;\n                root *= step;\n            }\n        }\n    }\n\n   \
    \ if (inverse) {\n        Real inverse_size = Real(1) / Real(size);\n        for\
    \ (auto& value : values) value *= inverse_size;\n    }\n}\n\ntemplate <std::floating_point\
    \ Real>\nstd::vector<std::complex<Real>> complex_convolution(const std::vector<std::complex<Real>>&\
    \ first,\n                                                    const std::vector<std::complex<Real>>&\
    \ second) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ result_size = first.size() + second.size() - 1;\n    std::size_t size = std::bit_ceil(result_size);\n\
    \    std::vector<std::complex<Real>> transformed_first(size);\n    std::vector<std::complex<Real>>\
    \ transformed_second(size);\n    std::copy(first.begin(), first.end(), transformed_first.begin());\n\
    \    std::copy(second.begin(), second.end(), transformed_second.begin());\n\n\
    \    fft(transformed_first, false);\n    fft(transformed_second, false);\n   \
    \ for (std::size_t index = 0; index < size; ++index) {\n        transformed_first[index]\
    \ *= transformed_second[index];\n    }\n    fft(transformed_first, true);\n  \
    \  transformed_first.resize(result_size);\n    return transformed_first;\n}\n\n\
    }  // namespace floating_point_convolution_detail\n\n// Convolution of complex\
    \ floating-point coefficients.\ntemplate <std::floating_point Real>\nstd::vector<std::complex<Real>>\
    \ convolution_fft(const std::vector<std::complex<Real>>& first,\n            \
    \                                    const std::vector<std::complex<Real>>& second)\
    \ {\n    return floating_point_convolution_detail::complex_convolution(first,\
    \ second);\n}\n\n// Convolution of real floating-point coefficients.\ntemplate\
    \ <std::floating_point Real>\nstd::vector<Real> convolution_fft(const std::vector<Real>&\
    \ first, const std::vector<Real>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<std::complex<Real>> complex_first(first.size());\n\
    \    std::vector<std::complex<Real>> complex_second(second.size());\n    for (std::size_t\
    \ index = 0; index < first.size(); ++index) {\n        complex_first[index] =\
    \ std::complex<Real>(first[index], 0);\n    }\n    for (std::size_t index = 0;\
    \ index < second.size(); ++index) {\n        complex_second[index] = std::complex<Real>(second[index],\
    \ 0);\n    }\n    auto result = floating_point_convolution_detail::complex_convolution(complex_first,\
    \ complex_second);\n    std::vector<Real> real_result(result.size());\n    for\
    \ (std::size_t index = 0; index < result.size(); ++index) {\n        real_result[index]\
    \ = result[index].real();\n    }\n    return real_result;\n}\n\n// Uses long-double\
    \ FFT and rounds each coefficient to the nearest integer.\ntemplate <std::integral\
    \ Integer>\nstd::vector<Integer> convolution_round(const std::vector<Integer>&\
    \ first, const std::vector<Integer>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<long double> real_first(first.begin(), first.end());\n\
    \    std::vector<long double> real_second(second.begin(), second.end());\n   \
    \ std::vector<long double> real_result = convolution_fft(real_first, real_second);\n\
    \    std::vector<Integer> result(real_result.size());\n    for (std::size_t index\
    \ = 0; index < result.size(); ++index) {\n        result[index] = static_cast<Integer>(std::round(real_result[index]));\n\
    \    }\n    return result;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\
    \n#line 1 \"math/fps/half_gcd.hpp\"\n\n\n\n#line 7 \"math/fps/half_gcd.hpp\"\n\
    \n#line 9 \"math/fps/half_gcd.hpp\"\n\nnamespace m1une {\nnamespace fps {\n\n\
    template <class Mint>\nstruct PolynomialMatrix2x2 {\n    using Fps = FormalPowerSeries<Mint>;\n\
    \n    Fps a00;\n    Fps a01;\n    Fps a10;\n    Fps a11;\n\n    static PolynomialMatrix2x2\
    \ identity() {\n        return PolynomialMatrix2x2{Fps(1, Mint(1)), Fps(), Fps(),\
    \ Fps(1, Mint(1))};\n    }\n\n    std::pair<Fps, Fps> apply(const Fps& first,\
    \ const Fps& second) const {\n        Fps result_first = a00 * first + a01 * second;\n\
    \        Fps result_second = a10 * first + a11 * second;\n        result_first.shrink();\n\
    \        result_second.shrink();\n        return std::make_pair(std::move(result_first),\
    \ std::move(result_second));\n    }\n\n    friend PolynomialMatrix2x2 operator*(const\
    \ PolynomialMatrix2x2& lhs,\n                                          const PolynomialMatrix2x2&\
    \ rhs) {\n        PolynomialMatrix2x2 result;\n        result.a00 = lhs.a00 *\
    \ rhs.a00 + lhs.a01 * rhs.a10;\n        result.a01 = lhs.a00 * rhs.a01 + lhs.a01\
    \ * rhs.a11;\n        result.a10 = lhs.a10 * rhs.a00 + lhs.a11 * rhs.a10;\n  \
    \      result.a11 = lhs.a10 * rhs.a01 + lhs.a11 * rhs.a11;\n        result.a00.shrink();\n\
    \        result.a01.shrink();\n        result.a10.shrink();\n        result.a11.shrink();\n\
    \        return result;\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nvoid polynomial_euclidean_step(PolynomialMatrix2x2<Mint>& matrix,\n \
    \                              std::pair<FormalPowerSeries<Mint>,\n          \
    \                               FormalPowerSeries<Mint>>& values) {\n    using\
    \ Fps = FormalPowerSeries<Mint>;\n    assert(!values.second.empty());\n\n    auto\
    \ division = values.first.divmod(values.second);\n    Fps next_a10 = matrix.a00\
    \ - matrix.a10 * division.first;\n    Fps next_a11 = matrix.a01 - matrix.a11 *\
    \ division.first;\n    next_a10.shrink();\n    next_a11.shrink();\n\n    matrix.a00\
    \ = std::move(matrix.a10);\n    matrix.a01 = std::move(matrix.a11);\n    matrix.a10\
    \ = std::move(next_a10);\n    matrix.a11 = std::move(next_a11);\n    values.first\
    \ = std::move(values.second);\n    values.second = std::move(division.second);\n\
    }\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint> half_gcd_impl(\n    std::pair<FormalPowerSeries<Mint>,\
    \ FormalPowerSeries<Mint>> values) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n\
    \n    const int first_size = int(values.first.size());\n    const int half_size\
    \ = (first_size + 1) / 2;\n    if (int(values.second.size()) <= half_size) return\
    \ Matrix::identity();\n\n    Matrix first_matrix =\n        half_gcd_impl<Mint>(std::make_pair(values.first\
    \ >> half_size, values.second >> half_size));\n    values = first_matrix.apply(values.first,\
    \ values.second);\n    if (int(values.second.size()) <= half_size) return first_matrix;\n\
    \n    polynomial_euclidean_step(first_matrix, values);\n    if (int(values.second.size())\
    \ <= half_size) return first_matrix;\n\n    const int first_degree = int(values.first.size())\
    \ - 1;\n    const int shift = 2 * half_size - first_degree;\n    assert(shift\
    \ >= 0);\n    values.first >>= shift;\n    values.second >>= shift;\n    return\
    \ half_gcd_impl<Mint>(std::move(values)) * first_matrix;\n}\n\ntemplate <class\
    \ Mint>\nPolynomialMatrix2x2<Mint> polynomial_gcd_matrix(FormalPowerSeries<Mint>\
    \ first,\n                                                FormalPowerSeries<Mint>\
    \ second) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n    first.shrink();\n\
    \    second.shrink();\n\n    if (first.size() < second.size()) {\n        Matrix\
    \ result = polynomial_gcd_matrix(std::move(second), std::move(first));\n     \
    \   std::swap(result.a00, result.a01);\n        std::swap(result.a10, result.a11);\n\
    \        return result;\n    }\n\n    std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>>\
    \ values(\n        std::move(first), std::move(second));\n    Matrix result =\
    \ Matrix::identity();\n    while (true) {\n        Matrix block = half_gcd_impl<Mint>(values);\n\
    \        values = block.apply(values.first, values.second);\n        if (values.second.empty())\
    \ return block * result;\n\n        polynomial_euclidean_step(block, values);\n\
    \        if (values.second.empty()) return block * result;\n        result = block\
    \ * result;\n    }\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint>\
    \ half_gcd(FormalPowerSeries<Mint> first,\n                                  \
    \ FormalPowerSeries<Mint> second) {\n    first.shrink();\n    second.shrink();\n\
    \    assert(first.size() >= second.size());\n    return internal::half_gcd_impl<Mint>(std::make_pair(std::move(first),\
    \ std::move(second)));\n}\n\ntemplate <class Mint>\nstruct PolynomialExtendedGcdResult\
    \ {\n    FormalPowerSeries<Mint> gcd;\n    FormalPowerSeries<Mint> x;\n    FormalPowerSeries<Mint>\
    \ y;\n};\n\ntemplate <class Mint>\nPolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(\n\
    \    const FormalPowerSeries<Mint>& first, const FormalPowerSeries<Mint>& second)\
    \ {\n    PolynomialMatrix2x2<Mint> matrix = internal::polynomial_gcd_matrix(first,\
    \ second);\n    auto values = matrix.apply(first, second);\n\n    if (!values.first.empty())\
    \ {\n        const Mint inverse_leading = values.first.back().inv();\n       \
    \ values.first *= inverse_leading;\n        matrix.a00 *= inverse_leading;\n \
    \       matrix.a01 *= inverse_leading;\n    }\n    return PolynomialExtendedGcdResult<Mint>{std::move(values.first),\
    \ std::move(matrix.a00),\n                                             std::move(matrix.a01)};\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_gcd(const FormalPowerSeries<Mint>&\
    \ first,\n                                       const FormalPowerSeries<Mint>&\
    \ second) {\n    return polynomial_extended_gcd(first, second).gcd;\n}\n\ntemplate\
    \ <class Mint>\nstd::optional<FormalPowerSeries<Mint>> polynomial_inv_mod(\n \
    \   const FormalPowerSeries<Mint>& polynomial, FormalPowerSeries<Mint> modulus)\
    \ {\n    modulus.shrink();\n    assert(!modulus.empty());\n    auto result = polynomial_extended_gcd(polynomial,\
    \ modulus);\n    if (result.gcd.size() != 1) return std::nullopt;\n    return\
    \ result.x % modulus;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/fps/lagrange_inversion.hpp\"\n\n\n\n#line 7 \"math/fps/lagrange_inversion.hpp\"\
    \n\n#line 9 \"math/fps/lagrange_inversion.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\ntemplate <class Mint>\nMint lagrange_inversion_coefficient(const FormalPowerSeries<Mint>&\
    \ phi, int degree) {\n    assert(1 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    assert(!phi.empty() && phi[0] != Mint(0));\n\n    FormalPowerSeries<Mint>\
    \ power = phi.pre(degree).pow(degree, degree);\n    return power[degree - 1] /\
    \ Mint(degree);\n}\n\ntemplate <class Mint>\nMint lagrange_burmann_coefficient(const\
    \ FormalPowerSeries<Mint>& phi,\n                                  const FormalPowerSeries<Mint>&\
    \ outer, int degree) {\n    assert(0 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    if (degree == 0) return outer.empty() ? Mint(0) : outer[0];\n    assert(!phi.empty()\
    \ && phi[0] != Mint(0));\n\n    FormalPowerSeries<Mint> power = phi.pre(degree).pow(degree,\
    \ degree);\n    Mint result = 0;\n    int limit = std::min(degree, int(outer.size())\
    \ - 1);\n    for (int i = 1; i <= limit; i++) {\n        result += Mint(i) * outer[i]\
    \ * power[degree - i];\n    }\n    return result / Mint(degree);\n}\n\ntemplate\
    \ <class Mint>\nMint compositional_inverse_coefficient(const FormalPowerSeries<Mint>&\
    \ f, int degree) {\n    assert(0 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    assert(2 <= int(f.size()) && f[0] == Mint(0) && f[1] != Mint(0));\n    if\
    \ (degree == 0) return Mint(0);\n\n    FormalPowerSeries<Mint> divided(degree);\n\
    \    for (int i = 0; i < degree && i + 1 < int(f.size()); i++) divided[i] = f[i\
    \ + 1];\n    FormalPowerSeries<Mint> phi = divided.inv(degree);\n    return lagrange_inversion_coefficient(phi,\
    \ degree);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/linear_recurrence.hpp\"\
    \n\n\n\n#line 7 \"math/fps/linear_recurrence.hpp\"\n\n#line 9 \"math/fps/linear_recurrence.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nMint coefficient_of_rational(FormalPowerSeries<Mint>\
    \ numerator,\n                             FormalPowerSeries<Mint> denominator,\
    \ uint64_t index) {\n    using Fps = FormalPowerSeries<Mint>;\n    assert(!denominator.empty()\
    \ && denominator[0] != Mint(0));\n\n    while (index > 0) {\n        Fps denominator_negative\
    \ = denominator;\n        for (int i = 1; i < int(denominator_negative.size());\
    \ i += 2) {\n            denominator_negative[i] = Mint(0) - denominator_negative[i];\n\
    \        }\n\n        Fps numerator_product = numerator * denominator_negative;\n\
    \        Fps denominator_product = denominator * denominator_negative;\n     \
    \   Fps next_numerator;\n        Fps next_denominator;\n        next_numerator.reserve((numerator_product.size()\
    \ + 1) / 2);\n        next_denominator.reserve((denominator_product.size() + 1)\
    \ / 2);\n        for (int i = int(index & 1); i < int(numerator_product.size());\
    \ i += 2) {\n            next_numerator.emplace_back(numerator_product[i]);\n\
    \        }\n        for (int i = 0; i < int(denominator_product.size()); i +=\
    \ 2) {\n            next_denominator.emplace_back(denominator_product[i]);\n \
    \       }\n        numerator = std::move(next_numerator);\n        denominator\
    \ = std::move(next_denominator);\n        index >>= 1;\n    }\n    return numerator.empty()\
    \ ? Mint(0) : numerator[0] / denominator[0];\n}\n\ntemplate <class Mint>\nMint\
    \ linear_recurrence_kth(const std::vector<Mint>& initial,\n                  \
    \         const std::vector<Mint>& recurrence, uint64_t index) {\n    using Fps\
    \ = FormalPowerSeries<Mint>;\n    assert(!initial.empty() && initial.size() ==\
    \ recurrence.size());\n    if (index < initial.size()) return initial[index];\n\
    \n    const int order = int(recurrence.size());\n    Fps denominator(order + 1);\n\
    \    denominator[0] = 1;\n    for (int i = 0; i < order; i++) denominator[i +\
    \ 1] = Mint(0) - recurrence[i];\n    Fps numerator = (Fps(initial) * denominator).pre(order);\n\
    \    return coefficient_of_rational(std::move(numerator), std::move(denominator),\
    \ index);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/multipoint_evaluation.hpp\"\
    \n\n\n\n#line 6 \"math/fps/multipoint_evaluation.hpp\"\n\n#line 8 \"math/fps/multipoint_evaluation.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct SubproductTree\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n\n   private:\n    int point_count_;\n\
    \    int leaf_count_;\n    std::vector<Mint> points_;\n    std::vector<Fps> product_;\n\
    \n   public:\n    explicit SubproductTree(const std::vector<Mint>& points)\n \
    \       : point_count_(points.size()), leaf_count_(1), points_(points) {\n   \
    \     while (leaf_count_ < point_count_) leaf_count_ <<= 1;\n        product_.resize(leaf_count_\
    \ << 1);\n        for (int i = 0; i < leaf_count_; i++) {\n            if (i <\
    \ point_count_) {\n                product_[leaf_count_ + i].resize(2);\n    \
    \            product_[leaf_count_ + i][0] = Mint(0) - points_[i];\n          \
    \      product_[leaf_count_ + i][1] = Mint(1);\n            } else {\n       \
    \         product_[leaf_count_ + i].resize(1, Mint(1));\n            }\n     \
    \   }\n        for (int node = leaf_count_ - 1; node > 0; node--) {\n        \
    \    product_[node] = product_[node << 1] * product_[node << 1 | 1];\n       \
    \ }\n    }\n\n    int size() const {\n        return point_count_;\n    }\n\n\
    \    const Fps& product() const {\n        return product_[1];\n    }\n\n    std::vector<Mint>\
    \ evaluate(const Fps& polynomial) const {\n        std::vector<Mint> result(point_count_);\n\
    \        if (point_count_ == 0) return result;\n\n        std::vector<Fps> remainder(leaf_count_\
    \ << 1);\n        remainder[1] = polynomial % product_[1];\n        for (int node\
    \ = 1; node < leaf_count_; node++) {\n            remainder[node << 1] = remainder[node]\
    \ % product_[node << 1];\n            remainder[node << 1 | 1] = remainder[node]\
    \ % product_[node << 1 | 1];\n        }\n        for (int i = 0; i < point_count_;\
    \ i++) {\n            const Fps& value = remainder[leaf_count_ + i];\n       \
    \     result[i] = value.empty() ? Mint(0) : value[0];\n        }\n        return\
    \ result;\n    }\n\n    Fps interpolate(const std::vector<Mint>& values) const\
    \ {\n        assert(int(values.size()) == point_count_);\n        if (point_count_\
    \ == 0) return {};\n\n        std::vector<Mint> derivative_values = evaluate(product_[1].derivative());\n\
    \        std::vector<Fps> polynomial(leaf_count_ << 1);\n        for (int i =\
    \ 0; i < leaf_count_; i++) {\n            polynomial[leaf_count_ + i].resize(1);\n\
    \            if (i < point_count_) {\n                assert(derivative_values[i]\
    \ != Mint(0));\n                polynomial[leaf_count_ + i][0] = values[i] / derivative_values[i];\n\
    \            }\n        }\n        for (int node = leaf_count_ - 1; node > 0;\
    \ node--) {\n            polynomial[node] = polynomial[node << 1] * product_[node\
    \ << 1 | 1] +\n                               polynomial[node << 1 | 1] * product_[node\
    \ << 1];\n        }\n        polynomial[1].resize(point_count_);\n        return\
    \ polynomial[1];\n    }\n};\n\ntemplate <class Mint>\nstd::vector<Mint> multipoint_evaluate(const\
    \ FormalPowerSeries<Mint>& polynomial,\n                                     \
    \ const std::vector<Mint>& points) {\n    return SubproductTree<Mint>(points).evaluate(polynomial);\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_interpolate(const\
    \ std::vector<Mint>& points,\n                                               const\
    \ std::vector<Mint>& values) {\n    return SubproductTree<Mint>(points).interpolate(values);\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 12 \"math/fps/all.hpp\"\
    \n\n\n#line 1 \"math/matrix/all.hpp\"\n\n\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\
    \n\n\n\n#line 7 \"math/matrix/linear_algebra.hpp\"\n\n#line 1 \"math/matrix/matrix.hpp\"\
    \n\n\n\n#line 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\nnamespace matrix\
    \ {\n\ntemplate <class T>\nclass Matrix {\n   private:\n    int _rows;\n    int\
    \ _cols;\n    std::vector<T> _data;\n\n    static std::size_t storage_size(int\
    \ rows, int cols) {\n        assert(rows >= 0);\n        assert(cols >= 0);\n\
    \        return std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n\
    \    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int\
    \ rows, int cols, const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
    \ cols), value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n\
    \        : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        assert(_data.size() == std::size_t(rows)\
    \ * std::size_t(cols));\n    }\n\n    explicit Matrix(const std::vector<std::vector<T>>&\
    \ values)\n        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),\n\
    \          _data(storage_size(_rows, _cols)) {\n        for (int row = 0; row\
    \ < _rows; row++) {\n            assert(int(values[std::size_t(row)].size()) ==\
    \ _cols);\n            for (int col = 0; col < _cols; col++) {\n             \
    \   (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n        \
    \    }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n  \
    \  }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/linear_algebra.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nconstexpr T default_epsilon()\
    \ {\n    if constexpr (std::is_floating_point_v<T>) {\n        return T(1e-10);\n\
    \    } else {\n        return T();\n    }\n}\n\nnamespace detail {\n\ntemplate\
    \ <class T>\nT matrix_abs(T value) {\n    return value < T() ? T() - value : value;\n\
    }\n\ntemplate <class T>\nbool is_zero(const T& value, const T& eps) {\n    if\
    \ constexpr (std::is_floating_point_v<T>) {\n        return matrix_abs(value)\
    \ <= eps;\n    } else {\n        (void)eps;\n        return value == T();\n  \
    \  }\n}\n\ntemplate <class T>\nint choose_pivot(const Matrix<T>& matrix, int first_row,\
    \ int col, const T& eps) {\n    int pivot = -1;\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (int row = first_row; row < matrix.rows(); row++) {\n       \
    \     if (is_zero(matrix[row][col], eps)) continue;\n            if (pivot ==\
    \ -1 || matrix_abs(matrix[pivot][col]) < matrix_abs(matrix[row][col])) {\n   \
    \             pivot = row;\n            }\n        }\n    } else {\n        for\
    \ (int row = first_row; row < matrix.rows(); row++) {\n            if (!is_zero(matrix[row][col],\
    \ eps)) {\n                pivot = row;\n                break;\n            }\n\
    \        }\n    }\n    return pivot;\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ row_reduce(Matrix<T>& matrix, int pivot_col_limit, const T& eps,\n         \
    \                   bool reduced) {\n    std::vector<int> pivot_columns;\n   \
    \ int pivot_row = 0;\n    for (int col = 0; col < pivot_col_limit && pivot_row\
    \ < matrix.rows(); col++) {\n        int pivot = choose_pivot(matrix, pivot_row,\
    \ col, eps);\n        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row,\
    \ pivot);\n\n        const T pivot_value = matrix[pivot_row][col];\n        if\
    \ (reduced) {\n            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j]\
    \ /= pivot_value;\n        }\n\n        const int first_row = reduced ? 0 : pivot_row\
    \ + 1;\n        for (int row = first_row; row < matrix.rows(); row++) {\n    \
    \        if (row == pivot_row || is_zero(matrix[row][col], eps)) continue;\n \
    \           T factor = matrix[row][col];\n            if (!reduced) factor /=\
    \ pivot_value;\n            matrix[row][col] = T();\n            for (int j =\
    \ col + 1; j < matrix.cols(); j++) {\n                matrix[row][j] -= factor\
    \ * matrix[pivot_row][j];\n            }\n        }\n\n        pivot_columns.push_back(col);\n\
    \        pivot_row++;\n    }\n\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (T& value : matrix.data()) {\n            if (is_zero(value,\
    \ eps)) value = T();\n        }\n    }\n    return pivot_columns;\n}\n\n}  //\
    \ namespace detail\n\ntemplate <class T>\nstruct RowReduction {\n    Matrix<T>\
    \ matrix;\n    std::vector<int> pivot_columns;\n\n    int rank() const {\n   \
    \     return int(pivot_columns.size());\n    }\n};\n\ntemplate <class T>\nRowReduction<T>\
    \ reduced_row_echelon_form(Matrix<T> matrix,\n                               \
    \          T eps = default_epsilon<T>()) {\n    RowReduction<T> result;\n    result.pivot_columns\
    \ = detail::row_reduce(matrix, matrix.cols(), eps, true);\n    result.matrix =\
    \ std::move(matrix);\n    return result;\n}\n\ntemplate <class T>\nint matrix_rank(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    return int(detail::row_reduce(matrix,\
    \ matrix.cols(), eps, false).size());\n}\n\ntemplate <class T>\nT determinant(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    assert(matrix.rows() == matrix.cols());\n\
    \    const int size = matrix.rows();\n    T result = T(1);\n    bool negate =\
    \ false;\n\n    for (int col = 0; col < size; col++) {\n        int pivot = detail::choose_pivot(matrix,\
    \ col, col, eps);\n        if (pivot == -1) return T();\n        if (pivot !=\
    \ col) {\n            matrix.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        const T pivot_value = matrix[col][col];\n        result\
    \ *= pivot_value;\n        for (int row = col + 1; row < size; row++) {\n    \
    \        if (detail::is_zero(matrix[row][col], eps)) continue;\n            const\
    \ T factor = matrix[row][col] / pivot_value;\n            matrix[row][col] = T();\n\
    \            for (int j = col + 1; j < size; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[col][j];\n            }\n        }\n    }\n    return negate\
    \ ? T() - result : result;\n}\n\ntemplate <class T>\nstd::optional<Matrix<T>>\
    \ inverse(const Matrix<T>& matrix,\n                                 T eps = default_epsilon<T>())\
    \ {\n    assert(matrix.rows() == matrix.cols());\n    const int size = matrix.rows();\n\
    \    Matrix<T> augmented(size, size * 2);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) {\n            augmented[row][col]\
    \ = matrix[row][col];\n        }\n        augmented[row][size + row] = T(1);\n\
    \    }\n\n    const std::vector<int> pivots = detail::row_reduce(augmented, size,\
    \ eps, true);\n    if (int(pivots.size()) != size) return std::nullopt;\n\n  \
    \  Matrix<T> result(size, size);\n    for (int row = 0; row < size; row++) {\n\
    \        for (int col = 0; col < size; col++) {\n            result[row][col]\
    \ = augmented[row][size + col];\n        }\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nstruct LinearSystemResult {\n    bool consistent = false;\n    std::vector<T>\
    \ particular_solution;\n    std::vector<std::vector<T>> nullspace_basis;\n   \
    \ std::vector<int> pivot_columns;\n\n    int rank() const {\n        return int(pivot_columns.size());\n\
    \    }\n\n    int nullity() const {\n        return consistent ? int(nullspace_basis.size())\
    \ : 0;\n    }\n\n    bool has_unique_solution() const {\n        return consistent\
    \ && nullspace_basis.empty();\n    }\n};\n\ntemplate <class T>\nLinearSystemResult<T>\
    \ solve_linear_system(const Matrix<T>& coefficients,\n                       \
    \                   const std::vector<T>& constants,\n                       \
    \                   T eps = default_epsilon<T>()) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    Matrix<T> augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            augmented[row][col]\
    \ = coefficients[row][col];\n        }\n        augmented[row][variable_count]\
    \ = constants[std::size_t(row)];\n    }\n\n    LinearSystemResult<T> result;\n\
    \    result.pivot_columns =\n        detail::row_reduce(augmented, variable_count,\
    \ eps, true);\n\n    for (int row = result.rank(); row < equation_count; row++)\
    \ {\n        bool zero_left = true;\n        for (int col = 0; col < variable_count;\
    \ col++) {\n            if (!detail::is_zero(augmented[row][col], eps)) {\n  \
    \              zero_left = false;\n                break;\n            }\n   \
    \     }\n        if (zero_left && !detail::is_zero(augmented[row][variable_count],\
    \ eps)) {\n            return result;\n        }\n    }\n\n    result.consistent\
    \ = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ T());\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] = augmented[row][variable_count];\n\
    \    }\n\n    for (int free_col = 0; free_col < variable_count; free_col++) {\n\
    \        if (is_pivot[std::size_t(free_col)]) continue;\n        std::vector<T>\
    \ direction(static_cast<std::size_t>(variable_count));\n        direction[std::size_t(free_col)]\
    \ = T(1);\n        for (int row = 0; row < result.rank(); row++) {\n         \
    \   const int pivot_col = result.pivot_columns[std::size_t(row)];\n          \
    \  direction[std::size_t(pivot_col)] = T() - augmented[row][free_col];\n     \
    \   }\n        result.nullspace_basis.push_back(std::move(direction));\n    }\n\
    \    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n\
    #line 6 \"math/matrix/all.hpp\"\n\n\n#line 1 \"math/number_theory.hpp\"\n\n\n\n\
    #line 7 \"math/number_theory.hpp\"\n#include <tuple>\n#line 10 \"math/number_theory.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\nnamespace internal {\n\ninline long\
    \ long safe_mod(long long x, long long mod) {\n    x %= mod;\n    if (x < 0) x\
    \ += mod;\n    return x;\n}\n\ninline unsigned __int128 floor_sum_unsigned(unsigned\
    \ long long n, unsigned long long mod, unsigned long long a,\n               \
    \                             unsigned long long b) {\n    unsigned __int128 answer\
    \ = 0;\n    while (true) {\n        if (a >= mod) {\n            answer += static_cast<unsigned\
    \ __int128>(n) * (n - 1) / 2 * (a / mod);\n            a %= mod;\n        }\n\
    \        if (b >= mod) {\n            answer += static_cast<unsigned __int128>(n)\
    \ * (b / mod);\n            b %= mod;\n        }\n\n        const unsigned __int128\
    \ y_max = static_cast<unsigned __int128>(a) * n + b;\n        if (y_max < mod)\
    \ break;\n        n = static_cast<unsigned long long>(y_max / mod);\n        b\
    \ = static_cast<unsigned long long>(y_max % mod);\n        unsigned long long\
    \ tmp = mod;\n        mod = a;\n        a = tmp;\n    }\n    return answer;\n\
    }\n\n}  // namespace internal\n\n// Returns (g, x, y), where g = gcd(a, b) is\
    \ nonnegative and\n// a * x + b * y = g. Returns (0, 0, 0) when a = b = 0.\ninline\
    \ std::tuple<long long, long long, long long> extended_gcd(long long a,\n    \
    \                                                           long long b) {\n \
    \   using i128 = __int128;\n    if (a == 0 && b == 0) return {0, 0, 0};\n\n  \
    \  i128 old_remainder = a;\n    i128 remainder = b;\n    if (old_remainder < 0)\
    \ old_remainder = -old_remainder;\n    if (remainder < 0) remainder = -remainder;\n\
    \    i128 old_x = 1;\n    i128 x = 0;\n    i128 old_y = 0;\n    i128 y = 1;\n\n\
    \    while (remainder != 0) {\n        i128 quotient = old_remainder / remainder;\n\
    \n        i128 next = old_remainder - quotient * remainder;\n        old_remainder\
    \ = remainder;\n        remainder = next;\n\n        next = old_x - quotient *\
    \ x;\n        old_x = x;\n        x = next;\n\n        next = old_y - quotient\
    \ * y;\n        old_y = y;\n        y = next;\n    }\n\n    if (a < 0) old_x =\
    \ -old_x;\n    if (b < 0) old_y = -old_y;\n\n#ifndef NDEBUG\n    const i128 minimum\
    \ = std::numeric_limits<long long>::min();\n    const i128 maximum = std::numeric_limits<long\
    \ long>::max();\n    assert(old_remainder <= maximum);\n    assert(minimum <=\
    \ old_x && old_x <= maximum);\n    assert(minimum <= old_y && old_y <= maximum);\n\
    #endif\n    return {static_cast<long long>(old_remainder), static_cast<long long>(old_x),\n\
    \            static_cast<long long>(old_y)};\n}\n\ninline long long pow_mod(long\
    \ long x, unsigned long long exponent, long long mod) {\n    assert(mod >= 1);\n\
    \    if (mod == 1) return 0;\n\n    unsigned long long base = static_cast<unsigned\
    \ long long>(internal::safe_mod(x, mod));\n    unsigned long long result = 1;\n\
    \    const unsigned long long unsigned_mod = static_cast<unsigned long long>(mod);\n\
    \    while (exponent > 0) {\n        if (exponent & 1) {\n            result =\
    \ static_cast<unsigned long long>(static_cast<unsigned __int128>(result) * base\
    \ % unsigned_mod);\n        }\n        base = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(base) * base % unsigned_mod);\n        exponent >>= 1;\n    }\n  \
    \  return static_cast<long long>(result);\n}\n\n// Returns gcd(a, mod) and x such\
    \ that a * x is congruent to gcd(a, mod)\n// modulo mod. The returned x is in\
    \ [0, mod / gcd(a, mod)).\ninline std::pair<long long, long long> inv_gcd(long\
    \ long a, long long mod) {\n    assert(mod >= 1);\n    a = internal::safe_mod(a,\
    \ mod);\n    if (a == 0) return {mod, 0};\n\n    long long s = mod;\n    long\
    \ long t = a;\n    long long m0 = 0;\n    long long m1 = 1;\n    while (t > 0)\
    \ {\n        const long long quotient = s / t;\n        s -= t * quotient;\n \
    \       m0 -= m1 * quotient;\n\n        long long tmp = s;\n        s = t;\n \
    \       t = tmp;\n        tmp = m0;\n        m0 = m1;\n        m1 = tmp;\n   \
    \ }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n}\n\ninline long long\
    \ inv_mod(long long x, long long mod) {\n    const auto result = inv_gcd(x, mod);\n\
    \    assert(result.first == 1);\n    return result.second;\n}\n\n// Returns the\
    \ smallest nonnegative solution and the least common multiple of\n// the moduli.\
    \ Returns {0, 0} when the system is inconsistent.\ninline std::pair<long long,\
    \ long long> crt(const std::vector<long long>& remainders,\n                 \
    \                          const std::vector<long long>& moduli) {\n    assert(remainders.size()\
    \ == moduli.size());\n\n    long long r0 = 0;\n    long long m0 = 1;\n    for\
    \ (int i = 0; i < int(remainders.size()); i++) {\n        assert(moduli[i] >=\
    \ 1);\n        long long r1 = internal::safe_mod(remainders[i], moduli[i]);\n\
    \        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n            long\
    \ long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n            tmp\
    \ = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n        if (m0\
    \ % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n            continue;\n\
    \        }\n\n        const auto inverse = inv_gcd(m0, m1);\n        const long\
    \ long gcd = inverse.first;\n        const long long reduced_modulus = m1 / gcd;\n\
    \        const __int128 difference = static_cast<__int128>(r1) - r0;\n       \
    \ if (difference % gcd != 0) return {0, 0};\n\n        __int128 multiplier = difference\
    \ / gcd % reduced_modulus;\n        multiplier = multiplier * inverse.second %\
    \ reduced_modulus;\n        if (multiplier < 0) multiplier += reduced_modulus;\n\
    \n        const __int128 new_modulus = static_cast<__int128>(m0) * reduced_modulus;\n\
    \        assert(new_modulus <= std::numeric_limits<long long>::max());\n     \
    \   __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n  \
    \      new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n#line 1 \"math/primitive_root.hpp\"\n\n\n\n#line 9 \"math/primitive_root.hpp\"\
    \n\n#line 11 \"math/primitive_root.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ninline bool has_primitive_root(uint64_t mod) {\n    if (mod == 2 || mod\
    \ == 4) return true;\n    if (mod < 2) return false;\n\n    uint64_t odd_part\
    \ = mod;\n    if ((odd_part & 1) == 0) {\n        odd_part >>= 1;\n        if\
    \ ((odd_part & 1) == 0) return false;\n    }\n\n    return prime_factorize(odd_part).size()\
    \ == 1;\n}\n\n// Returns the smallest positive primitive root modulo mod.\n//\
    \ Returns 0 when no primitive root exists.\ninline uint64_t primitive_root(uint64_t\
    \ mod) {\n    assert(mod >= 2);\n    if (mod == 2) return 1;\n    if (!has_primitive_root(mod))\
    \ return 0;\n\n    const uint64_t phi = euler_phi(mod);\n    const std::vector<std::pair<uint64_t,\
    \ int>> factors = prime_factorize(phi);\n    for (uint64_t candidate = 2; candidate\
    \ < mod; candidate++) {\n        if (std::gcd(candidate, mod) != 1) continue;\n\
    \n        bool generator = true;\n        for (const auto& factor : factors) {\n\
    \            if (internal::power_mod(candidate, phi / factor.first, mod) == 1)\
    \ {\n                generator = false;\n                break;\n            }\n\
    \        }\n        if (generator) return candidate;\n    }\n    return 0;\n}\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/prime_sieve.hpp\"\
    \n\n\n\n#line 8 \"math/prime_sieve.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nstruct PrimeSieve {\n   private:\n    int _limit;\n    std::vector<int>\
    \ _min_prime_factor;\n    std::vector<int> _primes;\n\n   public:\n    explicit\
    \ PrimeSieve(int limit = 0) : _limit(0) {\n        assert(limit >= 0);\n     \
    \   _limit = limit;\n        _min_prime_factor.assign(limit + 1, 0);\n       \
    \ if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int value = 2; value\
    \ <= limit; value++) {\n            if (_min_prime_factor[value] == 0) {\n   \
    \             _min_prime_factor[value] = value;\n                _primes.push_back(value);\n\
    \            }\n            for (int prime : _primes) {\n                if (prime\
    \ > _min_prime_factor[value] || value > limit / prime) break;\n              \
    \  _min_prime_factor[value * prime] = prime;\n            }\n        }\n    }\n\
    \n    int limit() const {\n        return _limit;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    const std::vector<int>&\
    \ min_prime_factors() const {\n        return _min_prime_factor;\n    }\n\n  \
    \  bool is_prime(int value) const {\n        assert(0 <= value && value <= _limit);\n\
    \        return value >= 2 && _min_prime_factor[value] == value;\n    }\n\n  \
    \  int min_prime_factor(int value) const {\n        assert(2 <= value && value\
    \ <= _limit);\n        return _min_prime_factor[value];\n    }\n\n    std::vector<std::pair<int,\
    \ int>> factorize(int value) const {\n        assert(1 <= value && value <= _limit);\n\
    \        std::vector<std::pair<int, int>> result;\n        while (value > 1) {\n\
    \            const int prime = _min_prime_factor[value];\n            int exponent\
    \ = 0;\n            do {\n                value /= prime;\n                exponent++;\n\
    \            } while (value > 1 && _min_prime_factor[value] == prime);\n     \
    \       result.emplace_back(prime, exponent);\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> divisors(int value) const {\n        std::vector<int>\
    \ result = {1};\n        for (const auto& factor : factorize(value)) {\n     \
    \       const int current_size = int(result.size());\n            int power =\
    \ 1;\n            for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n                power *= factor.first;\n                for (int i = 0; i\
    \ < current_size; i++) {\n                    result.push_back(result[i] * power);\n\
    \                }\n            }\n        }\n        std::sort(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    int totient(int value)\
    \ const {\n        assert(1 <= value && value <= _limit);\n        int result\
    \ = value;\n        for (const auto& factor : factorize(value)) {\n          \
    \  result = result / factor.first * (factor.first - 1);\n        }\n        return\
    \ result;\n    }\n\n    int mobius(int value) const {\n        assert(1 <= value\
    \ && value <= _limit);\n        int result = 1;\n        for (const auto& factor\
    \ : factorize(value)) {\n            if (factor.second >= 2) return 0;\n     \
    \       result = -result;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ totient_table() const {\n        std::vector<int> result(_limit + 1);\n    \
    \    if (_limit >= 1) result[1] = 1;\n        for (int value = 2; value <= _limit;\
    \ value++) {\n            const int prime = _min_prime_factor[value];\n      \
    \      const int reduced = value / prime;\n            result[value] = reduced\
    \ % prime == 0 ? result[reduced] * prime : result[reduced] * (prime - 1);\n  \
    \      }\n        return result;\n    }\n\n    std::vector<int> mobius_table()\
    \ const {\n        std::vector<int> result(_limit + 1);\n        if (_limit >=\
    \ 1) result[1] = 1;\n        for (int value = 2; value <= _limit; value++) {\n\
    \            const int prime = _min_prime_factor[value];\n            const int\
    \ reduced = value / prime;\n            result[value] = reduced % prime == 0 ?\
    \ 0 : -result[reduced];\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/rational.hpp\"\n\n\
    \n\n#line 5 \"math/rational.hpp\"\n#include <compare>\n#line 10 \"math/rational.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral T =\
    \ long long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    using Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\
    \n    T _numerator;\n    T _denominator;\n\n    static constexpr UnsignedWide\
    \ magnitude(Wide value) {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
    \ + 1)) + 1;\n        }\n        return static_cast<UnsignedWide>(value);\n  \
    \  }\n\n    static constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide\
    \ second) {\n        while (second != 0) {\n            UnsignedWide remainder\
    \ = first % second;\n            first = second;\n            second = remainder;\n\
    \        }\n        return first;\n    }\n\n    static constexpr T narrow(Wide\
    \ value) {\n        assert(Wide(std::numeric_limits<T>::min()) <= value);\n  \
    \      assert(value <= Wide(std::numeric_limits<T>::max()));\n        return static_cast<T>(value);\n\
    \    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        UnsignedWide divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n   public:\n    constexpr Rational() : _numerator(0), _denominator(1)\
    \ {}\n\n    constexpr Rational(T integer) : _numerator(integer), _denominator(1)\
    \ {}\n\n    constexpr Rational(T numerator, T denominator) {\n        assign_normalized(Wide(numerator),\
    \ Wide(denominator));\n    }\n\n    constexpr T numerator() const {\n        return\
    \ _numerator;\n    }\n\n    constexpr T denominator() const {\n        return\
    \ _denominator;\n    }\n\n    constexpr bool is_integer() const {\n        return\
    \ _denominator == 1;\n    }\n\n    constexpr int sign() const {\n        return\
    \ (_numerator > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal()\
    \ const {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    explicit constexpr operator long double()\
    \ const {\n        return to_long_double();\n    }\n\n    constexpr T trunc()\
    \ const {\n        return _numerator / _denominator;\n    }\n\n    constexpr T\
    \ floor() const {\n        T quotient = _numerator / _denominator;\n        if\
    \ (_numerator < 0 && _numerator % _denominator != 0) --quotient;\n        return\
    \ quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient = _numerator\
    \ / _denominator;\n        if (0 < _numerator && _numerator % _denominator !=\
    \ 0) ++quotient;\n        return quotient;\n    }\n\n    constexpr Rational operator+()\
    \ const {\n        return *this;\n    }\n\n    constexpr Rational operator-()\
    \ const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  UnsignedWide common =\n            gcd(static_cast<UnsignedWide>(_denominator),\
    \ static_cast<UnsignedWide>(other._denominator));\n        Wide left_scale = Wide(other._denominator)\
    \ / static_cast<Wide>(common);\n        Wide right_scale = Wide(_denominator)\
    \ / static_cast<Wide>(common);\n        assign_normalized(Wide(_numerator) * left_scale\
    \ + Wide(other._numerator) * right_scale,\n                          Wide(_denominator)\
    \ * left_scale);\n        return *this;\n    }\n\n    constexpr Rational& operator-=(const\
    \ Rational& other) {\n        return *this += -other;\n    }\n\n    constexpr\
    \ Rational& operator*=(const Rational& other) {\n        UnsignedWide first_gcd\
    \ = gcd(magnitude(Wide(_numerator)), static_cast<UnsignedWide>(other._denominator));\n\
    \        UnsignedWide second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        T numerator;\n        if (!(input >> numerator))\
    \ return input;\n        T denominator = 1;\n        if (input.peek() == '/')\
    \ {\n            input.get();\n            if (!(input >> denominator)) return\
    \ input;\n        }\n        value = Rational(numerator, denominator);\n     \
    \   return input;\n    }\n};\n\ntemplate <std::signed_integral T>\nconstexpr Rational<T>\
    \ abs(const Rational<T>& value) {\n    return value.abs();\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/repunit.hpp\"\n\n\n\n#line 9\
    \ \"math/repunit.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class\
    \ T>\nconstexpr std::pair<T, T> repunit_and_power(\n    std::uint64_t length,\n\
    \    T base = T(10)\n) {\n    T result = T(0);\n    T result_power = T(1);\n \
    \   T block = T(1);\n    T block_power = base;\n\n    while (length > 0) {\n \
    \       if (length & 1) {\n            result = result * block_power + block;\n\
    \            result_power = result_power * block_power;\n        }\n        block\
    \ = block * block_power + block;\n        block_power = block_power * block_power;\n\
    \        length >>= 1;\n    }\n    return std::make_pair(result, result_power);\n\
    }\n\n// Returns 1 + base + ... + base^(length - 1).\n// The arithmetic, including\
    \ any modular reduction, is performed by T.\ntemplate <class T>\nconstexpr T repunit(std::uint64_t\
    \ length, T base = T(10)) {\n    return repunit_and_power<T>(length, base).first;\n\
    }\n\ntemplate <class T>\nconstexpr T repdigit(std::uint64_t length, T digit, T\
    \ base = T(10)) {\n    return digit * repunit<T>(length, base);\n}\n\ntemplate\
    \ <class T>\nconstexpr T concatenate_digits(\n    T left,\n    T right,\n    std::uint64_t\
    \ right_length,\n    T base = T(10)\n) {\n    return left * repunit_and_power<T>(right_length,\
    \ base).second + right;\n}\n\nnamespace repunit_detail {\n\ninline std::uint64_t\
    \ multiply_mod(\n    std::uint64_t left,\n    std::uint64_t right,\n    std::uint64_t\
    \ mod\n) {\n    return static_cast<std::uint64_t>(\n        static_cast<unsigned\
    \ __int128>(left) * right % mod\n    );\n}\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    if (mod == 1) return std::make_pair(0,\
    \ 0);\n\n    std::uint64_t result = 0;\n    std::uint64_t result_power = 1;\n\
    \    std::uint64_t block = 1;\n    std::uint64_t block_power = base % mod;\n \
    \   while (length > 0) {\n        if (length & 1) {\n            result = (\n\
    \                static_cast<unsigned __int128>(result) * block_power + block\n\
    \            ) % mod;\n            result_power = multiply_mod(result_power, block_power,\
    \ mod);\n        }\n        block = (\n            static_cast<unsigned __int128>(block)\
    \ * block_power + block\n        ) % mod;\n        block_power = multiply_mod(block_power,\
    \ block_power, mod);\n        length >>= 1;\n    }\n    return std::make_pair(result,\
    \ result_power);\n}\n\n}  // namespace repunit_detail\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    return repunit_detail::repunit_and_power_mod(length,\
    \ base, mod);\n}\n\ninline std::uint64_t repunit_mod(\n    std::uint64_t length,\n\
    \    std::uint64_t base,\n    std::uint64_t mod\n) {\n    return repunit_and_power_mod(length,\
    \ base, mod).first;\n}\n\ninline std::uint64_t repdigit_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t digit,\n    std::uint64_t base,\n    std::uint64_t\
    \ mod\n) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    return repunit_detail::multiply_mod(\n\
    \        digit % mod,\n        repunit_mod(length, base, mod),\n        mod\n\
    \    );\n}\n\ninline std::uint64_t concatenate_digits_mod(\n    std::uint64_t\
    \ left,\n    std::uint64_t right,\n    std::uint64_t right_length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    if (mod == 1)\
    \ return 0;\n    const std::uint64_t power =\n        repunit_and_power_mod(right_length,\
    \ base, mod).second;\n    return (\n        static_cast<unsigned __int128>(left\
    \ % mod) * power + right % mod\n    ) % mod;\n}\n\ninline std::optional<std::uint64_t>\
    \ minimum_repunit_length(\n    std::uint64_t divisor,\n    std::uint64_t base\
    \ = 10\n) {\n    assert(divisor >= 1);\n    assert(base >= 2);\n    if (std::gcd(divisor,\
    \ base) != 1) return std::nullopt;\n\n    std::uint64_t remainder = 0;\n    for\
    \ (std::uint64_t length = 1; length <= divisor; length++) {\n        remainder\
    \ = (\n            static_cast<unsigned __int128>(remainder) * base + 1\n    \
    \    ) % divisor;\n        if (remainder == 0) return length;\n    }\n    return\
    \ std::nullopt;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1\
    \ \"math/stern_brocot_tree.hpp\"\n\n\n\n#line 10 \"math/stern_brocot_tree.hpp\"\
    \n\n#line 12 \"math/stern_brocot_tree.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nenum class SternBrocotDirection {\n    Left,\n    Right,\n};\n\nstruct\
    \ SternBrocotRun {\n    SternBrocotDirection direction;\n    uint64_t count;\n\
    \n    friend bool operator==(const SternBrocotRun&, const SternBrocotRun&) = default;\n\
    };\n\nstruct SternBrocotPath {\n    std::vector<SternBrocotRun> runs;\n\n    bool\
    \ empty() const {\n        return runs.empty();\n    }\n\n    uint64_t depth()\
    \ const {\n        uint64_t result = 0;\n        for (const SternBrocotRun& run\
    \ : runs) {\n            assert(run.count <= std::numeric_limits<uint64_t>::max()\
    \ - result);\n            result += run.count;\n        }\n        return result;\n\
    \    }\n\n    void push(SternBrocotDirection direction, uint64_t count = 1) {\n\
    \        if (count == 0) return;\n        if (!runs.empty() && runs.back().direction\
    \ == direction) {\n            assert(count <= std::numeric_limits<uint64_t>::max()\
    \ - runs.back().count);\n            runs.back().count += count;\n        } else\
    \ {\n            runs.push_back(SternBrocotRun{direction, count});\n        }\n\
    \    }\n\n    bool move_up(uint64_t count = 1) {\n        if (depth() < count)\
    \ return false;\n        while (count > 0) {\n            SternBrocotRun& run\
    \ = runs.back();\n            uint64_t removed = run.count < count ? run.count\
    \ : count;\n            run.count -= removed;\n            count -= removed;\n\
    \            if (run.count == 0) runs.pop_back();\n        }\n        return true;\n\
    \    }\n\n    SternBrocotPath ancestor(uint64_t count) const {\n        SternBrocotPath\
    \ result = *this;\n        [[maybe_unused]] bool valid = result.move_up(count);\n\
    \        assert(valid);\n        return result;\n    }\n\n    friend bool operator==(const\
    \ SternBrocotPath&, const SternBrocotPath&) = default;\n};\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct SternBrocotBounds {\n    std::pair<T, T> left;\n    std::pair<T,\
    \ T> right;\n};\n\ntemplate <std::signed_integral T>\nSternBrocotPath stern_brocot_path(T\
    \ numerator, T denominator) {\n    assert(0 < numerator);\n    assert(0 < denominator);\n\
    \    SternBrocotPath result;\n    while (numerator != denominator) {\n       \
    \ if (numerator < denominator) {\n            T count = (denominator - 1) / numerator;\n\
    \            result.push(SternBrocotDirection::Left, uint64_t(count));\n     \
    \       denominator -= count * numerator;\n        } else {\n            T count\
    \ = (numerator - 1) / denominator;\n            result.push(SternBrocotDirection::Right,\
    \ uint64_t(count));\n            numerator -= count * denominator;\n        }\n\
    \    }\n    assert(numerator == 1);\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T = long long>\nRational<T> stern_brocot_decode(const SternBrocotPath& path)\
    \ {\n    using Wide = __int128_t;\n    Wide left_numerator = 0;\n    Wide left_denominator\
    \ = 1;\n    Wide right_numerator = 1;\n    Wide right_denominator = 0;\n    Wide\
    \ numerator = 1;\n    Wide denominator = 1;\n    [[maybe_unused]] const Wide maximum\
    \ = std::numeric_limits<T>::max();\n    for (const SternBrocotRun& run : path.runs)\
    \ {\n        assert(run.count > 0);\n        assert(Wide(run.count) <= maximum);\n\
    \        Wide count = run.count;\n        if (run.direction == SternBrocotDirection::Left)\
    \ {\n            right_numerator = numerator + (count - 1) * left_numerator;\n\
    \            right_denominator = denominator + (count - 1) * left_denominator;\n\
    \            numerator += count * left_numerator;\n            denominator +=\
    \ count * left_denominator;\n        } else {\n            left_numerator = numerator\
    \ + (count - 1) * right_numerator;\n            left_denominator = denominator\
    \ + (count - 1) * right_denominator;\n            numerator += count * right_numerator;\n\
    \            denominator += count * right_denominator;\n        }\n        assert(numerator\
    \ <= maximum);\n        assert(denominator <= maximum);\n        assert(left_numerator\
    \ <= maximum);\n        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    return\
    \ Rational<T>(T(numerator), T(denominator));\n}\n\ntemplate <std::signed_integral\
    \ T>\nuint64_t stern_brocot_depth(T numerator, T denominator) {\n    return stern_brocot_path(numerator,\
    \ denominator).depth();\n}\n\ninline SternBrocotPath stern_brocot_lca_path(\n\
    \    const SternBrocotPath& first,\n    const SternBrocotPath& second\n) {\n \
    \   SternBrocotPath result;\n    int limit = int(first.runs.size() < second.runs.size()\
    \ ? first.runs.size() : second.runs.size());\n    for (int i = 0; i < limit; i++)\
    \ {\n        if (first.runs[i].direction != second.runs[i].direction) break;\n\
    \        uint64_t common =\n            first.runs[i].count < second.runs[i].count\n\
    \                ? first.runs[i].count\n                : second.runs[i].count;\n\
    \        result.push(first.runs[i].direction, common);\n        if (first.runs[i].count\
    \ != second.runs[i].count) break;\n    }\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T>\nRational<T> stern_brocot_lca(\n    T first_numerator,\n    T first_denominator,\n\
    \    T second_numerator,\n    T second_denominator\n) {\n    SternBrocotPath path\
    \ = stern_brocot_lca_path(\n        stern_brocot_path(first_numerator, first_denominator),\n\
    \        stern_brocot_path(second_numerator, second_denominator)\n    );\n   \
    \ return stern_brocot_decode<T>(path);\n}\n\ntemplate <std::signed_integral T>\n\
    Rational<T> stern_brocot_ancestor(T numerator, T denominator, uint64_t up) {\n\
    \    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n    [[maybe_unused]]\
    \ bool valid = path.move_up(up);\n    assert(valid);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_parent(T numerator,\
    \ T denominator) {\n    return stern_brocot_ancestor(numerator, denominator, 1);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_move(\n    T\
    \ numerator,\n    T denominator,\n    SternBrocotDirection direction,\n    uint64_t\
    \ count = 1\n) {\n    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n\
    \    path.push(direction, count);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T = long long>\nSternBrocotBounds<T> stern_brocot_bounds(const\
    \ SternBrocotPath& path) {\n    using Wide = __int128_t;\n    Wide left_numerator\
    \ = 0;\n    Wide left_denominator = 1;\n    Wide right_numerator = 1;\n    Wide\
    \ right_denominator = 0;\n    Wide numerator = 1;\n    Wide denominator = 1;\n\
    \    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();\n\n\
    \    for (const SternBrocotRun& run : path.runs) {\n        assert(run.count >\
    \ 0);\n        assert(Wide(run.count) <= maximum);\n        Wide count = run.count;\n\
    \        if (run.direction == SternBrocotDirection::Left) {\n            right_numerator\
    \ = numerator + (count - 1) * left_numerator;\n            right_denominator =\
    \ denominator + (count - 1) * left_denominator;\n            numerator += count\
    \ * left_numerator;\n            denominator += count * left_denominator;\n  \
    \      } else {\n            left_numerator = numerator + (count - 1) * right_numerator;\n\
    \            left_denominator = denominator + (count - 1) * right_denominator;\n\
    \            numerator += count * right_numerator;\n            denominator +=\
    \ count * right_denominator;\n        }\n        assert(numerator <= maximum);\n\
    \        assert(denominator <= maximum);\n        assert(left_numerator <= maximum);\n\
    \        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    SternBrocotBounds<T>\
    \ result;\n    result.left = {T(left_numerator), T(left_denominator)};\n    result.right\
    \ = {T(right_numerator), T(right_denominator)};\n    return result;\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/tetration.hpp\"\n\n\
    \n\n#line 9 \"math/tetration.hpp\"\n\n#line 11 \"math/tetration.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace tetration_detail {\n\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nuint64_t to_uint64(T\
    \ value) {\n    if constexpr (std::signed_integral<T>) {\n        assert(value\
    \ >= 0);\n    }\n    return static_cast<uint64_t>(value);\n}\n\ninline uint64_t\
    \ multiply_mod(uint64_t first, uint64_t second, uint64_t mod) {\n    return static_cast<uint64_t>(\n\
    \        static_cast<__uint128_t>(first) * second % mod\n    );\n}\n\ninline uint64_t\
    \ pow_mod(uint64_t base, __uint128_t exponent, uint64_t mod) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    base %= mod;\n    uint64_t result =\
    \ 1 % mod;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result\
    \ = multiply_mod(result, base, mod);\n        base = multiply_mod(base, base,\
    \ mod);\n        exponent >>= 1;\n    }\n    return result;\n}\n\ninline uint64_t\
    \ pow_bounded(uint64_t base, uint64_t exponent, uint64_t limit) {\n    if (limit\
    \ == 0) return 0;\n    __uint128_t result = 1;\n    for (uint64_t i = 0; i < exponent;\
    \ i++) {\n        result *= base;\n        if (result >= limit) return limit;\n\
    \    }\n    return static_cast<uint64_t>(result);\n}\n\ninline uint64_t exponent_threshold(uint64_t\
    \ base, uint64_t limit) {\n    assert(base >= 2);\n    if (limit <= 1) return\
    \ 0;\n\n    uint64_t exponent = 0;\n    uint64_t value = 1;\n    while (value\
    \ < limit) {\n        exponent++;\n        if (value > limit / base) return exponent;\n\
    \        value *= base;\n    }\n    return exponent;\n}\n\ninline uint64_t tetration_bounded_unsigned(uint64_t\
    \ base, uint64_t height, uint64_t limit) {\n    if (limit == 0) return 0;\n  \
    \  if (height == 0) return limit < 1 ? limit : 1;\n    if (height == 1) return\
    \ base < limit ? base : limit;\n\n    if (base == 0) {\n        const uint64_t\
    \ value = (height & 1) == 0 ? 1 : 0;\n        return value < limit ? value : limit;\n\
    \    }\n    if (base == 1) return limit < 1 ? limit : 1;\n\n    const uint64_t\
    \ threshold = exponent_threshold(base, limit);\n    const uint64_t exponent =\
    \ tetration_bounded_unsigned(base, height - 1, threshold);\n    if (exponent >=\
    \ threshold) return limit;\n    return pow_bounded(base, exponent, limit);\n}\n\
    \ninline uint64_t tetration_mod_unsigned(uint64_t base, uint64_t height, uint64_t\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    if (height ==\
    \ 0) return 1 % mod;\n    if (height == 1) return base % mod;\n    if (base ==\
    \ 0) return (height & 1) == 0 ? 1 % mod : 0;\n    if (base == 1) return 1 % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = tetration_mod_unsigned(base,\
    \ height - 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (tetration_bounded_unsigned(base,\
    \ height - 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(base,\
    \ exponent, mod);\n}\n\ninline uint64_t power_tower_bounded_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t limit\n) {\n   \
    \ if (limit == 0) return 0;\n    if (index == int(bases.size())) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t base = bases[index];\n    if (index +\
    \ 1 == int(bases.size())) return base < limit ? base : limit;\n\n    if (base\
    \ == 0) {\n        const uint64_t exponent = power_tower_bounded_unsigned(bases,\
    \ index + 1, 1);\n        const uint64_t value = exponent == 0 ? 1 : 0;\n    \
    \    return value < limit ? value : limit;\n    }\n    if (base == 1) return limit\
    \ < 1 ? limit : 1;\n\n    const uint64_t threshold = exponent_threshold(base,\
    \ limit);\n    const uint64_t exponent = power_tower_bounded_unsigned(bases, index\
    \ + 1, threshold);\n    if (exponent >= threshold) return limit;\n    return pow_bounded(base,\
    \ exponent, limit);\n}\n\ninline uint64_t power_tower_mod_unsigned(\n    const\
    \ std::vector<uint64_t>& bases,\n    int index,\n    uint64_t mod\n) {\n    assert(mod\
    \ >= 1);\n    if (mod == 1) return 0;\n    if (index == int(bases.size())) return\
    \ 1 % mod;\n    if (index + 1 == int(bases.size())) return bases[index] % mod;\n\
    \n    const uint64_t phi = euler_phi(mod);\n    uint64_t reduced_exponent = power_tower_mod_unsigned(bases,\
    \ index + 1, phi);\n    __uint128_t exponent = reduced_exponent;\n    if (power_tower_bounded_unsigned(bases,\
    \ index + 1, phi) >= phi) {\n        exponent += phi;\n    }\n    return pow_mod(bases[index],\
    \ exponent, mod);\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstd::vector<uint64_t> normalize_bases(const std::vector<T>& bases) {\n\
    \    std::vector<uint64_t> result;\n    result.reserve(bases.size());\n    for\
    \ (T base : bases) result.push_back(to_uint64(base));\n    return result;\n}\n\
    \n}  // namespace tetration_detail\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_mod(T base, uint64_t height, uint64_t mod) {\n  \
    \  assert(mod >= 1);\n    return tetration_detail::tetration_mod_unsigned(\n \
    \       tetration_detail::to_uint64(base),\n        height,\n        mod\n   \
    \ );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t tetration_bounded(T base, uint64_t height, uint64_t limit)\
    \ {\n    return tetration_detail::tetration_bounded_unsigned(\n        tetration_detail::to_uint64(base),\n\
    \        height,\n        limit\n    );\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nuint64_t power_tower_mod(const std::vector<T>& bases, uint64_t mod)\
    \ {\n    assert(mod >= 1);\n    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_mod_unsigned(normalized, 0, mod);\n\
    }\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\n\
    uint64_t power_tower_bounded(const std::vector<T>& bases, uint64_t limit) {\n\
    \    std::vector<uint64_t> normalized = tetration_detail::normalize_bases(bases);\n\
    \    return tetration_detail::power_tower_bounded_unsigned(normalized, 0, limit);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/totient_sum.hpp\"\
    \n\n\n\n#line 6 \"math/totient_sum.hpp\"\n#include <unordered_map>\n#line 8 \"\
    math/totient_sum.hpp\"\n\nnamespace m1une {\nnamespace math {\n\nstruct TotientSum\
    \ {\n   private:\n    int _precalculation_limit;\n    std::vector<__uint128_t>\
    \ _prefix_sum;\n    std::unordered_map<uint64_t, __uint128_t> _memo;\n\n    __uint128_t\
    \ solve(uint64_t n) {\n        if (n <= static_cast<uint64_t>(_precalculation_limit))\
    \ {\n            return _prefix_sum[static_cast<int>(n)];\n        }\n       \
    \ if (auto it = _memo.find(n); it != _memo.end()) {\n            return it->second;\n\
    \        }\n\n        const __uint128_t wide_n = n;\n        __uint128_t result\
    \ = wide_n * (wide_n + 1) / 2;\n        for (uint64_t left = 2; left <= n;) {\n\
    \            const uint64_t quotient = n / left;\n            const uint64_t right\
    \ = n / quotient;\n            result -= static_cast<__uint128_t>(right - left\
    \ + 1) * solve(quotient);\n            if (right == n) break;\n            left\
    \ = right + 1;\n        }\n\n        _memo.emplace(n, result);\n        return\
    \ result;\n    }\n\n   public:\n    explicit TotientSum(int precalculation_limit\
    \ = 1000000) : _precalculation_limit(precalculation_limit) {\n        assert(precalculation_limit\
    \ >= 0);\n\n        std::vector<uint64_t> phi(precalculation_limit + 1);\n   \
    \     std::vector<int> primes;\n        std::vector<bool> is_composite(precalculation_limit\
    \ + 1);\n        if (precalculation_limit >= 1) {\n            phi[1] = 1;\n \
    \       }\n        for (int value = 2; value <= precalculation_limit; value++)\
    \ {\n            if (!is_composite[value]) {\n                primes.push_back(value);\n\
    \                phi[value] = static_cast<uint64_t>(value - 1);\n            }\n\
    \            for (int prime : primes) {\n                if (value > precalculation_limit\
    \ / prime) break;\n                const int next = value * prime;\n         \
    \       is_composite[next] = true;\n                if (value % prime == 0) {\n\
    \                    phi[next] = phi[value] * static_cast<uint64_t>(prime);\n\
    \                    break;\n                }\n                phi[next] = phi[value]\
    \ * static_cast<uint64_t>(prime - 1);\n            }\n        }\n\n        _prefix_sum.assign(precalculation_limit\
    \ + 1, 0);\n        for (int value = 1; value <= precalculation_limit; value++)\
    \ {\n            _prefix_sum[value] = _prefix_sum[value - 1] + phi[value];\n \
    \       }\n    }\n\n    int precalculation_limit() const {\n        return _precalculation_limit;\n\
    \    }\n\n    // Returns sum_{i=1}^n phi(i).\n    __uint128_t prefix_sum(uint64_t\
    \ n) {\n        return solve(n);\n    }\n\n    __uint128_t operator()(uint64_t\
    \ n) {\n        return prefix_sum(n);\n    }\n};\n\ninline __uint128_t totient_sum(uint64_t\
    \ n, int precalculation_limit = 1000000) {\n    TotientSum solver(precalculation_limit);\n\
    \    return solver.prefix_sum(n);\n}\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/two_square_sum.hpp\"\n\n\n\n#line 9 \"math/two_square_sum.hpp\"\
    \n\n#line 12 \"math/two_square_sum.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\nnamespace two_square_sum_detail {\n\nstruct GaussianInteger {\n    __int128_t\
    \ real;\n    __int128_t imaginary;\n};\n\ninline GaussianInteger multiply(GaussianInteger\
    \ first, GaussianInteger second) {\n    return GaussianInteger{first.real * second.real\
    \ - first.imaginary * second.imaginary,\n                           first.real\
    \ * second.imaginary + first.imaginary * second.real};\n}\n\ninline GaussianInteger\
    \ power(GaussianInteger base, int exponent) {\n    GaussianInteger result{1, 0};\n\
    \    while (exponent > 0) {\n        if ((exponent & 1) != 0) result = multiply(result,\
    \ base);\n        exponent >>= 1;\n        if (exponent != 0) base = multiply(base,\
    \ base);\n    }\n    return result;\n}\n\ninline uint64_t absolute_value(__int128_t\
    \ value) {\n    return static_cast<uint64_t>(value < 0 ? -value : value);\n}\n\
    \ninline uint64_t pow_uint64(uint64_t base, int exponent) {\n    uint64_t result\
    \ = 1;\n    while (exponent > 0) {\n        if ((exponent & 1) != 0) result *=\
    \ base;\n        exponent >>= 1;\n        if (exponent != 0) base *= base;\n \
    \   }\n    return result;\n}\n\ninline GaussianInteger prime_one_mod_four_representation(uint64_t\
    \ prime) {\n    assert(prime % 4 == 1);\n    uint64_t non_residue = 2;\n    while\
    \ (internal::power_mod(non_residue, (prime - 1) / 2, prime) != prime - 1) {\n\
    \        non_residue++;\n    }\n\n    uint64_t root = internal::power_mod(non_residue,\
    \ (prime - 1) / 4, prime);\n    uint64_t previous = prime;\n    uint64_t current\
    \ = root;\n    while (static_cast<__uint128_t>(current) * current > prime) {\n\
    \        uint64_t next = previous % current;\n        previous = current;\n  \
    \      current = next;\n    }\n\n    const uint64_t real = current;\n    const\
    \ uint64_t remaining = prime - real * real;\n    const uint64_t imaginary = isqrt(remaining);\n\
    \    assert(imaginary * imaginary == remaining);\n    return GaussianInteger{static_cast<__int128_t>(real),\
    \ static_cast<__int128_t>(imaginary)};\n}\n\ninline std::vector<GaussianInteger>\
    \ prime_power_choices(GaussianInteger factor, int exponent) {\n    GaussianInteger\
    \ conjugate{factor.real, -factor.imaginary};\n\n    std::vector<GaussianInteger>\
    \ positive_powers(exponent + 1);\n    std::vector<GaussianInteger> negative_powers(exponent\
    \ + 1);\n    positive_powers[0] = GaussianInteger{1, 0};\n    negative_powers[0]\
    \ = GaussianInteger{1, 0};\n    for (int i = 0; i < exponent; i++) {\n       \
    \ positive_powers[i + 1] = multiply(positive_powers[i], factor);\n        negative_powers[i\
    \ + 1] = multiply(negative_powers[i], conjugate);\n    }\n\n    std::vector<GaussianInteger>\
    \ result;\n    result.reserve(exponent + 1);\n    for (int take_positive = 0;\
    \ take_positive <= exponent; take_positive++) {\n        result.push_back(multiply(positive_powers[take_positive],\
    \ negative_powers[exponent - take_positive]));\n    }\n    return result;\n}\n\
    \ninline void add_nonnegative_pairs(std::vector<std::pair<uint64_t, uint64_t>>&\
    \ result, GaussianInteger value,\n                                  uint64_t scale)\
    \ {\n    const uint64_t first = absolute_value(value.real) * scale;\n    const\
    \ uint64_t second = absolute_value(value.imaginary) * scale;\n    result.emplace_back(first,\
    \ second);\n    result.emplace_back(second, first);\n}\n\n}  // namespace two_square_sum_detail\n\
    \ninline std::vector<std::pair<uint64_t, uint64_t>> two_square_sum(uint64_t value)\
    \ {\n    using two_square_sum_detail::GaussianInteger;\n\n    if (value == 0)\
    \ return std::vector<std::pair<uint64_t, uint64_t>>{std::pair<uint64_t, uint64_t>(0,\
    \ 0)};\n\n    uint64_t real_scale = 1;\n    std::vector<std::vector<GaussianInteger>>\
    \ choices_by_prime;\n    for (const auto& factor : prime_factorize(value)) {\n\
    \        const uint64_t prime = factor.first;\n        const int exponent = factor.second;\n\
    \n        if (prime % 4 == 3) {\n            if ((exponent & 1) != 0) return {};\n\
    \            real_scale *= two_square_sum_detail::pow_uint64(prime, exponent /\
    \ 2);\n            continue;\n        }\n\n        GaussianInteger gaussian_factor;\n\
    \        if (prime == 2) {\n            gaussian_factor = GaussianInteger{1, 1};\n\
    \        } else {\n            gaussian_factor = two_square_sum_detail::prime_one_mod_four_representation(prime);\n\
    \        }\n        choices_by_prime.push_back(two_square_sum_detail::prime_power_choices(gaussian_factor,\
    \ exponent));\n    }\n\n    std::vector<GaussianInteger> values;\n    values.push_back(GaussianInteger{1,\
    \ 0});\n    for (const std::vector<GaussianInteger>& choices : choices_by_prime)\
    \ {\n        std::vector<GaussianInteger> next;\n        next.reserve(values.size()\
    \ * choices.size());\n        for (GaussianInteger value_so_far : values) {\n\
    \            for (GaussianInteger choice : choices) {\n                next.push_back(two_square_sum_detail::multiply(value_so_far,\
    \ choice));\n            }\n        }\n        values.swap(next);\n    }\n\n \
    \   std::vector<std::pair<uint64_t, uint64_t>> result;\n    result.reserve(values.size()\
    \ * 2);\n    for (GaussianInteger gaussian : values) {\n        two_square_sum_detail::add_nonnegative_pairs(result,\
    \ gaussian, real_scale);\n    }\n\n    std::sort(result.begin(), result.end());\n\
    \    result.erase(std::unique(result.begin(), result.end()), result.end());\n\
    \    return result;\n}\n\ninline std::vector<std::pair<uint64_t, uint64_t>> represent_as_two_square_sum(uint64_t\
    \ value) {\n    return two_square_sum(value);\n}\n\ninline bool is_two_square_sum(uint64_t\
    \ value) {\n    if (value == 0) return true;\n    for (const auto& factor : prime_factorize(value))\
    \ {\n        if (factor.first % 4 == 3 && (factor.second & 1) != 0) return false;\n\
    \    }\n    return true;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 29 \"math/all.hpp\"\n\n\n#line 12 \"verify/math/math_algorithms.test.cpp\"\
    \n\nlong long floor_div(long long numerator, long long denominator) {\n    long\
    \ long quotient = numerator / denominator;\n    if (numerator % denominator <\
    \ 0) quotient--;\n    return quotient;\n}\n\nvoid test_number_theory() {\n   \
    \ using m1une::math::crt;\n    using m1une::math::floor_sum;\n    using m1une::math::inv_gcd;\n\
    \    using m1une::math::inv_mod;\n    using m1une::math::pow_mod;\n\n    assert(pow_mod(-2,\
    \ 5, 13) == 7);\n    assert(pow_mod(123, 0, 1) == 0);\n    assert(inv_mod(3, 11)\
    \ == 4);\n\n    const auto inverse = inv_gcd(6, 15);\n    assert(inverse.first\
    \ == 3);\n    assert((6 * inverse.second - inverse.first) % 15 == 0);\n\n    const\
    \ auto solution = crt(\n        std::vector<long long>{2, 3, 2},\n        std::vector<long\
    \ long>{3, 5, 7}\n    );\n    assert(solution.first == 23);\n    assert(solution.second\
    \ == 105);\n    const auto inconsistent = crt(\n        std::vector<long long>{0,\
    \ 1},\n        std::vector<long long>{2, 4}\n    );\n    assert(inconsistent.second\
    \ == 0);\n\n    for (long long first_mod = 1; first_mod <= 12; first_mod++) {\n\
    \        for (long long second_mod = 1; second_mod <= 12; second_mod++) {\n  \
    \          const long long combined_mod = std::lcm(first_mod, second_mod);\n \
    \           for (long long first_remainder = -5; first_remainder <= 5;\n     \
    \            first_remainder++) {\n                for (long long second_remainder\
    \ = -5; second_remainder <= 5;\n                     second_remainder++) {\n \
    \                   long long expected = -1;\n                    for (long long\
    \ value = 0; value < combined_mod; value++) {\n                        if (\n\
    \                            (value - first_remainder) % first_mod == 0 &&\n \
    \                           (value - second_remainder) % second_mod == 0\n   \
    \                     ) {\n                            expected = value;\n   \
    \                         break;\n                        }\n                \
    \    }\n                    const auto actual = crt(\n                       \
    \ std::vector<long long>{first_remainder, second_remainder},\n               \
    \         std::vector<long long>{first_mod, second_mod}\n                    );\n\
    \                    if (expected == -1) {\n                        assert(actual.second\
    \ == 0);\n                    } else {\n                        assert(actual.first\
    \ == expected);\n                        assert(actual.second == combined_mod);\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    for (long long n = 0; n <= 15; n++) {\n        for (long long mod = 1; mod\
    \ <= 15; mod++) {\n            for (long long a = -15; a <= 15; a++) {\n     \
    \           for (long long b = -15; b <= 15; b++) {\n                    long\
    \ long expected = 0;\n                    for (long long i = 0; i < n; i++) {\n\
    \                        expected += floor_div(a * i + b, mod);\n            \
    \        }\n                    assert(floor_sum(n, mod, a, b) == expected);\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid test_prime_sieve()\
    \ {\n    m1une::math::PrimeSieve sieve(100);\n    assert(sieve.primes().size()\
    \ == 25);\n    assert(sieve.is_prime(97));\n    assert(!sieve.is_prime(1));\n\
    \    assert(sieve.min_prime_factor(91) == 7);\n\n    std::vector<std::pair<int,\
    \ int>> factors_72;\n    factors_72.emplace_back(2, 3);\n    factors_72.emplace_back(3,\
    \ 2);\n    assert(sieve.factorize(72) == factors_72);\n\n    std::vector<std::pair<int,\
    \ int>> factors_90;\n    factors_90.emplace_back(2, 1);\n    factors_90.emplace_back(3,\
    \ 2);\n    factors_90.emplace_back(5, 1);\n    assert(sieve.factorize(90) == factors_90);\n\
    \n    const std::vector<int> expected_divisors = {1, 2, 3, 4, 6, 12};\n    assert(sieve.divisors(12)\
    \ == expected_divisors);\n    assert(sieve.totient(36) == 12);\n    assert(sieve.mobius(30)\
    \ == -1);\n    assert(sieve.mobius(12) == 0);\n    assert(sieve.totient_table()[36]\
    \ == 12);\n    assert(sieve.mobius_table()[30] == -1);\n}\n\nvoid test_large_factorization()\
    \ {\n    using m1une::math::divisors;\n    using m1une::math::euler_phi;\n   \
    \ using m1une::math::is_prime;\n    using m1une::math::mobius;\n    using m1une::math::prime_factorize;\n\
    \n    assert(is_prime(2));\n    assert(is_prime(18446744073709551557ULL));\n \
    \   assert(!is_prime(341550071728321ULL));\n\n    const uint64_t semiprime = 1000000007ULL\
    \ * 1000000009ULL;\n    const auto factors = prime_factorize(semiprime);\n   \
    \ assert(factors.size() == 2);\n    assert((factors[0] == std::pair<uint64_t,\
    \ int>(1000000007ULL, 1)));\n    assert((factors[1] == std::pair<uint64_t, int>(1000000009ULL,\
    \ 1)));\n\n    const std::vector<uint64_t> expected_divisors = {1, 2, 3, 4, 6,\
    \ 9, 12, 18, 36};\n    assert(divisors(36) == expected_divisors);\n    assert(euler_phi(36)\
    \ == 12);\n    assert(mobius(30) == -1);\n    assert(mobius(12) == 0);\n\n   \
    \ m1une::math::PrimeSieve sieve(10000);\n    for (int value = 1; value <= sieve.limit();\
    \ value++) {\n        const auto small_factors = sieve.factorize(value);\n   \
    \     const auto large_factors = prime_factorize(value);\n        assert(small_factors.size()\
    \ == large_factors.size());\n        for (int i = 0; i < int(small_factors.size());\
    \ i++) {\n            assert(uint64_t(small_factors[i].first) == large_factors[i].first);\n\
    \            assert(small_factors[i].second == large_factors[i].second);\n   \
    \     }\n    }\n}\n\nvoid test_primitive_root() {\n    using m1une::math::euler_phi;\n\
    \    using m1une::math::has_primitive_root;\n    using m1une::math::primitive_root;\n\
    \n    assert(primitive_root(2) == 1);\n    assert(primitive_root(4) == 3);\n \
    \   assert(primitive_root(18) == 5);\n    assert(primitive_root(998244353) ==\
    \ 3);\n    assert(primitive_root(1000000007) == 5);\n    assert(!has_primitive_root(8));\n\
    \    assert(!has_primitive_root(12));\n    assert(primitive_root(8) == 0);\n\n\
    \    for (uint64_t mod = 2; mod <= 200; mod++) {\n        const uint64_t root\
    \ = primitive_root(mod);\n        const uint64_t phi = euler_phi(mod);\n     \
    \   if (root == 0) {\n            assert(!has_primitive_root(mod));\n        \
    \    bool found = false;\n            for (uint64_t candidate = 1; candidate <\
    \ mod; candidate++) {\n                if (std::gcd(candidate, mod) != 1) continue;\n\
    \                uint64_t value = 1;\n                uint64_t order = 0;\n  \
    \              do {\n                    value = value * candidate % mod;\n  \
    \                  order++;\n                } while (value != 1);\n         \
    \       if (order == phi) found = true;\n            }\n            assert(!found);\n\
    \            continue;\n        }\n\n        assert(has_primitive_root(mod));\n\
    \        assert(std::gcd(root, mod) == 1);\n\n        uint64_t value = 1;\n  \
    \      for (uint64_t exponent = 1; exponent < phi; exponent++) {\n           \
    \ value = value * root % mod;\n            assert(value != 1);\n        }\n  \
    \      value = value * root % mod;\n        assert(value == 1);\n\n        for\
    \ (uint64_t candidate = 1; candidate < root; candidate++) {\n            if (std::gcd(candidate,\
    \ mod) != 1) continue;\n            value = 1;\n            uint64_t order = 0;\n\
    \            do {\n                value = value * candidate % mod;\n        \
    \        order++;\n            } while (value != 1);\n            assert(order\
    \ != phi);\n        }\n    }\n}\n\nvoid test_totient_sum() {\n    using m1une::math::totient_sum;\n\
    \    using m1une::math::TotientSum;\n\n    TotientSum solver(100);\n    assert(solver.precalculation_limit()\
    \ == 100);\n    assert(solver.prefix_sum(0) == 0);\n    assert(solver.prefix_sum(1)\
    \ == 1);\n    assert(solver(10) == 32);\n    assert(totient_sum(100, 10) == 3044);\n\
    \n    m1une::math::PrimeSieve sieve(20000);\n    const std::vector<int> phi =\
    \ sieve.totient_table();\n    __uint128_t expected = 0;\n    for (int value =\
    \ 1; value <= 20000; value++) {\n        expected += static_cast<uint64_t>(phi[value]);\n\
    \        assert(solver.prefix_sum(value) == expected);\n    }\n\n    for (uint64_t\
    \ n : std::vector<uint64_t>{1, 2, 10, 100, 1000, 10000}) {\n        __uint128_t\
    \ left = 0;\n        for (uint64_t q = 1; q <= n;) {\n            const uint64_t\
    \ quotient = n / q;\n            const uint64_t next = n / quotient + 1;\n   \
    \         left += static_cast<__uint128_t>(next - q) * solver.prefix_sum(quotient);\n\
    \            q = next;\n        }\n        const __uint128_t wide_n = n;\n   \
    \     assert(left == wide_n * (wide_n + 1) / 2);\n    }\n}\n\nvoid test_combinatorics()\
    \ {\n    using Mint = m1une::math::modint998244353;\n    m1une::math::Combinatorics<Mint>\
    \ combinations(100);\n\n    assert(combinations.factorial(5) == Mint(120));\n\
    \    assert(combinations.inverse(5) * Mint(5) == Mint(1));\n    assert(combinations.binom(10,\
    \ 3) == Mint(120));\n    assert(combinations.binom(3, 5) == Mint(0));\n    assert(combinations.perm(5,\
    \ 3) == Mint(60));\n    assert(combinations.multiset(3, 4) == Mint(15));\n   \
    \ assert(combinations.multiset(0, 0) == Mint(1));\n    assert(combinations.catalan(5)\
    \ == Mint(42));\n\n    assert(combinations.binom(100, 0) == Mint(1));\n    assert(combinations.binom(100,\
    \ 100) == Mint(1));\n}\n\nvoid test_combinatorial_sequences() {\n    using Mint\
    \ = m1une::math::modint998244353;\n\n    const std::vector<Mint> catalan = m1une::math::catalan_numbers<Mint>(10);\n\
    \    const std::vector<int> expected_catalan =\n        {1, 1, 2, 5, 14, 42, 132,\
    \ 429, 1430, 4862, 16796};\n    for (int i = 0; i <= 10; i++) assert(catalan[i]\
    \ == Mint(expected_catalan[i]));\n    m1une::math::Combinatorics<Mint> catalan_combinations(100);\n\
    \    const std::vector<Mint> more_catalan =\n        m1une::math::catalan_numbers<Mint>(50);\n\
    \    for (int i = 0; i <= 50; i++) {\n        assert(more_catalan[i] == catalan_combinations.catalan(i));\n\
    \    }\n\n    const std::vector<Mint> bernoulli = m1une::math::bernoulli_numbers<Mint>(20);\n\
    \    assert(bernoulli[0] == Mint(1));\n    assert(bernoulli[1] * Mint(2) == Mint(-1));\n\
    \    assert(bernoulli[2] * Mint(6) == Mint(1));\n    assert(bernoulli[4] * Mint(30)\
    \ == Mint(-1));\n    assert(bernoulli[6] * Mint(42) == Mint(1));\n    for (int\
    \ i = 3; i <= 19; i += 2) assert(bernoulli[i] == Mint(0));\n\n    m1une::math::Combinatorics<Mint>\
    \ combinations(21);\n    for (int n = 1; n <= 20; n++) {\n        Mint sum = 0;\n\
    \        for (int k = 0; k <= n; k++) {\n            sum += combinations.binom(n\
    \ + 1, k) * bernoulli[k];\n        }\n        assert(sum == Mint(0));\n    }\n\
    \n    const std::vector<Mint> bell = m1une::math::bell_numbers<Mint>(10);\n  \
    \  const std::vector<int> expected_bell =\n        {1, 1, 2, 5, 15, 52, 203, 877,\
    \ 4140, 21147, 115975};\n    for (int i = 0; i <= 10; i++) assert(bell[i] == Mint(expected_bell[i]));\n\
    \n    const std::vector<Mint> stirling_zero =\n        m1une::math::stirling_numbers_second_kind<Mint>(0);\n\
    \    assert(stirling_zero == std::vector<Mint>{Mint(1)});\n    const std::vector<Mint>\
    \ stirling =\n        m1une::math::stirling_numbers_second_kind<Mint>(5);\n  \
    \  const std::vector<int> expected_stirling = {0, 1, 15, 25, 10, 1};\n    for\
    \ (int i = 0; i <= 5; i++) {\n        assert(stirling[i] == Mint(expected_stirling[i]));\n\
    \    }\n    std::vector<Mint> stirling_dp(1, Mint(1));\n    const std::vector<Mint>\
    \ more_bell = m1une::math::bell_numbers<Mint>(30);\n    for (int n = 0; n <= 30;\
    \ n++) {\n        if (n > 0) {\n            std::vector<Mint> next(n + 1);\n \
    \           for (int k = 1; k <= n; k++) {\n                next[k] = stirling_dp[k\
    \ - 1];\n                if (k < int(stirling_dp.size())) {\n                \
    \    next[k] += Mint(k) * stirling_dp[k];\n                }\n            }\n\
    \            stirling_dp = std::move(next);\n        }\n        const std::vector<Mint>\
    \ row =\n            m1une::math::stirling_numbers_second_kind<Mint>(n);\n   \
    \     assert(row == stirling_dp);\n        Mint sum = 0;\n        for (Mint value\
    \ : row) sum += value;\n        assert(sum == more_bell[n]);\n    }\n\n    const\
    \ std::vector<Mint> partitions = m1une::math::partition_numbers<Mint>(100);\n\
    \    const std::vector<int> expected_partitions =\n        {1, 1, 2, 3, 5, 7,\
    \ 11, 15, 22, 30, 42};\n    for (int i = 0; i <= 10; i++) {\n        assert(partitions[i]\
    \ == Mint(expected_partitions[i]));\n    }\n    std::vector<Mint> partition_dp(101);\n\
    \    partition_dp[0] = 1;\n    for (int part = 1; part <= 100; part++) {\n   \
    \     for (int sum = part; sum <= 100; sum++) {\n            partition_dp[sum]\
    \ += partition_dp[sum - part];\n        }\n    }\n    assert(partitions == partition_dp);\n\
    \n    const std::vector<Mint> derangements =\n        m1une::math::derangement_numbers<Mint>(10);\n\
    \    const std::vector<int> expected_derangements =\n        {1, 0, 1, 2, 9, 44,\
    \ 265, 1854, 14833, 133496, 1334961};\n    for (int i = 0; i <= 10; i++) {\n \
    \       assert(derangements[i] == Mint(expected_derangements[i]));\n    }\n  \
    \  m1une::math::Combinatorics<Mint> derangement_combinations(30);\n    const std::vector<Mint>\
    \ more_derangements =\n        m1une::math::derangement_numbers<Mint>(30);\n \
    \   Mint alternating_sum = 1;\n    for (int n = 0; n <= 30; n++) {\n        if\
    \ (n > 0) {\n            const Mint term = derangement_combinations.inverse_factorial(n);\n\
    \            alternating_sum += (n & 1) ? Mint(0) - term : term;\n        }\n\
    \        assert(\n            more_derangements[n] ==\n            derangement_combinations.factorial(n)\
    \ * alternating_sum\n        );\n    }\n}\n\nint main() {\n    test_number_theory();\n\
    \    test_prime_sieve();\n    test_large_factorization();\n    test_primitive_root();\n\
    \    test_totient_sum();\n    test_combinatorics();\n    test_combinatorial_sequences();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../math/all.hpp\"\n\nlong\
    \ long floor_div(long long numerator, long long denominator) {\n    long long\
    \ quotient = numerator / denominator;\n    if (numerator % denominator < 0) quotient--;\n\
    \    return quotient;\n}\n\nvoid test_number_theory() {\n    using m1une::math::crt;\n\
    \    using m1une::math::floor_sum;\n    using m1une::math::inv_gcd;\n    using\
    \ m1une::math::inv_mod;\n    using m1une::math::pow_mod;\n\n    assert(pow_mod(-2,\
    \ 5, 13) == 7);\n    assert(pow_mod(123, 0, 1) == 0);\n    assert(inv_mod(3, 11)\
    \ == 4);\n\n    const auto inverse = inv_gcd(6, 15);\n    assert(inverse.first\
    \ == 3);\n    assert((6 * inverse.second - inverse.first) % 15 == 0);\n\n    const\
    \ auto solution = crt(\n        std::vector<long long>{2, 3, 2},\n        std::vector<long\
    \ long>{3, 5, 7}\n    );\n    assert(solution.first == 23);\n    assert(solution.second\
    \ == 105);\n    const auto inconsistent = crt(\n        std::vector<long long>{0,\
    \ 1},\n        std::vector<long long>{2, 4}\n    );\n    assert(inconsistent.second\
    \ == 0);\n\n    for (long long first_mod = 1; first_mod <= 12; first_mod++) {\n\
    \        for (long long second_mod = 1; second_mod <= 12; second_mod++) {\n  \
    \          const long long combined_mod = std::lcm(first_mod, second_mod);\n \
    \           for (long long first_remainder = -5; first_remainder <= 5;\n     \
    \            first_remainder++) {\n                for (long long second_remainder\
    \ = -5; second_remainder <= 5;\n                     second_remainder++) {\n \
    \                   long long expected = -1;\n                    for (long long\
    \ value = 0; value < combined_mod; value++) {\n                        if (\n\
    \                            (value - first_remainder) % first_mod == 0 &&\n \
    \                           (value - second_remainder) % second_mod == 0\n   \
    \                     ) {\n                            expected = value;\n   \
    \                         break;\n                        }\n                \
    \    }\n                    const auto actual = crt(\n                       \
    \ std::vector<long long>{first_remainder, second_remainder},\n               \
    \         std::vector<long long>{first_mod, second_mod}\n                    );\n\
    \                    if (expected == -1) {\n                        assert(actual.second\
    \ == 0);\n                    } else {\n                        assert(actual.first\
    \ == expected);\n                        assert(actual.second == combined_mod);\n\
    \                    }\n                }\n            }\n        }\n    }\n\n\
    \    for (long long n = 0; n <= 15; n++) {\n        for (long long mod = 1; mod\
    \ <= 15; mod++) {\n            for (long long a = -15; a <= 15; a++) {\n     \
    \           for (long long b = -15; b <= 15; b++) {\n                    long\
    \ long expected = 0;\n                    for (long long i = 0; i < n; i++) {\n\
    \                        expected += floor_div(a * i + b, mod);\n            \
    \        }\n                    assert(floor_sum(n, mod, a, b) == expected);\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid test_prime_sieve()\
    \ {\n    m1une::math::PrimeSieve sieve(100);\n    assert(sieve.primes().size()\
    \ == 25);\n    assert(sieve.is_prime(97));\n    assert(!sieve.is_prime(1));\n\
    \    assert(sieve.min_prime_factor(91) == 7);\n\n    std::vector<std::pair<int,\
    \ int>> factors_72;\n    factors_72.emplace_back(2, 3);\n    factors_72.emplace_back(3,\
    \ 2);\n    assert(sieve.factorize(72) == factors_72);\n\n    std::vector<std::pair<int,\
    \ int>> factors_90;\n    factors_90.emplace_back(2, 1);\n    factors_90.emplace_back(3,\
    \ 2);\n    factors_90.emplace_back(5, 1);\n    assert(sieve.factorize(90) == factors_90);\n\
    \n    const std::vector<int> expected_divisors = {1, 2, 3, 4, 6, 12};\n    assert(sieve.divisors(12)\
    \ == expected_divisors);\n    assert(sieve.totient(36) == 12);\n    assert(sieve.mobius(30)\
    \ == -1);\n    assert(sieve.mobius(12) == 0);\n    assert(sieve.totient_table()[36]\
    \ == 12);\n    assert(sieve.mobius_table()[30] == -1);\n}\n\nvoid test_large_factorization()\
    \ {\n    using m1une::math::divisors;\n    using m1une::math::euler_phi;\n   \
    \ using m1une::math::is_prime;\n    using m1une::math::mobius;\n    using m1une::math::prime_factorize;\n\
    \n    assert(is_prime(2));\n    assert(is_prime(18446744073709551557ULL));\n \
    \   assert(!is_prime(341550071728321ULL));\n\n    const uint64_t semiprime = 1000000007ULL\
    \ * 1000000009ULL;\n    const auto factors = prime_factorize(semiprime);\n   \
    \ assert(factors.size() == 2);\n    assert((factors[0] == std::pair<uint64_t,\
    \ int>(1000000007ULL, 1)));\n    assert((factors[1] == std::pair<uint64_t, int>(1000000009ULL,\
    \ 1)));\n\n    const std::vector<uint64_t> expected_divisors = {1, 2, 3, 4, 6,\
    \ 9, 12, 18, 36};\n    assert(divisors(36) == expected_divisors);\n    assert(euler_phi(36)\
    \ == 12);\n    assert(mobius(30) == -1);\n    assert(mobius(12) == 0);\n\n   \
    \ m1une::math::PrimeSieve sieve(10000);\n    for (int value = 1; value <= sieve.limit();\
    \ value++) {\n        const auto small_factors = sieve.factorize(value);\n   \
    \     const auto large_factors = prime_factorize(value);\n        assert(small_factors.size()\
    \ == large_factors.size());\n        for (int i = 0; i < int(small_factors.size());\
    \ i++) {\n            assert(uint64_t(small_factors[i].first) == large_factors[i].first);\n\
    \            assert(small_factors[i].second == large_factors[i].second);\n   \
    \     }\n    }\n}\n\nvoid test_primitive_root() {\n    using m1une::math::euler_phi;\n\
    \    using m1une::math::has_primitive_root;\n    using m1une::math::primitive_root;\n\
    \n    assert(primitive_root(2) == 1);\n    assert(primitive_root(4) == 3);\n \
    \   assert(primitive_root(18) == 5);\n    assert(primitive_root(998244353) ==\
    \ 3);\n    assert(primitive_root(1000000007) == 5);\n    assert(!has_primitive_root(8));\n\
    \    assert(!has_primitive_root(12));\n    assert(primitive_root(8) == 0);\n\n\
    \    for (uint64_t mod = 2; mod <= 200; mod++) {\n        const uint64_t root\
    \ = primitive_root(mod);\n        const uint64_t phi = euler_phi(mod);\n     \
    \   if (root == 0) {\n            assert(!has_primitive_root(mod));\n        \
    \    bool found = false;\n            for (uint64_t candidate = 1; candidate <\
    \ mod; candidate++) {\n                if (std::gcd(candidate, mod) != 1) continue;\n\
    \                uint64_t value = 1;\n                uint64_t order = 0;\n  \
    \              do {\n                    value = value * candidate % mod;\n  \
    \                  order++;\n                } while (value != 1);\n         \
    \       if (order == phi) found = true;\n            }\n            assert(!found);\n\
    \            continue;\n        }\n\n        assert(has_primitive_root(mod));\n\
    \        assert(std::gcd(root, mod) == 1);\n\n        uint64_t value = 1;\n  \
    \      for (uint64_t exponent = 1; exponent < phi; exponent++) {\n           \
    \ value = value * root % mod;\n            assert(value != 1);\n        }\n  \
    \      value = value * root % mod;\n        assert(value == 1);\n\n        for\
    \ (uint64_t candidate = 1; candidate < root; candidate++) {\n            if (std::gcd(candidate,\
    \ mod) != 1) continue;\n            value = 1;\n            uint64_t order = 0;\n\
    \            do {\n                value = value * candidate % mod;\n        \
    \        order++;\n            } while (value != 1);\n            assert(order\
    \ != phi);\n        }\n    }\n}\n\nvoid test_totient_sum() {\n    using m1une::math::totient_sum;\n\
    \    using m1une::math::TotientSum;\n\n    TotientSum solver(100);\n    assert(solver.precalculation_limit()\
    \ == 100);\n    assert(solver.prefix_sum(0) == 0);\n    assert(solver.prefix_sum(1)\
    \ == 1);\n    assert(solver(10) == 32);\n    assert(totient_sum(100, 10) == 3044);\n\
    \n    m1une::math::PrimeSieve sieve(20000);\n    const std::vector<int> phi =\
    \ sieve.totient_table();\n    __uint128_t expected = 0;\n    for (int value =\
    \ 1; value <= 20000; value++) {\n        expected += static_cast<uint64_t>(phi[value]);\n\
    \        assert(solver.prefix_sum(value) == expected);\n    }\n\n    for (uint64_t\
    \ n : std::vector<uint64_t>{1, 2, 10, 100, 1000, 10000}) {\n        __uint128_t\
    \ left = 0;\n        for (uint64_t q = 1; q <= n;) {\n            const uint64_t\
    \ quotient = n / q;\n            const uint64_t next = n / quotient + 1;\n   \
    \         left += static_cast<__uint128_t>(next - q) * solver.prefix_sum(quotient);\n\
    \            q = next;\n        }\n        const __uint128_t wide_n = n;\n   \
    \     assert(left == wide_n * (wide_n + 1) / 2);\n    }\n}\n\nvoid test_combinatorics()\
    \ {\n    using Mint = m1une::math::modint998244353;\n    m1une::math::Combinatorics<Mint>\
    \ combinations(100);\n\n    assert(combinations.factorial(5) == Mint(120));\n\
    \    assert(combinations.inverse(5) * Mint(5) == Mint(1));\n    assert(combinations.binom(10,\
    \ 3) == Mint(120));\n    assert(combinations.binom(3, 5) == Mint(0));\n    assert(combinations.perm(5,\
    \ 3) == Mint(60));\n    assert(combinations.multiset(3, 4) == Mint(15));\n   \
    \ assert(combinations.multiset(0, 0) == Mint(1));\n    assert(combinations.catalan(5)\
    \ == Mint(42));\n\n    assert(combinations.binom(100, 0) == Mint(1));\n    assert(combinations.binom(100,\
    \ 100) == Mint(1));\n}\n\nvoid test_combinatorial_sequences() {\n    using Mint\
    \ = m1une::math::modint998244353;\n\n    const std::vector<Mint> catalan = m1une::math::catalan_numbers<Mint>(10);\n\
    \    const std::vector<int> expected_catalan =\n        {1, 1, 2, 5, 14, 42, 132,\
    \ 429, 1430, 4862, 16796};\n    for (int i = 0; i <= 10; i++) assert(catalan[i]\
    \ == Mint(expected_catalan[i]));\n    m1une::math::Combinatorics<Mint> catalan_combinations(100);\n\
    \    const std::vector<Mint> more_catalan =\n        m1une::math::catalan_numbers<Mint>(50);\n\
    \    for (int i = 0; i <= 50; i++) {\n        assert(more_catalan[i] == catalan_combinations.catalan(i));\n\
    \    }\n\n    const std::vector<Mint> bernoulli = m1une::math::bernoulli_numbers<Mint>(20);\n\
    \    assert(bernoulli[0] == Mint(1));\n    assert(bernoulli[1] * Mint(2) == Mint(-1));\n\
    \    assert(bernoulli[2] * Mint(6) == Mint(1));\n    assert(bernoulli[4] * Mint(30)\
    \ == Mint(-1));\n    assert(bernoulli[6] * Mint(42) == Mint(1));\n    for (int\
    \ i = 3; i <= 19; i += 2) assert(bernoulli[i] == Mint(0));\n\n    m1une::math::Combinatorics<Mint>\
    \ combinations(21);\n    for (int n = 1; n <= 20; n++) {\n        Mint sum = 0;\n\
    \        for (int k = 0; k <= n; k++) {\n            sum += combinations.binom(n\
    \ + 1, k) * bernoulli[k];\n        }\n        assert(sum == Mint(0));\n    }\n\
    \n    const std::vector<Mint> bell = m1une::math::bell_numbers<Mint>(10);\n  \
    \  const std::vector<int> expected_bell =\n        {1, 1, 2, 5, 15, 52, 203, 877,\
    \ 4140, 21147, 115975};\n    for (int i = 0; i <= 10; i++) assert(bell[i] == Mint(expected_bell[i]));\n\
    \n    const std::vector<Mint> stirling_zero =\n        m1une::math::stirling_numbers_second_kind<Mint>(0);\n\
    \    assert(stirling_zero == std::vector<Mint>{Mint(1)});\n    const std::vector<Mint>\
    \ stirling =\n        m1une::math::stirling_numbers_second_kind<Mint>(5);\n  \
    \  const std::vector<int> expected_stirling = {0, 1, 15, 25, 10, 1};\n    for\
    \ (int i = 0; i <= 5; i++) {\n        assert(stirling[i] == Mint(expected_stirling[i]));\n\
    \    }\n    std::vector<Mint> stirling_dp(1, Mint(1));\n    const std::vector<Mint>\
    \ more_bell = m1une::math::bell_numbers<Mint>(30);\n    for (int n = 0; n <= 30;\
    \ n++) {\n        if (n > 0) {\n            std::vector<Mint> next(n + 1);\n \
    \           for (int k = 1; k <= n; k++) {\n                next[k] = stirling_dp[k\
    \ - 1];\n                if (k < int(stirling_dp.size())) {\n                \
    \    next[k] += Mint(k) * stirling_dp[k];\n                }\n            }\n\
    \            stirling_dp = std::move(next);\n        }\n        const std::vector<Mint>\
    \ row =\n            m1une::math::stirling_numbers_second_kind<Mint>(n);\n   \
    \     assert(row == stirling_dp);\n        Mint sum = 0;\n        for (Mint value\
    \ : row) sum += value;\n        assert(sum == more_bell[n]);\n    }\n\n    const\
    \ std::vector<Mint> partitions = m1une::math::partition_numbers<Mint>(100);\n\
    \    const std::vector<int> expected_partitions =\n        {1, 1, 2, 3, 5, 7,\
    \ 11, 15, 22, 30, 42};\n    for (int i = 0; i <= 10; i++) {\n        assert(partitions[i]\
    \ == Mint(expected_partitions[i]));\n    }\n    std::vector<Mint> partition_dp(101);\n\
    \    partition_dp[0] = 1;\n    for (int part = 1; part <= 100; part++) {\n   \
    \     for (int sum = part; sum <= 100; sum++) {\n            partition_dp[sum]\
    \ += partition_dp[sum - part];\n        }\n    }\n    assert(partitions == partition_dp);\n\
    \n    const std::vector<Mint> derangements =\n        m1une::math::derangement_numbers<Mint>(10);\n\
    \    const std::vector<int> expected_derangements =\n        {1, 0, 1, 2, 9, 44,\
    \ 265, 1854, 14833, 133496, 1334961};\n    for (int i = 0; i <= 10; i++) {\n \
    \       assert(derangements[i] == Mint(expected_derangements[i]));\n    }\n  \
    \  m1une::math::Combinatorics<Mint> derangement_combinations(30);\n    const std::vector<Mint>\
    \ more_derangements =\n        m1une::math::derangement_numbers<Mint>(30);\n \
    \   Mint alternating_sum = 1;\n    for (int n = 0; n <= 30; n++) {\n        if\
    \ (n > 0) {\n            const Mint term = derangement_combinations.inverse_factorial(n);\n\
    \            alternating_sum += (n & 1) ? Mint(0) - term : term;\n        }\n\
    \        assert(\n            more_derangements[n] ==\n            derangement_combinations.factorial(n)\
    \ * alternating_sum\n        );\n    }\n}\n\nint main() {\n    test_number_theory();\n\
    \    test_prime_sieve();\n    test_large_factorization();\n    test_primitive_root();\n\
    \    test_totient_sum();\n    test_combinatorics();\n    test_combinatorial_sequences();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/all.hpp
  - math/base_n.hpp
  - math/bernoulli.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  - math/bitwise_convolution.hpp
  - math/zeta_mobius_transform.hpp
  - math/bit_ceil.hpp
  - math/combinatorial_sequences.hpp
  - math/partition_function.hpp
  - math/cyclotomic_polynomial.hpp
  - math/prime_factorization.hpp
  - math/generalized_floor_sum.hpp
  - math/integer_arithmetic.hpp
  - math/lucas.hpp
  - math/fps/all.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/matrix/all.hpp
  - math/matrix/linear_algebra.hpp
  - math/matrix/matrix.hpp
  - math/modint.hpp
  - math/number_theory.hpp
  - math/primitive_root.hpp
  - math/prime_sieve.hpp
  - math/rational.hpp
  - math/repunit.hpp
  - math/stern_brocot_tree.hpp
  - math/tetration.hpp
  - math/totient_sum.hpp
  - math/two_square_sum.hpp
  isVerificationFile: true
  path: verify/math/math_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-10 21:34:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/math_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/math/math_algorithms.test.cpp
- /verify/verify/math/math_algorithms.test.cpp.html
title: verify/math/math_algorithms.test.cpp
---
