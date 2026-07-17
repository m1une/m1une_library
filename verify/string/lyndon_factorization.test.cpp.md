---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  - icon: ':heavy_check_mark:'
    path: string/minimum_rotation.hpp
    title: Minimum Rotation
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
    PROBLEM: https://judge.yosupo.jp/problem/lyndon_factorization
    links:
    - https://judge.yosupo.jp/problem/lyndon_factorization
  bundledCode: "#line 1 \"verify/string/lyndon_factorization.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/lyndon_factorization\"\n\n#line 1 \"string/lyndon_factorization.hpp\"\
    \n\n\n\n#include <utility>\n#include <vector>\n\n#line 1 \"string/minimum_rotation.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace string {\n\n// Returns the smallest starting\
    \ index of a lexicographically minimum cyclic shift.\ntemplate <class Sequence>\n\
    int minimum_cyclic_shift(const Sequence& sequence) {\n    const int size = int(sequence.size());\n\
    \    if (size == 0) return 0;\n\n    auto less = [&](int left, int right) {\n\
    \        return sequence[left < size ? left : left - size] <\n               sequence[right\
    \ < size ? right : right - size];\n    };\n\n    int answer = 0;\n    int start\
    \ = 0;\n    while (start < size) {\n        answer = start;\n        int scan\
    \ = start + 1;\n        int matched = start;\n        while (scan < 2 * size &&\
    \ !less(scan, matched)) {\n            if (less(matched, scan)) {\n          \
    \      matched = start;\n            } else {\n                matched++;\n  \
    \          }\n            scan++;\n        }\n\n        const int period = scan\
    \ - matched;\n        while (start <= matched) start += period;\n    }\n    return\
    \ answer;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 8 \"\
    string/lyndon_factorization.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n\
    // Returns boundaries 0 = a[0] < a[1] < ... < a[k] = sequence.size()\n// of the\
    \ Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<int> lyndon_factor_boundaries(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    std::vector<int>\
    \ boundaries;\n    boundaries.push_back(0);\n\n    int i = 0;\n    while (i <\
    \ n) {\n        int j = i + 1;\n        int k = i;\n        while (j < n && !(sequence[j]\
    \ < sequence[k])) {\n            if (sequence[k] < sequence[j]) {\n          \
    \      k = i;\n            } else {\n                k++;\n            }\n   \
    \         j++;\n        }\n\n        int length = j - k;\n        while (i <=\
    \ k) {\n            i += length;\n            boundaries.push_back(i);\n     \
    \   }\n    }\n    return boundaries;\n}\n\n// Returns half-open intervals [left,\
    \ right) of the Lyndon factorization.\ntemplate <class Sequence>\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const Sequence& sequence) {\n    std::vector<int>\
    \ boundaries = lyndon_factor_boundaries(sequence);\n    std::vector<std::pair<int,\
    \ int>> factors;\n    factors.reserve(boundaries.size() - 1);\n    for (int i\
    \ = 0; i + 1 < int(boundaries.size()); i++) {\n        factors.emplace_back(boundaries[i],\
    \ boundaries[i + 1]);\n    }\n    return factors;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/string/lyndon_factorization.test.cpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\
    \n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include\
    \ <type_traits>\n#line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/string/lyndon_factorization.test.cpp\"\
    \n\nnamespace {\n\nbool is_strictly_smaller_rotation(const std::string& word,\
    \ int offset) {\n    int n = int(word.size());\n    for (int i = 0; i < n; i++)\
    \ {\n        char a = word[i];\n        char b = word[(offset + i) % n];\n   \
    \     if (a != b) return a < b;\n    }\n    return false;\n}\n\nbool is_lyndon_word(const\
    \ std::string& word) {\n    if (word.empty()) return false;\n    for (int offset\
    \ = 1; offset < int(word.size()); offset++) {\n        if (!is_strictly_smaller_rotation(word,\
    \ offset)) return false;\n    }\n    return true;\n}\n\nstd::vector<std::vector<int>>\
    \ enumerate_factorizations(int n) {\n    std::vector<std::vector<int>> result;\n\
    \    for (int mask = 0; mask < (1 << (n - 1)); mask++) {\n        std::vector<int>\
    \ boundaries;\n        boundaries.push_back(0);\n        for (int i = 1; i < n;\
    \ i++) {\n            if ((mask >> (i - 1)) & 1) boundaries.push_back(i);\n  \
    \      }\n        boundaries.push_back(n);\n        result.push_back(boundaries);\n\
    \    }\n    return result;\n}\n\nstd::vector<int> naive_lyndon_factor_boundaries(const\
    \ std::string& text) {\n    int n = int(text.size());\n    if (n == 0) return\
    \ std::vector<int>(1, 0);\n\n    std::vector<int> best;\n    for (const std::vector<int>&\
    \ boundaries : enumerate_factorizations(n)) {\n        bool valid = true;\n  \
    \      std::vector<std::string> factors;\n        for (int i = 0; i + 1 < int(boundaries.size());\
    \ i++) {\n            std::string word =\n                text.substr(boundaries[i],\
    \ boundaries[i + 1] - boundaries[i]);\n            if (!is_lyndon_word(word))\
    \ {\n                valid = false;\n                break;\n            }\n \
    \           factors.push_back(word);\n        }\n        for (int i = 0; i + 1\
    \ < int(factors.size()); i++) {\n            if (factors[i] < factors[i + 1])\
    \ {\n                valid = false;\n                break;\n            }\n \
    \       }\n        if (valid) {\n            assert(best.empty());\n         \
    \   best = boundaries;\n        }\n    }\n    assert(!best.empty());\n    return\
    \ best;\n}\n\nstd::string cyclic_shift(const std::string& text, int start) {\n\
    \    return text.substr(start) + text.substr(0, start);\n}\n\nint naive_minimum_cyclic_shift(const\
    \ std::string& text) {\n    int n = int(text.size());\n    if (n == 0) return\
    \ 0;\n\n    int best = 0;\n    for (int start = 1; start < n; start++) {\n   \
    \     if (cyclic_shift(text, start) < cyclic_shift(text, best)) {\n          \
    \  best = start;\n        }\n    }\n    return best;\n}\n\nvoid test_edge_cases()\
    \ {\n    std::string empty;\n    assert(m1une::string::lyndon_factor_boundaries(empty)\
    \ == std::vector<int>(1, 0));\n    assert(m1une::string::lyndon_factorization(empty).empty());\n\
    \    assert(m1une::string::minimum_cyclic_shift(empty) == 0);\n\n    assert(\n\
    \        m1une::string::lyndon_factor_boundaries(std::string(\"aaaa\")) ==\n \
    \       std::vector<int>({0, 1, 2, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    aaaa\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    abab\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    banana\")) == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    baca\")) == 3);\n\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(1, 3);\n    expected.emplace_back(3, 4);\n  \
    \  assert(m1une::string::lyndon_factorization(std::string(\"baca\")) == expected);\n\
    \n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(3);\n    values.push_back(1);\n    assert(\n        m1une::string::lyndon_factor_boundaries(values)\
    \ ==\n        std::vector<int>({0, 1, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1200; trial++) {\n        int n = int(random() % 10);\n        std::string\
    \ text(n, 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n\n        std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \        std::vector<int> expected = naive_lyndon_factor_boundaries(text);\n \
    \       assert(boundaries == expected);\n        assert(\n            m1une::string::minimum_cyclic_shift(text)\
    \ ==\n            naive_minimum_cyclic_shift(text)\n        );\n\n        std::vector<std::pair<int,\
    \ int>> factors = m1une::string::lyndon_factorization(text);\n        assert(int(factors.size())\
    \ + 1 == int(boundaries.size()));\n        for (int i = 0; i < int(factors.size());\
    \ i++) {\n            assert(factors[i].first == boundaries[i]);\n           \
    \ assert(factors[i].second == boundaries[i + 1]);\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \    std::string text;\n    fast_input >> text;\n    std::vector<int> boundaries\
    \ = m1une::string::lyndon_factor_boundaries(text);\n    for (int i = 0; i < int(boundaries.size());\
    \ i++) {\n        if (i > 0) fast_output << ' ';\n        fast_output << boundaries[i];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lyndon_factorization\"\n\
    \n#include \"../../string/lyndon_factorization.hpp\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <string>\n#include\
    \ <utility>\n#include <vector>\n\nnamespace {\n\nbool is_strictly_smaller_rotation(const\
    \ std::string& word, int offset) {\n    int n = int(word.size());\n    for (int\
    \ i = 0; i < n; i++) {\n        char a = word[i];\n        char b = word[(offset\
    \ + i) % n];\n        if (a != b) return a < b;\n    }\n    return false;\n}\n\
    \nbool is_lyndon_word(const std::string& word) {\n    if (word.empty()) return\
    \ false;\n    for (int offset = 1; offset < int(word.size()); offset++) {\n  \
    \      if (!is_strictly_smaller_rotation(word, offset)) return false;\n    }\n\
    \    return true;\n}\n\nstd::vector<std::vector<int>> enumerate_factorizations(int\
    \ n) {\n    std::vector<std::vector<int>> result;\n    for (int mask = 0; mask\
    \ < (1 << (n - 1)); mask++) {\n        std::vector<int> boundaries;\n        boundaries.push_back(0);\n\
    \        for (int i = 1; i < n; i++) {\n            if ((mask >> (i - 1)) & 1)\
    \ boundaries.push_back(i);\n        }\n        boundaries.push_back(n);\n    \
    \    result.push_back(boundaries);\n    }\n    return result;\n}\n\nstd::vector<int>\
    \ naive_lyndon_factor_boundaries(const std::string& text) {\n    int n = int(text.size());\n\
    \    if (n == 0) return std::vector<int>(1, 0);\n\n    std::vector<int> best;\n\
    \    for (const std::vector<int>& boundaries : enumerate_factorizations(n)) {\n\
    \        bool valid = true;\n        std::vector<std::string> factors;\n     \
    \   for (int i = 0; i + 1 < int(boundaries.size()); i++) {\n            std::string\
    \ word =\n                text.substr(boundaries[i], boundaries[i + 1] - boundaries[i]);\n\
    \            if (!is_lyndon_word(word)) {\n                valid = false;\n  \
    \              break;\n            }\n            factors.push_back(word);\n \
    \       }\n        for (int i = 0; i + 1 < int(factors.size()); i++) {\n     \
    \       if (factors[i] < factors[i + 1]) {\n                valid = false;\n \
    \               break;\n            }\n        }\n        if (valid) {\n     \
    \       assert(best.empty());\n            best = boundaries;\n        }\n   \
    \ }\n    assert(!best.empty());\n    return best;\n}\n\nstd::string cyclic_shift(const\
    \ std::string& text, int start) {\n    return text.substr(start) + text.substr(0,\
    \ start);\n}\n\nint naive_minimum_cyclic_shift(const std::string& text) {\n  \
    \  int n = int(text.size());\n    if (n == 0) return 0;\n\n    int best = 0;\n\
    \    for (int start = 1; start < n; start++) {\n        if (cyclic_shift(text,\
    \ start) < cyclic_shift(text, best)) {\n            best = start;\n        }\n\
    \    }\n    return best;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::lyndon_factor_boundaries(empty) == std::vector<int>(1,\
    \ 0));\n    assert(m1une::string::lyndon_factorization(empty).empty());\n    assert(m1une::string::minimum_cyclic_shift(empty)\
    \ == 0);\n\n    assert(\n        m1une::string::lyndon_factor_boundaries(std::string(\"\
    aaaa\")) ==\n        std::vector<int>({0, 1, 2, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    aaaa\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    abab\")) == 0);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    banana\")) == 5);\n    assert(m1une::string::minimum_cyclic_shift(std::string(\"\
    baca\")) == 3);\n\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(1, 3);\n    expected.emplace_back(3, 4);\n  \
    \  assert(m1une::string::lyndon_factorization(std::string(\"baca\")) == expected);\n\
    \n    std::vector<int> values;\n    values.push_back(2);\n    values.push_back(1);\n\
    \    values.push_back(3);\n    values.push_back(1);\n    assert(\n        m1une::string::lyndon_factor_boundaries(values)\
    \ ==\n        std::vector<int>({0, 1, 3, 4})\n    );\n    assert(m1une::string::minimum_cyclic_shift(values)\
    \ == 3);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 20260709;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1200; trial++) {\n        int n = int(random() % 10);\n        std::string\
    \ text(n, 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n\n        std::vector<int> boundaries = m1une::string::lyndon_factor_boundaries(text);\n\
    \        std::vector<int> expected = naive_lyndon_factor_boundaries(text);\n \
    \       assert(boundaries == expected);\n        assert(\n            m1une::string::minimum_cyclic_shift(text)\
    \ ==\n            naive_minimum_cyclic_shift(text)\n        );\n\n        std::vector<std::pair<int,\
    \ int>> factors = m1une::string::lyndon_factorization(text);\n        assert(int(factors.size())\
    \ + 1 == int(boundaries.size()));\n        for (int i = 0; i < int(factors.size());\
    \ i++) {\n            assert(factors[i].first == boundaries[i]);\n           \
    \ assert(factors[i].second == boundaries[i + 1]);\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \    std::string text;\n    fast_input >> text;\n    std::vector<int> boundaries\
    \ = m1une::string::lyndon_factor_boundaries(text);\n    for (int i = 0; i < int(boundaries.size());\
    \ i++) {\n        if (i > 0) fast_output << ' ';\n        fast_output << boundaries[i];\n\
    \    }\n    fast_output << '\\n';\n}\n"
  dependsOn:
  - string/lyndon_factorization.hpp
  - string/minimum_rotation.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/lyndon_factorization.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/lyndon_factorization.test.cpp
layout: document
redirect_from:
- /verify/verify/string/lyndon_factorization.test.cpp
- /verify/verify/string/lyndon_factorization.test.cpp.html
title: verify/string/lyndon_factorization.test.cpp
---
