---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':heavy_check_mark:'
    path: math/fps/composition.hpp
    title: Formal Power Series Composition
  - icon: ':heavy_check_mark:'
    path: math/fps/compositional_inverse.hpp
    title: Compositional Inverse of Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/geometric_sequence_evaluation.hpp
    title: Geometric-Sequence Polynomial Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrences and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/fps/polynomial_factorization.hpp
    title: Polynomial Factorization
  - icon: ':heavy_check_mark:'
    path: math/fps/polynomial_roots.hpp
    title: Polynomial Roots over a Finite Field
  - icon: ':heavy_check_mark:'
    path: math/fps/sparse_formal_power_series.hpp
    title: Sparse Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
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
  bundledCode: "#line 1 \"verify/math/fps/fps_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/math/fps/fps_algorithms.test.cpp\"\
    \n#include <random>\n#line 8 \"verify/math/fps/fps_algorithms.test.cpp\"\n#include\
    \ <vector>\n\n#line 1 \"math/fps/all.hpp\"\n\n\n\n#line 1 \"math/fps/composition.hpp\"\
    \n\n\n\n#line 10 \"math/fps/composition.hpp\"\n\n#line 1 \"math/fps/formal_power_series.hpp\"\
    \n\n\n\n#line 7 \"math/fps/formal_power_series.hpp\"\n#include <optional>\n#line\
    \ 10 \"math/fps/formal_power_series.hpp\"\n\n#line 1 \"math/modular_square_root.hpp\"\
    \n\n\n\n#line 7 \"math/modular_square_root.hpp\"\n\nnamespace m1une {\nnamespace\
    \ math {\n\nnamespace internal {\n\ninline uint64_t modular_square_root_multiply(uint64_t\
    \ lhs, uint64_t rhs, uint64_t mod) {\n    return static_cast<uint64_t>(static_cast<unsigned\
    \ __int128>(lhs) * rhs % mod);\n}\n\ninline uint64_t modular_square_root_power(uint64_t\
    \ base, uint64_t exponent, uint64_t mod) {\n    uint64_t result = 1 % mod;\n \
    \   while (exponent > 0) {\n        if (exponent & 1) result = modular_square_root_multiply(result,\
    \ base, mod);\n        base = modular_square_root_multiply(base, base, mod);\n\
    \        exponent >>= 1;\n    }\n    return result;\n}\n\n}  // namespace internal\n\
    \n// Returns x such that x * x = value (mod prime), or nullopt when no such x\
    \ exists.\n// The modulus must be prime.\ninline std::optional<uint64_t> modular_square_root(uint64_t\
    \ value, uint64_t prime) {\n    assert(prime >= 2);\n    value %= prime;\n   \
    \ if (value == 0 || prime == 2) return value;\n\n    if (internal::modular_square_root_power(value,\
    \ (prime - 1) / 2, prime) != 1) {\n        return std::nullopt;\n    }\n    if\
    \ (prime % 4 == 3) {\n        return internal::modular_square_root_power(value,\
    \ prime / 4 + 1, prime);\n    }\n\n    uint64_t odd_part = prime - 1;\n    int\
    \ power_of_two = 0;\n    while ((odd_part & 1) == 0) {\n        odd_part >>= 1;\n\
    \        power_of_two++;\n    }\n\n    uint64_t non_residue = 2;\n    while (internal::modular_square_root_power(non_residue,\
    \ (prime - 1) / 2, prime) == 1) {\n        non_residue++;\n    }\n\n    uint64_t\
    \ c = internal::modular_square_root_power(non_residue, odd_part, prime);\n   \
    \ uint64_t root = internal::modular_square_root_power(value, odd_part / 2 + 1,\
    \ prime);\n    uint64_t remainder = internal::modular_square_root_power(value,\
    \ odd_part, prime);\n    int remaining_power = power_of_two;\n\n    while (remainder\
    \ != 1) {\n        int exponent = 1;\n        uint64_t squared = internal::modular_square_root_multiply(remainder,\
    \ remainder, prime);\n        while (squared != 1) {\n            squared = internal::modular_square_root_multiply(squared,\
    \ squared, prime);\n            exponent++;\n        }\n\n        uint64_t correction\
    \ = c;\n        for (int i = 0; i < remaining_power - exponent - 1; i++) {\n \
    \           correction = internal::modular_square_root_multiply(correction, correction,\
    \ prime);\n        }\n        root = internal::modular_square_root_multiply(root,\
    \ correction, prime);\n        c = internal::modular_square_root_multiply(correction,\
    \ correction, prime);\n        remainder = internal::modular_square_root_multiply(remainder,\
    \ c, prime);\n        remaining_power = exponent;\n    }\n    return root;\n}\n\
    \ntemplate <class Mint>\nstd::optional<Mint> modular_square_root(Mint value) {\n\
    \    auto root = modular_square_root(static_cast<uint64_t>(value.val()),\n   \
    \                                 static_cast<uint64_t>(Mint::mod()));\n    if\
    \ (!root.has_value()) return std::nullopt;\n    return Mint(*root);\n}\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n#line 1 \"math/fps/convolution.hpp\"\
    \n\n\n\n#line 9 \"math/fps/convolution.hpp\"\n#include <new>\n#line 13 \"math/fps/convolution.hpp\"\
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
    #endif\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include\
    \ <iostream>\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math\
    \ {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus,\
    \ \"Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
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
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 13 \"math/fps/formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct FormalPowerSeries\
    \ : std::vector<Mint> {\n    using std::vector<Mint>::vector;\n    using Fps =\
    \ FormalPowerSeries;\n\n    FormalPowerSeries() = default;\n    FormalPowerSeries(const\
    \ std::vector<Mint>& values) : std::vector<Mint>(values) {}\n    FormalPowerSeries(std::vector<Mint>&&\
    \ values) : std::vector<Mint>(std::move(values)) {}\n\n    Fps& shrink() {\n \
    \       while (!this->empty() && this->back() == Mint(0)) this->pop_back();\n\
    \        return *this;\n    }\n\n    Fps pre(int degree) const {\n        assert(degree\
    \ >= 0);\n        Fps result(this->begin(), this->begin() + std::min<int>(degree,\
    \ this->size()));\n        result.resize(degree);\n        return result;\n  \
    \  }\n\n    Fps reversed(int size = -1) const {\n        Fps result = *this;\n\
    \        if (size >= 0) result.resize(size);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    Fps& operator+=(const Fps&\
    \ rhs) {\n        if (this->size() < rhs.size()) this->resize(rhs.size());\n \
    \       for (int i = 0; i < int(rhs.size()); i++) (*this)[i] += rhs[i];\n    \
    \    return *this;\n    }\n\n    Fps& operator-=(const Fps& rhs) {\n        if\
    \ (this->size() < rhs.size()) this->resize(rhs.size());\n        for (int i =\
    \ 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];\n        return *this;\n\
    \    }\n\n    Fps& operator*=(const Fps& rhs) {\n        std::vector<Mint> lhs(this->begin(),\
    \ this->end());\n        *this = convolution(lhs, rhs);\n        return *this;\n\
    \    }\n\n    Fps& operator*=(Mint rhs) {\n        for (Mint& value : *this) value\
    \ *= rhs;\n        return *this;\n    }\n\n    Fps& operator/=(Mint rhs) {\n \
    \       return *this *= rhs.inv();\n    }\n\n    Fps& operator<<=(int shift) {\n\
    \        assert(shift >= 0);\n        this->insert(this->begin(), shift, Mint(0));\n\
    \        return *this;\n    }\n\n    Fps& operator>>=(int shift) {\n        assert(shift\
    \ >= 0);\n        if (shift >= int(this->size())) {\n            this->clear();\n\
    \        } else {\n            this->erase(this->begin(), this->begin() + shift);\n\
    \        }\n        return *this;\n    }\n\n    Fps operator+() const {\n    \
    \    return *this;\n    }\n\n    Fps operator-() const {\n        Fps result =\
    \ *this;\n        for (Mint& value : result) value = Mint(0) - value;\n      \
    \  return result;\n    }\n\n    friend Fps operator+(Fps lhs, const Fps& rhs)\
    \ {\n        return lhs += rhs;\n    }\n\n    friend Fps operator-(Fps lhs, const\
    \ Fps& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Fps operator*(Fps\
    \ lhs, const Fps& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Fps\
    \ operator*(Fps lhs, Mint rhs) {\n        return lhs *= rhs;\n    }\n\n    friend\
    \ Fps operator*(Mint lhs, Fps rhs) {\n        return rhs *= lhs;\n    }\n\n  \
    \  friend Fps operator/(Fps lhs, Mint rhs) {\n        return lhs /= rhs;\n   \
    \ }\n\n    friend Fps operator<<(Fps lhs, int shift) {\n        return lhs <<=\
    \ shift;\n    }\n\n    friend Fps operator>>(Fps lhs, int shift) {\n        return\
    \ lhs >>= shift;\n    }\n\n    Fps derivative() const {\n        if (this->empty())\
    \ return {};\n        Fps result(this->size() - 1);\n        for (int i = 1; i\
    \ < int(this->size()); i++) result[i - 1] = (*this)[i] * Mint(i);\n        return\
    \ result;\n    }\n\n    Fps integral() const {\n        Fps result(this->size()\
    \ + 1);\n        if (this->empty()) return result;\n        assert(this->size()\
    \ < Mint::mod());\n\n        std::vector<Mint> inverse(this->size() + 1);\n  \
    \      inverse[1] = 1;\n        for (int i = 2; i <= int(this->size()); i++) {\n\
    \            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod()\
    \ % uint32_t(i)];\n        }\n        for (int i = 0; i < int(this->size()); i++)\
    \ result[i + 1] = (*this)[i] * inverse[i + 1];\n        return result;\n    }\n\
    \n    Mint evaluate(Mint x) const {\n        Mint result = 0;\n        for (auto\
    \ it = this->rbegin(); it != this->rend(); ++it) result = result * x + *it;\n\
    \        return result;\n    }\n\n    Fps inv(int degree = -1) const {\n     \
    \   if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ != Mint(0));\n\n        Fps result(1, (*this)[0].inv());\n        for (int size\
    \ = 1; size < degree; size <<= 1) {\n            const int next_size = std::min(size\
    \ << 1, degree);\n            const int transform_size = size << 1;\n        \
    \    if (size >= 32 && (Mint::mod() - 1) % uint32_t(transform_size) == 0) {\n\
    \                // Newton's g <- g(2-fg), restricted to the newly determined\n\
    \                // half.  Keeping g in the frequency domain avoids two general\n\
    \                // convolutions and their 2x larger padding.\n              \
    \  std::vector<Mint> transformed_f(transform_size);\n                std::copy_n(this->begin(),\
    \ std::min<int>(this->size(), next_size),\n                            transformed_f.begin());\n\
    \                std::vector<Mint> transformed_g(transform_size);\n          \
    \      std::copy(result.begin(), result.end(), transformed_g.begin());\n     \
    \           internal::ntt(transformed_f, false);\n                internal::ntt(transformed_g,\
    \ false);\n\n                std::vector<Mint> error(transform_size);\n      \
    \          for (int i = 0; i < transform_size; i++)\n                    error[i]\
    \ = transformed_f[i] * transformed_g[i];\n                internal::ntt(error,\
    \ true);\n                std::fill(error.begin(), error.begin() + size, Mint(0));\n\
    \                internal::ntt(error, false);\n                for (int i = 0;\
    \ i < transform_size; i++) error[i] *= transformed_g[i];\n                internal::ntt(error,\
    \ true);\n\n                result.resize(next_size);\n                for (int\
    \ i = size; i < next_size; i++) result[i] = Mint(0) - error[i];\n            \
    \    continue;\n            }\n            Fps product = this->pre(next_size)\
    \ * result;\n            product.resize(next_size);\n            for (Mint& value\
    \ : product) value = Mint(0) - value;\n            product[0] += Mint(2);\n  \
    \          result = (result * product).pre(next_size);\n        }\n        return\
    \ result.pre(degree);\n    }\n\n    Fps log(int degree = -1) const {\n       \
    \ if (degree < 0) degree = int(this->size());\n        assert(degree >= 0);\n\
    \        if (degree == 0) return {};\n        assert(!this->empty() && (*this)[0]\
    \ == Mint(1));\n        return (derivative() * inv(degree)).pre(degree - 1).integral();\n\
    \    }\n\n    Fps exp(int degree = -1) const {\n        if (degree < 0) degree\
    \ = int(this->size());\n        assert(degree >= 0);\n        if (degree == 0)\
    \ return {};\n        assert(this->empty() || (*this)[0] == Mint(0));\n\n    \
    \    Fps result(1, Mint(1));\n        for (int size = 1; size < degree; size <<=\
    \ 1) {\n            const int next_size = std::min(size << 1, degree);\n     \
    \       Fps correction = this->pre(next_size) - result.log(next_size);\n     \
    \       correction[0] += Mint(1);\n            result = (result * correction).pre(next_size);\n\
    \        }\n        return result.pre(degree);\n    }\n\n    Fps pow(long long\
    \ exponent, int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(exponent >= 0 && degree >= 0);\n        if (degree == 0) return\
    \ {};\n        if (exponent == 0) {\n            Fps result(degree);\n       \
    \     result[0] = 1;\n            return result;\n        }\n\n        int first\
    \ = 0;\n        while (first < int(this->size()) && (*this)[first] == Mint(0))\
    \ first++;\n        if (first == int(this->size()) || first > (degree - 1) / exponent)\
    \ return Fps(degree);\n\n        const int shift = int(first * exponent);\n  \
    \      const Mint leading = (*this)[first];\n        Fps normalized = (*this >>\
    \ first) / leading;\n        Fps result = (normalized.log(degree - shift) * Mint(exponent)).exp(degree\
    \ - shift);\n        result *= leading.pow(exponent);\n        result <<= shift;\n\
    \        result.resize(degree);\n        return result;\n    }\n\n    std::optional<Fps>\
    \ sqrt(int degree = -1) const {\n        if (degree < 0) degree = int(this->size());\n\
    \        assert(degree >= 0);\n        if (degree == 0) return Fps();\n\n    \
    \    int first = 0;\n        while (first < int(this->size()) && (*this)[first]\
    \ == Mint(0)) first++;\n        if (first == int(this->size())) return Fps(degree);\n\
    \        if (first >= degree) return Fps(degree);\n        if (first & 1) return\
    \ std::nullopt;\n\n        const int shift = first / 2;\n        auto leading_root\
    \ = m1une::math::modular_square_root((*this)[first]);\n        if (!leading_root.has_value())\
    \ return std::nullopt;\n\n        const int result_degree = degree - shift;\n\
    \        Fps normalized = (*this >> first) / (*this)[first];\n        Fps result\
    \ = (normalized.log(result_degree) / Mint(2)).exp(result_degree);\n        result\
    \ *= *leading_root;\n        result <<= shift;\n        result.resize(degree);\n\
    \        return result;\n    }\n\n    std::pair<Fps, Fps> divmod(const Fps& divisor)\
    \ const {\n        Fps dividend = *this;\n        Fps normalized_divisor = divisor;\n\
    \        dividend.shrink();\n        normalized_divisor.shrink();\n        assert(!normalized_divisor.empty());\n\
    \n        if (dividend.size() < normalized_divisor.size()) return std::make_pair(Fps(),\
    \ dividend);\n        const int quotient_size = int(dividend.size() - normalized_divisor.size()\
    \ + 1);\n        Fps quotient =\n            (dividend.reversed().pre(quotient_size)\
    \ * normalized_divisor.reversed().inv(quotient_size))\n                .pre(quotient_size)\n\
    \                .reversed();\n        quotient.shrink();\n        Fps remainder\
    \ = dividend - normalized_divisor * quotient;\n        remainder.resize(normalized_divisor.size()\
    \ - 1);\n        remainder.shrink();\n        return std::make_pair(std::move(quotient),\
    \ std::move(remainder));\n    }\n\n    Fps& operator/=(const Fps& rhs) {\n   \
    \     *this = divmod(rhs).first;\n        return *this;\n    }\n\n    Fps& operator%=(const\
    \ Fps& rhs) {\n        *this = divmod(rhs).second;\n        return *this;\n  \
    \  }\n\n    friend Fps operator/(Fps lhs, const Fps& rhs) {\n        return lhs\
    \ /= rhs;\n    }\n\n    friend Fps operator%(Fps lhs, const Fps& rhs) {\n    \
    \    return lhs %= rhs;\n    }\n\n    Fps taylor_shift(Mint shift) const {\n \
    \       const int n = int(this->size());\n        if (n == 0) return {};\n   \
    \     assert(uint32_t(n) < Mint::mod());\n\n        std::vector<Mint> factorial(n,\
    \ Mint(1));\n        std::vector<Mint> inverse_factorial(n, Mint(1));\n      \
    \  for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * Mint(i);\n  \
    \      inverse_factorial[n - 1] = factorial[n - 1].inv();\n        for (int i\
    \ = n - 1; i > 0; i--) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);\n\
    \n        Fps left(n);\n        Fps right(n);\n        Mint power = 1;\n     \
    \   for (int i = 0; i < n; i++) {\n            left[n - 1 - i] = (*this)[i] *\
    \ factorial[i];\n            right[i] = power * inverse_factorial[i];\n      \
    \      power *= shift;\n        }\n        Fps product = left * right;\n     \
    \   Fps result(n);\n        for (int i = 0; i < n; i++) result[i] = product[n\
    \ - 1 - i] * inverse_factorial[i];\n        return result;\n    }\n};\n\n}  //\
    \ namespace fps\n}  // namespace m1une\n\n\n#line 12 \"math/fps/composition.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nusing CompositionMatrix = std::vector<std::vector<Mint>>;\n\ntemplate\
    \ <class Mint>\nCompositionMatrix<Mint> composition_convolution_2d(const CompositionMatrix<Mint>&\
    \ lhs,\n                                                   const CompositionMatrix<Mint>&\
    \ rhs) {\n    const int lhs_height = int(lhs.size());\n    const int rhs_height\
    \ = int(rhs.size());\n    const int lhs_width = int(lhs[0].size());\n    const\
    \ int rhs_width = int(rhs[0].size());\n    const int height = lhs_height + rhs_height\
    \ - 1;\n    const int width = lhs_width + rhs_width - 1;\n\n    std::vector<Mint>\
    \ flattened_lhs(std::size_t(lhs_height) * width);\n    std::vector<Mint> flattened_rhs(std::size_t(rhs_height)\
    \ * width);\n    for (int i = 0; i < lhs_height; i++) {\n        std::copy(lhs[i].begin(),\
    \ lhs[i].end(),\n                  flattened_lhs.begin() + std::size_t(i) * width);\n\
    \    }\n    for (int i = 0; i < rhs_height; i++) {\n        std::copy(rhs[i].begin(),\
    \ rhs[i].end(),\n                  flattened_rhs.begin() + std::size_t(i) * width);\n\
    \    }\n\n    std::vector<Mint> flattened_result = convolution(flattened_lhs,\
    \ flattened_rhs);\n    CompositionMatrix<Mint> result(height, std::vector<Mint>(width));\n\
    \    for (int i = 0; i < height; i++) {\n        std::copy_n(flattened_result.begin()\
    \ + std::size_t(i) * width, width,\n                    result[i].begin());\n\
    \    }\n    return result;\n}\n\n// result[i] = sum_j kernel[j] * values[i + j]\n\
    template <class Mint>\nstd::vector<Mint> composition_middle_product(const std::vector<Mint>&\
    \ values,\n                                             const std::vector<Mint>&\
    \ kernel) {\n    assert(values.size() >= kernel.size() && !kernel.empty());\n\
    \    const int kernel_size = int(kernel.size());\n    const int result_size =\
    \ int(values.size()) - kernel_size + 1;\n    if (std::min(kernel_size, result_size)\
    \ <= 32) {\n        std::vector<Mint> result(result_size);\n        for (int i\
    \ = 0; i < result_size; i++) {\n            for (int j = 0; j < kernel_size; j++)\
    \ result[i] += kernel[j] * values[i + j];\n        }\n        return result;\n\
    \    }\n\n    int transform_size = 1;\n    while ((transform_size << 1) <= int(values.size())\
    \ * 2 - 1) transform_size <<= 1;\n    if ((Mint::mod() - 1) % uint32_t(transform_size)\
    \ == 0) {\n        std::vector<Mint> transformed_values(transform_size);\n   \
    \     std::vector<Mint> transformed_kernel(transform_size);\n        std::copy(values.begin(),\
    \ values.end(), transformed_values.begin());\n        std::reverse_copy(kernel.begin(),\
    \ kernel.end(), transformed_kernel.begin());\n        ntt(transformed_values,\
    \ false);\n        ntt(transformed_kernel, false);\n        for (int i = 0; i\
    \ < transform_size; i++) transformed_values[i] *= transformed_kernel[i];\n   \
    \     ntt(transformed_values, true);\n        return std::vector<Mint>(transformed_values.begin()\
    \ + kernel_size - 1,\n                                 transformed_values.begin()\
    \ + int(values.size()));\n    }\n\n    std::vector<Mint> reversed_kernel(kernel.rbegin(),\
    \ kernel.rend());\n    std::vector<Mint> product = convolution(values, reversed_kernel);\n\
    \    return std::vector<Mint>(product.begin() + kernel_size - 1,\n           \
    \                  product.begin() + int(values.size()));\n}\n\n}  // namespace\
    \ internal\n\n// Returns outer(inner(x)) modulo x^degree. Formal composition requires\
    \ inner(0) = 0.\ntemplate <class Mint>\nFormalPowerSeries<Mint> compose(const\
    \ FormalPowerSeries<Mint>& outer,\n                                const FormalPowerSeries<Mint>&\
    \ inner, int degree = -1) {\n    using Matrix = internal::CompositionMatrix<Mint>;\n\
    \    if (degree < 0) degree = int(outer.size());\n    assert(degree >= 0);\n \
    \   if (degree == 0) return {};\n    assert(inner.empty() || inner[0] == Mint(0));\n\
    \n    FormalPowerSeries<Mint> coefficients = outer.pre(degree);\n    FormalPowerSeries<Mint>\
    \ argument = inner.pre(degree);\n\n    auto transpose_power_projection = [&](auto&&\
    \ self, Matrix denominator) -> Matrix {\n        const int x_degree = int(denominator.size())\
    \ - 1;\n        const int y_degree = int(denominator[0].size()) - 1;\n       \
    \ if (x_degree == 0) {\n            Matrix result(1, std::vector<Mint>(y_degree\
    \ + 1));\n            std::copy(coefficients.begin(), coefficients.end(), result[0].begin());\n\
    \            return result;\n        }\n\n        Matrix conjugate = denominator;\n\
    \        for (int i = 1; i <= x_degree; i += 2) {\n            for (Mint& value\
    \ : conjugate[i]) value = Mint(0) - value;\n        }\n        Matrix reduced\
    \ = internal::composition_convolution_2d(denominator, conjugate);\n        for\
    \ (int i = 1; i <= x_degree / 2; i++) reduced[i] = std::move(reduced[i << 1]);\n\
    \        reduced.resize(x_degree / 2 + 1);\n        Matrix().swap(denominator);\n\
    \n        Matrix projected = self(self, std::move(reduced));\n        const int\
    \ block_width = 2 * y_degree + 1;\n        std::vector<Mint> expanded(std::size_t(2)\
    \ * (x_degree + 1) * block_width - 1);\n        for (int i = 0; i < int(projected.size());\
    \ i++) {\n            for (int j = 0; j < int(projected[i].size()); j++) {\n \
    \               const int row = 2 * i + (x_degree & 1);\n                expanded[std::size_t(row)\
    \ * block_width + j] = projected[i][j];\n            }\n        }\n\n        std::vector<Mint>\
    \ flattened_conjugate(std::size_t(x_degree + 1) * block_width);\n        for (int\
    \ i = 0; i <= x_degree; i++) {\n            std::copy(conjugate[i].begin(), conjugate[i].end(),\n\
    \                      flattened_conjugate.begin() + std::size_t(i) * block_width);\n\
    \        }\n        std::vector<Mint> middle =\n            internal::composition_middle_product(expanded,\
    \ flattened_conjugate);\n\n        Matrix result(x_degree + 1, std::vector<Mint>(y_degree\
    \ + 1));\n        for (int i = 0; i <= x_degree; i++) {\n            std::copy_n(middle.begin()\
    \ + std::size_t(i) * block_width, y_degree + 1,\n                        result[i].begin());\n\
    \        }\n        return result;\n    };\n\n    Matrix denominator(degree, std::vector<Mint>(2));\n\
    \    denominator[0][0] = Mint(1);\n    for (int i = 0; i < degree; i++) denominator[i][1]\
    \ = Mint(0) - argument[i];\n    Matrix transposed =\n        transpose_power_projection(transpose_power_projection,\
    \ std::move(denominator));\n\n    FormalPowerSeries<Mint> result(degree);\n  \
    \  for (int i = 0; i < degree; i++) result[i] = transposed[i][0];\n    std::reverse(result.begin(),\
    \ result.end());\n    return result;\n}\n\n}  // namespace fps\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/fps/compositional_inverse.hpp\"\n\n\n\n#line 6 \"\
    math/fps/compositional_inverse.hpp\"\n\n#line 8 \"math/fps/compositional_inverse.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ compositional_inverse(const FormalPowerSeries<Mint>& f,\n                  \
    \                            int degree = -1) {\n    using Fps = FormalPowerSeries<Mint>;\n\
    \    if (degree < 0) degree = int(f.size());\n    assert(degree >= 0);\n    if\
    \ (degree == 0) return {};\n    assert(f.size() >= 2 && f[0] == Mint(0) && f[1]\
    \ != Mint(0));\n\n    Fps result(2);\n    result[1] = f[1].inv();\n    if (degree\
    \ == 1) return result.pre(1);\n\n    for (int size = 2; size < degree;) {\n  \
    \      const int next_size = std::min(size << 1, degree);\n        Fps composed\
    \ = compose(f.pre(next_size), result, next_size);\n        const int correction_size\
    \ = next_size - size;\n        Fps inverse_derivative = composed.derivative().inv(correction_size);\n\
    \        composed[1] -= Mint(1);\n        Fps inverse_jacobian =\n           \
    \ (result.derivative().pre(correction_size) * inverse_derivative)\n          \
    \      .pre(correction_size);\n        Fps correction = ((composed >> size) *\
    \ inverse_jacobian).pre(correction_size);\n        correction <<= size;\n\n  \
    \      result = result.pre(next_size) - correction;\n        result.resize(next_size);\n\
    \        size = next_size;\n    }\n    return result.pre(degree);\n}\n\n}  //\
    \ namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/convolution_ll.hpp\"\
    \n\n\n\n#line 6 \"math/fps/convolution_ll.hpp\"\n#include <limits>\n#line 8 \"\
    math/fps/convolution_ll.hpp\"\n\n#line 11 \"math/fps/convolution_ll.hpp\"\n\n\
    namespace m1une {\nnamespace fps {\n\n// Exact convolution of signed 64-bit coefficients.\n\
    // Every result coefficient must fit in long long.\ninline std::vector<long long>\
    \ convolution_ll(\n    const std::vector<long long>& first,\n    const std::vector<long\
    \ long>& second\n) {\n    if (first.empty() || second.empty()) return {};\n  \
    \  std::size_t result_size = first.size() + second.size() - 1;\n    assert(result_size\
    \ <= (std::size_t(1) << 24));\n\n    using Mint1 = math::ModInt<167772161>;\n\
    \    using Mint2 = math::ModInt<469762049>;\n    using Mint3 = math::ModInt<754974721>;\n\
    \n    auto convolve = [&]<class Mint>() {\n        std::vector<Mint> converted_first(first.size());\n\
    \        std::vector<Mint> converted_second(second.size());\n        for (int\
    \ index = 0; index < int(first.size()); index++) {\n            converted_first[index]\
    \ = Mint(first[index]);\n        }\n        for (int index = 0; index < int(second.size());\
    \ index++) {\n            converted_second[index] = Mint(second[index]);\n   \
    \     }\n        return convolution(converted_first, converted_second);\n    };\n\
    \n    std::vector<Mint1> result1 = convolve.template operator()<Mint1>();\n  \
    \  std::vector<Mint2> result2 = convolve.template operator()<Mint2>();\n    std::vector<Mint3>\
    \ result3 = convolve.template operator()<Mint3>();\n\n    static const std::uint64_t\
    \ inverse_mod1_mod2 =\n        Mint2(Mint1::mod()).inv().val();\n    static const\
    \ std::uint64_t mod1_mod2 =\n        std::uint64_t(Mint1::mod()) * Mint2::mod();\n\
    \    static const std::uint64_t inverse_mod1_mod2_mod3 =\n        Mint3(mod1_mod2\
    \ % Mint3::mod()).inv().val();\n    static const unsigned __int128 crt_modulus\
    \ =\n        static_cast<unsigned __int128>(mod1_mod2) * Mint3::mod();\n\n   \
    \ std::vector<long long> result(result_size);\n    for (int index = 0; index <\
    \ int(result_size); index++) {\n        std::uint64_t residue1 = result1[index].val();\n\
    \        std::uint64_t residue2 = result2[index].val();\n        std::uint64_t\
    \ residue3 = result3[index].val();\n\n        std::uint64_t second_digit =\n \
    \           (residue2 + Mint2::mod() - residue1 % Mint2::mod()) %\n          \
    \  Mint2::mod();\n        second_digit = second_digit * inverse_mod1_mod2 % Mint2::mod();\n\
    \        std::uint64_t first_two =\n            residue1 + std::uint64_t(Mint1::mod())\
    \ * second_digit;\n\n        std::uint64_t third_digit =\n            (residue3\
    \ + Mint3::mod() - first_two % Mint3::mod()) %\n            Mint3::mod();\n  \
    \      third_digit =\n            third_digit * inverse_mod1_mod2_mod3 % Mint3::mod();\n\
    \n        unsigned __int128 reconstructed =\n            first_two + static_cast<unsigned\
    \ __int128>(mod1_mod2) * third_digit;\n        __int128 centered = reconstructed\
    \ <= crt_modulus / 2\n                                ? static_cast<__int128>(reconstructed)\n\
    \                                : -static_cast<__int128>(crt_modulus - reconstructed);\n\
    \        assert(std::numeric_limits<long long>::min() <= centered);\n        assert(centered\
    \ <= std::numeric_limits<long long>::max());\n        result[index] = static_cast<long\
    \ long>(centered);\n    }\n    return result;\n}\n\n}  // namespace fps\n}  //\
    \ namespace m1une\n\n\n#line 1 \"math/fps/floating_point_convolution.hpp\"\n\n\
    \n\n#line 5 \"math/fps/floating_point_convolution.hpp\"\n#include <bit>\n#include\
    \ <cmath>\n#include <complex>\n#include <concepts>\n#include <numbers>\n#line\
    \ 12 \"math/fps/floating_point_convolution.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\nnamespace floating_point_convolution_detail {\n\ntemplate <std::floating_point\
    \ Real>\nvoid fft(std::vector<std::complex<Real>>& values, bool inverse) {\n \
    \   int size = int(values.size());\n    for (int index = 1, reversed = 0; index\
    \ < size; ++index) {\n        int bit = size >> 1;\n        while (reversed &\
    \ bit) {\n            reversed ^= bit;\n            bit >>= 1;\n        }\n  \
    \      reversed ^= bit;\n        if (index < reversed) std::swap(values[index],\
    \ values[reversed]);\n    }\n\n    for (int length = 2; length <= size; length\
    \ <<= 1) {\n        Real angle = Real(2) * std::numbers::pi_v<Real> / Real(length);\n\
    \        if (inverse) angle = -angle;\n        std::complex<Real> step(std::cos(angle),\
    \ std::sin(angle));\n        int half = length >> 1;\n        for (int offset\
    \ = 0; offset < size; offset += length) {\n            std::complex<Real> root(1,\
    \ 0);\n            for (int index = 0; index < half; ++index) {\n            \
    \    std::complex<Real> even = values[offset + index];\n                std::complex<Real>\
    \ odd = values[offset + index + half] * root;\n                values[offset +\
    \ index] = even + odd;\n                values[offset + index + half] = even -\
    \ odd;\n                root *= step;\n            }\n        }\n    }\n\n   \
    \ if (inverse) {\n        Real inverse_size = Real(1) / Real(size);\n        for\
    \ (auto& value : values) value *= inverse_size;\n    }\n}\n\ntemplate <std::floating_point\
    \ Real>\nstd::vector<std::complex<Real>> complex_convolution(const std::vector<std::complex<Real>>&\
    \ first,\n                                                    const std::vector<std::complex<Real>>&\
    \ second) {\n    if (first.empty() || second.empty()) return {};\n    std::size_t\
    \ result_size = first.size() + second.size() - 1;\n    std::size_t size = std::bit_ceil(result_size);\n\
    \    std::vector<std::complex<Real>> transformed_first(size);\n    std::vector<std::complex<Real>>\
    \ transformed_second(size);\n    std::copy(first.begin(), first.end(), transformed_first.begin());\n\
    \    std::copy(second.begin(), second.end(), transformed_second.begin());\n\n\
    \    fft(transformed_first, false);\n    fft(transformed_second, false);\n   \
    \ for (std::size_t index = 0; index < size; ++index) {\n        transformed_first[index]\
    \ *= transformed_second[index];\n    }\n    fft(transformed_first, true);\n  \
    \  transformed_first.resize(result_size);\n    return transformed_first;\n}\n\n\
    }  // namespace floating_point_convolution_detail\n\n// Convolution of complex\
    \ floating-point coefficients.\ntemplate <std::floating_point Real>\nstd::vector<std::complex<Real>>\
    \ convolution_fft(const std::vector<std::complex<Real>>& first,\n            \
    \                                    const std::vector<std::complex<Real>>& second)\
    \ {\n    return floating_point_convolution_detail::complex_convolution(first,\
    \ second);\n}\n\n// Convolution of real floating-point coefficients.\ntemplate\
    \ <std::floating_point Real>\nstd::vector<Real> convolution_fft(const std::vector<Real>&\
    \ first, const std::vector<Real>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<std::complex<Real>> complex_first(first.size());\n\
    \    std::vector<std::complex<Real>> complex_second(second.size());\n    for (std::size_t\
    \ index = 0; index < first.size(); ++index) {\n        complex_first[index] =\
    \ std::complex<Real>(first[index], 0);\n    }\n    for (std::size_t index = 0;\
    \ index < second.size(); ++index) {\n        complex_second[index] = std::complex<Real>(second[index],\
    \ 0);\n    }\n    auto result = floating_point_convolution_detail::complex_convolution(complex_first,\
    \ complex_second);\n    std::vector<Real> real_result(result.size());\n    for\
    \ (std::size_t index = 0; index < result.size(); ++index) {\n        real_result[index]\
    \ = result[index].real();\n    }\n    return real_result;\n}\n\n// Uses long-double\
    \ FFT and rounds each coefficient to the nearest integer.\ntemplate <std::integral\
    \ Integer>\nstd::vector<Integer> convolution_round(const std::vector<Integer>&\
    \ first, const std::vector<Integer>& second) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<long double> real_first(first.begin(), first.end());\n\
    \    std::vector<long double> real_second(second.begin(), second.end());\n   \
    \ std::vector<long double> real_result = convolution_fft(real_first, real_second);\n\
    \    std::vector<Integer> result(real_result.size());\n    for (std::size_t index\
    \ = 0; index < result.size(); ++index) {\n        result[index] = static_cast<Integer>(std::round(real_result[index]));\n\
    \    }\n    return result;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\
    \n#line 1 \"math/fps/geometric_sequence_evaluation.hpp\"\n\n\n\n#line 8 \"math/fps/geometric_sequence_evaluation.hpp\"\
    \n\n#line 10 \"math/fps/geometric_sequence_evaluation.hpp\"\n\nnamespace m1une\
    \ {\nnamespace fps {\n\nnamespace internal {\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ geometric_triangular_powers(Mint ratio, int count) {\n    assert(count >= 0);\n\
    \    std::vector<Mint> result(count);\n    if (count == 0) return result;\n  \
    \  result[0] = Mint(1);\n    Mint power = Mint(1);\n    for (int i = 0; i + 1\
    \ < count; ++i) {\n        result[i + 1] = result[i] * power;\n        power *=\
    \ ratio;\n    }\n    return result;\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ geometric_batch_inverse(const std::vector<Mint>& values) {\n    const int count\
    \ = int(values.size());\n    std::vector<Mint> prefix(count + 1, Mint(1));\n \
    \   for (int i = 0; i < count; ++i) {\n        assert(values[i] != Mint(0));\n\
    \        prefix[i + 1] = prefix[i] * values[i];\n    }\n\n    std::vector<Mint>\
    \ result(count);\n    Mint inverse_suffix = prefix[count].inv();\n    for (int\
    \ i = count - 1; i >= 0; --i) {\n        result[i] = prefix[i] * inverse_suffix;\n\
    \        inverse_suffix *= values[i];\n    }\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nstd::vector<Mint> geometric_middle_product(const std::vector<Mint>&\
    \ first,\n                                           std::vector<Mint> second)\
    \ {\n    assert(first.size() >= second.size());\n    if (second.empty()) return\
    \ std::vector<Mint>(first.size() + 1);\n    std::reverse(second.begin(), second.end());\n\
    \    const std::vector<Mint> product = convolution(first, second);\n    const\
    \ int result_size = int(first.size() - second.size() + 1);\n    return std::vector<Mint>(product.begin()\
    \ + second.size() - 1,\n                             product.begin() + second.size()\
    \ - 1 + result_size);\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    std::vector<Mint> multipoint_evaluate_geometric(\n    const FormalPowerSeries<Mint>&\
    \ polynomial, Mint initial, Mint ratio, int count) {\n    assert(count >= 0);\n\
    \    if (count == 0) return {};\n    if (polynomial.empty()) return std::vector<Mint>(count);\n\
    \    if (initial == Mint(0)) return std::vector<Mint>(count, polynomial[0]);\n\
    \    if (ratio == Mint(0)) {\n        std::vector<Mint> result(count, polynomial[0]);\n\
    \        result[0] = polynomial.evaluate(initial);\n        return result;\n \
    \   }\n\n    const int coefficient_count = int(polynomial.size());\n    std::vector<Mint>\
    \ scaled(polynomial.begin(), polynomial.end());\n    Mint initial_power = Mint(1);\n\
    \    for (Mint& coefficient : scaled) {\n        coefficient *= initial_power;\n\
    \        initial_power *= initial;\n    }\n\n    const std::vector<Mint> chirp\
    \ = internal::geometric_triangular_powers(\n        ratio, coefficient_count +\
    \ count - 1);\n    const std::vector<Mint> inverse_chirp = internal::geometric_triangular_powers(\n\
    \        ratio.inv(), std::max(coefficient_count, count));\n    for (int i = 0;\
    \ i < coefficient_count; ++i) scaled[i] *= inverse_chirp[i];\n    std::reverse(scaled.begin(),\
    \ scaled.end());\n\n    const std::vector<Mint> product = convolution(scaled,\
    \ chirp);\n    std::vector<Mint> result(count);\n    for (int i = 0; i < count;\
    \ ++i) {\n        result[i] = product[coefficient_count - 1 + i] * inverse_chirp[i];\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ polynomial_interpolate_geometric(\n    const std::vector<Mint>& values, Mint\
    \ initial, Mint ratio) {\n    using Fps = FormalPowerSeries<Mint>;\n    const\
    \ int count = int(values.size());\n    if (count == 0) return {};\n    if (count\
    \ == 1) return Fps(1, values[0]);\n    assert(initial != Mint(0));\n    assert(ratio\
    \ != Mint(0));\n\n    std::vector<Mint> ratio_power(2 * count - 1, Mint(1));\n\
    \    std::vector<Mint> chirp(2 * count - 1, Mint(1));\n    for (int i = 0; i +\
    \ 1 < int(ratio_power.size()); ++i) {\n        ratio_power[i + 1] = ratio_power[i]\
    \ * ratio;\n        chirp[i + 1] = chirp[i] * ratio_power[i];\n    }\n    const\
    \ std::vector<Mint> inverse_chirp =\n        internal::geometric_triangular_powers(ratio.inv(),\
    \ count);\n\n    std::vector<Mint> difference_product(count, Mint(1));\n    for\
    \ (int i = 1; i < count; ++i) {\n        assert(ratio_power[i] != Mint(1));\n\
    \        difference_product[i] =\n            difference_product[i - 1] * (Mint(1)\
    \ - ratio_power[i]);\n    }\n    const std::vector<Mint> inverse_difference =\n\
    \        internal::geometric_batch_inverse(difference_product);\n    const Mint\
    \ complete_product =\n        difference_product[count - 1] * (Mint(1) - ratio_power[count]);\n\
    \n    std::vector<Mint> weighted = values;\n    for (int i = 0; i < count; ++i)\
    \ {\n        weighted[i] *= chirp[count - 1 - i] * inverse_chirp[count - 1] *\n\
    \                       inverse_difference[i] * inverse_difference[count - 1 -\
    \ i];\n        if (i & 1) weighted[i] = Mint(0) - weighted[i];\n        weighted[i]\
    \ *= inverse_chirp[i];\n    }\n\n    std::vector<Mint> coefficients =\n      \
    \  internal::geometric_middle_product(chirp, weighted);\n    for (int i = 0; i\
    \ < count; ++i) coefficients[i] *= inverse_chirp[i];\n\n    std::vector<Mint>\
    \ product_polynomial(count);\n    product_polynomial[0] = Mint(1);\n    for (int\
    \ i = 1; i < count; ++i) {\n        product_polynomial[i] = chirp[i] * complete_product\
    \ * inverse_difference[i] *\n                                inverse_difference[count\
    \ - i];\n        if (i & 1) product_polynomial[i] = Mint(0) - product_polynomial[i];\n\
    \    }\n    coefficients = convolution(coefficients, product_polynomial);\n  \
    \  coefficients.resize(count);\n\n    std::reverse(coefficients.begin(), coefficients.end());\n\
    \    const Mint inverse_initial = initial.inv();\n    Mint inverse_initial_power\
    \ = Mint(1);\n    for (Mint& coefficient : coefficients) {\n        coefficient\
    \ *= inverse_initial_power;\n        inverse_initial_power *= inverse_initial;\n\
    \    }\n    return Fps(std::move(coefficients));\n}\n\n}  // namespace fps\n}\
    \  // namespace m1une\n\n\n#line 1 \"math/fps/half_gcd.hpp\"\n\n\n\n#line 7 \"\
    math/fps/half_gcd.hpp\"\n\n#line 9 \"math/fps/half_gcd.hpp\"\n\nnamespace m1une\
    \ {\nnamespace fps {\n\ntemplate <class Mint>\nstruct PolynomialMatrix2x2 {\n\
    \    using Fps = FormalPowerSeries<Mint>;\n\n    Fps a00;\n    Fps a01;\n    Fps\
    \ a10;\n    Fps a11;\n\n    static PolynomialMatrix2x2 identity() {\n        return\
    \ PolynomialMatrix2x2{Fps(1, Mint(1)), Fps(), Fps(), Fps(1, Mint(1))};\n    }\n\
    \n    std::pair<Fps, Fps> apply(const Fps& first, const Fps& second) const {\n\
    \        Fps result_first = a00 * first + a01 * second;\n        Fps result_second\
    \ = a10 * first + a11 * second;\n        result_first.shrink();\n        result_second.shrink();\n\
    \        return std::make_pair(std::move(result_first), std::move(result_second));\n\
    \    }\n\n    friend PolynomialMatrix2x2 operator*(const PolynomialMatrix2x2&\
    \ lhs,\n                                          const PolynomialMatrix2x2& rhs)\
    \ {\n        PolynomialMatrix2x2 result;\n        result.a00 = lhs.a00 * rhs.a00\
    \ + lhs.a01 * rhs.a10;\n        result.a01 = lhs.a00 * rhs.a01 + lhs.a01 * rhs.a11;\n\
    \        result.a10 = lhs.a10 * rhs.a00 + lhs.a11 * rhs.a10;\n        result.a11\
    \ = lhs.a10 * rhs.a01 + lhs.a11 * rhs.a11;\n        result.a00.shrink();\n   \
    \     result.a01.shrink();\n        result.a10.shrink();\n        result.a11.shrink();\n\
    \        return result;\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nvoid polynomial_euclidean_step(PolynomialMatrix2x2<Mint>& matrix,\n \
    \                              std::pair<FormalPowerSeries<Mint>,\n          \
    \                               FormalPowerSeries<Mint>>& values) {\n    using\
    \ Fps = FormalPowerSeries<Mint>;\n    assert(!values.second.empty());\n\n    auto\
    \ division = values.first.divmod(values.second);\n    Fps next_a10 = matrix.a00\
    \ - matrix.a10 * division.first;\n    Fps next_a11 = matrix.a01 - matrix.a11 *\
    \ division.first;\n    next_a10.shrink();\n    next_a11.shrink();\n\n    matrix.a00\
    \ = std::move(matrix.a10);\n    matrix.a01 = std::move(matrix.a11);\n    matrix.a10\
    \ = std::move(next_a10);\n    matrix.a11 = std::move(next_a11);\n    values.first\
    \ = std::move(values.second);\n    values.second = std::move(division.second);\n\
    }\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint> half_gcd_impl(\n    std::pair<FormalPowerSeries<Mint>,\
    \ FormalPowerSeries<Mint>> values) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n\
    \n    const int first_size = int(values.first.size());\n    const int half_size\
    \ = (first_size + 1) / 2;\n    if (int(values.second.size()) <= half_size) return\
    \ Matrix::identity();\n\n    Matrix first_matrix =\n        half_gcd_impl<Mint>(std::make_pair(values.first\
    \ >> half_size, values.second >> half_size));\n    values = first_matrix.apply(values.first,\
    \ values.second);\n    if (int(values.second.size()) <= half_size) return first_matrix;\n\
    \n    polynomial_euclidean_step(first_matrix, values);\n    if (int(values.second.size())\
    \ <= half_size) return first_matrix;\n\n    const int first_degree = int(values.first.size())\
    \ - 1;\n    const int shift = 2 * half_size - first_degree;\n    assert(shift\
    \ >= 0);\n    values.first >>= shift;\n    values.second >>= shift;\n    return\
    \ half_gcd_impl<Mint>(std::move(values)) * first_matrix;\n}\n\ntemplate <class\
    \ Mint>\nPolynomialMatrix2x2<Mint> polynomial_gcd_matrix(FormalPowerSeries<Mint>\
    \ first,\n                                                FormalPowerSeries<Mint>\
    \ second) {\n    using Matrix = PolynomialMatrix2x2<Mint>;\n    first.shrink();\n\
    \    second.shrink();\n\n    if (first.size() < second.size()) {\n        Matrix\
    \ result = polynomial_gcd_matrix(std::move(second), std::move(first));\n     \
    \   std::swap(result.a00, result.a01);\n        std::swap(result.a10, result.a11);\n\
    \        return result;\n    }\n\n    std::pair<FormalPowerSeries<Mint>, FormalPowerSeries<Mint>>\
    \ values(\n        std::move(first), std::move(second));\n    Matrix result =\
    \ Matrix::identity();\n    while (true) {\n        Matrix block = half_gcd_impl<Mint>(values);\n\
    \        values = block.apply(values.first, values.second);\n        if (values.second.empty())\
    \ return block * result;\n\n        polynomial_euclidean_step(block, values);\n\
    \        if (values.second.empty()) return block * result;\n        result = block\
    \ * result;\n    }\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\nPolynomialMatrix2x2<Mint>\
    \ half_gcd(FormalPowerSeries<Mint> first,\n                                  \
    \ FormalPowerSeries<Mint> second) {\n    first.shrink();\n    second.shrink();\n\
    \    assert(first.size() >= second.size());\n    return internal::half_gcd_impl<Mint>(std::make_pair(std::move(first),\
    \ std::move(second)));\n}\n\ntemplate <class Mint>\nstruct PolynomialExtendedGcdResult\
    \ {\n    FormalPowerSeries<Mint> gcd;\n    FormalPowerSeries<Mint> x;\n    FormalPowerSeries<Mint>\
    \ y;\n};\n\ntemplate <class Mint>\nPolynomialExtendedGcdResult<Mint> polynomial_extended_gcd(\n\
    \    const FormalPowerSeries<Mint>& first, const FormalPowerSeries<Mint>& second)\
    \ {\n    PolynomialMatrix2x2<Mint> matrix = internal::polynomial_gcd_matrix(first,\
    \ second);\n    auto values = matrix.apply(first, second);\n\n    if (!values.first.empty())\
    \ {\n        const Mint inverse_leading = values.first.back().inv();\n       \
    \ values.first *= inverse_leading;\n        matrix.a00 *= inverse_leading;\n \
    \       matrix.a01 *= inverse_leading;\n    }\n    return PolynomialExtendedGcdResult<Mint>{std::move(values.first),\
    \ std::move(matrix.a00),\n                                             std::move(matrix.a01)};\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_gcd(const FormalPowerSeries<Mint>&\
    \ first,\n                                       const FormalPowerSeries<Mint>&\
    \ second) {\n    return polynomial_extended_gcd(first, second).gcd;\n}\n\ntemplate\
    \ <class Mint>\nstd::optional<FormalPowerSeries<Mint>> polynomial_inv_mod(\n \
    \   const FormalPowerSeries<Mint>& polynomial, FormalPowerSeries<Mint> modulus)\
    \ {\n    modulus.shrink();\n    assert(!modulus.empty());\n    auto result = polynomial_extended_gcd(polynomial,\
    \ modulus);\n    if (result.gcd.size() != 1) return std::nullopt;\n    return\
    \ result.x % modulus;\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/fps/lagrange_inversion.hpp\"\n\n\n\n#line 7 \"math/fps/lagrange_inversion.hpp\"\
    \n\n#line 9 \"math/fps/lagrange_inversion.hpp\"\n\nnamespace m1une {\nnamespace\
    \ fps {\n\ntemplate <class Mint>\nMint lagrange_inversion_coefficient(const FormalPowerSeries<Mint>&\
    \ phi, int degree) {\n    assert(1 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    assert(!phi.empty() && phi[0] != Mint(0));\n\n    FormalPowerSeries<Mint>\
    \ power = phi.pre(degree).pow(degree, degree);\n    return power[degree - 1] /\
    \ Mint(degree);\n}\n\ntemplate <class Mint>\nMint lagrange_burmann_coefficient(const\
    \ FormalPowerSeries<Mint>& phi,\n                                  const FormalPowerSeries<Mint>&\
    \ outer, int degree) {\n    assert(0 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    if (degree == 0) return outer.empty() ? Mint(0) : outer[0];\n    assert(!phi.empty()\
    \ && phi[0] != Mint(0));\n\n    FormalPowerSeries<Mint> power = phi.pre(degree).pow(degree,\
    \ degree);\n    Mint result = 0;\n    int limit = std::min(degree, int(outer.size())\
    \ - 1);\n    for (int i = 1; i <= limit; i++) {\n        result += Mint(i) * outer[i]\
    \ * power[degree - i];\n    }\n    return result / Mint(degree);\n}\n\ntemplate\
    \ <class Mint>\nMint compositional_inverse_coefficient(const FormalPowerSeries<Mint>&\
    \ f, int degree) {\n    assert(0 <= degree && uint32_t(degree) < Mint::mod());\n\
    \    assert(2 <= int(f.size()) && f[0] == Mint(0) && f[1] != Mint(0));\n    if\
    \ (degree == 0) return Mint(0);\n\n    FormalPowerSeries<Mint> divided(degree);\n\
    \    for (int i = 0; i < degree && i + 1 < int(f.size()); i++) divided[i] = f[i\
    \ + 1];\n    FormalPowerSeries<Mint> phi = divided.inv(degree);\n    return lagrange_inversion_coefficient(phi,\
    \ degree);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/linear_recurrence.hpp\"\
    \n\n\n\n#line 9 \"math/fps/linear_recurrence.hpp\"\n\n#line 11 \"math/fps/linear_recurrence.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\n// Returns a shortest linear recurrence\
    \ satisfied by the observed sequence.\n// The returned coefficients use\n// a[n]\
    \ = recurrence[0] * a[n - 1] + ... + recurrence[d - 1] * a[n - d].\ntemplate <class\
    \ Mint>\nstd::vector<Mint> berlekamp_massey(const std::vector<Mint>& sequence)\
    \ {\n    std::vector<Mint> connection(1, Mint(1));\n    std::vector<Mint> previous(1,\
    \ Mint(1));\n    int order = 0;\n    int shift = 1;\n    Mint previous_discrepancy\
    \ = Mint(1);\n\n    for (int index = 0; index < int(sequence.size()); index++)\
    \ {\n        Mint discrepancy = sequence[index];\n        for (int i = 1; i <=\
    \ order; i++) {\n            discrepancy += connection[i] * sequence[index - i];\n\
    \        }\n        if (discrepancy == Mint(0)) {\n            shift++;\n    \
    \        continue;\n        }\n\n        const Mint scale = discrepancy / previous_discrepancy;\n\
    \        std::vector<Mint> old_connection = connection;\n        if (connection.size()\
    \ < previous.size() + std::size_t(shift)) {\n            connection.resize(previous.size()\
    \ + std::size_t(shift));\n        }\n        for (int i = 0; i < int(previous.size());\
    \ i++) {\n            connection[i + shift] -= scale * previous[i];\n        }\n\
    \n        if (2 * order <= index) {\n            order = index + 1 - order;\n\
    \            previous = std::move(old_connection);\n            previous_discrepancy\
    \ = discrepancy;\n            shift = 1;\n        } else {\n            shift++;\n\
    \        }\n    }\n\n    std::vector<Mint> recurrence(order);\n    for (int i\
    \ = 0; i < order; i++) recurrence[i] = Mint(0) - connection[i + 1];\n    return\
    \ recurrence;\n}\n\ntemplate <class Mint>\nMint coefficient_of_rational(FormalPowerSeries<Mint>\
    \ numerator,\n                             FormalPowerSeries<Mint> denominator,\
    \ uint64_t index) {\n    using Fps = FormalPowerSeries<Mint>;\n    assert(!denominator.empty()\
    \ && denominator[0] != Mint(0));\n\n    while (index > 0) {\n        Fps denominator_negative\
    \ = denominator;\n        for (int i = 1; i < int(denominator_negative.size());\
    \ i += 2) {\n            denominator_negative[i] = Mint(0) - denominator_negative[i];\n\
    \        }\n\n        Fps numerator_product = numerator * denominator_negative;\n\
    \        Fps denominator_product = denominator * denominator_negative;\n     \
    \   Fps next_numerator;\n        Fps next_denominator;\n        next_numerator.reserve((numerator_product.size()\
    \ + 1) / 2);\n        next_denominator.reserve((denominator_product.size() + 1)\
    \ / 2);\n        for (int i = int(index & 1); i < int(numerator_product.size());\
    \ i += 2) {\n            next_numerator.emplace_back(numerator_product[i]);\n\
    \        }\n        for (int i = 0; i < int(denominator_product.size()); i +=\
    \ 2) {\n            next_denominator.emplace_back(denominator_product[i]);\n \
    \       }\n        numerator = std::move(next_numerator);\n        denominator\
    \ = std::move(next_denominator);\n        index >>= 1;\n    }\n    return numerator.empty()\
    \ ? Mint(0) : numerator[0] / denominator[0];\n}\n\ntemplate <class Mint>\nMint\
    \ linear_recurrence_kth(const std::vector<Mint>& initial,\n                  \
    \         const std::vector<Mint>& recurrence, uint64_t index) {\n    using Fps\
    \ = FormalPowerSeries<Mint>;\n    assert(!initial.empty() && initial.size() ==\
    \ recurrence.size());\n    if (index < initial.size()) return initial[index];\n\
    \n    const int order = int(recurrence.size());\n    Fps denominator(order + 1);\n\
    \    denominator[0] = 1;\n    for (int i = 0; i < order; i++) denominator[i +\
    \ 1] = Mint(0) - recurrence[i];\n    Fps numerator = (Fps(initial) * denominator).pre(order);\n\
    \    return coefficient_of_rational(std::move(numerator), std::move(denominator),\
    \ index);\n}\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/multipoint_evaluation.hpp\"\
    \n\n\n\n#line 6 \"math/fps/multipoint_evaluation.hpp\"\n\n#line 8 \"math/fps/multipoint_evaluation.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct SubproductTree\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n\n   private:\n    int point_count_;\n\
    \    int leaf_count_;\n    std::vector<Mint> points_;\n    std::vector<Fps> product_;\n\
    \n   public:\n    explicit SubproductTree(const std::vector<Mint>& points)\n \
    \       : point_count_(points.size()), leaf_count_(1), points_(points) {\n   \
    \     while (leaf_count_ < point_count_) leaf_count_ <<= 1;\n        product_.resize(leaf_count_\
    \ << 1);\n        for (int i = 0; i < leaf_count_; i++) {\n            if (i <\
    \ point_count_) {\n                product_[leaf_count_ + i].resize(2);\n    \
    \            product_[leaf_count_ + i][0] = Mint(0) - points_[i];\n          \
    \      product_[leaf_count_ + i][1] = Mint(1);\n            } else {\n       \
    \         product_[leaf_count_ + i].resize(1, Mint(1));\n            }\n     \
    \   }\n        for (int node = leaf_count_ - 1; node > 0; node--) {\n        \
    \    product_[node] = product_[node << 1] * product_[node << 1 | 1];\n       \
    \ }\n    }\n\n    int size() const {\n        return point_count_;\n    }\n\n\
    \    const Fps& product() const {\n        return product_[1];\n    }\n\n    std::vector<Mint>\
    \ evaluate(const Fps& polynomial) const {\n        std::vector<Mint> result(point_count_);\n\
    \        if (point_count_ == 0) return result;\n\n        std::vector<Fps> remainder(leaf_count_\
    \ << 1);\n        remainder[1] = polynomial % product_[1];\n        for (int node\
    \ = 1; node < leaf_count_; node++) {\n            remainder[node << 1] = remainder[node]\
    \ % product_[node << 1];\n            remainder[node << 1 | 1] = remainder[node]\
    \ % product_[node << 1 | 1];\n        }\n        for (int i = 0; i < point_count_;\
    \ i++) {\n            const Fps& value = remainder[leaf_count_ + i];\n       \
    \     result[i] = value.empty() ? Mint(0) : value[0];\n        }\n        return\
    \ result;\n    }\n\n    Fps interpolate(const std::vector<Mint>& values) const\
    \ {\n        assert(int(values.size()) == point_count_);\n        if (point_count_\
    \ == 0) return {};\n\n        std::vector<Mint> derivative_values = evaluate(product_[1].derivative());\n\
    \        std::vector<Fps> polynomial(leaf_count_ << 1);\n        for (int i =\
    \ 0; i < leaf_count_; i++) {\n            polynomial[leaf_count_ + i].resize(1);\n\
    \            if (i < point_count_) {\n                assert(derivative_values[i]\
    \ != Mint(0));\n                polynomial[leaf_count_ + i][0] = values[i] / derivative_values[i];\n\
    \            }\n        }\n        for (int node = leaf_count_ - 1; node > 0;\
    \ node--) {\n            polynomial[node] = polynomial[node << 1] * product_[node\
    \ << 1 | 1] +\n                               polynomial[node << 1 | 1] * product_[node\
    \ << 1];\n        }\n        polynomial[1].resize(point_count_);\n        return\
    \ polynomial[1];\n    }\n};\n\ntemplate <class Mint>\nstd::vector<Mint> multipoint_evaluate(const\
    \ FormalPowerSeries<Mint>& polynomial,\n                                     \
    \ const std::vector<Mint>& points) {\n    return SubproductTree<Mint>(points).evaluate(polynomial);\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_interpolate(const\
    \ std::vector<Mint>& points,\n                                               const\
    \ std::vector<Mint>& values) {\n    return SubproductTree<Mint>(points).interpolate(values);\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/polynomial_factorization.hpp\"\
    \n\n\n\n#line 9 \"math/fps/polynomial_factorization.hpp\"\n\n#line 11 \"math/fps/polynomial_factorization.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct PolynomialFactor\
    \ {\n    FormalPowerSeries<Mint> polynomial;\n    int multiplicity;\n};\n\ntemplate\
    \ <class Mint>\nstruct PolynomialFactorization {\n    Mint leading_coefficient;\n\
    \    std::vector<PolynomialFactor<Mint>> factors;\n};\n\nnamespace internal {\n\
    \ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_monic(FormalPowerSeries<Mint>\
    \ polynomial) {\n    polynomial.shrink();\n    if (polynomial.empty()) return\
    \ polynomial;\n    polynomial /= polynomial.back();\n    return polynomial;\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_multiply(\n\
    \    const FormalPowerSeries<Mint>& first,\n    const FormalPowerSeries<Mint>&\
    \ second\n) {\n    if (first.empty() || second.empty()) return {};\n    FormalPowerSeries<Mint>\
    \ result(first.size() + second.size() - 1);\n    for (int i = 0; i < int(first.size());\
    \ i++) {\n        for (int j = 0; j < int(second.size()); j++) {\n           \
    \ result[i + j] += first[i] * second[j];\n        }\n    }\n    result.shrink();\n\
    \    return result;\n}\n\ntemplate <class Mint>\nstd::pair<FormalPowerSeries<Mint>,\
    \ FormalPowerSeries<Mint>> factorization_divmod(\n    FormalPowerSeries<Mint>\
    \ dividend,\n    FormalPowerSeries<Mint> divisor\n) {\n    dividend.shrink();\n\
    \    divisor.shrink();\n    assert(!divisor.empty());\n    if (dividend.size()\
    \ < divisor.size()) return std::make_pair(FormalPowerSeries<Mint>(), dividend);\n\
    \n    FormalPowerSeries<Mint> quotient(dividend.size() - divisor.size() + 1);\n\
    \    const Mint inverse_leading = divisor.back().inv();\n    for (int i = int(dividend.size())\
    \ - 1; i >= int(divisor.size()) - 1; i--) {\n        const Mint coefficient =\
    \ dividend[i] * inverse_leading;\n        const int shift = i - int(divisor.size())\
    \ + 1;\n        quotient[shift] = coefficient;\n        if (coefficient == Mint(0))\
    \ continue;\n        for (int j = 0; j < int(divisor.size()); j++) {\n       \
    \     dividend[shift + j] -= coefficient * divisor[j];\n        }\n    }\n   \
    \ quotient.shrink();\n    dividend.resize(divisor.size() - 1);\n    dividend.shrink();\n\
    \    return std::make_pair(std::move(quotient), std::move(dividend));\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> factorization_gcd(\n    FormalPowerSeries<Mint>\
    \ first,\n    FormalPowerSeries<Mint> second\n) {\n    first.shrink();\n    second.shrink();\n\
    \    while (!second.empty()) {\n        FormalPowerSeries<Mint> remainder =\n\
    \            factorization_divmod(std::move(first), second).second;\n        first\
    \ = std::move(second);\n        second = std::move(remainder);\n    }\n    return\
    \ factorization_monic(std::move(first));\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ factorization_multiply_mod(\n    const FormalPowerSeries<Mint>& first,\n   \
    \ const FormalPowerSeries<Mint>& second,\n    const FormalPowerSeries<Mint>& modulus\n\
    ) {\n    return factorization_divmod(factorization_multiply(first, second), modulus).second;\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> factorization_power_mod(\n\
    \    FormalPowerSeries<Mint> base,\n    uint64_t exponent,\n    const FormalPowerSeries<Mint>&\
    \ modulus\n) {\n    FormalPowerSeries<Mint> result(1, Mint(1));\n    result =\
    \ factorization_divmod(std::move(result), modulus).second;\n    base = factorization_divmod(std::move(base),\
    \ modulus).second;\n    while (exponent > 0) {\n        if (exponent & 1) result\
    \ = factorization_multiply_mod(result, base, modulus);\n        exponent >>= 1;\n\
    \        if (exponent > 0) base = factorization_multiply_mod(base, base, modulus);\n\
    \    }\n    return result;\n}\n\nstruct PolynomialFactorizationRandom {\n    uint64_t\
    \ state;\n\n    uint64_t operator()() {\n        state ^= state << 7;\n      \
    \  state ^= state >> 9;\n        return state;\n    }\n};\n\ntemplate <class Mint>\n\
    FormalPowerSeries<Mint> factorization_random_polynomial(\n    int coefficient_count,\n\
    \    PolynomialFactorizationRandom& random\n) {\n    FormalPowerSeries<Mint> result(coefficient_count);\n\
    \    const uint64_t mod = Mint::mod();\n    for (Mint& coefficient : result) coefficient\
    \ = Mint(random() % mod);\n    result.shrink();\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> equal_degree_separator_odd(\n    const\
    \ FormalPowerSeries<Mint>& random_polynomial,\n    int factor_degree,\n    const\
    \ FormalPowerSeries<Mint>& modulus\n) {\n    FormalPowerSeries<Mint> power = factorization_power_mod(\n\
    \        random_polynomial, (uint64_t(Mint::mod()) - 1) / 2, modulus);\n    FormalPowerSeries<Mint>\
    \ result(1, Mint(1));\n    for (int i = 0; i < factor_degree; i++) {\n       \
    \ result = factorization_multiply_mod(result, power, modulus);\n        if (i\
    \ + 1 < factor_degree) {\n            power = factorization_power_mod(power, Mint::mod(),\
    \ modulus);\n        }\n    }\n    if (result.empty()) result.resize(1);\n   \
    \ result[0] -= Mint(1);\n    result.shrink();\n    return result;\n}\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> equal_degree_separator_two(\n    const\
    \ FormalPowerSeries<Mint>& random_polynomial,\n    int factor_degree,\n    const\
    \ FormalPowerSeries<Mint>& modulus\n) {\n    FormalPowerSeries<Mint> power =\n\
    \        factorization_divmod(random_polynomial, modulus).second;\n    FormalPowerSeries<Mint>\
    \ result;\n    for (int i = 0; i < factor_degree; i++) {\n        result += power;\n\
    \        result.shrink();\n        if (i + 1 < factor_degree) {\n            power\
    \ = factorization_multiply_mod(power, power, modulus);\n        }\n    }\n   \
    \ return result;\n}\n\ntemplate <class Mint>\nstd::vector<FormalPowerSeries<Mint>>\
    \ equal_degree_factorization(\n    FormalPowerSeries<Mint> polynomial,\n    int\
    \ factor_degree,\n    PolynomialFactorizationRandom& random\n) {\n    using Fps\
    \ = FormalPowerSeries<Mint>;\n    polynomial = factorization_monic(std::move(polynomial));\n\
    \    std::vector<Fps> queue(1, std::move(polynomial));\n    std::vector<Fps> result;\n\
    \    for (int head = 0; head < int(queue.size()); head++) {\n        Fps current\
    \ = factorization_monic(std::move(queue[head]));\n        const int degree = int(current.size())\
    \ - 1;\n        if (degree == factor_degree) {\n            result.push_back(std::move(current));\n\
    \            continue;\n        }\n\n        Fps divisor;\n        do {\n    \
    \        Fps random_polynomial =\n                factorization_random_polynomial<Mint>(degree,\
    \ random);\n            Fps separator = Mint::mod() == 2\n                ? equal_degree_separator_two(random_polynomial,\
    \ factor_degree, current)\n                : equal_degree_separator_odd(random_polynomial,\
    \ factor_degree, current);\n            divisor = factorization_gcd(current, std::move(separator));\n\
    \        } while (divisor.size() <= 1 || divisor.size() == current.size());\n\n\
    \        Fps quotient = factorization_divmod(current, divisor).first;\n      \
    \  queue.push_back(std::move(divisor));\n        queue.push_back(std::move(quotient));\n\
    \    }\n    return result;\n}\n\n}  // namespace internal\n\ntemplate <class Mint>\n\
    PolynomialFactorization<Mint> polynomial_factorize(\n    FormalPowerSeries<Mint>\
    \ polynomial,\n    uint64_t seed = 88172645463325252ULL\n) {\n    using Fps =\
    \ FormalPowerSeries<Mint>;\n    polynomial.shrink();\n    assert(!polynomial.empty());\n\
    \n    const Mint leading_coefficient = polynomial.back();\n    polynomial /= leading_coefficient;\n\
    \    std::vector<PolynomialFactor<Mint>> factors;\n    if (polynomial.size() ==\
    \ 1) return {leading_coefficient, std::move(factors)};\n\n    if (seed == 0) seed\
    \ = 88172645463325252ULL;\n    internal::PolynomialFactorizationRandom random{seed};\n\
    \    const Fps x = Fps({Mint(0), Mint(1)});\n    Fps frobenius = x;\n    for (int\
    \ degree = 1;\n         polynomial.size() > 1 && 2 * degree <= int(polynomial.size())\
    \ - 1;\n         degree++) {\n        frobenius = internal::factorization_power_mod(\n\
    \            std::move(frobenius), Mint::mod(), polynomial);\n        Fps difference\
    \ = frobenius - x;\n        difference.shrink();\n        Fps product = internal::factorization_gcd(polynomial,\
    \ std::move(difference));\n        if (product.size() <= 1) continue;\n\n    \
    \    std::vector<Fps> distinct = internal::equal_degree_factorization(\n     \
    \       std::move(product), degree, random);\n        for (Fps& factor : distinct)\
    \ {\n            int multiplicity = 0;\n            while (factor.size() <= polynomial.size())\
    \ {\n                auto division = internal::factorization_divmod(polynomial,\
    \ factor);\n                if (!division.second.empty()) break;\n           \
    \     polynomial = std::move(division.first);\n                multiplicity++;\n\
    \            }\n            assert(multiplicity > 0);\n            factors.push_back({std::move(factor),\
    \ multiplicity});\n        }\n    }\n    if (polynomial.size() > 1) {\n      \
    \  factors.push_back({internal::factorization_monic(std::move(polynomial)), 1});\n\
    \    }\n\n    auto less = [](const PolynomialFactor<Mint>& first,\n          \
    \         const PolynomialFactor<Mint>& second) {\n        if (first.polynomial.size()\
    \ != second.polynomial.size()) {\n            return first.polynomial.size() <\
    \ second.polynomial.size();\n        }\n        for (int i = int(first.polynomial.size())\
    \ - 1; i >= 0; i--) {\n            if (first.polynomial[i].val() != second.polynomial[i].val())\
    \ {\n                return first.polynomial[i].val() < second.polynomial[i].val();\n\
    \            }\n        }\n        return false;\n    };\n    std::sort(factors.begin(),\
    \ factors.end(), less);\n\n    std::vector<PolynomialFactor<Mint>> merged;\n \
    \   for (PolynomialFactor<Mint>& factor : factors) {\n        if (!merged.empty()\
    \ && merged.back().polynomial == factor.polynomial) {\n            merged.back().multiplicity\
    \ += factor.multiplicity;\n        } else {\n            merged.push_back(std::move(factor));\n\
    \        }\n    }\n    return {leading_coefficient, std::move(merged)};\n}\n\n\
    }  // namespace fps\n}  // namespace m1une\n\n\n#line 1 \"math/fps/polynomial_roots.hpp\"\
    \n\n\n\n#line 9 \"math/fps/polynomial_roots.hpp\"\n\n#line 11 \"math/fps/polynomial_roots.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\nnamespace internal {\n\nstruct PolynomialRootsRandom\
    \ {\n    uint64_t state;\n\n    uint64_t operator()() {\n        state ^= state\
    \ << 7;\n        state ^= state >> 9;\n        return state;\n    }\n};\n\ntemplate\
    \ <class Mint>\nFormalPowerSeries<Mint> polynomial_roots_power_mod(\n    FormalPowerSeries<Mint>\
    \ base, uint64_t exponent,\n    const FormalPowerSeries<Mint>& modulus) {\n  \
    \  using Fps = FormalPowerSeries<Mint>;\n    Fps result(1, Mint(1));\n    result\
    \ %= modulus;\n    base %= modulus;\n    while (exponent > 0) {\n        if (exponent\
    \ & 1) result = (result * base) % modulus;\n        exponent >>= 1;\n        if\
    \ (exponent > 0) base = (base * base) % modulus;\n    }\n    return result;\n\
    }\n\n}  // namespace internal\n\ntemplate <class Mint>\nstd::vector<Mint> polynomial_roots(\n\
    \    FormalPowerSeries<Mint> polynomial,\n    uint64_t seed = 88172645463325252ULL)\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n    polynomial.shrink();\n    assert(!polynomial.empty());\n\
    \    if (polynomial.size() == 1) return {};\n\n    const uint64_t modulus = Mint::mod();\n\
    \    if (modulus == 2) {\n        std::vector<Mint> result;\n        if (polynomial.evaluate(Mint(0))\
    \ == Mint(0)) result.push_back(Mint(0));\n        if (polynomial.evaluate(Mint(1))\
    \ == Mint(0)) result.push_back(Mint(1));\n        return result;\n    }\n    assert(modulus\
    \ & 1);\n\n    Fps x(2);\n    x[1] = Mint(1);\n    Fps frobenius = internal::polynomial_roots_power_mod(x,\
    \ modulus, polynomial);\n    frobenius -= x;\n    frobenius.shrink();\n    Fps\
    \ linear_part = polynomial_gcd(polynomial, frobenius);\n    if (linear_part.size()\
    \ <= 1) return {};\n\n    if (seed == 0) seed = 88172645463325252ULL;\n    internal::PolynomialRootsRandom\
    \ random{seed};\n    std::vector<Mint> result;\n    auto split = [&](auto&& self,\
    \ Fps current) -> void {\n        current.shrink();\n        if (current.size()\
    \ <= 1) return;\n        if (current.size() == 2) {\n            result.push_back((Mint(0)\
    \ - current[0]) / current[1]);\n            return;\n        }\n\n        Fps\
    \ divisor;\n        do {\n            Fps shifted_x(2);\n            shifted_x[0]\
    \ = Mint(random() % modulus);\n            shifted_x[1] = Mint(1);\n         \
    \   Fps separator = internal::polynomial_roots_power_mod(\n                std::move(shifted_x),\
    \ (modulus - 1) / 2, current);\n            if (separator.empty()) separator.resize(1);\n\
    \            separator[0] -= Mint(1);\n            separator.shrink();\n     \
    \       divisor = polynomial_gcd(current, separator);\n        } while (divisor.size()\
    \ <= 1 || divisor.size() == current.size());\n\n        auto division = current.divmod(divisor);\n\
    \        assert(division.second.empty());\n        self(self, std::move(divisor));\n\
    \        self(self, std::move(division.first));\n    };\n    split(split, std::move(linear_part));\n\
    \n    std::sort(result.begin(), result.end(), [](Mint lhs, Mint rhs) {\n     \
    \   return lhs.val() < rhs.val();\n    });\n    result.erase(std::unique(result.begin(),\
    \ result.end()), result.end());\n    return result;\n}\n\n}  // namespace fps\n\
    }  // namespace m1une\n\n\n#line 1 \"math/fps/sparse_formal_power_series.hpp\"\
    \n\n\n\n#line 9 \"math/fps/sparse_formal_power_series.hpp\"\n\n#line 11 \"math/fps/sparse_formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nusing SparseFormalPowerSeries\
    \ = std::vector<std::pair<int, Mint>>;\n\nnamespace internal {\n\ntemplate <class\
    \ Mint>\nvoid assert_valid_sparse_fps(const SparseFormalPowerSeries<Mint>& terms,\
    \ int degree) {\n    int previous_degree = -1;\n    for (const auto& [term_degree,\
    \ coefficient] : terms) {\n        assert(0 <= term_degree && previous_degree\
    \ < term_degree && term_degree < degree);\n        assert(coefficient != Mint(0));\n\
    \        previous_degree = term_degree;\n    }\n}\n\ntemplate <class Mint>\nstd::vector<Mint>\
    \ sparse_integer_inverses(int degree) {\n    assert(degree >= 0 && uint32_t(degree)\
    \ < Mint::mod());\n    std::vector<Mint> inverse(degree);\n    if (degree <= 1)\
    \ return inverse;\n    inverse[1] = Mint(1);\n    for (int i = 2; i < degree;\
    \ i++) {\n        const uint32_t quotient = Mint::mod() / uint32_t(i);\n     \
    \   const uint32_t remainder = Mint::mod() % uint32_t(i);\n        inverse[i]\
    \ = Mint(0) - Mint(quotient) * inverse[remainder];\n    }\n    return inverse;\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> sparse_unit_pow(const SparseFormalPowerSeries<Mint>&\
    \ terms,\n                                        Mint exponent, int degree) {\n\
    \    assert(degree > 0 && !terms.empty());\n    assert(terms[0].first == 0 &&\
    \ terms[0].second == Mint(1));\n    std::vector<Mint> inverse = sparse_integer_inverses<Mint>(degree);\n\
    \    FormalPowerSeries<Mint> result(degree);\n    result[0] = Mint(1);\n    for\
    \ (int n = 1; n < degree; n++) {\n        Mint coefficient = 0;\n        for (int\
    \ i = 1; i < int(terms.size()) && terms[i].first <= n; i++) {\n            const\
    \ auto& [d, value] = terms[i];\n            coefficient += value * result[n -\
    \ d] *\n                           (exponent * Mint(d) - Mint(n - d));\n     \
    \   }\n        result[n] = coefficient * inverse[n];\n    }\n    return result;\n\
    }\n\n}  // namespace internal\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ sparse_fps_inv(const SparseFormalPowerSeries<Mint>& terms,\n               \
    \                        int degree) {\n    assert(degree >= 0);\n    if (degree\
    \ == 0) return {};\n    internal::assert_valid_sparse_fps(terms, degree);\n  \
    \  assert(!terms.empty() && terms[0].first == 0);\n\n    const Mint inverse_constant\
    \ = terms[0].second.inv();\n    FormalPowerSeries<Mint> result(degree);\n    result[0]\
    \ = inverse_constant;\n    for (int n = 1; n < degree; n++) {\n        Mint coefficient\
    \ = 0;\n        for (int i = 1; i < int(terms.size()) && terms[i].first <= n;\
    \ i++) {\n            coefficient -= terms[i].second * result[n - terms[i].first];\n\
    \        }\n        result[n] = coefficient * inverse_constant;\n    }\n    return\
    \ result;\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> sparse_fps_log(const\
    \ SparseFormalPowerSeries<Mint>& terms,\n                                    \
    \   int degree) {\n    assert(degree >= 0);\n    if (degree == 0) return {};\n\
    \    assert(uint32_t(degree) < Mint::mod());\n    internal::assert_valid_sparse_fps(terms,\
    \ degree);\n    assert(!terms.empty() && terms[0].first == 0 && terms[0].second\
    \ == Mint(1));\n\n    std::vector<Mint> inverse = internal::sparse_integer_inverses<Mint>(degree);\n\
    \    FormalPowerSeries<Mint> result(degree);\n    for (int n = 0; n + 1 < degree;\
    \ n++) {\n        Mint derivative_quotient = 0;\n        for (int i = 1; i < int(terms.size())\
    \ && terms[i].first <= n + 1; i++) {\n            const auto& [d, value] = terms[i];\n\
    \            if (d == n + 1) derivative_quotient += Mint(d) * value;\n       \
    \     if (d <= n) {\n                derivative_quotient -=\n                \
    \    value * Mint(n - d + 1) * result[n - d + 1];\n            }\n        }\n\
    \        result[n + 1] = derivative_quotient * inverse[n + 1];\n    }\n    return\
    \ result;\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> sparse_fps_exp(const\
    \ SparseFormalPowerSeries<Mint>& terms,\n                                    \
    \   int degree) {\n    assert(degree >= 0);\n    if (degree == 0) return {};\n\
    \    assert(uint32_t(degree) < Mint::mod());\n    internal::assert_valid_sparse_fps(terms,\
    \ degree);\n    assert(terms.empty() || terms[0].first > 0);\n\n    std::vector<Mint>\
    \ inverse = internal::sparse_integer_inverses<Mint>(degree);\n    FormalPowerSeries<Mint>\
    \ result(degree);\n    result[0] = Mint(1);\n    for (int n = 1; n < degree; n++)\
    \ {\n        Mint coefficient = 0;\n        for (const auto& [d, value] : terms)\
    \ {\n            if (d > n) break;\n            coefficient += Mint(d) * value\
    \ * result[n - d];\n        }\n        result[n] = coefficient * inverse[n];\n\
    \    }\n    return result;\n}\n\ntemplate <class Mint>\nFormalPowerSeries<Mint>\
    \ sparse_fps_pow(const SparseFormalPowerSeries<Mint>& terms,\n               \
    \                        long long exponent, int degree) {\n    assert(exponent\
    \ >= 0 && degree >= 0);\n    if (degree == 0) return {};\n    assert(uint32_t(degree)\
    \ < Mint::mod());\n    internal::assert_valid_sparse_fps(terms, degree);\n   \
    \ if (exponent == 0) {\n        FormalPowerSeries<Mint> result(degree);\n    \
    \    result[0] = Mint(1);\n        return result;\n    }\n    if (terms.empty())\
    \ return FormalPowerSeries<Mint>(degree);\n\n    const int leading_degree = terms[0].first;\n\
    \    if (leading_degree > 0 && exponent > (degree - 1) / leading_degree) {\n \
    \       return FormalPowerSeries<Mint>(degree);\n    }\n    const int offset =\
    \ int(leading_degree * exponent);\n    const int normalized_degree = degree -\
    \ offset;\n    const Mint leading = terms[0].second;\n    const Mint inverse_leading\
    \ = leading.inv();\n    SparseFormalPowerSeries<Mint> normalized;\n    normalized.reserve(terms.size());\n\
    \    for (const auto& [d, value] : terms) {\n        if (d - leading_degree >=\
    \ normalized_degree) break;\n        normalized.emplace_back(d - leading_degree,\
    \ value * inverse_leading);\n    }\n\n    FormalPowerSeries<Mint> unit =\n   \
    \     internal::sparse_unit_pow(normalized, Mint(exponent), normalized_degree);\n\
    \    const Mint scale = leading.pow(exponent);\n    FormalPowerSeries<Mint> result(degree);\n\
    \    for (int i = 0; i < normalized_degree; i++) result[offset + i] = unit[i]\
    \ * scale;\n    return result;\n}\n\ntemplate <class Mint>\nstd::optional<FormalPowerSeries<Mint>>\
    \ sparse_fps_sqrt(\n    const SparseFormalPowerSeries<Mint>& terms, int degree)\
    \ {\n    assert(degree >= 0);\n    if (degree == 0) return FormalPowerSeries<Mint>();\n\
    \    assert(uint32_t(degree) < Mint::mod());\n    internal::assert_valid_sparse_fps(terms,\
    \ degree);\n    assert(Mint(2) != Mint(0));\n    if (terms.empty()) return FormalPowerSeries<Mint>(degree);\n\
    \n    const int leading_degree = terms[0].first;\n    if (leading_degree & 1)\
    \ return std::nullopt;\n    auto leading_root = m1une::math::modular_square_root(terms[0].second);\n\
    \    if (!leading_root.has_value()) return std::nullopt;\n\n    const int normalized_degree\
    \ = degree - leading_degree;\n    const Mint inverse_leading = terms[0].second.inv();\n\
    \    SparseFormalPowerSeries<Mint> normalized;\n    normalized.reserve(terms.size());\n\
    \    for (const auto& [d, value] : terms) {\n        normalized.emplace_back(d\
    \ - leading_degree, value * inverse_leading);\n    }\n    FormalPowerSeries<Mint>\
    \ unit = internal::sparse_unit_pow(\n        normalized, Mint(2).inv(), normalized_degree);\n\
    \n    FormalPowerSeries<Mint> result(degree);\n    const int offset = leading_degree\
    \ / 2;\n    for (int i = 0; i < normalized_degree; i++) {\n        result[offset\
    \ + i] = unit[i] * *leading_root;\n    }\n    return result;\n}\n\n}  // namespace\
    \ fps\n}  // namespace m1une\n\n\n#line 18 \"math/fps/all.hpp\"\n\n\n#line 12\
    \ \"verify/math/fps/fps_algorithms.test.cpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    using mint1e9 = m1une::math::modint1000000007;\nusing Fps = m1une::fps::FormalPowerSeries<mint>;\n\
    \ntemplate <class Mint>\nvoid assert_equal(const std::vector<Mint>& lhs, const\
    \ std::vector<Mint>& rhs) {\n    assert(lhs.size() == rhs.size());\n    for (int\
    \ i = 0; i < int(lhs.size()); i++) assert(lhs[i] == rhs[i]);\n}\n\ntemplate <class\
    \ Mint>\nbool has_recurrence_of_order(const std::vector<Mint>& sequence, int order)\
    \ {\n    assert(0 <= order && order <= int(sequence.size()));\n    const int equation_count\
    \ = int(sequence.size()) - order;\n    std::vector<std::vector<Mint>> matrix(\n\
    \        equation_count, std::vector<Mint>(order + 1)\n    );\n    for (int row\
    \ = 0; row < equation_count; row++) {\n        const int index = order + row;\n\
    \        for (int i = 0; i < order; i++) {\n            matrix[row][i] = sequence[index\
    \ - i - 1];\n        }\n        matrix[row][order] = sequence[index];\n    }\n\
    \n    int pivot_row = 0;\n    for (int column = 0; column < order && pivot_row\
    \ < equation_count; column++) {\n        int pivot = pivot_row;\n        while\
    \ (pivot < equation_count && matrix[pivot][column] == Mint(0)) pivot++;\n    \
    \    if (pivot == equation_count) continue;\n        std::swap(matrix[pivot_row],\
    \ matrix[pivot]);\n\n        const Mint inverse = Mint(1) / matrix[pivot_row][column];\n\
    \        for (int j = column; j <= order; j++) matrix[pivot_row][j] *= inverse;\n\
    \        for (int row = pivot_row + 1; row < equation_count; row++) {\n      \
    \      const Mint scale = matrix[row][column];\n            if (scale == Mint(0))\
    \ continue;\n            for (int j = column; j <= order; j++) {\n           \
    \     matrix[row][j] -= scale * matrix[pivot_row][j];\n            }\n       \
    \ }\n        pivot_row++;\n    }\n\n    for (int row = pivot_row; row < equation_count;\
    \ row++) {\n        bool all_zero = true;\n        for (int column = 0; column\
    \ < order; column++) {\n            if (matrix[row][column] != Mint(0)) all_zero\
    \ = false;\n        }\n        if (all_zero && matrix[row][order] != Mint(0))\
    \ return false;\n    }\n    return true;\n}\n\ntemplate <class Mint>\nvoid assert_recurrence(const\
    \ std::vector<Mint>& sequence,\n                       const std::vector<Mint>&\
    \ recurrence) {\n    const int order = int(recurrence.size());\n    for (int index\
    \ = order; index < int(sequence.size()); index++) {\n        Mint expected = 0;\n\
    \        for (int i = 0; i < order; i++) {\n            expected += recurrence[i]\
    \ * sequence[index - i - 1];\n        }\n        assert(sequence[index] == expected);\n\
    \    }\n    for (int smaller = 0; smaller < order; smaller++) {\n        assert(!has_recurrence_of_order(sequence,\
    \ smaller));\n    }\n}\n\nvoid test_convolution() {\n    std::mt19937 rng(712367);\n\
    \    for (int iteration = 0; iteration < 30; iteration++) {\n        int n = 33\
    \ + int(rng() % 70);\n        int m = 33 + int(rng() % 70);\n        std::vector<mint>\
    \ a(n), b(m);\n        for (mint& value : a) value = mint(static_cast<uint32_t>(rng()));\n\
    \        for (mint& value : b) value = mint(static_cast<uint32_t>(rng()));\n \
    \       assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a,\
    \ b));\n        assert_equal(m1une::fps::convolution(a, a), m1une::fps::convolution_naive(a,\
    \ a));\n        assert_equal(m1une::fps::internal::convolution_998244353_blocked(a,\
    \ b, 64),\n                     m1une::fps::convolution_naive(a, b));\n    }\n\
    \n    std::vector<mint1e9> a(70), b(65);\n    for (mint1e9& value : a) value =\
    \ mint1e9(static_cast<uint32_t>(rng()));\n    for (mint1e9& value : b) value =\
    \ mint1e9(static_cast<uint32_t>(rng()));\n    assert_equal(m1une::fps::convolution(a,\
    \ b), m1une::fps::convolution_naive(a, b));\n}\n\nvoid test_series_functions()\
    \ {\n    Fps f(96);\n    f[0] = 1;\n    for (int i = 1; i < int(f.size()); i++)\
    \ f[i] = mint(i * i + 7);\n\n    Fps inverse = f.inv();\n    Fps identity = (f\
    \ * inverse).pre(int(f.size()));\n    assert(identity[0] == mint(1));\n    for\
    \ (int i = 1; i < int(identity.size()); i++) assert(identity[i] == mint(0));\n\
    \n    Fps logarithm = f.log();\n    assert_equal(logarithm.exp(), f);\n    assert_equal(f.derivative().integral().pre(int(f.size()))\
    \ + Fps(1, f[0]), f);\n\n    Fps cube = f.pow(3);\n    assert_equal(cube, ((f\
    \ * f) * f).pre(int(f.size())));\n\n    Fps shifted(40);\n    shifted[4] = 9;\n\
    \    for (int i = 5; i < int(shifted.size()); i++) shifted[i] = mint(i + 11);\n\
    \    auto root = (shifted * shifted).pre(70).sqrt(70);\n    assert(root.has_value());\n\
    \    assert_equal(((*root) * (*root)).pre(70), (shifted * shifted).pre(70));\n\
    \n    Fps beyond_precision(8);\n    beyond_precision[5] = 1;\n    auto zero_root\
    \ = beyond_precision.sqrt(5);\n    assert(zero_root.has_value());\n    assert_equal(*zero_root,\
    \ Fps(5));\n\n    Fps odd_leading(8);\n    odd_leading[3] = 1;\n    assert(!odd_leading.sqrt(8).has_value());\n\
    \n    Fps zero(20);\n    Fps one(20);\n    one[0] = 1;\n    assert_equal(zero.pow(0),\
    \ one);\n    assert_equal(zero.pow(7), zero);\n}\n\nvoid test_polynomial_operations()\
    \ {\n    Fps dividend(80), divisor(35);\n    for (int i = 0; i < int(dividend.size());\
    \ i++) dividend[i] = mint(i * 17 + 3);\n    for (int i = 0; i < int(divisor.size());\
    \ i++) divisor[i] = mint(i * 5 + 1);\n    auto division = dividend.divmod(divisor);\n\
    \    Fps restored = division.first * divisor + division.second;\n    restored.resize(dividend.size());\n\
    \    assert_equal(restored, dividend);\n    assert(division.second.size() < divisor.size());\n\
    \n    mint shift = 12345;\n    Fps translated = dividend.taylor_shift(shift);\n\
    \    for (int x = 0; x < 10; x++) {\n        assert(translated.evaluate(mint(x))\
    \ == dividend.evaluate(mint(x) + shift));\n    }\n}\n\nvoid test_multipoint_and_recurrence()\
    \ {\n    Fps polynomial(70);\n    for (int i = 0; i < int(polynomial.size());\
    \ i++) polynomial[i] = mint(i * i * 13 + 5);\n    std::vector<mint> points(70);\n\
    \    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);\n\
    \n    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);\n\
    \    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));\n\
    \    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);\n\
    \    assert_equal(interpolated, polynomial);\n    std::vector<mint> one_point(1,\
    \ mint(42));\n    std::vector<mint> one_value(1, mint(314));\n    assert_equal(m1une::fps::polynomial_interpolate(one_point,\
    \ one_value), Fps(1, mint(314)));\n    assert(m1une::fps::multipoint_evaluate(Fps(),\
    \ std::vector<mint>()).empty());\n\n    std::vector<mint> initial(2);\n    std::vector<mint>\
    \ recurrence(2);\n    initial[0] = 0;\n    initial[1] = 1;\n    recurrence[0]\
    \ = 1;\n    recurrence[1] = 1;\n    mint previous = 0;\n    mint current = 1;\n\
    \    for (uint64_t index = 0; index < 200; index++) {\n        mint expected =\
    \ index == 0 ? previous : current;\n        assert(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index) == expected);\n        if (index > 0) {\n            mint\
    \ next = previous + current;\n            previous = current;\n            current\
    \ = next;\n        }\n    }\n\n    assert(m1une::fps::berlekamp_massey(std::vector<mint>()).empty());\n\
    \    assert(m1une::fps::berlekamp_massey(std::vector<mint>(20)).empty());\n\n\
    \    std::vector<mint> fibonacci = {0, 1};\n    for (int i = 2; i < 30; i++) {\n\
    \        fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);\n    }\n  \
    \  std::vector<mint> fibonacci_recurrence =\n        m1une::fps::berlekamp_massey(fibonacci);\n\
    \    assert_equal(fibonacci_recurrence, std::vector<mint>{1, 1});\n\n    std::vector<mint>\
    \ suffix_zero = {1, 0, 0, 0, 0, 0};\n    std::vector<mint> suffix_zero_recurrence\
    \ =\n        m1une::fps::berlekamp_massey(suffix_zero);\n    assert_equal(suffix_zero_recurrence,\
    \ std::vector<mint>{0});\n\n    std::mt19937 recurrence_rng(2481632);\n    for\
    \ (int iteration = 0; iteration < 300; iteration++) {\n        const int size\
    \ = int(recurrence_rng() % 17);\n        std::vector<mint> sequence(size);\n \
    \       for (mint& value : sequence) value = mint(recurrence_rng() % 11);\n  \
    \      std::vector<mint> found = m1une::fps::berlekamp_massey(sequence);\n   \
    \     assert_recurrence(sequence, found);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_convolution();\n\
    \    test_series_functions();\n    test_polynomial_operations();\n    test_multipoint_and_recurrence();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../../math/fps/all.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    using mint1e9 = m1une::math::modint1000000007;\nusing Fps = m1une::fps::FormalPowerSeries<mint>;\n\
    \ntemplate <class Mint>\nvoid assert_equal(const std::vector<Mint>& lhs, const\
    \ std::vector<Mint>& rhs) {\n    assert(lhs.size() == rhs.size());\n    for (int\
    \ i = 0; i < int(lhs.size()); i++) assert(lhs[i] == rhs[i]);\n}\n\ntemplate <class\
    \ Mint>\nbool has_recurrence_of_order(const std::vector<Mint>& sequence, int order)\
    \ {\n    assert(0 <= order && order <= int(sequence.size()));\n    const int equation_count\
    \ = int(sequence.size()) - order;\n    std::vector<std::vector<Mint>> matrix(\n\
    \        equation_count, std::vector<Mint>(order + 1)\n    );\n    for (int row\
    \ = 0; row < equation_count; row++) {\n        const int index = order + row;\n\
    \        for (int i = 0; i < order; i++) {\n            matrix[row][i] = sequence[index\
    \ - i - 1];\n        }\n        matrix[row][order] = sequence[index];\n    }\n\
    \n    int pivot_row = 0;\n    for (int column = 0; column < order && pivot_row\
    \ < equation_count; column++) {\n        int pivot = pivot_row;\n        while\
    \ (pivot < equation_count && matrix[pivot][column] == Mint(0)) pivot++;\n    \
    \    if (pivot == equation_count) continue;\n        std::swap(matrix[pivot_row],\
    \ matrix[pivot]);\n\n        const Mint inverse = Mint(1) / matrix[pivot_row][column];\n\
    \        for (int j = column; j <= order; j++) matrix[pivot_row][j] *= inverse;\n\
    \        for (int row = pivot_row + 1; row < equation_count; row++) {\n      \
    \      const Mint scale = matrix[row][column];\n            if (scale == Mint(0))\
    \ continue;\n            for (int j = column; j <= order; j++) {\n           \
    \     matrix[row][j] -= scale * matrix[pivot_row][j];\n            }\n       \
    \ }\n        pivot_row++;\n    }\n\n    for (int row = pivot_row; row < equation_count;\
    \ row++) {\n        bool all_zero = true;\n        for (int column = 0; column\
    \ < order; column++) {\n            if (matrix[row][column] != Mint(0)) all_zero\
    \ = false;\n        }\n        if (all_zero && matrix[row][order] != Mint(0))\
    \ return false;\n    }\n    return true;\n}\n\ntemplate <class Mint>\nvoid assert_recurrence(const\
    \ std::vector<Mint>& sequence,\n                       const std::vector<Mint>&\
    \ recurrence) {\n    const int order = int(recurrence.size());\n    for (int index\
    \ = order; index < int(sequence.size()); index++) {\n        Mint expected = 0;\n\
    \        for (int i = 0; i < order; i++) {\n            expected += recurrence[i]\
    \ * sequence[index - i - 1];\n        }\n        assert(sequence[index] == expected);\n\
    \    }\n    for (int smaller = 0; smaller < order; smaller++) {\n        assert(!has_recurrence_of_order(sequence,\
    \ smaller));\n    }\n}\n\nvoid test_convolution() {\n    std::mt19937 rng(712367);\n\
    \    for (int iteration = 0; iteration < 30; iteration++) {\n        int n = 33\
    \ + int(rng() % 70);\n        int m = 33 + int(rng() % 70);\n        std::vector<mint>\
    \ a(n), b(m);\n        for (mint& value : a) value = mint(static_cast<uint32_t>(rng()));\n\
    \        for (mint& value : b) value = mint(static_cast<uint32_t>(rng()));\n \
    \       assert_equal(m1une::fps::convolution(a, b), m1une::fps::convolution_naive(a,\
    \ b));\n        assert_equal(m1une::fps::convolution(a, a), m1une::fps::convolution_naive(a,\
    \ a));\n        assert_equal(m1une::fps::internal::convolution_998244353_blocked(a,\
    \ b, 64),\n                     m1une::fps::convolution_naive(a, b));\n    }\n\
    \n    std::vector<mint1e9> a(70), b(65);\n    for (mint1e9& value : a) value =\
    \ mint1e9(static_cast<uint32_t>(rng()));\n    for (mint1e9& value : b) value =\
    \ mint1e9(static_cast<uint32_t>(rng()));\n    assert_equal(m1une::fps::convolution(a,\
    \ b), m1une::fps::convolution_naive(a, b));\n}\n\nvoid test_series_functions()\
    \ {\n    Fps f(96);\n    f[0] = 1;\n    for (int i = 1; i < int(f.size()); i++)\
    \ f[i] = mint(i * i + 7);\n\n    Fps inverse = f.inv();\n    Fps identity = (f\
    \ * inverse).pre(int(f.size()));\n    assert(identity[0] == mint(1));\n    for\
    \ (int i = 1; i < int(identity.size()); i++) assert(identity[i] == mint(0));\n\
    \n    Fps logarithm = f.log();\n    assert_equal(logarithm.exp(), f);\n    assert_equal(f.derivative().integral().pre(int(f.size()))\
    \ + Fps(1, f[0]), f);\n\n    Fps cube = f.pow(3);\n    assert_equal(cube, ((f\
    \ * f) * f).pre(int(f.size())));\n\n    Fps shifted(40);\n    shifted[4] = 9;\n\
    \    for (int i = 5; i < int(shifted.size()); i++) shifted[i] = mint(i + 11);\n\
    \    auto root = (shifted * shifted).pre(70).sqrt(70);\n    assert(root.has_value());\n\
    \    assert_equal(((*root) * (*root)).pre(70), (shifted * shifted).pre(70));\n\
    \n    Fps beyond_precision(8);\n    beyond_precision[5] = 1;\n    auto zero_root\
    \ = beyond_precision.sqrt(5);\n    assert(zero_root.has_value());\n    assert_equal(*zero_root,\
    \ Fps(5));\n\n    Fps odd_leading(8);\n    odd_leading[3] = 1;\n    assert(!odd_leading.sqrt(8).has_value());\n\
    \n    Fps zero(20);\n    Fps one(20);\n    one[0] = 1;\n    assert_equal(zero.pow(0),\
    \ one);\n    assert_equal(zero.pow(7), zero);\n}\n\nvoid test_polynomial_operations()\
    \ {\n    Fps dividend(80), divisor(35);\n    for (int i = 0; i < int(dividend.size());\
    \ i++) dividend[i] = mint(i * 17 + 3);\n    for (int i = 0; i < int(divisor.size());\
    \ i++) divisor[i] = mint(i * 5 + 1);\n    auto division = dividend.divmod(divisor);\n\
    \    Fps restored = division.first * divisor + division.second;\n    restored.resize(dividend.size());\n\
    \    assert_equal(restored, dividend);\n    assert(division.second.size() < divisor.size());\n\
    \n    mint shift = 12345;\n    Fps translated = dividend.taylor_shift(shift);\n\
    \    for (int x = 0; x < 10; x++) {\n        assert(translated.evaluate(mint(x))\
    \ == dividend.evaluate(mint(x) + shift));\n    }\n}\n\nvoid test_multipoint_and_recurrence()\
    \ {\n    Fps polynomial(70);\n    for (int i = 0; i < int(polynomial.size());\
    \ i++) polynomial[i] = mint(i * i * 13 + 5);\n    std::vector<mint> points(70);\n\
    \    for (int i = 0; i < int(points.size()); i++) points[i] = mint(i * 3 + 1);\n\
    \n    std::vector<mint> values = m1une::fps::multipoint_evaluate(polynomial, points);\n\
    \    for (int i = 0; i < int(points.size()); i++) assert(values[i] == polynomial.evaluate(points[i]));\n\
    \    Fps interpolated = m1une::fps::polynomial_interpolate(points, values);\n\
    \    assert_equal(interpolated, polynomial);\n    std::vector<mint> one_point(1,\
    \ mint(42));\n    std::vector<mint> one_value(1, mint(314));\n    assert_equal(m1une::fps::polynomial_interpolate(one_point,\
    \ one_value), Fps(1, mint(314)));\n    assert(m1une::fps::multipoint_evaluate(Fps(),\
    \ std::vector<mint>()).empty());\n\n    std::vector<mint> initial(2);\n    std::vector<mint>\
    \ recurrence(2);\n    initial[0] = 0;\n    initial[1] = 1;\n    recurrence[0]\
    \ = 1;\n    recurrence[1] = 1;\n    mint previous = 0;\n    mint current = 1;\n\
    \    for (uint64_t index = 0; index < 200; index++) {\n        mint expected =\
    \ index == 0 ? previous : current;\n        assert(m1une::fps::linear_recurrence_kth(initial,\
    \ recurrence, index) == expected);\n        if (index > 0) {\n            mint\
    \ next = previous + current;\n            previous = current;\n            current\
    \ = next;\n        }\n    }\n\n    assert(m1une::fps::berlekamp_massey(std::vector<mint>()).empty());\n\
    \    assert(m1une::fps::berlekamp_massey(std::vector<mint>(20)).empty());\n\n\
    \    std::vector<mint> fibonacci = {0, 1};\n    for (int i = 2; i < 30; i++) {\n\
    \        fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);\n    }\n  \
    \  std::vector<mint> fibonacci_recurrence =\n        m1une::fps::berlekamp_massey(fibonacci);\n\
    \    assert_equal(fibonacci_recurrence, std::vector<mint>{1, 1});\n\n    std::vector<mint>\
    \ suffix_zero = {1, 0, 0, 0, 0, 0};\n    std::vector<mint> suffix_zero_recurrence\
    \ =\n        m1une::fps::berlekamp_massey(suffix_zero);\n    assert_equal(suffix_zero_recurrence,\
    \ std::vector<mint>{0});\n\n    std::mt19937 recurrence_rng(2481632);\n    for\
    \ (int iteration = 0; iteration < 300; iteration++) {\n        const int size\
    \ = int(recurrence_rng() % 17);\n        std::vector<mint> sequence(size);\n \
    \       for (mint& value : sequence) value = mint(recurrence_rng() % 11);\n  \
    \      std::vector<mint> found = m1une::fps::berlekamp_massey(sequence);\n   \
    \     assert_recurrence(sequence, found);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_convolution();\n\
    \    test_series_functions();\n    test_polynomial_operations();\n    test_multipoint_and_recurrence();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - math/fps/all.hpp
  - math/fps/composition.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/fps/compositional_inverse.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/floating_point_convolution.hpp
  - math/fps/geometric_sequence_evaluation.hpp
  - math/fps/half_gcd.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/fps/polynomial_factorization.hpp
  - math/fps/polynomial_roots.hpp
  - math/fps/sparse_formal_power_series.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/fps_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/fps_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/fps_algorithms.test.cpp
- /verify/verify/math/fps/fps_algorithms.test.cpp.html
title: verify/math/fps/fps_algorithms.test.cpp
---
