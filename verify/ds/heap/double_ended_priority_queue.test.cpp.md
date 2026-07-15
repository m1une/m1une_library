---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/heap/double_ended_priority_queue.hpp
    title: Double-Ended Priority Queue
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
    PROBLEM: https://judge.yosupo.jp/problem/double_ended_priority_queue
    links:
    - https://judge.yosupo.jp/problem/double_ended_priority_queue
  bundledCode: "#line 1 \"verify/ds/heap/double_ended_priority_queue.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <functional>\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/ds/heap/double_ended_priority_queue.test.cpp\"\
    \n#include <set>\n#include <vector>\n\n#line 1 \"ds/heap/double_ended_priority_queue.hpp\"\
    \n\n\n\n#include <bit>\n#line 8 \"ds/heap/double_ended_priority_queue.hpp\"\n\
    #include <initializer_list>\n#line 11 \"ds/heap/double_ended_priority_queue.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Min-max heap supporting access to\
    \ both extremes of a total ordering.\ntemplate <class T, class Compare = std::less<T>>\n\
    class DoubleEndedPriorityQueue {\n   private:\n    std::vector<T> _values;\n \
    \   [[no_unique_address]] Compare _compare;\n\n    static std::size_t parent(std::size_t\
    \ index) {\n        return (index - 1) / 2;\n    }\n\n    static std::size_t grandparent(std::size_t\
    \ index) {\n        return (index - 3) / 4;\n    }\n\n    static bool is_min_level(std::size_t\
    \ index) {\n        const int level = int(std::bit_width(index + 1)) - 1;\n  \
    \      return level % 2 == 0;\n    }\n\n    void bubble_up_min(std::size_t index)\
    \ {\n        while (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[index], _values[ancestor])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    void bubble_up_max(std::size_t index) {\n        while\
    \ (index >= 3) {\n            const std::size_t ancestor = grandparent(index);\n\
    \            if (!_compare(_values[ancestor], _values[index])) break;\n      \
    \      std::swap(_values[index], _values[ancestor]);\n            index = ancestor;\n\
    \        }\n    }\n\n    std::size_t minimum_descendant(std::size_t index) const\
    \ {\n        std::size_t result = _values.size();\n        const std::size_t first_child\
    \ = index * 2 + 1;\n        const std::size_t first_grandchild = index * 4 + 3;\n\
    \        for (std::size_t candidate = first_child;\n             candidate < _values.size()\
    \ && candidate < first_child + 2;\n             candidate++) {\n            if\
    \ (result == _values.size() ||\n                _compare(_values[candidate], _values[result]))\
    \ {\n                result = candidate;\n            }\n        }\n        for\
    \ (std::size_t candidate = first_grandchild;\n             candidate < _values.size()\
    \ && candidate < first_grandchild + 4;\n             candidate++) {\n        \
    \    if (result == _values.size() ||\n                _compare(_values[candidate],\
    \ _values[result])) {\n                result = candidate;\n            }\n  \
    \      }\n        return result;\n    }\n\n    std::size_t maximum_descendant(std::size_t\
    \ index) const {\n        std::size_t result = _values.size();\n        const\
    \ std::size_t first_child = index * 2 + 1;\n        const std::size_t first_grandchild\
    \ = index * 4 + 3;\n        for (std::size_t candidate = first_child;\n      \
    \       candidate < _values.size() && candidate < first_child + 2;\n         \
    \    candidate++) {\n            if (result == _values.size() ||\n           \
    \     _compare(_values[result], _values[candidate])) {\n                result\
    \ = candidate;\n            }\n        }\n        for (std::size_t candidate =\
    \ first_grandchild;\n             candidate < _values.size() && candidate < first_grandchild\
    \ + 4;\n             candidate++) {\n            if (result == _values.size()\
    \ ||\n                _compare(_values[result], _values[candidate])) {\n     \
    \           result = candidate;\n            }\n        }\n        return result;\n\
    \    }\n\n    void trickle_down_min(std::size_t index) {\n        while (true)\
    \ {\n            const std::size_t descendant = minimum_descendant(index);\n \
    \           if (descendant == _values.size()) return;\n            if (parent(descendant)\
    \ == index) {\n                if (_compare(_values[descendant], _values[index]))\
    \ {\n                    std::swap(_values[descendant], _values[index]);\n   \
    \             }\n                return;\n            }\n            if (!_compare(_values[descendant],\
    \ _values[index])) return;\n            std::swap(_values[descendant], _values[index]);\n\
    \            const std::size_t descendant_parent = parent(descendant);\n     \
    \       if (_compare(_values[descendant_parent], _values[descendant])) {\n   \
    \             std::swap(_values[descendant_parent], _values[descendant]);\n  \
    \          }\n            index = descendant;\n        }\n    }\n\n    void trickle_down_max(std::size_t\
    \ index) {\n        while (true) {\n            const std::size_t descendant =\
    \ maximum_descendant(index);\n            if (descendant == _values.size()) return;\n\
    \            if (parent(descendant) == index) {\n                if (_compare(_values[index],\
    \ _values[descendant])) {\n                    std::swap(_values[descendant],\
    \ _values[index]);\n                }\n                return;\n            }\n\
    \            if (!_compare(_values[index], _values[descendant])) return;\n   \
    \         std::swap(_values[descendant], _values[index]);\n            const std::size_t\
    \ descendant_parent = parent(descendant);\n            if (_compare(_values[descendant],\
    \ _values[descendant_parent])) {\n                std::swap(_values[descendant_parent],\
    \ _values[descendant]);\n            }\n            index = descendant;\n    \
    \    }\n    }\n\n    void restore_after_push(std::size_t index) {\n        if\
    \ (index == 0) return;\n        const std::size_t ancestor = parent(index);\n\
    \        if (is_min_level(index)) {\n            if (_compare(_values[ancestor],\
    \ _values[index])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_max(ancestor);\n            } else {\n            \
    \    bubble_up_min(index);\n            }\n        } else {\n            if (_compare(_values[index],\
    \ _values[ancestor])) {\n                std::swap(_values[ancestor], _values[index]);\n\
    \                bubble_up_min(ancestor);\n            } else {\n            \
    \    bubble_up_max(index);\n            }\n        }\n    }\n\n    std::size_t\
    \ maximum_index() const {\n        assert(!_values.empty());\n        if (_values.size()\
    \ == 1) return 0;\n        if (_values.size() == 2 || !_compare(_values[1], _values[2]))\
    \ return 1;\n        return 2;\n    }\n\n   public:\n    DoubleEndedPriorityQueue()\
    \ = default;\n\n    explicit DoubleEndedPriorityQueue(Compare compare)\n     \
    \   : _compare(std::move(compare)) {}\n\n    DoubleEndedPriorityQueue(std::initializer_list<T>\
    \ values,\n                             Compare compare = Compare())\n       \
    \ : DoubleEndedPriorityQueue(std::move(compare)) {\n        for (const T& value\
    \ : values) push(value);\n    }\n\n    template <class Iterator>\n    DoubleEndedPriorityQueue(Iterator\
    \ first, Iterator last,\n                             Compare compare = Compare())\n\
    \        : DoubleEndedPriorityQueue(std::move(compare)) {\n        while (first\
    \ != last) {\n            push(*first);\n            ++first;\n        }\n   \
    \ }\n\n    std::size_t size() const {\n        return _values.size();\n    }\n\
    \n    bool empty() const {\n        return _values.empty();\n    }\n\n    const\
    \ T& min() const {\n        assert(!empty());\n        return _values[0];\n  \
    \  }\n\n    const T& max() const {\n        return _values[maximum_index()];\n\
    \    }\n\n    void clear() {\n        _values.clear();\n    }\n\n    template\
    \ <class... Args>\n    void emplace(Args&&... args) {\n        _values.emplace_back(std::forward<Args>(args)...);\n\
    \        restore_after_push(_values.size() - 1);\n    }\n\n    void push(const\
    \ T& value) {\n        emplace(value);\n    }\n\n    void push(T&& value) {\n\
    \        emplace(std::move(value));\n    }\n\n    void pop_min() {\n        assert(!empty());\n\
    \        if (_values.size() == 1) {\n            _values.pop_back();\n       \
    \     return;\n        }\n        _values[0] = std::move(_values.back());\n  \
    \      _values.pop_back();\n        trickle_down_min(0);\n    }\n\n    void pop_max()\
    \ {\n        assert(!empty());\n        const std::size_t index = maximum_index();\n\
    \        if (index == _values.size() - 1) {\n            _values.pop_back();\n\
    \            return;\n        }\n        _values[index] = std::move(_values.back());\n\
    \        _values.pop_back();\n        trickle_down_max(index);\n    }\n\n    const\
    \ Compare& comparator() const {\n        return _compare;\n    }\n};\n\ntemplate\
    \ <class T, class Compare = std::less<T>>\nusing MinMaxHeap = DoubleEndedPriorityQueue<T,\
    \ Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"verify/ds/heap/double_ended_priority_queue.test.cpp\"\
    \n\nnamespace {\n\nvoid test_fixed() {\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue = {3, 1, 7, 7, -2};\n    assert(queue.size() == 5);\n    assert(queue.min()\
    \ == -2);\n    assert(queue.max() == 7);\n\n    queue.pop_min();\n    assert(queue.min()\
    \ == 1);\n    queue.pop_max();\n    assert(queue.max() == 7);\n    queue.pop_max();\n\
    \    assert(queue.max() == 3);\n    queue.emplace(10);\n    assert(queue.max()\
    \ == 10);\n\n    m1une::ds::MinMaxHeap<int, std::greater<int>> reversed;\n   \
    \ reversed.push(2);\n    reversed.push(8);\n    reversed.push(5);\n    assert(reversed.min()\
    \ == 8);\n    assert(reversed.max() == 2);\n    reversed.clear();\n    assert(reversed.empty());\n\
    }\n\nvoid test_randomized() {\n    uint64_t state = 0x92d68ca2ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    m1une::ds::DoubleEndedPriorityQueue<int> queue;\n\
    \    std::multiset<int> expected;\n    for (int operation = 0; operation < 300000;\
    \ operation++) {\n        const int type = expected.size() < 1000 ? 0 : int(random()\
    \ % 3);\n        if (type == 0) {\n            const int value = int(random()\
    \ % 2001) - 1000;\n            queue.push(value);\n            expected.insert(value);\n\
    \        } else if (type == 1) {\n            assert(queue.min() == *expected.begin());\n\
    \            queue.pop_min();\n            expected.erase(expected.begin());\n\
    \        } else {\n            auto iterator = std::prev(expected.end());\n  \
    \          assert(queue.max() == *iterator);\n            queue.pop_max();\n \
    \           expected.erase(iterator);\n        }\n\n        assert(queue.size()\
    \ == expected.size());\n        assert(queue.empty() == expected.empty());\n \
    \       if (!expected.empty()) {\n            assert(queue.min() == *expected.begin());\n\
    \            assert(queue.max() == *std::prev(expected.end()));\n        }\n \
    \   }\n\n    bool remove_minimum = false;\n    while (!expected.empty()) {\n \
    \       remove_minimum = !remove_minimum;\n        if (remove_minimum) {\n   \
    \         assert(queue.min() == *expected.begin());\n            queue.pop_min();\n\
    \            expected.erase(expected.begin());\n        } else {\n           \
    \ auto iterator = std::prev(expected.end());\n            assert(queue.max() ==\
    \ *iterator);\n            queue.pop_max();\n            expected.erase(iterator);\n\
    \        }\n    }\n    assert(queue.empty());\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n\n    int initial_size,\
    \ query_count;\n    fast_input >> initial_size >> query_count;\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue;\n    for (int i = 0; i < initial_size; i++) {\n        int value;\n \
    \       fast_input >> value;\n        queue.push(value);\n    }\n    while (query_count--)\
    \ {\n        int type;\n        fast_input >> type;\n        if (type == 0) {\n\
    \            int value;\n            fast_input >> value;\n            queue.push(value);\n\
    \        } else if (type == 1) {\n            fast_output << queue.min() << '\\\
    n';\n            queue.pop_min();\n        } else {\n            fast_output <<\
    \ queue.max() << '\\n';\n            queue.pop_max();\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <functional>\n#include \"\
    ../../../utilities/fast_io.hpp\"\n#include <iterator>\n#include <set>\n#include\
    \ <vector>\n\n#include \"../../../ds/heap/double_ended_priority_queue.hpp\"\n\n\
    namespace {\n\nvoid test_fixed() {\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue = {3, 1, 7, 7, -2};\n    assert(queue.size() == 5);\n    assert(queue.min()\
    \ == -2);\n    assert(queue.max() == 7);\n\n    queue.pop_min();\n    assert(queue.min()\
    \ == 1);\n    queue.pop_max();\n    assert(queue.max() == 7);\n    queue.pop_max();\n\
    \    assert(queue.max() == 3);\n    queue.emplace(10);\n    assert(queue.max()\
    \ == 10);\n\n    m1une::ds::MinMaxHeap<int, std::greater<int>> reversed;\n   \
    \ reversed.push(2);\n    reversed.push(8);\n    reversed.push(5);\n    assert(reversed.min()\
    \ == 8);\n    assert(reversed.max() == 2);\n    reversed.clear();\n    assert(reversed.empty());\n\
    }\n\nvoid test_randomized() {\n    uint64_t state = 0x92d68ca2ULL;\n    auto random\
    \ = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n    \
    \    return state;\n    };\n\n    m1une::ds::DoubleEndedPriorityQueue<int> queue;\n\
    \    std::multiset<int> expected;\n    for (int operation = 0; operation < 300000;\
    \ operation++) {\n        const int type = expected.size() < 1000 ? 0 : int(random()\
    \ % 3);\n        if (type == 0) {\n            const int value = int(random()\
    \ % 2001) - 1000;\n            queue.push(value);\n            expected.insert(value);\n\
    \        } else if (type == 1) {\n            assert(queue.min() == *expected.begin());\n\
    \            queue.pop_min();\n            expected.erase(expected.begin());\n\
    \        } else {\n            auto iterator = std::prev(expected.end());\n  \
    \          assert(queue.max() == *iterator);\n            queue.pop_max();\n \
    \           expected.erase(iterator);\n        }\n\n        assert(queue.size()\
    \ == expected.size());\n        assert(queue.empty() == expected.empty());\n \
    \       if (!expected.empty()) {\n            assert(queue.min() == *expected.begin());\n\
    \            assert(queue.max() == *std::prev(expected.end()));\n        }\n \
    \   }\n\n    bool remove_minimum = false;\n    while (!expected.empty()) {\n \
    \       remove_minimum = !remove_minimum;\n        if (remove_minimum) {\n   \
    \         assert(queue.min() == *expected.begin());\n            queue.pop_min();\n\
    \            expected.erase(expected.begin());\n        } else {\n           \
    \ auto iterator = std::prev(expected.end());\n            assert(queue.max() ==\
    \ *iterator);\n            queue.pop_max();\n            expected.erase(iterator);\n\
    \        }\n    }\n    assert(queue.empty());\n}\n\n}  // namespace\n\nint main()\
    \ {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n\n    int initial_size,\
    \ query_count;\n    fast_input >> initial_size >> query_count;\n    m1une::ds::DoubleEndedPriorityQueue<int>\
    \ queue;\n    for (int i = 0; i < initial_size; i++) {\n        int value;\n \
    \       fast_input >> value;\n        queue.push(value);\n    }\n    while (query_count--)\
    \ {\n        int type;\n        fast_input >> type;\n        if (type == 0) {\n\
    \            int value;\n            fast_input >> value;\n            queue.push(value);\n\
    \        } else if (type == 1) {\n            fast_output << queue.min() << '\\\
    n';\n            queue.pop_min();\n        } else {\n            fast_output <<\
    \ queue.max() << '\\n';\n            queue.pop_max();\n        }\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - ds/heap/double_ended_priority_queue.hpp
  isVerificationFile: true
  path: verify/ds/heap/double_ended_priority_queue.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/heap/double_ended_priority_queue.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/heap/double_ended_priority_queue.test.cpp
- /verify/verify/ds/heap/double_ended_priority_queue.test.cpp.html
title: verify/ds/heap/double_ended_priority_queue.test.cpp
---
