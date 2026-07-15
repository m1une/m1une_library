---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree_2d.hpp
    title: Fenwick Tree 2D
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
  bundledCode: "#line 1 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\n#line\
    \ 1 \"ds/range_query/fenwick_tree_2d.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T, class X\
    \ = int, class Y = X>\nclass FenwickTree2D {\n   public:\n    using value_type\
    \ = T;\n    using point_type = std::pair<X, Y>;\n    using weighted_point_type\
    \ = std::tuple<X, Y, T>;\n\n   private:\n    std::vector<point_type> _points;\n\
    \    std::vector<X> _xs;\n    std::vector<std::vector<Y>> _ys;\n    std::vector<std::vector<T>>\
    \ _data;\n\n    static std::vector<point_type> normalize_points(\n        std::vector<point_type>\
    \ points\n    ) {\n        std::sort(points.begin(), points.end());\n        points.erase(std::unique(points.begin(),\
    \ points.end()), points.end());\n        return points;\n    }\n\n    T prefix_sum_by_x_count(int\
    \ x_count, const Y& y_upper) const {\n        T result{};\n        for (int x_index\
    \ = x_count; x_index > 0; x_index -= x_index & -x_index) {\n            const\
    \ std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n\
    \                std::lower_bound(ys.begin(), ys.end(), y_upper) - ys.begin()\n\
    \            );\n            const std::vector<T>& data = _data[std::size_t(x_index)];\n\
    \            while (y_index > 0) {\n                result += data[std::size_t(y_index)];\n\
    \                y_index -= y_index & -y_index;\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prefix_sum(const X& x_upper, const Y& y_upper)\
    \ const {\n        const int x_count = int(\n            std::lower_bound(_xs.begin(),\
    \ _xs.end(), x_upper) - _xs.begin()\n        );\n        return prefix_sum_by_x_count(x_count,\
    \ y_upper);\n    }\n\n   public:\n    FenwickTree2D() : _ys(1), _data(1) {}\n\n\
    \    explicit FenwickTree2D(std::vector<point_type> points) {\n        build(std::move(points));\n\
    \    }\n\n    explicit FenwickTree2D(\n        const std::vector<weighted_point_type>&\
    \ points\n    ) {\n        build(points);\n    }\n\n    void build(std::vector<point_type>\
    \ points) {\n        _points = normalize_points(std::move(points));\n        _xs.clear();\n\
    \        _xs.reserve(_points.size());\n        for (const auto& [x, y] : _points)\
    \ {\n            (void)y;\n            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);\n\
    \        }\n\n        const int x_size = int(_xs.size());\n        _ys.assign(std::size_t(x_size\
    \ + 1), {});\n        for (const auto& [x, y] : _points) {\n            int x_index\
    \ = int(\n                std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n\
    \            ) + 1;\n            while (x_index <= x_size) {\n               \
    \ _ys[std::size_t(x_index)].push_back(y);\n                x_index += x_index\
    \ & -x_index;\n            }\n        }\n\n        _data.assign(std::size_t(x_size\
    \ + 1), {});\n        for (int x_index = 1; x_index <= x_size; x_index++) {\n\
    \            std::vector<Y>& ys = _ys[std::size_t(x_index)];\n            std::sort(ys.begin(),\
    \ ys.end());\n            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\
    \            _data[std::size_t(x_index)].assign(ys.size() + 1, T{});\n       \
    \ }\n    }\n\n    void build(const std::vector<weighted_point_type>& points) {\n\
    \        std::vector<point_type> coordinates;\n        coordinates.reserve(points.size());\n\
    \        for (const auto& [x, y, value] : points) {\n            (void)value;\n\
    \            coordinates.emplace_back(x, y);\n        }\n        build(std::move(coordinates));\n\
    \        for (const auto& [x, y, value] : points) add(x, y, value);\n    }\n\n\
    \    int size() const {\n        return int(_points.size());\n    }\n\n    bool\
    \ empty() const {\n        return _points.empty();\n    }\n\n    int x_size()\
    \ const {\n        return int(_xs.size());\n    }\n\n    const std::vector<X>&\
    \ xs() const {\n        return _xs;\n    }\n\n    bool contains_point(const X&\
    \ x, const Y& y) const {\n        return std::binary_search(_points.begin(), _points.end(),\
    \ point_type(x, y));\n    }\n\n    void add(const X& x, const Y& y, const T& value)\
    \ {\n        assert(contains_point(x, y));\n        int x_index = int(\n     \
    \       std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin()\n        ) +\
    \ 1;\n        while (x_index <= int(_xs.size())) {\n            const std::vector<Y>&\
    \ ys = _ys[std::size_t(x_index)];\n            int y_index = int(\n          \
    \      std::lower_bound(ys.begin(), ys.end(), y) - ys.begin()\n            ) +\
    \ 1;\n            std::vector<T>& data = _data[std::size_t(x_index)];\n      \
    \      while (y_index < int(data.size())) {\n                data[std::size_t(y_index)]\
    \ += value;\n                y_index += y_index & -y_index;\n            }\n \
    \           x_index += x_index & -x_index;\n        }\n    }\n\n    T sum(const\
    \ X& x_upper, const Y& y_upper) const {\n        return prefix_sum(x_upper, y_upper);\n\
    \    }\n\n    T sum(\n        const X& x_lower,\n        const X& x_upper,\n \
    \       const Y& y_lower,\n        const Y& y_upper\n    ) const {\n        assert(!(x_upper\
    \ < x_lower));\n        assert(!(y_upper < y_lower));\n        return prefix_sum(x_upper,\
    \ y_upper) -\n               prefix_sum(x_lower, y_upper) -\n               prefix_sum(x_upper,\
    \ y_lower) +\n               prefix_sum(x_lower, y_lower);\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n#include\
    \ <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\
    \n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct\
    \ is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\
    \n#include <map>\n#line 12 \"verify/ds/range_query/fenwick_tree_2d.test.cpp\"\n\
    \nnamespace {\n\nusing Point = std::pair<int, int>;\n\nlong long rectangle_sum(\n\
    \    const std::map<Point, long long>& values,\n    int x_lower,\n    int x_upper,\n\
    \    int y_lower,\n    int y_upper\n) {\n    long long result = 0;\n    for (const\
    \ auto& [point, value] : values) {\n        if (x_lower <= point.first && point.first\
    \ < x_upper &&\n            y_lower <= point.second && point.second < y_upper)\
    \ {\n            result += value;\n        }\n    }\n    return result;\n}\n\n\
    void test_edge_cases() {\n    m1une::ds::FenwickTree2D<long long> empty;\n   \
    \ assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.sum(10,\
    \ 20) == 0);\n    assert(empty.sum(-10, 10, -20, 20) == 0);\n\n    std::vector<std::tuple<int,\
    \ int, long long>> weighted{\n        {2, 3, 4},\n        {2, 3, 5},\n       \
    \ {-1, 7, 6}\n    };\n    m1une::ds::FenwickTree2D<long long> fenwick(weighted);\n\
    \    assert(fenwick.size() == 2);\n    assert(fenwick.x_size() == 2);\n    assert(fenwick.contains_point(2,\
    \ 3));\n    assert(!fenwick.contains_point(2, 4));\n    assert(fenwick.sum(2,\
    \ 3, 3, 4) == 9);\n    assert(fenwick.sum(100, 100) == 15);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0xc75b921e4a630df8ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 200; trial++) {\n        std::vector<Point>\
    \ points;\n        for (int index = 0; index < 50; index++) {\n            points.emplace_back(int(random()\
    \ % 21) - 10, int(random() % 21) - 10);\n        }\n        m1une::ds::FenwickTree2D<long\
    \ long> fenwick(points);\n        std::map<Point, long long> expected;\n     \
    \   for (const Point& point : points) expected[point] = 0;\n        assert(fenwick.size()\
    \ == int(expected.size()));\n\n        std::vector<Point> distinct_points;\n \
    \       for (const auto& [point, value] : expected) {\n            (void)value;\n\
    \            distinct_points.push_back(point);\n        }\n\n        for (int\
    \ operation = 0; operation < 500; operation++) {\n            if ((random() &\
    \ 1) == 0) {\n                const Point point =\n                    distinct_points[std::size_t(random()\
    \ % distinct_points.size())];\n                const long long value = static_cast<long\
    \ long>(random() % 101) - 50;\n                fenwick.add(point.first, point.second,\
    \ value);\n                expected[point] += value;\n            } else {\n \
    \               int x_lower = int(random() % 25) - 12;\n                int x_upper\
    \ = int(random() % 25) - 12;\n                int y_lower = int(random() % 25)\
    \ - 12;\n                int y_upper = int(random() % 25) - 12;\n            \
    \    if (x_upper < x_lower) std::swap(x_lower, x_upper);\n                if (y_upper\
    \ < y_lower) std::swap(y_lower, y_upper);\n                assert(\n         \
    \           fenwick.sum(x_lower, x_upper, y_lower, y_upper) ==\n             \
    \       rectangle_sum(expected, x_lower, x_upper, y_lower, y_upper)\n        \
    \        );\n                assert(\n                    fenwick.sum(x_upper,\
    \ y_upper) ==\n                    rectangle_sum(expected, -100, x_upper, -100,\
    \ y_upper)\n                );\n            }\n        }\n    }\n}\n\nstruct Query\
    \ {\n    int type;\n    int first;\n    int second;\n    int third;\n    int fourth;\n\
    \    long long value;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n\
    \    test_randomized();\n\n    int point_count, query_count;\n    fast_input >>\
    \ point_count >> query_count;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(\n        static_cast<std::size_t>(point_count)\n    );\n    std::vector<Point>\
    \ points;\n    points.reserve(static_cast<std::size_t>(point_count + query_count));\n\
    \    for (auto& [x, y, weight] : initial) {\n        fast_input >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(static_cast<std::size_t>(query_count));\n\
    \    for (Query& query : queries) {\n        fast_input >> query.type;\n     \
    \   if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            fast_input >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::FenwickTree2D<long long> fenwick(std::move(points));\n\
    \    for (const auto& [x, y, weight] : initial) fenwick.add(x, y, weight);\n\n\
    \    for (const Query& query : queries) {\n        if (query.type == 0) {\n  \
    \          fenwick.add(query.first, query.second, query.value);\n        } else\
    \ {\n            fast_output << fenwick.sum(\n                query.first,\n \
    \               query.third,\n                query.second,\n                query.fourth\n\
    \            ) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n\n#include \"../../../ds/range_query/fenwick_tree_2d.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n#include <map>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\nnamespace {\n\nusing\
    \ Point = std::pair<int, int>;\n\nlong long rectangle_sum(\n    const std::map<Point,\
    \ long long>& values,\n    int x_lower,\n    int x_upper,\n    int y_lower,\n\
    \    int y_upper\n) {\n    long long result = 0;\n    for (const auto& [point,\
    \ value] : values) {\n        if (x_lower <= point.first && point.first < x_upper\
    \ &&\n            y_lower <= point.second && point.second < y_upper) {\n     \
    \       result += value;\n        }\n    }\n    return result;\n}\n\nvoid test_edge_cases()\
    \ {\n    m1une::ds::FenwickTree2D<long long> empty;\n    assert(empty.empty());\n\
    \    assert(empty.size() == 0);\n    assert(empty.sum(10, 20) == 0);\n    assert(empty.sum(-10,\
    \ 10, -20, 20) == 0);\n\n    std::vector<std::tuple<int, int, long long>> weighted{\n\
    \        {2, 3, 4},\n        {2, 3, 5},\n        {-1, 7, 6}\n    };\n    m1une::ds::FenwickTree2D<long\
    \ long> fenwick(weighted);\n    assert(fenwick.size() == 2);\n    assert(fenwick.x_size()\
    \ == 2);\n    assert(fenwick.contains_point(2, 3));\n    assert(!fenwick.contains_point(2,\
    \ 4));\n    assert(fenwick.sum(2, 3, 3, 4) == 9);\n    assert(fenwick.sum(100,\
    \ 100) == 15);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0xc75b921e4a630df8ULL;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 200; trial++) {\n        std::vector<Point> points;\n        for (int index\
    \ = 0; index < 50; index++) {\n            points.emplace_back(int(random() %\
    \ 21) - 10, int(random() % 21) - 10);\n        }\n        m1une::ds::FenwickTree2D<long\
    \ long> fenwick(points);\n        std::map<Point, long long> expected;\n     \
    \   for (const Point& point : points) expected[point] = 0;\n        assert(fenwick.size()\
    \ == int(expected.size()));\n\n        std::vector<Point> distinct_points;\n \
    \       for (const auto& [point, value] : expected) {\n            (void)value;\n\
    \            distinct_points.push_back(point);\n        }\n\n        for (int\
    \ operation = 0; operation < 500; operation++) {\n            if ((random() &\
    \ 1) == 0) {\n                const Point point =\n                    distinct_points[std::size_t(random()\
    \ % distinct_points.size())];\n                const long long value = static_cast<long\
    \ long>(random() % 101) - 50;\n                fenwick.add(point.first, point.second,\
    \ value);\n                expected[point] += value;\n            } else {\n \
    \               int x_lower = int(random() % 25) - 12;\n                int x_upper\
    \ = int(random() % 25) - 12;\n                int y_lower = int(random() % 25)\
    \ - 12;\n                int y_upper = int(random() % 25) - 12;\n            \
    \    if (x_upper < x_lower) std::swap(x_lower, x_upper);\n                if (y_upper\
    \ < y_lower) std::swap(y_lower, y_upper);\n                assert(\n         \
    \           fenwick.sum(x_lower, x_upper, y_lower, y_upper) ==\n             \
    \       rectangle_sum(expected, x_lower, x_upper, y_lower, y_upper)\n        \
    \        );\n                assert(\n                    fenwick.sum(x_upper,\
    \ y_upper) ==\n                    rectangle_sum(expected, -100, x_upper, -100,\
    \ y_upper)\n                );\n            }\n        }\n    }\n}\n\nstruct Query\
    \ {\n    int type;\n    int first;\n    int second;\n    int third;\n    int fourth;\n\
    \    long long value;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n\
    \    test_randomized();\n\n    int point_count, query_count;\n    fast_input >>\
    \ point_count >> query_count;\n    std::vector<std::tuple<int, int, long long>>\
    \ initial(\n        static_cast<std::size_t>(point_count)\n    );\n    std::vector<Point>\
    \ points;\n    points.reserve(static_cast<std::size_t>(point_count + query_count));\n\
    \    for (auto& [x, y, weight] : initial) {\n        fast_input >> x >> y >> weight;\n\
    \        points.emplace_back(x, y);\n    }\n\n    std::vector<Query> queries(static_cast<std::size_t>(query_count));\n\
    \    for (Query& query : queries) {\n        fast_input >> query.type;\n     \
    \   if (query.type == 0) {\n            fast_input >> query.first >> query.second\
    \ >> query.value;\n            query.third = query.fourth = 0;\n            points.emplace_back(query.first,\
    \ query.second);\n        } else {\n            fast_input >> query.first >> query.second\
    \ >> query.third >> query.fourth;\n            query.value = 0;\n        }\n \
    \   }\n\n    m1une::ds::FenwickTree2D<long long> fenwick(std::move(points));\n\
    \    for (const auto& [x, y, weight] : initial) fenwick.add(x, y, weight);\n\n\
    \    for (const Query& query : queries) {\n        if (query.type == 0) {\n  \
    \          fenwick.add(query.first, query.second, query.value);\n        } else\
    \ {\n            fast_output << fenwick.sum(\n                query.first,\n \
    \               query.third,\n                query.second,\n                query.fourth\n\
    \            ) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/fenwick_tree_2d.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/fenwick_tree_2d.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/fenwick_tree_2d.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/fenwick_tree_2d.test.cpp
- /verify/verify/ds/range_query/fenwick_tree_2d.test.cpp.html
title: verify/ds/range_query/fenwick_tree_2d.test.cpp
---
