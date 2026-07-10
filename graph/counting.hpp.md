---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_counting.test.cpp
    title: verify/graph/graph_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/counting.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <optional>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"math/fps/convolution.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #line 10 \"math/fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line\
    \ 5 \"math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n#line 8\
    \ \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t\
    \ Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus must be\
    \ positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr\
    \ uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr ModInt\
    \ raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n        return\
    \ x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class\
    \ Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr\
    \ ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
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
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/formal_power_series.hpp\"\
    \n\n\n\n#line 10 \"math/fps/formal_power_series.hpp\"\n\n#line 12 \"math/fps/formal_power_series.hpp\"\
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
    \ 13 \"graph/counting.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nnamespace\
    \ graph_counting_detail {\n\ntemplate <class Mint>\nusing Fps = fps::FormalPowerSeries<Mint>;\n\
    \ntemplate <class Mint>\nvoid assert_maximum(int maximum) {\n    assert(maximum\
    \ >= 0);\n    assert(static_cast<uint64_t>(maximum) < Mint::mod());\n}\n\ntemplate\
    \ <class Mint>\nMint inverse_two() {\n    assert(Mint::mod() != 2);\n    return\
    \ Mint(2).inv();\n}\n\ntemplate <class Mint>\nstd::vector<Mint> to_egf(\n    std::vector<Mint>\
    \ values,\n    const math::Combinatorics<Mint>& combinations\n) {\n    for (int\
    \ i = 0; i < int(values.size()); i++) {\n        values[i] *= combinations.inverse_factorial(i);\n\
    \    }\n    return values;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> from_egf(\n\
    \    std::vector<Mint> coefficients,\n    const math::Combinatorics<Mint>& combinations\n\
    ) {\n    for (int i = 0; i < int(coefficients.size()); i++) {\n        coefficients[i]\
    \ *= combinations.factorial(i);\n    }\n    return coefficients;\n}\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> two_to_binom2(int maximum) {\n    std::vector<Mint>\
    \ result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int n = 1; n <= maximum; n++) {\n        result[n] = result[n - 1] * multiplier;\n\
    \        multiplier += multiplier;\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nFps<Mint> colored_bipartite_egf(\n    int maximum,\n    const math::Combinatorics<Mint>&\
    \ combinations\n) {\n    const Mint half = inverse_two<Mint>();\n\n    Fps<Mint>\
    \ kernel(maximum + 1);\n    kernel[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int i = 1; i <= maximum; i++) {\n        kernel[i] = kernel[i - 1] * multiplier;\n\
    \        multiplier *= half;\n    }\n    for (int i = 0; i <= maximum; i++) {\n\
    \        kernel[i] *= combinations.inverse_factorial(i);\n    }\n\n    Fps<Mint>\
    \ result = (kernel * kernel).pre(maximum + 1);\n    std::vector<Mint> edge_powers\
    \ = two_to_binom2<Mint>(maximum);\n    for (int i = 0; i <= maximum; i++) result[i]\
    \ *= edge_powers[i];\n    return result;\n}\n\n}  // namespace graph_counting_detail\n\
    \ntemplate <class Mint>\nstd::vector<Mint> count_labeled_undirected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    return\
    \ graph_counting_detail::two_to_binom2<Mint>(maximum);\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> count_labeled_connected_graphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(count_labeled_undirected_graphs<Mint>(maximum),\
    \ combinations);\n    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        result[n] = (n == 1 ? Mint(1) : Mint(n).pow(n - 2));\n    }\n   \
    \ return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_forests(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_trees<Mint>(maximum), combinations);\n\
    \    egf = egf.exp(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_unicyclic_connected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps rooted_tree_egf(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        rooted_tree_egf[n] =\n            Mint(n).pow(n - 1) * combinations.inverse_factorial(n);\n\
    \    }\n\n    Fps one_minus_rooted(maximum + 1);\n    one_minus_rooted[0] = 1;\n\
    \    for (int i = 1; i <= maximum; i++) {\n        one_minus_rooted[i] = Mint(0)\
    \ - rooted_tree_egf[i];\n    }\n\n    Fps egf = one_minus_rooted.log(maximum +\
    \ 1);\n    for (Mint& coefficient : egf) coefficient = Mint(0) - coefficient;\n\
    \    egf -= rooted_tree_egf;\n    egf -= ((rooted_tree_egf * rooted_tree_egf).pre(maximum\
    \ + 1) *\n            graph_counting_detail::inverse_two<Mint>());\n    egf *=\
    \ graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_eulerian_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::vector<Mint> all_even(maximum + 1);\n   \
    \ all_even[0] = 1;\n    if (maximum >= 1) {\n        std::vector<Mint> shifted\
    \ = count_labeled_undirected_graphs<Mint>(maximum - 1);\n        for (int n =\
    \ 1; n <= maximum; n++) all_even[n] = shifted[n - 1];\n    }\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(std::move(all_even), combinations);\n\
    \    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::colored_bipartite_egf(maximum, combinations).log(maximum\
    \ + 1);\n    egf *= graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::optional<graph_counting_detail::Fps<Mint>>\
    \ egf =\n        graph_counting_detail::colored_bipartite_egf(maximum, combinations).sqrt(maximum\
    \ + 1);\n    assert(egf.has_value());\n    return graph_counting_detail::from_egf(std::move(*egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_directed_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier\
    \ = 1;\n    const Mint four = 4;\n    for (int n = 1; n <= maximum; n++) {\n \
    \       result[n] = result[n - 1] * multiplier;\n        multiplier *= four;\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_dags(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps denominator(maximum + 1);\n    Mint multiplier = 1;\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n    denominator[0] = 1;\n   \
    \ for (int n = 1; n <= maximum; n++) {\n        denominator[n] = denominator[n\
    \ - 1] * multiplier;\n        multiplier *= half;\n    }\n    for (int n = 0;\
    \ n <= maximum; n++) {\n        denominator[n] *= combinations.inverse_factorial(n);\n\
    \        if (n & 1) denominator[n] = Mint(0) - denominator[n];\n    }\n\n    Fps\
    \ egf = denominator.inv(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] *= combinations.factorial(n)\
    \ * edge_powers[n];\n    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ count_labeled_strongly_connected_digraphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] = edge_powers[n] * combinations.inverse_factorial(n);\n\
    \    }\n\n    egf = egf.inv(maximum + 1);\n    for (int n = 0; n <= maximum; n++)\
    \ egf[n] *= edge_powers[n];\n    egf = egf.log(maximum + 1);\n    for (int n =\
    \ 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_tournaments(int\
    \ maximum) {\n    return count_labeled_undirected_graphs<Mint>(maximum);\n}\n\n\
    template <class Mint>\nstd::vector<Mint> count_labeled_strongly_connected_tournaments(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_tournaments<Mint>(maximum), combinations);\n\
    \    egf = egf.inv(maximum + 1);\n    if (!egf.empty()) egf[0] = 0;\n    for (int\
    \ n = 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_rooted_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    if (maximum == 0) return result;\n\
    \n    std::vector<Mint> divisor_sum(maximum + 1);\n    result[1] = 1;\n    for\
    \ (int multiple = 1; multiple <= maximum; multiple++) {\n        divisor_sum[multiple]\
    \ += result[1];\n    }\n\n    for (int n = 1; n < maximum; n++) {\n        Mint\
    \ sum = 0;\n        for (int i = 1; i <= n; i++) {\n            sum += divisor_sum[i]\
    \ * result[n - i + 1];\n        }\n        result[n + 1] = sum / Mint(n);\n\n\
    \        const int size = n + 1;\n        const Mint contribution = Mint(size)\
    \ * result[size];\n        for (int multiple = size; multiple <= maximum; multiple\
    \ += size) {\n            divisor_sum[multiple] += contribution;\n        }\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    using\
    \ Fps = graph_counting_detail::Fps<Mint>;\n\n    Fps rooted = count_unlabeled_rooted_trees<Mint>(maximum);\n\
    \    Fps rooted_square = (rooted * rooted).pre(maximum + 1);\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n\n    std::vector<Mint> result(maximum\
    \ + 1);\n    for (int n = 1; n <= maximum; n++) {\n        result[n] = rooted[n]\
    \ - rooted_square[n] * half;\n        if ((n & 1) == 0) result[n] += rooted[n\
    \ / 2] * half;\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_COUNTING_HPP\n#define M1UNE_GRAPH_COUNTING_HPP 1\n\n\
    #include <cassert>\n#include <cstdint>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#include \"../math/fps/convolution.hpp\"\n#include \"../math/fps/formal_power_series.hpp\"\
    \n#include \"../math/combinatorics.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nnamespace graph_counting_detail {\n\ntemplate <class Mint>\nusing Fps =\
    \ fps::FormalPowerSeries<Mint>;\n\ntemplate <class Mint>\nvoid assert_maximum(int\
    \ maximum) {\n    assert(maximum >= 0);\n    assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n}\n\ntemplate <class Mint>\nMint inverse_two() {\n    assert(Mint::mod()\
    \ != 2);\n    return Mint(2).inv();\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ to_egf(\n    std::vector<Mint> values,\n    const math::Combinatorics<Mint>&\
    \ combinations\n) {\n    for (int i = 0; i < int(values.size()); i++) {\n    \
    \    values[i] *= combinations.inverse_factorial(i);\n    }\n    return values;\n\
    }\n\ntemplate <class Mint>\nstd::vector<Mint> from_egf(\n    std::vector<Mint>\
    \ coefficients,\n    const math::Combinatorics<Mint>& combinations\n) {\n    for\
    \ (int i = 0; i < int(coefficients.size()); i++) {\n        coefficients[i] *=\
    \ combinations.factorial(i);\n    }\n    return coefficients;\n}\n\ntemplate <class\
    \ Mint>\nstd::vector<Mint> two_to_binom2(int maximum) {\n    std::vector<Mint>\
    \ result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int n = 1; n <= maximum; n++) {\n        result[n] = result[n - 1] * multiplier;\n\
    \        multiplier += multiplier;\n    }\n    return result;\n}\n\ntemplate <class\
    \ Mint>\nFps<Mint> colored_bipartite_egf(\n    int maximum,\n    const math::Combinatorics<Mint>&\
    \ combinations\n) {\n    const Mint half = inverse_two<Mint>();\n\n    Fps<Mint>\
    \ kernel(maximum + 1);\n    kernel[0] = 1;\n    Mint multiplier = 1;\n    for\
    \ (int i = 1; i <= maximum; i++) {\n        kernel[i] = kernel[i - 1] * multiplier;\n\
    \        multiplier *= half;\n    }\n    for (int i = 0; i <= maximum; i++) {\n\
    \        kernel[i] *= combinations.inverse_factorial(i);\n    }\n\n    Fps<Mint>\
    \ result = (kernel * kernel).pre(maximum + 1);\n    std::vector<Mint> edge_powers\
    \ = two_to_binom2<Mint>(maximum);\n    for (int i = 0; i <= maximum; i++) result[i]\
    \ *= edge_powers[i];\n    return result;\n}\n\n}  // namespace graph_counting_detail\n\
    \ntemplate <class Mint>\nstd::vector<Mint> count_labeled_undirected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    return\
    \ graph_counting_detail::two_to_binom2<Mint>(maximum);\n}\n\ntemplate <class Mint>\n\
    std::vector<Mint> count_labeled_connected_graphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(count_labeled_undirected_graphs<Mint>(maximum),\
    \ combinations);\n    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        result[n] = (n == 1 ? Mint(1) : Mint(n).pow(n - 2));\n    }\n   \
    \ return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_forests(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_trees<Mint>(maximum), combinations);\n\
    \    egf = egf.exp(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_unicyclic_connected_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps rooted_tree_egf(maximum + 1);\n    for (int n = 1; n <= maximum; n++)\
    \ {\n        rooted_tree_egf[n] =\n            Mint(n).pow(n - 1) * combinations.inverse_factorial(n);\n\
    \    }\n\n    Fps one_minus_rooted(maximum + 1);\n    one_minus_rooted[0] = 1;\n\
    \    for (int i = 1; i <= maximum; i++) {\n        one_minus_rooted[i] = Mint(0)\
    \ - rooted_tree_egf[i];\n    }\n\n    Fps egf = one_minus_rooted.log(maximum +\
    \ 1);\n    for (Mint& coefficient : egf) coefficient = Mint(0) - coefficient;\n\
    \    egf -= rooted_tree_egf;\n    egf -= ((rooted_tree_egf * rooted_tree_egf).pre(maximum\
    \ + 1) *\n            graph_counting_detail::inverse_two<Mint>());\n    egf *=\
    \ graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_eulerian_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::vector<Mint> all_even(maximum + 1);\n   \
    \ all_even[0] = 1;\n    if (maximum >= 1) {\n        std::vector<Mint> shifted\
    \ = count_labeled_undirected_graphs<Mint>(maximum - 1);\n        for (int n =\
    \ 1; n <= maximum; n++) all_even[n] = shifted[n - 1];\n    }\n\n    graph_counting_detail::Fps<Mint>\
    \ egf =\n        graph_counting_detail::to_egf(std::move(all_even), combinations);\n\
    \    egf = egf.log(maximum + 1);\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_connected_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::colored_bipartite_egf(maximum, combinations).log(maximum\
    \ + 1);\n    egf *= graph_counting_detail::inverse_two<Mint>();\n    return graph_counting_detail::from_egf(std::move(egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_bipartite_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    std::optional<graph_counting_detail::Fps<Mint>>\
    \ egf =\n        graph_counting_detail::colored_bipartite_egf(maximum, combinations).sqrt(maximum\
    \ + 1);\n    assert(egf.has_value());\n    return graph_counting_detail::from_egf(std::move(*egf),\
    \ combinations);\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_directed_graphs(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    result[0] = 1;\n    Mint multiplier\
    \ = 1;\n    const Mint four = 4;\n    for (int n = 1; n <= maximum; n++) {\n \
    \       result[n] = result[n - 1] * multiplier;\n        multiplier *= four;\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_dags(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n    using Fps = graph_counting_detail::Fps<Mint>;\n\n\
    \    Fps denominator(maximum + 1);\n    Mint multiplier = 1;\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n    denominator[0] = 1;\n   \
    \ for (int n = 1; n <= maximum; n++) {\n        denominator[n] = denominator[n\
    \ - 1] * multiplier;\n        multiplier *= half;\n    }\n    for (int n = 0;\
    \ n <= maximum; n++) {\n        denominator[n] *= combinations.inverse_factorial(n);\n\
    \        if (n & 1) denominator[n] = Mint(0) - denominator[n];\n    }\n\n    Fps\
    \ egf = denominator.inv(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] *= combinations.factorial(n)\
    \ * edge_powers[n];\n    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ count_labeled_strongly_connected_digraphs(int maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\
    \    math::Combinatorics<Mint> combinations(maximum);\n\n    graph_counting_detail::Fps<Mint>\
    \ egf(maximum + 1);\n    std::vector<Mint> edge_powers = graph_counting_detail::two_to_binom2<Mint>(maximum);\n\
    \    for (int n = 0; n <= maximum; n++) {\n        egf[n] = edge_powers[n] * combinations.inverse_factorial(n);\n\
    \    }\n\n    egf = egf.inv(maximum + 1);\n    for (int n = 0; n <= maximum; n++)\
    \ egf[n] *= edge_powers[n];\n    egf = egf.log(maximum + 1);\n    for (int n =\
    \ 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_labeled_tournaments(int\
    \ maximum) {\n    return count_labeled_undirected_graphs<Mint>(maximum);\n}\n\n\
    template <class Mint>\nstd::vector<Mint> count_labeled_strongly_connected_tournaments(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    math::Combinatorics<Mint>\
    \ combinations(maximum);\n\n    graph_counting_detail::Fps<Mint> egf =\n     \
    \   graph_counting_detail::to_egf(count_labeled_tournaments<Mint>(maximum), combinations);\n\
    \    egf = egf.inv(maximum + 1);\n    if (!egf.empty()) egf[0] = 0;\n    for (int\
    \ n = 0; n <= maximum; n++) {\n        egf[n] = Mint(0) - egf[n] * combinations.factorial(n);\n\
    \    }\n    return egf;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_rooted_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n\n  \
    \  std::vector<Mint> result(maximum + 1);\n    if (maximum == 0) return result;\n\
    \n    std::vector<Mint> divisor_sum(maximum + 1);\n    result[1] = 1;\n    for\
    \ (int multiple = 1; multiple <= maximum; multiple++) {\n        divisor_sum[multiple]\
    \ += result[1];\n    }\n\n    for (int n = 1; n < maximum; n++) {\n        Mint\
    \ sum = 0;\n        for (int i = 1; i <= n; i++) {\n            sum += divisor_sum[i]\
    \ * result[n - i + 1];\n        }\n        result[n + 1] = sum / Mint(n);\n\n\
    \        const int size = n + 1;\n        const Mint contribution = Mint(size)\
    \ * result[size];\n        for (int multiple = size; multiple <= maximum; multiple\
    \ += size) {\n            divisor_sum[multiple] += contribution;\n        }\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> count_unlabeled_trees(int\
    \ maximum) {\n    graph_counting_detail::assert_maximum<Mint>(maximum);\n    using\
    \ Fps = graph_counting_detail::Fps<Mint>;\n\n    Fps rooted = count_unlabeled_rooted_trees<Mint>(maximum);\n\
    \    Fps rooted_square = (rooted * rooted).pre(maximum + 1);\n    const Mint half\
    \ = graph_counting_detail::inverse_two<Mint>();\n\n    std::vector<Mint> result(maximum\
    \ + 1);\n    for (int n = 1; n <= maximum; n++) {\n        result[n] = rooted[n]\
    \ - rooted_square[n] * half;\n        if ((n & 1) == 0) result[n] += rooted[n\
    \ / 2] * half;\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_GRAPH_COUNTING_HPP\n"
  dependsOn:
  - math/fps/convolution.hpp
  - math/modint.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/combinatorics.hpp
  isVerificationFile: false
  path: graph/counting.hpp
  requiredBy:
  - graph/all.hpp
  timestamp: '2026-07-10 20:52:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_counting.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/counting.hpp
