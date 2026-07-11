---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_set.hpp
    title: Persistent Ordered Set
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"verify/ds/bst/persistent_ordered_set.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#line 1 \"ds/bst/persistent_ordered_set.hpp\"\
    \n\n\n\n#include <functional>\n#include <initializer_list>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"ds/bst/persistent_ordered_multiset.hpp\"\n\n\n\n\
    #include <cassert>\n#line 9 \"ds/bst/persistent_ordered_multiset.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\n\
    struct PersistentOrderedMultiset {\n   private:\n    struct Node {\n        T\
    \ key;\n        int count;\n        int size;\n        int distinct_size;\n  \
    \      int rank;\n        int l;\n        int r;\n        bool black;\n      \
    \  bool leaf;\n\n        Node(T value, int multiplicity)\n            : key(std::move(value)),\n\
    \              count(multiplicity),\n              size(multiplicity),\n     \
    \         distinct_size(1),\n              rank(0),\n              l(-1),\n  \
    \            r(-1),\n              black(true),\n              leaf(true) {}\n\
    \n        Node(T separator, int subtree_size, int unique_count, int node_rank,\n\
    \             int left, int right, bool is_black)\n            : key(std::move(separator)),\n\
    \              count(0),\n              size(subtree_size),\n              distinct_size(unique_count),\n\
    \              rank(node_rank),\n              l(left),\n              r(right),\n\
    \              black(is_black),\n              leaf(false) {}\n    };\n\n    static\
    \ constexpr int pool_block_bits = 16;\n    static constexpr int pool_block_size\
    \ = 1 << pool_block_bits;\n    static constexpr int pool_block_mask = pool_block_size\
    \ - 1;\n\n    struct Pool {\n        std::vector<std::vector<Node>> blocks;\n\
    \        int node_count = 0;\n\n        const Node& operator[](int index) const\
    \ {\n            return blocks[index >> pool_block_bits][index & pool_block_mask];\n\
    \        }\n\n        template <class... Args>\n        int emplace(Args&&...\
    \ args) {\n            if ((node_count & pool_block_mask) == 0) {\n          \
    \      blocks.emplace_back();\n                blocks.back().reserve(pool_block_size);\n\
    \            }\n            blocks.back().emplace_back(std::forward<Args>(args)...);\n\
    \            return node_count++;\n        }\n    };\n\n    inline static Pool\
    \ pool;\n\n    int root;\n    Compare comp;\n\n    static int subtree_size(int\
    \ t) { return t == -1 ? 0 : pool[t].size; }\n    static int subtree_distinct_size(int\
    \ t) { return t == -1 ? 0 : pool[t].distinct_size; }\n\n    bool equal(const T&\
    \ a, const T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\n\
    \    static int make_leaf(T key, int count) {\n        return pool.emplace(std::move(key),\
    \ count);\n    }\n\n    static int make_node(int l, int r, bool black) {\n   \
    \     assert(l != -1 && r != -1);\n        const int rank = pool[l].rank + int(pool[l].black);\n\
    \        assert(rank == pool[r].rank + int(pool[r].black));\n        return pool.emplace(pool[r].key,\n\
    \                            subtree_size(l) + subtree_size(r),\n            \
    \                subtree_distinct_size(l) + subtree_distinct_size(r),\n      \
    \                      rank, l, r, black);\n    }\n\n    static int as_root(int\
    \ t) {\n        if (t == -1 || pool[t].black) return t;\n        return make_node(pool[t].l,\
    \ pool[t].r, true);\n    }\n\n    static int merge_sub(int a, int b) {\n     \
    \   assert(a != -1 && b != -1);\n        if (pool[a].rank < pool[b].rank) {\n\
    \            const Node& right = pool[b];\n            int c = merge_sub(a, right.l);\n\
    \            if (right.black && !pool[c].black && !pool[pool[c].l].black) {\n\
    \                const Node& middle = pool[c];\n                if (pool[right.r].black)\
    \ {\n                    return make_node(middle.l,\n                        \
    \             make_node(middle.r, right.r, false),\n                         \
    \            true);\n                }\n                const Node& far = pool[right.r];\n\
    \                return make_node(make_node(middle.l, middle.r, true),\n     \
    \                            make_node(far.l, far.r, true),\n                \
    \                 false);\n            }\n            return make_node(c, right.r,\
    \ right.black);\n        }\n        if (pool[a].rank > pool[b].rank) {\n     \
    \       const Node& left = pool[a];\n            int c = merge_sub(left.r, b);\n\
    \            if (left.black && !pool[c].black && !pool[pool[c].r].black) {\n \
    \               const Node& middle = pool[c];\n                if (pool[left.l].black)\
    \ {\n                    return make_node(make_node(left.l, middle.l, false),\n\
    \                                     middle.r, true);\n                }\n  \
    \              const Node& far = pool[left.l];\n                return make_node(make_node(far.l,\
    \ far.r, true),\n                                 make_node(middle.l, middle.r,\
    \ true),\n                                 false);\n            }\n          \
    \  return make_node(left.l, c, left.black);\n        }\n        return make_node(a,\
    \ b, false);\n    }\n\n    static int merge_nodes(int a, int b) {\n        if\
    \ (a == -1 || b == -1) return a == -1 ? b : a;\n        return as_root(merge_sub(as_root(a),\
    \ as_root(b)));\n    }\n\n    std::pair<int, int> split_nodes(int t, const T&\
    \ key) const {\n        if (t == -1) return {-1, -1};\n        const Node& node\
    \ = pool[t];\n        if (node.leaf) return comp(node.key, key) ? std::pair{t,\
    \ -1} : std::pair{-1, t};\n        if (comp(pool[node.l].key, key)) {\n      \
    \      auto [l, r] = split_nodes(node.r, key);\n            return {merge_nodes(as_root(node.l),\
    \ l), r};\n        }\n        auto [l, r] = split_nodes(node.l, key);\n      \
    \  return {l, merge_nodes(r, as_root(node.r))};\n    }\n\n    int set_count_impl(int\
    \ t, const T& key, int count) const {\n        const Node& node = pool[t];\n \
    \       if (node.leaf) {\n            assert(equal(node.key, key));\n        \
    \    return make_leaf(node.key, count);\n        }\n        if (!comp(pool[node.l].key,\
    \ key)) {\n            return make_node(set_count_impl(node.l, key, count), node.r,\
    \ node.black);\n        }\n        return make_node(node.l, set_count_impl(node.r,\
    \ key, count), node.black);\n    }\n\n    int count_impl(int t, const T& key)\
    \ const {\n        if (t == -1) return 0;\n        while (!pool[t].leaf) {\n \
    \           t = !comp(pool[pool[t].l].key, key) ? pool[t].l : pool[t].r;\n   \
    \     }\n        return equal(pool[t].key, key) ? pool[t].count : 0;\n    }\n\n\
    \    const T* kth_impl(int t, int k) const {\n        while (!pool[t].leaf) {\n\
    \            const int left_size = subtree_size(pool[t].l);\n            if (k\
    \ < left_size) {\n                t = pool[t].l;\n            } else {\n     \
    \           k -= left_size;\n                t = pool[t].r;\n            }\n \
    \       }\n        return &pool[t].key;\n    }\n\n    int order_of_key_impl(int\
    \ t, const T& key, bool upper) const {\n        int result = 0;\n        while\
    \ (t != -1 && !pool[t].leaf) {\n            const Node& node = pool[t];\n    \
    \        const T& separator = pool[node.l].key;\n            const bool take_left\
    \ = upper ? !comp(key, separator) : comp(separator, key);\n            if (take_left)\
    \ {\n                result += subtree_size(node.l);\n                t = node.r;\n\
    \            } else {\n                t = node.l;\n            }\n        }\n\
    \        if (t != -1) {\n            const bool take_leaf = upper ? !comp(key,\
    \ pool[t].key) : comp(pool[t].key, key);\n            if (take_leaf) result +=\
    \ pool[t].count;\n        }\n        return result;\n    }\n\n    const T* lower_bound_impl(int\
    \ t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != -1) {\n            const Node& node = pool[t];\n        \
    \    if (node.leaf) {\n                const bool candidate = strict ? comp(key,\
    \ node.key) : !comp(node.key, key);\n                return candidate ? &node.key\
    \ : result;\n            }\n            const T& separator = pool[node.l].key;\n\
    \            const bool go_left = strict ? comp(key, separator) : !comp(separator,\
    \ key);\n            if (go_left) {\n                int candidate = node.r;\n\
    \                while (!pool[candidate].leaf) candidate = pool[candidate].l;\n\
    \                result = &pool[candidate].key;\n                t = node.l;\n\
    \            } else {\n                t = node.r;\n            }\n        }\n\
    \        return result;\n    }\n\n    const T* max_less_impl(int t, const T& key,\
    \ bool strict) const {\n        const T* result = nullptr;\n        while (t !=\
    \ -1) {\n            const Node& node = pool[t];\n            if (node.leaf) {\n\
    \                const bool candidate = strict ? comp(node.key, key) : !comp(key,\
    \ node.key);\n                return candidate ? &node.key : result;\n       \
    \     }\n            const T& separator = pool[node.l].key;\n            const\
    \ bool take_left = strict ? comp(separator, key) : !comp(key, separator);\n  \
    \          if (take_left) {\n                result = &separator;\n          \
    \      t = node.r;\n            } else {\n                t = node.l;\n      \
    \      }\n        }\n        return result;\n    }\n\n    static void dump_impl(int\
    \ t, std::vector<T>& result) {\n        if (t == -1) return;\n        const Node&\
    \ node = pool[t];\n        if (node.leaf) {\n            for (int i = 0; i < node.count;\
    \ ++i) result.push_back(node.key);\n            return;\n        }\n        dump_impl(node.l,\
    \ result);\n        dump_impl(node.r, result);\n    }\n\n    static std::pair<int,\
    \ int> pop_min(int t) {\n        assert(t != -1);\n        const Node& node =\
    \ pool[t];\n        if (node.leaf) return {t, -1};\n        auto [minimum, rest]\
    \ = pop_min(node.l);\n        return {minimum, merge_nodes(rest, as_root(node.r))};\n\
    \    }\n\n    PersistentOrderedMultiset(int node, Compare compare) : root(node),\
    \ comp(std::move(compare)) {}\n\n   public:\n    explicit PersistentOrderedMultiset(Compare\
    \ compare) : root(-1), comp(std::move(compare)) {}\n    PersistentOrderedMultiset()\
    \ : PersistentOrderedMultiset(Compare()) {}\n\n    PersistentOrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        for (const T& x : init) *this = insert(x);\n    }\n\n    template\
    \ <typename Iterator>\n    PersistentOrderedMultiset(Iterator first, Iterator\
    \ last, Compare compare = Compare())\n        : PersistentOrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) *this = insert(*first++);\n    }\n\n    int\
    \ size() const { return subtree_size(root); }\n    int unique_size() const { return\
    \ subtree_distinct_size(root); }\n    bool empty() const { return root == -1;\
    \ }\n    PersistentOrderedMultiset clear() const { return PersistentOrderedMultiset(-1,\
    \ comp); }\n\n    PersistentOrderedMultiset insert(T key, int multiplicity = 1)\
    \ const {\n        assert(multiplicity > 0);\n        const int old_count = count(key);\n\
    \        if (old_count != 0) {\n            return PersistentOrderedMultiset(set_count_impl(root,\
    \ key, old_count + multiplicity), comp);\n        }\n        auto [l, r] = split_nodes(root,\
    \ key);\n        return PersistentOrderedMultiset(merge_nodes(merge_nodes(l, make_leaf(std::move(key),\
    \ multiplicity)), r), comp);\n    }\n\n    PersistentOrderedMultiset erase_one(const\
    \ T& key) const {\n        const int old_count = count(key);\n        if (old_count\
    \ == 0) return *this;\n        if (old_count > 1) return PersistentOrderedMultiset(set_count_impl(root,\
    \ key, old_count - 1), comp);\n        auto [l, r] = split_nodes(root, key);\n\
    \        auto [discarded, rest] = pop_min(r);\n        assert(equal(pool[discarded].key,\
    \ key));\n        return PersistentOrderedMultiset(merge_nodes(l, rest), comp);\n\
    \    }\n\n    PersistentOrderedMultiset erase(const T& key) const { return erase_one(key);\
    \ }\n\n    PersistentOrderedMultiset erase_all(const T& key) const {\n       \
    \ const int old_count = count(key);\n        if (old_count == 0) return *this;\n\
    \        PersistentOrderedMultiset result = *this;\n        if (old_count > 1)\
    \ result = PersistentOrderedMultiset(set_count_impl(root, key, 1), comp);\n  \
    \      return result.erase_one(key);\n    }\n\n    bool contains(const T& key)\
    \ const { return count(key) > 0; }\n    int count(const T& key) const { return\
    \ count_impl(root, key); }\n\n    const T* find_by_order(int k) const {\n    \
    \    assert(0 <= k && k < size());\n        return kth_impl(root, k);\n    }\n\
    \n    T kth(int k) const { return *find_by_order(k); }\n    int order_of_key(const\
    \ T& key) const { return order_of_key_impl(root, key, false); }\n    int count_less(const\
    \ T& key) const { return order_of_key(key); }\n    int count_less_equal(const\
    \ T& key) const { return order_of_key_impl(root, key, true); }\n    int count_greater(const\
    \ T& key) const { return size() - count_less_equal(key); }\n    int count_greater_equal(const\
    \ T& key) const { return size() - count_less(key); }\n    const T* lower_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, false); }\n    const T* upper_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, true); }\n    const T* min_ge(const\
    \ T& key) const { return lower_bound(key); }\n    const T* min_gt(const T& key)\
    \ const { return upper_bound(key); }\n    const T* max_le(const T& key) const\
    \ { return max_less_impl(root, key, false); }\n    const T* max_lt(const T& key)\
    \ const { return max_less_impl(root, key, true); }\n    const T* min() const {\
    \ return empty() ? nullptr : kth_impl(root, 0); }\n    const T* max() const {\
    \ return empty() ? nullptr : &pool[root].key; }\n\n    std::pair<PersistentOrderedMultiset,\
    \ PersistentOrderedMultiset> split(const T& key) const {\n        auto [l, r]\
    \ = split_nodes(root, key);\n        return {PersistentOrderedMultiset(l, comp),\
    \ PersistentOrderedMultiset(r, comp)};\n    }\n\n    PersistentOrderedMultiset\
    \ merge(const PersistentOrderedMultiset& other) const {\n        assert(empty()\
    \ || other.empty() || comp(*max(), *other.min()));\n        return PersistentOrderedMultiset(merge_nodes(root,\
    \ other.root), comp);\n    }\n\n    std::vector<T> to_vector() const {\n     \
    \   std::vector<T> result;\n        result.reserve(size());\n        dump_impl(root,\
    \ result);\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 10 \"ds/bst/persistent_ordered_set.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\n\
    struct PersistentOrderedSet {\n   private:\n    using Multiset = PersistentOrderedMultiset<T,\
    \ Compare>;\n\n    Multiset data;\n\n    explicit PersistentOrderedSet(Multiset\
    \ multiset) : data(std::move(multiset)) {}\n\n   public:\n    explicit PersistentOrderedSet(Compare\
    \ compare) : data(std::move(compare)) {}\n\n    PersistentOrderedSet() : PersistentOrderedSet(Compare())\
    \ {}\n\n    PersistentOrderedSet(std::initializer_list<T> init, Compare compare\
    \ = Compare())\n        : PersistentOrderedSet(std::move(compare)) {\n       \
    \ for (const T& x : init) *this = insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    PersistentOrderedSet(Iterator first, Iterator last, Compare compare\
    \ = Compare())\n        : PersistentOrderedSet(std::move(compare)) {\n       \
    \ while (first != last) {\n            *this = insert(*first);\n            ++first;\n\
    \        }\n    }\n\n    int size() const {\n        return data.size();\n   \
    \ }\n\n    int unique_size() const {\n        return data.size();\n    }\n\n \
    \   bool empty() const {\n        return data.empty();\n    }\n\n    PersistentOrderedSet\
    \ clear() const {\n        return PersistentOrderedSet(data.clear());\n    }\n\
    \n    PersistentOrderedSet insert(T key) const {\n        if (data.contains(key))\
    \ return *this;\n        return PersistentOrderedSet(data.insert(std::move(key)));\n\
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
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/bst/persistent_ordered_set.test.cpp\"\
    \n\n#line 6 \"verify/ds/bst/persistent_ordered_set.test.cpp\"\n#include <iostream>\n\
    \nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n\n    m1une::ds::PersistentOrderedSet<int>\
    \ pointer_test = {1, 3, 5};\n    const int* stable_pointer = pointer_test.lower_bound(3);\n\
    \    auto pointer_test_next = pointer_test;\n    for (int x = 10; x < 1000; x++)\
    \ pointer_test_next = pointer_test_next.insert(x);\n    assert(stable_pointer\
    \ && *stable_pointer == 3);\n    auto [small, large] = pointer_test_next.split(500);\n\
    \    auto joined = small.merge(large);\n    assert(pointer_test_next.size() ==\
    \ joined.size());\n    assert(pointer_test_next.to_vector() == joined.to_vector());\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n\n    m1une::ds::PersistentOrderedSet<int>\
    \ st;\n    for (int i = 0; i < N; i++) {\n        int a;\n        std::cin >>\
    \ a;\n        st = st.insert(a);\n    }\n\n    while (Q--) {\n        int type,\
    \ x;\n        std::cin >> type >> x;\n\n        if (type == 0) {\n           \
    \ st = st.insert(x);\n        } else if (type == 1) {\n            st = st.erase(x);\n\
    \        } else if (type == 2) {\n            if (st.size() < x) {\n         \
    \       std::cout << -1 << '\\n';\n            } else {\n                std::cout\
    \ << st.kth(x - 1) << '\\n';\n            }\n        } else if (type == 3) {\n\
    \            std::cout << st.count_less_equal(x) << '\\n';\n        } else if\
    \ (type == 4) {\n            const int* ans = st.max_le(x);\n            std::cout\
    \ << (ans ? *ans : -1) << '\\n';\n        } else {\n            const int* ans\
    \ = st.min_ge(x);\n            std::cout << (ans ? *ans : -1) << '\\n';\n    \
    \    }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"../../../ds/bst/persistent_ordered_set.hpp\"\n\n#include <cassert>\n#include\
    \ <iostream>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n\n    m1une::ds::PersistentOrderedSet<int>\
    \ pointer_test = {1, 3, 5};\n    const int* stable_pointer = pointer_test.lower_bound(3);\n\
    \    auto pointer_test_next = pointer_test;\n    for (int x = 10; x < 1000; x++)\
    \ pointer_test_next = pointer_test_next.insert(x);\n    assert(stable_pointer\
    \ && *stable_pointer == 3);\n    auto [small, large] = pointer_test_next.split(500);\n\
    \    auto joined = small.merge(large);\n    assert(pointer_test_next.size() ==\
    \ joined.size());\n    assert(pointer_test_next.to_vector() == joined.to_vector());\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n\n    m1une::ds::PersistentOrderedSet<int>\
    \ st;\n    for (int i = 0; i < N; i++) {\n        int a;\n        std::cin >>\
    \ a;\n        st = st.insert(a);\n    }\n\n    while (Q--) {\n        int type,\
    \ x;\n        std::cin >> type >> x;\n\n        if (type == 0) {\n           \
    \ st = st.insert(x);\n        } else if (type == 1) {\n            st = st.erase(x);\n\
    \        } else if (type == 2) {\n            if (st.size() < x) {\n         \
    \       std::cout << -1 << '\\n';\n            } else {\n                std::cout\
    \ << st.kth(x - 1) << '\\n';\n            }\n        } else if (type == 3) {\n\
    \            std::cout << st.count_less_equal(x) << '\\n';\n        } else if\
    \ (type == 4) {\n            const int* ans = st.max_le(x);\n            std::cout\
    \ << (ans ? *ans : -1) << '\\n';\n        } else {\n            const int* ans\
    \ = st.min_ge(x);\n            std::cout << (ans ? *ans : -1) << '\\n';\n    \
    \    }\n    }\n}\n"
  dependsOn:
  - ds/bst/persistent_ordered_set.hpp
  - ds/bst/persistent_ordered_multiset.hpp
  isVerificationFile: true
  path: verify/ds/bst/persistent_ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-07-12 04:39:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/persistent_ordered_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/persistent_ordered_set.test.cpp
- /verify/verify/ds/bst/persistent_ordered_set.test.cpp.html
title: verify/ds/bst/persistent_ordered_set.test.cpp
---
