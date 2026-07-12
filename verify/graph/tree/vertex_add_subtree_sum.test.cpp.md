---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':question:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/tree/euler_tour.hpp
    title: Euler Tour
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"verify/graph/tree/vertex_add_subtree_sum.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <random>\n#include <vector>\n\n#line\
    \ 1 \"ds/range_query/fenwick_tree.hpp\"\n\n\n\n#line 6 \"ds/range_query/fenwick_tree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n   private:\n    int _n;\n    int _max_power;\n    std::vector<T> _data;\n\
    \n    static int max_power_leq(int n) {\n        int result = 1;\n        while\
    \ (result <= n / 2) result <<= 1;\n        return result;\n    }\n\n    T prefix_sum(int\
    \ r) const {\n        T result{};\n        const T* data = _data.data();\n   \
    \     while (r > 0) {\n            result += data[r];\n            r -= r & -r;\n\
    \        }\n        return result;\n    }\n\n   public:\n    FenwickTree() : _n(0),\
    \ _max_power(0) {}\n\n    explicit FenwickTree(int n)\n        : _n(n), _max_power(max_power_leq(n\
    \ > 0 ? n : 1)), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const std::vector<T>&\
    \ a)\n        : _n(int(a.size())),\n          _max_power(max_power_leq(_n > 0\
    \ ? _n : 1)),\n          _data(a.size() + 1, T{}) {\n        for (int i = 1; i\
    \ <= _n; ++i) {\n            _data[i] += a[i - 1];\n            const int p =\
    \ i + (i & -i);\n            if (p <= _n) {\n                _data[p] += _data[i];\n\
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
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n\
    #line 5 \"graph/graph.hpp\"\n#include <utility>\n#line 7 \"graph/graph.hpp\"\n\
    \nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
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
    \ m1une\n\n\n#line 1 \"graph/tree/euler_tour.hpp\"\n\n\n\n#line 8 \"graph/tree/euler_tour.hpp\"\
    \n\n#line 10 \"graph/tree/euler_tour.hpp\"\n\nnamespace m1une {\nnamespace tree\
    \ {\n\ntemplate <class T = int>\nstruct EulerTour {\n    using cost_type = T;\n\
    \    using edge_type = m1une::graph::Edge<T>;\n\n    int root;\n    std::vector<int>\
    \ parent;\n    std::vector<int> parent_edge;\n    std::vector<int> depth;\n  \
    \  std::vector<T> dist;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ tin;\n    std::vector<int> tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>>\
    \ children;\n\n   private:\n    int _n;\n\n    void check_vertex(int v) const\
    \ {\n        assert(0 <= v && v < _n);\n        assert(tin[v] != -1);\n    }\n\
    \n   public:\n    EulerTour() : root(-1), _n(0) {}\n    explicit EulerTour(const\
    \ m1une::graph::Graph<T>& g, int root_ = 0) {\n        build(g, root_);\n    }\n\
    \n    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {\n        _n\
    \ = g.size();\n        root = _n == 0 ? -1 : root_;\n        parent.assign(_n,\
    \ -2);\n        parent_edge.assign(_n, -1);\n        depth.assign(_n, 0);\n  \
    \      dist.assign(_n, T(0));\n        subtree_size.assign(_n, 0);\n        tin.assign(_n,\
    \ -1);\n        tout.assign(_n, -1);\n        order.clear();\n        order.reserve(_n);\n\
    \        children.assign(_n, {});\n\n        if (_n == 0) return;\n        assert(0\
    \ <= root && root < _n);\n\n        struct Frame {\n            int v;\n     \
    \       int state;\n        };\n\n        std::vector<Frame> stack;\n        stack.push_back({root,\
    \ 0});\n        parent[root] = -1;\n\n        while (!stack.empty()) {\n     \
    \       Frame frame = stack.back();\n            stack.pop_back();\n         \
    \   int v = frame.v;\n            if (frame.state == 0) {\n                tin[v]\
    \ = int(order.size());\n                order.push_back(v);\n                stack.push_back({v,\
    \ 1});\n                const auto& adj = g[v];\n                for (int i =\
    \ int(adj.size()) - 1; i >= 0; --i) {\n                    const auto& e = adj[i];\n\
    \                    if (!e.alive) continue;\n                    if (parent[e.to]\
    \ != -2) continue;\n                    parent[e.to] = v;\n                  \
    \  parent_edge[e.to] = e.id;\n                    depth[e.to] = depth[v] + 1;\n\
    \                    dist[e.to] = dist[v] + e.cost;\n                    children[v].push_back(e.to);\n\
    \                    stack.push_back({e.to, 0});\n                }\n        \
    \        std::reverse(children[v].begin(), children[v].end());\n            }\
    \ else {\n                subtree_size[v] = 1;\n                for (int child\
    \ : children[v]) subtree_size[v] += subtree_size[child];\n                tout[v]\
    \ = int(order.size());\n            }\n        }\n    }\n\n    int size() const\
    \ {\n        return _n;\n    }\n\n    int visited_size() const {\n        return\
    \ int(order.size());\n    }\n\n    bool empty() const {\n        return _n ==\
    \ 0;\n    }\n\n    bool is_ancestor(int u, int v) const {\n        check_vertex(u);\n\
    \        check_vertex(v);\n        return tin[u] <= tin[v] && tout[v] <= tout[u];\n\
    \    }\n\n    bool in_subtree(int v, int u) const {\n        return is_ancestor(u,\
    \ v);\n    }\n\n    std::pair<int, int> subtree_range(int v, bool edge = false)\
    \ const {\n        check_vertex(v);\n        return {tin[v] + (edge ? 1 : 0),\
    \ tout[v]};\n    }\n\n    std::vector<int> subtree_vertices(int v) const {\n \
    \       check_vertex(v);\n        return std::vector<int>(order.begin() + tin[v],\
    \ order.begin() + tout[v]);\n    }\n\n    template <class F>\n    void for_each_subtree(int\
    \ v, F f) const {\n        auto [l, r] = subtree_range(v);\n        for (int i\
    \ = l; i < r; ++i) f(order[i]);\n    }\n};\n\n}  // namespace tree\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cstddef>\n#include <cstdio>\n#include <cstdint>\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <type_traits>\n#line 13 \"utilities/fast_io.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
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
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 12 \"\
    verify/graph/tree/vertex_add_subtree_sum.test.cpp\"\n\nusing m1une::graph::Graph;\n\
    \nvoid test_euler_tour() {\n    Graph<int> empty_graph;\n    m1une::tree::EulerTour<int>\
    \ empty(empty_graph);\n    assert(empty.empty());\n    assert(empty.root == -1);\n\
    \    assert(empty.visited_size() == 0);\n\n    Graph<long long> sample(7);\n \
    \   sample.add_edge(0, 1, 3);\n    sample.add_edge(0, 2, 2);\n    sample.add_edge(1,\
    \ 3, 4);\n    sample.add_edge(1, 4, 1);\n    sample.add_edge(2, 5, 6);\n    sample.add_edge(5,\
    \ 6, 2);\n\n    m1une::tree::EulerTour<long long> tour(sample, 0);\n    std::vector<int>\
    \ expected_order = {0, 1, 3, 4, 2, 5, 6};\n    std::vector<int> expected_children_zero\
    \ = {1, 2};\n    std::vector<int> expected_subtree = {1, 3, 4};\n    assert(tour.size()\
    \ == 7);\n    assert(tour.visited_size() == 7);\n    assert(tour.root == 0);\n\
    \    assert(tour.order == expected_order);\n    assert(tour.children[0] == expected_children_zero);\n\
    \    assert(tour.parent[6] == 5);\n    assert(tour.parent_edge[6] == 5);\n   \
    \ assert(tour.depth[6] == 3);\n    assert(tour.dist[6] == 10);\n    assert(tour.subtree_size[0]\
    \ == 7);\n    assert(tour.subtree_size[1] == 3);\n    assert(tour.is_ancestor(1,\
    \ 4));\n    assert(!tour.is_ancestor(2, 4));\n    assert(tour.in_subtree(4, 1));\n\
    \    assert(tour.subtree_range(1).first == 1);\n    assert(tour.subtree_range(1).second\
    \ == 4);\n    assert(tour.subtree_range(1, true).first == 2);\n    assert(tour.subtree_range(1,\
    \ true).second == 4);\n    assert(tour.subtree_vertices(1) == expected_subtree);\n\
    \n    int subtree_sum = 0;\n    tour.for_each_subtree(1, [&](int vertex) {\n \
    \       subtree_sum += vertex;\n    });\n    assert(subtree_sum == 8);\n\n   \
    \ std::mt19937 random(123456789);\n    for (int test = 0; test < 50; ++test) {\n\
    \        int n = 1 + int(random() % 40);\n        Graph<int> graph(n);\n     \
    \   std::vector<int> parent(n, -1);\n        for (int v = 1; v < n; ++v) {\n \
    \           parent[v] = int(random() % v);\n            graph.add_edge(parent[v],\
    \ v);\n        }\n\n        m1une::tree::EulerTour<int> random_tour(graph, 0);\n\
    \        assert(random_tour.size() == n);\n        assert(random_tour.visited_size()\
    \ == n);\n\n        std::vector<int> expected_size(n, 1);\n        for (int v\
    \ = n - 1; v >= 1; --v) expected_size[parent[v]] += expected_size[v];\n      \
    \  assert(random_tour.subtree_size == expected_size);\n\n        for (int i =\
    \ 0; i < n; ++i) {\n            int vertex = random_tour.order[i];\n         \
    \   assert(random_tour.tin[vertex] == i);\n            assert(random_tour.tout[vertex]\
    \ - random_tour.tin[vertex] == random_tour.subtree_size[vertex]);\n        }\n\
    \n        auto naive_ancestor = [&](int ancestor, int vertex) {\n            while\
    \ (vertex != -1) {\n                if (vertex == ancestor) return true;\n   \
    \             vertex = parent[vertex];\n            }\n            return false;\n\
    \        };\n\n        for (int u = 0; u < n; ++u) {\n            std::vector<int>\
    \ expected_vertices;\n            for (int v = 0; v < n; ++v) {\n            \
    \    assert(random_tour.is_ancestor(u, v) == naive_ancestor(u, v));\n        \
    \        if (naive_ancestor(u, v)) expected_vertices.push_back(v);\n         \
    \   }\n            std::vector<int> actual_vertices = random_tour.subtree_vertices(u);\n\
    \            std::sort(actual_vertices.begin(), actual_vertices.end());\n    \
    \        assert(actual_vertices == expected_vertices);\n        }\n    }\n}\n\n\
    int main() {\n    test_euler_tour();\n\n    m1une::utilities::FastInput input;\n\
    \    m1une::utilities::FastOutput output;\n\n    int n = 0, q = 0;\n    if (!input.read(n))\
    \ return 0;\n    input.read(q);\n\n    std::vector<long long> values(n);\n   \
    \ for (long long& value : values) input.read(value);\n\n    Graph<int> graph(n);\n\
    \    for (int v = 1; v < n; ++v) {\n        int p = 0;\n        input.read(p);\n\
    \        graph.add_edge(p, v);\n    }\n\n    m1une::tree::EulerTour<int> tour(graph,\
    \ 0);\n    std::vector<long long> base(n);\n    for (int v = 0; v < n; ++v) base[tour.tin[v]]\
    \ = values[v];\n    m1une::ds::FenwickTree<long long> fenwick(base);\n\n    for\
    \ (int query = 0; query < q; ++query) {\n        int type = 0;\n        input.read(type);\n\
    \        if (type == 0) {\n            int u = 0;\n            long long x = 0;\n\
    \            input.read(u);\n            input.read(x);\n            fenwick.add(tour.tin[u],\
    \ x);\n        } else {\n            int u = 0;\n            input.read(u);\n\
    \            auto [l, r] = tour.subtree_range(u);\n            output.println(fenwick.sum(l,\
    \ r));\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <random>\n#include <vector>\n\
    \n#include \"../../../ds/range_query/fenwick_tree.hpp\"\n#include \"../../../graph/graph.hpp\"\
    \n#include \"../../../graph/tree/euler_tour.hpp\"\n#include \"../../../utilities/fast_io.hpp\"\
    \n\nusing m1une::graph::Graph;\n\nvoid test_euler_tour() {\n    Graph<int> empty_graph;\n\
    \    m1une::tree::EulerTour<int> empty(empty_graph);\n    assert(empty.empty());\n\
    \    assert(empty.root == -1);\n    assert(empty.visited_size() == 0);\n\n   \
    \ Graph<long long> sample(7);\n    sample.add_edge(0, 1, 3);\n    sample.add_edge(0,\
    \ 2, 2);\n    sample.add_edge(1, 3, 4);\n    sample.add_edge(1, 4, 1);\n    sample.add_edge(2,\
    \ 5, 6);\n    sample.add_edge(5, 6, 2);\n\n    m1une::tree::EulerTour<long long>\
    \ tour(sample, 0);\n    std::vector<int> expected_order = {0, 1, 3, 4, 2, 5, 6};\n\
    \    std::vector<int> expected_children_zero = {1, 2};\n    std::vector<int> expected_subtree\
    \ = {1, 3, 4};\n    assert(tour.size() == 7);\n    assert(tour.visited_size()\
    \ == 7);\n    assert(tour.root == 0);\n    assert(tour.order == expected_order);\n\
    \    assert(tour.children[0] == expected_children_zero);\n    assert(tour.parent[6]\
    \ == 5);\n    assert(tour.parent_edge[6] == 5);\n    assert(tour.depth[6] == 3);\n\
    \    assert(tour.dist[6] == 10);\n    assert(tour.subtree_size[0] == 7);\n   \
    \ assert(tour.subtree_size[1] == 3);\n    assert(tour.is_ancestor(1, 4));\n  \
    \  assert(!tour.is_ancestor(2, 4));\n    assert(tour.in_subtree(4, 1));\n    assert(tour.subtree_range(1).first\
    \ == 1);\n    assert(tour.subtree_range(1).second == 4);\n    assert(tour.subtree_range(1,\
    \ true).first == 2);\n    assert(tour.subtree_range(1, true).second == 4);\n \
    \   assert(tour.subtree_vertices(1) == expected_subtree);\n\n    int subtree_sum\
    \ = 0;\n    tour.for_each_subtree(1, [&](int vertex) {\n        subtree_sum +=\
    \ vertex;\n    });\n    assert(subtree_sum == 8);\n\n    std::mt19937 random(123456789);\n\
    \    for (int test = 0; test < 50; ++test) {\n        int n = 1 + int(random()\
    \ % 40);\n        Graph<int> graph(n);\n        std::vector<int> parent(n, -1);\n\
    \        for (int v = 1; v < n; ++v) {\n            parent[v] = int(random() %\
    \ v);\n            graph.add_edge(parent[v], v);\n        }\n\n        m1une::tree::EulerTour<int>\
    \ random_tour(graph, 0);\n        assert(random_tour.size() == n);\n        assert(random_tour.visited_size()\
    \ == n);\n\n        std::vector<int> expected_size(n, 1);\n        for (int v\
    \ = n - 1; v >= 1; --v) expected_size[parent[v]] += expected_size[v];\n      \
    \  assert(random_tour.subtree_size == expected_size);\n\n        for (int i =\
    \ 0; i < n; ++i) {\n            int vertex = random_tour.order[i];\n         \
    \   assert(random_tour.tin[vertex] == i);\n            assert(random_tour.tout[vertex]\
    \ - random_tour.tin[vertex] == random_tour.subtree_size[vertex]);\n        }\n\
    \n        auto naive_ancestor = [&](int ancestor, int vertex) {\n            while\
    \ (vertex != -1) {\n                if (vertex == ancestor) return true;\n   \
    \             vertex = parent[vertex];\n            }\n            return false;\n\
    \        };\n\n        for (int u = 0; u < n; ++u) {\n            std::vector<int>\
    \ expected_vertices;\n            for (int v = 0; v < n; ++v) {\n            \
    \    assert(random_tour.is_ancestor(u, v) == naive_ancestor(u, v));\n        \
    \        if (naive_ancestor(u, v)) expected_vertices.push_back(v);\n         \
    \   }\n            std::vector<int> actual_vertices = random_tour.subtree_vertices(u);\n\
    \            std::sort(actual_vertices.begin(), actual_vertices.end());\n    \
    \        assert(actual_vertices == expected_vertices);\n        }\n    }\n}\n\n\
    int main() {\n    test_euler_tour();\n\n    m1une::utilities::FastInput input;\n\
    \    m1une::utilities::FastOutput output;\n\n    int n = 0, q = 0;\n    if (!input.read(n))\
    \ return 0;\n    input.read(q);\n\n    std::vector<long long> values(n);\n   \
    \ for (long long& value : values) input.read(value);\n\n    Graph<int> graph(n);\n\
    \    for (int v = 1; v < n; ++v) {\n        int p = 0;\n        input.read(p);\n\
    \        graph.add_edge(p, v);\n    }\n\n    m1une::tree::EulerTour<int> tour(graph,\
    \ 0);\n    std::vector<long long> base(n);\n    for (int v = 0; v < n; ++v) base[tour.tin[v]]\
    \ = values[v];\n    m1une::ds::FenwickTree<long long> fenwick(base);\n\n    for\
    \ (int query = 0; query < q; ++query) {\n        int type = 0;\n        input.read(type);\n\
    \        if (type == 0) {\n            int u = 0;\n            long long x = 0;\n\
    \            input.read(u);\n            input.read(x);\n            fenwick.add(tour.tin[u],\
    \ x);\n        } else {\n            int u = 0;\n            input.read(u);\n\
    \            auto [l, r] = tour.subtree_range(u);\n            output.println(fenwick.sum(l,\
    \ r));\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/fenwick_tree.hpp
  - graph/graph.hpp
  - graph/tree/euler_tour.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/tree/vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2026-07-11 19:47:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/tree/vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/tree/vertex_add_subtree_sum.test.cpp
- /verify/verify/graph/tree/vertex_add_subtree_sum.test.cpp.html
title: verify/graph/tree/vertex_add_subtree_sum.test.cpp
---
