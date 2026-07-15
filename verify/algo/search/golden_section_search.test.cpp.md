---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/search/golden_section_search.hpp
    title: Golden Section Search
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
  bundledCode: "#line 1 \"verify/algo/search/golden_section_search.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n#include\
    \ <cmath>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#include\
    \ <cstdint>\n#include <cstring>\n#include <iterator>\n#include <string>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace utilities\
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
    \ m1une\n\n\n#line 6 \"verify/algo/search/golden_section_search.test.cpp\"\n#include\
    \ <random>\n#include <vector>\n\n#line 1 \"algo/search/golden_section_search.hpp\"\
    \n\n\n\n#line 5 \"algo/search/golden_section_search.hpp\"\n#include <concepts>\n\
    #include <numeric>\n#line 10 \"algo/search/golden_section_search.hpp\"\n\nnamespace\
    \ m1une {\nnamespace algo {\n\nnamespace detail {\n\ntemplate <std::integral Int,\
    \ class F, class Compare>\nInt integer_golden_section_search(Int left, Int right,\
    \ F f, Compare comp) {\n    assert(left < right);\n\n    using UInt = std::make_unsigned_t<Int>;\n\
    \    using Uint128 = unsigned __int128;\n    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right)\
    \ - static_cast<UInt>(left));\n\n    auto add_offset = [left](Uint128 offset)\
    \ -> Int {\n        if constexpr (std::signed_integral<Int>) {\n            if\
    \ (left < 0) {\n                const Uint128 negative_count = static_cast<Uint128>(-(left\
    \ + 1)) + 1;\n                if (offset < negative_count) {\n               \
    \     return static_cast<Int>(left + static_cast<Int>(offset));\n            \
    \    }\n                return static_cast<Int>(offset - negative_count);\n  \
    \          }\n        }\n        return static_cast<Int>(left + static_cast<Int>(offset));\n\
    \    };\n\n    using Value = std::decay_t<decltype(f(left))>;\n    struct Evaluated\
    \ {\n        Uint128 pos;\n        const Value* value;\n    };\n\n    Uint128\
    \ fib0 = 1;\n    Uint128 fib1 = 1;\n    Uint128 fib2 = 2;\n    int k = 2;\n  \
    \  while (fib2 < n) {\n        fib0 = fib1;\n        fib1 = fib2;\n        fib2\
    \ = fib0 + fib1;\n        ++k;\n    }\n\n    std::vector<std::pair<Uint128, Value>>\
    \ cache;\n    cache.reserve(static_cast<unsigned>(k) + 4);\n\n    auto find_cached\
    \ = [&](Uint128 pos) -> const Value* {\n        for (const auto& [cached_pos,\
    \ value] : cache) {\n            if (cached_pos == pos) return &value;\n     \
    \   }\n        return nullptr;\n    };\n\n    auto advance_fibonacci = [&]() {\n\
    \        const Uint128 old0 = fib0;\n        const Uint128 old1 = fib1;\n    \
    \    fib0 = old1 - old0;\n        fib1 = old0;\n        fib2 = old1;\n       \
    \ --k;\n    };\n\n    auto eval = [&](Uint128 pos) -> Evaluated {\n        if\
    \ (pos >= n) return Evaluated{pos, nullptr};\n        if (const Value* value =\
    \ find_cached(pos)) return Evaluated{pos, value};\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return Evaluated{pos, &cache.back().second};\n\
    \    };\n\n    auto get_value = [&](Uint128 pos) -> const Value& {\n        if\
    \ (const Value* value = find_cached(pos)) return *value;\n        cache.emplace_back(pos,\
    \ f(add_offset(pos)));\n        return cache.back().second;\n    };\n\n    auto\
    \ scan = [&](Uint128 scan_left, Uint128 scan_right) -> Int {\n        Int best\
    \ = add_offset(scan_left);\n        const Value* best_value = &get_value(scan_left);\n\
    \        for (Uint128 pos = scan_left + 1; pos <= scan_right; ++pos) {\n     \
    \       Int x = add_offset(pos);\n            const Value& value = get_value(pos);\n\
    \            if (comp(value, *best_value)) {\n                best = x;\n    \
    \            best_value = &value;\n            }\n        }\n        return best;\n\
    \    };\n\n    if (n <= 3) return scan(0, n - 1);\n\n    auto better = [&](const\
    \ Evaluated& a, const Evaluated& b) -> bool {\n        if ((a.value != nullptr)\
    \ != (b.value != nullptr)) return a.value != nullptr;\n        if (a.value ==\
    \ nullptr) return false;\n        return comp(*a.value, *b.value);\n    };\n\n\
    \    Uint128 left_pos = 0;\n    Uint128 right_pos = fib2 - 1;\n    Uint128 x1\
    \ = left_pos + fib0 - 1;\n    Uint128 x2 = left_pos + fib1 - 1;\n    Evaluated\
    \ y1 = eval(x1);\n    Evaluated y2 = eval(x2);\n\n    while (k > 2) {\n      \
    \  if (better(y2, y1)) {\n            left_pos = x1 + 1;\n            x1 = x2;\n\
    \            y1 = y2;\n            advance_fibonacci();\n            if (k ==\
    \ 2) break;\n            x2 = left_pos + fib1 - 1;\n            y2 = eval(x2);\n\
    \        } else {\n            right_pos = x2;\n            x2 = x1;\n       \
    \     y2 = y1;\n            advance_fibonacci();\n            if (k == 2) break;\n\
    \            x1 = left_pos + fib0 - 1;\n            y1 = eval(x1);\n        }\n\
    \    }\n\n    const Uint128 last_valid = n - 1;\n    if (right_pos > last_valid)\
    \ right_pos = last_valid;\n    assert(left_pos <= right_pos);\n    return scan(left_pos,\
    \ right_pos);\n}\n\n}  // namespace detail\n\ntemplate <std::integral Int, class\
    \ F>\nInt golden_section_search_argmin(Int left, Int right, F f) {\n    return\
    \ detail::integer_golden_section_search(left, right, f, [](const auto& a, const\
    \ auto& b) { return a < b; });\n}\n\ntemplate <std::integral Int, class F>\nInt\
    \ golden_section_search_argmax(Int left, Int right, F f) {\n    return detail::integer_golden_section_search(left,\
    \ right, f, [](const auto& a, const auto& b) { return b < a; });\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmin(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y2 < y1) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y2 < y1) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\ntemplate\
    \ <class F>\ndouble golden_section_search_argmax(double left, double right, F\
    \ f, int iterations = 100) {\n    assert(left <= right);\n    assert(0 <= iterations);\n\
    \    if (left == right || iterations == 0) return std::midpoint(left, right);\n\
    \n    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;\n\
    \    double x1 = right - (right - left) * inv_phi;\n    double x2 = left + (right\
    \ - left) * inv_phi;\n    auto y1 = f(x1);\n    auto y2 = f(x2);\n\n    for (int\
    \ i = 1; i < iterations; ++i) {\n        if (y1 < y2) {\n            left = x1;\n\
    \            x1 = x2;\n            y1 = std::move(y2);\n            x2 = left\
    \ + (right - left) * inv_phi;\n            y2 = f(x2);\n        } else {\n   \
    \         right = x2;\n            x2 = x1;\n            y2 = std::move(y1);\n\
    \            x1 = right - (right - left) * inv_phi;\n            y1 = f(x1);\n\
    \        }\n    }\n\n    if (y1 < y2) {\n        left = x1;\n    } else {\n  \
    \      right = x2;\n    }\n    return std::midpoint(left, right);\n}\n\n}  //\
    \ namespace algo\n}  // namespace m1une\n\n\n#line 10 \"verify/algo/search/golden_section_search.test.cpp\"\
    \n\ntemplate <class F>\nint naive_argmin(int left, int right, F f) {\n    int\
    \ best = left;\n    auto best_value = f(best);\n    for (int x = left + 1; x <\
    \ right; ++x) {\n        auto value = f(x);\n        if (value < best_value) {\n\
    \            best = x;\n            best_value = value;\n        }\n    }\n  \
    \  return best;\n}\n\ntemplate <class F>\nint naive_argmax(int left, int right,\
    \ F f) {\n    int best = left;\n    auto best_value = f(best);\n    for (int x\
    \ = left + 1; x < right; ++x) {\n        auto value = f(x);\n        if (best_value\
    \ < value) {\n            best = x;\n            best_value = value;\n       \
    \ }\n    }\n    return best;\n}\n\nvoid test_integer_argmin() {\n    auto convex\
    \ = [](long long x) {\n        return (x - 7) * (x - 7) + 3;\n    };\n    assert(m1une::algo::golden_section_search_argmin<long\
    \ long>(-100, 101, convex) == 7);\n\n    auto plateau = [](int x) {\n        if\
    \ (x < 3) return 3 - x;\n        if (5 < x) return x - 5;\n        return 0;\n\
    \    };\n    assert(m1une::algo::golden_section_search_argmin<int>(-10, 10, plateau)\
    \ == 3);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n   \
    \ assert(m1une::algo::golden_section_search_argmin<int>(-7, 9, increasing) ==\
    \ -7);\n}\n\nvoid test_integer_argmax() {\n    auto concave = [](int x) {\n  \
    \      return -(x + 2) * (x + 2) + 10;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-20,\
    \ 20, concave) == -2);\n\n    auto plateau = [](int x) {\n        if (x < -4)\
    \ return x + 4;\n        if (1 < x) return 1 - x;\n        return 0;\n    };\n\
    \    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, plateau) ==\
    \ -4);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-7,\
    \ 9, increasing) == 8);\n}\n\nvoid test_random_integer_arrays() {\n    std::mt19937_64\
    \ rng(20260709);\n    for (int tc = 0; tc < 1000; ++tc) {\n        int n = static_cast<int>(rng()\
    \ % 200) + 1;\n        int low = static_cast<int>(rng() % n);\n        int high\
    \ = low + static_cast<int>(rng() % (n - low));\n\n        std::vector<long long>\
    \ min_values(n);\n        long long value = 0;\n        for (int i = low - 1;\
    \ i >= 0; --i) {\n            value += static_cast<long long>(rng() % 7) + 1;\n\
    \            min_values[i] = value;\n        }\n        value = 0;\n        for\
    \ (int i = high + 1; i < n; ++i) {\n            value += static_cast<long long>(rng()\
    \ % 7) + 1;\n            min_values[i] = value;\n        }\n\n        int base\
    \ = static_cast<int>(rng() % 1000) - 500;\n        auto min_f = [&](int x) {\n\
    \            return min_values[x - base];\n        };\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, min_f);\n        assert(xmin == naive_argmin(base, base + n, min_f));\n\
    \n        std::vector<long long> max_values(n);\n        for (int i = 0; i < n;\
    \ ++i) max_values[i] = -min_values[i];\n        auto max_f = [&](int x) {\n  \
    \          return max_values[x - base];\n        };\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, max_f);\n        assert(xmax == naive_argmax(base, base + n, max_f));\n\
    \    }\n}\n\nvoid test_integer_evaluation_reuse() {\n    for (int n = 1; n <=\
    \ 300; ++n) {\n        int base = -n / 2;\n        int center = base + n / 3;\n\
    \        auto value_at = [center](int x) {\n            return x < center ? center\
    \ - x : x - center;\n        };\n\n        std::vector<int> count(n);\n      \
    \  auto f = [&](int x) {\n            int index = x - base;\n            assert(count[index]\
    \ == 0);\n            ++count[index];\n            return value_at(x);\n     \
    \   };\n\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, f);\n        assert(xmin == naive_argmin(base, base + n, value_at));\n\
    \n        std::fill(count.begin(), count.end(), 0);\n        auto g = [&](int\
    \ x) {\n            int index = x - base;\n            assert(count[index] ==\
    \ 0);\n            ++count[index];\n            return -value_at(x);\n       \
    \ };\n        auto max_value_at = [&](int x) {\n            return -value_at(x);\n\
    \        };\n\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, g);\n        assert(xmax == naive_argmax(base, base + n, max_value_at));\n\
    \    }\n}\n\nvoid test_real_argmin() {\n    auto convex = [](double x) {\n   \
    \     return (x - 2.75) * (x - 2.75);\n    };\n    double x = m1une::algo::golden_section_search_argmin(-100.0,\
    \ 100.0, convex);\n    assert(std::abs(x - 2.75) < 1e-9);\n\n    auto increasing\
    \ = [](double x) {\n        return x;\n    };\n    double left = m1une::algo::golden_section_search_argmin(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(left + 3.0) < 1e-9);\n}\n\nvoid test_real_argmax()\
    \ {\n    auto concave = [](double x) {\n        return -(x + 0.5) * (x + 0.5);\n\
    \    };\n    double x = m1une::algo::golden_section_search_argmax(-100.0, 100.0,\
    \ concave);\n    assert(std::abs(x + 0.5) < 1e-9);\n\n    auto increasing = [](double\
    \ x) {\n        return x;\n    };\n    double right = m1une::algo::golden_section_search_argmax(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(right - 8.0) < 1e-9);\n}\n\nvoid test_evaluation_count()\
    \ {\n    int zero_iteration_calls = 0;\n    auto f0 = [&](double x) {\n      \
    \  ++zero_iteration_calls;\n        return x * x;\n    };\n    double midpoint\
    \ = m1une::algo::golden_section_search_argmin(-2.0, 4.0, f0, 0);\n    assert(midpoint\
    \ == 1.0);\n    assert(zero_iteration_calls == 0);\n\n    int calls = 0;\n   \
    \ auto f = [&](double x) {\n        ++calls;\n        return (x - 1.0) * (x -\
    \ 1.0);\n    };\n    m1une::algo::golden_section_search_argmin(-5.0, 5.0, f, 37);\n\
    \    assert(calls == 38);\n}\n\nvoid test_random_quadratics() {\n    std::mt19937_64\
    \ rng(20260708);\n    std::uniform_real_distribution<double> center_dist(-1000.0,\
    \ 1000.0);\n    std::uniform_real_distribution<double> width_dist(0.1, 1000.0);\n\
    \    std::uniform_real_distribution<double> coef_dist(0.1, 10.0);\n\n    for (int\
    \ tc = 0; tc < 1000; ++tc) {\n        double center = center_dist(rng);\n    \
    \    double left_width = width_dist(rng);\n        double right_width = width_dist(rng);\n\
    \        double coef = coef_dist(rng);\n        double left = center - left_width;\n\
    \        double right = center + right_width;\n\n        auto convex = [=](double\
    \ x) {\n            double dx = x - center;\n            return coef * dx * dx;\n\
    \        };\n        double expected_min = center;\n        double xmin = m1une::algo::golden_section_search_argmin(left,\
    \ right, convex, 120);\n        assert(std::abs(xmin - expected_min) < 1e-8);\n\
    \n        auto concave = [=](double x) {\n            double dx = x - center;\n\
    \            return -coef * dx * dx;\n        };\n        double expected_max\
    \ = center;\n        double xmax = m1une::algo::golden_section_search_argmax(left,\
    \ right, concave, 120);\n        assert(std::abs(xmax - expected_max) < 1e-8);\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_integer_argmin();\n    test_integer_argmax();\n   \
    \ test_random_integer_arrays();\n    test_integer_evaluation_reuse();\n    test_real_argmin();\n\
    \    test_real_argmax();\n    test_evaluation_count();\n    test_random_quadratics();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cmath>\n#include \"../../../utilities/fast_io.hpp\"\n#include <random>\n\
    #include <vector>\n\n#include \"../../../algo/search/golden_section_search.hpp\"\
    \n\ntemplate <class F>\nint naive_argmin(int left, int right, F f) {\n    int\
    \ best = left;\n    auto best_value = f(best);\n    for (int x = left + 1; x <\
    \ right; ++x) {\n        auto value = f(x);\n        if (value < best_value) {\n\
    \            best = x;\n            best_value = value;\n        }\n    }\n  \
    \  return best;\n}\n\ntemplate <class F>\nint naive_argmax(int left, int right,\
    \ F f) {\n    int best = left;\n    auto best_value = f(best);\n    for (int x\
    \ = left + 1; x < right; ++x) {\n        auto value = f(x);\n        if (best_value\
    \ < value) {\n            best = x;\n            best_value = value;\n       \
    \ }\n    }\n    return best;\n}\n\nvoid test_integer_argmin() {\n    auto convex\
    \ = [](long long x) {\n        return (x - 7) * (x - 7) + 3;\n    };\n    assert(m1une::algo::golden_section_search_argmin<long\
    \ long>(-100, 101, convex) == 7);\n\n    auto plateau = [](int x) {\n        if\
    \ (x < 3) return 3 - x;\n        if (5 < x) return x - 5;\n        return 0;\n\
    \    };\n    assert(m1une::algo::golden_section_search_argmin<int>(-10, 10, plateau)\
    \ == 3);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n   \
    \ assert(m1une::algo::golden_section_search_argmin<int>(-7, 9, increasing) ==\
    \ -7);\n}\n\nvoid test_integer_argmax() {\n    auto concave = [](int x) {\n  \
    \      return -(x + 2) * (x + 2) + 10;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-20,\
    \ 20, concave) == -2);\n\n    auto plateau = [](int x) {\n        if (x < -4)\
    \ return x + 4;\n        if (1 < x) return 1 - x;\n        return 0;\n    };\n\
    \    assert(m1une::algo::golden_section_search_argmax<int>(-20, 20, plateau) ==\
    \ -4);\n\n    auto increasing = [](int x) {\n        return x;\n    };\n    assert(m1une::algo::golden_section_search_argmax<int>(-7,\
    \ 9, increasing) == 8);\n}\n\nvoid test_random_integer_arrays() {\n    std::mt19937_64\
    \ rng(20260709);\n    for (int tc = 0; tc < 1000; ++tc) {\n        int n = static_cast<int>(rng()\
    \ % 200) + 1;\n        int low = static_cast<int>(rng() % n);\n        int high\
    \ = low + static_cast<int>(rng() % (n - low));\n\n        std::vector<long long>\
    \ min_values(n);\n        long long value = 0;\n        for (int i = low - 1;\
    \ i >= 0; --i) {\n            value += static_cast<long long>(rng() % 7) + 1;\n\
    \            min_values[i] = value;\n        }\n        value = 0;\n        for\
    \ (int i = high + 1; i < n; ++i) {\n            value += static_cast<long long>(rng()\
    \ % 7) + 1;\n            min_values[i] = value;\n        }\n\n        int base\
    \ = static_cast<int>(rng() % 1000) - 500;\n        auto min_f = [&](int x) {\n\
    \            return min_values[x - base];\n        };\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, min_f);\n        assert(xmin == naive_argmin(base, base + n, min_f));\n\
    \n        std::vector<long long> max_values(n);\n        for (int i = 0; i < n;\
    \ ++i) max_values[i] = -min_values[i];\n        auto max_f = [&](int x) {\n  \
    \          return max_values[x - base];\n        };\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, max_f);\n        assert(xmax == naive_argmax(base, base + n, max_f));\n\
    \    }\n}\n\nvoid test_integer_evaluation_reuse() {\n    for (int n = 1; n <=\
    \ 300; ++n) {\n        int base = -n / 2;\n        int center = base + n / 3;\n\
    \        auto value_at = [center](int x) {\n            return x < center ? center\
    \ - x : x - center;\n        };\n\n        std::vector<int> count(n);\n      \
    \  auto f = [&](int x) {\n            int index = x - base;\n            assert(count[index]\
    \ == 0);\n            ++count[index];\n            return value_at(x);\n     \
    \   };\n\n        int xmin = m1une::algo::golden_section_search_argmin<int>(base,\
    \ base + n, f);\n        assert(xmin == naive_argmin(base, base + n, value_at));\n\
    \n        std::fill(count.begin(), count.end(), 0);\n        auto g = [&](int\
    \ x) {\n            int index = x - base;\n            assert(count[index] ==\
    \ 0);\n            ++count[index];\n            return -value_at(x);\n       \
    \ };\n        auto max_value_at = [&](int x) {\n            return -value_at(x);\n\
    \        };\n\n        int xmax = m1une::algo::golden_section_search_argmax<int>(base,\
    \ base + n, g);\n        assert(xmax == naive_argmax(base, base + n, max_value_at));\n\
    \    }\n}\n\nvoid test_real_argmin() {\n    auto convex = [](double x) {\n   \
    \     return (x - 2.75) * (x - 2.75);\n    };\n    double x = m1une::algo::golden_section_search_argmin(-100.0,\
    \ 100.0, convex);\n    assert(std::abs(x - 2.75) < 1e-9);\n\n    auto increasing\
    \ = [](double x) {\n        return x;\n    };\n    double left = m1une::algo::golden_section_search_argmin(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(left + 3.0) < 1e-9);\n}\n\nvoid test_real_argmax()\
    \ {\n    auto concave = [](double x) {\n        return -(x + 0.5) * (x + 0.5);\n\
    \    };\n    double x = m1une::algo::golden_section_search_argmax(-100.0, 100.0,\
    \ concave);\n    assert(std::abs(x + 0.5) < 1e-9);\n\n    auto increasing = [](double\
    \ x) {\n        return x;\n    };\n    double right = m1une::algo::golden_section_search_argmax(-3.0,\
    \ 8.0, increasing);\n    assert(std::abs(right - 8.0) < 1e-9);\n}\n\nvoid test_evaluation_count()\
    \ {\n    int zero_iteration_calls = 0;\n    auto f0 = [&](double x) {\n      \
    \  ++zero_iteration_calls;\n        return x * x;\n    };\n    double midpoint\
    \ = m1une::algo::golden_section_search_argmin(-2.0, 4.0, f0, 0);\n    assert(midpoint\
    \ == 1.0);\n    assert(zero_iteration_calls == 0);\n\n    int calls = 0;\n   \
    \ auto f = [&](double x) {\n        ++calls;\n        return (x - 1.0) * (x -\
    \ 1.0);\n    };\n    m1une::algo::golden_section_search_argmin(-5.0, 5.0, f, 37);\n\
    \    assert(calls == 38);\n}\n\nvoid test_random_quadratics() {\n    std::mt19937_64\
    \ rng(20260708);\n    std::uniform_real_distribution<double> center_dist(-1000.0,\
    \ 1000.0);\n    std::uniform_real_distribution<double> width_dist(0.1, 1000.0);\n\
    \    std::uniform_real_distribution<double> coef_dist(0.1, 10.0);\n\n    for (int\
    \ tc = 0; tc < 1000; ++tc) {\n        double center = center_dist(rng);\n    \
    \    double left_width = width_dist(rng);\n        double right_width = width_dist(rng);\n\
    \        double coef = coef_dist(rng);\n        double left = center - left_width;\n\
    \        double right = center + right_width;\n\n        auto convex = [=](double\
    \ x) {\n            double dx = x - center;\n            return coef * dx * dx;\n\
    \        };\n        double expected_min = center;\n        double xmin = m1une::algo::golden_section_search_argmin(left,\
    \ right, convex, 120);\n        assert(std::abs(xmin - expected_min) < 1e-8);\n\
    \n        auto concave = [=](double x) {\n            double dx = x - center;\n\
    \            return -coef * dx * dx;\n        };\n        double expected_max\
    \ = center;\n        double xmax = m1une::algo::golden_section_search_argmax(left,\
    \ right, concave, 120);\n        assert(std::abs(xmax - expected_max) < 1e-8);\n\
    \    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    test_integer_argmin();\n    test_integer_argmax();\n   \
    \ test_random_integer_arrays();\n    test_integer_evaluation_reuse();\n    test_real_argmin();\n\
    \    test_real_argmax();\n    test_evaluation_count();\n    test_random_quadratics();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - algo/search/golden_section_search.hpp
  isVerificationFile: true
  path: verify/algo/search/golden_section_search.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/search/golden_section_search.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/search/golden_section_search.test.cpp
- /verify/verify/algo/search/golden_section_search.test.cpp.html
title: verify/algo/search/golden_section_search.test.cpp
---
