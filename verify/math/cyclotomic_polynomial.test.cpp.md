---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/cyclotomic_polynomial.hpp
    title: Cyclotomic Polynomial
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/prime_factorization.hpp
    title: 64-bit Prime Factorization
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
    \n\n#line 5 \"verify/math/cyclotomic_polynomial.test.cpp\"\n\n#line 10 \"verify/math/cyclotomic_polynomial.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class T>\nstd::vector<T> multiply(\n    const std::vector<T>&\
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
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n\
    \    product_identity_tests();\n    generic_coefficient_tests();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/cyclotomic_polynomial.hpp\"\n#include \"../../math/modint.hpp\"\n\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \nnamespace {\n\ntemplate <class T>\nstd::vector<T> multiply(\n    const std::vector<T>&\
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
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    fixed_tests();\n\
    \    product_identity_tests();\n    generic_coefficient_tests();\n\n    long long\
    \ a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/cyclotomic_polynomial.hpp
  - math/prime_factorization.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/cyclotomic_polynomial.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/cyclotomic_polynomial.test.cpp
layout: document
redirect_from:
- /verify/verify/math/cyclotomic_polynomial.test.cpp
- /verify/verify/math/cyclotomic_polynomial.test.cpp.html
title: verify/math/cyclotomic_polynomial.test.cpp
---
