---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_multiset.hpp
    title: Ordered Multiset
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/rollback_counterparts.test.cpp
    title: verify/ds/rollback_counterparts.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/rollback_ordered_multiset.hpp\"\n\n\n\n#include <cassert>\n\
    #include <functional>\n#include <initializer_list>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"ds/bst/ordered_multiset.hpp\"\n\n\n\
    \n#line 7 \"ds/bst/ordered_multiset.hpp\"\n#include <memory>\n#line 10 \"ds/bst/ordered_multiset.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T, typename Compare\
    \ = std::less<T>>\nstruct OrderedMultiset {\n   private:\n    struct Node {\n\
    \        T key;\n        int count;\n        int size;\n        int distinct_size;\n\
    \        Node* l;\n        Node* r;\n\n        Node(T value, int multiplicity)\n\
    \            : key(std::move(value)),\n              count(multiplicity),\n  \
    \            size(multiplicity),\n              distinct_size(1),\n          \
    \    l(nullptr),\n              r(nullptr) {}\n    };\n\n    static constexpr\
    \ int pool_block_size = 1 << 14;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP\n#define M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP\
    \ 1\n\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\n#include \"ordered_multiset.hpp\"\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_BST_ROLLBACK_ORDERED_MULTISET_HPP\n"
  dependsOn:
  - ds/bst/ordered_multiset.hpp
  isVerificationFile: false
  path: ds/bst/rollback_ordered_multiset.hpp
  requiredBy: []
  timestamp: '2026-08-12 17:21:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/rollback_counterparts.test.cpp
documentation_of: ds/bst/rollback_ordered_multiset.hpp
layout: document
title: Rollback Ordered Multiset
---

## Overview

`RollbackOrderedMultiset<T, Compare>` is an ordered multiset with order
statistics and registered-snapshot rollback. It shares nodes between saved states.
`Compare` must define a strict weak ordering.

## Methods

Constructors and read-only methods follow `OrderedMultiset<T, Compare>`.

| Method | Description | Complexity |
| --- | --- | --- |
| `void clear()` | Clears the multiset. | $O(N)$ |
| `void insert(T key, int multiplicity = 1)`, `void insert_inplace(T key, int multiplicity = 1)` | Inserts positive multiplicity. | $O(\log N)$ |
| `bool erase_one(const T& key)`, `bool erase(const T& key)` | Erases one copy, reports whether one existed,. | $O(\log N)$ |
| `bool erase_one_inplace(const T& key)`, `bool erase_inplace(const T& key)` | Aliases of `erase_one`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Erases every copy and returns the erased multiplicity. | $O(\log N)$ |
| `bool erase_all_inplace(const T& key)` | Erases every copy and reports whether the key existed. | $O(\log N)$ |
| `void merge(const RollbackOrderedMultiset& other)` | Inserts an ordered multiset of size $M$. | $O(M \log(N+M))$ |
| `int snapshot()` | Registers the current state and returns its token. | $O(1)$ |
| `int snapshot_count() const` | Returns the number of active snapshots. | $O(1)$ |
| `void reserve_snapshots(int count)` | Reserves snapshot tokens. | $O(H)$ |
| `void rollback(int state)` | Rolls back to a current-path snapshot. | $O(F)$ total |
| `void clear_history()`, `void release()` | Releases saved states, or all states. | $O(F)$ |


## Snapshot semantics

Updates made before the first `snapshot()` retain no rollback data. A snapshot token is positive and valid only on the current path. `rollback(state)` restores that registered state, keeps it active, and invalidates newer snapshots. `clear_history()` commits the current state and invalidates every token. No per-update reversal operation is provided.

## Example

```cpp
#include "ds/bst/rollback_ordered_multiset.hpp"

m1une::ds::RollbackOrderedMultiset<int> values;
values.insert(3, 2);
int state = values.snapshot();
values.erase_one(3);
values.rollback(state);
assert(values.count(3) == 2);
```
