---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
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
  bundledCode: "#line 1 \"verify/string/string_hash.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"string/string_hash.hpp\"\
    \n\n\n\n#include <cstddef>\n#include <cstdint>\n#include <string>\n#include <string_view>\n\
    \nnamespace m1une {\nnamespace string {\n\nstruct StringHash {\n    std::uint32_t\
    \ first;\n    std::uint32_t second;\n    std::uint32_t first_power;\n    std::uint32_t\
    \ second_power;\n    std::size_t length;\n\n    friend constexpr bool operator==(const\
    \ StringHash& left, const StringHash& right) {\n        return left.length ==\
    \ right.length && left.first == right.first && left.second == right.second;\n\
    \    }\n};\n\nnamespace string_hash_detail {\n\ninline constexpr std::uint64_t\
    \ first_mod = 1'000'000'007;\ninline constexpr std::uint64_t second_mod = 1'000'000'009;\n\
    inline constexpr std::uint64_t base = 911'382'323;\n\n}  // namespace string_hash_detail\n\
    \n// Computes a double polynomial hash. Bytes are interpreted as unsigned.\nconstexpr\
    \ StringHash hash_string(std::string_view value) {\n    using namespace string_hash_detail;\n\
    \    std::uint64_t first = 0;\n    std::uint64_t second = 0;\n    std::uint64_t\
    \ first_power = 1;\n    std::uint64_t second_power = 1;\n    for (char character\
    \ : value) {\n        std::uint64_t symbol = static_cast<unsigned char>(character)\
    \ + std::uint64_t(1);\n        first = (first * base + symbol) % first_mod;\n\
    \        second = (second * base + symbol) % second_mod;\n        first_power\
    \ = first_power * base % first_mod;\n        second_power = second_power * base\
    \ % second_mod;\n    }\n    return StringHash{\n        static_cast<std::uint32_t>(first),\n\
    \        static_cast<std::uint32_t>(second),\n        static_cast<std::uint32_t>(first_power),\n\
    \        static_cast<std::uint32_t>(second_power),\n        value.size(),\n  \
    \  };\n}\n\nconstexpr StringHash hash_string(const std::string& value) {\n   \
    \ return hash_string(std::string_view(value));\n}\n\nconstexpr StringHash hash_string(const\
    \ char* value) {\n    return hash_string(std::string_view(value));\n}\n\n// Returns\
    \ the hash of the concatenation represented by `left` and `right`.\nconstexpr\
    \ StringHash concat_string_hash(const StringHash& left, const StringHash& right)\
    \ {\n    using namespace string_hash_detail;\n    return StringHash{\n       \
    \ static_cast<std::uint32_t>((std::uint64_t(left.first) * right.first_power +\
    \ right.first) % first_mod),\n        static_cast<std::uint32_t>((std::uint64_t(left.second)\
    \ * right.second_power + right.second) % second_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.first_power)\
    \ * right.first_power % first_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.second_power)\
    \ * right.second_power % second_mod),\n        left.length + right.length,\n \
    \   };\n}\n\n// Hash adapter for std::unordered_map and std::unordered_set.\n\
    struct StringHasher {\n    using is_transparent = void;\n\n    constexpr std::size_t\
    \ operator()(std::string_view value) const {\n        return operator()(hash_string(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const std::string& value) const\
    \ {\n        return operator()(std::string_view(value));\n    }\n\n    constexpr\
    \ std::size_t operator()(const char* value) const {\n        return operator()(std::string_view(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const StringHash& value) const\
    \ {\n        std::uint64_t combined = (std::uint64_t(value.first) << 32) | value.second;\n\
    \        combined ^= std::uint64_t(value.length) + 0x9e3779b97f4a7c15ULL;\n  \
    \      combined ^= combined >> 30;\n        combined *= 0xbf58476d1ce4e5b9ULL;\n\
    \        combined ^= combined >> 27;\n        combined *= 0x94d049bb133111ebULL;\n\
    \        combined ^= combined >> 31;\n        return static_cast<std::size_t>(combined);\n\
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/string_hash.test.cpp\"\
    \n\n#include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n#include\
    \ <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
    #include <iterator>\n#line 14 \"utilities/fast_io.hpp\"\n#include <sys/stat.h>\n\
    #include <type_traits>\n#include <utility>\n#include <unistd.h>\n\nnamespace m1une\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/string/string_hash.test.cpp\"\
    \n#include <unordered_set>\n\nnamespace {\n\nvoid test_fixed() {\n    using m1une::string::concat_string_hash;\n\
    \    using m1une::string::hash_string;\n\n    constexpr auto empty = hash_string(\"\
    \");\n    constexpr auto first = hash_string(\"abc\");\n    constexpr auto second\
    \ = hash_string(\"def\");\n    constexpr auto combined = concat_string_hash(first,\
    \ second);\n    static_assert(combined == hash_string(\"abcdef\"));\n    static_assert(concat_string_hash(empty,\
    \ first) == first);\n    static_assert(concat_string_hash(first, empty) == first);\n\
    \    static_assert(hash_string(\"abc\") != hash_string(\"abd\"));\n    static_assert(\n\
    \        hash_string(\"a\")\n        != hash_string(std::string_view(\"a\\0\"\
    , 2))\n    );\n\n    std::string bytes;\n    bytes.push_back(char(0));\n    bytes.push_back(char(128));\n\
    \    bytes.push_back(char(255));\n    assert(\n        hash_string(bytes)\n  \
    \      == hash_string(std::string_view(bytes.data(), bytes.size()))\n    );\n\n\
    \    std::unordered_set<\n        std::string,\n        m1une::string::StringHasher,\n\
    \        std::equal_to<>\n    > words;\n    words.insert(\"alpha\");\n    words.insert(\"\
    beta\");\n    assert(words.contains(std::string_view(\"alpha\")));\n    assert(!words.contains(std::string_view(\"\
    gamma\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 1103;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        int first_length = int(random() % 40);\n      \
    \  int second_length = int(random() % 40);\n        std::string first(first_length,\
    \ '\\0');\n        std::string second(second_length, '\\0');\n        for (char&\
    \ character : first) character = char(random() & 255);\n        for (char& character\
    \ : second) character = char(random() & 255);\n\n        std::string joined =\
    \ first + second;\n        assert(\n            m1une::string::concat_string_hash(\n\
    \                m1une::string::hash_string(first),\n                m1une::string::hash_string(second)\n\
    \            ) == m1une::string::hash_string(joined)\n        );\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../string/string_hash.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ \"../../utilities/fast_io.hpp\"\n#include <string>\n#include <string_view>\n\
    #include <unordered_set>\n\nnamespace {\n\nvoid test_fixed() {\n    using m1une::string::concat_string_hash;\n\
    \    using m1une::string::hash_string;\n\n    constexpr auto empty = hash_string(\"\
    \");\n    constexpr auto first = hash_string(\"abc\");\n    constexpr auto second\
    \ = hash_string(\"def\");\n    constexpr auto combined = concat_string_hash(first,\
    \ second);\n    static_assert(combined == hash_string(\"abcdef\"));\n    static_assert(concat_string_hash(empty,\
    \ first) == first);\n    static_assert(concat_string_hash(first, empty) == first);\n\
    \    static_assert(hash_string(\"abc\") != hash_string(\"abd\"));\n    static_assert(\n\
    \        hash_string(\"a\")\n        != hash_string(std::string_view(\"a\\0\"\
    , 2))\n    );\n\n    std::string bytes;\n    bytes.push_back(char(0));\n    bytes.push_back(char(128));\n\
    \    bytes.push_back(char(255));\n    assert(\n        hash_string(bytes)\n  \
    \      == hash_string(std::string_view(bytes.data(), bytes.size()))\n    );\n\n\
    \    std::unordered_set<\n        std::string,\n        m1une::string::StringHasher,\n\
    \        std::equal_to<>\n    > words;\n    words.insert(\"alpha\");\n    words.insert(\"\
    beta\");\n    assert(words.contains(std::string_view(\"alpha\")));\n    assert(!words.contains(std::string_view(\"\
    gamma\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 1103;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        int first_length = int(random() % 40);\n      \
    \  int second_length = int(random() % 40);\n        std::string first(first_length,\
    \ '\\0');\n        std::string second(second_length, '\\0');\n        for (char&\
    \ character : first) character = char(random() & 255);\n        for (char& character\
    \ : second) character = char(random() & 255);\n\n        std::string joined =\
    \ first + second;\n        assert(\n            m1une::string::concat_string_hash(\n\
    \                m1une::string::hash_string(first),\n                m1une::string::hash_string(second)\n\
    \            ) == m1une::string::hash_string(joined)\n        );\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/string_hash.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/string_hash.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/string_hash.test.cpp
layout: document
redirect_from:
- /verify/verify/string/string_hash.test.cpp
- /verify/verify/string/string_hash.test.cpp.html
title: verify/string/string_hash.test.cpp
---
