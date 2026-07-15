---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/generalized_floor_sum.hpp
    title: Generalized Floor Sum
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
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
  bundledCode: "#line 1 \"verify/math/generalized_floor_sum.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/generalized_floor_sum.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class T,\
    \ int MaxPower, int MaxFloorPower>\nusing GeneralizedFloorSumTable =\n    std::array<std::array<T,\
    \ MaxFloorPower + 1>, MaxPower + 1>;\n\nnamespace generalized_floor_sum_detail\
    \ {\n\nusing SignedWide = __int128_t;\nusing UnsignedWide = __uint128_t;\n\ntemplate\
    \ <class T>\nT from_wide(SignedWide value) {\n    bool negative = value < 0;\n\
    \    UnsignedWide magnitude;\n    if (negative) {\n        magnitude = static_cast<UnsignedWide>(-(value\
    \ + 1));\n        ++magnitude;\n    } else {\n        magnitude = static_cast<UnsignedWide>(value);\n\
    \    }\n\n    T result = T();\n    T binary_place = T(1);\n    while (magnitude\
    \ > 0) {\n        if ((magnitude & 1) != 0) result += binary_place;\n        magnitude\
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
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6\
    \ \"math/modint.hpp\"\n#include <iostream>\n#line 9 \"math/modint.hpp\"\n\nnamespace\
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
    \n\n#line 1 \"math/number_theory.hpp\"\n\n\n\n#line 6 \"math/number_theory.hpp\"\
    \n#include <limits>\n#include <tuple>\n#line 9 \"math/number_theory.hpp\"\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace math {\n\nnamespace internal {\n\n\
    inline long long safe_mod(long long x, long long mod) {\n    x %= mod;\n    if\
    \ (x < 0) x += mod;\n    return x;\n}\n\ninline unsigned __int128 floor_sum_unsigned(unsigned\
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
    \ namespace m1une\n\n\n#line 6 \"verify/math/generalized_floor_sum.test.cpp\"\n\
    \n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 10 \"verify/math/generalized_floor_sum.test.cpp\"\n\nusing\
    \ Mint = m1une::math::modint998244353;\n\nlong long floor_div(long long numerator,\
    \ long long denominator) {\n    long long quotient = numerator / denominator;\n\
    \    if (numerator % denominator < 0) --quotient;\n    return quotient;\n}\n\n\
    template <class T, int MaxPower, int MaxFloorPower>\nauto naive(long long n, long\
    \ long mod, long long a, long long b) {\n    m1une::math::GeneralizedFloorSumTable<\n\
    \        T,\n        MaxPower,\n        MaxFloorPower\n    > result{};\n    for\
    \ (long long x = 0; x < n; ++x) {\n        long long y = floor_div(a * x + b,\
    \ mod);\n        T x_power = T(1);\n        for (int p = 0; p <= MaxPower; ++p)\
    \ {\n            T y_power = T(1);\n            for (int q = 0; q <= MaxFloorPower;\
    \ ++q) {\n                result[p][q] += x_power * y_power;\n               \
    \ y_power *= T(y);\n            }\n            x_power *= T(x);\n        }\n \
    \   }\n    return result;\n}\n\nvoid test_fixed_cases() {\n    auto count_only\
    \ =\n        m1une::math::generalized_floor_sum_table<Mint, 0, 0>(12, 1, -5, -8);\n\
    \    assert(count_only[0][0] == Mint(12));\n\n    auto empty =\n        m1une::math::generalized_floor_sum_table<Mint,\
    \ 3, 3>(0, 7, 2, 3);\n    for (const auto& row : empty) {\n        for (Mint value\
    \ : row) assert(value == Mint(0));\n    }\n\n    auto actual =\n        m1une::math::generalized_floor_sum_table<Mint,\
    \ 4, 4>(20, 11, -7, -9);\n    auto expected = naive<Mint, 4, 4>(20, 11, -7, -9);\n\
    \    assert(actual == expected);\n\n    Mint moment =\n        m1une::math::generalized_floor_sum<Mint,\
    \ 3, 2>(20, 11, -7, -9);\n    assert(moment == expected[3][2]);\n\n    auto unsigned_actual\
    \ =\n        m1une::math::generalized_floor_sum_table<std::uint64_t, 3, 3>(\n\
    \            30,\n            17,\n            23,\n            -41\n        );\n\
    \    auto unsigned_expected = naive<std::uint64_t, 3, 3>(30, 17, 23, -41);\n \
    \   assert(unsigned_actual == unsigned_expected);\n\n    long long ordinary =\
    \ m1une::math::floor_sum(1000000, 998244353, 123456, -789);\n    Mint generalized\
    \ =\n        m1une::math::generalized_floor_sum<Mint, 0, 1>(\n            1000000,\n\
    \            998244353,\n            123456,\n            -789\n        );\n \
    \   assert(generalized == Mint(ordinary));\n}\n\nvoid test_randomized_against_naive()\
    \ {\n    std::uint64_t state = 0x6a09e667f3bcc909ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int test = 0; test < 5000; ++test) {\n        long\
    \ long n = static_cast<long long>(random() % 25);\n        long long mod = 1 +\
    \ static_cast<long long>(random() % 20);\n        long long a = static_cast<long\
    \ long>(random() % 101) - 50;\n        long long b = static_cast<long long>(random()\
    \ % 101) - 50;\n\n        auto actual =\n            m1une::math::generalized_floor_sum_table<Mint,\
    \ 4, 4>(\n                n,\n                mod,\n                a,\n     \
    \           b\n            );\n        auto expected = naive<Mint, 4, 4>(n, mod,\
    \ a, b);\n        assert(actual == expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed_cases();\n\
    \    test_randomized_against_naive();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/generalized_floor_sum.hpp\"\n#include \"../../math/modint.hpp\"\n#include\
    \ \"../../math/number_theory.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include \"../../utilities/fast_io.hpp\"\n\nusing Mint = m1une::math::modint998244353;\n\
    \nlong long floor_div(long long numerator, long long denominator) {\n    long\
    \ long quotient = numerator / denominator;\n    if (numerator % denominator <\
    \ 0) --quotient;\n    return quotient;\n}\n\ntemplate <class T, int MaxPower,\
    \ int MaxFloorPower>\nauto naive(long long n, long long mod, long long a, long\
    \ long b) {\n    m1une::math::GeneralizedFloorSumTable<\n        T,\n        MaxPower,\n\
    \        MaxFloorPower\n    > result{};\n    for (long long x = 0; x < n; ++x)\
    \ {\n        long long y = floor_div(a * x + b, mod);\n        T x_power = T(1);\n\
    \        for (int p = 0; p <= MaxPower; ++p) {\n            T y_power = T(1);\n\
    \            for (int q = 0; q <= MaxFloorPower; ++q) {\n                result[p][q]\
    \ += x_power * y_power;\n                y_power *= T(y);\n            }\n   \
    \         x_power *= T(x);\n        }\n    }\n    return result;\n}\n\nvoid test_fixed_cases()\
    \ {\n    auto count_only =\n        m1une::math::generalized_floor_sum_table<Mint,\
    \ 0, 0>(12, 1, -5, -8);\n    assert(count_only[0][0] == Mint(12));\n\n    auto\
    \ empty =\n        m1une::math::generalized_floor_sum_table<Mint, 3, 3>(0, 7,\
    \ 2, 3);\n    for (const auto& row : empty) {\n        for (Mint value : row)\
    \ assert(value == Mint(0));\n    }\n\n    auto actual =\n        m1une::math::generalized_floor_sum_table<Mint,\
    \ 4, 4>(20, 11, -7, -9);\n    auto expected = naive<Mint, 4, 4>(20, 11, -7, -9);\n\
    \    assert(actual == expected);\n\n    Mint moment =\n        m1une::math::generalized_floor_sum<Mint,\
    \ 3, 2>(20, 11, -7, -9);\n    assert(moment == expected[3][2]);\n\n    auto unsigned_actual\
    \ =\n        m1une::math::generalized_floor_sum_table<std::uint64_t, 3, 3>(\n\
    \            30,\n            17,\n            23,\n            -41\n        );\n\
    \    auto unsigned_expected = naive<std::uint64_t, 3, 3>(30, 17, 23, -41);\n \
    \   assert(unsigned_actual == unsigned_expected);\n\n    long long ordinary =\
    \ m1une::math::floor_sum(1000000, 998244353, 123456, -789);\n    Mint generalized\
    \ =\n        m1une::math::generalized_floor_sum<Mint, 0, 1>(\n            1000000,\n\
    \            998244353,\n            123456,\n            -789\n        );\n \
    \   assert(generalized == Mint(ordinary));\n}\n\nvoid test_randomized_against_naive()\
    \ {\n    std::uint64_t state = 0x6a09e667f3bcc909ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int test = 0; test < 5000; ++test) {\n        long\
    \ long n = static_cast<long long>(random() % 25);\n        long long mod = 1 +\
    \ static_cast<long long>(random() % 20);\n        long long a = static_cast<long\
    \ long>(random() % 101) - 50;\n        long long b = static_cast<long long>(random()\
    \ % 101) - 50;\n\n        auto actual =\n            m1une::math::generalized_floor_sum_table<Mint,\
    \ 4, 4>(\n                n,\n                mod,\n                a,\n     \
    \           b\n            );\n        auto expected = naive<Mint, 4, 4>(n, mod,\
    \ a, b);\n        assert(actual == expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed_cases();\n\
    \    test_randomized_against_naive();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - math/generalized_floor_sum.hpp
  - math/modint.hpp
  - math/number_theory.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/generalized_floor_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/generalized_floor_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/math/generalized_floor_sum.test.cpp
- /verify/verify/math/generalized_floor_sum.test.cpp.html
title: verify/math/generalized_floor_sum.test.cpp
---
