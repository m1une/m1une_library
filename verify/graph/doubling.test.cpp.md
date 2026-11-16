---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/doubling.hpp
    title: Doubling with Monoid Aggregates
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/affine.hpp
    title: Affine Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"verify/graph/doubling.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\
    \n\n#line 1 \"graph/doubling.hpp\"\n\n\n\n#include <algorithm>\n#include <bit>\n\
    #include <cassert>\n#include <cstddef>\n#include <cstdint>\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 13 \"graph/doubling.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\n// Static binary lifting with ordered aggregates. A step\
    \ collects values[v]\n// before moving to successor[v]. State -1 stays at -1 and\
    \ contributes id().\ntemplate <m1une::monoid::IsMonoid Monoid>\nclass Doubling\
    \ {\n   public:\n    using value_type = typename Monoid::value_type;\n\n    struct\
    \ Result {\n        int vertex;\n        value_type product;\n    };\n\n   private:\n\
    \    int _n = 0;\n    int _levels = 0;\n    std::uint64_t _max_steps = 0;\n  \
    \  // Level-major flat tables: the entry at (bit, v) describes 2^bit steps.\n\
    \    std::vector<int> _next;\n    std::vector<value_type> _products;\n\n    void\
    \ check_query(int vertex, std::uint64_t steps) const {\n        assert(-1 <= vertex\
    \ && vertex < _n);\n        assert(steps <= _max_steps);\n        (void)vertex;\n\
    \        (void)steps;\n    }\n\n   public:\n    Doubling() = default;\n\n    Doubling(const\
    \ std::vector<int>& successor, const std::vector<value_type>& values,\n      \
    \       std::uint64_t max_steps) {\n        build(successor, values, max_steps);\n\
    \    }\n\n    void build(const std::vector<int>& successor, const std::vector<value_type>&\
    \ values,\n               std::uint64_t max_steps) {\n        assert(successor.size()\
    \ == values.size());\n        assert(successor.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \        const int n = int(successor.size());\n        for (int to : successor)\
    \ {\n            assert(-1 <= to && to < n);\n            (void)to;\n        }\n\
    \        _n = n;\n        _levels = std::bit_width(max_steps);\n        _max_steps\
    \ = max_steps;\n        assert(_levels == 0 || std::size_t(n) <=\n           \
    \        std::numeric_limits<std::size_t>::max() / std::size_t(_levels));\n  \
    \      const std::size_t total = std::size_t(n) * std::size_t(_levels);\n    \
    \    _next = std::vector<int>(total, -1);\n        _products = std::vector<value_type>(total,\
    \ Monoid::id());\n        if (_levels == 0) return;\n\n        std::copy(successor.begin(),\
    \ successor.end(), _next.begin());\n        std::copy(values.begin(), values.end(),\
    \ _products.begin());\n        for (int bit = 1; bit < _levels; ++bit) {\n   \
    \         const std::size_t previous = std::size_t(bit - 1) * std::size_t(n);\n\
    \            const std::size_t current = previous + std::size_t(n);\n        \
    \    for (int vertex = 0; vertex < n; ++vertex) {\n                const int middle\
    \ = _next[previous + vertex];\n                if (middle == -1) {\n         \
    \           _products[current + vertex] = _products[previous + vertex];\n    \
    \            } else {\n                    _next[current + vertex] = _next[previous\
    \ + middle];\n                    _products[current + vertex] = Monoid::op(\n\
    \                        _products[previous + vertex], _products[previous + middle]);\n\
    \                }\n            }\n        }\n    }\n\n    int size() const {\
    \ return _n; }\n\n    bool empty() const { return _n == 0; }\n\n    int levels()\
    \ const { return _levels; }\n\n    std::uint64_t max_steps() const { return _max_steps;\
    \ }\n\n    int jump(int vertex, std::uint64_t steps) const {\n        check_query(vertex,\
    \ steps);\n        while (steps != 0 && vertex != -1) {\n            const int\
    \ bit = std::countr_zero(steps);\n            vertex = _next[std::size_t(bit)\
    \ * std::size_t(_n) + vertex];\n            steps &= steps - 1;\n        }\n \
    \       return vertex;\n    }\n\n    Result walk(int vertex, std::uint64_t steps)\
    \ const {\n        check_query(vertex, steps);\n        Result result{vertex,\
    \ Monoid::id()};\n        while (steps != 0 && result.vertex != -1) {\n      \
    \      const int bit = std::countr_zero(steps);\n            const std::size_t\
    \ index = std::size_t(bit) * std::size_t(_n) + result.vertex;\n            result.product\
    \ = Monoid::op(result.product, _products[index]);\n            result.vertex =\
    \ _next[index];\n            steps &= steps - 1;\n        }\n        return result;\n\
    \    }\n\n    value_type prod(int vertex, std::uint64_t steps) const {\n     \
    \   return walk(vertex, steps).product;\n    }\n};\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/graph/doubling.test.cpp\"\n\n#line\
    \ 8 \"verify/graph/doubling.test.cpp\"\n#include <string>\n#include <utility>\n\
    #line 11 \"verify/graph/doubling.test.cpp\"\n\n#line 1 \"math/modint.hpp\"\n\n\
    \n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n\
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
    \ math\n}  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate\
    \ <typename T>\nstruct Add {\n    using value_type = T;\n    static constexpr\
    \ bool commutative = true;\n\n    // Returns the identity element for addition,\
    \ which is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n\
    \    // Returns the sum of a and b.\n    static constexpr T op(const T& a, const\
    \ T& b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T&\
    \ x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/affine.hpp\"\n\n\n\n#line 5 \"monoid/affine.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for affine transformations\
    \ f(x) = ax + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct\
    \ Affine {\n    using value_type = std::pair<T, T>;\n    static constexpr bool\
    \ commutative = false;\n\n    // The identity transformation is f(x) = 1*x + 0.\n\
    \    static constexpr value_type id() {\n        return {T(1), T(0)};\n    }\n\
    \n    // Composes two affine transformations.\n    // f(g(x)) where f = a, g =\
    \ b.\n    // a.first * (b.first * x + b.second) + a.second\n    // = (a.first\
    \ * b.first) * x + (a.first * b.second + a.second)\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.first * b.first,\
    \ a.first * b.second + a.second};\n    }\n\n    // Helpers to create common affine\
    \ transformations\n    static constexpr value_type make_add(const T& b) {\n  \
    \      return {T(1), b};\n    }\n    static constexpr value_type make_mul(const\
    \ T& a) {\n        return {a, T(0)};\n    }\n    static constexpr value_type make_assign(const\
    \ T& b) {\n        return {T(0), b};\n    }\n};\n\n}  // namespace monoid\n} \
    \ // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"\
    utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#line\
    \ 15 \"utilities/fast_io.hpp\"\n#include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n#line 20 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\n\
    namespace utilities {\n\nstruct FastOutput;\n\nnamespace internal {\n\n// Shared\
    \ with the convenience helpers in template.hpp.\ninline FastOutput* standard_output_instance\
    \ = nullptr;\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class\
    \ = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\nstruct\
    \ is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n  \
    \  decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
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
    \    char _range_separator;\n    std::string* _capture = nullptr;\n\n    template\
    \ <class T>\n    std::string format_cell(const T& value) {\n        std::string\
    \ result;\n        struct CaptureGuard {\n            std::string*& target;\n\
    \            std::string* previous;\n            ~CaptureGuard() { target = previous;\
    \ }\n        } guard{_capture, _capture};\n        _capture = &result;\n     \
    \   write(value);\n        return result;\n    }\n\n    template <class Matrix>\n\
    \    void write_aligned_matrix(const Matrix& matrix) {\n        std::vector<std::vector<std::string>>\
    \ rows;\n        std::vector<std::size_t> widths;\n        for (const auto& row\
    \ : matrix) {\n            auto& cells = rows.emplace_back();\n            std::size_t\
    \ column = 0;\n            for (const auto& value : row) {\n                cells.push_back(format_cell(value));\n\
    \                if (column == widths.size()) widths.push_back(0);\n         \
    \       widths[column] = std::max(widths[column], cells.back().size());\n    \
    \            ++column;\n            }\n        }\n        bool first = true;\n\
    \        for (const auto& row : rows) {\n            if (!first) write_char('\\\
    n');\n            first = false;\n            for (std::size_t column = 0; column\
    \ < row.size(); ++column) {\n                if (column != 0) write_char(_range_separator);\n\
    \                for (std::size_t padding = row[column].size();\n            \
    \         padding < widths[column]; ++padding) {\n                    write_char('\
    \ ');\n                }\n                write(row[column]);\n            }\n\
    \        }\n    }\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream),\n          _position(0),\n          _precision(6),\n\
    \          _float_format(std::chars_format::general),\n          _range_separator('\
    \ ') {\n        if (_stream == stdout\n            && internal::standard_output_instance\
    \ == nullptr) {\n            internal::standard_output_instance = this;\n    \
    \    }\n    }\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \        if (internal::standard_output_instance == this) {\n            internal::standard_output_instance\
    \ = nullptr;\n        }\n    }\n\n    void flush() {\n        if (_position !=\
    \ 0) {\n            std::fwrite(_buffer, 1, _position, _stream);\n           \
    \ _position = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void\
    \ write_char(char c) {\n        if (_capture != nullptr) {\n            _capture->push_back(c);\n\
    \            return;\n        }\n        if (_position == buffer_size) flush();\n\
    \        _buffer[_position++] = c;\n    }\n\n    void write(const char* s) {\n\
    \        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        if (_capture != nullptr) {\n            _capture->append(s);\n\
    \            return;\n        }\n        std::size_t position = 0;\n        while\
    \ (position < s.size()) {\n            if (_position == buffer_size) flush();\n\
    \            const std::size_t copied =\n                std::min<std::size_t>(buffer_size\
    \ - _position, s.size() - position);\n            std::memcpy(_buffer + _position,\
    \ s.data() + position, copied);\n            _position += int(copied);\n     \
    \       position += copied;\n        }\n    }\n\n    void write(char c) {\n  \
    \      write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
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
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_capture\
    \ == nullptr && _position > buffer_size - 64) flush();\n        char captured[64];\n\
    \        char* const begin = _capture != nullptr ? captured : _buffer + _position;\n\
    \        char* destination = begin;\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) *destination++ = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(destination, digits, 4);\n            destination +=\
    \ 4;\n        }\n        if (_capture != nullptr) {\n            _capture->append(begin,\
    \ destination - begin);\n        } else {\n            _position += int(destination\
    \ - begin);\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
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
    \    _range_separator = separator;\n    }\n\n    template <class Matrix>\n   \
    \ void write_aligned(const Matrix& matrix) {\n        using Row = internal::range_stored_value_t<const\
    \ Matrix>;\n        using Cell = internal::range_stored_value_t<const Row>;\n\
    \        static_assert(internal::is_range_v<Row> && !internal::is_string_like_v<Row>,\n\
    \                      \"write_aligned requires a two-dimensional range\");\n\
    \        static_assert(!internal::is_range_v<Cell> || internal::is_string_like_v<Cell>,\n\
    \                      \"write_aligned requires scalar cells\");\n        write_aligned_matrix(matrix);\n\
    \    }\n\n    template <class Matrix>\n    void println_aligned(const Matrix&\
    \ matrix) {\n        write_aligned(matrix);\n        write_char('\\n');\n    }\n\
    \n    template <class... Args>\n    void println(const Args&... args) {\n    \
    \    print(args...);\n        write_char('\\n');\n    }\n\n    template <class\
    \ T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n  \
    \      return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 16 \"verify/graph/doubling.test.cpp\"\n\nnamespace {\n\ntemplate\
    \ <class Monoid>\nvoid check_walk(const m1une::graph::Doubling<Monoid>& doubling,\n\
    \                const std::vector<int>& successor,\n                const std::vector<typename\
    \ Monoid::value_type>& values,\n                int start, std::uint64_t steps)\
    \ {\n    int vertex = start;\n    auto product = Monoid::id();\n    for (std::uint64_t\
    \ step = 0; step < steps && vertex != -1; ++step) {\n        product = Monoid::op(product,\
    \ values[vertex]);\n        vertex = successor[vertex];\n    }\n    auto result\
    \ = doubling.walk(start, steps);\n    assert(result.vertex == vertex);\n    assert(result.product\
    \ == product);\n    assert(doubling.jump(start, steps) == vertex);\n    assert(doubling.prod(start,\
    \ steps) == product);\n}\n\nstruct Concat {\n    using value_type = std::string;\n\
    \    static value_type id() { return \"\"; }\n    static value_type op(const value_type&\
    \ a, const value_type& b) { return a + b; }\n};\n\nstruct Box {\n    int value;\n\
    \    explicit Box(int x) : value(x) {}\n};\n\nstruct BoxAdd {\n    using value_type\
    \ = Box;\n    static Box id() { return Box(0); }\n    static Box op(const Box&\
    \ a, const Box& b) { return Box(a.value + b.value); }\n};\n\nvoid test_boundaries()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    m1une::graph::Doubling<Sum>\
    \ empty;\n    assert(empty.empty() && empty.size() == 0);\n    assert(empty.levels()\
    \ == 0 && empty.max_steps() == 0);\n    assert(empty.jump(-1, 0) == -1 && empty.prod(-1,\
    \ 0) == 0);\n\n    std::vector<int> successor = {1, 2, -1};\n    std::vector<long\
    \ long> values = {2, 5, 9};\n    m1une::graph::Doubling<Sum> chain(successor,\
    \ values, 100);\n    auto zero = chain.walk(0, 0);\n    assert(zero.vertex ==\
    \ 0 && zero.product == 0);\n    auto before_exit = chain.walk(0, 2);\n    assert(before_exit.vertex\
    \ == 2 && before_exit.product == 7);\n    auto exit = chain.walk(0, 3);\n    assert(exit.vertex\
    \ == -1 && exit.product == 16);\n    assert(chain.jump(0, 100) == -1 && chain.prod(0,\
    \ 100) == 16);\n    assert(chain.walk(-1, 100).product == 0);\n    assert(chain.size()\
    \ == 3 && chain.levels() == 7 && chain.max_steps() == 100);\n\n    chain.build(successor,\
    \ values, 0);\n    assert(chain.levels() == 0 && chain.jump(2, 0) == 2);\n   \
    \ assert(chain.prod(1, 0) == 0);\n    chain.build(std::vector<int>{0}, std::vector<long\
    \ long>{3}, 16);\n    assert(chain.levels() == 5 && chain.prod(0, 16) == 48);\n\
    \    auto copied = chain;\n    chain.build(std::vector<int>{-1}, std::vector<long\
    \ long>{8}, 1);\n    assert(chain.prod(0, 1) == 8 && copied.prod(0, 16) == 48);\n\
    \    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();\n\
    \    chain.build(std::vector<int>{}, std::vector<long long>{}, maximum);\n   \
    \ assert(chain.empty() && chain.levels() == 64);\n    assert(chain.walk(-1, maximum).vertex\
    \ == -1 && chain.prod(-1, maximum) == 0);\n\n    std::vector<Box> boxes;\n   \
    \ boxes.emplace_back(3);\n    boxes.emplace_back(8);\n    m1une::graph::Doubling<BoxAdd>\
    \ boxed(std::vector<int>{1, -1}, boxes, 4);\n    assert(boxed.prod(0, 4).value\
    \ == 11);  // No default constructor or equality is needed.\n\n    using Mint\
    \ = m1une::math::modint998244353;\n    using Affine = m1une::monoid::Affine<Mint>;\n\
    \    std::vector<Affine::value_type> functions;\n    functions.emplace_back(2,\
    \ 3);\n    functions.emplace_back(5, 7);\n    m1une::graph::Doubling<Affine> composition(std::vector<int>{1,\
    \ -1}, functions, 2);\n    const auto result = composition.prod(0, 2);\n    assert(result.first\
    \ == Mint(10) && result.second == Mint(17));\n}\n\nvoid test_randomized() {\n\
    \    using Sum = m1une::monoid::Add<long long>;\n    using Mint = m1une::math::modint998244353;\n\
    \    using Affine = m1une::monoid::Affine<Mint>;\n    std::uint64_t state = 20261117;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 120;\
    \ ++trial) {\n        const int n = 1 + int(random() % 25);\n        const std::uint64_t\
    \ limit = random() % 257;\n        std::vector<int> successor(n);\n        std::vector<long\
    \ long> values(n);\n        std::vector<Affine::value_type> functions(n);\n  \
    \      for (int i = 0; i < n; ++i) {\n            successor[i] = int(random()\
    \ % (n + 1)) - 1;\n            values[i] = int(random() % 41) - 20;\n        \
    \    functions[i] = Affine::value_type{Mint(random() % 10), Mint(random() % 10)};\n\
    \        }\n        m1une::graph::Doubling<Sum> sums(successor, values, limit);\n\
    \        m1une::graph::Doubling<Affine> affine(successor, functions, limit);\n\
    \        for (int query = 0; query < 160; ++query) {\n            int start =\
    \ int(random() % (n + 1)) - 1;\n            std::uint64_t steps = random() % (limit\
    \ + 1);\n            check_walk<Sum>(sums, successor, values, start, steps);\n\
    \            check_walk<Affine>(affine, successor, functions, start, steps);\n\
    \        }\n\n        std::vector<std::string> letters(n);\n        for (int i\
    \ = 0; i < n; ++i) letters[i] = char('a' + i);\n        const m1une::graph::Doubling<Concat>\
    \ words(successor, letters, 17);\n        for (int start = -1; start < n; ++start)\
    \ {\n            for (int steps = 0; steps <= 17; ++steps) {\n               \
    \ check_walk<Concat>(words, successor, letters, start, steps);\n            }\n\
    \        }\n    }\n}\n\nvoid test_full_width_steps() {\n    using Sum = m1une::monoid::Add<std::uint64_t>;\n\
    \    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();\n\
    \    const std::vector<int> successor = {1, 2, 0};\n    const std::vector<std::uint64_t>\
    \ values = {1, 2, 4};\n    const m1une::graph::Doubling<Sum> cycle(successor,\
    \ values, maximum);\n    assert(cycle.levels() == 64);\n    std::vector<std::uint64_t>\
    \ queries = {0, 1, 2, 3, 63, 64, 65};\n    queries.push_back((std::uint64_t(1)\
    \ << 63) - 1);\n    queries.push_back(std::uint64_t(1) << 63);\n    queries.push_back((std::uint64_t(1)\
    \ << 63) + 1);\n    queries.push_back(maximum);\n    for (int start = 0; start\
    \ < 3; ++start) {\n        for (std::uint64_t steps : queries) {\n           \
    \ // Unsigned addition intentionally computes the aggregate modulo 2^64.\n   \
    \         std::uint64_t expected = (steps / 3) * 7;\n            for (std::uint64_t\
    \ i = 0; i < steps % 3; ++i) expected += values[(start + i) % 3];\n          \
    \  const int destination = (start + steps % 3) % 3;\n            auto result =\
    \ cycle.walk(start, steps);\n            assert(result.vertex == destination &&\
    \ result.product == expected);\n            assert(cycle.jump(start, steps) ==\
    \ destination);\n            assert(cycle.prod(start, steps) == expected);\n \
    \       }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_boundaries();\n\
    \    test_randomized();\n    test_full_width_steps();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    if (!input.read(n,\
    \ q)) return 0;\n    std::vector<int> successor(n + 1, -1);\n    std::vector<long\
    \ long> values(n + 1, 0);\n    for (int i = 0; i < n; ++i) {\n        successor[i]\
    \ = i + 1;\n        input >> values[i];\n    }\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    const m1une::graph::Doubling<Sum> doubling(successor, values, n);\n\
    \    while (q--) {\n        int l, r;\n        input >> l >> r;\n        auto\
    \ result = doubling.walk(l, r - l);\n        assert(result.vertex == r);\n   \
    \     output << result.product << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"../../graph/doubling.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <limits>\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    #include \"../../math/modint.hpp\"\n#include \"../../monoid/add.hpp\"\n#include\
    \ \"../../monoid/affine.hpp\"\n#include \"../../utilities/fast_io.hpp\"\n\nnamespace\
    \ {\n\ntemplate <class Monoid>\nvoid check_walk(const m1une::graph::Doubling<Monoid>&\
    \ doubling,\n                const std::vector<int>& successor,\n            \
    \    const std::vector<typename Monoid::value_type>& values,\n               \
    \ int start, std::uint64_t steps) {\n    int vertex = start;\n    auto product\
    \ = Monoid::id();\n    for (std::uint64_t step = 0; step < steps && vertex !=\
    \ -1; ++step) {\n        product = Monoid::op(product, values[vertex]);\n    \
    \    vertex = successor[vertex];\n    }\n    auto result = doubling.walk(start,\
    \ steps);\n    assert(result.vertex == vertex);\n    assert(result.product ==\
    \ product);\n    assert(doubling.jump(start, steps) == vertex);\n    assert(doubling.prod(start,\
    \ steps) == product);\n}\n\nstruct Concat {\n    using value_type = std::string;\n\
    \    static value_type id() { return \"\"; }\n    static value_type op(const value_type&\
    \ a, const value_type& b) { return a + b; }\n};\n\nstruct Box {\n    int value;\n\
    \    explicit Box(int x) : value(x) {}\n};\n\nstruct BoxAdd {\n    using value_type\
    \ = Box;\n    static Box id() { return Box(0); }\n    static Box op(const Box&\
    \ a, const Box& b) { return Box(a.value + b.value); }\n};\n\nvoid test_boundaries()\
    \ {\n    using Sum = m1une::monoid::Add<long long>;\n    m1une::graph::Doubling<Sum>\
    \ empty;\n    assert(empty.empty() && empty.size() == 0);\n    assert(empty.levels()\
    \ == 0 && empty.max_steps() == 0);\n    assert(empty.jump(-1, 0) == -1 && empty.prod(-1,\
    \ 0) == 0);\n\n    std::vector<int> successor = {1, 2, -1};\n    std::vector<long\
    \ long> values = {2, 5, 9};\n    m1une::graph::Doubling<Sum> chain(successor,\
    \ values, 100);\n    auto zero = chain.walk(0, 0);\n    assert(zero.vertex ==\
    \ 0 && zero.product == 0);\n    auto before_exit = chain.walk(0, 2);\n    assert(before_exit.vertex\
    \ == 2 && before_exit.product == 7);\n    auto exit = chain.walk(0, 3);\n    assert(exit.vertex\
    \ == -1 && exit.product == 16);\n    assert(chain.jump(0, 100) == -1 && chain.prod(0,\
    \ 100) == 16);\n    assert(chain.walk(-1, 100).product == 0);\n    assert(chain.size()\
    \ == 3 && chain.levels() == 7 && chain.max_steps() == 100);\n\n    chain.build(successor,\
    \ values, 0);\n    assert(chain.levels() == 0 && chain.jump(2, 0) == 2);\n   \
    \ assert(chain.prod(1, 0) == 0);\n    chain.build(std::vector<int>{0}, std::vector<long\
    \ long>{3}, 16);\n    assert(chain.levels() == 5 && chain.prod(0, 16) == 48);\n\
    \    auto copied = chain;\n    chain.build(std::vector<int>{-1}, std::vector<long\
    \ long>{8}, 1);\n    assert(chain.prod(0, 1) == 8 && copied.prod(0, 16) == 48);\n\
    \    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();\n\
    \    chain.build(std::vector<int>{}, std::vector<long long>{}, maximum);\n   \
    \ assert(chain.empty() && chain.levels() == 64);\n    assert(chain.walk(-1, maximum).vertex\
    \ == -1 && chain.prod(-1, maximum) == 0);\n\n    std::vector<Box> boxes;\n   \
    \ boxes.emplace_back(3);\n    boxes.emplace_back(8);\n    m1une::graph::Doubling<BoxAdd>\
    \ boxed(std::vector<int>{1, -1}, boxes, 4);\n    assert(boxed.prod(0, 4).value\
    \ == 11);  // No default constructor or equality is needed.\n\n    using Mint\
    \ = m1une::math::modint998244353;\n    using Affine = m1une::monoid::Affine<Mint>;\n\
    \    std::vector<Affine::value_type> functions;\n    functions.emplace_back(2,\
    \ 3);\n    functions.emplace_back(5, 7);\n    m1une::graph::Doubling<Affine> composition(std::vector<int>{1,\
    \ -1}, functions, 2);\n    const auto result = composition.prod(0, 2);\n    assert(result.first\
    \ == Mint(10) && result.second == Mint(17));\n}\n\nvoid test_randomized() {\n\
    \    using Sum = m1une::monoid::Add<long long>;\n    using Mint = m1une::math::modint998244353;\n\
    \    using Affine = m1une::monoid::Affine<Mint>;\n    std::uint64_t state = 20261117;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 120;\
    \ ++trial) {\n        const int n = 1 + int(random() % 25);\n        const std::uint64_t\
    \ limit = random() % 257;\n        std::vector<int> successor(n);\n        std::vector<long\
    \ long> values(n);\n        std::vector<Affine::value_type> functions(n);\n  \
    \      for (int i = 0; i < n; ++i) {\n            successor[i] = int(random()\
    \ % (n + 1)) - 1;\n            values[i] = int(random() % 41) - 20;\n        \
    \    functions[i] = Affine::value_type{Mint(random() % 10), Mint(random() % 10)};\n\
    \        }\n        m1une::graph::Doubling<Sum> sums(successor, values, limit);\n\
    \        m1une::graph::Doubling<Affine> affine(successor, functions, limit);\n\
    \        for (int query = 0; query < 160; ++query) {\n            int start =\
    \ int(random() % (n + 1)) - 1;\n            std::uint64_t steps = random() % (limit\
    \ + 1);\n            check_walk<Sum>(sums, successor, values, start, steps);\n\
    \            check_walk<Affine>(affine, successor, functions, start, steps);\n\
    \        }\n\n        std::vector<std::string> letters(n);\n        for (int i\
    \ = 0; i < n; ++i) letters[i] = char('a' + i);\n        const m1une::graph::Doubling<Concat>\
    \ words(successor, letters, 17);\n        for (int start = -1; start < n; ++start)\
    \ {\n            for (int steps = 0; steps <= 17; ++steps) {\n               \
    \ check_walk<Concat>(words, successor, letters, start, steps);\n            }\n\
    \        }\n    }\n}\n\nvoid test_full_width_steps() {\n    using Sum = m1une::monoid::Add<std::uint64_t>;\n\
    \    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();\n\
    \    const std::vector<int> successor = {1, 2, 0};\n    const std::vector<std::uint64_t>\
    \ values = {1, 2, 4};\n    const m1une::graph::Doubling<Sum> cycle(successor,\
    \ values, maximum);\n    assert(cycle.levels() == 64);\n    std::vector<std::uint64_t>\
    \ queries = {0, 1, 2, 3, 63, 64, 65};\n    queries.push_back((std::uint64_t(1)\
    \ << 63) - 1);\n    queries.push_back(std::uint64_t(1) << 63);\n    queries.push_back((std::uint64_t(1)\
    \ << 63) + 1);\n    queries.push_back(maximum);\n    for (int start = 0; start\
    \ < 3; ++start) {\n        for (std::uint64_t steps : queries) {\n           \
    \ // Unsigned addition intentionally computes the aggregate modulo 2^64.\n   \
    \         std::uint64_t expected = (steps / 3) * 7;\n            for (std::uint64_t\
    \ i = 0; i < steps % 3; ++i) expected += values[(start + i) % 3];\n          \
    \  const int destination = (start + steps % 3) % 3;\n            auto result =\
    \ cycle.walk(start, steps);\n            assert(result.vertex == destination &&\
    \ result.product == expected);\n            assert(cycle.jump(start, steps) ==\
    \ destination);\n            assert(cycle.prod(start, steps) == expected);\n \
    \       }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_boundaries();\n\
    \    test_randomized();\n    test_full_width_steps();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n    int n, q;\n    if (!input.read(n,\
    \ q)) return 0;\n    std::vector<int> successor(n + 1, -1);\n    std::vector<long\
    \ long> values(n + 1, 0);\n    for (int i = 0; i < n; ++i) {\n        successor[i]\
    \ = i + 1;\n        input >> values[i];\n    }\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    const m1une::graph::Doubling<Sum> doubling(successor, values, n);\n\
    \    while (q--) {\n        int l, r;\n        input >> l >> r;\n        auto\
    \ result = doubling.walk(l, r - l);\n        assert(result.vertex == r);\n   \
    \     output << result.product << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/doubling.hpp
  - monoid/concept.hpp
  - math/modint.hpp
  - monoid/add.hpp
  - monoid/affine.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/doubling.test.cpp
  requiredBy: []
  timestamp: '2026-11-17 03:42:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/doubling.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/doubling.test.cpp
- /verify/verify/graph/doubling.test.cpp.html
title: verify/graph/doubling.test.cpp
---
