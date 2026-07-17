---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/integer_arithmetic.hpp
    title: Integer Roots and Powers
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
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_integer
    links:
    - https://judge.yosupo.jp/problem/kth_root_integer
  bundledCode: "#line 1 \"verify/math/integer_arithmetic.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n#line 1 \"math/integer_arithmetic.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n\nnamespace m1une {\nnamespace math {\n\nnamespace integer_arithmetic_detail\
    \ {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr std::optional<T> checked_multiply(T first, T second) {\n \
    \   constexpr T minimum = std::numeric_limits<T>::min();\n    constexpr T maximum\
    \ = std::numeric_limits<T>::max();\n\n    if constexpr (std::unsigned_integral<T>)\
    \ {\n        if (second != 0 && maximum / second < first) return std::nullopt;\n\
    \    } else {\n        if (0 < first) {\n            if (0 < second) {\n     \
    \           if (maximum / second < first) return std::nullopt;\n            }\
    \ else if (second < minimum / first) {\n                return std::nullopt;\n\
    \            }\n        } else if (first < 0) {\n            if (0 < second) {\n\
    \                if (first < minimum / second) return std::nullopt;\n        \
    \    } else if (second < maximum / first) {\n                return std::nullopt;\n\
    \            }\n        }\n    }\n    return T(first * second);\n}\n\ntemplate\
    \ <std::unsigned_integral T>\nconstexpr bool kth_power_leq(T base, unsigned exponent,\
    \ T limit) {\n    assert(exponent > 0);\n    if (base <= 1) return base <= limit;\n\
    \n    const T multiplication_limit = limit / base;\n    T product = 1;\n    for\
    \ (unsigned i = 0; i < exponent; i++) {\n        if (product > multiplication_limit)\
    \ return false;\n        product *= base;\n    }\n    return true;\n}\n\n}  //\
    \ namespace integer_arithmetic_detail\n\n// Returns floor(sqrt(value)) exactly,\
    \ without floating-point arithmetic.\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T isqrt(T value) {\n    if constexpr (std::signed_integral<T>)\
    \ assert(0 <= value);\n    if (value <= 1) return value;\n\n    T low = 1;\n \
    \   T high = value / 2 + 1;\n    while (low < high) {\n        T middle = low\
    \ + (high - low + 1) / 2;\n        if (middle <= value / middle) {\n         \
    \   low = middle;\n        } else {\n            high = middle - 1;\n        }\n\
    \    }\n    return low;\n}\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nconstexpr T floor_sqrt(T value) {\n    return isqrt(value);\n}\n\n//\
    \ Returns ceil(sqrt(value)) exactly, without floating-point arithmetic.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nconstexpr\
    \ T ceil_sqrt(T value) {\n    T result = isqrt(value);\n    if (result == 0) return\
    \ 0;\n    if (result != 0 && value / result == result && value % result == 0)\
    \ {\n        return result;\n    }\n    return result + 1;\n}\n\n// Returns floor(value^(1\
    \ / degree)) exactly, without floating-point arithmetic.\ntemplate <std::integral\
    \ T, std::integral Degree>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Degree>, bool>\n)\nconstexpr T\
    \ floor_kth_root(T value, Degree degree) {\n    if constexpr (std::signed_integral<T>)\
    \ {\n        assert(0 <= value);\n        if (value < 0) return T();\n    }\n\
    \    assert(0 < degree);\n    if (degree <= 0) return T();\n    if (value <= 1\
    \ || degree == 1) return value;\n    if (degree == 2) return isqrt(value);\n\n\
    \    using U = std::make_unsigned_t<T>;\n    using UDegree = std::make_unsigned_t<Degree>;\n\
    \    constexpr int digits = std::numeric_limits<U>::digits;\n    const UDegree\
    \ unsigned_degree = static_cast<UDegree>(degree);\n    if (unsigned_degree >=\
    \ static_cast<UDegree>(digits)) return T(1);\n    const unsigned exponent = static_cast<unsigned>(unsigned_degree);\n\
    \    const U unsigned_value = static_cast<U>(value);\n\n    int bit_width = 0;\n\
    \    for (U remaining = unsigned_value; remaining != 0; remaining >>= 1) {\n \
    \       bit_width++;\n    }\n    const int root_bits =\n        (bit_width + static_cast<int>(exponent)\
    \ - 1) /\n        static_cast<int>(exponent);\n\n    U low = 1;\n    U high =\
    \ U(1) << root_bits;\n    while (high - low > 1) {\n        const U middle = low\
    \ + (high - low) / 2;\n        if (\n            integer_arithmetic_detail::kth_power_leq(\n\
    \                middle, exponent, unsigned_value\n            )\n        ) {\n\
    \            low = middle;\n        } else {\n            high = middle;\n   \
    \     }\n    }\n    return static_cast<T>(low);\n}\n\n// Returns base^exponent,\
    \ or nullopt when the result does not fit in T.\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr std::optional<T> checked_ipow(T base, Exponent exponent)\
    \ {\n    T result = 1;\n    while (exponent != 0) {\n        if (exponent & 1)\
    \ {\n            auto product =\n                integer_arithmetic_detail::checked_multiply(result,\
    \ base);\n            if (!product.has_value()) return std::nullopt;\n       \
    \     result = *product;\n        }\n        exponent >>= 1;\n        if (exponent\
    \ != 0) {\n            auto square =\n                integer_arithmetic_detail::checked_multiply(base,\
    \ base);\n            if (!square.has_value()) return std::nullopt;\n        \
    \    base = *square;\n        }\n    }\n    return result;\n}\n\ntemplate <std::integral\
    \ T, std::unsigned_integral Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>,\
    \ bool>\n    && !std::same_as<std::remove_cv_t<Exponent>, bool>\n)\nconstexpr\
    \ std::optional<T> checked_integer_pow(T base, Exponent exponent) {\n    return\
    \ checked_ipow(base, exponent);\n}\n\n// Returns base^exponent. The result must\
    \ be representable by T.\ntemplate <std::integral T, std::unsigned_integral Exponent>\n\
    requires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T ipow(T base, Exponent exponent) {\n    std::optional<T>\
    \ result = checked_ipow(base, exponent);\n    assert(result.has_value());\n  \
    \  return result.value_or(T());\n}\n\ntemplate <std::integral T, std::unsigned_integral\
    \ Exponent>\nrequires(\n    !std::same_as<std::remove_cv_t<T>, bool>\n    && !std::same_as<std::remove_cv_t<Exponent>,\
    \ bool>\n)\nconstexpr T integer_pow(T base, Exponent exponent) {\n    return ipow(base,\
    \ exponent);\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/math/integer_arithmetic.test.cpp\"\n\n#include <algorithm>\n#line 7 \"\
    verify/math/integer_arithmetic.test.cpp\"\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line\
    \ 16 \"utilities/fast_io.hpp\"\n#include <utility>\n#include <unistd.h>\n\nnamespace\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/math/integer_arithmetic.test.cpp\"\
    \n\nnamespace {\n\ntemplate <class T>\nvoid test_square_roots() {\n    using U\
    \ = std::make_unsigned_t<T>;\n    U limit = std::min<U>(std::numeric_limits<T>::max(),\
    \ U(100000));\n    for (U value = 0;; ++value) {\n        T input = static_cast<T>(value);\n\
    \        [[maybe_unused]] T floor = m1une::math::isqrt(input);\n        [[maybe_unused]]\
    \ T ceiling = m1une::math::ceil_sqrt(input);\n        assert(floor <= input /\
    \ (floor == 0 ? 1 : floor));\n        assert(floor == 0 || floor + 1 > input /\
    \ (floor + 1));\n        assert(ceiling == floor || ceiling == floor + 1);\n \
    \       assert(\n            ceiling == floor\n            ? floor * floor ==\
    \ input\n            : floor * floor < input\n        );\n        if (value ==\
    \ limit) break;\n    }\n}\n\nvoid test_boundaries() {\n    constexpr std::uint64_t\
    \ maximum =\n        std::numeric_limits<std::uint64_t>::max();\n    constexpr\
    \ std::uint64_t root = 4294967295ULL;\n    static_assert(m1une::math::isqrt(maximum)\
    \ == root);\n    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);\n\
    \    static_assert(m1une::math::isqrt(root * root) == root);\n\n    constexpr\
    \ long long signed_maximum =\n        std::numeric_limits<long long>::max();\n\
    \    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);\n    static_assert(m1une::math::ceil_sqrt(signed_maximum)\
    \ == 3037000500LL);\n}\n\nvoid test_kth_roots() {\n    using m1une::math::checked_ipow;\n\
    \    using m1une::math::floor_kth_root;\n    constexpr std::uint64_t maximum =\n\
    \        std::numeric_limits<std::uint64_t>::max();\n\n    static_assert(floor_kth_root(0ULL,\
    \ 1) == 0);\n    static_assert(floor_kth_root(1ULL, 64) == 1);\n    static_assert(floor_kth_root(7ULL,\
    \ 3) == 1);\n    static_assert(floor_kth_root(8ULL, 3) == 2);\n    static_assert(floor_kth_root(80ULL,\
    \ 4) == 2);\n    static_assert(floor_kth_root(81ULL, 4) == 3);\n    static_assert(floor_kth_root(maximum,\
    \ 1) == maximum);\n    static_assert(floor_kth_root(maximum, 2) == 4294967295ULL);\n\
    \    static_assert(floor_kth_root(maximum, 3) == 2642245ULL);\n    static_assert(floor_kth_root(maximum,\
    \ 64) == 1);\n    static_assert(\n        floor_kth_root(std::numeric_limits<long\
    \ long>::max(), 3U)\n        == 2097151LL\n    );\n\n    for (std::uint64_t value\
    \ = 0; value <= 10000; value++) {\n        for (unsigned degree = 1; degree <=\
    \ 16; degree++) {\n            std::uint64_t root = floor_kth_root(value, degree);\n\
    \            std::optional<std::uint64_t> power = checked_ipow(root, degree);\n\
    \            assert(power.has_value() && *power <= value);\n\n            std::optional<std::uint64_t>\
    \ next_power =\n                checked_ipow(root + 1, degree);\n            assert(!next_power.has_value()\
    \ || value < *next_power);\n        }\n    }\n}\n\nvoid test_powers() {\n    using\
    \ m1une::math::checked_ipow;\n    using m1une::math::ipow;\n\n    static_assert(ipow(0LL,\
    \ 0U) == 1);\n    static_assert(ipow(2LL, 10U) == 1024);\n    static_assert(ipow(-3LL,\
    \ 3U) == -27);\n    static_assert(ipow(-3LL, 4U) == 81);\n    static_assert(\n\
    \        ipow(-2LL, 63U) == std::numeric_limits<long long>::min()\n    );\n  \
    \  static_assert(!checked_ipow(2LL, 63U).has_value());\n    static_assert(!checked_ipow(-2LL,\
    \ 64U).has_value());\n    static_assert(!checked_ipow(10ULL, 20U).has_value());\n\
    \    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));\n\
    \    static_assert(\n        checked_ipow(std::numeric_limits<long long>::min(),\
    \ 1U)\n        == std::optional(std::numeric_limits<long long>::min())\n    );\n\
    \    static_assert(\n        !checked_ipow(std::numeric_limits<long long>::min(),\
    \ 2U).has_value()\n    );\n\n    for (long long base = -20; base <= 20; ++base)\
    \ {\n        [[maybe_unused]] long long expected = 1;\n        for (unsigned exponent\
    \ = 0; exponent <= 8; ++exponent) {\n            assert(ipow(base, exponent) ==\
    \ expected);\n            expected *= base;\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_square_roots<signed char>();\n    test_square_roots<unsigned\
    \ char>();\n    test_square_roots<short>();\n    test_square_roots<unsigned short>();\n\
    \    test_square_roots<int>();\n    test_square_roots<unsigned int>();\n    test_square_roots<long\
    \ long>();\n    test_square_roots<unsigned long long>();\n    test_boundaries();\n\
    \    test_kth_roots();\n    test_powers();\n\n    int test_count;\n    fast_input\
    \ >> test_count;\n    while (test_count--) {\n        std::uint64_t value;\n \
    \       int degree;\n        fast_input >> value >> degree;\n        fast_output\
    \ << m1une::math::floor_kth_root(value, degree) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n\
    #include \"../../math/integer_arithmetic.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include\
    \ <limits>\n#include <optional>\n\nnamespace {\n\ntemplate <class T>\nvoid test_square_roots()\
    \ {\n    using U = std::make_unsigned_t<T>;\n    U limit = std::min<U>(std::numeric_limits<T>::max(),\
    \ U(100000));\n    for (U value = 0;; ++value) {\n        T input = static_cast<T>(value);\n\
    \        [[maybe_unused]] T floor = m1une::math::isqrt(input);\n        [[maybe_unused]]\
    \ T ceiling = m1une::math::ceil_sqrt(input);\n        assert(floor <= input /\
    \ (floor == 0 ? 1 : floor));\n        assert(floor == 0 || floor + 1 > input /\
    \ (floor + 1));\n        assert(ceiling == floor || ceiling == floor + 1);\n \
    \       assert(\n            ceiling == floor\n            ? floor * floor ==\
    \ input\n            : floor * floor < input\n        );\n        if (value ==\
    \ limit) break;\n    }\n}\n\nvoid test_boundaries() {\n    constexpr std::uint64_t\
    \ maximum =\n        std::numeric_limits<std::uint64_t>::max();\n    constexpr\
    \ std::uint64_t root = 4294967295ULL;\n    static_assert(m1une::math::isqrt(maximum)\
    \ == root);\n    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);\n\
    \    static_assert(m1une::math::isqrt(root * root) == root);\n\n    constexpr\
    \ long long signed_maximum =\n        std::numeric_limits<long long>::max();\n\
    \    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);\n    static_assert(m1une::math::ceil_sqrt(signed_maximum)\
    \ == 3037000500LL);\n}\n\nvoid test_kth_roots() {\n    using m1une::math::checked_ipow;\n\
    \    using m1une::math::floor_kth_root;\n    constexpr std::uint64_t maximum =\n\
    \        std::numeric_limits<std::uint64_t>::max();\n\n    static_assert(floor_kth_root(0ULL,\
    \ 1) == 0);\n    static_assert(floor_kth_root(1ULL, 64) == 1);\n    static_assert(floor_kth_root(7ULL,\
    \ 3) == 1);\n    static_assert(floor_kth_root(8ULL, 3) == 2);\n    static_assert(floor_kth_root(80ULL,\
    \ 4) == 2);\n    static_assert(floor_kth_root(81ULL, 4) == 3);\n    static_assert(floor_kth_root(maximum,\
    \ 1) == maximum);\n    static_assert(floor_kth_root(maximum, 2) == 4294967295ULL);\n\
    \    static_assert(floor_kth_root(maximum, 3) == 2642245ULL);\n    static_assert(floor_kth_root(maximum,\
    \ 64) == 1);\n    static_assert(\n        floor_kth_root(std::numeric_limits<long\
    \ long>::max(), 3U)\n        == 2097151LL\n    );\n\n    for (std::uint64_t value\
    \ = 0; value <= 10000; value++) {\n        for (unsigned degree = 1; degree <=\
    \ 16; degree++) {\n            std::uint64_t root = floor_kth_root(value, degree);\n\
    \            std::optional<std::uint64_t> power = checked_ipow(root, degree);\n\
    \            assert(power.has_value() && *power <= value);\n\n            std::optional<std::uint64_t>\
    \ next_power =\n                checked_ipow(root + 1, degree);\n            assert(!next_power.has_value()\
    \ || value < *next_power);\n        }\n    }\n}\n\nvoid test_powers() {\n    using\
    \ m1une::math::checked_ipow;\n    using m1une::math::ipow;\n\n    static_assert(ipow(0LL,\
    \ 0U) == 1);\n    static_assert(ipow(2LL, 10U) == 1024);\n    static_assert(ipow(-3LL,\
    \ 3U) == -27);\n    static_assert(ipow(-3LL, 4U) == 81);\n    static_assert(\n\
    \        ipow(-2LL, 63U) == std::numeric_limits<long long>::min()\n    );\n  \
    \  static_assert(!checked_ipow(2LL, 63U).has_value());\n    static_assert(!checked_ipow(-2LL,\
    \ 64U).has_value());\n    static_assert(!checked_ipow(10ULL, 20U).has_value());\n\
    \    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));\n\
    \    static_assert(\n        checked_ipow(std::numeric_limits<long long>::min(),\
    \ 1U)\n        == std::optional(std::numeric_limits<long long>::min())\n    );\n\
    \    static_assert(\n        !checked_ipow(std::numeric_limits<long long>::min(),\
    \ 2U).has_value()\n    );\n\n    for (long long base = -20; base <= 20; ++base)\
    \ {\n        [[maybe_unused]] long long expected = 1;\n        for (unsigned exponent\
    \ = 0; exponent <= 8; ++exponent) {\n            assert(ipow(base, exponent) ==\
    \ expected);\n            expected *= base;\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_square_roots<signed char>();\n    test_square_roots<unsigned\
    \ char>();\n    test_square_roots<short>();\n    test_square_roots<unsigned short>();\n\
    \    test_square_roots<int>();\n    test_square_roots<unsigned int>();\n    test_square_roots<long\
    \ long>();\n    test_square_roots<unsigned long long>();\n    test_boundaries();\n\
    \    test_kth_roots();\n    test_powers();\n\n    int test_count;\n    fast_input\
    \ >> test_count;\n    while (test_count--) {\n        std::uint64_t value;\n \
    \       int degree;\n        fast_input >> value >> degree;\n        fast_output\
    \ << m1une::math::floor_kth_root(value, degree) << '\\n';\n    }\n}\n"
  dependsOn:
  - math/integer_arithmetic.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/integer_arithmetic.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/integer_arithmetic.test.cpp
layout: document
redirect_from:
- /verify/verify/math/integer_arithmetic.test.cpp
- /verify/verify/math/integer_arithmetic.test.cpp.html
title: verify/math/integer_arithmetic.test.cpp
---
