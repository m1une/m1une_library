---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_set.hpp
    title: Persistent Ordered Set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/persistent_ordered_multiset.test.cpp
    title: verify/ds/bst/persistent_ordered_multiset.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/persistent_ordered_set.test.cpp
    title: verify/ds/bst/persistent_ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/persistent_ordered_multiset.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <functional>\n#include <initializer_list>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T,\
    \ typename Compare>\nstruct PersistentOrderedSet;\n\ntemplate <typename T, typename\
    \ Compare = std::less<T>>\nstruct PersistentOrderedMultiset {\n   private:\n \
    \   friend struct PersistentOrderedSet<T, Compare>;\n    struct Node {\n     \
    \   T key;\n        int count;\n        int size;\n        int distinct_size;\n\
    \        int rank_color;\n        int l;\n        int r;\n        int min_leaf;\n\
    \        int max_leaf;\n\n        Node(T value, int multiplicity, int maximum)\n\
    \            : key(std::move(value)),\n              count(multiplicity),\n  \
    \            size(multiplicity),\n              distinct_size(1),\n          \
    \    rank_color(1),\n              l(-1),\n              r(-1),\n            \
    \  min_leaf(maximum),\n              max_leaf(maximum) {}\n\n        Node(T separator,\
    \ int subtree_size, int left_size, int unique_count, int node_rank,\n        \
    \     int left, int right, int minimum, int maximum, bool is_black)\n        \
    \    : key(std::move(separator)),\n              count(left_size),\n         \
    \     size(subtree_size),\n              distinct_size(unique_count),\n      \
    \        rank_color(node_rank * 2 + int(is_black)),\n              l(left),\n\
    \              r(right),\n              min_leaf(minimum),\n              max_leaf(maximum)\
    \ {}\n    };\n\n    static constexpr int pool_block_bits = 16;\n    static constexpr\
    \ int pool_block_size = 1 << pool_block_bits;\n    static constexpr int pool_block_mask\
    \ = pool_block_size - 1;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
    \ blocks;\n        int node_count = 0;\n\n        const Node& operator[](int index)\
    \ const {\n            return blocks[index >> pool_block_bits][index & pool_block_mask];\n\
    \        }\n\n        template <class... Args>\n        int emplace(Args&&...\
    \ args) {\n            if ((node_count & pool_block_mask) == 0) {\n          \
    \      blocks.emplace_back();\n                blocks.back().reserve(pool_block_size);\n\
    \            }\n            blocks.back().emplace_back(std::forward<Args>(args)...);\n\
    \            return node_count++;\n        }\n    };\n\n    inline static Pool\
    \ pool;\n\n    int root;\n    Compare comp;\n\n    static int subtree_size(int\
    \ t) { return t == -1 ? 0 : pool[t].size; }\n    static int subtree_distinct_size(int\
    \ t) { return t == -1 ? 0 : pool[t].distinct_size; }\n    static int node_rank(int\
    \ t) { return pool[t].rank_color >> 1; }\n    static bool is_black(int t) { return\
    \ (pool[t].rank_color & 1) != 0; }\n    static bool is_leaf(int t) { return pool[t].l\
    \ == -1; }\n\n    bool equal(const T& a, const T& b) const {\n        return !comp(a,\
    \ b) && !comp(b, a);\n    }\n\n    static int make_leaf(T key, int count) {\n\
    \        const int id = pool.node_count;\n        return pool.emplace(std::move(key),\
    \ count, id);\n    }\n\n    static int make_node(int l, int r, bool black) {\n\
    \        assert(l != -1 && r != -1);\n        const int rank = node_rank(l) +\
    \ int(is_black(l));\n        assert(rank == node_rank(r) + int(is_black(r)));\n\
    \        return pool.emplace(pool[pool[l].max_leaf].key,\n                   \
    \         subtree_size(l) + subtree_size(r),\n                            subtree_size(l),\n\
    \                            subtree_distinct_size(l) + subtree_distinct_size(r),\n\
    \                            rank, l, r, pool[l].min_leaf, pool[r].max_leaf,\n\
    \                            black);\n    }\n\n    static int as_root(int t) {\n\
    \        if (t == -1 || is_black(t)) return t;\n        return make_node(pool[t].l,\
    \ pool[t].r, true);\n    }\n\n    static int merge_sub(int a, int b) {\n     \
    \   assert(a != -1 && b != -1);\n        if (node_rank(a) < node_rank(b)) {\n\
    \            const Node& right = pool[b];\n            int c = merge_sub(a, right.l);\n\
    \            if (is_black(b) && !is_black(c) && !is_black(pool[c].l)) {\n    \
    \            const Node& middle = pool[c];\n                if (is_black(right.r))\
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
    \ compare) : root(node), comp(std::move(compare)) {}\n\n   public:\n    explicit\
    \ PersistentOrderedMultiset(Compare compare) : root(-1), comp(std::move(compare))\
    \ {}\n    PersistentOrderedMultiset() : PersistentOrderedMultiset(Compare()) {}\n\
    \n    PersistentOrderedMultiset(std::initializer_list<T> init, Compare compare\
    \ = Compare())\n        : PersistentOrderedMultiset(std::move(compare)) {\n  \
    \      for (const T& x : init) *this = insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator last, Compare\
    \ compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) *this = insert(*first++);\n    }\n\n    int\
    \ size() const { return subtree_size(root); }\n    int unique_size() const { return\
    \ subtree_distinct_size(root); }\n    bool empty() const { return root == -1;\
    \ }\n    PersistentOrderedMultiset clear() const { return PersistentOrderedMultiset(-1,\
    \ comp); }\n\n    PersistentOrderedMultiset insert(T key, int multiplicity = 1)\
    \ const {\n        assert(multiplicity > 0);\n        int old_count = 0;\n   \
    \     const int changed_root = change_count_impl(root, key, multiplicity, old_count);\n\
    \        if (old_count != 0) {\n            return PersistentOrderedMultiset(changed_root,\
    \ comp);\n        }\n        auto [l, r] = split_nodes(root, key);\n        return\
    \ PersistentOrderedMultiset(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ multiplicity)), r), comp);\n    }\n\n   private:\n    PersistentOrderedMultiset\
    \ insert_unique(T key) const {\n        if (contains(key)) return *this;\n   \
    \     auto [l, r] = split_nodes(root, key);\n        return PersistentOrderedMultiset(\n\
    \            merge_nodes(merge_nodes(l, make_leaf(std::move(key), 1)), r), comp);\n\
    \    }\n\n   public:\n    PersistentOrderedMultiset erase_one(const T& key) const\
    \ {\n        int old_count = 0;\n        const int changed_root = change_count_impl(root,\
    \ key, -1, old_count);\n        if (old_count == 0) return *this;\n        if\
    \ (old_count > 1) return PersistentOrderedMultiset(changed_root, comp);\n    \
    \    auto [l, r] = split_nodes(root, key);\n        auto [discarded, rest] = pop_min(r);\n\
    \        assert(equal(pool[discarded].key, key));\n        return PersistentOrderedMultiset(merge_nodes(l,\
    \ rest), comp);\n    }\n\n    PersistentOrderedMultiset erase(const T& key) const\
    \ { return erase_one(key); }\n\n    PersistentOrderedMultiset erase_all(const\
    \ T& key) const {\n        const int old_count = count(key);\n        if (old_count\
    \ == 0) return *this;\n        auto [l, r] = split_nodes(root, key);\n       \
    \ auto [discarded, rest] = pop_min(r);\n        assert(equal(pool[discarded].key,\
    \ key));\n        return PersistentOrderedMultiset(merge_nodes(l, rest), comp);\n\
    \    }\n\n    bool contains(const T& key) const { return count(key) > 0; }\n \
    \   int count(const T& key) const { return count_impl(root, key); }\n\n    const\
    \ T* find_by_order(int k) const {\n        assert(0 <= k && k < size());\n   \
    \     return kth_impl(root, k);\n    }\n\n    T kth(int k) const { return *find_by_order(k);\
    \ }\n    int order_of_key(const T& key) const { return order_of_key_impl(root,\
    \ key, false); }\n    int count_less(const T& key) const { return order_of_key(key);\
    \ }\n    int count_less_equal(const T& key) const { return order_of_key_impl(root,\
    \ key, true); }\n    int count_greater(const T& key) const { return size() - count_less_equal(key);\
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
    \ T& key) const {\n        auto [l, r] = split_nodes(root, key);\n        return\
    \ {PersistentOrderedMultiset(l, comp), PersistentOrderedMultiset(r, comp)};\n\
    \    }\n\n    PersistentOrderedMultiset merge(const PersistentOrderedMultiset&\
    \ other) const {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        return PersistentOrderedMultiset(merge_nodes(root, other.root), comp);\n\
    \    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T> result;\n\
    \        result.reserve(size());\n        dump_impl(root, result);\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_PERSISTENT_ORDERED_MULTISET_HPP\n#define M1UNE_PERSISTENT_ORDERED_MULTISET_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <typename T, typename Compare>\nstruct PersistentOrderedSet;\n\ntemplate\
    \ <typename T, typename Compare = std::less<T>>\nstruct PersistentOrderedMultiset\
    \ {\n   private:\n    friend struct PersistentOrderedSet<T, Compare>;\n    struct\
    \ Node {\n        T key;\n        int count;\n        int size;\n        int distinct_size;\n\
    \        int rank_color;\n        int l;\n        int r;\n        int min_leaf;\n\
    \        int max_leaf;\n\n        Node(T value, int multiplicity, int maximum)\n\
    \            : key(std::move(value)),\n              count(multiplicity),\n  \
    \            size(multiplicity),\n              distinct_size(1),\n          \
    \    rank_color(1),\n              l(-1),\n              r(-1),\n            \
    \  min_leaf(maximum),\n              max_leaf(maximum) {}\n\n        Node(T separator,\
    \ int subtree_size, int left_size, int unique_count, int node_rank,\n        \
    \     int left, int right, int minimum, int maximum, bool is_black)\n        \
    \    : key(std::move(separator)),\n              count(left_size),\n         \
    \     size(subtree_size),\n              distinct_size(unique_count),\n      \
    \        rank_color(node_rank * 2 + int(is_black)),\n              l(left),\n\
    \              r(right),\n              min_leaf(minimum),\n              max_leaf(maximum)\
    \ {}\n    };\n\n    static constexpr int pool_block_bits = 16;\n    static constexpr\
    \ int pool_block_size = 1 << pool_block_bits;\n    static constexpr int pool_block_mask\
    \ = pool_block_size - 1;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
    \ blocks;\n        int node_count = 0;\n\n        const Node& operator[](int index)\
    \ const {\n            return blocks[index >> pool_block_bits][index & pool_block_mask];\n\
    \        }\n\n        template <class... Args>\n        int emplace(Args&&...\
    \ args) {\n            if ((node_count & pool_block_mask) == 0) {\n          \
    \      blocks.emplace_back();\n                blocks.back().reserve(pool_block_size);\n\
    \            }\n            blocks.back().emplace_back(std::forward<Args>(args)...);\n\
    \            return node_count++;\n        }\n    };\n\n    inline static Pool\
    \ pool;\n\n    int root;\n    Compare comp;\n\n    static int subtree_size(int\
    \ t) { return t == -1 ? 0 : pool[t].size; }\n    static int subtree_distinct_size(int\
    \ t) { return t == -1 ? 0 : pool[t].distinct_size; }\n    static int node_rank(int\
    \ t) { return pool[t].rank_color >> 1; }\n    static bool is_black(int t) { return\
    \ (pool[t].rank_color & 1) != 0; }\n    static bool is_leaf(int t) { return pool[t].l\
    \ == -1; }\n\n    bool equal(const T& a, const T& b) const {\n        return !comp(a,\
    \ b) && !comp(b, a);\n    }\n\n    static int make_leaf(T key, int count) {\n\
    \        const int id = pool.node_count;\n        return pool.emplace(std::move(key),\
    \ count, id);\n    }\n\n    static int make_node(int l, int r, bool black) {\n\
    \        assert(l != -1 && r != -1);\n        const int rank = node_rank(l) +\
    \ int(is_black(l));\n        assert(rank == node_rank(r) + int(is_black(r)));\n\
    \        return pool.emplace(pool[pool[l].max_leaf].key,\n                   \
    \         subtree_size(l) + subtree_size(r),\n                            subtree_size(l),\n\
    \                            subtree_distinct_size(l) + subtree_distinct_size(r),\n\
    \                            rank, l, r, pool[l].min_leaf, pool[r].max_leaf,\n\
    \                            black);\n    }\n\n    static int as_root(int t) {\n\
    \        if (t == -1 || is_black(t)) return t;\n        return make_node(pool[t].l,\
    \ pool[t].r, true);\n    }\n\n    static int merge_sub(int a, int b) {\n     \
    \   assert(a != -1 && b != -1);\n        if (node_rank(a) < node_rank(b)) {\n\
    \            const Node& right = pool[b];\n            int c = merge_sub(a, right.l);\n\
    \            if (is_black(b) && !is_black(c) && !is_black(pool[c].l)) {\n    \
    \            const Node& middle = pool[c];\n                if (is_black(right.r))\
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
    \ compare) : root(node), comp(std::move(compare)) {}\n\n   public:\n    explicit\
    \ PersistentOrderedMultiset(Compare compare) : root(-1), comp(std::move(compare))\
    \ {}\n    PersistentOrderedMultiset() : PersistentOrderedMultiset(Compare()) {}\n\
    \n    PersistentOrderedMultiset(std::initializer_list<T> init, Compare compare\
    \ = Compare())\n        : PersistentOrderedMultiset(std::move(compare)) {\n  \
    \      for (const T& x : init) *this = insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator last, Compare\
    \ compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) *this = insert(*first++);\n    }\n\n    int\
    \ size() const { return subtree_size(root); }\n    int unique_size() const { return\
    \ subtree_distinct_size(root); }\n    bool empty() const { return root == -1;\
    \ }\n    PersistentOrderedMultiset clear() const { return PersistentOrderedMultiset(-1,\
    \ comp); }\n\n    PersistentOrderedMultiset insert(T key, int multiplicity = 1)\
    \ const {\n        assert(multiplicity > 0);\n        int old_count = 0;\n   \
    \     const int changed_root = change_count_impl(root, key, multiplicity, old_count);\n\
    \        if (old_count != 0) {\n            return PersistentOrderedMultiset(changed_root,\
    \ comp);\n        }\n        auto [l, r] = split_nodes(root, key);\n        return\
    \ PersistentOrderedMultiset(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ multiplicity)), r), comp);\n    }\n\n   private:\n    PersistentOrderedMultiset\
    \ insert_unique(T key) const {\n        if (contains(key)) return *this;\n   \
    \     auto [l, r] = split_nodes(root, key);\n        return PersistentOrderedMultiset(\n\
    \            merge_nodes(merge_nodes(l, make_leaf(std::move(key), 1)), r), comp);\n\
    \    }\n\n   public:\n    PersistentOrderedMultiset erase_one(const T& key) const\
    \ {\n        int old_count = 0;\n        const int changed_root = change_count_impl(root,\
    \ key, -1, old_count);\n        if (old_count == 0) return *this;\n        if\
    \ (old_count > 1) return PersistentOrderedMultiset(changed_root, comp);\n    \
    \    auto [l, r] = split_nodes(root, key);\n        auto [discarded, rest] = pop_min(r);\n\
    \        assert(equal(pool[discarded].key, key));\n        return PersistentOrderedMultiset(merge_nodes(l,\
    \ rest), comp);\n    }\n\n    PersistentOrderedMultiset erase(const T& key) const\
    \ { return erase_one(key); }\n\n    PersistentOrderedMultiset erase_all(const\
    \ T& key) const {\n        const int old_count = count(key);\n        if (old_count\
    \ == 0) return *this;\n        auto [l, r] = split_nodes(root, key);\n       \
    \ auto [discarded, rest] = pop_min(r);\n        assert(equal(pool[discarded].key,\
    \ key));\n        return PersistentOrderedMultiset(merge_nodes(l, rest), comp);\n\
    \    }\n\n    bool contains(const T& key) const { return count(key) > 0; }\n \
    \   int count(const T& key) const { return count_impl(root, key); }\n\n    const\
    \ T* find_by_order(int k) const {\n        assert(0 <= k && k < size());\n   \
    \     return kth_impl(root, k);\n    }\n\n    T kth(int k) const { return *find_by_order(k);\
    \ }\n    int order_of_key(const T& key) const { return order_of_key_impl(root,\
    \ key, false); }\n    int count_less(const T& key) const { return order_of_key(key);\
    \ }\n    int count_less_equal(const T& key) const { return order_of_key_impl(root,\
    \ key, true); }\n    int count_greater(const T& key) const { return size() - count_less_equal(key);\
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
    \ T& key) const {\n        auto [l, r] = split_nodes(root, key);\n        return\
    \ {PersistentOrderedMultiset(l, comp), PersistentOrderedMultiset(r, comp)};\n\
    \    }\n\n    PersistentOrderedMultiset merge(const PersistentOrderedMultiset&\
    \ other) const {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        return PersistentOrderedMultiset(merge_nodes(root, other.root), comp);\n\
    \    }\n\n    std::vector<T> to_vector() const {\n        std::vector<T> result;\n\
    \        result.reserve(size());\n        dump_impl(root, result);\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_PERSISTENT_ORDERED_MULTISET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/bst/persistent_ordered_multiset.hpp
  requiredBy:
  - ds/bst/persistent_ordered_set.hpp
  timestamp: '2026-07-12 04:52:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/persistent_ordered_multiset.test.cpp
  - verify/ds/bst/persistent_ordered_set.test.cpp
documentation_of: ds/bst/persistent_ordered_multiset.hpp
layout: document
title: Persistent Ordered Multiset
---

## Overview

`PersistentOrderedMultiset` is a path-copying red-black tree for multisets.
Updates, splits, and merges return new versions and leave every input version
available. Equal keys are stored as one leaf with a multiplicity.

Nodes are stored in a specialization-wide append-only chunked pool and refer to
children by integer index. This avoids per-node allocation and reference-counted
child pointers. The pool is released when the program exits.

Pointers returned by bound and predecessor/successor methods remain valid for
the remainder of the program.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

Trees passed to `merge` must use equivalent comparator state.

## Constructors

* `PersistentOrderedMultiset()`
  Constructs an empty multiset. ($O(1)$)

* `PersistentOrderedMultiset(Compare compare)`
  Constructs an empty multiset with a custom comparator. ($O(1)$)

* `PersistentOrderedMultiset(std::initializer_list<T> init)`
  Constructs a multiset from an initializer list. ($O(N \log N)$)

* `PersistentOrderedMultiset(Iterator first, Iterator last)`
  Constructs a multiset from a range. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the total number of elements, including duplicates. | $O(1)$ |
| `int unique_size() const` | Returns the number of distinct keys. | $O(1)$ |
| `bool empty() const` | Returns whether the multiset is empty. | $O(1)$ |
| `PersistentOrderedMultiset clear() const` | Returns an empty multiset with the same comparator. | $O(1)$ |
| `PersistentOrderedMultiset insert(T key, int multiplicity = 1) const` | Returns a new multiset with `multiplicity` copies of `key` inserted. | $O(\log N)$ |
| `PersistentOrderedMultiset erase_one(const T& key) const` | Returns a new multiset with one copy of `key` removed if it exists. | $O(\log N)$ |
| `PersistentOrderedMultiset erase(const T& key) const` | Alias for `erase_one(key)`. | $O(\log N)$ |
| `PersistentOrderedMultiset erase_all(const T& key) const` | Returns a new multiset with all copies of `key` removed if it exists. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns the multiplicity of `key`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest element. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest element by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of elements strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of elements less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of elements strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of elements greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest element greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest element strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest element less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest element strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum element, or `nullptr` if the multiset is empty. | $O(1)$ |
| `std::pair<PersistentOrderedMultiset, PersistentOrderedMultiset> split(const T& key) const` | Returns `{less, greater_equal}` without changing this version. | $O(\log N)$ |
| `PersistentOrderedMultiset merge(const PersistentOrderedMultiset& other) const` | Returns the union without changing either version. Requires every key in `*this` to be smaller than every key in `other`. | $O(\log(N + M))$ |
| `std::vector<T> to_vector() const` | Returns all elements in sorted order, including duplicates. | $O(N)$ |

## Example

```cpp
#include "ds/bst/persistent_ordered_multiset.hpp"

#include <iostream>

int main() {
    m1une::ds::PersistentOrderedMultiset<int> a;
    auto b = a.insert(3).insert(1).insert(3);
    auto c = b.erase_one(3);
    auto [small, large] = b.split(3);
    auto joined = small.merge(large);

    std::cout << a.size() << "\n";  // 0
    std::cout << b.count(3) << "\n";  // 2
    std::cout << c.count(3) << "\n";  // 1
}
```
