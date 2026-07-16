---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dfs.hpp
    title: DFS
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_B
  bundledCode: "#line 1 \"verify/graph/dfs.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_B\"\
    \n\n#line 1 \"graph/dfs.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <concepts>\n#include <functional>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace\
    \ m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using\
    \ cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n   \
    \ bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true)\
    \ {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ =\
    \ true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\
    \n    int other(int v) const {\n        assert(v == from || v == to);\n      \
    \  return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph\
    \ {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
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
    \ m1une\n\n\n#line 12 \"graph/dfs.hpp\"\n\nnamespace m1une {\nnamespace graph\
    \ {\n\nstruct DfsResult {\n    std::vector<int> depth;\n    std::vector<int> parent;\n\
    \    std::vector<int> parent_edge;\n    std::vector<int> root;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> preorder;\n    std::vector<int>\
    \ postorder;\n    std::vector<int> roots;\n\n    bool reachable(int vertex) const\
    \ {\n        assert(0 <= vertex && vertex < int(depth.size()));\n        return\
    \ depth[vertex] != -1;\n    }\n\n    int component_count() const {\n        return\
    \ int(roots.size());\n    }\n\n    std::vector<int> path(int target) const {\n\
    \        assert(reachable(target));\n        std::vector<int> result;\n      \
    \  for (int vertex = target; vertex != -1; vertex = parent[vertex]) {\n      \
    \      result.push_back(vertex);\n        }\n        std::reverse(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    bool is_ancestor(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < int(depth.size()));\n\
    \        assert(0 <= vertex && vertex < int(depth.size()));\n        if (!reachable(ancestor)\
    \ || !reachable(vertex)) return false;\n        return tin[ancestor] <= tin[vertex]\
    \ && tout[vertex] <= tout[ancestor];\n    }\n};\n\nnamespace dfs_detail {\n\n\
    template <class Callback>\nconcept DfsCallback =\n    std::invocable<Callback&,\
    \ int, int> ||\n    std::invocable<Callback&, int>;\n\ntemplate <DfsCallback Callback>\n\
    void invoke_callback(Callback& callback, int vertex, int parent) {\n    if constexpr\
    \ (std::invocable<Callback&, int, int>) {\n        std::invoke(callback, vertex,\
    \ parent);\n    } else {\n        std::invoke(callback, vertex);\n    }\n}\n\n\
    template <class T, class Callback>\nDfsResult run_dfs(\n    const Graph<T>& graph,\n\
    \    const std::vector<int>& sources,\n    bool complete_forest,\n    Callback&\
    \ callback\n) {\n    const int n = graph.size();\n    DfsResult result;\n    result.depth.assign(n,\
    \ -1);\n    result.parent.assign(n, -1);\n    result.parent_edge.assign(n, -1);\n\
    \    result.root.assign(n, -1);\n    result.tin.assign(n, -1);\n    result.tout.assign(n,\
    \ -1);\n    result.preorder.reserve(n);\n    result.postorder.reserve(n);\n  \
    \  result.roots.reserve(n);\n\n    struct Frame {\n        int vertex;\n     \
    \   int next_edge;\n    };\n    std::vector<Frame> stack;\n    stack.reserve(n);\n\
    \    int timer = 0;\n\n    auto traverse = [&](int source) {\n        assert(0\
    \ <= source && source < n);\n        if (result.reachable(source)) return;\n\n\
    \        result.depth[source] = 0;\n        result.root[source] = source;\n  \
    \      result.tin[source] = ++timer;\n        result.preorder.push_back(source);\n\
    \        result.roots.push_back(source);\n        invoke_callback(callback, source,\
    \ -1);\n        stack.push_back(Frame{source, 0});\n\n        while (!stack.empty())\
    \ {\n            Frame& frame = stack.back();\n            int vertex = frame.vertex;\n\
    \            if (frame.next_edge == int(graph[vertex].size())) {\n           \
    \     result.tout[vertex] = ++timer;\n                result.postorder.push_back(vertex);\n\
    \                stack.pop_back();\n                continue;\n            }\n\
    \n            const Edge<T>& edge = graph[vertex][frame.next_edge++];\n      \
    \      if (!edge.alive || result.reachable(edge.to)) continue;\n            result.depth[edge.to]\
    \ = result.depth[vertex] + 1;\n            result.parent[edge.to] = vertex;\n\
    \            result.parent_edge[edge.to] = edge.id;\n            result.root[edge.to]\
    \ = result.root[vertex];\n            result.tin[edge.to] = ++timer;\n       \
    \     result.preorder.push_back(edge.to);\n            invoke_callback(callback,\
    \ edge.to, vertex);\n            stack.push_back(Frame{edge.to, 0});\n       \
    \ }\n    };\n\n    for (int source : sources) traverse(source);\n    if (complete_forest)\
    \ {\n        for (int vertex = 0; vertex < n; vertex++) traverse(vertex);\n  \
    \  }\n    return result;\n}\n\n}  // namespace dfs_detail\n\ntemplate <class T>\n\
    DfsResult dfs(const Graph<T>& graph, const std::vector<int>& sources) {\n    auto\
    \ callback = [](int) {};\n    return dfs_detail::run_dfs(graph, sources, false,\
    \ callback);\n}\n\ntemplate <class T>\nDfsResult dfs(const Graph<T>& graph, int\
    \ source) {\n    return dfs(graph, std::vector<int>{source});\n}\n\ntemplate <class\
    \ T>\nDfsResult dfs(const Graph<T>& graph) {\n    auto callback = [](int) {};\n\
    \    return dfs_detail::run_dfs(\n        graph,\n        std::vector<int>(),\n\
    \        true,\n        callback\n    );\n}\n\ntemplate <class T, class Callback>\n\
    requires dfs_detail::DfsCallback<Callback>\nDfsResult dfs(\n    const Graph<T>&\
    \ graph,\n    const std::vector<int>& sources,\n    Callback&& callback\n) {\n\
    \    return dfs_detail::run_dfs(graph, sources, false, callback);\n}\n\ntemplate\
    \ <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\nDfsResult\
    \ dfs(const Graph<T>& graph, int source, Callback&& callback) {\n    return dfs(\n\
    \        graph,\n        std::vector<int>{source},\n        std::forward<Callback>(callback)\n\
    \    );\n}\n\ntemplate <class T, class Callback>\nrequires dfs_detail::DfsCallback<Callback>\n\
    DfsResult dfs(const Graph<T>& graph, Callback&& callback) {\n    return dfs_detail::run_dfs(\n\
    \        graph,\n        std::vector<int>(),\n        true,\n        callback\n\
    \    );\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\
    \n\n\n\n#include <array>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\n\
    #include <unistd.h>\n\nnamespace m1une {\nnamespace utilities {\nnamespace internal\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 6 \"verify/graph/dfs.test.cpp\"\n\
    \n#line 12 \"verify/graph/dfs.test.cpp\"\n\nnamespace {\n\ntemplate <class T>\n\
    m1une::graph::DfsResult recursive_dfs(\n    const m1une::graph::Graph<T>& graph,\n\
    \    const std::vector<int>& sources,\n    bool complete_forest\n) {\n    int\
    \ size = graph.size();\n    m1une::graph::DfsResult result;\n    result.depth.assign(size,\
    \ -1);\n    result.parent.assign(size, -1);\n    result.parent_edge.assign(size,\
    \ -1);\n    result.root.assign(size, -1);\n    result.tin.assign(size, -1);\n\
    \    result.tout.assign(size, -1);\n    int timer = 0;\n\n    auto visit = [&](auto&&\
    \ self, int vertex) -> void {\n        result.tin[vertex] = ++timer;\n       \
    \ result.preorder.push_back(vertex);\n        for (const auto& edge : graph[vertex])\
    \ {\n            if (!edge.alive || result.depth[edge.to] != -1) continue;\n \
    \           result.depth[edge.to] = result.depth[vertex] + 1;\n            result.parent[edge.to]\
    \ = vertex;\n            result.parent_edge[edge.to] = edge.id;\n            result.root[edge.to]\
    \ = result.root[vertex];\n            self(self, edge.to);\n        }\n      \
    \  result.tout[vertex] = ++timer;\n        result.postorder.push_back(vertex);\n\
    \    };\n    auto start = [&](int source) {\n        if (result.depth[source]\
    \ != -1) return;\n        result.depth[source] = 0;\n        result.root[source]\
    \ = source;\n        result.roots.push_back(source);\n        visit(visit, source);\n\
    \    };\n    for (int source : sources) start(source);\n    if (complete_forest)\
    \ {\n        for (int vertex = 0; vertex < size; vertex++) start(vertex);\n  \
    \  }\n    return result;\n}\n\nvoid assert_equal(\n    const m1une::graph::DfsResult&\
    \ actual,\n    const m1une::graph::DfsResult& expected\n) {\n    assert(actual.depth\
    \ == expected.depth);\n    assert(actual.parent == expected.parent);\n    assert(actual.parent_edge\
    \ == expected.parent_edge);\n    assert(actual.root == expected.root);\n    assert(actual.tin\
    \ == expected.tin);\n    assert(actual.tout == expected.tout);\n    assert(actual.preorder\
    \ == expected.preorder);\n    assert(actual.postorder == expected.postorder);\n\
    \    assert(actual.roots == expected.roots);\n    assert(actual.component_count()\
    \ == int(actual.roots.size()));\n\n    int size = int(actual.depth.size());\n\
    \    for (int vertex = 0; vertex < size; vertex++) {\n        assert(actual.reachable(vertex)\
    \ == (actual.depth[vertex] != -1));\n        if (!actual.reachable(vertex)) continue;\n\
    \        std::vector<int> path = actual.path(vertex);\n        assert(path.front()\
    \ == actual.root[vertex]);\n        assert(path.back() == vertex);\n        assert(int(path.size())\
    \ == actual.depth[vertex] + 1);\n    }\n    for (int ancestor = 0; ancestor <\
    \ size; ancestor++) {\n        for (int vertex = 0; vertex < size; vertex++) {\n\
    \            bool expected_ancestor = false;\n            if (actual.reachable(vertex))\
    \ {\n                for (int current = vertex; current != -1;\n             \
    \        current = actual.parent[current]) {\n                    expected_ancestor\
    \ |= current == ancestor;\n                }\n            }\n            assert(\n\
    \                actual.is_ancestor(ancestor, vertex) == expected_ancestor\n \
    \           );\n        }\n    }\n}\n\nvoid assert_callback_visits(\n    const\
    \ std::vector<std::pair<int, int>>& visits,\n    const m1une::graph::DfsResult&\
    \ result\n) {\n    assert(visits.size() == result.preorder.size());\n    for (int\
    \ i = 0; i < int(visits.size()); i++) {\n        int vertex = visits[i].first;\n\
    \        assert(vertex == result.preorder[i]);\n        assert(visits[i].second\
    \ == result.parent[vertex]);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 0x243f6a8885a308d3ULL;\n    auto random = [&]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 300; trial++) {\n        int size = int(random()\
    \ % 25);\n        m1une::graph::Graph<> graph(size);\n        for (int from =\
    \ 0; from < size; from++) {\n            for (int to = 0; to < size; to++) {\n\
    \                if (from == to || random() % 11 != 0) continue;\n           \
    \     int edge = graph.add_directed_edge(from, to);\n                if (random()\
    \ % 9 == 0) graph.erase_edge(edge);\n            }\n        }\n        if (size\
    \ == 0) {\n            assert_equal(\n                m1une::graph::dfs(graph),\n\
    \                recursive_dfs(graph, std::vector<int>(), true)\n            );\n\
    \            continue;\n        }\n\n        int source = int(random() % size);\n\
    \        std::vector<int> single_source(1, source);\n        assert_equal(\n \
    \           m1une::graph::dfs(graph, source),\n            recursive_dfs(graph,\
    \ single_source, false)\n        );\n        std::vector<std::pair<int, int>>\
    \ single_callback_visits;\n        auto single_callback_result = m1une::graph::dfs(\n\
    \            graph,\n            source,\n            [&](int vertex, int parent)\
    \ {\n                single_callback_visits.emplace_back(vertex, parent);\n  \
    \          }\n        );\n        assert_callback_visits(\n            single_callback_visits,\n\
    \            single_callback_result\n        );\n        assert_equal(\n     \
    \       single_callback_result,\n            recursive_dfs(graph, single_source,\
    \ false)\n        );\n\n        std::vector<int> sources;\n        int source_count\
    \ = int(random() % (size + 1));\n        for (int i = 0; i < source_count; i++)\
    \ {\n            sources.push_back(int(random() % size));\n        }\n       \
    \ assert_equal(\n            m1une::graph::dfs(graph, sources),\n            recursive_dfs(graph,\
    \ sources, false)\n        );\n        std::vector<std::pair<int, int>> multi_callback_visits;\n\
    \        auto multi_callback_result = m1une::graph::dfs(\n            graph,\n\
    \            sources,\n            [&](int vertex, int parent) {\n           \
    \     multi_callback_visits.emplace_back(vertex, parent);\n            }\n   \
    \     );\n        assert_callback_visits(\n            multi_callback_visits,\n\
    \            multi_callback_result\n        );\n        assert_equal(\n      \
    \      multi_callback_result,\n            recursive_dfs(graph, sources, false)\n\
    \        );\n        assert_equal(\n            m1une::graph::dfs(graph),\n  \
    \          recursive_dfs(graph, std::vector<int>(), true)\n        );\n      \
    \  std::vector<std::pair<int, int>> forest_callback_visits;\n        auto forest_callback_result\
    \ = m1une::graph::dfs(\n            graph,\n            [&](int vertex, int parent)\
    \ {\n                forest_callback_visits.emplace_back(vertex, parent);\n  \
    \          }\n        );\n        assert_callback_visits(\n            forest_callback_visits,\n\
    \            forest_callback_result\n        );\n        assert_equal(\n     \
    \       forest_callback_result,\n            recursive_dfs(graph, std::vector<int>(),\
    \ true)\n        );\n    }\n\n    constexpr int deep_size = 100'000;\n    m1une::graph::Graph<>\
    \ chain(deep_size);\n    for (int vertex = 1; vertex < deep_size; vertex++) {\n\
    \        chain.add_directed_edge(vertex - 1, vertex);\n    }\n    int callback_count\
    \ = 0;\n    auto deep = m1une::graph::dfs(\n        chain,\n        0,\n     \
    \   [&](int) { callback_count++; }\n    );\n    assert(callback_count == deep_size);\n\
    \    assert(deep.depth.back() == deep_size - 1);\n    assert(deep.is_ancestor(0,\
    \ deep_size - 1));\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    int vertex_count = 0;\n    fast_input >> vertex_count;\n    m1une::graph::Graph<>\
    \ graph(vertex_count);\n    for (int i = 0; i < vertex_count; i++) {\n       \
    \ int vertex = 0;\n        int degree = 0;\n        fast_input >> vertex >> degree;\n\
    \        vertex--;\n        while (degree--) {\n            int to = 0;\n    \
    \        fast_input >> to;\n            graph.add_directed_edge(vertex, to - 1);\n\
    \        }\n    }\n\n    m1une::graph::DfsResult result = m1une::graph::dfs(graph);\n\
    \    for (int vertex = 0; vertex < vertex_count; vertex++) {\n        fast_output\
    \ << vertex + 1 << ' ' << result.tin[vertex] << ' '\n                    << result.tout[vertex]\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_11_B\"\n\
    \n#include \"../../graph/dfs.hpp\"\n#include \"../../graph/graph.hpp\"\n#include\
    \ \"../../utilities/fast_io.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <utility>\n#include <vector>\n\nnamespace {\n\ntemplate\
    \ <class T>\nm1une::graph::DfsResult recursive_dfs(\n    const m1une::graph::Graph<T>&\
    \ graph,\n    const std::vector<int>& sources,\n    bool complete_forest\n) {\n\
    \    int size = graph.size();\n    m1une::graph::DfsResult result;\n    result.depth.assign(size,\
    \ -1);\n    result.parent.assign(size, -1);\n    result.parent_edge.assign(size,\
    \ -1);\n    result.root.assign(size, -1);\n    result.tin.assign(size, -1);\n\
    \    result.tout.assign(size, -1);\n    int timer = 0;\n\n    auto visit = [&](auto&&\
    \ self, int vertex) -> void {\n        result.tin[vertex] = ++timer;\n       \
    \ result.preorder.push_back(vertex);\n        for (const auto& edge : graph[vertex])\
    \ {\n            if (!edge.alive || result.depth[edge.to] != -1) continue;\n \
    \           result.depth[edge.to] = result.depth[vertex] + 1;\n            result.parent[edge.to]\
    \ = vertex;\n            result.parent_edge[edge.to] = edge.id;\n            result.root[edge.to]\
    \ = result.root[vertex];\n            self(self, edge.to);\n        }\n      \
    \  result.tout[vertex] = ++timer;\n        result.postorder.push_back(vertex);\n\
    \    };\n    auto start = [&](int source) {\n        if (result.depth[source]\
    \ != -1) return;\n        result.depth[source] = 0;\n        result.root[source]\
    \ = source;\n        result.roots.push_back(source);\n        visit(visit, source);\n\
    \    };\n    for (int source : sources) start(source);\n    if (complete_forest)\
    \ {\n        for (int vertex = 0; vertex < size; vertex++) start(vertex);\n  \
    \  }\n    return result;\n}\n\nvoid assert_equal(\n    const m1une::graph::DfsResult&\
    \ actual,\n    const m1une::graph::DfsResult& expected\n) {\n    assert(actual.depth\
    \ == expected.depth);\n    assert(actual.parent == expected.parent);\n    assert(actual.parent_edge\
    \ == expected.parent_edge);\n    assert(actual.root == expected.root);\n    assert(actual.tin\
    \ == expected.tin);\n    assert(actual.tout == expected.tout);\n    assert(actual.preorder\
    \ == expected.preorder);\n    assert(actual.postorder == expected.postorder);\n\
    \    assert(actual.roots == expected.roots);\n    assert(actual.component_count()\
    \ == int(actual.roots.size()));\n\n    int size = int(actual.depth.size());\n\
    \    for (int vertex = 0; vertex < size; vertex++) {\n        assert(actual.reachable(vertex)\
    \ == (actual.depth[vertex] != -1));\n        if (!actual.reachable(vertex)) continue;\n\
    \        std::vector<int> path = actual.path(vertex);\n        assert(path.front()\
    \ == actual.root[vertex]);\n        assert(path.back() == vertex);\n        assert(int(path.size())\
    \ == actual.depth[vertex] + 1);\n    }\n    for (int ancestor = 0; ancestor <\
    \ size; ancestor++) {\n        for (int vertex = 0; vertex < size; vertex++) {\n\
    \            bool expected_ancestor = false;\n            if (actual.reachable(vertex))\
    \ {\n                for (int current = vertex; current != -1;\n             \
    \        current = actual.parent[current]) {\n                    expected_ancestor\
    \ |= current == ancestor;\n                }\n            }\n            assert(\n\
    \                actual.is_ancestor(ancestor, vertex) == expected_ancestor\n \
    \           );\n        }\n    }\n}\n\nvoid assert_callback_visits(\n    const\
    \ std::vector<std::pair<int, int>>& visits,\n    const m1une::graph::DfsResult&\
    \ result\n) {\n    assert(visits.size() == result.preorder.size());\n    for (int\
    \ i = 0; i < int(visits.size()); i++) {\n        int vertex = visits[i].first;\n\
    \        assert(vertex == result.preorder[i]);\n        assert(visits[i].second\
    \ == result.parent[vertex]);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 0x243f6a8885a308d3ULL;\n    auto random = [&]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 300; trial++) {\n        int size = int(random()\
    \ % 25);\n        m1une::graph::Graph<> graph(size);\n        for (int from =\
    \ 0; from < size; from++) {\n            for (int to = 0; to < size; to++) {\n\
    \                if (from == to || random() % 11 != 0) continue;\n           \
    \     int edge = graph.add_directed_edge(from, to);\n                if (random()\
    \ % 9 == 0) graph.erase_edge(edge);\n            }\n        }\n        if (size\
    \ == 0) {\n            assert_equal(\n                m1une::graph::dfs(graph),\n\
    \                recursive_dfs(graph, std::vector<int>(), true)\n            );\n\
    \            continue;\n        }\n\n        int source = int(random() % size);\n\
    \        std::vector<int> single_source(1, source);\n        assert_equal(\n \
    \           m1une::graph::dfs(graph, source),\n            recursive_dfs(graph,\
    \ single_source, false)\n        );\n        std::vector<std::pair<int, int>>\
    \ single_callback_visits;\n        auto single_callback_result = m1une::graph::dfs(\n\
    \            graph,\n            source,\n            [&](int vertex, int parent)\
    \ {\n                single_callback_visits.emplace_back(vertex, parent);\n  \
    \          }\n        );\n        assert_callback_visits(\n            single_callback_visits,\n\
    \            single_callback_result\n        );\n        assert_equal(\n     \
    \       single_callback_result,\n            recursive_dfs(graph, single_source,\
    \ false)\n        );\n\n        std::vector<int> sources;\n        int source_count\
    \ = int(random() % (size + 1));\n        for (int i = 0; i < source_count; i++)\
    \ {\n            sources.push_back(int(random() % size));\n        }\n       \
    \ assert_equal(\n            m1une::graph::dfs(graph, sources),\n            recursive_dfs(graph,\
    \ sources, false)\n        );\n        std::vector<std::pair<int, int>> multi_callback_visits;\n\
    \        auto multi_callback_result = m1une::graph::dfs(\n            graph,\n\
    \            sources,\n            [&](int vertex, int parent) {\n           \
    \     multi_callback_visits.emplace_back(vertex, parent);\n            }\n   \
    \     );\n        assert_callback_visits(\n            multi_callback_visits,\n\
    \            multi_callback_result\n        );\n        assert_equal(\n      \
    \      multi_callback_result,\n            recursive_dfs(graph, sources, false)\n\
    \        );\n        assert_equal(\n            m1une::graph::dfs(graph),\n  \
    \          recursive_dfs(graph, std::vector<int>(), true)\n        );\n      \
    \  std::vector<std::pair<int, int>> forest_callback_visits;\n        auto forest_callback_result\
    \ = m1une::graph::dfs(\n            graph,\n            [&](int vertex, int parent)\
    \ {\n                forest_callback_visits.emplace_back(vertex, parent);\n  \
    \          }\n        );\n        assert_callback_visits(\n            forest_callback_visits,\n\
    \            forest_callback_result\n        );\n        assert_equal(\n     \
    \       forest_callback_result,\n            recursive_dfs(graph, std::vector<int>(),\
    \ true)\n        );\n    }\n\n    constexpr int deep_size = 100'000;\n    m1une::graph::Graph<>\
    \ chain(deep_size);\n    for (int vertex = 1; vertex < deep_size; vertex++) {\n\
    \        chain.add_directed_edge(vertex - 1, vertex);\n    }\n    int callback_count\
    \ = 0;\n    auto deep = m1une::graph::dfs(\n        chain,\n        0,\n     \
    \   [&](int) { callback_count++; }\n    );\n    assert(callback_count == deep_size);\n\
    \    assert(deep.depth.back() == deep_size - 1);\n    assert(deep.is_ancestor(0,\
    \ deep_size - 1));\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \n    int vertex_count = 0;\n    fast_input >> vertex_count;\n    m1une::graph::Graph<>\
    \ graph(vertex_count);\n    for (int i = 0; i < vertex_count; i++) {\n       \
    \ int vertex = 0;\n        int degree = 0;\n        fast_input >> vertex >> degree;\n\
    \        vertex--;\n        while (degree--) {\n            int to = 0;\n    \
    \        fast_input >> to;\n            graph.add_directed_edge(vertex, to - 1);\n\
    \        }\n    }\n\n    m1une::graph::DfsResult result = m1une::graph::dfs(graph);\n\
    \    for (int vertex = 0; vertex < vertex_count; vertex++) {\n        fast_output\
    \ << vertex + 1 << ' ' << result.tin[vertex] << ' '\n                    << result.tout[vertex]\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/dfs.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/dfs.test.cpp
  requiredBy: []
  timestamp: '2026-07-16 19:40:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/dfs.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/dfs.test.cpp
- /verify/verify/graph/dfs.test.cpp.html
title: verify/graph/dfs.test.cpp
---
