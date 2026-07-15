---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/bst/persistent_ordered_multiset.hpp
    title: Persistent Ordered Multiset
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
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
    \ m1une {\nnamespace ds {\n\ntemplate <typename T, typename Compare>\nstruct PersistentOrderedSet;\n\
    \ntemplate <typename T, typename Compare = std::less<T>>\nstruct PersistentOrderedMultiset\
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
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4\
    \ \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\n#include <cstdint>\n\
    #line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <charconv>\n\
    #include <cstddef>\n#include <cstdio>\n#include <cstdlib>\n#line 10 \"utilities/fast_io.hpp\"\
    \n#include <cstring>\n#include <iterator>\n#include <string>\n#include <type_traits>\n\
    #line 15 \"utilities/fast_io.hpp\"\n\nnamespace m1une {\nnamespace utilities {\n\
    namespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 9 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\n\
    #include <set>\n#line 11 \"verify/ds/bst/persistent_ordered_multiset.test.cpp\"\
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
    \        assert(std::is_sorted(values.begin(), values.end()));\n    }\n}\n\nint\
    \ main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    randomized_test();\n\n    int N, Q;\n    fast_input >> N\
    \ >> Q;\n\n    std::vector<int> a(N);\n    std::vector<int> xs;\n    xs.reserve(N);\n\
    \    for (int i = 0; i < N; i++) {\n        fast_input >> a[i];\n        xs.push_back(a[i]);\n\
    \    }\n\n    std::sort(xs.begin(), xs.end());\n    xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n    auto rank = [&](int value) { return int(std::lower_bound(xs.begin(),\
    \ xs.end(), value) - xs.begin()); };\n\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        fast_input >> l >> r >> k;\n\n        int ok = int(xs.size())\
    \ - 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        fast_output << xs[ok] << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../../ds/bst/persistent_ordered_multiset.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <set>\n#include <vector>\n\nvoid randomized_test() {\n    m1une::ds::PersistentOrderedMultiset<int>\
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
    \        assert(std::is_sorted(values.begin(), values.end()));\n    }\n}\n\nint\
    \ main() {\n    m1une::utilities::FastInput fast_input;\n    m1une::utilities::FastOutput\
    \ fast_output;\n\n    randomized_test();\n\n    int N, Q;\n    fast_input >> N\
    \ >> Q;\n\n    std::vector<int> a(N);\n    std::vector<int> xs;\n    xs.reserve(N);\n\
    \    for (int i = 0; i < N; i++) {\n        fast_input >> a[i];\n        xs.push_back(a[i]);\n\
    \    }\n\n    std::sort(xs.begin(), xs.end());\n    xs.erase(std::unique(xs.begin(),\
    \ xs.end()), xs.end());\n\n    auto rank = [&](int value) { return int(std::lower_bound(xs.begin(),\
    \ xs.end(), value) - xs.begin()); };\n\n    std::vector<m1une::ds::PersistentOrderedMultiset<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; i++) {\n        versions[i + 1]\
    \ = versions[i].insert(rank(a[i]));\n    }\n\n    while (Q--) {\n        int l,\
    \ r, k;\n        fast_input >> l >> r >> k;\n\n        int ok = int(xs.size())\
    \ - 1;\n        int ng = -1;\n        while (ok - ng > 1) {\n            int mid\
    \ = (ok + ng) / 2;\n            int count_le = versions[r].count_less_equal(mid)\
    \ - versions[l].count_less_equal(mid);\n            if (count_le > k) {\n    \
    \            ok = mid;\n            } else {\n                ng = mid;\n    \
    \        }\n        }\n\n        fast_output << xs[ok] << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/bst/persistent_ordered_multiset.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/bst/persistent_ordered_multiset.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/bst/persistent_ordered_multiset.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/bst/persistent_ordered_multiset.test.cpp
- /verify/verify/ds/bst/persistent_ordered_multiset.test.cpp.html
title: verify/ds/bst/persistent_ordered_multiset.test.cpp
---
