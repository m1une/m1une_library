---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/dp/knapsack.hpp
    title: Knapsack Helpers
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
  bundledCode: "#line 1 \"verify/algo/dp/knapsack.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <algorithm>\n#include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/algo/dp/knapsack.test.cpp\"\
    \n#include <limits>\n#include <vector>\n\n#line 1 \"algo/dp/knapsack.hpp\"\n\n\
    \n\n#line 7 \"algo/dp/knapsack.hpp\"\n#include <deque>\n#line 10 \"algo/dp/knapsack.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\ninline std::vector<char> subset_sum_reachable(const\
    \ std::vector<int>& weights, int limit) {\n    assert(0 <= limit);\n    using\
    \ Word = unsigned long long;\n    constexpr int word_bits = std::numeric_limits<Word>::digits;\n\
    \n    const std::size_t bit_count = std::size_t(limit) + 1;\n    std::vector<Word>\
    \ bits((bit_count + word_bits - 1) / word_bits, Word(0));\n    bits[0] = Word(1);\n\
    \n    auto trim = [&]() {\n        const int extra = int(bit_count % word_bits);\n\
    \        if (extra != 0) {\n            bits.back() &= (Word(1) << extra) - Word(1);\n\
    \        }\n    };\n\n    for (int weight : weights) {\n        assert(0 <= weight);\n\
    \        if (weight == 0 || limit < weight) continue;\n\n        const std::size_t\
    \ word_shift = std::size_t(weight / word_bits);\n        const int bit_shift =\
    \ weight % word_bits;\n        for (std::size_t i = bits.size() - word_shift;\
    \ i-- > 0;) {\n            const Word source = bits[i];\n            if (source\
    \ == Word(0)) continue;\n            const std::size_t target = i + word_shift;\n\
    \            bits[target] |= source << bit_shift;\n            if (bit_shift !=\
    \ 0 && target + 1 < bits.size()) {\n                bits[target + 1] |= source\
    \ >> (word_bits - bit_shift);\n            }\n        }\n        trim();\n   \
    \ }\n\n    std::vector<char> reachable(std::size_t(limit) + 1, 0);\n    for (int\
    \ sum = 0; sum <= limit; ++sum) {\n        reachable[sum] = char((bits[std::size_t(sum\
    \ / word_bits)] >> (sum % word_bits)) & Word(1));\n    }\n    return reachable;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> zero_one_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest() /\
    \ Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(0 <=\
    \ capacity);\n\n    std::vector<Value> dp(std::size_t(capacity) + 1, neg_inf);\n\
    \    dp[0] = Value{};\n    for (std::size_t item = 0; item < weights.size(); ++item)\
    \ {\n        const int weight = weights[item];\n        assert(0 <= weight);\n\
    \        for (int current = capacity; weight <= current; --current) {\n      \
    \      if (dp[current - weight] == neg_inf) continue;\n            dp[current]\
    \ = std::max(dp[current], dp[current - weight] + values[item]);\n        }\n \
    \   }\n\n    for (int current = 1; current <= capacity; ++current) {\n       \
    \ dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Value = long long>\nstd::vector<Value> bounded_knapsack_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<Value>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity,\n    Value neg_inf = std::numeric_limits<Value>::lowest()\
    \ / Value(4)\n) {\n    assert(weights.size() == values.size());\n    assert(weights.size()\
    \ == counts.size());\n    assert(0 <= capacity);\n\n    std::vector<Value> dp(std::size_t(capacity)\
    \ + 1, neg_inf);\n    dp[0] = Value{};\n\n    for (std::size_t item = 0; item\
    \ < weights.size(); ++item) {\n        const int weight = weights[item];\n   \
    \     const Value value = values[item];\n        const int count = counts[item];\n\
    \        assert(0 <= weight);\n        assert(0 <= count);\n        if (count\
    \ == 0) continue;\n\n        if (weight == 0) {\n            if (Value{} < value)\
    \ {\n                const Value gain = value * Value(count);\n              \
    \  for (Value& current : dp) {\n                    if (current != neg_inf) current\
    \ += gain;\n                }\n            }\n            continue;\n        }\n\
    \n        std::vector<Value> next = dp;\n        for (int residue = 0; residue\
    \ < weight && residue <= capacity; ++residue) {\n            std::deque<int> indices;\n\
    \            std::deque<Value> bases;\n            int k = 0;\n            for\
    \ (int current = residue; current <= capacity; current += weight, ++k) {\n   \
    \             if (dp[current] != neg_inf) {\n                    const Value base\
    \ = dp[current] - Value(k) * value;\n                    while (!bases.empty()\
    \ && bases.back() <= base) {\n                        bases.pop_back();\n    \
    \                    indices.pop_back();\n                    }\n            \
    \        bases.push_back(base);\n                    indices.push_back(k);\n \
    \               }\n\n                while (!indices.empty() && indices.front()\
    \ < k - count) {\n                    indices.pop_front();\n                 \
    \   bases.pop_front();\n                }\n                if (!bases.empty())\
    \ {\n                    next[current] = std::max(next[current], bases.front()\
    \ + Value(k) * value);\n                }\n            }\n        }\n        dp.swap(next);\n\
    \    }\n\n    for (int current = 1; current <= capacity; ++current) {\n      \
    \  dp[current] = std::max(dp[current], dp[current - 1]);\n    }\n    return dp;\n\
    }\n\ntemplate <typename Weight = long long>\nstd::vector<Weight> zero_one_knapsack_min_weight_for_value(\n\
    \    const std::vector<Weight>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit,\n    Weight inf = std::numeric_limits<Weight>::max() / Weight(4)\n\
    ) {\n    assert(weights.size() == values.size());\n    assert(0 <= value_limit);\n\
    \n    std::vector<Weight> dp(std::size_t(value_limit) + 1, inf);\n    dp[0] =\
    \ Weight{};\n    for (std::size_t item = 0; item < weights.size(); ++item) {\n\
    \        assert(Weight{} <= weights[item]);\n        assert(0 <= values[item]);\n\
    \        for (int value = value_limit; values[item] <= value; --value) {\n   \
    \         if (dp[value - values[item]] == inf) continue;\n            dp[value]\
    \ = std::min(dp[value], dp[value - values[item]] + weights[item]);\n        }\n\
    \    }\n    return dp;\n}\n\n}  // namespace algo\n}  // namespace m1une\n\n\n\
    #line 10 \"verify/algo/dp/knapsack.test.cpp\"\n\nstd::vector<char> naive_subset_sum(const\
    \ std::vector<int>& weights, int limit) {\n    std::vector<char> reachable(limit\
    \ + 1, 0);\n    reachable[0] = 1;\n    for (int weight : weights) {\n        for\
    \ (int sum = limit; weight <= sum; --sum) {\n            if (reachable[sum - weight])\
    \ reachable[sum] = 1;\n        }\n    }\n    return reachable;\n}\n\nstd::vector<long\
    \ long> naive_zero_one_max_value(\n    const std::vector<int>& weights,\n    const\
    \ std::vector<long long>& values,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n   \
    \ for (int mask = 0; mask < (1 << n); ++mask) {\n        int weight = 0;\n   \
    \     long long value = 0;\n        for (int i = 0; i < n; ++i) {\n          \
    \  if ((mask >> i) & 1) {\n                weight += weights[i];\n           \
    \     value += values[i];\n            }\n        }\n        if (weight <= capacity)\
    \ {\n            for (int current = weight; current <= capacity; ++current) {\n\
    \                result[current] = std::max(result[current], value);\n       \
    \     }\n        }\n    }\n    return result;\n}\n\nstd::vector<long long> naive_bounded_max_value(\n\
    \    const std::vector<int>& weights,\n    const std::vector<long long>& values,\n\
    \    const std::vector<int>& counts,\n    int capacity\n) {\n    std::vector<long\
    \ long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n\n \
    \   auto dfs = [&](auto& self, int item, int weight, long long value) -> void\
    \ {\n        if (item == n) {\n            if (weight <= capacity) {\n       \
    \         for (int current = weight; current <= capacity; ++current) {\n     \
    \               result[current] = std::max(result[current], value);\n        \
    \        }\n            }\n            return;\n        }\n        for (int take\
    \ = 0; take <= counts[item]; ++take) {\n            self(self, item + 1, weight\
    \ + weights[item] * take, value + values[item] * take);\n        }\n    };\n \
    \   dfs(dfs, 0, 0, 0);\n    return result;\n}\n\nstd::vector<long long> naive_min_weight_for_value(\n\
    \    const std::vector<long long>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit\n) {\n    const long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n    std::vector<long long> result(value_limit + 1, inf);\n\
    \    const int n = int(weights.size());\n    for (int mask = 0; mask < (1 << n);\
    \ ++mask) {\n        long long weight = 0;\n        int value = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) {\n            \
    \    weight += weights[i];\n                value += values[i];\n            }\n\
    \        }\n        if (value <= value_limit) {\n            result[value] = std::min(result[value],\
    \ weight);\n        }\n    }\n    return result;\n}\n\nvoid test_subset_sum()\
    \ {\n    for (int n = 0; n <= 8; ++n) {\n        std::vector<int> weights(n);\n\
    \        for (int seed = 0; seed < 60; ++seed) {\n            for (int i = 0;\
    \ i < n; ++i) {\n                weights[i] = (seed * 13 + i * 7) % 10;\n    \
    \        }\n            assert(m1une::algo::subset_sum_reachable(weights, 30)\
    \ == naive_subset_sum(weights, 30));\n        }\n    }\n}\n\nvoid test_zero_one_knapsack()\
    \ {\n    std::vector<int> weights = {2, 3, 4, 5};\n    std::vector<long long>\
    \ values = {4, 5, 7, 8};\n    assert(\n        m1une::algo::zero_one_knapsack_max_value(weights,\
    \ values, 10)\n        == naive_zero_one_max_value(weights, values, 10)\n    );\n\
    }\n\nvoid test_bounded_knapsack() {\n    std::vector<int> weights = {0, 2, 3};\n\
    \    std::vector<long long> values = {5, 3, 4};\n    std::vector<int> counts =\
    \ {2, 3, 2};\n    assert(\n        m1une::algo::bounded_knapsack_max_value(weights,\
    \ values, counts, 10)\n        == naive_bounded_max_value(weights, values, counts,\
    \ 10)\n    );\n}\n\nvoid test_min_weight_for_value() {\n    std::vector<long long>\
    \ weights = {3, 2, 5, 7};\n    std::vector<int> values = {4, 3, 6, 8};\n    assert(\n\
    \        m1une::algo::zero_one_knapsack_min_weight_for_value(weights, values,\
    \ 20)\n        == naive_min_weight_for_value(weights, values, 20)\n    );\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_subset_sum();\n    test_zero_one_knapsack();\n    test_bounded_knapsack();\n\
    \    test_min_weight_for_value();\n\n    long long a, b;\n    fast_input >> a\
    \ >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\n#include <limits>\n\
    #include <vector>\n\n#include \"../../../algo/dp/knapsack.hpp\"\n\nstd::vector<char>\
    \ naive_subset_sum(const std::vector<int>& weights, int limit) {\n    std::vector<char>\
    \ reachable(limit + 1, 0);\n    reachable[0] = 1;\n    for (int weight : weights)\
    \ {\n        for (int sum = limit; weight <= sum; --sum) {\n            if (reachable[sum\
    \ - weight]) reachable[sum] = 1;\n        }\n    }\n    return reachable;\n}\n\
    \nstd::vector<long long> naive_zero_one_max_value(\n    const std::vector<int>&\
    \ weights,\n    const std::vector<long long>& values,\n    int capacity\n) {\n\
    \    std::vector<long long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n\
    \    for (int mask = 0; mask < (1 << n); ++mask) {\n        int weight = 0;\n\
    \        long long value = 0;\n        for (int i = 0; i < n; ++i) {\n       \
    \     if ((mask >> i) & 1) {\n                weight += weights[i];\n        \
    \        value += values[i];\n            }\n        }\n        if (weight <=\
    \ capacity) {\n            for (int current = weight; current <= capacity; ++current)\
    \ {\n                result[current] = std::max(result[current], value);\n   \
    \         }\n        }\n    }\n    return result;\n}\n\nstd::vector<long long>\
    \ naive_bounded_max_value(\n    const std::vector<int>& weights,\n    const std::vector<long\
    \ long>& values,\n    const std::vector<int>& counts,\n    int capacity\n) {\n\
    \    std::vector<long long> result(capacity + 1, 0);\n    const int n = int(weights.size());\n\
    \n    auto dfs = [&](auto& self, int item, int weight, long long value) -> void\
    \ {\n        if (item == n) {\n            if (weight <= capacity) {\n       \
    \         for (int current = weight; current <= capacity; ++current) {\n     \
    \               result[current] = std::max(result[current], value);\n        \
    \        }\n            }\n            return;\n        }\n        for (int take\
    \ = 0; take <= counts[item]; ++take) {\n            self(self, item + 1, weight\
    \ + weights[item] * take, value + values[item] * take);\n        }\n    };\n \
    \   dfs(dfs, 0, 0, 0);\n    return result;\n}\n\nstd::vector<long long> naive_min_weight_for_value(\n\
    \    const std::vector<long long>& weights,\n    const std::vector<int>& values,\n\
    \    int value_limit\n) {\n    const long long inf = std::numeric_limits<long\
    \ long>::max() / 4;\n    std::vector<long long> result(value_limit + 1, inf);\n\
    \    const int n = int(weights.size());\n    for (int mask = 0; mask < (1 << n);\
    \ ++mask) {\n        long long weight = 0;\n        int value = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) {\n            \
    \    weight += weights[i];\n                value += values[i];\n            }\n\
    \        }\n        if (value <= value_limit) {\n            result[value] = std::min(result[value],\
    \ weight);\n        }\n    }\n    return result;\n}\n\nvoid test_subset_sum()\
    \ {\n    for (int n = 0; n <= 8; ++n) {\n        std::vector<int> weights(n);\n\
    \        for (int seed = 0; seed < 60; ++seed) {\n            for (int i = 0;\
    \ i < n; ++i) {\n                weights[i] = (seed * 13 + i * 7) % 10;\n    \
    \        }\n            assert(m1une::algo::subset_sum_reachable(weights, 30)\
    \ == naive_subset_sum(weights, 30));\n        }\n    }\n}\n\nvoid test_zero_one_knapsack()\
    \ {\n    std::vector<int> weights = {2, 3, 4, 5};\n    std::vector<long long>\
    \ values = {4, 5, 7, 8};\n    assert(\n        m1une::algo::zero_one_knapsack_max_value(weights,\
    \ values, 10)\n        == naive_zero_one_max_value(weights, values, 10)\n    );\n\
    }\n\nvoid test_bounded_knapsack() {\n    std::vector<int> weights = {0, 2, 3};\n\
    \    std::vector<long long> values = {5, 3, 4};\n    std::vector<int> counts =\
    \ {2, 3, 2};\n    assert(\n        m1une::algo::bounded_knapsack_max_value(weights,\
    \ values, counts, 10)\n        == naive_bounded_max_value(weights, values, counts,\
    \ 10)\n    );\n}\n\nvoid test_min_weight_for_value() {\n    std::vector<long long>\
    \ weights = {3, 2, 5, 7};\n    std::vector<int> values = {4, 3, 6, 8};\n    assert(\n\
    \        m1une::algo::zero_one_knapsack_min_weight_for_value(weights, values,\
    \ 20)\n        == naive_min_weight_for_value(weights, values, 20)\n    );\n}\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_subset_sum();\n    test_zero_one_knapsack();\n    test_bounded_knapsack();\n\
    \    test_min_weight_for_value();\n\n    long long a, b;\n    fast_input >> a\
    \ >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - algo/dp/knapsack.hpp
  isVerificationFile: true
  path: verify/algo/dp/knapsack.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/dp/knapsack.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/dp/knapsack.test.cpp
- /verify/verify/algo/dp/knapsack.test.cpp.html
title: verify/algo/dp/knapsack.test.cpp
---
