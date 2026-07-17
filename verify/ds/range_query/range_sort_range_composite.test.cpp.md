---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/range_sort_range_composite.hpp
    title: Range Sort Range Composite
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_sort_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_sort_range_composite
  bundledCode: "#line 1 \"verify/ds/range_query/range_sort_range_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_sort_range_composite\"\
    \n\n#line 1 \"ds/range_query/range_sort_range_composite.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <limits>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for groups.\
    \ A type satisfying this concept must also obey the group\n// laws; concepts can\
    \ check the interface but not the algebraic properties.\ntemplate <typename M>\n\
    concept IsGroup = IsMonoid<M> && requires(typename M::value_type a) {\n    { M::inv(a)\
    \ } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ groups. Commutativity is a semantic requirement and\n// cannot be checked by\
    \ a C++ concept.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsGroup<M>;\n\
    \n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/segtree.hpp\"\
    \n\n\n\n#line 8 \"ds/segtree/segtree.hpp\"\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <typename T>\nconstexpr T\
    \ bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n\n}  // namespace math\n}  // namespace m1une\n\n\
    \n#line 11 \"ds/segtree/segtree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    // A generic Segment Tree utilizing C++20 Concepts for type safety.\n// It requires\
    \ a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct Segtree {\n    using T = typename Monoid::value_type;\n\n  \
    \ private:\n    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void update(int\
    \ k) {\n        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n   public:\n\
    \    // Constructs an empty segment tree.\n    Segtree() : Segtree(0) {}\n\n \
    \   // Constructs a segment tree of size `n`, initialized with the identity element.\n\
    \    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}\n\n\
    \    // Constructs a segment tree from an existing vector.\n    explicit Segtree(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) _d[_size + i] = v[i];\n        for (int i = _size - 1; i >= 1;\
    \ i--) update(i);\n    }\n    explicit Segtree(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size\
    \ + i] = std::move(v[i]);\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Constructs a segment tree from a vector of a different type U.\n\
    \    // It automatically adapts to the Monoid's initialization requirements:\n\
    \    // 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index)\
    \ if the monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit Segtree(const std::vector<U>& v) : _n(int(v.size())) {\n  \
    \      _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n\
    \        while ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2\
    \ * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) {\n          \
    \  if constexpr (requires(U x) { Monoid::make(x); }) {\n                _d[_size\
    \ + i] = Monoid::make(v[i]);\n            } else if constexpr (requires(U x, int\
    \ idx) { Monoid::make(x, idx); }) {\n                _d[_size + i] = Monoid::make(v[i],\
    \ i);\n            } else {\n                _d[_size + i] = static_cast<T>(v[i]);\n\
    \            }\n        }\n        for (int i = _size - 1; i >= 1; i--) update(i);\n\
    \    }\n\n    // Returns the number of elements.\n    int size() const {\n   \
    \     return _n;\n    }\n\n    // Returns whether the tree is empty.\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Sets the value of\
    \ the element at index `p` to `x`.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        _d[p] = x;\n        for (int\
    \ i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T get(int p) const {\n        assert(0 <= p &&\
    \ p < _n);\n        return _d[p + _size];\n    }\n\n    // Returns the value of\
    \ the element at index `p`.\n    T operator[](int p) const {\n        return get(p);\n\
    \    }\n\n    // Returns the product (result of the monoid operation) in the range\
    \ [l, r).\n    T prod(int l, int r) const {\n        assert(0 <= l && l <= r &&\
    \ r <= _n);\n        T sml = Monoid::id(), smr = Monoid::id();\n        l += _size;\n\
    \        r += _size;\n        while (l < r) {\n            if (l & 1) sml = Monoid::op(sml,\
    \ _d[l++]);\n            if (r & 1) smr = Monoid::op(_d[--r], smr);\n        \
    \    l >>= 1;\n            r >>= 1;\n        }\n        return Monoid::op(sml,\
    \ smr);\n    }\n\n    // Returns the product of the entire array.\n    T all_prod()\
    \ const {\n        return _d[1];\n    }\n\n    // Returns all elements as a vector.\n\
    \    std::vector<T> to_vector() const {\n        return to_vector(0, _n);\n  \
    \  }\n\n    // Returns the elements in the range [l, r) as a vector.\n    std::vector<T>\
    \ to_vector(int l, int r) const {\n        assert(0 <= l && l <= r && r <= _n);\n\
    \        std::vector<T> res;\n        res.reserve(r - l);\n        for (int i\
    \ = l; i < r; i++) res.push_back(_d[_size + i]);\n        return res;\n    }\n\
    \n    // Finds the largest `r` such that `f(prod(l, r))` is true.\n    // Uses\
    \ a custom functor or lambda `f`.\n    template <class F>\n    int max_right(int\
    \ l, F f) const {\n        assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (l == _n) return _n;\n        l += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm,\
    \ _d[l]))) {\n                while (l < _size) {\n                    l = (2\
    \ * l);\n                    if (f(Monoid::op(sm, _d[l]))) {\n               \
    \         sm = Monoid::op(sm, _d[l]);\n                        l++;\n        \
    \            }\n                }\n                return l - _size;\n       \
    \     }\n            sm = Monoid::op(sm, _d[l]);\n            l++;\n        }\
    \ while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the smallest\
    \ `l` such that `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int\
    \ r, F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 15 \"ds/range_query/range_sort_range_composite.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\nnamespace detail {\n\nclass RangeSortBoundarySet\
    \ {\n   private:\n    static constexpr int word_bits = 64;\n\n    int _n;\n  \
    \  std::vector<std::vector<std::uint64_t>> _levels;\n\n   public:\n    explicit\
    \ RangeSortBoundarySet(int n = 0) : _n(n) {\n        assert(n >= 0);\n       \
    \ int size = std::max(n, 1);\n        do {\n            int words = (size + word_bits\
    \ - 1) / word_bits;\n            _levels.emplace_back(words, 0);\n           \
    \ size = words;\n        } while (size > 1);\n    }\n\n    bool contains(int index)\
    \ const {\n        assert(0 <= index && index < _n);\n        return ((_levels[0][index\
    \ / word_bits] >> (index % word_bits)) & 1U) != 0;\n    }\n\n    void insert(int\
    \ index) {\n        assert(0 <= index && index < _n);\n        for (auto& level\
    \ : _levels) {\n            level[index / word_bits] |= std::uint64_t(1) << (index\
    \ % word_bits);\n            index /= word_bits;\n        }\n    }\n\n    void\
    \ erase(int index) {\n        assert(0 <= index && index < _n);\n        for (auto&\
    \ level : _levels) {\n            level[index / word_bits] &= ~(std::uint64_t(1)\
    \ << (index % word_bits));\n            if (level[index / word_bits] != 0) break;\n\
    \            index /= word_bits;\n        }\n    }\n\n    int next(int index)\
    \ const {\n        if (index < 0) index = 0;\n        for (int level = 0; level\
    \ < int(_levels.size()); level++) {\n            if (index / word_bits >= int(_levels[level].size()))\
    \ break;\n            std::uint64_t word = _levels[level][index / word_bits] >>\
    \ (index % word_bits);\n            if (word == 0) {\n                index =\
    \ index / word_bits + 1;\n                continue;\n            }\n         \
    \   index += int(std::countr_zero(word));\n            for (int lower = level\
    \ - 1; lower >= 0; lower--) {\n                index *= word_bits;\n         \
    \       std::uint64_t lower_word = _levels[lower][index / word_bits];\n      \
    \          index += int(std::countr_zero(lower_word));\n            }\n      \
    \      return std::min(index, _n);\n        }\n        return _n;\n    }\n\n \
    \   int previous(int index) const {\n        if (_n == 0 || index < 0) return\
    \ -1;\n        if (index >= _n) index = _n - 1;\n        for (int level = 0; level\
    \ < int(_levels.size()); level++) {\n            std::uint64_t word = _levels[level][index\
    \ / word_bits]\n                               << (word_bits - 1 - index % word_bits);\n\
    \            if (word == 0) {\n                index = index / word_bits - 1;\n\
    \                if (index < 0) break;\n                continue;\n          \
    \  }\n            index += 63 - int(std::countl_zero(word)) - (word_bits - 1);\n\
    \            for (int lower = level - 1; lower >= 0; lower--) {\n            \
    \    index *= word_bits;\n                std::uint64_t lower_word = _levels[lower][index\
    \ / word_bits];\n                index += 63 - int(std::countl_zero(lower_word));\n\
    \            }\n            return index;\n        }\n        return -1;\n   \
    \ }\n};\n\n}  // namespace detail\n\n// Maintains a sequence under point assignment,\
    \ range product, and range sorting\n// by distinct compressed integer keys.\n\
    template <m1une::monoid::IsMonoid Monoid>\nclass RangeSortRangeComposite {\n \
    \  public:\n    using T = typename Monoid::value_type;\n\n   private:\n    struct\
    \ Node {\n        T product;\n        T reverse_product;\n        int count;\n\
    \        int left;\n        int right;\n\n        Node(T value, int node_count)\n\
    \            : product(std::move(value)),\n              reverse_product(product),\n\
    \              count(node_count),\n              left(0),\n              right(0)\
    \ {}\n    };\n\n    int _n;\n    int _key_count;\n    int _key_height;\n    detail::RangeSortBoundarySet\
    \ _boundaries;\n    Segtree<Monoid> _segments;\n    std::vector<bool> _reversed;\n\
    \    std::vector<int> _roots;\n    std::vector<int> _key_frequency;\n    std::vector<Node>\
    \ _nodes;\n    int _node_count;\n    std::size_t _node_limit;\n\n    static int\
    \ key_height(int key_count) {\n        int result = 0;\n        while (key_count\
    \ > 1) {\n            key_count = (key_count + 1) / 2;\n            result++;\n\
    \        }\n        return result;\n    }\n\n    void reset_node_pool() {\n  \
    \      T identity = Monoid::id();\n        if (_nodes.empty()) {\n           \
    \ _nodes.emplace_back(std::move(identity), 0);\n        } else {\n           \
    \ _nodes[0] = Node(std::move(identity), 0);\n        }\n        _node_count =\
    \ 1;\n    }\n\n    int new_node(T value = Monoid::id()) {\n        int result\
    \ = _node_count++;\n        if (result == int(_nodes.size())) {\n            _nodes.emplace_back(std::move(value),\
    \ 1);\n        } else {\n            _nodes[result] = Node(std::move(value), 1);\n\
    \        }\n        return result;\n    }\n\n    void update(int node) {\n   \
    \     int left = _nodes[node].left;\n        int right = _nodes[node].right;\n\
    \        if (left == 0 && right == 0) return;\n        if (left == 0) {\n    \
    \        _nodes[node].product = _nodes[right].product;\n            _nodes[node].reverse_product\
    \ = _nodes[right].reverse_product;\n            _nodes[node].count = _nodes[right].count;\n\
    \            return;\n        }\n        if (right == 0) {\n            _nodes[node].product\
    \ = _nodes[left].product;\n            _nodes[node].reverse_product = _nodes[left].reverse_product;\n\
    \            _nodes[node].count = _nodes[left].count;\n            return;\n \
    \       }\n        _nodes[node].product = Monoid::op(_nodes[left].product, _nodes[right].product);\n\
    \        _nodes[node].reverse_product = Monoid::op(\n            _nodes[right].reverse_product,\n\
    \            _nodes[left].reverse_product\n        );\n        _nodes[node].count\
    \ = _nodes[left].count + _nodes[right].count;\n    }\n\n    void set_key(int node,\
    \ int left, int right, int key, const T& value) {\n        if (right - left ==\
    \ 1) {\n            _nodes[node].product = value;\n            _nodes[node].reverse_product\
    \ = value;\n            return;\n        }\n        int middle = (left + right)\
    \ / 2;\n        if (key < middle) {\n            if (_nodes[node].left == 0) _nodes[node].left\
    \ = new_node();\n            int child = _nodes[node].left;\n            set_key(child,\
    \ left, middle, key, value);\n        } else {\n            if (_nodes[node].right\
    \ == 0) _nodes[node].right = new_node();\n            int child = _nodes[node].right;\n\
    \            set_key(child, middle, right, key, value);\n        }\n        update(node);\n\
    \    }\n\n    std::pair<int, int> split_tree(int node, int count) {\n        if\
    \ (count == 0) return {0, node};\n        if (count == _nodes[node].count) return\
    \ {node, 0};\n\n        int second = new_node();\n        int left_count = _nodes[_nodes[node].left].count;\n\
    \        if (count <= left_count) {\n            auto [first_left, second_left]\
    \ = split_tree(_nodes[node].left, count);\n            int old_right = _nodes[node].right;\n\
    \            _nodes[node].left = first_left;\n            _nodes[node].right =\
    \ 0;\n            _nodes[second].left = second_left;\n            _nodes[second].right\
    \ = old_right;\n        } else {\n            auto [first_right, second_right]\n\
    \                = split_tree(_nodes[node].right, count - left_count);\n     \
    \       _nodes[node].right = first_right;\n            _nodes[second].left = 0;\n\
    \            _nodes[second].right = second_right;\n        }\n        update(node);\n\
    \        update(second);\n        return {node, second};\n    }\n\n    int merge_trees(int\
    \ first, int second) {\n        if (first == 0 || second == 0) return first !=\
    \ 0 ? first : second;\n        int first_left = _nodes[first].left;\n        int\
    \ first_right = _nodes[first].right;\n        _nodes[first].left = merge_trees(first_left,\
    \ _nodes[second].left);\n        _nodes[first].right = merge_trees(first_right,\
    \ _nodes[second].right);\n        update(first);\n        return first;\n    }\n\
    \n    int only_key(int node, int left, int right) const {\n        assert(node\
    \ != 0 && _nodes[node].count == 1);\n        while (right - left > 1) {\n    \
    \        int middle = (left + right) / 2;\n            if (_nodes[node].left !=\
    \ 0) {\n                node = _nodes[node].left;\n                right = middle;\n\
    \            } else {\n                node = _nodes[node].right;\n          \
    \      left = middle;\n            }\n        }\n        return left;\n    }\n\
    \n    void split_at(int position) {\n        if (position == _n || _boundaries.contains(position))\
    \ return;\n        int first = _boundaries.previous(position);\n        int next\
    \ = _boundaries.next(first + 1);\n        assert(first >= 0 && next > position);\n\
    \        _boundaries.insert(position);\n\n        if (!_reversed[first]) {\n \
    \           auto [left, right] = split_tree(_roots[first], position - first);\n\
    \            _roots[first] = left;\n            _roots[position] = right;\n  \
    \          _reversed[first] = false;\n            _reversed[position] = false;\n\
    \            _segments.set(first, _nodes[left].product);\n            _segments.set(position,\
    \ _nodes[right].product);\n        } else {\n            auto [left, right] =\
    \ split_tree(_roots[first], next - position);\n            _roots[first] = right;\n\
    \            _roots[position] = left;\n            _reversed[first] = true;\n\
    \            _reversed[position] = true;\n            _segments.set(first, _nodes[right].reverse_product);\n\
    \            _segments.set(position, _nodes[left].reverse_product);\n        }\n\
    \    }\n\n    void dump_tree(\n        int node,\n        int left,\n        int\
    \ right,\n        bool reversed,\n        std::vector<int>& keys,\n        std::vector<T>&\
    \ values\n    ) const {\n        if (node == 0) return;\n        if (right - left\
    \ == 1) {\n            assert(_nodes[node].count == 1);\n            keys.push_back(left);\n\
    \            values.push_back(_nodes[node].product);\n            return;\n  \
    \      }\n        int middle = (left + right) / 2;\n        if (!reversed) {\n\
    \            dump_tree(_nodes[node].left, left, middle, false, keys, values);\n\
    \            dump_tree(_nodes[node].right, middle, right, false, keys, values);\n\
    \        } else {\n            dump_tree(_nodes[node].right, middle, right, true,\
    \ keys, values);\n            dump_tree(_nodes[node].left, left, middle, true,\
    \ keys, values);\n        }\n    }\n\n    void initialize_runs(const std::vector<int>&\
    \ keys, const std::vector<T>& values) {\n        reset_node_pool();\n        _boundaries\
    \ = detail::RangeSortBoundarySet(_n);\n        _segments = Segtree<Monoid>(values);\n\
    \        _reversed.assign(_n, false);\n        _roots.assign(_n, 0);\n       \
    \ for (int index = 0; index < _n; index++) {\n            _boundaries.insert(index);\n\
    \            _roots[index] = new_node();\n            set_key(_roots[index], 0,\
    \ _key_count, keys[index], values[index]);\n        }\n    }\n\n    void rebuild()\
    \ {\n        std::vector<int> keys;\n        std::vector<T> values;\n        keys.reserve(_n);\n\
    \        values.reserve(_n);\n        for (int position = _boundaries.next(0);\
    \ position < _n;\n             position = _boundaries.next(position + 1)) {\n\
    \            dump_tree(\n                _roots[position],\n                0,\n\
    \                _key_count,\n                _reversed[position],\n         \
    \       keys,\n                values\n            );\n        }\n        assert(int(keys.size())\
    \ == _n);\n        initialize_runs(keys, values);\n    }\n\n    void ensure_node_space()\
    \ {\n        std::size_t margin = std::size_t(4) * std::size_t(_key_height + 2);\n\
    \        if (std::size_t(_node_count) + margin > _node_limit) rebuild();\n   \
    \ }\n\n   public:\n    RangeSortRangeComposite()\n        : _n(0),\n         \
    \ _key_count(0),\n          _key_height(0),\n          _boundaries(0),\n     \
    \     _segments(),\n          _node_count(0),\n          _node_limit(1) {\n  \
    \      reset_node_pool();\n    }\n\n    RangeSortRangeComposite(\n        int\
    \ key_count,\n        const std::vector<int>& keys,\n        const std::vector<T>&\
    \ values\n    )\n        : _n(0),\n          _key_count(key_count),\n        \
    \  _key_height(0),\n          _boundaries(0),\n          _segments(),\n      \
    \    _node_count(0),\n          _node_limit(1) {\n        assert(key_count >=\
    \ 0);\n        assert(keys.size() == values.size());\n        assert(keys.size()\
    \ <= std::size_t(std::numeric_limits<int>::max()));\n        _n = int(keys.size());\n\
    \        assert(_n == 0 || key_count > 0);\n        _key_height = key_height(key_count);\n\
    \        _key_frequency.assign(key_count, 0);\n        for (int key : keys) {\n\
    \            assert(0 <= key && key < key_count);\n            assert(_key_frequency[key]\
    \ == 0);\n            _key_frequency[key] = 1;\n        }\n\n        std::size_t\
    \ height = std::size_t(_key_height + 1);\n        std::size_t initial_nodes =\
    \ std::size_t(_n) * height + 1;\n        std::size_t slack = std::max<std::size_t>(1024,\
    \ std::size_t(8) * std::size_t(_n) + 64);\n        _node_limit = initial_nodes\
    \ + slack;\n        _nodes.reserve(_node_limit);\n        initialize_runs(keys,\
    \ values);\n        assert(std::size_t(_node_count) <= initial_nodes);\n    }\n\
    \n    int size() const {\n        return _n;\n    }\n\n    bool empty() const\
    \ {\n        return _n == 0;\n    }\n\n    int key_count() const {\n        return\
    \ _key_count;\n    }\n\n    std::pair<int, T> get(int position) {\n        assert(0\
    \ <= position && position < _n);\n        ensure_node_space();\n        split_at(position);\n\
    \        split_at(position + 1);\n        int key = only_key(_roots[position],\
    \ 0, _key_count);\n        return {key, _nodes[_roots[position]].product};\n \
    \   }\n\n    void set(int position, int key, T value) {\n        assert(0 <= position\
    \ && position < _n);\n        assert(0 <= key && key < _key_count);\n        ensure_node_space();\n\
    \        split_at(position);\n        split_at(position + 1);\n        int old_key\
    \ = only_key(_roots[position], 0, _key_count);\n        assert(key == old_key\
    \ || _key_frequency[key] == 0);\n        _key_frequency[old_key]--;\n        _key_frequency[key]++;\n\
    \n        _reversed[position] = false;\n        _roots[position] = new_node();\n\
    \        set_key(_roots[position], 0, _key_count, key, value);\n        _segments.set(position,\
    \ value);\n    }\n\n    T prod(int left, int right) {\n        assert(0 <= left\
    \ && left <= right && right <= _n);\n        if (left == right) return Monoid::id();\n\
    \        ensure_node_space();\n        split_at(left);\n        split_at(right);\n\
    \        return _segments.prod(left, right);\n    }\n\n    T all_prod() const\
    \ {\n        return _segments.all_prod();\n    }\n\n    void sort_ascending(int\
    \ left, int right) {\n        assert(0 <= left && left <= right && right <= _n);\n\
    \        if (left == right) return;\n        ensure_node_space();\n        split_at(left);\n\
    \        split_at(right);\n        while (true) {\n            int next = _boundaries.next(left\
    \ + 1);\n            if (next == right) break;\n            _roots[left] = merge_trees(_roots[left],\
    \ _roots[next]);\n            _roots[next] = 0;\n            _reversed[next] =\
    \ false;\n            _boundaries.erase(next);\n            _segments.set(next,\
    \ Monoid::id());\n        }\n        _reversed[left] = false;\n        _segments.set(left,\
    \ _nodes[_roots[left]].product);\n    }\n\n    void sort_descending(int left,\
    \ int right) {\n        assert(0 <= left && left <= right && right <= _n);\n \
    \       if (left == right) return;\n        sort_ascending(left, right);\n   \
    \     _reversed[left] = true;\n        _segments.set(left, _nodes[_roots[left]].reverse_product);\n\
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/range_sort_range_composite.test.cpp\"\
    \n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <array>\n#include <cerrno>\n\
    #include <charconv>\n#line 8 \"utilities/fast_io.hpp\"\n#include <cstdio>\n#include\
    \ <cstdlib>\n#line 11 \"utilities/fast_io.hpp\"\n#include <cstring>\n#include\
    \ <iterator>\n#include <string>\n#include <sys/stat.h>\n#include <type_traits>\n\
    #line 17 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\nnamespace m1une {\n\
    namespace utilities {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\n\
    template <class T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate\
    \ <class T>\nstruct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
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
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c > ' ') {\n            value.push_back(char(c));\n           \
    \ c = read_char_raw();\n        }\n        return true;\n    }\n\n    bool read(bool&\
    \ value) {\n        int x;\n        if (!read(x)) return false;\n        value\
    \ = x != 0;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (_streaming) return read_integer_from_stream(value);\n\
    \        if (!prepare_number()) return false;\n        int c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        while (c <= ' ') c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n\n        bool negative = false;\n        if (c\
    \ == '-') {\n            negative = true;\n            c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n        }\n\n        if constexpr (internal::is_signed_v<T>)\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               const int first = c - '0';\n                const int second =\
    \ static_cast<unsigned char>(_buffer[_position]) - '0';\n                if (0\
    \ <= second && second <= 9) {\n                    result = negative ? result\
    \ * 100 - (first * 10 + second)\n                                      : result\
    \ * 100 + (first * 10 + second);\n                    ++_position;\n         \
    \       } else {\n                    result = negative ? result * 10 - first\
    \ : result * 10 + first;\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = result;\n \
    \       } else {\n            T result = 0;\n            while ('0' <= c && c\
    \ <= '9') {\n                const unsigned first = unsigned(c - '0');\n     \
    \           const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = result * 100 + T(first * 10 + unsigned(second));\n             \
    \       ++_position;\n                } else {\n                    result = result\
    \ * 10 + T(first);\n                }\n                c = static_cast<unsigned\
    \ char>(_buffer[_position++]);\n            }\n            value = negative ?\
    \ T(0) - result : result;\n        }\n        if (_position > _length) _position\
    \ = _length;\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>,\
    \ bool>\n    read(T& value) {\n        if (!skip_spaces()) return false;\n   \
    \     int c = read_char_raw();\n        bool negative = false;\n        if (c\
    \ == '-' || c == '+') {\n            negative = c == '-';\n            c = read_char_raw();\n\
    \        }\n\n        long double result = 0;\n        while ('0' <= c && c <=\
    \ '9') {\n            result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
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
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
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
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 9 \"verify/ds/range_query/range_sort_range_composite.test.cpp\"\
    \n#include <tuple>\n#line 12 \"verify/ds/range_query/range_sort_range_composite.test.cpp\"\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 14 \"verify/ds/range_query/range_sort_range_composite.test.cpp\"\
    \n\nnamespace {\n\nusing Mint = m1une::math::modint998244353;\nusing Function\
    \ = std::pair<Mint, Mint>;\n\nstruct AffineComposition {\n    using value_type\
    \ = Function;\n\n    static value_type id() {\n        return {Mint(1), Mint(0)};\n\
    \    }\n\n    static value_type op(const value_type& left, const value_type& right)\
    \ {\n        return {\n            right.first * left.first,\n            right.first\
    \ * left.second + right.second\n        };\n    }\n};\n\nstruct Item {\n    int\
    \ key;\n    Function function;\n};\n\nFunction naive_product(const std::vector<Item>&\
    \ items, int left, int right) {\n    Function result = AffineComposition::id();\n\
    \    for (int i = left; i < right; i++) {\n        result = AffineComposition::op(result,\
    \ items[i].function);\n    }\n    return result;\n}\n\nvoid test_randomized()\
    \ {\n    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;\n\
    \    Data empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n\
    \    assert(empty.key_count() == 0);\n    assert(empty.all_prod() == AffineComposition::id());\n\
    \n    std::uint64_t state = 818181;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 600; trial++) {\n        int size = 1 + int(random()\
    \ % 18);\n        int key_count = 32;\n        std::vector<int> available(key_count);\n\
    \        for (int i = 0; i < key_count; i++) available[i] = i;\n        for (int\
    \ i = key_count - 1; i > 0; i--) {\n            std::swap(available[i], available[random()\
    \ % (i + 1)]);\n        }\n\n        std::vector<int> keys;\n        std::vector<Function>\
    \ functions;\n        std::vector<Item> items;\n        for (int i = 0; i < size;\
    \ i++) {\n            Function function = {\n                Mint(1 + random()\
    \ % 20),\n                Mint(random() % 20)\n            };\n            keys.push_back(available[i]);\n\
    \            functions.push_back(function);\n            items.push_back(Item{available[i],\
    \ function});\n        }\n\n        Data data(key_count, keys, functions);\n \
    \       assert(data.size() == size);\n        assert(!data.empty());\n       \
    \ assert(data.key_count() == key_count);\n\n        for (int operation = 0; operation\
    \ < 300; operation++) {\n            int type = int(random() % 6);\n         \
    \   int left = int(random() % (size + 1));\n            int right = int(random()\
    \ % (size + 1));\n            if (left > right) std::swap(left, right);\n    \
    \        if (type == 0) {\n                int position = int(random() % size);\n\
    \                std::vector<bool> used(key_count, false);\n                for\
    \ (const auto& item : items) used[item.key] = true;\n                int key =\
    \ items[position].key;\n                if ((random() & 1U) != 0) {\n        \
    \            do {\n                        key = int(random() % key_count);\n\
    \                    } while (used[key]);\n                }\n               \
    \ Function function = {\n                    Mint(1 + random() % 20),\n      \
    \              Mint(random() % 20)\n                };\n                data.set(position,\
    \ key, function);\n                items[position] = Item{key, function};\n  \
    \          } else if (type == 1) {\n                assert(data.prod(left, right)\
    \ == naive_product(items, left, right));\n            } else if (type == 2) {\n\
    \                data.sort_ascending(left, right);\n                std::sort(items.begin()\
    \ + left, items.begin() + right, [](const Item& a, const Item& b) {\n        \
    \            return a.key < b.key;\n                });\n            } else if\
    \ (type == 3) {\n                data.sort_descending(left, right);\n        \
    \        std::sort(items.begin() + left, items.begin() + right, [](const Item&\
    \ a, const Item& b) {\n                    return a.key > b.key;\n           \
    \     });\n            } else if (type == 4) {\n                int position =\
    \ int(random() % size);\n                auto [key, function] = data.get(position);\n\
    \                assert(key == items[position].key);\n                assert(function\
    \ == items[position].function);\n            } else {\n                assert(data.all_prod()\
    \ == naive_product(items, 0, size));\n            }\n        }\n    }\n}\n\nstruct\
    \ Query {\n    int type;\n    int first;\n    int second;\n    int third;\n  \
    \  int fourth;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \    int n, q;\n    fast_input >> n >> q;\n    std::vector<int> keys(n);\n   \
    \ std::vector<Function> functions(n);\n    std::vector<int> all_keys;\n    all_keys.reserve(n\
    \ + q);\n    for (int i = 0; i < n; i++) {\n        int a, b;\n        fast_input\
    \ >> keys[i] >> a >> b;\n        functions[i] = {Mint(a), Mint(b)};\n        all_keys.push_back(keys[i]);\n\
    \    }\n\n    std::vector<Query> queries(q);\n    for (auto& query : queries)\
    \ {\n        fast_input >> query.type;\n        if (query.type == 0) {\n     \
    \       fast_input >> query.first >> query.second >> query.third >> query.fourth;\n\
    \            all_keys.push_back(query.second);\n        } else if (query.type\
    \ == 1) {\n            fast_input >> query.first >> query.second >> query.third;\n\
    \            query.fourth = 0;\n        } else {\n            fast_input >> query.first\
    \ >> query.second;\n            query.third = query.fourth = 0;\n        }\n \
    \   }\n\n    std::sort(all_keys.begin(), all_keys.end());\n    all_keys.erase(std::unique(all_keys.begin(),\
    \ all_keys.end()), all_keys.end());\n    for (int& key : keys) {\n        key\
    \ = int(std::lower_bound(all_keys.begin(), all_keys.end(), key) - all_keys.begin());\n\
    \    }\n\n    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;\n\
    \    Data data(int(all_keys.size()), keys, functions);\n    for (const auto& query\
    \ : queries) {\n        if (query.type == 0) {\n            int key = int(\n \
    \               std::lower_bound(all_keys.begin(), all_keys.end(), query.second)\
    \ - all_keys.begin()\n            );\n            data.set(query.first, key, Function{Mint(query.third),\
    \ Mint(query.fourth)});\n        } else if (query.type == 1) {\n            Function\
    \ function = data.prod(query.first, query.second);\n            Mint answer =\
    \ function.first * Mint(query.third) + function.second;\n            fast_output\
    \ << answer << '\\n';\n        } else if (query.type == 2) {\n            data.sort_ascending(query.first,\
    \ query.second);\n        } else {\n            data.sort_descending(query.first,\
    \ query.second);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_sort_range_composite\"\
    \n\n#include \"../../../ds/range_query/range_sort_range_composite.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <tuple>\n#include <utility>\n#include <vector>\n\n#include \"../../../math/modint.hpp\"\
    \n\nnamespace {\n\nusing Mint = m1une::math::modint998244353;\nusing Function\
    \ = std::pair<Mint, Mint>;\n\nstruct AffineComposition {\n    using value_type\
    \ = Function;\n\n    static value_type id() {\n        return {Mint(1), Mint(0)};\n\
    \    }\n\n    static value_type op(const value_type& left, const value_type& right)\
    \ {\n        return {\n            right.first * left.first,\n            right.first\
    \ * left.second + right.second\n        };\n    }\n};\n\nstruct Item {\n    int\
    \ key;\n    Function function;\n};\n\nFunction naive_product(const std::vector<Item>&\
    \ items, int left, int right) {\n    Function result = AffineComposition::id();\n\
    \    for (int i = left; i < right; i++) {\n        result = AffineComposition::op(result,\
    \ items[i].function);\n    }\n    return result;\n}\n\nvoid test_randomized()\
    \ {\n    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;\n\
    \    Data empty;\n    assert(empty.empty());\n    assert(empty.size() == 0);\n\
    \    assert(empty.key_count() == 0);\n    assert(empty.all_prod() == AffineComposition::id());\n\
    \n    std::uint64_t state = 818181;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 600; trial++) {\n        int size = 1 + int(random()\
    \ % 18);\n        int key_count = 32;\n        std::vector<int> available(key_count);\n\
    \        for (int i = 0; i < key_count; i++) available[i] = i;\n        for (int\
    \ i = key_count - 1; i > 0; i--) {\n            std::swap(available[i], available[random()\
    \ % (i + 1)]);\n        }\n\n        std::vector<int> keys;\n        std::vector<Function>\
    \ functions;\n        std::vector<Item> items;\n        for (int i = 0; i < size;\
    \ i++) {\n            Function function = {\n                Mint(1 + random()\
    \ % 20),\n                Mint(random() % 20)\n            };\n            keys.push_back(available[i]);\n\
    \            functions.push_back(function);\n            items.push_back(Item{available[i],\
    \ function});\n        }\n\n        Data data(key_count, keys, functions);\n \
    \       assert(data.size() == size);\n        assert(!data.empty());\n       \
    \ assert(data.key_count() == key_count);\n\n        for (int operation = 0; operation\
    \ < 300; operation++) {\n            int type = int(random() % 6);\n         \
    \   int left = int(random() % (size + 1));\n            int right = int(random()\
    \ % (size + 1));\n            if (left > right) std::swap(left, right);\n    \
    \        if (type == 0) {\n                int position = int(random() % size);\n\
    \                std::vector<bool> used(key_count, false);\n                for\
    \ (const auto& item : items) used[item.key] = true;\n                int key =\
    \ items[position].key;\n                if ((random() & 1U) != 0) {\n        \
    \            do {\n                        key = int(random() % key_count);\n\
    \                    } while (used[key]);\n                }\n               \
    \ Function function = {\n                    Mint(1 + random() % 20),\n      \
    \              Mint(random() % 20)\n                };\n                data.set(position,\
    \ key, function);\n                items[position] = Item{key, function};\n  \
    \          } else if (type == 1) {\n                assert(data.prod(left, right)\
    \ == naive_product(items, left, right));\n            } else if (type == 2) {\n\
    \                data.sort_ascending(left, right);\n                std::sort(items.begin()\
    \ + left, items.begin() + right, [](const Item& a, const Item& b) {\n        \
    \            return a.key < b.key;\n                });\n            } else if\
    \ (type == 3) {\n                data.sort_descending(left, right);\n        \
    \        std::sort(items.begin() + left, items.begin() + right, [](const Item&\
    \ a, const Item& b) {\n                    return a.key > b.key;\n           \
    \     });\n            } else if (type == 4) {\n                int position =\
    \ int(random() % size);\n                auto [key, function] = data.get(position);\n\
    \                assert(key == items[position].key);\n                assert(function\
    \ == items[position].function);\n            } else {\n                assert(data.all_prod()\
    \ == naive_product(items, 0, size));\n            }\n        }\n    }\n}\n\nstruct\
    \ Query {\n    int type;\n    int first;\n    int second;\n    int third;\n  \
    \  int fourth;\n};\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_randomized();\n\
    \    int n, q;\n    fast_input >> n >> q;\n    std::vector<int> keys(n);\n   \
    \ std::vector<Function> functions(n);\n    std::vector<int> all_keys;\n    all_keys.reserve(n\
    \ + q);\n    for (int i = 0; i < n; i++) {\n        int a, b;\n        fast_input\
    \ >> keys[i] >> a >> b;\n        functions[i] = {Mint(a), Mint(b)};\n        all_keys.push_back(keys[i]);\n\
    \    }\n\n    std::vector<Query> queries(q);\n    for (auto& query : queries)\
    \ {\n        fast_input >> query.type;\n        if (query.type == 0) {\n     \
    \       fast_input >> query.first >> query.second >> query.third >> query.fourth;\n\
    \            all_keys.push_back(query.second);\n        } else if (query.type\
    \ == 1) {\n            fast_input >> query.first >> query.second >> query.third;\n\
    \            query.fourth = 0;\n        } else {\n            fast_input >> query.first\
    \ >> query.second;\n            query.third = query.fourth = 0;\n        }\n \
    \   }\n\n    std::sort(all_keys.begin(), all_keys.end());\n    all_keys.erase(std::unique(all_keys.begin(),\
    \ all_keys.end()), all_keys.end());\n    for (int& key : keys) {\n        key\
    \ = int(std::lower_bound(all_keys.begin(), all_keys.end(), key) - all_keys.begin());\n\
    \    }\n\n    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;\n\
    \    Data data(int(all_keys.size()), keys, functions);\n    for (const auto& query\
    \ : queries) {\n        if (query.type == 0) {\n            int key = int(\n \
    \               std::lower_bound(all_keys.begin(), all_keys.end(), query.second)\
    \ - all_keys.begin()\n            );\n            data.set(query.first, key, Function{Mint(query.third),\
    \ Mint(query.fourth)});\n        } else if (query.type == 1) {\n            Function\
    \ function = data.prod(query.first, query.second);\n            Mint answer =\
    \ function.first * Mint(query.third) + function.second;\n            fast_output\
    \ << answer << '\\n';\n        } else if (query.type == 2) {\n            data.sort_ascending(query.first,\
    \ query.second);\n        } else {\n            data.sort_descending(query.first,\
    \ query.second);\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/range_sort_range_composite.hpp
  - monoid/concept.hpp
  - ds/segtree/segtree.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - utilities/fast_io.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/range_query/range_sort_range_composite.test.cpp
  requiredBy: []
  timestamp: '2026-07-17 22:34:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/range_sort_range_composite.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/range_sort_range_composite.test.cpp
- /verify/verify/ds/range_query/range_sort_range_composite.test.cpp.html
title: verify/ds/range_query/range_sort_range_composite.test.cpp
---
