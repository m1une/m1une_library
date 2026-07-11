---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 1 \"\
    ds/bst/persistent_ordered_multiset.hpp\"\n\n\n\n#include <cassert>\n#include <functional>\n\
    #include <initializer_list>\n#include <utility>\n#include <vector>\n\nnamespace\
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
    \ m1une\n\n\n#line 4 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\n\n\
    #include <algorithm>\n#line 7 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <set>\n#line 11 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\
    \n\nvoid randomized_test() {\n    m1une::ds::PersistentOrderedMultiset<int> tree;\n\
    \    std::multiset<int> expected;\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ old_versions;\n    std::uint64_t state = 123456789;\n\n    for (int query =\
    \ 0; query < 5000; ++query) {\n        state = state * 6364136223846793005ULL\
    \ + 1442695040888963407ULL;\n        const int key = int(state >> 32) % 100;\n\
    \        const int type = int(state % 5);\n        if (type <= 1) {\n        \
    \    tree = tree.insert(key);\n            expected.insert(key);\n        } else\
    \ if (type == 2) {\n            tree = tree.erase_one(key);\n            auto\
    \ it = expected.find(key);\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            tree = tree.erase_all(key);\n  \
    \          expected.erase(key);\n        } else {\n            auto before = tree;\n\
    \            auto [left, right] = tree.split(key);\n            tree = left.merge(right);\n\
    \            assert(before.to_vector() == tree.to_vector());\n        }\n    \
    \    if (query % 100 == 0) old_versions.push_back(tree);\n        std::vector<int>\
    \ values(expected.begin(), expected.end());\n        assert(tree.to_vector() ==\
    \ values);\n    }\n\n    for (const auto& version : old_versions) {\n        const\
    \ auto values = version.to_vector();\n        assert(int(values.size()) == version.size());\n\
    \        assert(std::is_sorted(values.begin(), values.end()));\n    }\n}\n\nvoid\
    \ fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n    randomized_test();\n\n    int N, Q;\n \
    \   std::cin >> N >> Q;\n\n    std::vector<int> a(N);\n    std::vector<int> xs;\n\
    \    xs.reserve(N);\n    for (int i = 0; i < N; i++) {\n        std::cin >> a[i];\n\
    \        xs.push_back(a[i]);\n    }\n\n    std::sort(xs.begin(), xs.end());\n\
    \    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\n    auto rank =\
    \ [&](int value) { return int(std::lower_bound(xs.begin(), xs.end(), value) -\
    \ xs.begin()); };\n\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        std::cin >> l >> r >> k;\n\n        int ok = int(xs.size()) -\
    \ 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        std::cout << xs[ok] << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/bst/persistent_ordered_multiset.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <set>\n\
    #include <vector>\n\nvoid randomized_test() {\n    m1une::ds::PersistentOrderedMultiset<int>\
    \ tree;\n    std::multiset<int> expected;\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ old_versions;\n    std::uint64_t state = 123456789;\n\n    for (int query =\
    \ 0; query < 5000; ++query) {\n        state = state * 6364136223846793005ULL\
    \ + 1442695040888963407ULL;\n        const int key = int(state >> 32) % 100;\n\
    \        const int type = int(state % 5);\n        if (type <= 1) {\n        \
    \    tree = tree.insert(key);\n            expected.insert(key);\n        } else\
    \ if (type == 2) {\n            tree = tree.erase_one(key);\n            auto\
    \ it = expected.find(key);\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            tree = tree.erase_all(key);\n  \
    \          expected.erase(key);\n        } else {\n            auto before = tree;\n\
    \            auto [left, right] = tree.split(key);\n            tree = left.merge(right);\n\
    \            assert(before.to_vector() == tree.to_vector());\n        }\n    \
    \    if (query % 100 == 0) old_versions.push_back(tree);\n        std::vector<int>\
    \ values(expected.begin(), expected.end());\n        assert(tree.to_vector() ==\
    \ values);\n    }\n\n    for (const auto& version : old_versions) {\n        const\
    \ auto values = version.to_vector();\n        assert(int(values.size()) == version.size());\n\
    \        assert(std::is_sorted(values.begin(), values.end()));\n    }\n}\n\nvoid\
    \ fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n    randomized_test();\n\n    int N, Q;\n \
    \   std::cin >> N >> Q;\n\n    std::vector<int> a(N);\n    std::vector<int> xs;\n\
    \    xs.reserve(N);\n    for (int i = 0; i < N; i++) {\n        std::cin >> a[i];\n\
    \        xs.push_back(a[i]);\n    }\n\n    std::sort(xs.begin(), xs.end());\n\
    \    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());\n\n    auto rank =\
    \ [&](int value) { return int(std::lower_bound(xs.begin(), xs.end(), value) -\
    \ xs.begin()); };\n\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        std::cin >> l >> r >> k;\n\n        int ok = int(xs.size()) -\
    \ 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        std::cout << xs[ok] << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/bst/persistent_ordered_multiset.hpp
  isVerificationFile: true
  path: verify/ds/bst/persistent_ordered_multiset.test.cpp
  requiredBy: []
  timestamp: '2026-07-12 04:39:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/persistent_ordered_multiset.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/persistent_ordered_multiset.test.cpp
- /verify/verify/ds/bst/persistent_ordered_multiset.test.cpp.html
title: verify/ds/bst/persistent_ordered_multiset.test.cpp
---
