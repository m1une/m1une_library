---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_2d.hpp
    title: Segtree 2D
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"verify/ds/segtree/segtree_2d.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line 1 \"ds/segtree/segtree_2d.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if\
    \ (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 12 \"ds/segtree/segtree_2d.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A static compressed 2D segment tree.\n// It supports\
    \ point assignment on registered points and rectangle product queries.\n//\n//\
    \ The query rectangle is [xl, xr) x [yl, yr).\n// All points that may be updated\
    \ must be registered before construction.\ntemplate <class Monoid, class X = int,\
    \ class Y = X>\nrequires m1une::monoid::IsMonoid<Monoid>\nstruct Segtree2D {\n\
    \    using T = typename Monoid::value_type;\n    using point_type = std::pair<X,\
    \ Y>;\n    using weighted_point_type = std::tuple<X, Y, T>;\n\nprivate:\n    int\
    \ _n;\n    int _size;\n    int _point_count;\n    std::vector<X> _xs;\n    std::vector<std::vector<Y>>\
    \ _ys;\n    std::vector<std::vector<T>> _d;\n\n    static std::vector<point_type>\
    \ normalize_points(std::vector<point_type> points) {\n        std::sort(points.begin(),\
    \ points.end());\n        points.erase(std::unique(points.begin(), points.end()),\
    \ points.end());\n        return points;\n    }\n\n    int x_index(const X& x)\
    \ const {\n        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);\n  \
    \      if (it == _xs.end() || *it != x) return -1;\n        return int(it - _xs.begin());\n\
    \    }\n\n    int y_index(int k, const Y& y) const {\n        const auto& ys =\
    \ _ys[k];\n        auto it = std::lower_bound(ys.begin(), ys.end(), y);\n    \
    \    if (it == ys.end() || *it != y) return -1;\n        return int(it - ys.begin());\n\
    \    }\n\n    T get_exact(int k, const Y& y) const {\n        int pos = y_index(k,\
    \ y);\n        if (pos == -1) return Monoid::id();\n        int m = int(_ys[k].size());\n\
    \        return _d[k][m + pos];\n    }\n\n    void set_exact(int k, const Y& y,\
    \ T x) {\n        int pos = y_index(k, y);\n        assert(pos != -1);\n\n   \
    \     int m = int(_ys[k].size());\n        int p = m + pos;\n\n        _d[k][p]\
    \ = std::move(x);\n        while (1 < p) {\n            p >>= 1;\n           \
    \ _d[k][p] = Monoid::op(_d[k][2 * p], _d[k][2 * p + 1]);\n        }\n    }\n\n\
    \    T prod_y(int k, const Y& yl, const Y& yr) const {\n        assert(yl <= yr);\n\
    \        if (yl == yr || _ys[k].empty()) return Monoid::id();\n\n        const\
    \ auto& ys = _ys[k];\n        int l = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yl) - ys.begin());\n        int r = int(std::lower_bound(ys.begin(), ys.end(),\
    \ yr) - ys.begin());\n\n        int m = int(ys.size());\n        l += m;\n   \
    \     r += m;\n\n        T sml = Monoid::id();\n        T smr = Monoid::id();\n\
    \n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _d[k][l++]);\n\
    \            if (r & 1) smr = Monoid::op(_d[k][--r], smr);\n            l >>=\
    \ 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\npublic:\n    Segtree2D() : _n(0), _size(1), _point_count(0), _ys(2),\
    \ _d(2) {}\n\n    explicit Segtree2D(const std::vector<point_type>& points) {\n\
    \        build(points);\n    }\n\n    explicit Segtree2D(std::vector<point_type>&&\
    \ points) {\n        build(std::move(points));\n    }\n\n    explicit Segtree2D(const\
    \ std::vector<weighted_point_type>& points) {\n        std::vector<point_type>\
    \ coords;\n        coords.reserve(points.size());\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            (void)value;\n            coords.emplace_back(x,\
    \ y);\n        }\n\n        build(std::move(coords));\n\n        for (const auto&\
    \ [x, y, value] : points) {\n            set(x, y, value);\n        }\n    }\n\
    \n    void build(std::vector<point_type> points) {\n        points = normalize_points(std::move(points));\n\
    \n        _point_count = int(points.size());\n\n        _xs.clear();\n       \
    \ _xs.reserve(points.size());\n\n        for (const auto& [x, y] : points) {\n\
    \            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        _n = int(_xs.size());\n        _size = int(m1une::math::bit_ceil((unsigned\
    \ int)std::max(1, _n)));\n\n        _ys.assign(2 * _size, {});\n        _d.assign(2\
    \ * _size, {});\n\n        for (const auto& [x, y] : points) {\n            int\
    \ xi = int(std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin());\n     \
    \       for (int k = xi + _size; k; k >>= 1) {\n                _ys[k].push_back(y);\n\
    \            }\n        }\n\n        for (int k = 1; k < 2 * _size; k++) {\n \
    \           auto& ys = _ys[k];\n            std::sort(ys.begin(), ys.end());\n\
    \            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n        \
    \    _d[k].assign(2 * ys.size(), Monoid::id());\n        }\n    }\n\n    int size()\
    \ const {\n        return _point_count;\n    }\n\n    bool empty() const {\n \
    \       return _point_count == 0;\n    }\n\n    int x_size() const {\n       \
    \ return _n;\n    }\n\n    const std::vector<X>& xs() const {\n        return\
    \ _xs;\n    }\n\n    bool contains_point(const X& x, const Y& y) const {\n   \
    \     int xi = x_index(x);\n        if (xi == -1) return false;\n        return\
    \ y_index(xi + _size, y) != -1;\n    }\n\n    void set(const X& x, const Y& y,\
    \ T value) {\n        int xi = x_index(x);\n        assert(xi != -1);\n      \
    \  assert(y_index(xi + _size, y) != -1);\n\n        int k = xi + _size;\n    \
    \    set_exact(k, y, std::move(value));\n\n        while (1 < k) {\n         \
    \   k >>= 1;\n            set_exact(k, y, Monoid::op(get_exact(2 * k, y), get_exact(2\
    \ * k + 1, y)));\n        }\n    }\n\n    T get(const X& x, const Y& y) const\
    \ {\n        int xi = x_index(x);\n        if (xi == -1) return Monoid::id();\n\
    \        return get_exact(xi + _size, y);\n    }\n\n    T operator()(const X&\
    \ x, const Y& y) const {\n        return get(x, y);\n    }\n\n    T prod(const\
    \ X& xl, const X& xr, const Y& yl, const Y& yr) const {\n        assert(xl <=\
    \ xr);\n        assert(yl <= yr);\n\n        if (xl == xr || yl == yr || empty())\
    \ return Monoid::id();\n\n        int l = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xl) - _xs.begin());\n        int r = int(std::lower_bound(_xs.begin(), _xs.end(),\
    \ xr) - _xs.begin());\n\n        l += _size;\n        r += _size;\n\n        T\
    \ sml = Monoid::id();\n        T smr = Monoid::id();\n\n        while (l < r)\
    \ {\n            if (l & 1) sml = Monoid::op(sml, prod_y(l++, yl, yr));\n    \
    \        if (r & 1) smr = Monoid::op(prod_y(--r, yl, yr), smr);\n            l\
    \ >>= 1;\n            r >>= 1;\n        }\n\n        return Monoid::op(sml, smr);\n\
    \    }\n\n    T all_prod() const {\n        if (empty() || _d[1].empty()) return\
    \ Monoid::id();\n        return _d[1][1];\n    }\n\n    std::vector<weighted_point_type>\
    \ to_vector() const {\n        std::vector<weighted_point_type> res;\n       \
    \ res.reserve(_point_count);\n\n        for (int xi = 0; xi < _n; xi++) {\n  \
    \          int k = xi + _size;\n            int m = int(_ys[k].size());\n\n  \
    \          for (int j = 0; j < m; j++) {\n                res.emplace_back(_xs[xi],\
    \ _ys[k][j], _d[k][m + j]);\n            }\n        }\n\n        return res;\n\
    \    }\n};\n\n} // namespace ds\n} // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n\n  \
    \  // Returns the identity element for addition, which is 0.\n    static constexpr\
    \ T id() {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n\
    \    static constexpr T op(const T& a, const T& b) {\n        return a + b;\n\
    \    }\n\n    static constexpr T inv(const T& x) {\n        return -x;\n    }\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/segtree/segtree_2d.test.cpp\"\
    \n\n#line 8 \"verify/ds/segtree/segtree_2d.test.cpp\"\n#include <cstdint>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n#include\
    \ <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 17 \"utilities/fast_io.hpp\"\
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
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/ds/segtree/segtree_2d.test.cpp\"\
    \n#include <map>\n#include <random>\n#line 15 \"verify/ds/segtree/segtree_2d.test.cpp\"\
    \n\nusing Sum = m1une::monoid::Add<long long>;\n\nstruct Query {\n    int type;\n\
    \    int first;\n    int second;\n    int third;\n    int fourth;\n    long long\
    \ value;\n};\n\n#ifndef NDEBUG\nvoid randomized_test() {\n    std::mt19937 random(314159265);\n\
    \    std::vector<std::pair<int, int>> points;\n    std::map<std::pair<int, int>,\
    \ long long> expected;\n    for (int i = 0; i < 40; i++) {\n        int x = int(random()\
    \ % 15) - 7;\n        int y = int(random() % 15) - 7;\n        points.emplace_back(x,\
    \ y);\n        expected[{x, y}] = 0;\n    }\n\n    m1une::ds::Segtree2D<Sum> seg(points);\n\
    \    assert(seg.size() == int(expected.size()));\n    assert(!seg.contains_point(100,\
    \ 100));\n    assert(seg.get(100, 100) == 0);\n\n    std::vector<std::pair<int,\
    \ int>> distinct_points;\n    for (const auto& [point, value] : expected) {\n\
    \        (void)value;\n        distinct_points.push_back(point);\n    }\n\n  \
    \  for (int operation = 0; operation < 1000; operation++) {\n        if (random()\
    \ % 3 == 0) {\n            auto point = distinct_points[random() % distinct_points.size()];\n\
    \            long long value = int(random() % 101) - 50;\n            seg.set(point.first,\
    \ point.second, value);\n            expected[point] = value;\n            assert(seg(point.first,\
    \ point.second) == value);\n        } else {\n            int x_lower = int(random()\
    \ % 19) - 9;\n            int x_upper = int(random() % 19) - 9;\n            int\
    \ y_lower = int(random() % 19) - 9;\n            int y_upper = int(random() %\
    \ 19) - 9;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n\n         \
    \   long long answer = 0;\n            for (const auto& [point, value] : expected)\
    \ {\n                if (x_lower <= point.first && point.first < x_upper &&\n\
    \                    y_lower <= point.second && point.second < y_upper) {\n  \
    \                  answer += value;\n                }\n            }\n      \
    \      assert(seg.prod(x_lower, x_upper, y_lower, y_upper) == answer);\n     \
    \   }\n    }\n\n    long long total = 0;\n    for (const auto& [point, value]\
    \ : expected) {\n        (void)point;\n        total += value;\n    }\n    assert(seg.all_prod()\
    \ == total);\n    auto values = seg.to_vector();\n    assert(values.size() ==\
    \ expected.size());\n    for (const auto& [x, y, value] : values) {\n        std::pair<int,\
    \ int> point(x, y);\n        assert(expected[point] == value);\n    }\n}\n#endif\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n#ifndef NDEBUG\n    randomized_test();\n#endif\n\n    int n,\
    \ q;\n    fast_input >> n >> q;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(n);\n    std::vector<std::pair<int, int>> points;\n    points.reserve(n\
    \ + q);\n    for (auto& [x, y, weight] : initial) {\n        fast_input >> x >>\
    \ y >> weight;\n        points.emplace_back(x, y);\n    }\n\n    std::vector<Query>\
    \ queries(q);\n    for (Query& query : queries) {\n        fast_input >> query.type;\n\
    \        if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            fast_input >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::Segtree2D<Sum> seg(std::move(points));\n    for (const\
    \ auto& [x, y, weight] : initial) {\n        seg.set(x, y, seg.get(x, y) + weight);\n\
    \    }\n\n    for (const Query& query : queries) {\n        if (query.type ==\
    \ 0) {\n            long long current = seg.get(query.first, query.second);\n\
    \            seg.set(query.first, query.second, current + query.value);\n    \
    \    } else {\n            fast_output << seg.prod(query.first, query.third, query.second,\
    \ query.fourth)\n                      << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../../ds/segtree/segtree_2d.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cstdint>\n#include \"\
    ../../../utilities/fast_io.hpp\"\n#include <map>\n#include <random>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\nusing Sum = m1une::monoid::Add<long\
    \ long>;\n\nstruct Query {\n    int type;\n    int first;\n    int second;\n \
    \   int third;\n    int fourth;\n    long long value;\n};\n\n#ifndef NDEBUG\n\
    void randomized_test() {\n    std::mt19937 random(314159265);\n    std::vector<std::pair<int,\
    \ int>> points;\n    std::map<std::pair<int, int>, long long> expected;\n    for\
    \ (int i = 0; i < 40; i++) {\n        int x = int(random() % 15) - 7;\n      \
    \  int y = int(random() % 15) - 7;\n        points.emplace_back(x, y);\n     \
    \   expected[{x, y}] = 0;\n    }\n\n    m1une::ds::Segtree2D<Sum> seg(points);\n\
    \    assert(seg.size() == int(expected.size()));\n    assert(!seg.contains_point(100,\
    \ 100));\n    assert(seg.get(100, 100) == 0);\n\n    std::vector<std::pair<int,\
    \ int>> distinct_points;\n    for (const auto& [point, value] : expected) {\n\
    \        (void)value;\n        distinct_points.push_back(point);\n    }\n\n  \
    \  for (int operation = 0; operation < 1000; operation++) {\n        if (random()\
    \ % 3 == 0) {\n            auto point = distinct_points[random() % distinct_points.size()];\n\
    \            long long value = int(random() % 101) - 50;\n            seg.set(point.first,\
    \ point.second, value);\n            expected[point] = value;\n            assert(seg(point.first,\
    \ point.second) == value);\n        } else {\n            int x_lower = int(random()\
    \ % 19) - 9;\n            int x_upper = int(random() % 19) - 9;\n            int\
    \ y_lower = int(random() % 19) - 9;\n            int y_upper = int(random() %\
    \ 19) - 9;\n            if (x_upper < x_lower) std::swap(x_lower, x_upper);\n\
    \            if (y_upper < y_lower) std::swap(y_lower, y_upper);\n\n         \
    \   long long answer = 0;\n            for (const auto& [point, value] : expected)\
    \ {\n                if (x_lower <= point.first && point.first < x_upper &&\n\
    \                    y_lower <= point.second && point.second < y_upper) {\n  \
    \                  answer += value;\n                }\n            }\n      \
    \      assert(seg.prod(x_lower, x_upper, y_lower, y_upper) == answer);\n     \
    \   }\n    }\n\n    long long total = 0;\n    for (const auto& [point, value]\
    \ : expected) {\n        (void)point;\n        total += value;\n    }\n    assert(seg.all_prod()\
    \ == total);\n    auto values = seg.to_vector();\n    assert(values.size() ==\
    \ expected.size());\n    for (const auto& [x, y, value] : values) {\n        std::pair<int,\
    \ int> point(x, y);\n        assert(expected[point] == value);\n    }\n}\n#endif\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n#ifndef NDEBUG\n    randomized_test();\n#endif\n\n    int n,\
    \ q;\n    fast_input >> n >> q;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(n);\n    std::vector<std::pair<int, int>> points;\n    points.reserve(n\
    \ + q);\n    for (auto& [x, y, weight] : initial) {\n        fast_input >> x >>\
    \ y >> weight;\n        points.emplace_back(x, y);\n    }\n\n    std::vector<Query>\
    \ queries(q);\n    for (Query& query : queries) {\n        fast_input >> query.type;\n\
    \        if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            fast_input >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::Segtree2D<Sum> seg(std::move(points));\n    for (const\
    \ auto& [x, y, weight] : initial) {\n        seg.set(x, y, seg.get(x, y) + weight);\n\
    \    }\n\n    for (const Query& query : queries) {\n        if (query.type ==\
    \ 0) {\n            long long current = seg.get(query.first, query.second);\n\
    \            seg.set(query.first, query.second, current + query.value);\n    \
    \    } else {\n            fast_output << seg.prod(query.first, query.third, query.second,\
    \ query.fourth)\n                      << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/segtree_2d.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/segtree/segtree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/segtree_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/segtree_2d.test.cpp
- /verify/verify/ds/segtree/segtree_2d.test.cpp.html
title: verify/ds/segtree/segtree_2d.test.cpp
---
