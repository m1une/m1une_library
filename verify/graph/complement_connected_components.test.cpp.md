---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dsu/dsu.hpp
    title: DSU (Disjoint Set Union)
  - icon: ':heavy_check_mark:'
    path: graph/complement_connected_components.hpp
    title: Complement-Graph Connected Components
  - icon: ':heavy_check_mark:'
    path: graph/connected_components.hpp
    title: Connected Components
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
    PROBLEM: https://judge.yosupo.jp/problem/connected_components_of_complement_graph
    links:
    - https://judge.yosupo.jp/problem/connected_components_of_complement_graph
  bundledCode: "#line 1 \"verify/graph/complement_connected_components.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n\n#line 1 \"graph/complement_connected_components.hpp\"\n\n\n\n#include <queue>\n\
    #include <vector>\n\n#line 1 \"graph/connected_components.hpp\"\n\n\n\n#include\
    \ <cassert>\n#line 6 \"graph/connected_components.hpp\"\n\n#line 1 \"ds/dsu/dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <numeric>\n#include <utility>\n#line 8\
    \ \"ds/dsu/dsu.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\nstruct Dsu {\n  \
    \ private:\n    int _n;\n    // parent_or_size[i] is the parent of i if it's >=\
    \ 0.\n    // If it's < 0, then i is a root and -parent_or_size[i] is the size\
    \ of the group.\n    std::vector<int> parent_or_size;\n\n    // Returns {new leader,\
    \ absorbed leader}. The absorbed leader is -1 when\n    // both vertices already\
    \ belong to the same component.\n    std::pair<int, int> merge_leaders(int a,\
    \ int b) {\n        int x = leader(a), y = leader(b);\n        if (x == y) return\
    \ {x, -1};\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x,\
    \ y);\n        parent_or_size[x] += parent_or_size[y];\n        parent_or_size[y]\
    \ = x;\n        return {x, y};\n    }\n\n   public:\n    Dsu() : _n(0) {}\n  \
    \  explicit Dsu(int n) : _n(n), parent_or_size(n, -1) {}\n\n    // Merges the\
    \ group containing 'a' with the group containing 'b'.\n    // Returns the leader\
    \ of the merged group.\n    int merge(int a, int b) {\n        return merge_leaders(a,\
    \ b).first;\n    }\n\n    // Invokes callback(new_leader, absorbed_leader) after\
    \ an actual merge.\n    // Returns the leader of the merged group.\n    template\
    \ <class Callback>\n    int merge(int a, int b, Callback&& callback) {\n     \
    \   std::pair<int, int> merged = merge_leaders(a, b);\n        if (merged.second\
    \ != -1) callback(merged.first, merged.second);\n        return merged.first;\n\
    \    }\n\n    // Returns true if 'a' and 'b' belong to the same group.\n    bool\
    \ same(int a, int b) {\n        return leader(a) == leader(b);\n    }\n\n    //\
    \ Returns the leader (representative) of the group containing 'a'.\n    int leader(int\
    \ a) {\n        if (parent_or_size[a] < 0) return a;\n        // Path compression\n\
    \        return parent_or_size[a] = leader(parent_or_size[a]);\n    }\n\n    //\
    \ Returns the size of the group containing 'a'.\n    int size(int a) {\n     \
    \   return -parent_or_size[leader(a)];\n    }\n\n    // Returns a list of all\
    \ groups, where each group is a vector of its elements.\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<int> leader_buf(_n), group_size(_n);\n     \
    \   for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(i);\n \
    \           group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
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
    \ m1une\n\n\n#line 9 \"graph/connected_components.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nstruct ConnectedComponents {\n    int count;\n    std::vector<int>\
    \ comp;\n    std::vector<std::vector<int>> groups;\n\n    bool same(int u, int\
    \ v) const {\n        assert(0 <= u && u < int(comp.size()));\n        assert(0\
    \ <= v && v < int(comp.size()));\n        return comp[u] == comp[v];\n    }\n\
    };\n\ntemplate <class T>\nConnectedComponents connected_components(const Graph<T>&\
    \ g) {\n    int n = g.size();\n    m1une::ds::Dsu dsu(n);\n    for (const auto&\
    \ e : g.edges()) dsu.merge(e.from, e.to);\n\n    ConnectedComponents result;\n\
    \    result.comp.assign(n, 0);\n    std::vector<int> leader_to_comp(n, -1);\n\
    \    for (int v = 0; v < n; v++) {\n        int leader = dsu.leader(v);\n    \
    \    if (leader_to_comp[leader] == -1) {\n            leader_to_comp[leader] =\
    \ int(result.groups.size());\n            result.groups.push_back({});\n     \
    \   }\n        int c = leader_to_comp[leader];\n        result.comp[v] = c;\n\
    \        result.groups[c].push_back(v);\n    }\n    result.count = int(result.groups.size());\n\
    \n    return result;\n}\n\n}  // namespace graph\n}  // namespace m1une\n\n\n\
    #line 8 \"graph/complement_connected_components.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\n// Computes connected components after complementing the underlying\
    \ simple\n// undirected graph, without constructing the complement graph.\ntemplate\
    \ <class T>\nConnectedComponents complement_connected_components(const Graph<T>&\
    \ graph) {\n    const int size = graph.size();\n    std::vector<std::vector<int>>\
    \ adjacency(size);\n    for (const Edge<T>& edge : graph.edges()) {\n        if\
    \ (edge.from == edge.to) continue;\n        adjacency[edge.from].push_back(edge.to);\n\
    \        adjacency[edge.to].push_back(edge.from);\n    }\n\n    const int sentinel\
    \ = size;\n    std::vector<int> next(size + 1);\n    std::vector<int> previous(size\
    \ + 1);\n    if (size == 0) {\n        next[sentinel] = previous[sentinel] = sentinel;\n\
    \    } else {\n        next[sentinel] = 0;\n        previous[sentinel] = size\
    \ - 1;\n        for (int vertex = 0; vertex < size; vertex++) {\n            next[vertex]\
    \ = (vertex + 1 == size ? sentinel : vertex + 1);\n            previous[vertex]\
    \ = (vertex == 0 ? sentinel : vertex - 1);\n        }\n    }\n\n    auto erase\
    \ = [&](int vertex) {\n        next[previous[vertex]] = next[vertex];\n      \
    \  previous[next[vertex]] = previous[vertex];\n    };\n\n    ConnectedComponents\
    \ result;\n    result.comp.assign(size, -1);\n    std::vector<int> neighbor_stamp(size,\
    \ -1);\n    std::queue<int> queue;\n\n    while (next[sentinel] != sentinel) {\n\
    \        const int root = next[sentinel];\n        erase(root);\n        const\
    \ int component = int(result.groups.size());\n        result.groups.emplace_back();\n\
    \        result.groups.back().push_back(root);\n        result.comp[root] = component;\n\
    \        queue.push(root);\n\n        while (!queue.empty()) {\n            const\
    \ int vertex = queue.front();\n            queue.pop();\n            for (int\
    \ to : adjacency[vertex]) neighbor_stamp[to] = vertex;\n\n            int candidate\
    \ = next[sentinel];\n            while (candidate != sentinel) {\n           \
    \     const int following = next[candidate];\n                if (neighbor_stamp[candidate]\
    \ != vertex) {\n                    erase(candidate);\n                    result.comp[candidate]\
    \ = component;\n                    result.groups.back().push_back(candidate);\n\
    \                    queue.push(candidate);\n                }\n             \
    \   candidate = following;\n            }\n        }\n    }\n    result.count\
    \ = int(result.groups.size());\n    return result;\n}\n\n}  // namespace graph\n\
    }  // namespace m1une\n\n\n#line 4 \"verify/graph/complement_connected_components.test.cpp\"\
    \n\n#line 6 \"verify/graph/complement_connected_components.test.cpp\"\n#include\
    \ <cstdint>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <array>\n#include <cerrno>\n#include <charconv>\n#include <cstddef>\n\
    #include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n#include\
    \ <cstring>\n#include <iterator>\n#include <string>\n#include <sys/stat.h>\n#include\
    \ <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace\
    \ m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect std::begin(x),\
    \ std::end(x).\ntemplate <class T, class = void>\nstruct is_range : std::false_type\
    \ {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 10 \"verify/graph/complement_connected_components.test.cpp\"\
    \n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing Result = m1une::graph::ConnectedComponents;\n\
    \nstd::vector<int> naive_components(const Graph& graph) {\n    const int size\
    \ = graph.size();\n    std::vector<std::vector<char>> adjacent(size, std::vector<char>(size,\
    \ false));\n    for (const auto& edge : graph.edges()) {\n        if (edge.from\
    \ == edge.to) continue;\n        adjacent[edge.from][edge.to] = true;\n      \
    \  adjacent[edge.to][edge.from] = true;\n    }\n\n    std::vector<int> component(size,\
    \ -1);\n    std::queue<int> queue;\n    int component_count = 0;\n    for (int\
    \ root = 0; root < size; root++) {\n        if (component[root] != -1) continue;\n\
    \        component[root] = component_count;\n        queue.push(root);\n     \
    \   while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int to = 0; to < size; to++) {\n \
    \               if (to == vertex || adjacent[vertex][to] || component[to] != -1)\
    \ continue;\n                component[to] = component_count;\n              \
    \  queue.push(to);\n            }\n        }\n        component_count++;\n   \
    \ }\n    return component;\n}\n\nvoid validate(const Graph& graph) {\n    Result\
    \ result = m1une::graph::complement_connected_components(graph);\n    std::vector<int>\
    \ expected = naive_components(graph);\n    assert(int(result.comp.size()) == graph.size());\n\
    \    assert(result.count == int(result.groups.size()));\n\n    std::vector<int>\
    \ occurrence(graph.size(), 0);\n    for (int component = 0; component < result.count;\
    \ component++) {\n        assert(!result.groups[component].empty());\n       \
    \ for (int vertex : result.groups[component]) {\n            assert(0 <= vertex\
    \ && vertex < graph.size());\n            assert(result.comp[vertex] == component);\n\
    \            occurrence[vertex]++;\n        }\n    }\n    for (int vertex = 0;\
    \ vertex < graph.size(); vertex++) {\n        assert(occurrence[vertex] == 1);\n\
    \        for (int other = 0; other < graph.size(); other++) {\n            assert(result.same(vertex,\
    \ other) == (expected[vertex] == expected[other]));\n        }\n    }\n}\n\nvoid\
    \ test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\n    Graph\
    \ no_edges(10);\n    validate(no_edges);\n    assert(m1une::graph::complement_connected_components(no_edges).count\
    \ == 1);\n\n    Graph complete(9);\n    for (int first = 0; first < 9; first++)\
    \ {\n        for (int second = first + 1; second < 9; second++) {\n          \
    \  complete.add_edge(first, second);\n        }\n    }\n    validate(complete);\n\
    \    assert(m1une::graph::complement_connected_components(complete).count == 9);\n\
    \n    Graph star(8);\n    for (int vertex = 1; vertex < 8; vertex++) star.add_edge(0,\
    \ vertex);\n    validate(star);\n    assert(m1une::graph::complement_connected_components(star).count\
    \ == 2);\n\n    Graph mixed(5);\n    mixed.add_directed_edge(0, 1);\n    mixed.add_edge(0,\
    \ 1);\n    int inactive = mixed.add_edge(1, 2);\n    mixed.erase_edge(inactive);\n\
    \    mixed.add_edge(3, 3);\n    validate(mixed);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x8cb92baa3f3d8dd7ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n       \
    \ const int size = int(random() % 13);\n        Graph graph(size);\n        for\
    \ (int first = 0; first < size; first++) {\n            for (int second = first\
    \ + 1; second < size; second++) {\n                if (random() % 2 == 0) continue;\n\
    \                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 11 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_large_sparse_graph() {\n    const int size = 100000;\n    Graph graph(size);\n\
    \    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1,\
    \ vertex);\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    assert(result.count == 1);\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n    test_large_sparse_graph();\n    int size, edge_count;\n\
    \    fast_input >> size >> edge_count;\n    Graph graph(size);\n    while (edge_count--)\
    \ {\n        int first, second;\n        fast_input >> first >> second;\n    \
    \    graph.add_edge(first, second);\n    }\n\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    fast_output << result.count << '\\n';\n    for (const auto& component : result.groups)\
    \ {\n        fast_output << component.size();\n        for (int vertex : component)\
    \ fast_output << ' ' << vertex;\n        fast_output << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n\n#include \"../../graph/complement_connected_components.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include \"../../utilities/fast_io.hpp\"\n#include <queue>\n\
    #include <vector>\n\nnamespace {\n\nusing Graph = m1une::graph::Graph<>;\nusing\
    \ Result = m1une::graph::ConnectedComponents;\n\nstd::vector<int> naive_components(const\
    \ Graph& graph) {\n    const int size = graph.size();\n    std::vector<std::vector<char>>\
    \ adjacent(size, std::vector<char>(size, false));\n    for (const auto& edge :\
    \ graph.edges()) {\n        if (edge.from == edge.to) continue;\n        adjacent[edge.from][edge.to]\
    \ = true;\n        adjacent[edge.to][edge.from] = true;\n    }\n\n    std::vector<int>\
    \ component(size, -1);\n    std::queue<int> queue;\n    int component_count =\
    \ 0;\n    for (int root = 0; root < size; root++) {\n        if (component[root]\
    \ != -1) continue;\n        component[root] = component_count;\n        queue.push(root);\n\
    \        while (!queue.empty()) {\n            const int vertex = queue.front();\n\
    \            queue.pop();\n            for (int to = 0; to < size; to++) {\n \
    \               if (to == vertex || adjacent[vertex][to] || component[to] != -1)\
    \ continue;\n                component[to] = component_count;\n              \
    \  queue.push(to);\n            }\n        }\n        component_count++;\n   \
    \ }\n    return component;\n}\n\nvoid validate(const Graph& graph) {\n    Result\
    \ result = m1une::graph::complement_connected_components(graph);\n    std::vector<int>\
    \ expected = naive_components(graph);\n    assert(int(result.comp.size()) == graph.size());\n\
    \    assert(result.count == int(result.groups.size()));\n\n    std::vector<int>\
    \ occurrence(graph.size(), 0);\n    for (int component = 0; component < result.count;\
    \ component++) {\n        assert(!result.groups[component].empty());\n       \
    \ for (int vertex : result.groups[component]) {\n            assert(0 <= vertex\
    \ && vertex < graph.size());\n            assert(result.comp[vertex] == component);\n\
    \            occurrence[vertex]++;\n        }\n    }\n    for (int vertex = 0;\
    \ vertex < graph.size(); vertex++) {\n        assert(occurrence[vertex] == 1);\n\
    \        for (int other = 0; other < graph.size(); other++) {\n            assert(result.same(vertex,\
    \ other) == (expected[vertex] == expected[other]));\n        }\n    }\n}\n\nvoid\
    \ test_fixed() {\n    validate(Graph());\n    validate(Graph(1));\n\n    Graph\
    \ no_edges(10);\n    validate(no_edges);\n    assert(m1une::graph::complement_connected_components(no_edges).count\
    \ == 1);\n\n    Graph complete(9);\n    for (int first = 0; first < 9; first++)\
    \ {\n        for (int second = first + 1; second < 9; second++) {\n          \
    \  complete.add_edge(first, second);\n        }\n    }\n    validate(complete);\n\
    \    assert(m1une::graph::complement_connected_components(complete).count == 9);\n\
    \n    Graph star(8);\n    for (int vertex = 1; vertex < 8; vertex++) star.add_edge(0,\
    \ vertex);\n    validate(star);\n    assert(m1une::graph::complement_connected_components(star).count\
    \ == 2);\n\n    Graph mixed(5);\n    mixed.add_directed_edge(0, 1);\n    mixed.add_edge(0,\
    \ 1);\n    int inactive = mixed.add_edge(1, 2);\n    mixed.erase_edge(inactive);\n\
    \    mixed.add_edge(3, 3);\n    validate(mixed);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 0x8cb92baa3f3d8dd7ULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 1000; trial++) {\n       \
    \ const int size = int(random() % 13);\n        Graph graph(size);\n        for\
    \ (int first = 0; first < size; first++) {\n            for (int second = first\
    \ + 1; second < size; second++) {\n                if (random() % 2 == 0) continue;\n\
    \                if (random() & 1) {\n                    graph.add_edge(first,\
    \ second);\n                } else {\n                    graph.add_directed_edge(first,\
    \ second);\n                }\n                if (random() % 11 == 0) graph.add_edge(first,\
    \ second);\n            }\n        }\n        validate(graph);\n    }\n}\n\nvoid\
    \ test_large_sparse_graph() {\n    const int size = 100000;\n    Graph graph(size);\n\
    \    for (int vertex = 1; vertex < size; vertex++) graph.add_edge(vertex - 1,\
    \ vertex);\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    assert(result.count == 1);\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_fixed();\n\
    \    test_randomized();\n    test_large_sparse_graph();\n    int size, edge_count;\n\
    \    fast_input >> size >> edge_count;\n    Graph graph(size);\n    while (edge_count--)\
    \ {\n        int first, second;\n        fast_input >> first >> second;\n    \
    \    graph.add_edge(first, second);\n    }\n\n    Result result = m1une::graph::complement_connected_components(graph);\n\
    \    fast_output << result.count << '\\n';\n    for (const auto& component : result.groups)\
    \ {\n        fast_output << component.size();\n        for (int vertex : component)\
    \ fast_output << ' ' << vertex;\n        fast_output << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/complement_connected_components.hpp
  - graph/connected_components.hpp
  - ds/dsu/dsu.hpp
  - graph/graph.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/graph/complement_connected_components.test.cpp
  requiredBy: []
  timestamp: '2026-07-18 22:54:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/complement_connected_components.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/complement_connected_components.test.cpp
- /verify/verify/graph/complement_connected_components.test.cpp.html
title: verify/graph/complement_connected_components.test.cpp
---
