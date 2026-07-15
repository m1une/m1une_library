---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: matroid/graphic_matroid.hpp
    title: Graphic Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/partition_matroid.hpp
    title: Partition Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/weighted_matroid_intersection.hpp
    title: Weighted Matroid Intersection
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
  bundledCode: "#line 1 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #include <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #include <type_traits>\n#include <utility>\n#include <unistd.h>\n\nnamespace m1une\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\
    \n#include <random>\n#line 8 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"matroid/graphic_matroid.hpp\"\n\n\n\n#line 5\
    \ \"matroid/graphic_matroid.hpp\"\n#include <numeric>\n#line 8 \"matroid/graphic_matroid.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\nclass GraphicMatroid {\n   private:\n\
    \    int _vertex_count;\n    std::vector<std::pair<int, int>> _edges;\n\n   public:\n\
    \    GraphicMatroid() : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count,\
    \ std::vector<std::pair<int, int>> edges)\n        : _vertex_count(vertex_count),\
    \ _edges(std::move(edges)) {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n\
    \        for (auto [u, v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n\
    \            assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n\
    \    int size() const {\n        return int(_edges.size());\n    }\n\n    int\
    \ vertex_count() const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/partition_matroid.hpp\"\
    \n\n\n\n#line 8 \"matroid/partition_matroid.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matroid {\n\nclass PartitionMatroid {\n   private:\n    std::vector<int> _group;\n\
    \    std::vector<int> _capacity;\n\n    void validate() const {\n#ifndef NDEBUG\n\
    \        for (int capacity : _capacity) assert(0 <= capacity);\n        for (int\
    \ group : _group) assert(0 <= group && group < int(_capacity.size()));\n#endif\n\
    \    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit PartitionMatroid(std::vector<int>\
    \ group) : _group(std::move(group)) {\n        int group_count = 0;\n        for\
    \ (int value : _group) {\n            assert(0 <= value);\n            group_count\
    \ = std::max(group_count, value + 1);\n        }\n        _capacity.assign(group_count,\
    \ 1);\n    }\n\n    PartitionMatroid(std::vector<int> group, std::vector<int>\
    \ capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/weighted_matroid_intersection.hpp\"\
    \n\n\n\n#line 6 \"matroid/weighted_matroid_intersection.hpp\"\n#include <queue>\n\
    #line 10 \"matroid/weighted_matroid_intersection.hpp\"\n\nnamespace m1une {\n\
    namespace matroid {\n\ntemplate <class Weight>\nstruct WeightedMatroidIntersectionResult\
    \ {\n    Weight total_weight = Weight(0);\n    std::vector<int> elements;\n\n\
    \    int size() const {\n        return int(elements.size());\n    }\n\n    bool\
    \ empty() const {\n        return elements.empty();\n    }\n};\n\nnamespace weighted_intersection_detail\
    \ {\n\ntemplate <class Weight>\nstruct QueueGreater {\n    bool operator()(const\
    \ std::pair<Weight, int>& lhs,\n                    const std::pair<Weight, int>&\
    \ rhs) const {\n        if (rhs.first < lhs.first) return true;\n        if (lhs.first\
    \ < rhs.first) return false;\n        return lhs.second > rhs.second;\n    }\n\
    };\n\ntemplate <bool Maximize, class Weight>\nWeight objective_cost(const Weight&\
    \ change) {\n    if constexpr (Maximize) {\n        return Weight(0) - change;\n\
    \    } else {\n        return change;\n    }\n}\n\ntemplate <bool Maximize, class\
    \ Weight, class IndependenceOracle1, class IndependenceOracle2,\n          class\
    \ OnSolution>\nWeightedMatroidIntersectionResult<Weight> solve(\n    int ground_size,\
    \ const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2\
    \ oracle2, OnSolution on_solution) {\n    static_assert(!std::is_arithmetic_v<Weight>\
    \ || std::is_signed_v<Weight>,\n                  \"Weight must support negative\
    \ intermediate values\");\n    assert(0 <= ground_size);\n    assert(int(weight.size())\
    \ == ground_size);\n\n    const int source_vertex = ground_size;\n    const int\
    \ sink_vertex = ground_size + 1;\n    const int vertex_count = ground_size + 2;\n\
    \    std::vector<char> selected(ground_size, false);\n    std::vector<int> elements;\n\
    \    std::vector<int> position(ground_size, -1);\n    std::vector<Weight> potential(vertex_count,\
    \ Weight(0));\n    Weight total_weight = Weight(0);\n    on_solution(0, total_weight,\
    \ elements);\n\n    while (true) {\n        std::vector<std::vector<int>> adjacency(vertex_count);\n\
    \        std::vector<int> sink_predecessors;\n\n        for (int x = 0; x < ground_size;\
    \ x++) {\n            if (selected[x]) continue;\n            elements.push_back(x);\n\
    \            bool source = oracle1(elements);\n            bool sink = oracle2(elements);\n\
    \            elements.pop_back();\n            if (source) adjacency[source_vertex].push_back(x);\n\
    \            if (sink) {\n                adjacency[x].push_back(sink_vertex);\n\
    \                sink_predecessors.push_back(x);\n            }\n        }\n\n\
    \        for (int y : elements) {\n            int index = position[y];\n    \
    \        assert(index != -1 && elements[index] == y);\n            for (int x\
    \ = 0; x < ground_size; x++) {\n                if (selected[x]) continue;\n \
    \               elements[index] = x;\n                if (oracle1(elements)) adjacency[y].push_back(x);\n\
    \                if (oracle2(elements)) adjacency[x].push_back(y);\n         \
    \       elements[index] = y;\n            }\n        }\n\n        if (adjacency[source_vertex].empty()\
    \ || sink_predecessors.empty()) break;\n\n        auto vertex_length = [&](int\
    \ vertex) {\n            if (vertex >= ground_size) return Weight(0);\n      \
    \      Weight change = selected[vertex] ? Weight(0) - weight[vertex] : weight[vertex];\n\
    \            return objective_cost<Maximize>(change);\n        };\n        auto\
    \ reduced_length = [&](int from, int to) {\n            return vertex_length(to)\
    \ - potential[to] + potential[from];\n        };\n\n        int first_source =\
    \ adjacency[source_vertex].front();\n        potential[source_vertex] = potential[first_source]\
    \ - vertex_length(first_source);\n        for (int x : adjacency[source_vertex])\
    \ {\n            Weight candidate = potential[x] - vertex_length(x);\n       \
    \     if (potential[source_vertex] < candidate) potential[source_vertex] = candidate;\n\
    \        }\n        potential[sink_vertex] = potential[sink_predecessors.front()];\n\
    \        for (int x : sink_predecessors) {\n            if (potential[x] < potential[sink_vertex])\
    \ potential[sink_vertex] = potential[x];\n        }\n        Weight source_potential\
    \ = potential[source_vertex];\n        for (Weight& value : potential) value =\
    \ value - source_potential;\n\n#ifndef NDEBUG\n        for (int from = 0; from\
    \ < vertex_count; from++) {\n            for (int to : adjacency[from]) assert(!(reduced_length(from,\
    \ to) < Weight(0)));\n        }\n#endif\n\n        // Dijkstra is performed lazily:\
    \ fixed_distance is added to every\n        // not-yet-fixed potential at once,\
    \ then materialized when a vertex is fixed.\n        using QueueEntry = std::pair<Weight,\
    \ int>;\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueGreater<Weight>>\
    \ heap;\n        std::vector<char> fixed(vertex_count, false);\n        std::vector<char>\
    \ has_distance(vertex_count, false);\n        std::vector<Weight> distance(vertex_count,\
    \ Weight(0));\n        std::vector<int> previous(vertex_count, -1);\n        heap.push({Weight(0),\
    \ source_vertex});\n        has_distance[source_vertex] = true;\n\n        Weight\
    \ fixed_distance = Weight(0);\n        bool reached_sink = false;\n        std::vector<int>\
    \ tight_stack;\n        tight_stack.reserve(vertex_count);\n        while (!heap.empty()\
    \ && !reached_sink) {\n            int start = heap.top().second;\n          \
    \  heap.pop();\n            if (fixed[start]) continue;\n            if (start\
    \ != source_vertex) {\n                assert(previous[start] != -1);\n      \
    \          fixed_distance = reduced_length(previous[start], start);\n        \
    \    }\n\n            tight_stack.clear();\n            fixed[start] = true;\n\
    \            potential[start] = potential[start] + fixed_distance;\n         \
    \   tight_stack.push_back(start);\n\n            while (!tight_stack.empty() &&\
    \ !reached_sink) {\n                int current = tight_stack.back();\n      \
    \          tight_stack.pop_back();\n                if (current == sink_vertex)\
    \ {\n                    reached_sink = true;\n                    break;\n  \
    \              }\n                for (int next : adjacency[current]) {\n    \
    \                if (fixed[next]) continue;\n                    Weight slack\
    \ = reduced_length(current, next) - fixed_distance;\n                    assert(!(slack\
    \ < Weight(0)));\n                    if (!(Weight(0) < slack)) {\n          \
    \              previous[next] = current;\n                        fixed[next]\
    \ = true;\n                        potential[next] = potential[next] + fixed_distance;\n\
    \                        tight_stack.push_back(next);\n                    } else\
    \ {\n                        Weight candidate = fixed_distance + slack;\n    \
    \                    if (!has_distance[next] || candidate < distance[next]) {\n\
    \                            has_distance[next] = true;\n                    \
    \        distance[next] = candidate;\n                            previous[next]\
    \ = current;\n                            heap.push({candidate, next});\n    \
    \                    }\n                    }\n                }\n           \
    \ }\n        }\n\n        for (int vertex = 0; vertex < vertex_count; vertex++)\
    \ {\n            if (!fixed[vertex]) potential[vertex] = potential[vertex] + fixed_distance;\n\
    \        }\n        if (!reached_sink) break;\n\n        std::fill(previous.begin(),\
    \ previous.end(), -1);\n        std::vector<char> reached(vertex_count, false);\n\
    \        std::vector<int> queue;\n        queue.reserve(vertex_count);\n     \
    \   reached[source_vertex] = true;\n        queue.push_back(source_vertex);\n\
    \        for (int head = 0; head < int(queue.size()) && !reached[sink_vertex];\
    \ head++) {\n            int current = queue[head];\n            for (int next\
    \ : adjacency[current]) {\n                if (reached[next]) continue;\n    \
    \            Weight length = reduced_length(current, next);\n                assert(!(length\
    \ < Weight(0)));\n                if (Weight(0) < length) continue;\n        \
    \        reached[next] = true;\n                previous[next] = current;\n  \
    \              queue.push_back(next);\n            }\n        }\n        assert(reached[sink_vertex]);\n\
    \        if (!reached[sink_vertex]) break;\n\n        // A shortest tight path\
    \ with the fewest edges preserves the potential invariant\n        // after its\
    \ elements switch between the inside and outside of the solution.\n        for\
    \ (int v = sink_vertex; v != source_vertex; v = previous[v]) {\n            assert(v\
    \ != -1);\n            if (v < ground_size) {\n                potential[v] =\
    \ potential[v] - vertex_length(v);\n                if (selected[v]) {\n     \
    \               total_weight = total_weight - weight[v];\n                } else\
    \ {\n                    total_weight = total_weight + weight[v];\n          \
    \      }\n                selected[v] = !selected[v];\n            }\n       \
    \ }\n\n        elements.clear();\n        std::fill(position.begin(), position.end(),\
    \ -1);\n        for (int x = 0; x < ground_size; x++) {\n            if (!selected[x])\
    \ continue;\n            position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n        on_solution(int(elements.size()), total_weight, elements);\n \
    \   }\n\n    WeightedMatroidIntersectionResult<Weight> result;\n    result.elements\
    \ = elements;\n    result.total_weight = total_weight;\n    return result;\n}\n\
    \n}  // namespace weighted_intersection_detail\n\ntemplate <class Weight, class\
    \ IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_max(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<true>(ground_size, weight, oracle1, oracle2,\n\
    \                                                      ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<false>(ground_size, weight, oracle1, oracle2,\n\
    \                                                       ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2, class OnSolution>\n\
    WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_max_each(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2, OnSolution on_solution) {\n    return weighted_intersection_detail::solve<true>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \      on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2, class OnSolution>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min_each(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2, OnSolution\
    \ on_solution) {\n    return weighted_intersection_detail::solve<false>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \       on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2) {\n    return weighted_matroid_intersection_max(ground_size,\
    \ weight, oracle1, oracle2);\n}\n\n}  // namespace matroid\n}  // namespace m1une\n\
    \n\n#line 13 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\n\nstruct\
    \ BruteResult {\n    int cardinality = -1;\n    std::vector<long long> minimum_weight;\n\
    \    std::vector<long long> maximum_weight;\n    std::vector<char> exists;\n};\n\
    \ntemplate <class Oracle1, class Oracle2>\nBruteResult brute_force(const std::vector<long\
    \ long>& weight, const Oracle1& oracle1,\n                        const Oracle2&\
    \ oracle2) {\n    int n = int(weight.size());\n    BruteResult result;\n    result.minimum_weight.resize(n\
    \ + 1);\n    result.maximum_weight.resize(n + 1);\n    result.exists.assign(n\
    \ + 1, false);\n    for (int mask = 0; mask < (1 << n); mask++) {\n        std::vector<int>\
    \ subset;\n        long long sum = 0;\n        for (int i = 0; i < n; i++) {\n\
    \            if (mask >> i & 1) {\n                subset.push_back(i);\n    \
    \            sum += weight[i];\n            }\n        }\n        if (!oracle1(subset)\
    \ || !oracle2(subset)) continue;\n        int cardinality = int(subset.size());\n\
    \        result.cardinality = std::max(result.cardinality, cardinality);\n   \
    \     if (!result.exists[cardinality]) {\n            result.exists[cardinality]\
    \ = true;\n            result.minimum_weight[cardinality] = sum;\n           \
    \ result.maximum_weight[cardinality] = sum;\n        } else {\n            result.minimum_weight[cardinality]\
    \ =\n                std::min(result.minimum_weight[cardinality], sum);\n    \
    \        result.maximum_weight[cardinality] =\n                std::max(result.maximum_weight[cardinality],\
    \ sum);\n        }\n    }\n    return result;\n}\n\ntemplate <class Oracle1, class\
    \ Oracle2>\nvoid check(const std::vector<long long>& weight, const Oracle1& oracle1,\n\
    \           const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ expected = brute_force(weight, oracle1, oracle2);\n    auto maximum =\n    \
    \    m1une::matroid::weighted_matroid_intersection_max(n, weight, oracle1, oracle2);\n\
    \    auto minimum =\n        m1une::matroid::weighted_matroid_intersection_min(n,\
    \ weight, oracle1, oracle2);\n    auto default_result =\n        m1une::matroid::weighted_matroid_intersection(n,\
    \ weight, oracle1, oracle2);\n\n    std::vector<long long> maximum_by_cardinality;\n\
    \    std::vector<long long> minimum_by_cardinality;\n    auto streamed_maximum\
    \ = m1une::matroid::weighted_matroid_intersection_max_each(\n        n, weight,\
    \ oracle1, oracle2,\n        [&](int cardinality, const long long& total_weight,\n\
    \            const std::vector<int>& elements) {\n            assert(cardinality\
    \ == int(maximum_by_cardinality.size()));\n            assert(int(elements.size())\
    \ == cardinality);\n            assert(oracle1(elements) && oracle2(elements));\n\
    \            assert(std::is_sorted(elements.begin(), elements.end()));\n     \
    \       long long sum = 0;\n            for (int element : elements) sum += weight[element];\n\
    \            (void)cardinality;\n            (void)sum;\n            assert(sum\
    \ == total_weight);\n            assert(total_weight == expected.maximum_weight[cardinality]);\n\
    \            maximum_by_cardinality.push_back(total_weight);\n        });\n  \
    \  auto streamed_minimum = m1une::matroid::weighted_matroid_intersection_min_each(\n\
    \        n, weight, oracle1, oracle2,\n        [&](int cardinality, const long\
    \ long& total_weight,\n            const std::vector<int>& elements) {\n     \
    \       assert(cardinality == int(minimum_by_cardinality.size()));\n         \
    \   assert(int(elements.size()) == cardinality);\n            assert(oracle1(elements)\
    \ && oracle2(elements));\n            assert(std::is_sorted(elements.begin(),\
    \ elements.end()));\n            long long sum = 0;\n            for (int element\
    \ : elements) sum += weight[element];\n            (void)cardinality;\n      \
    \      (void)sum;\n            assert(sum == total_weight);\n            assert(total_weight\
    \ == expected.minimum_weight[cardinality]);\n            minimum_by_cardinality.push_back(total_weight);\n\
    \        });\n\n    assert(maximum.size() == expected.cardinality);\n    assert(minimum.size()\
    \ == expected.cardinality);\n    assert(maximum.total_weight == expected.maximum_weight[expected.cardinality]);\n\
    \    assert(minimum.total_weight == expected.minimum_weight[expected.cardinality]);\n\
    \    assert(default_result.total_weight == maximum.total_weight);\n    assert(default_result.elements\
    \ == maximum.elements);\n    assert(streamed_maximum.total_weight == maximum.total_weight);\n\
    \    assert(streamed_maximum.elements == maximum.elements);\n    assert(streamed_minimum.total_weight\
    \ == minimum.total_weight);\n    assert(streamed_minimum.elements == minimum.elements);\n\
    \    assert(oracle1(maximum.elements) && oracle2(maximum.elements));\n    assert(oracle1(minimum.elements)\
    \ && oracle2(minimum.elements));\n    assert(std::is_sorted(maximum.elements.begin(),\
    \ maximum.elements.end()));\n    assert(std::is_sorted(minimum.elements.begin(),\
    \ minimum.elements.end()));\n\n    assert(int(maximum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    assert(int(minimum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    for (int cardinality = 0; cardinality <= expected.cardinality;\
    \ cardinality++) {\n        assert(expected.exists[cardinality]);\n        assert(maximum_by_cardinality[cardinality]\
    \ == expected.maximum_weight[cardinality]);\n        assert(minimum_by_cardinality[cardinality]\
    \ == expected.minimum_weight[cardinality]);\n    }\n}\n\nvoid test_weighted_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    std::vector<long\
    \ long> weight = {100, 60, 70};\n    auto result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert((result.elements == std::vector<int>{1, 2}));\n\
    \    assert(result.total_weight == 130);\n\n    std::vector<long long> best_weight;\n\
    \    auto streamed = m1une::matroid::weighted_matroid_intersection_max_each(\n\
    \        3, weight, left, right,\n        [&](int, const long long& total_weight,\
    \ const std::vector<int>&) {\n            best_weight.push_back(total_weight);\n\
    \        });\n    assert((best_weight == std::vector<long long>{0, 100, 130}));\n\
    \    assert(streamed.elements == result.elements);\n    assert(streamed.total_weight\
    \ == result.total_weight);\n\n    weight = {-1, -100, -200};\n    result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert(result.size() == 2);\n    assert(result.total_weight\
    \ == -300);\n}\n\nvoid test_equal_weights() {\n    m1une::matroid::PartitionMatroid\
    \ first(std::vector<int>{0, 0, 1, 1, 2, 2});\n    m1une::matroid::PartitionMatroid\
    \ second(std::vector<int>{0, 1, 1, 2, 2, 0});\n    check(std::vector<long long>(6,\
    \ 0), first, second);\n    check(std::vector<long long>(6, 7), first, second);\n\
    }\n\nvoid test_random_weighted_matroids() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 300; test++) {\n        int n = random() % 10;\n\
    \        std::vector<long long> weight(n);\n        for (long long& value : weight)\
    \ value = int(random() % 41) - 20;\n\n        int group_count = 1 + random() %\
    \ 5;\n        std::vector<int> group(n);\n        for (int& value : group) value\
    \ = random() % group_count;\n        m1une::matroid::PartitionMatroid partition(group);\n\
    \n        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edges(n);\n        for (auto& [u, v] : edges) {\n            u = random()\
    \ % vertex_count;\n            v = random() % vertex_count;\n        }\n     \
    \   m1une::matroid::GraphicMatroid graphic(vertex_count, edges);\n        check(weight,\
    \ partition, graphic);\n\n        int second_group_count = 1 + random() % 5;\n\
    \        std::vector<int> second_group(n);\n        for (int& value : second_group)\
    \ value = random() % second_group_count;\n        m1une::matroid::PartitionMatroid\
    \ second_partition(second_group);\n        check(weight, partition, second_partition);\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_weighted_exchange();\n    test_equal_weights();\n \
    \   test_random_weighted_matroids();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../utilities/fast_io.hpp\"\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../matroid/graphic_matroid.hpp\"\
    \n#include \"../../matroid/partition_matroid.hpp\"\n#include \"../../matroid/weighted_matroid_intersection.hpp\"\
    \n\nstruct BruteResult {\n    int cardinality = -1;\n    std::vector<long long>\
    \ minimum_weight;\n    std::vector<long long> maximum_weight;\n    std::vector<char>\
    \ exists;\n};\n\ntemplate <class Oracle1, class Oracle2>\nBruteResult brute_force(const\
    \ std::vector<long long>& weight, const Oracle1& oracle1,\n                  \
    \      const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ result;\n    result.minimum_weight.resize(n + 1);\n    result.maximum_weight.resize(n\
    \ + 1);\n    result.exists.assign(n + 1, false);\n    for (int mask = 0; mask\
    \ < (1 << n); mask++) {\n        std::vector<int> subset;\n        long long sum\
    \ = 0;\n        for (int i = 0; i < n; i++) {\n            if (mask >> i & 1)\
    \ {\n                subset.push_back(i);\n                sum += weight[i];\n\
    \            }\n        }\n        if (!oracle1(subset) || !oracle2(subset)) continue;\n\
    \        int cardinality = int(subset.size());\n        result.cardinality = std::max(result.cardinality,\
    \ cardinality);\n        if (!result.exists[cardinality]) {\n            result.exists[cardinality]\
    \ = true;\n            result.minimum_weight[cardinality] = sum;\n           \
    \ result.maximum_weight[cardinality] = sum;\n        } else {\n            result.minimum_weight[cardinality]\
    \ =\n                std::min(result.minimum_weight[cardinality], sum);\n    \
    \        result.maximum_weight[cardinality] =\n                std::max(result.maximum_weight[cardinality],\
    \ sum);\n        }\n    }\n    return result;\n}\n\ntemplate <class Oracle1, class\
    \ Oracle2>\nvoid check(const std::vector<long long>& weight, const Oracle1& oracle1,\n\
    \           const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ expected = brute_force(weight, oracle1, oracle2);\n    auto maximum =\n    \
    \    m1une::matroid::weighted_matroid_intersection_max(n, weight, oracle1, oracle2);\n\
    \    auto minimum =\n        m1une::matroid::weighted_matroid_intersection_min(n,\
    \ weight, oracle1, oracle2);\n    auto default_result =\n        m1une::matroid::weighted_matroid_intersection(n,\
    \ weight, oracle1, oracle2);\n\n    std::vector<long long> maximum_by_cardinality;\n\
    \    std::vector<long long> minimum_by_cardinality;\n    auto streamed_maximum\
    \ = m1une::matroid::weighted_matroid_intersection_max_each(\n        n, weight,\
    \ oracle1, oracle2,\n        [&](int cardinality, const long long& total_weight,\n\
    \            const std::vector<int>& elements) {\n            assert(cardinality\
    \ == int(maximum_by_cardinality.size()));\n            assert(int(elements.size())\
    \ == cardinality);\n            assert(oracle1(elements) && oracle2(elements));\n\
    \            assert(std::is_sorted(elements.begin(), elements.end()));\n     \
    \       long long sum = 0;\n            for (int element : elements) sum += weight[element];\n\
    \            (void)cardinality;\n            (void)sum;\n            assert(sum\
    \ == total_weight);\n            assert(total_weight == expected.maximum_weight[cardinality]);\n\
    \            maximum_by_cardinality.push_back(total_weight);\n        });\n  \
    \  auto streamed_minimum = m1une::matroid::weighted_matroid_intersection_min_each(\n\
    \        n, weight, oracle1, oracle2,\n        [&](int cardinality, const long\
    \ long& total_weight,\n            const std::vector<int>& elements) {\n     \
    \       assert(cardinality == int(minimum_by_cardinality.size()));\n         \
    \   assert(int(elements.size()) == cardinality);\n            assert(oracle1(elements)\
    \ && oracle2(elements));\n            assert(std::is_sorted(elements.begin(),\
    \ elements.end()));\n            long long sum = 0;\n            for (int element\
    \ : elements) sum += weight[element];\n            (void)cardinality;\n      \
    \      (void)sum;\n            assert(sum == total_weight);\n            assert(total_weight\
    \ == expected.minimum_weight[cardinality]);\n            minimum_by_cardinality.push_back(total_weight);\n\
    \        });\n\n    assert(maximum.size() == expected.cardinality);\n    assert(minimum.size()\
    \ == expected.cardinality);\n    assert(maximum.total_weight == expected.maximum_weight[expected.cardinality]);\n\
    \    assert(minimum.total_weight == expected.minimum_weight[expected.cardinality]);\n\
    \    assert(default_result.total_weight == maximum.total_weight);\n    assert(default_result.elements\
    \ == maximum.elements);\n    assert(streamed_maximum.total_weight == maximum.total_weight);\n\
    \    assert(streamed_maximum.elements == maximum.elements);\n    assert(streamed_minimum.total_weight\
    \ == minimum.total_weight);\n    assert(streamed_minimum.elements == minimum.elements);\n\
    \    assert(oracle1(maximum.elements) && oracle2(maximum.elements));\n    assert(oracle1(minimum.elements)\
    \ && oracle2(minimum.elements));\n    assert(std::is_sorted(maximum.elements.begin(),\
    \ maximum.elements.end()));\n    assert(std::is_sorted(minimum.elements.begin(),\
    \ minimum.elements.end()));\n\n    assert(int(maximum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    assert(int(minimum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    for (int cardinality = 0; cardinality <= expected.cardinality;\
    \ cardinality++) {\n        assert(expected.exists[cardinality]);\n        assert(maximum_by_cardinality[cardinality]\
    \ == expected.maximum_weight[cardinality]);\n        assert(minimum_by_cardinality[cardinality]\
    \ == expected.minimum_weight[cardinality]);\n    }\n}\n\nvoid test_weighted_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    std::vector<long\
    \ long> weight = {100, 60, 70};\n    auto result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert((result.elements == std::vector<int>{1, 2}));\n\
    \    assert(result.total_weight == 130);\n\n    std::vector<long long> best_weight;\n\
    \    auto streamed = m1une::matroid::weighted_matroid_intersection_max_each(\n\
    \        3, weight, left, right,\n        [&](int, const long long& total_weight,\
    \ const std::vector<int>&) {\n            best_weight.push_back(total_weight);\n\
    \        });\n    assert((best_weight == std::vector<long long>{0, 100, 130}));\n\
    \    assert(streamed.elements == result.elements);\n    assert(streamed.total_weight\
    \ == result.total_weight);\n\n    weight = {-1, -100, -200};\n    result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert(result.size() == 2);\n    assert(result.total_weight\
    \ == -300);\n}\n\nvoid test_equal_weights() {\n    m1une::matroid::PartitionMatroid\
    \ first(std::vector<int>{0, 0, 1, 1, 2, 2});\n    m1une::matroid::PartitionMatroid\
    \ second(std::vector<int>{0, 1, 1, 2, 2, 0});\n    check(std::vector<long long>(6,\
    \ 0), first, second);\n    check(std::vector<long long>(6, 7), first, second);\n\
    }\n\nvoid test_random_weighted_matroids() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 300; test++) {\n        int n = random() % 10;\n\
    \        std::vector<long long> weight(n);\n        for (long long& value : weight)\
    \ value = int(random() % 41) - 20;\n\n        int group_count = 1 + random() %\
    \ 5;\n        std::vector<int> group(n);\n        for (int& value : group) value\
    \ = random() % group_count;\n        m1une::matroid::PartitionMatroid partition(group);\n\
    \n        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edges(n);\n        for (auto& [u, v] : edges) {\n            u = random()\
    \ % vertex_count;\n            v = random() % vertex_count;\n        }\n     \
    \   m1une::matroid::GraphicMatroid graphic(vertex_count, edges);\n        check(weight,\
    \ partition, graphic);\n\n        int second_group_count = 1 + random() % 5;\n\
    \        std::vector<int> second_group(n);\n        for (int& value : second_group)\
    \ value = random() % second_group_count;\n        m1une::matroid::PartitionMatroid\
    \ second_partition(second_group);\n        check(weight, partition, second_partition);\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_weighted_exchange();\n    test_equal_weights();\n \
    \   test_random_weighted_matroids();\n\n    long long a, b;\n    fast_input >>\
    \ a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - matroid/graphic_matroid.hpp
  - matroid/partition_matroid.hpp
  - matroid/weighted_matroid_intersection.hpp
  isVerificationFile: true
  path: verify/matroid/weighted_matroid_intersection.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matroid/weighted_matroid_intersection.test.cpp
layout: document
redirect_from:
- /verify/verify/matroid/weighted_matroid_intersection.test.cpp
- /verify/verify/matroid/weighted_matroid_intersection.test.cpp.html
title: verify/matroid/weighted_matroid_intersection.test.cpp
---
