---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/all.hpp
    title: Tree All
  - icon: ':heavy_check_mark:'
    path: graph/tree/cartesian_tree.hpp
    title: Cartesian Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/centroid_decomposition.hpp
    title: Centroid Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/diameter.hpp
    title: Tree Diameter
  - icon: ':heavy_check_mark:'
    path: graph/tree/distance_frequency.hpp
    title: Tree Distance Frequency
  - icon: ':heavy_check_mark:'
    path: graph/tree/dsu_on_tree.hpp
    title: DSU on Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/euler_tour.hpp
    title: Euler Tour
  - icon: ':heavy_check_mark:'
    path: graph/tree/heavy_light_decomposition.hpp
    title: Heavy Light Decomposition
  - icon: ':heavy_check_mark:'
    path: graph/tree/range_contour_query.hpp
    title: Range Contour Query on Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/rerooting_dp.hpp
    title: Rerooting DP
  - icon: ':heavy_check_mark:'
    path: graph/tree/rerooting_static_top_tree.hpp
    title: Rerooting Static Top Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/rooted_tree.hpp
    title: Rooted Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  - icon: ':heavy_check_mark:'
    path: graph/tree/static_top_tree.hpp
    title: Static Top Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree.hpp
    title: Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/tree_hash.hpp
    title: Hash of Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/virtual_tree.hpp
    title: Virtual Tree
  - icon: ':heavy_check_mark:'
    path: graph/tree/zero_one_on_tree.hpp
    title: 01 on Tree
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
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
  bundledCode: "#line 1 \"verify/graph/tree/tree_algorithms.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <array>\n#include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line\
    \ 6 \"utilities/fast_io.hpp\"\n#include <cerrno>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include\
    \ <type_traits>\n#include <utility>\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 7 \"verify/graph/tree/tree_algorithms.test.cpp\"\
    \n#include <numeric>\n#include <random>\n#include <set>\n#include <vector>\n\n\
    #line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/tree/all.hpp\"\n\n\n\n#line 1 \"graph/tree/cartesian_tree.hpp\"\
    \n\n\n\n#line 6 \"graph/tree/cartesian_tree.hpp\"\n#include <functional>\n#include\
    \ <limits>\n#line 10 \"graph/tree/cartesian_tree.hpp\"\n\n#line 12 \"graph/tree/cartesian_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nstruct CartesianTree {\n    int root;\n\
    \    std::vector<int> parent;\n    std::vector<int> left;\n    std::vector<int>\
    \ right;\n\n   private:\n    int _n;\n\n    void check_vertex(int v) const {\n\
    \        assert(0 <= v && v < _n);\n    }\n\n   public:\n    CartesianTree() :\
    \ root(-1), _n(0) {}\n\n    template <class T, class Compare = std::less<T>>\n\
    \    explicit CartesianTree(const std::vector<T>& a, Compare comp = Compare())\
    \ : root(-1), _n(0) {\n        build(a, comp);\n    }\n\n    template <class T,\
    \ class Compare = std::less<T>>\n    void build(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n        assert(a.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));\n\
    \        _n = int(a.size());\n        root = -1;\n        parent.assign(_n, -1);\n\
    \        left.assign(_n, -1);\n        right.assign(_n, -1);\n\n        std::vector<int>\
    \ stack;\n        stack.reserve(_n);\n        for (int i = 0; i < _n; i++) {\n\
    \            int last = -1;\n            while (!stack.empty() && comp(a[i], a[stack.back()]))\
    \ {\n                last = stack.back();\n                stack.pop_back();\n\
    \            }\n            if (last != -1) {\n                left[i] = last;\n\
    \                parent[last] = i;\n            }\n            if (!stack.empty())\
    \ {\n                right[stack.back()] = i;\n                parent[i] = stack.back();\n\
    \            }\n            stack.push_back(i);\n        }\n\n        if (!stack.empty())\
    \ root = stack.front();\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ parent_or_self(int v) const {\n        check_vertex(v);\n        return parent[v]\
    \ == -1 ? v : parent[v];\n    }\n\n    std::vector<int> parent_with_root_self()\
    \ const {\n        std::vector<int> result = parent;\n        if (root != -1)\
    \ result[root] = root;\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> edges() const {\n        std::vector<std::pair<int, int>> result;\n  \
    \      if (_n == 0) return result;\n        result.reserve(_n - 1);\n        for\
    \ (int v = 0; v < _n; v++) {\n            if (parent[v] != -1) result.emplace_back(parent[v],\
    \ v);\n        }\n        return result;\n    }\n\n    m1une::graph::Graph<int>\
    \ to_graph() const {\n        m1une::graph::Graph<int> g(_n);\n        for (int\
    \ v = 0; v < _n; v++) {\n            if (parent[v] != -1) g.add_edge(parent[v],\
    \ v);\n        }\n        return g;\n    }\n};\n\ntemplate <class T, class Compare\
    \ = std::less<T>>\nCartesianTree cartesian_tree(const std::vector<T>& a, Compare\
    \ comp = Compare()) {\n    CartesianTree result;\n    result.build(a, comp);\n\
    \    return result;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line\
    \ 1 \"graph/tree/centroid_decomposition.hpp\"\n\n\n\n#line 6 \"graph/tree/centroid_decomposition.hpp\"\
    \n\n#line 8 \"graph/tree/centroid_decomposition.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T = int>\nstruct CentroidDecomposition {\n    int\
    \ n;\n    std::vector<int> parent;\n    std::vector<int> depth;\n    std::vector<int>\
    \ order;\n    std::vector<int> roots;\n    std::vector<std::vector<int>> children;\n\
    \n   private:\n    std::vector<int> _subtree_size;\n    std::vector<int> _work_parent;\n\
    \    std::vector<char> _removed;\n\n    void build_component(const m1une::graph::Graph<T>&\
    \ g, int start, int p, int d) {\n        std::vector<int> nodes;\n        std::vector<int>\
    \ stack = {start};\n        _work_parent[start] = -2;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      nodes.push_back(v);\n            for (const auto& e : g[v]) {\n       \
    \         if (!e.alive || _removed[e.to]) continue;\n                if (_work_parent[e.to]\
    \ != -1) continue;\n                _work_parent[e.to] = v;\n                stack.push_back(e.to);\n\
    \            }\n        }\n\n        for (int v : nodes) _subtree_size[v] = 1;\n\
    \        for (int i = int(nodes.size()) - 1; i >= 0; i--) {\n            int v\
    \ = nodes[i];\n            if (_work_parent[v] >= 0) _subtree_size[_work_parent[v]]\
    \ += _subtree_size[v];\n        }\n\n        int total = int(nodes.size());\n\
    \        int centroid = start;\n        int best = total + 1;\n        for (int\
    \ v : nodes) {\n            int largest = total - _subtree_size[v];\n        \
    \    for (const auto& e : g[v]) {\n                if (!e.alive || _removed[e.to])\
    \ continue;\n                if (_work_parent[e.to] == v) largest = std::max(largest,\
    \ _subtree_size[e.to]);\n            }\n            if (largest < best) {\n  \
    \              best = largest;\n                centroid = v;\n            }\n\
    \        }\n\n        for (int v : nodes) _work_parent[v] = -1;\n\n        parent[centroid]\
    \ = p;\n        depth[centroid] = d;\n        order.push_back(centroid);\n   \
    \     if (p == -1) {\n            roots.push_back(centroid);\n        } else {\n\
    \            children[p].push_back(centroid);\n        }\n        _removed[centroid]\
    \ = true;\n\n        for (const auto& e : g[centroid]) {\n            if (!e.alive\
    \ || _removed[e.to]) continue;\n            build_component(g, e.to, centroid,\
    \ d + 1);\n        }\n    }\n\n   public:\n    CentroidDecomposition() : n(0)\
    \ {}\n    explicit CentroidDecomposition(const m1une::graph::Graph<T>& g) {\n\
    \        build(g);\n    }\n\n    void build(const m1une::graph::Graph<T>& g) {\n\
    \        n = g.size();\n        parent.assign(n, -1);\n        depth.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        roots.clear();\n\
    \        children.assign(n, {});\n        _subtree_size.assign(n, 0);\n      \
    \  _work_parent.assign(n, -1);\n        _removed.assign(n, false);\n\n       \
    \ for (int v = 0; v < n; v++) {\n            if (depth[v] == -1) build_component(g,\
    \ v, -1, 0);\n        }\n    }\n\n    int size() const {\n        return n;\n\
    \    }\n\n    bool empty() const {\n        return n == 0;\n    }\n\n    int root()\
    \ const {\n        return roots.empty() ? -1 : roots[0];\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/diameter.hpp\"\n\n\n\n\
    #line 6 \"graph/tree/diameter.hpp\"\n\n#line 8 \"graph/tree/diameter.hpp\"\n\n\
    namespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct TreeDiameter\
    \ {\n    T cost;\n    int edge_count;\n    int from;\n    int to;\n    std::vector<int>\
    \ vertices;\n    std::vector<int> edge_ids;\n\n    bool empty() const {\n    \
    \    return vertices.empty();\n    }\n};\n\nnamespace internal {\n\ntemplate <class\
    \ T>\nstruct FarthestResult {\n    int vertex;\n    std::vector<char> seen;\n\
    \    std::vector<T> dist;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n};\n\ntemplate <class T>\nFarthestResult<T> farthest_from(const\
    \ m1une::graph::Graph<T>& g, int start) {\n    int n = g.size();\n    FarthestResult<T>\
    \ result;\n    result.vertex = start;\n    result.seen.assign(n, false);\n   \
    \ result.dist.assign(n, T(0));\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n,\
    \ -1);\n\n    std::vector<int> stack = {start};\n    result.seen[start] = true;\n\
    \    while (!stack.empty()) {\n        int v = stack.back();\n        stack.pop_back();\n\
    \        if (result.dist[result.vertex] < result.dist[v]) result.vertex = v;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (result.seen[e.to]) continue;\n            result.seen[e.to] =\
    \ true;\n            result.dist[e.to] = result.dist[v] + e.cost;\n          \
    \  result.parent[e.to] = v;\n            result.parent_edge[e.to] = e.id;\n  \
    \          stack.push_back(e.to);\n        }\n    }\n    return result;\n}\n\n\
    }  // namespace internal\n\ntemplate <class T>\nTreeDiameter<T> tree_diameter(const\
    \ m1une::graph::Graph<T>& g) {\n    int n = g.size();\n    TreeDiameter<T> best;\n\
    \    best.cost = T(0);\n    best.edge_count = 0;\n    best.from = -1;\n    best.to\
    \ = -1;\n    if (n == 0) return best;\n\n    std::vector<char> done(n, false);\n\
    \    for (int start = 0; start < n; start++) {\n        if (done[start]) continue;\n\
    \        auto first = internal::farthest_from(g, start);\n        for (int v =\
    \ 0; v < n; v++) {\n            if (first.seen[v]) done[v] = true;\n        }\n\
    \        auto second = internal::farthest_from(g, first.vertex);\n        int\
    \ a = first.vertex;\n        int b = second.vertex;\n        T cost = second.dist[b];\n\
    \        if (best.from != -1 && !(best.cost < cost)) continue;\n\n        best.cost\
    \ = cost;\n        best.from = a;\n        best.to = b;\n        best.vertices.clear();\n\
    \        best.edge_ids.clear();\n        for (int v = b; v != -1; v = second.parent[v])\
    \ {\n            best.vertices.push_back(v);\n            if (v != a) best.edge_ids.push_back(second.parent_edge[v]);\n\
    \        }\n        std::reverse(best.vertices.begin(), best.vertices.end());\n\
    \        std::reverse(best.edge_ids.begin(), best.edge_ids.end());\n        best.edge_count\
    \ = int(best.edge_ids.size());\n    }\n\n    return best;\n}\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/distance_frequency.hpp\"\
    \n\n\n\n#line 10 \"graph/tree/distance_frequency.hpp\"\n\n#line 1 \"math/fps/convolution.hpp\"\
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
    #undef M1UNE_FPS_HAS_X86_SIMD\n#endif\n\n\n#line 14 \"graph/tree/distance_frequency.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace distance_frequency_detail\
    \ {\n\ntemplate <class Mint, class T>\nstd::vector<Mint> count_ordered_pairs(\n\
    \    const m1une::graph::Graph<T>& tree,\n    const CentroidDecomposition<T>&\
    \ decomposition\n) {\n    const int size = tree.size();\n    std::vector<Mint>\
    \ count(static_cast<std::size_t>(size));\n    std::vector<char> removed(std::size_t(size),\
    \ false);\n    std::vector<Mint> histogram;\n    std::vector<std::pair<int, int>>\
    \ stack;\n    std::vector<int> parent(std::size_t(size), -1);\n\n    for (int\
    \ centroid : decomposition.order) {\n        std::vector<Mint> total(1, Mint(1));\n\
    \        for (const auto& edge : tree[centroid]) {\n            if (!edge.alive\
    \ || removed[std::size_t(edge.to)]) continue;\n\n            histogram.clear();\n\
    \            stack.clear();\n            stack.emplace_back(edge.to, 1);\n   \
    \         parent[std::size_t(edge.to)] = centroid;\n            while (!stack.empty())\
    \ {\n                const auto [vertex, distance] = stack.back();\n         \
    \       stack.pop_back();\n                if (int(histogram.size()) <= distance)\
    \ {\n                    histogram.resize(std::size_t(distance + 1));\n      \
    \          }\n                histogram[std::size_t(distance)] += Mint(1);\n\n\
    \                for (const auto& next : tree[vertex]) {\n                   \
    \ if (!next.alive || removed[std::size_t(next.to)]) continue;\n              \
    \      if (next.to == parent[std::size_t(vertex)]) continue;\n               \
    \     parent[std::size_t(next.to)] = vertex;\n                    stack.emplace_back(next.to,\
    \ distance + 1);\n                }\n            }\n\n            if (total.size()\
    \ < histogram.size()) {\n                total.resize(histogram.size());\n   \
    \         }\n            for (std::size_t distance = 0; distance < histogram.size();\
    \ distance++) {\n                total[distance] += histogram[distance];\n   \
    \         }\n\n            const std::vector<Mint> within_component =\n      \
    \          m1une::fps::convolution(histogram, histogram);\n            const std::size_t\
    \ limit = std::min(count.size(), within_component.size());\n            for (std::size_t\
    \ distance = 0; distance < limit; distance++) {\n                count[distance]\
    \ -= within_component[distance];\n            }\n        }\n\n        const std::vector<Mint>\
    \ through_centroid =\n            m1une::fps::convolution(total, total);\n   \
    \     const std::size_t limit = std::min(count.size(), through_centroid.size());\n\
    \        for (std::size_t distance = 0; distance < limit; distance++) {\n    \
    \        count[distance] += through_centroid[distance];\n        }\n        removed[std::size_t(centroid)]\
    \ = true;\n    }\n    return count;\n}\n\ninline std::uint64_t combine_residues(std::uint32_t\
    \ first, std::uint32_t second) {\n    using First = m1une::math::ModInt<998244353>;\n\
    \    using Second = m1une::math::ModInt<924844033>;\n    static const std::uint64_t\
    \ inverse = Second(First::mod()).inv().val();\n    const std::uint64_t offset\
    \ =\n        (std::uint64_t(second) + Second::mod() - first % Second::mod()) %\n\
    \        Second::mod();\n    const std::uint64_t multiplier = offset * inverse\
    \ % Second::mod();\n    return std::uint64_t(first) + std::uint64_t(First::mod())\
    \ * multiplier;\n}\n\n}  // namespace distance_frequency_detail\n\ntemplate <class\
    \ T>\nstd::vector<long long> tree_distance_frequency(\n    const m1une::graph::Graph<T>&\
    \ tree\n) {\n    const int size = tree.size();\n    assert(tree.edge_count() ==\
    \ std::max(0, size - 1));\n    if (size == 0) return {};\n\n    const CentroidDecomposition<T>\
    \ decomposition(tree);\n    assert(decomposition.roots.size() == 1);\n\n    using\
    \ First = m1une::math::ModInt<998244353>;\n    using Second = m1une::math::ModInt<924844033>;\n\
    \    assert(\n        std::uint64_t(size) * std::uint64_t(size - 1) <\n      \
    \  std::uint64_t(First::mod()) * Second::mod()\n    );\n    const std::vector<First>\
    \ first =\n        distance_frequency_detail::count_ordered_pairs<First>(\n  \
    \          tree,\n            decomposition\n        );\n    const std::vector<Second>\
    \ second =\n        distance_frequency_detail::count_ordered_pairs<Second>(\n\
    \            tree,\n            decomposition\n        );\n\n    std::vector<long\
    \ long> result(static_cast<std::size_t>(size));\n    result[0] = size;\n    for\
    \ (int distance = 1; distance < size; distance++) {\n        const std::uint64_t\
    \ ordered =\n            distance_frequency_detail::combine_residues(\n      \
    \          first[std::size_t(distance)].val(),\n                second[std::size_t(distance)].val()\n\
    \            );\n        assert((ordered & 1) == 0);\n        result[std::size_t(distance)]\
    \ = static_cast<long long>(ordered / 2);\n    }\n    return result;\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/dsu_on_tree.hpp\"\
    \n\n\n\n#line 7 \"graph/tree/dsu_on_tree.hpp\"\n\n#line 9 \"graph/tree/dsu_on_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct DsuOnTree\
    \ {\n    int n;\n    int root;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy_child;\n    std::vector<int> tin;\n    std::vector<int>\
    \ tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>> children;\n\
    \n    DsuOnTree() : n(0), root(-1) {}\n\n    explicit DsuOnTree(\n        const\
    \ m1une::graph::Graph<T>& graph,\n        int root_vertex = 0\n    ) {\n     \
    \   build(graph, root_vertex);\n    }\n\n    void build(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) {\n        n = graph.size();\n  \
    \      root = n == 0 ? -1 : root_vertex;\n        parent.assign(n, -2);\n    \
    \    parent_edge.assign(n, -1);\n        depth.assign(n, 0);\n        subtree_size.assign(n,\
    \ 1);\n        heavy_child.assign(n, -1);\n        tin.assign(n, -1);\n      \
    \  tout.assign(n, -1);\n        order.clear();\n        order.reserve(n);\n  \
    \      children.assign(n, {});\n        if (n == 0) return;\n\n        assert(0\
    \ <= root && root < n);\n        std::vector<int> stack;\n        stack.push_back(root);\n\
    \        parent[root] = -1;\n        while (!stack.empty()) {\n            int\
    \ vertex = stack.back();\n            stack.pop_back();\n            tin[vertex]\
    \ = int(order.size());\n            order.push_back(vertex);\n\n            for\
    \ (const auto& edge : graph[vertex]) {\n                if (!edge.alive || parent[edge.to]\
    \ != -2) continue;\n                parent[edge.to] = vertex;\n              \
    \  parent_edge[edge.to] = edge.id;\n                depth[edge.to] = depth[vertex]\
    \ + 1;\n                children[vertex].push_back(edge.to);\n               \
    \ stack.push_back(edge.to);\n            }\n        }\n        assert(int(order.size())\
    \ == n);\n\n        for (int index = n - 1; index >= 0; --index) {\n         \
    \   int vertex = order[index];\n            for (int child : children[vertex])\
    \ {\n                subtree_size[vertex] += subtree_size[child];\n          \
    \      if (\n                    heavy_child[vertex] == -1 ||\n              \
    \      subtree_size[heavy_child[vertex]] < subtree_size[child]\n             \
    \   ) {\n                    heavy_child[vertex] = child;\n                }\n\
    \            }\n            tout[vertex] = tin[vertex] + subtree_size[vertex];\n\
    \        }\n    }\n\n    int size() const {\n        return n;\n    }\n\n    bool\
    \ empty() const {\n        return n == 0;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < n);\n        return\
    \ {tin[vertex], tout[vertex]};\n    }\n\n    // Runs DSU on tree. `add(v)` inserts\
    \ one vertex into the maintained state,\n    // `remove(v)` erases it, and `answer(v)`\
    \ observes the state for subtree(v).\n    template <class Add, class Remove, class\
    \ Answer>\n    void run(Add add, Remove remove, Answer answer) const {\n     \
    \   if (n == 0) return;\n\n        enum ActionType {\n            Process,\n \
    \           AddSubtree,\n            AddVertex,\n            AnswerVertex,\n \
    \           RemoveSubtree,\n        };\n        struct Action {\n            ActionType\
    \ type;\n            int vertex;\n            bool keep;\n        };\n\n     \
    \   std::vector<Action> actions;\n        actions.reserve(3 * std::size_t(n));\n\
    \        actions.push_back(Action{Process, root, true});\n\n        while (!actions.empty())\
    \ {\n            Action action = actions.back();\n            actions.pop_back();\n\
    \            int vertex = action.vertex;\n\n            if (action.type == AddSubtree)\
    \ {\n                for (int index = tin[vertex]; index < tout[vertex]; ++index)\
    \ {\n                    add(order[index]);\n                }\n            }\
    \ else if (action.type == AddVertex) {\n                add(vertex);\n       \
    \     } else if (action.type == AnswerVertex) {\n                answer(vertex);\n\
    \            } else if (action.type == RemoveSubtree) {\n                for (int\
    \ index = tin[vertex]; index < tout[vertex]; ++index) {\n                    remove(order[index]);\n\
    \                }\n            } else {\n                if (!action.keep) {\n\
    \                    actions.push_back(Action{\n                        RemoveSubtree,\n\
    \                        vertex,\n                        false,\n           \
    \         });\n                }\n                actions.push_back(Action{AnswerVertex,\
    \ vertex, false});\n                actions.push_back(Action{AddVertex, vertex,\
    \ false});\n\n                for (int child : children[vertex]) {\n         \
    \           if (child != heavy_child[vertex]) {\n                        actions.push_back(Action{\n\
    \                            AddSubtree,\n                            child,\n\
    \                            false,\n                        });\n           \
    \         }\n                }\n                if (heavy_child[vertex] != -1)\
    \ {\n                    actions.push_back(Action{\n                        Process,\n\
    \                        heavy_child[vertex],\n                        true,\n\
    \                    });\n                }\n                for (int child :\
    \ children[vertex]) {\n                    if (child != heavy_child[vertex]) {\n\
    \                        actions.push_back(Action{Process, child, false});\n \
    \                   }\n                }\n            }\n        }\n    }\n};\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/euler_tour.hpp\"\
    \n\n\n\n#line 8 \"graph/tree/euler_tour.hpp\"\n\n#line 10 \"graph/tree/euler_tour.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct EulerTour\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<std::vector<int>> children;\n\n   private:\n    int _n;\n\n \
    \   void check_vertex(int v) const {\n        assert(0 <= v && v < _n);\n    \
    \    assert(tin[v] != -1);\n    }\n\n   public:\n    EulerTour() : root(-1), _n(0)\
    \ {}\n    explicit EulerTour(const m1une::graph::Graph<T>& g, int root_ = 0) {\n\
    \        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        parent.assign(_n, -2);\n        parent_edge.assign(_n, -1);\n       \
    \ depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n        subtree_size.assign(_n,\
    \ 0);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        children.assign(_n, {});\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n\n        struct Frame\
    \ {\n            int v;\n            int state;\n        };\n\n        std::vector<Frame>\
    \ stack;\n        stack.push_back({root, 0});\n        parent[root] = -1;\n\n\
    \        while (!stack.empty()) {\n            Frame frame = stack.back();\n \
    \           stack.pop_back();\n            int v = frame.v;\n            if (frame.state\
    \ == 0) {\n                tin[v] = int(order.size());\n                order.push_back(v);\n\
    \                stack.push_back({v, 1});\n                const auto& adj = g[v];\n\
    \                for (int i = int(adj.size()) - 1; i >= 0; --i) {\n          \
    \          const auto& e = adj[i];\n                    if (!e.alive) continue;\n\
    \                    if (parent[e.to] != -2) continue;\n                    parent[e.to]\
    \ = v;\n                    parent_edge[e.to] = e.id;\n                    depth[e.to]\
    \ = depth[v] + 1;\n                    dist[e.to] = dist[v] + e.cost;\n      \
    \              children[v].push_back(e.to);\n                    stack.push_back({e.to,\
    \ 0});\n                }\n                std::reverse(children[v].begin(), children[v].end());\n\
    \            } else {\n                subtree_size[v] = 1;\n                for\
    \ (int child : children[v]) subtree_size[v] += subtree_size[child];\n        \
    \        tout[v] = int(order.size());\n            }\n        }\n    }\n\n   \
    \ int size() const {\n        return _n;\n    }\n\n    int visited_size() const\
    \ {\n        return int(order.size());\n    }\n\n    bool empty() const {\n  \
    \      return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v) const {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        return tin[u] <=\
    \ tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v, int u) const\
    \ {\n        return is_ancestor(u, v);\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ v, bool edge = false) const {\n        check_vertex(v);\n        return {tin[v]\
    \ + (edge ? 1 : 0), tout[v]};\n    }\n\n    std::vector<int> subtree_vertices(int\
    \ v) const {\n        check_vertex(v);\n        return std::vector<int>(order.begin()\
    \ + tin[v], order.begin() + tout[v]);\n    }\n\n    template <class F>\n    void\
    \ for_each_subtree(int v, F f) const {\n        auto [l, r] = subtree_range(v);\n\
    \        for (int i = l; i < r; ++i) f(order[i]);\n    }\n};\n\n}  // namespace\
    \ tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/heavy_light_decomposition.hpp\"\
    \n\n\n\n#line 8 \"graph/tree/heavy_light_decomposition.hpp\"\n\n#line 10 \"graph/tree/heavy_light_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nstruct HldPathSegment {\n    int l;\n\
    \    int r;\n    bool reversed;\n};\n\ntemplate <class T = int>\nstruct HeavyLightDecomposition\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy;\n    std::vector<int> head;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\n   private:\n\
    \    int _n;\n\n    void check_vertex(int v) const {\n        assert(0 <= v &&\
    \ v < _n);\n        assert(tin[v] != -1);\n    }\n\n    static void add_segment(std::vector<HldPathSegment>&\
    \ result, int l, int r, bool reversed) {\n        if (l < r) result.push_back({l,\
    \ r, reversed});\n    }\n\n   public:\n    HeavyLightDecomposition() : root(-1),\
    \ _n(0) {}\n    explicit HeavyLightDecomposition(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n = g.size();\n      \
    \  root = _n == 0 ? -1 : root_;\n        parent.assign(_n, -2);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 1);\n        heavy.assign(_n, -1);\n        head.assign(_n,\
    \ -1);\n        tin.assign(_n, -1);\n        tout.assign(_n, -1);\n        order.clear();\n\
    \        order.reserve(_n);\n        if (_n == 0) return;\n        assert(0 <=\
    \ root && root < _n);\n\n        std::vector<int> dfs_order;\n        dfs_order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        parent[root] = -1;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            dfs_order.push_back(v);\n            for (const auto& e : g[v]) {\n\
    \                if (!e.alive) continue;\n                if (parent[e.to] !=\
    \ -2) continue;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                stack.push_back(e.to);\n            }\n\
    \        }\n\n        for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n\
    \            int v = dfs_order[i];\n            if (parent[v] == -1) continue;\n\
    \            int p = parent[v];\n            subtree_size[p] += subtree_size[v];\n\
    \            if (heavy[p] == -1 || subtree_size[heavy[p]] < subtree_size[v]) heavy[p]\
    \ = v;\n        }\n\n        order.assign(dfs_order.size(), -1);\n        int\
    \ timer = 0;\n        std::vector<std::pair<int, int>> starts = {std::pair<int,\
    \ int>{root, root}};\n        while (!starts.empty()) {\n            auto [start,\
    \ h] = starts.back();\n            starts.pop_back();\n            for (int v\
    \ = start; v != -1; v = heavy[v]) {\n                head[v] = h;\n          \
    \      tin[v] = timer;\n                order[timer++] = v;\n                for\
    \ (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {\n                    if\
    \ (!it->alive) continue;\n                    int to = it->to;\n             \
    \       if (parent[to] != v || to == heavy[v]) continue;\n                   \
    \ starts.push_back({to, to});\n                }\n            }\n        }\n \
    \       for (int i = int(dfs_order.size()) - 1; i >= 0; i--) {\n            int\
    \ v = dfs_order[i];\n            tout[v] = tin[v] + subtree_size[v];\n       \
    \ }\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    int lca(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        while (head[u]\
    \ != head[v]) {\n            if (depth[head[u]] < depth[head[v]]) std::swap(u,\
    \ v);\n            u = parent[head[u]];\n        }\n        return depth[u] <\
    \ depth[v] ? u : v;\n    }\n\n    int dist_edges(int u, int v) const {\n     \
    \   int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n \
    \   }\n\n    T dist_cost(int u, int v) const {\n        int w = lca(u, v);\n \
    \       return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   while (v != -1) {\n            int h = head[v];\n            int len = depth[v]\
    \ - depth[h];\n            if (k <= len) return order[tin[v] - k];\n         \
    \   k -= len + 1;\n            v = parent[h];\n        }\n        return -1;\n\
    \    }\n\n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::pair<int, int> subtree_range(int v, bool\
    \ edge = false) const {\n        check_vertex(v);\n        return {tin[v] + (edge\
    \ ? 1 : 0), tout[v]};\n    }\n\n    std::vector<HldPathSegment> path_segments(int\
    \ u, int v, bool edge = false) const {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        std::vector<HldPathSegment> result, down;\n        while (head[u] !=\
    \ head[v]) {\n            if (depth[head[u]] >= depth[head[v]]) {\n          \
    \      add_segment(result, tin[head[u]], tin[u] + 1, true);\n                u\
    \ = parent[head[u]];\n            } else {\n                add_segment(down,\
    \ tin[head[v]], tin[v] + 1, false);\n                v = parent[head[v]];\n  \
    \          }\n        }\n\n        if (depth[u] >= depth[v]) {\n            add_segment(result,\
    \ tin[v] + (edge ? 1 : 0), tin[u] + 1, true);\n        } else {\n            add_segment(down,\
    \ tin[u] + (edge ? 1 : 0), tin[v] + 1, false);\n        }\n        std::reverse(down.begin(),\
    \ down.end());\n        result.insert(result.end(), down.begin(), down.end());\n\
    \        return result;\n    }\n\n    template <class F>\n    void for_each_path(int\
    \ u, int v, F f, bool edge = false) const {\n        for (auto seg : path_segments(u,\
    \ v, edge)) f(seg.l, seg.r, seg.reversed);\n    }\n};\n\n}  // namespace tree\n\
    }  // namespace m1une\n\n\n#line 1 \"graph/tree/range_contour_query.hpp\"\n\n\n\
    \n#line 7 \"graph/tree/range_contour_query.hpp\"\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n    static\
    \ constexpr bool commutative = true;\n\n    // Returns the identity element for\
    \ addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/tree/rooted_tree.hpp\"\n\n\n\n#line 7 \"\
    graph/tree/rooted_tree.hpp\"\n\n#line 9 \"graph/tree/rooted_tree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct RootedTree {\n\
    \    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n  \
    \  int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<std::vector<int>> up;\n\n   private:\n    int _n;\n    int _log;\n\
    \n    void check_vertex(int v) const {\n        assert(0 <= v && v < _n);\n  \
    \      assert(tin[v] != -1);\n    }\n\n   public:\n    RootedTree() : root(-1),\
    \ _n(0), _log(0) {}\n    explicit RootedTree(const m1une::graph::Graph<T>& g,\
    \ int root_ = 0) {\n        build(g, root_);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root_ = 0) {\n        _n = g.size();\n        root = _n == 0 ? -1 : root_;\n\
    \        _log = 1;\n        while ((1U << _log) <= (unsigned int)(std::max(1,\
    \ _n))) _log++;\n\n        parent.assign(_n, -1);\n        parent_edge.assign(_n,\
    \ -1);\n        depth.assign(_n, 0);\n        dist.assign(_n, T(0));\n       \
    \ subtree_size.assign(_n, 0);\n        tin.assign(_n, -1);\n        tout.assign(_n,\
    \ -1);\n        order.clear();\n        order.reserve(_n);\n        up.assign(_log,\
    \ std::vector<int>(_n, -1));\n\n        if (_n == 0) return;\n        assert(0\
    \ <= root && root < _n);\n\n        struct Frame {\n            int v;\n     \
    \       int state;\n        };\n\n        std::vector<char> visited(_n, false);\n\
    \        std::vector<Frame> stack;\n        stack.push_back({root, 0});\n    \
    \    visited[root] = true;\n        int timer = 0;\n\n        while (!stack.empty())\
    \ {\n            Frame frame = stack.back();\n            stack.pop_back();\n\
    \            int v = frame.v;\n            if (frame.state == 0) {\n         \
    \       tin[v] = timer++;\n                order.push_back(v);\n             \
    \   up[0][v] = parent[v];\n                for (int k = 1; k < _log; k++) {\n\
    \                    int p = up[k - 1][v];\n                    up[k][v] = p ==\
    \ -1 ? -1 : up[k - 1][p];\n                }\n\n                stack.push_back({v,\
    \ 1});\n                const auto& adj = g[v];\n                for (int i =\
    \ int(adj.size()) - 1; i >= 0; i--) {\n                    const auto& e = adj[i];\n\
    \                    if (!e.alive) continue;\n                    if (visited[e.to])\
    \ continue;\n                    visited[e.to] = true;\n                    parent[e.to]\
    \ = v;\n                    parent_edge[e.to] = e.id;\n                    depth[e.to]\
    \ = depth[v] + 1;\n                    dist[e.to] = dist[v] + e.cost;\n      \
    \              stack.push_back({e.to, 0});\n                }\n            } else\
    \ {\n                subtree_size[v]++;\n                if (parent[v] != -1)\
    \ subtree_size[parent[v]] += subtree_size[v];\n                tout[v] = timer;\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    int\
    \ log() const {\n        return _log;\n    }\n\n    bool is_ancestor(int u, int\
    \ v) const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int kth_ancestor(int\
    \ v, int k) const {\n        check_vertex(v);\n        assert(0 <= k);\n     \
    \   int bit = 0;\n        while (k > 0 && v != -1) {\n            if (k & 1) {\n\
    \                if (_log <= bit) return -1;\n                v = up[bit][v];\n\
    \            }\n            k >>= 1;\n            bit++;\n        }\n        return\
    \ v;\n    }\n\n    int lca(int u, int v) const {\n        check_vertex(u);\n \
    \       check_vertex(v);\n        if (depth[u] < depth[v]) std::swap(u, v);\n\
    \        u = kth_ancestor(u, depth[u] - depth[v]);\n        if (u == v) return\
    \ u;\n        for (int k = _log - 1; k >= 0; k--) {\n            if (up[k][u]\
    \ != up[k][v]) {\n                u = up[k][u];\n                v = up[k][v];\n\
    \            }\n        }\n        return parent[u];\n    }\n\n    int dist_edges(int\
    \ u, int v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v]\
    \ - 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int\
    \ w = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    int jump(int from, int to, int k) const {\n        check_vertex(from);\n\
    \        check_vertex(to);\n        assert(0 <= k);\n        int w = lca(from,\
    \ to);\n        int up_len = depth[from] - depth[w];\n        int down_len = depth[to]\
    \ - depth[w];\n        if (up_len + down_len < k) return -1;\n        if (k <=\
    \ up_len) return kth_ancestor(from, k);\n        return kth_ancestor(to, down_len\
    \ - (k - up_len));\n    }\n\n    std::vector<int> path(int u, int v) const {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        int w = lca(u, v);\n\
    \        std::vector<int> a, b;\n        for (int x = u; x != w; x = parent[x])\
    \ a.push_back(x);\n        a.push_back(w);\n        for (int x = v; x != w; x\
    \ = parent[x]) b.push_back(x);\n        std::reverse(b.begin(), b.end());\n  \
    \      a.insert(a.end(), b.begin(), b.end());\n        return a;\n    }\n\n  \
    \  std::vector<int> path_edges(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        int w = lca(u, v);\n        std::vector<int>\
    \ a, b;\n        for (int x = u; x != w; x = parent[x]) a.push_back(parent_edge[x]);\n\
    \        for (int x = v; x != w; x = parent[x]) b.push_back(parent_edge[x]);\n\
    \        std::reverse(b.begin(), b.end());\n        a.insert(a.end(), b.begin(),\
    \ b.end());\n        return a;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ v) const {\n        check_vertex(v);\n        return {tin[v], tout[v]};\n  \
    \  }\n\n    std::vector<int> subtree_vertices(int v) const {\n        check_vertex(v);\n\
    \        return std::vector<int>(order.begin() + tin[v], order.begin() + tout[v]);\n\
    \    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 13 \"graph/tree/range_contour_query.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nstruct RangeContourPathEntry\
    \ {\n    int centroid;\n    int distance;\n    int subtree;\n};\n\nstruct RangeContourLayout\
    \ {\n    int n = 0;\n    std::vector<std::vector<RangeContourPathEntry>> path;\n\
    \    std::vector<int> all_size;\n    std::vector<int> subtree_size;\n\n    template\
    \ <class EdgeCost>\n    void build(const m1une::graph::Graph<EdgeCost>& graph)\
    \ {\n        n = graph.size();\n        path.assign(n, {});\n        all_size.assign(n,\
    \ 0);\n        subtree_size.assign(n, 0);\n        if (n == 0) return;\n\n#ifndef\
    \ NDEBUG\n        std::vector<int> incidence(graph.edge_count(), 0);\n       \
    \ for (int vertex = 0; vertex < n; vertex++) {\n            for (const auto& edge\
    \ : graph[vertex]) {\n                if (!edge.alive) continue;\n           \
    \     assert(0 <= edge.id && edge.id < graph.edge_count());\n                incidence[edge.id]++;\n\
    \            }\n        }\n        int active_edges = 0;\n        for (int count\
    \ : incidence) {\n            if (count == 0) continue;\n            assert(count\
    \ == 2);\n            active_edges++;\n        }\n        assert(active_edges\
    \ == n - 1);\n#endif\n\n        RootedTree<EdgeCost> rooted(graph, 0);\n     \
    \   assert(int(rooted.order.size()) == n);\n        CentroidDecomposition<EdgeCost>\
    \ decomposition(graph);\n\n        for (int vertex = 0; vertex < n; vertex++)\
    \ {\n            int previous = -1;\n            for (\n                int centroid\
    \ = vertex;\n                centroid != -1;\n                centroid = decomposition.parent[centroid]\n\
    \            ) {\n                int distance = rooted.dist_edges(vertex, centroid);\n\
    \                path[vertex].push_back(\n                    RangeContourPathEntry{centroid,\
    \ distance, previous}\n                );\n                all_size[centroid]\
    \ = std::max(\n                    all_size[centroid],\n                    distance\
    \ + 1\n                );\n                if (previous != -1) {\n           \
    \         subtree_size[previous] = std::max(\n                        subtree_size[previous],\n\
    \                        distance + 1\n                    );\n              \
    \  }\n                previous = centroid;\n            }\n        }\n    }\n\
    };\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass RangeContourFenwick\
    \ {\n   public:\n    using T = typename Group::value_type;\n\n   private:\n  \
    \  int _n = 0;\n    std::vector<T> _data;\n\n    T prefix_product(int right) const\
    \ {\n        T result = Group::id();\n        while (right > 0) {\n          \
    \  result = Group::op(result, _data[right]);\n            right -= right & -right;\n\
    \        }\n        return result;\n    }\n\n   public:\n    RangeContourFenwick()\
    \ : _data(1, Group::id()) {}\n\n    explicit RangeContourFenwick(int n)\n    \
    \    : _n(n), _data(n + 1, Group::id()) {\n        assert(0 <= n);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    void apply(int index,\
    \ const T& value) {\n        assert(0 <= index && index < _n);\n        for (index++;\
    \ index <= _n; index += index & -index) {\n            _data[index] = Group::op(_data[index],\
    \ value);\n        }\n    }\n\n    T product(int left, int right) const {\n  \
    \      left = std::max(left, 0);\n        right = std::min(right, _n);\n     \
    \   if (right <= left) return Group::id();\n        return Group::op(\n      \
    \      Group::inv(prefix_product(left)),\n            prefix_product(right)\n\
    \        );\n    }\n\n    void range_apply(int left, int right, const T& value)\
    \ {\n        left = std::max(left, 0);\n        right = std::min(right, _n);\n\
    \        if (right <= left) return;\n        apply(left, value);\n        if (right\
    \ < _n) apply(right, Group::inv(value));\n    }\n\n    T get(int index) const\
    \ {\n        assert(0 <= index && index < _n);\n        return prefix_product(index\
    \ + 1);\n    }\n};\n\n}  // namespace internal\n\ntemplate <m1une::monoid::IsCommutativeGroup\
    \ Group>\nclass VertexApplyRangeContourProduct {\n   public:\n    using T = typename\
    \ Group::value_type;\n\n   private:\n    internal::RangeContourLayout _layout;\n\
    \    std::vector<T> _value;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _all;\n    std::vector<internal::RangeContourFenwick<Group>> _subtree;\n\n \
    \   void check_vertex(int vertex) const {\n        assert(0 <= vertex && vertex\
    \ < size());\n    }\n\n   public:\n    VertexApplyRangeContourProduct() = default;\n\
    \n    template <class EdgeCost>\n    explicit VertexApplyRangeContourProduct(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _value.assign(n, Group::id());\n    \
    \    _all.assign(n, internal::RangeContourFenwick<Group>());\n        _subtree.assign(n,\
    \ internal::RangeContourFenwick<Group>());\n        for (int index = 0; index\
    \ < n; index++) {\n            _all[index] =\n                internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n\
    \            _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n        if (!initial.empty()) {\n            for (int vertex = 0; vertex\
    \ < n; vertex++) {\n                apply(vertex, initial[vertex]);\n        \
    \    }\n        }\n    }\n\n    int size() const {\n        return _layout.n;\n\
    \    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n   \
    \ T get(int vertex) const {\n        check_vertex(vertex);\n        return _value[vertex];\n\
    \    }\n\n    void apply(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _value[vertex] = Group::op(_value[vertex], value);\n        for (const\
    \ auto& entry : _layout.path[vertex]) {\n            _all[entry.centroid].apply(entry.distance,\
    \ value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].apply(entry.distance,\
    \ value);\n            }\n        }\n    }\n\n    void set(int vertex, const T&\
    \ value) {\n        check_vertex(vertex);\n        apply(vertex, Group::op(Group::inv(_value[vertex]),\
    \ value));\n    }\n\n    T prod(int vertex, int left_distance, int right_distance)\
    \ const {\n        check_vertex(vertex);\n        assert(0 <= left_distance &&\
    \ left_distance <= right_distance);\n        T result = Group::id();\n       \
    \ for (const auto& entry : _layout.path[vertex]) {\n            int left = left_distance\
    \ - entry.distance;\n            int right = right_distance - entry.distance;\n\
    \            result = Group::op(\n                result,\n                _all[entry.centroid].product(left,\
    \ right)\n            );\n            if (entry.subtree != -1) {\n           \
    \     result = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].product(left, right)\n      \
    \              )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n};\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\nclass\
    \ VertexGetRangeContourApply {\n   public:\n    using T = typename Group::value_type;\n\
    \n   private:\n    internal::RangeContourLayout _layout;\n    std::vector<T> _base;\n\
    \    std::vector<internal::RangeContourFenwick<Group>> _all;\n    std::vector<internal::RangeContourFenwick<Group>>\
    \ _subtree;\n\n    void check_vertex(int vertex) const {\n        assert(0 <=\
    \ vertex && vertex < size());\n    }\n\n   public:\n    VertexGetRangeContourApply()\
    \ = default;\n\n    template <class EdgeCost>\n    explicit VertexGetRangeContourApply(\n\
    \        const m1une::graph::Graph<EdgeCost>& graph,\n        const std::vector<T>&\
    \ initial = {}\n    ) {\n        build(graph, initial);\n    }\n\n    template\
    \ <class EdgeCost>\n    void build(\n        const m1une::graph::Graph<EdgeCost>&\
    \ graph,\n        const std::vector<T>& initial = {}\n    ) {\n        assert(initial.empty()\
    \ || int(initial.size()) == graph.size());\n        _layout.build(graph);\n  \
    \      const int n = _layout.n;\n        _base = initial.empty() ? std::vector<T>(n,\
    \ Group::id()) : initial;\n        _all.assign(n, internal::RangeContourFenwick<Group>());\n\
    \        _subtree.assign(n, internal::RangeContourFenwick<Group>());\n       \
    \ for (int index = 0; index < n; index++) {\n            _all[index] =\n     \
    \           internal::RangeContourFenwick<Group>(_layout.all_size[index]);\n \
    \           _subtree[index] =\n                internal::RangeContourFenwick<Group>(\n\
    \                    _layout.subtree_size[index]\n                );\n       \
    \ }\n    }\n\n    int size() const {\n        return _layout.n;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    T get(int vertex)\
    \ const {\n        check_vertex(vertex);\n        T result = _base[vertex];\n\
    \        for (const auto& entry : _layout.path[vertex]) {\n            result\
    \ = Group::op(\n                result,\n                _all[entry.centroid].get(entry.distance)\n\
    \            );\n            if (entry.subtree != -1) {\n                result\
    \ = Group::op(\n                    result,\n                    Group::inv(\n\
    \                        _subtree[entry.subtree].get(entry.distance)\n       \
    \             )\n                );\n            }\n        }\n        return\
    \ result;\n    }\n\n    void point_apply(int vertex, const T& value) {\n     \
    \   check_vertex(vertex);\n        _base[vertex] = Group::op(_base[vertex], value);\n\
    \    }\n\n    void set(int vertex, const T& value) {\n        check_vertex(vertex);\n\
    \        _base[vertex] = Group::op(\n            _base[vertex],\n            Group::op(Group::inv(get(vertex)),\
    \ value)\n        );\n    }\n\n    void apply(\n        int vertex,\n        int\
    \ left_distance,\n        int right_distance,\n        const T& value\n    ) {\n\
    \        check_vertex(vertex);\n        assert(0 <= left_distance && left_distance\
    \ <= right_distance);\n        for (const auto& entry : _layout.path[vertex])\
    \ {\n            int left = left_distance - entry.distance;\n            int right\
    \ = right_distance - entry.distance;\n            _all[entry.centroid].range_apply(left,\
    \ right, value);\n            if (entry.subtree != -1) {\n                _subtree[entry.subtree].range_apply(left,\
    \ right, value);\n            }\n        }\n    }\n};\n\ntemplate <class T>\n\
    class VertexAddRangeContourSum\n    : public VertexApplyRangeContourProduct<m1une::monoid::Add<T>>\
    \ {\n   private:\n    using Base = VertexApplyRangeContourProduct<m1une::monoid::Add<T>>;\n\
    \n   public:\n    using Base::Base;\n\n    void add(int vertex, const T& delta)\
    \ {\n        Base::apply(vertex, delta);\n    }\n\n    T sum(int vertex, int left_distance,\
    \ int right_distance) const {\n        return Base::prod(vertex, left_distance,\
    \ right_distance);\n    }\n};\n\ntemplate <class T>\nclass VertexGetRangeContourAdd\n\
    \    : public VertexGetRangeContourApply<m1une::monoid::Add<T>> {\n   private:\n\
    \    using Base = VertexGetRangeContourApply<m1une::monoid::Add<T>>;\n\n   public:\n\
    \    using Base::Base;\n\n    void add(int vertex, const T& delta) {\n       \
    \ Base::point_apply(vertex, delta);\n    }\n};\n\n}  // namespace tree\n}  //\
    \ namespace m1une\n\n\n#line 1 \"graph/tree/rerooting_dp.hpp\"\n\n\n\n#line 5\
    \ \"graph/tree/rerooting_dp.hpp\"\n\n#line 7 \"graph/tree/rerooting_dp.hpp\"\n\
    \nnamespace m1une {\nnamespace tree {\n\ntemplate <class T, class DP, class Merge,\
    \ class AddVertex, class AddEdge>\nstd::vector<DP> rerooting_dp(const m1une::graph::Graph<T>&\
    \ g, DP id, Merge merge, AddVertex add_vertex,\n                             AddEdge\
    \ add_edge) {\n    int n = g.size();\n    std::vector<int> parent(n, -2), parent_edge(n,\
    \ -1), order;\n    order.reserve(n);\n    for (int root = 0; root < n; root++)\
    \ {\n        if (parent[root] != -2) continue;\n        parent[root] = -1;\n \
    \       std::vector<int> stack = {root};\n        while (!stack.empty()) {\n \
    \           int v = stack.back();\n            stack.pop_back();\n           \
    \ order.push_back(v);\n            for (const auto& e : g[v]) {\n            \
    \    if (!e.alive) continue;\n                if (parent[e.to] != -2) continue;\n\
    \                parent[e.to] = v;\n                parent_edge[e.to] = e.id;\n\
    \                stack.push_back(e.to);\n            }\n        }\n    }\n\n \
    \   std::vector<DP> down(n, id), outside(n, id), answer(n, id);\n    for (int\
    \ i = n - 1; i >= 0; i--) {\n        int v = order[i];\n        DP acc = id;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           if (parent[e.to] != v) continue;\n            acc = merge(acc, add_edge(down[e.to],\
    \ e));\n        }\n        down[v] = add_vertex(acc, v);\n    }\n\n    for (int\
    \ v : order) {\n        int d = int(g[v].size());\n        std::vector<DP> contrib(d,\
    \ id);\n        for (int i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n\
    \            if (!e.alive) continue;\n            if (parent[e.to] == v) {\n \
    \               contrib[i] = add_edge(down[e.to], e);\n            } else if (parent[v]\
    \ == e.to && parent_edge[v] == e.id) {\n                contrib[i] = add_edge(outside[v],\
    \ e);\n            }\n        }\n\n        std::vector<DP> pref(d + 1, id), suff(d\
    \ + 1, id);\n        for (int i = 0; i < d; i++) pref[i + 1] = merge(pref[i],\
    \ contrib[i]);\n        for (int i = d - 1; i >= 0; i--) suff[i] = merge(contrib[i],\
    \ suff[i + 1]);\n        answer[v] = add_vertex(pref[d], v);\n\n        for (int\
    \ i = 0; i < d; i++) {\n            const auto& e = g[v][i];\n            if (!e.alive)\
    \ continue;\n            if (parent[e.to] != v) continue;\n            outside[e.to]\
    \ = add_vertex(merge(pref[i], suff[i + 1]), v);\n        }\n    }\n\n    return\
    \ answer;\n}\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/rerooting_static_top_tree.hpp\"\
    \n\n\n\n#line 6 \"graph/tree/rerooting_static_top_tree.hpp\"\n#include <optional>\n\
    #line 10 \"graph/tree/rerooting_static_top_tree.hpp\"\n\n#line 12 \"graph/tree/rerooting_static_top_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\nnamespace internal {\n\nenum class\
    \ RerootingStaticTopTreeNodeType {\n    Compress,\n    Rake,\n    AddEdge,\n \
    \   AddVertex,\n};\n\nenum class RerootingStaticTopTreeStepType {\n    CompressLower,\n\
    \    CompressUpper,\n    AddEdge,\n    RakeLeft,\n    RakeRight,\n    AddVertex,\n\
    };\n\n}  // namespace internal\n\ntemplate <class T, class Vertex, class Path,\
    \ class Point, class CompressDown, class CompressUp, class Rake,\n          class\
    \ AddEdgeDown, class AddEdgeUp, class AddVertex>\nstruct RerootingStaticTopTree\
    \ {\n    using cost_type = T;\n    using vertex_type = Vertex;\n    using path_type\
    \ = Path;\n    using point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n\
    \    using node_type = internal::RerootingStaticTopTreeNodeType;\n    using step_type\
    \ = internal::RerootingStaticTopTreeStepType;\n\n    struct Node {\n        node_type\
    \ type;\n        int left = -1;\n        int right = -1;\n        int parent =\
    \ -1;\n        int vertex = -1;\n        edge_type edge;\n        int size = 0;\n\
    \        int height = 1;\n        std::optional<Path> path_down;\n        std::optional<Path>\
    \ path_up;\n        std::optional<Point> point;\n    };\n\n    struct RerootingStep\
    \ {\n        step_type type;\n        int node = -1;\n        int sibling = -1;\n\
    \        int vertex = -1;\n        edge_type edge;\n    };\n\n   private:\n  \
    \  int _n;\n    int _root;\n    int _root_node;\n    Point _point_id;\n    CompressDown\
    \ _compress_down;\n    CompressUp _compress_up;\n    Rake _rake;\n    AddEdgeDown\
    \ _add_edge_down;\n    AddEdgeUp _add_edge_up;\n    AddVertex _add_vertex;\n \
    \   std::vector<Vertex> _values;\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _vertex_node;\n    std::vector<int> _edge_node;\n    std::vector<int> _parent;\n\
    \    std::vector<int> _subtree_size;\n    std::vector<int> _heavy;\n    std::vector<edge_type>\
    \ _heavy_edge;\n    std::vector<std::vector<edge_type>> _children;\n\n    static\
    \ edge_type reversed_edge(edge_type e) {\n        std::swap(e.from, e.to);\n \
    \       return e;\n    }\n\n    const Path& node_path_down(int node) const {\n\
    \        assert(0 <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path_down.has_value());\n\
    \        return *_nodes[node].path_down;\n    }\n\n    const Path& node_path_up(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].path_up.has_value());\n        return *_nodes[node].path_up;\n\
    \    }\n\n    const Point& node_point(int node) const {\n        assert(0 <= node\
    \ && node < int(_nodes.size()));\n        assert(_nodes[node].point.has_value());\n\
    \        return *_nodes[node].point;\n    }\n\n    void set_parent(int child,\
    \ int parent) {\n        if (child != -1) _nodes[child].parent = parent;\n   \
    \ }\n\n    void recompute(int node) {\n        auto& x = _nodes[node];\n     \
    \   if (x.type == node_type::Compress) {\n            x.path_down = _compress_down(node_path_down(x.left),\
    \ node_path_down(x.right), x.edge);\n            x.path_up = _compress_up(node_path_up(x.right),\
    \ node_path_up(x.left), reversed_edge(x.edge));\n        } else if (x.type ==\
    \ node_type::Rake) {\n            x.point = _rake(node_point(x.left), node_point(x.right));\n\
    \        } else if (x.type == node_type::AddEdge) {\n            x.point = _add_edge_down(node_path_down(x.left),\
    \ x.edge);\n        } else {\n            const Point& side = x.left == -1 ? _point_id\
    \ : node_point(x.left);\n            Path path = _add_vertex(side, _values[x.vertex],\
    \ x.vertex);\n            x.path_down = path;\n            x.path_up = std::move(path);\n\
    \        }\n    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = node_type::Compress;\n    \
    \    node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = node_type::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = node_type::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = node_type::AddVertex;\n        node.left\
    \ = side;\n        node.vertex = vertex;\n        node.size = 1 + (side == -1\
    \ ? 0 : _nodes[side].size);\n        node.height = 1 + (side == -1 ? 0 : _nodes[side].height);\n\
    \        int id = new_node(std::move(node));\n        _vertex_node[vertex] = id;\n\
    \        return id;\n    }\n\n    int weighted_split(const std::vector<int>& nodes,\
    \ int l, int r) const {\n        int total = 0;\n        for (int i = l; i < r;\
    \ i++) total += _nodes[nodes[i]].size;\n        int left_sum = 0;\n        for\
    \ (int i = l; i + 1 < r; i++) {\n            left_sum += _nodes[nodes[i]].size;\n\
    \            if (2 * left_sum >= total) return i + 1;\n        }\n        return\
    \ r - 1;\n    }\n\n    int build_rake(const std::vector<int>& nodes, int l, int\
    \ r) {\n        if (l == r) return -1;\n        if (l + 1 == r) return nodes[l];\n\
    \        int m = weighted_split(nodes, l, r);\n        return new_rake(build_rake(nodes,\
    \ l, m), build_rake(nodes, m, r));\n    }\n\n    int build_compress(const std::vector<int>&\
    \ nodes, const std::vector<edge_type>& edges, int l, int r) {\n        if (l +\
    \ 1 == r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n   \
    \     return new_compress(build_compress(nodes, edges, l, m), build_compress(nodes,\
    \ edges, m, r), edges[m - 1]);\n    }\n\n    int build_vertex(int v) {\n     \
    \   std::vector<int> side_nodes;\n        for (const auto& e : _children[v]) {\n\
    \            if (e.to == _heavy[v]) continue;\n            int child_path = build_path(e.to);\n\
    \            side_nodes.push_back(new_add_edge(child_path, e));\n        }\n \
    \       return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    RerootingStaticTopTree(const m1une::graph::Graph<T>&\
    \ g, const std::vector<Vertex>& values, Point point_id,\n                    \
    \       CompressDown compress_down, CompressUp compress_up, Rake rake,\n     \
    \                      AddEdgeDown add_edge_down, AddEdgeUp add_edge_up, AddVertex\
    \ add_vertex, int root = 0)\n        : _n(g.size()),\n          _root(_n == 0\
    \ ? -1 : root),\n          _root_node(-1),\n          _point_id(std::move(point_id)),\n\
    \          _compress_down(std::move(compress_down)),\n          _compress_up(std::move(compress_up)),\n\
    \          _rake(std::move(rake)),\n          _add_edge_down(std::move(add_edge_down)),\n\
    \          _add_edge_up(std::move(add_edge_up)),\n          _add_vertex(std::move(add_vertex)),\n\
    \          _values(values) {\n        build(g, root);\n    }\n\n    void build(const\
    \ m1une::graph::Graph<T>& g, int root = 0) {\n        _n = g.size();\n       \
    \ _root = _n == 0 ? -1 : root;\n        assert(int(_values.size()) == _n);\n \
    \       _nodes.clear();\n        _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(),\
    \ -1);\n        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n\
    \        _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n\
    \        _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n\
    \ == 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int root_node() const {\n        return _root_node;\n \
    \   }\n\n    int node_count() const {\n        return int(_nodes.size());\n  \
    \  }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(int id) const {\n        assert(0 <= id && id <\
    \ int(_nodes.size()));\n        return _nodes[id];\n    }\n\n    int parent_node(int\
    \ id) const {\n        return node(id).parent;\n    }\n\n    int vertex_node(int\
    \ v) const {\n        assert(0 <= v && v < _n);\n        return _vertex_node[v];\n\
    \    }\n\n    int local_point_node(int v) const {\n        int id = vertex_node(v);\n\
    \        assert(_nodes[id].type == node_type::AddVertex);\n        return _nodes[id].left;\n\
    \    }\n\n    const Point& local_point(int v) const {\n        int point_node\
    \ = local_point_node(v);\n        return point_node == -1 ? _point_id : node_point(point_node);\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& path_down(int node_id) const {\n        return node_path_down(node_id);\n\
    \    }\n\n    const Path& path_up(int node_id) const {\n        return node_path_up(node_id);\n\
    \    }\n\n    const Point& point(int node_id) const {\n        return node_point(node_id);\n\
    \    }\n\n    const Path& all_prod_down() const {\n        assert(_root_node !=\
    \ -1);\n        return path_down(_root_node);\n    }\n\n    const Path& all_prod_up()\
    \ const {\n        assert(_root_node != -1);\n        return path_up(_root_node);\n\
    \    }\n\n    const Point& point_id() const {\n        return _point_id;\n   \
    \ }\n\n    template <class F>\n    void for_each_rerooting_step(int v, F&& f)\
    \ const {\n        assert(0 <= v && v < _n);\n        int cur = _vertex_node[v];\n\
    \        assert(cur != -1);\n        while (_nodes[cur].parent != -1) {\n    \
    \        int par = _nodes[cur].parent;\n            const auto& p = _nodes[par];\n\
    \            RerootingStep step;\n            step.node = par;\n            if\
    \ (p.type == node_type::Compress) {\n                step.edge = p.edge;\n   \
    \             if (p.left == cur) {\n                    step.type = step_type::CompressLower;\n\
    \                    step.sibling = p.right;\n                } else {\n     \
    \               assert(p.right == cur);\n                    step.type = step_type::CompressUpper;\n\
    \                    step.sibling = p.left;\n                }\n            }\
    \ else if (p.type == node_type::Rake) {\n                if (p.left == cur) {\n\
    \                    step.type = step_type::RakeRight;\n                    step.sibling\
    \ = p.right;\n                } else {\n                    assert(p.right ==\
    \ cur);\n                    step.type = step_type::RakeLeft;\n              \
    \      step.sibling = p.left;\n                }\n            } else if (p.type\
    \ == node_type::AddEdge) {\n                assert(p.left == cur);\n         \
    \       step.type = step_type::AddEdge;\n                step.edge = p.edge;\n\
    \            } else {\n                assert(p.type == node_type::AddVertex);\n\
    \                assert(p.left == cur);\n                step.type = step_type::AddVertex;\n\
    \                step.vertex = p.vertex;\n            }\n            f(step);\n\
    \            cur = par;\n        }\n    }\n\n    std::vector<RerootingStep> rerooting_steps(int\
    \ v) const {\n        std::vector<RerootingStep> result;\n        int cur = vertex_node(v);\n\
    \        int depth = 0;\n        while (_nodes[cur].parent != -1) {\n        \
    \    cur = _nodes[cur].parent;\n            depth++;\n        }\n        result.reserve(depth);\n\
    \        for_each_rerooting_step(v, [&](const RerootingStep& step) {\n       \
    \     result.push_back(step);\n        });\n        return result;\n    }\n\n\
    \    template <class Folder>\n    auto fold_rerooting(int v, Folder folder) const\
    \ {\n        folder.start(v, _values[v], local_point(v));\n        for_each_rerooting_step(v,\
    \ [&](const RerootingStep& step) {\n            if (step.type == step_type::CompressLower)\
    \ {\n                folder.compress_lower(path_down(step.sibling), step.edge);\n\
    \            } else if (step.type == step_type::CompressUpper) {\n           \
    \     folder.compress_upper(path_up(step.sibling), reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::AddEdge) {\n                folder.add_edge(reversed_edge(step.edge));\n\
    \            } else if (step.type == step_type::RakeLeft) {\n                folder.rake_left(point(step.sibling));\n\
    \            } else if (step.type == step_type::RakeRight) {\n               \
    \ folder.rake_right(point(step.sibling));\n            } else {\n            \
    \    folder.add_vertex(step.vertex, _values[step.vertex]);\n            }\n  \
    \      });\n        return folder.result();\n    }\n\n    Path compress_down(const\
    \ Path& upper, const Path& lower, edge_type edge) const {\n        return _compress_down(upper,\
    \ lower, edge);\n    }\n\n    Path compress_up(const Path& lower, const Path&\
    \ upper, edge_type edge) const {\n        return _compress_up(lower, upper, edge);\n\
    \    }\n\n    Point rake(const Point& left, const Point& right) const {\n    \
    \    return _rake(left, right);\n    }\n\n    Point add_edge_down(const Path&\
    \ path, edge_type edge) const {\n        return _add_edge_down(path, edge);\n\
    \    }\n\n    Point add_edge_up(const Path& path, edge_type edge) const {\n  \
    \      return _add_edge_up(path, edge);\n    }\n\n    Path add_vertex(const Point&\
    \ side, const Vertex& value, int vertex) const {\n        return _add_vertex(side,\
    \ value, vertex);\n    }\n\n    static edge_type reverse_edge(edge_type edge)\
    \ {\n        return reversed_edge(edge);\n    }\n};\n\ntemplate <class T, class\
    \ Vertex, class Point, class CompressDown, class CompressUp, class Rake, class\
    \ AddEdgeDown,\n          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const\
    \ m1une::graph::Graph<T>&, const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n\
    \                       Rake, AddEdgeDown, AddEdgeUp, AddVertex, int)\n    ->\
    \ RerootingStaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point, Vertex,\
    \ int>, Point, CompressDown,\n                              CompressUp, Rake,\
    \ AddEdgeDown, AddEdgeUp, AddVertex>;\n\ntemplate <class T, class Vertex, class\
    \ Point, class CompressDown, class CompressUp, class Rake, class AddEdgeDown,\n\
    \          class AddEdgeUp, class AddVertex>\nRerootingStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, CompressDown, CompressUp,\n             \
    \          Rake, AddEdgeDown, AddEdgeUp, AddVertex)\n    -> RerootingStaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, CompressDown,\n\
    \                              CompressUp, Rake, AddEdgeDown, AddEdgeUp, AddVertex>;\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/sparse_table_lca.hpp\"\
    \n\n\n\n#line 9 \"graph/tree/sparse_table_lca.hpp\"\n\n#line 1 \"ds/range_query/sparse_table.hpp\"\
    \n\n\n\n#include <bit>\n#line 9 \"ds/range_query/sparse_table.hpp\"\n\n#line 11\
    \ \"ds/range_query/sparse_table.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    // A Sparse Table utilizing C++20 Concepts for type safety.\n// It requires a\
    \ Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n// [IMPORTANT] For\
    \ O(1) range queries to work correctly, the monoid operation MUST be idempotent.\n\
    // i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max, GCD, Bitwise AND/OR).\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable {\n    using T =\
    \ typename Monoid::value_type;\n\n   private:\n    int _n;\n    std::vector<std::vector<T>>\
    \ _st;\n\n   public:\n    // Constructs an empty sparse table.\n    SparseTable()\
    \ : _n(0) {}\n\n    // Constructs a sparse table from an existing vector in O(N\
    \ log N) time.\n    explicit SparseTable(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        // Compute the maximum power of 2\
    \ needed\n        int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Initialize the base level\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = v[i];\n        }\n\n        //\
    \ Build the sparse table\n        for (int k = 1; k < max_log; k++) {\n      \
    \      for (int i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] =\
    \ Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n\
    \        }\n    }\n    explicit SparseTable(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        for (int\
    \ i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n        }\n\
    \n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0; i +\
    \ (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Constructs a sparse table from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. Monoid::make(val)\
    \ if it exists.\n    // 2. Monoid::make(val, index) if the monoid requires global\
    \ indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x, i);\
    \ } ||\n        std::convertible_to<U, T>\n    )\n    explicit SparseTable(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       int max_log = std::bit_width((unsigned int)_n);\n        _st.assign(max_log,\
    \ std::vector<T>(_n));\n\n        // Compile-time branching based on the available\
    \ make() signature\n        for (int i = 0; i < _n; i++) {\n            if constexpr\
    \ (requires(U x) { Monoid::make(x); }) {\n                _st[0][i] = Monoid::make(v[i]);\n\
    \            } else if constexpr (requires(U x, int idx) { Monoid::make(x, idx);\
    \ }) {\n                _st[0][i] = Monoid::make(v[i], i);\n            } else\
    \ {\n                _st[0][i] = static_cast<T>(v[i]);\n            }\n      \
    \  }\n        for (int k = 1; k < max_log; k++) {\n            for (int i = 0;\
    \ i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k - 1][i],\
    \ _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\n    //\
    \ Returns the product (result of the monoid operation) in the range [l, r) in\
    \ O(1) time.\n    // Requires the monoid operation to be idempotent.\n    T prod(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n        if\
    \ (l == r) return Monoid::id();\n\n        // Calculate the largest power of 2\
    \ less than or equal to the interval length\n        int k = std::bit_width((unsigned\
    \ int)(r - l)) - 1;\n        return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"graph/tree/sparse_table_lca.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct SparseTableLca\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<int> first;\n    std::vector<int> euler;\n\n   private:\n   \
    \ struct RmqNode {\n        int depth;\n        int vertex;\n    };\n\n    struct\
    \ RmqMonoid {\n        using value_type = RmqNode;\n\n        static value_type\
    \ id() {\n            return {std::numeric_limits<int>::max(), -1};\n        }\n\
    \n        static value_type op(const value_type& a, const value_type& b) {\n \
    \           if (a.depth != b.depth) return a.depth < b.depth ? a : b;\n      \
    \      return a.vertex < b.vertex ? a : b;\n        }\n    };\n\n    int _n;\n\
    \    m1une::ds::SparseTable<RmqMonoid> _st;\n\n    void check_vertex(int v) const\
    \ {\n        assert(0 <= v && v < _n);\n        assert(first[v] != -1);\n    }\n\
    \n   public:\n    SparseTableLca() : root(-1), _n(0) {}\n    explicit SparseTableLca(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g, root_);\n    }\n\
    \n    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n\
    \ = g.size();\n        root = _n == 0 ? -1 : root_;\n        parent.assign(_n,\
    \ -2);\n        parent_edge.assign(_n, -1);\n        depth.assign(_n, 0);\n  \
    \      dist.assign(_n, T(0));\n        subtree_size.assign(_n, 0);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        first.assign(_n, -1);\n        euler.clear();\n        euler.reserve(std::max(0,\
    \ 2 * _n - 1));\n        _st = m1une::ds::SparseTable<RmqMonoid>();\n\n      \
    \  if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n        std::vector<int>\
    \ it(_n, 0);\n        std::vector<char> visited(_n, false);\n        std::vector<int>\
    \ stack = {root};\n        visited[root] = true;\n        parent[root] = -1;\n\
    \n        int timer = 0;\n        tin[root] = timer++;\n        order.push_back(root);\n\
    \        first[root] = 0;\n        euler.push_back(root);\n\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            if (it[v] < int(g[v].size()))\
    \ {\n                const auto& e = g[v][it[v]++];\n                if (!e.alive)\
    \ continue;\n                if (visited[e.to]) continue;\n                visited[e.to]\
    \ = true;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                tin[e.to] = timer++;\n                order.push_back(e.to);\n\
    \                first[e.to] = int(euler.size());\n                euler.push_back(e.to);\n\
    \                stack.push_back(e.to);\n            } else {\n              \
    \  subtree_size[v]++;\n                if (parent[v] != -1) subtree_size[parent[v]]\
    \ += subtree_size[v];\n                tout[v] = timer;\n                stack.pop_back();\n\
    \                if (!stack.empty()) euler.push_back(stack.back());\n        \
    \    }\n        }\n\n        std::vector<RmqNode> rmq;\n        rmq.reserve(euler.size());\n\
    \        for (int v : euler) rmq.push_back({depth[v], v});\n        _st = m1une::ds::SparseTable<RmqMonoid>(std::move(rmq));\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int lca(int\
    \ u, int v) const {\n        check_vertex(u);\n        check_vertex(v);\n    \
    \    int l = first[u], r = first[v];\n        if (l > r) std::swap(l, r);\n  \
    \      return _st.prod(l, r + 1).vertex;\n    }\n\n    int dist_edges(int u, int\
    \ v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v] -\
    \ 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int w\
    \ = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    std::pair<int, int> subtree_range(int v) const {\n        check_vertex(v);\n\
    \        return {tin[v], tout[v]};\n    }\n};\n\n}  // namespace tree\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/tree/static_top_tree.hpp\"\n\n\n\n#line 10 \"graph/tree/static_top_tree.hpp\"\
    \n\n#line 12 \"graph/tree/static_top_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\nnamespace internal {\n\nenum class StaticTopTreeNodeType {\n    Compress,\n\
    \    Rake,\n    AddEdge,\n    AddVertex,\n};\n\n}  // namespace internal\n\ntemplate\
    \ <class T, class Vertex, class Path, class Point, class Compress, class Rake,\
    \ class AddEdge,\n          class AddVertex>\nstruct StaticTopTree {\n    using\
    \ cost_type = T;\n    using vertex_type = Vertex;\n    using path_type = Path;\n\
    \    using point_type = Point;\n    using edge_type = m1une::graph::Edge<T>;\n\
    \n   private:\n    struct Node {\n        internal::StaticTopTreeNodeType type;\n\
    \        int left = -1;\n        int right = -1;\n        int parent = -1;\n \
    \       int vertex = -1;\n        edge_type edge;\n        int size = 0;\n   \
    \     int height = 1;\n        std::optional<Path> path;\n        std::optional<Point>\
    \ point;\n    };\n\n    int _n;\n    int _root;\n    int _root_node;\n    Point\
    \ _point_id;\n    Compress _compress;\n    Rake _rake;\n    AddEdge _add_edge;\n\
    \    AddVertex _add_vertex;\n    std::vector<Vertex> _values;\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _vertex_node;\n    std::vector<int> _edge_node;\n\
    \    std::vector<int> _parent;\n    std::vector<int> _subtree_size;\n    std::vector<int>\
    \ _heavy;\n    std::vector<edge_type> _heavy_edge;\n    std::vector<std::vector<edge_type>>\
    \ _children;\n\n    const Path& path_value(int node) const {\n        assert(0\
    \ <= node && node < int(_nodes.size()));\n        assert(_nodes[node].path.has_value());\n\
    \        return *_nodes[node].path;\n    }\n\n    const Point& point_value(int\
    \ node) const {\n        assert(0 <= node && node < int(_nodes.size()));\n   \
    \     assert(_nodes[node].point.has_value());\n        return *_nodes[node].point;\n\
    \    }\n\n    void set_parent(int child, int parent) {\n        if (child != -1)\
    \ _nodes[child].parent = parent;\n    }\n\n    void recompute(int node) {\n  \
    \      auto& x = _nodes[node];\n        if (x.type == internal::StaticTopTreeNodeType::Compress)\
    \ {\n            x.path = _compress(path_value(x.left), path_value(x.right), x.edge);\n\
    \        } else if (x.type == internal::StaticTopTreeNodeType::Rake) {\n     \
    \       x.point = _rake(point_value(x.left), point_value(x.right));\n        }\
    \ else if (x.type == internal::StaticTopTreeNodeType::AddEdge) {\n           \
    \ x.point = _add_edge(path_value(x.left), x.edge);\n        } else {\n       \
    \     const Point& side = x.left == -1 ? _point_id : point_value(x.left);\n  \
    \          x.path = _add_vertex(side, _values[x.vertex], x.vertex);\n        }\n\
    \    }\n\n    int new_node(Node node) {\n        int id = int(_nodes.size());\n\
    \        _nodes.push_back(std::move(node));\n        set_parent(_nodes[id].left,\
    \ id);\n        set_parent(_nodes[id].right, id);\n        recompute(id);\n  \
    \      return id;\n    }\n\n    int new_compress(int left, int right, edge_type\
    \ edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Compress;\n\
    \        node.left = left;\n        node.right = right;\n        node.edge = edge;\n\
    \        node.size = _nodes[left].size + _nodes[right].size;\n        node.height\
    \ = std::max(_nodes[left].height, _nodes[right].height) + 1;\n        int id =\
    \ new_node(std::move(node));\n        if (0 <= edge.id && edge.id < int(_edge_node.size()))\
    \ _edge_node[edge.id] = id;\n        return id;\n    }\n\n    int new_rake(int\
    \ left, int right) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::Rake;\n\
    \        node.left = left;\n        node.right = right;\n        node.size = _nodes[left].size\
    \ + _nodes[right].size;\n        node.height = std::max(_nodes[left].height, _nodes[right].height)\
    \ + 1;\n        return new_node(std::move(node));\n    }\n\n    int new_add_edge(int\
    \ child, edge_type edge) {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddEdge;\n\
    \        node.left = child;\n        node.edge = edge;\n        node.size = _nodes[child].size;\n\
    \        node.height = _nodes[child].height + 1;\n        int id = new_node(std::move(node));\n\
    \        if (0 <= edge.id && edge.id < int(_edge_node.size())) _edge_node[edge.id]\
    \ = id;\n        return id;\n    }\n\n    int new_add_vertex(int side, int vertex)\
    \ {\n        Node node;\n        node.type = internal::StaticTopTreeNodeType::AddVertex;\n\
    \        node.left = side;\n        node.vertex = vertex;\n        node.size =\
    \ 1 + (side == -1 ? 0 : _nodes[side].size);\n        node.height = 1 + (side ==\
    \ -1 ? 0 : _nodes[side].height);\n        int id = new_node(std::move(node));\n\
    \        _vertex_node[vertex] = id;\n        return id;\n    }\n\n    int weighted_split(const\
    \ std::vector<int>& nodes, int l, int r) const {\n        int total = 0;\n   \
    \     for (int i = l; i < r; i++) total += _nodes[nodes[i]].size;\n        int\
    \ left_sum = 0;\n        for (int i = l; i + 1 < r; i++) {\n            left_sum\
    \ += _nodes[nodes[i]].size;\n            if (2 * left_sum >= total) return i +\
    \ 1;\n        }\n        return r - 1;\n    }\n\n    int build_rake(const std::vector<int>&\
    \ nodes, int l, int r) {\n        if (l == r) return -1;\n        if (l + 1 ==\
    \ r) return nodes[l];\n        int m = weighted_split(nodes, l, r);\n        return\
    \ new_rake(build_rake(nodes, l, m), build_rake(nodes, m, r));\n    }\n\n    int\
    \ build_compress(const std::vector<int>& nodes, const std::vector<edge_type>&\
    \ edges, int l, int r) {\n        if (l + 1 == r) return nodes[l];\n        int\
    \ m = weighted_split(nodes, l, r);\n        return new_compress(build_compress(nodes,\
    \ edges, l, m), build_compress(nodes, edges, m, r), edges[m - 1]);\n    }\n\n\
    \    int build_vertex(int v) {\n        std::vector<int> side_nodes;\n       \
    \ for (const auto& e : _children[v]) {\n            if (e.to == _heavy[v]) continue;\n\
    \            int child_path = build_path(e.to);\n            side_nodes.push_back(new_add_edge(child_path,\
    \ e));\n        }\n        return new_add_vertex(build_rake(side_nodes, 0, int(side_nodes.size())),\
    \ v);\n    }\n\n    int build_path(int start) {\n        std::vector<int> path_nodes;\n\
    \        std::vector<edge_type> path_edges;\n        for (int v = start; v !=\
    \ -1; v = _heavy[v]) {\n            path_nodes.push_back(build_vertex(v));\n \
    \           if (_heavy[v] != -1) path_edges.push_back(_heavy_edge[v]);\n     \
    \   }\n        return build_compress(path_nodes, path_edges, 0, int(path_nodes.size()));\n\
    \    }\n\n    void recompute_up(int node) {\n        while (node != -1) {\n  \
    \          recompute(node);\n            node = _nodes[node].parent;\n       \
    \ }\n    }\n\n   public:\n    StaticTopTree(const m1une::graph::Graph<T>& g, const\
    \ std::vector<Vertex>& values, Point point_id,\n                  Compress compress,\
    \ Rake rake, AddEdge add_edge, AddVertex add_vertex, int root = 0)\n        :\
    \ _n(g.size()),\n          _root(_n == 0 ? -1 : root),\n          _root_node(-1),\n\
    \          _point_id(std::move(point_id)),\n          _compress(std::move(compress)),\n\
    \          _rake(std::move(rake)),\n          _add_edge(std::move(add_edge)),\n\
    \          _add_vertex(std::move(add_vertex)),\n          _values(values) {\n\
    \        build(g, root);\n    }\n\n    void build(const m1une::graph::Graph<T>&\
    \ g, int root = 0) {\n        _n = g.size();\n        _root = _n == 0 ? -1 : root;\n\
    \        assert(int(_values.size()) == _n);\n        _nodes.clear();\n       \
    \ _vertex_node.assign(_n, -1);\n        _edge_node.assign(g.edge_count(), -1);\n\
    \        _parent.assign(_n, -2);\n        _subtree_size.assign(_n, 1);\n     \
    \   _heavy.assign(_n, -1);\n        _heavy_edge.assign(_n, edge_type());\n   \
    \     _children.assign(_n, {});\n        _root_node = -1;\n\n        if (_n ==\
    \ 0) return;\n        assert(0 <= root && root < _n);\n        assert(int(g.edges().size())\
    \ == _n - 1);\n\n        std::vector<int> order;\n        order.reserve(_n);\n\
    \        std::vector<int> stack = {root};\n        _parent[root] = -1;\n     \
    \   while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            order.push_back(v);\n            for (const auto& e : g[v]) {\n \
    \               if (!e.alive) continue;\n                if (_parent[e.to] !=\
    \ -2) continue;\n                _parent[e.to] = v;\n                _children[v].push_back(e);\n\
    \                stack.push_back(e.to);\n            }\n        }\n        assert(int(order.size())\
    \ == _n);\n\n        for (int i = int(order.size()) - 1; i >= 0; i--) {\n    \
    \        int v = order[i];\n            for (const auto& e : _children[v]) {\n\
    \                _subtree_size[v] += _subtree_size[e.to];\n                if\
    \ (_heavy[v] == -1 || _subtree_size[_heavy[v]] < _subtree_size[e.to]) {\n    \
    \                _heavy[v] = e.to;\n                    _heavy_edge[v] = e;\n\
    \                }\n            }\n        }\n\n        _root_node = build_path(root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int root() const {\n        return\
    \ _root;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int height() const {\n        return _root_node == -1 ? 0 : _nodes[_root_node].height;\n\
    \    }\n\n    const Vertex& get(int v) const {\n        assert(0 <= v && v < _n);\n\
    \        return _values[v];\n    }\n\n    const Vertex& operator[](int v) const\
    \ {\n        return get(v);\n    }\n\n    void set(int v, const Vertex& value)\
    \ {\n        assert(0 <= v && v < _n);\n        assert(_vertex_node[v] != -1);\n\
    \        _values[v] = value;\n        recompute_up(_vertex_node[v]);\n    }\n\n\
    \    void set(int v, Vertex&& value) {\n        assert(0 <= v && v < _n);\n  \
    \      assert(_vertex_node[v] != -1);\n        _values[v] = std::move(value);\n\
    \        recompute_up(_vertex_node[v]);\n    }\n\n    void set_edge_cost(int edge_id,\
    \ T cost) {\n        assert(0 <= edge_id && edge_id < int(_edge_node.size()));\n\
    \        int node = _edge_node[edge_id];\n        assert(node != -1);\n      \
    \  _nodes[node].edge.cost = cost;\n        recompute_up(node);\n    }\n\n    const\
    \ Path& all_prod() const {\n        assert(_root_node != -1);\n        return\
    \ path_value(_root_node);\n    }\n\n    const Path& query() const {\n        return\
    \ all_prod();\n    }\n};\n\ntemplate <class T, class Vertex, class Point, class\
    \ Compress, class Rake, class AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&,\
    \ const std::vector<Vertex>&, Point, Compress, Rake, AddEdge,\n              AddVertex,\
    \ int)\n    -> StaticTopTree<T, Vertex, std::invoke_result_t<AddVertex, Point,\
    \ Vertex, int>, Point, Compress, Rake,\n                     AddEdge, AddVertex>;\n\
    \ntemplate <class T, class Vertex, class Point, class Compress, class Rake, class\
    \ AddEdge, class AddVertex>\nStaticTopTree(const m1une::graph::Graph<T>&, const\
    \ std::vector<Vertex>&, Point, Compress, Rake, AddEdge, AddVertex)\n    -> StaticTopTree<T,\
    \ Vertex, std::invoke_result_t<AddVertex, Point, Vertex, int>, Point, Compress,\
    \ Rake,\n                     AddEdge, AddVertex>;\n\n}  // namespace tree\n}\
    \  // namespace m1une\n\n\n#line 1 \"graph/tree/tree.hpp\"\n\n\n\n#line 8 \"graph/tree/tree.hpp\"\
    \n\n\n#line 1 \"graph/tree/tree_hash.hpp\"\n\n\n\n#line 9 \"graph/tree/tree_hash.hpp\"\
    \n\n#line 11 \"graph/tree/tree_hash.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\nusing TreeHashValue = std::array<std::uint64_t, 2>;\n\nclass TreeHasher\
    \ {\n   private:\n    static constexpr std::uint64_t mod = (std::uint64_t(1) <<\
    \ 61) - 1;\n    std::uint64_t _seed;\n\n    static std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n        x += 0x9e3779b97f4a7c15ULL;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n        return x ^ (x >>\
    \ 31);\n    }\n\n    static std::uint64_t mul_mod(std::uint64_t a, std::uint64_t\
    \ b) {\n        __uint128_t product = static_cast<__uint128_t>(a) * b;\n     \
    \   std::uint64_t result = std::uint64_t(product & mod) + std::uint64_t(product\
    \ >> 61);\n        if (mod <= result) result -= mod;\n        return result;\n\
    \    }\n\n    static std::uint64_t add_mod(std::uint64_t a, std::uint64_t b) {\n\
    \        std::uint64_t result = a + b;\n        if (mod <= result) result -= mod;\n\
    \        return result;\n    }\n\n    TreeHashValue salt(int height) const {\n\
    \        std::uint64_t x = static_cast<std::uint64_t>(height);\n        std::uint64_t\
    \ first = splitmix64(_seed ^ (x + 0x243f6a8885a308d3ULL));\n        std::uint64_t\
    \ second = splitmix64(_seed ^ (x + 0x13198a2e03707344ULL));\n        return {first\
    \ % (mod - 1) + 1, second % (mod - 1) + 1};\n    }\n\n    template <class T>\n\
    \    static std::vector<int> tree_centers(const m1une::graph::Graph<T>& g) {\n\
    \        int n = g.size();\n        if (n == 0) return {};\n\n        std::vector<int>\
    \ degree(n, 0);\n        std::vector<int> queue;\n        queue.reserve(n);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) {\n                if (!e.alive) continue;\n\
    \                degree[v]++;\n                active_arcs++;\n            }\n\
    \            if (degree[v] <= 1) queue.push_back(v);\n        }\n        assert(active_arcs\
    \ == 2LL * (n - 1));\n\n        std::vector<char> removed(n, false);\n       \
    \ int remaining = n;\n        int head = 0;\n        while (2 < remaining) {\n\
    \            int layer_end = int(queue.size());\n            assert(head < layer_end);\n\
    \            remaining -= layer_end - head;\n            while (head < layer_end)\
    \ {\n                int v = queue[head++];\n                removed[v] = true;\n\
    \                for (const auto& e : g[v]) {\n                    if (!e.alive\
    \ || removed[e.to]) continue;\n                    if (--degree[e.to] == 1) queue.push_back(e.to);\n\
    \                }\n            }\n        }\n\n        std::vector<int> centers;\n\
    \        for (int v = 0; v < n; v++) {\n            if (!removed[v]) centers.push_back(v);\n\
    \        }\n        assert(1 <= int(centers.size()) && int(centers.size()) <=\
    \ 2);\n        return centers;\n    }\n\n   public:\n    explicit TreeHasher(std::uint64_t\
    \ seed = 0x6a09e667f3bcc909ULL) : _seed(seed) {}\n\n    std::uint64_t seed() const\
    \ {\n        return _seed;\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_subtrees(const m1une::graph::Graph<T>& g, int root = 0) const {\n     \
    \   int n = g.size();\n        if (n == 0) return {};\n        assert(0 <= root\
    \ && root < n);\n\n        std::vector<int> parent(n, -1);\n        std::vector<int>\
    \ order;\n        order.reserve(n);\n        parent[root] = root;\n        order.push_back(root);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) active_arcs += e.alive;\n        }\n  \
    \      assert(active_arcs == 2LL * (n - 1));\n\n        for (int i = 0; i < int(order.size());\
    \ i++) {\n            int v = order[i];\n            for (const auto& e : g[v])\
    \ {\n                if (!e.alive || parent[e.to] != -1) continue;\n         \
    \       parent[e.to] = v;\n                order.push_back(e.to);\n          \
    \  }\n        }\n        assert(int(order.size()) == n);\n\n        std::vector<int>\
    \ height(n, 0);\n        std::vector<TreeHashValue> result(n, TreeHashValue{1,\
    \ 1});\n        for (int i = n - 1; i >= 0; i--) {\n            int v = order[i];\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                height[v] = std::max(height[v], height[e.to]\
    \ + 1);\n            }\n            TreeHashValue random = salt(height[v]);\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                result[v][0] = mul_mod(result[v][0], add_mod(result[e.to][0],\
    \ random[0]));\n                result[v][1] = mul_mod(result[v][1], add_mod(result[e.to][1],\
    \ random[1]));\n            }\n        }\n        return result;\n    }\n\n  \
    \  template <class T>\n    TreeHashValue hash_rooted(const m1une::graph::Graph<T>&\
    \ g, int root = 0) const {\n        if (g.empty()) return {0, 0};\n        return\
    \ hash_subtrees(g, root)[root];\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_unrooted(const m1une::graph::Graph<T>& g) const {\n        std::vector<int>\
    \ centers = tree_centers(g);\n        std::vector<TreeHashValue> result;\n   \
    \     result.reserve(centers.size());\n        for (int center : centers) result.push_back(hash_rooted(g,\
    \ center));\n        std::sort(result.begin(), result.end());\n        return\
    \ result;\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line\
    \ 1 \"graph/tree/virtual_tree.hpp\"\n\n\n\n#line 8 \"graph/tree/virtual_tree.hpp\"\
    \n\n#line 11 \"graph/tree/virtual_tree.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\ntemplate <class T = int>\nstruct VirtualTreeResult {\n    std::vector<int>\
    \ vertex;\n    std::vector<int> parent;\n    std::vector<int> parent_edge_count;\n\
    \    std::vector<T> parent_cost;\n    std::vector<std::vector<int>> children;\n\
    \    std::vector<bool> is_key;\n\n    int size() const {\n        return int(vertex.size());\n\
    \    }\n\n    bool empty() const {\n        return vertex.empty();\n    }\n\n\
    \    int edge_count() const {\n        return vertex.empty() ? 0 : int(vertex.size())\
    \ - 1;\n    }\n\n    int root() const {\n        return vertex.empty() ? -1 :\
    \ 0;\n    }\n\n    int root_vertex() const {\n        return vertex.empty() ?\
    \ -1 : vertex[0];\n    }\n};\n\ntemplate <class T = int>\nstruct VirtualTree {\n\
    \    using cost_type = T;\n    using result_type = VirtualTreeResult<T>;\n\n \
    \  private:\n    SparseTableLca<T> _lca;\n    std::vector<int> _key;\n    std::vector<int>\
    \ _vertices;\n    std::vector<int> _stack;\n\n   public:\n    VirtualTree() =\
    \ default;\n\n    explicit VirtualTree(const m1une::graph::Graph<T>& graph, int\
    \ root = 0) : _lca(graph, root) {}\n\n    void build_lca(const m1une::graph::Graph<T>&\
    \ graph, int root = 0) {\n        _lca.build(graph, root);\n    }\n\n    int original_size()\
    \ const {\n        return _lca.size();\n    }\n\n    const SparseTableLca<T>&\
    \ lca_data() const {\n        return _lca;\n    }\n\n    result_type build(std::vector<int>\
    \ key_vertices) {\n        result_type result;\n        if (key_vertices.empty())\
    \ return result;\n\n        auto by_tin = [&](int u, int v) { return _lca.tin[u]\
    \ < _lca.tin[v]; };\n        for (int v : key_vertices) {\n            assert(0\
    \ <= v && v < _lca.size());\n            assert(_lca.tin[v] != -1);\n        }\n\
    \        std::sort(key_vertices.begin(), key_vertices.end(), by_tin);\n      \
    \  key_vertices.erase(std::unique(key_vertices.begin(), key_vertices.end()), key_vertices.end());\n\
    \n        _key = key_vertices;\n        _vertices = key_vertices;\n        _vertices.reserve(2\
    \ * _key.size());\n        for (int i = 1; i < int(_key.size()); i++) {\n    \
    \        _vertices.push_back(_lca.lca(_key[i - 1], _key[i]));\n        }\n   \
    \     std::sort(_vertices.begin(), _vertices.end(), by_tin);\n        _vertices.erase(std::unique(_vertices.begin(),\
    \ _vertices.end()), _vertices.end());\n\n        int n = int(_vertices.size());\n\
    \        result.vertex = _vertices;\n        result.parent.assign(n, -1);\n  \
    \      result.parent_edge_count.assign(n, 0);\n        result.parent_cost.assign(n,\
    \ T(0));\n        result.children.assign(n, {});\n        result.is_key.assign(n,\
    \ false);\n\n        int key_index = 0;\n        for (int i = 0; i < n; i++) {\n\
    \            while (key_index < int(_key.size()) && _lca.tin[_key[key_index]]\
    \ < _lca.tin[_vertices[i]]) {\n                key_index++;\n            }\n \
    \           if (key_index < int(_key.size()) && _key[key_index] == _vertices[i])\
    \ result.is_key[i] = true;\n        }\n\n        _stack.clear();\n        _stack.reserve(n);\n\
    \        for (int i = 0; i < n; i++) {\n            while (!_stack.empty() &&\
    \ !_lca.is_ancestor(_vertices[_stack.back()], _vertices[i])) {\n             \
    \   _stack.pop_back();\n            }\n            if (!_stack.empty()) {\n  \
    \              int p = _stack.back();\n                result.parent[i] = p;\n\
    \                result.parent_edge_count[i] = _lca.depth[_vertices[i]] - _lca.depth[_vertices[p]];\n\
    \                result.parent_cost[i] = _lca.dist[_vertices[i]] - _lca.dist[_vertices[p]];\n\
    \                result.children[p].push_back(i);\n            }\n           \
    \ _stack.push_back(i);\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n#line 1 \"graph/tree/zero_one_on_tree.hpp\"\
    \n\n\n\n#line 7 \"graph/tree/zero_one_on_tree.hpp\"\n\n#line 9 \"graph/tree/zero_one_on_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ninline long long zero_one_on_tree(const\
    \ std::vector<int>& parent,\n                                  const std::vector<int>&\
    \ value) {\n    const int n = int(parent.size());\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n\n    int root = -1;\n    std::vector<std::vector<int>>\
    \ children(n);\n    for (int v = 0; v < n; v++) {\n        assert(value[v] ==\
    \ 0 || value[v] == 1);\n        if (parent[v] == -1) {\n            assert(root\
    \ == -1);\n            root = v;\n        } else {\n            assert(0 <= parent[v]\
    \ && parent[v] < n && parent[v] != v);\n            children[parent[v]].push_back(v);\n\
    \        }\n    }\n    assert(root != -1);\n\n    std::vector<int> stack(1, root);\n\
    \    std::vector<char> visited(n, false);\n    visited[root] = true;\n    int\
    \ visited_count = 0;\n    while (!stack.empty()) {\n        const int v = stack.back();\n\
    \        stack.pop_back();\n        visited_count++;\n        for (int child :\
    \ children[v]) {\n            assert(!visited[child]);\n            visited[child]\
    \ = true;\n            stack.push_back(child);\n        }\n    }\n    assert(visited_count\
    \ == n);\n\n    struct Component {\n        long long zeros;\n        long long\
    \ ones;\n        int vertex;\n    };\n    struct Compare {\n        bool operator()(const\
    \ Component& lhs, const Component& rhs) const {\n            const long long lhs_product\
    \ = lhs.zeros * rhs.ones;\n            const long long rhs_product = rhs.zeros\
    \ * lhs.ones;\n            if (lhs_product != rhs_product) return lhs_product\
    \ < rhs_product;\n            return lhs.vertex < rhs.vertex;\n        }\n   \
    \ };\n\n    std::vector<long long> zeros(n), ones(n);\n    std::vector<int> dsu(n);\n\
    \    std::set<Component, Compare> components;\n    for (int v = 0; v < n; v++)\
    \ {\n        zeros[v] = value[v] == 0;\n        ones[v] = value[v] == 1;\n   \
    \     dsu[v] = v;\n        if (v != root) components.insert(Component{zeros[v],\
    \ ones[v], v});\n    }\n\n    auto leader = [&](int v) {\n        int result =\
    \ v;\n        while (dsu[result] != result) result = dsu[result];\n        while\
    \ (dsu[v] != v) {\n            const int next = dsu[v];\n            dsu[v] =\
    \ result;\n            v = next;\n        }\n        return result;\n    };\n\n\
    \    long long answer = 0;\n    while (!components.empty()) {\n        auto it\
    \ = components.end();\n        --it;\n        const Component child = *it;\n \
    \       components.erase(it);\n\n        const int p = leader(parent[child.vertex]);\n\
    \        if (p != root) {\n            const int erased = int(components.erase(Component{zeros[p],\
    \ ones[p], p}));\n            assert(erased == 1);\n        }\n\n        answer\
    \ += ones[p] * zeros[child.vertex];\n        zeros[p] += zeros[child.vertex];\n\
    \        ones[p] += ones[child.vertex];\n        dsu[child.vertex] = p;\n\n  \
    \      if (p != root) components.insert(Component{zeros[p], ones[p], p});\n  \
    \  }\n    return answer;\n}\n\ntemplate <class T>\nlong long zero_one_on_tree(const\
    \ m1une::graph::Graph<T>& graph,\n                           const std::vector<int>&\
    \ value, int root = 0) {\n    const int n = graph.size();\n    assert(int(value.size())\
    \ == n);\n    if (n == 0) return 0;\n    assert(0 <= root && root < n);\n    assert(int(graph.edges().size())\
    \ == n - 1);\n\n    RootedTree<T> rooted_tree(graph, root);\n    assert(int(rooted_tree.order.size())\
    \ == n);\n    return zero_one_on_tree(rooted_tree.parent, value);\n}\n\n}  //\
    \ namespace tree\n}  // namespace m1une\n\n\n#line 21 \"graph/tree/all.hpp\"\n\
    \n\n#line 14 \"verify/graph/tree/tree_algorithms.test.cpp\"\n\nusing m1une::graph::Graph;\n\
    \ntemplate <class Hld>\nstd::vector<int> expand_segments(const Hld& hld, const\
    \ std::vector<m1une::tree::HldPathSegment>& segments) {\n    std::vector<int>\
    \ result;\n    for (auto seg : segments) {\n        if (seg.reversed) {\n    \
    \        for (int i = seg.r - 1; i >= seg.l; i--) result.push_back(hld.order[i]);\n\
    \        } else {\n            for (int i = seg.l; i < seg.r; i++) result.push_back(hld.order[i]);\n\
    \        }\n    }\n    return result;\n}\n\nGraph<long long> sample_tree() {\n\
    \    Graph<long long> g(7);\n    g.add_edge(0, 1, 3);\n    g.add_edge(0, 2, 2);\n\
    \    g.add_edge(1, 3, 4);\n    g.add_edge(1, 4, 1);\n    g.add_edge(2, 5, 6);\n\
    \    g.add_edge(5, 6, 2);\n    return g;\n}\n\nvoid test_rooted_tree() {\n   \
    \ auto g = sample_tree();\n    m1une::tree::RootedTree<long long> tree(g, 0);\n\
    \n    assert(tree.size() == 7);\n    assert(!tree.empty());\n    assert(tree.root\
    \ == 0);\n    assert(tree.parent[0] == -1);\n    assert(tree.parent[3] == 1);\n\
    \    assert(tree.depth[6] == 3);\n    assert(tree.dist[6] == 10);\n    assert(tree.subtree_size[0]\
    \ == 7);\n    assert(tree.subtree_size[1] == 3);\n    assert(tree.is_ancestor(1,\
    \ 4));\n    assert(!tree.is_ancestor(2, 4));\n    assert(tree.in_subtree(4, 1));\n\
    \n    assert(tree.kth_ancestor(6, 0) == 6);\n    assert(tree.kth_ancestor(6, 1)\
    \ == 5);\n    assert(tree.kth_ancestor(6, 3) == 0);\n    assert(tree.kth_ancestor(6,\
    \ 4) == -1);\n    assert(tree.lca(3, 4) == 1);\n    assert(tree.lca(3, 6) == 0);\n\
    \    assert(tree.dist_edges(3, 6) == 5);\n    assert(tree.dist_cost(3, 6) == 17);\n\
    \    assert(tree.jump(3, 6, 0) == 3);\n    assert(tree.jump(3, 6, 1) == 1);\n\
    \    assert(tree.jump(3, 6, 2) == 0);\n    assert(tree.jump(3, 6, 3) == 2);\n\
    \    assert(tree.jump(3, 6, 5) == 6);\n    assert(tree.jump(3, 6, 6) == -1);\n\
    \n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n    assert(tree.path(3,\
    \ 6) == expected_path);\n    std::vector<int> expected_edges = {2, 0, 1, 4, 5};\n\
    \    assert(tree.path_edges(3, 6) == expected_edges);\n\n    auto [l, r] = tree.subtree_range(1);\n\
    \    assert(r - l == 3);\n    auto sub = tree.subtree_vertices(1);\n    std::sort(sub.begin(),\
    \ sub.end());\n    assert((sub == std::vector<int>{1, 3, 4}));\n}\n\nvoid test_euler_tour()\
    \ {\n    auto g = sample_tree();\n    m1une::tree::EulerTour<long long> tour(g,\
    \ 0);\n\n    std::vector<int> expected_order = {0, 1, 3, 4, 2, 5, 6};\n    assert(tour.size()\
    \ == 7);\n    assert(tour.visited_size() == 7);\n    assert(tour.root == 0);\n\
    \    assert(tour.order == expected_order);\n    assert(tour.parent[6] == 5);\n\
    \    assert(tour.parent_edge[6] == 5);\n    assert(tour.depth[6] == 3);\n    assert(tour.dist[6]\
    \ == 10);\n    assert(tour.subtree_size[1] == 3);\n    assert(tour.is_ancestor(1,\
    \ 4));\n    assert(!tour.is_ancestor(2, 4));\n\n    auto [l, r] = tour.subtree_range(1);\n\
    \    assert(l == 1);\n    assert(r == 4);\n    auto [el, er] = tour.subtree_range(1,\
    \ true);\n    assert(el == 2);\n    assert(er == 4);\n\n    std::vector<int> subtree\
    \ = tour.subtree_vertices(1);\n    std::sort(subtree.begin(), subtree.end());\n\
    \    std::vector<int> expected_subtree = {1, 3, 4};\n    assert(subtree == expected_subtree);\n\
    }\n\nvoid test_sparse_table_lca() {\n    auto g = sample_tree();\n    m1une::tree::RootedTree<long\
    \ long> tree(g, 0);\n    m1une::tree::SparseTableLca<long long> lca(g, 0);\n\n\
    \    assert(lca.size() == 7);\n    assert(!lca.empty());\n    assert(lca.root\
    \ == 0);\n    assert(lca.parent[0] == -1);\n    assert(lca.parent[6] == 5);\n\
    \    assert(lca.depth[6] == 3);\n    assert(lca.dist[6] == 10);\n    assert(lca.euler.size()\
    \ == 13);\n    assert(lca.first[0] == 0);\n    assert(lca.is_ancestor(2, 6));\n\
    \    assert(!lca.is_ancestor(1, 6));\n    assert(lca.in_subtree(6, 2));\n\n  \
    \  for (int u = 0; u < 7; u++) {\n        for (int v = 0; v < 7; v++) {\n    \
    \        assert(lca.lca(u, v) == tree.lca(u, v));\n            assert(lca.dist_edges(u,\
    \ v) == tree.dist_edges(u, v));\n            assert(lca.dist_cost(u, v) == tree.dist_cost(u,\
    \ v));\n        }\n    }\n\n    auto [l, r] = lca.subtree_range(2);\n    assert(r\
    \ - l == 3);\n    std::vector<int> subtree;\n    for (int i = l; i < r; i++) subtree.push_back(lca.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{2,\
    \ 5, 6}));\n}\n\nvoid test_virtual_tree() {\n    auto graph = sample_tree();\n\
    \    m1une::tree::VirtualTree<long long> builder(graph, 0);\n\n    auto virtual_tree\
    \ = builder.build(std::vector<int>{3, 4, 6, 3});\n    std::vector<int> expected_vertices\
    \ = {0, 1, 3, 4, 6};\n    assert(virtual_tree.vertex == expected_vertices);\n\
    \    assert(virtual_tree.parent == std::vector<int>({-1, 0, 1, 1, 0}));\n    assert(virtual_tree.parent_edge_count\
    \ == std::vector<int>({0, 1, 1, 1, 3}));\n    assert(virtual_tree.parent_cost\
    \ == std::vector<long long>({0, 3, 4, 1, 10}));\n    assert(virtual_tree.is_key\
    \ == std::vector<bool>({false, false, true, true, true}));\n    assert(virtual_tree.children[0]\
    \ == std::vector<int>({1, 4}));\n    assert(virtual_tree.children[1] == std::vector<int>({2,\
    \ 3}));\n    assert(virtual_tree.root() == 0);\n    assert(virtual_tree.root_vertex()\
    \ == 0);\n    assert(virtual_tree.edge_count() == 4);\n\n    auto singleton =\
    \ builder.build(std::vector<int>{5, 5});\n    assert(singleton.size() == 1);\n\
    \    assert(singleton.vertex[0] == 5);\n    assert(singleton.parent[0] == -1);\n\
    \    assert(singleton.is_key[0]);\n\n    auto empty = builder.build({});\n   \
    \ assert(empty.empty());\n    assert(empty.root() == -1);\n    assert(empty.root_vertex()\
    \ == -1);\n    assert(empty.edge_count() == 0);\n\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 100; test++) {\n        int n = 1 + random() %\
    \ 200;\n        Graph<long long> random_graph(n);\n        for (int v = 1; v <\
    \ n; v++) {\n            int parent = random() % v;\n            long long cost\
    \ = 1 + random() % 1000000;\n            random_graph.add_edge(parent, v, cost);\n\
    \        }\n        m1une::tree::VirtualTree<long long> random_builder(random_graph,\
    \ 0);\n        const auto& lca = random_builder.lca_data();\n        for (int\
    \ query = 0; query < 100; query++) {\n            int k = random() % (2 * n +\
    \ 1);\n            std::vector<int> keys(k);\n            for (int& v : keys)\
    \ v = random() % n;\n            auto result = random_builder.build(keys);\n\n\
    \            std::sort(keys.begin(), keys.end(), [&](int u, int v) {\n       \
    \         return lca.tin[u] < lca.tin[v];\n            });\n            keys.erase(std::unique(keys.begin(),\
    \ keys.end()), keys.end());\n            std::vector<int> expected = keys;\n \
    \           for (int i = 1; i < int(keys.size()); i++) expected.push_back(lca.lca(keys[i\
    \ - 1], keys[i]));\n            std::sort(expected.begin(), expected.end(), [&](int\
    \ u, int v) {\n                return lca.tin[u] < lca.tin[v];\n            });\n\
    \            expected.erase(std::unique(expected.begin(), expected.end()), expected.end());\n\
    \            assert(result.vertex == expected);\n\n            int key_index =\
    \ 0;\n            for (int i = 0; i < result.size(); i++) {\n                while\
    \ (key_index < int(keys.size()) && lca.tin[keys[key_index]] < lca.tin[result.vertex[i]])\
    \ {\n                    key_index++;\n                }\n                bool\
    \ is_key = key_index < int(keys.size()) && keys[key_index] == result.vertex[i];\n\
    \                assert(result.is_key[i] == is_key);\n                if (i ==\
    \ 0) {\n                    assert(result.parent[i] == -1);\n                \
    \    continue;\n                }\n                int parent = result.parent[i];\n\
    \                assert(0 <= parent && parent < i);\n                assert(lca.is_ancestor(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_edge_count[i] == lca.dist_edges(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_cost[i] == lca.dist_cost(result.vertex[parent],\
    \ result.vertex[i]));\n                for (int j = parent + 1; j < i; j++) {\n\
    \                    assert(!lca.is_ancestor(result.vertex[j], result.vertex[i]));\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid test_hld() {\n\
    \    auto g = sample_tree();\n    m1une::tree::HeavyLightDecomposition<long long>\
    \ hld(g, 0);\n\n    assert(hld.size() == 7);\n    assert(hld.root == 0);\n   \
    \ assert(hld.lca(3, 4) == 1);\n    assert(hld.lca(3, 6) == 0);\n    assert(hld.dist_edges(3,\
    \ 6) == 5);\n    assert(hld.dist_cost(3, 6) == 17);\n    assert(hld.kth_ancestor(6,\
    \ 2) == 2);\n    assert(hld.kth_ancestor(6, 4) == -1);\n    assert(hld.jump(3,\
    \ 6, 4) == 5);\n\n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n \
    \   assert(expand_segments(hld, hld.path_segments(3, 6)) == expected_path);\n\
    \    std::vector<int> expected_edge_vertices = {3, 1, 2, 5, 6};\n    assert(expand_segments(hld,\
    \ hld.path_segments(3, 6, true)) == expected_edge_vertices);\n\n    int segment_count\
    \ = 0;\n    hld.for_each_path(3, 6, [&](int l, int r, bool) {\n        assert(l\
    \ < r);\n        segment_count++;\n    });\n    assert(segment_count == int(hld.path_segments(3,\
    \ 6).size()));\n\n    auto [vl, vr] = hld.subtree_range(1);\n    std::vector<int>\
    \ subtree;\n    for (int i = vl; i < vr; i++) subtree.push_back(hld.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{1,\
    \ 3, 4}));\n\n    auto [el, er] = hld.subtree_range(1, true);\n    std::vector<int>\
    \ edge_subtree;\n    for (int i = el; i < er; i++) edge_subtree.push_back(hld.order[i]);\n\
    \    std::sort(edge_subtree.begin(), edge_subtree.end());\n    assert((edge_subtree\
    \ == std::vector<int>{3, 4}));\n}\n\nvoid test_diameter() {\n    auto g = sample_tree();\n\
    \    auto diameter = m1une::tree::tree_diameter(g);\n\n    assert(!diameter.empty());\n\
    \    assert(diameter.cost == 17);\n    assert(diameter.edge_count == 5);\n   \
    \ assert(diameter.from == diameter.vertices.front());\n    assert(diameter.to\
    \ == diameter.vertices.back());\n    std::set<int> endpoints = {diameter.from,\
    \ diameter.to};\n    assert((endpoints == std::set<int>{3, 6}));\n\n    g.erase_edge(1);\n\
    \    auto split = m1une::tree::tree_diameter(g);\n    assert(split.cost == 8);\n\
    \    assert(split.edge_count == 2);\n}\n\nvoid test_rerooting() {\n    auto g\
    \ = sample_tree();\n    auto component_size = m1une::tree::rerooting_dp(\n   \
    \     g,\n        0,\n        [](int a, int b) { return a + b; },\n        [](int\
    \ acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return dp;\
    \ });\n    assert(component_size == std::vector<int>(7, 7));\n\n    auto eccentricity_edges\
    \ = m1une::tree::rerooting_dp(\n        g,\n        0,\n        [](int a, int\
    \ b) { return std::max(a, b); },\n        [](int acc, int) { return acc; },\n\
    \        [](int dp, const auto&) { return dp + 1; });\n    assert(eccentricity_edges[0]\
    \ == 3);\n    assert(eccentricity_edges[3] == 5);\n    assert(eccentricity_edges[6]\
    \ == 5);\n\n    auto eccentricity_cost = m1une::tree::rerooting_dp(\n        g,\n\
    \        0LL,\n        [](long long a, long long b) { return std::max(a, b); },\n\
    \        [](long long acc, int) { return acc; },\n        [](long long dp, const\
    \ auto& e) { return dp + e.cost; });\n    assert(eccentricity_cost[0] == 10);\n\
    \    assert(eccentricity_cost[3] == 17);\n    assert(eccentricity_cost[6] == 17);\n\
    }\n\nstruct DistancePath {\n    long long count;\n    long long sum;\n    long\
    \ long length;\n};\n\nstruct DistancePoint {\n    long long count;\n    long long\
    \ sum;\n};\n\nstruct ColorVertex {\n    long long weight;\n    int color;\n};\n\
    \nstruct ColorPath {\n    int first_color;\n    int last_color;\n    long long\
    \ first_sum;\n    long long last_sum;\n    bool connected;\n};\n\nstruct ColorPoint\
    \ {\n    std::array<long long, 2> sum;\n};\n\nvoid test_static_top_tree() {\n\
    \    auto g = sample_tree();\n    std::vector<long long> values = {1, 2, 3, 4,\
    \ 5, 6, 7};\n\n    auto vertex_sum = m1une::tree::StaticTopTree(\n        g,\n\
    \        values,\n        0LL,\n        [](long long top, long long bottom, const\
    \ auto&) {\n            return top + bottom;\n        },\n        [](long long\
    \ a, long long b) {\n            return a + b;\n        },\n        [](long long\
    \ path, const auto&) {\n            return path;\n        },\n        [](long\
    \ long side, long long value, int) {\n            return side + value;\n     \
    \   });\n\n    assert(vertex_sum.size() == 7);\n    assert(vertex_sum.root() ==\
    \ 0);\n    assert(vertex_sum.all_prod() == 28);\n    assert(vertex_sum.query()\
    \ == 28);\n    assert(vertex_sum.get(3) == 4);\n    assert(vertex_sum.height()\
    \ > 0);\n    vertex_sum.set(3, 100);\n    assert(vertex_sum[3] == 100);\n    assert(vertex_sum.all_prod()\
    \ == 124);\n\n    auto root_distance_sum = m1une::tree::StaticTopTree(\n     \
    \   g,\n        std::vector<int>(7, 0),\n        DistancePoint{0, 0},\n      \
    \  [](DistancePath top, DistancePath bottom, const auto& e) {\n            long\
    \ long shift = top.length + e.cost;\n            return DistancePath{top.count\
    \ + bottom.count, top.sum + bottom.sum + bottom.count * shift,\n             \
    \                   top.length + e.cost + bottom.length};\n        },\n      \
    \  [](DistancePoint a, DistancePoint b) {\n            return DistancePoint{a.count\
    \ + b.count, a.sum + b.sum};\n        },\n        [](DistancePath path, const\
    \ auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, int, int) {\n       \
    \     return DistancePath{side.count + 1, side.sum, 0};\n        });\n\n    assert(root_distance_sum.all_prod().count\
    \ == 7);\n    assert(root_distance_sum.all_prod().sum == 34);\n    root_distance_sum.set_edge_cost(0,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 55);\n    root_distance_sum.set_edge_cost(1,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 79);\n}\n\nvoid test_rerooting_static_top_tree()\
    \ {\n    Graph<long long> g(3);\n    int e01 = g.add_edge(0, 1, 2);\n    int e12\
    \ = g.add_edge(1, 2, 5);\n    std::vector<long long> weights = {1, 1, 1};\n\n\
    \    auto stt = m1une::tree::RerootingStaticTopTree(\n        g,\n        weights,\n\
    \        DistancePoint{0, 0},\n        [](DistancePath upper, DistancePath lower,\
    \ const auto& e) {\n            long long shift = upper.length + e.cost;\n   \
    \         return DistancePath{upper.count + lower.count, upper.sum + lower.sum\
    \ + lower.count * shift,\n                                upper.length + e.cost\
    \ + lower.length};\n        },\n        [](DistancePath lower, DistancePath upper,\
    \ const auto& e) {\n            long long shift = lower.length + e.cost;\n   \
    \         return DistancePath{lower.count + upper.count, lower.sum + upper.sum\
    \ + upper.count * shift,\n                                lower.length + e.cost\
    \ + upper.length};\n        },\n        [](DistancePoint a, DistancePoint b) {\n\
    \            return DistancePoint{a.count + b.count, a.sum + b.sum};\n       \
    \ },\n        [](DistancePath path, const auto& e) {\n            return DistancePoint{path.count,\
    \ path.sum + path.count * e.cost};\n        },\n        [](DistancePath path,\
    \ const auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, long long weight, int)\
    \ {\n            return DistancePath{side.count + weight, side.sum, 0};\n    \
    \    });\n\n    assert(stt.size() == 3);\n    assert(stt.root() == 0);\n    assert(stt.node_count()\
    \ >= 3);\n    assert(stt.height() > 0);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 9);\n    assert(stt.all_prod_down().length\
    \ == 7);\n    assert(stt.all_prod_up().count == 3);\n    assert(stt.all_prod_up().sum\
    \ == 12);\n    assert(stt.all_prod_up().length == 7);\n\n    int root_node = stt.root_node();\n\
    \    assert(stt.path_down(root_node).sum == stt.all_prod_down().sum);\n    assert(stt.path_up(root_node).sum\
    \ == stt.all_prod_up().sum);\n    int one_node = stt.vertex_node(1);\n    assert(stt.node(one_node).type\
    \ == m1une::tree::internal::RerootingStaticTopTreeNodeType::AddVertex);\n    assert(stt.parent_node(root_node)\
    \ == -1);\n    assert(stt.point_id().count == 0);\n    assert(stt.local_point_node(1)\
    \ == -1);\n    assert(stt.local_point(1).count == 0);\n\n    using RerootingStepType\
    \ = decltype(stt)::step_type;\n    using RerootingNodeType = decltype(stt)::node_type;\n\
    \    auto steps = stt.rerooting_steps(1);\n    std::vector<decltype(stt)::RerootingStep>\
    \ streamed_steps;\n    stt.for_each_rerooting_step(1, [&](const auto& step) {\n\
    \        streamed_steps.push_back(step);\n    });\n    assert(streamed_steps.size()\
    \ == steps.size());\n    int cur = one_node;\n    for (int i = 0; i < int(steps.size());\
    \ i++) {\n        const auto& step = steps[i];\n        const auto& streamed =\
    \ streamed_steps[i];\n        assert(streamed.type == step.type);\n        assert(streamed.node\
    \ == step.node);\n        assert(streamed.sibling == step.sibling);\n        assert(streamed.vertex\
    \ == step.vertex);\n        assert(streamed.edge.from == step.edge.from);\n  \
    \      assert(streamed.edge.to == step.edge.to);\n        assert(streamed.edge.id\
    \ == step.edge.id);\n\n        assert(stt.parent_node(cur) == step.node);\n  \
    \      const auto& parent = stt.node(step.node);\n        if (step.type == RerootingStepType::CompressLower)\
    \ {\n            assert(parent.type == RerootingNodeType::Compress);\n       \
    \     assert(parent.left == cur);\n            assert(parent.right == step.sibling);\n\
    \            assert(stt.node(step.sibling).path_down.has_value());\n        }\
    \ else if (step.type == RerootingStepType::CompressUpper) {\n            assert(parent.type\
    \ == RerootingNodeType::Compress);\n            assert(parent.right == cur);\n\
    \            assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).path_up.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeLeft) {\n            assert(parent.type\
    \ == RerootingNodeType::Rake);\n            assert(parent.right == cur);\n   \
    \         assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeRight) {\n           \
    \ assert(parent.type == RerootingNodeType::Rake);\n            assert(parent.left\
    \ == cur);\n            assert(parent.right == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::AddEdge) {\n            assert(parent.type\
    \ == RerootingNodeType::AddEdge);\n            assert(parent.left == cur);\n \
    \       } else {\n            assert(step.type == RerootingStepType::AddVertex);\n\
    \            assert(parent.type == RerootingNodeType::AddVertex);\n          \
    \  assert(parent.left == cur);\n            assert(parent.vertex == step.vertex);\n\
    \        }\n        cur = step.node;\n    }\n    assert(cur == stt.root_node());\n\
    \n    auto edge = m1une::graph::Edge<long long>(0, 1, 2, e01);\n    auto reversed\
    \ = decltype(stt)::reverse_edge(edge);\n    assert(reversed.from == 1);\n    assert(reversed.to\
    \ == 0);\n    DistancePath one = stt.add_vertex(stt.point_id(), 1LL, 0);\n   \
    \ assert(one.count == 1);\n    assert(one.sum == 0);\n    auto down_point = stt.add_edge_down(one,\
    \ edge);\n    auto up_point = stt.add_edge_up(one, reversed);\n    assert(down_point.sum\
    \ == 2);\n    assert(up_point.sum == 2);\n    auto raked = stt.rake(down_point,\
    \ up_point);\n    assert(raked.count == 2);\n    assert(raked.sum == 4);\n   \
    \ assert(stt.compress_down(one, one, edge).sum == 2);\n    assert(stt.compress_up(one,\
    \ one, reversed).sum == 2);\n\n    stt.set_edge_cost(e01, 10);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_down().length\
    \ == 15);\n    assert(stt.all_prod_up().sum == 20);\n    assert(stt.all_prod_up().length\
    \ == 15);\n\n    stt.set(0, 3);\n    assert(stt[0] == 3);\n    assert(stt.all_prod_down().count\
    \ == 5);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_up().count\
    \ == 5);\n    assert(stt.all_prod_up().sum == 50);\n\n    stt.set_edge_cost(e12,\
    \ 1);\n    assert(stt.all_prod_down().sum == 21);\n    assert(stt.all_prod_up().sum\
    \ == 34);\n}\n\nvoid test_rerooting_static_top_tree_vertex_component() {\n   \
    \ auto g = sample_tree();\n    std::vector<ColorVertex> values = {\n        ColorVertex{1,\
    \ 0},      ColorVertex{10, 0},     ColorVertex{100, 1},    ColorVertex{1000, 0},\n\
    \        ColorVertex{10000, 1},  ColorVertex{100000, 1}, ColorVertex{1000000,\
    \ 1},\n    };\n\n    auto compress = [](ColorPath a, ColorPath b, const auto&)\
    \ {\n        bool join = a.last_color == b.first_color;\n        ColorPath res{a.first_color,\
    \ b.last_color, a.first_sum, b.last_sum, false};\n        if (join && a.connected)\
    \ res.first_sum += b.first_sum;\n        if (join && b.connected) res.last_sum\
    \ += a.last_sum;\n        res.connected = a.connected && b.connected && join;\n\
    \        return res;\n    };\n    auto rake = [](ColorPoint a, ColorPoint b) {\n\
    \        return ColorPoint{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]};\n    };\n\
    \    auto add_edge = [](ColorPath path, const auto&) {\n        ColorPoint res{};\n\
    \        res.sum[path.first_color] = path.first_sum;\n        return res;\n  \
    \  };\n    auto add_vertex = [](ColorPoint side, ColorVertex value, int) {\n \
    \       long long sum = value.weight + side.sum[value.color];\n        return\
    \ ColorPath{value.color, value.color, sum, sum, true};\n    };\n\n    auto stt\
    \ = m1une::tree::RerootingStaticTopTree(\n        g, values, ColorPoint{0, 0},\
    \ compress, compress, rake, add_edge, add_edge, add_vertex);\n\n    using ColorStt\
    \ = decltype(stt);\n    struct QueryFolder {\n        const ColorStt& stt;\n \
    \       const std::vector<ColorVertex>& values;\n        int color = 0;\n    \
    \    long long answer = 0;\n        bool touches_top = false;\n        bool touches_bottom\
    \ = false;\n        bool pending_open = false;\n        ColorPoint pending{};\n\
    \n        void start(int v, const ColorVertex& value, const ColorPoint& local)\
    \ {\n            color = value.color;\n            answer = value.weight + local.sum[color];\n\
    \            touches_top = true;\n            touches_bottom = true;\n       \
    \     pending_open = false;\n            pending = stt.point_id();\n         \
    \   assert(values[v].color == color);\n        }\n\n        void compress_lower(const\
    \ ColorPath& lower, ColorStt::edge_type) {\n            bool connect = touches_bottom\
    \ && lower.first_color == color;\n            if (connect) answer += lower.first_sum;\n\
    \            touches_bottom = connect && lower.connected;\n        }\n\n     \
    \   void compress_upper(const ColorPath& upper, ColorStt::edge_type) {\n     \
    \       bool connect = touches_top && upper.first_color == color;\n          \
    \  if (connect) answer += upper.first_sum;\n            touches_top = connect\
    \ && upper.connected;\n        }\n\n        void add_edge(ColorStt::edge_type)\
    \ {\n            pending_open = touches_top;\n            pending = stt.point_id();\n\
    \        }\n\n        void rake_left(const ColorPoint& point) {\n            if\
    \ (pending_open) pending = stt.rake(point, pending);\n        }\n\n        void\
    \ rake_right(const ColorPoint& point) {\n            if (pending_open) pending\
    \ = stt.rake(pending, point);\n        }\n\n        void add_vertex(int, const\
    \ ColorVertex& value) {\n            if (pending_open && value.color == color)\
    \ {\n                answer += value.weight + pending.sum[color];\n          \
    \      touches_top = true;\n                touches_bottom = true;\n         \
    \   } else {\n                touches_top = false;\n                touches_bottom\
    \ = false;\n            }\n            pending_open = false;\n            pending\
    \ = stt.point_id();\n        }\n\n        long long result() const {\n       \
    \     return answer;\n        }\n    };\n\n    auto query = [&](int v) {\n   \
    \     return stt.fold_rerooting(v, QueryFolder{stt, values});\n    };\n\n    auto\
    \ brute = [&](int start) {\n        int color = values[start].color;\n       \
    \ long long answer = 0;\n        std::vector<char> seen(g.size(), false);\n  \
    \      std::vector<int> stack = {start};\n        seen[start] = true;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            answer += values[v].weight;\n            for (const auto& e : g[v])\
    \ {\n                if (seen[e.to] || values[e.to].color != color) continue;\n\
    \                seen[e.to] = true;\n                stack.push_back(e.to);\n\
    \            }\n        }\n        return answer;\n    };\n\n    auto check_all\
    \ = [&]() {\n        for (int v = 0; v < g.size(); v++) assert(query(v) == brute(v));\n\
    \    };\n\n    check_all();\n    values[2].color ^= 1;\n    stt.set(2, values[2]);\n\
    \    check_all();\n    values[5].weight += 7;\n    stt.set(5, values[5]);\n  \
    \  check_all();\n    values[1].color ^= 1;\n    stt.set(1, values[1]);\n    check_all();\n\
    \    values[4].weight += 11;\n    stt.set(4, values[4]);\n    check_all();\n}\n\
    \nvoid test_centroid_decomposition() {\n    auto g = sample_tree();\n    m1une::tree::CentroidDecomposition<long\
    \ long> cd(g);\n\n    assert(cd.size() == 7);\n    assert(!cd.empty());\n    assert(cd.root()\
    \ == 0);\n    assert(cd.roots == std::vector<int>{0});\n    assert(cd.parent[cd.root()]\
    \ == -1);\n    assert(cd.depth[cd.root()] == 0);\n    assert(cd.order.size() ==\
    \ 7);\n\n    int child_count = 0;\n    for (const auto& ch : cd.children) child_count\
    \ += int(ch.size());\n    assert(child_count == 6);\n    for (int v = 0; v < 7;\
    \ v++) {\n        if (v == cd.root()) continue;\n        assert(cd.parent[v] !=\
    \ -1);\n        assert(cd.depth[v] == cd.depth[cd.parent[v]] + 1);\n    }\n}\n\
    \nvoid test_forest() {\n    Graph<int> g(4);\n    g.add_edge(0, 1, 5);\n    g.add_edge(2,\
    \ 3, 7);\n\n    auto diameter = m1une::tree::tree_diameter(g);\n    assert(diameter.cost\
    \ == 7);\n    assert(diameter.edge_count == 1);\n\n    auto component_size = m1une::tree::rerooting_dp(\n\
    \        g,\n        0,\n        [](int a, int b) { return a + b; },\n       \
    \ [](int acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return\
    \ dp; });\n    assert(component_size == std::vector<int>(4, 2));\n\n    m1une::tree::CentroidDecomposition<int>\
    \ cd(g);\n    assert(cd.roots.size() == 2);\n    assert(cd.order.size() == 4);\n\
    }\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_rooted_tree();\n    test_euler_tour();\n    test_sparse_table_lca();\n\
    \    test_virtual_tree();\n    test_hld();\n    test_diameter();\n    test_rerooting();\n\
    \    test_static_top_tree();\n    test_rerooting_static_top_tree();\n    test_rerooting_static_top_tree_vertex_component();\n\
    \    test_centroid_decomposition();\n    test_forest();\n\n    long long a = 0,\
    \ b = 0;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <numeric>\n#include <random>\n#include <set>\n#include <vector>\n\n\
    #include \"../../../graph/graph.hpp\"\n#include \"../../../graph/tree/all.hpp\"\
    \n\nusing m1une::graph::Graph;\n\ntemplate <class Hld>\nstd::vector<int> expand_segments(const\
    \ Hld& hld, const std::vector<m1une::tree::HldPathSegment>& segments) {\n    std::vector<int>\
    \ result;\n    for (auto seg : segments) {\n        if (seg.reversed) {\n    \
    \        for (int i = seg.r - 1; i >= seg.l; i--) result.push_back(hld.order[i]);\n\
    \        } else {\n            for (int i = seg.l; i < seg.r; i++) result.push_back(hld.order[i]);\n\
    \        }\n    }\n    return result;\n}\n\nGraph<long long> sample_tree() {\n\
    \    Graph<long long> g(7);\n    g.add_edge(0, 1, 3);\n    g.add_edge(0, 2, 2);\n\
    \    g.add_edge(1, 3, 4);\n    g.add_edge(1, 4, 1);\n    g.add_edge(2, 5, 6);\n\
    \    g.add_edge(5, 6, 2);\n    return g;\n}\n\nvoid test_rooted_tree() {\n   \
    \ auto g = sample_tree();\n    m1une::tree::RootedTree<long long> tree(g, 0);\n\
    \n    assert(tree.size() == 7);\n    assert(!tree.empty());\n    assert(tree.root\
    \ == 0);\n    assert(tree.parent[0] == -1);\n    assert(tree.parent[3] == 1);\n\
    \    assert(tree.depth[6] == 3);\n    assert(tree.dist[6] == 10);\n    assert(tree.subtree_size[0]\
    \ == 7);\n    assert(tree.subtree_size[1] == 3);\n    assert(tree.is_ancestor(1,\
    \ 4));\n    assert(!tree.is_ancestor(2, 4));\n    assert(tree.in_subtree(4, 1));\n\
    \n    assert(tree.kth_ancestor(6, 0) == 6);\n    assert(tree.kth_ancestor(6, 1)\
    \ == 5);\n    assert(tree.kth_ancestor(6, 3) == 0);\n    assert(tree.kth_ancestor(6,\
    \ 4) == -1);\n    assert(tree.lca(3, 4) == 1);\n    assert(tree.lca(3, 6) == 0);\n\
    \    assert(tree.dist_edges(3, 6) == 5);\n    assert(tree.dist_cost(3, 6) == 17);\n\
    \    assert(tree.jump(3, 6, 0) == 3);\n    assert(tree.jump(3, 6, 1) == 1);\n\
    \    assert(tree.jump(3, 6, 2) == 0);\n    assert(tree.jump(3, 6, 3) == 2);\n\
    \    assert(tree.jump(3, 6, 5) == 6);\n    assert(tree.jump(3, 6, 6) == -1);\n\
    \n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n    assert(tree.path(3,\
    \ 6) == expected_path);\n    std::vector<int> expected_edges = {2, 0, 1, 4, 5};\n\
    \    assert(tree.path_edges(3, 6) == expected_edges);\n\n    auto [l, r] = tree.subtree_range(1);\n\
    \    assert(r - l == 3);\n    auto sub = tree.subtree_vertices(1);\n    std::sort(sub.begin(),\
    \ sub.end());\n    assert((sub == std::vector<int>{1, 3, 4}));\n}\n\nvoid test_euler_tour()\
    \ {\n    auto g = sample_tree();\n    m1une::tree::EulerTour<long long> tour(g,\
    \ 0);\n\n    std::vector<int> expected_order = {0, 1, 3, 4, 2, 5, 6};\n    assert(tour.size()\
    \ == 7);\n    assert(tour.visited_size() == 7);\n    assert(tour.root == 0);\n\
    \    assert(tour.order == expected_order);\n    assert(tour.parent[6] == 5);\n\
    \    assert(tour.parent_edge[6] == 5);\n    assert(tour.depth[6] == 3);\n    assert(tour.dist[6]\
    \ == 10);\n    assert(tour.subtree_size[1] == 3);\n    assert(tour.is_ancestor(1,\
    \ 4));\n    assert(!tour.is_ancestor(2, 4));\n\n    auto [l, r] = tour.subtree_range(1);\n\
    \    assert(l == 1);\n    assert(r == 4);\n    auto [el, er] = tour.subtree_range(1,\
    \ true);\n    assert(el == 2);\n    assert(er == 4);\n\n    std::vector<int> subtree\
    \ = tour.subtree_vertices(1);\n    std::sort(subtree.begin(), subtree.end());\n\
    \    std::vector<int> expected_subtree = {1, 3, 4};\n    assert(subtree == expected_subtree);\n\
    }\n\nvoid test_sparse_table_lca() {\n    auto g = sample_tree();\n    m1une::tree::RootedTree<long\
    \ long> tree(g, 0);\n    m1une::tree::SparseTableLca<long long> lca(g, 0);\n\n\
    \    assert(lca.size() == 7);\n    assert(!lca.empty());\n    assert(lca.root\
    \ == 0);\n    assert(lca.parent[0] == -1);\n    assert(lca.parent[6] == 5);\n\
    \    assert(lca.depth[6] == 3);\n    assert(lca.dist[6] == 10);\n    assert(lca.euler.size()\
    \ == 13);\n    assert(lca.first[0] == 0);\n    assert(lca.is_ancestor(2, 6));\n\
    \    assert(!lca.is_ancestor(1, 6));\n    assert(lca.in_subtree(6, 2));\n\n  \
    \  for (int u = 0; u < 7; u++) {\n        for (int v = 0; v < 7; v++) {\n    \
    \        assert(lca.lca(u, v) == tree.lca(u, v));\n            assert(lca.dist_edges(u,\
    \ v) == tree.dist_edges(u, v));\n            assert(lca.dist_cost(u, v) == tree.dist_cost(u,\
    \ v));\n        }\n    }\n\n    auto [l, r] = lca.subtree_range(2);\n    assert(r\
    \ - l == 3);\n    std::vector<int> subtree;\n    for (int i = l; i < r; i++) subtree.push_back(lca.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{2,\
    \ 5, 6}));\n}\n\nvoid test_virtual_tree() {\n    auto graph = sample_tree();\n\
    \    m1une::tree::VirtualTree<long long> builder(graph, 0);\n\n    auto virtual_tree\
    \ = builder.build(std::vector<int>{3, 4, 6, 3});\n    std::vector<int> expected_vertices\
    \ = {0, 1, 3, 4, 6};\n    assert(virtual_tree.vertex == expected_vertices);\n\
    \    assert(virtual_tree.parent == std::vector<int>({-1, 0, 1, 1, 0}));\n    assert(virtual_tree.parent_edge_count\
    \ == std::vector<int>({0, 1, 1, 1, 3}));\n    assert(virtual_tree.parent_cost\
    \ == std::vector<long long>({0, 3, 4, 1, 10}));\n    assert(virtual_tree.is_key\
    \ == std::vector<bool>({false, false, true, true, true}));\n    assert(virtual_tree.children[0]\
    \ == std::vector<int>({1, 4}));\n    assert(virtual_tree.children[1] == std::vector<int>({2,\
    \ 3}));\n    assert(virtual_tree.root() == 0);\n    assert(virtual_tree.root_vertex()\
    \ == 0);\n    assert(virtual_tree.edge_count() == 4);\n\n    auto singleton =\
    \ builder.build(std::vector<int>{5, 5});\n    assert(singleton.size() == 1);\n\
    \    assert(singleton.vertex[0] == 5);\n    assert(singleton.parent[0] == -1);\n\
    \    assert(singleton.is_key[0]);\n\n    auto empty = builder.build({});\n   \
    \ assert(empty.empty());\n    assert(empty.root() == -1);\n    assert(empty.root_vertex()\
    \ == -1);\n    assert(empty.edge_count() == 0);\n\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 100; test++) {\n        int n = 1 + random() %\
    \ 200;\n        Graph<long long> random_graph(n);\n        for (int v = 1; v <\
    \ n; v++) {\n            int parent = random() % v;\n            long long cost\
    \ = 1 + random() % 1000000;\n            random_graph.add_edge(parent, v, cost);\n\
    \        }\n        m1une::tree::VirtualTree<long long> random_builder(random_graph,\
    \ 0);\n        const auto& lca = random_builder.lca_data();\n        for (int\
    \ query = 0; query < 100; query++) {\n            int k = random() % (2 * n +\
    \ 1);\n            std::vector<int> keys(k);\n            for (int& v : keys)\
    \ v = random() % n;\n            auto result = random_builder.build(keys);\n\n\
    \            std::sort(keys.begin(), keys.end(), [&](int u, int v) {\n       \
    \         return lca.tin[u] < lca.tin[v];\n            });\n            keys.erase(std::unique(keys.begin(),\
    \ keys.end()), keys.end());\n            std::vector<int> expected = keys;\n \
    \           for (int i = 1; i < int(keys.size()); i++) expected.push_back(lca.lca(keys[i\
    \ - 1], keys[i]));\n            std::sort(expected.begin(), expected.end(), [&](int\
    \ u, int v) {\n                return lca.tin[u] < lca.tin[v];\n            });\n\
    \            expected.erase(std::unique(expected.begin(), expected.end()), expected.end());\n\
    \            assert(result.vertex == expected);\n\n            int key_index =\
    \ 0;\n            for (int i = 0; i < result.size(); i++) {\n                while\
    \ (key_index < int(keys.size()) && lca.tin[keys[key_index]] < lca.tin[result.vertex[i]])\
    \ {\n                    key_index++;\n                }\n                bool\
    \ is_key = key_index < int(keys.size()) && keys[key_index] == result.vertex[i];\n\
    \                assert(result.is_key[i] == is_key);\n                if (i ==\
    \ 0) {\n                    assert(result.parent[i] == -1);\n                \
    \    continue;\n                }\n                int parent = result.parent[i];\n\
    \                assert(0 <= parent && parent < i);\n                assert(lca.is_ancestor(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_edge_count[i] == lca.dist_edges(result.vertex[parent],\
    \ result.vertex[i]));\n                assert(result.parent_cost[i] == lca.dist_cost(result.vertex[parent],\
    \ result.vertex[i]));\n                for (int j = parent + 1; j < i; j++) {\n\
    \                    assert(!lca.is_ancestor(result.vertex[j], result.vertex[i]));\n\
    \                }\n            }\n        }\n    }\n}\n\nvoid test_hld() {\n\
    \    auto g = sample_tree();\n    m1une::tree::HeavyLightDecomposition<long long>\
    \ hld(g, 0);\n\n    assert(hld.size() == 7);\n    assert(hld.root == 0);\n   \
    \ assert(hld.lca(3, 4) == 1);\n    assert(hld.lca(3, 6) == 0);\n    assert(hld.dist_edges(3,\
    \ 6) == 5);\n    assert(hld.dist_cost(3, 6) == 17);\n    assert(hld.kth_ancestor(6,\
    \ 2) == 2);\n    assert(hld.kth_ancestor(6, 4) == -1);\n    assert(hld.jump(3,\
    \ 6, 4) == 5);\n\n    std::vector<int> expected_path = {3, 1, 0, 2, 5, 6};\n \
    \   assert(expand_segments(hld, hld.path_segments(3, 6)) == expected_path);\n\
    \    std::vector<int> expected_edge_vertices = {3, 1, 2, 5, 6};\n    assert(expand_segments(hld,\
    \ hld.path_segments(3, 6, true)) == expected_edge_vertices);\n\n    int segment_count\
    \ = 0;\n    hld.for_each_path(3, 6, [&](int l, int r, bool) {\n        assert(l\
    \ < r);\n        segment_count++;\n    });\n    assert(segment_count == int(hld.path_segments(3,\
    \ 6).size()));\n\n    auto [vl, vr] = hld.subtree_range(1);\n    std::vector<int>\
    \ subtree;\n    for (int i = vl; i < vr; i++) subtree.push_back(hld.order[i]);\n\
    \    std::sort(subtree.begin(), subtree.end());\n    assert((subtree == std::vector<int>{1,\
    \ 3, 4}));\n\n    auto [el, er] = hld.subtree_range(1, true);\n    std::vector<int>\
    \ edge_subtree;\n    for (int i = el; i < er; i++) edge_subtree.push_back(hld.order[i]);\n\
    \    std::sort(edge_subtree.begin(), edge_subtree.end());\n    assert((edge_subtree\
    \ == std::vector<int>{3, 4}));\n}\n\nvoid test_diameter() {\n    auto g = sample_tree();\n\
    \    auto diameter = m1une::tree::tree_diameter(g);\n\n    assert(!diameter.empty());\n\
    \    assert(diameter.cost == 17);\n    assert(diameter.edge_count == 5);\n   \
    \ assert(diameter.from == diameter.vertices.front());\n    assert(diameter.to\
    \ == diameter.vertices.back());\n    std::set<int> endpoints = {diameter.from,\
    \ diameter.to};\n    assert((endpoints == std::set<int>{3, 6}));\n\n    g.erase_edge(1);\n\
    \    auto split = m1une::tree::tree_diameter(g);\n    assert(split.cost == 8);\n\
    \    assert(split.edge_count == 2);\n}\n\nvoid test_rerooting() {\n    auto g\
    \ = sample_tree();\n    auto component_size = m1une::tree::rerooting_dp(\n   \
    \     g,\n        0,\n        [](int a, int b) { return a + b; },\n        [](int\
    \ acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return dp;\
    \ });\n    assert(component_size == std::vector<int>(7, 7));\n\n    auto eccentricity_edges\
    \ = m1une::tree::rerooting_dp(\n        g,\n        0,\n        [](int a, int\
    \ b) { return std::max(a, b); },\n        [](int acc, int) { return acc; },\n\
    \        [](int dp, const auto&) { return dp + 1; });\n    assert(eccentricity_edges[0]\
    \ == 3);\n    assert(eccentricity_edges[3] == 5);\n    assert(eccentricity_edges[6]\
    \ == 5);\n\n    auto eccentricity_cost = m1une::tree::rerooting_dp(\n        g,\n\
    \        0LL,\n        [](long long a, long long b) { return std::max(a, b); },\n\
    \        [](long long acc, int) { return acc; },\n        [](long long dp, const\
    \ auto& e) { return dp + e.cost; });\n    assert(eccentricity_cost[0] == 10);\n\
    \    assert(eccentricity_cost[3] == 17);\n    assert(eccentricity_cost[6] == 17);\n\
    }\n\nstruct DistancePath {\n    long long count;\n    long long sum;\n    long\
    \ long length;\n};\n\nstruct DistancePoint {\n    long long count;\n    long long\
    \ sum;\n};\n\nstruct ColorVertex {\n    long long weight;\n    int color;\n};\n\
    \nstruct ColorPath {\n    int first_color;\n    int last_color;\n    long long\
    \ first_sum;\n    long long last_sum;\n    bool connected;\n};\n\nstruct ColorPoint\
    \ {\n    std::array<long long, 2> sum;\n};\n\nvoid test_static_top_tree() {\n\
    \    auto g = sample_tree();\n    std::vector<long long> values = {1, 2, 3, 4,\
    \ 5, 6, 7};\n\n    auto vertex_sum = m1une::tree::StaticTopTree(\n        g,\n\
    \        values,\n        0LL,\n        [](long long top, long long bottom, const\
    \ auto&) {\n            return top + bottom;\n        },\n        [](long long\
    \ a, long long b) {\n            return a + b;\n        },\n        [](long long\
    \ path, const auto&) {\n            return path;\n        },\n        [](long\
    \ long side, long long value, int) {\n            return side + value;\n     \
    \   });\n\n    assert(vertex_sum.size() == 7);\n    assert(vertex_sum.root() ==\
    \ 0);\n    assert(vertex_sum.all_prod() == 28);\n    assert(vertex_sum.query()\
    \ == 28);\n    assert(vertex_sum.get(3) == 4);\n    assert(vertex_sum.height()\
    \ > 0);\n    vertex_sum.set(3, 100);\n    assert(vertex_sum[3] == 100);\n    assert(vertex_sum.all_prod()\
    \ == 124);\n\n    auto root_distance_sum = m1une::tree::StaticTopTree(\n     \
    \   g,\n        std::vector<int>(7, 0),\n        DistancePoint{0, 0},\n      \
    \  [](DistancePath top, DistancePath bottom, const auto& e) {\n            long\
    \ long shift = top.length + e.cost;\n            return DistancePath{top.count\
    \ + bottom.count, top.sum + bottom.sum + bottom.count * shift,\n             \
    \                   top.length + e.cost + bottom.length};\n        },\n      \
    \  [](DistancePoint a, DistancePoint b) {\n            return DistancePoint{a.count\
    \ + b.count, a.sum + b.sum};\n        },\n        [](DistancePath path, const\
    \ auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, int, int) {\n       \
    \     return DistancePath{side.count + 1, side.sum, 0};\n        });\n\n    assert(root_distance_sum.all_prod().count\
    \ == 7);\n    assert(root_distance_sum.all_prod().sum == 34);\n    root_distance_sum.set_edge_cost(0,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 55);\n    root_distance_sum.set_edge_cost(1,\
    \ 10);\n    assert(root_distance_sum.all_prod().sum == 79);\n}\n\nvoid test_rerooting_static_top_tree()\
    \ {\n    Graph<long long> g(3);\n    int e01 = g.add_edge(0, 1, 2);\n    int e12\
    \ = g.add_edge(1, 2, 5);\n    std::vector<long long> weights = {1, 1, 1};\n\n\
    \    auto stt = m1une::tree::RerootingStaticTopTree(\n        g,\n        weights,\n\
    \        DistancePoint{0, 0},\n        [](DistancePath upper, DistancePath lower,\
    \ const auto& e) {\n            long long shift = upper.length + e.cost;\n   \
    \         return DistancePath{upper.count + lower.count, upper.sum + lower.sum\
    \ + lower.count * shift,\n                                upper.length + e.cost\
    \ + lower.length};\n        },\n        [](DistancePath lower, DistancePath upper,\
    \ const auto& e) {\n            long long shift = lower.length + e.cost;\n   \
    \         return DistancePath{lower.count + upper.count, lower.sum + upper.sum\
    \ + upper.count * shift,\n                                lower.length + e.cost\
    \ + upper.length};\n        },\n        [](DistancePoint a, DistancePoint b) {\n\
    \            return DistancePoint{a.count + b.count, a.sum + b.sum};\n       \
    \ },\n        [](DistancePath path, const auto& e) {\n            return DistancePoint{path.count,\
    \ path.sum + path.count * e.cost};\n        },\n        [](DistancePath path,\
    \ const auto& e) {\n            return DistancePoint{path.count, path.sum + path.count\
    \ * e.cost};\n        },\n        [](DistancePoint side, long long weight, int)\
    \ {\n            return DistancePath{side.count + weight, side.sum, 0};\n    \
    \    });\n\n    assert(stt.size() == 3);\n    assert(stt.root() == 0);\n    assert(stt.node_count()\
    \ >= 3);\n    assert(stt.height() > 0);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 9);\n    assert(stt.all_prod_down().length\
    \ == 7);\n    assert(stt.all_prod_up().count == 3);\n    assert(stt.all_prod_up().sum\
    \ == 12);\n    assert(stt.all_prod_up().length == 7);\n\n    int root_node = stt.root_node();\n\
    \    assert(stt.path_down(root_node).sum == stt.all_prod_down().sum);\n    assert(stt.path_up(root_node).sum\
    \ == stt.all_prod_up().sum);\n    int one_node = stt.vertex_node(1);\n    assert(stt.node(one_node).type\
    \ == m1une::tree::internal::RerootingStaticTopTreeNodeType::AddVertex);\n    assert(stt.parent_node(root_node)\
    \ == -1);\n    assert(stt.point_id().count == 0);\n    assert(stt.local_point_node(1)\
    \ == -1);\n    assert(stt.local_point(1).count == 0);\n\n    using RerootingStepType\
    \ = decltype(stt)::step_type;\n    using RerootingNodeType = decltype(stt)::node_type;\n\
    \    auto steps = stt.rerooting_steps(1);\n    std::vector<decltype(stt)::RerootingStep>\
    \ streamed_steps;\n    stt.for_each_rerooting_step(1, [&](const auto& step) {\n\
    \        streamed_steps.push_back(step);\n    });\n    assert(streamed_steps.size()\
    \ == steps.size());\n    int cur = one_node;\n    for (int i = 0; i < int(steps.size());\
    \ i++) {\n        const auto& step = steps[i];\n        const auto& streamed =\
    \ streamed_steps[i];\n        assert(streamed.type == step.type);\n        assert(streamed.node\
    \ == step.node);\n        assert(streamed.sibling == step.sibling);\n        assert(streamed.vertex\
    \ == step.vertex);\n        assert(streamed.edge.from == step.edge.from);\n  \
    \      assert(streamed.edge.to == step.edge.to);\n        assert(streamed.edge.id\
    \ == step.edge.id);\n\n        assert(stt.parent_node(cur) == step.node);\n  \
    \      const auto& parent = stt.node(step.node);\n        if (step.type == RerootingStepType::CompressLower)\
    \ {\n            assert(parent.type == RerootingNodeType::Compress);\n       \
    \     assert(parent.left == cur);\n            assert(parent.right == step.sibling);\n\
    \            assert(stt.node(step.sibling).path_down.has_value());\n        }\
    \ else if (step.type == RerootingStepType::CompressUpper) {\n            assert(parent.type\
    \ == RerootingNodeType::Compress);\n            assert(parent.right == cur);\n\
    \            assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).path_up.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeLeft) {\n            assert(parent.type\
    \ == RerootingNodeType::Rake);\n            assert(parent.right == cur);\n   \
    \         assert(parent.left == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::RakeRight) {\n           \
    \ assert(parent.type == RerootingNodeType::Rake);\n            assert(parent.left\
    \ == cur);\n            assert(parent.right == step.sibling);\n            assert(stt.node(step.sibling).point.has_value());\n\
    \        } else if (step.type == RerootingStepType::AddEdge) {\n            assert(parent.type\
    \ == RerootingNodeType::AddEdge);\n            assert(parent.left == cur);\n \
    \       } else {\n            assert(step.type == RerootingStepType::AddVertex);\n\
    \            assert(parent.type == RerootingNodeType::AddVertex);\n          \
    \  assert(parent.left == cur);\n            assert(parent.vertex == step.vertex);\n\
    \        }\n        cur = step.node;\n    }\n    assert(cur == stt.root_node());\n\
    \n    auto edge = m1une::graph::Edge<long long>(0, 1, 2, e01);\n    auto reversed\
    \ = decltype(stt)::reverse_edge(edge);\n    assert(reversed.from == 1);\n    assert(reversed.to\
    \ == 0);\n    DistancePath one = stt.add_vertex(stt.point_id(), 1LL, 0);\n   \
    \ assert(one.count == 1);\n    assert(one.sum == 0);\n    auto down_point = stt.add_edge_down(one,\
    \ edge);\n    auto up_point = stt.add_edge_up(one, reversed);\n    assert(down_point.sum\
    \ == 2);\n    assert(up_point.sum == 2);\n    auto raked = stt.rake(down_point,\
    \ up_point);\n    assert(raked.count == 2);\n    assert(raked.sum == 4);\n   \
    \ assert(stt.compress_down(one, one, edge).sum == 2);\n    assert(stt.compress_up(one,\
    \ one, reversed).sum == 2);\n\n    stt.set_edge_cost(e01, 10);\n    assert(stt.all_prod_down().count\
    \ == 3);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_down().length\
    \ == 15);\n    assert(stt.all_prod_up().sum == 20);\n    assert(stt.all_prod_up().length\
    \ == 15);\n\n    stt.set(0, 3);\n    assert(stt[0] == 3);\n    assert(stt.all_prod_down().count\
    \ == 5);\n    assert(stt.all_prod_down().sum == 25);\n    assert(stt.all_prod_up().count\
    \ == 5);\n    assert(stt.all_prod_up().sum == 50);\n\n    stt.set_edge_cost(e12,\
    \ 1);\n    assert(stt.all_prod_down().sum == 21);\n    assert(stt.all_prod_up().sum\
    \ == 34);\n}\n\nvoid test_rerooting_static_top_tree_vertex_component() {\n   \
    \ auto g = sample_tree();\n    std::vector<ColorVertex> values = {\n        ColorVertex{1,\
    \ 0},      ColorVertex{10, 0},     ColorVertex{100, 1},    ColorVertex{1000, 0},\n\
    \        ColorVertex{10000, 1},  ColorVertex{100000, 1}, ColorVertex{1000000,\
    \ 1},\n    };\n\n    auto compress = [](ColorPath a, ColorPath b, const auto&)\
    \ {\n        bool join = a.last_color == b.first_color;\n        ColorPath res{a.first_color,\
    \ b.last_color, a.first_sum, b.last_sum, false};\n        if (join && a.connected)\
    \ res.first_sum += b.first_sum;\n        if (join && b.connected) res.last_sum\
    \ += a.last_sum;\n        res.connected = a.connected && b.connected && join;\n\
    \        return res;\n    };\n    auto rake = [](ColorPoint a, ColorPoint b) {\n\
    \        return ColorPoint{a.sum[0] + b.sum[0], a.sum[1] + b.sum[1]};\n    };\n\
    \    auto add_edge = [](ColorPath path, const auto&) {\n        ColorPoint res{};\n\
    \        res.sum[path.first_color] = path.first_sum;\n        return res;\n  \
    \  };\n    auto add_vertex = [](ColorPoint side, ColorVertex value, int) {\n \
    \       long long sum = value.weight + side.sum[value.color];\n        return\
    \ ColorPath{value.color, value.color, sum, sum, true};\n    };\n\n    auto stt\
    \ = m1une::tree::RerootingStaticTopTree(\n        g, values, ColorPoint{0, 0},\
    \ compress, compress, rake, add_edge, add_edge, add_vertex);\n\n    using ColorStt\
    \ = decltype(stt);\n    struct QueryFolder {\n        const ColorStt& stt;\n \
    \       const std::vector<ColorVertex>& values;\n        int color = 0;\n    \
    \    long long answer = 0;\n        bool touches_top = false;\n        bool touches_bottom\
    \ = false;\n        bool pending_open = false;\n        ColorPoint pending{};\n\
    \n        void start(int v, const ColorVertex& value, const ColorPoint& local)\
    \ {\n            color = value.color;\n            answer = value.weight + local.sum[color];\n\
    \            touches_top = true;\n            touches_bottom = true;\n       \
    \     pending_open = false;\n            pending = stt.point_id();\n         \
    \   assert(values[v].color == color);\n        }\n\n        void compress_lower(const\
    \ ColorPath& lower, ColorStt::edge_type) {\n            bool connect = touches_bottom\
    \ && lower.first_color == color;\n            if (connect) answer += lower.first_sum;\n\
    \            touches_bottom = connect && lower.connected;\n        }\n\n     \
    \   void compress_upper(const ColorPath& upper, ColorStt::edge_type) {\n     \
    \       bool connect = touches_top && upper.first_color == color;\n          \
    \  if (connect) answer += upper.first_sum;\n            touches_top = connect\
    \ && upper.connected;\n        }\n\n        void add_edge(ColorStt::edge_type)\
    \ {\n            pending_open = touches_top;\n            pending = stt.point_id();\n\
    \        }\n\n        void rake_left(const ColorPoint& point) {\n            if\
    \ (pending_open) pending = stt.rake(point, pending);\n        }\n\n        void\
    \ rake_right(const ColorPoint& point) {\n            if (pending_open) pending\
    \ = stt.rake(pending, point);\n        }\n\n        void add_vertex(int, const\
    \ ColorVertex& value) {\n            if (pending_open && value.color == color)\
    \ {\n                answer += value.weight + pending.sum[color];\n          \
    \      touches_top = true;\n                touches_bottom = true;\n         \
    \   } else {\n                touches_top = false;\n                touches_bottom\
    \ = false;\n            }\n            pending_open = false;\n            pending\
    \ = stt.point_id();\n        }\n\n        long long result() const {\n       \
    \     return answer;\n        }\n    };\n\n    auto query = [&](int v) {\n   \
    \     return stt.fold_rerooting(v, QueryFolder{stt, values});\n    };\n\n    auto\
    \ brute = [&](int start) {\n        int color = values[start].color;\n       \
    \ long long answer = 0;\n        std::vector<char> seen(g.size(), false);\n  \
    \      std::vector<int> stack = {start};\n        seen[start] = true;\n      \
    \  while (!stack.empty()) {\n            int v = stack.back();\n            stack.pop_back();\n\
    \            answer += values[v].weight;\n            for (const auto& e : g[v])\
    \ {\n                if (seen[e.to] || values[e.to].color != color) continue;\n\
    \                seen[e.to] = true;\n                stack.push_back(e.to);\n\
    \            }\n        }\n        return answer;\n    };\n\n    auto check_all\
    \ = [&]() {\n        for (int v = 0; v < g.size(); v++) assert(query(v) == brute(v));\n\
    \    };\n\n    check_all();\n    values[2].color ^= 1;\n    stt.set(2, values[2]);\n\
    \    check_all();\n    values[5].weight += 7;\n    stt.set(5, values[5]);\n  \
    \  check_all();\n    values[1].color ^= 1;\n    stt.set(1, values[1]);\n    check_all();\n\
    \    values[4].weight += 11;\n    stt.set(4, values[4]);\n    check_all();\n}\n\
    \nvoid test_centroid_decomposition() {\n    auto g = sample_tree();\n    m1une::tree::CentroidDecomposition<long\
    \ long> cd(g);\n\n    assert(cd.size() == 7);\n    assert(!cd.empty());\n    assert(cd.root()\
    \ == 0);\n    assert(cd.roots == std::vector<int>{0});\n    assert(cd.parent[cd.root()]\
    \ == -1);\n    assert(cd.depth[cd.root()] == 0);\n    assert(cd.order.size() ==\
    \ 7);\n\n    int child_count = 0;\n    for (const auto& ch : cd.children) child_count\
    \ += int(ch.size());\n    assert(child_count == 6);\n    for (int v = 0; v < 7;\
    \ v++) {\n        if (v == cd.root()) continue;\n        assert(cd.parent[v] !=\
    \ -1);\n        assert(cd.depth[v] == cd.depth[cd.parent[v]] + 1);\n    }\n}\n\
    \nvoid test_forest() {\n    Graph<int> g(4);\n    g.add_edge(0, 1, 5);\n    g.add_edge(2,\
    \ 3, 7);\n\n    auto diameter = m1une::tree::tree_diameter(g);\n    assert(diameter.cost\
    \ == 7);\n    assert(diameter.edge_count == 1);\n\n    auto component_size = m1une::tree::rerooting_dp(\n\
    \        g,\n        0,\n        [](int a, int b) { return a + b; },\n       \
    \ [](int acc, int) { return acc + 1; },\n        [](int dp, const auto&) { return\
    \ dp; });\n    assert(component_size == std::vector<int>(4, 2));\n\n    m1une::tree::CentroidDecomposition<int>\
    \ cd(g);\n    assert(cd.roots.size() == 2);\n    assert(cd.order.size() == 4);\n\
    }\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_rooted_tree();\n    test_euler_tour();\n    test_sparse_table_lca();\n\
    \    test_virtual_tree();\n    test_hld();\n    test_diameter();\n    test_rerooting();\n\
    \    test_static_top_tree();\n    test_rerooting_static_top_tree();\n    test_rerooting_static_top_tree_vertex_component();\n\
    \    test_centroid_decomposition();\n    test_forest();\n\n    long long a = 0,\
    \ b = 0;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - graph/graph.hpp
  - graph/tree/all.hpp
  - graph/tree/cartesian_tree.hpp
  - graph/graph.hpp
  - graph/tree/centroid_decomposition.hpp
  - graph/tree/diameter.hpp
  - graph/tree/distance_frequency.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  - graph/tree/dsu_on_tree.hpp
  - graph/tree/euler_tour.hpp
  - graph/tree/heavy_light_decomposition.hpp
  - graph/tree/range_contour_query.hpp
  - monoid/add.hpp
  - monoid/concept.hpp
  - graph/tree/rooted_tree.hpp
  - graph/tree/rerooting_dp.hpp
  - graph/tree/rerooting_static_top_tree.hpp
  - graph/tree/sparse_table_lca.hpp
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  - graph/tree/static_top_tree.hpp
  - graph/tree/tree.hpp
  - graph/tree/tree_hash.hpp
  - graph/tree/virtual_tree.hpp
  - graph/tree/zero_one_on_tree.hpp
  isVerificationFile: true
  path: verify/graph/tree/tree_algorithms.test.cpp
  requiredBy: []
  timestamp: '2026-07-21 20:17:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/tree_algorithms.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/tree_algorithms.test.cpp
- /verify/verify/graph/tree/tree_algorithms.test.cpp.html
title: verify/graph/tree/tree_algorithms.test.cpp
---
