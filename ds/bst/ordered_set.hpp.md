---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 1 \"ds/bst/ordered_set.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <functional>\n#include <initializer_list>\n#include <memory>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <typename T, typename Compare = std::less<T>>\nstruct OrderedSet {\n\
    \   private:\n    struct Node {\n        T key;\n        int size;\n        int\
    \ height;\n        Node* l;\n        Node* r;\n\n        explicit Node(T value)\n\
    \            : key(std::move(value)), size(1), height(1), l(nullptr), r(nullptr)\
    \ {}\n    };\n\n    static constexpr int pool_block_size = 1 << 15;\n\n    struct\
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
    \ int subtree_height(const Node* t) {\n        return t == nullptr ? 0 : t->height;\n\
    \    }\n\n    Node* new_node(T key) {\n        return pool.emplace(std::move(key));\n\
    \    }\n\n    static void update(Node* t) {\n        t->size = 1 + subtree_size(t->l)\
    \ + subtree_size(t->r);\n        t->height = 1 + std::max(subtree_height(t->l),\
    \ subtree_height(t->r));\n    }\n\n    static Node* rotate_right(Node* t) {\n\
    \        Node* s = t->l;\n        t->l = s->r;\n        s->r = t;\n        update(t);\n\
    \        update(s);\n        return s;\n    }\n\n    static Node* rotate_left(Node*\
    \ t) {\n        Node* s = t->r;\n        t->r = s->l;\n        s->l = t;\n   \
    \     update(t);\n        update(s);\n        return s;\n    }\n\n    static Node*\
    \ balance(Node* t) {\n        if (t == nullptr) return nullptr;\n        update(t);\n\
    \        const int balance_factor = subtree_height(t->l) - subtree_height(t->r);\n\
    \        if (balance_factor > 1) {\n            if (subtree_height(t->l->l) <\
    \ subtree_height(t->l->r)) {\n                t->l = rotate_left(t->l);\n    \
    \        }\n            return rotate_right(t);\n        }\n        if (balance_factor\
    \ < -1) {\n            if (subtree_height(t->r->r) < subtree_height(t->r->l))\
    \ {\n                t->r = rotate_right(t->r);\n            }\n            return\
    \ rotate_left(t);\n        }\n        return t;\n    }\n\n    static Node* join_with_root(Node*\
    \ l, Node* middle, Node* r) {\n        if (subtree_height(l) > subtree_height(r)\
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
    \ bool& inserted, bool& grew) {\n        if (t == nullptr) {\n            inserted\
    \ = true;\n            grew = true;\n            return new_node(std::move(key));\n\
    \        }\n        const int old_height = t->height;\n        if (comp(key, t->key))\
    \ {\n            t->l = insert_impl(t->l, key, inserted, grew);\n        } else\
    \ if (comp(t->key, key)) {\n            t->r = insert_impl(t->r, key, inserted,\
    \ grew);\n        } else {\n            grew = false;\n            return t;\n\
    \        }\n        if (!inserted) return t;\n        if (!grew) {\n         \
    \   ++t->size;\n            return t;\n        }\n        t = balance(t);\n  \
    \      grew = t->height > old_height;\n        return t;\n    }\n\n    Node* erase_impl(Node*\
    \ t, const T& key, bool& erased, bool& shrunk) {\n        if (t == nullptr) {\n\
    \            shrunk = false;\n            return nullptr;\n        }\n       \
    \ const int old_height = t->height;\n        if (comp(key, t->key)) {\n      \
    \      t->l = erase_impl(t->l, key, erased, shrunk);\n        } else if (comp(t->key,\
    \ key)) {\n            t->r = erase_impl(t->r, key, erased, shrunk);\n       \
    \ } else {\n            erased = true;\n            Node* l = t->l;\n        \
    \    Node* r = t->r;\n            pool.recycle(t);\n            Node* result =\
    \ merge_nodes(l, r);\n            shrunk = subtree_height(result) < old_height;\n\
    \            return result;\n        }\n        if (!erased) return t;\n     \
    \   if (!shrunk) {\n            --t->size;\n            return t;\n        }\n\
    \        t = balance(t);\n        shrunk = t->height < old_height;\n        return\
    \ t;\n    }\n\n    static const T* kth_impl(const Node* t, int k) {\n        while\
    \ (t != nullptr) {\n            const int left_size = subtree_size(t->l);\n  \
    \          if (k < left_size) {\n                t = t->l;\n            } else\
    \ if (k == left_size) {\n                return &t->key;\n            } else {\n\
    \                k -= left_size + 1;\n                t = t->r;\n            }\n\
    \        }\n        return nullptr;\n    }\n\n    int order_of_key_impl(const\
    \ Node* t, const T& key, bool upper) const {\n        int result = 0;\n      \
    \  while (t != nullptr) {\n            const bool take = upper ? !comp(key, t->key)\
    \ : comp(t->key, key);\n            if (take) {\n                result += subtree_size(t->l)\
    \ + 1;\n                t = t->r;\n            } else {\n                t = t->l;\n\
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
    \ = false;\n        bool grew = false;\n        root = insert_impl(root, key,\
    \ inserted, grew);\n        return inserted;\n    }\n\n    bool erase(const T&\
    \ key) {\n        bool erased = false;\n        bool shrunk = false;\n       \
    \ root = erase_impl(root, key, erased, shrunk);\n        return erased;\n    }\n\
    \n    bool contains(const T& key) const { return contains_impl(root, key); }\n\
    \    int count(const T& key) const { return contains(key) ? 1 : 0; }\n\n    const\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_ORDERED_SET_HPP\n#define M1UNE_ORDERED_SET_HPP 1\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct\
    \ OrderedSet {\n   private:\n    struct Node {\n        T key;\n        int size;\n\
    \        int height;\n        Node* l;\n        Node* r;\n\n        explicit Node(T\
    \ value)\n            : key(std::move(value)), size(1), height(1), l(nullptr),\
    \ r(nullptr) {}\n    };\n\n    static constexpr int pool_block_size = 1 << 15;\n\
    \n    struct Pool {\n        std::vector<std::vector<Node>> blocks;\n        std::vector<Node*>\
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
    \ int subtree_height(const Node* t) {\n        return t == nullptr ? 0 : t->height;\n\
    \    }\n\n    Node* new_node(T key) {\n        return pool.emplace(std::move(key));\n\
    \    }\n\n    static void update(Node* t) {\n        t->size = 1 + subtree_size(t->l)\
    \ + subtree_size(t->r);\n        t->height = 1 + std::max(subtree_height(t->l),\
    \ subtree_height(t->r));\n    }\n\n    static Node* rotate_right(Node* t) {\n\
    \        Node* s = t->l;\n        t->l = s->r;\n        s->r = t;\n        update(t);\n\
    \        update(s);\n        return s;\n    }\n\n    static Node* rotate_left(Node*\
    \ t) {\n        Node* s = t->r;\n        t->r = s->l;\n        s->l = t;\n   \
    \     update(t);\n        update(s);\n        return s;\n    }\n\n    static Node*\
    \ balance(Node* t) {\n        if (t == nullptr) return nullptr;\n        update(t);\n\
    \        const int balance_factor = subtree_height(t->l) - subtree_height(t->r);\n\
    \        if (balance_factor > 1) {\n            if (subtree_height(t->l->l) <\
    \ subtree_height(t->l->r)) {\n                t->l = rotate_left(t->l);\n    \
    \        }\n            return rotate_right(t);\n        }\n        if (balance_factor\
    \ < -1) {\n            if (subtree_height(t->r->r) < subtree_height(t->r->l))\
    \ {\n                t->r = rotate_right(t->r);\n            }\n            return\
    \ rotate_left(t);\n        }\n        return t;\n    }\n\n    static Node* join_with_root(Node*\
    \ l, Node* middle, Node* r) {\n        if (subtree_height(l) > subtree_height(r)\
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
    \ bool& inserted, bool& grew) {\n        if (t == nullptr) {\n            inserted\
    \ = true;\n            grew = true;\n            return new_node(std::move(key));\n\
    \        }\n        const int old_height = t->height;\n        if (comp(key, t->key))\
    \ {\n            t->l = insert_impl(t->l, key, inserted, grew);\n        } else\
    \ if (comp(t->key, key)) {\n            t->r = insert_impl(t->r, key, inserted,\
    \ grew);\n        } else {\n            grew = false;\n            return t;\n\
    \        }\n        if (!inserted) return t;\n        if (!grew) {\n         \
    \   ++t->size;\n            return t;\n        }\n        t = balance(t);\n  \
    \      grew = t->height > old_height;\n        return t;\n    }\n\n    Node* erase_impl(Node*\
    \ t, const T& key, bool& erased, bool& shrunk) {\n        if (t == nullptr) {\n\
    \            shrunk = false;\n            return nullptr;\n        }\n       \
    \ const int old_height = t->height;\n        if (comp(key, t->key)) {\n      \
    \      t->l = erase_impl(t->l, key, erased, shrunk);\n        } else if (comp(t->key,\
    \ key)) {\n            t->r = erase_impl(t->r, key, erased, shrunk);\n       \
    \ } else {\n            erased = true;\n            Node* l = t->l;\n        \
    \    Node* r = t->r;\n            pool.recycle(t);\n            Node* result =\
    \ merge_nodes(l, r);\n            shrunk = subtree_height(result) < old_height;\n\
    \            return result;\n        }\n        if (!erased) return t;\n     \
    \   if (!shrunk) {\n            --t->size;\n            return t;\n        }\n\
    \        t = balance(t);\n        shrunk = t->height < old_height;\n        return\
    \ t;\n    }\n\n    static const T* kth_impl(const Node* t, int k) {\n        while\
    \ (t != nullptr) {\n            const int left_size = subtree_size(t->l);\n  \
    \          if (k < left_size) {\n                t = t->l;\n            } else\
    \ if (k == left_size) {\n                return &t->key;\n            } else {\n\
    \                k -= left_size + 1;\n                t = t->r;\n            }\n\
    \        }\n        return nullptr;\n    }\n\n    int order_of_key_impl(const\
    \ Node* t, const T& key, bool upper) const {\n        int result = 0;\n      \
    \  while (t != nullptr) {\n            const bool take = upper ? !comp(key, t->key)\
    \ : comp(t->key, key);\n            if (take) {\n                result += subtree_size(t->l)\
    \ + 1;\n                t = t->r;\n            } else {\n                t = t->l;\n\
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
    \ = false;\n        bool grew = false;\n        root = insert_impl(root, key,\
    \ inserted, grew);\n        return inserted;\n    }\n\n    bool erase(const T&\
    \ key) {\n        bool erased = false;\n        bool shrunk = false;\n       \
    \ root = erase_impl(root, key, erased, shrunk);\n        return erased;\n    }\n\
    \n    bool contains(const T& key) const { return contains_impl(root, key); }\n\
    \    int count(const T& key) const { return contains(key) ? 1 : 0; }\n\n    const\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_ORDERED_SET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/bst/ordered_set.hpp
  requiredBy: []
  timestamp: '2026-07-13 02:53:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/bst/ordered_set.test.cpp
documentation_of: ds/bst/ordered_set.hpp
layout: document
title: Ordered Set
---

## Overview

`OrderedSet` is an AVL tree for sets. It keeps unique keys only, like
`std::set`, and also supports order-statistics queries such as k-th element and
rank. Nodes come from a recyclable block arena, so insertion and erasure avoid
general-purpose per-node allocation.

The arena is shared by each `OrderedSet<T, Compare>` specialization. Erased or
destroyed nodes are reused, while the arena's peak capacity is retained until
program exit.

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
| `void clear()` | Removes all keys and returns their nodes to the arena. | $O(N)$ |
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
| `std::pair<OrderedSet, OrderedSet> split(const T& key) &&` | Consumes the set and returns `{less, greater_equal}`. | $O(\log N)$ |
| `OrderedSet merge(OrderedSet other) &&` | Consumes both sets and returns their union. Requires every key in `*this` to be smaller than every key in `other`. | $O(\log(N + M))$ |
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
