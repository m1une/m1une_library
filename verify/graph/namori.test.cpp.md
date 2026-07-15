---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/namori.hpp
    title: Namori Graph Decomposition
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
  bundledCode: "#line 1 \"verify/graph/namori.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"graph/namori.hpp\"\n\n\n\n#include <cassert>\n#include <optional>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 11 \"graph/namori.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\ntemplate <class T>\nstruct NamoriDecomposition {\n    int component_count;\n\
    \    std::vector<std::vector<int>> cycles;\n    std::vector<std::vector<int>>\
    \ cycle_edge_ids;\n    std::vector<std::vector<T>> cycle_edge_costs;\n\n    std::vector<bool>\
    \ on_cycle;\n    std::vector<int> component;\n    std::vector<int> cycle_root;\n\
    \    std::vector<int> cycle_position;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<T> dist_to_cycle;\n\
    \    std::vector<std::vector<int>> children;\n\n    bool same_component(int u,\
    \ int v) const {\n        assert(0 <= u && u < int(component.size()));\n     \
    \   assert(0 <= v && v < int(component.size()));\n        return component[u]\
    \ == component[v];\n    }\n\n    bool same_tree(int u, int v) const {\n      \
    \  assert(0 <= u && u < int(cycle_root.size()));\n        assert(0 <= v && v <\
    \ int(cycle_root.size()));\n        return cycle_root[u] == cycle_root[v];\n \
    \   }\n};\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> namori_decomposition(const\
    \ Graph<T>& graph) {\n    int n = graph.size();\n    NamoriDecomposition<T> result;\n\
    \    result.component_count = 0;\n    result.on_cycle.assign(n, false);\n    result.component.assign(n,\
    \ -1);\n    result.cycle_root.assign(n, -1);\n    result.cycle_position.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.depth.assign(n, 0);\n    result.dist_to_cycle.assign(n, T(0));\n \
    \   result.children.assign(n, {});\n    if (n == 0) return result;\n\n    std::vector<int>\
    \ degree(n, 0);\n    for (int v = 0; v < n; v++) {\n        for (const auto& edge\
    \ : graph[v]) {\n            if (edge.alive) degree[v]++;\n        }\n    }\n\n\
    \    std::queue<int> queue;\n    std::vector<bool> removed(n, false);\n    for\
    \ (int v = 0; v < n; v++) {\n        if (degree[v] <= 1) queue.push(v);\n    }\n\
    \    while (!queue.empty()) {\n        int v = queue.front();\n        queue.pop();\n\
    \        if (removed[v] || degree[v] > 1) continue;\n        removed[v] = true;\n\
    \        for (const auto& edge : graph[v]) {\n            if (!edge.alive || removed[edge.to])\
    \ continue;\n            degree[edge.to]--;\n            if (degree[edge.to] ==\
    \ 1) queue.push(edge.to);\n        }\n    }\n\n    for (int v = 0; v < n; v++)\
    \ {\n        result.on_cycle[v] = !removed[v];\n    }\n    for (int v = 0; v <\
    \ n; v++) {\n        if (!result.on_cycle[v]) continue;\n        int cycle_degree\
    \ = 0;\n        for (const auto& edge : graph[v]) {\n            if (edge.alive\
    \ && result.on_cycle[edge.to]) cycle_degree++;\n        }\n        if (cycle_degree\
    \ != 2) return std::nullopt;\n    }\n\n    std::vector<bool> cycle_visited(n,\
    \ false);\n    for (int start = 0; start < n; start++) {\n        if (!result.on_cycle[start]\
    \ || cycle_visited[start]) continue;\n        int component_id = int(result.cycles.size());\n\
    \        std::vector<int> vertices;\n        std::vector<int> edge_ids;\n    \
    \    std::vector<T> edge_costs;\n\n        int current = start;\n        int previous_edge\
    \ = -1;\n        while (true) {\n            if (cycle_visited[current]) return\
    \ std::nullopt;\n            cycle_visited[current] = true;\n            vertices.push_back(current);\n\
    \n            int next_vertex = -1;\n            int next_edge = -1;\n       \
    \     T next_cost = T(0);\n            for (const auto& edge : graph[current])\
    \ {\n                if (!edge.alive || !result.on_cycle[edge.to] || edge.id ==\
    \ previous_edge) continue;\n                next_vertex = edge.to;\n         \
    \       next_edge = edge.id;\n                next_cost = edge.cost;\n       \
    \         break;\n            }\n            if (next_edge == -1) return std::nullopt;\n\
    \            edge_ids.push_back(next_edge);\n            edge_costs.push_back(next_cost);\n\
    \            if (next_vertex == start) break;\n            previous_edge = next_edge;\n\
    \            current = next_vertex;\n            if (int(vertices.size()) > n)\
    \ return std::nullopt;\n        }\n\n        for (int position = 0; position <\
    \ int(vertices.size()); position++) {\n            int v = vertices[position];\n\
    \            result.component[v] = component_id;\n            result.cycle_root[v]\
    \ = v;\n            result.cycle_position[v] = position;\n        }\n        result.cycles.push_back(std::move(vertices));\n\
    \        result.cycle_edge_ids.push_back(std::move(edge_ids));\n        result.cycle_edge_costs.push_back(std::move(edge_costs));\n\
    \    }\n    if (result.cycles.empty()) return std::nullopt;\n\n    std::vector<int>\
    \ stack;\n    stack.reserve(n);\n    for (const auto& cycle : result.cycles) {\n\
    \        for (int v : cycle) stack.push_back(v);\n    }\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[v]) {\n            if (!edge.alive || result.on_cycle[edge.to]\
    \ || edge.id == result.parent_edge[v]) continue;\n            int to = edge.to;\n\
    \            if (result.component[to] != -1) continue;\n            result.component[to]\
    \ = result.component[v];\n            result.cycle_root[to] = result.cycle_root[v];\n\
    \            result.cycle_position[to] = result.cycle_position[v];\n         \
    \   result.parent[to] = v;\n            result.parent_edge[to] = edge.id;\n  \
    \          result.depth[to] = result.depth[v] + 1;\n            result.dist_to_cycle[to]\
    \ = result.dist_to_cycle[v] + edge.cost;\n            result.children[v].push_back(to);\n\
    \            stack.push_back(to);\n        }\n    }\n    for (int v = 0; v < n;\
    \ v++) {\n        if (result.component[v] == -1) return std::nullopt;\n    }\n\
    \n    result.component_count = int(result.cycles.size());\n    return result;\n\
    }\n\ntemplate <class T>\nstd::optional<NamoriDecomposition<T>> decompose_namori(const\
    \ Graph<T>& graph) {\n    return namori_decomposition(graph);\n}\n\n}  // namespace\
    \ graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/namori.test.cpp\"\n\
    \n#include <algorithm>\n#line 7 \"verify/graph/namori.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/graph/namori.test.cpp\"\
    \n#include <numeric>\n#line 11 \"verify/graph/namori.test.cpp\"\n#include <set>\n\
    #line 14 \"verify/graph/namori.test.cpp\"\n\nnamespace {\n\nvoid test_features()\
    \ {\n    m1une::graph::Graph<long long> graph(7);\n    int e01 = graph.add_edge(0,\
    \ 1, 2);\n    int e12 = graph.add_edge(1, 2, 3);\n    int e20 = graph.add_edge(2,\
    \ 0, 4);\n    graph.add_edge(1, 3, 5);\n    graph.add_edge(3, 4, 6);\n    int\
    \ loop = graph.add_edge(5, 5, 7);\n    graph.add_edge(5, 6, 8);\n\n    auto optional\
    \ = m1une::graph::namori_decomposition(graph);\n    assert(optional.has_value());\n\
    \    const auto& result = *optional;\n    assert(result.component_count == 2);\n\
    \    assert(result.cycles.size() == 2);\n    assert(result.on_cycle[0]);\n   \
    \ assert(result.on_cycle[1]);\n    assert(result.on_cycle[2]);\n    assert(!result.on_cycle[3]);\n\
    \    assert(!result.on_cycle[4]);\n    assert(result.on_cycle[5]);\n    assert(!result.on_cycle[6]);\n\
    \    assert(result.same_component(0, 4));\n    assert(!result.same_component(0,\
    \ 5));\n    assert(result.same_tree(1, 4));\n    assert(!result.same_tree(0, 4));\n\
    \    assert(result.cycle_root[4] == 1);\n    assert(result.parent[4] == 3);\n\
    \    assert(result.parent[3] == 1);\n    assert(result.depth[4] == 2);\n    assert(result.dist_to_cycle[4]\
    \ == 11);\n    assert(result.cycle_root[6] == 5);\n    assert(result.dist_to_cycle[6]\
    \ == 8);\n\n    std::set<int> first_cycle_edges;\n    for (int id : result.cycle_edge_ids[result.component[0]])\
    \ first_cycle_edges.insert(id);\n    assert((first_cycle_edges == std::set<int>{e01,\
    \ e12, e20}));\n    int loop_component = result.component[5];\n    assert(result.cycles[loop_component]\
    \ == std::vector<int>({5}));\n    assert(result.cycle_edge_ids[loop_component]\
    \ == std::vector<int>({loop}));\n\n    m1une::graph::Graph<int> parallel(2);\n\
    \    int first = parallel.add_edge(0, 1);\n    int second = parallel.add_edge(0,\
    \ 1);\n    auto two_cycle = m1une::graph::decompose_namori(parallel);\n    assert(two_cycle.has_value());\n\
    \    assert(two_cycle->cycles[0].size() == 2);\n    std::set<int> parallel_ids(\n\
    \        two_cycle->cycle_edge_ids[0].begin(),\n        two_cycle->cycle_edge_ids[0].end()\n\
    \    );\n    assert((parallel_ids == std::set<int>{first, second}));\n\n    m1une::graph::Graph<int>\
    \ tree(3);\n    tree.add_edge(0, 1);\n    tree.add_edge(1, 2);\n    assert(!m1une::graph::namori_decomposition(tree).has_value());\n\
    \n    m1une::graph::Graph<int> bicyclic(5);\n    bicyclic.add_edge(0, 1);\n  \
    \  bicyclic.add_edge(1, 2);\n    bicyclic.add_edge(2, 0);\n    bicyclic.add_edge(2,\
    \ 3);\n    bicyclic.add_edge(3, 4);\n    int removable = bicyclic.add_edge(4,\
    \ 2);\n    assert(!m1une::graph::namori_decomposition(bicyclic).has_value());\n\
    \    bicyclic.erase_edge(removable);\n    auto inactive_ignored = m1une::graph::namori_decomposition(bicyclic);\n\
    \    assert(inactive_ignored.has_value());\n    assert(inactive_ignored->component_count\
    \ == 1);\n\n    m1une::graph::Graph<int> empty;\n    auto empty_result = m1une::graph::namori_decomposition(empty);\n\
    \    assert(empty_result.has_value());\n    assert(empty_result->component_count\
    \ == 0);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1000; trial++) {\n        int n = 1 + int(random() % 150);\n        int component_count\
    \ = 1 + int(random() % std::min(n, 10));\n        std::vector<int> component_size(component_count,\
    \ 1);\n        for (int i = component_count; i < n; i++) component_size[random()\
    \ % component_count]++;\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        std::vector<int> expected_component(n, -1);\n        int offset = 0;\n\
    \        for (int component = 0; component < component_count; component++) {\n\
    \            int size = component_size[component];\n            int cycle_size\
    \ = 1 + int(random() % size);\n            for (int i = 0; i < size; i++) expected_component[offset\
    \ + i] = component;\n\n            if (cycle_size == 1) {\n                graph.add_edge(offset,\
    \ offset, 1 + random() % 1000);\n            } else if (cycle_size == 2) {\n \
    \               graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n   \
    \             graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n     \
    \       } else {\n                for (int i = 0; i < cycle_size; i++) {\n   \
    \                 graph.add_edge(\n                        offset + i,\n     \
    \                   offset + (i + 1) % cycle_size,\n                        1\
    \ + random() % 1000\n                    );\n                }\n            }\n\
    \            for (int i = cycle_size; i < size; i++) {\n                int parent\
    \ = int(random() % i);\n                graph.add_edge(offset + i, offset + parent,\
    \ 1 + random() % 1000);\n            }\n            offset += size;\n        }\n\
    \n        auto optional = m1une::graph::namori_decomposition(graph);\n       \
    \ assert(optional.has_value());\n        const auto& result = *optional;\n   \
    \     assert(result.component_count == component_count);\n\n        int cycle_vertex_count\
    \ = 0;\n        for (int component = 0; component < result.component_count; component++)\
    \ {\n            const auto& cycle = result.cycles[component];\n            const\
    \ auto& edge_ids = result.cycle_edge_ids[component];\n            const auto&\
    \ edge_costs = result.cycle_edge_costs[component];\n            assert(!cycle.empty());\n\
    \            assert(cycle.size() == edge_ids.size());\n            assert(cycle.size()\
    \ == edge_costs.size());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int i = 0; i < int(cycle.size()); i++) {\n                int\
    \ from = cycle[i];\n                int to = cycle[(i + 1) % cycle.size()];\n\
    \                bool found = false;\n                for (const auto& edge :\
    \ graph[from]) {\n                    if (edge.id == edge_ids[i] && edge.to ==\
    \ to && edge.cost == edge_costs[i]) {\n                        found = true;\n\
    \                        break;\n                    }\n                }\n  \
    \              assert(found);\n            }\n        }\n\n        int counted_cycle_vertices\
    \ = 0;\n        for (int v = 0; v < n; v++) {\n            assert(0 <= result.component[v]\
    \ && result.component[v] < component_count);\n            assert(expected_component[v]\
    \ == expected_component[result.cycle_root[v]]);\n            assert(result.cycles[result.component[v]][result.cycle_position[v]]\
    \ == result.cycle_root[v]);\n            if (result.on_cycle[v]) {\n         \
    \       counted_cycle_vertices++;\n                assert(result.cycle_root[v]\
    \ == v);\n                assert(result.parent[v] == -1);\n                assert(result.parent_edge[v]\
    \ == -1);\n                assert(result.depth[v] == 0);\n                assert(result.dist_to_cycle[v]\
    \ == 0);\n            } else {\n                int parent = result.parent[v];\n\
    \                assert(parent != -1);\n                assert(result.depth[parent]\
    \ + 1 == result.depth[v]);\n                assert(result.cycle_root[parent] ==\
    \ result.cycle_root[v]);\n                bool found = false;\n              \
    \  for (const auto& edge : graph[v]) {\n                    if (edge.id == result.parent_edge[v]\
    \ && edge.to == parent) {\n                        assert(result.dist_to_cycle[v]\
    \ == result.dist_to_cycle[parent] + edge.cost);\n                        found\
    \ = true;\n                    }\n                }\n                assert(found);\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        std::vector<int> child_count(n, 0);\n        for (int v = 0; v < n;\
    \ v++) {\n            for (int child : result.children[v]) {\n               \
    \ assert(result.parent[child] == v);\n                child_count[child]++;\n\
    \            }\n        }\n        for (int v = 0; v < n; v++) {\n           \
    \ assert(child_count[v] == int(!result.on_cycle[v]));\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../graph/namori.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <numeric>\n#include\
    \ <queue>\n#include <set>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ {\n\nvoid test_features() {\n    m1une::graph::Graph<long long> graph(7);\n\
    \    int e01 = graph.add_edge(0, 1, 2);\n    int e12 = graph.add_edge(1, 2, 3);\n\
    \    int e20 = graph.add_edge(2, 0, 4);\n    graph.add_edge(1, 3, 5);\n    graph.add_edge(3,\
    \ 4, 6);\n    int loop = graph.add_edge(5, 5, 7);\n    graph.add_edge(5, 6, 8);\n\
    \n    auto optional = m1une::graph::namori_decomposition(graph);\n    assert(optional.has_value());\n\
    \    const auto& result = *optional;\n    assert(result.component_count == 2);\n\
    \    assert(result.cycles.size() == 2);\n    assert(result.on_cycle[0]);\n   \
    \ assert(result.on_cycle[1]);\n    assert(result.on_cycle[2]);\n    assert(!result.on_cycle[3]);\n\
    \    assert(!result.on_cycle[4]);\n    assert(result.on_cycle[5]);\n    assert(!result.on_cycle[6]);\n\
    \    assert(result.same_component(0, 4));\n    assert(!result.same_component(0,\
    \ 5));\n    assert(result.same_tree(1, 4));\n    assert(!result.same_tree(0, 4));\n\
    \    assert(result.cycle_root[4] == 1);\n    assert(result.parent[4] == 3);\n\
    \    assert(result.parent[3] == 1);\n    assert(result.depth[4] == 2);\n    assert(result.dist_to_cycle[4]\
    \ == 11);\n    assert(result.cycle_root[6] == 5);\n    assert(result.dist_to_cycle[6]\
    \ == 8);\n\n    std::set<int> first_cycle_edges;\n    for (int id : result.cycle_edge_ids[result.component[0]])\
    \ first_cycle_edges.insert(id);\n    assert((first_cycle_edges == std::set<int>{e01,\
    \ e12, e20}));\n    int loop_component = result.component[5];\n    assert(result.cycles[loop_component]\
    \ == std::vector<int>({5}));\n    assert(result.cycle_edge_ids[loop_component]\
    \ == std::vector<int>({loop}));\n\n    m1une::graph::Graph<int> parallel(2);\n\
    \    int first = parallel.add_edge(0, 1);\n    int second = parallel.add_edge(0,\
    \ 1);\n    auto two_cycle = m1une::graph::decompose_namori(parallel);\n    assert(two_cycle.has_value());\n\
    \    assert(two_cycle->cycles[0].size() == 2);\n    std::set<int> parallel_ids(\n\
    \        two_cycle->cycle_edge_ids[0].begin(),\n        two_cycle->cycle_edge_ids[0].end()\n\
    \    );\n    assert((parallel_ids == std::set<int>{first, second}));\n\n    m1une::graph::Graph<int>\
    \ tree(3);\n    tree.add_edge(0, 1);\n    tree.add_edge(1, 2);\n    assert(!m1une::graph::namori_decomposition(tree).has_value());\n\
    \n    m1une::graph::Graph<int> bicyclic(5);\n    bicyclic.add_edge(0, 1);\n  \
    \  bicyclic.add_edge(1, 2);\n    bicyclic.add_edge(2, 0);\n    bicyclic.add_edge(2,\
    \ 3);\n    bicyclic.add_edge(3, 4);\n    int removable = bicyclic.add_edge(4,\
    \ 2);\n    assert(!m1une::graph::namori_decomposition(bicyclic).has_value());\n\
    \    bicyclic.erase_edge(removable);\n    auto inactive_ignored = m1une::graph::namori_decomposition(bicyclic);\n\
    \    assert(inactive_ignored.has_value());\n    assert(inactive_ignored->component_count\
    \ == 1);\n\n    m1une::graph::Graph<int> empty;\n    auto empty_result = m1une::graph::namori_decomposition(empty);\n\
    \    assert(empty_result.has_value());\n    assert(empty_result->component_count\
    \ == 0);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 123456789;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1000; trial++) {\n        int n = 1 + int(random() % 150);\n        int component_count\
    \ = 1 + int(random() % std::min(n, 10));\n        std::vector<int> component_size(component_count,\
    \ 1);\n        for (int i = component_count; i < n; i++) component_size[random()\
    \ % component_count]++;\n\n        m1une::graph::Graph<long long> graph(n);\n\
    \        std::vector<int> expected_component(n, -1);\n        int offset = 0;\n\
    \        for (int component = 0; component < component_count; component++) {\n\
    \            int size = component_size[component];\n            int cycle_size\
    \ = 1 + int(random() % size);\n            for (int i = 0; i < size; i++) expected_component[offset\
    \ + i] = component;\n\n            if (cycle_size == 1) {\n                graph.add_edge(offset,\
    \ offset, 1 + random() % 1000);\n            } else if (cycle_size == 2) {\n \
    \               graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n   \
    \             graph.add_edge(offset, offset + 1, 1 + random() % 1000);\n     \
    \       } else {\n                for (int i = 0; i < cycle_size; i++) {\n   \
    \                 graph.add_edge(\n                        offset + i,\n     \
    \                   offset + (i + 1) % cycle_size,\n                        1\
    \ + random() % 1000\n                    );\n                }\n            }\n\
    \            for (int i = cycle_size; i < size; i++) {\n                int parent\
    \ = int(random() % i);\n                graph.add_edge(offset + i, offset + parent,\
    \ 1 + random() % 1000);\n            }\n            offset += size;\n        }\n\
    \n        auto optional = m1une::graph::namori_decomposition(graph);\n       \
    \ assert(optional.has_value());\n        const auto& result = *optional;\n   \
    \     assert(result.component_count == component_count);\n\n        int cycle_vertex_count\
    \ = 0;\n        for (int component = 0; component < result.component_count; component++)\
    \ {\n            const auto& cycle = result.cycles[component];\n            const\
    \ auto& edge_ids = result.cycle_edge_ids[component];\n            const auto&\
    \ edge_costs = result.cycle_edge_costs[component];\n            assert(!cycle.empty());\n\
    \            assert(cycle.size() == edge_ids.size());\n            assert(cycle.size()\
    \ == edge_costs.size());\n            cycle_vertex_count += int(cycle.size());\n\
    \            for (int i = 0; i < int(cycle.size()); i++) {\n                int\
    \ from = cycle[i];\n                int to = cycle[(i + 1) % cycle.size()];\n\
    \                bool found = false;\n                for (const auto& edge :\
    \ graph[from]) {\n                    if (edge.id == edge_ids[i] && edge.to ==\
    \ to && edge.cost == edge_costs[i]) {\n                        found = true;\n\
    \                        break;\n                    }\n                }\n  \
    \              assert(found);\n            }\n        }\n\n        int counted_cycle_vertices\
    \ = 0;\n        for (int v = 0; v < n; v++) {\n            assert(0 <= result.component[v]\
    \ && result.component[v] < component_count);\n            assert(expected_component[v]\
    \ == expected_component[result.cycle_root[v]]);\n            assert(result.cycles[result.component[v]][result.cycle_position[v]]\
    \ == result.cycle_root[v]);\n            if (result.on_cycle[v]) {\n         \
    \       counted_cycle_vertices++;\n                assert(result.cycle_root[v]\
    \ == v);\n                assert(result.parent[v] == -1);\n                assert(result.parent_edge[v]\
    \ == -1);\n                assert(result.depth[v] == 0);\n                assert(result.dist_to_cycle[v]\
    \ == 0);\n            } else {\n                int parent = result.parent[v];\n\
    \                assert(parent != -1);\n                assert(result.depth[parent]\
    \ + 1 == result.depth[v]);\n                assert(result.cycle_root[parent] ==\
    \ result.cycle_root[v]);\n                bool found = false;\n              \
    \  for (const auto& edge : graph[v]) {\n                    if (edge.id == result.parent_edge[v]\
    \ && edge.to == parent) {\n                        assert(result.dist_to_cycle[v]\
    \ == result.dist_to_cycle[parent] + edge.cost);\n                        found\
    \ = true;\n                    }\n                }\n                assert(found);\n\
    \            }\n        }\n        assert(counted_cycle_vertices == cycle_vertex_count);\n\
    \n        std::vector<int> child_count(n, 0);\n        for (int v = 0; v < n;\
    \ v++) {\n            for (int child : result.children[v]) {\n               \
    \ assert(result.parent[child] == v);\n                child_count[child]++;\n\
    \            }\n        }\n        for (int v = 0; v < n; v++) {\n           \
    \ assert(child_count[v] == int(!result.on_cycle[v]));\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_features();\n    test_randomized();\n\
    \n    long long a, b;\n    fast_input >> a >> b;\n    fast_output << a + b <<\
    \ '\\n';\n}\n"
  dependsOn:
  - graph/namori.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/namori.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 04:26:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/namori.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/namori.test.cpp
- /verify/verify/graph/namori.test.cpp.html
title: verify/graph/namori.test.cpp
---
