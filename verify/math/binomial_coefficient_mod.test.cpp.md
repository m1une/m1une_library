---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/binomial_coefficient_mod.hpp
    title: Binomial Coefficient Modulo an Arbitrary Modulus
  - icon: ':heavy_check_mark:'
    path: math/number_theory.hpp
    title: Number Theory
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
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "#line 1 \"verify/math/binomial_coefficient_mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/math/binomial_coefficient_mod.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"math/binomial_coefficient_mod.hpp\"\n\n\n\n#line\
    \ 8 \"math/binomial_coefficient_mod.hpp\"\n\n#line 1 \"math/number_theory.hpp\"\
    \n\n\n\n#line 6 \"math/number_theory.hpp\"\n#include <limits>\n#include <tuple>\n\
    #line 10 \"math/number_theory.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n\
    namespace internal {\n\ninline long long safe_mod(long long x, long long mod)\
    \ {\n    x %= mod;\n    if (x < 0) x += mod;\n    return x;\n}\n\ninline unsigned\
    \ __int128 floor_sum_unsigned(unsigned long long n, unsigned long long mod, unsigned\
    \ long long a,\n                                            unsigned long long\
    \ b) {\n    unsigned __int128 answer = 0;\n    while (true) {\n        if (a >=\
    \ mod) {\n            answer += static_cast<unsigned __int128>(n) * (n - 1) /\
    \ 2 * (a / mod);\n            a %= mod;\n        }\n        if (b >= mod) {\n\
    \            answer += static_cast<unsigned __int128>(n) * (b / mod);\n      \
    \      b %= mod;\n        }\n\n        const unsigned __int128 y_max = static_cast<unsigned\
    \ __int128>(a) * n + b;\n        if (y_max < mod) break;\n        n = static_cast<unsigned\
    \ long long>(y_max / mod);\n        b = static_cast<unsigned long long>(y_max\
    \ % mod);\n        unsigned long long tmp = mod;\n        mod = a;\n        a\
    \ = tmp;\n    }\n    return answer;\n}\n\n}  // namespace internal\n\n// Returns\
    \ (g, x, y), where g = gcd(a, b) is nonnegative and\n// a * x + b * y = g. Returns\
    \ (0, 0, 0) when a = b = 0.\ninline std::tuple<long long, long long, long long>\
    \ extended_gcd(long long a,\n                                                \
    \               long long b) {\n    using i128 = __int128;\n    if (a == 0 &&\
    \ b == 0) return {0, 0, 0};\n\n    i128 old_remainder = a;\n    i128 remainder\
    \ = b;\n    if (old_remainder < 0) old_remainder = -old_remainder;\n    if (remainder\
    \ < 0) remainder = -remainder;\n    i128 old_x = 1;\n    i128 x = 0;\n    i128\
    \ old_y = 0;\n    i128 y = 1;\n\n    while (remainder != 0) {\n        i128 quotient\
    \ = old_remainder / remainder;\n\n        i128 next = old_remainder - quotient\
    \ * remainder;\n        old_remainder = remainder;\n        remainder = next;\n\
    \n        next = old_x - quotient * x;\n        old_x = x;\n        x = next;\n\
    \n        next = old_y - quotient * y;\n        old_y = y;\n        y = next;\n\
    \    }\n\n    if (a < 0) old_x = -old_x;\n    if (b < 0) old_y = -old_y;\n\n#ifndef\
    \ NDEBUG\n    const i128 minimum = std::numeric_limits<long long>::min();\n  \
    \  const i128 maximum = std::numeric_limits<long long>::max();\n    assert(old_remainder\
    \ <= maximum);\n    assert(minimum <= old_x && old_x <= maximum);\n    assert(minimum\
    \ <= old_y && old_y <= maximum);\n#endif\n    return {static_cast<long long>(old_remainder),\
    \ static_cast<long long>(old_x),\n            static_cast<long long>(old_y)};\n\
    }\n\ninline long long pow_mod(long long x, unsigned long long exponent, long long\
    \ mod) {\n    assert(mod >= 1);\n    if (mod == 1) return 0;\n\n    unsigned long\
    \ long base = static_cast<unsigned long long>(internal::safe_mod(x, mod));\n \
    \   unsigned long long result = 1;\n    const unsigned long long unsigned_mod\
    \ = static_cast<unsigned long long>(mod);\n    while (exponent > 0) {\n      \
    \  if (exponent & 1) {\n            result = static_cast<unsigned long long>(static_cast<unsigned\
    \ __int128>(result) * base % unsigned_mod);\n        }\n        base = static_cast<unsigned\
    \ long long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);\n  \
    \      exponent >>= 1;\n    }\n    return static_cast<long long>(result);\n}\n\
    \n// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)\n//\
    \ modulo mod. The returned x is in [0, mod / gcd(a, mod)).\ninline std::pair<long\
    \ long, long long> inv_gcd(long long a, long long mod) {\n    assert(mod >= 1);\n\
    \    a = internal::safe_mod(a, mod);\n    if (a == 0) return {mod, 0};\n\n   \
    \ long long s = mod;\n    long long t = a;\n    long long m0 = 0;\n    long long\
    \ m1 = 1;\n    while (t > 0) {\n        const long long quotient = s / t;\n  \
    \      s -= t * quotient;\n        m0 -= m1 * quotient;\n\n        long long tmp\
    \ = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n\
    \        m1 = tmp;\n    }\n    if (m0 < 0) m0 += mod / s;\n    return {s, m0};\n\
    }\n\ninline long long inv_mod(long long x, long long mod) {\n    const auto result\
    \ = inv_gcd(x, mod);\n    assert(result.first == 1);\n    return result.second;\n\
    }\n\n// Returns the smallest nonnegative solution and the least common multiple\
    \ of\n// the moduli. Returns {0, 0} when the system is inconsistent.\ninline std::pair<long\
    \ long, long long> crt(const std::vector<long long>& remainders,\n           \
    \                                const std::vector<long long>& moduli) {\n   \
    \ assert(remainders.size() == moduli.size());\n\n    long long r0 = 0;\n    long\
    \ long m0 = 1;\n    for (int i = 0; i < int(remainders.size()); i++) {\n     \
    \   assert(moduli[i] >= 1);\n        long long r1 = internal::safe_mod(remainders[i],\
    \ moduli[i]);\n        long long m1 = moduli[i];\n\n        if (m0 < m1) {\n \
    \           long long tmp = r0;\n            r0 = r1;\n            r1 = tmp;\n\
    \            tmp = m0;\n            m0 = m1;\n            m1 = tmp;\n        }\n\
    \        if (m0 % m1 == 0) {\n            if (r0 % m1 != r1) return {0, 0};\n\
    \            continue;\n        }\n\n        const auto inverse = inv_gcd(m0,\
    \ m1);\n        const long long gcd = inverse.first;\n        const long long\
    \ reduced_modulus = m1 / gcd;\n        const __int128 difference = static_cast<__int128>(r1)\
    \ - r0;\n        if (difference % gcd != 0) return {0, 0};\n\n        __int128\
    \ multiplier = difference / gcd % reduced_modulus;\n        multiplier = multiplier\
    \ * inverse.second % reduced_modulus;\n        if (multiplier < 0) multiplier\
    \ += reduced_modulus;\n\n        const __int128 new_modulus = static_cast<__int128>(m0)\
    \ * reduced_modulus;\n        assert(new_modulus <= std::numeric_limits<long long>::max());\n\
    \        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;\n\
    \        new_remainder %= new_modulus;\n        if (new_remainder < 0) new_remainder\
    \ += new_modulus;\n        r0 = static_cast<long long>(new_remainder);\n     \
    \   m0 = static_cast<long long>(new_modulus);\n    }\n    return {r0, m0};\n}\n\
    \n// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).\ninline long long floor_sum(long\
    \ long n, long long mod, long long a, long long b) {\n    assert(n >= 0);\n  \
    \  assert(mod >= 1);\n\n    const long long normalized_a = internal::safe_mod(a,\
    \ mod);\n    const long long normalized_b = internal::safe_mod(b, mod);\n    __int128\
    \ answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;\n\
    \    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;\n    answer\
    \ += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned\
    \ long long>(mod),\n                                           static_cast<unsigned\
    \ long long>(normalized_a),\n                                           static_cast<unsigned\
    \ long long>(normalized_b));\n\n    assert(answer >= std::numeric_limits<long\
    \ long>::min());\n    assert(answer <= std::numeric_limits<long long>::max());\n\
    \    return static_cast<long long>(answer);\n}\n\n}  // namespace math\n}  //\
    \ namespace m1une\n\n\n#line 10 \"math/binomial_coefficient_mod.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\n// Binomial coefficients modulo a fixed, not necessarily\
    \ prime, modulus.\nclass BinomialCoefficientMod {\n   private:\n    struct PrimePower\
    \ {\n        uint32_t prime;\n        int exponent;\n        uint32_t modulus;\n\
    \        uint32_t crt_multiplier;\n        std::vector<uint32_t> unit_factorial_prefix;\n\
    \n        uint32_t multiply(uint32_t lhs, uint32_t rhs) const {\n            return\
    \ uint32_t(uint64_t(lhs) * rhs % modulus);\n        }\n\n        uint32_t power(uint32_t\
    \ base, uint64_t exponent_) const {\n            uint32_t result = 1 % modulus;\n\
    \            while (exponent_ > 0) {\n                if (exponent_ & 1) result\
    \ = multiply(result, base);\n                base = multiply(base, base);\n  \
    \              exponent_ >>= 1;\n            }\n            return result;\n \
    \       }\n\n        uint64_t factorial_valuation(uint64_t n) const {\n      \
    \      uint64_t result = 0;\n            while (n > 0) {\n                n /=\
    \ prime;\n                result += n;\n            }\n            return result;\n\
    \        }\n\n        uint32_t unit_factorial(uint64_t n) const {\n          \
    \  if (n == 0) return 1 % modulus;\n            const uint32_t block_product =\
    \ unit_factorial_prefix.back();\n            uint32_t result = power(block_product,\
    \ n / modulus);\n            result = multiply(result, unit_factorial_prefix[std::size_t(n\
    \ % modulus)]);\n            return multiply(result, unit_factorial(n / prime));\n\
    \        }\n\n        uint32_t binom(uint64_t n, uint64_t k) const {\n       \
    \     if (k > n) return 0;\n            const uint64_t valuation = factorial_valuation(n)\
    \ - factorial_valuation(k) -\n                                       factorial_valuation(n\
    \ - k);\n            if (valuation >= uint64_t(exponent)) return 0;\n\n      \
    \      const uint32_t numerator = unit_factorial(n);\n            const uint32_t\
    \ denominator =\n                multiply(unit_factorial(k), unit_factorial(n\
    \ - k));\n            const uint32_t inverse_denominator =\n                uint32_t(inv_mod(denominator,\
    \ modulus));\n            uint32_t result = multiply(numerator, inverse_denominator);\n\
    \            result = multiply(result, power(prime, valuation));\n           \
    \ return result;\n        }\n    };\n\n    uint32_t _modulus;\n    std::vector<PrimePower>\
    \ _prime_powers;\n\n   public:\n    explicit BinomialCoefficientMod(uint32_t modulus)\
    \ : _modulus(modulus) {\n        assert(modulus >= 1);\n        uint32_t remaining\
    \ = modulus;\n        for (uint32_t prime = 2; uint64_t(prime) * prime <= remaining;\
    \ prime++) {\n            if (remaining % prime != 0) continue;\n            int\
    \ exponent = 0;\n            uint32_t prime_power = 1;\n            do {\n   \
    \             remaining /= prime;\n                prime_power *= prime;\n   \
    \             exponent++;\n            } while (remaining % prime == 0);\n   \
    \         _prime_powers.push_back(\n                PrimePower{prime, exponent,\
    \ prime_power, 0, {}});\n        }\n        if (remaining > 1) {\n           \
    \ _prime_powers.push_back(PrimePower{remaining, 1, remaining, 0, {}});\n     \
    \   }\n\n        for (PrimePower& component : _prime_powers) {\n            component.unit_factorial_prefix.resize(std::size_t(component.modulus));\n\
    \            component.unit_factorial_prefix[0] = 1;\n            for (uint32_t\
    \ value = 1; value < component.modulus; value++) {\n                component.unit_factorial_prefix[value]\
    \ =\n                    component.unit_factorial_prefix[value - 1];\n       \
    \         if (value % component.prime != 0) {\n                    component.unit_factorial_prefix[value]\
    \ = component.multiply(\n                        component.unit_factorial_prefix[value],\
    \ value);\n                }\n            }\n\n            const uint32_t other\
    \ = modulus / component.modulus;\n            const uint32_t inverse =\n     \
    \           uint32_t(inv_mod(other, component.modulus));\n            component.crt_multiplier\
    \ =\n                uint32_t(uint64_t(other) * inverse % modulus);\n        }\n\
    \    }\n\n    uint32_t modulus() const {\n        return _modulus;\n    }\n\n\
    \    uint32_t binom(uint64_t n, uint64_t k) const {\n        if (k > n || _modulus\
    \ == 1) return 0;\n        uint64_t result = 0;\n        for (const PrimePower&\
    \ component : _prime_powers) {\n            const uint32_t residue = component.binom(n,\
    \ k);\n            result += uint64_t(residue) * component.crt_multiplier % _modulus;\n\
    \            result %= _modulus;\n        }\n        return uint32_t(result);\n\
    \    }\n\n    uint32_t operator()(uint64_t n, uint64_t k) const {\n        return\
    \ binom(n, k);\n    }\n};\n\nusing ArbitraryModBinomialCoefficient = BinomialCoefficientMod;\n\
    \n}  // namespace math\n}  // namespace m1une\n\n\n#line 9 \"verify/math/binomial_coefficient_mod.test.cpp\"\
    \n\nnamespace {\n\nvoid test_against_pascal_triangle() {\n    constexpr int maximum\
    \ = 60;\n    for (uint32_t modulus = 1; modulus <= 100; modulus++) {\n       \
    \ m1une::math::BinomialCoefficientMod combinations(modulus);\n        assert(combinations.modulus()\
    \ == modulus);\n\n        std::vector<std::vector<uint32_t>> binom(maximum + 1);\n\
    \        for (int n = 0; n <= maximum; n++) {\n            binom[n].resize(n +\
    \ 1);\n            binom[n][0] = 1 % modulus;\n            binom[n][n] = 1 % modulus;\n\
    \            for (int k = 1; k < n; k++) {\n                binom[n][k] = (binom[n\
    \ - 1][k - 1] + binom[n - 1][k]) % modulus;\n            }\n            for (int\
    \ k = 0; k <= n; k++) {\n                assert(combinations.binom(n, k) == binom[n][k]);\n\
    \                assert(combinations(n, k) == binom[n][k]);\n            }\n \
    \           assert(combinations.binom(n, uint64_t(n) + 1) == 0);\n        }\n\
    \    }\n}\n\nvoid test_large_arguments() {\n    constexpr uint64_t n = 1000000000000000000ULL;\n\
    \    for (uint32_t modulus : {1U, 2U, 8U, 9U, 12U, 999983U, 1000000U}) {\n   \
    \     m1une::math::ArbitraryModBinomialCoefficient combinations(modulus);\n  \
    \      assert(combinations(n, 0) == 1 % modulus);\n        assert(combinations(n,\
    \ 1) == n % modulus);\n        assert(combinations(n, n) == 1 % modulus);\n  \
    \      assert(combinations(n, 123456789) ==\n               combinations(n, n\
    \ - 123456789));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_against_pascal_triangle();\n\
    \    test_large_arguments();\n\n    int query_count;\n    uint32_t modulus;\n\
    \    fast_input >> query_count >> modulus;\n    m1une::math::BinomialCoefficientMod\
    \ combinations(modulus);\n    while (query_count--) {\n        uint64_t n, k;\n\
    \        fast_input >> n >> k;\n        fast_output << combinations.binom(n, k)\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    \n#include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\n#include \"../../math/binomial_coefficient_mod.hpp\"\n\n\
    namespace {\n\nvoid test_against_pascal_triangle() {\n    constexpr int maximum\
    \ = 60;\n    for (uint32_t modulus = 1; modulus <= 100; modulus++) {\n       \
    \ m1une::math::BinomialCoefficientMod combinations(modulus);\n        assert(combinations.modulus()\
    \ == modulus);\n\n        std::vector<std::vector<uint32_t>> binom(maximum + 1);\n\
    \        for (int n = 0; n <= maximum; n++) {\n            binom[n].resize(n +\
    \ 1);\n            binom[n][0] = 1 % modulus;\n            binom[n][n] = 1 % modulus;\n\
    \            for (int k = 1; k < n; k++) {\n                binom[n][k] = (binom[n\
    \ - 1][k - 1] + binom[n - 1][k]) % modulus;\n            }\n            for (int\
    \ k = 0; k <= n; k++) {\n                assert(combinations.binom(n, k) == binom[n][k]);\n\
    \                assert(combinations(n, k) == binom[n][k]);\n            }\n \
    \           assert(combinations.binom(n, uint64_t(n) + 1) == 0);\n        }\n\
    \    }\n}\n\nvoid test_large_arguments() {\n    constexpr uint64_t n = 1000000000000000000ULL;\n\
    \    for (uint32_t modulus : {1U, 2U, 8U, 9U, 12U, 999983U, 1000000U}) {\n   \
    \     m1une::math::ArbitraryModBinomialCoefficient combinations(modulus);\n  \
    \      assert(combinations(n, 0) == 1 % modulus);\n        assert(combinations(n,\
    \ 1) == n % modulus);\n        assert(combinations(n, n) == 1 % modulus);\n  \
    \      assert(combinations(n, 123456789) ==\n               combinations(n, n\
    \ - 123456789));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_against_pascal_triangle();\n\
    \    test_large_arguments();\n\n    int query_count;\n    uint32_t modulus;\n\
    \    fast_input >> query_count >> modulus;\n    m1une::math::BinomialCoefficientMod\
    \ combinations(modulus);\n    while (query_count--) {\n        uint64_t n, k;\n\
    \        fast_input >> n >> k;\n        fast_output << combinations.binom(n, k)\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - math/binomial_coefficient_mod.hpp
  - math/number_theory.hpp
  isVerificationFile: true
  path: verify/math/binomial_coefficient_mod.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/binomial_coefficient_mod.test.cpp
layout: document
redirect_from:
- /verify/verify/math/binomial_coefficient_mod.test.cpp
- /verify/verify/math/binomial_coefficient_mod.test.cpp.html
title: verify/math/binomial_coefficient_mod.test.cpp
---
