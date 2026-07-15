---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/max_flow.hpp
    title: Max Flow
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A
  bundledCode: "#line 1 \"verify/graph/flow/max_flow.test.cpp\"\n#define PROBLEM \"\
    https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A\"\n\n#line 1 \"graph/flow/max_flow.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <limits>\n#include <vector>\n\nnamespace m1une {\nnamespace flow {\n\ntemplate\
    \ <class Cap>\nstruct MaxFlow {\n    struct Edge {\n        int from;\n      \
    \  int to;\n        Cap cap;\n        Cap flow;\n    };\n\n   private:\n    struct\
    \ InternalEdge {\n        int to;\n        int rev;\n        Cap cap;\n    };\n\
    \n    struct Position {\n        int from;\n        int edge;\n    };\n\n    int\
    \ _n;\n    std::vector<Position> _pos;\n    std::vector<std::vector<InternalEdge>>\
    \ _g;\n\n   public:\n    MaxFlow() : MaxFlow(0) {}\n\n    explicit MaxFlow(int\
    \ n) : _n(n), _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int edge_count() const {\n        return\
    \ int(_pos.size());\n    }\n\n    void reserve_edges(int edge_count) {\n     \
    \   assert(0 <= edge_count);\n        _pos.reserve(edge_count);\n        if (_n\
    \ == 0 || edge_count == 0 ||\n            2 * std::size_t(edge_count) < std::size_t(_n))\
    \ {\n            return;\n        }\n        const std::size_t average_degree\
    \ =\n            (2 * std::size_t(edge_count) + std::size_t(_n) - 1)\n       \
    \     / std::size_t(_n);\n        for (auto& edges : _g) edges.reserve(average_degree);\n\
    \    }\n\n    int add_edge(int from, int to, Cap cap) {\n        assert(0 <= from\
    \ && from < _n);\n        assert(0 <= to && to < _n);\n        assert(Cap(0) <=\
    \ cap);\n        int id = int(_pos.size());\n        int from_id = int(_g[from].size());\n\
    \        int to_id = int(_g[to].size());\n        if (from == to) to_id++;\n \
    \       _pos.push_back(Position{from, from_id});\n        _g[from].push_back(InternalEdge{to,\
    \ to_id, cap});\n        _g[to].push_back(InternalEdge{from, from_id, Cap(0)});\n\
    \        return id;\n    }\n\n    int add_undirected_edge(int first, int second,\
    \ Cap cap) {\n        static_assert(std::numeric_limits<Cap>::is_signed);\n  \
    \      assert(0 <= first && first < _n);\n        assert(0 <= second && second\
    \ < _n);\n        assert(Cap(0) <= cap);\n        assert(cap <= std::numeric_limits<Cap>::max()\
    \ / Cap(2));\n        int id = int(_pos.size());\n        int first_id = int(_g[first].size());\n\
    \        int second_id = int(_g[second].size());\n        if (first == second)\
    \ second_id++;\n        _pos.push_back(Position{first, ~first_id});\n        _g[first].push_back(InternalEdge{second,\
    \ second_id, cap});\n        _g[second].push_back(InternalEdge{first, first_id,\
    \ cap});\n        return id;\n    }\n\n    Edge get_edge(int i) const {\n    \
    \    assert(0 <= i && i < int(_pos.size()));\n        const auto& position = _pos[i];\n\
    \        int from = position.from;\n        bool undirected = position.edge <\
    \ 0;\n        int idx = undirected ? ~position.edge : position.edge;\n       \
    \ const auto& e = _g[from][idx];\n        const auto& re = _g[e.to][e.rev];\n\
    \        if (undirected) {\n            return Edge{\n                from,\n\
    \                e.to,\n                (e.cap + re.cap) / Cap(2),\n         \
    \       (re.cap - e.cap) / Cap(2)\n            };\n        }\n        return Edge{from,\
    \ e.to, e.cap + re.cap, re.cap};\n    }\n\n    std::vector<Edge> edges() const\
    \ {\n        std::vector<Edge> result;\n        result.reserve(_pos.size());\n\
    \        for (int i = 0; i < int(_pos.size()); i++) result.push_back(get_edge(i));\n\
    \        return result;\n    }\n\n    void change_edge(int i, Cap new_cap, Cap\
    \ new_flow) {\n        assert(0 <= i && i < int(_pos.size()));\n        assert(Cap(0)\
    \ <= new_cap);\n        auto& position = _pos[i];\n        int from = position.from;\n\
    \        bool undirected = position.edge < 0;\n        int idx = undirected ?\
    \ ~position.edge : position.edge;\n        auto& e = _g[from][idx];\n        auto&\
    \ re = _g[e.to][e.rev];\n        if (undirected) {\n            assert(new_cap\
    \ <= std::numeric_limits<Cap>::max() / Cap(2));\n            assert(-new_cap <=\
    \ new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_cap + new_flow;\n        } else {\n            assert(Cap(0)\
    \ <= new_flow && new_flow <= new_cap);\n            e.cap = new_cap - new_flow;\n\
    \            re.cap = new_flow;\n        }\n    }\n\n    Cap max_flow(int s, int\
    \ t) {\n        return max_flow(s, t, std::numeric_limits<Cap>::max());\n    }\n\
    \n    Cap max_flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   std::vector<int> work(3 * std::size_t(_n));\n        int* level = work.data();\n\
    \        int* iter = level + _n;\n        int* queue = iter + _n;\n        auto\
    \ bfs = [&]() -> bool {\n            std::fill(level, level + _n, -1);\n     \
    \       int head = 0;\n            int tail = 0;\n            level[s] = 0;\n\
    \            queue[tail++] = s;\n            while (head != tail) {\n        \
    \        int v = queue[head++];\n                for (const auto& e : _g[v]) {\n\
    \                    if (e.cap == Cap(0) || level[e.to] != -1) continue;\n   \
    \                 level[e.to] = level[v] + 1;\n                    if (e.to ==\
    \ t) return true;\n                    queue[tail++] = e.to;\n               \
    \ }\n            }\n            return level[t] != -1;\n        };\n\n       \
    \ auto dfs = [&](auto&& self, int v, Cap up) -> Cap {\n            if (v == s)\
    \ return up;\n            Cap result = Cap(0);\n            const int current_level\
    \ = level[v];\n            for (int& i = iter[v]; i < int(_g[v].size()); i++)\
    \ {\n                auto& e = _g[v][i];\n                if (current_level <=\
    \ level[e.to]) continue;\n                auto& reverse = _g[e.to][e.rev];\n \
    \               if (reverse.cap == Cap(0)) continue;\n                Cap d =\
    \ self(\n                    self,\n                    e.to,\n              \
    \      std::min(up - result, reverse.cap)\n                );\n              \
    \  if (d == Cap(0)) continue;\n                e.cap += d;\n                reverse.cap\
    \ -= d;\n                result += d;\n                if (result == up) return\
    \ result;\n            }\n            level[v] = _n;\n            return result;\n\
    \        };\n\n        Cap flow = 0;\n        while (flow < flow_limit && bfs())\
    \ {\n            std::fill(iter, iter + _n, 0);\n            flow += dfs(dfs,\
    \ t, flow_limit - flow);\n        }\n        return flow;\n    }\n\n    std::vector<bool>\
    \ min_cut(int s) const {\n        assert(0 <= s && s < _n);\n        std::vector<bool>\
    \ visited(_n, false);\n        std::vector<int> queue(_n);\n        int head =\
    \ 0;\n        int tail = 0;\n        visited[s] = true;\n        queue[tail++]\
    \ = s;\n        while (head != tail) {\n            int v = queue[head++];\n \
    \           for (const auto& e : _g[v]) {\n                if (e.cap == Cap(0)\
    \ || visited[e.to]) continue;\n                visited[e.to] = true;\n       \
    \         queue[tail++] = e.to;\n            }\n        }\n        return visited;\n\
    \    }\n};\n\n}  // namespace flow\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#include <cstdint>\n#include <cstring>\n\
    #include <iterator>\n#include <string>\n#include <type_traits>\n#include <utility>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
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
    \ m1une\n\n\n#line 5 \"verify/graph/flow/max_flow.test.cpp\"\n\nint main() {\n\
    \    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int vertex_count, edge_count;\n    input >> vertex_count >> edge_count;\n\
    \    m1une::flow::MaxFlow<long long> flow(vertex_count);\n    flow.reserve_edges(edge_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        long long capacity;\n        input >> from >> to >> capacity;\n     \
    \   flow.add_edge(from, to, capacity);\n    }\n    output << flow.max_flow(0,\
    \ vertex_count - 1) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A\"\n\n\
    #include \"../../../graph/flow/max_flow.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int vertex_count, edge_count;\n    input >> vertex_count >> edge_count;\n\
    \    m1une::flow::MaxFlow<long long> flow(vertex_count);\n    flow.reserve_edges(edge_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        long long capacity;\n        input >> from >> to >> capacity;\n     \
    \   flow.add_edge(from, to, capacity);\n    }\n    output << flow.max_flow(0,\
    \ vertex_count - 1) << '\\n';\n}\n"
  dependsOn:
  - graph/flow/max_flow.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/flow/max_flow.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 21:34:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/flow/max_flow.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/flow/max_flow.test.cpp
- /verify/verify/graph/flow/max_flow.test.cpp.html
title: verify/graph/flow/max_flow.test.cpp
---
