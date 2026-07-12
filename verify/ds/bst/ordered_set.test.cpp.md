---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_set.hpp
    title: Ordered Set
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
  bundledCode: "#line 1 \"verify/ds/bst/ordered_set.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/ordered_set\"\n\n#line 1 \"ds/bst/ordered_set.hpp\"\
    \n\n\n\n#include <cassert>\n#include <functional>\n#include <initializer_list>\n\
    #include <memory>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\ntemplate <typename T, typename Compare = std::less<T>>\nstruct\
    \ OrderedSet {\n   private:\n    struct Node {\n        T key;\n        int size;\n\
    \        Node* l;\n        Node* r;\n\n        explicit Node(T value)\n      \
    \      : key(std::move(value)), size(1), l(nullptr), r(nullptr) {}\n    };\n\n\
    \    static constexpr int pool_block_size = 1 << 15;\n\n    struct Pool {\n  \
    \      std::vector<std::vector<Node>> blocks;\n        std::vector<Node*> free_nodes;\n\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/bst/ordered_set.test.cpp\"\
    \n\n#line 6 \"verify/ds/bst/ordered_set.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#include <iterator>\n#include <set>\n#line 12 \"verify/ds/bst/ordered_set.test.cpp\"\
    \n\nvoid randomized_test() {\n    m1une::ds::OrderedSet<int> tree;\n    std::set<int>\
    \ expected;\n    std::uint64_t state = 123456789;\n    for (int query = 0; query\
    \ < 10000; ++query) {\n        state = state * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        const int key = int(state >> 32) % 1000;\n        const int type = int(state\
    \ % 5);\n        if (type <= 1) {\n            assert(tree.insert(key) == expected.insert(key).second);\n\
    \        } else if (type == 2) {\n            assert(tree.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 3) {\n            assert(tree.contains(key)\
    \ == expected.contains(key));\n            assert(tree.order_of_key(key) == int(std::distance(expected.begin(),\
    \ expected.lower_bound(key))));\n        } else {\n            auto copy = tree;\n\
    \            auto [left, right] = std::move(tree).split(key);\n            std::vector<int>\
    \ expected_left(expected.begin(), expected.lower_bound(key));\n            std::vector<int>\
    \ expected_right(expected.lower_bound(key), expected.end());\n            assert(left.to_vector()\
    \ == expected_left);\n            assert(right.to_vector() == expected_right);\n\
    \            tree = std::move(left).merge(std::move(right));\n            assert(copy.to_vector()\
    \ == tree.to_vector());\n        }\n        assert(tree.size() == int(expected.size()));\n\
    \        assert(tree.to_vector() == std::vector<int>(expected.begin(), expected.end()));\n\
    \    }\n}\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n    randomized_test();\n\
    \n    m1une::ds::OrderedSet<int> split_test = {1, 3, 5};\n    auto [small, large]\
    \ = std::move(split_test).split(3);\n    split_test = std::move(small).merge(std::move(large));\n\
    \    assert(split_test.size() == 3 && split_test.kth(1) == 3);\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    m1une::ds::OrderedSet<int> st;\n    for (int i\
    \ = 0; i < N; i++) {\n        int a;\n        std::cin >> a;\n        st.insert(a);\n\
    \    }\n\n    while (Q--) {\n        int type, x;\n        std::cin >> type >>\
    \ x;\n\n        if (type == 0) {\n            st.insert(x);\n        } else if\
    \ (type == 1) {\n            st.erase(x);\n        } else if (type == 2) {\n \
    \           if (st.size() < x) {\n                std::cout << -1 << '\\n';\n\
    \            } else {\n                std::cout << st.kth(x - 1) << '\\n';\n\
    \            }\n        } else if (type == 3) {\n            std::cout << st.count_less_equal(x)\
    \ << '\\n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            std::cout << (ans ? *ans : -1) << '\\n';\n        } else {\n    \
    \        const int* ans = st.min_ge(x);\n            std::cout << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ \"../../../ds/bst/ordered_set.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <iterator>\n#include <set>\n#include <utility>\n\
    #include <vector>\n\nvoid randomized_test() {\n    m1une::ds::OrderedSet<int>\
    \ tree;\n    std::set<int> expected;\n    std::uint64_t state = 123456789;\n \
    \   for (int query = 0; query < 10000; ++query) {\n        state = state * 6364136223846793005ULL\
    \ + 1442695040888963407ULL;\n        const int key = int(state >> 32) % 1000;\n\
    \        const int type = int(state % 5);\n        if (type <= 1) {\n        \
    \    assert(tree.insert(key) == expected.insert(key).second);\n        } else\
    \ if (type == 2) {\n            assert(tree.erase(key) == (expected.erase(key)\
    \ != 0));\n        } else if (type == 3) {\n            assert(tree.contains(key)\
    \ == expected.contains(key));\n            assert(tree.order_of_key(key) == int(std::distance(expected.begin(),\
    \ expected.lower_bound(key))));\n        } else {\n            auto copy = tree;\n\
    \            auto [left, right] = std::move(tree).split(key);\n            std::vector<int>\
    \ expected_left(expected.begin(), expected.lower_bound(key));\n            std::vector<int>\
    \ expected_right(expected.lower_bound(key), expected.end());\n            assert(left.to_vector()\
    \ == expected_left);\n            assert(right.to_vector() == expected_right);\n\
    \            tree = std::move(left).merge(std::move(right));\n            assert(copy.to_vector()\
    \ == tree.to_vector());\n        }\n        assert(tree.size() == int(expected.size()));\n\
    \        assert(tree.to_vector() == std::vector<int>(expected.begin(), expected.end()));\n\
    \    }\n}\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n  \
    \  std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n    randomized_test();\n\
    \n    m1une::ds::OrderedSet<int> split_test = {1, 3, 5};\n    auto [small, large]\
    \ = std::move(split_test).split(3);\n    split_test = std::move(small).merge(std::move(large));\n\
    \    assert(split_test.size() == 3 && split_test.kth(1) == 3);\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    m1une::ds::OrderedSet<int> st;\n    for (int i\
    \ = 0; i < N; i++) {\n        int a;\n        std::cin >> a;\n        st.insert(a);\n\
    \    }\n\n    while (Q--) {\n        int type, x;\n        std::cin >> type >>\
    \ x;\n\n        if (type == 0) {\n            st.insert(x);\n        } else if\
    \ (type == 1) {\n            st.erase(x);\n        } else if (type == 2) {\n \
    \           if (st.size() < x) {\n                std::cout << -1 << '\\n';\n\
    \            } else {\n                std::cout << st.kth(x - 1) << '\\n';\n\
    \            }\n        } else if (type == 3) {\n            std::cout << st.count_less_equal(x)\
    \ << '\\n';\n        } else if (type == 4) {\n            const int* ans = st.max_le(x);\n\
    \            std::cout << (ans ? *ans : -1) << '\\n';\n        } else {\n    \
    \        const int* ans = st.min_ge(x);\n            std::cout << (ans ? *ans\
    \ : -1) << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/bst/ordered_set.hpp
  isVerificationFile: true
  path: verify/ds/bst/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 03:01:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/ordered_set.test.cpp
- /verify/verify/ds/bst/ordered_set.test.cpp.html
title: verify/ds/bst/ordered_set.test.cpp
---
