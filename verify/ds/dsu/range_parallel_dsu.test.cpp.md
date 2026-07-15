---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: ds/dsu/range_parallel_dsu.hpp
    title: Range-Parallel DSU
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
    PROBLEM: https://judge.yosupo.jp/problem/range_parallel_unionfind
    links:
    - https://judge.yosupo.jp/problem/range_parallel_unionfind
  bundledCode: "#line 1 \"verify/ds/dsu/range_parallel_dsu.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_parallel_unionfind\"\n\n#include <cassert>\n\
    #include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une\
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
    \ m1une\n\n\n#line 6 \"verify/ds/dsu/range_parallel_dsu.test.cpp\"\n#include <vector>\n\
    \n#line 1 \"ds/dsu/dsu.hpp\"\n\n\n\n#include <algorithm>\n#include <numeric>\n\
    #line 8 \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu\
    \ {\n   private:\n    int _n;\n    // parent_or_size[i] is the parent of i if\
    \ it's >= 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the\
    \ size of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns {new\
    \ leader, absorbed leader}. The absorbed leader is -1 when\n    // both vertices\
    \ already belong to the same component.\n    std::pair<int, int> merge_leaders(int\
    \ a, int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y)\
    \ return {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/dsu/range_parallel_dsu.hpp\"\n\n\n\n#include\
    \ <bit>\n#line 9 \"ds/dsu/range_parallel_dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// Merges corresponding vertices of two equal-length ranges.\nclass\
    \ RangeParallelDsu {\n   private:\n    struct LevelDsu {\n        std::vector<int>\
    \ parent_or_size;\n        int component_count;\n\n        explicit LevelDsu(int\
    \ size = 0)\n            : parent_or_size(std::size_t(size), -1), component_count(size)\
    \ {}\n\n        int leader(int vertex) {\n            if (parent_or_size[vertex]\
    \ < 0) return vertex;\n            return parent_or_size[vertex] = leader(parent_or_size[vertex]);\n\
    \        }\n\n        int leader(int vertex) const {\n            while (parent_or_size[vertex]\
    \ >= 0) {\n                vertex = parent_or_size[vertex];\n            }\n \
    \           return vertex;\n        }\n\n        std::pair<int, int> merge(int\
    \ first, int second) {\n            first = leader(first);\n            second\
    \ = leader(second);\n            if (first == second) return {first, -1};\n  \
    \          if (-parent_or_size[first] < -parent_or_size[second]) {\n         \
    \       std::swap(first, second);\n            }\n            parent_or_size[first]\
    \ += parent_or_size[second];\n            parent_or_size[second] = first;\n  \
    \          component_count--;\n            return {first, second};\n        }\n\
    \    };\n\n    int _size;\n    std::vector<LevelDsu> _levels;\n\n    static int\
    \ check_size(int size) {\n        assert(size >= 0);\n        return size;\n \
    \   }\n\n    void check_vertex(int vertex) const {\n        assert(0 <= vertex\
    \ && vertex < _size);\n    }\n\n    void check_range(int first, int length) const\
    \ {\n        assert(0 <= first && 0 <= length);\n        assert(length <= _size);\n\
    \        assert(first <= _size - length);\n    }\n\n    template <class Callback>\n\
    \    int merge_block(int level, int first, int second, Callback& callback) {\n\
    \        std::pair<int, int> merged = _levels[level].merge(first, second);\n \
    \       if (merged.second == -1) return 0;\n        if (level == 0) {\n      \
    \      callback(merged.first, merged.second);\n            return 1;\n       \
    \ }\n\n        const int half = 1 << (level - 1);\n        int result = merge_block(level\
    \ - 1, first, second, callback);\n        result += merge_block(level - 1, first\
    \ + half, second + half, callback);\n        return result;\n    }\n\n   public:\n\
    \    RangeParallelDsu() : RangeParallelDsu(0) {}\n\n    explicit RangeParallelDsu(int\
    \ size) : _size(check_size(size)) {\n        _levels.emplace_back(_size);\n  \
    \      for (int block_size = 2; block_size < _size; block_size *= 2) {\n     \
    \       _levels.emplace_back(_size - block_size + 1);\n            if (block_size\
    \ > _size / 2) break;\n        }\n    }\n\n    int size() const {\n        return\
    \ _size;\n    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\
    \n    int component_count() const {\n        return _levels[0].component_count;\n\
    \    }\n\n    int leader(int vertex) {\n        check_vertex(vertex);\n      \
    \  return _levels[0].leader(vertex);\n    }\n\n    int leader(int vertex) const\
    \ {\n        check_vertex(vertex);\n        return _levels[0].leader(vertex);\n\
    \    }\n\n    bool same(int first, int second) {\n        return leader(first)\
    \ == leader(second);\n    }\n\n    bool same(int first, int second) const {\n\
    \        return leader(first) == leader(second);\n    }\n\n    int group_size(int\
    \ vertex) {\n        return -_levels[0].parent_or_size[leader(vertex)];\n    }\n\
    \n    int group_size(int vertex) const {\n        return -_levels[0].parent_or_size[leader(vertex)];\n\
    \    }\n\n    template <class Callback>\n    int merge(int first, int second,\
    \ int length, Callback&& callback) {\n        check_range(first, length);\n  \
    \      check_range(second, length);\n        if (length == 0) return 0;\n    \
    \    if (length == 1) {\n            return merge_block(0, first, second, callback);\n\
    \        }\n\n        const int level = int(std::bit_width(unsigned(length - 1)))\
    \ - 1;\n        const int block_size = 1 << level;\n        int result = merge_block(level,\
    \ first, second, callback);\n        result += merge_block(level, first + length\
    \ - block_size,\n                              second + length - block_size, callback);\n\
    \        return result;\n    }\n\n    int merge(int first, int second, int length)\
    \ {\n        auto ignore = [](int, int) {};\n        return merge(first, second,\
    \ length, ignore);\n    }\n\n    template <class Callback>\n    int merge_ranges(int\
    \ first_left, int first_right, int second_left,\n                     int second_right,\
    \ Callback&& callback) {\n        assert(first_right - first_left == second_right\
    \ - second_left);\n        return merge(first_left, second_left, first_right -\
    \ first_left,\n                     std::forward<Callback>(callback));\n    }\n\
    \n    int merge_ranges(int first_left, int first_right, int second_left,\n   \
    \                  int second_right) {\n        auto ignore = [](int, int) {};\n\
    \        return merge_ranges(first_left, first_right, second_left, second_right,\n\
    \                            ignore);\n    }\n\n    template <class Callback>\n\
    \    int merge(int first, int second, Callback&& callback) {\n        check_vertex(first);\n\
    \        check_vertex(second);\n        return merge_block(0, first, second, callback);\n\
    \    }\n\n    int merge(int first, int second) {\n        auto ignore = [](int,\
    \ int) {};\n        return merge(first, second, ignore);\n    }\n};\n\nusing RangeParallelUnionFind\
    \ = RangeParallelDsu;\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
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
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
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
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 11 \"verify/ds/dsu/range_parallel_dsu.test.cpp\"\n\nnamespace {\n\n\
    void test_randomized() {\n    uint64_t state = 0xa0761d6478bd642fULL;\n    auto\
    \ random = [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 200; trial++)\
    \ {\n        const int size = int(random() % 60) + 1;\n        m1une::ds::RangeParallelDsu\
    \ range_dsu(size);\n        m1une::ds::Dsu naive(size);\n        assert(range_dsu.size()\
    \ == size);\n        assert(!range_dsu.empty());\n\n        for (int query = 0;\
    \ query < 500; query++) {\n            const int length = int(random() % (size\
    \ + 1));\n            const int first = int(random() % (size - length + 1));\n\
    \            const int second = int(random() % (size - length + 1));\n\n     \
    \       int expected_merges = 0;\n            for (int offset = 0; offset < length;\
    \ offset++) {\n                if (!naive.same(first + offset, second + offset))\
    \ {\n                    naive.merge(first + offset, second + offset);\n     \
    \               expected_merges++;\n                }\n            }\n\n     \
    \       int callback_count = 0;\n            const int merges = range_dsu.merge(\n\
    \                first, second, length,\n                [&](int leader, int absorbed)\
    \ {\n                    assert(range_dsu.leader(leader) == leader);\n       \
    \             assert(range_dsu.leader(absorbed) == leader);\n                \
    \    callback_count++;\n                });\n            assert(merges == expected_merges);\n\
    \            assert(callback_count == expected_merges);\n\n            for (int\
    \ first_vertex = 0; first_vertex < size; first_vertex++) {\n                assert(range_dsu.group_size(first_vertex)\
    \ ==\n                       naive.size(first_vertex));\n                for (int\
    \ second_vertex = 0; second_vertex < size;\n                     second_vertex++)\
    \ {\n                    assert(range_dsu.same(first_vertex, second_vertex) ==\n\
    \                           naive.same(first_vertex, second_vertex));\n      \
    \          }\n            }\n        }\n        assert(range_dsu.component_count()\
    \ == int(naive.groups().size()));\n    }\n}\n\nvoid test_overloads() {\n    m1une::ds::RangeParallelUnionFind\
    \ dsu(8);\n    assert(dsu.merge_ranges(0, 4, 4, 8) == 4);\n    assert(dsu.same(0,\
    \ 4));\n    assert(dsu.same(3, 7));\n    assert(dsu.merge(0, 1) == 1);\n    assert(dsu.group_size(0)\
    \ == 4);\n    assert(dsu.merge(0, 4, 4) == 0);\n\n    m1une::ds::RangeParallelDsu\
    \ empty;\n    assert(empty.empty());\n    assert(empty.component_count() == 0);\n\
    \    assert(empty.merge(0, 0, 0) == 0);\n}\n\n}  // namespace\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_randomized();\n    test_overloads();\n\n    using Mint\
    \ = m1une::math::modint998244353;\n    int size, query_count;\n    fast_input\
    \ >> size >> query_count;\n    std::vector<Mint> component_sum(size);\n    for\
    \ (Mint& value : component_sum) fast_input >> value;\n\n    m1une::ds::RangeParallelDsu\
    \ dsu(size);\n    Mint answer = 0;\n    auto on_merge = [&](int leader, int absorbed)\
    \ {\n        answer += component_sum[leader] * component_sum[absorbed];\n    \
    \    component_sum[leader] += component_sum[absorbed];\n    };\n\n    while (query_count--)\
    \ {\n        int length, first, second;\n        fast_input >> length >> first\
    \ >> second;\n        dsu.merge(first, second, length, on_merge);\n        fast_output\
    \ << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_parallel_unionfind\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\n#include \"../../../ds/dsu/dsu.hpp\"\n#include \"../../../ds/dsu/range_parallel_dsu.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    uint64_t state = 0xa0761d6478bd642fULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 200; trial++) {\n        const int\
    \ size = int(random() % 60) + 1;\n        m1une::ds::RangeParallelDsu range_dsu(size);\n\
    \        m1une::ds::Dsu naive(size);\n        assert(range_dsu.size() == size);\n\
    \        assert(!range_dsu.empty());\n\n        for (int query = 0; query < 500;\
    \ query++) {\n            const int length = int(random() % (size + 1));\n   \
    \         const int first = int(random() % (size - length + 1));\n           \
    \ const int second = int(random() % (size - length + 1));\n\n            int expected_merges\
    \ = 0;\n            for (int offset = 0; offset < length; offset++) {\n      \
    \          if (!naive.same(first + offset, second + offset)) {\n             \
    \       naive.merge(first + offset, second + offset);\n                    expected_merges++;\n\
    \                }\n            }\n\n            int callback_count = 0;\n   \
    \         const int merges = range_dsu.merge(\n                first, second,\
    \ length,\n                [&](int leader, int absorbed) {\n                 \
    \   assert(range_dsu.leader(leader) == leader);\n                    assert(range_dsu.leader(absorbed)\
    \ == leader);\n                    callback_count++;\n                });\n  \
    \          assert(merges == expected_merges);\n            assert(callback_count\
    \ == expected_merges);\n\n            for (int first_vertex = 0; first_vertex\
    \ < size; first_vertex++) {\n                assert(range_dsu.group_size(first_vertex)\
    \ ==\n                       naive.size(first_vertex));\n                for (int\
    \ second_vertex = 0; second_vertex < size;\n                     second_vertex++)\
    \ {\n                    assert(range_dsu.same(first_vertex, second_vertex) ==\n\
    \                           naive.same(first_vertex, second_vertex));\n      \
    \          }\n            }\n        }\n        assert(range_dsu.component_count()\
    \ == int(naive.groups().size()));\n    }\n}\n\nvoid test_overloads() {\n    m1une::ds::RangeParallelUnionFind\
    \ dsu(8);\n    assert(dsu.merge_ranges(0, 4, 4, 8) == 4);\n    assert(dsu.same(0,\
    \ 4));\n    assert(dsu.same(3, 7));\n    assert(dsu.merge(0, 1) == 1);\n    assert(dsu.group_size(0)\
    \ == 4);\n    assert(dsu.merge(0, 4, 4) == 0);\n\n    m1une::ds::RangeParallelDsu\
    \ empty;\n    assert(empty.empty());\n    assert(empty.component_count() == 0);\n\
    \    assert(empty.merge(0, 0, 0) == 0);\n}\n\n}  // namespace\n\nint main() {\n\
    \    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_randomized();\n    test_overloads();\n\n    using Mint\
    \ = m1une::math::modint998244353;\n    int size, query_count;\n    fast_input\
    \ >> size >> query_count;\n    std::vector<Mint> component_sum(size);\n    for\
    \ (Mint& value : component_sum) fast_input >> value;\n\n    m1une::ds::RangeParallelDsu\
    \ dsu(size);\n    Mint answer = 0;\n    auto on_merge = [&](int leader, int absorbed)\
    \ {\n        answer += component_sum[leader] * component_sum[absorbed];\n    \
    \    component_sum[leader] += component_sum[absorbed];\n    };\n\n    while (query_count--)\
    \ {\n        int length, first, second;\n        fast_input >> length >> first\
    \ >> second;\n        dsu.merge(first, second, length, on_merge);\n        fast_output\
    \ << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - ds/dsu/dsu.hpp
  - ds/dsu/range_parallel_dsu.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/dsu/range_parallel_dsu.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dsu/range_parallel_dsu.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dsu/range_parallel_dsu.test.cpp
- /verify/verify/ds/dsu/range_parallel_dsu.test.cpp.html
title: verify/ds/dsu/range_parallel_dsu.test.cpp
---
