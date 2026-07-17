---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/runs.hpp
    title: Runs
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
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 1 \"verify/string/runs.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\
    \n\n#line 1 \"string/runs.hpp\"\n\n\n\n#include <algorithm>\n#include <set>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \nstruct Run {\n    int period;\n    int left;\n    int right;\n\n    bool operator==(const\
    \ Run&) const = default;\n};\n\nnamespace internal {\n\ntemplate <class Sequence>\n\
    class RunEnumerator {\n   private:\n    const Sequence& _sequence;\n    int _size;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _candidates;\n\n    template\
    \ <class Access>\n    static std::vector<int> z_algorithm(int length, Access access)\
    \ {\n        std::vector<int> z(length + 1, 0);\n        if (length == 0) return\
    \ z;\n        z[0] = length;\n        int left = 0;\n        int right = 0;\n\
    \        for (int i = 1; i < length; i++) {\n            if (i < right) z[i] =\
    \ std::min(right - i, z[i - left]);\n            while (\n                i +\
    \ z[i] < length &&\n                access(z[i]) == access(i + z[i])\n       \
    \     ) {\n                z[i]++;\n            }\n            if (right < i +\
    \ z[i]) {\n                left = i;\n                right = i + z[i];\n    \
    \        }\n        }\n        return z;\n    }\n\n    decltype(auto) element(int\
    \ index, bool reversed) const {\n        int original_index = reversed ? _size\
    \ - 1 - index : index;\n        return _sequence[original_index];\n    }\n\n \
    \   void add_candidate(int period, int left, int right, bool reversed) {\n   \
    \     if (reversed) {\n            left = _size - left;\n            right = _size\
    \ - right;\n            std::swap(left, right);\n        }\n        _candidates[period].emplace_back(left,\
    \ right);\n    }\n\n    void collect(int range_left, int range_right, int phase,\
    \ bool reversed) {\n        if (range_right - range_left <= 1) return;\n     \
    \   int middle = (range_left + range_right + phase) / 2;\n        collect(range_left,\
    \ middle, phase, reversed);\n        collect(middle, range_right, phase, reversed);\n\
    \n        int left_length = middle - range_left;\n        int right_length = range_right\
    \ - middle;\n        std::vector<int> left_z = z_algorithm(left_length, [&](int\
    \ index) -> decltype(auto) {\n            return element(middle - 1 - index, reversed);\n\
    \        });\n\n        int combined_length = right_length + range_right - range_left;\n\
    \        std::vector<int> right_z = z_algorithm(combined_length, [&](int index)\
    \ -> decltype(auto) {\n            if (index < right_length) return element(middle\
    \ + index, reversed);\n            return element(range_left + index - right_length,\
    \ reversed);\n        });\n\n        for (int start = middle - 1; start >= range_left;\
    \ start--) {\n            int period = middle - start;\n            int extend_left\
    \ = std::min(start - range_left, left_z[period]);\n            int extend_right\
    \ = std::min(\n                range_right - middle,\n                right_z[range_right\
    \ - range_left - period]\n            );\n            int left = start - extend_left;\n\
    \            int right = middle + extend_right;\n            if (right - left\
    \ >= 2 * period) {\n                add_candidate(period, left, right, reversed);\n\
    \            }\n        }\n    }\n\n   public:\n    explicit RunEnumerator(const\
    \ Sequence& sequence)\n        : _sequence(sequence),\n          _size(int(sequence.size())),\n\
    \          _candidates(_size / 2 + 1) {}\n\n    std::vector<Run> enumerate() {\n\
    \        collect(0, _size, 0, true);\n        collect(0, _size, 1, false);\n\n\
    \        std::set<std::pair<int, int>> used_intervals;\n        std::vector<Run>\
    \ result;\n        for (int period = 1; period <= _size / 2; period++) {\n   \
    \         std::vector<std::pair<int, int>>& candidates = _candidates[period];\n\
    \            std::sort(\n                candidates.begin(),\n               \
    \ candidates.end(),\n                [](const auto& first, const auto& second)\
    \ {\n                    if (first.first != second.first) {\n                \
    \        return first.first < second.first;\n                    }\n         \
    \           return first.second > second.second;\n                }\n        \
    \    );\n\n            int farthest_right = -1;\n            for (const auto&\
    \ interval : candidates) {\n                if (interval.second <= farthest_right)\
    \ continue;\n                farthest_right = interval.second;\n             \
    \   if (!used_intervals.insert(interval).second) continue;\n                result.push_back(Run{period,\
    \ interval.first, interval.second});\n            }\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace internal\n\n// Returns all runs as (minimum\
    \ period, maximal half-open interval),\n// sorted lexicographically by (period,\
    \ left, right).\ntemplate <class Sequence>\nstd::vector<Run> enumerate_runs(const\
    \ Sequence& sequence) {\n    return internal::RunEnumerator<Sequence>(sequence).enumerate();\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/runs.test.cpp\"\
    \n\n#line 6 \"verify/string/runs.test.cpp\"\n#include <cassert>\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n\
    #line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 17 \"\
    utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/string/runs.test.cpp\"\
    \n\nnamespace {\n\nbool has_period(const std::string& text, int left, int right,\
    \ int period) {\n    for (int i = left; i + period < right; i++) {\n        if\
    \ (text[i] != text[i + period]) return false;\n    }\n    return true;\n}\n\n\
    std::vector<m1une::string::Run> naive_runs(const std::string& text) {\n    int\
    \ n = int(text.size());\n    std::vector<m1une::string::Run> result;\n    for\
    \ (int left = 0; left < n; left++) {\n        for (int right = left + 2; right\
    \ <= n; right++) {\n            int minimum_period = right - left;\n         \
    \   for (int period = 1; period < right - left; period++) {\n                if\
    \ (has_period(text, left, right, period)) {\n                    minimum_period\
    \ = period;\n                    break;\n                }\n            }\n  \
    \          if (right - left < 2 * minimum_period) continue;\n            if (\n\
    \                left > 0 &&\n                text[left - 1] == text[left - 1\
    \ + minimum_period]\n            ) {\n                continue;\n            }\n\
    \            if (\n                right < n &&\n                text[right] ==\
    \ text[right - minimum_period]\n            ) {\n                continue;\n \
    \           }\n            result.push_back(m1une::string::Run{minimum_period,\
    \ left, right});\n        }\n    }\n    std::sort(result.begin(), result.end(),\
    \ [](const auto& first, const auto& second) {\n        if (first.period != second.period)\
    \ return first.period < second.period;\n        if (first.left != second.left)\
    \ return first.left < second.left;\n        return first.right < second.right;\n\
    \    });\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::enumerate_runs(empty).empty());\n    assert(m1une::string::enumerate_runs(std::string(\"\
    a\")).empty());\n\n    std::vector<m1une::string::Run> equal_expected;\n    equal_expected.push_back(m1une::string::Run{1,\
    \ 0, 5});\n    assert(m1une::string::enumerate_runs(std::string(\"aaaaa\")) ==\
    \ equal_expected);\n\n    std::vector<int> values;\n    values.push_back(4);\n\
    \    values.push_back(7);\n    values.push_back(4);\n    values.push_back(7);\n\
    \    values.push_back(4);\n    std::vector<m1une::string::Run> vector_expected;\n\
    \    vector_expected.push_back(m1une::string::Run{2, 0, 5});\n    assert(m1une::string::enumerate_runs(values)\
    \ == vector_expected);\n\n    std::vector<bool> bits(6, false);\n    bits[1] =\
    \ true;\n    bits[3] = true;\n    bits[5] = true;\n    std::vector<m1une::string::Run>\
    \ bit_expected;\n    bit_expected.push_back(m1une::string::Run{2, 0, 6});\n  \
    \  assert(m1une::string::enumerate_runs(bits) == bit_expected);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260713;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n        int n = int(random()\
    \ % 14);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n        assert(m1une::string::enumerate_runs(text)\
    \ == naive_runs(text));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    std::vector<m1une::string::Run>\
    \ runs = m1une::string::enumerate_runs(text);\n    fast_output << runs.size()\
    \ << '\\n';\n    for (const auto& run : runs) {\n        fast_output << run.period\
    \ << ' ' << run.left << ' ' << run.right << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n\n#include\
    \ \"../../string/runs.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <string>\n#include\
    \ <vector>\n\nnamespace {\n\nbool has_period(const std::string& text, int left,\
    \ int right, int period) {\n    for (int i = left; i + period < right; i++) {\n\
    \        if (text[i] != text[i + period]) return false;\n    }\n    return true;\n\
    }\n\nstd::vector<m1une::string::Run> naive_runs(const std::string& text) {\n \
    \   int n = int(text.size());\n    std::vector<m1une::string::Run> result;\n \
    \   for (int left = 0; left < n; left++) {\n        for (int right = left + 2;\
    \ right <= n; right++) {\n            int minimum_period = right - left;\n   \
    \         for (int period = 1; period < right - left; period++) {\n          \
    \      if (has_period(text, left, right, period)) {\n                    minimum_period\
    \ = period;\n                    break;\n                }\n            }\n  \
    \          if (right - left < 2 * minimum_period) continue;\n            if (\n\
    \                left > 0 &&\n                text[left - 1] == text[left - 1\
    \ + minimum_period]\n            ) {\n                continue;\n            }\n\
    \            if (\n                right < n &&\n                text[right] ==\
    \ text[right - minimum_period]\n            ) {\n                continue;\n \
    \           }\n            result.push_back(m1une::string::Run{minimum_period,\
    \ left, right});\n        }\n    }\n    std::sort(result.begin(), result.end(),\
    \ [](const auto& first, const auto& second) {\n        if (first.period != second.period)\
    \ return first.period < second.period;\n        if (first.left != second.left)\
    \ return first.left < second.left;\n        return first.right < second.right;\n\
    \    });\n    return result;\n}\n\nvoid test_edge_cases() {\n    std::string empty;\n\
    \    assert(m1une::string::enumerate_runs(empty).empty());\n    assert(m1une::string::enumerate_runs(std::string(\"\
    a\")).empty());\n\n    std::vector<m1une::string::Run> equal_expected;\n    equal_expected.push_back(m1une::string::Run{1,\
    \ 0, 5});\n    assert(m1une::string::enumerate_runs(std::string(\"aaaaa\")) ==\
    \ equal_expected);\n\n    std::vector<int> values;\n    values.push_back(4);\n\
    \    values.push_back(7);\n    values.push_back(4);\n    values.push_back(7);\n\
    \    values.push_back(4);\n    std::vector<m1une::string::Run> vector_expected;\n\
    \    vector_expected.push_back(m1une::string::Run{2, 0, 5});\n    assert(m1une::string::enumerate_runs(values)\
    \ == vector_expected);\n\n    std::vector<bool> bits(6, false);\n    bits[1] =\
    \ true;\n    bits[3] = true;\n    bits[5] = true;\n    std::vector<m1une::string::Run>\
    \ bit_expected;\n    bit_expected.push_back(m1une::string::Run{2, 0, 6});\n  \
    \  assert(m1une::string::enumerate_runs(bits) == bit_expected);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 20260713;\n    auto random = [&state]() {\n   \
    \     state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 5000; trial++) {\n        int n = int(random()\
    \ % 14);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n        assert(m1une::string::enumerate_runs(text)\
    \ == naive_runs(text));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n\
    \    test_randomized();\n    std::string text;\n    fast_input >> text;\n    std::vector<m1une::string::Run>\
    \ runs = m1une::string::enumerate_runs(text);\n    fast_output << runs.size()\
    \ << '\\n';\n    for (const auto& run : runs) {\n        fast_output << run.period\
    \ << ' ' << run.left << ' ' << run.right << '\\n';\n    }\n}\n"
  dependsOn:
  - string/runs.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/string/runs.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/runs.test.cpp
layout: document
redirect_from:
- /verify/verify/string/runs.test.cpp
- /verify/verify/string/runs.test.cpp.html
title: verify/string/runs.test.cpp
---