layout: document
title: Graph Counting
---

## Overview

`graph/counting.hpp` computes common graph-counting sequences by number of
vertices. The labeled functions count simple graphs on vertex set
`{0, 1, ..., n - 1}`; two labeled graphs are different when some edge choice is
different. The unlabeled tree functions count isomorphism classes.

All functions return a vector `answer` of length `maximum + 1`, where
`answer[n]` is the number of objects on `n` vertices.

This header counts by vertex number only. It does not keep track of the number
of edges.

## Requirements and Conventions

Let `N = maximum`. In the complexity table, `M(N)` means the cost of one
polynomial multiplication where both inputs have length `O(N)`, and only the
first `N + 1` coefficients may be needed. Equivalently, it is the convolution
cost for formal power series truncated to degree at most `N`. With the supplied
convolution over NTT-friendly static modints, `M(N) = O(N log N)`.

`Mint` must support the operations required by
`fps::FormalPowerSeries<Mint>`: addition, subtraction, multiplication,
division by nonzero small integers, `pow`, `inv`, and `Mint::mod()`. In
practice this is intended for prime moduli such as
`m1une::math::modint998244353`.

The code asserts:

* `maximum >= 0`;
* `maximum < Mint::mod()`, because EGF operations divide by factorials and
  small integers;
