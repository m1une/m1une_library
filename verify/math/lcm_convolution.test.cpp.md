---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/divisor_convolution.hpp
    title: Divisor Convolution
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/zeta_mobius_transform.hpp
    title: Zeta and Mobius Transform
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
    PROBLEM: https://judge.yosupo.jp/problem/lcm_convolution
    links:
    - https://judge.yosupo.jp/problem/lcm_convolution
  bundledCode: "#line 1 \"verify/math/lcm_convolution.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/lcm_convolution\"\n\n#line 1 \"math/divisor_convolution.hpp\"\
    \n\n\n\n#include <cstddef>\n#include <vector>\n\n#line 1 \"math/zeta_mobius_transform.hpp\"\
    \n\n\n\n#include <cassert>\n#line 7 \"math/zeta_mobius_transform.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\nnamespace zeta_mobius_transform_detail {\n\ninline\
    \ bool is_power_of_two(std::size_t size) noexcept {\n    return size != 0 && (size\
    \ & (size - 1)) == 0;\n}\n\ninline std::vector<std::size_t> primes_up_to(std::size_t\
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
    \ 8 \"math/divisor_convolution.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n\
    template <typename T>\nstd::vector<T> gcd_convolution(\n    std::vector<T> first,\n\
    \    std::vector<T> second\n) {\n    if (first.empty() || second.empty()) return\
    \ {};\n    const std::size_t size = first.size() > second.size()\n        ? first.size()\n\
    \        : second.size();\n    first.resize(size);\n    second.resize(size);\n\
    \    first[0] = T{};\n    second[0] = T{};\n\n    multiple_zeta_transform(first);\n\
    \    multiple_zeta_transform(second);\n    for (std::size_t index = 1; index <\
    \ size; ++index) {\n        first[index] *= second[index];\n    }\n    multiple_mobius_transform(first);\n\
    \    return first;\n}\n\ntemplate <typename T>\nstd::vector<T> lcm_convolution(\n\
    \    std::vector<T> first,\n    std::vector<T> second\n) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    const std::size_t size = first.size() > second.size()\n\
    \        ? first.size()\n        : second.size();\n    first.resize(size);\n \
    \   second.resize(size);\n    first[0] = T{};\n    second[0] = T{};\n\n    divisor_zeta_transform(first);\n\
    \    divisor_zeta_transform(second);\n    for (std::size_t index = 1; index <\
    \ size; ++index) {\n        first[index] *= second[index];\n    }\n    divisor_mobius_transform(first);\n\
    \    return first;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 5 \"math/modint.hpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une\
    \ {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0\
    \ < Modulus, \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\
    \n   public:\n    static constexpr uint32_t mod() {\n        return Modulus;\n\
    \    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt\
    \ x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept\
    \ : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
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
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
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
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 5 \"verify/math/lcm_convolution.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\n#include\
    \ <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/math/lcm_convolution.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n;\n    fast_input >> n;\n    using mint = m1une::math::modint998244353;\n\
    \    std::vector<mint> first(n + 1), second(n + 1);\n    for (int index = 1; index\
    \ <= n; ++index) {\n        long long value;\n        fast_input >> value;\n \
    \       first[index] = value;\n    }\n    for (int index = 1; index <= n; ++index)\
    \ {\n        long long value;\n        fast_input >> value;\n        second[index]\
    \ = value;\n    }\n\n    std::vector<mint> result =\n        m1une::math::lcm_convolution(first,\
    \ second);\n    for (int index = 1; index <= n; ++index) {\n        if (index\
    \ != 1) fast_output << ' ';\n        fast_output << result[index].val();\n   \
    \ }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lcm_convolution\"\n\n#include\
    \ \"../../math/divisor_convolution.hpp\"\n#include \"../../math/modint.hpp\"\n\
    \n#include \"../../utilities/fast_io.hpp\"\n#include <vector>\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n;\n    fast_input >> n;\n    using mint = m1une::math::modint998244353;\n\
    \    std::vector<mint> first(n + 1), second(n + 1);\n    for (int index = 1; index\
    \ <= n; ++index) {\n        long long value;\n        fast_input >> value;\n \
    \       first[index] = value;\n    }\n    for (int index = 1; index <= n; ++index)\
    \ {\n        long long value;\n        fast_input >> value;\n        second[index]\
    \ = value;\n    }\n\n    std::vector<mint> result =\n        m1une::math::lcm_convolution(first,\
    \ second);\n    for (int index = 1; index <= n; ++index) {\n        if (index\
    \ != 1) fast_output << ' ';\n        fast_output << result[index].val();\n   \
    \ }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - math/divisor_convolution.hpp
  - math/zeta_mobius_transform.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/lcm_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-07-21 23:59:08+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/lcm_convolution.test.cpp
layout: document
redirect_from:
- /verify/verify/math/lcm_convolution.test.cpp
- /verify/verify/math/lcm_convolution.test.cpp.html
title: verify/math/lcm_convolution.test.cpp
---
