---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_set.hpp
    title: Persistent Ordered Set
  - icon: ':heavy_check_mark:'
    path: ds/deque/persistent_deque.hpp
    title: Persistent Deque
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/persistent_binary_node_pool.hpp
    title: ds/detail/persistent_binary_node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: ds/dsu/partially_persistent_dsu.hpp
    title: Partially Persistent DSU
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_dsu.hpp
    title: Persistent DSU
  - icon: ':heavy_check_mark:'
    path: ds/dsu/persistent_potentialized_dsu.hpp
    title: Persistent Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_array.hpp
    title: Persistent Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
    title: Persistent Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/persistent_dynamic_monoid_array.hpp
    title: Persistent Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/queue/persistent_queue.hpp
    title: Persistent Queue
  - icon: ':heavy_check_mark:'
    path: ds/stack/persistent_stack.hpp
    title: Persistent Stack
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"verify/ds/persistent_release.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n#line 1 \"ds/bst/persistent_ordered_multiset.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n\n\n\n#line 6 \"ds/detail/persistent_binary_node_pool.hpp\"\n#include <deque>\n\
    #include <limits>\n#include <optional>\n#line 11 \"ds/detail/persistent_binary_node_pool.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\nnamespace detail {\n\n// Node must have\
    \ integer `l` and `r` members. New nodes initially have no\n// owner; discard_unreferenced()\
    \ removes temporary path-copy nodes after the\n// result roots have been retained.\n\
    template <class Node, int null_node = -1>\nstruct PersistentBinaryNodePool {\n\
    \   private:\n    std::deque<std::optional<Node>> _nodes;\n    std::vector<int>\
    \ _references;\n    std::vector<int> _next_free;\n    std::vector<int> _unowned;\n\
    \    int _first_free = -1;\n    std::size_t _live_nodes = 0;\n\n    void release_zero(int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      int left = (*_nodes[node]).l;\n        int right = (*_nodes[node]).r;\n\
    \        _nodes[node].reset();\n        _next_free[node] = _first_free;\n    \
    \    _first_free = node;\n        --_live_nodes;\n        if (left != null_node\
    \ && --_references[left] == 0) release_zero(left);\n        if (right != null_node\
    \ && --_references[right] == 0) release_zero(right);\n    }\n\n   public:\n  \
    \  PersistentBinaryNodePool() {\n        if constexpr (null_node == 0) {\n   \
    \         _nodes.emplace_back();\n            _references.push_back(0);\n    \
    \        _next_free.push_back(-1);\n        }\n    }\n\n    Node& operator[](int\
    \ node) {\n        assert(node != null_node && _nodes[node].has_value());\n  \
    \      return *_nodes[node];\n    }\n\n    const Node& operator[](int node) const\
    \ {\n        assert(node != null_node && _nodes[node].has_value());\n        return\
    \ *_nodes[node];\n    }\n\n    template <class... Args>\n    int emplace(Args&&...\
    \ args) {\n        int result;\n        if (_first_free == -1) {\n           \
    \ assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n    \
    \        result = int(_nodes.size());\n            _nodes.emplace_back(std::in_place,\
    \ std::forward<Args>(args)...);\n            _references.push_back(0);\n     \
    \       _next_free.push_back(-1);\n        } else {\n            result = _first_free;\n\
    \            _first_free = _next_free[result];\n            _nodes[result].emplace(std::forward<Args>(args)...);\n\
    \            _references[result] = 0;\n        }\n        retain((*_nodes[result]).l);\n\
    \        retain((*_nodes[result]).r);\n        _unowned.push_back(result);\n \
    \       ++_live_nodes;\n        return result;\n    }\n\n    void retain(int node)\
    \ {\n        if (node != null_node) {\n            assert(_nodes[node].has_value());\n\
    \            ++_references[node];\n        }\n    }\n\n    void release(int node)\
    \ {\n        if (node == null_node) return;\n        assert(_nodes[node].has_value()\
    \ && _references[node] > 0);\n        if (--_references[node] == 0) release_zero(node);\n\
    \    }\n\n    void discard_unreferenced() {\n        while (!_unowned.empty())\
    \ {\n            int node = _unowned.back();\n            _unowned.pop_back();\n\
    \            if (_nodes[node].has_value() && _references[node] == 0) release_zero(node);\n\
    \        }\n    }\n\n    void reserve(std::size_t) {}\n\n    int next_index()\
    \ const { return _first_free == -1 ? int(_nodes.size()) : _first_free; }\n\n \
    \   std::size_t size() const { return _live_nodes; }\n};\n\n}  // namespace detail\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/bst/persistent_ordered_multiset.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T, typename Compare>\n\
    struct PersistentOrderedSet;\n\ntemplate <typename T, typename Compare = std::less<T>>\n\
    struct PersistentOrderedMultiset {\n   private:\n    friend struct PersistentOrderedSet<T,\
    \ Compare>;\n    struct Node {\n        T key;\n        int count;\n        int\
    \ size;\n        int distinct_size;\n        int rank_color;\n        int l;\n\
    \        int r;\n        int min_leaf;\n        int max_leaf;\n\n        Node(T\
    \ value, int multiplicity, int maximum)\n            : key(std::move(value)),\n\
    \              count(multiplicity),\n              size(multiplicity),\n     \
    \         distinct_size(1),\n              rank_color(1),\n              l(-1),\n\
    \              r(-1),\n              min_leaf(maximum),\n              max_leaf(maximum)\
    \ {}\n\n        Node(T separator, int subtree_size, int left_size, int unique_count,\
    \ int node_rank,\n             int left, int right, int minimum, int maximum,\
    \ bool is_black)\n            : key(std::move(separator)),\n              count(left_size),\n\
    \              size(subtree_size),\n              distinct_size(unique_count),\n\
    \              rank_color(node_rank * 2 + int(is_black)),\n              l(left),\n\
    \              r(right),\n              min_leaf(minimum),\n              max_leaf(maximum)\
    \ {}\n    };\n\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n \
    \   inline static Pool pool;\n\n    int root;\n    Compare comp;\n\n    static\
    \ int subtree_size(int t) { return t == -1 ? 0 : pool[t].size; }\n    static int\
    \ subtree_distinct_size(int t) { return t == -1 ? 0 : pool[t].distinct_size; }\n\
    \    static int node_rank(int t) { return pool[t].rank_color >> 1; }\n    static\
    \ bool is_black(int t) { return (pool[t].rank_color & 1) != 0; }\n    static bool\
    \ is_leaf(int t) { return pool[t].l == -1; }\n\n    bool equal(const T& a, const\
    \ T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\n    static\
    \ int make_leaf(T key, int count) {\n        const int id = pool.next_index();\n\
    \        return pool.emplace(std::move(key), count, id);\n    }\n\n    static\
    \ int make_node(int l, int r, bool black) {\n        assert(l != -1 && r != -1);\n\
    \        const int rank = node_rank(l) + int(is_black(l));\n        assert(rank\
    \ == node_rank(r) + int(is_black(r)));\n        return pool.emplace(pool[pool[l].max_leaf].key,\n\
    \                            subtree_size(l) + subtree_size(r),\n            \
    \                subtree_size(l),\n                            subtree_distinct_size(l)\
    \ + subtree_distinct_size(r),\n                            rank, l, r, pool[l].min_leaf,\
    \ pool[r].max_leaf,\n                            black);\n    }\n\n    static\
    \ int as_root(int t) {\n        if (t == -1 || is_black(t)) return t;\n      \
    \  return make_node(pool[t].l, pool[t].r, true);\n    }\n\n    static int merge_sub(int\
    \ a, int b) {\n        assert(a != -1 && b != -1);\n        if (node_rank(a) <\
    \ node_rank(b)) {\n            const Node& right = pool[b];\n            int c\
    \ = merge_sub(a, right.l);\n            if (is_black(b) && !is_black(c) && !is_black(pool[c].l))\
    \ {\n                const Node& middle = pool[c];\n                if (is_black(right.r))\
    \ {\n                    return make_node(middle.l,\n                        \
    \             make_node(middle.r, right.r, false),\n                         \
    \            true);\n                }\n                const Node& far = pool[right.r];\n\
    \                return make_node(make_node(middle.l, middle.r, true),\n     \
    \                            make_node(far.l, far.r, true),\n                \
    \                 false);\n            }\n            return make_node(c, right.r,\
    \ is_black(b));\n        }\n        if (node_rank(a) > node_rank(b)) {\n     \
    \       const Node& left = pool[a];\n            int c = merge_sub(left.r, b);\n\
    \            if (is_black(a) && !is_black(c) && !is_black(pool[c].r)) {\n    \
    \            const Node& middle = pool[c];\n                if (is_black(left.l))\
    \ {\n                    return make_node(make_node(left.l, middle.l, false),\n\
    \                                     middle.r, true);\n                }\n  \
    \              const Node& far = pool[left.l];\n                return make_node(make_node(far.l,\
    \ far.r, true),\n                                 make_node(middle.l, middle.r,\
    \ true),\n                                 false);\n            }\n          \
    \  return make_node(left.l, c, is_black(a));\n        }\n        return make_node(a,\
    \ b, false);\n    }\n\n    static int merge_nodes(int a, int b) {\n        if\
    \ (a == -1 || b == -1) return a == -1 ? b : a;\n        return as_root(merge_sub(as_root(a),\
    \ as_root(b)));\n    }\n\n    std::pair<int, int> split_nodes(int t, const T&\
    \ key) const {\n        if (t == -1) return {-1, -1};\n        const Node& node\
    \ = pool[t];\n        if (is_leaf(t)) return comp(node.key, key) ? std::pair{t,\
    \ -1} : std::pair{-1, t};\n        if (comp(node.key, key)) {\n            auto\
    \ [l, r] = split_nodes(node.r, key);\n            return {merge_nodes(as_root(node.l),\
    \ l), r};\n        }\n        auto [l, r] = split_nodes(node.l, key);\n      \
    \  return {l, merge_nodes(r, as_root(node.r))};\n    }\n\n    int change_count_impl(int\
    \ t, const T& key, int delta, int& old_count) const {\n        if (t == -1) return\
    \ -1;\n        const Node& node = pool[t];\n        if (is_leaf(t)) {\n      \
    \      if (!equal(node.key, key)) return t;\n            old_count = node.count;\n\
    \            return node.count + delta == 0 ? t : make_leaf(node.key, node.count\
    \ + delta);\n        }\n        int child;\n        if (!comp(node.key, key))\
    \ {\n            child = change_count_impl(node.l, key, delta, old_count);\n \
    \           if (old_count == 0 || old_count + delta == 0) return t;\n        \
    \    return make_node(child, node.r, is_black(t));\n        }\n        child =\
    \ change_count_impl(node.r, key, delta, old_count);\n        if (old_count ==\
    \ 0 || old_count + delta == 0) return t;\n        return make_node(node.l, child,\
    \ is_black(t));\n    }\n\n    int count_impl(int t, const T& key) const {\n  \
    \      if (t == -1) return 0;\n        while (!is_leaf(t)) {\n            t =\
    \ !comp(pool[t].key, key) ? pool[t].l : pool[t].r;\n        }\n        return\
    \ equal(pool[t].key, key) ? pool[t].count : 0;\n    }\n\n    const T* kth_impl(int\
    \ t, int k) const {\n        while (!is_leaf(t)) {\n            const int left_size\
    \ = pool[t].count;\n            if (k < left_size) {\n                t = pool[t].l;\n\
    \            } else {\n                k -= left_size;\n                t = pool[t].r;\n\
    \            }\n        }\n        return &pool[t].key;\n    }\n\n    int order_of_key_impl(int\
    \ t, const T& key, bool upper) const {\n        int result = 0;\n        while\
    \ (t != -1 && !is_leaf(t)) {\n            const Node& node = pool[t];\n      \
    \      const T& separator = node.key;\n            const bool take_left = upper\
    \ ? !comp(key, separator) : comp(separator, key);\n            if (take_left)\
    \ {\n                result += node.count;\n                t = node.r;\n    \
    \        } else {\n                t = node.l;\n            }\n        }\n   \
    \     if (t != -1) {\n            const bool take_leaf = upper ? !comp(key, pool[t].key)\
    \ : comp(pool[t].key, key);\n            if (take_leaf) result += pool[t].count;\n\
    \        }\n        return result;\n    }\n\n    const T* lower_bound_impl(int\
    \ t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != -1) {\n            const Node& node = pool[t];\n        \
    \    if (is_leaf(t)) {\n                const bool candidate = strict ? comp(key,\
    \ node.key) : !comp(node.key, key);\n                return candidate ? &node.key\
    \ : result;\n            }\n            const T& separator = node.key;\n     \
    \       const bool go_left = strict ? comp(key, separator) : !comp(separator,\
    \ key);\n            if (go_left) {\n                result = &pool[pool[node.r].min_leaf].key;\n\
    \                t = node.l;\n            } else {\n                t = node.r;\n\
    \            }\n        }\n        return result;\n    }\n\n    const T* max_less_impl(int\
    \ t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != -1) {\n            const Node& node = pool[t];\n        \
    \    if (is_leaf(t)) {\n                const bool candidate = strict ? comp(node.key,\
    \ key) : !comp(key, node.key);\n                return candidate ? &node.key :\
    \ result;\n            }\n            const T& separator = node.key;\n       \
    \     const bool take_left = strict ? comp(separator, key) : !comp(key, separator);\n\
    \            if (take_left) {\n                result = &separator;\n        \
    \        t = node.r;\n            } else {\n                t = node.l;\n    \
    \        }\n        }\n        return result;\n    }\n\n    static void dump_impl(int\
    \ t, std::vector<T>& result) {\n        if (t == -1) return;\n        const Node&\
    \ node = pool[t];\n        if (is_leaf(t)) {\n            for (int i = 0; i <\
    \ node.count; ++i) result.push_back(node.key);\n            return;\n        }\n\
    \        dump_impl(node.l, result);\n        dump_impl(node.r, result);\n    }\n\
    \n    static std::pair<int, int> pop_min(int t) {\n        assert(t != -1);\n\
    \        const Node& node = pool[t];\n        if (is_leaf(t)) return {t, -1};\n\
    \        auto [minimum, rest] = pop_min(node.l);\n        return {minimum, merge_nodes(rest,\
    \ as_root(node.r))};\n    }\n\n    PersistentOrderedMultiset(int node, Compare\
    \ compare) : root(node), comp(std::move(compare)) {\n        pool.retain(root);\n\
    \    }\n\n    PersistentOrderedMultiset make_version(int node) const {\n     \
    \   PersistentOrderedMultiset result(node, comp);\n        pool.discard_unreferenced();\n\
    \        return result;\n    }\n\n   public:\n    explicit PersistentOrderedMultiset(Compare\
    \ compare) : root(-1), comp(std::move(compare)) {}\n    PersistentOrderedMultiset()\
    \ : PersistentOrderedMultiset(Compare()) {}\n\n    PersistentOrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        for (const T& x : init) *this = insert(x);\n    }\n\n    template\
    \ <typename Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator\
    \ last, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) *this = insert(*first++);\n    }\n\n    PersistentOrderedMultiset(const\
    \ PersistentOrderedMultiset& other)\n        : root(other.root), comp(other.comp)\
    \ {\n        pool.retain(root);\n    }\n\n    PersistentOrderedMultiset(PersistentOrderedMultiset&&\
    \ other)\n        : root(other.root), comp(std::move(other.comp)) {\n        other.root\
    \ = -1;\n    }\n\n    PersistentOrderedMultiset& operator=(const PersistentOrderedMultiset&\
    \ other) {\n        if (this == &other) return *this;\n        pool.retain(other.root);\n\
    \        pool.release(root);\n        root = other.root;\n        comp = other.comp;\n\
    \        return *this;\n    }\n\n    PersistentOrderedMultiset& operator=(PersistentOrderedMultiset&&\
    \ other) {\n        if (this == &other) return *this;\n        pool.release(root);\n\
    \        root = other.root;\n        comp = std::move(other.comp);\n        other.root\
    \ = -1;\n        return *this;\n    }\n\n    ~PersistentOrderedMultiset() { pool.release(root);\
    \ }\n\n    int size() const { return subtree_size(root); }\n    int unique_size()\
    \ const { return subtree_distinct_size(root); }\n    bool empty() const { return\
    \ root == -1; }\n    void release() { pool.release(std::exchange(root, -1)); }\n\
    \    std::size_t node_count() const { return pool.size(); }\n    PersistentOrderedMultiset\
    \ clear() const { return make_version(-1); }\n\n    PersistentOrderedMultiset\
    \ insert(T key, int multiplicity = 1) const {\n        assert(multiplicity > 0);\n\
    \        int old_count = 0;\n        const int changed_root = change_count_impl(root,\
    \ key, multiplicity, old_count);\n        if (old_count != 0) {\n            return\
    \ make_version(changed_root);\n        }\n        auto [l, r] = split_nodes(root,\
    \ key);\n        return make_version(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ multiplicity)), r));\n    }\n\n   private:\n    PersistentOrderedMultiset insert_unique(T\
    \ key) const {\n        if (contains(key)) return *this;\n        auto [l, r]\
    \ = split_nodes(root, key);\n        return make_version(merge_nodes(merge_nodes(l,\
    \ make_leaf(std::move(key), 1)), r));\n    }\n\n   public:\n    PersistentOrderedMultiset\
    \ erase_one(const T& key) const {\n        int old_count = 0;\n        const int\
    \ changed_root = change_count_impl(root, key, -1, old_count);\n        if (old_count\
    \ == 0) return *this;\n        if (old_count > 1) return make_version(changed_root);\n\
    \        auto [l, r] = split_nodes(root, key);\n        auto [discarded, rest]\
    \ = pop_min(r);\n        assert(equal(pool[discarded].key, key));\n        return\
    \ make_version(merge_nodes(l, rest));\n    }\n\n    PersistentOrderedMultiset\
    \ erase(const T& key) const { return erase_one(key); }\n\n    PersistentOrderedMultiset\
    \ erase_all(const T& key) const {\n        const int old_count = count(key);\n\
    \        if (old_count == 0) return *this;\n        auto [l, r] = split_nodes(root,\
    \ key);\n        auto [discarded, rest] = pop_min(r);\n        assert(equal(pool[discarded].key,\
    \ key));\n        return make_version(merge_nodes(l, rest));\n    }\n\n    bool\
    \ contains(const T& key) const { return count(key) > 0; }\n    int count(const\
    \ T& key) const { return count_impl(root, key); }\n\n    const T* find_by_order(int\
    \ k) const {\n        assert(0 <= k && k < size());\n        return kth_impl(root,\
    \ k);\n    }\n\n    T kth(int k) const { return *find_by_order(k); }\n    int\
    \ order_of_key(const T& key) const { return order_of_key_impl(root, key, false);\
    \ }\n    int count_less(const T& key) const { return order_of_key(key); }\n  \
    \  int count_less_equal(const T& key) const { return order_of_key_impl(root, key,\
    \ true); }\n    int count_greater(const T& key) const { return size() - count_less_equal(key);\
    \ }\n    int count_greater_equal(const T& key) const { return size() - count_less(key);\
    \ }\n    const T* lower_bound(const T& key) const { return lower_bound_impl(root,\
    \ key, false); }\n    const T* upper_bound(const T& key) const { return lower_bound_impl(root,\
    \ key, true); }\n    const T* min_ge(const T& key) const { return lower_bound(key);\
    \ }\n    const T* min_gt(const T& key) const { return upper_bound(key); }\n  \
    \  const T* max_le(const T& key) const { return max_less_impl(root, key, false);\
    \ }\n    const T* max_lt(const T& key) const { return max_less_impl(root, key,\
    \ true); }\n    const T* min() const { return empty() ? nullptr : &pool[pool[root].min_leaf].key;\
    \ }\n    const T* max() const { return empty() ? nullptr : &pool[pool[root].max_leaf].key;\
    \ }\n\n    std::pair<PersistentOrderedMultiset, PersistentOrderedMultiset> split(const\
    \ T& key) const {\n        auto [l, r] = split_nodes(root, key);\n        PersistentOrderedMultiset\
    \ left(l, comp);\n        PersistentOrderedMultiset right(r, comp);\n        pool.discard_unreferenced();\n\
    \        return {std::move(left), std::move(right)};\n    }\n\n    PersistentOrderedMultiset\
    \ merge(const PersistentOrderedMultiset& other) const {\n        assert(empty()\
    \ || other.empty() || comp(*max(), *other.min()));\n        return make_version(merge_nodes(root,\
    \ other.root));\n    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T>\
    \ result;\n        result.reserve(size());\n        dump_impl(root, result);\n\
    \        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/bst/persistent_ordered_set.hpp\"\n\n\n\n#line 9 \"ds/bst/persistent_ordered_set.hpp\"\
    \n\n#line 11 \"ds/bst/persistent_ordered_set.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct PersistentOrderedSet\
    \ {\n   private:\n    using Multiset = PersistentOrderedMultiset<T, Compare>;\n\
    \n    Multiset data;\n\n    explicit PersistentOrderedSet(Multiset multiset) :\
    \ data(std::move(multiset)) {}\n\n   public:\n    explicit PersistentOrderedSet(Compare\
    \ compare) : data(std::move(compare)) {}\n\n    PersistentOrderedSet() : PersistentOrderedSet(Compare())\
    \ {}\n\n    PersistentOrderedSet(std::initializer_list<T> init, Compare compare\
    \ = Compare())\n        : PersistentOrderedSet(std::move(compare)) {\n       \
    \ for (const T& x : init) *this = insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    PersistentOrderedSet(Iterator first, Iterator last, Compare compare\
    \ = Compare())\n        : PersistentOrderedSet(std::move(compare)) {\n       \
    \ while (first != last) {\n            *this = insert(*first);\n            ++first;\n\
    \        }\n    }\n\n    int size() const {\n        return data.size();\n   \
    \ }\n\n    int unique_size() const {\n        return data.size();\n    }\n\n \
    \   bool empty() const {\n        return data.empty();\n    }\n\n    void release()\
    \ {\n        data.release();\n    }\n\n    std::size_t node_count() const {\n\
    \        return data.node_count();\n    }\n\n    PersistentOrderedSet clear()\
    \ const {\n        return PersistentOrderedSet(data.clear());\n    }\n\n    PersistentOrderedSet\
    \ insert(T key) const {\n        return PersistentOrderedSet(data.insert_unique(std::move(key)));\n\
    \    }\n\n    PersistentOrderedSet erase(const T& key) const {\n        return\
    \ PersistentOrderedSet(data.erase(key));\n    }\n\n    bool contains(const T&\
    \ key) const {\n        return data.contains(key);\n    }\n\n    int count(const\
    \ T& key) const {\n        return contains(key) ? 1 : 0;\n    }\n\n    const T*\
    \ find_by_order(int k) const {\n        return data.find_by_order(k);\n    }\n\
    \n    T kth(int k) const {\n        return data.kth(k);\n    }\n\n    int order_of_key(const\
    \ T& key) const {\n        return data.order_of_key(key);\n    }\n\n    int count_less(const\
    \ T& key) const {\n        return data.count_less(key);\n    }\n\n    int count_less_equal(const\
    \ T& key) const {\n        return data.count_less_equal(key);\n    }\n\n    int\
    \ count_greater(const T& key) const {\n        return data.count_greater(key);\n\
    \    }\n\n    int count_greater_equal(const T& key) const {\n        return data.count_greater_equal(key);\n\
    \    }\n\n    const T* lower_bound(const T& key) const {\n        return data.lower_bound(key);\n\
    \    }\n\n    const T* upper_bound(const T& key) const {\n        return data.upper_bound(key);\n\
    \    }\n\n    const T* min_ge(const T& key) const {\n        return data.min_ge(key);\n\
    \    }\n\n    const T* min_gt(const T& key) const {\n        return data.min_gt(key);\n\
    \    }\n\n    const T* max_le(const T& key) const {\n        return data.max_le(key);\n\
    \    }\n\n    const T* max_lt(const T& key) const {\n        return data.max_lt(key);\n\
    \    }\n\n    const T* min() const {\n        return data.min();\n    }\n\n  \
    \  const T* max() const {\n        return data.max();\n    }\n\n    std::pair<PersistentOrderedSet,\
    \ PersistentOrderedSet> split(const T& key) const {\n        auto [l, r] = data.split(key);\n\
    \        return {PersistentOrderedSet(std::move(l)), PersistentOrderedSet(std::move(r))};\n\
    \    }\n\n    PersistentOrderedSet merge(const PersistentOrderedSet& other) const\
    \ {\n        return PersistentOrderedSet(data.merge(other.data));\n    }\n\n \
    \   std::vector<T> to_vector() const {\n        return data.to_vector();\n   \
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/deque/persistent_deque.hpp\"\
    \n\n\n\n#line 6 \"ds/deque/persistent_deque.hpp\"\n#include <cstdint>\n#line 8\
    \ \"ds/deque/persistent_deque.hpp\"\n#include <memory>\n#line 12 \"ds/deque/persistent_deque.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Okasaki's purely persistent real-time\
    \ deque.\ntemplate <class T>\nstruct PersistentDeque {\n   private:\n    static\
    \ constexpr int balance_factor = 2;\n\n    enum class StreamKind : std::uint8_t\
    \ {\n        cons,\n        take,\n        rotate_drop,\n        rotate_reverse,\n\
    \    };\n\n    // The three integer fields contain either an evaluated cons cell\
    \ or the\n    // arguments of one incremental stream operation.\n    struct StreamNode\
    \ {\n        mutable StreamKind kind;\n        mutable int first;\n        mutable\
    \ int second;\n        mutable int third;\n\n        StreamNode(\n           \
    \ StreamKind node_kind,\n            int first_argument,\n            int second_argument,\n\
    \            int third_argument = -1\n        )\n            : kind(node_kind),\n\
    \              first(first_argument),\n              second(second_argument),\n\
    \              third(third_argument) {}\n    };\n\n    struct Pool {\n       \
    \ std::deque<std::optional<T>> values;\n        std::deque<std::optional<StreamNode>>\
    \ streams;\n        std::vector<int> value_references, stream_references;\n  \
    \      std::vector<int> next_free_value, next_free_stream;\n        std::vector<int>\
    \ unowned_values, unowned_streams;\n        int first_free_value = -1;\n     \
    \   int first_free_stream = -1;\n        std::size_t live_values = 0;\n      \
    \  std::size_t live_streams = 0;\n\n        void retain_value(int value) {\n \
    \           if (value != -1) ++value_references[value];\n        }\n\n       \
    \ void release_value(int value) {\n            if (value == -1) return;\n    \
    \        assert(values[value].has_value() && value_references[value] > 0);\n \
    \           if (--value_references[value] != 0) return;\n            values[value].reset();\n\
    \            next_free_value[value] = first_free_value;\n            first_free_value\
    \ = value;\n            --live_values;\n        }\n\n        void retain_stream(int\
    \ stream) {\n            if (stream != -1) ++stream_references[stream];\n    \
    \    }\n\n        void retain_dependencies(const StreamNode& node) {\n       \
    \     if (node.kind == StreamKind::cons) {\n                retain_value(node.first);\n\
    \                retain_stream(node.second);\n            } else if (node.kind\
    \ == StreamKind::take) {\n                retain_stream(node.first);\n       \
    \     } else if (node.kind == StreamKind::rotate_drop) {\n                retain_stream(node.first);\n\
    \                retain_stream(node.third);\n            } else {\n          \
    \      retain_stream(node.first);\n                retain_stream(node.second);\n\
    \                retain_stream(node.third);\n            }\n        }\n\n    \
    \    void release_zero_stream(int stream) {\n            std::vector<int> pending\
    \ = {stream};\n            while (!pending.empty()) {\n                int current\
    \ = pending.back();\n                pending.pop_back();\n                assert(streams[current].has_value()\
    \ && stream_references[current] == 0);\n                StreamNode node = *streams[current];\n\
    \                streams[current].reset();\n                next_free_stream[current]\
    \ = first_free_stream;\n                first_free_stream = current;\n       \
    \         --live_streams;\n\n                auto release_child = [&](int child)\
    \ {\n                    if (child != -1 && --stream_references[child] == 0) pending.push_back(child);\n\
    \                };\n                if (node.kind == StreamKind::cons) {\n  \
    \                  release_value(node.first);\n                    release_child(node.second);\n\
    \                } else if (node.kind == StreamKind::take) {\n               \
    \     release_child(node.first);\n                } else if (node.kind == StreamKind::rotate_drop)\
    \ {\n                    release_child(node.first);\n                    release_child(node.third);\n\
    \                } else {\n                    release_child(node.first);\n  \
    \                  release_child(node.second);\n                    release_child(node.third);\n\
    \                }\n            }\n        }\n\n        void release_stream(int\
    \ stream) {\n            if (stream == -1) return;\n            assert(streams[stream].has_value()\
    \ && stream_references[stream] > 0);\n            if (--stream_references[stream]\
    \ == 0) release_zero_stream(stream);\n        }\n\n        template <class...\
    \ Args>\n        int store_value(Args&&... args) {\n            int result;\n\
    \            if (first_free_value == -1) {\n                result = int(values.size());\n\
    \                values.emplace_back(std::in_place, std::forward<Args>(args)...);\n\
    \                value_references.push_back(0);\n                next_free_value.push_back(-1);\n\
    \            } else {\n                result = first_free_value;\n          \
    \      first_free_value = next_free_value[result];\n                values[result].emplace(std::forward<Args>(args)...);\n\
    \                value_references[result] = 0;\n            }\n            unowned_values.push_back(result);\n\
    \            ++live_values;\n            return result;\n        }\n\n       \
    \ int make_stream(StreamKind kind, int first, int second, int third) {\n     \
    \       int result;\n            if (first_free_stream == -1) {\n            \
    \    result = int(streams.size());\n                streams.emplace_back(std::in_place,\
    \ kind, first, second, third);\n                stream_references.push_back(0);\n\
    \                next_free_stream.push_back(-1);\n            } else {\n     \
    \           result = first_free_stream;\n                first_free_stream = next_free_stream[result];\n\
    \                streams[result].emplace(kind, first, second, third);\n      \
    \          stream_references[result] = 0;\n            }\n            retain_dependencies(*streams[result]);\n\
    \            unowned_streams.push_back(result);\n            ++live_streams;\n\
    \            return result;\n        }\n\n        void set_cons(int stream, int\
    \ value, int tail) {\n            retain_value(value);\n            retain_stream(tail);\n\
    \            StreamNode old = *streams[stream];\n            if (old.kind == StreamKind::take)\
    \ {\n                release_stream(old.first);\n            } else if (old.kind\
    \ == StreamKind::rotate_drop) {\n                release_stream(old.first);\n\
    \                release_stream(old.third);\n            } else if (old.kind ==\
    \ StreamKind::rotate_reverse) {\n                release_stream(old.first);\n\
    \                release_stream(old.second);\n                release_stream(old.third);\n\
    \            } else {\n                release_value(old.first);\n           \
    \     release_stream(old.second);\n            }\n            StreamNode& node\
    \ = *streams[stream];\n            node.kind = StreamKind::cons;\n           \
    \ node.first = value;\n            node.second = tail;\n            node.third\
    \ = -1;\n        }\n\n        void discard_unreferenced() {\n            while\
    \ (!unowned_streams.empty()) {\n                int stream = unowned_streams.back();\n\
    \                unowned_streams.pop_back();\n                if (streams[stream].has_value()\
    \ && stream_references[stream] == 0) release_zero_stream(stream);\n          \
    \  }\n            while (!unowned_values.empty()) {\n                int value\
    \ = unowned_values.back();\n                unowned_values.pop_back();\n     \
    \           if (values[value].has_value() && value_references[value] == 0) {\n\
    \                    values[value].reset();\n                    next_free_value[value]\
    \ = first_free_value;\n                    first_free_value = value;\n       \
    \             --live_values;\n                }\n            }\n        }\n\n\
    \        std::size_t size() const { return live_values + live_streams; }\n   \
    \ };\n\n    int _front_size;\n    int _front;\n    int _front_schedule;\n    int\
    \ _rear_size;\n    int _rear;\n    int _rear_schedule;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentDeque(\n        int front_size,\n        int front,\n\
    \        int front_schedule,\n        int rear_size,\n        int rear,\n    \
    \    int rear_schedule,\n        std::shared_ptr<Pool> pool\n    )\n        :\
    \ _front_size(front_size),\n          _front(front),\n          _front_schedule(front_schedule),\n\
    \          _rear_size(rear_size),\n          _rear(rear),\n          _rear_schedule(rear_schedule),\n\
    \          _pool(std::move(pool)) {\n        retain_state();\n        _pool->discard_unreferenced();\n\
    \    }\n\n    void retain_state() const {\n        _pool->retain_stream(_front);\n\
    \        _pool->retain_stream(_front_schedule);\n        _pool->retain_stream(_rear);\n\
    \        _pool->retain_stream(_rear_schedule);\n    }\n\n    void release_state()\
    \ const {\n        _pool->release_stream(_front);\n        _pool->release_stream(_front_schedule);\n\
    \        _pool->release_stream(_rear);\n        _pool->release_stream(_rear_schedule);\n\
    \    }\n\n    template <class... Args>\n    int store_value(Args&&... args) const\
    \ {\n        return _pool->store_value(std::forward<Args>(args)...);\n    }\n\n\
    \    int make_stream(\n        StreamKind kind,\n        int first,\n        int\
    \ second,\n        int third = -1\n    ) const {\n        return _pool->make_stream(kind,\
    \ first, second, third);\n    }\n\n    int make_cons(int value_index, int tail)\
    \ const {\n        return make_stream(StreamKind::cons, value_index, tail);\n\
    \    }\n\n    int make_take(int count, int stream) const {\n        if (count\
    \ == 0) return -1;\n        assert(count > 0 && stream != -1);\n        return\
    \ make_stream(StreamKind::take, stream, count);\n    }\n\n    int make_rotate_drop(int\
    \ rear, int count, int front) const {\n        return make_stream(StreamKind::rotate_drop,\
    \ rear, count, front);\n    }\n\n    int make_rotate_reverse(int rear, int front,\
    \ int accumulator) const {\n        return make_stream(\n            StreamKind::rotate_reverse,\n\
    \            rear,\n            front,\n            accumulator\n        );\n\
    \    }\n\n    void set_cons(int stream, int value_index, int tail) const {\n \
    \       _pool->set_cons(stream, value_index, tail);\n    }\n\n    int stream_head(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return (*_pool->streams[stream]).first;\n    }\n\n    int stream_tail(int\
    \ stream) const {\n        assert(stream != -1);\n        force(stream);\n   \
    \     return (*_pool->streams[stream]).second;\n    }\n\n    int drop(int stream,\
    \ int count) const {\n        assert(count >= 0);\n        while (count > 0) {\n\
    \            assert(stream != -1);\n            stream = stream_tail(stream);\n\
    \            count--;\n        }\n        return stream;\n    }\n\n    // Reverses\
    \ a bounded prefix onto accumulator and returns the unconsumed\n    // suffix\
    \ together with the new accumulator.\n    std::pair<int, int> reverse_prefix(\n\
    \        int stream,\n        int count,\n        int accumulator\n    ) const\
    \ {\n        while (count > 0 && stream != -1) {\n            int value_index\
    \ = stream_head(stream);\n            stream = stream_tail(stream);\n        \
    \    accumulator = make_cons(value_index, accumulator);\n            count--;\n\
    \        }\n        return {stream, accumulator};\n    }\n\n    void force(int\
    \ stream) const {\n        assert(stream != -1);\n        StreamNode node = *_pool->streams[stream];\n\
    \        if (node.kind == StreamKind::cons) return;\n\n        if (node.kind ==\
    \ StreamKind::take) {\n            int source = node.first;\n            int count\
    \ = node.second;\n            assert(source != -1 && count > 0);\n           \
    \ int value_index = stream_head(source);\n            int tail = make_take(count\
    \ - 1, stream_tail(source));\n            set_cons(stream, value_index, tail);\n\
    \            return;\n        }\n\n        if (node.kind == StreamKind::rotate_drop)\
    \ {\n            int rear = node.first;\n            int count = node.second;\n\
    \            int front = node.third;\n            if (count < balance_factor ||\
    \ rear == -1) {\n                assert(count <= balance_factor || rear != -1);\n\
    \                int result = make_rotate_reverse(\n                    rear,\n\
    \                    drop(front, count),\n                    -1\n           \
    \     );\n                set_cons(stream, stream_head(result), stream_tail(result));\n\
    \                return;\n            }\n            assert(rear != -1);\n   \
    \         int value_index = stream_head(rear);\n            int tail = make_rotate_drop(\n\
    \                stream_tail(rear),\n                count - balance_factor,\n\
    \                drop(front, balance_factor)\n            );\n            set_cons(stream,\
    \ value_index, tail);\n            return;\n        }\n\n        assert(node.kind\
    \ == StreamKind::rotate_reverse);\n        int rear = node.first;\n        int\
    \ front = node.second;\n        int accumulator = node.third;\n        if (rear\
    \ == -1) {\n            auto [remaining, result] = reverse_prefix(\n         \
    \       front,\n                balance_factor + 1,\n                accumulator\n\
    \            );\n            assert(remaining == -1 && result != -1);\n      \
    \      set_cons(stream, stream_head(result), stream_tail(result));\n         \
    \   return;\n        }\n\n        int value_index = stream_head(rear);\n     \
    \   auto [remaining, next_accumulator] = reverse_prefix(\n            front,\n\
    \            balance_factor,\n            accumulator\n        );\n        int\
    \ tail = make_rotate_reverse(\n            stream_tail(rear),\n            remaining,\n\
    \            next_accumulator\n        );\n        set_cons(stream, value_index,\
    \ tail);\n    }\n\n    int execute_once(int schedule) const {\n        return\
    \ schedule == -1 ? -1 : stream_tail(schedule);\n    }\n\n    int execute_twice(int\
    \ schedule) const {\n        return execute_once(execute_once(schedule));\n  \
    \  }\n\n    PersistentDeque check(\n        int front_size,\n        int front,\n\
    \        int front_schedule,\n        int rear_size,\n        int rear,\n    \
    \    int rear_schedule\n    ) const {\n        if (front_size > balance_factor\
    \ * rear_size + 1) {\n            int next_front_size = (front_size + rear_size)\
    \ / 2;\n            int next_rear_size = front_size + rear_size - next_front_size;\n\
    \            int next_front = make_take(next_front_size, front);\n           \
    \ int next_rear = make_rotate_drop(\n                rear,\n                next_front_size,\n\
    \                front\n            );\n            return PersistentDeque(\n\
    \                next_front_size,\n                next_front,\n             \
    \   next_front,\n                next_rear_size,\n                next_rear,\n\
    \                next_rear,\n                _pool\n            );\n        }\n\
    \n        if (rear_size > balance_factor * front_size + 1) {\n            int\
    \ next_front_size = (front_size + rear_size) / 2;\n            int next_rear_size\
    \ = front_size + rear_size - next_front_size;\n            int next_front = make_rotate_drop(\n\
    \                front,\n                next_rear_size,\n                rear\n\
    \            );\n            int next_rear = make_take(next_rear_size, rear);\n\
    \            return PersistentDeque(\n                next_front_size,\n     \
    \           next_front,\n                next_front,\n                next_rear_size,\n\
    \                next_rear,\n                next_rear,\n                _pool\n\
    \            );\n        }\n\n        return PersistentDeque(\n            front_size,\n\
    \            front,\n            front_schedule,\n            rear_size,\n   \
    \         rear,\n            rear_schedule,\n            _pool\n        );\n \
    \   }\n\n   public:\n    PersistentDeque()\n        : _front_size(0),\n      \
    \    _front(-1),\n          _front_schedule(-1),\n          _rear_size(0),\n \
    \         _rear(-1),\n          _rear_schedule(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentDeque(const PersistentDeque& other)\n        : _front_size(other._front_size),\n\
    \          _front(other._front),\n          _front_schedule(other._front_schedule),\n\
    \          _rear_size(other._rear_size),\n          _rear(other._rear),\n    \
    \      _rear_schedule(other._rear_schedule),\n          _pool(other._pool) {\n\
    \        if (_pool) retain_state();\n    }\n\n    PersistentDeque(PersistentDeque&&\
    \ other) noexcept\n        : _front_size(other._front_size),\n          _front(other._front),\n\
    \          _front_schedule(other._front_schedule),\n          _rear_size(other._rear_size),\n\
    \          _rear(other._rear),\n          _rear_schedule(other._rear_schedule),\n\
    \          _pool(std::move(other._pool)) {\n        other._front_size = other._rear_size\
    \ = 0;\n        other._front = other._front_schedule = other._rear = other._rear_schedule\
    \ = -1;\n    }\n\n    PersistentDeque& operator=(const PersistentDeque& other)\
    \ {\n        if (this == &other) return *this;\n        if (other._pool) other.retain_state();\n\
    \        if (_pool) release_state();\n        _front_size = other._front_size;\n\
    \        _front = other._front;\n        _front_schedule = other._front_schedule;\n\
    \        _rear_size = other._rear_size;\n        _rear = other._rear;\n      \
    \  _rear_schedule = other._rear_schedule;\n        _pool = other._pool;\n    \
    \    return *this;\n    }\n\n    PersistentDeque& operator=(PersistentDeque&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ release_state();\n        _front_size = other._front_size;\n        _front =\
    \ other._front;\n        _front_schedule = other._front_schedule;\n        _rear_size\
    \ = other._rear_size;\n        _rear = other._rear;\n        _rear_schedule =\
    \ other._rear_schedule;\n        _pool = std::move(other._pool);\n        other._front_size\
    \ = other._rear_size = 0;\n        other._front = other._front_schedule = other._rear\
    \ = other._rear_schedule = -1;\n        return *this;\n    }\n\n    ~PersistentDeque()\
    \ {\n        if (_pool) release_state();\n    }\n\n    int size() const {\n  \
    \      return _front_size + _rear_size;\n    }\n\n    bool empty() const {\n \
    \       return size() == 0;\n    }\n\n    void release() {\n        if (_pool)\
    \ release_state();\n        _front_size = _rear_size = 0;\n        _front = _front_schedule\
    \ = _rear = _rear_schedule = -1;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    const T& front() const {\n        assert(!empty());\n        int\
    \ stream = _front == -1 ? _rear : _front;\n        int value = stream_head(stream);\n\
    \        _pool->discard_unreferenced();\n        return *_pool->values[value];\n\
    \    }\n\n    const T& back() const {\n        assert(!empty());\n        int\
    \ stream = _rear == -1 ? _front : _rear;\n        int value = stream_head(stream);\n\
    \        _pool->discard_unreferenced();\n        return *_pool->values[value];\n\
    \    }\n\n    PersistentDeque push_front(T value) const {\n        return emplace_front(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentDeque emplace_front(Args&&...\
    \ args) const {\n        int value_index = store_value(std::forward<Args>(args)...);\n\
    \        return check(\n            _front_size + 1,\n            make_cons(value_index,\
    \ _front),\n            execute_once(_front_schedule),\n            _rear_size,\n\
    \            _rear,\n            execute_once(_rear_schedule)\n        );\n  \
    \  }\n\n    PersistentDeque push_back(T value) const {\n        return emplace_back(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    PersistentDeque emplace_back(Args&&...\
    \ args) const {\n        int value_index = store_value(std::forward<Args>(args)...);\n\
    \        return check(\n            _front_size,\n            _front,\n      \
    \      execute_once(_front_schedule),\n            _rear_size + 1,\n         \
    \   make_cons(value_index, _rear),\n            execute_once(_rear_schedule)\n\
    \        );\n    }\n\n    PersistentDeque pop_front() const {\n        assert(!empty());\n\
    \        if (size() == 1) return clear();\n        assert(_front != -1);\n   \
    \     return check(\n            _front_size - 1,\n            stream_tail(_front),\n\
    \            execute_twice(_front_schedule),\n            _rear_size,\n      \
    \      _rear,\n            execute_twice(_rear_schedule)\n        );\n    }\n\n\
    \    PersistentDeque pop_back() const {\n        assert(!empty());\n        if\
    \ (size() == 1) return clear();\n        assert(_rear != -1);\n        return\
    \ check(\n            _front_size,\n            _front,\n            execute_twice(_front_schedule),\n\
    \            _rear_size - 1,\n            stream_tail(_rear),\n            execute_twice(_rear_schedule)\n\
    \        );\n    }\n\n    PersistentDeque clear() const {\n        return PersistentDeque(0,\
    \ -1, -1, 0, -1, -1, _pool);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"ds/dsu/partially_persistent_dsu.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 9 \"ds/dsu/partially_persistent_dsu.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\nstruct PartiallyPersistentDsu {\n   private:\n    static constexpr int\
    \ never = std::numeric_limits<int>::max();\n\n    int _n;\n    int _time;\n  \
    \  std::vector<int> parent;\n    std::vector<int> parent_time;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> size_history;\n\n    static int check_size(int n) {\n        assert(0\
    \ <= n);\n        return n;\n    }\n\n    void check_time(int t) const {\n   \
    \     assert(0 <= t && t <= _time);\n    }\n\n   public:\n    PartiallyPersistentDsu()\
    \ : PartiallyPersistentDsu(0) {}\n\n    explicit PartiallyPersistentDsu(int n)\n\
    \        : _n(check_size(n)), _time(0), parent(_n, -1), parent_time(_n, never),\
    \ size_history(_n) {\n        for (int i = 0; i < _n; i++) size_history[i].emplace_back(0,\
    \ 1);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Releases the complete\
    \ history and resets this object to an empty DSU.\n    void release() {\n    \
    \    _n = 0;\n        _time = 0;\n        std::vector<int>().swap(parent);\n \
    \       std::vector<int>().swap(parent_time);\n        std::vector<std::vector<std::pair<int,\
    \ int>>>().swap(size_history);\n    }\n\n    int time() const {\n        return\
    \ _time;\n    }\n\n    int leader(int t, int a) const {\n        check_time(t);\n\
    \        assert(0 <= a && a < _n);\n        while (parent_time[a] <= t) a = parent[a];\n\
    \        return a;\n    }\n\n    int leader(int a) const {\n        return leader(_time,\
    \ a);\n    }\n\n    bool same(int t, int a, int b) const {\n        check_time(t);\n\
    \        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n      \
    \  return leader(t, a) == leader(t, b);\n    }\n\n    bool same(int a, int b)\
    \ const {\n        return same(_time, a, b);\n    }\n\n    int group_size(int\
    \ t, int a) const {\n        int r = leader(t, a);\n        const auto& h = size_history[r];\n\
    \        auto it = std::upper_bound(h.begin(), h.end(), std::pair<int, int>(t,\
    \ never));\n        --it;\n        return it->second;\n    }\n\n    int group_size(int\
    \ a) const {\n        return -parent[leader(a)];\n    }\n\n    int size(int t,\
    \ int a) const {\n        return group_size(t, a);\n    }\n\n    int size(int\
    \ a) const {\n        return group_size(a);\n    }\n\n    bool merge(int a, int\
    \ b) {\n        assert(0 <= a && a < _n);\n        assert(0 <= b && b < _n);\n\
    \        ++_time;\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return false;\n        if (-parent[x] < -parent[y]) {\n            std::swap(x,\
    \ y);\n        }\n        parent[x] += parent[y];\n        parent[y] = x;\n  \
    \      parent_time[y] = _time;\n        size_history[x].emplace_back(_time, -parent[x]);\n\
    \        return true;\n    }\n\n    std::vector<std::vector<int>> groups(int t)\
    \ const {\n        check_time(t);\n        std::vector<int> leader_buf(_n), group_size(_n);\n\
    \        for (int i = 0; i < _n; i++) {\n            leader_buf[i] = leader(t,\
    \ i);\n            group_size[leader_buf[i]]++;\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n\
    \        }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n\n    std::vector<std::vector<int>>\
    \ groups() const {\n        return groups(_time);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"ds/dsu/persistent_dsu.hpp\"\n\n\n\n\
    #line 10 \"ds/dsu/persistent_dsu.hpp\"\n\n#line 12 \"ds/dsu/persistent_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nstruct PersistentDsu {\n   private:\n\
    \    struct Node {\n        int val;\n        int l, r;\n\n        Node() : val(0),\
    \ l(0), r(0) {}\n        explicit Node(int value) : val(value), l(0), r(0) {}\n\
    \        Node(int value, int left, int right) : val(value), l(left), r(right)\
    \ {}\n    };\n\n    int _n;\n    int _root;\n    using Pool = detail::PersistentBinaryNodePool<Node,\
    \ 0>;\n\n    std::shared_ptr<Pool> _pool;\n\n    explicit PersistentDsu(int n,\
    \ int root, std::shared_ptr<Pool> pool)\n        : _n(n), _root(root), _pool(std::move(pool))\
    \ {\n        _pool->retain(_root);\n    }\n\n    int new_node(const Node& node)\
    \ const {\n        return _pool->emplace(node);\n    }\n\n    int new_node(Node&&\
    \ node) const {\n        return _pool->emplace(std::move(node));\n    }\n\n  \
    \  int build(int l, int r) const {\n        if (l == r) return 0;\n        if\
    \ (r - l == 1) return new_node(Node(-1));\n        int m = (l + r) >> 1;\n   \
    \     int left = build(l, m);\n        int right = build(m, r);\n        return\
    \ new_node(Node(0, left, right));\n    }\n\n    int set_node(int t, int l, int\
    \ r, int p, int value) const {\n        if (r - l == 1) return new_node(Node(value));\n\
    \        int m = (l + r) >> 1;\n            int left = (*_pool)[t].l;\n      \
    \      int right = (*_pool)[t].r;\n        if (p < m) {\n            left = set_node(left,\
    \ l, m, p, value);\n        } else {\n            right = set_node(right, m, r,\
    \ p, value);\n        }\n        return new_node(Node(0, left, right));\n    }\n\
    \n    PersistentDsu make_version(int root) const {\n        PersistentDsu result(_n,\
    \ root, _pool);\n        _pool->discard_unreferenced();\n        return result;\n\
    \    }\n\n    int get_node(int t, int l, int r, int p) const {\n        while\
    \ (r - l > 1) {\n            int m = (l + r) >> 1;\n            if (p < m) {\n\
    \                t = (*_pool)[t].l;\n                r = m;\n            } else\
    \ {\n                t = (*_pool)[t].r;\n                l = m;\n            }\n\
    \        }\n        return (*_pool)[t].val;\n    }\n\n   public:\n    PersistentDsu()\
    \ : PersistentDsu(0) {}\n\n    explicit PersistentDsu(int n) : _n(n), _root(0),\
    \ _pool(std::make_shared<Pool>()) {\n        assert(0 <= n);\n        _pool->reserve(n\
    \ * 2 + 1);\n        if (_n > 0) _root = build(0, _n);\n        _pool->retain(_root);\n\
    \        _pool->discard_unreferenced();\n    }\n\n    PersistentDsu(const PersistentDsu&\
    \ other) : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentDsu(PersistentDsu&& other)\
    \ noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentDsu&\
    \ operator=(const PersistentDsu& other) {\n        if (this == &other) return\
    \ *this;\n        if (other._pool) other._pool->retain(other._root);\n       \
    \ if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root = other._root;\n\
    \        _pool = other._pool;\n        return *this;\n    }\n\n    PersistentDsu&\
    \ operator=(PersistentDsu&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) _pool->release(_root);\n        _n = other._n;\n\
    \        _root = other._root;\n        _pool = std::move(other._pool);\n     \
    \   other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\n\
    \    ~PersistentDsu() {\n        if (_pool) _pool->release(_root);\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    void release() {\n        if (_pool) _pool->release(_root);\n\
    \        _n = 0;\n        _root = 0;\n        _pool = std::make_shared<Pool>();\n\
    \    }\n\n    std::size_t node_count() const { return _pool ? _pool->size() :\
    \ 0; }\n\n    int leader(int a) const {\n        assert(0 <= a && a < _n);\n \
    \       int x = a;\n        int p = get(x);\n        while (p >= 0) {\n      \
    \      x = p;\n            p = get(x);\n        }\n        return x;\n    }\n\n\
    \    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n    \
    \    assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n    }\n\
    \n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n     \
    \   return -get(leader(a));\n    }\n\n    int size(int a) const {\n        return\
    \ group_size(a);\n    }\n\n    int get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return get_node(_root, 0, _n, p);\n    }\n\n    PersistentDsu\
    \ merge(int a, int b) const {\n        assert(0 <= a && a < _n);\n        assert(0\
    \ <= b && b < _n);\n        int x = leader(a), y = leader(b);\n        if (x ==\
    \ y) return *this;\n        int sx = -get(x), sy = -get(y);\n        if (sx <\
    \ sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n      \
    \  }\n        int root = set_node(_root, 0, _n, x, -(sx + sy));\n        root\
    \ = set_node(root, 0, _n, y, x);\n        return make_version(root);\n    }\n\n\
    \    std::vector<std::vector<int>> groups() const {\n        std::vector<int>\
    \ leader_buf(_n), group_size(_n);\n        for (int i = 0; i < _n; i++) {\n  \
    \          leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\n\n\n#line 6 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n#include <concepts>\n\
    #line 11 \"ds/dsu/persistent_potentialized_dsu.hpp\"\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 14 \"ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct PersistentPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n    struct Value {\n       \
    \ int parent_or_size;\n        T diff_to_parent;\n\n        Value() : parent_or_size(0),\
    \ diff_to_parent(Group::id()) {}\n        Value(int parent_or_size_, const T&\
    \ diff_to_parent_)\n            : parent_or_size(parent_or_size_), diff_to_parent(diff_to_parent_)\
    \ {}\n        Value(int parent_or_size_, T&& diff_to_parent_)\n            : parent_or_size(parent_or_size_),\
    \ diff_to_parent(std::move(diff_to_parent_)) {}\n    };\n\n   private:\n    struct\
    \ Node {\n        Value val;\n        int l, r;\n\n        Node() : val(), l(0),\
    \ r(0) {}\n        explicit Node(const Value& value) : val(value), l(0), r(0)\
    \ {}\n        explicit Node(Value&& value) : val(std::move(value)), l(0), r(0)\
    \ {}\n        Node(const Value& value, int left, int right) : val(value), l(left),\
    \ r(right) {}\n        Node(Value&& value, int left, int right) : val(std::move(value)),\
    \ l(left), r(right) {}\n    };\n\n    int _n;\n    int _root;\n    using Pool\
    \ = detail::PersistentBinaryNodePool<Node, 0>;\n\n    std::shared_ptr<Pool> _pool;\n\
    \n    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<Pool>\
    \ pool)\n        : _n(n), _root(root), _pool(std::move(pool)) {\n        _pool->retain(_root);\n\
    \    }\n\n    int new_node(const Node& node) const {\n        return _pool->emplace(node);\n\
    \    }\n\n    int new_node(Node&& node) const {\n        return _pool->emplace(std::move(node));\n\
    \    }\n\n    int build(int l, int r) const {\n        if (l == r) return 0;\n\
    \        if (r - l == 1) return new_node(Node(Value(-1, Group::id())));\n    \
    \    int m = (l + r) >> 1;\n        int left = build(l, m);\n        int right\
    \ = build(m, r);\n        return new_node(Node(Value(), left, right));\n    }\n\
    \n    int set_node(int t, int l, int r, int p, Value value) const {\n        if\
    \ (r - l == 1) return new_node(Node(std::move(value)));\n        int m = (l +\
    \ r) >> 1;\n        int left = (*_pool)[t].l;\n        int right = (*_pool)[t].r;\n\
    \        if (p < m) {\n            left = set_node(left, l, m, p, std::move(value));\n\
    \        } else {\n            right = set_node(right, m, r, p, std::move(value));\n\
    \        }\n        return new_node(Node(Value(), left, right));\n    }\n\n  \
    \  Value get_value(int t, int l, int r, int p) const {\n        while (r - l >\
    \ 1) {\n            int m = (l + r) >> 1;\n            if (p < m) {\n        \
    \        t = (*_pool)[t].l;\n                r = m;\n            } else {\n  \
    \              t = (*_pool)[t].r;\n                l = m;\n            }\n   \
    \     }\n        return (*_pool)[t].val;\n    }\n\n    std::pair<int, T> leader_and_potential(int\
    \ a) const {\n        T res = Group::id();\n        while (true) {\n         \
    \   Value cur = get(a);\n            if (cur.parent_or_size < 0) return {a, res};\n\
    \            res = Group::op(cur.diff_to_parent, res);\n            a = cur.parent_or_size;\n\
    \        }\n    }\n\n    PersistentPotentializedDsu make_version(int root) const\
    \ {\n        PersistentPotentializedDsu result(_n, root, _pool);\n        _pool->discard_unreferenced();\n\
    \        return result;\n    }\n\n   public:\n    PersistentPotentializedDsu()\
    \ : PersistentPotentializedDsu(0) {}\n\n    explicit PersistentPotentializedDsu(int\
    \ n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {\n        assert(0 <=\
    \ n);\n        _pool->reserve(n * 4 + 1);\n        if (_n > 0) _root = build(0,\
    \ _n);\n        _pool->retain(_root);\n        _pool->discard_unreferenced();\n\
    \    }\n\n    PersistentPotentializedDsu(const PersistentPotentializedDsu& other)\n\
    \        : _n(other._n), _root(other._root), _pool(other._pool) {\n        if\
    \ (_pool) _pool->retain(_root);\n    }\n\n    PersistentPotentializedDsu(PersistentPotentializedDsu&&\
    \ other) noexcept\n        : _n(other._n), _root(other._root), _pool(std::move(other._pool))\
    \ {\n        other._n = 0;\n        other._root = 0;\n    }\n\n    PersistentPotentializedDsu&\
    \ operator=(const PersistentPotentializedDsu& other) {\n        if (this == &other)\
    \ return *this;\n        if (other._pool) other._pool->retain(other._root);\n\
    \        if (_pool) _pool->release(_root);\n        _n = other._n;\n        _root\
    \ = other._root;\n        _pool = other._pool;\n        return *this;\n    }\n\
    \n    PersistentPotentializedDsu& operator=(PersistentPotentializedDsu&& other)\
    \ noexcept {\n        if (this == &other) return *this;\n        if (_pool) _pool->release(_root);\n\
    \        _n = other._n;\n        _root = other._root;\n        _pool = std::move(other._pool);\n\
    \        other._n = 0;\n        other._root = 0;\n        return *this;\n    }\n\
    \n    ~PersistentPotentializedDsu() {\n        if (_pool) _pool->release(_root);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void release() {\n        if\
    \ (_pool) _pool->release(_root);\n        _n = 0;\n        _root = 0;\n      \
    \  _pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count() const\
    \ { return _pool ? _pool->size() : 0; }\n\n    int leader(int a) const {\n   \
    \     assert(0 <= a && a < _n);\n        return leader_and_potential(a).first;\n\
    \    }\n\n    bool same(int a, int b) const {\n        assert(0 <= a && a < _n);\n\
    \        assert(0 <= b && b < _n);\n        return leader(a) == leader(b);\n \
    \   }\n\n    int group_size(int a) const {\n        assert(0 <= a && a < _n);\n\
    \        return -get(leader(a)).parent_or_size;\n    }\n\n    int size(int a)\
    \ const {\n        return group_size(a);\n    }\n\n    T potential(int a) const\
    \ {\n        assert(0 <= a && a < _n);\n        return leader_and_potential(a).second;\n\
    \    }\n\n    T diff(int a, int b) const {\n        assert(same(a, b));\n    \
    \    return Group::op(Group::inv(potential(a)), potential(b));\n    }\n\n    Value\
    \ get(int p) const {\n        assert(0 <= p && p < _n);\n        return get_value(_root,\
    \ 0, _n, p);\n    }\n\n    int parent_or_size(int p) const {\n        return get(p).parent_or_size;\n\
    \    }\n\n    std::pair<PersistentPotentializedDsu, bool> merge(int a, int b,\
    \ const T& w) const {\n        assert(0 <= a && a < _n);\n        assert(0 <=\
    \ b && b < _n);\n        auto [x, pa] = leader_and_potential(a);\n        auto\
    \ [y, pb] = leader_and_potential(b);\n        if (x == y) return {*this, Group::op(Group::inv(pa),\
    \ pb) == w};\n\n        int sx = -get(x).parent_or_size;\n        int sy = -get(y).parent_or_size;\n\
    \        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));\n        if\
    \ (sx < sy) {\n            std::swap(x, y);\n            std::swap(sx, sy);\n\
    \            y_from_x = Group::inv(y_from_x);\n        }\n        int root = set_node(_root,\
    \ 0, _n, x, Value(-(sx + sy), Group::id()));\n        root = set_node(root, 0,\
    \ _n, y, Value(x, std::move(y_from_x)));\n        return {make_version(root),\
    \ true};\n    }\n\n    std::vector<std::vector<int>> groups() const {\n      \
    \  std::vector<int> leader_buf(_n), group_size(_n);\n        for (int i = 0; i\
    \ < _n; i++) {\n            leader_buf[i] = leader(i);\n            group_size[leader_buf[i]]++;\n\
    \        }\n        std::vector<std::vector<int>> result(_n);\n        for (int\
    \ i = 0; i < _n; i++) {\n            result[i].reserve(group_size[i]);\n     \
    \   }\n        for (int i = 0; i < _n; i++) {\n            result[leader_buf[i]].push_back(i);\n\
    \        }\n        result.erase(std::remove_if(result.begin(), result.end(),\
    \ [&](const std::vector<int>& v) { return v.empty(); }),\n                   \
    \  result.end());\n        return result;\n    }\n};\n\n}  // namespace ds\n}\
    \  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\
    \n\n\n\n#line 5 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include <chrono>\n\
    #line 13 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\n\n#line 15 \"ds/dynamic_array/persistent_dynamic_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T>\nstruct PersistentDynamicArray\
    \ {\n   private:\n    struct Node {\n        T val;\n        int priority;\n \
    \       int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ int node_priority, int node_count, int left, int right, bool reversed)\n   \
    \         : val(std::move(value)),\n              priority(node_priority),\n \
    \             count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed) {}\n    };\n\n    struct BuildNode {\n        T val;\n\
    \        int priority;\n        int l, r;\n\n        BuildNode(T value, int node_priority)\
    \ : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}\n    };\n\n\
    \    int root;\n    std::uint32_t rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\
    \n    std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n   \
    \     return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    static std::uint32_t\
    \ next_state(std::uint32_t state) {\n        state ^= state << 13;\n        state\
    \ ^= state >> 17;\n        state ^= state << 5;\n        return state == 0 ? 1\
    \ : state;\n    }\n\n    static int next_priority(std::uint32_t& state) {\n  \
    \      state = next_state(state);\n        return int(state);\n    }\n\n    int\
    \ make_node(T val, int priority, bool rev, int l, int r) const {\n        int\
    \ count = 1 + subtree_size(l) + subtree_size(r);\n        return pool->emplace(std::move(val),\
    \ priority, count, l, r, rev);\n    }\n\n    int reversed_node(int t) const {\n\
    \        if (t == -1) return -1;\n        const Node& node = (*pool)[t];\n   \
    \     return make_node(node.val, node.priority, !node.rev, node.l, node.r);\n\
    \    }\n\n    int push(int t) const {\n        if (t == -1 || !(*pool)[t].rev)\
    \ return t;\n        Node node = (*pool)[t];\n        int l = reversed_node(node.r);\n\
    \        int r = reversed_node(node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, l, r);\n    }\n\n    int merge(int l, int r) const {\n\
    \        if (l == -1 || r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority\
    \ > (*pool)[r].priority) {\n            Node node = (*pool)[push(l)];\n      \
    \      int right = merge(node.r, r);\n            return make_node(std::move(node.val),\
    \ node.priority, false, node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n\
    \        int left = merge(l, node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int\
    \ t, int pos) const {\n        if (t == -1) return {-1, -1};\n        Node node\
    \ = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n      \
    \  if (pos <= left_count) {\n            auto [a, b] = split_node(node.l, pos);\n\
    \            return {a, make_node(std::move(node.val), node.priority, false, b,\
    \ node.r)};\n        }\n        auto [a, b] = split_node(node.r, pos - left_count\
    \ - 1);\n        return {make_node(std::move(node.val), node.priority, false,\
    \ node.l, a), b};\n    }\n\n    int set_node(int t, int pos, T val) const {\n\
    \        Node node = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n\
    \        if (pos < left_count) {\n            int l = set_node(node.l, pos, std::move(val));\n\
    \            return make_node(std::move(node.val), node.priority, false, l, node.r);\n\
    \        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
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
    \    explicit PersistentDynamicArray(int node, std::uint32_t state, std::shared_ptr<Pool>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {\n        pool->retain(root);\n    }\n\n    PersistentDynamicArray make_version(int\
    \ node, std::uint32_t state) const {\n        PersistentDynamicArray result(node,\
    \ state, pool);\n        pool->discard_unreferenced();\n        return result;\n\
    \    }\n\n   public:\n    PersistentDynamicArray()\n        : root(-1),\n    \
    \      rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicArray(int n) : PersistentDynamicArray(n,\
    \ T()) {}\n\n    PersistentDynamicArray(int n, const T& value) : PersistentDynamicArray()\
    \ {\n        assert(0 <= n);\n        std::vector<T> v(n, value);\n        root\
    \ = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicArray(const\
    \ std::vector<T>& v) : PersistentDynamicArray() {\n        root = build_from_vector(v,\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    explicit PersistentDynamicArray(std::vector<T>&& v) : PersistentDynamicArray()\
    \ {\n        root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicArray(std::initializer_list<T>\
    \ init) : PersistentDynamicArray(std::vector<T>(init)) {}\n\n    PersistentDynamicArray(const\
    \ PersistentDynamicArray& other)\n        : root(other.root), rng_state(other.rng_state),\
    \ pool(other.pool) {\n        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicArray(PersistentDynamicArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicArray& operator=(const\
    \ PersistentDynamicArray& other) {\n        if (this == &other) return *this;\n\
    \        if (other.pool) other.pool->retain(other.root);\n        if (pool) pool->release(root);\n\
    \        root = other.root;\n        rng_state = other.rng_state;\n        pool\
    \ = other.pool;\n        return *this;\n    }\n\n    PersistentDynamicArray& operator=(PersistentDynamicArray&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (pool)\
    \ pool->release(root);\n        root = other.root;\n        rng_state = other.rng_state;\n\
    \        pool = std::move(other.pool);\n        other.root = -1;\n        return\
    \ *this;\n    }\n\n    ~PersistentDynamicArray() {\n        if (pool) pool->release(root);\n\
    \    }\n\n    int size() const {\n        return subtree_size(root);\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void release()\
    \ {\n        if (pool) pool->release(root);\n        root = -1;\n        pool\
    \ = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count() const { return\
    \ pool ? pool->size() : 0; }\n\n    PersistentDynamicArray clear() const {\n \
    \       return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, T val) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(val),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::vector<T>&&\
    \ v) const {\n        assert(0 <= pos && pos <= size());\n        if (v.empty())\
    \ return *this;\n        std::uint32_t next = rng_state;\n        int mid = build_from_vector(std::move(v),\
    \ next);\n        auto [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicArray push_back(T val)\
    \ const {\n        return insert(size(), std::move(val));\n    }\n\n    PersistentDynamicArray\
    \ push_front(T val) const {\n        return insert(0, std::move(val));\n    }\n\
    \n    PersistentDynamicArray append(const std::vector<T>& v) const {\n       \
    \ return insert(size(), v);\n    }\n\n    PersistentDynamicArray append(std::vector<T>&&\
    \ v) const {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicArray\
    \ append(const PersistentDynamicArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicArray erase(int pos) const {\n      \
    \  assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root, pos);\n\
    \        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicArray erase(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n      \
    \  if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n   \
    \     auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicArray pop_back()\
    \ const {\n        assert(!empty());\n        return erase(size() - 1);\n    }\n\
    \n    PersistentDynamicArray pop_front() const {\n        assert(!empty());\n\
    \        return erase(0);\n    }\n\n    const T& at(int pos) const {\n       \
    \ assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root, pos)].val;\n\
    \    }\n\n    const T& operator[](int pos) const {\n        return at(pos);\n\
    \    }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ at(0);\n    }\n\n    const T& back() const {\n        assert(!empty());\n  \
    \      return at(size() - 1);\n    }\n\n    T get(int pos) const {\n        return\
    \ at(pos);\n    }\n\n    PersistentDynamicArray set(int pos, T val) const {\n\
    \        assert(0 <= pos && pos < size());\n        return make_version(set_node(root,\
    \ pos, std::move(val)), rng_state);\n    }\n\n    PersistentDynamicArray reverse(int\
    \ l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n      \
    \  if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n   \
    \     auto [mid, c] = split_node(b, r - l);\n        return make_version(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state);\n    }\n\n    PersistentDynamicArray reverse()\
    \ const {\n        return make_version(reversed_node(root), rng_state);\n    }\n\
    \n    PersistentDynamicArray rotate(int l, int m, int r) const {\n        assert(0\
    \ <= l && l <= m && m <= r && r <= size());\n        if (l == m || m == r) return\
    \ *this;\n        auto [a, b] = split_node(root, l);\n        auto [c, d] = split_node(b,\
    \ m - l);\n        auto [e, f] = split_node(d, r - m);\n        return make_version(merge(merge(a,\
    \ e), merge(c, f)), rng_state);\n    }\n\n    std::pair<PersistentDynamicArray,\
    \ PersistentDynamicArray> split(int pos) const {\n        assert(0 <= pos && pos\
    \ <= size());\n        auto [l, r] = split_node(root, pos);\n        PersistentDynamicArray\
    \ left(l, rng_state, pool);\n        PersistentDynamicArray right(r, rng_state,\
    \ pool);\n        pool->discard_unreferenced();\n        return {std::move(left),\
    \ std::move(right)};\n    }\n\n    PersistentDynamicArray split_off(int pos) const\
    \ {\n        assert(0 <= pos && pos <= size());\n        return make_version(split_node(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n\n\
    \n#line 13 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n#line\
    \ 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\n\
    \nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 16 \"ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct PersistentDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        F lazy;\n\
    \        int priority;\n        int count;\n        int l, r;\n        bool rev;\n\
    \        bool has_lazy;\n\n        Node(T value, T product, T reverse_product,\
    \ F lazy_value, int node_priority, int node_count, int left,\n             int\
    \ right, bool reversed, bool lazy_flag)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              lazy(std::move(lazy_value)),\n              priority(node_priority),\n\
    \              count(node_count),\n              l(left),\n              r(right),\n\
    \              rev(reversed),\n              has_lazy(lazy_flag) {}\n    };\n\n\
    \    struct BuildNode {\n        T val;\n        int priority;\n        int l,\
    \ r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n   \
    \ std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n       \
    \ return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int t) const\
    \ {\n        return t == -1 ? ActedMonoid::id() : (*pool)[t].prod;\n    }\n\n\
    \    T node_rprod(int t) const {\n        return t == -1 ? ActedMonoid::id() :\
    \ (*pool)[t].rprod;\n    }\n\n    static std::uint32_t next_state(std::uint32_t\
    \ state) {\n        state ^= state << 13;\n        state ^= state >> 17;\n   \
    \     state ^= state << 5;\n        return state == 0 ? 1 : state;\n    }\n\n\
    \    static int next_priority(std::uint32_t& state) {\n        state = next_state(state);\n\
    \        return int(state);\n    }\n\n    template <typename U>\n    static T\
    \ make_value(const U& value) {\n        if constexpr (requires(U x) { ActedMonoid::make(x);\
    \ }) {\n            return ActedMonoid::make(value);\n        } else {\n     \
    \       return static_cast<T>(value);\n        }\n    }\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ord) {\n        if constexpr (requires(F g,\
    \ T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n            return\
    \ ActedMonoid::mapping(f, value, ord);\n        } else {\n            return ActedMonoid::mapping(f,\
    \ value);\n        }\n    }\n\n    static F shift_operator(const F& f, long long\
    \ ord) {\n        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g,\
    \ i); }) {\n            return ActedMonoid::op_shift(f, ord);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    static F reverse_operator(const\
    \ F& f, long long size) {\n        if constexpr (requires(F g, long long n) {\
    \ ActedMonoid::op_reverse(g, n); }) {\n            return ActedMonoid::op_reverse(f,\
    \ size);\n        } else {\n            return f;\n        }\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, long long ord) const {\n        F shifted = shift_operator(inherited,\
    \ ord);\n        const Node& node = (*pool)[t];\n        if (!node.has_lazy) return\
    \ shifted;\n        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy,\
    \ ord));\n    }\n\n    int make_raw_node(T val, T prod, T rprod, F lazy, int priority,\
    \ int count, bool rev, bool has_lazy, int l,\n                      int r) const\
    \ {\n        return pool->emplace(std::move(val), std::move(prod), std::move(rprod),\
    \ std::move(lazy), priority, count,\n                             l, r, rev, has_lazy);\n\
    \    }\n\n    int make_node(T val, int priority, bool rev, int l, int r) const\
    \ {\n        T prod = ActedMonoid::op(ActedMonoid::op(node_prod(l), val), node_prod(r));\n\
    \        T rprod = ActedMonoid::op(ActedMonoid::op(node_rprod(r), val), node_rprod(l));\n\
    \        if (rev) std::swap(prod, rprod);\n        int count = 1 + subtree_size(l)\
    \ + subtree_size(r);\n        return make_raw_node(std::move(val), std::move(prod),\
    \ std::move(rprod), ActedMonoid::op_id(), priority,\n                        \
    \     count, rev, false, l, r);\n    }\n\n    int reversed_node(int t) const {\n\
    \        if (t == -1) return -1;\n        Node node = (*pool)[t];\n        F lazy\
    \ = node.has_lazy ? reverse_operator(node.lazy, node.count) : node.lazy;\n   \
    \     return make_raw_node(std::move(node.val), std::move(node.rprod), std::move(node.prod),\
    \ std::move(lazy),\n                             node.priority, node.count, !node.rev,\
    \ node.has_lazy, node.l, node.r);\n    }\n\n    int all_apply(int t, const F&\
    \ f) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        int left_count = node.rev ? subtree_size(node.r) : subtree_size(node.l);\n\
    \        return make_raw_node(mapping_at(f, node.val, left_count), mapping_at(f,\
    \ node.prod, 0),\n                             mapping_at(reverse_operator(f,\
    \ node.count), node.rprod, 0),\n                             ActedMonoid::op_comp(f,\
    \ node.lazy), node.priority, node.count, node.rev, true, node.l,\n           \
    \                  node.r);\n    }\n\n    int push(int t) const {\n        if\
    \ (t == -1) return -1;\n        const Node& stored = (*pool)[t];\n        if (!stored.rev\
    \ && !stored.has_lazy) return t;\n        Node node = stored;\n        int l =\
    \ node.l;\n        int r = node.r;\n        if (node.rev) {\n            std::swap(l,\
    \ r);\n            l = reversed_node(l);\n            r = reversed_node(r);\n\
    \        }\n        if (node.has_lazy) {\n            l = all_apply(l, node.lazy);\n\
    \            r = all_apply(r, shift_operator(node.lazy, subtree_size(l) + 1));\n\
    \        }\n        return make_node(std::move(node.val), node.priority, false,\
    \ l, r);\n    }\n\n    int merge(int l, int r) const {\n        if (l == -1 ||\
    \ r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority > (*pool)[r].priority)\
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
    \ node.priority, false, node.l, r);\n    }\n\n    T get_value(int t, int pos,\
    \ F inherited, bool reversed = false) const {\n        while (t != -1) {\n   \
    \         const Node& node = (*pool)[t];\n            bool cur_reversed = reversed\
    \ ^ node.rev;\n            int l = cur_reversed ? node.r : node.l;\n         \
    \   int r = cur_reversed ? node.l : node.r;\n            int left_count = subtree_size(l);\n\
    \            if (pos < left_count) {\n                inherited = compose_for_child(inherited,\
    \ t, 0);\n                t = l;\n                reversed = cur_reversed;\n \
    \           } else if (pos == left_count) {\n                return mapping_at(inherited,\
    \ node.val, left_count);\n            } else {\n                pos -= left_count\
    \ + 1;\n                inherited = compose_for_child(inherited, t, left_count\
    \ + 1);\n                t = r;\n                reversed = cur_reversed;\n  \
    \          }\n        }\n        return ActedMonoid::id();\n    }\n\n    T prod_dfs(int\
    \ t, int ql, int qr, int offset, const F& inherited, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return\
    \ ActedMonoid::id();\n        const Node& node = (*pool)[t];\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        if (ql <= offset && offset + node.count <= qr)\
    \ {\n            return mapping_at(inherited, reversed ? node.rprod : node.prod,\
    \ 0);\n        }\n        int l = cur_reversed ? node.r : node.l;\n        int\
    \ r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, compose_for_child(inherited, t, 0), cur_reversed);\n        if (ql\
    \ <= node_pos && node_pos < qr) res = ActedMonoid::op(res, mapping_at(inherited,\
    \ node.val, left_count));\n        return ActedMonoid::op(\n            res, prod_dfs(r,\
    \ ql, qr, node_pos + 1, compose_for_child(inherited, t, left_count + 1),\n   \
    \                       cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, const F& inherited, bool reversed = false) const {\n        if (t == -1)\
    \ return;\n        const Node& node = (*pool)[t];\n        bool cur_reversed =\
    \ reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n    \
    \    int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        dump_dfs(l, res, compose_for_child(inherited, t, 0), cur_reversed);\n\
    \        res.push_back(mapping_at(inherited, node.val, left_count));\n       \
    \ dump_dfs(r, res, compose_for_child(inherited, t, left_count + 1), cur_reversed);\n\
    \    }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, const F& inherited,\n                        bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, compose_for_child(inherited, t, 0), cur_reversed);\n        if\
    \ (ql <= node_pos && node_pos < qr) res.push_back(mapping_at(inherited, node.val,\
    \ left_count));\n        dump_range_dfs(r, ql, qr, node_pos + 1, res, compose_for_child(inherited,\
    \ t, left_count + 1),\n                       cur_reversed);\n    }\n\n    int\
    \ build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n        if (t\
    \ == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n  \
    \      int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
    \ nodes[t].priority, false, l, r);\n    }\n\n    int build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return -1;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
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
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const\
    \ {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicLazyMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_raw_node(node.val, node.prod, node.rprod, node.lazy, node.priority,\
    \ node.count, node.rev,\n                             node.has_lazy, l, r);\n\
    \    }\n\n    explicit PersistentDynamicLazyMonoidArray(int node, std::uint32_t\
    \ state,\n                                              std::shared_ptr<Pool>\
    \ node_pool)\n        : root(node), rng_state(state), pool(std::move(node_pool))\
    \ {\n        pool->retain(root);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ make_version(int node, std::uint32_t state) const {\n        PersistentDynamicLazyMonoidArray\
    \ result(node, state, pool);\n        pool->discard_unreferenced();\n        return\
    \ result;\n    }\n\n   public:\n    PersistentDynamicLazyMonoidArray()\n     \
    \   : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(int n)\n      \
    \  : PersistentDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n    PersistentDynamicLazyMonoidArray(int\
    \ n, const T& value) : PersistentDynamicLazyMonoidArray() {\n        assert(0\
    \ <= n);\n        pool->reserve(n);\n        std::vector<T> v(n, value);\n   \
    \     root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicLazyMonoidArray(const\
    \ std::vector<T>& v)\n        : PersistentDynamicLazyMonoidArray() {\n       \
    \ pool->reserve(v.size());\n        root = build_from_vector(v, rng_state);\n\
    \        pool->retain(root);\n        pool->discard_unreferenced();\n    }\n\n\
    \    explicit PersistentDynamicLazyMonoidArray(std::vector<T>&& v) : PersistentDynamicLazyMonoidArray()\
    \ {\n        pool->reserve(v.size());\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\n\
    \                (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U,\
    \ T>)\n    explicit PersistentDynamicLazyMonoidArray(const std::vector<U>& v)\n\
    \        : PersistentDynamicLazyMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_values(v, rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicLazyMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicLazyMonoidArray(std::vector<T>(init)) {}\n\
    \n    PersistentDynamicLazyMonoidArray(const PersistentDynamicLazyMonoidArray&\
    \ other)\n        : root(other.root), rng_state(other.rng_state), pool(other.pool)\
    \ {\n        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicLazyMonoidArray(PersistentDynamicLazyMonoidArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicLazyMonoidArray&\
    \ operator=(const PersistentDynamicLazyMonoidArray& other) {\n        if (this\
    \ == &other) return *this;\n        if (other.pool) other.pool->retain(other.root);\n\
    \        if (pool) pool->release(root);\n        root = other.root;\n        rng_state\
    \ = other.rng_state;\n        pool = other.pool;\n        return *this;\n    }\n\
    \n    PersistentDynamicLazyMonoidArray& operator=(PersistentDynamicLazyMonoidArray&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (pool)\
    \ pool->release(root);\n        root = other.root;\n        rng_state = other.rng_state;\n\
    \        pool = std::move(other.pool);\n        other.root = -1;\n        return\
    \ *this;\n    }\n\n    ~PersistentDynamicLazyMonoidArray() {\n        if (pool)\
    \ pool->release(root);\n    }\n\n    int size() const {\n        return subtree_size(root);\n\
    \    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n   \
    \ void release() {\n        if (pool) pool->release(root);\n        root = -1;\n\
    \        pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count()\
    \ const { return pool ? pool->size() : 0; }\n\n    PersistentDynamicLazyMonoidArray\
    \ clear() const {\n        return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ insert(int pos, T value) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(value),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return make_version(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicLazyMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray insert(int pos, const PersistentDynamicLazyMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const std::vector<T>& v) const {\n        return insert(size(), v);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray append(std::vector<T>&& v) const\
    \ {\n        return insert(size(), std::move(v));\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ append(const PersistentDynamicLazyMonoidArray& other) const {\n        return\
    \ insert(size(), other);\n    }\n\n    PersistentDynamicLazyMonoidArray erase(int\
    \ pos) const {\n        assert(0 <= pos && pos < size());\n        auto [a, b]\
    \ = split_node(root, pos);\n        auto [mid, c] = split_node(b, 1);\n      \
    \  (void)mid;\n        return make_version(merge(a, c), rng_state);\n    }\n\n\
    \    PersistentDynamicLazyMonoidArray erase(int l, int r) const {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return *this;\n       \
    \ auto [a, b] = split_node(root, l);\n        auto [mid, c] = split_node(b, r\
    \ - l);\n        (void)mid;\n        return make_version(merge(a, c), rng_state);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray pop_back() const {\n        assert(!empty());\n\
    \        return erase(size() - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ pop_front() const {\n        assert(!empty());\n        return erase(0);\n \
    \   }\n\n    T get(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        return get_value(root, pos, ActedMonoid::op_id());\n    }\n\n    T operator[](int\
    \ pos) const {\n        return get(pos);\n    }\n\n    T front() const {\n   \
    \     assert(!empty());\n        return get(0);\n    }\n\n    T back() const {\n\
    \        assert(!empty());\n        return get(size() - 1);\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ set(int pos, T value) const {\n        assert(0 <= pos && pos < size());\n \
    \       return make_version(set_node(root, pos, std::move(value)), rng_state);\n\
    \    }\n\n    PersistentDynamicLazyMonoidArray reverse(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ *this;\n        auto [a, b] = split_node(root, l);\n        auto [mid, c] =\
    \ split_node(b, r - l);\n        return make_version(merge(merge(a, reversed_node(mid)),\
    \ c), rng_state);\n    }\n\n    PersistentDynamicLazyMonoidArray reverse() const\
    \ {\n        return make_version(reversed_node(root), rng_state);\n    }\n\n \
    \   PersistentDynamicLazyMonoidArray rotate(int l, int m, int r) const {\n   \
    \     assert(0 <= l && l <= m && m <= r && r <= size());\n        if (l == m ||\
    \ m == r) return *this;\n        auto [a, b] = split_node(root, l);\n        auto\
    \ [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d, r - m);\n\
    \        return make_version(merge(merge(a, e), merge(c, f)), rng_state);\n  \
    \  }\n\n    PersistentDynamicLazyMonoidArray apply(int pos, const F& f) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return apply(pos, pos\
    \ + 1, f);\n    }\n\n    PersistentDynamicLazyMonoidArray apply(int l, int r,\
    \ const F& f) const {\n        assert(0 <= l && l <= r && r <= size());\n    \
    \    if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n \
    \       auto [mid, c] = split_node(b, r - l);\n        return make_version(merge(merge(a,\
    \ all_apply(mid, f)), c), rng_state);\n    }\n\n    T prod(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        if (l == r) return\
    \ ActedMonoid::id();\n        return prod_dfs(root, l, r, 0, ActedMonoid::op_id());\n\
    \    }\n\n    T all_prod() const {\n        return root == -1 ? ActedMonoid::id()\
    \ : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicLazyMonoidArray,\
    \ PersistentDynamicLazyMonoidArray> split(int pos) const {\n        assert(0 <=\
    \ pos && pos <= size());\n        auto [l, r] = split_node(root, pos);\n     \
    \   PersistentDynamicLazyMonoidArray left(l, rng_state, pool);\n        PersistentDynamicLazyMonoidArray\
    \ right(r, rng_state, pool);\n        pool->discard_unreferenced();\n        return\
    \ {std::move(left), std::move(right)};\n    }\n\n    PersistentDynamicLazyMonoidArray\
    \ split_off(int pos) const {\n        assert(0 <= pos && pos <= size());\n   \
    \     return make_version(split_node(root, pos).second, rng_state);\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res, ActedMonoid::op_id());\n \
    \       return res;\n    }\n\n    std::vector<T> to_vector(int l, int r) const\
    \ {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res,\
    \ ActedMonoid::op_id());\n        return res;\n    }\n};\n\n}  // namespace ds\n\
    }  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\
    \n\n\n\n#line 13 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\n\
    #line 16 \"ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct\
    \ PersistentDynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        T val, prod, rprod;\n        int priority;\n\
    \        int count;\n        int l, r;\n        bool rev;\n\n        Node(T value,\
    \ T product, T reverse_product, int node_priority, int node_count, int left, int\
    \ right,\n             bool reversed)\n            : val(std::move(value)),\n\
    \              prod(std::move(product)),\n              rprod(std::move(reverse_product)),\n\
    \              priority(node_priority),\n              count(node_count),\n  \
    \            l(left),\n              r(right),\n              rev(reversed) {}\n\
    \    };\n\n    struct BuildNode {\n        T val;\n        int priority;\n   \
    \     int l, r;\n\n        BuildNode(T value, int node_priority) : val(std::move(value)),\
    \ priority(node_priority), l(-1), r(-1) {}\n    };\n\n    int root;\n    std::uint32_t\
    \ rng_state;\n    using Pool = detail::PersistentBinaryNodePool<Node>;\n\n   \
    \ std::shared_ptr<Pool> pool;\n\n    int subtree_size(int t) const {\n       \
    \ return t == -1 ? 0 : (*pool)[t].count;\n    }\n\n    T node_prod(int t) const\
    \ {\n        return t == -1 ? Monoid::id() : (*pool)[t].prod;\n    }\n\n    T\
    \ node_rprod(int t) const {\n        return t == -1 ? Monoid::id() : (*pool)[t].rprod;\n\
    \    }\n\n    static std::uint32_t next_state(std::uint32_t state) {\n       \
    \ state ^= state << 13;\n        state ^= state >> 17;\n        state ^= state\
    \ << 5;\n        return state == 0 ? 1 : state;\n    }\n\n    static int next_priority(std::uint32_t&\
    \ state) {\n        state = next_state(state);\n        return int(state);\n \
    \   }\n\n    template <typename U>\n    static T make_value(const U& value) {\n\
    \        if constexpr (requires(U x) { Monoid::make(x); }) {\n            return\
    \ Monoid::make(value);\n        } else {\n            return static_cast<T>(value);\n\
    \        }\n    }\n\n    int make_node(T val, int priority, bool rev, int l, int\
    \ r) const {\n        T prod = Monoid::op(Monoid::op(node_prod(l), val), node_prod(r));\n\
    \        T rprod = Monoid::op(Monoid::op(node_rprod(r), val), node_rprod(l));\n\
    \        if (rev) std::swap(prod, rprod);\n        int count = 1 + subtree_size(l)\
    \ + subtree_size(r);\n        return pool->emplace(std::move(val), std::move(prod),\
    \ std::move(rprod), priority, count, l, r, rev);\n    }\n\n    int reversed_node(int\
    \ t) const {\n        if (t == -1) return -1;\n        Node node = (*pool)[t];\n\
    \        return make_node(std::move(node.val), node.priority, !node.rev, node.l,\
    \ node.r);\n    }\n\n    int push(int t) const {\n        if (t == -1 || !(*pool)[t].rev)\
    \ return t;\n        Node node = (*pool)[t];\n        int l = reversed_node(node.r);\n\
    \        int r = reversed_node(node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, l, r);\n    }\n\n    int merge(int l, int r) const {\n\
    \        if (l == -1 || r == -1) return l == -1 ? r : l;\n        if ((*pool)[l].priority\
    \ > (*pool)[r].priority) {\n            Node node = (*pool)[push(l)];\n      \
    \      int right = merge(node.r, r);\n            return make_node(std::move(node.val),\
    \ node.priority, false, node.l, right);\n        }\n        Node node = (*pool)[push(r)];\n\
    \        int left = merge(l, node.l);\n        return make_node(std::move(node.val),\
    \ node.priority, false, left, node.r);\n    }\n\n    std::pair<int, int> split_node(int\
    \ t, int pos) const {\n        if (t == -1) return {-1, -1};\n        Node node\
    \ = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n      \
    \  if (pos <= left_count) {\n            auto [a, b] = split_node(node.l, pos);\n\
    \            return {a, make_node(std::move(node.val), node.priority, false, b,\
    \ node.r)};\n        }\n        auto [a, b] = split_node(node.r, pos - left_count\
    \ - 1);\n        return {make_node(std::move(node.val), node.priority, false,\
    \ node.l, a), b};\n    }\n\n    int set_node(int t, int pos, T val) const {\n\
    \        Node node = (*pool)[push(t)];\n        int left_count = subtree_size(node.l);\n\
    \        if (pos < left_count) {\n            int l = set_node(node.l, pos, std::move(val));\n\
    \            return make_node(std::move(node.val), node.priority, false, l, node.r);\n\
    \        }\n        if (pos == left_count) {\n            return make_node(std::move(val),\
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
    \         }\n        }\n        return -1;\n    }\n\n    T prod_dfs(int t, int\
    \ ql, int qr, int offset, bool reversed = false) const {\n        if (t == -1\
    \ || qr <= offset || offset + (*pool)[t].count <= ql) return Monoid::id();\n \
    \       const Node& node = (*pool)[t];\n        if (ql <= offset && offset + node.count\
    \ <= qr) return reversed ? node.rprod : node.prod;\n        bool cur_reversed\
    \ = reversed ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n  \
    \      int r = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        T res = prod_dfs(l, ql,\
    \ qr, offset, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res\
    \ = Monoid::op(res, node.val);\n        return Monoid::op(res, prod_dfs(r, ql,\
    \ qr, node_pos + 1, cur_reversed));\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (t == -1) return;\n        const\
    \ Node& node = (*pool)[t];\n        bool cur_reversed = reversed ^ node.rev;\n\
    \        int l = cur_reversed ? node.r : node.l;\n        int r = cur_reversed\
    \ ? node.l : node.r;\n        dump_dfs(l, res, cur_reversed);\n        res.push_back(node.val);\n\
    \        dump_dfs(r, res, cur_reversed);\n    }\n\n    void dump_range_dfs(int\
    \ t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const\
    \ {\n        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;\n\
    \        const Node& node = (*pool)[t];\n        bool cur_reversed = reversed\
    \ ^ node.rev;\n        int l = cur_reversed ? node.r : node.l;\n        int r\
    \ = cur_reversed ? node.l : node.r;\n        int left_count = subtree_size(l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(l, ql, qr,\
    \ offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr) res.push_back(node.val);\n\
    \        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n\
    \    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const {\n    \
    \    if (t == -1) return -1;\n        int l = build_from_nodes(nodes, nodes[t].l);\n\
    \        int r = build_from_nodes(nodes, nodes[t].r);\n        return make_node(std::move(nodes[t].val),\
    \ nodes[t].priority, false, l, r);\n    }\n\n    int build_cartesian(std::vector<BuildNode>&\
    \ nodes) const {\n        if (nodes.empty()) return -1;\n        std::vector<int>\
    \ stack;\n        stack.reserve(nodes.size());\n        for (int i = 0; i < int(nodes.size());\
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
    \        return build_cartesian(nodes);\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const\
    \ {\n        std::vector<BuildNode> nodes;\n        nodes.reserve(v.size());\n\
    \        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));\n\
    \        return build_cartesian(nodes);\n    }\n\n    int import_node(const PersistentDynamicMonoidArray&\
    \ other, int t) const {\n        if (t == -1) return -1;\n        if (pool ==\
    \ other.pool) return t;\n        const Node& node = (*other.pool)[t];\n      \
    \  int l = import_node(other, node.l);\n        int r = import_node(other, node.r);\n\
    \        return make_node(node.val, node.priority, node.rev, l, r);\n    }\n\n\
    \    explicit PersistentDynamicMonoidArray(int node, std::uint32_t state,\n  \
    \                                        std::shared_ptr<Pool> node_pool)\n  \
    \      : root(node), rng_state(state), pool(std::move(node_pool)) {\n        pool->retain(root);\n\
    \    }\n\n    PersistentDynamicMonoidArray make_version(int node, std::uint32_t\
    \ state) const {\n        PersistentDynamicMonoidArray result(node, state, pool);\n\
    \        pool->discard_unreferenced();\n        return result;\n    }\n\n   public:\n\
    \    PersistentDynamicMonoidArray()\n        : root(-1),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          pool(std::make_shared<Pool>()) {\n        if (rng_state == 0) rng_state\
    \ = 1;\n    }\n\n    explicit PersistentDynamicMonoidArray(int n) : PersistentDynamicMonoidArray(n,\
    \ Monoid::id()) {}\n\n    PersistentDynamicMonoidArray(int n, const T& value)\
    \ : PersistentDynamicMonoidArray() {\n        assert(0 <= n);\n        pool->reserve(n);\n\
    \        std::vector<T> v(n, value);\n        root = build_from_vector(std::move(v),\
    \ rng_state);\n        pool->retain(root);\n        pool->discard_unreferenced();\n\
    \    }\n\n    explicit PersistentDynamicMonoidArray(const std::vector<T>& v) :\
    \ PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n       \
    \ root = build_from_vector(v, rng_state);\n        pool->retain(root);\n     \
    \   pool->discard_unreferenced();\n    }\n\n    explicit PersistentDynamicMonoidArray(std::vector<T>&&\
    \ v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n  \
    \      root = build_from_vector(std::move(v), rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    template <typename U>\n \
    \       requires(!std::same_as<U, T>) && (requires(U x) { Monoid::make(x); } ||\
    \ std::convertible_to<U, T>)\n    explicit PersistentDynamicMonoidArray(const\
    \ std::vector<U>& v) : PersistentDynamicMonoidArray() {\n        pool->reserve(v.size());\n\
    \        root = build_from_values(v, rng_state);\n        pool->retain(root);\n\
    \        pool->discard_unreferenced();\n    }\n\n    PersistentDynamicMonoidArray(std::initializer_list<T>\
    \ init)\n        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}\n\n \
    \   PersistentDynamicMonoidArray(const PersistentDynamicMonoidArray& other)\n\
    \        : root(other.root), rng_state(other.rng_state), pool(other.pool) {\n\
    \        if (pool) pool->retain(root);\n    }\n\n    PersistentDynamicMonoidArray(PersistentDynamicMonoidArray&&\
    \ other) noexcept\n        : root(other.root), rng_state(other.rng_state), pool(std::move(other.pool))\
    \ {\n        other.root = -1;\n    }\n\n    PersistentDynamicMonoidArray& operator=(const\
    \ PersistentDynamicMonoidArray& other) {\n        if (this == &other) return *this;\n\
    \        if (other.pool) other.pool->retain(other.root);\n        if (pool) pool->release(root);\n\
    \        root = other.root;\n        rng_state = other.rng_state;\n        pool\
    \ = other.pool;\n        return *this;\n    }\n\n    PersistentDynamicMonoidArray&\
    \ operator=(PersistentDynamicMonoidArray&& other) noexcept {\n        if (this\
    \ == &other) return *this;\n        if (pool) pool->release(root);\n        root\
    \ = other.root;\n        rng_state = other.rng_state;\n        pool = std::move(other.pool);\n\
    \        other.root = -1;\n        return *this;\n    }\n\n    ~PersistentDynamicMonoidArray()\
    \ {\n        if (pool) pool->release(root);\n    }\n\n    int size() const {\n\
    \        return subtree_size(root);\n    }\n\n    bool empty() const {\n     \
    \   return size() == 0;\n    }\n\n    void release() {\n        if (pool) pool->release(root);\n\
    \        root = -1;\n        pool = std::make_shared<Pool>();\n    }\n\n    std::size_t\
    \ node_count() const { return pool ? pool->size() : 0; }\n\n    PersistentDynamicMonoidArray\
    \ clear() const {\n        return make_version(-1, rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ insert(int pos, T value) const {\n        assert(0 <= pos && pos <= size());\n\
    \        std::uint32_t next = next_state(rng_state);\n        int node = make_node(std::move(value),\
    \ int(next), false, -1, -1);\n        auto [l, r] = split_node(root, pos);\n \
    \       return make_version(merge(merge(l, node), r), next);\n    }\n\n    PersistentDynamicMonoidArray\
    \ insert(int pos, const std::vector<T>& v) const {\n        assert(0 <= pos &&\
    \ pos <= size());\n        if (v.empty()) return *this;\n        std::uint32_t\
    \ next = rng_state;\n        int mid = build_from_vector(v, next);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos,\
    \ std::vector<T>&& v) const {\n        assert(0 <= pos && pos <= size());\n  \
    \      if (v.empty()) return *this;\n        std::uint32_t next = rng_state;\n\
    \        int mid = build_from_vector(std::move(v), next);\n        auto [l, r]\
    \ = split_node(root, pos);\n        return make_version(merge(merge(l, mid), r),\
    \ next);\n    }\n\n    PersistentDynamicMonoidArray insert(int pos, std::initializer_list<T>\
    \ init) const {\n        return insert(pos, std::vector<T>(init));\n    }\n\n\
    \    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray&\
    \ other) const {\n        assert(0 <= pos && pos <= size());\n        if (other.empty())\
    \ return *this;\n        int mid = import_node(other, other.root);\n        auto\
    \ [l, r] = split_node(root, pos);\n        return make_version(merge(merge(l,\
    \ mid), r), rng_state);\n    }\n\n    PersistentDynamicMonoidArray push_back(T\
    \ value) const {\n        return insert(size(), std::move(value));\n    }\n\n\
    \    PersistentDynamicMonoidArray push_front(T value) const {\n        return\
    \ insert(0, std::move(value));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ std::vector<T>& v) const {\n        return insert(size(), v);\n    }\n\n   \
    \ PersistentDynamicMonoidArray append(std::vector<T>&& v) const {\n        return\
    \ insert(size(), std::move(v));\n    }\n\n    PersistentDynamicMonoidArray append(const\
    \ PersistentDynamicMonoidArray& other) const {\n        return insert(size(),\
    \ other);\n    }\n\n    PersistentDynamicMonoidArray erase(int pos) const {\n\
    \        assert(0 <= pos && pos < size());\n        auto [a, b] = split_node(root,\
    \ pos);\n        auto [mid, c] = split_node(b, 1);\n        (void)mid;\n     \
    \   return make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ erase(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        (void)mid;\n        return\
    \ make_version(merge(a, c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ pop_back() const {\n        assert(!empty());\n        return erase(size() -\
    \ 1);\n    }\n\n    PersistentDynamicMonoidArray pop_front() const {\n       \
    \ assert(!empty());\n        return erase(0);\n    }\n\n    T get(int pos) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return (*pool)[find_node(root,\
    \ pos)].val;\n    }\n\n    T operator[](int pos) const {\n        return get(pos);\n\
    \    }\n\n    T front() const {\n        assert(!empty());\n        return get(0);\n\
    \    }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    PersistentDynamicMonoidArray set(int pos, T value) const\
    \ {\n        assert(0 <= pos && pos < size());\n        return make_version(set_node(root,\
    \ pos, std::move(value)), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse(int l, int r) const {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return *this;\n        auto [a, b] = split_node(root, l);\n\
    \        auto [mid, c] = split_node(b, r - l);\n        return make_version(merge(merge(a,\
    \ reversed_node(mid)), c), rng_state);\n    }\n\n    PersistentDynamicMonoidArray\
    \ reverse() const {\n        return make_version(reversed_node(root), rng_state);\n\
    \    }\n\n    PersistentDynamicMonoidArray rotate(int l, int m, int r) const {\n\
    \        assert(0 <= l && l <= m && m <= r && r <= size());\n        if (l ==\
    \ m || m == r) return *this;\n        auto [a, b] = split_node(root, l);\n   \
    \     auto [c, d] = split_node(b, m - l);\n        auto [e, f] = split_node(d,\
    \ r - m);\n        return make_version(merge(merge(a, e), merge(c, f)), rng_state);\n\
    \    }\n\n    T prod(int l, int r) const {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return Monoid::id();\n        return prod_dfs(root,\
    \ l, r, 0);\n    }\n\n    T all_prod() const {\n        return root == -1 ? Monoid::id()\
    \ : (*pool)[root].prod;\n    }\n\n    std::pair<PersistentDynamicMonoidArray,\
    \ PersistentDynamicMonoidArray> split(int pos) const {\n        assert(0 <= pos\
    \ && pos <= size());\n        auto [l, r] = split_node(root, pos);\n        PersistentDynamicMonoidArray\
    \ left(l, rng_state, pool);\n        PersistentDynamicMonoidArray right(r, rng_state,\
    \ pool);\n        pool->discard_unreferenced();\n        return {std::move(left),\
    \ std::move(right)};\n    }\n\n    PersistentDynamicMonoidArray split_off(int\
    \ pos) const {\n        assert(0 <= pos && pos <= size());\n        return make_version(split_node(root,\
    \ pos).second, rng_state);\n    }\n\n    std::vector<T> to_vector() const {\n\
    \        std::vector<T> res;\n        res.reserve(size());\n        dump_dfs(root,\
    \ res);\n        return res;\n    }\n\n    std::vector<T> to_vector(int l, int\
    \ r) const {\n        assert(0 <= l && l <= r && r <= size());\n        std::vector<T>\
    \ res;\n        res.reserve(r - l);\n        dump_range_dfs(root, l, r, 0, res);\n\
    \        return res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/queue/persistent_queue.hpp\"\n\n\n\n#line 11 \"ds/queue/persistent_queue.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Purely persistent FIFO queue with\
    \ worst-case O(1) operations.\ntemplate <class T>\nstruct PersistentQueue {\n\
    \   private:\n    struct Link {\n        int value_index;\n        int next;\n\
    \n        Link(int index, int next_link) : value_index(index), next(next_link)\
    \ {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<T>> values;\n\
    \        std::deque<std::optional<Link>> links;\n        std::vector<int> value_references,\
    \ link_references;\n        std::vector<int> next_free_value, next_free_link;\n\
    \        std::vector<int> unowned_values, unowned_links;\n        int first_free_value\
    \ = -1;\n        int first_free_link = -1;\n        std::size_t live_values =\
    \ 0;\n        std::size_t live_links = 0;\n\n        void retain_value(int value)\
    \ {\n            if (value != -1) ++value_references[value];\n        }\n\n  \
    \      void release_value(int value) {\n            if (value == -1) return;\n\
    \            assert(values[value].has_value() && value_references[value] > 0);\n\
    \            if (--value_references[value] != 0) return;\n            values[value].reset();\n\
    \            next_free_value[value] = first_free_value;\n            first_free_value\
    \ = value;\n            --live_values;\n        }\n\n        void retain_link(int\
    \ link) {\n            if (link != -1) ++link_references[link];\n        }\n\n\
    \        void release_zero_link(int link) {\n            while (link != -1) {\n\
    \                assert(links[link].has_value() && link_references[link] == 0);\n\
    \                int value = links[link]->value_index;\n                int next\
    \ = links[link]->next;\n                links[link].reset();\n               \
    \ next_free_link[link] = first_free_link;\n                first_free_link = link;\n\
    \                --live_links;\n                release_value(value);\n      \
    \          if (next == -1 || --link_references[next] != 0) return;\n         \
    \       link = next;\n            }\n        }\n\n        void release_link(int\
    \ link) {\n            if (link == -1) return;\n            assert(links[link].has_value()\
    \ && link_references[link] > 0);\n            if (--link_references[link] == 0)\
    \ release_zero_link(link);\n        }\n\n        int store_value(T value) {\n\
    \            int result;\n            if (first_free_value == -1) {\n        \
    \        result = int(values.size());\n                values.emplace_back(std::in_place,\
    \ std::move(value));\n                value_references.push_back(0);\n       \
    \         next_free_value.push_back(-1);\n            } else {\n             \
    \   result = first_free_value;\n                first_free_value = next_free_value[result];\n\
    \                values[result].emplace(std::move(value));\n                value_references[result]\
    \ = 0;\n            }\n            unowned_values.push_back(result);\n       \
    \     ++live_values;\n            return result;\n        }\n\n        int make_link(int\
    \ value, int next) {\n            int result;\n            if (first_free_link\
    \ == -1) {\n                result = int(links.size());\n                links.emplace_back(std::in_place,\
    \ value, next);\n                link_references.push_back(0);\n             \
    \   next_free_link.push_back(-1);\n            } else {\n                result\
    \ = first_free_link;\n                first_free_link = next_free_link[result];\n\
    \                links[result].emplace(value, next);\n                link_references[result]\
    \ = 0;\n            }\n            retain_value(value);\n            retain_link(next);\n\
    \            unowned_links.push_back(result);\n            ++live_links;\n   \
    \         return result;\n        }\n\n        void discard_unreferenced() {\n\
    \            while (!unowned_links.empty()) {\n                int link = unowned_links.back();\n\
    \                unowned_links.pop_back();\n                if (links[link].has_value()\
    \ && link_references[link] == 0) release_zero_link(link);\n            }\n   \
    \         while (!unowned_values.empty()) {\n                int value = unowned_values.back();\n\
    \                unowned_values.pop_back();\n                if (values[value].has_value()\
    \ && value_references[value] == 0) {\n                    values[value].reset();\n\
    \                    next_free_value[value] = first_free_value;\n            \
    \        first_free_value = value;\n                    --live_values;\n     \
    \           }\n            }\n        }\n\n        std::size_t size() const {\
    \ return live_values + live_links; }\n    };\n\n    enum class RotationPhase {\n\
    \        idle,\n        reversing,\n        appending,\n        done,\n    };\n\
    \n    struct RotationState {\n        RotationPhase phase = RotationPhase::idle;\n\
    \        int valid_count = 0;\n        int remaining_front = -1;\n        int\
    \ reversed_front = -1;\n        int remaining_rear = -1;\n        int reversed_rear\
    \ = -1;\n    };\n\n    int _front_size;\n    int _front;\n    RotationState _rotation;\n\
    \    int _rear_size;\n    int _rear;\n    int _back_value;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentQueue(\n        int front_size,\n        int front,\n\
    \        RotationState rotation,\n        int rear_size,\n        int rear,\n\
    \        int back_value,\n        std::shared_ptr<Pool> pool\n    )\n        :\
    \ _front_size(front_size),\n          _front(front),\n          _rotation(rotation),\n\
    \          _rear_size(rear_size),\n          _rear(rear),\n          _back_value(back_value),\n\
    \          _pool(std::move(pool)) {\n        retain_state();\n        _pool->discard_unreferenced();\n\
    \    }\n\n    void retain_state() const {\n        _pool->retain_link(_front);\n\
    \        _pool->retain_link(_rotation.remaining_front);\n        _pool->retain_link(_rotation.reversed_front);\n\
    \        _pool->retain_link(_rotation.remaining_rear);\n        _pool->retain_link(_rotation.reversed_rear);\n\
    \        _pool->retain_link(_rear);\n        _pool->retain_value(_back_value);\n\
    \    }\n\n    void release_state() const {\n        _pool->release_link(_front);\n\
    \        _pool->release_link(_rotation.remaining_front);\n        _pool->release_link(_rotation.reversed_front);\n\
    \        _pool->release_link(_rotation.remaining_rear);\n        _pool->release_link(_rotation.reversed_rear);\n\
    \        _pool->release_link(_rear);\n        _pool->release_value(_back_value);\n\
    \    }\n\n    int next_link(int link) const {\n        assert(link != -1);\n \
    \       return (*_pool->links[link]).next;\n    }\n\n    int link_value(int link)\
    \ const {\n        assert(link != -1);\n        return (*_pool->links[link]).value_index;\n\
    \    }\n\n    int make_link(int value_index, int next) const {\n        return\
    \ _pool->make_link(value_index, next);\n    }\n\n    int store_value(T value)\
    \ const {\n        return _pool->store_value(std::move(value));\n    }\n\n   \
    \ RotationState execute(RotationState state) const {\n        if (state.phase\
    \ == RotationPhase::reversing) {\n            assert(state.remaining_rear != -1);\n\
    \            if (state.remaining_front != -1) {\n                state.reversed_front\
    \ = make_link(\n                    link_value(state.remaining_front),\n     \
    \               state.reversed_front\n                );\n                state.remaining_front\
    \ = next_link(state.remaining_front);\n                state.reversed_rear = make_link(\n\
    \                    link_value(state.remaining_rear),\n                    state.reversed_rear\n\
    \                );\n                state.remaining_rear = next_link(state.remaining_rear);\n\
    \                state.valid_count++;\n            } else {\n                assert(next_link(state.remaining_rear)\
    \ == -1);\n                state.reversed_rear = make_link(\n                \
    \    link_value(state.remaining_rear),\n                    state.reversed_rear\n\
    \                );\n                state.remaining_rear = -1;\n            \
    \    state.phase = RotationPhase::appending;\n            }\n        } else if\
    \ (state.phase == RotationPhase::appending) {\n            assert(state.valid_count\
    \ >= 0);\n            if (state.valid_count == 0) {\n                state.phase\
    \ = RotationPhase::done;\n            } else {\n                assert(state.reversed_front\
    \ != -1);\n                state.reversed_rear = make_link(\n                \
    \    link_value(state.reversed_front),\n                    state.reversed_rear\n\
    \                );\n                state.reversed_front = next_link(state.reversed_front);\n\
    \                state.valid_count--;\n            }\n        }\n        return\
    \ state;\n    }\n\n    RotationState invalidate(RotationState state) const {\n\
    \        if (state.phase == RotationPhase::reversing) {\n            state.valid_count--;\n\
    \        } else if (state.phase == RotationPhase::appending) {\n            if\
    \ (state.valid_count == 0) {\n                assert(state.reversed_rear != -1);\n\
    \                state.reversed_rear = next_link(state.reversed_rear);\n     \
    \           state.phase = RotationPhase::done;\n            } else {\n       \
    \         state.valid_count--;\n            }\n        }\n        return state;\n\
    \    }\n\n    PersistentQueue execute_twice(\n        int front_size,\n      \
    \  int front,\n        RotationState rotation,\n        int rear_size,\n     \
    \   int rear,\n        int back_value\n    ) const {\n        rotation = execute(std::move(rotation));\n\
    \        rotation = execute(std::move(rotation));\n        if (rotation.phase\
    \ == RotationPhase::done) {\n            front = rotation.reversed_rear;\n   \
    \         rotation = RotationState();\n        }\n        return PersistentQueue(\n\
    \            front_size,\n            front,\n            rotation,\n        \
    \    rear_size,\n            rear,\n            back_value,\n            _pool\n\
    \        );\n    }\n\n    PersistentQueue check(\n        int front_size,\n  \
    \      int front,\n        RotationState rotation,\n        int rear_size,\n \
    \       int rear,\n        int back_value\n    ) const {\n        if (rear_size\
    \ <= front_size) {\n            return execute_twice(\n                front_size,\n\
    \                front,\n                rotation,\n                rear_size,\n\
    \                rear,\n                back_value\n            );\n        }\n\
    \n        RotationState next_rotation;\n        next_rotation.phase = RotationPhase::reversing;\n\
    \        next_rotation.remaining_front = front;\n        next_rotation.remaining_rear\
    \ = rear;\n        return execute_twice(\n            front_size + rear_size,\n\
    \            front,\n            next_rotation,\n            0,\n            -1,\n\
    \            back_value\n        );\n    }\n\n   public:\n    PersistentQueue()\n\
    \        : _front_size(0),\n          _front(-1),\n          _rear_size(0),\n\
    \          _rear(-1),\n          _back_value(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentQueue(const PersistentQueue& other)\n        : _front_size(other._front_size),\n\
    \          _front(other._front),\n          _rotation(other._rotation),\n    \
    \      _rear_size(other._rear_size),\n          _rear(other._rear),\n        \
    \  _back_value(other._back_value),\n          _pool(other._pool) {\n        if\
    \ (_pool) retain_state();\n    }\n\n    PersistentQueue(PersistentQueue&& other)\
    \ noexcept\n        : _front_size(other._front_size),\n          _front(other._front),\n\
    \          _rotation(other._rotation),\n          _rear_size(other._rear_size),\n\
    \          _rear(other._rear),\n          _back_value(other._back_value),\n  \
    \        _pool(std::move(other._pool)) {\n        other._front_size = other._rear_size\
    \ = 0;\n        other._front = other._rear = other._back_value = -1;\n       \
    \ other._rotation = RotationState();\n    }\n\n    PersistentQueue& operator=(const\
    \ PersistentQueue& other) {\n        if (this == &other) return *this;\n     \
    \   if (other._pool) other.retain_state();\n        if (_pool) release_state();\n\
    \        _front_size = other._front_size;\n        _front = other._front;\n  \
    \      _rotation = other._rotation;\n        _rear_size = other._rear_size;\n\
    \        _rear = other._rear;\n        _back_value = other._back_value;\n    \
    \    _pool = other._pool;\n        return *this;\n    }\n\n    PersistentQueue&\
    \ operator=(PersistentQueue&& other) noexcept {\n        if (this == &other) return\
    \ *this;\n        if (_pool) release_state();\n        _front_size = other._front_size;\n\
    \        _front = other._front;\n        _rotation = other._rotation;\n      \
    \  _rear_size = other._rear_size;\n        _rear = other._rear;\n        _back_value\
    \ = other._back_value;\n        _pool = std::move(other._pool);\n        other._front_size\
    \ = other._rear_size = 0;\n        other._front = other._rear = other._back_value\
    \ = -1;\n        other._rotation = RotationState();\n        return *this;\n \
    \   }\n\n    ~PersistentQueue() {\n        if (_pool) release_state();\n    }\n\
    \n    int size() const {\n        return _front_size + _rear_size;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void release()\
    \ {\n        if (_pool) release_state();\n        _front_size = _rear_size = 0;\n\
    \        _front = _rear = _back_value = -1;\n        _rotation = RotationState();\n\
    \        _pool = std::make_shared<Pool>();\n    }\n\n    std::size_t node_count()\
    \ const { return _pool ? _pool->size() : 0; }\n\n    const T& front() const {\n\
    \        assert(!empty() && _front != -1);\n        return *_pool->values[link_value(_front)];\n\
    \    }\n\n    const T& back() const {\n        assert(!empty() && _back_value\
    \ != -1);\n        return *_pool->values[_back_value];\n    }\n\n    PersistentQueue\
    \ push(T value) const {\n        int value_index = store_value(std::move(value));\n\
    \        int rear = make_link(value_index, _rear);\n        return check(\n  \
    \          _front_size,\n            _front,\n            _rotation,\n       \
    \     _rear_size + 1,\n            rear,\n            value_index\n        );\n\
    \    }\n\n    PersistentQueue push_back(T value) const {\n        return push(std::move(value));\n\
    \    }\n\n    PersistentQueue pop() const {\n        assert(!empty() && _front\
    \ != -1);\n        int back_value = size() == 1 ? -1 : _back_value;\n        return\
    \ check(\n            _front_size - 1,\n            next_link(_front),\n     \
    \       invalidate(_rotation),\n            _rear_size,\n            _rear,\n\
    \            back_value\n        );\n    }\n\n    PersistentQueue pop_front()\
    \ const {\n        return pop();\n    }\n\n    PersistentQueue clear() const {\n\
    \        return PersistentQueue(\n            0,\n            -1,\n          \
    \  RotationState(),\n            0,\n            -1,\n            -1,\n      \
    \      _pool\n        );\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"ds/stack/persistent_stack.hpp\"\n\n\n\n#line 11 \"ds/stack/persistent_stack.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Purely persistent LIFO stack with\
    \ O(1) operations.\ntemplate <class T>\nstruct PersistentStack {\n   private:\n\
    \    struct Node {\n        T value;\n        int next;\n\n        template <class...\
    \ Args>\n        Node(int next_node, Args&&... args)\n            : value(std::forward<Args>(args)...),\
    \ next(next_node) {}\n    };\n\n    struct Pool {\n        std::deque<std::optional<Node>>\
    \ nodes;\n        std::vector<int> references;\n        std::vector<int> next_free;\n\
    \        int first_free = -1;\n        std::size_t live_nodes = 0;\n\n       \
    \ template <class... Args>\n        int emplace(int next, Args&&... args) {\n\
    \            int result;\n            if (first_free == -1) {\n              \
    \  result = int(nodes.size());\n                nodes.emplace_back(std::in_place,\
    \ next, std::forward<Args>(args)...);\n                references.push_back(0);\n\
    \                next_free.push_back(-1);\n            } else {\n            \
    \    result = first_free;\n                first_free = next_free[result];\n \
    \               nodes[result].emplace(next, std::forward<Args>(args)...);\n  \
    \              references[result] = 0;\n            }\n            retain(next);\n\
    \            ++live_nodes;\n            return result;\n        }\n\n        Node&\
    \ operator[](int node) { return *nodes[node]; }\n        const Node& operator[](int\
    \ node) const { return *nodes[node]; }\n\n        void retain(int node) {\n  \
    \          if (node != -1) ++references[node];\n        }\n\n        void release(int\
    \ node) {\n            while (node != -1) {\n                assert(nodes[node].has_value()\
    \ && references[node] > 0);\n                if (--references[node] != 0) return;\n\
    \                int next = nodes[node]->next;\n                nodes[node].reset();\n\
    \                next_free[node] = first_free;\n                first_free = node;\n\
    \                --live_nodes;\n                node = next;\n            }\n\
    \        }\n    };\n\n    int _size;\n    int _top;\n    std::shared_ptr<Pool>\
    \ _pool;\n\n    PersistentStack(\n        int stack_size,\n        int top,\n\
    \        std::shared_ptr<Pool> pool\n    )\n        : _size(stack_size), _top(top),\
    \ _pool(std::move(pool)) {\n        _pool->retain(_top);\n    }\n\n   public:\n\
    \    PersistentStack()\n        : _size(0),\n          _top(-1),\n          _pool(std::make_shared<Pool>())\
    \ {}\n\n    PersistentStack(const PersistentStack& other)\n        : _size(other._size),\
    \ _top(other._top), _pool(other._pool) {\n        if (_pool) _pool->retain(_top);\n\
    \    }\n\n    PersistentStack(PersistentStack&& other) noexcept\n        : _size(other._size),\
    \ _top(other._top), _pool(std::move(other._pool)) {\n        other._size = 0;\n\
    \        other._top = -1;\n    }\n\n    PersistentStack& operator=(const PersistentStack&\
    \ other) {\n        if (this == &other) return *this;\n        if (other._pool)\
    \ other._pool->retain(other._top);\n        if (_pool) _pool->release(_top);\n\
    \        _size = other._size;\n        _top = other._top;\n        _pool = other._pool;\n\
    \        return *this;\n    }\n\n    PersistentStack& operator=(PersistentStack&&\
    \ other) noexcept {\n        if (this == &other) return *this;\n        if (_pool)\
    \ _pool->release(_top);\n        _size = other._size;\n        _top = other._top;\n\
    \        _pool = std::move(other._pool);\n        other._size = 0;\n        other._top\
    \ = -1;\n        return *this;\n    }\n\n    ~PersistentStack() {\n        if\
    \ (_pool) _pool->release(_top);\n    }\n\n    int size() const {\n        return\
    \ _size;\n    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\
    \n    void release() {\n        if (_pool) _pool->release(_top);\n        _size\
    \ = 0;\n        _top = -1;\n        _pool = std::make_shared<Pool>();\n    }\n\
    \n    std::size_t node_count() const { return _pool ? _pool->live_nodes : 0; }\n\
    \n    const T& top() const {\n        assert(!empty() && _top != -1);\n      \
    \  return (*_pool)[_top].value;\n    }\n\n    PersistentStack push(T value) const\
    \ {\n        return emplace(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    PersistentStack emplace(Args&&... args) const {\n        int top\
    \ = _pool->emplace(_top, std::forward<Args>(args)...);\n        return PersistentStack(\n\
    \            _size + 1,\n            top,\n            _pool\n        );\n   \
    \ }\n\n    PersistentStack pop() const {\n        assert(!empty() && _top != -1);\n\
    \        return PersistentStack(_size - 1, (*_pool)[_top].next, _pool);\n    }\n\
    \n    PersistentStack clear() const {\n        return PersistentStack(0, -1, _pool);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace acted_monoid {\n\ntemplate <typename T>\n\
    struct RangeAddRangeSumNode {\n    T sum;\n    long long size;\n};\n\ntemplate\
    \ <typename T>\nstruct RangeAddRangeSum {\n    using value_type = RangeAddRangeSumNode<T>;\n\
    \    using operator_type = T;\n    static constexpr bool commutative = true;\n\
    \    static constexpr bool operator_commutative = true;\n\n    // Value Monoid\
    \ (Sum)\n    static constexpr value_type id() {\n        return {T(0), 0};\n \
    \   }\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        return {a.sum + b.sum, a.size + b.size};\n    }\n    static constexpr\
    \ value_type inv(const value_type& x) {\n        return {-x.sum, -x.size};\n \
    \   }\n\n    // Operator Monoid (Add)\n    static constexpr operator_type op_id()\
    \ {\n        return 0;\n    }\n    static constexpr operator_type op_comp(const\
    \ operator_type& f, const operator_type& g) {\n        return f + g;\n    }\n\n\
    \    // Mapping (sum + f * size)\n    static constexpr value_type mapping(const\
    \ operator_type& f, const value_type& x) {\n        return {x.sum + f * x.size,\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"monoid/add.hpp\"\
    \n\n\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for addition (Range\
    \ Sum).\ntemplate <typename T>\nstruct Add {\n    using value_type = T;\n    static\
    \ constexpr bool commutative = true;\n\n    // Returns the identity element for\
    \ addition, which is 0.\n    static constexpr T id() {\n        return T(0);\n\
    \    }\n\n    // Returns the sum of a and b.\n    static constexpr T op(const\
    \ T& a, const T& b) {\n        return a + b;\n    }\n\n    static constexpr T\
    \ inv(const T& x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"\
    utilities/fast_io.hpp\"\n#include <array>\n#include <cerrno>\n#include <charconv>\n\
    #line 9 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include <cstdlib>\n#line\
    \ 12 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include <iterator>\n#include\
    \ <string>\n#include <sys/stat.h>\n#include <type_traits>\n#line 18 \"utilities/fast_io.hpp\"\
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
    \ utilities\n}  // namespace m1une\n\n\n#line 17 \"verify/ds/persistent_release.test.cpp\"\
    \n\n#line 22 \"verify/ds/persistent_release.test.cpp\"\n\nvoid test_release()\
    \ {\n    {\n        m1une::ds::PersistentDynamicArray<int> base = {1, 2, 3, 4};\n\
    \        auto branch = base.insert(2, 9).reverse();\n        std::size_t live\
    \ = base.node_count();\n        branch.release();\n        assert(base.node_count()\
    \ < live);\n        std::vector<int> expected = {1, 2, 3, 4};\n        assert(base.to_vector()\
    \ == expected);\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        using Array = m1une::ds::PersistentDynamicMonoidArray<m1une::monoid::Add<long\
    \ long>>;\n        Array base(std::vector<long long>{1, 2, 3});\n        auto\
    \ branch = base.set(1, 7).reverse();\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.all_prod()\
    \ == 6);\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        using ActedMonoid = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n        using Array = m1une::ds::PersistentDynamicLazyMonoidArray<ActedMonoid>;\n\
    \        Array base(std::vector<long long>{1, 2, 3});\n        auto branch = base.apply(0,\
    \ 2, 5).reverse();\n        std::size_t live = base.node_count();\n        branch.release();\n\
    \        assert(base.node_count() < live && base.all_prod().sum == 6);\n     \
    \   base.release();\n        assert(base.empty() && base.node_count() == 0);\n\
    \    }\n    {\n        m1une::ds::PersistentDsu base(5);\n        auto branch\
    \ = base.merge(0, 1).merge(1, 2);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && !base.same(0,\
    \ 1));\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        using Dsu = m1une::ds::PersistentPotentializedDsu<m1une::monoid::Add<long\
    \ long>>;\n        Dsu base(4);\n        auto branch = base.merge(0, 1, 3).first.merge(1,\
    \ 2, 4).first;\n        std::size_t live = base.node_count();\n        branch.release();\n\
    \        assert(base.node_count() < live && !base.same(0, 1));\n        base.release();\n\
    \        assert(base.empty() && base.node_count() == 0);\n    }\n    {\n     \
    \   m1une::ds::PersistentStack<int> base;\n        base = base.push(1).push(2);\n\
    \        auto branch = base.push(3);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.top()\
    \ == 2);\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        m1une::ds::PersistentQueue<int> base;\n      \
    \  base = base.push(1).push(2).push(3);\n        auto branch = base.push(4).pop();\n\
    \        std::size_t live = base.node_count();\n        branch.release();\n  \
    \      assert(base.node_count() < live);\n        assert(base.front() == 1 &&\
    \ base.back() == 3);\n        base.release();\n        assert(base.empty() &&\
    \ base.node_count() == 0);\n    }\n    {\n        m1une::ds::PersistentDeque<int>\
    \ base;\n        base = base.push_back(1).push_front(2).push_back(3);\n      \
    \  auto branch = base.push_front(4).pop_back();\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live);\n      \
    \  assert(base.front() == 2 && base.back() == 3);\n        base.release();\n \
    \       assert(base.empty() && base.node_count() == 0);\n    }\n    {\n      \
    \  m1une::ds::PersistentOrderedMultiset<int> base = {1, 2, 3};\n        auto branch\
    \ = base.insert(4).erase(2);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.contains(2));\n\
    \        base.release();\n        assert(base.empty() && base.node_count() ==\
    \ 0);\n    }\n    {\n        m1une::ds::PersistentOrderedSet<int> base = {1, 2,\
    \ 3};\n        auto branch = base.insert(4).erase(2);\n        std::size_t live\
    \ = base.node_count();\n        branch.release();\n        assert(base.node_count()\
    \ < live && base.contains(2));\n        base.release();\n        assert(base.empty()\
    \ && base.node_count() == 0);\n    }\n    {\n        m1une::ds::PartiallyPersistentDsu\
    \ dsu(4);\n        dsu.merge(0, 1);\n        dsu.merge(2, 3);\n        dsu.release();\n\
    \        assert(dsu.empty() && dsu.time() == 0);\n    }\n    {\n        auto value\
    \ = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime = value;\n\
    \        m1une::ds::PersistentDynamicArray<std::shared_ptr<int>> empty;\n    \
    \    auto version = empty.push_back(value);\n        value.reset();\n        assert(!lifetime.expired());\n\
    \        version.release();\n        assert(lifetime.expired());\n    }\n    {\n\
    \        auto value = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime\
    \ = value;\n        m1une::ds::PersistentStack<std::shared_ptr<int>> empty;\n\
    \        auto version = empty.push(value);\n        value.reset();\n        version.release();\n\
    \        assert(lifetime.expired());\n    }\n    {\n        auto value = std::make_shared<int>(1);\n\
    \        std::weak_ptr<int> lifetime = value;\n        m1une::ds::PersistentQueue<std::shared_ptr<int>>\
    \ empty;\n        auto version = empty.push(value);\n        value.reset();\n\
    \        version.release();\n        assert(lifetime.expired());\n    }\n    {\n\
    \        auto value = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime\
    \ = value;\n        m1une::ds::PersistentDeque<std::shared_ptr<int>> empty;\n\
    \        auto version = empty.push_back(value);\n        value.reset();\n    \
    \    version.release();\n        assert(lifetime.expired());\n    }\n}\n\nint\
    \ main() {\n    test_release();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int n, query_count;\n    fast_input\
    \ >> n >> query_count;\n    using Dsu = m1une::ds::PersistentDsu;\n    std::vector<Dsu>\
    \ versions;\n    versions.emplace_back(n);\n    while (query_count--) {\n    \
    \    int type, version, u, v;\n        fast_input >> type >> version >> u >> v;\n\
    \        const Dsu& base = versions[version + 1];\n        if (type == 0) {\n\
    \            versions.push_back(base.merge(u, v));\n        } else {\n       \
    \     fast_output << int(base.same(u, v)) << '\\n';\n            versions.emplace_back();\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include \"../../ds/bst/persistent_ordered_multiset.hpp\"\n#include \"../../ds/bst/persistent_ordered_set.hpp\"\
    \n#include \"../../ds/deque/persistent_deque.hpp\"\n#include \"../../ds/dsu/partially_persistent_dsu.hpp\"\
    \n#include \"../../ds/dsu/persistent_dsu.hpp\"\n#include \"../../ds/dsu/persistent_potentialized_dsu.hpp\"\
    \n#include \"../../ds/dynamic_array/persistent_dynamic_array.hpp\"\n#include \"\
    ../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp\"\n#include \"\
    ../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp\"\n#include \"../../ds/queue/persistent_queue.hpp\"\
    \n#include \"../../ds/stack/persistent_stack.hpp\"\n#include \"../../acted_monoid/range_add_range_sum.hpp\"\
    \n#include \"../../monoid/add.hpp\"\n#include \"../../utilities/fast_io.hpp\"\n\
    \n#include <cassert>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nvoid test_release() {\n    {\n        m1une::ds::PersistentDynamicArray<int>\
    \ base = {1, 2, 3, 4};\n        auto branch = base.insert(2, 9).reverse();\n \
    \       std::size_t live = base.node_count();\n        branch.release();\n   \
    \     assert(base.node_count() < live);\n        std::vector<int> expected = {1,\
    \ 2, 3, 4};\n        assert(base.to_vector() == expected);\n        base.release();\n\
    \        assert(base.empty() && base.node_count() == 0);\n    }\n    {\n     \
    \   using Array = m1une::ds::PersistentDynamicMonoidArray<m1une::monoid::Add<long\
    \ long>>;\n        Array base(std::vector<long long>{1, 2, 3});\n        auto\
    \ branch = base.set(1, 7).reverse();\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.all_prod()\
    \ == 6);\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        using ActedMonoid = m1une::acted_monoid::RangeAddRangeSum<long\
    \ long>;\n        using Array = m1une::ds::PersistentDynamicLazyMonoidArray<ActedMonoid>;\n\
    \        Array base(std::vector<long long>{1, 2, 3});\n        auto branch = base.apply(0,\
    \ 2, 5).reverse();\n        std::size_t live = base.node_count();\n        branch.release();\n\
    \        assert(base.node_count() < live && base.all_prod().sum == 6);\n     \
    \   base.release();\n        assert(base.empty() && base.node_count() == 0);\n\
    \    }\n    {\n        m1une::ds::PersistentDsu base(5);\n        auto branch\
    \ = base.merge(0, 1).merge(1, 2);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && !base.same(0,\
    \ 1));\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        using Dsu = m1une::ds::PersistentPotentializedDsu<m1une::monoid::Add<long\
    \ long>>;\n        Dsu base(4);\n        auto branch = base.merge(0, 1, 3).first.merge(1,\
    \ 2, 4).first;\n        std::size_t live = base.node_count();\n        branch.release();\n\
    \        assert(base.node_count() < live && !base.same(0, 1));\n        base.release();\n\
    \        assert(base.empty() && base.node_count() == 0);\n    }\n    {\n     \
    \   m1une::ds::PersistentStack<int> base;\n        base = base.push(1).push(2);\n\
    \        auto branch = base.push(3);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.top()\
    \ == 2);\n        base.release();\n        assert(base.empty() && base.node_count()\
    \ == 0);\n    }\n    {\n        m1une::ds::PersistentQueue<int> base;\n      \
    \  base = base.push(1).push(2).push(3);\n        auto branch = base.push(4).pop();\n\
    \        std::size_t live = base.node_count();\n        branch.release();\n  \
    \      assert(base.node_count() < live);\n        assert(base.front() == 1 &&\
    \ base.back() == 3);\n        base.release();\n        assert(base.empty() &&\
    \ base.node_count() == 0);\n    }\n    {\n        m1une::ds::PersistentDeque<int>\
    \ base;\n        base = base.push_back(1).push_front(2).push_back(3);\n      \
    \  auto branch = base.push_front(4).pop_back();\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live);\n      \
    \  assert(base.front() == 2 && base.back() == 3);\n        base.release();\n \
    \       assert(base.empty() && base.node_count() == 0);\n    }\n    {\n      \
    \  m1une::ds::PersistentOrderedMultiset<int> base = {1, 2, 3};\n        auto branch\
    \ = base.insert(4).erase(2);\n        std::size_t live = base.node_count();\n\
    \        branch.release();\n        assert(base.node_count() < live && base.contains(2));\n\
    \        base.release();\n        assert(base.empty() && base.node_count() ==\
    \ 0);\n    }\n    {\n        m1une::ds::PersistentOrderedSet<int> base = {1, 2,\
    \ 3};\n        auto branch = base.insert(4).erase(2);\n        std::size_t live\
    \ = base.node_count();\n        branch.release();\n        assert(base.node_count()\
    \ < live && base.contains(2));\n        base.release();\n        assert(base.empty()\
    \ && base.node_count() == 0);\n    }\n    {\n        m1une::ds::PartiallyPersistentDsu\
    \ dsu(4);\n        dsu.merge(0, 1);\n        dsu.merge(2, 3);\n        dsu.release();\n\
    \        assert(dsu.empty() && dsu.time() == 0);\n    }\n    {\n        auto value\
    \ = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime = value;\n\
    \        m1une::ds::PersistentDynamicArray<std::shared_ptr<int>> empty;\n    \
    \    auto version = empty.push_back(value);\n        value.reset();\n        assert(!lifetime.expired());\n\
    \        version.release();\n        assert(lifetime.expired());\n    }\n    {\n\
    \        auto value = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime\
    \ = value;\n        m1une::ds::PersistentStack<std::shared_ptr<int>> empty;\n\
    \        auto version = empty.push(value);\n        value.reset();\n        version.release();\n\
    \        assert(lifetime.expired());\n    }\n    {\n        auto value = std::make_shared<int>(1);\n\
    \        std::weak_ptr<int> lifetime = value;\n        m1une::ds::PersistentQueue<std::shared_ptr<int>>\
    \ empty;\n        auto version = empty.push(value);\n        value.reset();\n\
    \        version.release();\n        assert(lifetime.expired());\n    }\n    {\n\
    \        auto value = std::make_shared<int>(1);\n        std::weak_ptr<int> lifetime\
    \ = value;\n        m1une::ds::PersistentDeque<std::shared_ptr<int>> empty;\n\
    \        auto version = empty.push_back(value);\n        value.reset();\n    \
    \    version.release();\n        assert(lifetime.expired());\n    }\n}\n\nint\
    \ main() {\n    test_release();\n\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n    int n, query_count;\n    fast_input\
    \ >> n >> query_count;\n    using Dsu = m1une::ds::PersistentDsu;\n    std::vector<Dsu>\
    \ versions;\n    versions.emplace_back(n);\n    while (query_count--) {\n    \
    \    int type, version, u, v;\n        fast_input >> type >> version >> u >> v;\n\
    \        const Dsu& base = versions[version + 1];\n        if (type == 0) {\n\
    \            versions.push_back(base.merge(u, v));\n        } else {\n       \
    \     fast_output << int(base.same(u, v)) << '\\n';\n            versions.emplace_back();\n\
    \        }\n    }\n}\n"
  dependsOn:
  - ds/bst/persistent_ordered_multiset.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/bst/persistent_ordered_set.hpp
  - ds/bst/persistent_ordered_multiset.hpp
  - ds/deque/persistent_deque.hpp
  - ds/dsu/partially_persistent_dsu.hpp
  - ds/dsu/persistent_dsu.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/dsu/persistent_potentialized_dsu.hpp
  - monoid/concept.hpp
  - ds/dynamic_array/persistent_dynamic_array.hpp
  - ds/detail/persistent_binary_node_pool.hpp
  - ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - ds/dynamic_array/persistent_dynamic_monoid_array.hpp
  - monoid/concept.hpp
  - ds/queue/persistent_queue.hpp
  - ds/stack/persistent_stack.hpp
  - acted_monoid/range_add_range_sum.hpp
  - monoid/add.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/persistent_release.test.cpp
  requiredBy: []
  timestamp: '2026-08-11 13:59:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/persistent_release.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/persistent_release.test.cpp
- /verify/verify/ds/persistent_release.test.cpp.html
title: verify/ds/persistent_release.test.cpp
---
