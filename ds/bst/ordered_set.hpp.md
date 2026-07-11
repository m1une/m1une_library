---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_multiset.hpp
    title: Ordered Multiset
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/ordered_set.test.cpp
    title: verify/ds/bst/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/ordered_set.hpp\"\n\n\n\n#line 1 \"ds/bst/ordered_multiset.hpp\"\
    \n\n\n\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n#include <functional>\n\
    #include <initializer_list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename T, typename Compare>\n\
    struct OrderedSet;\n\ntemplate <typename T, typename Compare = std::less<T>>\n\
    struct OrderedMultiset {\n   private:\n    friend struct OrderedSet<T, Compare>;\n\
    \    struct Node {\n        T key;\n        int priority;\n        int count;\n\
    \        int size;\n        int distinct_size;\n        Node* l;\n        Node*\
    \ r;\n\n        Node(T value, int node_priority, int multiplicity)\n         \
    \   : key(std::move(value)),\n              priority(node_priority),\n       \
    \       count(multiplicity),\n              size(multiplicity),\n            \
    \  distinct_size(1),\n              l(nullptr),\n              r(nullptr) {}\n\
    \    };\n\n    static constexpr int pool_block_bits = 14;\n    static constexpr\
    \ int pool_block_size = 1 << pool_block_bits;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
    \ blocks;\n\n        template <class... Args>\n        Node* emplace(Args&&...\
    \ args) {\n            if (blocks.empty() || int(blocks.back().size()) == pool_block_size)\
    \ {\n                blocks.emplace_back();\n                blocks.back().reserve(pool_block_size);\n\
    \            }\n            blocks.back().emplace_back(std::forward<Args>(args)...);\n\
    \            return &blocks.back().back();\n        }\n    };\n\n    struct Ownership\
    \ {\n        std::shared_ptr<Pool> pool;\n        std::shared_ptr<Ownership> l;\n\
    \        std::shared_ptr<Ownership> r;\n\n        explicit Ownership(std::shared_ptr<Pool>\
    \ node_pool) : pool(std::move(node_pool)) {}\n        Ownership(std::shared_ptr<Ownership>\
    \ left, std::shared_ptr<Ownership> right)\n            : l(std::move(left)), r(std::move(right))\
    \ {}\n    };\n\n    std::shared_ptr<Pool> allocation_pool;\n    std::shared_ptr<Ownership>\
    \ ownership;\n    Node* root;\n    std::uint32_t rng_state;\n    Compare comp;\n\
    \n    static int subtree_size(const Node* t) {\n        return t == nullptr ?\
    \ 0 : t->size;\n    }\n\n    static int subtree_distinct_size(const Node* t) {\n\
    \        return t == nullptr ? 0 : t->distinct_size;\n    }\n\n    bool equal(const\
    \ T& a, const T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\
    \n    int next_priority() {\n        rng_state ^= rng_state << 13;\n        rng_state\
    \ ^= rng_state >> 17;\n        rng_state ^= rng_state << 5;\n        if (rng_state\
    \ == 0) rng_state = 1;\n        return int(rng_state);\n    }\n\n    Node* new_node(T\
    \ key, int multiplicity) {\n        return allocation_pool->emplace(std::move(key),\
    \ next_priority(), multiplicity);\n    }\n\n    static void update(Node* t) {\n\
    \        if (t == nullptr) return;\n        t->size = t->count + subtree_size(t->l)\
    \ + subtree_size(t->r);\n        t->distinct_size = 1 + subtree_distinct_size(t->l)\
    \ + subtree_distinct_size(t->r);\n    }\n\n    static Node* merge_nodes(Node*\
    \ l, Node* r) {\n        if (l == nullptr || r == nullptr) return l == nullptr\
    \ ? r : l;\n        if (l->priority > r->priority) {\n            l->r = merge_nodes(l->r,\
    \ r);\n            update(l);\n            return l;\n        }\n        r->l\
    \ = merge_nodes(l, r->l);\n        update(r);\n        return r;\n    }\n\n  \
    \  std::pair<Node*, Node*> split_nodes(Node* t, const T& key) {\n        if (t\
    \ == nullptr) return {nullptr, nullptr};\n        if (comp(t->key, key)) {\n \
    \           auto [l, r] = split_nodes(t->r, key);\n            t->r = l;\n   \
    \         update(t);\n            return {t, r};\n        }\n        auto [l,\
    \ r] = split_nodes(t->l, key);\n        t->l = r;\n        update(t);\n      \
    \  return {l, t};\n    }\n\n    void rotate_right(Node*& t) {\n        Node* s\
    \ = t->l;\n        t->l = s->r;\n        s->r = t;\n        update(t);\n     \
    \   update(s);\n        t = s;\n    }\n\n    void rotate_left(Node*& t) {\n  \
    \      Node* s = t->r;\n        t->r = s->l;\n        s->l = t;\n        update(t);\n\
    \        update(s);\n        t = s;\n    }\n\n    Node* insert_impl(Node* t, T&\
    \ key, int multiplicity) {\n        if (t == nullptr) return new_node(std::move(key),\
    \ multiplicity);\n        if (equal(key, t->key)) {\n            t->count += multiplicity;\n\
    \            update(t);\n            return t;\n        }\n        if (comp(key,\
    \ t->key)) {\n            t->l = insert_impl(t->l, key, multiplicity);\n     \
    \       if (t->l->priority > t->priority) rotate_right(t);\n        } else {\n\
    \            t->r = insert_impl(t->r, key, multiplicity);\n            if (t->r->priority\
    \ > t->priority) rotate_left(t);\n        }\n        update(t);\n        return\
    \ t;\n    }\n\n    Node* insert_unique_impl(Node* t, T& key, bool& inserted) {\n\
    \        if (t == nullptr) {\n            inserted = true;\n            return\
    \ new_node(std::move(key), 1);\n        }\n        if (equal(key, t->key)) return\
    \ t;\n        if (comp(key, t->key)) {\n            t->l = insert_unique_impl(t->l,\
    \ key, inserted);\n            if (!inserted) return t;\n            if (t->l->priority\
    \ > t->priority) rotate_right(t);\n        } else {\n            t->r = insert_unique_impl(t->r,\
    \ key, inserted);\n            if (!inserted) return t;\n            if (t->r->priority\
    \ > t->priority) rotate_left(t);\n        }\n        update(t);\n        return\
    \ t;\n    }\n\n    bool erase_one_impl(Node*& t, const T& key) {\n        if (t\
    \ == nullptr) return false;\n        bool erased;\n        if (equal(key, t->key))\
    \ {\n            if (t->count > 1) {\n                --t->count;\n          \
    \      erased = true;\n            } else {\n                t = merge_nodes(t->l,\
    \ t->r);\n                return true;\n            }\n        } else if (comp(key,\
    \ t->key)) {\n            erased = erase_one_impl(t->l, key);\n        } else\
    \ {\n            erased = erase_one_impl(t->r, key);\n        }\n        if (!erased)\
    \ return false;\n        update(t);\n        return true;\n    }\n\n    int erase_all_impl(Node*&\
    \ t, const T& key) {\n        if (t == nullptr) return 0;\n        int erased;\n\
    \        if (equal(key, t->key)) {\n            erased = t->count;\n         \
    \   t = merge_nodes(t->l, t->r);\n            return erased;\n        }\n    \
    \    if (comp(key, t->key)) {\n            erased = erase_all_impl(t->l, key);\n\
    \        } else {\n            erased = erase_all_impl(t->r, key);\n        }\n\
    \        if (erased == 0) return 0;\n        update(t);\n        return erased;\n\
    \    }\n\n    static const T* kth_impl(const Node* t, int k) {\n        while\
    \ (t != nullptr) {\n            int left_size = subtree_size(t->l);\n        \
    \    if (k < left_size) {\n                t = t->l;\n            } else if (k\
    \ < left_size + t->count) {\n                return &t->key;\n            } else\
    \ {\n                k -= left_size + t->count;\n                t = t->r;\n \
    \           }\n        }\n        return nullptr;\n    }\n\n    int count_impl(const\
    \ Node* t, const T& key) const {\n        while (t != nullptr) {\n           \
    \ if (equal(key, t->key)) return t->count;\n            t = comp(key, t->key)\
    \ ? t->l : t->r;\n        }\n        return 0;\n    }\n\n    int order_of_key_impl(const\
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
    \    Node* clone_impl(const Node* t) {\n        if (t == nullptr) return nullptr;\n\
    \        Node* result = allocation_pool->emplace(t->key, t->priority, t->count);\n\
    \        result->l = clone_impl(t->l);\n        result->r = clone_impl(t->r);\n\
    \        update(result);\n        return result;\n    }\n\n    OrderedMultiset(Node*\
    \ node, std::uint32_t state, Compare compare,\n                    std::shared_ptr<Pool>\
    \ node_pool, std::shared_ptr<Ownership> node_ownership)\n        : allocation_pool(std::move(node_pool)),\n\
    \          ownership(std::move(node_ownership)),\n          root(node),\n    \
    \      rng_state(state),\n          comp(std::move(compare)) {}\n\n   public:\n\
    \    explicit OrderedMultiset(Compare compare)\n        : allocation_pool(std::make_shared<Pool>()),\n\
    \          ownership(std::make_shared<Ownership>(allocation_pool)),\n        \
    \  root(nullptr),\n          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),\n\
    \          comp(std::move(compare)) {\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    OrderedMultiset() : OrderedMultiset(Compare()) {}\n\n    OrderedMultiset(std::initializer_list<T>\
    \ init, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {\n\
    \        for (const T& x : init) insert(x);\n    }\n\n    template <typename Iterator>\n\
    \    OrderedMultiset(Iterator first, Iterator last, Compare compare = Compare())\
    \ : OrderedMultiset(std::move(compare)) {\n        while (first != last) insert(*first++);\n\
    \    }\n\n    OrderedMultiset(const OrderedMultiset& other)\n        : allocation_pool(std::make_shared<Pool>()),\n\
    \          ownership(std::make_shared<Ownership>(allocation_pool)),\n        \
    \  root(nullptr),\n          rng_state(other.rng_state),\n          comp(other.comp)\
    \ {\n        root = clone_impl(other.root);\n    }\n\n    OrderedMultiset(OrderedMultiset&&)\
    \ noexcept = default;\n\n    OrderedMultiset& operator=(OrderedMultiset other)\
    \ {\n        swap(other);\n        return *this;\n    }\n\n    void swap(OrderedMultiset&\
    \ other) noexcept {\n        using std::swap;\n        swap(allocation_pool, other.allocation_pool);\n\
    \        swap(ownership, other.ownership);\n        swap(root, other.root);\n\
    \        swap(rng_state, other.rng_state);\n        swap(comp, other.comp);\n\
    \    }\n\n    int size() const { return subtree_size(root); }\n    int unique_size()\
    \ const { return subtree_distinct_size(root); }\n    bool empty() const { return\
    \ root == nullptr; }\n\n    void clear() {\n        allocation_pool = std::make_shared<Pool>();\n\
    \        ownership = std::make_shared<Ownership>(allocation_pool);\n        root\
    \ = nullptr;\n    }\n\n    void insert(T key, int multiplicity = 1) {\n      \
    \  assert(multiplicity > 0);\n        root = insert_impl(root, key, multiplicity);\n\
    \    }\n\n   private:\n    bool insert_unique(T key) {\n        bool inserted\
    \ = false;\n        root = insert_unique_impl(root, key, inserted);\n        return\
    \ inserted;\n    }\n\n   public:\n    bool erase_one(const T& key) { return erase_one_impl(root,\
    \ key); }\n    bool erase(const T& key) { return erase_one(key); }\n    int erase_all(const\
    \ T& key) { return erase_all_impl(root, key); }\n    bool contains(const T& key)\
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
    \ return empty() ? nullptr : kth_impl(root, size() - 1); }\n\n    std::pair<OrderedMultiset,\
    \ OrderedMultiset> split(const T& key) && {\n        auto [l, r] = split_nodes(root,\
    \ key);\n        root = nullptr;\n        return {OrderedMultiset(l, rng_state,\
    \ comp, allocation_pool, ownership),\n                OrderedMultiset(r, rng_state,\
    \ std::move(comp),\n                                std::move(allocation_pool),\
    \ std::move(ownership))};\n    }\n\n    OrderedMultiset merge(OrderedMultiset\
    \ other) && {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        root = merge_nodes(root, other.root);\n        other.root = nullptr;\n\
    \        if (ownership != other.ownership) {\n            ownership = std::make_shared<Ownership>(std::move(ownership),\n\
    \                                                    std::move(other.ownership));\n\
    \        }\n        return std::move(*this);\n    }\n\n    std::vector<T> to_vector()\
    \ const {\n        std::vector<T> result;\n        result.reserve(size());\n \
    \       dump_impl(root, result);\n        return result;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 5 \"ds/bst/ordered_set.hpp\"\n\n#line 10\
    \ \"ds/bst/ordered_set.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\ntemplate\
    \ <typename T, typename Compare = std::less<T>>\nstruct OrderedSet {\n   private:\n\
    \    OrderedMultiset<T, Compare> data;\n\n    explicit OrderedSet(OrderedMultiset<T,\
    \ Compare> multiset) : data(std::move(multiset)) {}\n\n   public:\n    explicit\
    \ OrderedSet(Compare compare) : data(std::move(compare)) {}\n\n    OrderedSet()\
    \ : OrderedSet(Compare()) {}\n\n    OrderedSet(std::initializer_list<T> init,\
    \ Compare compare = Compare()) : OrderedSet(std::move(compare)) {\n        for\
    \ (const T& x : init) insert(x);\n    }\n\n    template <typename Iterator>\n\
    \    OrderedSet(Iterator first, Iterator last, Compare compare = Compare()) :\
    \ OrderedSet(std::move(compare)) {\n        while (first != last) {\n        \
    \    insert(*first);\n            ++first;\n        }\n    }\n\n    int size()\
    \ const {\n        return data.size();\n    }\n\n    int unique_size() const {\n\
    \        return data.size();\n    }\n\n    bool empty() const {\n        return\
    \ data.empty();\n    }\n\n    void clear() {\n        data.clear();\n    }\n\n\
    \    bool insert(T key) {\n        return data.insert_unique(std::move(key));\n\
    \    }\n\n    bool erase(const T& key) {\n        return data.erase(key);\n  \
    \  }\n\n    bool contains(const T& key) const {\n        return data.contains(key);\n\
    \    }\n\n    int count(const T& key) const {\n        return contains(key) ?\
    \ 1 : 0;\n    }\n\n    const T* find_by_order(int k) const {\n        return data.find_by_order(k);\n\
    \    }\n\n    T kth(int k) const {\n        return data.kth(k);\n    }\n\n   \
    \ int order_of_key(const T& key) const {\n        return data.order_of_key(key);\n\
    \    }\n\n    int count_less(const T& key) const {\n        return data.count_less(key);\n\
    \    }\n\n    int count_less_equal(const T& key) const {\n        return data.count_less_equal(key);\n\
    \    }\n\n    int count_greater(const T& key) const {\n        return data.count_greater(key);\n\
    \    }\n\n    int count_greater_equal(const T& key) const {\n        return data.count_greater_equal(key);\n\
    \    }\n\n    const T* lower_bound(const T& key) const {\n        return data.lower_bound(key);\n\
    \    }\n\n    const T* upper_bound(const T& key) const {\n        return data.upper_bound(key);\n\
    \    }\n\n    const T* min_ge(const T& key) const {\n        return data.min_ge(key);\n\
    \    }\n\n    const T* min_gt(const T& key) const {\n        return data.min_gt(key);\n\
    \    }\n\n    const T* max_le(const T& key) const {\n        return data.max_le(key);\n\
    \    }\n\n    const T* max_lt(const T& key) const {\n        return data.max_lt(key);\n\
    \    }\n\n    const T* min() const {\n        return data.min();\n    }\n\n  \
    \  const T* max() const {\n        return data.max();\n    }\n\n    std::pair<OrderedSet,\
    \ OrderedSet> split(const T& key) && {\n        auto [l, r] = std::move(data).split(key);\n\
    \        return {OrderedSet(std::move(l)), OrderedSet(std::move(r))};\n    }\n\
    \n    OrderedSet merge(OrderedSet other) && {\n        return OrderedSet(std::move(data).merge(std::move(other.data)));\n\
    \    }\n\n    std::vector<T> to_vector() const {\n        return data.to_vector();\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ORDERED_SET_HPP\n#define M1UNE_ORDERED_SET_HPP 1\n\n#include\
    \ \"ordered_multiset.hpp\"\n\n#include <functional>\n#include <initializer_list>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <typename T, typename Compare = std::less<T>>\nstruct OrderedSet {\n\
    \   private:\n    OrderedMultiset<T, Compare> data;\n\n    explicit OrderedSet(OrderedMultiset<T,\
    \ Compare> multiset) : data(std::move(multiset)) {}\n\n   public:\n    explicit\
    \ OrderedSet(Compare compare) : data(std::move(compare)) {}\n\n    OrderedSet()\
    \ : OrderedSet(Compare()) {}\n\n    OrderedSet(std::initializer_list<T> init,\
    \ Compare compare = Compare()) : OrderedSet(std::move(compare)) {\n        for\
    \ (const T& x : init) insert(x);\n    }\n\n    template <typename Iterator>\n\
    \    OrderedSet(Iterator first, Iterator last, Compare compare = Compare()) :\
    \ OrderedSet(std::move(compare)) {\n        while (first != last) {\n        \
    \    insert(*first);\n            ++first;\n        }\n    }\n\n    int size()\
    \ const {\n        return data.size();\n    }\n\n    int unique_size() const {\n\
    \        return data.size();\n    }\n\n    bool empty() const {\n        return\
    \ data.empty();\n    }\n\n    void clear() {\n        data.clear();\n    }\n\n\
    \    bool insert(T key) {\n        return data.insert_unique(std::move(key));\n\
    \    }\n\n    bool erase(const T& key) {\n        return data.erase(key);\n  \
    \  }\n\n    bool contains(const T& key) const {\n        return data.contains(key);\n\
    \    }\n\n    int count(const T& key) const {\n        return contains(key) ?\
    \ 1 : 0;\n    }\n\n    const T* find_by_order(int k) const {\n        return data.find_by_order(k);\n\
    \    }\n\n    T kth(int k) const {\n        return data.kth(k);\n    }\n\n   \
    \ int order_of_key(const T& key) const {\n        return data.order_of_key(key);\n\
    \    }\n\n    int count_less(const T& key) const {\n        return data.count_less(key);\n\
    \    }\n\n    int count_less_equal(const T& key) const {\n        return data.count_less_equal(key);\n\
    \    }\n\n    int count_greater(const T& key) const {\n        return data.count_greater(key);\n\
    \    }\n\n    int count_greater_equal(const T& key) const {\n        return data.count_greater_equal(key);\n\
    \    }\n\n    const T* lower_bound(const T& key) const {\n        return data.lower_bound(key);\n\
    \    }\n\n    const T* upper_bound(const T& key) const {\n        return data.upper_bound(key);\n\
    \    }\n\n    const T* min_ge(const T& key) const {\n        return data.min_ge(key);\n\
    \    }\n\n    const T* min_gt(const T& key) const {\n        return data.min_gt(key);\n\
    \    }\n\n    const T* max_le(const T& key) const {\n        return data.max_le(key);\n\
    \    }\n\n    const T* max_lt(const T& key) const {\n        return data.max_lt(key);\n\
    \    }\n\n    const T* min() const {\n        return data.min();\n    }\n\n  \
    \  const T* max() const {\n        return data.max();\n    }\n\n    std::pair<OrderedSet,\
    \ OrderedSet> split(const T& key) && {\n        auto [l, r] = std::move(data).split(key);\n\
    \        return {OrderedSet(std::move(l)), OrderedSet(std::move(r))};\n    }\n\
    \n    OrderedSet merge(OrderedSet other) && {\n        return OrderedSet(std::move(data).merge(std::move(other.data)));\n\
    \    }\n\n    std::vector<T> to_vector() const {\n        return data.to_vector();\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_ORDERED_SET_HPP\n"
  dependsOn:
  - ds/bst/ordered_multiset.hpp
  isVerificationFile: false
  path: ds/bst/ordered_set.hpp
  requiredBy: []
  timestamp: '2026-07-12 04:52:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/ordered_set.test.cpp
documentation_of: ds/bst/ordered_set.hpp
layout: document
title: Ordered Set
---

## Overview

`OrderedSet` is a randomized binary search tree for sets. It keeps unique keys only, like `std::set`, and also supports order-statistics queries such as k-th element and rank.

`split(key)` consumes a tree and partitions it into keys `< key` and keys
`>= key`. `merge(other)` consumes two trees whose key ranges are strictly
ordered.

Pointers returned by bound and predecessor/successor methods remain valid until the set is modified.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

Trees passed to `merge` must use equivalent comparator state.

## Constructors

* `OrderedSet()`
  Constructs an empty set. ($O(1)$)

* `OrderedSet(Compare compare)`
  Constructs an empty set with a custom comparator. ($O(1)$)

* `OrderedSet(std::initializer_list<T> init)`
  Constructs a set from an initializer list. Duplicate keys are ignored. ($O(N \log N)$)

* `OrderedSet(Iterator first, Iterator last)`
  Constructs a set from a range. Duplicate keys are ignored. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of keys. | $O(1)$ |
| `int unique_size() const` | Alias for `size()`. | $O(1)$ |
| `bool empty() const` | Returns whether the set is empty. | $O(1)$ |
| `void clear()` | Removes all keys. | $O(1)$ |
| `bool insert(T key)` | Inserts `key`; returns whether a new key was inserted. | $O(\log N)$ |
| `bool erase(const T& key)` | Removes `key`; returns whether a key was removed. | $O(\log N)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | $O(\log N)$ |
| `int count(const T& key) const` | Returns `1` if `key` exists, otherwise `0`. | $O(\log N)$ |
| `const T* find_by_order(int k) const` | Returns a pointer to the 0-indexed `k`-th smallest key. Requires `0 <= k < size()`. | $O(\log N)$ |
| `T kth(int k) const` | Returns the 0-indexed `k`-th smallest key by value. Requires `0 <= k < size()`. | $O(\log N)$ |
| `int order_of_key(const T& key) const` | Returns the number of keys strictly less than `key`. | $O(\log N)$ |
| `int count_less(const T& key) const` | Alias for `order_of_key(key)`. | $O(\log N)$ |
| `int count_less_equal(const T& key) const` | Returns the number of keys less than or equal to `key`. | $O(\log N)$ |
| `int count_greater(const T& key) const` | Returns the number of keys strictly greater than `key`. | $O(\log N)$ |
| `int count_greater_equal(const T& key) const` | Returns the number of keys greater than or equal to `key`. | $O(\log N)$ |
| `const T* lower_bound(const T& key) const`, `const T* min_ge(const T& key) const` | Returns the smallest key greater than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* upper_bound(const T& key) const`, `const T* min_gt(const T& key) const` | Returns the smallest key strictly greater than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_le(const T& key) const` | Returns the largest key less than or equal to `key`, or `nullptr`. | $O(\log N)$ |
| `const T* max_lt(const T& key) const` | Returns the largest key strictly less than `key`, or `nullptr`. | $O(\log N)$ |
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum key, or `nullptr` if the set is empty. | $O(\log N)$ |
| `std::pair<OrderedSet, OrderedSet> split(const T& key) &&` | Consumes the set and returns `{less, greater_equal}`. | Expected $O(\log N)$ |
| `OrderedSet merge(OrderedSet other) &&` | Consumes both sets and returns their union. Requires every key in `*this` to be smaller than every key in `other`. | Expected $O(\log(N + M))$ |
| `std::vector<T> to_vector() const` | Returns all keys in sorted order. | $O(N)$ |

## Example

```cpp
#include "ds/bst/ordered_set.hpp"

#include <iostream>
#include <utility>

int main() {
    m1une::ds::OrderedSet<int> st = {3, 1, 3, 5};

    st.insert(2);
    st.erase(3);

    auto [small, large] = std::move(st).split(4);
    st = std::move(small).merge(std::move(large));

    std::cout << st.kth(1) << "\n";           // 2
    std::cout << st.order_of_key(5) << "\n";  // 2

    if (auto p = st.max_le(4)) {
        std::cout << *p << "\n";              // 2
    }
}
```
