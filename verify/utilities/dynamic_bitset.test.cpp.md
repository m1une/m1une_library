---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/dynamic_bitset.hpp
    title: Dynamic Bitset
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
  bundledCode: "#line 1 \"verify/utilities/dynamic_bitset.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
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
    \ m1une\n\n\n#line 6 \"verify/utilities/dynamic_bitset.test.cpp\"\n#include <random>\n\
    #include <vector>\n\n#line 1 \"utilities/dynamic_bitset.hpp\"\n\n\n\n#line 9 \"\
    utilities/dynamic_bitset.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\n\
    struct DynamicBitset {\n   private:\n    static constexpr int BITS_PER_BLOCK =\
    \ 64;\n    static constexpr uint64_t FULL_BLOCK = ~uint64_t{0};\n\n    int _n;\n\
    \    std::vector<uint64_t> blocks;\n\n    static int block_count(int n) {\n  \
    \      assert(n >= 0);\n        return (n + BITS_PER_BLOCK - 1) >> 6;\n    }\n\
    \n    uint64_t tail_mask() const {\n        const int rem = _n & (BITS_PER_BLOCK\
    \ - 1);\n        return rem == 0 ? FULL_BLOCK : ((uint64_t{1} << rem) - 1);\n\
    \    }\n\n    // Keep unused bits in the last block equal to zero.\n    void clean()\
    \ {\n        if (!blocks.empty()) blocks.back() &= tail_mask();\n    }\n\n   public:\n\
    \    DynamicBitset() : _n(0), blocks() {}\n\n    explicit DynamicBitset(int n,\
    \ bool val = false) : _n(n), blocks(block_count(n), val ? FULL_BLOCK : 0) {\n\
    \        if (val) clean();\n    }\n\n    // Returns the logical number of bits.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ bit at index i is set.\n    bool test(int i) const {\n        assert(0 <= i\
    \ && i < _n);\n        return (blocks[i >> 6] >> (i & (BITS_PER_BLOCK - 1))) &\
    \ 1;\n    }\n\n    // Sets the bit at index i to true.\n    void set(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] |= uint64_t{1} << (i\
    \ & (BITS_PER_BLOCK - 1));\n    }\n\n    // Sets all bits to true.\n    void set()\
    \ {\n        std::fill(blocks.begin(), blocks.end(), FULL_BLOCK);\n        clean();\n\
    \    }\n\n    // Sets the bit at index i to false.\n    void reset(int i) {\n\
    \        assert(0 <= i && i < _n);\n        blocks[i >> 6] &= ~(uint64_t{1} <<\
    \ (i & (BITS_PER_BLOCK - 1)));\n    }\n\n    // Sets all bits to false.\n    void\
    \ reset() {\n        std::fill(blocks.begin(), blocks.end(), uint64_t{0});\n \
    \   }\n\n    // Flips the bit at index i.\n    void flip(int i) {\n        assert(0\
    \ <= i && i < _n);\n        blocks[i >> 6] ^= uint64_t{1} << (i & (BITS_PER_BLOCK\
    \ - 1));\n    }\n\n    // Flips all bits.\n    void flip() {\n        for (uint64_t&\
    \ block : blocks) block = ~block;\n        clean();\n    }\n\n    // Returns the\
    \ number of set bits.\n    int popcount() const {\n        int res = 0;\n    \
    \    for (uint64_t block : blocks) res += __builtin_popcountll(block);\n     \
    \   return res;\n    }\n\n    // Returns the index of the least significant set\
    \ bit, or -1 if no bit is set.\n    int lowbit() const {\n        const int m\
    \ = static_cast<int>(blocks.size());\n        for (int i = 0; i < m; ++i) {\n\
    \            if (blocks[i] != 0) return (i << 6) + __builtin_ctzll(blocks[i]);\n\
    \        }\n        return -1;\n    }\n\n    // Returns the index of the most\
    \ significant set bit, or -1 if no bit is set.\n    int topbit() const {\n   \
    \     for (int i = static_cast<int>(blocks.size()) - 1; i >= 0; --i) {\n     \
    \       if (blocks[i] != 0) return (i << 6) + (BITS_PER_BLOCK - 1 - __builtin_clzll(blocks[i]));\n\
    \        }\n        return -1;\n    }\n\n    // Returns whether at least one bit\
    \ is set.\n    bool any() const {\n        for (uint64_t block : blocks) {\n \
    \           if (block != 0) return true;\n        }\n        return false;\n \
    \   }\n\n    // Returns whether every logical bit is set.\n    bool all() const\
    \ {\n        if (_n == 0) return true;\n\n        const int m = static_cast<int>(blocks.size());\n\
    \        for (int i = 0; i + 1 < m; ++i) {\n            if (blocks[i] != FULL_BLOCK)\
    \ return false;\n        }\n        return blocks.back() == tail_mask();\n   \
    \ }\n\n    // Returns whether no bit is set.\n    bool none() const {\n      \
    \  return !any();\n    }\n\n    DynamicBitset& operator&=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] &= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator|=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] |= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset& operator^=(const DynamicBitset&\
    \ other) {\n        assert(_n == other._n);\n        const std::size_t m = blocks.size();\n\
    \        for (std::size_t i = 0; i < m; ++i) blocks[i] ^= other.blocks[i];\n \
    \       return *this;\n    }\n\n    DynamicBitset operator~() const {\n      \
    \  DynamicBitset res = *this;\n        res.flip();\n        return res;\n    }\n\
    \n    friend DynamicBitset operator&(DynamicBitset lhs, const DynamicBitset& rhs)\
    \ {\n        lhs &= rhs;\n        return lhs;\n    }\n\n    friend DynamicBitset\
    \ operator|(DynamicBitset lhs, const DynamicBitset& rhs) {\n        lhs |= rhs;\n\
    \        return lhs;\n    }\n\n    friend DynamicBitset operator^(DynamicBitset\
    \ lhs, const DynamicBitset& rhs) {\n        lhs ^= rhs;\n        return lhs;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 10 \"\
    verify/utilities/dynamic_bitset.test.cpp\"\n\nusing m1une::utilities::DynamicBitset;\n\
    \nvoid verify_state(const DynamicBitset& bits, const std::vector<int>& model)\
    \ {\n    const int n = static_cast<int>(model.size());\n    assert(bits.size()\
    \ == n);\n\n    int count = 0;\n    int low = -1;\n    int top = -1;\n    for\
    \ (int i = 0; i < n; ++i) {\n        assert(bits.test(i) == static_cast<bool>(model[i]));\n\
    \        if (model[i]) {\n            ++count;\n            if (low == -1) low\
    \ = i;\n            top = i;\n        }\n    }\n\n    assert(bits.popcount() ==\
    \ count);\n    assert(bits.lowbit() == low);\n    assert(bits.topbit() == top);\n\
    \    assert(bits.any() == (count > 0));\n    assert(bits.none() == (count == 0));\n\
    \    assert(bits.all() == (count == n));\n}\n\nDynamicBitset make_bitset(const\
    \ std::vector<int>& model) {\n    DynamicBitset bits(static_cast<int>(model.size()));\n\
    \    for (int i = 0; i < static_cast<int>(model.size()); ++i) {\n        if (model[i])\
    \ bits.set(i);\n    }\n    return bits;\n}\n\nstd::vector<int> bitwise_and_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] & rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_or_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] | rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_xor_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] ^ rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_not_model(const\
    \ std::vector<int>& model) {\n    std::vector<int> res(model.size());\n    for\
    \ (int i = 0; i < static_cast<int>(model.size()); ++i) res[i] = model[i] ^ 1;\n\
    \    return res;\n}\n\nvoid test_constructors() {\n    const std::vector<int>\
    \ sizes = {0, 1, 2, 3, 31, 32, 33, 63, 64, 65, 66,\n                         \
    \           127, 128, 129, 130, 191, 192, 193, 257};\n\n    DynamicBitset empty;\n\
    \    verify_state(empty, std::vector<int>());\n\n    for (int n : sizes) {\n \
    \       DynamicBitset zero(n);\n        verify_state(zero, std::vector<int>(n,\
    \ 0));\n\n        DynamicBitset one(n, true);\n        verify_state(one, std::vector<int>(n,\
    \ 1));\n    }\n}\n\nvoid test_point_and_global_operations() {\n    const std::vector<int>\
    \ sizes = {0, 1, 5, 63, 64, 65, 129, 257};\n\n    for (int n : sizes) {\n    \
    \    DynamicBitset bits(n);\n        std::vector<int> model(n, 0);\n        verify_state(bits,\
    \ model);\n\n        bits.set();\n        std::fill(model.begin(), model.end(),\
    \ 1);\n        verify_state(bits, model);\n\n        bits.reset();\n        std::fill(model.begin(),\
    \ model.end(), 0);\n        verify_state(bits, model);\n\n        bits.flip();\n\
    \        for (int& x : model) x ^= 1;\n        verify_state(bits, model);\n\n\
    \        bits.flip();\n        for (int& x : model) x ^= 1;\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 3 == 0)\
    \ {\n                bits.set(i);\n                model[i] = 1;\n           \
    \ }\n        }\n        verify_state(bits, model);\n\n        for (int i = 0;\
    \ i < n; ++i) {\n            if (i % 5 == 0) {\n                bits.reset(i);\n\
    \                model[i] = 0;\n            }\n        }\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 7 == 0)\
    \ {\n                bits.flip(i);\n                model[i] ^= 1;\n         \
    \   }\n        }\n        verify_state(bits, model);\n    }\n}\n\nvoid test_bitwise_operations()\
    \ {\n    const std::vector<int> sizes = {0, 1, 2, 63, 64, 65, 100, 127, 128, 129,\
    \ 255};\n\n    for (int n : sizes) {\n        std::vector<int> lhs(n), rhs(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            lhs[i] = ((i * 37 + n) % 5)\
    \ < 2;\n            rhs[i] = ((i * 19 + n * 3) % 7) < 3;\n        }\n\n      \
    \  const DynamicBitset a = make_bitset(lhs);\n        const DynamicBitset b =\
    \ make_bitset(rhs);\n\n        verify_state(a & b, bitwise_and_model(lhs, rhs));\n\
    \        verify_state(a | b, bitwise_or_model(lhs, rhs));\n        verify_state(a\
    \ ^ b, bitwise_xor_model(lhs, rhs));\n        verify_state(~a, bitwise_not_model(lhs));\n\
    \n        DynamicBitset c = a;\n        c &= b;\n        verify_state(c, bitwise_and_model(lhs,\
    \ rhs));\n\n        c = a;\n        c |= b;\n        verify_state(c, bitwise_or_model(lhs,\
    \ rhs));\n\n        c = a;\n        c ^= b;\n        verify_state(c, bitwise_xor_model(lhs,\
    \ rhs));\n    }\n}\n\nvoid test_randomized() {\n    std::mt19937_64 rng(123456789);\n\
    \n    for (int trial = 0; trial < 200; ++trial) {\n        int n;\n        if\
    \ (trial < 130) {\n            n = trial;\n        } else {\n            n = static_cast<int>(rng()\
    \ % 600);\n        }\n\n        DynamicBitset bits(n, (rng() & 1) != 0);\n   \
    \     std::vector<int> model(n, bits.all() ? 1 : 0);\n        verify_state(bits,\
    \ model);\n\n        for (int step = 0; step < 400; ++step) {\n            const\
    \ int op = static_cast<int>(rng() % 10);\n            if (op == 0) {\n       \
    \         bits.set();\n                std::fill(model.begin(), model.end(), 1);\n\
    \            } else if (op == 1) {\n                bits.reset();\n          \
    \      std::fill(model.begin(), model.end(), 0);\n            } else if (op ==\
    \ 2) {\n                bits.flip();\n                for (int& x : model) x ^=\
    \ 1;\n            } else if (op <= 5) {\n                if (n == 0) continue;\n\
    \                const int i = static_cast<int>(rng() % n);\n                if\
    \ (op == 3) {\n                    bits.set(i);\n                    model[i]\
    \ = 1;\n                } else if (op == 4) {\n                    bits.reset(i);\n\
    \                    model[i] = 0;\n                } else {\n               \
    \     bits.flip(i);\n                    model[i] ^= 1;\n                }\n \
    \           } else {\n                std::vector<int> other_model(n);\n     \
    \           for (int i = 0; i < n; ++i) other_model[i] = (rng() % 3) == 0;\n \
    \               DynamicBitset other = make_bitset(other_model);\n\n          \
    \      if (op == 6) {\n                    bits &= other;\n                  \
    \  model = bitwise_and_model(model, other_model);\n                } else if (op\
    \ == 7) {\n                    bits |= other;\n                    model = bitwise_or_model(model,\
    \ other_model);\n                } else if (op == 8) {\n                    bits\
    \ ^= other;\n                    model = bitwise_xor_model(model, other_model);\n\
    \                } else {\n                    verify_state(bits & other, bitwise_and_model(model,\
    \ other_model));\n                    verify_state(bits | other, bitwise_or_model(model,\
    \ other_model));\n                    verify_state(bits ^ other, bitwise_xor_model(model,\
    \ other_model));\n                    verify_state(~bits, bitwise_not_model(model));\n\
    \                }\n            }\n            verify_state(bits, model);\n  \
    \      }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_constructors();\n \
    \   test_point_and_global_operations();\n    test_bitwise_operations();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../utilities/fast_io.hpp\"\n#include <random>\n\
    #include <vector>\n\n#include \"../../utilities/dynamic_bitset.hpp\"\n\nusing\
    \ m1une::utilities::DynamicBitset;\n\nvoid verify_state(const DynamicBitset& bits,\
    \ const std::vector<int>& model) {\n    const int n = static_cast<int>(model.size());\n\
    \    assert(bits.size() == n);\n\n    int count = 0;\n    int low = -1;\n    int\
    \ top = -1;\n    for (int i = 0; i < n; ++i) {\n        assert(bits.test(i) ==\
    \ static_cast<bool>(model[i]));\n        if (model[i]) {\n            ++count;\n\
    \            if (low == -1) low = i;\n            top = i;\n        }\n    }\n\
    \n    assert(bits.popcount() == count);\n    assert(bits.lowbit() == low);\n \
    \   assert(bits.topbit() == top);\n    assert(bits.any() == (count > 0));\n  \
    \  assert(bits.none() == (count == 0));\n    assert(bits.all() == (count == n));\n\
    }\n\nDynamicBitset make_bitset(const std::vector<int>& model) {\n    DynamicBitset\
    \ bits(static_cast<int>(model.size()));\n    for (int i = 0; i < static_cast<int>(model.size());\
    \ ++i) {\n        if (model[i]) bits.set(i);\n    }\n    return bits;\n}\n\nstd::vector<int>\
    \ bitwise_and_model(const std::vector<int>& lhs, const std::vector<int>& rhs)\
    \ {\n    std::vector<int> res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size());\
    \ ++i) res[i] = lhs[i] & rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_or_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] | rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_xor_model(const\
    \ std::vector<int>& lhs, const std::vector<int>& rhs) {\n    std::vector<int>\
    \ res(lhs.size());\n    for (int i = 0; i < static_cast<int>(lhs.size()); ++i)\
    \ res[i] = lhs[i] ^ rhs[i];\n    return res;\n}\n\nstd::vector<int> bitwise_not_model(const\
    \ std::vector<int>& model) {\n    std::vector<int> res(model.size());\n    for\
    \ (int i = 0; i < static_cast<int>(model.size()); ++i) res[i] = model[i] ^ 1;\n\
    \    return res;\n}\n\nvoid test_constructors() {\n    const std::vector<int>\
    \ sizes = {0, 1, 2, 3, 31, 32, 33, 63, 64, 65, 66,\n                         \
    \           127, 128, 129, 130, 191, 192, 193, 257};\n\n    DynamicBitset empty;\n\
    \    verify_state(empty, std::vector<int>());\n\n    for (int n : sizes) {\n \
    \       DynamicBitset zero(n);\n        verify_state(zero, std::vector<int>(n,\
    \ 0));\n\n        DynamicBitset one(n, true);\n        verify_state(one, std::vector<int>(n,\
    \ 1));\n    }\n}\n\nvoid test_point_and_global_operations() {\n    const std::vector<int>\
    \ sizes = {0, 1, 5, 63, 64, 65, 129, 257};\n\n    for (int n : sizes) {\n    \
    \    DynamicBitset bits(n);\n        std::vector<int> model(n, 0);\n        verify_state(bits,\
    \ model);\n\n        bits.set();\n        std::fill(model.begin(), model.end(),\
    \ 1);\n        verify_state(bits, model);\n\n        bits.reset();\n        std::fill(model.begin(),\
    \ model.end(), 0);\n        verify_state(bits, model);\n\n        bits.flip();\n\
    \        for (int& x : model) x ^= 1;\n        verify_state(bits, model);\n\n\
    \        bits.flip();\n        for (int& x : model) x ^= 1;\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 3 == 0)\
    \ {\n                bits.set(i);\n                model[i] = 1;\n           \
    \ }\n        }\n        verify_state(bits, model);\n\n        for (int i = 0;\
    \ i < n; ++i) {\n            if (i % 5 == 0) {\n                bits.reset(i);\n\
    \                model[i] = 0;\n            }\n        }\n        verify_state(bits,\
    \ model);\n\n        for (int i = 0; i < n; ++i) {\n            if (i % 7 == 0)\
    \ {\n                bits.flip(i);\n                model[i] ^= 1;\n         \
    \   }\n        }\n        verify_state(bits, model);\n    }\n}\n\nvoid test_bitwise_operations()\
    \ {\n    const std::vector<int> sizes = {0, 1, 2, 63, 64, 65, 100, 127, 128, 129,\
    \ 255};\n\n    for (int n : sizes) {\n        std::vector<int> lhs(n), rhs(n);\n\
    \        for (int i = 0; i < n; ++i) {\n            lhs[i] = ((i * 37 + n) % 5)\
    \ < 2;\n            rhs[i] = ((i * 19 + n * 3) % 7) < 3;\n        }\n\n      \
    \  const DynamicBitset a = make_bitset(lhs);\n        const DynamicBitset b =\
    \ make_bitset(rhs);\n\n        verify_state(a & b, bitwise_and_model(lhs, rhs));\n\
    \        verify_state(a | b, bitwise_or_model(lhs, rhs));\n        verify_state(a\
    \ ^ b, bitwise_xor_model(lhs, rhs));\n        verify_state(~a, bitwise_not_model(lhs));\n\
    \n        DynamicBitset c = a;\n        c &= b;\n        verify_state(c, bitwise_and_model(lhs,\
    \ rhs));\n\n        c = a;\n        c |= b;\n        verify_state(c, bitwise_or_model(lhs,\
    \ rhs));\n\n        c = a;\n        c ^= b;\n        verify_state(c, bitwise_xor_model(lhs,\
    \ rhs));\n    }\n}\n\nvoid test_randomized() {\n    std::mt19937_64 rng(123456789);\n\
    \n    for (int trial = 0; trial < 200; ++trial) {\n        int n;\n        if\
    \ (trial < 130) {\n            n = trial;\n        } else {\n            n = static_cast<int>(rng()\
    \ % 600);\n        }\n\n        DynamicBitset bits(n, (rng() & 1) != 0);\n   \
    \     std::vector<int> model(n, bits.all() ? 1 : 0);\n        verify_state(bits,\
    \ model);\n\n        for (int step = 0; step < 400; ++step) {\n            const\
    \ int op = static_cast<int>(rng() % 10);\n            if (op == 0) {\n       \
    \         bits.set();\n                std::fill(model.begin(), model.end(), 1);\n\
    \            } else if (op == 1) {\n                bits.reset();\n          \
    \      std::fill(model.begin(), model.end(), 0);\n            } else if (op ==\
    \ 2) {\n                bits.flip();\n                for (int& x : model) x ^=\
    \ 1;\n            } else if (op <= 5) {\n                if (n == 0) continue;\n\
    \                const int i = static_cast<int>(rng() % n);\n                if\
    \ (op == 3) {\n                    bits.set(i);\n                    model[i]\
    \ = 1;\n                } else if (op == 4) {\n                    bits.reset(i);\n\
    \                    model[i] = 0;\n                } else {\n               \
    \     bits.flip(i);\n                    model[i] ^= 1;\n                }\n \
    \           } else {\n                std::vector<int> other_model(n);\n     \
    \           for (int i = 0; i < n; ++i) other_model[i] = (rng() % 3) == 0;\n \
    \               DynamicBitset other = make_bitset(other_model);\n\n          \
    \      if (op == 6) {\n                    bits &= other;\n                  \
    \  model = bitwise_and_model(model, other_model);\n                } else if (op\
    \ == 7) {\n                    bits |= other;\n                    model = bitwise_or_model(model,\
    \ other_model);\n                } else if (op == 8) {\n                    bits\
    \ ^= other;\n                    model = bitwise_xor_model(model, other_model);\n\
    \                } else {\n                    verify_state(bits & other, bitwise_and_model(model,\
    \ other_model));\n                    verify_state(bits | other, bitwise_or_model(model,\
    \ other_model));\n                    verify_state(bits ^ other, bitwise_xor_model(model,\
    \ other_model));\n                    verify_state(~bits, bitwise_not_model(model));\n\
    \                }\n            }\n            verify_state(bits, model);\n  \
    \      }\n    }\n}\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_constructors();\n \
    \   test_point_and_global_operations();\n    test_bitwise_operations();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - utilities/dynamic_bitset.hpp
  isVerificationFile: true
  path: verify/utilities/dynamic_bitset.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/dynamic_bitset.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/dynamic_bitset.test.cpp
- /verify/verify/utilities/dynamic_bitset.test.cpp.html
title: verify/utilities/dynamic_bitset.test.cpp
---
