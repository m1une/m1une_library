---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/rational_approximation.hpp
    title: Rational Approximation
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
    PROBLEM: https://judge.yosupo.jp/problem/rational_approximation
    links:
    - https://judge.yosupo.jp/problem/rational_approximation
  bundledCode: "#line 1 \"verify/math/rational_approximation.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rational_approximation\"\n\n#line 1 \"math/rational_approximation.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <concepts>\n#include\
    \ <cstdint>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\n\
    namespace math {\n\ntemplate <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\nstruct RationalApproximationResult {\n    using fraction_type = std::pair<T,\
    \ T>;\n\n    fraction_type lower;\n    fraction_type upper;\n};\n\nnamespace rational_approximation_detail\
    \ {\n\nusing Wide = __uint128_t;\n\nstruct Fraction {\n    Wide numerator;\n \
    \   Wide denominator;\n};\n\ninline bool equal(\n    const Fraction& fraction,\n\
    \    Wide numerator,\n    Wide denominator\n) {\n    return fraction.numerator\
    \ * denominator ==\n           numerator * fraction.denominator;\n}\n\ninline\
    \ Wide coordinate_bound(\n    Wide maximum,\n    Wide offset,\n    Wide step\n\
    ) {\n    return step == 0 ? maximum : (maximum - offset) / step;\n}\n\ninline\
    \ Fraction multiply_add(\n    const Fraction& first,\n    Wide multiplier,\n \
    \   const Fraction& second\n) {\n    return {\n        first.numerator * multiplier\
    \ + second.numerator,\n        first.denominator * multiplier + second.denominator\n\
    \    };\n}\n\n}  // namespace rational_approximation_detail\n\n// Returns the\
    \ closest reduced fractions below and above numerator/denominator\n// whose positive\
    \ numerator and denominator are both at most maximum.\ntemplate <std::integral\
    \ T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nRationalApproximationResult<T>\
    \ rational_approximation(\n    T maximum,\n    T numerator,\n    T denominator\n\
    ) {\n    assert(maximum > 0);\n    assert(numerator > 0);\n    assert(denominator\
    \ > 0);\n    static_assert(sizeof(T) <= sizeof(uint64_t));\n\n    using rational_approximation_detail::Fraction;\n\
    \    using rational_approximation_detail::Wide;\n    using rational_approximation_detail::coordinate_bound;\n\
    \    using rational_approximation_detail::equal;\n    using rational_approximation_detail::multiply_add;\n\
    \n    const Wide limit = static_cast<std::make_unsigned_t<T>>(maximum);\n    const\
    \ Wide target_numerator =\n        static_cast<std::make_unsigned_t<T>>(numerator);\n\
    \    const Wide target_denominator =\n        static_cast<std::make_unsigned_t<T>>(denominator);\n\
    \    Fraction lower{0, 1};\n    Fraction upper{1, 0};\n\n    while (true) {\n\
    \        Wide lower_multiplier = limit;\n        lower_multiplier = std::min(\n\
    \            lower_multiplier,\n            coordinate_bound(limit, lower.numerator,\
    \ upper.numerator)\n        );\n        lower_multiplier = std::min(\n       \
    \     lower_multiplier,\n            coordinate_bound(limit, lower.denominator,\
    \ upper.denominator)\n        );\n        const Wide lower_slack =\n         \
    \   target_numerator * lower.denominator -\n            lower.numerator * target_denominator;\n\
    \        const Wide lower_step =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        assert(lower_step\
    \ != 0);\n        lower_multiplier = std::min(\n            lower_multiplier,\
    \ lower_slack / lower_step\n        );\n        lower = multiply_add(upper, lower_multiplier,\
    \ lower);\n        if (equal(lower, target_numerator, target_denominator)) {\n\
    \            upper = lower;\n            break;\n        }\n\n        Wide upper_multiplier\
    \ = limit;\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.numerator, lower.numerator)\n     \
    \   );\n        upper_multiplier = std::min(\n            upper_multiplier,\n\
    \            coordinate_bound(limit, upper.denominator, lower.denominator)\n \
    \       );\n        const Wide upper_slack =\n            upper.numerator * target_denominator\
    \ -\n            target_numerator * upper.denominator;\n        const Wide upper_step\
    \ =\n            target_numerator * lower.denominator -\n            lower.numerator\
    \ * target_denominator;\n        assert(upper_step != 0);\n        upper_multiplier\
    \ = std::min(\n            upper_multiplier, upper_slack / upper_step\n      \
    \  );\n        upper = multiply_add(lower, upper_multiplier, upper);\n       \
    \ if (equal(upper, target_numerator, target_denominator)) {\n            lower\
    \ = upper;\n            break;\n        }\n\n        if (lower_multiplier == 0\
    \ && upper_multiplier == 0) break;\n    }\n\n    RationalApproximationResult<T>\
    \ result;\n    result.lower = {\n        static_cast<T>(lower.numerator),\n  \
    \      static_cast<T>(lower.denominator)\n    };\n    result.upper = {\n     \
    \   static_cast<T>(upper.numerator),\n        static_cast<T>(upper.denominator)\n\
    \    };\n    return result;\n}\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/math/rational_approximation.test.cpp\"\n\n#line 7 \"verify/math/rational_approximation.test.cpp\"\
    \n#include <numeric>\n#line 9 \"verify/math/rational_approximation.test.cpp\"\n\
    \n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n\
    #include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#line\
    \ 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace\
    \ utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/math/rational_approximation.test.cpp\"\
    \n\nnamespace {\n\nusing Fraction = std::pair<uint64_t, uint64_t>;\n\nbool less(const\
    \ Fraction& first, const Fraction& second) {\n    if (second.second == 0) return\
    \ first.second != 0;\n    if (first.second == 0) return false;\n    return static_cast<__uint128_t>(first.first)\
    \ * second.second <\n           static_cast<__uint128_t>(second.first) * first.second;\n\
    }\n\nstd::pair<Fraction, Fraction> brute(\n    uint64_t maximum,\n    uint64_t\
    \ numerator,\n    uint64_t denominator\n) {\n    Fraction lower(0, 1);\n    Fraction\
    \ upper(1, 0);\n    for (uint64_t a = 1; a <= maximum; a++) {\n        for (uint64_t\
    \ b = 1; b <= maximum; b++) {\n            if (std::gcd(a, b) != 1) continue;\n\
    \            const bool below =\n                static_cast<__uint128_t>(a) *\
    \ denominator <=\n                static_cast<__uint128_t>(numerator) * b;\n \
    \           const bool above =\n                static_cast<__uint128_t>(numerator)\
    \ * b <=\n                static_cast<__uint128_t>(a) * denominator;\n       \
    \     Fraction candidate(a, b);\n            if (below && less(lower, candidate))\
    \ lower = candidate;\n            if (above && less(candidate, upper)) upper =\
    \ candidate;\n        }\n    }\n    return {lower, upper};\n}\n\nvoid test_exhaustive()\
    \ {\n    for (uint64_t maximum = 1; maximum <= 10; maximum++) {\n        for (uint64_t\
    \ numerator = 1; numerator <= 12; numerator++) {\n            for (uint64_t denominator\
    \ = 1; denominator <= 12; denominator++) {\n                auto expected = brute(maximum,\
    \ numerator, denominator);\n                auto actual = m1une::math::rational_approximation(\n\
    \                    maximum, numerator, denominator\n                );\n   \
    \             assert(actual.lower == expected.first);\n                assert(actual.upper\
    \ == expected.second);\n            }\n        }\n    }\n\n    auto small = m1une::math::rational_approximation(1LL,\
    \ 1LL, 2LL);\n    using SignedFraction = decltype(small)::fraction_type;\n   \
    \ assert(small.lower == SignedFraction(0, 1));\n    assert(small.upper == SignedFraction(1,\
    \ 1));\n    auto large = m1une::math::rational_approximation(1LL, 2LL, 1LL);\n\
    \    assert(large.lower == SignedFraction(1, 1));\n    assert(large.upper == SignedFraction(1,\
    \ 0));\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_exhaustive();\n\
    \n    int test_count;\n    fast_input >> test_count;\n    while (test_count--)\
    \ {\n        uint64_t maximum, numerator, denominator;\n        fast_input >>\
    \ maximum >> numerator >> denominator;\n        auto result = m1une::math::rational_approximation(\n\
    \            maximum, numerator, denominator\n        );\n        fast_output\
    \ << result.lower.first << ' ' << result.lower.second << ' '\n               \
    \     << result.upper.first << ' ' << result.upper.second << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rational_approximation\"\
    \n\n#include \"../../math/rational_approximation.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <numeric>\n#include <utility>\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing Fraction = std::pair<uint64_t, uint64_t>;\n\nbool less(const\
    \ Fraction& first, const Fraction& second) {\n    if (second.second == 0) return\
    \ first.second != 0;\n    if (first.second == 0) return false;\n    return static_cast<__uint128_t>(first.first)\
    \ * second.second <\n           static_cast<__uint128_t>(second.first) * first.second;\n\
    }\n\nstd::pair<Fraction, Fraction> brute(\n    uint64_t maximum,\n    uint64_t\
    \ numerator,\n    uint64_t denominator\n) {\n    Fraction lower(0, 1);\n    Fraction\
    \ upper(1, 0);\n    for (uint64_t a = 1; a <= maximum; a++) {\n        for (uint64_t\
    \ b = 1; b <= maximum; b++) {\n            if (std::gcd(a, b) != 1) continue;\n\
    \            const bool below =\n                static_cast<__uint128_t>(a) *\
    \ denominator <=\n                static_cast<__uint128_t>(numerator) * b;\n \
    \           const bool above =\n                static_cast<__uint128_t>(numerator)\
    \ * b <=\n                static_cast<__uint128_t>(a) * denominator;\n       \
    \     Fraction candidate(a, b);\n            if (below && less(lower, candidate))\
    \ lower = candidate;\n            if (above && less(candidate, upper)) upper =\
    \ candidate;\n        }\n    }\n    return {lower, upper};\n}\n\nvoid test_exhaustive()\
    \ {\n    for (uint64_t maximum = 1; maximum <= 10; maximum++) {\n        for (uint64_t\
    \ numerator = 1; numerator <= 12; numerator++) {\n            for (uint64_t denominator\
    \ = 1; denominator <= 12; denominator++) {\n                auto expected = brute(maximum,\
    \ numerator, denominator);\n                auto actual = m1une::math::rational_approximation(\n\
    \                    maximum, numerator, denominator\n                );\n   \
    \             assert(actual.lower == expected.first);\n                assert(actual.upper\
    \ == expected.second);\n            }\n        }\n    }\n\n    auto small = m1une::math::rational_approximation(1LL,\
    \ 1LL, 2LL);\n    using SignedFraction = decltype(small)::fraction_type;\n   \
    \ assert(small.lower == SignedFraction(0, 1));\n    assert(small.upper == SignedFraction(1,\
    \ 1));\n    auto large = m1une::math::rational_approximation(1LL, 2LL, 1LL);\n\
    \    assert(large.lower == SignedFraction(1, 1));\n    assert(large.upper == SignedFraction(1,\
    \ 0));\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_exhaustive();\n\
    \n    int test_count;\n    fast_input >> test_count;\n    while (test_count--)\
    \ {\n        uint64_t maximum, numerator, denominator;\n        fast_input >>\
    \ maximum >> numerator >> denominator;\n        auto result = m1une::math::rational_approximation(\n\
    \            maximum, numerator, denominator\n        );\n        fast_output\
    \ << result.lower.first << ' ' << result.lower.second << ' '\n               \
    \     << result.upper.first << ' ' << result.upper.second << '\\n';\n    }\n}\n"
  dependsOn:
  - math/rational_approximation.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/rational_approximation.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/rational_approximation.test.cpp
layout: document
redirect_from:
- /verify/verify/math/rational_approximation.test.cpp
- /verify/verify/math/rational_approximation.test.cpp.html
title: verify/math/rational_approximation.test.cpp
---
