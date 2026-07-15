---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_tree/lazy_link_cut_tree.hpp
    title: Lazy Link-Cut Tree
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
  bundledCode: "#line 1 \"verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#line\
    \ 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp\"\
    \n#include <random>\n#line 7 \"verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\n\
    namespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n\n    // Value Monoid (Sum)\n    static constexpr value_type id() {\n\
    \        return {T(0), 0};\n    }\n    static constexpr value_type op(const value_type&\
    \ a, const value_type& b) {\n        return {a.sum + b.sum, a.size + b.size};\n\
    \    }\n    static constexpr value_type inv(const value_type& x) {\n        return\
    \ {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n    static constexpr\
    \ operator_type op_id() {\n        return 0;\n    }\n    static constexpr operator_type\
    \ op_comp(const operator_type& f, const operator_type& g) {\n        return f\
    \ + g;\n    }\n\n    // Mapping (sum + f * size)\n    static constexpr value_type\
    \ mapping(const operator_type& f, const value_type& x) {\n        return {x.sum\
    \ + f * x.size, x.size};\n    }\n\n    // Helper for initializing a leaf node\n\
    \    static constexpr value_type make(const T& val) {\n        return {val, 1};\n\
    \    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1\
    \ \"ds/dynamic_tree/lazy_link_cut_tree.hpp\"\n\n\n\n#line 5 \"ds/dynamic_tree/lazy_link_cut_tree.hpp\"\
    \n#include <concepts>\n#line 9 \"ds/dynamic_tree/lazy_link_cut_tree.hpp\"\n\n\
    #line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 11 \"ds/dynamic_tree/lazy_link_cut_tree.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <m1une::acted_monoid::IsCommutativeActedGroup ActedGroup>\n\
    struct LazyLinkCutTree {\n    using T = typename ActedGroup::value_type;\n   \
    \ using F = typename ActedGroup::operator_type;\n\n   private:\n    struct Node\
    \ {\n        int left = -1;\n        int right = -1;\n        int parent = -1;\n\
    \        bool rev = false;\n        int size = 1;\n        int virtual_size =\
    \ 0;\n        int rake_size = 0;\n        int all_size = 1;\n        T value =\
    \ ActedGroup::id();\n        T prod = ActedGroup::id();\n        T rev_prod =\
    \ ActedGroup::id();\n        T virtual_prod = ActedGroup::id();\n        T rake_prod\
    \ = ActedGroup::id();\n        T all_prod = ActedGroup::id();\n        F lazy\
    \ = ActedGroup::op_id();\n    };\n\n    struct EdgeInfo {\n        int u = -1;\n\
    \        int v = -1;\n        int node = -1;\n        bool alive = false;\n  \
    \  };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo> _edges;\n  \
    \  std::vector<int> _path_buffer;\n\n    static T make_node_value(const T& value,\
    \ int) {\n        return value;\n    }\n\n    static T make_node_value(T&& value,\
    \ int) {\n        return std::move(value);\n    }\n\n    template <class U>\n\
    \    requires (!std::same_as<U, T>) && (\n        requires(U x) { ActedGroup::make(x);\
    \ } ||\n        requires(U x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { ActedGroup::make(x); }) {\n            return\
    \ ActedGroup::make(value);\n        } else if constexpr (requires(U x, int i)\
    \ { ActedGroup::make(x, i); }) {\n            return ActedGroup::make(value, index);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    int child_size(int node) const {\n        return node == -1 ? 0 : _nodes[node].size;\n\
    \    }\n\n    int child_all_size(int node) const {\n        return node == -1\
    \ ? 0 : _nodes[node].all_size;\n    }\n\n    int child_rake_size(int node) const\
    \ {\n        return node == -1 ? 0 : _nodes[node].rake_size;\n    }\n\n    T child_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].prod;\n\
    \    }\n\n    T child_rev_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rev_prod;\n    }\n\n    T child_all_prod(int\
    \ node) const {\n        return node == -1 ? ActedGroup::id() : _nodes[node].all_prod;\n\
    \    }\n\n    T child_rake_prod(int node) const {\n        return node == -1 ?\
    \ ActedGroup::id() : _nodes[node].rake_prod;\n    }\n\n    T node_subtree_prod(int\
    \ node) const {\n        const Node& x = _nodes[node];\n        return ActedGroup::op(x.value,\
    \ x.virtual_prod);\n    }\n\n    int node_subtree_size(int node) const {\n   \
    \     return 1 + _nodes[node].virtual_size;\n    }\n\n    bool is_splay_root(int\
    \ node) const {\n        int parent = _nodes[node].parent;\n        return parent\
    \ == -1 || (_nodes[parent].left != node && _nodes[parent].right != node);\n  \
    \  }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n       \
    \ x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.rake_size\
    \ = x.virtual_size + child_rake_size(x.left) + child_rake_size(x.right);\n   \
    \     x.all_size = x.size + x.rake_size;\n        x.prod = ActedGroup::op(ActedGroup::op(child_prod(x.left),\
    \ x.value), child_prod(x.right));\n        x.rev_prod = ActedGroup::op(ActedGroup::op(child_rev_prod(x.right),\
    \ x.value), child_rev_prod(x.left));\n        x.rake_prod = ActedGroup::op(ActedGroup::op(child_rake_prod(x.left),\
    \ x.virtual_prod),\n                                      child_rake_prod(x.right));\n\
    \        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n    }\n\n    void\
    \ add_virtual_child(int node, int child) {\n        if (child == -1) return;\n\
    \        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = ActedGroup::op(x.virtual_prod, ActedGroup::inv(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ apply_operator(int node, const F& f) {\n        if (node == -1) return;\n  \
    \      Node& x = _nodes[node];\n        x.value = ActedGroup::mapping(f, x.value);\n\
    \        x.prod = ActedGroup::mapping(f, x.prod);\n        x.rev_prod = ActedGroup::mapping(f,\
    \ x.rev_prod);\n        x.all_prod = ActedGroup::op(x.prod, x.rake_prod);\n  \
    \      x.lazy = ActedGroup::op_comp(f, x.lazy);\n    }\n\n    void push(int node)\
    \ {\n        if (node == -1) return;\n        Node& x = _nodes[node];\n      \
    \  if (x.rev) {\n            apply_reverse(x.left);\n            apply_reverse(x.right);\n\
    \            x.rev = false;\n        }\n        apply_operator(x.left, x.lazy);\n\
    \        apply_operator(x.right, x.lazy);\n        x.lazy = ActedGroup::op_id();\n\
    \    }\n\n    void push_to(int node) {\n        _path_buffer.clear();\n      \
    \  int cur = node;\n        _path_buffer.push_back(cur);\n        while (!is_splay_root(cur))\
    \ {\n            cur = _nodes[cur].parent;\n            _path_buffer.push_back(cur);\n\
    \        }\n        for (int i = int(_path_buffer.size()) - 1; i >= 0; i--) push(_path_buffer[i]);\n\
    \    }\n\n    void rotate(int node) {\n        int parent = _nodes[node].parent;\n\
    \        int grand = _nodes[parent].parent;\n        bool is_right = _nodes[parent].right\
    \ == node;\n        int middle = is_right ? _nodes[node].left : _nodes[node].right;\n\
    \n        if (!is_splay_root(parent)) {\n            if (_nodes[grand].left ==\
    \ parent) {\n                _nodes[grand].left = node;\n            } else {\n\
    \                _nodes[grand].right = node;\n            }\n        }\n     \
    \   _nodes[node].parent = grand;\n\n        if (is_right) {\n            _nodes[node].left\
    \ = parent;\n            _nodes[parent].right = middle;\n        } else {\n  \
    \          _nodes[node].right = parent;\n            _nodes[parent].left = middle;\n\
    \        }\n        if (middle != -1) _nodes[middle].parent = parent;\n      \
    \  _nodes[parent].parent = node;\n\n        update(parent);\n        update(node);\n\
    \    }\n\n    void splay(int node) {\n        push_to(node);\n        while (!is_splay_root(node))\
    \ {\n            int parent = _nodes[node].parent;\n            int grand = _nodes[parent].parent;\n\
    \            if (!is_splay_root(parent)) {\n                bool zig_zig = (_nodes[parent].left\
    \ == node) == (_nodes[grand].left == parent);\n                rotate(zig_zig\
    \ ? parent : node);\n            }\n            rotate(node);\n        }\n   \
    \ }\n\n    int access(int node) {\n        int last = -1;\n        for (int cur\
    \ = node; cur != -1; cur = _nodes[cur].parent) {\n            splay(cur);\n  \
    \          add_virtual_child(cur, _nodes[cur].right);\n            remove_virtual_child(cur,\
    \ last);\n            _nodes[cur].right = last;\n            if (last != -1) _nodes[last].parent\
    \ = cur;\n            update(cur);\n            last = cur;\n        }\n     \
    \   splay(node);\n        return last;\n    }\n\n    void check_vertex(int v)\
    \ const {\n        assert(0 <= v && v < int(_nodes.size()));\n    }\n\n    void\
    \ check_edge(int edge_id) const {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n\
    \    }\n\n   public:\n    LazyLinkCutTree() = default;\n\n    explicit LazyLinkCutTree(int\
    \ n) {\n        assert(0 <= n);\n        _nodes.reserve(n);\n        for (int\
    \ i = 0; i < n; i++) add_vertex();\n    }\n\n    explicit LazyLinkCutTree(const\
    \ std::vector<T>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n    }\n\n \
    \   explicit LazyLinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   explicit LazyLinkCutTree(const std::vector<U>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = ActedGroup::id()) {\n        Node node;\n\
    \        node.value = value;\n        node.prod = value;\n        node.rev_prod\
    \ = value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
    \ size()));\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        check_edge(edge_id);\n\
    \        return _edges[edge_id].alive;\n    }\n\n    int edge_node(int edge_id)\
    \ const {\n        check_edge(edge_id);\n        return _edges[edge_id].node;\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  check_edge(edge_id);\n        return {_edges[edge_id].u, _edges[edge_id].v};\n\
    \    }\n\n    T get(int v) {\n        check_vertex(v);\n        access(v);\n \
    \       return _nodes[v].value;\n    }\n\n    T operator[](int v) {\n        return\
    \ get(v);\n    }\n\n    void set(int v, const T& value) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = value;\n        update(v);\n  \
    \  }\n\n    void set(int v, T&& value) {\n        check_vertex(v);\n        access(v);\n\
    \        _nodes[v].value = std::move(value);\n        update(v);\n    }\n\n  \
    \  template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>)\
    \ && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set(int v, const U& value) {\n        set(v, make_node_value(value,\
    \ v));\n    }\n\n    // Applies `f` to one vertex.\n    void apply(int v, const\
    \ F& f) {\n        check_vertex(v);\n        access(v);\n        _nodes[v].value\
    \ = ActedGroup::mapping(f, _nodes[v].value);\n        update(v);\n    }\n\n  \
    \  // Applies `f` to the path from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    void apply(int u, int v, const\
    \ F& f) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        apply_operator(v, f);\n\
    \    }\n\n    // Makes `v` the represented root of its component.\n    void evert(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        apply_reverse(v);\n\
    \    }\n\n    // Alias for `evert(v)`; changes the represented root to `v`.\n\
    \    void reroot(int v) {\n        evert(v);\n    }\n\n    // Returns the current\
    \ represented root of `v`'s component.\n    int component_root(int v) {\n    \
    \    check_vertex(v);\n        access(v);\n        int cur = v;\n        push(cur);\n\
    \        while (_nodes[cur].left != -1) {\n            cur = _nodes[cur].left;\n\
    \            push(cur);\n        }\n        splay(cur);\n        return cur;\n\
    \    }\n\n    // Alias for `component_root(v)`.\n    int root(int v) {\n     \
    \   return component_root(v);\n    }\n\n    bool connected(int u, int v) {\n \
    \       check_vertex(u);\n        check_vertex(v);\n        if (u == v) return\
    \ true;\n        return component_root(u) == component_root(v);\n    }\n\n   \
    \ bool same(int u, int v) {\n        return connected(u, v);\n    }\n\n    //\
    \ Links two components. Internally calls `evert(u)`, so the represented root may\
    \ change.\n    bool link(int u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v) return false;\n        evert(u);\n        if (component_root(v)\
    \ == u) return false;\n        access(v);\n        _nodes[u].parent = v;\n   \
    \     add_virtual_child(v, u);\n        update(v);\n        return true;\n   \
    \ }\n\n    // Links `child` under `parent`. This is the same operation as `link(child,\
    \ parent)`;\n    // it internally calls `evert(child)`, so that side's represented\
    \ root may change.\n    bool link_parent(int child, int parent) {\n        return\
    \ link(child, parent);\n    }\n\n    int link_edge(int u, int v, const T& value\
    \ = ActedGroup::id()) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { ActedGroup::make(x); } ||\n        requires(U x, int i)\
    \ { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n \
    \   int link_edge(int u, int v, const U& value) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (u == v || connected(u, v)) return -1;\n\
    \        return link_edge(u, v, make_node_value(value, size()));\n    }\n\n  \
    \  // Cuts edge `(u, v)`. Internally calls `evert(u)`, so the represented root\
    \ may change.\n    bool cut(int u, int v) {\n        check_vertex(u);\n      \
    \  check_vertex(v);\n        if (u == v) return false;\n        evert(u);\n  \
    \      access(v);\n        if (_nodes[v].left != u || _nodes[u].right != -1) return\
    \ false;\n        _nodes[v].left = -1;\n        _nodes[u].parent = -1;\n     \
    \   update(v);\n        return true;\n    }\n\n    // Cuts the parent edge of\
    \ `v` in the current represented-root orientation.\n    // Unlike `cut(u, v)`,\
    \ this does not call `evert`.\n    bool cut_parent(int v) {\n        check_vertex(v);\n\
    \        access(v);\n        int left = _nodes[v].left;\n        if (left == -1)\
    \ return false;\n        _nodes[v].left = -1;\n        _nodes[left].parent = -1;\n\
    \        update(v);\n        return true;\n    }\n\n    bool cut_edge(int edge_id)\
    \ {\n        check_edge(edge_id);\n        EdgeInfo& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        bool ok1 = cut(edge.u, edge.node);\n\
    \        bool ok2 = cut(edge.node, edge.v);\n        if (ok1 && ok2) edge.alive\
    \ = false;\n        return ok1 && ok2;\n    }\n\n    T get_edge(int edge_id) {\n\
    \        return get(edge_node(edge_id));\n    }\n\n    void set_edge(int edge_id,\
    \ const T& value) {\n        set(edge_node(edge_id), value);\n    }\n\n    void\
    \ set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id), std::move(value));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { ActedGroup::make(x); } ||\n        requires(U\
    \ x, int i) { ActedGroup::make(x, i); } ||\n        std::convertible_to<U, T>\n\
    \    )\n    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    void apply_edge(int\
    \ edge_id, const F& f) {\n        apply(edge_node(edge_id), f);\n    }\n\n   \
    \ // Returns the path product from `u` to `v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    T prod(int u, int v) {\n    \
    \    check_vertex(u);\n        check_vertex(v);\n        assert(connected(u, v));\n\
    \        evert(u);\n        access(v);\n        return _nodes[v].prod;\n    }\n\
    \n    // Alias for `prod(u, v)`. Internally calls `evert(u)`,\n    // so the represented\
    \ root may change.\n    T path_prod(int u, int v) {\n        return prod(u, v);\n\
    \    }\n\n    // Returns the number of vertices on path `u`-`v`. Internally calls\
    \ `evert(u)`,\n    // so the represented root may change.\n    int path_size(int\
    \ u, int v) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        return _nodes[v].size;\n\
    \    }\n\n    // Returns the `k`-th vertex on path `u`-`v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    int kth_vertex(int u, int v,\
    \ int k) {\n        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
    \ v));\n        evert(u);\n        access(v);\n        assert(0 <= k && k < _nodes[v].size);\n\
    \n        int cur = v;\n        while (true) {\n            push(cur);\n     \
    \       int left_size = child_size(_nodes[cur].left);\n            if (k < left_size)\
    \ {\n                cur = _nodes[cur].left;\n            } else if (k == left_size)\
    \ {\n                splay(cur);\n                return cur;\n            } else\
    \ {\n                k -= left_size + 1;\n                cur = _nodes[cur].right;\n\
    \            }\n        }\n    }\n\n    int lca(int u, int v) {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        if (!connected(u, v)) return -1;\n        if\
    \ (u == v) return u;\n        access(u);\n        return access(v);\n    }\n\n\
    \    // Returns the aggregate of `v`'s subtree when the represented tree is rooted\
    \ at `root`.\n    // Internally calls `evert(root)`, so the represented root may\
    \ change.\n    T subtree_prod(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(connected(root, v));\n        evert(root);\n\
    \        access(v);\n        return node_subtree_prod(v);\n    }\n\n    // Returns\
    \ the aggregate of `v`'s subtree with respect to the current represented root.\n\
    \    T subtree_prod(int v) {\n        check_vertex(v);\n        access(v);\n \
    \       return node_subtree_prod(v);\n    }\n\n    // Returns the size of `v`'s\
    \ subtree when the represented tree is rooted at `root`.\n    // Internally calls\
    \ `evert(root)`, so the represented root may change.\n    int subtree_size(int\
    \ root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n    \
    \    assert(connected(root, v));\n        evert(root);\n        access(v);\n \
    \       return node_subtree_size(v);\n    }\n\n    // Returns the size of `v`'s\
    \ subtree with respect to the current represented root.\n    int subtree_size(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        return node_subtree_size(v);\n\
    \    }\n\n    // Returns the aggregate of the whole connected component containing\
    \ `v`.\n    T component_prod(int v) {\n        int r = root(v);\n        return\
    \ subtree_prod(r, r);\n    }\n\n    // Returns the number of vertices in the connected\
    \ component containing `v`.\n    int component_size(int v) {\n        int r =\
    \ root(v);\n        return subtree_size(r, r);\n    }\n\n    // Returns the child\
    \ of `root` that lies on path `root`-`v`.\n    int child_toward(int root, int\
    \ v) {\n        check_vertex(root);\n        check_vertex(v);\n        assert(root\
    \ != v);\n        assert(connected(root, v));\n        return kth_vertex(root,\
    \ v, 1);\n    }\n\n    // Returns the aggregate of the entire branch of `root`\
    \ that contains `v`.\n    T branch_prod(int root, int v) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        assert(root != v);\n        int child = child_toward(root,\
    \ v);\n        return subtree_prod(root, child);\n    }\n\n    // Returns the\
    \ size of the entire branch of `root` that contains `v`.\n    int branch_size(int\
    \ root, int v) {\n        check_vertex(root);\n        check_vertex(v);\n    \
    \    assert(root != v);\n        int child = child_toward(root, v);\n        return\
    \ subtree_size(root, child);\n    }\n\n    // Returns the parent of `v` when rooted\
    \ at `root`, or `-1` if `v == root`.\n    int parent(int root, int v) {\n    \
    \    check_vertex(root);\n        check_vertex(v);\n        if (root == v) return\
    \ -1;\n        assert(connected(root, v));\n        int d = path_size(root, v);\n\
    \        assert(2 <= d);\n        return kth_vertex(root, v, d - 2);\n    }\n\n\
    \    // Returns `v`'s rooted subtree aggregate excluding the child-side subtree.\n\
    \    T subtree_prod_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        T whole = subtree_prod(root, v);\n        T sub = subtree_prod(root,\
    \ child);\n        return ActedGroup::op(whole, ActedGroup::inv(sub));\n    }\n\
    \n    // Returns `v`'s rooted subtree size excluding the child-side subtree.\n\
    \    int subtree_size_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        return subtree_size(root, v) - subtree_size(root, child);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 11 \"verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp\"\
    \n\nusing AddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node\
    \ = AddSum::value_type;\n\nvoid test_vertex_path_and_subtree_updates() {\n   \
    \ m1une::ds::LazyLinkCutTree<AddSum> lct(std::vector<long long>{1, 2, 3, 4, 5});\n\
    \n    assert(lct.link(0, 1));\n    assert(lct.link(1, 2));\n    assert(lct.link(1,\
    \ 3));\n    assert(lct.link(3, 4));\n\n    Node subtree = lct.subtree_prod(0,\
    \ 1);\n    assert(subtree.sum == 14);\n    assert(subtree.size == 4);\n    assert(lct.subtree_size(0,\
    \ 1) == 4);\n\n    lct.apply(2, 4, 10);\n    Node path = lct.path_prod(2, 4);\n\
    \    assert(path.sum == 54);\n    assert(path.size == 4);\n    subtree = lct.subtree_prod(0,\
    \ 1);\n    assert(subtree.sum == 54);\n    assert(subtree.size == 4);\n    assert(lct.get(0).sum\
    \ == 1);\n    assert(lct.subtree_prod(1, 3).sum == 29);\n\n    lct.apply(0, 3,\
    \ 5);\n    subtree = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 64);\n\
    \    assert(subtree.size == 4);\n    assert(lct.path_prod(2, 4).sum == 64);\n\n\
    \    subtree = lct.subtree_prod(2, 1);\n    assert(subtree.sum == 57);\n    assert(subtree.size\
    \ == 4);\n}\n\nvoid test_edge_path_and_subtree_updates() {\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(3);\n\n    int e01 = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1,\
    \ 2, 7);\n    assert(e01 == 0);\n    assert(e12 == 1);\n\n    Node full = lct.subtree_prod(0,\
    \ 0);\n    assert(full.sum == 12);\n    assert(full.size == 2);\n    Node child\
    \ = lct.subtree_prod(0, 1);\n    assert(child.sum == 7);\n    assert(child.size\
    \ == 1);\n    assert(lct.subtree_size(0, 1) == 3);\n\n    lct.apply(0, 2, 3);\n\
    \    assert(lct.path_prod(0, 2).sum == 18);\n    assert(lct.subtree_prod(0, 1).sum\
    \ == 10);\n\n    lct.apply(1, 2, 2);\n    assert(lct.get_edge(e01).sum == 8);\n\
    \    assert(lct.get_edge(e12).sum == 12);\n    assert(lct.subtree_prod(0, 0).sum\
    \ == 20);\n\n    assert(lct.cut_edge(e01));\n    assert(!lct.connected(0, 2));\n\
    }\n\nvoid test_rooted_tree_utility_apis() {\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(std::vector<long long>{1, 2, 3, 4, 5});\n\n    assert(lct.link_parent(1,\
    \ 0));\n    assert(lct.link_parent(2, 0));\n    assert(lct.link_parent(3, 2));\n\
    \    assert(lct.link_parent(4, 2));\n\n    assert(lct.root(4) == 0);\n    lct.reroot(0);\n\
    \n    Node component = lct.component_prod(0);\n    assert(component.sum == 15);\n\
    \    assert(component.size == 5);\n    assert(lct.component_size(0) == 5);\n\n\
    \    assert(lct.child_toward(0, 4) == 2);\n    assert(lct.child_toward(2, 4) ==\
    \ 4);\n    assert(lct.child_toward(4, 0) == 2);\n\n    Node branch = lct.branch_prod(0,\
    \ 4);\n    assert(branch.sum == 12);\n    assert(branch.size == 3);\n    assert(lct.branch_size(0,\
    \ 4) == 3);\n\n    assert(lct.parent(0, 4) == 2);\n    assert(lct.parent(0, 2)\
    \ == 0);\n    assert(lct.parent(0, 0) == -1);\n\n    Node subtree = lct.subtree_prod(0,\
    \ 2);\n    assert(subtree.sum == 12);\n    assert(subtree.size == 3);\n    assert(lct.subtree_size(0,\
    \ 2) == 3);\n\n    Node excluding = lct.subtree_prod_excluding_child(0, 2, 4);\n\
    \    assert(excluding.sum == 7);\n    assert(excluding.size == 2);\n    assert(lct.subtree_size_excluding_child(0,\
    \ 2, 4) == 2);\n\n    lct.reroot(0);\n    assert(lct.cut_parent(4));\n\n    assert(!lct.connected(4,\
    \ 0));\n    component = lct.component_prod(0);\n    assert(component.sum == 10);\n\
    \    assert(component.size == 4);\n    assert(lct.component_size(0) == 4);\n \
    \   component = lct.component_prod(4);\n    assert(component.sum == 5);\n    assert(component.size\
    \ == 1);\n    assert(lct.component_size(4) == 1);\n\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct2(std::vector<long long>{1, 2, 3, 4, 5});\n    assert(lct2.link_parent(1,\
    \ 0));\n    assert(lct2.link_parent(2, 0));\n    assert(lct2.link_parent(3, 2));\n\
    \    assert(lct2.link_parent(4, 2));\n    lct2.apply(3, 4, 10);\n    lct2.reroot(0);\n\
    \n    assert(lct2.cut_parent(2));\n    assert(!lct2.connected(2, 0));\n    component\
    \ = lct2.component_prod(0);\n    assert(component.sum == 3);\n    assert(component.size\
    \ == 2);\n    assert(lct2.component_size(0) == 2);\n    component = lct2.component_prod(2);\n\
    \    assert(component.sum == 42);\n    assert(component.size == 3);\n    assert(lct2.component_size(2)\
    \ == 3);\n}\n\nbool naive_connected(const std::vector<std::vector<int>>& adj,\
    \ int s, int t) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[s] = s;\n    stack.push_back(s);\n    for (int it = 0; it\
    \ < int(stack.size()); it++) {\n        int v = stack[it];\n        if (v == t)\
    \ return true;\n        for (int to : adj[v]) {\n            if (parent[to] !=\
    \ -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    return false;\n}\n\nstd::vector<int> naive_path_vertices(const\
    \ std::vector<std::vector<int>>& adj, int s, int t) {\n    std::vector<int> parent(adj.size(),\
    \ -1);\n    std::vector<int> stack;\n    parent[s] = s;\n    stack.push_back(s);\n\
    \    for (int it = 0; it < int(stack.size()); it++) {\n        int v = stack[it];\n\
    \        if (v == t) break;\n        for (int to : adj[v]) {\n            if (parent[to]\
    \ != -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    assert(parent[t] != -1);\n    std::vector<int> path;\n\
    \    for (int v = t; v != s; v = parent[v]) path.push_back(v);\n    path.push_back(s);\n\
    \    return path;\n}\n\nlong long naive_path_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int s, int t) {\n    long long res\
    \ = 0;\n    for (int v : naive_path_vertices(adj, s, t)) res += value[v];\n  \
    \  return res;\n}\n\nlong long naive_subtree_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int root,\n                      \
    \      int v) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[root] = root;\n    stack.push_back(root);\n    for (int it\
    \ = 0; it < int(stack.size()); it++) {\n        int x = stack[it];\n        for\
    \ (int to : adj[x]) {\n            if (parent[to] != -1) continue;\n         \
    \   parent[to] = x;\n            stack.push_back(to);\n        }\n    }\n    assert(parent[v]\
    \ != -1);\n\n    long long res = 0;\n    stack.clear();\n    stack.push_back(v);\n\
    \    while (!stack.empty()) {\n        int x = stack.back();\n        stack.pop_back();\n\
    \        res += value[x];\n        for (int to : adj[x]) {\n            if (to\
    \ == parent[x]) continue;\n            stack.push_back(to);\n        }\n    }\n\
    \    return res;\n}\n\nvoid test_random_vertex_path_updates() {\n    constexpr\
    \ int n = 8;\n    std::vector<long long> initial;\n    std::vector<long long>\
    \ value;\n    for (int i = 0; i < n; i++) {\n        initial.push_back(i + 1);\n\
    \        value.push_back(i + 1);\n    }\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(initial);\n    std::vector<std::vector<int>> adj(n);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    std::mt19937 rng(2);\n\n    for (int step = 0; step < 700;\
    \ step++) {\n        int op = int(rng() % 6);\n        int u = int(rng() % n);\n\
    \        int v = int(rng() % n);\n        if (op == 0) {\n            if (u !=\
    \ v && !naive_connected(adj, u, v)) {\n                assert(lct.link(u, v));\n\
    \                adj[u].push_back(v);\n                adj[v].push_back(u);\n\
    \                edges.emplace_back(u, v);\n            }\n        } else if (op\
    \ == 1) {\n            if (!edges.empty()) {\n                int id = int(rng()\
    \ % edges.size());\n                auto [a, b] = edges[id];\n               \
    \ assert(lct.cut(a, b));\n                for (int i = 0; i < int(adj[a].size());\
    \ i++) {\n                    if (adj[a][i] == b) {\n                        adj[a][i]\
    \ = adj[a].back();\n                        adj[a].pop_back();\n             \
    \           break;\n                    }\n                }\n               \
    \ for (int i = 0; i < int(adj[b].size()); i++) {\n                    if (adj[b][i]\
    \ == a) {\n                        adj[b][i] = adj[b].back();\n              \
    \          adj[b].pop_back();\n                        break;\n              \
    \      }\n                }\n                edges[id] = edges.back();\n     \
    \           edges.pop_back();\n            }\n        } else if (op == 2) {\n\
    \            long long x = int(rng() % 200) - 100;\n            value[u] = x;\n\
    \            lct.set(u, x);\n        } else if (u != v && naive_connected(adj,\
    \ u, v)) {\n            if (op == 3) {\n                long long add = int(rng()\
    \ % 21) - 10;\n                lct.apply(u, v, add);\n                for (int\
    \ x : naive_path_vertices(adj, u, v)) value[x] += add;\n            } else if\
    \ (op == 4) {\n                assert(lct.path_prod(u, v).sum == naive_path_sum(adj,\
    \ value, u, v));\n            } else {\n                assert(lct.subtree_prod(u,\
    \ v).sum == naive_subtree_sum(adj, value, u, v));\n                assert(lct.subtree_prod(v,\
    \ u).sum == naive_subtree_sum(adj, value, v, u));\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_vertex_path_and_subtree_updates();\n    test_edge_path_and_subtree_updates();\n\
    \    test_rooted_tree_utility_apis();\n    test_random_vertex_path_updates();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include \"../../../utilities/fast_io.hpp\"\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../acted_monoid/range_add_range_sum.hpp\"\
    \n#include \"../../../ds/dynamic_tree/lazy_link_cut_tree.hpp\"\n\nusing AddSum\
    \ = m1une::acted_monoid::RangeAddRangeSum<long long>;\nusing Node = AddSum::value_type;\n\
    \nvoid test_vertex_path_and_subtree_updates() {\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(std::vector<long long>{1, 2, 3, 4, 5});\n\n    assert(lct.link(0, 1));\n\
    \    assert(lct.link(1, 2));\n    assert(lct.link(1, 3));\n    assert(lct.link(3,\
    \ 4));\n\n    Node subtree = lct.subtree_prod(0, 1);\n    assert(subtree.sum ==\
    \ 14);\n    assert(subtree.size == 4);\n    assert(lct.subtree_size(0, 1) == 4);\n\
    \n    lct.apply(2, 4, 10);\n    Node path = lct.path_prod(2, 4);\n    assert(path.sum\
    \ == 54);\n    assert(path.size == 4);\n    subtree = lct.subtree_prod(0, 1);\n\
    \    assert(subtree.sum == 54);\n    assert(subtree.size == 4);\n    assert(lct.get(0).sum\
    \ == 1);\n    assert(lct.subtree_prod(1, 3).sum == 29);\n\n    lct.apply(0, 3,\
    \ 5);\n    subtree = lct.subtree_prod(0, 1);\n    assert(subtree.sum == 64);\n\
    \    assert(subtree.size == 4);\n    assert(lct.path_prod(2, 4).sum == 64);\n\n\
    \    subtree = lct.subtree_prod(2, 1);\n    assert(subtree.sum == 57);\n    assert(subtree.size\
    \ == 4);\n}\n\nvoid test_edge_path_and_subtree_updates() {\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(3);\n\n    int e01 = lct.link_edge(0, 1, 5);\n    int e12 = lct.link_edge(1,\
    \ 2, 7);\n    assert(e01 == 0);\n    assert(e12 == 1);\n\n    Node full = lct.subtree_prod(0,\
    \ 0);\n    assert(full.sum == 12);\n    assert(full.size == 2);\n    Node child\
    \ = lct.subtree_prod(0, 1);\n    assert(child.sum == 7);\n    assert(child.size\
    \ == 1);\n    assert(lct.subtree_size(0, 1) == 3);\n\n    lct.apply(0, 2, 3);\n\
    \    assert(lct.path_prod(0, 2).sum == 18);\n    assert(lct.subtree_prod(0, 1).sum\
    \ == 10);\n\n    lct.apply(1, 2, 2);\n    assert(lct.get_edge(e01).sum == 8);\n\
    \    assert(lct.get_edge(e12).sum == 12);\n    assert(lct.subtree_prod(0, 0).sum\
    \ == 20);\n\n    assert(lct.cut_edge(e01));\n    assert(!lct.connected(0, 2));\n\
    }\n\nvoid test_rooted_tree_utility_apis() {\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(std::vector<long long>{1, 2, 3, 4, 5});\n\n    assert(lct.link_parent(1,\
    \ 0));\n    assert(lct.link_parent(2, 0));\n    assert(lct.link_parent(3, 2));\n\
    \    assert(lct.link_parent(4, 2));\n\n    assert(lct.root(4) == 0);\n    lct.reroot(0);\n\
    \n    Node component = lct.component_prod(0);\n    assert(component.sum == 15);\n\
    \    assert(component.size == 5);\n    assert(lct.component_size(0) == 5);\n\n\
    \    assert(lct.child_toward(0, 4) == 2);\n    assert(lct.child_toward(2, 4) ==\
    \ 4);\n    assert(lct.child_toward(4, 0) == 2);\n\n    Node branch = lct.branch_prod(0,\
    \ 4);\n    assert(branch.sum == 12);\n    assert(branch.size == 3);\n    assert(lct.branch_size(0,\
    \ 4) == 3);\n\n    assert(lct.parent(0, 4) == 2);\n    assert(lct.parent(0, 2)\
    \ == 0);\n    assert(lct.parent(0, 0) == -1);\n\n    Node subtree = lct.subtree_prod(0,\
    \ 2);\n    assert(subtree.sum == 12);\n    assert(subtree.size == 3);\n    assert(lct.subtree_size(0,\
    \ 2) == 3);\n\n    Node excluding = lct.subtree_prod_excluding_child(0, 2, 4);\n\
    \    assert(excluding.sum == 7);\n    assert(excluding.size == 2);\n    assert(lct.subtree_size_excluding_child(0,\
    \ 2, 4) == 2);\n\n    lct.reroot(0);\n    assert(lct.cut_parent(4));\n\n    assert(!lct.connected(4,\
    \ 0));\n    component = lct.component_prod(0);\n    assert(component.sum == 10);\n\
    \    assert(component.size == 4);\n    assert(lct.component_size(0) == 4);\n \
    \   component = lct.component_prod(4);\n    assert(component.sum == 5);\n    assert(component.size\
    \ == 1);\n    assert(lct.component_size(4) == 1);\n\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct2(std::vector<long long>{1, 2, 3, 4, 5});\n    assert(lct2.link_parent(1,\
    \ 0));\n    assert(lct2.link_parent(2, 0));\n    assert(lct2.link_parent(3, 2));\n\
    \    assert(lct2.link_parent(4, 2));\n    lct2.apply(3, 4, 10);\n    lct2.reroot(0);\n\
    \n    assert(lct2.cut_parent(2));\n    assert(!lct2.connected(2, 0));\n    component\
    \ = lct2.component_prod(0);\n    assert(component.sum == 3);\n    assert(component.size\
    \ == 2);\n    assert(lct2.component_size(0) == 2);\n    component = lct2.component_prod(2);\n\
    \    assert(component.sum == 42);\n    assert(component.size == 3);\n    assert(lct2.component_size(2)\
    \ == 3);\n}\n\nbool naive_connected(const std::vector<std::vector<int>>& adj,\
    \ int s, int t) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[s] = s;\n    stack.push_back(s);\n    for (int it = 0; it\
    \ < int(stack.size()); it++) {\n        int v = stack[it];\n        if (v == t)\
    \ return true;\n        for (int to : adj[v]) {\n            if (parent[to] !=\
    \ -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    return false;\n}\n\nstd::vector<int> naive_path_vertices(const\
    \ std::vector<std::vector<int>>& adj, int s, int t) {\n    std::vector<int> parent(adj.size(),\
    \ -1);\n    std::vector<int> stack;\n    parent[s] = s;\n    stack.push_back(s);\n\
    \    for (int it = 0; it < int(stack.size()); it++) {\n        int v = stack[it];\n\
    \        if (v == t) break;\n        for (int to : adj[v]) {\n            if (parent[to]\
    \ != -1) continue;\n            parent[to] = v;\n            stack.push_back(to);\n\
    \        }\n    }\n    assert(parent[t] != -1);\n    std::vector<int> path;\n\
    \    for (int v = t; v != s; v = parent[v]) path.push_back(v);\n    path.push_back(s);\n\
    \    return path;\n}\n\nlong long naive_path_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int s, int t) {\n    long long res\
    \ = 0;\n    for (int v : naive_path_vertices(adj, s, t)) res += value[v];\n  \
    \  return res;\n}\n\nlong long naive_subtree_sum(const std::vector<std::vector<int>>&\
    \ adj, const std::vector<long long>& value, int root,\n                      \
    \      int v) {\n    std::vector<int> parent(adj.size(), -1);\n    std::vector<int>\
    \ stack;\n    parent[root] = root;\n    stack.push_back(root);\n    for (int it\
    \ = 0; it < int(stack.size()); it++) {\n        int x = stack[it];\n        for\
    \ (int to : adj[x]) {\n            if (parent[to] != -1) continue;\n         \
    \   parent[to] = x;\n            stack.push_back(to);\n        }\n    }\n    assert(parent[v]\
    \ != -1);\n\n    long long res = 0;\n    stack.clear();\n    stack.push_back(v);\n\
    \    while (!stack.empty()) {\n        int x = stack.back();\n        stack.pop_back();\n\
    \        res += value[x];\n        for (int to : adj[x]) {\n            if (to\
    \ == parent[x]) continue;\n            stack.push_back(to);\n        }\n    }\n\
    \    return res;\n}\n\nvoid test_random_vertex_path_updates() {\n    constexpr\
    \ int n = 8;\n    std::vector<long long> initial;\n    std::vector<long long>\
    \ value;\n    for (int i = 0; i < n; i++) {\n        initial.push_back(i + 1);\n\
    \        value.push_back(i + 1);\n    }\n    m1une::ds::LazyLinkCutTree<AddSum>\
    \ lct(initial);\n    std::vector<std::vector<int>> adj(n);\n    std::vector<std::pair<int,\
    \ int>> edges;\n    std::mt19937 rng(2);\n\n    for (int step = 0; step < 700;\
    \ step++) {\n        int op = int(rng() % 6);\n        int u = int(rng() % n);\n\
    \        int v = int(rng() % n);\n        if (op == 0) {\n            if (u !=\
    \ v && !naive_connected(adj, u, v)) {\n                assert(lct.link(u, v));\n\
    \                adj[u].push_back(v);\n                adj[v].push_back(u);\n\
    \                edges.emplace_back(u, v);\n            }\n        } else if (op\
    \ == 1) {\n            if (!edges.empty()) {\n                int id = int(rng()\
    \ % edges.size());\n                auto [a, b] = edges[id];\n               \
    \ assert(lct.cut(a, b));\n                for (int i = 0; i < int(adj[a].size());\
    \ i++) {\n                    if (adj[a][i] == b) {\n                        adj[a][i]\
    \ = adj[a].back();\n                        adj[a].pop_back();\n             \
    \           break;\n                    }\n                }\n               \
    \ for (int i = 0; i < int(adj[b].size()); i++) {\n                    if (adj[b][i]\
    \ == a) {\n                        adj[b][i] = adj[b].back();\n              \
    \          adj[b].pop_back();\n                        break;\n              \
    \      }\n                }\n                edges[id] = edges.back();\n     \
    \           edges.pop_back();\n            }\n        } else if (op == 2) {\n\
    \            long long x = int(rng() % 200) - 100;\n            value[u] = x;\n\
    \            lct.set(u, x);\n        } else if (u != v && naive_connected(adj,\
    \ u, v)) {\n            if (op == 3) {\n                long long add = int(rng()\
    \ % 21) - 10;\n                lct.apply(u, v, add);\n                for (int\
    \ x : naive_path_vertices(adj, u, v)) value[x] += add;\n            } else if\
    \ (op == 4) {\n                assert(lct.path_prod(u, v).sum == naive_path_sum(adj,\
    \ value, u, v));\n            } else {\n                assert(lct.subtree_prod(u,\
    \ v).sum == naive_subtree_sum(adj, value, u, v));\n                assert(lct.subtree_prod(v,\
    \ u).sum == naive_subtree_sum(adj, value, v, u));\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_vertex_path_and_subtree_updates();\n    test_edge_path_and_subtree_updates();\n\
    \    test_rooted_tree_utility_apis();\n    test_random_vertex_path_updates();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - acted_monoid/range_add_range_sum.hpp
  - ds/dynamic_tree/lazy_link_cut_tree.hpp
  - acted_monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
- /verify/verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp.html
title: verify/ds/dynamic_tree/lazy_link_cut_tree.test.cpp
---
