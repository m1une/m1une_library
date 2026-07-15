---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/segtree.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#line 1 \"ds/segtree/segtree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1)\
    \ return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n} \
    \ // namespace math\n}  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ group monoids.\n// A type satisfying this concept must also obey commutativity\
    \ and inverse laws.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 11 \"ds/segtree/segtree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n// A generic\
    \ Segment Tree utilizing C++20 Concepts for type safety.\n// It requires a Monoid\
    \ struct that satisfies `m1une::monoid::IsMonoid`.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct Segtree {\n    using T = typename Monoid::value_type;\n\n  \
    \ private:\n    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void update(int\
    \ k) {\n        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n   public:\n\
    \    // Constructs an empty segment tree.\n    Segtree() : Segtree(0) {}\n\n \
    \   // Constructs a segment tree of size `n`, initialized with the identity element.\n\
    \    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}\n\n\
    \    // Constructs a segment tree from an existing vector.\n    explicit Segtree(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) _d[_size + i] = v[i];\n        for (int i = _size - 1; i >= 1;\
    \ i--) update(i);\n    }\n    explicit Segtree(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size\
    \ + i] = std::move(v[i]);\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Constructs a segment tree from a vector of a different type U.\n\
    \    // It automatically adapts to the Monoid's initialization requirements:\n\
    \    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index)\
    \ if the monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit Segtree(const std::vector<U>& v) : _n(int(v.size())) {\n  \
    \      _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n\
    \        while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) {\n          \
    \  if constexpr (requires(U x) { Monoid::make(x); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i]);\n            } else if constexpr (requires(U x, int\
    \ idx) { Monoid::make(x, idx); }) {\n                _d[_size + i] = Monoid::make(v[i],\
    \ i);\n            } else {\n                _d[_size + i] = static_cast<T>(v[i]);\n\
    \            }\n        }\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Returns the number of elements.\n    int size() const {\n   \
    \     return _n;\n    }\n\n    // Returns whether the tree is empty.\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Sets the value of\
    \ the element at index `p` to `x`.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        _d[p] = x;\n        for (int\
    \ i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return _d[p + _size];\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T operator[](int p) const {\n        return get(p);\n\
    \    }\n\n    // Returns the product (result of the monoid operation) in the range\
    \ [l, r).\n    T prod(int l, int r) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        T sml = Monoid::id(), smr = Monoid::id();\n        l += _size;\n\
    \        r += _size;\n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml,\
    \ _d[l++]);\n            if (r & 1) smr = Monoid::op(_d[--r], smr);\n        \
    \    l >>= 1;\n            r >>= 1;\n        }\n        return Monoid::op(sml,\
    \ smr);\n    }\n\n    // Returns the product of the entire array.\n    T all_prod()\
    \ const {\n        return _d[1];\n    }\n\n    // Returns all elements as a vector.\n\
    \    std::vector<T> to_vector() const {\n        return to_vector(0, _n);\n  \
    \  }\n\n    // Returns the elements in the range [l, r) as a vector.\n    std::vector<T>\
    \ to_vector(int l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        std::vector<T> res;\n        res.reserve(r - l);\n        for (int i\
    \ = l; i < r; i++) res.push_back(_d[_size + i]);\n        return res;\n    }\n\
    \n    // Finds the largest `r` such that `f(prod(l, r))` is true.\n    // Uses\
    \ a custom functor or lambda `f`.\n    template <class F>\n    int max_right(int\
    \ l, F f) const {\n        assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (l == _n) return _n;\n        l += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm,\
    \ _d[l]))) {\n                while (l < _size) {\n                    l = (2\
    \ * l);\n                    if (f(Monoid::op(sm, _d[l]))) {\n               \
    \         sm = Monoid::op(sm, _d[l]);\n                        l++;\n        \
    \            }\n                }\n                return l - _size;\n       \
    \     }\n            sm = Monoid::op(sm, _d[l]);\n            l++;\n        }\
    \ while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the smallest\
    \ `l` such that `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int\
    \ r, F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Monoid for addition (Range Sum).\ntemplate <typename\
    \ T>\nstruct Add {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #include <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une\
    \ {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ m1une\n\n\n#line 8 \"verify/ds/segtree/segtree.test.cpp\"\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n, q;\n    fast_input >> n >> q;\n\n    std::vector<long\
    \ long> a(n);\n    for (int i = 0; i < n; i++) {\n        fast_input >> a[i];\n\
    \    }\n\n    m1une::ds::Segtree<m1une::monoid::Add<long long>> seg(a);\n    assert(seg.size()\
    \ == n);\n    assert(seg.empty() == (n == 0));\n    assert(seg.to_vector() ==\
    \ a);\n    for (int i = 0; i < n; i++) assert(seg[i] == a[i]);\n\n    for (int\
    \ i = 0; i < q; i++) {\n        int type;\n        fast_input >> type;\n     \
    \   if (type == 0) {\n            int p;\n            long long x;\n         \
    \   fast_input >> p >> x;\n            seg.set(p, seg.get(p) + x);\n        }\
    \ else {\n            int l, r;\n            fast_input >> l >> r;\n         \
    \   fast_output << seg.prod(l, r) << \"\\n\";\n        }\n    }\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"../../../ds/segtree/segtree.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n#include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\n#include <vector>\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int n, q;\n    fast_input >> n >> q;\n\n    std::vector<long\
    \ long> a(n);\n    for (int i = 0; i < n; i++) {\n        fast_input >> a[i];\n\
    \    }\n\n    m1une::ds::Segtree<m1une::monoid::Add<long long>> seg(a);\n    assert(seg.size()\
    \ == n);\n    assert(seg.empty() == (n == 0));\n    assert(seg.to_vector() ==\
    \ a);\n    for (int i = 0; i < n; i++) assert(seg[i] == a[i]);\n\n    for (int\
    \ i = 0; i < q; i++) {\n        int type;\n        fast_input >> type;\n     \
    \   if (type == 0) {\n            int p;\n            long long x;\n         \
    \   fast_input >> p >> x;\n            seg.set(p, seg.get(p) + x);\n        }\
    \ else {\n            int l, r;\n            fast_input >> l >> r;\n         \
    \   fast_output << seg.prod(l, r) << \"\\n\";\n        }\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - ds/segtree/segtree.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/segtree/segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/segtree.test.cpp
- /verify/verify/ds/segtree/segtree.test.cpp.html
title: verify/ds/segtree/segtree.test.cpp
---
