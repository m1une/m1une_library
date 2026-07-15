---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/cyclotomic_polynomial.hpp
    title: Cyclotomic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
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
  bundledCode: "#line 1 \"verify/math/cyclotomic_polynomial.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/cyclotomic_polynomial.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"math/prime_factorization.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#line 7 \"math/prime_factorization.hpp\"\n#include <numeric>\n\
    #include <utility>\n#line 10 \"math/prime_factorization.hpp\"\n\nnamespace m1une\
    \ {\nnamespace math {\n\nnamespace internal {\n\ninline uint64_t multiply_mod(uint64_t\
    \ a, uint64_t b, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned\
    \ __int128>(a) * b % mod);\n}\n\ninline uint64_t power_mod(uint64_t base, uint64_t\
    \ exponent, uint64_t mod) {\n    uint64_t result = 1;\n    while (exponent > 0)\
    \ {\n        if (exponent & 1) result = multiply_mod(result, base, mod);\n   \
    \     base = multiply_mod(base, base, mod);\n        exponent >>= 1;\n    }\n\
    \    return result;\n}\n\ninline uint64_t pollard_random() {\n    static uint64_t\
    \ state = 0x123456789abcdef0ULL;\n    state += 0x9e3779b97f4a7c15ULL;\n    uint64_t\
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
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
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
    \n\n#line 5 \"verify/math/cyclotomic_polynomial.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#line 15 \"utilities/fast_io.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
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
    \ m1une\n\n\n#line 10 \"verify/math/cyclotomic_polynomial.test.cpp\"\n\nnamespace\
    \ {\n\ntemplate <class T>\nstd::vector<T> multiply(\n    const std::vector<T>&\
    \ left,\n    const std::vector<T>& right\n) {\n    std::vector<T> result(left.size()\
    \ + right.size() - 1, T(0));\n    for (int i = 0; i < int(left.size()); i++) {\n\
    \        for (int j = 0; j < int(right.size()); j++) {\n            result[i +\
    \ j] += left[i] * right[j];\n        }\n    }\n    return result;\n}\n\nvoid fixed_tests()\
    \ {\n    using m1une::math::cyclotomic_polynomial;\n\n    assert(cyclotomic_polynomial(1)\
    \ == std::vector<long long>({-1, 1}));\n    assert(cyclotomic_polynomial(2) ==\
    \ std::vector<long long>({1, 1}));\n    assert(cyclotomic_polynomial(3) == std::vector<long\
    \ long>({1, 1, 1}));\n    assert(cyclotomic_polynomial(4) == std::vector<long\
    \ long>({1, 0, 1}));\n    assert(cyclotomic_polynomial(6) == std::vector<long\
    \ long>({1, -1, 1}));\n    assert(\n        cyclotomic_polynomial(12) ==\n   \
    \     std::vector<long long>({1, 0, -1, 0, 1})\n    );\n}\n\nvoid product_identity_tests()\
    \ {\n    for (std::uint64_t index = 1; index <= 300; index++) {\n        const\
    \ std::vector<long long> polynomial =\n            m1une::math::cyclotomic_polynomial(index);\n\
    \        assert(polynomial.size() == m1une::math::euler_phi(index) + 1);\n   \
    \     assert(polynomial.back() == 1);\n        if (index > 1) {\n            assert(polynomial.front()\
    \ == 1);\n            for (int i = 0; i < int(polynomial.size()); i++) {\n   \
    \             assert(polynomial[i] == polynomial[polynomial.size() - 1 - i]);\n\
    \            }\n        }\n\n        std::vector<long long> product(1, 1);\n \
    \       for (std::uint64_t divisor : m1une::math::divisors(index)) {\n       \
    \     product = multiply(\n                product,\n                m1une::math::cyclotomic_polynomial(divisor)\n\
    \            );\n        }\n        std::vector<long long> expected(index + 1,\
    \ 0);\n        expected[0] = -1;\n        expected[index] = 1;\n        assert(product\
    \ == expected);\n    }\n}\n\nvoid generic_coefficient_tests() {\n    using Mint\
    \ = m1une::math::modint998244353;\n    for (std::uint64_t index = 1; index <=\
    \ 200; index++) {\n        const std::vector<long long> integer =\n          \
    \  m1une::math::cyclotomic_polynomial(index);\n        const std::vector<Mint>\
    \ modular =\n            m1une::math::cyclotomic_polynomial<Mint>(index);\n  \
    \      assert(integer.size() == modular.size());\n        for (int i = 0; i <\
    \ int(integer.size()); i++) {\n            assert(modular[i] == Mint(integer[i]));\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    fixed_tests();\n\
    \    product_identity_tests();\n    generic_coefficient_tests();\n\n    long long\
    \ a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/cyclotomic_polynomial.hpp\"\n#include \"../../math/modint.hpp\"\n\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nnamespace {\n\ntemplate <class T>\nstd::vector<T> multiply(\n\
    \    const std::vector<T>& left,\n    const std::vector<T>& right\n) {\n    std::vector<T>\
    \ result(left.size() + right.size() - 1, T(0));\n    for (int i = 0; i < int(left.size());\
    \ i++) {\n        for (int j = 0; j < int(right.size()); j++) {\n            result[i\
    \ + j] += left[i] * right[j];\n        }\n    }\n    return result;\n}\n\nvoid\
    \ fixed_tests() {\n    using m1une::math::cyclotomic_polynomial;\n\n    assert(cyclotomic_polynomial(1)\
    \ == std::vector<long long>({-1, 1}));\n    assert(cyclotomic_polynomial(2) ==\
    \ std::vector<long long>({1, 1}));\n    assert(cyclotomic_polynomial(3) == std::vector<long\
    \ long>({1, 1, 1}));\n    assert(cyclotomic_polynomial(4) == std::vector<long\
    \ long>({1, 0, 1}));\n    assert(cyclotomic_polynomial(6) == std::vector<long\
    \ long>({1, -1, 1}));\n    assert(\n        cyclotomic_polynomial(12) ==\n   \
    \     std::vector<long long>({1, 0, -1, 0, 1})\n    );\n}\n\nvoid product_identity_tests()\
    \ {\n    for (std::uint64_t index = 1; index <= 300; index++) {\n        const\
    \ std::vector<long long> polynomial =\n            m1une::math::cyclotomic_polynomial(index);\n\
    \        assert(polynomial.size() == m1une::math::euler_phi(index) + 1);\n   \
    \     assert(polynomial.back() == 1);\n        if (index > 1) {\n            assert(polynomial.front()\
    \ == 1);\n            for (int i = 0; i < int(polynomial.size()); i++) {\n   \
    \             assert(polynomial[i] == polynomial[polynomial.size() - 1 - i]);\n\
    \            }\n        }\n\n        std::vector<long long> product(1, 1);\n \
    \       for (std::uint64_t divisor : m1une::math::divisors(index)) {\n       \
    \     product = multiply(\n                product,\n                m1une::math::cyclotomic_polynomial(divisor)\n\
    \            );\n        }\n        std::vector<long long> expected(index + 1,\
    \ 0);\n        expected[0] = -1;\n        expected[index] = 1;\n        assert(product\
    \ == expected);\n    }\n}\n\nvoid generic_coefficient_tests() {\n    using Mint\
    \ = m1une::math::modint998244353;\n    for (std::uint64_t index = 1; index <=\
    \ 200; index++) {\n        const std::vector<long long> integer =\n          \
    \  m1une::math::cyclotomic_polynomial(index);\n        const std::vector<Mint>\
    \ modular =\n            m1une::math::cyclotomic_polynomial<Mint>(index);\n  \
    \      assert(integer.size() == modular.size());\n        for (int i = 0; i <\
    \ int(integer.size()); i++) {\n            assert(modular[i] == Mint(integer[i]));\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    fixed_tests();\n\
    \    product_identity_tests();\n    generic_coefficient_tests();\n\n    long long\
    \ a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - math/cyclotomic_polynomial.hpp
  - math/prime_factorization.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/cyclotomic_polynomial.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/cyclotomic_polynomial.test.cpp
layout: document
redirect_from:
- /verify/verify/math/cyclotomic_polynomial.test.cpp
- /verify/verify/math/cyclotomic_polynomial.test.cpp.html
title: verify/math/cyclotomic_polynomial.test.cpp
---
