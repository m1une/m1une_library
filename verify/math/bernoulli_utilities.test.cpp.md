---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
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
  bundledCode: "#line 1 \"verify/math/bernoulli_utilities.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/bernoulli.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#line 1 \"\
    math/fps/formal_power_series.hpp\"\n\n\n\n#include <algorithm>\n#line 7 \"math/fps/formal_power_series.hpp\"\
    \n#include <optional>\n#include <utility>\n#line 10 \"math/fps/formal_power_series.hpp\"\
    \n\n#line 1 \"math/fps/convolution.hpp\"\n\n\n\n#line 5 \"math/fps/convolution.hpp\"\
    \n#include <array>\n#line 10 \"math/fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\
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
    \ max_base> inverse_rate;\n\n    NttRoots() {\n        constexpr uint32_t primitive_root\
    \ = primitive_root_constexpr(Mint::mod());\n        for (int level = 1; level\
    \ <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n        Mint product = 1;\n        Mint inverse_product = 1;\n       \
    \ for (int i = 0; i + 1 < max_base; i++) {\n            rate[i] = root[i + 2]\
    \ * product;\n            inverse_rate[i] = inverse_root[i + 2] * inverse_product;\n\
    \            product *= inverse_root[i + 2];\n            inverse_product *= root[i\
    \ + 2];\n        }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>&\
    \ ntt_roots() {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\
    \ntemplate <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse) {\n    const\
    \ int n = int(a.size());\n    assert(n > 0 && (n & (n - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(n) == 0);\n\n    const auto& roots = ntt_roots<Mint>();\n  \
    \  const int height = two_adic_order(uint32_t(n));\n    if (!inverse) {\n    \
    \    // The transposed access order avoids bit reversal and changes the\n    \
    \    // twiddle only once per block instead of once per butterfly.\n        for\
    \ (int phase = 1; phase <= height; phase++) {\n            const int blocks =\
    \ 1 << (phase - 1);\n            const int width = 1 << (height - phase);\n  \
    \          Mint twiddle = 1;\n            for (int block = 0; block < blocks;\
    \ block++) {\n                const int offset = block << (height - phase + 1);\n\
    \                for (int i = 0; i < width; i++) {\n                    const\
    \ Mint left = a[offset + i];\n                    const Mint right = a[offset\
    \ + i + width] * twiddle;\n                    a[offset + i] = left + right;\n\
    \                    a[offset + i + width] = left - right;\n                }\n\
    \                if (block + 1 != blocks)\n                    twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n        }\n    } else {\n        for (int phase = height; phase\
    \ >= 1; phase--) {\n            const int blocks = 1 << (phase - 1);\n       \
    \     const int width = 1 << (height - phase);\n            Mint twiddle = 1;\n\
    \            for (int block = 0; block < blocks; block++) {\n                const\
    \ int offset = block << (height - phase + 1);\n                for (int i = 0;\
    \ i < width; i++) {\n                    const Mint left = a[offset + i];\n  \
    \                  const Mint right = a[offset + i + width];\n               \
    \     a[offset + i] = left + right;\n                    a[offset + i + width]\
    \ = (left - right) * twiddle;\n                }\n                if (block +\
    \ 1 != blocks)\n                    twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n        }\n        const Mint inverse_n = Mint(n).inv();\n   \
    \     for (Mint& value : a) value *= inverse_n;\n    }\n}\n\n}  // namespace internal\n\
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
    \ n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n    std::vector<Mint>\
    \ fa(a.begin(), a.end());\n    std::vector<Mint> fb(b.begin(), b.end());\n   \
    \ fa.resize(n);\n    fb.resize(n);\n    internal::ntt(fa, false);\n    internal::ntt(fb,\
    \ false);\n    for (int i = 0; i < n; i++) fa[i] *= fb[i];\n    internal::ntt(fa,\
    \ true);\n    fa.resize(result_size);\n    return fa;\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>&\
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
    }  // namespace m1une\n\n\n#line 5 \"verify/math/bernoulli_utilities.test.cpp\"\
    \n\n#line 10 \"verify/math/bernoulli_utilities.test.cpp\"\n\nusing Mint = m1une::math::modint998244353;\n\
    \nMint evaluate(const std::vector<Mint>& coefficients, Mint x) {\n    Mint result\
    \ = 0;\n    for (int index = int(coefficients.size()) - 1; index >= 0; --index)\
    \ {\n        result = result * x + coefficients[index];\n    }\n    return result;\n\
    }\n\nMint power(Mint base, int exponent) {\n    Mint result = 1;\n    while (exponent--)\
    \ result *= base;\n    return result;\n}\n\nvoid test_numbers_and_polynomials()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(30);\n    assert(bernoulli.number(0)\
    \ == Mint(1));\n    assert(bernoulli.number(1) * Mint(2) == Mint(-1));\n    assert(bernoulli.number(2)\
    \ * Mint(6) == Mint(1));\n    assert(bernoulli.number(4) * Mint(30) == Mint(-1));\n\
    \    for (int degree = 3; degree <= 29; degree += 2) {\n        assert(bernoulli.number(degree)\
    \ == Mint(0));\n    }\n\n    for (int degree = 0; degree <= 20; ++degree) {\n\
    \        auto coefficients = bernoulli.polynomial_coefficients(degree);\n    \
    \    for (int value = -5; value <= 5; ++value) {\n            Mint x = value;\n\
    \            assert(evaluate(coefficients, x) == bernoulli.polynomial(degree,\
    \ x));\n            if (degree > 0) {\n                assert(\n             \
    \       bernoulli.polynomial(degree, x + Mint(1)) -\n                        bernoulli.polynomial(degree,\
    \ x) ==\n                    Mint(degree) * power(x, degree - 1)\n           \
    \     );\n            }\n        }\n    }\n}\n\nvoid test_power_sums() {\n   \
    \ m1une::math::Bernoulli<Mint> bernoulli(20);\n    for (int degree = 0; degree\
    \ <= 20; ++degree) {\n        auto coefficients = bernoulli.power_sum_polynomial(degree);\n\
    \        Mint expected = 0;\n        for (int n = 0; n <= 40; ++n) {\n       \
    \     assert(bernoulli.power_sum(Mint(n), degree) == expected);\n            assert(evaluate(coefficients,\
    \ Mint(n)) == expected);\n            expected += power(Mint(n), degree);\n  \
    \      }\n    }\n\n    for (int degree = 0; degree <= 12; ++degree) {\n      \
    \  for (int left = -10; left <= 10; ++left) {\n            Mint expected = 0;\n\
    \            for (int right = left; right <= 12; ++right) {\n                assert(\n\
    \                    bernoulli.power_sum(Mint(left), Mint(right), degree) ==\n\
    \                    expected\n                );\n                expected +=\
    \ power(Mint(right), degree);\n            }\n        }\n    }\n}\n\nvoid test_polynomial_sums_randomized()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    std::uint64_t state\
    \ = 0xbb67ae8584caa73bULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int test = 0; test < 2000; ++test) {\n        int degree = static_cast<int>(random()\
    \ % 13);\n        std::vector<Mint> coefficients(degree + 1);\n        for (Mint&\
    \ coefficient : coefficients) {\n            coefficient = static_cast<long long>(random()\
    \ % 101) - 50;\n        }\n\n        auto prefix = bernoulli.polynomial_prefix_sum(coefficients);\n\
    \        for (int x = -10; x <= 10; ++x) {\n            assert(\n            \
    \    evaluate(prefix, Mint(x + 1)) - evaluate(prefix, Mint(x)) ==\n          \
    \      evaluate(coefficients, Mint(x))\n            );\n        }\n\n        int\
    \ left = static_cast<int>(random() % 21) - 10;\n        int length = static_cast<int>(random()\
    \ % 21);\n        int right = left + length;\n        Mint expected = 0;\n   \
    \     for (int x = left; x < right; ++x) {\n            expected += evaluate(coefficients,\
    \ Mint(x));\n        }\n        assert(\n            bernoulli.polynomial_sum(\n\
    \                coefficients,\n                Mint(left),\n                Mint(right)\n\
    \            ) == expected\n        );\n    }\n}\n\nvoid test_arithmetic_progressions()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    for (int degree = 0;\
    \ degree <= 12; ++degree) {\n        for (int start = -3; start <= 3; ++start)\
    \ {\n            for (int step = -2; step <= 2; ++step) {\n                Mint\
    \ expected = 0;\n                for (int count = 0; count <= 15; ++count) {\n\
    \                    assert(\n                        bernoulli.arithmetic_progression_power_sum(\n\
    \                            Mint(start),\n                            Mint(step),\n\
    \                            Mint(count),\n                            degree\n\
    \                        ) == expected\n                    );\n             \
    \       expected += power(Mint(start + step * count), degree);\n             \
    \   }\n            }\n        }\n    }\n}\n\nint main() {\n    test_numbers_and_polynomials();\n\
    \    test_power_sums();\n    test_polynomial_sums_randomized();\n    test_arithmetic_progressions();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/bernoulli.hpp\"\n#include \"../../math/modint.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nusing Mint = m1une::math::modint998244353;\n\
    \nMint evaluate(const std::vector<Mint>& coefficients, Mint x) {\n    Mint result\
    \ = 0;\n    for (int index = int(coefficients.size()) - 1; index >= 0; --index)\
    \ {\n        result = result * x + coefficients[index];\n    }\n    return result;\n\
    }\n\nMint power(Mint base, int exponent) {\n    Mint result = 1;\n    while (exponent--)\
    \ result *= base;\n    return result;\n}\n\nvoid test_numbers_and_polynomials()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(30);\n    assert(bernoulli.number(0)\
    \ == Mint(1));\n    assert(bernoulli.number(1) * Mint(2) == Mint(-1));\n    assert(bernoulli.number(2)\
    \ * Mint(6) == Mint(1));\n    assert(bernoulli.number(4) * Mint(30) == Mint(-1));\n\
    \    for (int degree = 3; degree <= 29; degree += 2) {\n        assert(bernoulli.number(degree)\
    \ == Mint(0));\n    }\n\n    for (int degree = 0; degree <= 20; ++degree) {\n\
    \        auto coefficients = bernoulli.polynomial_coefficients(degree);\n    \
    \    for (int value = -5; value <= 5; ++value) {\n            Mint x = value;\n\
    \            assert(evaluate(coefficients, x) == bernoulli.polynomial(degree,\
    \ x));\n            if (degree > 0) {\n                assert(\n             \
    \       bernoulli.polynomial(degree, x + Mint(1)) -\n                        bernoulli.polynomial(degree,\
    \ x) ==\n                    Mint(degree) * power(x, degree - 1)\n           \
    \     );\n            }\n        }\n    }\n}\n\nvoid test_power_sums() {\n   \
    \ m1une::math::Bernoulli<Mint> bernoulli(20);\n    for (int degree = 0; degree\
    \ <= 20; ++degree) {\n        auto coefficients = bernoulli.power_sum_polynomial(degree);\n\
    \        Mint expected = 0;\n        for (int n = 0; n <= 40; ++n) {\n       \
    \     assert(bernoulli.power_sum(Mint(n), degree) == expected);\n            assert(evaluate(coefficients,\
    \ Mint(n)) == expected);\n            expected += power(Mint(n), degree);\n  \
    \      }\n    }\n\n    for (int degree = 0; degree <= 12; ++degree) {\n      \
    \  for (int left = -10; left <= 10; ++left) {\n            Mint expected = 0;\n\
    \            for (int right = left; right <= 12; ++right) {\n                assert(\n\
    \                    bernoulli.power_sum(Mint(left), Mint(right), degree) ==\n\
    \                    expected\n                );\n                expected +=\
    \ power(Mint(right), degree);\n            }\n        }\n    }\n}\n\nvoid test_polynomial_sums_randomized()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    std::uint64_t state\
    \ = 0xbb67ae8584caa73bULL;\n    auto random = [&state]() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for\
    \ (int test = 0; test < 2000; ++test) {\n        int degree = static_cast<int>(random()\
    \ % 13);\n        std::vector<Mint> coefficients(degree + 1);\n        for (Mint&\
    \ coefficient : coefficients) {\n            coefficient = static_cast<long long>(random()\
    \ % 101) - 50;\n        }\n\n        auto prefix = bernoulli.polynomial_prefix_sum(coefficients);\n\
    \        for (int x = -10; x <= 10; ++x) {\n            assert(\n            \
    \    evaluate(prefix, Mint(x + 1)) - evaluate(prefix, Mint(x)) ==\n          \
    \      evaluate(coefficients, Mint(x))\n            );\n        }\n\n        int\
    \ left = static_cast<int>(random() % 21) - 10;\n        int length = static_cast<int>(random()\
    \ % 21);\n        int right = left + length;\n        Mint expected = 0;\n   \
    \     for (int x = left; x < right; ++x) {\n            expected += evaluate(coefficients,\
    \ Mint(x));\n        }\n        assert(\n            bernoulli.polynomial_sum(\n\
    \                coefficients,\n                Mint(left),\n                Mint(right)\n\
    \            ) == expected\n        );\n    }\n}\n\nvoid test_arithmetic_progressions()\
    \ {\n    m1une::math::Bernoulli<Mint> bernoulli(12);\n    for (int degree = 0;\
    \ degree <= 12; ++degree) {\n        for (int start = -3; start <= 3; ++start)\
    \ {\n            for (int step = -2; step <= 2; ++step) {\n                Mint\
    \ expected = 0;\n                for (int count = 0; count <= 15; ++count) {\n\
    \                    assert(\n                        bernoulli.arithmetic_progression_power_sum(\n\
    \                            Mint(start),\n                            Mint(step),\n\
    \                            Mint(count),\n                            degree\n\
    \                        ) == expected\n                    );\n             \
    \       expected += power(Mint(start + step * count), degree);\n             \
    \   }\n            }\n        }\n    }\n}\n\nint main() {\n    test_numbers_and_polynomials();\n\
    \    test_power_sums();\n    test_polynomial_sums_randomized();\n    test_arithmetic_progressions();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/bernoulli.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/modint.hpp
  - math/combinatorics.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/bernoulli_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-07-10 20:52:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/bernoulli_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/math/bernoulli_utilities.test.cpp
- /verify/verify/math/bernoulli_utilities.test.cpp.html
title: verify/math/bernoulli_utilities.test.cpp
---
