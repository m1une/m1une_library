---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':question:'
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
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
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
  bundledCode: "#line 1 \"verify/math/fps/fps_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <random>\n#include <vector>\n\n#line 1 \"math/fps/all.hpp\"\
    \n\n\n\n#line 1 \"math/fps/convolution.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <array>\n#line 8 \"math/fps/convolution.hpp\"\n#include <utility>\n#line 10\
    \ \"math/fps/convolution.hpp\"\n\n#if defined(__GNUC__) && !defined(__clang__)\
    \ && (defined(__x86_64__) || defined(__i386__))\n#include <immintrin.h>\n#define\
    \ M1UNE_FPS_HAS_X86_SIMD 1\n#endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line\
    \ 6 \"math/modint.hpp\"\n#include <type_traits>\n#line 8 \"math/modint.hpp\"\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt\
    \ {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
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
    \ m1une\n\n\n#line 17 \"math/fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ntemplate <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse, bool normalize\
    \ = true) {\n    const int n = int(a.size());\n    assert(n > 0 && (n & (n - 1))\
    \ == 0);\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n    const auto&\
    \ roots = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\
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
    \ : a) value *= inverse_n;\n        }\n    }\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \n#pragma GCC push_options\n#pragma GCC target(\"avx2,bmi\")\n\nstruct Montgomery998Simd\
    \ {\n    static constexpr uint32_t mod = 998244353;\n    static constexpr uint32_t\
    \ mod2 = 2 * mod;\n    uint32_t negative_inverse;\n    uint32_t r;\n    uint32_t\
    \ r2;\n    __m256i modulus;\n    __m256i inverse;\n\n    Montgomery998Simd()\n\
    \        : negative_inverse(1),\n          r(uint32_t((uint64_t(1) << 32) % mod)),\n\
    \          r2(uint32_t(uint64_t(r) * r % mod)) {\n        for (int i = 0; i <\
    \ 5; i++) negative_inverse *= 2 + negative_inverse * mod;\n        modulus = _mm256_set1_epi32(int(mod));\n\
    \        inverse = _mm256_set1_epi32(int(negative_inverse));\n    }\n\n    uint32_t\
    \ shrink(uint32_t value) const {\n        return std::min(value, value - mod);\n\
    \    }\n\n    uint32_t reduce(uint64_t value) const {\n        return uint32_t((value\
    \ + uint64_t(uint32_t(value) * negative_inverse) * mod) >> 32);\n    }\n\n   \
    \ uint32_t multiply(uint32_t lhs, uint32_t rhs) const {\n        return shrink(reduce(uint64_t(lhs)\
    \ * rhs));\n    }\n\n    uint32_t encode(uint32_t value) const {\n        return\
    \ multiply(value, r2);\n    }\n\n    __m256i shrink(__m256i value) const {\n \
    \       return _mm256_min_epu32(value, _mm256_sub_epi32(value, modulus));\n  \
    \  }\n\n    __m256i multiply(__m256i lhs, __m256i rhs) const {\n        const\
    \ __m256i lhs_odd = _mm256_bsrli_epi128(lhs, 4);\n        const __m256i rhs_odd\
    \ = _mm256_bsrli_epi128(rhs, 4);\n        __m256i even = _mm256_mul_epu32(lhs,\
    \ rhs);\n        __m256i odd = _mm256_mul_epu32(lhs_odd, rhs_odd);\n        __m256i\
    \ even_correction = _mm256_mul_epu32(even, inverse);\n        __m256i odd_correction\
    \ = _mm256_mul_epu32(odd, inverse);\n        even_correction = _mm256_mul_epu32(even_correction,\
    \ modulus);\n        odd_correction = _mm256_mul_epu32(odd_correction, modulus);\n\
    \        even = _mm256_add_epi64(even, even_correction);\n        odd = _mm256_add_epi64(odd,\
    \ odd_correction);\n        return shrink(_mm256_or_si256(_mm256_bsrli_epi128(even,\
    \ 4), odd));\n    }\n\n    __m256i add(__m256i lhs, __m256i rhs) const {\n   \
    \     return shrink(_mm256_add_epi32(lhs, rhs));\n    }\n\n    __m256i subtract(__m256i\
    \ lhs, __m256i rhs) const {\n        const __m256i difference = _mm256_sub_epi32(lhs,\
    \ rhs);\n        return _mm256_min_epu32(difference, _mm256_add_epi32(difference,\
    \ modulus));\n    }\n};\n\ntemplate <class Mint>\n__attribute__((target(\"avx2,bmi\"\
    ), hot))\nvoid ntt_998244353_simd(uint32_t* data, int n, bool inverse, bool normalize\
    \ = true) {\n    static const Montgomery998Simd montgomery;\n    const auto& roots\
    \ = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\n\
    \    if (!inverse) {\n        for (int phase = 1; phase <= height; phase++) {\n\
    \            const int blocks = 1 << (phase - 1);\n            const int width\
    \ = 1 << (height - phase);\n            uint32_t twiddle = montgomery.r;\n   \
    \         for (int block = 0; block < blocks; block++) {\n                const\
    \ int offset = block << (height - phase + 1);\n                const __m256i vector_twiddle\
    \ = _mm256_set1_epi32(int(twiddle));\n                int i = 0;\n           \
    \     for (; i + 8 <= width; i += 8) {\n                    const __m256i lhs\
    \ = _mm256_loadu_si256(\n                        reinterpret_cast<const __m256i*>(data\
    \ + offset + i));\n                    const __m256i rhs = _mm256_loadu_si256(\n\
    \                        reinterpret_cast<const __m256i*>(data + offset + width\
    \ + i));\n                    const __m256i weighted_rhs = montgomery.multiply(rhs,\
    \ vector_twiddle);\n                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data\
    \ + offset + i),\n                                       montgomery.add(lhs, weighted_rhs));\n\
    \                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset\
    \ + width + i),\n                                       montgomery.subtract(lhs,\
    \ weighted_rhs));\n                }\n                for (; i < width; i++) {\n\
    \                    const uint32_t lhs = data[offset + i];\n                \
    \    const uint32_t rhs = data[offset + width + i];\n                    const\
    \ uint32_t weighted_rhs = montgomery.multiply(rhs, twiddle);\n               \
    \     uint32_t sum = lhs + weighted_rhs;\n                    if (sum >= Montgomery998Simd::mod)\
    \ sum -= Montgomery998Simd::mod;\n                    uint32_t difference = lhs\
    \ >= weighted_rhs\n                                              ? lhs - weighted_rhs\n\
    \                                              : lhs + Montgomery998Simd::mod\
    \ - weighted_rhs;\n                    data[offset + i] = sum;\n             \
    \       data[offset + width + i] = difference;\n                }\n          \
    \      if (block + 1 != blocks) {\n                    const uint32_t rate = montgomery.encode(\n\
    \                        roots.rate[__builtin_ctz(~uint32_t(block))].val());\n\
    \                    twiddle = montgomery.multiply(twiddle, rate);\n         \
    \       }\n            }\n        }\n    } else {\n        for (int phase = height;\
    \ phase >= 1; phase--) {\n            const int blocks = 1 << (phase - 1);\n \
    \           const int width = 1 << (height - phase);\n            uint32_t twiddle\
    \ = montgomery.r;\n            for (int block = 0; block < blocks; block++) {\n\
    \                const int offset = block << (height - phase + 1);\n         \
    \       const __m256i vector_twiddle = _mm256_set1_epi32(int(twiddle));\n    \
    \            int i = 0;\n                for (; i + 8 <= width; i += 8) {\n  \
    \                  const __m256i lhs = _mm256_loadu_si256(\n                 \
    \       reinterpret_cast<const __m256i*>(data + offset + i));\n              \
    \      const __m256i rhs = _mm256_loadu_si256(\n                        reinterpret_cast<const\
    \ __m256i*>(data + offset + width + i));\n                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data\
    \ + offset + i),\n                                       montgomery.add(lhs, rhs));\n\
    \                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset\
    \ + width + i),\n                                       montgomery.multiply(montgomery.subtract(lhs,\
    \ rhs),\n                                                           vector_twiddle));\n\
    \                }\n                for (; i < width; i++) {\n               \
    \     const uint32_t lhs = data[offset + i];\n                    const uint32_t\
    \ rhs = data[offset + width + i];\n                    uint32_t sum = lhs + rhs;\n\
    \                    if (sum >= Montgomery998Simd::mod) sum -= Montgomery998Simd::mod;\n\
    \                    uint32_t difference = lhs >= rhs ? lhs - rhs : lhs + Montgomery998Simd::mod\
    \ - rhs;\n                    data[offset + i] = sum;\n                    data[offset\
    \ + width + i] = montgomery.multiply(difference, twiddle);\n                }\n\
    \                if (block + 1 != blocks) {\n                    const uint32_t\
    \ rate = montgomery.encode(\n                        roots.inverse_rate[__builtin_ctz(~uint32_t(block))].val());\n\
    \                    twiddle = montgomery.multiply(twiddle, rate);\n         \
    \       }\n            }\n        }\n        if (normalize) {\n            const\
    \ uint32_t scale = montgomery.encode(Mint(n).inv().val());\n            const\
    \ __m256i vector_scale = _mm256_set1_epi32(int(scale));\n            int i = 0;\n\
    \            for (; i + 8 <= n; i += 8) {\n                __m256i values =\n\
    \                    _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data\
    \ + i));\n                _mm256_storeu_si256(reinterpret_cast<__m256i*>(data\
    \ + i),\n                                   montgomery.multiply(values, vector_scale));\n\
    \            }\n            for (; i < n; i++) data[i] = montgomery.multiply(data[i],\
    \ scale);\n        }\n    }\n}\n\ntemplate <class Mint>\n__attribute__((target(\"\
    avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_simd(const std::vector<Mint>&\
    \ a,\n                                             const std::vector<Mint>& b)\
    \ {\n    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n\
    \    while (n < result_size) n <<= 1;\n    std::vector<uint32_t> transformed_a(n);\n\
    \    std::vector<uint32_t> transformed_b(n);\n    for (int i = 0; i < int(a.size());\
    \ i++) transformed_a[i] = a[i].val();\n    for (int i = 0; i < int(b.size());\
    \ i++) transformed_b[i] = b[i].val();\n    ntt_998244353_simd<Mint>(transformed_a.data(),\
    \ n, false);\n    ntt_998244353_simd<Mint>(transformed_b.data(), n, false);\n\n\
    \    static const Montgomery998Simd montgomery;\n    // A normal-by-normal Montgomery\
    \ product is off by R^-1.  Scaling the\n    // inverse transform by n^-1 R compensates\
    \ for it without another pass.\n    const uint32_t inverse_n_montgomery = montgomery.encode(Mint(n).inv().val());\n\
    \    const uint32_t inverse_n_r2 = montgomery.multiply(inverse_n_montgomery, montgomery.r2);\n\
    \    const __m256i vector_scale = _mm256_set1_epi32(int(inverse_n_r2));\n    int\
    \ i = 0;\n    for (; i + 8 <= n; i += 8) {\n        const __m256i lhs =\n    \
    \        _mm256_loadu_si256(reinterpret_cast<const __m256i*>(transformed_a.data()\
    \ + i));\n        const __m256i rhs =\n            _mm256_loadu_si256(reinterpret_cast<const\
    \ __m256i*>(transformed_b.data() + i));\n        __m256i product = montgomery.multiply(lhs,\
    \ rhs);\n        product = montgomery.multiply(product, vector_scale);\n     \
    \   _mm256_storeu_si256(reinterpret_cast<__m256i*>(transformed_a.data() + i),\
    \ product);\n    }\n    for (; i < n; i++) {\n        uint32_t product = montgomery.multiply(transformed_a[i],\
    \ transformed_b[i]);\n        transformed_a[i] = montgomery.multiply(product,\
    \ inverse_n_r2);\n    }\n    ntt_998244353_simd<Mint>(transformed_a.data(), n,\
    \ true, false);\n\n    std::vector<Mint> result(result_size);\n    for (int j\
    \ = 0; j < result_size; j++) result[j] = Mint::raw(transformed_a[j]);\n    return\
    \ result;\n}\n\n#pragma GCC pop_options\n\n#endif\n\n}  // namespace internal\n\
    \ntemplate <class Mint>\nstd::vector<Mint> convolution_naive(const std::vector<Mint>&\
    \ a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size() < b.size())\
    \ {\n        for (int i = 0; i < int(a.size()); i++) {\n            for (int j\
    \ = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n        }\n    }\
    \ else {\n        for (int j = 0; j < int(b.size()); j++) {\n            for (int\
    \ i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n        }\n  \
    \  }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_ntt(const\
    \ std::vector<Mint>& a, const std::vector<Mint>& b) {\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \    if constexpr (Mint::mod() == 998244353) {\n        if (n >= 64 && __builtin_cpu_supports(\"\
    avx2\"))\n            return internal::convolution_998244353_simd(a, b);\n   \
    \ }\n#endif\n\n    // Allocate the padded buffers directly.  Constructing from\
    \ the inputs and\n    // then resizing used to allocate and copy both large operands\
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
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 1 \"math/fps/convolution_ll.hpp\"\
    \n\n\n\n#line 6 \"math/fps/convolution_ll.hpp\"\n#include <limits>\n#line 8 \"\
    math/fps/convolution_ll.hpp\"\n\n#line 11 \"math/fps/convolution_ll.hpp\"\n\n\
    namespace m1une {\nnamespace fps {\n\n// Exact convolution of signed 64-bit coefficients.\n\
    // Every result coefficient must fit in long long.\ninline std::vector<long long>\
    \ convolution_ll(\n    const std::vector<long long>& first,\n    const std::vector<long\
    \ long>& second\n) {\n    if (first.empty() || second.empty()) return {};\n  \
    \  std::size_t result_size = first.size() + second.size() - 1;\n    assert(result_size\
    \ <= (std::size_t(1) << 24));\n\n    using Mint1 = math::ModInt<167772161>;\n\
    \    using Mint2 = math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n\
    \n    auto convolve = [&]<class Mint>() {\n        std::vector<Mint> converted_first(first.size());\n\
    \        std::vector<Mint> converted_second(second.size());\n        for (int\
    \ index = 0; index < int(first.size()); index++) {\n            converted_first[index]\
    \ = Mint(first[index]);\n        }\n        for (int index = 0; index < int(second.size());\
    \ index++) {\n            converted_second[index] = Mint(second[index]);\n   \
    \     }\n        return convolution(converted_first, converted_second);\n    };\n\
    \n    std::vector<Mint1> result1 = convolve.template operator()<Mint1>();\n  \
    \  std::vector<Mint2> result2 = convolve.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ result3 = convolve.template operator()<Mint3>();\n\n    static const std::uint64_t\
    \ inverse_mod1_mod2 =\n        Mint2(Mint1::mod()).inv().val();\n    static const\
    \ std::uint64_t mod1_mod2 =\n        std::uint64_t(Mint1::mod()) * Mint2::mod();\n\
    \    static const std::uint64_t inverse_mod1_mod2_mod3 =\n        Mint3(mod1_mod2\
    \ % Mint3::mod()).inv().val();\n    static const unsigned __int128 crt_modulus\
    \ =\n        static_cast<unsigned __int128>(mod1_mod2) * Mint3::mod();\n\n   \
    \ std::vector<long long> result(result_size);\n    for (int index = 0; index <\
    \ int(result_size); index++) {\n        std::uint64_t residue1 = result1[index].val();\n\
    \        std::uint64_t residue2 = result2[index].val();\n        std::uint64_t\
    \ residue3 = result3[index].val();\n\n        std::uint64_t second_digit =\n \
    \           (residue2 + Mint2::mod() - residue1 % Mint2::mod()) %\n          \
    \  Mint2::mod();\n        second_digit = second_digit * inverse_mod1_mod2 % Mint2::mod();\n\
    \        std::uint64_t first_two =\n            residue1 + std::uint64_t(Mint1::mod())\
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
    \ <cmath>\n#include <complex>\n#include <concepts>\n#include <numbers>\n#line\
    \ 12 \"math/fps/floating_point_convolution.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\nnamespace floating_point_convolution_detail {\n\ntemplate <std::floating_point\
    \ Real>\nvoid fft(std::vector<std::complex<Real>>& values, bool inverse) {\n \
    \   int size = int(values.size());\n    for (int index = 1, reversed = 0; index\
    \ < size; ++index) {\n        int bit = size >> 1;\n        while (reversed &\
    \ bit) {\n            reversed ^= bit;\n            bit >>= 1;\n        }\n  \
    \      reversed ^= bit;\n        if (index < reversed) std::swap(values[index],\
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
    \n#line 1 \"math/fps/formal_power_series.hpp\"\n\n\n\n#line 7 \"math/fps/formal_power_series.hpp\"\
    \n#include <optional>\n#line 10 \"math/fps/formal_power_series.hpp\"\n\n#line\
    \ 12 \"math/fps/formal_power_series.hpp\"\n\nnamespace m1une {\nnamespace fps\
    \ {\n\nnamespace internal {\n\ntemplate <class Mint>\nstd::optional<Mint> modular_square_root(Mint\
    \ value) {\n    const uint32_t mod = Mint::mod();\n    if (value == Mint(0)) return\
    \ Mint(0);\n    if (mod == 2) return value;\n    if (value.pow((mod - 1) / 2)\
    \ != Mint(1)) return std::nullopt;\n    if (mod % 4 == 3) return value.pow((mod\
    \ + 1) / 4);\n\n    uint32_t q = mod - 1;\n    int s = 0;\n    while ((q & 1)\
    \ == 0) {\n        q >>= 1;\n        s++;\n    }\n\n    Mint z = 2;\n    while\
    \ (z.pow((mod - 1) / 2) == Mint(1)) ++z;\n    Mint c = z.pow(q);\n    Mint x =\
    \ value.pow((q + 1) / 2);\n    Mint t = value.pow(q);\n    int m = s;\n    while\
    \ (t != Mint(1)) {\n        int i = 1;\n        Mint squared = t * t;\n      \
    \  while (squared != Mint(1)) {\n            squared *= squared;\n           \
    \ i++;\n        }\n        Mint b = c.pow(uint64_t(1) << (m - i - 1));\n     \
    \   x *= b;\n        c = b * b;\n        t *= c;\n        m = i;\n    }\n    return\
    \ x;\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\nstruct FormalPowerSeries\
    \ : std::vector<Mint> {\n    using std::vector<Mint>::vector;\n    using Fps =\
    \ FormalPowerSeries;\n\n    FormalPowerSeries() = default;\n    FormalPowerSeries(const\
    \ std::vector<Mint>& values) : std::vector<Mint>(values) {}\n    FormalPowerSeries(std::vector<Mint>&&\
    \ values) : std::vector<Mint>(std::move(values)) {}\n\n    Fps& shrink() {\n \
    \       while (!this->empty() && this->back() == Mint(0)) this->pop_back();\n\
    \        return *this;\n    }\n\n    Fps pre(int degree) const {\n        assert(degree\
    \ >= 0);\n        Fps result(this->begin(), this->begin() + std::min<int>(degree,\
    \ this->size()));\n        result.resize(degree);\n        return result;\n  \
    \  }\n\n    Fps reversed(int size = -1) const {\n        Fps result = *this;\n\
    \        if (size >= 0) result.resize(size);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    Fps& operator+=(const Fps&\
    \ rhs) {\n        if (this->size() < rhs.size()) this->resize(rhs.size());\n \
    \       for (int i = 0; i < int(rhs.size()); i++) (*this)[i] += rhs[i];\n    \
    \    return *this;\n    }\n\n    Fps& operator-=(const Fps& rhs) {\n        if\
    \ (this->size() < rhs.size()) this->resize(rhs.size());\n        for (int i =\
    \ 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];\n        return *this;\n\
    \    }\n\n    Fps& operator*=(const Fps& rhs) {\n        std::vector<Mint> lhs(this->begin(),\
    \ this->end());\n        *this = convolution(lhs, rhs);\n        return *this;\n\
    \    }\n\n    Fps& operator*=(Mint rhs) {\n        for (Mint& value : *this) value\
    \ *= rhs;\n        return *this;\n    }\n\n    Fps& operator/=(Mint rhs) {\n \
    \       return *this *= rhs.inv();\n    }\n\n    Fps& operator<<=(int shift) {\n\
    \        assert(shift >= 0);\n        this->insert(this->begin(), shift, Mint(0));\n\
    \        return *this;\n    }\n\n    Fps& operator>>=(int shift) {\n        assert(shift\
    \ >= 0);\n        if (shift >= int(this->size())) {\n            this->clear();\n\
    \        } else {\n            this->erase(this->begin(), this->begin() + shift);\n\
    \        }\n        return *this;\n    }\n\n    Fps operator+() const {\n    \
    \    return *this;\n    }\n\n    Fps operator-() const {\n        Fps result =\
    \ *this;\n        for (Mint& value : result) value = Mint(0) - value;\n      \
    \  return result;\n    }\n\n    friend Fps operator+(Fps lhs, const Fps& rhs)\
    \ {\n        return lhs += rhs;\n    }\n\n    friend Fps operator-(Fps lhs, const\
    \ Fps& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Fps operator*(Fps\
    \ lhs, const Fps& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Fps\
    \ operator*(Fps lhs, Mint rhs) {\n        return lhs *= rhs;\n    }\n\n    friend\
    \ Fps operator*(Mint lhs, Fps rhs) {\n        return rhs *= lhs;\n    }\n\n  \
    \  friend Fps operator/(Fps lhs, Mint rhs) {\n        return lhs /= rhs;\n   \
    \ }\n\n    friend Fps operator<<(Fps lhs, int shift) {\n        return lhs <<=\
    \ shift;\n    }\n\n    friend Fps operator>>(Fps lhs, int shift) {\n        return\
    \ lhs >>= shift;\n    }\n\n    Fps derivative() const {\n        if (this->empty())\
    \ return {};\n        Fps result(this->size() - 1);\n        for (int i = 1; i\
    \ < int(this->size()); i++) result[i - 1] = (*this)[i] * Mint(i);\n        return\
    \ result;\n    }\n\n    Fps integral() const {\n        Fps result(this->size()\
    \ + 1);\n        if (this->empty()) return result;\n        assert(this->size()\
    \ < Mint::mod());\n\n        std::vector<Mint> inverse(this->size() + 1);\n  \
    \      inverse[1] = 1;\n        for (int i = 2; i <= int(this->size()); i++) {\n\
    \            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod()\
    \ % uint32_t(i)];\n        }\n        for (int i = 0; i < int(this->size()); i++)\
    \ result[i + 1] = (*this)[i] * inverse[i + 1];\n        return result;\n    }\n\
    \n    Mint evaluate(Mint x) const {\n        Mint result = 0;\n        for (auto\
    \ it = this->rbegin(); it != this->rend(); ++it) result = result * x + *it;\n\
    \        return result;\n    }\n\n    Fps inv(int degree = -1) const {\n     \
    \   if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ != Mint(0));\n\n        Fps result(1, (*this)[0].inv());\n        for (int size\
    \ = 1; size < degree; size <<= 1) {\n            const int next_size = std::min(size\
    \ << 1, degree);\n            const int transform_size = size << 1;\n        \
    \    if (size >= 32 && (Mint::mod() - 1) % uint32_t(transform_size) == 0) {\n\
    \                // Newton's g <- g(2-fg), restricted to the newly determined\n\
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
    \ namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/half_gcd.hpp\"\n\
    \n\n\n#line 7 \"math/fps/half_gcd.hpp\"\n\n#line 9 \"math/fps/half_gcd.hpp\"\n\
    \nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct PolynomialMatrix2x2\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n\n    Fps a00;\n    Fps a01;\n\
    \    Fps a10;\n    Fps a11;\n\n    static PolynomialMatrix2x2 identity() {\n \
    \       return PolynomialMatrix2x2{Fps(1, Mint(1)), Fps(), Fps(), Fps(1, Mint(1))};\n\
    \    }\n\n    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const\
    \ {\n        Fps result_first = a00 * first + a01 * second;\n        Fps result_second\
    \ = a10 * first + a11 * second;\n        result_first.shrink();\n        result_second.shrink();\n\
    \        return std::make_pair(std::move(result_first), std::move(result_second));\n\
    \    }\n\n    friend PolynomialMatrix2x2 operator*(const PolynomialMatrix2x2&\
    \ lhs,\n                                          const PolynomialMatrix2x2& rhs)\
    \ {\n        PolynomialMatrix2x2 result;\n        result.a00 = lhs.a00 * rhs.a00\
    \ + lhs.a01 * rhs.a10;\n        result.a01 = lhs.a00 * rhs.a01 + lhs.a01 * rhs.a11;\n\
    \        result.a10 = lhs.a10 * rhs.a00 + lhs.a11 * rhs.a10;\n        result.a11\
    \ = lhs.a10 * rhs.a01 + lhs.a11 * rhs.a11;\n        result.a00.shrink();\n   \
    \     result.a01.shrink();\n        result.a10.shrink();\n        result.a11.shrink();\n\
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
    \n\n\n#line 11 \"verify/math/fps/fps_algorithms.test.cpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    using mint1e9 = m1une::math::modint1000000007;\nusing Fps = m1une::fps::FormalPowerSeries<mint>;\n\
    \ntemplate <class Mint>\nvoid assert_equal(const std::vector<Mint>& lhs, const\
    \ std::vector<Mint>& rhs) {\n    assert(lhs.size() == rhs.size());\n    for (int\
    \ i = 0; i < int(lhs.size()); i++) assert(lhs[i] == rhs[i]);\n}\n\nvoid test_convolution()\
    \ {\n    std::mt19937 rng(712367);\n    for (int iteration = 0; iteration < 30;\
    \ iteration++) {\n        int n = 33 + int(rng() % 70);\n        int m = 33 +\
    \ int(rng() % 70);\n        std::vector<mint> a(n), b(m);\n        for (mint&\
    \ value : a) value = mint(static_cast<uint32_t>(rng()));\n        for (mint& value\
    \ : b) value = mint(static_cast<uint32_t>(rng()));\n        assert_equal(m1une::fps::convolution(a,\
    \ b), m1une::fps::convolution_naive(a, b));\n    }\n\n    std::vector<mint1e9>\
    \ a(70), b(65);\n    for (mint1e9& value : a) value = mint1e9(static_cast<uint32_t>(rng()));\n\
    \    for (mint1e9& value : b) value = mint1e9(static_cast<uint32_t>(rng()));\n\
    \    assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a,\
    \ b));\n}\n\nvoid test_series_functions() {\n    Fps f(96);\n    f[0] = 1;\n \
    \   for (int i = 1; i < int(f.size()); i++) f[i] = mint(i * i + 7);\n\n    Fps\
    \ inverse = f.inv();\n    Fps identity = (f * inverse).pre(int(f.size()));\n \
    \   assert(identity[0] == mint(1));\n    for (int i = 1; i < int(identity.size());\
    \ i++) assert(identity[i] == mint(0));\n\n    Fps logarithm = f.log();\n    assert_equal(logarithm.exp(),\
    \ f);\n    assert_equal(f.derivative().integral().pre(int(f.size())) + Fps(1,\
    \ f[0]), f);\n\n    Fps cube = f.pow(3);\n    assert_equal(cube, ((f * f) * f).pre(int(f.size())));\n\
    \n    Fps shifted(40);\n    shifted[4] = 9;\n    for (int i = 5; i < int(shifted.size());\
    \ i++) shifted[i] = mint(i + 11);\n    auto root = (shifted * shifted).pre(70).sqrt(70);\n\
    \    assert(root.has_value());\n    assert_equal(((*root) * (*root)).pre(70),\
    \ (shifted * shifted).pre(70));\n\n    Fps beyond_precision(8);\n    beyond_precision[5]\
    \ = 1;\n    auto zero_root = beyond_precision.sqrt(5);\n    assert(zero_root.has_value());\n\
    \    assert_equal(*zero_root, Fps(5));\n\n    Fps odd_leading(8);\n    odd_leading[3]\
    \ = 1;\n    assert(!odd_leading.sqrt(8).has_value());\n\n    Fps zero(20);\n \
    \   Fps one(20);\n    one[0] = 1;\n    assert_equal(zero.pow(0), one);\n    assert_equal(zero.pow(7),\
    \ zero);\n}\n\nvoid test_polynomial_operations() {\n    Fps dividend(80), divisor(35);\n\
    \    for (int i = 0; i < int(dividend.size()); i++) dividend[i] = mint(i * 17\
    \ + 3);\n    for (int i = 0; i < int(divisor.size()); i++) divisor[i] = mint(i\
    \ * 5 + 1);\n    auto division = dividend.divmod(divisor);\n    Fps restored =\
    \ division.first * divisor + division.second;\n    restored.resize(dividend.size());\n\
    \    assert_equal(restored, dividend);\n    assert(division.second.size() < divisor.size());\n\
    \n    mint shift = 12345;\n    Fps translated = dividend.taylor_shift(shift);\n\
    \    for (int x = 0; x < 10; x++) {\n        assert(translated.evaluate(mint(x))\
    \ == dividend.evaluate(mint(x) + shift));\n    }\n}\n\nvoid test_multipoint_and_recurrence()\
    \ {\n    Fps polynomial(70);\n    for (int i = 0; i < int(polynomial.size());\
    \ i++) polynomial[i] = mint(i * i * 13 + 5);\n    std::vector<mint> points(70);\n\
    \    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);\n\
    \n    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);\n\
    \    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));\n\
    \    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);\n\
    \    assert_equal(interpolated, polynomial);\n    std::vector<mint> one_point(1,\
    \ mint(42));\n    std::vector<mint> one_value(1, mint(314));\n    assert_equal(m1une::fps::polynomial_interpolate(one_point,\
    \ one_value), Fps(1, mint(314)));\n    assert(m1une::fps::multipoint_evaluate(Fps(),\
    \ std::vector<mint>()).empty());\n\n    std::vector<mint> initial(2);\n    std::vector<mint>\
    \ recurrence(2);\n    initial[0] = 0;\n    initial[1] = 1;\n    recurrence[0]\
    \ = 1;\n    recurrence[1] = 1;\n    mint previous = 0;\n    mint current = 1;\n\
    \    for (uint64_t index = 0; index < 200; index++) {\n        mint expected =\
    \ index == 0 ? previous : current;\n        assert(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index) == expected);\n        if (index > 0) {\n            mint\
    \ next = previous + current;\n            previous = current;\n            current\
    \ = next;\n        }\n    }\n}\n\nint main() {\n    test_convolution();\n    test_series_functions();\n\
    \    test_polynomial_operations();\n    test_multipoint_and_recurrence();\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <random>\n#include <vector>\n\
    \n#include \"../../../math/fps/all.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing mint1e9 = m1une::math::modint1000000007;\n\
    using Fps = m1une::fps::FormalPowerSeries<mint>;\n\ntemplate <class Mint>\nvoid\
    \ assert_equal(const std::vector<Mint>& lhs, const std::vector<Mint>& rhs) {\n\
    \    assert(lhs.size() == rhs.size());\n    for (int i = 0; i < int(lhs.size());\
    \ i++) assert(lhs[i] == rhs[i]);\n}\n\nvoid test_convolution() {\n    std::mt19937\
    \ rng(712367);\n    for (int iteration = 0; iteration < 30; iteration++) {\n \
    \       int n = 33 + int(rng() % 70);\n        int m = 33 + int(rng() % 70);\n\
    \        std::vector<mint> a(n), b(m);\n        for (mint& value : a) value =\
    \ mint(static_cast<uint32_t>(rng()));\n        for (mint& value : b) value = mint(static_cast<uint32_t>(rng()));\n\
    \        assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a,\
    \ b));\n    }\n\n    std::vector<mint1e9> a(70), b(65);\n    for (mint1e9& value\
    \ : a) value = mint1e9(static_cast<uint32_t>(rng()));\n    for (mint1e9& value\
    \ : b) value = mint1e9(static_cast<uint32_t>(rng()));\n    assert_equal(m1une::fps::convolution(a,\
    \ b), m1une::fps::convolution_naive(a, b));\n}\n\nvoid test_series_functions()\
    \ {\n    Fps f(96);\n    f[0] = 1;\n    for (int i = 1; i < int(f.size()); i++)\
    \ f[i] = mint(i * i + 7);\n\n    Fps inverse = f.inv();\n    Fps identity = (f\
    \ * inverse).pre(int(f.size()));\n    assert(identity[0] == mint(1));\n    for\
    \ (int i = 1; i < int(identity.size()); i++) assert(identity[i] == mint(0));\n\
    \n    Fps logarithm = f.log();\n    assert_equal(logarithm.exp(), f);\n    assert_equal(f.derivative().integral().pre(int(f.size()))\
    \ + Fps(1, f[0]), f);\n\n    Fps cube = f.pow(3);\n    assert_equal(cube, ((f\
    \ * f) * f).pre(int(f.size())));\n\n    Fps shifted(40);\n    shifted[4] = 9;\n\
    \    for (int i = 5; i < int(shifted.size()); i++) shifted[i] = mint(i + 11);\n\
    \    auto root = (shifted * shifted).pre(70).sqrt(70);\n    assert(root.has_value());\n\
    \    assert_equal(((*root) * (*root)).pre(70), (shifted * shifted).pre(70));\n\
    \n    Fps beyond_precision(8);\n    beyond_precision[5] = 1;\n    auto zero_root\
    \ = beyond_precision.sqrt(5);\n    assert(zero_root.has_value());\n    assert_equal(*zero_root,\
    \ Fps(5));\n\n    Fps odd_leading(8);\n    odd_leading[3] = 1;\n    assert(!odd_leading.sqrt(8).has_value());\n\
    \n    Fps zero(20);\n    Fps one(20);\n    one[0] = 1;\n    assert_equal(zero.pow(0),\
    \ one);\n    assert_equal(zero.pow(7), zero);\n}\n\nvoid test_polynomial_operations()\
    \ {\n    Fps dividend(80), divisor(35);\n    for (int i = 0; i < int(dividend.size());\
    \ i++) dividend[i] = mint(i * 17 + 3);\n    for (int i = 0; i < int(divisor.size());\
    \ i++) divisor[i] = mint(i * 5 + 1);\n    auto division = dividend.divmod(divisor);\n\
    \    Fps restored = division.first * divisor + division.second;\n    restored.resize(dividend.size());\n\
    \    assert_equal(restored, dividend);\n    assert(division.second.size() < divisor.size());\n\
    \n    mint shift = 12345;\n    Fps translated = dividend.taylor_shift(shift);\n\
    \    for (int x = 0; x < 10; x++) {\n        assert(translated.evaluate(mint(x))\
    \ == dividend.evaluate(mint(x) + shift));\n    }\n}\n\nvoid test_multipoint_and_recurrence()\
    \ {\n    Fps polynomial(70);\n    for (int i = 0; i < int(polynomial.size());\
    \ i++) polynomial[i] = mint(i * i * 13 + 5);\n    std::vector<mint> points(70);\n\
    \    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);\n\
    \n    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);\n\
    \    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));\n\
    \    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);\n\
    \    assert_equal(interpolated, polynomial);\n    std::vector<mint> one_point(1,\
    \ mint(42));\n    std::vector<mint> one_value(1, mint(314));\n    assert_equal(m1une::fps::polynomial_interpolate(one_point,\
    \ one_value), Fps(1, mint(314)));\n    assert(m1une::fps::multipoint_evaluate(Fps(),\
    \ std::vector<mint>()).empty());\n\n    std::vector<mint> initial(2);\n    std::vector<mint>\
    \ recurrence(2);\n    initial[0] = 0;\n    initial[1] = 1;\n    recurrence[0]\
    \ = 1;\n    recurrence[1] = 1;\n    mint previous = 0;\n    mint current = 1;\n\
    \    for (uint64_t index = 0; index < 200; index++) {\n        mint expected =\
    \ index == 0 ? previous : current;\n        assert(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index) == expected);\n        if (index > 0) {\n            mint\
    \ next = previous + current;\n            previous = current;\n            current\
    \ = next;\n        }\n    }\n}\n\nint main() {\n    test_convolution();\n    test_series_functions();\n\
    \    test_polynomial_operations();\n    test_multipoint_and_recurrence();\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - math/fps/all.hpp
  - math/fps/convolution.hpp
  - math/modint.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/fps_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:27:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/fps_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/fps_algorithms.test.cpp
- /verify/verify/math/fps/fps_algorithms.test.cpp.html
title: verify/math/fps/fps_algorithms.test.cpp
---
