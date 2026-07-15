---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/monge/all.hpp
    title: Monge All
  - icon: ':heavy_check_mark:'
    path: convex/monge/check.hpp
    title: Monge Checks
  - icon: ':heavy_check_mark:'
    path: convex/monge/divide_and_conquer_optimization.hpp
    title: Divide-and-Conquer DP Optimization
  - icon: ':heavy_check_mark:'
    path: convex/monge/knuth_optimization.hpp
    title: Knuth Optimization
  - icon: ':heavy_check_mark:'
    path: convex/monge/larsch.hpp
    title: LARSCH
  - icon: ':heavy_check_mark:'
    path: convex/monge/min_plus_convolution.hpp
    title: Structured Min-Plus and Max-Plus Convolution
  - icon: ':heavy_check_mark:'
    path: convex/monge/monotone_minima.hpp
    title: Monotone Minima
  - icon: ':heavy_check_mark:'
    path: convex/monge/smawk.hpp
    title: SMAWK
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
  bundledCode: "#line 1 \"verify/convex/monge/monge_algorithms.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#line 1 \"utilities/fast_io.hpp\"\n\
    \n\n\n#include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <type_traits>\n#include <utility>\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/convex/monge/monge_algorithms.test.cpp\"\
    \n#include <limits>\n#include <vector>\n\n#line 1 \"convex/monge/all.hpp\"\n\n\
    \n\n#line 1 \"convex/monge/check.hpp\"\n\n\n\n#line 6 \"convex/monge/check.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class Value>\nbool is_monge(int\
    \ row_count, int column_count, Value value) {\n    assert(row_count >= 0);\n \
    \   assert(column_count >= 0);\n    for (int row = 0; row + 1 < row_count; row++)\
    \ {\n        for (int column = 0; column + 1 < column_count; column++) {\n   \
    \         if (value(row, column) + value(row + 1, column + 1) >\n            \
    \    value(row, column + 1) + value(row + 1, column)) {\n                return\
    \ false;\n            }\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ Value>\nbool is_anti_monge(int row_count, int column_count, Value value) {\n\
    \    assert(row_count >= 0);\n    assert(column_count >= 0);\n    for (int row\
    \ = 0; row + 1 < row_count; row++) {\n        for (int column = 0; column + 1\
    \ < column_count; column++) {\n            if (value(row, column) + value(row\
    \ + 1, column + 1) <\n                value(row, column + 1) + value(row + 1,\
    \ column)) {\n                return false;\n            }\n        }\n    }\n\
    \    return true;\n}\n\ntemplate <class T>\nbool is_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_monge(row_count, column_count,\n          \
    \          [&](int row, int column) -> const T& { return matrix[row][column];\
    \ });\n}\n\ntemplate <class T>\nbool is_anti_monge(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return is_anti_monge(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\n\n\n#line 7 \"convex/monge/divide_and_conquer_optimization.hpp\"\n\n#line\
    \ 1 \"convex/monge/monotone_minima.hpp\"\n\n\n\n#line 7 \"convex/monge/monotone_minima.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace monotone_minima_detail\
    \ {\n\ntemplate <class Value, class Compare>\nvoid solve(int row_left, int row_right,\
    \ int column_left, int column_right,\n           const Value& value, const Compare&\
    \ compare, std::vector<int>& answer) {\n    if (row_left == row_right) return;\n\
    \    int row = (row_left + row_right) / 2;\n    int best = column_left;\n    for\
    \ (int column = column_left + 1; column < column_right; column++) {\n        if\
    \ (compare(value(row, column), value(row, best))) best = column;\n    }\n    answer[row]\
    \ = best;\n    solve(row_left, row, column_left, best + 1, value, compare, answer);\n\
    \    solve(row + 1, row_right, best, column_right, value, compare, answer);\n\
    }\n\n}  // namespace monotone_minima_detail\n\ntemplate <class Value, class Compare\
    \ = std::less<>>\nstd::vector<int> monotone_row_optima(int row_count, int column_count,\
    \ Value value,\n                                     Compare compare = Compare())\
    \ {\n    assert(row_count >= 0);\n    assert(column_count >= 0);\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n    monotone_minima_detail::solve(0, row_count, 0, column_count, value,\
    \ compare, answer);\n    return answer;\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ monotone_row_argmin(int row_count, int column_count, Value value) {\n    return\
    \ monotone_row_optima(row_count, column_count, value, std::less<>());\n}\n\ntemplate\
    \ <class Value>\nstd::vector<int> monotone_row_argmax(int row_count, int column_count,\
    \ Value value) {\n    return monotone_row_optima(row_count, column_count, value,\
    \ std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<int> monotone_row_argmin(const\
    \ std::vector<std::vector<T>>& matrix) {\n    int row_count = int(matrix.size());\n\
    \    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n    for (const\
    \ auto& row : matrix) assert(int(row.size()) == column_count);\n    return monotone_row_argmin(\n\
    \        row_count, column_count,\n        [&](int row, int column) -> const T&\
    \ { return matrix[row][column]; });\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ monotone_row_argmax(const std::vector<std::vector<T>>& matrix) {\n    int row_count\
    \ = int(matrix.size());\n    int column_count = row_count == 0 ? 0 : int(matrix[0].size());\n\
    \    for (const auto& row : matrix) assert(int(row.size()) == column_count);\n\
    \    return monotone_row_argmax(\n        row_count, column_count,\n        [&](int\
    \ row, int column) -> const T& { return matrix[row][column]; });\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/divide_and_conquer_optimization.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nstruct DivideAndConquerDpResult\
    \ {\n    std::vector<T> value;\n    std::vector<int> argmin;\n};\n\ntemplate <class\
    \ Value>\nauto divide_and_conquer_dp(int state_count, int candidate_count, Value\
    \ value)\n    -> DivideAndConquerDpResult<\n        std::decay_t<std::invoke_result_t<Value,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Value, int, int>>;\n\
    \    DivideAndConquerDpResult<T> result;\n    result.argmin = monotone_row_argmin(state_count,\
    \ candidate_count, value);\n    result.value.resize(state_count);\n    for (int\
    \ state = 0; state < state_count; state++) {\n        if (result.argmin[state]\
    \ != -1) {\n            result.value[state] = value(state, result.argmin[state]);\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class T, class Cost>\nauto\
    \ divide_and_conquer_transition(const std::vector<T>& previous, int state_count,\n\
    \                                   Cost cost)\n    -> DivideAndConquerDpResult<\n\
    \        std::decay_t<decltype(std::declval<T>() + cost(0, 0))>> {\n    using\
    \ Result = std::decay_t<decltype(std::declval<T>() + cost(0, 0))>;\n    return\
    \ divide_and_conquer_dp(\n        state_count, int(previous.size()),\n       \
    \ [&](int state, int candidate) -> Result {\n            return previous[candidate]\
    \ + cost(candidate, state);\n        });\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/knuth_optimization.hpp\"\n\n\n\n#line 8 \"\
    convex/monge/knuth_optimization.hpp\"\n\nnamespace m1une {\nnamespace convex {\n\
    \ntemplate <class T>\nstruct KnuthOptimizationResult {\n    std::vector<std::vector<T>>\
    \ value;\n    std::vector<std::vector<int>> split;\n\n    T optimum() const {\n\
    \        return value[0].back();\n    }\n};\n\ntemplate <class IntervalCost>\n\
    auto knuth_optimization(int element_count, IntervalCost interval_cost)\n    ->\
    \ KnuthOptimizationResult<\n        std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>> {\n    assert(element_count >= 0);\n    using T = std::decay_t<std::invoke_result_t<IntervalCost,\
    \ int, int>>;\n\n    KnuthOptimizationResult<T> result;\n    result.value.assign(element_count\
    \ + 1, std::vector<T>(element_count + 1, T()));\n    result.split.assign(element_count\
    \ + 1, std::vector<int>(element_count + 1, -1));\n\n    for (int left = 0; left\
    \ <= element_count; left++) result.split[left][left] = left;\n    for (int left\
    \ = 0; left < element_count; left++) result.split[left][left + 1] = left + 1;\n\
    \n    for (int length = 2; length <= element_count; length++) {\n        for (int\
    \ left = 0; left + length <= element_count; left++) {\n            int right =\
    \ left + length;\n            int first = std::max(left + 1, result.split[left][right\
    \ - 1]);\n            int last = std::min(right - 1, result.split[left + 1][right]);\n\
    \            assert(first <= last);\n\n            int best = first;\n       \
    \     T best_value = result.value[left][best] + result.value[best][right];\n \
    \           for (int split = first + 1; split <= last; split++) {\n          \
    \      T candidate = result.value[left][split] + result.value[split][right];\n\
    \                if (candidate < best_value) {\n                    best = split;\n\
    \                    best_value = candidate;\n                }\n            }\n\
    \            result.value[left][right] = best_value + interval_cost(left, right);\n\
    \            result.split[left][right] = best;\n        }\n    }\n    return result;\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 1 \"convex/monge/larsch.hpp\"\
    \n\n\n\n#line 6 \"convex/monge/larsch.hpp\"\n#include <memory>\n#line 10 \"convex/monge/larsch.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\ntemplate <class T>\nclass Larsch\
    \ {\n    struct ReduceColumn;\n\n    struct ReduceRow {\n        int size;\n \
    \       std::function<T(int, int)> value;\n        int current_row = 0;\n    \
    \    int boundary = 0;\n        std::unique_ptr<ReduceColumn> recursive;\n\n \
    \       explicit ReduceRow(int size_) : size(size_) {\n            if (size /\
    \ 2 != 0) recursive = std::make_unique<ReduceColumn>(size / 2);\n        }\n\n\
    \        void set_value(std::function<T(int, int)> value_) {\n            value\
    \ = std::move(value_);\n            if (recursive) {\n                recursive->set_value(\n\
    \                    [&](int row, int column) { return value(row * 2 + 1, column);\
    \ });\n            }\n        }\n\n        int next_argmin() {\n            int\
    \ row = current_row++;\n            if (row % 2 == 0) {\n                int previous\
    \ = boundary;\n                int next = row + 1 == size ? size - 1 : recursive->next_argmin();\n\
    \                boundary = next;\n                int best = previous;\n    \
    \            for (int column = previous + 1; column <= next; column++) {\n   \
    \                 if (value(row, column) < value(row, best)) best = column;\n\
    \                }\n                return best;\n            }\n            return\
    \ value(row, boundary) <= value(row, row) ? boundary : row;\n        }\n    };\n\
    \n    struct ReduceColumn {\n        int size;\n        std::function<T(int, int)>\
    \ value;\n        int current_row = 0;\n        std::vector<int> columns;\n  \
    \      ReduceRow recursive;\n\n        explicit ReduceColumn(int size_) : size(size_),\
    \ recursive(size_) {}\n\n        void set_value(std::function<T(int, int)> value_)\
    \ {\n            value = std::move(value_);\n            recursive.set_value(\n\
    \                [&](int row, int column) { return value(row, columns[column]);\
    \ });\n        }\n\n        int next_argmin() {\n            int row = current_row++;\n\
    \            int first = row == 0 ? 0 : row * 2 - 1;\n            int last = row\
    \ * 2;\n            for (int column = first; column <= last; column++) {\n   \
    \             while (int(columns.size()) != row &&\n                       value(int(columns.size())\
    \ - 1, columns.back()) >\n                           value(int(columns.size())\
    \ - 1, column)) {\n                    columns.pop_back();\n                }\n\
    \                if (int(columns.size()) != size) columns.push_back(column);\n\
    \            }\n            return columns[recursive.next_argmin()];\n       \
    \ }\n    };\n\n    int _size;\n    int _processed = 0;\n    std::unique_ptr<ReduceRow>\
    \ _base;\n\n   public:\n    template <class Value>\n    explicit Larsch(int size,\
    \ Value value)\n        : _size(size), _base(std::make_unique<ReduceRow>(size))\
    \ {\n        assert(size >= 0);\n        _base->set_value(std::function<T(int,\
    \ int)>(std::move(value)));\n    }\n\n    int size() const {\n        return _size;\n\
    \    }\n\n    int processed_rows() const {\n        return _processed;\n    }\n\
    \n    bool finished() const {\n        return _processed == _size;\n    }\n\n\
    \    int next_argmin() {\n        assert(!finished());\n        _processed++;\n\
    \        return _base->next_argmin();\n    }\n};\n\ntemplate <class T>\nstruct\
    \ LarschShortestPathResult {\n    std::vector<T> distance;\n    std::vector<int>\
    \ parent;\n};\n\ntemplate <class Cost>\nauto larsch_shortest_path(int vertex_count,\
    \ Cost cost)\n    -> LarschShortestPathResult<\n        std::decay_t<std::invoke_result_t<Cost,\
    \ int, int>>> {\n    using T = std::decay_t<std::invoke_result_t<Cost, int, int>>;\n\
    \    assert(vertex_count >= 0);\n\n    LarschShortestPathResult<T> result;\n \
    \   result.distance.assign(vertex_count, T());\n    result.parent.assign(vertex_count,\
    \ -1);\n    if (vertex_count <= 1) return result;\n\n    Larsch<T> optimizer(vertex_count\
    \ - 1, [&](int row, int column) {\n        return result.distance[column] + cost(column,\
    \ row + 1);\n    });\n    for (int vertex = 1; vertex < vertex_count; vertex++)\
    \ {\n        int parent = optimizer.next_argmin();\n        result.parent[vertex]\
    \ = parent;\n        result.distance[vertex] = result.distance[parent] + cost(parent,\
    \ vertex);\n    }\n    return result;\n}\n\n}  // namespace convex\n}  // namespace\
    \ m1une\n\n\n#line 1 \"convex/monge/min_plus_convolution.hpp\"\n\n\n\n#line 7\
    \ \"convex/monge/min_plus_convolution.hpp\"\n\n#line 1 \"convex/monge/smawk.hpp\"\
    \n\n\n\n#line 6 \"convex/monge/smawk.hpp\"\n#include <numeric>\n#line 8 \"convex/monge/smawk.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace smawk_detail {\n\ntemplate\
    \ <class Select>\nvoid solve(const std::vector<int>& rows, const std::vector<int>&\
    \ columns,\n           const Select& select, std::vector<int>& answer) {\n   \
    \ if (rows.empty()) return;\n\n    std::vector<int> reduced;\n    reduced.reserve(columns.size());\n\
    \    for (int column : columns) {\n        while (!reduced.empty()) {\n      \
    \      int row = rows[int(reduced.size()) - 1];\n            if (!select(row,\
    \ reduced.back(), column)) break;\n            reduced.pop_back();\n        }\n\
    \        if (reduced.size() < rows.size()) reduced.push_back(column);\n    }\n\
    \n    std::vector<int> odd_rows;\n    odd_rows.reserve(rows.size() / 2);\n   \
    \ for (int i = 1; i < int(rows.size()); i += 2) odd_rows.push_back(rows[i]);\n\
    \    solve(odd_rows, reduced, select, answer);\n\n    int left = 0;\n    int right\
    \ = 0;\n    for (int i = 0; i < int(rows.size()); i += 2) {\n        if (i + 1\
    \ < int(rows.size())) {\n            while (reduced[right] != answer[rows[i +\
    \ 1]]) right++;\n        } else {\n            right = int(reduced.size()) - 1;\n\
    \        }\n\n        int best = left;\n        for (int j = left + 1; j <= right;\
    \ j++) {\n            if (select(rows[i], reduced[best], reduced[j])) {\n    \
    \            best = j;\n            }\n        }\n        answer[rows[i]] = reduced[best];\n\
    \        left = right;\n    }\n}\n\ntemplate <class Select>\nstd::vector<int>\
    \ row_optima(int row_count, int column_count, const Select& select) {\n    std::vector<int>\
    \ answer(row_count, -1);\n    if (row_count == 0 || column_count == 0) return\
    \ answer;\n\n    std::vector<int> rows(row_count), columns(column_count);\n  \
    \  std::iota(rows.begin(), rows.end(), 0);\n    std::iota(columns.begin(), columns.end(),\
    \ 0);\n    solve(rows, columns, select, answer);\n    return answer;\n}\n\n} \
    \ // namespace smawk_detail\n\ntemplate <class Value, class Compare = std::less<>>\n\
    std::vector<int> smawk_row_optima(int row_count, int column_count, Value value,\n\
    \                                  Compare compare = Compare()) {\n    assert(row_count\
    \ >= 0);\n    assert(column_count >= 0);\n    return smawk_detail::row_optima(\n\
    \        row_count, column_count,\n        [&](int row, int current, int candidate)\
    \ {\n            return compare(value(row, candidate), value(row, current));\n\
    \        });\n}\n\ntemplate <class Value>\nstd::vector<int> smawk_row_argmin(int\
    \ row_count, int column_count, Value value) {\n    return smawk_row_optima(row_count,\
    \ column_count, value, std::less<>());\n}\n\ntemplate <class Value>\nstd::vector<int>\
    \ smawk_row_argmax(int row_count, int column_count, Value value) {\n    return\
    \ smawk_row_optima(row_count, column_count, value, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<int> smawk_row_argmin(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmin(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\ntemplate <class T>\nstd::vector<int> smawk_row_argmax(const std::vector<std::vector<T>>&\
    \ matrix) {\n    int row_count = int(matrix.size());\n    int column_count = row_count\
    \ == 0 ? 0 : int(matrix[0].size());\n    for (const auto& row : matrix) assert(int(row.size())\
    \ == column_count);\n    return smawk_row_argmax(\n        row_count, column_count,\n\
    \        [&](int row, int column) -> const T& { return matrix[row][column]; });\n\
    }\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line 9 \"convex/monge/min_plus_convolution.hpp\"\
    \n\nnamespace m1une {\nnamespace convex {\n\nnamespace convolution_detail {\n\n\
    template <class T, class Compare, class Add>\nstd::vector<T> structured_convolution(const\
    \ std::vector<T>& arbitrary,\n                                      const std::vector<T>&\
    \ structured,\n                                      Compare compare, Add add)\
    \ {\n    if (arbitrary.empty() || structured.empty()) return {};\n\n    int first_size\
    \ = int(arbitrary.size());\n    int second_size = int(structured.size());\n  \
    \  int result_size = first_size + second_size - 1;\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= second_size) return true;\n        T\
    \ current_value = add(arbitrary[current], structured[index - current]);\n    \
    \    T candidate_value = add(arbitrary[candidate], structured[index - candidate]);\n\
    \        return !compare(current_value, candidate_value);\n    };\n\n    std::vector<int>\
    \ optima =\n        smawk_detail::row_optima(result_size, first_size, select);\n\
    \    std::vector<T> result;\n    result.reserve(result_size);\n    for (int index\
    \ = 0; index < result_size; index++) {\n        int first_index = optima[index];\n\
    \        result.emplace_back(add(arbitrary[first_index],\n                   \
    \             structured[index - first_index]));\n    }\n    return result;\n\
    }\n\ntemplate <class T>\nstd::pair<int, int> finite_interval(const std::vector<T>&\
    \ sequence,\n                                    const T& infinity) {\n    int\
    \ left = 0;\n    while (left < int(sequence.size()) && sequence[left] == infinity)\
    \ left++;\n    int right = int(sequence.size());\n    while (right > left && sequence[right\
    \ - 1] == infinity) right--;\n    return {left, right};\n}\n\ntemplate <class\
    \ T, class Compare>\nstd::vector<T> structured_convolution_with_infinity(\n  \
    \  const std::vector<T>& arbitrary, const std::vector<T>& structured,\n    const\
    \ T& infinity, Compare compare) {\n    if (arbitrary.empty() || structured.empty())\
    \ return {};\n\n    auto [left, right] = finite_interval(structured, infinity);\n\
    \    int result_size = int(arbitrary.size() + structured.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (left == right) return result;\n\n  \
    \  std::vector<int> columns;\n    columns.reserve(arbitrary.size());\n    for\
    \ (int i = 0; i < int(arbitrary.size()); i++) {\n        if (arbitrary[i] != infinity)\
    \ columns.push_back(i);\n    }\n    if (columns.empty()) return result;\n\n  \
    \  int finite_size = right - left;\n    int middle_size = int(arbitrary.size())\
    \ + finite_size - 1;\n    std::vector<int> rows;\n    rows.reserve(middle_size);\n\
    \    int active = 0;\n    for (int row = 0; row < middle_size; row++) {\n    \
    \    if (row < int(arbitrary.size()) && arbitrary[row] != infinity) active++;\n\
    \        if (row >= finite_size && arbitrary[row - finite_size] != infinity) active--;\n\
    \        if (active > 0) rows.push_back(row);\n    }\n\n    auto select = [&](int\
    \ index, int current, int candidate) {\n        if (index < candidate) return\
    \ false;\n        if (index - current >= finite_size) return true;\n        T\
    \ current_value =\n            arbitrary[current] + structured[left + index -\
    \ current];\n        T candidate_value =\n            arbitrary[candidate] + structured[left\
    \ + index - candidate];\n        return !compare(current_value, candidate_value);\n\
    \    };\n    std::vector<int> optima(middle_size, -1);\n    smawk_detail::solve(rows,\
    \ columns, select, optima);\n    for (int row : rows) {\n        int first_index\
    \ = optima[row];\n        result[left + row] =\n            arbitrary[first_index]\
    \ + structured[left + row - first_index];\n    }\n    return result;\n}\n\ntemplate\
    \ <class T, class Compare>\nstd::vector<T> linear_structured_convolution(const\
    \ std::vector<T>& first,\n                                             const std::vector<T>&\
    \ second,\n                                             Compare compare) {\n \
    \   if (first.empty() || second.empty()) return {};\n\n    int first_size = int(first.size());\n\
    \    int second_size = int(second.size());\n    std::vector<T> result(first_size\
    \ + second_size - 1);\n    result[0] = first[0] + second[0];\n\n    int first_index\
    \ = 1;\n    int second_index = 1;\n    int result_index = 1;\n    while (first_index\
    \ < first_size && second_index < second_size) {\n        T first_difference =\
    \ first[first_index] - first[first_index - 1];\n        T second_difference =\
    \ second[second_index] - second[second_index - 1];\n        if (compare(second_difference,\
    \ first_difference)) {\n            result[result_index] = result[result_index\
    \ - 1] + second_difference;\n            second_index++;\n        } else {\n \
    \           result[result_index] = result[result_index - 1] + first_difference;\n\
    \            first_index++;\n        }\n        result_index++;\n    }\n    while\
    \ (first_index < first_size) {\n        T difference = first[first_index] - first[first_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        first_index++;\n        result_index++;\n    }\n    while (second_index\
    \ < second_size) {\n        T difference = second[second_index] - second[second_index\
    \ - 1];\n        result[result_index] = result[result_index - 1] + difference;\n\
    \        second_index++;\n        result_index++;\n    }\n    return result;\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> linear_structured_convolution_with_infinity(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity, Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n\n    auto [first_left, first_right] = finite_interval(first, infinity);\n\
    \    auto [second_left, second_right] = finite_interval(second, infinity);\n \
    \   int result_size = int(first.size() + second.size() - 1);\n    std::vector<T>\
    \ result(result_size, infinity);\n    if (first_left == first_right || second_left\
    \ == second_right) return result;\n\n    int offset = first_left + second_left;\n\
    \    result[offset] = first[first_left] + second[second_left];\n\n    int first_index\
    \ = first_left + 1;\n    int second_index = second_left + 1;\n    int result_index\
    \ = offset + 1;\n    while (first_index < first_right && second_index < second_right)\
    \ {\n        T first_difference = first[first_index] - first[first_index - 1];\n\
    \        T second_difference = second[second_index] - second[second_index - 1];\n\
    \        if (compare(second_difference, first_difference)) {\n            result[result_index]\
    \ = result[result_index - 1] + second_difference;\n            second_index++;\n\
    \        } else {\n            result[result_index] = result[result_index - 1]\
    \ + first_difference;\n            first_index++;\n        }\n        result_index++;\n\
    \    }\n    while (first_index < first_right) {\n        T difference = first[first_index]\
    \ - first[first_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        first_index++;\n        result_index++;\n    }\n\
    \    while (second_index < second_right) {\n        T difference = second[second_index]\
    \ - second[second_index - 1];\n        result[result_index] = result[result_index\
    \ - 1] + difference;\n        second_index++;\n        result_index++;\n    }\n\
    \    return result;\n}\n\ntemplate <class T, class Compare>\nbool is_structured_sequence_with_infinity(const\
    \ std::vector<T>& sequence,\n                                          const T&\
    \ infinity, Compare violation) {\n    auto [left, right] = finite_interval(sequence,\
    \ infinity);\n    for (int i = left; i < right; i++) {\n        if (sequence[i]\
    \ == infinity) return false;\n    }\n    for (int i = left + 1; i + 1 < right;\
    \ i++) {\n        T first_difference = sequence[i] - sequence[i - 1];\n      \
    \  T second_difference = sequence[i + 1] - sequence[i];\n        if (violation(first_difference,\
    \ second_difference)) return false;\n    }\n    return true;\n}\n\n}  // namespace\
    \ convolution_detail\n\ntemplate <class T>\nbool is_convex_sequence(const std::vector<T>&\
    \ sequence) {\n    for (int i = 1; i + 1 < int(sequence.size()); i++) {\n    \
    \    if (sequence[i] - sequence[i - 1] > sequence[i + 1] - sequence[i]) {\n  \
    \          return false;\n        }\n    }\n    return true;\n}\n\ntemplate <class\
    \ T>\nbool is_convex_sequence(const std::vector<T>& sequence, const T& infinity)\
    \ {\n    return convolution_detail::is_structured_sequence_with_infinity(\n  \
    \      sequence, infinity, std::greater<>());\n}\n\ntemplate <class T>\nbool is_concave_sequence(const\
    \ std::vector<T>& sequence) {\n    for (int i = 1; i + 1 < int(sequence.size());\
    \ i++) {\n        if (sequence[i] - sequence[i - 1] < sequence[i + 1] - sequence[i])\
    \ {\n            return false;\n        }\n    }\n    return true;\n}\n\ntemplate\
    \ <class T>\nbool is_concave_sequence(const std::vector<T>& sequence,\n      \
    \                   const T& negative_infinity) {\n    return convolution_detail::is_structured_sequence_with_infinity(\n\
    \        sequence, negative_infinity, std::less<>());\n}\n\ntemplate <class T>\n\
    std::vector<T> min_plus_convolution_convex(const std::vector<T>& arbitrary,\n\
    \                                           const std::vector<T>& convex) {\n\
    \    auto add = [](const T& first, const T& second) { return first + second; };\n\
    \    return convolution_detail::structured_convolution(arbitrary, convex,\n  \
    \                                                    std::less<>(), add);\n}\n\
    \ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex(const std::vector<T>&\
    \ arbitrary,\n                                           const std::vector<T>&\
    \ convex,\n                                           const T& infinity) {\n \
    \   return convolution_detail::structured_convolution_with_infinity(\n       \
    \ arbitrary, convex, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ min_plus_convolution_convex_convex(const std::vector<T>& first,\n          \
    \                                        const std::vector<T>& second) {\n   \
    \ return convolution_detail::linear_structured_convolution(first, second, std::less<>());\n\
    }\n\ntemplate <class T>\nstd::vector<T> min_plus_convolution_convex_convex(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, infinity, std::less<>());\n}\n\ntemplate <class T>\nstd::vector<T>\
    \ max_plus_convolution_concave(const std::vector<T>& arbitrary,\n            \
    \                                const std::vector<T>& concave) {\n    auto add\
    \ = [](const T& first, const T& second) { return first + second; };\n    return\
    \ convolution_detail::structured_convolution(arbitrary, concave,\n           \
    \                                           std::greater<>(), add);\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave(const std::vector<T>&\
    \ arbitrary,\n                                            const std::vector<T>&\
    \ concave,\n                                            const T& negative_infinity)\
    \ {\n    return convolution_detail::structured_convolution_with_infinity(\n  \
    \      arbitrary, concave, negative_infinity, std::greater<>());\n}\n\ntemplate\
    \ <class T>\nstd::vector<T> max_plus_convolution_concave_concave(const std::vector<T>&\
    \ first,\n                                                    const std::vector<T>&\
    \ second) {\n    return convolution_detail::linear_structured_convolution(first,\
    \ second, std::greater<>());\n}\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution_concave_concave(\n\
    \    const std::vector<T>& first, const std::vector<T>& second,\n    const T&\
    \ negative_infinity) {\n    return convolution_detail::linear_structured_convolution_with_infinity(\n\
    \        first, second, negative_infinity, std::greater<>());\n}\n\n}  // namespace\
    \ convex\n}  // namespace m1une\n\n\n#line 11 \"convex/monge/all.hpp\"\n\n\n#line\
    \ 11 \"verify/convex/monge/monge_algorithms.test.cpp\"\n\ntemplate <class Value,\
    \ class Compare>\nstd::vector<int> brute_row_optima(int rows, int columns, Value\
    \ value, Compare compare) {\n    std::vector<int> result(rows, -1);\n    if (columns\
    \ == 0) return result;\n    for (int row = 0; row < rows; row++) {\n        result[row]\
    \ = 0;\n        for (int column = 1; column < columns; column++) {\n         \
    \   if (compare(value(row, column), value(row, result[row]))) {\n            \
    \    result[row] = column;\n            }\n        }\n    }\n    return result;\n\
    }\n\nvoid test_smawk_monge() {\n    for (int rows = 0; rows <= 40; rows++) {\n\
    \        for (int columns = 0; columns <= 40; columns++) {\n            auto value\
    \ = [&](int row, int column) {\n                long long difference = row * 3LL\
    \ - column * 2LL;\n                return difference * difference + row * 7LL\
    \ + column * 5LL;\n            };\n            auto expected = brute_row_optima(rows,\
    \ columns, value, std::less<>());\n            assert(m1une::convex::smawk_row_argmin(rows,\
    \ columns, value) == expected);\n        }\n    }\n}\n\nvoid test_smawk_totally_monotone_and_ties()\
    \ {\n    for (int rows = 1; rows <= 50; rows++) {\n        for (int columns =\
    \ 1; columns <= 50; columns++) {\n            std::vector<int> threshold(rows);\n\
    \            for (int row = 0; row < rows; row++) {\n                threshold[row]\
    \ = std::min(columns - 1, (row * 7 + rows) / 5);\n            }\n            auto\
    \ value = [&](int row, int column) {\n                int difference = column\
    \ - threshold[row];\n                return difference * difference;\n       \
    \     };\n            auto result = m1une::convex::smawk_row_argmin(rows, columns,\
    \ value);\n            assert(result == threshold);\n        }\n    }\n\n    auto\
    \ constant = [](int, int) { return 0; };\n    auto result = m1une::convex::smawk_row_argmin(20,\
    \ 30, constant);\n    assert(result == std::vector<int>(20, 0));\n}\n\nvoid test_smawk_max()\
    \ {\n    auto value = [](int row, int column) {\n        long long difference\
    \ = row - column;\n        return -difference * difference;\n    };\n    auto\
    \ expected = brute_row_optima(30, 25, value, std::greater<>());\n    assert(m1une::convex::smawk_row_argmax(30,\
    \ 25, value) == expected);\n}\n\nvoid test_smawk_matrix_overload_and_evaluations()\
    \ {\n    std::vector<std::vector<long long>> matrix(17, std::vector<long long>(23));\n\
    \    for (int row = 0; row < 17; row++) {\n        for (int column = 0; column\
    \ < 23; column++) {\n            long long difference = row * 2LL - column;\n\
    \            matrix[row][column] = difference * difference;\n        }\n    }\n\
    \    auto expected = brute_row_optima(\n        17, 23, [&](int row, int column)\
    \ { return matrix[row][column]; }, std::less<>());\n    assert(m1une::convex::smawk_row_argmin(matrix)\
    \ == expected);\n\n    for (auto sizes : std::vector<std::pair<int, int>>{\n \
    \            std::pair<int, int>{10, 1000},\n             std::pair<int, int>{1000,\
    \ 10},\n             std::pair<int, int>{700, 900},\n         }) {\n        int\
    \ evaluations = 0;\n        auto value = [&](int row, int column) {\n        \
    \    evaluations++;\n            long long difference = row * 3LL - column * 2LL;\n\
    \            return difference * difference;\n        };\n        auto result\
    \ = m1une::convex::smawk_row_argmin(sizes.first, sizes.second, value);\n     \
    \   assert(int(result.size()) == sizes.first);\n        assert(evaluations <=\
    \ 20 * (sizes.first + sizes.second));\n    }\n}\n\nvoid test_monotone_minima()\
    \ {\n    for (int rows = 1; rows <= 40; rows++) {\n        for (int columns =\
    \ 1; columns <= 40; columns++) {\n            std::vector<int> optimum(rows);\n\
    \            for (int row = 0; row < rows; row++) {\n                optimum[row]\
    \ = std::min(columns - 1, row * columns / rows);\n            }\n            auto\
    \ value = [&](int row, int column) {\n                if (column == optimum[row])\
    \ return 0;\n                return 1000 + (row * 97 + column * 53) % 101;\n \
    \           };\n            auto result = m1une::convex::monotone_row_argmin(rows,\
    \ columns, value);\n            assert(result == optimum);\n        }\n    }\n\
    \n    auto empty = m1une::convex::monotone_row_argmin(5, 0, [](int, int) { return\
    \ 0; });\n    assert(empty == std::vector<int>(5, -1));\n\n    std::vector<std::vector<int>>\
    \ matrix;\n    matrix.emplace_back(std::vector<int>{0, 5, 7});\n    matrix.emplace_back(std::vector<int>{4,\
    \ 0, 8});\n    matrix.emplace_back(std::vector<int>{9, 3, 0});\n    assert(m1une::convex::monotone_row_argmin(matrix)\
    \ == std::vector<int>({0, 1, 2}));\n}\n\nvoid test_monge_checks() {\n    std::vector<std::vector<long\
    \ long>> matrix(8, std::vector<long long>(11));\n    for (int row = 0; row < 8;\
    \ row++) {\n        for (int column = 0; column < 11; column++) {\n          \
    \  long long difference = row - column;\n            matrix[row][column] = difference\
    \ * difference;\n        }\n    }\n    assert(m1une::convex::is_monge(matrix));\n\
    \    assert(!m1une::convex::is_anti_monge(matrix));\n\n    for (auto& row : matrix)\
    \ {\n        for (auto& value : row) value = -value;\n    }\n    assert(!m1une::convex::is_monge(matrix));\n\
    \    assert(m1une::convex::is_anti_monge(matrix));\n\n    std::vector<std::vector<int>>\
    \ empty;\n    assert(m1une::convex::is_monge(empty));\n    assert(m1une::convex::is_anti_monge(empty));\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> brute_convolution(const\
    \ std::vector<T>& first, const std::vector<T>& second,\n                     \
    \            Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n    std::vector<T> result(first.size() + second.size() - 1);\n    for (int\
    \ index = 0; index < int(result.size()); index++) {\n        int left = std::max(0,\
    \ index - int(second.size()) + 1);\n        int right = std::min(int(first.size()),\
    \ index + 1);\n        result[index] = first[left] + second[index - left];\n \
    \       for (int i = left + 1; i < right; i++) {\n            T value = first[i]\
    \ + second[index - i];\n            if (compare(value, result[index])) result[index]\
    \ = value;\n        }\n    }\n    return result;\n}\n\ntemplate <class T, class\
    \ Compare>\nstd::vector<T> brute_convolution_with_infinity(const std::vector<T>&\
    \ first,\n                                               const std::vector<T>&\
    \ second,\n                                               Compare compare,\n \
    \                                              const T& infinity) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    std::vector<T> result(first.size() + second.size()\
    \ - 1, infinity);\n    for (int i = 0; i < int(first.size()); i++) {\n       \
    \ for (int j = 0; j < int(second.size()); j++) {\n            if (first[i] ==\
    \ infinity || second[j] == infinity) continue;\n            T value = first[i]\
    \ + second[j];\n            if (result[i + j] == infinity || compare(value, result[i\
    \ + j])) {\n                result[i + j] = value;\n            }\n        }\n\
    \    }\n    return result;\n}\n\nvoid test_structured_convolutions() {\n    const\
    \ long long infinity = 2'000'000'000'000'000'000LL;\n    const long long negative_infinity\
    \ = -infinity;\n    for (int first_size = 0; first_size <= 35; first_size++) {\n\
    \        for (int second_size = 0; second_size <= 35; second_size++) {\n     \
    \       for (int test = 0; test < 8; test++) {\n                std::vector<long\
    \ long> arbitrary(first_size);\n                for (int i = 0; i < first_size;\
    \ i++) {\n                    arbitrary[i] = (test * 17 + i * 31 + first_size\
    \ * 7) % 61 - 30;\n                }\n\n                std::vector<long long>\
    \ convex(second_size);\n                long long difference = -10 + test;\n \
    \               for (int i = 1; i < second_size; i++) {\n                    difference\
    \ += (test * 3 + i * 5) % 4;\n                    convex[i] = convex[i - 1] +\
    \ difference;\n                }\n                assert(m1une::convex::is_convex_sequence(convex));\n\
    \                auto expected_min = brute_convolution(arbitrary, convex, std::less<>());\n\
    \                assert(m1une::convex::min_plus_convolution_convex(arbitrary,\
    \ convex) ==\n                       expected_min);\n\n                std::vector<long\
    \ long> arbitrary_extended = arbitrary;\n                for (int i = 0; i < first_size;\
    \ i++) {\n                    if ((i + test) % 7 == 0) arbitrary_extended[i] =\
    \ infinity;\n                }\n                std::vector<long long> convex_extended(second_size\
    \ + 2, infinity);\n                std::copy(convex.begin(), convex.end(), convex_extended.begin()\
    \ + 1);\n                assert(m1une::convex::is_convex_sequence(convex_extended,\
    \ infinity));\n                auto expected_extended_min = brute_convolution_with_infinity(\n\
    \                    arbitrary_extended, convex_extended, std::less<>(), infinity);\n\
    \                assert(m1une::convex::min_plus_convolution_convex(\n        \
    \                   arbitrary_extended, convex_extended, infinity) ==\n      \
    \                 expected_extended_min);\n\n                std::vector<long\
    \ long> first_convex(first_size);\n                difference = -12 - test;\n\
    \                for (int i = 1; i < first_size; i++) {\n                    difference\
    \ += (test * 5 + i * 7) % 5;\n                    first_convex[i] = first_convex[i\
    \ - 1] + difference;\n                }\n                assert(m1une::convex::is_convex_sequence(first_convex));\n\
    \                auto expected_convex =\n                    brute_convolution(first_convex,\
    \ convex, std::less<>());\n                assert(m1une::convex::min_plus_convolution_convex(first_convex,\
    \ convex) ==\n                       expected_convex);\n                assert(m1une::convex::min_plus_convolution_convex(convex,\
    \ first_convex) ==\n                       expected_convex);\n               \
    \ assert(m1une::convex::min_plus_convolution_convex_convex(first_convex,\n   \
    \                                                                     convex)\
    \ ==\n                       expected_convex);\n                assert(m1une::convex::min_plus_convolution_convex_convex(convex,\n\
    \                                                                        first_convex)\
    \ ==\n                       expected_convex);\n\n                std::vector<long\
    \ long> first_convex_extended(first_size + 2,\n                              \
    \                                infinity);\n                std::copy(first_convex.begin(),\
    \ first_convex.end(),\n                          first_convex_extended.begin()\
    \ + 1);\n                auto expected_extended_convex = brute_convolution_with_infinity(\n\
    \                    first_convex_extended, convex_extended, std::less<>(), infinity);\n\
    \                assert(m1une::convex::min_plus_convolution_convex_convex(\n \
    \                          first_convex_extended, convex_extended, infinity) ==\n\
    \                       expected_extended_convex);\n\n                std::vector<long\
    \ long> concave = convex;\n                for (auto& value : concave) value =\
    \ -value;\n                assert(m1une::convex::is_concave_sequence(concave));\n\
    \                auto expected_max = brute_convolution(arbitrary, concave, std::greater<>());\n\
    \                assert(m1une::convex::max_plus_convolution_concave(arbitrary,\
    \ concave) ==\n                       expected_max);\n\n                std::vector<long\
    \ long> first_concave = first_convex;\n                for (auto& value : first_concave)\
    \ value = -value;\n                assert(m1une::convex::is_concave_sequence(first_concave));\n\
    \                auto expected_concave =\n                    brute_convolution(first_concave,\
    \ concave, std::greater<>());\n                assert(m1une::convex::max_plus_convolution_concave(first_concave,\
    \ concave) ==\n                       expected_concave);\n                assert(m1une::convex::max_plus_convolution_concave(concave,\
    \ first_concave) ==\n                       expected_concave);\n             \
    \   assert(m1une::convex::max_plus_convolution_concave_concave(first_concave,\n\
    \                                                                          concave)\
    \ ==\n                       expected_concave);\n                assert(m1une::convex::max_plus_convolution_concave_concave(concave,\n\
    \                                                                          first_concave)\
    \ ==\n                       expected_concave);\n\n                std::vector<long\
    \ long> arbitrary_max_extended = arbitrary_extended;\n                for (long\
    \ long& value : arbitrary_max_extended) {\n                    value = value ==\
    \ infinity ? negative_infinity : -value;\n                }\n                std::vector<long\
    \ long> concave_extended = convex_extended;\n                for (long long& value\
    \ : concave_extended) {\n                    value = value == infinity ? negative_infinity\
    \ : -value;\n                }\n                auto expected_extended_max = brute_convolution_with_infinity(\n\
    \                    arbitrary_max_extended, concave_extended, std::greater<>(),\n\
    \                    negative_infinity);\n                assert(m1une::convex::max_plus_convolution_concave(\n\
    \                           arbitrary_max_extended, concave_extended,\n      \
    \                     negative_infinity) == expected_extended_max);\n\n      \
    \          std::vector<long long> first_concave_extended =\n                 \
    \   first_convex_extended;\n                for (long long& value : first_concave_extended)\
    \ {\n                    value = value == infinity ? negative_infinity : -value;\n\
    \                }\n                auto expected_extended_concave = brute_convolution_with_infinity(\n\
    \                    first_concave_extended, concave_extended, std::greater<>(),\n\
    \                    negative_infinity);\n                assert(m1une::convex::max_plus_convolution_concave_concave(\n\
    \                           first_concave_extended, concave_extended,\n      \
    \                     negative_infinity) == expected_extended_concave);\n    \
    \        }\n        }\n    }\n\n    assert(!m1une::convex::is_convex_sequence(std::vector<int>{0,\
    \ 2, 1}));\n    assert(!m1une::convex::is_concave_sequence(std::vector<int>{0,\
    \ -2, -1}));\n    assert(!m1une::convex::is_convex_sequence(\n        std::vector<long\
    \ long>{1, infinity, infinity}));\n    assert(m1une::convex::is_convex_sequence(\n\
    \        std::vector<long long>{1, infinity, infinity}, infinity));\n    assert(m1une::convex::is_convex_sequence(\n\
    \        std::vector<long long>{infinity, 0, 1, 4, infinity}, infinity));\n  \
    \  assert(!m1une::convex::is_convex_sequence(\n        std::vector<long long>{0,\
    \ infinity, 1}, infinity));\n\n    std::vector<long long> arbitrary = {infinity,\
    \ 3, infinity, -2};\n    std::vector<long long> convex = {infinity, 0, 1, 4, infinity,\
    \ infinity};\n    auto expected_min =\n        brute_convolution_with_infinity(arbitrary,\
    \ convex, std::less<>(), infinity);\n    assert(m1une::convex::min_plus_convolution_convex(arbitrary,\
    \ convex, infinity) ==\n           expected_min);\n\n    std::vector<long long>\
    \ first_convex = {infinity, 2, 2, 3, infinity};\n    expected_min = brute_convolution_with_infinity(first_convex,\
    \ convex,\n                                                   std::less<>(), infinity);\n\
    \    assert(m1une::convex::min_plus_convolution_convex_convex(\n             \
    \  first_convex, convex, infinity) == expected_min);\n\n    long long unordered_infinity\
    \ = 7;\n    std::vector<long long> large_arbitrary = {10, 20};\n    std::vector<long\
    \ long> small_convex = {0, 1};\n    assert(m1une::convex::min_plus_convolution_convex(\n\
    \               large_arbitrary, small_convex, unordered_infinity) ==\n      \
    \     std::vector<long long>({10, 11, 21}));\n\n    std::vector<long long> arbitrary_max\
    \ = {negative_infinity, 3,\n                                             negative_infinity,\
    \ -2};\n    std::vector<long long> concave = {negative_infinity, 0, -1, -4,\n\
    \                                      negative_infinity};\n    assert(m1une::convex::is_concave_sequence(concave,\
    \ negative_infinity));\n    auto expected_max = brute_convolution_with_infinity(\n\
    \        arbitrary_max, concave, std::greater<>(), negative_infinity);\n    assert(m1une::convex::max_plus_convolution_concave(\n\
    \               arbitrary_max, concave, negative_infinity) == expected_max);\n\
    \n    std::vector<long long> first_concave = {negative_infinity, 2, 2, 1,\n  \
    \                                          negative_infinity};\n    expected_max\
    \ = brute_convolution_with_infinity(\n        first_concave, concave, std::greater<>(),\
    \ negative_infinity);\n    assert(m1une::convex::max_plus_convolution_concave_concave(\n\
    \               first_concave, concave, negative_infinity) == expected_max);\n\
    \n    std::vector<long long> all_infinity(3, infinity);\n    assert(m1une::convex::is_convex_sequence(all_infinity,\
    \ infinity));\n    assert(m1une::convex::min_plus_convolution_convex_convex(\n\
    \               all_infinity, convex, infinity) ==\n           std::vector<long\
    \ long>(all_infinity.size() + convex.size() - 1,\n                           \
    \       infinity));\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_smawk_monge();\n  \
    \  test_smawk_totally_monotone_and_ties();\n    test_smawk_max();\n    test_smawk_matrix_overload_and_evaluations();\n\
    \    test_monotone_minima();\n    test_monge_checks();\n    test_structured_convolutions();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <limits>\n#include <vector>\n\n#include \"../../../convex/monge/all.hpp\"\
    \n\ntemplate <class Value, class Compare>\nstd::vector<int> brute_row_optima(int\
    \ rows, int columns, Value value, Compare compare) {\n    std::vector<int> result(rows,\
    \ -1);\n    if (columns == 0) return result;\n    for (int row = 0; row < rows;\
    \ row++) {\n        result[row] = 0;\n        for (int column = 1; column < columns;\
    \ column++) {\n            if (compare(value(row, column), value(row, result[row])))\
    \ {\n                result[row] = column;\n            }\n        }\n    }\n\
    \    return result;\n}\n\nvoid test_smawk_monge() {\n    for (int rows = 0; rows\
    \ <= 40; rows++) {\n        for (int columns = 0; columns <= 40; columns++) {\n\
    \            auto value = [&](int row, int column) {\n                long long\
    \ difference = row * 3LL - column * 2LL;\n                return difference *\
    \ difference + row * 7LL + column * 5LL;\n            };\n            auto expected\
    \ = brute_row_optima(rows, columns, value, std::less<>());\n            assert(m1une::convex::smawk_row_argmin(rows,\
    \ columns, value) == expected);\n        }\n    }\n}\n\nvoid test_smawk_totally_monotone_and_ties()\
    \ {\n    for (int rows = 1; rows <= 50; rows++) {\n        for (int columns =\
    \ 1; columns <= 50; columns++) {\n            std::vector<int> threshold(rows);\n\
    \            for (int row = 0; row < rows; row++) {\n                threshold[row]\
    \ = std::min(columns - 1, (row * 7 + rows) / 5);\n            }\n            auto\
    \ value = [&](int row, int column) {\n                int difference = column\
    \ - threshold[row];\n                return difference * difference;\n       \
    \     };\n            auto result = m1une::convex::smawk_row_argmin(rows, columns,\
    \ value);\n            assert(result == threshold);\n        }\n    }\n\n    auto\
    \ constant = [](int, int) { return 0; };\n    auto result = m1une::convex::smawk_row_argmin(20,\
    \ 30, constant);\n    assert(result == std::vector<int>(20, 0));\n}\n\nvoid test_smawk_max()\
    \ {\n    auto value = [](int row, int column) {\n        long long difference\
    \ = row - column;\n        return -difference * difference;\n    };\n    auto\
    \ expected = brute_row_optima(30, 25, value, std::greater<>());\n    assert(m1une::convex::smawk_row_argmax(30,\
    \ 25, value) == expected);\n}\n\nvoid test_smawk_matrix_overload_and_evaluations()\
    \ {\n    std::vector<std::vector<long long>> matrix(17, std::vector<long long>(23));\n\
    \    for (int row = 0; row < 17; row++) {\n        for (int column = 0; column\
    \ < 23; column++) {\n            long long difference = row * 2LL - column;\n\
    \            matrix[row][column] = difference * difference;\n        }\n    }\n\
    \    auto expected = brute_row_optima(\n        17, 23, [&](int row, int column)\
    \ { return matrix[row][column]; }, std::less<>());\n    assert(m1une::convex::smawk_row_argmin(matrix)\
    \ == expected);\n\n    for (auto sizes : std::vector<std::pair<int, int>>{\n \
    \            std::pair<int, int>{10, 1000},\n             std::pair<int, int>{1000,\
    \ 10},\n             std::pair<int, int>{700, 900},\n         }) {\n        int\
    \ evaluations = 0;\n        auto value = [&](int row, int column) {\n        \
    \    evaluations++;\n            long long difference = row * 3LL - column * 2LL;\n\
    \            return difference * difference;\n        };\n        auto result\
    \ = m1une::convex::smawk_row_argmin(sizes.first, sizes.second, value);\n     \
    \   assert(int(result.size()) == sizes.first);\n        assert(evaluations <=\
    \ 20 * (sizes.first + sizes.second));\n    }\n}\n\nvoid test_monotone_minima()\
    \ {\n    for (int rows = 1; rows <= 40; rows++) {\n        for (int columns =\
    \ 1; columns <= 40; columns++) {\n            std::vector<int> optimum(rows);\n\
    \            for (int row = 0; row < rows; row++) {\n                optimum[row]\
    \ = std::min(columns - 1, row * columns / rows);\n            }\n            auto\
    \ value = [&](int row, int column) {\n                if (column == optimum[row])\
    \ return 0;\n                return 1000 + (row * 97 + column * 53) % 101;\n \
    \           };\n            auto result = m1une::convex::monotone_row_argmin(rows,\
    \ columns, value);\n            assert(result == optimum);\n        }\n    }\n\
    \n    auto empty = m1une::convex::monotone_row_argmin(5, 0, [](int, int) { return\
    \ 0; });\n    assert(empty == std::vector<int>(5, -1));\n\n    std::vector<std::vector<int>>\
    \ matrix;\n    matrix.emplace_back(std::vector<int>{0, 5, 7});\n    matrix.emplace_back(std::vector<int>{4,\
    \ 0, 8});\n    matrix.emplace_back(std::vector<int>{9, 3, 0});\n    assert(m1une::convex::monotone_row_argmin(matrix)\
    \ == std::vector<int>({0, 1, 2}));\n}\n\nvoid test_monge_checks() {\n    std::vector<std::vector<long\
    \ long>> matrix(8, std::vector<long long>(11));\n    for (int row = 0; row < 8;\
    \ row++) {\n        for (int column = 0; column < 11; column++) {\n          \
    \  long long difference = row - column;\n            matrix[row][column] = difference\
    \ * difference;\n        }\n    }\n    assert(m1une::convex::is_monge(matrix));\n\
    \    assert(!m1une::convex::is_anti_monge(matrix));\n\n    for (auto& row : matrix)\
    \ {\n        for (auto& value : row) value = -value;\n    }\n    assert(!m1une::convex::is_monge(matrix));\n\
    \    assert(m1une::convex::is_anti_monge(matrix));\n\n    std::vector<std::vector<int>>\
    \ empty;\n    assert(m1une::convex::is_monge(empty));\n    assert(m1une::convex::is_anti_monge(empty));\n\
    }\n\ntemplate <class T, class Compare>\nstd::vector<T> brute_convolution(const\
    \ std::vector<T>& first, const std::vector<T>& second,\n                     \
    \            Compare compare) {\n    if (first.empty() || second.empty()) return\
    \ {};\n    std::vector<T> result(first.size() + second.size() - 1);\n    for (int\
    \ index = 0; index < int(result.size()); index++) {\n        int left = std::max(0,\
    \ index - int(second.size()) + 1);\n        int right = std::min(int(first.size()),\
    \ index + 1);\n        result[index] = first[left] + second[index - left];\n \
    \       for (int i = left + 1; i < right; i++) {\n            T value = first[i]\
    \ + second[index - i];\n            if (compare(value, result[index])) result[index]\
    \ = value;\n        }\n    }\n    return result;\n}\n\ntemplate <class T, class\
    \ Compare>\nstd::vector<T> brute_convolution_with_infinity(const std::vector<T>&\
    \ first,\n                                               const std::vector<T>&\
    \ second,\n                                               Compare compare,\n \
    \                                              const T& infinity) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    std::vector<T> result(first.size() + second.size()\
    \ - 1, infinity);\n    for (int i = 0; i < int(first.size()); i++) {\n       \
    \ for (int j = 0; j < int(second.size()); j++) {\n            if (first[i] ==\
    \ infinity || second[j] == infinity) continue;\n            T value = first[i]\
    \ + second[j];\n            if (result[i + j] == infinity || compare(value, result[i\
    \ + j])) {\n                result[i + j] = value;\n            }\n        }\n\
    \    }\n    return result;\n}\n\nvoid test_structured_convolutions() {\n    const\
    \ long long infinity = 2'000'000'000'000'000'000LL;\n    const long long negative_infinity\
    \ = -infinity;\n    for (int first_size = 0; first_size <= 35; first_size++) {\n\
    \        for (int second_size = 0; second_size <= 35; second_size++) {\n     \
    \       for (int test = 0; test < 8; test++) {\n                std::vector<long\
    \ long> arbitrary(first_size);\n                for (int i = 0; i < first_size;\
    \ i++) {\n                    arbitrary[i] = (test * 17 + i * 31 + first_size\
    \ * 7) % 61 - 30;\n                }\n\n                std::vector<long long>\
    \ convex(second_size);\n                long long difference = -10 + test;\n \
    \               for (int i = 1; i < second_size; i++) {\n                    difference\
    \ += (test * 3 + i * 5) % 4;\n                    convex[i] = convex[i - 1] +\
    \ difference;\n                }\n                assert(m1une::convex::is_convex_sequence(convex));\n\
    \                auto expected_min = brute_convolution(arbitrary, convex, std::less<>());\n\
    \                assert(m1une::convex::min_plus_convolution_convex(arbitrary,\
    \ convex) ==\n                       expected_min);\n\n                std::vector<long\
    \ long> arbitrary_extended = arbitrary;\n                for (int i = 0; i < first_size;\
    \ i++) {\n                    if ((i + test) % 7 == 0) arbitrary_extended[i] =\
    \ infinity;\n                }\n                std::vector<long long> convex_extended(second_size\
    \ + 2, infinity);\n                std::copy(convex.begin(), convex.end(), convex_extended.begin()\
    \ + 1);\n                assert(m1une::convex::is_convex_sequence(convex_extended,\
    \ infinity));\n                auto expected_extended_min = brute_convolution_with_infinity(\n\
    \                    arbitrary_extended, convex_extended, std::less<>(), infinity);\n\
    \                assert(m1une::convex::min_plus_convolution_convex(\n        \
    \                   arbitrary_extended, convex_extended, infinity) ==\n      \
    \                 expected_extended_min);\n\n                std::vector<long\
    \ long> first_convex(first_size);\n                difference = -12 - test;\n\
    \                for (int i = 1; i < first_size; i++) {\n                    difference\
    \ += (test * 5 + i * 7) % 5;\n                    first_convex[i] = first_convex[i\
    \ - 1] + difference;\n                }\n                assert(m1une::convex::is_convex_sequence(first_convex));\n\
    \                auto expected_convex =\n                    brute_convolution(first_convex,\
    \ convex, std::less<>());\n                assert(m1une::convex::min_plus_convolution_convex(first_convex,\
    \ convex) ==\n                       expected_convex);\n                assert(m1une::convex::min_plus_convolution_convex(convex,\
    \ first_convex) ==\n                       expected_convex);\n               \
    \ assert(m1une::convex::min_plus_convolution_convex_convex(first_convex,\n   \
    \                                                                     convex)\
    \ ==\n                       expected_convex);\n                assert(m1une::convex::min_plus_convolution_convex_convex(convex,\n\
    \                                                                        first_convex)\
    \ ==\n                       expected_convex);\n\n                std::vector<long\
    \ long> first_convex_extended(first_size + 2,\n                              \
    \                                infinity);\n                std::copy(first_convex.begin(),\
    \ first_convex.end(),\n                          first_convex_extended.begin()\
    \ + 1);\n                auto expected_extended_convex = brute_convolution_with_infinity(\n\
    \                    first_convex_extended, convex_extended, std::less<>(), infinity);\n\
    \                assert(m1une::convex::min_plus_convolution_convex_convex(\n \
    \                          first_convex_extended, convex_extended, infinity) ==\n\
    \                       expected_extended_convex);\n\n                std::vector<long\
    \ long> concave = convex;\n                for (auto& value : concave) value =\
    \ -value;\n                assert(m1une::convex::is_concave_sequence(concave));\n\
    \                auto expected_max = brute_convolution(arbitrary, concave, std::greater<>());\n\
    \                assert(m1une::convex::max_plus_convolution_concave(arbitrary,\
    \ concave) ==\n                       expected_max);\n\n                std::vector<long\
    \ long> first_concave = first_convex;\n                for (auto& value : first_concave)\
    \ value = -value;\n                assert(m1une::convex::is_concave_sequence(first_concave));\n\
    \                auto expected_concave =\n                    brute_convolution(first_concave,\
    \ concave, std::greater<>());\n                assert(m1une::convex::max_plus_convolution_concave(first_concave,\
    \ concave) ==\n                       expected_concave);\n                assert(m1une::convex::max_plus_convolution_concave(concave,\
    \ first_concave) ==\n                       expected_concave);\n             \
    \   assert(m1une::convex::max_plus_convolution_concave_concave(first_concave,\n\
    \                                                                          concave)\
    \ ==\n                       expected_concave);\n                assert(m1une::convex::max_plus_convolution_concave_concave(concave,\n\
    \                                                                          first_concave)\
    \ ==\n                       expected_concave);\n\n                std::vector<long\
    \ long> arbitrary_max_extended = arbitrary_extended;\n                for (long\
    \ long& value : arbitrary_max_extended) {\n                    value = value ==\
    \ infinity ? negative_infinity : -value;\n                }\n                std::vector<long\
    \ long> concave_extended = convex_extended;\n                for (long long& value\
    \ : concave_extended) {\n                    value = value == infinity ? negative_infinity\
    \ : -value;\n                }\n                auto expected_extended_max = brute_convolution_with_infinity(\n\
    \                    arbitrary_max_extended, concave_extended, std::greater<>(),\n\
    \                    negative_infinity);\n                assert(m1une::convex::max_plus_convolution_concave(\n\
    \                           arbitrary_max_extended, concave_extended,\n      \
    \                     negative_infinity) == expected_extended_max);\n\n      \
    \          std::vector<long long> first_concave_extended =\n                 \
    \   first_convex_extended;\n                for (long long& value : first_concave_extended)\
    \ {\n                    value = value == infinity ? negative_infinity : -value;\n\
    \                }\n                auto expected_extended_concave = brute_convolution_with_infinity(\n\
    \                    first_concave_extended, concave_extended, std::greater<>(),\n\
    \                    negative_infinity);\n                assert(m1une::convex::max_plus_convolution_concave_concave(\n\
    \                           first_concave_extended, concave_extended,\n      \
    \                     negative_infinity) == expected_extended_concave);\n    \
    \        }\n        }\n    }\n\n    assert(!m1une::convex::is_convex_sequence(std::vector<int>{0,\
    \ 2, 1}));\n    assert(!m1une::convex::is_concave_sequence(std::vector<int>{0,\
    \ -2, -1}));\n    assert(!m1une::convex::is_convex_sequence(\n        std::vector<long\
    \ long>{1, infinity, infinity}));\n    assert(m1une::convex::is_convex_sequence(\n\
    \        std::vector<long long>{1, infinity, infinity}, infinity));\n    assert(m1une::convex::is_convex_sequence(\n\
    \        std::vector<long long>{infinity, 0, 1, 4, infinity}, infinity));\n  \
    \  assert(!m1une::convex::is_convex_sequence(\n        std::vector<long long>{0,\
    \ infinity, 1}, infinity));\n\n    std::vector<long long> arbitrary = {infinity,\
    \ 3, infinity, -2};\n    std::vector<long long> convex = {infinity, 0, 1, 4, infinity,\
    \ infinity};\n    auto expected_min =\n        brute_convolution_with_infinity(arbitrary,\
    \ convex, std::less<>(), infinity);\n    assert(m1une::convex::min_plus_convolution_convex(arbitrary,\
    \ convex, infinity) ==\n           expected_min);\n\n    std::vector<long long>\
    \ first_convex = {infinity, 2, 2, 3, infinity};\n    expected_min = brute_convolution_with_infinity(first_convex,\
    \ convex,\n                                                   std::less<>(), infinity);\n\
    \    assert(m1une::convex::min_plus_convolution_convex_convex(\n             \
    \  first_convex, convex, infinity) == expected_min);\n\n    long long unordered_infinity\
    \ = 7;\n    std::vector<long long> large_arbitrary = {10, 20};\n    std::vector<long\
    \ long> small_convex = {0, 1};\n    assert(m1une::convex::min_plus_convolution_convex(\n\
    \               large_arbitrary, small_convex, unordered_infinity) ==\n      \
    \     std::vector<long long>({10, 11, 21}));\n\n    std::vector<long long> arbitrary_max\
    \ = {negative_infinity, 3,\n                                             negative_infinity,\
    \ -2};\n    std::vector<long long> concave = {negative_infinity, 0, -1, -4,\n\
    \                                      negative_infinity};\n    assert(m1une::convex::is_concave_sequence(concave,\
    \ negative_infinity));\n    auto expected_max = brute_convolution_with_infinity(\n\
    \        arbitrary_max, concave, std::greater<>(), negative_infinity);\n    assert(m1une::convex::max_plus_convolution_concave(\n\
    \               arbitrary_max, concave, negative_infinity) == expected_max);\n\
    \n    std::vector<long long> first_concave = {negative_infinity, 2, 2, 1,\n  \
    \                                          negative_infinity};\n    expected_max\
    \ = brute_convolution_with_infinity(\n        first_concave, concave, std::greater<>(),\
    \ negative_infinity);\n    assert(m1une::convex::max_plus_convolution_concave_concave(\n\
    \               first_concave, concave, negative_infinity) == expected_max);\n\
    \n    std::vector<long long> all_infinity(3, infinity);\n    assert(m1une::convex::is_convex_sequence(all_infinity,\
    \ infinity));\n    assert(m1une::convex::min_plus_convolution_convex_convex(\n\
    \               all_infinity, convex, infinity) ==\n           std::vector<long\
    \ long>(all_infinity.size() + convex.size() - 1,\n                           \
    \       infinity));\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_smawk_monge();\n  \
    \  test_smawk_totally_monotone_and_ties();\n    test_smawk_max();\n    test_smawk_matrix_overload_and_evaluations();\n\
    \    test_monotone_minima();\n    test_monge_checks();\n    test_structured_convolutions();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - convex/monge/all.hpp
  - convex/monge/check.hpp
  - convex/monge/divide_and_conquer_optimization.hpp
  - convex/monge/monotone_minima.hpp
  - convex/monge/knuth_optimization.hpp
  - convex/monge/larsch.hpp
  - convex/monge/min_plus_convolution.hpp
  - convex/monge/smawk.hpp
  isVerificationFile: true
  path: verify/convex/monge/monge_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/convex/monge/monge_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/convex/monge/monge_algorithms.test.cpp
- /verify/verify/convex/monge/monge_algorithms.test.cpp.html
title: verify/convex/monge/monge_algorithms.test.cpp
---
