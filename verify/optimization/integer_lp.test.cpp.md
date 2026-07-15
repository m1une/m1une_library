---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
  - icon: ':heavy_check_mark:'
    path: optimization/all.hpp
    title: Optimization All
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
  - icon: ':heavy_check_mark:'
    path: optimization/integer_lp.hpp
    title: Integer Linear Programming
  - icon: ':heavy_check_mark:'
    path: optimization/project_selection.hpp
    title: Project Selection
  - icon: ':heavy_check_mark:'
    path: optimization/simplex.hpp
    title: Simplex Algorithm
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
  bundledCode: "#line 1 \"verify/optimization/integer_lp.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#line 1 \"\
    utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ m1une\n\n\n#line 5 \"verify/optimization/integer_lp.test.cpp\"\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"optimization/all.hpp\"\n\n\n\n#line 1 \"optimization/hungarian.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 9 \"optimization/hungarian.hpp\"\n\nnamespace\
    \ m1une {\nnamespace opt {\n\ntemplate <class T>\nstruct HungarianResult {\n \
    \   T cost;\n    std::vector<int> row_to_col;\n    std::vector<int> col_to_row;\n\
    \n    int matching_size() const {\n        int result = 0;\n        for (int col\
    \ : row_to_col) {\n            if (col != -1) result++;\n        }\n        return\
    \ result;\n    }\n\n    std::vector<std::pair<int, int>> matching() const {\n\
    \        std::vector<std::pair<int, int>> result;\n        for (int row = 0; row\
    \ < int(row_to_col.size()); row++) {\n            if (row_to_col[row] != -1) result.push_back({row,\
    \ row_to_col[row]});\n        }\n        return result;\n    }\n};\n\nnamespace\
    \ detail {\n\ntemplate <class T>\nT assignment_cost(const std::vector<std::vector<T>>&\
    \ cost, const std::vector<int>& row_to_col) {\n    T result = T();\n    for (int\
    \ row = 0; row < int(row_to_col.size()); row++) {\n        if (row_to_col[row]\
    \ != -1) result += cost[row][row_to_col[row]];\n    }\n    return result;\n}\n\
    \n}  // namespace detail\n\ntemplate <class T>\nHungarianResult<T> hungarian_min(const\
    \ std::vector<std::vector<T>>& cost) {\n    int row_count = int(cost.size());\n\
    \    int col_count = row_count == 0 ? 0 : int(cost[0].size());\n    for (const\
    \ auto& row : cost) assert(int(row.size()) == col_count);\n\n    HungarianResult<T>\
    \ result;\n    result.cost = T();\n    result.row_to_col.assign(row_count, -1);\n\
    \    result.col_to_row.assign(col_count, -1);\n    if (row_count == 0 || col_count\
    \ == 0) return result;\n\n    bool transposed = row_count > col_count;\n    int\
    \ n = transposed ? col_count : row_count;\n    int m = transposed ? row_count\
    \ : col_count;\n    T inf = std::numeric_limits<T>::max() / T(4);\n\n    std::vector<T>\
    \ u(n + 1, T()), v(m + 1, T()), minv(m + 1);\n    std::vector<int> p(m + 1, 0),\
    \ way(m + 1, 0);\n\n    auto value = [&](int i, int j) -> T {\n        return\
    \ transposed ? cost[j][i] : cost[i][j];\n    };\n\n    for (int i = 1; i <= n;\
    \ i++) {\n        p[0] = i;\n        int j0 = 0;\n        std::fill(minv.begin(),\
    \ minv.end(), inf);\n        std::vector<char> used(m + 1, false);\n\n       \
    \ do {\n            used[j0] = true;\n            int i0 = p[j0];\n          \
    \  int j1 = 0;\n            T delta = inf;\n\n            for (int j = 1; j <=\
    \ m; j++) {\n                if (used[j]) continue;\n                T cur = value(i0\
    \ - 1, j - 1) - u[i0] - v[j];\n                if (cur < minv[j]) {\n        \
    \            minv[j] = cur;\n                    way[j] = j0;\n              \
    \  }\n                if (minv[j] < delta) {\n                    delta = minv[j];\n\
    \                    j1 = j;\n                }\n            }\n\n           \
    \ for (int j = 0; j <= m; j++) {\n                if (used[j]) {\n           \
    \         u[p[j]] += delta;\n                    v[j] -= delta;\n            \
    \    } else {\n                    minv[j] -= delta;\n                }\n    \
    \        }\n            j0 = j1;\n        } while (p[j0] != 0);\n\n        do\
    \ {\n            int j1 = way[j0];\n            p[j0] = p[j1];\n            j0\
    \ = j1;\n        } while (j0 != 0);\n    }\n\n    for (int j = 1; j <= m; j++)\
    \ {\n        if (p[j] == 0) continue;\n        int i = p[j] - 1;\n        int\
    \ matched = j - 1;\n        if (transposed) {\n            int row = matched;\n\
    \            int col = i;\n            result.row_to_col[row] = col;\n       \
    \     result.col_to_row[col] = row;\n        } else {\n            int row = i;\n\
    \            int col = matched;\n            result.row_to_col[row] = col;\n \
    \           result.col_to_row[col] = row;\n        }\n    }\n    result.cost =\
    \ detail::assignment_cost(cost, result.row_to_col);\n    return result;\n}\n\n\
    template <class T>\nHungarianResult<T> hungarian_max(const std::vector<std::vector<T>>&\
    \ cost) {\n    std::vector<std::vector<T>> negated = cost;\n    for (auto& row\
    \ : negated) {\n        for (auto& x : row) x = -x;\n    }\n    auto result =\
    \ hungarian_min(negated);\n    result.cost = detail::assignment_cost(cost, result.row_to_col);\n\
    \    return result;\n}\n\ntemplate <class T>\nHungarianResult<T> hungarian(const\
    \ std::vector<std::vector<T>>& cost) {\n    return hungarian_min(cost);\n}\n\n\
    }  // namespace opt\n}  // namespace m1une\n\n\n#line 1 \"optimization/integer_lp.hpp\"\
    \n\n\n\n#line 6 \"optimization/integer_lp.hpp\"\n#include <cmath>\n#line 10 \"\
    optimization/integer_lp.hpp\"\n\n#line 1 \"optimization/simplex.hpp\"\n\n\n\n\
    #line 9 \"optimization/simplex.hpp\"\n\nnamespace m1une {\nnamespace opt {\n\n\
    enum class SimplexStatus {\n    Optimal,\n    Infeasible,\n    Unbounded,\n};\n\
    \ntemplate <class T>\nstruct SimplexResult {\n    SimplexStatus status;\n    T\
    \ objective_value;\n    std::vector<T> variables;\n\n    bool is_optimal() const\
    \ { return status == SimplexStatus::Optimal; }\n    bool is_infeasible() const\
    \ { return status == SimplexStatus::Infeasible; }\n    bool is_unbounded() const\
    \ { return status == SimplexStatus::Unbounded; }\n};\n\nnamespace detail {\n\n\
    template <class T>\nT simplex_abs(T x) {\n    return x < T() ? -x : x;\n}\n\n\
    template <class T>\nstruct SimplexTableau {\n    int constraint_count;\n    int\
    \ variable_count;\n    T eps;\n    std::vector<int> basis;\n    std::vector<int>\
    \ nonbasis;\n    std::vector<std::vector<T>> table;\n\n    SimplexTableau(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \  const std::vector<T>& c, T epsilon)\n        : constraint_count(int(b.size())),\n\
    \          variable_count(int(c.size())),\n          eps(epsilon),\n         \
    \ basis(constraint_count),\n          nonbasis(variable_count + 1),\n        \
    \  table(constraint_count + 2, std::vector<T>(variable_count + 2, T())) {\n  \
    \      for (int i = 0; i < constraint_count; i++) {\n            for (int j =\
    \ 0; j < variable_count; j++) table[i][j] = a[i][j];\n        }\n        for (int\
    \ i = 0; i < constraint_count; i++) {\n            basis[i] = variable_count +\
    \ i;\n            table[i][artificial_col()] = T(-1);\n            table[i][rhs_col()]\
    \ = b[i];\n        }\n        for (int j = 0; j < variable_count; j++) {\n   \
    \         nonbasis[j] = j;\n            table[objective_row()][j] = -c[j];\n \
    \       }\n        nonbasis[artificial_col()] = artificial_id();\n        table[auxiliary_row()][artificial_col()]\
    \ = T(1);\n    }\n\n    int objective_row() const { return constraint_count; }\n\
    \    int auxiliary_row() const { return constraint_count + 1; }\n    int artificial_col()\
    \ const { return variable_count; }\n    int rhs_col() const { return variable_count\
    \ + 1; }\n    int artificial_id() const { return -1; }\n\n    T normalize(T x)\
    \ const {\n        return simplex_abs(x) <= eps ? T() : x;\n    }\n\n    bool\
    \ less_with_tie(int row, int lhs, int rhs) const {\n        if (table[row][lhs]\
    \ < table[row][rhs] - eps) return true;\n        if (table[row][rhs] < table[row][lhs]\
    \ - eps) return false;\n        return nonbasis[lhs] < nonbasis[rhs];\n    }\n\
    \n    bool better_leaving_row(int lhs, int rhs, int entering_col) const {\n  \
    \      T lhs_ratio = table[lhs][rhs_col()] / table[lhs][entering_col];\n     \
    \   T rhs_ratio = table[rhs][rhs_col()] / table[rhs][entering_col];\n        if\
    \ (lhs_ratio < rhs_ratio - eps) return true;\n        if (rhs_ratio < lhs_ratio\
    \ - eps) return false;\n        return basis[lhs] < basis[rhs];\n    }\n\n   \
    \ void pivot(int leaving_row, int entering_col) {\n        T inverse = T(1) /\
    \ table[leaving_row][entering_col];\n        for (int i = 0; i < constraint_count\
    \ + 2; i++) {\n            if (i == leaving_row) continue;\n            for (int\
    \ j = 0; j < variable_count + 2; j++) {\n                if (j == entering_col)\
    \ continue;\n                table[i][j] -= table[leaving_row][j] * table[i][entering_col]\
    \ * inverse;\n            }\n        }\n        for (int j = 0; j < variable_count\
    \ + 2; j++) {\n            if (j != entering_col) table[leaving_row][j] *= inverse;\n\
    \        }\n        for (int i = 0; i < constraint_count + 2; i++) {\n       \
    \     if (i != leaving_row) table[i][entering_col] *= -inverse;\n        }\n \
    \       table[leaving_row][entering_col] = inverse;\n        std::swap(basis[leaving_row],\
    \ nonbasis[entering_col]);\n    }\n\n    bool run_simplex(int row) {\n       \
    \ while (true) {\n            int entering_col = -1;\n            for (int j =\
    \ 0; j <= variable_count; j++) {\n                if (nonbasis[j] == artificial_id())\
    \ continue;\n                if (entering_col == -1 || less_with_tie(row, j, entering_col))\
    \ entering_col = j;\n            }\n            if (entering_col == -1 || table[row][entering_col]\
    \ >= -eps) return true;\n\n            int leaving_row = -1;\n            for\
    \ (int i = 0; i < constraint_count; i++) {\n                if (table[i][entering_col]\
    \ <= eps) continue;\n                if (leaving_row == -1 || better_leaving_row(i,\
    \ leaving_row, entering_col)) {\n                    leaving_row = i;\n      \
    \          }\n            }\n            if (leaving_row == -1) return false;\n\
    \            pivot(leaving_row, entering_col);\n        }\n    }\n\n    bool make_feasible()\
    \ {\n        int leaving_row = 0;\n        for (int i = 1; i < constraint_count;\
    \ i++) {\n            if (table[i][rhs_col()] < table[leaving_row][rhs_col()])\
    \ leaving_row = i;\n        }\n        if (constraint_count == 0 || table[leaving_row][rhs_col()]\
    \ >= -eps) return true;\n\n        pivot(leaving_row, artificial_col());\n   \
    \     if (!run_simplex(auxiliary_row())) return false;\n        if (table[auxiliary_row()][rhs_col()]\
    \ < -eps) return false;\n\n        for (int i = 0; i < constraint_count; i++)\
    \ {\n            if (basis[i] != artificial_id()) continue;\n            int entering_col\
    \ = -1;\n            for (int j = 0; j <= variable_count; j++) {\n           \
    \     if (nonbasis[j] == artificial_id()) continue;\n                if (simplex_abs(table[i][j])\
    \ <= eps) continue;\n                if (entering_col == -1 || nonbasis[j] < nonbasis[entering_col])\
    \ entering_col = j;\n            }\n            if (entering_col != -1) pivot(i,\
    \ entering_col);\n        }\n        return true;\n    }\n\n    SimplexStatus\
    \ solve(std::vector<T>& variables, T& objective_value) {\n        if (!make_feasible())\
    \ return SimplexStatus::Infeasible;\n        if (!run_simplex(objective_row()))\
    \ return SimplexStatus::Unbounded;\n\n        variables.assign(variable_count,\
    \ T());\n        for (int i = 0; i < constraint_count; i++) {\n            if\
    \ (0 <= basis[i] && basis[i] < variable_count) {\n                variables[basis[i]]\
    \ = normalize(table[i][rhs_col()]);\n            }\n        }\n        objective_value\
    \ = normalize(table[objective_row()][rhs_col()]);\n        return SimplexStatus::Optimal;\n\
    \    }\n};\n\n}  // namespace detail\n\ntemplate <class T>\nSimplexResult<T> simplex_maximize(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \                 const std::vector<T>& c, T eps = T(1e-10)) {\n    static_assert(std::is_floating_point_v<T>,\
    \ \"simplex requires a floating-point type\");\n    assert(int(a.size()) == int(b.size()));\n\
    \    for (const auto& row : a) assert(int(row.size()) == int(c.size()));\n   \
    \ assert(eps > T());\n\n    SimplexResult<T> result;\n    result.status = SimplexStatus::Infeasible;\n\
    \    result.objective_value = std::numeric_limits<T>::quiet_NaN();\n    result.variables.assign(c.size(),\
    \ T());\n\n    detail::SimplexTableau<T> solver(a, b, c, eps);\n    result.status\
    \ = solver.solve(result.variables, result.objective_value);\n    if (result.status\
    \ == SimplexStatus::Infeasible) {\n        result.objective_value = std::numeric_limits<T>::quiet_NaN();\n\
    \    } else if (result.status == SimplexStatus::Unbounded) {\n        result.objective_value\
    \ = std::numeric_limits<T>::infinity();\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nSimplexResult<T> simplex_minimize(const std::vector<std::vector<T>>&\
    \ a, const std::vector<T>& b,\n                                  const std::vector<T>&\
    \ c, T eps = T(1e-10)) {\n    std::vector<T> negated = c;\n    for (T& x : negated)\
    \ x = -x;\n    auto result = simplex_maximize(a, b, negated, eps);\n    if (result.status\
    \ == SimplexStatus::Optimal) {\n        result.objective_value = -result.objective_value;\n\
    \    } else if (result.status == SimplexStatus::Unbounded) {\n        result.objective_value\
    \ = -std::numeric_limits<T>::infinity();\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nSimplexResult<T> simplex(const std::vector<std::vector<T>>& a, const\
    \ std::vector<T>& b,\n                         const std::vector<T>& c, T eps\
    \ = T(1e-10)) {\n    return simplex_maximize(a, b, c, eps);\n}\n\n}  // namespace\
    \ opt\n}  // namespace m1une\n\n\n#line 12 \"optimization/integer_lp.hpp\"\n\n\
    namespace m1une {\nnamespace opt {\n\nenum class IntegerLpStatus {\n    Optimal,\n\
    \    Infeasible,\n    Unbounded,\n};\n\ntemplate <class T>\nstruct IntegerLpResult\
    \ {\n    IntegerLpStatus status;\n    T objective_value;\n    std::vector<T> variables;\n\
    \n    bool is_optimal() const { return status == IntegerLpStatus::Optimal; }\n\
    \    bool is_infeasible() const { return status == IntegerLpStatus::Infeasible;\
    \ }\n    bool is_unbounded() const { return status == IntegerLpStatus::Unbounded;\
    \ }\n};\n\nnamespace detail {\n\ntemplate <class T>\nstruct IntegerLpSolver {\n\
    \    using Real = long double;\n\n    struct Node {\n        std::vector<std::vector<Real>>\
    \ a;\n        std::vector<Real> b;\n    };\n\n    int variable_count;\n    bool\
    \ maximize;\n    Real eps;\n    std::vector<T> objective;\n    std::vector<Real>\
    \ relaxation_objective;\n    Node initial_node;\n\n    bool has_incumbent = false;\n\
    \    T best_value = T();\n    std::vector<T> best_variables;\n\n    IntegerLpSolver(const\
    \ std::vector<std::vector<T>>& a, const std::vector<T>& b,\n                 \
    \   const std::vector<T>& c, bool is_maximize, Real epsilon)\n        : variable_count(int(c.size())),\n\
    \          maximize(is_maximize),\n          eps(epsilon),\n          objective(c),\n\
    \          relaxation_objective(c.size(), Real()),\n          initial_node() {\n\
    \        initial_node.a.assign(a.size(), std::vector<Real>(variable_count, Real()));\n\
    \        initial_node.b.assign(b.size(), Real());\n        for (int i = 0; i <\
    \ int(a.size()); i++) {\n            for (int j = 0; j < variable_count; j++)\
    \ initial_node.a[i][j] = Real(a[i][j]);\n            initial_node.b[i] = Real(b[i]);\n\
    \        }\n        Real sign = maximize ? Real(1) : Real(-1);\n        for (int\
    \ j = 0; j < variable_count; j++) relaxation_objective[j] = sign * Real(c[j]);\n\
    \    }\n\n    Real abs_value(Real x) const {\n        return x < Real() ? -x :\
    \ x;\n    }\n\n    bool better_value(T lhs, T rhs) const {\n        return maximize\
    \ ? lhs > rhs : lhs < rhs;\n    }\n\n    bool can_prune_by_bound(Real relaxation_value)\
    \ const {\n        if (!has_incumbent) return false;\n        Real signed_best\
    \ = maximize ? Real(best_value) : -Real(best_value);\n        return relaxation_value\
    \ <= signed_best + eps;\n    }\n\n    T evaluate(const std::vector<T>& variables)\
    \ const {\n        T result = T();\n        for (int i = 0; i < variable_count;\
    \ i++) result += objective[i] * variables[i];\n        return result;\n    }\n\
    \n    bool round_solution(const std::vector<Real>& real_variables, std::vector<T>&\
    \ variables) const {\n        variables.assign(variable_count, T());\n       \
    \ for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            if (value < -eps) return false;\n            Real rounded = std::round(value);\n\
    \            if (abs_value(value - rounded) > eps) return false;\n           \
    \ variables[i] = static_cast<T>(rounded);\n        }\n        return true;\n \
    \   }\n\n    int find_fractional_variable(const std::vector<Real>& real_variables)\
    \ const {\n        int result = -1;\n        Real best_distance = eps;\n     \
    \   for (int i = 0; i < variable_count; i++) {\n            Real value = real_variables[i];\n\
    \            Real rounded = std::round(value);\n            Real distance = abs_value(value\
    \ - rounded);\n            if (distance > best_distance) {\n                best_distance\
    \ = distance;\n                result = i;\n            }\n        }\n       \
    \ return result;\n    }\n\n    Node with_upper_bound(const Node& node, int variable,\
    \ T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(1);\n        result.b.push_back(Real(bound));\n\
    \        return result;\n    }\n\n    Node with_lower_bound(const Node& node,\
    \ int variable, T bound) const {\n        Node result = node;\n        result.a.emplace_back(variable_count,\
    \ Real());\n        result.a.back()[variable] = Real(-1);\n        result.b.push_back(-Real(bound));\n\
    \        return result;\n    }\n\n    void push_branches(std::vector<Node>& stack,\
    \ const Node& node, int variable, Real value) const {\n        Real floor_value\
    \ = std::floor(value);\n        Real ceil_value = std::ceil(value);\n        T\
    \ upper_bound = static_cast<T>(floor_value);\n        T lower_bound = static_cast<T>(ceil_value);\n\
    \n        bool has_upper_branch = upper_bound >= T();\n        bool prefer_lower_branch\
    \ = relaxation_objective[variable] >= -eps;\n\n        if (prefer_lower_branch)\
    \ {\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n        } else {\n            stack.push_back(with_lower_bound(node,\
    \ variable, lower_bound));\n            if (has_upper_branch) stack.push_back(with_upper_bound(node,\
    \ variable, upper_bound));\n        }\n    }\n\n    bool has_positive_direction(const\
    \ Node& node) const {\n        std::vector<std::vector<Real>> direction_a = node.a;\n\
    \        std::vector<Real> direction_b(node.b.size(), Real());\n\n        std::vector<Real>\
    \ objective_row(variable_count, Real());\n        for (int i = 0; i < variable_count;\
    \ i++) objective_row[i] = -relaxation_objective[i];\n        direction_a.push_back(objective_row);\n\
    \        direction_b.push_back(Real(-1));\n\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n        auto result = simplex_maximize(direction_a, direction_b, zero_objective,\
    \ eps);\n        return result.is_optimal();\n    }\n\n    bool find_integer_feasible(const\
    \ Node& start, std::vector<T>& feasible_variables) const {\n        std::vector<Node>\
    \ stack;\n        stack.push_back(start);\n        std::vector<Real> zero_objective(variable_count,\
    \ Real());\n\n        while (!stack.empty()) {\n            Node node = stack.back();\n\
    \            stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, zero_objective, eps);\n            if (relaxation.is_infeasible()) continue;\n\
    \            if (relaxation.is_unbounded()) continue;\n\n            if (round_solution(relaxation.variables,\
    \ feasible_variables)) return true;\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n        return false;\n\
    \    }\n\n    void update_incumbent(const std::vector<T>& variables) {\n     \
    \   T value = evaluate(variables);\n        if (!has_incumbent || better_value(value,\
    \ best_value)) {\n            has_incumbent = true;\n            best_value =\
    \ value;\n            best_variables = variables;\n        }\n    }\n\n    IntegerLpResult<T>\
    \ make_infeasible_result() const {\n        IntegerLpResult<T> result;\n     \
    \   result.status = IntegerLpStatus::Infeasible;\n        result.objective_value\
    \ = T();\n        result.variables.assign(variable_count, T());\n        return\
    \ result;\n    }\n\n    IntegerLpResult<T> make_unbounded_result(const std::vector<T>&\
    \ variables) const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Unbounded;\n        result.objective_value =\n          \
    \  maximize ? std::numeric_limits<T>::max() : std::numeric_limits<T>::lowest();\n\
    \        result.variables = variables;\n        return result;\n    }\n\n    IntegerLpResult<T>\
    \ make_optimal_result() const {\n        IntegerLpResult<T> result;\n        result.status\
    \ = IntegerLpStatus::Optimal;\n        result.objective_value = best_value;\n\
    \        result.variables = best_variables;\n        return result;\n    }\n\n\
    \    IntegerLpResult<T> solve() {\n        std::vector<Node> stack;\n        stack.push_back(initial_node);\n\
    \n        while (!stack.empty()) {\n            Node node = stack.back();\n  \
    \          stack.pop_back();\n\n            auto relaxation = simplex_maximize(node.a,\
    \ node.b, relaxation_objective, eps);\n            if (relaxation.is_infeasible())\
    \ continue;\n\n            if (relaxation.is_unbounded()) {\n                std::vector<T>\
    \ feasible_variables;\n                if (has_positive_direction(node) && find_integer_feasible(node,\
    \ feasible_variables)) {\n                    return make_unbounded_result(feasible_variables);\n\
    \                }\n                continue;\n            }\n\n            if\
    \ (can_prune_by_bound(relaxation.objective_value)) continue;\n\n            std::vector<T>\
    \ integer_variables;\n            if (round_solution(relaxation.variables, integer_variables))\
    \ {\n                update_incumbent(integer_variables);\n                continue;\n\
    \            }\n\n            int variable = find_fractional_variable(relaxation.variables);\n\
    \            if (variable == -1) continue;\n            push_branches(stack, node,\
    \ variable, relaxation.variables[variable]);\n        }\n\n        if (!has_incumbent)\
    \ return make_infeasible_result();\n        return make_optimal_result();\n  \
    \  }\n};\n\n}  // namespace detail\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_maximize(const\
    \ std::vector<std::vector<T>>& a,\n                                       const\
    \ std::vector<T>& b, const std::vector<T>& c,\n                              \
    \         long double eps = 1e-10L) {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>,\n                  \"integer_lp requires a signed integer\
    \ type\");\n    assert(int(a.size()) == int(b.size()));\n    for (const auto&\
    \ row : a) assert(int(row.size()) == int(c.size()));\n    assert(eps > 0);\n\n\
    \    detail::IntegerLpSolver<T> solver(a, b, c, true, eps);\n    return solver.solve();\n\
    }\n\ntemplate <class T>\nIntegerLpResult<T> integer_lp_minimize(const std::vector<std::vector<T>>&\
    \ a,\n                                       const std::vector<T>& b, const std::vector<T>&\
    \ c,\n                                       long double eps = 1e-10L) {\n   \
    \ static_assert(std::is_integral_v<T> && std::is_signed_v<T>,\n              \
    \    \"integer_lp requires a signed integer type\");\n    assert(int(a.size())\
    \ == int(b.size()));\n    for (const auto& row : a) assert(int(row.size()) ==\
    \ int(c.size()));\n    assert(eps > 0);\n\n    detail::IntegerLpSolver<T> solver(a,\
    \ b, c, false, eps);\n    return solver.solve();\n}\n\ntemplate <class T>\nIntegerLpResult<T>\
    \ integer_lp(const std::vector<std::vector<T>>& a, const std::vector<T>& b,\n\
    \                              const std::vector<T>& c, long double eps = 1e-10L)\
    \ {\n    return integer_lp_maximize(a, b, c, eps);\n}\n\n}  // namespace opt\n\
    }  // namespace m1une\n\n\n#line 1 \"optimization/project_selection.hpp\"\n\n\n\
    \n#line 9 \"optimization/project_selection.hpp\"\n\n#line 1 \"graph/flow/max_flow.hpp\"\
    \n\n\n\n#line 9 \"graph/flow/max_flow.hpp\"\n\nnamespace m1une {\nnamespace flow\
    \ {\n\ntemplate <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int\
    \ from;\n        int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n\
    \    struct InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n\
    \    };\n\n    struct Position {\n        int from;\n        int edge;\n    };\n\
    \n    int _n;\n    std::vector<Position> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n    Cap push_relabel(int s, int t) {\n        const int dead = 2 * _n;\n\
    \        const int unreachable = _n + 1;\n        std::vector<Cap> excess(_n,\
    \ Cap(0));\n        std::vector<int> state(8 * std::size_t(_n) + 2);\n       \
    \ int* height = state.data();\n        int* height_count = height + _n;\n    \
    \    int* current = height_count + dead + 1;\n        int* queue = current + _n;\n\
    \        int* next = queue + _n;\n        int* bucket_head = next + _n;\n    \
    \    std::vector<char> active(_n, false);\n        int highest = -1;\n       \
    \ long long work = 0;\n        long long arc_count = 0;\n        for (const auto&\
    \ edges : _g) arc_count += int(edges.size());\n        const long long work_limit\
    \ = std::max(1LL, 4 * arc_count + _n);\n\n        auto activate = [&](int v) {\n\
    \            if (v == s || v == t || active[v] || excess[v] == Cap(0) ||\n   \
    \             height[v] >= dead) {\n                return;\n            }\n \
    \           active[v] = true;\n            next[v] = bucket_head[height[v]];\n\
    \            bucket_head[height[v]] = v;\n            highest = std::max(highest,\
    \ height[v]);\n        };\n\n        auto rebuild_buckets = [&]() {\n        \
    \    std::fill(bucket_head, bucket_head + dead + 1, -1);\n            std::fill(active.begin(),\
    \ active.end(), false);\n            highest = -1;\n            for (int v = 0;\
    \ v < _n; v++) activate(v);\n        };\n\n        auto global_relabel = [&]()\
    \ {\n            std::fill(height, height + _n, unreachable);\n            std::fill(height_count,\
    \ height_count + dead + 1, 0);\n            std::fill(current, current + _n, 0);\n\
    \            int head = 0;\n            int tail = 0;\n            height[t] =\
    \ 0;\n            height[s] = _n;\n            queue[tail++] = t;\n          \
    \  while (head != tail) {\n                int v = queue[head++];\n          \
    \      for (const auto& e : _g[v]) {\n                    if (e.to == s || height[e.to]\
    \ != unreachable) continue;\n                    const auto& reverse = _g[e.to][e.rev];\n\
    \                    if (reverse.cap == Cap(0)) continue;\n                  \
    \  height[e.to] = height[v] + 1;\n                    queue[tail++] = e.to;\n\
    \                }\n            }\n            for (int v = 0; v < _n; v++) height_count[height[v]]++;\n\
    \            rebuild_buckets();\n            work = 0;\n        };\n\n       \
    \ auto gap = [&](int empty_height) {\n            for (int v = 0; v < _n; v++)\
    \ {\n                if (v == s || v == t || height[v] <= empty_height ||\n  \
    \                  height[v] >= _n) {\n                    continue;\n       \
    \         }\n                height_count[height[v]]--;\n                height[v]\
    \ = unreachable;\n                height_count[height[v]]++;\n               \
    \ current[v] = 0;\n            }\n            rebuild_buckets();\n        };\n\
    \n        auto relabel = [&](int v) -> bool {\n            int old_height = height[v];\n\
    \            int new_height = dead;\n            work += int(_g[v].size());\n\
    \            for (const auto& e : _g[v]) {\n                if (e.cap != Cap(0))\
    \ {\n                    new_height = std::min(new_height, height[e.to] + 1);\n\
    \                }\n            }\n            height_count[old_height]--;\n \
    \           height[v] = std::min(new_height, dead);\n            height_count[height[v]]++;\n\
    \            current[v] = 0;\n            if (old_height < _n && height_count[old_height]\
    \ == 0) {\n                gap(old_height);\n                return true;\n  \
    \          }\n            return false;\n        };\n\n        auto push = [&](int\
    \ v, InternalEdge& e) {\n            Cap sent = std::min(excess[v], e.cap);\n\
    \            bool was_zero = excess[e.to] == Cap(0);\n            e.cap -= sent;\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[v] -= sent;\n  \
    \          excess[e.to] += sent;\n            if (was_zero) activate(e.to);\n\
    \        };\n\n        auto discharge = [&](int v) {\n            while (excess[v]\
    \ != Cap(0) && height[v] < dead) {\n                if (current[v] == int(_g[v].size()))\
    \ {\n                    if (relabel(v)) return;\n                    continue;\n\
    \                }\n                auto& e = _g[v][current[v]];\n           \
    \     work++;\n                if (e.cap != Cap(0) && height[v] == height[e.to]\
    \ + 1) {\n                    push(v, e);\n                } else {\n        \
    \            current[v]++;\n                }\n            }\n            activate(v);\n\
    \        };\n\n        for (auto& e : _g[s]) {\n            if (e.to == s || e.cap\
    \ == Cap(0)) continue;\n            Cap sent = e.cap;\n            e.cap = Cap(0);\n\
    \            _g[e.to][e.rev].cap += sent;\n            excess[e.to] += sent;\n\
    \        }\n        global_relabel();\n\n        while (highest >= 0) {\n    \
    \        if (bucket_head[highest] == -1) {\n                highest--;\n     \
    \           continue;\n            }\n            int v = bucket_head[highest];\n\
    \            bucket_head[highest] = next[v];\n            if (!active[v] || height[v]\
    \ != highest) continue;\n            active[v] = false;\n            discharge(v);\n\
    \            if (work >= work_limit) global_relabel();\n        }\n        return\
    \ excess[t];\n    }\n\n   public:\n    MaxFlow() : MaxFlow(0) {}\n\n    explicit\
    \ MaxFlow(int n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    int edge_count() const {\n       \
    \ return int(_pos.size());\n    }\n\n    void reserve_edges(int edge_count) {\n\
    \        assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n       \
    \ if (_n == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count) <\
    \ std::size_t(_n)) {\n            return;\n        }\n        const std::size_t\
    \ average_degree =\n            (3 * std::size_t(edge_count) + std::size_t(_n)\
    \ - 1)\n            / std::size_t(_n);\n        for (auto& edges : _g) edges.reserve(average_degree);\n\
    \    }\n\n    void reserve_edges(int edge_count, const std::vector<int>& degrees)\
    \ {\n        assert(0 <= edge_count);\n        assert(int(degrees.size()) == _n);\n\
    \        _pos.reserve(edge_count);\n        for (int v = 0; v < _n; v++) {\n \
    \           assert(0 <= degrees[v]);\n            _g[v].reserve(degrees[v]);\n\
    \        }\n    }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0\
    \ <= from && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0)\
    \ <= cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.push_back(Position{from, from_id});\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    int add_undirected_edge(int first, int second,\
    \ Cap cap) {\n        static_assert(std::numeric_limits<Cap>::is_signed);\n  \
    \      assert(0 <= first && first < _n);\n        assert(0 <= second && second\
    \ < _n);\n        assert(Cap(0) <= cap);\n        assert(cap <= std::numeric_limits<Cap>::max()\
    \ / Cap(2));\n        int id = int(_pos.size());\n        int first_id = int(_g[first].size());\n\
    \        int second_id = int(_g[second].size());\n        if (first == second)\
    \ second_id++;\n        _pos.push_back(Position{first, ~first_id});\n        _g[first].push_back(InternalEdge{second,\
    \ second_id, cap});\n        _g[second].push_back(InternalEdge{first, first_id,\
    \ cap});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n    \
    \    assert(0 <= i && i < int(_pos.size()));\n        const auto& position = _pos[i];\n\
    \        int from = position.from;\n        bool undirected = position.edge <\
    \ 0;\n        int idx = undirected ? ~position.edge : position.edge;\n       \
    \ const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        if (undirected) {\n            return Edge{\n                from,\n\
    \                e.to,\n                (e.cap + re.cap) / Cap(2),\n         \
    \       (re.cap - e.cap) / Cap(2)\n            };\n        }\n        return Edge{from,\
    \ e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge> edges() const\
    \ {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_cap);\n        auto& position = _pos[i];\n        int from = position.from;\n\
    \        bool undirected = position.edge < 0;\n        int idx = undirected ?\
    \ ~position.edge : position.edge;\n        auto& e = _g[from][idx];\n        auto&\
    \ re = _g[e.to][e.rev];\n        if (undirected) {\n            assert(new_cap\
    \ <= std::numeric_limits<Cap>::max() / Cap(2));\n            assert(-new_cap <=\
    \ new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_cap + new_flow;\n        } else {\n            assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_flow;\n        }\n    }\n\n    Cap max_flow(int s, int\
    \ t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\
    \n    Cap max_flow_push_relabel(int s, int t) {\n        assert(0 <= s && s <\
    \ _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n        return\
    \ push_relabel(s, t);\n    }\n\n    Cap max_flow(int s, int t, Cap flow_limit)\
    \ {\n        assert(0 <= s && s < _n);\n        assert(0 <= t && t < _n);\n  \
    \      assert(s != t);\n\n        std::vector<int> work(3 * std::size_t(_n));\n\
    \        int* level = work.data();\n        int* iter = level + _n;\n        int*\
    \ queue = iter + _n;\n        auto bfs = [&]() -> bool {\n            std::fill(level,\
    \ level + _n, -1);\n            int head = 0;\n            int tail = 0;\n   \
    \         level[s] = 0;\n            queue[tail++] = s;\n            while (head\
    \ != tail) {\n                int v = queue[head++];\n                for (const\
    \ auto& e : _g[v]) {\n                    if (level[e.to] != -1 || e.cap == Cap(0))\
    \ continue;\n                    level[e.to] = level[v] + 1;\n               \
    \     if (e.to == t) return true;\n                    queue[tail++] = e.to;\n\
    \                }\n            }\n            return level[t] != -1;\n      \
    \  };\n\n        auto dfs = [&](auto&& self, int v, Cap up) -> Cap {\n       \
    \     if (v == s) return up;\n            Cap result = Cap(0);\n            const\
    \ int current_level = level[v];\n            auto& edges = _g[v];\n          \
    \  const int edge_count = int(edges.size());\n            for (int& i = iter[v];\
    \ i < edge_count; i++) {\n                auto& e = edges[i];\n              \
    \  if (level[e.to] + 1 != current_level) continue;\n                auto& reverse\
    \ = _g[e.to][e.rev];\n                if (reverse.cap == Cap(0)) continue;\n \
    \               Cap d = self(\n                    self,\n                   \
    \ e.to,\n                    std::min(up - result, reverse.cap)\n            \
    \    );\n                if (d == Cap(0)) continue;\n                e.cap +=\
    \ d;\n                reverse.cap -= d;\n                result += d;\n      \
    \          if (result == up) return result;\n            }\n            level[v]\
    \ = _n;\n            return result;\n        };\n\n        Cap flow = 0;\n   \
    \     while (flow < flow_limit && bfs()) {\n            std::fill(iter, iter +\
    \ _n, 0);\n            flow += dfs(dfs, t, flow_limit - flow);\n        }\n  \
    \      return flow;\n    }\n\n    std::vector<bool> min_cut(int s) const {\n \
    \       assert(0 <= s && s < _n);\n        std::vector<bool> visited(_n, false);\n\
    \        std::vector<int> queue(_n);\n        int head = 0;\n        int tail\
    \ = 0;\n        visited[s] = true;\n        queue[tail++] = s;\n        while\
    \ (head != tail) {\n            int v = queue[head++];\n            for (const\
    \ auto& e : _g[v]) {\n                if (e.cap == Cap(0) || visited[e.to]) continue;\n\
    \                visited[e.to] = true;\n                queue[tail++] = e.to;\n\
    \            }\n        }\n        return visited;\n    }\n};\n\n}  // namespace\
    \ flow\n}  // namespace m1une\n\n\n#line 11 \"optimization/project_selection.hpp\"\
    \n\nnamespace m1une {\nnamespace opt {\n\ntemplate <class T>\nstruct ProjectSelectionResult\
    \ {\n    bool feasible;\n    T max_gain;\n    std::vector<bool> selected;\n\n\
    \    bool is_feasible() const {\n        return feasible;\n    }\n};\n\ntemplate\
    \ <class T>\nclass ProjectSelection {\n    static_assert(std::is_integral_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct Arc {\n        int from;\n        int\
    \ to;\n        T cap;\n    };\n\n    static constexpr int source = -1;\n    static\
    \ constexpr int sink = -2;\n\n    int _project_count;\n    int _vertex_count;\n\
    \    T _offset = T();\n    T _finite_cap_sum = T();\n    std::vector<Arc> _arcs;\n\
    \    std::vector<std::pair<int, int>> _hard_arcs;\n\n    void assert_project(int\
    \ project) const {\n        (void)project;\n        assert(0 <= project && project\
    \ < _project_count);\n    }\n\n    void assert_vertex(int vertex) const {\n  \
    \      (void)vertex;\n        assert(0 <= vertex && vertex < _vertex_count);\n\
    \    }\n\n    void add_offset(T value) {\n        if (value > T()) {\n       \
    \     assert(_offset <= std::numeric_limits<T>::max() - value);\n        } else\
    \ if (value < T()) {\n            assert(_offset >= std::numeric_limits<T>::lowest()\
    \ - value);\n        }\n        _offset += value;\n    }\n\n    T nonnegative_difference(T\
    \ large, T small) const {\n        assert(small <= large);\n        if (small\
    \ < T()) {\n            assert(large <= std::numeric_limits<T>::max() + small);\n\
    \        }\n        return large - small;\n    }\n\n    void add_arc(int from,\
    \ int to, T cap) {\n        assert(cap >= T());\n        if (from == to) return;\n\
    \        assert(cap <= std::numeric_limits<T>::max() - _finite_cap_sum);\n   \
    \     _finite_cap_sum += cap;\n        _arcs.push_back(Arc{from, to, cap});\n\
    \    }\n\n    void add_hard_arc(int from, int to) {\n        if (from == to) return;\n\
    \        _hard_arcs.emplace_back(from, to);\n    }\n\n    void add_vertex_gain(int\
    \ vertex, T gain_if_selected, T gain_if_unselected) {\n        assert_vertex(vertex);\n\
    \        if (gain_if_selected >= gain_if_unselected) {\n            add_offset(gain_if_selected);\n\
    \            add_arc(source, vertex,\n                    nonnegative_difference(gain_if_selected,\
    \ gain_if_unselected));\n        } else {\n            add_offset(gain_if_unselected);\n\
    \            add_arc(vertex, sink,\n                    nonnegative_difference(gain_if_unselected,\
    \ gain_if_selected));\n        }\n    }\n\n    int add_auxiliary_vertex() {\n\
    \        return _vertex_count++;\n    }\n\n   public:\n    ProjectSelection()\
    \ : ProjectSelection(0) {}\n\n    explicit ProjectSelection(int project_count)\n\
    \        : _project_count(project_count), _vertex_count(project_count) {\n   \
    \     assert(project_count >= 0);\n    }\n\n    int size() const {\n        return\
    \ _project_count;\n    }\n\n    void add_gain(int project, T gain_if_selected)\
    \ {\n        add_gain(project, gain_if_selected, T());\n    }\n\n    void add_gain(int\
    \ project, T gain_if_selected, T gain_if_unselected) {\n        assert_project(project);\n\
    \        add_vertex_gain(project, gain_if_selected, gain_if_unselected);\n   \
    \ }\n\n    void add_penalty(int selected_project, int unselected_project, T penalty)\
    \ {\n        assert_project(selected_project);\n        assert_project(unselected_project);\n\
    \        add_arc(selected_project, unselected_project, penalty);\n    }\n\n  \
    \  void add_penalty_if_different(int project_a, int project_b, T penalty) {\n\
    \        assert_project(project_a);\n        assert_project(project_b);\n    \
    \    add_arc(project_a, project_b, penalty);\n        add_arc(project_b, project_a,\
    \ penalty);\n    }\n\n    void add_gain_if_same(int project_a, int project_b,\
    \ T gain) {\n        assert(gain >= T());\n        add_offset(gain);\n       \
    \ add_penalty_if_different(project_a, project_b, gain);\n    }\n\n    void add_hard_implication(int\
    \ selected_project, int required_project) {\n        assert_project(selected_project);\n\
    \        assert_project(required_project);\n        add_hard_arc(selected_project,\
    \ required_project);\n    }\n\n    void force_selected(int project) {\n      \
    \  assert_project(project);\n        add_hard_arc(source, project);\n    }\n\n\
    \    void force_unselected(int project) {\n        assert_project(project);\n\
    \        add_hard_arc(project, sink);\n    }\n\n    void add_gain_if_all_selected(const\
    \ std::vector<int>& projects, T gain) {\n        assert(gain >= T());\n      \
    \  for (int project : projects) assert_project(project);\n        if (projects.empty())\
    \ {\n            add_offset(gain);\n            return;\n        }\n        if\
    \ (projects.size() == 1) {\n            add_vertex_gain(projects[0], gain, T());\n\
    \            return;\n        }\n        if (projects.size() == 2) {\n       \
    \     add_vertex_gain(projects[0], gain, T());\n            add_arc(projects[0],\
    \ projects[1], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, gain, T());\n\
    \        for (int project : projects) add_hard_arc(auxiliary, project);\n    }\n\
    \n    void add_gain_if_all_unselected(const std::vector<int>& projects, T gain)\
    \ {\n        assert(gain >= T());\n        for (int project : projects) assert_project(project);\n\
    \        if (projects.empty()) {\n            add_offset(gain);\n            return;\n\
    \        }\n        if (projects.size() == 1) {\n            add_vertex_gain(projects[0],\
    \ T(), gain);\n            return;\n        }\n        if (projects.size() ==\
    \ 2) {\n            add_vertex_gain(projects[0], T(), gain);\n            add_arc(projects[1],\
    \ projects[0], gain);\n            return;\n        }\n\n        int auxiliary\
    \ = add_auxiliary_vertex();\n        add_vertex_gain(auxiliary, T(), gain);\n\
    \        for (int project : projects) add_hard_arc(project, auxiliary);\n    }\n\
    \n    ProjectSelectionResult<T> solve() const {\n        int s = _vertex_count;\n\
    \        int t = s + 1;\n        flow::MaxFlow<T> max_flow(_vertex_count + 2);\n\
    \n        auto vertex_id = [&](int vertex) {\n            if (vertex == source)\
    \ return s;\n            if (vertex == sink) return t;\n            return vertex;\n\
    \        };\n\n        for (const auto& arc : _arcs) {\n            max_flow.add_edge(vertex_id(arc.from),\
    \ vertex_id(arc.to), arc.cap);\n        }\n\n        T hard_cap = T();\n     \
    \   if (!_hard_arcs.empty()) {\n            assert(_finite_cap_sum < std::numeric_limits<T>::max());\n\
    \            hard_cap = _finite_cap_sum + T(1);\n            for (auto [from,\
    \ to] : _hard_arcs) {\n                max_flow.add_edge(vertex_id(from), vertex_id(to),\
    \ hard_cap);\n            }\n        }\n\n        T cut_cost =\n            _hard_arcs.empty()\
    \ ? max_flow.max_flow(s, t) : max_flow.max_flow(s, t, hard_cap);\n        ProjectSelectionResult<T>\
    \ result;\n        result.feasible = _hard_arcs.empty() || cut_cost < hard_cap;\n\
    \        result.max_gain = T();\n        result.selected.assign(_project_count,\
    \ false);\n        if (!result.feasible) return result;\n\n        assert(_offset\
    \ >= std::numeric_limits<T>::lowest() + cut_cost);\n        result.max_gain =\
    \ _offset - cut_cost;\n        auto source_side = max_flow.min_cut(s);\n     \
    \   for (int project = 0; project < _project_count; project++) {\n           \
    \ result.selected[project] = source_side[project];\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace opt\n}  // namespace m1une\n\n\n#line\
    \ 8 \"optimization/all.hpp\"\n\n\n#line 9 \"verify/optimization/integer_lp.test.cpp\"\
    \n\nlong long evaluate(const std::vector<long long>& c, const std::vector<long\
    \ long>& x) {\n    long long result = 0;\n    for (int i = 0; i < int(c.size());\
    \ i++) result += c[i] * x[i];\n    return result;\n}\n\nbool feasible(const std::vector<std::vector<long\
    \ long>>& a, const std::vector<long long>& b,\n              const std::vector<long\
    \ long>& x) {\n    for (long long value : x) {\n        if (value < 0) return\
    \ false;\n    }\n    for (int i = 0; i < int(a.size()); i++) {\n        long long\
    \ lhs = 0;\n        for (int j = 0; j < int(x.size()); j++) lhs += a[i][j] * x[j];\n\
    \        if (lhs > b[i]) return false;\n    }\n    return true;\n}\n\nvoid brute_dfs(const\
    \ std::vector<std::vector<long long>>& a, const std::vector<long long>& b,\n \
    \              const std::vector<long long>& c, const std::vector<long long>&\
    \ limits, int index,\n               std::vector<long long>& current, bool maximize,\
    \ bool& found, long long& best) {\n    if (index == int(c.size())) {\n       \
    \ if (!feasible(a, b, current)) return;\n        long long value = evaluate(c,\
    \ current);\n        if (!found || (maximize ? value > best : value < best)) {\n\
    \            found = true;\n            best = value;\n        }\n        return;\n\
    \    }\n    for (long long value = 0; value <= limits[index]; value++) {\n   \
    \     current[index] = value;\n        brute_dfs(a, b, c, limits, index + 1, current,\
    \ maximize, found, best);\n    }\n}\n\nlong long brute_solve(const std::vector<std::vector<long\
    \ long>>& a,\n                      const std::vector<long long>& b, const std::vector<long\
    \ long>& c,\n                      const std::vector<long long>& limits, bool\
    \ maximize) {\n    bool found = false;\n    long long best = 0;\n    std::vector<long\
    \ long> current(c.size(), 0);\n    brute_dfs(a, b, c, limits, 0, current, maximize,\
    \ found, best);\n    assert(found);\n    return best;\n}\n\nvoid check_optimal(const\
    \ std::vector<std::vector<long long>>& a,\n                   const std::vector<long\
    \ long>& b, const std::vector<long long>& c,\n                   const m1une::opt::IntegerLpResult<long\
    \ long>& result,\n                   long long expected) {\n    assert(result.is_optimal());\n\
    \    assert(feasible(a, b, result.variables));\n    assert(result.objective_value\
    \ == expected);\n    assert(evaluate(c, result.variables) == expected);\n}\n\n\
    void test_basic_maximize() {\n    std::vector<std::vector<long long>> a;\n   \
    \ a.emplace_back(std::vector<long long>{2, 1});\n    a.emplace_back(std::vector<long\
    \ long>{1, 2});\n    std::vector<long long> b = {4, 4};\n    std::vector<long\
    \ long> c = {3, 2};\n\n    auto result = m1une::opt::integer_lp_maximize(a, b,\
    \ c);\n    check_optimal(a, b, c, result, 6);\n\n    auto alias_result = m1une::opt::integer_lp(a,\
    \ b, c);\n    check_optimal(a, b, c, alias_result, 6);\n}\n\nvoid test_minimize()\
    \ {\n    std::vector<std::vector<long long>> a;\n    a.emplace_back(std::vector<long\
    \ long>{-1, -1});\n    a.emplace_back(std::vector<long long>{1, 0});\n    a.emplace_back(std::vector<long\
    \ long>{0, 1});\n    std::vector<long long> b = {-3, 5, 5};\n    std::vector<long\
    \ long> c = {1, 1};\n\n    auto result = m1une::opt::integer_lp_minimize(a, b,\
    \ c);\n    check_optimal(a, b, c, result, 3);\n}\n\nvoid test_integer_infeasible_fractional_relaxation()\
    \ {\n    std::vector<std::vector<long long>> a;\n    a.emplace_back(std::vector<long\
    \ long>{2});\n    a.emplace_back(std::vector<long long>{-2});\n    std::vector<long\
    \ long> b = {1, -1};\n    std::vector<long long> c = {1};\n\n    auto result =\
    \ m1une::opt::integer_lp_maximize(a, b, c);\n    assert(result.is_infeasible());\n\
    }\n\nvoid test_unbounded() {\n    std::vector<std::vector<long long>> a;\n   \
    \ a.emplace_back(std::vector<long long>{-1});\n    std::vector<long long> b =\
    \ {-1};\n    std::vector<long long> c = {1};\n\n    auto result = m1une::opt::integer_lp_maximize(a,\
    \ b, c);\n    assert(result.is_unbounded());\n    assert(feasible(a, b, result.variables));\n\
    }\n\nvoid test_unbounded_relaxation_but_integer_infeasible() {\n    std::vector<std::vector<long\
    \ long>> a;\n    a.emplace_back(std::vector<long long>{2, 0});\n    a.emplace_back(std::vector<long\
    \ long>{-2, 0});\n    std::vector<long long> b = {1, -1};\n    std::vector<long\
    \ long> c = {0, 1};\n\n    auto result = m1une::opt::integer_lp_maximize(a, b,\
    \ c);\n    assert(result.is_infeasible());\n}\n\nvoid test_no_variables() {\n\
    \    std::vector<std::vector<long long>> a(2);\n    std::vector<long long> b =\
    \ {0, 3};\n    std::vector<long long> c;\n\n    auto result = m1une::opt::integer_lp_maximize(a,\
    \ b, c);\n    assert(result.is_optimal());\n    assert(result.variables.empty());\n\
    \    assert(result.objective_value == 0);\n\n    std::vector<std::vector<long\
    \ long>> bad_a(1);\n    std::vector<long long> bad_b = {-1};\n    auto bad_result\
    \ = m1une::opt::integer_lp_maximize(bad_a, bad_b, c);\n    assert(bad_result.is_infeasible());\n\
    }\n\nvoid test_against_bruteforce() {\n    for (int t = 0; t < 20; t++) {\n  \
    \      std::vector<std::vector<long long>> a;\n        std::vector<long long>\
    \ b;\n        std::vector<long long> limits;\n        int variable_count = 3;\n\
    \n        for (int j = 0; j < variable_count; j++) {\n            long long limit\
    \ = 2 + (t + j * 2) % 4;\n            limits.push_back(limit);\n            std::vector<long\
    \ long> row(variable_count, 0);\n            row[j] = 1;\n            a.push_back(row);\n\
    \            b.push_back(limit);\n        }\n\n        for (int i = 0; i < 4;\
    \ i++) {\n            std::vector<long long> row(variable_count, 0);\n       \
    \     for (int j = 0; j < variable_count; j++) {\n                row[j] = (t\
    \ * 3 + i * 5 + j * 7) % 7 - 3;\n            }\n            long long rhs = 3\
    \ + (t * 2 + i * 4) % 9;\n            a.push_back(row);\n            b.push_back(rhs);\n\
    \        }\n\n        std::vector<long long> c(variable_count, 0);\n        for\
    \ (int j = 0; j < variable_count; j++) c[j] = (t * 5 + j * 3) % 11 - 5;\n\n  \
    \      long long expected_max = brute_solve(a, b, c, limits, true);\n        auto\
    \ max_result = m1une::opt::integer_lp_maximize(a, b, c);\n        check_optimal(a,\
    \ b, c, max_result, expected_max);\n\n        long long expected_min = brute_solve(a,\
    \ b, c, limits, false);\n        auto min_result = m1une::opt::integer_lp_minimize(a,\
    \ b, c);\n        check_optimal(a, b, c, min_result, expected_min);\n    }\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic_maximize();\n    test_minimize();\n    test_integer_infeasible_fractional_relaxation();\n\
    \    test_unbounded();\n    test_unbounded_relaxation_but_integer_infeasible();\n\
    \    test_no_variables();\n    test_against_bruteforce();\n\n    long long a,\
    \ b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include \"../../utilities/fast_io.hpp\"\n#include <limits>\n#include <vector>\n\
    \n#include \"../../optimization/all.hpp\"\n\nlong long evaluate(const std::vector<long\
    \ long>& c, const std::vector<long long>& x) {\n    long long result = 0;\n  \
    \  for (int i = 0; i < int(c.size()); i++) result += c[i] * x[i];\n    return\
    \ result;\n}\n\nbool feasible(const std::vector<std::vector<long long>>& a, const\
    \ std::vector<long long>& b,\n              const std::vector<long long>& x) {\n\
    \    for (long long value : x) {\n        if (value < 0) return false;\n    }\n\
    \    for (int i = 0; i < int(a.size()); i++) {\n        long long lhs = 0;\n \
    \       for (int j = 0; j < int(x.size()); j++) lhs += a[i][j] * x[j];\n     \
    \   if (lhs > b[i]) return false;\n    }\n    return true;\n}\n\nvoid brute_dfs(const\
    \ std::vector<std::vector<long long>>& a, const std::vector<long long>& b,\n \
    \              const std::vector<long long>& c, const std::vector<long long>&\
    \ limits, int index,\n               std::vector<long long>& current, bool maximize,\
    \ bool& found, long long& best) {\n    if (index == int(c.size())) {\n       \
    \ if (!feasible(a, b, current)) return;\n        long long value = evaluate(c,\
    \ current);\n        if (!found || (maximize ? value > best : value < best)) {\n\
    \            found = true;\n            best = value;\n        }\n        return;\n\
    \    }\n    for (long long value = 0; value <= limits[index]; value++) {\n   \
    \     current[index] = value;\n        brute_dfs(a, b, c, limits, index + 1, current,\
    \ maximize, found, best);\n    }\n}\n\nlong long brute_solve(const std::vector<std::vector<long\
    \ long>>& a,\n                      const std::vector<long long>& b, const std::vector<long\
    \ long>& c,\n                      const std::vector<long long>& limits, bool\
    \ maximize) {\n    bool found = false;\n    long long best = 0;\n    std::vector<long\
    \ long> current(c.size(), 0);\n    brute_dfs(a, b, c, limits, 0, current, maximize,\
    \ found, best);\n    assert(found);\n    return best;\n}\n\nvoid check_optimal(const\
    \ std::vector<std::vector<long long>>& a,\n                   const std::vector<long\
    \ long>& b, const std::vector<long long>& c,\n                   const m1une::opt::IntegerLpResult<long\
    \ long>& result,\n                   long long expected) {\n    assert(result.is_optimal());\n\
    \    assert(feasible(a, b, result.variables));\n    assert(result.objective_value\
    \ == expected);\n    assert(evaluate(c, result.variables) == expected);\n}\n\n\
    void test_basic_maximize() {\n    std::vector<std::vector<long long>> a;\n   \
    \ a.emplace_back(std::vector<long long>{2, 1});\n    a.emplace_back(std::vector<long\
    \ long>{1, 2});\n    std::vector<long long> b = {4, 4};\n    std::vector<long\
    \ long> c = {3, 2};\n\n    auto result = m1une::opt::integer_lp_maximize(a, b,\
    \ c);\n    check_optimal(a, b, c, result, 6);\n\n    auto alias_result = m1une::opt::integer_lp(a,\
    \ b, c);\n    check_optimal(a, b, c, alias_result, 6);\n}\n\nvoid test_minimize()\
    \ {\n    std::vector<std::vector<long long>> a;\n    a.emplace_back(std::vector<long\
    \ long>{-1, -1});\n    a.emplace_back(std::vector<long long>{1, 0});\n    a.emplace_back(std::vector<long\
    \ long>{0, 1});\n    std::vector<long long> b = {-3, 5, 5};\n    std::vector<long\
    \ long> c = {1, 1};\n\n    auto result = m1une::opt::integer_lp_minimize(a, b,\
    \ c);\n    check_optimal(a, b, c, result, 3);\n}\n\nvoid test_integer_infeasible_fractional_relaxation()\
    \ {\n    std::vector<std::vector<long long>> a;\n    a.emplace_back(std::vector<long\
    \ long>{2});\n    a.emplace_back(std::vector<long long>{-2});\n    std::vector<long\
    \ long> b = {1, -1};\n    std::vector<long long> c = {1};\n\n    auto result =\
    \ m1une::opt::integer_lp_maximize(a, b, c);\n    assert(result.is_infeasible());\n\
    }\n\nvoid test_unbounded() {\n    std::vector<std::vector<long long>> a;\n   \
    \ a.emplace_back(std::vector<long long>{-1});\n    std::vector<long long> b =\
    \ {-1};\n    std::vector<long long> c = {1};\n\n    auto result = m1une::opt::integer_lp_maximize(a,\
    \ b, c);\n    assert(result.is_unbounded());\n    assert(feasible(a, b, result.variables));\n\
    }\n\nvoid test_unbounded_relaxation_but_integer_infeasible() {\n    std::vector<std::vector<long\
    \ long>> a;\n    a.emplace_back(std::vector<long long>{2, 0});\n    a.emplace_back(std::vector<long\
    \ long>{-2, 0});\n    std::vector<long long> b = {1, -1};\n    std::vector<long\
    \ long> c = {0, 1};\n\n    auto result = m1une::opt::integer_lp_maximize(a, b,\
    \ c);\n    assert(result.is_infeasible());\n}\n\nvoid test_no_variables() {\n\
    \    std::vector<std::vector<long long>> a(2);\n    std::vector<long long> b =\
    \ {0, 3};\n    std::vector<long long> c;\n\n    auto result = m1une::opt::integer_lp_maximize(a,\
    \ b, c);\n    assert(result.is_optimal());\n    assert(result.variables.empty());\n\
    \    assert(result.objective_value == 0);\n\n    std::vector<std::vector<long\
    \ long>> bad_a(1);\n    std::vector<long long> bad_b = {-1};\n    auto bad_result\
    \ = m1une::opt::integer_lp_maximize(bad_a, bad_b, c);\n    assert(bad_result.is_infeasible());\n\
    }\n\nvoid test_against_bruteforce() {\n    for (int t = 0; t < 20; t++) {\n  \
    \      std::vector<std::vector<long long>> a;\n        std::vector<long long>\
    \ b;\n        std::vector<long long> limits;\n        int variable_count = 3;\n\
    \n        for (int j = 0; j < variable_count; j++) {\n            long long limit\
    \ = 2 + (t + j * 2) % 4;\n            limits.push_back(limit);\n            std::vector<long\
    \ long> row(variable_count, 0);\n            row[j] = 1;\n            a.push_back(row);\n\
    \            b.push_back(limit);\n        }\n\n        for (int i = 0; i < 4;\
    \ i++) {\n            std::vector<long long> row(variable_count, 0);\n       \
    \     for (int j = 0; j < variable_count; j++) {\n                row[j] = (t\
    \ * 3 + i * 5 + j * 7) % 7 - 3;\n            }\n            long long rhs = 3\
    \ + (t * 2 + i * 4) % 9;\n            a.push_back(row);\n            b.push_back(rhs);\n\
    \        }\n\n        std::vector<long long> c(variable_count, 0);\n        for\
    \ (int j = 0; j < variable_count; j++) c[j] = (t * 5 + j * 3) % 11 - 5;\n\n  \
    \      long long expected_max = brute_solve(a, b, c, limits, true);\n        auto\
    \ max_result = m1une::opt::integer_lp_maximize(a, b, c);\n        check_optimal(a,\
    \ b, c, max_result, expected_max);\n\n        long long expected_min = brute_solve(a,\
    \ b, c, limits, false);\n        auto min_result = m1une::opt::integer_lp_minimize(a,\
    \ b, c);\n        check_optimal(a, b, c, min_result, expected_min);\n    }\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic_maximize();\n    test_minimize();\n    test_integer_infeasible_fractional_relaxation();\n\
    \    test_unbounded();\n    test_unbounded_relaxation_but_integer_infeasible();\n\
    \    test_no_variables();\n    test_against_bruteforce();\n\n    long long a,\
    \ b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - optimization/all.hpp
  - optimization/hungarian.hpp
  - optimization/integer_lp.hpp
  - optimization/simplex.hpp
  - optimization/project_selection.hpp
  - graph/flow/max_flow.hpp
  isVerificationFile: true
  path: verify/optimization/integer_lp.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 22:14:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/integer_lp.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/integer_lp.test.cpp
- /verify/verify/optimization/integer_lp.test.cpp.html
title: verify/optimization/integer_lp.test.cpp
---
