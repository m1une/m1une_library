---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: template.hpp
    title: template.hpp
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
  bundledCode: "#line 1 \"verify/utilities/template_fast_io.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"template.hpp\"\n\n\n\
    \n#include <algorithm>\n#include <any>\n#include <array>\n#include <atomic>\n\
    #include <barrier>\n#include <bit>\n#include <bitset>\n#include <cassert>\n#include\
    \ <cctype>\n#include <cerrno>\n#include <cfenv>\n#include <cfloat>\n#include <charconv>\n\
    #include <chrono>\n#include <cinttypes>\n#include <climits>\n#include <clocale>\n\
    #include <cmath>\n#include <codecvt>\n#include <compare>\n#include <complex>\n\
    #include <concepts>\n#include <condition_variable>\n#include <coroutine>\n#include\
    \ <cstdint>\n#include <cstdio>\n#include <cstdlib>\n#include <csetjmp>\n#include\
    \ <csignal>\n#include <cstdarg>\n#include <cstddef>\n#include <cstring>\n#include\
    \ <ctime>\n#include <cuchar>\n#include <cwchar>\n#include <cwctype>\n#include\
    \ <deque>\n#include <exception>\n#include <execution>\n#include <filesystem>\n\
    #include <format>\n#include <forward_list>\n#include <fstream>\n#include <functional>\n\
    #include <future>\n#include <iomanip>\n#include <initializer_list>\n#include <iostream>\n\
    #include <ios>\n#include <iosfwd>\n#include <istream>\n#include <iterator>\n#include\
    \ <latch>\n#include <limits>\n#include <list>\n#include <locale>\n#include <map>\n\
    #include <memory>\n#include <memory_resource>\n#include <mutex>\n#include <new>\n\
    #include <numbers>\n#include <numeric>\n#include <optional>\n#include <ostream>\n\
    #include <queue>\n#include <random>\n#include <ranges>\n#include <ratio>\n#include\
    \ <regex>\n#include <scoped_allocator>\n#include <semaphore>\n#include <set>\n\
    #include <shared_mutex>\n#include <source_location>\n#include <span>\n#include\
    \ <sstream>\n#include <stack>\n#include <stdexcept>\n#include <stop_token>\n#include\
    \ <streambuf>\n#include <string>\n#include <string_view>\n#include <syncstream>\n\
    #include <system_error>\n#include <thread>\n#include <tuple>\n#include <type_traits>\n\
    #include <typeindex>\n#include <typeinfo>\n#include <unordered_map>\n#include\
    \ <unordered_set>\n#include <utility>\n#include <valarray>\n#include <variant>\n\
    #include <vector>\n#include <version>\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\
    \n\n#line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 103 \"template.hpp\"\nusing namespace\
    \ std;\n\nnamespace m1une {\nnamespace template_io {\n\ninline utilities::FastInput&\
    \ input() {\n    static utilities::FastInput instance;\n    return instance;\n\
    }\n\ninline utilities::FastOutput& output() {\n    static utilities::FastOutput\
    \ instance;\n    return instance;\n}\n\n}  // namespace template_io\n}  // namespace\
    \ m1une\n\nusing ll = long long;\nusing u32 = unsigned int;\nusing u64 = unsigned\
    \ long long;\nusing i128 = __int128;\nusing u128 = unsigned __int128;\n#ifdef\
    \ __SIZEOF_FLOAT128__\nusing f128 = __float128;\n#endif\n\ntemplate <class T>\n\
    constexpr T infty = 0;\ntemplate <>\nconstexpr int infty<int> = 1'000'000'000;\n\
    template <>\nconstexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;\ntemplate\
    \ <>\nconstexpr u32 infty<u32> = infty<int>;\ntemplate <>\nconstexpr u64 infty<u64>\
    \ = infty<ll>;\ntemplate <>\nconstexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;\n\
    template <>\nconstexpr double infty<double> = infty<ll>;\ntemplate <>\nconstexpr\
    \ long double infty<long double> = infty<ll>;\n\nusing pi = pair<int, int>;\n\
    using pl = pair<ll, ll>;\nusing vi = vector<int>;\nusing vl = vector<ll>;\ntemplate\
    \ <class T>\nusing vc = vector<T>;\ntemplate <class T>\nusing vvc = vector<vc<T>>;\n\
    using vvi = vvc<int>;\nusing vvl = vvc<ll>;\ntemplate <class T>\nusing vvvc =\
    \ vector<vvc<T>>;\ntemplate <class T>\nusing vvvvc = vector<vvvc<T>>;\ntemplate\
    \ <class T>\nusing vvvvvc = vector<vvvvc<T>>;\ntemplate <class T>\nusing pqg =\
    \ std::priority_queue<T, vector<T>, greater<T>>;\ntemplate <class T, class U>\n\
    using umap = unordered_map<T, U>;\n\n// template <typename K>\n// using tree =\
    \ __gnu_pbds::tree<K, __gnu_pbds::null_type, std::less<>,\n//                \
    \               __gnu_pbds::rb_tree_tag,\n//                               __gnu_pbds::tree_order_statistics_node_update>;\n\
    \n#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))\n\
    #define vvv(type, name, h, w, ...) \\\n    vector<vector<vector<type>>> name(h,\
    \ vector<vector<type>>(w, vector<type>(__VA_ARGS__)))\n#define vvvv(type, name,\
    \ a, b, c, ...)         \\\n    vector<vector<vector<vector<type>>>> name( \\\n\
    \        a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))\n\
    \n#define overload4(a, b, c, d, e, ...) e\n#define overload3(a, b, c, d, ...)\
    \ d\n\n// FOR(a) :=  for (ll _ = 0; _ < (ll)a; ++_)\n// FOR(i, a) := for (ll i\
    \ = 0; i < (ll)a; ++i)\n// FOR(i, a, b) := for (ll i = a; i < (ll)b; ++i)\n//\
    \ FOR(i, a, b, c) := for (ll i = a; i < (ll)b; i += (c))\n// FOR_R(a) := for (ll\
    \ i = (a) - 1; i >= 0; --i)\n// FOR_R(i, a) := for (ll i = (a) - 1; i >= 0; --i)\n\
    // FOR_R(i, a, b) := for (ll i = (b) - 1; i >= (ll)a; --i)\n#define FOR1(a) for\
    \ (ll _ = 0; _ < (ll)a; ++_)\n#define FOR2(i, a) for (ll i = 0; i < (ll)a; ++i)\n\
    #define FOR3(i, a, b) for (ll i = a; i < (ll)b; ++i)\n#define FOR4(i, a, b, c)\
    \ for (ll i = a; i < (ll)b; i += (c))\n#define FOR1_R(a) for (ll i = (a) - 1;\
    \ i >= 0; --i)\n#define FOR2_R(i, a) for (ll i = (a) - 1; i >= 0; --i)\n#define\
    \ FOR3_R(i, a, b) for (ll i = (b) - 1; i >= (ll)a; --i)\n#define FOR(...) overload4(__VA_ARGS__,\
    \ FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)\n#define FOR_R(...) overload3(__VA_ARGS__,\
    \ FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)\n\n#define FORI1(a) for (int _ = 0; _ <\
    \ (int)a; ++_)\n#define FORI2(i, a) for (int i = 0; i < (int)a; ++i)\n#define\
    \ FORI3(i, a, b) for (int i = a; i < (int)b; ++i)\n#define FORI4(i, a, b, c) for\
    \ (int i = a; i < (int)b; i += (c))\n#define FORI1_R(a) for (int i = (a) - 1;\
    \ i >= 0; --i)\n#define FORI2_R(i, a) for (int i = (a) - 1; i >= 0; --i)\n#define\
    \ FORI3_R(i, a, b) for (int i = (b) - 1; i >= (int)a; --i)\n#define FORI(...)\
    \ overload4(__VA_ARGS__, FORI4, FORI3, FORI2, FORI1)(__VA_ARGS__)\n#define FORI_R(...)\
    \ overload3(__VA_ARGS__, FORI3_R, FORI2_R, FORI1_R)(__VA_ARGS__)\n\n#define FOR_subset(t,\
    \ s) for (int t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))\n#define all(x)\
    \ x.begin(), x.end()\n#define rall(x) x.rbegin(), x.rend()\n\nint popcnt(int x)\
    \ {\n    return __builtin_popcount(x);\n}\nint popcnt(u32 x) {\n    return __builtin_popcount(x);\n\
    }\nint popcnt(ll x) {\n    return __builtin_popcountll(x);\n}\nint popcnt(u64\
    \ x) {\n    return __builtin_popcountll(x);\n}\nint popcnt_mod_2(int x) {\n  \
    \  return __builtin_parity(x);\n}\nint popcnt_mod_2(u32 x) {\n    return __builtin_parity(x);\n\
    }\nint popcnt_mod_2(ll x) {\n    return __builtin_parityll(x);\n}\nint popcnt_mod_2(u64\
    \ x) {\n    return __builtin_parityll(x);\n}\n// (0, 1, 2, 3, 4) -> (-1, 0, 1,\
    \ 1, 2)\nint topbit(int x) {\n    return (x == 0 ? -1 : 31 - __builtin_clz(x));\n\
    }\nint topbit(u32 x) {\n    return (x == 0 ? -1 : 31 - __builtin_clz(x));\n}\n\
    int topbit(ll x) {\n    return (x == 0 ? -1 : 63 - __builtin_clzll(x));\n}\nint\
    \ topbit(u64 x) {\n    return (x == 0 ? -1 : 63 - __builtin_clzll(x));\n}\n//\
    \ (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)\nint lowbit(int x) {\n    return (x == 0\
    \ ? -1 : __builtin_ctz(x));\n}\nint lowbit(u32 x) {\n    return (x == 0 ? -1 :\
    \ __builtin_ctz(x));\n}\nint lowbit(ll x) {\n    return (x == 0 ? -1 : __builtin_ctzll(x));\n\
    }\nint lowbit(u64 x) {\n    return (x == 0 ? -1 : __builtin_ctzll(x));\n}\n\n\
    template <typename T>\nT floor(T a, T b) {\n    return a / b - (a % b && (a ^\
    \ b) < 0);\n}\ntemplate <typename T>\nT ceil(T x, T y) {\n    return floor(x +\
    \ y - 1, y);\n}\ntemplate <typename T>\nT bmod(T x, T y) {\n    return x - y *\
    \ floor(x, y);\n}\ntemplate <typename T>\npair<T, T> divmod(T x, T y) {\n    T\
    \ q = floor(x, y);\n    return {q, x - q * y};\n}\n\ntemplate <typename T, typename\
    \ U>\nT POW(U x_, int n) {\n    T x = x_;\n    T ret = 1;\n    while (n > 0) {\n\
    \        if (n & 1) ret *= x;\n        x *= x;\n        n >>= 1;\n    }\n    return\
    \ ret;\n}\n\ntemplate <typename T, typename U>\nT SUM(const vector<U>& A) {\n\
    \    T sm = 0;\n    for (auto&& a : A) sm += a;\n    return sm;\n}\n\n#define\
    \ LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))\n#define UB(c, x) distance((c).begin(),\
    \ upper_bound(all(c), (x)))\n#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)),\
    \ x.end()), x.shrink_to_fit()\n\ntemplate <class T, class S>\ninline bool chmax(T&\
    \ a, const S& b) {\n    return (a < b ? a = b, 1 : 0);\n}\ntemplate <class T,\
    \ class S>\ninline bool chmin(T& a, const S& b) {\n    return (a > b ? a = b,\
    \ 1 : 0);\n}\n\n// ? \u306F -1\nvc<int> s_to_vi(const string& S, char first_char)\
    \ {\n    vc<int> A(S.size());\n    FOR(i, S.size()) {\n        A[i] = (S[i] !=\
    \ '?' ? S[i] - first_char : -1);\n    }\n    return A;\n}\n\ntemplate <typename\
    \ T, typename U>\nvector<T> cumsum(vector<U>& A, int off = 1) {\n    int N = A.size();\n\
    \    vector<T> B(N + 1);\n    FOR(i, N) {\n        B[i + 1] = B[i] + A[i];\n \
    \   }\n    if (off == 0) B.erase(B.begin());\n    return B;\n}\n\ntemplate <typename\
    \ T>\nvector<int> argsort(const vector<T>& A) {\n    vector<int> ids(A.size());\n\
    \    iota(all(ids), 0);\n    sort(all(ids), [&](int i, int j) { return (A[i] ==\
    \ A[j] ? i < j : A[i] < A[j]); });\n    return ids;\n}\n\n// A[I[0]], A[I[1]],\
    \ ...\ntemplate <typename T>\nvc<T> rearrange(const vc<T>& A, const vc<int>& I)\
    \ {\n    vc<T> B(I.size());\n    FOR(i, I.size()) B[i] = A[I[i]];\n    return\
    \ B;\n}\n\ntemplate <class... T>\nconstexpr auto min(T... a) {\n    return min(initializer_list<common_type_t<T...>>{a...});\n\
    }\ntemplate <class... T>\nconstexpr auto max(T... a) {\n    return max(initializer_list<common_type_t<T...>>{a...});\n\
    }\n\ntemplate <class... Ts>\nbool scan(Ts&... values) {\n    return m1une::template_io::input().read(values...);\n\
    }\n\ntemplate <class... Ts>\nvoid print(const Ts&... values) {\n    m1une::template_io::output().println(values...);\n\
    }\nvoid YESNO(bool b) {\n    m1une::template_io::output().println(b ? \"YES\"\
    \ : \"NO\");\n}\nvoid YesNo(bool b) {\n    m1une::template_io::output().println(b\
    \ ? \"Yes\" : \"No\");\n}\nvoid YES() {\n    m1une::template_io::output().println(\"\
    YES\");\n}\nvoid NO() {\n    m1une::template_io::output().println(\"NO\");\n}\n\
    void Yes() {\n    m1une::template_io::output().println(\"Yes\");\n}\nvoid No()\
    \ {\n    m1une::template_io::output().println(\"No\");\n}\n\n#line 4 \"verify/utilities/template_fast_io.test.cpp\"\
    \n\n#line 10 \"verify/utilities/template_fast_io.test.cpp\"\n\nstd::FILE* helper_output\
    \ = std::tmpfile();\n\nvoid test_output_helpers() {\n    assert(helper_output\
    \ != nullptr);\n    const int saved_stdout = ::dup(::fileno(stdout));\n    assert(saved_stdout\
    \ != -1);\n    assert(::dup2(::fileno(helper_output), ::fileno(stdout)) != -1);\n\
    \n    print();\n    print(1, \"two\");\n\n    std::vector<int> values(3);\n  \
    \  values[0] = 3;\n    values[1] = 4;\n    values[2] = 5;\n    print(values);\n\
    \n    const std::pair<int, int> edge(6, 7);\n    print(edge);\n\n    m1une::template_io::output().set_range_separator('\\\
    n');\n    print(values);\n    m1une::template_io::output().set_range_separator('\
    \ ');\n\n    YESNO(true);\n    YESNO(false);\n    YesNo(true);\n    YesNo(false);\n\
    \    YES();\n    NO();\n    Yes();\n    No();\n    m1une::template_io::output().flush();\n\
    \    std::fflush(stdout);\n    assert(::dup2(saved_stdout, ::fileno(stdout)) !=\
    \ -1);\n    ::close(saved_stdout);\n\n    std::rewind(helper_output);\n    char\
    \ buffer[128];\n    const std::size_t length = std::fread(buffer, 1, sizeof(buffer),\
    \ helper_output);\n    const std::string result(buffer, buffer + length);\n  \
    \  assert(\n        result\n        == \"\\n1 two\\n3 4 5\\n6 7\\n3\\n4\\n5\\\
    n\"\n           \"YES\\nNO\\nYes\\nNo\\nYES\\nNO\\nYes\\nNo\\n\"\n    );\n}\n\n\
    int main() {\n    test_output_helpers();\n\n    long long a, b;\n    std::scanf(\"\
    %lld%lld\", &a, &b);\n    print(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../template.hpp\"\n\n#include <cassert>\n#include <cstdio>\n#include <string>\n\
    #include <unistd.h>\n#include <vector>\n\nstd::FILE* helper_output = std::tmpfile();\n\
    \nvoid test_output_helpers() {\n    assert(helper_output != nullptr);\n    const\
    \ int saved_stdout = ::dup(::fileno(stdout));\n    assert(saved_stdout != -1);\n\
    \    assert(::dup2(::fileno(helper_output), ::fileno(stdout)) != -1);\n\n    print();\n\
    \    print(1, \"two\");\n\n    std::vector<int> values(3);\n    values[0] = 3;\n\
    \    values[1] = 4;\n    values[2] = 5;\n    print(values);\n\n    const std::pair<int,\
    \ int> edge(6, 7);\n    print(edge);\n\n    m1une::template_io::output().set_range_separator('\\\
    n');\n    print(values);\n    m1une::template_io::output().set_range_separator('\
    \ ');\n\n    YESNO(true);\n    YESNO(false);\n    YesNo(true);\n    YesNo(false);\n\
    \    YES();\n    NO();\n    Yes();\n    No();\n    m1une::template_io::output().flush();\n\
    \    std::fflush(stdout);\n    assert(::dup2(saved_stdout, ::fileno(stdout)) !=\
    \ -1);\n    ::close(saved_stdout);\n\n    std::rewind(helper_output);\n    char\
    \ buffer[128];\n    const std::size_t length = std::fread(buffer, 1, sizeof(buffer),\
    \ helper_output);\n    const std::string result(buffer, buffer + length);\n  \
    \  assert(\n        result\n        == \"\\n1 two\\n3 4 5\\n6 7\\n3\\n4\\n5\\\
    n\"\n           \"YES\\nNO\\nYes\\nNo\\nYES\\nNO\\nYes\\nNo\\n\"\n    );\n}\n\n\
    int main() {\n    test_output_helpers();\n\n    long long a, b;\n    std::scanf(\"\
    %lld%lld\", &a, &b);\n    print(a + b);\n}\n"
  dependsOn:
  - template.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/utilities/template_fast_io.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 13:30:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/template_fast_io.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/template_fast_io.test.cpp
- /verify/verify/utilities/template_fast_io.test.cpp.html
title: verify/utilities/template_fast_io.test.cpp
---
