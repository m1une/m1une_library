---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/lazy_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/segtree/lazy_segtree.test.cpp\"\
    \n\n#line 1 \"ds/segtree/lazy_segtree.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
    #include <concepts>\n#line 8 \"ds/segtree/lazy_segtree.hpp\"\n#include <vector>\n\
    \n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
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
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/lazy_segtree.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\n// A highly generic Lazy Segment Tree utilizing\
    \ C++20 Concepts for type safety.\n// It operates on any Acted Monoid structure\
    \ satisfying the `m1une::acted_monoid::IsActedMonoid` concept.\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n,\
    \ _size, _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    // Recalculates\
    \ the value of the node k from its children.\n    void update(int k) {\n     \
    \   _d[k] = ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n    static T\
    \ mapping_at(const F& f, const T& value, long long ord) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ord);\n        } else {\n    \
    \        return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ord) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ord);\n        } else {\n            return f;\n        }\n    }\n\n    int\
    \ node_length(int k) const {\n        int level = std::bit_width((unsigned int)k)\
    \ - 1;\n        return _size >> level;\n    }\n\n    int node_left(int k) const\
    \ {\n        int level = std::bit_width((unsigned int)k) - 1;\n        int len\
    \ = _size >> level;\n        return (k - (1 << level)) * len;\n    }\n\n    //\
    \ Applies the operator f to the node k and updates its lazy tag if it's an internal\
    \ node.\n    void all_apply(int k, F f) {\n        _d[k] = mapping_at(f, _d[k],\
    \ 0);\n        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f,\
    \ _lz[k]);\n        }\n    }\n\n    // Propagates the lazy tag of the node k down\
    \ to its children.\n    void push(int k) {\n        all_apply(2 * k, _lz[k]);\n\
    \        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k) / 2));\n \
    \       _lz[k] = ActedMonoid::op_id();\n    }\n\n   public:\n    // Constructs\
    \ an empty lazy segment tree.\n    LazySegtree() : LazySegtree(0) {}\n\n    //\
    \ Constructs a lazy segment tree of size `n`, initialized with the identity element.\n\
    \    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n, ActedMonoid::id()))\
    \ {}\n\n    // Constructs a lazy segment tree from an existing vector.\n    explicit\
    \ LazySegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n    \
    \    for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n    explicit LazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);\n     \
    \   for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Constructs\
    \ a lazy segment tree from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. ActedMonoid::make(val)\
    \ if it exists.\n    // 2. ActedMonoid::make(val, index) if the monoid requires\
    \ global indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LazySegtree(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; i++) {\n           \
    \ if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n                _d[_size\
    \ + i] = ActedMonoid::make(v[i]);\n            } else if constexpr (requires(U\
    \ x, int idx) { ActedMonoid::make(x, idx); }) {\n                _d[_size + i]\
    \ = ActedMonoid::make(v[i], i);\n            } else {\n                _d[_size\
    \ + i] = static_cast<T>(v[i]);\n            }\n        }\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Returns the number of elements.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Assigns x to the p-th element.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--)\
    \ push(p >> i);\n        _d[p] = x;\n        for (int i = 1; i <= _log; i++) update(p\
    \ >> i);\n    }\n\n    // Returns the value of the p-th element.\n    T get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for (int\
    \ i = _log; i >= 1; i--) push(p >> i);\n        return _d[p];\n    }\n\n    //\
    \ Returns the value of the p-th element.\n    T operator[](int p) {\n        return\
    \ get(p);\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return ActedMonoid::id();\n\n       \
    \ l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        T sml = ActedMonoid::id(),\
    \ smr = ActedMonoid::id();\n        while (l < r) {\n            if (l & 1) sml\
    \ = ActedMonoid::op(sml, _d[l++]);\n            if (r & 1) smr = ActedMonoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ ActedMonoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire\
    \ array.\n    T all_prod() const {\n        return _d[1];\n    }\n\n    // Returns\
    \ all elements as a vector.\n    std::vector<T> to_vector() {\n        for (int\
    \ k = 1; k < _size; k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n\
    \        for (int i = 0; i < _n; i++) res.push_back(_d[_size + i]);\n        return\
    \ res;\n    }\n\n    // Returns the elements in the range [l, r) as a vector.\n\
    \    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        std::vector<T> res;\n        res.reserve(r - l);\n   \
    \     for (int i = l; i < r; i++) res.push_back(get(i));\n        return res;\n\
    \    }\n\n    // Applies the operator f to the p-th element.\n    void apply(int\
    \ p, F f) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p] = mapping_at(f, _d[p],\
    \ 0);\n        for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    //\
    \ Applies the operator f to all elements in the range [l, r).\n    void apply(int\
    \ l, int r, F f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l\
    \ == r) return;\n\n        int base_l = l;\n        l += _size;\n        r +=\
    \ _size;\n\n        for (int i = _log; i >= 1; i--) {\n            if (((l >>\
    \ i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        {\n            int l2 = l, r2 = r;\n     \
    \       while (l < r) {\n                if (l & 1) {\n                    all_apply(l,\
    \ shift_operator(f, node_left(l) - base_l));\n                    l++;\n     \
    \           }\n                if (r & 1) {\n                    --r;\n      \
    \              all_apply(r, shift_operator(f, node_left(r) - base_l));\n     \
    \           }\n                l >>= 1;\n                r >>= 1;\n          \
    \  }\n            l = l2;\n            r = r2;\n        }\n\n        for (int\
    \ i = 1; i <= _log; i++) {\n            if (((l >> i) << i) != l) update(l >>\
    \ i);\n            if (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n\
    \    }\n\n    // Finds the largest r such that g(prod(l, r)) is true.\n    template\
    \ <class F_pred>\n    int max_right(int l, F_pred g) {\n        assert(0 <= l\
    \ && l <= _n);\n        assert(g(ActedMonoid::id()));\n        if (l == _n) return\
    \ _n;\n        l += _size;\n        for (int i = _log; i >= 1; i--) push(l >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            while (l %\
    \ 2 == 0) l >>= 1;\n            if (!g(ActedMonoid::op(sm, _d[l]))) {\n      \
    \          while (l < _size) {\n                    push(l);\n               \
    \     l = (2 * l);\n                    if (g(ActedMonoid::op(sm, _d[l]))) {\n\
    \                        sm = ActedMonoid::op(sm, _d[l]);\n                  \
    \      l++;\n                    }\n                }\n                return\
    \ l - _size;\n            }\n            sm = ActedMonoid::op(sm, _d[l]);\n  \
    \          l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Finds the smallest l such that g(prod(l, r)) is true.\n    template <class\
    \ F_pred>\n    int min_left(int r, F_pred g) {\n        assert(0 <= r && r <=\
    \ _n);\n        assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n\
    \        r += _size;\n        for (int i = _log; i >= 1; i--) push((r - 1) >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            r--;\n   \
    \         while (r > 1 && (r % 2)) r >>= 1;\n            if (!g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                while (r < _size) {\n                    push(r);\n\
    \                    r = (2 * r + 1);\n                    if (g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                        sm = ActedMonoid::op(_d[r], sm);\n        \
    \                r--;\n                    }\n                }\n            \
    \    return r + 1 - _size;\n            }\n            sm = ActedMonoid::op(_d[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 6 \"verify/ds/segtree/lazy_segtree.test.cpp\"\
    \n\n#include <bits/stdc++.h>\n\n#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/range_affine_range_sum.hpp\"\n\nnamespace m1une\
    \ {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAffineRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\n// Designed to accept Modint or similar\
    \ types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum {\n    using value_type\
    \ = RangeAffineRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for ax + b\n\n    // Value Monoid\n    static constexpr value_type id()\
    \ {\n        return {T(0), 0};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n    // f(x)\
    \ = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x\
    \ + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n        return\
    \ {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first * g.first, f.first * g.second\
    \ + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum\
    \ x_i + b * size\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return {f.first * x.sum + f.second * T(x.size),\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\n\
    template <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"\
    Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
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
    \ math\n}  // namespace m1une\n\n\n#line 11 \"verify/ds/segtree/lazy_segtree.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nusing AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\
    \nusing namespace std;\nusing ll = long long;\n\nvoid solve(\n    m1une::utilities::FastInput&\
    \ fast_input,\n    m1une::utilities::FastOutput& fast_output\n) {\n    ll N, Q;\n\
    \    fast_input >> N >> Q;\n    vector<ll> a(N);\n    for (int i = 0; i < N; ++i)\
    \ fast_input >> a[i];\n\n    m1une::ds::LazySegtree<AM> seg(a);\n    assert(seg.size()\
    \ == N);\n    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n\
    \    assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n   \
    \     assert(values[i].sum == mint(a[i]));\n        assert(seg[i].sum == mint(a[i]));\n\
    \    }\n    for (int q = 0; q < Q; ++q) {\n        ll t;\n        fast_input >>\
    \ t;\n        if (t == 0) {\n            ll l, r, b, c;\n            fast_input\
    \ >> l >> r >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n\
    \            ll l, r;\n            fast_input >> l >> r;\n            auto prd\
    \ = seg.prod(l, r);\n            fast_output << prd.sum << '\\n';\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    solve(fast_input, fast_output);\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../../utilities/fast_io.hpp\"\n\n#include \"../../../ds/segtree/lazy_segtree.hpp\"\
    \n\n#include <bits/stdc++.h>\n\n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nusing mint = m1une::math::modint998244353;\n\
    \nusing AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\nusing namespace\
    \ std;\nusing ll = long long;\n\nvoid solve(\n    m1une::utilities::FastInput&\
    \ fast_input,\n    m1une::utilities::FastOutput& fast_output\n) {\n    ll N, Q;\n\
    \    fast_input >> N >> Q;\n    vector<ll> a(N);\n    for (int i = 0; i < N; ++i)\
    \ fast_input >> a[i];\n\n    m1une::ds::LazySegtree<AM> seg(a);\n    assert(seg.size()\
    \ == N);\n    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n\
    \    assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n   \
    \     assert(values[i].sum == mint(a[i]));\n        assert(seg[i].sum == mint(a[i]));\n\
    \    }\n    for (int q = 0; q < Q; ++q) {\n        ll t;\n        fast_input >>\
    \ t;\n        if (t == 0) {\n            ll l, r, b, c;\n            fast_input\
    \ >> l >> r >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n\
    \            ll l, r;\n            fast_input >> l >> r;\n            auto prd\
    \ = seg.prod(l, r);\n            fast_output << prd.sum << '\\n';\n        }\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    solve(fast_input, fast_output);\n    return 0;\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - ds/segtree/lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/lazy_segtree.test.cpp
- /verify/verify/ds/segtree/lazy_segtree.test.cpp.html
title: verify/ds/segtree/lazy_segtree.test.cpp
---
