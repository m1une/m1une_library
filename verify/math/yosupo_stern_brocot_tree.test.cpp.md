---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/rational.hpp
    title: Rational Number
  - icon: ':heavy_check_mark:'
    path: math/stern_brocot_tree.hpp
    title: Stern-Brocot Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/stern_brocot_tree
    links:
    - https://judge.yosupo.jp/problem/stern_brocot_tree
  bundledCode: "#line 1 \"verify/math/yosupo_stern_brocot_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n#include\
    \ <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include\
    \ <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <sys/stat.h>\n#include <type_traits>\n#include <utility>\n\
    #include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
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
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 4 \"verify/math/yosupo_stern_brocot_tree.test.cpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"math/stern_brocot_tree.hpp\"\
    \n\n\n\n#line 5 \"math/stern_brocot_tree.hpp\"\n#include <concepts>\n#line 10\
    \ \"math/stern_brocot_tree.hpp\"\n\n#line 1 \"math/rational.hpp\"\n\n\n\n#line\
    \ 5 \"math/rational.hpp\"\n#include <compare>\n#line 10 \"math/rational.hpp\"\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <std::signed_integral T = long\
    \ long>\nstruct Rational {\n    static_assert(sizeof(T) <= sizeof(long long));\n\
    \n   private:\n    using Wide = __int128_t;\n    using UnsignedWide = __uint128_t;\n\
    \n    T _numerator;\n    T _denominator;\n\n    static constexpr UnsignedWide\
    \ magnitude(Wide value) {\n        if (value < 0) {\n            return static_cast<UnsignedWide>(-(value\
    \ + 1)) + 1;\n        }\n        return static_cast<UnsignedWide>(value);\n  \
    \  }\n\n    static constexpr UnsignedWide gcd(UnsignedWide first, UnsignedWide\
    \ second) {\n        while (second != 0) {\n            UnsignedWide remainder\
    \ = first % second;\n            first = second;\n            second = remainder;\n\
    \        }\n        return first;\n    }\n\n    static constexpr T narrow(Wide\
    \ value) {\n        assert(Wide(std::numeric_limits<T>::min()) <= value);\n  \
    \      assert(value <= Wide(std::numeric_limits<T>::max()));\n        return static_cast<T>(value);\n\
    \    }\n\n    constexpr void assign_normalized(Wide numerator, Wide denominator)\
    \ {\n        assert(denominator != 0);\n        if (numerator == 0) {\n      \
    \      _numerator = 0;\n            _denominator = 1;\n            return;\n \
    \       }\n\n        UnsignedWide divisor = gcd(magnitude(numerator), magnitude(denominator));\n\
    \        numerator /= static_cast<Wide>(divisor);\n        denominator /= static_cast<Wide>(divisor);\n\
    \        if (denominator < 0) {\n            numerator = -numerator;\n       \
    \     denominator = -denominator;\n        }\n        _numerator = narrow(numerator);\n\
    \        _denominator = narrow(denominator);\n    }\n\n    static constexpr Rational\
    \ from_wide(Wide numerator, Wide denominator) {\n        Rational result;\n  \
    \      result.assign_normalized(numerator, denominator);\n        return result;\n\
    \    }\n\n   public:\n    constexpr Rational() : _numerator(0), _denominator(1)\
    \ {}\n\n    constexpr Rational(T integer) : _numerator(integer), _denominator(1)\
    \ {}\n\n    constexpr Rational(T numerator, T denominator) {\n        assign_normalized(Wide(numerator),\
    \ Wide(denominator));\n    }\n\n    constexpr T numerator() const {\n        return\
    \ _numerator;\n    }\n\n    constexpr T denominator() const {\n        return\
    \ _denominator;\n    }\n\n    constexpr bool is_integer() const {\n        return\
    \ _denominator == 1;\n    }\n\n    constexpr int sign() const {\n        return\
    \ (_numerator > 0) - (_numerator < 0);\n    }\n\n    constexpr Rational reciprocal()\
    \ const {\n        assert(_numerator != 0);\n        return from_wide(Wide(_denominator),\
    \ Wide(_numerator));\n    }\n\n    constexpr Rational abs() const {\n        return\
    \ _numerator < 0 ? -*this : *this;\n    }\n\n    constexpr long double to_long_double()\
    \ const {\n        return static_cast<long double>(_numerator) / static_cast<long\
    \ double>(_denominator);\n    }\n\n    explicit constexpr operator long double()\
    \ const {\n        return to_long_double();\n    }\n\n    constexpr T trunc()\
    \ const {\n        return _numerator / _denominator;\n    }\n\n    constexpr T\
    \ floor() const {\n        T quotient = _numerator / _denominator;\n        if\
    \ (_numerator < 0 && _numerator % _denominator != 0) --quotient;\n        return\
    \ quotient;\n    }\n\n    constexpr T ceil() const {\n        T quotient = _numerator\
    \ / _denominator;\n        if (0 < _numerator && _numerator % _denominator !=\
    \ 0) ++quotient;\n        return quotient;\n    }\n\n    constexpr Rational operator+()\
    \ const {\n        return *this;\n    }\n\n    constexpr Rational operator-()\
    \ const {\n        return from_wide(-Wide(_numerator), Wide(_denominator));\n\
    \    }\n\n    constexpr Rational& operator+=(const Rational& other) {\n      \
    \  UnsignedWide common =\n            gcd(static_cast<UnsignedWide>(_denominator),\
    \ static_cast<UnsignedWide>(other._denominator));\n        Wide left_scale = Wide(other._denominator)\
    \ / static_cast<Wide>(common);\n        Wide right_scale = Wide(_denominator)\
    \ / static_cast<Wide>(common);\n        assign_normalized(Wide(_numerator) * left_scale\
    \ + Wide(other._numerator) * right_scale,\n                          Wide(_denominator)\
    \ * left_scale);\n        return *this;\n    }\n\n    constexpr Rational& operator-=(const\
    \ Rational& other) {\n        return *this += -other;\n    }\n\n    constexpr\
    \ Rational& operator*=(const Rational& other) {\n        UnsignedWide first_gcd\
    \ = gcd(magnitude(Wide(_numerator)), static_cast<UnsignedWide>(other._denominator));\n\
    \        UnsignedWide second_gcd = gcd(magnitude(Wide(other._numerator)), static_cast<UnsignedWide>(_denominator));\n\
    \        assign_normalized((Wide(_numerator) / static_cast<Wide>(first_gcd)) *\n\
    \                              (Wide(other._numerator) / static_cast<Wide>(second_gcd)),\n\
    \                          (Wide(_denominator) / static_cast<Wide>(second_gcd))\
    \ *\n                              (Wide(other._denominator) / static_cast<Wide>(first_gcd)));\n\
    \        return *this;\n    }\n\n    constexpr Rational& operator/=(const Rational&\
    \ other) {\n        return *this *= other.reciprocal();\n    }\n\n    friend constexpr\
    \ Rational operator+(Rational left, const Rational& right) {\n        return left\
    \ += right;\n    }\n\n    friend constexpr Rational operator-(Rational left, const\
    \ Rational& right) {\n        return left -= right;\n    }\n\n    friend constexpr\
    \ Rational operator*(Rational left, const Rational& right) {\n        return left\
    \ *= right;\n    }\n\n    friend constexpr Rational operator/(Rational left, const\
    \ Rational& right) {\n        return left /= right;\n    }\n\n    friend constexpr\
    \ bool operator==(const Rational& left, const Rational& right) {\n        return\
    \ left._numerator == right._numerator && left._denominator == right._denominator;\n\
    \    }\n\n    friend constexpr std::strong_ordering operator<=>(const Rational&\
    \ left, const Rational& right) {\n        Wide first = Wide(left._numerator) *\
    \ Wide(right._denominator);\n        Wide second = Wide(right._numerator) * Wide(left._denominator);\n\
    \        if (first < second) return std::strong_ordering::less;\n        if (second\
    \ < first) return std::strong_ordering::greater;\n        return std::strong_ordering::equal;\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& output, const Rational&\
    \ value) {\n        output << value._numerator;\n        if (value._denominator\
    \ != 1) {\n            output << '/' << value._denominator;\n        }\n     \
    \   return output;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ input, Rational& value) {\n        T numerator;\n        if (!(input >> numerator))\
    \ return input;\n        T denominator = 1;\n        if (input.peek() == '/')\
    \ {\n            input.get();\n            if (!(input >> denominator)) return\
    \ input;\n        }\n        value = Rational(numerator, denominator);\n     \
    \   return input;\n    }\n};\n\ntemplate <std::signed_integral T>\nconstexpr Rational<T>\
    \ abs(const Rational<T>& value) {\n    return value.abs();\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"math/stern_brocot_tree.hpp\"\n\n\
    namespace m1une {\nnamespace math {\n\nenum class SternBrocotDirection {\n   \
    \ Left,\n    Right,\n};\n\nstruct SternBrocotRun {\n    SternBrocotDirection direction;\n\
    \    uint64_t count;\n\n    friend bool operator==(const SternBrocotRun&, const\
    \ SternBrocotRun&) = default;\n};\n\nstruct SternBrocotPath {\n    std::vector<SternBrocotRun>\
    \ runs;\n\n    bool empty() const {\n        return runs.empty();\n    }\n\n \
    \   uint64_t depth() const {\n        uint64_t result = 0;\n        for (const\
    \ SternBrocotRun& run : runs) {\n            assert(run.count <= std::numeric_limits<uint64_t>::max()\
    \ - result);\n            result += run.count;\n        }\n        return result;\n\
    \    }\n\n    void push(SternBrocotDirection direction, uint64_t count = 1) {\n\
    \        if (count == 0) return;\n        if (!runs.empty() && runs.back().direction\
    \ == direction) {\n            assert(count <= std::numeric_limits<uint64_t>::max()\
    \ - runs.back().count);\n            runs.back().count += count;\n        } else\
    \ {\n            runs.push_back(SternBrocotRun{direction, count});\n        }\n\
    \    }\n\n    bool move_up(uint64_t count = 1) {\n        if (depth() < count)\
    \ return false;\n        while (count > 0) {\n            SternBrocotRun& run\
    \ = runs.back();\n            uint64_t removed = run.count < count ? run.count\
    \ : count;\n            run.count -= removed;\n            count -= removed;\n\
    \            if (run.count == 0) runs.pop_back();\n        }\n        return true;\n\
    \    }\n\n    SternBrocotPath ancestor(uint64_t count) const {\n        SternBrocotPath\
    \ result = *this;\n        [[maybe_unused]] bool valid = result.move_up(count);\n\
    \        assert(valid);\n        return result;\n    }\n\n    friend bool operator==(const\
    \ SternBrocotPath&, const SternBrocotPath&) = default;\n};\n\ntemplate <std::signed_integral\
    \ T = long long>\nstruct SternBrocotBounds {\n    std::pair<T, T> left;\n    std::pair<T,\
    \ T> right;\n};\n\ntemplate <std::signed_integral T>\nSternBrocotPath stern_brocot_path(T\
    \ numerator, T denominator) {\n    assert(0 < numerator);\n    assert(0 < denominator);\n\
    \    SternBrocotPath result;\n    while (numerator != denominator) {\n       \
    \ if (numerator < denominator) {\n            T count = (denominator - 1) / numerator;\n\
    \            result.push(SternBrocotDirection::Left, uint64_t(count));\n     \
    \       denominator -= count * numerator;\n        } else {\n            T count\
    \ = (numerator - 1) / denominator;\n            result.push(SternBrocotDirection::Right,\
    \ uint64_t(count));\n            numerator -= count * denominator;\n        }\n\
    \    }\n    assert(numerator == 1);\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T = long long>\nRational<T> stern_brocot_decode(const SternBrocotPath& path)\
    \ {\n    using Wide = __int128_t;\n    Wide left_numerator = 0;\n    Wide left_denominator\
    \ = 1;\n    Wide right_numerator = 1;\n    Wide right_denominator = 0;\n    Wide\
    \ numerator = 1;\n    Wide denominator = 1;\n    [[maybe_unused]] const Wide maximum\
    \ = std::numeric_limits<T>::max();\n    for (const SternBrocotRun& run : path.runs)\
    \ {\n        assert(run.count > 0);\n        assert(Wide(run.count) <= maximum);\n\
    \        Wide count = run.count;\n        if (run.direction == SternBrocotDirection::Left)\
    \ {\n            right_numerator = numerator + (count - 1) * left_numerator;\n\
    \            right_denominator = denominator + (count - 1) * left_denominator;\n\
    \            numerator += count * left_numerator;\n            denominator +=\
    \ count * left_denominator;\n        } else {\n            left_numerator = numerator\
    \ + (count - 1) * right_numerator;\n            left_denominator = denominator\
    \ + (count - 1) * right_denominator;\n            numerator += count * right_numerator;\n\
    \            denominator += count * right_denominator;\n        }\n        assert(numerator\
    \ <= maximum);\n        assert(denominator <= maximum);\n        assert(left_numerator\
    \ <= maximum);\n        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    return\
    \ Rational<T>(T(numerator), T(denominator));\n}\n\ntemplate <std::signed_integral\
    \ T>\nuint64_t stern_brocot_depth(T numerator, T denominator) {\n    return stern_brocot_path(numerator,\
    \ denominator).depth();\n}\n\ninline SternBrocotPath stern_brocot_lca_path(\n\
    \    const SternBrocotPath& first,\n    const SternBrocotPath& second\n) {\n \
    \   SternBrocotPath result;\n    int limit = int(first.runs.size() < second.runs.size()\
    \ ? first.runs.size() : second.runs.size());\n    for (int i = 0; i < limit; i++)\
    \ {\n        if (first.runs[i].direction != second.runs[i].direction) break;\n\
    \        uint64_t common =\n            first.runs[i].count < second.runs[i].count\n\
    \                ? first.runs[i].count\n                : second.runs[i].count;\n\
    \        result.push(first.runs[i].direction, common);\n        if (first.runs[i].count\
    \ != second.runs[i].count) break;\n    }\n    return result;\n}\n\ntemplate <std::signed_integral\
    \ T>\nRational<T> stern_brocot_lca(\n    T first_numerator,\n    T first_denominator,\n\
    \    T second_numerator,\n    T second_denominator\n) {\n    SternBrocotPath path\
    \ = stern_brocot_lca_path(\n        stern_brocot_path(first_numerator, first_denominator),\n\
    \        stern_brocot_path(second_numerator, second_denominator)\n    );\n   \
    \ return stern_brocot_decode<T>(path);\n}\n\ntemplate <std::signed_integral T>\n\
    Rational<T> stern_brocot_ancestor(T numerator, T denominator, uint64_t up) {\n\
    \    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n    [[maybe_unused]]\
    \ bool valid = path.move_up(up);\n    assert(valid);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_parent(T numerator,\
    \ T denominator) {\n    return stern_brocot_ancestor(numerator, denominator, 1);\n\
    }\n\ntemplate <std::signed_integral T>\nRational<T> stern_brocot_move(\n    T\
    \ numerator,\n    T denominator,\n    SternBrocotDirection direction,\n    uint64_t\
    \ count = 1\n) {\n    SternBrocotPath path = stern_brocot_path(numerator, denominator);\n\
    \    path.push(direction, count);\n    return stern_brocot_decode<T>(path);\n\
    }\n\ntemplate <std::signed_integral T = long long>\nSternBrocotBounds<T> stern_brocot_bounds(const\
    \ SternBrocotPath& path) {\n    using Wide = __int128_t;\n    Wide left_numerator\
    \ = 0;\n    Wide left_denominator = 1;\n    Wide right_numerator = 1;\n    Wide\
    \ right_denominator = 0;\n    Wide numerator = 1;\n    Wide denominator = 1;\n\
    \    [[maybe_unused]] const Wide maximum = std::numeric_limits<T>::max();\n\n\
    \    for (const SternBrocotRun& run : path.runs) {\n        assert(run.count >\
    \ 0);\n        assert(Wide(run.count) <= maximum);\n        Wide count = run.count;\n\
    \        if (run.direction == SternBrocotDirection::Left) {\n            right_numerator\
    \ = numerator + (count - 1) * left_numerator;\n            right_denominator =\
    \ denominator + (count - 1) * left_denominator;\n            numerator += count\
    \ * left_numerator;\n            denominator += count * left_denominator;\n  \
    \      } else {\n            left_numerator = numerator + (count - 1) * right_numerator;\n\
    \            left_denominator = denominator + (count - 1) * right_denominator;\n\
    \            numerator += count * right_numerator;\n            denominator +=\
    \ count * right_denominator;\n        }\n        assert(numerator <= maximum);\n\
    \        assert(denominator <= maximum);\n        assert(left_numerator <= maximum);\n\
    \        assert(left_denominator <= maximum);\n        assert(right_numerator\
    \ <= maximum);\n        assert(right_denominator <= maximum);\n    }\n    SternBrocotBounds<T>\
    \ result;\n    result.left = {T(left_numerator), T(left_denominator)};\n    result.right\
    \ = {T(right_numerator), T(right_denominator)};\n    return result;\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 9 \"verify/math/yosupo_stern_brocot_tree.test.cpp\"\
    \nusing ll = long long;\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    ll T;\n    fast_input >>\
    \ T;\n    while (T--) {\n        string s;\n        fast_input >> s;\n       \
    \ if (s == \"ENCODE_PATH\") {\n            ll a, b;\n            fast_input >>\
    \ a >> b;\n            auto path = m1une::math::stern_brocot_path(a, b);\n   \
    \         auto& runs = path.runs;\n            fast_output << runs.size();\n \
    \           for (auto& dir : runs) {\n                if (dir.direction == m1une::math::SternBrocotDirection::Left)\
    \ {\n                    fast_output << \" L \" << dir.count;\n              \
    \  } else {\n                    fast_output << \" R \" << dir.count;\n      \
    \          }\n            }\n            fast_output << '\\n';\n        } else\
    \ if (s == \"DECODE_PATH\") {\n            m1une::math::SternBrocotPath path;\n\
    \            ll k;\n            fast_input >> k;\n            while (k--) {\n\
    \                char c;\n                fast_input >> c;\n                ll\
    \ n;\n                fast_input >> n;\n                if (c == 'L') {\n    \
    \                path.push(m1une::math::SternBrocotDirection::Left, n);\n    \
    \            } else if (c == 'R') {\n                    path.push(m1une::math::SternBrocotDirection::Right,\
    \ n);\n                } else {\n                    exit(1);\n              \
    \  }\n            }\n            auto r = m1une::math::stern_brocot_decode(path);\n\
    \            fast_output << r.numerator() << ' ' << r.denominator() << '\\n';\n\
    \        } else if (s == \"LCA\") {\n            ll a, b, c, d;\n            fast_input\
    \ >> a >> b >> c >> d;\n            auto r = m1une::math::stern_brocot_lca(a,\
    \ b, c, d);\n            fast_output << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n        } else if (s == \"ANCESTOR\") {\n            ll k, a, b;\n\
    \            fast_input >> k >> a >> b;\n            ll d = m1une::math::stern_brocot_depth(a,\
    \ b);\n            if (d < k) {\n                fast_output << \"-1\\n\";\n \
    \           } else {\n                auto r = m1une::math::stern_brocot_ancestor(a,\
    \ b, d - k);\n                fast_output << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n            }\n        } else if (s == \"RANGE\") {\n           \
    \ ll a, b;\n            fast_input >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto bound = m1une::math::stern_brocot_bounds(path);\n    \
    \        fast_output << bound.left.first << ' ' << bound.left.second << ' ' <<\
    \ bound.right.first << ' ' << bound.right.second\n                 << '\\n';\n\
    \        } else {\n            exit(1);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/stern_brocot_tree\"\n\n\
    #include \"../../utilities/fast_io.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace\
    \ std;\n\n#include \"math/stern_brocot_tree.hpp\"\nusing ll = long long;\n\nint\
    \ main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    ll T;\n    fast_input >> T;\n    while (T--) {\n       \
    \ string s;\n        fast_input >> s;\n        if (s == \"ENCODE_PATH\") {\n \
    \           ll a, b;\n            fast_input >> a >> b;\n            auto path\
    \ = m1une::math::stern_brocot_path(a, b);\n            auto& runs = path.runs;\n\
    \            fast_output << runs.size();\n            for (auto& dir : runs) {\n\
    \                if (dir.direction == m1une::math::SternBrocotDirection::Left)\
    \ {\n                    fast_output << \" L \" << dir.count;\n              \
    \  } else {\n                    fast_output << \" R \" << dir.count;\n      \
    \          }\n            }\n            fast_output << '\\n';\n        } else\
    \ if (s == \"DECODE_PATH\") {\n            m1une::math::SternBrocotPath path;\n\
    \            ll k;\n            fast_input >> k;\n            while (k--) {\n\
    \                char c;\n                fast_input >> c;\n                ll\
    \ n;\n                fast_input >> n;\n                if (c == 'L') {\n    \
    \                path.push(m1une::math::SternBrocotDirection::Left, n);\n    \
    \            } else if (c == 'R') {\n                    path.push(m1une::math::SternBrocotDirection::Right,\
    \ n);\n                } else {\n                    exit(1);\n              \
    \  }\n            }\n            auto r = m1une::math::stern_brocot_decode(path);\n\
    \            fast_output << r.numerator() << ' ' << r.denominator() << '\\n';\n\
    \        } else if (s == \"LCA\") {\n            ll a, b, c, d;\n            fast_input\
    \ >> a >> b >> c >> d;\n            auto r = m1une::math::stern_brocot_lca(a,\
    \ b, c, d);\n            fast_output << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n        } else if (s == \"ANCESTOR\") {\n            ll k, a, b;\n\
    \            fast_input >> k >> a >> b;\n            ll d = m1une::math::stern_brocot_depth(a,\
    \ b);\n            if (d < k) {\n                fast_output << \"-1\\n\";\n \
    \           } else {\n                auto r = m1une::math::stern_brocot_ancestor(a,\
    \ b, d - k);\n                fast_output << r.numerator() << ' ' << r.denominator()\
    \ << '\\n';\n            }\n        } else if (s == \"RANGE\") {\n           \
    \ ll a, b;\n            fast_input >> a >> b;\n            auto path = m1une::math::stern_brocot_path(a,\
    \ b);\n            auto bound = m1une::math::stern_brocot_bounds(path);\n    \
    \        fast_output << bound.left.first << ' ' << bound.left.second << ' ' <<\
    \ bound.right.first << ' ' << bound.right.second\n                 << '\\n';\n\
    \        } else {\n            exit(1);\n        }\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - math/stern_brocot_tree.hpp
  - math/rational.hpp
  isVerificationFile: true
  path: verify/math/yosupo_stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/yosupo_stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/math/yosupo_stern_brocot_tree.test.cpp
- /verify/verify/math/yosupo_stern_brocot_tree.test.cpp.html
title: verify/math/yosupo_stern_brocot_tree.test.cpp
---