* the modulus is not `2` for functions that divide by `2`.

Connectivity follows the convention that the empty graph is not connected.
Thus connected counts have value `0` at `n = 0`. A forest has value `1` at
`n = 0`, representing the empty forest.

A labeled tournament is an orientation of the complete graph on labeled
vertices: for every unordered pair of distinct vertices, exactly one of the two
possible directed edges is chosen. A strongly connected labeled tournament is a
labeled tournament in which every ordered pair of vertices `(u, v)` has a
directed path from `u` to `v`.

## Public Interface

All signatures below are in namespace `m1une::graph`.

| Function | Counts | Time |
| --- | --- | --- |
| `template <class Mint> std::vector<Mint> count_labeled_undirected_graphs(int maximum)` | Simple undirected labeled graphs. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_graphs(int maximum)` | Connected simple undirected labeled graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_trees(int maximum)` | Labeled trees, using Cayley's formula. | `O(N log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_forests(int maximum)` | Labeled forests. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_unicyclic_connected_graphs(int maximum)` | Connected labeled graphs with exactly `n` edges on `n` vertices. | `O(N log N + M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_eulerian_graphs(int maximum)` | Connected undirected labeled graphs where every degree is even. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_connected_bipartite_graphs(int maximum)` | Connected undirected labeled bipartite graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_bipartite_graphs(int maximum)` | Undirected labeled bipartite graphs, not necessarily connected. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_directed_graphs(int maximum)` | Simple directed labeled graphs without loops. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_dags(int maximum)` | Labeled directed acyclic graphs. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_digraphs(int maximum)` | Strongly connected simple directed labeled graphs without loops. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_labeled_tournaments(int maximum)` | Labeled tournaments. | `O(N)` |
| `template <class Mint> std::vector<Mint> count_labeled_strongly_connected_tournaments(int maximum)` | Strongly connected labeled tournaments. | `O(M(N) log N)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_rooted_trees(int maximum)` | Unlabeled rooted trees. | `O(N^2)` |
| `template <class Mint> std::vector<Mint> count_unlabeled_trees(int maximum)` | Unlabeled unrooted trees. | `O(N^2 + M(N))` |

All functions use `O(N)` memory, apart from temporary polynomial buffers.

## Example

```cpp
#include "graph/counting.hpp"
#include "math/modint.hpp"
#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;

    auto connected = m1une::graph::count_labeled_connected_graphs<mint>(5);
    auto dags = m1une::graph::count_labeled_dags<mint>(5);

    std::cout << connected[4] << "\n";  // 38
    std::cout << dags[4] << "\n";       // 543
}
```
