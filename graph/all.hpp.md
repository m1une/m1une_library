---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: graph/bellman_ford.hpp
    title: Bellman-Ford
  - icon: ':heavy_check_mark:'
    path: graph/bfs.hpp
    title: BFS
  - icon: ':heavy_check_mark:'
    path: graph/bipartite.hpp
    title: Bipartite Graph
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/counting.hpp
    title: Graph Counting
  - icon: ':heavy_check_mark:'
    path: graph/cow_game.hpp
    title: Cow Game (Difference Constraints)
  - icon: ':heavy_check_mark:'
    path: graph/cycle_detection.hpp
    title: Cycle Detection
  - icon: ':heavy_check_mark:'
    path: graph/dag_shortest_path.hpp
    title: DAG Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/dominator_tree.hpp
    title: Dominator Tree
  - icon: ':heavy_check_mark:'
    path: graph/general_matching.hpp
    title: General Matching
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/grid.hpp
    title: Grid
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.hpp
    title: Kruskal
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: graph/maximum_clique.hpp
    title: Maximum Clique, Independent Set, and Vertex Cover
  - icon: ':heavy_check_mark:'
    path: graph/minimum_steiner_tree.hpp
    title: Minimum Steiner Tree
  - icon: ':heavy_check_mark:'
    path: graph/namori.hpp
    title: Namori Graph Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/range_edge_graph.hpp
    title: Range Edge Graph
  - icon: ':heavy_check_mark:'
    path: graph/scc.hpp
    title: Strongly Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/topological_sort.hpp
    title: Topological Sort
  - icon: ':heavy_check_mark:'
    path: graph/two_sat.hpp
    title: Two-Satisfiability
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
  - icon: ':heavy_check_mark:'
    path: graph/warshall_floyd.hpp
    title: Warshall-Floyd
  - icon: ':heavy_check_mark:'
    path: graph/zero_one_bfs.hpp
    title: 0-1 BFS
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/all.hpp\"\n\n\n\n#line 1 \"graph/counting.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstdint>\n#include <optional>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"fps/convolution.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#line 10 \"fps/convolution.hpp\"\n\n#line 1 \"math/modint.hpp\"\
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
    \ m1une\n\n\n#line 12 \"fps/convolution.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ + 1> inverse_root;\n\n    NttRoots() {\n        constexpr uint32_t primitive_root\
    \ = primitive_root_constexpr(Mint::mod());\n        for (int level = 1; level\
    \ <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>& ntt_roots()\
    \ {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\ntemplate\
    \ <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse) {\n    const int\
    \ n = int(a.size());\n    assert(n > 0 && (n & (n - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(n) == 0);\n\n    for (int i = 1, j = 0; i < n; i++) {\n    \
    \    int bit = n >> 1;\n        while (j & bit) {\n            j ^= bit;\n   \
    \         bit >>= 1;\n        }\n        j ^= bit;\n        if (i < j) std::swap(a[i],\
    \ a[j]);\n    }\n\n    const auto& roots = ntt_roots<Mint>();\n    int level =\
    \ 1;\n    for (int len = 2; len <= n; len <<= 1, level++) {\n        const Mint\
    \ step = inverse ? roots.inverse_root[level] : roots.root[level];\n        const\
    \ int half = len >> 1;\n        for (int offset = 0; offset < n; offset += len)\
    \ {\n            Mint w = 1;\n            for (int j = 0; j < half; j++) {\n \
    \               Mint even = a[offset + j];\n                Mint odd = a[offset\
    \ + j + half] * w;\n                a[offset + j] = even + odd;\n            \
    \    a[offset + j + half] = even - odd;\n                w *= step;\n        \
    \    }\n        }\n    }\n\n    if (inverse) {\n        const Mint inverse_n =\
    \ Mint(n).inv();\n        for (Mint& value : a) value *= inverse_n;\n    }\n}\n\
    \n}  // namespace internal\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_naive(const\
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
    \ == 0);\n\n    std::vector<Mint> fa(a.begin(), a.end());\n    std::vector<Mint>\
    \ fb(b.begin(), b.end());\n    fa.resize(n);\n    fb.resize(n);\n    internal::ntt(fa,\
    \ false);\n    internal::ntt(fb, false);\n    for (int i = 0; i < n; i++) fa[i]\
    \ *= fb[i];\n    internal::ntt(fa, true);\n    fa.resize(result_size);\n    return\
    \ fa;\n}\n\ntemplate <class Mint>\nstd::vector<Mint> convolution(const std::vector<Mint>&\
    \ a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    if (std::min(a.size(), b.size()) <= 32) return convolution_naive(a, b);\n\
    \n    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n\
    \    while (n < result_size) n <<= 1;\n    if ((Mint::mod() - 1) % uint32_t(n)\
    \ == 0) return convolution_ntt(a, b);\n\n    using Mint1 = math::ModInt<167772161>;\n\
    \    using Mint2 = math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n\
    \    assert(n <= (1 << 24));\n\n    [[maybe_unused]] const unsigned __int128 coefficient_bound\
    \ =\n        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod()\
    \ - 1) *\n        (Mint::mod() - 1);\n    [[maybe_unused]] const unsigned __int128\
    \ crt_modulus =\n        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod()\
    \ * Mint3::mod();\n    assert(coefficient_bound < crt_modulus);\n\n    auto converted_convolution\
    \ = [&]<class OtherMint>() {\n        std::vector<OtherMint> converted_a(a.size());\n\
    \        std::vector<OtherMint> converted_b(b.size());\n        for (int i = 0;\
    \ i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());\n        for\
    \ (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());\n\
    \        return convolution_ntt(converted_a, converted_b);\n    };\n    std::vector<Mint1>\
    \ c1 = converted_convolution.template operator()<Mint1>();\n    std::vector<Mint2>\
    \ c2 = converted_convolution.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ c3 = converted_convolution.template operator()<Mint3>();\n    static const uint64_t\
    \ inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n    static const uint64_t\
    \ mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static const uint64_t mod1_mod2_mod3\
    \ =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();\n    static\
    \ const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
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
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"fps/formal_power_series.hpp\"\
    \n\n\n\n#line 10 \"fps/formal_power_series.hpp\"\n\n#line 12 \"fps/formal_power_series.hpp\"\
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
    \ = std::min(size << 1, degree);\n            Fps product = this->pre(next_size)\
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
    \ m1une\n\n\n#line 1 \"graph/directed.hpp\"\n\n\n\n#line 1 \"graph/cycle_detection.hpp\"\
    \n\n\n\n#line 6 \"graph/cycle_detection.hpp\"\n\n#line 1 \"graph/graph.hpp\"\n\
    \n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 8 \"graph/cycle_detection.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct Cycle {\n    std::vector<int> vertices;\n    std::vector<int>\
    \ edge_ids;\n\n    bool empty() const {\n        return vertices.empty();\n  \
    \  }\n};\n\ninline Cycle restore_cycle(int from, int to, int closing_edge, const\
    \ std::vector<int>& parent,\n                           const std::vector<int>&\
    \ parent_edge) {\n    Cycle result;\n    result.vertices.push_back(to);\n\n  \
    \  std::vector<int> middle_vertices;\n    std::vector<int> middle_edges;\n   \
    \ for (int v = from; v != to; v = parent[v]) {\n        middle_vertices.push_back(v);\n\
    \        middle_edges.push_back(parent_edge[v]);\n    }\n    std::reverse(middle_vertices.begin(),\
    \ middle_vertices.end());\n    std::reverse(middle_edges.begin(), middle_edges.end());\n\
    \n    result.vertices.insert(result.vertices.end(), middle_vertices.begin(), middle_vertices.end());\n\
    \    result.vertices.push_back(to);\n    result.edge_ids.insert(result.edge_ids.end(),\
    \ middle_edges.begin(), middle_edges.end());\n    result.edge_ids.push_back(closing_edge);\n\
    \    return result;\n}\n\ntemplate <class T>\nCycle find_directed_cycle(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> color(n, 0), parent(n,\
    \ -1), parent_edge(n, -1);\n    Cycle result;\n\n    auto dfs = [&](auto self,\
    \ int v) -> bool {\n        color[v] = 1;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to)) return true;\n            } else if (color[e.to]\
    \ == 1) {\n                result = restore_cycle(v, e.to, e.id, parent, parent_edge);\n\
    \                return true;\n            }\n        }\n        color[v] = 2;\n\
    \        return false;\n    };\n\n    for (int v = 0; v < n; v++) {\n        if\
    \ (color[v] == 0 && dfs(dfs, v)) break;\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nCycle find_undirected_cycle(const Graph<T>& g) {\n    int n = g.size();\n\
    \    std::vector<int> color(n, 0), parent(n, -1), parent_edge(n, -1);\n    Cycle\
    \ result;\n\n    auto dfs = [&](auto self, int v, int pe) -> bool {\n        color[v]\
    \ = 1;\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            if (e.id == pe) continue;\n            if (color[e.to] == 0) {\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                if (self(self, e.to, e.id)) return true;\n            } else\
    \ if (color[e.to] == 1) {\n                result = restore_cycle(v, e.to, e.id,\
    \ parent, parent_edge);\n                return true;\n            }\n       \
    \ }\n        color[v] = 2;\n        return false;\n    };\n\n    for (int v =\
    \ 0; v < n; v++) {\n        if (color[v] == 0 && dfs(dfs, v, -1)) break;\n   \
    \ }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\
    \n#line 1 \"graph/scc.hpp\"\n\n\n\n#line 8 \"graph/scc.hpp\"\n\n#line 10 \"graph/scc.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct SccResult {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n\n    template <class T>\n    Graph<int> dag(const Graph<T>& g) const\
    \ {\n        std::vector<std::pair<int, int>> edges;\n        for (int v = 0;\
    \ v < g.size(); v++) {\n            for (const auto& e : g[v]) {\n           \
    \     if (!e.alive) continue;\n                int a = comp[e.from], b = comp[e.to];\n\
    \                if (a != b) edges.emplace_back(a, b);\n            }\n      \
    \  }\n        std::sort(edges.begin(), edges.end());\n        edges.erase(std::unique(edges.begin(),\
    \ edges.end()), edges.end());\n\n        Graph<int> result(count);\n        for\
    \ (auto [a, b] : edges) result.add_directed_edge(a, b);\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nSccResult strongly_connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> ord(n, -1), low(n,\
    \ 0), comp(n, -1), stack;\n    std::vector<char> in_stack(n, false);\n    std::vector<std::vector<int>>\
    \ groups;\n    int now = 0;\n\n    auto dfs = [&](auto self, int v) -> void {\n\
    \        ord[v] = low[v] = now++;\n        stack.push_back(v);\n        in_stack[v]\
    \ = true;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n\
    \            int to = e.to;\n            if (ord[to] == -1) {\n              \
    \  self(self, to);\n                low[v] = std::min(low[v], low[to]);\n    \
    \        } else if (in_stack[to]) {\n                low[v] = std::min(low[v],\
    \ ord[to]);\n            }\n        }\n\n        if (low[v] != ord[v]) return;\n\
    \        std::vector<int> group;\n        while (true) {\n            int u =\
    \ stack.back();\n            stack.pop_back();\n            in_stack[u] = false;\n\
    \            group.push_back(u);\n            if (u == v) break;\n        }\n\
    \        groups.push_back(std::move(group));\n    };\n\n    for (int v = 0; v\
    \ < n; v++) {\n        if (ord[v] == -1) dfs(dfs, v);\n    }\n\n    std::reverse(groups.begin(),\
    \ groups.end());\n    for (int i = 0; i < int(groups.size()); i++) {\n       \
    \ for (int v : groups[i]) comp[v] = i;\n    }\n\n    return SccResult{int(groups.size()),\
    \ std::move(comp), std::move(groups)};\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/shortest_path.hpp\"\n\n\n\n#line 1 \"graph/bellman_ford.hpp\"\
    \n\n\n\n#line 6 \"graph/bellman_ford.hpp\"\n#include <limits>\n#include <queue>\n\
    #line 9 \"graph/bellman_ford.hpp\"\n\n#line 11 \"graph/bellman_ford.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct BellmanFordResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<bool> negative;\n    T inf;\n    bool has_negative_cycle;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    bool affected_by_negative_cycle(int\
    \ v) const {\n        assert(0 <= v && v < int(negative.size()));\n        return\
    \ negative[v];\n    }\n\n    std::vector<int> path(int t) const {\n        assert(reachable(t));\n\
    \        assert(!affected_by_negative_cycle(t));\n        std::vector<int> result;\n\
    \        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n      \
    \  std::reverse(result.begin(), result.end());\n        return result;\n    }\n\
    };\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const Graph<T>& g,\
    \ const std::vector<int>& sources,\n                                  T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    BellmanFordResult<T>\
    \ result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n, -1);\n\
    \    result.parent_edge.assign(n, -1);\n    result.negative.assign(n, false);\n\
    \    result.inf = inf;\n    result.has_negative_cycle = false;\n\n    for (int\
    \ s : sources) {\n        assert(0 <= s && s < n);\n        result.dist[s] = T(0);\n\
    \    }\n\n    std::vector<int> relaxed_vertices;\n    for (int iter = 0; iter\
    \ < n; iter++) {\n        bool updated = false;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (result.dist[v] == inf) continue;\n            for (const\
    \ auto& e : g[v]) {\n                if (!e.alive) continue;\n               \
    \ T nd = result.dist[v] + e.cost;\n                if (result.dist[e.to] <= nd)\
    \ continue;\n                result.dist[e.to] = nd;\n                result.parent[e.to]\
    \ = v;\n                result.parent_edge[e.to] = e.id;\n                updated\
    \ = true;\n                if (iter == n - 1) relaxed_vertices.push_back(e.to);\n\
    \            }\n        }\n        if (!updated) break;\n    }\n\n    std::queue<int>\
    \ que;\n    for (int v : relaxed_vertices) {\n        if (result.negative[v])\
    \ continue;\n        result.negative[v] = true;\n        que.push(v);\n    }\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.negative[e.to]) continue;\n            result.negative[e.to]\
    \ = true;\n            que.push(e.to);\n        }\n    }\n\n    for (bool x :\
    \ result.negative) result.has_negative_cycle = result.has_negative_cycle || x;\n\
    \    return result;\n}\n\ntemplate <class T>\nBellmanFordResult<T> bellman_ford(const\
    \ Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4)) {\n    return\
    \ bellman_ford(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/bfs.hpp\"\n\n\n\n#line 8 \"graph/bfs.hpp\"\
    \n\n#line 10 \"graph/bfs.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ BfsResult {\n    std::vector<int> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n\n    bool reachable(int v) const {\n        assert(0 <= v &&\
    \ v < int(dist.size()));\n        return dist[v] != -1;\n    }\n\n    std::vector<int>\
    \ path(int t) const {\n        assert(reachable(t));\n        std::vector<int>\
    \ result;\n        for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n\
    \        std::reverse(result.begin(), result.end());\n        return result;\n\
    \    }\n};\n\ntemplate <class T>\nBfsResult bfs(const Graph<T>& g, const std::vector<int>&\
    \ sources) {\n    int n = g.size();\n    BfsResult result;\n    result.dist.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \n    std::queue<int> que;\n    for (int s : sources) {\n        assert(0 <= s\
    \ && s < n);\n        if (result.dist[s] != -1) continue;\n        result.dist[s]\
    \ = 0;\n        que.push(s);\n    }\n\n    while (!que.empty()) {\n        int\
    \ v = que.front();\n        que.pop();\n        for (const auto& e : g[v]) {\n\
    \            if (!e.alive) continue;\n            if (result.dist[e.to] != -1)\
    \ continue;\n            result.dist[e.to] = result.dist[v] + 1;\n           \
    \ result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n   \
    \         que.push(e.to);\n        }\n    }\n\n    return result;\n}\n\ntemplate\
    \ <class T>\nBfsResult bfs(const Graph<T>& g, int s) {\n    return bfs(g, std::vector<int>{s});\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/cow_game.hpp\"\
    \n\n\n\n#line 10 \"graph/cow_game.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct CowGameConstraint {\n    int from;\n    int\
    \ to;\n    T upper_bound;\n};\n\ntemplate <class T>\nstruct CowGameSolution {\n\
    \    bool feasible = false;\n    std::vector<T> value;\n\n    bool is_feasible()\
    \ const {\n        return feasible;\n    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds\
    \ {\n    bool feasible;\n    std::vector<T> upper_bound;\n    T inf;\n\n    bool\
    \ is_feasible() const {\n        return feasible;\n    }\n\n    bool bounded(int\
    \ variable) const {\n        assert(0 <= variable && variable < int(upper_bound.size()));\n\
    \        return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"\
    graph/dag_shortest_path.hpp\"\n\n\n\n#line 9 \"graph/dag_shortest_path.hpp\"\n\
    \n#line 1 \"graph/topological_sort.hpp\"\n\n\n\n#line 7 \"graph/topological_sort.hpp\"\
    \n\n#line 9 \"graph/topological_sort.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstd::optional<std::vector<int>> topological_sort(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    std::vector<int> indeg(n, 0);\n \
    \   for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v]) {\n    \
    \        if (!e.alive) continue;\n            indeg[e.to]++;\n        }\n    }\n\
    \n    std::queue<int> que;\n    for (int v = 0; v < n; v++) {\n        if (indeg[v]\
    \ == 0) que.push(v);\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    while (!que.empty()) {\n        int v = que.front();\n        que.pop();\n\
    \        order.push_back(v);\n        for (const auto& e : g[v]) {\n         \
    \   if (!e.alive) continue;\n            indeg[e.to]--;\n            if (indeg[e.to]\
    \ == 0) que.push(e.to);\n        }\n    }\n\n    if (int(order.size()) != n) return\
    \ std::nullopt;\n    return order;\n}\n\ntemplate <class T>\nbool is_dag(const\
    \ Graph<T>& g) {\n    return topological_sort(g).has_value();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 12 \"graph/dag_shortest_path.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct DagShortestPathResult\
    \ {\n    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> topological_order;\n    T inf;\n\n    bool\
    \ reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, const std::vector<int>& sources,\
    \ T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n   \
    \ auto order = topological_sort(g);\n    if (!order) return std::nullopt;\n\n\
    \    DagShortestPathResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.topological_order =\
    \ *order;\n    result.inf = inf;\n\n    for (int s : sources) {\n        assert(0\
    \ <= s && s < n);\n        if (result.dist[s] == T(0)) continue;\n        result.dist[s]\
    \ = T(0);\n    }\n\n    for (int v : *order) {\n        if (result.dist[v] ==\
    \ inf) continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            T nd = result.dist[v] + e.cost;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n        }\n    }\n\n   \
    \ return result;\n}\n\ntemplate <class T>\nstd::optional<DagShortestPathResult<T>>\
    \ dag_shortest_path(\n    const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    return dag_shortest_path(g, std::vector<int>{s}, inf);\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/dijkstra.hpp\"\
    \n\n\n\n#line 6 \"graph/dijkstra.hpp\"\n#include <functional>\n#line 11 \"graph/dijkstra.hpp\"\
    \n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T>\nstruct DijkstraResult {\n    std::vector<T> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    T inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, const std::vector<int>& sources,\n             \
    \              T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    DijkstraResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using\
    \ P = std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           T nd = d + e.cost;\n            if (result.dist[e.to] <= nd) continue;\n\
    \            result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n \
    \           result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))\
    \ {\n    return dijkstra(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/warshall_floyd.hpp\"\n\n\n\n#line 8\
    \ \"graph/warshall_floyd.hpp\"\n\n#line 10 \"graph/warshall_floyd.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstd::vector<std::vector<T>>\
    \ warshall_floyd(std::vector<std::vector<T>> dist,\n                         \
    \                  T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n\
    \ = int(dist.size());\n    for (int k = 0; k < n; k++) {\n        for (int i =\
    \ 0; i < n; i++) {\n            if (dist[i][k] == inf) continue;\n           \
    \ for (int j = 0; j < n; j++) {\n                if (dist[k][j] == inf) continue;\n\
    \                T nd = dist[i][k] + dist[k][j];\n                if (nd < dist[i][j])\
    \ dist[i][j] = nd;\n            }\n        }\n    }\n    return dist;\n}\n\ntemplate\
    \ <class T>\nstd::vector<std::vector<T>> warshall_floyd(const Graph<T>& g, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n    std::vector<std::vector<T>>\
    \ dist(n, std::vector<T>(n, inf));\n    for (int i = 0; i < n; i++) dist[i][i]\
    \ = T(0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            if (e.cost < dist[e.from][e.to])\
    \ dist[e.from][e.to] = e.cost;\n        }\n    }\n    return warshall_floyd(std::move(dist),\
    \ inf);\n}\n\ntemplate <class T>\nbool warshall_floyd_add_directed_edge(std::vector<std::vector<T>>&\
    \ dist, int from, int to, T cost,\n                                      T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n \
    \   assert(0 <= from && from < n);\n    assert(0 <= to && to < n);\n\n    std::vector<T>\
    \ to_from(n), from_to(n);\n    for (int i = 0; i < n; i++) {\n        to_from[i]\
    \ = dist[i][from];\n        from_to[i] = dist[to][i];\n    }\n\n    bool updated\
    \ = false;\n    for (int i = 0; i < n; i++) {\n        if (to_from[i] == inf)\
    \ continue;\n        for (int j = 0; j < n; j++) {\n            if (from_to[j]\
    \ == inf) continue;\n            T nd = to_from[i] + cost + from_to[j];\n    \
    \        if (nd < dist[i][j]) {\n                dist[i][j] = nd;\n          \
    \      updated = true;\n            }\n        }\n    }\n    return updated;\n\
    }\n\ntemplate <class T>\nbool warshall_floyd_add_undirected_edge(std::vector<std::vector<T>>&\
    \ dist, int u, int v, T cost,\n                                        T inf =\
    \ std::numeric_limits<T>::max() / T(4)) {\n    int n = int(dist.size());\n   \
    \ assert(0 <= u && u < n);\n    assert(0 <= v && v < n);\n\n    std::vector<T>\
    \ to_u(n), from_u(n), to_v(n), from_v(n);\n    for (int i = 0; i < n; i++) {\n\
    \        to_u[i] = dist[i][u];\n        from_u[i] = dist[u][i];\n        to_v[i]\
    \ = dist[i][v];\n        from_v[i] = dist[v][i];\n    }\n\n    bool updated =\
    \ false;\n    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++)\
    \ {\n            if (to_u[i] != inf && from_v[j] != inf) {\n                T\
    \ nd = to_u[i] + cost + from_v[j];\n                if (nd < dist[i][j]) {\n \
    \                   dist[i][j] = nd;\n                    updated = true;\n  \
    \              }\n            }\n            if (to_v[i] != inf && from_u[j] !=\
    \ inf) {\n                T nd = to_v[i] + cost + from_u[j];\n               \
    \ if (nd < dist[i][j]) {\n                    dist[i][j] = nd;\n             \
    \       updated = true;\n                }\n            }\n        }\n    }\n\
    \    return updated;\n}\n\ntemplate <class T>\nbool has_negative_cycle(const std::vector<std::vector<T>>&\
    \ dist) {\n    int n = int(dist.size());\n    for (int i = 0; i < n; i++) {\n\
    \        if (dist[i][i] < T(0)) return true;\n    }\n    return false;\n}\n\n\
    }  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/zero_one_bfs.hpp\"\
    \n\n\n\n#line 6 \"graph/zero_one_bfs.hpp\"\n#include <deque>\n#line 9 \"graph/zero_one_bfs.hpp\"\
    \n\n#line 11 \"graph/zero_one_bfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct ZeroOneBfsResult {\n    std::vector<int> dist;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    int inf;\n\n    bool reachable(int\
    \ v) const {\n        assert(0 <= v && v < int(dist.size()));\n        return\
    \ dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const {\n       \
    \ assert(reachable(t));\n        std::vector<int> result;\n        for (int v\
    \ = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nZeroOneBfsResult\
    \ zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources,\n         \
    \                     int inf = std::numeric_limits<int>::max() / 2) {\n    int\
    \ n = g.size();\n    ZeroOneBfsResult result;\n    result.dist.assign(n, inf);\n\
    \    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n   \
    \ result.inf = inf;\n\n    std::deque<int> deq;\n    for (int s : sources) {\n\
    \        assert(0 <= s && s < n);\n        if (result.dist[s] == 0) continue;\n\
    \        result.dist[s] = 0;\n        deq.push_back(s);\n    }\n\n    while (!deq.empty())\
    \ {\n        int v = deq.front();\n        deq.pop_front();\n        for (const\
    \ auto& e : g[v]) {\n            if (!e.alive) continue;\n            int w;\n\
    \            if (e.cost == T(0)) {\n                w = 0;\n            } else\
    \ {\n                assert(e.cost == T(1));\n                w = 1;\n       \
    \     }\n            int nd = result.dist[v] + w;\n            if (result.dist[e.to]\
    \ <= nd) continue;\n            result.dist[e.to] = nd;\n            result.parent[e.to]\
    \ = v;\n            result.parent_edge[e.to] = e.id;\n            if (w == 0)\
    \ {\n                deq.push_front(e.to);\n            } else {\n           \
    \     deq.push_back(e.to);\n            }\n        }\n    }\n\n    return result;\n\
    }\n\ntemplate <class T>\nZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int\
    \ s, int inf = std::numeric_limits<int>::max() / 2) {\n    return zero_one_bfs(g,\
    \ std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 11 \"graph/shortest_path.hpp\"\n\n\n#line 1 \"graph/two_sat.hpp\"\n\n\
    \n\n#line 5 \"graph/two_sat.hpp\"\n#include <cstddef>\n#line 9 \"graph/two_sat.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\n// A 2-SAT solver using iterative\
    \ strongly connected components.\nstruct TwoSat {\n   private:\n    struct Csr\
    \ {\n        std::vector<int> start;\n        std::vector<int> to;\n    };\n\n\
    \    int _n;\n    std::vector<std::pair<int, int>> _edges;\n    bool _solved;\n\
    \    bool _satisfiable;\n    std::vector<bool> _answer;\n\n    int node(int variable,\
    \ bool value) const {\n        assert(0 <= variable && variable < _n);\n     \
    \   return 2 * variable + int(value);\n    }\n\n    void add_edge(int from, int\
    \ to) {\n        _edges.emplace_back(from, to);\n        _solved = false;\n  \
    \      _answer.clear();\n    }\n\n    Csr build_csr(bool reverse) const {\n  \
    \      int vertices = 2 * _n;\n        Csr graph;\n        graph.start.assign(vertices\
    \ + 1, 0);\n        graph.to.resize(_edges.size());\n\n        for (auto [from,\
    \ to] : _edges) {\n            int source = reverse ? to : from;\n           \
    \ graph.start[source + 1]++;\n        }\n        for (int v = 0; v < vertices;\
    \ v++) {\n            graph.start[v + 1] += graph.start[v];\n        }\n\n   \
    \     std::vector<int> cursor = graph.start;\n        for (auto [from, to] : _edges)\
    \ {\n            int source = reverse ? to : from;\n            int target = reverse\
    \ ? from : to;\n            graph.to[cursor[source]++] = target;\n        }\n\
    \        return graph;\n    }\n\n   public:\n    TwoSat() : TwoSat(0) {}\n\n \
    \   explicit TwoSat(int n)\n        : _n(n), _solved(false), _satisfiable(false)\
    \ {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 10 \"graph/directed.hpp\"\
    \n\n\n#line 1 \"graph/dominator_tree.hpp\"\n\n\n\n#line 7 \"graph/dominator_tree.hpp\"\
    \n\n#line 9 \"graph/dominator_tree.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct DominatorTree {\n    int root;\n    std::vector<int> immediate_dominator;\n\
    \    std::vector<std::vector<int>> children;\n    std::vector<int> dfs_order;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n\n    int size() const\
    \ {\n        return int(immediate_dominator.size());\n    }\n\n    bool reachable(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < size());\n        return\
    \ immediate_dominator[vertex] != -1;\n    }\n\n    bool dominates(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < size());\n \
    \       assert(0 <= vertex && vertex < size());\n        return\n            reachable(ancestor)\
    \ &&\n            reachable(vertex) &&\n            tin[ancestor] <= tin[vertex]\
    \ &&\n            tin[vertex] < tout[ancestor];\n    }\n};\n\n// Lengauer-Tarjan\
    \ immediate dominators from one start vertex.\ntemplate <class T>\nDominatorTree\
    \ dominator_tree(const Graph<T>& graph, int root) {\n    int n = graph.size();\n\
    \    assert(0 <= root && root < n);\n\n    std::vector<int> dfs_index(n, -1);\n\
    \    std::vector<int> vertex;\n    std::vector<int> parent_vertex(n, -1);\n  \
    \  std::vector<std::pair<int, int>> stack;\n    dfs_index[root] = 0;\n    vertex.push_back(root);\n\
    \    stack.emplace_back(root, 0);\n\n    while (!stack.empty()) {\n        int\
    \ current = stack.back().first;\n        int& edge_index = stack.back().second;\n\
    \        if (edge_index == int(graph[current].size())) {\n            stack.pop_back();\n\
    \            continue;\n        }\n        const auto& edge = graph[current][edge_index++];\n\
    \        if (!edge.alive || dfs_index[edge.to] != -1) continue;\n        parent_vertex[edge.to]\
    \ = current;\n        dfs_index[edge.to] = int(vertex.size());\n        vertex.push_back(edge.to);\n\
    \        stack.emplace_back(edge.to, 0);\n    }\n\n    int reachable_count = int(vertex.size());\n\
    \    std::vector<std::vector<int>> predecessor(reachable_count);\n    for (int\
    \ from : vertex) {\n        for (const auto& edge : graph[from]) {\n         \
    \   if (!edge.alive || dfs_index[edge.to] == -1) continue;\n            predecessor[dfs_index[edge.to]].push_back(dfs_index[from]);\n\
    \        }\n    }\n\n    std::vector<int> parent(reachable_count, -1);\n    for\
    \ (int index = 1; index < reachable_count; ++index) {\n        parent[index] =\
    \ dfs_index[parent_vertex[vertex[index]]];\n    }\n\n    std::vector<int> semi(reachable_count);\n\
    \    std::vector<int> idom(reachable_count, -1);\n    std::vector<int> ancestor(reachable_count,\
    \ -1);\n    std::vector<int> label(reachable_count);\n    std::vector<std::vector<int>>\
    \ bucket(reachable_count);\n    for (int index = 0; index < reachable_count; ++index)\
    \ {\n        semi[index] = index;\n        label[index] = index;\n    }\n\n  \
    \  auto compress = [&](int start) {\n        std::vector<int> path;\n        int\
    \ current = start;\n        while (\n            ancestor[current] != -1 &&\n\
    \            ancestor[ancestor[current]] != -1\n        ) {\n            path.push_back(current);\n\
    \            current = ancestor[current];\n        }\n        for (int index =\
    \ int(path.size()) - 1; index >= 0; --index) {\n            int node = path[index];\n\
    \            int parent_node = ancestor[node];\n            if (semi[label[parent_node]]\
    \ < semi[label[node]]) {\n                label[node] = label[parent_node];\n\
    \            }\n            ancestor[node] = ancestor[parent_node];\n        }\n\
    \    };\n\n    auto eval = [&](int node) {\n        if (ancestor[node] == -1)\
    \ return label[node];\n        compress(node);\n        int parent_node = ancestor[node];\n\
    \        if (semi[label[parent_node]] < semi[label[node]]) {\n            return\
    \ label[parent_node];\n        }\n        return label[node];\n    };\n\n    for\
    \ (int current = reachable_count - 1; current >= 1; --current) {\n        for\
    \ (int previous : predecessor[current]) {\n            semi[current] = std::min(semi[current],\
    \ semi[eval(previous)]);\n        }\n        bucket[semi[current]].push_back(current);\n\
    \        ancestor[current] = parent[current];\n\n        int parent_node = parent[current];\n\
    \        for (int node : bucket[parent_node]) {\n            int best = eval(node);\n\
    \            idom[node] =\n                semi[best] < semi[node] ? best : parent_node;\n\
    \        }\n        bucket[parent_node].clear();\n    }\n\n    for (int current\
    \ = 1; current < reachable_count; ++current) {\n        if (idom[current] != semi[current])\
    \ {\n            idom[current] = idom[idom[current]];\n        }\n    }\n    idom[0]\
    \ = 0;\n\n    DominatorTree result;\n    result.root = root;\n    result.immediate_dominator.assign(n,\
    \ -1);\n    result.children.assign(n, {});\n    result.dfs_order = vertex;\n \
    \   for (int index = 0; index < reachable_count; ++index) {\n        int current\
    \ = vertex[index];\n        int dominator = vertex[idom[index]];\n        result.immediate_dominator[current]\
    \ = dominator;\n        if (current != root) result.children[dominator].push_back(current);\n\
    \    }\n\n    result.tin.assign(n, -1);\n    result.tout.assign(n, -1);\n    int\
    \ timer = 0;\n    std::vector<std::pair<int, int>> tree_stack;\n    tree_stack.emplace_back(root,\
    \ 0);\n    result.tin[root] = timer++;\n    while (!tree_stack.empty()) {\n  \
    \      int current = tree_stack.back().first;\n        int& child_index = tree_stack.back().second;\n\
    \        if (child_index == int(result.children[current].size())) {\n        \
    \    result.tout[current] = timer;\n            tree_stack.pop_back();\n     \
    \       continue;\n        }\n        int child = result.children[current][child_index++];\n\
    \        result.tin[child] = timer++;\n        tree_stack.emplace_back(child,\
    \ 0);\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/grid.hpp\"\n\n\n\n#line 8 \"graph/grid.hpp\"\n\n\
    #line 10 \"graph/grid.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\nstruct\
    \ Grid {\n   private:\n    int _h;\n    int _w;\n\n   public:\n    static constexpr\
    \ std::array<int, 4> di4 = {-1, 0, 1, 0};\n    static constexpr std::array<int,\
    \ 4> dj4 = {0, 1, 0, -1};\n    static constexpr std::array<int, 8> di8 = {-1,\
    \ -1, -1, 0, 0, 1, 1, 1};\n    static constexpr std::array<int, 8> dj8 = {-1,\
    \ 0, 1, -1, 1, -1, 0, 1};\n\n    Grid() : _h(0), _w(0) {}\n    Grid(int h, int\
    \ w) : _h(h), _w(w) {\n        assert(0 <= h);\n        assert(0 <= w);\n    }\n\
    \n    int height() const {\n        return _h;\n    }\n\n    int width() const\
    \ {\n        return _w;\n    }\n\n    int size() const {\n        return _h *\
    \ _w;\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    bool inside(int i, int j) const {\n        return 0 <= i && i < _h && 0\
    \ <= j && j < _w;\n    }\n\n    int id(int i, int j) const {\n        assert(inside(i,\
    \ j));\n        return i * _w + j;\n    }\n\n    std::pair<int, int> pos(int v)\
    \ const {\n        assert(0 <= v && v < size());\n        return {v / _w, v %\
    \ _w};\n    }\n\n    std::vector<std::pair<int, int>> adj4(int i, int j) const\
    \ {\n        assert(inside(i, j));\n        std::vector<std::pair<int, int>> result;\n\
    \        result.reserve(4);\n        for (int k = 0; k < 4; k++) {\n         \
    \   int ni = i + di4[k], nj = j + dj4[k];\n            if (inside(ni, nj)) result.emplace_back(ni,\
    \ nj);\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> adj8(int i, int j) const {\n        assert(inside(i, j));\n        std::vector<std::pair<int,\
    \ int>> result;\n        result.reserve(8);\n        for (int k = 0; k < 8; k++)\
    \ {\n            int ni = i + di8[k], nj = j + dj8[k];\n            if (inside(ni,\
    \ nj)) result.emplace_back(ni, nj);\n        }\n        return result;\n    }\n\
    \n    std::vector<int> adj4_ids(int v) const {\n        auto [i, j] = pos(v);\n\
    \        std::vector<int> result;\n        result.reserve(4);\n        for (auto\
    \ [ni, nj] : adj4(i, j)) result.push_back(id(ni, nj));\n        return result;\n\
    \    }\n\n    std::vector<int> adj8_ids(int v) const {\n        auto [i, j] =\
    \ pos(v);\n        std::vector<int> result;\n        result.reserve(8);\n    \
    \    for (auto [ni, nj] : adj8(i, j)) result.push_back(id(ni, nj));\n        return\
    \ result;\n    }\n\n    Graph<int> graph4() const {\n        return graph4([](int,\
    \ int) { return true; });\n    }\n\n    Graph<int> graph8() const {\n        return\
    \ graph8([](int, int) { return true; });\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph4(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj4(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n\n    template <class Passable>\n\
    \    Graph<int> graph8(Passable passable) const {\n        Graph<int> g(size());\n\
    \        for (int i = 0; i < _h; i++) {\n            for (int j = 0; j < _w; j++)\
    \ {\n                if (!passable(i, j)) continue;\n                int v = id(i,\
    \ j);\n                for (auto [ni, nj] : adj8(i, j)) {\n                  \
    \  if (!passable(ni, nj)) continue;\n                    int to = id(ni, nj);\n\
    \                    if (v < to) g.add_edge(v, to);\n                }\n     \
    \       }\n        }\n        return g;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/range_edge_graph.hpp\"\n\n\n\n#line\
    \ 6 \"graph/range_edge_graph.hpp\"\n\n#line 8 \"graph/range_edge_graph.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\nstruct RangeEdgeNode {\n    int vertex;\n\
    \    int left;\n    int right;\n};\n\ntemplate <class T>\nclass RangeEdgeGraph\
    \ {\n    struct SegmentNode {\n        int left = 0;\n        int right = 0;\n\
    \        int from_vertex = -1;\n        int to_vertex = -1;\n    };\n\n    int\
    \ _n;\n    Graph<T> _graph;\n    std::vector<SegmentNode> _segment;\n\n    void\
    \ assert_point(int point) const {\n        (void)point;\n        assert(0 <= point\
    \ && point < _n);\n    }\n\n    void assert_range(int left, int right) const {\n\
    \        (void)left;\n        (void)right;\n        assert(0 <= left && left <=\
    \ right && right <= _n);\n    }\n\n    void build(int node, int left, int right)\
    \ {\n        _segment[node].left = left;\n        _segment[node].right = right;\n\
    \        if (right - left == 1) {\n            _segment[node].from_vertex = left;\n\
    \            _segment[node].to_vertex = left;\n            return;\n        }\n\
    \n        int middle = (left + right) / 2;\n        build(node * 2, left, middle);\n\
    \        build(node * 2 + 1, middle, right);\n\n        int from_vertex = _graph.add_vertex();\n\
    \        int to_vertex = _graph.add_vertex();\n        _segment[node].from_vertex\
    \ = from_vertex;\n        _segment[node].to_vertex = to_vertex;\n\n        _graph.add_directed_edge(_segment[node\
    \ * 2].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(_segment[node\
    \ * 2 + 1].from_vertex, from_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2].to_vertex, T());\n        _graph.add_directed_edge(to_vertex,\
    \ _segment[node * 2 + 1].to_vertex, T());\n    }\n\n    void collect(int node,\
    \ int left, int right, bool from_side,\n                 std::vector<RangeEdgeNode>&\
    \ result) const {\n        const auto& current = _segment[node];\n        if (right\
    \ <= current.left || current.right <= left) return;\n        if (left <= current.left\
    \ && current.right <= right) {\n            int vertex = from_side ? current.from_vertex\
    \ : current.to_vertex;\n            result.push_back(RangeEdgeNode{vertex, current.left,\
    \ current.right});\n            return;\n        }\n        collect(node * 2,\
    \ left, right, from_side, result);\n        collect(node * 2 + 1, left, right,\
    \ from_side, result);\n    }\n\n   public:\n    RangeEdgeGraph() : RangeEdgeGraph(0)\
    \ {}\n\n    explicit RangeEdgeGraph(int point_count)\n        : _n(point_count),\n\
    \          _graph(point_count),\n          _segment(point_count == 0 ? 1 : point_count\
    \ * 4) {\n        assert(point_count >= 0);\n        if (point_count != 0) build(1,\
    \ 0, point_count);\n    }\n\n    int size() const {\n        return _n;\n    }\n\
    \n    int point_vertex(int point) const {\n        assert_point(point);\n    \
    \    return point;\n    }\n\n    int add_vertex() {\n        return _graph.add_vertex();\n\
    \    }\n\n    Graph<T>& graph() {\n        return _graph;\n    }\n\n    const\
    \ Graph<T>& graph() const {\n        return _graph;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ from_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, true, result);\n        return result;\n    }\n\n    std::vector<RangeEdgeNode>\
    \ to_range_nodes(int left, int right) const {\n        assert_range(left, right);\n\
    \        std::vector<RangeEdgeNode> result;\n        if (left != right) collect(1,\
    \ left, right, false, result);\n        return result;\n    }\n\n    int add_point_to_point(int\
    \ from, int to, T cost) {\n        assert_point(from);\n        assert_point(to);\n\
    \        return _graph.add_directed_edge(from, to, cost);\n    }\n\n    void add_point_to_range(int\
    \ from, int left, int right, T cost) {\n        assert_point(from);\n        for\
    \ (const auto& node : to_range_nodes(left, right)) {\n            _graph.add_directed_edge(from,\
    \ node.vertex, cost);\n        }\n    }\n\n    void add_range_to_point(int left,\
    \ int right, int to, T cost) {\n        assert_point(to);\n        for (const\
    \ auto& node : from_range_nodes(left, right)) {\n            _graph.add_directed_edge(node.vertex,\
    \ to, cost);\n        }\n    }\n\n    int add_range_to_range(int from_left, int\
    \ from_right, int to_left, int to_right,\n                           T cost) {\n\
    \        assert_range(from_left, from_right);\n        assert_range(to_left, to_right);\n\
    \        if (from_left == from_right || to_left == to_right) return -1;\n\n  \
    \      int auxiliary = add_vertex();\n        for (const auto& node : from_range_nodes(from_left,\
    \ from_right)) {\n            _graph.add_directed_edge(node.vertex, auxiliary,\
    \ cost);\n        }\n        for (const auto& node : to_range_nodes(to_left, to_right))\
    \ {\n            _graph.add_directed_edge(auxiliary, node.vertex, T());\n    \
    \    }\n        return auxiliary;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/undirected.hpp\"\n\n\n\n#line 1 \"graph/bipartite.hpp\"\
    \n\n\n\n#line 8 \"graph/bipartite.hpp\"\n\n#line 10 \"graph/bipartite.hpp\"\n\n\
    namespace m1une {\nnamespace graph {\n\nstruct BipartiteResult {\n    bool is_bipartite;\n\
    \    std::vector<int> color;\n    std::vector<int> left_vertices;\n    std::vector<int>\
    \ right_vertices;\n    std::vector<int> left_id;\n    std::vector<int> right_id;\n\
    };\n\ntemplate <class T>\nBipartiteResult bipartite(const Graph<T>& g) {\n   \
    \ int n = g.size();\n    BipartiteResult result;\n    result.is_bipartite = true;\n\
    \    result.color.assign(n, -1);\n    result.left_id.assign(n, -1);\n    result.right_id.assign(n,\
    \ -1);\n\n    std::vector<std::vector<int>> adjacency(n);\n    for (const auto&\
    \ e : g.edges()) {\n        adjacency[e.from].push_back(e.to);\n        adjacency[e.to].push_back(e.from);\n\
    \    }\n\n    std::queue<int> que;\n    for (int s = 0; s < n; s++) {\n      \
    \  if (result.color[s] != -1) continue;\n        result.color[s] = 0;\n      \
    \  que.push(s);\n        while (!que.empty()) {\n            int v = que.front();\n\
    \            que.pop();\n            for (int to : adjacency[v]) {\n         \
    \       if (result.color[to] == -1) {\n                    result.color[to] =\
    \ result.color[v] ^ 1;\n                    que.push(to);\n                } else\
    \ if (result.color[to] == result.color[v]) {\n                    result.is_bipartite\
    \ = false;\n                    return result;\n                }\n          \
    \  }\n        }\n    }\n\n    for (int v = 0; v < n; v++) {\n        if (result.color[v]\
    \ == 0) {\n            result.left_id[v] = int(result.left_vertices.size());\n\
    \            result.left_vertices.push_back(v);\n        } else {\n          \
    \  result.right_id[v] = int(result.right_vertices.size());\n            result.right_vertices.push_back(v);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nbool is_bipartite(const\
    \ Graph<T>& g) {\n    return bipartite(g).is_bipartite;\n}\n\nstruct BipartiteVertexSet\
    \ {\n    std::vector<int> left;\n    std::vector<int> right;\n\n    int size()\
    \ const {\n        return int(left.size() + right.size());\n    }\n};\n\nstruct\
    \ BipartiteMatching {\n    struct Edge {\n        int left;\n        int right;\n\
    \        int id;\n        bool alive;\n    };\n\n    struct Pair {\n        int\
    \ left;\n        int right;\n        int edge_id;\n    };\n\n   private:\n   \
    \ int _left_size;\n    int _right_size;\n    std::vector<Edge> _edges;\n    std::vector<std::vector<int>>\
    \ _adj;\n    std::vector<std::vector<int>> _radj;\n    std::vector<int> _left_match;\n\
    \    std::vector<int> _right_match;\n    std::vector<int> _left_match_edge;\n\
    \    std::vector<int> _right_match_edge;\n    bool _calculated;\n\n    void invalidate()\
    \ {\n        _calculated = false;\n    }\n\n    void ensure_matching() {\n   \
    \     if (!_calculated) max_matching();\n    }\n\n   public:\n    BipartiteMatching()\
    \ : BipartiteMatching(0, 0) {}\n\n    BipartiteMatching(int left_size, int right_size)\n\
    \        : _left_size(left_size),\n          _right_size(right_size),\n      \
    \    _adj(left_size),\n          _radj(right_size),\n          _left_match(left_size,\
    \ -1),\n          _right_match(right_size, -1),\n          _left_match_edge(left_size,\
    \ -1),\n          _right_match_edge(right_size, -1),\n          _calculated(false)\
    \ {\n        assert(0 <= left_size);\n        assert(0 <= right_size);\n    }\n\
    \n    int left_size() const {\n        return _left_size;\n    }\n\n    int right_size()\
    \ const {\n        return _right_size;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int add_edge(int left, int right)\
    \ {\n        assert(0 <= left && left < _left_size);\n        assert(0 <= right\
    \ && right < _right_size);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{left,\
    \ right, id, true});\n        _adj[left].push_back(id);\n        _radj[right].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        _left_match.assign(_left_size,\
    \ -1);\n        _right_match.assign(_right_size, -1);\n        _left_match_edge.assign(_left_size,\
    \ -1);\n        _right_match_edge.assign(_right_size, -1);\n\n        std::vector<int>\
    \ dist(_left_size);\n        auto bfs = [&]() -> bool {\n            std::queue<int>\
    \ que;\n            bool found = false;\n            for (int l = 0; l < _left_size;\
    \ l++) {\n                if (_left_match[l] == -1) {\n                    dist[l]\
    \ = 0;\n                    que.push(l);\n                } else {\n         \
    \           dist[l] = -1;\n                }\n            }\n\n            while\
    \ (!que.empty()) {\n                int l = que.front();\n                que.pop();\n\
    \                for (int id : _adj[l]) {\n                    const auto& e =\
    \ _edges[id];\n                    if (!e.alive) continue;\n                 \
    \   int next_left = _right_match[e.right];\n                    if (next_left\
    \ == -1) {\n                        found = true;\n                    } else\
    \ if (dist[next_left] == -1) {\n                        dist[next_left] = dist[l]\
    \ + 1;\n                        que.push(next_left);\n                    }\n\
    \                }\n            }\n            return found;\n        };\n\n \
    \       auto dfs = [&](auto self, int l) -> bool {\n            for (int id :\
    \ _adj[l]) {\n                const auto& e = _edges[id];\n                if\
    \ (!e.alive) continue;\n                int next_left = _right_match[e.right];\n\
    \                if (next_left != -1 && (dist[next_left] != dist[l] + 1 || !self(self,\
    \ next_left))) {\n                    continue;\n                }\n         \
    \       _left_match[l] = e.right;\n                _right_match[e.right] = l;\n\
    \                _left_match_edge[l] = id;\n                _right_match_edge[e.right]\
    \ = id;\n                return true;\n            }\n            dist[l] = -1;\n\
    \            return false;\n        };\n\n        int result = 0;\n        while\
    \ (bfs()) {\n            for (int l = 0; l < _left_size; l++) {\n            \
    \    if (_left_match[l] == -1 && dfs(dfs, l)) result++;\n            }\n     \
    \   }\n\n        _calculated = true;\n        return result;\n    }\n\n    int\
    \ matching_size() {\n        ensure_matching();\n        int result = 0;\n   \
    \     for (int right : _left_match) {\n            if (right != -1) result++;\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> left_match()\
    \ {\n        ensure_matching();\n        return _left_match;\n    }\n\n    std::vector<int>\
    \ right_match() {\n        ensure_matching();\n        return _right_match;\n\
    \    }\n\n    std::vector<Pair> matching() {\n        ensure_matching();\n   \
    \     std::vector<Pair> result;\n        for (int l = 0; l < _left_size; l++)\
    \ {\n            if (_left_match[l] != -1) result.push_back(Pair{l, _left_match[l],\
    \ _left_match_edge[l]});\n        }\n        return result;\n    }\n\n    BipartiteVertexSet\
    \ minimum_vertex_cover() {\n        ensure_matching();\n\n        std::vector<char>\
    \ visited_left(_left_size, false), visited_right(_right_size, false);\n      \
    \  std::queue<int> que;\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match[l] == -1) {\n                visited_left[l] = true;\n\
    \                que.push(l);\n            }\n        }\n\n        while (!que.empty())\
    \ {\n            int l = que.front();\n            que.pop();\n            for\
    \ (int id : _adj[l]) {\n                const auto& e = _edges[id];\n        \
    \        if (!e.alive || _left_match_edge[l] == id || visited_right[e.right])\
    \ continue;\n                visited_right[e.right] = true;\n                int\
    \ next_left = _right_match[e.right];\n                if (next_left != -1 && !visited_left[next_left])\
    \ {\n                    visited_left[next_left] = true;\n                   \
    \ que.push(next_left);\n                }\n            }\n        }\n\n      \
    \  BipartiteVertexSet result;\n        for (int l = 0; l < _left_size; l++) {\n\
    \            if (!visited_left[l]) result.left.push_back(l);\n        }\n    \
    \    for (int r = 0; r < _right_size; r++) {\n            if (visited_right[r])\
    \ result.right.push_back(r);\n        }\n        return result;\n    }\n\n   \
    \ BipartiteVertexSet maximum_independent_set() {\n        auto cover = minimum_vertex_cover();\n\
    \        std::vector<char> in_left_cover(_left_size, false), in_right_cover(_right_size,\
    \ false);\n        for (int l : cover.left) in_left_cover[l] = true;\n       \
    \ for (int r : cover.right) in_right_cover[r] = true;\n\n        BipartiteVertexSet\
    \ result;\n        for (int l = 0; l < _left_size; l++) {\n            if (!in_left_cover[l])\
    \ result.left.push_back(l);\n        }\n        for (int r = 0; r < _right_size;\
    \ r++) {\n            if (!in_right_cover[r]) result.right.push_back(r);\n   \
    \     }\n        return result;\n    }\n\n    std::optional<std::vector<int>>\
    \ minimum_edge_cover() {\n        ensure_matching();\n\n        std::vector<int>\
    \ result;\n        std::vector<char> covered_left(_left_size, false), covered_right(_right_size,\
    \ false);\n        std::vector<char> used_edge(_edges.size(), false);\n\n    \
    \    auto use_edge = [&](int id) {\n            if (used_edge[id]) return;\n \
    \           used_edge[id] = true;\n            result.push_back(id);\n       \
    \     covered_left[_edges[id].left] = true;\n            covered_right[_edges[id].right]\
    \ = true;\n        };\n\n        for (int l = 0; l < _left_size; l++) {\n    \
    \        if (_left_match_edge[l] != -1) use_edge(_left_match_edge[l]);\n     \
    \   }\n\n        for (int l = 0; l < _left_size; l++) {\n            if (covered_left[l])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[l])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      for (int r = 0; r < _right_size; r++) {\n            if (covered_right[r])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _radj[r])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct BipartiteMatchingGraph {\n    BipartiteResult\
    \ parts;\n    BipartiteMatching matching;\n    std::vector<int> original_edge_id;\n\
    \n    int left_vertex(int left) const {\n        assert(0 <= left && left < int(parts.left_vertices.size()));\n\
    \        return parts.left_vertices[left];\n    }\n\n    int right_vertex(int\
    \ right) const {\n        assert(0 <= right && right < int(parts.right_vertices.size()));\n\
    \        return parts.right_vertices[right];\n    }\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    std::optional<BipartiteMatchingGraph> make_bipartite_matching(const Graph<T>&\
    \ g) {\n    auto parts = bipartite(g);\n    if (!parts.is_bipartite) return std::nullopt;\n\
    \n    BipartiteMatchingGraph result;\n    result.parts = parts;\n    result.matching\
    \ = BipartiteMatching(int(parts.left_vertices.size()), int(parts.right_vertices.size()));\n\
    \n    for (const auto& e : g.edges()) {\n        int left, right;\n        if\
    \ (parts.color[e.from] == 0) {\n            left = parts.left_id[e.from];\n  \
    \          right = parts.right_id[e.to];\n        } else {\n            left =\
    \ parts.left_id[e.to];\n            right = parts.right_id[e.from];\n        }\n\
    \        int id = result.matching.add_edge(left, right);\n        if (int(result.original_edge_id.size())\
    \ <= id) result.original_edge_id.resize(id + 1);\n        result.original_edge_id[id]\
    \ = e.id;\n    }\n\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/connected_components.hpp\"\n\n\n\n#line 6 \"graph/connected_components.hpp\"\
    \n\n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#line 5 \"ds/dsu/dsu.hpp\"\n#include <numeric>\n\
    #line 7 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu\
    \ {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent of i if\
    \ it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the\
    \ size of the group.\n    std::vector<int> parent_or_size;\n\n   public:\n   \
    \ Dsu() : _n(0) {}\n    explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\
    \n    // Merges the group containing 'a' with the group containing 'b'.\n    //\
    \ Returns the leader of the merged group.\n    int merge(int a, int b) {\n   \
    \     int x = leader(a), y = leader(b);\n        if (x == y) return x;\n     \
    \   // Union by size\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return x;\n    }\n\n    // Returns true if 'a' and 'b' belong\
    \ to the same group.\n    bool same(int a, int b) {\n        return leader(a)\
    \ == leader(b);\n    }\n\n    // Returns the leader (representative) of the group\
    \ containing 'a'.\n    int leader(int a) {\n        if (parent_or_size[a] < 0)\
    \ return a;\n        // Path compression\n        return parent_or_size[a] = leader(parent_or_size[a]);\n\
    \    }\n\n    // Returns the size of the group containing 'a'.\n    int size(int\
    \ a) {\n        return -parent_or_size[leader(a)];\n    }\n\n    // Returns a\
    \ list of all groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct ConnectedComponents {\n    int count;\n\
    \    std::vector<int> comp;\n    std::vector<std::vector<int>> groups;\n\n   \
    \ bool same(int u, int v) const {\n        assert(0 <= u && u < int(comp.size()));\n\
    \        assert(0 <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n\
    \    }\n};\n\ntemplate <class T>\nConnectedComponents connected_components(const\
    \ Graph<T>& g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const\
    \ auto& e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 1 \"graph/general_matching.hpp\"\n\n\n\n#line 9 \"graph/general_matching.hpp\"\
    \n\n#line 11 \"graph/general_matching.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct GeneralMatching {\n    struct Edge {\n        int from;\n      \
    \  int to;\n        int id;\n        bool alive;\n\n        int other(int v) const\
    \ {\n            assert(v == from || v == to);\n            return from ^ to ^\
    \ v;\n        }\n    };\n\n    struct Pair {\n        int from;\n        int to;\n\
    \        int edge_id;\n    };\n\n   private:\n    int _n;\n    std::vector<Edge>\
    \ _edges;\n    std::vector<std::vector<int>> _adj;\n    std::vector<int> _mate;\n\
    \    std::vector<int> _mate_edge;\n    bool _calculated;\n\n    void invalidate()\
    \ {\n        _calculated = false;\n    }\n\n    void ensure_matching() {\n   \
    \     if (!_calculated) max_matching();\n    }\n\n    bool is_matched_edge(int\
    \ id) const {\n        const auto& e = _edges[id];\n        return _mate[e.from]\
    \ == e.to && _mate_edge[e.from] == id;\n    }\n\n    enum MatchingLabel : char\
    \ {\n        even_label,\n        odd_label,\n        unlabeled\n    };\n\n  \
    \  struct MutablePartition {\n        std::vector<int> parent;\n        std::vector<int>\
    \ rank;\n        std::vector<int> representative;\n\n        MutablePartition()\
    \ = default;\n\n        explicit MutablePartition(int n) {\n            reset(n);\n\
    \        }\n\n        void reset(int n) {\n            parent.resize(n);\n   \
    \         rank.assign(n, 0);\n            representative.resize(n);\n        \
    \    for (int i = 0; i < n; i++) {\n                parent[i] = i;\n         \
    \       representative[i] = i;\n            }\n        }\n\n        int root(int\
    \ v) {\n            if (parent[v] == v) return v;\n            return parent[v]\
    \ = root(parent[v]);\n        }\n\n        int operator()(int v) {\n         \
    \   return representative[root(v)];\n        }\n\n        void unite(int a, int\
    \ b) {\n            int ra = root(a);\n            int rb = root(b);\n       \
    \     if (ra == rb) return;\n            if (rank[ra] < rank[rb]) std::swap(ra,\
    \ rb);\n            parent[rb] = ra;\n            if (rank[ra] == rank[rb]) rank[ra]++;\n\
    \        }\n\n        void make_rep(int v) {\n            representative[root(v)]\
    \ = v;\n        }\n    };\n\n    struct EdgeBucketQueue {\n        std::vector<std::vector<int>>\
    \ bucket;\n        std::vector<int> head;\n\n        void reset(int n) {\n   \
    \         bucket.assign(n + 3, {});\n            head.assign(n + 3, 0);\n    \
    \    }\n\n        void insert(int edge_id, int key) {\n            if (key < 0\
    \ || int(bucket.size()) <= key) return;\n            bucket[key].push_back(edge_id);\n\
    \        }\n\n        int pop(int key) {\n            if (key < 0 || int(bucket.size())\
    \ <= key) return -1;\n            if (head[key] == int(bucket[key].size())) return\
    \ -1;\n            return bucket[key][head[key]++];\n        }\n    };\n\n   \
    \ struct NewMatchingPair {\n        int from;\n        int to;\n        int edge_id;\n\
    \    };\n\n    // General-graph shortest augmenting path phase solver.\n    struct\
    \ MicaliVaziraniSolver {\n        GeneralMatching& graph;\n        int n;\n  \
    \      int matching_size;\n        int delta;\n        int visit_token;\n    \
    \    int even_time_token;\n        MutablePartition base;\n        MutablePartition\
    \ delayed_base;\n        EdgeBucketQueue queue;\n        std::vector<MatchingLabel>\
    \ label;\n        std::vector<MatchingLabel> h_label;\n        std::vector<int>\
    \ parent;\n        std::vector<int> parent_edge;\n        std::vector<int> source_bridge;\n\
    \        std::vector<int> target_bridge;\n        std::vector<int> bridge_edge;\n\
    \        std::vector<int> lcp;\n        std::vector<int> path_mark_1;\n      \
    \  std::vector<int> path_mark_2;\n        std::vector<int> restore_vertex;\n \
    \       std::vector<int> restore_value;\n        std::vector<int> rep;\n     \
    \   std::vector<int> h_mate;\n        std::vector<char> is_h_edge;\n        std::vector<std::vector<int>>\
    \ contracted_into;\n        std::vector<int> h_parent_edge;\n        std::vector<int>\
    \ h_even_time;\n        std::vector<int> h_bridge_edge;\n        std::vector<int>\
    \ h_bridge_dir;\n\n        explicit MicaliVaziraniSolver(GeneralMatching& graph_)\n\
    \            : graph(graph_),\n              n(graph_._n),\n              matching_size(0),\n\
    \              delta(0),\n              visit_token(0),\n              even_time_token(0),\n\
    \              base(n),\n              delayed_base(n),\n              label(n,\
    \ unlabeled),\n              h_label(n, unlabeled),\n              parent(n, -1),\n\
    \              parent_edge(n, -1),\n              source_bridge(n, -1),\n    \
    \          target_bridge(n, -1),\n              bridge_edge(n, -1),\n        \
    \      lcp(n, 0),\n              path_mark_1(n, 0),\n              path_mark_2(n,\
    \ 0),\n              rep(n, -1),\n              h_mate(n, -1),\n             \
    \ is_h_edge(graph_._edges.size(), false),\n              contracted_into(n),\n\
    \              h_parent_edge(n, -1),\n              h_even_time(n, 0),\n     \
    \         h_bridge_edge(n, -1),\n              h_bridge_dir(n, 0) {}\n\n     \
    \   bool active(int edge_id) const {\n            return graph._edges[edge_id].alive;\n\
    \        }\n\n        int other(int edge_id, int v) const {\n            return\
    \ graph._edges[edge_id].other(v);\n        }\n\n        int edge_weight(int edge_id)\
    \ const {\n            return graph.is_matched_edge(edge_id) ? 2 : 0;\n      \
    \  }\n\n        void set_match(int edge_id) {\n            const auto& e = graph._edges[edge_id];\n\
    \            graph._mate[e.from] = e.to;\n            graph._mate[e.to] = e.from;\n\
    \            graph._mate_edge[e.from] = edge_id;\n            graph._mate_edge[e.to]\
    \ = edge_id;\n        }\n\n        void initialize_greedy_matching() {\n     \
    \       graph._mate.assign(n, -1);\n            graph._mate_edge.assign(n, -1);\n\
    \            matching_size = 0;\n            for (const auto& e : graph._edges)\
    \ {\n                if (!e.alive) continue;\n                if (graph._mate[e.from]\
    \ != -1 || graph._mate[e.to] != -1) continue;\n                set_match(e.id);\n\
    \                matching_size++;\n            }\n        }\n\n        void scan_edge(int\
    \ edge_id, int from) {\n            if (!active(edge_id)) return;\n          \
    \  int to = other(edge_id, from);\n            if (to == from || graph._mate[to]\
    \ == from || label[base(to)] == odd_label) return;\n            if (label[to]\
    \ == unlabeled) {\n                queue.insert(edge_id, lcp[from] + 2);\n   \
    \         } else {\n                queue.insert(edge_id, (lcp[from] + lcp[to])\
    \ / 2 + 1);\n            }\n        }\n\n        void shrink_path(int blossom_base,\
    \ int x, int y, int edge_id,\n                         std::vector<std::pair<int,\
    \ int>>& delayed_unions) {\n            int v = base(x);\n            while (v\
    \ != blossom_base) {\n                base.unite(v, blossom_base);\n         \
    \       delayed_unions.push_back({v, blossom_base});\n\n                v = graph._mate[v];\n\
    \                assert(v != -1);\n                base.unite(v, blossom_base);\n\
    \                delayed_unions.push_back({v, blossom_base});\n              \
    \  base.make_rep(blossom_base);\n\n                source_bridge[v] = x;\n   \
    \             target_bridge[v] = y;\n                bridge_edge[v] = edge_id;\n\
    \                restore_vertex.push_back(v);\n                restore_value.push_back(lcp[v]);\n\
    \                lcp[v] = lcp[x] + lcp[y] - lcp[graph._mate[v]] + 2;\n\n     \
    \           for (int id : graph._adj[v]) scan_edge(id, v);\n                assert(parent[v]\
    \ != -1);\n                v = base(parent[v]);\n            }\n            delayed_unions.push_back({blossom_base,\
    \ blossom_base});\n        }\n\n        void build_phase_graph() {\n         \
    \   std::fill(h_mate.begin(), h_mate.end(), -1);\n            std::fill(is_h_edge.begin(),\
    \ is_h_edge.end(), false);\n            for (auto& vertices : contracted_into)\
    \ vertices.clear();\n\n            for (int v = 0; v < n; v++) contracted_into[delayed_base(v)].push_back(v);\n\
    \n            for (const auto& e : graph._edges) {\n                if (!e.alive)\
    \ continue;\n                int u = e.from;\n                int v = e.to;\n\
    \                int uh = delayed_base(u);\n                int vh = delayed_base(v);\n\
    \                if (uh == vh) continue;\n                if (label[uh] == odd_label\
    \ && label[vh] == odd_label) continue;\n\n                int w = edge_weight(e.id);\n\
    \                bool even_odd =\n                    (label[uh] == even_label\
    \ && label[vh] == odd_label && lcp[v] == lcp[u] + 1 - w) ||\n                \
    \    (label[vh] == even_label && label[uh] == odd_label && lcp[u] == lcp[v] +\
    \ 1 - w);\n                bool unlabeled_unlabeled = label[uh] == unlabeled &&\
    \ label[vh] == unlabeled && w == 2;\n                bool even_unlabeled =\n \
    \                   (label[uh] == even_label && label[vh] == unlabeled && lcp[u]\
    \ == delta - 2) ||\n                    (label[vh] == even_label && label[uh]\
    \ == unlabeled && lcp[v] == delta - 2);\n                bool even_even = label[uh]\
    \ == even_label && label[vh] == even_label;\n                bool tight_even_even\
    \ = even_even && lcp[u] + lcp[v] == 2 * delta + w - 2;\n\n                if (even_odd\
    \ || unlabeled_unlabeled || even_unlabeled || tight_even_even) {\n           \
    \         is_h_edge[e.id] = true;\n                    if (w == 2) {\n       \
    \                 h_mate[uh] = vh;\n                        h_mate[vh] = uh;\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  bool phase_one() {\n            delta = 0;\n            base.reset(n);\n  \
    \          delayed_base.reset(n);\n            queue.reset(n);\n            std::fill(label.begin(),\
    \ label.end(), unlabeled);\n            std::fill(parent.begin(), parent.end(),\
    \ -1);\n            std::fill(parent_edge.begin(), parent_edge.end(), -1);\n \
    \           std::fill(source_bridge.begin(), source_bridge.end(), -1);\n     \
    \       std::fill(target_bridge.begin(), target_bridge.end(), -1);\n         \
    \   std::fill(bridge_edge.begin(), bridge_edge.end(), -1);\n            std::fill(lcp.begin(),\
    \ lcp.end(), 0);\n\n            for (int v = 0; v < n; v++) {\n              \
    \  if (graph._mate[v] == -1) label[v] = even_label;\n            }\n         \
    \   for (int v = 0; v < n; v++) {\n                if (label[v] != even_label)\
    \ continue;\n                for (int id : graph._adj[v]) scan_edge(id, v);\n\
    \            }\n\n            std::vector<std::pair<int, int>> delayed_unions;\n\
    \            while (delta <= n + 1) {\n                restore_vertex.clear();\n\
    \                restore_value.clear();\n\n                while (true) {\n  \
    \                  int edge_id = queue.pop(delta);\n                    if (edge_id\
    \ == -1) break;\n                    if (!active(edge_id)) continue;\n\n     \
    \               int x = graph._edges[edge_id].from;\n                    int y\
    \ = graph._edges[edge_id].to;\n                    if (label[base(x)] != even_label)\
    \ std::swap(x, y);\n                    if (label[base(x)] != even_label) continue;\n\
    \                    if (graph._mate[x] == y || base(x) == base(y) || label[base(y)]\
    \ == odd_label) continue;\n\n                    if (label[base(y)] == unlabeled)\
    \ {\n                        int z = graph._mate[y];\n                       \
    \ assert(z != -1);\n                        lcp[y] = lcp[x] + 1;\n           \
    \             lcp[z] = lcp[x] + 2;\n                        parent[y] = x;\n \
    \                       parent_edge[y] = edge_id;\n                        parent[z]\
    \ = y;\n                        parent_edge[z] = graph._mate_edge[z];\n      \
    \                  label[y] = odd_label;\n                        label[z] = even_label;\n\
    \                        for (int id : graph._adj[z]) scan_edge(id, z);\n    \
    \                    continue;\n                    }\n\n                    if\
    \ (label[base(y)] != even_label || lcp[x] + lcp[y] != 2 * delta - 2) continue;\n\
    \n                    ++visit_token;\n                    int hx = base(x);\n\
    \                    int hy = base(y);\n                    path_mark_1[hx] =\
    \ visit_token;\n                    path_mark_2[hy] = visit_token;\n         \
    \           while (path_mark_1[hy] != visit_token && path_mark_2[hx] != visit_token\
    \ &&\n                           (graph._mate[hx] != -1 || graph._mate[hy] !=\
    \ -1)) {\n                        if (graph._mate[hx] != -1) {\n             \
    \               assert(parent[graph._mate[hx]] != -1);\n                     \
    \       hx = base(parent[graph._mate[hx]]);\n                            path_mark_1[hx]\
    \ = visit_token;\n                        }\n                        if (graph._mate[hy]\
    \ != -1) {\n                            assert(parent[graph._mate[hy]] != -1);\n\
    \                            hy = base(parent[graph._mate[hy]]);\n           \
    \                 path_mark_2[hy] = visit_token;\n                        }\n\
    \                    }\n\n                    if (path_mark_1[hy] == visit_token\
    \ || path_mark_2[hx] == visit_token) {\n                        int blossom_base\
    \ = path_mark_1[hy] == visit_token ? hy : hx;\n                        shrink_path(blossom_base,\
    \ x, y, edge_id, delayed_unions);\n                        shrink_path(blossom_base,\
    \ y, x, edge_id, delayed_unions);\n                    } else {\n            \
    \            for (int i = int(restore_vertex.size()) - 1; i >= 0; i--) {\n   \
    \                         lcp[restore_vertex[i]] = restore_value[i];\n       \
    \                 }\n                        build_phase_graph();\n          \
    \              return true;\n                    }\n                }\n\n    \
    \            for (auto [a, b] : delayed_unions) {\n                    if (a ==\
    \ b) {\n                        delayed_base.make_rep(a);\n                  \
    \  } else {\n                        delayed_base.unite(a, b);\n             \
    \       }\n                }\n                delayed_unions.clear();\n      \
    \          delta++;\n            }\n            return false;\n        }\n\n \
    \       int next_h_vertex_through_edge(int edge_id, int current_h) const {\n \
    \           const auto& e = graph._edges[edge_id];\n            return rep[rep[e.from]\
    \ == current_h ? e.to : e.from];\n        }\n\n        int find_path_in_h(int\
    \ h_vertex) {\n            for (int v : contracted_into[h_vertex]) {\n       \
    \         for (int edge_id : graph._adj[v]) {\n                    if (!is_h_edge[edge_id])\
    \ continue;\n                    int uh = rep[other(edge_id, v)];\n          \
    \          if (h_mate[h_vertex] == uh) continue;\n\n                    if (h_label[uh]\
    \ == unlabeled) {\n                        int mate_uh = h_mate[uh];\n       \
    \                 h_label[uh] = odd_label;\n                        h_parent_edge[uh]\
    \ = edge_id;\n                        if (mate_uh == -1) return uh;\n\n      \
    \                  h_label[mate_uh] = even_label;\n                        h_even_time[mate_uh]\
    \ = even_time_token++;\n                        int found = find_path_in_h(mate_uh);\n\
    \                        if (found != -1) return found;\n                    }\
    \ else {\n                        int bh = delayed_base(h_vertex);\n         \
    \               int zh = delayed_base(uh);\n                        if (h_even_time[bh]\
    \ >= h_even_time[zh]) continue;\n\n                        std::vector<int> blossom_path;\n\
    \                        std::vector<int> blossom_vertices;\n                \
    \        while (zh != bh) {\n                            blossom_vertices.push_back(zh);\n\
    \                            zh = h_mate[zh];\n                            assert(zh\
    \ != -1);\n                            blossom_vertices.push_back(zh);\n     \
    \                       blossom_path.push_back(zh);\n                        \
    \    assert(h_parent_edge[zh] != -1);\n                            zh = delayed_base(next_h_vertex_through_edge(h_parent_edge[zh],\
    \ zh));\n                        }\n\n                        for (int x : blossom_vertices)\
    \ delayed_base.unite(x, bh);\n                        delayed_base.make_rep(bh);\n\
    \n                        std::reverse(blossom_path.begin(), blossom_path.end());\n\
    \                        for (int x : blossom_path) {\n                      \
    \      h_bridge_edge[x] = edge_id;\n                            h_bridge_dir[x]\
    \ = graph._edges[edge_id].to == v ? 1 : -1;\n                        }\n     \
    \                   for (int x : blossom_path) {\n                           \
    \ int found = find_path_in_h(x);\n                            if (found != -1)\
    \ return found;\n                        }\n                    }\n          \
    \      }\n            }\n            return -1;\n        }\n\n        void collect_path_in_h(std::vector<int>&\
    \ path, int from_h, int to_h) {\n            if (from_h == to_h) return;\n   \
    \         if (h_label[from_h] == even_label) {\n                int mate_from\
    \ = h_mate[from_h];\n                assert(mate_from != -1);\n              \
    \  int edge_id = h_parent_edge[mate_from];\n                assert(edge_id !=\
    \ -1);\n                path.push_back(edge_id);\n                collect_path_in_h(path,\
    \ next_h_vertex_through_edge(edge_id, mate_from), to_h);\n            } else {\n\
    \                int edge_id = h_bridge_edge[from_h];\n                assert(edge_id\
    \ != -1);\n                const auto& e = graph._edges[edge_id];\n          \
    \      int first = rep[h_bridge_dir[from_h] == 1 ? e.from : e.to];\n         \
    \       int second = rep[h_bridge_dir[from_h] == 1 ? e.to : e.from];\n       \
    \         collect_path_in_h(path, first, rep[h_mate[from_h]]);\n             \
    \   path.push_back(edge_id);\n                collect_path_in_h(path, second,\
    \ to_h);\n            }\n        }\n\n        void add_new_pair(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to, int edge_id) const {\n            const auto& e = graph._edges[edge_id];\n\
    \            assert(e.alive);\n            assert((e.from == from && e.to == to)\
    \ || (e.from == to && e.to == from));\n            pairs.push_back(NewMatchingPair{from,\
    \ to, edge_id});\n        }\n\n        void collect_path_in_graph(std::vector<NewMatchingPair>&\
    \ pairs, int from, int to) {\n            if (from == to) return;\n          \
    \  if (label[from] == even_label) {\n                int mate_from = graph._mate[from];\n\
    \                assert(mate_from != -1);\n                int parent_of_mate\
    \ = parent[mate_from];\n                int edge_id = parent_edge[mate_from];\n\
    \                assert(parent_of_mate != -1 && edge_id != -1);\n            \
    \    add_new_pair(pairs, mate_from, parent_of_mate, edge_id);\n              \
    \  collect_path_in_graph(pairs, parent_of_mate, to);\n            } else {\n \
    \               assert(source_bridge[from] != -1 && target_bridge[from] != -1\
    \ && bridge_edge[from] != -1);\n                collect_path_in_graph(pairs, source_bridge[from],\
    \ graph._mate[from]);\n                add_new_pair(pairs, source_bridge[from],\
    \ target_bridge[from], bridge_edge[from]);\n                collect_path_in_graph(pairs,\
    \ target_bridge[from], to);\n            }\n        }\n\n        void augment_path(const\
    \ std::vector<int>& h_path) {\n            std::vector<NewMatchingPair> pairs;\n\
    \            for (int edge_id : h_path) {\n                const auto& e = graph._edges[edge_id];\n\
    \                add_new_pair(pairs, e.from, e.to, edge_id);\n               \
    \ collect_path_in_graph(pairs, e.from, rep[e.from]);\n                collect_path_in_graph(pairs,\
    \ e.to, rep[e.to]);\n            }\n\n            for (const auto& p : pairs)\
    \ {\n                if (graph._mate[p.from] != -1) {\n                    int\
    \ old = graph._mate[p.from];\n                    graph._mate[old] = -1;\n   \
    \                 graph._mate_edge[old] = -1;\n                }\n           \
    \     if (graph._mate[p.to] != -1) {\n                    int old = graph._mate[p.to];\n\
    \                    graph._mate[old] = -1;\n                    graph._mate_edge[old]\
    \ = -1;\n                }\n                graph._mate[p.from] = graph._mate[p.to]\
    \ = -1;\n                graph._mate_edge[p.from] = graph._mate_edge[p.to] = -1;\n\
    \            }\n            for (const auto& p : pairs) {\n                assert(graph._mate[p.from]\
    \ == -1 && graph._mate[p.to] == -1);\n                graph._mate[p.from] = p.to;\n\
    \                graph._mate[p.to] = p.from;\n                graph._mate_edge[p.from]\
    \ = p.edge_id;\n                graph._mate_edge[p.to] = p.edge_id;\n        \
    \    }\n            matching_size++;\n        }\n\n        void phase_two() {\n\
    \            std::fill(h_label.begin(), h_label.end(), unlabeled);\n         \
    \   std::fill(h_parent_edge.begin(), h_parent_edge.end(), -1);\n            std::fill(h_bridge_edge.begin(),\
    \ h_bridge_edge.end(), -1);\n            std::fill(h_bridge_dir.begin(), h_bridge_dir.end(),\
    \ 0);\n            for (int v = 0; v < n; v++) rep[v] = delayed_base(v);\n\n \
    \           std::vector<std::vector<int>> paths;\n            for (int h_vertex\
    \ = 0; h_vertex < n; h_vertex++) {\n                if (rep[h_vertex] != h_vertex)\
    \ continue;\n                if (h_label[h_vertex] != unlabeled || h_mate[h_vertex]\
    \ != -1) continue;\n\n                h_label[h_vertex] = even_label;\n      \
    \          h_even_time[h_vertex] = even_time_token++;\n                int free_h\
    \ = find_path_in_h(h_vertex);\n                if (free_h == -1) continue;\n\n\
    \                std::vector<int> path;\n                int edge_id = h_parent_edge[free_h];\n\
    \                assert(edge_id != -1);\n                path.push_back(edge_id);\n\
    \                collect_path_in_h(path, next_h_vertex_through_edge(edge_id, free_h),\
    \ h_vertex);\n                paths.push_back(path);\n            }\n\n      \
    \      assert(!paths.empty());\n            for (const auto& path : paths) augment_path(path);\n\
    \            for (auto& vertices : contracted_into) vertices.clear();\n      \
    \  }\n\n        int solve() {\n            initialize_greedy_matching();\n   \
    \         while (phase_one()) phase_two();\n            return matching_size;\n\
    \        }\n    };\n\n   public:\n    GeneralMatching() : GeneralMatching(0) {}\n\
    \n    explicit GeneralMatching(int n) : _n(n), _adj(n), _mate(n, -1), _mate_edge(n,\
    \ -1), _calculated(false) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_edges.size());\n    }\n\n    int add_edge(int from, int to) {\n\
    \        assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n\
    \        assert(from != to);\n        int id = int(_edges.size());\n        _edges.push_back(Edge{from,\
    \ to, id, true});\n        _adj[from].push_back(id);\n        _adj[to].push_back(id);\n\
    \        invalidate();\n        return id;\n    }\n\n    Edge get_edge(int i)\
    \ const {\n        assert(0 <= i && i < int(_edges.size()));\n        return _edges[i];\n\
    \    }\n\n    std::vector<Edge> edges(bool include_inactive = false) const {\n\
    \        std::vector<Edge> result;\n        result.reserve(_edges.size());\n \
    \       for (const auto& e : _edges) {\n            if (include_inactive || e.alive)\
    \ result.push_back(e);\n        }\n        return result;\n    }\n\n    void set_edge_alive(int\
    \ id, bool alive) {\n        assert(0 <= id && id < int(_edges.size()));\n   \
    \     _edges[id].alive = alive;\n        invalidate();\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < int(_edges.size()));\n        return\
    \ _edges[id].alive;\n    }\n\n    int max_matching() {\n        MicaliVaziraniSolver\
    \ solver(*this);\n        int result = solver.solve();\n\n        _calculated\
    \ = true;\n        return result;\n    }\n\n    int matching_size() {\n      \
    \  ensure_matching();\n        int result = 0;\n        for (int v = 0; v < _n;\
    \ v++) {\n            if (v < _mate[v]) result++;\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> mate() {\n        ensure_matching();\n        return\
    \ _mate;\n    }\n\n    std::vector<int> mate_edge() {\n        ensure_matching();\n\
    \        return _mate_edge;\n    }\n\n    std::vector<Pair> matching() {\n   \
    \     ensure_matching();\n        std::vector<Pair> result;\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (v < _mate[v]) result.push_back(Pair{v,\
    \ _mate[v], _mate_edge[v]});\n        }\n        return result;\n    }\n\n   \
    \ std::optional<std::vector<int>> minimum_edge_cover() {\n        ensure_matching();\n\
    \n        std::vector<int> result;\n        std::vector<char> covered(_n, false),\
    \ used_edge(_edges.size(), false);\n\n        auto use_edge = [&](int id) {\n\
    \            if (used_edge[id]) return;\n            used_edge[id] = true;\n \
    \           result.push_back(id);\n            covered[_edges[id].from] = true;\n\
    \            covered[_edges[id].to] = true;\n        };\n\n        for (int v\
    \ = 0; v < _n; v++) {\n            if (v < _mate[v]) use_edge(_mate_edge[v]);\n\
    \        }\n\n        for (int v = 0; v < _n; v++) {\n            if (covered[v])\
    \ continue;\n            int id = -1;\n            for (int edge_id : _adj[v])\
    \ {\n                if (_edges[edge_id].alive) {\n                    id = edge_id;\n\
    \                    break;\n                }\n            }\n            if\
    \ (id == -1) return std::nullopt;\n            use_edge(id);\n        }\n\n  \
    \      return result;\n    }\n};\n\nstruct GeneralMatchingGraph {\n    GeneralMatching\
    \ matching;\n    std::vector<int> original_edge_id;\n\n    int original_edge(int\
    \ edge_id) const {\n        assert(0 <= edge_id && edge_id < int(original_edge_id.size()));\n\
    \        return original_edge_id[edge_id];\n    }\n};\n\ntemplate <class T>\n\
    GeneralMatchingGraph make_general_matching(const Graph<T>& g) {\n    GeneralMatchingGraph\
    \ result;\n    result.matching = GeneralMatching(g.size());\n    for (const auto&\
    \ e : g.edges()) {\n        int id = result.matching.add_edge(e.from, e.to);\n\
    \        if (int(result.original_edge_id.size()) <= id) result.original_edge_id.resize(id\
    \ + 1);\n        result.original_edge_id[id] = e.id;\n    }\n    return result;\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/kruskal.hpp\"\
    \n\n\n\n#line 6 \"graph/kruskal.hpp\"\n\n#line 9 \"graph/kruskal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T>\nstruct MinimumSpanningForest\
    \ {\n    T cost;\n    std::vector<Edge<T>> edges;\n    int components;\n\n   \
    \ bool is_spanning_tree(int n) const {\n        return components <= 1 && int(edges.size())\
    \ == std::max(0, n - 1);\n    }\n};\n\ntemplate <class T>\nMinimumSpanningForest<T>\
    \ kruskal(const Graph<T>& g) {\n    int n = g.size();\n    auto edges = g.edges();\n\
    \    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {\n\
    \        return a.cost < b.cost;\n    });\n\n    m1une::ds::Dsu dsu(n);\n    MinimumSpanningForest<T>\
    \ result;\n    result.cost = T(0);\n    result.components = n;\n\n    for (const\
    \ auto& e : edges) {\n        if (dsu.same(e.from, e.to)) continue;\n        dsu.merge(e.from,\
    \ e.to);\n        result.cost += e.cost;\n        result.edges.push_back(e);\n\
    \        result.components--;\n    }\n\n    return result;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/lowlink.hpp\"\n\n\n\n#line\
    \ 6 \"graph/lowlink.hpp\"\n\n#line 8 \"graph/lowlink.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T>\nstruct LowLinkResult {\n    std::vector<int>\
    \ ord;\n    std::vector<int> low;\n    std::vector<int> articulation;\n    std::vector<Edge<T>>\
    \ bridges;\n    std::vector<int> bridge_ids;\n};\n\ntemplate <class T>\nLowLinkResult<T>\
    \ lowlink(const Graph<T>& g) {\n    int n = g.size();\n    LowLinkResult<T> result;\n\
    \    result.ord.assign(n, -1);\n    result.low.assign(n, -1);\n    int now = 0;\n\
    \n    auto dfs = [&](auto self, int v, int parent_edge) -> void {\n        result.ord[v]\
    \ = result.low[v] = now++;\n        int child_count = 0;\n        bool is_articulation\
    \ = false;\n\n        for (const auto& e : g[v]) {\n            if (!e.alive)\
    \ continue;\n            if (e.id == parent_edge) continue;\n            int to\
    \ = e.to;\n            if (result.ord[to] == -1) {\n                child_count++;\n\
    \                self(self, to, e.id);\n                result.low[v] = std::min(result.low[v],\
    \ result.low[to]);\n                if (parent_edge != -1 && result.ord[v] <=\
    \ result.low[to]) is_articulation = true;\n                if (result.ord[v] <\
    \ result.low[to]) {\n                    result.bridges.push_back(e);\n      \
    \              result.bridge_ids.push_back(e.id);\n                }\n       \
    \     } else {\n                result.low[v] = std::min(result.low[v], result.ord[to]);\n\
    \            }\n        }\n\n        if (parent_edge == -1 && child_count >= 2)\
    \ is_articulation = true;\n        if (is_articulation) result.articulation.push_back(v);\n\
    \    };\n\n    for (int v = 0; v < n; v++) {\n        if (result.ord[v] == -1)\
    \ dfs(dfs, v, -1);\n    }\n    std::sort(result.articulation.begin(), result.articulation.end());\n\
    \    std::sort(result.bridge_ids.begin(), result.bridge_ids.end());\n    return\
    \ result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"graph/maximum_clique.hpp\"\
    \n\n\n\n#line 7 \"graph/maximum_clique.hpp\"\n\n#line 9 \"graph/maximum_clique.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\nstruct MaximumCliqueResult {\n   \
    \ std::vector<int> vertices;\n\n    int size() const {\n        return int(vertices.size());\n\
    \    }\n\n    bool empty() const {\n        return vertices.empty();\n    }\n\
    };\n\nstruct MaximumIndependentSetResult {\n    std::vector<int> vertices;\n\n\
    \    int size() const {\n        return int(vertices.size());\n    }\n\n    bool\
    \ empty() const {\n        return vertices.empty();\n    }\n};\n\nstruct MinimumVertexCoverResult\
    \ {\n    std::vector<int> vertices;\n\n    int size() const {\n        return\
    \ int(vertices.size());\n    }\n\n    bool empty() const {\n        return vertices.empty();\n\
    \    }\n};\n\nnamespace detail {\n\nstruct MaximumIndependentSetBranching {\n\
    \    int n;\n    std::vector<std::vector<char>> adjacent;\n    std::vector<std::vector<int>>\
    \ graph;\n\n    explicit MaximumIndependentSetBranching(const std::vector<std::vector<char>>&\
    \ adjacent_)\n        : n(int(adjacent_.size())), adjacent(adjacent_), graph(n)\
    \ {\n        for (int v = 0; v < n; v++) {\n            for (int to = 0; to <\
    \ n; to++) {\n                if (adjacent[v][to]) graph[v].push_back(to);\n \
    \           }\n        }\n    }\n\n    std::vector<int> solve_path(const std::vector<int>&\
    \ order) const {\n        int m = int(order.size());\n        if (m == 0) return\
    \ {};\n\n        std::vector<int> dp0(m, 0), dp1(m, 0);\n        dp1[0] = 1;\n\
    \        for (int i = 1; i < m; i++) {\n            dp0[i] = std::max(dp0[i -\
    \ 1], dp1[i - 1]);\n            dp1[i] = dp0[i - 1] + 1;\n        }\n\n      \
    \  std::vector<int> result;\n        int state = (dp1[m - 1] > dp0[m - 1] ? 1\
    \ : 0);\n        for (int i = m - 1; i >= 0; i--) {\n            if (state ==\
    \ 1) {\n                result.push_back(order[i]);\n                state = 0;\n\
    \            } else if (i > 0) {\n                state = (dp1[i - 1] > dp0[i\
    \ - 1] ? 1 : 0);\n            }\n        }\n        return result;\n    }\n\n\
    \    std::vector<int> solve_cycle(const std::vector<int>& order) const {\n   \
    \     int m = int(order.size());\n        if (m == 0) return {};\n        if (m\
    \ == 1) return {order[0]};\n\n        std::vector<int> without_first(order.begin()\
    \ + 1, order.end());\n        auto result_without = solve_path(without_first);\n\
    \n        std::vector<int> result_with = {order[0]};\n        if (m >= 4) {\n\
    \            std::vector<int> middle(order.begin() + 2, order.end() - 1);\n  \
    \          auto middle_result = solve_path(middle);\n            result_with.insert(result_with.end(),\
    \ middle_result.begin(), middle_result.end());\n        }\n\n        return (result_with.size()\
    \ > result_without.size() ? result_with : result_without);\n    }\n\n    std::vector<int>\
    \ solve_degree_at_most_two(const std::vector<char>& active,\n                \
    \                              const std::vector<int>& degree) const {\n     \
    \   std::vector<int> result;\n        std::vector<char> visited(n, false);\n\n\
    \        for (int s = 0; s < n; s++) {\n            if (!active[s] || visited[s])\
    \ continue;\n\n            std::vector<int> component;\n            std::vector<int>\
    \ stack = {s};\n            visited[s] = true;\n            for (int it = 0; it\
    \ < int(stack.size()); it++) {\n                int v = stack[it];\n         \
    \       component.push_back(v);\n                for (int to : graph[v]) {\n \
    \                   if (!active[to] || visited[to]) continue;\n              \
    \      visited[to] = true;\n                    stack.push_back(to);\n       \
    \         }\n            }\n\n            if (component.size() == 1) {\n     \
    \           result.push_back(component[0]);\n                continue;\n     \
    \       }\n\n            int endpoint = -1;\n            for (int v : component)\
    \ {\n                if (degree[v] <= 1) {\n                    endpoint = v;\n\
    \                    break;\n                }\n            }\n\n            std::vector<int>\
    \ order;\n            if (endpoint != -1) {\n                int prev = -1, cur\
    \ = endpoint;\n                while (cur != -1) {\n                    order.push_back(cur);\n\
    \                    int next = -1;\n                    for (int to : graph[cur])\
    \ {\n                        if (active[to] && to != prev) {\n               \
    \             next = to;\n                            break;\n               \
    \         }\n                    }\n                    prev = cur;\n        \
    \            cur = next;\n                }\n                auto part = solve_path(order);\n\
    \                result.insert(result.end(), part.begin(), part.end());\n    \
    \        } else {\n                int start = component[0];\n               \
    \ int first = -1;\n                for (int to : graph[start]) {\n           \
    \         if (active[to]) {\n                        first = to;\n           \
    \             break;\n                    }\n                }\n             \
    \   assert(first != -1);\n\n                order.push_back(start);\n        \
    \        int prev = start, cur = first;\n                while (cur != start)\
    \ {\n                    order.push_back(cur);\n                    int next =\
    \ -1;\n                    for (int to : graph[cur]) {\n                     \
    \   if (active[to] && to != prev) {\n                            next = to;\n\
    \                            break;\n                        }\n             \
    \       }\n                    assert(next != -1);\n                    prev =\
    \ cur;\n                    cur = next;\n                }\n                auto\
    \ part = solve_cycle(order);\n                result.insert(result.end(), part.begin(),\
    \ part.end());\n            }\n        }\n\n        return result;\n    }\n\n\
    \    std::vector<int> solve(std::vector<char> active) const {\n        int active_count\
    \ = 0;\n        int max_degree = -1;\n        int branch_vertex = -1;\n      \
    \  std::vector<int> degree(n, 0);\n\n        for (int v = 0; v < n; v++) {\n \
    \           if (!active[v]) continue;\n            active_count++;\n         \
    \   for (int to : graph[v]) {\n                if (active[to]) degree[v]++;\n\
    \            }\n            if (degree[v] > max_degree) {\n                max_degree\
    \ = degree[v];\n                branch_vertex = v;\n            }\n        }\n\
    \n        if (active_count == 0) return {};\n        if (max_degree <= 2) {\n\
    \            auto result = solve_degree_at_most_two(active, degree);\n       \
    \     std::sort(result.begin(), result.end());\n            return result;\n \
    \       }\n\n        auto without = active;\n        without[branch_vertex] =\
    \ false;\n        auto result_without = solve(without);\n\n        auto with =\
    \ active;\n        with[branch_vertex] = false;\n        for (int to : graph[branch_vertex])\
    \ with[to] = false;\n        auto result_with = solve(with);\n        result_with.push_back(branch_vertex);\n\
    \n        auto result = (result_with.size() > result_without.size() ? result_with\
    \ : result_without);\n        std::sort(result.begin(), result.end());\n     \
    \   return result;\n    }\n\n    std::vector<int> solve() const {\n        std::vector<char>\
    \ active(n, true);\n        return solve(active);\n    }\n};\n\ntemplate <class\
    \ T>\nstd::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    std::vector<std::vector<char>> adjacent(n,\
    \ std::vector<char>(n, false));\n    for (const auto& e : g.edges()) {\n     \
    \   if (e.from == e.to) continue;\n        adjacent[e.from][e.to] = true;\n  \
    \      adjacent[e.to][e.from] = true;\n    }\n    return adjacent;\n}\n\nstd::vector<std::vector<char>>\
    \ complement_adjacency_matrix(const std::vector<std::vector<char>>& adjacent)\
    \ {\n    int n = int(adjacent.size());\n    std::vector<std::vector<char>> complement(n,\
    \ std::vector<char>(n, false));\n    for (int i = 0; i < n; i++) {\n        for\
    \ (int j = i + 1; j < n; j++) {\n            if (adjacent[i][j]) continue;\n \
    \           complement[i][j] = true;\n            complement[j][i] = true;\n \
    \       }\n    }\n    return complement;\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class T>\nbool is_clique(const Graph<T>& g, const std::vector<int>& vertices)\
    \ {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    for (int\
    \ v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n    for (int\
    \ i = 0; i < int(vertices.size()); i++) {\n        for (int j = i + 1; j < int(vertices.size());\
    \ j++) {\n            if (!adjacent[vertices[i]][vertices[j]]) return false;\n\
    \        }\n    }\n    return true;\n}\n\ntemplate <class T>\nbool is_independent_set(const\
    \ Graph<T>& g, const std::vector<int>& vertices) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    for (int v : vertices) {\n        assert(0 <= v && v < g.size());\n    }\n\
    \    for (int i = 0; i < int(vertices.size()); i++) {\n        for (int j = i\
    \ + 1; j < int(vertices.size()); j++) {\n            if (adjacent[vertices[i]][vertices[j]])\
    \ return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class T>\n\
    bool is_vertex_cover(const Graph<T>& g, const std::vector<int>& vertices) {\n\
    \    std::vector<char> selected(g.size(), false);\n    for (int v : vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        selected[v] = true;\n  \
    \  }\n    for (const auto& e : g.edges()) {\n        if (e.from == e.to) continue;\n\
    \        if (!selected[e.from] && !selected[e.to]) return false;\n    }\n    return\
    \ true;\n}\n\ntemplate <class T>\nMaximumCliqueResult maximum_clique(const Graph<T>&\
    \ g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n    auto\
    \ complement = detail::complement_adjacency_matrix(adjacent);\n    detail::MaximumIndependentSetBranching\
    \ solver(complement);\n    return MaximumCliqueResult{solver.solve()};\n}\n\n\
    template <class T>\nint maximum_clique_size(const Graph<T>& g) {\n    return maximum_clique(g).size();\n\
    }\n\ntemplate <class T>\nMaximumIndependentSetResult maximum_independent_set(const\
    \ Graph<T>& g) {\n    auto adjacent = detail::undirected_adjacency_matrix(g);\n\
    \    detail::MaximumIndependentSetBranching solver(adjacent);\n    return MaximumIndependentSetResult{solver.solve()};\n\
    }\n\ntemplate <class T>\nint maximum_independent_set_size(const Graph<T>& g) {\n\
    \    return maximum_independent_set(g).size();\n}\n\ntemplate <class T>\nMinimumVertexCoverResult\
    \ minimum_vertex_cover(const Graph<T>& g) {\n    auto independent = maximum_independent_set(g);\n\
    \    std::vector<char> in_independent(g.size(), false);\n    for (int v : independent.vertices)\
    \ in_independent[v] = true;\n\n    MinimumVertexCoverResult result;\n    for (int\
    \ v = 0; v < g.size(); v++) {\n        if (!in_independent[v]) result.vertices.push_back(v);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nint minimum_vertex_cover_size(const\
    \ Graph<T>& g) {\n    return minimum_vertex_cover(g).size();\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/minimum_steiner_tree.hpp\"\
    \n\n\n\n#line 5 \"graph/minimum_steiner_tree.hpp\"\n#include <bit>\n#line 15 \"\
    graph/minimum_steiner_tree.hpp\"\n\n#line 17 \"graph/minimum_steiner_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeResult\
    \ {\n    Cost cost;\n    std::vector<int> edge_ids;\n    std::vector<int> vertices;\n\
    };\n\nnamespace internal {\n\ninline std::vector<int> steiner_terminals(int n,\
    \ std::vector<int> terminals) {\n    for (int v : terminals) assert(0 <= v &&\
    \ v < n);\n    std::sort(terminals.begin(), terminals.end());\n    terminals.erase(std::unique(terminals.begin(),\
    \ terminals.end()), terminals.end());\n    assert(terminals.size() < std::numeric_limits<std::size_t>::digits);\n\
    \    return terminals;\n}\n\ntemplate <class Cost>\nstruct MinimumSteinerTreeDp\
    \ {\n    Cost cost;\n    Cost inf;\n    std::size_t states;\n    std::size_t width;\n\
    \    std::vector<Cost> dp;\n    std::vector<int> terminals;\n};\n\ntemplate <class\
    \ Cost, class GraphCost, class EdgeCost>\nstd::optional<MinimumSteinerTreeDp<Cost>>\
    \ minimum_steiner_tree_dp(\n    const Graph<GraphCost>& g,\n    std::vector<int>\
    \ terminals,\n    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost,\n\
    \    Cost inf\n) {\n    const int n = g.size();\n    assert(vertex_cost.size()\
    \ == std::size_t(n));\n    for (Cost cost : vertex_cost) assert(Cost(0) <= cost);\n\
    \    terminals = steiner_terminals(n, std::move(terminals));\n    const int k\
    \ = int(terminals.size());\n    if (k == 0) return MinimumSteinerTreeDp<Cost>{Cost(0),\
    \ inf, 1, std::size_t(n), {}, {}};\n\n    assert(Cost(0) < inf);\n    for (int\
    \ v = 0; v < n; v++) {\n        for (const auto& edge : g[v]) {\n            if\
    \ (edge.alive) assert(Cost(0) <= edge_cost(edge));\n        }\n    }\n\n    const\
    \ std::size_t states = std::size_t(1) << k;\n    const std::size_t width = std::size_t(n);\n\
    \    assert(width <= std::numeric_limits<std::size_t>::max() / states);\n    std::vector<Cost>\
    \ dp(states * width, inf);\n    for (int i = 0; i < k; i++) {\n        const int\
    \ terminal = terminals[i];\n        if (vertex_cost[terminal] < inf) {\n     \
    \       dp[(std::size_t(1) << i) * width + std::size_t(terminal)] = vertex_cost[terminal];\n\
    \        }\n    }\n\n    using QueueEntry = std::pair<Cost, int>;\n    for (std::size_t\
    \ mask = 1; mask < states; mask++) {\n        const std::size_t mask_offset =\
    \ mask * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub\
    \ = (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n \
    \           if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const Cost left = dp[sub_offset +\
    \ vertex];\n                const Cost right = dp[other_offset + vertex];\n  \
    \              if (left == inf || right == inf) continue;\n                assert(vertex_cost[v]\
    \ <= right);\n                const Cost extra = right - vertex_cost[v];\n   \
    \             if (left > inf - extra) continue;\n                const Cost candidate\
    \ = left + extra;\n                Cost& current = dp[mask_offset + vertex];\n\
    \                if (candidate < current) current = candidate;\n            }\n\
    \        }\n\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>,\
    \ std::greater<QueueEntry>> queue;\n        for (int v = 0; v < n; v++) {\n  \
    \          const Cost distance = dp[mask_offset + std::size_t(v)];\n         \
    \   if (distance != inf) queue.emplace(distance, v);\n        }\n        while\
    \ (!queue.empty()) {\n            auto [distance, v] = queue.top();\n        \
    \    queue.pop();\n            if (distance != dp[mask_offset + std::size_t(v)])\
    \ continue;\n            for (const auto& edge : g[v]) {\n                if (!edge.alive)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= inf || vertex_cost[edge.to] > inf - cost) continue;\n       \
    \         const Cost extra = cost + vertex_cost[edge.to];\n                if\
    \ (distance > inf - extra) continue;\n                const Cost candidate = distance\
    \ + extra;\n                Cost& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                if (current <= candidate) continue;\n                current\
    \ = candidate;\n                queue.emplace(candidate, edge.to);\n         \
    \   }\n        }\n    }\n\n    const auto answer_begin = dp.begin() + (states\
    \ - 1) * width;\n    const Cost answer = *std::min_element(answer_begin, dp.end());\n\
    \    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<Cost>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeDp<int>>\
    \ minimum_steiner_tree_unweighted_dp(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    const int n = g.size();\n    terminals = steiner_terminals(n,\
    \ std::move(terminals));\n    const int k = int(terminals.size());\n    if (k\
    \ == 0) return MinimumSteinerTreeDp<int>{0, n, 1, std::size_t(n), {}, {}};\n\n\
    \    const std::size_t states = std::size_t(1) << k;\n    const std::size_t width\
    \ = std::size_t(n);\n    assert(width <= std::numeric_limits<std::size_t>::max()\
    \ / states);\n    const int inf = n;\n    std::vector<int> dp(states * width,\
    \ inf);\n    for (int i = 0; i < k; i++) {\n        dp[(std::size_t(1) << i) *\
    \ width + std::size_t(terminals[i])] = 0;\n    }\n\n    for (std::size_t mask\
    \ = 1; mask < states; mask++) {\n        const std::size_t mask_offset = mask\
    \ * width;\n        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub =\
    \ (sub - 1) & mask) {\n            const std::size_t other = mask ^ sub;\n   \
    \         if (sub > other) continue;\n            const std::size_t sub_offset\
    \ = sub * width;\n            const std::size_t other_offset = other * width;\n\
    \            for (int v = 0; v < n; v++) {\n                const std::size_t\
    \ vertex = std::size_t(v);\n                const int candidate = dp[sub_offset\
    \ + vertex] + dp[other_offset + vertex];\n                int& current = dp[mask_offset\
    \ + vertex];\n                if (candidate < current) current = candidate;\n\
    \            }\n        }\n\n        std::vector<int> bucket_head(n, -1);\n  \
    \      std::vector<int> entry_vertex;\n        std::vector<int> entry_next;\n\
    \        entry_vertex.reserve(2 * width);\n        entry_next.reserve(2 * width);\n\
    \        auto push = [&](int distance, int v) {\n            entry_vertex.push_back(v);\n\
    \            entry_next.push_back(bucket_head[distance]);\n            bucket_head[distance]\
    \ = int(entry_vertex.size()) - 1;\n        };\n        for (int v = 0; v < n;\
    \ v++) {\n            const int distance = dp[mask_offset + std::size_t(v)];\n\
    \            if (distance != inf) push(distance, v);\n        }\n        for (int\
    \ distance = 0; distance < n; distance++) {\n            for (int entry = bucket_head[distance];\
    \ entry != -1; entry = entry_next[entry]) {\n                const int v = entry_vertex[entry];\n\
    \                if (dp[mask_offset + std::size_t(v)] != distance) continue;\n\
    \                for (const auto& edge : g[v]) {\n                    if (!edge.alive)\
    \ continue;\n                    int& current = dp[mask_offset + std::size_t(edge.to)];\n\
    \                    if (distance + 1 >= current) continue;\n                \
    \    current = distance + 1;\n                    push(current, edge.to);\n  \
    \              }\n            }\n        }\n    }\n\n    const auto answer_begin\
    \ = dp.begin() + (states - 1) * width;\n    const int answer = *std::min_element(answer_begin,\
    \ dp.end());\n    if (answer == inf) return std::nullopt;\n    return MinimumSteinerTreeDp<int>{\n\
    \        answer,\n        inf,\n        states,\n        width,\n        std::move(dp),\n\
    \        std::move(terminals)\n    };\n}\n\ntemplate <class Cost, class GraphCost,\
    \ class EdgeCost>\nMinimumSteinerTreeResult<Cost> restore_minimum_steiner_tree(\n\
    \    const Graph<GraphCost>& g,\n    const MinimumSteinerTreeDp<Cost>& data,\n\
    \    const std::vector<Cost>& vertex_cost,\n    EdgeCost edge_cost\n) {\n    MinimumSteinerTreeResult<Cost>\
    \ result;\n    result.cost = data.cost;\n    if (data.terminals.empty()) return\
    \ result;\n\n    const int n = g.size();\n    const std::size_t cells = data.states\
    \ * data.width;\n    std::vector<char> state(cells, 0);\n    std::vector<char>\
    \ selected_edge(g.edge_count(), false);\n\n    std::function<bool(std::size_t,\
    \ int)> restore = [&](std::size_t mask, int start) {\n        const std::size_t\
    \ position = mask * data.width + std::size_t(start);\n        if (state[position]\
    \ == 2) return true;\n        if (state[position] == 1) return false;\n      \
    \  state[position] = 1;\n\n        std::vector<int> search_parent(n, -2), search_edge(n,\
    \ -1), stack;\n        search_parent[start] = -1;\n        stack.push_back(start);\n\
    \        int seed = -1;\n        std::size_t seed_split = 0;\n\n        while\
    \ (!stack.empty() && seed == -1) {\n            const int v = stack.back();\n\
    \            stack.pop_back();\n            const std::size_t vertex_position\
    \ = mask * data.width + std::size_t(v);\n            const Cost current = data.dp[vertex_position];\n\
    \n            if (v != start && state[vertex_position] == 2) {\n             \
    \   seed = v;\n                break;\n            }\n            if ((mask &\
    \ (mask - 1)) == 0) {\n                const int terminal_index = int(std::countr_zero(mask));\n\
    \                if (v == data.terminals[terminal_index] && current == vertex_cost[v])\
    \ {\n                    seed = v;\n                    break;\n             \
    \   }\n            }\n            for (std::size_t sub = (mask - 1) & mask; sub\
    \ != 0; sub = (sub - 1) & mask) {\n                const std::size_t other = mask\
    \ ^ sub;\n                if (sub > other) continue;\n                const Cost\
    \ left = data.dp[sub * data.width + std::size_t(v)];\n                const Cost\
    \ right = data.dp[other * data.width + std::size_t(v)];\n                if (left\
    \ == data.inf || right == data.inf || right < vertex_cost[v]) continue;\n    \
    \            const Cost extra = right - vertex_cost[v];\n                if (left\
    \ > data.inf - extra || left + extra != current) continue;\n                seed\
    \ = v;\n                seed_split = sub;\n                break;\n          \
    \  }\n            if (seed != -1) break;\n\n            for (const auto& edge\
    \ : g[v]) {\n                if (!edge.alive || search_parent[edge.to] != -2)\
    \ continue;\n                const Cost cost = edge_cost(edge);\n            \
    \    if (cost >= data.inf || vertex_cost[v] > data.inf - cost) continue;\n   \
    \             const Cost extra = cost + vertex_cost[v];\n                const\
    \ Cost previous = data.dp[mask * data.width + std::size_t(edge.to)];\n       \
    \         if (previous == data.inf || previous > data.inf - extra) continue;\n\
    \                if (previous + extra != current) continue;\n                search_parent[edge.to]\
    \ = v;\n                search_edge[edge.to] = edge.id;\n                stack.push_back(edge.to);\n\
    \            }\n        }\n\n        if (seed == -1) {\n            state[position]\
    \ = 0;\n            return false;\n        }\n        if (seed_split != 0) {\n\
    \            const bool restored_left = restore(seed_split, seed);\n         \
    \   const bool restored_right = restore(mask ^ seed_split, seed);\n          \
    \  assert(restored_left && restored_right);\n            if (!restored_left ||\
    \ !restored_right) {\n                state[position] = 0;\n                return\
    \ false;\n            }\n        }\n\n        for (int v = seed; v != -1; v =\
    \ search_parent[v]) {\n            state[mask * data.width + std::size_t(v)] =\
    \ 2;\n            if (search_parent[v] == -1) continue;\n            const int\
    \ id = search_edge[v];\n            assert(0 <= id && id < g.edge_count());\n\
    \            selected_edge[id] = true;\n        }\n        return true;\n    };\n\
    \n    int root = -1;\n    const std::size_t full_mask = data.states - 1;\n   \
    \ for (int v = 0; v < n; v++) {\n        if (data.dp[full_mask * data.width +\
    \ std::size_t(v)] == data.cost) {\n            root = v;\n            break;\n\
    \        }\n    }\n    assert(root != -1);\n    const bool restored = restore(full_mask,\
    \ root);\n    assert(restored);\n    (void)restored;\n\n    std::vector<Edge<GraphCost>>\
    \ edge_by_id(g.edge_count());\n    std::vector<char> has_edge(g.edge_count(),\
    \ false);\n    for (const auto& edge : g.edges()) {\n        edge_by_id[edge.id]\
    \ = edge;\n        has_edge[edge.id] = true;\n    }\n\n    std::vector<int> parent(n),\
    \ component_size(n, 1);\n    for (int v = 0; v < n; v++) parent[v] = v;\n    auto\
    \ leader = [&](auto&& self, int v) -> int {\n        if (parent[v] == v) return\
    \ v;\n        return parent[v] = self(self, parent[v]);\n    };\n\n    std::vector<char>\
    \ tree_edge(g.edge_count(), false);\n    for (int id = 0; id < g.edge_count();\
    \ id++) {\n        if (!selected_edge[id]) continue;\n        assert(has_edge[id]);\n\
    \        const auto& edge = edge_by_id[id];\n        int u = leader(leader, edge.from);\n\
    \        int v = leader(leader, edge.to);\n        if (u == v) continue;\n   \
    \     if (component_size[u] < component_size[v]) std::swap(u, v);\n        parent[v]\
    \ = u;\n        component_size[u] += component_size[v];\n        tree_edge[id]\
    \ = true;\n    }\n\n    std::vector<std::vector<std::pair<int, int>>> tree(n);\n\
    \    std::vector<int> degree(n, 0);\n    std::vector<char> in_tree(n, false),\
    \ is_terminal(n, false);\n    for (int terminal : data.terminals) {\n        in_tree[terminal]\
    \ = true;\n        is_terminal[terminal] = true;\n    }\n    for (int id = 0;\
    \ id < g.edge_count(); id++) {\n        if (!tree_edge[id]) continue;\n      \
    \  const auto& edge = edge_by_id[id];\n        tree[edge.from].emplace_back(edge.to,\
    \ id);\n        tree[edge.to].emplace_back(edge.from, id);\n        degree[edge.from]++;\n\
    \        degree[edge.to]++;\n        in_tree[edge.from] = true;\n        in_tree[edge.to]\
    \ = true;\n    }\n\n    std::queue<int> leaves;\n    for (int v = 0; v < n; v++)\
    \ {\n        if (in_tree[v] && !is_terminal[v] && degree[v] <= 1) leaves.push(v);\n\
    \    }\n    std::vector<char> removed_vertex(n, false), removed_edge(g.edge_count(),\
    \ false);\n    while (!leaves.empty()) {\n        const int v = leaves.front();\n\
    \        leaves.pop();\n        if (removed_vertex[v] || is_terminal[v] || degree[v]\
    \ > 1) continue;\n        removed_vertex[v] = true;\n        for (auto [to, id]\
    \ : tree[v]) {\n            if (removed_edge[id]) continue;\n            removed_edge[id]\
    \ = true;\n            degree[v]--;\n            degree[to]--;\n            if\
    \ (!is_terminal[to] && degree[to] <= 1) leaves.push(to);\n            break;\n\
    \        }\n    }\n\n    Cost restored_cost = Cost(0);\n    for (int id = 0; id\
    \ < g.edge_count(); id++) {\n        if (!tree_edge[id] || removed_edge[id]) continue;\n\
    \        result.edge_ids.push_back(id);\n        restored_cost += edge_cost(edge_by_id[id]);\n\
    \    }\n    for (int v = 0; v < n; v++) {\n        if (!in_tree[v] || removed_vertex[v])\
    \ continue;\n        result.vertices.push_back(v);\n        restored_cost += vertex_cost[v];\n\
    \    }\n    if constexpr (std::is_integral_v<Cost>) assert(restored_cost == result.cost);\n\
    \    result.cost = restored_cost;\n    return result;\n}\n\n}  // namespace internal\n\
    \ntemplate <class T>\nstd::optional<T> minimum_steiner_tree(\n    const Graph<T>&\
    \ g,\n    std::vector<int> terminals,\n    const std::vector<T>& vertex_cost,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto result = internal::minimum_steiner_tree_dp(\n\
    \        g,\n        std::move(terminals),\n        vertex_cost,\n        [](const\
    \ Edge<T>& edge) { return edge.cost; },\n        inf\n    );\n    if (!result)\
    \ return std::nullopt;\n    return result->cost;\n}\n\ntemplate <class T>\nstd::optional<T>\
    \ minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    return minimum_steiner_tree(g,\
    \ std::move(terminals), std::vector<T>(g.size(), T(0)), inf);\n}\n\ntemplate <class\
    \ GraphCost, class Cost>\nstd::optional<Cost> minimum_steiner_tree_unweighted(\n\
    \    const Graph<GraphCost>& g,\n    std::vector<int> terminals,\n    const std::vector<Cost>&\
    \ vertex_cost,\n    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n\
    \    auto result = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!result) return std::nullopt;\n    return result->cost;\n\
    }\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals,\n    const std::vector<T>&\
    \ vertex_cost,\n    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    auto\
    \ data = internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<T>& edge) { return edge.cost; },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>& edge)\
    \ { return edge.cost; }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<T>>\
    \ build_minimum_steiner_tree(\n    const Graph<T>& g,\n    std::vector<int> terminals,\n\
    \    T inf = std::numeric_limits<T>::max() / T(4)\n) {\n    std::vector<T> vertex_cost(g.size(),\
    \ T(0));\n    return build_minimum_steiner_tree(g, std::move(terminals), vertex_cost,\
    \ inf);\n}\n\ntemplate <class GraphCost, class Cost>\nstd::optional<MinimumSteinerTreeResult<Cost>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<GraphCost>& g,\n   \
    \ std::vector<int> terminals,\n    const std::vector<Cost>& vertex_cost,\n   \
    \ Cost inf = std::numeric_limits<Cost>::max() / Cost(4)\n) {\n    auto data =\
    \ internal::minimum_steiner_tree_dp(\n        g,\n        std::move(terminals),\n\
    \        vertex_cost,\n        [](const Edge<GraphCost>&) { return Cost(1); },\n\
    \        inf\n    );\n    if (!data) return std::nullopt;\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<GraphCost>&)\
    \ { return Cost(1); }\n    );\n}\n\ntemplate <class T>\nstd::optional<MinimumSteinerTreeResult<int>>\
    \ build_minimum_steiner_tree_unweighted(\n    const Graph<T>& g,\n    std::vector<int>\
    \ terminals\n) {\n    auto data = internal::minimum_steiner_tree_unweighted_dp(g,\
    \ std::move(terminals));\n    if (!data) return std::nullopt;\n    std::vector<int>\
    \ vertex_cost(g.size(), 0);\n    return internal::restore_minimum_steiner_tree(\n\
    \        g,\n        *data,\n        vertex_cost,\n        [](const Edge<T>&)\
    \ { return 1; }\n    );\n}\n\ntemplate <class T>\nstd::optional<int> minimum_steiner_tree_unweighted(\n\
    \    const Graph<T>& g,\n    std::vector<int> terminals\n) {\n    auto result\
    \ = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));\n \
    \   if (!result) return std::nullopt;\n    return result->cost;\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 1 \"graph/namori.hpp\"\n\n\n\n#line\
    \ 9 \"graph/namori.hpp\"\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int\
    \ component_count;\n    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 16 \"graph/undirected.hpp\"\n\n\n#line\
    \ 12 \"graph/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_GRAPH_ALL_HPP

    #define M1UNE_GRAPH_ALL_HPP 1


    #include "counting.hpp"

    #include "directed.hpp"

    #include "dominator_tree.hpp"

    #include "graph.hpp"

    #include "grid.hpp"

    #include "range_edge_graph.hpp"

    #include "shortest_path.hpp"

    #include "undirected.hpp"


    #endif  // M1UNE_GRAPH_ALL_HPP

    '
  dependsOn:
  - graph/counting.hpp
  - fps/convolution.hpp
  - math/modint.hpp
  - fps/formal_power_series.hpp
  - fps/convolution.hpp
  - math/combinatorics.hpp
  - graph/directed.hpp
  - graph/cycle_detection.hpp
  - graph/graph.hpp
  - graph/scc.hpp
  - graph/shortest_path.hpp
  - graph/bellman_ford.hpp
  - graph/bfs.hpp
  - graph/cow_game.hpp
  - graph/dag_shortest_path.hpp
  - graph/topological_sort.hpp
  - graph/dijkstra.hpp
  - graph/warshall_floyd.hpp
  - graph/zero_one_bfs.hpp
  - graph/two_sat.hpp
  - graph/dominator_tree.hpp
  - graph/grid.hpp
  - graph/range_edge_graph.hpp
  - graph/undirected.hpp
  - graph/bipartite.hpp
  - graph/connected_components.hpp
  - ds/dsu/dsu.hpp
  - graph/general_matching.hpp
  - graph/kruskal.hpp
  - graph/lowlink.hpp
  - graph/maximum_clique.hpp
  - graph/minimum_steiner_tree.hpp
  - graph/namori.hpp
  isVerificationFile: false
  path: graph/all.hpp
  requiredBy: []
  timestamp: '2026-07-07 14:04:22+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/all.hpp
