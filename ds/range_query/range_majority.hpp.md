---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/ordered_set.hpp
    title: Ordered Set
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_majority.test.cpp
    title: verify/ds/range_query/range_majority.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/range_majority.hpp\"\n\n\n\n#line 1 \"ds/bst/ordered_set.hpp\"\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/range_query/range_majority.hpp\"\
    \n\n#line 7 \"ds/range_query/range_majority.hpp\"\n#include <map>\n#include <optional>\n\
    #line 11 \"ds/range_query/range_majority.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// Strict-majority queries and point assignments in O(log N) time.\n\
    template <class T>\nstruct RangeMajority {\n    using result_type = std::optional<T>;\n\
    \n   private:\n    struct Vote {\n        int candidate = -1;\n        int balance\
    \ = 0;\n    };\n\n    int _n;\n    int _tree_size;\n    std::vector<T> _values;\n\
    \    std::map<T, int> _ranks;\n    std::vector<int> _current;\n    std::vector<OrderedSet<int>>\
    \ _positions;\n    std::vector<Vote> _tree;\n\n    int register_value(T value)\
    \ {\n        int rank = int(_values.size());\n        auto [iterator, inserted]\
    \ = _ranks.emplace(std::move(value), rank);\n        if (inserted) {\n       \
    \     _values.push_back(iterator->first);\n            _positions.emplace_back();\n\
    \        }\n        return iterator->second;\n    }\n\n    static Vote combine(Vote\
    \ first, Vote second) {\n        if (first.balance == 0) return second;\n    \
    \    if (second.balance == 0) return first;\n        if (first.candidate == second.candidate)\
    \ {\n            return Vote{first.candidate, first.balance + second.balance};\n\
    \        }\n        if (first.balance > second.balance) {\n            return\
    \ Vote{first.candidate, first.balance - second.balance};\n        }\n        if\
    \ (second.balance > first.balance) {\n            return Vote{second.candidate,\
    \ second.balance - first.balance};\n        }\n        return Vote();\n    }\n\
    \n    Vote range_vote(int left, int right) const {\n        Vote left_vote;\n\
    \        Vote right_vote;\n        left += _tree_size;\n        right += _tree_size;\n\
    \        while (left < right) {\n            if (left & 1) left_vote = combine(left_vote,\
    \ _tree[left++]);\n            if (right & 1) right_vote = combine(_tree[--right],\
    \ right_vote);\n            left >>= 1;\n            right >>= 1;\n        }\n\
    \        return combine(left_vote, right_vote);\n    }\n\n   public:\n    RangeMajority()\
    \ : _n(0), _tree_size(1), _tree(2) {}\n\n    explicit RangeMajority(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())),\n          _tree_size(1),\n     \
    \     _current(values.size()) {\n        _values.reserve(values.size());\n   \
    \     _positions.reserve(values.size());\n        while (_tree_size < _n) _tree_size\
    \ <<= 1;\n        _tree.assign(2 * _tree_size, Vote());\n        for (int index\
    \ = 0; index < _n; index++) {\n            int rank = register_value(values[index]);\n\
    \            _current[index] = rank;\n            _positions[rank].insert(index);\n\
    \            _tree[_tree_size + index] = Vote{rank, 1};\n        }\n        for\
    \ (int node = _tree_size - 1; node > 0; node--) {\n            _tree[node] = combine(_tree[node\
    \ << 1], _tree[(node << 1) | 1]);\n        }\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    // Assigns value to one position. Previously unseen values are supported.\n\
    \    void set(int index, T value) {\n        assert(0 <= index && index < _n);\n\
    \        int rank = register_value(std::move(value));\n        int previous_rank\
    \ = _current[index];\n        if (rank == previous_rank) return;\n\n        [[maybe_unused]]\
    \ bool erased =\n            _positions[previous_rank].erase(index);\n       \
    \ [[maybe_unused]] bool inserted = _positions[rank].insert(index);\n        assert(erased\
    \ && inserted);\n        _current[index] = rank;\n\n        int node = _tree_size\
    \ + index;\n        _tree[node] = Vote{rank, 1};\n        while ((node >>= 1)\
    \ != 0) {\n            _tree[node] = combine(_tree[node << 1], _tree[(node <<\
    \ 1) | 1]);\n        }\n    }\n\n    // Returns the unique value occurring more\
    \ than half the time in\n    // [left, right), or nullopt when no such value exists.\n\
    \    result_type query(int left, int right) const {\n        assert(0 <= left\
    \ && left < right && right <= _n);\n        Vote vote = range_vote(left, right);\n\
    \        if (vote.balance == 0) return std::nullopt;\n\n        const OrderedSet<int>&\
    \ positions = _positions[vote.candidate];\n        int frequency =\n         \
    \   positions.order_of_key(right) - positions.order_of_key(left);\n        if\
    \ (2LL * frequency <= right - left) return std::nullopt;\n        return _values[vote.candidate];\n\
    \    }\n\n    result_type majority(int left, int right) const {\n        return\
    \ query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_RANGE_MAJORITY_HPP\n#define M1UNE_DS_RANGE_QUERY_RANGE_MAJORITY_HPP\
    \ 1\n\n#include \"../bst/ordered_set.hpp\"\n\n#include <cassert>\n#include <map>\n\
    #include <optional>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\n// Strict-majority queries and point assignments in O(log\
    \ N) time.\ntemplate <class T>\nstruct RangeMajority {\n    using result_type\
    \ = std::optional<T>;\n\n   private:\n    struct Vote {\n        int candidate\
    \ = -1;\n        int balance = 0;\n    };\n\n    int _n;\n    int _tree_size;\n\
    \    std::vector<T> _values;\n    std::map<T, int> _ranks;\n    std::vector<int>\
    \ _current;\n    std::vector<OrderedSet<int>> _positions;\n    std::vector<Vote>\
    \ _tree;\n\n    int register_value(T value) {\n        int rank = int(_values.size());\n\
    \        auto [iterator, inserted] = _ranks.emplace(std::move(value), rank);\n\
    \        if (inserted) {\n            _values.push_back(iterator->first);\n  \
    \          _positions.emplace_back();\n        }\n        return iterator->second;\n\
    \    }\n\n    static Vote combine(Vote first, Vote second) {\n        if (first.balance\
    \ == 0) return second;\n        if (second.balance == 0) return first;\n     \
    \   if (first.candidate == second.candidate) {\n            return Vote{first.candidate,\
    \ first.balance + second.balance};\n        }\n        if (first.balance > second.balance)\
    \ {\n            return Vote{first.candidate, first.balance - second.balance};\n\
    \        }\n        if (second.balance > first.balance) {\n            return\
    \ Vote{second.candidate, second.balance - first.balance};\n        }\n       \
    \ return Vote();\n    }\n\n    Vote range_vote(int left, int right) const {\n\
    \        Vote left_vote;\n        Vote right_vote;\n        left += _tree_size;\n\
    \        right += _tree_size;\n        while (left < right) {\n            if\
    \ (left & 1) left_vote = combine(left_vote, _tree[left++]);\n            if (right\
    \ & 1) right_vote = combine(_tree[--right], right_vote);\n            left >>=\
    \ 1;\n            right >>= 1;\n        }\n        return combine(left_vote, right_vote);\n\
    \    }\n\n   public:\n    RangeMajority() : _n(0), _tree_size(1), _tree(2) {}\n\
    \n    explicit RangeMajority(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _tree_size(1),\n          _current(values.size()) {\n        _values.reserve(values.size());\n\
    \        _positions.reserve(values.size());\n        while (_tree_size < _n) _tree_size\
    \ <<= 1;\n        _tree.assign(2 * _tree_size, Vote());\n        for (int index\
    \ = 0; index < _n; index++) {\n            int rank = register_value(values[index]);\n\
    \            _current[index] = rank;\n            _positions[rank].insert(index);\n\
    \            _tree[_tree_size + index] = Vote{rank, 1};\n        }\n        for\
    \ (int node = _tree_size - 1; node > 0; node--) {\n            _tree[node] = combine(_tree[node\
    \ << 1], _tree[(node << 1) | 1]);\n        }\n    }\n\n    int size() const {\n\
    \        return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n\
    \    }\n\n    // Assigns value to one position. Previously unseen values are supported.\n\
    \    void set(int index, T value) {\n        assert(0 <= index && index < _n);\n\
    \        int rank = register_value(std::move(value));\n        int previous_rank\
    \ = _current[index];\n        if (rank == previous_rank) return;\n\n        [[maybe_unused]]\
    \ bool erased =\n            _positions[previous_rank].erase(index);\n       \
    \ [[maybe_unused]] bool inserted = _positions[rank].insert(index);\n        assert(erased\
    \ && inserted);\n        _current[index] = rank;\n\n        int node = _tree_size\
    \ + index;\n        _tree[node] = Vote{rank, 1};\n        while ((node >>= 1)\
    \ != 0) {\n            _tree[node] = combine(_tree[node << 1], _tree[(node <<\
    \ 1) | 1]);\n        }\n    }\n\n    // Returns the unique value occurring more\
    \ than half the time in\n    // [left, right), or nullopt when no such value exists.\n\
    \    result_type query(int left, int right) const {\n        assert(0 <= left\
    \ && left < right && right <= _n);\n        Vote vote = range_vote(left, right);\n\
    \        if (vote.balance == 0) return std::nullopt;\n\n        const OrderedSet<int>&\
    \ positions = _positions[vote.candidate];\n        int frequency =\n         \
    \   positions.order_of_key(right) - positions.order_of_key(left);\n        if\
    \ (2LL * frequency <= right - left) return std::nullopt;\n        return _values[vote.candidate];\n\
    \    }\n\n    result_type majority(int left, int right) const {\n        return\
    \ query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\
    \n#endif  // M1UNE_DS_RANGE_QUERY_RANGE_MAJORITY_HPP\n"
  dependsOn:
  - ds/bst/ordered_set.hpp
  isVerificationFile: false
  path: ds/range_query/range_majority.hpp
  requiredBy: []
  timestamp: '2026-07-21 22:01:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/range_majority.test.cpp
