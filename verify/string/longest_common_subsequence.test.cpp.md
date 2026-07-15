---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/longest_common_subsequence.hpp
    title: Longest Common Subsequence
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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C
  bundledCode: "#line 1 \"verify/string/longest_common_subsequence.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C\"\
    \n\n#line 1 \"string/longest_common_subsequence.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\nstruct LongestCommonSubsequence {\n\
    \    std::vector<std::pair<int, int>> matches;\n\n    int length() const {\n \
    \       return int(matches.size());\n    }\n\n    bool empty() const {\n     \
    \   return matches.empty();\n    }\n\n    std::vector<int> first_indices() const\
    \ {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(i);\n\
    \        }\n        return result;\n    }\n\n    std::vector<int> second_indices()\
    \ const {\n        std::vector<int> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(j);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_first(const Sequence& first) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)j;\n            result.push_back(first[i]);\n\
    \        }\n        return result;\n    }\n\n    template <class Sequence>\n \
    \   std::vector<std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>>\n    values_from_second(const Sequence& second) const {\n\
    \        using Value = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<const\
    \ Sequence&>()[0])>>;\n        std::vector<Value> result;\n        result.reserve(matches.size());\n\
    \        for (auto [i, j] : matches) {\n            (void)i;\n            result.push_back(second[j]);\n\
    \        }\n        return result;\n    }\n};\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nint longest_common_subsequence_length(const FirstSequence&\
    \ first, const SecondSequence& second) {\n    int n = int(first.size());\n   \
    \ int m = int(second.size());\n    if (m <= n) {\n        std::vector<int> dp(m\
    \ + 1, 0);\n        for (int i = 0; i < n; i++) {\n            int diagonal =\
    \ 0;\n            for (int j = 0; j < m; j++) {\n                int up = dp[j\
    \ + 1];\n                if (first[i] == second[j]) {\n                    dp[j\
    \ + 1] = diagonal + 1;\n                } else {\n                    dp[j + 1]\
    \ = std::max(dp[j + 1], dp[j]);\n                }\n                diagonal =\
    \ up;\n            }\n        }\n        return dp[m];\n    } else {\n       \
    \ std::vector<int> dp(n + 1, 0);\n        for (int j = 0; j < m; j++) {\n    \
    \        int diagonal = 0;\n            for (int i = 0; i < n; i++) {\n      \
    \          int up = dp[i + 1];\n                if (first[i] == second[j]) {\n\
    \                    dp[i + 1] = diagonal + 1;\n                } else {\n   \
    \                 dp[i + 1] = std::max(dp[i + 1], dp[i]);\n                }\n\
    \                diagonal = up;\n            }\n        }\n        return dp[n];\n\
    \    }\n}\n\ntemplate <class FirstSequence, class SecondSequence>\nLongestCommonSubsequence\
    \ longest_common_subsequence(\n    const FirstSequence& first,\n    const SecondSequence&\
    \ second\n) {\n    int n = int(first.size());\n    int m = int(second.size());\n\
    \    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));\n  \
    \  for (int i = 0; i < n; i++) {\n        for (int j = 0; j < m; j++) {\n    \
    \        if (first[i] == second[j]) {\n                dp[i + 1][j + 1] = dp[i][j]\
    \ + 1;\n            } else {\n                dp[i + 1][j + 1] = std::max(dp[i][j\
    \ + 1], dp[i + 1][j]);\n            }\n        }\n    }\n\n    LongestCommonSubsequence\
    \ result;\n    result.matches.reserve(dp[n][m]);\n    int i = n;\n    int j =\
    \ m;\n    while (i > 0 && j > 0) {\n        if (first[i - 1] == second[j - 1])\
    \ {\n            result.matches.emplace_back(i - 1, j - 1);\n            i--;\n\
    \            j--;\n        } else if (dp[i - 1][j] >= dp[i][j - 1]) {\n      \
    \      i--;\n        } else {\n            j--;\n        }\n    }\n    std::reverse(result.matches.begin(),\
    \ result.matches.end());\n    return result;\n}\n\n}  // namespace string\n} \
    \ // namespace m1une\n\n\n#line 4 \"verify/string/longest_common_subsequence.test.cpp\"\
    \n\n#line 7 \"verify/string/longest_common_subsequence.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#line 15 \"utilities/fast_io.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
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
    \ m1une\n\n\n#line 11 \"verify/string/longest_common_subsequence.test.cpp\"\n\n\
    namespace {\n\ntemplate <class FirstSequence, class SecondSequence>\nint independent_lcs_length(const\
    \ FirstSequence& first, const SecondSequence& second) {\n    int n = int(first.size());\n\
    \    int m = int(second.size());\n    std::vector<std::vector<int>> dp(n + 1,\
    \ std::vector<int>(m + 1, 0));\n    for (int i = n - 1; i >= 0; i--) {\n     \
    \   for (int j = m - 1; j >= 0; j--) {\n            if (first[i] == second[j])\
    \ {\n                dp[i][j] = dp[i + 1][j + 1] + 1;\n            } else {\n\
    \                dp[i][j] = std::max(dp[i + 1][j], dp[i][j + 1]);\n          \
    \  }\n        }\n    }\n    return dp[0][0];\n}\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nvoid check_result(const FirstSequence& first, const SecondSequence&\
    \ second) {\n    auto result = m1une::string::longest_common_subsequence(first,\
    \ second);\n    int expected = independent_lcs_length(first, second);\n    assert(result.length()\
    \ == expected);\n    assert(result.empty() == (expected == 0));\n    assert(\n\
    \        m1une::string::longest_common_subsequence_length(first, second) ==\n\
    \        expected\n    );\n\n    std::vector<int> first_indices = result.first_indices();\n\
    \    std::vector<int> second_indices = result.second_indices();\n    assert(int(first_indices.size())\
    \ == expected);\n    assert(int(second_indices.size()) == expected);\n\n    for\
    \ (int k = 0; k < expected; k++) {\n        int i = result.matches[k].first;\n\
    \        int j = result.matches[k].second;\n        assert(i == first_indices[k]);\n\
    \        assert(j == second_indices[k]);\n        assert(0 <= i && i < int(first.size()));\n\
    \        assert(0 <= j && j < int(second.size()));\n        assert(first[i] ==\
    \ second[j]);\n        if (k > 0) {\n            assert(result.matches[k - 1].first\
    \ < i);\n            assert(result.matches[k - 1].second < j);\n        }\n  \
    \  }\n}\n\nvoid test_fixed() {\n    check_result(std::string(), std::string());\n\
    \    check_result(std::string(\"abc\"), std::string());\n    check_result(std::string(),\
    \ std::string(\"abc\"));\n    check_result(std::string(\"abc\"), std::string(\"\
    def\"));\n    check_result(std::string(\"abcbdab\"), std::string(\"bdcaba\"));\n\
    \    check_result(std::string(\"aaaa\"), std::string(\"aa\"));\n\n    std::string\
    \ first = \"abcbdab\";\n    std::string second = \"bdcaba\";\n    auto result\
    \ = m1une::string::longest_common_subsequence(first, second);\n    assert(result.length()\
    \ == 4);\n    assert(result.values_from_first(first) == result.values_from_second(second));\n\
    \n    std::vector<int> first_values;\n    first_values.push_back(1);\n    first_values.push_back(3);\n\
    \    first_values.push_back(2);\n    first_values.push_back(4);\n    first_values.push_back(3);\n\
    \    std::vector<int> second_values;\n    second_values.push_back(3);\n    second_values.push_back(1);\n\
    \    second_values.push_back(2);\n    second_values.push_back(3);\n    check_result(first_values,\
    \ second_values);\n    auto vector_result = m1une::string::longest_common_subsequence(first_values,\
    \ second_values);\n    assert(vector_result.values_from_first(first_values) ==\
    \ vector_result.values_from_second(second_values));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 30);\n        int m = int(random() % 30);\n        std::string first(n, 'a');\n\
    \        std::string second(m, 'a');\n        for (char& character : first) character\
    \ = char('a' + random() % 5);\n        for (char& character : second) character\
    \ = char('a' + random() % 5);\n        check_result(first, second);\n\n      \
    \  std::vector<int> first_values(n);\n        std::vector<int> second_values(m);\n\
    \        for (int& value : first_values) value = int(random() % 7) - 3;\n    \
    \    for (int& value : second_values) value = int(random() % 7) - 3;\n       \
    \ check_result(first_values, second_values);\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n    int q;\n    fast_input\
    \ >> q;\n    while (q--) {\n        std::string first, second;\n        fast_input\
    \ >> first >> second;\n        fast_output << m1une::string::longest_common_subsequence_length(first,\
    \ second) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_C\"\
    \n\n#include \"../../string/longest_common_subsequence.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <string>\n#include <vector>\n\nnamespace {\n\ntemplate <class FirstSequence,\
    \ class SecondSequence>\nint independent_lcs_length(const FirstSequence& first,\
    \ const SecondSequence& second) {\n    int n = int(first.size());\n    int m =\
    \ int(second.size());\n    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m\
    \ + 1, 0));\n    for (int i = n - 1; i >= 0; i--) {\n        for (int j = m -\
    \ 1; j >= 0; j--) {\n            if (first[i] == second[j]) {\n              \
    \  dp[i][j] = dp[i + 1][j + 1] + 1;\n            } else {\n                dp[i][j]\
    \ = std::max(dp[i + 1][j], dp[i][j + 1]);\n            }\n        }\n    }\n \
    \   return dp[0][0];\n}\n\ntemplate <class FirstSequence, class SecondSequence>\n\
    void check_result(const FirstSequence& first, const SecondSequence& second) {\n\
    \    auto result = m1une::string::longest_common_subsequence(first, second);\n\
    \    int expected = independent_lcs_length(first, second);\n    assert(result.length()\
    \ == expected);\n    assert(result.empty() == (expected == 0));\n    assert(\n\
    \        m1une::string::longest_common_subsequence_length(first, second) ==\n\
    \        expected\n    );\n\n    std::vector<int> first_indices = result.first_indices();\n\
    \    std::vector<int> second_indices = result.second_indices();\n    assert(int(first_indices.size())\
    \ == expected);\n    assert(int(second_indices.size()) == expected);\n\n    for\
    \ (int k = 0; k < expected; k++) {\n        int i = result.matches[k].first;\n\
    \        int j = result.matches[k].second;\n        assert(i == first_indices[k]);\n\
    \        assert(j == second_indices[k]);\n        assert(0 <= i && i < int(first.size()));\n\
    \        assert(0 <= j && j < int(second.size()));\n        assert(first[i] ==\
    \ second[j]);\n        if (k > 0) {\n            assert(result.matches[k - 1].first\
    \ < i);\n            assert(result.matches[k - 1].second < j);\n        }\n  \
    \  }\n}\n\nvoid test_fixed() {\n    check_result(std::string(), std::string());\n\
    \    check_result(std::string(\"abc\"), std::string());\n    check_result(std::string(),\
    \ std::string(\"abc\"));\n    check_result(std::string(\"abc\"), std::string(\"\
    def\"));\n    check_result(std::string(\"abcbdab\"), std::string(\"bdcaba\"));\n\
    \    check_result(std::string(\"aaaa\"), std::string(\"aa\"));\n\n    std::string\
    \ first = \"abcbdab\";\n    std::string second = \"bdcaba\";\n    auto result\
    \ = m1une::string::longest_common_subsequence(first, second);\n    assert(result.length()\
    \ == 4);\n    assert(result.values_from_first(first) == result.values_from_second(second));\n\
    \n    std::vector<int> first_values;\n    first_values.push_back(1);\n    first_values.push_back(3);\n\
    \    first_values.push_back(2);\n    first_values.push_back(4);\n    first_values.push_back(3);\n\
    \    std::vector<int> second_values;\n    second_values.push_back(3);\n    second_values.push_back(1);\n\
    \    second_values.push_back(2);\n    second_values.push_back(3);\n    check_result(first_values,\
    \ second_values);\n    auto vector_result = m1une::string::longest_common_subsequence(first_values,\
    \ second_values);\n    assert(vector_result.values_from_first(first_values) ==\
    \ vector_result.values_from_second(second_values));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260709;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 30);\n        int m = int(random() % 30);\n        std::string first(n, 'a');\n\
    \        std::string second(m, 'a');\n        for (char& character : first) character\
    \ = char('a' + random() % 5);\n        for (char& character : second) character\
    \ = char('a' + random() % 5);\n        check_result(first, second);\n\n      \
    \  std::vector<int> first_values(n);\n        std::vector<int> second_values(m);\n\
    \        for (int& value : first_values) value = int(random() % 7) - 3;\n    \
    \    for (int& value : second_values) value = int(random() % 7) - 3;\n       \
    \ check_result(first_values, second_values);\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_fixed();\n    test_randomized();\n    int q;\n    fast_input\
    \ >> q;\n    while (q--) {\n        std::string first, second;\n        fast_input\
    \ >> first >> second;\n        fast_output << m1une::string::longest_common_subsequence_length(first,\
    \ second) << '\\n';\n    }\n}\n"
  dependsOn:
  - string/longest_common_subsequence.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/longest_common_subsequence.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/longest_common_subsequence.test.cpp
layout: document
redirect_from:
- /verify/verify/string/longest_common_subsequence.test.cpp
- /verify/verify/string/longest_common_subsequence.test.cpp.html
title: verify/string/longest_common_subsequence.test.cpp
---