layout: document
title: Graph All
---

## Overview

`graph/all.hpp` includes every general graph header in this directory. It is
convenient when writing quickly during a contest and you do not want to manage
individual graph includes. Flow-network algorithms live separately under
`flow/`.

## Included Headers

| Header | Graph orientation | Contents |
| --- | --- | --- |
| `graph/graph.hpp` | Container | `Graph<T>` and `Edge<T>` adjacency-list container. |
| `graph/counting.hpp` | Counting formulas | Counts common labeled graph classes, tournaments, DAGs, and unlabeled trees by vertex number. |
| `graph/range_edge_graph.hpp` | Directed graph builder | Compact point-to-range, range-to-point, and range-to-range edges using segment trees. |
| `graph/shortest_path.hpp` | Direction-respecting / DAG-specific | Cow game difference constraints, BFS, 0-1 BFS, DAG shortest path, Dijkstra, Bellman-Ford, and Warshall-Floyd. |
| `graph/directed.hpp` | Directed-oriented bundle | Directed algorithms plus shortest paths. |
| `graph/undirected.hpp` | Undirected-oriented bundle | Undirected algorithms plus shortest paths and grid helpers. |
| `graph/bfs.hpp` | Direction-respecting | Unweighted shortest paths. |
| `graph/zero_one_bfs.hpp` | Direction-respecting | Shortest paths with edge costs `0` or `1`. |
| `graph/dag_shortest_path.hpp` | Directed DAG only | Shortest paths in a DAG, including negative edge costs. |
| `graph/dijkstra.hpp` | Direction-respecting | Non-negative weighted shortest paths. |
| `graph/bellman_ford.hpp` | Direction-respecting | Shortest paths with negative edges and negative-cycle marking. |
| `graph/cow_game.hpp` | Difference constraints | Feasibility, assignments, and tight bounds for systems of difference inequalities. |
| `graph/warshall_floyd.hpp` | Direction-respecting | All-pairs shortest paths. |
| `graph/grid.hpp` | Undirected graph builder | Helper for converting 2D grid cells to graph vertex ids. |
| `graph/topological_sort.hpp` | Directed only | DAG ordering and cycle check. |
| `graph/dominator_tree.hpp` | Directed rooted graph | Lengauer-Tarjan immediate dominators and dominator tree. |
| `graph/scc.hpp` | Directed only | Strongly connected components and condensation DAG. |
| `graph/two_sat.hpp` | Implication graph | 2-SAT clauses, satisfiability, and one assignment. |
| `graph/lowlink.hpp` | Undirected only | Articulation points and bridges. |
| `graph/bipartite.hpp` | Direction ignored / explicit bipartite sides | Two-colorability, maximum matching, minimum vertex cover, maximum independent set, and minimum edge cover. |
| `graph/general_matching.hpp` | Undirected only | Maximum-cardinality matching and minimum edge cover in general undirected graphs. |
| `graph/maximum_clique.hpp` | Direction ignored | Exact maximum clique, maximum independent set, and minimum vertex cover with bitset branch-and-bound. |
| `graph/minimum_steiner_tree.hpp` | Undirected only | Exact edge- and vertex-weighted minimum Steiner-tree costs and reconstruction for a small terminal set. |
| `graph/namori.hpp` | Undirected Namori graph | Decomposes each unicyclic component into its cycle and attached rooted trees. |
| `graph/connected_components.hpp` | Direction ignored | Weak/ordinary connected components. |
| `graph/cycle_detection.hpp` | Directed and undirected variants | Finds one cycle with the matching function. |
| `graph/kruskal.hpp` | Undirected only | Minimum spanning forest. |

## Example

```cpp
#include "graph/all.hpp"
#include <iostream>

int main() {
    m1une::graph::Graph<long long> g(3);
    g.add_directed_edge(0, 1, 10);
    auto dist = m1une::graph::dijkstra(g, 0).dist;
    std::cout << dist[1] << "\n";
}
```
