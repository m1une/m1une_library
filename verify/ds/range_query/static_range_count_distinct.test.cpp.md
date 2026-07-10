---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/static_range_count_distinct.hpp
    title: Static Range Count Distinct
  - icon: ':heavy_check_mark:'
    path: ds/range_query/wavelet_matrix.hpp
    title: Wavelet Matrix
  - icon: ':question:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_count_distinct
    links:
    - https://judge.yosupo.jp/problem/static_range_count_distinct
  bundledCode: "#line 1 \"verify/ds/range_query/static_range_count_distinct.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_count_distinct\"\
    \n\n#line 1 \"ds/range_query/static_range_count_distinct.hpp\"\n\n\n\n#line 1\
    \ \"ds/range_query/wavelet_matrix.hpp\"\n\n\n\n#include <bit>\n#include <cassert>\n\
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
    \ m1une\n\n\n#line 5 \"ds/range_query/static_range_count_distinct.hpp\"\n\n#include\
    \ <algorithm>\n#line 9 \"ds/range_query/static_range_count_distinct.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\n// Counts distinct values in static half-open\
    \ ranges.\ntemplate <class T>\nstruct StaticRangeCountDistinct {\n   private:\n\
    \    int _n;\n    WaveletMatrix<int> _previous;\n\n   public:\n    StaticRangeCountDistinct()\
    \ : _n(0), _previous() {}\n\n    explicit StaticRangeCountDistinct(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())), _previous() {\n        if (_n ==\
    \ 0) return;\n\n        std::vector<T> compressed = values;\n        std::sort(compressed.begin(),\
    \ compressed.end());\n        compressed.erase(\n            std::unique(compressed.begin(),\
    \ compressed.end()),\n            compressed.end()\n        );\n\n        std::vector<int>\
    \ last(compressed.size(), -1);\n        std::vector<int> previous(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            int rank = int(\n            \
    \    std::lower_bound(\n                    compressed.begin(),\n            \
    \        compressed.end(),\n                    values[i]\n                ) -\
    \ compressed.begin()\n            );\n            previous[i] = last[rank];\n\
    \            last[rank] = i;\n        }\n        _previous = WaveletMatrix<int>(previous);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int query(int left, int right)\
    \ const {\n        assert(0 <= left && left <= right && right <= _n);\n      \
    \  if (left == right) return 0;\n        return _previous.range_freq(left, right,\
    \ left);\n    }\n\n    int count_distinct(int left, int right) const {\n     \
    \   return query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <iterator>\n#include <string>\n#line\
    \ 11 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\nnamespace\
    \ internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class T, class\
    \ = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\nstruct\
    \ is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n  \
    \  decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
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
    \ bool has_val_method_v = has_val_method<T>::value;\n\n}  // namespace internal\n\
    \nstruct FastInput {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n\
    \    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int _position;\n\
    \    int _length;\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length) {\n           \
    \ _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n            _position\
    \ = 0;\n            if (_length == 0) return EOF;\n        }\n        return _buffer[_position++];\n\
    \    }\n\n    bool skip_spaces() {\n        int c = read_char_raw();\n       \
    \ while (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return\
    \ false;\n        --_position;\n        return true;\n    }\n\n    bool read(char&\
    \ value) {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \n        bool negative = false;\n        if (c == '-') {\n            negative\
    \ = true;\n            c = read_char_raw();\n        }\n\n        if constexpr\
    \ (std::is_signed_v<T>) {\n            T result = 0;\n            while ('0' <=\
    \ c && c <= '9') {\n                int digit = c - '0';\n                result\
    \ = negative ? result * 10 - digit : result * 10 + digit;\n                c =\
    \ read_char_raw();\n            }\n            value = result;\n        } else\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               result = result * 10 + T(c - '0');\n                c = read_char_raw();\n\
    \            }\n            value = negative ? T(0) - result : result;\n     \
    \   }\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        value\
    \ = T(x);\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
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
    \ buffer_size = 1 << 20;\n\n   private:\n    inline static constexpr auto digit_pairs\
    \ = [] {\n        std::array<char, 200> result{};\n        for (int i = 0; i <\
    \ 100; i++) {\n            result[2 * i] = char('0' + i / 10);\n            result[2\
    \ * i + 1] = char('0' + i % 10);\n        }\n        return result;\n    }();\n\
    \n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int _position;\n\
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\
    \ _position(0) {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \    }\n\n    void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<\n    \
    \    std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        char\
    \ digits[64];\n        int begin = 64;\n        while (magnitude >= 100) {\n \
    \           const Unsigned quotient = magnitude / 100;\n            const unsigned\
    \ remainder = unsigned(magnitude - quotient * 100);\n            begin -= 2;\n\
    \            digits[begin] = digit_pairs[2 * remainder];\n            digits[begin\
    \ + 1] = digit_pairs[2 * remainder + 1];\n            magnitude = quotient;\n\
    \        }\n        if (magnitude < 10) {\n            digits[--begin] = char('0'\
    \ + magnitude);\n        } else {\n            begin -= 2;\n            digits[begin]\
    \ = digit_pairs[2 * unsigned(magnitude)];\n            digits[begin + 1] = digit_pairs[2\
    \ * unsigned(magnitude) + 1];\n        }\n        while (begin < 64) write_char(digits[begin++]);\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n\
    \            && !std::is_integral_v<T>\n            && !internal::is_range_v<T>\n\
    \    >\n    write(const T& value) {\n        write(value.val());\n    }\n\n  \
    \  template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n\n    template <class T>\n    FastOutput&\
    \ operator<<(const T& value) {\n        write(value);\n        return *this;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 5 \"\
    verify/ds/range_query/static_range_count_distinct.test.cpp\"\n\n#line 10 \"verify/ds/range_query/static_range_count_distinct.test.cpp\"\
    \n\nnamespace {\n\nint brute(const std::vector<int>& values, int left, int right)\
    \ {\n    std::vector<int> distinct(values.begin() + left, values.begin() + right);\n\
    \    std::sort(distinct.begin(), distinct.end());\n    return int(std::unique(distinct.begin(),\
    \ distinct.end()) - distinct.begin());\n}\n\nvoid test_randomized() {\n    m1une::ds::StaticRangeCountDistinct<int>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.query(0,\
    \ 0) == 0);\n\n    std::uint64_t state = 1618033988ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        int\
    \ n = int(random() % 80);\n        std::vector<int> values(n);\n        for (int&\
    \ value : values) value = int(random() % 21) - 10;\n        m1une::ds::StaticRangeCountDistinct<int>\
    \ structure(values);\n        assert(structure.size() == n);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int left = int(random() % std::uint64_t(n\
    \ + 1));\n            int right = int(random() % std::uint64_t(n + 1));\n    \
    \        if (right < left) std::swap(left, right);\n            int expected =\
    \ brute(values, left, right);\n            assert(structure.query(left, right)\
    \ == expected);\n            assert(structure.count_distinct(left, right) == expected);\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n\n    m1une::ds::StaticRangeCountDistinct<int>\
    \ structure(values);\n    while (query_count--) {\n        int left = 0, right\
    \ = 0;\n        input.read(left, right);\n        output.println(structure.query(left,\
    \ right));\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_count_distinct\"\
    \n\n#include \"../../../ds/range_query/static_range_count_distinct.hpp\"\n#include\
    \ \"../../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\nnamespace {\n\nint brute(const std::vector<int>&\
    \ values, int left, int right) {\n    std::vector<int> distinct(values.begin()\
    \ + left, values.begin() + right);\n    std::sort(distinct.begin(), distinct.end());\n\
    \    return int(std::unique(distinct.begin(), distinct.end()) - distinct.begin());\n\
    }\n\nvoid test_randomized() {\n    m1une::ds::StaticRangeCountDistinct<int> empty;\n\
    \    assert(empty.empty());\n    assert(empty.size() == 0);\n    assert(empty.query(0,\
    \ 0) == 0);\n\n    std::uint64_t state = 1618033988ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        int\
    \ n = int(random() % 80);\n        std::vector<int> values(n);\n        for (int&\
    \ value : values) value = int(random() % 21) - 10;\n        m1une::ds::StaticRangeCountDistinct<int>\
    \ structure(values);\n        assert(structure.size() == n);\n\n        for (int\
    \ query = 0; query < 500; query++) {\n            int left = int(random() % std::uint64_t(n\
    \ + 1));\n            int right = int(random() % std::uint64_t(n + 1));\n    \
    \        if (right < left) std::swap(left, right);\n            int expected =\
    \ brute(values, left, right);\n            assert(structure.query(left, right)\
    \ == expected);\n            assert(structure.count_distinct(left, right) == expected);\n\
    \        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n = 0, query_count = 0;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n\n    m1une::ds::StaticRangeCountDistinct<int>\
    \ structure(values);\n    while (query_count--) {\n        int left = 0, right\
    \ = 0;\n        input.read(left, right);\n        output.println(structure.query(left,\
    \ right));\n    }\n}\n"
  dependsOn:
  - ds/range_query/static_range_count_distinct.hpp
  - ds/range_query/wavelet_matrix.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/static_range_count_distinct.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 02:39:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/static_range_count_distinct.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/static_range_count_distinct.test.cpp
- /verify/verify/ds/range_query/static_range_count_distinct.test.cpp.html
title: verify/ds/range_query/static_range_count_distinct.test.cpp
---
