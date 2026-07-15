---
data:
  _extendedDependsOn:
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
    \ <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include\
    \ <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace utilities\
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
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
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
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 6 \"verify/utilities/basic_utilities.test.cpp\"\n#include <limits>\n\
    #include <sstream>\n#include <stdexcept>\n#line 10 \"verify/utilities/basic_utilities.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"utilities/bigint.hpp\"\n\n\n\n#line 5 \"utilities/bigint.hpp\"\
    \n#include <iomanip>\n#include <iostream>\n#line 9 \"utilities/bigint.hpp\"\n\
    #include <tuple>\n#line 11 \"utilities/bigint.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nstruct BigInt {\n    static constexpr int BASE = 1000000000;\n\
    \    static constexpr int BASE_DIGITS = 9;\n\n    std::vector<int> a;\n    int\
    \ sign;\n\n    BigInt() : sign(1) {}\n\n    BigInt(long long v) {\n        *this\
    \ = v;\n    }\n\n    BigInt(const std::string& s) {\n        read(s);\n    }\n\
    \n    BigInt& operator=(long long v) {\n        sign = 1;\n        unsigned long\
    \ long magnitude = static_cast<unsigned long long>(v);\n        if (v < 0) {\n\
    \            sign = -1;\n            magnitude = 0 - magnitude;\n        }\n \
    \       a.clear();\n        for (; magnitude > 0; magnitude /= BASE) {\n     \
    \       a.push_back(int(magnitude % BASE));\n        }\n        return *this;\n\
    \    }\n\n    BigInt& operator=(const std::string& s) {\n        read(s);\n  \
    \      return *this;\n    }\n\n    void trim() {\n        while (!a.empty() &&\
    \ a.back() == 0) {\n            a.pop_back();\n        }\n        if (a.empty())\
    \ sign = 1;\n    }\n\n    void read(const std::string& s) {\n        sign = 1;\n\
    \        a.clear();\n        int pos = 0;\n        while (pos < (int)s.size()\
    \ && (s[pos] == '-' || s[pos] == '+')) {\n            if (s[pos] == '-') sign\
    \ = -1;\n            ++pos;\n        }\n        for (int i = int(s.size()) - 1;\
    \ i >= pos; i -= BASE_DIGITS) {\n            int x = 0;\n            for (int\
    \ j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {\n                x =\
    \ x * 10 + (s[j] - '0');\n            }\n            a.push_back(x);\n       \
    \ }\n        trim();\n    }\n\n    std::string to_string() const {\n        if\
    \ (a.empty()) return \"0\";\n        std::string res = \"\";\n        if (sign\
    \ == -1) res += '-';\n        res += std::to_string(a.back());\n        for (int\
    \ i = (int)a.size() - 2; i >= 0; --i) {\n            std::string block = std::to_string(a[i]);\n\
    \            res += std::string(BASE_DIGITS - block.length(), '0') + block;\n\
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
    \ BigInt& x, const BigInt& y) {\n        return !(x < y) && !(y < x);\n    }\n\
    \    friend bool operator!=(const BigInt& x, const BigInt& y) {\n        return\
    \ x < y || y < x;\n    }\n\n    BigInt& operator+=(const BigInt& other) {\n  \
    \      if (other.is_zero()) return *this;\n        if (is_zero()) return *this\
    \ = other;\n        if (sign != other.sign) return *this -= (-other);\n      \
    \  for (int i = 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry;\
    \ ++i) {\n            if (i == (int)a.size()) a.push_back(0);\n            a[i]\
    \ += carry + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry =\
    \ a[i] >= BASE;\n            if (carry) a[i] -= BASE;\n        }\n        return\
    \ *this;\n    }\n\n    BigInt& operator-=(const BigInt& other) {\n        if (other.is_zero())\
    \ return *this;\n        if (is_zero()) return *this = -other;\n        if (sign\
    \ != other.sign) return *this += (-other);\n        if (abs() < other.abs()) {\n\
    \            BigInt tmp = other;\n            tmp -= *this;\n            *this\
    \ = tmp;\n            sign = -sign;\n            return *this;\n        }\n  \
    \      for (int i = 0, carry = 0; i < (int)other.a.size() || carry; ++i) {\n \
    \           a[i] -= carry + (i < (int)other.a.size() ? other.a[i] : 0);\n    \
    \        carry = a[i] < 0;\n            if (carry) a[i] += BASE;\n        }\n\
    \        trim();\n        return *this;\n    }\n\n    BigInt& operator*=(int v)\
    \ {\n        long long multiplier = v;\n        if (multiplier < 0) {\n      \
    \      sign = -sign;\n            multiplier = -multiplier;\n        }\n     \
    \   long long carry = 0;\n        for (int i = 0; i < (int)a.size() || carry;\
    \ ++i) {\n            if (i == (int)a.size()) a.push_back(0);\n            const\
    \ long long cur = a[i] * multiplier + carry;\n            carry = cur / BASE;\n\
    \            a[i] = (int)(cur % BASE);\n        }\n        trim();\n        return\
    \ *this;\n    }\n\n    BigInt& operator*=(const BigInt& other) {\n        if (is_zero()\
    \ || other.is_zero()) return *this = 0;\n        std::vector<int> res(a.size()\
    \ + other.a.size());\n        for (int i = 0; i < (int)a.size(); ++i) {\n    \
    \        for (int j = 0, carry = 0; j < (int)other.a.size() || carry; ++j) {\n\
    \                long long cur = res[i + j] + a[i] * (long long)(j < (int)other.a.size()\
    \ ? other.a[j] : 0) + carry;\n                carry = (int)(cur / BASE);\n   \
    \             res[i + j] = (int)(cur % BASE);\n            }\n        }\n    \
    \    a = res;\n        sign *= other.sign;\n        trim();\n        return *this;\n\
    \    }\n\n    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const\
    \ BigInt& b1) {\n        if (b1.is_zero()) {\n            throw std::domain_error(\"\
    BigInt division by zero\");\n        }\n        BigInt a = a1.abs(), b = b1.abs(),\
    \ q, r;\n        q.a.resize(a.a.size());\n        for (int i = (int)a.a.size()\
    \ - 1; i >= 0; --i) {\n            r *= BASE;\n            r += a.a[i];\n    \
    \        int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];\n          \
    \  int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];\n        \
    \    int d = ((long long)BASE * s1 + s2) / b.a.back();\n            r -= b * d;\n\
    \            while (r < 0) {\n                r += b;\n                --d;\n\
    \            }\n            q.a[i] = d;\n        }\n        q.sign = a1.sign *\
    \ b1.sign;\n        r.sign = a1.sign;\n        q.trim();\n        r.trim();\n\
    \        return {q, r};\n    }\n\n    BigInt& operator/=(const BigInt& other)\
    \ {\n        return *this = divmod(*this, other).first;\n    }\n    BigInt& operator%=(const\
    \ BigInt& other) {\n        return *this = divmod(*this, other).second;\n    }\n\
    \n    friend BigInt operator+(BigInt x, const BigInt& y) {\n        return x +=\
    \ y;\n    }\n    friend BigInt operator-(BigInt x, const BigInt& y) {\n      \
    \  return x -= y;\n    }\n    friend BigInt operator*(BigInt x, const BigInt&\
    \ y) {\n        return x *= y;\n    }\n    friend BigInt operator/(BigInt x, const\
    \ BigInt& y) {\n        return x /= y;\n    }\n    friend BigInt operator%(BigInt\
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
    \n#include <string_view>\n#line 17 \"utilities/random.hpp\"\n#include <unordered_set>\n\
    #line 20 \"utilities/random.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    \nstruct RandomGraphOptions {\n    bool directed = false;\n    bool allow_self_loops\
    \ = false;\n    bool allow_parallel_edges = false;\n};\n\nstruct Random {\n  \
    \ private:\n    std::mt19937_64 _engine;\n\n    static unsigned long long chrono_seed()\
    \ {\n        return static_cast<unsigned long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
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
  - utilities/int128.hpp
  - utilities/random.hpp
  - utilities/timer.hpp
  isVerificationFile: true
  path: verify/utilities/basic_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/basic_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/basic_utilities.test.cpp
- /verify/verify/utilities/basic_utilities.test.cpp.html
title: verify/utilities/basic_utilities.test.cpp
---
