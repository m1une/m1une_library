---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_add_range_sum.hpp
    title: Range Add Range Sum
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/concept.hpp
    title: Beats Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
    title: Range Chmin/Chmax/Add Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_multiset.hpp
    title: Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_set.hpp
    title: Ordered Set
  - icon: ':heavy_check_mark:'
    path: ds/bst/rollback_ordered_multiset.hpp
    title: Rollback Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: ds/bst/rollback_ordered_set.hpp
    title: Rollback Ordered Set
  - icon: ':heavy_check_mark:'
    path: ds/deque/rollback_deque.hpp
    title: Rollback Deque
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: ds/detail/rollback_journal.hpp
    title: ds/detail/rollback_journal.hpp
  - icon: ':heavy_check_mark:'
    path: ds/dsu/rollback_potentialized_dsu.hpp
    title: Rollback Potentialized DSU
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/dynamic_array.hpp
    title: Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/dynamic_monoid_array.hpp
    title: Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_array.hpp
    title: Rollback Dynamic Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
    title: Rollback Dynamic Lazy Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/dynamic_array/rollback_dynamic_monoid_array.hpp
    title: Rollback Dynamic Monoid Array
  - icon: ':heavy_check_mark:'
    path: ds/queue/rollback_queue.hpp
    title: Rollback Queue
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dual_segtree.hpp
    title: Rollback Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_dual_segtree.hpp
    title: Rollback Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_lazy_segtree.hpp
    title: Rollback Dynamic Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_dynamic_segtree.hpp
    title: Rollback Dynamic Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_lazy_segtree.hpp
    title: Rollback Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_segtree.hpp
    title: Rollback Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/rollback_segtree_beats.hpp
    title: Rollback Segment Tree Beats
  - icon: ':heavy_check_mark:'
    path: ds/stack/rollback_stack.hpp
    title: Rollback Stack
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
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
    path: monoid/concept.hpp
    title: Monoid Concept
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
  bundledCode: "#line 1 \"verify/ds/rollback_counterparts.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/bst/rollback_ordered_multiset.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/bst/ordered_multiset.hpp\"\
    \n\n\n\n#line 7 \"ds/bst/ordered_multiset.hpp\"\n#include <memory>\n#line 10 \"\
    ds/bst/ordered_multiset.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <typename T, typename Compare = std::less<T>>\nstruct OrderedMultiset {\n  \
    \ private:\n    struct Node {\n        T key;\n        int count;\n        int\
    \ size;\n        int distinct_size;\n        Node* l;\n        Node* r;\n\n  \
    \      Node(T value, int multiplicity)\n            : key(std::move(value)),\n\
    \              count(multiplicity),\n              size(multiplicity),\n     \
    \         distinct_size(1),\n              l(nullptr),\n              r(nullptr)\
    \ {}\n    };\n\n    static constexpr int pool_block_size = 1 << 14;\n\n    struct\
    \ Pool {\n        std::vector<std::vector<Node>> blocks;\n        std::vector<Node*>\
    \ free_nodes;\n\n        template <class... Args>\n        Node* emplace(Args&&...\
    \ args) {\n            if (!free_nodes.empty()) {\n                Node* result\
    \ = free_nodes.back();\n                free_nodes.pop_back();\n             \
    \   std::destroy_at(result);\n                std::construct_at(result, std::forward<Args>(args)...);\n\
    \                return result;\n            }\n            if (blocks.empty()\
    \ || int(blocks.back().size()) == pool_block_size) {\n                blocks.emplace_back();\n\
    \                blocks.back().reserve(pool_block_size);\n            }\n    \
    \        blocks.back().emplace_back(std::forward<Args>(args)...);\n          \
    \  return &blocks.back().back();\n        }\n\n        void recycle(Node* node)\
    \ {\n            free_nodes.push_back(node);\n        }\n    };\n\n    inline\
    \ static Pool pool;\n\n    Node* root;\n    Compare comp;\n\n    static int subtree_size(const\
    \ Node* t) {\n        return t == nullptr ? 0 : t->size;\n    }\n\n    static\
    \ int subtree_distinct_size(const Node* t) {\n        return t == nullptr ? 0\
    \ : t->distinct_size;\n    }\n\n    bool equal(const T& a, const T& b) const {\n\
    \        return !comp(a, b) && !comp(b, a);\n    }\n\n    Node* new_node(T key,\
    \ int multiplicity) {\n        return pool.emplace(std::move(key), multiplicity);\n\
    \    }\n\n    static void update(Node* t) {\n        t->size = t->count + subtree_size(t->l)\
    \ + subtree_size(t->r);\n        t->distinct_size = 1 + subtree_distinct_size(t->l)\
    \ + subtree_distinct_size(t->r);\n    }\n\n    static Node* rotate_right(Node*\
    \ t) {\n        Node* s = t->l;\n        t->l = s->r;\n        s->r = t;\n   \
    \     update(t);\n        update(s);\n        return s;\n    }\n\n    static Node*\
    \ rotate_left(Node* t) {\n        Node* s = t->r;\n        t->r = s->l;\n    \
    \    s->l = t;\n        update(t);\n        update(s);\n        return s;\n  \
    \  }\n\n    static Node* balance(Node* t) {\n        if (t == nullptr) return\
    \ nullptr;\n        const int left_size = subtree_distinct_size(t->l);\n     \
    \   const int right_size = subtree_distinct_size(t->r);\n        if (left_size\
    \ + right_size > 1 && left_size > 3LL * right_size) {\n            if (subtree_distinct_size(t->l->r)\
    \ >= 2LL * subtree_distinct_size(t->l->l)) {\n                t->l = rotate_left(t->l);\n\
    \            }\n            return rotate_right(t);\n        }\n        if (left_size\
    \ + right_size > 1 && right_size > 3LL * left_size) {\n            if (subtree_distinct_size(t->r->l)\
    \ >= 2LL * subtree_distinct_size(t->r->r)) {\n                t->r = rotate_right(t->r);\n\
    \            }\n            return rotate_left(t);\n        }\n        update(t);\n\
    \        return t;\n    }\n\n    static Node* join_with_root(Node* l, Node* middle,\
    \ Node* r) {\n        const int left_size = subtree_distinct_size(l);\n      \
    \  const int right_size = subtree_distinct_size(r);\n        if (left_size > 3LL\
    \ * (right_size + 1)) {\n            l->r = join_with_root(l->r, middle, r);\n\
    \            return balance(l);\n        }\n        if (right_size > 3LL * (left_size\
    \ + 1)) {\n            r->l = join_with_root(l, middle, r->l);\n            return\
    \ balance(r);\n        }\n        middle->l = l;\n        middle->r = r;\n   \
    \     return balance(middle);\n    }\n\n    static Node* detach_max(Node* t, Node*&\
    \ maximum) {\n        if (t->r == nullptr) {\n            maximum = t;\n     \
    \       return t->l;\n        }\n        t->r = detach_max(t->r, maximum);\n \
    \       return balance(t);\n    }\n\n    static Node* merge_nodes(Node* l, Node*\
    \ r) {\n        if (l == nullptr || r == nullptr) return l == nullptr ? r : l;\n\
    \        Node* middle;\n        l = detach_max(l, middle);\n        return join_with_root(l,\
    \ middle, r);\n    }\n\n    std::pair<Node*, Node*> split_nodes(Node* t, const\
    \ T& key) {\n        if (t == nullptr) return {nullptr, nullptr};\n        Node*\
    \ left = t->l;\n        Node* right = t->r;\n        t->l = nullptr;\n       \
    \ t->r = nullptr;\n        if (comp(t->key, key)) {\n            auto [l, r] =\
    \ split_nodes(right, key);\n            return {join_with_root(left, t, l), r};\n\
    \        }\n        auto [l, r] = split_nodes(left, key);\n        return {l,\
    \ join_with_root(r, t, right)};\n    }\n\n    Node* insert_impl(Node* t, T& key,\
    \ int multiplicity, bool& new_key) {\n        if (t == nullptr) {\n          \
    \  new_key = true;\n            return new_node(std::move(key), multiplicity);\n\
    \        }\n        if (comp(key, t->key)) {\n            t->l = insert_impl(t->l,\
    \ key, multiplicity, new_key);\n        } else if (comp(t->key, key)) {\n    \
    \        t->r = insert_impl(t->r, key, multiplicity, new_key);\n        } else\
    \ {\n            t->count += multiplicity;\n            t->size += multiplicity;\n\
    \            new_key = false;\n            return t;\n        }\n        if (!new_key)\
    \ {\n            t->size += multiplicity;\n            return t;\n        }\n\
    \        return balance(t);\n    }\n\n    Node* erase_impl(Node* t, const T& key,\
    \ bool erase_all,\n                     int& erased, bool& removed_key) {\n  \
    \      if (t == nullptr) return nullptr;\n        if (comp(key, t->key)) {\n \
    \           t->l = erase_impl(t->l, key, erase_all, erased, removed_key);\n  \
    \      } else if (comp(t->key, key)) {\n            t->r = erase_impl(t->r, key,\
    \ erase_all, erased, removed_key);\n        } else if (!erase_all && t->count\
    \ > 1) {\n            --t->count;\n            --t->size;\n            erased\
    \ = 1;\n            removed_key = false;\n            return t;\n        } else\
    \ {\n            erased = t->count;\n            removed_key = true;\n       \
    \     Node* l = t->l;\n            Node* r = t->r;\n            pool.recycle(t);\n\
    \            return merge_nodes(l, r);\n        }\n        if (erased == 0) return\
    \ t;\n        if (!removed_key) {\n            t->size -= erased;\n          \
    \  return t;\n        }\n        return balance(t);\n    }\n\n    static const\
    \ T* kth_impl(const Node* t, int k) {\n        while (t != nullptr) {\n      \
    \      const int left_size = subtree_size(t->l);\n            if (k < left_size)\
    \ {\n                t = t->l;\n            } else if (k < left_size + t->count)\
    \ {\n                return &t->key;\n            } else {\n                k\
    \ -= left_size + t->count;\n                t = t->r;\n            }\n       \
    \ }\n        return nullptr;\n    }\n\n    int count_impl(const Node* t, const\
    \ T& key) const {\n        while (t != nullptr) {\n            if (comp(key, t->key))\
    \ {\n                t = t->l;\n            } else if (comp(t->key, key)) {\n\
    \                t = t->r;\n            } else {\n                return t->count;\n\
    \            }\n        }\n        return 0;\n    }\n\n    int order_of_key_impl(const\
    \ Node* t, const T& key, bool upper) const {\n        int result = 0;\n      \
    \  while (t != nullptr) {\n            const bool take = upper ? !comp(key, t->key)\
    \ : comp(t->key, key);\n            if (take) {\n                result += subtree_size(t->l)\
    \ + t->count;\n                t = t->r;\n            } else {\n             \
    \   t = t->l;\n            }\n        }\n        return result;\n    }\n\n   \
    \ const T* lower_bound_impl(const Node* t, const T& key, bool strict) const {\n\
    \        const T* result = nullptr;\n        while (t != nullptr) {\n        \
    \    const bool candidate = strict ? comp(key, t->key) : !comp(t->key, key);\n\
    \            if (candidate) {\n                result = &t->key;\n           \
    \     t = t->l;\n            } else {\n                t = t->r;\n           \
    \ }\n        }\n        return result;\n    }\n\n    const T* max_less_impl(const\
    \ Node* t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != nullptr) {\n            const bool candidate = strict ? comp(t->key,\
    \ key) : !comp(key, t->key);\n            if (candidate) {\n                result\
    \ = &t->key;\n                t = t->r;\n            } else {\n              \
    \  t = t->l;\n            }\n        }\n        return result;\n    }\n\n    static\
    \ void dump_impl(const Node* t, std::vector<T>& result) {\n        if (t == nullptr)\
    \ return;\n        dump_impl(t->l, result);\n        for (int i = 0; i < t->count;\
    \ ++i) result.push_back(t->key);\n        dump_impl(t->r, result);\n    }\n\n\
    \    static void recycle_impl(Node* t) {\n        if (t == nullptr) return;\n\
    \        recycle_impl(t->l);\n        recycle_impl(t->r);\n        pool.recycle(t);\n\
    \    }\n\n    Node* clone_impl(const Node* t) {\n        if (t == nullptr) return\
    \ nullptr;\n        Node* result = new_node(t->key, t->count);\n        result->l\
    \ = clone_impl(t->l);\n        result->r = clone_impl(t->r);\n        update(result);\n\
    \        return result;\n    }\n\n    OrderedMultiset(Node* node, Compare compare)\
    \ : root(node), comp(std::move(compare)) {}\n\n   public:\n    explicit OrderedMultiset(Compare\
    \ compare) : root(nullptr), comp(std::move(compare)) {}\n    OrderedMultiset()\
    \ : OrderedMultiset(Compare()) {}\n\n    OrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare())\n        : OrderedMultiset(std::move(compare))\
    \ {\n        for (const T& x : init) insert(x);\n    }\n\n    template <typename\
    \ Iterator>\n    OrderedMultiset(Iterator first, Iterator last, Compare compare\
    \ = Compare())\n        : OrderedMultiset(std::move(compare)) {\n        while\
    \ (first != last) insert(*first++);\n    }\n\n    OrderedMultiset(const OrderedMultiset&\
    \ other) : root(nullptr), comp(other.comp) {\n        root = clone_impl(other.root);\n\
    \    }\n\n    OrderedMultiset(OrderedMultiset&& other) noexcept\n        : root(std::exchange(other.root,\
    \ nullptr)), comp(std::move(other.comp)) {}\n\n    ~OrderedMultiset() {\n    \
    \    recycle_impl(root);\n    }\n\n    OrderedMultiset& operator=(OrderedMultiset\
    \ other) {\n        swap(other);\n        return *this;\n    }\n\n    void swap(OrderedMultiset&\
    \ other) noexcept {\n        using std::swap;\n        swap(root, other.root);\n\
    \        swap(comp, other.comp);\n    }\n\n    int size() const { return subtree_size(root);\
    \ }\n    int unique_size() const { return subtree_distinct_size(root); }\n   \
    \ bool empty() const { return root == nullptr; }\n\n    void clear() {\n     \
    \   recycle_impl(root);\n        root = nullptr;\n    }\n\n    void insert(T key,\
    \ int multiplicity = 1) {\n        assert(multiplicity > 0);\n        bool new_key\
    \ = false;\n        root = insert_impl(root, key, multiplicity, new_key);\n  \
    \  }\n\n    bool erase_one(const T& key) {\n        int erased = 0;\n        bool\
    \ removed_key = false;\n        root = erase_impl(root, key, false, erased, removed_key);\n\
    \        return erased != 0;\n    }\n\n    bool erase(const T& key) { return erase_one(key);\
    \ }\n\n    int erase_all(const T& key) {\n        int erased = 0;\n        bool\
    \ removed_key = false;\n        root = erase_impl(root, key, true, erased, removed_key);\n\
    \        return erased;\n    }\n\n    bool contains(const T& key) const { return\
    \ count(key) > 0; }\n    int count(const T& key) const { return count_impl(root,\
    \ key); }\n\n    const T* find_by_order(int k) const {\n        assert(0 <= k\
    \ && k < size());\n        return kth_impl(root, k);\n    }\n\n    T kth(int k)\
    \ const { return *find_by_order(k); }\n    int order_of_key(const T& key) const\
    \ { return order_of_key_impl(root, key, false); }\n    int count_less(const T&\
    \ key) const { return order_of_key(key); }\n    int count_less_equal(const T&\
    \ key) const { return order_of_key_impl(root, key, true); }\n    int count_greater(const\
    \ T& key) const { return size() - count_less_equal(key); }\n    int count_greater_equal(const\
    \ T& key) const { return size() - count_less(key); }\n    const T* lower_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, false); }\n    const T* upper_bound(const\
    \ T& key) const { return lower_bound_impl(root, key, true); }\n    const T* min_ge(const\
    \ T& key) const { return lower_bound(key); }\n    const T* min_gt(const T& key)\
    \ const { return upper_bound(key); }\n    const T* max_le(const T& key) const\
    \ { return max_less_impl(root, key, false); }\n    const T* max_lt(const T& key)\
    \ const { return max_less_impl(root, key, true); }\n    const T* min() const {\
    \ return empty() ? nullptr : kth_impl(root, 0); }\n    const T* max() const {\
    \ return empty() ? nullptr : kth_impl(root, size() - 1); }\n\n    std::pair<OrderedMultiset,\
    \ OrderedMultiset> split(const T& key) && {\n        auto [l, r] = split_nodes(root,\
    \ key);\n        root = nullptr;\n        return {OrderedMultiset(l, comp), OrderedMultiset(r,\
    \ std::move(comp))};\n    }\n\n    OrderedMultiset merge(OrderedMultiset other)\
    \ && {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        root = merge_nodes(root, other.root);\n        other.root = nullptr;\n\
    \        return std::move(*this);\n    }\n\n    std::vector<T> to_vector() const\
    \ {\n        std::vector<T> result;\n        result.reserve(size());\n       \
    \ dump_impl(root, result);\n        return result;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 12 \"ds/bst/rollback_ordered_multiset.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T, class Compare = std::less<T>>\n\
    struct RollbackOrderedMultiset {\n   private:\n    enum class Kind { key, clear,\
    \ merge };\n    struct Entry {\n        Kind kind;\n        std::optional<T> key;\n\
    \        int old_count;\n        std::vector<T> values;\n    };\n\n    OrderedMultiset<T,\
    \ Compare> _data;\n    std::vector<Entry> _history;\n    std::vector<std::size_t>\
    \ _checkpoints;\n\n    void restore_count(const T& key, int count) {\n       \
    \ _data.erase_all(key);\n        if (count > 0) _data.insert(key, count);\n  \
    \  }\n\n   public:\n    explicit RollbackOrderedMultiset(Compare compare)\n  \
    \      : _data(std::move(compare)) {}\n    RollbackOrderedMultiset() = default;\n\
    \n    RollbackOrderedMultiset(\n        std::initializer_list<T> init,\n     \
    \   Compare compare = Compare()\n    ) : _data(init, std::move(compare)) {}\n\n\
    \    template <class Iterator>\n    RollbackOrderedMultiset(\n        Iterator\
    \ first,\n        Iterator last,\n        Compare compare = Compare()\n    ) :\
    \ _data(first, last, std::move(compare)) {}\n\n    int size() const { return _data.size();\
    \ }\n    int unique_size() const { return _data.unique_size(); }\n    bool empty()\
    \ const { return _data.empty(); }\n    std::size_t node_count() const { return\
    \ std::size_t(unique_size()); }\n\n    void clear() {\n        if (_checkpoints.empty())\
    \ {\n            _data.clear();\n            return;\n        }\n        Entry\
    \ entry{Kind::clear, std::nullopt, 0, {}};\n        entry.values = _data.to_vector();\n\
    \        _data.clear();\n        _history.push_back(std::move(entry));\n    }\n\
    \n    void insert(T key, int multiplicity = 1) {\n        assert(multiplicity\
    \ > 0);\n        if (_checkpoints.empty()) {\n            _data.insert(std::move(key),\
    \ multiplicity);\n            return;\n        }\n        Entry entry{Kind::key,\
    \ std::optional<T>(key), _data.count(key), {}};\n        _data.insert(std::move(key),\
    \ multiplicity);\n        _history.push_back(std::move(entry));\n    }\n\n   \
    \ void insert_inplace(T key, int multiplicity = 1) {\n        insert(std::move(key),\
    \ multiplicity);\n    }\n\n    bool erase_one(const T& key) {\n        if (_checkpoints.empty())\
    \ return _data.erase_one(key);\n        int old_count = _data.count(key);\n  \
    \      Entry entry{Kind::key, std::optional<T>(key), old_count, {}};\n       \
    \ bool erased = _data.erase_one(key);\n        _history.push_back(std::move(entry));\n\
    \        return erased;\n    }\n\n    bool erase(const T& key) { return erase_one(key);\
    \ }\n    bool erase_one_inplace(const T& key) { return erase_one(key); }\n   \
    \ bool erase_inplace(const T& key) { return erase_one(key); }\n\n    int erase_all(const\
    \ T& key) {\n        int old_count = _data.count(key);\n        if (_checkpoints.empty())\
    \ {\n            _data.erase_all(key);\n            return old_count;\n      \
    \  }\n        Entry entry{Kind::key, std::optional<T>(key), old_count, {}};\n\
    \        _data.erase_all(key);\n        _history.push_back(std::move(entry));\n\
    \        return old_count;\n    }\n\n    bool erase_all_inplace(const T& key)\
    \ { return erase_all(key) != 0; }\n\n    void merge(const RollbackOrderedMultiset&\
    \ other) {\n        std::vector<T> values = other.to_vector();\n        for (const\
    \ T& value : values) _data.insert(value);\n        if (!_checkpoints.empty())\
    \ {\n            _history.push_back(Entry{Kind::merge, std::nullopt, 0, std::move(values)});\n\
    \        }\n    }\n\n    void merge(const OrderedMultiset<T, Compare>& other)\
    \ {\n        std::vector<T> values = other.to_vector();\n        for (const T&\
    \ value : values) _data.insert(value);\n        if (!_checkpoints.empty()) {\n\
    \            _history.push_back(Entry{Kind::merge, std::nullopt, 0, std::move(values)});\n\
    \        }\n    }\n\n    bool contains(const T& key) const { return _data.contains(key);\
    \ }\n    int count(const T& key) const { return _data.count(key); }\n    const\
    \ T* find_by_order(int order) const { return _data.find_by_order(order); }\n \
    \   T kth(int order) const { return _data.kth(order); }\n    int order_of_key(const\
    \ T& key) const { return _data.order_of_key(key); }\n    int count_less(const\
    \ T& key) const { return _data.count_less(key); }\n    int count_less_equal(const\
    \ T& key) const { return _data.count_less_equal(key); }\n    int count_greater(const\
    \ T& key) const { return _data.count_greater(key); }\n    int count_greater_equal(const\
    \ T& key) const { return _data.count_greater_equal(key); }\n    const T* lower_bound(const\
    \ T& key) const { return _data.lower_bound(key); }\n    const T* upper_bound(const\
    \ T& key) const { return _data.upper_bound(key); }\n    const T* min_ge(const\
    \ T& key) const { return _data.min_ge(key); }\n    const T* min_gt(const T& key)\
    \ const { return _data.min_gt(key); }\n    const T* max_le(const T& key) const\
    \ { return _data.max_le(key); }\n    const T* max_lt(const T& key) const { return\
    \ _data.max_lt(key); }\n    const T* min() const { return _data.min(); }\n   \
    \ const T* max() const { return _data.max(); }\n    std::vector<T> to_vector()\
    \ const { return _data.to_vector(); }\n\n    int snapshot() { _checkpoints.push_back(_history.size());\
    \ return int(_checkpoints.size()); }\n    int snapshot_count() const { return\
    \ int(_checkpoints.size()); }\n\n    void reserve_snapshots(int count) {\n   \
    \     assert(0 <= count);\n        _checkpoints.reserve(count);\n    }\n\n   private:\n\
    \    void restore_one() {\n        Entry entry = std::move(_history.back());\n\
    \        _history.pop_back();\n        if (entry.kind == Kind::key) {\n      \
    \      restore_count(*entry.key, entry.old_count);\n        } else if (entry.kind\
    \ == Kind::clear) {\n            for (T& value : entry.values) _data.insert(std::move(value));\n\
    \        } else {\n            for (const T& value : entry.values) _data.erase_one(value);\n\
    \        }\n    }\n\n   public:\n\n    void rollback(int state) {\n        assert(1\
    \ <= state && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() { _history.clear(); _checkpoints.clear(); }\n\n    void release()\
    \ {\n        _data.clear();\n        _history.clear();\n        _checkpoints.clear();\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/bst/rollback_ordered_set.hpp\"\
    \n\n\n\n#line 10 \"ds/bst/rollback_ordered_set.hpp\"\n\n#line 1 \"ds/bst/ordered_set.hpp\"\
    \n\n\n\n#line 10 \"ds/bst/ordered_set.hpp\"\n\nnamespace m1une {\nnamespace ds\
    \ {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct OrderedSet\
    \ {\n   private:\n    struct Node {\n        T key;\n        int size;\n     \
    \   Node* l;\n        Node* r;\n\n        explicit Node(T value)\n           \
    \ : key(std::move(value)), size(1), l(nullptr), r(nullptr) {}\n    };\n\n    static\
    \ constexpr int pool_block_size = 1 << 15;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
    \ blocks;\n        std::vector<Node*> free_nodes;\n\n        template <class...\
    \ Args>\n        Node* emplace(Args&&... args) {\n            if (!free_nodes.empty())\
    \ {\n                Node* result = free_nodes.back();\n                free_nodes.pop_back();\n\
    \                std::destroy_at(result);\n                std::construct_at(result,\
    \ std::forward<Args>(args)...);\n                return result;\n            }\n\
    \            if (blocks.empty() || int(blocks.back().size()) == pool_block_size)\
    \ {\n                blocks.emplace_back();\n                blocks.back().reserve(pool_block_size);\n\
    \            }\n            blocks.back().emplace_back(std::forward<Args>(args)...);\n\
    \            return &blocks.back().back();\n        }\n\n        void recycle(Node*\
    \ node) {\n            free_nodes.push_back(node);\n        }\n    };\n\n    inline\
    \ static Pool pool;\n\n    Node* root;\n    Compare comp;\n\n    static int subtree_size(const\
    \ Node* t) {\n        return t == nullptr ? 0 : t->size;\n    }\n\n    Node* new_node(T\
    \ key) {\n        return pool.emplace(std::move(key));\n    }\n\n    static void\
    \ update(Node* t) {\n        t->size = 1 + subtree_size(t->l) + subtree_size(t->r);\n\
    \    }\n\n    static Node* rotate_right(Node* t) {\n        Node* s = t->l;\n\
    \        t->l = s->r;\n        s->r = t;\n        update(t);\n        update(s);\n\
    \        return s;\n    }\n\n    static Node* rotate_left(Node* t) {\n       \
    \ Node* s = t->r;\n        t->r = s->l;\n        s->l = t;\n        update(t);\n\
    \        update(s);\n        return s;\n    }\n\n    static Node* balance(Node*\
    \ t) {\n        if (t == nullptr) return nullptr;\n        const int left_size\
    \ = subtree_size(t->l);\n        const int right_size = subtree_size(t->r);\n\
    \        if (left_size + right_size > 1 && left_size > 3LL * right_size) {\n \
    \           if (subtree_size(t->l->r) >= 2LL * subtree_size(t->l->l)) {\n    \
    \            t->l = rotate_left(t->l);\n            }\n            return rotate_right(t);\n\
    \        }\n        if (left_size + right_size > 1 && right_size > 3LL * left_size)\
    \ {\n            if (subtree_size(t->r->l) >= 2LL * subtree_size(t->r->r)) {\n\
    \                t->r = rotate_right(t->r);\n            }\n            return\
    \ rotate_left(t);\n        }\n        update(t);\n        return t;\n    }\n\n\
    \    static Node* join_with_root(Node* l, Node* middle, Node* r) {\n        const\
    \ int left_size = subtree_size(l);\n        const int right_size = subtree_size(r);\n\
    \        if (left_size > 3LL * (right_size + 1)) {\n            l->r = join_with_root(l->r,\
    \ middle, r);\n            return balance(l);\n        }\n        if (right_size\
    \ > 3LL * (left_size + 1)) {\n            r->l = join_with_root(l, middle, r->l);\n\
    \            return balance(r);\n        }\n        middle->l = l;\n        middle->r\
    \ = r;\n        return balance(middle);\n    }\n\n    static Node* detach_max(Node*\
    \ t, Node*& maximum) {\n        if (t->r == nullptr) {\n            maximum =\
    \ t;\n            return t->l;\n        }\n        t->r = detach_max(t->r, maximum);\n\
    \        return balance(t);\n    }\n\n    static Node* merge_nodes(Node* l, Node*\
    \ r) {\n        if (l == nullptr || r == nullptr) return l == nullptr ? r : l;\n\
    \        Node* middle;\n        l = detach_max(l, middle);\n        return join_with_root(l,\
    \ middle, r);\n    }\n\n    std::pair<Node*, Node*> split_nodes(Node* t, const\
    \ T& key) {\n        if (t == nullptr) return {nullptr, nullptr};\n        Node*\
    \ left = t->l;\n        Node* right = t->r;\n        t->l = nullptr;\n       \
    \ t->r = nullptr;\n        if (comp(t->key, key)) {\n            auto [l, r] =\
    \ split_nodes(right, key);\n            return {join_with_root(left, t, l), r};\n\
    \        }\n        auto [l, r] = split_nodes(left, key);\n        return {l,\
    \ join_with_root(r, t, right)};\n    }\n\n    Node* insert_impl(Node* t, T& key,\
    \ bool& inserted) {\n        if (t == nullptr) {\n            inserted = true;\n\
    \            return new_node(std::move(key));\n        }\n        if (comp(key,\
    \ t->key)) {\n            t->l = insert_impl(t->l, key, inserted);\n        }\
    \ else if (comp(t->key, key)) {\n            t->r = insert_impl(t->r, key, inserted);\n\
    \        } else {\n            return t;\n        }\n        if (!inserted) return\
    \ t;\n        return balance(t);\n    }\n\n    Node* erase_impl(Node* t, const\
    \ T& key, bool& erased) {\n        if (t == nullptr) return nullptr;\n       \
    \ if (comp(key, t->key)) {\n            t->l = erase_impl(t->l, key, erased);\n\
    \        } else if (comp(t->key, key)) {\n            t->r = erase_impl(t->r,\
    \ key, erased);\n        } else {\n            erased = true;\n            Node*\
    \ l = t->l;\n            Node* r = t->r;\n            pool.recycle(t);\n     \
    \       return merge_nodes(l, r);\n        }\n        if (!erased) return t;\n\
    \        return balance(t);\n    }\n\n    static const T* kth_impl(const Node*\
    \ t, int k) {\n        while (t != nullptr) {\n            const int left_size\
    \ = subtree_size(t->l);\n            if (k < left_size) {\n                t =\
    \ t->l;\n            } else if (k == left_size) {\n                return &t->key;\n\
    \            } else {\n                k -= left_size + 1;\n                t\
    \ = t->r;\n            }\n        }\n        return nullptr;\n    }\n\n    int\
    \ order_of_key_impl(const Node* t, const T& key, bool upper) const {\n       \
    \ int result = 0;\n        while (t != nullptr) {\n            const bool take\
    \ = upper ? !comp(key, t->key) : comp(t->key, key);\n            if (take) {\n\
    \                result += subtree_size(t->l) + 1;\n                t = t->r;\n\
    \            } else {\n                t = t->l;\n            }\n        }\n \
    \       return result;\n    }\n\n    const T* lower_bound_impl(const Node* t,\
    \ const T& key, bool strict) const {\n        const T* result = nullptr;\n   \
    \     while (t != nullptr) {\n            const bool candidate = strict ? comp(key,\
    \ t->key) : !comp(t->key, key);\n            if (candidate) {\n              \
    \  result = &t->key;\n                t = t->l;\n            } else {\n      \
    \          t = t->r;\n            }\n        }\n        return result;\n    }\n\
    \n    const T* max_less_impl(const Node* t, const T& key, bool strict) const {\n\
    \        const T* result = nullptr;\n        while (t != nullptr) {\n        \
    \    const bool candidate = strict ? comp(t->key, key) : !comp(key, t->key);\n\
    \            if (candidate) {\n                result = &t->key;\n           \
    \     t = t->r;\n            } else {\n                t = t->l;\n           \
    \ }\n        }\n        return result;\n    }\n\n    bool contains_impl(const\
    \ Node* t, const T& key) const {\n        while (t != nullptr) {\n           \
    \ if (comp(key, t->key)) {\n                t = t->l;\n            } else if (comp(t->key,\
    \ key)) {\n                t = t->r;\n            } else {\n                return\
    \ true;\n            }\n        }\n        return false;\n    }\n\n    static\
    \ void dump_impl(const Node* t, std::vector<T>& result) {\n        if (t == nullptr)\
    \ return;\n        dump_impl(t->l, result);\n        result.push_back(t->key);\n\
    \        dump_impl(t->r, result);\n    }\n\n    static void recycle_impl(Node*\
    \ t) {\n        if (t == nullptr) return;\n        recycle_impl(t->l);\n     \
    \   recycle_impl(t->r);\n        pool.recycle(t);\n    }\n\n    Node* clone_impl(const\
    \ Node* t) {\n        if (t == nullptr) return nullptr;\n        Node* result\
    \ = new_node(t->key);\n        result->l = clone_impl(t->l);\n        result->r\
    \ = clone_impl(t->r);\n        update(result);\n        return result;\n    }\n\
    \n    OrderedSet(Node* node, Compare compare) : root(node), comp(std::move(compare))\
    \ {}\n\n   public:\n    explicit OrderedSet(Compare compare)\n        : root(nullptr),\
    \ comp(std::move(compare)) {}\n\n    OrderedSet() : OrderedSet(Compare()) {}\n\
    \n    OrderedSet(std::initializer_list<T> init, Compare compare = Compare()) :\
    \ OrderedSet(std::move(compare)) {\n        for (const T& x : init) insert(x);\n\
    \    }\n\n    template <typename Iterator>\n    OrderedSet(Iterator first, Iterator\
    \ last, Compare compare = Compare()) : OrderedSet(std::move(compare)) {\n    \
    \    while (first != last) insert(*first++);\n    }\n\n    OrderedSet(const OrderedSet&\
    \ other)\n        : root(nullptr), comp(other.comp) {\n        root = clone_impl(other.root);\n\
    \    }\n\n    OrderedSet(OrderedSet&& other) noexcept\n        : root(std::exchange(other.root,\
    \ nullptr)), comp(std::move(other.comp)) {}\n\n    ~OrderedSet() {\n        recycle_impl(root);\n\
    \    }\n\n    OrderedSet& operator=(OrderedSet other) {\n        swap(other);\n\
    \        return *this;\n    }\n\n    void swap(OrderedSet& other) noexcept {\n\
    \        using std::swap;\n        swap(root, other.root);\n        swap(comp,\
    \ other.comp);\n    }\n\n    int size() const { return subtree_size(root); }\n\
    \    int unique_size() const { return size(); }\n    bool empty() const { return\
    \ root == nullptr; }\n\n    void clear() {\n        recycle_impl(root);\n    \
    \    root = nullptr;\n    }\n\n    bool insert(T key) {\n        bool inserted\
    \ = false;\n        root = insert_impl(root, key, inserted);\n        return inserted;\n\
    \    }\n\n    bool erase(const T& key) {\n        bool erased = false;\n     \
    \   root = erase_impl(root, key, erased);\n        return erased;\n    }\n\n \
    \   bool contains(const T& key) const { return contains_impl(root, key); }\n \
    \   int count(const T& key) const { return contains(key) ? 1 : 0; }\n\n    const\
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
    \ true); }\n    const T* min() const { return empty() ? nullptr : kth_impl(root,\
    \ 0); }\n    const T* max() const { return empty() ? nullptr : kth_impl(root,\
    \ size() - 1); }\n\n    std::pair<OrderedSet, OrderedSet> split(const T& key)\
    \ && {\n        auto [l, r] = split_nodes(root, key);\n        root = nullptr;\n\
    \        return {OrderedSet(l, comp), OrderedSet(r, std::move(comp))};\n    }\n\
    \n    OrderedSet merge(OrderedSet other) && {\n        assert(empty() || other.empty()\
    \ || comp(*max(), *other.min()));\n        root = merge_nodes(root, other.root);\n\
    \        other.root = nullptr;\n        return std::move(*this);\n    }\n\n  \
    \  std::vector<T> to_vector() const {\n        std::vector<T> result;\n      \
    \  result.reserve(size());\n        dump_impl(root, result);\n        return result;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"ds/bst/rollback_ordered_set.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T, class Compare = std::less<T>>\n\
    struct RollbackOrderedSet {\n   private:\n    enum class Kind { insert, erase,\
    \ clear, merge };\n    struct Entry {\n        Kind kind;\n        bool changed;\n\
    \        std::optional<T> key;\n        std::vector<T> keys;\n    };\n\n    OrderedSet<T,\
    \ Compare> _data;\n    std::vector<Entry> _history;\n    std::vector<std::size_t>\
    \ _checkpoints;\n\n   public:\n    explicit RollbackOrderedSet(Compare compare)\n\
    \        : _data(std::move(compare)) {}\n    RollbackOrderedSet() = default;\n\
    \n    RollbackOrderedSet(\n        std::initializer_list<T> init,\n        Compare\
    \ compare = Compare()\n    ) : _data(init, std::move(compare)) {}\n\n    template\
    \ <class Iterator>\n    RollbackOrderedSet(\n        Iterator first,\n       \
    \ Iterator last,\n        Compare compare = Compare()\n    ) : _data(first, last,\
    \ std::move(compare)) {}\n\n    int size() const { return _data.size(); }\n  \
    \  int unique_size() const { return _data.size(); }\n    bool empty() const {\
    \ return _data.empty(); }\n    std::size_t node_count() const { return std::size_t(size());\
    \ }\n\n    void clear() {\n        if (_checkpoints.empty()) {\n            _data.clear();\n\
    \            return;\n        }\n        Entry entry{Kind::clear, !empty(), std::nullopt,\
    \ {}};\n        if (!empty()) entry.keys = _data.to_vector();\n        _data.clear();\n\
    \        _history.push_back(std::move(entry));\n    }\n\n    bool insert(T key)\
    \ {\n        if (_checkpoints.empty()) return _data.insert(std::move(key));\n\
    \        bool changed = !_data.contains(key);\n        Entry entry{Kind::insert,\
    \ changed, std::nullopt, {}};\n        if (changed) entry.key.emplace(key);\n\
    \        _data.insert(std::move(key));\n        _history.push_back(std::move(entry));\n\
    \        return changed;\n    }\n\n    bool erase(const T& key) {\n        if\
    \ (_checkpoints.empty()) return _data.erase(key);\n        bool changed = _data.contains(key);\n\
    \        Entry entry{Kind::erase, changed, std::nullopt, {}};\n        if (changed)\
    \ entry.key.emplace(key);\n        _data.erase(key);\n        _history.push_back(std::move(entry));\n\
    \        return changed;\n    }\n\n    void merge(const RollbackOrderedSet& other)\
    \ {\n        std::vector<T> keys = other.to_vector();\n        for (const T& key\
    \ : keys) {\n            bool inserted = _data.insert(key);\n            assert(inserted);\n\
    \        }\n        if (!_checkpoints.empty()) {\n            _history.push_back(Entry{Kind::merge,\
    \ !keys.empty(), std::nullopt, std::move(keys)});\n        }\n    }\n\n    void\
    \ merge(const OrderedSet<T, Compare>& other) {\n        std::vector<T> keys =\
    \ other.to_vector();\n        for (const T& key : keys) {\n            bool inserted\
    \ = _data.insert(key);\n            assert(inserted);\n        }\n        if (!_checkpoints.empty())\
    \ {\n            _history.push_back(Entry{Kind::merge, !keys.empty(), std::nullopt,\
    \ std::move(keys)});\n        }\n    }\n\n    bool contains(const T& key) const\
    \ { return _data.contains(key); }\n    int count(const T& key) const { return\
    \ _data.count(key); }\n    const T* find_by_order(int order) const { return _data.find_by_order(order);\
    \ }\n    T kth(int order) const { return _data.kth(order); }\n    int order_of_key(const\
    \ T& key) const { return _data.order_of_key(key); }\n    int count_less(const\
    \ T& key) const { return _data.count_less(key); }\n    int count_less_equal(const\
    \ T& key) const { return _data.count_less_equal(key); }\n    int count_greater(const\
    \ T& key) const { return _data.count_greater(key); }\n    int count_greater_equal(const\
    \ T& key) const { return _data.count_greater_equal(key); }\n    const T* lower_bound(const\
    \ T& key) const { return _data.lower_bound(key); }\n    const T* upper_bound(const\
    \ T& key) const { return _data.upper_bound(key); }\n    const T* min_ge(const\
    \ T& key) const { return _data.min_ge(key); }\n    const T* min_gt(const T& key)\
    \ const { return _data.min_gt(key); }\n    const T* max_le(const T& key) const\
    \ { return _data.max_le(key); }\n    const T* max_lt(const T& key) const { return\
    \ _data.max_lt(key); }\n    const T* min() const { return _data.min(); }\n   \
    \ const T* max() const { return _data.max(); }\n    std::vector<T> to_vector()\
    \ const { return _data.to_vector(); }\n\n    int snapshot() { _checkpoints.push_back(_history.size());\
    \ return int(_checkpoints.size()); }\n    int snapshot_count() const { return\
    \ int(_checkpoints.size()); }\n\n    void reserve_snapshots(int count) {\n   \
    \     assert(0 <= count);\n        _checkpoints.reserve(count);\n    }\n\n   private:\n\
    \    void restore_one() {\n        Entry entry = std::move(_history.back());\n\
    \        _history.pop_back();\n        if (!entry.changed) return;\n        if\
    \ (entry.kind == Kind::insert) {\n            _data.erase(*entry.key);\n     \
    \   } else if (entry.kind == Kind::erase) {\n            _data.insert(std::move(*entry.key));\n\
    \        } else if (entry.kind == Kind::clear) {\n            for (T& key : entry.keys)\
    \ _data.insert(std::move(key));\n        } else {\n            for (const T& key\
    \ : entry.keys) _data.erase(key);\n        }\n    }\n\n   public:\n\n    void\
    \ rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        while (_history.size() > _checkpoints[state - 1]) restore_one();\n  \
    \      _checkpoints.resize(state);\n    }\n\n    void clear_history() { _history.clear();\
    \ _checkpoints.clear(); }\n\n    void release() {\n        _data.clear();\n  \
    \      _history.clear();\n        _checkpoints.clear();\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"ds/deque/rollback_deque.hpp\"\n\n\n\
    \n#line 5 \"ds/deque/rollback_deque.hpp\"\n#include <deque>\n#line 9 \"ds/deque/rollback_deque.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackDeque\
    \ {\n   private:\n    enum class Kind { push_front, push_back, pop_front, pop_back,\
    \ clear };\n    struct Entry {\n        Kind kind;\n        std::optional<T> value;\n\
    \        std::deque<T> values;\n    };\n\n    std::deque<T> _values;\n    std::vector<Entry>\
    \ _history;\n    std::vector<std::size_t> _checkpoints;\n    std::size_t _stored_values\
    \ = 0;\n\n    void record_push(Kind kind) {\n        if (!_checkpoints.empty())\
    \ _history.push_back(Entry{kind, std::nullopt, {}});\n        ++_stored_values;\n\
    \    }\n\n   public:\n    RollbackDeque() = default;\n\n    int size() const {\
    \ return int(_values.size()); }\n    bool empty() const { return _values.empty();\
    \ }\n    std::size_t node_count() const { return _stored_values; }\n\n    const\
    \ T& front() const {\n        assert(!empty());\n        return _values.front();\n\
    \    }\n\n    const T& back() const {\n        assert(!empty());\n        return\
    \ _values.back();\n    }\n\n    void push_front(T value) {\n        record_push(Kind::push_front);\n\
    \        _values.push_front(std::move(value));\n    }\n\n    template <class...\
    \ Args>\n    void emplace_front(Args&&... args) {\n        record_push(Kind::push_front);\n\
    \        _values.emplace_front(std::forward<Args>(args)...);\n    }\n\n    void\
    \ push_back(T value) {\n        record_push(Kind::push_back);\n        _values.push_back(std::move(value));\n\
    \    }\n\n    template <class... Args>\n    void emplace_back(Args&&... args)\
    \ {\n        record_push(Kind::push_back);\n        _values.emplace_back(std::forward<Args>(args)...);\n\
    \    }\n\n    void pop_front() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_front();\n            --_stored_values;\n       \
    \ } else {\n            Entry entry{Kind::pop_front, std::nullopt, {}};\n    \
    \        entry.value.emplace(std::move(_values.front()));\n            _values.pop_front();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    void\
    \ pop_back() {\n        assert(!empty());\n        if (_checkpoints.empty()) {\n\
    \            _values.pop_back();\n            --_stored_values;\n        } else\
    \ {\n            Entry entry{Kind::pop_back, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
    \            _values.pop_back();\n            _history.push_back(std::move(entry));\n\
    \        }\n    }\n\n    void clear() {\n        if (_checkpoints.empty()) {\n\
    \            _stored_values -= _values.size();\n            _values.clear();\n\
    \        } else {\n            Entry entry{Kind::clear, std::nullopt, {}};\n \
    \           entry.values = std::move(_values);\n            _values.clear();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(_history.size());\n        return\
    \ int(_checkpoints.size());\n    }\n    int snapshot_count() const { return int(_checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        _checkpoints.reserve(count);\n    }\n\n   private:\n    void restore_one()\
    \ {\n        Entry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.kind == Kind::push_front) {\n            _values.pop_front();\n\
    \            --_stored_values;\n        } else if (entry.kind == Kind::push_back)\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else if (entry.kind == Kind::pop_front) {\n            _values.push_front(std::move(*entry.value));\n\
    \        } else if (entry.kind == Kind::pop_back) {\n            _values.push_back(std::move(*entry.value));\n\
    \        } else {\n            _values = std::move(entry.values);\n        }\n\
    \    }\n\n   public:\n    void rollback(int state) {\n        assert(1 <= state\
    \ && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() {\n        for (const Entry& entry : _history) {\n         \
    \   if (entry.value) --_stored_values;\n            _stored_values -= entry.values.size();\n\
    \        }\n        _history.clear();\n        _checkpoints.clear();\n    }\n\n\
    \    void release() {\n        _values.clear();\n        _history.clear();\n \
    \       _checkpoints.clear();\n        _stored_values = 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/dsu/rollback_potentialized_dsu.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 6 \"ds/dsu/rollback_potentialized_dsu.hpp\"\
    \n#include <concepts>\n#include <cstddef>\n#line 10 \"ds/dsu/rollback_potentialized_dsu.hpp\"\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for groups. A type satisfying this concept\
    \ must also obey the group\n// laws; concepts can check the interface but not\
    \ the algebraic properties.\ntemplate <typename M>\nconcept IsGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative groups. Commutativity is a\
    \ semantic requirement and\n// cannot be checked by a C++ concept.\ntemplate <typename\
    \ M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\n}  // namespace monoid\n}  //\
    \ namespace m1une\n\n\n#line 12 \"ds/dsu/rollback_potentialized_dsu.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsGroup Group>\n\
    \    requires std::equality_comparable<typename Group::value_type>\nstruct RollbackPotentializedDsu\
    \ {\n    using T = typename Group::value_type;\n\n   private:\n    struct HistoryEntry\
    \ {\n        int first;\n        int first_value;\n        int second;\n     \
    \   int second_value;\n        T second_diff;\n\n        HistoryEntry(int first_index,\
    \ int first_parent, int second_index,\n                     int second_parent,\
    \ T diff)\n            : first(first_index),\n              first_value(first_parent),\n\
    \              second(second_index),\n              second_value(second_parent),\n\
    \              second_diff(std::move(diff)) {}\n    };\n\n    int _n;\n    int\
    \ _component_count;\n    std::vector<int> _parent_or_size;\n    std::vector<T>\
    \ _diff_to_parent;\n    std::vector<HistoryEntry> _history;\n    std::vector<std::size_t>\
    \ _checkpoints;\n\n    static int check_size(int n) {\n        assert(0 <= n);\n\
    \        return n;\n    }\n\n    std::pair<int, T> leader_and_potential(int vertex)\
    \ const {\n        assert(0 <= vertex && vertex < _n);\n        T result = Group::id();\n\
    \        while (_parent_or_size[vertex] >= 0) {\n            result = Group::op(_diff_to_parent[vertex],\
    \ result);\n            vertex = _parent_or_size[vertex];\n        }\n       \
    \ return {vertex, std::move(result)};\n    }\n\n   public:\n    RollbackPotentializedDsu()\
    \ : RollbackPotentializedDsu(0) {}\n\n    explicit RollbackPotentializedDsu(int\
    \ n)\n        : _n(check_size(n)),\n          _component_count(_n),\n        \
    \  _parent_or_size(_n, -1),\n          _diff_to_parent(_n, Group::id()) {}\n\n\
    \    int size() const { return _n; }\n    bool empty() const { return _n == 0;\
    \ }\n    int component_count() const { return _component_count; }\n    int snapshot_count()\
    \ const { return int(_checkpoints.size()); }\n\n    void reserve_snapshots(int\
    \ count) {\n        assert(0 <= count);\n        _checkpoints.reserve(count);\n\
    \    }\n\n    int leader(int vertex) const {\n        return leader_and_potential(vertex).first;\n\
    \    }\n\n    bool same(int first, int second) const {\n        return leader(first)\
    \ == leader(second);\n    }\n\n    int group_size(int vertex) const {\n      \
    \  return -_parent_or_size[leader(vertex)];\n    }\n\n    int size(int vertex)\
    \ const { return group_size(vertex); }\n\n    T potential(int vertex) const {\n\
    \        return leader_and_potential(vertex).second;\n    }\n\n    T diff(int\
    \ first, int second) const {\n        assert(same(first, second));\n        return\
    \ Group::op(Group::inv(potential(first)), potential(second));\n    }\n\n    int\
    \ parent_or_size(int vertex) const {\n        assert(0 <= vertex && vertex < _n);\n\
    \        return _parent_or_size[vertex];\n    }\n\n    bool merge(int first, int\
    \ second, const T& difference) {\n        auto [first_root, first_potential] =\
    \ leader_and_potential(first);\n        auto [second_root, second_potential] =\
    \ leader_and_potential(second);\n        if (first_root == second_root) {\n  \
    \          return Group::op(Group::inv(first_potential), second_potential) ==\
    \ difference;\n        }\n\n        T second_from_first = Group::op(\n       \
    \     Group::op(first_potential, difference),\n            Group::inv(second_potential)\n\
    \        );\n        if (-_parent_or_size[first_root] < -_parent_or_size[second_root])\
    \ {\n            std::swap(first_root, second_root);\n            second_from_first\
    \ = Group::inv(second_from_first);\n        }\n\n        if (!_checkpoints.empty())\
    \ {\n            _history.emplace_back(\n                first_root, _parent_or_size[first_root],\
    \ second_root,\n                _parent_or_size[second_root], _diff_to_parent[second_root]\n\
    \            );\n        }\n        _parent_or_size[first_root] += _parent_or_size[second_root];\n\
    \        _parent_or_size[second_root] = first_root;\n        _diff_to_parent[second_root]\
    \ = std::move(second_from_first);\n        --_component_count;\n        return\
    \ true;\n    }\n\n   private:\n    void restore_one() {\n        HistoryEntry\
    \ entry = std::move(_history.back());\n        _history.pop_back();\n        _parent_or_size[entry.first]\
    \ = entry.first_value;\n        _parent_or_size[entry.second] = entry.second_value;\n\
    \        _diff_to_parent[entry.second] = std::move(entry.second_diff);\n     \
    \   ++_component_count;\n    }\n\n   public:\n    int snapshot() { _checkpoints.push_back(_history.size());\
    \ return int(_checkpoints.size()); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        while (_history.size()\
    \ > _checkpoints[state - 1]) restore_one();\n        _checkpoints.resize(state);\n\
    \    }\n\n    void clear_history() { _history.clear(); _checkpoints.clear(); }\n\
    \n    std::vector<std::vector<int>> groups() const {\n        std::vector<int>\
    \ leaders(_n);\n        std::vector<int> sizes(_n);\n        for (int vertex =\
    \ 0; vertex < _n; ++vertex) {\n            leaders[vertex] = leader(vertex);\n\
    \            ++sizes[leaders[vertex]];\n        }\n        std::vector<std::vector<int>>\
    \ result(_n);\n        for (int vertex = 0; vertex < _n; ++vertex) {\n       \
    \     result[vertex].reserve(sizes[vertex]);\n        }\n        for (int vertex\
    \ = 0; vertex < _n; ++vertex) {\n            result[leaders[vertex]].push_back(vertex);\n\
    \        }\n        result.erase(\n            std::remove_if(\n             \
    \   result.begin(), result.end(),\n                [](const std::vector<int>&\
    \ group) { return group.empty(); }\n            ),\n            result.end()\n\
    \        );\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"ds/dynamic_array/rollback_dynamic_array.hpp\"\n\n\n\n#line\
    \ 9 \"ds/dynamic_array/rollback_dynamic_array.hpp\"\n\n#line 1 \"ds/dynamic_array/dynamic_array.hpp\"\
    \n\n\n\n#line 5 \"ds/dynamic_array/dynamic_array.hpp\"\n#include <chrono>\n#include\
    \ <cstdint>\n#line 10 \"ds/dynamic_array/dynamic_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename T>\nstruct DynamicArray {\n   private:\n\
    \    struct Node {\n        T val;\n        int priority;\n        int count;\n\
    \        int l, r;\n        bool rev;\n\n        Node() : val(T()), priority(0),\
    \ count(0), l(0), r(0), rev(false) {}\n        Node(T value, int node_priority)\n\
    \            : val(std::move(value)), priority(node_priority), count(1), l(0),\
    \ r(0), rev(false) {}\n    };\n\n    std::vector<Node> pool;\n    int root;\n\
    \    std::uint32_t rng_state;\n\n    int new_node(T val) {\n        pool.push_back(Node(std::move(val),\
    \ next_priority()));\n        return pool.size() - 1;\n    }\n\n    int next_priority()\
    \ {\n        rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >>\
    \ 17;\n        rng_state ^= rng_state << 5;\n        return int(rng_state);\n\
    \    }\n\n    void update(int t) {\n        if (t) {\n            pool[t].count\
    \ = 1 + pool[pool[t].l].count + pool[pool[t].r].count;\n        }\n    }\n\n \
    \   void apply_reverse(int t) {\n        if (t) {\n            pool[t].rev = !pool[t].rev;\n\
    \        }\n    }\n\n    void push(int t) {\n        if (!t || !pool[t].rev) return;\n\
    \        std::swap(pool[t].l, pool[t].r);\n        apply_reverse(pool[t].l);\n\
    \        apply_reverse(pool[t].r);\n        pool[t].rev = false;\n    }\n\n  \
    \  void split(int t, int pos, int& l, int& r) {\n        if (!t) {\n         \
    \   l = r = 0;\n            return;\n        }\n        if (pos == 0) {\n    \
    \        l = 0;\n            r = t;\n            return;\n        }\n        if\
    \ (pos == pool[t].count) {\n            l = t;\n            r = 0;\n         \
    \   return;\n        }\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos == left_count) {\n            l = pool[t].l;\n            pool[t].l\
    \ = 0;\n            update(t);\n            r = t;\n            return;\n    \
    \    }\n        if (pos == left_count + 1) {\n            r = pool[t].r;\n   \
    \         pool[t].r = 0;\n            update(t);\n            l = t;\n       \
    \     return;\n        }\n        if (pos <= left_count) {\n            split(pool[t].l,\
    \ pos, l, pool[t].l);\n            r = t;\n        } else {\n            split(pool[t].r,\
    \ pos - left_count - 1, pool[t].r, r);\n            l = t;\n        }\n      \
    \  update(t);\n    }\n\n    int merge(int l, int r) {\n        if (!l || !r) return\
    \ l ? l : r;\n        if (pool[l].priority > pool[r].priority) {\n           \
    \ push(l);\n            if (pool[l].r) {\n                pool[l].r = merge(pool[l].r,\
    \ r);\n            } else {\n                pool[l].r = r;\n            }\n \
    \           update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    int insert_node(int\
    \ t, int pos, int node) {\n        if (!t) return node;\n        if (pool[node].priority\
    \ > pool[t].priority) {\n            split(t, pos, pool[node].l, pool[node].r);\n\
    \            update(node);\n            return node;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos <= left_count)\
    \ {\n            pool[t].l = insert_node(pool[t].l, pos, node);\n        } else\
    \ {\n            pool[t].r = insert_node(pool[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            pool[t].l = erase_node(pool[t].l,\
    \ pos);\n            update(t);\n            return t;\n        }\n        if\
    \ (pos == left_count) {\n            return merge(pool[t].l, pool[t].r);\n   \
    \     }\n        pool[t].r = erase_node(pool[t].r, pos - left_count - 1);\n  \
    \      update(t);\n        return t;\n    }\n\n    int find_node(int t, int pos)\
    \ {\n        while (t) {\n            push(t);\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return t;\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = pool[t].r;\n\
    \            }\n        }\n        return 0;\n    }\n\n    int find_node(int t,\
    \ int pos, bool reversed) const {\n        while (t) {\n            bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n            int left = cur_reversed ? pool[t].r :\
    \ pool[t].l;\n            int right = cur_reversed ? pool[t].l : pool[t].r;\n\
    \            int left_count = pool[left].count;\n            if (pos < left_count)\
    \ {\n                t = left;\n                reversed = cur_reversed;\n   \
    \         } else if (pos == left_count) {\n                return t;\n       \
    \     } else {\n                pos -= left_count + 1;\n                t = right;\n\
    \                reversed = cur_reversed;\n            }\n        }\n        return\
    \ 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>& res, bool reversed = false)\
    \ const {\n        if (!t) return;\n        bool cur_reversed = reversed ^ pool[t].rev;\n\
    \        int left = cur_reversed ? pool[t].r : pool[t].l;\n        int right =\
    \ cur_reversed ? pool[t].l : pool[t].r;\n        dump_dfs(left, res, cur_reversed);\n\
    \        res.push_back(pool[t].val);\n        dump_dfs(right, res, cur_reversed);\n\
    \    }\n\n    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (!t || qr <= offset || offset\
    \ + pool[t].count <= ql) return;\n        bool cur_reversed = reversed ^ pool[t].rev;\n\
    \        int left = cur_reversed ? pool[t].r : pool[t].l;\n        int right =\
    \ cur_reversed ? pool[t].l : pool[t].r;\n        int left_count = pool[left].count;\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(left, ql,\
    \ qr, offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos < qr)\
    \ {\n            res.push_back(pool[t].val);\n        }\n        dump_range_dfs(right,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int clone_subtree_from(const\
    \ DynamicArray& other, int t) {\n        if (!t) return 0;\n        int res =\
    \ static_cast<int>(pool.size());\n        pool.push_back(other.pool[t]);\n   \
    \     pool[res].l = clone_subtree_from(other, other.pool[t].l);\n        pool[res].r\
    \ = clone_subtree_from(other, other.pool[t].r);\n        return res;\n    }\n\n\
    \    void update_dfs(int t) {\n        if (!t) return;\n        update_dfs(pool[t].l);\n\
    \        update_dfs(pool[t].r);\n        update(t);\n    }\n\n    int build_cartesian(int\
    \ first, int last) {\n        if (first == last) return 0;\n        std::vector<int>\
    \ stack;\n        stack.reserve(last - first);\n        for (int i = first; i\
    \ < last; i++) {\n            int left_child = 0;\n            while (!stack.empty()\
    \ && pool[stack.back()].priority < pool[i].priority) {\n                left_child\
    \ = stack.back();\n                stack.pop_back();\n            }\n        \
    \    pool[i].l = left_child;\n            if (!stack.empty()) {\n            \
    \    pool[stack.back()].r = i;\n            }\n            stack.push_back(i);\n\
    \        }\n        int res = stack.front();\n        update_dfs(res);\n     \
    \   return res;\n    }\n\n    int build_from_vector(const std::vector<T>& v) {\n\
    \        int first = int(pool.size());\n        pool.reserve(pool.size() + v.size());\n\
    \        for (const T& x : v) {\n            new_node(x);\n        }\n       \
    \ return build_cartesian(first, int(pool.size()));\n    }\n\n    int build_from_vector(std::vector<T>&&\
    \ v) {\n        int first = int(pool.size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        return build_cartesian(first, int(pool.size()));\n    }\n\n\
    \    void reset_to_empty() {\n        pool.clear();\n        pool.push_back(Node());\n\
    \        root = 0;\n    }\n\n   public:\n    DynamicArray() : root(0), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicArray(const DynamicArray& other) : pool(other.pool),\
    \ root(other.root), rng_state(other.rng_state) {}\n\n    DynamicArray(DynamicArray&&\
    \ other) noexcept\n        : pool(std::move(other.pool)), root(other.root), rng_state(other.rng_state)\
    \ {\n        other.reset_to_empty();\n    }\n\n    DynamicArray& operator=(const\
    \ DynamicArray& other) {\n        if (this != &other) {\n            pool = other.pool;\n\
    \            root = other.root;\n            rng_state = other.rng_state;\n  \
    \      }\n        return *this;\n    }\n\n    DynamicArray& operator=(DynamicArray&&\
    \ other) noexcept {\n        if (this != &other) {\n            pool = std::move(other.pool);\n\
    \            root = other.root;\n            rng_state = other.rng_state;\n  \
    \          other.reset_to_empty();\n        }\n        return *this;\n    }\n\n\
    \    explicit DynamicArray(int n) : DynamicArray(n, T()) {}\n\n    DynamicArray(int\
    \ n, const T& value) : DynamicArray() {\n        assert(0 <= n);\n        pool.reserve(n\
    \ + 1);\n        int first = int(pool.size());\n        for (int i = 0; i < n;\
    \ i++) {\n            new_node(value);\n        }\n        root = build_cartesian(first,\
    \ int(pool.size()));\n    }\n\n    explicit DynamicArray(const std::vector<T>&\
    \ v) : DynamicArray() {\n        pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit DynamicArray(std::vector<T>&& v) : DynamicArray() {\n \
    \       pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    DynamicArray(std::initializer_list<T> init) : DynamicArray() {\n\
    \        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T val) {\n \
    \       assert(0 <= pos && pos <= size());\n        root = insert_node(root, pos,\
    \ new_node(std::move(val)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicArray& other) {\n        assert(0\
    \ <= pos && pos <= size());\n        if (other.empty()) return;\n        pool.reserve(pool.size()\
    \ + other.size());\n        int mid = clone_subtree_from(other, other.root);\n\
    \        int l, r;\n        split(root, pos, l, r);\n        root = merge(merge(l,\
    \ mid), r);\n    }\n\n    void push_back(T val) {\n        insert(size(), std::move(val));\n\
    \    }\n\n    void push_front(T val) {\n        insert(0, std::move(val));\n \
    \   }\n\n    void append(const std::vector<T>& v) {\n        insert(size(), v);\n\
    \    }\n\n    void append(std::vector<T>&& v) {\n        insert(size(), std::move(v));\n\
    \    }\n\n    void append(const DynamicArray& other) {\n        insert(size(),\
    \ other);\n    }\n\n    void erase(int pos) {\n        assert(0 <= pos && pos\
    \ < size());\n        root = erase_node(root, pos);\n    }\n\n    void erase(int\
    \ l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l\
    \ == r) return;\n        int a, b, c;\n        split(root, l, a, b);\n       \
    \ split(b, r - l, b, c);\n        root = merge(a, c);\n    }\n\n    void pop_back()\
    \ {\n        assert(!empty());\n        erase(size() - 1);\n    }\n\n    void\
    \ pop_front() {\n        assert(!empty());\n        erase(0);\n    }\n\n    T&\
    \ at(int pos) {\n        assert(0 <= pos && pos < size());\n        return pool[find_node(root,\
    \ pos)].val;\n    }\n\n    const T& at(int pos) const {\n        assert(0 <= pos\
    \ && pos < size());\n        return pool[find_node(root, pos, false)].val;\n \
    \   }\n\n    T& operator[](int pos) {\n        return at(pos);\n    }\n\n    const\
    \ T& operator[](int pos) const {\n        return at(pos);\n    }\n\n    T& front()\
    \ {\n        assert(!empty());\n        return at(0);\n    }\n\n    const T& front()\
    \ const {\n        assert(!empty());\n        return at(0);\n    }\n\n    T& back()\
    \ {\n        assert(!empty());\n        return at(size() - 1);\n    }\n\n    const\
    \ T& back() const {\n        assert(!empty());\n        return at(size() - 1);\n\
    \    }\n\n    void reverse(int l, int r) {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return;\n        int a, b, c;\n        split(root,\
    \ l, a, b);\n        split(b, r - l, b, c);\n        apply_reverse(b);\n     \
    \   root = merge(merge(a, b), c);\n    }\n\n    void reverse() {\n        apply_reverse(root);\n\
    \    }\n\n    void rotate(int l, int m, int r) {\n        assert(0 <= l && l <=\
    \ m && m <= r && r <= size());\n        if (l == m || m == r) return;\n      \
    \  int a, b, c, d;\n        split(root, l, a, b);\n        split(b, m - l, b,\
    \ c);\n        split(c, r - m, c, d);\n        root = merge(merge(a, c), merge(b,\
    \ d));\n    }\n\n    T get(int pos) const {\n        return at(pos);\n    }\n\n\
    \    void set(int pos, T val) {\n        at(pos) = std::move(val);\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicArray split_off(int pos) {\n        assert(0 <= pos && pos\
    \ <= size());\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = l;\n\n        DynamicArray res;\n        res.pool.reserve(pool[r].count +\
    \ 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return res;\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 11 \"ds/dynamic_array/rollback_dynamic_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct RollbackDynamicArray\
    \ {\n   private:\n    enum class Kind { insert, erase, set, reverse, rotate, clear\
    \ };\n    struct Entry {\n        Kind kind;\n        int first;\n        int\
    \ second;\n        int third;\n        std::optional<T> value;\n        std::vector<T>\
    \ values;\n    };\n\n    DynamicArray<T> _data;\n    std::vector<Entry> _history;\n\
    \    std::vector<std::size_t> _checkpoints;\n\n    void record_insert(int pos,\
    \ int count) {\n        if (!_checkpoints.empty()) {\n            _history.push_back(Entry{Kind::insert,\
    \ pos, count, 0, std::nullopt, {}});\n        }\n    }\n\n   public:\n    RollbackDynamicArray()\
    \ = default;\n    explicit RollbackDynamicArray(int n) : _data(n) {}\n    RollbackDynamicArray(int\
    \ n, const T& value) : _data(n, value) {}\n    explicit RollbackDynamicArray(const\
    \ std::vector<T>& values) : _data(values) {}\n    explicit RollbackDynamicArray(std::vector<T>&&\
    \ values) : _data(std::move(values)) {}\n    RollbackDynamicArray(std::initializer_list<T>\
    \ init) : _data(init) {}\n\n    int size() const { return _data.size(); }\n  \
    \  bool empty() const { return _data.empty(); }\n    std::size_t node_count()\
    \ const { return std::size_t(size()); }\n\n    void clear() {\n        Entry entry{Kind::clear,\
    \ 0, 0, 0, std::nullopt, {}};\n        if (!_checkpoints.empty()) entry.values\
    \ = _data.to_vector();\n        _data.clear();\n        if (!_checkpoints.empty())\
    \ _history.push_back(std::move(entry));\n    }\n\n    void insert(int pos, T value)\
    \ {\n        _data.insert(pos, std::move(value));\n        record_insert(pos,\
    \ 1);\n    }\n\n    void insert(int pos, const std::vector<T>& values) {\n   \
    \     _data.insert(pos, values);\n        record_insert(pos, int(values.size()));\n\
    \    }\n\n    void insert(int pos, std::vector<T>&& values) {\n        int count\
    \ = int(values.size());\n        _data.insert(pos, std::move(values));\n     \
    \   record_insert(pos, count);\n    }\n\n    void insert(int pos, std::initializer_list<T>\
    \ values) {\n        insert(pos, std::vector<T>(values));\n    }\n\n    void insert(int\
    \ pos, const RollbackDynamicArray& other) {\n        insert(pos, other.to_vector());\n\
    \    }\n\n    void insert(int pos, const DynamicArray<T>& other) {\n        insert(pos,\
    \ other.to_vector());\n    }\n\n    void push_back(T value) { insert(size(), std::move(value));\
    \ }\n    void push_front(T value) { insert(0, std::move(value)); }\n    void append(const\
    \ std::vector<T>& values) { insert(size(), values); }\n    void append(std::vector<T>&&\
    \ values) { insert(size(), std::move(values)); }\n    void append(const RollbackDynamicArray&\
    \ other) { insert(size(), other); }\n    void append(const DynamicArray<T>& other)\
    \ { insert(size(), other); }\n\n    void erase(int pos) { erase(pos, pos + 1);\
    \ }\n\n    void erase(int left, int right) {\n        assert(0 <= left && left\
    \ <= right && right <= size());\n        Entry entry{Kind::erase, left, 0, 0,\
    \ std::nullopt, {}};\n        if (!_checkpoints.empty()) entry.values = _data.to_vector(left,\
    \ right);\n        _data.erase(left, right);\n        if (!_checkpoints.empty())\
    \ _history.push_back(std::move(entry));\n    }\n\n    void pop_back() {\n    \
    \    assert(!empty());\n        erase(size() - 1);\n    }\n\n    void pop_front()\
    \ {\n        assert(!empty());\n        erase(0);\n    }\n\n    const T& at(int\
    \ pos) const { return _data.at(pos); }\n    const T& operator[](int pos) const\
    \ { return _data[pos]; }\n    const T& front() const { return _data.front(); }\n\
    \    const T& back() const { return _data.back(); }\n    T get(int pos) const\
    \ { return _data.get(pos); }\n\n    void set(int pos, T value) {\n        Entry\
    \ entry{Kind::set, pos, 0, 0, std::nullopt, {}};\n        if (!_checkpoints.empty())\
    \ entry.value.emplace(_data.get(pos));\n        _data.set(pos, std::move(value));\n\
    \        if (!_checkpoints.empty()) _history.push_back(std::move(entry));\n  \
    \  }\n\n    void set_inplace(int pos, T value) { set(pos, std::move(value)); }\n\
    \n    void reverse(int left, int right) {\n        _data.reverse(left, right);\n\
    \        if (!_checkpoints.empty()) {\n            _history.push_back(Entry{Kind::reverse,\
    \ left, right, 0, std::nullopt, {}});\n        }\n    }\n\n    void reverse()\
    \ { reverse(0, size()); }\n\n    void rotate(int left, int middle, int right)\
    \ {\n        _data.rotate(left, middle, right);\n        if (!_checkpoints.empty())\
    \ {\n            _history.push_back(Entry{Kind::rotate, left, middle, right, std::nullopt,\
    \ {}});\n        }\n    }\n\n    std::vector<T> to_vector() const { return _data.to_vector();\
    \ }\n    std::vector<T> to_vector(int left, int right) const { return _data.to_vector(left,\
    \ right); }\n\n    std::pair<DynamicArray<T>, DynamicArray<T>> split(int pos)\
    \ const {\n        assert(0 <= pos && pos <= size());\n        DynamicArray<T>\
    \ left = _data;\n        DynamicArray<T> right = left.split_off(pos);\n      \
    \  return {std::move(left), std::move(right)};\n    }\n\n    DynamicArray<T> split_off(int\
    \ pos) const {\n        return split(pos).second;\n    }\n\n    int snapshot()\
    \ { _checkpoints.push_back(_history.size()); return int(_checkpoints.size());\
    \ }\n    int snapshot_count() const { return int(_checkpoints.size()); }\n\n \
    \   void reserve_snapshots(int count) {\n        assert(0 <= count);\n       \
    \ _checkpoints.reserve(count);\n    }\n\n   private:\n    void restore_one() {\n\
    \        Entry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.kind == Kind::insert) {\n            _data.erase(entry.first,\
    \ entry.first + entry.second);\n        } else if (entry.kind == Kind::erase)\
    \ {\n            _data.insert(entry.first, std::move(entry.values));\n       \
    \ } else if (entry.kind == Kind::set) {\n            _data.set(entry.first, std::move(*entry.value));\n\
    \        } else if (entry.kind == Kind::reverse) {\n            _data.reverse(entry.first,\
    \ entry.second);\n        } else if (entry.kind == Kind::rotate) {\n         \
    \   int new_middle = entry.first + entry.third - entry.second;\n            _data.rotate(entry.first,\
    \ new_middle, entry.third);\n        } else {\n            _data.insert(0, std::move(entry.values));\n\
    \        }\n    }\n\n   public:\n\n    void rollback(int state) {\n        assert(1\
    \ <= state && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() { _history.clear(); _checkpoints.clear(); }\n\n    void release()\
    \ {\n        _data.clear();\n        _history.clear();\n        _checkpoints.clear();\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\
    \n\n\n\n#line 9 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\n\
    #include <type_traits>\n#line 12 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\
    \n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
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
    \n\n#line 1 \"ds/detail/rollback_journal.hpp\"\n\n\n\n#line 8 \"ds/detail/rollback_journal.hpp\"\
    \n#include <limits>\n#line 11 \"ds/detail/rollback_journal.hpp\"\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ntemplate <class Node>\nstruct\
    \ RollbackJournal {\n    struct Change {\n        int index;\n        Node value;\n\
    \    };\n\n    struct Checkpoint {\n        std::size_t change_size;\n       \
    \ std::size_t node_size;\n        std::uint64_t epoch;\n    };\n\n    std::vector<Node>\
    \ nodes;\n    std::vector<Change> changes;\n    std::vector<Checkpoint> checkpoints;\n\
    \    std::vector<std::uint64_t> saved_epoch;\n    std::uint64_t next_epoch = 1;\n\
    \n    std::uint64_t new_epoch() {\n        if (next_epoch == 0) {\n          \
    \  std::fill(saved_epoch.begin(), saved_epoch.end(), 0);\n            next_epoch\
    \ = 1;\n        }\n        return next_epoch++;\n    }\n\n    int size() const\
    \ { return int(nodes.size()); }\n\n    Node& operator[](int index) { return nodes[index];\
    \ }\n    const Node& operator[](int index) const { return nodes[index]; }\n\n\
    \    template <class... Args>\n    int emplace(Args&&... args) {\n        assert(nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        int index = int(nodes.size());\n\
    \        nodes.emplace_back(std::forward<Args>(args)...);\n        saved_epoch.push_back(0);\n\
    \        return index;\n    }\n\n    int snapshot() {\n        assert(checkpoints.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        checkpoints.push_back(Checkpoint{changes.size(),\
    \ nodes.size(), new_epoch()});\n        return int(checkpoints.size());\n    }\n\
    \n    void touch(int index) {\n        assert(0 <= index && index < size());\n\
    \        if (checkpoints.empty()) return;\n        const Checkpoint& checkpoint\
    \ = checkpoints.back();\n        if (std::size_t(index) >= checkpoint.node_size)\
    \ return;\n        if (saved_epoch[index] == checkpoint.epoch) return;\n     \
    \   saved_epoch[index] = checkpoint.epoch;\n        changes.push_back(Change{index,\
    \ nodes[index]});\n    }\n\n    int snapshot_count() const { return int(checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        checkpoints.reserve(count);\n    }\n\n    void reserve_changes(std::size_t\
    \ count) { changes.reserve(count); }\n\n    void rollback(int state) {\n     \
    \   assert(1 <= state && state <= snapshot_count());\n        Checkpoint checkpoint\
    \ = checkpoints[state - 1];\n        while (changes.size() > checkpoint.change_size)\
    \ {\n            Change change = std::move(changes.back());\n            changes.pop_back();\n\
    \            nodes[change.index] = std::move(change.value);\n        }\n     \
    \   nodes.erase(nodes.begin() + checkpoint.node_size, nodes.end());\n        saved_epoch.resize(checkpoint.node_size);\n\
    \        checkpoints.resize(state);\n        checkpoints.back().change_size =\
    \ changes.size();\n        checkpoints.back().node_size = nodes.size();\n    \
    \    checkpoints.back().epoch = new_epoch();\n    }\n\n    void clear_history()\
    \ {\n        changes.clear();\n        checkpoints.clear();\n        std::fill(saved_epoch.begin(),\
    \ saved_epoch.end(), 0);\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        changes.clear();\n        checkpoints.clear();\n        saved_epoch.clear();\n\
    \        next_epoch = 1;\n    }\n};\n\n}  // namespace detail\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 15 \"ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct RollbackDynamicLazyMonoidArray {\n    using T = typename\
    \ ActedMonoid::value_type;\n    using F = typename ActedMonoid::operator_type;\n\
    \n   private:\n    static constexpr bool value_commutative = [] {\n        if\
    \ constexpr (requires { ActedMonoid::commutative; }) {\n            return bool(ActedMonoid::commutative);\n\
    \        } else {\n            return false;\n        }\n    }();\n\n    struct\
    \ EmptyReverseProduct {};\n    using ReverseProduct = std::conditional_t<value_commutative,\
    \ EmptyReverseProduct, T>;\n\n    static constexpr bool count_stored_in_value\
    \ = requires(const T& value) {\n        { ActedMonoid::size(value) } -> std::convertible_to<int>;\n\
    \    };\n\n    struct EmptyCount {};\n    using Count = std::conditional_t<count_stored_in_value,\
    \ EmptyCount, int>;\n\n    static ReverseProduct make_reverse_product(const T&\
    \ value) {\n        if constexpr (value_commutative) {\n            return {};\n\
    \        } else {\n            return value;\n        }\n    }\n\n    static Count\
    \ make_count(int count) {\n        if constexpr (count_stored_in_value) {\n  \
    \          return {};\n        } else {\n            return count;\n        }\n\
    \    }\n\n    struct Node {\n        T val;\n        T prod;\n        [[no_unique_address]]\
    \ ReverseProduct rprod;\n        F lazy;\n        std::uint32_t priority : 30;\n\
    \        std::uint32_t rev : 1;\n        std::uint32_t has_lazy : 1;\n       \
    \ [[no_unique_address]] Count count;\n        int l, r;\n\n        Node()\n  \
    \          : val(ActedMonoid::id()),\n              prod(ActedMonoid::id()),\n\
    \              rprod(make_reverse_product(prod)),\n              lazy(ActedMonoid::op_id()),\n\
    \              priority(0),\n              rev(false),\n              has_lazy(false),\n\
    \              count(make_count(0)),\n              l(0),\n              r(0)\
    \ {}\n\n        Node(T value, int node_priority)\n            : val(std::move(value)),\n\
    \              prod(val),\n              rprod(make_reverse_product(val)),\n \
    \             lazy(ActedMonoid::op_id()),\n              priority(std::uint32_t(node_priority)),\n\
    \              rev(false),\n              has_lazy(false),\n              count(make_count(1)),\n\
    \              l(0),\n              r(0) {}\n    };\n\n    detail::RollbackJournal<Node>\
    \ _journal;\n    struct StateCheckpoint { int root; int free_head; };\n    std::vector<StateCheckpoint>\
    \ _state_checkpoints;\n    int root;\n    int free_head;\n    std::uint32_t rng_state;\n\
    \n    int node_count(int t) const {\n        if constexpr (count_stored_in_value)\
    \ {\n            return int(ActedMonoid::size(_journal[t].prod));\n        } else\
    \ {\n            return _journal[t].count;\n        }\n    }\n\n    void set_node_count(int\
    \ t, int count) {\n        _journal.touch(t);\n        if constexpr (!count_stored_in_value)\
    \ {\n            _journal[t].count = count;\n        }\n    }\n\n    template\
    \ <typename U>\n    static T make_value(const U& value) {\n        if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n            return ActedMonoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    static T mapping_at(const F& f, const T& value, long long ord) {\n     \
    \   if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x,\
    \ i); }) {\n            return ActedMonoid::mapping(f, value, ord);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static F shift_operator(const F& f, long long ord) {\n        if constexpr\
    \ (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {\n          \
    \  return ActedMonoid::op_shift(f, ord);\n        } else {\n            return\
    \ f;\n        }\n    }\n\n    static F reverse_operator(const F& f, long long\
    \ size) {\n        if constexpr (requires(F g, long long n) { ActedMonoid::op_reverse(g,\
    \ n); }) {\n            return ActedMonoid::op_reverse(f, size);\n        } else\
    \ {\n            return f;\n        }\n    }\n\n    int new_node(T value) {\n\
    \        int priority = next_priority();\n        if (free_head) {\n         \
    \   int res = free_head;\n            _journal.touch(res);\n            free_head\
    \ = _journal[res].l;\n            _journal[res] = Node(std::move(value), priority);\n\
    \            return res;\n        }\n        _journal.emplace(std::move(value),\
    \ priority);\n        return int(_journal.nodes.size()) - 1;\n    }\n\n    void\
    \ release_node(int t) {\n        _journal.touch(t);\n        _journal[t].l = free_head;\n\
    \        free_head = t;\n    }\n\n    int next_priority() {\n        rng_state\
    \ ^= rng_state << 13;\n        rng_state ^= rng_state >> 17;\n        rng_state\
    \ ^= rng_state << 5;\n        return int(rng_state);\n    }\n\n    void update(int\
    \ t) {\n        if (!t) return;\n        _journal.touch(t);\n        int l = _journal[t].l;\n\
    \        int r = _journal[t].r;\n        set_node_count(t, 1 + node_count(l) +\
    \ node_count(r));\n        _journal[t].prod = ActedMonoid::op(ActedMonoid::op(_journal[l].prod,\
    \ _journal[t].val), _journal[r].prod);\n        if constexpr (!value_commutative)\
    \ {\n            _journal[t].rprod = ActedMonoid::op(ActedMonoid::op(_journal[r].rprod,\
    \ _journal[t].val), _journal[l].rprod);\n        }\n    }\n\n    void all_apply(int\
    \ t, const F& f) {\n        if (!t) return;\n        _journal.touch(t);\n    \
    \    int left_count = node_count(_journal[t].l);\n        _journal[t].val = mapping_at(f,\
    \ _journal[t].val, left_count);\n        _journal[t].prod = mapping_at(f, _journal[t].prod,\
    \ 0);\n        if constexpr (!value_commutative) {\n            _journal[t].rprod\
    \ = mapping_at(reverse_operator(f, node_count(t)), _journal[t].rprod, 0);\n  \
    \      }\n        _journal[t].lazy = ActedMonoid::op_comp(f, _journal[t].lazy);\n\
    \        _journal[t].has_lazy = true;\n    }\n\n    void apply_reverse(int t)\
    \ {\n        if (!t) return;\n        _journal.touch(t);\n        std::swap(_journal[t].l,\
    \ _journal[t].r);\n        _journal[t].rev = !_journal[t].rev;\n        if constexpr\
    \ (!value_commutative) {\n            std::swap(_journal[t].prod, _journal[t].rprod);\n\
    \        }\n        if (_journal[t].has_lazy) {\n            _journal[t].lazy\
    \ = reverse_operator(_journal[t].lazy, node_count(t));\n        }\n    }\n\n \
    \   void push(int t) {\n        if (!t) return;\n        _journal.touch(t);\n\
    \        if (_journal[t].rev) {\n            apply_reverse(_journal[t].l);\n \
    \           apply_reverse(_journal[t].r);\n            _journal[t].rev = false;\n\
    \        }\n        if (_journal[t].has_lazy) {\n            all_apply(_journal[t].l,\
    \ _journal[t].lazy);\n            all_apply(_journal[t].r, shift_operator(_journal[t].lazy,\
    \ node_count(_journal[t].l) + 1));\n            _journal[t].lazy = ActedMonoid::op_id();\n\
    \            _journal[t].has_lazy = false;\n        }\n    }\n\n    void split(int\
    \ t, int pos, int& l, int& r) {\n        if (!t) {\n            l = r = 0;\n \
    \           return;\n        }\n        if (pos == 0) {\n            l = 0;\n\
    \            r = t;\n            return;\n        }\n        if (pos == node_count(t))\
    \ {\n            l = t;\n            r = 0;\n            return;\n        }\n\
    \        _journal.touch(t);\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        if (pos == left_count) {\n            l = _journal[t].l;\n          \
    \  _journal[t].l = 0;\n            update(t);\n            r = t;\n          \
    \  return;\n        }\n        if (pos == left_count + 1) {\n            r = _journal[t].r;\n\
    \            _journal[t].r = 0;\n            update(t);\n            l = t;\n\
    \            return;\n        }\n        if (pos <= left_count) {\n          \
    \  split(_journal[t].l, pos, l, _journal[t].l);\n            r = t;\n        }\
    \ else {\n            split(_journal[t].r, pos - left_count - 1, _journal[t].r,\
    \ r);\n            l = t;\n        }\n        update(t);\n    }\n\n    int merge(int\
    \ l, int r) {\n        if (!l || !r) return l ? l : r;\n        if (_journal[l].priority\
    \ > _journal[r].priority) {\n            push(l);\n            _journal.touch(l);\n\
    \            if (_journal[l].r) {\n                _journal[l].r = merge(_journal[l].r,\
    \ r);\n            } else {\n                _journal[l].r = r;\n            }\n\
    \            update(l);\n            return l;\n        } else {\n           \
    \ push(r);\n            _journal.touch(r);\n            if (_journal[r].l) {\n\
    \                _journal[r].l = merge(l, _journal[r].l);\n            } else\
    \ {\n                _journal[r].l = l;\n            }\n            update(r);\n\
    \            return r;\n        }\n    }\n\n    void split_three(int t, int ql,\
    \ int qr, int& a, int& b, int& c) {\n        if (ql == qr) {\n            split(t,\
    \ ql, a, c);\n            b = 0;\n            return;\n        }\n        if (ql\
    \ == 0 && qr == node_count(t)) {\n            a = c = 0;\n            b = t;\n\
    \            return;\n        }\n        _journal.touch(t);\n        push(t);\n\
    \        int left_count = node_count(_journal[t].l);\n        if (qr <= left_count)\
    \ {\n            split_three(_journal[t].l, ql, qr, a, b, _journal[t].l);\n  \
    \          c = t;\n            update(t);\n        } else if (left_count < ql)\
    \ {\n            split_three(_journal[t].r, ql - left_count - 1, qr - left_count\
    \ - 1, _journal[t].r, b, c);\n            a = t;\n            update(t);\n   \
    \     } else {\n            split(_journal[t].l, ql, a, _journal[t].l);\n    \
    \        split(_journal[t].r, qr - left_count - 1, _journal[t].r, c);\n      \
    \      b = t;\n            update(t);\n        }\n    }\n\n    int merge_three(int\
    \ a, int b, int c) {\n        if (!a) return merge(b, c);\n        if (!b) return\
    \ merge(a, c);\n        if (!c) return merge(a, b);\n        std::uint32_t pa\
    \ = _journal[a].priority;\n        std::uint32_t pb = _journal[b].priority;\n\
    \        std::uint32_t pc = _journal[c].priority;\n        if (pb >= pa && pb\
    \ >= pc) {\n            push(b);\n            _journal.touch(b);\n           \
    \ _journal[b].l = merge(a, _journal[b].l);\n            _journal[b].r = merge(_journal[b].r,\
    \ c);\n            update(b);\n            return b;\n        }\n        if (pa\
    \ >= pc) {\n            push(a);\n            _journal.touch(a);\n           \
    \ _journal[a].r = merge_three(_journal[a].r, b, c);\n            update(a);\n\
    \            return a;\n        }\n        push(c);\n        _journal.touch(c);\n\
    \        _journal[c].l = merge_three(a, b, _journal[c].l);\n        update(c);\n\
    \        return c;\n    }\n\n    int insert_node(int t, int pos, int node) {\n\
    \        if (!t) return node;\n        if (_journal[node].priority > _journal[t].priority)\
    \ {\n            _journal.touch(node);\n            split(t, pos, _journal[node].l,\
    \ _journal[node].r);\n            update(node);\n            return node;\n  \
    \      }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos <= left_count) {\n           \
    \ _journal[t].l = insert_node(_journal[t].l, pos, node);\n        } else {\n \
    \           _journal[t].r = insert_node(_journal[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            _journal[t].l\
    \ = erase_node(_journal[t].l, pos);\n            update(t);\n            return\
    \ t;\n        }\n        if (pos == left_count) {\n            int res = merge(_journal[t].l,\
    \ _journal[t].r);\n            release_node(t);\n            return res;\n   \
    \     }\n        _journal[t].r = erase_node(_journal[t].r, pos - left_count -\
    \ 1);\n        update(t);\n        return t;\n    }\n\n    void set_node(int t,\
    \ int pos, T value) {\n        push(t);\n        _journal.touch(t);\n        int\
    \ left_count = node_count(_journal[t].l);\n        if (pos < left_count) {\n \
    \           set_node(_journal[t].l, pos, std::move(value));\n        } else if\
    \ (pos == left_count) {\n            _journal[t].val = std::move(value);\n   \
    \     } else {\n            set_node(_journal[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    void apply_node(int t, int pos, const\
    \ F& f) {\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (pos < left_count) {\n            apply_node(_journal[t].l,\
    \ pos, f);\n        } else if (pos == left_count) {\n            _journal[t].val\
    \ = mapping_at(f, _journal[t].val, 0);\n        } else {\n            apply_node(_journal[t].r,\
    \ pos - left_count - 1, f);\n        }\n        update(t);\n    }\n\n    void\
    \ apply_range(int t, int ql, int qr, const F& f) {\n        if (ql == 0 && qr\
    \ == node_count(t)) {\n            all_apply(t, f);\n            return;\n   \
    \     }\n        push(t);\n        _journal.touch(t);\n        int left_count\
    \ = node_count(_journal[t].l);\n        if (qr <= left_count) {\n            apply_range(_journal[t].l,\
    \ ql, qr, f);\n        } else if (left_count < ql) {\n            apply_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1, f);\n        } else {\n          \
    \  if (ql < left_count) {\n                apply_range(_journal[t].l, ql, left_count,\
    \ f);\n            }\n            _journal[t].val = mapping_at(f, _journal[t].val,\
    \ left_count - ql);\n            if (left_count + 1 < qr) {\n                apply_range(_journal[t].r,\
    \ 0, qr - left_count - 1,\n                            shift_operator(f, left_count\
    \ + 1 - ql));\n            }\n        }\n        update(t);\n    }\n\n    T prod_range(int\
    \ t, int ql, int qr) {\n        if (ql == 0 && qr == node_count(t)) return _journal[t].prod;\n\
    \        push(t);\n        int left_count = node_count(_journal[t].l);\n     \
    \   if (qr <= left_count) {\n            return prod_range(_journal[t].l, ql,\
    \ qr);\n        }\n        if (left_count < ql) {\n            return prod_range(_journal[t].r,\
    \ ql - left_count - 1, qr - left_count - 1);\n        }\n        T res = _journal[t].val;\n\
    \        if (ql < left_count) {\n            res = ActedMonoid::op(prod_range(_journal[t].l,\
    \ ql, left_count), res);\n        }\n        if (left_count + 1 < qr) {\n    \
    \        res = ActedMonoid::op(res, prod_range(_journal[t].r, 0, qr - left_count\
    \ - 1));\n        }\n        return res;\n    }\n\n    int find_node(int t, int\
    \ pos) {\n        while (t) {\n            push(t);\n            int left_count\
    \ = node_count(_journal[t].l);\n            if (pos < left_count) {\n        \
    \        t = _journal[t].l;\n            } else if (pos == left_count) {\n   \
    \             return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = _journal[t].r;\n            }\n        }\n       \
    \ return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>& res) {\n      \
    \  if (!t) return;\n        push(t);\n        dump_dfs(_journal[t].l, res);\n\
    \        res.push_back(_journal[t].val);\n        dump_dfs(_journal[t].r, res);\n\
    \        update(t);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res) {\n        if (!t || qr <= offset || offset + node_count(t)\
    \ <= ql) return;\n        push(t);\n        int left_count = node_count(_journal[t].l);\n\
    \        int node_pos = offset + left_count;\n        dump_range_dfs(_journal[t].l,\
    \ ql, qr, offset, res);\n        if (ql <= node_pos && node_pos < qr) {\n    \
    \        res.push_back(_journal[t].val);\n        }\n        dump_range_dfs(_journal[t].r,\
    \ ql, qr, node_pos + 1, res);\n        update(t);\n    }\n\n    int clone_subtree_from(const\
    \ RollbackDynamicLazyMonoidArray& other, int t) {\n        if (!t) return 0;\n\
    \        Node source = other._journal[t];\n        int res = int(_journal.nodes.size());\n\
    \        _journal.emplace(std::move(source));\n        _journal[res].l = clone_subtree_from(other,\
    \ other._journal[t].l);\n        _journal[res].r = clone_subtree_from(other, other._journal[t].r);\n\
    \        return res;\n    }\n\n    void update_dfs(int t) {\n        if (!t) return;\n\
    \        update_dfs(_journal[t].l);\n        update_dfs(_journal[t].r);\n    \
    \    update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n   \
    \     if (first == last) return 0;\n        std::vector<int> stack;\n        stack.reserve(last\
    \ - first);\n        for (int i = first; i < last; i++) {\n            int left_child\
    \ = 0;\n            while (!stack.empty() && _journal[stack.back()].priority <\
    \ _journal[i].priority) {\n                left_child = stack.back();\n      \
    \          stack.pop_back();\n            }\n            _journal[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                _journal[stack.back()].r =\
    \ i;\n            }\n            stack.push_back(i);\n        }\n        int res\
    \ = stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n \
    \   int build_from_vector(const std::vector<T>& v) {\n        int saved_free_head\
    \ = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const T& x : v) {\n            new_node(x);\n        }\n        int result\
    \ = build_cartesian(first, int(_journal.nodes.size()));\n        free_head = saved_free_head;\n\
    \        return result;\n    }\n\n    int build_from_vector(std::vector<T>&& v)\
    \ {\n        int saved_free_head = std::exchange(free_head, 0);\n        int first\
    \ = int(_journal.nodes.size());\n        _journal.nodes.reserve(_journal.nodes.size()\
    \ + v.size());\n        for (T& x : v) {\n            new_node(std::move(x));\n\
    \        }\n        int result = build_cartesian(first, int(_journal.nodes.size()));\n\
    \        free_head = saved_free_head;\n        return result;\n    }\n\n    template\
    \ <typename U>\n    int build_from_values(const std::vector<U>& v) {\n       \
    \ int saved_free_head = std::exchange(free_head, 0);\n        int first = int(_journal.nodes.size());\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        for\
    \ (const U& x : v) {\n            new_node(make_value(x));\n        }\n      \
    \  int result = build_cartesian(first, int(_journal.nodes.size()));\n        free_head\
    \ = saved_free_head;\n        return result;\n    }\n\n    void release_subtree(int\
    \ t) {\n        if (!t) return;\n        std::vector<int> stack(1, t);\n     \
    \   while (!stack.empty()) {\n            int node = stack.back();\n         \
    \   stack.pop_back();\n            int left = _journal[node].l;\n            int\
    \ right = _journal[node].r;\n            if (left) stack.push_back(left);\n  \
    \          if (right) stack.push_back(right);\n            release_node(node);\n\
    \        }\n    }\n\n    void reset_to_empty() {\n        _journal.clear();\n\
    \        _journal.emplace();\n        root = 0;\n        _state_checkpoints.clear();\n\
    \        free_head = 0;\n    }\n\n   public:\n    RollbackDynamicLazyMonoidArray()\n\
    \        : root(0),\n          free_head(0),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        _journal.emplace();\n        if (rng_state == 0) rng_state = 1;\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(const RollbackDynamicLazyMonoidArray&\
    \ other)\n        : root(other.root), free_head(other.free_head), rng_state(other.rng_state)\
    \ {\n        _journal.nodes = other._journal.nodes;\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n    }\n\n    RollbackDynamicLazyMonoidArray(RollbackDynamicLazyMonoidArray&&\
    \ other) noexcept\n        : _journal(std::move(other._journal)),\n          _state_checkpoints(std::move(other._state_checkpoints)),\n\
    \          root(other.root),\n          free_head(other.free_head),\n        \
    \  rng_state(other.rng_state) {\n        other.reset_to_empty();\n    }\n\n  \
    \  RollbackDynamicLazyMonoidArray& operator=(const RollbackDynamicLazyMonoidArray&\
    \ other) {\n        if (this != &other) {\n            _journal.nodes = other._journal.nodes;\n\
    \            _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n        \
    \    _journal.changes.clear();\n            _journal.checkpoints.clear();\n  \
    \          _state_checkpoints.clear();\n            root = other.root;\n     \
    \       free_head = other.free_head;\n            rng_state = other.rng_state;\n\
    \        }\n        return *this;\n    }\n\n    RollbackDynamicLazyMonoidArray&\
    \ operator=(RollbackDynamicLazyMonoidArray&& other) noexcept {\n        if (this\
    \ != &other) {\n            _journal = std::move(other._journal);\n          \
    \  _state_checkpoints = std::move(other._state_checkpoints);\n            root\
    \ = other.root;\n            free_head = other.free_head;\n            rng_state\
    \ = other.rng_state;\n            other.reset_to_empty();\n        }\n       \
    \ return *this;\n    }\n\n    explicit RollbackDynamicLazyMonoidArray(int n)\n\
    \        : RollbackDynamicLazyMonoidArray(n, ActedMonoid::id()) {}\n\n    RollbackDynamicLazyMonoidArray(int\
    \ n, const T& value) : RollbackDynamicLazyMonoidArray() {\n        assert(0 <=\
    \ n);\n        _journal.nodes.reserve(n + 1);\n        int first = int(_journal.nodes.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(_journal.nodes.size()));\n    }\n\
    \n    explicit RollbackDynamicLazyMonoidArray(const std::vector<T>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(v);\n\
    \    }\n\n    explicit RollbackDynamicLazyMonoidArray(std::vector<T>&& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)\n   \
    \ explicit RollbackDynamicLazyMonoidArray(const std::vector<U>& v) : RollbackDynamicLazyMonoidArray()\
    \ {\n        _journal.nodes.reserve(v.size() + 1);\n        root = build_from_values(v);\n\
    \    }\n\n    RollbackDynamicLazyMonoidArray(std::initializer_list<T> init) :\
    \ RollbackDynamicLazyMonoidArray() {\n        _journal.nodes.reserve(init.size()\
    \ + 1);\n        for (const T& x : init) push_back(x);\n    }\n\n    int size()\
    \ const {\n        return node_count(root);\n    }\n\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ capacity) {\n        _journal.nodes.reserve(capacity + 1);\n        _journal.saved_epoch.reserve(capacity\
    \ + 1);\n    }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\
    \n    void clear() {\n        release_subtree(root);\n        root = 0;\n    }\n\
    \n    void insert(int pos, T value) {\n        assert(0 <= pos && pos <= size());\n\
    \        root = insert_node(root, pos, new_node(std::move(value)));\n    }\n\n\
    \    void insert(int pos, const std::vector<T>& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        _journal.nodes.reserve(_journal.nodes.size() + v.size());\n\
    \        int mid = build_from_vector(v);\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::vector<T>&& v) {\n        assert(0 <= pos && pos <= size());\n   \
    \     _journal.nodes.reserve(_journal.nodes.size() + v.size());\n        int mid\
    \ = build_from_vector(std::move(v));\n        int l, r;\n        split(root, pos,\
    \ l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const RollbackDynamicLazyMonoidArray& other)\
    \ {\n        assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n\
    \        _journal.nodes.reserve(_journal.nodes.size() + other.size());\n     \
    \   int mid = clone_subtree_from(other, other.root);\n        int l, r;\n    \
    \    split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\
    \n    void push_back(T value) {\n        insert(size(), std::move(value));\n \
    \   }\n\n    void push_front(T value) {\n        insert(0, std::move(value));\n\
    \    }\n\n    void append(const std::vector<T>& v) {\n        insert(size(), v);\n\
    \    }\n\n    void append(std::vector<T>&& v) {\n        insert(size(), std::move(v));\n\
    \    }\n\n    void append(const RollbackDynamicLazyMonoidArray& other) {\n   \
    \     insert(size(), other);\n    }\n\n    void erase(int pos) {\n        assert(0\
    \ <= pos && pos < size());\n        root = erase_node(root, pos);\n    }\n\n \
    \   void erase(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split_three(root,\
    \ l, r, a, b, c);\n        release_subtree(b);\n        root = merge(a, c);\n\
    \    }\n\n    void pop_back() {\n        assert(!empty());\n        erase(size()\
    \ - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n        erase(0);\n\
    \    }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < size());\n  \
    \      int t = find_node(root, pos);\n        return _journal[t].val;\n    }\n\
    \n    T operator[](int pos) {\n        return get(pos);\n    }\n\n    T front()\
    \ {\n        assert(!empty());\n        return get(0);\n    }\n\n    T back()\
    \ {\n        assert(!empty());\n        return get(size() - 1);\n    }\n\n   \
    \ void set(int pos, T value) {\n        assert(0 <= pos && pos < size());\n  \
    \      set_node(root, pos, std::move(value));\n    }\n\n    void reverse(int l,\
    \ int r) {\n        assert(0 <= l && l <= r && r <= size());\n        if (l ==\
    \ r) return;\n        int a, b, c;\n        split_three(root, l, r, a, b, c);\n\
    \        apply_reverse(b);\n        root = merge_three(a, b, c);\n    }\n\n  \
    \  void reverse() {\n        apply_reverse(root);\n    }\n\n    void rotate(int\
    \ l, int m, int r) {\n        assert(0 <= l && l <= m && m <= r && r <= size());\n\
    \        if (l == m || m == r) return;\n        int a, b, c, d;\n        split(root,\
    \ l, a, b);\n        split(b, m - l, b, c);\n        split(c, r - m, c, d);\n\
    \        root = merge(merge(a, c), merge(b, d));\n    }\n\n    void apply(int\
    \ pos, const F& f) {\n        assert(0 <= pos && pos < size());\n        apply_node(root,\
    \ pos, f);\n    }\n\n    void apply(int l, int r, const F& f) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        apply_range(root,\
    \ l, r, f);\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <=\
    \ r && r <= size());\n        if (l == r) return ActedMonoid::id();\n        return\
    \ prod_range(root, l, r);\n    }\n\n    T all_prod() const {\n        return _journal[root].prod;\n\
    \    }\n\n    std::vector<T> to_vector() {\n        std::vector<T> res;\n    \
    \    res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n\
    \    }\n\n    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l\
    \ && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    RollbackDynamicLazyMonoidArray split_off(int pos) {\n        assert(0\
    \ <= pos && pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n\
    \        root = l;\n\n        RollbackDynamicLazyMonoidArray res;\n        res._journal.nodes.reserve(node_count(r)\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        release_subtree(r);\n\
    \        return res;\n    }\n\n    void set_inplace(int pos, T value) { set(pos,\
    \ std::move(value)); }\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() {\n        int state = _journal.snapshot();\n\
    \        _state_checkpoints.push_back(StateCheckpoint{root, free_head});\n   \
    \     assert(state == int(_state_checkpoints.size()));\n        return state;\n\
    \    }\n    int snapshot_count() const { return int(_state_checkpoints.size());\
    \ }\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n  \
    \      _journal.reserve_snapshots(count);\n        _state_checkpoints.reserve(count);\n\
    \    }\n    void rollback(int state) {\n        assert(1 <= state && state <=\
    \ snapshot_count());\n        StateCheckpoint checkpoint = _state_checkpoints[state\
    \ - 1];\n        _journal.rollback(state);\n        root = checkpoint.root;\n\
    \        free_head = checkpoint.free_head;\n        _state_checkpoints.resize(state);\n\
    \    }\n    void clear_history() {\n        _journal.clear_history();\n      \
    \  _state_checkpoints.clear();\n    }\n    void release() { reset_to_empty();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/dynamic_array/rollback_dynamic_monoid_array.hpp\"\
    \n\n\n\n#line 10 \"ds/dynamic_array/rollback_dynamic_monoid_array.hpp\"\n\n#line\
    \ 1 \"ds/dynamic_array/dynamic_monoid_array.hpp\"\n\n\n\n#line 11 \"ds/dynamic_array/dynamic_monoid_array.hpp\"\
    \n\n#line 13 \"ds/dynamic_array/dynamic_monoid_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct DynamicMonoidArray\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Node\
    \ {\n        T val;\n        T prod;\n        T rprod;\n        int priority;\n\
    \        int count;\n        int l, r;\n        bool rev;\n\n        Node()\n\
    \            : val(Monoid::id()),\n              prod(Monoid::id()),\n       \
    \       rprod(Monoid::id()),\n              priority(0),\n              count(0),\n\
    \              l(0),\n              r(0),\n              rev(false) {}\n\n   \
    \     Node(T value, int node_priority)\n            : val(std::move(value)), prod(val),\
    \ rprod(val), priority(node_priority), count(1), l(0), r(0), rev(false) {}\n \
    \   };\n\n    std::vector<Node> pool;\n    int root;\n    std::uint32_t rng_state;\n\
    \n    template <typename U>\n    static T make_value(const U& value) {\n     \
    \   if constexpr (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else {\n            return static_cast<T>(value);\n        }\n    }\n\
    \n    int new_node(T value) {\n        pool.push_back(Node(std::move(value), next_priority()));\n\
    \        return int(pool.size()) - 1;\n    }\n\n    int next_priority() {\n  \
    \      rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >> 17;\n\
    \        rng_state ^= rng_state << 5;\n        return int(rng_state);\n    }\n\
    \n    void update(int t) {\n        if (!t) return;\n        int l = pool[t].l;\n\
    \        int r = pool[t].r;\n        pool[t].count = 1 + pool[l].count + pool[r].count;\n\
    \        pool[t].prod = Monoid::op(Monoid::op(pool[l].prod, pool[t].val), pool[r].prod);\n\
    \        pool[t].rprod = Monoid::op(Monoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);\n\
    \    }\n\n    void apply_reverse(int t) {\n        if (!t) return;\n        pool[t].rev\
    \ = !pool[t].rev;\n        std::swap(pool[t].prod, pool[t].rprod);\n    }\n\n\
    \    void push(int t) {\n        if (!t || !pool[t].rev) return;\n        std::swap(pool[t].l,\
    \ pool[t].r);\n        apply_reverse(pool[t].l);\n        apply_reverse(pool[t].r);\n\
    \        pool[t].rev = false;\n    }\n\n    void split(int t, int pos, int& l,\
    \ int& r) {\n        if (!t) {\n            l = r = 0;\n            return;\n\
    \        }\n        if (pos == 0) {\n            l = 0;\n            r = t;\n\
    \            return;\n        }\n        if (pos == pool[t].count) {\n       \
    \     l = t;\n            r = 0;\n            return;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos == left_count)\
    \ {\n            l = pool[t].l;\n            pool[t].l = 0;\n            update(t);\n\
    \            r = t;\n            return;\n        }\n        if (pos == left_count\
    \ + 1) {\n            r = pool[t].r;\n            pool[t].r = 0;\n           \
    \ update(t);\n            l = t;\n            return;\n        }\n        if (pos\
    \ <= left_count) {\n            split(pool[t].l, pos, l, pool[t].l);\n       \
    \     r = t;\n        } else {\n            split(pool[t].r, pos - left_count\
    \ - 1, pool[t].r, r);\n            l = t;\n        }\n        update(t);\n   \
    \ }\n\n    int merge(int l, int r) {\n        if (!l || !r) return l ? l : r;\n\
    \        if (pool[l].priority > pool[r].priority) {\n            push(l);\n  \
    \          if (pool[l].r) {\n                pool[l].r = merge(pool[l].r, r);\n\
    \            } else {\n                pool[l].r = r;\n            }\n       \
    \     update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    int insert_node(int\
    \ t, int pos, int node) {\n        if (!t) return node;\n        if (pool[node].priority\
    \ > pool[t].priority) {\n            split(t, pos, pool[node].l, pool[node].r);\n\
    \            update(node);\n            return node;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos <= left_count)\
    \ {\n            pool[t].l = insert_node(pool[t].l, pos, node);\n        } else\
    \ {\n            pool[t].r = insert_node(pool[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            pool[t].l = erase_node(pool[t].l,\
    \ pos);\n            update(t);\n            return t;\n        }\n        if\
    \ (pos == left_count) {\n            return merge(pool[t].l, pool[t].r);\n   \
    \     }\n        pool[t].r = erase_node(pool[t].r, pos - left_count - 1);\n  \
    \      update(t);\n        return t;\n    }\n\n    void set_node(int t, int pos,\
    \ T value) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            set_node(pool[t].l, pos, std::move(value));\n\
    \        } else if (pos == left_count) {\n            pool[t].val = std::move(value);\n\
    \        } else {\n            set_node(pool[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    int find_node(int t, int pos) {\n\
    \        while (t) {\n            push(t);\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return t;\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = pool[t].r;\n\
    \            }\n        }\n        return 0;\n    }\n\n    int find_node(int t,\
    \ int pos, bool reversed) const {\n        while (t) {\n            bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n            int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \            int r = cur_reversed ? pool[t].l : pool[t].r;\n            int left_count\
    \ = pool[l].count;\n            if (pos < left_count) {\n                t = l;\n\
    \                reversed = cur_reversed;\n            } else if (pos == left_count)\
    \ {\n                return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (!t) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        dump_dfs(l, res,\
    \ cur_reversed);\n        res.push_back(pool[t].val);\n        dump_dfs(r, res,\
    \ cur_reversed);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res, bool reversed = false) const {\n        if (!t\
    \ || qr <= offset || offset + pool[t].count <= ql) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        int left_count\
    \ = pool[l].count;\n        int node_pos = offset + left_count;\n        dump_range_dfs(l,\
    \ ql, qr, offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos\
    \ < qr) {\n            res.push_back(pool[t].val);\n        }\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int clone_subtree_from(const\
    \ DynamicMonoidArray& other, int t) {\n        if (!t) return 0;\n        int\
    \ res = int(pool.size());\n        pool.push_back(other.pool[t]);\n        pool[res].l\
    \ = clone_subtree_from(other, other.pool[t].l);\n        pool[res].r = clone_subtree_from(other,\
    \ other.pool[t].r);\n        return res;\n    }\n\n    void update_dfs(int t)\
    \ {\n        if (!t) return;\n        update_dfs(pool[t].l);\n        update_dfs(pool[t].r);\n\
    \        update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n\
    \        if (first == last) return 0;\n        std::vector<int> stack;\n     \
    \   stack.reserve(last - first);\n        for (int i = first; i < last; i++) {\n\
    \            int left_child = 0;\n            while (!stack.empty() && pool[stack.back()].priority\
    \ < pool[i].priority) {\n                left_child = stack.back();\n        \
    \        stack.pop_back();\n            }\n            pool[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                pool[stack.back()].r = i;\n\
    \            }\n            stack.push_back(i);\n        }\n        int res =\
    \ stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n   \
    \ int build_from_vector(const std::vector<T>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const T& x : v) {\n\
    \            new_node(x);\n        }\n        return build_cartesian(first, int(pool.size()));\n\
    \    }\n\n    int build_from_vector(std::vector<T>&& v) {\n        int first =\
    \ int(pool.size());\n        pool.reserve(pool.size() + v.size());\n        for\
    \ (T& x : v) {\n            new_node(std::move(x));\n        }\n        return\
    \ build_cartesian(first, int(pool.size()));\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const U& x : v) {\n\
    \            new_node(make_value(x));\n        }\n        return build_cartesian(first,\
    \ int(pool.size()));\n    }\n\n    void reset_to_empty() {\n        pool.clear();\n\
    \        pool.push_back(Node());\n        root = 0;\n    }\n\n   public:\n   \
    \ DynamicMonoidArray()\n        : root(0), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicMonoidArray(const DynamicMonoidArray& other)\n     \
    \   : pool(other.pool), root(other.root), rng_state(other.rng_state) {}\n\n  \
    \  DynamicMonoidArray(DynamicMonoidArray&& other) noexcept\n        : pool(std::move(other.pool)),\
    \ root(other.root), rng_state(other.rng_state) {\n        other.reset_to_empty();\n\
    \    }\n\n    DynamicMonoidArray& operator=(const DynamicMonoidArray& other) {\n\
    \        if (this != &other) {\n            pool = other.pool;\n            root\
    \ = other.root;\n            rng_state = other.rng_state;\n        }\n       \
    \ return *this;\n    }\n\n    DynamicMonoidArray& operator=(DynamicMonoidArray&&\
    \ other) noexcept {\n        if (this != &other) {\n            pool = std::move(other.pool);\n\
    \            root = other.root;\n            rng_state = other.rng_state;\n  \
    \          other.reset_to_empty();\n        }\n        return *this;\n    }\n\n\
    \    explicit DynamicMonoidArray(int n) : DynamicMonoidArray(n, Monoid::id())\
    \ {}\n\n    DynamicMonoidArray(int n, const T& value) : DynamicMonoidArray() {\n\
    \        assert(0 <= n);\n        pool.reserve(n + 1);\n        int first = int(pool.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(pool.size()));\n    }\n\n    explicit\
    \ DynamicMonoidArray(const std::vector<T>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n    }\n\
    \n    explicit DynamicMonoidArray(std::vector<T>&& v) : DynamicMonoidArray() {\n\
    \        pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { Monoid::make(x); } || std::convertible_to<U, T>)\n    explicit\
    \ DynamicMonoidArray(const std::vector<U>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_values(v);\n    }\n\
    \n    DynamicMonoidArray(std::initializer_list<T> init) : DynamicMonoidArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T value) {\n\
    \        assert(0 <= pos && pos <= size());\n        root = insert_node(root,\
    \ pos, new_node(std::move(value)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicMonoidArray& other) {\n      \
    \  assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n  \
    \      pool.reserve(pool.size() + other.size());\n        int mid = clone_subtree_from(other,\
    \ other.root);\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = merge(merge(l, mid), r);\n    }\n\n    void push_back(T value) {\n       \
    \ insert(size(), std::move(value));\n    }\n\n    void push_front(T value) {\n\
    \        insert(0, std::move(value));\n    }\n\n    void append(const std::vector<T>&\
    \ v) {\n        insert(size(), v);\n    }\n\n    void append(std::vector<T>&&\
    \ v) {\n        insert(size(), std::move(v));\n    }\n\n    void append(const\
    \ DynamicMonoidArray& other) {\n        insert(size(), other);\n    }\n\n    void\
    \ erase(int pos) {\n        assert(0 <= pos && pos < size());\n        root =\
    \ erase_node(root, pos);\n    }\n\n    void erase(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        int a,\
    \ b, c;\n        split(root, l, a, b);\n        split(b, r - l, b, c);\n     \
    \   root = merge(a, c);\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        erase(size() - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n\
    \        erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0 <= pos\
    \ && pos < size());\n        return pool[find_node(root, pos, false)].val;\n \
    \   }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\n\
    \    T front() const {\n        assert(!empty());\n        return get(0);\n  \
    \  }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    void set(int pos, T value) {\n        assert(0 <= pos &&\
    \ pos < size());\n        set_node(root, pos, std::move(value));\n    }\n\n  \
    \  void reverse(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split(root, l, a,\
    \ b);\n        split(b, r - l, b, c);\n        apply_reverse(b);\n        root\
    \ = merge(merge(a, b), c);\n    }\n\n    void reverse() {\n        apply_reverse(root);\n\
    \    }\n\n    void rotate(int l, int m, int r) {\n        assert(0 <= l && l <=\
    \ m && m <= r && r <= size());\n        if (l == m || m == r) return;\n      \
    \  int a, b, c, d;\n        split(root, l, a, b);\n        split(b, m - l, b,\
    \ c);\n        split(c, r - m, c, d);\n        root = merge(merge(a, c), merge(b,\
    \ d));\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return Monoid::id();\n        int a, b, c;\n\
    \        split(root, l, a, b);\n        split(b, r - l, b, c);\n        T res\
    \ = pool[b].prod;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\n    T all_prod() const {\n        return pool[root].prod;\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicMonoidArray split_off(int pos) {\n        assert(0 <= pos &&\
    \ pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n      \
    \  root = l;\n\n        DynamicMonoidArray res;\n        res.pool.reserve(pool[r].count\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return\
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12 \"\
    ds/dynamic_array/rollback_dynamic_monoid_array.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class Monoid>\nstruct RollbackDynamicMonoidArray {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    enum class Kind { insert,\
    \ erase, set, reverse, rotate, clear };\n    struct Entry {\n        Kind kind;\n\
    \        int first;\n        int second;\n        int third;\n        std::optional<T>\
    \ value;\n        std::vector<T> values;\n    };\n\n    DynamicMonoidArray<Monoid>\
    \ _data;\n    std::vector<Entry> _history;\n    std::vector<std::size_t> _checkpoints;\n\
    \n    void record_insert(int pos, int count) {\n        if (!_checkpoints.empty())\
    \ {\n            _history.push_back(Entry{Kind::insert, pos, count, 0, std::nullopt,\
    \ {}});\n        }\n    }\n\n   public:\n    RollbackDynamicMonoidArray() = default;\n\
    \    explicit RollbackDynamicMonoidArray(int n) : _data(n) {}\n    RollbackDynamicMonoidArray(int\
    \ n, const T& value) : _data(n, value) {}\n    explicit RollbackDynamicMonoidArray(const\
    \ std::vector<T>& values) : _data(values) {}\n    explicit RollbackDynamicMonoidArray(std::vector<T>&&\
    \ values) : _data(std::move(values)) {}\n\n    template <class U>\n        requires(!std::same_as<U,\
    \ T>)\n    explicit RollbackDynamicMonoidArray(const std::vector<U>& values) :\
    \ _data(values) {}\n\n    RollbackDynamicMonoidArray(std::initializer_list<T>\
    \ init) : _data(init) {}\n\n    int size() const { return _data.size(); }\n  \
    \  bool empty() const { return _data.empty(); }\n    std::size_t node_count()\
    \ const { return std::size_t(size()); }\n\n    void clear() {\n        Entry entry{Kind::clear,\
    \ 0, 0, 0, std::nullopt, {}};\n        if (!_checkpoints.empty()) entry.values\
    \ = _data.to_vector();\n        _data.clear();\n        if (!_checkpoints.empty())\
    \ _history.push_back(std::move(entry));\n    }\n\n    void insert(int pos, T value)\
    \ {\n        _data.insert(pos, std::move(value));\n        record_insert(pos,\
    \ 1);\n    }\n\n    void insert(int pos, const std::vector<T>& values) {\n   \
    \     _data.insert(pos, values);\n        record_insert(pos, int(values.size()));\n\
    \    }\n\n    void insert(int pos, std::vector<T>&& values) {\n        int count\
    \ = int(values.size());\n        _data.insert(pos, std::move(values));\n     \
    \   record_insert(pos, count);\n    }\n\n    void insert(int pos, std::initializer_list<T>\
    \ values) {\n        insert(pos, std::vector<T>(values));\n    }\n\n    void insert(int\
    \ pos, const RollbackDynamicMonoidArray& other) {\n        insert(pos, other.to_vector());\n\
    \    }\n\n    void insert(int pos, const DynamicMonoidArray<Monoid>& other) {\n\
    \        DynamicMonoidArray<Monoid> copy = other;\n        insert(pos, copy.to_vector());\n\
    \    }\n\n    void push_back(T value) { insert(size(), std::move(value)); }\n\
    \    void push_front(T value) { insert(0, std::move(value)); }\n    void append(const\
    \ std::vector<T>& values) { insert(size(), values); }\n    void append(std::vector<T>&&\
    \ values) { insert(size(), std::move(values)); }\n    void append(const RollbackDynamicMonoidArray&\
    \ other) { insert(size(), other); }\n    void append(const DynamicMonoidArray<Monoid>&\
    \ other) { insert(size(), other); }\n\n    void erase(int pos) { erase(pos, pos\
    \ + 1); }\n\n    void erase(int left, int right) {\n        assert(0 <= left &&\
    \ left <= right && right <= size());\n        Entry entry{Kind::erase, left, 0,\
    \ 0, std::nullopt, {}};\n        if (!_checkpoints.empty()) entry.values = _data.to_vector(left,\
    \ right);\n        _data.erase(left, right);\n        if (!_checkpoints.empty())\
    \ _history.push_back(std::move(entry));\n    }\n\n    void pop_back() { assert(!empty());\
    \ erase(size() - 1); }\n    void pop_front() { assert(!empty()); erase(0); }\n\
    \n    T get(int pos) const { return _data.get(pos); }\n    T operator[](int pos)\
    \ const { return get(pos); }\n    T front() const { assert(!empty()); return get(0);\
    \ }\n    T back() const { assert(!empty()); return get(size() - 1); }\n\n    void\
    \ set(int pos, T value) {\n        Entry entry{Kind::set, pos, 0, 0, std::nullopt,\
    \ {}};\n        if (!_checkpoints.empty()) entry.value.emplace(_data.get(pos));\n\
    \        _data.set(pos, std::move(value));\n        if (!_checkpoints.empty())\
    \ _history.push_back(std::move(entry));\n    }\n\n    void set_inplace(int pos,\
    \ T value) { set(pos, std::move(value)); }\n\n    void reverse(int left, int right)\
    \ {\n        _data.reverse(left, right);\n        if (!_checkpoints.empty()) {\n\
    \            _history.push_back(Entry{Kind::reverse, left, right, 0, std::nullopt,\
    \ {}});\n        }\n    }\n\n    void reverse() { reverse(0, size()); }\n\n  \
    \  void rotate(int left, int middle, int right) {\n        _data.rotate(left,\
    \ middle, right);\n        if (!_checkpoints.empty()) {\n            _history.push_back(Entry{Kind::rotate,\
    \ left, middle, right, std::nullopt, {}});\n        }\n    }\n\n    T prod(int\
    \ left, int right) { return _data.prod(left, right); }\n    T all_prod() const\
    \ { return _data.all_prod(); }\n    std::vector<T> to_vector() { return _data.to_vector();\
    \ }\n    std::vector<T> to_vector() const {\n        DynamicMonoidArray<Monoid>\
    \ copy = _data;\n        return copy.to_vector();\n    }\n    std::vector<T> to_vector(int\
    \ left, int right) { return _data.to_vector(left, right); }\n    std::vector<T>\
    \ to_vector(int left, int right) const {\n        DynamicMonoidArray<Monoid> copy\
    \ = _data;\n        return copy.to_vector(left, right);\n    }\n\n    int snapshot()\
    \ { _checkpoints.push_back(_history.size()); return int(_checkpoints.size());\
    \ }\n    int snapshot_count() const { return int(_checkpoints.size()); }\n   \
    \ void reserve_snapshots(int count) { assert(0 <= count); _checkpoints.reserve(count);\
    \ }\n\n   private:\n    void restore_one() {\n        Entry entry = std::move(_history.back());\n\
    \        _history.pop_back();\n        if (entry.kind == Kind::insert) {\n   \
    \         _data.erase(entry.first, entry.first + entry.second);\n        } else\
    \ if (entry.kind == Kind::erase) {\n            _data.insert(entry.first, std::move(entry.values));\n\
    \        } else if (entry.kind == Kind::set) {\n            _data.set(entry.first,\
    \ std::move(*entry.value));\n        } else if (entry.kind == Kind::reverse) {\n\
    \            _data.reverse(entry.first, entry.second);\n        } else if (entry.kind\
    \ == Kind::rotate) {\n            _data.rotate(entry.first, entry.first + entry.third\
    \ - entry.second, entry.third);\n        } else {\n            _data.insert(0,\
    \ std::move(entry.values));\n        }\n    }\n\n   public:\n    void rollback(int\
    \ state) {\n        assert(1 <= state && state <= snapshot_count());\n       \
    \ while (_history.size() > _checkpoints[state - 1]) restore_one();\n        _checkpoints.resize(state);\n\
    \    }\n    void clear_history() { _history.clear(); _checkpoints.clear(); }\n\
    \    void release() { _data.clear(); _history.clear(); _checkpoints.clear(); }\n\
    };\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/queue/rollback_queue.hpp\"\
    \n\n\n\n#line 9 \"ds/queue/rollback_queue.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class T>\nstruct RollbackQueue {\n   private:\n    enum class\
    \ Kind { push, pop, clear };\n    struct Entry {\n        Kind kind;\n       \
    \ std::optional<T> value;\n        std::deque<T> values;\n    };\n\n    std::deque<T>\
    \ _values;\n    std::vector<Entry> _history;\n    std::vector<std::size_t> _checkpoints;\n\
    \    std::size_t _stored_values = 0;\n\n   public:\n    RollbackQueue() = default;\n\
    \n    int size() const { return int(_values.size()); }\n    bool empty() const\
    \ { return _values.empty(); }\n    std::size_t node_count() const { return _stored_values;\
    \ }\n\n    const T& front() const {\n        assert(!empty());\n        return\
    \ _values.front();\n    }\n\n    const T& back() const {\n        assert(!empty());\n\
    \        return _values.back();\n    }\n\n    void push(T value) {\n        if\
    \ (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt, {}});\n\
    \        _values.push_back(std::move(value));\n        ++_stored_values;\n   \
    \ }\n\n    void push_back(T value) { push(std::move(value)); }\n\n    void pop()\
    \ {\n        assert(!empty());\n        if (_checkpoints.empty()) {\n        \
    \    _values.pop_front();\n            --_stored_values;\n        } else {\n \
    \           Entry entry{Kind::pop, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.front()));\n\
    \            _values.pop_front();\n            _history.push_back(std::move(entry));\n\
    \        }\n    }\n\n    void pop_front() { pop(); }\n\n    void clear() {\n \
    \       if (_checkpoints.empty()) {\n            _stored_values -= _values.size();\n\
    \            _values.clear();\n        } else {\n            Entry entry{Kind::clear,\
    \ std::nullopt, {}};\n            entry.values = std::move(_values);\n       \
    \     _values.clear();\n            _history.push_back(std::move(entry));\n  \
    \      }\n    }\n\n    int snapshot() {\n        _checkpoints.push_back(_history.size());\n\
    \        return int(_checkpoints.size());\n    }\n    int snapshot_count() const\
    \ { return int(_checkpoints.size()); }\n\n    void reserve_snapshots(int count)\
    \ {\n        assert(0 <= count);\n        _checkpoints.reserve(count);\n    }\n\
    \n   private:\n    void restore_one() {\n        Entry entry = std::move(_history.back());\n\
    \        _history.pop_back();\n        if (entry.kind == Kind::push) {\n     \
    \       _values.pop_back();\n            --_stored_values;\n        } else if\
    \ (entry.kind == Kind::pop) {\n            _values.push_front(std::move(*entry.value));\n\
    \        } else {\n            _values = std::move(entry.values);\n        }\n\
    \    }\n\n   public:\n    void rollback(int state) {\n        assert(1 <= state\
    \ && state <= snapshot_count());\n        while (_history.size() > _checkpoints[state\
    \ - 1]) restore_one();\n        _checkpoints.resize(state);\n    }\n\n    void\
    \ clear_history() {\n        for (const Entry& entry : _history) {\n         \
    \   if (entry.value) --_stored_values;\n            _stored_values -= entry.values.size();\n\
    \        }\n        _history.clear();\n        _checkpoints.clear();\n    }\n\n\
    \    void release() {\n        _values.clear();\n        _history.clear();\n \
    \       _checkpoints.clear();\n        _stored_values = 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_dual_segtree.hpp\"\
    \n\n\n\n#line 9 \"ds/segtree/rollback_dual_segtree.hpp\"\n\n#line 12 \"ds/segtree/rollback_dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct RollbackDualSegtree {\n    using T = typename Monoid::value_type;\n\n \
    \  private:\n    struct Node {\n        T value = Monoid::id();\n        bool\
    \ has_value = false;\n    };\n\n    int _n = 0;\n    detail::RollbackJournal<Node>\
    \ _journal;\n\n    template <class U>\n    static T make_value(const U& value,\
    \ int index) {\n        if constexpr (requires(U x) { Monoid::make(x); }) {\n\
    \            return Monoid::make(value);\n        } else if constexpr (requires(U\
    \ x, int i) { Monoid::make(x, i); }) {\n            return Monoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    void initialize(int n) {\n        assert(0 <= n);\n      \
    \  _n = n;\n        _journal.nodes.assign(std::max(1, 4 * n), Node());\n     \
    \   _journal.saved_epoch.assign(_journal.nodes.size(), 0);\n    }\n\n    template\
    \ <class U>\n    void build(int node, int left, int right, const std::vector<U>&\
    \ values) {\n        if (right - left == 1) {\n            _journal[node].value\
    \ = make_value(values[left], left);\n            _journal[node].has_value = true;\n\
    \            return;\n        }\n        int middle = (left + right) >> 1;\n \
    \       build(node << 1, left, middle, values);\n        build(node << 1 | 1,\
    \ middle, right, values);\n    }\n\n    void all_apply(int node, const T& value)\
    \ {\n        _journal.touch(node);\n        Node& current = _journal[node];\n\
    \        current.value = current.has_value\n            ? Monoid::op(value, current.value)\n\
    \            : value;\n        current.has_value = true;\n    }\n\n    void push(int\
    \ node) {\n        if (!_journal[node].has_value) return;\n        T value = _journal[node].value;\n\
    \        all_apply(node << 1, value);\n        all_apply(node << 1 | 1, value);\n\
    \        _journal.touch(node);\n        _journal[node].value = Monoid::id();\n\
    \        _journal[node].has_value = false;\n    }\n\n    void set_node(int node,\
    \ int left, int right, int pos, T value) {\n        if (right - left == 1) {\n\
    \            _journal.touch(node);\n            _journal[node].value = std::move(value);\n\
    \            _journal[node].has_value = true;\n            return;\n        }\n\
    \        push(node);\n        int middle = (left + right) >> 1;\n        if (pos\
    \ < middle) set_node(node << 1, left, middle, pos, std::move(value));\n      \
    \  else set_node(node << 1 | 1, middle, right, pos, std::move(value));\n    }\n\
    \n    void apply_node(int node, int left, int right, int query_left, int query_right,\
    \ const T& value) {\n        if (query_right <= left || right <= query_left) return;\n\
    \        if (query_left <= left && right <= query_right) {\n            all_apply(node,\
    \ value);\n            return;\n        }\n        push(node);\n        int middle\
    \ = (left + right) >> 1;\n        apply_node(node << 1, left, middle, query_left,\
    \ query_right, value);\n        apply_node(node << 1 | 1, middle, right, query_left,\
    \ query_right, value);\n    }\n\n    T get_node(int node, int left, int right,\
    \ int pos, T inherited) const {\n        const Node& current = _journal[node];\n\
    \        if (right - left == 1) {\n            assert(current.has_value);\n  \
    \          return Monoid::op(inherited, current.value);\n        }\n        if\
    \ (current.has_value) inherited = Monoid::op(inherited, current.value);\n    \
    \    int middle = (left + right) >> 1;\n        if (pos < middle) return get_node(node\
    \ << 1, left, middle, pos, std::move(inherited));\n        return get_node(node\
    \ << 1 | 1, middle, right, pos, std::move(inherited));\n    }\n\n   public:\n\
    \    RollbackDualSegtree() { initialize(0); }\n    explicit RollbackDualSegtree(int\
    \ n) {\n        initialize(n);\n        if (n > 0) {\n            std::vector<T>\
    \ values(n, Monoid::id());\n            build(1, 0, n, values);\n        }\n \
    \   }\n\n    explicit RollbackDualSegtree(const std::vector<T>& values) {\n  \
    \      initialize(int(values.size()));\n        if (_n > 0) build(1, 0, _n, values);\n\
    \    }\n\n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackDualSegtree(const std::vector<U>& values) {\n        initialize(int(values.size()));\n\
    \        if (_n > 0) build(1, 0, _n, values);\n    }\n\n    int size() const {\
    \ return _n; }\n    bool empty() const { return _n == 0; }\n    std::size_t node_count()\
    \ const { return _journal.nodes.size(); }\n\n    void set(int pos, T value) {\n\
    \        assert(0 <= pos && pos < _n);\n        set_node(1, 0, _n, pos, std::move(value));\n\
    \    }\n    void set_inplace(int pos, T value) { set(pos, std::move(value)); }\n\
    \n    T get(int pos) const {\n        assert(0 <= pos && pos < _n);\n        return\
    \ get_node(1, 0, _n, pos, Monoid::id());\n    }\n    T operator[](int pos) const\
    \ { return get(pos); }\n\n    void apply(int pos, const T& value) { apply(pos,\
    \ pos + 1, value); }\n    void apply(int left, int right, const T& value) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ != right) apply_node(1, 0, _n, left, right, value);\n    }\n    void apply_inplace(int\
    \ pos, const T& value) { apply(pos, value); }\n    void apply_inplace(int left,\
    \ int right, const T& value) { apply(left, right, value); }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _journal.clear();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\
    \n\n\n\n#line 7 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n#include <numeric>\n\
    #line 10 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing\
    \ dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
    \ Index>\nconstexpr dynamic_size_type<Index> dynamic_distance(Index left, Index\
    \ right) {\n    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
    }\n\ntemplate <class Monoid, class Size>\ntypename Monoid::value_type monoid_repeat(typename\
    \ Monoid::value_type value, Size count) {\n    typename Monoid::value_type result\
    \ = Monoid::id();\n    while (count != 0) {\n        if (count & 1) result = Monoid::op(result,\
    \ value);\n        count >>= 1;\n        if (count != 0) value = Monoid::op(value,\
    \ value);\n    }\n    return result;\n}\n\ntemplate <class ActedMonoid>\ntypename\
    \ ActedMonoid::value_type dynamic_mapping(\n    const typename ActedMonoid::operator_type&\
    \ f,\n    const typename ActedMonoid::value_type& value\n) {\n    using F = typename\
    \ ActedMonoid::operator_type;\n    using T = typename ActedMonoid::value_type;\n\
    \    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g,\
    \ x, ord); }) {\n        return ActedMonoid::mapping(f, value, 0);\n    } else\
    \ {\n        return ActedMonoid::mapping(f, value);\n    }\n}\n\ntemplate <class\
    \ ActedMonoid, class Size>\ntypename ActedMonoid::operator_type dynamic_shift(\n\
    \    const typename ActedMonoid::operator_type& f,\n    Size offset\n) {\n   \
    \ using F = typename ActedMonoid::operator_type;\n    if constexpr (requires(F\
    \ g, long long ord) { ActedMonoid::op_shift(g, ord); }) {\n        assert(offset\
    \ <= static_cast<Size>(std::numeric_limits<long long>::max()));\n        return\
    \ ActedMonoid::op_shift(f, static_cast<long long>(offset));\n    } else {\n  \
    \      return f;\n    }\n}\n\ntemplate <class Monoid, std::integral Index>\nclass\
    \ UniformMonoidDomain {\n   public:\n    using T = typename Monoid::value_type;\n\
    \    using size_type = dynamic_size_type<Index>;\n\n   private:\n    struct Level\
    \ {\n        size_type small_length;\n        T small_value;\n        T large_value;\n\
    \    };\n\n    Index _left;\n    Index _right;\n    T _initial_value;\n    std::vector<Level>\
    \ _levels;\n\n   public:\n    UniformMonoidDomain(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        size_type n = size();\n        constexpr\
    \ int digits = std::numeric_limits<size_type>::digits;\n        _levels.reserve(digits\
    \ + 1);\n        for (int depth = 0; depth <= digits; depth++) {\n           \
    \ size_type small = depth == digits ? 0 : n >> depth;\n            size_type large\
    \ = small;\n            if (depth != 0) {\n                bool has_remainder;\n\
    \                if (depth == digits) {\n                    has_remainder = n\
    \ != 0;\n                } else {\n                    size_type mask = (size_type(1)\
    \ << depth) - 1;\n                    has_remainder = (n & mask) != 0;\n     \
    \           }\n                if (has_remainder) large++;\n            }\n  \
    \          _levels.push_back(Level{\n                small,\n                monoid_repeat<Monoid>(_initial_value,\
    \ small),\n                monoid_repeat<Monoid>(_initial_value, large),\n   \
    \         });\n        }\n    }\n\n    Index left_bound() const {\n        return\
    \ _left;\n    }\n\n    Index right_bound() const {\n        return _right;\n \
    \   }\n\n    size_type size() const {\n        return dynamic_distance(_left,\
    \ _right);\n    }\n\n    bool empty() const {\n        return _left == _right;\n\
    \    }\n\n    const T& initial_value() const {\n        return _initial_value;\n\
    \    }\n\n    const T& default_product(int depth, Index left, Index right) const\
    \ {\n        assert(0 <= depth && depth < int(_levels.size()));\n        const\
    \ Level& level = _levels[depth];\n        size_type length = dynamic_distance(left,\
    \ right);\n        if (length == level.small_length) return level.small_value;\n\
    \        assert(length == level.small_length + 1);\n        return level.large_value;\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 14 \"ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct RollbackDynamicDualSegtree {\n    using T = typename Monoid::value_type;\n\
    \    using index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n        bool has_value = false;\n    };\n\
    \n    Index _left;\n    Index _right;\n    T _initial_value;\n    detail::RollbackJournal<Node>\
    \ _journal;\n\n    int root() const { return _journal[0].left; }\n    int new_node()\
    \ { return _journal.emplace(); }\n\n    int ensure(int node) { return node ? node\
    \ : new_node(); }\n\n    void all_apply(int node, Index left, Index right, const\
    \ T& value) {\n        _journal.touch(node);\n        Node& current = _journal[node];\n\
    \        if (std::midpoint(left, right) == left) {\n            T old = current.has_value\
    \ ? current.value : _initial_value;\n            current.value = Monoid::op(value,\
    \ old);\n        } else {\n            current.value = current.has_value ? Monoid::op(value,\
    \ current.value) : value;\n        }\n        current.has_value = true;\n    }\n\
    \n    void push(int node, Index left, Index right) {\n        if (!_journal[node].has_value)\
    \ return;\n        Index middle = std::midpoint(left, right);\n        if (middle\
    \ == left) return;\n        T lazy = _journal[node].value;\n        int left_child\
    \ = ensure(_journal[node].left);\n        int right_child = ensure(_journal[node].right);\n\
    \        all_apply(left_child, left, middle, lazy);\n        all_apply(right_child,\
    \ middle, right, lazy);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        _journal[node].value\
    \ = Monoid::id();\n        _journal[node].has_value = false;\n    }\n\n    int\
    \ set_node(int node, Index left, Index right, Index pos, T value) {\n        node\
    \ = ensure(node);\n        Index middle = std::midpoint(left, right);\n      \
    \  if (middle == left) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            _journal[node].has_value = true;\n        \
    \    return node;\n        }\n        push(node, left, right);\n        if (pos\
    \ < middle) {\n            int child = set_node(_journal[node].left, left, middle,\
    \ pos, std::move(value));\n            _journal.touch(node);\n            _journal[node].left\
    \ = child;\n        } else {\n            int child = set_node(_journal[node].right,\
    \ middle, right, pos, std::move(value));\n            _journal.touch(node);\n\
    \            _journal[node].right = child;\n        }\n        return node;\n\
    \    }\n\n    int apply_node(int node, Index left, Index right, Index query_left,\
    \ Index query_right, const T& value) {\n        if (query_right <= left || right\
    \ <= query_left) return node;\n        node = ensure(node);\n        if (query_left\
    \ <= left && right <= query_right) {\n            all_apply(node, left, right,\
    \ value);\n            return node;\n        }\n        push(node, left, right);\n\
    \        Index middle = std::midpoint(left, right);\n        int left_child =\
    \ apply_node(_journal[node].left, left, middle, query_left, query_right, value);\n\
    \        int right_child = apply_node(_journal[node].right, middle, right, query_left,\
    \ query_right, value);\n        _journal.touch(node);\n        _journal[node].left\
    \ = left_child;\n        _journal[node].right = right_child;\n        return node;\n\
    \    }\n\n   public:\n    RollbackDynamicDualSegtree()\n        : RollbackDynamicDualSegtree(Index(0),\
    \ Index(0), Monoid::id()) {}\n    explicit RollbackDynamicDualSegtree(Index n)\n\
    \        : RollbackDynamicDualSegtree(Index(0), n, Monoid::id()) {\n        if\
    \ constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n    }\n    RollbackDynamicDualSegtree(Index\
    \ left, Index right)\n        : RollbackDynamicDualSegtree(left, right, Monoid::id())\
    \ {}\n    RollbackDynamicDualSegtree(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        _journal.emplace();\n    }\n\n  \
    \  size_type size() const { return detail::dynamic_distance(_left, _right); }\n\
    \    bool empty() const { return _left == _right; }\n    Index left_bound() const\
    \ { return _left; }\n    Index right_bound() const { return _right; }\n    const\
    \ T& initial_value() const { return _initial_value; }\n    std::size_t node_count()\
    \ const { return _journal.nodes.size() - 1; }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _journal.nodes.reserve(node_capacity + 1);\n     \
    \   _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n    void set(Index\
    \ pos, T value) {\n        assert(_left <= pos && pos < _right);\n        int\
    \ next_root = set_node(root(), _left, _right, pos, std::move(value));\n      \
    \  if (next_root != root()) {\n            _journal.touch(0);\n            _journal[0].left\
    \ = next_root;\n        }\n    }\n    void set_inplace(Index pos, T value) { set(pos,\
    \ std::move(value)); }\n\n    T get(Index pos) const {\n        assert(_left <=\
    \ pos && pos < _right);\n        int node = root();\n        Index left = _left;\n\
    \        Index right = _right;\n        T inherited = Monoid::id();\n        while\
    \ (node) {\n            Index middle = std::midpoint(left, right);\n         \
    \   if (middle == left) {\n                T value = _journal[node].has_value\
    \ ? _journal[node].value : _initial_value;\n                return Monoid::op(inherited,\
    \ value);\n            }\n            if (_journal[node].has_value) inherited\
    \ = Monoid::op(inherited, _journal[node].value);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ _initial_value);\n    }\n    T operator[](Index pos) const { return get(pos);\
    \ }\n\n    void apply(Index pos, const T& value) { apply(pos, pos + 1, value);\
    \ }\n    void apply(Index left, Index right, const T& value) {\n        assert(_left\
    \ <= left && left <= right && right <= _right);\n        if (left == right) return;\n\
    \        int next_root = apply_node(root(), _left, _right, left, right, value);\n\
    \        if (next_root != root()) {\n            _journal.touch(0);\n        \
    \    _journal[0].left = next_root;\n        }\n    }\n    void apply_inplace(Index\
    \ pos, const T& value) { apply(pos, value); }\n    void apply_inplace(Index left,\
    \ Index right, const T& value) { apply(left, right, value); }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\
    \n\n\n\n#line 12 \"ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\n\n#line 16\
    \ \"ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// A sparse lazy segment tree over an integral half-open interval.\n\
    template <m1une::acted_monoid::IsActedMonoid ActedMonoid, std::integral Index\
    \ = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct\
    \ RollbackDynamicLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n    using index_type = Index;\n\
    \    using size_type = detail::dynamic_size_type<Index>;\n\n   private:\n    struct\
    \ Node {\n        T val;\n        F lazy;\n        int left;\n        int right;\n\
    \        bool has_lazy;\n\n        explicit Node(T value)\n            : val(std::move(value)),\n\
    \              lazy(ActedMonoid::op_id()),\n              left(0),\n         \
    \     right(0),\n              has_lazy(false) {}\n    };\n\n    detail::UniformMonoidDomain<ActedMonoid,\
    \ Index> _domain;\n    detail::RollbackJournal<Node> _journal;\n\n    int root()\
    \ const { return _journal[0].left; }\n\n    int new_node(Index left, Index right,\
    \ int depth) {\n        assert(_journal.nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        return _journal.emplace(_domain.default_product(depth, left, right));\n\
    \    }\n\n    const T& value(int t, Index left, Index right, int depth) const\
    \ {\n        if (t) return _journal[t].val;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void all_apply(int& t, Index left, Index right,\
    \ int depth, const F& f) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        _journal.touch(t);\n        Node& node = _journal[t];\n        node.val\
    \ = detail::dynamic_mapping<ActedMonoid>(f, node.val);\n        if (std::midpoint(left,\
    \ right) != left) {\n            node.lazy = ActedMonoid::op_comp(f, node.lazy);\n\
    \            node.has_lazy = true;\n        }\n    }\n\n    void push(int t, Index\
    \ left, Index right, int depth) {\n        if (!_journal[t].has_lazy) return;\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ return;\n\n        F lazy = _journal[t].lazy;\n        int left_child = _journal[t].left;\n\
    \        int right_child = _journal[t].right;\n        all_apply(left_child, left,\
    \ middle, depth + 1, lazy);\n        all_apply(\n            right_child,\n  \
    \          middle,\n            right,\n            depth + 1,\n            detail::dynamic_shift<ActedMonoid>(lazy,\
    \ detail::dynamic_distance(left, middle))\n        );\n\n        _journal.touch(t);\n\
    \        Node& node = _journal[t];\n        node.left = left_child;\n        node.right\
    \ = right_child;\n        node.lazy = ActedMonoid::op_id();\n        node.has_lazy\
    \ = false;\n    }\n\n    void update(int t, Index left, Index right, int depth)\
    \ {\n        _journal.touch(t);\n        Index middle = std::midpoint(left, right);\n\
    \        _journal[t].val = ActedMonoid::op(\n            value(_journal[t].left,\
    \ left, middle, depth + 1),\n            value(_journal[t].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    int set_node(int t, Index left, Index right,\
    \ int depth, Index p, T x) {\n        if (!t) t = new_node(left, right, depth);\n\
    \        Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ {\n            _journal.touch(t);\n            Node& node = _journal[t];\n \
    \           node.val = std::move(x);\n            node.lazy = ActedMonoid::op_id();\n\
    \            node.has_lazy = false;\n            return t;\n        }\n\n    \
    \    push(t, left, right, depth);\n        if (p < middle) {\n            int\
    \ child = set_node(_journal[t].left, left, middle, depth + 1, p, std::move(x));\n\
    \            _journal.touch(t);\n            _journal[t].left = child;\n     \
    \   } else {\n            int child = set_node(_journal[t].right, middle, right,\
    \ depth + 1, p, std::move(x));\n            _journal.touch(t);\n            _journal[t].right\
    \ = child;\n        }\n        update(t, left, right, depth);\n        return\
    \ t;\n    }\n\n    int apply_node(\n        int t,\n        Index left,\n    \
    \    Index right,\n        int depth,\n        Index query_left,\n        Index\
    \ query_right,\n        const F& f\n    ) {\n        if (query_right <= left ||\
    \ right <= query_left) return t;\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                t,\n                left,\n     \
    \           right,\n                depth,\n                detail::dynamic_shift<ActedMonoid>(f,\
    \ detail::dynamic_distance(query_left, left))\n            );\n            return\
    \ t;\n        }\n\n        if (!t) t = new_node(left, right, depth);\n       \
    \ push(t, left, right, depth);\n        Index middle = std::midpoint(left, right);\n\
    \        int left_child = apply_node(_journal[t].left, left, middle, depth + 1,\
    \ query_left, query_right, f);\n        int right_child = apply_node(_journal[t].right,\
    \ middle, right, depth + 1, query_left, query_right, f);\n        _journal.touch(t);\n\
    \        _journal[t].left = left_child;\n        _journal[t].right = right_child;\n\
    \        update(t, left, right, depth);\n        return t;\n    }\n\n    F compose_for_child(const\
    \ F& inherited, int t, size_type offset) const {\n        F shifted = detail::dynamic_shift<ActedMonoid>(inherited,\
    \ offset);\n        if (!t || !_journal[t].has_lazy) return shifted;\n       \
    \ return ActedMonoid::op_comp(\n            shifted,\n            detail::dynamic_shift<ActedMonoid>(_journal[t].lazy,\
    \ offset)\n        );\n    }\n\n    T prod_node(\n        int t,\n        Index\
    \ left,\n        Index right,\n        int depth,\n        Index query_left,\n\
    \        Index query_right,\n        const F& inherited\n    ) const {\n     \
    \   if (query_right <= left || right <= query_left) return ActedMonoid::id();\n\
    \        if (query_left <= left && right <= query_right) {\n            return\
    \ detail::dynamic_mapping<ActedMonoid>(\n                inherited,\n        \
    \        value(t, left, right, depth)\n            );\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        return ActedMonoid::op(\n    \
    \        prod_node(\n                t ? _journal[t].left : 0,\n             \
    \   left,\n                middle,\n                depth + 1,\n             \
    \   query_left,\n                query_right,\n                compose_for_child(inherited,\
    \ t, 0)\n            ),\n            prod_node(\n                t ? _journal[t].right\
    \ : 0,\n                middle,\n                right,\n                depth\
    \ + 1,\n                query_left,\n                query_right,\n          \
    \      compose_for_child(inherited, t, detail::dynamic_distance(left, middle))\n\
    \            )\n        );\n    }\n\n    template <class G>\n    Index max_right_node(\n\
    \        int t,\n        Index left,\n        Index right,\n        int depth,\n\
    \        Index query_left,\n        T& product,\n        const F& inherited,\n\
    \        G& predicate\n    ) const {\n        if (right <= query_left) return\
    \ right;\n        if (query_left <= left) {\n            T next = ActedMonoid::op(\n\
    \                product,\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                )\n            );\n            if (predicate(next)) {\n     \
    \           product = std::move(next);\n                return right;\n      \
    \      }\n            Index middle = std::midpoint(left, right);\n           \
    \ if (middle == left) return left;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = max_right_node(\n            t ? _journal[t].left\
    \ : 0,\n            left,\n            middle,\n            depth + 1,\n     \
    \       query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, 0),\n            predicate\n        );\n        if (result < middle) return\
    \ result;\n        return max_right_node(\n            t ? _journal[t].right :\
    \ 0,\n            middle,\n            right,\n            depth + 1,\n      \
    \      query_left,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n    }\n\n    template <class G>\n    Index min_left_node(\n        int t,\n\
    \        Index left,\n        Index right,\n        int depth,\n        Index\
    \ query_right,\n        T& product,\n        const F& inherited,\n        G& predicate\n\
    \    ) const {\n        if (query_right <= left) return left;\n        if (right\
    \ <= query_right) {\n            T next = ActedMonoid::op(\n                detail::dynamic_mapping<ActedMonoid>(\n\
    \                    inherited,\n                    value(t, left, right, depth)\n\
    \                ),\n                product\n            );\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return left;\n\
    \            }\n            Index middle = std::midpoint(left, right);\n     \
    \       if (middle == left) return right;\n        }\n        Index middle = std::midpoint(left,\
    \ right);\n        Index result = min_left_node(\n            t ? _journal[t].right\
    \ : 0,\n            middle,\n            right,\n            depth + 1,\n    \
    \        query_right,\n            product,\n            compose_for_child(inherited,\
    \ t, detail::dynamic_distance(left, middle)),\n            predicate\n       \
    \ );\n        if (middle < result) return result;\n        return min_left_node(\n\
    \            t ? _journal[t].left : 0,\n            left,\n            middle,\n\
    \            depth + 1,\n            query_right,\n            product,\n    \
    \        compose_for_child(inherited, t, 0),\n            predicate\n        );\n\
    \    }\n\n   public:\n    RollbackDynamicLazySegtree()\n        : RollbackDynamicLazySegtree(Index(0),\
    \ Index(0), ActedMonoid::id()) {}\n\n    explicit RollbackDynamicLazySegtree(Index\
    \ n)\n        : RollbackDynamicLazySegtree(Index(0), n, ActedMonoid::id()) {\n\
    \        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);\n \
    \   }\n\n    RollbackDynamicLazySegtree(Index left, Index right)\n        : RollbackDynamicLazySegtree(left,\
    \ right, ActedMonoid::id()) {}\n\n    RollbackDynamicLazySegtree(Index left, Index\
    \ right, T initial_value)\n        : _domain(left, right, std::move(initial_value))\
    \ {\n        _journal.emplace(ActedMonoid::id());\n    }\n\n    size_type size()\
    \ const {\n        return _domain.size();\n    }\n\n    bool empty() const {\n\
    \        return _domain.empty();\n    }\n\n    Index left_bound() const {\n  \
    \      return _domain.left_bound();\n    }\n\n    Index right_bound() const {\n\
    \        return _domain.right_bound();\n    }\n\n    const T& initial_value()\
    \ const {\n        return _domain.initial_value();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _journal.nodes.reserve(node_capacity + 1);\n        _journal.saved_epoch.reserve(node_capacity\
    \ + 1);\n    }\n\n    std::size_t node_count() const {\n        return _journal.nodes.size()\
    \ - 1;\n    }\n\n    void clear() {\n        if (_journal.snapshot_count() ==\
    \ 0) {\n            _journal.clear();\n            _journal.emplace(ActedMonoid::id());\n\
    \            return;\n        }\n        _journal.touch(0);\n        _journal[0].left\
    \ = 0;\n    }\n\n    void set(Index p, T x) {\n        assert(left_bound() <=\
    \ p && p < right_bound());\n        int next_root = set_node(root(), left_bound(),\
    \ right_bound(), 0, p, std::move(x));\n        if (next_root != root()) {\n  \
    \          _journal.touch(0);\n            _journal[0].left = next_root;\n   \
    \     }\n    }\n\n    T get(Index p) const {\n        assert(left_bound() <= p\
    \ && p < right_bound());\n        return prod(p, p + 1);\n    }\n\n    T operator[](Index\
    \ p) const {\n        return get(p);\n    }\n\n    T prod(Index left, Index right)\
    \ const {\n        assert(left_bound() <= left && left <= right && right <= right_bound());\n\
    \        if (left == right) return ActedMonoid::id();\n        return prod_node(\n\
    \            root(),\n            left_bound(),\n            right_bound(),\n\
    \            0,\n            left,\n            right,\n            ActedMonoid::op_id()\n\
    \        );\n    }\n\n    T all_prod() const {\n        return value(root(), left_bound(),\
    \ right_bound(), 0);\n    }\n\n    void apply(Index p, const F& f) {\n       \
    \ assert(left_bound() <= p && p < right_bound());\n        apply(p, p + 1, f);\n\
    \    }\n\n    void apply(Index left, Index right, const F& f) {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return;\n        int next_root = apply_node(\n            root(), left_bound(),\
    \ right_bound(), 0, left, right, f\n        );\n        if (next_root != root())\
    \ {\n            _journal.touch(0);\n            _journal[0].left = next_root;\n\
    \        }\n    }\n\n    template <class G>\n    Index max_right(Index left, G\
    \ predicate) const {\n        assert(left_bound() <= left && left <= right_bound());\n\
    \        assert(predicate(ActedMonoid::id()));\n        if (left == right_bound())\
    \ return right_bound();\n        T product = ActedMonoid::id();\n        return\
    \ max_right_node(\n            root(),\n            left_bound(),\n          \
    \  right_bound(),\n            0,\n            left,\n            product,\n \
    \           ActedMonoid::op_id(),\n            predicate\n        );\n    }\n\n\
    \    template <class G>\n    Index min_left(Index right, G predicate) const {\n\
    \        assert(left_bound() <= right && right <= right_bound());\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == left_bound()) return left_bound();\n        T product =\
    \ ActedMonoid::id();\n        return min_left_node(\n            root(),\n   \
    \         left_bound(),\n            right_bound(),\n            0,\n        \
    \    right,\n            product,\n            ActedMonoid::op_id(),\n       \
    \     predicate\n        );\n    }\n\n    void set_inplace(Index p, T x) { set(p,\
    \ std::move(x)); }\n    void apply_inplace(Index p, const F& f) { apply(p, f);\
    \ }\n    void apply_inplace(Index left, Index right, const F& f) { apply(left,\
    \ right, f); }\n\n    int snapshot() { return _journal.snapshot(); }\n    int\
    \ snapshot_count() const { return _journal.snapshot_count(); }\n    void reserve_snapshots(int\
    \ count) { _journal.reserve_snapshots(count); }\n    void rollback(int state)\
    \ { _journal.rollback(state); }\n    void clear_history() { _journal.clear_history();\
    \ }\n    void release() { _journal.clear(); _journal.emplace(ActedMonoid::id());\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_dynamic_segtree.hpp\"\
    \n\n\n\n#include <array>\n#line 11 \"ds/segtree/rollback_dynamic_segtree.hpp\"\
    \n\n#line 15 \"ds/segtree/rollback_dynamic_segtree.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral Index\
    \ = long long>\n    requires(!std::same_as<std::remove_cv_t<Index>, bool>)\nstruct\
    \ RollbackDynamicSegtree {\n    using T = typename Monoid::value_type;\n    using\
    \ index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T value = Monoid::id();\n        int\
    \ left = 0;\n        int right = 0;\n    };\n\n    static constexpr int path_capacity\
    \ = std::numeric_limits<size_type>::digits + 1;\n    detail::UniformMonoidDomain<Monoid,\
    \ Index> _domain;\n    detail::RollbackJournal<Node> _journal;\n\n    int root()\
    \ const { return _journal[0].left; }\n\n    int new_node() { return _journal.emplace();\
    \ }\n\n    const T& value(int node, Index left, Index right, int depth) const\
    \ {\n        if (node) return _journal[node].value;\n        return _domain.default_product(depth,\
    \ left, right);\n    }\n\n    void update(int node, Index left, Index right, int\
    \ depth) {\n        Index middle = std::midpoint(left, right);\n        _journal.touch(node);\n\
    \        _journal[node].value = Monoid::op(\n            value(_journal[node].left,\
    \ left, middle, depth + 1),\n            value(_journal[node].right, middle, right,\
    \ depth + 1)\n        );\n    }\n\n    T prod_node(int node, Index left, Index\
    \ right, int depth, Index query_left, Index query_right) const {\n        if (query_right\
    \ <= left || right <= query_left) return Monoid::id();\n        if (query_left\
    \ <= left && right <= query_right) return value(node, left, right, depth);\n \
    \       Index middle = std::midpoint(left, right);\n        return Monoid::op(\n\
    \            prod_node(node ? _journal[node].left : 0, left, middle, depth + 1,\
    \ query_left, query_right),\n            prod_node(node ? _journal[node].right\
    \ : 0, middle, right, depth + 1, query_left, query_right)\n        );\n    }\n\
    \n    template <class Predicate>\n    Index max_right_node(int node, Index left,\
    \ Index right, int depth, Index query_left, T& product,\n                    \
    \     Predicate& predicate) const {\n        if (right <= query_left) return right;\n\
    \        if (query_left <= left) {\n            T next = Monoid::op(product, value(node,\
    \ left, right, depth));\n            if (predicate(next)) {\n                product\
    \ = std::move(next);\n                return right;\n            }\n         \
    \   Index middle = std::midpoint(left, right);\n            if (middle == left)\
    \ return left;\n        }\n        Index middle = std::midpoint(left, right);\n\
    \        Index result = max_right_node(node ? _journal[node].left : 0, left, middle,\
    \ depth + 1,\n                                      query_left, product, predicate);\n\
    \        if (result < middle) return result;\n        return max_right_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \          query_left, product, predicate);\n    }\n\n    template <class Predicate>\n\
    \    Index min_left_node(int node, Index left, Index right, int depth, Index query_right,\
    \ T& product,\n                        Predicate& predicate) const {\n       \
    \ if (query_right <= left) return left;\n        if (right <= query_right) {\n\
    \            T next = Monoid::op(value(node, left, right, depth), product);\n\
    \            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return left;\n            }\n            Index middle = std::midpoint(left,\
    \ right);\n            if (middle == left) return right;\n        }\n        Index\
    \ middle = std::midpoint(left, right);\n        Index result = min_left_node(node\
    \ ? _journal[node].right : 0, middle, right, depth + 1,\n                    \
    \                 query_right, product, predicate);\n        if (middle < result)\
    \ return result;\n        return min_left_node(node ? _journal[node].left : 0,\
    \ left, middle, depth + 1,\n                             query_right, product,\
    \ predicate);\n    }\n\n   public:\n    RollbackDynamicSegtree() : RollbackDynamicSegtree(Index(0),\
    \ Index(0)) {}\n    explicit RollbackDynamicSegtree(Index n) : RollbackDynamicSegtree(Index(0),\
    \ n) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0) <=\
    \ n);\n    }\n    RollbackDynamicSegtree(Index left, Index right)\n        : RollbackDynamicSegtree(left,\
    \ right, Monoid::id()) {}\n    RollbackDynamicSegtree(Index left, Index right,\
    \ T initial_value)\n        : _domain(left, right, std::move(initial_value)) {\n\
    \        _journal.emplace();\n    }\n\n    size_type size() const { return _domain.size();\
    \ }\n    bool empty() const { return _domain.empty(); }\n    Index left_bound()\
    \ const { return _domain.left_bound(); }\n    Index right_bound() const { return\
    \ _domain.right_bound(); }\n    const T& initial_value() const { return _domain.initial_value();\
    \ }\n\n    void reserve(std::size_t node_capacity) {\n        _journal.nodes.reserve(node_capacity\
    \ + 1);\n        _journal.saved_epoch.reserve(node_capacity + 1);\n    }\n\n \
    \   std::size_t node_count() const { return _journal.nodes.size() - 1; }\n\n \
    \   void set(Index pos, T x) {\n        assert(left_bound() <= pos && pos < right_bound());\n\
    \        if (!root()) {\n            int node = new_node();\n            _journal.touch(0);\n\
    \            _journal[0].left = node;\n        }\n\n        std::array<int, path_capacity>\
    \ path;\n        std::array<Index, path_capacity> path_left;\n        std::array<Index,\
    \ path_capacity> path_right;\n        int depth = 0;\n        int node = root();\n\
    \        Index left = left_bound();\n        Index right = right_bound();\n\n\
    \        while (true) {\n            path[depth] = node;\n            path_left[depth]\
    \ = left;\n            path_right[depth] = right;\n            ++depth;\n    \
    \        Index middle = std::midpoint(left, right);\n            if (middle ==\
    \ left) break;\n            if (pos < middle) {\n                if (!_journal[node].left)\
    \ {\n                    int child = new_node();\n                    _journal.touch(node);\n\
    \                    _journal[node].left = child;\n                }\n       \
    \         node = _journal[node].left;\n                right = middle;\n     \
    \       } else {\n                if (!_journal[node].right) {\n             \
    \       int child = new_node();\n                    _journal.touch(node);\n \
    \                   _journal[node].right = child;\n                }\n       \
    \         node = _journal[node].right;\n                left = middle;\n     \
    \       }\n        }\n        _journal.touch(node);\n        _journal[node].value\
    \ = std::move(x);\n        for (int index = depth - 2; index >= 0; --index) {\n\
    \            update(path[index], path_left[index], path_right[index], index);\n\
    \        }\n    }\n\n    void set_inplace(Index pos, T x) { set(pos, std::move(x));\
    \ }\n\n    T get(Index pos) const {\n        assert(left_bound() <= pos && pos\
    \ < right_bound());\n        int node = root();\n        Index left = left_bound();\n\
    \        Index right = right_bound();\n        int depth = 0;\n        while (node)\
    \ {\n            Index middle = std::midpoint(left, right);\n            if (middle\
    \ == left) return value(node, left, right, depth);\n            if (pos < middle)\
    \ {\n                node = _journal[node].left;\n                right = middle;\n\
    \            } else {\n                node = _journal[node].right;\n        \
    \        left = middle;\n            }\n            ++depth;\n        }\n    \
    \    return initial_value();\n    }\n\n    T operator[](Index pos) const { return\
    \ get(pos); }\n    T prod(Index left, Index right) const {\n        assert(left_bound()\
    \ <= left && left <= right && right <= right_bound());\n        if (left == right)\
    \ return Monoid::id();\n        return prod_node(root(), left_bound(), right_bound(),\
    \ 0, left, right);\n    }\n    T all_prod() const { return value(root(), left_bound(),\
    \ right_bound(), 0); }\n\n    template <class Predicate>\n    Index max_right(Index\
    \ left, Predicate predicate) const {\n        assert(left_bound() <= left && left\
    \ <= right_bound());\n        assert(predicate(Monoid::id()));\n        if (left\
    \ == right_bound()) return right_bound();\n        T product = Monoid::id();\n\
    \        return max_right_node(root(), left_bound(), right_bound(), 0, left, product,\
    \ predicate);\n    }\n\n    template <class Predicate>\n    Index min_left(Index\
    \ right, Predicate predicate) const {\n        assert(left_bound() <= right &&\
    \ right <= right_bound());\n        assert(predicate(Monoid::id()));\n       \
    \ if (right == left_bound()) return left_bound();\n        T product = Monoid::id();\n\
    \        return min_left_node(root(), left_bound(), right_bound(), 0, right, product,\
    \ predicate);\n    }\n\n    int snapshot() { return _journal.snapshot(); }\n \
    \   int snapshot_count() const { return _journal.snapshot_count(); }\n    void\
    \ reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n    void\
    \ rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _journal.clear(); _journal.emplace();\
    \ }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/rollback_lazy_segtree.hpp\"\
    \n\n\n\n#include <bit>\n#line 9 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\n#line\
    \ 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T\
    \ x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace math\n\
    }  // namespace m1une\n\n\n#line 13 \"ds/segtree/rollback_lazy_segtree.hpp\"\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct RollbackLazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    struct\
    \ Node {\n        T value = ActedMonoid::id();\n        F lazy = ActedMonoid::op_id();\n\
    \        bool has_lazy = false;\n    };\n\n    int _n = 0;\n    int _size = 1;\n\
    \    int _log = 0;\n    detail::RollbackJournal<Node> _journal;\n\n    static\
    \ T mapping_at(const F& f, const T& value, long long ordinal) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ordinal);\n        } else {\n\
    \            return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ordinal) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ordinal);\n        } else {\n            return f;\n        }\n    }\n\n   \
    \ template <class U>\n    static T make_value(const U& value, int index) {\n \
    \       if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n           \
    \ return ActedMonoid::make(value);\n        } else if constexpr (requires(U x,\
    \ int i) { ActedMonoid::make(x, i); }) {\n            return ActedMonoid::make(value,\
    \ index);\n        } else {\n            return static_cast<T>(value);\n     \
    \   }\n    }\n\n    int node_length(int node) const {\n        int level = std::bit_width(static_cast<unsigned\
    \ int>(node)) - 1;\n        return _size >> level;\n    }\n\n    int node_left(int\
    \ node) const {\n        int level = std::bit_width(static_cast<unsigned int>(node))\
    \ - 1;\n        int length = _size >> level;\n        return (node - (1 << level))\
    \ * length;\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node <<\
    \ 1].value,\n            _journal[node << 1 | 1].value\n        );\n    }\n\n\
    \    void all_apply(int node, const F& f) {\n        _journal.touch(node);\n \
    \       _journal[node].value = mapping_at(f, _journal[node].value, 0);\n     \
    \   if (node < _size) {\n            _journal[node].lazy = ActedMonoid::op_comp(f,\
    \ _journal[node].lazy);\n            _journal[node].has_lazy = true;\n       \
    \ }\n    }\n\n    void push(int node) {\n        if (!_journal[node].has_lazy)\
    \ return;\n        F lazy = _journal[node].lazy;\n        all_apply(node << 1,\
    \ lazy);\n        all_apply(node << 1 | 1, shift_operator(lazy, node_length(node)\
    \ / 2));\n        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n    }\n\n    template <class U>\n \
    \   void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = int(m1une::math::bit_ceil(static_cast<unsigned int>(_n)));\n\
    \        _log = 0;\n        while ((1U << _log) < static_cast<unsigned int>(_size))\
    \ ++_log;\n        _journal.nodes.assign(2 * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int index = 0; index < _n; ++index) {\n            _journal[_size\
    \ + index].value = make_value(values[index], index);\n        }\n        for (int\
    \ node = _size - 1; node > 0; --node) {\n            _journal[node].value = ActedMonoid::op(\n\
    \                _journal[node << 1].value,\n                _journal[node <<\
    \ 1 | 1].value\n            );\n        }\n    }\n\n   public:\n    RollbackLazySegtree()\
    \ { build(std::vector<T>()); }\n    explicit RollbackLazySegtree(int n) {\n  \
    \      assert(0 <= n);\n        build(std::vector<T>(n, ActedMonoid::id()));\n\
    \    }\n    explicit RollbackLazySegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackLazySegtree(std::vector<T>&& values) { build(values);\
    \ }\n\n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackLazySegtree(const std::vector<U>& values) { build(values); }\n\n   \
    \ int size() const { return _n; }\n    bool empty() const { return _n == 0; }\n\
    \    std::size_t node_count() const { return _journal.nodes.size(); }\n\n    void\
    \ set(int pos, T value) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        _journal.touch(node);\n        _journal[node].value = std::move(value);\n\
    \        for (int level = 1; level <= _log; ++level) update(node >> level);\n\
    \    }\n\n    void set_inplace(int pos, T value) { set(pos, std::move(value));\
    \ }\n\n    T get(int pos) {\n        assert(0 <= pos && pos < _n);\n        int\
    \ node = pos + _size;\n        for (int level = _log; level >= 1; --level) push(node\
    \ >> level);\n        return _journal[node].value;\n    }\n\n    T operator[](int\
    \ pos) { return get(pos); }\n\n    T prod(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left == right) return\
    \ ActedMonoid::id();\n        left += _size;\n        right += _size;\n      \
    \  for (int level = _log; level >= 1; --level) {\n            if (((left >> level)\
    \ << level) != left) push(left >> level);\n            if (((right >> level) <<\
    \ level) != right) push((right - 1) >> level);\n        }\n        T left_product\
    \ = ActedMonoid::id();\n        T right_product = ActedMonoid::id();\n       \
    \ while (left < right) {\n            if (left & 1) left_product = ActedMonoid::op(left_product,\
    \ _journal[left++].value);\n            if (right & 1) right_product = ActedMonoid::op(_journal[--right].value,\
    \ right_product);\n            left >>= 1;\n            right >>= 1;\n       \
    \ }\n        return ActedMonoid::op(left_product, right_product);\n    }\n\n \
    \   T all_prod() const { return _journal[1].value; }\n\n    std::vector<T> to_vector()\
    \ {\n        for (int node = 1; node < _size; ++node) push(node);\n        std::vector<T>\
    \ result;\n        result.reserve(_n);\n        for (int index = 0; index < _n;\
    \ ++index) result.push_back(_journal[_size + index].value);\n        return result;\n\
    \    }\n\n    std::vector<T> to_vector(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        std::vector<T> result;\n\
    \        result.reserve(right - left);\n        for (int index = left; index <\
    \ right; ++index) result.push_back(get(index));\n        return result;\n    }\n\
    \n    void apply(int pos, const F& f) {\n        assert(0 <= pos && pos < _n);\n\
    \        int node = pos + _size;\n        for (int level = _log; level >= 1; --level)\
    \ push(node >> level);\n        _journal.touch(node);\n        _journal[node].value\
    \ = mapping_at(f, _journal[node].value, 0);\n        for (int level = 1; level\
    \ <= _log; ++level) update(node >> level);\n    }\n\n    void apply(int left,\
    \ int right, const F& f) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        if (left == right) return;\n        int base_left = left;\n\
    \        left += _size;\n        right += _size;\n        for (int level = _log;\
    \ level >= 1; --level) {\n            if (((left >> level) << level) != left)\
    \ push(left >> level);\n            if (((right >> level) << level) != right)\
    \ push((right - 1) >> level);\n        }\n        int saved_left = left;\n   \
    \     int saved_right = right;\n        while (left < right) {\n            if\
    \ (left & 1) {\n                all_apply(left, shift_operator(f, node_left(left)\
    \ - base_left));\n                ++left;\n            }\n            if (right\
    \ & 1) {\n                --right;\n                all_apply(right, shift_operator(f,\
    \ node_left(right) - base_left));\n            }\n            left >>= 1;\n  \
    \          right >>= 1;\n        }\n        left = saved_left;\n        right\
    \ = saved_right;\n        for (int level = 1; level <= _log; ++level) {\n    \
    \        if (((left >> level) << level) != left) update(left >> level);\n    \
    \        if (((right >> level) << level) != right) update((right - 1) >> level);\n\
    \        }\n    }\n\n    void apply_inplace(int pos, const F& f) { apply(pos,\
    \ f); }\n    void apply_inplace(int left, int right, const F& f) { apply(left,\
    \ right, f); }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        int node = left + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push(node >> level);\n        T\
    \ product = ActedMonoid::id();\n        do {\n            while ((node & 1) ==\
    \ 0) node >>= 1;\n            T next = ActedMonoid::op(product, _journal[node].value);\n\
    \            if (!predicate(next)) {\n                while (node < _size) {\n\
    \                    push(node);\n                    node <<= 1;\n          \
    \          next = ActedMonoid::op(product, _journal[node].value);\n          \
    \          if (predicate(next)) {\n                        product = std::move(next);\n\
    \                        ++node;\n                    }\n                }\n \
    \               return node - _size;\n            }\n            product = std::move(next);\n\
    \            ++node;\n        } while ((node & -node) != node);\n        return\
    \ _n;\n    }\n\n    template <class Predicate>\n    int min_left(int right, Predicate\
    \ predicate) {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  for (int level = _log; level >= 1; --level) push((node - 1) >> level);\n  \
    \      T product = ActedMonoid::id();\n        do {\n            --node;\n   \
    \         while (node > 1 && (node & 1)) node >>= 1;\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    push(node);\n                    node = node\
    \ << 1 | 1;\n                    next = ActedMonoid::op(_journal[node].value,\
    \ product);\n                    if (predicate(next)) {\n                    \
    \    product = std::move(next);\n                        --node;\n           \
    \         }\n                }\n                return node + 1 - _size;\n   \
    \         }\n            product = std::move(next);\n        } while ((node &\
    \ -node) != node);\n        return 0;\n    }\n\n    int snapshot() { return _journal.snapshot();\
    \ }\n    int snapshot_count() const { return _journal.snapshot_count(); }\n  \
    \  void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }\n\
    \    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { _n = 0; _size = 1; _log\
    \ = 0; _journal.clear(); }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n#line 1 \"ds/segtree/rollback_segtree.hpp\"\n\n\n\n#line 10 \"ds/segtree/rollback_segtree.hpp\"\
    \n\n#line 12 \"ds/segtree/rollback_segtree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct RollbackSegtree {\n\
    \    using T = typename Monoid::value_type;\n\n   private:\n    struct Entry {\n\
    \        int pos;\n        T value;\n    };\n    struct Checkpoint {\n       \
    \ std::size_t change_size;\n        std::uint64_t epoch;\n    };\n\n    int _n\
    \ = 0;\n    int _size = 1;\n    std::vector<T> _data = std::vector<T>(2, Monoid::id());\n\
    \    std::vector<Entry> _history;\n    std::vector<Checkpoint> _checkpoints;\n\
    \    std::vector<std::uint64_t> _saved_epoch;\n    std::uint64_t _next_epoch =\
    \ 1;\n\n    std::uint64_t new_epoch() {\n        if (_next_epoch == 0) {\n   \
    \         std::fill(_saved_epoch.begin(), _saved_epoch.end(), 0);\n          \
    \  _next_epoch = 1;\n        }\n        return _next_epoch++;\n    }\n\n    template\
    \ <class U>\n    static T make_value(const U& value, int index) {\n        if\
    \ constexpr (requires(U x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n\
    \        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n\
    \            return Monoid::make(value, index);\n        } else {\n          \
    \  return static_cast<T>(value);\n        }\n    }\n\n    void assign(int pos,\
    \ T value) {\n        int node = pos + _size;\n        _data[node] = std::move(value);\n\
    \        while (node >>= 1) {\n            _data[node] = Monoid::op(_data[node\
    \ << 1], _data[node << 1 | 1]);\n        }\n    }\n\n    template <class U>\n\
    \    void build(const std::vector<U>& values) {\n        _n = int(values.size());\n\
    \        _size = 1;\n        while (_size < _n) _size <<= 1;\n        _data.assign(2\
    \ * _size, Monoid::id());\n        _saved_epoch.assign(_n, 0);\n        for (int\
    \ index = 0; index < _n; ++index) {\n            _data[_size + index] = make_value(values[index],\
    \ index);\n        }\n        for (int node = _size - 1; node > 0; --node) {\n\
    \            _data[node] = Monoid::op(_data[node << 1], _data[node << 1 | 1]);\n\
    \        }\n    }\n\n   public:\n    RollbackSegtree() = default;\n    explicit\
    \ RollbackSegtree(int n) { assert(0 <= n); build(std::vector<T>(n, Monoid::id()));\
    \ }\n    explicit RollbackSegtree(const std::vector<T>& values) { build(values);\
    \ }\n    explicit RollbackSegtree(std::vector<T>&& values) { build(values); }\n\
    \n    template <class U>\n        requires(!std::same_as<U, T>)\n    explicit\
    \ RollbackSegtree(const std::vector<U>& values) { build(values); }\n\n    int\
    \ size() const { return _n; }\n    bool empty() const { return _n == 0; }\n  \
    \  std::size_t node_count() const { return _data.size(); }\n\n    void set(int\
    \ pos, T value) {\n        assert(0 <= pos && pos < _n);\n        if (!_checkpoints.empty()\
    \ && _saved_epoch[pos] != _checkpoints.back().epoch) {\n            _saved_epoch[pos]\
    \ = _checkpoints.back().epoch;\n            _history.push_back(Entry{pos, get(pos)});\n\
    \        }\n        assign(pos, std::move(value));\n    }\n\n    void set_inplace(int\
    \ pos, T value) { set(pos, std::move(value)); }\n\n    T get(int pos) const {\n\
    \        assert(0 <= pos && pos < _n);\n        return _data[_size + pos];\n \
    \   }\n\n    T operator[](int pos) const { return get(pos); }\n\n    T prod(int\
    \ left, int right) const {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        T left_product = Monoid::id();\n        T right_product = Monoid::id();\n\
    \        for (left += _size, right += _size; left < right; left >>= 1, right >>=\
    \ 1) {\n            if (left & 1) left_product = Monoid::op(left_product, _data[left++]);\n\
    \            if (right & 1) right_product = Monoid::op(_data[--right], right_product);\n\
    \        }\n        return Monoid::op(left_product, right_product);\n    }\n\n\
    \    T all_prod() const { return _data[1]; }\n\n    std::vector<T> to_vector()\
    \ const { return to_vector(0, _n); }\n    std::vector<T> to_vector(int left, int\
    \ right) const {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        return std::vector<T>(_data.begin() + _size + left, _data.begin() + _size\
    \ + right);\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) const {\n        assert(0 <= left && left <= _n);\n   \
    \     assert(predicate(Monoid::id()));\n        if (left == _n) return _n;\n \
    \       int node = left + _size;\n        T product = Monoid::id();\n        do\
    \ {\n            while ((node & 1) == 0) node >>= 1;\n            T next = Monoid::op(product,\
    \ _data[node]);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node <<= 1;\n                    next = Monoid::op(product,\
    \ _data[node]);\n                    if (predicate(next)) {\n                \
    \        product = std::move(next);\n                        ++node;\n       \
    \             }\n                }\n                return std::min(_n, node -\
    \ _size);\n            }\n            product = std::move(next);\n           \
    \ ++node;\n        } while ((node & -node) != node);\n        return _n;\n   \
    \ }\n\n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ const {\n        assert(0 <= right && right <= _n);\n        assert(predicate(Monoid::id()));\n\
    \        if (right == 0) return 0;\n        int node = right + _size;\n      \
    \  T product = Monoid::id();\n        do {\n            --node;\n            while\
    \ (node > 1 && (node & 1)) node >>= 1;\n            T next = Monoid::op(_data[node],\
    \ product);\n            if (!predicate(next)) {\n                while (node\
    \ < _size) {\n                    node = node << 1 | 1;\n                    next\
    \ = Monoid::op(_data[node], product);\n                    if (predicate(next))\
    \ {\n                        product = std::move(next);\n                    \
    \    --node;\n                    }\n                }\n                return\
    \ std::max(0, node + 1 - _size);\n            }\n            product = std::move(next);\n\
    \        } while ((node & -node) != node);\n        return 0;\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(Checkpoint{_history.size(), new_epoch()});\n\
    \        return int(_checkpoints.size());\n    }\n    int snapshot_count() const\
    \ { return int(_checkpoints.size()); }\n    void reserve_snapshots(int count)\
    \ { assert(0 <= count); _checkpoints.reserve(count); }\n\n    void rollback(int\
    \ state) {\n        assert(1 <= state && state <= snapshot_count());\n       \
    \ while (_history.size() > _checkpoints[state - 1].change_size) {\n          \
    \  Entry entry = std::move(_history.back());\n            _history.pop_back();\n\
    \            assign(entry.pos, std::move(entry.value));\n        }\n        _checkpoints.resize(state);\n\
    \        _checkpoints.back().epoch = new_epoch();\n    }\n    void clear_history()\
    \ {\n        _history.clear();\n        _checkpoints.clear();\n        std::fill(_saved_epoch.begin(),\
    \ _saved_epoch.end(), 0);\n    }\n    void release() {\n        _n = 0;\n    \
    \    _size = 1;\n        _data.assign(2, Monoid::id());\n        _history.clear();\n\
    \        _checkpoints.clear();\n        _saved_epoch.clear();\n        _next_epoch\
    \ = 1;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"\
    ds/segtree/rollback_segtree_beats.hpp\"\n\n\n\n#line 8 \"ds/segtree/rollback_segtree_beats.hpp\"\
    \n\n#line 1 \"beats_acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"beats_acted_monoid/concept.hpp\"\
    \n\n#line 7 \"beats_acted_monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace\
    \ beats_acted_monoid {\n\n// An acted monoid whose action may require descent\
    \ before it can be applied.\ntemplate <typename AM>\nconcept IsBeatsActedMonoid\
    \ = m1une::acted_monoid::IsActedMonoid<AM> &&\n    requires(typename AM::value_type\
    \ x, typename AM::operator_type f) {\n        { AM::can_apply(f, x) } -> std::same_as<bool>;\n\
    \    };\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n#line\
    \ 12 \"ds/segtree/rollback_segtree_beats.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// Generic Segment Tree Beats for actions that may require recursive\
    \ descent.\ntemplate <m1une::beats_acted_monoid::IsBeatsActedMonoid ActedMonoid>\n\
    struct RollbackSegtreeBeats {\n    using value_type = typename ActedMonoid::value_type;\n\
    \    using operator_type = typename ActedMonoid::operator_type;\n    using T =\
    \ value_type;\n    using F = operator_type;\n\n   private:\n    int _n = 0;\n\
    \    int _size = 1;\n    struct Node {\n        T value = ActedMonoid::id();\n\
    \        F lazy = ActedMonoid::op_id();\n        bool has_lazy = false;\n    };\n\
    \n    detail::RollbackJournal<Node> _journal;\n\n    static T mapping_at(const\
    \ F& f, const T& value, long long ordinal) {\n        if constexpr (requires(F\
    \ g, T x, long long i) {\n            ActedMonoid::mapping(g, x, i);\n       \
    \ }) {\n            return ActedMonoid::mapping(f, value, ordinal);\n        }\
    \ else {\n            return ActedMonoid::mapping(f, value);\n        }\n    }\n\
    \n    static bool can_apply_at(const F& f, const T& value, long long ordinal)\
    \ {\n        if constexpr (requires(F g, T x, long long i) {\n            ActedMonoid::can_apply(g,\
    \ x, i);\n        }) {\n            return ActedMonoid::can_apply(f, value, ordinal);\n\
    \        } else {\n            return ActedMonoid::can_apply(f, value);\n    \
    \    }\n    }\n\n    static F shift_operator(const F& f, long long ordinal) {\n\
    \        if constexpr (requires(F g, long long i) {\n            ActedMonoid::op_shift(g,\
    \ i);\n        }) {\n            return ActedMonoid::op_shift(f, ordinal);\n \
    \       } else {\n            return f;\n        }\n    }\n\n    void initialize(std::vector<T>&&\
    \ values) {\n        _journal.clear();\n        _n = int(values.size());\n   \
    \     _size = int(m1une::math::bit_ceil((unsigned int)_n));\n        _journal.nodes.assign(2\
    \ * _size, Node());\n        _journal.saved_epoch.assign(_journal.nodes.size(),\
    \ 0);\n        for (int i = 0; i < _n; ++i) {\n            _journal[_size + i].value\
    \ = std::move(values[i]);\n        }\n        for (int k = _size - 1; k >= 1;\
    \ --k) update(k);\n    }\n\n    void update(int node) {\n        _journal.touch(node);\n\
    \        _journal[node].value = ActedMonoid::op(\n            _journal[node *\
    \ 2].value,\n            _journal[node * 2 + 1].value\n        );\n    }\n\n \
    \   void all_apply(int node, int left, int right, const F& f) {\n        if (_n\
    \ <= left) return;\n        if (can_apply_at(f, _journal[node].value, 0)) {\n\
    \            _journal.touch(node);\n            _journal[node].value = mapping_at(f,\
    \ _journal[node].value, 0);\n            if (node < _size) {\n               \
    \ _journal[node].lazy = ActedMonoid::op_comp(f, _journal[node].lazy);\n      \
    \          _journal[node].has_lazy = true;\n            }\n            return;\n\
    \        }\n\n        assert(right - left > 1);\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        all_apply(node * 2,\
    \ left, middle, f);\n        all_apply(\n            node * 2 + 1,\n         \
    \   middle,\n            right,\n            shift_operator(f, middle - left)\n\
    \        );\n        update(node);\n    }\n\n    void push(int node, int left,\
    \ int right) {\n        assert(right - left > 1);\n        if (!_journal[node].has_lazy)\
    \ return;\n        int middle = left + (right - left) / 2;\n        F f = _journal[node].lazy;\n\
    \        _journal.touch(node);\n        _journal[node].lazy = ActedMonoid::op_id();\n\
    \        _journal[node].has_lazy = false;\n        all_apply(node * 2, left, middle,\
    \ f);\n        all_apply(\n            node * 2 + 1,\n            middle,\n  \
    \          right,\n            shift_operator(f, middle - left)\n        );\n\
    \    }\n\n    void set_impl(\n        int node,\n        int left,\n        int\
    \ right,\n        int index,\n        T value\n    ) {\n        if (right - left\
    \ == 1) {\n            _journal.touch(node);\n            _journal[node].value\
    \ = std::move(value);\n            return;\n        }\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            set_impl(node * 2, left, middle, index, std::move(value));\n\
    \        } else {\n            set_impl(\n                node * 2 + 1,\n    \
    \            middle,\n                right,\n                index,\n       \
    \         std::move(value)\n            );\n        }\n        update(node);\n\
    \    }\n\n    T get_impl(int node, int left, int right, int index) {\n       \
    \ if (right - left == 1) return _journal[node].value;\n        push(node, left,\
    \ right);\n        int middle = left + (right - left) / 2;\n        if (index\
    \ < middle) {\n            return get_impl(node * 2, left, middle, index);\n \
    \       }\n        return get_impl(node * 2 + 1, middle, right, index);\n    }\n\
    \n    T prod_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_left,\n        int query_right\n    ) {\n        if (\n   \
    \         query_right <= left || right <= query_left || _n <= left\n        )\
    \ {\n            return ActedMonoid::id();\n        }\n        if (query_left\
    \ <= left && right <= query_right) {\n            return _journal[node].value;\n\
    \        }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        return ActedMonoid::op(\n            prod_impl(\n    \
    \            node * 2,\n                left,\n                middle,\n     \
    \           query_left,\n                query_right\n            ),\n       \
    \     prod_impl(\n                node * 2 + 1,\n                middle,\n   \
    \             right,\n                query_left,\n                query_right\n\
    \            )\n        );\n    }\n\n    void apply_impl(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        int base_left,\n        const F& f\n    ) {\n        if (\n         \
    \   query_right <= left || right <= query_left || _n <= left\n        ) {\n  \
    \          return;\n        }\n        if (query_left <= left && right <= query_right)\
    \ {\n            all_apply(\n                node,\n                left,\n  \
    \              right,\n                shift_operator(f, left - base_left)\n \
    \           );\n            return;\n        }\n        push(node, left, right);\n\
    \        int middle = left + (right - left) / 2;\n        apply_impl(\n      \
    \      node * 2,\n            left,\n            middle,\n            query_left,\n\
    \            query_right,\n            base_left,\n            f\n        );\n\
    \        apply_impl(\n            node * 2 + 1,\n            middle,\n       \
    \     right,\n            query_left,\n            query_right,\n            base_left,\n\
    \            f\n        );\n        update(node);\n    }\n\n    void collect_impl(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        std::vector<T>& result\n    ) {\n        if\
    \ (\n            query_right <= left || right <= query_left || _n <= left\n  \
    \      ) {\n            return;\n        }\n        if (right - left == 1) {\n\
    \            result.push_back(_journal[node].value);\n            return;\n  \
    \      }\n        push(node, left, right);\n        int middle = left + (right\
    \ - left) / 2;\n        collect_impl(\n            node * 2,\n            left,\n\
    \            middle,\n            query_left,\n            query_right,\n    \
    \        result\n        );\n        collect_impl(\n            node * 2 + 1,\n\
    \            middle,\n            right,\n            query_left,\n          \
    \  query_right,\n            result\n        );\n    }\n\n    template <class\
    \ Predicate>\n    bool max_right_impl(\n        int node,\n        int left,\n\
    \        int right,\n        int query_left,\n        Predicate& predicate,\n\
    \        T& product,\n        int& answer\n    ) {\n        if (right <= query_left\
    \ || _n <= left) return true;\n        if (query_left <= left) {\n           \
    \ T next = ActedMonoid::op(product, _journal[node].value);\n            if (predicate(next))\
    \ {\n                product = std::move(next);\n                return true;\n\
    \            }\n            if (right - left == 1) {\n                answer =\
    \ left;\n                return false;\n            }\n        }\n        push(node,\
    \ left, right);\n        int middle = left + (right - left) / 2;\n        if (!max_right_impl(\n\
    \                node * 2,\n                left,\n                middle,\n \
    \               query_left,\n                predicate,\n                product,\n\
    \                answer\n            )) {\n            return false;\n       \
    \ }\n        return max_right_impl(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            predicate,\n       \
    \     product,\n            answer\n        );\n    }\n\n    template <class Predicate>\n\
    \    bool min_left_impl(\n        int node,\n        int left,\n        int right,\n\
    \        int query_right,\n        Predicate& predicate,\n        T& product,\n\
    \        int& answer\n    ) {\n        if (query_right <= left || _n <= left)\
    \ return true;\n        if (right <= query_right) {\n            T next = ActedMonoid::op(_journal[node].value,\
    \ product);\n            if (predicate(next)) {\n                product = std::move(next);\n\
    \                return true;\n            }\n            if (right - left ==\
    \ 1) {\n                answer = right;\n                return false;\n     \
    \       }\n        }\n        push(node, left, right);\n        int middle = left\
    \ + (right - left) / 2;\n        if (!min_left_impl(\n                node * 2\
    \ + 1,\n                middle,\n                right,\n                query_right,\n\
    \                predicate,\n                product,\n                answer\n\
    \            )) {\n            return false;\n        }\n        return min_left_impl(\n\
    \            node * 2,\n            left,\n            middle,\n            query_right,\n\
    \            predicate,\n            product,\n            answer\n        );\n\
    \    }\n\n   public:\n    RollbackSegtreeBeats() {\n        initialize({});\n\
    \    }\n\n    explicit RollbackSegtreeBeats(int n) {\n        assert(0 <= n);\n\
    \        initialize(std::vector<T>(n, ActedMonoid::id()));\n    }\n\n    explicit\
    \ RollbackSegtreeBeats(const std::vector<T>& values) {\n        initialize(std::vector<T>(values));\n\
    \    }\n\n    explicit RollbackSegtreeBeats(std::vector<T>&& values) {\n     \
    \   initialize(std::move(values));\n    }\n\n    template <typename U>\n    requires\
    \ (!std::same_as<U, T>) && (\n        requires(U x) { ActedMonoid::make(x); }\
    \ ||\n        requires(U x, int i) { ActedMonoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit RollbackSegtreeBeats(const std::vector<U>& values) {\n\
    \        std::vector<T> converted;\n        converted.reserve(values.size());\n\
    \        for (int i = 0; i < int(values.size()); ++i) {\n            if constexpr\
    \ (requires(U x) { ActedMonoid::make(x); }) {\n                converted.push_back(ActedMonoid::make(values[i]));\n\
    \            } else if constexpr (requires(U x, int index) {\n               \
    \ ActedMonoid::make(x, index);\n            }) {\n                converted.push_back(ActedMonoid::make(values[i],\
    \ i));\n            } else {\n                converted.push_back(static_cast<T>(values[i]));\n\
    \            }\n        }\n        initialize(std::move(converted));\n    }\n\n\
    \    int size() const {\n        return _n;\n    }\n\n    bool empty() const {\n\
    \        return _n == 0;\n    }\n\n    std::size_t node_count() const { return\
    \ _journal.nodes.size(); }\n\n    void set(int index, T value) {\n        assert(0\
    \ <= index && index < _n);\n        set_impl(1, 0, _size, index, std::move(value));\n\
    \    }\n    void set_inplace(int index, T value) { set(index, std::move(value));\
    \ }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n   \
    \     return get_impl(1, 0, _size, index);\n    }\n\n    T operator[](int index)\
    \ {\n        return get(index);\n    }\n\n    T prod(int left, int right) {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (left\
    \ == right) return ActedMonoid::id();\n        return prod_impl(1, 0, _size, left,\
    \ right);\n    }\n\n    T all_prod() const {\n        return _journal[1].value;\n\
    \    }\n\n    void apply(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        apply_impl(1, 0, _size, index, index + 1, index, f);\n    }\n\
    \n    void apply(int left, int right, F f) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        if (left == right) return;\n        apply_impl(1,\
    \ 0, _size, left, right, left, f);\n    }\n    void apply_inplace(int index, F\
    \ f) { apply(index, std::move(f)); }\n    void apply_inplace(int left, int right,\
    \ F f) {\n        apply(left, right, std::move(f));\n    }\n\n    std::vector<T>\
    \ to_vector() {\n        return to_vector(0, _n);\n    }\n\n    std::vector<T>\
    \ to_vector(int left, int right) {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        std::vector<T> result;\n        result.reserve(right\
    \ - left);\n        collect_impl(1, 0, _size, left, right, result);\n        return\
    \ result;\n    }\n\n    template <class Predicate>\n    int max_right(int left,\
    \ Predicate predicate) {\n        assert(0 <= left && left <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (left == _n) return _n;\n        T product = ActedMonoid::id();\n\
    \        int answer = _n;\n        max_right_impl(\n            1,\n         \
    \   0,\n            _size,\n            left,\n            predicate,\n      \
    \      product,\n            answer\n        );\n        return answer;\n    }\n\
    \n    template <class Predicate>\n    int min_left(int right, Predicate predicate)\
    \ {\n        assert(0 <= right && right <= _n);\n        assert(predicate(ActedMonoid::id()));\n\
    \        if (right == 0) return 0;\n        T product = ActedMonoid::id();\n \
    \       int answer = 0;\n        min_left_impl(\n            1,\n            0,\n\
    \            _size,\n            right,\n            predicate,\n            product,\n\
    \            answer\n        );\n        return answer;\n    }\n\n    int snapshot()\
    \ { return _journal.snapshot(); }\n    int snapshot_count() const { return _journal.snapshot_count();\
    \ }\n    void reserve_snapshots(int count) { _journal.reserve_snapshots(count);\
    \ }\n    void rollback(int state) { _journal.rollback(state); }\n    void clear_history()\
    \ { _journal.clear_history(); }\n    void release() { initialize({}); }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 1 \"ds/stack/rollback_stack.hpp\"\
    \n\n\n\n#line 8 \"ds/stack/rollback_stack.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <class T>\nstruct RollbackStack {\n   private:\n    enum class\
    \ Kind { push, pop, clear };\n    struct Entry {\n        Kind kind;\n       \
    \ std::optional<T> value;\n        std::vector<T> values;\n    };\n\n    std::vector<T>\
    \ _values;\n    std::vector<Entry> _history;\n    std::vector<std::size_t> _checkpoints;\n\
    \    std::size_t _stored_values = 0;\n\n   public:\n    RollbackStack() = default;\n\
    \n    int size() const { return int(_values.size()); }\n    bool empty() const\
    \ { return _values.empty(); }\n    std::size_t node_count() const { return _stored_values;\
    \ }\n\n    const T& top() const {\n        assert(!empty());\n        return _values.back();\n\
    \    }\n\n    void push(T value) {\n        if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push,\
    \ std::nullopt, {}});\n        _values.push_back(std::move(value));\n        ++_stored_values;\n\
    \    }\n\n    template <class... Args>\n    void emplace(Args&&... args) {\n \
    \       if (!_checkpoints.empty()) _history.push_back(Entry{Kind::push, std::nullopt,\
    \ {}});\n        _values.emplace_back(std::forward<Args>(args)...);\n        ++_stored_values;\n\
    \    }\n\n    void pop() {\n        assert(!empty());\n        if (_checkpoints.empty())\
    \ {\n            _values.pop_back();\n            --_stored_values;\n        }\
    \ else {\n            Entry entry{Kind::pop, std::nullopt, {}};\n            entry.value.emplace(std::move(_values.back()));\n\
    \            _values.pop_back();\n            _history.push_back(std::move(entry));\n\
    \        }\n    }\n\n    void clear() {\n        if (_checkpoints.empty()) {\n\
    \            _stored_values -= _values.size();\n            _values.clear();\n\
    \        } else {\n            Entry entry{Kind::clear, std::nullopt, {}};\n \
    \           entry.values = std::move(_values);\n            _values.clear();\n\
    \            _history.push_back(std::move(entry));\n        }\n    }\n\n    int\
    \ snapshot() {\n        _checkpoints.push_back(_history.size());\n        return\
    \ int(_checkpoints.size());\n    }\n    int snapshot_count() const { return int(_checkpoints.size());\
    \ }\n\n    void reserve_snapshots(int count) {\n        assert(0 <= count);\n\
    \        _checkpoints.reserve(count);\n    }\n\n   private:\n    void restore_one()\
    \ {\n        Entry entry = std::move(_history.back());\n        _history.pop_back();\n\
    \        if (entry.kind == Kind::push) {\n            _values.pop_back();\n  \
    \          --_stored_values;\n        } else if (entry.kind == Kind::pop) {\n\
    \            _values.push_back(std::move(*entry.value));\n        } else {\n \
    \           _values = std::move(entry.values);\n        }\n    }\n\n   public:\n\
    \    void rollback(int state) {\n        assert(1 <= state && state <= snapshot_count());\n\
    \        while (_history.size() > _checkpoints[state - 1]) restore_one();\n  \
    \      _checkpoints.resize(state);\n    }\n\n    void clear_history() {\n    \
    \    for (const Entry& entry : _history) {\n            if (entry.value) --_stored_values;\n\
    \            _stored_values -= entry.values.size();\n        }\n        _history.clear();\n\
    \        _checkpoints.clear();\n    }\n\n    void release() {\n        _values.clear();\n\
    \        _history.clear();\n        _checkpoints.clear();\n        _stored_values\
    \ = 0;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 19 \"\
    verify/ds/rollback_counterparts.test.cpp\"\n\n#line 22 \"verify/ds/rollback_counterparts.test.cpp\"\
    \n#include <iostream>\n#include <random>\n#line 25 \"verify/ds/rollback_counterparts.test.cpp\"\
    \n\n#line 1 \"acted_monoid/range_add_range_sum.hpp\"\n\n\n\nnamespace m1une {\n\
    namespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAddRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\ntemplate <typename T>\nstruct RangeAddRangeSum\
    \ {\n    using value_type = RangeAddRangeSumNode<T>;\n    using operator_type\
    \ = T;\n    static constexpr bool commutative = true;\n    static constexpr bool\
    \ operator_commutative = true;\n\n    // Value Monoid (Sum)\n    static constexpr\
    \ value_type id() {\n        return {T(0), 0};\n    }\n    static constexpr value_type\
    \ op(const value_type& a, const value_type& b) {\n        return {a.sum + b.sum,\
    \ a.size + b.size};\n    }\n    static constexpr value_type inv(const value_type&\
    \ x) {\n        return {-x.sum, -x.size};\n    }\n\n    // Operator Monoid (Add)\n\
    \    static constexpr operator_type op_id() {\n        return 0;\n    }\n    static\
    \ constexpr operator_type op_comp(const operator_type& f, const operator_type&\
    \ g) {\n        return f + g;\n    }\n\n    // Mapping (sum + f * size)\n    static\
    \ constexpr value_type mapping(const operator_type& f, const value_type& x) {\n\
    \        return {x.sum + f * x.size, x.size};\n    }\n\n    // Helper for initializing\
    \ a leaf node\n    static constexpr value_type make(const T& val) {\n        return\
    \ {val, 1};\n    }\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n\n\n\n\
    #line 8 \"beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n\nnamespace\
    \ m1une {\nnamespace beats_acted_monoid {\n\ntemplate <std::signed_integral T>\n\
    struct RangeChminChmaxAddRangeSumNode {\n    T sum;\n    T maximum;\n    T second_maximum;\n\
    \    T minimum;\n    T second_minimum;\n    int maximum_count;\n    int minimum_count;\n\
    \    int length;\n};\n\n// Beats acted monoid for range chmin/chmax/add updates\
    \ and range sum queries.\ntemplate <std::signed_integral T = long long>\nstruct\
    \ RangeChminChmaxAddRangeSum {\n    using value_type = RangeChminChmaxAddRangeSumNode<T>;\n\
    \n    // Represents f(x) = clamp(x + add, lower, upper).\n    struct operator_type\
    \ {\n        T add;\n        T lower;\n        T upper;\n    };\n\n    static\
    \ constexpr bool commutative = true;\n    static constexpr bool operator_commutative\
    \ = false;\n    static constexpr T negative_infinity = std::numeric_limits<T>::lowest();\n\
    \    static constexpr T positive_infinity = std::numeric_limits<T>::max();\n\n\
    \   private:\n    static constexpr T shift_lower_bound(T bound, T add) {\n   \
    \     return bound == negative_infinity ? bound : bound + add;\n    }\n\n    static\
    \ constexpr T shift_upper_bound(T bound, T add) {\n        return bound == positive_infinity\
    \ ? bound : bound + add;\n    }\n\n    static constexpr void apply_add(value_type&\
    \ value, T add) {\n        if (value.length == 0 || add == T(0)) return;\n   \
    \     value.sum += add * T(value.length);\n        value.maximum += add;\n   \
    \     value.minimum += add;\n        if (value.maximum_count != value.length)\
    \ {\n            value.second_maximum += add;\n        }\n        if (value.minimum_count\
    \ != value.length) {\n            value.second_minimum += add;\n        }\n  \
    \  }\n\n    static constexpr bool can_apply_chmin(\n        const value_type&\
    \ value,\n        T upper\n    ) {\n        return value.maximum <= upper ||\n\
    \            value.maximum_count == value.length ||\n            value.second_maximum\
    \ < upper;\n    }\n\n    static constexpr void apply_chmin(value_type& value,\
    \ T upper) {\n        if (value.maximum <= upper) return;\n        assert(can_apply_chmin(value,\
    \ upper));\n        value.sum +=\n            (upper - value.maximum) * T(value.maximum_count);\n\
    \        if (value.minimum == value.maximum) {\n            value.minimum = upper;\n\
    \        } else if (value.second_minimum == value.maximum) {\n            value.second_minimum\
    \ = upper;\n        }\n        value.maximum = upper;\n    }\n\n    static constexpr\
    \ bool can_apply_chmax(\n        const value_type& value,\n        T lower\n \
    \   ) {\n        return lower <= value.minimum ||\n            value.minimum_count\
    \ == value.length ||\n            lower < value.second_minimum;\n    }\n\n   \
    \ static constexpr void apply_chmax(value_type& value, T lower) {\n        if\
    \ (lower <= value.minimum) return;\n        assert(can_apply_chmax(value, lower));\n\
    \        value.sum +=\n            (lower - value.minimum) * T(value.minimum_count);\n\
    \        if (value.maximum == value.minimum) {\n            value.maximum = lower;\n\
    \        } else if (value.second_maximum == value.minimum) {\n            value.second_maximum\
    \ = lower;\n        }\n        value.minimum = lower;\n    }\n\n    static constexpr\
    \ value_type constant_value(T value, int length) {\n        return {\n       \
    \     value * T(length),\n            value,\n            negative_infinity,\n\
    \            value,\n            positive_infinity,\n            length,\n   \
    \         length,\n            length\n        };\n    }\n\n   public:\n    static\
    \ constexpr value_type id() {\n        return {\n            T(0),\n         \
    \   negative_infinity,\n            negative_infinity,\n            positive_infinity,\n\
    \            positive_infinity,\n            0,\n            0,\n            0\n\
    \        };\n    }\n\n    static constexpr value_type op(\n        const value_type&\
    \ left,\n        const value_type& right\n    ) {\n        if (left.length ==\
    \ 0) return right;\n        if (right.length == 0) return left;\n\n        value_type\
    \ result;\n        result.sum = left.sum + right.sum;\n        result.length =\
    \ left.length + right.length;\n\n        result.maximum = std::max(left.maximum,\
    \ right.maximum);\n        result.maximum_count = 0;\n        result.second_maximum\
    \ = negative_infinity;\n        if (left.maximum == result.maximum) {\n      \
    \      result.maximum_count += left.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                left.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                left.maximum\n      \
    \      );\n        }\n        if (right.maximum == result.maximum) {\n       \
    \     result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ = std::max(\n                result.second_maximum,\n                right.second_maximum\n\
    \            );\n        } else {\n            result.second_maximum = std::max(\n\
    \                result.second_maximum,\n                right.maximum\n     \
    \       );\n        }\n\n        result.minimum = std::min(left.minimum, right.minimum);\n\
    \        result.minimum_count = 0;\n        result.second_minimum = positive_infinity;\n\
    \        if (left.minimum == result.minimum) {\n            result.minimum_count\
    \ += left.minimum_count;\n            result.second_minimum = std::min(\n    \
    \            result.second_minimum,\n                left.second_minimum\n   \
    \         );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                left.minimum\n      \
    \      );\n        }\n        if (right.minimum == result.minimum) {\n       \
    \     result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ = std::min(\n                result.second_minimum,\n                right.second_minimum\n\
    \            );\n        } else {\n            result.second_minimum = std::min(\n\
    \                result.second_minimum,\n                right.minimum\n     \
    \       );\n        }\n        return result;\n    }\n\n    static constexpr operator_type\
    \ op_id() {\n        return {T(0), negative_infinity, positive_infinity};\n  \
    \  }\n\n    // Returns f(g(x)).\n    static constexpr operator_type op_comp(\n\
    \        const operator_type& f,\n        const operator_type& g\n    ) {\n  \
    \      T lower = shift_lower_bound(g.lower, f.add);\n        T upper = shift_upper_bound(g.upper,\
    \ f.add);\n        return {\n            g.add + f.add,\n            std::clamp(lower,\
    \ f.lower, f.upper),\n            std::clamp(upper, f.lower, f.upper)\n      \
    \  };\n    }\n\n    static constexpr bool can_apply(\n        const operator_type&\
    \ f,\n        const value_type& value\n    ) {\n        if (value.length == 0\
    \ || f.lower == f.upper) return true;\n        value_type mapped = value;\n  \
    \      apply_add(mapped, f.add);\n        if (\n            mapped.maximum <=\
    \ f.lower ||\n            f.upper <= mapped.minimum\n        ) {\n           \
    \ return true;\n        }\n        if (!can_apply_chmax(mapped, f.lower)) return\
    \ false;\n        apply_chmax(mapped, f.lower);\n        return can_apply_chmin(mapped,\
    \ f.upper);\n    }\n\n    static constexpr value_type mapping(\n        const\
    \ operator_type& f,\n        const value_type& value\n    ) {\n        assert(can_apply(f,\
    \ value));\n        if (value.length == 0) return value;\n        if (f.lower\
    \ == f.upper) {\n            return constant_value(f.lower, value.length);\n \
    \       }\n        value_type result = value;\n        apply_add(result, f.add);\n\
    \        if (result.maximum <= f.lower) {\n            return constant_value(f.lower,\
    \ result.length);\n        }\n        if (f.upper <= result.minimum) {\n     \
    \       return constant_value(f.upper, result.length);\n        }\n        apply_chmax(result,\
    \ f.lower);\n        apply_chmin(result, f.upper);\n        return result;\n \
    \   }\n\n    static constexpr value_type make(const T& value) {\n        return\
    \ constant_value(value, 1);\n    }\n\n    static constexpr operator_type make_chmin(const\
    \ T& upper) {\n        return {T(0), negative_infinity, upper};\n    }\n\n   \
    \ static constexpr operator_type make_chmax(const T& lower) {\n        return\
    \ {T(0), lower, positive_infinity};\n    }\n\n    static constexpr operator_type\
    \ make_add(const T& add) {\n        return {add, negative_infinity, positive_infinity};\n\
    \    }\n};\n\n}  // namespace beats_acted_monoid\n}  // namespace m1une\n\n\n\
    #line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n    using\
    \ value_type = T;\n    static constexpr bool commutative = true;\n\n    // Returns\
    \ the identity element for addition, which is 0.\n    static constexpr T id()\
    \ {\n        return T(0);\n    }\n\n    // Returns the sum of a and b.\n    static\
    \ constexpr T op(const T& a, const T& b) {\n        return a + b;\n    }\n\n \
    \   static constexpr T inv(const T& x) {\n        return -x;\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n#line 29 \"verify/ds/rollback_counterparts.test.cpp\"\
    \n\nnamespace {\n\nusing Add = m1une::monoid::Add<long long>;\nusing RangeAddSum\
    \ = m1une::acted_monoid::RangeAddRangeSum<long long>;\n\nvoid assert_lazy_array(\n\
    \    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum>& array,\n    const\
    \ std::vector<long long>& expected\n) {\n    std::vector<RangeAddSum::value_type>\
    \ values = array.to_vector();\n    assert(values.size() == expected.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        assert(values[index].sum\
    \ == expected[index]);\n        assert(values[index].size == 1);\n    }\n}\n\n\
    void test_sequence_containers() {\n    m1une::ds::RollbackStack<int> stack;\n\
    \    stack.push(1);\n    int outer = stack.snapshot();\n    stack.emplace(2);\n\
    \    int inner = stack.snapshot();\n    stack.push(3);\n    stack.rollback(inner);\n\
    \    assert(stack.top() == 2 && stack.snapshot_count() == inner);\n    stack.pop();\n\
    \    stack.rollback(outer);\n    assert(stack.top() == 1 && stack.snapshot_count()\
    \ == outer);\n    stack.push(4);\n    stack.rollback(outer);\n    assert(stack.top()\
    \ == 1);\n\n    m1une::ds::RollbackQueue<int> queue;\n    queue.push(1);\n   \
    \ outer = queue.snapshot();\n    queue.push_back(2);\n    queue.pop_front();\n\
    \    assert(queue.front() == 2);\n    queue.rollback(outer);\n    assert(queue.front()\
    \ == 1 && queue.back() == 1);\n\n    m1une::ds::RollbackDeque<int> deque;\n  \
    \  deque.push_back(2);\n    outer = deque.snapshot();\n    deque.emplace_front(1);\n\
    \    deque.emplace_back(3);\n    deque.pop_front();\n    assert(deque.front()\
    \ == 2 && deque.back() == 3);\n    deque.rollback(outer);\n    assert(deque.front()\
    \ == 2 && deque.back() == 2);\n}\n\nvoid test_ordered_containers() {\n    m1une::ds::RollbackOrderedSet<int>\
    \ set({2, 1});\n    int outer = set.snapshot();\n    assert(set.insert(3));\n\
    \    assert(!set.insert(3));\n    assert(set.erase(1));\n    int inner = set.snapshot();\n\
    \    set.clear();\n    set.rollback(inner);\n    assert(set.to_vector() == std::vector<int>({2,\
    \ 3}));\n    set.rollback(outer);\n    assert(set.to_vector() == std::vector<int>({1,\
    \ 2}));\n\n    m1une::ds::RollbackOrderedMultiset<int> multiset({2, 2, 3});\n\
    \    outer = multiset.snapshot();\n    assert(multiset.erase_one(2));\n    multiset.insert(1,\
    \ 3);\n    assert(multiset.erase_all(3) == 1);\n    assert(multiset.count(1) ==\
    \ 3 && multiset.count(2) == 1);\n    multiset.rollback(outer);\n    assert(multiset.to_vector()\
    \ == std::vector<int>({2, 2, 3}));\n}\n\nvoid test_dynamic_arrays() {\n    m1une::ds::RollbackDynamicArray<int>\
    \ array(std::vector<int>{1, 2, 3});\n    int outer = array.snapshot();\n    array.insert(1,\
    \ 5);\n    array.reverse(0, 4);\n    array.erase(1, 3);\n    assert(array.to_vector()\
    \ == std::vector<int>({3, 1}));\n    array.rollback(outer);\n    assert(array.to_vector()\
    \ == std::vector<int>({1, 2, 3}));\n\n    m1une::ds::RollbackDynamicMonoidArray<Add>\
    \ monoid_array(\n        std::vector<long long>{1, 2, 3}\n    );\n    outer =\
    \ monoid_array.snapshot();\n    monoid_array.set(1, 7);\n    monoid_array.push_back(4);\n\
    \    assert(monoid_array.all_prod() == 15);\n    monoid_array.rollback(outer);\n\
    \    assert(monoid_array.to_vector() == std::vector<long long>({1, 2, 3}));\n\n\
    \    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> lazy_array(\n    \
    \    std::vector<long long>{1, 2, 3, 4}\n    );\n    outer = lazy_array.snapshot();\n\
    \    lazy_array.apply(0, 3, 4);\n    lazy_array.reverse(1, 4);\n    lazy_array.insert(2,\
    \ RangeAddSum::make(10));\n    lazy_array.erase(0);\n    assert(lazy_array.all_prod().sum\
    \ == 27);\n    int inner = lazy_array.snapshot();\n    lazy_array.clear();\n \
    \   assert(lazy_array.empty());\n    lazy_array.rollback(inner);\n    assert(lazy_array.all_prod().sum\
    \ == 27);\n    lazy_array.rollback(outer);\n    std::vector<RangeAddSum::value_type>\
    \ restored = lazy_array.to_vector();\n    assert(restored.size() == 4);\n    for\
    \ (int index = 0; index < 4; ++index) {\n        assert(restored[index].sum ==\
    \ index + 1);\n        assert(restored[index].size == 1);\n    }\n}\n\nvoid randomized_lazy_array_test()\
    \ {\n    std::mt19937 random(0);\n    std::vector<long long> naive = {0, 1, 2,\
    \ 3, 4, 5};\n    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> array(naive);\n\
    \    for (int round = 0; round < 80; ++round) {\n        int state = array.snapshot();\n\
    \        std::vector<long long> saved = naive;\n        for (int step = 0; step\
    \ < 35; ++step) {\n            int type = int(random() % 5);\n            if (type\
    \ == 0 && !naive.empty()) {\n                int pos = int(random() % naive.size());\n\
    \                long long value = int(random() % 31) - 15;\n                array.set(pos,\
    \ RangeAddSum::make(value));\n                naive[pos] = value;\n          \
    \  } else if (type == 1) {\n                int left = int(random() % (naive.size()\
    \ + 1));\n                int right = left + int(random() % (naive.size() - left\
    \ + 1));\n                long long add = int(random() % 11) - 5;\n          \
    \      array.apply(left, right, add);\n                for (int index = left;\
    \ index < right; ++index) naive[index] += add;\n            } else if (type ==\
    \ 2) {\n                int left = int(random() % (naive.size() + 1));\n     \
    \           int right = left + int(random() % (naive.size() - left + 1));\n  \
    \              array.reverse(left, right);\n                std::reverse(naive.begin()\
    \ + left, naive.begin() + right);\n            } else if (type == 3) {\n     \
    \           int pos = int(random() % (naive.size() + 1));\n                std::vector<long\
    \ long> raw_values = {\n                    int(random() % 21) - 10,\n       \
    \             int(random() % 21) - 10\n                };\n                std::vector<RangeAddSum::value_type>\
    \ values;\n                for (long long value : raw_values) {\n            \
    \        values.push_back(RangeAddSum::make(value));\n                }\n    \
    \            array.insert(pos, std::move(values));\n                naive.insert(\n\
    \                    naive.begin() + pos, raw_values.begin(), raw_values.end()\n\
    \                );\n            } else if (!naive.empty()) {\n              \
    \  int pos = int(random() % naive.size());\n                array.erase(pos);\n\
    \                naive.erase(naive.begin() + pos);\n            }\n          \
    \  assert_lazy_array(array, naive);\n        }\n        array.rollback(state);\n\
    \        naive = std::move(saved);\n        assert_lazy_array(array, naive);\n\
    \        array.clear_history();\n    }\n}\n\nvoid test_segment_trees() {\n   \
    \ m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});\n \
    \   int outer = seg.snapshot();\n    seg.set(1, 10);\n    seg.set(1, 12);\n  \
    \  assert(seg.all_prod() == 20);\n    int inner = seg.snapshot();\n    seg.set(0,\
    \ 8);\n    seg.rollback(inner);\n    assert(seg.all_prod() == 20);\n    seg.rollback(outer);\n\
    \    assert(seg.all_prod() == 10);\n\n    m1une::ds::RollbackLazySegtree<RangeAddSum>\
    \ lazy(\n        std::vector<long long>{1, 2, 3, 4}\n    );\n    outer = lazy.snapshot();\n\
    \    lazy.apply(1, 4, 5);\n    lazy.set(0, RangeAddSum::make(9));\n    assert(lazy.all_prod().sum\
    \ == 33);\n    assert(lazy.prod(1, 3).sum == 15);\n    lazy.rollback(outer);\n\
    \    assert(lazy.all_prod().sum == 10);\n\n    m1une::ds::RollbackDualSegtree<Add>\
    \ dual(4);\n    outer = dual.snapshot();\n    dual.apply(0, 3, 4);\n    dual.set(1,\
    \ 2);\n    assert(dual.get(0) == 4 && dual.get(1) == 2);\n    dual.rollback(outer);\n\
    \    assert(dual.get(0) == 0 && dual.get(1) == 0);\n\n    m1une::ds::RollbackDynamicSegtree<Add>\
    \ dynamic(-10, 10);\n    outer = dynamic.snapshot();\n    dynamic.set(-4, 7);\n\
    \    dynamic.set(8, 3);\n    assert(dynamic.all_prod() == 10);\n    dynamic.rollback(outer);\n\
    \    assert(dynamic.all_prod() == 0 && dynamic.node_count() == 0);\n\n    m1une::ds::RollbackDynamicLazySegtree<RangeAddSum>\
    \ dynamic_lazy(\n        -10, 10, RangeAddSum::id()\n    );\n    outer = dynamic_lazy.snapshot();\n\
    \    dynamic_lazy.set(-2, RangeAddSum::make(3));\n    dynamic_lazy.apply(-3, 2,\
    \ 4);\n    assert(dynamic_lazy.get(-2).sum == 7);\n    assert(dynamic_lazy.prod(-3,\
    \ 2).sum == 7);\n    dynamic_lazy.rollback(outer);\n    assert(dynamic_lazy.get(-2).sum\
    \ == 0 && dynamic_lazy.node_count() == 0);\n\n    m1une::ds::RollbackDynamicDualSegtree<Add>\
    \ dynamic_dual(-10, 10, 0);\n    outer = dynamic_dual.snapshot();\n    dynamic_dual.apply(-3,\
    \ 5, 7);\n    dynamic_dual.set(0, 2);\n    assert(dynamic_dual.get(-1) == 7 &&\
    \ dynamic_dual.get(0) == 2);\n    dynamic_dual.rollback(outer);\n    assert(dynamic_dual.get(-1)\
    \ == 0 && dynamic_dual.get(0) == 0);\n\n    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n    m1une::ds::RollbackSegtreeBeats<Beats> beats(\n        std::vector<long\
    \ long>{1, 5, 3, 7}\n    );\n    outer = beats.snapshot();\n    Beats::operator_type\
    \ chmin;\n    chmin.add = 0;\n    chmin.lower = Beats::negative_infinity;\n  \
    \  chmin.upper = 4;\n    beats.apply(0, 4, chmin);\n    assert(beats.all_prod().sum\
    \ == 12);\n    assert(beats.prod(1, 4).sum == 11);\n    beats.rollback(outer);\n\
    \    assert(beats.all_prod().sum == 16);\n}\n\nvoid randomized_segment_tree_test()\
    \ {\n    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n    std::mt19937 random(1);\n    constexpr int size = 24;\n    std::vector<long\
    \ long> naive(size);\n    std::vector<long long> lazy_naive(size);\n    m1une::ds::RollbackLazySegtree<RangeAddSum>\
    \ lazy(lazy_naive);\n    m1une::ds::RollbackSegtreeBeats<Beats> beats(naive);\n\
    \n    for (int round = 0; round < 70; ++round) {\n        int lazy_state = lazy.snapshot();\n\
    \        int beats_state = beats.snapshot();\n        std::vector<long long> saved\
    \ = naive;\n        std::vector<long long> lazy_saved = lazy_naive;\n        for\
    \ (int step = 0; step < 45; ++step) {\n            int type = int(random() % 3);\n\
    \            int left = int(random() % size);\n            int right = left +\
    \ 1 + int(random() % (size - left));\n            if (type == 0) {\n         \
    \       long long add = int(random() % 17) - 8;\n                lazy.apply(left,\
    \ right, add);\n                Beats::operator_type action;\n               \
    \ action.add = add;\n                action.lower = Beats::negative_infinity;\n\
    \                action.upper = Beats::positive_infinity;\n                beats.apply(left,\
    \ right, action);\n                for (int index = left; index < right; ++index)\
    \ naive[index] += add;\n                for (int index = left; index < right;\
    \ ++index) lazy_naive[index] += add;\n            } else if (type == 1) {\n  \
    \              long long value = int(random() % 41) - 20;\n                lazy.set(left,\
    \ RangeAddSum::make(value));\n                beats.set(left, Beats::make(value));\n\
    \                naive[left] = value;\n                lazy_naive[left] = value;\n\
    \            } else {\n                long long upper = int(random() % 31) -\
    \ 15;\n                Beats::operator_type action;\n                action.add\
    \ = 0;\n                action.lower = Beats::negative_infinity;\n           \
    \     action.upper = upper;\n                beats.apply(left, right, action);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          naive[index] = std::min(naive[index], upper);\n                }\n\
    \            }\n\n            long long sum = 0;\n            for (long long value\
    \ : naive) sum += value;\n            assert(beats.all_prod().sum == sum);\n \
    \           long long lazy_sum = 0;\n            for (long long value : lazy_naive)\
    \ lazy_sum += value;\n            assert(lazy.all_prod().sum == lazy_sum);\n \
    \       }\n        beats.rollback(beats_state);\n        lazy.rollback(lazy_state);\n\
    \        naive = std::move(saved);\n        lazy_naive = std::move(lazy_saved);\n\
    \        long long sum = 0;\n        for (long long value : naive) sum += value;\n\
    \        assert(beats.all_prod().sum == sum);\n        long long lazy_sum = 0;\n\
    \        for (long long value : lazy_naive) lazy_sum += value;\n        assert(lazy.all_prod().sum\
    \ == lazy_sum);\n        beats.clear_history();\n        lazy.clear_history();\n\
    \    }\n}\n\nvoid test_potentialized_dsu() {\n    m1une::ds::RollbackPotentializedDsu<Add>\
    \ dsu(5);\n    assert(dsu.merge(0, 1, 3));\n    int outer = dsu.snapshot();\n\
    \    assert(dsu.merge(1, 2, 4));\n    assert(dsu.diff(0, 2) == 7);\n    assert(!dsu.merge(0,\
    \ 2, 8));\n    int inner = dsu.snapshot();\n    assert(dsu.merge(3, 4, -2));\n\
    \    dsu.rollback(inner);\n    assert(!dsu.same(3, 4));\n    dsu.rollback(outer);\n\
    \    assert(!dsu.same(0, 2));\n    assert(dsu.diff(0, 1) == 3);\n    assert(dsu.component_count()\
    \ == 4);\n}\n\n}  // namespace\n\nint main() {\n    test_sequence_containers();\n\
    \    test_ordered_containers();\n    test_dynamic_arrays();\n    randomized_lazy_array_test();\n\
    \    test_segment_trees();\n    randomized_segment_tree_test();\n    test_potentialized_dsu();\n\
    \n    long long first, second;\n    std::cin >> first >> second;\n    std::cout\
    \ << first + second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../ds/bst/rollback_ordered_multiset.hpp\"\n#include \"../../ds/bst/rollback_ordered_set.hpp\"\
    \n#include \"../../ds/deque/rollback_deque.hpp\"\n#include \"../../ds/dsu/rollback_potentialized_dsu.hpp\"\
    \n#include \"../../ds/dynamic_array/rollback_dynamic_array.hpp\"\n#include \"\
    ../../ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp\"\n#include \"../../ds/dynamic_array/rollback_dynamic_monoid_array.hpp\"\
    \n#include \"../../ds/queue/rollback_queue.hpp\"\n#include \"../../ds/segtree/rollback_dual_segtree.hpp\"\
    \n#include \"../../ds/segtree/rollback_dynamic_dual_segtree.hpp\"\n#include \"\
    ../../ds/segtree/rollback_dynamic_lazy_segtree.hpp\"\n#include \"../../ds/segtree/rollback_dynamic_segtree.hpp\"\
    \n#include \"../../ds/segtree/rollback_lazy_segtree.hpp\"\n#include \"../../ds/segtree/rollback_segtree.hpp\"\
    \n#include \"../../ds/segtree/rollback_segtree_beats.hpp\"\n#include \"../../ds/stack/rollback_stack.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\n#include \"../../acted_monoid/range_add_range_sum.hpp\"\n\
    #include \"../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp\"\n#include\
    \ \"../../monoid/add.hpp\"\n\nnamespace {\n\nusing Add = m1une::monoid::Add<long\
    \ long>;\nusing RangeAddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;\n\
    \nvoid assert_lazy_array(\n    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum>&\
    \ array,\n    const std::vector<long long>& expected\n) {\n    std::vector<RangeAddSum::value_type>\
    \ values = array.to_vector();\n    assert(values.size() == expected.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        assert(values[index].sum\
    \ == expected[index]);\n        assert(values[index].size == 1);\n    }\n}\n\n\
    void test_sequence_containers() {\n    m1une::ds::RollbackStack<int> stack;\n\
    \    stack.push(1);\n    int outer = stack.snapshot();\n    stack.emplace(2);\n\
    \    int inner = stack.snapshot();\n    stack.push(3);\n    stack.rollback(inner);\n\
    \    assert(stack.top() == 2 && stack.snapshot_count() == inner);\n    stack.pop();\n\
    \    stack.rollback(outer);\n    assert(stack.top() == 1 && stack.snapshot_count()\
    \ == outer);\n    stack.push(4);\n    stack.rollback(outer);\n    assert(stack.top()\
    \ == 1);\n\n    m1une::ds::RollbackQueue<int> queue;\n    queue.push(1);\n   \
    \ outer = queue.snapshot();\n    queue.push_back(2);\n    queue.pop_front();\n\
    \    assert(queue.front() == 2);\n    queue.rollback(outer);\n    assert(queue.front()\
    \ == 1 && queue.back() == 1);\n\n    m1une::ds::RollbackDeque<int> deque;\n  \
    \  deque.push_back(2);\n    outer = deque.snapshot();\n    deque.emplace_front(1);\n\
    \    deque.emplace_back(3);\n    deque.pop_front();\n    assert(deque.front()\
    \ == 2 && deque.back() == 3);\n    deque.rollback(outer);\n    assert(deque.front()\
    \ == 2 && deque.back() == 2);\n}\n\nvoid test_ordered_containers() {\n    m1une::ds::RollbackOrderedSet<int>\
    \ set({2, 1});\n    int outer = set.snapshot();\n    assert(set.insert(3));\n\
    \    assert(!set.insert(3));\n    assert(set.erase(1));\n    int inner = set.snapshot();\n\
    \    set.clear();\n    set.rollback(inner);\n    assert(set.to_vector() == std::vector<int>({2,\
    \ 3}));\n    set.rollback(outer);\n    assert(set.to_vector() == std::vector<int>({1,\
    \ 2}));\n\n    m1une::ds::RollbackOrderedMultiset<int> multiset({2, 2, 3});\n\
    \    outer = multiset.snapshot();\n    assert(multiset.erase_one(2));\n    multiset.insert(1,\
    \ 3);\n    assert(multiset.erase_all(3) == 1);\n    assert(multiset.count(1) ==\
    \ 3 && multiset.count(2) == 1);\n    multiset.rollback(outer);\n    assert(multiset.to_vector()\
    \ == std::vector<int>({2, 2, 3}));\n}\n\nvoid test_dynamic_arrays() {\n    m1une::ds::RollbackDynamicArray<int>\
    \ array(std::vector<int>{1, 2, 3});\n    int outer = array.snapshot();\n    array.insert(1,\
    \ 5);\n    array.reverse(0, 4);\n    array.erase(1, 3);\n    assert(array.to_vector()\
    \ == std::vector<int>({3, 1}));\n    array.rollback(outer);\n    assert(array.to_vector()\
    \ == std::vector<int>({1, 2, 3}));\n\n    m1une::ds::RollbackDynamicMonoidArray<Add>\
    \ monoid_array(\n        std::vector<long long>{1, 2, 3}\n    );\n    outer =\
    \ monoid_array.snapshot();\n    monoid_array.set(1, 7);\n    monoid_array.push_back(4);\n\
    \    assert(monoid_array.all_prod() == 15);\n    monoid_array.rollback(outer);\n\
    \    assert(monoid_array.to_vector() == std::vector<long long>({1, 2, 3}));\n\n\
    \    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> lazy_array(\n    \
    \    std::vector<long long>{1, 2, 3, 4}\n    );\n    outer = lazy_array.snapshot();\n\
    \    lazy_array.apply(0, 3, 4);\n    lazy_array.reverse(1, 4);\n    lazy_array.insert(2,\
    \ RangeAddSum::make(10));\n    lazy_array.erase(0);\n    assert(lazy_array.all_prod().sum\
    \ == 27);\n    int inner = lazy_array.snapshot();\n    lazy_array.clear();\n \
    \   assert(lazy_array.empty());\n    lazy_array.rollback(inner);\n    assert(lazy_array.all_prod().sum\
    \ == 27);\n    lazy_array.rollback(outer);\n    std::vector<RangeAddSum::value_type>\
    \ restored = lazy_array.to_vector();\n    assert(restored.size() == 4);\n    for\
    \ (int index = 0; index < 4; ++index) {\n        assert(restored[index].sum ==\
    \ index + 1);\n        assert(restored[index].size == 1);\n    }\n}\n\nvoid randomized_lazy_array_test()\
    \ {\n    std::mt19937 random(0);\n    std::vector<long long> naive = {0, 1, 2,\
    \ 3, 4, 5};\n    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> array(naive);\n\
    \    for (int round = 0; round < 80; ++round) {\n        int state = array.snapshot();\n\
    \        std::vector<long long> saved = naive;\n        for (int step = 0; step\
    \ < 35; ++step) {\n            int type = int(random() % 5);\n            if (type\
    \ == 0 && !naive.empty()) {\n                int pos = int(random() % naive.size());\n\
    \                long long value = int(random() % 31) - 15;\n                array.set(pos,\
    \ RangeAddSum::make(value));\n                naive[pos] = value;\n          \
    \  } else if (type == 1) {\n                int left = int(random() % (naive.size()\
    \ + 1));\n                int right = left + int(random() % (naive.size() - left\
    \ + 1));\n                long long add = int(random() % 11) - 5;\n          \
    \      array.apply(left, right, add);\n                for (int index = left;\
    \ index < right; ++index) naive[index] += add;\n            } else if (type ==\
    \ 2) {\n                int left = int(random() % (naive.size() + 1));\n     \
    \           int right = left + int(random() % (naive.size() - left + 1));\n  \
    \              array.reverse(left, right);\n                std::reverse(naive.begin()\
    \ + left, naive.begin() + right);\n            } else if (type == 3) {\n     \
    \           int pos = int(random() % (naive.size() + 1));\n                std::vector<long\
    \ long> raw_values = {\n                    int(random() % 21) - 10,\n       \
    \             int(random() % 21) - 10\n                };\n                std::vector<RangeAddSum::value_type>\
    \ values;\n                for (long long value : raw_values) {\n            \
    \        values.push_back(RangeAddSum::make(value));\n                }\n    \
    \            array.insert(pos, std::move(values));\n                naive.insert(\n\
    \                    naive.begin() + pos, raw_values.begin(), raw_values.end()\n\
    \                );\n            } else if (!naive.empty()) {\n              \
    \  int pos = int(random() % naive.size());\n                array.erase(pos);\n\
    \                naive.erase(naive.begin() + pos);\n            }\n          \
    \  assert_lazy_array(array, naive);\n        }\n        array.rollback(state);\n\
    \        naive = std::move(saved);\n        assert_lazy_array(array, naive);\n\
    \        array.clear_history();\n    }\n}\n\nvoid test_segment_trees() {\n   \
    \ m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});\n \
    \   int outer = seg.snapshot();\n    seg.set(1, 10);\n    seg.set(1, 12);\n  \
    \  assert(seg.all_prod() == 20);\n    int inner = seg.snapshot();\n    seg.set(0,\
    \ 8);\n    seg.rollback(inner);\n    assert(seg.all_prod() == 20);\n    seg.rollback(outer);\n\
    \    assert(seg.all_prod() == 10);\n\n    m1une::ds::RollbackLazySegtree<RangeAddSum>\
    \ lazy(\n        std::vector<long long>{1, 2, 3, 4}\n    );\n    outer = lazy.snapshot();\n\
    \    lazy.apply(1, 4, 5);\n    lazy.set(0, RangeAddSum::make(9));\n    assert(lazy.all_prod().sum\
    \ == 33);\n    assert(lazy.prod(1, 3).sum == 15);\n    lazy.rollback(outer);\n\
    \    assert(lazy.all_prod().sum == 10);\n\n    m1une::ds::RollbackDualSegtree<Add>\
    \ dual(4);\n    outer = dual.snapshot();\n    dual.apply(0, 3, 4);\n    dual.set(1,\
    \ 2);\n    assert(dual.get(0) == 4 && dual.get(1) == 2);\n    dual.rollback(outer);\n\
    \    assert(dual.get(0) == 0 && dual.get(1) == 0);\n\n    m1une::ds::RollbackDynamicSegtree<Add>\
    \ dynamic(-10, 10);\n    outer = dynamic.snapshot();\n    dynamic.set(-4, 7);\n\
    \    dynamic.set(8, 3);\n    assert(dynamic.all_prod() == 10);\n    dynamic.rollback(outer);\n\
    \    assert(dynamic.all_prod() == 0 && dynamic.node_count() == 0);\n\n    m1une::ds::RollbackDynamicLazySegtree<RangeAddSum>\
    \ dynamic_lazy(\n        -10, 10, RangeAddSum::id()\n    );\n    outer = dynamic_lazy.snapshot();\n\
    \    dynamic_lazy.set(-2, RangeAddSum::make(3));\n    dynamic_lazy.apply(-3, 2,\
    \ 4);\n    assert(dynamic_lazy.get(-2).sum == 7);\n    assert(dynamic_lazy.prod(-3,\
    \ 2).sum == 7);\n    dynamic_lazy.rollback(outer);\n    assert(dynamic_lazy.get(-2).sum\
    \ == 0 && dynamic_lazy.node_count() == 0);\n\n    m1une::ds::RollbackDynamicDualSegtree<Add>\
    \ dynamic_dual(-10, 10, 0);\n    outer = dynamic_dual.snapshot();\n    dynamic_dual.apply(-3,\
    \ 5, 7);\n    dynamic_dual.set(0, 2);\n    assert(dynamic_dual.get(-1) == 7 &&\
    \ dynamic_dual.get(0) == 2);\n    dynamic_dual.rollback(outer);\n    assert(dynamic_dual.get(-1)\
    \ == 0 && dynamic_dual.get(0) == 0);\n\n    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n    m1une::ds::RollbackSegtreeBeats<Beats> beats(\n        std::vector<long\
    \ long>{1, 5, 3, 7}\n    );\n    outer = beats.snapshot();\n    Beats::operator_type\
    \ chmin;\n    chmin.add = 0;\n    chmin.lower = Beats::negative_infinity;\n  \
    \  chmin.upper = 4;\n    beats.apply(0, 4, chmin);\n    assert(beats.all_prod().sum\
    \ == 12);\n    assert(beats.prod(1, 4).sum == 11);\n    beats.rollback(outer);\n\
    \    assert(beats.all_prod().sum == 16);\n}\n\nvoid randomized_segment_tree_test()\
    \ {\n    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long\
    \ long>;\n    std::mt19937 random(1);\n    constexpr int size = 24;\n    std::vector<long\
    \ long> naive(size);\n    std::vector<long long> lazy_naive(size);\n    m1une::ds::RollbackLazySegtree<RangeAddSum>\
    \ lazy(lazy_naive);\n    m1une::ds::RollbackSegtreeBeats<Beats> beats(naive);\n\
    \n    for (int round = 0; round < 70; ++round) {\n        int lazy_state = lazy.snapshot();\n\
    \        int beats_state = beats.snapshot();\n        std::vector<long long> saved\
    \ = naive;\n        std::vector<long long> lazy_saved = lazy_naive;\n        for\
    \ (int step = 0; step < 45; ++step) {\n            int type = int(random() % 3);\n\
    \            int left = int(random() % size);\n            int right = left +\
    \ 1 + int(random() % (size - left));\n            if (type == 0) {\n         \
    \       long long add = int(random() % 17) - 8;\n                lazy.apply(left,\
    \ right, add);\n                Beats::operator_type action;\n               \
    \ action.add = add;\n                action.lower = Beats::negative_infinity;\n\
    \                action.upper = Beats::positive_infinity;\n                beats.apply(left,\
    \ right, action);\n                for (int index = left; index < right; ++index)\
    \ naive[index] += add;\n                for (int index = left; index < right;\
    \ ++index) lazy_naive[index] += add;\n            } else if (type == 1) {\n  \
    \              long long value = int(random() % 41) - 20;\n                lazy.set(left,\
    \ RangeAddSum::make(value));\n                beats.set(left, Beats::make(value));\n\
    \                naive[left] = value;\n                lazy_naive[left] = value;\n\
    \            } else {\n                long long upper = int(random() % 31) -\
    \ 15;\n                Beats::operator_type action;\n                action.add\
    \ = 0;\n                action.lower = Beats::negative_infinity;\n           \
    \     action.upper = upper;\n                beats.apply(left, right, action);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          naive[index] = std::min(naive[index], upper);\n                }\n\
    \            }\n\n            long long sum = 0;\n            for (long long value\
    \ : naive) sum += value;\n            assert(beats.all_prod().sum == sum);\n \
    \           long long lazy_sum = 0;\n            for (long long value : lazy_naive)\
    \ lazy_sum += value;\n            assert(lazy.all_prod().sum == lazy_sum);\n \
    \       }\n        beats.rollback(beats_state);\n        lazy.rollback(lazy_state);\n\
    \        naive = std::move(saved);\n        lazy_naive = std::move(lazy_saved);\n\
    \        long long sum = 0;\n        for (long long value : naive) sum += value;\n\
    \        assert(beats.all_prod().sum == sum);\n        long long lazy_sum = 0;\n\
    \        for (long long value : lazy_naive) lazy_sum += value;\n        assert(lazy.all_prod().sum\
    \ == lazy_sum);\n        beats.clear_history();\n        lazy.clear_history();\n\
    \    }\n}\n\nvoid test_potentialized_dsu() {\n    m1une::ds::RollbackPotentializedDsu<Add>\
    \ dsu(5);\n    assert(dsu.merge(0, 1, 3));\n    int outer = dsu.snapshot();\n\
    \    assert(dsu.merge(1, 2, 4));\n    assert(dsu.diff(0, 2) == 7);\n    assert(!dsu.merge(0,\
    \ 2, 8));\n    int inner = dsu.snapshot();\n    assert(dsu.merge(3, 4, -2));\n\
    \    dsu.rollback(inner);\n    assert(!dsu.same(3, 4));\n    dsu.rollback(outer);\n\
    \    assert(!dsu.same(0, 2));\n    assert(dsu.diff(0, 1) == 3);\n    assert(dsu.component_count()\
    \ == 4);\n}\n\n}  // namespace\n\nint main() {\n    test_sequence_containers();\n\
    \    test_ordered_containers();\n    test_dynamic_arrays();\n    randomized_lazy_array_test();\n\
    \    test_segment_trees();\n    randomized_segment_tree_test();\n    test_potentialized_dsu();\n\
    \n    long long first, second;\n    std::cin >> first >> second;\n    std::cout\
    \ << first + second << '\\n';\n}\n"
  dependsOn:
  - ds/bst/rollback_ordered_multiset.hpp
  - ds/bst/ordered_multiset.hpp
  - ds/bst/rollback_ordered_set.hpp
  - ds/bst/ordered_set.hpp
  - ds/deque/rollback_deque.hpp
  - ds/dsu/rollback_potentialized_dsu.hpp
  - monoid/concept.hpp
  - ds/dynamic_array/rollback_dynamic_array.hpp
  - ds/dynamic_array/dynamic_array.hpp
  - ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp
  - acted_monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  - ds/dynamic_array/rollback_dynamic_monoid_array.hpp
  - ds/dynamic_array/dynamic_monoid_array.hpp
  - monoid/concept.hpp
  - ds/queue/rollback_queue.hpp
  - ds/segtree/rollback_dual_segtree.hpp
  - monoid/concept.hpp
  - ds/detail/rollback_journal.hpp
  - ds/segtree/rollback_dynamic_dual_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - ds/segtree/rollback_dynamic_lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - ds/segtree/rollback_dynamic_segtree.hpp
  - ds/segtree/rollback_lazy_segtree.hpp
  - math/bit_ceil.hpp
  - ds/segtree/rollback_segtree.hpp
  - ds/segtree/rollback_segtree_beats.hpp
  - beats_acted_monoid/concept.hpp
  - acted_monoid/concept.hpp
  - ds/stack/rollback_stack.hpp
  - acted_monoid/range_add_range_sum.hpp
  - beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp
  - monoid/add.hpp
  isVerificationFile: true
  path: verify/ds/rollback_counterparts.test.cpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/rollback_counterparts.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/rollback_counterparts.test.cpp
- /verify/verify/ds/rollback_counterparts.test.cpp.html
title: verify/ds/rollback_counterparts.test.cpp
---
