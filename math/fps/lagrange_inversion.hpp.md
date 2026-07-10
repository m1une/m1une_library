---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/lagrange_inversion.test.cpp
    title: verify/math/fps/lagrange_inversion.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fps/lagrange_inversion.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n\n#line 1 \"math/fps/formal_power_series.hpp\"\
    \n\n\n\n#line 7 \"math/fps/formal_power_series.hpp\"\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"math/fps/convolution.hpp\"\n\n\n\n\
    #line 5 \"math/fps/convolution.hpp\"\n#include <array>\n#line 10 \"math/fps/convolution.hpp\"\
    \n\n#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))\n\
    #include <immintrin.h>\n#define M1UNE_FPS_HAS_X86_SIMD 1\n#endif\n\n#line 1 \"\
    math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n#include\
    \ <type_traits>\n#line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
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
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 12 \"math/fps/formal_power_series.hpp\"\
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
    \ namespace fps\n}  // namespace m1une\n\n\n#line 9 \"math/fps/lagrange_inversion.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nMint lagrange_inversion_coefficient(const\
    \ FormalPowerSeries<Mint>& phi, int degree) {\n    assert(1 <= degree && uint32_t(degree)\
    \ < Mint::mod());\n    assert(!phi.empty() && phi[0] != Mint(0));\n\n    FormalPowerSeries<Mint>\
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
    \ degree);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FPS_LAGRANGE_INVERSION_HPP\n#define M1UNE_FPS_LAGRANGE_INVERSION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n\n#include\
    \ \"formal_power_series.hpp\"\n\nnamespace m1une {\nnamespace fps {\n\ntemplate\
    \ <class Mint>\nMint lagrange_inversion_coefficient(const FormalPowerSeries<Mint>&\
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
    \ degree);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_LAGRANGE_INVERSION_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/lagrange_inversion.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-11 02:27:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/lagrange_inversion.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/lagrange_inversion.hpp
layout: document
title: Lagrange Inversion Formula
---

## Overview

This header finds one coefficient of a formal power series that is defined
implicitly. You provide a series $\phi(t)$ and consider the unique series
$w(x)$ satisfying

$$w(x)=x\phi(w(x)).$$

The important point is that **`w` is defined by `phi`**. It is not another
function argument, and the library does not construct all of `w`. The Lagrange
inversion formula obtains the requested coefficient directly from $\phi$:

$$[x^n]w(x)=\frac{1}{n}[t^{n-1}]\phi(t)^n.$$

For example, if

$$\phi(t)=(1+t)^2,$$

then `w` means the solution of

$$w=x(1+w)^2=x+2x^2+5x^3+14x^4+\cdots.$$

The coefficient of $x^4$ is therefore `14`.

## Which Function Should I Use?

### Coefficient of `w`

```cpp
Mint lagrange_inversion_coefficient(const Fps& phi, int n);
```

Use this when `w` is defined by $w=x\phi(w)$ and you want $[x^n]w$.

```cpp
Fps phi = {1, 2, 1}; // phi(t) = (1+t)^2
mint answer = m1une::fps::lagrange_inversion_coefficient(phi, 4);
// answer = [x^4]w(x) = 14
```

### Coefficient after applying another series

```cpp
Mint lagrange_burmann_coefficient(
    const Fps& phi, const Fps& outer, int n);
```

This is the generalized form. As before, `phi` implicitly defines
$w=x\phi(w)$. The `outer` argument stores a second series $H(t)$. The function
returns

$$[x^n]H(w(x)).$$

It uses the Lagrange-Bürmann formula

$$[x^n]H(w(x))
=\frac{1}{n}[t^{n-1}]H'(t)\phi(t)^n.$$

For example:

```cpp
Fps phi = {1, 2, 1};  // w = x(1+w)^2
Fps outer = {0, 0, 1}; // H(t) = t^2

mint answer = m1une::fps::lagrange_burmann_coefficient(phi, outer, 5);
// answer = [x^5]H(w(x)) = [x^5]w(x)^2 = 48
```

The parameter correspondence is:

| C++ argument | Mathematical meaning |
| --- | --- |
| `phi` | Defines the otherwise-unwritten series `w` through $w=x\phi(w)$. |
| `outer` | Coefficients of $H(t)$. |
| `n` | The requested degree of $x$. |
| return value | $[x^n]H(w(x))$. |

### Coefficient of a compositional inverse

```cpp
Mint compositional_inverse_coefficient(const Fps& f, int n);
```

Use this when a series $f(t)$ is given directly and you want one coefficient
of its compositional inverse $g(x)$:

$$f(g(x))=x.$$

Internally, the function sets

$$\phi(t)=\frac{t}{f(t)},$$

so that $g=x\phi(g)$, and then applies the basic formula.

```cpp
Fps f = {0, 1, 1}; // f(t) = t+t^2
mint answer = m1une::fps::compositional_inverse_coefficient(f, 4);
// g(x) = x-x^2+2x^3-5x^4+...
// answer = -5 modulo mint::mod()
```

## Interface and Complexity

Let `Fps` denote `FormalPowerSeries<Mint>`.

| Function | Requirement | Result | Complexity |
| --- | --- | --- | --- |
| `Mint lagrange_inversion_coefficient(const Fps& phi, int n)` | `n > 0`, `phi[0] != 0` | $[x^n]w$, where $w=x\phi(w)$ | $O(n\log n)$ time, $O(n)$ memory |
| `Mint lagrange_burmann_coefficient(const Fps& phi, const Fps& outer, int n)` | `phi[0] != 0` when `n > 0` | $[x^n]H(w)$, where `outer` stores $H$ | $O(n\log n)$ time, $O(n)$ memory |
| `Mint compositional_inverse_coefficient(const Fps& f, int n)` | `f[0] == 0`, `f[1] != 0` | $[x^n]g$, where $f(g)=x$ | $O(n\log n)$ time, $O(n)$ memory |

Each call returns only one coefficient. Calling it separately for every degree
is not intended as a fast way to construct an entire compositional inverse.

For `n == 0`, `lagrange_burmann_coefficient` returns $H(0)$ and
`compositional_inverse_coefficient` returns zero.

## Requirements

`Mint` must satisfy the requirements of `FormalPowerSeries<Mint>`. The supplied
static modular integers are supported. The modulus is assumed to be prime, and
`n` must be smaller than the modulus so division by `n` is valid.

Missing coefficients above a series' stored size are treated as zero. None of
the input series are modified.

## Complete Example

```cpp
#include "math/fps/lagrange_inversion.hpp"
#include "math/modint.hpp"
#include <iostream>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps phi = {1, 2, 1}; // phi(t) = (1+t)^2

    // Here w is implicitly defined as w = x(1+w)^2.
    mint coefficient_of_w =
        m1une::fps::lagrange_inversion_coefficient(phi, 4);

    Fps outer = {0, 0, 1}; // H(t) = t^2
    mint coefficient_of_w_squared =
        m1une::fps::lagrange_burmann_coefficient(phi, outer, 5);

    std::cout << coefficient_of_w << "\n";         // 14
    std::cout << coefficient_of_w_squared << "\n"; // 48
}
```
