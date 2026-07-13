---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/algo/sequence/number_of_subsequences.test.cpp
    title: verify/algo/sequence/number_of_subsequences.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/fenwick_tree.test.cpp
    title: verify/ds/range_query/fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_inversion_count.test.cpp
    title: verify/ds/range_query/range_inversion_count.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_lis_query.test.cpp
    title: verify/ds/range_query/range_lis_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_count_distinct.test.cpp
    title: verify/ds/range_query/static_range_count_distinct.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/static_range_mode_query.test.cpp
    title: verify/ds/range_query/static_range_mode_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/geometry/rectangle_union_area.test.cpp
    title: verify/geometry/rectangle_union_area.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/tree/vertex_add_subtree_sum.test.cpp
    title: verify/graph/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/convolution_mod.test.cpp
    title: verify/math/fps/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':x:'
    path: verify/math/multivariate_convolution_cyclic.test.cpp
    title: verify/math/multivariate_convolution_cyclic.test.cpp
  - icon: ':x:'
    path: verify/math/multivariate_convolution_truncated.test.cpp
    title: verify/math/multivariate_convolution_truncated.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/utilities/fast_io.test.cpp
    title: verify/utilities/fast_io.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdint>\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <type_traits>\n#include <utility>\n\n\
    namespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ = has_static_mod_raw<T>::value;\n\n}  // namespace internal\n\nstruct FastInput\
    \ {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n    std::FILE*\
    \ _stream;\n    char _buffer[buffer_size];\n    int _position;\n    int _length;\n\
    \n    bool prepare_number() {\n        if (_length - _position >= 32) return true;\n\
    \        const int remaining = _length - _position;\n        if (remaining > 0)\
    \ std::memmove(_buffer, _buffer + _position, remaining);\n        const int added\
    \ = int(std::fread(_buffer + remaining, 1, buffer_size - remaining, _stream));\n\
    \        _position = 0;\n        _length = remaining + added;\n        if (_length\
    \ < buffer_size) _buffer[_length] = '\\0';\n        return _length != 0;\n   \
    \ }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n       \
    \ : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const FastInput&)\
    \ = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\n    int read_char_raw()\
    \ {\n        if (_position == _length) {\n            _length = int(std::fread(_buffer,\
    \ 1, buffer_size, _stream));\n            _position = 0;\n            if (_length\
    \ == 0) return EOF;\n        }\n        return _buffer[_position++];\n    }\n\n\
    \    bool skip_spaces() {\n        int c = read_char_raw();\n        while (c\
    \ != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \        --_position;\n        return true;\n    }\n\n    bool read(char& value)\
    \ {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (std::is_signed_v<T>) {\n            T result = 0;\n  \
    \          while ('0' <= c && c <= '9') {\n                const int first = c\
    \ - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
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
    \ <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n  \
    \          && !std::is_integral_v<T>\n            && !internal::is_range_v<T>,\n\
    \        bool\n    >\n    read(T& value) {\n        long long x;\n        if (!read(x))\
    \ return false;\n        if constexpr (internal::has_static_mod_raw_v<T>) {\n\
    \            if (x >= 0 && uint64_t(x) < uint64_t(T::mod())) {\n             \
    \   value = T::raw(uint32_t(x));\n            } else {\n                value\
    \ = T(x);\n            }\n        } else {\n            value = T(x);\n      \
    \  }\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>,\n\
    \        bool\n    >\n    read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        read(value);\n   \
    \     return *this;\n    }\n};\n\nstruct FastOutput {\n    static constexpr int\
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static const auto digit_quads\
    \ = [] {\n        std::array<char, 40000> result{};\n        for (int i = 0; i\
    \ < 10000; i++) {\n            int value = i;\n            for (int j = 3; j >=\
    \ 0; j--) {\n                result[4 * i + j] = char('0' + value % 10);\n   \
    \             value /= 10;\n            }\n        }\n        return result;\n\
    \    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream), _position(0) {}\n\n    FastOutput(const FastOutput&)\
    \ = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput()\
    \ {\n        flush();\n    }\n\n    void flush() {\n        if (_position == 0)\
    \ return;\n        std::fwrite(_buffer, 1, _position, _stream);\n        _position\
    \ = 0;\n    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        unsigned\
    \ chunks[16];\n        int count = 0;\n        while (magnitude >= 10000) {\n\
    \            const Unsigned quotient = magnitude / 10000;\n            chunks[count++]\
    \ = unsigned(magnitude - quotient * 10000);\n            magnitude = quotient;\n\
    \        }\n        if (_position > buffer_size - 64) flush();\n        const\
    \ unsigned leading = unsigned(magnitude);\n        const char* first = digit_quads.data()\
    \ + 4 * leading;\n        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading\
    \ < 1000 ? 1 : 0;\n        for (; skip < 4; skip++) _buffer[_position++] = first[skip];\n\
    \        while (count--) {\n            const char* digits = digit_quads.data()\
    \ + 4 * chunks[count];\n            std::memcpy(_buffer + _position, digits, 4);\n\
    \            _position += 4;\n        }\n    }\n\n    template <class T>\n   \
    \ std::enable_if_t<\n        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
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
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FAST_IO_HPP\n#define M1UNE_FAST_IO_HPP 1\n\n#include <array>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ = has_static_mod_raw<T>::value;\n\n}  // namespace internal\n\nstruct FastInput\
    \ {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n    std::FILE*\
    \ _stream;\n    char _buffer[buffer_size];\n    int _position;\n    int _length;\n\
    \n    bool prepare_number() {\n        if (_length - _position >= 32) return true;\n\
    \        const int remaining = _length - _position;\n        if (remaining > 0)\
    \ std::memmove(_buffer, _buffer + _position, remaining);\n        const int added\
    \ = int(std::fread(_buffer + remaining, 1, buffer_size - remaining, _stream));\n\
    \        _position = 0;\n        _length = remaining + added;\n        if (_length\
    \ < buffer_size) _buffer[_length] = '\\0';\n        return _length != 0;\n   \
    \ }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n       \
    \ : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const FastInput&)\
    \ = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\n    int read_char_raw()\
    \ {\n        if (_position == _length) {\n            _length = int(std::fread(_buffer,\
    \ 1, buffer_size, _stream));\n            _position = 0;\n            if (_length\
    \ == 0) return EOF;\n        }\n        return _buffer[_position++];\n    }\n\n\
    \    bool skip_spaces() {\n        int c = read_char_raw();\n        while (c\
    \ != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \        --_position;\n        return true;\n    }\n\n    bool read(char& value)\
    \ {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (std::is_signed_v<T>) {\n            T result = 0;\n  \
    \          while ('0' <= c && c <= '9') {\n                const int first = c\
    \ - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
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
    \ <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n  \
    \          && !std::is_integral_v<T>\n            && !internal::is_range_v<T>,\n\
    \        bool\n    >\n    read(T& value) {\n        long long x;\n        if (!read(x))\
    \ return false;\n        if constexpr (internal::has_static_mod_raw_v<T>) {\n\
    \            if (x >= 0 && uint64_t(x) < uint64_t(T::mod())) {\n             \
    \   value = T::raw(uint32_t(x));\n            } else {\n                value\
    \ = T(x);\n            }\n        } else {\n            value = T(x);\n      \
    \  }\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>,\n\
    \        bool\n    >\n    read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        read(value);\n   \
    \     return *this;\n    }\n};\n\nstruct FastOutput {\n    static constexpr int\
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static const auto digit_quads\
    \ = [] {\n        std::array<char, 40000> result{};\n        for (int i = 0; i\
    \ < 10000; i++) {\n            int value = i;\n            for (int j = 3; j >=\
    \ 0; j--) {\n                result[4 * i + j] = char('0' + value % 10);\n   \
    \             value /= 10;\n            }\n        }\n        return result;\n\
    \    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream), _position(0) {}\n\n    FastOutput(const FastOutput&)\
    \ = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput()\
    \ {\n        flush();\n    }\n\n    void flush() {\n        if (_position == 0)\
    \ return;\n        std::fwrite(_buffer, 1, _position, _stream);\n        _position\
    \ = 0;\n    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        unsigned\
    \ chunks[16];\n        int count = 0;\n        while (magnitude >= 10000) {\n\
    \            const Unsigned quotient = magnitude / 10000;\n            chunks[count++]\
    \ = unsigned(magnitude - quotient * 10000);\n            magnitude = quotient;\n\
    \        }\n        if (_position > buffer_size - 64) flush();\n        const\
    \ unsigned leading = unsigned(magnitude);\n        const char* first = digit_quads.data()\
    \ + 4 * leading;\n        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading\
    \ < 1000 ? 1 : 0;\n        for (; skip < 4; skip++) _buffer[_position++] = first[skip];\n\
    \        while (count--) {\n            const char* digits = digit_quads.data()\
    \ + 4 * chunks[count];\n            std::memcpy(_buffer + _position, digits, 4);\n\
    \            _position += 4;\n        }\n    }\n\n    template <class T>\n   \
    \ std::enable_if_t<\n        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
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
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_FAST_IO_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/fast_io.hpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/algo/sequence/number_of_subsequences.test.cpp
  - verify/utilities/fast_io.test.cpp
  - verify/geometry/rectangle_union_area.test.cpp
  - verify/ds/range_query/static_range_mode_query.test.cpp
  - verify/ds/range_query/range_inversion_count.test.cpp
  - verify/ds/range_query/fenwick_tree.test.cpp
  - verify/ds/range_query/range_lis_query.test.cpp
  - verify/ds/range_query/static_range_count_distinct.test.cpp
  - verify/math/multivariate_convolution_cyclic.test.cpp
  - verify/math/multivariate_convolution_truncated.test.cpp
  - verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - verify/math/fps/convolution_mod.test.cpp
  - verify/graph/tree/vertex_add_subtree_sum.test.cpp
documentation_of: utilities/fast_io.hpp
layout: document
title: Fast IO
---

## Overview

`FastInput` and `FastOutput` are buffered replacements for `std::cin` and
`std::cout`. They provide familiar, chainable `operator>>` and `operator<<`
syntax while using `std::FILE*` internally. By default they read from `stdin`
and write to `stdout`.

```cpp
FastInput input;
FastOutput output;

int n;
input >> n;
output << n << '\n';
```

All names are in `m1une::utilities`.

## Supported types

Both operators support integral types, `bool`, `char`, `std::string`, and
ModInt-like types. A ModInt-like type must provide `value.val()` for output and
be constructible from `long long` for input. Output additionally accepts
null-terminated C strings.

Ranges recognized by `std::begin` and `std::end` are also supported, including
ordinary arrays, `std::array`, and nested containers. Strings are treated as
single values rather than ranges of characters.

## Vectors and other ranges

Input never changes a container's size. Allocate every dimension before using
`operator>>`:

```cpp
int n;
input >> n;
std::vector<int> a(n);
input >> a;

int h, w;
input >> h >> w;
std::vector<std::vector<int>> matrix(h, std::vector<int>(w));
input >> matrix;
```

Elements are processed in iteration order. Nested ranges are processed
recursively, so the matrix above is read in row-major order. Empty ranges read
nothing. `std::vector<bool>` is supported.

For output, elements of a one-dimensional range are separated by spaces. When
the elements are themselves ranges, they are separated by newlines:

```cpp
output << a << '\n';
output << matrix << '\n';
```

For `a = {1, 2, 3}` and a two-row matrix, the result is:

```text
1 2 3
1 2 3
4 5 6
```

No trailing separator is written by the range itself. Add `<< '\n'` when a
final newline is wanted. Higher-dimensional ranges use a newline at every
nested-range boundary and a space between scalar values.

## Interface

### `FastInput`

| Method | Description | Complexity |
| --- | --- | --- |
| `FastInput(std::FILE* stream = stdin)` | Creates an input buffer for `stream`. | $O(1)$ |
| `FastInput& operator>>(T& value)` | Reads one value or a pre-sized range and returns `*this`. | Linear in consumed input |
| `bool read(T& value)` | Reads one value and reports whether input was available. | Linear in consumed input |
| `bool read(a, b, ...)` | Reads several values and returns `false` if any read fails. | Linear in consumed input |
| `int read_char_raw()` | Reads the next byte without skipping whitespace, or returns `EOF`. | Amortized $O(1)$ |
| `bool skip_spaces()` | Skips whitespace and reports whether a token remains. | Linear in skipped input |

`operator>>` is intended for valid contest input and does not expose a failure
state. Use `read(...)` when EOF or malformed/missing input must be detected.

### `FastOutput`

| Method | Description | Complexity |
| --- | --- | --- |
| `FastOutput(std::FILE* stream = stdout)` | Creates an output buffer for `stream`. | $O(1)$ |
| `FastOutput& operator<<(const T& value)` | Writes a value or range and returns `*this`. | Linear in produced output |
| `void write(value)` | Writes one value or range without an added separator. | Linear in produced output |
| `void print(a, b, ...)` | Writes several values separated by spaces. | Linear in produced output |
| `void println(a, b, ...)` | Calls `print`, then writes a newline. | Linear in produced output |
| `void println()` | Writes a newline. | Amortized $O(1)$ |
| `void flush()` | Writes all buffered bytes to the underlying stream. | Linear in buffered output |

Pending output is flushed by the destructor. Standard iostream manipulators
such as `std::endl` are not supported; use `output << '\n'` and call `flush()`
explicitly only when the output must become visible immediately.

## Example

```cpp
#include "utilities/fast_io.hpp"

#include <vector>

using m1une::utilities::FastInput;
using m1une::utilities::FastOutput;

int main() {
    FastInput input;
    FastOutput output;

    int n;
    input >> n;

    std::vector<long long> a(n);
    input >> a;

    long long sum = 0;
    for (long long x : a) sum += x;

    output << sum << '\n';
    output << a << '\n';
}
```
