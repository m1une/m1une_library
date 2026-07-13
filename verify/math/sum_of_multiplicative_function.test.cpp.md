---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/multiplicative_function_prefix_sum.hpp
    title: Multiplicative Function Prefix Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_multiplicative_function
    links:
    - https://judge.yosupo.jp/problem/sum_of_multiplicative_function
  bundledCode: "#line 1 \"verify/math/sum_of_multiplicative_function.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_multiplicative_function\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \n#line 1 \"math/modint.hpp\"\n\n\n\n#line 7 \"math/modint.hpp\"\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t\
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
    \n\n#line 1 \"math/multiplicative_function_prefix_sum.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 6 \"math/multiplicative_function_prefix_sum.hpp\"\n#include <cmath>\n#line\
    \ 8 \"math/multiplicative_function_prefix_sum.hpp\"\n#include <limits>\n#line\
    \ 11 \"math/multiplicative_function_prefix_sum.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\n// Computes summatory multiplicative functions with a Min_25 sieve.\n\
    // prime_power(p, e) must return f(p^e), and prime_prefix must contain\n// sum_{p\
    \ <= x} f(p) at every x represented by quotient_values().\ntemplate <class T,\
    \ class PrimePower>\nstruct MultiplicativeFunctionPrefixSum {\n   private:\n \
    \   uint64_t _n;\n    uint64_t _sqrt_n;\n    uint64_t _large_size;\n    std::vector<int>\
    \ _primes;\n    PrimePower _prime_power;\n\n    static uint64_t integer_sqrt(uint64_t\
    \ n) {\n        uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long\
    \ double>(n)));\n        while (result != 0 && result > n / result) result--;\n\
    \        while (result + 1 <= n / (result + 1)) result++;\n        return result;\n\
    \    }\n\n    static uint64_t validated_sqrt(uint64_t n) {\n        const uint64_t\
    \ result = integer_sqrt(n);\n        assert(result <= static_cast<uint64_t>(std::numeric_limits<int>::max()\
    \ / 2));\n        return result;\n    }\n\n    static std::vector<int> enumerate_primes(uint64_t\
    \ limit) {\n        assert(limit <= static_cast<uint64_t>(std::numeric_limits<int>::max()));\n\
    \        const int n = static_cast<int>(limit);\n        std::vector<bool> is_composite(n\
    \ + 1);\n        std::vector<int> primes;\n        for (int value = 2; value <=\
    \ n; value++) {\n            if (!is_composite[value]) primes.push_back(value);\n\
    \            for (int prime : primes) {\n                if (value > n / prime)\
    \ break;\n                is_composite[value * prime] = true;\n              \
    \  if (value % prime == 0) break;\n            }\n        }\n        return primes;\n\
    \    }\n\n    T triangular(uint64_t n) const {\n        if ((n & 1) == 0) return\
    \ T(n / 2) * T(n + 1);\n        return T(n) * T((n + 1) / 2);\n    }\n\n   public:\n\
    \    explicit MultiplicativeFunctionPrefixSum(uint64_t n, PrimePower prime_power)\n\
    \        : _n(n),\n          _sqrt_n(validated_sqrt(n)),\n          _large_size(n\
    \ == 0 ? 0 : n / _sqrt_n),\n          _primes(enumerate_primes(_sqrt_n)),\n  \
    \        _prime_power(std::move(prime_power)) {\n        if (n == 0) return;\n\
    \        while (_large_size > 1 && n / (_large_size - 1) == _sqrt_n) _large_size--;\n\
    \    }\n\n    uint64_t n() const {\n        return _n;\n    }\n\n    uint64_t\
    \ sqrt_n() const {\n        return _sqrt_n;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    int table_size() const\
    \ {\n        if (_n == 0) return 0;\n        return static_cast<int>(_large_size\
    \ + _sqrt_n);\n    }\n\n    // Returns the table index representing x. The argument\
    \ must be one of the\n    // values returned by quotient_values().\n    int index(uint64_t\
    \ x) const {\n        assert(_n > 0 && 1 <= x && x <= _n);\n        if (x <= _sqrt_n)\
    \ return table_size() - static_cast<int>(x);\n        const uint64_t result =\
    \ _n / x;\n        assert(result < _large_size);\n        return static_cast<int>(result);\n\
    \    }\n\n    // table[i] represents the value at quotient_values()[i]. Index\
    \ zero is a\n    // dummy entry; the represented values occupy indices [1, table_size()).\n\
    \    std::vector<uint64_t> quotient_values() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> result(table_size());\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) result[i] = _n / i;\n        for (uint64_t value\
    \ = 1; value <= _sqrt_n; value++) {\n            result[index(value)] = value;\n\
    \        }\n        return result;\n    }\n\n    // Returns pi(x) at every represented\
    \ x.\n    std::vector<T> prime_count_table() const {\n        if (_n == 0) return\
    \ {};\n        std::vector<uint64_t> large(_large_size);\n        for (uint64_t\
    \ i = 1; i < _large_size; i++) large[i] = _n / i - 1;\n\n        std::vector<uint64_t>\
    \ small(_sqrt_n + 1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++)\
    \ small[value] = value - 1;\n\n        uint64_t prime_count = 0;\n        for\
    \ (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const uint64_t\
    \ end = std::min(_large_size, _n / square + 1);\n            uint64_t product\
    \ = prime;\n            for (uint64_t i = 1; i < end; i++, product += prime) {\n\
    \                const uint64_t previous = product < _large_size ? large[product]\
    \ : small[_n / product];\n                large[i] -= previous - prime_count;\n\
    \            }\n            for (uint64_t value = _sqrt_n; value >= square; value--)\
    \ {\n                small[value] -= small[value / prime] - prime_count;\n   \
    \         }\n            prime_count++;\n        }\n\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 0; i < _large_size; i++) result[i] = T(large[i]);\n\
    \        for (uint64_t value = 1; value <= _sqrt_n; value++) result[index(value)]\
    \ = T(small[value]);\n        return result;\n    }\n\n    // Returns sum_{p <=\
    \ x} p at every represented x.\n    std::vector<T> prime_sum_table() const {\n\
    \        if (_n == 0) return {};\n        std::vector<T> result(table_size());\n\
    \        for (uint64_t i = 1; i < _large_size; i++) result[i] = triangular(_n\
    \ / i) - T(1);\n        for (uint64_t value = 1; value <= _sqrt_n; value++) {\n\
    \            result[index(value)] = triangular(value) - T(1);\n        }\n\n \
    \       for (int prime_int : _primes) {\n            const uint64_t prime = static_cast<uint64_t>(prime_int);\n\
    \            const uint64_t square = prime * prime;\n            const T before\
    \ = result[index(prime - 1)];\n            const uint64_t end = std::min(_large_size,\
    \ _n / square + 1);\n            uint64_t product = prime;\n            for (uint64_t\
    \ i = 1; i < end; i++, product += prime) {\n                result[i] -= (result[index(_n\
    \ / product)] - before) * T(prime);\n            }\n            for (uint64_t\
    \ value = _sqrt_n; value >= square; value--) {\n                result[index(value)]\
    \ -= (result[index(value / prime)] - before) * T(prime);\n            }\n    \
    \    }\n        return result;\n    }\n\n    // Returns sum_{k=1}^x f(k) at every\
    \ represented x.\n    std::vector<T> prefix_sum_table(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return {};\n        }\n        assert(static_cast<int>(prime_prefix.size())\
    \ == table_size());\n\n        const std::vector<uint64_t> values = quotient_values();\n\
    \        std::vector<T> result = prime_prefix;\n        std::vector<T> next =\
    \ prime_prefix;\n        for (int prime_index = static_cast<int>(_primes.size())\
    \ - 1; prime_index >= 0; prime_index--) {\n            const uint64_t prime =\
    \ static_cast<uint64_t>(_primes[prime_index]);\n            uint64_t power = prime;\n\
    \            int exponent = 1;\n            while (power <= _n / prime) {\n  \
    \              const T current_value = _prime_power(prime, exponent);\n      \
    \          const T next_value = _prime_power(prime, exponent + 1);\n         \
    \       const T primes_before = prime_prefix[index(prime)];\n                for\
    \ (int i = 1; i < table_size(); i++) {\n                    const uint64_t value\
    \ = values[i];\n                    if (value < power * prime) break;\n      \
    \              next[i] += current_value * (result[index(value / power)] - primes_before)\
    \ + next_value;\n                }\n                exponent++;\n            \
    \    power *= prime;\n            }\n            const uint64_t bound = prime\
    \ * prime;\n            const int copy_size = std::min(table_size(), index(bound)\
    \ + 1);\n            std::copy(next.begin(), next.begin() + copy_size, result.begin());\n\
    \        }\n        for (int i = 1; i < table_size(); i++) result[i] += T(1);\n\
    \        return result;\n    }\n\n    T prefix_sum(const std::vector<T>& prime_prefix)\
    \ const {\n        if (_n == 0) {\n            assert(prime_prefix.empty());\n\
    \            return T{};\n        }\n        return prefix_sum_table(prime_prefix)[index(_n)];\n\
    \    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 10 \"verify/math/sum_of_multiplicative_function.test.cpp\"\
    \n\nusing Mint = m1une::math::ModInt<469762049>;\n\nMint solve(uint64_t n, Mint\
    \ a, Mint b) {\n    auto prime_power = [a, b](uint64_t prime, int exponent) {\n\
    \        return a * Mint(exponent) + b * Mint(prime);\n    };\n    m1une::math::MultiplicativeFunctionPrefixSum<Mint,\
    \ decltype(prime_power)> solver(n, prime_power);\n    std::vector<Mint> prime_prefix\
    \ = solver.prime_count_table();\n    const std::vector<Mint> prime_sum = solver.prime_sum_table();\n\
    \    for (int i = 0; i < solver.table_size(); i++) {\n        prime_prefix[i]\
    \ = a * prime_prefix[i] + b * prime_sum[i];\n    }\n    return solver.prefix_sum(prime_prefix);\n\
    }\n\nvoid test_small() {\n    for (uint64_t n = 0; n <= 300; n++) {\n        for\
    \ (uint32_t a = 0; a <= 3; a++) {\n            for (uint32_t b = 0; b <= 3; b++)\
    \ {\n                std::vector<Mint> function(n + 1, Mint(1));\n           \
    \     std::vector<int> min_prime(n + 1);\n                for (uint64_t value\
    \ = 2; value <= n; value++) {\n                    if (min_prime[value] == 0)\
    \ {\n                        for (uint64_t multiple = value; multiple <= n; multiple\
    \ += value) {\n                            if (min_prime[multiple] == 0) min_prime[multiple]\
    \ = static_cast<int>(value);\n                        }\n                    }\n\
    \                    uint64_t reduced = value;\n                    int exponent\
    \ = 0;\n                    while (reduced % static_cast<uint64_t>(min_prime[value])\
    \ == 0) {\n                        reduced /= static_cast<uint64_t>(min_prime[value]);\n\
    \                        exponent++;\n                    }\n                \
    \    function[value] = function[reduced] *\n                                 \
    \     (Mint(a) * Mint(exponent) + Mint(b) * Mint(min_prime[value]));\n       \
    \         }\n                Mint expected = 0;\n                for (uint64_t\
    \ value = 1; value <= n; value++) expected += function[value];\n             \
    \   assert(solve(n, Mint(a), Mint(b)) == expected);\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_small();\n\n    int test_count;\n    std::cin >> test_count;\n    while\
    \ (test_count--) {\n        uint64_t n;\n        Mint a, b;\n        std::cin\
    \ >> n >> a >> b;\n        std::cout << solve(n, a, b) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_multiplicative_function\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \n#include \"../../math/modint.hpp\"\n#include \"../../math/multiplicative_function_prefix_sum.hpp\"\
    \n\nusing Mint = m1une::math::ModInt<469762049>;\n\nMint solve(uint64_t n, Mint\
    \ a, Mint b) {\n    auto prime_power = [a, b](uint64_t prime, int exponent) {\n\
    \        return a * Mint(exponent) + b * Mint(prime);\n    };\n    m1une::math::MultiplicativeFunctionPrefixSum<Mint,\
    \ decltype(prime_power)> solver(n, prime_power);\n    std::vector<Mint> prime_prefix\
    \ = solver.prime_count_table();\n    const std::vector<Mint> prime_sum = solver.prime_sum_table();\n\
    \    for (int i = 0; i < solver.table_size(); i++) {\n        prime_prefix[i]\
    \ = a * prime_prefix[i] + b * prime_sum[i];\n    }\n    return solver.prefix_sum(prime_prefix);\n\
    }\n\nvoid test_small() {\n    for (uint64_t n = 0; n <= 300; n++) {\n        for\
    \ (uint32_t a = 0; a <= 3; a++) {\n            for (uint32_t b = 0; b <= 3; b++)\
    \ {\n                std::vector<Mint> function(n + 1, Mint(1));\n           \
    \     std::vector<int> min_prime(n + 1);\n                for (uint64_t value\
    \ = 2; value <= n; value++) {\n                    if (min_prime[value] == 0)\
    \ {\n                        for (uint64_t multiple = value; multiple <= n; multiple\
    \ += value) {\n                            if (min_prime[multiple] == 0) min_prime[multiple]\
    \ = static_cast<int>(value);\n                        }\n                    }\n\
    \                    uint64_t reduced = value;\n                    int exponent\
    \ = 0;\n                    while (reduced % static_cast<uint64_t>(min_prime[value])\
    \ == 0) {\n                        reduced /= static_cast<uint64_t>(min_prime[value]);\n\
    \                        exponent++;\n                    }\n                \
    \    function[value] = function[reduced] *\n                                 \
    \     (Mint(a) * Mint(exponent) + Mint(b) * Mint(min_prime[value]));\n       \
    \         }\n                Mint expected = 0;\n                for (uint64_t\
    \ value = 1; value <= n; value++) expected += function[value];\n             \
    \   assert(solve(n, Mint(a), Mint(b)) == expected);\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_small();\n\n    int test_count;\n    std::cin >> test_count;\n    while\
    \ (test_count--) {\n        uint64_t n;\n        Mint a, b;\n        std::cin\
    \ >> n >> a >> b;\n        std::cout << solve(n, a, b) << '\\n';\n    }\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/multiplicative_function_prefix_sum.hpp
  isVerificationFile: true
  path: verify/math/sum_of_multiplicative_function.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/sum_of_multiplicative_function.test.cpp
layout: document
redirect_from:
- /verify/verify/math/sum_of_multiplicative_function.test.cpp
- /verify/verify/math/sum_of_multiplicative_function.test.cpp.html
title: verify/math/sum_of_multiplicative_function.test.cpp
---