documentation_of: ds/range_query/range_majority.hpp
layout: document
title: Range Majority
---

## Overview

`RangeMajority<T>` maintains a fixed-length array under point assignments
and finds the strict majority of any nonempty half-open range `[left, right)`.
A strict majority is a value occurring more than `(right - left) / 2` times. It
is necessarily unique. The query returns `std::nullopt` when no strict majority
exists.

Each segment-tree node stores the result of Boyer--Moore cancellation. A strict
majority survives every cancellation of two unequal values, so merging the
nodes covering a query produces the only possible candidate. An order-statistics
set of current positions for each value verifies the candidate's exact
frequency and supports point assignments.

The algorithm is deterministic.

## Requirements and Behavior

`T` must be copyable and provide a strict weak ordering through `operator<`.
Construction does not modify the input vector. `set` accepts values that were
not present during construction.

Let $D$ be the number of distinct values seen by the constructor and all calls
to `set`. The structure uses $O(N + D)$ memory. It retains bookkeeping for a
value after its final occurrence is replaced.

Queries use zero-based indices and require
`0 <= left < right <= size()`. Point assignments require
`0 <= index < size()` and mutate the structure. Both query methods are `const`.

## Interface

| Method | Exact signature | Description | Complexity |
| --- | --- | --- | --- |
| Constructor | `RangeMajority()` | Constructs an empty structure. | $O(1)$ |
| Constructor | `explicit RangeMajority(const std::vector<T>& values)` | Preprocesses `values`. | $O(N\log N)$ time |
| `size` | `int size() const` | Returns the array length. | $O(1)$ |
| `empty` | `bool empty() const` | Returns whether the array is empty. | $O(1)$ |
| `set` | `void set(int index, T value)` | Assigns `value` to position `index`. | Amortized $O(\log N + \log D)$ |
| `query` | `std::optional<T> query(int left, int right) const` | Returns the strict majority of `[left, right)`, or `std::nullopt`. | $O(\log N)$ |
| `majority` | `std::optional<T> majority(int left, int right) const` | Alias of `query`. | $O(\log N)$ |

`result_type` is an alias of `std::optional<T>`.

## Example

```cpp
#include "ds/range_query/range_majority.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {2, 1, 2, 2, 3, 3};
    m1une::ds::RangeMajority<int> majority(values);

    auto first = majority.query(0, 4);
    if (first) std::cout << *first << '\n';  // 2

    majority.set(1, 3);
    auto second = majority.query(1, 6);
    if (second) std::cout << *second << '\n';  // 3
}
```
