---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/bigint.hpp
    title: BigInt
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  - icon: ':heavy_check_mark:'
    path: utilities/int128.hpp
    title: Int128
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
  - icon: ':heavy_check_mark:'
    path: utilities/timer.hpp
    title: Timer
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
  bundledCode: "#line 1 \"verify/utilities/basic_utilities.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/utilities/basic_utilities.test.cpp\"\
    \n#include <limits>\n#include <sstream>\n#include <stdexcept>\n#line 10 \"verify/utilities/basic_utilities.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"utilities/bigint.hpp\"\n\n\n\n#line 5 \"utilities/bigint.hpp\"\
    \n#include <bit>\n#line 8 \"utilities/bigint.hpp\"\n#include <cmath>\n#line 10\
    \ \"utilities/bigint.hpp\"\n#include <iostream>\n#include <numbers>\n#line 16\
    \ \"utilities/bigint.hpp\"\n\n#line 1 \"math/fps/convolution.hpp\"\n\n\n\n#line\
    \ 9 \"math/fps/convolution.hpp\"\n#include <new>\n#line 13 \"math/fps/convolution.hpp\"\
    \n\n#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))\n\
    #include <immintrin.h>\n#define M1UNE_FPS_HAS_X86_SIMD 1\n#pragma GCC push_options\n\
    #pragma GCC target(\"avx2,bmi\")\n#endif\n\n#line 1 \"math/fps/internal/ntt998_faster.hpp\"\
    \n\n\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\n#line 9 \"math/fps/internal/ntt998_faster.hpp\"\
    \n\n#include <immintrin.h>\n\nnamespace m1une {\nnamespace fps {\nnamespace internal\
    \ {\nnamespace fast998_v2 {\n\n// Fixed-modulus AVX2 transform with an in-register\
    \ degree-8 residue product.\n\nusing u32=unsigned;\nusing u64=unsigned long long;\n\
    using idt=std::size_t;\nusing I256=__m256i;\ninline void store256(void*p,I256\
    \ x){\n    _mm256_store_si256((I256*)p,x);\n}\ninline I256 load256(const void*p){\n\
    \    return _mm256_load_si256((const I256*)p);\n}\nconstexpr u32 shrk(u32 x,u32\
    \ M){\n    return std::min(x,x-M);\n}\nconstexpr u32 dilt(u32 x,u32 M){\n    return\
    \ std::min(x,x+M);\n}\nconstexpr u32 reduce(u64 x,u32 niv,u32 M){\n    return\
    \ (x+u64(u32(x)*niv)*M)>>32;\n}\nconstexpr u32 mul(u32 x,u32 y,u32 niv,u32 M){\n\
    \    return reduce(u64(x)*y,niv,M);\n}\nconstexpr u32 mul_s(u32 x,u32 y,u32 niv,u32\
    \ M){\n    return shrk(reduce(u64(x)*y,niv,M),M);\n}\nconstexpr u32 qpw(u32 a,u32\
    \ b,u32 niv,u32 M,u32 r){\n    for(;b;b>>=1,a=mul(a,a,niv,M)){\n        if(b&1){\n\
    \            r=mul(r,a,niv,M);\n        }\n    }\n    return r;\n}\nconstexpr\
    \ u32 qpw_s(u32 a,u32 b,u32 niv,u32 M,u32 r){\n    return shrk(qpw(a,b,niv,M,r),M);\n\
    }\ninline I256 shrk32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_sub_epi32(x,M));\n\
    }\ninline I256 dilt32(I256 x,I256 M){\n    return _mm256_min_epu32(x,_mm256_add_epi32(x,M));\n\
    }\ninline I256 Ladd32(I256 x,I256 y,I256){\n    return _mm256_add_epi32(x,y);\n\
    }\ninline I256 Lsub32(I256 x,I256 y,I256 M){\n    return _mm256_add_epi32(_mm256_sub_epi32(x,y),M);\n\
    }\ninline I256 add32(I256 x,I256 y,I256 M){\n    return shrk32(_mm256_add_epi32(x,y),M);\n\
    }\ninline I256 sub32(I256 x,I256 y,I256 M){\n    return dilt32(_mm256_sub_epi32(x,y),M);\n\
    }\ntemplate<int msk>inline I256 neg32_m(I256 x,I256 M){\n    return _mm256_blend_epi32(x,_mm256_sub_epi32(M,x),msk);\n\
    }\ninline I256 reduce(I256 a,I256 b,I256 niv,I256 M){\n    I256 c=_mm256_mul_epu32(a,niv),d=_mm256_mul_epu32(b,niv);\n\
    \    c=_mm256_mul_epu32(c,M),d=_mm256_mul_epu32(d,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(a,c),32),_mm256_add_epi64(b,d),0xaa);\n\
    }\ninline I256 mul(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32)),niv,M);\n\
    }\ninline I256 mul_s(I256 a,I256 b,I256 niv,I256 M){\n    return shrk32(mul(a,b,niv,M),M);\n\
    }\ninline I256 mul_bsm(I256 a,I256 b,I256 niv,I256 M){\n    return reduce(_mm256_mul_epu32(a,b),_mm256_mul_epu32(_mm256_srli_epi64(a,32),b),niv,M);\n\
    }\ninline I256 mul_bsmfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),bniv);\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),b);\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_bfxd(I256 a,I256 b,I256 bniv,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bniv),dd=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(bniv,32));\n\
    \    I256 c=_mm256_mul_epu32(a,b),d=_mm256_mul_epu32(_mm256_srli_epi64(a,32),_mm256_srli_epi64(b,32));\n\
    \    cc=_mm256_mul_epu32(cc,M),dd=_mm256_mul_epu32(dd,M);\n    return _mm256_blend_epi32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),_mm256_add_epi64(d,dd),0xaa);\n\
    }\ninline I256 mul_upd_rt(I256 a,I256 bu,I256 M){\n    I256 cc=_mm256_mul_epu32(a,bu),c=_mm256_mul_epu32(a,_mm256_srli_epi64(bu,32));\n\
    \    cc=_mm256_mul_epu32(cc,M);\n    return shrk32(_mm256_srli_epi64(_mm256_add_epi64(c,cc),32),M);\n\
    }\nconstexpr auto _mxlg=26,_lg_itth=6;\nconstexpr auto _itth=idt(1)<<_lg_itth;\n\
    static_assert(_lg_itth%2==0);\nstruct FNTT32_info{\n    u32 mod,mod2,niv,one,r2,r3,img,imgniv,RT1[_mxlg];\n\
    \    alignas(32) std::array<u32,8> rt3[_mxlg-2],rt3i[_mxlg-2],bwbr,bwb,bwbi,rt4[_mxlg-3],rt4niv[_mxlg-3],rt4i[_mxlg-3],rt4iniv[_mxlg-3],pr2,pr4,pr2niv,pr4niv,pr2i,pr2iniv,pr4i,pr4iniv;\n\
    \    constexpr FNTT32_info(const u32 m):mod(m),mod2(m*2),niv([&]{u32 n=2+m;for(int\
    \ i=0;i<4;++i){n*=2+m*n;}return n;}()),one((-m)%m),r2((-u64(m))%m),r3(mul_s(r2,r2,niv,m)),img{},imgniv{},RT1{},rt3{},rt3i{},bwbr{},bwb{},bwbi{},rt4{},rt4niv{},rt4i{},rt4iniv{},pr2{},pr4{},pr2niv{},pr4niv{},pr2i{},pr2iniv{},pr4i{},pr4iniv{}{\n\
    \        const int k=__builtin_ctz(m-1);\n\t\tu32 _g=mul(3,r2,niv,mod);\n    \
    \    for(;;++_g){\n            if(qpw_s(_g,mod>>1,niv,mod,one)!=one){\n      \
    \          break;\n            }\n        }\n\t\t_g=qpw(_g,mod>>k,niv,mod,one);\n\
    \        u32 rt1[_mxlg-1],rt1i[_mxlg-1];\n        rt1[k-2]=_g,rt1i[k-2]=qpw(_g,mod-2,niv,mod,one);\n\
    \        for(int i=k-2;i>0;--i){\n            rt1[i-1]=mul(rt1[i],rt1[i],niv,mod);\n\
    \            rt1i[i-1]=mul(rt1i[i],rt1i[i],niv,mod);\n        }\n        RT1[k-1]=qpw_s(_g,3,niv,mod,one);\n\
    \        for(int i=k-1;i>0;--i){\n\t\t\tRT1[i-1]=mul_s(RT1[i],RT1[i],niv,mod);\n\
    \        }\n        img=rt1[0],imgniv=img*niv;\n        bwbr={one,0,one,0,one};\n\
    \        bwb={rt1[1],0,rt1[0],0,mod-mul_s(rt1[0],rt1[1],niv,mod)};\n        bwbi={rt1i[1],0,rt1i[0],0,mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        u32 pr=one,pri=one;\n        for(int i=0;i<k-2;++i){\n            const\
    \ u32 r=mul_s(pr,rt1[i+1],niv,mod),ri=mul_s(pri,rt1i[i+1],niv,mod);\n        \
    \    const u32 r2=mul_s(r,r,niv,mod),r2i=mul_s(ri,ri,niv,mod);\n            const\
    \ u32 r3=mul_s(r,r2,niv,mod),r3i=mul_s(ri,r2i,niv,mod);\n            rt3[i]={r*niv,r,r2*niv,r2,r3*niv,r3};\n\
    \            rt3i[i]={ri*niv,ri,r2i*niv,r2i,r3i*niv,r3i};\n            pr=mul(pr,rt1i[i+1],niv,mod),pri=mul(pri,rt1[i+1],niv,mod);\n\
    \        }\n        pr=one,pri=one;\n        for(int i=0;i<k-3;++i){\n       \
    \     const u32 r=mul_s(pr,rt1[i+2],niv,mod),ri=mul_s(pri,rt1i[i+2],niv,mod);\n\
    \            rt4[i][0]=rt4i[i][0]=one;\n            for(int j=1;j<8;++j){\n  \
    \              rt4[i][j]=mul_s(rt4[i][j-1],r,niv,mod);\n                rt4i[i][j]=mul_s(rt4i[i][j-1],ri,niv,mod);\n\
    \            }\n            for(int j=0;j<8;++j){\n                rt4niv[i][j]=rt4[i][j]*niv;\n\
    \                rt4iniv[i][j]=rt4i[i][j]*niv;\n            }\n            pr=mul(pr,rt1i[i+2],niv,mod),pri=mul(pri,rt1[i+2],niv,mod);\n\
    \        }\n        pr2={one,one,one,img,one,one,one,img};\n        pr4={one,one,one,one,one,rt1[1],img,mul_s(img,rt1[1],niv,mod)};\n\
    \        const u32 nr2=mod-r2,imgr2=mul_s(img,r2,niv,mod);\n        pr2i={nr2,nr2,nr2,imgr2,nr2,nr2,nr2,imgr2};\n\
    \        pr4i={one,one,one,one,one,rt1i[1],rt1i[0],mul_s(rt1i[0],rt1i[1],niv,mod)};\n\
    \        for(int j=0;j<8;++j){\n            pr2niv[j]=pr2[j]*niv,pr4niv[j]=pr4[j]*niv;\n\
    \            pr2iniv[j]=pr2i[j]*niv,pr4iniv[j]=pr4i[j]*niv;\n        }\n    }\n\
    };\ninline void vector_dif(I256*const f,const idt n,const FNTT32_info*info){\n\
    \    alignas(32) std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(lgn>>1),info->bwb);\n\
    \    const idt nn=n>>(lgn&1),m=std::min(n,_itth),mm=std::min(nn,_itth);\n    //\
    \ I256 rr=_mm256_set1_epi32(info->one);\n    if(nn!=n){\n        for(idt i=0;i<nn;++i){\n\
    \            auto const p0=f+i,p1=f+nn+i;\n            const auto f0=load256(p0),f1=load256(p1);\n\
    \            const auto g0=add32(f0,f1,Mod2),g1=Lsub32(f0,f1,Mod2);\n        \
    \    store256(p0,g0),store256(p1,g1);\n        }\n    }\n    for(idt L=nn>>2;L>0;L>>=2){\n\
    \        for(idt i=0;i<L;++i){\n            auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \            const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \            const auto g3=mul_bsmfxd(Lsub32(f1,f3,Mod2),Img,ImgNiv,Mod),g1=add32(f1,f3,Mod2);\n\
    \            const auto g0=add32(f0,f2,Mod2),g2=sub32(f0,f2,Mod2);\n         \
    \   const auto h0=add32(g0,g1,Mod2),h1=Lsub32(g0,g1,Mod2);\n            const\
    \ auto h2=Ladd32(g2,g3,Mod2),h3=Lsub32(g2,g3,Mod2);\n            store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \        }\n    }\n    for(idt j=0;j<n;j+=m){\n        int t=((j==0)?std::min(_lg_itth,lgn):__builtin_ctzll(j))&-2,p=(t-2)>>1;\n\
    \        for(idt L=(idt(1)<<t)>>2;L>=_itth;L>>=2,t-=2,--p){\n            auto\
    \ rt=load256(st_1+p);\n            const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \            const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \            rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~j>>t)),Mod);\n\
    \            const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \            const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),nr3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \            store256(st_1+p,rt);\n            for(idt i=0;i<L;++i){\n       \
    \         auto const p0=f+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n                const\
    \ auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n        \
    \        const auto g1=mul_bsmfxd(f1,r1,r1Niv,Mod),ng3=mul_bsmfxd(f3,nr3,nr3Niv,Mod);\n\
    \                const auto g2=mul_bsmfxd(f2,r2,r2Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n     \
    \           const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n        \
    \        const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n           \
    \     store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n     \
    \       }\n        }\n        I256*const g=f+j;\n        for(idt l=mm,L=mm>>2;L;l=L,L>>=2,t-=2,--p){\n\
    \            auto rt=load256(st_1+p);\n            for(idt i=(j==0?l:0),k=(j+i)>>t;i<m;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto nr3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f1=load256(p1),f3=load256(p3),f2=load256(p2),f0=load256(p0);\n\
    \                    const auto g1=mul_bsm(f1,r1,Niv,Mod),ng3=mul_bsm(f3,nr3,Niv,Mod);\n\
    \                    const auto g2=mul_bsm(f2,r2,Niv,Mod),g0=shrk32(f0,Mod2);\n\
    \                    const auto h3=mul_bsmfxd(Ladd32(g1,ng3,Mod2),Img,ImgNiv,Mod),h1=sub32(g1,ng3,Mod2);\n\
    \                    const auto h0=add32(g0,g2,Mod2),h2=sub32(g0,g2,Mod2);\n \
    \                   const auto u0=Ladd32(h0,h1,Mod2),u1=Lsub32(h0,h1,Mod2);\n\
    \                    const auto u2=Ladd32(h2,h3,Mod2),u3=Lsub32(h2,h3,Mod2);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        // const\
    \ auto pr2=load256(&info->pr2),pr4=load256(&info->pr4);\n        // const auto\
    \ pr2Niv=load256(&info->pr2niv),pr4Niv=load256(&info->pr4niv);\n        // for(idt\
    \ i=j;i<j+m;++i){\n        //     auto fi=load256(f+i);\n        //     fi=mul(fi,rr,Niv,Mod);\n\
    \        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4+__builtin_ctzll(~i)),load256(info->rt4niv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=sub32(_mm256_shuffle_epi32(fi,0xb1),neg32_m<0x55>(fi,Mod2),Mod2);\n\
    \        //     store256(f+i,fi);\n        // }\n    }\n}\ntemplate<bool shrk=false>inline\
    \ void vector_dit(I256*const f,idt n,const FNTT32_info*const info){\n    alignas(32)\
    \ std::array<u32,8> st_1[_mxlg>>1];\n    const I256 Mod=_mm256_set1_epi32(info->mod),Mod2=_mm256_set1_epi32(info->mod2),Niv=_mm256_set1_epi32(info->niv);\n\
    \    const I256 Img=_mm256_set1_epi32(info->img),ImgNiv=_mm256_set1_epi32(info->imgniv),id=_mm256_setr_epi32(0,2,0,4,0,2,0,4);\n\
    \    const int lgn=__builtin_ctzll(n);\n    std::fill(st_1,st_1+(_lg_itth>>1),info->bwbr);\n\
    \    std::fill(st_1+(_lg_itth>>1),st_1+(_mxlg>>1),info->bwbi);\n    const idt\
    \ nn=n>>(lgn&1),mm=std::min(nn,_itth);\n    // I256 rr=_mm256_set1_epi32((info->mod-1)>>(lgn+3));\n\
    \    for(idt j=0;j<n;j+=mm){\n        // const auto pr2=load256(&info->pr2i),pr4=load256(&info->pr4i);\n\
    \        // const auto pr2Niv=load256(&info->pr2iniv),pr4Niv=load256(&info->pr4iniv);\n\
    \        // for(idt i=j;i<j+mm;++i){\n        //     auto fi=load256(f+i);\n \
    \       //     const auto rt=rr;\n        //     rr=shrk32(mul_bfxd(rr,load256(info->rt4i+__builtin_ctzll(~i)),load256(info->rt4iniv+__builtin_ctzll(~i)),Mod),Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xaa>(fi,Mod2),_mm256_shuffle_epi32(fi,0xb1),Mod2),pr2,pr2Niv,Mod);\n\
    \        //     fi=mul_bfxd(Ladd32(neg32_m<0xcc>(fi,Mod2),_mm256_shuffle_epi32(fi,0x4e),Mod2),pr4,pr4Niv,Mod);\n\
    \        //     fi=mul(Ladd32(neg32_m<0xf0>(fi,Mod2),_mm256_permute2x128_si256(fi,fi,1),Mod2),rt,Niv,Mod);\n\
    \        //     store256(f+i,fi);\n        // }\n        I256*const g=f+j;\n \
    \       int t=2,p=0;\n        for(idt l=4,L=1;l<=mm;L=l,l<<=2,t+=2,++p){\n   \
    \         auto rt=load256(st_1+p);\n            for(idt i=0,k=j>>t;i<mm;i+=l,++k){\n\
    \                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n         \
    \       const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB);\n              \
    \  const auto r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n                for(idt\
    \ j=0;j<L;++j){\n                    auto const p0=g+i+j,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                    const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsm(h1,r1,Niv,Mod);\n\
    \                    const auto u2=mul_bsm(h2,r2,Niv,Mod),u3=mul_bsm(h3,r3,Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~k)),Mod);\n\
    \            }\n            store256(st_1+p,rt);\n        }\n        int tt=std::min(__builtin_ctzll(~(j>>_lg_itth))+_lg_itth,lgn);\n\
    \        for(idt L=_itth,l=L<<2;t<=tt;L=l,l<<=2,t+=2,++p){\n            if((j+_itth)==l){\n\
    \                if(shrk && l==n){\n                    for(idt i=0;i<L;++i){\n\
    \                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n        \
    \                const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        const auto u0=shrk32(h0,Mod),u1=shrk32(h1,Mod);\n   \
    \                     const auto u2=shrk32(h2,Mod),u3=shrk32(h3,Mod);\n      \
    \                  store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                    }\n                }\n                else{\n           \
    \         for(idt i=0;i<L;++i){\n                        auto const p0=f+i,p1=p0+L,p2=p1+L,p3=p2+L;\n\
    \                        const auto f2=load256(p2),f3=load256(p3),f0=load256(p0),f1=load256(p1);\n\
    \                        const auto g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod),g2=add32(f2,f3,Mod2);\n\
    \                        const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \                        const auto h0=add32(g0,g2,Mod2),h1=add32(g1,g3,Mod2);\n\
    \                        const auto h2=sub32(g0,g2,Mod2),h3=sub32(g1,g3,Mod2);\n\
    \                        store256(p0,h0),store256(p1,h1),store256(p2,h2),store256(p3,h3);\n\
    \                    }\n                }\n            }\n            else{\n\
    \                auto rt=load256(st_1+p);\n                const auto r1=_mm256_permutevar8x32_epi32(rt,id);\n\
    \                const auto r1Niv=_mm256_permutevar8x32_epi32(_mm256_mul_epu32(rt,Niv),id);\n\
    \                rt=mul_upd_rt(rt,load256(info->rt3i+__builtin_ctzll(~j>>t)),Mod);\n\
    \                const auto r2=_mm256_shuffle_epi32(r1,_MM_PERM_BBBB),r3=_mm256_shuffle_epi32(r1,_MM_PERM_DDDD);\n\
    \                const auto r2Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_BBBB),r3Niv=_mm256_shuffle_epi32(r1Niv,_MM_PERM_DDDD);\n\
    \                store256(st_1+p,rt);\n                for(idt i=0;i<L;++i){\n\
    \                    auto const p0=f+j+_itth-l+i,p1=p0+L,p2=p1+L,p3=p2+L;\n  \
    \                  const auto f0=load256(p0),f1=load256(p1),f2=load256(p2),f3=load256(p3);\n\
    \                    const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n \
    \                   const auto g2=add32(f2,f3,Mod2),g3=mul_bsmfxd(Lsub32(f3,f2,Mod2),Img,ImgNiv,Mod);\n\
    \                    const auto h0=Ladd32(g0,g2,Mod2),h1=Ladd32(g1,g3,Mod2);\n\
    \                    const auto h2=Lsub32(g0,g2,Mod2),h3=Lsub32(g1,g3,Mod2);\n\
    \                    const auto u0=shrk32(h0,Mod2),u1=mul_bsmfxd(h1,r1,r1Niv,Mod);\n\
    \                    const auto u2=mul_bsmfxd(h2,r2,r2Niv,Mod),u3=mul_bsmfxd(h3,r3,r3Niv,Mod);\n\
    \                    store256(p0,u0),store256(p1,u1),store256(p2,u2),store256(p3,u3);\n\
    \                }\n            }\n        }\n    }\n    if(shrk && nn==n && n<=_itth){\n\
    \        for(idt i=0;i<n;++i){\n            const auto f0=load256(f+i);\n    \
    \        store256(f+i,shrk32(f0,Mod));\n        }\n    }\n    if(nn!=n){\n   \
    \     for(idt i=0;i<nn;++i){\n            auto const p0=f+i,p1=f+nn+i;\n     \
    \       const auto f0=load256(p0),f1=load256(p1);\n            const auto g0=add32(f0,f1,Mod2),g1=sub32(f0,f1,Mod2);\n\
    \            if constexpr(shrk){\n                const auto h0=shrk32(g0,Mod),h1=shrk32(g1,Mod);\n\
    \                store256(p0,h0),store256(p1,h1);\n            }\n           \
    \ else{\n                store256(p0,g0),store256(p1,g1);\n            }\n   \
    \     }\n    }\n}\n// Returns fx * f[0,8) * g[0,8) (mod x^8 - ww).\n[[gnu::always_inline]]\
    \ inline I256 convolve8(const I256*f,const I256*g,I256 ww,I256 fx,I256 Niv,I256\
    \ Mod,I256 Mod2){\n    const auto raa=load256(f),rbb=load256(g);\n    const auto\
    \ taa=shrk32(raa,Mod2),bb=shrk32(mul_bsm(rbb,fx,Niv,Mod),Mod);\n    const auto\
    \ aw=shrk32(mul_bsm(taa,ww,Niv,Mod),Mod);\n    const auto aa=shrk32(taa,Mod);\n\
    \    const auto awa=_mm256_permute2x128_si256(aa,aw,3);\n    \n    const auto\
    \ b0=_mm256_permute4x64_epi64(bb,0x00),b1=_mm256_shuffle_epi32(b0,_MM_PERM_CDAB);\n\
    \    const auto a0=aa,a1=_mm256_srli_epi64(a0,32);\n    const auto aw7=_mm256_alignr_epi8(aa,awa,12);\n\
    \    auto res00=_mm256_mul_epu32(a0,b0);\n    auto res01=_mm256_mul_epu32(a1,b0);\n\
    \    auto res10=_mm256_mul_epu32(aw7,b1);\n    auto res11=_mm256_mul_epu32(a0,b1);\n\
    \n    const auto b2=_mm256_permute4x64_epi64(bb,0x55),b3=_mm256_shuffle_epi32(b2,_MM_PERM_CDAB);\n\
    \    const auto aw6=_mm256_alignr_epi8(aa,awa,8);\n    const auto aw5=_mm256_alignr_epi8(aa,awa,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw6,b2));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw7,b2));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw5,b3));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw6,b3));\n\
    \n    const auto b4=_mm256_permute4x64_epi64(bb,0xaa),b5=_mm256_shuffle_epi32(b4,_MM_PERM_CDAB);\n\
    \    const auto aw3=_mm256_alignr_epi8(awa,aw,12);\n    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(awa,b4));\n\
    \    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw5,b4));\n    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw3,b5));\n\
    \    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(awa,b5));\n\n    const auto\
    \ b6=_mm256_permute4x64_epi64(bb,0xff),b7=_mm256_shuffle_epi32(b6,_MM_PERM_CDAB);\n\
    \    const auto aw2=_mm256_alignr_epi8(awa,aw,8);\n    const auto aw1=_mm256_alignr_epi8(awa,aw,4);\n\
    \    res00=_mm256_add_epi64(res00,_mm256_mul_epu32(aw2,b6));\n    res01=_mm256_add_epi64(res01,_mm256_mul_epu32(aw3,b6));\n\
    \    res10=_mm256_add_epi64(res10,_mm256_mul_epu32(aw1,b7));\n    res11=_mm256_add_epi64(res11,_mm256_mul_epu32(aw2,b7));\n\
    \n    res00=_mm256_add_epi64(res00,res10);\n    res01=_mm256_add_epi64(res01,res11);\n\
    \n    return shrk32(reduce(res00,res01,Niv,Mod),Mod2);\n}\ninline void vector_convolution_direct(I256*f,const\
    \ I256*g,idt lm,const FNTT32_info*const info){\n    u32 RR=info->one;\n    const\
    \ auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        store256(f+i,convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2));\n\
    \        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n    }\n}\ninline\
    \ void vector_convolution_accumulate(I256*const result,const I256*const f,\n \
    \                                         const I256*const g,idt lm,\n       \
    \                                   const FNTT32_info*const info){\n    u32 RR=info->one;\n\
    \    const auto mod=info->mod,niv=info->niv;\n    const auto Fx=_mm256_set1_epi32(mul_s((mod-((mod-1)>>(__builtin_ctzll(lm)))),info->r3,niv,mod));\n\
    \    const auto Niv=_mm256_set1_epi32(niv),Mod=_mm256_set1_epi32(mod),Mod2=_mm256_set1_epi32(info->mod2);\n\
    \    for(idt i=0;i<lm;++i){\n        const auto product=convolve8(f+i,g+i,_mm256_set1_epi32(RR),Fx,Niv,Mod,Mod2);\n\
    \        store256(result+i,add32(load256(result+i),product,Mod2));\n        RR=mul(RR,info->RT1[__builtin_ctzll(~i)],niv,mod);\n\
    \    }\n}\n\n}  // namespace fast998_v2\n}  // namespace internal\n}  // namespace\
    \ fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_HAS_X86_SIMD\n\n\n#line 22\
    \ \"math/fps/convolution.hpp\"\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n#pragma GCC pop_options\n\
    #endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 9 \"math/modint.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n\
    \    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
    \    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod() {\n     \
    \   return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept\
    \ {\n        ModInt x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr\
    \ ModInt() noexcept : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
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
    \ math\n}  // namespace m1une\n\n\n#line 27 \"math/fps/convolution.hpp\"\n\nnamespace\
    \ m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class Mint, class\
    \ = void>\nstruct has_static_modulus : std::false_type {};\n\ntemplate <class\
    \ Mint>\nstruct has_static_modulus<\n    Mint, std::void_t<decltype(std::integral_constant<uint32_t,\
    \ Mint::mod()>{})>>\n    : std::true_type {};\n\nconstexpr uint32_t primitive_root_constexpr(uint32_t\
    \ mod) {\n    if (mod == 2) return 1;\n    if (mod == 167772161) return 3;\n \
    \   if (mod == 469762049) return 3;\n    if (mod == 754974721) return 11;\n  \
    \  if (mod == 998244353) return 3;\n    if (mod == 1224736769) return 3;\n\n \
    \   uint32_t divisors[32] = {};\n    int count = 0;\n    uint32_t x = mod - 1;\n\
    \    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {\n        if (x % p != 0)\
    \ continue;\n        divisors[count++] = p;\n        while (x % p == 0) x /= p;\n\
    \    }\n    if (x > 1) divisors[count++] = x;\n\n    for (uint32_t g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < count; i++) {\n    \
    \        uint64_t value = 1;\n            uint64_t base = g;\n            uint32_t\
    \ exponent = (mod - 1) / divisors[i];\n            while (exponent > 0) {\n  \
    \              if (exponent & 1) value = value * base % mod;\n               \
    \ base = base * base % mod;\n                exponent >>= 1;\n            }\n\
    \            if (value == 1) {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n}\n\nconstexpr int\
    \ two_adic_order(uint32_t x) {\n    int result = 0;\n    while ((x & 1) == 0)\
    \ {\n        x >>= 1;\n        result++;\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstruct NttRoots {\n    static constexpr int max_base = two_adic_order(Mint::mod()\
    \ - 1);\n    std::array<Mint, max_base + 1> root;\n    std::array<Mint, max_base\
    \ + 1> inverse_root;\n    std::array<Mint, max_base> rate;\n    std::array<Mint,\
    \ max_base> inverse_rate;\n    std::array<Mint, max_base> rate_radix4;\n    std::array<Mint,\
    \ max_base> inverse_rate_radix4;\n\n    NttRoots() {\n        constexpr uint32_t\
    \ primitive_root = primitive_root_constexpr(Mint::mod());\n        for (int level\
    \ = 1; level <= max_base; level++) {\n            root[level] = Mint(primitive_root).pow((Mint::mod()\
    \ - 1) >> level);\n            inverse_root[level] = root[level].inv();\n    \
    \    }\n        Mint product = 1;\n        Mint inverse_product = 1;\n       \
    \ for (int i = 0; i + 1 < max_base; i++) {\n            rate[i] = root[i + 2]\
    \ * product;\n            inverse_rate[i] = inverse_root[i + 2] * inverse_product;\n\
    \            product *= inverse_root[i + 2];\n            inverse_product *= root[i\
    \ + 2];\n        }\n        product = 1;\n        inverse_product = 1;\n     \
    \   for (int i = 0; i + 2 < max_base; i++) {\n            rate_radix4[i] = root[i\
    \ + 3] * product;\n            inverse_rate_radix4[i] = inverse_root[i + 3] *\
    \ inverse_product;\n            product *= inverse_root[i + 3];\n            inverse_product\
    \ *= root[i + 3];\n        }\n    }\n};\n\ntemplate <class Mint>\nconst NttRoots<Mint>&\
    \ ntt_roots() {\n    static const NttRoots<Mint> roots;\n    return roots;\n}\n\
    \ntemplate <class Mint>\nvoid ntt(std::vector<Mint>& a, bool inverse, bool normalize\
    \ = true) {\n    const int n = int(a.size());\n    assert(n > 0 && (n & (n - 1))\
    \ == 0);\n    assert((Mint::mod() - 1) % uint32_t(n) == 0);\n\n    const auto&\
    \ roots = ntt_roots<Mint>();\n    const int height = two_adic_order(uint32_t(n));\n\
    \    if (!inverse) {\n        int phase = 0;\n        while (phase < height) {\n\
    \            if (height - phase == 1) {\n                const int width = 1 <<\
    \ (height - phase - 1);\n                Mint twiddle = 1;\n                for\
    \ (int block = 0; block < (1 << phase); block++) {\n                    const\
    \ int offset = block << (height - phase);\n                    for (int i = 0;\
    \ i < width; i++) {\n                        const Mint left = a[offset + i];\n\
    \                        const Mint right = a[offset + i + width] * twiddle;\n\
    \                        a[offset + i] = left + right;\n                     \
    \   a[offset + i + width] = left - right;\n                    }\n           \
    \         if (block + 1 != (1 << phase))\n                        twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase++;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase - 2);\n     \
    \       Mint twiddle = 1;\n            const Mint imaginary = roots.root[2];\n\
    \            for (int block = 0; block < (1 << phase); block++) {\n          \
    \      const Mint twiddle2 = twiddle * twiddle;\n                const Mint twiddle3\
    \ = twiddle2 * twiddle;\n                const int offset = block << (height -\
    \ phase);\n                for (int i = 0; i < width; i++) {\n               \
    \     const uint64_t mod2 = uint64_t(Mint::mod()) * Mint::mod();\n           \
    \         const uint64_t a0 = a[offset + i].val();\n                    const\
    \ uint64_t a1 = uint64_t(a[offset + i + width].val()) * twiddle.val();\n     \
    \               const uint64_t a2 =\n                        uint64_t(a[offset\
    \ + i + 2 * width].val()) * twiddle2.val();\n                    const uint64_t\
    \ a3 =\n                        uint64_t(a[offset + i + 3 * width].val()) * twiddle3.val();\n\
    \                    const uint64_t a1na3i =\n                        uint64_t(Mint(a1\
    \ + mod2 - a3).val()) * imaginary.val();\n                    const uint64_t negative_a2\
    \ = mod2 - a2;\n                    a[offset + i] = Mint(a0 + a2 + a1 + a3);\n\
    \                    a[offset + i + width] = Mint(a0 + a2 + 2 * mod2 - a1 - a3);\n\
    \                    a[offset + i + 2 * width] = Mint(a0 + negative_a2 + a1na3i);\n\
    \                    a[offset + i + 3 * width] = Mint(a0 + negative_a2 + mod2\
    \ - a1na3i);\n                }\n                if (block + 1 != (1 << phase))\n\
    \                    twiddle *= roots.rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase += 2;\n        }\n    } else {\n        int\
    \ phase = height;\n        while (phase > 0) {\n            if (phase == 1) {\n\
    \                const int width = 1 << (height - phase);\n                Mint\
    \ twiddle = 1;\n                for (int block = 0; block < (1 << (phase - 1));\
    \ block++) {\n                    const int offset = block << (height - phase\
    \ + 1);\n                    for (int i = 0; i < width; i++) {\n             \
    \           const Mint left = a[offset + i];\n                        const Mint\
    \ right = a[offset + i + width];\n                        a[offset + i] = left\
    \ + right;\n                        a[offset + i + width] = (left - right) * twiddle;\n\
    \                    }\n                    if (block + 1 != (1 << (phase - 1)))\n\
    \                        twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];\n\
    \                }\n                phase--;\n                continue;\n    \
    \        }\n\n            const int width = 1 << (height - phase);\n         \
    \   Mint twiddle = 1;\n            const Mint inverse_imaginary = roots.inverse_root[2];\n\
    \            for (int block = 0; block < (1 << (phase - 2)); block++) {\n    \
    \            const Mint twiddle2 = twiddle * twiddle;\n                const Mint\
    \ twiddle3 = twiddle2 * twiddle;\n                const int offset = block <<\
    \ (height - phase + 2);\n                for (int i = 0; i < width; i++) {\n \
    \                   const uint64_t a0 = a[offset + i].val();\n               \
    \     const uint64_t a1 = a[offset + i + width].val();\n                    const\
    \ uint64_t a2 = a[offset + i + 2 * width].val();\n                    const uint64_t\
    \ a3 = a[offset + i + 3 * width].val();\n                    const uint64_t a2na3i\
    \ =\n                        uint64_t(Mint((Mint::mod() + a2 - a3) * inverse_imaginary.val()).val());\n\
    \                    a[offset + i] = Mint(a0 + a1 + a2 + a3);\n              \
    \      a[offset + i + width] =\n                        Mint((a0 + Mint::mod()\
    \ - a1 + a2na3i) * twiddle.val());\n                    a[offset + i + 2 * width]\
    \ = Mint(\n                        (a0 + a1 + 2ULL * Mint::mod() - a2 - a3) *\
    \ twiddle2.val());\n                    a[offset + i + 3 * width] = Mint(\n  \
    \                      (a0 + Mint::mod() - a1 + Mint::mod() - a2na3i) * twiddle3.val());\n\
    \                }\n                if (block + 1 != (1 << (phase - 2)))\n   \
    \                 twiddle *= roots.inverse_rate_radix4[__builtin_ctz(~uint32_t(block))];\n\
    \            }\n            phase -= 2;\n        }\n        if (normalize) {\n\
    \            const Mint inverse_n = Mint(n).inv();\n            for (Mint& value\
    \ : a) value *= inverse_n;\n        }\n    }\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \n#pragma GCC push_options\n#pragma GCC target(\"avx2,bmi\")\n\ntemplate <class\
    \ Mint>\n__attribute__((target(\"avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_simd(const\
    \ std::vector<Mint>& a,\n                                             const std::vector<Mint>&\
    \ b) {\n    const int result_size = int(a.size() + b.size() - 1);\n    int n =\
    \ 1;\n    while (n < result_size) n <<= 1;\n    const bool squaring = &a == &b;\n\
    \    auto* transformed_a = static_cast<uint32_t*>(\n        ::operator new[](sizeof(uint32_t)\
    \ * n, std::align_val_t(32)));\n    auto* transformed_b = squaring\n         \
    \                     ? transformed_a\n                              : static_cast<uint32_t*>(::operator\
    \ new[](\n                                    sizeof(uint32_t) * n, std::align_val_t(32)));\n\
    \    if constexpr (std::is_same_v<Mint, math::ModInt<998244353>>) {\n        static_assert(sizeof(Mint)\
    \ == sizeof(uint32_t) && std::is_trivially_copyable_v<Mint>);\n        std::memcpy(transformed_a,\
    \ a.data(), sizeof(uint32_t) * a.size());\n        if (!squaring)\n          \
    \  std::memcpy(transformed_b, b.data(), sizeof(uint32_t) * b.size());\n    } else\
    \ {\n        for (int i = 0; i < int(a.size()); i++) transformed_a[i] = a[i].val();\n\
    \        if (!squaring)\n            for (int i = 0; i < int(b.size()); i++) transformed_b[i]\
    \ = b[i].val();\n    }\n    std::memset(transformed_a + a.size(), 0, sizeof(uint32_t)\
    \ * (n - a.size()));\n    if (!squaring)\n        std::memset(transformed_b +\
    \ b.size(), 0, sizeof(uint32_t) * (n - b.size()));\n\n    static constexpr fast998_v2::FNTT32_info\
    \ transform(998244353);\n    const std::size_t vector_size = std::size_t(n) >>\
    \ 3;\n    fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_a), vector_size,\
    \ &transform);\n    if (!squaring)\n        fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed_b),\
    \ vector_size,\n                              &transform);\n    fast998_v2::vector_convolution_direct(\n\
    \        reinterpret_cast<__m256i*>(transformed_a),\n        reinterpret_cast<const\
    \ __m256i*>(transformed_b), vector_size, &transform);\n    fast998_v2::vector_dit<true>(reinterpret_cast<__m256i*>(transformed_a),\
    \ vector_size,\n                                 &transform);\n\n    std::vector<Mint>\
    \ result(result_size);\n    for (int j = 0; j < result_size; j++) result[j] =\
    \ Mint::raw(transformed_a[j]);\n    ::operator delete[](transformed_a, std::align_val_t(32));\n\
    \    if (!squaring) ::operator delete[](transformed_b, std::align_val_t(32));\n\
    \    return result;\n}\n\n#pragma GCC pop_options\n\n#endif\n\n}  // namespace\
    \ internal\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_naive(const\
    \ std::vector<Mint>& a, const std::vector<Mint>& b) {\n    if (a.empty() || b.empty())\
    \ return {};\n    std::vector<Mint> result(a.size() + b.size() - 1);\n    if (a.size()\
    \ < b.size()) {\n        for (int i = 0; i < int(a.size()); i++) {\n         \
    \   for (int j = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];\n  \
    \      }\n    } else {\n        for (int j = 0; j < int(b.size()); j++) {\n  \
    \          for (int i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];\n\
    \        }\n    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>& b) {\n\
    \    const int result_size = int(a.size() + b.size() - 1);\n    int n = 1;\n \
    \   while (n < result_size) n <<= 1;\n    assert((Mint::mod() - 1) % uint32_t(n)\
    \ == 0);\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if constexpr (Mint::mod() == 998244353)\
    \ {\n        if (n >= 64 && __builtin_cpu_supports(\"avx2\"))\n            return\
    \ internal::convolution_998244353_simd(a, b);\n    }\n#endif\n\n    // Allocate\
    \ the padded buffers directly.  Constructing from the inputs and\n    // then\
    \ resizing used to allocate and copy both large operands twice.\n    const bool\
    \ squaring = &a == &b;\n    std::vector<Mint> fa(n);\n    std::copy(a.begin(),\
    \ a.end(), fa.begin());\n    internal::ntt(fa, false);\n    const Mint inverse_n\
    \ = Mint(n).inv();\n    if (squaring) {\n        for (int i = 0; i < n; i++) fa[i]\
    \ *= fa[i] * inverse_n;\n    } else {\n        std::vector<Mint> fb(n);\n    \
    \    std::copy(b.begin(), b.end(), fb.begin());\n        internal::ntt(fb, false);\n\
    \        for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;\n    }\n    internal::ntt(fa,\
    \ true, false);\n    fa.resize(result_size);\n    return fa;\n}\n\nnamespace internal\
    \ {\n\ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked_scalar(const\
    \ std::vector<Mint>& a,\n                                                    \
    \   const std::vector<Mint>& b,\n                                            \
    \           int transform_size) {\n    assert(Mint::mod() == 998244353);\n   \
    \ assert(transform_size >= 2 && (transform_size & (transform_size - 1)) == 0);\n\
    \    assert((Mint::mod() - 1) % uint32_t(transform_size) == 0);\n\n    const int\
    \ block_size = transform_size / 2;\n    const int a_blocks = int((a.size() + block_size\
    \ - 1) / block_size);\n    const int b_blocks = int((b.size() + block_size - 1)\
    \ / block_size);\n\n    auto transform_blocks = [&](const std::vector<Mint>& values,\
    \ int block_count) {\n        std::vector<std::vector<Mint>> blocks;\n       \
    \ blocks.reserve(block_count);\n        for (int block = 0; block < block_count;\
    \ block++) {\n            const int begin = block * block_size;\n            const\
    \ int count = std::min(block_size, int(values.size()) - begin);\n            std::vector<Mint>\
    \ transformed(transform_size);\n            std::copy_n(values.begin() + begin,\
    \ count, transformed.begin());\n            ntt(transformed, false);\n       \
    \     blocks.emplace_back(std::move(transformed));\n        }\n        return\
    \ blocks;\n    };\n\n    std::vector<std::vector<Mint>> transformed_a = transform_blocks(a,\
    \ a_blocks);\n    std::vector<std::vector<Mint>> transformed_b = transform_blocks(b,\
    \ b_blocks);\n    const int result_size = int(a.size() + b.size() - 1);\n    std::vector<Mint>\
    \ result(result_size);\n    std::vector<Mint> transformed_result(transform_size);\n\
    \    for (int diagonal = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n\
    \        std::fill(transformed_result.begin(), transformed_result.end(), Mint(0));\n\
    \        const int first_a = std::max(0, diagonal - (b_blocks - 1));\n       \
    \ const int last_a = std::min(a_blocks - 1, diagonal);\n        for (int a_block\
    \ = first_a; a_block <= last_a; a_block++) {\n            const int b_block =\
    \ diagonal - a_block;\n            for (int i = 0; i < transform_size; i++)\n\
    \                transformed_result[i] +=\n                    transformed_a[a_block][i]\
    \ * transformed_b[b_block][i];\n        }\n        ntt(transformed_result, true);\n\
    \n        const int output_offset = diagonal * block_size;\n        const int\
    \ output_count = std::min(transform_size, result_size - output_offset);\n    \
    \    for (int i = 0; i < output_count; i++)\n            result[output_offset\
    \ + i] += transformed_result[i];\n    }\n    return result;\n}\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    \nclass AlignedUint32Buffer {\n   private:\n    uint32_t* data_;\n\n   public:\n\
    \    explicit AlignedUint32Buffer(std::size_t size)\n        : data_(static_cast<uint32_t*>(\n\
    \              ::operator new[](sizeof(uint32_t) * size, std::align_val_t(32))))\
    \ {}\n\n    AlignedUint32Buffer(const AlignedUint32Buffer&) = delete;\n    AlignedUint32Buffer&\
    \ operator=(const AlignedUint32Buffer&) = delete;\n\n    AlignedUint32Buffer(AlignedUint32Buffer&&\
    \ other) noexcept : data_(other.data_) {\n        other.data_ = nullptr;\n   \
    \ }\n\n    AlignedUint32Buffer& operator=(AlignedUint32Buffer&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        ::operator delete[](data_,\
    \ std::align_val_t(32));\n        data_ = other.data_;\n        other.data_ =\
    \ nullptr;\n        return *this;\n    }\n\n    ~AlignedUint32Buffer() {\n   \
    \     ::operator delete[](data_, std::align_val_t(32));\n    }\n\n    uint32_t*\
    \ data() {\n        return data_;\n    }\n\n    const uint32_t* data() const {\n\
    \        return data_;\n    }\n};\n\ntemplate <class Mint>\n__attribute__((target(\"\
    avx2,bmi\"), hot))\nstd::vector<Mint> convolution_998244353_blocked_simd(const\
    \ std::vector<Mint>& a,\n                                                    \
    \ const std::vector<Mint>& b,\n                                              \
    \       int transform_size) {\n    assert(Mint::mod() == 998244353);\n    assert(transform_size\
    \ >= 64 && (transform_size & (transform_size - 1)) == 0);\n    assert((Mint::mod()\
    \ - 1) % uint32_t(transform_size) == 0);\n\n    const int block_size = transform_size\
    \ / 2;\n    const int a_blocks = int((a.size() + block_size - 1) / block_size);\n\
    \    const int b_blocks = int((b.size() + block_size - 1) / block_size);\n   \
    \ static constexpr fast998_v2::FNTT32_info transform(998244353);\n    const std::size_t\
    \ vector_size = std::size_t(transform_size) / 8;\n\n    auto transform_blocks\
    \ = [&](const std::vector<Mint>& values, int block_count) {\n        std::vector<AlignedUint32Buffer>\
    \ blocks;\n        blocks.reserve(block_count);\n        for (int block = 0; block\
    \ < block_count; block++) {\n            const int begin = block * block_size;\n\
    \            const int count = std::min(block_size, int(values.size()) - begin);\n\
    \            AlignedUint32Buffer transformed(transform_size);\n            if\
    \ constexpr (std::is_same_v<Mint, math::ModInt<998244353>>) {\n              \
    \  static_assert(sizeof(Mint) == sizeof(uint32_t) &&\n                       \
    \       std::is_trivially_copyable_v<Mint>);\n                std::memcpy(transformed.data(),\
    \ values.data() + begin,\n                            sizeof(uint32_t) * count);\n\
    \            } else {\n                for (int i = 0; i < count; i++)\n     \
    \               transformed.data()[i] = values[begin + i].val();\n           \
    \ }\n            std::memset(transformed.data() + count, 0,\n                \
    \        sizeof(uint32_t) * (transform_size - count));\n            fast998_v2::vector_dif(reinterpret_cast<__m256i*>(transformed.data()),\n\
    \                                   vector_size, &transform);\n            blocks.emplace_back(std::move(transformed));\n\
    \        }\n        return blocks;\n    };\n\n    std::vector<AlignedUint32Buffer>\
    \ transformed_a = transform_blocks(a, a_blocks);\n    std::vector<AlignedUint32Buffer>\
    \ transformed_b = transform_blocks(b, b_blocks);\n    const int result_size =\
    \ int(a.size() + b.size() - 1);\n    std::vector<Mint> result(result_size);\n\
    \    AlignedUint32Buffer transformed_result(transform_size);\n    for (int diagonal\
    \ = 0; diagonal < a_blocks + b_blocks - 1; diagonal++) {\n        std::memset(transformed_result.data(),\
    \ 0, sizeof(uint32_t) * transform_size);\n        const int first_a = std::max(0,\
    \ diagonal - (b_blocks - 1));\n        const int last_a = std::min(a_blocks -\
    \ 1, diagonal);\n        for (int a_block = first_a; a_block <= last_a; a_block++)\
    \ {\n            const int b_block = diagonal - a_block;\n            fast998_v2::vector_convolution_accumulate(\n\
    \                reinterpret_cast<__m256i*>(transformed_result.data()),\n    \
    \            reinterpret_cast<const __m256i*>(transformed_a[a_block].data()),\n\
    \                reinterpret_cast<const __m256i*>(transformed_b[b_block].data()),\n\
    \                vector_size, &transform);\n        }\n        fast998_v2::vector_dit<true>(\n\
    \            reinterpret_cast<__m256i*>(transformed_result.data()), vector_size,\n\
    \            &transform);\n\n        const int output_offset = diagonal * block_size;\n\
    \        const int output_count = std::min(transform_size, result_size - output_offset);\n\
    \        for (int i = 0; i < output_count; i++) {\n            uint32_t value\
    \ = result[output_offset + i].val() + transformed_result.data()[i];\n        \
    \    if (value >= Mint::mod()) value -= Mint::mod();\n            result[output_offset\
    \ + i] = Mint::raw(value);\n        }\n    }\n    return result;\n}\n\n#endif\n\
    \ntemplate <class Mint>\nstd::vector<Mint> convolution_998244353_blocked(const\
    \ std::vector<Mint>& a,\n                                                const\
    \ std::vector<Mint>& b,\n                                                int transform_size\
    \ = 1 << 23) {\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n    if (transform_size >= 64 &&\
    \ __builtin_cpu_supports(\"avx2\"))\n        return convolution_998244353_blocked_simd(a,\
    \ b, transform_size);\n#endif\n    return convolution_998244353_blocked_scalar(a,\
    \ b, transform_size);\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>&\
    \ b) {\n    if (a.empty() || b.empty()) return {};\n    if (std::min(a.size(),\
    \ b.size()) <= 32) return convolution_naive(a, b);\n\n    const int result_size\
    \ = int(a.size() + b.size() - 1);\n    int n = 1;\n    while (n < result_size)\
    \ n <<= 1;\n    if constexpr (internal::has_static_modulus<Mint>::value) {\n \
    \       if constexpr (Mint::mod() == 998244353) {\n            if (n > (1 << 23))\n\
    \                return internal::convolution_998244353_blocked(a, b);\n     \
    \   }\n        if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a,\
    \ b);\n    }\n\n    using Mint1 = math::ModInt<167772161>;\n    using Mint2 =\
    \ math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n    assert(n\
    \ <= (1 << 24));\n\n    [[maybe_unused]] const unsigned __int128 coefficient_bound\
    \ =\n        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod()\
    \ - 1) *\n        (Mint::mod() - 1);\n    [[maybe_unused]] const unsigned __int128\
    \ crt_modulus =\n        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod()\
    \ * Mint3::mod();\n    assert(coefficient_bound < crt_modulus);\n\n    auto converted_convolution\
    \ = [&]<class OtherMint>() {\n        std::vector<OtherMint> converted_a(a.size());\n\
    \        std::vector<OtherMint> converted_b(b.size());\n        for (int i = 0;\
    \ i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());\n        for\
    \ (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());\n\
    \        return convolution_ntt(converted_a, converted_b);\n    };\n    std::vector<Mint1>\
    \ c1 = converted_convolution.template operator()<Mint1>();\n    std::vector<Mint2>\
    \ c2 = converted_convolution.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ c3 = converted_convolution.template operator()<Mint3>();\n    static const uint64_t\
    \ inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();\n    static const uint64_t\
    \ mod1_mod3 = Mint1::mod() % Mint3::mod();\n    static const uint64_t mod1_mod2_mod3\
    \ =\n        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();\n    static\
    \ const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();\n\
    \n    const uint64_t target_mod = Mint::mod();\n    const uint64_t mod1_target\
    \ = Mint1::mod() % target_mod;\n    const uint64_t mod1_mod2_target = mod1_target\
    \ * (Mint2::mod() % target_mod) % target_mod;\n    std::vector<Mint> result(result_size);\n\
    \    for (int i = 0; i < result_size; i++) {\n        const uint64_t r1 = c1[i].val();\n\
    \        const uint64_t r2 = c2[i].val();\n        const uint64_t r3 = c3[i].val();\n\
    \        const uint64_t first =\n            (r2 + Mint2::mod() - r1 % Mint2::mod())\
    \ % Mint2::mod() * inverse_mod1_mod2 %\n            Mint2::mod();\n        const\
    \ uint64_t combined_mod3 =\n            (r1 % Mint3::mod() + mod1_mod3 * (first\
    \ % Mint3::mod())) % Mint3::mod();\n        const uint64_t second =\n        \
    \    (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3\
    \ %\n            Mint3::mod();\n\n        uint64_t value = r1 % target_mod;\n\
    \        value = (value + mod1_target * (first % target_mod)) % target_mod;\n\
    \        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;\n\
    \        result[i] = Mint::raw(uint32_t(value));\n    }\n    return result;\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n#ifdef M1UNE_FPS_HAS_X86_SIMD\n\
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 18 \"utilities/bigint.hpp\"\n\
    \nnamespace m1une {\nnamespace utilities {\n\nstruct BigInt {\n    static constexpr\
    \ int BASE = 1000000000;\n    static constexpr int BASE_DIGITS = 9;\n\n    std::vector<int>\
    \ a;\n    int sign;\n\n    BigInt() : sign(1) {}\n\n    BigInt(long long v) {\n\
    \        *this = v;\n    }\n\n    BigInt(const std::string& s) {\n        read(s);\n\
    \    }\n\n    BigInt& operator=(long long v) {\n        sign = 1;\n        unsigned\
    \ long long magnitude = static_cast<unsigned long long>(v);\n        if (v < 0)\
    \ {\n            sign = -1;\n            magnitude = 0 - magnitude;\n        }\n\
    \        a.clear();\n        for (; magnitude > 0; magnitude /= BASE) {\n    \
    \        a.push_back(int(magnitude % BASE));\n        }\n        return *this;\n\
    \    }\n\n    BigInt& operator=(const std::string& s) {\n        read(s);\n  \
    \      return *this;\n    }\n\n    void trim() {\n        while (!a.empty() &&\
    \ a.back() == 0) {\n            a.pop_back();\n        }\n        if (a.empty())\
    \ sign = 1;\n    }\n\n    void read(const std::string& s) {\n        sign = 1;\n\
    \        a.clear();\n        int pos = 0;\n        while (pos < (int)s.size()\
    \ && (s[pos] == '-' || s[pos] == '+')) {\n            if (s[pos] == '-') sign\
    \ = -1;\n            ++pos;\n        }\n        a.reserve((int(s.size()) - pos\
    \ + BASE_DIGITS - 1) / BASE_DIGITS);\n        for (int i = int(s.size()) - 1;\
    \ i >= pos; i -= BASE_DIGITS) {\n            int x = 0;\n            for (int\
    \ j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {\n                x =\
    \ x * 10 + (s[j] - '0');\n            }\n            a.push_back(x);\n       \
    \ }\n        trim();\n    }\n\n    std::string to_string() const {\n        if\
    \ (a.empty()) return \"0\";\n        char leading[BASE_DIGITS];\n        const\
    \ std::to_chars_result converted =\n            std::to_chars(leading, leading\
    \ + BASE_DIGITS, a.back());\n        assert(converted.ec == std::errc());\n  \
    \      const int leading_size = int(converted.ptr - leading);\n        std::string\
    \ res((sign == -1) + leading_size +\n                            (a.size() - 1)\
    \ * BASE_DIGITS,\n                        '0');\n        int offset = 0;\n   \
    \     if (sign == -1) res[offset++] = '-';\n        std::copy(leading, converted.ptr,\
    \ res.begin() + offset);\n        offset += leading_size;\n        for (int i\
    \ = (int)a.size() - 2; i >= 0; --i) {\n            char block[BASE_DIGITS];\n\
    \            const std::to_chars_result block_converted =\n                std::to_chars(block,\
    \ block + BASE_DIGITS, a[i]);\n            assert(block_converted.ec == std::errc());\n\
    \            const int block_size = int(block_converted.ptr - block);\n      \
    \      std::copy(block, block_converted.ptr,\n                      res.begin()\
    \ + offset + BASE_DIGITS - block_size);\n            offset += BASE_DIGITS;\n\
    \        }\n        return res;\n    }\n\n    bool is_zero() const {\n       \
    \ return a.empty() || (a.size() == 1 && a[0] == 0);\n    }\n\n    BigInt operator-()\
    \ const {\n        BigInt res = *this;\n        if (!is_zero()) res.sign = -sign;\n\
    \        return res;\n    }\n\n    BigInt abs() const {\n        BigInt res =\
    \ *this;\n        res.sign = 1;\n        return res;\n    }\n\n    friend bool\
    \ operator<(const BigInt& x, const BigInt& y) {\n        if (x.sign != y.sign)\
    \ return x.sign < y.sign;\n        if (x.a.size() != y.a.size()) {\n         \
    \   return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());\n\
    \        }\n        for (int i = (int)x.a.size() - 1; i >= 0; --i) {\n       \
    \     if (x.a[i] != y.a[i]) {\n                return (x.sign == 1) ? (x.a[i]\
    \ < y.a[i]) : (x.a[i] > y.a[i]);\n            }\n        }\n        return false;\n\
    \    }\n\n    friend bool operator>(const BigInt& x, const BigInt& y) {\n    \
    \    return y < x;\n    }\n    friend bool operator<=(const BigInt& x, const BigInt&\
    \ y) {\n        return !(y < x);\n    }\n    friend bool operator>=(const BigInt&\
    \ x, const BigInt& y) {\n        return !(x < y);\n    }\n    friend bool operator==(const\
    \ BigInt& x, const BigInt& y) {\n        return x.sign == y.sign && x.a == y.a;\n\
    \    }\n    friend bool operator!=(const BigInt& x, const BigInt& y) {\n     \
    \   return !(x == y);\n    }\n\n    BigInt& operator+=(const BigInt& other) {\n\
    \        if (other.is_zero()) return *this;\n        if (is_zero()) return *this\
    \ = other;\n        if (sign != other.sign) {\n            const int comparison\
    \ = magnitude_compare(a, other.a);\n            if (comparison == 0) {\n     \
    \           a.clear();\n                sign = 1;\n            } else if (comparison\
    \ > 0) {\n                subtract_magnitude_inplace(a, other.a);\n          \
    \  } else {\n                std::vector<int> result = other.a;\n            \
    \    subtract_magnitude_inplace(result, a);\n                a = std::move(result);\n\
    \                sign = other.sign;\n            }\n            return *this;\n\
    \        }\n        add_magnitude_inplace(a, other.a);\n        return *this;\n\
    \    }\n\n    BigInt& operator-=(const BigInt& other) {\n        if (other.is_zero())\
    \ return *this;\n        if (is_zero()) return *this = -other;\n        if (sign\
    \ != other.sign) {\n            add_magnitude_inplace(a, other.a);\n         \
    \   return *this;\n        }\n        const int comparison = magnitude_compare(a,\
    \ other.a);\n        if (comparison == 0) {\n            a.clear();\n        \
    \    sign = 1;\n        } else if (comparison > 0) {\n            subtract_magnitude_inplace(a,\
    \ other.a);\n        } else {\n            std::vector<int> result = other.a;\n\
    \            subtract_magnitude_inplace(result, a);\n            a = std::move(result);\n\
    \            sign = -sign;\n        }\n        return *this;\n    }\n\n    BigInt&\
    \ operator*=(int v) {\n        if (v == 0 || is_zero()) return *this = 0;\n  \
    \      long long multiplier = v;\n        if (multiplier < 0) {\n            sign\
    \ = -sign;\n            multiplier = -multiplier;\n        }\n        a.reserve(a.size()\
    \ + 2);\n        long long carry = 0;\n        for (int i = 0; i < (int)a.size()\
    \ || carry; ++i) {\n            if (i == (int)a.size()) a.push_back(0);\n    \
    \        const long long cur = a[i] * multiplier + carry;\n            carry =\
    \ cur / BASE;\n            a[i] = (int)(cur % BASE);\n        }\n        trim();\n\
    \        return *this;\n    }\n\n   private:\n    static constexpr int MULTIPLICATION_THRESHOLD\
    \ = 128;\n    static constexpr int SQUARE_THRESHOLD = 224;\n    static constexpr\
    \ int DIVISION_THRESHOLD = 64;\n    static constexpr int FFT_SPLIT = 1 << 15;\n\
    \n    struct FftComplex {\n        double real;\n        double imaginary;\n\n\
    \        FftComplex operator+(const FftComplex& other) const {\n            return\
    \ {real + other.real, imaginary + other.imaginary};\n        }\n\n        FftComplex\
    \ operator-(const FftComplex& other) const {\n            return {real - other.real,\
    \ imaginary - other.imaginary};\n        }\n\n        FftComplex operator*(const\
    \ FftComplex& other) const {\n            return {real * other.real - imaginary\
    \ * other.imaginary,\n                    real * other.imaginary + imaginary *\
    \ other.real};\n        }\n\n        FftComplex operator*(double scalar) const\
    \ {\n            return {real * scalar, imaginary * scalar};\n        }\n\n  \
    \      FftComplex conjugate() const {\n            return {real, -imaginary};\n\
    \        }\n    };\n\n    struct FftProducts {\n        FftComplex diagonal;\n\
    \        FftComplex cross;\n    };\n\n    static const std::vector<FftComplex>&\
    \ fft_roots(int size) {\n        static std::vector<FftComplex> roots(2, FftComplex{1,\
    \ 0});\n        if (int(roots.size()) < size) {\n            int length = int(roots.size());\n\
    \            roots.resize(size);\n            while (length < size) {\n      \
    \          const long double angle = std::numbers::pi_v<long double> / length;\n\
    \                const long double step_real = std::cos(angle);\n            \
    \    const long double step_imaginary = std::sin(angle);\n                for\
    \ (int i = length; i < 2 * length; ++i) {\n                    roots[i] = roots[i\
    \ / 2];\n                    if (i & 1) {\n                        const long\
    \ double real = roots[i].real;\n                        const long double imaginary\
    \ = roots[i].imaginary;\n                        roots[i] = {\n              \
    \              double(real * step_real - imaginary * step_imaginary),\n      \
    \                      double(real * step_imaginary + imaginary * step_real)};\n\
    \                    }\n                }\n                length *= 2;\n    \
    \        }\n        }\n        return roots;\n    }\n\n    static void fft(std::vector<FftComplex>&\
    \ values) {\n        const int size = int(values.size());\n        assert(size\
    \ > 0 && (size & (size - 1)) == 0);\n        const std::vector<FftComplex>& roots\
    \ = fft_roots(size);\n\n        // Decimation in frequency leaves the spectrum\
    \ bit-reversed. The inverse\n        // transform consumes that order directly,\
    \ avoiding permutation passes.\n        for (int length = size / 2; length > 0;\
    \ length /= 2) {\n            for (int offset = 0; offset < size; offset += 2\
    \ * length) {\n                for (int i = 0; i < length; ++i) {\n          \
    \          const FftComplex even = values[offset + i];\n                    const\
    \ FftComplex odd = values[offset + i + length];\n                    values[offset\
    \ + i] = even + odd;\n                    values[offset + i + length] =\n    \
    \                    (even - odd) * roots[length + i];\n                }\n  \
    \          }\n        }\n    }\n\n    static void inverse_fft(std::vector<FftComplex>&\
    \ values) {\n        const int size = int(values.size());\n        assert(size\
    \ > 0 && (size & (size - 1)) == 0);\n        const std::vector<FftComplex>& roots\
    \ = fft_roots(size);\n\n        for (int length = 1; length < size; length *=\
    \ 2) {\n            for (int offset = 0; offset < size; offset += 2 * length)\
    \ {\n                for (int i = 0; i < length; ++i) {\n                    const\
    \ FftComplex even = values[offset + i];\n                    const FftComplex\
    \ value = values[offset + i + length];\n                    const FftComplex root\
    \ = roots[length + i];\n                    const FftComplex odd = {\n       \
    \                 value.real * root.real + value.imaginary * root.imaginary,\n\
    \                        value.imaginary * root.real - value.real * root.imaginary};\n\
    \                    values[offset + i] = even + odd;\n                    values[offset\
    \ + i + length] = even - odd;\n                }\n            }\n        }\n \
    \       const double inverse_size = 1.0 / double(size);\n        for (FftComplex&\
    \ value : values) {\n            value.real *= inverse_size;\n            value.imaginary\
    \ *= inverse_size;\n        }\n    }\n\n    static FftComplex fft_low(const FftComplex&\
    \ value,\n                              const FftComplex& reflected) {\n     \
    \   return (value + reflected) * 0.5;\n    }\n\n    static FftComplex fft_high(const\
    \ FftComplex& value,\n                               const FftComplex& reflected)\
    \ {\n        const FftComplex difference = value - reflected;\n        return\
    \ {difference.imaginary * 0.5, -difference.real * 0.5};\n    }\n\n    static void\
    \ trim_magnitude(std::vector<int>& value) {\n        while (!value.empty() &&\
    \ value.back() == 0) value.pop_back();\n    }\n\n    static bool magnitude_less(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n        return magnitude_compare(lhs,\
    \ rhs) < 0;\n    }\n\n    static int magnitude_compare(const std::vector<int>&\
    \ lhs,\n                                 const std::vector<int>& rhs) {\n    \
    \    if (lhs.size() != rhs.size()) return lhs.size() < rhs.size() ? -1 : 1;\n\
    \        for (int i = int(lhs.size()) - 1; i >= 0; --i) {\n            if (lhs[i]\
    \ != rhs[i]) return lhs[i] < rhs[i] ? -1 : 1;\n        }\n        return 0;\n\
    \    }\n\n    static void add_magnitude_inplace(std::vector<int>& lhs,\n     \
    \                                 const std::vector<int>& rhs) {\n        const\
    \ int lhs_size = int(lhs.size());\n        const int rhs_size = int(rhs.size());\n\
    \        const int size = std::max(lhs_size, rhs_size);\n        if (lhs_size\
    \ < rhs_size) lhs.resize(rhs_size);\n        int carry = 0;\n        int i = 0;\n\
    \        for (; i < rhs_size; ++i) {\n            const long long current = (long\
    \ long)lhs[i] + rhs[i] + carry;\n            lhs[i] = int(current >= BASE ? current\
    \ - BASE : current);\n            carry = current >= BASE;\n        }\n      \
    \  while (i < size && carry) {\n            ++lhs[i];\n            carry = lhs[i]\
    \ == BASE;\n            if (carry) lhs[i] = 0;\n            ++i;\n        }\n\
    \        if (carry) lhs.push_back(1);\n    }\n\n    static void subtract_magnitude_inplace(std::vector<int>&\
    \ lhs,\n                                           const std::vector<int>& rhs)\
    \ {\n        assert(!magnitude_less(lhs, rhs));\n        int borrow = 0;\n   \
    \     for (int i = 0; i < int(rhs.size()) || borrow; ++i) {\n            int current\
    \ = lhs[i] - borrow - (i < int(rhs.size()) ? rhs[i] : 0);\n            borrow\
    \ = current < 0;\n            if (borrow) current += BASE;\n            lhs[i]\
    \ = current;\n        }\n        assert(borrow == 0);\n        trim_magnitude(lhs);\n\
    \    }\n\n    static bool magnitude_less_equal(const std::vector<int>& lhs,\n\
    \                                     const std::vector<int>& rhs) {\n       \
    \ return !magnitude_less(rhs, lhs);\n    }\n\n    static std::vector<int> add_magnitude(const\
    \ std::vector<int>& lhs,\n                                          const std::vector<int>&\
    \ rhs) {\n        std::vector<int> result(std::max(lhs.size(), rhs.size()) + 1);\n\
    \        for (int i = 0; i < int(result.size()) - 1; ++i) {\n            if (i\
    \ < int(lhs.size())) result[i] += lhs[i];\n            if (i < int(rhs.size()))\
    \ result[i] += rhs[i];\n            if (result[i] >= BASE) {\n               \
    \ result[i] -= BASE;\n                result[i + 1]++;\n            }\n      \
    \  }\n        trim_magnitude(result);\n        return result;\n    }\n\n    static\
    \ std::vector<int> subtract_magnitude(const std::vector<int>& lhs,\n         \
    \                                      const std::vector<int>& rhs) {\n      \
    \  assert(!magnitude_less(lhs, rhs));\n        std::vector<int> result = lhs;\n\
    \        int borrow = 0;\n        for (int i = 0; i < int(result.size()); ++i)\
    \ {\n            const long long current =\n                (long long)result[i]\
    \ - borrow - (i < int(rhs.size()) ? rhs[i] : 0);\n            if (current < 0)\
    \ {\n                result[i] = int(current + BASE);\n                borrow\
    \ = 1;\n            } else {\n                result[i] = int(current);\n    \
    \            borrow = 0;\n            }\n        }\n        assert(borrow == 0);\n\
    \        trim_magnitude(result);\n        return result;\n    }\n\n    static\
    \ std::vector<int> multiply_naive(const std::vector<int>& lhs,\n             \
    \                              const std::vector<int>& rhs) {\n        if (lhs.empty()\
    \ || rhs.empty()) return std::vector<int>();\n        std::vector<long long> product(lhs.size()\
    \ + rhs.size());\n        constexpr long long REDUCTION = 4LL * BASE * BASE;\n\
    \        for (int i = 0; i < int(lhs.size()); ++i) {\n            for (int j =\
    \ 0; j < int(rhs.size()); ++j) {\n                product[i + j] += (long long)lhs[i]\
    \ * rhs[j];\n                if (product[i + j] >= REDUCTION) {\n            \
    \        product[i + j] -= REDUCTION;\n                    product[i + j + 1]\
    \ += 4LL * BASE;\n                }\n            }\n        }\n\n        std::vector<int>\
    \ result;\n        result.reserve(product.size() + 1);\n        long long carry\
    \ = 0;\n        for (int i = 0; i < int(product.size()) || carry > 0; ++i) {\n\
    \            if (i < int(product.size())) carry += product[i];\n            result.push_back(int(carry\
    \ % BASE));\n            carry /= BASE;\n        }\n        trim_magnitude(result);\n\
    \        return result;\n    }\n\n    static std::vector<int> square_naive(const\
    \ std::vector<int>& value) {\n        if (value.empty()) return std::vector<int>();\n\
    \        std::vector<long long> product(2 * value.size());\n        constexpr\
    \ long long REDUCTION = 4LL * BASE * BASE;\n        for (int i = 0; i < int(value.size());\
    \ ++i) {\n            product[2 * i] += (long long)value[i] * value[i];\n    \
    \        if (product[2 * i] >= REDUCTION) {\n                product[2 * i] -=\
    \ REDUCTION;\n                product[2 * i + 1] += 4LL * BASE;\n            }\n\
    \            for (int j = i + 1; j < int(value.size()); ++j) {\n             \
    \   product[i + j] += 2LL * value[i] * value[j];\n                if (product[i\
    \ + j] >= REDUCTION) {\n                    product[i + j] -= REDUCTION;\n   \
    \                 product[i + j + 1] += 4LL * BASE;\n                }\n     \
    \       }\n        }\n\n        std::vector<int> result;\n        result.reserve(product.size()\
    \ + 1);\n        long long carry = 0;\n        for (int i = 0; i < int(product.size())\
    \ || carry > 0; ++i) {\n            if (i < int(product.size())) carry += product[i];\n\
    \            result.push_back(int(carry % BASE));\n            carry /= BASE;\n\
    \        }\n        trim_magnitude(result);\n        return result;\n    }\n\n\
    \    static std::vector<int> multiply_by_limb(const std::vector<int>& value,\n\
    \                                             int multiplier) {\n        assert(0\
    \ <= multiplier && multiplier < BASE);\n        if (value.empty() || multiplier\
    \ == 0) return std::vector<int>();\n        std::vector<int> result;\n       \
    \ result.reserve(value.size() + 1);\n        uint64_t carry = 0;\n        for\
    \ (int limb : value) {\n            const uint64_t current = uint64_t(limb) *\
    \ multiplier + carry;\n            result.push_back(int(current % BASE));\n  \
    \          carry = current / BASE;\n        }\n        if (carry) result.push_back(int(carry));\n\
    \        return result;\n    }\n\n    static std::vector<int> multiply_ntt(const\
    \ std::vector<int>& lhs,\n                                         const std::vector<int>&\
    \ rhs) {\n        using Mint1 = math::ModInt<998244353>;\n        using Mint2\
    \ = math::ModInt<754974721>;\n        using Mint3 = math::ModInt<469762049>;\n\
    \n        const int result_size = int(lhs.size() + rhs.size() - 1);\n        assert(result_size\
    \ <= (1 << 24));\n\n        auto convolve = [&]<class Mint>() {\n            std::vector<Mint>\
    \ x(lhs.begin(), lhs.end());\n            if (&lhs == &rhs) return fps::convolution(x,\
    \ x);\n            std::vector<Mint> y(rhs.begin(), rhs.end());\n            return\
    \ fps::convolution(x, y);\n        };\n        const std::vector<Mint1> residues1\
    \ = convolve.template operator()<Mint1>();\n        const std::vector<Mint2> residues2\
    \ = convolve.template operator()<Mint2>();\n        const std::vector<Mint3> residues3\
    \ = convolve.template operator()<Mint3>();\n\n        constexpr uint64_t MOD1\
    \ = Mint1::mod();\n        constexpr uint64_t MOD2 = Mint2::mod();\n        constexpr\
    \ uint64_t MOD3 = Mint3::mod();\n        constexpr uint64_t MOD12 = MOD1 * MOD2;\n\
    \        const static uint64_t inverse_mod1_mod2 = Mint2(MOD1).inv().val();\n\
    \        const static uint64_t inverse_mod12_mod3 = Mint3(MOD12 % MOD3).inv().val();\n\
    \        [[maybe_unused]] const unsigned __int128 coefficient_bound =\n      \
    \      static_cast<unsigned __int128>(std::min(lhs.size(), rhs.size())) *\n  \
    \          (BASE - 1) * (BASE - 1);\n        [[maybe_unused]] constexpr unsigned\
    \ __int128 CRT_MODULUS =\n            static_cast<unsigned __int128>(MOD12) *\
    \ MOD3;\n        assert(coefficient_bound < CRT_MODULUS);\n\n        std::vector<int>\
    \ result;\n        result.reserve(result_size + 2);\n        unsigned __int128\
    \ carry = 0;\n        for (int i = 0; i < result_size || carry > 0; ++i) {\n \
    \           if (i < result_size) {\n                const uint64_t first = residues1[i].val();\n\
    \                const uint64_t second = residues2[i].val();\n               \
    \ const uint64_t third = residues3[i].val();\n                const uint64_t difference12\
    \ =\n                    (second + MOD2 - first % MOD2) % MOD2;\n            \
    \    const uint64_t quotient12 =\n                    difference12 * inverse_mod1_mod2\
    \ % MOD2;\n                const uint64_t combined12 = first + MOD1 * quotient12;\n\
    \                const uint64_t difference3 =\n                    (third + MOD3\
    \ - combined12 % MOD3) % MOD3;\n                const uint64_t quotient3 =\n \
    \                   difference3 * inverse_mod12_mod3 % MOD3;\n               \
    \ carry += combined12 +\n                         static_cast<unsigned __int128>(MOD12)\
    \ * quotient3;\n            }\n            result.push_back(int(carry % BASE));\n\
    \            carry /= BASE;\n        }\n        trim_magnitude(result);\n    \
    \    return result;\n    }\n\n    static uint64_t mersenne_reduce(unsigned __int128\
    \ value) {\n        constexpr uint64_t MODULUS = (uint64_t(1) << 61) - 1;\n  \
    \      value = (value & MODULUS) + (value >> 61);\n        uint64_t result = uint64_t(value\
    \ & MODULUS) + uint64_t(value >> 61);\n        if (result >= MODULUS) result -=\
    \ MODULUS;\n        return result;\n    }\n\n    static uint64_t magnitude_mod(const\
    \ std::vector<int>& value) {\n        uint64_t result = 0;\n        for (int i\
    \ = int(value.size()) - 1; i >= 0; --i) {\n            result = mersenne_reduce(static_cast<unsigned\
    \ __int128>(result) * BASE +\n                                     value[i]);\n\
    \        }\n        return result;\n    }\n\n    static bool product_matches(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs,\n                      \
    \          const std::vector<int>& product) {\n        const uint64_t expected\
    \ = mersenne_reduce(\n            static_cast<unsigned __int128>(magnitude_mod(lhs))\
    \ * magnitude_mod(rhs));\n        return magnitude_mod(product) == expected;\n\
    \    }\n\n    static std::vector<int> multiply_fft(const std::vector<int>& lhs,\n\
    \                                         const std::vector<int>& rhs) {\n   \
    \     const int result_size = int(lhs.size() + rhs.size() - 1);\n        const\
    \ int transform_size = int(std::bit_ceil(unsigned(result_size)));\n        const\
    \ unsigned __int128 coefficient_bound =\n            static_cast<unsigned __int128>(std::min(lhs.size(),\
    \ rhs.size())) *\n            2 * (FFT_SPLIT - 1) * ((BASE - 1) / FFT_SPLIT);\n\
    \        if (transform_size > (1 << 20) || coefficient_bound >= (uint64_t(1) <<\
    \ 48)) {\n            return multiply_ntt(lhs, rhs);\n        }\n\n        std::vector<FftComplex>\
    \ transformed_lhs(transform_size, FftComplex{0, 0});\n        for (int i = 0;\
    \ i < int(lhs.size()); ++i) {\n            transformed_lhs[i] = {double(lhs[i]\
    \ % FFT_SPLIT),\n                                  double(lhs[i] / FFT_SPLIT)};\n\
    \        }\n        fft(transformed_lhs);\n\n        const bool squaring = &lhs\
    \ == &rhs;\n        std::vector<FftComplex> transformed_rhs;\n        if (!squaring)\
    \ {\n            transformed_rhs.assign(transform_size, FftComplex{0, 0});\n \
    \           for (int i = 0; i < int(rhs.size()); ++i) {\n                transformed_rhs[i]\
    \ = {double(rhs[i] % FFT_SPLIT),\n                                      double(rhs[i]\
    \ / FFT_SPLIT)};\n            }\n            fft(transformed_rhs);\n        }\n\
    \n        std::vector<FftComplex> square_cross_product;\n        if (squaring)\
    \ square_cross_product.resize(transform_size);\n        static std::vector<int>\
    \ reflected_indices;\n        if (int(reflected_indices.size()) != transform_size)\
    \ {\n            reflected_indices.resize(transform_size);\n            reflected_indices[0]\
    \ = 0;\n            for (int i = 1; i < transform_size; ++i) {\n             \
    \   // Negating a frequency complements the bits below the highest\n         \
    \       // set bit of its bit-reversed index.\n                reflected_indices[i]\
    \ =\n                    i ^ int(std::bit_floor(unsigned(i)) - 1);\n         \
    \   }\n        }\n        auto calculate_products = [&](int index) {\n       \
    \     const int opposite = reflected_indices[index];\n            const FftComplex\
    \ lhs_reflected =\n                transformed_lhs[opposite].conjugate();\n  \
    \          const FftComplex lhs_low =\n                fft_low(transformed_lhs[index],\
    \ lhs_reflected);\n            const FftComplex lhs_high =\n                fft_high(transformed_lhs[index],\
    \ lhs_reflected);\n\n            FftComplex rhs_low = lhs_low;\n            FftComplex\
    \ rhs_high = lhs_high;\n            if (!squaring) {\n                const FftComplex\
    \ rhs_reflected =\n                    transformed_rhs[opposite].conjugate();\n\
    \                rhs_low = fft_low(transformed_rhs[index], rhs_reflected);\n \
    \               rhs_high = fft_high(transformed_rhs[index], rhs_reflected);\n\
    \            }\n\n            const FftComplex low_product = lhs_low * rhs_low;\n\
    \            const FftComplex high_product = lhs_high * rhs_high;\n          \
    \  const FftComplex diagonal =\n                low_product + FftComplex{-high_product.imaginary,\n\
    \                                         high_product.real};\n            const\
    \ FftComplex cross =\n                lhs_low * rhs_high + lhs_high * rhs_low;\n\
    \            return FftProducts{diagonal, cross};\n        };\n\n        for (int\
    \ i = 0; i < transform_size; ++i) {\n            const int opposite = reflected_indices[i];\n\
    \            if (i > opposite) continue;\n            const FftProducts products\
    \ = calculate_products(i);\n            FftProducts opposite_products = products;\n\
    \            if (i != opposite) opposite_products = calculate_products(opposite);\n\
    \n            transformed_lhs[i] = products.diagonal;\n            transformed_lhs[opposite]\
    \ = opposite_products.diagonal;\n            if (squaring) {\n               \
    \ square_cross_product[i] = products.cross;\n                square_cross_product[opposite]\
    \ = opposite_products.cross;\n            } else {\n                transformed_rhs[i]\
    \ = products.cross;\n                transformed_rhs[opposite] = opposite_products.cross;\n\
    \            }\n        }\n        std::vector<FftComplex>& cross_product =\n\
    \            squaring ? square_cross_product : transformed_rhs;\n        inverse_fft(transformed_lhs);\n\
    \        inverse_fft(cross_product);\n\n        std::vector<int> result;\n   \
    \     result.reserve(result_size + 2);\n        unsigned __int128 carry = 0;\n\
    \        for (int i = 0; i < result_size || carry > 0; ++i) {\n            if\
    \ (i < result_size) {\n                const long long low = std::llround(transformed_lhs[i].real);\n\
    \                const long long high = std::llround(transformed_lhs[i].imaginary);\n\
    \                const long long cross = std::llround(cross_product[i].real);\n\
    \                if (low < 0 || high < 0 || cross < 0) return multiply_ntt(lhs,\
    \ rhs);\n                carry += low + static_cast<unsigned __int128>(cross)\
    \ * FFT_SPLIT +\n                         static_cast<unsigned __int128>(high)\
    \ * FFT_SPLIT * FFT_SPLIT;\n            }\n            result.push_back(int(carry\
    \ % BASE));\n            carry /= BASE;\n        }\n        trim_magnitude(result);\n\
    \        if (result.empty() || !product_matches(lhs, rhs, result)) {\n       \
    \     return multiply_ntt(lhs, rhs);\n        }\n        return result;\n    }\n\
    \n    static std::vector<int> multiply_magnitude(const std::vector<int>& lhs,\n\
    \                                               const std::vector<int>& rhs) {\n\
    \        if (lhs.empty() || rhs.empty()) return std::vector<int>();\n        if\
    \ (lhs.size() == 1) return multiply_by_limb(rhs, lhs[0]);\n        if (rhs.size()\
    \ == 1) return multiply_by_limb(lhs, rhs[0]);\n        if (&lhs == &rhs && lhs.size()\
    \ <= SQUARE_THRESHOLD) {\n            return square_naive(lhs);\n        }\n \
    \       if (std::min(lhs.size(), rhs.size()) <= MULTIPLICATION_THRESHOLD) {\n\
    \            return multiply_naive(lhs, rhs);\n        }\n        return multiply_fft(lhs,\
    \ rhs);\n    }\n\n    static std::pair<std::vector<int>, std::vector<int>> divide_by_limb(\n\
    \        const std::vector<int>& dividend, int divisor) {\n        assert(0 <\
    \ divisor && divisor < BASE);\n        if (divisor == 1) {\n            return\
    \ std::make_pair(dividend, std::vector<int>());\n        }\n        std::vector<int>\
    \ quotient(dividend.size());\n        long long remainder = 0;\n        for (int\
    \ i = int(dividend.size()) - 1; i >= 0; --i) {\n            const long long current\
    \ = remainder * BASE + dividend[i];\n            quotient[i] = int(current / divisor);\n\
    \            remainder = current % divisor;\n        }\n        trim_magnitude(quotient);\n\
    \        std::vector<int> remainder_digits;\n        if (remainder != 0) remainder_digits.push_back(int(remainder));\n\
    \        return std::make_pair(std::move(quotient), std::move(remainder_digits));\n\
    \    }\n\n    static std::pair<std::vector<int>, std::vector<int>> divide_classical(\n\
    \        const std::vector<int>& dividend, const std::vector<int>& divisor) {\n\
    \        assert(!divisor.empty());\n        if (divisor.size() == 1) return divide_by_limb(dividend,\
    \ divisor[0]);\n        if (magnitude_less(dividend, divisor)) {\n           \
    \ return std::make_pair(std::vector<int>(), dividend);\n        }\n\n        const\
    \ int normalization = BASE / (divisor.back() + 1);\n        std::vector<int> normalized_divisor(divisor.size());\n\
    \        uint64_t carry = 0;\n        for (int i = 0; i < int(divisor.size());\
    \ ++i) {\n            const uint64_t current = uint64_t(divisor[i]) * normalization\
    \ + carry;\n            normalized_divisor[i] = int(current % BASE);\n       \
    \     carry = current / BASE;\n        }\n        assert(carry == 0);\n\n    \
    \    std::vector<int> normalized_dividend(dividend.size() + 1);\n        carry\
    \ = 0;\n        for (int i = 0; i < int(dividend.size()); ++i) {\n           \
    \ const uint64_t current = uint64_t(dividend[i]) * normalization + carry;\n  \
    \          normalized_dividend[i] = int(current % BASE);\n            carry =\
    \ current / BASE;\n        }\n        normalized_dividend[dividend.size()] = int(carry);\n\
    \n        const int divisor_size = int(normalized_divisor.size());\n        const\
    \ int quotient_size = int(dividend.size()) - divisor_size + 1;\n        const\
    \ uint64_t leading_divisor = normalized_divisor.back();\n        const uint64_t\
    \ second_divisor = normalized_divisor[divisor_size - 2];\n        std::vector<int>\
    \ quotient(quotient_size);\n\n        for (int position = quotient_size - 1; position\
    \ >= 0; --position) {\n            const uint64_t leading_dividend =\n       \
    \         uint64_t(normalized_dividend[position + divisor_size]) * BASE +\n  \
    \              normalized_dividend[position + divisor_size - 1];\n           \
    \ uint64_t digit = leading_dividend / leading_divisor;\n            uint64_t remainder\
    \ = leading_dividend % leading_divisor;\n            if (digit >= BASE) {\n  \
    \              digit = BASE - 1;\n                remainder = leading_dividend\
    \ - digit * leading_divisor;\n            }\n            while (remainder < BASE\
    \ &&\n                   digit * second_divisor >\n                       remainder\
    \ * BASE +\n                           normalized_dividend[position + divisor_size\
    \ - 2]) {\n                --digit;\n                remainder += leading_divisor;\n\
    \            }\n\n            uint64_t borrow = 0;\n            for (int i = 0;\
    \ i < divisor_size; ++i) {\n                const uint64_t product =\n       \
    \             digit * uint64_t(normalized_divisor[i]) + borrow;\n            \
    \    const uint64_t low = product % BASE;\n                borrow = product /\
    \ BASE;\n                if (uint64_t(normalized_dividend[position + i]) < low)\
    \ {\n                    normalized_dividend[position + i] =\n               \
    \         int(uint64_t(normalized_dividend[position + i]) + BASE - low);\n   \
    \                 ++borrow;\n                } else {\n                    normalized_dividend[position\
    \ + i] -= int(low);\n                }\n            }\n\n            long long\
    \ top =\n                (long long)normalized_dividend[position + divisor_size]\
    \ -\n                static_cast<long long>(borrow);\n            if (top < 0)\
    \ {\n                --digit;\n                uint64_t add_carry = 0;\n     \
    \           for (int i = 0; i < divisor_size; ++i) {\n                    const\
    \ uint64_t current =\n                        uint64_t(normalized_dividend[position\
    \ + i]) +\n                        normalized_divisor[i] + add_carry;\n      \
    \              normalized_dividend[position + i] = int(current % BASE);\n    \
    \                add_carry = current / BASE;\n                }\n            \
    \    top += add_carry;\n            }\n            assert(0 <= top && top < BASE);\n\
    \            normalized_dividend[position + divisor_size] = int(top);\n      \
    \      quotient[position] = int(digit);\n        }\n\n        trim_magnitude(quotient);\n\
    \        std::vector<int> remainder(normalized_dividend.begin(),\n           \
    \                        normalized_dividend.begin() + divisor_size);\n      \
    \  trim_magnitude(remainder);\n        std::pair<std::vector<int>, std::vector<int>>\
    \ denormalized =\n            divide_by_limb(remainder, normalization);\n    \
    \    assert(denormalized.second.empty());\n        return std::make_pair(std::move(quotient),\
    \ std::move(denormalized.first));\n    }\n\n    static std::vector<int> reciprocal(const\
    \ std::vector<int>& value, int degree) {\n        assert(!value.empty());\n  \
    \      assert(BASE / 2 <= value.back() && value.back() < BASE);\n        assert(degree\
    \ >= 0);\n\n        int precision = degree;\n        const int value_size = int(value.size());\n\
    \        while (precision > DIVISION_THRESHOLD) precision = (precision + 1) /\
    \ 2;\n\n        std::vector<int> inverse(value_size + precision + 1);\n      \
    \  inverse.back() = 1;\n        inverse = divide_classical(inverse, value).first;\n\
    \n        while (precision < degree) {\n            std::vector<int> square =\
    \ multiply_magnitude(inverse, inverse);\n            square.insert(square.begin(),\
    \ 0);\n\n            std::vector<int> leading(2 * precision + 1);\n          \
    \  const int copied = std::min(value_size, int(leading.size()));\n           \
    \ std::copy(value.end() - copied, value.end(), leading.end() - copied);\n\n  \
    \          std::vector<int> correction = multiply_magnitude(square, leading);\n\
    \            assert(int(correction.size()) >= 2 * precision + 1);\n          \
    \  correction.erase(correction.begin(), correction.begin() + 2 * precision + 1);\n\
    \n            std::vector<int> shifted(precision + 1);\n            const std::vector<int>\
    \ doubled = add_magnitude(inverse, inverse);\n            shifted.insert(shifted.end(),\
    \ doubled.begin(), doubled.end());\n            inverse = subtract_magnitude(shifted,\
    \ correction);\n            assert(!inverse.empty());\n            inverse.erase(inverse.begin());\n\
    \            precision *= 2;\n        }\n\n        assert(precision >= degree);\n\
    \        inverse.erase(inverse.begin(), inverse.begin() + precision - degree);\n\
    \        trim_magnitude(inverse);\n        return inverse;\n    }\n\n    static\
    \ std::pair<std::vector<int>, std::vector<int>> divide_magnitude(\n        const\
    \ std::vector<int>& dividend, const std::vector<int>& divisor) {\n        assert(!divisor.empty());\n\
    \        if (divisor.size() <= DIVISION_THRESHOLD ||\n            int(dividend.size())\
    \ - int(divisor.size()) <= DIVISION_THRESHOLD) {\n            return divide_classical(dividend,\
    \ divisor);\n        }\n\n        const int normalization = BASE / (divisor.back()\
    \ + 1);\n        const std::vector<int> normalized_dividend =\n            multiply_magnitude(dividend,\
    \ std::vector<int>(1, normalization));\n        const std::vector<int> normalized_divisor\
    \ =\n            multiply_magnitude(divisor, std::vector<int>(1, normalization));\n\
    \        const int dividend_size = int(normalized_dividend.size());\n        const\
    \ int divisor_size = int(normalized_divisor.size());\n        const int degree\
    \ = dividend_size - divisor_size + 2;\n        const std::vector<int> inverse\
    \ = reciprocal(normalized_divisor, degree);\n\n        std::vector<int> quotient\
    \ = multiply_magnitude(normalized_dividend, inverse);\n        const int discarded\
    \ = divisor_size + degree;\n        assert(discarded <= int(quotient.size()));\n\
    \        quotient.erase(quotient.begin(), quotient.begin() + discarded);\n\n \
    \       std::vector<int> product = multiply_magnitude(normalized_divisor, quotient);\n\
    \        while (magnitude_less(normalized_dividend, product)) {\n            quotient\
    \ = subtract_magnitude(quotient, std::vector<int>(1, 1));\n            product\
    \ = subtract_magnitude(product, normalized_divisor);\n        }\n        std::vector<int>\
    \ remainder = subtract_magnitude(normalized_dividend, product);\n        while\
    \ (magnitude_less_equal(normalized_divisor, remainder)) {\n            quotient\
    \ = add_magnitude(quotient, std::vector<int>(1, 1));\n            remainder =\
    \ subtract_magnitude(remainder, normalized_divisor);\n        }\n        trim_magnitude(quotient);\n\
    \        trim_magnitude(remainder);\n\n        std::pair<std::vector<int>, std::vector<int>>\
    \ denormalized =\n            divide_by_limb(remainder, normalization);\n    \
    \    assert(denormalized.second.empty());\n        return std::make_pair(std::move(quotient),\
    \ std::move(denormalized.first));\n    }\n\n   public:\n    BigInt& operator*=(const\
    \ BigInt& other) {\n        if (is_zero() || other.is_zero()) return *this = 0;\n\
    \        const int result_sign = sign * other.sign;\n        a = multiply_magnitude(a,\
    \ other.a);\n        sign = result_sign;\n        trim();\n        return *this;\n\
    \    }\n\n    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const\
    \ BigInt& b1) {\n        if (b1.is_zero()) {\n            throw std::domain_error(\"\
    BigInt division by zero\");\n        }\n        std::pair<std::vector<int>, std::vector<int>>\
    \ result =\n            divide_magnitude(a1.a, b1.a);\n        BigInt q, r;\n\
    \        q.a = std::move(result.first);\n        r.a = std::move(result.second);\n\
    \        q.sign = a1.sign * b1.sign;\n        r.sign = a1.sign;\n        q.trim();\n\
    \        r.trim();\n        return {q, r};\n    }\n\n    BigInt& operator/=(const\
    \ BigInt& other) {\n        return *this = divmod(*this, other).first;\n    }\n\
    \    BigInt& operator%=(const BigInt& other) {\n        return *this = divmod(*this,\
    \ other).second;\n    }\n\n    friend BigInt operator+(BigInt x, const BigInt&\
    \ y) {\n        return x += y;\n    }\n    friend BigInt operator-(BigInt x, const\
    \ BigInt& y) {\n        return x -= y;\n    }\n    friend BigInt operator*(BigInt\
    \ x, const BigInt& y) {\n        return x *= y;\n    }\n    friend BigInt operator/(BigInt\
    \ x, const BigInt& y) {\n        return x /= y;\n    }\n    friend BigInt operator%(BigInt\
    \ x, const BigInt& y) {\n        return x %= y;\n    }\n\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const BigInt& b) {\n        return os << b.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(std::istream& is, BigInt& b) {\n\
    \        std::string s;\n        if (is >> s) b.read(s);\n        return is;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"\
    utilities/int128.hpp\"\n\n\n\n#line 5 \"utilities/int128.hpp\"\n#include <cctype>\n\
    #include <istream>\n#include <ostream>\n#line 10 \"utilities/int128.hpp\"\n\n\
    namespace m1une {\nnamespace utilities {\n\nusing i128 = __int128_t;\nusing u128\
    \ = __uint128_t;\n\ninline std::string to_string(u128 x) {\n    if (x == 0) {\n\
    \        return \"0\";\n    }\n    std::string s;\n    while (x > 0) {\n     \
    \   s.push_back(static_cast<char>('0' + x % 10));\n        x /= 10;\n    }\n \
    \   std::reverse(s.begin(), s.end());\n    return s;\n}\n\ninline std::string\
    \ to_string(i128 x) {\n    if (x < 0) {\n        u128 magnitude = static_cast<u128>(-(x\
    \ + 1)) + 1;\n        return \"-\" + to_string(magnitude);\n    }\n    return\
    \ to_string(static_cast<u128>(x));\n}\n\ninline u128 parse_uint128(const std::string&\
    \ s) {\n    if (s.empty()) {\n        throw std::invalid_argument(\"empty string\"\
    );\n    }\n    u128 value = 0;\n    for (char c : s) {\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid unsigned __int128\
    \ literal\");\n        }\n        value = value * 10 + static_cast<unsigned>(c\
    \ - '0');\n    }\n    return value;\n}\n\ninline i128 parse_int128(const std::string&\
    \ s) {\n    if (s.empty()) {\n        throw std::invalid_argument(\"empty string\"\
    );\n    }\n    bool negative = s[0] == '-';\n    std::size_t pos = (s[0] == '-'\
    \ || s[0] == '+') ? 1 : 0;\n    if (pos == s.size()) {\n        throw std::invalid_argument(\"\
    invalid __int128 literal\");\n    }\n\n    i128 value = 0;\n    for (; pos < s.size();\
    \ ++pos) {\n        char c = s[pos];\n        if (!std::isdigit(static_cast<unsigned\
    \ char>(c))) {\n            throw std::invalid_argument(\"invalid __int128 literal\"\
    );\n        }\n        int digit = c - '0';\n        value = value * 10 + (negative\
    \ ? -digit : digit);\n    }\n    return value;\n}\n\n}  // namespace utilities\n\
    }  // namespace m1une\n\ninline std::ostream& operator<<(std::ostream& os, __uint128_t\
    \ x) {\n    return os << m1une::utilities::to_string(x);\n}\n\ninline std::ostream&\
    \ operator<<(std::ostream& os, __int128_t x) {\n    return os << m1une::utilities::to_string(x);\n\
    }\n\ninline std::istream& operator>>(std::istream& is, __uint128_t& x) {\n   \
    \ std::string s;\n    is >> s;\n    if (is) {\n        x = m1une::utilities::parse_uint128(s);\n\
    \    }\n    return is;\n}\n\ninline std::istream& operator>>(std::istream& is,\
    \ __int128_t& x) {\n    std::string s;\n    is >> s;\n    if (is) {\n        x\
    \ = m1une::utilities::parse_int128(s);\n    }\n    return is;\n}\n\n\n#line 1\
    \ \"utilities/random.hpp\"\n\n\n\n#line 6 \"utilities/random.hpp\"\n#include <chrono>\n\
    #include <concepts>\n#line 9 \"utilities/random.hpp\"\n#include <functional>\n\
    #include <numeric>\n#include <queue>\n#include <random>\n#line 14 \"utilities/random.hpp\"\
    \n#include <string_view>\n#include <tuple>\n#line 17 \"utilities/random.hpp\"\n\
    #include <unordered_set>\n#line 20 \"utilities/random.hpp\"\n\nnamespace m1une\
    \ {\nnamespace utilities {\n\nstruct RandomGraphOptions {\n    bool directed =\
    \ false;\n    bool allow_self_loops = false;\n    bool allow_parallel_edges =\
    \ false;\n};\n\nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\n\
    \    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n    static std::uint64_t graph_edge_count(int vertex_count,\n      \
    \                                    const RandomGraphOptions& options) {\n  \
    \      std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if\
    \ (options.directed) {\n            return options.allow_self_loops ? n * n :\
    \ n * (n - 1);\n        }\n        return options.allow_self_loops ? n * (n +\
    \ 1) / 2 : n * (n - 1) / 2;\n    }\n\n    static std::pair<int, int> decode_graph_edge(\n\
    \        std::uint64_t index, int vertex_count,\n        const RandomGraphOptions&\
    \ options) {\n        std::uint64_t n = static_cast<unsigned int>(vertex_count);\n\
    \        if (options.directed) {\n            std::uint64_t width = options.allow_self_loops\
    \ ? n : n - 1;\n            int from = int(index / width);\n            int offset\
    \ = int(index % width);\n            int to = options.allow_self_loops || offset\
    \ < from ? offset : offset + 1;\n            return {from, to};\n        }\n\n\
    \        auto prefix = [&](std::uint64_t vertex) {\n            if (options.allow_self_loops)\
    \ {\n                return vertex * (2 * n - vertex + 1) / 2;\n            }\n\
    \            return vertex * (2 * n - vertex - 1) / 2;\n        };\n        std::uint64_t\
    \ low = 0;\n        std::uint64_t high = n;\n        while (low + 1 < high) {\n\
    \            std::uint64_t middle = (low + high) / 2;\n            if (prefix(middle)\
    \ <= index) {\n                low = middle;\n            } else {\n         \
    \       high = middle;\n            }\n        }\n        int from = int(low);\n\
    \        int to = from + int(index - prefix(low)) +\n                 (options.allow_self_loops\
    \ ? 0 : 1);\n        return {from, to};\n    }\n\n   public:\n    Random() : _engine(chrono_seed())\
    \ {}\n    explicit Random(unsigned long long seed) : _engine(seed) {}\n\n    void\
    \ seed(unsigned long long value) {\n        _engine.seed(value);\n    }\n\n  \
    \  std::mt19937_64& engine() {\n        return _engine;\n    }\n\n    unsigned\
    \ long long operator()() {\n        return _engine();\n    }\n\n    long long\
    \ uniform(long long l, long long r) {\n        return std::uniform_int_distribution<long\
    \ long>(l, r)(_engine);\n    }\n\n    unsigned long long uniform_unsigned(unsigned\
    \ long long l, unsigned long long r) {\n        return std::uniform_int_distribution<unsigned\
    \ long long>(l, r)(_engine);\n    }\n\n    double real(double l = 0.0, double\
    \ r = 1.0) {\n        return std::uniform_real_distribution<double>(l, r)(_engine);\n\
    \    }\n\n    template <std::integral T>\n    requires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\n    std::vector<T> sequence(int size, T lower, T upper) {\n        assert(0\
    \ <= size);\n        assert(lower <= upper);\n        if (size < 0 || upper <\
    \ lower) return {};\n        std::vector<T> result(size);\n        if constexpr\
    \ (std::signed_integral<T>) {\n            std::uniform_int_distribution<long\
    \ long> distribution(\n                static_cast<long long>(lower), static_cast<long\
    \ long>(upper));\n            for (T& value : result) value = static_cast<T>(distribution(_engine));\n\
    \        } else {\n            std::uniform_int_distribution<unsigned long long>\
    \ distribution(\n                static_cast<unsigned long long>(lower),\n   \
    \             static_cast<unsigned long long>(upper));\n            for (T& value\
    \ : result) value = static_cast<T>(distribution(_engine));\n        }\n      \
    \  return result;\n    }\n\n    std::string string(\n        int length,\n   \
    \     std::string_view alphabet = \"abcdefghijklmnopqrstuvwxyz\") {\n        assert(0\
    \ <= length);\n        assert(length == 0 || !alphabet.empty());\n        if (length\
    \ < 0 || (0 < length && alphabet.empty())) return {};\n        std::string result(length,\
    \ '\\0');\n        for (char& character : result) {\n            character = alphabet[uniform(0,\
    \ int(alphabet.size()) - 1)];\n        }\n        return result;\n    }\n\n  \
    \  std::vector<int> permutation(int size, int first = 0) {\n        assert(0 <=\
    \ size);\n        if (size < 0) return {};\n        std::vector<int> result(size);\n\
    \        std::iota(result.begin(), result.end(), first);\n        shuffle(result);\n\
    \        return result;\n    }\n\n    // Returns the edges of a uniformly random\
    \ labeled tree on [0, size).\n    std::vector<std::pair<int, int>> tree(int size)\
    \ {\n        assert(0 <= size);\n        if (size <= 1) return {};\n\n       \
    \ std::vector<int> prufer = sequence(size - 2, 0, size - 1);\n        std::vector<int>\
    \ degree(size, 1);\n        for (int vertex : prufer) degree[vertex]++;\n    \
    \    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;\n \
    \       for (int vertex = 0; vertex < size; vertex++) {\n            if (degree[vertex]\
    \ == 1) leaves.push(vertex);\n        }\n\n        std::vector<std::pair<int,\
    \ int>> edges;\n        edges.reserve(size - 1);\n        for (int vertex : prufer)\
    \ {\n            int leaf = leaves.top();\n            leaves.pop();\n       \
    \     edges.emplace_back(leaf, vertex);\n            if (--degree[vertex] == 1)\
    \ leaves.push(vertex);\n        }\n        int first = leaves.top();\n       \
    \ leaves.pop();\n        edges.emplace_back(first, leaves.top());\n\n        shuffle(edges);\n\
    \        for (auto& [from, to] : edges) {\n            if (uniform(0, 1)) std::swap(from,\
    \ to);\n        }\n        return edges;\n    }\n\n    // Returns m random edges\
    \ on [0, vertex_count). By default the result is\n    // a simple undirected graph\
    \ without self-loops.\n    std::vector<std::pair<int, int>> graph(\n        int\
    \ vertex_count, int edge_count,\n        RandomGraphOptions options = {}) {\n\
    \        assert(0 <= vertex_count);\n        assert(0 <= edge_count);\n      \
    \  if (vertex_count < 0 || edge_count < 0) return {};\n        if (edge_count\
    \ == 0) return {};\n        assert(0 < vertex_count);\n        if (vertex_count\
    \ == 0) return {};\n        if (!options.allow_self_loops) {\n            assert(2\
    \ <= vertex_count || edge_count == 0);\n            if (vertex_count < 2) return\
    \ {};\n        }\n\n        std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        if (options.allow_parallel_edges) {\n            for (int edge = 0; edge\
    \ < edge_count; edge++) {\n                int from = int(uniform(0, vertex_count\
    \ - 1));\n                int to;\n                if (options.allow_self_loops)\
    \ {\n                    to = int(uniform(0, vertex_count - 1));\n           \
    \     } else {\n                    to = int(uniform(0, vertex_count - 2));\n\
    \                    if (from <= to) to++;\n                }\n              \
    \  if (!options.directed && to < from) std::swap(from, to);\n                edges.emplace_back(from,\
    \ to);\n            }\n            return edges;\n        }\n\n        std::uint64_t\
    \ maximum = graph_edge_count(vertex_count, options);\n        assert(static_cast<std::uint64_t>(edge_count)\
    \ <= maximum);\n        if (maximum < static_cast<std::uint64_t>(edge_count))\
    \ return {};\n\n        std::unordered_set<std::uint64_t> selected;\n        selected.reserve(static_cast<std::size_t>(edge_count)\
    \ * 2 + 1);\n        std::vector<std::uint64_t> indices;\n        indices.reserve(edge_count);\n\
    \        for (std::uint64_t current = maximum - edge_count;\n             current\
    \ < maximum; current++) {\n            std::uint64_t candidate = uniform_unsigned(0,\
    \ current);\n            if (selected.contains(candidate)) candidate = current;\n\
    \            selected.insert(candidate);\n            indices.push_back(candidate);\n\
    \        }\n        for (std::uint64_t index : indices) {\n            edges.push_back(decode_graph_edge(index,\
    \ vertex_count, options));\n        }\n        return edges;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> directed_graph(\n        int vertex_count, int edge_count,\n        bool\
    \ allow_self_loops = false) {\n        RandomGraphOptions options;\n        options.allow_self_loops\
    \ = allow_self_loops;\n        return directed_graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    std::vector<std::pair<int, int>> directed_graph(\n \
    \       int vertex_count, int edge_count, RandomGraphOptions options) {\n    \
    \    options.directed = true;\n        return graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    // Returns a directed acyclic graph. Vertices are randomly\
    \ permuted before\n    // every sampled edge is directed forward in that topological\
    \ order.\n    std::vector<std::pair<int, int>> dag(\n        int vertex_count,\
    \ int edge_count,\n        RandomGraphOptions options = {}) {\n        options.directed\
    \ = false;\n        options.allow_self_loops = false;\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<int> order = permutation(vertex_count);\n        for (auto& [from,\
    \ to] : edges) {\n            from = order[from];\n            to = order[to];\n\
    \        }\n        return edges;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_tree(\n        int size, Weight lower, Weight upper)\
    \ {\n        std::vector<std::pair<int, int>> edges = tree(size);\n        std::vector<Weight>\
    \ weights = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_graph(\n        int vertex_count, int edge_count, Weight\
    \ lower, Weight upper,\n        RandomGraphOptions options = {}) {\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);\n\
    \        std::vector<std::tuple<int, int, Weight>> result;\n        result.reserve(edges.size());\n\
    \        for (int index = 0; index < int(edges.size()); index++) {\n         \
    \   result.emplace_back(edges[index].first, edges[index].second,\n           \
    \                     weights[index]);\n        }\n        return result;\n  \
    \  }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   bool allow_self_loops = false) {\n        RandomGraphOptions options;\n  \
    \      options.allow_self_loops = allow_self_loops;\n        return weighted_directed_graph(vertex_count,\
    \ edge_count, lower, upper,\n                                       options);\n\
    \    }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   RandomGraphOptions options) {\n        options.directed = true;\n        return\
    \ weighted_graph(vertex_count, edge_count, lower, upper, options);\n    }\n\n\
    \    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_dag(\n      \
    \  int vertex_count, int edge_count, Weight lower, Weight upper,\n        RandomGraphOptions\
    \ options = {}) {\n        std::vector<std::pair<int, int>> edges =\n        \
    \    dag(vertex_count, edge_count, options);\n        std::vector<Weight> weights\
    \ = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <typename T>\n    void\
    \ shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(), v.end(), _engine);\n\
    \    }\n\n    template <typename Iterator>\n    void shuffle(Iterator first, Iterator\
    \ last) {\n        std::shuffle(first, last, _engine);\n    }\n\n    template\
    \ <typename T>\n    const T& choice(const std::vector<T>& v) {\n        return\
    \ v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/timer.hpp\"\n\n\n\n\
    #line 5 \"utilities/timer.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\n\
    struct Timer {\n   private:\n    using clock = std::chrono::steady_clock;\n\n\
    \    clock::time_point _start;\n    double _limit;\n\n   public:\n    explicit\
    \ Timer(double limit_seconds = 0.0) : _start(clock::now()), _limit(limit_seconds)\
    \ {}\n\n    void reset() {\n        _start = clock::now();\n    }\n\n    void\
    \ set_limit(double limit_seconds) {\n        _limit = limit_seconds;\n    }\n\n\
    \    double elapsed() const {\n        return std::chrono::duration<double>(clock::now()\
    \ - _start).count();\n    }\n\n    long long elapsed_ms() const {\n        return\
    \ std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - _start).count();\n\
    \    }\n\n    bool expired() const {\n        return elapsed() >= _limit;\n  \
    \  }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 16 \"\
    verify/utilities/basic_utilities.test.cpp\"\n\nvoid test_bigint() {\n    using\
    \ m1une::utilities::BigInt;\n\n    const long long min_long_long = std::numeric_limits<long\
    \ long>::min();\n    BigInt minimum(min_long_long);\n    assert(minimum.to_string()\
    \ == std::to_string(min_long_long));\n\n    BigInt scaled = 1;\n    scaled *=\
    \ std::numeric_limits<int>::min();\n    assert(scaled.to_string() == std::to_string(std::numeric_limits<int>::min()));\n\
    \n    BigInt positive = -1;\n    positive *= std::numeric_limits<int>::min();\n\
    \    assert(positive.to_string() == \"2147483648\");\n\n    BigInt negative =\
    \ -5;\n    negative += BigInt(0);\n    assert(negative.to_string() == \"-5\");\n\
    \    negative -= BigInt(0);\n    assert(negative.to_string() == \"-5\");\n\n \
    \   BigInt large(\"12345678901234567890\");\n    assert(large.to_string() == \"\
    12345678901234567890\");\n\n    bool rejected_division_by_zero = false;\n    try\
    \ {\n        (void)(large / BigInt(0));\n    } catch (const std::domain_error&)\
    \ {\n        rejected_division_by_zero = true;\n    }\n    assert(rejected_division_by_zero);\n\
    }\n\nvoid test_int128() {\n    using m1une::utilities::i128;\n    using m1une::utilities::parse_int128;\n\
    \    using m1une::utilities::parse_uint128;\n    using m1une::utilities::to_string;\n\
    \    using m1une::utilities::u128;\n\n    i128 x = parse_int128(\"-170141183460469231731687303715884105\"\
    );\n    assert(to_string(x) == \"-170141183460469231731687303715884105\");\n\n\
    \    u128 y = parse_uint128(\"340282366920938463463374607431768211\");\n    assert(to_string(y)\
    \ == \"340282366920938463463374607431768211\");\n\n    std::stringstream ss;\n\
    \    ss << x << \" \" << y;\n    assert(ss.str() == \"-170141183460469231731687303715884105\
    \ 340282366920938463463374607431768211\");\n\n    i128 read_x;\n    u128 read_y;\n\
    \    ss >> read_x >> read_y;\n    assert(read_x == x);\n    assert(read_y == y);\n\
    }\n\nvoid test_random() {\n    m1une::utilities::Random rng1(42), rng2(42);\n\
    \    for (int i = 0; i < 10; ++i) {\n        assert(rng1() == rng2());\n    }\n\
    \n    for (int i = 0; i < 100; ++i) {\n        long long x = rng1.uniform(-5,\
    \ 5);\n        assert(-5 <= x && x <= 5);\n        double y = rng1.real(-1.0,\
    \ 2.0);\n        assert(-1.0 <= y && y < 2.0);\n    }\n\n    std::vector<int>\
    \ v = {1, 2, 3, 4, 5};\n    rng1.shuffle(v);\n    std::sort(v.begin(), v.end());\n\
    \    assert((v == std::vector<int>{1, 2, 3, 4, 5}));\n    int picked = rng1.choice(v);\n\
    \    assert(1 <= picked && picked <= 5);\n}\n\nvoid test_timer() {\n    m1une::utilities::Timer\
    \ timer(0.0);\n    assert(timer.elapsed() >= 0.0);\n    assert(timer.elapsed_ms()\
    \ >= 0);\n    assert(timer.expired());\n    timer.set_limit(1000000.0);\n    timer.reset();\n\
    \    assert(!timer.expired());\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_bigint();\n\
    \    test_int128();\n    test_random();\n    test_timer();\n\n    long long a,\
    \ b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../utilities/fast_io.hpp\"\n#include <limits>\n\
    #include <sstream>\n#include <stdexcept>\n#include <string>\n#include <vector>\n\
    \n#include \"../../utilities/bigint.hpp\"\n#include \"../../utilities/int128.hpp\"\
    \n#include \"../../utilities/random.hpp\"\n#include \"../../utilities/timer.hpp\"\
    \n\nvoid test_bigint() {\n    using m1une::utilities::BigInt;\n\n    const long\
    \ long min_long_long = std::numeric_limits<long long>::min();\n    BigInt minimum(min_long_long);\n\
    \    assert(minimum.to_string() == std::to_string(min_long_long));\n\n    BigInt\
    \ scaled = 1;\n    scaled *= std::numeric_limits<int>::min();\n    assert(scaled.to_string()\
    \ == std::to_string(std::numeric_limits<int>::min()));\n\n    BigInt positive\
    \ = -1;\n    positive *= std::numeric_limits<int>::min();\n    assert(positive.to_string()\
    \ == \"2147483648\");\n\n    BigInt negative = -5;\n    negative += BigInt(0);\n\
    \    assert(negative.to_string() == \"-5\");\n    negative -= BigInt(0);\n   \
    \ assert(negative.to_string() == \"-5\");\n\n    BigInt large(\"12345678901234567890\"\
    );\n    assert(large.to_string() == \"12345678901234567890\");\n\n    bool rejected_division_by_zero\
    \ = false;\n    try {\n        (void)(large / BigInt(0));\n    } catch (const\
    \ std::domain_error&) {\n        rejected_division_by_zero = true;\n    }\n  \
    \  assert(rejected_division_by_zero);\n}\n\nvoid test_int128() {\n    using m1une::utilities::i128;\n\
    \    using m1une::utilities::parse_int128;\n    using m1une::utilities::parse_uint128;\n\
    \    using m1une::utilities::to_string;\n    using m1une::utilities::u128;\n\n\
    \    i128 x = parse_int128(\"-170141183460469231731687303715884105\");\n    assert(to_string(x)\
    \ == \"-170141183460469231731687303715884105\");\n\n    u128 y = parse_uint128(\"\
    340282366920938463463374607431768211\");\n    assert(to_string(y) == \"340282366920938463463374607431768211\"\
    );\n\n    std::stringstream ss;\n    ss << x << \" \" << y;\n    assert(ss.str()\
    \ == \"-170141183460469231731687303715884105 340282366920938463463374607431768211\"\
    );\n\n    i128 read_x;\n    u128 read_y;\n    ss >> read_x >> read_y;\n    assert(read_x\
    \ == x);\n    assert(read_y == y);\n}\n\nvoid test_random() {\n    m1une::utilities::Random\
    \ rng1(42), rng2(42);\n    for (int i = 0; i < 10; ++i) {\n        assert(rng1()\
    \ == rng2());\n    }\n\n    for (int i = 0; i < 100; ++i) {\n        long long\
    \ x = rng1.uniform(-5, 5);\n        assert(-5 <= x && x <= 5);\n        double\
    \ y = rng1.real(-1.0, 2.0);\n        assert(-1.0 <= y && y < 2.0);\n    }\n\n\
    \    std::vector<int> v = {1, 2, 3, 4, 5};\n    rng1.shuffle(v);\n    std::sort(v.begin(),\
    \ v.end());\n    assert((v == std::vector<int>{1, 2, 3, 4, 5}));\n    int picked\
    \ = rng1.choice(v);\n    assert(1 <= picked && picked <= 5);\n}\n\nvoid test_timer()\
    \ {\n    m1une::utilities::Timer timer(0.0);\n    assert(timer.elapsed() >= 0.0);\n\
    \    assert(timer.elapsed_ms() >= 0);\n    assert(timer.expired());\n    timer.set_limit(1000000.0);\n\
    \    timer.reset();\n    assert(!timer.expired());\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_bigint();\n\
    \    test_int128();\n    test_random();\n    test_timer();\n\n    long long a,\
    \ b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - utilities/bigint.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - utilities/int128.hpp
  - utilities/random.hpp
  - utilities/timer.hpp
  isVerificationFile: true
  path: verify/utilities/basic_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 20:24:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/basic_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/basic_utilities.test.cpp
- /verify/verify/utilities/basic_utilities.test.cpp.html
title: verify/utilities/basic_utilities.test.cpp
---
