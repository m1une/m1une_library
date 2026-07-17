---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
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
  bundledCode: "#line 1 \"verify/ds/dynamic_array/persistent_dynamic_array.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <deque>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node {\n        T val;\n        int priority;\n \
    \       int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ int node_priority, int node_count, int left, int right, bool reversed)\n   \
    \         : val(std::move(value)),\n              priority(node_priority),\n \
    \             count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    std::shared_ptr<std::deque<Node>>\
    \ pool;\n\n    int subtree_size(int t) const {\n        return t == -1 ? 0 : (*pool)[t].count;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    int make_node(T val, int priority, bool rev, int l, int r) const\
    \ {\n        int count = 1 + subtree_size(l) + subtree_size(r);\n        pool->emplace_back(std::move(val),\
    \ priority, count, l, r, rev);\n        return int(pool->size()) - 1;\n    }\n\
    \n    int reversed_node(int t) const {\n        if (t == -1) return -1;\n    \
    \    const Node& node = (*pool)[t];\n        return make_node(node.val, node.priority,\
    \ !node.rev, node.l, node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1 || !(*pool)[t].rev) return t;\n        Node node = (*pool)[t];\n  \
    \      int l = reversed_node(node.r);\n        int r = reversed_node(node.l);\n\
    \        return make_node(std::move(node.val), node.priority, false, l, r);\n\
    \    }\n\n    int merge(int l, int r) const {\n        if (l == -1 || r == -1)\
    \ return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
    \ {\n            Node node = (*pool)[push(l)];\n            int right = merge(node.r,\
    \ r);\n            return make_node(std::move(node.val), node.priority, false,\
    \ node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n        int\
    \ left = merge(l, node.l);\n        return make_node(std::move(node.val), node.priority,\
    \ false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int t, int\
    \ pos) const {\n        if (t == -1) return {-1, -1};\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos <= left_count)\
    \ {\n            auto [a, b] = split_node(node.l, pos);\n            return {a,\
    \ make_node(std::move(node.val), node.priority, false, b, node.r)};\n        }\n\
    \        auto [a, b] = split_node(node.r, pos - left_count - 1);\n        return\
    \ {make_node(std::move(node.val), node.priority, false, node.l, a), b};\n    }\n\
    \n    int set_node(int t, int pos, T val) const {\n        Node node = (*pool)[push(t)];\n\
    \        int left_count = subtree_size(node.l);\n        if (pos < left_count)\
    \ {\n            int l = set_node(node.l, pos, std::move(val));\n            return\
    \ make_node(std::move(node.val), node.priority, false, l, node.r);\n        }\n\
    \        if (pos == left_count) {\n            return make_node(std::move(val),\
    \ node.priority, false, node.l, node.r);\n        }\n        int r = set_node(node.r,\
    \ pos - left_count - 1, std::move(val));\n        return make_node(std::move(node.val),\
    \ node.priority, false, node.l, r);\n    }\n\n    int find_node(int t, int pos)\
    \ const {\n        bool reversed = false;\n        while (t != -1) {\n       \
    \     const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                t = l;\n               \
    \ reversed = cur_reversed;\n            } else if (pos == left_count) {\n    \
    \            return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return -1;\n    }\n\n    void dump_dfs(int t,\
    \ std::vector<T>& res, bool reversed = false) const {\n        if (t == -1) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n\
    \        res.push_back(node.val);\n        dump_dfs(r, res, cur_reversed);\n \
    \   }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1 || qr <= offset ||\
    \ offset + (*pool)[t].count <= ql) return;\n        const Node& node = (*pool)[t];\n\
    \        bool cur_reversed = reversed ^ node.rev;\n        int l = cur_reversed\
    \ ? node.r : node.l;\n        int r = cur_reversed ? node.l : node.r;\n      \
    \  int left_count = subtree_size(l);\n        int node_pos = offset + left_count;\n\
    \        dump_range_dfs(l, ql, qr, offset, res, cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res.push_back(node.val);\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int build_from_nodes(std::vector<BuildNode>&\
    \ nodes, int t) const {\n        if (t == -1) return -1;\n        int l = build_from_nodes(nodes,\
    \ nodes[t].l);\n        int r = build_from_nodes(nodes, nodes[t].r);\n       \
    \ return make_node(std::move(nodes[t].val), nodes[t].priority, false, l, r);\n\
    \    }\n\n    int build_cartesian(std::vector<BuildNode>& nodes) const {\n   \
    \     if (nodes.empty()) return -1;\n        std::vector<int> stack;\n       \
    \ stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
    \ i++) {\n            int left_child = -1;\n            while (!stack.empty()\
    \ && nodes[stack.back()].priority < nodes[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    nodes[i].l = left_child;\n            if (!stack.empty()) nodes[stack.back()].r\
    \ = i;\n            stack.push_back(i);\n        }\n        return build_from_nodes(nodes,\
    \ stack.front());\n    }\n\n    int build_from_vector(const std::vector<T>& v,\
    \ std::uint32_t& state) const {\n        std::vector<BuildNode> nodes;\n     \
    \   nodes.reserve(v.size());\n        for (const T& x : v) nodes.emplace_back(x,\
    \ next_priority(state));\n        return build_cartesian(nodes);\n    }\n\n  \
    \  int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {\n \
    \       std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n    \
    \    for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicArray(int node, std::uint32_t state, std::shared_ptr<std::deque<Node>>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {}\n\n   public:\n    PersistentDynamicArray()\n        : root(-1),\n      \
    \    rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<std::deque<Node>>()) {\n        if (rng_state\
    \ == 0) rng_state = 1;\n    }\n\n    explicit PersistentDynamicArray(int n) :\
    \ PersistentDynamicArray(n, T()) {}\n\n    PersistentDynamicArray(int n, const\
    \ T& value) : PersistentDynamicArray() {\n        assert(0 <= n);\n        std::vector<T>\
    \ v(n, value);\n        root = build_from_vector(std::move(v), rng_state);\n \
    \   }\n\n    explicit PersistentDynamicArray(const std::vector<T>& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(v, rng_state);\n    }\n\n    explicit PersistentDynamicArray(std::vector<T>&&\
    \ v) : PersistentDynamicArray() {\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n    }\n\n    PersistentDynamicArray(std::initializer_list<T> init)\
    \ : PersistentDynamicArray(std::vector<T>(init)) {}\n\n    int size() const {\n\
    \        return subtree_size(root);\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    PersistentDynamicArray clear() const {\n\
    \        return PersistentDynamicArray(-1, rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, T val) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(val),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return PersistentDynamicArray(merge(merge(l, node), r), next, pool);\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const std::vector<T>& v)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(v,\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), next, pool);\n    }\n\n    PersistentDynamicArray insert(int pos,\
    \ std::initializer_list<T> init) const {\n        return insert(pos, std::vector<T>(init));\n\
    \    }\n\n    PersistentDynamicArray insert(int pos, const PersistentDynamicArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return PersistentDynamicArray(merge(merge(l,\
    \ mid), r), rng_state, pool);\n    }\n\n    PersistentDynamicArray push_back(T\
    \ val) const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root, pos);\n\
    \        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ PersistentDynamicArray(merge(a, c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ pop_back() const {\n        assert(!empty());\n        return erase(size() -\
    \ 1);\n    }\n\n    PersistentDynamicArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    const T& at(int pos) const {\n       \
    \ assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    const T& operator[](int pos) const {\n        return at(pos);\n\
    \    }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ at(0);\n    }\n\n    const T& back() const {\n        assert(!empty());\n  \
    \      return at(size() - 1);\n    }\n\n    T get(int pos) const {\n        return\
    \ at(pos);\n    }\n\n    PersistentDynamicArray set(int pos, T val) const {\n\
    \        assert(0 <= pos && pos < size());\n        return PersistentDynamicArray(set_node(root,\
    \ pos, std::move(val)), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return PersistentDynamicArray(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state, pool);\n    }\n\n    PersistentDynamicArray\
    \ reverse() const {\n        return PersistentDynamicArray(reversed_node(root),\
    \ rng_state, pool);\n    }\n\n    PersistentDynamicArray rotate(int l, int m,\
    \ int r) const {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return *this;\n        auto [a, b] = split_node(root,\
    \ l);\n        auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)),\
    \ rng_state, pool);\n    }\n\n    std::pair<PersistentDynamicArray, PersistentDynamicArray>\
    \ split(int pos) const {\n        assert(0 <= pos && pos <= size());\n       \
    \ auto [l, r] = split_node(root, pos);\n        return {PersistentDynamicArray(l,\
    \ rng_state, pool), PersistentDynamicArray(r, rng_state, pool)};\n    }\n\n  \
    \  PersistentDynamicArray split_off(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        return PersistentDynamicArray(split_node(root, pos).second,\
    \ rng_state, pool);\n    }\n\n    std::vector<T> to_vector() const {\n       \
    \ std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root, res);\n\
    \        return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/ds/dynamic_array/persistent_dynamic_array.test.cpp\"\n\n\
    #include <algorithm>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n\
    #include <cerrno>\n#include <charconv>\n#include <cstddef>\n#include <cstdio>\n\
    #include <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
    #line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
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
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
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
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"verify/ds/dynamic_array/persistent_dynamic_array.test.cpp\"\
    \n#include <random>\n#line 11 \"verify/ds/dynamic_array/persistent_dynamic_array.test.cpp\"\
    \n\nint main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    using Array = m1une::ds::PersistentDynamicArray<int>;\n\n\
    \    Array a = {1, 2, 3, 4, 5};\n    Array b = a.insert(2, 10);\n    Array c =\
    \ b.erase(4);\n    Array d = c.reverse(1, 4);\n    Array e = d.rotate(1, 3, 5);\n\
    \    Array f = e.set(0, -1);\n    Array g = f.push_front(-2).push_back(6);\n \
    \   Array h = g.erase(2, 5);\n    Array i = h.append(Array({7, 8}));\n\n    assert(a.to_vector()\
    \ == (std::vector<int>{1, 2, 3, 4, 5}));\n    assert(b.to_vector() == (std::vector<int>{1,\
    \ 2, 10, 3, 4, 5}));\n    assert(c.to_vector() == (std::vector<int>{1, 2, 10,\
    \ 3, 5}));\n    assert(d.to_vector() == (std::vector<int>{1, 3, 10, 2, 5}));\n\
    \    assert(e.to_vector() == (std::vector<int>{1, 2, 5, 3, 10}));\n    assert(f.to_vector()\
    \ == (std::vector<int>{-1, 2, 5, 3, 10}));\n    assert(g.to_vector() == (std::vector<int>{-2,\
    \ -1, 2, 5, 3, 10, 6}));\n    assert(h.to_vector() == (std::vector<int>{-2, -1,\
    \ 10, 6}));\n    assert(i.to_vector() == (std::vector<int>{-2, -1, 10, 6, 7, 8}));\n\
    \n    assert(a.to_vector(1, 4) == (std::vector<int>{2, 3, 4}));\n    assert(i.size()\
    \ == 6);\n    assert(!i.empty());\n    assert(i.front() == -2);\n    assert(i.back()\
    \ == 8);\n    assert(i[2] == 10);\n    assert(i.get(3) == 6);\n\n    auto [left,\
    \ right] = i.split(3);\n    assert(left.to_vector() == (std::vector<int>{-2, -1,\
    \ 10}));\n    assert(right.to_vector() == (std::vector<int>{6, 7, 8}));\n    assert(i.split_off(4).to_vector()\
    \ == (std::vector<int>{7, 8}));\n    assert(left.append(right).to_vector() ==\
    \ i.to_vector());\n    assert(i.clear().empty());\n\n    Array base = {1, 2, 3};\n\
    \    const int& stable_reference = base[1];\n    Array pointer_growth = base;\n\
    \    for (int x = 0; x < 1000; x++) pointer_growth = pointer_growth.push_back(x);\n\
    \    Array j = base.append(base);\n    assert(j.to_vector() == (std::vector<int>{1,\
    \ 2, 3, 1, 2, 3}));\n    assert(j.reverse().to_vector() == (std::vector<int>{3,\
    \ 2, 1, 3, 2, 1}));\n    assert(base.to_vector() == (std::vector<int>{1, 2, 3}));\n\
    \    assert(stable_reference == 2);\n    assert(pointer_growth.size() == 1003);\n\
    \n    std::mt19937 rng(0);\n    std::vector<std::pair<Array, std::vector<int>>>\
    \ versions;\n    versions.push_back({Array(), {}});\n    for (int step = 0; step\
    \ < 300; step++) {\n        int id = int(rng() % versions.size());\n        const\
    \ Array cur = versions[id].first;\n        std::vector<int> expected = versions[id].second;\n\
    \        assert(cur.to_vector() == expected);\n\n        Array next = cur;\n \
    \       std::vector<int> next_expected = expected;\n        int op = int(rng()\
    \ % 8);\n        if (op == 0 || next_expected.empty()) {\n            int pos\
    \ = int(rng() % (next_expected.size() + 1));\n            int val = int(rng()\
    \ % 1000) - 500;\n            next = cur.insert(pos, val);\n            next_expected.insert(next_expected.begin()\
    \ + pos, val);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            int val = int(rng() % 1000) - 500;\n            next = cur.set(pos,\
    \ val);\n            next_expected[pos] = val;\n        } else if (op == 4) {\n\
    \            int l = int(rng() % (next_expected.size() + 1));\n            int\
    \ r = int(rng() % (next_expected.size() + 1));\n            if (l > r) std::swap(l,\
    \ r);\n            next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 5) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 6 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(cur.to_vector() == expected);\n\
    \        assert(next.to_vector() == next_expected);\n        if (!next_expected.empty())\
    \ {\n            int pos = int(rng() % next_expected.size());\n            assert(next[pos]\
    \ == next_expected[pos]);\n            assert(next.get(pos) == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<int>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<int>(next_expected.begin() +\
    \ split_pos, next_expected.end()));\n        assert(prefix.append(suffix).to_vector()\
    \ == next_expected);\n\n        if (next_expected.size() <= 100) {\n         \
    \   versions.push_back({next, next_expected});\n        }\n    }\n\n    long long\
    \ x, y;\n    fast_input >> x >> y;\n    fast_output << x + y << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include \"../../../utilities/fast_io.hpp\"\n#include <random>\n\
    #include <utility>\n#include <vector>\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    using Array\
    \ = m1une::ds::PersistentDynamicArray<int>;\n\n    Array a = {1, 2, 3, 4, 5};\n\
    \    Array b = a.insert(2, 10);\n    Array c = b.erase(4);\n    Array d = c.reverse(1,\
    \ 4);\n    Array e = d.rotate(1, 3, 5);\n    Array f = e.set(0, -1);\n    Array\
    \ g = f.push_front(-2).push_back(6);\n    Array h = g.erase(2, 5);\n    Array\
    \ i = h.append(Array({7, 8}));\n\n    assert(a.to_vector() == (std::vector<int>{1,\
    \ 2, 3, 4, 5}));\n    assert(b.to_vector() == (std::vector<int>{1, 2, 10, 3, 4,\
    \ 5}));\n    assert(c.to_vector() == (std::vector<int>{1, 2, 10, 3, 5}));\n  \
    \  assert(d.to_vector() == (std::vector<int>{1, 3, 10, 2, 5}));\n    assert(e.to_vector()\
    \ == (std::vector<int>{1, 2, 5, 3, 10}));\n    assert(f.to_vector() == (std::vector<int>{-1,\
    \ 2, 5, 3, 10}));\n    assert(g.to_vector() == (std::vector<int>{-2, -1, 2, 5,\
    \ 3, 10, 6}));\n    assert(h.to_vector() == (std::vector<int>{-2, -1, 10, 6}));\n\
    \    assert(i.to_vector() == (std::vector<int>{-2, -1, 10, 6, 7, 8}));\n\n   \
    \ assert(a.to_vector(1, 4) == (std::vector<int>{2, 3, 4}));\n    assert(i.size()\
    \ == 6);\n    assert(!i.empty());\n    assert(i.front() == -2);\n    assert(i.back()\
    \ == 8);\n    assert(i[2] == 10);\n    assert(i.get(3) == 6);\n\n    auto [left,\
    \ right] = i.split(3);\n    assert(left.to_vector() == (std::vector<int>{-2, -1,\
    \ 10}));\n    assert(right.to_vector() == (std::vector<int>{6, 7, 8}));\n    assert(i.split_off(4).to_vector()\
    \ == (std::vector<int>{7, 8}));\n    assert(left.append(right).to_vector() ==\
    \ i.to_vector());\n    assert(i.clear().empty());\n\n    Array base = {1, 2, 3};\n\
    \    const int& stable_reference = base[1];\n    Array pointer_growth = base;\n\
    \    for (int x = 0; x < 1000; x++) pointer_growth = pointer_growth.push_back(x);\n\
    \    Array j = base.append(base);\n    assert(j.to_vector() == (std::vector<int>{1,\
    \ 2, 3, 1, 2, 3}));\n    assert(j.reverse().to_vector() == (std::vector<int>{3,\
    \ 2, 1, 3, 2, 1}));\n    assert(base.to_vector() == (std::vector<int>{1, 2, 3}));\n\
    \    assert(stable_reference == 2);\n    assert(pointer_growth.size() == 1003);\n\
    \n    std::mt19937 rng(0);\n    std::vector<std::pair<Array, std::vector<int>>>\
    \ versions;\n    versions.push_back({Array(), {}});\n    for (int step = 0; step\
    \ < 300; step++) {\n        int id = int(rng() % versions.size());\n        const\
    \ Array cur = versions[id].first;\n        std::vector<int> expected = versions[id].second;\n\
    \        assert(cur.to_vector() == expected);\n\n        Array next = cur;\n \
    \       std::vector<int> next_expected = expected;\n        int op = int(rng()\
    \ % 8);\n        if (op == 0 || next_expected.empty()) {\n            int pos\
    \ = int(rng() % (next_expected.size() + 1));\n            int val = int(rng()\
    \ % 1000) - 500;\n            next = cur.insert(pos, val);\n            next_expected.insert(next_expected.begin()\
    \ + pos, val);\n        } else if (op == 1) {\n            int pos = int(rng()\
    \ % next_expected.size());\n            next = cur.erase(pos);\n            next_expected.erase(next_expected.begin()\
    \ + pos);\n        } else if (op == 2) {\n            int l = int(rng() % (next_expected.size()\
    \ + 1));\n            int r = int(rng() % (next_expected.size() + 1));\n     \
    \       if (l > r) std::swap(l, r);\n            next = cur.erase(l, r);\n   \
    \         next_expected.erase(next_expected.begin() + l, next_expected.begin()\
    \ + r);\n        } else if (op == 3) {\n            int pos = int(rng() % next_expected.size());\n\
    \            int val = int(rng() % 1000) - 500;\n            next = cur.set(pos,\
    \ val);\n            next_expected[pos] = val;\n        } else if (op == 4) {\n\
    \            int l = int(rng() % (next_expected.size() + 1));\n            int\
    \ r = int(rng() % (next_expected.size() + 1));\n            if (l > r) std::swap(l,\
    \ r);\n            next = cur.reverse(l, r);\n            std::reverse(next_expected.begin()\
    \ + l, next_expected.begin() + r);\n        } else if (op == 5) {\n          \
    \  int l = int(rng() % (next_expected.size() + 1));\n            int m = int(rng()\
    \ % (next_expected.size() + 1));\n            int r = int(rng() % (next_expected.size()\
    \ + 1));\n            if (l > m) std::swap(l, m);\n            if (m > r) std::swap(m,\
    \ r);\n            if (l > m) std::swap(l, m);\n            next = cur.rotate(l,\
    \ m, r);\n            std::rotate(next_expected.begin() + l, next_expected.begin()\
    \ + m, next_expected.begin() + r);\n        } else if (op == 6 && next_expected.size()\
    \ < 80) {\n            int other_id = int(rng() % versions.size());\n        \
    \    next = cur.append(versions[other_id].first);\n            next_expected.insert(next_expected.end(),\
    \ versions[other_id].second.begin(), versions[other_id].second.end());\n     \
    \   } else {\n            next = cur.reverse();\n            std::reverse(next_expected.begin(),\
    \ next_expected.end());\n        }\n\n        assert(cur.to_vector() == expected);\n\
    \        assert(next.to_vector() == next_expected);\n        if (!next_expected.empty())\
    \ {\n            int pos = int(rng() % next_expected.size());\n            assert(next[pos]\
    \ == next_expected[pos]);\n            assert(next.get(pos) == next_expected[pos]);\n\
    \        }\n        int split_pos = int(rng() % (next_expected.size() + 1));\n\
    \        auto [prefix, suffix] = next.split(split_pos);\n        assert(prefix.to_vector()\
    \ == std::vector<int>(next_expected.begin(), next_expected.begin() + split_pos));\n\
    \        assert(suffix.to_vector() == std::vector<int>(next_expected.begin() +\
    \ split_pos, next_expected.end()));\n        assert(prefix.append(suffix).to_vector()\
    \ == next_expected);\n\n        if (next_expected.size() <= 100) {\n         \
    \   versions.push_back({next, next_expected});\n        }\n    }\n\n    long long\
    \ x, y;\n    fast_input >> x >> y;\n    fast_output << x + y << '\\n';\n}\n"
  dependsOn:
  - ds/dynamic_array/persistent_dynamic_array.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
- /verify/verify/ds/dynamic_array/persistent_dynamic_array.test.cpp.html
title: verify/ds/dynamic_array/persistent_dynamic_array.test.cpp
---
