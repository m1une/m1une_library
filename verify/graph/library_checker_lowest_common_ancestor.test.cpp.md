---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sparse_table.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/sparse_table_lca.hpp
    title: Sparse Table LCA
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"verify/graph/library_checker_lowest_common_ancestor.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une\
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
    \ m1une\n\n\n#line 4 \"verify/graph/library_checker_lowest_common_ancestor.test.cpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#line 1 \"graph/graph.hpp\"\
    \n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\n\
    template <class T = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n\
    \    int to;\n    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1),\
    \ to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_\
    \ = T(1), int id_ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_),\
    \ id(id_), alive(alive_) {}\n\n    int other(int v) const {\n        assert(v\
    \ == from || v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class\
    \ T = int>\nstruct Graph {\n    using edge_type = Edge<T>;\n    using cost_type\
    \ = T;\n\n   private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 1 \"graph/tree/sparse_table_lca.hpp\"\n\n\n\n#line 9 \"graph/tree/sparse_table_lca.hpp\"\
    \n\n#line 1 \"ds/range_query/sparse_table.hpp\"\n\n\n\n#include <bit>\n#line 6\
    \ \"ds/range_query/sparse_table.hpp\"\n#include <concepts>\n#line 9 \"ds/range_query/sparse_table.hpp\"\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/range_query/sparse_table.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A Sparse Table utilizing C++20 Concepts\
    \ for type safety.\n// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n\
    // [IMPORTANT] For O(1) range queries to work correctly, the monoid operation\
    \ MUST be idempotent.\n// i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max,\
    \ GCD, Bitwise AND/OR).\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n\
    \    std::vector<std::vector<T>> _st;\n\n   public:\n    // Constructs an empty\
    \ sparse table.\n    SparseTable() : _n(0) {}\n\n    // Constructs a sparse table\
    \ from an existing vector in O(N log N) time.\n    explicit SparseTable(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       // Compute the maximum power of 2 needed\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Initialize\
    \ the base level\n        for (int i = 0; i < _n; i++) {\n            _st[0][i]\
    \ = v[i];\n        }\n\n        // Build the sparse table\n        for (int k\
    \ = 1; k < max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++)\
    \ {\n                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 <<\
    \ (k - 1))]);\n            }\n        }\n    }\n    explicit SparseTable(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n        int max_log\
    \ = std::bit_width((unsigned int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\
    \n        for (int i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n\
    \        }\n\n        for (int k = 1; k < max_log; k++) {\n            for (int\
    \ i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k\
    \ - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\
    \n    // Constructs a sparse table from a vector of a different type U.\n    //\
    \ It automatically adapts to the Monoid's initialization requirements:\n    //\
    \ 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index) if the\
    \ monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit SparseTable(const std::vector<U>& v) : _n(int(v.size())) {\n\
    \        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Compile-time\
    \ branching based on the available make() signature\n        for (int i = 0; i\
    \ < _n; i++) {\n            if constexpr (requires(U x) { Monoid::make(x); })\
    \ {\n                _st[0][i] = Monoid::make(v[i]);\n            } else if constexpr\
    \ (requires(U x, int idx) { Monoid::make(x, idx); }) {\n                _st[0][i]\
    \ = Monoid::make(v[i], i);\n            } else {\n                _st[0][i] =\
    \ static_cast<T>(v[i]);\n            }\n        }\n        for (int k = 1; k <\
    \ max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++) {\n  \
    \              _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k -\
    \ 1))]);\n            }\n        }\n    }\n\n    // Returns the product (result\
    \ of the monoid operation) in the range [l, r) in O(1) time.\n    // Requires\
    \ the monoid operation to be idempotent.\n    T prod(int l, int r) const {\n \
    \       assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return Monoid::id();\n\
    \n        // Calculate the largest power of 2 less than or equal to the interval\
    \ length\n        int k = std::bit_width((unsigned int)(r - l)) - 1;\n       \
    \ return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 12 \"graph/tree/sparse_table_lca.hpp\"\n\
    \nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct SparseTableLca\
    \ {\n    using cost_type = T;\n    using edge_type = m1une::graph::Edge<T>;\n\n\
    \    int root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n\
    \    std::vector<int> depth;\n    std::vector<T> dist;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n\
    \    std::vector<int> first;\n    std::vector<int> euler;\n\n   private:\n   \
    \ struct RmqNode {\n        int depth;\n        int vertex;\n    };\n\n    struct\
    \ RmqMonoid {\n        using value_type = RmqNode;\n\n        static value_type\
    \ id() {\n            return {std::numeric_limits<int>::max(), -1};\n        }\n\
    \n        static value_type op(const value_type& a, const value_type& b) {\n \
    \           if (a.depth != b.depth) return a.depth < b.depth ? a : b;\n      \
    \      return a.vertex < b.vertex ? a : b;\n        }\n    };\n\n    int _n;\n\
    \    m1une::ds::SparseTable<RmqMonoid> _st;\n\n    void check_vertex(int v) const\
    \ {\n        assert(0 <= v && v < _n);\n        assert(first[v] != -1);\n    }\n\
    \n   public:\n    SparseTableLca() : root(-1), _n(0) {}\n    explicit SparseTableLca(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g, root_);\n    }\n\
    \n    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n\
    \ = g.size();\n        root = _n == 0 ? -1 : root_;\n        parent.assign(_n,\
    \ -2);\n        parent_edge.assign(_n, -1);\n        depth.assign(_n, 0);\n  \
    \      dist.assign(_n, T(0));\n        subtree_size.assign(_n, 0);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        first.assign(_n, -1);\n        euler.clear();\n        euler.reserve(std::max(0,\
    \ 2 * _n - 1));\n        _st = m1une::ds::SparseTable<RmqMonoid>();\n\n      \
    \  if (_n == 0) return;\n        assert(0 <= root && root < _n);\n\n        std::vector<int>\
    \ it(_n, 0);\n        std::vector<char> visited(_n, false);\n        std::vector<int>\
    \ stack = {root};\n        visited[root] = true;\n        parent[root] = -1;\n\
    \n        int timer = 0;\n        tin[root] = timer++;\n        order.push_back(root);\n\
    \        first[root] = 0;\n        euler.push_back(root);\n\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            if (it[v] < int(g[v].size()))\
    \ {\n                const auto& e = g[v][it[v]++];\n                if (!e.alive)\
    \ continue;\n                if (visited[e.to]) continue;\n                visited[e.to]\
    \ = true;\n                parent[e.to] = v;\n                parent_edge[e.to]\
    \ = e.id;\n                depth[e.to] = depth[v] + 1;\n                dist[e.to]\
    \ = dist[v] + e.cost;\n                tin[e.to] = timer++;\n                order.push_back(e.to);\n\
    \                first[e.to] = int(euler.size());\n                euler.push_back(e.to);\n\
    \                stack.push_back(e.to);\n            } else {\n              \
    \  subtree_size[v]++;\n                if (parent[v] != -1) subtree_size[parent[v]]\
    \ += subtree_size[v];\n                tout[v] = timer;\n                stack.pop_back();\n\
    \                if (!stack.empty()) euler.push_back(stack.back());\n        \
    \    }\n        }\n\n        std::vector<RmqNode> rmq;\n        rmq.reserve(euler.size());\n\
    \        for (int v : euler) rmq.push_back({depth[v], v});\n        _st = m1une::ds::SparseTable<RmqMonoid>(std::move(rmq));\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    bool is_ancestor(int u, int v)\
    \ const {\n        check_vertex(u);\n        check_vertex(v);\n        return\
    \ tin[u] <= tin[v] && tout[v] <= tout[u];\n    }\n\n    bool in_subtree(int v,\
    \ int u) const {\n        return is_ancestor(u, v);\n    }\n\n    int lca(int\
    \ u, int v) const {\n        check_vertex(u);\n        check_vertex(v);\n    \
    \    int l = first[u], r = first[v];\n        if (l > r) std::swap(l, r);\n  \
    \      return _st.prod(l, r + 1).vertex;\n    }\n\n    int dist_edges(int u, int\
    \ v) const {\n        int w = lca(u, v);\n        return depth[u] + depth[v] -\
    \ 2 * depth[w];\n    }\n\n    T dist_cost(int u, int v) const {\n        int w\
    \ = lca(u, v);\n        return dist[u] + dist[v] - dist[w] - dist[w];\n    }\n\
    \n    std::pair<int, int> subtree_range(int v) const {\n        check_vertex(v);\n\
    \        return {tin[v], tout[v]};\n    }\n};\n\n}  // namespace tree\n}  // namespace\
    \ m1une\n\n\n#line 10 \"verify/graph/library_checker_lowest_common_ancestor.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    int N, Q;\n    fast_input >> N >> Q;\n    m1une::graph::Graph<>\
    \ g(N);\n    for (int i = 1; i < N; ++i) {\n        int p;\n        fast_input\
    \ >> p;\n        g.add_edge(p, i);\n    }\n    m1une::tree::SparseTableLca<> lca(g,\
    \ 0);\n    while (Q--) {\n        int u, v;\n        fast_input >> u >> v;\n \
    \       fast_output << lca.lca(u, v) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\n\n#include \"../../graph/graph.hpp\"\
    \n#include \"../../graph/tree/sparse_table_lca.hpp\"\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    int N, Q;\n\
    \    fast_input >> N >> Q;\n    m1une::graph::Graph<> g(N);\n    for (int i =\
    \ 1; i < N; ++i) {\n        int p;\n        fast_input >> p;\n        g.add_edge(p,\
    \ i);\n    }\n    m1une::tree::SparseTableLca<> lca(g, 0);\n    while (Q--) {\n\
    \        int u, v;\n        fast_input >> u >> v;\n        fast_output << lca.lca(u,\
    \ v) << '\\n';\n    }\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  - graph/graph.hpp
  - graph/tree/sparse_table_lca.hpp
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/library_checker_lowest_common_ancestor.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/library_checker_lowest_common_ancestor.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/library_checker_lowest_common_ancestor.test.cpp
- /verify/verify/graph/library_checker_lowest_common_ancestor.test.cpp.html
title: verify/graph/library_checker_lowest_common_ancestor.test.cpp
---
