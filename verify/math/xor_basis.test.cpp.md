---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/xor_basis.hpp
    title: XOR Basis
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
  bundledCode: "#line 1 \"verify/math/xor_basis.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"math/xor_basis.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <concepts>\n#include <initializer_list>\n#include <iterator>\n#include\
    \ <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <std::unsigned_integral UInt = unsigned long long>\nclass XorBasis {\n    static_assert(!std::same_as<UInt,\
    \ bool>);\n\npublic:\n    static constexpr int bit_width = std::numeric_limits<UInt>::digits;\n\
    \n    XorBasis() = default;\n\n    template <std::input_iterator Iterator, std::sentinel_for<Iterator>\
    \ Sentinel>\n        requires std::convertible_to<std::iter_reference_t<Iterator>,\
    \ UInt>\n    XorBasis(Iterator first, Sentinel last) {\n        for (; first !=\
    \ last; ++first) insert(UInt(*first));\n    }\n\n    XorBasis(std::initializer_list<UInt>\
    \ values)\n        : XorBasis(values.begin(), values.end()) {}\n\n    bool insert(UInt\
    \ value) {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n       \
    \     if (((value >> bit) & UInt(1)) == 0) continue;\n            if (basis_[bit]\
    \ != 0) {\n                value ^= basis_[bit];\n                continue;\n\
    \            }\n\n            for (int lower = bit - 1; lower >= 0; lower--) {\n\
    \                if (((value >> lower) & UInt(1)) != 0) value ^= basis_[lower];\n\
    \            }\n            basis_[bit] = value;\n            rank_++;\n     \
    \       for (int higher = bit + 1; higher < bit_width; higher++) {\n         \
    \       if (((basis_[higher] >> bit) & UInt(1)) != 0) {\n                    basis_[higher]\
    \ ^= value;\n                }\n            }\n            return true;\n    \
    \    }\n        return false;\n    }\n\n    bool contains(UInt value) const {\n\
    \        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if (((value\
    \ >> bit) & UInt(1)) != 0) value ^= basis_[bit];\n        }\n        return value\
    \ == 0;\n    }\n\n    int rank() const {\n        return rank_;\n    }\n\n   \
    \ bool empty() const {\n        return rank_ == 0;\n    }\n\n    void clear()\
    \ {\n        basis_.fill(UInt(0));\n        rank_ = 0;\n    }\n\n    int merge(const\
    \ XorBasis& other) {\n        const int old_rank = rank_;\n        for (UInt value\
    \ : other.basis_) {\n            if (value != 0) insert(value);\n        }\n \
    \       return rank_ - old_rank;\n    }\n\n    UInt min_xor(UInt value = 0) const\
    \ {\n        for (int bit = bit_width - 1; bit >= 0; bit--) {\n            if\
    \ ((value ^ basis_[bit]) < value) value ^= basis_[bit];\n        }\n        return\
    \ value;\n    }\n\n    UInt max_xor(UInt value = 0) const {\n        for (int\
    \ bit = bit_width - 1; bit >= 0; bit--) {\n            if (value < (value ^ basis_[bit]))\
    \ value ^= basis_[bit];\n        }\n        return value;\n    }\n\n    UInt kth_smallest(UInt\
    \ index) const {\n        if (rank_ < bit_width) assert(index < (UInt(1) << rank_));\n\
    \        UInt result = 0;\n        int coefficient = 0;\n        for (int bit\
    \ = 0; bit < bit_width; bit++) {\n            if (basis_[bit] == 0) continue;\n\
    \            if (((index >> coefficient) & UInt(1)) != 0) result ^= basis_[bit];\n\
    \            coefficient++;\n        }\n        return result;\n    }\n\n    std::vector<UInt>\
    \ vectors() const {\n        std::vector<UInt> result;\n        result.reserve(rank_);\n\
    \        for (UInt value : basis_) {\n            if (value != 0) result.push_back(value);\n\
    \        }\n        return result;\n    }\n\nprivate:\n    std::array<UInt, bit_width>\
    \ basis_{};\n    int rank_ = 0;\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/math/xor_basis.test.cpp\"\n\n#include <algorithm>\n#line\
    \ 7 \"verify/math/xor_basis.test.cpp\"\n#include <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#line 12 \"utilities/fast_io.hpp\"\n#include <string>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
    \ {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class = void>\n\
    struct is_range : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T,\
    \ std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ m1une\n\n\n#line 9 \"verify/math/xor_basis.test.cpp\"\n#include <random>\n#line\
    \ 11 \"verify/math/xor_basis.test.cpp\"\n\nnamespace {\n\nusing Basis = m1une::math::XorBasis<uint64_t>;\n\
    \nstd::vector<uint64_t> enumerate(const std::vector<uint64_t>& values) {\n   \
    \ std::vector<uint64_t> result;\n    result.reserve(std::size_t(1) << values.size());\n\
    \    for (uint64_t mask = 0; mask < (uint64_t(1) << values.size()); mask++) {\n\
    \        uint64_t value = 0;\n        for (int i = 0; i < int(values.size());\
    \ i++) {\n            if (((mask >> i) & 1) != 0) value ^= values[i];\n      \
    \  }\n        result.push_back(value);\n    }\n    std::sort(result.begin(), result.end());\n\
    \    result.erase(std::unique(result.begin(), result.end()), result.end());\n\
    \    return result;\n}\n\nvoid test_basic() {\n    Basis basis{3, 5, 6, 0};\n\
    \    assert(basis.rank() == 2);\n    assert(!basis.empty());\n    assert(basis.contains(0));\n\
    \    assert(basis.contains(3));\n    assert(basis.contains(5));\n    assert(basis.contains(6));\n\
    \    assert(!basis.contains(1));\n    assert(!basis.insert(6));\n    assert(basis.min_xor(4)\
    \ == 1);\n    assert(basis.max_xor() == 6);\n    assert(basis.max_xor(8) == 14);\n\
    \n    const std::vector<uint64_t> expected{0, 3, 5, 6};\n    for (uint64_t i =\
    \ 0; i < expected.size(); i++) {\n        assert(basis.kth_smallest(i) == expected[i]);\n\
    \    }\n\n    Basis other{1, 8, 9};\n    assert(basis.merge(other) == 2);\n  \
    \  assert(basis.rank() == 4);\n    assert(basis.contains(15));\n    basis.clear();\n\
    \    assert(basis.empty());\n    assert(basis.vectors().empty());\n}\n\nvoid test_randomized()\
    \ {\n    std::mt19937_64 random(123456789);\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        const int size = int(random() % 11);\n        std::vector<uint64_t>\
    \ values(size);\n        for (uint64_t& value : values) value = random() & 1023;\n\
    \n        Basis basis(values.begin(), values.end());\n        const std::vector<uint64_t>\
    \ span = enumerate(values);\n        assert(span.size() == (std::size_t(1) <<\
    \ basis.rank()));\n        assert(int(basis.vectors().size()) == basis.rank());\n\
    \n        for (uint64_t value = 0; value < 1024; value++) {\n            const\
    \ bool expected = std::binary_search(span.begin(), span.end(), value);\n     \
    \       assert(basis.contains(value) == expected);\n        }\n        for (std::size_t\
    \ i = 0; i < span.size(); i++) {\n            assert(basis.kth_smallest(i) ==\
    \ span[i]);\n        }\n\n        for (int query = 0; query < 20; query++) {\n\
    \            const uint64_t seed = random() & 2047;\n            uint64_t expected_min\
    \ = ~uint64_t(0);\n            uint64_t expected_max = 0;\n            for (uint64_t\
    \ value : span) {\n                expected_min = std::min(expected_min, seed\
    \ ^ value);\n                expected_max = std::max(expected_max, seed ^ value);\n\
    \            }\n            assert(basis.min_xor(seed) == expected_min);\n   \
    \         assert(basis.max_xor(seed) == expected_max);\n        }\n    }\n}\n\n\
    void test_full_rank() {\n    m1une::math::XorBasis<uint8_t> basis;\n    for (int\
    \ bit = 0; bit < 8; bit++) basis.insert(uint8_t(1U << bit));\n    assert(basis.rank()\
    \ == 8);\n    for (int value = 0; value < 256; value++) {\n        assert(basis.kth_smallest(uint8_t(value))\
    \ == uint8_t(value));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_basic();\n\
    \    test_randomized();\n    test_full_rank();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../math/xor_basis.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <random>\n#include\
    \ <vector>\n\nnamespace {\n\nusing Basis = m1une::math::XorBasis<uint64_t>;\n\n\
    std::vector<uint64_t> enumerate(const std::vector<uint64_t>& values) {\n    std::vector<uint64_t>\
    \ result;\n    result.reserve(std::size_t(1) << values.size());\n    for (uint64_t\
    \ mask = 0; mask < (uint64_t(1) << values.size()); mask++) {\n        uint64_t\
    \ value = 0;\n        for (int i = 0; i < int(values.size()); i++) {\n       \
    \     if (((mask >> i) & 1) != 0) value ^= values[i];\n        }\n        result.push_back(value);\n\
    \    }\n    std::sort(result.begin(), result.end());\n    result.erase(std::unique(result.begin(),\
    \ result.end()), result.end());\n    return result;\n}\n\nvoid test_basic() {\n\
    \    Basis basis{3, 5, 6, 0};\n    assert(basis.rank() == 2);\n    assert(!basis.empty());\n\
    \    assert(basis.contains(0));\n    assert(basis.contains(3));\n    assert(basis.contains(5));\n\
    \    assert(basis.contains(6));\n    assert(!basis.contains(1));\n    assert(!basis.insert(6));\n\
    \    assert(basis.min_xor(4) == 1);\n    assert(basis.max_xor() == 6);\n    assert(basis.max_xor(8)\
    \ == 14);\n\n    const std::vector<uint64_t> expected{0, 3, 5, 6};\n    for (uint64_t\
    \ i = 0; i < expected.size(); i++) {\n        assert(basis.kth_smallest(i) ==\
    \ expected[i]);\n    }\n\n    Basis other{1, 8, 9};\n    assert(basis.merge(other)\
    \ == 2);\n    assert(basis.rank() == 4);\n    assert(basis.contains(15));\n  \
    \  basis.clear();\n    assert(basis.empty());\n    assert(basis.vectors().empty());\n\
    }\n\nvoid test_randomized() {\n    std::mt19937_64 random(123456789);\n    for\
    \ (int trial = 0; trial < 2000; trial++) {\n        const int size = int(random()\
    \ % 11);\n        std::vector<uint64_t> values(size);\n        for (uint64_t&\
    \ value : values) value = random() & 1023;\n\n        Basis basis(values.begin(),\
    \ values.end());\n        const std::vector<uint64_t> span = enumerate(values);\n\
    \        assert(span.size() == (std::size_t(1) << basis.rank()));\n        assert(int(basis.vectors().size())\
    \ == basis.rank());\n\n        for (uint64_t value = 0; value < 1024; value++)\
    \ {\n            const bool expected = std::binary_search(span.begin(), span.end(),\
    \ value);\n            assert(basis.contains(value) == expected);\n        }\n\
    \        for (std::size_t i = 0; i < span.size(); i++) {\n            assert(basis.kth_smallest(i)\
    \ == span[i]);\n        }\n\n        for (int query = 0; query < 20; query++)\
    \ {\n            const uint64_t seed = random() & 2047;\n            uint64_t\
    \ expected_min = ~uint64_t(0);\n            uint64_t expected_max = 0;\n     \
    \       for (uint64_t value : span) {\n                expected_min = std::min(expected_min,\
    \ seed ^ value);\n                expected_max = std::max(expected_max, seed ^\
    \ value);\n            }\n            assert(basis.min_xor(seed) == expected_min);\n\
    \            assert(basis.max_xor(seed) == expected_max);\n        }\n    }\n\
    }\n\nvoid test_full_rank() {\n    m1une::math::XorBasis<uint8_t> basis;\n    for\
    \ (int bit = 0; bit < 8; bit++) basis.insert(uint8_t(1U << bit));\n    assert(basis.rank()\
    \ == 8);\n    for (int value = 0; value < 256; value++) {\n        assert(basis.kth_smallest(uint8_t(value))\
    \ == uint8_t(value));\n    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_basic();\n\
    \    test_randomized();\n    test_full_rank();\n\n    long long a, b;\n    fast_input\
    \ >> a >> b;\n    fast_output << a + b << '\\n';\n}\n"
  dependsOn:
  - math/xor_basis.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/xor_basis.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/xor_basis.test.cpp
layout: document
redirect_from:
- /verify/verify/math/xor_basis.test.cpp
- /verify/verify/math/xor_basis.test.cpp.html
title: verify/math/xor_basis.test.cpp
---
