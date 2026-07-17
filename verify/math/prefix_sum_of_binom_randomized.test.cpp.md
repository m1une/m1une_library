---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/combinatorics.hpp
    title: Combinatorics
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/prefix_sum_of_binom.hpp
    title: Prefix Sum of Binomial Coefficients
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
  bundledCode: "#line 1 \"verify/math/prefix_sum_of_binom_randomized.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/combinatorics.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <class Mint>\nstruct Combinatorics {\n\
    \   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint> _inverse_factorial;\n\
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
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
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
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/prefix_sum_of_binom.hpp\"\n\n\
    \n\n#include <algorithm>\n#line 6 \"math/prefix_sum_of_binom.hpp\"\n#include <cmath>\n\
    #line 8 \"math/prefix_sum_of_binom.hpp\"\n#include <numeric>\n#line 11 \"math/prefix_sum_of_binom.hpp\"\
    \n\n#line 13 \"math/prefix_sum_of_binom.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\n// Answers sum_{k=0}^{m-1} binom(n, k) after square-root decomposition.\n\
    template <class Mint>\nstruct PrefixSumOfBinom {\n   private:\n    int _maximum;\n\
    \    int _block_size;\n    Combinatorics<Mint> _combinations;\n    std::vector<Mint>\
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
    \ m1une\n\n\n#line 6 \"verify/math/prefix_sum_of_binom_randomized.test.cpp\"\n\
    \n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#line 15 \"utilities/fast_io.hpp\"\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/math/prefix_sum_of_binom_randomized.test.cpp\"\
    \n\nusing Mint = m1une::math::modint998244353;\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    constexpr\
    \ int maximum = 300;\n    m1une::math::Combinatorics<Mint> combinations(maximum);\n\
    \    m1une::math::PrefixSumOfBinom<Mint> online(maximum);\n    m1une::math::OfflinePrefixSumOfBinom<Mint>\
    \ offline;\n    std::vector<Mint> expected;\n    assert(online.maximum() == maximum);\n\
    \    assert(offline.empty());\n\n    for (int n = 0; n <= maximum; n++) {\n  \
    \      Mint sum = 0;\n        for (int m = 0; m <= n + 5; m++) {\n           \
    \ expected.push_back(sum);\n            assert(online.query(n, m) == sum);\n \
    \           assert(offline.add_query(n, m) == int(expected.size()) - 1);\n   \
    \         sum += combinations.binom(n, m);\n        }\n    }\n    assert(offline.query_count()\
    \ == int(expected.size()));\n    assert(offline.calculate() == expected);\n  \
    \  assert(offline.calculate() == expected);\n    offline.clear();\n    assert(offline.empty());\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/combinatorics.hpp\"\n#include \"../../math/modint.hpp\"\n#include \"\
    ../../math/prefix_sum_of_binom.hpp\"\n\n#include <cassert>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nusing Mint = m1une::math::modint998244353;\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    constexpr int maximum = 300;\n    m1une::math::Combinatorics<Mint>\
    \ combinations(maximum);\n    m1une::math::PrefixSumOfBinom<Mint> online(maximum);\n\
    \    m1une::math::OfflinePrefixSumOfBinom<Mint> offline;\n    std::vector<Mint>\
    \ expected;\n    assert(online.maximum() == maximum);\n    assert(offline.empty());\n\
    \n    for (int n = 0; n <= maximum; n++) {\n        Mint sum = 0;\n        for\
    \ (int m = 0; m <= n + 5; m++) {\n            expected.push_back(sum);\n     \
    \       assert(online.query(n, m) == sum);\n            assert(offline.add_query(n,\
    \ m) == int(expected.size()) - 1);\n            sum += combinations.binom(n, m);\n\
    \        }\n    }\n    assert(offline.query_count() == int(expected.size()));\n\
    \    assert(offline.calculate() == expected);\n    assert(offline.calculate()\
    \ == expected);\n    offline.clear();\n    assert(offline.empty());\n\n    long\
    \ long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - math/combinatorics.hpp
  - math/modint.hpp
  - math/prefix_sum_of_binom.hpp
  - math/combinatorics.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/prefix_sum_of_binom_randomized.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 04:56:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/prefix_sum_of_binom_randomized.test.cpp
layout: document
redirect_from:
- /verify/verify/math/prefix_sum_of_binom_randomized.test.cpp
- /verify/verify/math/prefix_sum_of_binom_randomized.test.cpp.html
title: verify/math/prefix_sum_of_binom_randomized.test.cpp
---
