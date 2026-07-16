---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/st_numbering.hpp
    title: st-Numbering
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
    PROBLEM: https://judge.yosupo.jp/problem/st_numbering
    links:
    - https://judge.yosupo.jp/problem/st_numbering
  bundledCode: "#line 1 \"verify/graph/st_numbering.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/st_numbering\"\n\n#line 1 \"graph/st_numbering.hpp\"\
    \n\n\n\n#include <cassert>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\
    \n\n\n#line 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 8 \"graph/st_numbering.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\n// Returns ranks p with p[source] = 0 and p[sink] = n - 1 such that\
    \ every\n// other vertex has neighbors of both smaller and larger rank. Returns\
    \ an empty\n// vector when no such numbering exists.\ntemplate <class T>\nstd::vector<int>\
    \ st_numbering(\n    const Graph<T>& graph,\n    int source,\n    int sink\n)\
    \ {\n    const int n = graph.size();\n    assert(0 < n);\n    assert(0 <= source\
    \ && source < n);\n    assert(0 <= sink && sink < n);\n    assert(source != sink);\n\
    \n#ifndef NDEBUG\n    std::vector<int> incidence_count(graph.edge_count(), 0);\n\
    \    for (int vertex = 0; vertex < n; vertex++) {\n        for (const Edge<T>&\
    \ edge : graph[vertex]) {\n            if (!edge.alive) continue;\n          \
    \  assert(0 <= edge.id && edge.id < graph.edge_count());\n            incidence_count[edge.id]++;\n\
    \        }\n    }\n    for (int edge_id = 0; edge_id < graph.edge_count(); edge_id++)\
    \ {\n        if (graph.is_edge_alive(edge_id)) {\n            assert(incidence_count[edge_id]\
    \ == 2);\n        }\n    }\n#endif\n\n    std::vector<int> parent(n, -1);\n  \
    \  std::vector<int> preorder(n, -1);\n    std::vector<int> low_vertex(n, -1);\n\
    \    std::vector<int> next_edge(n, 0);\n    std::vector<int> traversal;\n    traversal.reserve(n);\n\
    \n    preorder[source] = 0;\n    low_vertex[source] = source;\n    traversal.push_back(source);\n\
    \    preorder[sink] = 1;\n    low_vertex[sink] = sink;\n    traversal.push_back(sink);\n\
    \n    std::vector<int> stack(1, sink);\n    while (!stack.empty()) {\n       \
    \ const int vertex = stack.back();\n        if (next_edge[vertex] < int(graph[vertex].size()))\
    \ {\n            const Edge<T>& edge = graph[vertex][next_edge[vertex]++];\n \
    \           if (!edge.alive || edge.to == vertex) continue;\n            const\
    \ int to = edge.to;\n            if (preorder[to] == -1) {\n                parent[to]\
    \ = vertex;\n                preorder[to] = int(traversal.size());\n         \
    \       low_vertex[to] = to;\n                traversal.push_back(to);\n     \
    \           stack.push_back(to);\n            } else if (preorder[to] < preorder[low_vertex[vertex]])\
    \ {\n                low_vertex[vertex] = to;\n            }\n            continue;\n\
    \        }\n\n        stack.pop_back();\n        const int parent_vertex = parent[vertex];\n\
    \        if (parent_vertex != -1 &&\n            preorder[low_vertex[vertex]]\
    \ <\n                preorder[low_vertex[parent_vertex]]) {\n            low_vertex[parent_vertex]\
    \ = low_vertex[vertex];\n        }\n    }\n    if (int(traversal.size()) != n)\
    \ return {};\n\n    std::vector<int> next(n, -1);\n    std::vector<int> previous(n,\
    \ -1);\n    std::vector<int> sign(n, 0);\n    next[source] = sink;\n    previous[sink]\
    \ = source;\n    sign[source] = -1;\n\n    for (int index = 2; index < n; index++)\
    \ {\n        const int vertex = traversal[index];\n        const int parent_vertex\
    \ = parent[vertex];\n        assert(parent_vertex != -1);\n        if (sign[low_vertex[vertex]]\
    \ == -1) {\n            const int before = previous[parent_vertex];\n        \
    \    if (before == -1) return {};\n            next[before] = vertex;\n      \
    \      next[vertex] = parent_vertex;\n            previous[vertex] = before;\n\
    \            previous[parent_vertex] = vertex;\n            sign[parent_vertex]\
    \ = 1;\n        } else {\n            const int after = next[parent_vertex];\n\
    \            if (after == -1) return {};\n            next[parent_vertex] = vertex;\n\
    \            next[vertex] = after;\n            previous[vertex] = parent_vertex;\n\
    \            previous[after] = vertex;\n            sign[parent_vertex] = -1;\n\
    \        }\n    }\n\n    std::vector<int> order;\n    order.reserve(n);\n    int\
    \ vertex = source;\n    while (vertex != -1 && int(order.size()) <= n) {\n   \
    \     order.push_back(vertex);\n        if (vertex == sink) break;\n        vertex\
    \ = next[vertex];\n    }\n    if (int(order.size()) != n || order.back() != sink)\
    \ return {};\n\n    std::vector<int> rank(n, -1);\n    for (int index = 0; index\
    \ < n; index++) rank[order[index]] = index;\n\n    for (int index = 0; index <\
    \ n; index++) {\n        const int current = order[index];\n        bool has_smaller\
    \ = false;\n        bool has_larger = false;\n        for (const Edge<T>& edge\
    \ : graph[current]) {\n            if (!edge.alive || edge.to == current) continue;\n\
    \            has_smaller = has_smaller || rank[edge.to] < index;\n           \
    \ has_larger = has_larger || index < rank[edge.to];\n        }\n        if (index\
    \ > 0 && !has_smaller) return {};\n        if (index + 1 < n && !has_larger) return\
    \ {};\n    }\n    return rank;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/graph/st_numbering.test.cpp\"\n\n#include <algorithm>\n#line\
    \ 7 \"verify/graph/st_numbering.test.cpp\"\n#include <cstdint>\n#include <numeric>\n\
    #line 10 \"verify/graph/st_numbering.test.cpp\"\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\
    \n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
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
    \    int _position;\n    int _length;\n    bool _terminal;\n\n    bool refill()\
    \ {\n        _position = 0;\n        if (_terminal) {\n            if (std::fgets(_buffer,\
    \ buffer_size, _stream) == nullptr) {\n                _length = 0;\n        \
    \        return false;\n            }\n            _length = int(std::strlen(_buffer));\n\
    \        } else {\n            _length = int(std::fread(_buffer, 1, buffer_size,\
    \ _stream));\n        }\n        return _length != 0;\n    }\n\n    template <class\
    \ T>\n    bool read_integer_from_terminal(T& value) {\n        if (!skip_spaces())\
    \ return false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _terminal(::isatty(::fileno(stream)) != 0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_terminal) return read_integer_from_terminal(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position == 0) return;\n\
    \        std::fwrite(_buffer, 1, _position, _stream);\n        _position = 0;\n\
    \    }\n\n    void write_char(char c) {\n        if (_position == buffer_size)\
    \ flush();\n        _buffer[_position++] = c;\n    }\n\n    void write(const char*\
    \ s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\n    void write(const\
    \ std::string& s) {\n        for (char c : s) write_char(c);\n    }\n\n    void\
    \ write(char c) {\n        write_char(c);\n    }\n\n    void write(bool value)\
    \ {\n        write_char(value ? '1' : '0');\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<std::is_floating_point_v<T>>\n    write(T value) {\n   \
    \     char digits[128];\n        auto [end, error] = std::to_chars(\n        \
    \    digits,\n            digits + sizeof(digits),\n            value,\n     \
    \       _float_format,\n            _precision\n        );\n        if (error\
    \ != std::errc()) std::abort();\n        for (const char* pointer = digits; pointer\
    \ != end; pointer++) {\n            write_char(*pointer);\n        }\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
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
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 12 \"verify/graph/st_numbering.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\n\nbool valid_numbering(\n\
    \    const Graph& graph,\n    int source,\n    int sink,\n    const std::vector<int>&\
    \ rank\n) {\n    const int n = graph.size();\n    if (int(rank.size()) != n) return\
    \ false;\n    std::vector<int> order(n, -1);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        if (rank[vertex] < 0 || rank[vertex] >= n) return\
    \ false;\n        if (order[rank[vertex]] != -1) return false;\n        order[rank[vertex]]\
    \ = vertex;\n    }\n    if (rank[source] != 0 || rank[sink] != n - 1) return false;\n\
    \n    for (int index = 0; index < n; index++) {\n        bool smaller = index\
    \ == 0;\n        bool larger = index + 1 == n;\n        for (const auto& edge\
    \ : graph[order[index]]) {\n            if (!edge.alive || edge.to == order[index])\
    \ continue;\n            smaller = smaller || rank[edge.to] < index;\n       \
    \     larger = larger || index < rank[edge.to];\n        }\n        if (!smaller\
    \ || !larger) return false;\n    }\n    return true;\n}\n\nbool brute_exists(const\
    \ Graph& graph, int source, int sink) {\n    const int n = graph.size();\n   \
    \ std::vector<int> middle;\n    for (int vertex = 0; vertex < n; vertex++) {\n\
    \        if (vertex != source && vertex != sink) middle.push_back(vertex);\n \
    \   }\n    do {\n        std::vector<int> rank(n, -1);\n        rank[source] =\
    \ 0;\n        for (int index = 0; index < int(middle.size()); index++) {\n   \
    \         rank[middle[index]] = index + 1;\n        }\n        rank[sink] = n\
    \ - 1;\n        if (valid_numbering(graph, source, sink, rank)) return true;\n\
    \    } while (std::next_permutation(middle.begin(), middle.end()));\n    return\
    \ false;\n}\n\nvoid validate(const Graph& graph, int source, int sink) {\n   \
    \ const std::vector<int> rank =\n        m1une::graph::st_numbering(graph, source,\
    \ sink);\n    assert(rank.empty() == !brute_exists(graph, source, sink));\n  \
    \  if (!rank.empty()) assert(valid_numbering(graph, source, sink, rank));\n}\n\
    \nvoid test_fixed() {\n    Graph edge(2);\n    edge.add_edge(0, 1);\n    validate(edge,\
    \ 0, 1);\n\n    Graph path(5);\n    for (int vertex = 1; vertex < 5; vertex++)\
    \ {\n        path.add_edge(vertex - 1, vertex);\n    }\n    validate(path, 0,\
    \ 4);\n    validate(path, 1, 4);\n\n    Graph cycle(6);\n    for (int vertex =\
    \ 0; vertex < 6; vertex++) {\n        cycle.add_edge(vertex, (vertex + 1) % 6);\n\
    \    }\n    validate(cycle, 1, 4);\n\n    Graph parallel(3);\n    parallel.add_edge(0,\
    \ 1);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(1, 2);\n    int shortcut\
    \ = parallel.add_edge(0, 2);\n    validate(parallel, 0, 2);\n    parallel.erase_edge(shortcut);\n\
    \    validate(parallel, 0, 2);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 20260717;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 1500; trial++) {\n        const int n = 2 + int(random()\
    \ % 6);\n        Graph graph(n);\n        for (int first = 0; first < n; first++)\
    \ {\n            for (int second = first + 1; second < n; second++) {\n      \
    \          if (random() % 3 == 0) graph.add_edge(first, second);\n           \
    \ }\n        }\n        const int source = int(random() % n);\n        int sink\
    \ = int(random() % (n - 1));\n        if (sink >= source) sink++;\n        validate(graph,\
    \ source, sink);\n    }\n}\n\nvoid test_deep_path() {\n    const int n = 50000;\n\
    \    Graph graph(n);\n    for (int vertex = 1; vertex < n; vertex++) {\n     \
    \   graph.add_edge(vertex - 1, vertex);\n    }\n    const std::vector<int> rank\
    \ = m1une::graph::st_numbering(graph, 0, n - 1);\n    assert(int(rank.size())\
    \ == n);\n    for (int vertex = 0; vertex < n; vertex++) assert(rank[vertex] ==\
    \ vertex);\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \    test_deep_path();\n\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    int test_count;\n    fast_input >> test_count;\n    while\
    \ (test_count--) {\n        int vertex_count, edge_count, source, sink;\n    \
    \    fast_input >> vertex_count >> edge_count >> source >> sink;\n        Graph\
    \ graph(vertex_count);\n        while (edge_count--) {\n            int first,\
    \ second;\n            fast_input >> first >> second;\n            graph.add_edge(first,\
    \ second);\n        }\n\n        const std::vector<int> rank =\n            m1une::graph::st_numbering(graph,\
    \ source, sink);\n        if (rank.empty()) {\n            fast_output << \"No\\\
    n\";\n        } else {\n            fast_output << \"Yes\\n\";\n            for\
    \ (int vertex = 0; vertex < vertex_count; vertex++) {\n                if (vertex)\
    \ fast_output << ' ';\n                fast_output << rank[vertex];\n        \
    \    }\n            fast_output << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/st_numbering\"\n\n#include\
    \ \"../../graph/st_numbering.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <numeric>\n#include <vector>\n\n#include \"../../utilities/fast_io.hpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\n\nbool valid_numbering(\n\
    \    const Graph& graph,\n    int source,\n    int sink,\n    const std::vector<int>&\
    \ rank\n) {\n    const int n = graph.size();\n    if (int(rank.size()) != n) return\
    \ false;\n    std::vector<int> order(n, -1);\n    for (int vertex = 0; vertex\
    \ < n; vertex++) {\n        if (rank[vertex] < 0 || rank[vertex] >= n) return\
    \ false;\n        if (order[rank[vertex]] != -1) return false;\n        order[rank[vertex]]\
    \ = vertex;\n    }\n    if (rank[source] != 0 || rank[sink] != n - 1) return false;\n\
    \n    for (int index = 0; index < n; index++) {\n        bool smaller = index\
    \ == 0;\n        bool larger = index + 1 == n;\n        for (const auto& edge\
    \ : graph[order[index]]) {\n            if (!edge.alive || edge.to == order[index])\
    \ continue;\n            smaller = smaller || rank[edge.to] < index;\n       \
    \     larger = larger || index < rank[edge.to];\n        }\n        if (!smaller\
    \ || !larger) return false;\n    }\n    return true;\n}\n\nbool brute_exists(const\
    \ Graph& graph, int source, int sink) {\n    const int n = graph.size();\n   \
    \ std::vector<int> middle;\n    for (int vertex = 0; vertex < n; vertex++) {\n\
    \        if (vertex != source && vertex != sink) middle.push_back(vertex);\n \
    \   }\n    do {\n        std::vector<int> rank(n, -1);\n        rank[source] =\
    \ 0;\n        for (int index = 0; index < int(middle.size()); index++) {\n   \
    \         rank[middle[index]] = index + 1;\n        }\n        rank[sink] = n\
    \ - 1;\n        if (valid_numbering(graph, source, sink, rank)) return true;\n\
    \    } while (std::next_permutation(middle.begin(), middle.end()));\n    return\
    \ false;\n}\n\nvoid validate(const Graph& graph, int source, int sink) {\n   \
    \ const std::vector<int> rank =\n        m1une::graph::st_numbering(graph, source,\
    \ sink);\n    assert(rank.empty() == !brute_exists(graph, source, sink));\n  \
    \  if (!rank.empty()) assert(valid_numbering(graph, source, sink, rank));\n}\n\
    \nvoid test_fixed() {\n    Graph edge(2);\n    edge.add_edge(0, 1);\n    validate(edge,\
    \ 0, 1);\n\n    Graph path(5);\n    for (int vertex = 1; vertex < 5; vertex++)\
    \ {\n        path.add_edge(vertex - 1, vertex);\n    }\n    validate(path, 0,\
    \ 4);\n    validate(path, 1, 4);\n\n    Graph cycle(6);\n    for (int vertex =\
    \ 0; vertex < 6; vertex++) {\n        cycle.add_edge(vertex, (vertex + 1) % 6);\n\
    \    }\n    validate(cycle, 1, 4);\n\n    Graph parallel(3);\n    parallel.add_edge(0,\
    \ 1);\n    parallel.add_edge(0, 1);\n    parallel.add_edge(1, 2);\n    int shortcut\
    \ = parallel.add_edge(0, 2);\n    validate(parallel, 0, 2);\n    parallel.erase_edge(shortcut);\n\
    \    validate(parallel, 0, 2);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 20260717;\n    auto random = [&state]() {\n        state ^= state <<\
    \ 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n    for (int\
    \ trial = 0; trial < 1500; trial++) {\n        const int n = 2 + int(random()\
    \ % 6);\n        Graph graph(n);\n        for (int first = 0; first < n; first++)\
    \ {\n            for (int second = first + 1; second < n; second++) {\n      \
    \          if (random() % 3 == 0) graph.add_edge(first, second);\n           \
    \ }\n        }\n        const int source = int(random() % n);\n        int sink\
    \ = int(random() % (n - 1));\n        if (sink >= source) sink++;\n        validate(graph,\
    \ source, sink);\n    }\n}\n\nvoid test_deep_path() {\n    const int n = 50000;\n\
    \    Graph graph(n);\n    for (int vertex = 1; vertex < n; vertex++) {\n     \
    \   graph.add_edge(vertex - 1, vertex);\n    }\n    const std::vector<int> rank\
    \ = m1une::graph::st_numbering(graph, 0, n - 1);\n    assert(int(rank.size())\
    \ == n);\n    for (int vertex = 0; vertex < n; vertex++) assert(rank[vertex] ==\
    \ vertex);\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \    test_deep_path();\n\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n    int test_count;\n    fast_input >> test_count;\n    while\
    \ (test_count--) {\n        int vertex_count, edge_count, source, sink;\n    \
    \    fast_input >> vertex_count >> edge_count >> source >> sink;\n        Graph\
    \ graph(vertex_count);\n        while (edge_count--) {\n            int first,\
    \ second;\n            fast_input >> first >> second;\n            graph.add_edge(first,\
    \ second);\n        }\n\n        const std::vector<int> rank =\n            m1une::graph::st_numbering(graph,\
    \ source, sink);\n        if (rank.empty()) {\n            fast_output << \"No\\\
    n\";\n        } else {\n            fast_output << \"Yes\\n\";\n            for\
    \ (int vertex = 0; vertex < vertex_count; vertex++) {\n                if (vertex)\
    \ fast_output << ' ';\n                fast_output << rank[vertex];\n        \
    \    }\n            fast_output << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - graph/st_numbering.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/st_numbering.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 23:38:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/st_numbering.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/st_numbering.test.cpp
- /verify/verify/graph/st_numbering.test.cpp.html
title: verify/graph/st_numbering.test.cpp
---
