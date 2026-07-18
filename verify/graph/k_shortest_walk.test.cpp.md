---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/k_shortest_walk.hpp
    title: K-Shortest Walk
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
    PROBLEM: https://judge.yosupo.jp/problem/k_shortest_walk
    links:
    - https://judge.yosupo.jp/problem/k_shortest_walk
  bundledCode: "#line 1 \"verify/graph/k_shortest_walk.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#line 1 \"graph/k_shortest_walk.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <limits>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 12 \"graph/k_shortest_walk.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nnamespace internal {\n\ntemplate <class T>\nclass KShortestWalkHeap\
    \ {\n    struct Node {\n        T key;\n        int to;\n        int left;\n \
    \       int right;\n        int rank;\n    };\n\n    std::vector<Node> _nodes;\n\
    \n    int rank(int root) const {\n        return root == -1 ? 0 : _nodes[root].rank;\n\
    \    }\n\n   public:\n    int make_node(T key, int to) {\n        int result =\
    \ int(_nodes.size());\n        _nodes.push_back(Node{key, to, -1, -1, 1});\n \
    \       return result;\n    }\n\n    int meld_mutable(int first, int second) {\n\
    \        if (first == -1) return second;\n        if (second == -1) return first;\n\
    \        if (_nodes[second].key < _nodes[first].key) std::swap(first, second);\n\
    \        _nodes[first].right = meld_mutable(_nodes[first].right, second);\n  \
    \      if (rank(_nodes[first].left) < rank(_nodes[first].right)) {\n         \
    \   std::swap(_nodes[first].left, _nodes[first].right);\n        }\n        _nodes[first].rank\
    \ = rank(_nodes[first].right) + 1;\n        return first;\n    }\n\n    int meld_persistent(int\
    \ first, int second) {\n        if (first == -1) return second;\n        if (second\
    \ == -1) return first;\n        if (_nodes[second].key < _nodes[first].key) std::swap(first,\
    \ second);\n        int result = int(_nodes.size());\n        _nodes.push_back(_nodes[first]);\n\
    \        _nodes[result].right = meld_persistent(_nodes[result].right, second);\n\
    \        if (rank(_nodes[result].left) < rank(_nodes[result].right)) {\n     \
    \       std::swap(_nodes[result].left, _nodes[result].right);\n        }\n   \
    \     _nodes[result].rank = rank(_nodes[result].right) + 1;\n        return result;\n\
    \    }\n\n    const Node& operator[](int index) const {\n        return _nodes[index];\n\
    \    }\n};\n\n}  // namespace internal\n\ntemplate <class T>\nstd::vector<T> k_shortest_walk(\n\
    \    const Graph<T>& g,\n    int s,\n    int t,\n    int k,\n    T inf = std::numeric_limits<T>::max()\
    \ / T(4)\n) {\n    int n = g.size();\n    assert(0 <= s && s < n);\n    assert(0\
    \ <= t && t < n);\n    assert(0 <= k);\n    if (k == 0) return {};\n\n    struct\
    \ ReverseEdge {\n        int from;\n        int index;\n        T cost;\n    };\n\
    \    std::vector<std::vector<ReverseEdge>> reverse_graph(n);\n    for (int from\
    \ = 0; from < n; from++) {\n        for (int index = 0; index < int(g[from].size());\
    \ index++) {\n            const auto& edge = g[from][index];\n            if (!edge.alive)\
    \ continue;\n            assert(T(0) <= edge.cost);\n            reverse_graph[edge.to].push_back(ReverseEdge{from,\
    \ index, edge.cost});\n        }\n    }\n\n    std::vector<T> dist(n, inf);\n\
    \    std::vector<int> tree_edge(n, -1);\n    std::vector<int> order;\n    order.reserve(n);\n\
    \    using QueueEntry = std::pair<T, int>;\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> queue;\n    dist[t] = T(0);\n\
    \    queue.emplace(T(0), t);\n    while (!queue.empty()) {\n        auto [current_dist,\
    \ vertex] = queue.top();\n        queue.pop();\n        if (dist[vertex] != current_dist)\
    \ continue;\n        order.push_back(vertex);\n        for (const auto& edge :\
    \ reverse_graph[vertex]) {\n            T next_dist = current_dist + edge.cost;\n\
    \            if (dist[edge.from] <= next_dist) continue;\n            dist[edge.from]\
    \ = next_dist;\n            tree_edge[edge.from] = edge.index;\n            queue.emplace(next_dist,\
    \ edge.from);\n        }\n    }\n    if (dist[s] == inf) return {};\n\n    internal::KShortestWalkHeap<T>\
    \ heap_pool;\n    std::vector<int> local_heap(n, -1);\n    for (int vertex : order)\
    \ {\n        for (int index = 0; index < int(g[vertex].size()); index++) {\n \
    \           const auto& edge = g[vertex][index];\n            if (!edge.alive\
    \ || dist[edge.to] == inf || index == tree_edge[vertex]) continue;\n         \
    \   T extra = edge.cost + dist[edge.to] - dist[vertex];\n            assert(T(0)\
    \ <= extra);\n            int node = heap_pool.make_node(extra, edge.to);\n  \
    \          local_heap[vertex] = heap_pool.meld_mutable(local_heap[vertex], node);\n\
    \        }\n    }\n\n    std::vector<int> path_heap(n, -1);\n    for (int vertex\
    \ : order) {\n        int inherited = -1;\n        if (tree_edge[vertex] != -1)\
    \ inherited = path_heap[g[vertex][tree_edge[vertex]].to];\n        path_heap[vertex]\
    \ = heap_pool.meld_persistent(inherited, local_heap[vertex]);\n    }\n\n    std::vector<T>\
    \ result;\n    result.reserve(k);\n    result.push_back(dist[s]);\n    std::priority_queue<QueueEntry,\
    \ std::vector<QueueEntry>, std::greater<QueueEntry>> candidates;\n    if (path_heap[s]\
    \ != -1) {\n        candidates.emplace(dist[s] + heap_pool[path_heap[s]].key,\
    \ path_heap[s]);\n    }\n    while (int(result.size()) < k && !candidates.empty())\
    \ {\n        auto [cost, node_index] = candidates.top();\n        candidates.pop();\n\
    \        result.push_back(cost);\n        const auto& node = heap_pool[node_index];\n\
    \        if (node.left != -1) {\n            candidates.emplace(cost - node.key\
    \ + heap_pool[node.left].key, node.left);\n        }\n        if (node.right !=\
    \ -1) {\n            candidates.emplace(cost - node.key + heap_pool[node.right].key,\
    \ node.right);\n        }\n        int next_heap = path_heap[node.to];\n     \
    \   if (next_heap != -1) {\n            candidates.emplace(cost + heap_pool[next_heap].key,\
    \ next_heap);\n        }\n    }\n    return result;\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/graph/k_shortest_walk.test.cpp\"\n\
    \n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <algorithm>\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #include <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 18 \"\
    utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
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
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
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
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/graph/k_shortest_walk.test.cpp\"\
    \n#include <random>\n#line 12 \"verify/graph/k_shortest_walk.test.cpp\"\n\nnamespace\
    \ {\n\nstd::vector<long long> naive_k_shortest_walk(\n    const m1une::graph::Graph<long\
    \ long>& graph,\n    int source,\n    int target,\n    int k\n) {\n    using Entry\
    \ = std::pair<long long, int>;\n    std::priority_queue<Entry, std::vector<Entry>,\
    \ std::greater<Entry>> queue;\n    std::vector<int> popped(graph.size(), 0);\n\
    \    std::vector<long long> result;\n    queue.emplace(0, source);\n    while\
    \ (!queue.empty() && int(result.size()) < k) {\n        auto [cost, vertex] =\
    \ queue.top();\n        queue.pop();\n        if (popped[vertex] == k) continue;\n\
    \        popped[vertex]++;\n        if (vertex == target) result.push_back(cost);\n\
    \        for (const auto& edge : graph[vertex]) {\n            if (edge.alive)\
    \ queue.emplace(cost + edge.cost, edge.to);\n        }\n    }\n    return result;\n\
    }\n\nvoid deterministic_test() {\n    m1une::graph::Graph<long long> graph(3);\n\
    \    graph.add_directed_edge(0, 1, 2);\n    graph.add_directed_edge(1, 2, 3);\n\
    \    graph.add_directed_edge(0, 2, 8);\n    graph.add_directed_edge(1, 1, 1);\n\
    \    std::vector<long long> expected{5, 6, 7, 8, 8, 9};\n    assert(m1une::graph::k_shortest_walk(graph,\
    \ 0, 2, 6) == expected);\n\n    m1une::graph::Graph<long long> loop(1);\n    loop.add_directed_edge(0,\
    \ 0, 0);\n    assert(m1une::graph::k_shortest_walk(loop, 0, 0, 20) == std::vector<long\
    \ long>(20, 0));\n\n    m1une::graph::Graph<long long> unreachable(2);\n    assert(m1une::graph::k_shortest_walk(unreachable,\
    \ 0, 1, 10).empty());\n    assert(m1une::graph::k_shortest_walk(unreachable, 0,\
    \ 0, 0).empty());\n}\n\nvoid randomized_test() {\n    std::mt19937 random(20260713);\n\
    \    for (int test = 0; test < 2000; test++) {\n        int n = std::uniform_int_distribution<int>(1,\
    \ 7)(random);\n        int m = std::uniform_int_distribution<int>(0, 18)(random);\n\
    \        int source = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int target = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int k = std::uniform_int_distribution<int>(0, 20)(random);\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        for (int edge = 0; edge < m; edge++) {\n          \
    \  int from = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int to = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int cost = std::uniform_int_distribution<int>(0, 8)(random);\n          \
    \  int id = graph.add_directed_edge(from, to, cost);\n            if (std::uniform_int_distribution<int>(0,\
    \ 7)(random) == 0) graph.erase_edge(id);\n        }\n        auto expected = naive_k_shortest_walk(graph,\
    \ source, target, k);\n        auto actual = m1une::graph::k_shortest_walk(graph,\
    \ source, target, k);\n        assert(actual == expected);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    deterministic_test();\n   \
    \ randomized_test();\n\n    int n, m, source, target, k;\n    fast_input >> n\
    \ >> m >> source >> target >> k;\n    m1une::graph::Graph<long long> graph(n);\n\
    \    for (int edge = 0; edge < m; edge++) {\n        int from, to;\n        long\
    \ long cost;\n        fast_input >> from >> to >> cost;\n        graph.add_directed_edge(from,\
    \ to, cost);\n    }\n    auto answer = m1une::graph::k_shortest_walk(graph, source,\
    \ target, k);\n    answer.resize(k, -1);\n    for (long long value : answer) fast_output\
    \ << value << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/k_shortest_walk\"\n\n#include\
    \ \"../../graph/k_shortest_walk.hpp\"\n\n#include <cassert>\n#include <functional>\n\
    #include \"../../utilities/fast_io.hpp\"\n#include <queue>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nstd::vector<long long>\
    \ naive_k_shortest_walk(\n    const m1une::graph::Graph<long long>& graph,\n \
    \   int source,\n    int target,\n    int k\n) {\n    using Entry = std::pair<long\
    \ long, int>;\n    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>>\
    \ queue;\n    std::vector<int> popped(graph.size(), 0);\n    std::vector<long\
    \ long> result;\n    queue.emplace(0, source);\n    while (!queue.empty() && int(result.size())\
    \ < k) {\n        auto [cost, vertex] = queue.top();\n        queue.pop();\n \
    \       if (popped[vertex] == k) continue;\n        popped[vertex]++;\n      \
    \  if (vertex == target) result.push_back(cost);\n        for (const auto& edge\
    \ : graph[vertex]) {\n            if (edge.alive) queue.emplace(cost + edge.cost,\
    \ edge.to);\n        }\n    }\n    return result;\n}\n\nvoid deterministic_test()\
    \ {\n    m1une::graph::Graph<long long> graph(3);\n    graph.add_directed_edge(0,\
    \ 1, 2);\n    graph.add_directed_edge(1, 2, 3);\n    graph.add_directed_edge(0,\
    \ 2, 8);\n    graph.add_directed_edge(1, 1, 1);\n    std::vector<long long> expected{5,\
    \ 6, 7, 8, 8, 9};\n    assert(m1une::graph::k_shortest_walk(graph, 0, 2, 6) ==\
    \ expected);\n\n    m1une::graph::Graph<long long> loop(1);\n    loop.add_directed_edge(0,\
    \ 0, 0);\n    assert(m1une::graph::k_shortest_walk(loop, 0, 0, 20) == std::vector<long\
    \ long>(20, 0));\n\n    m1une::graph::Graph<long long> unreachable(2);\n    assert(m1une::graph::k_shortest_walk(unreachable,\
    \ 0, 1, 10).empty());\n    assert(m1une::graph::k_shortest_walk(unreachable, 0,\
    \ 0, 0).empty());\n}\n\nvoid randomized_test() {\n    std::mt19937 random(20260713);\n\
    \    for (int test = 0; test < 2000; test++) {\n        int n = std::uniform_int_distribution<int>(1,\
    \ 7)(random);\n        int m = std::uniform_int_distribution<int>(0, 18)(random);\n\
    \        int source = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int target = std::uniform_int_distribution<int>(0, n - 1)(random);\n\
    \        int k = std::uniform_int_distribution<int>(0, 20)(random);\n        m1une::graph::Graph<long\
    \ long> graph(n);\n        for (int edge = 0; edge < m; edge++) {\n          \
    \  int from = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int to = std::uniform_int_distribution<int>(0, n - 1)(random);\n        \
    \    int cost = std::uniform_int_distribution<int>(0, 8)(random);\n          \
    \  int id = graph.add_directed_edge(from, to, cost);\n            if (std::uniform_int_distribution<int>(0,\
    \ 7)(random) == 0) graph.erase_edge(id);\n        }\n        auto expected = naive_k_shortest_walk(graph,\
    \ source, target, k);\n        auto actual = m1une::graph::k_shortest_walk(graph,\
    \ source, target, k);\n        assert(actual == expected);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n   \
    \ m1une::utilities::FastOutput fast_output;\n\n    deterministic_test();\n   \
    \ randomized_test();\n\n    int n, m, source, target, k;\n    fast_input >> n\
    \ >> m >> source >> target >> k;\n    m1une::graph::Graph<long long> graph(n);\n\
    \    for (int edge = 0; edge < m; edge++) {\n        int from, to;\n        long\
    \ long cost;\n        fast_input >> from >> to >> cost;\n        graph.add_directed_edge(from,\
    \ to, cost);\n    }\n    auto answer = m1une::graph::k_shortest_walk(graph, source,\
    \ target, k);\n    answer.resize(k, -1);\n    for (long long value : answer) fast_output\
    \ << value << \"\\n\";\n}\n"
  dependsOn:
  - graph/k_shortest_walk.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/k_shortest_walk.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/k_shortest_walk.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/k_shortest_walk.test.cpp
- /verify/verify/graph/k_shortest_walk.test.cpp.html
title: verify/graph/k_shortest_walk.test.cpp
---
