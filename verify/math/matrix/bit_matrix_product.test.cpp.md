---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/bit_matrix.hpp
    title: Bit Matrix
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
    PROBLEM: https://judge.yosupo.jp/problem/matrix_product_mod_2
    links:
    - https://judge.yosupo.jp/problem/matrix_product_mod_2
  bundledCode: "#line 1 \"verify/math/matrix/bit_matrix_product.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include\
    \ <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/math/matrix/bit_matrix_product.test.cpp\"\
    \n#include <optional>\n#line 8 \"verify/math/matrix/bit_matrix_product.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"math/matrix/bit_matrix.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <bit>\n#line 11 \"math/matrix/bit_matrix.hpp\"\n#include\
    \ <string_view>\n#line 14 \"math/matrix/bit_matrix.hpp\"\n\nnamespace m1une {\n\
    namespace matrix {\n\nclass BitMatrix {\n   private:\n    int _rows;\n    int\
    \ _cols;\n    int _blocks;\n    std::vector<std::uint64_t> _data;\n\n    static\
    \ int block_count(int cols) {\n        assert(cols >= 0);\n        return (cols\
    \ + 63) / 64;\n    }\n\n    static std::size_t storage_size(int rows, int blocks)\
    \ {\n        assert(rows >= 0);\n        return std::size_t(rows) * std::size_t(blocks);\n\
    \    }\n\n    std::size_t word_index(int row, int col) const {\n        assert(0\
    \ <= row && row < _rows);\n        assert(0 <= col && col < _cols);\n        return\
    \ std::size_t(row) * std::size_t(_blocks) +\n               std::size_t(col /\
    \ 64);\n    }\n\n    std::uint64_t trailing_mask() const {\n        if ((_cols\
    \ & 63) == 0) return ~std::uint64_t(0);\n        return (std::uint64_t(1) << (_cols\
    \ & 63)) - 1;\n    }\n\n   public:\n    class BitReference {\n       private:\n\
    \        std::uint64_t* word;\n        std::uint64_t mask;\n\n       public:\n\
    \        BitReference(std::uint64_t& word_value, std::uint64_t mask_value)\n \
    \           : word(&word_value), mask(mask_value) {}\n\n        operator bool()\
    \ const {\n            return (*word & mask) != 0;\n        }\n\n        BitReference&\
    \ operator=(bool value) {\n            if (value) {\n                *word |=\
    \ mask;\n            } else {\n                *word &= ~mask;\n            }\n\
    \            return *this;\n        }\n\n        BitReference& operator=(const\
    \ BitReference& other) {\n            return *this = bool(other);\n        }\n\
    \n        void flip() {\n            *word ^= mask;\n        }\n    };\n\n   \
    \ class RowReference {\n       private:\n        BitMatrix* matrix;\n        int\
    \ row;\n\n       public:\n        RowReference(BitMatrix& matrix_value, int row_value)\n\
    \            : matrix(&matrix_value), row(row_value) {}\n\n        BitReference\
    \ operator[](int col) const {\n            return (*matrix)(row, col);\n     \
    \   }\n    };\n\n    class ConstRowReference {\n       private:\n        const\
    \ BitMatrix* matrix;\n        int row;\n\n       public:\n        ConstRowReference(const\
    \ BitMatrix& matrix_value, int row_value)\n            : matrix(&matrix_value),\
    \ row(row_value) {}\n\n        bool operator[](int col) const {\n            return\
    \ (*matrix)(row, col);\n        }\n    };\n\n    BitMatrix() : _rows(0), _cols(0),\
    \ _blocks(0) {}\n\n    BitMatrix(int rows, int cols, bool value = false)\n   \
    \     : _rows(rows),\n          _cols(cols),\n          _blocks(block_count(cols)),\n\
    \          _data(\n              storage_size(rows, _blocks),\n              value\
    \ ? ~std::uint64_t(0) : std::uint64_t(0)\n          ) {\n        assert(rows >=\
    \ 0);\n        if (value && _blocks > 0) {\n            const std::uint64_t mask\
    \ = trailing_mask();\n            for (int row = 0; row < _rows; row++) {\n  \
    \              _data[\n                    std::size_t(row + 1) * std::size_t(_blocks)\
    \ - 1\n                ] &= mask;\n            }\n        }\n    }\n\n    int\
    \ rows() const {\n        return _rows;\n    }\n\n    int cols() const {\n   \
    \     return _cols;\n    }\n\n    int blocks_per_row() const {\n        return\
    \ _blocks;\n    }\n\n    bool empty() const {\n        return _rows == 0 || _cols\
    \ == 0;\n    }\n\n    RowReference operator[](int row) {\n        assert(0 <=\
    \ row && row < _rows);\n        return RowReference(*this, row);\n    }\n\n  \
    \  ConstRowReference operator[](int row) const {\n        assert(0 <= row && row\
    \ < _rows);\n        return ConstRowReference(*this, row);\n    }\n\n    BitReference\
    \ operator()(int row, int col) {\n        const std::size_t index = word_index(row,\
    \ col);\n        return BitReference(_data[index], std::uint64_t(1) << (col &\
    \ 63));\n    }\n\n    bool operator()(int row, int col) const {\n        const\
    \ std::size_t index = word_index(row, col);\n        return (_data[index] >> (col\
    \ & 63)) & 1;\n    }\n\n    bool get(int row, int col) const {\n        return\
    \ (*this)(row, col);\n    }\n\n    void set(int row, int col, bool value = true)\
    \ {\n        (*this)(row, col) = value;\n    }\n\n    void reset(int row, int\
    \ col) {\n        set(row, col, false);\n    }\n\n    void flip(int row, int col)\
    \ {\n        (*this)(row, col).flip();\n    }\n\n    void clear() {\n        std::fill(_data.begin(),\
    \ _data.end(), std::uint64_t(0));\n    }\n\n    void set_row(int row, std::string_view\
    \ bits) {\n        assert(0 <= row && row < _rows);\n        assert(int(bits.size())\
    \ == _cols);\n        const std::size_t offset =\n            std::size_t(row)\
    \ * std::size_t(_blocks);\n        std::fill(\n            _data.begin() + std::ptrdiff_t(offset),\n\
    \            _data.begin() + std::ptrdiff_t(offset + std::size_t(_blocks)),\n\
    \            std::uint64_t(0)\n        );\n        for (int col = 0; col < _cols;\
    \ col++) {\n            assert(bits[std::size_t(col)] == '0' || bits[std::size_t(col)]\
    \ == '1');\n            if (bits[std::size_t(col)] == '1') set(row, col);\n  \
    \      }\n    }\n\n    std::string row_string(int row) const {\n        assert(0\
    \ <= row && row < _rows);\n        std::string result(std::size_t(_cols), '0');\n\
    \        for (int col = 0; col < _cols; col++) {\n            if (get(row, col))\
    \ result[std::size_t(col)] = '1';\n        }\n        return result;\n    }\n\n\
    \    static BitMatrix identity(int size) {\n        assert(size >= 0);\n     \
    \   BitMatrix result(size, size);\n        for (int index = 0; index < size; index++)\
    \ result.set(index, index);\n        return result;\n    }\n\n    BitMatrix transposed()\
    \ const {\n        BitMatrix result(_cols, _rows);\n        for (int row = 0;\
    \ row < _rows; row++) {\n            for (int col = 0; col < _cols; col++) {\n\
    \                if (get(row, col)) result.set(col, row);\n            }\n   \
    \     }\n        return result;\n    }\n\n    void swap_rows(int first, int second)\
    \ {\n        assert(0 <= first && first < _rows);\n        assert(0 <= second\
    \ && second < _rows);\n        if (first == second) return;\n        const std::size_t\
    \ first_offset =\n            std::size_t(first) * std::size_t(_blocks);\n   \
    \     const std::size_t second_offset =\n            std::size_t(second) * std::size_t(_blocks);\n\
    \        for (int block = 0; block < _blocks; block++) {\n            std::swap(\n\
    \                _data[first_offset + std::size_t(block)],\n                _data[second_offset\
    \ + std::size_t(block)]\n            );\n        }\n    }\n\n    void xor_rows(int\
    \ target, int source, int first_col = 0) {\n        assert(0 <= target && target\
    \ < _rows);\n        assert(0 <= source && source < _rows);\n        assert(0\
    \ <= first_col && first_col <= _cols);\n        if (first_col == _cols) return;\n\
    \        const std::size_t target_offset =\n            std::size_t(target) *\
    \ std::size_t(_blocks);\n        const std::size_t source_offset =\n         \
    \   std::size_t(source) * std::size_t(_blocks);\n        const int first_block\
    \ = first_col / 64;\n        const int first_bit = first_col & 63;\n        if\
    \ (first_bit != 0) {\n            const std::uint64_t mask = ~std::uint64_t(0)\
    \ << first_bit;\n            _data[target_offset + std::size_t(first_block)] ^=\n\
    \                _data[source_offset + std::size_t(first_block)] & mask;\n   \
    \     } else {\n            _data[target_offset + std::size_t(first_block)] ^=\n\
    \                _data[source_offset + std::size_t(first_block)];\n        }\n\
    \        for (int block = first_block + 1; block < _blocks; block++) {\n     \
    \       _data[target_offset + std::size_t(block)] ^=\n                _data[source_offset\
    \ + std::size_t(block)];\n        }\n    }\n\n    BitMatrix& operator^=(const\
    \ BitMatrix& rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n\
    \        for (std::size_t index = 0; index < _data.size(); index++) {\n      \
    \      _data[index] ^= rhs._data[index];\n        }\n        return *this;\n \
    \   }\n\n    BitMatrix& operator+=(const BitMatrix& rhs) {\n        return *this\
    \ ^= rhs;\n    }\n\n    BitMatrix& operator-=(const BitMatrix& rhs) {\n      \
    \  return *this ^= rhs;\n    }\n\n    BitMatrix& operator*=(const BitMatrix& rhs)\
    \ {\n        return *this = *this * rhs;\n    }\n\n    friend BitMatrix operator^(BitMatrix\
    \ lhs, const BitMatrix& rhs) {\n        return lhs ^= rhs;\n    }\n\n    friend\
    \ BitMatrix operator+(BitMatrix lhs, const BitMatrix& rhs) {\n        return lhs\
    \ += rhs;\n    }\n\n    friend BitMatrix operator-(BitMatrix lhs, const BitMatrix&\
    \ rhs) {\n        return lhs -= rhs;\n    }\n\n    friend BitMatrix operator*(const\
    \ BitMatrix& lhs, const BitMatrix& rhs) {\n        assert(lhs._cols == rhs._rows);\n\
    \        BitMatrix result(lhs._rows, rhs._cols);\n        for (int row = 0; row\
    \ < lhs._rows; row++) {\n            const std::size_t lhs_offset =\n        \
    \        std::size_t(row) * std::size_t(lhs._blocks);\n            const std::size_t\
    \ result_offset =\n                std::size_t(row) * std::size_t(result._blocks);\n\
    \            for (int lhs_block = 0; lhs_block < lhs._blocks; lhs_block++) {\n\
    \                std::uint64_t word =\n                    lhs._data[lhs_offset\
    \ + std::size_t(lhs_block)];\n                while (word != 0) {\n          \
    \          const int bit = std::countr_zero(word);\n                    const\
    \ int middle = lhs_block * 64 + bit;\n                    const std::size_t rhs_offset\
    \ =\n                        std::size_t(middle) * std::size_t(rhs._blocks);\n\
    \                    for (int block = 0; block < rhs._blocks; block++) {\n   \
    \                     result._data[result_offset + std::size_t(block)] ^=\n  \
    \                          rhs._data[rhs_offset + std::size_t(block)];\n     \
    \               }\n                    word &= word - 1;\n                }\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ BitMatrix& rhs) const {\n        return\n            _rows == rhs._rows && _cols\
    \ == rhs._cols && _data == rhs._data;\n    }\n\n    bool operator!=(const BitMatrix&\
    \ rhs) const {\n        return !(*this == rhs);\n    }\n\n    BitMatrix pow(std::uint64_t\
    \ exponent) const {\n        assert(_rows == _cols);\n        BitMatrix result\
    \ = identity(_rows);\n        BitMatrix base = *this;\n        while (exponent\
    \ > 0) {\n            if (exponent & 1) result *= base;\n            exponent\
    \ >>= 1;\n            if (exponent > 0) base *= base;\n        }\n        return\
    \ result;\n    }\n};\n\nnamespace bit_matrix_detail {\n\ninline std::vector<int>\
    \ row_reduce(\n    BitMatrix& matrix,\n    int pivot_col_limit,\n    bool reduced\n\
    ) {\n    assert(0 <= pivot_col_limit && pivot_col_limit <= matrix.cols());\n \
    \   std::vector<int> pivot_columns;\n    int pivot_row = 0;\n    for (\n     \
    \   int col = 0;\n        col < pivot_col_limit && pivot_row < matrix.rows();\n\
    \        col++\n    ) {\n        int pivot = -1;\n        for (int row = pivot_row;\
    \ row < matrix.rows(); row++) {\n            if (matrix.get(row, col)) {\n   \
    \             pivot = row;\n                break;\n            }\n        }\n\
    \        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row, pivot);\n\
    \n        const int first_row = reduced ? 0 : pivot_row + 1;\n        for (int\
    \ row = first_row; row < matrix.rows(); row++) {\n            if (row != pivot_row\
    \ && matrix.get(row, col)) {\n                matrix.xor_rows(row, pivot_row,\
    \ col);\n            }\n        }\n        pivot_columns.push_back(col);\n   \
    \     pivot_row++;\n    }\n    return pivot_columns;\n}\n\n}  // namespace bit_matrix_detail\n\
    \nstruct BitRowReduction {\n    BitMatrix matrix;\n    std::vector<int> pivot_columns;\n\
    \n    int rank() const {\n        return int(pivot_columns.size());\n    }\n};\n\
    \ninline BitRowReduction reduced_row_echelon_form(BitMatrix matrix) {\n    BitRowReduction\
    \ result;\n    result.pivot_columns = bit_matrix_detail::row_reduce(\n       \
    \ matrix,\n        matrix.cols(),\n        true\n    );\n    result.matrix = std::move(matrix);\n\
    \    return result;\n}\n\ninline int matrix_rank(BitMatrix matrix) {\n    if (matrix.rows()\
    \ > matrix.cols()) matrix = matrix.transposed();\n    return int(bit_matrix_detail::row_reduce(\n\
    \        matrix,\n        matrix.cols(),\n        false\n    ).size());\n}\n\n\
    inline bool determinant(const BitMatrix& matrix) {\n    assert(matrix.rows() ==\
    \ matrix.cols());\n    return matrix_rank(matrix) == matrix.rows();\n}\n\ninline\
    \ std::optional<BitMatrix> inverse(const BitMatrix& matrix) {\n    assert(matrix.rows()\
    \ == matrix.cols());\n    const int size = matrix.rows();\n    BitMatrix augmented(size,\
    \ 2 * size);\n    for (int row = 0; row < size; row++) {\n        for (int col\
    \ = 0; col < size; col++) {\n            if (matrix.get(row, col)) augmented.set(row,\
    \ col);\n        }\n        augmented.set(row, size + row);\n    }\n\n    const\
    \ std::vector<int> pivots = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        size,\n        true\n    );\n    if (int(pivots.size()) != size) return\
    \ std::nullopt;\n\n    BitMatrix result(size, size);\n    for (int row = 0; row\
    \ < size; row++) {\n        for (int col = 0; col < size; col++) {\n         \
    \   if (augmented.get(row, size + col)) result.set(row, col);\n        }\n   \
    \ }\n    return result;\n}\n\nstruct BitLinearSystemResult {\n    bool consistent\
    \ = false;\n    std::vector<bool> particular_solution;\n    std::vector<std::vector<bool>>\
    \ nullspace_basis;\n    std::vector<int> pivot_columns;\n\n    int rank() const\
    \ {\n        return int(pivot_columns.size());\n    }\n\n    int nullity() const\
    \ {\n        return consistent ? int(nullspace_basis.size()) : 0;\n    }\n\n \
    \   bool has_unique_solution() const {\n        return consistent && nullspace_basis.empty();\n\
    \    }\n};\n\ninline BitLinearSystemResult solve_linear_system(\n    const BitMatrix&\
    \ coefficients,\n    const std::vector<bool>& constants\n) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    BitMatrix augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            if (coefficients.get(row,\
    \ col)) augmented.set(row, col);\n        }\n        if (constants[std::size_t(row)])\
    \ augmented.set(row, variable_count);\n    }\n\n    BitLinearSystemResult result;\n\
    \    result.pivot_columns = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        variable_count,\n        true\n    );\n    for (int row = result.rank();\
    \ row < equation_count; row++) {\n        if (augmented.get(row, variable_count))\
    \ return result;\n    }\n\n    result.consistent = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ false);\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] =\n          \
    \  augmented.get(row, variable_count);\n    }\n\n    for (int free_col = 0; free_col\
    \ < variable_count; free_col++) {\n        if (is_pivot[std::size_t(free_col)])\
    \ continue;\n        std::vector<bool> direction(std::size_t(variable_count),\
    \ false);\n        direction[std::size_t(free_col)] = true;\n        for (int\
    \ row = 0; row < result.rank(); row++) {\n            const int pivot_col = result.pivot_columns[std::size_t(row)];\n\
    \            direction[std::size_t(pivot_col)] = augmented.get(row, free_col);\n\
    \        }\n        result.nullspace_basis.push_back(std::move(direction));\n\
    \    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\
    \n\n#line 11 \"verify/math/matrix/bit_matrix_product.test.cpp\"\n\nnamespace {\n\
    \nusing m1une::matrix::BitMatrix;\n\nBitMatrix naive_product(const BitMatrix&\
    \ first, const BitMatrix& second) {\n    assert(first.cols() == second.rows());\n\
    \    BitMatrix result(first.rows(), second.cols());\n    for (int row = 0; row\
    \ < first.rows(); row++) {\n        for (int col = 0; col < second.cols(); col++)\
    \ {\n            bool value = false;\n            for (int middle = 0; middle\
    \ < first.cols(); middle++) {\n                value ^= first.get(row, middle)\
    \ && second.get(middle, col);\n            }\n            result.set(row, col,\
    \ value);\n        }\n    }\n    return result;\n}\n\nbool satisfies(\n    const\
    \ BitMatrix& matrix,\n    const std::vector<bool>& solution,\n    const std::vector<bool>&\
    \ constants\n) {\n    for (int row = 0; row < matrix.rows(); row++) {\n      \
    \  bool value = false;\n        for (int col = 0; col < matrix.cols(); col++)\
    \ {\n            value ^= matrix.get(row, col) && solution[std::size_t(col)];\n\
    \        }\n        if (value != constants[std::size_t(row)]) return false;\n\
    \    }\n    return true;\n}\n\nvoid test_basic() {\n    BitMatrix filled(2, 70,\
    \ true);\n    assert(filled.row_string(0) == std::string(70, '1'));\n    filled[0][0]\
    \ = false;\n    filled[0][1] = filled[0][0];\n    filled.flip(0, 0);\n    filled.reset(0,\
    \ 2);\n    assert(filled.get(0, 0));\n    assert(!filled.get(0, 1));\n    assert(!filled.get(0,\
    \ 2));\n\n    BitMatrix partial(2, 70);\n    partial.set_row(1, std::string(70,\
    \ '1'));\n    partial.xor_rows(0, 1, 65);\n    for (int col = 0; col < 70; col++)\
    \ {\n        assert(partial.get(0, col) == (65 <= col));\n    }\n    partial.clear();\n\
    \    assert(partial == BitMatrix(2, 70));\n\n    BitMatrix transition(2, 2);\n\
    \    transition.set_row(0, \"11\");\n    transition.set_row(1, \"10\");\n    BitMatrix\
    \ repeated = BitMatrix::identity(2);\n    for (int i = 0; i < 13; i++) repeated\
    \ *= transition;\n    assert(transition.pow(13) == repeated);\n    assert(transition\
    \ + transition == BitMatrix(2, 2));\n    assert(transition - transition == BitMatrix(2,\
    \ 2));\n    assert((transition ^ transition) == BitMatrix(2, 2));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x9e3779b97f4a7c15ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int test = 0; test < 300; test++) {\n        const\
    \ int rows = int(random() % 10);\n        const int middle = int(random() % 10);\n\
    \        const int cols = int(random() % 10);\n        BitMatrix first(rows, middle);\n\
    \        BitMatrix second(middle, cols);\n        for (int row = 0; row < rows;\
    \ row++) {\n            for (int col = 0; col < middle; col++) {\n           \
    \     first[row][col] = (random() & 1) != 0;\n            }\n        }\n     \
    \   for (int row = 0; row < middle; row++) {\n            for (int col = 0; col\
    \ < cols; col++) {\n                second[row][col] = (random() & 1) != 0;\n\
    \            }\n        }\n        assert(first * second == naive_product(first,\
    \ second));\n        assert(first.transposed().transposed() == first);\n\n   \
    \     if (rows == middle) {\n            std::optional<BitMatrix> inverse = m1une::matrix::inverse(first);\n\
    \            assert(inverse.has_value() == m1une::matrix::determinant(first));\n\
    \            if (inverse) {\n                assert(first * *inverse == BitMatrix::identity(rows));\n\
    \                assert(*inverse * first == BitMatrix::identity(rows));\n    \
    \        }\n        }\n\n        std::vector<bool> constants(std::size_t(rows),\
    \ false);\n        for (int row = 0; row < rows; row++) {\n            constants[std::size_t(row)]\
    \ = (random() & 1) != 0;\n        }\n        m1une::matrix::BitLinearSystemResult\
    \ solved =\n            m1une::matrix::solve_linear_system(first, constants);\n\
    \        bool brute_consistent = false;\n        if (middle <= 9) {\n        \
    \    for (int mask = 0; mask < (1 << middle); mask++) {\n                std::vector<bool>\
    \ candidate(std::size_t(middle), false);\n                for (int col = 0; col\
    \ < middle; col++) {\n                    candidate[std::size_t(col)] = (mask\
    \ >> col) & 1;\n                }\n                brute_consistent |= satisfies(first,\
    \ candidate, constants);\n            }\n        }\n        assert(solved.consistent\
    \ == brute_consistent);\n        if (solved.consistent) {\n            assert(satisfies(first,\
    \ solved.particular_solution, constants));\n            std::vector<bool> zero(std::size_t(rows),\
    \ false);\n            for (const std::vector<bool>& direction : solved.nullspace_basis)\
    \ {\n                assert(satisfies(first, direction, zero));\n            }\n\
    \            assert(solved.nullity() == middle - solved.rank());\n        }\n\
    \    }\n}\n\nBitMatrix read_matrix(\n    int rows,\n    int cols,\n    m1une::utilities::FastInput&\
    \ fast_input\n) {\n    BitMatrix matrix(rows, cols);\n    std::string bits;\n\
    \    for (int row = 0; row < rows; row++) {\n        fast_input >> bits;\n   \
    \     matrix.set_row(row, bits);\n    }\n    return matrix;\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_randomized();\n    int rows, middle,\
    \ cols;\n    fast_input >> rows >> middle >> cols;\n    BitMatrix first = read_matrix(rows,\
    \ middle, fast_input);\n    BitMatrix second = read_matrix(middle, cols, fast_input);\n\
    \    BitMatrix result = first * second;\n    for (int row = 0; row < rows; row++)\
    \ {\n        fast_output << result.row_string(row) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/matrix_product_mod_2\"\n\
    \n#include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <optional>\n#include <string>\n#include <vector>\n\n#include \"../../../math/matrix/bit_matrix.hpp\"\
    \n\nnamespace {\n\nusing m1une::matrix::BitMatrix;\n\nBitMatrix naive_product(const\
    \ BitMatrix& first, const BitMatrix& second) {\n    assert(first.cols() == second.rows());\n\
    \    BitMatrix result(first.rows(), second.cols());\n    for (int row = 0; row\
    \ < first.rows(); row++) {\n        for (int col = 0; col < second.cols(); col++)\
    \ {\n            bool value = false;\n            for (int middle = 0; middle\
    \ < first.cols(); middle++) {\n                value ^= first.get(row, middle)\
    \ && second.get(middle, col);\n            }\n            result.set(row, col,\
    \ value);\n        }\n    }\n    return result;\n}\n\nbool satisfies(\n    const\
    \ BitMatrix& matrix,\n    const std::vector<bool>& solution,\n    const std::vector<bool>&\
    \ constants\n) {\n    for (int row = 0; row < matrix.rows(); row++) {\n      \
    \  bool value = false;\n        for (int col = 0; col < matrix.cols(); col++)\
    \ {\n            value ^= matrix.get(row, col) && solution[std::size_t(col)];\n\
    \        }\n        if (value != constants[std::size_t(row)]) return false;\n\
    \    }\n    return true;\n}\n\nvoid test_basic() {\n    BitMatrix filled(2, 70,\
    \ true);\n    assert(filled.row_string(0) == std::string(70, '1'));\n    filled[0][0]\
    \ = false;\n    filled[0][1] = filled[0][0];\n    filled.flip(0, 0);\n    filled.reset(0,\
    \ 2);\n    assert(filled.get(0, 0));\n    assert(!filled.get(0, 1));\n    assert(!filled.get(0,\
    \ 2));\n\n    BitMatrix partial(2, 70);\n    partial.set_row(1, std::string(70,\
    \ '1'));\n    partial.xor_rows(0, 1, 65);\n    for (int col = 0; col < 70; col++)\
    \ {\n        assert(partial.get(0, col) == (65 <= col));\n    }\n    partial.clear();\n\
    \    assert(partial == BitMatrix(2, 70));\n\n    BitMatrix transition(2, 2);\n\
    \    transition.set_row(0, \"11\");\n    transition.set_row(1, \"10\");\n    BitMatrix\
    \ repeated = BitMatrix::identity(2);\n    for (int i = 0; i < 13; i++) repeated\
    \ *= transition;\n    assert(transition.pow(13) == repeated);\n    assert(transition\
    \ + transition == BitMatrix(2, 2));\n    assert(transition - transition == BitMatrix(2,\
    \ 2));\n    assert((transition ^ transition) == BitMatrix(2, 2));\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x9e3779b97f4a7c15ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int test = 0; test < 300; test++) {\n        const\
    \ int rows = int(random() % 10);\n        const int middle = int(random() % 10);\n\
    \        const int cols = int(random() % 10);\n        BitMatrix first(rows, middle);\n\
    \        BitMatrix second(middle, cols);\n        for (int row = 0; row < rows;\
    \ row++) {\n            for (int col = 0; col < middle; col++) {\n           \
    \     first[row][col] = (random() & 1) != 0;\n            }\n        }\n     \
    \   for (int row = 0; row < middle; row++) {\n            for (int col = 0; col\
    \ < cols; col++) {\n                second[row][col] = (random() & 1) != 0;\n\
    \            }\n        }\n        assert(first * second == naive_product(first,\
    \ second));\n        assert(first.transposed().transposed() == first);\n\n   \
    \     if (rows == middle) {\n            std::optional<BitMatrix> inverse = m1une::matrix::inverse(first);\n\
    \            assert(inverse.has_value() == m1une::matrix::determinant(first));\n\
    \            if (inverse) {\n                assert(first * *inverse == BitMatrix::identity(rows));\n\
    \                assert(*inverse * first == BitMatrix::identity(rows));\n    \
    \        }\n        }\n\n        std::vector<bool> constants(std::size_t(rows),\
    \ false);\n        for (int row = 0; row < rows; row++) {\n            constants[std::size_t(row)]\
    \ = (random() & 1) != 0;\n        }\n        m1une::matrix::BitLinearSystemResult\
    \ solved =\n            m1une::matrix::solve_linear_system(first, constants);\n\
    \        bool brute_consistent = false;\n        if (middle <= 9) {\n        \
    \    for (int mask = 0; mask < (1 << middle); mask++) {\n                std::vector<bool>\
    \ candidate(std::size_t(middle), false);\n                for (int col = 0; col\
    \ < middle; col++) {\n                    candidate[std::size_t(col)] = (mask\
    \ >> col) & 1;\n                }\n                brute_consistent |= satisfies(first,\
    \ candidate, constants);\n            }\n        }\n        assert(solved.consistent\
    \ == brute_consistent);\n        if (solved.consistent) {\n            assert(satisfies(first,\
    \ solved.particular_solution, constants));\n            std::vector<bool> zero(std::size_t(rows),\
    \ false);\n            for (const std::vector<bool>& direction : solved.nullspace_basis)\
    \ {\n                assert(satisfies(first, direction, zero));\n            }\n\
    \            assert(solved.nullity() == middle - solved.rank());\n        }\n\
    \    }\n}\n\nBitMatrix read_matrix(\n    int rows,\n    int cols,\n    m1une::utilities::FastInput&\
    \ fast_input\n) {\n    BitMatrix matrix(rows, cols);\n    std::string bits;\n\
    \    for (int row = 0; row < rows; row++) {\n        fast_input >> bits;\n   \
    \     matrix.set_row(row, bits);\n    }\n    return matrix;\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_basic();\n    test_randomized();\n    int rows, middle,\
    \ cols;\n    fast_input >> rows >> middle >> cols;\n    BitMatrix first = read_matrix(rows,\
    \ middle, fast_input);\n    BitMatrix second = read_matrix(middle, cols, fast_input);\n\
    \    BitMatrix result = first * second;\n    for (int row = 0; row < rows; row++)\
    \ {\n        fast_output << result.row_string(row) << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - math/matrix/bit_matrix.hpp
  isVerificationFile: true
  path: verify/math/matrix/bit_matrix_product.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/bit_matrix_product.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/bit_matrix_product.test.cpp
- /verify/verify/math/matrix/bit_matrix_product.test.cpp.html
title: verify/math/matrix/bit_matrix_product.test.cpp
---
