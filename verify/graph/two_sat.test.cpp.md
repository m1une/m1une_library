---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/two_sat.hpp
    title: Two-Satisfiability
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
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"verify/graph/two_sat.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\
    \n\n#line 1 \"graph/two_sat.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace graph {\n\n// A 2-SAT solver using iterative strongly connected components.\n\
    struct TwoSat {\n   private:\n    struct Csr {\n        std::vector<int> start;\n\
    \        std::vector<int> to;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _edges;\n    bool _solved;\n    bool _satisfiable;\n    std::vector<bool>\
    \ _answer;\n\n    int node(int variable, bool value) const {\n        assert(0\
    \ <= variable && variable < _n);\n        return 2 * variable + int(value);\n\
    \    }\n\n    void add_edge(int from, int to) {\n        _edges.emplace_back(from,\
    \ to);\n        _solved = false;\n        _answer.clear();\n    }\n\n    Csr build_csr(bool\
    \ reverse) const {\n        int vertices = 2 * _n;\n        Csr graph;\n     \
    \   graph.start.assign(vertices + 1, 0);\n        graph.to.resize(_edges.size());\n\
    \n        for (auto [from, to] : _edges) {\n            int source = reverse ?\
    \ to : from;\n            graph.start[source + 1]++;\n        }\n        for (int\
    \ v = 0; v < vertices; v++) {\n            graph.start[v + 1] += graph.start[v];\n\
    \        }\n\n        std::vector<int> cursor = graph.start;\n        for (auto\
    \ [from, to] : _edges) {\n            int source = reverse ? to : from;\n    \
    \        int target = reverse ? from : to;\n            graph.to[cursor[source]++]\
    \ = target;\n        }\n        return graph;\n    }\n\n   public:\n    TwoSat()\
    \ : TwoSat(0) {}\n\n    explicit TwoSat(int n)\n        : _n(n), _solved(false),\
    \ _satisfiable(false) {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/two_sat.test.cpp\"\
    \n\n#line 6 \"verify/graph/two_sat.test.cpp\"\n#include <cstdint>\n#include <cstdlib>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
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
    \ m1une\n\n\n#line 9 \"verify/graph/two_sat.test.cpp\"\n#include <tuple>\n#line\
    \ 11 \"verify/graph/two_sat.test.cpp\"\n\nnamespace {\n\nstruct Clause {\n   \
    \ int i;\n    bool f;\n    int j;\n    bool g;\n};\n\nbool satisfies(const std::vector<bool>&\
    \ assignment, const Clause& clause) {\n    return assignment[clause.i] == clause.f\
    \ ||\n           assignment[clause.j] == clause.g;\n}\n\nvoid test_helpers() {\n\
    \    m1une::graph::TwoSat sat(4);\n    assert(sat.size() == 4);\n    assert(!sat.empty());\n\
    \    sat.reserve(8);\n\n    sat.set_value(0, true);\n    sat.add_implication(0,\
    \ true, 1, false);\n    sat.add_equal(1, 2);\n    sat.add_not_equal(2, 3);\n \
    \   assert(sat.satisfiable());\n    assert(sat.satisfiable());\n    assert(sat.value(0));\n\
    \    assert(!sat.value(1));\n    assert(!sat.value(2));\n    assert(sat.value(3));\n\
    \n    sat.set_value(3, false);\n    assert(!sat.satisfiable());\n\n    m1une::graph::TwoSat\
    \ empty;\n    assert(empty.empty());\n    assert(empty.satisfiable());\n    assert(empty.answer().empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 29;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int n = int(random() % 8);\n        int m = n == 0 ? 0 : int(random()\
    \ % 24);\n        m1une::graph::TwoSat sat(n);\n        sat.reserve(std::size_t(m));\n\
    \        std::vector<Clause> clauses;\n\n        for (int edge = 0; edge < m;\
    \ edge++) {\n            Clause clause;\n            clause.i = int(random() %\
    \ std::uint64_t(n));\n            clause.f = bool(random() & 1);\n           \
    \ clause.j = int(random() % std::uint64_t(n));\n            clause.g = bool(random()\
    \ & 1);\n            clauses.push_back(clause);\n            sat.add_clause(clause.i,\
    \ clause.f, clause.j, clause.g);\n        }\n\n        bool expected = false;\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<bool>\
    \ assignment(n);\n            for (int i = 0; i < n; i++) assignment[i] = (mask\
    \ >> i) & 1;\n\n            bool valid = true;\n            for (const Clause&\
    \ clause : clauses) {\n                if (!satisfies(assignment, clause)) {\n\
    \                    valid = false;\n                    break;\n            \
    \    }\n            }\n            if (valid) {\n                expected = true;\n\
    \                break;\n            }\n        }\n\n        assert(sat.satisfiable()\
    \ == expected);\n        if (expected) {\n            [[maybe_unused]] const std::vector<bool>&\
    \ assignment = sat.answer();\n            assert(int(assignment.size()) == n);\n\
    \            for ([[maybe_unused]] const Clause& clause : clauses) {\n       \
    \         assert(satisfies(assignment, clause));\n            }\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_helpers();\n    test_randomized();\n\
    \n    char p;\n    std::string cnf;\n    int n, m;\n    fast_input >> p >> cnf\
    \ >> n >> m;\n\n    m1une::graph::TwoSat sat(n);\n    sat.reserve(std::size_t(m));\n\
    \    for (int clause = 0; clause < m; clause++) {\n        int a, b, zero;\n \
    \       fast_input >> a >> b >> zero;\n        assert(zero == 0);\n        sat.add_clause(std::abs(a)\
    \ - 1, 0 < a, std::abs(b) - 1, 0 < b);\n    }\n\n    if (!sat.satisfiable()) {\n\
    \        fast_output << \"s UNSATISFIABLE\\n\";\n        return 0;\n    }\n\n\
    \    fast_output << \"s SATISFIABLE\\n\";\n    fast_output << \"v\";\n    const\
    \ std::vector<bool>& answer = sat.answer();\n    for (int i = 0; i < n; i++) {\n\
    \        fast_output << \" \" << (answer[i] ? i + 1 : -(i + 1));\n    }\n    fast_output\
    \ << \" 0\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n\n#include \"\
    ../../graph/two_sat.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <cstdlib>\n#include \"../../utilities/fast_io.hpp\"\n#include <tuple>\n#include\
    \ <vector>\n\nnamespace {\n\nstruct Clause {\n    int i;\n    bool f;\n    int\
    \ j;\n    bool g;\n};\n\nbool satisfies(const std::vector<bool>& assignment, const\
    \ Clause& clause) {\n    return assignment[clause.i] == clause.f ||\n        \
    \   assignment[clause.j] == clause.g;\n}\n\nvoid test_helpers() {\n    m1une::graph::TwoSat\
    \ sat(4);\n    assert(sat.size() == 4);\n    assert(!sat.empty());\n    sat.reserve(8);\n\
    \n    sat.set_value(0, true);\n    sat.add_implication(0, true, 1, false);\n \
    \   sat.add_equal(1, 2);\n    sat.add_not_equal(2, 3);\n    assert(sat.satisfiable());\n\
    \    assert(sat.satisfiable());\n    assert(sat.value(0));\n    assert(!sat.value(1));\n\
    \    assert(!sat.value(2));\n    assert(sat.value(3));\n\n    sat.set_value(3,\
    \ false);\n    assert(!sat.satisfiable());\n\n    m1une::graph::TwoSat empty;\n\
    \    assert(empty.empty());\n    assert(empty.satisfiable());\n    assert(empty.answer().empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 29;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int n = int(random() % 8);\n        int m = n == 0 ? 0 : int(random()\
    \ % 24);\n        m1une::graph::TwoSat sat(n);\n        sat.reserve(std::size_t(m));\n\
    \        std::vector<Clause> clauses;\n\n        for (int edge = 0; edge < m;\
    \ edge++) {\n            Clause clause;\n            clause.i = int(random() %\
    \ std::uint64_t(n));\n            clause.f = bool(random() & 1);\n           \
    \ clause.j = int(random() % std::uint64_t(n));\n            clause.g = bool(random()\
    \ & 1);\n            clauses.push_back(clause);\n            sat.add_clause(clause.i,\
    \ clause.f, clause.j, clause.g);\n        }\n\n        bool expected = false;\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<bool>\
    \ assignment(n);\n            for (int i = 0; i < n; i++) assignment[i] = (mask\
    \ >> i) & 1;\n\n            bool valid = true;\n            for (const Clause&\
    \ clause : clauses) {\n                if (!satisfies(assignment, clause)) {\n\
    \                    valid = false;\n                    break;\n            \
    \    }\n            }\n            if (valid) {\n                expected = true;\n\
    \                break;\n            }\n        }\n\n        assert(sat.satisfiable()\
    \ == expected);\n        if (expected) {\n            [[maybe_unused]] const std::vector<bool>&\
    \ assignment = sat.answer();\n            assert(int(assignment.size()) == n);\n\
    \            for ([[maybe_unused]] const Clause& clause : clauses) {\n       \
    \         assert(satisfies(assignment, clause));\n            }\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_helpers();\n    test_randomized();\n\
    \n    char p;\n    std::string cnf;\n    int n, m;\n    fast_input >> p >> cnf\
    \ >> n >> m;\n\n    m1une::graph::TwoSat sat(n);\n    sat.reserve(std::size_t(m));\n\
    \    for (int clause = 0; clause < m; clause++) {\n        int a, b, zero;\n \
    \       fast_input >> a >> b >> zero;\n        assert(zero == 0);\n        sat.add_clause(std::abs(a)\
    \ - 1, 0 < a, std::abs(b) - 1, 0 < b);\n    }\n\n    if (!sat.satisfiable()) {\n\
    \        fast_output << \"s UNSATISFIABLE\\n\";\n        return 0;\n    }\n\n\
    \    fast_output << \"s SATISFIABLE\\n\";\n    fast_output << \"v\";\n    const\
    \ std::vector<bool>& answer = sat.answer();\n    for (int i = 0; i < n; i++) {\n\
    \        fast_output << \" \" << (answer[i] ? i + 1 : -(i + 1));\n    }\n    fast_output\
    \ << \" 0\\n\";\n}\n"
  dependsOn:
  - graph/two_sat.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/two_sat.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/two_sat.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/two_sat.test.cpp
- /verify/verify/graph/two_sat.test.cpp.html
title: verify/graph/two_sat.test.cpp
---
