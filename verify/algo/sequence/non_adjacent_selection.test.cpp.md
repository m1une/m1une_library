---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/non_adjacent_selection.hpp
    title: Non-Adjacent Selection Sums
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
  bundledCode: "#line 1 \"verify/algo/sequence/non_adjacent_selection.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <vector>\n\n#line 1 \"algo/sequence/non_adjacent_selection.hpp\"\
    \n\n\n\n#include <functional>\n#include <queue>\n#line 7 \"algo/sequence/non_adjacent_selection.hpp\"\
    \n\nnamespace m1une {\nnamespace algo {\n\nnamespace detail {\n\ntemplate <typename\
    \ T>\nstruct NonAdjacentSelectionEntry {\n    T value;\n    int index;\n};\n\n\
    template <typename T, typename Better>\nstruct NonAdjacentSelectionCompare {\n\
    \    Better better;\n\n    bool operator()(\n        const NonAdjacentSelectionEntry<T>&\
    \ lhs,\n        const NonAdjacentSelectionEntry<T>& rhs\n    ) const {\n     \
    \   if (better(lhs.value, rhs.value)) return false;\n        if (better(rhs.value,\
    \ lhs.value)) return true;\n        return lhs.index > rhs.index;\n    }\n};\n\
    \ntemplate <typename T, typename Better>\nstd::vector<T> non_adjacent_selection_sums(const\
    \ std::vector<T>& values, Better better) {\n    const int n = int(values.size());\n\
    \    std::vector<T> weight = values;\n    std::vector<int> left(n), right(n);\n\
    \    std::vector<char> alive(n, true);\n    for (int i = 0; i < n; ++i) {\n  \
    \      left[i] = i - 1;\n        right[i] = (i + 1 == n ? -1 : i + 1);\n    }\n\
    \n    using Entry = NonAdjacentSelectionEntry<T>;\n    using Compare = NonAdjacentSelectionCompare<T,\
    \ Better>;\n    std::priority_queue<Entry, std::vector<Entry>, Compare> heap(Compare{better});\n\
    \    for (int i = 0; i < n; ++i) heap.push(Entry{weight[i], i});\n\n    std::vector<T>\
    \ result;\n    result.reserve((n + 1) / 2);\n    T sum{};\n    while (int(result.size())\
    \ < (n + 1) / 2) {\n        while (!alive[heap.top().index]) heap.pop();\n   \
    \     const int current = heap.top().index;\n        heap.pop();\n\n        sum\
    \ += weight[current];\n        result.push_back(sum);\n\n        const int l =\
    \ left[current];\n        const int r = right[current];\n        if (l != -1 &&\
    \ r != -1) {\n            weight[current] = weight[l] + weight[r] - weight[current];\n\
    \n            const int ll = left[l];\n            const int rr = right[r];\n\
    \            alive[l] = false;\n            alive[r] = false;\n            left[current]\
    \ = ll;\n            right[current] = rr;\n            if (ll != -1) right[ll]\
    \ = current;\n            if (rr != -1) left[rr] = current;\n            heap.push(Entry{weight[current],\
    \ current});\n        } else {\n            const int ll = (l == -1 ? -1 : left[l]);\n\
    \            const int rr = (r == -1 ? -1 : right[r]);\n            alive[current]\
    \ = false;\n            if (l != -1) alive[l] = false;\n            if (r != -1)\
    \ alive[r] = false;\n            if (ll != -1) right[ll] = rr;\n            if\
    \ (rr != -1) left[rr] = ll;\n        }\n    }\n    return result;\n}\n\n}  //\
    \ namespace detail\n\n// Entry k - 1 is the maximum sum obtained by selecting\
    \ exactly k values, with\n// no two selected indices adjacent.\ntemplate <typename\
    \ T>\nstd::vector<T> maximum_non_adjacent_selection_sums(const std::vector<T>&\
    \ values) {\n    return detail::non_adjacent_selection_sums(values, std::greater<T>{});\n\
    }\n\n// Entry k - 1 is the minimum sum obtained by selecting exactly k values,\
    \ with\n// no two selected indices adjacent.\ntemplate <typename T>\nstd::vector<T>\
    \ minimum_non_adjacent_selection_sums(const std::vector<T>& values) {\n    return\
    \ detail::non_adjacent_selection_sums(values, std::less<T>{});\n}\n\n}  // namespace\
    \ algo\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line\
    \ 5 \"utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/sequence/non_adjacent_selection.test.cpp\"\
    \n\nstd::vector<long long> naive_non_adjacent_selection_sums(\n    const std::vector<long\
    \ long>& values,\n    bool maximize\n) {\n    const int n = int(values.size());\n\
    \    const int count_limit = (n + 1) / 2;\n    const long long inf = std::numeric_limits<long\
    \ long>::max();\n    std::vector<long long> result(count_limit, maximize ? -inf\
    \ : inf);\n\n    for (int mask = 0; mask < (1 << n); ++mask) {\n        if ((mask\
    \ & (mask << 1)) != 0) continue;\n        const int count = __builtin_popcount(unsigned(mask));\n\
    \        if (count == 0) continue;\n\n        long long sum = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if ((mask >> i) & 1) sum += values[i];\n\
    \        }\n        if (maximize) {\n            result[count - 1] = std::max(result[count\
    \ - 1], sum);\n        } else {\n            result[count - 1] = std::min(result[count\
    \ - 1], sum);\n        }\n    }\n    return result;\n}\n\nvoid test_examples_and_boundaries()\
    \ {\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(std::vector<long\
    \ long>{}).empty());\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(std::vector<long\
    \ long>{}).empty());\n\n    std::vector<long long> one = {-7};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(one)\
    \ == one);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(one) ==\
    \ one);\n\n    std::vector<long long> values = {4, 1, 7, 3};\n    std::vector<long\
    \ long> expected_maximum = {7, 11};\n    std::vector<long long> expected_minimum\
    \ = {1, 4};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(values)\
    \ == expected_maximum);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(values)\
    \ == expected_minimum);\n\n    values = {1, 100, 1};\n    expected_maximum = {100,\
    \ 2};\n    expected_minimum = {1, 2};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(values)\
    \ == expected_maximum);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(values)\
    \ == expected_minimum);\n}\n\nvoid test_randomized() {\n    unsigned state = 123456789U;\n\
    \    auto random = [&]() {\n        state ^= state << 13;\n        state ^= state\
    \ >> 17;\n        state ^= state << 5;\n        return state;\n    };\n\n    for\
    \ (int n = 0; n <= 12; ++n) {\n        for (int iteration = 0; iteration < 500;\
    \ ++iteration) {\n            std::vector<long long> values(n);\n            for\
    \ (long long& value : values) {\n                value = static_cast<long long>(random()\
    \ % 41) - 20;\n            }\n\n            assert(\n                m1une::algo::maximum_non_adjacent_selection_sums(values)\n\
    \                == naive_non_adjacent_selection_sums(values, true)\n        \
    \    );\n            assert(\n                m1une::algo::minimum_non_adjacent_selection_sums(values)\n\
    \                == naive_non_adjacent_selection_sums(values, false)\n       \
    \     );\n        }\n    }\n}\n\nint main() {\n    test_examples_and_boundaries();\n\
    \    test_randomized();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <vector>\n\n#include \"../../../algo/sequence/non_adjacent_selection.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\nstd::vector<long long> naive_non_adjacent_selection_sums(\n\
    \    const std::vector<long long>& values,\n    bool maximize\n) {\n    const\
    \ int n = int(values.size());\n    const int count_limit = (n + 1) / 2;\n    const\
    \ long long inf = std::numeric_limits<long long>::max();\n    std::vector<long\
    \ long> result(count_limit, maximize ? -inf : inf);\n\n    for (int mask = 0;\
    \ mask < (1 << n); ++mask) {\n        if ((mask & (mask << 1)) != 0) continue;\n\
    \        const int count = __builtin_popcount(unsigned(mask));\n        if (count\
    \ == 0) continue;\n\n        long long sum = 0;\n        for (int i = 0; i < n;\
    \ ++i) {\n            if ((mask >> i) & 1) sum += values[i];\n        }\n    \
    \    if (maximize) {\n            result[count - 1] = std::max(result[count -\
    \ 1], sum);\n        } else {\n            result[count - 1] = std::min(result[count\
    \ - 1], sum);\n        }\n    }\n    return result;\n}\n\nvoid test_examples_and_boundaries()\
    \ {\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(std::vector<long\
    \ long>{}).empty());\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(std::vector<long\
    \ long>{}).empty());\n\n    std::vector<long long> one = {-7};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(one)\
    \ == one);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(one) ==\
    \ one);\n\n    std::vector<long long> values = {4, 1, 7, 3};\n    std::vector<long\
    \ long> expected_maximum = {7, 11};\n    std::vector<long long> expected_minimum\
    \ = {1, 4};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(values)\
    \ == expected_maximum);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(values)\
    \ == expected_minimum);\n\n    values = {1, 100, 1};\n    expected_maximum = {100,\
    \ 2};\n    expected_minimum = {1, 2};\n    assert(m1une::algo::maximum_non_adjacent_selection_sums(values)\
    \ == expected_maximum);\n    assert(m1une::algo::minimum_non_adjacent_selection_sums(values)\
    \ == expected_minimum);\n}\n\nvoid test_randomized() {\n    unsigned state = 123456789U;\n\
    \    auto random = [&]() {\n        state ^= state << 13;\n        state ^= state\
    \ >> 17;\n        state ^= state << 5;\n        return state;\n    };\n\n    for\
    \ (int n = 0; n <= 12; ++n) {\n        for (int iteration = 0; iteration < 500;\
    \ ++iteration) {\n            std::vector<long long> values(n);\n            for\
    \ (long long& value : values) {\n                value = static_cast<long long>(random()\
    \ % 41) - 20;\n            }\n\n            assert(\n                m1une::algo::maximum_non_adjacent_selection_sums(values)\n\
    \                == naive_non_adjacent_selection_sums(values, true)\n        \
    \    );\n            assert(\n                m1une::algo::minimum_non_adjacent_selection_sums(values)\n\
    \                == naive_non_adjacent_selection_sums(values, false)\n       \
    \     );\n        }\n    }\n}\n\nint main() {\n    test_examples_and_boundaries();\n\
    \    test_randomized();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n    long long a, b;\n    input >> a >> b;\n    output << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - algo/sequence/non_adjacent_selection.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/algo/sequence/non_adjacent_selection.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/sequence/non_adjacent_selection.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/sequence/non_adjacent_selection.test.cpp
- /verify/verify/algo/sequence/non_adjacent_selection.test.cpp.html
title: verify/algo/sequence/non_adjacent_selection.test.cpp
---
