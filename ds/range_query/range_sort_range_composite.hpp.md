---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/range_sort_range_composite.test.cpp
    title: verify/ds/range_query/range_sort_range_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/range_sort_range_composite.hpp\"\n\n\n\n\
    #include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 1 \"ds/segtree/segtree.hpp\"\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP\n#define M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP\
    \ 1\n\n#include <algorithm>\n#include <bit>\n#include <cassert>\n#include <cstddef>\n\
    #include <cstdint>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../monoid/concept.hpp\"\n#include \"../segtree/segtree.hpp\"\n\
    \nnamespace m1une {\nnamespace ds {\n\nnamespace detail {\n\nclass RangeSortBoundarySet\
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
    \    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - ds/segtree/segtree.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/range_sort_range_composite.hpp
  requiredBy: []
  timestamp: '2026-07-14 01:05:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/range_sort_range_composite.test.cpp
documentation_of: ds/range_query/range_sort_range_composite.hpp
layout: document
title: Range Sort Range Composite
---

## Overview

`RangeSortRangeComposite<Monoid>` maintains a fixed-length sequence of distinct
integer keys and monoid values. It supports point replacement, range products,
and sorting any half-open range by key in ascending or descending order.

Internally, each currently sorted run is represented by a dynamic key segment
tree that stores both forward and reverse products. A boundary set and an outer
segment tree combine the runs. This is commonly called a sortable segment tree.

## Template and Key Requirements

`Monoid` must satisfy `m1une::monoid::IsMonoid`:

```cpp
using value_type = T;
static T id();
static T op(const T& left, const T& right);
```

The supplied keys must be distinct integers in `[0, key_count)`. Every `set`
must preserve this property. Coordinate-compress all initial and future keys
before construction when the original key values are arbitrary.

`Monoid::op` need not be commutative. Products preserve the current left-to-right
sequence order.

## Public Interface

| Method | Description | Complexity |
| --- | --- | --- |
| `RangeSortRangeComposite()` | Constructs an empty sequence with no key domain. | $O(1)$ |
| `RangeSortRangeComposite(int key_count, const std::vector<int>& keys, const std::vector<T>& values)` | Constructs the sequence. `keys.size()` must equal `values.size()`. | $O(N\log K)$ time and memory |
| `int size() const` | Returns the sequence length. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `int key_count() const` | Returns the compressed key-domain size. | $O(1)$ |
| `std::pair<int, T> get(int position)` | Returns the key and value at `position`. | Amortized $O(\log K\log N)$ |
| `void set(int position, int key, T value)` | Replaces one key-value pair. | Amortized $O(\log K\log N)$ |
| `T prod(int left, int right)` | Returns the ordered monoid product over `[left, right)`. | Amortized $O(\log K\log N)$ |
| `T all_prod() const` | Returns the product of the complete sequence. | $O(1)$ |
| `void sort_ascending(int left, int right)` | Sorts `[left, right)` by increasing key. | Amortized $O((B+1)(\log K+\log N))$ |
| `void sort_descending(int left, int right)` | Sorts `[left, right)` by decreasing key. | Amortized $O((B+1)(\log K+\log N))$ |

Here, $N$ is the sequence length, $K$ is `key_count`, and $B$ is the number of
stored run boundaries removed by a sort. Across operations, a boundary must be
created before it can be removed, so the boundary-dependent work amortizes.
The implementation periodically rebuilds its internal node pool without
changing the logical sequence.

`get`, `set`, `prod`, and sorting may refine or merge the internal run
partition, so they are mutating member functions. `all_prod` does not mutate
the representation.

## Example

This example stores affine functions. The monoid operation composes the right
function after the left function, matching left-to-right sequence application.

```cpp
#include "ds/range_query/range_sort_range_composite.hpp"

#include <iostream>
#include <utility>
#include <vector>

struct Affine {
    using value_type = std::pair<long long, long long>;

    static value_type id() {
        return {1, 0};
    }

    static value_type op(const value_type& left, const value_type& right) {
        return {
            right.first * left.first,
            right.first * left.second + right.second
        };
    }
};

int main() {
    std::vector<int> keys = {2, 0, 1};
    std::vector<Affine::value_type> functions;
    functions.emplace_back(2, 1);
    functions.emplace_back(1, 3);
    functions.emplace_back(3, 0);

    m1une::ds::RangeSortRangeComposite<Affine> data(3, keys, functions);
    data.sort_ascending(0, 3);

    auto composed = data.prod(0, 3);
    long long x = 4;
    std::cout << composed.first * x + composed.second << "\n";
}
```
