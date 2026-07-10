---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algo/sequence/number_of_subsequences.hpp
    title: Number of Subsequences
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_subsequences
    links:
    - https://judge.yosupo.jp/problem/number_of_subsequences
  bundledCode: "#line 1 \"verify/algo/sequence/number_of_subsequences.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/number_of_subsequences\"\n\n\
    #line 1 \"algo/sequence/number_of_subsequences.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace algo {\n\n// Returns the number\
    \ of distinct nonempty subsequences.\ntemplate <class Mint, class T>\nMint number_of_distinct_subsequences(const\
    \ std::vector<T>& values) {\n    std::vector<T> compressed = values;\n    std::sort(compressed.begin(),\
    \ compressed.end());\n    compressed.erase(\n        std::unique(compressed.begin(),\
    \ compressed.end()),\n        compressed.end()\n    );\n\n    std::vector<Mint>\
    \ previous_total(compressed.size(), Mint(0));\n    Mint total = 1;\n    for (const\
    \ T& value : values) {\n        int rank = int(\n            std::lower_bound(\n\
    \                compressed.begin(),\n                compressed.end(),\n    \
    \            value\n            ) - compressed.begin()\n        );\n        Mint\
    \ old_total = total;\n        total = total + total - previous_total[rank];\n\
    \        previous_total[rank] = old_total;\n    }\n    return total - Mint(1);\n\
    }\n\ntemplate <class Mint, class T>\nMint number_of_subsequences(const std::vector<T>&\
    \ values) {\n    return number_of_distinct_subsequences<Mint>(values);\n}\n\n\
    }  // namespace algo\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\n\
    \n\n\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n#include\
    \ <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\n\
    struct ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\
    \n   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cstddef>\n#include <cstdio>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#line 13 \"utilities/fast_io.hpp\"\n\n\
    namespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
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
    \ = has_static_mod_raw<T>::value;\n\n}  // namespace internal\n\nstruct FastInput\
    \ {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n    std::FILE*\
    \ _stream;\n    char _buffer[buffer_size];\n    int _position;\n    int _length;\n\
    \n    bool prepare_number() {\n        if (_length - _position >= 32) return true;\n\
    \        const int remaining = _length - _position;\n        if (remaining > 0)\
    \ std::memmove(_buffer, _buffer + _position, remaining);\n        const int added\
    \ = int(std::fread(_buffer + remaining, 1, buffer_size - remaining, _stream));\n\
    \        _position = 0;\n        _length = remaining + added;\n        if (_length\
    \ < buffer_size) _buffer[_length] = '\\0';\n        return _length != 0;\n   \
    \ }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n       \
    \ : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const FastInput&)\
    \ = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\n    int read_char_raw()\
    \ {\n        if (_position == _length) {\n            _length = int(std::fread(_buffer,\
    \ 1, buffer_size, _stream));\n            _position = 0;\n            if (_length\
    \ == 0) return EOF;\n        }\n        return _buffer[_position++];\n    }\n\n\
    \    bool skip_spaces() {\n        int c = read_char_raw();\n        while (c\
    \ != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \        --_position;\n        return true;\n    }\n\n    bool read(char& value)\
    \ {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (std::is_signed_v<T>) {\n            T result = 0;\n  \
    \          while ('0' <= c && c <= '9') {\n                const int first = c\
    \ - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
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
    \ <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n  \
    \          && !std::is_integral_v<T>\n            && !internal::is_range_v<T>,\n\
    \        bool\n    >\n    read(T& value) {\n        long long x;\n        if (!read(x))\
    \ return false;\n        if constexpr (internal::has_static_mod_raw_v<T>) {\n\
    \            if (x >= 0 && uint64_t(x) < uint64_t(T::mod())) {\n             \
    \   value = T::raw(uint32_t(x));\n            } else {\n                value\
    \ = T(x);\n            }\n        } else {\n            value = T(x);\n      \
    \  }\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>,\n\
    \        bool\n    >\n    read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        read(value);\n   \
    \     return *this;\n    }\n};\n\nstruct FastOutput {\n    static constexpr int\
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static const auto digit_quads\
    \ = [] {\n        std::array<char, 40000> result{};\n        for (int i = 0; i\
    \ < 10000; i++) {\n            int value = i;\n            for (int j = 3; j >=\
    \ 0; j--) {\n                result[4 * i + j] = char('0' + value % 10);\n   \
    \             value /= 10;\n            }\n        }\n        return result;\n\
    \    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n\
    \        : _stream(stream), _position(0) {}\n\n    FastOutput(const FastOutput&)\
    \ = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput()\
    \ {\n        flush();\n    }\n\n    void flush() {\n        if (_position == 0)\
    \ return;\n        std::fwrite(_buffer, 1, _position, _stream);\n        _position\
    \ = 0;\n    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        unsigned\
    \ chunks[16];\n        int count = 0;\n        while (magnitude >= 10000) {\n\
    \            const Unsigned quotient = magnitude / 10000;\n            chunks[count++]\
    \ = unsigned(magnitude - quotient * 10000);\n            magnitude = quotient;\n\
    \        }\n        if (_position > buffer_size - 64) flush();\n        const\
    \ unsigned leading = unsigned(magnitude);\n        const char* first = digit_quads.data()\
    \ + 4 * leading;\n        int skip = leading < 10 ? 3 : leading < 100 ? 2 : leading\
    \ < 1000 ? 1 : 0;\n        for (; skip < 4; skip++) _buffer[_position++] = first[skip];\n\
    \        while (count--) {\n            const char* digits = digit_quads.data()\
    \ + 4 * chunks[count];\n            std::memcpy(_buffer + _position, digits, 4);\n\
    \            _position += 4;\n        }\n    }\n\n    template <class T>\n   \
    \ std::enable_if_t<\n        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
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
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 6 \"\
    verify/algo/sequence/number_of_subsequences.test.cpp\"\n\n#include <cassert>\n\
    #line 9 \"verify/algo/sequence/number_of_subsequences.test.cpp\"\n#include <set>\n\
    #line 12 \"verify/algo/sequence/number_of_subsequences.test.cpp\"\n\nnamespace\
    \ {\n\nusing Mint = m1une::math::ModInt<998244353>;\n\nlong long brute(const std::vector<int>&\
    \ values) {\n    std::set<std::vector<int>> subsequences;\n    int n = int(values.size());\n\
    \    for (int mask = 1; mask < (1 << n); mask++) {\n        std::vector<int> subsequence;\n\
    \        for (int i = 0; i < n; i++) {\n            if (mask >> i & 1) subsequence.push_back(values[i]);\n\
    \        }\n        subsequences.insert(std::move(subsequence));\n    }\n    return\
    \ static_cast<long long>(subsequences.size());\n}\n\nvoid test_randomized() {\n\
    \    std::vector<int> empty;\n    assert(m1une::algo::number_of_subsequences<Mint>(empty)\
    \ == Mint(0));\n\n    std::uint64_t state = 1732050807ULL;\n    auto random =\
    \ [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n      \
    \  return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++) {\n\
    \        int n = int(random() % 13);\n        std::vector<int> values(n);\n  \
    \      for (int& value : values) value = int(random() % 7) - 3;\n        Mint\
    \ expected = brute(values);\n        assert(\n            m1une::algo::number_of_distinct_subsequences<Mint>(values)\n\
    \            == expected\n        );\n        assert(\n            m1une::algo::number_of_subsequences<Mint>(values)\
    \ == expected\n        );\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0;\n    input.read(n);\n    std::vector<int> values(n);\n    for\
    \ (int& value : values) input.read(value);\n    output.println(\n        m1une::algo::number_of_subsequences<Mint>(values).val()\n\
    \    );\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_subsequences\"\
    \n\n#include \"../../../algo/sequence/number_of_subsequences.hpp\"\n#include \"\
    ../../../math/modint.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <set>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace {\n\nusing Mint = m1une::math::ModInt<998244353>;\n\n\
    long long brute(const std::vector<int>& values) {\n    std::set<std::vector<int>>\
    \ subsequences;\n    int n = int(values.size());\n    for (int mask = 1; mask\
    \ < (1 << n); mask++) {\n        std::vector<int> subsequence;\n        for (int\
    \ i = 0; i < n; i++) {\n            if (mask >> i & 1) subsequence.push_back(values[i]);\n\
    \        }\n        subsequences.insert(std::move(subsequence));\n    }\n    return\
    \ static_cast<long long>(subsequences.size());\n}\n\nvoid test_randomized() {\n\
    \    std::vector<int> empty;\n    assert(m1une::algo::number_of_subsequences<Mint>(empty)\
    \ == Mint(0));\n\n    std::uint64_t state = 1732050807ULL;\n    auto random =\
    \ [&]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n      \
    \  return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++) {\n\
    \        int n = int(random() % 13);\n        std::vector<int> values(n);\n  \
    \      for (int& value : values) value = int(random() % 7) - 3;\n        Mint\
    \ expected = brute(values);\n        assert(\n            m1une::algo::number_of_distinct_subsequences<Mint>(values)\n\
    \            == expected\n        );\n        assert(\n            m1une::algo::number_of_subsequences<Mint>(values)\
    \ == expected\n        );\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0;\n    input.read(n);\n    std::vector<int> values(n);\n    for\
    \ (int& value : values) input.read(value);\n    output.println(\n        m1une::algo::number_of_subsequences<Mint>(values).val()\n\
    \    );\n}\n"
  dependsOn:
  - algo/sequence/number_of_subsequences.hpp
  - math/modint.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/algo/sequence/number_of_subsequences.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/algo/sequence/number_of_subsequences.test.cpp
layout: document
redirect_from:
- /verify/verify/algo/sequence/number_of_subsequences.test.cpp
- /verify/verify/algo/sequence/number_of_subsequences.test.cpp.html
title: verify/algo/sequence/number_of_subsequences.test.cpp
---
