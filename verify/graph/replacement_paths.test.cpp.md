---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.hpp
    title: Dijkstra
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/replacement_paths.hpp
    title: Replacement Paths
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
  bundledCode: "#line 1 \"verify/graph/replacement_paths.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <functional>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n\
    #include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
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
    \ m1une\n\n\n#line 7 \"verify/graph/replacement_paths.test.cpp\"\n#include <limits>\n\
    #include <queue>\n#include <random>\n#line 11 \"verify/graph/replacement_paths.test.cpp\"\
    \n#include <vector>\n\n#line 1 \"graph/replacement_paths.hpp\"\n\n\n\n#line 11\
    \ \"graph/replacement_paths.hpp\"\n\n#line 1 \"graph/dijkstra.hpp\"\n\n\n\n#line\
    \ 11 \"graph/dijkstra.hpp\"\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     _g[u].push_back(edge_type(u, v, cost, id));\n        int v_idx = int(_g[v].size());\n\
    \        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \ m1une\n\n\n#line 13 \"graph/dijkstra.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct DijkstraResult {\n    std::vector<T> dist;\n\
    \    std::vector<int> parent;\n    std::vector<int> parent_edge;\n    T inf;\n\
    \n    bool reachable(int v) const {\n        assert(0 <= v && v < int(dist.size()));\n\
    \        return dist[v] != inf;\n    }\n\n    std::vector<int> path(int t) const\
    \ {\n        assert(reachable(t));\n        std::vector<int> result;\n       \
    \ for (int v = t; v != -1; v = parent[v]) result.push_back(v);\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n};\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, const std::vector<int>& sources,\n             \
    \              T inf = std::numeric_limits<T>::max() / T(4)) {\n    int n = g.size();\n\
    \    DijkstraResult<T> result;\n    result.dist.assign(n, inf);\n    result.parent.assign(n,\
    \ -1);\n    result.parent_edge.assign(n, -1);\n    result.inf = inf;\n\n    using\
    \ P = std::pair<T, int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n    for (int s : sources) {\n        assert(0 <= s && s < n);\n      \
    \  if (result.dist[s] == T(0)) continue;\n        result.dist[s] = T(0);\n   \
    \     que.emplace(T(0), s);\n    }\n\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (result.dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive) continue;\n \
    \           T nd = d + e.cost;\n            if (result.dist[e.to] <= nd) continue;\n\
    \            result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n \
    \           result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n\
    \        }\n    }\n\n    return result;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ dijkstra(const Graph<T>& g, int s, T inf = std::numeric_limits<T>::max() / T(4))\
    \ {\n    return dijkstra(g, std::vector<int>{s}, inf);\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 14 \"graph/replacement_paths.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\nstruct GraphPath {\n    std::vector<int> vertices;\n\
    \    std::vector<int> edges;\n};\n\ntemplate <class T>\nstruct EdgeReplacementPathsResult\
    \ {\n    GraphPath path;\n    std::vector<T> replacement_dist;\n    T inf;\n\n\
    \    bool reachable(int path_edge_index) const {\n        assert(0 <= path_edge_index\
    \ && path_edge_index < int(replacement_dist.size()));\n        return replacement_dist[path_edge_index]\
    \ != inf;\n    }\n};\n\ntemplate <class T>\nstruct VertexReplacementPathsResult\
    \ {\n    GraphPath path;\n    std::vector<T> replacement_dist;\n    T inf;\n\n\
    \    bool reachable(int path_vertex_index) const {\n        assert(0 <= path_vertex_index\
    \ && path_vertex_index < int(replacement_dist.size()));\n        return replacement_dist[path_vertex_index]\
    \ != inf;\n    }\n};\n\nnamespace internal {\n\ntemplate <class T>\nT replacement_paths_safe_add(T\
    \ a, T b, T inf) {\n    if (a >= inf || b >= inf) return inf;\n    if (a > inf\
    \ - b) return inf;\n    return a + b;\n}\n\ntemplate <class T>\nDijkstraResult<T>\
    \ replacement_paths_dijkstra(const Graph<T>& g, int s, T inf) {\n    int n = g.size();\n\
    \    assert(0 <= s && s < n);\n    DijkstraResult<T> result;\n    result.dist.assign(n,\
    \ inf);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.inf = inf;\n\n    using P = std::pair<T, int>;\n    std::priority_queue<P,\
    \ std::vector<P>, std::greater<P>> que;\n    result.dist[s] = T(0);\n    que.emplace(T(0),\
    \ s);\n    while (!que.empty()) {\n        auto [d, v] = que.top();\n        que.pop();\n\
    \        if (result.dist[v] != d) continue;\n        for (const auto& e : g[v])\
    \ {\n            if (!e.alive) continue;\n            T nd = replacement_paths_safe_add(d,\
    \ e.cost, inf);\n            if (result.dist[e.to] <= nd) continue;\n        \
    \    result.dist[e.to] = nd;\n            result.parent[e.to] = v;\n         \
    \   result.parent_edge[e.to] = e.id;\n            que.emplace(nd, e.to);\n   \
    \     }\n    }\n    return result;\n}\n\ntemplate <class T>\nstd::vector<Edge<T>>\
    \ replacement_paths_validate_graph(const Graph<T>& g, T inf) {\n    assert(T(0)\
    \ < inf);\n    std::vector<int> occurrence(g.edge_count(), 0);\n    std::vector<Edge<T>>\
    \ edge_by_id(g.edge_count());\n    for (int v = 0; v < g.size(); v++) {\n    \
    \    for (const auto& e : g[v]) {\n            assert(e.from == v);\n        \
    \    assert(0 <= e.to && e.to < g.size());\n            assert(0 <= e.id && e.id\
    \ < g.edge_count());\n            if (e.alive) assert(T(0) < e.cost);\n      \
    \      if (occurrence[e.id] == 0) {\n                edge_by_id[e.id] = e;\n \
    \           } else {\n                assert(occurrence[e.id] == 1);\n       \
    \         const auto& other = edge_by_id[e.id];\n                assert(e.from\
    \ == other.to && e.to == other.from);\n                assert(e.cost == other.cost\
    \ && e.alive == other.alive);\n            }\n            occurrence[e.id]++;\n\
    \        }\n    }\n\n    for (int id = 0; id < g.edge_count(); id++) {\n     \
    \   // add_edge creates exactly two mutually reversed arcs with one logical id.\n\
    \        assert(occurrence[id] == 2);\n    }\n    return edge_by_id;\n}\n\ntemplate\
    \ <class T>\nvoid replacement_paths_validate_path(const Graph<T>& g, const GraphPath&\
    \ path,\n                                     const std::vector<Edge<T>>& edge_by_id,\n\
    \                                     const DijkstraResult<T>& from_s) {\n   \
    \ assert(!path.vertices.empty());\n    assert(path.edges.size() + 1 == path.vertices.size());\n\
    \    std::vector<char> used_vertex(g.size(), false);\n    for (int v : path.vertices)\
    \ {\n        assert(0 <= v && v < g.size());\n        assert(!used_vertex[v]);\n\
    \        used_vertex[v] = true;\n    }\n\n    T path_cost = T(0);\n    for (int\
    \ i = 0; i < int(path.edges.size()); i++) {\n        int id = path.edges[i];\n\
    \        assert(0 <= id && id < g.edge_count());\n        assert(g.is_edge_alive(id));\n\
    \        const auto& e = edge_by_id[id];\n        int u = path.vertices[i];\n\
    \        int v = path.vertices[i + 1];\n        assert((e.from == u && e.to ==\
    \ v) || (e.from == v && e.to == u));\n        assert(T(0) < e.cost);\n       \
    \ path_cost = replacement_paths_safe_add(path_cost, e.cost, from_s.inf);\n   \
    \ }\n    assert(from_s.reachable(path.vertices.back()));\n    assert(path_cost\
    \ == from_s.dist[path.vertices.back()]);\n}\n\ntemplate <class T>\nGraphPath replacement_paths_restore_path(const\
    \ DijkstraResult<T>& result, int s, int t) {\n    assert(result.reachable(t));\n\
    \    GraphPath path;\n    for (int v = t; v != s; v = result.parent[v]) {\n  \
    \      assert(v != -1 && result.parent[v] != -1 && result.parent_edge[v] != -1);\n\
    \        path.vertices.push_back(v);\n        path.edges.push_back(result.parent_edge[v]);\n\
    \    }\n    path.vertices.push_back(s);\n    std::reverse(path.vertices.begin(),\
    \ path.vertices.end());\n    std::reverse(path.edges.begin(), path.edges.end());\n\
    \    return path;\n}\n\ntemplate <class T>\nstruct ReplacementPathsData {\n  \
    \  GraphPath path;\n    std::vector<T> dist_s;\n    std::vector<T> dist_t;\n \
    \   std::vector<int> block;\n    std::vector<char> is_path_edge;\n    std::vector<Edge<T>>\
    \ edge_by_id;\n    T inf;\n};\n\ntemplate <class T>\nReplacementPathsData<T> replacement_paths_prepare(const\
    \ Graph<T>& g, const GraphPath& path,\n                                      \
    \             T inf, const DijkstraResult<T>* known_from_s) {\n    auto edge_by_id\
    \ = replacement_paths_validate_graph(g, inf);\n    int s = path.vertices.front();\n\
    \    int t = path.vertices.back();\n    auto computed_from_s = known_from_s ==\
    \ nullptr\n                               ? replacement_paths_dijkstra(g, s, inf)\n\
    \                               : DijkstraResult<T>();\n    const auto& from_s\
    \ = known_from_s == nullptr ? computed_from_s : *known_from_s;\n    replacement_paths_validate_path(g,\
    \ path, edge_by_id, from_s);\n    auto from_t = replacement_paths_dijkstra(g,\
    \ t, inf);\n\n    int n = g.size();\n    std::vector<int> path_position(n, -1);\n\
    \    std::vector<char> is_path_edge(g.edge_count(), false);\n    for (int i =\
    \ 0; i < int(path.vertices.size()); i++) path_position[path.vertices[i]] = i;\n\
    \    for (int id : path.edges) is_path_edge[id] = true;\n\n    std::vector<int>\
    \ parent(n, -1);\n    for (int i = 0; i < int(path.edges.size()); i++) {\n   \
    \     int v = path.vertices[i + 1];\n        parent[v] = path.vertices[i];\n \
    \       const auto& e = edge_by_id[path.edges[i]];\n        assert(replacement_paths_safe_add(from_s.dist[parent[v]],\
    \ e.cost, inf) == from_s.dist[v]);\n    }\n    for (int v = 0; v < n; v++) {\n\
    \        if (!from_s.reachable(v) || v == s || path_position[v] != -1) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive || !from_s.reachable(e.to))\
    \ continue;\n            if (replacement_paths_safe_add(from_s.dist[e.to], e.cost,\
    \ inf) != from_s.dist[v]) {\n                continue;\n            }\n      \
    \      parent[v] = e.to;\n            break;\n        }\n        assert(parent[v]\
    \ != -1);\n        assert(from_s.dist[parent[v]] < from_s.dist[v]);\n    }\n\n\
    \    std::vector<std::vector<int>> children(n);\n    for (int v = 0; v < n; v++)\
    \ {\n        if (parent[v] != -1) children[parent[v]].push_back(v);\n    }\n \
    \   std::vector<int> block(n, -1);\n    block[s] = 0;\n    std::vector<int> stack\
    \ = {s};\n    while (!stack.empty()) {\n        int v = stack.back();\n      \
    \  stack.pop_back();\n        for (int to : children[v]) {\n            block[to]\
    \ = path_position[to] == -1 ? block[v] : path_position[to];\n            stack.push_back(to);\n\
    \        }\n    }\n    for (int v = 0; v < n; v++) assert(!from_s.reachable(v)\
    \ || block[v] != -1);\n\n    return {path, from_s.dist, from_t.dist, block, is_path_edge,\
    \ edge_by_id, inf};\n}\n\ntemplate <class T>\nclass ReplacementPathsRangeChmin\
    \ {\n   private:\n    int _size;\n    std::vector<T> _lazy;\n\n   public:\n  \
    \  ReplacementPathsRangeChmin(int n, T inf) : _size(1) {\n        while (_size\
    \ < n) _size <<= 1;\n        _lazy.assign(2 * _size, inf);\n    }\n\n    void\
    \ apply(int l, int r, T value) {\n        assert(0 <= l && l <= r && r <= _size);\n\
    \        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {\n           \
    \ if (l & 1) {\n                _lazy[l] = std::min(_lazy[l], value);\n      \
    \          l++;\n            }\n            if (r & 1) {\n                --r;\n\
    \                _lazy[r] = std::min(_lazy[r], value);\n            }\n      \
    \  }\n    }\n\n    std::vector<T> values(int n) {\n        for (int v = 1; v <\
    \ _size; v++) {\n            _lazy[2 * v] = std::min(_lazy[2 * v], _lazy[v]);\n\
    \            _lazy[2 * v + 1] = std::min(_lazy[2 * v + 1], _lazy[v]);\n      \
    \  }\n        return std::vector<T>(_lazy.begin() + _size, _lazy.begin() + _size\
    \ + n);\n    }\n};\n\ntemplate <class T>\nstd::vector<T> replacement_paths_solve_edges(const\
    \ ReplacementPathsData<T>& data) {\n    int answer_size = int(data.path.edges.size());\n\
    \    ReplacementPathsRangeChmin<T> range_chmin(answer_size, data.inf);\n    for\
    \ (const auto& e : data.edge_by_id) {\n        if (!e.alive || data.is_path_edge[e.id])\
    \ continue;\n        int u = e.from;\n        int v = e.to;\n        if (data.block[u]\
    \ == -1 || data.block[v] == -1 || data.block[u] == data.block[v]) continue;\n\
    \        if (data.block[u] > data.block[v]) std::swap(u, v);\n        int a =\
    \ data.block[u];\n        int b = data.block[v];\n        T candidate = replacement_paths_safe_add(data.dist_s[u],\
    \ e.cost, data.inf);\n        candidate = replacement_paths_safe_add(candidate,\
    \ data.dist_t[v], data.inf);\n        if (candidate == data.inf) continue;\n \
    \       range_chmin.apply(a, b, candidate);\n    }\n    return range_chmin.values(answer_size);\n\
    }\n\ntemplate <class T>\nT replacement_paths_without_vertex(const Graph<T>& g,\
    \ int s, int t, int removed, T inf) {\n    if (s == removed || t == removed) return\
    \ inf;\n    std::vector<T> dist(g.size(), inf);\n    using P = std::pair<T, int>;\n\
    \    std::priority_queue<P, std::vector<P>, std::greater<P>> que;\n    dist[s]\
    \ = T(0);\n    que.emplace(T(0), s);\n    while (!que.empty()) {\n        auto\
    \ [d, v] = que.top();\n        que.pop();\n        if (dist[v] != d) continue;\n\
    \        for (const auto& e : g[v]) {\n            if (!e.alive || e.to == removed)\
    \ continue;\n            T nd = replacement_paths_safe_add(d, e.cost, inf);\n\
    \            if (dist[e.to] <= nd) continue;\n            dist[e.to] = nd;\n \
    \           que.emplace(nd, e.to);\n        }\n    }\n    return dist[t];\n}\n\
    \ntemplate <class T>\nstd::vector<T> replacement_paths_solve_vertices(const Graph<T>&\
    \ g,\n                                                const ReplacementPathsData<T>&\
    \ data) {\n    // One edge can cross an edge cut, but a vertex-avoiding path may\
    \ enter and\n    // leave the failed vertex's tree block through two different\
    \ detour edges.\n    int path_size = int(data.path.vertices.size());\n    std::vector<T>\
    \ answer(path_size, data.inf);\n    int s = data.path.vertices.front();\n    int\
    \ t = data.path.vertices.back();\n    for (int i = 1; i + 1 < path_size; i++)\
    \ {\n        answer[i] = replacement_paths_without_vertex(g, s, t, data.path.vertices[i],\
    \ data.inf);\n    }\n    return answer;\n}\n\n}  // namespace internal\n\ntemplate\
    \ <class T>\nEdgeReplacementPathsResult<T> edge_replacement_paths(\n    const\
    \ Graph<T>& g, const GraphPath& path, T inf = std::numeric_limits<T>::max() /\
    \ T(4)) {\n    assert(!path.vertices.empty());\n    auto data = internal::replacement_paths_prepare(\n\
    \        g, path, inf, static_cast<const DijkstraResult<T>*>(nullptr));\n    auto\
    \ replacement_dist = internal::replacement_paths_solve_edges(data);\n    return\
    \ {path, replacement_dist, inf};\n}\n\ntemplate <class T>\nEdgeReplacementPathsResult<T>\
    \ edge_replacement_paths(\n    const Graph<T>& g, int s, int t, T inf = std::numeric_limits<T>::max()\
    \ / T(4)) {\n    assert(0 <= s && s < g.size());\n    assert(0 <= t && t < g.size());\n\
    \    auto from_s = internal::replacement_paths_dijkstra(g, s, inf);\n    assert(from_s.reachable(t));\n\
    \    auto path = internal::replacement_paths_restore_path(from_s, s, t);\n   \
    \ auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);\n  \
    \  auto replacement_dist = internal::replacement_paths_solve_edges(data);\n  \
    \  return {path, replacement_dist, inf};\n}\n\ntemplate <class T>\nVertexReplacementPathsResult<T>\
    \ vertex_replacement_paths(\n    const Graph<T>& g, const GraphPath& path, T inf\
    \ = std::numeric_limits<T>::max() / T(4)) {\n    assert(!path.vertices.empty());\n\
    \    auto data = internal::replacement_paths_prepare(\n        g, path, inf, static_cast<const\
    \ DijkstraResult<T>*>(nullptr));\n    auto replacement_dist = internal::replacement_paths_solve_vertices(g,\
    \ data);\n    return {path, replacement_dist, inf};\n}\n\ntemplate <class T>\n\
    VertexReplacementPathsResult<T> vertex_replacement_paths(\n    const Graph<T>&\
    \ g, int s, int t, T inf = std::numeric_limits<T>::max() / T(4)) {\n    assert(0\
    \ <= s && s < g.size());\n    assert(0 <= t && t < g.size());\n    auto from_s\
    \ = internal::replacement_paths_dijkstra(g, s, inf);\n    assert(from_s.reachable(t));\n\
    \    auto path = internal::replacement_paths_restore_path(from_s, s, t);\n   \
    \ auto data = internal::replacement_paths_prepare(g, path, inf, &from_s);\n  \
    \  auto replacement_dist = internal::replacement_paths_solve_vertices(g, data);\n\
    \    return {path, replacement_dist, inf};\n}\n\n}  // namespace graph\n}  //\
    \ namespace m1une\n\n\n#line 14 \"verify/graph/replacement_paths.test.cpp\"\n\n\
    namespace {\n\nusing m1une::graph::Graph;\nusing m1une::graph::GraphPath;\n\n\
    template <class T>\nT brute_distance(const Graph<T>& g, int s, int t, int removed_edge,\
    \ int removed_vertex, T inf) {\n    if (s == removed_vertex || t == removed_vertex)\
    \ return inf;\n    std::vector<T> dist(g.size(), inf);\n    using P = std::pair<T,\
    \ int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>> que;\n  \
    \  dist[s] = T(0);\n    que.emplace(T(0), s);\n    while (!que.empty()) {\n  \
    \      auto [d, v] = que.top();\n        que.pop();\n        if (dist[v] != d)\
    \ continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive ||\
    \ e.id == removed_edge || e.to == removed_vertex) continue;\n            T nd\
    \ = d + e.cost;\n            if (nd >= inf || dist[e.to] <= nd) continue;\n  \
    \          dist[e.to] = nd;\n            que.emplace(nd, e.to);\n        }\n \
    \   }\n    return dist[t];\n}\n\ntemplate <class T>\nvoid compare_with_brute(const\
    \ Graph<T>& g, const GraphPath& path) {\n    auto edge_result = m1une::graph::edge_replacement_paths(g,\
    \ path);\n    auto vertex_result = m1une::graph::vertex_replacement_paths(g, path);\n\
    \    assert(edge_result.path.vertices == path.vertices);\n    assert(edge_result.path.edges\
    \ == path.edges);\n    assert(vertex_result.path.vertices == path.vertices);\n\
    \    assert(vertex_result.path.edges == path.edges);\n    assert(edge_result.replacement_dist.size()\
    \ == path.edges.size());\n    assert(vertex_result.replacement_dist.size() ==\
    \ path.vertices.size());\n    for (int i = 0; i < int(path.edges.size()); i++)\
    \ {\n        T expected = brute_distance(\n            g, path.vertices.front(),\
    \ path.vertices.back(), path.edges[i], -1, edge_result.inf\n        );\n     \
    \   assert(edge_result.replacement_dist[i] == expected);\n        assert(edge_result.reachable(i)\
    \ == (expected != edge_result.inf));\n    }\n    for (int i = 0; i < int(path.vertices.size());\
    \ i++) {\n        T expected = brute_distance(\n            g, path.vertices.front(),\
    \ path.vertices.back(), -1, path.vertices[i], vertex_result.inf\n        );\n\
    \        assert(vertex_result.replacement_dist[i] == expected);\n        assert(vertex_result.reachable(i)\
    \ == (expected != vertex_result.inf));\n    }\n}\n\ntemplate <class T>\nvoid compare_automatic_with_brute(const\
    \ Graph<T>& g, int s, int t) {\n    auto edge_result = m1une::graph::edge_replacement_paths(g,\
    \ s, t);\n    auto vertex_result = m1une::graph::vertex_replacement_paths(g, s,\
    \ t);\n    assert(edge_result.path.vertices == vertex_result.path.vertices);\n\
    \    assert(edge_result.path.edges == vertex_result.path.edges);\n    compare_with_brute(g,\
    \ edge_result.path);\n    assert(edge_result.replacement_dist ==\n           m1une::graph::edge_replacement_paths(g,\
    \ edge_result.path).replacement_dist);\n    assert(vertex_result.replacement_dist\
    \ ==\n           m1une::graph::vertex_replacement_paths(g, vertex_result.path).replacement_dist);\n\
    }\n\nvoid test_only_path_and_trivial() {\n    Graph<int> g(4);\n    int e0 = g.add_edge(0,\
    \ 1, 2);\n    int e1 = g.add_edge(1, 2, 3);\n    int e2 = g.add_edge(2, 3, 4);\n\
    \    GraphPath path;\n    path.vertices = {0, 1, 2, 3};\n    path.edges = {e0,\
    \ e1, e2};\n    auto edges = m1une::graph::edge_replacement_paths(g, path);\n\
    \    auto vertices = m1une::graph::vertex_replacement_paths(g, path);\n    assert(std::all_of(edges.replacement_dist.begin(),\
    \ edges.replacement_dist.end(),\n                       [&](int x) { return x\
    \ == edges.inf; }));\n    assert(std::all_of(vertices.replacement_dist.begin(),\
    \ vertices.replacement_dist.end(),\n                       [&](int x) { return\
    \ x == vertices.inf; }));\n    compare_with_brute(g, path);\n\n    auto trivial_edges\
    \ = m1une::graph::edge_replacement_paths(g, 2, 2);\n    auto trivial_vertices\
    \ = m1une::graph::vertex_replacement_paths(g, 2, 2);\n    assert((trivial_edges.path.vertices\
    \ == std::vector<int>{2}));\n    assert(trivial_edges.path.edges.empty());\n \
    \   assert(trivial_edges.replacement_dist.empty());\n    assert((trivial_vertices.replacement_dist\
    \ == std::vector<int>{trivial_vertices.inf}));\n}\n\nvoid test_parallel_edges_and_inactive_edges()\
    \ {\n    Graph<long long> g(4);\n    int fixed = g.add_edge(0, 1, 2);\n    int\
    \ equal_parallel = g.add_edge(0, 1, 2);\n    int longer_parallel = g.add_edge(0,\
    \ 1, 5);\n    int e12 = g.add_edge(1, 2, 2);\n    int e23 = g.add_edge(2, 3, 2);\n\
    \    int inactive = g.add_edge(0, 3, 1);\n    g.erase_edge(inactive);\n    GraphPath\
    \ path;\n    path.vertices = {0, 1, 2, 3};\n    path.edges = {fixed, e12, e23};\n\
    \    auto result = m1une::graph::edge_replacement_paths(g, path);\n    assert(result.replacement_dist[0]\
    \ == 6);\n    assert(equal_parallel != fixed && longer_parallel != fixed);\n \
    \   compare_with_brute(g, path);\n}\n\nvoid test_detour_intervals_and_disconnections()\
    \ {\n    Graph<long long> g(9);\n    int e0 = g.add_edge(0, 1, 1);\n    int e1\
    \ = g.add_edge(1, 2, 1);\n    int e2 = g.add_edge(2, 3, 1);\n    int e3 = g.add_edge(3,\
    \ 4, 1);\n    g.add_edge(1, 5, 2);\n    g.add_edge(5, 2, 2);\n    g.add_edge(5,\
    \ 3, 2);\n    g.add_edge(0, 6, 4);\n    g.add_edge(6, 3, 4);\n    g.add_edge(1,\
    \ 7, 3);\n    g.add_edge(7, 4, 3);\n    g.add_edge(0, 8, 20);\n    g.add_edge(8,\
    \ 4, 20);\n    GraphPath path;\n    path.vertices = {0, 1, 2, 3, 4};\n    path.edges\
    \ = {e0, e1, e2, e3};\n    compare_with_brute(g, path);\n\n    Graph<int> bridge(5);\n\
    \    int b0 = bridge.add_edge(0, 1);\n    int b1 = bridge.add_edge(1, 2);\n  \
    \  int b2 = bridge.add_edge(2, 3);\n    int b3 = bridge.add_edge(3, 4);\n    GraphPath\
    \ bridge_path;\n    bridge_path.vertices = {0, 1, 2, 3, 4};\n    bridge_path.edges\
    \ = {b0, b1, b2, b3};\n    compare_with_brute(bridge, bridge_path);\n}\n\nvoid\
    \ test_multiple_and_external_shortest_paths() {\n    Graph<int> g(4);\n    int\
    \ e02 = g.add_edge(0, 2, 1);\n    int e23 = g.add_edge(2, 3, 1);\n    int e01\
    \ = g.add_edge(0, 1, 1);\n    int e13 = g.add_edge(1, 3, 1);\n    GraphPath through_two;\n\
    \    through_two.vertices = {0, 2, 3};\n    through_two.edges = {e02, e23};\n\
    \    GraphPath through_one;\n    through_one.vertices = {0, 1, 3};\n    through_one.edges\
    \ = {e01, e13};\n    compare_with_brute(g, through_two);\n    compare_with_brute(g,\
    \ through_one);\n    compare_automatic_with_brute(g, 0, 3);\n    auto result =\
    \ m1une::graph::edge_replacement_paths(g, through_two);\n    assert(result.replacement_dist\
    \ == std::vector<int>(2, 2));\n}\n\ntemplate <class T>\nstd::vector<GraphPath>\
    \ enumerate_shortest_paths(const Graph<T>& g, int s, int t, int limit) {\n   \
    \ auto from_s = m1une::graph::dijkstra(g, s);\n    std::vector<GraphPath> paths;\n\
    \    GraphPath current;\n    current.vertices.push_back(s);\n    std::vector<char>\
    \ used(g.size(), false);\n    used[s] = true;\n    auto dfs = [&](auto&& self,\
    \ int v) -> void {\n        if (int(paths.size()) == limit) return;\n        if\
    \ (v == t) {\n            paths.push_back(current);\n            return;\n   \
    \     }\n        for (const auto& e : g[v]) {\n            if (!e.alive || used[e.to])\
    \ continue;\n            if (from_s.dist[v] + e.cost != from_s.dist[e.to]) continue;\n\
    \            used[e.to] = true;\n            current.vertices.push_back(e.to);\n\
    \            current.edges.push_back(e.id);\n            self(self, e.to);\n \
    \           current.edges.pop_back();\n            current.vertices.pop_back();\n\
    \            used[e.to] = false;\n        }\n    };\n    dfs(dfs, s);\n    return\
    \ paths;\n}\n\nvoid test_randomized() {\n    std::mt19937 rng(712367821);\n  \
    \  for (int iteration = 0; iteration < 1500; iteration++) {\n        int n = 2\
    \ + int(rng() % 7);\n        Graph<long long> g(n);\n        int attempts = int(rng()\
    \ % 22);\n        for (int i = 0; i < attempts; i++) {\n            int u = int(rng()\
    \ % n);\n            int v = int(rng() % n);\n            if (u == v) continue;\n\
    \            int id = g.add_edge(u, v, 1 + int(rng() % 10));\n            if (rng()\
    \ % 13 == 0) g.erase_edge(id);\n        }\n        int s = int(rng() % n);\n \
    \       int t = int(rng() % n);\n        if (s == t) t = (t + 1) % n;\n      \
    \  auto shortest = m1une::graph::dijkstra(g, s);\n        if (!shortest.reachable(t))\
    \ continue;\n        compare_automatic_with_brute(g, s, t);\n        auto paths\
    \ = enumerate_shortest_paths(g, s, t, 5);\n        assert(!paths.empty());\n \
    \       for (const auto& path : paths) compare_with_brute(g, path);\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_only_path_and_trivial();\n\
    \    test_parallel_edges_and_inactive_edges();\n    test_detour_intervals_and_disconnections();\n\
    \    test_multiple_and_external_shortest_paths();\n    test_randomized();\n\n\
    \    int a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include \"../../utilities/fast_io.hpp\"\
    \n#include <limits>\n#include <queue>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../graph/replacement_paths.hpp\"\n\nnamespace\
    \ {\n\nusing m1une::graph::Graph;\nusing m1une::graph::GraphPath;\n\ntemplate\
    \ <class T>\nT brute_distance(const Graph<T>& g, int s, int t, int removed_edge,\
    \ int removed_vertex, T inf) {\n    if (s == removed_vertex || t == removed_vertex)\
    \ return inf;\n    std::vector<T> dist(g.size(), inf);\n    using P = std::pair<T,\
    \ int>;\n    std::priority_queue<P, std::vector<P>, std::greater<P>> que;\n  \
    \  dist[s] = T(0);\n    que.emplace(T(0), s);\n    while (!que.empty()) {\n  \
    \      auto [d, v] = que.top();\n        que.pop();\n        if (dist[v] != d)\
    \ continue;\n        for (const auto& e : g[v]) {\n            if (!e.alive ||\
    \ e.id == removed_edge || e.to == removed_vertex) continue;\n            T nd\
    \ = d + e.cost;\n            if (nd >= inf || dist[e.to] <= nd) continue;\n  \
    \          dist[e.to] = nd;\n            que.emplace(nd, e.to);\n        }\n \
    \   }\n    return dist[t];\n}\n\ntemplate <class T>\nvoid compare_with_brute(const\
    \ Graph<T>& g, const GraphPath& path) {\n    auto edge_result = m1une::graph::edge_replacement_paths(g,\
    \ path);\n    auto vertex_result = m1une::graph::vertex_replacement_paths(g, path);\n\
    \    assert(edge_result.path.vertices == path.vertices);\n    assert(edge_result.path.edges\
    \ == path.edges);\n    assert(vertex_result.path.vertices == path.vertices);\n\
    \    assert(vertex_result.path.edges == path.edges);\n    assert(edge_result.replacement_dist.size()\
    \ == path.edges.size());\n    assert(vertex_result.replacement_dist.size() ==\
    \ path.vertices.size());\n    for (int i = 0; i < int(path.edges.size()); i++)\
    \ {\n        T expected = brute_distance(\n            g, path.vertices.front(),\
    \ path.vertices.back(), path.edges[i], -1, edge_result.inf\n        );\n     \
    \   assert(edge_result.replacement_dist[i] == expected);\n        assert(edge_result.reachable(i)\
    \ == (expected != edge_result.inf));\n    }\n    for (int i = 0; i < int(path.vertices.size());\
    \ i++) {\n        T expected = brute_distance(\n            g, path.vertices.front(),\
    \ path.vertices.back(), -1, path.vertices[i], vertex_result.inf\n        );\n\
    \        assert(vertex_result.replacement_dist[i] == expected);\n        assert(vertex_result.reachable(i)\
    \ == (expected != vertex_result.inf));\n    }\n}\n\ntemplate <class T>\nvoid compare_automatic_with_brute(const\
    \ Graph<T>& g, int s, int t) {\n    auto edge_result = m1une::graph::edge_replacement_paths(g,\
    \ s, t);\n    auto vertex_result = m1une::graph::vertex_replacement_paths(g, s,\
    \ t);\n    assert(edge_result.path.vertices == vertex_result.path.vertices);\n\
    \    assert(edge_result.path.edges == vertex_result.path.edges);\n    compare_with_brute(g,\
    \ edge_result.path);\n    assert(edge_result.replacement_dist ==\n           m1une::graph::edge_replacement_paths(g,\
    \ edge_result.path).replacement_dist);\n    assert(vertex_result.replacement_dist\
    \ ==\n           m1une::graph::vertex_replacement_paths(g, vertex_result.path).replacement_dist);\n\
    }\n\nvoid test_only_path_and_trivial() {\n    Graph<int> g(4);\n    int e0 = g.add_edge(0,\
    \ 1, 2);\n    int e1 = g.add_edge(1, 2, 3);\n    int e2 = g.add_edge(2, 3, 4);\n\
    \    GraphPath path;\n    path.vertices = {0, 1, 2, 3};\n    path.edges = {e0,\
    \ e1, e2};\n    auto edges = m1une::graph::edge_replacement_paths(g, path);\n\
    \    auto vertices = m1une::graph::vertex_replacement_paths(g, path);\n    assert(std::all_of(edges.replacement_dist.begin(),\
    \ edges.replacement_dist.end(),\n                       [&](int x) { return x\
    \ == edges.inf; }));\n    assert(std::all_of(vertices.replacement_dist.begin(),\
    \ vertices.replacement_dist.end(),\n                       [&](int x) { return\
    \ x == vertices.inf; }));\n    compare_with_brute(g, path);\n\n    auto trivial_edges\
    \ = m1une::graph::edge_replacement_paths(g, 2, 2);\n    auto trivial_vertices\
    \ = m1une::graph::vertex_replacement_paths(g, 2, 2);\n    assert((trivial_edges.path.vertices\
    \ == std::vector<int>{2}));\n    assert(trivial_edges.path.edges.empty());\n \
    \   assert(trivial_edges.replacement_dist.empty());\n    assert((trivial_vertices.replacement_dist\
    \ == std::vector<int>{trivial_vertices.inf}));\n}\n\nvoid test_parallel_edges_and_inactive_edges()\
    \ {\n    Graph<long long> g(4);\n    int fixed = g.add_edge(0, 1, 2);\n    int\
    \ equal_parallel = g.add_edge(0, 1, 2);\n    int longer_parallel = g.add_edge(0,\
    \ 1, 5);\n    int e12 = g.add_edge(1, 2, 2);\n    int e23 = g.add_edge(2, 3, 2);\n\
    \    int inactive = g.add_edge(0, 3, 1);\n    g.erase_edge(inactive);\n    GraphPath\
    \ path;\n    path.vertices = {0, 1, 2, 3};\n    path.edges = {fixed, e12, e23};\n\
    \    auto result = m1une::graph::edge_replacement_paths(g, path);\n    assert(result.replacement_dist[0]\
    \ == 6);\n    assert(equal_parallel != fixed && longer_parallel != fixed);\n \
    \   compare_with_brute(g, path);\n}\n\nvoid test_detour_intervals_and_disconnections()\
    \ {\n    Graph<long long> g(9);\n    int e0 = g.add_edge(0, 1, 1);\n    int e1\
    \ = g.add_edge(1, 2, 1);\n    int e2 = g.add_edge(2, 3, 1);\n    int e3 = g.add_edge(3,\
    \ 4, 1);\n    g.add_edge(1, 5, 2);\n    g.add_edge(5, 2, 2);\n    g.add_edge(5,\
    \ 3, 2);\n    g.add_edge(0, 6, 4);\n    g.add_edge(6, 3, 4);\n    g.add_edge(1,\
    \ 7, 3);\n    g.add_edge(7, 4, 3);\n    g.add_edge(0, 8, 20);\n    g.add_edge(8,\
    \ 4, 20);\n    GraphPath path;\n    path.vertices = {0, 1, 2, 3, 4};\n    path.edges\
    \ = {e0, e1, e2, e3};\n    compare_with_brute(g, path);\n\n    Graph<int> bridge(5);\n\
    \    int b0 = bridge.add_edge(0, 1);\n    int b1 = bridge.add_edge(1, 2);\n  \
    \  int b2 = bridge.add_edge(2, 3);\n    int b3 = bridge.add_edge(3, 4);\n    GraphPath\
    \ bridge_path;\n    bridge_path.vertices = {0, 1, 2, 3, 4};\n    bridge_path.edges\
    \ = {b0, b1, b2, b3};\n    compare_with_brute(bridge, bridge_path);\n}\n\nvoid\
    \ test_multiple_and_external_shortest_paths() {\n    Graph<int> g(4);\n    int\
    \ e02 = g.add_edge(0, 2, 1);\n    int e23 = g.add_edge(2, 3, 1);\n    int e01\
    \ = g.add_edge(0, 1, 1);\n    int e13 = g.add_edge(1, 3, 1);\n    GraphPath through_two;\n\
    \    through_two.vertices = {0, 2, 3};\n    through_two.edges = {e02, e23};\n\
    \    GraphPath through_one;\n    through_one.vertices = {0, 1, 3};\n    through_one.edges\
    \ = {e01, e13};\n    compare_with_brute(g, through_two);\n    compare_with_brute(g,\
    \ through_one);\n    compare_automatic_with_brute(g, 0, 3);\n    auto result =\
    \ m1une::graph::edge_replacement_paths(g, through_two);\n    assert(result.replacement_dist\
    \ == std::vector<int>(2, 2));\n}\n\ntemplate <class T>\nstd::vector<GraphPath>\
    \ enumerate_shortest_paths(const Graph<T>& g, int s, int t, int limit) {\n   \
    \ auto from_s = m1une::graph::dijkstra(g, s);\n    std::vector<GraphPath> paths;\n\
    \    GraphPath current;\n    current.vertices.push_back(s);\n    std::vector<char>\
    \ used(g.size(), false);\n    used[s] = true;\n    auto dfs = [&](auto&& self,\
    \ int v) -> void {\n        if (int(paths.size()) == limit) return;\n        if\
    \ (v == t) {\n            paths.push_back(current);\n            return;\n   \
    \     }\n        for (const auto& e : g[v]) {\n            if (!e.alive || used[e.to])\
    \ continue;\n            if (from_s.dist[v] + e.cost != from_s.dist[e.to]) continue;\n\
    \            used[e.to] = true;\n            current.vertices.push_back(e.to);\n\
    \            current.edges.push_back(e.id);\n            self(self, e.to);\n \
    \           current.edges.pop_back();\n            current.vertices.pop_back();\n\
    \            used[e.to] = false;\n        }\n    };\n    dfs(dfs, s);\n    return\
    \ paths;\n}\n\nvoid test_randomized() {\n    std::mt19937 rng(712367821);\n  \
    \  for (int iteration = 0; iteration < 1500; iteration++) {\n        int n = 2\
    \ + int(rng() % 7);\n        Graph<long long> g(n);\n        int attempts = int(rng()\
    \ % 22);\n        for (int i = 0; i < attempts; i++) {\n            int u = int(rng()\
    \ % n);\n            int v = int(rng() % n);\n            if (u == v) continue;\n\
    \            int id = g.add_edge(u, v, 1 + int(rng() % 10));\n            if (rng()\
    \ % 13 == 0) g.erase_edge(id);\n        }\n        int s = int(rng() % n);\n \
    \       int t = int(rng() % n);\n        if (s == t) t = (t + 1) % n;\n      \
    \  auto shortest = m1une::graph::dijkstra(g, s);\n        if (!shortest.reachable(t))\
    \ continue;\n        compare_automatic_with_brute(g, s, t);\n        auto paths\
    \ = enumerate_shortest_paths(g, s, t, 5);\n        assert(!paths.empty());\n \
    \       for (const auto& path : paths) compare_with_brute(g, path);\n    }\n}\n\
    \n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_only_path_and_trivial();\n\
    \    test_parallel_edges_and_inactive_edges();\n    test_detour_intervals_and_disconnections();\n\
    \    test_multiple_and_external_shortest_paths();\n    test_randomized();\n\n\
    \    int a, b;\n    fast_input >> a >> b;\n    fast_output << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - utilities/fast_io.hpp
  - graph/replacement_paths.hpp
  - graph/dijkstra.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/replacement_paths.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/replacement_paths.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/replacement_paths.test.cpp
- /verify/verify/graph/replacement_paths.test.cpp.html
title: verify/graph/replacement_paths.test.cpp
---
