---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convex/slope_trick.hpp
    title: Slope Trick
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
  bundledCode: "#line 1 \"verify/convex/slope_trick.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include <cassert>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/convex/slope_trick.test.cpp\"\
    \n#include <limits>\n#include <vector>\n\n#line 1 \"convex/slope_trick.hpp\"\n\
    \n\n\n#line 5 \"convex/slope_trick.hpp\"\n#include <functional>\n#include <optional>\n\
    #include <queue>\n#line 11 \"convex/slope_trick.hpp\"\n\nnamespace m1une {\nnamespace\
    \ convex {\n\ntemplate <class T>\nstruct SlopeTrickArgmin {\n    std::optional<T>\
    \ left;\n    std::optional<T> right;\n};\n\ntemplate <class T>\nclass SlopeTrick\
    \ {\n    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);\n\n  \
    \  T _minimum = T();\n    T _left_offset = T();\n    T _right_offset = T();\n\
    \    std::priority_queue<T> _left;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> _right;\n\n    T left_top() const {\n        return _left.top()\
    \ + _left_offset;\n    }\n\n    T right_top() const {\n        return _right.top()\
    \ + _right_offset;\n    }\n\n    void push_left(T value) {\n        _left.push(value\
    \ - _left_offset);\n    }\n\n    void push_right(T value) {\n        _right.push(value\
    \ - _right_offset);\n    }\n\n   public:\n    SlopeTrick() = default;\n\n    T\
    \ minimum() const {\n        return _minimum;\n    }\n\n    int breakpoint_count()\
    \ const {\n        return int(_left.size() + _right.size());\n    }\n\n    SlopeTrickArgmin<T>\
    \ argmin() const {\n        SlopeTrickArgmin<T> result;\n        if (!_left.empty())\
    \ result.left = left_top();\n        if (!_right.empty()) result.right = right_top();\n\
    \        return result;\n    }\n\n    void add_constant(T value) {\n        _minimum\
    \ += value;\n    }\n\n    void add_x_minus_a(T a) {\n        if (!_left.empty()\
    \ && left_top() > a) {\n            T old = left_top();\n            _minimum\
    \ += old - a;\n            _left.pop();\n            push_left(a);\n         \
    \   push_right(old);\n        } else {\n            push_right(a);\n        }\n\
    \    }\n\n    void add_a_minus_x(T a) {\n        if (!_right.empty() && right_top()\
    \ < a) {\n            T old = right_top();\n            _minimum += a - old;\n\
    \            _right.pop();\n            push_right(a);\n            push_left(old);\n\
    \        } else {\n            push_left(a);\n        }\n    }\n\n    void add_abs(T\
    \ a) {\n        add_a_minus_x(a);\n        add_x_minus_a(a);\n    }\n\n    void\
    \ clear_left() {\n        _left = std::priority_queue<T>();\n    }\n\n    void\
    \ clear_right() {\n        _right = std::priority_queue<T, std::vector<T>, std::greater<T>>();\n\
    \    }\n\n    void prefix_minimum() {\n        clear_right();\n    }\n\n    void\
    \ suffix_minimum() {\n        clear_left();\n    }\n\n    void shift(T delta)\
    \ {\n        _left_offset += delta;\n        _right_offset += delta;\n    }\n\n\
    \    void shift(T left_delta, T right_delta) {\n        assert(left_delta <= right_delta);\n\
    \        _left_offset += left_delta;\n        _right_offset += right_delta;\n\
    \    }\n\n    T evaluate(T x) const {\n        T result = _minimum;\n        auto\
    \ left = _left;\n        while (!left.empty()) {\n            T breakpoint = left.top()\
    \ + _left_offset;\n            if (breakpoint > x) result += breakpoint - x;\n\
    \            left.pop();\n        }\n\n        auto right = _right;\n        while\
    \ (!right.empty()) {\n            T breakpoint = right.top() + _right_offset;\n\
    \            if (x > breakpoint) result += x - breakpoint;\n            right.pop();\n\
    \        }\n        return result;\n    }\n\n    void merge(SlopeTrick other)\
    \ {\n        add_constant(other._minimum);\n        while (!other._left.empty())\
    \ {\n            add_a_minus_x(other.left_top());\n            other._left.pop();\n\
    \        }\n        while (!other._right.empty()) {\n            add_x_minus_a(other.right_top());\n\
    \            other._right.pop();\n        }\n    }\n\n    void min_plus_convolve(SlopeTrick\
    \ other) {\n        SlopeTrick result;\n        result._minimum = _minimum + other._minimum;\n\
    \n        while (!_left.empty() && !other._left.empty()) {\n            result.push_left(left_top()\
    \ + other.left_top());\n            _left.pop();\n            other._left.pop();\n\
    \        }\n        while (!_right.empty() && !other._right.empty()) {\n     \
    \       result.push_right(right_top() + other.right_top());\n            _right.pop();\n\
    \            other._right.pop();\n        }\n        *this = std::move(result);\n\
    \    }\n};\n\ntemplate <class T>\nSlopeTrick<T> min_plus_convolution(SlopeTrick<T>\
    \ first,\n                                   SlopeTrick<T> second) {\n    first.min_plus_convolve(std::move(second));\n\
    \    return first;\n}\n\n}  // namespace convex\n}  // namespace m1une\n\n\n#line\
    \ 10 \"verify/convex/slope_trick.test.cpp\"\n\nusing SlopeTrick = m1une::convex::SlopeTrick<long\
    \ long>;\n\nconstexpr int coordinate_limit = 300;\nconstexpr long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n\nint index_of(int x) {\n    return x + coordinate_limit;\n\
    }\n\nvoid check_values(const SlopeTrick& slope, const std::vector<long long>&\
    \ value) {\n    long long expected_minimum = *std::min_element(value.begin(),\
    \ value.end());\n    assert(slope.minimum() == expected_minimum);\n    for (int\
    \ x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x) == value[index_of(x)]);\n\
    \    }\n\n    auto range = slope.argmin();\n    int first = -coordinate_limit;\n\
    \    while (first <= coordinate_limit && value[index_of(first)] != expected_minimum)\
    \ first++;\n    int last = coordinate_limit;\n    while (last >= -coordinate_limit\
    \ && value[index_of(last)] != expected_minimum) last--;\n    if (range.left.has_value())\
    \ assert(*range.left == first);\n    if (range.right.has_value()) assert(*range.right\
    \ == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n    assert(slope.minimum()\
    \ == 0);\n    assert(!slope.argmin().left.has_value());\n    assert(!slope.argmin().right.has_value());\n\
    \n    slope.add_abs(3);\n    slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n\
    \    slope.add_constant(5);\n    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3)\
    \ == 14);\n    auto range = slope.argmin();\n    assert(range.left == std::optional<long\
    \ long>(3));\n    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nvoid test_min_plus_convolution()\
    \ {\n    constexpr int brute_limit = 500;\n\n    for (int test = 0; test < 120;\
    \ test++) {\n        SlopeTrick first;\n        SlopeTrick second;\n\n       \
    \ for (int i = 0; i < 18; i++) {\n            int a = (test * 17 + i * 11) % 51\
    \ - 25;\n            int b = (test * 23 + i * 7) % 51 - 25;\n\n            if\
    \ (i % 4 == 0) {\n                first.add_abs(a);\n                second.add_abs(b);\n\
    \            } else if (i % 4 == 1) {\n                first.add_x_minus_a(a);\n\
    \                second.add_a_minus_x(b);\n            } else if (i % 4 == 2)\
    \ {\n                first.add_a_minus_x(a);\n                second.add_x_minus_a(b);\n\
    \            } else {\n                first.add_constant(a - b);\n          \
    \      second.add_constant(b - a / 2);\n            }\n\n            if (i % 7\
    \ == 3) first.shift(-2, 3);\n            if (i % 7 == 5) second.shift(1);\n  \
    \      }\n\n        if (test % 4 == 0) first.prefix_minimum();\n        if (test\
    \ % 5 == 0) first.suffix_minimum();\n        if (test % 6 == 0) second.prefix_minimum();\n\
    \        if (test % 7 == 0) second.suffix_minimum();\n\n        SlopeTrick assigned\
    \ = first;\n        assigned.min_plus_convolve(second);\n        SlopeTrick returned\
    \ = m1une::convex::min_plus_convolution(first, second);\n\n        assert(assigned.minimum()\
    \ == first.minimum() + second.minimum());\n        auto first_range = first.argmin();\n\
    \        auto second_range = second.argmin();\n        auto result_range = assigned.argmin();\n\
    \        if (first_range.left && second_range.left) {\n            assert(result_range.left);\n\
    \            assert(*result_range.left == *first_range.left + *second_range.left);\n\
    \        } else {\n            assert(!result_range.left);\n        }\n      \
    \  if (first_range.right && second_range.right) {\n            assert(result_range.right);\n\
    \            assert(*result_range.right == *first_range.right + *second_range.right);\n\
    \        } else {\n            assert(!result_range.right);\n        }\n\n   \
    \     for (int x = -100; x <= 100; x++) {\n            long long expected = inf;\n\
    \            for (int y = -brute_limit; y <= brute_limit; y++) {\n           \
    \     expected =\n                    std::min(expected, first.evaluate(y) + second.evaluate(x\
    \ - y));\n            }\n            assert(assigned.evaluate(x) == expected);\n\
    \            assert(returned.evaluate(x) == expected);\n        }\n    }\n}\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_operations_against_explicit_function();\n\
    \    test_merge();\n    test_min_plus_convolution();\n\n    long long a, b;\n\
    \    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../utilities/fast_io.hpp\"\n#include <limits>\n\
    #include <vector>\n\n#include \"../../convex/slope_trick.hpp\"\n\nusing SlopeTrick\
    \ = m1une::convex::SlopeTrick<long long>;\n\nconstexpr int coordinate_limit =\
    \ 300;\nconstexpr long long inf = std::numeric_limits<long long>::max() / 4;\n\
    \nint index_of(int x) {\n    return x + coordinate_limit;\n}\n\nvoid check_values(const\
    \ SlopeTrick& slope, const std::vector<long long>& value) {\n    long long expected_minimum\
    \ = *std::min_element(value.begin(), value.end());\n    assert(slope.minimum()\
    \ == expected_minimum);\n    for (int x = -100; x <= 100; x++) {\n        assert(slope.evaluate(x)\
    \ == value[index_of(x)]);\n    }\n\n    auto range = slope.argmin();\n    int\
    \ first = -coordinate_limit;\n    while (first <= coordinate_limit && value[index_of(first)]\
    \ != expected_minimum) first++;\n    int last = coordinate_limit;\n    while (last\
    \ >= -coordinate_limit && value[index_of(last)] != expected_minimum) last--;\n\
    \    if (range.left.has_value()) assert(*range.left == first);\n    if (range.right.has_value())\
    \ assert(*range.right == last);\n}\n\nvoid test_basic() {\n    SlopeTrick slope;\n\
    \    assert(slope.minimum() == 0);\n    assert(!slope.argmin().left.has_value());\n\
    \    assert(!slope.argmin().right.has_value());\n\n    slope.add_abs(3);\n   \
    \ slope.add_x_minus_a(-2);\n    slope.add_a_minus_x(7);\n    slope.add_constant(5);\n\
    \    assert(slope.minimum() == 14);\n    assert(slope.evaluate(3) == 14);\n  \
    \  auto range = slope.argmin();\n    assert(range.left == std::optional<long long>(3));\n\
    \    assert(range.right == std::optional<long long>(3));\n    assert(slope.breakpoint_count()\
    \ == 4);\n\n    SlopeTrick right_hinge;\n    right_hinge.add_x_minus_a(5);\n \
    \   assert(!right_hinge.argmin().left.has_value());\n    assert(right_hinge.argmin().right\
    \ == std::optional<long long>(5));\n\n    SlopeTrick left_hinge;\n    left_hinge.add_a_minus_x(-4);\n\
    \    assert(left_hinge.argmin().left == std::optional<long long>(-4));\n    assert(!left_hinge.argmin().right.has_value());\n\
    }\n\nvoid test_operations_against_explicit_function() {\n    for (int test = 0;\
    \ test < 80; test++) {\n        SlopeTrick slope;\n        std::vector<long long>\
    \ value(coordinate_limit * 2 + 1, 0);\n\n        for (int operation = 0; operation\
    \ < 80; operation++) {\n            int type = (test * 11 + operation * 7) % 8;\n\
    \            int a = (test * 17 + operation * 13) % 61 - 30;\n\n            if\
    \ (type == 0) {\n                long long constant = (test + operation * 3) %\
    \ 17 - 8;\n                slope.add_constant(constant);\n                for\
    \ (auto& current : value) current += constant;\n            } else if (type ==\
    \ 1) {\n                slope.add_x_minus_a(a);\n                for (int x =\
    \ -coordinate_limit; x <= coordinate_limit; x++) {\n                    value[index_of(x)]\
    \ += std::max(0, x - a);\n                }\n            } else if (type == 2)\
    \ {\n                slope.add_a_minus_x(a);\n                for (int x = -coordinate_limit;\
    \ x <= coordinate_limit; x++) {\n                    value[index_of(x)] += std::max(0,\
    \ a - x);\n                }\n            } else if (type == 3) {\n          \
    \      slope.add_abs(a);\n                for (int x = -coordinate_limit; x <=\
    \ coordinate_limit; x++) {\n                    value[index_of(x)] += std::abs(x\
    \ - a);\n                }\n            } else if (type == 4) {\n            \
    \    int delta = (test + operation) % 7 - 3;\n                slope.shift(delta);\n\
    \                std::vector<long long> next(value.size(), inf);\n           \
    \     for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n        \
    \            int source = x - delta;\n                    if (-coordinate_limit\
    \ <= source && source <= coordinate_limit) {\n                        next[index_of(x)]\
    \ = value[index_of(source)];\n                    }\n                }\n     \
    \           value.swap(next);\n            } else if (type == 5) {\n         \
    \       int left = (test + operation * 2) % 4 - 3;\n                int right\
    \ = left + 1 + (test * 3 + operation) % 4;\n                slope.shift(left,\
    \ right);\n                std::vector<long long> next(value.size(), inf);\n \
    \               for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n\
    \                    for (int y = x - right; y <= x - left; y++) {\n         \
    \               if (-coordinate_limit <= y && y <= coordinate_limit) {\n     \
    \                       next[index_of(x)] = std::min(next[index_of(x)], value[index_of(y)]);\n\
    \                        }\n                    }\n                }\n       \
    \         value.swap(next);\n            } else if (type == 6) {\n           \
    \     slope.prefix_minimum();\n                long long best = inf;\n       \
    \         for (int x = -coordinate_limit; x <= coordinate_limit; x++) {\n    \
    \                best = std::min(best, value[index_of(x)]);\n                \
    \    value[index_of(x)] = best;\n                }\n            } else {\n   \
    \             slope.suffix_minimum();\n                long long best = inf;\n\
    \                for (int x = coordinate_limit; x >= -coordinate_limit; x--) {\n\
    \                    best = std::min(best, value[index_of(x)]);\n            \
    \        value[index_of(x)] = best;\n                }\n            }\n      \
    \      check_values(slope, value);\n        }\n    }\n}\n\nvoid test_merge() {\n\
    \    for (int test = 0; test < 100; test++) {\n        SlopeTrick first;\n   \
    \     SlopeTrick second;\n        for (int i = 0; i < 20; i++) {\n           \
    \ int a = (test * 7 + i * 11) % 41 - 20;\n            int b = (test * 13 + i *\
    \ 5) % 41 - 20;\n            if (i % 3 == 0) {\n                first.add_abs(a);\n\
    \                second.add_abs(b);\n            } else if (i % 3 == 1) {\n  \
    \              first.add_x_minus_a(a);\n                second.add_a_minus_x(b);\n\
    \            } else {\n                first.add_a_minus_x(a);\n             \
    \   second.add_x_minus_a(b);\n            }\n        }\n        first.add_constant(test\
    \ - 50);\n        second.add_constant(30 - test);\n        first.shift(-2, 1);\n\
    \        second.shift(3);\n        if (test % 2 == 0) first.clear_right();\n \
    \       if (test % 3 == 0) second.clear_left();\n\n        std::vector<long long>\
    \ expected(201);\n        for (int x = -100; x <= 100; x++) {\n            expected[x\
    \ + 100] = first.evaluate(x) + second.evaluate(x);\n        }\n        first.merge(second);\n\
    \        for (int x = -100; x <= 100; x++) {\n            assert(first.evaluate(x)\
    \ == expected[x + 100]);\n        }\n    }\n}\n\nvoid test_min_plus_convolution()\
    \ {\n    constexpr int brute_limit = 500;\n\n    for (int test = 0; test < 120;\
    \ test++) {\n        SlopeTrick first;\n        SlopeTrick second;\n\n       \
    \ for (int i = 0; i < 18; i++) {\n            int a = (test * 17 + i * 11) % 51\
    \ - 25;\n            int b = (test * 23 + i * 7) % 51 - 25;\n\n            if\
    \ (i % 4 == 0) {\n                first.add_abs(a);\n                second.add_abs(b);\n\
    \            } else if (i % 4 == 1) {\n                first.add_x_minus_a(a);\n\
    \                second.add_a_minus_x(b);\n            } else if (i % 4 == 2)\
    \ {\n                first.add_a_minus_x(a);\n                second.add_x_minus_a(b);\n\
    \            } else {\n                first.add_constant(a - b);\n          \
    \      second.add_constant(b - a / 2);\n            }\n\n            if (i % 7\
    \ == 3) first.shift(-2, 3);\n            if (i % 7 == 5) second.shift(1);\n  \
    \      }\n\n        if (test % 4 == 0) first.prefix_minimum();\n        if (test\
    \ % 5 == 0) first.suffix_minimum();\n        if (test % 6 == 0) second.prefix_minimum();\n\
    \        if (test % 7 == 0) second.suffix_minimum();\n\n        SlopeTrick assigned\
    \ = first;\n        assigned.min_plus_convolve(second);\n        SlopeTrick returned\
    \ = m1une::convex::min_plus_convolution(first, second);\n\n        assert(assigned.minimum()\
    \ == first.minimum() + second.minimum());\n        auto first_range = first.argmin();\n\
    \        auto second_range = second.argmin();\n        auto result_range = assigned.argmin();\n\
    \        if (first_range.left && second_range.left) {\n            assert(result_range.left);\n\
    \            assert(*result_range.left == *first_range.left + *second_range.left);\n\
    \        } else {\n            assert(!result_range.left);\n        }\n      \
    \  if (first_range.right && second_range.right) {\n            assert(result_range.right);\n\
    \            assert(*result_range.right == *first_range.right + *second_range.right);\n\
    \        } else {\n            assert(!result_range.right);\n        }\n\n   \
    \     for (int x = -100; x <= 100; x++) {\n            long long expected = inf;\n\
    \            for (int y = -brute_limit; y <= brute_limit; y++) {\n           \
    \     expected =\n                    std::min(expected, first.evaluate(y) + second.evaluate(x\
    \ - y));\n            }\n            assert(assigned.evaluate(x) == expected);\n\
    \            assert(returned.evaluate(x) == expected);\n        }\n    }\n}\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_operations_against_explicit_function();\n\
    \    test_merge();\n    test_min_plus_convolution();\n\n    long long a, b;\n\
    \    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - convex/slope_trick.hpp
  isVerificationFile: true
  path: verify/convex/slope_trick.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/convex/slope_trick.test.cpp
layout: document
redirect_from:
- /verify/verify/convex/slope_trick.test.cpp
- /verify/verify/convex/slope_trick.test.cpp.html
title: verify/convex/slope_trick.test.cpp
---
