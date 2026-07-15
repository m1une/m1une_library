---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: optimization/hungarian.hpp
    title: Hungarian Algorithm
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
    PROBLEM: https://judge.yosupo.jp/problem/assignment
    links:
    - https://judge.yosupo.jp/problem/assignment
  bundledCode: "#line 1 \"verify/optimization/hungarian.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/assignment\"\n\n#include <algorithm>\n#include\
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
    \ m1une\n\n\n#line 6 \"verify/optimization/hungarian.test.cpp\"\n#include <limits>\n\
    #include <vector>\n\n#line 1 \"optimization/hungarian.hpp\"\n\n\n\n#line 9 \"\
    optimization/hungarian.hpp\"\n\nnamespace m1une {\nnamespace opt {\n\ntemplate\
    \ <class T>\nstruct HungarianResult {\n    T cost;\n    std::vector<int> row_to_col;\n\
    \    std::vector<int> col_to_row;\n\n    int matching_size() const {\n       \
    \ int result = 0;\n        for (int col : row_to_col) {\n            if (col !=\
    \ -1) result++;\n        }\n        return result;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> matching() const {\n        std::vector<std::pair<int, int>> result;\n\
    \        for (int row = 0; row < int(row_to_col.size()); row++) {\n          \
    \  if (row_to_col[row] != -1) result.push_back({row, row_to_col[row]});\n    \
    \    }\n        return result;\n    }\n};\n\nnamespace detail {\n\ntemplate <class\
    \ T>\nT assignment_cost(const std::vector<std::vector<T>>& cost, const std::vector<int>&\
    \ row_to_col) {\n    T result = T();\n    for (int row = 0; row < int(row_to_col.size());\
    \ row++) {\n        if (row_to_col[row] != -1) result += cost[row][row_to_col[row]];\n\
    \    }\n    return result;\n}\n\n}  // namespace detail\n\ntemplate <class T>\n\
    HungarianResult<T> hungarian_min(const std::vector<std::vector<T>>& cost) {\n\
    \    int row_count = int(cost.size());\n    int col_count = row_count == 0 ? 0\
    \ : int(cost[0].size());\n    for (const auto& row : cost) assert(int(row.size())\
    \ == col_count);\n\n    HungarianResult<T> result;\n    result.cost = T();\n \
    \   result.row_to_col.assign(row_count, -1);\n    result.col_to_row.assign(col_count,\
    \ -1);\n    if (row_count == 0 || col_count == 0) return result;\n\n    bool transposed\
    \ = row_count > col_count;\n    int n = transposed ? col_count : row_count;\n\
    \    int m = transposed ? row_count : col_count;\n    T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n\n    std::vector<T> u(n + 1, T()), v(m + 1, T()), minv(m + 1);\n \
    \   std::vector<int> p(m + 1, 0), way(m + 1, 0);\n\n    auto value = [&](int i,\
    \ int j) -> T {\n        return transposed ? cost[j][i] : cost[i][j];\n    };\n\
    \n    for (int i = 1; i <= n; i++) {\n        p[0] = i;\n        int j0 = 0;\n\
    \        std::fill(minv.begin(), minv.end(), inf);\n        std::vector<char>\
    \ used(m + 1, false);\n\n        do {\n            used[j0] = true;\n        \
    \    int i0 = p[j0];\n            int j1 = 0;\n            T delta = inf;\n\n\
    \            for (int j = 1; j <= m; j++) {\n                if (used[j]) continue;\n\
    \                T cur = value(i0 - 1, j - 1) - u[i0] - v[j];\n              \
    \  if (cur < minv[j]) {\n                    minv[j] = cur;\n                \
    \    way[j] = j0;\n                }\n                if (minv[j] < delta) {\n\
    \                    delta = minv[j];\n                    j1 = j;\n         \
    \       }\n            }\n\n            for (int j = 0; j <= m; j++) {\n     \
    \           if (used[j]) {\n                    u[p[j]] += delta;\n          \
    \          v[j] -= delta;\n                } else {\n                    minv[j]\
    \ -= delta;\n                }\n            }\n            j0 = j1;\n        }\
    \ while (p[j0] != 0);\n\n        do {\n            int j1 = way[j0];\n       \
    \     p[j0] = p[j1];\n            j0 = j1;\n        } while (j0 != 0);\n    }\n\
    \n    for (int j = 1; j <= m; j++) {\n        if (p[j] == 0) continue;\n     \
    \   int i = p[j] - 1;\n        int matched = j - 1;\n        if (transposed) {\n\
    \            int row = matched;\n            int col = i;\n            result.row_to_col[row]\
    \ = col;\n            result.col_to_row[col] = row;\n        } else {\n      \
    \      int row = i;\n            int col = matched;\n            result.row_to_col[row]\
    \ = col;\n            result.col_to_row[col] = row;\n        }\n    }\n    result.cost\
    \ = detail::assignment_cost(cost, result.row_to_col);\n    return result;\n}\n\
    \ntemplate <class T>\nHungarianResult<T> hungarian_max(const std::vector<std::vector<T>>&\
    \ cost) {\n    std::vector<std::vector<T>> negated = cost;\n    for (auto& row\
    \ : negated) {\n        for (auto& x : row) x = -x;\n    }\n    auto result =\
    \ hungarian_min(negated);\n    result.cost = detail::assignment_cost(cost, result.row_to_col);\n\
    \    return result;\n}\n\ntemplate <class T>\nHungarianResult<T> hungarian(const\
    \ std::vector<std::vector<T>>& cost) {\n    return hungarian_min(cost);\n}\n\n\
    }  // namespace opt\n}  // namespace m1une\n\n\n#line 10 \"verify/optimization/hungarian.test.cpp\"\
    \n\nlong long brute_min(const std::vector<std::vector<long long>>& cost) {\n \
    \   int h = int(cost.size());\n    int w = h == 0 ? 0 : int(cost[0].size());\n\
    \    if (h == 0 || w == 0) return 0;\n\n    long long best = std::numeric_limits<long\
    \ long>::max() / 4;\n    if (h <= w) {\n        std::vector<int> perm(w);\n  \
    \      for (int i = 0; i < w; i++) perm[i] = i;\n        do {\n            long\
    \ long sum = 0;\n            for (int i = 0; i < h; i++) sum += cost[i][perm[i]];\n\
    \            best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    } else {\n        std::vector<int> perm(h);\n        for\
    \ (int i = 0; i < h; i++) perm[i] = i;\n        do {\n            long long sum\
    \ = 0;\n            for (int j = 0; j < w; j++) sum += cost[perm[j]][j];\n   \
    \         best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    }\n    return best;\n}\n\nlong long brute_max(const std::vector<std::vector<long\
    \ long>>& cost) {\n    std::vector<std::vector<long long>> negated = cost;\n \
    \   for (auto& row : negated) {\n        for (auto& x : row) x = -x;\n    }\n\
    \    return -brute_min(negated);\n}\n\nvoid check_result(const std::vector<std::vector<long\
    \ long>>& cost,\n                  const m1une::opt::HungarianResult<long long>&\
    \ result,\n                  long long expected) {\n    int h = int(cost.size());\n\
    \    int w = h == 0 ? 0 : int(cost[0].size());\n    assert(int(result.row_to_col.size())\
    \ == h);\n    assert(int(result.col_to_row.size()) == w);\n    assert(result.matching_size()\
    \ == std::min(h, w));\n    assert(result.cost == expected);\n\n    std::vector<bool>\
    \ used_cols(w, false);\n    long long sum = 0;\n    for (int i = 0; i < h; i++)\
    \ {\n        int j = result.row_to_col[i];\n        if (j == -1) continue;\n \
    \       assert(0 <= j && j < w);\n        assert(!used_cols[j]);\n        assert(result.col_to_row[j]\
    \ == i);\n        used_cols[j] = true;\n        sum += cost[i][j];\n    }\n  \
    \  for (int j = 0; j < w; j++) {\n        int i = result.col_to_row[j];\n    \
    \    if (i == -1) continue;\n        assert(0 <= i && i < h);\n        assert(result.row_to_col[i]\
    \ == j);\n    }\n    assert(sum == result.cost);\n\n    auto pairs = result.matching();\n\
    \    assert(int(pairs.size()) == result.matching_size());\n    for (auto [row,\
    \ col] : pairs) assert(result.row_to_col[row] == col);\n}\n\nvoid test_hungarian_min()\
    \ {\n    std::vector<std::vector<long long>> square = {\n        {4, 1, 3},\n\
    \        {2, 0, 5},\n        {3, 2, 2},\n    };\n    auto sq = m1une::opt::hungarian_min(square);\n\
    \    check_result(square, sq, 5);\n\n    std::vector<std::vector<long long>> wide\
    \ = {\n        {7, 4, 6, 8},\n        {5, 9, 3, 1},\n    };\n    check_result(wide,\
    \ m1une::opt::hungarian(wide), brute_min(wide));\n\n    std::vector<std::vector<long\
    \ long>> tall = {\n        {9, 4},\n        {6, 7},\n        {5, 8},\n       \
    \ {1, 3},\n    };\n    auto tall_result = m1une::opt::hungarian_min(tall);\n \
    \   check_result(tall, tall_result, brute_min(tall));\n    assert(tall_result.col_to_row[0]\
    \ != -1);\n    assert(tall_result.col_to_row[1] != -1);\n\n    std::vector<std::vector<long\
    \ long>> negative = {\n        {-4, 2, 0},\n        {3, -5, 1},\n    };\n    check_result(negative,\
    \ m1une::opt::hungarian_min(negative), brute_min(negative));\n\n    std::vector<std::vector<long\
    \ long>> zero_cols(3);\n    check_result(zero_cols, m1une::opt::hungarian_min(zero_cols),\
    \ 0);\n}\n\nvoid test_hungarian_max() {\n    std::vector<std::vector<long long>>\
    \ cost = {\n        {1, 8, 2},\n        {5, 3, 4},\n        {6, 7, 0},\n    };\n\
    \    check_result(cost, m1une::opt::hungarian_max(cost), brute_max(cost));\n}\n\
    \nvoid test_against_bruteforce() {\n    for (int h = 1; h <= 4; h++) {\n     \
    \   for (int w = 1; w <= 4; w++) {\n            std::vector<std::vector<long long>>\
    \ cost(h, std::vector<long long>(w));\n            for (int i = 0; i < h; i++)\
    \ {\n                for (int j = 0; j < w; j++) {\n                    cost[i][j]\
    \ = ((i + 2) * (j + 3) * 5 + i * 7 - j * 11) % 17 - 8;\n                }\n  \
    \          }\n            check_result(cost, m1une::opt::hungarian_min(cost),\
    \ brute_min(cost));\n            check_result(cost, m1une::opt::hungarian_max(cost),\
    \ brute_max(cost));\n        }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_hungarian_min();\n\
    \    test_hungarian_max();\n    test_against_bruteforce();\n    int n;\n    fast_input\
    \ >> n;\n    std::vector<std::vector<long long>> cost(n, std::vector<long long>(n));\n\
    \    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++) {\n  \
    \          fast_input >> cost[i][j];\n        }\n    }\n\n    auto result = m1une::opt::hungarian_min(cost);\n\
    \    fast_output << result.cost << '\\n';\n    for (int i = 0; i < n; i++) {\n\
    \        if (i) fast_output << ' ';\n        fast_output << result.row_to_col[i];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include \"../../utilities/fast_io.hpp\"\n\
    #include <limits>\n#include <vector>\n\n#include \"../../optimization/hungarian.hpp\"\
    \n\nlong long brute_min(const std::vector<std::vector<long long>>& cost) {\n \
    \   int h = int(cost.size());\n    int w = h == 0 ? 0 : int(cost[0].size());\n\
    \    if (h == 0 || w == 0) return 0;\n\n    long long best = std::numeric_limits<long\
    \ long>::max() / 4;\n    if (h <= w) {\n        std::vector<int> perm(w);\n  \
    \      for (int i = 0; i < w; i++) perm[i] = i;\n        do {\n            long\
    \ long sum = 0;\n            for (int i = 0; i < h; i++) sum += cost[i][perm[i]];\n\
    \            best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    } else {\n        std::vector<int> perm(h);\n        for\
    \ (int i = 0; i < h; i++) perm[i] = i;\n        do {\n            long long sum\
    \ = 0;\n            for (int j = 0; j < w; j++) sum += cost[perm[j]][j];\n   \
    \         best = std::min(best, sum);\n        } while (std::next_permutation(perm.begin(),\
    \ perm.end()));\n    }\n    return best;\n}\n\nlong long brute_max(const std::vector<std::vector<long\
    \ long>>& cost) {\n    std::vector<std::vector<long long>> negated = cost;\n \
    \   for (auto& row : negated) {\n        for (auto& x : row) x = -x;\n    }\n\
    \    return -brute_min(negated);\n}\n\nvoid check_result(const std::vector<std::vector<long\
    \ long>>& cost,\n                  const m1une::opt::HungarianResult<long long>&\
    \ result,\n                  long long expected) {\n    int h = int(cost.size());\n\
    \    int w = h == 0 ? 0 : int(cost[0].size());\n    assert(int(result.row_to_col.size())\
    \ == h);\n    assert(int(result.col_to_row.size()) == w);\n    assert(result.matching_size()\
    \ == std::min(h, w));\n    assert(result.cost == expected);\n\n    std::vector<bool>\
    \ used_cols(w, false);\n    long long sum = 0;\n    for (int i = 0; i < h; i++)\
    \ {\n        int j = result.row_to_col[i];\n        if (j == -1) continue;\n \
    \       assert(0 <= j && j < w);\n        assert(!used_cols[j]);\n        assert(result.col_to_row[j]\
    \ == i);\n        used_cols[j] = true;\n        sum += cost[i][j];\n    }\n  \
    \  for (int j = 0; j < w; j++) {\n        int i = result.col_to_row[j];\n    \
    \    if (i == -1) continue;\n        assert(0 <= i && i < h);\n        assert(result.row_to_col[i]\
    \ == j);\n    }\n    assert(sum == result.cost);\n\n    auto pairs = result.matching();\n\
    \    assert(int(pairs.size()) == result.matching_size());\n    for (auto [row,\
    \ col] : pairs) assert(result.row_to_col[row] == col);\n}\n\nvoid test_hungarian_min()\
    \ {\n    std::vector<std::vector<long long>> square = {\n        {4, 1, 3},\n\
    \        {2, 0, 5},\n        {3, 2, 2},\n    };\n    auto sq = m1une::opt::hungarian_min(square);\n\
    \    check_result(square, sq, 5);\n\n    std::vector<std::vector<long long>> wide\
    \ = {\n        {7, 4, 6, 8},\n        {5, 9, 3, 1},\n    };\n    check_result(wide,\
    \ m1une::opt::hungarian(wide), brute_min(wide));\n\n    std::vector<std::vector<long\
    \ long>> tall = {\n        {9, 4},\n        {6, 7},\n        {5, 8},\n       \
    \ {1, 3},\n    };\n    auto tall_result = m1une::opt::hungarian_min(tall);\n \
    \   check_result(tall, tall_result, brute_min(tall));\n    assert(tall_result.col_to_row[0]\
    \ != -1);\n    assert(tall_result.col_to_row[1] != -1);\n\n    std::vector<std::vector<long\
    \ long>> negative = {\n        {-4, 2, 0},\n        {3, -5, 1},\n    };\n    check_result(negative,\
    \ m1une::opt::hungarian_min(negative), brute_min(negative));\n\n    std::vector<std::vector<long\
    \ long>> zero_cols(3);\n    check_result(zero_cols, m1une::opt::hungarian_min(zero_cols),\
    \ 0);\n}\n\nvoid test_hungarian_max() {\n    std::vector<std::vector<long long>>\
    \ cost = {\n        {1, 8, 2},\n        {5, 3, 4},\n        {6, 7, 0},\n    };\n\
    \    check_result(cost, m1une::opt::hungarian_max(cost), brute_max(cost));\n}\n\
    \nvoid test_against_bruteforce() {\n    for (int h = 1; h <= 4; h++) {\n     \
    \   for (int w = 1; w <= 4; w++) {\n            std::vector<std::vector<long long>>\
    \ cost(h, std::vector<long long>(w));\n            for (int i = 0; i < h; i++)\
    \ {\n                for (int j = 0; j < w; j++) {\n                    cost[i][j]\
    \ = ((i + 2) * (j + 3) * 5 + i * 7 - j * 11) % 17 - 8;\n                }\n  \
    \          }\n            check_result(cost, m1une::opt::hungarian_min(cost),\
    \ brute_min(cost));\n            check_result(cost, m1une::opt::hungarian_max(cost),\
    \ brute_max(cost));\n        }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_hungarian_min();\n\
    \    test_hungarian_max();\n    test_against_bruteforce();\n    int n;\n    fast_input\
    \ >> n;\n    std::vector<std::vector<long long>> cost(n, std::vector<long long>(n));\n\
    \    for (int i = 0; i < n; i++) {\n        for (int j = 0; j < n; j++) {\n  \
    \          fast_input >> cost[i][j];\n        }\n    }\n\n    auto result = m1une::opt::hungarian_min(cost);\n\
    \    fast_output << result.cost << '\\n';\n    for (int i = 0; i < n; i++) {\n\
    \        if (i) fast_output << ' ';\n        fast_output << result.row_to_col[i];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - optimization/hungarian.hpp
  isVerificationFile: true
  path: verify/optimization/hungarian.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/optimization/hungarian.test.cpp
layout: document
redirect_from:
- /verify/verify/optimization/hungarian.test.cpp
- /verify/verify/optimization/hungarian.test.cpp.html
title: verify/optimization/hungarian.test.cpp
---
