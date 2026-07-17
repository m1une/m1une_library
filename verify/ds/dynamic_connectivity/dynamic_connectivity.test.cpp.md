---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/rollback_dsu.hpp
    title: Rollback DSU
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/all.hpp
    title: Dynamic Connectivity
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
    title: Offline Dynamic Connectivity
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_connectivity/online_dynamic_connectivity.hpp
    title: Online Dynamic Connectivity
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_tree/link_cut_tree.hpp
    title: Link-Cut Tree
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
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
  bundledCode: "#line 1 \"verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #include <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n\
    #include <sys/stat.h>\n#include <type_traits>\n#include <utility>\n#include <unistd.h>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp\"\
    \n#include <queue>\n#include <random>\n#line 8 \"verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"ds/dynamic_connectivity/all.hpp\"\n\n\n\n#line\
    \ 1 \"ds/dynamic_connectivity/offline_dynamic_connectivity.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#line 8 \"ds/dynamic_connectivity/offline_dynamic_connectivity.hpp\"\
    \n\n#line 1 \"ds/dsu/rollback_dsu.hpp\"\n\n\n\n#line 7 \"ds/dsu/rollback_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct RollbackDsu {\n   private:\n \
    \   struct HistoryEntry {\n        int first;\n        int first_value;\n    \
    \    int second;\n        int second_value;\n    };\n\n    int _n;\n    int _component_count;\n\
    \    std::vector<int> parent_or_size;\n    std::vector<HistoryEntry> history;\n\
    \n    static int check_size(int n) {\n        assert(0 <= n);\n        return\
    \ n;\n    }\n\n   public:\n    RollbackDsu() : RollbackDsu(0) {}\n\n    explicit\
    \ RollbackDsu(int n)\n        : _n(check_size(n)), _component_count(_n), parent_or_size(_n,\
    \ -1) {}\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int component_count() const {\n\
    \        return _component_count;\n    }\n\n    int history_size() const {\n \
    \       return int(history.size());\n    }\n\n    void reserve_history(int count)\
    \ {\n        assert(0 <= count);\n        history.reserve(count);\n    }\n\n \
    \   int leader(int vertex) const {\n        assert(0 <= vertex && vertex < _n);\n\
    \        while (parent_or_size[vertex] >= 0) vertex = parent_or_size[vertex];\n\
    \        return vertex;\n    }\n\n    bool same(int first, int second) const {\n\
    \        return leader(first) == leader(second);\n    }\n\n    int group_size(int\
    \ vertex) const {\n        return -parent_or_size[leader(vertex)];\n    }\n\n\
    \    int size(int vertex) const {\n        return group_size(vertex);\n    }\n\
    \n    bool merge(int first, int second) {\n        first = leader(first);\n  \
    \      second = leader(second);\n        if (first == second) {\n            history.push_back(HistoryEntry{-1,\
    \ 0, -1, 0});\n            return false;\n        }\n        if (-parent_or_size[first]\
    \ < -parent_or_size[second]) {\n            std::swap(first, second);\n      \
    \  }\n        history.push_back(HistoryEntry{\n            first, parent_or_size[first],\
    \ second, parent_or_size[second]\n        });\n        parent_or_size[first] +=\
    \ parent_or_size[second];\n        parent_or_size[second] = first;\n        _component_count--;\n\
    \        return true;\n    }\n\n    bool undo() {\n        if (history.empty())\
    \ return false;\n        const HistoryEntry entry = history.back();\n        history.pop_back();\n\
    \        if (entry.first == -1) return true;\n        parent_or_size[entry.first]\
    \ = entry.first_value;\n        parent_or_size[entry.second] = entry.second_value;\n\
    \        _component_count++;\n        return true;\n    }\n\n    int snapshot()\
    \ const {\n        return history_size();\n    }\n\n    void rollback(int state)\
    \ {\n        assert(0 <= state && state <= history_size());\n        while (history_size()\
    \ > state) undo();\n    }\n\n    std::vector<std::vector<int>> groups() const\
    \ {\n        std::vector<int> leader_buffer(_n);\n        std::vector<int> group_sizes(_n,\
    \ 0);\n        for (int vertex = 0; vertex < _n; vertex++) {\n            leader_buffer[vertex]\
    \ = leader(vertex);\n            group_sizes[leader_buffer[vertex]]++;\n     \
    \   }\n        std::vector<std::vector<int>> result(_n);\n        for (int vertex\
    \ = 0; vertex < _n; vertex++) {\n            result[vertex].reserve(group_sizes[vertex]);\n\
    \        }\n        for (int vertex = 0; vertex < _n; vertex++) {\n          \
    \  result[leader_buffer[vertex]].push_back(vertex);\n        }\n        result.erase(\n\
    \            std::remove_if(\n                result.begin(), result.end(),\n\
    \                [](const std::vector<int>& group) { return group.empty(); }\n\
    \            ),\n            result.end()\n        );\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 10 \"ds/dynamic_connectivity/offline_dynamic_connectivity.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct OfflineDynamicConnectivity {\n\
    \   private:\n    struct Edge {\n        int u;\n        int v;\n        int begin;\n\
    \        int end;\n        bool alive;\n    };\n\n    struct Query {\n       \
    \ int u;\n        int v;\n        int time;\n    };\n\n    int _n;\n    int _time\
    \ = 0;\n    std::vector<Edge> _edges;\n    std::vector<Query> _queries;\n\n  \
    \  void dfs(\n        const std::vector<int>& offset,\n        const std::vector<std::pair<int,\
    \ int>>& stored_edges,\n        const std::vector<int>& query_at,\n        std::vector<bool>&\
    \ answer,\n        RollbackDsu& dsu,\n        int node,\n        int base\n  \
    \  ) const {\n        int snapshot = dsu.snapshot();\n        for (int i = offset[node];\
    \ i < offset[node + 1]; i++) {\n            auto [u, v] = stored_edges[i];\n \
    \           dsu.merge(u, v);\n        }\n        if (node >= base) {\n       \
    \     int query_id = query_at[node - base];\n            if (query_id != -1) {\n\
    \                const Query& query = _queries[query_id];\n                answer[query_id]\
    \ = dsu.same(query.u, query.v);\n            }\n        } else {\n           \
    \ dfs(offset, stored_edges, query_at, answer, dsu, 2 * node, base);\n        \
    \    dfs(offset, stored_edges, query_at, answer, dsu, 2 * node + 1, base);\n \
    \       }\n        dsu.rollback(snapshot);\n    }\n\n   public:\n    OfflineDynamicConnectivity()\
    \ : OfflineDynamicConnectivity(0) {}\n\n    explicit OfflineDynamicConnectivity(int\
    \ n) : _n(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n   \
    \     return _n;\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    int query_count() const {\n        return int(_queries.size());\n\
    \    }\n\n    int operation_count() const {\n        return _time;\n    }\n\n\
    \    void reserve_edges(int count) {\n        assert(0 <= count);\n        _edges.reserve(count);\n\
    \    }\n\n    void reserve_queries(int count) {\n        assert(0 <= count);\n\
    \        _queries.reserve(count);\n    }\n\n    bool edge_alive(int edge_id) const\
    \ {\n        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return\
    \ _edges[edge_id].alive;\n    }\n\n    int add_edge(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        int edge_id = int(_edges.size());\n\
    \        _edges.push_back(Edge{u, v, _time, -1, true});\n        _time++;\n  \
    \      return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n        assert(0\
    \ <= edge_id && edge_id < int(_edges.size()));\n        Edge& edge = _edges[edge_id];\n\
    \        if (!edge.alive) return false;\n        edge.end = _time;\n        edge.alive\
    \ = false;\n        _time++;\n        return true;\n    }\n\n    int add_query(int\
    \ u, int v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v <\
    \ _n);\n        int query_id = int(_queries.size());\n        _queries.push_back(Query{u,\
    \ v, _time});\n        _time++;\n        return query_id;\n    }\n\n    std::vector<bool>\
    \ solve() const {\n        std::vector<bool> answer(_queries.size(), false);\n\
    \        if (_queries.empty()) return answer;\n        if (_edges.empty()) {\n\
    \            for (int query_id = 0; query_id < int(_queries.size()); query_id++)\
    \ {\n                answer[query_id] = _queries[query_id].u == _queries[query_id].v;\n\
    \            }\n            return answer;\n        }\n\n        int base = 1;\n\
    \        while (base < _time) base *= 2;\n        int node_count = 2 * base;\n\
    \        std::vector<int> count(node_count, 0);\n        for (const Edge& edge\
    \ : _edges) {\n            int end = edge.alive ? _time : edge.end;\n        \
    \    if (edge.begin < end && edge.u != edge.v) {\n                int left = edge.begin\
    \ + base;\n                int right = end + base;\n                while (left\
    \ < right) {\n                    if (left & 1) count[left++]++;\n           \
    \         if (right & 1) count[--right]++;\n                    left /= 2;\n \
    \                   right /= 2;\n                }\n            }\n        }\n\
    \        std::vector<int> offset(node_count + 1, 0);\n        for (int node =\
    \ 1; node < node_count; node++) offset[node + 1] = offset[node] + count[node];\n\
    \        std::vector<int> cursor = offset;\n        std::vector<std::pair<int,\
    \ int>> stored_edges(offset[node_count]);\n        for (const Edge& edge : _edges)\
    \ {\n            int end = edge.alive ? _time : edge.end;\n            if (edge.begin\
    \ >= end || edge.u == edge.v) continue;\n            int left = edge.begin + base;\n\
    \            int right = end + base;\n            while (left < right) {\n   \
    \             if (left & 1) stored_edges[cursor[left]++] = {edge.u, edge.v}, left++;\n\
    \                if (right & 1) --right, stored_edges[cursor[right]++] = {edge.u,\
    \ edge.v};\n                left /= 2;\n                right /= 2;\n        \
    \    }\n        }\n        std::vector<int> query_at(base, -1);\n        for (int\
    \ query_id = 0; query_id < int(_queries.size()); query_id++) {\n            query_at[_queries[query_id].time]\
    \ = query_id;\n        }\n        RollbackDsu dsu(_n);\n        dsu.reserve_history(int(std::min<std::size_t>(_n,\
    \ stored_edges.size())));\n        dfs(offset, stored_edges, query_at, answer,\
    \ dsu, 1, base);\n        return answer;\n    }\n};\n\n}  // namespace ds\n} \
    \ // namespace m1une\n\n\n#line 1 \"ds/dynamic_connectivity/online_dynamic_connectivity.hpp\"\
    \n\n\n\n#line 9 \"ds/dynamic_connectivity/online_dynamic_connectivity.hpp\"\n\n\
    #line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n    using\
    \ value_type = T;\n\n    // Returns the identity element for addition, which is\
    \ 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    // Returns\
    \ the sum of a and b.\n    static constexpr T op(const T& a, const T& b) {\n \
    \       return a + b;\n    }\n\n    static constexpr T inv(const T& x) {\n   \
    \     return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/dynamic_tree/link_cut_tree.hpp\"\n\n\n\n#line 5 \"ds/dynamic_tree/link_cut_tree.hpp\"\
    \n#include <concepts>\n#line 9 \"ds/dynamic_tree/link_cut_tree.hpp\"\n\n#line\
    \ 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 11 \"ds/dynamic_tree/link_cut_tree.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsCommutativeGroup Group>\n\
    struct LinkCutTree {\n    using T = typename Group::value_type;\n\n   private:\n\
    \    struct Node {\n        int left = -1;\n        int right = -1;\n        int\
    \ parent = -1;\n        bool rev = false;\n        int size = 1;\n        int\
    \ virtual_size = 0;\n        int all_size = 1;\n        T value = Group::id();\n\
    \        T prod = Group::id();\n        T rev_prod = Group::id();\n        T virtual_prod\
    \ = Group::id();\n        T all_prod = Group::id();\n    };\n\n    struct EdgeInfo\
    \ {\n        int u = -1;\n        int v = -1;\n        int node = -1;\n      \
    \  bool alive = false;\n    };\n\n    std::vector<Node> _nodes;\n    std::vector<EdgeInfo>\
    \ _edges;\n    std::vector<int> _path_buffer;\n\n    static T make_node_value(const\
    \ T& value, int) {\n        return value;\n    }\n\n    static T make_node_value(T&&\
    \ value, int) {\n        return std::move(value);\n    }\n\n    template <class\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { Group::make(x);\
    \ } ||\n        requires(U x, int i) { Group::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    static T make_node_value(const U& value, int index) {\n     \
    \   if constexpr (requires(U x) { Group::make(x); }) {\n            return Group::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Group::make(x, i); }) {\n\
    \            return Group::make(value, index);\n        } else {\n           \
    \ return static_cast<T>(value);\n        }\n    }\n\n    int child_size(int node)\
    \ const {\n        return node == -1 ? 0 : _nodes[node].size;\n    }\n\n    int\
    \ child_all_size(int node) const {\n        return node == -1 ? 0 : _nodes[node].all_size;\n\
    \    }\n\n    T child_prod(int node) const {\n        return node == -1 ? Group::id()\
    \ : _nodes[node].prod;\n    }\n\n    T child_rev_prod(int node) const {\n    \
    \    return node == -1 ? Group::id() : _nodes[node].rev_prod;\n    }\n\n    T\
    \ child_all_prod(int node) const {\n        return node == -1 ? Group::id() :\
    \ _nodes[node].all_prod;\n    }\n\n    T node_subtree_prod(int node) const {\n\
    \        const Node& x = _nodes[node];\n        return Group::op(x.value, x.virtual_prod);\n\
    \    }\n\n    int node_subtree_size(int node) const {\n        return 1 + _nodes[node].virtual_size;\n\
    \    }\n\n    bool is_splay_root(int node) const {\n        int parent = _nodes[node].parent;\n\
    \        return parent == -1 || (_nodes[parent].left != node && _nodes[parent].right\
    \ != node);\n    }\n\n    void update(int node) {\n        Node& x = _nodes[node];\n\
    \        x.size = 1 + child_size(x.left) + child_size(x.right);\n        x.all_size\
    \ = 1 + x.virtual_size + child_all_size(x.left) + child_all_size(x.right);\n \
    \       x.prod = Group::op(Group::op(child_prod(x.left), x.value), child_prod(x.right));\n\
    \        x.rev_prod = Group::op(Group::op(child_rev_prod(x.right), x.value), child_rev_prod(x.left));\n\
    \        x.all_prod = Group::op(Group::op(child_all_prod(x.left), x.value),\n\
    \                                Group::op(x.virtual_prod, child_all_prod(x.right)));\n\
    \    }\n\n    void add_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size += _nodes[child].all_size;\n\
    \        x.virtual_prod = Group::op(x.virtual_prod, _nodes[child].all_prod);\n\
    \    }\n\n    void remove_virtual_child(int node, int child) {\n        if (child\
    \ == -1) return;\n        Node& x = _nodes[node];\n        x.virtual_size -= _nodes[child].all_size;\n\
    \        x.virtual_prod = Group::op(x.virtual_prod, Group::inv(_nodes[child].all_prod));\n\
    \    }\n\n    void apply_reverse(int node) {\n        if (node == -1) return;\n\
    \        Node& x = _nodes[node];\n        std::swap(x.left, x.right);\n      \
    \  std::swap(x.prod, x.rev_prod);\n        x.rev = !x.rev;\n    }\n\n    void\
    \ push(int node) {\n        if (node == -1 || !_nodes[node].rev) return;\n   \
    \     apply_reverse(_nodes[node].left);\n        apply_reverse(_nodes[node].right);\n\
    \        _nodes[node].rev = false;\n    }\n\n    void push_to(int node) {\n  \
    \      _path_buffer.clear();\n        int cur = node;\n        _path_buffer.push_back(cur);\n\
    \        while (!is_splay_root(cur)) {\n            cur = _nodes[cur].parent;\n\
    \            _path_buffer.push_back(cur);\n        }\n        for (int i = int(_path_buffer.size())\
    \ - 1; i >= 0; i--) push(_path_buffer[i]);\n    }\n\n    void rotate(int node)\
    \ {\n        int parent = _nodes[node].parent;\n        int grand = _nodes[parent].parent;\n\
    \        bool is_right = _nodes[parent].right == node;\n        int middle = is_right\
    \ ? _nodes[node].left : _nodes[node].right;\n\n        if (!is_splay_root(parent))\
    \ {\n            if (_nodes[grand].left == parent) {\n                _nodes[grand].left\
    \ = node;\n            } else {\n                _nodes[grand].right = node;\n\
    \            }\n        }\n        _nodes[node].parent = grand;\n\n        if\
    \ (is_right) {\n            _nodes[node].left = parent;\n            _nodes[parent].right\
    \ = middle;\n        } else {\n            _nodes[node].right = parent;\n    \
    \        _nodes[parent].left = middle;\n        }\n        if (middle != -1) _nodes[middle].parent\
    \ = parent;\n        _nodes[parent].parent = node;\n\n        update(parent);\n\
    \        update(node);\n    }\n\n    void splay(int node) {\n        push_to(node);\n\
    \        while (!is_splay_root(node)) {\n            int parent = _nodes[node].parent;\n\
    \            int grand = _nodes[parent].parent;\n            if (!is_splay_root(parent))\
    \ {\n                bool zig_zig = (_nodes[parent].left == node) == (_nodes[grand].left\
    \ == parent);\n                rotate(zig_zig ? parent : node);\n            }\n\
    \            rotate(node);\n        }\n    }\n\n    int access(int node) {\n \
    \       int last = -1;\n        for (int cur = node; cur != -1; cur = _nodes[cur].parent)\
    \ {\n            splay(cur);\n            add_virtual_child(cur, _nodes[cur].right);\n\
    \            remove_virtual_child(cur, last);\n            _nodes[cur].right =\
    \ last;\n            if (last != -1) _nodes[last].parent = cur;\n            update(cur);\n\
    \            last = cur;\n        }\n        splay(node);\n        return last;\n\
    \    }\n\n    void check_vertex(int v) const {\n        assert(0 <= v && v < int(_nodes.size()));\n\
    \    }\n\n    void check_edge(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n    }\n\n   public:\n    LinkCutTree() =\
    \ default;\n\n    explicit LinkCutTree(int n) {\n        assert(0 <= n);\n   \
    \     _nodes.reserve(n);\n        for (int i = 0; i < n; i++) add_vertex();\n\
    \    }\n\n    explicit LinkCutTree(const std::vector<T>& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(values[i]);\n\
    \    }\n\n    explicit LinkCutTree(std::vector<T>&& values) {\n        _nodes.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); i++) add_vertex(std::move(values[i]));\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Group::make(x); } ||\n        requires(U x, int i) { Group::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LinkCutTree(const\
    \ std::vector<U>& values) {\n        _nodes.reserve(values.size());\n        for\
    \ (int i = 0; i < int(values.size()); i++) add_vertex(make_node_value(values[i],\
    \ i));\n    }\n\n    int size() const {\n        return int(_nodes.size());\n\
    \    }\n\n    bool empty() const {\n        return _nodes.empty();\n    }\n\n\
    \    int add_vertex(const T& value = Group::id()) {\n        Node node;\n    \
    \    node.value = value;\n        node.prod = value;\n        node.rev_prod =\
    \ value;\n        node.all_prod = value;\n        _nodes.push_back(std::move(node));\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    int add_vertex(T&& value)\
    \ {\n        Node node;\n        node.value = std::move(value);\n        node.prod\
    \ = node.value;\n        node.rev_prod = node.value;\n        node.all_prod =\
    \ node.value;\n        _nodes.push_back(std::move(node));\n        return int(_nodes.size())\
    \ - 1;\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x,\
    \ int i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    int add_vertex(const U& value) {\n        return add_vertex(make_node_value(value,\
    \ size()));\n    }\n\n    int edge_count() const {\n        return int(_edges.size());\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        check_edge(edge_id);\n\
    \        return _edges[edge_id].alive;\n    }\n\n    int edge_node(int edge_id)\
    \ const {\n        check_edge(edge_id);\n        return _edges[edge_id].node;\n\
    \    }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n      \
    \  check_edge(edge_id);\n        return {_edges[edge_id].u, _edges[edge_id].v};\n\
    \    }\n\n    const T& get(int v) const {\n        check_vertex(v);\n        return\
    \ _nodes[v].value;\n    }\n\n    const T& operator[](int v) const {\n        return\
    \ get(v);\n    }\n\n    void set(int v, const T& value) {\n        check_vertex(v);\n\
    \        access(v);\n        _nodes[v].value = value;\n        update(v);\n  \
    \  }\n\n    void set(int v, T&& value) {\n        check_vertex(v);\n        access(v);\n\
    \        _nodes[v].value = std::move(value);\n        update(v);\n    }\n\n  \
    \  template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>)\
    \ && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x, int\
    \ i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n   \
    \ void set(int v, const U& value) {\n        set(v, make_node_value(value, v));\n\
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
    \ = Group::id()) {\n        check_vertex(u);\n        check_vertex(v);\n     \
    \   if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(value);\n        _edges.push_back(EdgeInfo{u, v,\
    \ node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    int\
    \ link_edge(int u, int v, T&& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        int edge_id = int(_edges.size());\n\
    \        int node = add_vertex(std::move(value));\n        _edges.push_back(EdgeInfo{u,\
    \ v, node, true});\n        bool ok1 = link(u, node);\n        bool ok2 = link(node,\
    \ v);\n        assert(ok1 && ok2);\n        return edge_id;\n    }\n\n    template\
    \ <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>, T>) && (\n  \
    \      requires(U x) { Group::make(x); } ||\n        requires(U x, int i) { Group::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    int link_edge(int u,\
    \ int v, const U& value) {\n        check_vertex(u);\n        check_vertex(v);\n\
    \        if (u == v || connected(u, v)) return -1;\n        return link_edge(u,\
    \ v, make_node_value(value, size()));\n    }\n\n    // Cuts edge `(u, v)`. Internally\
    \ calls `evert(u)`, so the represented root may change.\n    bool cut(int u, int\
    \ v) {\n        check_vertex(u);\n        check_vertex(v);\n        if (u == v)\
    \ return false;\n        evert(u);\n        access(v);\n        if (_nodes[v].left\
    \ != u || _nodes[u].right != -1) return false;\n        _nodes[v].left = -1;\n\
    \        _nodes[u].parent = -1;\n        update(v);\n        return true;\n  \
    \  }\n\n    // Cuts the parent edge of `v` in the current represented-root orientation.\n\
    \    // Unlike `cut(u, v)`, this does not call `evert`.\n    bool cut_parent(int\
    \ v) {\n        check_vertex(v);\n        access(v);\n        int left = _nodes[v].left;\n\
    \        if (left == -1) return false;\n        _nodes[v].left = -1;\n       \
    \ _nodes[left].parent = -1;\n        update(v);\n        return true;\n    }\n\
    \n    bool cut_edge(int edge_id) {\n        check_edge(edge_id);\n        EdgeInfo&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        bool\
    \ ok1 = cut(edge.u, edge.node);\n        bool ok2 = cut(edge.node, edge.v);\n\
    \        if (ok1 && ok2) edge.alive = false;\n        return ok1 && ok2;\n   \
    \ }\n\n    const T& get_edge(int edge_id) const {\n        return get(edge_node(edge_id));\n\
    \    }\n\n    void set_edge(int edge_id, const T& value) {\n        set(edge_node(edge_id),\
    \ value);\n    }\n\n    void set_edge(int edge_id, T&& value) {\n        set(edge_node(edge_id),\
    \ std::move(value));\n    }\n\n    template <class U>\n    requires (!std::same_as<std::remove_cvref_t<U>,\
    \ T>) && (\n        requires(U x) { Group::make(x); } ||\n        requires(U x,\
    \ int i) { Group::make(x, i); } ||\n        std::convertible_to<U, T>\n    )\n\
    \    void set_edge(int edge_id, const U& value) {\n        set(edge_node(edge_id),\
    \ make_node_value(value, edge_node(edge_id)));\n    }\n\n    // Returns the path\
    \ product from `u` to `v`. Internally calls `evert(u)`,\n    // so the represented\
    \ root may change.\n    T prod(int u, int v) {\n        check_vertex(u);\n   \
    \     check_vertex(v);\n        assert(connected(u, v));\n        evert(u);\n\
    \        access(v);\n        return _nodes[v].prod;\n    }\n\n    // Alias for\
    \ `prod(u, v)`. Internally calls `evert(u)`,\n    // so the represented root may\
    \ change.\n    T path_prod(int u, int v) {\n        return prod(u, v);\n    }\n\
    \n    // Returns the number of vertices on path `u`-`v`. Internally calls `evert(u)`,\n\
    \    // so the represented root may change.\n    int path_size(int u, int v) {\n\
    \        check_vertex(u);\n        check_vertex(v);\n        assert(connected(u,\
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
    \ child);\n        return Group::op(whole, Group::inv(sub));\n    }\n\n    //\
    \ Returns `v`'s rooted subtree size excluding the child-side subtree.\n    int\
    \ subtree_size_excluding_child(int root, int v, int child) {\n        check_vertex(root);\n\
    \        check_vertex(v);\n        check_vertex(child);\n        assert(parent(root,\
    \ child) == v);\n        return subtree_size(root, v) - subtree_size(root, child);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/dynamic_connectivity/online_dynamic_connectivity.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct OnlineDynamicConnectivity {\n\
    \   private:\n    using Forest = LinkCutTree<m1une::monoid::Add<int>>;\n\n   \
    \ struct Edge {\n        int u;\n        int v;\n        bool alive;\n       \
    \ bool tree;\n        int previous_u = -1;\n        int next_u = -1;\n       \
    \ int previous_v = -1;\n        int next_v = -1;\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    int _active_edge_count = 0;\n    Forest _forest;\n  \
    \  std::vector<Edge> _edges;\n    std::vector<int> _tree_head;\n    std::vector<int>\
    \ _non_tree_head;\n    std::vector<std::uint32_t> _visited;\n    std::vector<std::uint32_t>\
    \ _edge_visited;\n    std::uint32_t _visit_token = 0;\n    std::vector<int> _stack;\n\
    \    std::vector<int> _component;\n\n    int endpoint_side(const Edge& edge, int\
    \ v) const {\n        return edge.u == v ? 0 : 1;\n    }\n\n    int& previous(Edge&\
    \ edge, int side) {\n        return side == 0 ? edge.previous_u : edge.previous_v;\n\
    \    }\n\n    int& next(Edge& edge, int side) {\n        return side == 0 ? edge.next_u\
    \ : edge.next_v;\n    }\n\n    int next(const Edge& edge, int side) const {\n\
    \        return side == 0 ? edge.next_u : edge.next_v;\n    }\n\n    void insert_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int old_head = head[v];\n        previous(edge, side) = -1;\n       \
    \ next(edge, side) = old_head;\n        if (old_head != -1) {\n            Edge&\
    \ old_edge = _edges[old_head];\n            previous(old_edge, endpoint_side(old_edge,\
    \ v)) = edge_id;\n        }\n        head[v] = edge_id;\n    }\n\n    void erase_one(std::vector<int>&\
    \ head, int edge_id, int v, int side) {\n        Edge& edge = _edges[edge_id];\n\
    \        int previous_id = previous(edge, side);\n        int next_id = next(edge,\
    \ side);\n        if (previous_id == -1) {\n            head[v] = next_id;\n \
    \       } else {\n            Edge& previous_edge = _edges[previous_id];\n   \
    \         next(previous_edge, endpoint_side(previous_edge, v)) = next_id;\n  \
    \      }\n        if (next_id != -1) {\n            Edge& next_edge = _edges[next_id];\n\
    \            previous(next_edge, endpoint_side(next_edge, v)) = previous_id;\n\
    \        }\n        previous(edge, side) = -1;\n        next(edge, side) = -1;\n\
    \    }\n\n    void insert_incident(std::vector<int>& head, int edge_id) {\n  \
    \      const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n        int\
    \ v = edge.v;\n        insert_one(head, edge_id, u, 0);\n        if (u != v) insert_one(head,\
    \ edge_id, v, 1);\n    }\n\n    void erase_incident(std::vector<int>& head, int\
    \ edge_id) {\n        const Edge& edge = _edges[edge_id];\n        int u = edge.u;\n\
    \        int v = edge.v;\n        erase_one(head, edge_id, u, 0);\n        if\
    \ (u != v) erase_one(head, edge_id, v, 1);\n    }\n\n    void make_tree_edge(int\
    \ edge_id) {\n        Edge& edge = _edges[edge_id];\n        assert(edge.alive\
    \ && !edge.tree && edge.u != edge.v);\n        erase_incident(_non_tree_head,\
    \ edge_id);\n        bool linked = _forest.link(edge.u, edge.v);\n        assert(linked);\n\
    \        edge.tree = true;\n        insert_incident(_tree_head, edge_id);\n  \
    \      _component_count--;\n    }\n\n    void collect_component(int start) {\n\
    \        _visit_token++;\n        if (_visit_token == 0) {\n            std::fill(_visited.begin(),\
    \ _visited.end(), 0);\n            std::fill(_edge_visited.begin(), _edge_visited.end(),\
    \ 0);\n            _visit_token = 1;\n        }\n        _stack.clear();\n   \
    \     _component.clear();\n        _visited[start] = _visit_token;\n        _stack.push_back(start);\n\
    \        while (!_stack.empty()) {\n            int v = _stack.back();\n     \
    \       _stack.pop_back();\n            _component.push_back(v);\n           \
    \ for (int edge_id = _tree_head[v]; edge_id != -1;) {\n                const Edge&\
    \ edge = _edges[edge_id];\n                int edge_side = endpoint_side(edge,\
    \ v);\n                edge_id = next(edge, edge_side);\n                int to\
    \ = edge.u ^ edge.v ^ v;\n                if (_visited[to] == _visit_token) continue;\n\
    \                _visited[to] = _visit_token;\n                _stack.push_back(to);\n\
    \            }\n        }\n    }\n\n    void reconnect(int u, int v) {\n     \
    \   int start = _forest.component_size(u) <= _forest.component_size(v) ? u : v;\n\
    \        collect_component(start);\n        int replacement = -1;\n        for\
    \ (int x : _component) {\n            for (int edge_id = _non_tree_head[x]; edge_id\
    \ != -1;) {\n                const Edge& edge = _edges[edge_id];\n           \
    \     int edge_side = endpoint_side(edge, x);\n                int current_edge\
    \ = edge_id;\n                edge_id = next(edge, edge_side);\n             \
    \   if (_edge_visited[current_edge] == _visit_token) continue;\n             \
    \   _edge_visited[current_edge] = _visit_token;\n                if (_visited[edge.u]\
    \ != _visit_token || _visited[edge.v] != _visit_token) {\n                   \
    \ replacement = current_edge;\n                    break;\n                }\n\
    \            }\n            if (replacement != -1) break;\n        }\n       \
    \ if (replacement != -1) make_tree_edge(replacement);\n    }\n\n   public:\n \
    \   OnlineDynamicConnectivity() : OnlineDynamicConnectivity(0) {}\n\n    explicit\
    \ OnlineDynamicConnectivity(int n)\n        : _n(n),\n          _component_count(n),\n\
    \          _forest(n),\n          _tree_head(n, -1),\n          _non_tree_head(n,\
    \ -1),\n          _visited(n, 0) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    int edge_count() const {\n\
    \        return int(_edges.size());\n    }\n\n    int active_edge_count() const\
    \ {\n        return _active_edge_count;\n    }\n\n    int component_count() const\
    \ {\n        return _component_count;\n    }\n\n    void reserve_edges(int count)\
    \ {\n        assert(0 <= count);\n        _edges.reserve(count);\n        _edge_visited.reserve(count);\n\
    \    }\n\n    bool edge_alive(int edge_id) const {\n        assert(0 <= edge_id\
    \ && edge_id < int(_edges.size()));\n        return _edges[edge_id].alive;\n \
    \   }\n\n    std::pair<int, int> edge_endpoints(int edge_id) const {\n       \
    \ assert(0 <= edge_id && edge_id < int(_edges.size()));\n        return {_edges[edge_id].u,\
    \ _edges[edge_id].v};\n    }\n\n    bool connected(int u, int v) {\n        assert(0\
    \ <= u && u < _n);\n        assert(0 <= v && v < _n);\n        return _forest.connected(u,\
    \ v);\n    }\n\n    bool same(int u, int v) {\n        return connected(u, v);\n\
    \    }\n\n    int component_size(int v) {\n        assert(0 <= v && v < _n);\n\
    \        return _forest.component_size(v);\n    }\n\n    int add_edge(int u, int\
    \ v) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        bool is_tree = u != v && _forest.link(u, v);\n        int edge_id = int(_edges.size());\n\
    \        Edge edge;\n        edge.u = u;\n        edge.v = v;\n        edge.alive\
    \ = true;\n        edge.tree = is_tree;\n        _edges.push_back(edge);\n   \
    \     _edge_visited.push_back(0);\n        _active_edge_count++;\n        if (is_tree)\
    \ {\n            insert_incident(_tree_head, edge_id);\n            _component_count--;\n\
    \        } else {\n            insert_incident(_non_tree_head, edge_id);\n   \
    \     }\n        return edge_id;\n    }\n\n    bool erase_edge(int edge_id) {\n\
    \        assert(0 <= edge_id && edge_id < int(_edges.size()));\n        Edge&\
    \ edge = _edges[edge_id];\n        if (!edge.alive) return false;\n        edge.alive\
    \ = false;\n        _active_edge_count--;\n        if (!edge.tree) {\n       \
    \     erase_incident(_non_tree_head, edge_id);\n            return true;\n   \
    \     }\n\n        erase_incident(_tree_head, edge_id);\n        bool cut = _forest.cut(edge.u,\
    \ edge.v);\n        assert(cut);\n        _component_count++;\n        reconnect(edge.u,\
    \ edge.v);\n        return true;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 6 \"ds/dynamic_connectivity/all.hpp\"\n\n\n#line 11 \"verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp\"\
    \n\nstruct NaiveDynamicGraph {\n    struct Edge {\n        int u;\n        int\
    \ v;\n        bool alive;\n    };\n\n    int n;\n    std::vector<Edge> edges;\n\
    \n    explicit NaiveDynamicGraph(int n) : n(n) {}\n\n    int add_edge(int u, int\
    \ v) {\n        int id = int(edges.size());\n        edges.push_back(Edge{u, v,\
    \ true});\n        return id;\n    }\n\n    bool erase_edge(int id) {\n      \
    \  if (!edges[id].alive) return false;\n        edges[id].alive = false;\n   \
    \     return true;\n    }\n\n    std::vector<int> component(int start) const {\n\
    \        std::vector<std::vector<int>> graph(n);\n        for (const Edge& edge\
    \ : edges) {\n            if (!edge.alive || edge.u == edge.v) continue;\n   \
    \         graph[edge.u].push_back(edge.v);\n            graph[edge.v].push_back(edge.u);\n\
    \        }\n        std::vector<int> visited(n, false);\n        std::queue<int>\
    \ queue;\n        std::vector<int> vertices;\n        visited[start] = true;\n\
    \        queue.push(start);\n        while (!queue.empty()) {\n            int\
    \ v = queue.front();\n            queue.pop();\n            vertices.push_back(v);\n\
    \            for (int to : graph[v]) {\n                if (visited[to]) continue;\n\
    \                visited[to] = true;\n                queue.push(to);\n      \
    \      }\n        }\n        return vertices;\n    }\n\n    bool connected(int\
    \ u, int v) const {\n        std::vector<int> vertices = component(u);\n     \
    \   for (int x : vertices) {\n            if (x == v) return true;\n        }\n\
    \        return false;\n    }\n\n    int component_count() const {\n        std::vector<bool>\
    \ visited(n, false);\n        int result = 0;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (visited[v]) continue;\n            result++;\n     \
    \       for (int x : component(v)) visited[x] = true;\n        }\n        return\
    \ result;\n    }\n};\n\nvoid test_online_basic() {\n    m1une::ds::OnlineDynamicConnectivity\
    \ graph(4);\n    graph.reserve_edges(8);\n    int e01 = graph.add_edge(0, 1);\n\
    \    int e12 = graph.add_edge(1, 2);\n    int e02 = graph.add_edge(0, 2);\n  \
    \  int loop = graph.add_edge(3, 3);\n    assert(graph.connected(0, 2));\n    assert(graph.component_size(0)\
    \ == 3);\n    assert(graph.component_count() == 2);\n    assert(graph.active_edge_count()\
    \ == 4);\n\n    assert(graph.erase_edge(e12));\n    assert(graph.connected(0,\
    \ 2));\n    assert(graph.erase_edge(e02));\n    assert(!graph.connected(0, 2));\n\
    \    assert(graph.component_count() == 3);\n    assert(!graph.erase_edge(e02));\n\
    \    assert(graph.erase_edge(loop));\n    assert(graph.erase_edge(e01));\n   \
    \ assert(graph.component_count() == 4);\n}\n\nvoid test_offline_basic() {\n  \
    \  m1une::ds::OfflineDynamicConnectivity graph(3);\n    graph.reserve_edges(8);\n\
    \    graph.reserve_queries(8);\n    int e01 = graph.add_edge(0, 1);\n    int q0\
    \ = graph.add_query(0, 2);\n    int e12 = graph.add_edge(1, 2);\n    int q1 =\
    \ graph.add_query(0, 2);\n    assert(graph.erase_edge(e01));\n    int q2 = graph.add_query(0,\
    \ 2);\n    assert(!graph.erase_edge(e01));\n    int parallel = graph.add_edge(1,\
    \ 2);\n    int q3 = graph.add_query(1, 2);\n    assert(graph.erase_edge(e12));\n\
    \    int q4 = graph.add_query(1, 2);\n    assert(graph.erase_edge(parallel));\n\
    \    int q5 = graph.add_query(1, 2);\n\n    std::vector<bool> answer = graph.solve();\n\
    \    assert(!answer[q0]);\n    assert(answer[q1]);\n    assert(!answer[q2]);\n\
    \    assert(answer[q3]);\n    assert(answer[q4]);\n    assert(!answer[q5]);\n\
    \    assert(answer == graph.solve());\n\n    int restored = graph.add_edge(0,\
    \ 2);\n    int q6 = graph.add_query(0, 2);\n    answer = graph.solve();\n    assert(answer[q6]);\n\
    \    assert(graph.erase_edge(restored));\n}\n\nvoid test_online_random() {\n \
    \   std::mt19937 random(123456789);\n    for (int test = 0; test < 80; test++)\
    \ {\n        int n = 1 + random() % 15;\n        m1une::ds::OnlineDynamicConnectivity\
    \ graph(n);\n        NaiveDynamicGraph naive(n);\n        std::vector<int> active;\n\
    \        for (int operation = 0; operation < 1000; operation++) {\n          \
    \  int type = random() % 5;\n            if (type <= 1 || active.empty()) {\n\
    \                int u = random() % n;\n                int v = random() % n;\n\
    \                int id = graph.add_edge(u, v);\n                assert(id ==\
    \ naive.add_edge(u, v));\n                active.push_back(id);\n            }\
    \ else if (type == 2) {\n                int index = random() % active.size();\n\
    \                int id = active[index];\n                std::swap(active[index],\
    \ active.back());\n                active.pop_back();\n                assert(graph.erase_edge(id));\n\
    \                assert(naive.erase_edge(id));\n            } else {\n       \
    \         int u = random() % n;\n                int v = random() % n;\n     \
    \           assert(graph.connected(u, v) == naive.connected(u, v));\n        \
    \        assert(graph.component_size(u) == int(naive.component(u).size()));\n\
    \            }\n            assert(graph.active_edge_count() == int(active.size()));\n\
    \            assert(graph.component_count() == naive.component_count());\n   \
    \     }\n    }\n}\n\nvoid test_offline_random() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 100; test++) {\n        int n = 1 + random() %\
    \ 12;\n        m1une::ds::OfflineDynamicConnectivity graph(n);\n        NaiveDynamicGraph\
    \ naive(n);\n        std::vector<int> active;\n        std::vector<bool> expected;\n\
    \        for (int operation = 0; operation < 500; operation++) {\n           \
    \ int type = random() % 4;\n            if (type == 0 || active.empty()) {\n \
    \               int u = random() % n;\n                int v = random() % n;\n\
    \                int id = graph.add_edge(u, v);\n                assert(id ==\
    \ naive.add_edge(u, v));\n                active.push_back(id);\n            }\
    \ else if (type == 1) {\n                int index = random() % active.size();\n\
    \                int id = active[index];\n                std::swap(active[index],\
    \ active.back());\n                active.pop_back();\n                assert(graph.erase_edge(id));\n\
    \                assert(naive.erase_edge(id));\n            } else {\n       \
    \         int u = random() % n;\n                int v = random() % n;\n     \
    \           assert(graph.add_query(u, v) == int(expected.size()));\n         \
    \       expected.push_back(naive.connected(u, v));\n            }\n        }\n\
    \        assert(graph.solve() == expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_online_basic();\n\
    \    test_offline_basic();\n    test_online_random();\n    test_offline_random();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include \"../../../utilities/fast_io.hpp\"\n#include <queue>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#include \"../../../ds/dynamic_connectivity/all.hpp\"\
    \n\nstruct NaiveDynamicGraph {\n    struct Edge {\n        int u;\n        int\
    \ v;\n        bool alive;\n    };\n\n    int n;\n    std::vector<Edge> edges;\n\
    \n    explicit NaiveDynamicGraph(int n) : n(n) {}\n\n    int add_edge(int u, int\
    \ v) {\n        int id = int(edges.size());\n        edges.push_back(Edge{u, v,\
    \ true});\n        return id;\n    }\n\n    bool erase_edge(int id) {\n      \
    \  if (!edges[id].alive) return false;\n        edges[id].alive = false;\n   \
    \     return true;\n    }\n\n    std::vector<int> component(int start) const {\n\
    \        std::vector<std::vector<int>> graph(n);\n        for (const Edge& edge\
    \ : edges) {\n            if (!edge.alive || edge.u == edge.v) continue;\n   \
    \         graph[edge.u].push_back(edge.v);\n            graph[edge.v].push_back(edge.u);\n\
    \        }\n        std::vector<int> visited(n, false);\n        std::queue<int>\
    \ queue;\n        std::vector<int> vertices;\n        visited[start] = true;\n\
    \        queue.push(start);\n        while (!queue.empty()) {\n            int\
    \ v = queue.front();\n            queue.pop();\n            vertices.push_back(v);\n\
    \            for (int to : graph[v]) {\n                if (visited[to]) continue;\n\
    \                visited[to] = true;\n                queue.push(to);\n      \
    \      }\n        }\n        return vertices;\n    }\n\n    bool connected(int\
    \ u, int v) const {\n        std::vector<int> vertices = component(u);\n     \
    \   for (int x : vertices) {\n            if (x == v) return true;\n        }\n\
    \        return false;\n    }\n\n    int component_count() const {\n        std::vector<bool>\
    \ visited(n, false);\n        int result = 0;\n        for (int v = 0; v < n;\
    \ v++) {\n            if (visited[v]) continue;\n            result++;\n     \
    \       for (int x : component(v)) visited[x] = true;\n        }\n        return\
    \ result;\n    }\n};\n\nvoid test_online_basic() {\n    m1une::ds::OnlineDynamicConnectivity\
    \ graph(4);\n    graph.reserve_edges(8);\n    int e01 = graph.add_edge(0, 1);\n\
    \    int e12 = graph.add_edge(1, 2);\n    int e02 = graph.add_edge(0, 2);\n  \
    \  int loop = graph.add_edge(3, 3);\n    assert(graph.connected(0, 2));\n    assert(graph.component_size(0)\
    \ == 3);\n    assert(graph.component_count() == 2);\n    assert(graph.active_edge_count()\
    \ == 4);\n\n    assert(graph.erase_edge(e12));\n    assert(graph.connected(0,\
    \ 2));\n    assert(graph.erase_edge(e02));\n    assert(!graph.connected(0, 2));\n\
    \    assert(graph.component_count() == 3);\n    assert(!graph.erase_edge(e02));\n\
    \    assert(graph.erase_edge(loop));\n    assert(graph.erase_edge(e01));\n   \
    \ assert(graph.component_count() == 4);\n}\n\nvoid test_offline_basic() {\n  \
    \  m1une::ds::OfflineDynamicConnectivity graph(3);\n    graph.reserve_edges(8);\n\
    \    graph.reserve_queries(8);\n    int e01 = graph.add_edge(0, 1);\n    int q0\
    \ = graph.add_query(0, 2);\n    int e12 = graph.add_edge(1, 2);\n    int q1 =\
    \ graph.add_query(0, 2);\n    assert(graph.erase_edge(e01));\n    int q2 = graph.add_query(0,\
    \ 2);\n    assert(!graph.erase_edge(e01));\n    int parallel = graph.add_edge(1,\
    \ 2);\n    int q3 = graph.add_query(1, 2);\n    assert(graph.erase_edge(e12));\n\
    \    int q4 = graph.add_query(1, 2);\n    assert(graph.erase_edge(parallel));\n\
    \    int q5 = graph.add_query(1, 2);\n\n    std::vector<bool> answer = graph.solve();\n\
    \    assert(!answer[q0]);\n    assert(answer[q1]);\n    assert(!answer[q2]);\n\
    \    assert(answer[q3]);\n    assert(answer[q4]);\n    assert(!answer[q5]);\n\
    \    assert(answer == graph.solve());\n\n    int restored = graph.add_edge(0,\
    \ 2);\n    int q6 = graph.add_query(0, 2);\n    answer = graph.solve();\n    assert(answer[q6]);\n\
    \    assert(graph.erase_edge(restored));\n}\n\nvoid test_online_random() {\n \
    \   std::mt19937 random(123456789);\n    for (int test = 0; test < 80; test++)\
    \ {\n        int n = 1 + random() % 15;\n        m1une::ds::OnlineDynamicConnectivity\
    \ graph(n);\n        NaiveDynamicGraph naive(n);\n        std::vector<int> active;\n\
    \        for (int operation = 0; operation < 1000; operation++) {\n          \
    \  int type = random() % 5;\n            if (type <= 1 || active.empty()) {\n\
    \                int u = random() % n;\n                int v = random() % n;\n\
    \                int id = graph.add_edge(u, v);\n                assert(id ==\
    \ naive.add_edge(u, v));\n                active.push_back(id);\n            }\
    \ else if (type == 2) {\n                int index = random() % active.size();\n\
    \                int id = active[index];\n                std::swap(active[index],\
    \ active.back());\n                active.pop_back();\n                assert(graph.erase_edge(id));\n\
    \                assert(naive.erase_edge(id));\n            } else {\n       \
    \         int u = random() % n;\n                int v = random() % n;\n     \
    \           assert(graph.connected(u, v) == naive.connected(u, v));\n        \
    \        assert(graph.component_size(u) == int(naive.component(u).size()));\n\
    \            }\n            assert(graph.active_edge_count() == int(active.size()));\n\
    \            assert(graph.component_count() == naive.component_count());\n   \
    \     }\n    }\n}\n\nvoid test_offline_random() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 100; test++) {\n        int n = 1 + random() %\
    \ 12;\n        m1une::ds::OfflineDynamicConnectivity graph(n);\n        NaiveDynamicGraph\
    \ naive(n);\n        std::vector<int> active;\n        std::vector<bool> expected;\n\
    \        for (int operation = 0; operation < 500; operation++) {\n           \
    \ int type = random() % 4;\n            if (type == 0 || active.empty()) {\n \
    \               int u = random() % n;\n                int v = random() % n;\n\
    \                int id = graph.add_edge(u, v);\n                assert(id ==\
    \ naive.add_edge(u, v));\n                active.push_back(id);\n            }\
    \ else if (type == 1) {\n                int index = random() % active.size();\n\
    \                int id = active[index];\n                std::swap(active[index],\
    \ active.back());\n                active.pop_back();\n                assert(graph.erase_edge(id));\n\
    \                assert(naive.erase_edge(id));\n            } else {\n       \
    \         int u = random() % n;\n                int v = random() % n;\n     \
    \           assert(graph.add_query(u, v) == int(expected.size()));\n         \
    \       expected.push_back(naive.connected(u, v));\n            }\n        }\n\
    \        assert(graph.solve() == expected);\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_online_basic();\n\
    \    test_offline_basic();\n    test_online_random();\n    test_offline_random();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - ds/dynamic_connectivity/all.hpp
  - ds/dynamic_connectivity/offline_dynamic_connectivity.hpp
  - ds/dsu/rollback_dsu.hpp
  - ds/dynamic_connectivity/online_dynamic_connectivity.hpp
  - monoid/add.hpp
  - ds/dynamic_tree/link_cut_tree.hpp
  - monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
- /verify/verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp.html
title: verify/ds/dynamic_connectivity/dynamic_connectivity.test.cpp
---
