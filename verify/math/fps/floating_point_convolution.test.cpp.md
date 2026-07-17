---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/floating_point_convolution.hpp
    title: Floating-Point Convolution
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
  bundledCode: "#line 1 \"verify/math/fps/floating_point_convolution.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"math/fps/floating_point_convolution.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <bit>\n#include <cmath>\n#include <complex>\n\
    #include <concepts>\n#include <numbers>\n#include <type_traits>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace fps {\n\nnamespace floating_point_convolution_detail\
    \ {\n\ntemplate <std::floating_point Real>\nvoid fft(std::vector<std::complex<Real>>&\
    \ values, bool inverse) {\n    int size = int(values.size());\n    for (int index\
    \ = 1, reversed = 0; index < size; ++index) {\n        int bit = size >> 1;\n\
    \        while (reversed & bit) {\n            reversed ^= bit;\n            bit\
    \ >>= 1;\n        }\n        reversed ^= bit;\n        if (index < reversed) std::swap(values[index],\
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
    \n#line 4 \"verify/math/fps/floating_point_convolution.test.cpp\"\n\n#line 6 \"\
    verify/math/fps/floating_point_convolution.test.cpp\"\n#include <cassert>\n#line\
    \ 9 \"verify/math/fps/floating_point_convolution.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#line 16 \"utilities/fast_io.hpp\"\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/math/fps/floating_point_convolution.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class T>\nstd::vector<T> naive(\n    const std::vector<T>&\
    \ first,\n    const std::vector<T>& second\n) {\n    if (first.empty() || second.empty())\
    \ return {};\n    std::vector<T> result(first.size() + second.size() - 1);\n \
    \   for (std::size_t i = 0; i < first.size(); ++i) {\n        for (std::size_t\
    \ j = 0; j < second.size(); ++j) {\n            result[i + j] += first[i] * second[j];\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_fixed() {\n    std::vector<double>\
    \ first = {1.5, 2.0};\n    std::vector<double> second = {3.0, -1.0};\n    auto\
    \ result = m1une::fps::convolution_fft(first, second);\n    assert(std::fabs(result[0]\
    \ - 4.5) < 1e-12);\n    assert(std::fabs(result[1] - 4.5) < 1e-12);\n    assert(std::fabs(result[2]\
    \ + 2.0) < 1e-12);\n\n    std::vector<std::complex<double>> complex_first;\n \
    \   complex_first.emplace_back(1, 2);\n    complex_first.emplace_back(3, -1);\n\
    \    std::vector<std::complex<double>> complex_second;\n    complex_second.emplace_back(-2,\
    \ 1);\n    complex_second.emplace_back(0, 4);\n    auto complex_result =\n   \
    \     m1une::fps::convolution_fft(complex_first, complex_second);\n    auto complex_expected\
    \ = naive(complex_first, complex_second);\n    for (std::size_t index = 0; index\
    \ < complex_result.size(); ++index) {\n        assert(std::abs(complex_result[index]\
    \ - complex_expected[index]) < 1e-11);\n    }\n\n    std::vector<long long> integers\
    \ = {1, -2, 3, 4};\n    assert(\n        m1une::fps::convolution_round(integers,\
    \ integers)\n        == naive(integers, integers)\n    );\n    assert(\n     \
    \   m1une::fps::convolution_fft(\n            std::vector<double>(),\n       \
    \     std::vector<double>{1}\n        ).empty()\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1409;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; ++trial) {\n        int first_size\
    \ = int(random() % 100);\n        int second_size = int(random() % 100);\n   \
    \     std::vector<long double> first(first_size);\n        std::vector<long double>\
    \ second(second_size);\n        for (long double& value : first) {\n         \
    \   value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        for (long double& value : second) {\n        \
    \    value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        auto actual = m1une::fps::convolution_fft(first,\
    \ second);\n        auto expected = naive(first, second);\n        for (std::size_t\
    \ index = 0; index < actual.size(); ++index) {\n            long double magnitude\
    \ = 0;\n            for (std::size_t first_index = 0; first_index < first.size();\
    \ ++first_index) {\n                if (index < first_index) continue;\n     \
    \           std::size_t second_index = index - first_index;\n                if\
    \ (second_index < second.size()) {\n                    magnitude += std::fabs(\n\
    \                        first[first_index] * second[second_index]\n         \
    \           );\n                }\n            }\n            [[maybe_unused]]\
    \ long double tolerance =\n                1e-12L * std::max(1.0L, magnitude);\n\
    \            assert(std::fabs(actual[index] - expected[index]) <= tolerance);\n\
    \        }\n\n        std::vector<long long> integer_first(first_size);\n    \
    \    std::vector<long long> integer_second(second_size);\n        for (long long&\
    \ value : integer_first) {\n            value = static_cast<long long>(random()\
    \ % 2001) - 1000;\n        }\n        for (long long& value : integer_second)\
    \ {\n            value = static_cast<long long>(random() % 2001) - 1000;\n   \
    \     }\n        assert(\n            m1une::fps::convolution_round(integer_first,\
    \ integer_second)\n            == naive(integer_first, integer_second)\n     \
    \   );\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    long long a, b;\n    fast_input >> a >> b;\n  \
    \  fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../math/fps/floating_point_convolution.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <complex>\n#include <cstdint>\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n#include <vector>\n\nnamespace {\n\ntemplate\
    \ <class T>\nstd::vector<T> naive(\n    const std::vector<T>& first,\n    const\
    \ std::vector<T>& second\n) {\n    if (first.empty() || second.empty()) return\
    \ {};\n    std::vector<T> result(first.size() + second.size() - 1);\n    for (std::size_t\
    \ i = 0; i < first.size(); ++i) {\n        for (std::size_t j = 0; j < second.size();\
    \ ++j) {\n            result[i + j] += first[i] * second[j];\n        }\n    }\n\
    \    return result;\n}\n\nvoid test_fixed() {\n    std::vector<double> first =\
    \ {1.5, 2.0};\n    std::vector<double> second = {3.0, -1.0};\n    auto result\
    \ = m1une::fps::convolution_fft(first, second);\n    assert(std::fabs(result[0]\
    \ - 4.5) < 1e-12);\n    assert(std::fabs(result[1] - 4.5) < 1e-12);\n    assert(std::fabs(result[2]\
    \ + 2.0) < 1e-12);\n\n    std::vector<std::complex<double>> complex_first;\n \
    \   complex_first.emplace_back(1, 2);\n    complex_first.emplace_back(3, -1);\n\
    \    std::vector<std::complex<double>> complex_second;\n    complex_second.emplace_back(-2,\
    \ 1);\n    complex_second.emplace_back(0, 4);\n    auto complex_result =\n   \
    \     m1une::fps::convolution_fft(complex_first, complex_second);\n    auto complex_expected\
    \ = naive(complex_first, complex_second);\n    for (std::size_t index = 0; index\
    \ < complex_result.size(); ++index) {\n        assert(std::abs(complex_result[index]\
    \ - complex_expected[index]) < 1e-11);\n    }\n\n    std::vector<long long> integers\
    \ = {1, -2, 3, 4};\n    assert(\n        m1une::fps::convolution_round(integers,\
    \ integers)\n        == naive(integers, integers)\n    );\n    assert(\n     \
    \   m1une::fps::convolution_fft(\n            std::vector<double>(),\n       \
    \     std::vector<double>{1}\n        ).empty()\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1409;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 3000; ++trial) {\n        int first_size\
    \ = int(random() % 100);\n        int second_size = int(random() % 100);\n   \
    \     std::vector<long double> first(first_size);\n        std::vector<long double>\
    \ second(second_size);\n        for (long double& value : first) {\n         \
    \   value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        for (long double& value : second) {\n        \
    \    value =\n                (static_cast<long long>(random() % 2001) - 1000)\
    \ / 100.0L;\n        }\n        auto actual = m1une::fps::convolution_fft(first,\
    \ second);\n        auto expected = naive(first, second);\n        for (std::size_t\
    \ index = 0; index < actual.size(); ++index) {\n            long double magnitude\
    \ = 0;\n            for (std::size_t first_index = 0; first_index < first.size();\
    \ ++first_index) {\n                if (index < first_index) continue;\n     \
    \           std::size_t second_index = index - first_index;\n                if\
    \ (second_index < second.size()) {\n                    magnitude += std::fabs(\n\
    \                        first[first_index] * second[second_index]\n         \
    \           );\n                }\n            }\n            [[maybe_unused]]\
    \ long double tolerance =\n                1e-12L * std::max(1.0L, magnitude);\n\
    \            assert(std::fabs(actual[index] - expected[index]) <= tolerance);\n\
    \        }\n\n        std::vector<long long> integer_first(first_size);\n    \
    \    std::vector<long long> integer_second(second_size);\n        for (long long&\
    \ value : integer_first) {\n            value = static_cast<long long>(random()\
    \ % 2001) - 1000;\n        }\n        for (long long& value : integer_second)\
    \ {\n            value = static_cast<long long>(random() % 2001) - 1000;\n   \
    \     }\n        assert(\n            m1une::fps::convolution_round(integer_first,\
    \ integer_second)\n            == naive(integer_first, integer_second)\n     \
    \   );\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n\n    long long a, b;\n    fast_input >> a >> b;\n  \
    \  fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - math/fps/floating_point_convolution.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/fps/floating_point_convolution.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/floating_point_convolution.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/floating_point_convolution.test.cpp
- /verify/verify/math/fps/floating_point_convolution.test.cpp.html
title: verify/math/fps/floating_point_convolution.test.cpp
---
