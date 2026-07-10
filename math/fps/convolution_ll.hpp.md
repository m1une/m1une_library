---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
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
    path: verify/math/fps/convolution_ll.test.cpp
    title: verify/math/fps/convolution_ll.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fps/convolution_ll.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstdint>\n#include <limits>\n#include <vector>\n\n#line 1 \"math/fps/convolution.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#line 8 \"math/fps/convolution.hpp\"\
    \n#include <utility>\n#line 10 \"math/fps/convolution.hpp\"\n\n#if ((defined(__GNUC__)\
    \ && !defined(__clang__)) || defined(M1UNE_FPS_TEST_X86_SIMD)) && \\\n    (defined(__x86_64__)\
    \ || defined(__i386__))\n#include <immintrin.h>\n#define M1UNE_FPS_HAS_X86_SIMD\
    \ 1\n#endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n\
    #include <iostream>\n#include <type_traits>\n#line 8 \"math/modint.hpp\"\n\nnamespace\
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
    \ m1une\n\n\n#line 18 \"math/fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ r2;\n    __m256i modulus;\n    __m256i modulus2;\n    __m256i inverse;\n\n \
    \   Montgomery998Simd()\n        : negative_inverse(1),\n          r(uint32_t((uint64_t(1)\
    \ << 32) % mod)),\n          r2(uint32_t(uint64_t(r) * r % mod)) {\n        for\
    \ (int i = 0; i < 5; i++) negative_inverse *= 2 + negative_inverse * mod;\n  \
    \      modulus = _mm256_set1_epi32(int(mod));\n        modulus2 = _mm256_set1_epi32(int(mod2));\n\
    \        inverse = _mm256_set1_epi32(int(negative_inverse));\n    }\n\n    uint32_t\
    \ shrink(uint32_t value) const {\n        return std::min(value, value - mod);\n\
    \    }\n\n    uint32_t reduce(uint64_t value) const {\n        return uint32_t((value\
    \ + uint64_t(uint32_t(value) * negative_inverse) * mod) >> 32);\n    }\n\n   \
    \ uint32_t multiply(uint32_t lhs, uint32_t rhs) const {\n        return reduce(uint64_t(lhs)\
    \ * rhs);\n    }\n\n    uint32_t encode(uint32_t value) const {\n        return\
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
    \ odd_correction);\n        return _mm256_or_si256(_mm256_bsrli_epi128(even, 4),\
    \ odd);\n    }\n\n    __m256i add(__m256i lhs, __m256i rhs) const {\n        const\
    \ __m256i sum = _mm256_add_epi32(lhs, rhs);\n        return _mm256_min_epu32(sum,\
    \ _mm256_sub_epi32(sum, modulus2));\n    }\n\n    __m256i subtract(__m256i lhs,\
    \ __m256i rhs) const {\n        const __m256i difference = _mm256_sub_epi32(lhs,\
    \ rhs);\n        return _mm256_min_epu32(difference, _mm256_add_epi32(difference,\
    \ modulus2));\n    }\n};\n\ntemplate <class Mint>\nstruct Montgomery998NttRoots\
    \ {\n    std::array<uint32_t, 24> rate{};\n    std::array<uint32_t, 24> inverse_rate{};\n\
    \    std::array<uint32_t, 24> rate_radix4{};\n    std::array<uint32_t, 24> inverse_rate_radix4{};\n\
    \    uint32_t imaginary;\n    uint32_t inverse_imaginary;\n\n    Montgomery998NttRoots()\
    \ {\n        const Montgomery998Simd montgomery;\n        const auto& roots =\
    \ ntt_roots<Mint>();\n        for (int i = 0; i < NttRoots<Mint>::max_base; i++)\
    \ {\n            rate[i] = montgomery.encode(roots.rate[i].val());\n         \
    \   inverse_rate[i] = montgomery.encode(roots.inverse_rate[i].val());\n      \
    \      rate_radix4[i] = montgomery.encode(roots.rate_radix4[i].val());\n     \
    \       inverse_rate_radix4[i] =\n                montgomery.encode(roots.inverse_rate_radix4[i].val());\n\
    \        }\n        imaginary = montgomery.encode(roots.root[2].val());\n    \
    \    inverse_imaginary = montgomery.encode(roots.inverse_root[2].val());\n   \
    \ }\n};\n\ntemplate <class Mint>\n__attribute__((target(\"avx2,bmi\"), hot))\n\
    void ntt_998244353_simd(uint32_t* data, int n, bool inverse, bool normalize =\
    \ true) {\n    static const Montgomery998Simd montgomery;\n    static const Montgomery998NttRoots<Mint>\
    \ roots;\n    const int height = two_adic_order(uint32_t(n));\n\n    if (!inverse)\
    \ {\n        for (int phase = 1; phase <= height; phase++) {\n            const\
    \ int blocks = 1 << (phase - 1);\n            const int width = 1 << (height -\
    \ phase);\n            uint32_t twiddle = montgomery.r;\n            if (width\
    \ >= 16 && phase < height) {\n                const int radix_width = width >>\
    \ 1;\n                const uint32_t imaginary = roots.imaginary;\n          \
    \      const __m256i vector_imaginary = _mm256_set1_epi32(int(imaginary));\n \
    \               for (int block = 0; block < blocks; block++) {\n             \
    \       const uint32_t twiddle2 = montgomery.multiply(twiddle, twiddle);\n   \
    \                 const uint32_t twiddle3 = montgomery.multiply(twiddle2, twiddle);\n\
    \                    const __m256i vector_twiddle = _mm256_set1_epi32(int(twiddle));\n\
    \                    const __m256i vector_twiddle2 = _mm256_set1_epi32(int(twiddle2));\n\
    \                    const __m256i vector_twiddle3 = _mm256_set1_epi32(int(twiddle3));\n\
    \                    const int offset = block << (height - phase + 1);\n     \
    \               for (int i = 0; i < radix_width; i += 8) {\n                 \
    \       const __m256i a0 = _mm256_loadu_si256(\n                            reinterpret_cast<const\
    \ __m256i*>(data + offset + i));\n                        const __m256i loaded_a1\
    \ = _mm256_loadu_si256(\n                            reinterpret_cast<const __m256i*>(\n\
    \                                data + offset + radix_width + i));\n        \
    \                const __m256i loaded_a2 = _mm256_loadu_si256(\n             \
    \               reinterpret_cast<const __m256i*>(\n                          \
    \      data + offset + 2 * radix_width + i));\n                        const __m256i\
    \ loaded_a3 = _mm256_loadu_si256(\n                            reinterpret_cast<const\
    \ __m256i*>(\n                                data + offset + 3 * radix_width\
    \ + i));\n                        const __m256i a1 = block == 0\n            \
    \                                   ? loaded_a1\n                            \
    \                   : montgomery.multiply(loaded_a1, vector_twiddle);\n      \
    \                  const __m256i a2 = block == 0\n                           \
    \                    ? loaded_a2\n                                           \
    \    : montgomery.multiply(loaded_a2, vector_twiddle2);\n                    \
    \    const __m256i a3 = block == 0\n                                         \
    \      ? loaded_a3\n                                               : montgomery.multiply(loaded_a3,\
    \ vector_twiddle3);\n                        const __m256i a0a2 = montgomery.add(a0,\
    \ a2);\n                        const __m256i a0na2 = montgomery.subtract(a0,\
    \ a2);\n                        const __m256i a1a3 = montgomery.add(a1, a3);\n\
    \                        const __m256i a1na3i = montgomery.multiply(\n       \
    \                     montgomery.subtract(a1, a3), vector_imaginary);\n      \
    \                  _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset\
    \ + i),\n                                           montgomery.add(a0a2, a1a3));\n\
    \                        _mm256_storeu_si256(reinterpret_cast<__m256i*>(\n   \
    \                                            data + offset + radix_width + i),\n\
    \                                           montgomery.subtract(a0a2, a1a3));\n\
    \                        _mm256_storeu_si256(reinterpret_cast<__m256i*>(\n   \
    \                                            data + offset + 2 * radix_width +\
    \ i),\n                                           montgomery.add(a0na2, a1na3i));\n\
    \                        _mm256_storeu_si256(reinterpret_cast<__m256i*>(\n   \
    \                                            data + offset + 3 * radix_width +\
    \ i),\n                                           montgomery.subtract(a0na2, a1na3i));\n\
    \                    }\n                    if (block + 1 != blocks) {\n     \
    \                   twiddle = montgomery.multiply(\n                         \
    \   twiddle, roots.rate_radix4[__builtin_ctz(~uint32_t(block))]);\n          \
    \          }\n                }\n                phase++;\n                continue;\n\
    \            }\n            if (width < 8) {\n                const int blocks_per_vector\
    \ = 8 / (width << 1);\n                for (int block = 0; block < blocks; block\
    \ += blocks_per_vector) {\n                    alignas(32) uint32_t twiddles[8];\n\
    \                    for (int local = 0; local < blocks_per_vector; local++) {\n\
    \                        const int begin = local * (width << 1);\n           \
    \             for (int lane = 0; lane < (width << 1); lane++)\n              \
    \              twiddles[begin + lane] = twiddle;\n                        const\
    \ int current = block + local;\n                        if (current + 1 != blocks)\
    \ {\n                            twiddle = montgomery.multiply(\n            \
    \                    twiddle, roots.rate[__builtin_ctz(~uint32_t(current))]);\n\
    \                        }\n                    }\n                    const int\
    \ offset = block * (width << 1);\n                    const __m256i values = _mm256_loadu_si256(\n\
    \                        reinterpret_cast<const __m256i*>(data + offset));\n \
    \                   __m256i lhs;\n                    __m256i rhs;\n         \
    \           if (width == 4) {\n                        lhs = _mm256_permute2x128_si256(values,\
    \ values, 0x00);\n                        rhs = _mm256_permute2x128_si256(values,\
    \ values, 0x11);\n                    } else if (width == 2) {\n             \
    \           lhs = _mm256_shuffle_epi32(values, 0x44);\n                      \
    \  rhs = _mm256_shuffle_epi32(values, 0xee);\n                    } else {\n \
    \                       lhs = _mm256_shuffle_epi32(values, 0xa0);\n          \
    \              rhs = _mm256_shuffle_epi32(values, 0xf5);\n                   \
    \ }\n                    const __m256i vector_twiddle = _mm256_load_si256(\n \
    \                       reinterpret_cast<const __m256i*>(twiddles));\n       \
    \             rhs = montgomery.multiply(rhs, vector_twiddle);\n              \
    \      const __m256i sums = montgomery.add(lhs, rhs);\n                    const\
    \ __m256i differences = montgomery.subtract(lhs, rhs);\n                    const\
    \ __m256i result = width == 4\n                                              \
    \ ? _mm256_blend_epi32(sums, differences, 0xf0)\n                            \
    \               : width == 2\n                                               ?\
    \ _mm256_blend_epi32(sums, differences, 0xcc)\n                              \
    \                 : _mm256_blend_epi32(sums, differences, 0xaa);\n           \
    \         _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset), result);\n\
    \                }\n                continue;\n            }\n            for\
    \ (int block = 0; block < blocks; block++) {\n                const int offset\
    \ = block << (height - phase + 1);\n                const __m256i vector_twiddle\
    \ = _mm256_set1_epi32(int(twiddle));\n                int i = 0;\n           \
    \     for (; i + 8 <= width; i += 8) {\n                    const __m256i lhs\
    \ = _mm256_loadu_si256(\n                        reinterpret_cast<const __m256i*>(data\
    \ + offset + i));\n                    const __m256i rhs = _mm256_loadu_si256(\n\
    \                        reinterpret_cast<const __m256i*>(data + offset + width\
    \ + i));\n                    const __m256i weighted_rhs =\n                 \
    \       block == 0 ? rhs : montgomery.multiply(rhs, vector_twiddle);\n       \
    \             _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + i),\n\
    \                                       montgomery.add(lhs, weighted_rhs));\n\
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
    \      if (block + 1 != blocks) {\n                    twiddle = montgomery.multiply(\n\
    \                        twiddle, roots.rate[__builtin_ctz(~uint32_t(block))]);\n\
    \                }\n            }\n        }\n    } else {\n        for (int phase\
    \ = height; phase >= 1; phase--) {\n            const int blocks = 1 << (phase\
    \ - 1);\n            const int width = 1 << (height - phase);\n            uint32_t\
    \ twiddle = montgomery.r;\n            if (width >= 8 && phase >= 2) {\n     \
    \           const int radix_blocks = blocks >> 1;\n                const uint32_t\
    \ inverse_imaginary = roots.inverse_imaginary;\n                const __m256i\
    \ vector_inverse_imaginary =\n                    _mm256_set1_epi32(int(inverse_imaginary));\n\
    \                for (int block = 0; block < radix_blocks; block++) {\n      \
    \              const uint32_t twiddle2 = montgomery.multiply(twiddle, twiddle);\n\
    \                    const uint32_t twiddle3 = montgomery.multiply(twiddle2, twiddle);\n\
    \                    const __m256i vector_twiddle = _mm256_set1_epi32(int(twiddle));\n\
    \                    const __m256i vector_twiddle2 = _mm256_set1_epi32(int(twiddle2));\n\
    \                    const __m256i vector_twiddle3 = _mm256_set1_epi32(int(twiddle3));\n\
    \                    const int offset = block << (height - phase + 2);\n     \
    \               for (int i = 0; i < width; i += 8) {\n                       \
    \ const __m256i a0 = _mm256_loadu_si256(\n                            reinterpret_cast<const\
    \ __m256i*>(data + offset + i));\n                        const __m256i a1 = _mm256_loadu_si256(\n\
    \                            reinterpret_cast<const __m256i*>(data + offset +\
    \ width + i));\n                        const __m256i a2 = _mm256_loadu_si256(reinterpret_cast<const\
    \ __m256i*>(\n                            data + offset + 2 * width + i));\n \
    \                       const __m256i a3 = _mm256_loadu_si256(reinterpret_cast<const\
    \ __m256i*>(\n                            data + offset + 3 * width + i));\n \
    \                       const __m256i a0a1 = montgomery.add(a0, a1);\n       \
    \                 const __m256i a0na1 = montgomery.subtract(a0, a1);\n       \
    \                 const __m256i a2a3 = montgomery.add(a2, a3);\n             \
    \           const __m256i a2na3i = montgomery.multiply(\n                    \
    \        montgomery.subtract(a2, a3), vector_inverse_imaginary);\n           \
    \             _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + i),\n\
    \                                           montgomery.add(a0a1, a2a3));\n   \
    \                     const __m256i output1 = montgomery.add(a0na1, a2na3i);\n\
    \                        const __m256i output2 = montgomery.subtract(a0a1, a2a3);\n\
    \                        const __m256i output3 = montgomery.subtract(a0na1, a2na3i);\n\
    \                        _mm256_storeu_si256(\n                            reinterpret_cast<__m256i*>(data\
    \ + offset + width + i),\n                            block == 0 ? output1\n \
    \                                      : montgomery.multiply(output1, vector_twiddle));\n\
    \                        _mm256_storeu_si256(\n                            reinterpret_cast<__m256i*>(data\
    \ + offset + 2 * width + i),\n                            block == 0 ? output2\n\
    \                                       : montgomery.multiply(output2, vector_twiddle2));\n\
    \                        _mm256_storeu_si256(\n                            reinterpret_cast<__m256i*>(data\
    \ + offset + 3 * width + i),\n                            block == 0 ? output3\n\
    \                                       : montgomery.multiply(output3, vector_twiddle3));\n\
    \                    }\n                    if (block + 1 != radix_blocks) {\n\
    \                        twiddle = montgomery.multiply(\n                    \
    \        twiddle, roots.inverse_rate_radix4[\n                               \
    \           __builtin_ctz(~uint32_t(block))]);\n                    }\n      \
    \          }\n                phase--;\n                continue;\n          \
    \  }\n            if (width < 8) {\n                const int blocks_per_vector\
    \ = 8 / (width << 1);\n                for (int block = 0; block < blocks; block\
    \ += blocks_per_vector) {\n                    alignas(32) uint32_t twiddles[8];\n\
    \                    for (int local = 0; local < blocks_per_vector; local++) {\n\
    \                        const int begin = local * (width << 1);\n           \
    \             for (int lane = 0; lane < (width << 1); lane++)\n              \
    \              twiddles[begin + lane] = twiddle;\n                        const\
    \ int current = block + local;\n                        if (current + 1 != blocks)\
    \ {\n                            twiddle = montgomery.multiply(\n            \
    \                    twiddle,\n                                roots.inverse_rate[__builtin_ctz(~uint32_t(current))]);\n\
    \                        }\n                    }\n                    const int\
    \ offset = block * (width << 1);\n                    const __m256i values = _mm256_loadu_si256(\n\
    \                        reinterpret_cast<const __m256i*>(data + offset));\n \
    \                   __m256i lhs;\n                    __m256i rhs;\n         \
    \           if (width == 4) {\n                        lhs = _mm256_permute2x128_si256(values,\
    \ values, 0x00);\n                        rhs = _mm256_permute2x128_si256(values,\
    \ values, 0x11);\n                    } else if (width == 2) {\n             \
    \           lhs = _mm256_shuffle_epi32(values, 0x44);\n                      \
    \  rhs = _mm256_shuffle_epi32(values, 0xee);\n                    } else {\n \
    \                       lhs = _mm256_shuffle_epi32(values, 0xa0);\n          \
    \              rhs = _mm256_shuffle_epi32(values, 0xf5);\n                   \
    \ }\n                    const __m256i sums = montgomery.add(lhs, rhs);\n    \
    \                const __m256i vector_twiddle = _mm256_load_si256(\n         \
    \               reinterpret_cast<const __m256i*>(twiddles));\n               \
    \     const __m256i differences = montgomery.multiply(\n                     \
    \   montgomery.subtract(lhs, rhs), vector_twiddle);\n                    const\
    \ __m256i result = width == 4\n                                              \
    \ ? _mm256_blend_epi32(sums, differences, 0xf0)\n                            \
    \               : width == 2\n                                               ?\
    \ _mm256_blend_epi32(sums, differences, 0xcc)\n                              \
    \                 : _mm256_blend_epi32(sums, differences, 0xaa);\n           \
    \         _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset), result);\n\
    \                }\n                continue;\n            }\n            for\
    \ (int block = 0; block < blocks; block++) {\n                const int offset\
    \ = block << (height - phase + 1);\n                const __m256i vector_twiddle\
    \ = _mm256_set1_epi32(int(twiddle));\n                int i = 0;\n           \
    \     for (; i + 8 <= width; i += 8) {\n                    const __m256i lhs\
    \ = _mm256_loadu_si256(\n                        reinterpret_cast<const __m256i*>(data\
    \ + offset + i));\n                    const __m256i rhs = _mm256_loadu_si256(\n\
    \                        reinterpret_cast<const __m256i*>(data + offset + width\
    \ + i));\n                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data\
    \ + offset + i),\n                                       montgomery.add(lhs, rhs));\n\
    \                    const __m256i difference = montgomery.subtract(lhs, rhs);\n\
    \                    _mm256_storeu_si256(\n                        reinterpret_cast<__m256i*>(data\
    \ + offset + width + i),\n                        block == 0 ? difference\n  \
    \                                 : montgomery.multiply(difference, vector_twiddle));\n\
    \                }\n                for (; i < width; i++) {\n               \
    \     const uint32_t lhs = data[offset + i];\n                    const uint32_t\
    \ rhs = data[offset + width + i];\n                    uint32_t sum = lhs + rhs;\n\
    \                    if (sum >= Montgomery998Simd::mod) sum -= Montgomery998Simd::mod;\n\
    \                    uint32_t difference = lhs >= rhs ? lhs - rhs : lhs + Montgomery998Simd::mod\
    \ - rhs;\n                    data[offset + i] = sum;\n                    data[offset\
    \ + width + i] = montgomery.multiply(difference, twiddle);\n                }\n\
    \                if (block + 1 != blocks) {\n                    twiddle = montgomery.multiply(\n\
    \                        twiddle, roots.inverse_rate[__builtin_ctz(~uint32_t(block))]);\n\
    \                }\n            }\n        }\n        if (normalize) {\n     \
    \       const uint32_t scale = montgomery.encode(Mint(n).inv().val());\n     \
    \       const __m256i vector_scale = _mm256_set1_epi32(int(scale));\n        \
    \    int i = 0;\n            for (; i + 8 <= n; i += 8) {\n                __m256i\
    \ values =\n                    _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data\
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
    \ = 0; j < result_size; j++)\n        result[j] = Mint::raw(montgomery.shrink(transformed_a[j]));\n\
    \    return result;\n}\n\n#pragma GCC pop_options\n\n#endif\n\n}  // namespace\
    \ internal\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_naive(const\
    \ std::vector<Mint>& a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty())\
    \ return {};\n    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size()\
    \ < b.size()) {\n        for (int i = 0; i < int(a.size()); i++) {\n         \
    \   for (int j = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n  \
    \      }\n    } else {\n        for (int j = 0; j < int(b.size()); j++) {\n  \
    \          for (int i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>& b) {\n\
    \    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n \
    \   while (n < result_size) n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n)\
    \ == 0);\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if constexpr (Mint::mod() == 998244353)\
    \ {\n        if (n >= 64 && __builtin_cpu_supports(\"avx2\"))\n            return\
    \ internal::convolution_998244353_simd(a, b);\n    }\n#endif\n\n    // Allocate\
    \ the padded buffers directly.  Constructing from the inputs and\n    // then\
    \ resizing used to allocate and copy both large operands twice.\n    std::vector<Mint>\
    \ fa(n);\n    std::vector<Mint> fb(n);\n    std::copy(a.begin(), a.end(), fa.begin());\n\
    \    std::copy(b.begin(), b.end(), fb.begin());\n    internal::ntt(fa, false);\n\
    \    internal::ntt(fb, false);\n    const Mint inverse_n = Mint(n).inv();\n  \
    \  for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;\n    internal::ntt(fa,\
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
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 11 \"math/fps/convolution_ll.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\n// Exact convolution of signed 64-bit\
    \ coefficients.\n// Every result coefficient must fit in long long.\ninline std::vector<long\
    \ long> convolution_ll(\n    const std::vector<long long>& first,\n    const std::vector<long\
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
    \ namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FPS_CONVOLUTION_LL_HPP\n#define M1UNE_FPS_CONVOLUTION_LL_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <limits>\n#include <vector>\n\
    \n#include \"convolution.hpp\"\n#include \"../modint.hpp\"\n\nnamespace m1une\
    \ {\nnamespace fps {\n\n// Exact convolution of signed 64-bit coefficients.\n\
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
    \ namespace m1une\n\n#endif  // M1UNE_FPS_CONVOLUTION_LL_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/convolution_ll.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-11 02:39:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/convolution_ll.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/convolution_ll.hpp
layout: document
title: Long Long Convolution
---

## Overview

`convolution_ll` computes an exact polynomial convolution whose inputs and
outputs use signed `long long` coefficients.

It performs convolution modulo three NTT-friendly primes and reconstructs each
signed coefficient with the Chinese remainder theorem. Unlike FFT followed by
rounding, the result has no floating-point error.

## Function

```cpp
std::vector<long long> convolution_ll(
    const std::vector<long long>& first,
    const std::vector<long long>& second);
```

The coefficient at index `k` is

$$
\sum_{i+j=k} \text{first}[i]\,\text{second}[j].
$$

If either input is empty, the result is empty. Otherwise, the result has
`first.size() + second.size() - 1` coefficients.

Every exact result coefficient must fit in signed `long long`. Individual
products and intermediate mathematical sums may exceed 64 bits. The required
NTT length must not exceed $2^{24}$.

| Function | Complexity |
| --- | --- |
| `convolution_ll(first, second)` | $O(L\log L)$ time and $O(L)$ memory. |

Here $L$ is the output length rounded up to a power of two. Small inputs use
the modular convolution implementation's quadratic cutoff.

## Example

```cpp
#include "math/fps/convolution_ll.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<long long> first = {1, -2, 3};
    std::vector<long long> second = {4, 5};
    auto result = m1une::fps::convolution_ll(first, second);

    for (long long value : result) std::cout << value << " ";
    std::cout << "\n"; // 4 -3 2 15
}
```
