---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
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
    \n#include <utility>\n#line 10 \"math/fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 5 \"math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n\
    #line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
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
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 11 \"math/fps/convolution_ll.hpp\"\
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
  timestamp: '2026-07-10 21:34:58+09:00'
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
