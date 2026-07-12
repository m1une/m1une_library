---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/bst/ordered_multiset.test.cpp
    title: verify/ds/bst/ordered_multiset.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/bst/ordered_multiset.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <initializer_list>\n#include\
    \ <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct OrderedMultiset\
    \ {\n   private:\n    struct Node {\n        T key;\n        int count;\n    \
    \    int size;\n        int distinct_size;\n        int height;\n        Node*\
    \ l;\n        Node* r;\n\n        Node(T value, int multiplicity)\n          \
    \  : key(std::move(value)),\n              count(multiplicity),\n            \
    \  size(multiplicity),\n              distinct_size(1),\n              height(1),\n\
    \              l(nullptr),\n              r(nullptr) {}\n    };\n\n    static\
    \ constexpr int pool_block_size = 1 << 14;\n\n    struct Pool {\n        std::vector<std::vector<Node>>\
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
    \ : t->distinct_size;\n    }\n\n    static int subtree_height(const Node* t) {\n\
    \        return t == nullptr ? 0 : t->height;\n    }\n\n    bool equal(const T&\
    \ a, const T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\n\
    \    Node* new_node(T key, int multiplicity) {\n        return pool.emplace(std::move(key),\
    \ multiplicity);\n    }\n\n    static void update(Node* t) {\n        t->size\
    \ = t->count + subtree_size(t->l) + subtree_size(t->r);\n        t->distinct_size\
    \ = 1 + subtree_distinct_size(t->l) + subtree_distinct_size(t->r);\n        t->height\
    \ = 1 + std::max(subtree_height(t->l), subtree_height(t->r));\n    }\n\n    static\
    \ Node* rotate_right(Node* t) {\n        Node* s = t->l;\n        t->l = s->r;\n\
    \        s->r = t;\n        update(t);\n        update(s);\n        return s;\n\
    \    }\n\n    static Node* rotate_left(Node* t) {\n        Node* s = t->r;\n \
    \       t->r = s->l;\n        s->l = t;\n        update(t);\n        update(s);\n\
    \        return s;\n    }\n\n    static Node* balance(Node* t) {\n        if (t\
    \ == nullptr) return nullptr;\n        update(t);\n        const int balance_factor\
    \ = subtree_height(t->l) - subtree_height(t->r);\n        if (balance_factor >\
    \ 1) {\n            if (subtree_height(t->l->l) < subtree_height(t->l->r)) {\n\
    \                t->l = rotate_left(t->l);\n            }\n            return\
    \ rotate_right(t);\n        }\n        if (balance_factor < -1) {\n          \
    \  if (subtree_height(t->r->r) < subtree_height(t->r->l)) {\n                t->r\
    \ = rotate_right(t->r);\n            }\n            return rotate_left(t);\n \
    \       }\n        return t;\n    }\n\n    static Node* join_with_root(Node* l,\
    \ Node* middle, Node* r) {\n        if (subtree_height(l) > subtree_height(r)\
    \ + 1) {\n            l->r = join_with_root(l->r, middle, r);\n            return\
    \ balance(l);\n        }\n        if (subtree_height(r) > subtree_height(l) +\
    \ 1) {\n            r->l = join_with_root(l, middle, r->l);\n            return\
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
    \ int multiplicity, bool& new_key, bool& grew) {\n        if (t == nullptr) {\n\
    \            new_key = true;\n            grew = true;\n            return new_node(std::move(key),\
    \ multiplicity);\n        }\n        const int old_height = t->height;\n     \
    \   if (comp(key, t->key)) {\n            t->l = insert_impl(t->l, key, multiplicity,\
    \ new_key, grew);\n        } else if (comp(t->key, key)) {\n            t->r =\
    \ insert_impl(t->r, key, multiplicity, new_key, grew);\n        } else {\n   \
    \         t->count += multiplicity;\n            t->size += multiplicity;\n  \
    \          new_key = false;\n            grew = false;\n            return t;\n\
    \        }\n        if (!grew) {\n            t->size += multiplicity;\n     \
    \       t->distinct_size += int(new_key);\n            return t;\n        }\n\
    \        t = balance(t);\n        grew = t->height > old_height;\n        return\
    \ t;\n    }\n\n    Node* erase_impl(Node* t, const T& key, bool erase_all,\n \
    \                    int& erased, bool& removed_key, bool& shrunk) {\n       \
    \ if (t == nullptr) {\n            shrunk = false;\n            return nullptr;\n\
    \        }\n        const int old_height = t->height;\n        if (comp(key, t->key))\
    \ {\n            t->l = erase_impl(t->l, key, erase_all, erased, removed_key,\
    \ shrunk);\n        } else if (comp(t->key, key)) {\n            t->r = erase_impl(t->r,\
    \ key, erase_all, erased, removed_key, shrunk);\n        } else if (!erase_all\
    \ && t->count > 1) {\n            --t->count;\n            --t->size;\n      \
    \      erased = 1;\n            removed_key = false;\n            shrunk = false;\n\
    \            return t;\n        } else {\n            erased = t->count;\n   \
    \         removed_key = true;\n            Node* l = t->l;\n            Node*\
    \ r = t->r;\n            pool.recycle(t);\n            Node* result = merge_nodes(l,\
    \ r);\n            shrunk = subtree_height(result) < old_height;\n           \
    \ return result;\n        }\n        if (erased == 0) return t;\n        if (!shrunk)\
    \ {\n            t->size -= erased;\n            t->distinct_size -= int(removed_key);\n\
    \            return t;\n        }\n        t = balance(t);\n        shrunk = t->height\
    \ < old_height;\n        return t;\n    }\n\n    static const T* kth_impl(const\
    \ Node* t, int k) {\n        while (t != nullptr) {\n            const int left_size\
    \ = subtree_size(t->l);\n            if (k < left_size) {\n                t =\
    \ t->l;\n            } else if (k < left_size + t->count) {\n                return\
    \ &t->key;\n            } else {\n                k -= left_size + t->count;\n\
    \                t = t->r;\n            }\n        }\n        return nullptr;\n\
    \    }\n\n    int count_impl(const Node* t, const T& key) const {\n        while\
    \ (t != nullptr) {\n            if (comp(key, t->key)) {\n                t =\
    \ t->l;\n            } else if (comp(t->key, key)) {\n                t = t->r;\n\
    \            } else {\n                return t->count;\n            }\n     \
    \   }\n        return 0;\n    }\n\n    int order_of_key_impl(const Node* t, const\
    \ T& key, bool upper) const {\n        int result = 0;\n        while (t != nullptr)\
    \ {\n            const bool take = upper ? !comp(key, t->key) : comp(t->key, key);\n\
    \            if (take) {\n                result += subtree_size(t->l) + t->count;\n\
    \                t = t->r;\n            } else {\n                t = t->l;\n\
    \            }\n        }\n        return result;\n    }\n\n    const T* lower_bound_impl(const\
    \ Node* t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != nullptr) {\n            const bool candidate = strict ? comp(key,\
    \ t->key) : !comp(t->key, key);\n            if (candidate) {\n              \
    \  result = &t->key;\n                t = t->l;\n            } else {\n      \
    \          t = t->r;\n            }\n        }\n        return result;\n    }\n\
    \n    const T* max_less_impl(const Node* t, const T& key, bool strict) const {\n\
    \        const T* result = nullptr;\n        while (t != nullptr) {\n        \
    \    const bool candidate = strict ? comp(t->key, key) : !comp(key, t->key);\n\
    \            if (candidate) {\n                result = &t->key;\n           \
    \     t = t->r;\n            } else {\n                t = t->l;\n           \
    \ }\n        }\n        return result;\n    }\n\n    static void dump_impl(const\
    \ Node* t, std::vector<T>& result) {\n        if (t == nullptr) return;\n    \
    \    dump_impl(t->l, result);\n        for (int i = 0; i < t->count; ++i) result.push_back(t->key);\n\
    \        dump_impl(t->r, result);\n    }\n\n    static void recycle_impl(Node*\
    \ t) {\n        if (t == nullptr) return;\n        recycle_impl(t->l);\n     \
    \   recycle_impl(t->r);\n        pool.recycle(t);\n    }\n\n    Node* clone_impl(const\
    \ Node* t) {\n        if (t == nullptr) return nullptr;\n        Node* result\
    \ = new_node(t->key, t->count);\n        result->l = clone_impl(t->l);\n     \
    \   result->r = clone_impl(t->r);\n        update(result);\n        return result;\n\
    \    }\n\n    OrderedMultiset(Node* node, Compare compare) : root(node), comp(std::move(compare))\
    \ {}\n\n   public:\n    explicit OrderedMultiset(Compare compare) : root(nullptr),\
    \ comp(std::move(compare)) {}\n    OrderedMultiset() : OrderedMultiset(Compare())\
    \ {}\n\n    OrderedMultiset(std::initializer_list<T> init, Compare compare = Compare())\n\
    \        : OrderedMultiset(std::move(compare)) {\n        for (const T& x : init)\
    \ insert(x);\n    }\n\n    template <typename Iterator>\n    OrderedMultiset(Iterator\
    \ first, Iterator last, Compare compare = Compare())\n        : OrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) insert(*first++);\n    }\n\n    OrderedMultiset(const\
    \ OrderedMultiset& other) : root(nullptr), comp(other.comp) {\n        root =\
    \ clone_impl(other.root);\n    }\n\n    OrderedMultiset(OrderedMultiset&& other)\
    \ noexcept\n        : root(std::exchange(other.root, nullptr)), comp(std::move(other.comp))\
    \ {}\n\n    ~OrderedMultiset() {\n        recycle_impl(root);\n    }\n\n    OrderedMultiset&\
    \ operator=(OrderedMultiset other) {\n        swap(other);\n        return *this;\n\
    \    }\n\n    void swap(OrderedMultiset& other) noexcept {\n        using std::swap;\n\
    \        swap(root, other.root);\n        swap(comp, other.comp);\n    }\n\n \
    \   int size() const { return subtree_size(root); }\n    int unique_size() const\
    \ { return subtree_distinct_size(root); }\n    bool empty() const { return root\
    \ == nullptr; }\n\n    void clear() {\n        recycle_impl(root);\n        root\
    \ = nullptr;\n    }\n\n    void insert(T key, int multiplicity = 1) {\n      \
    \  assert(multiplicity > 0);\n        bool new_key = false;\n        bool grew\
    \ = false;\n        root = insert_impl(root, key, multiplicity, new_key, grew);\n\
    \    }\n\n    bool erase_one(const T& key) {\n        int erased = 0;\n      \
    \  bool removed_key = false;\n        bool shrunk = false;\n        root = erase_impl(root,\
    \ key, false, erased, removed_key, shrunk);\n        return erased != 0;\n   \
    \ }\n\n    bool erase(const T& key) { return erase_one(key); }\n\n    int erase_all(const\
    \ T& key) {\n        int erased = 0;\n        bool removed_key = false;\n    \
    \    bool shrunk = false;\n        root = erase_impl(root, key, true, erased,\
    \ removed_key, shrunk);\n        return erased;\n    }\n\n    bool contains(const\
    \ T& key) const { return count(key) > 0; }\n    int count(const T& key) const\
    \ { return count_impl(root, key); }\n\n    const T* find_by_order(int k) const\
    \ {\n        assert(0 <= k && k < size());\n        return kth_impl(root, k);\n\
    \    }\n\n    T kth(int k) const { return *find_by_order(k); }\n    int order_of_key(const\
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
    \ key);\n        root = nullptr;\n        return {OrderedMultiset(l, comp), OrderedMultiset(r,\
    \ std::move(comp))};\n    }\n\n    OrderedMultiset merge(OrderedMultiset other)\
    \ && {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        root = merge_nodes(root, other.root);\n        other.root = nullptr;\n\
    \        return std::move(*this);\n    }\n\n    std::vector<T> to_vector() const\
    \ {\n        std::vector<T> result;\n        result.reserve(size());\n       \
    \ dump_impl(root, result);\n        return result;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ORDERED_MULTISET_HPP\n#define M1UNE_ORDERED_MULTISET_HPP 1\n\
    \n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct\
    \ OrderedMultiset {\n   private:\n    struct Node {\n        T key;\n        int\
    \ count;\n        int size;\n        int distinct_size;\n        int height;\n\
    \        Node* l;\n        Node* r;\n\n        Node(T value, int multiplicity)\n\
    \            : key(std::move(value)),\n              count(multiplicity),\n  \
    \            size(multiplicity),\n              distinct_size(1),\n          \
    \    height(1),\n              l(nullptr),\n              r(nullptr) {}\n    };\n\
    \n    static constexpr int pool_block_size = 1 << 14;\n\n    struct Pool {\n \
    \       std::vector<std::vector<Node>> blocks;\n        std::vector<Node*> free_nodes;\n\
    \n        template <class... Args>\n        Node* emplace(Args&&... args) {\n\
    \            if (!free_nodes.empty()) {\n                Node* result = free_nodes.back();\n\
    \                free_nodes.pop_back();\n                std::destroy_at(result);\n\
    \                std::construct_at(result, std::forward<Args>(args)...);\n   \
    \             return result;\n            }\n            if (blocks.empty() ||\
    \ int(blocks.back().size()) == pool_block_size) {\n                blocks.emplace_back();\n\
    \                blocks.back().reserve(pool_block_size);\n            }\n    \
    \        blocks.back().emplace_back(std::forward<Args>(args)...);\n          \
    \  return &blocks.back().back();\n        }\n\n        void recycle(Node* node)\
    \ {\n            free_nodes.push_back(node);\n        }\n    };\n\n    inline\
    \ static Pool pool;\n\n    Node* root;\n    Compare comp;\n\n    static int subtree_size(const\
    \ Node* t) {\n        return t == nullptr ? 0 : t->size;\n    }\n\n    static\
    \ int subtree_distinct_size(const Node* t) {\n        return t == nullptr ? 0\
    \ : t->distinct_size;\n    }\n\n    static int subtree_height(const Node* t) {\n\
    \        return t == nullptr ? 0 : t->height;\n    }\n\n    bool equal(const T&\
    \ a, const T& b) const {\n        return !comp(a, b) && !comp(b, a);\n    }\n\n\
    \    Node* new_node(T key, int multiplicity) {\n        return pool.emplace(std::move(key),\
    \ multiplicity);\n    }\n\n    static void update(Node* t) {\n        t->size\
    \ = t->count + subtree_size(t->l) + subtree_size(t->r);\n        t->distinct_size\
    \ = 1 + subtree_distinct_size(t->l) + subtree_distinct_size(t->r);\n        t->height\
    \ = 1 + std::max(subtree_height(t->l), subtree_height(t->r));\n    }\n\n    static\
    \ Node* rotate_right(Node* t) {\n        Node* s = t->l;\n        t->l = s->r;\n\
    \        s->r = t;\n        update(t);\n        update(s);\n        return s;\n\
    \    }\n\n    static Node* rotate_left(Node* t) {\n        Node* s = t->r;\n \
    \       t->r = s->l;\n        s->l = t;\n        update(t);\n        update(s);\n\
    \        return s;\n    }\n\n    static Node* balance(Node* t) {\n        if (t\
    \ == nullptr) return nullptr;\n        update(t);\n        const int balance_factor\
    \ = subtree_height(t->l) - subtree_height(t->r);\n        if (balance_factor >\
    \ 1) {\n            if (subtree_height(t->l->l) < subtree_height(t->l->r)) {\n\
    \                t->l = rotate_left(t->l);\n            }\n            return\
    \ rotate_right(t);\n        }\n        if (balance_factor < -1) {\n          \
    \  if (subtree_height(t->r->r) < subtree_height(t->r->l)) {\n                t->r\
    \ = rotate_right(t->r);\n            }\n            return rotate_left(t);\n \
    \       }\n        return t;\n    }\n\n    static Node* join_with_root(Node* l,\
    \ Node* middle, Node* r) {\n        if (subtree_height(l) > subtree_height(r)\
    \ + 1) {\n            l->r = join_with_root(l->r, middle, r);\n            return\
    \ balance(l);\n        }\n        if (subtree_height(r) > subtree_height(l) +\
    \ 1) {\n            r->l = join_with_root(l, middle, r->l);\n            return\
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
    \ int multiplicity, bool& new_key, bool& grew) {\n        if (t == nullptr) {\n\
    \            new_key = true;\n            grew = true;\n            return new_node(std::move(key),\
    \ multiplicity);\n        }\n        const int old_height = t->height;\n     \
    \   if (comp(key, t->key)) {\n            t->l = insert_impl(t->l, key, multiplicity,\
    \ new_key, grew);\n        } else if (comp(t->key, key)) {\n            t->r =\
    \ insert_impl(t->r, key, multiplicity, new_key, grew);\n        } else {\n   \
    \         t->count += multiplicity;\n            t->size += multiplicity;\n  \
    \          new_key = false;\n            grew = false;\n            return t;\n\
    \        }\n        if (!grew) {\n            t->size += multiplicity;\n     \
    \       t->distinct_size += int(new_key);\n            return t;\n        }\n\
    \        t = balance(t);\n        grew = t->height > old_height;\n        return\
    \ t;\n    }\n\n    Node* erase_impl(Node* t, const T& key, bool erase_all,\n \
    \                    int& erased, bool& removed_key, bool& shrunk) {\n       \
    \ if (t == nullptr) {\n            shrunk = false;\n            return nullptr;\n\
    \        }\n        const int old_height = t->height;\n        if (comp(key, t->key))\
    \ {\n            t->l = erase_impl(t->l, key, erase_all, erased, removed_key,\
    \ shrunk);\n        } else if (comp(t->key, key)) {\n            t->r = erase_impl(t->r,\
    \ key, erase_all, erased, removed_key, shrunk);\n        } else if (!erase_all\
    \ && t->count > 1) {\n            --t->count;\n            --t->size;\n      \
    \      erased = 1;\n            removed_key = false;\n            shrunk = false;\n\
    \            return t;\n        } else {\n            erased = t->count;\n   \
    \         removed_key = true;\n            Node* l = t->l;\n            Node*\
    \ r = t->r;\n            pool.recycle(t);\n            Node* result = merge_nodes(l,\
    \ r);\n            shrunk = subtree_height(result) < old_height;\n           \
    \ return result;\n        }\n        if (erased == 0) return t;\n        if (!shrunk)\
    \ {\n            t->size -= erased;\n            t->distinct_size -= int(removed_key);\n\
    \            return t;\n        }\n        t = balance(t);\n        shrunk = t->height\
    \ < old_height;\n        return t;\n    }\n\n    static const T* kth_impl(const\
    \ Node* t, int k) {\n        while (t != nullptr) {\n            const int left_size\
    \ = subtree_size(t->l);\n            if (k < left_size) {\n                t =\
    \ t->l;\n            } else if (k < left_size + t->count) {\n                return\
    \ &t->key;\n            } else {\n                k -= left_size + t->count;\n\
    \                t = t->r;\n            }\n        }\n        return nullptr;\n\
    \    }\n\n    int count_impl(const Node* t, const T& key) const {\n        while\
    \ (t != nullptr) {\n            if (comp(key, t->key)) {\n                t =\
    \ t->l;\n            } else if (comp(t->key, key)) {\n                t = t->r;\n\
    \            } else {\n                return t->count;\n            }\n     \
    \   }\n        return 0;\n    }\n\n    int order_of_key_impl(const Node* t, const\
    \ T& key, bool upper) const {\n        int result = 0;\n        while (t != nullptr)\
    \ {\n            const bool take = upper ? !comp(key, t->key) : comp(t->key, key);\n\
    \            if (take) {\n                result += subtree_size(t->l) + t->count;\n\
    \                t = t->r;\n            } else {\n                t = t->l;\n\
    \            }\n        }\n        return result;\n    }\n\n    const T* lower_bound_impl(const\
    \ Node* t, const T& key, bool strict) const {\n        const T* result = nullptr;\n\
    \        while (t != nullptr) {\n            const bool candidate = strict ? comp(key,\
    \ t->key) : !comp(t->key, key);\n            if (candidate) {\n              \
    \  result = &t->key;\n                t = t->l;\n            } else {\n      \
    \          t = t->r;\n            }\n        }\n        return result;\n    }\n\
    \n    const T* max_less_impl(const Node* t, const T& key, bool strict) const {\n\
    \        const T* result = nullptr;\n        while (t != nullptr) {\n        \
    \    const bool candidate = strict ? comp(t->key, key) : !comp(key, t->key);\n\
    \            if (candidate) {\n                result = &t->key;\n           \
    \     t = t->r;\n            } else {\n                t = t->l;\n           \
    \ }\n        }\n        return result;\n    }\n\n    static void dump_impl(const\
    \ Node* t, std::vector<T>& result) {\n        if (t == nullptr) return;\n    \
    \    dump_impl(t->l, result);\n        for (int i = 0; i < t->count; ++i) result.push_back(t->key);\n\
    \        dump_impl(t->r, result);\n    }\n\n    static void recycle_impl(Node*\
    \ t) {\n        if (t == nullptr) return;\n        recycle_impl(t->l);\n     \
    \   recycle_impl(t->r);\n        pool.recycle(t);\n    }\n\n    Node* clone_impl(const\
    \ Node* t) {\n        if (t == nullptr) return nullptr;\n        Node* result\
    \ = new_node(t->key, t->count);\n        result->l = clone_impl(t->l);\n     \
    \   result->r = clone_impl(t->r);\n        update(result);\n        return result;\n\
    \    }\n\n    OrderedMultiset(Node* node, Compare compare) : root(node), comp(std::move(compare))\
    \ {}\n\n   public:\n    explicit OrderedMultiset(Compare compare) : root(nullptr),\
    \ comp(std::move(compare)) {}\n    OrderedMultiset() : OrderedMultiset(Compare())\
    \ {}\n\n    OrderedMultiset(std::initializer_list<T> init, Compare compare = Compare())\n\
    \        : OrderedMultiset(std::move(compare)) {\n        for (const T& x : init)\
    \ insert(x);\n    }\n\n    template <typename Iterator>\n    OrderedMultiset(Iterator\
    \ first, Iterator last, Compare compare = Compare())\n        : OrderedMultiset(std::move(compare))\
    \ {\n        while (first != last) insert(*first++);\n    }\n\n    OrderedMultiset(const\
    \ OrderedMultiset& other) : root(nullptr), comp(other.comp) {\n        root =\
    \ clone_impl(other.root);\n    }\n\n    OrderedMultiset(OrderedMultiset&& other)\
    \ noexcept\n        : root(std::exchange(other.root, nullptr)), comp(std::move(other.comp))\
    \ {}\n\n    ~OrderedMultiset() {\n        recycle_impl(root);\n    }\n\n    OrderedMultiset&\
    \ operator=(OrderedMultiset other) {\n        swap(other);\n        return *this;\n\
    \    }\n\n    void swap(OrderedMultiset& other) noexcept {\n        using std::swap;\n\
    \        swap(root, other.root);\n        swap(comp, other.comp);\n    }\n\n \
    \   int size() const { return subtree_size(root); }\n    int unique_size() const\
    \ { return subtree_distinct_size(root); }\n    bool empty() const { return root\
    \ == nullptr; }\n\n    void clear() {\n        recycle_impl(root);\n        root\
    \ = nullptr;\n    }\n\n    void insert(T key, int multiplicity = 1) {\n      \
    \  assert(multiplicity > 0);\n        bool new_key = false;\n        bool grew\
    \ = false;\n        root = insert_impl(root, key, multiplicity, new_key, grew);\n\
    \    }\n\n    bool erase_one(const T& key) {\n        int erased = 0;\n      \
    \  bool removed_key = false;\n        bool shrunk = false;\n        root = erase_impl(root,\
    \ key, false, erased, removed_key, shrunk);\n        return erased != 0;\n   \
    \ }\n\n    bool erase(const T& key) { return erase_one(key); }\n\n    int erase_all(const\
    \ T& key) {\n        int erased = 0;\n        bool removed_key = false;\n    \
    \    bool shrunk = false;\n        root = erase_impl(root, key, true, erased,\
    \ removed_key, shrunk);\n        return erased;\n    }\n\n    bool contains(const\
    \ T& key) const { return count(key) > 0; }\n    int count(const T& key) const\
    \ { return count_impl(root, key); }\n\n    const T* find_by_order(int k) const\
    \ {\n        assert(0 <= k && k < size());\n        return kth_impl(root, k);\n\
    \    }\n\n    T kth(int k) const { return *find_by_order(k); }\n    int order_of_key(const\
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
    \ key);\n        root = nullptr;\n        return {OrderedMultiset(l, comp), OrderedMultiset(r,\
    \ std::move(comp))};\n    }\n\n    OrderedMultiset merge(OrderedMultiset other)\
    \ && {\n        assert(empty() || other.empty() || comp(*max(), *other.min()));\n\
    \        root = merge_nodes(root, other.root);\n        other.root = nullptr;\n\
    \        return std::move(*this);\n    }\n\n    std::vector<T> to_vector() const\
    \ {\n        std::vector<T> result;\n        result.reserve(size());\n       \
    \ dump_impl(root, result);\n        return result;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n#endif  // M1UNE_ORDERED_MULTISET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/bst/ordered_multiset.hpp
  requiredBy: []
  timestamp: '2026-07-13 02:53:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/ordered_multiset.test.cpp
documentation_of: ds/bst/ordered_multiset.hpp
layout: document
title: Ordered Multiset
---

## Overview

`OrderedMultiset` is an AVL tree for multisets. It stores equal keys as one node
with a multiplicity, so it supports standard multiset operations plus
order-statistics queries such as k-th element and rank. Nodes come from a
recyclable block arena, avoiding general-purpose per-node allocation.

The arena is shared by each `OrderedMultiset<T, Compare>` specialization.
Erased or destroyed nodes are reused, while the arena's peak capacity is
retained until program exit.

`split(key)` consumes a tree and partitions it into keys `< key` and keys
`>= key`. `merge(other)` consumes two trees whose key ranges are strictly
ordered. Equal keys therefore cannot occur across the merge boundary.

Pointers returned by bound and predecessor/successor methods remain valid until the multiset is modified.

## Template Parameters

* `T`: The key type.
* `Compare`: Ordering predicate. Defaults to `std::less<T>`.

Trees passed to `merge` must use equivalent comparator state.

## Constructors

* `OrderedMultiset()`
  Constructs an empty multiset. ($O(1)$)

* `OrderedMultiset(Compare compare)`
  Constructs an empty multiset with a custom comparator. ($O(1)$)

* `OrderedMultiset(std::initializer_list<T> init)`
  Constructs a multiset from an initializer list. ($O(N \log N)$)

* `OrderedMultiset(Iterator first, Iterator last)`
  Constructs a multiset from a range. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the total number of elements, including duplicates. | $O(1)$ |
| `int unique_size() const` | Returns the number of distinct keys. | $O(1)$ |
| `bool empty() const` | Returns whether the multiset is empty. | $O(1)$ |
| `void clear()` | Removes all elements and returns their nodes to the arena. | $O(N)$ |
| `void insert(T key, int multiplicity = 1)` | Inserts `multiplicity` copies of `key`. | $O(\log N)$ |
| `bool erase_one(const T& key)` | Removes one copy of `key`; returns whether an element was removed. | $O(\log N)$ |
| `bool erase(const T& key)` | Alias for `erase_one(key)`. | $O(\log N)$ |
| `int erase_all(const T& key)` | Removes all copies of `key` and returns the number removed. | $O(\log N)$ |
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
| `const T* min() const`, `const T* max() const` | Returns the minimum or maximum element, or `nullptr` if the multiset is empty. | $O(\log N)$ |
| `std::pair<OrderedMultiset, OrderedMultiset> split(const T& key) &&` | Consumes the multiset and returns `{less, greater_equal}`. | $O(\log N)$ |
| `OrderedMultiset merge(OrderedMultiset other) &&` | Consumes both multisets and returns their union. Requires every key in `*this` to be smaller than every key in `other`. | $O(\log(N + M))$ |
| `std::vector<T> to_vector() const` | Returns all elements in sorted order, including duplicates. | $O(N)$ |

## Example

```cpp
#include "ds/bst/ordered_multiset.hpp"

#include <iostream>
#include <utility>

int main() {
    m1une::ds::OrderedMultiset<int> ms = {3, 1, 3, 5};

    ms.insert(2);
    ms.erase_one(3);

    auto [small, large] = std::move(ms).split(3);
    ms = std::move(small).merge(std::move(large));

    std::cout << ms.kth(2) << "\n";           // 3
    std::cout << ms.order_of_key(4) << "\n";  // 3

    if (auto p = ms.max_le(4)) {
        std::cout << *p << "\n";              // 3
    }
}
```
