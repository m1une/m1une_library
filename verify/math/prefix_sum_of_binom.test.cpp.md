---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':x:'
    path: math/prefix_sum_of_binom.hpp
    title: Prefix Sum of Binomial Coefficients
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2206
    links:
    - https://yukicoder.me/problems/no/2206
  bundledCode: "#line 1 \"verify/math/prefix_sum_of_binom.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/no/2206\"\n\n#line 1 \"math/modint.hpp\"\n\n\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\
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
    \n\n#line 1 \"math/prefix_sum_of_binom.hpp\"\n\n\n\n#include <algorithm>\n#line\
    \ 6 \"math/prefix_sum_of_binom.hpp\"\n#include <cmath>\n#line 8 \"math/prefix_sum_of_binom.hpp\"\
    \n#include <numeric>\n#line 10 \"math/prefix_sum_of_binom.hpp\"\n#include <vector>\n\
    \n#line 1 \"math/combinatorics.hpp\"\n\n\n\n#line 7 \"math/combinatorics.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <class Mint>\nstruct Combinatorics\
    \ {\n   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint> _inverse_factorial;\n\
    \n   public:\n    explicit Combinatorics(int maximum = 0) : _factorial(1, Mint(1)),\
    \ _inverse_factorial(1, Mint(1)) {\n        ensure(maximum);\n    }\n\n    int\
    \ maximum() const {\n        return int(_factorial.size()) - 1;\n    }\n\n   \
    \ void ensure(int maximum) {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
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
    \ 13 \"math/prefix_sum_of_binom.hpp\"\n\nnamespace m1une {\nnamespace math {\n\
    \n// Answers sum_{k=0}^{m-1} binom(n, k) after square-root decomposition.\ntemplate\
    \ <class Mint>\nstruct PrefixSumOfBinom {\n   private:\n    int _maximum;\n  \
    \  int _block_size;\n    Combinatorics<Mint> _combinations;\n    std::vector<Mint>\
    \ _powers_of_two;\n    std::vector<std::vector<Mint>> _data;\n\n    Mint _block_prefix(int\
    \ n, int block) const {\n        const int endpoint = block * _block_size;\n \
    \       if (n <= endpoint) return _powers_of_two[n];\n        return _data[block][n\
    \ - endpoint] * _combinations.inverse_factorial(endpoint);\n    }\n\n    Mint\
    \ _binom_sum(int n, int left, int right) const {\n        __uint128_t sum = 0;\n\
    \        for (int k = left; k < right; k++) {\n            sum += static_cast<__uint128_t>(_combinations.inverse_factorial(k).val())\
    \ *\n                   _combinations.inverse_factorial(n - k).val();\n      \
    \  }\n        const uint32_t reduced = static_cast<uint32_t>(sum % Mint::mod());\n\
    \        return Mint::raw(reduced) * _combinations.factorial(n);\n    }\n\n  \
    \ public:\n    explicit PrefixSumOfBinom(int maximum)\n        : _maximum(maximum),\n\
    \          _block_size(std::max(1, int(std::sqrt(static_cast<double>(maximum)\
    \ + 1)))),\n          _combinations(maximum),\n          _powers_of_two(maximum\
    \ + 1, Mint(1)) {\n        assert(maximum >= 0);\n\n        for (int n = 0; n\
    \ < maximum; n++) {\n            _powers_of_two[n + 1] = _powers_of_two[n] + _powers_of_two[n];\n\
    \        }\n\n        const int block_count = maximum / (2 * _block_size) + 3;\n\
    \        _data.resize(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int endpoint = block * _block_size;\n        \
    \    if (endpoint > maximum) continue;\n\n            std::vector<Mint>& values\
    \ = _data[block];\n            values.resize(maximum - endpoint + 1);\n      \
    \      values[0] = _powers_of_two[endpoint] * _combinations.factorial(endpoint);\n\
    \            for (int offset = 0; offset < maximum - endpoint; offset++) {\n \
    \               values[offset + 1] =\n                    values[offset] + values[offset]\
    \ -\n                    _combinations.factorial(offset + endpoint) *\n      \
    \                  _combinations.inverse_factorial(offset);\n            }\n \
    \       }\n    }\n\n    int maximum() const {\n        return _maximum;\n    }\n\
    \n    // Returns sum_{k=0}^{m-1} binom(n, k). Values m > n + 1 are clamped.\n\
    \    Mint query(int n, int m) const {\n        assert(0 <= n && n <= _maximum);\n\
    \        assert(m >= 0);\n        m = std::min(m, n + 1);\n        if (m == 0)\
    \ return Mint(0);\n        if (2 * m > n + 1) {\n            return _powers_of_two[n]\
    \ - query(n, n + 1 - m);\n        }\n\n        const int endpoint = m - 1;\n \
    \       const int block = endpoint / _block_size;\n        const int lower = block\
    \ * _block_size;\n        const int upper = (block + 1) * _block_size;\n     \
    \   if (endpoint - lower <= upper - endpoint) {\n            return _block_prefix(n,\
    \ block) + _binom_sum(n, lower + 1, endpoint + 1);\n        }\n        return\
    \ _block_prefix(n, block + 1) - _binom_sum(n, endpoint + 1, upper + 1);\n    }\n\
    };\n\n// Batches the same queries and evaluates them in Mo order with linear memory.\n\
    template <class Mint>\nstruct OfflinePrefixSumOfBinom {\n   private:\n    std::vector<std::pair<int,\
    \ int>> _queries;\n\n   public:\n    int query_count() const {\n        return\
    \ int(_queries.size());\n    }\n\n    bool empty() const {\n        return _queries.empty();\n\
    \    }\n\n    void reserve(int query_capacity) {\n        assert(query_capacity\
    \ >= 0);\n        _queries.reserve(query_capacity);\n    }\n\n    void clear()\
    \ {\n        _queries.clear();\n    }\n\n    // Adds sum_{k=0}^{m-1} binom(n,\
    \ k) and returns its insertion-order ID.\n    int add_query(int n, int m) {\n\
    \        assert(n >= 0);\n        assert(m >= 0);\n        m = std::min(m, n +\
    \ 1);\n        const int id = query_count();\n        _queries.emplace_back(n,\
    \ m);\n        return id;\n    }\n\n    std::vector<Mint> calculate() const {\n\
    \        const int count = query_count();\n        std::vector<Mint> answers(count);\n\
    \        if (count == 0) return answers;\n\n        int maximum = 0;\n       \
    \ for (const auto& query : _queries) maximum = std::max(maximum, query.first);\n\
    \        assert(static_cast<uint64_t>(maximum) < Mint::mod());\n        assert(Mint::mod()\
    \ % 2 == 1);\n        Combinatorics<Mint> combinations(maximum);\n\n        const\
    \ int block_size =\n            std::max(1, int(maximum / std::sqrt(static_cast<double>(count))));\n\
    \        std::vector<int> order(count);\n        std::iota(order.begin(), order.end(),\
    \ 0);\n        std::sort(order.begin(), order.end(), [&](int first, int second)\
    \ {\n            const int first_block = _queries[first].first / block_size;\n\
    \            const int second_block = _queries[second].first / block_size;\n \
    \           if (first_block != second_block) return first_block < second_block;\n\
    \            if (first_block & 1) return _queries[first].second > _queries[second].second;\n\
    \            return _queries[first].second < _queries[second].second;\n      \
    \  });\n\n        int n = 0;\n        int m = 0;\n        Mint answer = 0;\n \
    \       const Mint inverse_two = Mint(2).inv();\n        for (int id : order)\
    \ {\n            const int next_n = _queries[id].first;\n            const int\
    \ next_m = _queries[id].second;\n            while (n < next_n) {\n          \
    \      answer += answer;\n                answer -= combinations.binom(n, m -\
    \ 1);\n                n++;\n            }\n            while (n > next_n) {\n\
    \                answer += combinations.binom(n - 1, m - 1);\n               \
    \ answer *= inverse_two;\n                n--;\n            }\n            while\
    \ (m < next_m) answer += combinations.binom(n, m++);\n            while (m > next_m)\
    \ answer -= combinations.binom(n, --m);\n            answers[id] = answer;\n \
    \       }\n        return answers;\n    }\n};\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 5 \"verify/math/prefix_sum_of_binom.test.cpp\"\n\n#line 9 \"\
    verify/math/prefix_sum_of_binom.test.cpp\"\n\nusing Mint = m1une::math::modint998244353;\n\
    \nint main() {\n    int test_count;\n    std::cin >> test_count;\n    std::vector<std::pair<int,\
    \ int>> queries(test_count);\n    for (auto& query : queries) {\n        std::cin\
    \ >> query.first >> query.second;\n    }\n\n    m1une::math::OfflinePrefixSumOfBinom<Mint>\
    \ prefix;\n    prefix.reserve(test_count);\n    for (const auto& query : queries)\
    \ {\n        prefix.add_query(query.first - 1, query.second);\n    }\n    const\
    \ std::vector<Mint> answers = prefix.calculate();\n\n    for (int i = 0; i < test_count;\
    \ i++) {\n        const int n = queries[i].first;\n        std::cout << answers[i]\
    \ * (Mint(2).pow(n) - Mint(1)) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2206\"\n\n#include \"\
    ../../math/modint.hpp\"\n#include \"../../math/prefix_sum_of_binom.hpp\"\n\n#include\
    \ <iostream>\n#include <utility>\n#include <vector>\n\nusing Mint = m1une::math::modint998244353;\n\
    \nint main() {\n    int test_count;\n    std::cin >> test_count;\n    std::vector<std::pair<int,\
    \ int>> queries(test_count);\n    for (auto& query : queries) {\n        std::cin\
    \ >> query.first >> query.second;\n    }\n\n    m1une::math::OfflinePrefixSumOfBinom<Mint>\
    \ prefix;\n    prefix.reserve(test_count);\n    for (const auto& query : queries)\
    \ {\n        prefix.add_query(query.first - 1, query.second);\n    }\n    const\
    \ std::vector<Mint> answers = prefix.calculate();\n\n    for (int i = 0; i < test_count;\
    \ i++) {\n        const int n = queries[i].first;\n        std::cout << answers[i]\
    \ * (Mint(2).pow(n) - Mint(1)) << '\\n';\n    }\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/prefix_sum_of_binom.hpp
  - math/combinatorics.hpp
  isVerificationFile: true
  path: verify/math/prefix_sum_of_binom.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/math/prefix_sum_of_binom.test.cpp
layout: document
redirect_from:
- /verify/verify/math/prefix_sum_of_binom.test.cpp
- /verify/verify/math/prefix_sum_of_binom.test.cpp.html
title: verify/math/prefix_sum_of_binom.test.cpp
---
