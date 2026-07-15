---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: matroid/graphic_matroid.hpp
    title: Graphic Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/linear_matroid.hpp
    title: Linear Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/matroid_intersection.hpp
    title: Matroid Intersection
  - icon: ':heavy_check_mark:'
    path: matroid/partition_matroid.hpp
    title: Partition Matroid
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
  bundledCode: "#line 1 \"verify/matroid/matroid_intersection.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\
    \n#include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
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
    \ m1une\n\n\n#line 7 \"verify/matroid/matroid_intersection.test.cpp\"\n#include\
    \ <random>\n#line 9 \"verify/matroid/matroid_intersection.test.cpp\"\n#include\
    \ <vector>\n\n#line 1 \"matroid/graphic_matroid.hpp\"\n\n\n\n#line 5 \"matroid/graphic_matroid.hpp\"\
    \n#include <numeric>\n#line 8 \"matroid/graphic_matroid.hpp\"\n\nnamespace m1une\
    \ {\nnamespace matroid {\n\nclass GraphicMatroid {\n   private:\n    int _vertex_count;\n\
    \    std::vector<std::pair<int, int>> _edges;\n\n   public:\n    GraphicMatroid()\
    \ : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count, std::vector<std::pair<int,\
    \ int>> edges)\n        : _vertex_count(vertex_count), _edges(std::move(edges))\
    \ {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n        for (auto [u,\
    \ v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n         \
    \   assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n    int\
    \ size() const {\n        return int(_edges.size());\n    }\n\n    int vertex_count()\
    \ const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/linear_matroid.hpp\"\n\
    \n\n\n#line 9 \"matroid/linear_matroid.hpp\"\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class Field>\nclass LinearMatroid {\n   private:\n    int _dimension;\n\
    \    std::vector<std::vector<Field>> _vectors;\n\n   public:\n    LinearMatroid()\
    \ : _dimension(0) {}\n\n    explicit LinearMatroid(std::vector<std::vector<Field>>\
    \ vectors)\n        : _dimension(vectors.empty() ? 0 : int(vectors[0].size())),\n\
    \          _vectors(std::move(vectors)) {\n#ifndef NDEBUG\n        for (const\
    \ auto& vector : _vectors) assert(int(vector.size()) == _dimension);\n#endif\n\
    \    }\n\n    int size() const {\n        return int(_vectors.size());\n    }\n\
    \n    int dimension() const {\n        return _dimension;\n    }\n\n    const\
    \ std::vector<std::vector<Field>>& vectors() const {\n        return _vectors;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   if (int(subset.size()) > _dimension) return false;\n\n        std::vector<std::vector<Field>>\
    \ basis(_dimension);\n        std::vector<char> has_pivot(_dimension, false);\n\
    \        for (int element : subset) {\n            assert(0 <= element && element\
    \ < int(_vectors.size()));\n            std::vector<Field> vector = _vectors[element];\n\
    \            bool inserted = false;\n            for (int column = 0; column <\
    \ _dimension; column++) {\n                if (vector[column] == Field(0)) continue;\n\
    \                if (!has_pivot[column]) {\n                    Field inverse\
    \ = Field(1) / vector[column];\n                    for (int j = column; j < _dimension;\
    \ j++) vector[j] *= inverse;\n                    basis[column] = std::move(vector);\n\
    \                    has_pivot[column] = true;\n                    inserted =\
    \ true;\n                    break;\n                }\n                Field\
    \ factor = vector[column];\n                for (int j = column; j < _dimension;\
    \ j++) {\n                    vector[j] -= factor * basis[column][j];\n      \
    \          }\n            }\n            if (!inserted) return false;\n      \
    \  }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\nclass BinaryLinearMatroid\
    \ {\n   private:\n    std::vector<std::uint64_t> _vectors;\n\n   public:\n   \
    \ BinaryLinearMatroid() = default;\n    explicit BinaryLinearMatroid(std::vector<std::uint64_t>\
    \ vectors)\n        : _vectors(std::move(vectors)) {}\n\n    int size() const\
    \ {\n        return int(_vectors.size());\n    }\n\n    int dimension() const\
    \ {\n        return 64;\n    }\n\n    const std::vector<std::uint64_t>& vectors()\
    \ const {\n        return _vectors;\n    }\n\n    bool independent(const std::vector<int>&\
    \ subset) const {\n        if (subset.size() > 64) return false;\n\n        std::array<std::uint64_t,\
    \ 64> basis = {};\n        for (int element : subset) {\n            assert(0\
    \ <= element && element < int(_vectors.size()));\n            std::uint64_t value\
    \ = _vectors[element];\n            for (int bit = 63; bit >= 0; bit--) {\n  \
    \              if ((value >> bit & 1) == 0) continue;\n                if (basis[bit]\
    \ == 0) {\n                    basis[bit] = value;\n                    break;\n\
    \                }\n                value ^= basis[bit];\n            }\n    \
    \        if (value == 0) return false;\n        }\n        return true;\n    }\n\
    \n    bool operator()(const std::vector<int>& subset) const {\n        return\
    \ independent(subset);\n    }\n};\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/matroid_intersection.hpp\"\n\n\n\n#line 7 \"matroid/matroid_intersection.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\ntemplate <class IndependenceOracle1,\
    \ class IndependenceOracle2>\nstd::vector<int> matroid_intersection(int ground_size,\
    \ IndependenceOracle1 oracle1,\n                                      IndependenceOracle2\
    \ oracle2) {\n    assert(0 <= ground_size);\n\n    std::vector<char> selected(ground_size,\
    \ false);\n    std::vector<int> elements;\n    std::vector<int> position(ground_size,\
    \ -1);\n\n    while (true) {\n        std::vector<char> source(ground_size, false);\n\
    \        std::vector<char> sink(ground_size, false);\n        std::vector<int>\
    \ distance(ground_size, -1);\n        std::vector<int> previous(ground_size, -1);\n\
    \        std::vector<int> queue;\n        queue.reserve(ground_size);\n\n    \
    \    for (int x = 0; x < ground_size; x++) {\n            if (selected[x]) continue;\n\
    \            elements.push_back(x);\n            source[x] = oracle1(elements);\n\
    \            sink[x] = oracle2(elements);\n            elements.pop_back();\n\
    \            if (source[x]) {\n                distance[x] = 0;\n            \
    \    queue.push_back(x);\n            }\n        }\n\n        int target = -1;\n\
    \        for (int head = 0; head < int(queue.size()) && target == -1; head++)\
    \ {\n            int v = queue[head];\n            if (!selected[v] && sink[v])\
    \ {\n                target = v;\n                break;\n            }\n\n  \
    \          if (selected[v]) {\n                int index = position[v];\n    \
    \            assert(index != -1 && elements[index] == v);\n                for\
    \ (int x = 0; x < ground_size; x++) {\n                    if (selected[x] ||\
    \ distance[x] != -1) continue;\n                    elements[index] = x;\n   \
    \                 bool independent = oracle1(elements);\n                    elements[index]\
    \ = v;\n                    if (!independent) continue;\n                    distance[x]\
    \ = distance[v] + 1;\n                    previous[x] = v;\n                 \
    \   queue.push_back(x);\n                }\n            } else {\n           \
    \     for (int y : elements) {\n                    if (distance[y] != -1) continue;\n\
    \                    int index = position[y];\n                    assert(index\
    \ != -1 && elements[index] == y);\n                    elements[index] = v;\n\
    \                    bool independent = oracle2(elements);\n                 \
    \   elements[index] = y;\n                    if (!independent) continue;\n  \
    \                  distance[y] = distance[v] + 1;\n                    previous[y]\
    \ = v;\n                    queue.push_back(y);\n                }\n         \
    \   }\n        }\n\n        if (target == -1) break;\n        for (int v = target;\
    \ v != -1; v = previous[v]) selected[v] = !selected[v];\n\n        elements.clear();\n\
    \        std::fill(position.begin(), position.end(), -1);\n        for (int x\
    \ = 0; x < ground_size; x++) {\n            if (!selected[x]) continue;\n    \
    \        position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n    }\n\n    return elements;\n}\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/partition_matroid.hpp\"\n\n\n\n#line 8 \"matroid/partition_matroid.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\nclass PartitionMatroid {\n   private:\n\
    \    std::vector<int> _group;\n    std::vector<int> _capacity;\n\n    void validate()\
    \ const {\n#ifndef NDEBUG\n        for (int capacity : _capacity) assert(0 <=\
    \ capacity);\n        for (int group : _group) assert(0 <= group && group < int(_capacity.size()));\n\
    #endif\n    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit\
    \ PartitionMatroid(std::vector<int> group) : _group(std::move(group)) {\n    \
    \    int group_count = 0;\n        for (int value : _group) {\n            assert(0\
    \ <= value);\n            group_count = std::max(group_count, value + 1);\n  \
    \      }\n        _capacity.assign(group_count, 1);\n    }\n\n    PartitionMatroid(std::vector<int>\
    \ group, std::vector<int> capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 15 \"verify/matroid/matroid_intersection.test.cpp\"\
    \n\ntemplate <class Oracle1, class Oracle2>\nint brute_force(int ground_size,\
    \ const Oracle1& oracle1, const Oracle2& oracle2) {\n    int best = 0;\n    for\
    \ (int mask = 0; mask < (1 << ground_size); mask++) {\n        std::vector<int>\
    \ subset;\n        for (int i = 0; i < ground_size; i++) {\n            if (mask\
    \ >> i & 1) subset.push_back(i);\n        }\n        if (oracle1(subset) && oracle2(subset))\
    \ best = std::max(best, int(subset.size()));\n    }\n    return best;\n}\n\ntemplate\
    \ <class Oracle1, class Oracle2>\nvoid check(int ground_size, const Oracle1& oracle1,\
    \ const Oracle2& oracle2) {\n    auto result = m1une::matroid::matroid_intersection(ground_size,\
    \ oracle1, oracle2);\n    assert(std::is_sorted(result.begin(), result.end()));\n\
    \    assert(std::adjacent_find(result.begin(), result.end()) == result.end());\n\
    \    assert(oracle1(result));\n    assert(oracle2(result));\n    assert(int(result.size())\
    \ == brute_force(ground_size, oracle1, oracle2));\n}\n\nvoid test_augmenting_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    auto\
    \ result = m1une::matroid::matroid_intersection(3, left, right);\n    assert((result\
    \ == std::vector<int>{1, 2}));\n}\n\nvoid test_random_matroids() {\n    std::mt19937\
    \ random(123456789);\n    for (int test = 0; test < 300; test++) {\n        int\
    \ ground_size = random() % 11;\n        int group_count = 1 + random() % 5;\n\
    \        std::vector<int> group(ground_size);\n        for (int& value : group)\
    \ value = random() % group_count;\n        std::vector<int> capacity(group_count,\
    \ 1);\n        m1une::matroid::PartitionMatroid partition(group, capacity);\n\n\
    \        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edge(ground_size);\n        for (auto& [u, v] : edge) {\n            u\
    \ = random() % vertex_count;\n            v = random() % vertex_count;\n     \
    \   }\n        m1une::matroid::GraphicMatroid graphic(vertex_count, edge);\n \
    \       check(ground_size, partition, graphic);\n\n        int second_group_count\
    \ = 1 + random() % 5;\n        std::vector<int> second_group(ground_size);\n \
    \       for (int& value : second_group) value = random() % second_group_count;\n\
    \        m1une::matroid::PartitionMatroid second_partition(second_group);\n  \
    \      check(ground_size, partition, second_partition);\n\n        std::vector<std::uint64_t>\
    \ vector1(ground_size), vector2(ground_size);\n        for (int i = 0; i < ground_size;\
    \ i++) {\n            vector1[i] = random() % 64;\n            vector2[i] = random()\
    \ % 64;\n        }\n        m1une::matroid::BinaryLinearMatroid linear1(vector1),\
    \ linear2(vector2);\n        check(ground_size, linear1, linear2);\n    }\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_augmenting_exchange();\n    test_random_matroids();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <random>\n#include <utility>\n#include <vector>\n\n#include \"../../matroid/graphic_matroid.hpp\"\
    \n#include \"../../matroid/linear_matroid.hpp\"\n#include \"../../matroid/matroid_intersection.hpp\"\
    \n#include \"../../matroid/partition_matroid.hpp\"\n\ntemplate <class Oracle1,\
    \ class Oracle2>\nint brute_force(int ground_size, const Oracle1& oracle1, const\
    \ Oracle2& oracle2) {\n    int best = 0;\n    for (int mask = 0; mask < (1 <<\
    \ ground_size); mask++) {\n        std::vector<int> subset;\n        for (int\
    \ i = 0; i < ground_size; i++) {\n            if (mask >> i & 1) subset.push_back(i);\n\
    \        }\n        if (oracle1(subset) && oracle2(subset)) best = std::max(best,\
    \ int(subset.size()));\n    }\n    return best;\n}\n\ntemplate <class Oracle1,\
    \ class Oracle2>\nvoid check(int ground_size, const Oracle1& oracle1, const Oracle2&\
    \ oracle2) {\n    auto result = m1une::matroid::matroid_intersection(ground_size,\
    \ oracle1, oracle2);\n    assert(std::is_sorted(result.begin(), result.end()));\n\
    \    assert(std::adjacent_find(result.begin(), result.end()) == result.end());\n\
    \    assert(oracle1(result));\n    assert(oracle2(result));\n    assert(int(result.size())\
    \ == brute_force(ground_size, oracle1, oracle2));\n}\n\nvoid test_augmenting_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    auto\
    \ result = m1une::matroid::matroid_intersection(3, left, right);\n    assert((result\
    \ == std::vector<int>{1, 2}));\n}\n\nvoid test_random_matroids() {\n    std::mt19937\
    \ random(123456789);\n    for (int test = 0; test < 300; test++) {\n        int\
    \ ground_size = random() % 11;\n        int group_count = 1 + random() % 5;\n\
    \        std::vector<int> group(ground_size);\n        for (int& value : group)\
    \ value = random() % group_count;\n        std::vector<int> capacity(group_count,\
    \ 1);\n        m1une::matroid::PartitionMatroid partition(group, capacity);\n\n\
    \        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edge(ground_size);\n        for (auto& [u, v] : edge) {\n            u\
    \ = random() % vertex_count;\n            v = random() % vertex_count;\n     \
    \   }\n        m1une::matroid::GraphicMatroid graphic(vertex_count, edge);\n \
    \       check(ground_size, partition, graphic);\n\n        int second_group_count\
    \ = 1 + random() % 5;\n        std::vector<int> second_group(ground_size);\n \
    \       for (int& value : second_group) value = random() % second_group_count;\n\
    \        m1une::matroid::PartitionMatroid second_partition(second_group);\n  \
    \      check(ground_size, partition, second_partition);\n\n        std::vector<std::uint64_t>\
    \ vector1(ground_size), vector2(ground_size);\n        for (int i = 0; i < ground_size;\
    \ i++) {\n            vector1[i] = random() % 64;\n            vector2[i] = random()\
    \ % 64;\n        }\n        m1une::matroid::BinaryLinearMatroid linear1(vector1),\
    \ linear2(vector2);\n        check(ground_size, linear1, linear2);\n    }\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_augmenting_exchange();\n    test_random_matroids();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - matroid/graphic_matroid.hpp
  - matroid/linear_matroid.hpp
  - matroid/matroid_intersection.hpp
  - matroid/partition_matroid.hpp
  isVerificationFile: true
  path: verify/matroid/matroid_intersection.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matroid/matroid_intersection.test.cpp
layout: document
redirect_from:
- /verify/verify/matroid/matroid_intersection.test.cpp
- /verify/verify/matroid/matroid_intersection.test.cpp.html
title: verify/matroid/matroid_intersection.test.cpp
---
