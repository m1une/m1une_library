---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix.hpp
    title: Wavelet Matrix
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
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/range_query/wavelet_matrix.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <limits>\n#include <optional>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// A static wavelet matrix for integral values.\ntemplate\
    \ <std::integral T>\nrequires(!std::same_as<std::remove_cv_t<T>, bool>)\nstruct\
    \ WaveletMatrix {\n    using value_type = T;\n    using unsigned_type = std::make_unsigned_t<T>;\n\
    \n   private:\n    static constexpr int bit_width = std::numeric_limits<unsigned_type>::digits;\n\
    \    static constexpr unsigned_type sign_mask = [] {\n        if constexpr (std::signed_integral<T>)\
    \ {\n            return unsigned_type(1) << (bit_width - 1);\n        } else {\n\
    \            return unsigned_type(0);\n        }\n    }();\n\n    struct BitVector\
    \ {\n        std::vector<std::uint64_t> bits;\n        std::vector<int> prefix;\n\
    \n        BitVector() = default;\n\n        explicit BitVector(int n)\n      \
    \      : bits((std::size_t(n) + 63) >> 6, 0),\n              prefix(bits.size()\
    \ + 1, 0) {}\n\n        void set(int p) {\n            bits[std::size_t(p) >>\
    \ 6] |= std::uint64_t(1) << (p & 63);\n        }\n\n        void build() {\n \
    \           for (std::size_t i = 0; i < bits.size(); i++) {\n                prefix[i\
    \ + 1] = prefix[i] + std::popcount(bits[i]);\n            }\n        }\n\n   \
    \     bool get(int p) const {\n            return (bits[std::size_t(p) >> 6] >>\
    \ (p & 63)) & 1;\n        }\n\n        int rank1(int r) const {\n            std::size_t\
    \ word = std::size_t(r) >> 6;\n            int offset = r & 63;\n            int\
    \ result = prefix[word];\n            if (offset != 0) {\n                result\
    \ += std::popcount(\n                    bits[word] & ((std::uint64_t(1) << offset)\
    \ - 1)\n                );\n            }\n            return result;\n      \
    \  }\n\n        int rank0(int r) const {\n            return r - rank1(r);\n \
    \       }\n    };\n\n    int _n;\n    std::vector<BitVector> _matrix;\n    std::vector<int>\
    \ _zero_count;\n\n    static unsigned_type encode(T value) {\n        unsigned_type\
    \ bits;\n        if constexpr (std::signed_integral<T>) {\n            bits =\
    \ std::bit_cast<unsigned_type>(value);\n        } else {\n            bits = value;\n\
    \        }\n        return bits ^ sign_mask;\n    }\n\n    static T decode(unsigned_type\
    \ key) {\n        unsigned_type bits = key ^ sign_mask;\n        if constexpr\
    \ (std::signed_integral<T>) {\n            return std::bit_cast<T>(bits);\n  \
    \      } else {\n            return bits;\n        }\n    }\n\n    static bool\
    \ bit(unsigned_type value, int level) {\n        return (value >> (bit_width -\
    \ 1 - level)) & unsigned_type(1);\n    }\n\n    int count_less_encoded(int l,\
    \ int r, unsigned_type upper) const {\n        int result = 0;\n        for (int\
    \ level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            if (bit(upper, level))\
    \ {\n                result += r0 - l0;\n                l = _zero_count[level]\
    \ + _matrix[level].rank1(l);\n                r = _zero_count[level] + _matrix[level].rank1(r);\n\
    \            } else {\n                l = l0;\n                r = r0;\n    \
    \        }\n        }\n        return result;\n    }\n\n   public:\n    WaveletMatrix()\
    \ : _n(0), _matrix(bit_width), _zero_count(bit_width, 0) {}\n\n    explicit WaveletMatrix(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())),\n          _matrix(),\n\
    \          _zero_count(bit_width, 0) {\n        std::vector<unsigned_type> current(_n);\n\
    \        std::vector<unsigned_type> next(_n);\n        for (int i = 0; i < _n;\
    \ i++) current[i] = encode(values[i]);\n\n        _matrix.reserve(bit_width);\n\
    \        for (int level = 0; level < bit_width; level++) {\n            _matrix.emplace_back(_n);\n\
    \            for (int i = 0; i < _n; i++) {\n                if (bit(current[i],\
    \ level)) _matrix.back().set(i);\n            }\n            _matrix.back().build();\n\
    \n            int zeros = _matrix.back().rank0(_n);\n            _zero_count[level]\
    \ = zeros;\n            int zero_pos = 0;\n            int one_pos = zeros;\n\
    \            for (unsigned_type value : current) {\n                if (bit(value,\
    \ level)) {\n                    next[one_pos++] = value;\n                } else\
    \ {\n                    next[zero_pos++] = value;\n                }\n      \
    \      }\n            current.swap(next);\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    T access(int p) const {\n        assert(0 <= p && p <\
    \ _n);\n        unsigned_type key = 0;\n        for (int level = 0; level < bit_width;\
    \ level++) {\n            bool one = _matrix[level].get(p);\n            if (one)\
    \ {\n                key |= unsigned_type(1) << (bit_width - 1 - level);\n   \
    \             p = _zero_count[level] + _matrix[level].rank1(p);\n            }\
    \ else {\n                p = _matrix[level].rank0(p);\n            }\n      \
    \  }\n        return decode(key);\n    }\n\n    T operator[](int p) const {\n\
    \        return access(p);\n    }\n\n    int rank(T value, int r) const {\n  \
    \      assert(0 <= r && r <= _n);\n        return rank(value, 0, r);\n    }\n\n\
    \    int rank(T value, int l, int r) const {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        unsigned_type key = encode(value);\n        for (int level\
    \ = 0; level < bit_width; level++) {\n            if (bit(key, level)) {\n   \
    \             l = _zero_count[level] + _matrix[level].rank1(l);\n            \
    \    r = _zero_count[level] + _matrix[level].rank1(r);\n            } else {\n\
    \                l = _matrix[level].rank0(l);\n                r = _matrix[level].rank0(r);\n\
    \            }\n        }\n        return r - l;\n    }\n\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        unsigned_type key = 0;\n        for\
    \ (int level = 0; level < bit_width; level++) {\n            int l0 = _matrix[level].rank0(l);\n\
    \            int r0 = _matrix[level].rank0(r);\n            int zeros = r0 - l0;\n\
    \            if (k < zeros) {\n                l = l0;\n                r = r0;\n\
    \            } else {\n                k -= zeros;\n                key |= unsigned_type(1)\
    \ << (bit_width - 1 - level);\n                l = _zero_count[level] + _matrix[level].rank1(l);\n\
    \                r = _zero_count[level] + _matrix[level].rank1(r);\n         \
    \   }\n        }\n        return decode(key);\n    }\n\n    T kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l && l <= r && r <= _n);\n   \
    \     assert(0 <= k && k < r - l);\n        return kth_smallest(l, r, r - l -\
    \ 1 - k);\n    }\n\n    int range_freq(int l, int r, T upper) const {\n      \
    \  assert(0 <= l && l <= r && r <= _n);\n        return count_less_encoded(l,\
    \ r, encode(upper));\n    }\n\n    int range_freq(int l, int r, T lower, T upper)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        if (upper <=\
    \ lower) return 0;\n        return range_freq(l, r, upper) - range_freq(l, r,\
    \ lower);\n    }\n\n    std::optional<T> prev_value(int l, int r, T upper) const\
    \ {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, upper);\n        if (count == 0) return std::nullopt;\n        return kth_smallest(l,\
    \ r, count - 1);\n    }\n\n    std::optional<T> next_value(int l, int r, T lower)\
    \ const {\n        assert(0 <= l && l <= r && r <= _n);\n        int count = range_freq(l,\
    \ r, lower);\n        if (count == r - l) return std::nullopt;\n        return\
    \ kth_smallest(l, r, count);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <charconv>\n#include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 12 \"verify/ds/range_query/wavelet_matrix.test.cpp\"\n\nnamespace\
    \ {\n\nvoid test_edge_cases() {\n    m1une::ds::WaveletMatrix<long long> empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n\n    std::vector<long\
    \ long> values;\n    values.push_back(std::numeric_limits<long long>::min());\n\
    \    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n    assert(matrix.rank(-5,\
    \ 5) == 2);\n    assert(matrix.rank(-5, 1, 4) == 2);\n    assert(matrix.kth_smallest(0,\
    \ 5, 0) == std::numeric_limits<long long>::min());\n    assert(matrix.kth_largest(0,\
    \ 5, 0) == std::numeric_limits<long long>::max());\n    assert(matrix.range_freq(0,\
    \ 5, 0) == 3);\n    assert(matrix.range_freq(0, 5, -5, 1) == 3);\n    assert(matrix.prev_value(0,\
    \ 5, -5).value() == std::numeric_limits<long long>::min());\n    assert(matrix.next_value(0,\
    \ 5, 1).value() == std::numeric_limits<long long>::max());\n    assert(!matrix.prev_value(0,\
    \ 5, std::numeric_limits<long long>::min()));\n    assert(\n        matrix.next_value(0,\
    \ 5, std::numeric_limits<long long>::max()).value() ==\n        std::numeric_limits<long\
    \ long>::max()\n    );\n    assert(!matrix.next_value(1, 4, std::numeric_limits<long\
    \ long>::max()));\n\n    std::vector<unsigned int> unsigned_values;\n    unsigned_values.push_back(0);\n\
    \    unsigned_values.push_back(std::numeric_limits<unsigned int>::max());\n  \
    \  unsigned_values.push_back(7);\n    m1une::ds::WaveletMatrix<unsigned int> unsigned_matrix(unsigned_values);\n\
    \    assert(unsigned_matrix.kth_smallest(0, 3, 2) == std::numeric_limits<unsigned\
    \ int>::max());\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 17;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 80; trial++) {\n        int n = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 101) -\
    \ 50;\n        m1une::ds::WaveletMatrix<int> matrix(values);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int l = int(random() % std::uint64_t(n\
    \ + 1));\n            int r = int(random() % std::uint64_t(n + 1));\n        \
    \    if (r < l) std::swap(l, r);\n            int x = int(random() % 121) - 60;\n\
    \            int y = int(random() % 121) - 60;\n            if (y < x) std::swap(x,\
    \ y);\n\n            [[maybe_unused]] int rank = 0;\n            [[maybe_unused]]\
    \ int below = 0;\n            [[maybe_unused]] int between = 0;\n            std::optional<int>\
    \ previous;\n            std::optional<int> next;\n            std::vector<int>\
    \ sorted;\n            for (int i = l; i < r; i++) {\n                sorted.push_back(values[i]);\n\
    \                if (values[i] == x) rank++;\n                if (values[i] <\
    \ x) below++;\n                if (x <= values[i] && values[i] < y) between++;\n\
    \                if (values[i] < x && (!previous || *previous < values[i])) {\n\
    \                    previous = values[i];\n                }\n              \
    \  if (x <= values[i] && (!next || values[i] < *next)) {\n                   \
    \ next = values[i];\n                }\n            }\n            std::sort(sorted.begin(),\
    \ sorted.end());\n\n            assert(matrix.rank(x, l, r) == rank);\n      \
    \      assert(matrix.range_freq(l, r, x) == below);\n            assert(matrix.range_freq(l,\
    \ r, x, y) == between);\n            assert(matrix.prev_value(l, r, x) == previous);\n\
    \            assert(matrix.next_value(l, r, x) == next);\n            for (int\
    \ k = 0; k < int(sorted.size()); k++) {\n                assert(matrix.kth_smallest(l,\
    \ r, k) == sorted[k]);\n                assert(matrix.kth_largest(l, r, k) ==\
    \ sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) fast_input >> value;\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    for (int query = 0; query < q; query++) {\n     \
    \   int l, r, k;\n        fast_input >> l >> r >> k;\n        fast_output << matrix.kth_smallest(l,\
    \ r, k) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/range_query/wavelet_matrix.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <limits>\n#include <optional>\n#include <vector>\n\nnamespace {\n\n\
    void test_edge_cases() {\n    m1une::ds::WaveletMatrix<long long> empty;\n   \
    \ assert(empty.empty());\n    assert(empty.size() == 0);\n\n    std::vector<long\
    \ long> values;\n    values.push_back(std::numeric_limits<long long>::min());\n\
    \    values.push_back(-5);\n    values.push_back(0);\n    values.push_back(-5);\n\
    \    values.push_back(std::numeric_limits<long long>::max());\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    assert(matrix.size() == 5);\n    assert(!matrix.empty());\n\
    \    for (int i = 0; i < 5; i++) assert(matrix[i] == values[i]);\n    assert(matrix.rank(-5,\
    \ 5) == 2);\n    assert(matrix.rank(-5, 1, 4) == 2);\n    assert(matrix.kth_smallest(0,\
    \ 5, 0) == std::numeric_limits<long long>::min());\n    assert(matrix.kth_largest(0,\
    \ 5, 0) == std::numeric_limits<long long>::max());\n    assert(matrix.range_freq(0,\
    \ 5, 0) == 3);\n    assert(matrix.range_freq(0, 5, -5, 1) == 3);\n    assert(matrix.prev_value(0,\
    \ 5, -5).value() == std::numeric_limits<long long>::min());\n    assert(matrix.next_value(0,\
    \ 5, 1).value() == std::numeric_limits<long long>::max());\n    assert(!matrix.prev_value(0,\
    \ 5, std::numeric_limits<long long>::min()));\n    assert(\n        matrix.next_value(0,\
    \ 5, std::numeric_limits<long long>::max()).value() ==\n        std::numeric_limits<long\
    \ long>::max()\n    );\n    assert(!matrix.next_value(1, 4, std::numeric_limits<long\
    \ long>::max()));\n\n    std::vector<unsigned int> unsigned_values;\n    unsigned_values.push_back(0);\n\
    \    unsigned_values.push_back(std::numeric_limits<unsigned int>::max());\n  \
    \  unsigned_values.push_back(7);\n    m1une::ds::WaveletMatrix<unsigned int> unsigned_matrix(unsigned_values);\n\
    \    assert(unsigned_matrix.kth_smallest(0, 3, 2) == std::numeric_limits<unsigned\
    \ int>::max());\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 17;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 80; trial++) {\n        int n = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 101) -\
    \ 50;\n        m1une::ds::WaveletMatrix<int> matrix(values);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int l = int(random() % std::uint64_t(n\
    \ + 1));\n            int r = int(random() % std::uint64_t(n + 1));\n        \
    \    if (r < l) std::swap(l, r);\n            int x = int(random() % 121) - 60;\n\
    \            int y = int(random() % 121) - 60;\n            if (y < x) std::swap(x,\
    \ y);\n\n            [[maybe_unused]] int rank = 0;\n            [[maybe_unused]]\
    \ int below = 0;\n            [[maybe_unused]] int between = 0;\n            std::optional<int>\
    \ previous;\n            std::optional<int> next;\n            std::vector<int>\
    \ sorted;\n            for (int i = l; i < r; i++) {\n                sorted.push_back(values[i]);\n\
    \                if (values[i] == x) rank++;\n                if (values[i] <\
    \ x) below++;\n                if (x <= values[i] && values[i] < y) between++;\n\
    \                if (values[i] < x && (!previous || *previous < values[i])) {\n\
    \                    previous = values[i];\n                }\n              \
    \  if (x <= values[i] && (!next || values[i] < *next)) {\n                   \
    \ next = values[i];\n                }\n            }\n            std::sort(sorted.begin(),\
    \ sorted.end());\n\n            assert(matrix.rank(x, l, r) == rank);\n      \
    \      assert(matrix.range_freq(l, r, x) == below);\n            assert(matrix.range_freq(l,\
    \ r, x, y) == between);\n            assert(matrix.prev_value(l, r, x) == previous);\n\
    \            assert(matrix.next_value(l, r, x) == next);\n            for (int\
    \ k = 0; k < int(sorted.size()); k++) {\n                assert(matrix.kth_smallest(l,\
    \ r, k) == sorted[k]);\n                assert(matrix.kth_largest(l, r, k) ==\
    \ sorted[sorted.size() - 1 - k]);\n            }\n        }\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    test_edge_cases();\n    test_randomized();\n\
    \n    int n, q;\n    fast_input >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) fast_input >> value;\n\n    m1une::ds::WaveletMatrix<long\
    \ long> matrix(values);\n    for (int query = 0; query < q; query++) {\n     \
    \   int l, r, k;\n        fast_input >> l >> r >> k;\n        fast_output << matrix.kth_smallest(l,\
    \ r, k) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/wavelet_matrix.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/wavelet_matrix.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/wavelet_matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/wavelet_matrix.test.cpp
- /verify/verify/ds/range_query/wavelet_matrix.test.cpp.html
title: verify/ds/range_query/wavelet_matrix.test.cpp
---
