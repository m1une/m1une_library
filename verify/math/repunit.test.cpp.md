---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/repunit.hpp
    title: Repunit
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
  bundledCode: "#line 1 \"verify/math/repunit.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#include <cstdint>\n#include <iostream>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math\
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
    \ m1une\n\n\n#line 1 \"math/repunit.hpp\"\n\n\n\n#include <cassert>\n#line 6 \"\
    math/repunit.hpp\"\n#include <numeric>\n#include <optional>\n#line 9 \"math/repunit.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <class T>\nconstexpr std::pair<T,\
    \ T> repunit_and_power(\n    std::uint64_t length,\n    T base = T(10)\n) {\n\
    \    T result = T(0);\n    T result_power = T(1);\n    T block = T(1);\n    T\
    \ block_power = base;\n\n    while (length > 0) {\n        if (length & 1) {\n\
    \            result = result * block_power + block;\n            result_power\
    \ = result_power * block_power;\n        }\n        block = block * block_power\
    \ + block;\n        block_power = block_power * block_power;\n        length >>=\
    \ 1;\n    }\n    return std::make_pair(result, result_power);\n}\n\n// Returns\
    \ 1 + base + ... + base^(length - 1).\n// The arithmetic, including any modular\
    \ reduction, is performed by T.\ntemplate <class T>\nconstexpr T repunit(std::uint64_t\
    \ length, T base = T(10)) {\n    return repunit_and_power<T>(length, base).first;\n\
    }\n\ntemplate <class T>\nconstexpr T repdigit(std::uint64_t length, T digit, T\
    \ base = T(10)) {\n    return digit * repunit<T>(length, base);\n}\n\ntemplate\
    \ <class T>\nconstexpr T concatenate_digits(\n    T left,\n    T right,\n    std::uint64_t\
    \ right_length,\n    T base = T(10)\n) {\n    return left * repunit_and_power<T>(right_length,\
    \ base).second + right;\n}\n\nnamespace repunit_detail {\n\ninline std::uint64_t\
    \ multiply_mod(\n    std::uint64_t left,\n    std::uint64_t right,\n    std::uint64_t\
    \ mod\n) {\n    return static_cast<std::uint64_t>(\n        static_cast<unsigned\
    \ __int128>(left) * right % mod\n    );\n}\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    if (mod == 1) return std::make_pair(0,\
    \ 0);\n\n    std::uint64_t result = 0;\n    std::uint64_t result_power = 1;\n\
    \    std::uint64_t block = 1;\n    std::uint64_t block_power = base % mod;\n \
    \   while (length > 0) {\n        if (length & 1) {\n            result = (\n\
    \                static_cast<unsigned __int128>(result) * block_power + block\n\
    \            ) % mod;\n            result_power = multiply_mod(result_power, block_power,\
    \ mod);\n        }\n        block = (\n            static_cast<unsigned __int128>(block)\
    \ * block_power + block\n        ) % mod;\n        block_power = multiply_mod(block_power,\
    \ block_power, mod);\n        length >>= 1;\n    }\n    return std::make_pair(result,\
    \ result_power);\n}\n\n}  // namespace repunit_detail\n\ninline std::pair<std::uint64_t,\
    \ std::uint64_t> repunit_and_power_mod(\n    std::uint64_t length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    return repunit_detail::repunit_and_power_mod(length,\
    \ base, mod);\n}\n\ninline std::uint64_t repunit_mod(\n    std::uint64_t length,\n\
    \    std::uint64_t base,\n    std::uint64_t mod\n) {\n    return repunit_and_power_mod(length,\
    \ base, mod).first;\n}\n\ninline std::uint64_t repdigit_mod(\n    std::uint64_t\
    \ length,\n    std::uint64_t digit,\n    std::uint64_t base,\n    std::uint64_t\
    \ mod\n) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n    return repunit_detail::multiply_mod(\n\
    \        digit % mod,\n        repunit_mod(length, base, mod),\n        mod\n\
    \    );\n}\n\ninline std::uint64_t concatenate_digits_mod(\n    std::uint64_t\
    \ left,\n    std::uint64_t right,\n    std::uint64_t right_length,\n    std::uint64_t\
    \ base,\n    std::uint64_t mod\n) {\n    assert(mod >= 1);\n    if (mod == 1)\
    \ return 0;\n    const std::uint64_t power =\n        repunit_and_power_mod(right_length,\
    \ base, mod).second;\n    return (\n        static_cast<unsigned __int128>(left\
    \ % mod) * power + right % mod\n    ) % mod;\n}\n\ninline std::optional<std::uint64_t>\
    \ minimum_repunit_length(\n    std::uint64_t divisor,\n    std::uint64_t base\
    \ = 10\n) {\n    assert(divisor >= 1);\n    assert(base >= 2);\n    if (std::gcd(divisor,\
    \ base) != 1) return std::nullopt;\n\n    std::uint64_t remainder = 0;\n    for\
    \ (std::uint64_t length = 1; length <= divisor; length++) {\n        remainder\
    \ = (\n            static_cast<unsigned __int128>(remainder) * base + 1\n    \
    \    ) % divisor;\n        if (remainder == 0) return length;\n    }\n    return\
    \ std::nullopt;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 5\
    \ \"verify/math/repunit.test.cpp\"\n\n#line 11 \"verify/math/repunit.test.cpp\"\
    \n#include <random>\n#line 13 \"verify/math/repunit.test.cpp\"\n\nnamespace {\n\
    \ntemplate <class T>\nT naive_repunit(std::uint64_t length, T base) {\n    T result\
    \ = T(0);\n    for (std::uint64_t i = 0; i < length; i++) {\n        result =\
    \ result * base + T(1);\n    }\n    return result;\n}\n\ntemplate <class T>\n\
    T power(T base, std::uint64_t exponent) {\n    T result = T(1);\n    while (exponent\
    \ > 0) {\n        if (exponent & 1) result = result * base;\n        base = base\
    \ * base;\n        exponent >>= 1;\n    }\n    return result;\n}\n\nstd::uint64_t\
    \ naive_repunit_mod(\n    std::uint64_t length,\n    std::uint64_t base,\n   \
    \ std::uint64_t mod\n) {\n    std::uint64_t result = 0;\n    for (std::uint64_t\
    \ i = 0; i < length; i++) {\n        result = (\n            static_cast<unsigned\
    \ __int128>(result) * base + 1\n        ) % mod;\n    }\n    return result;\n\
    }\n\nstd::uint64_t naive_power_mod(\n    std::uint64_t base,\n    std::uint64_t\
    \ exponent,\n    std::uint64_t mod\n) {\n    std::uint64_t result = 1 % mod;\n\
    \    for (std::uint64_t i = 0; i < exponent; i++) {\n        result = static_cast<unsigned\
    \ __int128>(result) * base % mod;\n    }\n    return result;\n}\n\nvoid fixed_tests()\
    \ {\n    using m1une::math::repunit;\n\n    static_assert(repunit<unsigned long\
    \ long>(0) == 0);\n    static_assert(repunit<unsigned long long>(1) == 1);\n \
    \   static_assert(repunit<unsigned long long>(3) == 111);\n    static_assert(repunit<unsigned\
    \ long long>(4, 2) == 15);\n    static_assert(repunit<unsigned long long>(5, 1)\
    \ == 5);\n    static_assert(repunit<unsigned long long>(5, 0) == 1);\n    static_assert(\n\
    \        m1une::math::repdigit<unsigned long long>(3, 7) == 777\n    );\n    static_assert(\n\
    \        m1une::math::concatenate_digits(12ULL, 34ULL, 2) == 1234\n    );\n\n\
    \    constexpr std::pair<unsigned long long, unsigned long long> block =\n   \
    \     m1une::math::repunit_and_power<unsigned long long>(3);\n    static_assert(block.first\
    \ == 111);\n    static_assert(block.second == 1000);\n\n    using CompositeMint\
    \ = m1une::math::ModInt<1000>;\n    assert(repunit<CompositeMint>(3).val() ==\
    \ 111);\n    assert(repunit<CompositeMint>(30).val() == 111);\n\n    using Mint\
    \ = m1une::math::modint1000000007;\n    constexpr std::uint64_t large_length =\
    \ 1000000000000000000ULL;\n    Mint left = repunit<Mint>(large_length);\n    Mint\
    \ half = repunit<Mint>(large_length / 2);\n    Mint expected = half * power(Mint(10),\
    \ large_length / 2) + half;\n    assert(left == expected);\n\n    assert(m1une::math::repunit_mod(30,\
    \ 10, 1000) == 111);\n    assert((\n        m1une::math::repunit_and_power_mod(3,\
    \ 10, 1000) ==\n        std::pair<std::uint64_t, std::uint64_t>(111, 0)\n    ));\n\
    \    assert(m1une::math::repdigit_mod(3, 7, 10, 1000) == 777);\n    assert(m1une::math::concatenate_digits_mod(12,\
    \ 34, 2, 10, 1000) == 234);\n\n    assert(m1une::math::minimum_repunit_length(1)\
    \ == 1);\n    assert(!m1une::math::minimum_repunit_length(2).has_value());\n \
    \   assert(m1une::math::minimum_repunit_length(3) == 3);\n    assert(m1une::math::minimum_repunit_length(7)\
    \ == 6);\n    assert(m1une::math::minimum_repunit_length(13) == 6);\n    assert(m1une::math::minimum_repunit_length(27)\
    \ == 27);\n    assert(m1une::math::minimum_repunit_length(7, 2) == 3);\n}\n\n\
    void exhaustive_tests() {\n    using Mint = m1une::math::ModInt<1009>;\n    for\
    \ (int base = 0; base <= 50; base++) {\n        for (int length = 0; length <=\
    \ 500; length++) {\n            assert(\n                m1une::math::repunit<Mint>(length,\
    \ Mint(base)) ==\n                naive_repunit<Mint>(length, Mint(base))\n  \
    \          );\n        }\n    }\n}\n\nvoid runtime_modulus_tests() {\n    std::mt19937_64\
    \ random(0x13198a2e03707344ULL);\n    for (int trial = 0; trial < 30000; trial++)\
    \ {\n        const std::uint64_t mod = random() | 1;\n        const std::uint64_t\
    \ base = random();\n        const std::uint64_t digit = random();\n        const\
    \ std::uint64_t length = random() % 200;\n        const std::uint64_t expected\
    \ = naive_repunit_mod(length, base, mod);\n        assert(m1une::math::repunit_mod(length,\
    \ base, mod) == expected);\n        assert(\n            m1une::math::repdigit_mod(length,\
    \ digit, base, mod) ==\n            static_cast<unsigned __int128>(digit % mod)\
    \ * expected % mod\n        );\n\n        const std::uint64_t right_length = random()\
    \ % 100;\n        const std::uint64_t left = random();\n        const std::uint64_t\
    \ right = random();\n        const std::uint64_t base_power =\n            naive_power_mod(base,\
    \ right_length, mod);\n        const std::uint64_t concatenated = (\n        \
    \    static_cast<unsigned __int128>(left % mod) * base_power + right % mod\n \
    \       ) % mod;\n        assert(\n            m1une::math::concatenate_digits_mod(\n\
    \                left,\n                right,\n                right_length,\n\
    \                base,\n                mod\n            ) == concatenated\n \
    \       );\n    }\n}\n\nvoid minimum_length_tests() {\n    for (std::uint64_t\
    \ base = 2; base <= 20; base++) {\n        for (std::uint64_t divisor = 1; divisor\
    \ <= 500; divisor++) {\n            const std::optional<std::uint64_t> actual\
    \ =\n                m1une::math::minimum_repunit_length(divisor, base);\n   \
    \         if (std::gcd(base, divisor) != 1) {\n                assert(!actual.has_value());\n\
    \                continue;\n            }\n\n            assert(actual.has_value());\n\
    \            assert(*actual <= divisor);\n            assert(naive_repunit_mod(*actual,\
    \ base, divisor) == 0);\n            for (std::uint64_t length = 1; length < *actual;\
    \ length++) {\n                assert(naive_repunit_mod(length, base, divisor)\
    \ != 0);\n            }\n        }\n    }\n}\n\nvoid randomized_tests() {\n  \
    \  using Mint = m1une::math::modint998244353;\n    std::mt19937_64 random(0x243f6a8885a308d3ULL);\n\
    \n    for (int trial = 0; trial < 100000; trial++) {\n        const std::uint64_t\
    \ first_length = random() % 1000000000000ULL;\n        const std::uint64_t second_length\
    \ = random() % 1000000000000ULL;\n        const Mint base = Mint(random());\n\n\
    \        const Mint first = m1une::math::repunit<Mint>(first_length, base);\n\
    \        const Mint second = m1une::math::repunit<Mint>(second_length, base);\n\
    \        const Mint combined = m1une::math::repunit<Mint>(\n            first_length\
    \ + second_length,\n            base\n        );\n        assert(combined == first\
    \ * power(base, second_length) + second);\n    }\n}\n\n}  // namespace\n\nint\
    \ main() {\n    fixed_tests();\n    exhaustive_tests();\n    randomized_tests();\n\
    \    runtime_modulus_tests();\n    minimum_length_tests();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/modint.hpp\"\n#include \"../../math/repunit.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <numeric>\n#include <optional>\n\
    #include <random>\n#include <utility>\n\nnamespace {\n\ntemplate <class T>\nT\
    \ naive_repunit(std::uint64_t length, T base) {\n    T result = T(0);\n    for\
    \ (std::uint64_t i = 0; i < length; i++) {\n        result = result * base + T(1);\n\
    \    }\n    return result;\n}\n\ntemplate <class T>\nT power(T base, std::uint64_t\
    \ exponent) {\n    T result = T(1);\n    while (exponent > 0) {\n        if (exponent\
    \ & 1) result = result * base;\n        base = base * base;\n        exponent\
    \ >>= 1;\n    }\n    return result;\n}\n\nstd::uint64_t naive_repunit_mod(\n \
    \   std::uint64_t length,\n    std::uint64_t base,\n    std::uint64_t mod\n) {\n\
    \    std::uint64_t result = 0;\n    for (std::uint64_t i = 0; i < length; i++)\
    \ {\n        result = (\n            static_cast<unsigned __int128>(result) *\
    \ base + 1\n        ) % mod;\n    }\n    return result;\n}\n\nstd::uint64_t naive_power_mod(\n\
    \    std::uint64_t base,\n    std::uint64_t exponent,\n    std::uint64_t mod\n\
    ) {\n    std::uint64_t result = 1 % mod;\n    for (std::uint64_t i = 0; i < exponent;\
    \ i++) {\n        result = static_cast<unsigned __int128>(result) * base % mod;\n\
    \    }\n    return result;\n}\n\nvoid fixed_tests() {\n    using m1une::math::repunit;\n\
    \n    static_assert(repunit<unsigned long long>(0) == 0);\n    static_assert(repunit<unsigned\
    \ long long>(1) == 1);\n    static_assert(repunit<unsigned long long>(3) == 111);\n\
    \    static_assert(repunit<unsigned long long>(4, 2) == 15);\n    static_assert(repunit<unsigned\
    \ long long>(5, 1) == 5);\n    static_assert(repunit<unsigned long long>(5, 0)\
    \ == 1);\n    static_assert(\n        m1une::math::repdigit<unsigned long long>(3,\
    \ 7) == 777\n    );\n    static_assert(\n        m1une::math::concatenate_digits(12ULL,\
    \ 34ULL, 2) == 1234\n    );\n\n    constexpr std::pair<unsigned long long, unsigned\
    \ long long> block =\n        m1une::math::repunit_and_power<unsigned long long>(3);\n\
    \    static_assert(block.first == 111);\n    static_assert(block.second == 1000);\n\
    \n    using CompositeMint = m1une::math::ModInt<1000>;\n    assert(repunit<CompositeMint>(3).val()\
    \ == 111);\n    assert(repunit<CompositeMint>(30).val() == 111);\n\n    using\
    \ Mint = m1une::math::modint1000000007;\n    constexpr std::uint64_t large_length\
    \ = 1000000000000000000ULL;\n    Mint left = repunit<Mint>(large_length);\n  \
    \  Mint half = repunit<Mint>(large_length / 2);\n    Mint expected = half * power(Mint(10),\
    \ large_length / 2) + half;\n    assert(left == expected);\n\n    assert(m1une::math::repunit_mod(30,\
    \ 10, 1000) == 111);\n    assert((\n        m1une::math::repunit_and_power_mod(3,\
    \ 10, 1000) ==\n        std::pair<std::uint64_t, std::uint64_t>(111, 0)\n    ));\n\
    \    assert(m1une::math::repdigit_mod(3, 7, 10, 1000) == 777);\n    assert(m1une::math::concatenate_digits_mod(12,\
    \ 34, 2, 10, 1000) == 234);\n\n    assert(m1une::math::minimum_repunit_length(1)\
    \ == 1);\n    assert(!m1une::math::minimum_repunit_length(2).has_value());\n \
    \   assert(m1une::math::minimum_repunit_length(3) == 3);\n    assert(m1une::math::minimum_repunit_length(7)\
    \ == 6);\n    assert(m1une::math::minimum_repunit_length(13) == 6);\n    assert(m1une::math::minimum_repunit_length(27)\
    \ == 27);\n    assert(m1une::math::minimum_repunit_length(7, 2) == 3);\n}\n\n\
    void exhaustive_tests() {\n    using Mint = m1une::math::ModInt<1009>;\n    for\
    \ (int base = 0; base <= 50; base++) {\n        for (int length = 0; length <=\
    \ 500; length++) {\n            assert(\n                m1une::math::repunit<Mint>(length,\
    \ Mint(base)) ==\n                naive_repunit<Mint>(length, Mint(base))\n  \
    \          );\n        }\n    }\n}\n\nvoid runtime_modulus_tests() {\n    std::mt19937_64\
    \ random(0x13198a2e03707344ULL);\n    for (int trial = 0; trial < 30000; trial++)\
    \ {\n        const std::uint64_t mod = random() | 1;\n        const std::uint64_t\
    \ base = random();\n        const std::uint64_t digit = random();\n        const\
    \ std::uint64_t length = random() % 200;\n        const std::uint64_t expected\
    \ = naive_repunit_mod(length, base, mod);\n        assert(m1une::math::repunit_mod(length,\
    \ base, mod) == expected);\n        assert(\n            m1une::math::repdigit_mod(length,\
    \ digit, base, mod) ==\n            static_cast<unsigned __int128>(digit % mod)\
    \ * expected % mod\n        );\n\n        const std::uint64_t right_length = random()\
    \ % 100;\n        const std::uint64_t left = random();\n        const std::uint64_t\
    \ right = random();\n        const std::uint64_t base_power =\n            naive_power_mod(base,\
    \ right_length, mod);\n        const std::uint64_t concatenated = (\n        \
    \    static_cast<unsigned __int128>(left % mod) * base_power + right % mod\n \
    \       ) % mod;\n        assert(\n            m1une::math::concatenate_digits_mod(\n\
    \                left,\n                right,\n                right_length,\n\
    \                base,\n                mod\n            ) == concatenated\n \
    \       );\n    }\n}\n\nvoid minimum_length_tests() {\n    for (std::uint64_t\
    \ base = 2; base <= 20; base++) {\n        for (std::uint64_t divisor = 1; divisor\
    \ <= 500; divisor++) {\n            const std::optional<std::uint64_t> actual\
    \ =\n                m1une::math::minimum_repunit_length(divisor, base);\n   \
    \         if (std::gcd(base, divisor) != 1) {\n                assert(!actual.has_value());\n\
    \                continue;\n            }\n\n            assert(actual.has_value());\n\
    \            assert(*actual <= divisor);\n            assert(naive_repunit_mod(*actual,\
    \ base, divisor) == 0);\n            for (std::uint64_t length = 1; length < *actual;\
    \ length++) {\n                assert(naive_repunit_mod(length, base, divisor)\
    \ != 0);\n            }\n        }\n    }\n}\n\nvoid randomized_tests() {\n  \
    \  using Mint = m1une::math::modint998244353;\n    std::mt19937_64 random(0x243f6a8885a308d3ULL);\n\
    \n    for (int trial = 0; trial < 100000; trial++) {\n        const std::uint64_t\
    \ first_length = random() % 1000000000000ULL;\n        const std::uint64_t second_length\
    \ = random() % 1000000000000ULL;\n        const Mint base = Mint(random());\n\n\
    \        const Mint first = m1une::math::repunit<Mint>(first_length, base);\n\
    \        const Mint second = m1une::math::repunit<Mint>(second_length, base);\n\
    \        const Mint combined = m1une::math::repunit<Mint>(\n            first_length\
    \ + second_length,\n            base\n        );\n        assert(combined == first\
    \ * power(base, second_length) + second);\n    }\n}\n\n}  // namespace\n\nint\
    \ main() {\n    fixed_tests();\n    exhaustive_tests();\n    randomized_tests();\n\
    \    runtime_modulus_tests();\n    minimum_length_tests();\n\n    long long a,\
    \ b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/repunit.hpp
  isVerificationFile: true
  path: verify/math/repunit.test.cpp
  requiredBy: []
  timestamp: '2026-07-03 15:39:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/repunit.test.cpp
layout: document
redirect_from:
- /verify/verify/math/repunit.test.cpp
- /verify/verify/math/repunit.test.cpp.html
title: verify/math/repunit.test.cpp
---
