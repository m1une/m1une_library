---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
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
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/ds/range_query/fenwick_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n#include <cassert>\n\
    #include <vector>\n\n#line 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#line\
    \ 6 \"ds/range_query/fenwick_tree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \ntemplate <typename T>\nstruct FenwickTree {\n   private:\n    int _n;\n    int\
    \ _max_power;\n    std::vector<T> _data;\n\n    static int max_power_leq(int n)\
    \ {\n        int result = 1;\n        while (result <= n / 2) result <<= 1;\n\
    \        return result;\n    }\n\n    T prefix_sum(int r) const {\n        T result{};\n\
    \        const T* data = _data.data();\n        while (r > 0) {\n            result\
    \ += data[r];\n            r -= r & -r;\n        }\n        return result;\n \
    \   }\n\n   public:\n    FenwickTree() : _n(0), _max_power(0) {}\n\n    explicit\
    \ FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n > 0 ? n : 1)),\
    \ _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>& a)\n\
    \        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0 ? _n\
    \ : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i <= _n;\
    \ ++i) {\n            _data[i] += a[i - 1];\n            const int p = i + (i\
    \ & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
    \            }\n        }\n    }\n\n    int size() const {\n        return _n;\n\
    \    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n    // Adds\
    \ `x` to the element at zero-based index `p`.\n    void add(int p, const T& x)\
    \ {\n        assert(0 <= p && p < _n);\n        ++p;\n        T* data = _data.data();\n\
    \        while (p <= _n) {\n            data[p] += x;\n            p += p & -p;\n\
    \        }\n    }\n\n    // Returns the sum of elements in the range [0, r).\n\
    \    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n        return\
    \ prefix_sum(r);\n    }\n\n    // Returns the sum of elements in the range [l,\
    \ r).\n    T sum(int l, int r) const {\n        assert(0 <= l && l <= r && r <=\
    \ _n);\n        return prefix_sum(r) - prefix_sum(l);\n    }\n\n    // Returns\
    \ the minimum index `r` such that the sum of [0, r) >= w.\n    // Requires all\
    \ elements in the tree to be non-negative.\n    int lower_bound(T w) const {\n\
    \        if (w <= 0) return 0;\n        int x = 0;\n        const T* data = _data.data();\n\
    \        for (int k = _max_power; k > 0; k >>= 1) {\n            if (x + k <=\
    \ _n && data[x + k] < w) {\n                w -= data[x + k];\n              \
    \  x += k;\n            }\n        }\n        return x + 1;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\
    \n\n\n#include <array>\n#include <cstddef>\n#include <cstdio>\n#include <cstdint>\n\
    #include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
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
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 8 \"\
    verify/ds/range_query/fenwick_tree.test.cpp\"\n\nvoid test_fenwick_tree() {\n\
    \    const std::vector<long long> values = {1, 2, 3};\n    m1une::ds::FenwickTree<long\
    \ long> tree(values);\n\n    assert(tree.size() == 3);\n    assert(!tree.empty());\n\
    \    assert(tree.sum(0) == 0);\n    assert(tree.sum(3) == 6);\n    assert(tree.sum(1,\
    \ 3) == 5);\n    assert(tree.lower_bound(0) == 0);\n    assert(tree.lower_bound(1)\
    \ == 1);\n    assert(tree.lower_bound(3) == 2);\n    assert(tree.lower_bound(6)\
    \ == 3);\n    assert(tree.lower_bound(7) == 4);\n\n    m1une::ds::FenwickTree<long\
    \ long> empty;\n    assert(empty.empty());\n    assert(empty.lower_bound(1) ==\
    \ 1);\n}\n\nint main() {\n    test_fenwick_tree();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n, q;\n    if (!input.read(n))\
    \ return 0;\n    input.read(q);\n    std::vector<long long> values(n);\n    for\
    \ (long long& value : values) {\n        input.read(value);\n    }\n\n    m1une::ds::FenwickTree<long\
    \ long> tree(values);\n    for (int query = 0; query < q; ++query) {\n       \
    \ int type;\n        input.read(type);\n        if (type == 0) {\n           \
    \ int p;\n            long long x;\n            input.read(p);\n            input.read(x);\n\
    \            tree.add(p, x);\n        } else {\n            int l, r;\n      \
    \      input.read(l);\n            input.read(r);\n            output.println(tree.sum(l,\
    \ r));\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <cassert>\n#include <vector>\n\n#include \"../../../ds/range_query/fenwick_tree.hpp\"\
    \n#include \"../../../utilities/fast_io.hpp\"\n\nvoid test_fenwick_tree() {\n\
    \    const std::vector<long long> values = {1, 2, 3};\n    m1une::ds::FenwickTree<long\
    \ long> tree(values);\n\n    assert(tree.size() == 3);\n    assert(!tree.empty());\n\
    \    assert(tree.sum(0) == 0);\n    assert(tree.sum(3) == 6);\n    assert(tree.sum(1,\
    \ 3) == 5);\n    assert(tree.lower_bound(0) == 0);\n    assert(tree.lower_bound(1)\
    \ == 1);\n    assert(tree.lower_bound(3) == 2);\n    assert(tree.lower_bound(6)\
    \ == 3);\n    assert(tree.lower_bound(7) == 4);\n\n    m1une::ds::FenwickTree<long\
    \ long> empty;\n    assert(empty.empty());\n    assert(empty.lower_bound(1) ==\
    \ 1);\n}\n\nint main() {\n    test_fenwick_tree();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    int n, q;\n    if (!input.read(n))\
    \ return 0;\n    input.read(q);\n    std::vector<long long> values(n);\n    for\
    \ (long long& value : values) {\n        input.read(value);\n    }\n\n    m1une::ds::FenwickTree<long\
    \ long> tree(values);\n    for (int query = 0; query < q; ++query) {\n       \
    \ int type;\n        input.read(type);\n        if (type == 0) {\n           \
    \ int p;\n            long long x;\n            input.read(p);\n            input.read(x);\n\
    \            tree.add(p, x);\n        } else {\n            int l, r;\n      \
    \      input.read(l);\n            input.read(r);\n            output.println(tree.sum(l,\
    \ r));\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/fenwick_tree.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/fenwick_tree.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 03:19:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/fenwick_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/fenwick_tree.test.cpp
- /verify/verify/ds/range_query/fenwick_tree.test.cpp.html
title: verify/ds/range_query/fenwick_tree.test.cpp
---
